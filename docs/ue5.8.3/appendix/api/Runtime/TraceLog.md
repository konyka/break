# Runtime / TraceLog

- module root: `Source/Runtime/TraceLog`
- headers: 33; symbols: 1422
- symbol kinds: class=13, enum=62, enumerator=227, externvar=6, function=189, macro=235, member=236, namespace=85, prototype=214, struct=87, typedef=52, union=7, variable=9
- PrivateDependencyModuleNames: OpenSSL
- PublicIncludePathModuleNames: Core

### `Source/Runtime/TraceLog/Private/Trace/LZ4/lz4.c.inl` (Private)


#### enum `(anonymous)`  
`typedef enum`  
_L269-273_

#### union `LZ4_isLittleEndian::(anonymous)`  
`const union`  
_L281-281_

#### union `(anonymous)`  
`typedef union`  
_L300-300_
- desc: currently only defined for gcc and icc

#### enum `(anonymous)`  
`typedef enum`  
_L576-576_
- desc: Local Structures and types

#### enum `(anonymous)`  
`typedef enum`  
_L601-601_
- desc: This enum distinguishes several different modes of accessing previous content in the stream. - noDict        : There is no preceding content. - withPrefix64k : Table entries up to ctx->dictSize before the current blob blob being compressed are valid and refer to the preceding content (of length ctx->dictSize), which is available contiguously preceding in memory the content currently being compressed. - usingExtDict  : Like withPrefix64k, but the preceding content is somewhere else in memory, starting at ctx->dictionary with length ctx->dictSize. - usingDictCtx  : Like usingExtDict, but everything concerning the preceding content is in a separate context, pointed to by ctx->dictCtx. ctx->dictionary, ctx->dictSize, and table entries in the current context that refer to positions preceding the beginning of the current compression are ignored. Instead, ctx->dictCtx->dictionary and ctx->dictCtx ->dictSize describe the location and size of the preceding content, and matches are found by looking in the ctx ->dictCtx->hashTable.

#### enum `(anonymous)`  
`typedef enum`  
_L602-602_

#### struct `LZ4_stream_t_alignment::(anonymous)`  
`struct`  
_L1359-1359_

#### enum `(anonymous)`  
`typedef enum`  
_L1621-1621_

#### enum `(anonymous)`  
`typedef enum`  
_L1622-1622_

#### enum `(anonymous)`  
`typedef enum`  
_L1636-1636_
- desc: BEGIN EPIC MOD : The 'ok' identifier collides with symbols in the MacOS SDK

#### Free symbols / members of external scopes

- L44 _macro_ `# define LZ4_HEAPMODE 0`
- L51 _macro_ `#define ACCELERATION_DEFAULT 1` — ACCELERATION_DEFAULT : Select "acceleration" for LZ4_compress_fast() when parameter value <= 0
- L74 _macro_ `# define LZ4_FORCE_MEMORY_ACCESS 2`
- L76 _macro_ `# define LZ4_FORCE_MEMORY_ACCESS 1`
- L85 _macro_ `# define LZ4_FORCE_SW_BITCOUNT` — #if defined(_MSC_VER) && defined(_WIN32_WCE)     Visual Studio for WinCE doesn't support Hardware bit count
- L98 _macro_ `# define LZ4_SRC_INCLUDED 1`
- L102 _macro_ `#define LZ4_STATIC_LINKING_ONLY`
- L106 _macro_ `#define LZ4_DISABLE_DEPRECATE_WARNINGS /* due to LZ4_decompress_safe_withPrefix64k */`
- L109 _macro_ `#define LZ4_STATIC_LINKING_ONLY /* LZ4_DISTANCE_MAX */`
- L125 _macro_ `# define LZ4_FORCE_INLINE static __forceinline` — #  ifdef _MSC_VER      Visual Studio
- L129 _macro_ `# define LZ4_FORCE_INLINE static inline __attribute__((always_inline))`
- L131 _macro_ `# define LZ4_FORCE_INLINE static inline`
- L134 _macro_ `# define LZ4_FORCE_INLINE static`
- L154 _macro_ `# define LZ4_FORCE_O2_GCC_PPC64LE __attribute__((optimize("O2")))`
- L155 _macro_ `# define LZ4_FORCE_O2_INLINE_GCC_PPC64LE __attribute__((optimize("O2"))) LZ4_FORCE_INLINE`
- L157 _macro_ `# define LZ4_FORCE_O2_GCC_PPC64LE`
- L158 _macro_ `# define LZ4_FORCE_O2_INLINE_GCC_PPC64LE static`
- L162 _macro_ `# define expect(expr,value) (__builtin_expect ((expr),(value)) )`
- L164 _macro_ `# define expect(expr,value) (expr)`
- L168 _macro_ `#define likely(expr) expect(int(expr) != 0, 1)`
- L171 _macro_ `#define unlikely(expr) expect(int(expr) != 0, 0)`
- L179 _macro_ `#define ALLOC(s) malloc(s)` — #include <stdlib.h>     malloc, calloc, free
- L180 _macro_ `#define ALLOC_AND_ZERO(s) calloc(1,s)`
- L181 _macro_ `#define FREEMEM(p) free(p)`
- L183 _macro_ `#define MEM_INIT(p,v,s) memset((p),(v),(s))` — #include <string.h>     memset, memcpy
- L189 _macro_ `#define MINMATCH 4` — Common Constants
- L191 _macro_ `#define WILDCOPYLENGTH 8`
- L192 _macro_ `#define LASTLITERALS 5 /* see ../doc/lz4_Block_format.md#parsing-restrictions */`
- L193 _macro_ `#define MFLIMIT 12 /* see ../doc/lz4_Block_format.md#parsing-restrictions */` — #define LASTLITERALS   5     see ../doc/lz4_Block_format.md#parsing-restrictions
- L194 _macro_ `#define MATCH_SAFEGUARD_DISTANCE ((2*WILDCOPYLENGTH) - MINMATCH) /* ensure it's possible to write 2 x wildcopyLength without overflowing output buffer */` — #define MFLIMIT       12     see ../doc/lz4_Block_format.md#parsing-restrictions
- L195 _macro_ `#define FASTLOOP_SAFE_DISTANCE 64` — #define MATCH_SAFEGUARD_DISTANCE  ((2*WILDCOPYLENGTH) - MINMATCH)     ensure it's possible to write 2 x wildcopyLength without overflowing output buffer
- L196 _variable_ `static const int LZ4_minLength = (MFLIMIT+1);`
- L198 _macro_ `#define KB *(1 <<10)`
- L199 _macro_ `#define MB *(1 <<20)`
- L200 _macro_ `#define GB *(1U<<30)`
- L202 _macro_ `#define LZ4_DISTANCE_ABSOLUTE_MAX 65535`
- L207 _macro_ `#define ML_BITS 4`
- L208 _macro_ `#define ML_MASK ((1U<<ML_BITS)-1)`
- L209 _macro_ `#define RUN_BITS (8-ML_BITS)`
- L210 _macro_ `#define RUN_MASK ((1U<<RUN_BITS)-1)`
- L220 _macro_ `# define assert(condition) ((void)0)`
- L224 _macro_ `#define LZ4_STATIC_ASSERT(c) { enum { LZ4_static_assert = 1/(int)(!!(c)) }; } /* use after variable declarations */`
- L228 _variable_ `static int g_debuglog_enable = 1;`
- L229 _macro_ `# define DEBUGLOG(l, ...) { \`
- L236 _macro_ `# define DEBUGLOG(l, ...) {} /* disabled */`
- L248 _typedef_ `typedef uint8_t BYTE;`
- L249 _typedef_ `typedef uint16_t U16;`
- L250 _typedef_ `typedef uint32_t U32;`
- L251 _typedef_ `typedef int32_t S32;`
- L252 _typedef_ `typedef uint64_t U64;`
- L253 _typedef_ `typedef uintptr_t uptrval;`
- L255 _typedef_ `typedef unsigned char BYTE;`
- L256 _typedef_ `typedef unsigned short U16;`
- L257 _typedef_ `typedef unsigned int U32;`
- L258 _typedef_ `typedef signed int S32;`
- L259 _typedef_ `typedef unsigned long long U64;`
- L260 _typedef_ `typedef size_t uptrval;`
- L264 _typedef_ `typedef U64 reg_t;`
- L266 _typedef_ `typedef size_t reg_t;`
- L270 _enumerator_ `notLimited = 0` (scope `__anon79d69c360103`)
- L271 _enumerator_ `limitedOutput = 1` (scope `__anon79d69c360103`)
- L272 _enumerator_ `fillOutput = 2` (scope `__anon79d69c360103`)
- L273 _typedef_ `} limitedOutput_directive;`
- L279 _function_ `static unsigned LZ4_isLittleEndian(void)` — Reading and writing into memory
- L281 _member_ `const union { U32 u; BYTE c[4]; } one = { 1 };` (scope `LZ4_isLittleEndian::__anon79d69c36020a`)
- L281 _member_ `const union { U32 u; BYTE c[4]; } one = { 1 };` (scope `LZ4_isLittleEndian::__anon79d69c36020a`)
- L289 _function_ `static U16 LZ4_read16(const void* memPtr)`
- L290 _function_ `static U32 LZ4_read32(const void* memPtr)`
- L291 _function_ `static reg_t LZ4_read_ARCH(const void* memPtr)`
- L293 _function_ `static void LZ4_write16(void* memPtr, U16 value)`
- L294 _function_ `static void LZ4_write32(void* memPtr, U32 value)`
- L300 _member_ `typedef union { U16 u16; U32 u32; reg_t uArch; } __attribute__((packed)) unalign;` (scope `__anon79d69c36030a`) — currently only defined for gcc and icc
- L300 _member_ `typedef union { U16 u16; U32 u32; reg_t uArch; } __attribute__((packed)) unalign;` (scope `__anon79d69c36030a`) — currently only defined for gcc and icc
- L300 _member_ `typedef union { U16 u16; U32 u32; reg_t uArch; } __attribute__((packed)) unalign;` (scope `__anon79d69c36030a`) — currently only defined for gcc and icc
- L300 _typedef_ `typedef union { U16 u16; U32 u32; reg_t uArch; } __attribute__((packed)) unalign;` — currently only defined for gcc and icc
- L302 _function_ `static U16 LZ4_read16(const void* ptr)`
- L303 _function_ `static U32 LZ4_read32(const void* ptr)`
- L304 _function_ `static reg_t LZ4_read_ARCH(const void* ptr)`
- L339 _function_ `static U16 LZ4_readLE16(const void* memPtr)`
- L349 _function_ `static void LZ4_writeLE16(void* memPtr, U16 value)`
- L362 _function_ `void LZ4_wildCopy8(void* dstPtr, const void* srcPtr, void* dstEnd)`
- L371 _variable_ `static const unsigned inc32table[8] = {0, 1, 2, 1, 0, 4, 4, 4};`
- L372 _variable_ `static const int dec64table[8] = {0, 0, 0, -1, -4, 1, 2, 3};`
- L377 _macro_ `# define LZ4_FAST_DEC_LOOP 1`
- L384 _macro_ `# define LZ4_FAST_DEC_LOOP 0`
- L391 _function_ `LZ4_memcpy_using_offset_base(BYTE* dstPtr, const BYTE* srcPtr, BYTE* dstEnd, const size_t offset)`
- L415 _function_ `LZ4_wildCopy32(void* dstPtr, const void* srcPtr, void* dstEnd)`
- L428 _function_ `LZ4_memcpy_using_offset(BYTE* dstPtr, const BYTE* srcPtr, BYTE* dstEnd, const size_t offset)`
- L466 _function_ `static unsigned LZ4_NbCommonBytes (reg_t val)` — Common functions
- L537 _macro_ `#define STEPSIZE sizeof(reg_t)`
- L539 _function_ `unsigned LZ4_count(const BYTE* pIn, const BYTE* pMatch, const BYTE* pInLimit)`
- L569 _variable_ `static const int LZ4_64Klimit = ((64 KB) + (MFLIMIT-1));` — Local Constants
- L570 _variable_ `static const U32 LZ4_skipTrigger = 6;`
- L576 _enumerator_ `typedef enum { clearedTable = 0, byPtr, byU32, byU16 } tableType_t; /** * This enum distinguishes several different modes of accessing previous * content in the stream. * * - noDict : There is no preceding content. * - withPrefix64k : Table entries up to ctx->dictSize before the current blob` (scope `__anon79d69c360403`) — Local Structures and types
- L576 _enumerator_ `typedef enum { clearedTable = 0, byPtr, byU32, byU16 } tableType_t; /** * This enum distinguishes several different modes of accessing previous * content in the stream. * * - noDict : There is no preceding content. * - withPrefix64k : Table entries up to ctx->dictSize before the current blob` (scope `__anon79d69c360403`) — Local Structures and types
- L576 _enumerator_ `typedef enum { clearedTable = 0, byPtr, byU32, byU16 } tableType_t; /** * This enum distinguishes several different modes of accessing previous * content in the stream. * * - noDict : There is no preceding content. * - withPrefix64k : Table entries up to ctx->dictSize before the current blob` (scope `__anon79d69c360403`) — Local Structures and types
- L576 _enumerator_ `typedef enum { clearedTable = 0, byPtr, byU32, byU16 } tableType_t; /** * This enum distinguishes several different modes of accessing previous * content in the stream. * * - noDict : There is no preceding content. * - withPrefix64k : Table entries up to ctx->dictSize before the current blob` (scope `__anon79d69c360403`) — Local Structures and types
- L576 _typedef_ `typedef enum { clearedTable = 0, byPtr, byU32, byU16 } tableType_t;` — Local Structures and types
- L601 _enumerator_ `typedef enum { noDict = 0, withPrefix64k, usingExtDict, usingDictCtx } dict_directive; typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive; /*-************************************ * Local Utils **************************************/ int LZ4_versionNumber (void) { return LZ4_VERSION_NUMBER; }` (scope `__anon79d69c360503`) — This enum distinguishes several different modes of accessing previous content in the stream. - noDict        : There is no preceding content. - withPrefix64k : Table entries up to ctx->dictSize before the current blob blob being compressed are valid and refer to the preceding content (of length ctx->dictSize), which is available contiguously preceding in memory the content currently being compressed. - usingExtDict  : Like withPrefix64k, but the preceding content is somewhere else in memory, starting at ctx->dictionary with length ctx->dictSize. - usingDictCtx  : Like usingExtDict, but everything concerning the preceding content is in a separate context, pointed to by ctx->dictCtx. ctx->dictionary, ctx->dictSize, and table entries in the current context that refer to positions preceding the beginning of the current compression are ignored. Instead, ctx->dictCtx->dictionary and ctx->dictCtx ->dictSize describe the location and size of the preceding content, and matches are found by looking in the ctx ->dictCtx->hashTable.
- L601 _enumerator_ `typedef enum { noDict = 0, withPrefix64k, usingExtDict, usingDictCtx } dict_directive; typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive; /*-************************************ * Local Utils **************************************/ int LZ4_versionNumber (void) { return LZ4_VERSION_NUMBER; }` (scope `__anon79d69c360503`) — This enum distinguishes several different modes of accessing previous content in the stream. - noDict        : There is no preceding content. - withPrefix64k : Table entries up to ctx->dictSize before the current blob blob being compressed are valid and refer to the preceding content (of length ctx->dictSize), which is available contiguously preceding in memory the content currently being compressed. - usingExtDict  : Like withPrefix64k, but the preceding content is somewhere else in memory, starting at ctx->dictionary with length ctx->dictSize. - usingDictCtx  : Like usingExtDict, but everything concerning the preceding content is in a separate context, pointed to by ctx->dictCtx. ctx->dictionary, ctx->dictSize, and table entries in the current context that refer to positions preceding the beginning of the current compression are ignored. Instead, ctx->dictCtx->dictionary and ctx->dictCtx ->dictSize describe the location and size of the preceding content, and matches are found by looking in the ctx ->dictCtx->hashTable.
- L601 _enumerator_ `typedef enum { noDict = 0, withPrefix64k, usingExtDict, usingDictCtx } dict_directive; typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive; /*-************************************ * Local Utils **************************************/ int LZ4_versionNumber (void) { return LZ4_VERSION_NUMBER; }` (scope `__anon79d69c360503`) — This enum distinguishes several different modes of accessing previous content in the stream. - noDict        : There is no preceding content. - withPrefix64k : Table entries up to ctx->dictSize before the current blob blob being compressed are valid and refer to the preceding content (of length ctx->dictSize), which is available contiguously preceding in memory the content currently being compressed. - usingExtDict  : Like withPrefix64k, but the preceding content is somewhere else in memory, starting at ctx->dictionary with length ctx->dictSize. - usingDictCtx  : Like usingExtDict, but everything concerning the preceding content is in a separate context, pointed to by ctx->dictCtx. ctx->dictionary, ctx->dictSize, and table entries in the current context that refer to positions preceding the beginning of the current compression are ignored. Instead, ctx->dictCtx->dictionary and ctx->dictCtx ->dictSize describe the location and size of the preceding content, and matches are found by looking in the ctx ->dictCtx->hashTable.
- L601 _enumerator_ `typedef enum { noDict = 0, withPrefix64k, usingExtDict, usingDictCtx } dict_directive; typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive; /*-************************************ * Local Utils **************************************/ int LZ4_versionNumber (void) { return LZ4_VERSION_NUMBER; }` (scope `__anon79d69c360503`) — This enum distinguishes several different modes of accessing previous content in the stream. - noDict        : There is no preceding content. - withPrefix64k : Table entries up to ctx->dictSize before the current blob blob being compressed are valid and refer to the preceding content (of length ctx->dictSize), which is available contiguously preceding in memory the content currently being compressed. - usingExtDict  : Like withPrefix64k, but the preceding content is somewhere else in memory, starting at ctx->dictionary with length ctx->dictSize. - usingDictCtx  : Like usingExtDict, but everything concerning the preceding content is in a separate context, pointed to by ctx->dictCtx. ctx->dictionary, ctx->dictSize, and table entries in the current context that refer to positions preceding the beginning of the current compression are ignored. Instead, ctx->dictCtx->dictionary and ctx->dictCtx ->dictSize describe the location and size of the preceding content, and matches are found by looking in the ctx ->dictCtx->hashTable.
- L601 _typedef_ `typedef enum { noDict = 0, withPrefix64k, usingExtDict, usingDictCtx } dict_directive;` — This enum distinguishes several different modes of accessing previous content in the stream. - noDict        : There is no preceding content. - withPrefix64k : Table entries up to ctx->dictSize before the current blob blob being compressed are valid and refer to the preceding content (of length ctx->dictSize), which is available contiguously preceding in memory the content currently being compressed. - usingExtDict  : Like withPrefix64k, but the preceding content is somewhere else in memory, starting at ctx->dictionary with length ctx->dictSize. - usingDictCtx  : Like usingExtDict, but everything concerning the preceding content is in a separate context, pointed to by ctx->dictCtx. ctx->dictionary, ctx->dictSize, and table entries in the current context that refer to positions preceding the beginning of the current compression are ignored. Instead, ctx->dictCtx->dictionary and ctx->dictCtx ->dictSize describe the location and size of the preceding content, and matches are found by looking in the ctx ->dictCtx->hashTable.
- L602 _enumerator_ `typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive; /*-************************************ * Local Utils **************************************/ int LZ4_versionNumber (void) { return LZ4_VERSION_NUMBER; } const char* LZ4_versionString(void) { return LZ4_VERSION_STRING; }` (scope `__anon79d69c360603`)
- L602 _enumerator_ `typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive; /*-************************************ * Local Utils **************************************/ int LZ4_versionNumber (void) { return LZ4_VERSION_NUMBER; } const char* LZ4_versionString(void) { return LZ4_VERSION_STRING; }` (scope `__anon79d69c360603`)
- L602 _typedef_ `typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive;`
- L608 _function_ `int LZ4_versionNumber (void)` — Local Utils
- L609 _function_ `const char* LZ4_versionString(void)`
- L610 _function_ `int LZ4_compressBound(int isize)`
- L611 _function_ `int LZ4_sizeofState()`
- L650 _function_ `static U32 LZ4_hash5(U64 sequence, tableType_t const tableType)`
- L662 _function_ `LZ4_FORCE_INLINE U32 LZ4_hashPosition(const void* const p, tableType_t const tableType)`
- L668 _function_ `static void LZ4_clearHash(U32 h, void* tableBase, tableType_t const tableType)`
- L680 _function_ `static void LZ4_putIndexOnHash(U32 idx, U32 h, void* tableBase, tableType_t const tableType)`
- L692 _function_ `static void LZ4_putPositionOnHash(const BYTE* p, U32 h, void* tableBase, tableType_t const tableType, const BYTE* srcBase)`
- L705 _function_ `LZ4_FORCE_INLINE void LZ4_putPosition(const BYTE* p, void* tableBase, tableType_t tableType, const BYTE* srcBase)`
- L717 _function_ `static U32 LZ4_getIndexOnHash(U32 h, const void* tableBase, tableType_t tableType)` — LZ4_getIndexOnHash() : Index of match position registered in hash table. hash position must be calculated by using base+index, or dictBase+index. Assumption 1 : only valid if tableType == byU32 or byU16. Assumption 2 : h is presumed valid (within limits of hash table)
- L733 _function_ `static const BYTE* LZ4_getPositionOnHash(U32 h, const void* tableBase, tableType_t tableType, const BYTE* srcBase)`
- L741 _function_ `LZ4_getPosition(const BYTE* p, const void* tableBase, tableType_t tableType, const BYTE* srcBase)`
- L750 _function_ `LZ4_prepareTable(LZ4_stream_t_internal* const cctx, const int inputSize, const tableType_t tableType)`
- L800 _function_ `LZ4_FORCE_INLINE int LZ4_compress_generic( LZ4_stream_t_internal* const cctx, const char* const source, char* const dest, const int inputSize, int *inputConsumed, const int maxOutputSize, const limitedOutput_directive outputDirective, const tableType_t tableType, const dict_directive dictDirective, const dictIssue_directive dictIssue, const int acceleration)` — LZ4_compress_generic() : inlined, to ensure branches are decided at compilation time
- L1191 _function_ `int LZ4_compress_fast_extState(void* state, const char* source, char* dest, int inputSize, int maxOutputSize, int acceleration)`
- L1222 _function_ `int LZ4_compress_fast_extState_fastReset(void* state, const char* src, char* dst, int srcSize, int dstCapacity, int acceleration)` — LZ4_compress_fast_extState_fastReset() : A variant of LZ4_compress_fast_extState(). Using this variant avoids an expensive initialization step. It is only safe to call if the state buffer is known to be correctly initialized already (see comment in lz4.h on LZ4_resetStream_fast() for a definition of "correctly initialized").
- L1259 _function_ `int LZ4_compress_fast(const char* source, char* dest, int inputSize, int maxOutputSize, int acceleration)`
- L1278 _function_ `int LZ4_compress_default(const char* src, char* dst, int srcSize, int maxOutputSize)`
- L1286 _function_ `int LZ4_compress_fast_force(const char* src, char* dst, int srcSize, int dstCapacity, int acceleration)` — strangely enough, gcc generates faster code when this function is uncommented, even if unused
- L1303 _function_ `static int LZ4_compress_destSize_extState (LZ4_stream_t* state, const char* src, char* dst, int* srcSizePtr, int targetDstSize)` — Note!: This function leaves the stream in an unclean/broken state! It is not safe to subsequently use the same state with a _fastReset() or _continue() call without resetting it.
- L1320 _function_ `int LZ4_compress_destSize(const char* src, char* dst, int* srcSizePtr, int targetDstSize)`
- L1344 _function_ `LZ4_stream_t* LZ4_createStream(void)`
- L1357 _function_ `static size_t LZ4_stream_t_alignment(void)` — #ifndef _MSC_VER    for some reason, Visual fails the aligment test on 32-bit x86 : it reports an aligment of 8-bytes, while actually aligning LZ4_stream_t on 4 bytes.
- L1359 _member_ `struct { char c; LZ4_stream_t t; } t_a;` (scope `LZ4_stream_t_alignment::__anon79d69c360708`)
- L1359 _member_ `struct { char c; LZ4_stream_t t; } t_a;` (scope `LZ4_stream_t_alignment::__anon79d69c360708`)
- L1364 _function_ `LZ4_stream_t* LZ4_initStream (void* buffer, size_t size)`
- L1380 _function_ `void LZ4_resetStream (LZ4_stream_t* LZ4_stream)` — resetStream is now deprecated, prefer initStream() which is more general
- L1386 _function_ `void LZ4_resetStream_fast(LZ4_stream_t* ctx)`
- L1390 _function_ `int LZ4_freeStream (LZ4_stream_t* LZ4_stream)`
- L1399 _macro_ `#define HASH_UNIT sizeof(reg_t)`
- L1400 _function_ `int LZ4_loadDict (LZ4_stream_t* LZ4_dict, const char* dictionary, int dictSize)`
- L1442 _function_ `void LZ4_attach_dictionary(LZ4_stream_t* workingStream, const LZ4_stream_t* dictionaryStream)`
- L1476 _function_ `static void LZ4_renormDictT(LZ4_stream_t_internal* LZ4_dict, int nextSize)`
- L1496 _function_ `int LZ4_compress_fast_continue (LZ4_stream_t* LZ4_stream, const char* source, char* dest, int inputSize, int maxOutputSize, int acceleration)`
- L1572 _function_ `int LZ4_compress_forceExtDict (LZ4_stream_t* LZ4_dict, const char* source, char* dest, int srcSize)` — Hidden debug function, to force-test external dictionary mode
- L1599 _function_ `int LZ4_saveDict (LZ4_stream_t* LZ4_dict, char* safeBuffer, int dictSize)` — LZ4_saveDict() : If previously compressed data block is not guaranteed to remain available at its memory location, save it into a safer place (char* safeBuffer). Note : you don't need to call LZ4_loadDict() afterwards, dictionary is immediately usable, you can therefore call LZ4_compress_fast_continue(). Return : saved dictionary size in bytes (necessarily <= dictSize), or 0 if error.
- L1621 _enumerator_ `typedef enum { endOnOutputSize = 0, endOnInputSize = 1 } endCondition_directive; typedef enum { decode_full_block = 0, partial_decode = 1 } earlyEnd_directive; #undef MIN #define MIN(a,b) ( (a) < (b) ? (a) : (b) ) /* Read the variable-length literal or match length. *` (scope `__anon79d69c360803`)
- L1621 _enumerator_ `typedef enum { endOnOutputSize = 0, endOnInputSize = 1 } endCondition_directive; typedef enum { decode_full_block = 0, partial_decode = 1 } earlyEnd_directive; #undef MIN #define MIN(a,b) ( (a) < (b) ? (a) : (b) ) /* Read the variable-length literal or match length. *` (scope `__anon79d69c360803`)
- L1621 _typedef_ `typedef enum { endOnOutputSize = 0, endOnInputSize = 1 } endCondition_directive;`
- L1622 _enumerator_ `typedef enum { decode_full_block = 0, partial_decode = 1 } earlyEnd_directive; #undef MIN #define MIN(a,b) ( (a) < (b) ? (a) : (b) ) /* Read the variable-length literal or match length. * * ip - pointer to use as input.` (scope `__anon79d69c360903`)
- L1622 _enumerator_ `typedef enum { decode_full_block = 0, partial_decode = 1 } earlyEnd_directive; #undef MIN #define MIN(a,b) ( (a) < (b) ? (a) : (b) ) /* Read the variable-length literal or match length. * * ip - pointer to use as input.` (scope `__anon79d69c360903`)
- L1622 _typedef_ `typedef enum { decode_full_block = 0, partial_decode = 1 } earlyEnd_directive;`
- L1625 _macro_ `#define MIN(a,b) ( (a) < (b) ? (a) : (b) )`
- L1636 _enumerator_ `typedef enum { loop_error = -2, initial_error = -1, length_ok = 0 } variable_length_error; LZ4_FORCE_INLINE unsigned read_variable_length(const BYTE**ip, const BYTE* lencheck, int loop_check, int initial_check, variable_length_error* error) { unsigned length = 0; unsigned s; if (initial_check && unlikely((*ip) >= lencheck)) {` (scope `__anon79d69c360a03`) — BEGIN EPIC MOD : The 'ok' identifier collides with symbols in the MacOS SDK
- L1636 _enumerator_ `typedef enum { loop_error = -2, initial_error = -1, length_ok = 0 } variable_length_error; LZ4_FORCE_INLINE unsigned read_variable_length(const BYTE**ip, const BYTE* lencheck, int loop_check, int initial_check, variable_length_error* error) { unsigned length = 0; unsigned s; if (initial_check && unlikely((*ip) >= lencheck)) {` (scope `__anon79d69c360a03`) — BEGIN EPIC MOD : The 'ok' identifier collides with symbols in the MacOS SDK
- L1636 _enumerator_ `typedef enum { loop_error = -2, initial_error = -1, length_ok = 0 } variable_length_error; LZ4_FORCE_INLINE unsigned read_variable_length(const BYTE**ip, const BYTE* lencheck, int loop_check, int initial_check, variable_length_error* error) { unsigned length = 0; unsigned s; if (initial_check && unlikely((*ip) >= lencheck)) {` (scope `__anon79d69c360a03`) — BEGIN EPIC MOD : The 'ok' identifier collides with symbols in the MacOS SDK
- L1636 _typedef_ `typedef enum { loop_error = -2, initial_error = -1, length_ok = 0 } variable_length_error;` — BEGIN EPIC MOD : The 'ok' identifier collides with symbols in the MacOS SDK
- L1639 _function_ `read_variable_length(const BYTE**ip, const BYTE* lencheck, int loop_check, int initial_check, variable_length_error* error)`
- L1667 _function_ `LZ4_decompress_generic( const char* const src, char* const dst, int srcSize, int outputSize, endCondition_directive endOnInput, earlyEnd_directive partialDecoding, dict_directive dict, const BYTE* const lowPrefix, const BYTE* const dictStart, const size_t dictSize )`
- L2099 _function_ `int LZ4_decompress_safe(const char* source, char* dest, int compressedSize, int maxDecompressedSize)`
- L2107 _function_ `int LZ4_decompress_safe_partial(const char* src, char* dst, int compressedSize, int targetOutputSize, int dstCapacity)`
- L2116 _function_ `int LZ4_decompress_fast(const char* source, char* dest, int originalSize)`
- L2126 _function_ `int LZ4_decompress_safe_withPrefix64k(const char* source, char* dest, int compressedSize, int maxOutputSize)` — LZ4_FORCE_O2_GCC_PPC64LE   Exported, an obsolete API function.
- L2134 _function_ `int LZ4_decompress_fast_withPrefix64k(const char* source, char* dest, int originalSize)` — Another obsolete API function, paired with the previous one.
- L2142 _function_ `static int LZ4_decompress_safe_withSmallPrefix(const char* source, char* dest, int compressedSize, int maxOutputSize, size_t prefixSize)`
- L2151 _function_ `int LZ4_decompress_safe_forceExtDict(const char* source, char* dest, int compressedSize, int maxOutputSize, const void* dictStart, size_t dictSize)`
- L2161 _function_ `static int LZ4_decompress_fast_extDict(const char* source, char* dest, int originalSize, const void* dictStart, size_t dictSize)`
- L2174 _function_ `int LZ4_decompress_safe_doubleDict(const char* source, char* dest, int compressedSize, int maxOutputSize, size_t prefixSize, const void* dictStart, size_t dictSize)`
- L2183 _function_ `int LZ4_decompress_fast_doubleDict(const char* source, char* dest, int originalSize, size_t prefixSize, const void* dictStart, size_t dictSize)`
- L2193 _function_ `LZ4_streamDecode_t* LZ4_createStreamDecode(void)`
- L2200 _function_ `int LZ4_freeStreamDecode (LZ4_streamDecode_t* LZ4_stream)`
- L2213 _function_ `int LZ4_setStreamDecode (LZ4_streamDecode_t* LZ4_streamDecode, const char* dictionary, int dictSize)` — LZ4_setStreamDecode() : Use this function to instruct where to find the dictionary. This function is not necessary if previous data is still available where it was decoded. Loading a size of 0 is allowed (same effect as no dictionary). @return : 1 if OK, 0 if error
- L2234 _function_ `int LZ4_decoderRingBufferSize(int maxBlockSize)` — LZ4_decoderRingBufferSize() : when setting a ring buffer for streaming decompression (optional scenario), provides the minimum size of this ring buffer to be compatible with any source respecting maxBlockSize condition. Note : in a ring buffer scenario, blocks are presumed decompressed next to each other. When not enough space remains for next block (remainingSize < maxBlockSize), decoding resumes from beginning of ring buffer. @return : minimum ring buffer size, or 0 if there is an error (invalid maxBlockSize).
- L2250 _function_ `int LZ4_decompress_safe_continue (LZ4_streamDecode_t* LZ4_streamDecode, const char* source, char* dest, int compressedSize, int maxOutputSize)`
- L2290 _function_ `int LZ4_decompress_fast_continue (LZ4_streamDecode_t* LZ4_streamDecode, const char* source, char* dest, int originalSize)`
- L2332 _function_ `int LZ4_decompress_safe_usingDict(const char* source, char* dest, int compressedSize, int maxOutputSize, const char* dictStart, int dictSize)`
- L2347 _function_ `int LZ4_decompress_fast_usingDict(const char* source, char* dest, int originalSize, const char* dictStart, int dictSize)`
- L2360 _function_ `int LZ4_compress_limitedOutput(const char* source, char* dest, int inputSize, int maxOutputSize)` — obsolete compression functions
- L2364 _function_ `int LZ4_compress(const char* src, char* dest, int srcSize)`
- L2368 _function_ `int LZ4_compress_limitedOutput_withState (void* state, const char* src, char* dst, int srcSize, int dstSize)`
- L2372 _function_ `int LZ4_compress_withState (void* state, const char* src, char* dst, int srcSize)`
- L2376 _function_ `int LZ4_compress_limitedOutput_continue (LZ4_stream_t* LZ4_stream, const char* src, char* dst, int srcSize, int dstCapacity)`
- L2380 _function_ `int LZ4_compress_continue (LZ4_stream_t* LZ4_stream, const char* source, char* dest, int inputSize)`
- L2391 _function_ `int LZ4_uncompress (const char* source, char* dest, int outputSize)` — These decompression functions are deprecated and should no longer be used. They are only provided here for compatibility with older user programs. - LZ4_uncompress is totally equivalent to LZ4_decompress_fast - LZ4_uncompress_unknownOutputSize is totally equivalent to LZ4_decompress_safe
- L2395 _function_ `int LZ4_uncompress_unknownOutputSize (const char* source, char* dest, int isize, int maxOutputSize)`
- L2402 _function_ `int LZ4_sizeofStreamState()`
- L2404 _function_ `int LZ4_resetStreamState(void* state, char* inputBuffer)`
- L2411 _function_ `void* LZ4_create (char* inputBuffer)`
- L2417 _function_ `char* LZ4_slideInputBuffer (void* state)`

