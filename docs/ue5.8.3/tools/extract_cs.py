#!/usr/bin/env python3
"""Exhaustive C# declaration extractor for Engine/{Source,Plugins,Platforms,Build}.

Writes api/CSharp/<csproj|dir>.md (+ ModuleRules / TargetRules for *.Build.cs / *.Target.cs, with the
constructor assignments parsed out), index/CSharp__<group>.tsv.gz and csharp_report.md.
A comment/string-aware declaration parser is used (ctags' C# parser misses records, delegates, indexers and
mis-tags conversion operators); universal-ctags (-I attributes, --sort=no) is used as fallback for files the
parser cannot balance, and as a per-file count cross-check.
"""
import argparse
import bisect
import gzip
import json
import os
import re
import subprocess
import sys
from collections import defaultdict, Counter
from multiprocessing import Pool
from pathlib import Path

ENGINE = "/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release/Engine"
OUT = "/home/timeshift/opensource/break/docs/ue5.8.3/appendix"
ROOTS = ("Source", "Plugins", "Platforms", "Build")
SKIP_DIRS = {"ThirdParty", "Intermediate", "obj", "bin", ".git", "Saved", "Binaries"}
TEST_RE = re.compile(r"Tests?$")
RULES_RE = re.compile(r"\.(build|target)\.cs$", re.I)
PART_LIMIT = 3 * 1024 * 1024
MODS = ("public protected internal private static readonly const sealed abstract virtual override partial new "
        "extern unsafe async volatile required file ref fixed implicit explicit").split()
MOD_RE = re.compile(r"^(?:(?:%s)\b\s*)*" % "|".join(MODS))
INTEREST = re.compile(r'//|/\*|[$@]*"|\'|^[ \t]*#', re.M)


# --------------------------------------------------------------------------- discovery
def is_test_path(parts):
    return any(TEST_RE.search(p[:-3] if p.endswith(".cs") else p) for p in parts)


def find_cs(engine):
    out = []
    for top in ROOTS:
        for dp, dns, fns in os.walk(os.path.join(engine, top)):
            dns[:] = sorted(d for d in dns if d not in SKIP_DIRS)
            for fn in fns:
                if fn.endswith(".cs"):
                    rel = os.path.relpath(os.path.join(dp, fn), engine)
                    if not is_test_path(rel.split(os.sep)):
                        out.append(rel)
    return sorted(out)


def group_of(engine, rel, cache={}):
    if RULES_RE.search(rel):
        return ("ModuleRules" if rel.lower().endswith(".build.cs") else "TargetRules"), ""
    d = os.path.dirname(rel)
    chain = []
    while d:
        if d in cache:
            res = cache[d]
            break
        chain.append(d)
        try:
            cs = sorted(x for x in os.listdir(os.path.join(engine, d)) if x.endswith(".csproj"))
        except OSError:
            cs = []
        if cs:
            res = (cs[0][:-len(".csproj")], d)
            cache[d] = res
            chain.pop()
            break
        d = os.path.dirname(d)
    else:
        res = None
    if res is None:
        parts = os.path.dirname(rel).split("/")
        res = ("NoProject__" + "__".join(parts[:4]), "/".join(parts[:4]))
    for c in chain:
        cache[c] = res
    return res


# --------------------------------------------------------------------------- masking
TOK = re.compile(r'//[^\n]*|/\*.*?\*/|^[ \t]*#[^\n]*|\$@"|@\$"|\$+"""|"""+|@"|\$"|"|\'', re.S | re.M)
STR_REG = re.compile(r'(?:[^"\\\n]|\\.)*"')
STR_VERB = re.compile(r'(?:[^"]|"")*"', re.S)
CHR_REG = re.compile(r"'(?:\\(?:u[0-9a-fA-F]{4}|x[0-9a-fA-F]{1,4}|.)|[^'\\\n])'")
DIR_WORD = re.compile(r"#\s*(\w+)")


def blank(s):
    return " " * len(s) if "\n" not in s else re.sub(r"[^\n]", " ", s)


def interp_end(t, i, verbatim):
    depth, n = 0, len(t)
    while i < n:
        c = t[i]
        if depth == 0:
            if c == '"':
                if verbatim and t[i + 1:i + 2] == '"':
                    i += 2
                    continue
                return i + 1
            if c == "\\" and not verbatim:
                i += 2
                continue
            if c == "{":
                if t[i + 1:i + 2] == "{":
                    i += 2
                    continue
                depth = 1
        else:
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
            elif c == "'":
                m2 = CHR_REG.match(t, i)
                if m2:
                    i = m2.end()
                    continue
            elif c == '"':
                m2 = STR_REG.match(t, i + 1)
                i = m2.end() if m2 else i + 1
                continue
        i += 1
    return n


def mask(text):
    """Return (nocomment, code, directives): comments/directives blanked; `code` additionally blanks strings."""
    nc, cd, dirs, pos = [], [], [], 0
    while True:
        m = TOK.search(text, pos)
        if not m:
            nc.append(text[pos:])
            cd.append(text[pos:])
            break
        s, tok = m.start(), m.group()
        seg = text[pos:s]
        nc.append(seg)
        cd.append(seg)
        pos = m.end()
        if tok[:2] in ("//", "/*"):
            b = blank(tok)
            nc.append(b)
            cd.append(b)
            continue
        if tok.lstrip(" \t")[:1] == "#":
            dm = DIR_WORD.match(tok.lstrip(" \t"))
            dirs.append((dm.group(1) if dm else "", s, m.end(), tok[dm.end():].strip() if dm else ""))
            b = blank(tok)
            nc.append(b)
            cd.append(b)
            continue
        if tok == "'":
            m2 = CHR_REG.match(text, s)
            if not m2:
                nc.append(tok)
                cd.append(tok)
                continue
            e = m2.end()
        elif tok == '"':
            m2 = STR_REG.match(text, pos)
            e = m2.end() if m2 else (text.find("\n", pos) if text.find("\n", pos) >= 0 else len(text))
        elif tok == '@"':
            m2 = STR_VERB.match(text, pos)
            e = m2.end() if m2 else len(text)
        elif tok in ('$"',):
            e = interp_end(text, pos, False)
        elif tok in ('$@"', '@$"'):
            e = interp_end(text, pos, True)
        else:
            q = tok.count('"')
            k = text.find('"' * q, pos)
            if k < 0:
                e = len(text)
            else:
                e = k + q
                while e < len(text) and text[e] == '"':
                    e += 1
        nc.append(text[s:e])
        cd.append(blank(text[s:e]))
        pos = e
    return "".join(nc), "".join(cd), dirs


