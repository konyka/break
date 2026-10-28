#!/usr/bin/env python3
"""Console variable / console command data dictionary for the Unreal Engine source tree.

Sources scanned (Engine/{Source,Plugins,Platforms}, *.cpp/*.h/*.inl/*.hpp, ThirdParty excluded):
  * auto-registering objects: TAutoConsoleVariable<T>, FAutoConsoleVariableRef, FAutoConsoleVariable,
    FAutoConsoleCommand*, FAutoConsoleVariableSink, FAutoConsoleTaskPriority, FAutoConsoleVariableDeprecated,
    FAutoConsoleCommandDeprecated[_NoReplace], TAutoConsoleVariableDeprecated_NoReplace<T>, FAutoConsoleVariableShadow
    (as globals/statics, members with ctor-initialiser lists, `new` / MakeUnique / MakeShared / temporaries);
  * IConsoleManager calls: RegisterConsoleVariable[Ref|BitRef], RegisterDelegatedConsoleVariable,
    RegisterConsoleCommand, RegisterConsoleVariableSink_Handle;
  * function-like #define wrappers whose body contains one of the above (FASTVRAM_CVAR, ...) are expanded at
    every invocation site (# stringize, ## paste, adjacent literal concatenation);
  * UPROPERTY(meta=(ConsoleVariable="...")) settings bindings;
  * ini overrides: [ConsoleVariables], [SystemSettings*], [*Quality@N] scalability groups, DeviceProfile +CVars=.
Every argument list is located by paren/brace matching on a comment/string-masked copy of the file; when the name,
default or help cannot be resolved to literals the raw call text is kept (status column says why).

Outputs: dictionary/cvars.md, dictionary/cvars.tsv, dictionary/cvars_ini.tsv, dictionary/cvars_report.json
"""
import argparse
import json
import os
import re
import subprocess
import sys
from collections import defaultdict, Counter
from multiprocessing import Pool
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from extract_shaders import mask, line_starts, lineno, match_close, PP  # noqa: E402

ENGINE = "/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release/Engine"
OUT = "/home/timeshift/opensource/break/docs/ue5.8.3/appendix"
SRC_EXT = (".cpp", ".h", ".inl", ".hpp", ".c", ".cc", ".mm", ".m")
SKIP_DIRS = {"ThirdParty", "Intermediate", "Binaries", ".git", "Saved"}
PART_LIMIT = 3 * 1024 * 1024

OBJ_TYPES = ["TAutoConsoleVariableDeprecated_NoReplace", "TAutoConsoleVariable", "FAutoConsoleVariableRef",
             "FAutoConsoleVariableSink", "FAutoConsoleVariableDeprecated", "FAutoConsoleVariableShadow",
             "FAutoConsoleVariable", "FAutoConsoleCommandDeprecated_NoReplace", "FAutoConsoleCommandDeprecated",
             "FAutoConsoleCommandWithWorldArgsAndOutputDevice", "FAutoConsoleCommandWithWorldAndArgs",
             "FAutoConsoleCommandWithArgsAndOutputDevice", "FAutoConsoleCommandWithOutputDevice",
             "FAutoConsoleCommandWithWorld", "FAutoConsoleCommand", "FAutoConsoleTaskPriority"]
CALLS = ["RegisterConsoleVariableRef", "RegisterConsoleVariableBitRef", "RegisterConsoleVariableSink_Handle",
         "RegisterConsoleVariableSink", "RegisterDelegatedConsoleVariable", "RegisterConsoleVariable",
         "RegisterConsoleCommand"]
TOKEN_RE = re.compile(r"\b(" + "|".join(OBJ_TYPES + CALLS) + r")\b")
GREP_PAT = r"\b(" + "|".join(OBJ_TYPES + CALLS) + r")\b"
KIND_OF = {
    "TAutoConsoleVariable": "variable", "FAutoConsoleVariable": "variable", "FAutoConsoleVariableRef": "variable_ref",
    "FAutoConsoleVariableSink": "sink", "FAutoConsoleTaskPriority": "task_priority",
    "FAutoConsoleVariableDeprecated": "deprecated_alias", "FAutoConsoleCommandDeprecated": "deprecated_command_alias",
    "TAutoConsoleVariableDeprecated_NoReplace": "deprecated_variable",
    "FAutoConsoleCommandDeprecated_NoReplace": "deprecated_command", "FAutoConsoleVariableShadow": "shadow_alias",
    "RegisterConsoleVariable": "variable", "RegisterConsoleVariableRef": "variable_ref",
    "RegisterConsoleVariableBitRef": "variable_bitref", "RegisterDelegatedConsoleVariable": "variable_delegated",
    "RegisterConsoleCommand": "command", "RegisterConsoleVariableSink_Handle": "sink",
    "RegisterConsoleVariableSink": "sink"}
for _t in OBJ_TYPES:
    if _t.startswith("FAutoConsoleCommand") and _t not in KIND_OF:
        KIND_OF[_t] = "command"
STR_RE = re.compile(r'(?:u8|u|U|L)?"((?:\\.|[^"\\\n])*)"')
WRAP_RE = re.compile(r"\b(?:TEXT|UTF8TEXT|UE_CVAR_HELP_TEXT_PARAM|WIDETEXT|TEXTVIEW|INVTEXT)\s*\(|[()\s]")
ESC = {"n": "\n", "t": "\t", '"': '"', "\\": "\\", "'": "'", "r": ""}


