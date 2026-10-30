#define _POSIX_C_SOURCE 200809L
#include <crash/break_crash_symbolize.h>

#include <elf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define SYM_MAX_FILE (256ull * 1024ull * 1024ull)
#define SYM_MAX_SECTIONS 4096u
#define SYM_MAX_SYMBOLS (4u * 1024u * 1024u)
#define SYM_NAME_COPY BREAK_CRASH_SYMBOLIZE_NAME_MAX

/* One usable function symbol, in file-address terms. The name is an offset
 * into a private copy of the string table (validated NUL-terminated). */
typedef struct {
    u64 addr;
    u64 size;
    u32 name_off;
} SymEntry;

struct BreakElfSymbols {
    SymEntry *syms;      /* sorted by addr, non-overlapping not required */
    u32 count;
    char *strtab;        /* owned copy */
    u64 strtab_size;
    bool is_exec;        /* ET_EXEC: symbol addresses are absolute, no load bias applies */
    char build_id[129];
};

/* [off, off+len) inside a file of `size` bytes, overflow-safe. */
static bool in_file(u64 off, u64 len, u64 size) {
    return off <= size && len <= size - off;
}

static int sym_cmp(const void *a, const void *b) {
    const SymEntry *x = (const SymEntry *)a, *y = (const SymEntry *)b;
    if (x->addr != y->addr) return x->addr < y->addr ? -1 : 1;
    if (x->size != y->size) return x->size > y->size ? -1 : 1; /* larger first */
    return 0;
}

/* NT_GNU_BUILD_ID from a SHT_NOTE section, as lowercase hex. */
static void read_build_id(const u8 *file, u64 size, const Elf64_Shdr *sh, char out[129]) {
    u64 pos = 0;
    const u8 *p = file + sh->sh_offset;
    out[0] = '\0';
    while (pos + sizeof(Elf64_Nhdr) <= sh->sh_size) {
        Elf64_Nhdr nh;
        u64 name_len, desc_len, name_pad, desc_pad;
        memcpy(&nh, p + pos, sizeof(nh));
        pos += sizeof(nh);
        name_len = nh.n_namesz;
        desc_len = nh.n_descsz;
        name_pad = (name_len + 3u) & ~3ull;
        desc_pad = (desc_len + 3u) & ~3ull;
        if (!in_file(pos, name_pad, sh->sh_size) ||
            !in_file(pos + name_pad, desc_pad, sh->sh_size)) {
            return;
        }
        if (nh.n_type == NT_GNU_BUILD_ID && name_len == 4u &&
            memcmp(p + pos, "GNU", 4u) == 0 && desc_len > 0u && desc_len <= 64u) {
            static const char hex[] = "0123456789abcdef";
            for (u64 i = 0; i < desc_len; i++) {
                out[2u * i] = hex[p[pos + name_pad + i] >> 4];
                out[2u * i + 1u] = hex[p[pos + name_pad + i] & 15u];
            }
            out[2u * desc_len] = '\0';
            return;
        }
        pos += name_pad + desc_pad;
    }
    (void)file;
    (void)size;
}

