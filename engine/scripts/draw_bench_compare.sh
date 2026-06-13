#!/usr/bin/env bash
# Compare DrawBench: unified mega-path vs legacy (unified off).
# Usage: draw_bench_compare.sh [engine_demo] [frames] [out_dir]
set -euo pipefail

DEMO="${1:-./engine_demo}"
FRAMES="${2:-120}"
OUTDIR="${3:-./draw_bench_out}"

if [[ ! -x "$DEMO" ]]; then
    echo "error: engine_demo not found or not executable: $DEMO" >&2
    exit 1
fi

mkdir -p "$OUTDIR"

run_phase() {
    local name="$1"
    shift
    local csv="$OUTDIR/draw_bench_${name}.csv"
    echo "--- phase: $name -> $csv ---"
    env BREAK_DRAW_BENCH=1 \
        BREAK_DRAW_BENCH_EXPORT="$csv" \
        BREAK_FRAMES="$FRAMES" \
        "$@" \
        "$DEMO" >/dev/null
    if [[ -f "$csv" ]]; then
        grep '^# summary' "$csv" || echo "(no summary line)"
    else
        echo "warning: CSV not written: $csv" >&2
    fi
}

echo "=== DrawBench compare (frames=$FRAMES) ==="
run_phase unified
run_phase legacy \
    BREAK_UNIFIED_SHADOW=0 \
    BREAK_UNIFIED_FORWARD=0 \
    BREAK_UNIFIED_DEFERRED=0

echo ""
echo "Results:"
echo "  unified: $OUTDIR/draw_bench_unified.csv"
echo "  legacy:  $OUTDIR/draw_bench_legacy.csv"
echo "Open in chrome://tracing with profile_trace.json when using F11/PROFILER_TRACE=1."