def unescape(s):
    return re.sub(r"\\(.)", lambda m: ESC.get(m.group(1), m.group(1)), s)


def literal_value(arg):
    """If arg is made only of string literals (+ TEXT() wrappers), return concatenated value else None."""
    lits = list(STR_RE.finditer(arg))
    if not lits:
        return None
    rest = STR_RE.sub("", arg)
    if WRAP_RE.sub("", rest).strip():
        return None
    return unescape("".join(m.group(1) for m in lits))


def collapse(s):
    return re.sub(r"\s+", " ", s).strip()


# --------------------------------------------------------------------------- discovery helpers
def module_index(engine):
    mods, plugs = {}, {}
    for top in ("Source", "Plugins", "Platforms"):
        for dp, dns, fns in os.walk(os.path.join(engine, top)):
            dns[:] = [d for d in dns if d not in SKIP_DIRS]
            for fn in fns:
                lf = fn.lower()
                if lf.endswith(".build.cs"):
                    mods[os.path.relpath(dp, engine)] = fn[:-len(".build.cs")]
                elif lf.endswith(".uplugin"):
                    plugs[os.path.relpath(dp, engine)] = fn[:-len(".uplugin")]
    return mods, plugs


def owner(rel, table):
    d = os.path.dirname(rel)
    while d:
        if d in table:
            return table[d]
        d = os.path.dirname(d)
    return ""


def grep_files(engine, pattern, word=False):
    cmd = ["grep", "-rlE"] + (["-w"] if word else []) + [f"--include=*{e}" for e in SRC_EXT] + \
          [f"--exclude-dir={d}" for d in SKIP_DIRS] + [pattern, "Source", "Plugins", "Platforms"]
    r = subprocess.run(cmd, cwd=engine, capture_output=True, text=True)
    return sorted(x for x in r.stdout.split("\n") if x)


# --------------------------------------------------------------------------- argument handling
def split_args(s):
    out, d, cur = [], 0, []
    for c in s:
        if c in "([{":
            d += 1
        elif c in ")]}":
            d -= 1
        if c == "," and d == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(c)
    out.append("".join(cur))
    return [collapse(x) for x in out] if any(x.strip() for x in out) else []


def split_args_masked(nc, cd, a, b):
    """Split nc[a:b] at top-level commas found on the masked copy cd (strings/comments can't confuse it)."""
    out, d, start = [], 0, a
    for i in range(a, b):
        c = cd[i]
        if c in "([{":
            d += 1
        elif c in ")]}":
            d -= 1
        elif c == "<" and False:
            pass
        elif c == "," and d == 0:
            out.append(collapse(nc[start:i]))
            start = i + 1
    out.append(collapse(nc[start:b]))
    return out if any(out) else []


PARAM_DECL_RE = re.compile(r"^(?:const\s+)?(?:class\s+|struct\s+|typename\s+)?[A-Za-z_][\w:]*(?:<.*>)?\s*[*&]*\s*"
                           r"(?:const\s*)?[*&]*\s*[A-Za-z_]\w*\s*(?:=.*)?$")
FLAGS_RE = re.compile(r"\bECVF_\w+|\bEConsoleVariableFlags\b|^\(uint32\)\s*\w+$")
TYPE_LIT = [(re.compile(r"^(true|false)$"), "bool"), (re.compile(r"^[-+]?\d+[uUlL]*$"), "int32"),
            (re.compile(r"^[-+]?(\d+\.\d*|\.\d+|\d+)(e[-+]?\d+)?[fF]?$"), "float")]


def guess_type(default, kind):
    if default is None:
        return ""
    d = default.strip()
    if literal_value(d) is not None:
        return "FString"
    for rx, t in TYPE_LIT:
        if rx.match(d):
            if t == "float" and not re.search(r"[.eEfF]", d):
                return "int32"
            return t
    return ""


