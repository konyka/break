#!/usr/bin/env python3
import ast
import json
import os
from pathlib import Path
import stat
import subprocess
import sys

DIGEST = "sha256:" + "a" * 64
OVERRIDE = "ghcr.io/other/image@sha256:" + "b" * 64
BASH = ""
SIMULATE_WINDOWS = False


def trigger(data):
    return data.get("on", data.get(True))


def scalar(text):
    text = text.strip()
    if len(text) >= 2 and text[0] == text[-1] and text[0] in "'\"":
        return ast.literal_eval(text)
    return text


def parse_workflow(path):
    lines = path.read_text().splitlines()

    def indentation(line):
        return len(line) - len(line.lstrip(" "))

    def next_content(index):
        while index < len(lines):
            stripped = lines[index].strip()
            if stripped and not stripped.startswith("#"):
                return index
            index += 1
        return len(lines)

    def block_scalar(index, parent_indent):
        chunk = []
        while index < len(lines):
            line = lines[index]
            if line.strip() and indentation(line) <= parent_indent:
                break
            if not line.strip():
                chunk.append("")
            else:
                chunk.append(line[parent_indent + 2:])
            index += 1
        return index, "\n".join(chunk) + "\n"

    def parse_node(index, indent):
        text = lines[index].strip()
        if text == "-" or text.startswith("- "):
            return parse_list(index, indent)
        return parse_map(index, indent)

    def parse_map(index, indent):
        result = {}
        while True:
            index = next_content(index)
            if index >= len(lines) or indentation(lines[index]) < indent:
                break
            actual = indentation(lines[index])
            text = lines[index].strip()
            if actual > indent:
                raise ValueError(f"unexpected indentation in {path}:{index + 1}")
            if text == "-" or text.startswith("- "):
                break
            if ":" not in text:
                raise ValueError(f"expected mapping in {path}:{index + 1}")
            key, value = text.split(":", 1)
            key = key.strip()
            value = value.strip()
            index += 1
            if value in ("|", ">"):
                index, result[key] = block_scalar(index, indent)
            elif not value:
                following = next_content(index)
                if (following < len(lines) and
                        indentation(lines[following]) > indent):
                    child_indent = indentation(lines[following])
                    index, result[key] = parse_node(following, child_indent)
                else:
                    result[key] = {}
            else:
                result[key] = scalar(value)
        return index, result

    def parse_list(index, indent):
        result = []
        while True:
            index = next_content(index)
            if (index >= len(lines) or indentation(lines[index]) != indent or
                    not (lines[index].strip() == "-" or
                         lines[index].strip().startswith("- "))):
                break
            text = lines[index].strip()[1:].strip()
            index += 1
            if ":" not in text:
                result.append(scalar(text))
                continue
            key, value = text.split(":", 1)
            item = {key.strip(): scalar(value)}
            following = next_content(index)
            if (following < len(lines) and
                    indentation(lines[following]) > indent):
                child_indent = indentation(lines[following])
                index, extra = parse_map(following, child_indent)
                item.update(extra)
            result.append(item)
        return index, result

    first = next_content(0)
    if first >= len(lines):
        return {}
    _, data = parse_node(first, indentation(lines[first]))
    return data


def run(cmd, env, cwd):
    if (SIMULATE_WINDOWS and os.path.normcase(cmd[0]) != os.path.normcase(BASH)
            and not cmd[0].lower().endswith(".exe")):
        return subprocess.CompletedProcess(
            cmd, 127, "", "simulated Win32 CreateProcess cannot execute a shell script")
    try:
        return subprocess.run(cmd, text=True, capture_output=True, env=env, cwd=cwd)
    except OSError as exc:
        return subprocess.CompletedProcess(cmd, 127, "", str(exc))


