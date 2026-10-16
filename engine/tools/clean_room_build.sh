#!/usr/bin/env bash
# clean_room_build.sh <repo_root> <workdir> [--backend vulkan|opengl]
# 干净导出（git archive）→ 仅用锁定依赖 → configure/build/headless ctest。
# exit 0 = 绿; exit 77 = 缺失 SDK (UNAVAILABLE); 其他非零 = 失败。
set -euo pipefail
REPO="${1:?usage: clean_room_build.sh <repo_root> <workdir> [--backend B]}"
WORK="${2:?usage: clean_room_build.sh <repo_root> <workdir> [--backend B]}"
BACKEND="vulkan"
[ "${3:-}" = "--backend" ] && BACKEND="${4:?backend name required}"

LOCK_JSON="$REPO/engine/external/locked_dependencies.json"
[ -f "$LOCK_JSON" ] || { echo "locked_dependencies.json missing at $LOCK_JSON"; exit 2; }
if grep -qi '"latest"' "$LOCK_JSON"; then
    echo "locked manifest contains 'latest'"; exit 2
fi

# 依赖闸：vendored Vulkan SDK 必须存在且 sha256 匹配清单。
SDK_DIR="$REPO/engine/external/VulkanSDK"
SDK_LIB="$SDK_DIR/Lib/vulkan-1.lib"
EXPECT=$(grep -A6 '"name": "vulkan-sdk"' "$LOCK_JSON" | grep '"sha256"' | head -1 \
         | sed -E 's/.*"sha256": "([0-9a-f]{64})".*/\1/')
if [ "$(uname -s)" = "Linux" ]; then
    # Linux 闸：要求 lavapipe ICD 或真实驱动；均无 → UNAVAILABLE (77)。
    if ! ls /usr/share/vulkan/icd.d/*.json >/dev/null 2>&1; then
        echo "UNAVAILABLE: no Vulkan ICD on this host"; exit 77
    fi
elif [ -f "$SDK_LIB" ]; then
    ACTUAL=$(cmake -E sha256sum "$SDK_LIB" | awk '{print $1}')
    [ "$ACTUAL" = "$EXPECT" ] || { echo "vendored Vulkan SDK sha256 mismatch"; exit 2; }
    # git archive 不含被 git ignore 的 vendored SDK；把锁定清单里这套 SDK 显式
    # 注入干净导出的环境（覆盖/替代宿主机 VULKAN_SDK），configure 与 ctest 只能
    # 命中它（Bin 目录同时提供 vulkan-1.dll / shaderc_shared.dll 运行时）。
    VULKAN_SDK_NATIVE="$SDK_DIR"
    if command -v cygpath >/dev/null 2>&1; then
        VULKAN_SDK_NATIVE=$(cygpath -m "$SDK_DIR")
    fi
    export VULKAN_SDK="$VULKAN_SDK_NATIVE"
    PATH="$SDK_DIR/Bin:$PATH"
else
    echo "UNAVAILABLE: vendored Vulkan SDK not present"; exit 77
fi

rm -rf "$WORK"; mkdir -p "$WORK"
git -C "$REPO" archive HEAD | tar -x -C "$WORK"

# Materialize locked, gitignored artifacts into the export so the in-export
# contract tests verify the same vendored set as a developer tree. Hosts
# without the vendored set (Linux CI: apt-pinned system SDKs) rely on the
# per-platform verify rules in test_locked_dependencies instead.
if [ "$(uname -s)" != "Linux" ]; then
    for f in Lib/vulkan-1.lib Lib/shaderc_shared.lib \
             Bin/VkLayer_khronos_validation.json Bin/dxc.exe Bin/glslang.exe; do
        src="$REPO/engine/external/VulkanSDK/$f"
        dst="$WORK/engine/external/VulkanSDK/$f"
        if [ ! -f "$src" ]; then
            echo "UNAVAILABLE: vendored VulkanSDK file missing in source tree: $f"; exit 77
        fi
        mkdir -p "$(dirname "$dst")"
        cp "$src" "$dst"
    done
fi
if [ -d "$REPO/engine/external/d3d12" ]; then
    cp -r "$REPO/engine/external/d3d12" "$WORK/engine/external/"
fi

# 原生 cmake/ctest 需要原生路径（Git Bash 的 /tmp 等 MSYS 路径不认）。
WORK_NATIVE="$WORK"
if command -v cygpath >/dev/null 2>&1; then
    WORK_NATIVE=$(cygpath -m "$WORK")
fi
cmake -S "$WORK_NATIVE/engine" -B "$WORK_NATIVE/build" -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND="$BACKEND" 2>&1 | tee "$WORK/configure.log"
# 无 GL 承诺：configure log 不得出现 OpenGL 发现（Task 6 条件 7 复用此断言）。
if [ "$BACKEND" = "vulkan" ] && grep -qi "found OpenGL" "$WORK/configure.log"; then
    echo "clean-room violation: OpenGL discovered in a vulkan-only configure"; exit 3
fi
cmake --build "$WORK_NATIVE/build" --parallel
ctest --test-dir "$WORK_NATIVE/build" -LE "graphics|fuzz" --output-on-failure
echo "CLEAN-ROOM OK (backend=$BACKEND)"