def drop_else_branches(nc, cd, dirs):
    """Blank `#if false` bodies and, when drop_else is on, every #else/#elif branch."""
    stack, regions = [], []
    for w, s, e, cond in dirs:
        if w == "if":
            stack.append({"else": None, "false_from": e if cond == "false" else None})
        elif w in ("else", "elif") and stack:
            st = stack[-1]
            if st["false_from"] is not None:
                regions.append((st["false_from"], s))
                st["false_from"] = None
            if st["else"] is None:
                st["else"] = s
        elif w == "endif" and stack:
            st = stack.pop()
            if st["false_from"] is not None:
                regions.append((st["false_from"], s))
            if st["else"] is not None:
                regions.append((st["else"], e))
    return regions


def false_only(nc, dirs):
    stack, regions = [], []
    for w, s, e, cond in dirs:
        if w == "if":
            stack.append(e if cond == "false" else None)
        elif w in ("else", "elif") and stack:
            if stack[-1] is not None:
                regions.append((stack[-1], s))
                stack[-1] = None
        elif w == "endif" and stack:
            st = stack.pop()
            if st is not None:
                regions.append((st, s))
    return regions


def apply_regions(nc, cd, regions):
    for a, b in regions:
        nc = nc[:a] + blank(nc[a:b]) + nc[b:]
        cd = cd[:a] + blank(cd[a:b]) + cd[b:]
    return nc, cd


# --------------------------------------------------------------------------- parsing helpers
HDR_TOK = re.compile(r"[;{()\[\]=]")
ANY_TOK = re.compile(r"[;,(){}\[\]]")
NONWS = re.compile(r"\S")
BRACES = re.compile(r"[{}]")
BR_SQ = re.compile(r"[\[\]]")
DECL_COMMA = re.compile(r",\s*@?[A-Za-z_]\w*\s*(?:=(?![=>])|,|;)")
WS = re.compile(r"\s+")
IDENT = re.compile(r"@?[A-Za-z_]\w*")
TYPE_KW = re.compile(r"(class|struct|interface|enum|record(?:\s+(?:struct|class))?)\s+(@?[A-Za-z_]\w*)")
OPERATOR_RE = re.compile(
    r"\boperator\s*(?:(\+\+|--|<<|>>|[-+*/%&|^!~<>=]=?|true|false)|([\w.<>?\[\],\s]+?))\s*\(")


def collapse(s):
    return WS.sub(" ", s).strip()


class Ctx:
    __slots__ = ("rel", "nc", "cd", "bm", "nl", "lines", "ok")


def build_ctx(rel, text, drop_else):
    c = Ctx()
    c.rel = rel
    nc, cd, dirs = mask(text)
    nc, cd = apply_regions(nc, cd, drop_else_branches(nc, cd, dirs) if drop_else else false_only(nc, dirs))
    c.nc, c.cd = nc, cd
    bm, st, ok = {}, [], True
    for m in BRACES.finditer(cd):
        if m.group() == "{":
            st.append(m.start())
        elif st:
            a = st.pop()
            bm[a] = m.start()
        else:
            ok = False
    if st:
        ok = False
    c.bm, c.ok = bm, ok
    c.nl = [m.start() for m in re.finditer("\n", text)]
    c.lines = text.split("\n")
    return c


def line_of(c, pos):
    return bisect.bisect_left(c.nl, pos) + 1


def scan_header(cd, i, end):
    depth = 0
    for m in HDR_TOK.finditer(cd, i, end):
        ch, p = m.group(), m.start()
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth = max(0, depth - 1)
        elif depth == 0:
            if ch in ";{":
                return p, ch
            nxt = cd[p + 1:p + 2]
            if nxt == ">":
                return p, "=>"
            before = cd[i:p].rstrip()
            if before.endswith("operator") or (before and before[-1] in "=!<>") or nxt == "=":
                continue
            return p, "="
    return -1, ""


def match_bracket(cd, a, b):
    depth = 0
    for m in BR_SQ.finditer(cd, a, b):
        depth += 1 if m.group() == "[" else -1
        if depth == 0:
            return m.start()
    return -1


def skip_expr(cd, i, end):
    depth = 0
    for m in ANY_TOK.finditer(cd, i, end):
        ch = m.group()
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        elif depth <= 0:
            if ch == ";":
                return m.start(), ";"
            if ch == "," and DECL_COMMA.match(cd, m.start()):
                return m.start(), ","
    return end, ""


def split_top(cd, a, b, seps=","):
    out, depth, s = [], 0, a
    for m in re.finditer(r"[,()\[\]{}]", cd[a:b]):
        ch, p = m.group(), m.start() + a
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif depth == 0:
            out.append((s, p))
            s = p + 1
    out.append((s, b))
    return out


