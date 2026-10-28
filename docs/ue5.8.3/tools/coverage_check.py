#!/usr/bin/env python3
"""Independent coverage check of the generated appendix (writes appendix/COVERAGE.md + coverage.json).

Deliberately shares NO code with extract_*.py / gen_catalog.py: file inventories come from `find`, raw counts from
`grep`, and the declaration samples from this file's own (simpler) comment-masking + regexes.  Each check compares
that independent ground truth with what the generated artefacts (Markdown + TSV indexes + dictionaries) contain.

Checks
  1  C++ headers (file level)          find .h/.hpp/.inl  vs  "### `path`" sections in api/<tier>/*.md + index
  2  C++ reflection macros             grep-found U* macros (comment-free) vs (a) a symbol at the declaration line
                                       that follows the macro, (b) the macro text attached in the Markdown section
  3  C++ types, random sample 2000     own regex for class/struct/enum/union definitions vs index rows
  4  C++ functions, random sample 3000 own regex for declarations at namespace/class scope vs index rows
  5  C# files + type sample 1000       find *.cs vs api/CSharp sections, own regex type sample vs CSharp index
  6  Shaders                           find .usf/.ush vs api/Shaders; [numthreads]/struct/top-level function lines
  7  CVars                             grep files with registrations; own regex literal names vs cvars.tsv; ini
  8  Catalog                           find .uplugin/.Build.cs/.Target.cs/.uproject/.ini, grep UCLASS(config=)
"""
import argparse
import bisect
import glob
import gzip
import json
import os
import random
import re
import subprocess
import sys
from collections import defaultdict, Counter
from multiprocessing import Pool
from pathlib import Path

UE = "/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release"
OUT = "/home/timeshift/opensource/break/docs/ue5.8.3/appendix"
PRUNE = ["ThirdParty", "Intermediate", "Binaries", ".git", "Saved", "obj", "bin"]
SEED = 20261019


# --------------------------------------------------------------------------- shell helpers (ground truth)
def find(root, tops, names, prune=PRUNE, iname=False):
    cmd = ["find"] + [t for t in tops if os.path.isdir(os.path.join(root, t))]
    if prune:
        cmd += ["("] + sum([["-name", p, "-o"] for p in prune], [])[:-1] + [")", "-prune", "-o"]
    cmd += ["-type", "f", "("] + sum([["-iname" if iname else "-name", n, "-o"] for n in names], [])[:-1] + \
           [")", "-print"]
    r = subprocess.run(cmd, cwd=root, capture_output=True, text=True)
    return sorted(x[2:] if x.startswith("./") else x for x in r.stdout.split("\n") if x)


def grep_l(root, tops, pattern, includes, excl=PRUNE):
    cmd = ["grep", "-rlE"] + [f"--include={i}" for i in includes] + [f"--exclude-dir={d}" for d in excl] + \
          [pattern] + [t for t in tops if os.path.isdir(os.path.join(root, t))]
    r = subprocess.run(cmd, cwd=root, capture_output=True, text=True)
    return sorted(x for x in r.stdout.split("\n") if x)


def grep_count(root, tops, pattern, includes, excl=PRUNE):
    cmd = ["grep", "-rhoE"] + [f"--include={i}" for i in includes] + [f"--exclude-dir={d}" for d in excl] + \
          [pattern] + [t for t in tops if os.path.isdir(os.path.join(root, t))]
    r = subprocess.run(cmd, cwd=root, capture_output=True, text=True)
    return len([x for x in r.stdout.split("\n") if x])


def pct(a, b):
    return 100.0 * a / b if b else 100.0


# --------------------------------------------------------------------------- own lexer
LEX_RE = re.compile(r'R"([^(\s"]{0,16})\((?:.|\n)*?\)\1"|//[^\n]*|/\*(?:.|\n)*?\*/|"(?:\\.|[^"\\\n])*"|'
                    r"'(?:\\.|[^'\\\n]){1,8}'")


def _blank(m):
    t = m.group(0)
    if t.startswith("/"):
        return re.sub(r"[^\n]", " ", t)
    q = t.index('"') if '"' in t[:20] and not t.startswith("'") else 0
    return t[:q + 1] + re.sub(r"[^\n]", " ", t[q + 1:-1]) + t[-1]


def strip_code(text):
    """Blank comments and string/char literal contents, keep newlines (independent implementation)."""
    return LEX_RE.sub(_blank, text)


def blank_if0(lines):
    """Blank lines inside `#if 0 ... #else|#endif` (code never compiled by any configuration)."""
    depth, dead = 0, 0
    for i, l in enumerate(lines):
        s = l.strip()
        if dead:
            if re.match(r"#\s*if", s):
                depth += 1
            elif re.match(r"#\s*endif", s):
                if depth == 0:
                    dead = 0
                else:
                    depth -= 1
            elif re.match(r"#\s*(else|elif)", s) and depth == 0:
                dead = 0
            lines[i] = " " * len(l)
        elif re.match(r"#\s*if\s+0\b", s):
            dead, depth = 1, 0
    return lines


def blank_directives(code):
    lines = blank_if0(code.split("\n"))
    i, directive = 0, set()
    while i < len(lines):
        if lines[i].lstrip().startswith("#"):
            j = i
            while lines[j].rstrip().endswith("\\") and j + 1 < len(lines):
                j += 1
            for k in range(i, j + 1):
                directive.add(k + 1)
                lines[k] = " " * len(lines[k])
            i = j + 1
        else:
            i += 1
    return "\n".join(lines), directive


def line_index(text):
    return [m.start() for m in re.finditer("\n", text)]


def line_of(nl, pos):
    return bisect.bisect_left(nl, pos) + 1


def paren_end(code, i, limit=20000):
    d = 0
    for j in range(i, min(len(code), i + limit)):
        c = code[j]
        if c == "(":
            d += 1
        elif c == ")":
            d -= 1
            if d == 0:
                return j
    return -1


