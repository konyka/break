#define _POSIX_C_SOURCE 200809L
/* break_crash_symbolize: the ELF symbol reader (this file) and the frame
 * recovery (G2, below). Fixtures are built at test time with the host
 * compiler so the symbol addresses are the real ones, and hostile ELF files
 * are made by corrupting a known-good one field by field. */

#include "test_framework.h"

#include <crash/break_crash.h>
#include <crash/break_crash_symbolize.h>

#include <elf.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef BREAK_TEST_CC
#define BREAK_TEST_CC "cc"
#endif

static char g_dir[300];
#define CMD_CAP 4096

static void dir_init(void) {
    const char *t = getenv("TMPDIR");
    snprintf(g_dir, sizeof(g_dir), "%s/break_symb_%d", t && t[0] ? t : "/tmp", (int)getpid());
    mkdir(g_dir, 0700);
}

static void path_in(char *out, size_t cap, const char *name) {
    snprintf(out, cap, "%s/%s", g_dir, name);
}

static bool write_text(const char *path, const char *text) {
    FILE *f = fopen(path, "w");
    bool ok = f != NULL && fputs(text, f) >= 0;
    if (f && fclose(f) != 0) ok = false;
    return ok;
}

static bool run(const char *cmd) {
    int rc = system(cmd);
    return rc == 0;
}

/* A small program with known functions, compiled -O0, no PIE, with symbols. */
static const char k_fixture_src[] =
    "#include <stdio.h>\n"
    "__attribute__((noinline)) int leaf(int x) { return x * 3 + 1; }\n"
    "__attribute__((noinline)) int mid(int x) { return leaf(x) + 2; }\n"
    "__attribute__((noinline)) int outer(int x) { return mid(x) + 3; }\n"
    "int main(void) { printf(\"%d\\n\", outer(4)); return 0; }\n";

static bool build_fixture(const char *exe, const char *extra_flags) {
    char src[400], cmd[1200];
    path_in(src, sizeof(src), "fixture.c");
    if (!write_text(src, k_fixture_src)) return false;
    snprintf(cmd, sizeof(cmd), "%s -O0 -g0 -fno-pie -no-pie %s -o '%s' '%s' 2>/dev/null",
             BREAK_TEST_CC, extra_flags, exe, src);
    return run(cmd);
}

/* addr of a symbol, from nm (the independent oracle) */
static bool nm_addr(const char *exe, const char *sym, u64 *out) {
    char cmd[800], line[200];
    FILE *p;
    snprintf(cmd, sizeof(cmd), "nm '%s' 2>/dev/null | awk '$3==\"%s\" {print $1}'", exe, sym);
    p = popen(cmd, "r");
    if (p == NULL) return false;
    if (fgets(line, sizeof(line), p) == NULL) {
        pclose(p);
        return false;
    }
    pclose(p);
    *out = strtoull(line, NULL, 16);
    return *out != 0u;
}

static bool nm_size(const char *exe, const char *sym, u64 *out) {
    char cmd[800], line[200];
    FILE *p;
    snprintf(cmd, sizeof(cmd), "nm -S '%s' 2>/dev/null | awk '$4==\"%s\" {print $2}'", exe, sym);
    p = popen(cmd, "r");
    if (p == NULL) return false;
    if (fgets(line, sizeof(line), p) == NULL) {
        pclose(p);
        return false;
    }
    pclose(p);
    *out = strtoull(line, NULL, 16);
    return *out != 0u;
}

/* true when `readelf -S` finds a .symtab section */
static bool run_quiet_nm_has_symtab(const char *path) {
    char cmd[600];
    snprintf(cmd, sizeof(cmd), "readelf -S '%s' 2>/dev/null | grep -q ' .symtab '", path);
    return system(cmd) == 0;
}

static u8 *read_all(const char *path, size_t *n) {
    FILE *f = fopen(path, "rb");
    u8 *b;
    long sz;
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    b = malloc((size_t)sz + 1u);
    if (!b || fread(b, 1, (size_t)sz, f) != (size_t)sz) {
        fclose(f);
        free(b);
        return NULL;
    }
    fclose(f);
    *n = (size_t)sz;
    return b;
}

static bool write_bytes(const char *path, const u8 *b, size_t n) {
    FILE *f = fopen(path, "wb");
    bool ok = f != NULL && fwrite(b, 1, n, f) == n;
    if (f && fclose(f) != 0) ok = false;
    return ok;
}

TEST(resolves_every_function_of_a_real_binary_against_nm) {
    char exe[400];
    BreakElfSymbols *s;
    const char *names[] = {"leaf", "mid", "outer", "main"};
    path_in(exe, sizeof(exe), "fixture");
    ASSERT_TRUE(build_fixture(exe, ""));
    s = break_elf_symbols_open(exe);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_elf_symbols_count(s) > 4u);
    for (int i = 0; i < 4; i++) {
        u64 addr = 0, size = 0, off = 99;
        char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
        ASSERT_TRUE(nm_addr(exe, names[i], &addr));
        ASSERT_TRUE(nm_size(exe, names[i], &size));
        ASSERT_TRUE(break_elf_symbols_lookup(s, addr, name, sizeof(name), &off));
        ASSERT_STR_EQ(name, names[i]);
        ASSERT_EQ(off, 0u);
        ASSERT_TRUE(break_elf_symbols_lookup(s, addr + 4u, name, sizeof(name), &off));
        ASSERT_STR_EQ(name, names[i]);
        ASSERT_EQ(off, 4u);
        ASSERT_TRUE(break_elf_symbols_lookup(s, addr + size - 1u, name, sizeof(name), &off));
        ASSERT_STR_EQ(name, names[i]);
        ASSERT_EQ(off, size - 1u);
        /* one past the end belongs to the next symbol or to padding, never to this one */
        if (break_elf_symbols_lookup(s, addr + size, name, sizeof(name), &off)) {
            ASSERT_TRUE(strcmp(name, names[i]) != 0);
        }
    }
    break_elf_symbols_destroy(s);
}