def check_windows_registration(root, work, failures):
    build = work / "nested-windows-registration"
    python_launcher = work / "cmake-python-launcher"
    python_launcher.write_text(
        f"#!{BASH}\nexec \"{sys.executable}\" \"$@\"\n")
    python_launcher.chmod(python_launcher.stat().st_mode | stat.S_IXUSR)
    configure = subprocess.run([
        "cmake", "-S", str(root / "engine"), "-B", str(build),
        "-DCMAKE_SYSTEM_NAME=Windows",
        "-DCMAKE_C_COMPILER_WORKS=TRUE", "-DCMAKE_CXX_COMPILER_WORKS=TRUE",
        "-DCMAKE_C_ABI_COMPILED=TRUE", "-DCMAKE_CXX_ABI_COMPILED=TRUE",
        "-DENGINE_ENABLE_WAYLAND=OFF", "-DENGINE_RHI_BACKEND=opengl",
        "-DENGINE_ENABLE_IPO=OFF", "-DENGINE_BUILD_TESTS=ON",
        "-DBREAK_ENABLE_SNOWFLAKE=OFF", "-DBREAK_ENABLE_CRYPTO=OFF",
        "-DBREAK_ENABLE_CRASH=OFF", "-DMYUI_PAL=dummy",
        f"-DPython3_EXECUTABLE={python_launcher}",
        f"-DBASH_EXECUTABLE={BASH}",
    ], text=True, capture_output=True)
    if configure.returncode != 0:
        failures.append(
            f"Windows nested configure failed: {configure.stdout}{configure.stderr}")
        return
    listing = subprocess.run(
        ["ctest", "--test-dir", str(build), "--show-only=json-v1"],
        text=True, capture_output=True)
    if listing.returncode != 0:
        failures.append(f"Windows CTest JSON listing failed: {listing.stderr}")
        return
    tests = {test["name"]: test for test in json.loads(listing.stdout)["tests"]}
    for name in ("test_ci_image_fix2", "test_rollback_input_contract"):
        command = tests.get(name, {}).get("command", [])
        if not command or Path(command[0]) != python_launcher:
            failures.append(f"{name} does not use CMake's Python3_EXECUTABLE: {command}")
        if BASH not in command:
            failures.append(f"{name} does not receive CMake's BASH_EXECUTABLE: {command}")


