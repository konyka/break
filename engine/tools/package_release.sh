#!/usr/bin/env bash
# package_release.sh <repo_root> <build_dir> <out_dir> <version>
# 生成离线 artifact 包：每平台二进制 + shader 产物 + 配置 + 收据 + SHA256SUMS + MANIFEST。
set -euo pipefail
REPO="${1:?}"; BUILD="${2:?}"; OUT="${3:?}"; VER="${4:?}"
PKG="$OUT/purec-engine-$VER"
rm -rf "$PKG"; mkdir -p "$PKG"/{bin,shaders,config,evidence,docs}

# 二进制与运行时（存在的才收；缺失 = 该平台 UNAVAILABLE，记入 MANIFEST）。
# 命名矩阵：POSIX = <name> / lib<name>.a；Windows = <name>.exe / <name>.lib（无 lib 前缀）。
for n in engine_demo dxx_break; do
    for sfx in "" ".exe"; do
        [ -f "$BUILD/$n$sfx" ] && cp "$BUILD/$n$sfx" "$PKG/bin/"
    done
done
for n in engine engine_rhi_vulkan engine_rhi_metal engine_rhi_d3d12 engine_rhi_opengl engine_rhi_headless; do
    for pre in "lib" ""; do
        for ext in ".a" ".lib"; do
            [ -f "$BUILD/$pre$n$ext" ] && cp "$BUILD/$pre$n$ext" "$PKG/bin/"
        done
    done
done
# D3D12 Agility SDK 运行时（Windows 包）
find "$BUILD" "$REPO/engine/external" -name 'D3D12Core.dll' 2>/dev/null | head -1 | while read -r d; do
    cp "$d" "$PKG/bin/"
done
# shader 产物：metallib（macOS/iOS）、DXIL（Windows）、SPIR-V（全部）
find "$BUILD" -name '*.metallib' -exec cp {} "$PKG/shaders/" \; 2>/dev/null || true
find "$BUILD" -name '*.dxil' -not -path '*/Testing/*' -exec cp {} "$PKG/shaders/" \; 2>/dev/null || true
find "$BUILD" -name '*.spv' -exec cp {} "$PKG/shaders/" \; 2>/dev/null || true
# 注意：repo 根的 d3d12_shader_gate.dxil 是冻结文件，永不进包（上面的 find 只扫 BUILD）。

# 配置与证据
cp "$REPO/engine/assets/rhi_backend_rollout.json" "$PKG/config/"
cp "$REPO/engine/external/locked_dependencies.json" "$PKG/config/"
# rhi_opengl_removal_migration.md 随已取消的 OpenGL 移除计划不再产出，容忍缺失
cp "$REPO/docs/rhi_opengl_removal_migration.md" "$REPO/docs/rhi_rollback_runbook.md" "$PKG/docs/" 2>/dev/null || true
find "$BUILD" -name 'receipt*.json' -exec cp {} "$PKG/evidence/" \; 2>/dev/null || true
# bench 收据命名为 rhi_receipt_*.json（前缀 rhi_），单独收集
find "$BUILD" -name 'rhi_receipt*.json' -exec cp {} "$PKG/evidence/" \; 2>/dev/null || true

# MANIFEST + SHA256SUMS（离线可验）
( cd "$PKG" && find . -type f | sort > MANIFEST.txt && \
  { echo "version: $VER"; echo "commit: $(git -C "$REPO" rev-parse HEAD)"; \
    echo "locked_deps: config/locked_dependencies.json"; \
    echo "built: $(date -u +%FT%TZ)"; } > MANIFEST )
( cd "$PKG" && find . -type f ! -name SHA256SUMS -exec sha256sum {} + > SHA256SUMS )
( cd "$OUT" && tar -czf "purec-engine-$VER.tar.gz" "purec-engine-$VER" && \
  sha256sum "purec-engine-$VER.tar.gz" > "purec-engine-$VER.tar.gz.sha256" )
echo "release package: $OUT/purec-engine-$VER.tar.gz"
