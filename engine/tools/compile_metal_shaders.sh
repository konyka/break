#!/bin/sh
# Offline Metal shader pipeline (plan C Task 10):
#   *_vk GLSL (+ shared *.comp) -> SPIR-V (glslc) -> MSL (spirv-cross)
#   -> .air (xcrun metal) -> engine.metallib (xcrun metallib) + manifest inputs.
#
# Binding contract (MSL index from GLSL set/binding — per-namespace
# multipliers keep every namespace inside its hardware limit: buffers cap at
# 30, samplers at 15, textures at 127 on macOS):
#   combined samplers (sampler2D/Cube/Array):  set*4  + B  (texture+sampler)
#   samplerBuffer / image:                     set*16 + B  (texture only)
#   uniform/buffer blocks:                     set*8  + B  (buffer)
# The GLSL temp copy has its `binding = B` rewritten accordingly
# (spirv-cross --msl-decoration-binding ignores the set and uses the binding
# verbatim). Push-constant blocks carry no binding; spirv-cross puts them at
# [[buffer(0)]], which collides with set0/binding0 SSBOs in the compute
# shaders — so the MSL text is post-fixed to [[buffer(29)]] (30 is taken by
# spirv-cross's own spvBufferSizeConstants for SSBO .length(); 30/31 stay
# reserved for the toolchain).
#
# Usage: compile_metal_shaders.sh <shader_dir> <out_dir> [sdk]
set -eu
SHADER_DIR="$1"; OUT_DIR="$2"; SDK="${3:-macosx}"
mkdir -p "$OUT_DIR/spv" "$OUT_DIR/msl" "$OUT_DIR/air" "$OUT_DIR/tmp"
: > "$OUT_DIR/manifest.lines"

# Flatten one GLSL file: rewrite `binding = B` per declaration kind (the
# multiplier keeps every MSL namespace inside its hardware limit — buffers
# cap at 30, samplers at 15, textures at 127 on macOS):
#   combined samplers (sampler2D/Cube/Array):  set*4  + B  (texture+sampler)
#   samplerBuffer / image:                     set*16 + B  (texture only)
#   uniform/buffer blocks:                     set*8  + B  (buffer)
# spirv-cross --msl-decoration-binding uses the binding verbatim and ignores
# the set, so the flattened value IS the MSL index. The [^_a-zA-Z] guard
# keeps "offset = N" from matching "set = N". The push-constant block type
# name goes to the side channel file $3 ("-" when absent).
flatten_glsl() {
    _src="$1"; _dst="$2"; _pushfile="$3"
    awk '
        BEGIN { push_type = "-" }
        {
            line = $0; s = 0; mult = 0
            if (match(line, /layout\(push_constant\)[ \t]*uniform[ \t]+[A-Za-z_][A-Za-z0-9_]*/)) {
                seg = substr(line, RSTART, RLENGTH)
                sub(/.*uniform[ \t]+/, "", seg)
                push_type = seg
            }
            if (match(line, /(^|[^_a-zA-Z])set[ \t]*=[ \t]*[0-9]+/)) {
                ss = substr(line, RSTART, RLENGTH)
                gsub(/[^0-9]/, "", ss); s = ss + 0
            }
            if (line ~ /uniform[ \t]+samplerBuffer/)      mult = 16
            else if (line ~ /uniform[ \t]+sampler/)       mult = 4
            else if (line ~ /[ui]?image[0-9]/)            mult = 16
            else if (line ~ /(uniform|buffer)[ \t]+[A-Z]/) mult = 8
            if (mult > 0 && match(line, /binding[ \t]*=[ \t]*[0-9]+/)) {
                seg = substr(line, RSTART, RLENGTH)
                b = seg; gsub(/[^0-9]/, "", b); nb = s * mult + b
                if (mult == 8 && nb > 27) {
                    # M5/I1: 28 is the ray-query acceleration-structure slot
                    # (setAccelerationStructure:atBufferIndex:28, Task 12),
                    # 29 push constants, 30/31 belong to the toolchain —
                    # a future set3 binding>=4 must fail loudly, not collide.
                    print "flatten: buffer index " nb " out of range in " FILENAME > "/dev/stderr"
                    exit 1
                }
                sub(/[0-9]+/, nb, seg)
                line = substr(line, 1, RSTART - 1) seg substr(line, RSTART + RLENGTH)
            }
            print line
        }
        END { print push_type > pushfile }
    ' pushfile="$_pushfile" "$_src" > "$_dst"
}