### `Source/Runtime/TraceLog/Private/Trace/LZ4/lz4.h` (Private)


#### struct `LZ4_stream_t_internal`  
`struct LZ4_stream_t_internal`  
_L587-595_
- L588 _public member_ `uint32_t hashTable[LZ4_HASH_SIZE_U32];`
- L589 _public member_ `uint32_t currentOffset;`
- L590 _public member_ `uint16_t dirty;`
- L591 _public member_ `uint16_t tableType;`
- L592 _public member_ `const uint8_t* dictionary;`
- L593 _public member_ `const LZ4_stream_t_internal* dictCtx;`
- L594 _public member_ `uint32_t dictSize;`

#### struct `(anonymous)`  
`typedef struct`  
_L597-602_

#### union `LZ4_stream_u`  
`union LZ4_stream_u`  
_L637-640_
- L638 _public member_ `unsigned long long table[LZ4_STREAMSIZE_U64];`
- L639 _public member_ `LZ4_stream_t_internal internal_donotuse;`

#### union `LZ4_streamDecode_u`  
`union LZ4_streamDecode_u`  
_L668-671_
- L669 _public member_ `unsigned long long table[LZ4_STREAMDECODESIZE_U64];`
- L670 _public member_ `LZ4_streamDecode_t_internal internal_donotuse;`

#### Free symbols / members of external scopes