def interpret(tok, targs, args, refs, strs=None):
    """Map positional args to fields. Returns dict(name, default, help, flags, type, extra, status)."""
    r = dict(name_raw="", name="", default="", help="", flags="", type="", extra="", status=[])
    a = list(args)
    dep = ""
    if a and a[0].startswith("FCVarDeprecationArgs"):
        dep = a.pop(0)
        mm = STR_RE.search(dep)
        r["extra"] = "deprecated " + (mm.group(1) if mm else dep)
    kind = KIND_OF[tok]
    flags_first = False
    if a and FLAGS_RE.search(a[0]) and len(a) > 1 and kind not in ("sink",):
        flags_first = True
        r["flags"] = a.pop(0)
    if not flags_first:
        for k in range(len(a) - 1, 0, -1):
            if FLAGS_RE.search(a[k]) and literal_value(a[k]) is None:
                r["flags"] = a.pop(k)
                break
    if kind == "sink":
        r["name"] = "(sink)"
        r["extra"] = a[0] if a else ""
        return r
    if not a:
        r["status"].append("no-args")
        return r
    r["name_raw"] = a[0]
    nv = literal_value(a[0])
    if nv is None and strs:
        bare = re.sub(r"^\*|\s+", "", a[0])
        bare = re.sub(r"\.(?:GetData|ToString|c_str)\(\)$|^ToCStr\((.*)\)$|^\*?(\w+)\.ToString\(\)$", r"\1\2", bare) or bare
        if bare in strs:
            nv = strs[bare]
            r["status"].append("name:via-constant")
    if nv is None:
        r["status"].append("name:expr")
        r["name"] = a[0]
    else:
        r["name"] = nv
    rest = a[1:]

    def lit_or_raw(x, field):
        v = literal_value(x)
        if v is None:
            if x and x not in ("nullptr", "TEXT(\"\")"):
                r["status"].append(f"{field}:expr")
            return x
        return v

    if kind in ("variable",) and tok != "RegisterConsoleVariable" and len(rest) >= 4 and "Help" not in rest[1]:
        # TAutoConsoleVariable(Flags, Name, Default, Getter, Setter, Help)
        r["default"], r["help"] = rest[0], lit_or_raw(rest[-1], "help")
        r["extra"] = (r["extra"] + " delegated getter/setter").strip()
    elif kind in ("variable", "variable_delegated", "deprecated_variable"):
        r["default"] = rest[0] if rest else ""
        if kind == "variable_delegated":
            r["help"] = lit_or_raw(rest[3], "help") if len(rest) > 3 else ""
        elif kind == "deprecated_variable":
            r["extra"] = "deprecated " + (literal_value(rest[1]) or rest[1]) if len(rest) > 1 else "deprecated"
        elif dep:
            r["help"] = ""
        else:
            r["help"] = lit_or_raw(rest[1], "help") if len(rest) > 1 else ""
            if len(rest) > 2:
                r["extra"] = (r["extra"] + " callback").strip()
        if targs:
            r["type"] = targs
        else:
            r["type"] = guess_type(r["default"], kind)
        dv = literal_value(r["default"]) if r["default"] else None
        if dv is not None:
            r["default"] = '"' + dv + '"'
    elif kind == "variable_ref":
        ref = rest[0] if rest else ""
        r["extra"] = (r["extra"] + f" ref {ref}").strip()
        r["help"] = "" if dep else (lit_or_raw(rest[1], "help") if len(rest) > 1 else "")
        bare = re.sub(r"^[*&(]+|\)$", "", ref)
        info = refs.get(bare) or refs.get(re.split(r"\.|->|::", bare)[-1])
        if info:
            r["type"], r["default"] = info
            if r["default"] == "":
                r["status"].append("default:uninitialised-ref")
        else:
            r["status"].append("default:ref-not-found")
    elif kind == "variable_bitref":
        r["help"] = lit_or_raw(rest[4], "help") if len(rest) > 4 else ""
        r["extra"] = f"bit flag {literal_value(rest[0]) or rest[0]} bit {rest[1] if len(rest) > 1 else ''}"
        r["type"] = "bit"
    elif kind == "command":
        if rest and literal_value(rest[0]) is not None or (rest and "Help" in rest[0]) or (
                rest and not re.search(r"Create(Raw|Static|Lambda|SP|UObject|Weak|Thread)|\[|Delegate|::", rest[0])):
            r["help"] = lit_or_raw(rest[0], "help") if rest else ""
            if len(rest) > 1:
                r["extra"] = rest[1][:160]
        else:
            r["extra"] = rest[0][:160] if rest else ""
        r["type"] = "command"
    elif kind in ("deprecated_alias", "deprecated_command_alias", "shadow_alias"):
        tgt = literal_value(rest[0]) if rest else None
        r["extra"] = f"-> {tgt if tgt is not None else (rest[0] if rest else '?')}"
        if len(rest) > 1 and kind != "shadow_alias":
            r["extra"] += f" (deprecated {literal_value(rest[1]) or rest[1]})"
        r["type"] = "alias"
    elif kind == "deprecated_command":
        ver = [literal_value(x) for x in rest if literal_value(x) is not None and re.match(r"\d", literal_value(x))]
        r["extra"] = f"deprecated {ver[0] if ver else '?'}"
        r["type"] = "command"
    elif kind == "task_priority":
        r["help"] = lit_or_raw(rest[0], "help") if rest else ""
        r["default"] = ", ".join(rest[1:3])
        r["type"] = "task_priority"
    return r


# --------------------------------------------------------------------------- per-file scan
REF_DECL_RE = re.compile(r"\b(bool|int32|int|uint32|int64|float|double|FString|FName|uint8|int16|uint16)\s+"
                         r"((?:[A-Za-z_]\w*::)*[A-Za-z_]\w*)\s*(?:=\s*([^;,{}]+?)|\{\s*([^{};]*?)\s*\}|\(\s*([^();]*)\s*\))?\s*;")
MACRO_DEF_RE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+(\w+)\(([^)]*)\)((?:[^\n]*\\\n)*[^\n]*)", re.M)


STRCONST_RE = re.compile(r"\b(?:const\s+)?(?:TCHAR|ANSICHAR|char|FString|FStringView|FName|FLazyName|FAnsiStringView|"
                         r"FWideStringView|TCHAR\s+const)\s*(?:\*\s*(?:const\s*)?)?\s*([A-Za-z_]\w*)\s*(?:\[\s*\])?\s*"
                         r"(?:=\s*|\(\s*|\{\s*)((?:(?:TEXT\s*\(\s*)?(?:u8|u|U|L)?\"(?:\\.|[^\"\\\n])*\"\s*\)?\s*)+)[;)}]")


