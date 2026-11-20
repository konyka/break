#!/usr/bin/env python3
"""Write ANGLE and SwiftShader configurations for an explicit QNX target path."""

import argparse
import json
from pathlib import Path
import re


def stage_angle_configs(output, target_root):
    target_root = target_root.rstrip("/")
    if not target_root.startswith("/") or re.search(r"[^A-Za-z0-9_./-]", target_root):
        raise ValueError(f"invalid ANGLE target root: {target_root}")
    output.mkdir(parents=True, exist_ok=True)
    (output / "angle").mkdir(exist_ok=True)
    manifest = {
        "file_format_version": "1.0.0",
        "ICD": {
            "library_path": target_root + "/swiftshader/libvk_swiftshader.so",
            "api_version": "1.3.0",
        },
    }
    manifest_text = json.dumps(manifest, indent=2) + "\n"
    for path in (output / "vk_swiftshader_icd.json",
                 output / "angle/vk_swiftshader_icd.json"):
        path.write_text(manifest_text, encoding="utf-8")
    (output / "graphics.conf").write_text(
        "begin khronos\n"
        "  begin egl display 1\n"
        f"    egl-dlls = {target_root}/angle/libEGL.so\n"
        f"    glesv2-dlls = {target_root}/angle/libGLESv2.so\n"
        f"    vk-icds = {target_root}/angle/vk_swiftshader_icd.json\n"
        "  end egl display\n"
        "end khronos\n", encoding="utf-8")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--target-root", required=True)
    args = parser.parse_args()
    stage_angle_configs(args.output, args.target_root)


if __name__ == "__main__":
    main()