def doc_above(c, pos):
    """XML-doc / comment lines directly above the line containing pos (1-based line of pos)."""
    ln = line_of(c, pos) - 1
    out = []
    while ln >= 1:
        t = c.lines[ln - 1].strip()
        if t.startswith("///"):
            out.append(t[3:])
        elif t.startswith("#") or t == "":
            if out or t == "":
                break
        elif t.endswith("*/") or t.startswith("*") or t.startswith("/*"):
            break
        else:
            break
        ln -= 1
    if not out:
        return ""
    txt = " ".join(reversed(out))
    m = re.search(r"<summary>(.*?)</summary>", txt, re.S)
    if m:
        txt = m.group(1)
    elif "<inheritdoc" in txt:
        return "(inheritdoc)"
    txt = re.sub(r"<see\s+(?:cref|langword|href)=\"([^\"]*)\"\s*/?>", r"\1", txt)
    txt = re.sub(r"<(?:paramref|typeparamref)\s+name=\"([^\"]*)\"\s*/?>", r"\1", txt)
    txt = re.sub(r"<[^>]+>", " ", txt)
    txt = txt.replace("&lt;", "<").replace("&gt;", ">").replace("&amp;", "&")
    return collapse(txt)[:1000]

# --------------------------------------------------------------------------- declaration parser
CALL_NAME = re.compile(r"(@?[A-Za-z_]\w*)\s*(<[^()]*?>)?\s*$")


def angle_balance(s):
    d = 0
    for i, ch in enumerate(s):
        if ch == "<":
            d += 1
        elif ch == ">" and s[i - 1:i] != "=":
            d -= 1
    return d


def find_call(rest):
    """Locate the parameter-list paren of a method-like header. Returns (pos, name, name_start) or None."""
    for m in re.finditer(r"\(", rest):
        pos = m.start()
        pre = rest[:pos].rstrip()
        if not pre or not (pre[-1].isalnum() or pre[-1] in "_>"):
            continue
        if angle_balance(pre) != 0:
            continue
        k = len(pre)
        if pre[-1] == ">":
            d = 0
            while k > 0:
                k -= 1
                if pre[k] == ">":
                    d += 1
                elif pre[k] == "<":
                    d -= 1
                    if d == 0:
                        break
            if d != 0:
                continue
        im = re.search(r"@?[A-Za-z_]\w*$", pre[:k])
        if im and im.group() not in ("where", "new", "typeof", "default", "nameof"):
            if k < len(pre) and pre[k - 1:k] == " ":
                continue
            return pos, pre[im.start():], im.start()
    return None


def last_ident(h):
    ids = IDENT.findall(re.sub(r"<[^<>]*>", " ", h))
    return ids[-1] if ids else ""


def join_ns(a, b):
    return b if not a else a + "." + b


def accessors(c, a, b):
    out, depth = [], 0
    for m in re.finditer(r"[{}]|\b(?:get|set|init|add|remove)\b", c.cd[a + 1:b]):
        t = m.group()
        if t == "{":
            depth += 1
        elif t == "}":
            depth -= 1
        elif depth == 0 and t not in out:
            out.append(t)
    return out