def strconst_table(text):
    out = {}
    for m in STRCONST_RE.finditer(text):
        v = literal_value(m.group(2))
        if v is not None:
            out.setdefault(m.group(1), v)
    return out


def ref_table(cd, nc):
    refs = {}
    for m in REF_DECL_RE.finditer(cd):
        name = m.group(2)
        a, b = (m.start(3), m.end(3)) if m.group(3) is not None else (
            (m.start(4), m.end(4)) if m.group(4) is not None else ((m.start(5), m.end(5)) if m.group(5) else (0, 0)))
        val = collapse(nc[a:b]) if b > a else ""
        t = {"int": "int32"}.get(m.group(1), m.group(1))
        for nm in {name, name.split("::")[-1]}:
            if nm not in refs or (not refs[nm][1] and val):
                refs[nm] = (t, val)
    return refs


def find_template_args(cd, pos):
    """cd[pos] == '<' -> (args, end_index_after_>)."""
    d, i = 0, pos
    while i < len(cd) and i < pos + 300:
        if cd[i] == "<":
            d += 1
        elif cd[i] == ">":
            d -= 1
            if d == 0:
                return cd[pos + 1:i], i + 1
        i += 1
    return None, pos


def scan_text(text, rel, macro_defs, refs_extra=None, depth=0):
    """Return (records, failures) for a single translation unit text."""
    nc, cd = mask(text)
    # blank preprocessor directive lines (#define bodies are analysed separately)
    cl, nl = cd.split("\n"), nc.split("\n")
    raw = text.split("\n")
    pp = PP(nl, raw)
    define_lines = set()
    for ln in pp.directive_lines:
        s = nl[ln - 1].lstrip()
        if s.startswith("#"):
            pass
    i = 0
    while i < len(nl):
        if nl[i].lstrip().startswith("#"):
            j = i
            while nl[j].rstrip().endswith("\\") and j + 1 < len(nl):
                j += 1
            if re.match(r"\s*#\s*define\b", nl[i]):
                for k in range(i, j + 1):
                    define_lines.add(k + 1)
            for k in range(i, j + 1):
                cl[k] = " " * len(cl[k])
                nl[k] = " " * len(nl[k])
            i = j + 1
        else:
            i += 1
    cd2, nc2 = "\n".join(cl), "\n".join(nl)
    starts = line_starts(text)
    refs = ref_table(cd2, nc2)
    strs = strconst_table(text)
    if refs_extra:
        for k, v in refs_extra.items():
            refs.setdefault(k, v)
    recs, fails = [], []
    for m in TOKEN_RE.finditer(cd2):
        tok = m.group(1)
        pos = m.end()
        targs = ""
        k = pos
        while k < len(cd2) and cd2[k] in " \t\n":
            k += 1
        if k < len(cd2) and cd2[k] == "<":
            ta, k2 = find_template_args(cd2, k)
            if ta is None:
                continue
            targs = collapse(ta)
            k = k2
        ln = lineno(starts, m.start())
        prev = cd2[max(0, m.start() - 60):m.start()]
        # skip non-constructing uses
        if re.search(r"(::|\.|->)\s*$", prev) and tok in OBJ_TYPES:
            continue
        if re.search(r"\b(class|struct|friend|typedef|using|operator|extern)\s+(\w+\s+)*$", prev):
            continue
        if re.search(r"\b(class|struct|friend|extern)\b[^;{}()]*$", prev) and tok in OBJ_TYPES:
            continue
        rest = cd2[k:k + 400]
        if tok in OBJ_TYPES:
            # declaration with constructor args: Type [*&]* Name ( | {   ;   temporary Type( ; MakeUnique<Type>(
            mm = re.match(r"\s*>?\s*\)?\s*(\(|\{)", rest)
            md = re.match(r"\s*(?:(?:const|volatile)\s+)?([A-Za-z_]\w*)\s*(\(|\{|\[|;|=|,|\))", rest)
            if mm:
                o = k + rest.index(mm.group(1))
                var = ""
            elif md and md.group(2) in "({":
                var = md.group(1)
                o = k + md.end() - 1
            elif md and md.group(2) == "[":
                continue  # array of auto objects: initialised elsewhere
            elif md:
                if md.group(2) == "=":
                    q = k + md.end()
                    r2 = re.match(r"\s*(?:\w+\s*)?[({]", cd2[q:q + 200])
                    if r2:
                        o = q + r2.end() - 1
                        var = md.group(1)
                    else:
                        continue
                else:
                    continue   # plain member declaration, initialised by ctor-initialiser or Emplace (handled below)
            else:
                continue
            # function declaration whose return type is the auto object? (Type Foo(int x);) -> params look like decls
        else:
            if re.search(r"\b(virtual|override)\b[^;{}]*$", prev) or re.search(r"\bIConsoleObject\s*\*\s*$", prev) and False:
                continue
            mm = re.match(r"\s*\(", rest)
            if not mm:
                continue
            o = k + mm.end() - 1
            var = ""
        open_c = cd2[o]
        close_c = ")" if open_c == "(" else "}"
        e = match_close(cd2, o, open_c, close_c, min(len(cd2), o + 200000))
        if e < 0:
            fails.append(dict(file=rel, line=ln, token=tok, raw=collapse(nc2[m.start():m.start() + 300]),
                              why="unbalanced argument list"))
            continue
        args = split_args_masked(nc2, cd2, o + 1, e)
        if not args and tok in OBJ_TYPES and not var:
            continue  # default constructor declaration / zero-arg temporary: registers nothing
        if args and all(PARAM_DECL_RE.match(x) and literal_value(x) is None and not FLAGS_RE.search(x)
                        and not re.match(r"[-+]?\d", x) and " " in x for x in args):
            continue  # a prototype/definition taking parameters, not a construction
        rawcall = collapse(nc2[m.start():e + 1])
        r = interpret(tok, targs, args, refs, strs)
        r.update(file=rel, line=ln, token=tok + (f"<{targs}>" if targs else ""), kind=KIND_OF[tok],
                 var=var, raw=rawcall[:1500], cond=pp.cond[ln] if ln < len(pp.cond) else "")
        if r["name"] == "" and KIND_OF[tok] != "sink":
            fails.append(dict(file=rel, line=ln, token=tok, raw=rawcall[:600], why="no name argument"))
        recs.append(r)
    # member objects initialised via ctor-initialiser list:  , Member(TEXT("x"), ...)  and Arr.Emplace(TEXT("x"),..)
    members = {}
    for m in re.finditer(r"\b(" + "|".join(OBJ_TYPES) + r")\s*(<[^<>;]*>)?\s+([A-Za-z_]\w*)\s*;", cd2):
        members[m.group(3)] = (m.group(1), collapse(m.group(2) or "").strip("<>"))
    for m in re.finditer(r"\b(" + "|".join(OBJ_TYPES) + r")\s*>\s+([A-Za-z_]\w*)\s*;", cd2):
        members[m.group(2)] = (m.group(1), "")
    for m in re.finditer(r"(?:TArray|TIndirectArray)\s*<\s*(" + "|".join(OBJ_TYPES) + r")\s*(<[^<>;]*>)?\s*>\s+"
                         r"(?:[\w:]+::)?([A-Za-z_]\w*)\s*;", cd2):
        members[m.group(3) + ".Emplace"] = (m.group(1), collapse(m.group(2) or "").strip("<>"))
        members[m.group(3) + ".Add"] = (m.group(1), collapse(m.group(2) or "").strip("<>"))
    if members:
        names = "|".join(re.escape(x).replace(r"\.", r"\s*\.\s*") for x in sorted(members, key=len, reverse=True))
        for m in re.finditer(r"(?:^|[,:;{]\s*|\n\s*)(" + names + r")\s*([({])", cd2):
            key = re.sub(r"\s+", "", m.group(1))
            if key not in members:
                continue
            tok, targs = members[key]
            o = m.end() - 1
            e = match_close(cd2, o, cd2[o], ")" if cd2[o] == "(" else "}", min(len(cd2), o + 200000))
            if e < 0:
                continue
            args = split_args_masked(nc2, cd2, o + 1, e)
            if not args or TOKEN_RE.search(cd2[o:e]):
                continue
            a0 = args[0]
            if not (literal_value(a0) is not None or a0.startswith("FCVarDeprecationArgs") or FLAGS_RE.search(a0)
                    or "TEXT" in a0 or '"' in a0):
                continue
            ln = lineno(starts, m.start(1))
            r = interpret(tok, targs, args, refs, strs)
            r.update(file=rel, line=ln, token=tok + (f"<{targs}>" if targs else ""), kind=KIND_OF[tok],
                     var=key, raw=collapse(nc2[m.start(1):e + 1])[:1500], cond=pp.cond[ln] if ln < len(pp.cond) else "")
            recs.append(r)
    # invocations of function-like macros whose body creates console objects
    if macro_defs:
        names = "|".join(re.escape(x) for x in macro_defs)
        for m in re.finditer(r"\b(" + names + r")\s*\(", cd2):
            ln = lineno(starts, m.start())
            if ln in define_lines:
                continue
            o = m.end() - 1
            e = match_close(cd2, o, "(", ")", min(len(cd2), o + 200000))
            if e < 0:
                fails.append(dict(file=rel, line=ln, token=m.group(1), raw=collapse(nc2[m.start():m.start() + 300]),
                                  why="unbalanced macro invocation"))
                continue
            args = split_args_masked(nc2, cd2, o + 1, e)
            mdef = macro_defs[m.group(1)]
            body = expand_macro(mdef, args)
            if body is None:
                fails.append(dict(file=rel, line=ln, token=m.group(1), raw=collapse(nc2[m.start():e + 1])[:600],
                                  why="macro arity mismatch"))
                continue
            inner = {k: v for k, v in macro_defs.items() if k != m.group(1)} if depth < 3 else {}
            sub, _ = scan_text(body, rel, inner, refs, depth + 1)
            for r in sub:
                r.update(line=ln, raw=collapse(nc2[m.start():e + 1])[:800] + "  ⇒  " + r["raw"][:700],
                         token=r["token"] + f" via {m.group(1)}", cond=pp.cond[ln] if ln < len(pp.cond) else "")
                r["status"] = r["status"] + ["macro-expanded"]
                recs.append(r)
    return recs, fails