# Post-fix the MSL: push-constant parameter (constant <PushType>& <inst>
# [[buffer(N)]]) moves to [[buffer(29)]]. Slot 30 is taken by spirv-cross's
# own spvBufferSizeConstants (SSBO .length() support); 30/31 stay reserved
# for the toolchain. The rewrite operates on the matched segment only — the
# kernel signature is a single line with several buffer attributes, so a
# bare sub() would rewrite the first attribute on the line.
fixup_push() {
    _msl="$1"; _push_type="$2"
    [ "$_push_type" = "-" ] && return 0
    awk -v pt="$_push_type" '
        {
            pat = "constant " pt "& [A-Za-z_][A-Za-z0-9_]* \\[\\[buffer\\([0-9]+\\)\\]\\]"
            if (match($0, pat)) {
                seg = substr($0, RSTART, RLENGTH)
                sub(/\[\[buffer\([0-9]+\)\]\]/, "[[buffer(29)]]", seg)
                $0 = substr($0, 1, RSTART - 1) seg substr($0, RSTART + RLENGTH)
            }
            print
        }
    ' "$_msl" > "$_msl.fixed"
    mv "$_msl.fixed" "$_msl"
}

# Task 11: runtime define-injection variants. The engine injects defines
# into shader texts at runtime (core/shader_io.c shader_inject_define:
# insert "#define NAME 1\n" immediately after the first #version line;
# chained injections re-insert at the same head, so the final order is the
# REVERSE of the call order). rhi_shader_create hashes the INJECTED text,
# so the offline pipeline must compile each variant and the manifest key
# must be the hash of byte-identical injected text. This awk port replicates
# the injection byte-for-byte (all corpus shaders start with #version and
# end with a newline, so the no-trailing-newline lead case never fires).
inject_defines() {
    _src="$1"; _dst="$2"; _defs="$3"   # defs: comma-separated, call order
    awk -v defs="$_defs" '
        BEGIN { n = split(defs, d, ","); injected = 0 }
        {
            if (!injected && $0 ~ /^[ \t]*#version[ \t]/) {
                print
                for (i = n; i >= 1; --i) print "#define " d[i] " 1"
                injected = 1
                next
            }
            print
        }
        END {
            if (!injected) {
                print "inject_defines: no #version line in source" > "/dev/stderr"
                exit 1
            }
        }
    ' "$_src" > "$_dst"
}

# Actual define combinations triggered by engine call sites (grep
# shader_inject_define engine/src/main.c engine/src/renderer/*.c — the
# contract test pins this list). Row: <file> <comma-separated defines in
# call order>. pbr_clustered_vk.frag chains HAS_IBL -> HAS_POINT_SHADOW ->
# FORWARD_MRT (main.c:491-498), and the texture-array path appends
# CLUSTERED_ARR (main.c:535); with the R703a LOD cross-fade on, the
# instanced pipelines also append LOD_FADE. The deferred renderer injects HAS_IBL into
# every fragment stage (deferred.c defrd_inject_define — byte-identical to
# shader_inject_define on these #version-first files).
VARIANTS='
blinn_phong_vk.vert FORWARD_MRT
blinn_phong_vk.frag FORWARD_MRT
blinn_phong_arr_vk.vert FORWARD_MRT
blinn_phong_arr_vk.frag FORWARD_MRT
pbr_clustered_vk.vert FORWARD_MRT
pbr_clustered_vk.frag HAS_IBL,HAS_POINT_SHADOW,FORWARD_MRT
pbr_clustered_vk.frag HAS_IBL,HAS_POINT_SHADOW,FORWARD_MRT,CLUSTERED_ARR
pbr_clustered_inst_vk.vert FORWARD_MRT
pbr_clustered_inst_vk.vert FORWARD_MRT,LOD_FADE
pbr_clustered_vk.frag HAS_IBL,HAS_POINT_SHADOW,FORWARD_MRT,LOD_FADE
pbr_clustered_skin_vk.vert FORWARD_MRT
pbr_clustered_arr_vk.vert FORWARD_MRT
instanced_vk.vert FORWARD_MRT
instanced_vk.frag FORWARD_MRT
instanced_vk.vert FORWARD_MRT,LOD_FADE
instanced_vk.frag FORWARD_MRT,LOD_FADE
skinned_vk.vert FORWARD_MRT
skinned_vk.frag FORWARD_MRT
skybox_vk.frag FORWARD_MRT
terrain_vk.vert FORWARD_MRT
terrain_vk.frag FORWARD_MRT
water_vk.vert FORWARD_MRT
water_vk.frag FORWARD_MRT
particle.vert FORWARD_MRT
particle.frag FORWARD_MRT
deferred_light_vk.frag HAS_IBL
gbuffer_vk.frag HAS_IBL
gbuffer_arr_vk.frag HAS_IBL
gbuffer_skinned_vk.frag HAS_IBL
'