class Parser:
    def __init__(self, c):
        self.c = c
        self.recs = []

    def add(self, **kw):
        self.recs.append(kw)
        return kw

    def region(self, i, end, ns, cont, owner):
        c, cd, nc = self.c, self.c.cd, self.c.nc
        while True:
            m = NONWS.search(cd, i, end)
            if not m:
                return
            i = m.start()
            if cd[i] in ";}":
                i += 1
                continue
            dstart = i
            attrs = []
            while cd[i] == "[":
                j = match_bracket(cd, i, end)
                if j < 0:
                    return
                attrs.append(collapse(nc[i:j + 1]))
                m = NONWS.search(cd, j + 1, end)
                if not m:
                    return
                i = m.start()
            p, ch = scan_header(cd, i, end)
            if p < 0:
                return
            hdr = collapse(nc[i:p])
            line = line_of(c, i)
            nxt = p + 1
            if not hdr:
                i = nxt
                continue
            if hdr.startswith("global "):
                hdr = hdr[7:]
            mm = MOD_RE.match(hdr)
            mods = hdr[:mm.end()].split()
            rest = hdr[mm.end():]
            access = " ".join(x for x in mods if x in ("public", "protected", "internal", "private"))
            implied = False
            doc = None

            def getdoc():
                return doc_above(c, dstart)

            if cont == "ns" and rest.startswith("namespace "):
                name = rest[10:].strip()
                if ch == "{":
                    close = c.bm.get(p)
                    if close is None:
                        return
                    self.region(p + 1, close, join_ns(ns, name), "ns", None)
                    i = close + 1
                else:
                    ns = join_ns(ns, name)
                    i = nxt
                continue
            if rest.startswith("using") and (len(rest) == 5 or not rest[5].isalnum()) or rest.startswith("extern alias"):
                if ch == ";":
                    i = nxt
                else:
                    e, _ = skip_expr(cd, p + 1, end)
                    i = e + 1
                continue
            tm = TYPE_KW.match(rest)
            if tm and cont != "enum":
                kw = tm.group(1)
                kw = "record struct" if kw.startswith("record") and "struct" in kw else (
                    "record" if kw.startswith("record") else kw)
                tname = tm.group(2)
                tail = rest[tm.end():]
                gen = ""
                if tail.startswith("<"):
                    k, d = 0, 0
                    for k, chh in enumerate(tail):
                        d += chh == "<"
                        d -= chh == ">"
                        if d == 0:
                            break
                    gen, tail = tail[:k + 1], tail[k + 1:]
                tail = tail.strip()
                rparams = ""
                if tail.startswith("(") and kw.startswith("record"):
                    d = 0
                    for k, chh in enumerate(tail):
                        d += chh == "("
                        d -= chh == ")"
                        if d == 0:
                            break
                    rparams, tail = tail[:k + 1], tail[k + 1:].strip()
                inh, cons = "", ""
                if tail.startswith(":"):
                    t2 = tail[1:]
                    wm = re.search(r"\swhere\s", " " + t2)
                    if wm:
                        inh, cons = t2[:max(wm.start() - 1, 0)].strip(), t2[max(wm.start() - 1, 0):].strip()
                    else:
                        inh = t2.strip()
                elif tail.startswith("where "):
                    cons = tail
                if not access:
                    access = "internal" if cont == "ns" else ("public" if cont == "interface" else "private")
                    implied = True
                q = join_ns(owner["q"] if owner else ns, tname)
                end_ln = line_of(c, c.bm.get(p, p)) if ch == "{" else line
                rec = self.add(kind=kw, name=tname + gen, bare=tname, scope=(owner["q"] if owner else ns), q=q,
                               access=access, implied=implied, mods=mods, sig=hdr, line=line, end=end_ln,
                               inherits=inh, constraints=cons, attrs=attrs, doc=getdoc(), owner=owner,
                               ns=ns, cont=kw.split()[0])
                if ch == "{":
                    close = c.bm.get(p)
                    if close is None:
                        return
                    if kw == "enum":
                        self.enum_body(p + 1, close, rec)
                    else:
                        self.region(p + 1, close, ns, kw.split()[0], rec)
                    i = close + 1
                else:
                    i = nxt
                continue
            if cont == "ns" and not rest.startswith("delegate "):
                if ch == "{":
                    close = c.bm.get(p)
                    if close is None:
                        return
                    nxt = close + 1
                elif ch in ("=", "=>"):
                    e, _ = skip_expr(cd, p + 1, end)
                    nxt = e + 1
                i = nxt
                continue
            if not access:
                access = "public" if cont == "interface" else "private"
                implied = True
            scope = owner["q"] if owner else ns
            tname = owner["bare"] if owner else ""
            base = dict(scope=scope, access=access, implied=implied, mods=mods, line=line, attrs=attrs,
                        owner=owner, ns=ns, cont=cont)
            if rest.startswith("delegate "):
                fc = find_call(rest)
                name = fc[1] if fc else last_ident(rest)
                self.add(kind="delegate", name=name, bare=re.sub(r"<.*", "", name), sig=hdr, end=line,
                         doc=getdoc(), **base)
                i = nxt if ch == ";" else (c.bm.get(p, p) + 1)
                continue
            body = None
            if ch == "{":
                close = c.bm.get(p)
                if close is None:
                    return
                body = (p, close)
                nxt = close + 1
            end_ln = line_of(c, nxt - 1) if body else line
            fc = None if rest.startswith("event ") else find_call(rest)
            om = OPERATOR_RE.search(rest) if "operator" in rest else None
            if om:
                nm = "operator " + (om.group(1) or om.group(2).strip())
                self.add(kind="operator", name=nm, bare=nm, sig=hdr, end=end_ln, doc=getdoc(), body=body, **base)
            elif rest.startswith("~") and fc:
                self.add(kind="dtor", name=fc[1], bare=fc[1], sig=hdr, end=end_ln, doc=getdoc(), body=body, **base)
            elif fc:
                pre = rest[:fc[2]].strip()
                kind = "ctor" if (not pre or fc[1].split("<")[0] == tname) and not rest.startswith("event") else "method"
                self.add(kind=kind, name=fc[1], bare=fc[1].split("<")[0], sig=hdr, end=end_ln, doc=getdoc(),
                         body=body, **base)
            elif rest.startswith("event "):
                parts = split_top(cd, i, p)
                names = []
                first = collapse(nc[parts[0][0]:parts[0][1]])
                names.append(last_ident(first))
                names += [collapse(nc[a:b]).split("=")[0].strip() for a, b in parts[1:]]
                prefix = hdr[:hdr.rfind(names[0])] if names[0] in hdr else ""
                for nm in names:
                    self.add(kind="event", name=nm, bare=nm, sig=(prefix + nm if nm != names[0] else hdr) +
                             (" " + "{ " + "; ".join(accessors(c, *body)) + "; }" if body else ""),
                             end=end_ln, doc=getdoc(), body=None, **base)
            elif re.search(r"\bthis\s*\[", rest) and not (ch == "=" and False):
                acc = accessors(c, *body) if body else []
                self.add(kind="indexer", name="this[]", bare="this", end=end_ln, doc=getdoc(), body=body,
                         sig=hdr + (" { " + "; ".join(acc) + "; }" if acc else ""), **base)
            elif ch in ("{", "=>") and not (ch == "=" ):
                acc = accessors(c, *body) if body else []
                nm = last_ident(hdr)
                self.add(kind="property", name=nm, bare=nm, end=end_ln, doc=getdoc(), body=body,
                         sig=hdr + (" { " + "; ".join(acc) + "; }" if acc else (" => ..." if ch == "=>" else "")),
                         **base)
            else:
                parts = split_top(cd, i, p)
                kind = "const" if "const" in mods else "field"
                first = collapse(nc[parts[0][0]:parts[0][1]])
                nm = last_ident(first)
                self.add(kind=kind, name=nm, bare=nm, sig=hdr + (" = ..." if ch == "=" else ""), end=end_ln,
                         doc=getdoc(), body=None, **base)
                typ = first[:first.rfind(nm)].strip() if nm in first else ""
                pre = hdr[:hdr.find(first)] if first in hdr else ""
                for a, b in parts[1:]:
                    nm2 = last_ident(collapse(nc[a:b]).split("=")[0])
                    if nm2:
                        self.add(kind=kind, name=nm2, bare=nm2, sig=f"{pre}{typ} {nm2}".strip(), end=end_ln,
                                 doc=getdoc(), body=None, **base)
            if ch == "=" and not fc and not om:
                e, t = skip_expr(cd, p + 1, end)
                init = collapse(nc[p + 1:e])
                if init:
                    for r in self.recs[-1:]:
                        if r["kind"] in ("field", "const") and r["line"] == line:
                            r["sig"] = r["sig"].replace(" = ...", "") + " = " + init[:200] + (" ..." if len(init) > 200 else "")
                while t == ",":
                    m3 = NONWS.search(cd, e + 1)
                    mi = IDENT.match(cd, m3.start()) if m3 else None
                    p2, ch2 = scan_header(cd, mi.end() if mi else e + 1, end)
                    if mi:
                        typ = hdr[:hdr.rfind(last_ident(hdr.split("=")[0]))].strip()
                        self.add(kind="const" if "const" in mods else "field", name=mi.group(), bare=mi.group(),
                                 sig=f"{typ} {mi.group()}".strip(), end=end_ln, doc=getdoc(), body=None, **base)
                    if ch2 == "=":
                        e, t = skip_expr(cd, p2 + 1, end)
                        if mi:
                            self.recs[-1]["sig"] += " = " + collapse(nc[p2 + 1:e])[:200]
                    else:
                        e, t = skip_expr(cd, mi.end() if mi else e + 1, end)
                nxt = e + 1
            elif ch in ("=", "=>"):
                e, _ = skip_expr(cd, p + 1, end)
                nxt = e + 1
            elif body and ch == "{":
                m2 = NONWS.search(cd, nxt, end)
                if m2 and cd[m2.start()] == "=" and cd[m2.start() + 1:m2.start() + 2] != ">":
                    e, _ = skip_expr(cd, m2.start() + 1, end)
                    nxt = e + 1
            i = nxt

    def enum_body(self, a, b, owner):
        c, cd, nc = self.c, self.c.cd, self.c.nc
        for s, e in split_top(cd, a, b):
            m = NONWS.search(cd, s, e)
            if not m:
                continue
            i = m.start()
            ds = i
            attrs = []
            while i < e and cd[i] == "[":
                j = match_bracket(cd, i, e)
                if j < 0:
                    break
                attrs.append(collapse(nc[i:j + 1]))
                m = NONWS.search(cd, j + 1, e)
                if not m:
                    i = e
                    break
                i = m.start()
            txt = collapse(nc[i:e])
            im = IDENT.match(txt)
            if not im:
                continue
            self.add(kind="enumerator", name=im.group(), bare=im.group(), scope=owner["q"], access="public",
                     implied=True, mods=[], sig=txt, line=line_of(c, i), end=line_of(c, i), attrs=attrs,
                     doc=doc_above(c, ds) or "", owner=owner, ns=owner["ns"], cont="enum", body=None)