# --------------------------------------------------------------------------- function-like macro wrappers
def collect_macro_defs(args):
    engine, rel = args
    out = {}
    try:
        text = open(os.path.join(engine, rel), encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
    except OSError:
        return rel, out
    if "define" not in text:
        return rel, out
    nc, _ = mask(text)
    for m in MACRO_DEF_RE.finditer(nc):
        body = m.group(3).replace("\\\n", " ")
        if TOKEN_RE.search(body):
            params = [p.strip() for p in m.group(2).split(",") if p.strip()]
            raw_body = text[m.start(3):m.end(3)].replace("\\\n", " ")
            out[m.group(1)] = dict(params=params, body=raw_body, file=rel,
                                   line=text.count("\n", 0, m.start()) + 1)
    return rel, out


def expand_macro(mdef, args):
    params = mdef["params"]
    va = params and params[-1] == "..."
    fixed = params[:-1] if va else params
    if len(args) < len(fixed) or (not va and len(args) > len(fixed) and not (len(fixed) == 0 and args == [""])):
        if not (len(fixed) == 1 and not args):
            return None
    amap = {p: (args[i] if i < len(args) else "") for i, p in enumerate(fixed)}
    if va:
        amap["__VA_ARGS__"] = ", ".join(args[len(fixed):])
    body = mdef["body"]

    def stringize(m):
        v = amap.get(m.group(1))
        if v is None:
            return m.group(0)
        return '"' + v.replace("\\", "\\\\").replace('"', '\\"') + '"'

    body = re.sub(r"(?<!#)#\s*([A-Za-z_]\w*)", stringize, body)
    if amap:
        body = re.sub(r"\b(" + "|".join(re.escape(k) for k in amap) + r")\b", lambda m: amap[m.group(1)], body)
    body = re.sub(r"\s*##\s*", "", body)
    return body


# --------------------------------------------------------------------------- per-file job
def scan_file(args):
    engine, rel, macro_defs = args
    try:
        text = open(os.path.join(engine, rel), encoding="utf-8", errors="replace").read()
        text = text.lstrip("\ufeff").replace("\r\n", "\n").replace("\r", "\n")
    except OSError as e:
        return rel, [], [dict(file=rel, line=0, token="", raw="", why=f"read error {e}")]
    local = dict(macro_defs)
    try:
        recs, fails = scan_text(text, rel, local)
    except Exception as ex:  # keep going; record failure
        return rel, [], [dict(file=rel, line=0, token="", raw="", why=f"{type(ex).__name__}: {ex}")]
    return rel, recs, fails


UPROP_CV_RE = re.compile(r"\bUPROPERTY\s*\(")


def scan_uproperty(args):
    engine, rel = args
    out = []
    try:
        text = open(os.path.join(engine, rel), encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
    except OSError:
        return out
    if "ConsoleVariable" not in text:
        return out
    nc, cd = mask(text)
    for m in UPROP_CV_RE.finditer(cd):
        o = m.end() - 1
        e = match_close(cd, o, "(", ")", min(len(cd), o + 6000))
        if e < 0:
            continue
        inner = nc[o:e]
        mm = re.search(r'\bConsoleVariable\s*=\s*"([^"]+)"', inner)
        if not mm:
            continue
        semi = cd.find(";", e)
        decl = collapse(nc[e + 1:semi]) if semi > 0 else ""
        cls = ""
        for cm in re.finditer(r"\b(?:class|struct)\s+(?:\w+_API\s+)?([A-Z]\w+)\s*(?:final\s*)?:", cd[:m.start()]):
            cls = cm.group(1)
        out.append(dict(name=mm.group(1), file=rel, line=text.count("\n", 0, m.start()) + 1, decl=decl[:200], cls=cls))
    return out


# --------------------------------------------------------------------------- ini overrides
CVAR_SECTION_RE = re.compile(r"^(ConsoleVariables|Startup|SystemSettings\w*|ScalabilitySettings|\w+Quality@\w+)$")


def find_inis(engine):
    out = []
    for top in ("Config", "Plugins", "Platforms", "Programs", "Source"):
        for dp, dns, fns in os.walk(os.path.join(engine, top)):
            dns[:] = sorted(d for d in dns if d not in SKIP_DIRS)
            for fn in fns:
                if fn.lower().endswith(".ini"):
                    out.append(os.path.relpath(os.path.join(dp, fn), engine))
    return sorted(out)


def parse_ini_cvars(engine, rel):
    out = []
    try:
        lines = open(os.path.join(engine, rel), encoding="utf-8", errors="replace").read().splitlines()
    except OSError:
        return out
    sect = ""
    for i, l in enumerate(lines, 1):
        s = l.strip()
        if not s or s.startswith(";") or s.startswith("#"):
            continue
        if s.startswith("[") and s.endswith("]"):
            sect = s[1:-1]
            continue
        m = re.match(r"([+\-.!]?)([^=]+?)\s*=\s*(.*)$", s)
        if not m:
            continue
        op, key, val = m.groups()
        if sect.endswith(" DeviceProfile") or sect == "DeviceProfiles":
            if key == "CVars":
                mm = re.match(r"([^=]+?)\s*=\s*(.*)$", val)
                if mm:
                    out.append(dict(name=mm.group(1).strip(), value=mm.group(2).strip(), file=rel, line=i,
                                    section=sect, src="DeviceProfile +CVars", op=op))
            continue
        if CVAR_SECTION_RE.match(sect):
            if key.startswith("@") or " " in key.strip():
                continue
            if sect == "ScalabilitySettings" and "." not in key:
                continue
            out.append(dict(name=key.strip(), value=val.strip(), file=rel, line=i, section=sect,
                            src="scalability" if "@" in sect else sect, op=op))
    return out


# --------------------------------------------------------------------------- rendering helpers
def esc(s):
    return (s or "").replace("|", "\\|").replace("`", "'").replace("\n", " ⏎ ").replace("\t", " ")


def tsv_clean(s):
    return (s or "").replace("\t", " ").replace("\r", " ").replace("\n", " \\n ")


def prefix_of(name):
    if not re.match(r"[A-Za-z_][\w.\-]*$", name or ""):
        return "(non-literal names)"
    p = name.split(".")
    return p[0].lower() if len(p) > 1 else "(no prefix)"


FLAG_SHORT = re.compile(r"\bECVF_")


# --------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--engine", default=ENGINE)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--jobs", type=int, default=14)
    ap.add_argument("--only", default="", help="substring filter on path (debug)")
    a = ap.parse_args()
    engine, out = a.engine, Path(a.out)
    ddir = out / "dictionary"
    ddir.mkdir(parents=True, exist_ok=True)
    jobs = min(a.jobs, 14)
    cand = grep_files(engine, GREP_PAT)
    uprop_files = grep_files(engine, r"ConsoleVariable\s*=")
    if a.only:
        cand = [f for f in cand if a.only in f]
        uprop_files = [f for f in uprop_files if a.only in f]
    mods, plugs = module_index(engine)
    with Pool(jobs) as pool:
        mdefs_by_file = dict(pool.imap_unordered(collect_macro_defs, [(engine, f) for f in cand], chunksize=32))
        gdefs = defaultdict(list)
        for f, d in mdefs_by_file.items():
            for k, v in d.items():
                gdefs[k].append(v)
        # files invoking wrapper macros but not themselves containing a token
        extra = []
        if gdefs:
            pat = r"\b(" + "|".join(sorted(gdefs)) + r")\s*\("
            extra = [f for f in grep_files(engine, pat) if f not in set(cand)]
            if a.only:
                extra = [f for f in extra if a.only in f]
        files = sorted(set(cand) | set(extra))

        def defs_for(f):
            d = {}
            for k, lst in gdefs.items():
                loc = [x for x in lst if x["file"] == f]
                d[k] = loc[0] if loc else lst[0]
            return d

        res = list(pool.imap_unordered(scan_file, [(engine, f, defs_for(f)) for f in files], chunksize=8))
        uprops = [x for lst in pool.imap_unordered(scan_uproperty, [(engine, f) for f in uprop_files], chunksize=16)
                  for x in lst]
    recs, fails = [], []
    for rel, r, fl in res:
        recs += r
        fails += fl
    # de-duplicate (same file/line/name/kind found by two passes)
    seen, uniq = set(), []
    for r in sorted(recs, key=lambda x: (x["file"], x["line"], x["name"])):
        key = (r["file"], r["line"], r["name"], r["kind"])
        if key in seen:
            continue
        seen.add(key)
        r["module"] = owner(r["file"], mods)
        r["plugin"] = owner(r["file"], plugs)
        r["status"] = ",".join(dict.fromkeys(r["status"])) or "ok"
        uniq.append(r)
    recs = uniq
    inis = find_inis(engine)
    ini_rows = [x for f in inis for x in parse_ini_cvars(engine, f)]
    src_names = {r["name"].lower() for r in recs}
    for x in ini_rows:
        x["known"] = "yes" if x["name"].lower() in src_names else "no"
    for u in uprops:
        u["known"] = "yes" if u["name"].lower() in src_names else "no"

    cols = ["name", "kind", "type", "default", "flags", "help", "file", "line", "module", "plugin", "var", "token",
            "cond", "status", "raw"]
    with open(ddir / "cvars.tsv", "w", encoding="utf-8") as f:
        f.write("\t".join(cols) + "\n")
        for r in sorted(recs, key=lambda x: (x["name"].lower(), x["file"], x["line"])):
            f.write("\t".join(tsv_clean(str(r.get(c, ""))) for c in cols) + "\n")
    icols = ["name", "value", "section", "src", "op", "file", "line", "known"]
    with open(ddir / "cvars_ini.tsv", "w", encoding="utf-8") as f:
        f.write("\t".join(icols) + "\n")
        for r in ini_rows:
            f.write("\t".join(tsv_clean(str(r.get(c, ""))) for c in icols) + "\n")
    write_md(ddir, recs, ini_rows, uprops, fails, gdefs, len(files))
    kinds = Counter(r["kind"] for r in recs)
    st = Counter()
    for r in recs:
        for s in r["status"].split(","):
            st[s] += 1
    rep = dict(files_scanned=len(files), records=len(recs), unique_names=len({r["name"] for r in recs}),
               kinds=dict(kinds), status=dict(st), failures=len(fails), failure_list=fails[:500],
               wrapper_macros={k: [f"{x['file']}:{x['line']}" for x in v] for k, v in sorted(gdefs.items())},
               ini_rows=len(ini_rows), ini_files=len(inis), ini_unknown=sum(x["known"] == "no" for x in ini_rows),
               uproperty_bindings=len(uprops), files=files)
    (ddir / "cvars_report.json").write_text(json.dumps(rep, indent=1), encoding="utf-8")
    print(json.dumps({k: v for k, v in rep.items() if k not in ("failure_list", "wrapper_macros", "files")}))


def write_md(ddir, recs, ini_rows, uprops, fails, gdefs, nfiles):
    kinds = Counter(r["kind"] for r in recs)
    bad = [r for r in recs if r["status"] != "ok" and r["status"] != "macro-expanded"]
    names = {r["name"] for r in recs}
    L = ["# Console variables & commands (CVar dictionary)", "",
         "Generated by `tools/extract_cvars.py` from Engine/{Source,Plugins,Platforms} C++ sources "
         "(ThirdParty excluded) and Engine ini files. Machine-readable: `cvars.tsv` (one row per registration "
         "site, `raw` column holds the full original call text), `cvars_ini.tsv` (ini overrides).", "",
         f"- source files with registrations: {nfiles}",
         f"- registration sites: {len(recs)}; distinct names: {len(names)}",
         "- by kind: " + ", ".join(f"{k}={v}" for k, v in sorted(kinds.items())),
         f"- sites whose name/default/help is not a plain literal (raw text kept): {len(bad)}",
         f"- unparseable sites: {len(fails)} (listed at the end)",
         f"- ini override rows: {len(ini_rows)} (names not registered in C++ source: "
         f"{sum(x['known'] == 'no' for x in ini_rows)})",
         f"- UPROPERTY(meta=(ConsoleVariable=...)) bindings: {len(uprops)}",
         f"- function-like wrapper macros expanded: {', '.join(sorted(gdefs)) or '-'}", "",
         "Column notes: *kind* = variable / variable_ref (bound to a C++ global, default = that global's "
         "initialiser) / command / sink / alias / deprecated_* / task_priority; *flags* = ECVF_* expression as "
         "written; *cond* = enclosing #if; *status* `ok` or which field is a non-literal expression.", ""]
    by_pref = defaultdict(list)
    for r in recs:
        by_pref[prefix_of(r["name"])].append(r)
    L.append("## Index by prefix\n")
    L.append(" · ".join(f"[{p}](#{re.sub(r'[^a-z0-9-]', '', ('prefix-' + p).lower().replace(' ', '-'))}) "
                        f"({len(v)})" for p, v in sorted(by_pref.items())))
    L.append("")
    for p, lst in sorted(by_pref.items()):
        L.append(f"\n## prefix {p}\n")
        L.append("| name | kind / type | default | flags | help | location |")
        L.append("|---|---|---|---|---|---|")
        for r in sorted(lst, key=lambda x: (x["name"].lower(), x["file"], x["line"])):
            loc = f"`{r['file']}:{r['line']}`" + (f" ({r['module']})" if r["module"] else "")
            flags = FLAG_SHORT.sub("", r["flags"])
            kt = r["kind"] + (f" `{esc(r['type'])}`" if r["type"] else "")
            helpt = r["help"] if len(r["help"]) <= 600 else r["help"][:600] + " ..."
            extra = []
            if r["extra"]:
                extra.append(r["extra"])
            if r["cond"]:
                extra.append("#if " + r["cond"])
            if r["status"] not in ("ok",):
                extra.append("status: " + r["status"])
            if r["status"] not in ("ok", "macro-expanded"):
                extra.append("raw: `" + esc(r["raw"][:400]) + "`")
            helpcell = esc(helpt) + ((" <br>_" + esc("; ".join(extra[:-1] if extra and extra[-1].startswith("raw")
                                                               else extra)) + "_") if extra else "")
            if extra and extra[-1].startswith("raw"):
                helpcell += " <br>" + extra[-1]
            L.append(f"| `{esc(r['name'])}` | {kt} | `{esc(r['default'][:120])}` | {esc(flags[:80])} | "
                     f"{helpcell} | {loc} |")
    L.append("\n## ini overrides\n")
    L.append("Rows from [ConsoleVariables], [Startup], [SystemSettings*], scalability groups ([XQuality@N]) and "
             "DeviceProfile `+CVars=` lines. *known* = name is registered somewhere in the scanned C++ sources.\n")
    L.append("| name | value | section | file:line | known |")
    L.append("|---|---|---|---|---|")
    for x in sorted(ini_rows, key=lambda x: (x["file"], x["line"])):
        L.append(f"| `{esc(x['name'])}` | `{esc(x['value'][:100])}` | {esc(x['section'])} | "
                 f"`{x['file']}:{x['line']}` | {x['known']} |")
    L.append("\n## UPROPERTY settings bound to console variables\n")
    L.append("| cvar | class | property | file:line | known |")
    L.append("|---|---|---|---|---|")
    for u in sorted(uprops, key=lambda x: x["name"].lower()):
        L.append(f"| `{esc(u['name'])}` | {esc(u['cls'])} | `{esc(u['decl'])}` | `{u['file']}:{u['line']}` | "
                 f"{u['known']} |")
    L.append("\n## Unparseable registration sites (raw text)\n")
    if not fails:
        L.append("_none_")
    for x in fails:
        L.append(f"- `{x['file']}:{x['line']}` {esc(x['token'])}: {esc(x['why'])} — `{esc(x['raw'][:400])}`")
    (ddir / "cvars.md").write_text("\n".join(L) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