- L44 _macro_ `# define LZ4_BEGIN_NAMESPACE extern "C++" { namespace LZ4_NAMESPACE {`
- L45 _macro_ `# define LZ4_END_NAMESPACE } /* extern */ } /* namespace */`
- L53 _macro_ `#define LZ4_H_2983827168210`
- L100 _macro_ `# define LZ4LIB_VISIBILITY __attribute__ ((visibility ("default")))`
- L106 _macro_ `# define LZ4LIB_API __declspec(dllexport) LZ4LIB_VISIBILITY`
- L114 _macro_ `#define LZ4_VERSION_MAJOR 1 /* for breaking interface changes */` — ------   Version   ------
- L115 _macro_ `#define LZ4_VERSION_MINOR 9 /* for new (non-breaking) interface capabilities */` — #define LZ4_VERSION_MAJOR    1      for breaking interface changes
- L116 _macro_ `#define LZ4_VERSION_RELEASE 2 /* for tweaks, bug-fixes, or development */` — #define LZ4_VERSION_MINOR    9      for new (non-breaking) interface capabilities
- L118 _macro_ `#define LZ4_VERSION_NUMBER (LZ4_VERSION_MAJOR *100*100 + LZ4_VERSION_MINOR *100 + LZ4_VERSION_RELEASE)`
- L120 _macro_ `#define LZ4_LIB_VERSION LZ4_VERSION_MAJOR.LZ4_VERSION_MINOR.LZ4_VERSION_RELEASE`
- L121 _macro_ `#define LZ4_QUOTE(str) #str`
- L122 _macro_ `#define LZ4_EXPAND_AND_QUOTE(str) LZ4_QUOTE(str)`
- L123 _macro_ `#define LZ4_VERSION_STRING LZ4_EXPAND_AND_QUOTE(LZ4_LIB_VERSION)`
- L127 _prototype_ `int LZ4_versionNumber (void);`
- L128 _prototype_ `const char* LZ4_versionString (void);` — LZ4LIB_API int LZ4_versionNumber (void);   < library version number; useful to check dll version
- L142 _macro_ `# define LZ4_MEMORY_USAGE 14`
- L163 _prototype_ `int LZ4_compress_default(const char* src, char* dst, int srcSize, int dstCapacity);` — LZ4_compress_default() : Compresses 'srcSize' bytes from buffer 'src' into already allocated 'dst' buffer of size 'dstCapacity'. Compression is guaranteed to succeed if 'dstCapacity' >= LZ4_compressBound(srcSize). It also runs faster, so it's a recommended setting. If the function cannot compress 'src' into a more limited 'dst' budget, compression stops *immediately*, and the function result is zero. In which case, 'dst' content is undefined (invalid). srcSize : max supported value is LZ4_MAX_INPUT_SIZE. dstCapacity : size of buffer 'dst' (which must be already allocated) @return  : the number of bytes written into buffer 'dst' (necessarily <= dstCapacity) or 0 if compression fails Note : This function is protected against buffer overflow scenarios (never writes outside 'dst' buffer, nor read outside 'source' buffer).
- L179 _prototype_ `int LZ4_decompress_safe (const char* src, char* dst, int compressedSize, int dstCapacity);` — LZ4_decompress_safe() : compressedSize : is the exact complete size of the compressed block. dstCapacity : is the size of destination buffer (which must be already allocated), presumed an upper bound of decompressed size. @return : the number of bytes decompressed into destination buffer (necessarily <= dstCapacity) If destination buffer is not large enough, decoding will stop and output an error code (negative value). If the source stream is detected malformed, the function will stop decoding and return a negative result. Note 1 : This function is protected against malicious data packets : it will never writes outside 'dst' buffer, nor read outside 'source' buffer, even if the compressed block is maliciously modified to order the decoder to do these actions. In such case, the decoder stops immediately, and considers the compressed block malformed. Note 2 : compressedSize and dstCapacity must be provided to the function, the compressed block does not contain them. The implementation is free to send / store / derive this information in whichever way is most beneficial. If there is a need for a different format which bundles together both compressed data and its metadata, consider looking at lz4frame.h instead.
- L185 _macro_ `#define LZ4_MAX_INPUT_SIZE 0x7E000000 /* 2 113 929 216 bytes */` — Advanced Functions
- L186 _macro_ `#define LZ4_COMPRESSBOUND(isize) ((unsigned)(isize) > (unsigned)LZ4_MAX_INPUT_SIZE ? 0 : (isize) + ((isize)/255) + 16)` — #define LZ4_MAX_INPUT_SIZE        0x7E000000     2 113 929 216 bytes
- L197 _prototype_ `int LZ4_compressBound(int inputSize);` — LZ4_compressBound() : Provides the maximum size that LZ4 compression may output in a "worst case" scenario (input data not compressible) This function is primarily useful for memory allocation purposes (destination buffer size). Macro LZ4_COMPRESSBOUND() is also provided for compilation-time evaluation (stack memory allocation for example). Note that LZ4_compress_default() compresses faster when dstCapacity is >= LZ4_compressBound(srcSize) inputSize  : max supported value is LZ4_MAX_INPUT_SIZE return : maximum output size in a "worst case" scenario or 0, if input size is incorrect (too large or negative)
- L206 _prototype_ `int LZ4_compress_fast (const char* src, char* dst, int srcSize, int dstCapacity, int acceleration);` — LZ4_compress_fast() : Same as LZ4_compress_default(), but allows selection of "acceleration" factor. The larger the acceleration value, the faster the algorithm, but also the lesser the compression. It's a trade-off. It can be fine tuned, with each successive value providing roughly +~3% to speed. An acceleration value of "1" is the same as regular LZ4_compress_default() Values <= 0 will be replaced by ACCELERATION_DEFAULT (currently == 1, see lz4.c).
- L215 _prototype_ `int LZ4_sizeofState(void);` — LZ4_compress_fast_extState() : Same as LZ4_compress_fast(), using an externally allocated memory space for its state. Use LZ4_sizeofState() to know how much memory must be allocated, and allocate it on 8-bytes boundaries (using `malloc()` typically). Then, provide this buffer as `void* state` to compression function.
- L216 _prototype_ `int LZ4_compress_fast_extState (void* state, const char* src, char* dst, int srcSize, int dstCapacity, int acceleration);`
- L231 _prototype_ `int LZ4_compress_destSize (const char* src, char* dst, int* srcSizePtr, int targetDstSize);` — LZ4_compress_destSize() : Reverse the logic : compresses as much data as possible from 'src' buffer into already allocated buffer 'dst', of size >= 'targetDestSize'. This function either compresses the entire 'src' content into 'dst' if it's large enough, or fill 'dst' buffer completely with as much data as possible from 'src'. note: acceleration parameter is fixed to "default". *srcSizePtr : will be modified to indicate how many bytes where read from 'src' to fill 'dst'. New value is necessarily <= input value. @return : Nb bytes written into 'dst' (necessarily <= targetDestSize) or 0 if compression fails.
- L258 _prototype_ `int LZ4_decompress_safe_partial (const char* src, char* dst, int srcSize, int targetOutputSize, int dstCapacity);` — LZ4_decompress_safe_partial() : Decompress an LZ4 compressed block, of size 'srcSize' at position 'src', into destination buffer 'dst' of size 'dstCapacity'. Up to 'targetOutputSize' bytes will be decoded. The function stops decoding on reaching this objective, which can boost performance when only the beginning of a block is required. @return : the number of bytes decoded in `dst` (necessarily <= dstCapacity) If source stream is detected malformed, function returns a negative result. Note : @return can be < targetOutputSize, if compressed block contains less data. Note 2 : this function features 2 parameters, targetOutputSize and dstCapacity, and expects targetOutputSize <= dstCapacity. It effectively stops decoding on reaching targetOutputSize, so dstCapacity is kind of redundant. This is because in a previous version of this function, decoding operation would not "break" a sequence in the middle. As a consequence, there was no guarantee that decoding would stop at exactly targetOutputSize, it could write more bytes, though only up to dstCapacity. Some "margin" used to be required for this operation to work properly. This is no longer necessary. The function nonetheless keeps its signature, in an effort to not break API.
- L264 _typedef_ `typedef union LZ4_stream_u LZ4_stream_t;` — Streaming Compression Functions
- L266 _prototype_ `LZ4_stream_t* LZ4_createStream(void);`
- L267 _prototype_ `int LZ4_freeStream (LZ4_stream_t* streamPtr);`
- L291 _prototype_ `void LZ4_resetStream_fast (LZ4_stream_t* streamPtr);` — LZ4_resetStream_fast() : v1.9.0+ Use this to prepare an LZ4_stream_t for a new chain of dependent blocks (e.g., LZ4_compress_fast_continue()). An LZ4_stream_t must be initialized once before usage. This is automatically done when created by LZ4_createStream(). However, should the LZ4_stream_t be simply declared on stack (for example), it's necessary to initialize it first, using LZ4_initStream(). After init, start any new stream with LZ4_resetStream_fast(). A same LZ4_stream_t can be re-used multiple times consecutively and compress multiple streams, provided that it starts each new stream with LZ4_resetStream_fast(). LZ4_resetStream_fast() is much faster than LZ4_initStream(), but is not compatible with memory regions containing garbage data. Note: it's only useful to call LZ4_resetStream_fast() in the context of streaming compression. The *extState* functions perform their own resets. Invoking LZ4_resetStream_fast() before is redundant, and even counterproductive.
- L304 _prototype_ `int LZ4_loadDict (LZ4_stream_t* streamPtr, const char* dictionary, int dictSize);` — LZ4_loadDict() : Use this function to reference a static dictionary into LZ4_stream_t. The dictionary must remain available during compression. LZ4_loadDict() triggers a reset, so any previous data will be forgotten. The same dictionary will have to be loaded on decompression side for successful decoding. Dictionary are useful for better compression of small data (KB range). While LZ4 accept any input as dictionary, results are generally better when using Zstandard's Dictionary Builder. Loading a size of 0 is allowed, and is the same as reset. @return : loaded dictionary size, in bytes (necessarily <= 64 KB)
- L329 _prototype_ `int LZ4_compress_fast_continue (LZ4_stream_t* streamPtr, const char* src, char* dst, int srcSize, int dstCapacity, int acceleration);` — LZ4_compress_fast_continue() : Compress 'src' content using data from previously compressed blocks, for better compression ratio. 'dst' buffer must be already allocated. If dstCapacity >= LZ4_compressBound(srcSize), compression is guaranteed to succeed, and runs faster. @return : size of compressed block or 0 if there is an error (typically, cannot fit into 'dst'). Note 1 : Each invocation to LZ4_compress_fast_continue() generates a new block. Each block has precise boundaries. Each block must be decompressed separately, calling LZ4_decompress_*() with relevant metadata. It's not possible to append blocks together and expect a single invocation of LZ4_decompress_*() to decompress them together. Note 2 : The previous 64KB of source data is __assumed__ to remain present, unmodified, at same address in memory ! Note 3 : When input is structured as a double-buffer, each buffer can have any size, including < 64 KB. Make sure that buffers are separated, by at least one byte. This construction ensures that each block only depends on previous block. Note 4 : If input buffer is a ring-buffer, it can have any size, including < 64 KB. Note 5 : After an error, the stream status is undefined (invalid), it can only be reset or freed.
- L338 _prototype_ `int LZ4_saveDict (LZ4_stream_t* streamPtr, char* safeBuffer, int maxDictSize);` — LZ4_saveDict() : If last 64KB data cannot be guaranteed to remain available at its current memory location, save it into a safer place (char* safeBuffer). This is schematically equivalent to a memcpy() followed by LZ4_loadDict(), but is much faster, because LZ4_saveDict() doesn't need to rebuild tables. @return : saved dictionary size in bytes (necessarily <= maxDictSize), or 0 if error.
- L345 _typedef_ `typedef union LZ4_streamDecode_u LZ4_streamDecode_t;` — Streaming Decompression Functions Bufferless synchronous API
- L351 _prototype_ `LZ4_streamDecode_t* LZ4_createStreamDecode(void);` — LZ4_createStreamDecode() and LZ4_freeStreamDecode() : creation / destruction of streaming decompression tracking context. A tracking context can be re-used multiple times.
- L352 _prototype_ `int LZ4_freeStreamDecode (LZ4_streamDecode_t* LZ4_stream);`
- L361 _prototype_ `int LZ4_setStreamDecode (LZ4_streamDecode_t* LZ4_streamDecode, const char* dictionary, int dictSize);` — LZ4_setStreamDecode() : An LZ4_streamDecode_t context can be allocated once and re-used multiple times. Use this function to start decompression of a new stream of blocks. A dictionary can optionally be set. Use NULL or size 0 for a reset order. Dictionary is presumed stable : it must remain accessible and unmodified during next decompression. @return : 1 if OK, 0 if error
- L374 _prototype_ `int LZ4_decoderRingBufferSize(int maxBlockSize);` — LZ4_decoderRingBufferSize() : v1.8.2+ Note : in a ring buffer scenario (optional), blocks are presumed decompressed next to each other up to the moment there is not enough remaining space for next block (remainingSize < maxBlockSize), at which stage it resumes from beginning of ring buffer. When setting such a ring buffer for streaming decompression, provides the minimum size of this ring buffer to be compatible with any source respecting maxBlockSize condition. @return : minimum ring buffer size, or 0 if there is an error (invalid maxBlockSize).
- L375 _macro_ `#define LZ4_DECODER_RING_BUFFER_SIZE(maxBlockSize) (65536 + 14 + (maxBlockSize)) /* for static allocation; maxBlockSize presumed valid */`
- L402 _prototype_ `int LZ4_decompress_safe_continue (LZ4_streamDecode_t* LZ4_streamDecode, const char* src, char* dst, int srcSize, int dstCapacity);` — LZ4_decompress_*_continue() : These decoding functions allow decompression of consecutive blocks in "streaming" mode. A block is an unsplittable entity, it must be presented entirely to a decompression function. Decompression functions only accepts one block at a time. The last 64KB of previously decoded data *must* remain available and unmodified at the memory position where they were decoded. If less than 64KB of data has been decoded, all the data must be present. Special : if decompression side sets a ring buffer, it must respect one of the following conditions : - Decompression buffer size is _at least_ LZ4_decoderRingBufferSize(maxBlockSize). maxBlockSize is the maximum size of any single block. It can have any value > 16 bytes. In which case, encoding and decoding buffers do not need to be synchronized. Actually, data can be produced by any source compliant with LZ4 format specification, and respecting maxBlockSize. - Synchronized mode : Decompression buffer size is _exactly_ the same as compression buffer size, and follows exactly same update rule (block boundaries at same positions), and decoding function is provided with exact decompressed size of each block (exception for last block of the stream), _then_ decoding & encoding ring buffer can have any size, including small ones ( < 64 KB). - Decompression buffer is larger than encoding buffer, by a minimum of maxBlockSize more bytes. In which case, encoding and decoding buffers do not need to be synchronized, and enc
- L413 _prototype_ `int LZ4_decompress_safe_usingDict (const char* src, char* dst, int srcSize, int dstCapcity, const char* dictStart, int dictSize);` — LZ4_decompress_*_usingDict() : These decoding functions work the same as a combination of LZ4_setStreamDecode() followed by LZ4_decompress_*_continue() They are stand-alone, and don't need an LZ4_streamDecode_t structure. Dictionary is presumed stable : it must remain accessible and unmodified during decompression. Performance tip : Decompression speed can be substantially increased when dst == dictStart + dictSize.
- L447 _macro_ `#define LZ4_STATIC_3504398509`
- L450 _macro_ `#define LZ4LIB_STATIC_API LZ4LIB_API`
- L468 _prototype_ `int LZ4_compress_fast_extState_fastReset (void* state, const char* src, char* dst, int srcSize, int dstCapacity, int acceleration);` — LZ4_compress_fast_extState_fastReset() : A variant of LZ4_compress_fast_extState(). Using this variant avoids an expensive initialization step. It is only safe to call if the state buffer is known to be correctly initialized already (see above comment on LZ4_resetStream_fast() for a definition of "correctly initialized"). From a high level, the difference is that this function initializes the provided state with a call to something like LZ4_resetStream_fast() while LZ4_compress_fast_extState() starts with a call to LZ4_resetStream().
- L496 _prototype_ `void LZ4_attach_dictionary(LZ4_stream_t* workingStream, const LZ4_stream_t* dictionaryStream);` — LZ4_attach_dictionary() : This is an experimental API that allows efficient use of a static dictionary many times. Rather than re-loading the dictionary buffer into a working context before each compression, or copying a pre-loaded dictionary's LZ4_stream_t into a working LZ4_stream_t, this function introduces a no-copy setup mechanism, in which the working stream references the dictionary stream in-place. Several assumptions are made about the state of the dictionary stream. Currently, only streams which have been prepared by LZ4_loadDict() should be expected to work. Alternatively, the provided dictionaryStream may be NULL, in which case any existing dictionary stream is unset. If a dictionary is provided, it replaces any pre-existing stream history. The dictionary contents are the only history that can be referenced and logically immediately precede the data compressed in the first subsequent compression call. The dictionary will only remain attached to the working stream through the first compression call, at the end of which it is cleared. The dictionary stream (and source buffer) must remain in-place / accessible / unchanged through the completion of the first compression call on the stream.
- L550 _macro_ `#define LZ4_DECOMPRESS_INPLACE_MARGIN(compressedSize) (((compressedSize) >> 8) + 32)`
- L551 _macro_ `#define LZ4_DECOMPRESS_INPLACE_BUFFER_SIZE(decompressedSize) ((decompressedSize) + LZ4_DECOMPRESS_INPLACE_MARGIN(decompressedSize)) /**< note: presumes that compressedSize < decompressedSize. note2: margin is overestimated a bit, since it c`
- L554 _macro_ `# define LZ4_DISTANCE_MAX 65535 /* set to maximum value by default */` — #ifndef LZ4_DISTANCE_MAX     history window size; can be user-defined at compile time
- L557 _macro_ `#define LZ4_COMPRESS_INPLACE_MARGIN (LZ4_DISTANCE_MAX + 32) /* LZ4_DISTANCE_MAX can be safely replaced by srcSize when it's smaller */`
- L558 _macro_ `#define LZ4_COMPRESS_INPLACE_BUFFER_SIZE(maxCompressedSize) ((maxCompressedSize) + LZ4_COMPRESS_INPLACE_MARGIN) /**< maxCompressedSize is generally LZ4_COMPRESSBOUND(inputSize), but can be set to any lower value, with the risk that compress` — #define LZ4_COMPRESS_INPLACE_MARGIN                           (LZ4_DISTANCE_MAX + 32)     LZ4_DISTANCE_MAX can be safely replaced by srcSize when it's smaller
- L568 _macro_ `#define LZ4_H_98237428734687`
- L577 _macro_ `#define LZ4_HASHLOG (LZ4_MEMORY_USAGE-2)` — PRIVATE DEFINITIONS Do not use these definitions directly. They are only exposed to allow static allocation of `LZ4_stream_t` and `LZ4_streamDecode_t`. Accessing members will expose code to API and/or ABI break in future versions of the library.
- L578 _macro_ `#define LZ4_HASHTABLESIZE (1 << LZ4_MEMORY_USAGE)`
- L579 _macro_ `#define LZ4_HASH_SIZE_U32 (1 << LZ4_HASHLOG) /* required as macro for static allocation */`
- L586 _typedef_ `typedef struct LZ4_stream_t_internal LZ4_stream_t_internal;`
- L598 _member_ `const uint8_t* externalDict;` (scope `__anonf70b9b0a0108`)
- L599 _member_ `size_t extDictSize;` (scope `__anonf70b9b0a0108`)
- L600 _member_ `const uint8_t* prefixEnd;` (scope `__anonf70b9b0a0108`)
- L601 _member_ `size_t prefixSize;` (scope `__anonf70b9b0a0108`)
- L602 _typedef_ `} LZ4_streamDecode_t_internal;`
- L635 _macro_ `#define LZ4_STREAMSIZE_U64 ((1 << (LZ4_MEMORY_USAGE-3)) + 4 + ((sizeof(void*)==16) ? 4 : 0) /*AS-400*/ )` — LZ4_stream_t : information structure to track an LZ4 stream. LZ4_stream_t can also be created using LZ4_createStream(), which is recommended. The structure definition can be convenient for static allocation (on stack, or as part of larger structure). Init this structure with LZ4_initStream() before first use. note : only use this definition in association with static linking ! this definition is not API/ABI safe, and may change in a future version.
- L636 _macro_ `#define LZ4_STREAMSIZE (LZ4_STREAMSIZE_U64 * sizeof(unsigned long long))`
- L656 _prototype_ `LZ4_stream_t* LZ4_initStream (void* buffer, size_t size);` — LZ4_initStream() : v1.9.0+ An LZ4_stream_t structure must be initialized at least once. This is automatically done when invoking LZ4_createStream(), but it's not when the structure is simply declared on stack (for example). Use LZ4_initStream() to properly initialize a newly declared LZ4_stream_t. It can also initialize any arbitrary buffer of sufficient size, and will @return a pointer of proper type upon initialization. Note : initialization fails if size and alignment conditions are not respected. In which case, the function will @return NULL. Note2: An LZ4_stream_t structure guarantees correct alignment and size. Note3: Before v1.9.0, use LZ4_resetStream() instead
- L666 _macro_ `#define LZ4_STREAMDECODESIZE_U64 (4 + ((sizeof(void*)==16) ? 2 : 0) /*AS-400*/ )` — LZ4_streamDecode_t : information structure to track an LZ4 stream during decompression. init this structure  using LZ4_setStreamDecode() before first use. note : only use in association with static linking ! this definition is not API/ABI safe, and may change in a future version !
- L667 _macro_ `#define LZ4_STREAMDECODESIZE (LZ4_STREAMDECODESIZE_U64 * sizeof(unsigned long long))`
- L691 _macro_ `# define LZ4_DEPRECATED(message) /* disable deprecation warnings */`
- L693 _macro_ `# define LZ4_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)`
- L695 _macro_ `# define LZ4_DEPRECATED(message) [[deprecated(message)]]` — #  if defined (__cplusplus) && (__cplusplus >= 201402)   C++14 or greater
- L697 _macro_ `# define LZ4_DEPRECATED(message) __attribute__((deprecated(message)))`
- L699 _macro_ `# define LZ4_DEPRECATED(message) __attribute__((deprecated))`
- L701 _macro_ `# define LZ4_DEPRECATED(message) __declspec(deprecated(message))`
- L704 _macro_ `# define LZ4_DEPRECATED(message)`
- L709 _prototype_ `LZ4_DEPRECATED("use LZ4_compress_default() instead") int LZ4_compress (const ch` — Obsolete compression functions
- L710 _prototype_ `LZ4_DEPRECATED("use LZ4_compress_default() instead") int LZ4_compress_limitedOutput (const char* src, char* dest`
- L711 _prototype_ `LZ4_DEPRECATED("use LZ4_compress_fast_extState() instead") int LZ4_compress_withState (void* state, const c`
- L712 _prototype_ `LZ4_DEPRECATED("use LZ4_compress_fast_extState() instead") int LZ4_compress_limitedOutput_withState (void* state, const char* source, char*`
- L713 _prototype_ `LZ4_DEPRECATED("use LZ4_compress_fast_continue() instead") int LZ4_compress_continue (LZ4_stream_t* LZ4_streamPtr, const c`
- L714 _prototype_ `LZ4_DEPRECATED("use LZ4_compress_fast_continue() instead") int LZ4_compress_limitedOutput_continue (LZ4_stream_t* LZ4_streamPtr, const char* source, char*`
- L717 _prototype_ `LZ4_DEPRECATED("use LZ4_decompress_fast() instead") int LZ4_uncompress (const char* sou` — Obsolete decompression functions
- L718 _prototype_ `LZ4_DEPRECATED("use LZ4_decompress_safe() instead") int LZ4_uncompress_unknownOutputSize (const char* source, char* des`
- L729 _prototype_ `LZ4_DEPRECATED("Use LZ4_createStream() instead") void* L` — Obsolete streaming functions; degraded functionality; do not use! In order to perform streaming compression, these functions depended on data that is no longer tracked in the state. They have been preserved as well as possible: using them will still produce a correct output. However, they don't actually retain any history between compression calls. The compression ratio achieved will therefore be no better than compressing each chunk independently.
- L730 _prototype_ `LZ4_DEPRECATED("Use LZ4_createStream() instead") int`
- L731 _prototype_ `LZ4_DEPRECATED("Use LZ4_resetStream() instead") int LZ4_resetStreamState(voi`
- L732 _prototype_ `LZ4_DEPRECATED("Use LZ4_saveDict() instead") char* LZ4_slide`
- L735 _prototype_ `LZ4_DEPRECATED("use LZ4_decompress_safe_usingDict() instead") int LZ4_decompress_safe_withPrefix64k (const char* src, char` — Obsolete streaming decoding functions
- L736 _prototype_ `LZ4_DEPRECATED("use LZ4_decompress_fast_usingDict() instead") int LZ4_decompress_fast_withPrefix64k (con`
- L767 _prototype_ `int LZ4_decompress_fast (const char* src, char* dst, int originalSize);`
- L769 _prototype_ `int LZ4_decompress_fast_continue (LZ4_streamDecode_t* LZ4_streamDecode, const char* src, char* dst, int originalSize);`
- L771 _prototype_ `int LZ4_decompress_fast_usingDict (const char* src, char* dst, int originalSize, const char* dictStart, int dictSize);`
- L779 _prototype_ `void LZ4_resetStream (LZ4_stream_t* streamPtr);` — LZ4_resetStream() : An LZ4_stream_t structure must be initialized at least once. This is done with LZ4_initStream(), or LZ4_resetStream(). Consider switching to LZ4_initStream(), invoking LZ4_resetStream() will trigger deprecation warnings in the future.

### `Source/Runtime/TraceLog/Private/Trace/Lock.h` (Private)


#### struct `UE::Trace::Private::FLock`  
`struct FLock`  
_L15-54_
- L17 _public function_ `FLock(volatile uint8* InLock) : Lock(InLock)`
- L34 _public function_ `~FLock()`
- L39 _public function_ `double GetTime()`
- L44 _public function_ `bool TimedOut()`
- L50 _public member_ `volatile uint8* Lock;`
- L51 _public member_ `uint64 CyclesPerSecond;`
- L52 _public member_ `double StartSeconds;`
- L53 _public member_ `inline const static double MaxWaitSeconds = 1.0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Trace`)

### `Source/Runtime/TraceLog/Private/Trace/Message.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Trace`)
- L15 _prototype_ `bool GetErrorMessage(char* OutBuffer, uint32 BufferSize, int32 ErrorCode);` (scope `UE::Trace::Private`)
- L21 _macro_ `#define UE_TRACE_MESSAGE_FMT_MAX_SIZE 512`
- L22 _macro_ `#define UE_TRACE_MESSAGE_ERR_MAX_SIZE 256`
- L24 _macro_ `#define UE_TRACE_MESSAGE(Type, Msg) \`
- L27 _macro_ `#define UE_TRACE_MESSAGE_F(Type, Fmt, ...) \`
- L34 _macro_ `#define UE_TRACE_ERRORMESSAGE(Type, ErrorCode)\`
- L41 _macro_ `#define UE_TRACE_ERRORMESSAGE_F(Type, ErrorCode, ContextFmt, ...)\`
- L59 _prototype_ `void Message_SetCallback(UE::Trace::OnMessageFunc* Callback);` (scope `UE::Trace::Private`) — Initialize messages. Saves the provided callback if specified.
- L65 _prototype_ `void Message_Send(EMessageType Type, const char* TypeStr, const char* Description = nullptr);` (scope `UE::Trace::Private`) — Sends a message to the registered callback. Description string is not expected to outlive the function call.

### `Source/Runtime/TraceLog/Private/Trace/Platform.h` (Private)


#### struct `UE::Trace::Private::FProfilerScope`  
`struct FProfilerScope`  
_L75-86_
- L77 _public member_ `static OnScopeBeginFunc* OnScopeBegin;`
- L78 _public member_ `static OnScopeEndFunc* OnScopeEnd;`
- L81 _public function_ `FProfilerScope(const ANSICHAR* Label)`
- L82 _public function_ `~FProfilerScope()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Trace`)
- L15 _prototype_ `UPTRINT ThreadCreate(const ANSICHAR* Name, void (*Entry)());` (scope `UE::Trace::Private`)
- L16 _prototype_ `void ThreadSleep(uint32 Milliseconds);` (scope `UE::Trace::Private`)
- L17 _prototype_ `void ThreadJoin(UPTRINT Handle);` (scope `UE::Trace::Private`)
- L18 _prototype_ `void ThreadDestroy(UPTRINT Handle);` (scope `UE::Trace::Private`)
- L21 _prototype_ `uint64 TimeGetFrequency();` (scope `UE::Trace::Private`)
- L26 _prototype_ `uint64 TimeGetTimestamp();` (scope `UE::Trace::Private`) — Gets the absolute timestamp of the system. @return Absolute timestamp
- L32 _prototype_ `uint64 TimeGetRelativeTimestamp();` (scope `UE::Trace::Private`) — Gets the timestamp (relative to base). If called before Trace initialization value will be zero. @return Timestamp relative base time stamp
- L35 _prototype_ `UPTRINT TcpSocketConnect(const ANSICHAR* Host, uint16 Port);` (scope `UE::Trace::Private`)
- L36 _prototype_ `UPTRINT TcpSocketListen(uint16 Port);` (scope `UE::Trace::Private`)
- L37 _prototype_ `int32 TcpSocketAccept(UPTRINT Socket, UPTRINT& Out, bool bAsNonBlocking = false);` (scope `UE::Trace::Private`)
- L38 _prototype_ `bool TcpSocketHasData(UPTRINT Socket);` (scope `UE::Trace::Private`)
- L39 _prototype_ `int TcpSocketNative(UPTRINT Socket);` (scope `UE::Trace::Private`)
- L40 _prototype_ `bool TcpSocketPeerName(UPTRINT Socket, char* Name, uint32 NameSize);` (scope `UE::Trace::Private`)
- L41 _prototype_ `bool TcpSocketSetNonBlocking(UPTRINT Socket, bool bNonBlocking);` (scope `UE::Trace::Private`)
- L44 _prototype_ `int32 IoRead(UPTRINT Handle, void* Data, uint32 Size);` (scope `UE::Trace::Private`)
- L45 _prototype_ `bool IoWrite(UPTRINT Handle, const void* Data, uint32 Size);` (scope `UE::Trace::Private`)
- L46 _prototype_ `void IoClose(UPTRINT Handle);` (scope `UE::Trace::Private`)
- L49 _prototype_ `UPTRINT FileOpen(const ANSICHAR* Path);` (scope `UE::Trace::Private`)
- L52 _prototype_ `int32 GetLastErrorCode();` (scope `UE::Trace::Private`)
- L53 _prototype_ `bool GetErrorMessage(char* OutBuffer, uint32 BufferSize, int32 ErrorCode);` (scope `UE::Trace::Private`)
- L57 _macro_ `# define TRACE_PRIVATE_HAS_THROTTLE 0`
- L61 _macro_ `# define THROTTLE_IMPL(x) ;`
- L62 _macro_ `# define THROTTLE_INL`
- L64 _macro_ `# define THROTTLE_IMPL(x) {x}`
- L65 _macro_ `# define THROTTLE_INL inline`

### `Source/Runtime/TraceLog/Private/Trace/Secure/CertUtils.h` (Private)


#### struct `UE::Trace::Private::FCertificateOptions`  
`struct FCertificateOptions`  
_L30-36_
- desc: Options used to create an SSL Certificate. UTF-8 string are supported.
- L32 _public member_ `const char* CommonName = UE_TRACE_SECURESOCKET_DEFAULT_CMNNAME;`
- L33 _public member_ `const char* Organization = UE_TRACE_SECURESOCKET_DEFAULT_ORG;`
- L34 _public member_ `const char* Country = UE_TRACE_SECURESOCKET_DEFAULT_COUNTRY;`
- L35 _public member_ `long DurationInSeconds = 3600L;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Trace`)
- L15 _macro_ `#define UE_TRACE_SECURESOCKET_DEFAULT_CMNNAME "Unreal Engine Trace"` — todo: Make required configuration option when secure connection is enabled
- L16 _macro_ `#define UE_TRACE_SECURESOCKET_DEFAULT_ORG "Epic Games Inc"`
- L17 _macro_ `#define UE_TRACE_SECURESOCKET_DEFAULT_COUNTRY "US"`
- L24 _prototype_ `bool GeneratePrivateKey(EVP_PKEY* PrivateKey);` (scope `UE::Trace::Private`) — Generate a 2048-bit RSA key. @param PrivateKey The private key struct
- L45 _prototype_ `bool GenerateCertificate(EVP_PKEY* PrivateKey, X509* x509, const FCertificateOptions& InCertOptions);` (scope `UE::Trace::Private`) — Generate self-signed x509 certificate. @param PrivateKey The private key struct @param x509 The certificate struct @return True if successful, false otherwise
- L54 _prototype_ `bool X509ToDER(X509* x509, uint8** OutEncoded, int32& OutEncodedSize);` (scope `UE::Trace::Private`) — Encodes the provided certificate in DER format @param x509 Certificate to Encode @param OutEncoded A DER encode SSL Certificate @param OutEncodedSize Size of the certificate @return True if successful, false otherwise
- L63 _prototype_ `bool DERToX509(const uint8* EncodedCert, size_t EncodedSize, X509** OutCert);` (scope `UE::Trace::Private`) — Decodes a DER formatted buffer into a x509 certificate instance @param EncodedCert buffer containing the certificate encoded data @param EncodedSize size of the byffer @param OutCert A pointer to the generated X509 certificate instance @return True if successful, false otherwise
- L72 _prototype_ `bool CreateSelfSignedCert(const FCertificateOptions& InCertOptions, X509** OutCert, EVP_PKEY** OutPrivateKey);` (scope `UE::Trace::Private`) — Creates a self signed certificate based on input options. @param InCertOptions Options used to create the certificate @param OutCert Generated certificate @param OutPrivateKey Generated private key @return True if successful, false otherwise

### `Source/Runtime/TraceLog/Private/Trace/ThreadRegistry.h` (Private)


#### struct `UE::Trace::Private::FThreadInfoNode`  
`struct FThreadInfoNode`  
_L17-25_
- L19 _public member_ `volatile FThreadInfoNode* Next;`
- L20 _public member_ `uint32 ThreadId;`
- L21 _public member_ `uint32 SystemId;`
- L22 _public member_ `int32 SortHint;`
- L23 _public member_ `uint32 _Padding;` — ensures Name is 8-bytes aligned
- L24 _public member_ `ANSICHAR Name[MaxNameLength];`

#### struct `UE::Trace::Private::FThreadGroupNode`  
`struct FThreadGroupNode`  
_L28-33_
- L30 _public member_ `volatile FThreadGroupNode* Next;`
- L31 _public member_ `volatile FThreadInfoNode* ThreadInfoHead;`
- L32 _public member_ `ANSICHAR GroupName[MaxNameLength];`

#### struct `UE::Trace::Private::FThreadRegistryBlock`  
`struct FThreadRegistryBlock`  
_L36-42_
- L38 _public member_ `uint32 Size;`
- L39 _public member_ `volatile uint32 Allocated;`
- L40 _public member_ `volatile FThreadRegistryBlock* Next;`
- L41 _public member_ `uint8 Data[];`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Trace` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Trace`)
- L13 _variable_ `static constexpr uint8 MaxNameLength = 96;` (scope `UE::Trace::Private`)
- L14 _variable_ `static constexpr SIZE_T BlockAllocSize = 4 << 10;` (scope `UE::Trace::Private`)
- L45 _typedef_ `typedef void (*FThreadGroupCallback)(volatile FThreadGroupNode*);` (scope `UE::Trace::Private`)
- L46 _typedef_ `typedef void (*FThreadInfoCallback)(volatile FThreadInfoNode*);` (scope `UE::Trace::Private`)
- L54 _prototype_ `bool Writer_AddThreadGroupBegin(const ANSICHAR* Name);` (scope `UE::Trace::Private`) — Closes the current thread group and appends a new group to a linked list of groups. @param Name ANSI string name of the group (max 95 chars + null terminator).
- L58 _prototype_ `void Writer_AddThreadGroupEnd();` (scope `UE::Trace::Private`) — Closes the current thread group.
- L67 _prototype_ `const ANSICHAR* Writer_AddThreadInfo(uint32 ThreadId, uint32 SystemId, int32 SortHint, const ANSICHAR* Name);` (scope `UE::Trace::Private`) — Adds thread information to the current thread group. @param ThreadId Trace thread identifier. @param SystemId Operating system thread ID. @param SortHint Hint for sorting threads in analysis (-1 for default). @param Name ANSI string name of the thread (max 95 chars + null terminator).
- L73 _prototype_ `void Writer_EnumerateThreadGroups(FThreadGroupCallback Callback);` (scope `UE::Trace::Private`) — Enumerates over the linked list of thread groups. @param Callback Pointer to the thread group node.
- L79 _prototype_ `void Writer_EnumerateUngroupedThreads(FThreadInfoCallback Callback);` (scope `UE::Trace::Private`) — Enumerates over the linked list of ungrouped threads. @param Callback Pointer to the thread node.
- L83 _prototype_ `FThreadGroupNode* Writer_GetCurrentGroup();` (scope `UE::Trace::Private`) — @returns the currently focused thread group