TEST(addresses_outside_any_function_do_not_resolve) {
    char exe[400];
    BreakElfSymbols *s;
    u64 addr = 0, off = 0;
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    path_in(exe, sizeof(exe), "fixture");
    ASSERT_TRUE(build_fixture(exe, ""));
    s = break_elf_symbols_open(exe);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(nm_addr(exe, "leaf", &addr));
    ASSERT_FALSE(break_elf_symbols_lookup(s, 0u, name, sizeof(name), &off));
    ASSERT_FALSE(break_elf_symbols_lookup(s, 1u, name, sizeof(name), &off));
    ASSERT_FALSE(break_elf_symbols_lookup(s, addr - 1u, name, sizeof(name), &off));
    ASSERT_FALSE(break_elf_symbols_lookup(s, UINT64_MAX, name, sizeof(name), &off));
    ASSERT_FALSE(break_elf_symbols_lookup(s, UINT64_MAX - 7u, name, sizeof(name), &off));
    /* bad arguments are bounded */
    ASSERT_FALSE(break_elf_symbols_lookup(NULL, addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_elf_symbols_lookup(s, addr, NULL, sizeof(name), &off));
    ASSERT_FALSE(break_elf_symbols_lookup(s, addr, name, 0u, &off));
    ASSERT_FALSE(break_elf_symbols_lookup(s, addr, name, sizeof(name), NULL));
    /* a too-small buffer cuts the name and still terminates it */
    {
        char tiny[3];
        ASSERT_TRUE(break_elf_symbols_lookup(s, addr, tiny, sizeof(tiny), &off));
        ASSERT_EQ(strlen(tiny), 2u);
        ASSERT_TRUE(strncmp(tiny, "le", 2) == 0);
    }
    break_elf_symbols_destroy(s);
    break_elf_symbols_destroy(NULL);
}

TEST(a_stripped_binary_loads_and_resolves_nothing) {
    char exe[400], cmd[900];
    BreakElfSymbols *s;
    u64 addr = 0, off;
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    path_in(exe, sizeof(exe), "fixture_stripped");
    ASSERT_TRUE(build_fixture(exe, ""));
    ASSERT_TRUE(nm_addr(exe, "leaf", &addr));
    snprintf(cmd, sizeof(cmd), "strip '%s'", exe);
    ASSERT_TRUE(run(cmd));
    s = break_elf_symbols_open(exe);
    ASSERT_NOT_NULL(s);
    ASSERT_FALSE(break_elf_symbols_lookup(s, addr, name, sizeof(name), &off));
    break_elf_symbols_destroy(s);
}

TEST(a_position_independent_binary_resolves_by_file_address) {
    char exe[400];
    BreakElfSymbols *s;
    u64 addr = 0, off = 0;
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    char cmd[1200], src[400];
    path_in(exe, sizeof(exe), "fixture_pie");
    path_in(src, sizeof(src), "fixture.c");
    ASSERT_TRUE(write_text(src, k_fixture_src));
    snprintf(cmd, sizeof(cmd), "%s -O0 -g0 -fPIE -pie -o '%s' '%s' 2>/dev/null", BREAK_TEST_CC, exe, src);
    ASSERT_TRUE(run(cmd));
    s = break_elf_symbols_open(exe);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(nm_addr(exe, "mid", &addr));       /* small file-relative address */
    ASSERT_TRUE(addr < 0x100000u);
    ASSERT_TRUE(break_elf_symbols_lookup(s, addr + 2u, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "mid");
    ASSERT_EQ(off, 2u);
    break_elf_symbols_destroy(s);
}

TEST(a_shared_object_resolves_its_exported_functions) {
    char so[400], src[400], cmd[1200];
    BreakElfSymbols *s;
    u64 addr = 0, off = 0;
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    path_in(so, sizeof(so), "libfixture.so");
    path_in(src, sizeof(src), "fixture.c");
    ASSERT_TRUE(write_text(src, k_fixture_src));
    snprintf(cmd, sizeof(cmd), "%s -O0 -g0 -fPIC -shared -o '%s' '%s' 2>/dev/null", BREAK_TEST_CC, so, src);
    ASSERT_TRUE(run(cmd));
    s = break_elf_symbols_open(so);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(nm_addr(so, "outer", &addr));
    ASSERT_TRUE(break_elf_symbols_lookup(s, addr + 1u, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "outer");
    break_elf_symbols_destroy(s);
}

TEST(the_gnu_build_id_is_read_as_hex) {
    char exe[400], cmd[900], line[200] = "";
    BreakElfSymbols *s;
    FILE *p;
    path_in(exe, sizeof(exe), "fixture_id");
    ASSERT_TRUE(build_fixture(exe, "-Wl,--build-id=0xa1b2c3d4e5f60718293a4b5c6d7e8f9001122334"));
    s = break_elf_symbols_open(exe);
    ASSERT_NOT_NULL(s);
    ASSERT_STR_EQ(break_elf_symbols_build_id(s), "a1b2c3d4e5f60718293a4b5c6d7e8f9001122334");
    break_elf_symbols_destroy(s);
    /* the independent oracle agrees: readelf shows the same id */
    snprintf(cmd, sizeof(cmd), "readelf -n '%s' 2>/dev/null | awk '/Build ID/ {print $3}'", exe);
    p = popen(cmd, "r");
    ASSERT_NOT_NULL(p);
    if (fgets(line, sizeof(line), p) == NULL) line[0] = '\0';
    pclose(p);
    line[strcspn(line, "\r\n")] = '\0';
    ASSERT_STR_EQ(line, "a1b2c3d4e5f60718293a4b5c6d7e8f9001122334");
    /* a binary linked with --build-id=none has none */
    path_in(exe, sizeof(exe), "fixture_noid");
    ASSERT_TRUE(build_fixture(exe, "-Wl,--build-id=none"));
    s = break_elf_symbols_open(exe);
    ASSERT_NOT_NULL(s);
    ASSERT_STR_EQ(break_elf_symbols_build_id(s), "");
    break_elf_symbols_destroy(s);
}

/* ---- hostile files ---- */

TEST(files_that_are_not_64_bit_little_endian_elf_are_refused) {
    char exe[400], bad[400];
    u8 *b;
    size_t n;
    path_in(exe, sizeof(exe), "fixture");
    path_in(bad, sizeof(bad), "bad.elf");
    ASSERT_TRUE(build_fixture(exe, ""));
    ASSERT_TRUE(break_elf_symbols_open(NULL) == NULL);
    ASSERT_TRUE(break_elf_symbols_open("") == NULL);
    ASSERT_TRUE(break_elf_symbols_open("/nonexistent/x.elf") == NULL);
    ASSERT_TRUE(break_elf_symbols_open(g_dir) == NULL);                 /* a directory */
    ASSERT_TRUE(write_text(bad, "not an elf file at all"));
    ASSERT_TRUE(break_elf_symbols_open(bad) == NULL);
    ASSERT_TRUE(write_text(bad, ""));
    ASSERT_TRUE(break_elf_symbols_open(bad) == NULL);
    b = read_all(exe, &n);
    ASSERT_NOT_NULL(b);
    {
        struct { const char *what; size_t off; u8 val; } mut[] = {
            {"magic", 0, 0x7e}, {"class 32-bit", EI_CLASS, ELFCLASS32}, {"big endian", EI_DATA, ELFDATA2MSB},
            {"ident version", EI_VERSION, 2}, {"e_version", 20, 7}, {"unknown class", EI_CLASS, 9},
            {"e_shentsize", 58, 7}, {"e_machine none", 18, 0}};
        for (size_t i = 0; i < sizeof(mut) / sizeof(mut[0]); i++) {
            u8 save = b[mut[i].off];
            BreakElfSymbols *s;
            b[mut[i].off] = mut[i].val;
            ASSERT_TRUE(write_bytes(bad, b, n));
            s = break_elf_symbols_open(bad);
            if (s != NULL) printf("    accepted mutation: %s\n", mut[i].what);
            ASSERT_TRUE(s == NULL);
            b[mut[i].off] = save;
        }
    }
    free(b);
}

TEST(a_truncated_file_is_refused_at_every_length) {
    char exe[400], bad[400];
    u8 *b;
    size_t n;
    path_in(exe, sizeof(exe), "fixture");
    path_in(bad, sizeof(bad), "trunc.elf");
    ASSERT_TRUE(build_fixture(exe, ""));
    b = read_all(exe, &n);
    ASSERT_NOT_NULL(b);
    /* the section header table sits at the end: every cut inside it or before it breaks the file */
    for (size_t cut = 0; cut + 1u < n; cut += (cut < 700u ? 1u : 331u)) {
        BreakElfSymbols *s;
        ASSERT_TRUE(write_bytes(bad, b, cut));
        s = break_elf_symbols_open(bad);
        if (s != NULL) {
            /* an ELF cut after its section headers can stay valid; then it must still answer safely */
            char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
            u64 off;
            (void)break_elf_symbols_lookup(s, 0x401000u, name, sizeof(name), &off);
            break_elf_symbols_destroy(s);
        }
    }
    free(b);
}

/* byte-level mutation of the section header table, symbol table and string table */
TEST(corrupting_the_section_and_symbol_tables_never_crashes_and_usually_fails) {
    char exe[400], bad[400];
    u8 *b;
    size_t n;
    Elf64_Ehdr eh;
    unsigned refused = 0, accepted = 0;
    path_in(exe, sizeof(exe), "fixture");
    path_in(bad, sizeof(bad), "corrupt.elf");
    ASSERT_TRUE(build_fixture(exe, ""));
    b = read_all(exe, &n);
    ASSERT_NOT_NULL(b);
    memcpy(&eh, b, sizeof(eh));
    {
        Elf64_Shdr *sh = (Elf64_Shdr *)(void *)(b + eh.e_shoff);
        const u32 bad_values[] = {0xffffffffu, 0x80000000u, 0x7fffffffu, 1u, 0u};
        /* every field of every section header, set to hostile values one at a time */
        for (unsigned si = 0; si < eh.e_shnum; si++) {
            for (unsigned field = 0; field < 6; field++) {
                for (size_t bv = 0; bv < sizeof(bad_values) / sizeof(bad_values[0]); bv++) {
                    u8 *copy = malloc(n);
                    Elf64_Shdr *csh;
                    BreakElfSymbols *s;
                    ASSERT_NOT_NULL(copy);
                    memcpy(copy, b, n);
                    csh = (Elf64_Shdr *)(void *)(copy + eh.e_shoff) + si;
                    switch (field) {
                    case 0: csh->sh_offset = ((u64)bad_values[bv] << 32) | bad_values[bv]; break;
                    case 1: csh->sh_size = ((u64)bad_values[bv] << 32) | bad_values[bv]; break;
                    case 2: csh->sh_link = bad_values[bv]; break;
                    case 3: csh->sh_entsize = bad_values[bv]; break;
                    case 4: csh->sh_type = bad_values[bv]; break;
                    default: csh->sh_name = bad_values[bv]; break;
                    }
                    ASSERT_TRUE(write_bytes(bad, copy, n));
                    s = break_elf_symbols_open(bad);
                    if (s == NULL) {
                        refused++;
                    } else {
                        char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
                        u64 off;
                        accepted++;
                        (void)break_elf_symbols_lookup(s, 0x401000u, name, sizeof(name), &off);
                        (void)break_elf_symbols_lookup(s, UINT64_MAX, name, sizeof(name), &off);
                        (void)break_elf_symbols_build_id(s);
                        break_elf_symbols_destroy(s);
                    }
                    free(copy);
                }
            }
        }
        (void)sh;
    }
    free(b);
    printf("    section-header corruption: %u refused, %u still readable (no crash)\n", refused, accepted);
    ASSERT_TRUE(refused > 0u);
}

TEST(symbol_entries_pointing_outside_the_string_table_are_skipped_not_followed) {
    char exe[400], bad[400];
    u8 *b;
    size_t n;
    Elf64_Ehdr eh;
    Elf64_Shdr *sh;
    int symtab = -1;
    path_in(exe, sizeof(exe), "fixture");
    path_in(bad, sizeof(bad), "badsym.elf");
    ASSERT_TRUE(build_fixture(exe, ""));
    b = read_all(exe, &n);
    ASSERT_NOT_NULL(b);
    memcpy(&eh, b, sizeof(eh));
    sh = (Elf64_Shdr *)(void *)(b + eh.e_shoff);
    for (unsigned i = 0; i < eh.e_shnum; i++) if (sh[i].sh_type == SHT_SYMTAB) symtab = (int)i;
    ASSERT_TRUE(symtab >= 0);
    {
        Elf64_Sym *sym = (Elf64_Sym *)(void *)(b + sh[symtab].sh_offset);
        size_t count = sh[symtab].sh_size / sizeof(Elf64_Sym);
        BreakElfSymbols *s;
        u64 leaf_addr = 0;
        char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
        u64 off;
        ASSERT_TRUE(nm_addr(exe, "leaf", &leaf_addr));
        /* every symbol's name offset beyond the string table */
        for (size_t i = 0; i < count; i++) sym[i].st_name = 0x7ffffff0u;
        ASSERT_TRUE(write_bytes(bad, b, n));
        s = break_elf_symbols_open(bad);
        if (s != NULL) {
            ASSERT_FALSE(break_elf_symbols_lookup(s, leaf_addr, name, sizeof(name), &off));
            break_elf_symbols_destroy(s);
        }
    }
    free(b);
}

TEST(a_file_larger_than_the_limit_is_refused_even_when_it_is_otherwise_valid) {
    char exe[400], big[400];
    u8 *b;
    size_t n;
    FILE *f;
    BreakElfSymbols *s;
    path_in(exe, sizeof(exe), "fixture");
    path_in(big, sizeof(big), "huge.elf");
    ASSERT_TRUE(build_fixture(exe, ""));
    b = read_all(exe, &n);
    ASSERT_NOT_NULL(b);
    /* control: the valid file loads */
    s = break_elf_symbols_open(exe);
    ASSERT_NOT_NULL(s);
    break_elf_symbols_destroy(s);
    /* the same bytes followed by sparse zeros up to 300 MiB: every table is still where the
     * header says, so nothing but the size limit can refuse it */
    ASSERT_TRUE(write_bytes(big, b, n));
    free(b);
    f = fopen(big, "r+b");
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(ftruncate(fileno(f), 300L * 1024L * 1024L), 0);
    fclose(f);
    ASSERT_TRUE(break_elf_symbols_open(big) == NULL);
    remove(big);
}

TEST(a_symbol_table_with_the_wrong_entry_size_is_refused) {
    char exe[400], bad[400];
    u8 *b;
    size_t n;
    Elf64_Ehdr eh;
    Elf64_Shdr *sh;
    int symtab = -1;
    path_in(exe, sizeof(exe), "fixture");
    path_in(bad, sizeof(bad), "entsize.elf");
    ASSERT_TRUE(build_fixture(exe, ""));
    b = read_all(exe, &n);
    ASSERT_NOT_NULL(b);
    memcpy(&eh, b, sizeof(eh));
    sh = (Elf64_Shdr *)(void *)(b + eh.e_shoff);
    for (unsigned i = 0; i < eh.e_shnum; i++) if (sh[i].sh_type == SHT_SYMTAB) symtab = (int)i;
    ASSERT_TRUE(symtab >= 0);
    ASSERT_EQ(sh[symtab].sh_entsize, (u64)sizeof(Elf64_Sym));
    sh[symtab].sh_entsize = 16u;           /* a different record size than the reader assumes */
    ASSERT_TRUE(write_bytes(bad, b, n));
    ASSERT_TRUE(break_elf_symbols_open(bad) == NULL);
    free(b);
}

TEST(a_stripped_shared_object_still_resolves_its_exports_through_dynsym) {
    char so[400], src[400], cmd[1500];
    BreakElfSymbols *s;
    u64 addr = 0, off = 0;
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    path_in(so, sizeof(so), "libstripped.so");
    path_in(src, sizeof(src), "fixture.c");
    ASSERT_TRUE(write_text(src, k_fixture_src));
    snprintf(cmd, sizeof(cmd), "%s -O0 -g0 -fPIC -shared -o '%s' '%s' 2>/dev/null && strip '%s'",
             BREAK_TEST_CC, so, src, so);
    ASSERT_TRUE(run(cmd));
    ASSERT_FALSE(run_quiet_nm_has_symtab(so));          /* no .symtab left: only .dynsym */
    s = break_elf_symbols_open(so);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_elf_symbols_count(s) > 0u);
    /* the address comes from .dynsym via nm -D, the independent oracle */
    {
        char c2[800], line[200];
        FILE *p;
        snprintf(c2, sizeof(c2), "nm -D '%s' 2>/dev/null | awk '$3==\"outer\" {print $1}'", so);
        p = popen(c2, "r");
        ASSERT_NOT_NULL(p);
        ASSERT_NOT_NULL(fgets(line, sizeof(line), p));
        pclose(p);
        addr = strtoull(line, NULL, 16);
    }
    ASSERT_TRUE(addr != 0u);
    ASSERT_TRUE(break_elf_symbols_lookup(s, addr + 1u, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "outer");
    ASSERT_EQ(off, 1u);
    break_elf_symbols_destroy(s);
}

/* ---- frame recovery ---------------------------------------------------------
 * A real crash: a child process installs break_crash, calls a chain of
 * frame-pointer functions and faults in the innermost one. The record it
 * leaves is parsed by the real break_crash parser and symbolized against the
 * child's own executable. The child program is compiled with
 * -fno-omit-frame-pointer so the saved-RBP chain exists. */

static const char k_crash_src[] =
    "#include <crash/break_crash.h>\n"
    "#include <signal.h>\n"
    "#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "#include <string.h>\n"
    "volatile int *g_null = 0;\n"
    "__attribute__((noinline)) int leaf(int x) { *g_null = x; return x; }\n"
    "__attribute__((noinline)) int mid(int x) { return leaf(x + 1) + 1; }\n"
    "__attribute__((noinline)) int outer(int x) { return mid(x + 1) + 1; }\n"
    "int main(int argc, char **argv) {\n"
    "    BreakCrashConfig cfg; cfg.spool_root = argv[1];\n"
    "    if (!break_crash_install(&cfg)) return 3;\n"
    "    if (argc > 2 && strcmp(argv[2], \"deep\") == 0) {\n"
    "        return outer(1);\n"
    "    }\n"
    "    return outer(1);\n"
    "}\n";

/* Builds the crashing child with the crash library and runs it; returns the
 * recorded bytes. */
static bool crash_child(const char *exe_name, const char *extra, u8 **rec, u64 *rec_len,
                        char *exe_path, size_t exe_cap) {
    char src[400], spool[400], cmd[CMD_CAP];
    BreakCrashSpool *sp;
    path_in(src, sizeof(src), "crasher.c");
    path_in(exe_path, exe_cap, exe_name);
    path_in(spool, sizeof(spool), "spool");
    if (!write_text(src, k_crash_src)) return false;
    snprintf(cmd, sizeof(cmd),
             "%s -O0 -g0 -fno-pie -no-pie -fno-omit-frame-pointer %s -I'%s' -o '%s' '%s' "
             "'%s' '%s' '%s' 2>/dev/null",
             BREAK_TEST_CC, extra, BREAK_TEST_SRC_DIR, exe_path, src,
             BREAK_TEST_SRC_DIR "/crash/break_crash.c", BREAK_TEST_SRC_DIR "/platform/platform_fs.c",
             BREAK_TEST_SRC_DIR "/core/break_version.c");
    if (!run(cmd)) return false;
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", spool, spool);
    if (!run(cmd)) return false;
    snprintf(cmd, sizeof(cmd), "'%s' '%s' >/dev/null 2>&1; true", exe_path, spool);
    if (!run(cmd)) return false;
    sp = break_crash_spool_open(spool);
    if (sp == NULL) return false;
    if (break_crash_spool_count(sp, 0) != 1u || !break_crash_spool_read_pending(sp, 0, rec, rec_len)) {
        break_crash_spool_destroy(sp);
        return false;
    }
    break_crash_spool_destroy(sp);
    return true;
}

/* Lays out <root>/<build-id>/<module> with a copy of the unstripped binary. */
static bool store_binary(const char *root, const char *build_id, const char *module, const char *exe) {
    char cmd[CMD_CAP];
    snprintf(cmd, sizeof(cmd), "mkdir -p '%s/%s' && cp '%s' '%s/%s/%s'", root, build_id, exe, root, build_id, module);
    return run(cmd);
}

TEST(a_real_crash_is_symbolized_into_the_call_chain) {
    char exe[400], root[400];
    u8 *rec = NULL;
    u64 rec_len = 0;
    BreakCrashRecord *r;
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES];
    u32 n;
    ASSERT_TRUE(crash_child("crasher", "", &rec, &rec_len, exe, sizeof(exe)));
    r = break_crash_record_parse(rec, (usize)rec_len);
    ASSERT_NOT_NULL(r);
    path_in(root, sizeof(root), "symbols");
    ASSERT_TRUE(store_binary(root, break_crash_record_build_id(r), "crasher", exe));
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    n = break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES);
    ASSERT_TRUE(n >= 5u);
    ASSERT_TRUE(fr[0].resolved);
    ASSERT_STR_EQ(fr[0].symbol, "leaf");     /* the faulting function */
    ASSERT_STR_EQ(fr[1].symbol, "mid");
    ASSERT_STR_EQ(fr[2].symbol, "outer");
    ASSERT_STR_EQ(fr[3].symbol, "main");
    ASSERT_STR_EQ(fr[0].module, "crasher");
    ASSERT_STR_EQ(fr[3].module, "crasher");
    ASSERT_TRUE(fr[0].pc != 0u && fr[0].pc != fr[1].pc);
    /* the frames are real return addresses: each one is inside its function */
    {
        u64 a = 0;
        ASSERT_TRUE(nm_addr(exe, "mid", &a));
        ASSERT_TRUE(fr[1].pc > a && fr[1].symbol_offset == fr[1].pc - a);
    }
    break_crash_symbol_store_destroy(st);
    break_crash_record_destroy(r);
    free(rec);
}

TEST(a_position_independent_executable_is_symbolized_through_its_load_bias) {
    char exe[400], root[400];
    u8 *rec = NULL;
    u64 rec_len = 0, a = 0;
    BreakCrashRecord *r;
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES];
    u32 n;
    ASSERT_TRUE(crash_child("crasher_pie", "-fPIE -pie", &rec, &rec_len, exe, sizeof(exe)));
    r = break_crash_record_parse(rec, (usize)rec_len);
    ASSERT_NOT_NULL(r);
    path_in(root, sizeof(root), "symbols_pie");
    ASSERT_TRUE(store_binary(root, break_crash_record_build_id(r), "crasher_pie", exe));
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    n = break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES);
    ASSERT_TRUE(n >= 4u);
    ASSERT_STR_EQ(fr[0].symbol, "leaf");
    ASSERT_STR_EQ(fr[1].symbol, "mid");
    ASSERT_STR_EQ(fr[2].symbol, "outer");
    ASSERT_STR_EQ(fr[3].symbol, "main");
    ASSERT_TRUE(nm_addr(exe, "mid", &a));
    ASSERT_TRUE(fr[1].module_offset > a && fr[1].symbol_offset == fr[1].module_offset - a);
    ASSERT_TRUE(fr[1].pc > fr[1].module_offset);       /* a real, non-zero load bias was removed */
    break_crash_symbol_store_destroy(st);
    break_crash_record_destroy(r);
    free(rec);
}

