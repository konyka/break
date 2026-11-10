#!/usr/bin/env python3
import os
from pathlib import Path
import stat
import subprocess
import sys

BASH = ""


def validation_script(workflow):
    try:
        section = workflow.split("- name: Validate supported rollback tag", 1)[1]
        block = section.split("run: |", 1)[1]
    except IndexError as exc:
        raise RuntimeError("missing Validate supported rollback tag run block") from exc
    lines = []
    for line in block.splitlines()[1:]:
        if line.startswith("          "):
            lines.append(line[10:])
        elif not line.strip():
            lines.append("")
        else:
            break
    return "\n".join(lines) + "\n"


def run_tag_script(script, tag, work):
    marker = work / "injected-side-effect"
    marker.unlink(missing_ok=True)
    env = dict(os.environ)
    env["TAG"] = tag
    env["GITHUB_STEP_SUMMARY"] = str(work / "summary.md")
    env["ROLLBACK_TEST_MARKER"] = str(marker)
    env["PATH"] = f"{work / 'stock-bin'}{os.pathsep}{env['PATH']}"
    direct = "${{ inputs.tag }}" in script
    if direct:
        script = script.replace("${{ inputs.tag }}", tag)
    result = subprocess.run([BASH, "-c", script], text=True,
                            capture_output=True, env=env)
    return result, marker.exists(), direct


def main():
    global BASH
    if len(sys.argv) != 4:
        print("usage: test_rollback_input_contract.py <rollback-drill.yml> <work-dir> <bash>")
        return 2
    workflow_path = Path(sys.argv[1])
    work = Path(sys.argv[2])
    BASH = sys.argv[3]
    work.mkdir(parents=True, exist_ok=True)
    stock_bin = work / "stock-bin"
    stock_bin.mkdir(exist_ok=True)
    stock_sort = stock_bin / "sort"
    stock_sort.write_text("""#!/usr/bin/env bash
if [ "${1:-}" = "-V" ]; then
    echo "sort: illegal option -- V" >&2
    exit 1
fi
exec /usr/bin/sort "$@"
""")
    stock_sort.chmod(stock_sort.stat().st_mode | stat.S_IXUSR)
    workflow = workflow_path.read_text()
    script = validation_script(workflow)
    failures = []

    if "ref: ${{ env.TAG }}" not in workflow:
        failures.append("checkout does not use ref: ${{ env.TAG }}")
    for forbidden in ['tag="${{ inputs.tag }}"',
                      'git tag -v "${{ inputs.tag }}"',
                      'supported tag ${{ inputs.tag }}']:
        if forbidden in workflow:
            failures.append(f"direct GitHub expression reaches shell: {forbidden}")

    for tag, expected in [("v1.9.9", 1), ("v2.0.0", 0), ("v2.0.1", 0),
                          ("v10.0.0", 0), ("not-a-version", 1)]:
        result, side_effect, _ = run_tag_script(script, tag, work)
        print(f"normal {tag!r}: rc={result.returncode}, side_effect={side_effect}")
        if result.returncode != expected or side_effect:
            failures.append(f"normal tag {tag!r}: rc={result.returncode}, side_effect={side_effect}")
        if expected and "UNAVAILABLE" not in result.stdout:
            failures.append(f"normal tag {tag!r}: missing UNAVAILABLE")

    payloads = [
        'v2.0.0"; touch "$ROLLBACK_TEST_MARKER"; #',
        'v2.0.0$(touch "$ROLLBACK_TEST_MARKER")',
        'v2.0.0"\ntouch "$ROLLBACK_TEST_MARKER"\n#',
    ]
    for payload in payloads:
        result, side_effect, direct = run_tag_script(script, payload, work)
        print(f"payload {payload!r}: rc={result.returncode}, side_effect={side_effect}, direct={direct}")
        if side_effect:
            failures.append(f"payload executed a side effect: {payload!r}")
        if result.returncode == 0:
            failures.append(f"payload was accepted: {payload!r}")
        if "UNAVAILABLE" not in result.stdout:
            failures.append(f"payload lacks UNAVAILABLE: {payload!r}")

    if failures:
        print("ROLLBACK INPUT CONTRACT FAILED:")
        for failure in failures:
            print(f"  {failure}")
        return 1
    print("rollback input contract OK: safe env channel, normal matrix, no injection side effects")
    return 0


if __name__ == "__main__":
    sys.exit(main())