BreakElfSymbols *break_elf_symbols_open(const char *path) {
    BreakElfSymbols *s = NULL;
    u8 *file = NULL;
    FILE *f;
    struct stat st;
    u64 size;
    Elf64_Ehdr eh;
    const Elf64_Shdr *sh;
    int sym_idx = -1, dyn_idx = -1;
    if (path == NULL || path[0] == '\0') return NULL;
    f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fstat(fileno(f), &st) != 0 || !S_ISREG(st.st_mode) || st.st_size < (off_t)sizeof(eh) ||
        (u64)st.st_size > SYM_MAX_FILE) {
        fclose(f);
        return NULL;
    }
    size = (u64)st.st_size;
    file = (u8 *)malloc((size_t)size);
    if (file == NULL || fread(file, 1u, (size_t)size, f) != (size_t)size) {
        fclose(f);
        free(file);
        return NULL;
    }
    fclose(f);

    memcpy(&eh, file, sizeof(eh));
    if (memcmp(eh.e_ident, ELFMAG, SELFMAG) != 0 || eh.e_ident[EI_CLASS] != ELFCLASS64 ||
        eh.e_ident[EI_DATA] != ELFDATA2LSB || eh.e_ident[EI_VERSION] != EV_CURRENT ||
        eh.e_version != EV_CURRENT || eh.e_machine != EM_X86_64 ||
        eh.e_shentsize != sizeof(Elf64_Shdr) || eh.e_shnum == 0u || eh.e_shnum > SYM_MAX_SECTIONS ||
        !in_file(eh.e_shoff, (u64)eh.e_shnum * sizeof(Elf64_Shdr), size)) {
        free(file);
        return NULL;
    }
    sh = (const Elf64_Shdr *)(const void *)(file + eh.e_shoff);
    s = (BreakElfSymbols *)calloc(1u, sizeof(*s));
    if (s == NULL) {
        free(file);
        return NULL;
    }
    s->is_exec = eh.e_type == ET_EXEC;
    for (unsigned i = 0; i < eh.e_shnum; i++) {
        if (sh[i].sh_type == SHT_NOBITS) continue;
        if (sh[i].sh_type != SHT_NULL && !in_file(sh[i].sh_offset, sh[i].sh_size, size)) {
            goto fail; /* a section that claims bytes outside the file: the file is not trustworthy */
        }
        if (sh[i].sh_type == SHT_SYMTAB && sym_idx < 0) sym_idx = (int)i;
        if (sh[i].sh_type == SHT_DYNSYM && dyn_idx < 0) dyn_idx = (int)i;
        if (sh[i].sh_type == SHT_NOTE && s->build_id[0] == '\0') {
            read_build_id(file, size, &sh[i], s->build_id);
        }
    }
    {
        int use = sym_idx >= 0 ? sym_idx : dyn_idx;   /* a stripped file keeps only .dynsym */
        if (use >= 0) {
            const Elf64_Shdr *symsec = &sh[use];
            const Elf64_Shdr *strsec;
            u64 n_syms;
            const Elf64_Sym *syms;
            u32 kept = 0;
            if (symsec->sh_entsize != sizeof(Elf64_Sym) || symsec->sh_link >= eh.e_shnum) goto fail;
            strsec = &sh[symsec->sh_link];
            if (strsec->sh_type != SHT_STRTAB || strsec->sh_size == 0u) goto fail;
            n_syms = symsec->sh_size / sizeof(Elf64_Sym);
            if (n_syms > SYM_MAX_SYMBOLS) goto fail;
            syms = (const Elf64_Sym *)(const void *)(file + symsec->sh_offset);
            s->strtab = (char *)malloc((size_t)strsec->sh_size);
            s->syms = (SymEntry *)malloc((size_t)(n_syms ? n_syms : 1u) * sizeof(SymEntry));
            if (s->strtab == NULL || s->syms == NULL) goto fail;
            memcpy(s->strtab, file + strsec->sh_offset, (size_t)strsec->sh_size);
            s->strtab[strsec->sh_size - 1u] = '\0';       /* every name now ends inside the table */
            s->strtab_size = strsec->sh_size;
            for (u64 i = 0; i < n_syms; i++) {
                unsigned type = ELF64_ST_TYPE(syms[i].st_info);
                if (syms[i].st_shndx == SHN_UNDEF || syms[i].st_shndx >= SHN_LORESERVE) continue;
                if (syms[i].st_shndx >= eh.e_shnum) continue;
                if (type != STT_FUNC && type != STT_GNU_IFUNC && type != STT_NOTYPE) continue;
                if (type != STT_FUNC && type != STT_GNU_IFUNC) {
                    /* untyped symbols count only when they sit in an executable section */
                    if (!(sh[syms[i].st_shndx].sh_flags & SHF_EXECINSTR)) continue;
                }
                if (syms[i].st_size == 0u || syms[i].st_value > UINT64_MAX - syms[i].st_size) continue;
                if (syms[i].st_name >= s->strtab_size || s->strtab[syms[i].st_name] == '\0') continue;
                s->syms[kept].addr = syms[i].st_value;
                s->syms[kept].size = syms[i].st_size;
                s->syms[kept].name_off = syms[i].st_name;
                kept++;
            }
            qsort(s->syms, kept, sizeof(SymEntry), sym_cmp);
            s->count = kept;
        }
    }
    free(file);
    return s;

fail:
    free(file);
    break_elf_symbols_destroy(s);
    return NULL;
}

void break_elf_symbols_destroy(BreakElfSymbols *s) {
    if (s == NULL) return;
    free(s->syms);
    free(s->strtab);
    free(s);
}

u32 break_elf_symbols_count(const BreakElfSymbols *s) {
    return s != NULL ? s->count : 0u;
}

bool break_elf_symbols_is_exec(const BreakElfSymbols *s) {
    return s != NULL && s->is_exec;
}

const char *break_elf_symbols_build_id(const BreakElfSymbols *s) {
    return s != NULL ? s->build_id : "";
}

