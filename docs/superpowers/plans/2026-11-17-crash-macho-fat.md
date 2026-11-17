# Crash symbolization: universal (fat) Mach-O files

Status: Done

## Goal

`break_macho_symbols_open` refuses universal files, so a symbol store fed
with the usual macOS build output (an x86_64 + arm64 universal binary) needs
`lipo -thin` first. Read the slice that matches the crash's CPU directly.

## API

- `BreakElfSymbols *break_macho_symbols_open_cpu(const char *path, u32 cpu_type);`
  opens a thin file whose CPU is `cpu_type`, or the slice of that CPU in a
  universal file. Only x86_64 (`0x01000007`) and arm64 (`0x0100000c`) are
  valid values.
- `break_macho_symbols_open(path)` and `break_crash_symbols_open(path)` take
  the x86_64 slice of a universal file (frame recovery is x86-64 only); a
  thin file of either CPU still opens as before.

## Rules

- Header big-endian: `0xcafebabe` (32-bit entries, 20 bytes) or `0xcafebabf`
  (64-bit entries, 32 bytes). `nfat_arch` 1..32 (`0xcafebabe` is also a Java
  class magic; those carry a version there, far above 32).
- Every entry's slice lies inside the file and starts after the entry table;
  slices do not overlap; no two entries share a CPU type.
- The chosen slice is parsed as a thin file of exactly `size` bytes; its CPU
  must equal the entry's. No slice of the requested CPU gives NULL.

## Tests (test_break_crash_symbolize.c)

1. Hand-built universal image (x86_64 + arm64 slices told apart by UUID):
   both magics, either CPU selected, default picks x86_64, store lookup.
2. A thin file opened for the other CPU is refused.
3. Refused: 0 or 33 entries, slice past the file, slice overlapping the
   table, overlapping slices, duplicate CPU, slice CPU differing from the
   entry, invalid requested CPU, every truncation.
4. With `llvm-lipo`: a real universal dylib agrees with `llvm-nm --arch`.

## Result

Delivered as planned; one case added for the 32-entry limit and for a
requested CPU of 0. `test_break_crash_symbolize` has 43 cases. Of 17
mutations, the entry-table bound is caught only under ASan and the
zero-entry check is equivalent (no slice can be picked). Not done: arm64
frame walking, so the store keeps taking the x86_64 slice.