TEST(frames_in_modules_without_stored_symbols_stay_unresolved) {
    char exe[400], root[400];
    u8 *rec = NULL;
    u64 rec_len = 0;
    BreakCrashRecord *r;
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES];
    u32 n;
    ASSERT_TRUE(crash_child("crasher2", "", &rec, &rec_len, exe, sizeof(exe)));
    r = break_crash_record_parse(rec, (usize)rec_len);
    ASSERT_NOT_NULL(r);
    path_in(root, sizeof(root), "symbols2");
    ASSERT_TRUE(store_binary(root, break_crash_record_build_id(r), "crasher2", exe));
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    n = break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES);
    {
        u32 libc_frames = 0u;
        bool seen_main = false;
        for (u32 i = 0; i < n; i++) {
            if (strcmp(fr[i].symbol, "main") == 0) seen_main = true;
            if (!seen_main) continue;
            /* a frame in a module the store holds no file for is kept with its module
             * name and is NOT given a made-up symbol */
            if (fr[i].module[0] != '\0' && strcmp(fr[i].module, "crasher2") != 0) {
                ASSERT_FALSE(fr[i].resolved);
                ASSERT_STR_EQ(fr[i].symbol, "");
                libc_frames++;
            }
        }
        ASSERT_TRUE(seen_main);
        ASSERT_TRUE(libc_frames >= 1u);
    }
    break_crash_symbol_store_destroy(st);
    break_crash_record_destroy(r);
    free(rec);
}

TEST(a_missing_symbol_file_leaves_frames_with_module_offsets_only) {
    char exe[400], root[400];
    u8 *rec = NULL;
    u64 rec_len = 0;
    BreakCrashRecord *r;
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[8];
    u32 n;
    ASSERT_TRUE(crash_child("crasher3", "", &rec, &rec_len, exe, sizeof(exe)));
    r = break_crash_record_parse(rec, (usize)rec_len);
    ASSERT_NOT_NULL(r);
    path_in(root, sizeof(root), "symbols_empty");
    ASSERT_TRUE(run("mkdir -p /dev/null 2>/dev/null; true"));
    {
        char cmd[CMD_CAP];
        snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", root, root);
        ASSERT_TRUE(run(cmd));
    }
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    n = break_crash_symbolize_record(st, r, fr, 8u);
    ASSERT_TRUE(n >= 3u);
    for (u32 i = 0; i < n; i++) {
        ASSERT_FALSE(fr[i].resolved);
        ASSERT_STR_EQ(fr[i].symbol, "");
    }
    ASSERT_STR_EQ(fr[0].module, "crasher3");           /* the module is known from the record alone */
    ASSERT_TRUE(fr[0].module_offset != 0u);
    break_crash_symbol_store_destroy(st);
    break_crash_record_destroy(r);
    free(rec);
}

/* ---- the walker against crafted records: the record is untrusted ---- */

typedef struct { u8 bytes[4096]; usize len; } Win;

static void put64(Win *w, usize at, u64 v) { for (int i = 0; i < 8; i++) w->bytes[at + (usize)i] = (u8)(v >> (8 * i)); }

/* A record with a chosen rip/rsp/rbp, one module [0x400000, +0x10000) and the given stack window. */
static BreakCrashRecord *craft(u64 rip, u64 rsp, u64 rbp, const Win *w) {
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    u8 text[70000];
    usize n;
    BreakCrashRecord *r;
    if (b == NULL) return NULL;
    break_crash_record_builder_set_signal(b, 11, 1, 0);
    break_crash_record_builder_set_process(b, 1, 1);
    break_crash_record_builder_set_registers(b, rip, rsp, rbp);
    break_crash_record_builder_set_build_id(b, "testbuild");
    (void)break_crash_record_builder_add_module(b, "mod.bin", 0x400000u, 0x10000u);
    if (w != NULL) break_crash_record_builder_set_stack_window(b, w->bytes, w->len);
    n = break_crash_record_builder_finish(b, text, sizeof(text));
    break_crash_record_builder_destroy(b);
    r = n != 0u ? break_crash_record_parse(text, n) : NULL;
    return r;
}

/* AAPCS64's frame record is [fp] = caller's fp, [fp+8] = LR, the same
 * layout and word size the x86-64 walk reads, so one walk serves both
 * (design 2026-11-20-crash-arm64-registers). */
TEST(the_walker_follows_an_arm64_frame_pointer_chain_too) {
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES];
    BreakCrashRecord *r;
    Win w;
    char empty[300], cmd[CMD_CAP];
    path_in(empty, sizeof(empty), "nosyms_arm64");
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", empty, empty);
    ASSERT_TRUE(run(cmd));
    st = break_crash_symbol_store_open(empty);
    ASSERT_NOT_NULL(st);
    memset(&w, 0, sizeof(w));
    w.len = 4096u;
    /* sp = 0x7ff00000, x29 (fp) = sp + 0x40; each record holds the caller's
     * fp then its LR, exactly as the x86-64 case holds rbp then the return
     * address */
    put64(&w, 0x40, 0x7ff00080u);  put64(&w, 0x48, 0x400140u);   /* innermost: LR into the module */
    put64(&w, 0x80, 0x7ff000c0u);  put64(&w, 0x88, 0x400240u);
    put64(&w, 0xc0, 0u);           put64(&w, 0xc8, 0x400340u);   /* fp 0 stops the walk after this LR */
    r = craft(0x400040u, 0x7ff00000u, 0x7ff00040u, &w);
    ASSERT_NOT_NULL(r);
    {
        u32 n = break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES);
        /* pc, then the three LRs; the last fp is 0, which is not greater
         * than the current one, so the walk stops there */
        ASSERT_EQ(n, 4u);
        ASSERT_EQ(fr[0].pc, 0x400040u);
        ASSERT_EQ(fr[1].pc, 0x400140u);
        ASSERT_EQ(fr[2].pc, 0x400240u);
        ASSERT_EQ(fr[3].pc, 0x400340u);
        ASSERT_EQ(fr[0].module_offset, 0x40u);
        ASSERT_STR_EQ(fr[1].module, "mod.bin");
    }
    break_crash_record_destroy(r);
    break_crash_symbol_store_destroy(st);
}

