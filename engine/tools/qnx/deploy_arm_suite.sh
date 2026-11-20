#!/bin/bash
set -euo pipefail

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/../../.." && pwd)
BUILD_DIR=${1:?usage: deploy_arm_suite.sh <build-dir> [deploy|run]}
ACTION=${2:-deploy}
WORK=${QNX_ARM_DEPLOY_WORKDIR:-$ROOT/build-validation/qnx-arm-deploy}
TARGET_ROOT=${QNX_ARM_TARGET_ROOT:-/var/bt}
TARGET_HOST=${QNX_ARM_HOST:-127.0.0.1}
TARGET_USER=${QNX_ARM_USER:-root}
SSH_PORT=${QNX_ARM_SSH_PORT:-2301}
PYTHON=${PYTHON:-python3}

if [ -n "${QNX_SDP_DIR:-}" ]; then
    . "$QNX_SDP_DIR/qnxsdp-env.sh" >/dev/null
fi
: "${QNX_HOST:?set QNX_HOST or QNX_SDP_DIR/source qnxsdp-env.sh}"
: "${QNX_TARGET:?set QNX_TARGET or QNX_SDP_DIR/source qnxsdp-env.sh}"
if [ ! -f "$BUILD_DIR/CMakeCache.txt" ] || [ ! -x "$BUILD_DIR/test_platform_compat" ]; then
    printf 'not a QNX ARM test build: %s\n' "$BUILD_DIR" >&2
    exit 1
fi
case "$(file -b "$BUILD_DIR/test_platform_compat")" in
    *"ARM aarch64"*) ;;
    *) printf 'build does not contain AArch64 ELF binaries\n' >&2; exit 1 ;;