bool break_elf_symbols_lookup(const BreakElfSymbols *s, u64 vaddr, char *out_name, usize out_cap,
                              u64 *out_offset) {
    u32 lo, hi, best;
    bool found = false;
    if (s == NULL || out_name == NULL || out_cap == 0u || out_offset == NULL || s->count == 0u) {
        return false;
    }
    /* last symbol whose start <= vaddr, then walk back over larger candidates:
     * nested or aliased symbols are possible, so the first one that CONTAINS
     * vaddr wins (the walk is bounded) */
    lo = 0u;
    hi = s->count;
    while (lo < hi) {
        u32 mid = lo + (hi - lo) / 2u;
        if (s->syms[mid].addr <= vaddr) lo = mid + 1u; else hi = mid;
    }
    best = lo;
    for (u32 steps = 0u; best > 0u && steps < 64u; steps++) {
        const SymEntry *e = &s->syms[best - 1u];
        if (vaddr - e->addr < e->size) {
            const char *name = s->strtab + e->name_off;
            usize n = strnlen(name, (usize)(s->strtab_size - e->name_off));
            if (n >= out_cap) n = out_cap - 1u;
            memcpy(out_name, name, n);
            out_name[n] = '\0';
            *out_offset = vaddr - e->addr;
            found = true;
            break;
        }
        best--;
    }
    return found;
}

/* ---------------------------------------------------------------------------
 * Frame recovery
 * ------------------------------------------------------------------------- */

#include <crash/break_crash.h>

#define STORE_ROOT_MAX 1000u
#define STORE_CACHE 8u

typedef struct {
    char key[STORE_ROOT_MAX + 160u]; /* the path the entry was loaded from */
    BreakElfSymbols *syms;           /* a successfully loaded symbol file */
    bool used;
} StoreEntry;

struct BreakCrashSymbolStore {
    char root[STORE_ROOT_MAX + 1u];
    StoreEntry cache[STORE_CACHE];
    u32 next;
};

BreakCrashSymbolStore *break_crash_symbol_store_open(const char *symbol_root) {
    BreakCrashSymbolStore *st;
    struct stat sb;
    if (symbol_root == NULL || symbol_root[0] == '\0' || strlen(symbol_root) > STORE_ROOT_MAX ||
        stat(symbol_root, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        return NULL;
    }
    st = (BreakCrashSymbolStore *)calloc(1u, sizeof(*st));
    if (st != NULL) {
        memcpy(st->root, symbol_root, strlen(symbol_root) + 1u);
    }
    return st;
}

void break_crash_symbol_store_destroy(BreakCrashSymbolStore *st) {
    if (st == NULL) return;
    for (u32 i = 0u; i < STORE_CACHE; i++) {
        break_elf_symbols_destroy(st->cache[i].syms);
    }
    free(st);
}

/* [0-9a-z-]{1,64}: the record grammar's build id, re-checked here so the store
 * does not depend on the parser to keep a path safe. */
static bool build_id_ok(const char *id) {
    usize n;
    if (id == NULL) return false;
    n = strlen(id);
    if (n == 0u || n > 64u) return false;
    for (usize i = 0u; i < n; i++) {
        char c = id[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '-')) return false;
    }
    return true;
}

/* a module name that is exactly one path component: printable, no '/', no
 * backslash, not "." or "..", at most 255 bytes */
static bool module_name_ok(const char *name) {
    usize n;
    if (name == NULL) return false;
    n = strlen(name);
    if (n == 0u || n > 255u || strcmp(name, ".") == 0 || strcmp(name, "..") == 0) return false;
    for (usize i = 0u; i < n; i++) {
        unsigned char c = (unsigned char)name[i];
        if (c < 0x21u || c > 0x7eu || c == '/' || c == '\\') return false;
    }
    return true;
}

static BreakElfSymbols *store_get(BreakCrashSymbolStore *st, const char *build_id, const char *module) {
    char path[STORE_ROOT_MAX + 160u + 256u];
    int n;
    if (!build_id_ok(build_id) || !module_name_ok(module)) return NULL;
    n = snprintf(path, sizeof(path), "%s/%s/%s", st->root, build_id, module);
    if (n <= 0 || (usize)n >= sizeof(path)) return NULL;
    for (u32 i = 0u; i < STORE_CACHE; i++) {
        if (st->cache[i].used && strcmp(st->cache[i].key, path) == 0) {
            return st->cache[i].syms;
        }
    }
    {
        /* only successful loads are cached: a build's symbol file never changes once it is
         * there, but it may not have arrived yet when the first crash of that build does */
        BreakElfSymbols *loaded = break_elf_symbols_open(path);
        StoreEntry *e;
        if (loaded == NULL) return NULL;
        e = &st->cache[st->next];
        st->next = (st->next + 1u) % STORE_CACHE;
        break_elf_symbols_destroy(e->syms);
        e->syms = loaded;
        e->used = true;
        memcpy(e->key, path, (usize)n + 1u);
        return e->syms;
    }
}