# --------------------------------------------------------------------------- generated-artefact readers
def md_sections(paths):
    """Paths of `### \\`file\\`` headers in generated Markdown (+ per-file section text offsets)."""
    out = set()
    for p in paths:
        with open(p, encoding="utf-8", errors="replace") as f:
            for l in f:
                if l.startswith("### `"):
                    m = re.match(r"### `([^`]+)`", l)
                    if m:
                        out.add(m.group(1))
    return out


def load_index(paths):
    """{path: {line: [(kind, scope, name)]}} from gz TSV indexes."""
    idx = defaultdict(lambda: defaultdict(list))
    for p in paths:
        with gzip.open(p, "rt", encoding="utf-8", errors="replace") as g:
            for l in g:
                c = l.rstrip("\n").split("\t")
                if len(c) < 5:
                    continue
                try:
                    ln = int(c[1])
                except ValueError:
                    continue
                idx[c[0]][ln].append((c[2], c[3], c[4]))
    return idx


def md_text_by_file(paths, wanted):
    """{file: section text} for the wanted files only (memory bound)."""
    out = {}
    for p in paths:
        cur, buf = None, []
        with open(p, encoding="utf-8", errors="replace") as f:
            for l in f:
                if l.startswith("### `"):
                    if cur in wanted:
                        out[cur] = "".join(buf)
                    m = re.match(r"### `([^`]+)`", l)
                    cur, buf = (m.group(1) if m else None), []
                elif cur in wanted:
                    buf.append(l)
        if cur in wanted:
            out[cur] = "".join(buf)
    return out


# --------------------------------------------------------------------------- C++ header scanner (independent)
REFLECT = ("UCLASS", "USTRUCT", "UENUM", "UINTERFACE", "UFUNCTION", "UPROPERTY", "UDELEGATE")
REFLECT_RE = re.compile(r"\b(" + "|".join(REFLECT) + r")\s*\(")
TYPE_DEF_RE = re.compile(
    r"\b(class|struct|union|enum\s+class|enum\s+struct|enum)\s+"
    r"((?:[A-Z_][A-Z0-9_]*_API\s+|alignas\s*\([^()]*\)\s*|UE_DEPRECATED\s*\((?:[^()]|\([^()]*\))*\)\s*|"
    r"\[\[[^\]]*\]\]\s*|MS_ALIGN\s*\([^()]*\)\s*|GCC_ALIGN\s*\([^()]*\)\s*|DECLSPEC_\w+\s*)*)"
    r"([A-Za-z_]\w*)\s*(?:final\s*)?(?::(?!:)[^;{}()]*(?:\([^;{}()]*\)[^;{}()]*)*)?\{")
CAPS_CALL_RE = re.compile(r"\b[A-Z_][A-Z0-9_]*\s*\((?:[^()]|\((?:[^()]|\([^()]*\))*\))*\)")
KEYWORDS = {"if", "for", "while", "switch", "return", "sizeof", "decltype", "alignas", "alignof", "static_assert",
            "catch", "throw", "new", "delete", "typeid", "noexcept", "requires", "co_return", "co_await", "else",
            "do", "case", "using", "typedef", "operator", "template", "explicit", "constexpr", "consteval"}
TYPEISH_RE = re.compile(r"^[\w\s:<>,\*&\.\[\]~()]*$")
LIT_ARG_RE = re.compile(r'^\s*(?:"|[-+]?\d|TEXT\s*\(|L"|u8"|true\b|false\b|nullptr\b|\{|\[|&\w)')
TAIL_TOKEN_RE = re.compile(r"\s*(?:const\b|volatile\b|&&|&|noexcept\s*\([^()]*\)|noexcept\b|override\b|final\b|"
                           r"throw\s*\(\s*\)|[A-Z_][A-Z0-9_]*\s*\([^()]*\)|[A-Z_][A-Z0-9_]*\b)")


def tail_ok(tail):
    """Linear check that what follows a parameter list is a declaration tail (no nested quantifiers)."""
    t = tail
    for _ in range(50):
        m = TAIL_TOKEN_RE.match(t)
        if not m or m.end() == 0:
            break
        t = t[m.end():]
    t = t.strip()
    if not t or t.startswith(("->", "requires", ":")):
        return True
    return bool(re.fullmatch(r"=\s*(?:0|default|delete)", t))


def classify_block(seg):
    s = CAPS_CALL_RE.sub(" ", seg)
    s = re.sub(r"\balignas\s*\([^()]*\)|\[\[[^\]]*\]\]", " ", s)
    s = re.sub(r"template\s*<[^{};]*>", " ", s)
    st = s.strip()
    if re.match(r"(?:inline\s+)?namespace\b[^()]*$", st) or re.match(r'extern\s+"', seg.strip()):
        return "scope", ""
    if re.search(r"\benum\b", st) and "(" not in st:
        return "enum", ""
    m = re.match(r"(?:.*\s)?(?:class|struct|union)\s+(?:\w+\s+)*?([A-Za-z_]\w*)\s*(?:final\s*)?(?::(?!:).*)?$", st, re.S)
    if m and "(" not in st and "=" not in st:
        return "scope", m.group(1)
    if re.match(r"(?:class|struct|union)\s*$", st):
        return "scope", ""
    return "body", ""


def clean_stmt(seg):
    s = seg
    while True:
        s2 = re.sub(r"^\s*(?:(?:public|private|protected)\s*:|template\s*<(?:[^<>]|<(?:[^<>]|<[^<>]*>)*>)*>|"
                    r"\[\[[^\]]*\]\]|[A-Z_][A-Z0-9_]*\s*\((?:[^()]|\((?:[^()]|\([^()]*\))*\))*\))", "", s)
        if s2 == s:
            return s
        s = s2


