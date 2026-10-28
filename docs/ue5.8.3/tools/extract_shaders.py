#!/usr/bin/env python3
"""Exhaustive HLSL (.usf/.ush) declaration extractor for Engine/Shaders and Engine/{Plugins,Platforms}/**/Shaders.

For every shader source file it records #include / #define / #pragma, struct / enum / cbuffer (with members),
functions and prototypes, global parameters / resources / groupshared / static const, typedefs, top-level macro
invocations and entry points.  Every record carries its line number and the active #if condition.
Entry points are detected from attributes ([numthreads]/[shader(..)]/[NodeLaunch]/...), from entry-point macros
(RAY_TRACING_ENTRY_*), and from the C++ side: every IMPLEMENT_*(...) call that names a virtual shader path plus an
entry function is resolved back to the file (so the C++ shader class / frequency / file:line is shown next to it).
Shared C/HLSL headers in Engine/Shaders/**.h are included too (extract_api.py does not walk Engine/Shaders).

Outputs:  api/Shaders/<dir>.md (split at 3 MB), index/shaders.tsv.gz, shaders_summary.json, api/Shaders/_REPORT.md
TSV columns: path, line, kind, scope, name, visibility, info (stage for entries / condition otherwise).
"""
import argparse
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
SKIP_DIRS = {"Intermediate", "Binaries", ".git", "Saved"}
SHADER_EXT = (".usf", ".ush")
PART_LIMIT = 3 * 1024 * 1024
ENTRY_ATTRS = ("numthreads", "shader", "nodelaunch", "maxvertexcount", "outputtopology", "domain",
               "patchconstantfunc", "earlydepthstencil", "outputcontrolpoints", "partitioning", "wavesize")
RESOURCE_RE = re.compile(r"\b(?:RW|RasterizerOrdered|Globallycoherent\s+)?(?:Texture\w*|Buffer|StructuredBuffer|"
                         r"ByteAddressBuffer|AppendStructuredBuffer|ConsumeStructuredBuffer|SamplerState|"
                         r"SamplerComparisonState|ConstantBuffer|RaytracingAccelerationStructure|FeedbackTexture\w*|"
                         r"TextureCube\w*|Texture2DMS\w*|RWByteAddressBuffer|RWStructuredBuffer|RWBuffer|RWTexture\w*)\b")
STAGE_BY_SUFFIX = [("RGS", "RayGen"), ("CHS", "ClosestHit"), ("AHS", "AnyHit"), ("CS", "Compute"), ("PS", "Pixel"),
                   ("VS", "Vertex"), ("GS", "Geometry"), ("HS", "Hull"), ("DS", "Domain"), ("MS", "Mesh"),
                   ("AS", "Amplification")]
KEYWORDS = {"if", "for", "while", "switch", "return", "do", "else", "sizeof", "case"}


# --------------------------------------------------------------------------- discovery
def find_shader_files(engine):
    out = []
    for top in ("Shaders", "Plugins", "Platforms", "Source"):
        base = os.path.join(engine, top)
        for dp, dns, fns in os.walk(base):
            dns[:] = sorted(d for d in dns if d not in SKIP_DIRS)
            rel_dp = os.path.relpath(dp, engine)
            for fn in fns:
                if fn.endswith(SHADER_EXT):
                    out.append(os.path.join(rel_dp, fn))
                elif top == "Shaders" and fn.endswith(".h"):
                    out.append(os.path.join(rel_dp, fn))
    return sorted(out)


def group_of(rel):
    return re.sub(r"[^A-Za-z0-9_.-]+", "__", os.path.dirname(rel)).strip("_") or "root"


def visibility_of(rel):
    parts = rel.split("/")
    for p in parts[1:-1]:
        if p in ("Public", "Private", "Shared", "Internal", "Generated"):
            return p
    return "Other"


# --------------------------------------------------------------------------- lexical masking
def mask(text):
    """Return (nc, cd): nc = comments blanked; cd = comments and string/char literal contents blanked.
    Newlines are always preserved so offsets/lines stay aligned with the original text."""
    nc = list(text)
    cd = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = i
            while True:
                j = text.find("\n", j)
                if j < 0:
                    j = n
                    break
                if text[j - 1] == "\\":
                    j += 1
                    continue
                break
            for k in range(i, j):
                if text[k] != "\n":
                    nc[k] = cd[k] = " "
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if text[k] != "\n":
                    nc[k] = cd[k] = " "
            i = j
        elif c == '"' or (c == "'" and i + 2 < n and (text[i + 2] == "'" or text[i + 1] == "\\")):
            q = c
            j = i + 1
            while j < n and text[j] != q and text[j] != "\n":
                if text[j] == "\\":
                    j += 1
                j += 1
            for k in range(i + 1, min(j, n)):
                if text[k] != "\n":
                    cd[k] = " "
            i = j + 1
        else:
            i += 1
    return "".join(nc), "".join(cd)


def line_starts(text):
    st = [0]
    for m in re.finditer("\n", text):
        st.append(m.end())
    return st


def lineno(starts, pos):
    lo, hi = 0, len(starts)
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        if starts[mid] <= pos:
            lo = mid
        else:
            hi = mid
    return lo + 1


def collapse(s):
    return re.sub(r"\s+", " ", s).strip()


