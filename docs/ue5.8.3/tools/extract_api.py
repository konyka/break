#!/usr/bin/env python3
"""Exhaustive API / data-dictionary extractor for the Unreal Engine source tree.

For every module (a directory holding a *.Build.cs) it collects all C/C++ headers,
runs universal-ctags, enriches each symbol with its full declaration text, the
preceding reflection macros (UCLASS/UFUNCTION/UPROPERTY/...) and the doc comment,
then writes Markdown (one or more files per module) and a compact TSV symbol index
that coverage_check.py uses to prove nothing was dropped.
"""
import argparse
import bisect
import gzip
import json
import os
import re
import subprocess
import sys
from collections import defaultdict
from multiprocessing import Pool
from pathlib import Path

HDR_EXT = (".h", ".hpp", ".inl")
SKIP_DIRS = {"ThirdParty", "Intermediate", "Binaries", ".git", "Saved", "obj", "bin"}
TEST_DIRS = {"Tests", "Test", "LowLevelTests"}
PART_LIMIT = 3 * 1024 * 1024

REFLECT_RE = re.compile(
    r"\b(UCLASS|USTRUCT|UENUM|UINTERFACE|UFUNCTION|UPROPERTY|UDELEGATE|UE_DEPRECATED|UE_DEPRECATED_FORGAME|"
    r"UE_EXPERIMENTAL|RIGVM_METHOD|DEPRECATED_CHARACTER_MOVEMENT_RPC)\s*\(")
DELEGATE_RE = re.compile(
    r"^\s*(DECLARE_(?:DYNAMIC_)?(?:MULTICAST_)?(?:DELEGATE|EVENT|TS_MULTICAST_DELEGATE|DERIVED_EVENT)\w*|"
    r"DECLARE_LOG_CATEGORY_(?:EXTERN|CLASS)|DECLARE_STATS_GROUP\w*|DECLARE_CYCLE_STAT_EXTERN|"
    r"DECLARE_(?:DWORD|FLOAT|MEMORY)_\w*STAT_EXTERN|DECLARE_GPU_STAT\w*|RENDERER_API\s+DECLARE_\w+)\s*\(")
API_RE = re.compile(r"\b[A-Z][A-Z0-9_]*_API\b\s*")
ATTR_LINE_RE = re.compile(r"^\s*(\[\[.*\]\]|PRAGMA_\w+.*|UE_[A-Z_]+\s*(\(.*\))?\s*)$")
SECTION_MARK_RE = re.compile(r"^\s*(//\s*~|//\s*~?\s*(Begin|End)\b|///+\s*$|//+\s*[-=*_/]{4,}\s*$)")


# --------------------------------------------------------------------------- discovery
def find_modules(engine: Path):
    """Return {module_dir: (tier, name, build_cs)} for Source/, Plugins/, Platforms/."""
    mods = {}
    for top in ("Source", "Plugins", "Platforms"):
        base = engine / top
        for dp, dns, fns in os.walk(base):
            dns[:] = [d for d in dns if d not in SKIP_DIRS]
            for fn in fns:
                if fn.lower().endswith(".build.cs"):
                    p = Path(dp)
                    rel = p.relative_to(engine).parts
                    if top == "Source":
                        tier = rel[1] if len(rel) > 1 else "Source"
                    else:
                        tier = top
                    mods[str(p)] = (tier, fn[:-len(".Build.cs")], str(p / fn))
    return mods


def collect_headers(engine: Path, mods):
    """Assign each header to the deepest enclosing module directory."""
    by_module = defaultdict(list)
    excluded_tests = 0
    for top in ("Source", "Plugins", "Platforms"):
        for dp, dns, fns in os.walk(engine / top):
            dns[:] = [d for d in dns if d not in SKIP_DIRS]
            hs = [f for f in fns if f.endswith(HDR_EXT)]
            if not hs:
                continue
            parts = Path(dp).relative_to(engine).parts
            if any(x in TEST_DIRS for x in parts):
                excluded_tests += len(hs)
                continue
            cur = Path(dp)
            owner = None
            while True:
                if str(cur) in mods:
                    owner = str(cur)
                    break
                if cur == engine or cur.parent == cur:
                    break
                cur = cur.parent
            for f in hs:
                full = os.path.join(dp, f)
                if owner is None:
                    rel = Path(dp).relative_to(engine).parts
                    tier = rel[1] if top == "Source" and len(rel) > 1 else top
                    key = f"_nomodule/{tier}/{'/'.join(rel[:4])}"
                    by_module[("nomodule", key)].append(full)
                else:
                    by_module[("module", owner)].append(full)
    return by_module, excluded_tests


# --------------------------------------------------------------------------- build.cs
LIST_RE = re.compile(
    r"(\w*(?:Dependency|IncludePath|Dynamically)\w*ModuleNames)\s*\.\s*(?:AddRange\s*\(\s*new\s+string\s*\[\s*\]\s*\{(.*?)\}\s*\)|Add\s*\(\s*\"([^\"]+)\"\s*\))",
    re.S)


def parse_build_cs(path):
    try:
        txt = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return {}
    out = defaultdict(list)
    for m in LIST_RE.finditer(txt):
        key = m.group(1)
        if m.group(2) is not None:
            out[key] += re.findall(r"\"([^\"]+)\"", m.group(2))
        else:
            out[key].append(m.group(3))
    return {k: sorted(set(v)) for k, v in out.items()}