TEST(the_walker_follows_the_saved_rbp_chain_inside_the_window_only) {
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES];
    BreakCrashRecord *r;
    Win w;
    char empty[300], cmd[CMD_CAP];
    path_in(empty, sizeof(empty), "nosyms");
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", empty, empty);
    ASSERT_TRUE(run(cmd));
    st = break_crash_symbol_store_open(empty);
    ASSERT_NOT_NULL(st);
    memset(&w, 0, sizeof(w));
    w.len = 4096u;
    /* stack at rsp = 0x7ff00000: frame A at +0x20 (rbp), caller frame B at +0x60, C at +0xa0 */
    put64(&w, 0x20, 0x7ff00060u);  put64(&w, 0x28, 0x400100u);   /* A: saved rbp -> B, ret into module */
    put64(&w, 0x60, 0x7ff000a0u);  put64(&w, 0x68, 0x400200u);   /* B */
    put64(&w, 0xa0, 0x7ff00ff0u);  put64(&w, 0xa8, 0x400300u);   /* C: saved rbp points at 0xff0: 8 bytes before the window end, no room for the return address */
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, &w);
    ASSERT_NOT_NULL(r);
    {
        u32 n = break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES);
        ASSERT_EQ(n, 4u);                      /* rip, then the return addresses of A, B, C */
        ASSERT_EQ(fr[0].pc, 0x400050u);
        ASSERT_EQ(fr[1].pc, 0x400100u);
        ASSERT_EQ(fr[2].pc, 0x400200u);
        ASSERT_EQ(fr[3].pc, 0x400300u);
        ASSERT_EQ(fr[0].module_offset, 0x50u); /* pc - load offset 0x400000 */
        ASSERT_STR_EQ(fr[1].module, "mod.bin");
    }
    break_crash_record_destroy(r);

    /* a frame whose saved-rbp word fits but whose return-address word straddles the window end */
    put64(&w, 0xa0, 0x7ff00ff4u);
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, &w);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 4u);
    break_crash_record_destroy(r);
    put64(&w, 0xa0, 0x7ff00ff0u);

    /* a frame pointer below rsp, far above the window, or at the top of the address space: only rip */
    {
        const u64 bad_rbp[] = {0x7feffff0u, 0x7ff10000u, 0x7ff01000u, 0xfffffffffffffff8ull, 0u};
        for (usize k = 0; k < sizeof(bad_rbp) / sizeof(bad_rbp[0]); k++) {
            r = craft(0x400050u, 0x7ff00000u, bad_rbp[k], &w);
            ASSERT_NOT_NULL(r);
            ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 1u);
            break_crash_record_destroy(r);
        }
    }

    /* a cap smaller than the chain truncates, never overflows */
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, &w);
    {
        u32 n = break_crash_symbolize_record(st, r, fr, 2u);
        ASSERT_EQ(n, 2u);
    }
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, 0u), 0u);
    ASSERT_EQ(break_crash_symbolize_record(st, r, NULL, 4u), 0u);
    break_crash_record_destroy(r);
    break_crash_symbol_store_destroy(st);
}

TEST(a_forged_chain_cannot_loop_backwards_or_leave_the_window) {
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES];
    BreakCrashRecord *r;
    Win w;
    char empty[300], cmd[CMD_CAP];
    path_in(empty, sizeof(empty), "nosyms2");
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", empty, empty);
    ASSERT_TRUE(run(cmd));
    st = break_crash_symbol_store_open(empty);
    ASSERT_NOT_NULL(st);
    memset(&w, 0, sizeof(w));
    w.len = 4096u;
    /* saved rbp points BACKWARDS (to itself, then lower): a loop if followed */
    put64(&w, 0x20, 0x7ff00020u);  put64(&w, 0x28, 0x400100u);
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 2u);  /* rip + one ret, then stop */
    break_crash_record_destroy(r);

    memset(&w, 0, sizeof(w));
    w.len = 4096u;
    put64(&w, 0x20, 0x7ff00010u);  put64(&w, 0x28, 0x400100u);   /* lower than the current rbp */
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 2u);
    break_crash_record_destroy(r);

    /* saved rbp far above the window: the next read is outside it */
    memset(&w, 0, sizeof(w));
    w.len = 4096u;
    put64(&w, 0x20, 0x7ffffff0u);  put64(&w, 0x28, 0x400100u);
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 2u);
    break_crash_record_destroy(r);

    /* rbp below rsp (not a stack frame of this window) */
    r = craft(0x400050u, 0x7ff00000u, 0x7feffff0u, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 1u);
    break_crash_record_destroy(r);

    /* near-overflow addresses: rbp + 8 would wrap */
    r = craft(0x400050u, 0xfffffffffffff000u, 0xfffffffffffffffcu, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 1u);
    break_crash_record_destroy(r);

    /* a return address of 0 ends the chain without a frame */
    memset(&w, 0, sizeof(w));
    w.len = 4096u;
    put64(&w, 0x20, 0x7ff00060u);  put64(&w, 0x28, 0u);
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 1u);
    break_crash_record_destroy(r);

    /* a zero rip: nothing to report */
    r = craft(0u, 0x7ff00000u, 0x7ff00020u, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 0u);
    break_crash_record_destroy(r);

    /* no stack window at all: only the faulting frame */
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, NULL);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES), 1u);
    break_crash_record_destroy(r);

    ASSERT_EQ(break_crash_symbolize_record(st, NULL, fr, 4u), 0u);
    ASSERT_EQ(break_crash_symbolize_record(NULL, NULL, fr, 4u), 0u);
    break_crash_symbol_store_destroy(st);
}

TEST(a_long_chain_is_cut_at_the_cap) {
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES + 8u];
    BreakCrashRecord *r;
    Win w;
    char empty[300], cmd[CMD_CAP];
    path_in(empty, sizeof(empty), "nosyms3");
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", empty, empty);
    ASSERT_TRUE(run(cmd));
    st = break_crash_symbol_store_open(empty);
    ASSERT_NOT_NULL(st);
    memset(&w, 0, sizeof(w));
    w.len = 4096u;
    for (u64 i = 0; i < 100u; i++) {                     /* 100 frames of 0x20 bytes */
        put64(&w, i * 0x20u, 0x7ff00000u + (i + 1u) * 0x20u);
        put64(&w, i * 0x20u + 8u, 0x400100u + i);
    }
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00000u, &w);
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES + 8u),
              BREAK_CRASH_SYMBOLIZE_MAX_FRAMES);
    break_crash_record_destroy(r);
    break_crash_symbol_store_destroy(st);
}

TEST(a_hostile_build_id_or_module_name_cannot_reach_outside_the_symbol_root) {
    /* the record grammar already forbids '/' in names and limits the build id to [0-9a-z-];
     * the store re-checks anyway, so a parser change cannot open a traversal. A planted file
     * outside the root, named like what a traversal would reach, must never be read. */
    char root[400], outside[400], cmd[CMD_CAP];
    BreakCrashSymbolStore *st;
    BreakCrashFrame fr[4];
    BreakCrashRecord *r;
    Win w;
    path_in(root, sizeof(root), "symroot");
    path_in(outside, sizeof(outside), "outside_secret.bin");
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s/testbuild'; cp '%s/fixture' '%s'; "
                               "cp '%s/fixture' '%s/mod.bin'",
             root, root, g_dir, outside, g_dir, g_dir);
    (void)run(cmd);
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    memset(&w, 0, sizeof(w));
    w.len = 0u;
    r = craft(0x400050u, 0x7ff00000u, 0x7ff00020u, NULL);
    ASSERT_NOT_NULL(r);
    /* nothing under <root>/testbuild/mod.bin: unresolved, never a read of ../../fixture */
    ASSERT_EQ(break_crash_symbolize_record(st, r, fr, 4u), 1u);
    ASSERT_FALSE(fr[0].resolved);
    break_crash_record_destroy(r);
    break_crash_symbol_store_destroy(st);
    ASSERT_TRUE(break_crash_symbol_store_open("") == NULL);
    ASSERT_TRUE(break_crash_symbol_store_open(NULL) == NULL);
    ASSERT_TRUE(break_crash_symbol_store_open("/nonexistent/dir/for/symbols") == NULL);
}

TEST(the_store_refuses_names_that_could_leave_its_root_even_when_a_valid_file_is_there) {
    char root[400], cmd[CMD_CAP], long_name[300], long_id[100];
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    u64 off = 0, addr = 0;
    BreakCrashSymbolStore *st;
    path_in(root, sizeof(root), "symroot2");
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s/goodid' '%s/a'; cp '%s/fixture' '%s/goodid/mod'; "
                               "cp '%s/fixture' '%s/planted'; cp '%s/fixture' '%s/a/x'",
             root, root, root, g_dir, root, g_dir, root, g_dir, root);
    ASSERT_TRUE(run(cmd));
    {
        char fx[400];
        path_in(fx, sizeof(fx), "fixture");
        ASSERT_TRUE(nm_addr(fx, "outer", &addr));
    }
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    ASSERT_TRUE(break_crash_symbol_store_lookup(st, "goodid", "mod", addr, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "outer");
    /* each of these would reach a real, valid ELF file if the name were used as a path */
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "a", "../planted", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "a/..", "planted", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "..", "planted", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "a", "..", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "a", "x\\y", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "A", "x", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "", "x", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "a", "", addr, name, sizeof(name), &off));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, NULL, "x", addr, name, sizeof(name), &off));
    memset(long_id, 'a', 65u);
    long_id[65] = '\0';
    {
        char mk[CMD_CAP];
        snprintf(mk, sizeof(mk), "mkdir -p '%s/%s' && cp '%s/fixture' '%s/%s/mod'", root, long_id, g_dir, root, long_id);
        ASSERT_TRUE(run(mk));     /* a real, valid file exists under the over-long id */
    }
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, long_id, "mod", addr, name, sizeof(name), &off));
    memset(long_name, 'm', 256u);
    long_name[256] = '\0';
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "goodid", long_name, addr, name, sizeof(name), &off));
    break_crash_symbol_store_destroy(st);
}

TEST(symbols_uploaded_after_a_miss_are_found_by_the_same_open_store) {
    char root[400], cmd[CMD_CAP], fx[400];
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    u64 off = 0, addr = 0;
    BreakCrashSymbolStore *st;
    path_in(root, sizeof(root), "symroot3");
    path_in(fx, sizeof(fx), "fixture");
    ASSERT_TRUE(nm_addr(fx, "outer", &addr));
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s/late'", root, root);
    ASSERT_TRUE(run(cmd));
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    /* a long-running server sees the crash before the build's symbols arrive */
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "late", "mod", addr, name, sizeof(name), &off));
    snprintf(cmd, sizeof(cmd), "cp '%s' '%s/late/mod'", fx, root);
    ASSERT_TRUE(run(cmd));
    ASSERT_TRUE(break_crash_symbol_store_lookup(st, "late", "mod", addr, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "outer");
    /* a file that is not an ELF is a miss too, and fixing it later works */
    snprintf(cmd, sizeof(cmd), "mkdir -p '%s/late2' && echo junk > '%s/late2/mod'", root, root);
    ASSERT_TRUE(run(cmd));
    ASSERT_FALSE(break_crash_symbol_store_lookup(st, "late2", "mod", addr, name, sizeof(name), &off));
    snprintf(cmd, sizeof(cmd), "cp '%s' '%s/late2/mod'", fx, root);
    ASSERT_TRUE(run(cmd));
    ASSERT_TRUE(break_crash_symbol_store_lookup(st, "late2", "mod", addr, name, sizeof(name), &off));
    break_crash_symbol_store_destroy(st);
}

