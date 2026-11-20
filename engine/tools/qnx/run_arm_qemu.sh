#!/bin/bash
set -eu

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/../../.." && pwd)
BSP=${QNX_ARM_BSP:-$ROOT/build-validation/qnx-unsupported/qemu-virt}
WORK=${QNX_ARM_WORKDIR:-$ROOT/build-validation/qnx-arm-runtime}
PATCH=$ROOT/engine/tools/qnx/qemu-virt-psci.patch
EXPECTED_BSP_COMMIT=01437f23c75260fc2fcbb24fbc08608947c88f40
VM_NAME=break-qnx-arm-runtime
ACTION=${1:-start}

if [ -n "${QNX_SDP_DIR:-}" ]; then
    . "$QNX_SDP_DIR/qnxsdp-env.sh" >/dev/null
fi
: "${QNX_HOST:?set QNX_HOST or QNX_SDP_DIR/source qnxsdp-env.sh}"
: "${QNX_TARGET:?set QNX_TARGET or QNX_SDP_DIR/source qnxsdp-env.sh}"

build_runtime() {
    commit=$(git -C "$BSP" rev-parse HEAD)
    if [ "$commit" != "$EXPECTED_BSP_COMMIT" ]; then
        printf 'unsupported qemu-virt commit: %s\n' "$commit" >&2
        return 1
    fi
    if git -C "$BSP" apply --check --reverse "$PATCH" >/dev/null 2>&1; then
        :
    else
        git -C "$BSP" apply --check "$PATCH"
        git -C "$BSP" apply "$PATCH"
    fi
    mkdir -p "$WORK"
    make -C "$BSP/src" -j "${JOBS:-4}"
    make -C "$BSP/src" install
    make -C "$BSP" -B images
    "${PYTHON:-python3}" "$ROOT/engine/tools/qnx/build_arm_runtime.py" \
        --ram-mib "${QNX_ARM_RAM_MIB:-256}" \
        "$BSP/images/qemu-virt.build" "$WORK/ifs-test.build"
    mkifs -o "$WORK" -r "$BSP/install" \
        "$WORK/ifs-test.build" "$WORK/ifs-test.bin" > "$WORK/build.log" 2>&1
    dumpifs "$WORK/ifs-test.bin" > "$WORK/image-contents.log"
    for file in proc/boot/procnto-smp-instr proc/boot/sshd_config sbin/rtc usr/sbin/sshd usr/libexec/sshd-session; do
        if ! grep -F "$file" "$WORK/image-contents.log" >/dev/null; then
            printf 'required IFS component missing: %s\n' "$file" >&2
            return 1
        fi
    done
}

stop_runtime() {
    if [ ! -r "$WORK/qemu.pid" ]; then
        return 0
    fi
    read -r pid < "$WORK/qemu.pid"
    case "$(ps -p "$pid" -o args=)" in
        *"$VM_NAME"*) kill "$pid" ;;
    esac
}

start_runtime() {
    if [ -z "${QEMU_SYSTEM_AARCH64:-}" ]; then
        QEMU_SYSTEM_AARCH64=$ROOT/build-validation/qnx-unsupported/qemu-arm-root/usr/bin/qemu-system-aarch64
        if [ ! -x "$QEMU_SYSTEM_AARCH64" ]; then
            QEMU_SYSTEM_AARCH64=$(command -v qemu-system-aarch64)
        fi
    fi
    if [ -z "${QEMU_MODULE_DIR:-}" ] && [ -d "$ROOT/build-validation/qnx-unsupported/qemu-arm-root/usr/lib/x86_64-linux-gnu/qemu" ]; then
        QEMU_MODULE_DIR=$ROOT/build-validation/qnx-unsupported/qemu-arm-root/usr/lib/x86_64-linux-gnu/qemu
        export QEMU_MODULE_DIR
    fi
    stop_runtime
    rm -f "$WORK/serial.sock"
    "$QEMU_SYSTEM_AARCH64" \
        -name "$VM_NAME" \
        -machine virt,gic-version=3 -cpu cortex-a72 \
        -smp "${QNX_ARM_SMP:-2}" -m "${QNX_ARM_MEMORY_MIB:-1024}M" \
        -display none \
        -chardev socket,id=ser0,path="$WORK/serial.sock",server=on,wait=off,logfile="$WORK/console.log" \
        -serial chardev:ser0 -monitor none \
        -bios "$BSP/images/qemu-virt.bios" \
        -device loader,file="$WORK/ifs-test.bin",addr=0x40200000,force-raw=true \
        -netdev user,id=n0,hostfwd=tcp:127.0.0.1:"${QNX_ARM_SSH_PORT:-2301}"-:22 \
        -device virtio-net-device,netdev=n0 \
        -pidfile "$WORK/qemu.pid" -daemonize
    printf 'started %s; SSH 127.0.0.1:%s; serial %s\n' \
        "$VM_NAME" "${QNX_ARM_SSH_PORT:-2301}" "$WORK/serial.sock"
}

case "$ACTION" in
    build) build_runtime ;;
    start) build_runtime && start_runtime ;;
    stop) stop_runtime ;;
    *) printf 'usage: %s [build|start|stop]\n' "$0" >&2; exit 2 ;;
esac