def function_candidate(seg, cls):
    """-> (name, offset_of_name_in_seg, reason) ; reason '' means a valid declaration candidate."""
    if len(seg) > 6000:
        lead = len(seg) - len(seg.lstrip())
        if len(seg) - lead > 6000:
            return None
    st = clean_stmt(seg)
    off0 = len(seg) - len(st)
    d_angle, i = 0, 0
    for i, c in enumerate(st):
        if c == "<":
            d_angle += 1
        elif c == ">":
            d_angle = max(0, d_angle - 1)
        elif c == "(" and d_angle == 0:
            break
        elif c in "=;{}" and d_angle == 0:
            return None
    else:
        return None
    pre = st[:i].rstrip()
    m = re.search(r"[A-Za-z_]\w*$", pre)
    if not m:
        return None
    start = m.start()
    head = pre[:start].rstrip()
    name = m.group(0)
    if head.endswith("~"):
        name = "~" + name
        head = head[:-1]
        start = len(head)
    bare = name.lstrip("~")
    ret = head
    if bare in KEYWORDS or ret.endswith("operator") and re.search(r"\boperator$", ret):
        return None
    if re.fullmatch(r"[A-Z_][A-Z0-9_]*", bare):
        return (name, off0 + m.start(), "macro-like")
    ret_s = re.sub(r"\b(?:[A-Z_][A-Z0-9_]*_API|static|virtual|inline|constexpr|consteval|explicit|friend|extern|"
                   r"FORCEINLINE|FORCENOINLINE|UE_FORCEINLINE_HINT|UE_NODISCARD|UE_NODISCARD_CTOR|mutable|"
                   r"typename|const|volatile|unsigned|signed)\b", " ", ret).strip()
    if "=" in ret or "(" in ret_s or ")" in ret_s:
        return None
    if not ret_s:
        if not cls or bare != cls:
            return None
    elif not TYPEISH_RE.match(ret_s):
        return None
    close = -1
    d = 0
    for j in range(i, len(st)):
        if st[j] == "(":
            d += 1
        elif st[j] == ")":
            d -= 1
            if d == 0:
                close = j
                break
    if close < 0:
        return None
    args = st[i + 1:close]
    tail = st[close + 1:]
    if not tail_ok(tail):
        return None
    parts, dd, cur = [], 0, ""
    for c in args:
        if c in "(<[{":
            dd += 1
        elif c in ")>]}":
            dd -= 1
        if c == "," and dd == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += c
    parts.append(cur)
    if any(LIT_ARG_RE.match(p) for p in parts if p.strip()):
        return (name, off0 + m.start(), "object-construction")
    if ret_s and all(p.strip() and re.fullmatch(r"\s*[A-Za-z_]\w*\s*", p) for p in parts) and \
            not re.search(r"[*&>]", ret_s) and len(ret_s.split()) == 1 and re.match(r"F|T|U|A", ret_s) and \
            any(re.match(r"[a-z]", p.strip()) or re.match(r"G[A-Z]|In[A-Z]", p.strip()) for p in parts):
        return (name, off0 + m.start(), "ambiguous-construction")
    return (name, off0 + m.start(), "")


def scan_header(args):
    root, rel = args
    try:
        raw = open(os.path.join(root, rel), encoding="utf-8", errors="replace").read()
    except OSError as e:
        return rel, None, str(e)
    raw = raw.lstrip("\ufeff").replace("\r\n", "\n").replace("\r", "\n")
    code, _ = blank_directives(strip_code(raw))
    nl = line_index(code)
    refl = []
    for m in REFLECT_RE.finditer(code):
        o = m.end() - 1
        e = paren_end(code, o)
        if e < 0:
            refl.append((m.group(1), line_of(nl, m.start()), -1))
            continue
        k = e + 1
        while k < len(code) and code[k] in " \t\n;":
            k += 1  # tolerate `UPROPERTY(...);` (stray semicolon, accepted by UHT)
        dpar = 0
        end = -1
        for j in range(k, min(len(code), k + 4000)):
            c = code[j]
            if c == "(":
                dpar += 1
            elif c == ")":
                dpar -= 1
            elif dpar <= 0 and c in ";{":
                end = j
                break
        refl.append((m.group(1), line_of(nl, m.start()), line_of(nl, end) if end >= 0 else line_of(nl, e)))
    types = [(m.group(3), line_of(nl, m.start(3)), m.group(1).split()[0]) for m in TYPE_DEF_RE.finditer(code)]
    funcs = []
    stack = []
    last = 0
    pdepth = 0
    for m in re.finditer(r"[{};()]", code):
        c = m.group()
        if c == "(":
            pdepth += 1
            continue
        if c == ")":
            pdepth = max(0, pdepth - 1)
            continue
        if pdepth > 0:
            continue
        at_scope = all(t == "scope" for t, _ in stack)
        seg = code[last:m.start()]
        if at_scope and c in ";{" and "(" in seg:
            cls = stack[-1][1] if stack else ""
            fc = function_candidate(seg, cls)
            if fc:
                funcs.append((fc[0].lstrip("~") if not fc[0].startswith("~") else fc[0], line_of(nl, last + fc[1]),
                              fc[2]))
        if c == "{":
            kind, nm = classify_block(seg) if at_scope else ("body", "")
            stack.append((kind, nm))
        elif c == "}":
            if stack:
                stack.pop()
        last = m.end()
    return rel, dict(refl=refl, types=types, funcs=funcs, lines=raw.count("\n") + 1), ""


# --------------------------------------------------------------------------- check 1-4: C++
def tier_of(rel):
    p = rel.split("/")
    return p[1] if p[0] == "Source" and len(p) > 2 else p[0]