### `Source/Runtime/TraceLog/Private/Trace/WriteBufferRedirect.h` (Private)


#### class `UE::Trace::Private::TWriteBufferQueue`  
`template <uint16 BufferSize> class TWriteBufferQueue`  
_L32-42_
- desc: A buffer queue of traced data. Usable for redirecting behaviour.
- L35 _public prototype_ `TWriteBufferQueue();`
- L36 _public prototype_ `~TWriteBufferQueue();`
- L37 _public prototype_ `static FWriteBuffer* AllocBuffer();`
- L38 _public prototype_ `static FWriteBuffer* FreeBuffer(FWriteBuffer*);`
- L39 _public prototype_ `static FWriteBuffer* NextBuffer(FWriteBuffer*);`
- L41 _public member_ `FWriteBuffer* Head;`
- L46 _function_ `template <uint16 BufferSize> TWriteBufferQueue<BufferSize>::TWriteBufferQueue()`
- L53 _function_ `template <uint16 BufferSize> TWriteBufferQueue<BufferSize>::~TWriteBufferQueue()`
- L64 _function_ `template <uint16 BufferSize> FWriteBuffer* TWriteBufferQueue<BufferSize>::AllocBuffer()`
- L93 _function_ `template <uint16 BufferSize> FWriteBuffer* TWriteBufferQueue<BufferSize>::FreeBuffer(FWriteBuffer* Buffer)`
- L106 _function_ `template <uint16 BufferSize> FWriteBuffer* TWriteBufferQueue<BufferSize>::NextBuffer(FWriteBuffer* __restrict PrevBuffer)`

#### class `UE::Trace::Private::TRedirectScope`  
`template <uint16 BufferSize> class TRedirectScope : public TWriteBufferQueue<BufferSize>`  
_L122-137_
- inherits: `TWriteBufferQueue<BufferSize>`
- desc: Unbounded redirect buffer. Will allocate new buffers with templated size while active.
- L127 _public prototype_ `TRedirectScope();`
- L128 _public prototype_ `~TRedirectScope();`
- L130 _public prototype_ `FWriteBuffer* Finish();`
- L131 _public prototype_ `static FWriteBuffer* NextBuffer(FWriteBuffer* CurrentBuffer);`
- L134 _private prototype_ `void ResetThreadLocalState();`
- L136 _private member_ `FTlsState Prev;`
- L141 _function_ `template <uint16 BufferSize> TRedirectScope<BufferSize>::TRedirectScope()`
- L151 _function_ `template <uint16 BufferSize> TRedirectScope<BufferSize>::~TRedirectScope()`
- L158 _function_ `template <uint16 BufferSize> void TRedirectScope<BufferSize>::ResetThreadLocalState()`
- L169 _function_ `template <uint16 BufferSize> FWriteBuffer* TRedirectScope<BufferSize>::NextBuffer(FWriteBuffer* CurrentBuffer)`
- L178 _function_ `template <uint16 BufferSize> FWriteBuffer* TRedirectScope<BufferSize>::Finish()`

#### enum `UE::Trace::Private::TRedirectScope::(anonymous)`  
`enum : uint16`  
_L125-125_

#### class `UE::Trace::Private::TBoundedRedirectScope`  
`template <uint16 BufferSize> class TBoundedRedirectScope`  
_L193-211_
- desc: Bounded redirect buffer.
- L198 _public prototype_ `TBoundedRedirectScope();`
- L199 _public prototype_ `~TBoundedRedirectScope();`
- L200 _public prototype_ `void Close();`
- L201 _public prototype_ `void Abandon();`
- L202 _public prototype_ `uint8* GetData();`
- L203 _public prototype_ `uint32 GetSize() const;`
- L204 _public prototype_ `uint32 GetCapacity() const;`
- L205 _public prototype_ `void Reset();`
- L208 _private member_ `FTlsState Prev;`
- L209 _private member_ `uint8 Data[BufferSize];`
- L210 _private member_ `FWriteBuffer Buffer;`
- L215 _function_ `template <uint16 BufferSize> inline TBoundedRedirectScope<BufferSize>::TBoundedRedirectScope()`
- L229 _function_ `template <uint16 BufferSize> inline TBoundedRedirectScope<BufferSize>::~TBoundedRedirectScope()`
- L236 _function_ `template <uint16 BufferSize> inline void TBoundedRedirectScope<BufferSize>::Close()`
- L248 _function_ `template <uint16 BufferSize> inline void TBoundedRedirectScope<BufferSize>::Abandon()`
- L255 _function_ `template <uint16 BufferSize> inline uint8* TBoundedRedirectScope<BufferSize>::GetData()`
- L262 _function_ `template <uint16 BufferSize> inline uint32 TBoundedRedirectScope<BufferSize>::GetSize() const`
- L269 _function_ `template <uint16 BufferSize> inline uint32 TBoundedRedirectScope<BufferSize>::GetCapacity() const`
- L276 _function_ `template <uint16 BufferSize> inline void TBoundedRedirectScope<BufferSize>::Reset()`

#### enum `UE::Trace::Private::TBoundedRedirectScope::(anonymous)`  
`enum : uint16`  
_L196-196_

#### class `UE::Trace::Private::FOnConnectRedirectScope`  
`class FOnConnectRedirectScope : public TWriteBufferQueue<OnConnectBufferSize>`  
_L295-305_
- inherits: `TWriteBufferQueue<OnConnectBufferSize>`
- desc: Specialized redirect buffer queue for OnConnect callback.
- L298 _public prototype_ `FOnConnectRedirectScope();`
- L299 _public prototype_ `~FOnConnectRedirectScope();`
- L300 _public prototype_ `static FWriteBuffer* GetBuffer();`
- L301 _public prototype_ `static FWriteBuffer* NextBuffer(FWriteBuffer* CurrentBuffer);`
- L304 _private member_ `static FWriteBuffer* Tail;`
- L308 _function_ `inline FOnConnectRedirectScope::FOnConnectRedirectScope()`
- L314 _function_ `inline FOnConnectRedirectScope::~FOnConnectRedirectScope()`
- L320 _function_ `inline FWriteBuffer* FOnConnectRedirectScope::GetBuffer()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Trace` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Trace`)
- L20 _prototype_ `void* Writer_MemoryAllocate(SIZE_T, uint32);` (scope `UE::Trace::Private`)
- L21 _prototype_ `void Writer_MemoryFree(void*, uint32);` (scope `UE::Trace::Private`)
- L23 _externvar_ `extern thread_local FTlsState GTlsState;` (scope `UE::Trace::Private`)
- L125 _enumerator_ `enum : uint16 { ActiveGrowingRedirection = 0xfffe }; TRedirectScope(); ~TRedirectScope(); FWriteBuffer* Finish(); static FWriteBuffer* NextBuffer(FWriteBuffer* CurrentBuffer);` (scope `UE::Trace::Private::TRedirectScope::__anoneab1971e0103`)
- L196 _enumerator_ `enum : uint16 { ActiveRedirection = 0xffff }; TBoundedRedirectScope(); ~TBoundedRedirectScope(); void Close(); void Abandon(); uint8* GetData(); uint32 GetSize() const;` (scope `UE::Trace::Private::TBoundedRedirectScope::__anoneab1971e0203`)
- L290 _variable_ `constexpr uint16 OnConnectBufferSize = 65408;` (scope `UE::Trace::Private`) — Default size for fallback allocations. These are temporary allocations so fewer larger allocations makes sense. Should be a 128 byte multiple close to max value of uint16.

### `Source/Runtime/TraceLog/Public/Trace/Config.h` (Public)


#### Free symbols / members of external scopes

- L15 _macro_ `# define UE_TRACE_ENABLED 1`
- L21 _macro_ `# define UE_TRACE_ENABLED 0`
- L33 _macro_ `# define UE_TRACE_ENABLED_SHIPPING_EXPERIMENTAL 0`
- L41 _macro_ `# define UE_TRACE_MINIMAL_ENABLED UE_TRACE_ENABLED`
- L48 _macro_ `# define TRACE_PRIVATE_MINIMAL_ENABLED 1`
- L50 _macro_ `# define TRACE_PRIVATE_MINIMAL_ENABLED 0`
- L54 _macro_ `# define TRACE_PRIVATE_FULL_ENABLED 1`
- L56 _macro_ `# define TRACE_PRIVATE_FULL_ENABLED 0`
- L74 _macro_ `# define TRACE_PRIVATE_PROTOCOL_7`
- L82 _macro_ `# define TRACE_PRIVATE_ALLOW_TCP_CONTROL TRACE_PRIVATE_FULL_ENABLED`
- L84 _macro_ `# define TRACE_PRIVATE_ALLOW_TCP_CONTROL UE_TRACE_ALLOW_TCP_CONTROL`
- L91 _macro_ `# define TRACE_PRIVATE_ALLOW_TCP TRACE_PRIVATE_FULL_ENABLED`
- L93 _macro_ `# define TRACE_PRIVATE_ALLOW_TCP UE_TRACE_ALLOW_TCP_TRACING`
- L100 _macro_ `# define TRACE_PRIVATE_ALLOW_FILE TRACE_PRIVATE_FULL_ENABLED`
- L102 _macro_ `# define TRACE_PRIVATE_ALLOW_FILE UE_TRACE_ALLOW_FILE_TRACING`
- L109 _macro_ `# define UE_TRACE_ALLOW_SECURE_TRACING 0`
- L110 _macro_ `# define TRACE_PRIVATE_ALLOW_SECURE_TRACING 0`
- L112 _macro_ `# define TRACE_PRIVATE_ALLOW_SECURE_TRACING UE_TRACE_ALLOW_SECURE_TRACING`
- L119 _macro_ `# define TRACE_PRIVATE_ALLOW_IMPORTANTS TRACE_PRIVATE_FULL_ENABLED`
- L121 _macro_ `# define TRACE_PRIVATE_ALLOW_IMPORTANTS UE_TRACE_ALLOW_IMPORTANT_EVENTS`
- L129 _macro_ `# define UE_TRACE_DEFAULT_TAIL_SIZE 4 << 20`
- L131 _macro_ `# define UE_TRACE_DEFAULT_TAIL_SIZE 0`
- L140 _macro_ `# define UE_TRACE_BLOCK_POOL_MAXSIZE 79 << 20`
- L147 _macro_ `# define UE_TRACE_BLOCK_SIZE (4 << 10)`
- L154 _macro_ `# define UE_TRACE_WRITER_SLEEP_MS (17)`
- L162 _macro_ `# define UE_TRACE_PACKET_VERIFICATION 0`
- L169 _macro_ `# define UE_TRACE_STATISTICS_ENABLED (!(UE_BUILD_SHIPPING || USING_THREAD_SANITISER))`
- L177 _macro_ `# define UE_TRACE_EMIT_STATISTICS UE_TRACE_STATISTICS_ENABLED`
- L193 _macro_ `# define UE_TRACE_ASSERT_FMT(Cond, Fmt, ...)`

### `Source/Runtime/TraceLog/Public/Trace/Detail/Atomic.h` (Public)


#### Free symbols / members of external scopes

- L13 _macro_ `# define TRACE_PRIVATE_THREAD_YIELD 0`
- L16 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Trace` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::Trace`)
- L21 _prototype_ `template <typename Type> Type AtomicLoadRelaxed(Type volatile* Source);` (scope `UE::Trace::Private`)
- L22 _prototype_ `template <typename Type> Type AtomicLoadRelaxed(Type volatile* Source);` (scope `UE::Trace::Private`)
- L23 _prototype_ `template <typename Type> Type AtomicLoadRelaxed(Type volatile* Source);` (scope `UE::Trace::Private`)
- L24 _prototype_ `template <typename Type> Type AtomicLoadRelaxed(Type volatile* Source);` (scope `UE::Trace::Private`)
- L25 _prototype_ `template <typename Type> Type AtomicLoadAcquire(Type volatile* Source);` (scope `UE::Trace::Private`)
- L26 _prototype_ `template <typename Type> void AtomicStoreRelaxed(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L27 _prototype_ `template <typename Type> void AtomicStoreRelease(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L28 _prototype_ `template <typename Type> Type AtomicExchangeAcquire(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L29 _prototype_ `template <typename Type> Type AtomicExchangeRelease(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L30 _prototype_ `template <typename Type> bool AtomicCompareExchangeRelaxed(Type volatile* Target, Type New, Type Expected);` (scope `UE::Trace::Private`)
- L31 _prototype_ `template <typename Type> bool AtomicCompareExchangeAcquire(Type volatile* Target, Type New, Type Expected);` (scope `UE::Trace::Private`)
- L32 _prototype_ `template <typename Type> bool AtomicCompareExchangeRelease(Type volatile* Target, Type New, Type Expected);` (scope `UE::Trace::Private`)
- L33 _prototype_ `template <typename Type> Type AtomicAddRelaxed(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L34 _prototype_ `template <typename Type> Type AtomicAddRelease(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L35 _prototype_ `template <typename Type> Type AtomicAddAcquire(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L36 _prototype_ `template <typename Type> Type AtomicSubRelaxed(Type volatile* Target, Type Value);` (scope `UE::Trace::Private`)
- L39 _function_ `inline void PlatformYield()` (scope `UE::Trace::Private`)
- L59 _function_ `template <typename Type> inline Type AtomicLoadRelaxed(Type volatile* Source)` (scope `UE::Trace::Private`)
- L67 _function_ `template <typename Type> inline Type AtomicLoadAcquire(Type volatile* Source)` (scope `UE::Trace::Private`)
- L75 _function_ `template <typename Type> inline void AtomicStoreRelaxed(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L83 _function_ `template <typename Type> inline void AtomicStoreRelease(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L91 _function_ `template <typename Type> inline Type AtomicExchangeAcquire(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L99 _function_ `template <typename Type> inline Type AtomicExchangeRelease(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L107 _function_ `template <typename Type> inline bool AtomicCompareExchangeRelaxed(Type volatile* Target, Type New, Type Expected)` (scope `UE::Trace::Private`)
- L115 _function_ `template <typename Type> inline bool AtomicCompareExchangeAcquire(Type volatile* Target, Type New, Type Expected)` (scope `UE::Trace::Private`)
- L123 _function_ `template <typename Type> inline bool AtomicCompareExchangeRelease(Type volatile* Target, Type New, Type Expected)` (scope `UE::Trace::Private`)
- L131 _function_ `template <typename Type> inline Type AtomicAddRelaxed(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L139 _function_ `template <typename Type> inline Type AtomicAddAcquire(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L147 _function_ `template <typename Type> inline Type AtomicAddRelease(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L155 _function_ `template <typename Type> inline Type AtomicSubRelaxed(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L163 _function_ `template <typename Type> inline Type AtomicSubAcquire(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)
- L171 _function_ `template <typename Type> inline Type AtomicSubRelease(Type volatile* Target, Type Value)` (scope `UE::Trace::Private`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Channel.h` (Public)


#### class `UE::Trace::FChannel`  
`class FChannel`  
_L32-115_
- desc: A named channel which can be used to filter trace events. Channels can be combined using the '|' operator which allows expressions like ``` UE_TRACE_LOG(FooWriter, FooEvent, FooChannel|BarChannel); ``` Note that this works as an AND operator, similar to how a bitmask is constructed. Channels are by default enabled until FChannel::Initialize() is called. This is to allow events to be emitted during static initialization. In fact all events during this phase are always emitted.
- L57 _public prototype_ `void Setup(const ANSICHAR* InChannelName, const InitArgs& Args);` — Initializes a channel. Used by channel macros, do no use directly.
- L66 _public function_ `virtual bool OnToggle(bool bNewState, const TCHAR** OutReason)` — Allows channels to act pre state change deny the change from happening. @param bNewState Desired new state for channel @param OutReason Deny reason. Set only when returning false. @return True when new state is acceptable, false otherwise.
- L74 _public function_ `virtual void OnToggled(bool bNewState)` — Allows channels to act post state change. At this point it is possible to emit events on this channel. @param bNewState New state for the channel
- L84 _public prototype_ `bool Toggle(bool bEnabled, const TCHAR** OutReason = nullptr);` — Toggles the channel state (on/off). If the channel could not be toggled an optional deny reason can be accessed. @param bEnabled Requested state @param OutReason Optional string pointer. Will contain deny reason on failure. @return New channel state
- L86 _public prototype_ `static void Initialize();`
- L87 _public prototype_ `static Iter ReadNew();`
- L88 _public prototype_ `void Announce() const;`
- L89 _public prototype_ `static bool Toggle(const ANSICHAR* ChannelName, bool bEnabled);`
- L90 _public prototype_ `static void ToggleAll(bool bEnabled);`
- L91 _public prototype_ `static void PanicDisableAll();` — Disabled channels wont be logged with UE_TRACE_LOG
- L92 _public prototype_ `static FChannel* FindChannel(const ANSICHAR* ChannelName);`
- L93 _public prototype_ `static FChannel* FindChannel(FChannelId ChannelId);`
- L94 _public prototype_ `static void EnumerateChannels(ChannelIterCallback Func, void* User);`
- L95 _public prototype_ `bool IsEnabled() const;`
- L96 _public function_ `bool IsReadOnly() const`
- L97 _public prototype_ `uint32 GetName(const ANSICHAR** OutName) const;`
- L98 _public prototype_ `explicit operator bool () const;`
- L99 _public prototype_ `bool operator | (const FChannel& Rhs) const;`
- L102 _private prototype_ `bool ToggleInternal(bool bEnabled, bool bIssueCallback, const TCHAR** OutReason = nullptr);`
- L103 _private prototype_ `static void ToggleAllInternal(bool bEnabled, bool bIssueCallback);`
- L105 _private member_ `FChannel* volatile Next;`
- L111 _private member_ `} Name;`
- L112 _private member_ `volatile int32 Enabled;`
- L113 _private member_ `InitArgs Args;`
- L114 _private member_ `volatile uint8 Lock;`
- L117 _function_ `inline uint32 FChannel::GetName(const ANSICHAR** OutName) const`

#### struct `UE::Trace::FChannel::Iter`  
`struct Iter`  
_L35-40_
- L37 _public prototype_ `~Iter();`
- L38 _public prototype_ `const FChannel* GetNext();`
- L39 _public member_ `void*Inner[3];`

#### struct `UE::Trace::FChannel::InitArgs`  
`struct InitArgs`  
_L42-52_
- L47 _public member_ `const ANSICHAR* Desc;` — User facing description string.
- L51 _public member_ `bool bReadOnly;` — If set, channel cannot be changed during a run, only set through command line.

#### struct `UE::Trace::FChannel::(anonymous)`  
``  
_L107-111_

#### class `UE::Trace::FChannel`  
`namespace UE::Trace`  
_L136-136_
- desc: Since we use this type in macros we need provide an empty definition when trace is not enabled.
- L57 _public prototype_ `void Setup(const ANSICHAR* InChannelName, const InitArgs& Args);` — Initializes a channel. Used by channel macros, do no use directly.
- L66 _public function_ `virtual bool OnToggle(bool bNewState, const TCHAR** OutReason)` — Allows channels to act pre state change deny the change from happening. @param bNewState Desired new state for channel @param OutReason Deny reason. Set only when returning false. @return True when new state is acceptable, false otherwise.
- L74 _public function_ `virtual void OnToggled(bool bNewState)` — Allows channels to act post state change. At this point it is possible to emit events on this channel. @param bNewState New state for the channel
- L84 _public prototype_ `bool Toggle(bool bEnabled, const TCHAR** OutReason = nullptr);` — Toggles the channel state (on/off). If the channel could not be toggled an optional deny reason can be accessed. @param bEnabled Requested state @param OutReason Optional string pointer. Will contain deny reason on failure. @return New channel state
- L86 _public prototype_ `static void Initialize();`
- L87 _public prototype_ `static Iter ReadNew();`
- L88 _public prototype_ `void Announce() const;`
- L89 _public prototype_ `static bool Toggle(const ANSICHAR* ChannelName, bool bEnabled);`
- L90 _public prototype_ `static void ToggleAll(bool bEnabled);`
- L91 _public prototype_ `static void PanicDisableAll();` — Disabled channels wont be logged with UE_TRACE_LOG
- L92 _public prototype_ `static FChannel* FindChannel(const ANSICHAR* ChannelName);`
- L93 _public prototype_ `static FChannel* FindChannel(FChannelId ChannelId);`
- L94 _public prototype_ `static void EnumerateChannels(ChannelIterCallback Func, void* User);`
- L95 _public prototype_ `bool IsEnabled() const;`
- L96 _public function_ `bool IsReadOnly() const`
- L97 _public prototype_ `uint32 GetName(const ANSICHAR** OutName) const;`
- L98 _public prototype_ `explicit operator bool () const;`
- L99 _public prototype_ `bool operator | (const FChannel& Rhs) const;`
- L102 _private prototype_ `bool ToggleInternal(bool bEnabled, bool bIssueCallback, const TCHAR** OutReason = nullptr);`
- L103 _private prototype_ `static void ToggleAllInternal(bool bEnabled, bool bIssueCallback);`
- L105 _private member_ `FChannel* volatile Next;`
- L111 _private member_ `} Name;`
- L112 _private member_ `volatile int32 Enabled;`
- L113 _private member_ `InitArgs Args;`
- L114 _private member_ `volatile uint8 Lock;`
- L117 _function_ `inline uint32 FChannel::GetName(const ANSICHAR** OutName) const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)
- L16 _typedef_ `typedef bool ChannelIterCallback(const FChannelInfo& OutChannelInfo, void*);` (scope `UE::Trace`)
- L108 _member_ `const ANSICHAR* Ptr;` (scope `UE::Trace::FChannel::__anonca429f860108`)
- L109 _member_ `uint32 Len;` (scope `UE::Trace::FChannel::__anonca429f860108`)
- L110 _member_ `uint32 Hash;` (scope `UE::Trace::FChannel::__anonca429f860108`)
- L136 _namespace_ `namespace UE`
- L136 _namespace_ `namespace Trace` (scope `UE`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Channel.inl` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)
- L13 _externvar_ `extern FChannel& TraceLogChannel;` (scope `UE::Trace`)
- L16 _function_ `inline bool FChannel::IsEnabled() const` (scope `UE::Trace::FChannel`)
- L22 _function_ `inline FChannel::operator bool () const` (scope `UE::Trace::FChannel`)
- L28 _function_ `inline bool FChannel::operator | (const FChannel& Rhs) const` (scope `UE::Trace::FChannel`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/EventNode.h` (Public)


#### struct `UE::Trace::Private::FEventInfo`  
`struct FEventInfo`  
_L17-39_
- L34 _public member_ `FLiteralName LoggerName;`
- L35 _public member_ `FLiteralName EventName;`
- L36 _public member_ `const FFieldDesc* Fields;`
- L37 _public member_ `uint16 FieldCount;`
- L38 _public member_ `uint16 Flags;`

#### enum `UE::Trace::Private::FEventInfo::(anonymous)`  
``  
_L20-32_

#### class `UE::Trace::Private::FEventNode`  
`class FEventNode`  
_L42-62_
- L51 _public prototype_ `static FIter Read();`
- L52 _public prototype_ `static FIter ReadNew();`
- L53 _public prototype_ `static void OnConnect();`
- L54 _public prototype_ `uint32 Initialize(const FEventInfo* InInfo);`
- L55 _public prototype_ `void Describe() const;`
- L56 _public function_ `uint32 GetUid() const`
- L59 _private member_ `FEventNode* Next;`
- L60 _private member_ `const FEventInfo* Info;`
- L61 _private member_ `uint32 Uid;`

#### struct `UE::Trace::Private::FEventNode::FIter`  
`struct FIter`  
_L45-49_
- L47 _public prototype_ `const FEventNode* GetNext();`
- L48 _public member_ `void* Inner;`

#### struct `UE::Trace::Private::FEventInfo`  
`namespace UE::Trace::Private`  
_L73-73_
- desc: Since we use this type in macros we need provide an empty definition when trace is not enabled.
- L34 _public member_ `FLiteralName LoggerName;`
- L35 _public member_ `FLiteralName EventName;`
- L36 _public member_ `const FFieldDesc* Fields;`
- L37 _public member_ `uint16 FieldCount;`
- L38 _public member_ `uint16 Flags;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Trace`)
- L21 _enumerator_ `Flag_None = 0` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L22 _enumerator_ `Flag_Important = 1 << 0` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L23 _enumerator_ `Flag_MaybeHasAux = 1 << 1` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L24 _enumerator_ `Flag_NoSync = 1 << 2` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L25 _enumerator_ `Flag_Definition8 = 1 << 3` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L26 _enumerator_ `Flag_Definition16 = 1 << 4` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L27 _enumerator_ `Flag_Definition32 = 1 << 5` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L28 _enumerator_ `Flag_Definition64 = 1 << 6` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L29 _enumerator_ `Flag_MaybeImportant = 1 << 7` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L31 _enumerator_ `DefinitionBits = Flag_Definition8 | Flag_Definition16 | Flag_Definition32 | Flag_Definition64` (scope `UE::Trace::Private::FEventInfo::__anon13325cf50103`)
- L73 _namespace_ `namespace UE`
- L73 _namespace_ `namespace Trace` (scope `UE`)
- L73 _namespace_ `namespace Private` (scope `UE::Trace`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Field.h` (Public)


#### enum `UE::Trace::DisabledField`  
`enum DisabledField`  
_L37-37_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<DisabledField>`  
_L41-41_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<DisabledField>`  
_L41-41_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<DisabledField>`  
_L42-42_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<DisabledField>`  
_L42-42_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<DisabledField>`  
_L43-43_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<DisabledField>`  
_L43-43_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<DisabledField>`  
_L44-44_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<DisabledField>`  
_L44-44_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<bool>`  
_L45-45_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<bool>`  
_L45-45_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<int8>`  
_L46-46_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<int8>`  
_L46-46_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<int16>`  
_L47-47_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<int16>`  
_L47-47_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<int32>`  
_L48-48_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<int32>`  
_L48-48_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<int64>`  
_L49-49_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<int64>`  
_L49-49_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<uint8>`  
_L50-50_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<uint8>`  
_L50-50_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<uint16>`  
_L51-51_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<uint16>`  
_L51-51_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<uint32>`  
_L52-52_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<uint32>`  
_L52-52_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<uint64>`  
_L53-53_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<uint64>`  
_L53-53_

#### struct `UE::Trace::TFieldType`  
`template <typename T> struct TFieldType<T[]>`  
_L56-63_

#### enum `UE::Trace::TFieldType::(anonymous)`  
``  
_L59-62_

#### struct `UE::Trace::TFieldType`  
`template <typename T, int N> struct TFieldType<T[N]>`  
_L67-74_

#### enum `UE::Trace::TFieldType::(anonymous)`  
``  
_L70-73_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<AnsiString>`  
_L77-77_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<AnsiString>`  
_L77-77_

#### enum `UE::Trace::TFieldType::(anonymous)`  
`template <> struct TFieldType<AnsiString>`  
_L78-78_

#### struct `UE::Trace::TFieldType`  
`template <> struct TFieldType<AnsiString>`  
_L78-78_

#### struct `UE::Trace::FLiteralName`  
`struct FLiteralName`  
_L83-95_
- L86 _public function_ `template <uint32 Size> explicit FLiteralName(const ANSICHAR (&Name)[Size]) : Ptr(Name) , Length(Size - 1)`
- L93 _public member_ `const ANSICHAR* Ptr;`
- L94 _public member_ `uint8 Length;`

#### struct `UE::Trace::FFieldDesc`  
`struct FFieldDesc`  
_L98-116_
- L100 _public function_ `FFieldDesc(const FLiteralName& Name, uint8 Type, uint16 Offset, uint16 Size, uint32 ReferencedUid = 0) : Name(Name.Ptr) , ValueOffset(Offset) , ValueSize(Size) , NameSize(Name.Length) , TypeInfo(Type) , Reference(ReferencedUid)`
- L110 _public member_ `const ANSICHAR* Name;`
- L111 _public member_ `uint16 ValueOffset;`
- L112 _public member_ `uint16 ValueSize;`
- L113 _public member_ `uint8 NameSize;`
- L114 _public member_ `uint8 TypeInfo;`
- L115 _public member_ `uint32 Reference;`

#### enum `UE::Trace::EIndexPack`  
`enum class EIndexPack`  
_L123-129_
- L125 _public enumerator_ `NumFieldsMax = 1 << FAuxHeader::FieldBits`
- L126 _public enumerator_ `NumFieldsShift = 8`
- L127 _public enumerator_ `NumFieldsMask = (1 << NumFieldsShift) - 1`
- L128 _public enumerator_ `AuxFieldCounter = 1 << NumFieldsShift`

#### struct `UE::Trace::TField`  
`template <int InIndex, int InOffset, typename Type> struct TField<InIndex, InOffset, Type[]>`  
_L151-154_
- L161 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type[Count]);`
- L183 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, DefinitionType);`
- L185 _public function_ `TField(const FLiteralName& Name, uint32 ReferencedUid) : FieldDesc(Name, Tid, Offset, Size, ReferencedUid)`
- L195 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);`

#### struct `UE::Trace::TField`  
`template <int InIndex, int InOffset, typename Type, int Count> struct TField<InIndex, InOffset, Type[Count]>`  
_L159-162_
- L161 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type[Count]);`
- L183 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, DefinitionType);`
- L185 _public function_ `TField(const FLiteralName& Name, uint32 ReferencedUid) : FieldDesc(Name, Tid, Offset, Size, ReferencedUid)`
- L195 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);`

#### struct `UE::Trace::TField`  
`template <int InIndex, int InOffset> struct TField<InIndex, InOffset, AnsiString>`  
_L167-170_
- L161 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type[Count]);`
- L183 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, DefinitionType);`
- L185 _public function_ `TField(const FLiteralName& Name, uint32 ReferencedUid) : FieldDesc(Name, Tid, Offset, Size, ReferencedUid)`
- L195 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);`

#### struct `UE::Trace::TField`  
`template <int InIndex, int InOffset> struct TField<InIndex, InOffset, WideString>`  
_L174-177_
- L161 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type[Count]);`
- L183 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, DefinitionType);`
- L185 _public function_ `TField(const FLiteralName& Name, uint32 ReferencedUid) : FieldDesc(Name, Tid, Offset, Size, ReferencedUid)`
- L195 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);`

#### struct `UE::Trace::TField`  
`template <int InIndex, int InOffset, typename DefinitionType> struct TField<InIndex, InOffset, TEventRef<DefinitionType>>`  
_L181-189_
- L161 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type[Count]);`
- L183 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, DefinitionType);`
- L185 _public function_ `TField(const FLiteralName& Name, uint32 ReferencedUid) : FieldDesc(Name, Tid, Offset, Size, ReferencedUid)`
- L195 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);`

