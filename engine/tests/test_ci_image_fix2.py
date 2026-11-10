#!/usr/bin/env python3
import os
from pathlib import Path
import stat
import subprocess
import sys
import yaml

DIGEST = "sha256:" + "a" * 64
OVERRIDE = "ghcr.io/other/image@sha256:" + "b" * 64


def trigger(data):
    return data.get("on", data.get(True))


def run(cmd, env, cwd):
    try:
        return subprocess.run(cmd, text=True, capture_output=True, env=env, cwd=cwd)
    except OSError as exc:
        return subprocess.CompletedProcess(cmd, 127, "", str(exc))


def main():
    if len(sys.argv) != 3:
        print("usage: test_ci_image_fix2.py <repo-root> <work-dir>")
        return 2
    root = Path(sys.argv[1])
    work = Path(sys.argv[2])
    work.mkdir(parents=True, exist_ok=True)
    failures = []
    image_data = yaml.safe_load((root / ".github/workflows/ci-image.yml").read_text())
    ci_data = yaml.safe_load((root / ".github/workflows/ci.yml").read_text())
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
  "tag "*|"push "*)
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
        "PATH": f"{fake_bin}:{env['PATH']}",
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
    result = run([str(resolver), image, "", "", ""], env, work)
    if result.returncode != 0 or result.stdout.strip() != f"{image}@{DIGEST}":
        failures.append(f"unset PR fallback did not resolve immutable public digest: {result.stdout}{result.stderr}")
    docker_log = log.read_text()
    if "latest" not in docker_log:
        failures.append("unset PR fallback did not inspect public latest")
    if "login" in docker_log or "push" in docker_log:
        failures.append("PR fallback attempted login/push")

    log.write_text("")
    result = run([str(resolver), image, "", "", OVERRIDE], env, work)
    if result.returncode != 0 or result.stdout.strip() != OVERRIDE or log.read_text():
        failures.append("explicit digest override was not preserved without public inspection")

    env["FAIL_INSPECT"] = "1"
    result = run([str(resolver), image, "", "", ""], env, work)
    if result.returncode == 0 or "immutable public digest" not in result.stderr:
        failures.append("public digest resolution failure was not explicit")
    del env["FAIL_INSPECT"]

    log.write_text("")
    result = run([str(publisher), image, inputs_hash], env, work)
    if result.returncode != 0 or result.stdout.strip() != DIGEST:
        failures.append(f"candidate publish failed: {result.stdout}{result.stderr}")
    docker_log = log.read_text().splitlines()
    sequence = " | ".join(docker_log)
    if "tag " not in sequence or "push " not in sequence or "imagetools inspect" not in sequence:
        failures.append(f"candidate was not tagged, pushed, and inspected: {sequence}")
    if "build-push-action" in sequence or " build " in sequence:
        failures.append("publish performed a second build")

    log.write_text("")
    env["FAKE_VERIFIED_ID"] = "sha256:different"
    result = run([str(publisher), image, inputs_hash], env, work)
    if result.returncode == 0 or "push" in log.read_text():
        failures.append("candidate identity mismatch was not rejected before push")

    alias_verifier = root / "engine/tools/verify_ci_master_aliases.sh"
    result = run([str(alias_verifier), image, DIGEST, "test-sha"], env, work)
    if result.returncode != 0:
        failures.append(f"matching master aliases were rejected: {result.stderr}")
    env["FAKE_DIGEST"] = "sha256:" + "c" * 64
    result = run([str(alias_verifier), image, DIGEST, "test-sha"], env, work)
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