def check_cpp(root, out, jobs, n_types, n_funcs, rng):
    res = {}
    hdr = find(root, ["Source", "Plugins", "Platforms"], ["*.h", "*.hpp", "*.inl"])
    tests = [h for h in hdr if any(p in ("Tests", "Test", "LowLevelTests") for p in h.split("/")[:-1])]
    nontest = [h for h in hdr if h not in set(tests)]
    md = [p for p in glob.glob(os.path.join(out, "api", "*", "*.md"))
          if os.sep + "CSharp" + os.sep not in p and os.sep + "Shaders" + os.sep not in p]
    secs = md_sections(md)
    idxfiles = [p for p in glob.glob(os.path.join(out, "index", "*.tsv.gz"))
                if not os.path.basename(p).startswith(("CSharp__", "shaders", "csharp_"))]
    idx = load_index(idxfiles)
    in_md = [h for h in nontest if h in secs]
    in_idx = [h for h in nontest if h in idx]
    missing = [h for h in nontest if h not in secs]
    extra = sorted(s for s in secs if s not in set(hdr))
    res["headers"] = dict(found=len(hdr), tests_excluded=len(tests), expected=len(nontest), in_md=len(in_md),
                          with_symbols=len(in_idx), missing=missing[:300], n_missing=len(missing),
                          md_not_on_disk=extra[:50], n_md_not_on_disk=len(extra),
                          empty_files=[h for h in in_md if h not in idx][:100],
                          n_empty=len([h for h in in_md if h not in idx]))
    miss_by = Counter("/".join(h.split("/")[:3]) for h in missing)
    res["headers"]["missing_by_dir"] = miss_by.most_common(30)
    # per-file scan (independent parser)
    scan = {}
    errs = []
    with Pool(jobs) as pool:
        for rel, r, e in pool.imap_unordered(scan_header, [(root, h) for h in nontest], chunksize=64):
            if r is None:
                errs.append((rel, e))
            else:
                scan[rel] = r
    res["scan_errors"] = errs[:50]
    with_decl = [h for h in nontest if h in scan and (scan[h]["types"] or scan[h]["refl"] or
                                                      any(not w for _, _, w in scan[h]["funcs"]))]
    res["headers"]["with_decl"] = len(with_decl)
    res["headers"]["with_decl_indexed"] = len([h for h in with_decl if h in idx])
    res["headers"]["with_decl_not_indexed"] = [h for h in with_decl if h not in idx][:100]
    # ---- reflection macros
    grep_total = {m: grep_count(root, ["Source", "Plugins", "Platforms"], r"\b" + m + r"\s*\(",
                                ["*.h", "*.hpp", "*.inl"]) for m in REFLECT}
    tot, hit, attached, att_tot = Counter(), Counter(), Counter(), Counter()
    miss_ex = defaultdict(list)
    md_need = set()
    sample_attach = []
    for rel, r in scan.items():
        for mac, l0, l1 in r["refl"]:
            tot[mac] += 1
            lines = idx.get(rel, {})
            ok = l1 > 0 and any(lines.get(l) for l in range(l0, l1 + 1))
            if ok:
                hit[mac] += 1
            elif len(miss_ex[mac]) < 25:
                miss_ex[mac].append(f"{rel}:{l0}")
            sample_attach.append((rel, mac, l0))
    rng2 = random.Random(SEED + 7)
    sample_attach = rng2.sample(sample_attach, min(3000, len(sample_attach)))
    md_need = {r for r, _, _ in sample_attach}
    texts = md_text_by_file(md, md_need)
    for rel, mac, l0 in sample_attach:
        att_tot[mac] += 1
        if f"{mac}(" in texts.get(rel, ""):
            attached[mac] += 1
    res["reflection"] = dict(grep_total=grep_total, scanned=dict(tot), hit=dict(hit),
                             attach_sample=dict(att_tot), attach_hit=dict(attached),
                             missing_examples={k: v for k, v in miss_ex.items()})
    # ---- types sample
    allt = [(rel, n, l, k) for rel, r in scan.items() for (n, l, k) in r["types"]]
    st = rng.sample(allt, min(n_types, len(allt)))
    th, tmiss = 0, []
    for rel, n, l, k in st:
        rows = idx.get(rel, {})
        ok = any(x[2] == n and x[0] in ("class", "struct", "union", "enum") for d in (0, -1, 1, -2, 2)
                 for x in rows.get(l + d, []))
        if not ok:
            ok = any(x[2] == n and x[0] in ("class", "struct", "union", "enum") for lst in rows.values() for x in lst)
            if ok:
                ok = "line-shift"
        if ok:
            th += 1
        else:
            tmiss.append(f"{rel}:{l} {k} {n}")
    res["types"] = dict(population=len(allt), sample=len(st), hit=th, missing=tmiss)
    # ---- functions sample
    allf = [(rel, n, l) for rel, r in scan.items() for (n, l, why) in r["funcs"] if not why]
    excluded = Counter(why for r in scan.values() for (_, _, why) in r["funcs"] if why)
    sf = rng.sample(allf, min(n_funcs, len(allf)))
    fh, fmiss = 0, []
    fkinds = ("prototype", "function", "member", "variable", "externvar", "macro", "typedef")
    for rel, n, l in sf:
        rows = idx.get(rel, {})
        ok = any(x[2] == n.lstrip("~") or x[2] == n for d in (0, -1, 1, -2, 2, -3, 3) for x in rows.get(l + d, []))
        if ok:
            fh += 1
        else:
            fmiss.append(f"{rel}:{l} {n}")
    mt = md_text_by_file(md, {m.split(":")[0] for m in fmiss})
    in_text = [m for m in fmiss if re.search(r"\b" + re.escape(m.split()[-1].lstrip("~")) + r"\s*\(",
                                             mt.get(m.split(":")[0], ""))]
    res["functions"] = dict(population=len(allf), excluded=dict(excluded), sample=len(sf), hit=fh, missing=fmiss,
                            miss_but_in_md_text=len(in_text))
    return res


# --------------------------------------------------------------------------- check 5: C#
CS_TYPE_RE = re.compile(r"^[ \t]*(?:\[[^\]\n]*\]\s*)*(?:(?:public|private|protected|internal|static|sealed|abstract|"
                        r"partial|readonly|unsafe|new|file|ref)\s+)*(class|struct|interface|enum|record(?:\s+struct|"
                        r"\s+class)?)\s+([A-Za-z_]\w*)", re.M)