#### struct `UE::Trace::TField`  
`template <int InIndex, int InOffset, typename Type> struct TField`  
_L193-196_
- L161 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type[Count]);`
- L183 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, DefinitionType);`
- L185 _public function_ `TField(const FLiteralName& Name, uint32 ReferencedUid) : FieldDesc(Name, Tid, Offset, Size, ReferencedUid)`
- L195 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);`

#### enum `UE::Trace::EventProps`  
`enum EventProps`  
_L204-204_
- desc: Used to terminate the field list and determine an event's size.

#### struct `UE::Trace::TField`  
`template <int InNumFields, int InSize> struct TField<InNumFields, InSize, EventProps>`  
_L206-214_
- L161 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type[Count]);`
- L183 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, DefinitionType);`
- L185 _public function_ `TField(const FLiteralName& Name, uint32 ReferencedUid) : FieldDesc(Name, Tid, Offset, Size, ReferencedUid)`
- L195 _public prototype_ `TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);`

#### enum `UE::Trace::TField::(anonymous)`  
``  
_L209-213_

#### Free symbols / members of external scopes

- L18 _macro_ `#define STATICALLY_SIZED_ARRAY_FIELDS_SUPPORT 0` — Statically sized fields (e.g. UE_TRACE_EVENT_FIELD(float[4], Colours)) are not supported as yet. No call for them. The following define is used to track where and partially how to implement them
- L20 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Trace` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::Trace`)
- L27 _prototype_ `void Field_WriteAuxData(uint32, const uint8*, int32);` (scope `UE::Trace::Private`)
- L28 _prototype_ `void Field_WriteStringAnsi(uint32, const ANSICHAR*, int32);` (scope `UE::Trace::Private`)
- L29 _prototype_ `void Field_WriteStringAnsi(uint32, const WIDECHAR*, int32);` (scope `UE::Trace::Private`)
- L30 _prototype_ `void Field_WriteStringWide(uint32, const WIDECHAR*, int32);` (scope `UE::Trace::Private`)
- L41 _enumerator_ `template <> struct TFieldType<DisabledField>{ enum { Tid = 0, Size = 0 }; }; template <> struct TFieldType<bool> { enum { Tid = int(EFieldType::Bool), Size = sizeof(bool) }; }; template <> struct TFieldType<int8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(int8) }; }; template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10103`)
- L41 _enumerator_ `template <> struct TFieldType<DisabledField>{ enum { Tid = 0, Size = 0 }; }; template <> struct TFieldType<bool> { enum { Tid = int(EFieldType::Bool), Size = sizeof(bool) }; }; template <> struct TFieldType<int8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(int8) }; }; template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10103`)
- L42 _enumerator_ `template <> struct TFieldType<bool> { enum { Tid = int(EFieldType::Bool), Size = sizeof(bool) }; }; template <> struct TFieldType<int8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(int8) }; }; template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10203`)
- L42 _enumerator_ `template <> struct TFieldType<bool> { enum { Tid = int(EFieldType::Bool), Size = sizeof(bool) }; }; template <> struct TFieldType<int8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(int8) }; }; template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10203`)
- L43 _enumerator_ `template <> struct TFieldType<int8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(int8) }; }; template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10303`)
- L43 _enumerator_ `template <> struct TFieldType<int8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(int8) }; }; template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10303`)
- L44 _enumerator_ `template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10403`)
- L44 _enumerator_ `template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; }; template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10403`)
- L45 _enumerator_ `template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10503`)
- L45 _enumerator_ `template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; }; template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10503`)
- L46 _enumerator_ `template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10603`)
- L46 _enumerator_ `template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; }; template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10603`)
- L47 _enumerator_ `template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10703`)
- L47 _enumerator_ `template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Uint8), Size = sizeof(uint8) }; }; template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; };` (scope `UE::Trace::TFieldType::__anonaef583b10703`)
- L48 _enumerator_ `template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T>` (scope `UE::Trace::TFieldType::__anonaef583b10803`)
- L48 _enumerator_ `template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Uint16), Size = sizeof(uint16) }; }; template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T>` (scope `UE::Trace::TFieldType::__anonaef583b10803`)
- L49 _enumerator_ `template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]>` (scope `UE::Trace::TFieldType::__anonaef583b10903`)
- L49 _enumerator_ `template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Uint32), Size = sizeof(uint32) }; }; template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]>` (scope `UE::Trace::TFieldType::__anonaef583b10903`)
- L50 _enumerator_ `template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> {` (scope `UE::Trace::TFieldType::__anonaef583b10a03`)
- L50 _enumerator_ `template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Uint64), Size = sizeof(uint64) }; }; template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> {` (scope `UE::Trace::TFieldType::__anonaef583b10a03`)
- L51 _enumerator_ `template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> { enum` (scope `UE::Trace::TFieldType::__anonaef583b10b03`)
- L51 _enumerator_ `template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32),Size = sizeof(float) }; }; template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> { enum` (scope `UE::Trace::TFieldType::__anonaef583b10b03`)
- L52 _enumerator_ `template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> { enum {` (scope `UE::Trace::TFieldType::__anonaef583b10c03`)
- L52 _enumerator_ `template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64),Size = sizeof(double) }; }; template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> { enum {` (scope `UE::Trace::TFieldType::__anonaef583b10c03`)
- L53 _enumerator_ `template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> { enum { Tid = int(TFieldType<T>::Tid)|int(EFieldType::Array),` (scope `UE::Trace::TFieldType::__anonaef583b10d03`)
- L53 _enumerator_ `template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer),Size = sizeof(void*) }; }; template <typename T> struct TFieldType<T[]> { enum { Tid = int(TFieldType<T>::Tid)|int(EFieldType::Array),` (scope `UE::Trace::TFieldType::__anonaef583b10d03`)
- L60 _enumerator_ `Tid = int(TFieldType<T>::Tid)|int(EFieldType::Array)` (scope `UE::Trace::TFieldType::__anonaef583b10e03`)
- L61 _enumerator_ `Size = 0` (scope `UE::Trace::TFieldType::__anonaef583b10e03`)
- L71 _enumerator_ `Tid = int(TFieldType<T>::Tid)|int(EFieldType::Array)` (scope `UE::Trace::TFieldType::__anonaef583b10f03`)
- L72 _enumerator_ `Size = sizeof(T[N])` (scope `UE::Trace::TFieldType::__anonaef583b10f03`)
- L77 _enumerator_ `template <> struct TFieldType<AnsiString> { enum { Tid = int(EFieldType::AnsiString), Size = 0, }; }; template <> struct TFieldType<WideString> { enum { Tid = int(EFieldType::WideString), Size = 0, }; }; struct FLiteralName {` (scope `UE::Trace::TFieldType::__anonaef583b11003`)
- L77 _enumerator_ `template <> struct TFieldType<AnsiString> { enum { Tid = int(EFieldType::AnsiString), Size = 0, }; }; template <> struct TFieldType<WideString> { enum { Tid = int(EFieldType::WideString), Size = 0, }; }; struct FLiteralName {` (scope `UE::Trace::TFieldType::__anonaef583b11003`)
- L78 _enumerator_ `template <> struct TFieldType<WideString> { enum { Tid = int(EFieldType::WideString), Size = 0, }; }; struct FLiteralName { template <uint32 Size>` (scope `UE::Trace::TFieldType::__anonaef583b11103`)
- L78 _enumerator_ `template <> struct TFieldType<WideString> { enum { Tid = int(EFieldType::WideString), Size = 0, }; }; struct FLiteralName { template <uint32 Size>` (scope `UE::Trace::TFieldType::__anonaef583b11103`)
- L132 _macro_ `#define TRACE_PRIVATE_FIELD(InIndex, InOffset, Type) \`
- L210 _enumerator_ `NumFields = InNumFields & int(EIndexPack::NumFieldsMask)` (scope `UE::Trace::TField::__anonaef583b11203`)
- L211 _enumerator_ `Size = InSize` (scope `UE::Trace::TField::__anonaef583b11203`)
- L212 _enumerator_ `NumAuxFields = (InNumFields >> int(EIndexPack::NumFieldsShift)) & int(EIndexPack::NumFieldsMask)` (scope `UE::Trace::TField::__anonaef583b11203`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Important/ImportantLogScope.h` (Public)