# --------------------------------------------------------------------------- statement-level macros
# Function-like macros invoked on a line of their own (no trailing `;` needed) make ctags glue the invocation onto
# the next declaration.  The set is measured from the source tree (scan_macro_usage) and every such macro is passed
# to ctags as `-I NAME+`; the invocations themselves are re-emitted as `macro-arg` / `macro-call` records.
# Macros that open or close a brace scope are mapped to an equivalent declaration with `-D` instead.
BASE_IGNORE = [
    "FORCEINLINE", "FORCENOINLINE", "UE_FORCEINLINE_HINT", "UE_NODISCARD", "UE_NODISCARD_CTOR",
    "UE_INTERNAL", "UE_EXPERIMENTAL+", "UE_AUTORTFM_ALWAYS_OPEN", "UE_AUTORTFM_ALWAYS_OPEN_NO_MEMORY_VALIDATION",
    "CONSTEXPR", "VARARGS", "CDECL", "STDCALL", "MS_ALIGN+", "GCC_ALIGN+", "FORCEINLINE_DEBUGGABLE",
    "UE_ASSUME_UNREACHABLE", "RESTRICT", "DLLEXPORT", "DLLIMPORT", "UE_STATIC_ONLY+", "UE_NONCOPYABLE+",
    "UE_REQUIRES+", "UE_DEPRECATED+", "UE_DEPRECATED_FORGAME+", "UCLASS+", "USTRUCT+", "UENUM+", "UINTERFACE+",
    "UFUNCTION+", "UPROPERTY+", "UDELEGATE+", "UMETA+", "UPARAM+", "UE_LIFETIMEBOUND",
    "GENERATED_BODY+", "GENERATED_UCLASS_BODY+",
    "GENERATED_USTRUCT_BODY+", "GENERATED_IINTERFACE_BODY+", "GENERATED_UINTERFACE_BODY+",
    "DECLARE_CLASS+", "DECLARE_CLASS_INTRINSIC+", "DECLARE_FUNCTION+", "DECLARE_VIRTUAL_TYPE_LAYOUT+",
    "DECLARE_TYPE_LAYOUT+", "LAYOUT_FIELD+", "LAYOUT_BITFIELD+", "LAYOUT_ARRAY+", "LAYOUT_FIELD_INITIALIZED+",
    "LAYOUT_FIELD_EDITORONLY+", "LAYOUT_MUTABLE_FIELD+", "UE_DECLARE_COMPONENT_ACTOR_INTERFACE+",
    "RIGVM_METHOD+", "DEPRECATED_CHARACTER_MOVEMENT_RPC+"]
SCOPE_DEFINES = {
    "SLATE_BEGIN_ARGS": "SLATE_BEGIN_ARGS(T)=struct FArguments { FArguments()",
    "SLATE_USER_ARGS": "SLATE_USER_ARGS(T)=struct FArguments { FArguments()",
    "SLATE_END_ARGS": "SLATE_END_ARGS()=};",
    "SLATE_SLOT_BEGIN_ARGS": "SLATE_SLOT_BEGIN_ARGS(...)=struct FSlotArguments {",
    "SLATE_SLOT_BEGIN_ARGS_OneMixin": "SLATE_SLOT_BEGIN_ARGS_OneMixin(...)=struct FSlotArguments {",
    "SLATE_SLOT_BEGIN_ARGS_TwoMixins": "SLATE_SLOT_BEGIN_ARGS_TwoMixins(...)=struct FSlotArguments {",
    "SLATE_SLOT_BEGIN_ARGS_ThreeMixins": "SLATE_SLOT_BEGIN_ARGS_ThreeMixins(...)=struct FSlotArguments {",
    "SLATE_SLOT_BEGIN_ARGS_FourMixins": "SLATE_SLOT_BEGIN_ARGS_FourMixins(...)=struct FSlotArguments {",
    "SLATE_SLOT_END_ARGS": "SLATE_SLOT_END_ARGS()=};",
    "BEGIN_SHADER_PARAMETER_STRUCT": "BEGIN_SHADER_PARAMETER_STRUCT(N,...)=struct N {",
    "END_SHADER_PARAMETER_STRUCT": "END_SHADER_PARAMETER_STRUCT(...)=};",
    "BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT": "BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(N,...)=struct N {",
    "BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT_WITH_CONSTRUCTOR":
        "BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT_WITH_CONSTRUCTOR(N,...)=struct N {",
    "END_GLOBAL_SHADER_PARAMETER_STRUCT": "END_GLOBAL_SHADER_PARAMETER_STRUCT(...)=};",
    "BEGIN_UNIFORM_BUFFER_STRUCT": "BEGIN_UNIFORM_BUFFER_STRUCT(N,...)=struct N {",
    "BEGIN_UNIFORM_BUFFER_STRUCT_WITH_CONSTRUCTOR": "BEGIN_UNIFORM_BUFFER_STRUCT_WITH_CONSTRUCTOR(N,...)=struct N {",
    "END_UNIFORM_BUFFER_STRUCT": "END_UNIFORM_BUFFER_STRUCT(...)=};",
    "CARBON_NAMESPACE_BEGIN": "CARBON_NAMESPACE_BEGIN(N)=namespace N {",
    "CARBON_NAMESPACE_END": "CARBON_NAMESPACE_END(...)=}",
    "PURE_VIRTUAL": "PURE_VIRTUAL(...)={}",
}
# annotations of the following declaration: attached to it as reflection-like metadata, no record of their own
ANNOTATION_MACROS = {"UE_DEPRECATED", "UE_DEPRECATED_FORGAME", "UE_EXPERIMENTAL", "RIGVM_METHOD",
                     "DEPRECATED_CHARACTER_MOVEMENT_RPC", "UCLASS", "USTRUCT", "UENUM", "UINTERFACE", "UFUNCTION",
                     "UPROPERTY", "UDELEGATE", "UMETA", "UPARAM", "GENERATED_BODY", "GENERATED_UCLASS_BODY",
                     "GENERATED_USTRUCT_BODY", "GENERATED_IINTERFACE_BODY", "GENERATED_UINTERFACE_BODY",
                     "UE_REQUIRES", "MS_ALIGN", "GCC_ALIGN", "PURE_VIRTUAL", "UE_STATIC_ONLY", "UE_NONCOPYABLE"}