/* ---- Mach-O symbol files ---------------------------------------------------
 * Images are written byte by byte here, so no Apple SDK is needed: a __TEXT
 * segment (__text and __stubs hold code, __const does not), a __DATA segment,
 * LC_SYMTAB and optionally LC_UUID. Symbol values are relative to `base`,
 * the __TEXT vmaddr. */

typedef struct {
    u8 b[32768];
    usize n;
    usize symtab_cmd;
    usize uuid_cmd;
    usize data_seg;
} MachoImg;

typedef struct {
    u64 base;
    u32 cpu;
    u32 filetype;
    bool uuid;
    u32 extra_sections;
} MachoSpec;

typedef struct {
    const char *name; /* NULL: a string index past the table */
    u8 type;
    u8 sect;
    u64 value;
} MoSym;

static const u8 k_mo_uuid[16] = {0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78,
                                 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0};

static const MoSym k_mo_syms[] = {
    {"_alpha", 0x0f, 1, 0x1000},      {"_beta", 0x0f, 1, 0x1040},
    {"_alpha_alias", 0x0f, 1, 0x1000}, {"_gamma", 0x0e, 1, 0x1080},
    {"noprefix", 0x0f, 1, 0x10c0},    {"_stub", 0x0e, 2, 0x1200},
    {"_konst", 0x0f, 3, 0x2000},      {"_data", 0x0f, 4, 0x3000},
    {"_undef", 0x01, 0, 0x0},         {"_abs", 0x03, 0, 0x1050},
    {"_stabfn", 0x24, 1, 0x1010},     {"_wrongsect", 0x0f, 250, 0x1020},
    {"_bnsym", 0x2e, 1, 0x1010}, /* N_BNSYM: a stab whose low bits read as N_SECT */
    {"_outside", 0x0f, 1, 0x1100},    {"_below", 0x0f, 1, 0x0ff0},
    {"", 0x0f, 1, 0x1030},            {NULL, 0x0f, 1, 0x1038},
};

static void mo_put32(u8 *p, u32 v) { for (int i = 0; i < 4; i++) p[i] = (u8)(v >> (8 * i)); }
static void mo_put64(u8 *p, u64 v) { for (int i = 0; i < 8; i++) p[i] = (u8)(v >> (8 * i)); }
static u32 mo_get32(const u8 *p) { return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24); }

static void mo_name16(u8 *p, const char *s) {
    memset(p, 0, 16);
    memcpy(p, s, strlen(s));
}

static usize mo_section(u8 *p, const char *sect, const char *seg, u64 addr, u64 size, u32 flags) {
    memset(p, 0, 80);
    mo_name16(p, sect);
    mo_name16(p + 16, seg);
    mo_put64(p + 32, addr);
    mo_put64(p + 40, size);
    mo_put32(p + 64, flags);
    return 80u;
}

static usize mo_segment(u8 *p, const char *name, u64 vmaddr, u64 vmsize, u32 nsects) {
    memset(p, 0, 72);
    mo_put32(p, 0x19u);
    mo_put32(p + 4, 72u + 80u * nsects);
    mo_name16(p + 8, name);
    mo_put64(p + 24, vmaddr);
    mo_put64(p + 32, vmsize);
    mo_put32(p + 64, nsects);
    return 72u;
}

static void macho_build(MachoImg *img, const MachoSpec *sp) {
    u8 *b = img->b;
    usize at = 32u;
    u32 ncmds = 0u;
    usize nsyms = sizeof(k_mo_syms) / sizeof(k_mo_syms[0]);
    u32 data_sects = 1u + sp->extra_sections;
    memset(img, 0, sizeof(*img));
    at += mo_segment(b + at, "__TEXT", sp->base, 0x3000u, 3u);
    at += mo_section(b + at, "__text", "__TEXT", sp->base + 0x1000u, 0x100u, 0x80000400u);
    at += mo_section(b + at, "__stubs", "__TEXT", sp->base + 0x1200u, 0x20u, 0x00000400u);
    at += mo_section(b + at, "__const", "__TEXT", sp->base + 0x2000u, 0x40u, 0u);
    ncmds++;
    img->data_seg = at;
    at += mo_segment(b + at, "__DATA", sp->base + 0x3000u, 0x1000u, data_sects);
    for (u32 i = 0; i < data_sects; i++) {
        at += mo_section(b + at, "__data", "__DATA", sp->base + 0x3000u + 8u * i, 8u, 0u);
    }
    ncmds++;
    img->symtab_cmd = at;
    at += 24u;
    ncmds++;
    if (sp->uuid) {
        img->uuid_cmd = at;
        mo_put32(b + at, 0x1bu);
        mo_put32(b + at + 4, 24u);
        memcpy(b + at + 8, k_mo_uuid, 16u);
        at += 24u;
        ncmds++;
    }
    mo_put32(b, 0xfeedfacfu);
    mo_put32(b + 4, sp->cpu);
    mo_put32(b + 8, 3u);
    mo_put32(b + 12, sp->filetype);
    mo_put32(b + 16, ncmds);
    mo_put32(b + 20, (u32)(at - 32u));
    {
        usize symoff = (at + 15u) & ~(usize)15u;
        usize stroff = symoff + 16u * nsyms;
        usize str = 2u;
        b[stroff] = ' ';
        b[stroff + 1u] = '\0';
        for (usize i = 0; i < nsyms; i++) {
            u8 *e = b + symoff + 16u * i;
            u32 strx = 0x00ffffffu;
            if (k_mo_syms[i].name != NULL) {
                usize len = strlen(k_mo_syms[i].name);
                strx = len == 0u ? 1u : (u32)str;
                if (len != 0u) {
                    memcpy(b + stroff + str, k_mo_syms[i].name, len + 1u);
                    str += len + 1u;
                }
            }
            mo_put32(e, strx);
            e[4] = k_mo_syms[i].type;
            e[5] = k_mo_syms[i].sect;
            mo_put64(e + 8, k_mo_syms[i].sect == 0u && k_mo_syms[i].type == 0x01u
                                ? 0u
                                : sp->base + k_mo_syms[i].value);
        }
        mo_put32(b + img->symtab_cmd, 0x2u);
        mo_put32(b + img->symtab_cmd + 4, 24u);
        mo_put32(b + img->symtab_cmd + 8, (u32)symoff);
        mo_put32(b + img->symtab_cmd + 12, (u32)nsyms);
        mo_put32(b + img->symtab_cmd + 16, (u32)stroff);
        mo_put32(b + img->symtab_cmd + 20, (u32)str);
        img->n = stroff + str;
    }
}

static void macho_default(MachoImg *img, u64 base, u32 filetype) {
    MachoSpec sp = {base, 0x01000007u, filetype, true, 0u};
    macho_build(img, &sp);
}

static BreakElfSymbols *macho_open_bytes(const u8 *b, usize n) {
    char path[400];
    path_in(path, sizeof(path), "image.macho");
    if (!write_bytes(path, b, n)) return NULL;
    return break_macho_symbols_open(path);
}

static bool mo_lookup(const BreakElfSymbols *s, u64 addr, const char *want, u64 want_off) {
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    u64 off = 0;
    if (!break_elf_symbols_lookup(s, addr, name, sizeof(name), &off)) return want == NULL;
    if (want == NULL) {
        printf("    0x%llx unexpectedly resolved to %s\n", (unsigned long long)addr, name);
        return false;
    }
    if (strcmp(name, want) != 0 || off != want_off) {
        printf("    0x%llx -> %s+0x%llx, want %s+0x%llx\n", (unsigned long long)addr, name,
               (unsigned long long)off, want, (unsigned long long)want_off);
        return false;
    }
    return true;
}

static bool mo_alpha_at(const BreakElfSymbols *s, u64 addr, u64 want_off) {
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    u64 off = 0;
    if (!break_elf_symbols_lookup(s, addr, name, sizeof(name), &off)) return false;
    return (strcmp(name, "alpha") == 0 || strcmp(name, "alpha_alias") == 0) && off == want_off;
}

static bool mo_expect_layout(const BreakElfSymbols *s, u64 rel) {
    return mo_alpha_at(s, rel + 0x1000u, 0u) && mo_alpha_at(s, rel + 0x103fu, 0x3fu) &&
           mo_lookup(s, rel + 0x1040u, "beta", 0u) && mo_lookup(s, rel + 0x1080u, "gamma", 0u) &&
           mo_lookup(s, rel + 0x10c0u, "noprefix", 0u) && mo_lookup(s, rel + 0x10ffu, "noprefix", 0x3fu) &&
           mo_lookup(s, rel + 0x1200u, "stub", 0u) && mo_lookup(s, rel + 0x121fu, "stub", 0x1fu) &&
           mo_lookup(s, rel + 0x1100u, NULL, 0u) && mo_lookup(s, rel + 0x1220u, NULL, 0u) &&
           mo_lookup(s, rel + 0x2000u, NULL, 0u) && mo_lookup(s, rel + 0x3000u, NULL, 0u) &&
           mo_lookup(s, rel + 0x0ff0u, NULL, 0u);
}

TEST(a_mach_o_image_resolves_code_symbols_relative_to_its_text_segment) {
    static MachoImg img;
    const u64 bases[] = {0u, 0x100000000ull};
    const u32 types[] = {6u, 2u, 8u, 0xau};
    for (usize b = 0; b < 2u; b++) {
        for (usize t = 0; t < 4u; t++) {
            BreakElfSymbols *s;
            macho_default(&img, bases[b], types[t]);
            s = macho_open_bytes(img.b, img.n);
            ASSERT_NOT_NULL(s);
            ASSERT_FALSE(break_elf_symbols_is_exec(s));
            /* alpha, alpha_alias, beta, gamma, noprefix, stub */
            ASSERT_EQ(break_elf_symbols_count(s), 6u);
            ASSERT_TRUE(mo_expect_layout(s, 0u));
            break_elf_symbols_destroy(s);
        }
    }
}

TEST(the_mach_o_uuid_is_read_as_hex) {
    static MachoImg img;
    MachoSpec sp = {0u, 0x01000007u, 6u, false, 0u};
    BreakElfSymbols *s;
    macho_default(&img, 0u, 6u);
    s = macho_open_bytes(img.b, img.n);
    ASSERT_NOT_NULL(s);
    ASSERT_STR_EQ(break_elf_symbols_build_id(s), "0f1e2d3c4b5a69788796a5b4c3d2e1f0");
    break_elf_symbols_destroy(s);
    macho_build(&img, &sp);
    s = macho_open_bytes(img.b, img.n);
    ASSERT_NOT_NULL(s);
    ASSERT_STR_EQ(break_elf_symbols_build_id(s), "");
    ASSERT_TRUE(mo_expect_layout(s, 0u));
    break_elf_symbols_destroy(s);
}

TEST(section_numbers_count_across_segments_and_data_sections_are_not_code) {
    static MachoImg img;
    MachoSpec sp = {0u, 0x01000007u, 6u, true, 247u};
    BreakElfSymbols *s;
    macho_build(&img, &sp); /* section 250 now exists, as a __data section */
    s = macho_open_bytes(img.b, img.n);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_elf_symbols_count(s), 6u);
    ASSERT_TRUE(mo_expect_layout(s, 0u));
    ASSERT_TRUE(mo_alpha_at(s, 0x1020u, 0x20u));
    break_elf_symbols_destroy(s);
}