#### class `UE::Trace::Private::FImportantLogScope`  
`class FImportantLogScope`  
_L14-33_
- L18 _public prototype_ `template <typename EventType> static FImportantLogScope Enter();`
- L20 _public prototype_ `template <typename EventType> static FImportantLogScope Enter(uint32 ArrayDataSize);`
- L21 _public prototype_ `void operator += (const FImportantLogScope&) const;`
- L22 _public function_ `const FImportantLogScope& operator << (bool) const`
- L23 _public function_ `constexpr explicit operator bool () const`
- L29 _private prototype_ `static FImportantLogScope EnterImpl(uint32 Uid, uint32 Size);`
- L30 _private member_ `uint8* Ptr;`
- L31 _private member_ `int32 BufferOffset;`
- L32 _private member_ `int32 AuxCursor;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Trace`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Important/ImportantLogScope.inl` (Public)


#### struct `UE::Trace::Private::FImportantLogScope::FFieldSet`  
`template <typename FieldMeta, typename Type> struct FImportantLogScope::FFieldSet`  
_L97-105_
- L100 _public function_ `static void Impl(FImportantLogScope* Scope, const Type& Value)`
- L112 _public function_ `static void Impl(FImportantLogScope* Scope, Type const* Data, int32 Num)`
- L135 _public function_ `static void Impl(FImportantLogScope* Scope, const ANSICHAR* String, int32 Length=-1)`
- L156 _public function_ `static void Impl(FImportantLogScope* Scope, const WIDECHAR* String, int32 Length=-1)`
- L218 _public function_ `static void Impl(FImportantLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FImportantLogScope::FFieldSet`  
`template <typename FieldMeta, typename Type> struct FImportantLogScope::FFieldSet<FieldMeta, Type[]>`  
_L109-128_
- L100 _public function_ `static void Impl(FImportantLogScope* Scope, const Type& Value)`
- L112 _public function_ `static void Impl(FImportantLogScope* Scope, Type const* Data, int32 Num)`
- L135 _public function_ `static void Impl(FImportantLogScope* Scope, const ANSICHAR* String, int32 Length=-1)`
- L156 _public function_ `static void Impl(FImportantLogScope* Scope, const WIDECHAR* String, int32 Length=-1)`
- L218 _public function_ `static void Impl(FImportantLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FImportantLogScope::FFieldSet`  
`template <typename FieldMeta> struct FImportantLogScope::FFieldSet<FieldMeta, AnsiString>`  
_L132-182_
- L100 _public function_ `static void Impl(FImportantLogScope* Scope, const Type& Value)`
- L112 _public function_ `static void Impl(FImportantLogScope* Scope, Type const* Data, int32 Num)`
- L135 _public function_ `static void Impl(FImportantLogScope* Scope, const ANSICHAR* String, int32 Length=-1)`
- L156 _public function_ `static void Impl(FImportantLogScope* Scope, const WIDECHAR* String, int32 Length=-1)`
- L218 _public function_ `static void Impl(FImportantLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FImportantLogScope::FFieldSet`  
`template <typename FieldMeta> struct FImportantLogScope::FFieldSet<FieldMeta, WideString>`  
_L186-211_
- L100 _public function_ `static void Impl(FImportantLogScope* Scope, const Type& Value)`
- L112 _public function_ `static void Impl(FImportantLogScope* Scope, Type const* Data, int32 Num)`
- L135 _public function_ `static void Impl(FImportantLogScope* Scope, const ANSICHAR* String, int32 Length=-1)`
- L156 _public function_ `static void Impl(FImportantLogScope* Scope, const WIDECHAR* String, int32 Length=-1)`
- L218 _public function_ `static void Impl(FImportantLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FImportantLogScope::FFieldSet`  
`template <typename FieldMeta, typename DefinitionType> struct FImportantLogScope::FFieldSet<FieldMeta, TEventRef<DefinitionType>>`  
_L215-222_
- L100 _public function_ `static void Impl(FImportantLogScope* Scope, const Type& Value)`
- L112 _public function_ `static void Impl(FImportantLogScope* Scope, Type const* Data, int32 Num)`
- L135 _public function_ `static void Impl(FImportantLogScope* Scope, const ANSICHAR* String, int32 Length=-1)`
- L156 _public function_ `static void Impl(FImportantLogScope* Scope, const WIDECHAR* String, int32 Length=-1)`
- L218 _public function_ `static void Impl(FImportantLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Trace` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Trace`)
- L21 _externvar_ `extern FSharedBuffer* volatile GSharedBuffer;` (scope `UE::Trace::Private`)
- L22 _prototype_ `FNextSharedBuffer Writer_NextSharedBuffer(FSharedBuffer*, int32, int32);` (scope `UE::Trace::Private`)
- L28 _function_ `template <class T> UE_AUTORTFM_ALWAYS_OPEN FORCENOINLINE FImportantLogScope FImportantLogScope::Enter(uint32 ArrayDataSize)` (scope `UE::Trace::Private::FImportantLogScope`)
- L46 _function_ `template <class T> UE_AUTORTFM_ALWAYS_OPEN inline FImportantLogScope FImportantLogScope::Enter()` (scope `UE::Trace::Private::FImportantLogScope`)
- L56 _function_ `UE_AUTORTFM_ALWAYS_OPEN inline FImportantLogScope FImportantLogScope::EnterImpl(uint32 Uid, uint32 Size)` (scope `UE::Trace::Private::FImportantLogScope`)
- L89 _function_ `UE_AUTORTFM_ALWAYS_OPEN inline void FImportantLogScope::operator += (const FImportantLogScope& Other) const` (scope `UE::Trace::Private::FImportantLogScope`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Important/SharedBuffer.h` (Public)


#### struct `UE::Trace::Private::FSharedBuffer`  
`struct FSharedBuffer`  
_L15-27_
- L22 _public member_ `int32 volatile Cursor;` — also packs in a ref count.
- L23 _public member_ `uint32 Size;`
- L24 _public member_ `uint32 Final;`
- L25 _public member_ `uint32 _Unused;`
- L26 _public member_ `FSharedBuffer* Next;`

#### enum `UE::Trace::Private::FSharedBuffer::(anonymous)`  
`enum : uint32`  
_L17-17_

#### enum `UE::Trace::Private::FSharedBuffer::(anonymous)`  
`enum : uint32`  
_L18-18_

#### enum `UE::Trace::Private::FSharedBuffer::(anonymous)`  
`enum : uint32`  
_L19-19_

#### enum `UE::Trace::Private::FSharedBuffer::(anonymous)`  
`enum : uint32`  
_L20-20_

#### struct `UE::Trace::Private::FNextSharedBuffer`  
`struct FNextSharedBuffer`  
_L30-34_
- L32 _public member_ `FSharedBuffer* Buffer;`
- L33 _public member_ `int32 RegionStart;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Trace`)
- L17 _enumerator_ `enum : uint32 { CursorShift = 10 }; enum : uint32 { RefBit = 1 << 0 }; enum : uint32 { RefInit = (1 << CursorShift) - 1 }; enum : uint32 { MaxSize = 1 << (32 - CursorShift - 1) }; int32 volatile Cursor; uint32 Size; uint32 Final;` (scope `UE::Trace::Private::FSharedBuffer::__anon9ef66eeb0103`)
- L18 _enumerator_ `enum : uint32 { RefBit = 1 << 0 }; enum : uint32 { RefInit = (1 << CursorShift) - 1 }; enum : uint32 { MaxSize = 1 << (32 - CursorShift - 1) }; int32 volatile Cursor; uint32 Size; uint32 Final; uint32 _Unused;` (scope `UE::Trace::Private::FSharedBuffer::__anon9ef66eeb0203`)
- L19 _enumerator_ `enum : uint32 { RefInit = (1 << CursorShift) - 1 }; enum : uint32 { MaxSize = 1 << (32 - CursorShift - 1) }; int32 volatile Cursor; uint32 Size; uint32 Final; uint32 _Unused; FSharedBuffer* Next;` (scope `UE::Trace::Private::FSharedBuffer::__anon9ef66eeb0303`)
- L20 _enumerator_ `enum : uint32 { MaxSize = 1 << (32 - CursorShift - 1) }; int32 volatile Cursor; uint32 Size; uint32 Final; uint32 _Unused; FSharedBuffer* Next;` (scope `UE::Trace::Private::FSharedBuffer::__anon9ef66eeb0403`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/LogScope.h` (Public)


#### class `UE::Trace::Private::FLogScope`  
`class FLogScope`  
_L19-49_
- L25 _public prototype_ `template <typename EventType> static auto Enter();`
- L27 _public prototype_ `template <typename EventType> static auto ScopedEnter();`
- L29 _public prototype_ `template <typename EventType> static auto ScopedStampedEnter();`
- L30 _public function_ `void* GetPointer() const`
- L31 _public function_ `const FLogScope& operator << (bool) const`
- L32 _public function_ `constexpr explicit operator bool () const`
- L38 _protected prototype_ `void Commit() const;`
- L39 _protected prototype_ `void Commit(FWriteBuffer* __restrict LatestBuffer) const;`
- L43 _private prototype_ `template <uint32 Flags> static auto EnterImpl(uint32 Uid, uint32 Size);`
- L44 _private prototype_ `template <class T> inline void EnterPrelude(uint32 Size);`
- L45 _private prototype_ `template <class T> inline void EnterPrelude(uint32 Size);`
- L46 _private prototype_ `inline void EnterNoSync(uint32 Uid, uint32 Size);`
- L47 _private member_ `uint8* Ptr;`
- L48 _private member_ `FWriteBuffer* Buffer;`

#### class `UE::Trace::Private::TLogScope`  
`template <bool bMaybeHasAux> class TLogScope : public FLogScope`  
_L53-58_
- inherits: `FLogScope`
- L57 _public prototype_ `inline void operator += (const FLogScope&) const;`

#### class `UE::Trace::Private::TOnConnectLogScope`  
`template <bool bMaybeHasAux> class TOnConnectLogScope : public TLogScope<bMaybeHasAux>`  
_L62-77_
- inherits: `TLogScope<bMaybeHasAux>`
- L66 _public prototype_ `TOnConnectLogScope();`
- L67 _public function_ `TOnConnectLogScope(TOnConnectLogScope&& Other) : TLogScope<bMaybeHasAux>(std::move(Other)) , PrevState(Other.PrevState) , bActive(Other.bActive)`
- L72 _public prototype_ `~TOnConnectLogScope();`
- L75 _private member_ `FTlsState PrevState;`
- L76 _private member_ `bool bActive;`

#### class `UE::Trace::Private::FScopedLogScope`  
`class FScopedLogScope`  
_L81-90_
- L84 _public prototype_ `~FScopedLogScope();`
- L85 _public prototype_ `void SetActive();`
- L86 _public member_ `bool bActive = false;`
- L89 _private prototype_ `void Deinit();`

#### class `UE::Trace::Private::FScopedStampedLogScope`  
`class FScopedStampedLogScope`  
_L93-102_
- L96 _public prototype_ `~FScopedStampedLogScope();`
- L97 _public prototype_ `void SetActive();`
- L98 _public member_ `bool bActive = false;`
- L101 _private prototype_ `void Deinit();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Trace`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/LogScope.inl` (Public)


#### struct `UE::Trace::Private::FLogScope::FFieldSet`  
`template <typename FieldMeta, typename Type> struct FLogScope::FFieldSet`  
_L344-352_
- L347 _public function_ `static void Impl(FLogScope* Scope, const Type& Value)`
- L359 _public function_ `static void Impl(FLogScope*, Type const* Data, int32 Num)`
- L372 _public prototype_ `static void Impl(FLogScope*, Type const* Data, int32 Num=-1) = delete;`
- L381 _public function_ `static void Impl(FLogScope*, const ANSICHAR* String, int32 Length=-1)`
- L393 _public function_ `static void Impl(FLogScope*, const WIDECHAR* String, int32 Length=-1)`
- L429 _public function_ `static void Impl(FLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FLogScope::FFieldSet`  
`template <typename FieldMeta, typename Type> struct FLogScope::FFieldSet<FieldMeta, Type[]>`  
_L356-365_
- L347 _public function_ `static void Impl(FLogScope* Scope, const Type& Value)`
- L359 _public function_ `static void Impl(FLogScope*, Type const* Data, int32 Num)`
- L372 _public prototype_ `static void Impl(FLogScope*, Type const* Data, int32 Num=-1) = delete;`
- L381 _public function_ `static void Impl(FLogScope*, const ANSICHAR* String, int32 Length=-1)`
- L393 _public function_ `static void Impl(FLogScope*, const WIDECHAR* String, int32 Length=-1)`
- L429 _public function_ `static void Impl(FLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FLogScope::FFieldSet`  
`template <typename FieldMeta, typename Type, int32 Count> struct FLogScope::FFieldSet<FieldMeta, Type[Count]>`  
_L370-373_
- L347 _public function_ `static void Impl(FLogScope* Scope, const Type& Value)`
- L359 _public function_ `static void Impl(FLogScope*, Type const* Data, int32 Num)`
- L372 _public prototype_ `static void Impl(FLogScope*, Type const* Data, int32 Num=-1) = delete;`
- L381 _public function_ `static void Impl(FLogScope*, const ANSICHAR* String, int32 Length=-1)`
- L393 _public function_ `static void Impl(FLogScope*, const WIDECHAR* String, int32 Length=-1)`
- L429 _public function_ `static void Impl(FLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FLogScope::FFieldSet`  
`template <typename FieldMeta> struct FLogScope::FFieldSet<FieldMeta, AnsiString>`  
_L378-404_
- L347 _public function_ `static void Impl(FLogScope* Scope, const Type& Value)`
- L359 _public function_ `static void Impl(FLogScope*, Type const* Data, int32 Num)`
- L372 _public prototype_ `static void Impl(FLogScope*, Type const* Data, int32 Num=-1) = delete;`
- L381 _public function_ `static void Impl(FLogScope*, const ANSICHAR* String, int32 Length=-1)`
- L393 _public function_ `static void Impl(FLogScope*, const WIDECHAR* String, int32 Length=-1)`
- L429 _public function_ `static void Impl(FLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FLogScope::FFieldSet`  
`template <typename FieldMeta> struct FLogScope::FFieldSet<FieldMeta, WideString>`  
_L408-422_
- L347 _public function_ `static void Impl(FLogScope* Scope, const Type& Value)`
- L359 _public function_ `static void Impl(FLogScope*, Type const* Data, int32 Num)`
- L372 _public prototype_ `static void Impl(FLogScope*, Type const* Data, int32 Num=-1) = delete;`
- L381 _public function_ `static void Impl(FLogScope*, const ANSICHAR* String, int32 Length=-1)`
- L393 _public function_ `static void Impl(FLogScope*, const WIDECHAR* String, int32 Length=-1)`
- L429 _public function_ `static void Impl(FLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### struct `UE::Trace::Private::FLogScope::FFieldSet`  
`template <typename FieldMeta, typename DefinitionType> struct FLogScope::FFieldSet<FieldMeta, TEventRef<DefinitionType>>`  
_L426-433_
- L347 _public function_ `static void Impl(FLogScope* Scope, const Type& Value)`
- L359 _public function_ `static void Impl(FLogScope*, Type const* Data, int32 Num)`
- L372 _public prototype_ `static void Impl(FLogScope*, Type const* Data, int32 Num=-1) = delete;`
- L381 _public function_ `static void Impl(FLogScope*, const ANSICHAR* String, int32 Length=-1)`
- L393 _public function_ `static void Impl(FLogScope*, const WIDECHAR* String, int32 Length=-1)`
- L429 _public function_ `static void Impl(FLogScope* Scope, const TEventRef<DefinitionType>& Reference)`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Trace` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Trace`)
- L22 _externvar_ `extern uint64 GStartCycle;` (scope `UE::Trace::Private`)
- L23 _externvar_ `extern uint32 volatile GLogSerial;` (scope `UE::Trace::Private`)
- L27 _function_ `inline void FLogScope::Commit() const` (scope `UE::Trace::Private::FLogScope`)
- L34 _function_ `inline void FLogScope::Commit(FWriteBuffer* __restrict LatestBuffer) const` (scope `UE::Trace::Private::FLogScope`)
- L47 _function_ `inline auto FLogScope::EnterImpl(uint32 Uid, uint32 Size)` (scope `UE::Trace::Private::FLogScope`)
- L89 _function_ `inline void FLogScope::EnterPrelude(uint32 Size)` (scope `UE::Trace::Private::FLogScope`)
- L115 _function_ `inline void FLogScope::Enter(uint32 Uid, uint32 Size, bool bSetSerial )` (scope `UE::Trace::Private::FLogScope`)
- L129 _function_ `inline void FLogScope::EnterNoSync(uint32 Uid, uint32 Size)` (scope `UE::Trace::Private::FLogScope`)
- L143 _function_ `inline void TLogScope<bMaybeHasAux>::operator += (const FLogScope&) const` (scope `UE::Trace::Private::TLogScope`)
- L160 _function_ `inline void FScopedLogScope::Deinit()` (scope `UE::Trace::Private::FScopedLogScope`)
- L173 _function_ `AutoRTFM::Open([this] { this->Deinit(); });` (scope `UE::Trace::Private::FScopedLogScope::Deinit`)
- L192 _function_ `inline FScopedLogScope::~FScopedLogScope()` (scope `UE::Trace::Private::FScopedLogScope`)
- L198 _function_ `inline void FScopedLogScope::SetActive()` (scope `UE::Trace::Private::FScopedLogScope`)
- L211 _function_ `AutoRTFM::PushOnAbortHandler(this, [this] { this->Deinit(); });` (scope `UE::Trace::Private::FScopedLogScope::SetActive`) — If we are operating closed (in a transaction) we could abort before `this` hits its destructor. In that case we need to remember when we abort to close out the scoped trace event.
- L212 _function_ `AutoRTFM::Open([this] { this->SetActive(); });` (scope `UE::Trace::Private::FScopedLogScope::SetActive`)
- L220 _function_ `inline void FScopedStampedLogScope::Deinit()` (scope `UE::Trace::Private::FScopedStampedLogScope`)
- L233 _function_ `AutoRTFM::Open([this] { this->Deinit(); });` (scope `UE::Trace::Private::FScopedStampedLogScope::Deinit`)
- L254 _function_ `inline FScopedStampedLogScope::~FScopedStampedLogScope()` (scope `UE::Trace::Private::FScopedStampedLogScope`)
- L260 _function_ `inline void FScopedStampedLogScope::SetActive()` (scope `UE::Trace::Private::FScopedStampedLogScope`)
- L273 _function_ `AutoRTFM::PushOnAbortHandler(this, [this] { this->Deinit(); });` (scope `UE::Trace::Private::FScopedStampedLogScope::SetActive`) — If we are operating closed (in a transaction) we could abort before `this` hits its destructor. In that case we need to remember when we abort to close out the scoped trace event.
- L274 _function_ `AutoRTFM::Open([this] { this->SetActive(); });` (scope `UE::Trace::Private::FScopedStampedLogScope::SetActive`)
- L284 _function_ `FORCENOINLINE auto FLogScope::Enter()` (scope `UE::Trace::Private::FLogScope`)
- L294 _function_ `FORCENOINLINE auto FLogScope::ScopedEnter()` (scope `UE::Trace::Private::FLogScope`)
- L317 _function_ `FORCENOINLINE auto FLogScope::ScopedStampedEnter()` (scope `UE::Trace::Private::FLogScope`)
- L437 _function_ `template <bool bMaybeHasAux> TOnConnectLogScope<bMaybeHasAux>::TOnConnectLogScope()` (scope `UE::Trace::Private::TOnConnectLogScope`)
- L444 _function_ `template <bool bMaybeHasAux> TOnConnectLogScope<bMaybeHasAux>::~TOnConnectLogScope()` (scope `UE::Trace::Private::TOnConnectLogScope`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocol.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol0.h` (Public)


#### enum `UE::Trace::Protocol0::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 0 }; enum : uint8 { Field_CategoryMask = 0300, Field_Integer = 0000,`

#### enum `UE::Trace::Protocol0::(anonymous)`  
``  
_L21-44_

#### enum `UE::Trace::Protocol0::EFieldType`  
`enum class EFieldType : uint8`  
_L47-64_
- L49 _public enumerator_ `Bool = Field_Pod | Field_Integer | Field_8`
- L50 _public enumerator_ `Int8 = Field_Pod | Field_Integer|Field_Signed | Field_8`
- L51 _public enumerator_ `Int16 = Field_Pod | Field_Integer|Field_Signed | Field_16`
- L52 _public enumerator_ `Int32 = Field_Pod | Field_Integer|Field_Signed | Field_32`
- L53 _public enumerator_ `Int64 = Field_Pod | Field_Integer|Field_Signed | Field_64`
- L54 _public enumerator_ `Uint8 = Field_Pod | Field_Integer | Field_8`
- L55 _public enumerator_ `Uint16 = Field_Pod | Field_Integer | Field_16`
- L56 _public enumerator_ `Uint32 = Field_Pod | Field_Integer | Field_32`
- L57 _public enumerator_ `Uint64 = Field_Pod | Field_Integer | Field_64`
- L58 _public enumerator_ `Pointer = Field_Pod | Field_Integer | Field_Ptr`
- L59 _public enumerator_ `Float32 = Field_Pod | Field_Float | Field_32`
- L60 _public enumerator_ `Float64 = Field_Pod | Field_Float | Field_64`
- L61 _public enumerator_ `AnsiString = Field_String | Field_Integer|Field_Array | Field_8`
- L62 _public enumerator_ `WideString = Field_String | Field_Integer|Field_Array | Field_16`
- L63 _public enumerator_ `Array = Field_Array`

#### struct `UE::Trace::Protocol0::FNewEventEvent`  
`struct FNewEventEvent`  
_L67-82_
- L69 _public member_ `uint16 EventUid;`
- L70 _public member_ `uint8 FieldCount;`
- L71 _public member_ `uint8 Flags;`
- L72 _public member_ `uint8 LoggerNameSize;`
- L73 _public member_ `uint8 EventNameSize;`
- L80 _public member_ `} Fields[];`

#### struct `UE::Trace::Protocol0::FNewEventEvent::(anonymous)`  
``  
_L75-80_

#### enum `UE::Trace::Protocol0::EKnownEventUids`  
`enum class EKnownEventUids : uint16`  
_L85-94_
- L87 _public enumerator_ `NewEvent`
- L88 _public enumerator_ `User`
- L89 _public enumerator_ `Max = (1 << 14) - 1` — ...leaves two MSB bits for other uses.
- L90 _public enumerator_ `UidMask = Max`
- L91 _public enumerator_ `Invalid = Max`
- L92 _public enumerator_ `Flag_Important = 1 << 14`
- L93 _public enumerator_ `Flag_Unused = 1 << 15`

#### struct `UE::Trace::Protocol0::FEventHeader`  
`struct FEventHeader`  
_L97-102_
- L99 _public member_ `uint16 Uid;`
- L100 _public member_ `uint16 Size;`
- L101 _public member_ `uint8 EventData[];`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol0` (scope `UE::Trace`)
- L23 _enumerator_ `Field_CategoryMask = 0300` (scope `UE::Trace::Protocol0::__anona420dac30103`) — Category
- L24 _enumerator_ `Field_Integer = 0000` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L25 _enumerator_ `Field_Float = 0100` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L26 _enumerator_ `Field_Array = 0200` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L29 _enumerator_ `Field_Pow2SizeMask = 0003` (scope `UE::Trace::Protocol0::__anona420dac30103`) — Size
- L30 _enumerator_ `Field_8 = 0000` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L31 _enumerator_ `Field_16 = 0001` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L32 _enumerator_ `Field_32 = 0002` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L33 _enumerator_ `Field_64 = 0003` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L34 _enumerator_ `Field_Ptr = Field_64` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L37 _enumerator_ `Field_SpecialMask = 0030` (scope `UE::Trace::Protocol0::__anona420dac30103`) — Specials
- L38 _enumerator_ `Field_Pod = 0000` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L39 _enumerator_ `Field_String = 0010` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L40 _enumerator_ `Field_Signed = 0020` (scope `UE::Trace::Protocol0::__anona420dac30103`)
- L76 _member_ `uint16 Offset;` (scope `UE::Trace::Protocol0::FNewEventEvent::__anona420dac30208`)
- L77 _member_ `uint16 Size;` (scope `UE::Trace::Protocol0::FNewEventEvent::__anona420dac30208`)
- L78 _member_ `uint8 TypeInfo;` (scope `UE::Trace::Protocol0::FNewEventEvent::__anona420dac30208`)
- L79 _member_ `uint8 NameSize;` (scope `UE::Trace::Protocol0::FNewEventEvent::__anona420dac30208`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol1.h` (Public)


#### enum `UE::Trace::Protocol1::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 1 }; using Protocol0::EFieldType; using Protocol0::FNewEventEvent; enum class EEventFlags : uint8`

#### enum `UE::Trace::Protocol1::EEventFlags`  
`enum class EEventFlags : uint8`  
_L24-29_
- L26 _public enumerator_ `Important = 1 << 0`
- L27 _public enumerator_ `MaybeHasAux = 1 << 1`
- L28 _public enumerator_ `NoSync = 1 << 2`

#### enum `UE::Trace::Protocol1::EKnownEventUids`  
`enum class EKnownEventUids : uint16`  
_L32-39_
- L34 _public enumerator_ `NewEvent`
- L35 _public enumerator_ `User`
- L36 _public enumerator_ `Max = (1 << 15) - 1`
- L37 _public enumerator_ `UidMask = Max`
- L38 _public enumerator_ `Invalid = Max`

#### struct `UE::Trace::Protocol1::FEventHeader`  
`struct FEventHeader`  
_L42-48_
- L44 _public member_ `uint16 Uid;`
- L45 _public member_ `uint16 Size;`
- L46 _public member_ `uint16 Serial;`
- L47 _public member_ `uint8 EventData[];`

#### struct `UE::Trace::Protocol1::FAuxHeader`  
`struct FAuxHeader`  
_L51-66_
- L65 _public member_ `uint8 Data[];`

#### enum `UE::Trace::Protocol1::FAuxHeader::(anonymous)`  
``  
_L54-58_

#### union `UE::Trace::Protocol1::FAuxHeader::(anonymous)`  
``  
_L61-64_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol1` (scope `UE::Trace`)
- L55 _enumerator_ `AuxDataBit = 0x80` (scope `UE::Trace::Protocol1::FAuxHeader::__anona420df040103`)
- L56 _enumerator_ `FieldMask = 0x7f` (scope `UE::Trace::Protocol1::FAuxHeader::__anona420df040103`)
- L57 _enumerator_ `SizeLimit = 1 << 24` (scope `UE::Trace::Protocol1::FAuxHeader::__anona420df040103`)
- L62 _member_ `uint8 FieldIndex;` (scope `UE::Trace::Protocol1::FAuxHeader::__anona420df04020a`) — 7 bits max (MSB is used to indicate aux data)
- L63 _member_ `uint32 Size;` (scope `UE::Trace::Protocol1::FAuxHeader::__anona420df04020a`) — encoded as (Size & 0x00ffffff) << 8

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol2.h` (Public)


#### enum `UE::Trace::Protocol2::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 2 }; using Protocol1::EFieldType; using Protocol1::FNewEventEvent; using Protocol1::EEventFlags; using Protocol1::EKnownEventUids; using Protocol1::FAuxHeader;`

#### struct `UE::Trace::Protocol2::FEventHeader`  
`struct FEventHeader`  
_L27-31_
- L29 _public member_ `uint16 Uid;`
- L30 _public member_ `uint16 Size;`

#### struct `UE::Trace::Protocol2::FEventHeaderSync`  
`struct FEventHeaderSync : public FEventHeader`  
_L35-41_
- inherits: `FEventHeader`
- L38 _public member_ `uint16 SerialLow;` — 24-bit...
- L39 _public member_ `uint8 SerialHigh;` — ...serial no.
- L40 _public member_ `uint8 EventData[];`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol2` (scope `UE::Trace`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol3.h` (Public)


#### enum `UE::Trace::Protocol3::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 3 }; using Protocol2::EFieldType; using Protocol2::FNewEventEvent; using Protocol2::EEventFlags; using Protocol2::EKnownEventUids; using Protocol2::FAuxHeader;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol3` (scope `UE::Trace`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol4.h` (Public)


#### enum `UE::Trace::Protocol4::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 4 }; using Protocol3::EFieldType; using Protocol3::FNewEventEvent; using Protocol3::EEventFlags; using Protocol3::FAuxHeader; using Protocol3::FEventHeader;`

#### struct `UE::Trace::Protocol4::EKnownEventUids`  
`struct EKnownEventUids`  
_L28-44_
- L30 _public member_ `static const uint16 Flag_TwoByteUid = 1 << 0;`
- L31 _public member_ `static const uint16 _UidShift = 1;`
- L41 _public member_ `static const uint16 User = _WellKnownNum;`
- L42 _public member_ `static const uint16 Max = (1 << (16 - _UidShift)) - 1;`
- L43 _public member_ `static const uint16 Invalid = Max;`

#### enum `UE::Trace::Protocol4::EKnownEventUids::(anonymous)`  
``  
_L33-40_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol4` (scope `UE::Trace`)
- L34 _enumerator_ `NewEvent = 0` (scope `UE::Trace::Protocol4::EKnownEventUids::__anona420ebc70103`)
- L35 _enumerator_ `EnterScope` (scope `UE::Trace::Protocol4::EKnownEventUids::__anona420ebc70103`)
- L36 _enumerator_ `EnterScope_T` (scope `UE::Trace::Protocol4::EKnownEventUids::__anona420ebc70103`)
- L37 _enumerator_ `LeaveScope` (scope `UE::Trace::Protocol4::EKnownEventUids::__anona420ebc70103`)
- L38 _enumerator_ `LeaveScope_T` (scope `UE::Trace::Protocol4::EKnownEventUids::__anona420ebc70103`)
- L39 _enumerator_ `_WellKnownNum` (scope `UE::Trace::Protocol4::EKnownEventUids::__anona420ebc70103`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol5.h` (Public)


#### enum `UE::Trace::Protocol5::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 5 }; using Protocol4::EFieldType; using Protocol4::FNewEventEvent; using Protocol4::EEventFlags;`

#### struct `UE::Trace::Protocol5::EKnownEventUids`  
`struct EKnownEventUids`  
_L25-52_
- L27 _public member_ `static const uint16 Flag_TwoByteUid = 1 << 0;`
- L28 _public member_ `static const uint16 _UidShift = 1;`
- L49 _public member_ `static const uint16 User = _WellKnownNum;`
- L50 _public member_ `static const uint16 Max = (1 << (16 - _UidShift)) - 1;`
- L51 _public member_ `static const uint16 Invalid = Max;`

#### enum `UE::Trace::Protocol5::EKnownEventUids::(anonymous)`  
``  
_L30-48_

#### struct `UE::Trace::Protocol5::FEventHeader`  
`struct FEventHeader`  
_L55-59_
- L57 _public member_ `uint16 Uid;`
- L58 _public member_ `uint8 Data[];`

#### struct `UE::Trace::Protocol5::FImportantEventHeader`  
`struct FImportantEventHeader`  
_L63-68_
- L65 _public member_ `uint16 Uid;`
- L66 _public member_ `uint16 Size;`
- L67 _public member_ `uint8 Data[];`

#### struct `UE::Trace::Protocol5::FEventHeaderSync`  
`struct FEventHeaderSync`  
_L73-79_
- L75 _public member_ `uint16 Uid;`
- L76 _public member_ `uint16 SerialLow;` — 24-bit
- L77 _public member_ `uint8 SerialHigh;` — serial no.
- L78 _public member_ `uint8 Data[];`

#### struct `UE::Trace::Protocol5::FAuxHeader`  
`struct FAuxHeader`  
_L84-106_
- L105 _public member_ `uint8 Data[];`

#### enum `UE::Trace::Protocol5::FAuxHeader::(anonymous)`  
``  
_L87-93_

#### union `UE::Trace::Protocol5::FAuxHeader::(anonymous)`  
``  
_L96-104_

#### struct `UE::Trace::Protocol5::FAuxHeader::__anona420f008030a::(anonymous)`  
``  
_L98-102_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol5` (scope `UE::Trace`)
- L31 _enumerator_ `NewEvent = 0` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L32 _enumerator_ `AuxData` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L33 _enumerator_ `_AuxData_Unused` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L34 _enumerator_ `AuxDataTerminal` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L35 _enumerator_ `EnterScope` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L36 _enumerator_ `LeaveScope` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L37 _enumerator_ `_Unused6` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L38 _enumerator_ `_Unused7` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L39 _enumerator_ `EnterScope_T` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L40 _enumerator_ `_EnterScope_T_Unused0` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`) — reserved for variable
- L41 _enumerator_ `_EnterScope_T_Unused1` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`) — length timestamps
- L42 _enumerator_ `_EnterScope_T_Unused2` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L43 _enumerator_ `LeaveScope_T` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L44 _enumerator_ `_LeaveScope_T_Unused0` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L45 _enumerator_ `_LeaveScope_T_Unused1` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L46 _enumerator_ `_LeaveScope_T_Unused2` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L47 _enumerator_ `_WellKnownNum` (scope `UE::Trace::Protocol5::EKnownEventUids::__anona420f0080103`)
- L88 _enumerator_ `FieldShift = 8` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f0080203`)
- L89 _enumerator_ `FieldBits = 5` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f0080203`)
- L90 _enumerator_ `FieldMask = (1 << FieldBits) - 1` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f0080203`)
- L91 _enumerator_ `SizeShift = FieldShift + FieldBits` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f0080203`)
- L92 _enumerator_ `SizeLimit = 1 << (32 - SizeShift)` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f0080203`)
- L99 _member_ `uint8 Uid;` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f008030a::__anona420f0080408`)
- L100 _member_ `uint8 FieldIndex_Size;` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f008030a::__anona420f0080408`)
- L101 _member_ `uint16 Size;` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f008030a::__anona420f0080408`)
- L103 _member_ `uint32 Pack;` (scope `UE::Trace::Protocol5::FAuxHeader::__anona420f008030a`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol6.h` (Public)


#### enum `UE::Trace::Protocol6::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 6 }; using Protocol5::EFieldType; using Protocol5::FEventHeader; using Protocol5::FImportantEventHeader; using Protocol5::FEventHeaderSync; using Protocol5::FAuxHeader;`

#### enum `UE::Trace::Protocol6::EEventFlags`  
`enum class EEventFlags : uint8`  
_L28-35_
- L30 _public enumerator_ `None = 0`
- L31 _public enumerator_ `Important = 1 << 0`
- L32 _public enumerator_ `MaybeHasAux = 1 << 1`
- L33 _public enumerator_ `NoSync = 1 << 2`
- L34 _public enumerator_ `Definition = 1 << 3`

#### enum `UE::Trace::Protocol6::EFieldFamily`  
`enum EFieldFamily : uint8`  
_L38-43_
- L40 _public enumerator_ `Regular`
- L41 _public enumerator_ `Reference`
- L42 _public enumerator_ `DefinitionId`

#### struct `UE::Trace::Protocol6::FNewEventField`  
`struct FNewEventField`  
_L46-74_
- L48 _public member_ `uint8 FieldType;` — EFieldFamily
- L49 _public member_ `uint8 Unused;`

#### union `UE::Trace::Protocol6::FNewEventField::(anonymous)`  
``  
_L51-73_

#### struct `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::(anonymous)`  
``  
_L53-58_

#### struct `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::(anonymous)`  
``  
_L60-65_

#### struct `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::(anonymous)`  
``  
_L67-72_

#### struct `UE::Trace::Protocol6::FNewEventEvent`  
`struct FNewEventEvent`  
_L77-85_
- L79 _public member_ `uint16 EventUid;`
- L80 _public member_ `uint8 FieldCount;`
- L81 _public member_ `uint8 Flags;` — EEventFlags
- L82 _public member_ `uint8 LoggerNameSize;`
- L83 _public member_ `uint8 EventNameSize;`
- L84 _public member_ `FNewEventField Fields[];`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol6` (scope `UE::Trace`)
- L54 _member_ `uint16 Offset;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490208`)
- L55 _member_ `uint16 Size;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490208`)
- L56 _member_ `uint8 TypeInfo;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490208`) — EFieldType
- L57 _member_ `uint8 NameSize;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490208`)
- L58 _member_ `} Regular;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a`)
- L61 _member_ `uint16 Offset;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490308`)
- L62 _member_ `uint16 RefUid;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490308`)
- L63 _member_ `uint8 TypeInfo;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490308`) — EFieldType
- L64 _member_ `uint8 NameSize;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490308`)
- L65 _member_ `} Reference;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a`)
- L68 _member_ `uint16 Offset;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490408`)
- L69 _member_ `uint16 Unused1;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490408`)
- L70 _member_ `uint8 Unused2;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490408`)
- L71 _member_ `uint8 TypeInfo;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a::__anona420f4490408`) — EFieldType
- L72 _member_ `} DefinitionId;` (scope `UE::Trace::Protocol6::FNewEventField::__anona420f449010a`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Protocols/Protocol7.h` (Public)