bool break_crash_symbol_store_lookup(BreakCrashSymbolStore *st, const char *build_id, const char *module,
                                     u64 module_offset, char *out_name, usize out_cap, u64 *out_offset) {
    BreakElfSymbols *syms;
    if (st == NULL || out_name == NULL || out_cap == 0u || out_offset == NULL) return false;
    syms = store_get(st, build_id, module);
    if (syms == NULL) return false;
    return break_elf_symbols_lookup(syms, module_offset, out_name, out_cap, out_offset);
}

void break_crash_symbolize_address(BreakCrashSymbolStore *st, const BreakCrashRecord *r, u64 pc,
                                   BreakCrashFrame *out) {
    u64 modules;
    if (out == NULL) return;
    memset(out, 0, sizeof(*out));
    out->pc = pc;
    if (st == NULL || r == NULL) return;
    modules = break_crash_record_module_count(r);
    for (u64 i = 0u; i < modules; i++) {
        const char *name = NULL;
        u64 bias = 0u, size = 0u;
        if (!break_crash_record_module_at(r, i, &name, &bias, &size) || name == NULL) continue;
        if (pc < bias || pc - bias >= size) continue;
        {
            BreakElfSymbols *syms;
            usize nl = strlen(name);
            out->module_offset = pc - bias;
            if (nl >= sizeof(out->module)) nl = sizeof(out->module) - 1u;
            memcpy(out->module, name, nl);
            out->module[nl] = '\0';
            syms = store_get(st, break_crash_record_build_id(r), name);
            if (syms != NULL &&
                break_elf_symbols_lookup(syms, break_elf_symbols_is_exec(syms) ? pc : out->module_offset,
                                         out->symbol, sizeof(out->symbol), &out->symbol_offset)) {
                out->resolved = true;
            } else {
                out->symbol[0] = '\0';
                out->symbol_offset = 0u;
            }
        }
        return;
    }
}

static bool read_word(const u8 *win, usize len, u64 base, u64 addr, u64 *out) {
    u64 off;
    if (addr < base) return false;
    off = addr - base;
    if (off > len || len - off < 8u) return false;
    memcpy(out, win + off, 8u);   /* x86-64 is little endian; so is the record's stack bytes */
    return true;
}

u32 break_crash_symbolize_record(BreakCrashSymbolStore *st, const BreakCrashRecord *r,
                                 BreakCrashFrame *frames, u32 cap) {
    u64 regs[3];
    const u8 *win = NULL;
    usize wlen;
    u64 rbp;
    u32 n = 0u;
    if (r == NULL || frames == NULL || cap == 0u) return 0u;
    if (cap > BREAK_CRASH_SYMBOLIZE_MAX_FRAMES) cap = BREAK_CRASH_SYMBOLIZE_MAX_FRAMES;
    break_crash_record_registers(r, regs);
    if (regs[0] == 0u) return 0u;
    break_crash_symbolize_address(st, r, regs[0], &frames[n++]);
    wlen = break_crash_record_stack_window(r, &win);
    rbp = regs[2];
    /* the window starts at rsp; read_word refuses any address outside it */
    while (n < cap && win != NULL && wlen >= 16u) {
        u64 saved_rbp, ret;
        if (rbp > UINT64_MAX - 16u) break;
        if (!read_word(win, wlen, regs[1], rbp, &saved_rbp) ||
            !read_word(win, wlen, regs[1], rbp + 8u, &ret)) {
            break;
        }
        if (ret == 0u) break;
        /* a return address names the instruction AFTER the call; look up pc-1 so a call that
         * ends a function is attributed to the caller, and report the return address itself */
        {
            BreakCrashFrame *f = &frames[n++];
            break_crash_symbolize_address(st, r, ret - 1u, f);
            f->pc = ret;
            if (f->module[0] != '\0') {
                f->module_offset += 1u;
            }
            if (f->resolved) {
                f->symbol_offset += 1u;
            }
        }
        if (saved_rbp <= rbp) break;          /* a frame-pointer chain only grows toward higher addresses */
        rbp = saved_rbp;
    }
    return n;
}
