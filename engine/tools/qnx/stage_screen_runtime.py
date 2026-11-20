#!/usr/bin/env python3
"""Stage QNX Screen and optional Vulkan or sanitizer runtime files.

No Vulkan ICD is installed unless all Vulkan inputs are provided. The generated
tree contains the virtual-display configuration and never implies physical GPU
support; an explicitly staged SwiftShader ICD remains a software renderer.
Sanitizer inputs use the SDP 8.0 SONAMEs and include their ELF dependency closure.
"""

import argparse
import json
import os
from pathlib import Path
import re
import shutil
import subprocess


ARCH_ELF = {
    "x86_64": (2, 62),
    "aarch64le": (2, 183),
    "armle": (1, 40),
}


def validate_elf(path, arch):
    data = path.read_bytes()[:20]
    if len(data) < 20 or data[:4] != b"\x7fELF" or data[5] != 1:
        raise RuntimeError(f"not a little-endian ELF file: {path}")
    expected_class, expected_machine = ARCH_ELF[arch]
    if data[4] != expected_class or int.from_bytes(data[18:20], "little") != expected_machine:
        raise RuntimeError(f"ELF architecture is not {arch}: {path}")


def stage_vulkan_runtime(args, root, readelf, candidates):
    target_root = args.vulkan_target_root.rstrip("/")
    if not target_root.startswith("/") or re.search(r"[^A-Za-z0-9_./-]", target_root):
        raise RuntimeError(f"invalid Vulkan target root: {args.vulkan_target_root}")
    target_runtime = target_root + "/swiftshader"
    output = args.output
    runtime = Path("swiftshader")
    inputs = (
        (args.vulkan_icd, runtime / "libvk_swiftshader.so"),
        (args.vulkan_loader, Path("usr/lib/libvulkan.so.1")),
        (args.vulkan_redirect, runtime / "libgraphics_conf_redirect.so"),
        (args.shaderc, runtime / "libshaderc_shared.so.1"),
    )
    destinations = {}
    names = {}
    for source, destination in inputs:
        source = source.resolve()
        if not source.is_file():
            raise RuntimeError(f"missing Vulkan runtime input: {source}")
        destinations[source] = destination
        names[source.name] = source

    queue = list(destinations)
    seen = set()
    while queue:
        source = queue.pop(0)
        if source in seen:
            continue
        validate_elf(source, args.arch)
        destination = destinations[source]
        staged = output / destination
        staged.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, staged)
        seen.add(source)

        dynamic = subprocess.check_output([readelf, "-d", source], text=True)
        for dependency_name in re.findall(r"Shared library: \[(.*?)\]", dynamic):
            dependency = names.get(dependency_name) or candidates.get(dependency_name)
            if dependency is None:
                raise RuntimeError(
                    f"missing Vulkan runtime dependency {dependency_name} required by {source}")
            dependency = dependency.resolve()
            names[dependency_name] = dependency
            destinations.setdefault(dependency, runtime / "lib" / dependency_name)
            queue.append(dependency)

    manifest = json.loads(args.vulkan_icd_manifest.read_text(encoding="utf-8"))
    if not isinstance(manifest.get("ICD"), dict) or "api_version" not in manifest["ICD"]:
        raise RuntimeError(f"invalid Vulkan ICD manifest: {args.vulkan_icd_manifest}")
    manifest["ICD"]["library_path"] = target_runtime + "/libvk_swiftshader.so"
    manifest_path = output / runtime / "swiftshader_icd.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")

    config_lines = args.vulkan_graphics_config.read_text(encoding="utf-8").splitlines()
    replacements = 0
    for index, line in enumerate(config_lines):
        stripped = line.lstrip()
        if stripped.startswith("vk-icds") and not stripped.startswith("#"):
            indent = line[:len(line) - len(stripped)]
            config_lines[index] = indent + "vk-icds = " + target_runtime + "/swiftshader_icd.json"
            replacements += 1
    if replacements != 1:
        raise RuntimeError(
            f"expected one vk-icds entry in {args.vulkan_graphics_config}")
    (output / runtime / "graphics.conf").write_text(
        "\n".join(config_lines) + "\n", encoding="utf-8")
    return len(seen)