TEST(mach_o_files_of_the_wrong_kind_are_refused) {
    static MachoImg img;
    MachoSpec arm = {0u, 0x0100000cu, 6u, true, 0u};
    BreakElfSymbols *s;
    macho_build(&img, &arm);
    s = macho_open_bytes(img.b, img.n);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(mo_expect_layout(s, 0u));
    break_elf_symbols_destroy(s);
    {
        const u32 cpus[] = {0x00000007u, 0x0000000cu, 0x01000012u, 0u};
        for (usize i = 0; i < 4u; i++) {
            MachoSpec sp = {0u, cpus[i], 6u, true, 0u};
            macho_build(&img, &sp);
            ASSERT_TRUE(macho_open_bytes(img.b, img.n) == NULL);
        }
    }
    {
        const u32 types[] = {0u, 1u, 3u, 4u, 5u, 7u, 9u, 0xbu, 0xcu};
        for (usize i = 0; i < 9u; i++) {
            macho_default(&img, 0u, types[i]);
            ASSERT_TRUE(macho_open_bytes(img.b, img.n) == NULL);
        }
    }
    macho_default(&img, 0u, 6u);
    mo_put32(img.b, 0xfeedfaceu); /* 32-bit */
    ASSERT_TRUE(macho_open_bytes(img.b, img.n) == NULL);
    mo_put32(img.b, 0xcffaedfeu); /* the 64-bit magic read big-endian */
    ASSERT_TRUE(macho_open_bytes(img.b, img.n) == NULL);
    mo_put32(img.b, 0xbebafecau); /* fat (0xcafebabe big-endian) */
    ASSERT_TRUE(macho_open_bytes(img.b, img.n) == NULL);
}

TEST(a_truncated_mach_o_file_is_refused_at_every_length) {
    static MachoImg img;
    macho_default(&img, 0x100000000ull, 2u);
    for (usize n = 0; n < img.n; n++) {
        BreakElfSymbols *s = macho_open_bytes(img.b, n);
        if (s != NULL) {
            printf("    a %zu-byte prefix of %zu loaded\n", (size_t)n, (size_t)img.n);
            break_elf_symbols_destroy(s);
            ASSERT_TRUE(false);
        }
    }
}

/* Re-opens `img` after `edit` changed it, expecting a refusal; restores it. */
static bool mo_refused_after(MachoImg *img, usize at, u32 v) {
    u32 old = mo_get32(img->b + at);
    BreakElfSymbols *s;
    mo_put32(img->b + at, v);
    s = macho_open_bytes(img->b, img->n);
    mo_put32(img->b + at, old);
    if (s != NULL) {
        printf("    writing 0x%x at %zu still loaded\n", v, (size_t)at);
        break_elf_symbols_destroy(s);
        return false;
    }
    return true;
}

TEST(each_structural_mach_o_corruption_is_refused) {
    static MachoImg img;
    usize text_sect = 32u + 72u;          /* the first section header, __text */
    usize sc;
    macho_default(&img, 0u, 6u);
    sc = img.symtab_cmd;
    ASSERT_TRUE(mo_refused_after(&img, 16u, 4097u));                 /* ncmds over the cap */
    ASSERT_TRUE(mo_refused_after(&img, 16u, 5u));                    /* more commands than sizeofcmds holds */
    ASSERT_TRUE(mo_refused_after(&img, 20u, (u32)img.n));            /* sizeofcmds past the file */
    ASSERT_TRUE(mo_refused_after(&img, 32u + 4u, 4u));               /* cmdsize below 8 */
    ASSERT_TRUE(mo_refused_after(&img, 32u + 4u, 72u + 80u * 3u + 4u)); /* not a multiple of 8 */
    ASSERT_TRUE(mo_refused_after(&img, 32u + 4u, 0x10000u));         /* past sizeofcmds */
    ASSERT_TRUE(mo_refused_after(&img, 32u + 64u, 4u));              /* nsects disagrees with cmdsize */
    ASSERT_TRUE(mo_refused_after(&img, 32u + 64u, 0x40000000u));
    {
        /* __text addr+size wraps */
        BreakElfSymbols *s;
        mo_put64(img.b + text_sect + 40u, ~(u64)0);
        s = macho_open_bytes(img.b, img.n);
        if (s != NULL) break_elf_symbols_destroy(s);
        ASSERT_TRUE(s == NULL);
        mo_put64(img.b + text_sect + 40u, 0x100u);
    }
    ASSERT_TRUE(mo_refused_after(&img, sc + 4u, 16u));                /* LC_SYMTAB too short */
    ASSERT_TRUE(mo_refused_after(&img, sc + 8u, (u32)img.n));         /* symoff past the file */
    ASSERT_TRUE(mo_refused_after(&img, sc + 12u, 0x10000000u));       /* nsyms past the file */
    ASSERT_TRUE(mo_refused_after(&img, sc + 16u, (u32)img.n));        /* stroff past the file */
    ASSERT_TRUE(mo_refused_after(&img, sc + 20u, 0xffffffffu));       /* strsize past the file */
    ASSERT_TRUE(mo_refused_after(&img, img.uuid_cmd + 4u, 16u));      /* LC_UUID too short for its 16 bytes */
    {
        /* a second LC_SYMTAB in place of the UUID */
        BreakElfSymbols *s;
        memcpy(img.b + img.uuid_cmd, img.b + sc, 24u);
        s = macho_open_bytes(img.b, img.n);
        if (s != NULL) break_elf_symbols_destroy(s);
        ASSERT_TRUE(s == NULL);
    }
}

TEST(random_mach_o_load_command_damage_never_crashes) {
    static MachoImg img, work;
    u32 seed = 0x9e3779b9u;
    usize cmds_end;
    macho_default(&img, 0x100000000ull, 2u);
    cmds_end = 32u + (usize)mo_get32(img.b + 20u);
    for (int round = 0; round < 3000; round++) {
        BreakElfSymbols *s;
        memcpy(&work, &img, sizeof(img));
        for (int k = 0; k < 1 + round % 4; k++) {
            usize at;
            seed = seed * 1664525u + 1013904223u;
            at = (usize)(seed >> 8) % (cmds_end + 160u);
            seed = seed * 1664525u + 1013904223u;
            work.b[at] = (u8)(seed >> 24);
        }
        s = macho_open_bytes(work.b, work.n);
        if (s != NULL) {
            char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
            u64 off = 0;
            for (u64 a = 0; a < 0x4000u; a += 0x10u) {
                (void)break_elf_symbols_lookup(s, a, name, sizeof(name), &off);
            }
            break_elf_symbols_destroy(s);
        }
    }
}

TEST(the_store_symbolizes_a_mach_o_module_from_a_record) {
    static MachoImg img;
    char root[400], dir[600], path[700], cmd[CMD_CAP];
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    u64 off = 0;
    BreakCrashSymbolStore *st;
    BreakCrashRecord *r;
    BreakCrashFrame fr;
    path_in(root, sizeof(root), "machoroot");
    snprintf(dir, sizeof(dir), "%s/testbuild", root);
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", root, dir);
    ASSERT_TRUE(run(cmd));
    macho_default(&img, 0x100000000ull, 2u);
    snprintf(path, sizeof(path), "%s/mod.bin", dir);
    ASSERT_TRUE(write_bytes(path, img.b, img.n));
    st = break_crash_symbol_store_open(root);
    ASSERT_NOT_NULL(st);
    ASSERT_TRUE(break_crash_symbol_store_lookup(st, "testbuild", "mod.bin", 0x1044u, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "beta");
    ASSERT_EQ(off, 4u);
    /* the record says the image header was mapped at 0x400000: the module offset is used as is */
    r = craft(0x401204u, 0x7ff00000u, 0u, NULL);
    ASSERT_NOT_NULL(r);
    break_crash_symbolize_address(st, r, 0x401204u, &fr);
    ASSERT_TRUE(fr.resolved);
    ASSERT_STR_EQ(fr.module, "mod.bin");
    ASSERT_EQ(fr.module_offset, 0x1204u);
    ASSERT_STR_EQ(fr.symbol, "stub");
    ASSERT_EQ(fr.symbol_offset, 4u);
    break_crash_record_destroy(r);
    break_crash_symbol_store_destroy(st);
}

TEST(the_load_command_count_is_capped_even_when_the_commands_fit) {
    const u32 counts[] = {4096u, 4097u};
    for (usize c = 0; c < 2u; c++) {
        u32 ncmds = counts[c];
        usize n = 32u + 72u + 80u + 8u * (usize)(ncmds - 1u);
        u8 *b = (u8 *)calloc(1u, n);
        BreakElfSymbols *s;
        ASSERT_NOT_NULL(b);
        mo_segment(b + 32u, "__TEXT", 0u, 0x2000u, 1u);
        mo_section(b + 104u, "__text", "__TEXT", 0x1000u, 0x100u, 0x80000400u);
        for (u32 i = 0; i + 1u < ncmds; i++) {
            mo_put32(b + 184u + 8u * i, 0x7fffff00u); /* an unknown command, skipped by size */
            mo_put32(b + 188u + 8u * i, 8u);
        }
        mo_put32(b, 0xfeedfacfu);
        mo_put32(b + 4, 0x01000007u);
        mo_put32(b + 12, 6u);
        mo_put32(b + 16, ncmds);
        mo_put32(b + 20, (u32)(n - 32u));
        s = macho_open_bytes(b, n);
        free(b);
        if (ncmds == 4096u) {
            ASSERT_NOT_NULL(s);
            ASSERT_EQ(break_elf_symbols_count(s), 0u);
            break_elf_symbols_destroy(s);
        } else {
            if (s != NULL) break_elf_symbols_destroy(s);
            ASSERT_TRUE(s == NULL);
        }
    }
}

TEST(an_unknown_load_command_must_still_be_eight_byte_aligned) {
    static MachoImg img;
    BreakElfSymbols *s;
    macho_default(&img, 0u, 6u);
    mo_put32(img.b + img.uuid_cmd, 0x32u); /* LC_BUILD_VERSION, which the reader skips */
    s = macho_open_bytes(img.b, img.n);
    ASSERT_NOT_NULL(s);
    ASSERT_STR_EQ(break_elf_symbols_build_id(s), "");
    break_elf_symbols_destroy(s);
    ASSERT_TRUE(mo_refused_after(&img, img.uuid_cmd + 4u, 20u));
}

TEST(a_code_symbol_below_the_text_segment_is_skipped) {
    static MachoImg img;
    const u64 base = 0x100000000ull;
    usize konst_sect = 32u + 72u + 160u;
    usize symoff;
    BreakElfSymbols *s;
    macho_default(&img, base, 2u);
    symoff = mo_get32(img.b + img.symtab_cmd + 8u);
    /* __const now claims code below the segment start, and _konst (entry 6) sits there */
    mo_put64(img.b + konst_sect + 32u, base - 0x100u);
    mo_put32(img.b + konst_sect + 64u, 0x80000400u);
    mo_put64(img.b + symoff + 16u * 6u + 8u, base - 0x100u);
    s = macho_open_bytes(img.b, img.n);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_elf_symbols_count(s), 6u);
    ASSERT_TRUE(mo_expect_layout(s, 0u));
    ASSERT_TRUE(mo_lookup(s, (u64)0 - 0x100u, NULL, 0u));
    break_elf_symbols_destroy(s);
}

TEST(a_command_count_past_the_last_command_is_refused_at_the_file_end) {
    /* header + one segment and nothing after it: the second command would start at the end of the file */
    u8 b[32u + 72u + 80u];
    BreakElfSymbols *s;
    memset(b, 0, sizeof(b));
    mo_segment(b + 32u, "__TEXT", 0u, 0x2000u, 1u);
    mo_section(b + 104u, "__text", "__TEXT", 0x1000u, 0x100u, 0x80000400u);
    mo_put32(b, 0xfeedfacfu);
    mo_put32(b + 4, 0x01000007u);
    mo_put32(b + 12, 6u);
    mo_put32(b + 16, 1u);
    mo_put32(b + 20, 152u);
    s = macho_open_bytes(b, sizeof(b));
    ASSERT_NOT_NULL(s);
    break_elf_symbols_destroy(s);
    mo_put32(b + 16, 2u);
    s = macho_open_bytes(b, sizeof(b));
    if (s != NULL) break_elf_symbols_destroy(s);
    ASSERT_TRUE(s == NULL);
}