# --------------------------------------------------------------------------- preprocessor pass
class PP:
    """Directive records + per-line #if condition + list of (line range, branch index) for fallback masking."""

    def __init__(self, nc_lines, raw_lines):
        self.records = []
        self.cond = [""] * (len(nc_lines) + 2)
        self.directive_lines = set()
        self.else_lines = set()      # lines inside a non-first branch of some #if
        self.first_lines = set()     # lines inside a first branch that has an #else/#elif sibling
        self.errors = []
        self.groups = []             # every #if group (innermost first): list of branches, each a list of lines
        stack = []                   # frames: dict(conds=[...], branch=int, start=line, lines=[[...], ...])
        i, n = 0, len(nc_lines)
        while i < n:
            ln = i + 1
            line = nc_lines[i]
            st = line.lstrip()
            if not st.startswith("#"):
                self.cond[ln] = self._cond_str(stack)
                for fr in stack:
                    fr["lines"][-1].append(ln)
                i += 1
                continue
            j = i
            parts = [line]
            raw = [raw_lines[i]]
            while parts[-1].rstrip().endswith("\\") and j + 1 < n:
                j += 1
                parts.append(nc_lines[j])
                raw.append(raw_lines[j])
            for k in range(i + 1, j + 2):
                self.directive_lines.add(k)
                self.cond[k] = self._cond_str(stack)
            body = collapse(" ".join(p.rstrip().rstrip("\\") for p in parts).strip()[1:])
            m = re.match(r"(\w+)\s*(.*)", body)
            d, rest = (m.group(1), m.group(2)) if m else ("", body)
            if d in ("if", "ifdef", "ifndef"):
                c = rest if d == "if" else (f"defined({rest})" if d == "ifdef" else f"!defined({rest})")
                stack.append(dict(conds=[c], branch=0, start=ln, lines=[[]]))
                self.records.append(("pp_if", ln, d, rest))
            elif d in ("elif", "else"):
                if not stack:
                    self.errors.append(f"L{ln}: #{d} without #if")
                else:
                    fr = stack[-1]
                    fr["branch"] += 1
                    fr["conds"].append(rest if d == "elif" else "")
                    fr["lines"].append([])
            elif d == "endif":
                if not stack:
                    self.errors.append(f"L{ln}: #endif without #if")
                else:
                    fr = stack.pop()
                    self.groups.append([list(b) for b in fr["lines"]])
                    if len(fr["lines"]) > 1:
                        self.first_lines.update(fr["lines"][0])
                        for br in fr["lines"][1:]:
                            self.else_lines.update(br)
                    for outer in stack:
                        for br in fr["lines"]:
                            outer["lines"][-1].extend(br)
            elif d == "include":
                rawtxt = " ".join(raw)
                mm = re.search(r'#\s*include\s*["<]([^">]+)[">]', rawtxt)
                self.records.append(("include", ln, mm.group(1) if mm else rest, self.cond[ln]))
            elif d == "define":
                mm = re.match(r"(\w+)(\([^)]*\))?\s*(.*)", rest)
                if mm:
                    self.records.append(("define", ln, mm.group(1), (mm.group(2) or "", mm.group(3)), self.cond[ln],
                                         j - i + 1))
                else:
                    self.records.append(("define", ln, rest[:60], ("", ""), self.cond[ln], j - i + 1))
            elif d == "undef":
                self.records.append(("undef", ln, rest, self.cond[ln]))
            elif d == "pragma":
                self.records.append(("pragma", ln, rest, self.cond[ln]))
            elif d in ("error", "warning", "line", ""):
                pass
            else:
                self.records.append(("pp_other", ln, d, rest))
            i = j + 1
        if stack:
            self.errors.append(f"{len(stack)} unterminated #if (first at L{stack[0]['start']})")

    @staticmethod
    def _cond_str(stack):
        out = []
        for fr in stack:
            cs = fr["conds"]
            if len(cs) == 1:
                out.append(cs[0])
            else:
                neg = " && ".join(f"!({c})" for c in cs[:-1] if c)
                cur = cs[-1]
                out.append((neg + (" && " + cur if cur else "")) if neg else cur or "else")
        s = " && ".join(x for x in out if x)
        return s if len(s) <= 200 else s[:197] + "..."


# --------------------------------------------------------------------------- declaration parser
def match_close(cd, i, open_c, close_c, limit=None):
    """cd[i] == open_c; return index of the matching close or -1."""
    d = 0
    n = len(cd) if limit is None else limit
    pairs = {"(": ")", "[": "]", "{": "}"}
    j = i
    while j < n:
        c = cd[j]
        if c == open_c:
            d += 1
        elif c == close_c:
            d -= 1
            if d == 0:
                return j
        j += 1
    return -1


def balanced(cd):
    d = {"(": 0, "{": 0, "[": 0}
    close = {")": "(", "}": "{", "]": "["}
    for c in cd:
        if c in d:
            d[c] += 1
        elif c in close:
            d[close[c]] -= 1
            if d[close[c]] < 0:
                return False
    return all(v == 0 for v in d.values())


def split_top(s, sep=","):
    out, d, cur = [], 0, []
    for c in s:
        if c in "([{<" and not (c == "<" and False):
            d += 1 if c != "<" else 0
        if c in ")]}":
            d -= 1
        if c == sep and d == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(c)
    out.append("".join(cur))
    return out


ATTR_LEAD_RE = re.compile(r"\s*(\[\[?)")
IDENT_RE = re.compile(r"[A-Za-z_]\w*")


def strip_attrs(h):
    """Split leading [attr(...)] / [[vk::x]] groups from header h. Returns (attrs, rest, offset_of_rest)."""
    attrs, off = [], 0
    while True:
        m = ATTR_LEAD_RE.match(h, off)
        if not m:
            break
        a = m.start(1)
        e = match_close(h, a, "[", "]")
        if e < 0:
            break
        attrs.append(collapse(h[a:e + 1]))
        off = e + 1
    return attrs, h[off:], off


def parse_attr(a):
    m = re.match(r"\[\[?\s*([\w:]+)\s*(?:\((.*)\))?", a, re.S)
    return (m.group(1).lower(), collapse(m.group(2) or "")) if m else ("", "")


def decl_name(stmt):
    """Name of a variable/member declarator: last identifier before [..] / : semantic / = init / register."""
    s = stmt
    d = 0
    cut = len(s)
    for i, c in enumerate(s):
        if c in "(<[{":
            d += 1
        elif c in ")>]}":
            d -= 1
        elif d == 0 and (c == "=" or (c == ":" and s[i:i + 2] != "::" and s[i - 1:i + 1] != "::")):
            cut = i
            break
    head = s[:cut]
    head = re.sub(r"\[[^\]]*\]\s*$", "", head.rstrip())
    while re.search(r"\[[^\]]*\]\s*$", head):
        head = re.sub(r"\[[^\]]*\]\s*$", "", head.rstrip())
    ids = IDENT_RE.findall(head)
    return ids[-1] if ids else ""


def classify_var(text):
    t = collapse(text)
    if re.match(r"(?:static\s+)?groupshared\b", t):
        return "groupshared"
    if re.match(r"(?:static\s+)?(?:const\s+)?static\s+const\b|static\s+const\b|const\s+static\b", t):
        return "static_const"
    if re.match(r"static\b", t):
        return "static_var"
    if RESOURCE_RE.search(t.split("=")[0]):
        return "resource"
    return "parameter"


class Decl:
    __slots__ = ("kind", "name", "scope", "line", "end", "text", "doc", "cond", "attrs", "extra", "members")

    def __init__(self, kind, name, scope, line, end, text, doc="", cond="", attrs=None, extra="", members=None):
        self.kind, self.name, self.scope, self.line, self.end = kind, name, scope, line, end
        self.text, self.doc, self.cond, self.attrs, self.extra = text, doc, cond, attrs or [], extra
        self.members = members if members is not None else []


