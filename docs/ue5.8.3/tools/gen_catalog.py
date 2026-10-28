#!/usr/bin/env python3
"""Catalog / data dictionaries for modules, plugins, targets, projects, config ini files and config UCLASSes.

  dictionary/modules.{md,tsv}       every *.Build.cs (Engine/Source,Plugins,Platforms incl. ThirdParty): Type, owning
                                    plugin + .uplugin descriptor (Type/LoadingPhase/allow-deny lists), PCHUsage,
                                    dependency lists (public/private/dynamic/include-path), third-party deps
  dictionary/plugins.{md,tsv}       every *.uplugin under $UE (Engine + Samples/Templates): all top-level fields,
                                    module descriptors, plugin dependencies  (+ plugin_modules.tsv, plugin_deps.tsv)
  dictionary/targets.{md,tsv}       every *.Target.cs under $UE: every assignment / call in the rules constructor
  dictionary/projects.{md,tsv}      every *.uproject under $UE: all fields, modules, plugin enable list
  dictionary/config.{md,tsv}        every Engine *.ini: sections and keys (config_keys.tsv has one row per key line)
  dictionary/uclass_config.{md,tsv} every UCLASS(config=X) in Engine headers + its Config/GlobalConfig UPROPERTYs
Build.cs / Target.cs constructors are parsed with tools/extract_cs.py's comment/string aware rules parser (imported,
not modified); .uplugin/.uproject JSON is parsed strictly first, then leniently (comments/trailing commas removed),
with the leniency recorded in the status column.
"""
import argparse
import json
import os
import re
import sys
from collections import defaultdict, Counter
from multiprocessing import Pool
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import extract_cs as XCS  # noqa: E402
from extract_shaders import mask, match_close, line_starts, lineno  # noqa: E402

UE = "/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release"
OUT = "/home/timeshift/opensource/break/docs/ue5.8.3/appendix"
SKIP_DIRS = {"Intermediate", "Binaries", ".git", "Saved", "obj", "bin"}
DEP_PROPS = ["PublicDependencyModuleNames", "PrivateDependencyModuleNames", "DynamicallyLoadedModuleNames",
             "PublicIncludePathModuleNames", "PrivateIncludePathModuleNames", "CircularlyReferencedDependentModules",
             "@AddEngineThirdPartyPrivateStaticDependencies", "@AddEngineThirdPartyPrivateDynamicDependencies"]
SHORT = {"PublicDependencyModuleNames": "public", "PrivateDependencyModuleNames": "private",
         "DynamicallyLoadedModuleNames": "dynamic", "PublicIncludePathModuleNames": "pub-include",
         "PrivateIncludePathModuleNames": "priv-include", "CircularlyReferencedDependentModules": "circular",
         "@AddEngineThirdPartyPrivateStaticDependencies": "3p-static",
         "@AddEngineThirdPartyPrivateDynamicDependencies": "3p-dynamic"}


def esc(s):
    return str(s if s is not None else "").replace("|", "\\|").replace("`", "'").replace("\n", " ").replace("\r", "")


def tsv(s):
    if isinstance(s, (list, tuple)):
        s = ",".join(str(x) for x in s)
    elif isinstance(s, dict):
        s = json.dumps(s, ensure_ascii=False)
    return str(s if s is not None else "").replace("\t", " ").replace("\r", " ").replace("\n", " ")


def walk(root, pred, tops=None):
    out = []
    bases = [os.path.join(root, t) for t in tops] if tops else [root]
    for base in bases:
        for dp, dns, fns in os.walk(base):
            dns[:] = sorted(d for d in dns if d not in SKIP_DIRS)
            for fn in fns:
                if pred(fn):
                    out.append(os.path.relpath(os.path.join(dp, fn), root))
    return sorted(out)


def load_json_lenient(path):
    raw = open(path, encoding="utf-8-sig", errors="replace").read()
    try:
        return json.loads(raw), "ok"
    except json.JSONDecodeError:
        pass
    t = re.sub(r'("(?:\\.|[^"\\])*")|//[^\n]*|/\*.*?\*/', lambda m: m.group(1) or "", raw, flags=re.S)
    t = re.sub(r",(\s*[}\]])", r"\1", t)
    try:
        return json.loads(t), "lenient(trailing comma/comment)"
    except json.JSONDecodeError as e:
        return None, f"invalid JSON: {e}"


def write_tsv(path, cols, rows):
    with open(path, "w", encoding="utf-8") as f:
        f.write("\t".join(cols) + "\n")
        for r in rows:
            f.write("\t".join(tsv(r.get(c, "")) for c in cols) + "\n")


def write_md(path, lines):
    Path(path).write_text("\n".join(lines) + "\n", encoding="utf-8")


# --------------------------------------------------------------------------- rules (*.Build.cs / *.Target.cs)
def parse_rules(args):
    root, rel = args
    try:
        classes = XCS.parse_rules_file(os.path.join(root, rel), rel)
        return rel, classes, ""
    except Exception as e:  # recorded, not fatal
        return rel, [], f"{type(e).__name__}: {e}"


def first_assign(stmts, target):
    for s in stmts:
        if s["kind"] == "assign" and s["target"] in (target, "this." + target) and s["op"] == "=":
            return s["expr"] + (f"  [if {s['cond']}]" if s["cond"] else "")
    return ""


def all_assigns(stmts, target):
    return [s["expr"] + (f" [if {s['cond']}]" if s["cond"] else "") for s in stmts
            if s["kind"] == "assign" and s["target"] in (target, "this." + target)]


def module_tier(rel):
    p = rel.split("/")
    if p[0] == "Source":
        return p[1] if len(p) > 2 else "Source"
    if p[0] in ("Plugins", "Platforms") and len(p) > 2:
        return p[0] + "/" + p[1]
    return p[0]