# --------------------------------------------------------------------------- rules (Build.cs / Target.cs)
STMT_ASSIGN = re.compile(r"(?<![\w.@])([A-Za-z_]\w*(?:\s*\.\s*[A-Za-z_]\w*|\s*\[[^\]\n]*\])*)\s*(\+=|-=|\|=|&=|=)(?![=>])")
STMT_CALL = re.compile(r"(?<![\w.@])([A-Za-z_]\w*(?:\s*\.\s*[A-Za-z_]\w*)*)\s*(?:<[^<>()]*>)?\s*\(")
LIT = re.compile(r'"((?:[^"\\\n]|\\.)*)"')
KEYWORDS = {"if", "for", "foreach", "while", "switch", "using", "lock", "return", "catch", "fixed", "nameof",
            "typeof", "new", "else", "base", "this", "throw", "sizeof", "default", "checked", "unchecked", "var",
            "string", "int", "bool", "float", "double", "long", "object", "void", "await", "yield", "do", "try",
            "foreach", "when", "where", "select", "from", "in"}
LIST_PROPS = re.compile(r"(?:Dependency|IncludePath)ModuleNames$|DynamicallyLoadedModuleNames$|ExtraModuleNames$|"
                        r"^(?:Public|Private)(?:System)?(?:IncludePaths|Definitions|Libraries|SystemLibraries|"
                        r"SystemLibraryPaths|Frameworks|WeakFrameworks|AdditionalLibraries|DelayLoadDLLs|"
                        r"AdditionalShadowVariables)$|^(?:Runtime|Public|Private)?(?:Dependencies|AdditionalPropertiesForReceipt)$|"
                        r"^(?:Global|Additional)\w*(?:Definitions|Modules|Plugins)$|^(?:Enable|Disable)Plugins$")


def stmt_prev(cd, pos):
    j = pos - 1
    while j >= 0 and cd[j] in " \t\r\n":
        j -= 1
    return j


def enclosing_cond(blocks, pos, lo):
    conds = []
    for a, b, h in blocks:
        if lo < a < pos < b and h:
            conds.append(h)
    return " && ".join(conds)


def collect_blocks(c, lo, hi):
    cd, nc = c.cd, c.nc
    blocks = []
    for a, b in c.bm.items():
        if lo < a and b < hi:
            k = a - 1
            while k > lo and cd[k] not in ";{}":
                k -= 1
            h = collapse(nc[k + 1:a])
            if h.startswith("else if"):
                h = h
            if re.match(r"(if|else|foreach|for|while|switch|case|default|using|lock|try|catch|finally|unless)\b", h):
                blocks.append((a, b, h[:160]))
    blocks.sort()
    return blocks