#### enum `UE::Trace::Protocol7::EProtocol`  
`enum EProtocol : uint8`  
_L17-17_
- L17 _public enumerator_ `enum EProtocol : uint8 { Id = 7 }; using Protocol6::EFieldType; using Protocol6::FEventHeader; using Protocol6::FImportantEventHeader; using Protocol6::FEventHeaderSync; using Protocol6::FAuxHeader;`

#### struct `UE::Trace::Protocol7::EKnownEventUids`  
`struct EKnownEventUids`  
_L31-59_
- L33 _public member_ `static const uint16 Flag_TwoByteUid = 1 << 0;`
- L34 _public member_ `static const uint16 _UidShift = 1;`
- L55 _public member_ `static const uint16 User = _WellKnownNum;`
- L56 _public member_ `static const uint16 Max = (1 << (16 - _UidShift)) - 1;`
- L57 _public member_ `static const uint16 Invalid = Max;`

#### enum `UE::Trace::Protocol7::EKnownEventUids::(anonymous)`  
``  
_L36-54_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L13 _namespace_ `namespace Protocol7` (scope `UE::Trace`)
- L37 _enumerator_ `NewEvent = 0` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — same as Protocol5
- L38 _enumerator_ `AuxData` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — same as Protocol5
- L39 _enumerator_ `_Unused0` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`)
- L40 _enumerator_ `AuxDataTerminal` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — same as Protocol5
- L41 _enumerator_ `EnterScope` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — same as Protocol5
- L42 _enumerator_ `LeaveScope` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — same as Protocol5
- L43 _enumerator_ `EnterScope_TA` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — new in Protocol7, absolute timestamps
- L44 _enumerator_ `LeaveScope_TA` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — new in Protocol7, absolute timestamps
- L45 _enumerator_ `EnterScope_TB` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — new in Protocol7, timestamps relative to BaseTimestamp
- L46 _enumerator_ `LeaveScope_TB` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — new in Protocol7, timestamps relative to BaseTimestamp
- L47 _enumerator_ `_Unused1` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`)
- L48 _enumerator_ `_Unused2` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`)
- L49 _enumerator_ `_Unused3` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`)
- L50 _enumerator_ `_Unused4` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`)
- L51 _enumerator_ `_Unused5` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`)
- L52 _enumerator_ `_Unused6` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`)
- L53 _enumerator_ `_WellKnownNum` (scope `UE::Trace::Protocol7::EKnownEventUids::__anona420f88a0103`) — same as Protocol5

### `Source/Runtime/TraceLog/Public/Trace/Detail/Trace.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Trace` (scope `UE`)
- L25 _macro_ `#define TRACE_PRIVATE_EXPAND(x) x`
- L33 _macro_ `#define TRACE_PRIVATE_STATISTICS UE_TRACE_STATISTICS_ENABLED`
- L35 _macro_ `#define TRACE_PRIVATE_CHANNEL_DEFAULT_ARGS false, "None"`
- L37 _macro_ `#define TRACE_PRIVATE_CHANNEL_DECLARE(LinkageType, ChannelName, ChannelClass) \`
- L42 _macro_ `#define TRACE_PRIVATE_CHANNEL_IMPL(ChannelName, ...) \`
- L52 _macro_ `#define TRACE_PRIVATE_CHANNEL(ChannelName, ...) \`
- L56 _macro_ `#define TRACE_PRIVATE_CHANNEL_CUSTOM(ChannelName, ChannelClass, ...) \`
- L60 _macro_ `#define TRACE_PRIVATE_CHANNEL_DEFINE(ChannelName, ...) \`
- L64 _macro_ `#define TRACE_PRIVATE_CHANNEL_CUSTOM_DEFINE(ChannelName, ChannelClass, ...) \`
- L68 _macro_ `#define TRACE_PRIVATE_CHANNEL_EXTERN(ChannelName, ...) \`
- L71 _macro_ `#define TRACE_PRIVATE_CHANNEL_CUSTOM_EXTERN(ChannelName, ChannelClass, ...) \`
- L74 _macro_ `#define TRACE_PRIVATE_CHANNELEXPR_IS_ENABLED(ChannelsExpr) \`
- L77 _macro_ `#define TRACE_PRIVATE_EVENT_DEFINE(LoggerName, EventName) \`
- L81 _macro_ `#define TRACE_PRIVATE_EVENT_BEGIN(LoggerName, EventName, ...) \`
- L85 _macro_ `#define TRACE_PRIVATE_EVENT_BEGIN_EXTERN(LoggerName, EventName, ...) \`
- L89 _macro_ `#define TRACE_PRIVATE_EVENT_BEGIN_IMPL(LoggerName, EventName, ...) \`
- L132 _macro_ `#define TRACE_PRIVATE_EVENT_FIELD(FieldType, FieldName) \`
- L143 _macro_ `#define TRACE_PRIVATE_EVENT_REFFIELD(RefLogger, RefEventType, FieldName) \`
- L155 _macro_ `#define TRACE_PRIVATE_EVENT_END() \`
- L177 _macro_ `#define TRACE_PRIVATE_LOG_PRELUDE(EnterFunc, LoggerName, EventName, ChannelsExpr, ...) \`
- L183 _macro_ `#define TRACE_PRIVATE_LOG_PRELUDE_CONDITIONAL(EnterFunc, LoggerName, EventName, ChannelsExpr, Condition, ...) \`
- L187 _macro_ `#define TRACE_PRIVATE_LOG_EPILOG() \`
- L190 _macro_ `#define TRACE_PRIVATE_LOG(LoggerName, EventName, ChannelsExpr, ...) \`
- L194 _macro_ `#define TRACE_PRIVATE_LOG_SCOPED(LoggerName, EventName, ChannelsExpr, ...) \`
- L200 _macro_ `#define TRACE_PRIVATE_LOG_SCOPED_CONDITIONAL(LoggerName, EventName, ChannelsExpr, Condition, ...) \`
- L206 _macro_ `#define TRACE_PRIVATE_LOG_SCOPED_T(LoggerName, EventName, ChannelsExpr, ...) \`
- L212 _macro_ `#define TRACE_PRIVATE_LOG_SCOPED_T_CONDITIONAL(LoggerName, EventName, ChannelsExpr, Condition, ...) \`
- L218 _macro_ `#define TRACE_PRIVATE_GET_DEFINITION_TYPE_ID(LoggerName, EventName) \`
- L221 _macro_ `#define TRACE_PRIVATE_LOG_DEFINITION(LoggerName, EventName, Id, ChannelsExpr, ...) \`
- L232 _macro_ `#define TRACE_PRIVATE_NOP_CHANNEL(ChannelName, ...)`
- L234 _macro_ `#define TRACE_PRIVATE_NOP_CHANNEL_CUSTOM(ChannelName, ChannelClass, ...)`
- L236 _macro_ `#define TRACE_PRIVATE_NOP_CHANNEL_EXTERN(ChannelName, ...)`
- L238 _macro_ `#define TRACE_PRIVATE_NOP_CHANNEL_CUSTOM_EXTERN(ChannelName, ChannelClass, ...)`
- L240 _macro_ `#define TRACE_PRIVATE_NOP_CHANNEL_DEFINE(ChannelName, ...)`
- L242 _macro_ `#define TRACE_PRIVATE_NOP_CHANNEL_CUSTOM_DEFINE(ChannelName, ChannelClass, ...)`
- L244 _macro_ `#define TRACE_PRIVATE_NOP_CHANNELEXPR_IS_ENABLED(ChannelsExpr) \`
- L247 _macro_ `#define TRACE_PRIVATE_NOP_EVENT_DEFINE(LoggerName, EventName) \`
- L250 _macro_ `#define TRACE_PRIVATE_NOP_EVENT_BEGIN(LoggerName, EventName, ...) \`
- L253 _macro_ `#define TRACE_PRIVATE_NOP_EVENT_BEGIN_EXTERN(LoggerName, EventName, ...) \`
- L257 _macro_ `#define TRACE_PRIVATE_NOP_EVENT_BEGIN_IMPL(LoggerName, EventName) \`
- L280 _macro_ `#define TRACE_PRIVATE_NOP_EVENT_FIELD(FieldType, FieldName) \`
- L283 _macro_ `#define TRACE_PRIVATE_NOP_EVENT_REFFIELD(RefLogger, RefEventType, FieldName) \`
- L286 _macro_ `#define TRACE_PRIVATE_NOP_EVENT_END() \`
- L289 _macro_ `#define TRACE_PRIVATE_NOP_LOG(LoggerName, EventName, ...) \`
- L293 _macro_ `#define TRACE_PRIVATE_NOP_LOG_SCOPED(LoggerName, EventName, ...) \`
- L297 _macro_ `#define TRACE_PRIVATE_NOP_LOG_SCOPED_CONDITIONAL(LoggerName, EventName, ...) \`
- L301 _macro_ `#define TRACE_PRIVATE_NOP_LOG_SCOPED_T(LoggerName, EventName, ...) \`
- L305 _macro_ `#define TRACE_PRIVATE_NOP_LOG_SCOPED_T_CONDITIONAL(LoggerName, EventName, ...) \`
- L309 _macro_ `#define TRACE_PRIVATE_NOP_GET_DEFINITION_TYPE_ID(LoggerName, EventName) \`
- L312 _macro_ `#define TRACE_PRIVATE_NOP_LOG_DEFINITION(LoggerName, EventName, Id, ChannelsExpr, ...) \`

### `Source/Runtime/TraceLog/Public/Trace/Detail/Transport.h` (Public)


#### enum `UE::Trace::ETransport`  
`enum ETransport : uint8`  
_L11-19_
- L13 _public enumerator_ `_Unused = 0`
- L14 _public enumerator_ `Raw = 1`
- L15 _public enumerator_ `Packet = 2`
- L16 _public enumerator_ `TidPacket = 3`
- L17 _public enumerator_ `TidPacketSync = 4`
- L18 _public enumerator_ `Active = TidPacketSync`

#### enum `UE::Trace::ETransportTid`  
`enum ETransportTid : uint32`  
_L22-32_
- L24 _public enumerator_ `Events = 0` — used to describe events
- L25 _public enumerator_ `Internal = 1` — events to make the trace stream function
- L26 _public enumerator_ `Importants = Internal` — important/cached events
- L27 _public enumerator_ `Bias` — [Bias,End] = threads. Note bias can't be..
- L29 _public enumerator_ `End = 0x3ff0` — two msbs are user for packet markers
- L30 _public enumerator_ `PseudoImportants = 0x3ffe` — see Writer_CallbackOnConnect()
- L31 _public enumerator_ `Sync = 0x3fff` — see Writer_SendSync()

#### struct `UE::Trace::Private::FTidPacketBase`  
`struct FTidPacketBase`  
_L40-52_
- L50 _public member_ `uint16 PacketSize;`
- L51 _public member_ `uint16 ThreadId;`

#### enum `UE::Trace::Private::FTidPacketBase::(anonymous)`  
``  
_L43-48_

#### struct `UE::Trace::Private::TTidPacket`  
`template <uint32 DataSize> struct TTidPacket : public FTidPacketBase`  
_L55-59_
- inherits: `FTidPacketBase`
- L58 _public member_ `uint8 Data[DataSize];`

#### struct `UE::Trace::Private::TTidPacketEncoded`  
`template <uint32 DataSize> struct TTidPacketEncoded : public FTidPacketBase`  
_L62-67_
- inherits: `FTidPacketBase`
- L65 _public member_ `uint16 DecodedSize;`
- L66 _public member_ `uint8 Data[DataSize];`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L36 _namespace_ `namespace Private` (scope `UE::Trace`)
- L44 _enumerator_ `EncodedMarker = 0x8000` (scope `UE::Trace::Private::FTidPacketBase::__anon03e208fa0103`)
- L45 _enumerator_ `PartialMarker = 0x4000` (scope `UE::Trace::Private::FTidPacketBase::__anon03e208fa0103`) — now unused. fragmented aux-data has an event header
- L46 _enumerator_ `Verification = 0x4000` (scope `UE::Trace::Private::FTidPacketBase::__anon03e208fa0103`) — when set the packet data is immediately followed by 64-bit verification value, see UE_TRACE_PACKET_VERIFICATION
- L47 _enumerator_ `ThreadIdMask = PartialMarker - 1` (scope `UE::Trace::Private::FTidPacketBase::__anon03e208fa0103`)
- L69 _typedef_ `using FTidPacket = TTidPacket<0>;` (scope `UE::Trace::Private`)
- L70 _typedef_ `using FTidPacketEncoded = TTidPacketEncoded<0>;` (scope `UE::Trace::Private`)

### `Source/Runtime/TraceLog/Public/Trace/Detail/Writer.inl` (Public)


#### struct `UE::Trace::Private::FWriteBuffer`  
`struct FWriteBuffer`  
_L18-35_
- desc: Structure for managing event data buffers. Most fields are only accessed by the one thread; consuming thread (e.g. worker thread) or producing thread (e.g. any thread tracing data). Volatile fields are used to safely communicate commited data and buffer usage.
- L20 _public prototype_ `void MoveCursor(uint16 Bytes);`
- L21 _public prototype_ `void SetCursor(uint8* Ptr);`
- L22 _public prototype_ `uint8* ReadCursor() const;`
- L24 _public member_ `uint8 Overflow[6];`
- L25 _public member_ `uint16 CursorMaskInv;`
- L26 _public member_ `uint64 PrevTimestamp;`
- L27 _public member_ `uint16 Size;`
- L28 _public member_ `uint16 ThreadId;`
- L29 _public member_ `int32 volatile EtxOffset;` — Shared access (producer and consumer)
- L30 _public member_ `FWriteBuffer* __restrict NextThread;`
- L31 _public member_ `FWriteBuffer* volatile NextBuffer;` — Shared access
- L32 _public member_ `uint8* __restrict volatile Committed;` — Shared access
- L33 _public member_ `uint8* __restrict Reaped;`
- L34 _public member_ `uint8* __restrict Cursor;`
- L38 _function_ `inline void FWriteBuffer::MoveCursor(uint16 Bytes)`
- L44 _function_ `inline void FWriteBuffer::SetCursor(uint8* Ptr)`
- L54 _function_ `inline uint8* FWriteBuffer::ReadCursor() const`

#### struct `UE::Trace::Private::FTlsState`  
`struct FTlsState`  
_L61-65_
- L63 _public member_ `FWriteBuffer* WriteBuffer;`
- L64 _public member_ `NextBufferFunc* NextBufferFn;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Trace` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Trace`)
- L60 _typedef_ `using NextBufferFunc = struct FWriteBuffer*(struct FWriteBuffer*);` (scope `UE::Trace::Private`)
- L68 _prototype_ `uint64 TimeGetTimestamp();` (scope `UE::Trace::Private`)
- L69 _prototype_ `FWriteBuffer* Writer_NextBuffer(FWriteBuffer*);` (scope `UE::Trace::Private`)
- L70 _prototype_ `FWriteBuffer* Writer_GetBuffer();` (scope `UE::Trace::Private`)
- L71 _prototype_ `bool Writer_OnConnectActivate(FTlsState& OutPrevState);` (scope `UE::Trace::Private`)
- L72 _prototype_ `void Writer_OnConnectDeactivate(const FTlsState& PrevState);` (scope `UE::Trace::Private`)
- L76 _externvar_ `extern thread_local FTlsState GTlsState;` (scope `UE::Trace::Private`)
- L77 _function_ `inline FWriteBuffer* Writer_GetBuffer()` (scope `UE::Trace::Private`)
- L84 _function_ `inline uint64 Writer_GetTimestamp(FWriteBuffer* Buffer)` (scope `UE::Trace::Private`)

### `Source/Runtime/TraceLog/Public/Trace/Trace.h` (Public)


#### enum `UE::Trace::AnsiString`  
`enum AnsiString`  
_L52-52_
- desc: Field types

#### enum `UE::Trace::WideString`  
`enum WideString`  
_L53-53_

#### struct `UE::Trace::TEventRef`  
`template<typename IdType> struct TEventRef`  
_L57-84_
- desc: Reference to a definition event.
- L59 _public typedef_ `using ReferenceType = IdType;`
- L61 _public function_ `TEventRef(IdType InId, uint32 InTypeId) : Id(InId) , RefTypeId(InTypeId)`
- L67 _public member_ `IdType Id;`
- L68 _public member_ `uint32 RefTypeId;`
- L70 _public function_ `uint64 GetHash() const`
- L83 _private prototype_ `TEventRef() = delete;`

#### enum `UE::Trace::EMessageType`  
`enum class EMessageType : uint8`  
_L97-128_
- L99 _public enumerator_ `Reserved = 0`
- L100 _public enumerator_ `VeryVerbose`
- L101 _public enumerator_ `Verbose`
- L103 _public enumerator_ `Log` — Add to log
- L105 _public enumerator_ `Info = Log` — For backwards compatibility
- L107 _public enumerator_ `Display` — Display in console or similar
- L109 _public enumerator_ `WarningStart = 0x04` — Warnings to notify user
- L112 _public enumerator_ `ErrorStart = 0x10` — Errors are critical to the user, but application can continue to run.
- L113 _public enumerator_ `WriteError`
- L114 _public enumerator_ `ReadError`
- L115 _public enumerator_ `ConnectError`
- L116 _public enumerator_ `ListenError`
- L117 _public enumerator_ `EstablishError`
- L118 _public enumerator_ `FileOpenError`
- L119 _public enumerator_ `WriterError`
- L120 _public enumerator_ `CompressionError`
- L121 _public enumerator_ `PanicError`
- L122 _public enumerator_ `SecureInitError`
- L123 _public enumerator_ `SecureSocketError`
- L125 _public enumerator_ `FatalStart = 0x40` — Fatal errors should cause application to stop
- L126 _public enumerator_ `GenericFatal`
- L127 _public enumerator_ `OOMFatal`

#### struct `UE::Trace::FMessageEvent`  
`struct FMessageEvent`  
_L130-138_
- L133 _public member_ `EMessageType Type;` — Type of message
- L135 _public member_ `const char* TypeStr;` — Type of message stringified
- L137 _public member_ `const char* Description;` — Clarifying message, may be null for some message types. Pointer only valid during callback.

#### struct `UE::Trace::FInitializeDesc`  
`struct FInitializeDesc`  
_L147-160_
- L149 _public member_ `uint32 TailSizeBytes = UE_TRACE_DEFAULT_TAIL_SIZE;` — set to 0 when minimal tracing
- L150 _public member_ `uint32 ThreadSleepTimeInMS = 0;`
- L151 _public member_ `uint32 BlockPoolMaxSize = UE_TRACE_BLOCK_POOL_MAXSIZE;`
- L152 _public member_ `bool bUseWorkerThread = true;`
- L153 _public member_ `bool bUseImportantCache = true;`
- L154 _public member_ `uint32 SessionGuid[4] = {0,0,0,0};` — leave as zero to generate random
- L155 _public member_ `OnConnectFunc* OnConnectionFunc = nullptr;`
- L156 _public member_ `OnUpdateFunc* OnUpdateFunc = nullptr;`
- L157 _public member_ `OnScopeBeginFunc* OnScopeBeginFunc = nullptr;`
- L158 _public member_ `OnScopeEndFunc* OnScopeEndFunc = nullptr;`
- L159 _public member_ `OnCloseFunc* OnCloseFunc = nullptr;`

#### struct `UE::Trace::FChannelInfo`  
`struct FChannelInfo`  
_L164-171_
- L166 _public member_ `const ANSICHAR* Name;`
- L167 _public member_ `const ANSICHAR* Desc;`
- L168 _public member_ `FChannelId Id;`
- L169 _public member_ `bool bIsEnabled;`
- L170 _public member_ `bool bIsReadOnly;`

#### struct `UE::Trace::FStatistics`  
`struct FStatistics`  
_L237-252_
- L239 _public member_ `uint64 BytesSent = 0;` — Bytes sent/written to the current endpoint
- L240 _public member_ `uint64 BytesTraced = 0;` — Bytes sent/written to the current endpoint (uncompressed)
- L241 _public member_ `uint64 BytesEmitted = 0;` — Bytes emitted but potentially not yet written
- L242 _public member_ `uint64 MemoryUsed = 0;` — Memory allocated by TraceLog allocator functions
- L243 _public member_ `uint64 BlockPoolAllocated = 0;` — Memory allocated for the (TLS) block pool.
- L244 _public member_ `uint32 BlockPoolFreeBlocks = 0;` — Number of available blocks
- L245 _public member_ `uint32 BlockPoolAllocatedBlocks= 0;` — Number of allocated blocks
- L246 _public member_ `uint32 SharedBufferAllocated = 0;` — Memory allocated for shared buffers
- L247 _public member_ `uint32 FixedBufferAllocated = 0;` — Memory allocated for fixed buffers (tail, send)
- L248 _public member_ `uint32 CacheAllocated = 0;` — Total memory allocated in cache buffers
- L249 _public member_ `uint32 CacheUsed = 0;` — Used cache memory; Important-marked events are stored in the cache.
- L250 _public member_ `uint32 CacheWaste = 0;` — Unused memory from retired cache buffers
- L251 _public member_ `uint32 ThreadRegistryAllocated = 0;` — Memory allocated for ThreadInfo/GroupBegin event data stored in the ThreadRegistry

#### struct `UE::Trace::FSendFlags`  
`struct FSendFlags`  
_L254-259_
- L256 _public member_ `static const uint16 None = 0;`
- L257 _public member_ `static const uint16 ExcludeTail = 1 << 0;` — do not send the tail of historical events
- L258 _public member_ `static const uint16 _Reserved = 1 << 15;` — this bit is used internally

#### enum `UE::Trace::ESecureTraceMode`  
`enum class ESecureTraceMode : uint8`  
_L463-468_
- L465 _public enumerator_ `SelfSigned`
- L466 _public enumerator_ `CertificateFile`
- L467 _public enumerator_ `PreSharedKeys`