def main():
    global BASH, SIMULATE_WINDOWS
    if len(sys.argv) not in (4, 5):
        print("usage: test_ci_image_fix2.py <repo-root> <work-dir> <bash> [--simulate-windows]")
        return 2
    root = Path(sys.argv[1]).resolve()
    work = Path(sys.argv[2]).resolve()
    BASH = sys.argv[3]
    SIMULATE_WINDOWS = len(sys.argv) == 5 and sys.argv[4] == "--simulate-windows"
    if len(sys.argv) == 5 and not SIMULATE_WINDOWS:
        print(f"unknown option: {sys.argv[4]}")
        return 2
    work.mkdir(parents=True, exist_ok=True)
    failures = []
    image_data = parse_workflow(root / ".github/workflows/ci-image.yml")
    ci_data = parse_workflow(root / ".github/workflows/ci.yml")
    if SIMULATE_WINDOWS:
        check_windows_registration(root, work, failures)
    call = trigger(image_data).get("workflow_call", {})
    expected_workflow_output = "${{ jobs.prepare.outputs.digest }}"
    if call.get("outputs", {}).get("digest", {}).get("value") != expected_workflow_output:
        failures.append(f"workflow_call.outputs.digest.value is not {expected_workflow_output}")
    prepare = image_data.get("jobs", {}).get("prepare", {})
    if prepare.get("outputs", {}).get("digest") != "${{ steps.selected.outputs.digest }}":
        failures.append("prepare job does not expose steps.selected.outputs.digest")

    consumers = []
    for name, job in ci_data.get("jobs", {}).items():
        if isinstance(job, dict) and job.get("needs") == "image":
            consumers.append(name)
            if job.get("container", {}).get("image") != "${{ needs.image.outputs.digest }}":
                failures.append(f"{name} does not consume needs.image.outputs.digest")
    if len(consumers) != 10:
        failures.append(f"expected 10 digest consumers, got {len(consumers)}")

    steps = prepare.get("steps", [])
    publish = next((s for s in steps if s.get("name") == "Publish verified image"), {})
    if "uses" in publish:
        failures.append("Publish verified image still builds instead of pushing the candidate")
    if "publish_ci_candidate.sh" not in publish.get("run", ""):
        failures.append("Publish verified image does not call publish_ci_candidate.sh")
    select = next((s for s in steps if s.get("name") == "Select consumer digest"), {})
    if "resolve_ci_consumer_digest.sh" not in select.get("run", ""):
        failures.append("Select consumer digest does not call resolve_ci_consumer_digest.sh")
    aliases = next((s for s in steps if s.get("name") == "Verify master aliases"), {})
    if "verify_ci_master_aliases.sh" not in aliases.get("run", ""):
        failures.append("master SHA/latest aliases are not inspected for digest equality")
    for name in ("Login to GHCR", "Publish verified image"):
        step = next((s for s in steps if s.get("name") == name), {})
        if step.get("if") != "env.PUBLISH == 'true'" and name == "Login to GHCR":
            failures.append("login is not gated only by PUBLISH")
        elif name == "Publish verified image" and "env.PUBLISH == 'true'" not in step.get("if", ""):
            failures.append("publish is not gated only by PUBLISH")

    fake_bin = work / "bin"
    fake_bin.mkdir(exist_ok=True)
    log = work / "docker.log"
    docker = fake_bin / "docker"
    docker.write_text("""#!/usr/bin/env bash
printf '%s\\n' "$*" >> "$FAKE_LOG"
if [ "${FAIL_INSPECT:-0}" = "1" ]; then exit 1; fi
case "$*" in
  "buildx imagetools inspect "*)
    echo "Digest: $FAKE_DIGEST"
    ;;
  "image inspect "*)
    case "$*" in
      *candidate-*) echo "$FAKE_CANDIDATE_ID" ;;
      *verified-*) echo "$FAKE_VERIFIED_ID" ;;
      *) exit 98 ;;
    esac
    ;;
  "tag "*)
    ;;
  "push "*)
    echo "The push refers to repository [ghcr.io/konyka/break-ci-linux]"
    echo "layer-abc123: Pushed"
    ;;
  *)
    echo "unexpected docker invocation: $*" >&2
    exit 97
    ;;
esac
""")
    docker.chmod(docker.stat().st_mode | stat.S_IXUSR)
    env = dict(os.environ)
    env.update({
        "PATH": f"{fake_bin}{os.pathsep}{env['PATH']}",
        "FAKE_LOG": str(log),
        "FAKE_DIGEST": DIGEST,
        "FAKE_CANDIDATE_ID": "sha256:candidate",
        "FAKE_VERIFIED_ID": "sha256:candidate",
        "PUBLISH": "false",
    })
    resolver = root / "engine/tools/resolve_ci_consumer_digest.sh"
    publisher = root / "engine/tools/publish_ci_candidate.sh"
    image = "ghcr.io/konyka/break-ci-linux"
    inputs_hash = "abc123"

    log.write_text("")
    result = run([BASH, str(resolver), image, "", "", ""], env, work)
    if result.returncode != 0 or result.stdout.strip() != f"{image}@{DIGEST}":
        failures.append(f"unset PR fallback did not resolve immutable public digest: {result.stdout}{result.stderr}")
    docker_log = log.read_text()
    if "latest" not in docker_log:
        failures.append("unset PR fallback did not inspect public latest")
    if "login" in docker_log or "push" in docker_log:
        failures.append("PR fallback attempted login/push")

    log.write_text("")
    result = run([BASH, str(resolver), image, "", "", OVERRIDE], env, work)
    if result.returncode != 0 or result.stdout.strip() != OVERRIDE or log.read_text():
        failures.append("explicit digest override was not preserved without public inspection")

    env["FAIL_INSPECT"] = "1"
    result = run([BASH, str(resolver), image, "", "", ""], env, work)
    if result.returncode == 0 or "immutable public digest" not in result.stderr:
        failures.append("public digest resolution failure was not explicit")
    del env["FAIL_INSPECT"]

    log.write_text("")
    result = run([BASH, str(publisher), image, inputs_hash], env, work)
    if result.returncode != 0 or result.stdout.strip() != DIGEST:
        failures.append(f"candidate publish failed: {result.stdout}{result.stderr}")
    docker_log = log.read_text().splitlines()
    sequence = " | ".join(docker_log)
    if "tag " not in sequence or "push " not in sequence or "imagetools inspect" not in sequence:
        failures.append(f"candidate was not tagged, pushed, and inspected: {sequence}")
    if "build-push-action" in sequence or " build " in sequence:
        failures.append("publish performed a second build")
    if "The push refers to repository" in result.stdout:
        failures.append("docker push progress polluted helper stdout")
    if "The push refers to repository" not in result.stderr:
        failures.append("docker push progress was not routed to stderr")
    final = run([BASH, str(resolver), image, "", DIGEST, ""], env, work)
    expected_output = f"{image}@{DIGEST}"
    if final.returncode != 0 or final.stdout != expected_output + "\n" or len(final.stdout.splitlines()) != 1:
        failures.append(f"workflow output is not one immutable image digest: {final.stdout!r}")

    log.write_text("")
    env["FAKE_VERIFIED_ID"] = "sha256:different"
    result = run([BASH, str(publisher), image, inputs_hash], env, work)
    if result.returncode == 0 or "push" in log.read_text():
        failures.append("candidate identity mismatch was not rejected before push")

    alias_verifier = root / "engine/tools/verify_ci_master_aliases.sh"
    result = run([BASH, str(alias_verifier), image, DIGEST, "test-sha"], env, work)
    if result.returncode != 0:
        failures.append(f"matching master aliases were rejected: {result.stderr}")
    env["FAKE_DIGEST"] = "sha256:" + "c" * 64
    result = run([BASH, str(alias_verifier), image, DIGEST, "test-sha"], env, work)
    if result.returncode == 0:
        failures.append("mismatched master alias digest was accepted")

    if failures:
        print("CI image fix2 contract FAILED:")
        for failure in failures:
            print(f"  {failure}")
        return 1
    print("CI image fix2 contract OK: workflow output, anonymous PR digest, candidate identity")
    return 0


if __name__ == "__main__":
    sys.exit(main())