def rules_statements(c, lo, hi):
    """Statements inside [lo,hi) of a rules constructor: (kind, target, op, literals, expr, line, cond)."""
    cd, nc = c.cd, c.nc
    blocks = collect_blocks(c, lo, hi)
    out, seen = [], set()
    hits = []
    for m in STMT_ASSIGN.finditer(cd, lo, hi):
        hits.append((m.start(), "assign", m))
    for m in STMT_CALL.finditer(cd, lo, hi):
        hits.append((m.start(), "call", m))
    hits.sort(key=lambda x: x[0])
    for pos, typ, m in hits:
        j = stmt_prev(cd, pos)
        prevc = cd[j] if j >= lo else ";"
        inline = ""
        if prevc == ")":
            d, k = 0, j
            while k > lo:
                if cd[k] == ")":
                    d += 1
                elif cd[k] == "(":
                    d -= 1
                    if d == 0:
                        break
                k -= 1
            w = re.search(r"(\w+)\s*$", cd[lo:k])
            if w and w.group(1) in ("if", "foreach", "for", "while", "using", "lock"):
                inline = collapse(nc[k - len(w.group(1)):j + 1])
            else:
                continue
        elif prevc not in ";{}" and not cd[max(lo, j - 3):j + 1].endswith("else"):
            continue
        if pos in seen:
            continue
        name = collapse(m.group(1)).replace(" ", "")
        if name.split(".")[0] in KEYWORDS and typ == "call":
            continue
        if typ == "assign":
            e, _ = skip_expr(cd, m.end(), hi)
            expr = collapse(nc[m.end():e])
            seen.add(pos)
            kind = "assign"
            op = m.group(2)
        else:
            d, k = 0, m.end() - 1
            for mm in re.finditer(r"[()]", cd[k:hi]):
                d += 1 if mm.group() == "(" else -1
                if d == 0:
                    k = k + mm.start()
                    break
            else:
                continue
            expr = collapse(nc[m.end():k])
            seen.add(pos)
            kind = "call"
            op = ""
        cond = enclosing_cond(blocks, pos, lo)
        if inline:
            cond = (cond + " && " if cond else "") + inline
        lits = LIT.findall(expr)
        out.append(dict(kind=kind, target=name, op=op, lits=lits, expr=expr[:600], line=line_of(c, pos), cond=cond[:300]))
    return out


def parse_rules_ctx(c, recs):
    """Return list of rule classes: {name, base, line, ctors:[{sig,line,stmts}], ...}."""
    res = []
    for r in recs:
        if r["kind"] != "class":
            continue
        inh = r.get("inherits", "")
        base = inh.split(",")[0].strip() if inh else ""
        ctors = []
        for q in recs:
            if q["kind"] == "ctor" and q.get("owner") is r and q.get("body"):
                a, b = q["body"]
                ctors.append(dict(sig=q["sig"], line=q["line"], stmts=rules_statements(c, a, b)))
        stray = []
        for q in recs:
            if q["kind"] in ("method",) and q.get("owner") is r and q.get("body"):
                a, b = q["body"]
                st = rules_statements(c, a, b)
                if st:
                    stray.append(dict(sig=q["sig"], line=q["line"], stmts=st))
        res.append(dict(name=r["bare"], q=r["q"], base=base, line=r["line"], end=r["end"], sig=r["sig"],
                        attrs=r["attrs"], ctors=ctors, methods=stray))
    return res


def parse_rules_file(path, rel=None):
    text = open(path, encoding="utf-8", errors="replace").read().lstrip("\ufeff").replace("\r\n", "\n").replace("\r", "\n")
    c = build_ctx(rel or path, text, False)
    if not c.ok:
        c = build_ctx(rel or path, text, True)
    p = Parser(c)
    p.region(0, len(c.cd), "", "ns", None)
    return parse_rules_ctx(c, p.recs)


def merged_lists(stmts):
    """{prop: {"always":[names], "cond":[(cond,[names])]}} for list-like Add/AddRange/+= statements."""
    d = defaultdict(lambda: {"always": [], "cond": []})
    for s in stmts:
        t = s["target"].split(".")
        if s["kind"] == "call" and len(t) >= 2 and t[-1] in ("Add", "AddRange", "Remove"):
            prop = t[-2]
            if t[-1] == "Remove":
                continue
        elif s["kind"] == "assign" and s["op"] == "+=":
            prop = t[-1]
        elif s["kind"] == "call" and t[-1].startswith("AddEngineThirdParty"):
            prop = "@" + t[-1]
        else:
            continue
        if s["kind"] == "call" and t[-1].startswith("AddEngineThirdParty"):
            names = [x for x in s["lits"]]
        else:
            names = s["lits"] if s["lits"] else [s["expr"][:80]]
        if s["cond"]:
            d[prop]["cond"].append((s["cond"], names))
        else:
            d[prop]["always"] += names
    return d

# --------------------------------------------------------------------------- rendering
def esc(s):
    return s.replace("`", "'")


ACC = {"public", "protected", "internal", "private"}


def fmt_member(r):
    acc = r["access"] + ("*" if r["implied"] else "")
    other = " ".join(m for m in r["mods"] if m not in ACC)
    sig = r["sig"]
    ln = f"- L{r['line']}" + (f"-{r['end']}" if r["end"] > r["line"] else "") + f" _{acc} {r['kind']}_ `{esc(sig)}`"
    if r["attrs"]:
        ln += " — attrs: `" + esc(" ".join(r["attrs"])[:240]) + "`"
    if r["doc"]:
        ln += f" — {r['doc']}"
    return ln


def render_file(rel, label, recs, out):
    out.append(f"\n### `{rel}` ({label})\n")
    types = [r for r in recs if r["kind"] in ("class", "struct", "interface", "enum", "record", "record struct")]
    members = defaultdict(list)
    free = []
    for r in recs:
        if r["kind"] in ("class", "struct", "interface", "enum", "record", "record struct"):
            continue
        (members[id(r["owner"])] if r["owner"] is not None else free).append(r)
    for t in types:
        acc = t["access"] + ("*" if t["implied"] else "")
        out.append(f"\n#### {t['kind']} `{esc(t['q'])}`  \n`{esc(t['sig'])}`  \n_{acc}; L{t['line']}-{t['end']}_")
        if t["attrs"]:
            out.append("- attrs: `" + esc(" ".join(t["attrs"])[:400]) + "`")
        if t["inherits"]:
            out.append(f"- inherits: `{esc(t['inherits'])}`")
        if t["constraints"]:
            out.append(f"- constraints: `{esc(t['constraints'])}`")
        if t["doc"]:
            out.append(f"- desc: {t['doc']}")
        for m in members.get(id(t), []):
            out.append(fmt_member(m))
    if free:
        out.append("\n#### Namespace-level symbols\n")
        for m in free:
            out.append(fmt_member(m))