#### struct `UE::Trace::FSecureTraceSettings`  
`struct FSecureTraceSettings`  
_L477-498_
- desc: Options for initializing secure tracing. Supports three modes of operation depending on what values are set. * External certificate + private key and optional authentication token. * Self signed certificate and optional authentication token. * Pre-shared keys
- L482 _public member_ `ESecureTraceMode Mode = ESecureTraceMode::SelfSigned;` — Desired operational mode.
- L487 _public member_ `uint16 Port = 0;` — Port used to listen for peer connections.
- L492 _public member_ `const ANSICHAR* CertificatePath = nullptr;` — Path to certificate file. Only used if Mode is CertificateFile.
- L497 _public member_ `const ANSICHAR* PrivateKeyPath = nullptr;` — Path to private key. Only used if Mode is CertificateFile.

#### struct `UE::Trace::FSecureTraceOptions`  
`struct FSecureTraceOptions`  
_L525-553_
- desc: Options for a secure trace connection. Allows to set a unique authorization token and identity where applicable.
- L530 _public member_ `const uint8* AuthorizationToken = nullptr;` — AuthorizationToken that peer will use to connect. Used as pre-shared keys if Mode is PreSharedKeys
- L535 _public member_ `const char* Identity = nullptr;` — Identity string expected. Used when Mode is PreSharedKeys. String does not need to outlive function call.
- L540 _public member_ `uint32 AuthorizationTokenSize = 0u;` — Expected authorization token size in bytes. Must be set if AuthorizationToken is set.
- L545 _public member_ `bool bCanReceive = false;` — If the connection can receive data.
- L552 _public member_ `uint32 TimeoutMs = 0u;` — Timeout in ms for connect and handshakes. If peer doesn't connect or supply handshake within this time connection is closed. Zero is interpreted as no timeouts should be applied.

#### Free symbols / members of external scopes

- L9 _macro_ `# define UE_TRACE_IMPL(...)`
- L10 _macro_ `# define UE_TRACE_API TRACELOG_API`
- L12 _macro_ `# define UE_TRACE_IMPL(...) { return __VA_ARGS__; }`
- L13 _macro_ `# define UE_TRACE_API inline`
- L20 _macro_ `# define TRACE_IMPL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_##Macro(__VA_ARGS__))`
- L22 _macro_ `# define TRACE_IMPL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_NOP_##Macro(__VA_ARGS__))`
- L26 _macro_ `# define TRACE_IMPL_MINIMAL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_##Macro(__VA_ARGS__))`
- L28 _macro_ `# define TRACE_IMPL_MINIMAL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_NOP_##Macro(__VA_ARGS__))`
- L34 _macro_ `# define TRACE_IMPL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_##Macro)(__VA_ARGS__)`
- L36 _macro_ `# define TRACE_IMPL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_NOP_##Macro)(__VA_ARGS__)`
- L40 _macro_ `# define TRACE_IMPL_MINIMAL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_##Macro)(__VA_ARGS__)`
- L42 _macro_ `# define TRACE_IMPL_MINIMAL(Macro, ...) TRACE_PRIVATE_EXPAND(TRACE_PRIVATE_NOP_##Macro)(__VA_ARGS__)`
- L48 _namespace_ `namespace UE`
- L49 _namespace_ `namespace Trace` (scope `UE`)
- L86 _typedef_ `typedef TEventRef<uint8> FEventRef8;` (scope `UE::Trace`)
- L87 _typedef_ `typedef TEventRef<uint16> FEventRef16;` (scope `UE::Trace`)
- L88 _typedef_ `typedef TEventRef<uint32> FEventRef32;` (scope `UE::Trace`)
- L89 _typedef_ `typedef TEventRef<uint64> FEventRef64;` (scope `UE::Trace`)
- L92 _function_ `template<typename IdType> TEventRef<IdType> MakeEventRef(IdType InId, uint32 InTypeId)` (scope `UE::Trace`)
- L140 _typedef_ `using OnMessageFunc = void(const FMessageEvent&);` (scope `UE::Trace`)
- L141 _typedef_ `using OnConnectFunc = void(void);` (scope `UE::Trace`)
- L142 _typedef_ `using OnUpdateFunc = void(void);` (scope `UE::Trace`)
- L143 _typedef_ `using OnCloseFunc = void(void);` (scope `UE::Trace`)
- L144 _typedef_ `using OnScopeBeginFunc = void(const ANSICHAR*);` (scope `UE::Trace`)
- L145 _typedef_ `using OnScopeEndFunc = void(void);` (scope `UE::Trace`)
- L162 _typedef_ `typedef uint32 FChannelId;` (scope `UE::Trace`)
- L181 _typedef_ `typedef void* AllocFunc(SIZE_T Size, uint32 Alignment);` (scope `UE::Trace`) — Allocate memory callback @param Size Size to allocate @param Alignment Alignment of memory @return Pointer to allocated memory
- L188 _typedef_ `typedef void FreeFunc(void* Ptr, SIZE_T Size);` (scope `UE::Trace`) — Free memory callback @param Ptr Memory to free @param Size Size of memory to free
- L196 _typedef_ `typedef void ChannelIterFunc(const ANSICHAR* Name, bool State, void* User);` (scope `UE::Trace`) — The callback provides information about a channel and a user provided pointer. @param Name Name of channel @param State Enabled state of channel @param User User data passed to the callback
- L204 _typedef_ `typedef bool ChannelIterCallback(const FChannelInfo& Info, void* );` (scope `UE::Trace`) — The callback provides information about a channel and a user provided pointer. @param Info Information about the channel @param User User data passed to the callback @return Returning false from the callback will stop the enumeration
- L213 _typedef_ `typedef bool IoWriteFunc(UPTRINT Handle, const void* Data, uint32 Size);` (scope `UE::Trace`) — User defined write callback. @param Handle User defined handle passed to the function @param Data Pointer to data to write @param Size Size of data to write @return True if all data could be written correctly, false if error occurred.
- L219 _typedef_ `typedef void IoCloseFunc(UPTRINT Handle);` (scope `UE::Trace`) — User defined close callback. @param Handle User defined handle passed to the function
- L227 _typedef_ `typedef bool IoUpdateFunc(UPTRINT Handle);` (scope `UE::Trace`) — User defined update  callback. @param Handle User defined handle passed to the function @return True while connection is active, false if closed or error state occurred
- L235 _typedef_ `typedef bool IoIsReadyFunc(UPTRINT Handle);` (scope `UE::Trace`) — User defined is ready callback. Used to check if a pending connection is ready to be used. @param Handle User defined handle passed to the function @return True if ready, false if further waiting is needed.
- L267 _prototype_ `void SetMemoryHooks(AllocFunc Alloc, FreeFunc Free) UE_TRACE_IMPL();` (scope `UE::Trace`) — Set optional allocation and free methods to use. If not set TraceLog will fall back to default platform allocation methods. @param Alloc Callback for allocations @param Free Callback for free
- L273 _prototype_ `void SetMessageCallback(OnMessageFunc* MessageFunc) UE_TRACE_IMPL();` (scope `UE::Trace`) — Set optional callback to use for critical messages. See \ref OnMessageFunc for details. @param MessageFunc Function to call for critical messages
- L279 _prototype_ `void SetUpdateCallback(OnUpdateFunc* UpdateFunc) UE_TRACE_IMPL();` (scope `UE::Trace`) — Set optional on update callbacks. If set issued after every update and once after initialization. @param UpdateFunc Function to call after every update
- L285 _prototype_ `void Initialize(const FInitializeDesc& Desc) UE_TRACE_IMPL();` (scope `UE::Trace`) — Initialize TraceLog library. @param Desc Initialization options
- L290 _prototype_ `void StartWorkerThread() UE_TRACE_IMPL();` (scope `UE::Trace`) — Manually start worker thread if library is initialized without worker thread.
- L296 _prototype_ `void Exit() UE_TRACE_IMPL();` (scope `UE::Trace`) — Call when application is exiting. Notifies TraceLog that the worker thread can disappear at any time and clears block pool limits. Tracing is still possible.
- L302 _prototype_ `void Shutdown() UE_TRACE_IMPL();` (scope `UE::Trace`) — Shuts down the library completely and frees resources. After this tracing will not be possible.
- L308 _prototype_ `void Panic() UE_TRACE_IMPL();` (scope `UE::Trace`) — Puts TraceLog in a critical failure stats. Disables all tracing by muting all channels. Tracing will be totally disabled for the remainder of the process lifetime.
- L314 _prototype_ `void Update() UE_TRACE_IMPL();` (scope `UE::Trace`) — Manually update TraceLog if no worker thread is running. Only one thread (including the worker thread) is able to enter the update method at any point.
- L320 _prototype_ `void GetStatistics(FStatistics& Out) UE_TRACE_IMPL();` (scope `UE::Trace`) — Fetches tracked telemetry from the library. @param Out Pointer to struct where telemetry values will be written to.
- L330 _prototype_ `bool SendTo(const TCHAR* Host, uint32 Port=0, uint16 Flags=FSendFlags::None) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Setup TraceLog to output to remote host using a socket connection, to take effect next update. Will fail if another pending output has been queued or the host is unreachable. @param Host Target hostname or ip @param Port Target port @param Flags Options for the connection @return True on successful connection to host, false otherwise
- L339 _prototype_ `bool WriteTo(const TCHAR* Path, uint16 Flags=FSendFlags::None) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Setup TraceLog to output to a new or existing file, to take effect next update. Will fail if another pending output has been queued or if the file location is not writeable. @param Path Target path @param Flags Options for the connection @return True if the file could be opened or created correctly, false otherwise
- L349 _prototype_ `bool RelayTo(UPTRINT InHandle, IoWriteFunc WriteFunc, IoCloseFunc CloseFunc, uint16 Flags = FSendFlags::None) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Setup TraceLog to output to user defined callback, to take effect next update. Will fail if another pending output has been queued. @param WriteFunc Function to call when writing data @param CloseFunc Function to call when output is closed @param Flags Options for the connection @return True if successful, false otherwise
- L356 _prototype_ `bool WriteSnapshotTo(const TCHAR* Path, uint32 MaxTailSize = 0) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Immediately write contents of tail buffers and important events to a new or existing file. @param Path Target path @param MaxTailSize Maximum size of tail buffer to write. Zero indicates no limit.
- L364 _prototype_ `bool SendSnapshotTo(const TCHAR* Host, uint32 Port, uint32 MaxTailSize = 0) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Immediately write contents of tail buffers and important events to a remote host. @param Host Target hostname or ip @param Port Target port @param MaxTailSize Maximum size of tail buffer to write. Zero indicates no limit.
- L371 _prototype_ `bool IsTracing() UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Checks if TraceLog currently has an output. Note that trace events can still be recorded and saved in tail buffers regardless if an output is active. @return True if an output is active, false if not
- L380 _prototype_ `bool IsTracingTo(uint32 (&OutSessionGuid)[4], uint32 (&OutTraceGuid)[4]) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Checks if TraceLog currently has an output and return session and trace GUIDs of active trace stream. Note that trace events can still be recorded and saved in tail buffers regardless if an output is active. @param OutSessionGuid If output is active current session GUID will be written, otherwise it will be unchanged @param OutTraceGuid If output is active current trace GUID will be written, otherwise it will be unchanged @return True if an output is active, false if not
- L387 _prototype_ `bool IsTailing() UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Checks if TraceLog is currently using the Tail Buffer, which means that trace events are being cached in memory and could be dumped into a file at any time. @return True if the TailBuffer is active, false if not
- L394 _prototype_ `bool Stop() UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Stops current output if any is active.This will fail there is no active output or if there is already a queued output to be started. @return True if any output was stopped, false if no output was active or there is a queued output to be started.
- L401 _prototype_ `bool IsChannel(const TCHAR* ChannelName) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Checks if a string is valid channel name. @param ChannelName String to check @return True if there is a registered channel object with the same name.
- L409 _prototype_ `bool ToggleChannel(const TCHAR* ChannelName, bool bEnabled) UE_TRACE_IMPL(false);` (scope `UE::Trace`) — Toggles channel to control output of events. @param ChannelName Name of channel to control @param bEnabled Set if channel should be enabled or disabled @return Final channel state. If the channel name was not found return false.
- L416 _prototype_ `void EnumerateChannels(ChannelIterFunc IterFunc, void* User) UE_TRACE_IMPL();` (scope `UE::Trace`) — Enumerates registered channels. @param IterFunc Function to call for each channel @param User Optional pointer to user data to pass to callback
- L423 _prototype_ `void EnumerateChannels(ChannelIterCallback IterFunc, void* User) UE_TRACE_IMPL();` (scope `UE::Trace`) — Enumerates registered channels. @param IterFunc Function to call for each channel @param User Optional pointer to user data to pass to callback
- L431 _prototype_ `void ThreadRegister(const TCHAR* Name, uint32 SystemId, int32 SortHint) UE_TRACE_IMPL();` (scope `UE::Trace`) — Register a new thread in Trace. This is a requirement before tracing anything from the thread. @param Name Display name of thread @param SystemId Platform specific thread id @param SortHint Suggestion on how to order thread in presentation
- L438 _prototype_ `void ThreadGroupBegin(const TCHAR* Name) UE_TRACE_IMPL();` (scope `UE::Trace`) — Define a group of threads with similar use. Any thread created within this call and /ref ThreadGroupEnd will be grouped together. @param Name Display name of group
- L443 _prototype_ `void ThreadGroupEnd() UE_TRACE_IMPL();` (scope `UE::Trace`) — End a group of threads with similar use. See /ref ThreadGroupBegin.
- L450 _prototype_ `FChannel* FindChannel(const TCHAR* ChannelName) UE_TRACE_IMPL(nullptr);` (scope `UE::Trace`) — Attempts to find the corresponding channel object given a channel name. @param ChannelName Name to search for @return Pointer to channel object, or null if no channel matching the name have been registered
- L457 _prototype_ `FChannel* FindChannel(FChannelId ChannelId) UE_TRACE_IMPL(nullptr);` (scope `UE::Trace`) — Attempts to find the corresponding channel object given a channel id. @param ChannelId Id to search for @return Pointer to channel object, or null if no channel with matching id have been registered
- L505 _prototype_ `bool SecureInitialize(const FSecureTraceSettings& Settings);` (scope `UE::Trace`) — Initialize secure connection component. This must happen exactly once before it's possible to call \ref SecureSendTo. @param Settings Settings to use for secure connections
- L511 _prototype_ `bool SecureIsInitialized();` (scope `UE::Trace`) — Checks if secure connection component has been initialized. @return true if \ref SecureInitialize has already been called.
- L519 _prototype_ `bool SecureGetSelfSignedCertificate(uint8** OutPtr, uint32* OutSize);` (scope `UE::Trace`) — Retrieve the public certificate (DER format) when using a self-signed certificate. @param OutPtr If successful, the pointer to the certificate data. The pointer is valid for the remiander of the process lifetime. @param OutSize If successful, certificate size in bytes. @return True if initialized with self-signed certificate, and the certificate was successfully generated.
- L563 _prototype_ `bool SecureSendTo(const FSecureTraceOptions& Options, uint16 Flags = FSendFlags::None);` (scope `UE::Trace`) — Setup output to a secure socket connection. This requires the receiver to connect to the tracing machine on the specified listening port. Additionally certificates to use and optional authorization tokens can be specified for the connection. @param Options Configuration options for the connection @param Flags Options for the connection
- L576 _macro_ `#define UE_TRACE_EVENT_DEFINE(LoggerName, EventName) TRACE_IMPL(EVENT_DEFINE, LoggerName, EventName)`
- L577 _macro_ `#define UE_TRACE_EVENT_BEGIN(LoggerName, EventName, ...) TRACE_IMPL(EVENT_BEGIN, LoggerName, EventName, ##__VA_ARGS__)`
- L578 _macro_ `#define UE_TRACE_EVENT_BEGIN_EXTERN(LoggerName, EventName, ...) TRACE_IMPL(EVENT_BEGIN_EXTERN, LoggerName, EventName, ##__VA_ARGS__)`
- L579 _macro_ `#define UE_TRACE_EVENT_FIELD(FieldType, FieldName) TRACE_IMPL(EVENT_FIELD, FieldType, FieldName)`
- L580 _macro_ `#define UE_TRACE_EVENT_REFERENCE_FIELD(RefLogger, RefEvent, FieldName) TRACE_IMPL(EVENT_REFFIELD, RefLogger, RefEvent, FieldName)`
- L581 _macro_ `#define UE_TRACE_EVENT_END() TRACE_IMPL(EVENT_END)`
- L582 _macro_ `#define UE_TRACE_LOG(LoggerName, EventName, ChannelsExpr, ...) TRACE_IMPL(LOG, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)`
- L583 _macro_ `#define UE_TRACE_LOG_SCOPED(LoggerName, EventName, ChannelsExpr, ...) TRACE_IMPL(LOG_SCOPED, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)`
- L584 _macro_ `#define UE_TRACE_LOG_SCOPED_CONDITIONAL(LoggerName, EventName, ChannelsExpr, Condition, ...) TRACE_IMPL(LOG_SCOPED_CONDITIONAL, LoggerName, EventName, ChannelsExpr, Condition, ##__VA_ARGS__)`
- L585 _macro_ `#define UE_TRACE_LOG_SCOPED_T(LoggerName, EventName, ChannelsExpr, ...) TRACE_IMPL(LOG_SCOPED_T, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)`
- L586 _macro_ `#define UE_TRACE_LOG_SCOPED_T_CONDITIONAL(LoggerName, EventName, ChannelsExpr, Condition, ...) TRACE_IMPL(LOG_SCOPED_T_CONDITIONAL, LoggerName, EventName, ChannelsExpr, Condition, ##__VA_ARGS__)`
- L587 _macro_ `#define UE_TRACE_GET_DEFINITION_TYPE_ID(LoggerName, EventName) TRACE_IMPL(GET_DEFINITION_TYPE_ID, LoggerName, EventName)`
- L588 _macro_ `#define UE_TRACE_LOG_DEFINITION(LoggerName, EventName, Id, ChannelsExpr, ...) TRACE_IMPL(LOG_DEFINITION, LoggerName, EventName, Id, ChannelsExpr, ##__VA_ARGS__)`
- L589 _macro_ `#define UE_TRACE_CHANNEL(ChannelName, ...) TRACE_IMPL(CHANNEL, ChannelName, ##__VA_ARGS__)`
- L590 _macro_ `#define UE_TRACE_CHANNEL_CUSTOM(ChannelName, ChannelClass, ...) TRACE_IMPL(CHANNEL_CUSTOM, ChannelName, ChannelClass, ##__VA_ARGS__)`
- L591 _macro_ `#define UE_TRACE_CHANNEL_EXTERN(ChannelName, ...) TRACE_IMPL(CHANNEL_EXTERN, ChannelName, ##__VA_ARGS__)`
- L592 _macro_ `#define UE_TRACE_CHANNEL_CUSTOM_EXTERN(ChannelName, ChannelClass, ...) TRACE_IMPL(CHANNEL_CUSTOM_EXTERN, ChannelName, ChannelClass, ##__VA_ARGS__)`
- L593 _macro_ `#define UE_TRACE_CHANNEL_DEFINE(ChannelName, ...) TRACE_IMPL(CHANNEL_DEFINE, ChannelName, ##__VA_ARGS__)`
- L594 _macro_ `#define UE_TRACE_CHANNEL_CUSTOM_DEFINE(ChannelName, ChannelClass, ...) TRACE_IMPL(CHANNEL_CUSTOM_DEFINE, ChannelName, ChannelClass, ##__VA_ARGS__)`
- L595 _macro_ `#define UE_TRACE_CHANNELEXPR_IS_ENABLED(ChannelsExpr) TRACE_IMPL(CHANNELEXPR_IS_ENABLED, ChannelsExpr)`
- L603 _macro_ `#define UE_TRACE_MINIMAL_EVENT_DEFINE(LoggerName, EventName) TRACE_IMPL_MINIMAL(EVENT_DEFINE, LoggerName, EventName)`
- L604 _macro_ `#define UE_TRACE_MINIMAL_EVENT_BEGIN(LoggerName, EventName, ...) TRACE_IMPL_MINIMAL(EVENT_BEGIN, LoggerName, EventName, ##__VA_ARGS__)`
- L605 _macro_ `#define UE_TRACE_MINIMAL_EVENT_BEGIN_EXTERN(LoggerName, EventName, ...) TRACE_IMPL_MINIMAL(EVENT_BEGIN_EXTERN, LoggerName, EventName, ##__VA_ARGS__)`
- L606 _macro_ `#define UE_TRACE_MINIMAL_EVENT_FIELD(FieldType, FieldName) TRACE_IMPL_MINIMAL(EVENT_FIELD, FieldType, FieldName)`
- L607 _macro_ `#define UE_TRACE_MINIMAL_EVENT_REFERENCE_FIELD(RefLogger, RefEvent, FieldName) TRACE_IMPL_MINIMAL(EVENT_REFFIELD, RefLogger, RefEvent, FieldName)`
- L608 _macro_ `#define UE_TRACE_MINIMAL_EVENT_END() TRACE_IMPL_MINIMAL(EVENT_END)`
- L609 _macro_ `#define UE_TRACE_MINIMAL_LOG(LoggerName, EventName, ChannelsExpr, ...) TRACE_IMPL_MINIMAL(LOG, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)`
- L610 _macro_ `#define UE_TRACE_MINIMAL_LOG_SCOPED(LoggerName, EventName, ChannelsExpr, ...) TRACE_IMPL_MINIMAL(LOG_SCOPED, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)`
- L611 _macro_ `#define UE_TRACE_MINIMAL_LOG_SCOPED_CONDITIONAL(LoggerName, EventName, ChannelsExpr, Condition, ...) TRACE_IMPL_MINIMAL(LOG_SCOPED_CONDITIONAL, LoggerName, EventName, ChannelsExpr, Condition, ##__VA_ARGS__)`
- L612 _macro_ `#define UE_TRACE_MINIMAL_LOG_SCOPED_T(LoggerName, EventName, ChannelsExpr, ...) TRACE_IMPL_MINIMAL(LOG_SCOPED_T, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)`
- L613 _macro_ `#define UE_TRACE_MINIMAL_LOG_SCOPED_T_CONDITIONAL(LoggerName, EventName, ChannelsExpr, Condition, ...) TRACE_IMPL_MINIMAL(LOG_SCOPED_T_CONDITIONAL, LoggerName, EventName, ChannelsExpr, Condition, ##__VA_ARGS__)`
- L614 _macro_ `#define UE_TRACE_MINIMAL_GET_DEFINITION_TYPE_ID(LoggerName, EventName) TRACE_IMPL_MINIMAL(GET_DEFINITION_TYPE_ID, LoggerName, EventName)`
- L615 _macro_ `#define UE_TRACE_MINIMAL_LOG_DEFINITION(LoggerName, EventName, Id, ChannelsExpr, ...) TRACE_IMPL_MINIMAL(LOG_DEFINITION, LoggerName, EventName, Id, ChannelsExpr, ##__VA_ARGS__)`
- L616 _macro_ `#define UE_TRACE_MINIMAL_CHANNEL(ChannelName, ...) TRACE_IMPL_MINIMAL(CHANNEL, ChannelName, ##__VA_ARGS__)`
- L617 _macro_ `#define UE_TRACE_MINIMAL_CHANNEL_CUSTOM(ChannelName, ChannelClass, ...) TRACE_IMPL_MINIMAL(CHANNEL_CUSTOM, ChannelName, ChannelClass, ##__VA_ARGS__)`
- L618 _macro_ `#define UE_TRACE_MINIMAL_CHANNEL_EXTERN(ChannelName, ...) TRACE_IMPL_MINIMAL(CHANNEL_EXTERN, ChannelName, ##__VA_ARGS__)`
- L619 _macro_ `#define UE_TRACE_MINIMAL_CHANNEL_CUSTOM_EXTERN(ChannelName, ChannelClass, ...) TRACE_IMPL_MINIMAL(CHANNEL_CUSTOM_EXTERN, ChannelName, ChannelClass, ##__VA_ARGS__)`
- L620 _macro_ `#define UE_TRACE_MINIMAL_CHANNEL_DEFINE(ChannelName, ...) TRACE_IMPL_MINIMAL(CHANNEL_DEFINE, ChannelName, ##__VA_ARGS__)`
- L621 _macro_ `#define UE_TRACE_MINIMAL_CHANNEL_CUSTOM_DEFINE(ChannelName, ChannelClass, ...) TRACE_IMPL_MINIMAL(CHANNEL_CUSTOM_DEFINE, ChannelName, ChannelClass, ##__VA_ARGS__)`
- L622 _macro_ `#define UE_TRACE_MINIMAL_CHANNELEXPR_IS_ENABLED(ChannelsExpr) TRACE_IMPL_MINIMAL(CHANNELEXPR_IS_ENABLED, ChannelsExpr)`

### `Source/Runtime/TraceLog/Public/Trace/Trace.inl` (Public)
_(no declarations extracted)_
