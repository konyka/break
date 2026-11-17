# Crash symbolization: Mach-O symbol files

Status: Done

## Goal

missing_capabilities section 14 lists macOS symbolization as missing:
`break_crash_symbolize` reads only 64-bit ELF. Let the symbol store resolve
addresses in thin 64-bit Mach-O files (executables, dylibs, bundles, dSYM
companions) so macOS crashes can be symbolized on the Linux server.

## Rules

- Magic `0xfeedfacf` (little-endian 64-bit), CPU x86_64 or arm64, file type
  EXECUTE, DYLIB, BUNDLE or DSYM. Universal (fat), 32-bit, big-endian and
  other file types are refused.
- Every load command is bounds-checked: `cmdsize` >= 8, a multiple of 8,
  inside `sizeofcmds`; `ncmds` <= 4096; a segment's `cmdsize` equals
  72 + 80 * nsects; section `addr + size` does not wrap; at most one
  `LC_SYMTAB`, whose symbol and string tables lie inside the file.
- Symbols kept: not a stab, type `N_SECT`, `n_sect` naming a section with
  instructions (`S_ATTR_PURE_INSTRUCTIONS` or `S_ATTR_SOME_INSTRUCTIONS`),
  name inside the string table and non-empty. Mach-O has no symbol sizes, so
  a symbol extends to the next higher symbol address or the end of its
  section, whichever is first. One leading `_` is dropped (C names).
- Addresses are relative to the `__TEXT` segment's vmaddr, so a record's
  module bias is the image header's load address and the module offset is
  looked up directly (`is_exec` is false). A symbol below `__TEXT` is skipped.
- `LC_UUID` gives the build id as 32 lowercase hex digits.
- `break_crash_symbols_open` dispatches on the magic; the store uses it.

## Tests (test_break_crash_symbolize.c)

Hand-built Mach-O images (no SDK needed):
1. Lookup, sizes from neighbours and section end, aliases, local symbols,
   undefined/abs/stab/data-section symbols skipped, underscore dropped.
2. Executable with `__TEXT` at 0x100000000 resolves header-relative offsets.
3. UUID as hex; no UUID gives "".
4. arm64 accepted; wrong CPU, file type, 32-bit, big-endian, fat refused.
5. Every truncation refused; each structural corruption refused; random
   load-command bytes never crash.
6. Store: a Mach-O module in `<root>/<id>/<module>` resolves through
   `break_crash_symbol_store_lookup` and `break_crash_symbolize_address`.
7. When clang and ld64.lld exist, a real dylib and executable agree with
   `llvm-nm`; otherwise the case reports a skip.

## Result

Delivered as planned. `test_break_crash_symbolize` has 37 cases (14 new).
Additions beyond the plan: an `ncmds` cap case, alignment of unknown load
commands, a code symbol below `__TEXT`, a command count running past the
file end, and an `N_BNSYM` stab entry. Of 29 mutations, the remaining-bytes
check is caught only under ASan; the `n_sect` upper bound and the alias
skip are equivalent mutations. Not done: fat files, arm64 frame walking,
real macOS crash records.