def stage_sanitizer_runtime(output, arch, root, readelf, candidates, use_asan, use_ubsan,
                            cleanup=None):
    requested = []
    if use_asan:
        requested.append((root / "lib/libasan.so.8.0.0",
                          "libasan.so.8.0.0", "libasan.so.8"))
    if use_ubsan:
        requested.append((root / "lib/libubsan.so.1.0.0",
                          "libubsan.so.1.0.0", "libubsan.so.1"))
    if cleanup is not None:
        requested.append((cleanup, cleanup.name, None))
    if not requested:
        return 0

    output.mkdir(parents=True, exist_ok=True)
    queue = list(requested)
    seen = set()
    while queue:
        source, output_name, link_name = queue.pop(0)
        if output_name in seen:
            continue
        if not source.is_file():
            raise RuntimeError(f"missing sanitizer runtime input: {source}")
        validate_elf(source, arch)
        dynamic = subprocess.check_output([readelf, "-d", source], text=True)
        shutil.copy2(source, output / output_name)
        if link_name is not None:
            link = output / link_name
            if link.exists() or link.is_symlink():
                if not link.is_symlink() or link.readlink() != Path(output_name):
                    raise RuntimeError(f"sanitizer SONAME link conflicts with an existing file: {link}")
            else:
                link.symlink_to(output_name)
        seen.add(output_name)

        for dependency_name in re.findall(r"Shared library: \[(.*?)\]", dynamic):
            dependency = candidates.get(dependency_name)
            if dependency is None:
                raise RuntimeError(
                    f"missing sanitizer dependency {dependency_name} required by {source}")
            queue.append((dependency.resolve(), dependency_name, None))
    return len(seen)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--qnx-target", default=os.environ.get("QNX_TARGET"))
    parser.add_argument("--qnx-host", default=os.environ.get("QNX_HOST"))
    parser.add_argument("--arch", default="x86_64",
                        choices=("x86_64", "aarch64le", "armle"))
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--config", default="virtual-display",
                        choices=("virtual-display", "headless"))
    parser.add_argument("--vulkan-icd", type=Path)
    parser.add_argument("--vulkan-loader", type=Path)
    parser.add_argument("--vulkan-redirect", type=Path)
    parser.add_argument("--shaderc", type=Path)
    parser.add_argument("--vulkan-icd-manifest", type=Path)
    parser.add_argument("--vulkan-graphics-config", type=Path)
    parser.add_argument("--vulkan-target-root", default="/var/bt")
    parser.add_argument("--asan", action="store_true",
                        help="stage the SDP 8.0 ASan runtime and its ELF dependencies")
    parser.add_argument("--ubsan", action="store_true",
                        help="stage the SDP 8.0 UBSan runtime and its ELF dependencies")
    parser.add_argument("--sanitizer-cleanup", type=Path,
                        help="stage the test-only QNX ASan cleanup helper")
    args = parser.parse_args()
    if not args.qnx_target or not args.qnx_host:
        parser.error("set QNX_TARGET/QNX_HOST or pass --qnx-target/--qnx-host")
    vulkan_options = (
        args.vulkan_icd, args.vulkan_loader, args.vulkan_redirect, args.shaderc,
        args.vulkan_icd_manifest, args.vulkan_graphics_config,
    )
    if any(option is not None for option in vulkan_options) and not all(
            option is not None for option in vulkan_options):
        parser.error(
            "Vulkan runtime requires --vulkan-icd, --vulkan-loader, "
            "--vulkan-redirect, --shaderc, --vulkan-icd-manifest, and "
            "--vulkan-graphics-config together")

    target = Path(args.qnx_target).resolve()
    host = Path(args.qnx_host).resolve()
    root = target / args.arch
    readelf_name = {
        "x86_64": "ntox86_64-readelf",
        "aarch64le": "ntoaarch64-readelf",
        "armle": "ntoarm-readelf",
    }[args.arch]
    readelf = host / "usr/bin" / readelf_name
    config = target / "usr/share/screen" / f"graphics-{args.config}.conf"
    for required in (root, readelf, config):
        if not required.exists():
            parser.error(f"missing QNX SDP input: {required}")

    candidates = {}
    for relative in ("lib", "usr/lib", "lib/dll", "usr/lib/dll"):
        directory = root / relative
        if directory.is_dir():
            for path in directory.iterdir():
                if path.is_file() or path.is_symlink():
                    candidates[path.name] = path

    queue = [
        "sbin/screen",
        "usr/bin/vulkaninfo",
        "usr/lib/libscreen.so.1",
        "lib/dll/screen-sw.so",
        "lib/dll/screen-stdbuf.so",
    ]
    seen = set()
    while queue:
        relative = queue.pop()
        name = Path(relative).name
        if relative in seen or name.startswith(
                ("libc.so", "libgcc_s.so", "libm.so", "libsocket.so")):
            continue
        source = root / relative
        if not source.is_file():
            source = candidates.get(name)
        if source is None:
            raise RuntimeError(f"missing Screen runtime dependency: {relative}")
        seen.add(relative)
        destination = args.output / relative
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source.resolve(), destination)
        dynamic = subprocess.check_output([readelf, "-d", source], text=True)
        for dependency_name in re.findall(r"Shared library: \[(.*?)\]", dynamic):
            dependency = candidates.get(dependency_name)
            if dependency is not None:
                queue.append(str(dependency.relative_to(root)))

    shutil.copy2(config, args.output / config.name)
    print(f"staged {len(seen)} Screen runtime files in {args.output}")
    if args.vulkan_icd:
        count = stage_vulkan_runtime(args, root, readelf, candidates)
        print(f"staged {count} Vulkan runtime ELF files in {args.output}")
        print("Vulkan runtime: explicit SwiftShader software ICD; no physical GPU is implied")
    else:
        print(f"configuration: {args.config}; no Vulkan ICD is installed by this tool")
    if args.asan or args.ubsan:
        count = stage_sanitizer_runtime(
            args.output, args.arch, root, readelf, candidates,
            use_asan=args.asan, use_ubsan=args.ubsan,
            cleanup=args.sanitizer_cleanup)
        print(f"staged {count} sanitizer runtime ELF files in {args.output}")


if __name__ == "__main__":
    main()
