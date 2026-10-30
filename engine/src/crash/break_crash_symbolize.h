#pragma once
/* ==========================================================================
 *  break_crash_symbolize — Stage 5 subproject 3, server side: turn a crash
 *  RECORD (break_crash.h) plus the build's symbol files into readable frames
 *  (docs/design/crash_symbolization.md).
 *
 *  Meant for the SERVER (or a developer machine): it reads symbol files from
 *  disk and is never linked into a shipped game binary. Every input is
 *  untrusted: the record comes from a client, and the ELF file is validated
 *  as hostile (all offsets and sizes bounds-checked, no allocation sized by an
 *  unchecked field, a corrupt file gives NULL, never a crash).
 *
 *  Scope: 64-bit little-endian ELF, x86-64 frames. The unwinder follows the
 *  saved-RBP chain (frame-pointer code) through the record's stack window; it
 *  does NOT use DWARF CFI, so code compiled without frame pointers yields a
 *  short, possibly wrong chain, and every frame beyond the first is marked as
 *  a guess in the documentation of this limitation, not in the data.
 * ========================================================================== */

#include <core/types.h>

#define BREAK_CRASH_SYMBOLIZE_MAX_FRAMES 32u
#define BREAK_CRASH_SYMBOLIZE_NAME_MAX 128u

/* ---- ELF symbol table --------------------------------------------------- */

typedef struct BreakElfSymbols BreakElfSymbols;

/* Reads the .symtab (or, when stripped, the .dynsym) of a 64-bit LE ELF.
 * NULL for a file that is missing, not that format, larger than 256 MiB, or
 * structurally inconsistent anywhere (section table, string table, symbol
 * entries pointing outside the file). A file with no usable symbols still
 * loads (every lookup then fails). */
BreakElfSymbols *break_elf_symbols_open(const char *path);
void break_elf_symbols_destroy(BreakElfSymbols *s); /* NULL is a no-op */
u32 break_elf_symbols_count(const BreakElfSymbols *s);

/* Finds the function symbol (STT_FUNC with a non-zero size, or STT_NOTYPE/
 * STT_GNU_IFUNC placed in an executable section) that CONTAINS the virtual
 * address `vaddr` (as the file states it, i.e. before the load bias): the
 * address must satisfy start <= vaddr < start + size. An address in padding
 * between functions, or past the last one, is not found. On success the name
 * is copied (cut to out_cap-1) and *out_offset = vaddr - start. */
bool break_elf_symbols_lookup(const BreakElfSymbols *s, u64 vaddr, char *out_name,
                              usize out_cap, u64 *out_offset);

/* True for a fixed-address executable (ET_EXEC): its symbols are absolute
 * virtual addresses and the load bias must NOT be subtracted before lookup.
 * Shared objects and PIE executables (ET_DYN) are bias-relative. */
bool break_elf_symbols_is_exec(const BreakElfSymbols *s);

/* The GNU build id (NT_GNU_BUILD_ID) as lowercase hex, "" when absent. */
const char *break_elf_symbols_build_id(const BreakElfSymbols *s);

/* ---- frame recovery from a crash record -------------------------------- */

typedef struct BreakCrashRecord BreakCrashRecord; /* break_crash.h */

typedef struct BreakCrashFrame {
    u64 pc;                  /* the instruction address the frame was executing / will return to */
    u64 module_offset;       /* pc - the module's load bias (the address inside the module file) */
    char module[256];        /* the module's basename; "" when no recorded module contains pc */
    char symbol[BREAK_CRASH_SYMBOLIZE_NAME_MAX]; /* "" when unresolved */
    u64 symbol_offset;       /* pc - the symbol's start (0 when unresolved) */
    bool resolved;           /* symbol[] holds a name */
} BreakCrashFrame;

/* Resolves one address: finds the recorded module containing `pc`
 * (load-offset <= pc < load-offset + size) and then the function in that
 * module's symbols. `symbol_root` is a directory laid out as
 * <root>/<build-id>/<module-basename> holding the unstripped binaries; the
 * build id is the RECORD's. Both path parts are validated (the build id
 * against the record grammar's charset, the module name as a basename) so a
 * hostile record cannot name a path outside the root. A module or symbol
 * that cannot be found leaves `resolved` false but still fills pc, module and
 * module_offset. */
typedef struct BreakCrashSymbolStore BreakCrashSymbolStore;
BreakCrashSymbolStore *break_crash_symbol_store_open(const char *symbol_root);
void break_crash_symbol_store_destroy(BreakCrashSymbolStore *st); /* NULL no-op */
/* Looks a module-relative address up by raw names. Both names are validated
 * (build id [0-9a-z-]{1,64}, module = one printable path component), so
 * "..", "a/b" or an over-long name find nothing. For a fixed-address
 * executable pass the absolute address. */
bool break_crash_symbol_store_lookup(BreakCrashSymbolStore *st, const char *build_id, const char *module,
                                     u64 module_offset, char *out_name, usize out_cap, u64 *out_offset);
void break_crash_symbolize_address(BreakCrashSymbolStore *st, const BreakCrashRecord *r, u64 pc,
                                   BreakCrashFrame *out);

/* Recovers up to `cap` (<= 32) frames. Frame 0 is the faulting rip. The rest
 * come from the saved-RBP chain read out of the record's stack window:
 *   [rbp]   = the caller's saved rbp,    [rbp+8] = the return address.
 * The walk stops at the first of: the window does not contain both words at
 * rbp, the saved rbp is not strictly greater than the current one (a
 * frame-pointer chain only grows toward higher addresses; this also stops
 * loops), the return address is 0, the cap. Every read is inside the window.
 * Returns the number of frames (>= 1 when the record has a non-zero rip,
 * else 0). The first frame's pc is exact; frames after it are return
 * addresses (pc - 1 is used for the symbol lookup so a call that is the last
 * instruction of a function is attributed to the caller). */
u32 break_crash_symbolize_record(BreakCrashSymbolStore *st, const BreakCrashRecord *r,
                                 BreakCrashFrame *frames, u32 cap);