class FileParser:
    def __init__(self, text, force=None):
        self.text = text
        nc, cd = mask(text)
        self.raw_lines = text.split("\n")
        self.nc_lines = nc.split("\n")
        self.pp = PP(self.nc_lines, self.raw_lines)
        self.starts = line_starts(text)
        # blank directive lines in code views
        nl, cl = nc.split("\n"), cd.split("\n")
        for ln in self.pp.directive_lines:
            nl[ln - 1] = " " * len(nl[ln - 1])
            cl[ln - 1] = " " * len(cl[ln - 1])
        self.nc = "\n".join(nl)
        self.cd_all = "\n".join(cl)
        self.mode = "all-branches"
        self.cd = self.cd_all
        if force is None and not balanced(self.cd_all):
            sm = self.smart_view(cl)
            if sm is not None:
                self.cd, self.mode = sm, "per-group"
                force = "done"
        if force == "done":
            pass
        elif force is not None or not balanced(self.cd_all):
            cl2 = list(cl)
            for ln in self.pp.else_lines:
                if ln - 1 < len(cl2):
                    cl2[ln - 1] = " " * len(cl2[ln - 1])
            cd2 = "\n".join(cl2)
            if force == "first-branch" or (force is None and balanced(cd2)):
                self.cd, self.mode = cd2, "first-branch"
            else:
                cl3 = list(cl)
                for ln in self.pp.first_lines:
                    if ln - 1 < len(cl3):
                        cl3[ln - 1] = " " * len(cl3[ln - 1])
                cd3 = "\n".join(cl3)
                if force == "last-branch" or (force is None and balanced(cd3)):
                    self.cd, self.mode = cd3, "last-branch"
                else:
                    self.cd, self.mode = cd2, "unbalanced"
        self.decls = []
        self.errors = list(self.pp.errors)

    def smart_view(self, cl):
        """Blank only the non-first branches of #if groups whose branches are not individually brace-balanced."""
        lines = list(cl)

        def delta(br):
            d = 0
            for ln in br:
                t = lines[ln - 1]
                d += t.count("{") - t.count("}")
            return d

        for g in self.pp.groups:
            if len(g) < 2:
                continue
            uniq = [sorted(set(b)) for b in g]
            if all(delta(b) == 0 for b in uniq):
                continue
            keep = 0
            for k, b in enumerate(uniq):
                if b:
                    keep = k
                    break
            for k, b in enumerate(uniq):
                if k != keep:
                    for ln in b:
                        if ln not in uniq[keep]:
                            lines[ln - 1] = " " * len(lines[ln - 1])
        cd = "\n".join(lines)
        return cd if balanced(cd) else None

    def ln(self, pos):
        return lineno(self.starts, pos)

    def doc_above(self, line):
        j = line - 1
        out = []
        while j >= 1:
            t = self.raw_lines[j - 1].strip()
            if t.startswith("//"):
                out.append(t)
                j -= 1
                continue
            if t.endswith("*/"):
                k = j
                blk = []
                while k >= 1:
                    blk.append(self.raw_lines[k - 1])
                    if "/*" in self.raw_lines[k - 1]:
                        break
                    k -= 1
                out.extend(blk)
                j = k - 1
                break
            break
        out.reverse()
        txt = "\n".join(out)
        txt = re.sub(r"/\*+|\*+/", " ", txt)
        cleaned = []
        for l in txt.split("\n"):
            l = re.sub(r"^\s*(?:\*+|/{2,}!?<?)\s?", "", l).strip()
            if l and not re.fullmatch(r"[-=*_/#~]{3,}", l) and not re.match(r"[-=]{5,}", l):
                cleaned.append(l)
        d = " ".join(cleaned)
        if "Copyright Epic Games" in d:
            d = re.sub(r".*?Copyright Epic Games, Inc\. All Rights Reserved\.?", "", d).strip()
        return d[:600]

    def trailing(self, line):
        if line - 1 >= len(self.raw_lines):
            return ""
        m = re.search(r"//+!?<?\s*(.+)$", self.raw_lines[line - 1])
        return m.group(1).strip()[:300] if m else ""

    # ---------------------------------------------------------------- statement scanner
    def scan(self, lo, hi, scope, ctx):
        """Scan statements of a scope (ctx in file/namespace/struct/cbuffer) between [lo, hi)."""
        cd = self.cd
        i = lo
        while i < hi:
            while i < hi and cd[i] in " \t\r\n;":
                i += 1
            if i >= hi:
                break
            j, d = i, 0
            stop = -1
            while j < hi:
                c = cd[j]
                if c in "([":
                    d += 1
                elif c in ")]":
                    d -= 1
                elif d <= 0 and c in "{;":
                    stop = j
                    break
                elif d <= 0 and c == "}":
                    stop = j
                    break
                j += 1
            if stop < 0:
                frag = collapse(self.nc[i:hi])
                if frag:
                    self.handle_tail(i, hi, frag, scope, ctx)
                break
            if cd[stop] == "}":
                frag = collapse(self.nc[i:stop])
                if frag:
                    self.handle_tail(i, stop, frag, scope, ctx)
                i = stop + 1
                continue
            hstart = i
            header = self.nc[i:stop]
            i = self.split_macro_calls(hstart, stop, scope, ctx)
            header = self.nc[i:stop]
            if cd[stop] == ";":
                self.handle_stmt(i, stop, header, scope, ctx)
                i = stop + 1
            else:
                e = match_close(cd, stop, "{", "}", hi)
                if e < 0:
                    self.errors.append(f"L{self.ln(stop)}: unmatched '{{'")
                    self.handle_block(i, stop, hi - 1, header, scope, ctx)
                    break
                nxt = self.handle_block(i, stop, e, header, scope, ctx)
                i = max(nxt, e + 1)

    def split_macro_calls(self, i, stop, scope, ctx):
        """Leading `MACRO(args)` lines that end without ';' (top-level macro invocations) become records."""
        cd = self.cd
        while True:
            m = re.compile(r"\s*([A-Z][A-Z0-9_]{2,})\s*\(").match(cd, i, stop)
            if not m:
                return i
            o = m.end() - 1
            e = match_close(cd, o, "(", ")", stop)
            if e < 0:
                return i
            rest = cd[e + 1:stop]
            if rest.strip() == "" or "\n" not in cd[e + 1:e + 1 + (len(rest) - len(rest.lstrip()))]:
                return i
            name = m.group(1)
            if name.startswith("RAY_TRACING_ENTRY") or name.endswith("_ENTRY"):
                return i
            ln = self.ln(m.start(1))
            self.decls.append(Decl("macro_call", name, scope, ln, self.ln(e),
                                   collapse(self.nc[m.start(1):e + 1])[:400], "", self.pp.cond[ln]))
            i = e + 1

    def handle_tail(self, a, b, frag, scope, ctx):
        m = re.match(r"([A-Z][A-Z0-9_]{2,})\s*(\(.*\))?$", frag, re.S)
        ln = self.ln(a + len(self.nc[a:b]) - len(self.nc[a:b].lstrip()))
        if m:
            self.decls.append(Decl("macro_call", m.group(1), scope, ln, self.ln(b), frag[:400], "", self.pp.cond[ln]))
        else:
            self.decls.append(Decl("unparsed", frag[:40], scope, ln, self.ln(b), frag[:400], "", self.pp.cond[ln]))
            self.errors.append(f"L{ln}: unparsed fragment `{frag[:80]}`")

    def head_info(self, a, header):
        lead = len(header) - len(header.lstrip())
        pre = re.match(r"\s*((?:[A-Z][A-Z0-9_]{2,}\s+)+)(?=\[)", header)
        lead_macros = ""
        if pre:
            lead_macros = collapse(pre.group(1))
            header = " " * pre.end() + header[pre.end():]
        attrs, rest, off = strip_attrs(header)
        if lead_macros:
            attrs = [lead_macros] + attrs
        start = a + lead
        ln = self.ln(start)
        tmpl = ""
        m = re.match(r"\s*template\s*<", rest)
        if m:
            k, d = m.end() - 1, 0
            for q in range(k, len(rest)):
                if rest[q] == "<":
                    d += 1
                elif rest[q] == ">":
                    d -= 1
                    if d == 0:
                        tmpl = collapse(rest[m.start():q + 1])
                        rest = rest[q + 1:]
                        break
        return attrs, rest, ln, tmpl

    def handle_block(self, a, brace, e, header, scope, ctx):
        """Header followed by {...}. Returns position to resume scanning."""
        cd = self.cd
        attrs, rest, ln, tmpl = self.head_info(a, header)
        h = collapse(rest)
        doc = self.doc_above(ln) or self.trailing(ln)
        cond = self.pp.cond[ln]
        endl = self.ln(e)
        m = re.match(r"(struct|class|interface)\s+([A-Za-z_]\w*)\s*(:\s*(.+))?$", h)
        if m:
            q = (scope + "::" if scope else "") + m.group(2)
            dcl = Decl(m.group(1), m.group(2), scope, ln, endl, (tmpl + " " if tmpl else "") + h, doc, cond, attrs,
                       extra=collapse(m.group(4) or ""))
            self.decls.append(dcl)
            self.scan(brace + 1, e, q, "struct")
            return self.after_type(e, scope, ctx)
        m = re.match(r"(enum)(\s+class)?\s+([A-Za-z_]\w*)?\s*(:\s*(\w+))?$", h)
        if m:
            name = m.group(3) or "(anonymous)"
            dcl = Decl("enum", name, scope, ln, endl, h, doc, cond, attrs, extra=m.group(5) or "")
            self.decls.append(dcl)
            self.enumerators(brace + 1, e, (scope + "::" if scope else "") + name)
            return self.after_type(e, scope, ctx)
        m = re.match(r"(cbuffer|tbuffer)\s+([A-Za-z_]\w*)\s*(:\s*(.+))?$", h)
        if m:
            q = (scope + "::" if scope else "") + m.group(2)
            self.decls.append(Decl("cbuffer", m.group(2), scope, ln, endl, h, doc, cond, attrs,
                                   extra=collapse(m.group(4) or "")))
            self.scan(brace + 1, e, q, "cbuffer")
            return e + 1
        m = re.match(r"namespace\s+([A-Za-z_][\w:]*)$", h)
        if m:
            q = (scope + "::" if scope else "") + m.group(1)
            self.decls.append(Decl("namespace", m.group(1), scope, ln, endl, h, "", cond))
            self.scan(brace + 1, e, q, "namespace")
            return e + 1
        if re.match(r"struct\s*$", h):
            self.decls.append(Decl("struct", "(anonymous)", scope, ln, endl, h, doc, cond, attrs))
            self.scan(brace + 1, e, (scope + "::" if scope else "") + "(anonymous)", "struct")
            return self.after_type(e, scope, ctx)
        f = self.as_function(h)
        if f:
            name, ret, params, post = f
            self.add_function(name, ret, params, post, attrs, tmpl, h, ln, endl, doc, cond, scope, ctx, True)
            return e + 1
        if re.search(r"=\s*$", h) or re.search(r"=\s*\w*\s*$", h):
            # aggregate initializer: static const float A[] = { ... };
            k = e + 1
            while k < len(cd) and cd[k] in " \t\r\n":
                k += 1
            semi = cd.find(";", e)
            if semi < 0:
                semi = e
            full = collapse(self.nc[a:semi + 1])
            self.add_vars(full, ln, self.ln(semi), doc, cond, attrs, scope, ctx)
            return semi + 1
        if not h:
            self.decls.append(Decl("stray_block", "", scope, ln, endl, "{ ... }", "", cond, attrs))
            self.errors.append(f"L{ln}: brace block without header (code split across #if branches)")
            return e + 1
        mm = re.match(r"([A-Z][A-Z0-9_]{2,})\s*\((.*)\)\s*$", h, re.S)
        if mm:
            self.decls.append(Decl("macro_block", mm.group(1), scope, ln, endl, h[:400], doc, cond, attrs))
            return e + 1
        lm = LEAD_MACROS_RE.match(header)
        if lm and lm.group(2).strip() and not getattr(self, "_retry", False):
            self._retry = True
            try:
                hdr2 = header[:lm.start(1)] + " " * len(lm.group(1)) + header[lm.end(1):]
                nxt = self.handle_block(a, brace, e, hdr2, scope, ctx)
            finally:
                self._retry = False
            last = self.decls[-1] if self.decls else None
            if last is not None and last.line >= ln and last.kind != "unparsed":
                last.attrs = [collapse(lm.group(1))] + last.attrs
                return nxt
            if last is not None and last.kind == "unparsed":
                self.decls.pop()
                self.errors.pop()
        self.decls.append(Decl("unparsed", h[:40], scope, ln, endl, h[:400], doc, cond, attrs))
        self.errors.append(f"L{ln}: unrecognised block header `{h[:80]}`")
        return e + 1

    def after_type(self, e, scope, ctx):
        """After `struct X {...}` consume optional declarators up to ';'."""
        cd = self.cd
        k = e + 1
        while k < len(cd) and cd[k] in " \t\r\n":
            k += 1
        if k < len(cd) and cd[k] == ";":
            return k + 1
        m = re.compile(r"[A-Za-z_][\w\s,\[\]]*;").match(cd, k)
        if m and "\n\n" not in m.group(0):
            return m.end()
        return e + 1

    def as_function(self, h):
        """If header h looks like `ret name(params) [const] [: SEM]`, return (name, ret, params, post)."""
        d = 0
        eq = -1
        for i, c in enumerate(h):
            if c in "([<":
                d += 1 if c != "<" else 0
            elif c in ")]":
                d -= 1
            elif c == "=" and d == 0 and h[i - 1:i + 1] not in ("==", "<=", ">=", "!=") and h[i:i + 2] != "==":
                eq = i
                break
            elif c == "(" and d == 1:
                pass
        if eq >= 0:
            return None
        for m in re.finditer(r"((?:[A-Za-z_][\w:]*::)?operator\s*(?:\(\s*\)|\[\s*\]|[^\w\s(]+|\w+)|"
                             r"[A-Za-z_][\w:]*)\s*\(", h):
            name = m.group(1)
            if name.split("::")[-1] in KEYWORDS:
                return None
            pre = h[:m.start()]
            if pre.count("(") != pre.count(")"):
                continue
            o = m.end() - 1
            e = match_close(h, o, "(", ")")
            if e < 0:
                return None
            post = h[e + 1:].strip()
            if not re.fullmatch(r"(?:const\s*)?(?::\s*[A-Za-z_]\w*\s*)?", post):
                return None
            ret = collapse(pre)
            return name, ret, collapse(h[o + 1:e]), post
        return None

    def add_function(self, name, ret, params, post, attrs, tmpl, h, ln, endl, doc, cond, scope, ctx, is_def):
        bare = name.split("::")[-1]
        if not ret:
            # macro-wrapped entry point (RAY_TRACING_ENTRY_RAYGEN(Name) {...}) or macro invocation with a block
            if re.fullmatch(r"[A-Z][A-Z0-9_]+", name):
                args = [collapse(x) for x in split_top(params)]
                if "ENTRY" in name:
                    stage = ENTRY_MACRO_STAGE.get(name, name)
                    en = args[0] if args else name
                    self.decls.append(Decl("entry", en, scope, ln, endl, h[:600], doc, cond, attrs, extra=stage))
                else:
                    self.decls.append(Decl("macro_block" if is_def else "macro_call", name, scope, ln, endl,
                                           h[:400], doc, cond, attrs))
                return
            kind = "ctor" if ctx == "struct" and bare == scope.split("::")[-1] else (
                "macro_call" if not is_def else "unparsed")
            if kind == "unparsed":
                self.errors.append(f"L{ln}: function without return type `{h[:80]}`")
            self.decls.append(Decl(kind, bare, scope, ln, endl, h[:600], doc, cond, attrs))
            return
        sig = (tmpl + " " if tmpl else "") + h
        stage = ""
        akeys = [parse_attr(a) for a in attrs]
        for k, v in akeys:
            if k == "shader":
                stage = v.strip('"').strip()
            elif k == "numthreads" and not stage:
                stage = "compute"
            elif k == "nodelaunch":
                stage = "node(" + v.strip('"') + ")"
            elif k in ("maxvertexcount",) and not stage:
                stage = "geometry"
            elif k in ("domain", "outputcontrolpoints", "patchconstantfunc") and not stage:
                stage = "hull/domain"
            elif k == "outputtopology" and not stage:
                stage = "mesh"
        if stage:
            kind = "entry"
        elif ctx == "struct":
            kind = "method" if is_def else "method_proto"
        else:
            kind = "function" if is_def else "prototype"
        sv = bool(re.search(r":\s*SV_\w+", params + " " + post))
        extra = stage or ("sv-semantics" if sv and kind in ("function",) else "")
        self.decls.append(Decl(kind, bare, scope if "::" not in name else "::".join(name.split("::")[:-1]),
                               ln, endl, sig[:900], doc, cond, attrs, extra=extra))

    def add_vars(self, full, ln, endl, doc, cond, attrs, scope, ctx):
        t = full.rstrip(";").strip()
        if re.match(r"typedef\b", t):
            nm = decl_name(t[len("typedef"):])
            self.decls.append(Decl("typedef", nm, scope, ln, endl, full[:600], doc, cond, attrs))
            return
        if re.match(r"using\b", t):
            m = re.match(r"using\s+(\w+)", t)
            self.decls.append(Decl("typedef", m.group(1) if m else t[:40], scope, ln, endl, full[:600], doc, cond,
                                   attrs))
            return
        if ctx == "struct":
            kind = "member"
        elif ctx == "cbuffer":
            kind = "cbuffer_member"
        else:
            kind = classify_var(t)
        decls = split_top(t)
        first = decls[0]
        names = [decl_name(first)]
        for extra in decls[1:]:
            nm = decl_name("x " + extra) if not re.match(r"\s*[A-Za-z_]\w*\s+[A-Za-z_]", extra) else decl_name(extra)
            if nm:
                names.append(nm)
        for nm in names:
            if not nm:
                self.decls.append(Decl("unparsed", t[:40], scope, ln, endl, full[:600], doc, cond, attrs))
                self.errors.append(f"L{ln}: unnamed declaration `{t[:80]}`")
                continue
            self.decls.append(Decl(kind, nm, scope, ln, endl, full[:600], doc, cond, attrs))

    def handle_stmt(self, a, stop, header, scope, ctx):
        attrs, rest, ln, tmpl = self.head_info(a, header)
        h = collapse(rest)
        if not h:
            return
        endl = self.ln(stop)
        doc = self.doc_above(ln) or self.trailing(endl)
        cond = self.pp.cond[ln]
        full = collapse(self.nc[a:stop + 1])
        full = collapse(rest) + ";"
        if re.match(r"(struct|class|interface|enum)\s+\w+\s*$", h):
            self.decls.append(Decl("forward", h.split()[-1], scope, ln, endl, full, doc, cond, attrs))
            return
        if re.match(r"(typedef|using)\b", h):
            self.add_vars(full, ln, endl, doc, cond, attrs, scope, ctx)
            return
        if re.match(r"(return|break|continue|discard)\b", h):
            self.decls.append(Decl("unparsed", h[:40], scope, ln, endl, full[:400], doc, cond, attrs))
            self.errors.append(f"L{ln}: statement at declaration scope `{h[:80]}`")
            return
        f = self.as_function(h)
        if f:
            name, ret, params, post = f
            if ret and not re.search(r"\b(static|const|groupshared|uniform)\b", ret) or (ret and "(" not in ret):
                self.add_function(name, ret, params, post, attrs, tmpl, h, ln, endl, doc, cond, scope, ctx, False)
                return
            if not ret:
                self.add_function(name, ret, params, post, attrs, tmpl, h, ln, endl, doc, cond, scope, ctx, False)
                return
        self.add_vars(full, ln, endl, doc, cond, attrs, scope, ctx)

    def enumerators(self, a, b, scope):
        body = self.cd[a:b]
        pos = a
        for part in split_top(body):
            raw = self.nc[pos:pos + len(part)]
            nm = IDENT_RE.match(part.strip())
            if nm:
                off = pos + part.index(nm.group(0))
                ln = self.ln(off)
                self.decls.append(Decl("enumerator", nm.group(0), scope, ln, ln, collapse(raw)[:300],
                                       self.trailing(ln), self.pp.cond[ln]))
            pos += len(part) + 1


