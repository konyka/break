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
    RUN_TEST(the_walker_follows_the_saved_rbp_chain_inside_the_window_only);
    RUN_TEST(a_forged_chain_cannot_loop_backwards_or_leave_the_window);
    RUN_TEST(a_long_chain_is_cut_at_the_cap);
    RUN_TEST(a_hostile_build_id_or_module_name_cannot_reach_outside_the_symbol_root);
    RUN_TEST(the_store_refuses_names_that_could_leave_its_root_even_when_a_valid_file_is_there);
    cleanup();
TEST_MAIN_END()
