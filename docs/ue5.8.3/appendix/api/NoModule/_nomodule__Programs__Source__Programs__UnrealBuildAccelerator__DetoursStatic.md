# NoModule / _nomodule__Programs__Source__Programs__UnrealBuildAccelerator__DetoursStatic

- module root: `.`
- headers: 1; symbols: 63
- symbol kinds: enum=1, enumerator=2, member=7, namespace=1, prototype=48, struct=2, variable=2

### `Source/Programs/UnrealBuildAccelerator/DetoursStatic/UbaGlibc.h` (Other)


#### enum `GlibcEntryKind`  
`enum GlibcEntryKind : uba::u32`  
_L23-27_
- L25 _public enumerator_ `GlibcEntry_HandlerHook = 0`
- L26 _public enumerator_ `GlibcEntry_ImportSlot = 1`

#### struct `GlibcHandlerEntry`  
`struct GlibcHandlerEntry`  
_L29-34_
- L31 _public member_ `char name[24];` — HandlerHook: stripped libc name (e.g. "open"). ImportSlot: exact target symbol name.
- L32 _public member_ `uba::u32 offset;` — bytes from blob base (stamped post-link by Build.sh)
- L33 _public member_ `uba::u32 kind;` — GlibcEntryKind

#### struct `GlibcHandlerTable`  
`struct GlibcHandlerTable`  
_L38-44_
- L40 _public member_ `uba::u64 magic;`
- L41 _public member_ `uba::u32 count;`
- L42 _public member_ `uba::u32 reserved;`
- L43 _public member_ `GlibcHandlerEntry entries[kGlibcHandlerTableMaxEntries];`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uba`
- L20 _variable_ `static constexpr uba::u64 kGlibcHandlerTableMagic = 0x5448424C47414255ULL;` — 'UBAGLBHT' LE
- L21 _variable_ `static constexpr uba::u32 kGlibcHandlerTableMaxEntries = 64;`
- L49 _prototype_ `extern "C" int GlibcOpen(const char* path, int flags, int mode)`
- L50 _prototype_ `extern "C" int GlibcOpenat(int dirfd, const char* path, int flags, int mode)`
- L51 _prototype_ `extern "C" long GlibcRead(int fd, void* buf, unsigned long n)`
- L52 _prototype_ `extern "C" long GlibcWrite(int fd, const void* buf, unsigned long n)`
- L53 _prototype_ `extern "C" int GlibcClose(int fd)`
- L54 _prototype_ `extern "C" long GlibcLseek(int fd, long off, int whence)`
- L55 _prototype_ `extern "C" int GlibcFxstat(int ver, int fd, void* statbuf)`
- L56 _prototype_ `extern "C" void* GlibcMmap(void* addr, unsigned long len, int prot, int flags, int fd, long off)`
- L57 _prototype_ `extern "C" int GlibcAccess(const char* path, int mode)`
- L58 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcExit(int status)`
- L62 _prototype_ `extern "C" int GlibcStat(long arg1, void* arg2, void* arg3)` — Abort-on-reach handlers: stderr + exit_group(134). Patcher skips entries the target lacks. stat/lstat/fstatat ABI varies (__xstat 3-arg vs stat 2-arg); handler autodetects via LooksLikeXstatVer.
- L63 _prototype_ `extern "C" int GlibcLstat(long arg1, void* arg2, void* arg3)`
- L64 _prototype_ `extern "C" int GlibcFstatat(long arg1, long arg2, void* arg3, void* arg4, int arg5)`
- L65 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcStatx(void)`
- L66 _prototype_ `extern "C" int GlibcUnlink(const char* path)`
- L67 _prototype_ `extern "C" int GlibcUnlinkat(int dirfd, const char* path, int flags)`
- L68 _prototype_ `extern "C" int GlibcRename(const char* oldpath, const char* newpath)`
- L69 _prototype_ `extern "C" int GlibcRenameat(int olddirfd, const char* oldpath, int newdirfd, const char* newpath)`
- L70 _prototype_ `extern "C" int GlibcRenameat2(int olddirfd, const char* oldpath, int newdirfd, const char* newpath, unsigned int flags)`
- L71 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcLink(void)`
- L72 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcLinkat(void)`
- L73 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcSymlink(void)`
- L74 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcSymlinkat(void)`
- L75 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcReadlink(void)`
- L76 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcReadlinkat(void)`
- L77 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcTruncate(void)`
- L78 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcFtruncate(void)`
- L79 _prototype_ `extern "C" int GlibcMkdir(const char* path, unsigned int mode)` — `unsigned int` avoids pulling in <sys/types.h>; ABI matches libc mode_t.
- L80 _prototype_ `extern "C" int GlibcMkdirat(int dirfd, const char* path, unsigned int mode)`
- L81 _prototype_ `extern "C" int GlibcRmdir(const char* path)`
- L82 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcFork(void)`
- L83 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcVfork(void)`
- L84 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcClone(void)`
- L85 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcClone3(void)`
- L86 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcExecve(void)`
- L87 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcExecveat(void)`
- L88 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcDup(void)`
- L89 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcDup2(void)`
- L90 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcDup3(void)`
- L91 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcPipe(void)`
- L92 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcPipe2(void)`
- L93 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcOpendir(void)`
- L94 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcFdopendir(void)`
- L95 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcReaddir(void)`
- L96 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcClosedir(void)`
- L97 _prototype_ `extern "C" __attribute__((noreturn)) void GlibcGetdents64(void)`
- L98 _prototype_ `extern "C" int GlibcChdir(const char* path)`
- L99 _prototype_ `extern "C" int GlibcFchdir(int fd)`
