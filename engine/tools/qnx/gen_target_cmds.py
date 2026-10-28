#!/usr/bin/env python3
"""gen_target_cmds.py — QNX on-target suite: generate the command list.

Reads the ctest test registry of a QNX cross build dir and emits one command
per runnable headless test, rewritten for the on-target deployment layout:

  - keeps tests whose command[0] is a built ELF binary (drops cmake -P
    script tests, which need the host CMake runtime)
  - drops graphics/fuzz-labelled tests
  - prefixes WILL_FAIL tests with EXPECT_FAIL (run_target_suite.sh treats a
    nonzero exit as the pass condition for those)
  - rewrites the build dir to '.' (run from the binary directory) and the
    source root to the on-target copy

Usage:
  gen_target_cmds.py <build-dir> <repo-root> <target-source-root> <out-file>
Example:
  gen_target_cmds.py /tmp/build-qnx /path/to/engine /tmp/bt cmds.txt
"""

import json
import os
import subprocess
import sys


def main():
    if len(sys.argv) != 5:
        print(__doc__)
        return 2
    build, repo, target_root, out_path = sys.argv[1:5]

    info = json.loads(subprocess.run(
        ["ctest", "--test-dir", build, "-N", "-LE", "graphics|fuzz",
         "--show-only", "json-v1"],
        capture_output=True, text=True, check=True).stdout)

    lines = []
    for t in info["tests"]:
        labels = [l for l in t.get("labels", []) if l not in ("headless",)]
        if any(l in ("graphics", "fuzz") for l in labels):
            continue
        cmd = t.get("command") or []
        if not cmd:
            continue
        exe = cmd[0]
        if os.path.basename(exe) == "cmake":
            continue  # cmake -P contract tests need the host CMake runtime
        if not os.path.isfile(exe) or not os.access(exe, os.X_OK):
            continue
        with open(exe, "rb") as fh:
            if fh.read(4) != b"\x7fELF":
                continue
        parts = ["./" + os.path.basename(exe)]
        for arg in cmd[1:]:
            arg = arg.replace(build, ".")
            arg = arg.replace(repo, target_root)
            parts.append(arg)
        line = " ".join(parts)
        will_fail = any(p.get("name") == "WILL_FAIL" and p.get("value")
                        for p in t.get("properties", []))
        if will_fail:
            line = "EXPECT_FAIL " + line
        lines.append(line)

    seen = set()
    with open(out_path, "w") as fh:
        for line in lines:
            if line in seen:
                continue
            seen.add(line)
            fh.write(line + "\n")
    print(f"{len(seen)} commands -> {out_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