def render_rules(rel, label, rules, out):
    out.append(f"\n### `{rel}` ({label})\n")
    if not rules:
        out.append("_(no rules class parsed)_")
        return
    for r in rules:
        out.append(f"\n#### class `{esc(r['name'])}` : `{esc(r['base'])}`  \n`{esc(r['sig'])}`  \n_L{r['line']}-{r['end']}_")
        if r["attrs"]:
            out.append("- attrs: `" + esc(" ".join(r["attrs"])[:300]) + "`")
        for ct in r["ctors"] + r["methods"]:
            kind = "ctor" if ct in r["ctors"] else "method"
            out.append(f"- L{ct['line']} _{kind}_ `{esc(ct['sig'])}`")
            ml = merged_lists(ct["stmts"])
            for prop in sorted(ml):
                v = ml[prop]
                if v["always"]:
                    out.append(f"  - **{prop}**: {', '.join(v['always'])}")
                for cond, names in v["cond"]:
                    out.append(f"  - **{prop}** [`{esc(cond)}`]: {', '.join(names)}")
            for s in ct["stmts"]:
                if s["kind"] == "assign" and s["op"] == "+=" or (s["kind"] == "call" and re.search(r"\.(Add|AddRange)$", s["target"]) and
                                                               not s["target"].startswith(("Target", "Log"))
                                                               and any(s["target"].split(".")[-2:-1] == [p] for p in ml)):
                    continue
                cond = f" [`{esc(s['cond'])}`]" if s["cond"] else ""
                if s["kind"] == "assign":
                    out.append(f"  - L{s['line']}{cond} `{esc(s['target'])} {s['op']} {esc(s['expr'][:300])}`")
                else:
                    out.append(f"  - L{s['line']}{cond} call `{esc(s['target'])}({esc(s['expr'][:300])})`")

# --------------------------------------------------------------------------- ctags cross-check / fallback
CT_KINDS = "cdeEfgimnpst"
CT_TYPES = {"class": "class", "struct": "struct", "interface": "interface", "enum": "enum"}


def run_ctags(engine, files):
    if not files:
        return {}
    cmd = ["ctags", "-f", "-", "--output-format=json", "--sort=no", "--fields=+SaitKzne",
           f"--kinds-C#=+{CT_KINDS}", "--language-force=C#", "-L", "-"]
    p = subprocess.run(cmd, input="\n".join(os.path.join(engine, f) for f in files), text=True,
                       capture_output=True, errors="replace")
    by = defaultdict(list)
    pre = engine.rstrip("/") + "/"
    for ln in p.stdout.splitlines():
        if ln.startswith("{"):
            try:
                t = json.loads(ln)
            except json.JSONDecodeError:
                continue
            if t.get("kind") in (None, "local", "macro"):
                continue
            by[t["path"][len(pre):] if t["path"].startswith(pre) else t["path"]].append(t)
    return by


def ctags_fallback(c, tags):
    recs = []
    for t in tags:
        ln = int(t.get("line", 0) or 0)
        if ln < 1 or ln > len(c.lines):
            continue
        kind = {"enumerator": "enumerator", "namespace": "namespace", "typedef": "delegate"}.get(t["kind"], t["kind"])
        if kind == "namespace":
            continue
        src = collapse(c.lines[ln - 1])
        acc = t.get("access", "")
        recs.append(dict(kind=kind, name=t["name"], bare=t["name"], scope=t.get("scope", ""), q=(t.get("scope", "") + "." if t.get("scope") else "") + t["name"],
                         access=acc or "?", implied=not acc, mods=[], sig=src + " (ctags fallback)", line=ln,
                         end=int(t.get("end", ln) or ln), inherits=t.get("inherits", ""), constraints="", attrs=[],
                         doc="", owner=None, ns="", cont="", body=None))
    return recs


def parse_file(engine, rel, ct_tags):
    """Return (recs, ctx, mode)."""
    path = os.path.join(engine, rel)
    text = open(path, encoding="utf-8", errors="replace").read().lstrip("\ufeff").replace("\r\n", "\n").replace("\r", "\n")
    for drop in (False, True):
        try:
            c = build_ctx(rel, text, drop)
            if not c.ok:
                continue
            p = Parser(c)
            p.region(0, len(c.cd), "", "ns", None)
            return p.recs, c, ("ok" if not drop else "ok-else-dropped")
        except Exception as ex:  # noqa
            err = repr(ex)
    c = build_ctx(rel, text, False)
    return ctags_fallback(c, ct_tags), c, "ctags-fallback"


def ct_expected(tags):
    s = set()
    for t in tags:
        k = t.get("kind")
        if k in ("class", "struct", "interface", "enum", "method", "property", "event", "enumerator"):
            s.add((k, t["name"], int(t.get("line", 0) or 0)))
    return s