LEAD_MACROS_RE = re.compile(r"\s*((?:[A-Z][A-Z0-9_]{2,}(?:\s*\([^()]*\))?\s+)+)(.*)", re.S)

ENTRY_MACRO_STAGE = {
    "RAY_TRACING_ENTRY_RAYGEN": "raygeneration", "RAY_TRACING_ENTRY_CLOSEST_HIT": "closesthit",
    "RAY_TRACING_ENTRY_ANY_HIT": "anyhit", "RAY_TRACING_ENTRY_MISS": "miss",
    "RAY_TRACING_ENTRY_CALLABLE": "callable", "RAY_TRACING_ENTRY_INTERSECTION": "intersection",
    "RAY_TRACING_ENTRY_RAYGEN_OR_INLINE": "raygeneration|compute(inline)",
    "LUMEN_HARDWARE_RAY_TRACING_ENTRY": "raygeneration|compute(inline)",
}


# --------------------------------------------------------------------------- C++ side: IMPLEMENT_*(..."/X/Y.usf", "Entry", SF_*)
IMPL_RE = re.compile(r"\b(IMPLEMENT_\w+)\s*\(")
STR_LIT_RE = re.compile(r'(?:TEXT\s*\(\s*)?"((?:\\.|[^"\\])*)"\s*\)?')