def nearest(rel_dir, table):
    d = rel_dir
    while d:
        if d in table:
            return table[d]
        d = os.path.dirname(d)
    return None


def build_modules(engine, pool, plugins_by_dir):
    files = walk(engine, lambda f: f.lower().endswith(".build.cs"), ("Source", "Plugins", "Platforms"))
    rows, fails = [], []
    for rel, classes, err in pool.imap(parse_rules, [(engine, f) for f in files], chunksize=8):
        if err or not classes:
            fails.append(dict(file=rel, why=err or "no rules class found"))
            stem = os.path.basename(rel)[:-len(".build.cs")]
            rows.append(dict(name=stem, file=rel, status="PARSE-FAILED " + (err or "no class")))
            continue
        mod_classes = [c for c in classes if "TargetRules" not in c["base"]]
        for c in classes:
            if c not in mod_classes:
                fails.append(dict(file=rel, why=f"class {c['name']} : {c['base']} is a TargetRules in a Build.cs "
                                                f"(listed in targets, not modules)"))
        for c in mod_classes:
            stmts = [s for ct in c["ctors"] for s in ct["stmts"]]
            mstmts = [s for mt in c.get("methods", []) for s in mt["stmts"]]
            lists = XCS.merged_lists(stmts + mstmts)
            stem = os.path.basename(rel)[:-len(".build.cs")] if rel.lower().endswith(".build.cs") else rel
            name = c["name"]
            d = os.path.dirname(rel)
            plug = nearest(d, plugins_by_dir)
            desc = {}
            if plug:
                for m in plug.get("Modules", []) or []:
                    if isinstance(m, dict) and m.get("Name") in (name, stem):
                        desc = m
                        break
            if len(mod_classes) > 1 and c["name"] != stem and any(x["name"] == stem for x in mod_classes):
                continue  # helper/base rules class sharing the file with the real module class
            row = dict(name=name, file=rel, dir=d, tier=module_tier(rel), base=c["base"],
                       thirdparty="yes" if "/ThirdParty/" in "/" + rel else "",
                       type=first_assign(stmts, "Type") or ("External" if "/ThirdParty/" in "/" + rel else "CPlusPlus"),
                       pch=first_assign(stmts, "PCHUsage"), precompile=first_assign(stmts, "PrecompileForTargets"),
                       short_name=first_assign(stmts, "ShortName"),
                       plugin=(plug or {}).get("_name", ""), plugin_file=(plug or {}).get("_file", ""),
                       desc_type=desc.get("Type", ""), desc_phase=desc.get("LoadingPhase", ""),
                       desc_lists={k: v for k, v in desc.items() if k not in ("Name", "Type", "LoadingPhase")},
                       ctors=len(c["ctors"]), stmts=len(stmts) + len(mstmts),
                       status="ok" if c["ctors"] else "no constructor parsed")
            if c["name"] != stem:
                row["status"] += f"; class name != file stem ({stem})"
            for p in DEP_PROPS:
                v = lists.get(p)
                row[SHORT[p]] = sorted(set(v["always"])) if v else []
                row[SHORT[p] + "_cond"] = [f"[{cnd}] {','.join(ns)}" for cnd, ns in v["cond"]] if v else []
            extras = {}
            for p, v in lists.items():
                if p not in DEP_PROPS and (v["always"] or v["cond"]):
                    extras[p] = len(v["always"]) + sum(len(n) for _, n in v["cond"])
            row["other_lists"] = extras
            rows.append(row)
    return rows, fails, files


def render_modules(ddir, rows, fails, nfiles):
    cols = ["name", "tier", "type", "thirdparty", "plugin", "desc_type", "desc_phase", "pch", "public", "private",
            "dynamic", "pub-include", "priv-include", "circular", "3p-static", "3p-dynamic", "public_cond",
            "private_cond", "dynamic_cond", "precompile", "short_name", "base", "file", "plugin_file", "desc_lists",
            "other_lists", "status"]
    write_tsv(ddir / "modules.tsv", cols, rows)
    tiers = Counter(r.get("tier", "?") for r in rows)
    types = Counter(re.sub(r"ModuleRules\.ModuleType\.|ModuleType\.", "", r.get("type", "")).split(" ")[0]
                    for r in rows)
    L = ["# Module dictionary (*.Build.cs)", "",
         f"- Build.cs files: {nfiles}; module rule classes: {len(rows)}; parse failures: {len(fails)}",
         "- by tier: " + ", ".join(f"{k}={v}" for k, v in sorted(tiers.items())),
         "- by Type: " + ", ".join(f"{k or '(default CPlusPlus)'}={v}" for k, v in sorted(types.items())),
         f"- third-party (External) modules: {sum(1 for r in rows if r.get('thirdparty'))}",
         f"- modules owned by a plugin: {sum(1 for r in rows if r.get('plugin'))}", "",
         "Columns: *Type* from `Type = ModuleType.X` (default CPlusPlus; ThirdParty dirs default External); "
         "*desc* = Type/LoadingPhase from the owning .uplugin `Modules[]` entry; dependency lists are the "
         "unconditional `Add`/`AddRange` names, conditional ones are listed with their `if` condition. "
         "Full machine-readable data incl. include-path and circular lists: `modules.tsv`.", ""]
    by_tier = defaultdict(list)
    for r in rows:
        by_tier[r.get("tier", "?")].append(r)
    for t in sorted(by_tier):
        L.append(f"\n## {t} ({len(by_tier[t])})\n")
        L.append("| module | Type | plugin (desc Type / LoadingPhase) | public deps | private deps | dynamic | "
                 "third-party | file |")
        L.append("|---|---|---|---|---|---|---|---|")
        for r in sorted(by_tier[t], key=lambda x: x["name"].lower()):
            ty = re.sub(r"ModuleRules\.ModuleType\.|ModuleType\.", "", r.get("type", ""))
            pl = r.get("plugin", "")
            if r.get("desc_type"):
                pl += f" ({r['desc_type']} / {r.get('desc_phase') or 'Default'})"
            pub = ", ".join(r.get("public", [])) + ("" if not r.get("public_cond") else
                                                    " · cond: " + "; ".join(r["public_cond"]))
            prv = ", ".join(r.get("private", [])) + ("" if not r.get("private_cond") else
                                                     " · cond: " + "; ".join(r["private_cond"]))
            dyn = ", ".join(r.get("dynamic", [])) + ("" if not r.get("dynamic_cond") else
                                                     " · cond: " + "; ".join(r["dynamic_cond"]))
            tp = ", ".join(r.get("3p-static", []) + r.get("3p-dynamic", []) +
                           [x for x in r.get("3p-static_cond", []) + r.get("3p-dynamic_cond", [])])
            st = "" if r.get("status") == "ok" else f" _{esc(r.get('status'))}_"
            L.append(f"| `{esc(r['name'])}` | {esc(ty)} | {esc(pl)} | {esc(pub)} | {esc(prv)} | {esc(dyn)} | "
                     f"{esc(tp)} | `{r['file']}`{st} |")
    if fails:
        L.append("\n## Parse failures\n")
        L += [f"- `{f['file']}`: {esc(f['why'])}" for f in fails]
    write_md(ddir / "modules.md", L)