def check_csharp(root, out, rng, n):
    cs = find(root, ["Source", "Plugins", "Platforms", "Build"], ["*.cs"],
              prune=["ThirdParty", "Intermediate", "obj", "bin", ".git", "Saved", "Binaries"])
    is_test = lambda rel: any(re.search(r"Tests?$", p[:-3] if p.endswith(".cs") else p) for p in rel.split("/"))
    tests = [c for c in cs if is_test(c)]
    want = [c for c in cs if not is_test(c)]
    secs = md_sections(glob.glob(os.path.join(out, "api", "CSharp", "*.md")))
    listed = set(json.load(open(os.path.join(out, "csharp_files.json"))))
    missing = [c for c in want if c not in secs]
    idx = load_index(glob.glob(os.path.join(out, "index", "CSharp__*.tsv.gz")))
    types = []
    for rel in want:
        try:
            t = strip_code(open(os.path.join(root, rel), encoding="utf-8", errors="replace").read())
        except OSError:
            continue
        nl = line_index(t)
        for m in CS_TYPE_RE.finditer(t):
            types.append((rel, m.group(2), line_of(nl, m.start(2)), m.group(1)))
    st = rng.sample(types, min(n, len(types)))
    hit, miss = 0, []
    for rel, nm, l, k in st:
        rows = idx.get(rel, {})
        if any(x[2] == nm for d in (0, -1, 1) for x in rows.get(l + d, [])):
            hit += 1
        else:
            miss.append(f"{rel}:{l} {k} {nm}")
    summ = json.load(open(os.path.join(out, "csharp_summary.json")))
    return dict(found=len(cs), tests_excluded=len(tests), expected=len(want), in_md=len(want) - len(missing),
                in_list=len([c for c in want if c in listed]), missing=missing[:200], n_missing=len(missing),
                type_population=len(types), type_sample=len(st), type_hit=hit, type_missing=miss[:200],
                rules_files=len([c for c in want if re.search(r"\.(build|target)\.cs$", c, re.I)]),
                ctags_names=sum(g["ct_total"] for g in summ["groups"]),
                ctags_hit=sum(g["ct_hit"] for g in summ["groups"]))