# --------------------------------------------------------------------------- group worker
def process_group(args):
    (label, gdir, files), engine, outdir, is_rules = args
    ct = run_ctags(engine, files)
    parts, cur, size = [], [], 0
    tsv = []
    stat = Counter()
    fails, modes, missing = [], Counter(), []
    rules_out = []
    ct_total = ct_hit = 0
    for rel in sorted(files):
        try:
            recs, c, mode = parse_file(engine, rel, ct.get(rel, []))
        except Exception as ex:  # noqa
            fails.append((rel, repr(ex)))
            cur.append(f"\n### `{rel}` ({label})\n_(parse failure: {esc(repr(ex))})_\n")
            continue
        modes[mode] += 1
        if mode == "ctags-fallback":
            fails.append((rel, "unbalanced braces/parser exception; ctags fallback used"))
        buf = []
        if is_rules:
            try:
                rules = parse_rules_ctx(c, recs) if mode != "ctags-fallback" else []
            except Exception as ex:  # noqa
                rules, fails = [], fails + [(rel, "rules: " + repr(ex))]
            render_rules(rel, label, rules, buf)
            for r in rules:
                rules_out.append(dict(file=rel, name=r["name"], base=r["base"], line=r["line"],
                                      ctors=[dict(sig=x["sig"], line=x["line"], stmts=x["stmts"]) for x in r["ctors"] + r["methods"]]))
        elif recs:
            render_file(rel, label, recs, buf)
        else:
            buf.append(f"\n### `{rel}` ({label})\n_(no declarations)_\n")
        have = {(r["kind"] if r["kind"] not in ("ctor", "dtor", "operator", "indexer", "record", "record struct", "delegate", "const") else
                 {"ctor": "method", "dtor": "method", "operator": "method", "indexer": "property", "record": "method",
                  "record struct": "method", "delegate": "method", "const": "field"}[r["kind"]], r["bare"], r["line"]) for r in recs}
        have_names = {(r["bare"], r["line"]) for r in recs}
        for k, n, ln in ct_expected(ct.get(rel, [])):
            n = n.lstrip("~")
            ct_total += 1
            if (n, ln) in have_names or (k, n, ln) in have or (n.split("<")[0], ln) in have_names:
                ct_hit += 1
            else:
                missing.append((rel, ln, k, n))
        for r in recs:
            stat[r["kind"]] += 1
            tsv.append("\t".join([rel, str(r["line"]), r["kind"], r["scope"], r["bare"], r["access"]]))
        text = "\n".join(buf) + "\n"
        if size + len(text) > PART_LIMIT and cur:
            parts.append("".join(cur))
            cur, size = [], 0
        cur.append(text)
        size += len(text)
    if cur:
        parts.append("".join(cur))
    odir = Path(outdir) / "api" / "CSharp"
    odir.mkdir(parents=True, exist_ok=True)
    names = []
    for pi, body in enumerate(parts, 1):
        fn = f"{label}.md" if len(parts) == 1 else f"{label}.part{pi:02d}.md"
        head = [f"# CSharp / {label}" + (f" (part {pi}/{len(parts)})" if len(parts) > 1 else ""), ""]
        if pi == 1:
            head.append(f"- project root: `{gdir or '-'}`")
            head.append(f"- files: {len(files)}; symbols: {sum(stat.values())}")
            head.append("- symbol kinds: " + ", ".join(f"{k}={v}" for k, v in sorted(stat.items())))
            head.append("- access marked `*` is implicit (not written in source)")
            head.append("")
        (odir / fn).write_text("\n".join(head) + body, encoding="utf-8")
        names.append(fn)
    with gzip.open(Path(outdir) / "index" / f"CSharp__{label}.tsv.gz", "wt", encoding="utf-8") as g:
        g.write("\n".join(tsv) + ("\n" if tsv else ""))
    return dict(label=label, root=gdir, files=len(files), symbols=sum(stat.values()), stat=dict(stat),
                outputs=names, fails=fails, modes=dict(modes), ct_total=ct_total, ct_hit=ct_hit,
                ct_missing=missing[:200], ct_missing_n=len(missing), rules=rules_out,
                file_list=sorted(files))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--engine", default=ENGINE)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--jobs", type=int, default=14)
    ap.add_argument("--only", default="", help="substring filter on group label (debug)")
    a = ap.parse_args()
    engine, out = a.engine, a.out
    (Path(out) / "index").mkdir(parents=True, exist_ok=True)
    files = find_cs(engine)
    groups = defaultdict(list)
    meta = {}
    for rel in files:
        lab, d = group_of(engine, rel)
        groups[(lab, d)].append(rel)
    byname = defaultdict(list)
    for (lab, d) in groups:
        byname[lab].append(d)
    jobs = []
    for (lab, d), fl in groups.items():
        name = lab
        if len(byname[lab]) > 1:
            name = lab + "__" + (re.sub(r"[^A-Za-z0-9]+", "_", d).strip("_")[-60:] or "root")
        if a.only and a.only not in name:
            continue
        is_rules = lab in ("ModuleRules", "TargetRules")
        jobs.append(((name, d, fl), engine, out, is_rules))
    jobs.sort(key=lambda j: -len(j[0][2]))
    results = []
    with Pool(a.jobs) as pool:
        for i, res in enumerate(pool.imap_unordered(process_group, jobs, chunksize=1), 1):
            results.append(res)
            if i % 20 == 0:
                print(f"[{i}/{len(jobs)}]", file=sys.stderr)
    results.sort(key=lambda r: r["label"])
    rules = []
    for r in results:
        rules += r.pop("rules")
    with gzip.open(Path(out) / "index" / "csharp_rules.json.gz", "wt", encoding="utf-8") as g:
        json.dump(rules, g)
    allfiles = [f for r in results for f in r["file_list"]]
    summary = dict(total_files=len(allfiles), total_symbols=sum(r["symbols"] for r in results), groups=[
        {k: v for k, v in r.items() if k != "file_list"} for r in results])
    (Path(out) / "csharp_files.json").write_text(json.dumps(sorted(allfiles)), encoding="utf-8")
    (Path(out) / "csharp_summary.json").write_text(json.dumps(summary, indent=1), encoding="utf-8")
    ft = sum(r["ct_total"] for r in results)
    fh = sum(r["ct_hit"] for r in results)
    nf = sum(len(r["fails"]) for r in results)
    print(json.dumps(dict(files=len(allfiles), symbols=summary["total_symbols"], groups=len(results),
                          ctags_names=ft, ctags_hit=fh, parse_failures=nf)))


if __name__ == "__main__":
    main()