def cpp_impl_scan(path_rel_engine):
    engine, rel = path_rel_engine
    out, errs = [], []
    try:
        text = open(os.path.join(engine, rel), encoding="utf-8", errors="replace").read()
    except OSError as e:
        return out, [f"{rel}: {e}"]
    if ".us" not in text:
        return out, errs
    nc, cd = mask(text)
    starts = line_starts(text)
    for m in IMPL_RE.finditer(cd):
        o = m.end() - 1
        e = match_close(cd, o, "(", ")", min(len(cd), o + 4000))
        if e < 0:
            continue
        args = [a.strip() for a in split_top(nc[o + 1:e])]
        pi = -1
        for k, a in enumerate(args):
            sm = STR_LIT_RE.fullmatch(a)
            if sm and re.search(r"\.us[fh]$", sm.group(1)):
                pi = k
                break
        if pi < 0:
            continue
        vpath = STR_LIT_RE.fullmatch(args[pi]).group(1)
        entry = ""
        if pi + 1 < len(args):
            sm = STR_LIT_RE.fullmatch(args[pi + 1])
            entry = sm.group(1) if sm else args[pi + 1]
        freq = ""
        for a in args[pi + 1:]:
            mm = re.search(r"\bSF_\w+", a)
            if mm:
                freq = mm.group(0)
                break
        cls = ""
        for a in args[:pi]:
            a2 = collapse(a)
            if re.match(r"[A-Za-z_][\w:]*(<.*>)?$", a2) and a2 not in ("template", "typename"):
                cls = a2
        ln = lineno(starts, m.start())
        in_define = text[starts[ln - 1]:starts[ln - 1] + 200].lstrip().startswith("#")
        out.append(dict(macro=m.group(1), cls=cls, vpath=vpath, entry=entry, freq=freq, src=rel, line=ln,
                        in_define=in_define))
    return out, errs


