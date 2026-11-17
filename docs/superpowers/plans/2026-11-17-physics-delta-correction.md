# Physics delta correction

Status: Done

## Goal

`physics_sync_encode_correction` always sends a full `physics_snapshot_save`
payload. missing_capabilities section 9 lists incremental sync as missing. Add
a delta packet that carries only the bytes that changed relative to a
snapshot both peers already hold.

## Format

Little-endian, 28-byte header followed by runs.

    magic u32 = 0x444e5350 ("PSND"), tick u32, baseline_tick u32,
    baseline_size u32, baseline FNV-1a 32 u32,
    target_size u32, target FNV-1a 32 u32
    run: offset u32, len u32, len bytes

The baseline is treated as zero-extended to `target_size`, so a target that
grew only carries its nonzero tail bytes. Runs must have len > 0, be strictly
ascending and non-overlapping, and end within `target_size`. The decoder
rebuilds the full target and checks its checksum.

## API (physics_sync.h)

- `physics_sync_encode_delta(tick, baseline_tick, baseline, baseline_size,
  target, target_size, buffer, capacity, out_size)`: `*out_size` always gets
  the required size; buffer untouched when too small.
- `physics_sync_delta_ticks(data, size, out_tick, out_baseline_tick)`: lets the
  receiver pick the baseline.
- `physics_sync_decode_delta(baseline, baseline_size, data, size, target,
  target_capacity, out_target_size, out_tick)`: byte level. Outputs untouched
  on failure; target contents unspecified on failure.
- `physics_sync_apply_delta(tracker, pw, baseline, baseline_size, data, size,
  target, target_capacity, out_tick)`: decode then restore; same atomicity as
  `physics_sync_apply_correction`.

## Tests (test_physics_sync.c)

1. Byte-level encoding: exact run layout, identical input gives header only,
   capacity too small, grown target with zero tail, shrunk target.
2. Byte-level decode rejections, each isolated so only one rule fires:
   magic, short header, baseline size/checksum, target checksum, capacity,
   zero-length run, overlap, unsorted, out of bounds (including u32 wrap),
   truncated run.
3. World round trip: delta smaller than full correction, hashes match,
   tracker reset; failures leave world, tracker and tick unchanged.

## Out of scope

core_app keeping per-peer baselines and choosing delta vs full packets: next
slice.

## Result

- Four functions added to `physics_sync`; `test_physics_sync` has 10 cases.
- Baseline size compare removed: the baseline checksum already depends on
  the length, and mutation testing showed the compare was redundant.
- 26 mutations, all killed after adding gap-threshold, mid-baseline and
  tracker-reset assertions.