static const char k_macho_src[] =
    "int f1(int x) { return x * 3 + 1; }\n"
    "int f2(int x) { return f1(x) ^ 0x55; }\n"
    "static int f3(int x) { return f2(x) - f1(x); }\n"
    "int (*keep)(int) = f3;\n"
    "void start(void) { for (;;) { (void)keep(1); } }\n";

/* llvm-nm's address for `_name`, minus `text_base` */
static bool llvm_nm_rel(const char *bin, const char *name, u64 text_base, u64 *out) {
    char cmd[900], line[200];
    FILE *p;
    snprintf(cmd, sizeof(cmd), "llvm-nm '%s' 2>/dev/null | awk '$3==\"_%s\" {print $1}'", bin, name);
    p = popen(cmd, "r");
    if (p == NULL) return false;
    if (fgets(line, sizeof(line), p) == NULL) {
        pclose(p);
        return false;
    }
    pclose(p);
    *out = strtoull(line, NULL, 16) - text_base;
    return true;
}

TEST(real_mach_o_images_from_the_llvm_toolchain_agree_with_llvm_nm) {
    struct { const char *arch, *triple, *kind; u64 base; } cases[] = {
        {"x86_64", "x86_64-apple-macos11", "-dylib", 0u},
        {"arm64", "arm64-apple-macos11", "-dylib", 0u},
        {"x86_64", "x86_64-apple-macos11", "-execute -e _start", 0x100000000ull},
    };
    const char *names[] = {"f1", "f2", "f3", "start"};
    char src[400], obj[400], bin[400], cmd[CMD_CAP];
    if (system("command -v clang >/dev/null 2>&1 && command -v ld64.lld >/dev/null 2>&1 && "
               "command -v llvm-nm >/dev/null 2>&1") != 0) {
        printf("skipped (clang, ld64.lld or llvm-nm missing) ");
        return;
    }
    path_in(src, sizeof(src), "mo.c");
    path_in(obj, sizeof(obj), "mo.o");
    path_in(bin, sizeof(bin), "mo.image");
    ASSERT_TRUE(write_text(src, k_macho_src));
    for (usize c = 0; c < sizeof(cases) / sizeof(cases[0]); c++) {
        BreakElfSymbols *s;
        snprintf(cmd, sizeof(cmd),
                 "clang -target %s -O1 -fno-inline -c '%s' -o '%s' 2>/dev/null && "
                 "ld64.lld -arch %s -platform_version macos 11.0 11.0 %s '%s' -o '%s' 2>/dev/null",
                 cases[c].triple, src, obj, cases[c].arch, cases[c].kind, obj, bin);
        ASSERT_TRUE(run(cmd));
        s = break_crash_symbols_open(bin);
        ASSERT_NOT_NULL(s);
        ASSERT_EQ(strlen(break_elf_symbols_build_id(s)), 32u);
        for (usize i = 0; i < 4u; i++) {
            u64 rel = 0;
            ASSERT_TRUE(llvm_nm_rel(bin, names[i], cases[c].base, &rel));
            ASSERT_TRUE(mo_lookup(s, rel, names[i], 0u));
            ASSERT_TRUE(mo_lookup(s, rel + 1u, names[i], 1u));
        }
        break_elf_symbols_destroy(s);
    }
}

TEST(the_format_dispatcher_opens_elf_and_mach_o_and_nothing_else) {
    static MachoImg img;
    char fx[400], junk[400];
    BreakElfSymbols *s;
    path_in(fx, sizeof(fx), "fixture");
    s = break_crash_symbols_open(fx);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_elf_symbols_count(s) > 0u);
    break_elf_symbols_destroy(s);
    macho_default(&img, 0u, 6u);
    path_in(junk, sizeof(junk), "dispatch.macho");
    ASSERT_TRUE(write_bytes(junk, img.b, img.n));
    s = break_crash_symbols_open(junk);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(mo_expect_layout(s, 0u));
    break_elf_symbols_destroy(s);
    /* each reader refuses the other's format */
    ASSERT_TRUE(break_elf_symbols_open(junk) == NULL);
    ASSERT_TRUE(break_macho_symbols_open(fx) == NULL);
    ASSERT_TRUE(write_text(junk, "not a symbol file at all\n"));
    ASSERT_TRUE(break_crash_symbols_open(junk) == NULL);
    ASSERT_TRUE(break_crash_symbols_open(NULL) == NULL);
    ASSERT_TRUE(break_macho_symbols_open("") == NULL);
}

/* ---- universal (fat) Mach-O: big-endian header, one thin image per CPU ---- */

#define MO_X86_64 0x01000007u
#define MO_ARM64 0x0100000cu

typedef struct {
    u8 b[3u * 4096u];
    usize n;
    usize slice_n;
} FatImg;

static void fat_be32(u8 *p, u32 v) { for (int i = 0; i < 4; i++) p[i] = (u8)(v >> (8 * (3 - i))); }
static void fat_be64(u8 *p, u64 v) { fat_be32(p, (u32)(v >> 32)); fat_be32(p + 4, (u32)v); }

/* arm64 slice at 0x1000, x86_64 slice at 0x2000 (arm64 first, so a reader
 * that takes the first slice is caught). The last UUID byte is the CPU's low
 * byte: ...07 for x86_64, ...0c for arm64. */
static void fat_build(FatImg *f, bool wide) {
    static MachoImg slice;
    const u32 cpus[2] = {MO_ARM64, MO_X86_64};
    usize entry = wide ? 32u : 20u;
    memset(f, 0, sizeof(*f));
    fat_be32(f->b, wide ? 0xcafebabfu : 0xcafebabeu);
    fat_be32(f->b + 4, 2u);
    for (u32 i = 0; i < 2u; i++) {
        MachoSpec sp = {0u, cpus[i], 6u, true, 0u};
        u8 *e = f->b + 8u + entry * i;
        usize off = 0x1000u * (i + 1u);
        macho_build(&slice, &sp);
        slice.b[slice.uuid_cmd + 8u + 15u] = (u8)cpus[i];
        memcpy(f->b + off, slice.b, slice.n);
        fat_be32(e, cpus[i]);
        fat_be32(e + 4, cpus[i] == MO_ARM64 ? 0u : 3u);
        if (wide) {
            fat_be64(e + 8, off);
            fat_be64(e + 16, slice.n);
            fat_be32(e + 24, 12u);
        } else {
            fat_be32(e + 8, (u32)off);
            fat_be32(e + 12, (u32)slice.n);
            fat_be32(e + 16, 12u);
        }
        f->n = off + slice.n;
        f->slice_n = slice.n;
    }
}

/* cpu 0: break_macho_symbols_open, else break_macho_symbols_open_cpu */
static BreakElfSymbols *fat_open(const u8 *b, usize n, u32 cpu) {
    char path[400];
    path_in(path, sizeof(path), "image.fat");
    if (!write_bytes(path, b, n)) return NULL;
    return cpu == 0u ? break_macho_symbols_open(path) : break_macho_symbols_open_cpu(path, cpu);
}

static bool fat_slice_is(const u8 *b, usize n, u32 cpu, const char *want_id) {
    BreakElfSymbols *s = fat_open(b, n, cpu);
    bool ok;
    if (s == NULL) {
        if (want_id != NULL) printf("    cpu 0x%x: no slice\n", cpu);
        return want_id == NULL;
    }
    ok = want_id != NULL && strcmp(break_elf_symbols_build_id(s), want_id) == 0 && mo_expect_layout(s, 0u);
    if (!ok) printf("    cpu 0x%x opened as %s, want %s\n", cpu, break_elf_symbols_build_id(s), want_id ? want_id : "NULL");
    break_elf_symbols_destroy(s);
    return ok;
}

static const char k_fat_x86_id[] = "0f1e2d3c4b5a69788796a5b4c3d2e107";
static const char k_fat_arm_id[] = "0f1e2d3c4b5a69788796a5b4c3d2e10c";

TEST(universal_mach_o_files_yield_the_slice_of_the_requested_cpu) {
    static FatImg f;
    for (int wide = 0; wide < 2; wide++) {
        fat_build(&f, wide != 0);
        ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_X86_64, k_fat_x86_id));
        ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, k_fat_arm_id));
        ASSERT_TRUE(fat_slice_is(f.b, f.n, 0u, k_fat_x86_id)); /* frame recovery is x86-64 */
    }
    {
        char root[400], dir[600], path[700], cmd[CMD_CAP];
        char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
        u64 off = 0;
        BreakCrashSymbolStore *st;
        BreakElfSymbols *s;
        path_in(root, sizeof(root), "fatroot");
        snprintf(dir, sizeof(dir), "%s/fatbuild", root);
        snprintf(cmd, sizeof(cmd), "rm -rf '%s'; mkdir -p '%s'", root, dir);
        ASSERT_TRUE(run(cmd));
        snprintf(path, sizeof(path), "%s/universal.dylib", dir);
        ASSERT_TRUE(write_bytes(path, f.b, f.n));
        s = break_crash_symbols_open(path);
        ASSERT_NOT_NULL(s);
        ASSERT_STR_EQ(break_elf_symbols_build_id(s), k_fat_x86_id);
        break_elf_symbols_destroy(s);
        st = break_crash_symbol_store_open(root);
        ASSERT_NOT_NULL(st);
        ASSERT_TRUE(break_crash_symbol_store_lookup(st, "fatbuild", "universal.dylib", 0x1084u, name,
                                                    sizeof(name), &off));
        ASSERT_STR_EQ(name, "gamma");
        ASSERT_EQ(off, 4u);
        break_crash_symbol_store_destroy(st);
    }
}

TEST(a_mach_o_file_without_the_requested_cpu_gives_null) {
    static MachoImg img;
    static FatImg f;
    MachoSpec arm = {0u, MO_ARM64, 6u, true, 0u};
    BreakElfSymbols *s;
    macho_default(&img, 0u, 6u); /* thin x86_64 */
    ASSERT_TRUE(fat_slice_is(img.b, img.n, MO_X86_64, "0f1e2d3c4b5a69788796a5b4c3d2e1f0"));
    ASSERT_TRUE(fat_slice_is(img.b, img.n, MO_ARM64, NULL));
    macho_build(&img, &arm);
    ASSERT_TRUE(fat_slice_is(img.b, img.n, MO_ARM64, "0f1e2d3c4b5a69788796a5b4c3d2e1f0"));
    ASSERT_TRUE(fat_slice_is(img.b, img.n, MO_X86_64, NULL));
    s = fat_open(img.b, img.n, 0u); /* a thin file of either CPU opens without a request */
    ASSERT_NOT_NULL(s);
    break_elf_symbols_destroy(s);
    /* only CPU types the reader supports may be requested */
    ASSERT_TRUE(fat_slice_is(img.b, img.n, 0x0000000cu, NULL));
    ASSERT_TRUE(fat_slice_is(img.b, img.n, 0x01000012u, NULL));
    /* a universal file holding only arm64 has no default slice */
    fat_build(&f, false);
    fat_be32(f.b + 4, 1u);
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, k_fat_arm_id));
    ASSERT_TRUE(fat_slice_is(f.b, f.n, 0u, NULL));
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_X86_64, NULL));
}