NOT_STATEMENT_MACROS = {"TEXT", "LOCTEXT", "NSLOCTEXT", "INVTEXT", "UTF8TEXT", "WIDETEXT"}
MACRO_ARG_RE = re.compile(r"^(?:SLATE_(?:\w+_)?(?:ARGUMENT|ATTRIBUTE|EVENT|SLOT)(?:_\w+)?|SHADER_PARAMETER\w*|"
                          r"RDG_(?:BUFFER|TEXTURE)_ACCESS\w*)$")
DEFINE_RE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Z_][A-Za-z0-9_]*)\(")
LINE_CALL_RE = re.compile(r"^[ \t]*([A-Z_][A-Z0-9_]*)[ \t]*\(", re.M)
LITERAL_RE = re.compile(r'R"([^(\s"]{0,16})\((?:.|\n)*?\)\1"|//[^\n]*|/\*(?:.|\n)*?\*/|"(?:\\.|[^"\\\n])*"|'
                        r"'(?:\\.|[^'\\\n]){1,8}'")


def mask_code(txt):
    """Same-length copy with comments and string/char literal contents replaced by spaces."""
    def blank(m):
        t = m.group(0)
        if t.startswith("/"):
            return re.sub(r"[^\n]", " ", t)
        return t[0] + re.sub(r"[^\n]", " ", t[1:-1]) + t[-1] if len(t) >= 2 else t
    return LITERAL_RE.sub(blank, txt)


PP_RE = re.compile(r"^[ \t]*#[ \t]*(if|ifdef|ifndef|elif|else|endif)\b(.*)$")


def _pp_truth(cond):
    c = re.sub(r"//.*|/\*.*?\*/", "", cond).strip()
    while c.startswith("(") and c.endswith(")"):
        c = c[1:-1].strip()
    if c in ("0", "false"):
        return False
    if c in ("1", "true"):
        return True
    if re.fullmatch(r"0\s*&&.*", c):
        return False
    return None


def dead_lines(lines):
    """1-based line numbers inside never-compiled branches (`#if 0`, `#if false`, the `#else` of `#if 1`, ...).
    Nested conditionals inside a dead branch are dead as a whole; unknown conditions keep every branch live."""
    dead, stack = set(), []
    for i, l in enumerate(lines, 1):
        m = PP_RE.match(l)
        parent_dead = bool(stack) and stack[-1][0]
        if m:
            d, cond = m.group(1), m.group(2)
            if d in ("if", "ifdef", "ifndef"):
                if parent_dead:
                    stack.append([True, "dead-parent"])
                else:
                    t = _pp_truth(cond) if d == "if" else None
                    stack.append([t is False, {True: "taken", False: "none", None: "unknown"}[t]])
                continue
            if not stack:
                continue
            top = stack[-1]
            outer_dead = len(stack) > 1 and stack[-2][0]
            if d == "endif":
                stack.pop()
                continue
            if top[1] == "dead-parent" or outer_dead:
                top[0] = True
            elif top[1] == "taken":
                top[0] = True
            elif d == "else":
                top[0] = False
            else:
                t = _pp_truth(cond) if top[1] == "none" else None
                if top[1] == "none" and t is False:
                    top[0] = True
                else:
                    top[0] = False
                    if top[1] == "none":
                        top[1] = "taken" if t else "unknown"
            continue
        if parent_dead:
            dead.add(i)
    return dead


def _match(code, i, op, cl, limit=20000):
    d = 0
    for j in range(i, min(len(code), i + limit)):
        c = code[j]
        if c == op:
            d += 1
        elif c == cl:
            d -= 1
            if d == 0:
                return j
    return -1


TEMPLATE_ENUM_RE = re.compile(r"([<,]\s*)enum(\s+[A-Za-z_][\w:]*\s*[>,])")
BRACED_INIT_RE = re.compile(r"(?<![=!<>+\-*/%&|^])=\s*(?:typename\s+)?(?:::)?[A-Za-z_][\w:]*\s*(<)?")


def sanitize_for_ctags(txt, dead):
    """Line-preserving rewrite of constructs universal-ctags mis-parses: dead `#if` branches are blanked,
    `TEnumAsByte<enum E>` loses the elaborated `enum`, and `= T{...}` / `= T<..>{...}` initialisers use (...)."""
    lines = txt.split("\n")
    for ln in dead:
        lines[ln - 1] = ""
    txt = "\n".join(lines)
    txt = TEMPLATE_ENUM_RE.sub(lambda m: m.group(1) + "    " + m.group(2), txt)
    code = mask_code(txt)
    out = None
    pos = 0
    while True:
        m = BRACED_INIT_RE.search(code, pos)
        if not m:
            break
        k = m.end()
        if m.group(1):
            depth = 1
            while k < len(code) and depth and code[k] not in ";{}":
                depth += {"<": 1, ">": -1}.get(code[k], 0)
                k += 1
            if depth:
                pos = m.end()
                continue
        while k < len(code) and code[k] in " \t\n":
            k += 1
        if k >= len(code) or code[k] != "{":
            pos = m.end()
            continue
        e = _match(code, k, "{", "}")
        if e < 0:
            pos = k + 1
            continue
        if out is None:
            out = list(txt)
        for q in range(k, e + 1):
            if code[q] == "{":
                out[q] = "("
            elif code[q] == "}":
                out[q] = ")"
        pos = e + 1
    return "".join(out) if out is not None else txt


def scan_macro_usage(path):
    """-> (defined function-like macros {name: brace balance}, line-start invocations [(name, scope, next, semi)])."""
    try:
        txt = open(path, encoding="utf-8", errors="replace").read().lstrip("\ufeff").replace("\r\n", "\n")
    except OSError:
        return {}, []
    raw_lines = txt.split("\n")
    defs = {}
    i = 0
    while i < len(raw_lines):
        m = DEFINE_RE.match(raw_lines[i])
        if m:
            body, j = raw_lines[i], i
            while body.rstrip().endswith("\\") and j + 1 < len(raw_lines):
                j += 1
                body = body.rstrip()[:-1] + "\n" + raw_lines[j]
            b = mask_code(body)
            defs[m.group(1)] = defs.get(m.group(1), 0) or (b.count("{") - b.count("}"))
            i = j
        i += 1
    if not path.endswith(HDR_EXT):
        return defs, []
    dead = dead_lines(raw_lines)
    code_lines = mask_code(txt).split("\n")
    for k, l in enumerate(code_lines):
        if (k + 1) in dead or l.lstrip().startswith("#"):
            code_lines[k] = " " * len(l)
    for k in range(len(code_lines) - 1):
        if raw_lines[k].lstrip().startswith("#"):
            kk = k
            while raw_lines[kk].rstrip().endswith("\\") and kk + 1 < len(code_lines):
                kk += 1
                code_lines[kk] = " " * len(code_lines[kk])
    code = "\n".join(code_lines)
    calls = []
    toks = [(m.start(), m.group()) for m in re.finditer(r"[{}()]", code)]
    stack, ti, pdepth = [], 0, 0
    for m in LINE_CALL_RE.finditer(code):
        name = m.group(1)
        off = m.start(1)
        while ti < len(toks) and toks[ti][0] < off:
            p, c = toks[ti]
            if c == "(":
                pdepth += 1
            elif c == ")":
                pdepth = max(0, pdepth - 1)
            elif c == "{":
                head = code[max(0, p - 400):p]
                head = re.split(r"[;{}]", head)[-1]
                if re.search(r"\b(class|struct|union)\b", head) and "(" not in head.replace("()", "") \
                        and "=" not in head:
                    stack.append("cls")
                elif re.search(r"\bnamespace\b|extern\s*\"", head) or re.search(r"\bextern\s*$", head):
                    stack.append("ns")
                else:
                    stack.append("other")
            elif stack:
                stack.pop()
            ti += 1
        if pdepth:
            continue
        scope = stack[-1] if stack else "ns"
        if scope == "other":
            continue
        prev = code[:off].rstrip()[-1:] if code[:off].strip() else ";"
        if prev not in ";{}:)":
            continue
        e = _match(code, m.end() - 1, "(", ")")
        if e < 0:
            continue
        nl = code.find("\n", e)
        rest = code[e + 1: nl if nl >= 0 else len(code)].strip()
        if rest not in ("", ";"):
            continue
        k = e + 1
        while k < len(code) and code[k] in " \t\n;":
            k += 1
        calls.append((name, scope, code[k:k + 1], rest == ";"))
    return defs, calls


def compute_macro_rules(engine, jobs):
    files = []
    for top in ("Source", "Plugins", "Platforms"):
        for dp, dns, fns in os.walk(engine / top):
            dns[:] = [d for d in dns if d not in SKIP_DIRS]
            files += [os.path.join(dp, f) for f in fns if f.endswith(HDR_EXT + (".cpp",))]
    defs, uses = {}, defaultdict(lambda: defaultdict(int))
    with Pool(jobs) as pool:
        for d, calls in pool.imap_unordered(scan_macro_usage, files, chunksize=64):
            for k, v in d.items():
                defs[k] = defs.get(k, 0) or v
            for name, scope, nxt, semi in calls:
                u = uses[name]
                u["total"] += 1
                u["semi" if semi else "nosemi"] += 1
                if not semi and nxt in ("{", ":"):
                    u["opens_body"] += 1
    base = {x.rstrip("+") for x in BASE_IGNORE}
    ignore, skipped = [], {}
    for name, u in sorted(uses.items()):
        if name in SCOPE_DEFINES or name in base:
            continue
        if name not in defs:
            skipped[name] = "not a #define'd function-like macro"
        elif name in NOT_STATEMENT_MACROS:
            skipped[name] = "expression macro"
        elif u["opens_body"]:
            skipped[name] = "introduces a body/initialiser on the next line"
        else:
            ignore.append(name)
    rules = {"ignore": ignore, "defines": sorted(SCOPE_DEFINES.values()), "base_ignore": BASE_IGNORE,
             "skipped": skipped,
             "usage": {n: dict(uses[n], brace_balance=defs.get(n)) for n in ignore + sorted(skipped)}}
    return rules


# --------------------------------------------------------------------------- ctags
def ctags_options(api_macros, rules, optfile):
    ign = sorted(api_macros) + BASE_IGNORE + [n + "+" for n in rules["ignore"]]
    with open(optfile, "w", encoding="utf-8") as f:
        for d in rules["defines"]:
            f.write(f"-D{d}\n")
        for i in range(0, len(ign), 200):
            f.write("-I" + ",".join(ign[i:i + 200]) + "\n")
    return [
        "--language-force=C++", "--output-format=json", "--sort=no",
        "--kinds-C++=+cdefgmnpstuvxU", "--fields=+SaitKzne",
        f"--options={optfile}",
    ]


def run_ctags(files, opts):
    p = subprocess.run(["ctags", "-f", "-", "-L", "-"] + opts, input="\n".join(files), text=True,
                       capture_output=True)
    tags = []
    for ln in p.stdout.splitlines():
        if not ln.startswith("{"):
            continue
        try:
            tags.append(json.loads(ln))
        except json.JSONDecodeError:
            pass
    return tags


# --------------------------------------------------------------------------- source scanning
class SrcFile:
    __slots__ = ("path", "lines", "macros_by_end", "delegates", "dead", "text", "code_lines")

    def __init__(self, path):
        self.path = path
        txt = open(path, encoding="utf-8", errors="replace").read().lstrip("\ufeff")
        self.lines = [l.rstrip("\r") for l in txt.split("\n")]
        txt = "\n".join(self.lines)
        self.text = txt
        self.dead = dead_lines(self.lines)
        masked = mask_code(txt)
        self.code_lines = masked.split("\n")
        self.macros_by_end = {}
        self.delegates = []
        nl = [m.start() for m in re.finditer("\n", txt)]
        for m in REFLECT_RE.finditer(masked):
            open_pos = m.end() - 1
            end = self._match_paren(txt, open_pos)
            if end < 0:
                continue
            sline = bisect.bisect_left(nl, m.start()) + 1
            if sline in self.dead or self.code_lines[sline - 1].lstrip().startswith("#"):
                continue
            eline = bisect.bisect_left(nl, end) + 1
            args = re.sub(r"\s+", " ", txt[open_pos + 1:end]).strip()
            self.macros_by_end[eline] = (m.group(1), args, sline)
        for i, l in enumerate(self.lines, 1):
            if i not in self.dead and DELEGATE_RE.match(l):
                self.delegates.append(i)

    @staticmethod
    def _match_paren(txt, pos):
        depth, i, n, instr = 0, pos, len(txt), False
        lim = min(n, pos + 4000)
        while i < lim:
            c = txt[i]
            if instr:
                if c == "\\":
                    i += 1
                elif c == '"':
                    instr = False
            else:
                if c == '"':
                    instr = True
                elif c == "(":
                    depth += 1
                elif c == ")":
                    depth -= 1
                    if depth == 0:
                        return i
            i += 1
        return -1


COMMENT_RE = re.compile(r"//.*?$|/\*.*?\*/", re.S | re.M)


def strip_comments(s):
    return COMMENT_RE.sub(" ", s)


def clean_decl(s):
    s = strip_comments(s)
    s = API_RE.sub("", s)
    s = re.sub(r"\s+", " ", s).strip()
    return s


def forward_decl(lines, i, kind):
    """Collect declaration text starting at 1-based line i."""
    buf, depth, brace = [], 0, 0
    by_semicolon_only = kind in ("member", "variable", "externvar", "typedef")
    for ln in range(i - 1, min(len(lines), i + 39)):
        line = lines[ln]
        code = re.sub(r'"(?:\\.|[^"\\])*"', '""', line)
        code = code.split("//")[0] if "/*" not in code else code
        for ci, ch in enumerate(code):
            if ch in "([":
                depth += 1
            elif ch in ")]":
                depth -= 1
            elif ch == "{":
                if not by_semicolon_only and depth <= 0:
                    buf.append(line[:ci] if line is lines[ln] else line)
                    return " ".join(buf)
                brace += 1
            elif ch == "}":
                brace -= 1
            elif ch == ";" and depth <= 0 and brace <= 0:
                buf.append(line[:ci + 1])
                return " ".join(buf)
        buf.append(line)
    return " ".join(buf)


def enumerator_text(lines, i):
    buf, depth = [], 0
    for ln in range(i - 1, min(len(lines), i + 7)):
        code = strip_comments(lines[ln])
        for ci, ch in enumerate(code):
            if ch in "([{":
                depth += 1
            elif ch in ")]":
                depth -= 1
            elif ch == "}":
                if depth == 0:
                    buf.append(code[:ci])
                    return " ".join(buf)
                depth -= 1
            elif ch == "," and depth == 0:
                buf.append(code[:ci])
                return " ".join(buf)
        buf.append(code)
    return " ".join(buf)


def decl_start(lines, i):
    """Walk up over template<...> headers."""
    s = i
    for k in range(1, 4):
        j = i - k
        if j < 1:
            break
        t = lines[j - 1].strip()
        if t.startswith("template") or t.startswith("requires"):
            s = j
            continue
        if t.endswith(",") or t.endswith("<") or (t.endswith(">") and s != i):
            s = j
            continue
        break
    return s


def doc_above(lines, j):
    """Comment block ending at 1-based line j (inclusive)."""
    if j < 1:
        return ""
    t = lines[j - 1].strip()
    out = []
    if t.endswith("*/"):
        k = j
        while k >= 1:
            out.append(lines[k - 1])
            if "/*" in lines[k - 1]:
                break
            k -= 1
        if k < 1 or not lines[k - 1].strip().startswith("/*"):
            return ""
        out.reverse()
    elif t.startswith("//"):
        k = j
        while k >= 1 and lines[k - 1].strip().startswith("//"):
            if SECTION_MARK_RE.match(lines[k - 1]):
                break
            out.append(lines[k - 1])
            k -= 1
        out.reverse()
    else:
        return ""
    txt = "\n".join(out)
    txt = re.sub(r"/\*+!?|\*+/", " ", txt)
    cleaned = []
    for l in txt.split("\n"):
        l = re.sub(r"^\s*(?:\*+|/{2,}!?<?)\s?", "", l).strip()
        if l and not re.fullmatch(r"[-=*_/#~]{3,}", l):
            cleaned.append(l)
    d = " ".join(cleaned)
    if re.search(r"Copyright Epic Games", d):
        return ""
    return d[:1500]


def _comment_col(code_line, raw_line):
    """Column where a comment starts on a code line (masked copy has the comment blanked), -1 if none."""
    for tok in ("//", "/*"):
        k = raw_line.find(tok)
        while k >= 0:
            if code_line[k:k + 2].strip() == "":
                return k
            k = raw_line.find(tok, k + 1)
    return -1


def trailing_comment(line, lines=None, code_lines=None, i=0):
    """Comment after code on line i (1-based); with `lines` given, also `/* ... */` spanning lines and `//`
    continuation lines aligned to the same column."""
    if lines is None:
        m = re.search(r"//+!?<?\s*(.+)$", line)
        return m.group(1).strip()[:300] if m else ""
    raw, code = lines[i - 1], code_lines[i - 1]
    col = _comment_col(code, raw)
    if col < 0 or not code[:col].strip():
        return ""
    body = raw[col:]
    parts = []
    if body.startswith("/*"):
        k = i
        txt = body
        while "*/" not in txt[2:] and k < len(lines) and k < i + 12:
            k += 1
            txt += "\n" + lines[k - 1]
        txt = txt[:txt.find("*/", 2)] if "*/" in txt[2:] else txt
        parts = [re.sub(r"^\s*(?:/\*+!?<?|\*+)\s?", "", l).strip() for l in txt.split("\n")]
    else:
        parts.append(re.sub(r"^//+!?<?\s*", "", body).strip())
        k = i
        while k < len(lines) and k < i + 12:
            nxt = lines[k]
            if nxt.find("//") == col and not nxt[:col].strip() and not SECTION_MARK_RE.match(nxt):
                parts.append(re.sub(r"^\s*//+!?<?\s*", "", nxt).strip())
                k += 1
            else:
                break
    return " ".join(p for p in parts if p)[:600]


def is_trailing_continuation(lines, code_lines, j):
    """True if comment-only line j continues the trailing comment of the code line above it (same column)."""
    t = lines[j - 1]
    col = t.find("//")
    if col < 0 or t[:col].strip():
        return False
    k = j - 1
    while k >= 1 and lines[k - 1].find("//") == col and not lines[k - 1][:col].strip():
        k -= 1
    if k < 1:
        return False
    c = _comment_col(code_lines[k - 1], lines[k - 1])
    return c == col and bool(code_lines[k - 1][:c].strip())


def attach_meta(sf, start):
    """Return (reflection macros, doc) found immediately above declaration start."""
    macros, j = [], start - 1
    for _ in range(8):
        if j < 1:
            break
        if j in sf.macros_by_end:
            name, args, sline = sf.macros_by_end[j]
            macros.append((name, args))
            j = sline - 1
            continue
        t = sf.lines[j - 1].strip()
        if t == "" or ATTR_LINE_RE.match(t):
            if t == "":
                break
            j -= 1
            continue
        break
    doc = doc_above(sf.lines, j)
    return list(reversed(macros)), doc


# --------------------------------------------------------------------------- per-module work
TYPE_KINDS = {"class", "struct", "union", "enum", "typedef"}
SYM_KINDS = TYPE_KINDS | {"member", "prototype", "function", "enumerator", "variable", "externvar", "macro",
                          "namespace"}


def vis_of(path, modroot):
    rel = os.path.relpath(path, modroot).split(os.sep)
    for p in rel[:-1]:
        if p in ("Public", "Classes"):
            return "Public"
        if p == "Internal":
            return "Internal"
        if p == "Private":
            return "Private"
    return "Other"


def build_records(sf, tags, path):
    recs = []
    seen = set()
    for t in tags:
        kind = t.get("kind")
        if kind not in SYM_KINDS:
            continue
        name = t.get("name", "")
        if not name or name.startswith("__anon"):
            name = "(anonymous)" if kind != "enumerator" else name
        line = int(t.get("line", 0) or 0)
        if line < 1 or line > len(sf.lines):
            continue
        scope = t.get("scope", "") or ""
        r = {"kind": kind, "name": name, "scope": scope, "line": line, "access": t.get("access", ""),
             "inherits": t.get("inherits", ""), "end": t.get("end", 0)}
        if kind == "enumerator":
            r["decl"] = re.sub(r"\s+", " ", enumerator_text(sf.lines, line)).strip()
            m = re.search(r"\bUMETA\s*\((.*)\)", r["decl"])
            r["macros"] = []
            r["doc"] = doc_above(sf.lines, line - 1) or trailing_comment(sf.lines[line - 1])
        elif kind == "macro":
            r["decl"] = re.sub(r"\s+", " ", sf.lines[line - 1].strip())[:240]
            r["macros"] = []
            r["doc"] = doc_above(sf.lines, line - 1)
        elif kind == "namespace":
            r["decl"] = f"namespace {name}"
            r["macros"] = []
            r["doc"] = ""
        else:
            st = decl_start(sf.lines, line)
            d = clean_decl(forward_decl(sf.lines, st, kind))
            if len(d) > 1500:
                d = d[:1500] + " ..."
            r["decl"] = d
            r["macros"], r["doc"] = attach_meta(sf, st)
            if not r["doc"]:
                last = min(len(sf.lines), line + d.count(";"))
                r["doc"] = trailing_comment(sf.lines[line - 1])
        sig = (kind, scope, name, re.sub(r"\s+", "", r["decl"])[:200])
        if sig in seen and kind not in ("class", "struct", "enum", "namespace"):
            continue
        seen.add(sig)
        recs.append(r)
    for ln in sf.delegates:
        txt = clean_decl(forward_decl(sf.lines, ln, "typedef"))
        mm = re.match(r"(\w+)\s*\(\s*([^,)]*)", txt)
        mname = mm.group(1) if mm else "DECLARE"
        # delegate type name is first arg for non-signature macros, second for DECLARE_*DELEGATE_RetVal, handled uniformly
        nm = re.search(r"\(\s*(?:[\w:<>\*&\s]+,\s*)?(F\w+|[A-Z]\w+)", txt)
        recs.append({"kind": "delegate", "name": nm.group(1) if nm else mname, "scope": "", "line": ln,
                     "access": "", "inherits": "", "end": ln, "decl": txt[:1500], "macros": [],
                     "doc": doc_above(sf.lines, decl_start(sf.lines, ln) - 1)})
    recs.sort(key=lambda x: (x["line"], x["kind"]))
    return recs


def md_esc(s):
    return s.replace("`", "'")


def render_file(rel, vis, recs, out):
    out.append(f"\n### `{rel}` ({vis})\n")
    types = {}
    children = defaultdict(list)
    top_free = []
    for r in recs:
        q = (r["scope"] + "::" if r["scope"] else "") + r["name"]
        if r["kind"] in ("class", "struct", "union", "enum"):
            r["q"] = q
            types[q] = r
        if r["kind"] == "enumerator":
            children[r["scope"]].append(r)
        elif r["scope"] and r["kind"] not in ("class", "struct", "union", "enum", "namespace"):
            children[r["scope"]].append(r)
        elif r["kind"] in ("typedef",) and r["scope"] in types:
            children[r["scope"]].append(r)
    emitted = set()
    for r in recs:
        k = r["kind"]
        q = (r["scope"] + "::" if r["scope"] else "") + r["name"]
        if k in ("class", "struct", "union", "enum"):
            out.append(f"\n#### {k} `{md_esc(q)}`  \n`{md_esc(r['decl'])}`  \n_L{r['line']}-{r['end']}_")
            for mn, ma in r["macros"]:
                out.append(f"- reflection: `{mn}({md_esc(ma)})`")
            if r["inherits"]:
                out.append(f"- inherits: `{md_esc(r['inherits'])}`")
            if r["doc"]:
                out.append(f"- desc: {r['doc']}")
            for c in children.get(q, []):
                emitted.add(id(c))
                acc = f"{c['access']} " if c["access"] else ""
                line = f"- L{c['line']} _{acc}{c['kind']}_ `{md_esc(c['decl'])}`"
                for mn, ma in c["macros"]:
                    line += f" — `{mn}({md_esc(ma)})`"
                if c["doc"]:
                    line += f" — {c['doc']}"
                out.append(line)
            emitted.add(id(r))
    free = [r for r in recs if id(r) not in emitted]
    if free:
        out.append("\n#### Free symbols / members of external scopes\n")
        for c in free:
            sc = f"{c['scope']}::" if c["scope"] else ""
            line = f"- L{c['line']} _{c['kind']}_ `{md_esc(c['decl'] if c['kind'] != 'macro' else c['decl'])}`"
            if sc and c["kind"] not in ("macro", "delegate"):
                line += f" (scope `{md_esc(c['scope'])}`)"
            for mn, ma in c["macros"]:
                line += f" — `{mn}({md_esc(ma)})`"
            if c["doc"]:
                line += f" — {c['doc']}"
            out.append(line)


def process_module(args):
    (kind, key), files, engine, opts, outdir, meta = args
    engine = Path(engine)
    if kind == "module":
        tier, name, bcs = meta
        modroot = key
        safe = name
    else:
        tier, name, bcs, modroot = "NoModule", key.replace("/", "__"), None, str(engine)
        safe = name
    tags = run_ctags(sorted(files), opts)
    by_file = defaultdict(list)
    for t in tags:
        by_file[t["path"]].append(t)
    parts, cur, size = [], [], 0
    total_syms, stat = 0, defaultdict(int)
    tsv = []
    reflect_hdr = defaultdict(int)
    for f in sorted(files):
        try:
            sf = SrcFile(f)
        except OSError:
            continue
        recs = build_records(sf, by_file.get(f, []), f)
        for ln, (mn, ma, sl) in sf.macros_by_end.items():
            reflect_hdr[mn] += 1
        rel = os.path.relpath(f, engine)
        vis = vis_of(f, modroot) if modroot and modroot != str(engine) else "Other"
        buf = []
        if recs:
            render_file(rel, vis, recs, buf)
        for r in recs:
            stat[r["kind"]] += 1
            tsv.append("\t".join([rel, str(r["line"]), r["kind"], r["scope"], r["name"], vis]))
        total_syms += len(recs)
        text = "\n".join(buf) + "\n" if buf else f"\n### `{rel}` ({vis})\n_(no declarations extracted)_\n"
        if size + len(text) > PART_LIMIT and cur:
            parts.append("".join(cur))
            cur, size = [], 0
        cur.append(text)
        size += len(text)
    if cur:
        parts.append("".join(cur))
    odir = Path(outdir) / "api" / tier
    odir.mkdir(parents=True, exist_ok=True)
    deps = parse_build_cs(bcs) if bcs else {}
    names = []
    for pi, body in enumerate(parts, 1):
        fn = f"{safe}.md" if len(parts) == 1 else f"{safe}.part{pi:02d}.md"
        head = [f"# {tier} / {name}" + (f" (part {pi}/{len(parts)})" if len(parts) > 1 else ""), ""]
        if pi == 1:
            head.append(f"- module root: `{os.path.relpath(modroot, engine) if modroot else '-'}`")
            head.append(f"- headers: {len(files)}; symbols: {total_syms}")
            head.append("- symbol kinds: " + ", ".join(f"{k}={v}" for k, v in sorted(stat.items())))
            for dk, dv in sorted(deps.items()):
                head.append(f"- {dk}: {', '.join(dv)}")
            head.append("")
        (odir / fn).write_text("\n".join(head) + body, encoding="utf-8")
        names.append(fn)
    with gzip.open(Path(outdir) / "index" / f"{tier}__{safe}.tsv.gz", "wt", encoding="utf-8") as g:
        g.write("\n".join(tsv) + ("\n" if tsv else ""))
    return {"tier": tier, "name": name, "root": os.path.relpath(modroot, engine) if modroot else "",
            "headers": len(files), "symbols": total_syms, "stat": dict(stat), "deps": deps,
            "files": names, "reflect_macros_in_src": dict(reflect_hdr)}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--engine", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--only", default="", help="comma-separated module names (debug)")
    ap.add_argument("--jobs", type=int, default=14)
    a = ap.parse_args()
    engine = Path(a.engine).resolve()
    out = Path(a.out)
    (out / "index").mkdir(parents=True, exist_ok=True)
    mods = find_modules(engine)
    by_module, ex_tests = collect_headers(engine, mods)

    api_macros = set()
    r = subprocess.run(["grep", "-rhoE", r"\b[A-Z][A-Z0-9_]*_API\b", "--include=*.h", "--include=*.inl", "--include=*.cs",
                        str(engine / "Source"), str(engine / "Plugins"), str(engine / "Platforms")],
                       capture_output=True, text=True)
    api_macros.update(r.stdout.split())
    opts = ctags_options(api_macros)

    jobs = []
    for (k, key), files in by_module.items():
        meta = mods.get(key) if k == "module" else (key.split("/")[1], key, None)
        if a.only and not (k == "module" and meta[1] in a.only.split(",")):
            continue
        jobs.append(((k, key), files, str(engine), opts, str(out), meta))
    jobs.sort(key=lambda j: -len(j[1]))
    results = []
    with Pool(a.jobs) as pool:
        for i, res in enumerate(pool.imap_unordered(process_module, jobs, chunksize=1), 1):
            results.append(res)
            if i % 100 == 0:
                print(f"[{i}/{len(jobs)}]", file=sys.stderr)
    results.sort(key=lambda x: (x["tier"], x["name"]))
    summary = {"modules": results, "excluded_test_headers": ex_tests,
               "total_headers": sum(x["headers"] for x in results),
               "total_symbols": sum(x["symbols"] for x in results)}
    (out / "modules.json").write_text(json.dumps(summary, indent=1), encoding="utf-8")
    print(json.dumps({k: v for k, v in summary.items() if k != "modules"}))


if __name__ == "__main__":
    main()