def cpp_candidates(engine):
    r = subprocess.run(["grep", "-rlE", "--include=*.cpp", "--include=*.h", "--include=*.inl", r"IMPLEMENT_\w+",
                        "Source", "Plugins", "Platforms"], cwd=engine, capture_output=True, text=True)
    return sorted(x for x in r.stdout.split("\n") if x and "/ThirdParty/" not in x)


def build_resolver(files):
    """Virtual shader path -> engine-relative file (suffix match with mount-name preference)."""
    by_tail = defaultdict(list)
    for f in files:
        parts = f.split("/")
        for k in range(1, len(parts)):
            by_tail["/".join(parts[k:])].append(f)

    cache = {}

    def resolve(vp):
        if vp in cache:
            return cache[vp]
        p = vp.lstrip("/").split("/")
        res = None
        if p[0] == "Engine" and len(p) > 1:
            cand = "Shaders/" + "/".join(p[1:])
            res = cand if cand in set_files else None
        if res is None:
            mount = p[1] if p[0] in ("Plugin", "Plugins") and len(p) > 1 else p[0]
            for k in range(1, len(p)):
                tail = "/".join(p[k:])
                c = by_tail.get(tail, [])
                if len(c) == 1:
                    res = c[0]
                    break
                if len(c) > 1:
                    pref = [x for x in c if f"/{mount}/" in x or f"/{mount}" in x]
                    if len(pref) == 1:
                        res = pref[0]
                    break
        cache[vp] = res
        return res

    set_files = set(files)
    return resolve


# --------------------------------------------------------------------------- per-file job
# Data-interface HLSL templates (Niagara / PCG / ComputeFramework / Optimus) are instantiated by C++ string
# formatting; their identifiers contain {ParameterName}-style placeholders.  They are rewritten to identifier tokens
# for parsing and restored when rendering.
TPL_RE = re.compile(r"\{([A-Za-z_]\w*)\}")
TPL_ADJ_RE = re.compile(r"\w\{[A-Za-z_]\w*\}|\{[A-Za-z_]\w*\}\w|\{[A-Za-z_]\w*\}\s*\(|^[ \t]*\{[A-Za-z_]\w*\}[ \t]*$",
                        re.M)
TPL_PREFIX, TPL_SUFFIX = "TPLx0", "x0TPL"
TPL_BACK_RE = re.compile(TPL_PREFIX + r"(\w+?)" + TPL_SUFFIX)


def untpl(s):
    return TPL_BACK_RE.sub(lambda m: "{" + m.group(1) + "}", s) if TPL_PREFIX in s else s

def parse_shader(args):
    engine, rel = args
    res = dict(rel=rel, vis=visibility_of(rel), lines=0, mode="", errors=[], decls=[], pp=[], failed="")
    try:
        text = open(os.path.join(engine, rel), encoding="utf-8", errors="replace").read()
        text = text.lstrip("\ufeff").replace("\r\n", "\n").replace("\r", "\n")
        res["lines"] = text.count("\n") + 1
        if len(TPL_ADJ_RE.findall(text)) >= 1 and len(TPL_RE.findall(text)) >= 2:
            text = TPL_RE.sub(lambda m: TPL_PREFIX + m.group(1) + TPL_SUFFIX, text)
            res["template"] = True
        fp = FileParser(text)
        fp.scan(0, len(fp.cd), "", "file")
        bad = lambda f: sum(d.kind in ("unparsed", "stray_block") for d in f.decls) * 1000 - len(f.decls)
        if any(d.kind in ("unparsed", "stray_block") for d in fp.decls) and fp.mode != "per-group":
            for force in ("first-branch", "last-branch"):
                alt = FileParser(text, force)
                if not balanced(alt.cd):
                    continue
                alt.scan(0, len(alt.cd), "", "file")
                if bad(alt) < bad(fp):
                    have = {(d.kind, d.name, d.line) for d in alt.decls}
                    lines_bad = {d.line for d in alt.decls if d.kind in ("unparsed", "stray_block")}
                    merged = [d for d in fp.decls if d.kind not in ("unparsed", "stray_block")
                              and (d.kind, d.name, d.line) not in have and d.line not in lines_bad]
                    alt.decls = sorted(alt.decls + merged, key=lambda d: d.line)
                    alt.mode += f" (retry, +{len(merged)} merged from all-branches pass)"
                    fp = alt
        if not fp.mode.startswith(("all-branches", "per-group")):
            # a single-branch view drops declarations that only exist in the other #if/#else branches: parse the
            # alternative branch selection too and merge whatever it found that the primary pass did not
            have = {(d.kind, d.name) for d in fp.decls}
            added = 0
            for force in ("first-branch", "last-branch"):
                if fp.mode.startswith(force):
                    continue
                alt = FileParser(text, force)
                if not balanced(alt.cd):
                    continue
                alt.scan(0, len(alt.cd), "", "file")
                for d in alt.decls:
                    if d.kind not in ("unparsed", "stray_block") and (d.kind, d.name) not in have:
                        fp.decls.append(d)
                        have.add((d.kind, d.name))
                        added += 1
            if added:
                fp.decls.sort(key=lambda d: d.line)
                fp.mode += f" (+{added} from other #if branch)"
        res["mode"] = fp.mode
        res["errors"] = fp.errors[:50]
        res["n_errors"] = len(fp.errors)
        res["pp"] = fp.pp.records
        res["decls"] = [(d.kind, untpl(d.name), untpl(d.scope), d.line, d.end, untpl(d.text), d.doc, untpl(d.cond),
                         [untpl(x) for x in d.attrs], untpl(d.extra)) for d in fp.decls]
        if res.get("template"):
            res["pp"] = [tuple(untpl(x) if isinstance(x, str) else
                               (tuple(untpl(y) for y in x) if isinstance(x, tuple) else x) for x in p)
                         for p in res["pp"]]
    except Exception as ex:  # robust: record and continue
        res["failed"] = f"{type(ex).__name__}: {ex}"
        res["n_errors"] = 1
    return res


# --------------------------------------------------------------------------- rendering
def esc(s):
    return s.replace("`", "'").replace("|", "\\|")


def cond_s(c):
    return f" _[#if {esc(c)}]_" if c else ""


