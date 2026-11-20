#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)
PATCH="$SCRIPT_DIR/angle-qnx.patch"
ANGLE_REVISION=db5eb421c4350138e291220646de7764987a07e3
ANGLE_DEPS_SHA256=f57919baac75447a1722f69f7f1d91457e406541c74be6e78e2d68e7008271ff

usage() {
    printf 'Usage: %s [--asan] [--gen-only] ANGLE_SRC OUT_DIR\n' "${0##*/}"
    printf 'Required: QNX_SDP_DIR; optional: QNX_HOST, GN, NINJA, PYTHON_EXECUTABLE, NINJA_JOBS\n'
}

die() {
    printf 'error: %s\n' "$*" >&2
    exit 1
}

resolve_executable() {
    local tool=$1
    if [[ $tool == */* ]]; then
        [[ -x $tool ]] || return 1
        (cd "$(dirname "$tool")" && printf '%s/%s\n' "$(pwd -P)" "$(basename "$tool")")
    else
        command -v "$tool"
    fi
}

gn_quote() {
    local value=$1
    [[ $value != *$'\n'* && $value != *$'\r'* ]] || die 'GN paths cannot contain newlines'
    value=${value//\\/\\\\}
    value=${value//\"/\\\"}
    value=${value//\$/\\\$}
    printf '"%s"' "$value"
}

apply_patch() {
    (cd "$ANGLE_SRC" && GIT_CEILING_DIRECTORIES="$(dirname "$ANGLE_SRC")" git apply "$@")
}

asan=0
gen_only=0
while (($#)); do
    case $1 in
        --asan) asan=1 ;;
        --gen-only) gen_only=1 ;;
        -h|--help)
            usage
            exit 0
            ;;
        --) shift; break ;;
        -*) die "unknown option: $1" ;;
        *) break ;;
    esac
    shift
done
[[ $# -eq 2 ]] || { usage >&2; exit 2; }

ANGLE_SRC=$1
OUT_DIR=$2
[[ -d $ANGLE_SRC ]] || die "ANGLE source directory not found: $ANGLE_SRC"
ANGLE_SRC=$(cd "$ANGLE_SRC" && pwd -P)
mkdir -p "$OUT_DIR"
OUT_DIR=$(cd "$OUT_DIR" && pwd -P)
[[ $ANGLE_SRC != "$OUT_DIR" ]] || die 'OUT_DIR must differ from ANGLE_SRC'

for tool in git sha256sum; do
    command -v "$tool" >/dev/null 2>&1 || die "required tool not found: $tool"
done
for file in \
    .gn BUILD.gn DEPS build/config/BUILDCONFIG.gn \
    build/config/gclient_args.gni build/config/sanitizers/BUILD.gn \
    src/common/vulkan/BUILD.gn \
    third_party/vulkan_memory_allocator/include/vk_mem_alloc.h; do
    [[ -f $ANGLE_SRC/$file ]] || die "missing source or dependency: $ANGLE_SRC/$file"
done
[[ -s $PATCH ]] || die "patch not found: $PATCH"

if ((asan)); then
    ARGS="$SCRIPT_DIR/angle-qnx-x86_64-asan.gn"
else
    ARGS="$SCRIPT_DIR/angle-qnx-x86_64.gn"
fi
[[ -s $ARGS ]] || die "GN args not found: $ARGS"

GN=${GN:-"$ANGLE_SRC/buildtools/linux64/gn"}
NINJA=${NINJA:-"$ANGLE_SRC/third_party/ninja/ninja"}
PYTHON_EXECUTABLE=${PYTHON_EXECUTABLE:-python3}
GN_BIN=$(resolve_executable "$GN") || die "GN executable not found: $GN"
NINJA_BIN=$(resolve_executable "$NINJA") || die "Ninja executable not found: $NINJA"
PYTHON_BIN=$(resolve_executable "$PYTHON_EXECUTABLE") || die "Python executable not found: $PYTHON_EXECUTABLE"

git_top=$(GIT_CEILING_DIRECTORIES="$(dirname "$ANGLE_SRC")" git -C "$ANGLE_SRC" rev-parse --show-toplevel 2>/dev/null || true)
if [[ -n $git_top ]] && [[ $(cd "$git_top" && pwd -P) == "$ANGLE_SRC" ]]; then
    actual_revision=$(git -C "$ANGLE_SRC" rev-parse HEAD)
    [[ $actual_revision == "$ANGLE_REVISION" ]] || die "ANGLE HEAD is $actual_revision; expected $ANGLE_REVISION"
else
    actual_deps_sha256=$(sha256sum "$ANGLE_SRC/DEPS")
    actual_deps_sha256=${actual_deps_sha256%% *}
    [[ $actual_deps_sha256 == "$ANGLE_DEPS_SHA256" ]] || die 'non-Git ANGLE source has an unexpected DEPS fingerprint'
fi

[[ -n ${QNX_SDP_DIR:-} ]] || die 'QNX_SDP_DIR must be set; no machine-specific default is provided'
[[ -f $QNX_SDP_DIR/qnxsdp-env.sh ]] || die "QNX environment script not found: $QNX_SDP_DIR/qnxsdp-env.sh"
QNX_SDP_DIR=$(cd "$QNX_SDP_DIR" && pwd -P)
requested_qnx_host=${QNX_HOST:-}
# shellcheck disable=SC1091
source "$QNX_SDP_DIR/qnxsdp-env.sh" >/dev/null
if [[ -n $requested_qnx_host ]]; then
    QNX_HOST=$requested_qnx_host
fi
[[ -n ${QNX_HOST:-} ]] || die 'QNX_HOST was not set by the caller or qnxsdp-env.sh'
[[ -n ${QNX_TARGET:-} ]] || die 'QNX_TARGET was not set by qnxsdp-env.sh'
[[ -d $QNX_HOST ]] || die "QNX host directory not found: $QNX_HOST"
QNX_HOST=$(cd "$QNX_HOST" && pwd -P)
export QNX_SDP_DIR QNX_HOST QNX_TARGET
for tool in gcc g++ ar readelf nm; do
    [[ -x $QNX_HOST/usr/bin/ntox86_64-$tool ]] || die "QNX tool not found: $QNX_HOST/usr/bin/ntox86_64-$tool"
done

NINJA_JOBS=${NINJA_JOBS:-2}
[[ $NINJA_JOBS =~ ^[1-9][0-9]*$ ]] || die 'NINJA_JOBS must be a positive integer'

if apply_patch --check "$PATCH" >/dev/null 2>&1; then
    apply_patch "$PATCH"
    printf 'Applied %s\n' "$PATCH"
elif apply_patch --reverse --check "$PATCH"; then
    printf 'Patch is already applied: %s\n' "$PATCH"
else
    apply_patch --check "$PATCH"
fi

{
    cat "$ARGS"
    printf '\nqnx_sdp_dir = %s\n' "$(gn_quote "$QNX_SDP_DIR")"
    printf 'qnx_host = %s\n' "$(gn_quote "$QNX_HOST")"
} > "$OUT_DIR/args.gn"

(cd "$ANGLE_SRC" && "$GN_BIN" gen --check "$OUT_DIR" \
    --script-executable="$PYTHON_BIN" \
    --ninja-executable="$NINJA_BIN")

if ((gen_only)); then
    printf 'GN generation completed: %s\n' "$OUT_DIR"
    exit 0
fi

"$NINJA_BIN" -C "$OUT_DIR" "-j$NINJA_JOBS" libEGL libGLESv2
printf 'Built libEGL and libGLESv2 in %s\n' "$OUT_DIR"