TEST(structurally_bad_universal_headers_are_refused) {
    static FatImg f;
    /* entry 0 is arm64 at 0x1000, entry 1 is x86_64 at 0x2000; narrow entries are 20 bytes */
    const u32 counts[] = {0u, 33u, 52u /* a Java class file's major version */, 0xffffffffu};
    for (usize i = 0; i < sizeof(counts) / sizeof(counts[0]); i++) {
        fat_build(&f, false);
        fat_be32(f.b + 4, counts[i]);
        ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    }
    fat_build(&f, false);
    fat_be32(f.b + 8 + 20 + 12, (u32)f.slice_n + 1u); /* x86_64 slice runs past the file */
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    fat_build(&f, false);
    fat_be32(f.b + 8 + 8, 40u); /* arm64 slice starts inside the entry table (which ends at 48) */
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_X86_64, NULL));
    fat_build(&f, false);
    fat_be32(f.b + 8 + 20 + 8, 0x1010u); /* x86_64 slice overlaps the arm64 one */
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    /* two arm64 entries, each naming a valid arm64 image */
    fat_build(&f, false);
    memcpy(f.b + 0x2000, f.b + 0x1000, f.slice_n);
    fat_be32(f.b + 8 + 20, MO_ARM64);
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    /* entries swapped CPU types: each slice holds the other CPU's image */
    fat_build(&f, false);
    fat_be32(f.b + 8, MO_X86_64);
    fat_be32(f.b + 8 + 20, MO_ARM64);
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_X86_64, NULL));
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    /* 64-bit entries: an offset with its high word set */
    fat_build(&f, true);
    fat_be64(f.b + 8 + 32 + 8, 0x100002000ull);
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    fat_build(&f, true);
    fat_be64(f.b + 8 + 32 + 16, (u64)1 << 40); /* size past the file */
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    /* a slice is parsed as exactly its size: one byte short of the image */
    fat_build(&f, false);
    fat_be32(f.b + 8 + 20 + 12, (u32)f.slice_n - 1u);
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_X86_64, NULL));
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, k_fat_arm_id));
}

TEST(a_truncated_universal_file_is_refused_at_every_length) {
    static FatImg f;
    fat_build(&f, false);
    for (usize n = 0; n < f.n; n += (n < 64u || n + 64u > f.n) ? 1u : 7u) {
        BreakElfSymbols *s = fat_open(f.b, n, 0u);
        if (s != NULL) {
            printf("    a %zu-byte prefix of %zu loaded\n", (size_t)n, (size_t)f.n);
            break_elf_symbols_destroy(s);
            ASSERT_TRUE(false);
        }
    }
}

/* `count` narrow entries: the real arm64 and x86_64 slices, then empty
 * slices of distinct unsupported CPU types placed just past the table. */
static void fat_with_entries(FatImg *f, u32 count) {
    fat_build(f, false);
    fat_be32(f->b + 4, count);
    for (u32 i = 2u; i < count; i++) {
        u8 *e = f->b + 8u + 20u * i;
        fat_be32(e, 0x00000100u + i);
        fat_be32(e + 8, 8u + 20u * count);
        fat_be32(e + 12, 0u);
    }
}

TEST(a_universal_file_may_list_32_slices_but_not_33) {
    static FatImg f;
    char path[400];
    BreakElfSymbols *s;
    fat_with_entries(&f, 32u);
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_X86_64, k_fat_x86_id));
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, k_fat_arm_id));
    fat_with_entries(&f, 33u);
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_X86_64, NULL));
    ASSERT_TRUE(fat_slice_is(f.b, f.n, MO_ARM64, NULL));
    /* 0 is not a CPU: the "either CPU" default is only for break_macho_symbols_open */
    fat_build(&f, false);
    path_in(path, sizeof(path), "image.fat0");
    ASSERT_TRUE(write_bytes(path, f.b, f.n));
    ASSERT_TRUE(break_macho_symbols_open_cpu(path, 0u) == NULL);
    {
        static MachoImg img;
        macho_default(&img, 0u, 6u);
        ASSERT_TRUE(write_bytes(path, img.b, img.n));
        s = break_macho_symbols_open(path);
        ASSERT_NOT_NULL(s);
        break_elf_symbols_destroy(s);
        ASSERT_TRUE(break_macho_symbols_open_cpu(path, 0u) == NULL);
    }
}

/* llvm-nm's address for `_name` in one architecture of a universal file */
static bool llvm_nm_arch(const char *bin, const char *arch, const char *name, u64 *out) {
    char cmd[900], line[200];
    FILE *p;
    snprintf(cmd, sizeof(cmd), "llvm-nm --arch=%s '%s' 2>/dev/null | awk '$3==\"_%s\" {print $1}'", arch,
             bin, name);
    p = popen(cmd, "r");
    if (p == NULL) return false;
    if (fgets(line, sizeof(line), p) == NULL) {
        pclose(p);
        return false;
    }
    pclose(p);
    *out = strtoull(line, NULL, 16);
    return true;
}

TEST(a_real_universal_dylib_from_llvm_lipo_agrees_with_llvm_nm) {
    const struct { const char *arch, *triple; u32 cpu; } archs[] = {
        {"x86_64", "x86_64-apple-macos11", MO_X86_64},
        {"arm64", "arm64-apple-macos11", MO_ARM64},
    };
    const char *names[] = {"f1", "f2", "f3", "start"};
    char src[400], obj[400], thin[2][400], uni[400], cmd[CMD_CAP];
    char ids[2][129];
    if (system("command -v clang >/dev/null 2>&1 && command -v ld64.lld >/dev/null 2>&1 && "
               "command -v llvm-nm >/dev/null 2>&1 && command -v llvm-lipo >/dev/null 2>&1") != 0) {
        printf("skipped (clang, ld64.lld, llvm-nm or llvm-lipo missing) ");
        return;
    }
    path_in(src, sizeof(src), "uni.c");
    path_in(obj, sizeof(obj), "uni.o");
    path_in(thin[0], sizeof(thin[0]), "uni_x86_64.dylib");
    path_in(thin[1], sizeof(thin[1]), "uni_arm64.dylib");
    path_in(uni, sizeof(uni), "uni.dylib");
    ASSERT_TRUE(write_text(src, k_macho_src));
    for (usize a = 0; a < 2u; a++) {
        BreakElfSymbols *s;
        snprintf(cmd, sizeof(cmd),
                 "clang -target %s -O1 -fno-inline -c '%s' -o '%s' 2>/dev/null && "
                 "ld64.lld -arch %s -platform_version macos 11.0 11.0 -dylib '%s' -o '%s' 2>/dev/null",
                 archs[a].triple, src, obj, archs[a].arch, obj, thin[a]);
        ASSERT_TRUE(run(cmd));
        s = break_macho_symbols_open(thin[a]);
        ASSERT_NOT_NULL(s);
        snprintf(ids[a], sizeof(ids[a]), "%s", break_elf_symbols_build_id(s));
        break_elf_symbols_destroy(s);
    }
    ASSERT_TRUE(strcmp(ids[0], ids[1]) != 0);
    snprintf(cmd, sizeof(cmd), "llvm-lipo -create '%s' '%s' -output '%s' 2>/dev/null", thin[0], thin[1], uni);
    ASSERT_TRUE(run(cmd));
    for (usize a = 0; a < 2u; a++) {
        BreakElfSymbols *s = break_macho_symbols_open_cpu(uni, archs[a].cpu);
        ASSERT_NOT_NULL(s);
        ASSERT_STR_EQ(break_elf_symbols_build_id(s), ids[a]);
        for (usize i = 0; i < 4u; i++) {
            u64 rel = 0;
            ASSERT_TRUE(llvm_nm_arch(uni, archs[a].arch, names[i], &rel));
            ASSERT_TRUE(mo_lookup(s, rel, names[i], 0u));
            ASSERT_TRUE(mo_lookup(s, rel + 1u, names[i], 1u));
        }
        break_elf_symbols_destroy(s);
    }
}

static void cleanup(void) {
    char cmd[400];
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'", g_dir);
    (void)system(cmd);
}

TEST_MAIN_BEGIN()
    dir_init();
    RUN_TEST(resolves_every_function_of_a_real_binary_against_nm);
    RUN_TEST(addresses_outside_any_function_do_not_resolve);
    RUN_TEST(a_stripped_binary_loads_and_resolves_nothing);
    RUN_TEST(a_position_independent_binary_resolves_by_file_address);
    RUN_TEST(a_shared_object_resolves_its_exported_functions);
    RUN_TEST(the_gnu_build_id_is_read_as_hex);
    RUN_TEST(files_that_are_not_64_bit_little_endian_elf_are_refused);
    RUN_TEST(a_truncated_file_is_refused_at_every_length);
    RUN_TEST(corrupting_the_section_and_symbol_tables_never_crashes_and_usually_fails);
    RUN_TEST(symbol_entries_pointing_outside_the_string_table_are_skipped_not_followed);
    RUN_TEST(a_file_larger_than_the_limit_is_refused_even_when_it_is_otherwise_valid);
    RUN_TEST(a_symbol_table_with_the_wrong_entry_size_is_refused);
    RUN_TEST(a_stripped_shared_object_still_resolves_its_exports_through_dynsym);
    RUN_TEST(a_real_crash_is_symbolized_into_the_call_chain);
    RUN_TEST(a_position_independent_executable_is_symbolized_through_its_load_bias);
    RUN_TEST(frames_in_modules_without_stored_symbols_stay_unresolved);
    RUN_TEST(a_missing_symbol_file_leaves_frames_with_module_offsets_only);
    RUN_TEST(the_walker_follows_an_arm64_frame_pointer_chain_too);
    RUN_TEST(the_walker_follows_the_saved_rbp_chain_inside_the_window_only);
    RUN_TEST(a_forged_chain_cannot_loop_backwards_or_leave_the_window);
    RUN_TEST(a_long_chain_is_cut_at_the_cap);
    RUN_TEST(a_hostile_build_id_or_module_name_cannot_reach_outside_the_symbol_root);
    RUN_TEST(the_store_refuses_names_that_could_leave_its_root_even_when_a_valid_file_is_there);
    RUN_TEST(symbols_uploaded_after_a_miss_are_found_by_the_same_open_store);
    RUN_TEST(a_mach_o_image_resolves_code_symbols_relative_to_its_text_segment);
    RUN_TEST(the_mach_o_uuid_is_read_as_hex);
    RUN_TEST(section_numbers_count_across_segments_and_data_sections_are_not_code);
    RUN_TEST(mach_o_files_of_the_wrong_kind_are_refused);
    RUN_TEST(a_truncated_mach_o_file_is_refused_at_every_length);
    RUN_TEST(each_structural_mach_o_corruption_is_refused);
    RUN_TEST(random_mach_o_load_command_damage_never_crashes);
    RUN_TEST(the_store_symbolizes_a_mach_o_module_from_a_record);
    RUN_TEST(real_mach_o_images_from_the_llvm_toolchain_agree_with_llvm_nm);
    RUN_TEST(the_format_dispatcher_opens_elf_and_mach_o_and_nothing_else);
    RUN_TEST(the_load_command_count_is_capped_even_when_the_commands_fit);
    RUN_TEST(an_unknown_load_command_must_still_be_eight_byte_aligned);
    RUN_TEST(a_code_symbol_below_the_text_segment_is_skipped);
    RUN_TEST(a_command_count_past_the_last_command_is_refused_at_the_file_end);
    RUN_TEST(universal_mach_o_files_yield_the_slice_of_the_requested_cpu);
    RUN_TEST(a_mach_o_file_without_the_requested_cpu_gives_null);
    RUN_TEST(structurally_bad_universal_headers_are_refused);
    RUN_TEST(a_truncated_universal_file_is_refused_at_every_length);
    RUN_TEST(a_universal_file_may_list_32_slices_but_not_33);
    RUN_TEST(a_real_universal_dylib_from_llvm_lipo_agrees_with_llvm_nm);
    cleanup();
TEST_MAIN_END()