esac
case "$TARGET_ROOT" in
    /*) ;;
    *) printf 'target root must be absolute\n' >&2; exit 1 ;;
esac
if [[ "$TARGET_ROOT" =~ [^A-Za-z0-9_./-] ]]; then
    printf 'target root contains unsupported characters\n' >&2
    exit 1
fi
if [ "$ACTION" != deploy ] && [ "$ACTION" != run ]; then
    printf 'action must be deploy or run\n' >&2
    exit 2
fi
STAGE_ARGS=()
VULKAN_REQUESTED=0
VULKAN_INPUT_NAMES=(
    QNX_ARM_VULKAN_ICD
    QNX_ARM_VULKAN_LOADER
    QNX_ARM_VULKAN_REDIRECT
    QNX_ARM_SHADERC
    QNX_ARM_VULKAN_ICD_MANIFEST
    QNX_ARM_VULKAN_GRAPHICS_CONF
)
for name in "${VULKAN_INPUT_NAMES[@]}"; do
    if [ -n "${!name:-}" ]; then VULKAN_REQUESTED=1; fi
done
if [ "$VULKAN_REQUESTED" = 1 ]; then
    for name in "${VULKAN_INPUT_NAMES[@]}"; do
        value=${!name:-}
        if [ -z "$value" ]; then
            printf 'Vulkan runtime inputs must be provided together; missing %s\n' "$name" >&2
            exit 2
        fi
        if [ ! -f "$value" ]; then
            printf 'Vulkan runtime input is not a file: %s=%s\n' "$name" "$value" >&2
            exit 2
        fi
    done
    STAGE_ARGS=(
        --vulkan-icd "$QNX_ARM_VULKAN_ICD"
        --vulkan-loader "$QNX_ARM_VULKAN_LOADER"
        --vulkan-redirect "$QNX_ARM_VULKAN_REDIRECT"
        --shaderc "$QNX_ARM_SHADERC"
        --vulkan-icd-manifest "$QNX_ARM_VULKAN_ICD_MANIFEST"
        --vulkan-graphics-config "$QNX_ARM_VULKAN_GRAPHICS_CONF"
        --vulkan-target-root "$TARGET_ROOT"
    )
fi
while IFS='=' read -r cache_key cache_value; do
    case "$cache_key=$cache_value" in
        ENGINE_USE_ASAN:BOOL=ON) STAGE_ARGS+=(--asan) ;;
        ENGINE_USE_UBSAN:BOOL=ON) STAGE_ARGS+=(--ubsan) ;;
    esac
done < "$BUILD_DIR/CMakeCache.txt"
if [ -f "$BUILD_DIR/libqnx_sanitizer_cleanup.so" ]; then
    STAGE_ARGS+=(--sanitizer-cleanup "$BUILD_DIR/libqnx_sanitizer_cleanup.so")
fi
mkdir -p "$WORK"
KNOWN_HOSTS=${QNX_ARM_KNOWN_HOSTS:-$WORK/known_hosts}
AUTH=(-o BatchMode=yes)
PASS=()
if [ -n "${QNX_ARM_PASSWORD:-}" ]; then
    export SSHPASS="$QNX_ARM_PASSWORD"
    PASS=("${QNX_ARM_SSHPASS:-sshpass}" -e)
    AUTH=(-o PreferredAuthentications=password -o PubkeyAuthentication=no)
fi
SSH=("${PASS[@]}" ssh -F /dev/null -o LogLevel=ERROR
    -o StrictHostKeyChecking=no -o UserKnownHostsFile="$KNOWN_HOSTS"
    "${AUTH[@]}" -p "$SSH_PORT" "$TARGET_USER@$TARGET_HOST")
SCP=("${PASS[@]}" scp -F /dev/null -o LogLevel=ERROR
    -o StrictHostKeyChecking=no -o UserKnownHostsFile="$KNOWN_HOSTS"
    "${AUTH[@]}" -P "$SSH_PORT")

arch=
for attempt in {1..30}; do
    if arch=$("${SSH[@]}" 'uname -a' 2>/dev/null); then
        break
    fi
    sleep 1
done
case "$arch" in
    *aarch64le*) ;;
    *) printf 'target is not reachable on AArch64 QNX (uname -a=%s)\n' "$arch" >&2; exit 1 ;;
esac

STORAGE=${QNX_ARM_STORAGE:-tar}
if [ "$STORAGE" != tar ] && [ "$STORAGE" != loopback ]; then
    printf 'QNX_ARM_STORAGE must be tar or loopback\n' >&2
    exit 2
fi
case "$SSH_PORT" in
    ''|*[!0-9]*) printf 'SSH port must be numeric\n' >&2; exit 2 ;;
esac

"$PYTHON" "$ROOT/engine/tools/qnx/gen_target_cmds.py" \
    "$BUILD_DIR" "$ROOT" "$TARGET_ROOT" "$WORK/cmds.txt"
"$PYTHON" "$ROOT/engine/tools/qnx/stage_screen_runtime.py" \
    --arch aarch64le --output "$WORK/runtime" "${STAGE_ARGS[@]}"
SOURCE_ROOT=$("$PYTHON" -c 'import sys
for line in open(sys.argv[1], encoding="utf-8"):
    if line.startswith("ENGINE_TEST_SOURCE_ROOT:PATH="):
        print(line.rstrip().split("=", 1)[1])
        break' "$BUILD_DIR/CMakeCache.txt")
if [[ "$SOURCE_ROOT" =~ [^A-Za-z0-9_./-] ]]; then
    printf 'source root contains unsupported characters\n' >&2
    exit 1
fi

TEST_ARTIFACTS=()
while IFS= read -r line; do
    line=${line#EXPECT_FAIL }
    case "$line" in
        ./*)
            exe=${line#./}
            exe=${exe%% *}
            if [ ! -x "$BUILD_DIR/$exe" ]; then
                printf 'required test executable is missing: %s\n' "$exe" >&2
                exit 1
            fi
            duplicate=0
            for existing in "${TEST_ARTIFACTS[@]}"; do
                if [ "$existing" = "$exe" ]; then duplicate=1; break; fi
            done
            if [ "$duplicate" = 0 ]; then TEST_ARTIFACTS+=("$exe"); fi
            ;;
    esac
done < "$WORK/cmds.txt"
if [ ! -x "$BUILD_DIR/test_vulkan" ]; then
    printf 'required graphics test executable is missing: test_vulkan\n' >&2
    exit 1
fi
duplicate=0
for existing in "${TEST_ARTIFACTS[@]}"; do
    if [ "$existing" = test_vulkan ]; then duplicate=1; break; fi
done
if [ "$duplicate" = 0 ]; then TEST_ARTIFACTS+=(test_vulkan); fi
printf 'staging %d test/helper executables including graphics test_vulkan\n' "${#TEST_ARTIFACTS[@]}"
CMAKE_EXCLUDES=(
    --exclude=CMakeFiles --exclude='CMakeFiles/*'
    --exclude='*/CMakeFiles' --exclude='*/CMakeFiles/*'
    --exclude=__pycache__ --exclude='__pycache__/*'
    --exclude='*/__pycache__' --exclude='*/__pycache__/*'
    --exclude='*.pyc'
)

if [ "$STORAGE" = loopback ]; then
    if [ "$TARGET_ROOT" != /var/bt ]; then
        printf 'loopback deployment requires QNX_ARM_TARGET_ROOT=/var/bt\n' >&2
        exit 2
    fi
    case "$SOURCE_ROOT" in
        ''|/var/bt/engine) ;;
        *) printf 'loopback requires ENGINE_TEST_SOURCE_ROOT=/var/bt/engine\n' >&2; exit 2 ;;
    esac
    IMAGE_SECTORS=${QNX_ARM_IMAGE_SECTORS:-2097152}
    IMAGE_INODES=${QNX_ARM_IMAGE_INODES:-12000}
    case "$IMAGE_SECTORS:$IMAGE_INODES" in
        *[!0-9:]*|0:*|*:0) printf 'image sectors and inodes must be positive integers\n' >&2; exit 2 ;;
    esac
    IMAGE_ROOT=$WORK/loopback-root
    DRIVER=$WORK/loopback-driver
    BACKING=/dev/shmem/break-arm-tests-$SSH_PORT.img
    for generated in "$IMAGE_ROOT" "$DRIVER" "$WORK/tests-qnx6.img" "$WORK/tests-qnx6.img.gz"; do
        if [ -e "$generated" ]; then
            printf 'generated path exists; choose a new QNX_ARM_DEPLOY_WORKDIR: %s\n' "$generated" >&2
            exit 2
        fi
    done
    mkdir -p "$IMAGE_ROOT/tmp" "$DRIVER" "$IMAGE_ROOT/engine"
    for exe in "${TEST_ARTIFACTS[@]}"; do
        cp "$BUILD_DIR/$exe" "$IMAGE_ROOT/"
    done
    tar -C "$ROOT/engine" "${CMAKE_EXCLUDES[@]}" -cf - . | \
        tar -C "$IMAGE_ROOT/engine" -xf -
    cp -a "$WORK/runtime/." "$IMAGE_ROOT/"
    for f in "$IMAGE_ROOT"/usr/lib/*.so* "$IMAGE_ROOT"/lib/*.so* "$IMAGE_ROOT"/lib/dll/*.so*; do
        [ ! -e "$f" ] || cp "$f" "$IMAGE_ROOT/"
    done
    ln -s engine "$IMAGE_ROOT/src"
    cp "$WORK/cmds.txt" "$ROOT/engine/tools/qnx/run_target_suite.sh" "$IMAGE_ROOT/"
    chmod 1777 "$IMAGE_ROOT/tmp"
    for relative in sbin/devb-loopback lib/libcam.so.2 lib/libsecpol.so.1 \
                    lib/libslog2.so.1 lib/dll/io-blk.so lib/dll/cam-disk.so \
                    lib/dll/fs-qnx6.so; do
        cp "$QNX_TARGET/aarch64le/$relative" "$DRIVER/"
    done
    "$QNX_HOST/usr/bin/mkqnx6fsimg" \
        -l "[num_inodes=$IMAGE_INODES]" -l "[num_sectors=$IMAGE_SECTORS]" \
        "$IMAGE_ROOT" "$WORK/tests-qnx6.img" > "$WORK/mkqnx6fsimg.log"
    gzip -1c "$WORK/tests-qnx6.img" > "$WORK/tests-qnx6.img.gz"
    "${SSH[@]}" 'mkdir -p /var/qnx-arm-image/driver /var/bt'
    tar -C "$DRIVER" -cf - . | "${SSH[@]}" 'tar -xf - -C /var/qnx-arm-image/driver'
    "${SCP[@]}" "$WORK/tests-qnx6.img.gz" "$TARGET_USER@$TARGET_HOST:$BACKING.gz"
    "${SSH[@]}" "set -e
mounts=\$(mount)
case \"\$mounts\" in
    *'/dev/lo0 on '*) printf 'a loopback device is already active; use a fresh test VM\n' >&2; exit 3 ;;
esac
[ ! -e /dev/lo0 ] || { printf '/dev/lo0 already exists\n' >&2; exit 3; }
gzip -dc '$BACKING.gz' > '$BACKING'
export LD_LIBRARY_PATH=/var/qnx-arm-image/driver
/var/qnx-arm-image/driver/devb-loopback \
    loopback async,blksz=512,rw,fd='$BACKING' \
    blk cache=16M,auto=partition </dev/null >/var/qnx-arm-image/driver.log 2>&1 &
waitfor /dev/lo0 10
mount -t qnx6 -o sync=none /dev/lo0 '$TARGET_ROOT'
cd '$TARGET_ROOT'
cp test_platform_compat .loopback-write-check
cmp test_platform_compat .loopback-write-check
rm .loopback-write-check
printf 'loopback QNX6 is ephemeral test storage (sync=none), not persistent media\n'"
else
    tar -C "$BUILD_DIR" -cf - -- "${TEST_ARTIFACTS[@]}" | gzip -1 > "$WORK/tests.tar.gz"
    tar -C "$ROOT/engine" "${CMAKE_EXCLUDES[@]}" -cf - . | gzip -1 > "$WORK/engine.tar.gz"
    tar -C "$WORK/runtime" -cf - . | gzip -1 > "$WORK/runtime.tar.gz"
    "${SSH[@]}" "mkdir -p '$TARGET_ROOT' '$TARGET_ROOT/engine' '$TARGET_ROOT/tmp'"
    "${SCP[@]}" "$WORK/tests.tar.gz" "$WORK/engine.tar.gz" "$WORK/runtime.tar.gz" \
        "$WORK/cmds.txt" "$ROOT/engine/tools/qnx/run_target_suite.sh" \
        "$TARGET_USER@$TARGET_HOST:$TARGET_ROOT/"
    "${SSH[@]}" "set -e
cd '$TARGET_ROOT'
tar -xzf tests.tar.gz
tar -xzf engine.tar.gz -C '$TARGET_ROOT/engine'
tar -xzf runtime.tar.gz
for f in usr/lib/*.so* lib/*.so* lib/dll/*.so*; do
    [ ! -e \"\$f\" ] || cp \"\$f\" .
done
ln -sfn '$TARGET_ROOT/engine' '$TARGET_ROOT/src'
if [ -n '$SOURCE_ROOT' ] && [ ! -e '$SOURCE_ROOT' ]; then
    ln -sP '$TARGET_ROOT/engine' '$SOURCE_ROOT'
fi
chmod 755 '$TARGET_ROOT'/test_* '$TARGET_ROOT/run_target_suite.sh'"
fi
printf 'deployed %s to %s@%s:%s (%s)\n' "$BUILD_DIR" "$TARGET_USER" "$TARGET_HOST" "$TARGET_ROOT" "$arch"
if [ "$ACTION" = run ]; then
    "${SSH[@]}" "cd '$TARGET_ROOT' && BREAK_QNX_TARGET_ROOT='$TARGET_ROOT' BREAK_QNX_VULKAN_RUNTIME='$VULKAN_REQUESTED' sh run_target_suite.sh cmds.txt"
fi