# --------------------------------------------------------------------------- plugins
PLUGIN_SCALARS = ["FileVersion", "Version", "VersionName", "FriendlyName", "Description", "Category", "CreatedBy",
                  "CreatedByURL", "DocsURL", "MarketplaceURL", "SupportURL", "EngineVersion", "EnabledByDefault",
                  "CanContainContent", "CanContainVerse", "IsBetaVersion", "IsExperimentalVersion", "Installed",
                  "Hidden", "EditorOnly", "NoRedist", "ExplicitlyLoaded", "RequiresBuildPlatform",
                  "HasExplicitPlatforms", "SupportedTargetPlatforms", "SupportedPrograms", "PlatformAllowList",
                  "DeprecatedEngineVersion", "bIsPluginExtension", "VersePath", "VerseScope", "VerseVersion",
                  "BuiltInInitialFeatureState", "EditorCustomVirtualPath", "PluginIconPath", "NoCode"]
KNOWN_PLUGIN_FIELDS = set(PLUGIN_SCALARS) | {"Modules", "Plugins", "LocalizationTargets", "PythonRequirements",
                                             "PreBuildSteps", "PostBuildSteps", "DisallowedPlugins"}


def plugin_fields_from_source(ue):
    """Field names some reader actually looks up (Runtime/Projects FPluginDescriptor::Read, UBT PluginDescriptor.cs,
    plus the plugins that read the raw descriptor JSON); used to flag misspelled / dead fields."""
    names = set()
    for rel in ("Engine/Source/Programs/UnrealBuildTool/Configuration/Descriptors/PluginDescriptor.cs",
                "Engine/Source/Programs/UnrealBuildTool/Configuration/Descriptors/ModuleDescriptor.cs",
                "Engine/Source/Programs/UnrealBuildTool/Configuration/Descriptors/ProjectDescriptor.cs",
                "Engine/Source/Programs/UnrealBuildTool/Configuration/Descriptors/PluginReferenceDescriptor.cs",
                "Engine/Source/Programs/UnrealBuildTool/Configuration/Descriptors/CustomBuildSteps.cs",
                "Engine/Source/Programs/UnrealBuildTool/Configuration/Descriptors/LocalizationDescriptor.cs",
                "Engine/Source/Programs/UnrealBuildTool/Modes/PipInstallMode.cs"):
        try:
            t = open(os.path.join(ue, rel), encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        names.update(re.findall(r'"([A-Za-z_][A-Za-z0-9_]*)"', t))
    for rel in ("Engine/Plugins/Runtime/GameFeatures/Source/GameFeatures/Private/GameFeaturesSubsystem.cpp",
                "Engine/Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PipInstall.cpp"):
        try:
            t = open(os.path.join(ue, rel), encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        names.update(re.findall(r'(?:Field|Get\w*)\(\s*TEXT\("([A-Za-z_]\w*)"\)', t))
    for rel in ("Engine/Source/Runtime/Projects/Private/PluginDescriptor.cpp",
                "Engine/Source/Runtime/Projects/Private/ModuleDescriptor.cpp",
                "Engine/Source/Runtime/Projects/Private/PluginReferenceDescriptor.cpp",
                "Engine/Source/Runtime/Projects/Private/LocalizationDescriptor.cpp",
                "Engine/Source/Runtime/Projects/Private/CustomBuildSteps.cpp",
                "Engine/Source/Runtime/Projects/Private/ProjectDescriptor.cpp",
                "Engine/Source/Runtime/Projects/Private/PluginDisallowedDescriptor.cpp"):
        try:
            t = open(os.path.join(ue, rel), encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        names.update(re.findall(r'TEXT\("([A-Za-z_][A-Za-z0-9_]*)"\)', t))
    return names


def build_plugins(ue):
    files = walk(ue, lambda f: f.endswith(".uplugin"))
    readable = plugin_fields_from_source(ue)
    rows, mods, deps, by_dir = [], [], [], {}
    for rel in files:
        d, st = load_json_lenient(os.path.join(ue, rel))
        name = os.path.basename(rel)[:-len(".uplugin")]
        row = dict(name=name, file=rel, status=st, root=rel.split("/")[0])
        if d is None or not isinstance(d, dict):
            rows.append(row)
            continue
        for k in PLUGIN_SCALARS:
            if k in d:
                row[k] = d[k]
        unknown = sorted(k for k in d if k not in KNOWN_PLUGIN_FIELDS)
        unread = sorted(k for k in d if readable and k not in readable)
        row["unknown_fields"] = unknown
        row["fields_not_read"] = unread
        row["n_modules"] = len(d.get("Modules", []) or [])
        row["n_plugin_deps"] = len(d.get("Plugins", []) or [])
        row["LocalizationTargets"] = [x.get("Name", "") for x in d.get("LocalizationTargets", []) or []
                                      if isinstance(x, dict)]
        row["PythonRequirements"] = d.get("PythonRequirements", "")
        row["extra"] = {k: d[k] for k in unknown}
        parts = rel.split("/")
        row["group"] = "/".join(parts[:3]) if parts[0] == "Engine" else "/".join(parts[:2])
        rows.append(row)
        for m in d.get("Modules", []) or []:
            if not isinstance(m, dict):
                continue
            mr = dict(plugin=name, plugin_file=rel, module=m.get("Name", ""), Type=m.get("Type", ""),
                      LoadingPhase=m.get("LoadingPhase", ""))
            mr["lists"] = {k: v for k, v in m.items() if k not in ("Name", "Type", "LoadingPhase")}
            mods.append(mr)
        for p in d.get("Plugins", []) or []:
            if isinstance(p, dict):
                deps.append(dict(plugin=name, plugin_file=rel, dep=p.get("Name", ""), Enabled=p.get("Enabled", ""),
                                 Optional=p.get("Optional", ""),
                                 other={k: v for k, v in p.items() if k not in ("Name", "Enabled", "Optional")}))
        dd = dict(d)
        dd["_name"], dd["_file"] = name, rel
        if rel.startswith("Engine/"):
            by_dir[os.path.dirname(rel)[len("Engine/"):]] = dd
    return rows, mods, deps, by_dir, files


def render_plugins(ddir, rows, mods, deps, nfiles):
    cols = ["name", "FriendlyName", "Category", "Version", "VersionName", "EnabledByDefault", "IsBetaVersion",
            "IsExperimentalVersion", "CanContainContent", "Installed", "Hidden", "EditorOnly", "ExplicitlyLoaded",
            "NoRedist", "RequiresBuildPlatform", "SupportedTargetPlatforms", "SupportedPrograms", "PlatformAllowList",
            "n_modules", "n_plugin_deps", "LocalizationTargets", "PythonRequirements", "CreatedBy", "CreatedByURL",
            "DocsURL", "MarketplaceURL", "SupportURL", "FileVersion", "EngineVersion", "DeprecatedEngineVersion",
            "CanContainVerse", "VersePath", "VerseScope", "VerseVersion", "bIsPluginExtension",
            "BuiltInInitialFeatureState", "EditorCustomVirtualPath", "PluginIconPath", "NoCode", "HasExplicitPlatforms",
            "Description", "group", "file", "unknown_fields", "fields_not_read", "extra", "status"]
    write_tsv(ddir / "plugins.tsv", cols, rows)
    write_tsv(ddir / "plugin_modules.tsv", ["plugin", "module", "Type", "LoadingPhase", "lists", "plugin_file"], mods)
    write_tsv(ddir / "plugin_deps.tsv", ["plugin", "dep", "Enabled", "Optional", "other", "plugin_file"], deps)
    eng = [r for r in rows if r["file"].startswith("Engine/")]
    L = ["# Plugin dictionary (*.uplugin)", "",
         f"- .uplugin files: {nfiles} (Engine: {len(eng)}, Engine/Plugins: "
         f"{sum(r['file'].startswith('Engine/Plugins/') for r in rows)}, outside Engine: {nfiles - len(eng)})",
         f"- module descriptors: {len(mods)}; plugin dependency entries: {len(deps)}",
         f"- non-strict JSON (parsed leniently): {sum(1 for r in rows if r['status'] != 'ok')}",
         "- module Type: " + ", ".join(f"{k}={v}" for k, v in sorted(Counter(m['Type'] for m in mods).items())),
         "- LoadingPhase: " + ", ".join(f"{k or '(Default)'}={v}" for k, v in
                                       sorted(Counter(m['LoadingPhase'] for m in mods).items())),
         f"- descriptors with fields no reader looks up (Runtime/Projects, UBT descriptors, GameFeatures, "
         f"PythonScriptPlugin; likely misspelt or dead): "
         f"{sum(1 for r in rows if r.get('fields_not_read'))}", "",
         "All top-level fields are in `plugins.tsv`; module descriptors (incl. Platform/Target/Program allow/deny "
         "lists) in `plugin_modules.tsv`; dependencies in `plugin_deps.tsv`.", ""]
    mods_by = defaultdict(list)
    for m in mods:
        mods_by[m["plugin_file"]].append(m)
    deps_by = defaultdict(list)
    for p in deps:
        deps_by[p["plugin_file"]].append(p)
    groups = defaultdict(list)
    for r in rows:
        groups[r.get("group", r["file"].split("/")[0])].append(r)
    for g in sorted(groups):
        L.append(f"\n## {g} ({len(groups[g])})\n")
        L.append("| plugin | FriendlyName / Category | flags | modules (Type, LoadingPhase) | plugin deps | "
                 "description | file |")
        L.append("|---|---|---|---|---|---|---|")
        for r in sorted(groups[g], key=lambda x: x["name"].lower()):
            fl = []
            for k, lab in (("EnabledByDefault", "default-on"), ("IsBetaVersion", "beta"),
                           ("IsExperimentalVersion", "experimental"), ("Hidden", "hidden"), ("EditorOnly", "editor-only"),
                           ("ExplicitlyLoaded", "explicit"), ("CanContainContent", "content"), ("Installed", "installed"),
                           ("NoRedist", "noredist")):
                if r.get(k) is True:
                    fl.append(lab)
            if r.get("EnabledByDefault") is False:
                fl.append("default-off")
            if r.get("SupportedTargetPlatforms"):
                fl.append("platforms=" + ",".join(r["SupportedTargetPlatforms"]))
            if r.get("fields_not_read"):
                fl.append("**unread fields: " + ",".join(r["fields_not_read"]) + "**")
            if r["status"] != "ok":
                fl.append(r["status"])
            ms = "; ".join(f"{m['module']} ({m['Type']}, {m['LoadingPhase'] or 'Default'})"
                           + (" " + ",".join(f"{k}={v}" for k, v in m["lists"].items()) if m["lists"] else "")
                           for m in mods_by.get(r["file"], []))
            ds = ", ".join(p["dep"] + ("" if p["Enabled"] in (True, "") else "(disabled)") +
                           ("?" if p["Optional"] is True else "") for p in deps_by.get(r["file"], []))
            L.append(f"| `{esc(r['name'])}` | {esc(r.get('FriendlyName', ''))} / {esc(r.get('Category', ''))} | "
                     f"{esc(' '.join(fl))} | {esc(ms)} | {esc(ds)} | {esc(str(r.get('Description', ''))[:300])} | "
                     f"`{r['file']}` |")
    write_md(ddir / "plugins.md", L)


# --------------------------------------------------------------------------- targets
TARGET_KEYS = ["Type", "LinkType", "BuildEnvironment", "LaunchModuleName", "DefaultBuildSettings", "IncludeOrderVersion",
               "bBuildDeveloperTools", "bBuildWithEditorOnlyData", "bCompileAgainstEngine", "bCompileAgainstCoreUObject",
               "bCompileAgainstApplicationCore", "bCompileICU", "bIsBuildingConsoleApplication", "bUseMallocProfiler",
               "SolutionDirectory", "ExeBinariesSubFolder", "bLegalToDistributeBinary", "bUsesSlate",
               "bWithServerCode", "bCompileWithPluginSupport", "bBuildRequiresCookedData"]


def build_targets(ue, pool):
    files = walk(ue, lambda f: f.endswith(".Target.cs"))
    extra = walk(ue, lambda f: f.lower().endswith(".build.cs"))
    rows, fails = [], []
    jobs = [(ue, f) for f in files] + [(ue, f) for f in extra if "TargetRules" in
                                       open(os.path.join(ue, f), encoding="utf-8", errors="replace").read()]
    for rel, classes, err in pool.imap(parse_rules, jobs, chunksize=4):
        if not rel.endswith(".Target.cs"):
            classes = [c for c in classes if "TargetRules" in c["base"]]
            if not classes:
                continue
        if err or not classes:
            fails.append(dict(file=rel, why=err or "no rules class"))
            rows.append(dict(name=os.path.basename(rel)[:-len(".Target.cs")], file=rel, status="PARSE-FAILED"))
            continue
        for c in classes:
            stmts = [s for ct in c["ctors"] for s in ct["stmts"]]
            mstmts = [s for mt in c.get("methods", []) for s in mt["stmts"]]
            row = dict(name=c["name"], base=c["base"], file=rel, status="ok" if c["ctors"] else "no ctor parsed",
                       root=rel.split("/")[0])
            for k in TARGET_KEYS:
                v = all_assigns(stmts, k)
                row[k] = re.sub(r"^(TargetType|TargetLinkType|TargetBuildEnvironment|BuildSettingsVersion|"
                                r"EngineIncludeOrderVersion)\.", "", v[0]) if v else ""
                if len(v) > 1:
                    row[k] += f" (+{len(v) - 1} more)"
            lists = XCS.merged_lists(stmts + mstmts)
            row["ExtraModuleNames"] = (lists.get("ExtraModuleNames") or {}).get("always", [])
            row["EnablePlugins"] = (lists.get("EnablePlugins") or {}).get("always", [])
            row["DisablePlugins"] = (lists.get("DisablePlugins") or {}).get("always", [])
            row["GlobalDefinitions"] = (lists.get("GlobalDefinitions") or {}).get("always", [])
            row["statements"] = [f"L{s['line']} {s['target']} {s['op'] or '()'} {s['expr'][:160]}"
                                 + (f" [if {s['cond']}]" if s["cond"] else "") for s in stmts + mstmts]
            rows.append(row)
    return rows, fails, files


def render_targets(ddir, rows, fails, nfiles):
    cols = ["name", "base", "Type", "LinkType", "BuildEnvironment", "LaunchModuleName", "DefaultBuildSettings",
            "IncludeOrderVersion"] + TARGET_KEYS[6:] + ["ExtraModuleNames", "EnablePlugins", "DisablePlugins",
                                                       "GlobalDefinitions", "file", "status", "statements"]
    write_tsv(ddir / "targets.tsv", cols, rows)
    L = ["# Target dictionary (*.Target.cs)", "",
         f"- Target.cs files: {nfiles} (Engine: {sum(r['file'].startswith('Engine/') for r in rows)}); "
         f"target classes: {len(rows)}; parse failures: {len(fails)}",
         "- by Type: " + ", ".join(f"{k or '(unset/inherited)'}={v}" for k, v in
                                  sorted(Counter(r.get('Type', '') for r in rows).items())), "",
         "Every assignment/call of the constructor is listed under the table (`targets.tsv` column *statements*).", ""]
    by_root = defaultdict(list)
    for r in rows:
        p = r["file"].split("/")
        by_root["/".join(p[:3]) if p[0] == "Engine" else "/".join(p[:2])].append(r)
    for g in sorted(by_root):
        L.append(f"\n## {g} ({len(by_root[g])})\n")
        L.append("| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |")
        L.append("|---|---|---|---|---|---|---|---|")
        for r in sorted(by_root[g], key=lambda x: x["name"].lower()):
            L.append(f"| `{esc(r['name'])}` | {esc(r.get('base'))} | {esc(r.get('Type'))} | {esc(r.get('LinkType'))} | "
                     f"{esc(r.get('BuildEnvironment'))} | {esc(r.get('LaunchModuleName'))} | "
                     f"{esc(', '.join(r.get('ExtraModuleNames', [])))} | `{r['file']}` |")
    L.append("\n## Constructor statements\n")
    for r in sorted(rows, key=lambda x: x["file"]):
        L.append(f"\n### `{esc(r['name'])}` — `{r['file']}`\n")
        for s in r.get("statements", []) or ["_(no statements parsed)_"]:
            L.append(f"- `{esc(s)}`")
    if fails:
        L.append("\n## Parse failures\n")
        L += [f"- `{f['file']}`: {esc(f['why'])}" for f in fails]
    write_md(ddir / "targets.md", L)


# --------------------------------------------------------------------------- projects
def build_projects(ue):
    files = walk(ue, lambda f: f.endswith(".uproject"))
    rows = []
    for rel in files:
        d, st = load_json_lenient(os.path.join(ue, rel))
        row = dict(name=os.path.basename(rel)[:-len(".uproject")], file=rel, status=st)
        if isinstance(d, dict):
            for k in ("FileVersion", "EngineAssociation", "Category", "Description", "TargetPlatforms",
                      "DisableEnginePluginsByDefault", "AdditionalRootDirectories", "AdditionalPluginDirectories",
                      "Enterprise", "IsEnterpriseProject"):
                if k in d:
                    row[k] = d[k]
            row["Modules"] = [f"{m.get('Name')}({m.get('Type', '')},{m.get('LoadingPhase', 'Default')})"
                              for m in d.get("Modules", []) or [] if isinstance(m, dict)]
            row["PluginsEnabled"] = [p.get("Name") for p in d.get("Plugins", []) or []
                                     if isinstance(p, dict) and p.get("Enabled", True)]
            row["PluginsDisabled"] = [p.get("Name") for p in d.get("Plugins", []) or []
                                      if isinstance(p, dict) and not p.get("Enabled", True)]
            row["other_fields"] = sorted(set(d) - {"FileVersion", "EngineAssociation", "Category", "Description",
                                                   "TargetPlatforms", "Modules", "Plugins",
                                                   "DisableEnginePluginsByDefault", "AdditionalRootDirectories",
                                                   "AdditionalPluginDirectories", "Enterprise", "IsEnterpriseProject"})
        rows.append(row)
    return rows, files


def render_projects(ddir, rows):
    cols = ["name", "Category", "Description", "EngineAssociation", "FileVersion", "TargetPlatforms", "Modules",
            "PluginsEnabled", "PluginsDisabled", "DisableEnginePluginsByDefault", "AdditionalRootDirectories",
            "AdditionalPluginDirectories", "Enterprise", "other_fields", "file", "status"]
    write_tsv(ddir / "projects.tsv", cols, rows)
    L = ["# Project dictionary (*.uproject)", "", f"- .uproject files: {len(rows)} (Samples / Templates; the Engine "
         "itself ships none)", "",
         "| project | Category | modules | plugins enabled | plugins disabled | target platforms | description | file |",
         "|---|---|---|---|---|---|---|---|"]
    for r in sorted(rows, key=lambda x: x["file"]):
        L.append(f"| `{esc(r['name'])}` | {esc(r.get('Category', ''))} | {esc(', '.join(r.get('Modules', [])))} | "
                 f"{esc(', '.join(r.get('PluginsEnabled', [])))} | {esc(', '.join(r.get('PluginsDisabled', [])))} | "
                 f"{esc(', '.join(r.get('TargetPlatforms', []) or []))} | {esc(str(r.get('Description', ''))[:200])} | "
                 f"`{r['file']}` |")
    write_md(ddir / "projects.md", L)


# --------------------------------------------------------------------------- config ini
def build_config(engine):
    files = walk(engine, lambda f: f.lower().endswith(".ini"))
    files = [f for f in files if "/ThirdParty/" not in "/" + f]
    secs, keys = [], []
    for rel in files:
        try:
            lines = open(os.path.join(engine, rel), encoding="utf-8-sig", errors="replace").read().splitlines()
        except OSError as e:
            secs.append(dict(file=rel, section="(unreadable)", keys=0, status=str(e)))
            continue
        cur, cur_line, n, sk = "(no section)", 0, 0, Counter()
        def flush():
            if n or cur != "(no section)":
                secs.append(dict(file=rel, section=cur, line=cur_line, keys=n, distinct=len(sk),
                                 sample=", ".join(list(sk)[:12])))
        for i, l in enumerate(lines, 1):
            s = l.strip()
            if not s or s.startswith(";") or s.startswith("#"):
                continue
            if s.startswith("[") and s.endswith("]"):
                flush()
                cur, cur_line, n, sk = s[1:-1], i, 0, Counter()
                continue
            m = re.match(r"([+\-.!@*]?)([^=]+?)\s*=\s*(.*)$", s)
            if m:
                op, k, v = m.groups()
            else:
                op, k, v = "", s, ""
            n += 1
            sk[k.strip()] += 1
            keys.append(dict(file=rel, line=i, section=cur, op=op, key=k.strip(), value=v[:400]))
        flush()
        if not any(x["file"] == rel for x in secs[-max(1, len(sk) + 1):]) and not any(x["file"] == rel for x in secs):
            secs.append(dict(file=rel, section="(no sections: empty or comments only)", line=0, keys=0, distinct=0,
                             sample=""))
    return secs, keys, files


def config_layer(rel):
    p = rel.split("/")
    b = p[-1]
    if p[0] == "Config":
        if len(p) == 2:
            return "Engine base" if b.startswith("Base") or b in ("ConsoleVariables.ini", "ConfigRedirects.ini") \
                else "Engine"
        return f"Engine platform ({p[1]})"
    return p[0] + (" (plugin)" if p[0] == "Plugins" else "")


def render_config(ddir, secs, keys, files):
    write_tsv(ddir / "config.tsv", ["file", "section", "line", "keys", "distinct", "sample"], secs)
    write_tsv(ddir / "config_keys.tsv", ["file", "line", "section", "op", "key", "value"], keys)
    per_file = defaultdict(list)
    for s in secs:
        per_file[s["file"]].append(s)
    L = ["# Config dictionary (*.ini)", "",
         f"- ini files under Engine (ThirdParty excluded): {len(files)}; sections: {len(secs)}; key lines: {len(keys)}",
         f"- distinct section names: {len({s['section'] for s in secs})}", "",
         "Engine config hierarchy (FConfigCacheIni): Base.ini → Base<Cat>.ini → Platform/<Plat><Cat>.ini → "
         "project Default<Cat>.ini → … Engine-side layers are listed here; every key line is in `config_keys.tsv`.", ""]
    by_layer = defaultdict(list)
    for f in files:
        by_layer[config_layer(f)].append(f)
    for layer in sorted(by_layer):
        L.append(f"\n## {layer} ({len(by_layer[layer])} files)\n")
        for f in sorted(by_layer[layer]):
            ss = per_file.get(f, [])
            L.append(f"\n### `{f}` — {len(ss)} sections, {sum(s['keys'] for s in ss)} keys\n")
            if not ss:
                L.append("_(empty)_")
                continue
            L.append("| section | line | keys | sample keys |")
            L.append("|---|---|---|---|")
            for s in ss:
                L.append(f"| `{esc(s['section'])}` | {s.get('line', '')} | {s['keys']} | {esc(s.get('sample', ''))[:300]} |")
    write_md(ddir / "config.md", L)


# --------------------------------------------------------------------------- UCLASS(config=...)
UCLASS_RE = re.compile(r"\bUCLASS\s*\(")
UPROP_RE = re.compile(r"\bUPROPERTY\s*\(")


def scan_uclass_config(args):
    engine, rel = args
    out = []
    try:
        text = open(os.path.join(engine, rel), encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
    except OSError as e:
        return out, [dict(file=rel, why=str(e))]
    if not re.search(r"\b[Cc]onfig\s*=", text):
        return out, []
    nc, cd = mask(text)
    starts = line_starts(text)
    errs = []
    for m in UCLASS_RE.finditer(cd):
        o = m.end() - 1
        e = match_close(cd, o, "(", ")", min(len(cd), o + 5000))
        if e < 0:
            errs.append(dict(file=rel, why=f"L{lineno(starts, m.start())}: unbalanced UCLASS("))
            continue
        spec = re.sub(r"\s+", " ", nc[o + 1:e])
        cm = re.search(r"\b[Cc]onfig\s*=\s*\"?(\w+)", spec)
        if not cm:
            continue
        hm = re.compile(r"\s*(?:class|struct)\s+(?:UE_DEPRECATED\s*\([^()]*\)\s*)?(?:\w+_API\s+)?(\w+)\s*"
                        r"(?:final\s*)?(?::\s*([^{]+))?\{").match(cd, e + 1)
        if not hm:
            errs.append(dict(file=rel, why=f"L{lineno(starts, m.start())}: class head after UCLASS not found"))
            continue
        bo = hm.end() - 1
        be = match_close(cd, bo, "{", "}")
        props = []
        if be > 0:
            for pm in UPROP_RE.finditer(cd, bo, be):
                po = pm.end() - 1
                pe = match_close(cd, po, "(", ")", be)
                if pe < 0:
                    continue
                pspec = re.sub(r"\s+", " ", nc[po + 1:pe])
                if not re.search(r"\b(GlobalConfig|Config)\b", pspec):
                    continue
                semi = cd.find(";", pe)
                decl = re.sub(r"\s+", " ", nc[pe + 1:semi]).strip() if semi > 0 else ""
                decl = re.sub(r"\s*=.*$", "", decl)
                props.append(dict(decl=decl[:160], global_="GlobalConfig" in pspec,
                                  line=lineno(starts, pm.start())))
        base = re.sub(r"\s+", " ", (hm.group(2) or "")).strip()
        base = re.sub(r"\bpublic\s+", "", base)
        flags = [f for f in ("DefaultConfig", "GlobalUserConfig", "ProjectUserConfig", "PerObjectConfig",
                             "PerPlatformConfig", "Abstract") if re.search(r"\b" + f + r"\b", spec)]
        em = re.search(r"\bEditorConfig\s*=\s*\"?([\w.]+)", spec)
        out.append(dict(cls=hm.group(1), base=base[:120], config=cm.group(1), flags=flags,
                        editor_config=em.group(1) if em else "", file=rel, line=lineno(starts, m.start()),
                        props=props, spec=spec[:300]))
    return out, errs


def build_uclass_config(engine, pool, mods_by_dir):
    files = walk(engine, lambda f: f.endswith((".h", ".hpp")), ("Source", "Plugins", "Platforms"))
    files = [f for f in files if "/ThirdParty/" not in "/" + f]
    rows, errs = [], []
    for o, e in pool.imap_unordered(scan_uclass_config, [(engine, f) for f in files], chunksize=64):
        rows += o
        errs += e
    for r in rows:
        r["module"] = nearest(os.path.dirname(r["file"]), mods_by_dir) or ""
        r["n_props"] = len(r["props"])
        r["n_global"] = sum(p["global_"] for p in r["props"])
        r["prop_list"] = [("G " if p["global_"] else "") + p["decl"] for p in r["props"]]
    rows.sort(key=lambda x: (x["config"], x["cls"]))
    return rows, errs, len(files)


def render_uclass_config(ddir, rows, errs, nfiles):
    write_tsv(ddir / "uclass_config.tsv", ["cls", "config", "flags", "editor_config", "base", "module", "n_props",
                                           "n_global", "prop_list", "file", "line", "spec"], rows)
    L = ["# UCLASS(config=...) dictionary", "",
         f"- headers scanned: {nfiles}; UCLASSes with config=: {len(rows)}; Config/GlobalConfig UPROPERTYs: "
         f"{sum(r['n_props'] for r in rows)}; scan problems: {len(errs)}",
         "- by config file: " + ", ".join(f"{k}={v}" for k, v in sorted(Counter(r['config'] for r in rows).items(),
                                                                         key=lambda x: -x[1])), "",
         "Section name in ini is `[/Script/<Module>.<ClassWithoutPrefix>]` (PerObjectConfig: `[<ObjName> <Class>]`). "
         "`G` marks GlobalConfig properties.", ""]
    by_cfg = defaultdict(list)
    for r in rows:
        by_cfg[r["config"]].append(r)
    for c in sorted(by_cfg, key=lambda k: -len(by_cfg[k])):
        L.append(f"\n## config={c} ({len(by_cfg[c])})\n")
        L.append("| class | ini section | flags | base | config properties | file:line |")
        L.append("|---|---|---|---|---|---|")
        for r in by_cfg[c]:
            sec = f"/Script/{r['module']}.{r['cls'][1:] if r['cls'][:1] in 'UA' else r['cls']}" if r["module"] else ""
            fl = " ".join(r["flags"]) + (f" EditorConfig={r['editor_config']}" if r["editor_config"] else "")
            props = "; ".join(r["prop_list"][:60]) + (f" … (+{len(r['prop_list']) - 60})" if len(r["prop_list"]) > 60 else "")
            L.append(f"| `{esc(r['cls'])}` | `{esc(sec)}` | {esc(fl)} | {esc(r['base'])} | {esc(props)} | "
                     f"`{r['file']}:{r['line']}` |")
    if errs:
        L.append("\n## Scan problems\n")
        L += [f"- `{e['file']}`: {esc(e['why'])}" for e in errs]
    write_md(ddir / "uclass_config.md", L)


# --------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ue", default=UE)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--jobs", type=int, default=14)
    a = ap.parse_args()
    ue = a.ue
    engine = os.path.join(ue, "Engine")
    ddir = Path(a.out) / "dictionary"
    ddir.mkdir(parents=True, exist_ok=True)
    rep = {}
    with Pool(min(a.jobs, 14)) as pool:
        prow, pmods, pdeps, by_dir, pfiles = build_plugins(ue)
        render_plugins(ddir, prow, pmods, pdeps, len(pfiles))
        rep["plugins"] = dict(files=len(pfiles), modules=len(pmods), deps=len(pdeps),
                              lenient=[r["file"] for r in prow if r["status"] != "ok"],
                              unread_fields={r["file"]: r["fields_not_read"] for r in prow
                                             if r.get("fields_not_read")})
        mrows, mfails, mfiles = build_modules(engine, pool, by_dir)
        render_modules(ddir, mrows, mfails, len(mfiles))
        rep["modules"] = dict(files=len(mfiles), rows=len(mrows), failures=mfails)
        mods_by_dir = {r["dir"]: r["name"] for r in mrows if r.get("dir") is not None}
        trows, tfails, tfiles = build_targets(ue, pool)
        render_targets(ddir, trows, tfails, len(tfiles))
        rep["targets"] = dict(files=len(tfiles), rows=len(trows), failures=tfails)
        jrows, jfiles = build_projects(ue)
        render_projects(ddir, jrows)
        rep["projects"] = dict(files=len(jfiles), lenient=[r["file"] for r in jrows if r["status"] != "ok"])
        secs, keys, cfiles = build_config(engine)
        render_config(ddir, secs, keys, cfiles)
        rep["config"] = dict(files=len(cfiles), sections=len(secs), keys=len(keys))
        urows, uerrs, nh = build_uclass_config(engine, pool, mods_by_dir)
        render_uclass_config(ddir, urows, uerrs, nh)
        rep["uclass_config"] = dict(headers=nh, classes=len(urows), props=sum(r["n_props"] for r in urows),
                                    errors=uerrs)
    rep["file_lists"] = dict(uplugin=pfiles, build_cs=mfiles, target_cs=tfiles, uproject=jfiles, ini=cfiles)
    (ddir / "catalog_report.json").write_text(json.dumps(rep, indent=1), encoding="utf-8")
    print(json.dumps({k: {kk: (len(vv) if isinstance(vv, (list, dict)) else vv) for kk, vv in v.items()}
                      for k, v in rep.items() if k != "file_lists"}))


if __name__ == "__main__":
    main()
