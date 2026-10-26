#!/usr/bin/env python3
"""Stage the QNX Screen software runtime and its ELF dependency closure.

This does not install a Vulkan ICD or claim GPU support. The generated tree
contains the virtual-display configuration for native-window validation.
"""

import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--qnx-target", default=os.environ.get("QNX_TARGET"))
    parser.add_argument("--qnx-host", default=os.environ.get("QNX_HOST"))
    parser.add_argument("--arch", default="x86_64",
                        choices=("x86_64", "aarch64le", "armle"))
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--config", default="virtual-display",
                        choices=("virtual-display", "headless"))
    args = parser.parse_args()
    if not args.qnx_target or not args.qnx_host:
        parser.error("set QNX_TARGET/QNX_HOST or pass --qnx-target/--qnx-host")

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
    print(f"configuration: {args.config}; no Vulkan ICD is installed by this tool")


if __name__ == "__main__":
    main()