# --------------------------------------------------------------------------- check 6: shaders
def check_shaders(root, out):
    sh = find(root, ["Shaders", "Plugins", "Platforms", "Source"], ["*.usf", "*.ush"], prune=[".git"])
    shared_h = find(root, ["Shaders"], ["*.h"], prune=[".git"])
    secs = md_sections(glob.glob(os.path.join(out, "api", "Shaders", "*.md")))
    idx = load_index([os.path.join(out, "index", "shaders.tsv.gz")])
    missing = [f for f in sh + shared_h if f not in secs]
    probes = Counter()
    hits = Counter()
    miss = defaultdict(list)
    for rel in sh:
        try:
            raw = open(os.path.join(root, rel), encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
        except OSError:
            continue
        code = strip_code(raw)
        lines = code.split("\n")
        rows = idx.get(rel, {})
        for i, l in enumerate(lines, 1):
            s = l.strip()
            probe = None
            if re.match(r"#\s*include\b", s):
                probe = ("include", ("include",))
            elif re.match(r"#\s*define\s+\w", s):
                probe = ("define", ("define",))
            elif re.match(r"\[\s*numthreads\s*\(", s, re.I):
                # entry declared on this or following lines
                probe = ("numthreads-entry", ("entry",), 6)
            elif re.match(r"struct\s+[A-Za-z_]\w*\s*(\{|$)", s) and not l.startswith((" ", "\t")):
                probe = ("struct", ("struct", "class", "unparsed", "macro_block"))
            elif re.match(r"[A-Za-z_][\w<>,\s]*\s+[A-Za-z_]\w*\s*\(", s) and not l[:1].isspace() and \
                    not re.match(r"(return|if|for|while|switch|else|#|do)\b", s) and \
                    not re.match(r"[A-Z_][A-Z0-9_]*\s*\(", s):
                probe = ("toplevel-function", ("function", "entry", "prototype", "macro_call", "macro_block",
                                               "resource", "parameter", "static_const", "unparsed", "typedef",
                                               "method", "groupshared", "static_var", "member"), 2)
            if not probe:
                continue
            name, kinds = probe[0], probe[1]
            span = probe[2] if len(probe) > 2 else 0
            probes[name] += 1
            # a record may sit on a preceding attribute / template<> / #if-split attribute line, or on following lines
            back = 6 if name in ("toplevel-function", "numthreads-entry") else 2
            ok = any(x[0] in kinds for d in range(-back, span + 1) for x in rows.get(i + d, []))
            if ok:
                hits[name] += 1
            elif len(miss[name]) < 25:
                miss[name].append(f"{rel}:{i}")
    rep = json.load(open(os.path.join(out, "shaders_summary.json")))
    return dict(found=len(sh), shared_h=len(shared_h), in_md=len(sh) + len(shared_h) - len(missing),
                missing=missing, probes=dict(probes), hits=dict(hits), probe_missing={k: v for k, v in miss.items()},
                parse_modes=rep.get("parse_modes", {}), failures=len(rep.get("failures", [])),
                unparsed=rep.get("stat", {}).get("unparsed", 0), stray=rep.get("stat", {}).get("stray_block", 0),
                records=rep.get("total_records"))


# --------------------------------------------------------------------------- check 7: CVars
CV_TOKENS = (r"TAutoConsoleVariable|FAutoConsoleVariableRef|FAutoConsoleVariable|FAutoConsoleCommand\w*|"
             r"FAutoConsoleVariableSink|FAutoConsoleTaskPriority|FAutoConsoleVariableDeprecated|"
             r"TAutoConsoleVariableDeprecated_NoReplace|FAutoConsoleVariableShadow|RegisterConsoleVariable\w*|"
             r"RegisterConsoleCommand|RegisterDelegatedConsoleVariable")
CV_LIT_RE = re.compile(r"\b(?:" + CV_TOKENS + r")\b\s*(?:<[^<>;()]*>)?\s*(?:[A-Za-z_]\w*\s*)?[({]\s*"
                       r"(?:(?:ECVF_\w+(?:\s*\|\s*ECVF_\w+)*|FCVarDeprecationArgs\s*\{[^{}]*\})\s*,\s*)?"
                       r"(?:TEXT\s*\(\s*)?\"([A-Za-z_][\w.\-]*)\"", re.S)


def check_cvars(root, out, rng):
    exts = ["*.cpp", "*.h", "*.inl", "*.hpp", "*.c", "*.cc", "*.mm", "*.m"]
    files = grep_l(root, ["Source", "Plugins", "Platforms"], r"\b(" + CV_TOKENS + r")\b", exts)
    tsvp = os.path.join(out, "dictionary", "cvars.tsv")
    names, by_file = set(), defaultdict(set)
    rows = 0
    with open(tsvp, encoding="utf-8") as f:
        hdr = f.readline().rstrip("\n").split("\t")
        ni, fi, li = hdr.index("name"), hdr.index("file"), hdr.index("line")
        for l in f:
            c = l.rstrip("\n").split("\t")
            rows += 1
            names.add(c[ni].lower())
            by_file[c[fi]].add(c[ni].lower())
    rep = json.load(open(os.path.join(out, "dictionary", "cvars_report.json")))
    scanned = set(rep.get("files", []))
    lit, hit, miss = 0, 0, []
    all_lits = []
    for rel in files:
        try:
            raw = open(os.path.join(root, rel), encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        # strip comments only (names live in strings)
        code = re.sub(r"//[^\n]*|/\*(?:.|\n)*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), raw)
        code, _ = blank_directives(code)
        nl = line_index(code)
        for m in CV_LIT_RE.finditer(code):
            all_lits.append((rel, m.group(1), line_of(nl, m.start())))
    for rel, nm, l in all_lits:
        lit += 1
        if nm.lower() in by_file.get(rel, set()):
            hit += 1
        elif len(miss) < 200:
            miss.append(f"{rel}:{l} {nm}" + ("" if nm.lower() not in names else " (name present, other file)"))
    # files: grep set vs files scanned / present in tsv
    files_missing = [f for f in files if f not in scanned]
    # ini
    inis = find(root, ["Config", "Plugins", "Platforms", "Programs", "Source"], ["*.ini"], prune=PRUNE[1:], iname=True)
    ini_cv = 0
    for rel in inis:
        sect = ""
        try:
            lines = open(os.path.join(root, rel), encoding="utf-8", errors="replace").read().splitlines()
        except OSError:
            continue
        for l in lines:
            s = l.strip()
            if s.startswith("["):
                sect = s.strip("[]")
            elif s and not s.startswith((";", "#")) and "=" in s and (
                    sect == "ConsoleVariables" or sect == "Startup" or sect.startswith("SystemSettings") or
                    re.match(r"\w+Quality@", sect) or (sect.endswith(" DeviceProfile") and s.lstrip("+-.!")
                                                       .startswith("CVars="))):
                ini_cv += 1
    ini_rows = sum(1 for _ in open(os.path.join(out, "dictionary", "cvars_ini.tsv"), encoding="utf-8")) - 1
    return dict(grep_files=len(files), scanned_files=len(scanned), files_missing=files_missing[:100],
                n_files_missing=len(files_missing), files_with_rows=len(by_file), tsv_rows=rows,
                distinct_names=len(names), literal_sites=lit, literal_hit=hit, literal_missing=miss,
                ini_files=len(inis), ini_lines=ini_cv, ini_rows=ini_rows, status=rep.get("status", {}),
                failures=rep.get("failures", 0))


# --------------------------------------------------------------------------- check 8: catalog
def tsv_count(p, col=None):
    with open(p, encoding="utf-8") as f:
        hdr = f.readline().rstrip("\n").split("\t")
        if col is None:
            return sum(1 for _ in f), None
        ci = hdr.index(col)
        vals = [l.rstrip("\n").split("\t")[ci] for l in f]
        return len(vals), vals


def check_catalog(ue, out):
    e = os.path.join(ue, "Engine")
    d = os.path.join(out, "dictionary")
    upl = find(ue, ["."], ["*.uplugin"], prune=[".git", "Intermediate", "Binaries", "Saved"])
    bcs = find(e, ["Source", "Plugins", "Platforms"], ["*.build.cs"], prune=[".git", "Intermediate", "Binaries",
                                                                          "Saved", "obj", "bin"], iname=True)
    tcs = find(ue, ["."], ["*.Target.cs"], prune=[".git", "Intermediate", "Binaries", "Saved", "obj", "bin"])
    upj = find(ue, ["."], ["*.uproject"], prune=[".git", "Intermediate", "Binaries", "Saved"])
    ini = [x for x in find(e, ["."], ["*.ini"], prune=[".git", "Intermediate", "Binaries", "Saved", "obj", "bin"],
                           iname=True) if "/ThirdParty/" not in "/" + x]
    _, pf = tsv_count(os.path.join(d, "plugins.tsv"), "file")
    _, mf = tsv_count(os.path.join(d, "modules.tsv"), "file")
    _, tf = tsv_count(os.path.join(d, "targets.tsv"), "file")
    _, jf = tsv_count(os.path.join(d, "projects.tsv"), "file")
    _, cf = tsv_count(os.path.join(d, "config.tsv"), "file")
    ucl_files = grep_l(e, ["Source", "Plugins", "Platforms"], r"^[[:space:]]*UCLASS\s*\([^)]*\b[Cc]onfig\s*=",
                       ["*.h", "*.hpp"], excl=PRUNE)
    ucl_n = grep_count(e, ["Source", "Plugins", "Platforms"], r"^[[:space:]]*UCLASS\s*\([^)]*\b[Cc]onfig\s*=", ["*.h", "*.hpp"],
                       excl=PRUNE)
    _, uf = tsv_count(os.path.join(d, "uclass_config.tsv"), "file")
    mods_json = json.load(open(os.path.join(out, "modules.json")))
    bcs_mod = find(e, ["Source", "Plugins", "Platforms"], ["*.build.cs"], prune=PRUNE, iname=True)
    res = {}
    for key, disk, got in (("uplugin", upl, pf), ("build_cs", ["Engine/" + x for x in bcs] and bcs, mf),
                           ("target_cs", tcs, tf), ("uproject", upj, jf), ("ini", ini, cf)):
        gs = set(got)
        miss = [x for x in disk if x not in gs]
        res[key] = dict(disk=len(disk), covered=len(disk) - len(miss), missing=miss[:50])
    # config.tsv lists sections; a file with no sections still appears? check by file presence
    res["uclass_config"] = dict(grep_lines_single_line=ucl_n, files=len(ucl_files),
                                files_covered=len(set(ucl_files) & set(uf)), rows=len(uf),
                                missing=[x for x in ucl_files if x not in set(uf)][:50])
    res["modules_json"] = dict(build_cs_outside_thirdparty=len(bcs_mod), modules_json=len(
        [m for m in mods_json["modules"] if m["tier"] != "NoModule"]))
    return res


# --------------------------------------------------------------------------- report
def row(label, hit, total, note=""):
    p = pct(hit, total)
    flag = "" if p >= 99.0 else " ⚠"
    return f"| {label} | {hit} / {total} | {p:.2f}%{flag} | {note} |"


def write_report(out, R, args):
    c, cs, sh, cv, ca = R["cpp"], R["csharp"], R["shaders"], R["cvars"], R["catalog"]
    h, rf, ty, fn = c["headers"], c["reflection"], c["types"], c["functions"]
    rtot = sum(rf["scanned"].values())
    rhit = sum(rf["hit"].values())
    atot = sum(rf["attach_sample"].values())
    ahit = sum(rf["attach_hit"].values())
    L = ["# Appendix coverage report", "",
         f"Generated by `tools/coverage_check.py` (seed {SEED}, type sample {args.types}, function sample "
         f"{args.funcs}, C# type sample {args.cs_types}). Ground truth comes from `find`/`grep` and this script's own "
         "comment-masking + regex scanner, which shares no code with the extractors. Numbers are reported as "
         "measured; ⚠ marks < 99%. Each miss category is explained in “Known gaps”.", "",
         "## Summary", "",
         "| check | hit / total | rate | note |", "|---|---|---|---|",
         row("C++ headers → api/*.md section", h["in_md"], h["expected"],
             f"{h['found']} found, {h['tests_excluded']} under Tests/Test/LowLevelTests excluded by design"),
         row("C++ headers with declarations → ≥1 indexed symbol", h["with_decl_indexed"], h["with_decl"],
             f"headers where the independent scanner sees a type/function/U-macro; overall {h['with_symbols']}/"
             f"{h['expected']} headers have symbols, the other {h['n_empty']} render “no declarations extracted”"),
         row("Reflection macros → symbol at the declaration", rhit, rtot,
             "comment-free UCLASS/USTRUCT/UENUM/UINTERFACE/UFUNCTION/UPROPERTY/UDELEGATE; grep(raw, incl. comments) = "
             f"{sum(rf['grep_total'].values())}"),
         row("Reflection macro text attached in Markdown (sample)", ahit, atot, "macro text present in the file section"),
         row(f"C++ types (sample {ty['sample']} of {ty['population']})", ty["hit"], ty["sample"],
             "class/struct/union/enum definitions"),
         row(f"C++ functions (sample {fn['sample']} of {fn['population']})", fn["hit"], fn["sample"],
             "namespace/class-scope declarations & definitions, matched by name in the symbol index"),
         row("C++ functions, index miss but declaration text present in Markdown", fn["hit"] +
             fn.get("miss_but_in_md_text", 0), fn["sample"], "name( appears in the file's Markdown section"),
         row("C# files → api/CSharp section", cs["in_md"], cs["expected"],
             f"{cs['found']} found, {cs['tests_excluded']} test paths excluded by design"),
         row(f"C# types (sample {cs['type_sample']} of {cs['type_population']})", cs["type_hit"], cs["type_sample"], ""),
         row("C# ctags cross-check (extractor self-report)", cs["ctags_hits"] if "ctags_hits" in cs else cs["ctags_hit"],
             cs["ctags_names"], "names ctags finds that the C# parser also emitted; not independent"),
         row("Shader files → api/Shaders section", sh["in_md"], sh["found"] + sh["shared_h"],
             f"{sh['found']} .usf/.ush + {sh['shared_h']} Engine/Shaders/**.h"),
         ]
    for k in ("include", "define", "numthreads-entry", "struct", "toplevel-function"):
        if k in sh["probes"]:
            L.append(row(f"Shader {k} lines → record", sh["hits"].get(k, 0), sh["probes"][k], ""))
    L += [row("CVar source files (grep) scanned", cv["grep_files"] - cv["n_files_missing"], cv["grep_files"], ""),
          row("CVar literal-name registrations → cvars.tsv (same file)", cv["literal_hit"], cv["literal_sites"],
              "independent regex for `Type[<T>] [Var](|{ [flags,] TEXT(\"name\")`"),
          row("ini CVar lines → cvars_ini.tsv", min(cv["ini_rows"], cv["ini_lines"]), cv["ini_lines"],
              f"{cv['ini_files']} ini files"),
          ]
    for k, lab in (("uplugin", ".uplugin → plugins.tsv"), ("build_cs", "*.Build.cs → modules.tsv"),
                   ("target_cs", "*.Target.cs → targets.tsv"), ("uproject", "*.uproject → projects.tsv"),
                   ("ini", "Engine *.ini → config.tsv")):
        L.append(row(lab, ca[k]["covered"], ca[k]["disk"], ""))
    u = ca["uclass_config"]
    L.append(row("headers with UCLASS(config=) → uclass_config.tsv", u["files_covered"], u["files"],
                 f"{u['rows']} classes listed; single-line grep finds {u['grep_lines_single_line']}"))
    L.append("")
    R["_lines"] = L
    return L


def details(R):
    c, cs, sh, cv, ca = R["cpp"], R["csharp"], R["shaders"], R["cvars"], R["catalog"]
    h, rf, ty, fn = c["headers"], c["reflection"], c["types"], c["functions"]
    L = ["## Details", "", "### C++ headers", "",
         f"- found {h['found']}; test-dir headers excluded {h['tests_excluded']}; expected {h['expected']}; "
         f"sections in Markdown {h['in_md']}; missing {h['n_missing']}; sections whose path is not on disk "
         f"{h['n_md_not_on_disk']}; modules.json lists {ca['modules_json']['modules_json']} modules for "
         f"{ca['modules_json']['build_cs_outside_thirdparty']} Build.cs outside ThirdParty"]
    if h["missing_by_dir"]:
        L.append("- missing by directory: " + ", ".join(f"`{d}` {n}" for d, n in h["missing_by_dir"]))
    if h["missing"]:
        L.append("- missing (first 40): " + ", ".join(f"`{x}`" for x in h["missing"][:40]))
    if c.get("scan_errors"):
        L.append(f"- coverage scanner read errors: {len(c['scan_errors'])}")
    L += ["", "### Reflection macros", "", "| macro | grep (raw) | scanned (comment-free) | symbol at decl | rate | "
          "attached text (sample) |", "|---|---|---|---|---|---|"]
    for m in REFLECT:
        t = rf["scanned"].get(m, 0)
        L.append(f"| {m} | {rf['grep_total'].get(m, 0)} | {t} | {rf['hit'].get(m, 0)} | "
                 f"{pct(rf['hit'].get(m, 0), t):.2f}% | {rf['attach_hit'].get(m, 0)}/{rf['attach_sample'].get(m, 0)} |")
    for m, ex in rf["missing_examples"].items():
        L.append(f"- {m} misses (examples): " + ", ".join(f"`{x}`" for x in ex[:12]))
    L += ["", "### C++ type sample misses", ""] + ([f"- `{x}`" for x in ty["missing"][:80]] or ["_none_"])
    L += ["", "### C++ function sample", "",
          f"- population {fn['population']} (excluded from the population as not real declarations: "
          + ", ".join(f"{k}={v}" for k, v in fn["excluded"].items()) + ")", "- misses:"]
    L += [f"  - `{x}`" for x in fn["missing"][:120]] or ["  - _none_"]
    L += ["", "### C#", "",
          f"- found {cs['found']}, excluded tests {cs['tests_excluded']}, expected {cs['expected']}, in Markdown "
          f"{cs['in_md']}, in csharp_files.json {cs['in_list']}, Build/Target rules files {cs['rules_files']}"]
    if cs["missing"]:
        L.append("- missing files: " + ", ".join(f"`{x}`" for x in cs["missing"][:40]))
    if cs["type_missing"]:
        L.append("- type sample misses: " + ", ".join(f"`{x}`" for x in cs["type_missing"][:60]))
    L += ["", "### Shaders", "",
          f"- records {sh['records']}; parse modes {sh['parse_modes']}; hard failures {sh['failures']}; "
          f"raw-preserved unparsed {sh['unparsed']}; stray brace blocks {sh['stray']}"]
    if sh["missing"]:
        L.append("- files missing: " + ", ".join(f"`{x}`" for x in sh["missing"][:40]))
    for k, ex in sh["probe_missing"].items():
        L.append(f"- {k} misses (examples): " + ", ".join(f"`{x}`" for x in ex[:12]))
    L += ["", "### CVars", "",
          f"- grep files {cv['grep_files']}, scanned by extractor {cv['scanned_files']}, files with ≥1 row "
          f"{cv['files_with_rows']}; tsv rows {cv['tsv_rows']}, distinct names {cv['distinct_names']}; "
          f"extractor failures {cv['failures']}; status counts {cv['status']}"]
    if cv["files_missing"]:
        L.append("- grep files not scanned: " + ", ".join(f"`{x}`" for x in cv["files_missing"][:30]))
    if cv["literal_missing"]:
        L.append("- literal-name misses: " + ", ".join(f"`{x}`" for x in cv["literal_missing"][:60]))
    L += ["", "### Catalog", ""]
    for k in ("uplugin", "build_cs", "target_cs", "uproject", "ini"):
        L.append(f"- {k}: disk {ca[k]['disk']}, covered {ca[k]['covered']}" +
                 (": missing " + ", ".join(f"`{x}`" for x in ca[k]["missing"][:20]) if ca[k]["missing"] else ""))
    u = ca["uclass_config"]
    if u["missing"]:
        L.append("- UCLASS(config=) headers not covered: " + ", ".join(f"`{x}`" for x in u["missing"][:20]))
    return L


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ue", default=UE)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--jobs", type=int, default=14)
    ap.add_argument("--types", type=int, default=2000)
    ap.add_argument("--funcs", type=int, default=3000)
    ap.add_argument("--cs-types", type=int, default=1000)
    ap.add_argument("--gaps", default="", help="Markdown file with the 'Known gaps' section to append")
    ap.add_argument("--only", default="", help="comma list of checks (cpp,csharp,shaders,cvars,catalog)")
    a = ap.parse_args()
    e = os.path.join(a.ue, "Engine")
    jobs = min(a.jobs, 14)
    rng = random.Random(SEED)
    R = {}
    prev = os.path.join(a.out, "coverage.json")
    if a.only and os.path.exists(prev):
        R = json.load(open(prev))
    todo = a.only.split(",") if a.only else ["cpp", "csharp", "shaders", "cvars", "catalog"]
    if "cpp" in todo:
        R["cpp"] = check_cpp(e, a.out, jobs, a.types, a.funcs, rng)
        print("cpp done", file=sys.stderr)
    if "csharp" in todo:
        R["csharp"] = check_csharp(e, a.out, random.Random(SEED + 1), a.cs_types)
        print("csharp done", file=sys.stderr)
    if "shaders" in todo:
        R["shaders"] = check_shaders(e, a.out)
        print("shaders done", file=sys.stderr)
    if "cvars" in todo:
        R["cvars"] = check_cvars(e, a.out, rng)
        print("cvars done", file=sys.stderr)
    if "catalog" in todo:
        R["catalog"] = check_catalog(a.ue, a.out)
        print("catalog done", file=sys.stderr)
    R.pop("_lines", None)
    (Path(a.out) / "coverage.json").write_text(json.dumps(R, indent=1), encoding="utf-8")
    L = write_report(a.out, R, a)
    L += details(R)
    if a.gaps and os.path.exists(a.gaps):
        L += ["", open(a.gaps, encoding="utf-8").read().rstrip()]
    (Path(a.out) / "COVERAGE.md").write_text("\n".join(L) + "\n", encoding="utf-8")
    print("\n".join(R.get("_lines", [])[:60]))


if __name__ == "__main__":
    main()