process_one() {
    _src="$1"; _stage="$2"; _model="$3"   # e.g. vert/vertex
    base=$(basename "$_src")              # e.g. blinn_phong_vk.vert
    case "$base" in
        *_vk.*) name=${base%_vk.*} ;;     # blinn_phong
        *.vert) name=${base%.vert} ;;     # particle (shared source)
        *.frag) name=${base%.frag} ;;
        *.comp) name=${base%.comp} ;;     # cull
    esac
    entry="${name}_${_stage}"
    flatten_glsl "$_src" "$OUT_DIR/tmp/$base.flat" "$OUT_DIR/tmp/$base.push"
    push_type=$(cat "$OUT_DIR/tmp/$base.push")
    glslc --target-env=vulkan1.2 -fshader-stage="$_stage" \
        "$OUT_DIR/tmp/$base.flat" -o "$OUT_DIR/spv/$base.spv"
    spirv-cross "$OUT_DIR/spv/$base.spv" --msl --msl-version 20300 \
        --msl-decoration-binding \
        --rename-entry-point main "$entry" "$_stage" \
        --output "$OUT_DIR/msl/$entry.metal"
    fixup_push "$OUT_DIR/msl/$entry.metal" "$push_type"
    xcrun -sdk "$SDK" metal -c "$OUT_DIR/msl/$entry.metal" \
        -o "$OUT_DIR/air/$entry.air"
    printf '%s %s\n' "$base" "$entry" >> "$OUT_DIR/manifest.lines"
}

for src in "$SHADER_DIR"/*_vk.vert; do  [ -e "$src" ] || continue; process_one "$src" vert vertex; done
for src in "$SHADER_DIR"/*_vk.frag; do  [ -e "$src" ] || continue; process_one "$src" frag fragment; done
# Compute shaders are shared GLSL (no _vk infix); *_gl.comp are the GL variants
# and *_hlsl.comp are D3D12 HLSL sidecars (not GLSL, glslc cannot compile them).
for src in "$SHADER_DIR"/*.comp; do
    [ -e "$src" ] || continue
    case "$src" in *_gl.comp|*_hlsl.comp) continue ;; esac
    process_one "$src" comp kernel
done
# Shared-source graphics shaders used by the Vulkan path without a _vk
# variant (particles, CSM depth pass), so the Metal pipeline needs them too
# (Task 11/13).
for src in particle.vert particle.frag depth_only.vert depth_only.frag; do
    [ -e "$SHADER_DIR/$src" ] || continue
    case "$src" in
        *.vert) p_stage=vert; p_model=vertex ;;
        *.frag) p_stage=frag; p_model=fragment ;;
    esac
    process_one "$SHADER_DIR/$src" "$p_stage" "$p_model"
done

# Task 11: runtime define-injection variants. Variant texts live in
# $OUT_DIR/variants (gen_metal_shader_manifest hashes them from there).
mkdir -p "$OUT_DIR/variants"
echo "$VARIANTS" | while read -r vfile vdefs; do
    [ -n "$vfile" ] || continue
    [ -f "$SHADER_DIR/$vfile" ] || {
        echo "variant source missing: $vfile" >&2
        exit 1
    }
    vbase=$(basename "$vfile")
    case "$vbase" in
        *_vk.*) vname=${vbase%_vk.*} ;;
        *.vert) vname=${vbase%.vert} ;;
        *.frag) vname=${vbase%.frag} ;;
        *.comp) vname=${vbase%.comp} ;;
    esac
    case "$vbase" in
        *.vert) vstage=vert ;;
        *.frag) vstage=frag ;;
        *.comp) vstage=comp ;;
    esac
    vsuffix=$(printf '%s' "$vdefs" | tr 'A-Z,' 'a-z_')
    ventry="${vname}_${vstage}__${vsuffix}"
    vtext="$OUT_DIR/variants/$vbase.$vsuffix"
    inject_defines "$SHADER_DIR/$vbase" "$vtext" "$vdefs"
    flatten_glsl "$vtext" "$OUT_DIR/tmp/$vbase.$vsuffix.flat" \
        "$OUT_DIR/tmp/$vbase.$vsuffix.push"
    vpush_type=$(cat "$OUT_DIR/tmp/$vbase.$vsuffix.push")
    glslc --target-env=vulkan1.2 -fshader-stage="$vstage" \
        "$OUT_DIR/tmp/$vbase.$vsuffix.flat" -o "$OUT_DIR/spv/$vbase.$vsuffix.spv"
    spirv-cross "$OUT_DIR/spv/$vbase.$vsuffix.spv" --msl --msl-version 20300 \
        --msl-decoration-binding \
        --rename-entry-point main "$ventry" "$vstage" \
        --output "$OUT_DIR/msl/$ventry.metal"
    fixup_push "$OUT_DIR/msl/$ventry.metal" "$vpush_type"
    xcrun -sdk "$SDK" metal -c "$OUT_DIR/msl/$ventry.metal" \
        -o "$OUT_DIR/air/$ventry.air"
    printf 'variants/%s %s\n' "$vbase.$vsuffix" "$ventry" \
        >> "$OUT_DIR/manifest.lines"
done
xcrun -sdk "$SDK" metallib "$OUT_DIR"/air/*.air -o "$OUT_DIR/engine.metallib"
echo "metal shader pipeline: $(wc -l < "$OUT_DIR/manifest.lines" | tr -d ' ') shaders -> $OUT_DIR/engine.metallib"
