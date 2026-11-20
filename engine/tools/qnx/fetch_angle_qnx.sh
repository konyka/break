#!/usr/bin/env bash
set -euo pipefail

ANGLE_URL=https://chromium.googlesource.com/angle/angle
ANGLE_REVISION=db5eb421c4350138e291220646de7764987a07e3
ANGLE_DEPS_SHA256=f57919baac75447a1722f69f7f1d91457e406541c74be6e78e2d68e7008271ff

usage() {
    printf 'Usage: %s NEW_OR_EMPTY_WORK_DIR\n' "${0##*/}"
    printf 'Requires git and depot_tools gclient on PATH; creates WORK_DIR/src.\n'
}

die() {
    printf 'error: %s\n' "$*" >&2
    exit 1
}

[[ $# -eq 1 ]] || { usage >&2; exit 2; }
WORK_DIR=$1
for tool in git gclient sha256sum; do
    command -v "$tool" >/dev/null 2>&1 || die "required tool not found: $tool"
done
if [[ -e $WORK_DIR ]]; then
    [[ -d $WORK_DIR ]] || die "not a directory: $WORK_DIR"
    [[ -z $(ls -A "$WORK_DIR") ]] || die 'WORK_DIR must be new or empty; refusing to overwrite an existing checkout'
fi
mkdir -p "$WORK_DIR"
WORK_DIR=$(cd "$WORK_DIR" && pwd -P)
ANGLE_SRC="$WORK_DIR/src"

git clone --depth 1 --filter=blob:none --no-checkout "$ANGLE_URL" "$ANGLE_SRC"
git -C "$ANGLE_SRC" fetch --depth 1 origin "$ANGLE_REVISION"
git -C "$ANGLE_SRC" checkout --detach "$ANGLE_REVISION"
actual_revision=$(git -C "$ANGLE_SRC" rev-parse HEAD)
[[ $actual_revision == "$ANGLE_REVISION" ]] || die "checked out unexpected revision: $actual_revision"
actual_deps_sha256=$(sha256sum "$ANGLE_SRC/DEPS")
actual_deps_sha256=${actual_deps_sha256%% *}
[[ $actual_deps_sha256 == "$ANGLE_DEPS_SHA256" ]] || die 'checked out DEPS has an unexpected fingerprint'

cat > "$WORK_DIR/.gclient" <<'EOF'
solutions = [
  {
    "name": "src",
    "url": "https://chromium.googlesource.com/angle/angle",
    "deps_file": "DEPS",
    "managed": False,
    "custom_vars": {
      "android_ndk_version": "2@30.0.16248370",
      "checkout_angle_cl_deps": False,
      "checkout_angle_dawn_deps": False,
      "checkout_angle_internal": False,
      "checkout_angle_mesa": False,
      "checkout_angle_partition_alloc": False,
      "checkout_angle_restricted_traces": False,
      "checkout_extra_traces": False,
      "generate_location_tags": False,
    },
  },
]
EOF

(cd "$WORK_DIR" && gclient sync --revision "src@$ANGLE_REVISION" --nohooks --no-history)
(cd "$WORK_DIR" && gclient runhooks)
[[ -f $ANGLE_SRC/build/config/gclient_args.gni ]] || die 'gclient did not generate build/config/gclient_args.gni'
printf 'ANGLE %s and its DEPS-managed dependencies are ready in %s\n' "$ANGLE_REVISION" "$ANGLE_SRC"