SECTION_ORDER = [
    ("entry", "Entry points"), ("struct", "Structs / classes"), ("class", None), ("interface", None),
    ("enum", "Enums"), ("cbuffer", "cbuffers"), ("namespace", "Namespaces"),
    ("resource", "Global resources (textures / buffers / samplers)"), ("parameter", "Global parameters (uniforms)"),
    ("groupshared", "groupshared"), ("static_const", "static const"), ("static_var", "static variables"),
    ("typedef", "typedef / using"), ("function", "Functions"), ("prototype", "Prototypes"), ("forward", "Forward decls"),
    ("macro_block", "Macro blocks"), ("macro_call", "Top-level macro invocations"), ("unparsed", "Unparsed (raw text)"),
    ("stray_block", "Stray brace blocks (function body split by #if)"),
]
CHILD_KINDS = {"member", "cbuffer_member", "method", "method_proto", "ctor", "enumerator"}


def render_file(r, bindings, out):
    rel = r["rel"]
    out.append(f"\n### `{rel}` ({r['vis']})\n")
    meta = f"- lines: {r['lines']}; parse: {r['mode'] or 'FAILED'}"
    if r.get("template"):
        meta += "; HLSL template with {Placeholder} identifiers (instantiated from C++)"
    if r.get("n_errors"):
        meta += f"; parse notes: {r['n_errors']}"
    out.append(meta)
    if r["failed"]:
        out.append(f"- **parse failure**: {esc(r['failed'])}")
    incs = [p for p in r["pp"] if p[0] == "include"]
    if incs:
        out.append("- includes: " + ", ".join(f"L{p[1]} `{esc(p[2])}`" + (f" [{esc(p[3])}]" if p[3] else "")
                                            for p in incs))
    defs = [p for p in r["pp"] if p[0] == "define"]
    if defs:
        out.append(f"\n#### Macros (#define, {len(defs)})\n")
        for p in defs:
            _, ln, name, (args, val), cond, nlines = p
            v = collapse(val)
            v = v if len(v) <= 200 else v[:200] + " ..."
            out.append(f"- L{ln} `#define {esc(name)}{esc(args)} {esc(v)}`".rstrip() +
                       (f" ({nlines} lines)" if nlines > 1 else "") + cond_s(cond))
    other = [p for p in r["pp"] if p[0] in ("undef", "pragma")]
    if other:
        out.append("- " + "; ".join(f"L{p[1]} #{p[0]} `{esc(p[2])}`" for p in other[:60]) +
                   (f" ... (+{len(other) - 60})" if len(other) > 60 else ""))
    decls = r["decls"]
    children = defaultdict(list)
    tops = []
    for d in decls:
        if d[0] in CHILD_KINDS:
            children[d[2]].append(d)
        else:
            tops.append(d)
    used_child_scopes = set()
    by_kind = defaultdict(list)
    for d in tops:
        by_kind[d[0]].append(d)
    for kind, title in SECTION_ORDER:
        items = by_kind.get(kind, [])
        if kind == "struct":
            items = by_kind.get("struct", []) + by_kind.get("class", []) + by_kind.get("interface", [])
            items.sort(key=lambda x: x[3])
        if not items or title is None:
            continue
        out.append(f"\n#### {title} ({len(items)})\n")
        for d in items:
            k, name, scope, ln, end, text, doc, cond, attrs, extra = d
            q = (scope + "::" if scope else "") + name
            att = (" ".join(esc(a) for a in attrs) + " ") if attrs else ""
            if k in ("struct", "class", "interface", "enum", "cbuffer", "namespace"):
                line = f"- L{ln}-{end} _{k}_ **`{esc(q)}`** `{att}{esc(text)}`"
                if extra:
                    line += f" — base/reg: `{esc(extra)}`"
            else:
                line = f"- L{ln}{'-' + str(end) if end != ln else ''} _{k}_ `{att}{esc(text)}`"
                if k == "entry":
                    line += f" — stage: **{esc(extra)}**"
                    for b in bindings.get(name, []):
                        line += (f" — C++: `{esc(b['cls'] or '?')}` {b['freq']} via {b['macro']} "
                                 f"({b['src']}:{b['line']})")
                elif extra:
                    line += f" — {esc(extra)}"
                if scope:
                    line += f" (scope `{esc(scope)}`)"
            if doc:
                line += f" — {esc(doc)}"
            line += cond_s(cond)
            out.append(line)
            if k in ("struct", "class", "interface", "enum", "cbuffer"):
                used_child_scopes.add(q)
                for c in children.get(q, []):
                    ck, cn, cs, cl, ce, ct, cdoc, ccond, cattrs, cextra = c
                    catt = (" ".join(esc(a) for a in cattrs) + " ") if cattrs else ""
                    s = f"  - L{cl} _{ck}_ `{catt}{esc(ct)}`"
                    if cdoc:
                        s += f" — {esc(cdoc)}"
                    s += cond_s(ccond)
                    out.append(s)
    orphans = [c for sc, cl in children.items() if sc not in used_child_scopes for c in cl]
    if orphans:
        out.append(f"\n#### Members of unresolved scopes ({len(orphans)})\n")
        for c in orphans:
            out.append(f"- L{c[3]} _{c[0]}_ `{esc(c[5])}` (scope `{esc(c[2])}`)" + cond_s(c[7]))
    # C++ bindings that name a function not detected as entry
    names_entry = set()
    for d in decls:
        if d[0] == "entry":
            names_entry.add(d[1])
            if "inline" in d[9]:
                names_entry.update({d[1] + "CS", d[1] + "RGS"})
    extra_b = [(n, b) for n, bl in bindings.items() if n not in names_entry for b in bl]
    if extra_b:
        out.append(f"\n#### C++ shader bindings (IMPLEMENT_* naming this file, {len(extra_b)})\n")
        for n, b in sorted(extra_b, key=lambda x: (x[0], x[1]["src"], x[1]["line"])):
            fn = [d for d in decls if d[1] == n and d[0] in ("function", "prototype", "macro_block")]
            loc = f"L{fn[0][3]}" if fn else "entry not found in file (macro-generated or #include'd)"
            out.append(f"- `{esc(n) or '(none)'}` → {loc}; C++ `{esc(b['cls'] or '?')}` {b['freq']} via "
                       f"{b['macro']} ({b['src']}:{b['line']})")
    if r.get("errors"):
        out.append("\n<details><summary>parse notes</summary>\n")
        for e in r["errors"]:
            out.append(f"- {esc(e)}")
        out.append("\n</details>")


FREQ_STAGE = {"SF_Vertex": "vertex", "SF_Pixel": "pixel", "SF_Compute": "compute", "SF_Geometry": "geometry",
              "SF_Mesh": "mesh", "SF_Amplification": "amplification", "SF_RayGen": "raygeneration",
              "SF_RayMiss": "miss", "SF_RayHitGroup": "closesthit/anyhit", "SF_RayCallable": "callable",
              "SF_WorkGraphRoot": "workgraph-root", "SF_WorkGraphComputeNode": "workgraph-node"}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--engine", default=ENGINE)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--jobs", type=int, default=14)
    ap.add_argument("--only", default="", help="substring filter on path (debug)")
    a = ap.parse_args()
    engine, out = a.engine, Path(a.out)
    files = find_shader_files(engine)
    if a.only:
        files = [f for f in files if a.only in f]
    (out / "index").mkdir(parents=True, exist_ok=True)
    sdir = out / "api" / "Shaders"
    sdir.mkdir(parents=True, exist_ok=True)
    for old in sdir.glob("*.md"):
        old.unlink()
    with Pool(min(a.jobs, 14)) as pool:
        results = list(pool.imap(parse_shader, [(engine, f) for f in files], chunksize=4))
        cands = cpp_candidates(engine)
        impl, impl_err = [], []
        for o, e in pool.imap_unordered(cpp_impl_scan, [(engine, f) for f in cands], chunksize=16):
            impl += o
            impl_err += e
    resolve = build_resolver(files)
    by_file_bind = defaultdict(lambda: defaultdict(list))
    unresolved = []
    for b in impl:
        if b["in_define"]:
            continue
        f = resolve(b["vpath"])
        if f is None:
            unresolved.append(b)
        else:
            names = re.findall(r"\w+=(\w+)", b["entry"]) if "=" in b["entry"] else [b["entry"]]
            for nm in names:
                by_file_bind[f][nm].append(b)
    # promote functions named by a C++ binding to entry points
    promoted = 0
    for r in results:
        binds = by_file_bind.get(r["rel"], {})
        if not binds:
            continue
        new = []
        for d in r["decls"]:
            if d[0] == "function" and d[1] in binds and not d[2]:
                fr = sorted({FREQ_STAGE.get(b["freq"], b["freq"] or "?") for b in binds[d[1]]})
                d = ("entry",) + d[1:9] + ("/".join(fr) + " (from C++ binding)",)
                promoted += 1
            new.append(d)
        r["decls"] = new
    groups = defaultdict(list)
    for r in results:
        groups[group_of(r["rel"])].append(r)
    tsv = []
    stat = Counter()
    gsum = []
    for g in sorted(groups):
        rs = sorted(groups[g], key=lambda x: x["rel"])
        parts, cur, size = [], [], 0
        gstat = Counter()
        for r in rs:
            buf = []
            render_file(r, by_file_bind.get(r["rel"], {}), buf)
            text = "\n".join(buf) + "\n"
            if size + len(text) > PART_LIMIT and cur:
                parts.append("".join(cur))
                cur, size = [], 0
            cur.append(text)
            size += len(text)
            for p in r["pp"]:
                if p[0] in ("include", "define"):
                    gstat[p[0]] += 1
                    info = p[3] if p[0] == "include" else p[4]
                    tsv.append("\t".join([r["rel"], str(p[1]), p[0], "", p[2], r["vis"], info.replace("\t", " ")]))
            for d in r["decls"]:
                gstat[d[0]] += 1
                info = d[9] if d[0] == "entry" else d[7]
                tsv.append("\t".join([r["rel"], str(d[3]), d[0], d[2], d[1], r["vis"],
                                      (info or "").replace("\t", " ")]))
            for (n, bl) in by_file_bind.get(r["rel"], {}).items():
                for b in bl:
                    gstat["cpp_binding"] += 1
                    tsv.append("\t".join([r["rel"], "0", "cpp_binding", b["cls"], n, r["vis"],
                                          f"{b['freq']} {b['macro']} {b['src']}:{b['line']}"]))
        if cur:
            parts.append("".join(cur))
        names = []
        for pi, body in enumerate(parts, 1):
            fn = f"{g}.md" if len(parts) == 1 else f"{g}.part{pi:02d}.md"
            head = [f"# Shaders / {os.path.dirname(rs[0]['rel'])}" +
                    (f" (part {pi}/{len(parts)})" if len(parts) > 1 else ""), ""]
            if pi == 1:
                head.append(f"- files: {len(rs)}; lines: {sum(x['lines'] for x in rs)}")
                head.append("- record kinds: " + ", ".join(f"{k}={v}" for k, v in sorted(gstat.items())))
                head.append("")
            (sdir / fn).write_text("\n".join(head) + body, encoding="utf-8")
            names.append(fn)
        stat.update(gstat)
        gsum.append(dict(group=g, dir=os.path.dirname(rs[0]["rel"]), files=len(rs), outputs=names,
                         stat=dict(gstat)))
    with gzip.open(out / "index" / "shaders.tsv.gz", "wt", encoding="utf-8") as gz:
        gz.write("\n".join(tsv) + "\n")
    fails = [dict(rel=r["rel"], failed=r["failed"]) for r in results if r["failed"]]
    modes = Counter(re.sub(r" \(\+\d+ from other #if branch\)", " +other-branch", re.sub(r" \(retry[^)]*\)", " (retry)",
                                                                                         r["mode"])) or "FAILED"
                    for r in results)
    noted = sorted(((r["rel"], r.get("n_errors", 0), r["errors"][:5]) for r in results if r.get("n_errors")),
                   key=lambda x: -x[1])
    summary = dict(total_files=len(results), usf=sum(r["rel"].endswith(".usf") for r in results),
                   ush=sum(r["rel"].endswith(".ush") for r in results),
                   h=sum(r["rel"].endswith(".h") for r in results),
                   total_records=len(tsv), stat=dict(stat), parse_modes=dict(modes), failures=fails,
                   files_with_notes=len(noted), cpp_bindings=len(impl),
                   cpp_bindings_in_macro_defs=sum(b["in_define"] for b in impl),
                   cpp_bindings_unresolved=len(unresolved), promoted_entries=promoted,
                   files=[r["rel"] for r in results], groups=gsum)
    (out / "shaders_summary.json").write_text(json.dumps(summary, indent=1), encoding="utf-8")
    rep = ["# Shader extraction report", "",
           f"- files: {len(results)} (usf {summary['usf']}, ush {summary['ush']}, shared .h {summary['h']})",
           f"- records (TSV rows): {len(tsv)}",
           "- kinds: " + ", ".join(f"{k}={v}" for k, v in sorted(stat.items())),
           "- parse modes: " + ", ".join(f"{k}={v}" for k, v in sorted(modes.items())),
           f"- hard failures: {len(fails)}",
           f"- C++ IMPLEMENT_* bindings: {len(impl)} (inside #define bodies, skipped: "
           f"{summary['cpp_bindings_in_macro_defs']}; unresolved virtual paths: {len(unresolved)}); "
           f"functions promoted to entry by binding: {promoted}", ""]
    if fails:
        rep += ["## Hard failures", ""] + [f"- `{f['rel']}`: {esc(f['failed'])}" for f in fails] + [""]
    if unresolved:
        rep += ["## Unresolved C++ virtual shader paths", ""]
        for b in sorted(unresolved, key=lambda x: x["vpath"]):
            rep.append(f"- `{esc(b['vpath'])}` entry `{esc(b['entry'])}` ({b['src']}:{b['line']})")
        rep.append("")
    rep += ["## Files with parse notes (top 200)", ""]
    for rel, n, es in noted[:200]:
        rep.append(f"- `{rel}`: {n} — " + "; ".join(esc(e) for e in es))
    rep.append("")
    rep += ["## Groups", ""] + [f"- `{g['dir']}`: {g['files']} files → {', '.join(g['outputs'])}" for g in gsum]
    (sdir / "_REPORT.md").write_text("\n".join(rep) + "\n", encoding="utf-8")
    print(json.dumps({k: v for k, v in summary.items() if k not in ("files", "groups", "failures")}))


if __name__ == "__main__":
    main()
