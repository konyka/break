# Runtime / SymsLib

- module root: `Source/Runtime/SymsLib`
- headers: 61; symbols: 12242
- symbol kinds: enum=393, enumerator=6310, macro=386, member=2357, prototype=933, struct=514, typedef=945, union=28, variable=376

### `Source/Runtime/SymsLib/syms/core/base/syms_base.h` (Other)


#### struct `SYMS_U64Array`  
`typedef struct SYMS_U64Array`  
_L233-236_
- L234 _public member_ `SYMS_U64 *u64;`
- L235 _public member_ `SYMS_U64 count;`

#### struct `SYMS_U32Array`  
`typedef struct SYMS_U32Array`  
_L238-241_
- L239 _public member_ `SYMS_U32 *u32;`
- L240 _public member_ `SYMS_U64 count;`

#### struct `SYMS_U16Array`  
`typedef struct SYMS_U16Array`  
_L243-246_
- L244 _public member_ `SYMS_U16 *u16;`
- L245 _public member_ `SYMS_U64 count;`

#### struct `SYMS_U64ArrayNode`  
`typedef struct SYMS_U64ArrayNode`  
_L248-252_
- L249 _public member_ `struct SYMS_U64ArrayNode *next;`
- L250 _public member_ `SYMS_U64 *u64;`
- L251 _public member_ `SYMS_U64 count;`

#### struct `SYMS_U64Maybe`  
`typedef struct SYMS_U64Maybe`  
_L254-257_
- L255 _public member_ `SYMS_B32 valid;`
- L256 _public member_ `SYMS_U64 u64;`

#### struct `SYMS_U32Range`  
`typedef struct SYMS_U32Range`  
_L259-262_
- L260 _public member_ `SYMS_U32 min;`
- L261 _public member_ `SYMS_U32 max;`

#### struct `SYMS_U64Range`  
`typedef struct SYMS_U64Range`  
_L264-267_
- L265 _public member_ `SYMS_U64 min;`
- L266 _public member_ `SYMS_U64 max;`

#### struct `SYMS_U64RangeNode`  
`typedef struct SYMS_U64RangeNode`  
_L269-272_
- L270 _public member_ `struct SYMS_U64RangeNode *next;`
- L271 _public member_ `SYMS_U64Range range;`

#### struct `SYMS_U64RangeList`  
`typedef struct SYMS_U64RangeList`  
_L274-278_
- L275 _public member_ `SYMS_U64RangeNode *first;`
- L276 _public member_ `SYMS_U64RangeNode *last;`
- L277 _public member_ `SYMS_U64 node_count;`

#### struct `SYMS_U64RangeArray`  
`typedef struct SYMS_U64RangeArray`  
_L280-283_
- L281 _public member_ `SYMS_U64Range *ranges;`
- L282 _public member_ `SYMS_U64 count;`

#### struct `SYMS_U64Node`  
`typedef struct SYMS_U64Node`  
_L285-288_
- L286 _public member_ `struct SYMS_U64Node *next;`
- L287 _public member_ `SYMS_U64 u64;`

#### struct `SYMS_U64List`  
`typedef struct SYMS_U64List`  
_L290-294_
- L291 _public member_ `SYMS_U64Node *first;`
- L292 _public member_ `SYMS_U64Node *last;`
- L293 _public member_ `SYMS_U64 count;`

#### struct `SYMS_String8`  
`typedef struct SYMS_String8`  
_L296-299_
- L297 _public member_ `SYMS_U8 *str;`
- L298 _public member_ `SYMS_U64 size;`

#### struct `SYMS_String8Node`  
`typedef struct SYMS_String8Node`  
_L301-304_
- L302 _public member_ `struct SYMS_String8Node *next;`
- L303 _public member_ `SYMS_String8 string;`

#### struct `SYMS_String8List`  
`typedef struct SYMS_String8List`  
_L306-311_
- L307 _public member_ `SYMS_String8Node *first;`
- L308 _public member_ `SYMS_String8Node *last;`
- L309 _public member_ `SYMS_U64 node_count;`
- L310 _public member_ `SYMS_U64 total_size;`

#### struct `SYMS_String8Array`  
`typedef struct SYMS_String8Array`  
_L313-316_
- L314 _public member_ `SYMS_String8 *strings;`
- L315 _public member_ `SYMS_U64 count;`

#### enum `(anonymous)`  
`enum`  
_L319-323_

#### struct `SYMS_StringJoin`  
`typedef struct SYMS_StringJoin`  
_L325-329_
- L326 _public member_ `SYMS_String8 pre;`
- L327 _public member_ `SYMS_String8 sep;`
- L328 _public member_ `SYMS_String8 post;`

#### struct `SYMS_SortNode`  
`typedef struct SYMS_SortNode`  
_L334-338_
- L335 _public member_ `struct SYMS_SortNode *next;`
- L336 _public member_ `SYMS_U64 first;`
- L337 _public member_ `SYMS_U64 opl;`

#### enum `SYMS_SerialWidthKind`  
`typedef enum SYMS_SerialWidthKind`  
_L348-357_
- L349 _public enumerator_ `SYMS_SerialWidthKind_Null`
- L350 _public enumerator_ `SYMS_SerialWidthKind_Fixed`
- L351 _public enumerator_ `SYMS_SerialWidthKind_Array`
- L352 _public enumerator_ `SYMS_SerialWidthKind_NullTerminated`
- L353 _public enumerator_ `SYMS_SerialWidthKind_SequenceNullTerminated`
- L354 _public enumerator_ `SYMS_SerialWidthKind_RestOfStream`
- L355 _public enumerator_ `SYMS_SerialWidthKind_PdbNumeric`
- L356 _public enumerator_ `SYMS_SerialWidthKind_COUNT`

#### struct `SYMS_SerialField`  
`typedef struct SYMS_SerialField`  
_L359-364_
- L360 _public member_ `SYMS_String8 name;`
- L361 _public member_ `struct SYMS_SerialType *type;`
- L362 _public member_ `SYMS_SerialWidthKind width_kind;`
- L363 _public member_ `SYMS_U32 width_var;`

#### struct `SYMS_SerialValue`  
`typedef struct SYMS_SerialValue`  
_L366-369_
- L367 _public member_ `SYMS_String8 name;`
- L368 _public member_ `SYMS_U64 value;`

#### struct `SYMS_SerialFlag`  
`typedef struct SYMS_SerialFlag`  
_L371-376_
- L372 _public member_ `SYMS_String8 name;`
- L373 _public member_ `struct SYMS_SerialType *type;`
- L374 _public member_ `SYMS_U32 mask;`
- L375 _public member_ `SYMS_U32 bitshift;`

#### enum `SYMS_SerialTypeKind`  
`typedef enum SYMS_SerialTypeKind`  
_L378-388_
- L379 _public enumerator_ `SYMS_SerialTypeKind_Null`
- L380 _public enumerator_ `SYMS_SerialTypeKind_Integer`
- L381 _public enumerator_ `SYMS_SerialTypeKind_UnsignedInteger`
- L382 _public enumerator_ `SYMS_SerialTypeKind_Character`
- L383 _public enumerator_ `SYMS_SerialTypeKind_BinaryAnnotation`
- L384 _public enumerator_ `SYMS_SerialTypeKind_Enum`
- L385 _public enumerator_ `SYMS_SerialTypeKind_Flags`
- L386 _public enumerator_ `SYMS_SerialTypeKind_Struct`
- L387 _public enumerator_ `SYMS_SerialTypeKind_COUNT`

#### struct `SYMS_SerialType`  
`typedef struct SYMS_SerialType`  
_L390-397_
- L391 _public member_ `SYMS_String8 name;`
- L392 _public member_ `SYMS_SerialTypeKind kind;`
- L393 _public member_ `SYMS_U32 child_count;`
- L394 _public member_ `void *children;`
- L395 _public member_ `SYMS_U64 basic_size;`
- L396 _public member_ `SYMS_U64 (*enum_index_from_value)(SYMS_U64 value);`

#### struct `SYMS_ArenaTemp`  
`typedef struct SYMS_ArenaTemp`  
_L402-405_
- L403 _public member_ `SYMS_Arena *arena;`
- L404 _public member_ `SYMS_U64 pos;`

#### struct `SYMS_MemoryView`  
`typedef struct SYMS_MemoryView`  
_L410-418_
- L415 _public member_ `void *data;` — allen: Upgrade path: 1. A list of ranges like this one 2. After building the list put into a binary-searchable format 3. Equip with the ability to request missing memory in-line.
- L416 _public member_ `SYMS_U64 addr_first;`
- L417 _public member_ `SYMS_U64 addr_opl;`

#### struct `SYMS_UnwindResult`  
`typedef struct SYMS_UnwindResult`  
_L420-425_
- L421 _public member_ `SYMS_B32 dead;`
- L422 _public member_ `SYMS_B32 missed_read;`
- L423 _public member_ `SYMS_U64 missed_read_addr;`
- L424 _public member_ `SYMS_U64 stack_pointer;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_BASE_H`
- L10 _macro_ `#define SYMS_VERSION_MAJOR 1`
- L11 _macro_ `#define SYMS_VERSION_MINOR 0`
- L12 _macro_ `#define SYMS_VERSION_SUBMINOR 0`
- L13 _macro_ `#define SYMS_VERSION_STR "1.0.0"`
- L29 _macro_ `# define SYMS_API static`
- L33 _macro_ `# define SYMS_C_LINKAGE_BEGIN extern "C" {`
- L34 _macro_ `# define SYMS_C_LINKAGE_END }`
- L35 _macro_ `# define SYMS_EXTERN extern "C"`
- L37 _macro_ `# define SYMS_C_LINKAGE_BEGIN`
- L38 _macro_ `# define SYMS_C_LINKAGE_END`
- L39 _macro_ `# define SYMS_EXTERN extern`
- L42 _macro_ `#define SYMS_GLOBAL static`
- L43 _macro_ `#define SYMS_LOCAL static`
- L48 _macro_ `# define SYMS_READ_ONLY __declspec(allocate(".roglob"))`
- L50 _macro_ `# define SYMS_READ_ONLY __attribute__((section(".rodata")))`
- L57 _macro_ `# define SYMS_READ_ONLY` — NOTE(rjf): I don't know of a useful way to do this in GCC land. __attribute__((section(".rodata"))) looked promising, but it introduces a strange warning about malformed section attributes, and it doesn't look like writing to that section reliably produces access violations, strangely enough. (It does on Clang)
- L62 _macro_ `# define SYMS_THREAD_LOCAL __declspec(thread)`
- L64 _macro_ `# define SYMS_THREAD_LOCAL __thread`
- L73 _macro_ `# define SYMS_PARANOID 0`
- L76 _macro_ `# define SYMS_ASSERT_INVARIANTS 0`
- L79 _macro_ `# define SYMS_DISABLE_NORMAL_ASSERTS 0`
- L82 _macro_ `# define SYMS_ENABLE_DEV_SRCLOC 0`
- L85 _macro_ `# define SYMS_ENABLE_DEV_STRING 0`
- L88 _macro_ `# define SYMS_ENABLE_DEV_LOG 0`
- L91 _macro_ `# define SYMS_ENABLE_DEV_PROFILE 0`
- L97 _typedef_ `typedef SYMS_S8 SYMS_B8;`
- L98 _typedef_ `typedef SYMS_S16 SYMS_B16;`
- L99 _typedef_ `typedef SYMS_S32 SYMS_B32;`
- L100 _typedef_ `typedef SYMS_S64 SYMS_B64;`
- L101 _typedef_ `typedef float SYMS_F32;`
- L102 _typedef_ `typedef double SYMS_F64;`
- L104 _macro_ `#define syms_false 0`
- L105 _macro_ `#define syms_true 1`
- L107 _typedef_ `typedef SYMS_U32 SYMS_RegID;`
- L113 _macro_ `# define syms_write_srcloc__impl(f,l) ((void)0)`
- L116 _macro_ `# define SYMS_WRITE_SRCLOC(f,l) syms_write_srcloc__impl(f,l)`
- L118 _macro_ `# define SYMS_WRITE_SRCLOC(f,l) ((void)0)`
- L122 _macro_ `#define SYMS_ASSERT_RAW(x) do { if(!(x)) { SYMS_ASSERT_BREAK(x); } } while(0)`
- L125 _macro_ `# define SYMS_ASSERT(x) SYMS_ASSERT_RAW(x)`
- L127 _macro_ `# define SYMS_ASSERT(x)`
- L130 _macro_ `# define SYMS_ASSERT_PARANOID(x) SYMS_ASSERT_RAW(x)`
- L132 _macro_ `# define SYMS_ASSERT_PARANOID(x)`
- L136 _macro_ `# define SYMS_INVARIANT(r,x) SYMS_ASSERT_RAW(x)`
- L138 _macro_ `# define SYMS_INVARIANT(r,x) do{ if (!(x)){ (r) = syms_false; goto finish_invariants; } } while(0)`
- L141 _macro_ `#define SYMS_NOT_IMPLEMENTED SYMS_ASSERT_BREAK("not implemented")`
- L142 _macro_ `#define SYMS_INVALID_CODE_PATH SYMS_ASSERT_BREAK("invalid code path")`
- L144 _macro_ `#define SYMS_ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))`
- L147 _macro_ `#define SYMS_PTR_DIF(a, b) (SYMS_U64)((SYMS_U8*)(a) - (SYMS_U8*)(b))`
- L148 _macro_ `#define SYMS_MEMBER(type, member) (&((type*)0)->member)`
- L149 _macro_ `#define SYMS_MEMBER_OFFSET(type, member) (SYMS_PTR_DIF(SYMS_MEMBER(type, member), 0))`
- L151 _macro_ `#define SYMS_KB(num) ((SYMS_U64)(num) << 10)`
- L152 _macro_ `#define SYMS_MB(num) ((SYMS_U64)(num) << 20)`
- L153 _macro_ `#define SYMS_GB(num) ((SYMS_U64)(num) << 30)`
- L154 _macro_ `#define SYMS_TB(num) ((SYMS_U64)(num) << 40)`
- L156 _macro_ `#define SYMS_Stringify_(x) #x`
- L157 _macro_ `#define SYMS_Stringify(x) SYMS_Stringify_(x)`
- L158 _macro_ `#define SYMS_Glue_(a,b) a ## b`
- L159 _macro_ `#define SYMS_Glue(a,b) SYMS_Glue_(a,b)`
- L161 _macro_ `#define syms_memzero_struct(s) syms_memset((s), 0, sizeof(*(s)))`
- L162 _macro_ `#define syms_memisnull_struct(s) syms_memisnull((s), sizeof(*(s)))`
- L164 _macro_ `#define SYMS_S8_MIN 0x80 // -128`
- L165 _macro_ `#define SYMS_S8_MAX 0x7f // +127`
- L166 _macro_ `#define SYMS_S16_MIN 0x8000 // -32768`
- L167 _macro_ `#define SYMS_S16_MAX 0x7fff // +32767`
- L168 _macro_ `#define SYMS_S32_MIN 0x80000000 // -2147483648`
- L169 _macro_ `#define SYMS_S32_MAX 0x7fffffff // +2147483647`
- L170 _macro_ `#define SYMS_S64_MIN 0x8000000000000000ull // -9223372036854775808`
- L171 _macro_ `#define SYMS_S64_MAX 0x7fffffffffffffffull // +9223372036854775807`
- L173 _macro_ `#define SYMS_U8_MAX 0xFFu`
- L174 _macro_ `#define SYMS_U16_MAX 0xFFFFu`
- L175 _macro_ `#define SYMS_U32_MAX 0xFFFFFFFFu`
- L176 _macro_ `#define SYMS_U64_MAX 0xFFFFFFFFFFFFFFFFu`
- L178 _macro_ `#define SYMS_STATIC_ASSERT(c) typedef char SYMS_Glue(assert, __LINE__)[(c)?+1:-1]`
- L179 _macro_ `#define SYMS_MIN(a,b) ((a)<(b)?(a):(b))`
- L180 _macro_ `#define SYMS_MAX(a,b) ((a)>(b)?(a):(b))`
- L182 _macro_ `#define SYMS_ClampTop(a,b) SYMS_MIN(a,b)`
- L183 _macro_ `#define SYMS_ClampBot(a,b) SYMS_MAX(a,b)`
- L185 _macro_ `#define SYMS_CeilIntegerDiv(a,b) (((a) + (b) - 1)/(b))`
- L187 _macro_ `#define SYMS_AlignPow2(a,b) (((a) + (b) - 1)&(~((b) - 1)))`
- L188 _macro_ `#define SYMS_AlignDownPow2(a,b) ((a)&(~((b) - 1)))`
- L190 _macro_ `#define SYMS_Swap(T,a,b) do{ T t__ = (a); (a) = (b); (b) = t__; }while(0)`
- L192 _macro_ `#define SYMS_THIS_SRCLOC __FILE__ ":" SYMS_Stringify(__LINE__)`
- L197 _macro_ `#define SYMS_ID_u32_0(id) (SYMS_U32)(id)`
- L198 _macro_ `#define SYMS_ID_u32_1(id) (SYMS_U32)((id) >> 32)`
- L199 _macro_ `#define SYMS_ID_u16_0(id) (SYMS_U16)(id)`
- L200 _macro_ `#define SYMS_ID_u16_1(id) (SYMS_U16)((id) >> 16)`
- L201 _macro_ `#define SYMS_ID_u16_2(id) (SYMS_U16)((id) >> 32)`
- L202 _macro_ `#define SYMS_ID_u16_3(id) (SYMS_U16)((id) >> 48)`
- L204 _macro_ `#define SYMS_ID_u32_u32(a,b) ((SYMS_U64)(a) | ((SYMS_U64)(b) << 32))`
- L205 _macro_ `#define SYMS_ID_u16_u16_u32(a,b,c) ((SYMS_U64)(a) | ((SYMS_U64)(b) << 16) | ((SYMS_U64)(c) << 32))`
- L210 _macro_ `#define SYMS_QueuePush_N(f,l,n,next) ( (f)==0?\`
- L213 _macro_ `#define SYMS_QueuePushFront_N(f,l,n,next) ( (f)==0?\`
- L216 _macro_ `#define SYMS_QueuePop_N(f,l,next) ( (f)==(l)?\`
- L220 _macro_ `#define SYMS_QueuePush(f,l,n) SYMS_QueuePush_N(f,l,n,next)`
- L221 _macro_ `#define SYMS_QueuePushFront(f,l,n) SYMS_QueuePushFront_N(f,l,n,next)`
- L222 _macro_ `#define SYMS_QueuePop(f,l) SYMS_QueuePop_N(f,l,next)`
- L224 _macro_ `#define SYMS_StackPush_N(f,n,next) ( (n)->next=(f), (f)=(n) )`
- L225 _macro_ `#define SYMS_StackPop_N(f,next) ( (f)=(f)->next )`
- L227 _macro_ `#define SYMS_StackPush(f,n) SYMS_StackPush_N(f,n,next)`
- L228 _macro_ `#define SYMS_StackPop(f) SYMS_StackPop_N(f,next)`
- L236 _typedef_ `} SYMS_U64Array;`
- L241 _typedef_ `} SYMS_U32Array;`
- L246 _typedef_ `} SYMS_U16Array;`
- L252 _typedef_ `} SYMS_U64ArrayNode;`
- L257 _typedef_ `} SYMS_U64Maybe;`
- L262 _typedef_ `} SYMS_U32Range;`
- L267 _typedef_ `} SYMS_U64Range;`
- L272 _typedef_ `} SYMS_U64RangeNode;`
- L278 _typedef_ `} SYMS_U64RangeList;`
- L283 _typedef_ `} SYMS_U64RangeArray;`
- L288 _typedef_ `} SYMS_U64Node;`
- L294 _typedef_ `} SYMS_U64List;`
- L299 _typedef_ `} SYMS_String8;`
- L304 _typedef_ `} SYMS_String8Node;`
- L311 _typedef_ `} SYMS_String8List;`
- L316 _typedef_ `} SYMS_String8Array;`
- L318 _typedef_ `typedef SYMS_U32 SYMS_StringMatchFlags;`
- L320 _enumerator_ `SYMS_StringMatchFlag_CaseInsensitive = (1<<0)` (scope `__anon139ed4d40103`)
- L321 _enumerator_ `SYMS_StringMatchFlag_RightSideSloppy = (1<<1)` (scope `__anon139ed4d40103`)
- L322 _enumerator_ `SYMS_StringMatchFlag_SlashInsensitive = (1<<2)` (scope `__anon139ed4d40103`)
- L329 _typedef_ `} SYMS_StringJoin;`
- L338 _typedef_ `} SYMS_SortNode;`
- L357 _typedef_ `} SYMS_SerialWidthKind;`
- L364 _typedef_ `} SYMS_SerialField;`
- L369 _typedef_ `} SYMS_SerialValue;`
- L376 _typedef_ `} SYMS_SerialFlag;`
- L388 _typedef_ `} SYMS_SerialTypeKind;`
- L397 _typedef_ `} SYMS_SerialType;`
- L405 _typedef_ `} SYMS_ArenaTemp;`
- L418 _typedef_ `} SYMS_MemoryView;`
- L425 _typedef_ `} SYMS_UnwindResult;`
- L439 _prototype_ `SYMS_String8 syms_version_string(void);`
- L444 _prototype_ `SYMS_U64Range syms_make_u64_range(SYMS_U64 min, SYMS_U64 max);`
- L445 _prototype_ `SYMS_U64Range syms_make_u64_inrange(SYMS_U64Range range, SYMS_U64 offset, SYMS_U64 size);`
- L446 _prototype_ `SYMS_U64 syms_u64_range_size(SYMS_U64Range range);`
- L451 _variable_ `SYMS_GLOBAL SYMS_U64 syms_hash_djb2_initial = 5381;`
- L452 _prototype_ `SYMS_U64 syms_hash_djb2(SYMS_String8 string);`
- L453 _prototype_ `SYMS_U64 syms_hash_djb2_continue(SYMS_String8 string, SYMS_U64 intermediate_hash);`
- L455 _prototype_ `SYMS_U64 syms_hash_u64(SYMS_U64 x);`
- L460 _macro_ `#define syms_serial_type(name) (_syms_serial_type_##name)`
- L461 _macro_ `#define syms_string_from_enum_value(enum_type, value) \`
- L463 _macro_ `#define syms_bswap_in_place(type, ptr) syms_bswap_in_place__##type((type*)(ptr))`
- L465 _prototype_ `SYMS_SerialField* syms_serial_first_field(SYMS_SerialType *type);`
- L466 _prototype_ `SYMS_SerialValue* syms_serial_first_value(SYMS_SerialType *type);`
- L467 _prototype_ `SYMS_SerialFlag* syms_serial_first_flag(SYMS_SerialType *type);`
- L469 _prototype_ `SYMS_SerialValue* syms_serial_value_from_enum_value(SYMS_SerialType *type, SYMS_U64 value);`
- L470 _prototype_ `SYMS_SerialFlag* syms_serial_flag_from_bit_offset(SYMS_SerialType *type, SYMS_U64 bit_off);`
- L472 _prototype_ `SYMS_String8List syms_string_list_from_flags(SYMS_Arena *arena, SYMS_SerialType *type, SYMS_U32 flags);`
- L474 _prototype_ `SYMS_U64 syms_enum_index_from_value_identity(SYMS_U64 v);`
- L479 _prototype_ `SYMS_B32 syms_codepoint_is_whitespace(SYMS_U32 codepoint);`
- L480 _prototype_ `SYMS_U32 syms_lowercase_from_codepoint(SYMS_U32 codepoint);`
- L482 _macro_ `#define syms_str8_comp(s) { (SYMS_U8 *)(s), sizeof(s) - 1 }`
- L483 _macro_ `#define syms_str8_lit(s) syms_str8((SYMS_U8 *)(s), sizeof(s) - 1)`
- L484 _macro_ `#define syms_expand_string(s) (int)((s).size), ((s).str)`
- L486 _prototype_ `SYMS_String8 syms_str8(SYMS_U8 *str, SYMS_U64 size);`
- L487 _prototype_ `SYMS_String8 syms_str8_cstring(char *str);`
- L488 _prototype_ `SYMS_String8 syms_str8_range(SYMS_U8 *first, SYMS_U8 *opl);`
- L490 _prototype_ `SYMS_String8 syms_str8_skip_chop_whitespace(SYMS_String8 str);`
- L492 _prototype_ `SYMS_B32 syms_string_match(SYMS_String8 a, SYMS_String8 b, SYMS_StringMatchFlags flags);`
- L493 _prototype_ `SYMS_U8* syms_decode_utf8(SYMS_U8 *p, SYMS_U32 *dst);`
- L495 _prototype_ `void syms_string_list_push_node(SYMS_String8Node *node, SYMS_String8List *list, SYMS_String8 string);`
- L497 _prototype_ `void syms_string_list_push_node_front(SYMS_String8Node *node, SYMS_String8List *list, SYMS_String8 string);`
- L499 _prototype_ `void syms_string_list_push(SYMS_Arena *arena, SYMS_String8List *list, SYMS_String8 string);`
- L500 _prototype_ `void syms_string_list_push_front(SYMS_Arena *arena, SYMS_String8List *list, SYMS_String8 string);`
- L501 _prototype_ `SYMS_String8List syms_string_list_concat(SYMS_String8List *left, SYMS_String8List *right);`
- L504 _prototype_ `SYMS_String8 syms_string_list_join(SYMS_Arena *arena, SYMS_String8List *list, SYMS_StringJoin *join);`
- L505 _prototype_ `SYMS_String8 syms_push_string_copy(SYMS_Arena *arena, SYMS_String8 string);`
- L507 _prototype_ `SYMS_String8 syms_string_trunc_symbol_heuristic(SYMS_String8 string);`
- L509 _prototype_ `SYMS_String8List syms_string_split(SYMS_Arena *arena, SYMS_String8 input, SYMS_U32 delimiter);`
- L514 _prototype_ `SYMS_U64 syms_u64_from_string(SYMS_String8 str, SYMS_U32 radix);`
- L515 _prototype_ `SYMS_S64 syms_s64_from_string_c_rules(SYMS_String8 str);`
- L517 _prototype_ `SYMS_String8 syms_string_from_u64(SYMS_Arena *arena, SYMS_U64 x);`
- L522 _prototype_ `void syms_u64_range_list_push_node(SYMS_U64RangeNode *node, SYMS_U64RangeList *list, SYMS_U64Range range);`
- L523 _prototype_ `void syms_u64_range_list_push(SYMS_Arena *arena, SYMS_U64RangeList *list, SYMS_U64Range range);`
- L524 _prototype_ `void syms_u64_range_list_concat(SYMS_U64RangeList *list, SYMS_U64RangeList *to_push);`
- L526 _prototype_ `SYMS_U64RangeArray syms_u64_range_array_from_list(SYMS_Arena *arena, SYMS_U64RangeList *list);`
- L531 _prototype_ `void syms_u64_list_push_node(SYMS_U64Node *node, SYMS_U64List *list, SYMS_U64 v);`
- L532 _prototype_ `void syms_u64_list_push(SYMS_Arena *arena, SYMS_U64List *list, SYMS_U64 v);`
- L533 _prototype_ `void syms_u64_list_concat_in_place(SYMS_U64List *dst, SYMS_U64List *src);`
- L534 _prototype_ `SYMS_U64Array syms_u64_array_from_list(SYMS_Arena *arena, SYMS_U64List *list);`
- L539 _prototype_ `SYMS_U64 syms_1based_checked_lookup_u64(SYMS_U64 *u64, SYMS_U64 count, SYMS_U64 n);`
- L544 _macro_ `#define syms_arena_alloc syms_arena_alloc__impl`
- L545 _macro_ `#define syms_arena_release syms_arena_release__impl`
- L546 _macro_ `#define syms_arena_get_pos syms_arena_get_pos__impl`
- L547 _macro_ `#define syms_arena_push syms_arena_push__impl`
- L548 _macro_ `#define syms_arena_pop_to syms_arena_pop_to__impl`
- L549 _macro_ `#define syms_arena_set_auto_align syms_arena_set_auto_align__impl`
- L550 _macro_ `#define syms_arena_absorb syms_arena_absorb__impl`
- L551 _macro_ `#define syms_arena_tidy syms_arena_tidy__impl`
- L553 _macro_ `#define syms_get_implicit_thread_arena syms_get_implicit_thread_arena__impl`
- L555 _prototype_ `void syms_arena_push_align(SYMS_Arena *arena, SYMS_U64 boundary);`
- L556 _prototype_ `void syms_arena_put_back(SYMS_Arena *arena, SYMS_U64 amount);`
- L558 _prototype_ `SYMS_ArenaTemp syms_arena_temp_begin(SYMS_Arena *arena);`
- L559 _prototype_ `void syms_arena_temp_end(SYMS_ArenaTemp frame);`
- L561 _macro_ `#define syms_push_array(a,T,c) (SYMS_WRITE_SRCLOC(__FILE__, __LINE__),\`
- L564 _macro_ `#define syms_push_array_zero(a,T,c) ((T*)syms_memset(syms_push_array(a,T,c), 0, sizeof(T)*(c)))`
- L566 _prototype_ `SYMS_ArenaTemp syms_get_scratch(SYMS_Arena **conflicts, SYMS_U64 count);`
- L567 _macro_ `#define syms_release_scratch syms_arena_temp_end`
- L569 _macro_ `#define syms_scratch_pool_tidy syms_scratch_pool_tidy__impl`
- L574 _prototype_ `SYMS_SortNode* syms_sort_node_push(SYMS_Arena *arena, SYMS_SortNode **stack, SYMS_SortNode **free_stack, SYMS_U64 first, SYMS_U64 opl);`
- L580 _prototype_ `void syms_set_lane(SYMS_U64 lane);`
- L581 _prototype_ `SYMS_U64 syms_get_lane(void);`
- L586 _prototype_ `void * syms_based_range_ptr(void *base, SYMS_U64Range range, SYMS_U64 offset);`
- L587 _prototype_ `SYMS_U64 syms_based_range_read(void *base, SYMS_U64Range range, SYMS_U64 offset, SYMS_U64 out_size, void *out);`
- L588 _prototype_ `SYMS_U64 syms_based_range_read_uleb128(void *base, SYMS_U64Range range, SYMS_U64 offset, SYMS_U64 *out_value);`
- L589 _prototype_ `SYMS_U64 syms_based_range_read_sleb128(void *base, SYMS_U64Range range, SYMS_U64 offset, SYMS_S64 *out_value);`
- L591 _prototype_ `SYMS_String8 syms_based_range_read_string(void *base, SYMS_U64Range range, SYMS_U64 offset);`
- L593 _macro_ `#define syms_based_range_read_struct(b,r,o,p) syms_based_range_read((b), (r), (o), sizeof(*(p)), p)`
- L598 _prototype_ `SYMS_MemoryView syms_memory_view_make(SYMS_String8 data, SYMS_U64 base);`
- L599 _prototype_ `SYMS_B32 syms_memory_view_read(SYMS_MemoryView *memview, SYMS_U64 addr, SYMS_U64 size, void *ptr);`
- L602 _macro_ `#define syms_memory_view_read_struct(s,a,p) syms_memory_view_read((s),(a),sizeof(*(p)),(p))`
- L604 _prototype_ `void syms_unwind_result_missed_read(SYMS_UnwindResult *unwind_result, SYMS_U64 addr);`
- L609 _prototype_ `SYMS_U16 syms_bswap_u16(SYMS_U16 x);`
- L610 _prototype_ `SYMS_U32 syms_bswap_u32(SYMS_U32 x);`
- L611 _prototype_ `SYMS_U64 syms_bswap_u64(SYMS_U64 x);`
- L612 _prototype_ `void syms_bswap_bytes(void *p, SYMS_U64 size);`

### `Source/Runtime/SymsLib/syms/core/base/syms_base_context_crack.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_BASE_CONTEXT_CRACK_H`
- L9 _macro_ `# define SYMS_COMPILER_CLANG 1`
- L12 _macro_ `# define SYMS_OS_WINDOWS 1`
- L14 _macro_ `# define SYMS_OS_LINUX 1`
- L16 _macro_ `# define SYMS_OS_MAC 1`
- L22 _macro_ `# define SYMS_ARCH_X64 1`
- L24 _macro_ `# define SYMS_ARCH_X86 1`
- L26 _macro_ `# define SYMS_ARCH_ARM64 1`
- L28 _macro_ `# define SYMS_ARCH_ARM32 1`
- L35 _macro_ `# define SYMS_COMPILER_CL 1`
- L57 _macro_ `# define SYMS_COMPILER_GCC 1`
- L82 _macro_ `# define SYMS_ARCH_64BIT 1`
- L84 _macro_ `# define SYMS_ARCH_32BIT 1`
- L88 _macro_ `# define SYMS_LANG_CPP 1`
- L90 _macro_ `# define SYMS_LANG_C 1`
- L96 _macro_ `# define SYMS_ARCH_32BIT 0`
- L99 _macro_ `# define SYMS_ARCH_64BIT 0`
- L102 _macro_ `# define SYMS_ARCH_X64 0`
- L105 _macro_ `# define SYMS_ARCH_X86 0`
- L108 _macro_ `# define SYMS_ARCH_ARM64 0`
- L111 _macro_ `# define SYMS_ARCH_ARM32 0`
- L114 _macro_ `# define SYMS_COMPILER_CL 0`
- L117 _macro_ `# define SYMS_COMPILER_GCC 0`
- L120 _macro_ `# define SYMS_COMPILER_CLANG 0`
- L123 _macro_ `# define SYMS_OS_WINDOWS 0`
- L126 _macro_ `# define SYMS_OS_LINUX 0`
- L129 _macro_ `# define SYMS_OS_MAC 0`
- L132 _macro_ `# define SYMS_LANG_CPP 0`
- L135 _macro_ `# define SYMS_LANG_C 0`
- L139 _macro_ `# define SYMS_LITTLE_ENDIAN 1`

### `Source/Runtime/SymsLib/syms/core/base/syms_base_overrides_check.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_BASE_OVERRIDES_CHECK_H`

### `Source/Runtime/SymsLib/syms/core/base/syms_dev.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L19-34_

#### struct `SYMS_ProfChain`  
`typedef struct SYMS_ProfChain`  
_L39-42_
- L40 _public member_ `struct SYMS_ProfChain *next;`
- L41 _public member_ `SYMS_U8 *ptr;`

#### struct `SYMS_ProfState`  
`typedef struct SYMS_ProfState`  
_L44-48_
- L45 _public member_ `SYMS_ProfChain *first;`
- L46 _public member_ `SYMS_ProfChain *current;`
- L47 _public member_ `SYMS_ProfChain *free;`

#### struct `SYMS_ProfLock`  
`typedef struct SYMS_ProfLock`  
_L50-53_
- L51 _public member_ `SYMS_ProfState *state;`
- L52 _public member_ `SYMS_String8 data;`

#### struct `SYMS_ProfTreeNode`  
`typedef struct SYMS_ProfTreeNode`  
_L55-73_
- L57 _public member_ `struct SYMS_ProfTreeNode *next;` — hash table
- L58 _public member_ `SYMS_U64 hash;`
- L59 _public member_ `SYMS_String8 key;`
- L62 _public member_ `SYMS_U64 count;` — local counts
- L63 _public member_ `SYMS_U64 total_time;`
- L66 _public member_ `struct SYMS_ProfTreeNode *tree_first;` — tree
- L67 _public member_ `struct SYMS_ProfTreeNode *tree_last;`
- L68 _public member_ `struct SYMS_ProfTreeNode *tree_next;`
- L69 _public member_ `struct SYMS_ProfTreeNode *tree_parent;`
- L72 _public member_ `SYMS_U64 time_min;` — mutable space - not a fixed value for users to rely on

#### struct `SYMS_ProfTree`  
`typedef struct SYMS_ProfTree`  
_L75-85_
- L77 _public member_ `SYMS_ProfTreeNode **buckets;` — hash table
- L78 _public member_ `SYMS_U64 bucket_count;`
- L79 _public member_ `SYMS_U64 count;`
- L80 _public member_ `SYMS_U64 max_key_size;`
- L83 _public member_ `SYMS_ProfTreeNode *root;` — tree
- L84 _public member_ `SYMS_U64 height;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DEV_H`
- L12 _macro_ `# define SYMS_ENABLE_DEV_STRING 1`
- L18 _typedef_ `typedef SYMS_U32 SYMS_LogFeatures;`
- L20 _enumerator_ `SYMS_LogFeature_LineTable = (1 << 0)` (scope `__anon1fc65f580103`)
- L21 _enumerator_ `SYMS_LogFeature_DwarfUnitRanges = (1 << 1)` (scope `__anon1fc65f580103`)
- L22 _enumerator_ `SYMS_LogFeature_DwarfTags = (1 << 2)` (scope `__anon1fc65f580103`)
- L23 _enumerator_ `SYMS_LogFeature_DwarfUnwind = (1 << 3)` (scope `__anon1fc65f580103`)
- L24 _enumerator_ `SYMS_LogFeature_DwarfCFILookup = (1 << 4)` (scope `__anon1fc65f580103`)
- L25 _enumerator_ `SYMS_LogFeature_DwarfCFIDecode = (1 << 5)` (scope `__anon1fc65f580103`)
- L26 _enumerator_ `SYMS_LogFeature_DwarfCFIApply = (1 << 6)` (scope `__anon1fc65f580103`)
- L27 _enumerator_ `SYMS_LogFeature_PEEpilog = (1 << 7)` (scope `__anon1fc65f580103`)
- L28 _enumerator_ `SYMS_LogFeature_PeResParser = (1 << 8)` (scope `__anon1fc65f580103`)
- L33 _enumerator_ `SYMS_LogFeature_Dummy = (1 << 31)` (scope `__anon1fc65f580103`) — Dummy flag shouldn't be associated to anything. This gives us a way to disable all logging.
- L42 _typedef_ `} SYMS_ProfChain;`
- L48 _typedef_ `} SYMS_ProfState;`
- L53 _typedef_ `} SYMS_ProfLock;`
- L73 _typedef_ `} SYMS_ProfTreeNode;`
- L85 _typedef_ `} SYMS_ProfTree;`
- L98 _prototype_ `SYMS_String8 syms_push_stringfv__dev(SYMS_Arena *arena, char *fmt, va_list args);`
- L99 _prototype_ `SYMS_String8 syms_push_stringf__dev(SYMS_Arena *arena, char *fmt, ...);`
- L101 _prototype_ `void syms_string_list_pushfv__dev(SYMS_Arena *arena, SYMS_String8List *list, char *fmt, va_list args);`
- L103 _prototype_ `void syms_string_list_pushf__dev(SYMS_Arena *arena, SYMS_String8List *list, char *fmt, ...);`
- L114 _macro_ `# define SYMS_LOG_RAW_APPEND(s) fwrite((s).str, (s).size, 1, stderr)`
- L117 _macro_ `# define SYMS_LOG_FILTER_FEATURES 0`
- L120 _macro_ `# define SYMS_LOG_FILTER_UID 0`
- L123 _prototype_ `void syms_log_set_filter__dev(SYMS_LogFeatures features, SYMS_U64 uid);`
- L125 _prototype_ `SYMS_U32 syms_log_open__dev(SYMS_B32 enabled);`
- L126 _prototype_ `void syms_log_close__dev(SYMS_U32 prev_state);`
- L127 _prototype_ `SYMS_B32 syms_log_is_enabled__dev(void);`
- L128 _prototype_ `SYMS_U32 syms_log_open_annotated__dev(SYMS_LogFeatures features, SYMS_U64 uid);`
- L130 _prototype_ `void syms_logfv__dev(char *fmt, va_list args);`
- L131 _prototype_ `void syms_logf__dev(char *fmt, ...);`
- L136 _macro_ `# define SYMS_LogOpen(ftr,uid,block) SYMS_U32 syms_log_state__##block = syms_log_open_annotated__dev((ftr),(uid))`
- L137 _macro_ `# define SYMS_LogClose(block) syms_log_close__dev(syms_log_state__##block)`
- L138 _macro_ `# define SYMS_Log(...) syms_logf__dev(__VA_ARGS__)`
- L139 _macro_ `# define SYMS_LogIsEnabled() syms_log_is_enabled__dev()`
- L141 _macro_ `# define SYMS_LogOpen(ftr,uid,block) ((void)0)`
- L142 _macro_ `# define SYMS_LogClose(block) ((void)0)`
- L143 _macro_ `# define SYMS_Log(fmt,...) ((void)0)`
- L144 _macro_ `# define SYMS_LogIsEnabled() (0)`
- L163 _macro_ `# define SYMS_PROF_BLOCK_SIZE (1 << 20)`
- L166 _prototype_ `void syms_prof_equip_thread__dev(SYMS_ProfState *prof_state);`
- L167 _prototype_ `void syms_prof_equip_thread_auto__dev(void);`
- L168 _prototype_ `void syms_prof_unequip_thread__dev(void);`
- L169 _prototype_ `SYMS_U64* syms_prof_push__dev(void);`
- L170 _prototype_ `void syms_prof_paste__dev(SYMS_ProfState *sub_state);`
- L172 _prototype_ `SYMS_ProfLock syms_prof_lock__dev(SYMS_Arena *arena);`
- L173 _prototype_ `void syms_prof_clear__dev(SYMS_ProfLock lock);`
- L174 _prototype_ `void syms_prof_unlock__dev(SYMS_ProfLock lock);`
- L176 _prototype_ `SYMS_ProfTree syms_prof_tree__dev(SYMS_Arena *arena, SYMS_String8 data);`
- L177 _prototype_ `void syms_prof_tree_sort_in_place__dev(SYMS_ProfTreeNode *root);`
- L178 _prototype_ `void syms_prof_tree_sort_pointer_array__dev(SYMS_ProfTreeNode **array, SYMS_U64 count);`
- L181 _prototype_ `void syms_prof_stringize_tree__dev(SYMS_Arena *arena, SYMS_ProfTree *tree, SYMS_String8List *out);`
- L183 _prototype_ `void syms_prof_stringize_tree__rec__dev(SYMS_Arena *arena, SYMS_ProfTreeNode *node, SYMS_String8List *out, SYMS_U64 align, SYMS_U64 indent);`
- L186 _prototype_ `void syms_prof_stringize_basic__dev(SYMS_Arena *arena, SYMS_ProfLock lock, SYMS_String8List *out);`
- L194 _macro_ `# define SYMS_ProfBegin(str) do{ SYMS_U64 t = SYMS_PROF_TIME(); SYMS_U64 *v = syms_prof_push__dev(); \`
- L199 _macro_ `# define SYMS_ProfEnd() do{ SYMS_U64 *v = syms_prof_push__dev(); \`
- L204 _macro_ `# define SYMS_ProfPasteSubChain(s) syms_prof_paste__dev(s)`
- L209 _macro_ `# define SYMS_ProfBegin(str) ((void)0)`
- L212 _macro_ `# define SYMS_ProfEnd() ((void)0)`
- L215 _macro_ `# define SYMS_ProfPasteSubChain(s) ((void)0)`

### `Source/Runtime/SymsLib/syms/core/base/syms_serial.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_SERIAL_H`
- L12 _macro_ `# define SYMS_ENABLE_BASE_SERIAL_INFO`
- L15 _macro_ `# define SYMS_ENABLE_DEBUG_INFO_SERIAL_INFO`
- L18 _macro_ `# define SYMS_ENABLE_CV_SERIAL_INFO`
- L21 _macro_ `# define SYMS_ENABLE_DWARF_SERIAL_INFO`
- L24 _macro_ `# define SYMS_ENABLE_COFF_SERIAL_INFO`
- L27 _macro_ `# define SYMS_ENABLE_PE_SERIAL_INFO`
- L30 _macro_ `# define SYMS_ENABLE_MACH_SERIAL_INFO`
- L33 _macro_ `# define SYMS_ENABLE_ELF_SERIAL_INFO`

### `Source/Runtime/SymsLib/syms/core/data_structures/syms_data_structures.h` (Other)


#### struct `SYMS_StringConsNode`  
`typedef struct SYMS_StringConsNode`  
_L14-18_
- L15 _public member_ `struct SYMS_StringConsNode *next;`
- L16 _public member_ `SYMS_String8 string;`
- L17 _public member_ `SYMS_U64 hash;`

#### struct `SYMS_StringCons`  
`typedef struct SYMS_StringCons`  
_L20-22_
- L21 _public member_ `SYMS_StringConsNode *buckets[SYMS_STRING_CONS_BUCKET_COUNT];`

#### struct `SYMS_DataIdxConsNode`  
`typedef struct SYMS_DataIdxConsNode`  
_L26-32_
- L27 _public member_ `struct SYMS_DataIdxConsNode *bucket_next;`
- L28 _public member_ `struct SYMS_DataIdxConsNode *all_next;`
- L29 _public member_ `SYMS_String8 data;`
- L30 _public member_ `SYMS_U64 hash;`
- L31 _public member_ `SYMS_U64 id;`

#### struct `SYMS_DataIdxCons`  
`typedef struct SYMS_DataIdxCons`  
_L34-41_
- L35 _public member_ `SYMS_DataIdxConsNode **buckets;`
- L36 _public member_ `SYMS_U64 bucket_count;`
- L37 _public member_ `SYMS_DataIdxConsNode *first;`
- L38 _public member_ `SYMS_DataIdxConsNode *last;`
- L39 _public member_ `SYMS_U64 count;`
- L40 _public member_ `SYMS_U64 total_size;`

#### struct `SYMS_U64Set`  
`typedef struct SYMS_U64Set`  
_L46-50_
- L47 _public member_ `SYMS_U64 *vals;`
- L48 _public member_ `SYMS_U64 count;`
- L49 _public member_ `SYMS_U64 cap;`

#### struct `SYMS_SpatialMap1DRange`  
`typedef struct SYMS_SpatialMap1DRange`  
_L59-62_
- L60 _public member_ `SYMS_U64Range range;`
- L61 _public member_ `SYMS_U64 val;`

#### struct `SYMS_SpatialMap1D`  
`typedef struct SYMS_SpatialMap1D`  
_L65-68_
- desc: TODO(allen): optimize this by using end points instead of ranges
- L66 _public member_ `SYMS_SpatialMap1DRange *ranges;`
- L67 _public member_ `SYMS_U64 count;`

#### struct `SYMS_SpatialMap1DNode`  
`typedef struct SYMS_SpatialMap1DNode`  
_L71-76_
- desc: - loose version
- L72 _public member_ `struct SYMS_SpatialMap1DNode *next;`
- L73 _public member_ `SYMS_U64Range range;`
- L74 _public member_ `SYMS_U64RangeArray ranges;`
- L75 _public member_ `SYMS_U64 val;`

#### struct `SYMS_SpatialMap1DLoose`  
`typedef struct SYMS_SpatialMap1DLoose`  
_L78-82_
- L79 _public member_ `SYMS_SpatialMap1DNode *first;`
- L80 _public member_ `SYMS_SpatialMap1DNode *last;`
- L81 _public member_ `SYMS_U64 total_count;`

#### struct `SYMS_SpatialMultiMap1D`  
`typedef struct SYMS_SpatialMultiMap1D`  
_L85-92_
- desc: - version with support for overlapping ranges
- L86 _public member_ `SYMS_SpatialMap1D spatial_map;`
- L88 _public member_ `SYMS_U64 *set_end_points;` — set_end_points length: (set_count + 1)
- L90 _public member_ `SYMS_U8 *set_data;` — set_data length: sizeof(SYMS_U64)*(set_end_points[set_count])
- L91 _public member_ `SYMS_U64 set_count;`

#### struct `SYMS_1DEndPoint`  
`typedef struct SYMS_1DEndPoint`  
_L94-98_
- L95 _public member_ `SYMS_U64 x;`
- L96 _public member_ `SYMS_U64 val;`
- L97 _public member_ `SYMS_B32 open;`

#### struct `SYMS_FileID2NameNode`  
`typedef struct SYMS_FileID2NameNode`  
_L108-115_
- L109 _public member_ `struct SYMS_FileID2NameNode *next;`
- L111 _public member_ `SYMS_UnitID uid;` — key
- L112 _public member_ `SYMS_FileID file_id;`
- L114 _public member_ `SYMS_String8 name;` — value

#### struct `SYMS_FileID2NameMap`  
`typedef struct SYMS_FileID2NameMap`  
_L117-120_
- L118 _public member_ `SYMS_FileID2NameNode *buckets[SYMS_FILE_ID_TO_NAME_MAP_BUCKET_COUNT];`
- L119 _public member_ `SYMS_U64 count;`

#### struct `SYMS_Name2FileIDMapUnit`  
`typedef struct SYMS_Name2FileIDMapUnit`  
_L134-137_
- L135 _public member_ `SYMS_UnitID uid;`
- L136 _public member_ `SYMS_FileID file_id;`

#### struct `SYMS_Name2FileIDMapFile`  
`typedef struct SYMS_Name2FileIDMapFile`  
_L139-143_
- L140 _public member_ `SYMS_String8 name;`
- L141 _public member_ `SYMS_Name2FileIDMapUnit *units;`
- L142 _public member_ `SYMS_U64 unit_count;`

#### struct `SYMS_Name2FileIDMap`  
`typedef struct SYMS_Name2FileIDMap`  
_L145-148_
- L146 _public member_ `SYMS_Name2FileIDMapFile *files;`
- L147 _public member_ `SYMS_U64 file_count;`

#### struct `SYMS_Name2FileIDMapUnitNode`  
`typedef struct SYMS_Name2FileIDMapUnitNode`  
_L151-155_
- desc: - loose version
- L152 _public member_ `struct SYMS_Name2FileIDMapUnitNode *next;`
- L153 _public member_ `SYMS_UnitID uid;`
- L154 _public member_ `SYMS_FileID file_id;`

#### struct `SYMS_Name2FileIDMapFileNode`  
`typedef struct SYMS_Name2FileIDMapFileNode`  
_L157-163_
- L158 _public member_ `struct SYMS_Name2FileIDMapFileNode *next;`
- L159 _public member_ `SYMS_String8 name;`
- L160 _public member_ `SYMS_Name2FileIDMapUnitNode *first;`
- L161 _public member_ `SYMS_Name2FileIDMapUnitNode *last;`
- L162 _public member_ `SYMS_U64 count;`

#### struct `SYMS_Name2FileIDMapLoose`  
`typedef struct SYMS_Name2FileIDMapLoose`  
_L165-169_
- L166 _public member_ `SYMS_Name2FileIDMapFileNode *first;`
- L167 _public member_ `SYMS_Name2FileIDMapFileNode *last;`
- L168 _public member_ `SYMS_U64 count;`

#### struct `SYMS_IDMapNode`  
`typedef struct SYMS_IDMapNode`  
_L180-185_
- L181 _public member_ `struct SYMS_IDMapNode *next;`
- L182 _public member_ `SYMS_U64 count;`
- L183 _public member_ `SYMS_U64 key[SYMS_ID_MAP_NODE_CAP];`
- L184 _public member_ `void *val[SYMS_ID_MAP_NODE_CAP];`

#### struct `SYMS_IDMap`  
`typedef struct SYMS_IDMap`  
_L187-191_
- L188 _public member_ `SYMS_IDMapNode **buckets;`
- L189 _public member_ `SYMS_U64 bucket_count;`
- L190 _public member_ `SYMS_U64 node_count;`

#### struct `SYMS_SymbolNameNode`  
`typedef struct SYMS_SymbolNameNode`  
_L204-209_
- L205 _public member_ `struct SYMS_SymbolNameNode *next_bucket;`
- L206 _public member_ `SYMS_String8 name;`
- L207 _public member_ `SYMS_U64 hash;`
- L208 _public member_ `SYMS_SymbolIDArray sid_array;`

#### struct `SYMS_SymbolNameMap`  
`typedef struct SYMS_SymbolNameMap`  
_L211-215_
- L212 _public member_ `SYMS_SymbolNameNode *buckets[SYMS_SYMBOL_NAME_MAP_BUCKET_COUNT];`
- L213 _public member_ `SYMS_SymbolNameNode *nodes;`
- L214 _public member_ `SYMS_U64 node_count;`

#### struct `SYMS_SymbolNameNodeLoose`  
`typedef struct SYMS_SymbolNameNodeLoose`  
_L218-224_
- desc: - loose version
- L219 _public member_ `struct SYMS_SymbolNameNodeLoose *next;`
- L220 _public member_ `struct SYMS_SymbolNameNodeLoose *next_bucket;`
- L221 _public member_ `SYMS_String8 name;`
- L222 _public member_ `SYMS_U64 hash;`
- L223 _public member_ `SYMS_SymbolIDList sid_list;`

#### struct `SYMS_SymbolNameMapLoose`  
`typedef struct SYMS_SymbolNameMapLoose`  
_L226-231_
- L227 _public member_ `SYMS_SymbolNameNodeLoose *buckets[SYMS_SYMBOL_NAME_MAP_BUCKET_COUNT];`
- L228 _public member_ `SYMS_SymbolNameNodeLoose *first;`
- L229 _public member_ `SYMS_SymbolNameNodeLoose *last;`
- L230 _public member_ `SYMS_U64 node_count;`

#### struct `SYMS_LineToAddrMap`  
`typedef struct SYMS_LineToAddrMap`  
_L237-245_
- L238 _public member_ `SYMS_U64Range *ranges;`
- L242 _public member_ `SYMS_U32 *line_range_indexes;` — line_range_indexes ranges from [0,line_count] inclusive so that: for-all i in [0,line_count): (line_range_indexes[i + 1] - line_range_indexes[i]) == # of ranges for line at index i
- L243 _public member_ `SYMS_U32 *line_numbers;`
- L244 _public member_ `SYMS_U64 line_count;`

#### struct `SYMS_FileToLineToAddrNode`  
`typedef struct SYMS_FileToLineToAddrNode`  
_L247-251_
- L248 _public member_ `struct SYMS_FileToLineToAddrNode *next;`
- L249 _public member_ `SYMS_FileID file_id;`
- L250 _public member_ `SYMS_LineToAddrMap *map;`

#### struct `SYMS_FileToLineToAddrMap`  
`typedef struct SYMS_FileToLineToAddrMap`  
_L253-256_
- L254 _public member_ `SYMS_FileToLineToAddrNode **buckets;`
- L255 _public member_ `SYMS_U64 bucket_count;`

#### struct `SYMS_FileToLineToAddrLooseLine`  
`typedef struct SYMS_FileToLineToAddrLooseLine`  
_L259-263_
- desc: - loose version
- L260 _public member_ `struct SYMS_FileToLineToAddrLooseLine *next;`
- L261 _public member_ `SYMS_U32 line;`
- L262 _public member_ `SYMS_U64RangeList ranges;`

#### struct `SYMS_FileToLineToAddrLooseFile`  
`typedef struct SYMS_FileToLineToAddrLooseFile`  
_L265-272_
- L266 _public member_ `struct SYMS_FileToLineToAddrLooseFile *next;`
- L267 _public member_ `SYMS_FileID file_id;`
- L268 _public member_ `SYMS_FileToLineToAddrLooseLine *first;`
- L269 _public member_ `SYMS_FileToLineToAddrLooseLine *last;`
- L270 _public member_ `SYMS_U64 line_count;`
- L271 _public member_ `SYMS_U64 range_count;`

#### struct `SYMS_FileToLineToAddrLoose`  
`typedef struct SYMS_FileToLineToAddrLoose`  
_L274-278_
- L275 _public member_ `SYMS_FileToLineToAddrLooseFile *first;`
- L276 _public member_ `SYMS_FileToLineToAddrLooseFile *last;`
- L277 _public member_ `SYMS_U64 count;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DATA_STRUCTURES_H`
- L12 _macro_ `#define SYMS_STRING_CONS_BUCKET_COUNT 1024`
- L18 _typedef_ `} SYMS_StringConsNode;`
- L22 _typedef_ `} SYMS_StringCons;`
- L32 _typedef_ `} SYMS_DataIdxConsNode;`
- L41 _typedef_ `} SYMS_DataIdxCons;`
- L50 _typedef_ `} SYMS_U64Set;`
- L62 _typedef_ `} SYMS_SpatialMap1DRange;`
- L68 _typedef_ `} SYMS_SpatialMap1D;`
- L76 _typedef_ `} SYMS_SpatialMap1DNode;`
- L82 _typedef_ `} SYMS_SpatialMap1DLoose;`
- L92 _typedef_ `} SYMS_SpatialMultiMap1D;`
- L98 _typedef_ `} SYMS_1DEndPoint;`
- L106 _macro_ `#define SYMS_FILE_ID_TO_NAME_MAP_BUCKET_COUNT 1024`
- L115 _typedef_ `} SYMS_FileID2NameNode;`
- L120 _typedef_ `} SYMS_FileID2NameMap;`
- L137 _typedef_ `} SYMS_Name2FileIDMapUnit;`
- L143 _typedef_ `} SYMS_Name2FileIDMapFile;`
- L148 _typedef_ `} SYMS_Name2FileIDMap;`
- L155 _typedef_ `} SYMS_Name2FileIDMapUnitNode;`
- L163 _typedef_ `} SYMS_Name2FileIDMapFileNode;`
- L169 _typedef_ `} SYMS_Name2FileIDMapLoose;`
- L178 _macro_ `#define SYMS_ID_MAP_NODE_CAP 3`
- L185 _typedef_ `} SYMS_IDMapNode;`
- L191 _typedef_ `} SYMS_IDMap;`
- L202 _macro_ `#define SYMS_SYMBOL_NAME_MAP_BUCKET_COUNT 1024`
- L209 _typedef_ `} SYMS_SymbolNameNode;`
- L215 _typedef_ `} SYMS_SymbolNameMap;`
- L224 _typedef_ `} SYMS_SymbolNameNodeLoose;`
- L231 _typedef_ `} SYMS_SymbolNameMapLoose;`
- L245 _typedef_ `} SYMS_LineToAddrMap;`
- L251 _typedef_ `} SYMS_FileToLineToAddrNode;`
- L256 _typedef_ `} SYMS_FileToLineToAddrMap;`
- L263 _typedef_ `} SYMS_FileToLineToAddrLooseLine;`
- L272 _typedef_ `} SYMS_FileToLineToAddrLooseFile;`
- L278 _typedef_ `} SYMS_FileToLineToAddrLoose;`
- L284 _prototype_ `SYMS_String8 syms_string_cons(SYMS_Arena *arena, SYMS_StringCons *cons, SYMS_String8 string);`
- L286 _prototype_ `SYMS_DataIdxCons syms_data_idx_cons_alloc(SYMS_Arena *arena, SYMS_U64 bucket_count);`
- L287 _prototype_ `SYMS_U64 syms_data_idx_cons(SYMS_Arena *arena, SYMS_DataIdxCons *cons, SYMS_String8 data);`
- L292 _prototype_ `SYMS_U64Set syms_u64_set_alloc(SYMS_Arena *arena, SYMS_U64 cap);`
- L293 _prototype_ `SYMS_U64 syms_u64_set__bs(SYMS_U64Set *set, SYMS_U64 x);`
- L294 _prototype_ `SYMS_B32 syms_u64_set_insert(SYMS_U64Set *set, SYMS_U64 x);`
- L295 _prototype_ `void syms_u64_set_erase(SYMS_U64Set *set, SYMS_U64 x);`
- L301 _prototype_ `SYMS_U64 syms_spatial_map_1d_binary_search(SYMS_SpatialMap1D *map, SYMS_U64 x);` — - lookups into spatial maps
- L302 _prototype_ `SYMS_U64 syms_spatial_map_1d_index_from_point(SYMS_SpatialMap1D *map, SYMS_U64 x);`
- L303 _prototype_ `SYMS_U64 syms_spatial_map_1d_value_from_point(SYMS_SpatialMap1D *map, SYMS_U64 x);`
- L306 _prototype_ `SYMS_SpatialMap1D syms_spatial_map_1d_copy(SYMS_Arena *arena, SYMS_SpatialMap1D *map);` — - copying spatial maps
- L309 _prototype_ `void syms_spatial_map_1d_loose_push(SYMS_Arena *arena, SYMS_SpatialMap1DLoose *loose, SYMS_U64 val, SYMS_U64RangeArray ranges);` — - constructing spatial maps
- L311 _prototype_ `void syms_spatial_map_1d_loose_push_single(SYMS_Arena *arena, SYMS_SpatialMap1DLoose *loose, SYMS_U64 val, SYMS_U64Range range);`
- L313 _prototype_ `SYMS_SpatialMap1D syms_spatial_map_1d_bake(SYMS_Arena *arena, SYMS_SpatialMap1DLoose *loose);`
- L315 _prototype_ `SYMS_B32 syms_spatial_map_1d_array_check_sorted(SYMS_SpatialMap1DRange *ranges, SYMS_U64 count);`
- L316 _prototype_ `void syms_spatial_map_1d_array_sort(SYMS_SpatialMap1DRange *ranges, SYMS_U64 count);`
- L317 _prototype_ `void syms_spatial_map_1d_array_sort__rec(SYMS_SpatialMap1DRange *ranges, SYMS_U64 count);`
- L320 _prototype_ `SYMS_SpatialMultiMap1D syms_spatial_multi_map_1d_bake(SYMS_Arena *arena, SYMS_SpatialMap1DLoose *loose);` — - support for the overlapping ranges
- L322 _prototype_ `SYMS_U64Array syms_spatial_multi_map_1d_array_from_point(SYMS_SpatialMultiMap1D *map, SYMS_U64 x);`
- L324 _prototype_ `void syms_spatial_map_1d_endpoint_sort(SYMS_1DEndPoint *endpoints, SYMS_U64 count);`
- L329 _prototype_ `SYMS_B32 syms_spatial_map_1d_invariants(SYMS_SpatialMap1D *map);` — - invariants for spatial maps
- L335 _prototype_ `SYMS_U64 syms_file_id_2_name_map_hash(SYMS_UnitID uid, SYMS_FileID file_id);` — - shared file id bucket definitions
- L338 _prototype_ `SYMS_String8 syms_file_id_2_name_map_name_from_id(SYMS_FileID2NameMap *map, SYMS_UnitID uid, SYMS_FileID file_id);` — - lookups into file id buckets
- L342 _prototype_ `SYMS_FileID2NameMap syms_file_id_2_name_map_copy(SYMS_Arena *arena, SYMS_StringCons *cons_optional, SYMS_FileID2NameMap *map);` — - copying file id buckets
- L346 _prototype_ `void syms_file_id_2_name_map_insert(SYMS_Arena *arena, SYMS_FileID2NameMap *map, SYMS_UnitID uid, SYMS_FileID file_id, SYMS_String8 name);` — - constructing file id buckets
- L355 _prototype_ `SYMS_Name2FileIDMap syms_name_2_file_id_map_copy(SYMS_Arena *arena, SYMS_StringCons *cons_optional, SYMS_Name2FileIDMap *file_map);` — - copying file maps
- L359 _prototype_ `SYMS_Name2FileIDMap syms_name_2_file_id_map_bake(SYMS_Arena *arena, SYMS_Name2FileIDMapLoose *loose);` — - constructing file maps
- L361 _prototype_ `void syms_name_2_file_id_map_loose_push(SYMS_Arena *arena, SYMS_Name2FileIDMapLoose *map, SYMS_String8 name_cons, SYMS_UnitID uid, SYMS_FileID file_id);` — allen: Strings passed to this function should all be cons'ed in the same cons structure first.
- L370 _prototype_ `SYMS_IDMap syms_id_map_copy(SYMS_Arena *arena, SYMS_IDMap *map);` — - copying id maps
- L373 _prototype_ `void* syms_id_map_ptr_from_u64(SYMS_IDMap *map, SYMS_U64 key);` — - lookups into id map
- L376 _prototype_ `SYMS_IDMap syms_id_map_alloc(SYMS_Arena *arena, SYMS_U64 bucket_count);` — - constructing id maps
- L377 _prototype_ `void syms_id_map_insert(SYMS_Arena *arena, SYMS_IDMap *map, SYMS_U64 key, void *val);`
- L386 _prototype_ `SYMS_SymbolIDArray syms_symbol_name_map_array_from_string(SYMS_SymbolNameMap *map, SYMS_String8 string);` — - lookups into symbol name map
- L389 _prototype_ `void syms_symbol_name_map_push(SYMS_Arena *arena, SYMS_SymbolNameMapLoose *map, SYMS_String8 name, SYMS_SymbolID sid);` — - constructing symbol name maps
- L391 _prototype_ `SYMS_SymbolNameMap syms_symbol_name_map_bake(SYMS_Arena *arena, SYMS_SymbolNameMapLoose *loose);`
- L399 _prototype_ `SYMS_U64 syms_line_index_from_voff__binary_search(SYMS_Line *lines, SYMS_U64 ender_index, SYMS_U64 voff);` — - lookups into line tables
- L400 _prototype_ `SYMS_Line syms_line_from_sequence_voff(SYMS_LineTable *line_table, SYMS_U64 seq_index, SYMS_U64 voff);`
- L403 _prototype_ `SYMS_LineTable syms_line_table_copy(SYMS_Arena *arena, SYMS_LineTable *line_table);` — - copying and rewriting line tables
- L404 _prototype_ `void syms_line_table_rewrite_file_ids_in_place(SYMS_FileIDArray *file_ids, SYMS_LineTable *line_table_in_out);`
- L406 _prototype_ `SYMS_LineTable syms_line_table_with_indexes_from_parse(SYMS_Arena *arena, SYMS_LineParseOut *parse);`
- L413 _prototype_ `syms_line_to_addr_map_from_line_table(SYMS_Arena *arena, SYMS_LineTable *table);`
- L416 _prototype_ `SYMS_LineToAddrMap* syms_line_to_addr_map_lookup_file_id(SYMS_FileToLineToAddrMap *map, SYMS_FileID file_id);` — - line-to-addr query
- L419 _prototype_ `SYMS_U64RangeArray syms_line_to_addr_map_lookup_nearest_line_number(SYMS_LineToAddrMap *map, SYMS_U32 line, SYMS_U32 *actual_line_out);`
- L424 _prototype_ `void syms_line_to_addr_line_sort(SYMS_FileToLineToAddrLooseLine **array, SYMS_U64 count);` — - line-to-addr map helpers
- L425 _prototype_ `void syms_line_to_addr_line_sort__rec(SYMS_FileToLineToAddrLooseLine **array, SYMS_U64 count);`
- L430 _prototype_ `SYMS_String8Array syms_string_array_copy(SYMS_Arena *arena, SYMS_StringCons *cons_optional, SYMS_String8Array *array);`
- L433 _prototype_ `SYMS_LinkNameRecArray syms_link_name_record_copy(SYMS_Arena *arena, SYMS_LinkNameRecArray *array);`
- L438 _prototype_ `SYMS_U64 syms_index_from_n__u32__binary_search_round_up(SYMS_U32 *v, SYMS_U64 count, SYMS_U32 n);`

### `Source/Runtime/SymsLib/syms/core/dwarf/syms_dwarf.h` (Other)


#### enum `SYMS_DwCompUnitKind`  
`typedef enum SYMS_DwCompUnitKind`  
_L15-26_
- L17 _public enumerator_ `SYMS_DwCompUnitKind_RESERVED = 0x00`
- L18 _public enumerator_ `SYMS_DwCompUnitKind_COMPILE = 0x01`
- L19 _public enumerator_ `SYMS_DwCompUnitKind_TYPE = 0x02`
- L20 _public enumerator_ `SYMS_DwCompUnitKind_PARTIAL = 0x03`
- L21 _public enumerator_ `SYMS_DwCompUnitKind_SKELETON = 0x04`
- L22 _public enumerator_ `SYMS_DwCompUnitKind_SPLIT_COMPILE = 0x05`
- L23 _public enumerator_ `SYMS_DwCompUnitKind_SPLIT_TYPE = 0x06`
- L24 _public enumerator_ `SYMS_DwCompUnitKind_LO_USER = 0x80`
- L25 _public enumerator_ `SYMS_DwCompUnitKind_HI_USER = 0xff`

#### enum `SYMS_DwLNCT`  
`typedef enum SYMS_DwLNCT`  
_L29-38_
- L31 _public enumerator_ `SYMS_DwLNCT_PATH = 0x1`
- L32 _public enumerator_ `SYMS_DwLNCT_DIRECTORY_INDEX = 0x2`
- L33 _public enumerator_ `SYMS_DwLNCT_TIMESTAMP = 0x3`
- L34 _public enumerator_ `SYMS_DwLNCT_SIZE = 0x4`
- L35 _public enumerator_ `SYMS_DwLNCT_MD5 = 0x5`
- L36 _public enumerator_ `SYMS_DwLNCT_USER_LO = 0x2000`
- L37 _public enumerator_ `SYMS_DwLNCT_USER_HI = 0x3fff`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DWARF_H`
- L27 _typedef_ `SYMS_DwCompUnitKind;`
- L39 _typedef_ `SYMS_DwLNCT;`
- L46 _prototype_ `SYMS_String8 syms_dw_name_string_from_section_kind(SYMS_DwSectionKind kind);`
- L47 _prototype_ `SYMS_String8 syms_dw_mach_name_string_from_section_kind(SYMS_DwSectionKind kind);`
- L49 _prototype_ `SYMS_String8 syms_dw_dwo_name_string_from_section_kind(SYMS_DwSectionKind kind);`
- L50 _prototype_ `SYMS_U64 syms_dw_offset_size_from_mode(SYMS_DwMode mode);`
- L51 _prototype_ `SYMS_B32 syms_dw_are_attrib_class_and_form_kind_compatible(SYMS_DwAttribClass attrib_class, SYMS_DwFormKind form_kind);`
- L52 _prototype_ `SYMS_TypeKind syms_dw_type_kind_from_tag_encoding_size(SYMS_DwTagKind tag_kind, SYMS_DwAttribTypeEncoding encoding, SYMS_U64 size);`
- L53 _prototype_ `SYMS_TypeModifiers syms_dw_type_modifiers_from_tag_kind(SYMS_DwTagKind tag_kind);`
- L55 _prototype_ `SYMS_DwAttribClass syms_dw_attrib_class_from_attrib_kind_extensions(SYMS_DwAttribKind attrib);`
- L56 _prototype_ `SYMS_DwAttribClass syms_dw_attrib_class_from_attrib_kind_v2(SYMS_DwAttribKind attrib);`
- L57 _prototype_ `SYMS_DwAttribClass syms_dw_attrib_class_from_form_kind_v2(SYMS_DwFormKind form);`

### `Source/Runtime/SymsLib/syms/core/dwarf/syms_dwarf_expr.h` (Other)


#### struct `SYMS_DwRegsX64`  
`typedef struct SYMS_DwRegsX64`  
_L15-38_

#### union `SYMS_DwRegsX64::(anonymous)`  
`union`  
_L16-37_

#### struct `SYMS_DwRegsX64::__anon4e7f9f44010a::(anonymous)`  
`struct`  
_L17-35_

#### struct `SYMS_DwExprMachineCallConfig`  
`typedef struct SYMS_DwExprMachineCallConfig`  
_L78-81_
- L79 _public member_ `void *user_ptr;`
- L80 _public member_ `SYMS_DwExprResolveCallFunc *func;`

#### struct `SYMS_DwExprMachineConfig`  
`typedef struct SYMS_DwExprMachineConfig`  
_L83-94_
- L85 _public member_ `SYMS_U64 max_step_count;` — (read only in the eval functions)
- L86 _public member_ `SYMS_MemoryView *memview;`
- L87 _public member_ `SYMS_DwRegsX64 *regs;`
- L88 _public member_ `SYMS_U64 *text_section_base;`
- L89 _public member_ `SYMS_U64 *frame_base;`
- L90 _public member_ `SYMS_U64 *object_address;`
- L91 _public member_ `SYMS_U64 *tls_address;`
- L92 _public member_ `SYMS_U64 *cfa;`
- L93 _public member_ `SYMS_DwExprMachineCallConfig call;`

#### enum `(anonymous)`  
`enum`  
_L99-113_

#### struct `SYMS_DwExprAnalysis`  
`typedef struct SYMS_DwExprAnalysis`  
_L115-117_
- L116 _public member_ `SYMS_DwExprFlags flags;`

#### struct `SYMS_DwExprAnalysisTask`  
`typedef struct SYMS_DwExprAnalysisTask`  
_L119-123_
- L120 _public member_ `struct SYMS_DwExprAnalysisTask *next;`
- L121 _public member_ `SYMS_U64 p;`
- L122 _public member_ `SYMS_String8 data;`

#### enum `SYMS_DwSimpleLocKind`  
`typedef enum SYMS_DwSimpleLocKind`  
_L127-134_
- desc: - location types
- L128 _public enumerator_ `SYMS_DwSimpleLocKind_Address`
- L129 _public enumerator_ `SYMS_DwSimpleLocKind_Register`
- L130 _public enumerator_ `SYMS_DwSimpleLocKind_Value`
- L131 _public enumerator_ `SYMS_DwSimpleLocKind_ValueLong`
- L132 _public enumerator_ `SYMS_DwSimpleLocKind_Empty`
- L133 _public enumerator_ `SYMS_DwSimpleLocKind_Fail`

#### enum `SYMS_DwLocFailKind`  
`typedef enum SYMS_DwLocFailKind`  
_L136-157_
- L144 _public enumerator_ `SYMS_DwLocFailKind_BadData`
- L145 _public enumerator_ `SYMS_DwLocFailKind_NotSupported`
- L146 _public enumerator_ `SYMS_DwLocFailKind_TimeOut`
- L147 _public enumerator_ `SYMS_DwLocFailKind_TooComplicated`
- L148 _public enumerator_ `SYMS_DwLocFailKind_MissingTextBase`
- L149 _public enumerator_ `SYMS_DwLocFailKind_MissingMemory`
- L150 _public enumerator_ `SYMS_DwLocFailKind_MissingRegisters`
- L151 _public enumerator_ `SYMS_DwLocFailKind_MissingFrameBase`
- L152 _public enumerator_ `SYMS_DwLocFailKind_MissingObjectAddress`
- L153 _public enumerator_ `SYMS_DwLocFailKind_MissingTLSAddress`
- L154 _public enumerator_ `SYMS_DwLocFailKind_MissingCFA`
- L155 _public enumerator_ `SYMS_DwLocFailKind_MissingCallResolution`
- L156 _public enumerator_ `SYMS_DwLocFailKind_MissingArenaForComposite`

#### struct `SYMS_DwSimpleLoc`  
`typedef struct SYMS_DwSimpleLoc`  
_L159-171_
- L160 _public member_ `SYMS_DwSimpleLocKind kind;`

#### union `SYMS_DwSimpleLoc::(anonymous)`  
`union`  
_L161-170_

#### struct `SYMS_DwSimpleLoc::__anon4e7f9f44040a::(anonymous)`  
`struct`  
_L166-169_

#### struct `SYMS_DwPiece`  
`typedef struct SYMS_DwPiece`  
_L173-184_
- L179 _public member_ `struct SYMS_DwPiece *next;`
- L180 _public member_ `SYMS_DwSimpleLoc loc;`
- L181 _public member_ `SYMS_U64 bit_size;`
- L182 _public member_ `SYMS_U64 bit_off;`
- L183 _public member_ `SYMS_B32 is_bit_loc;`

#### struct `SYMS_DwLocation`  
`typedef struct SYMS_DwLocation`  
_L186-215_
- L210 _public member_ `SYMS_DwPiece *first_piece;`
- L211 _public member_ `SYMS_DwPiece *last_piece;`
- L212 _public member_ `SYMS_U64 count;`
- L214 _public member_ `SYMS_DwSimpleLoc non_piece_loc;`

#### struct `SYMS_DwExprStackNode`  
`typedef struct SYMS_DwExprStackNode`  
_L219-222_
- desc: - full evaluator state types
- L220 _public member_ `struct SYMS_DwExprStackNode *next;`
- L221 _public member_ `SYMS_U64 val;`

#### struct `SYMS_DwExprStack`  
`typedef struct SYMS_DwExprStack`  
_L224-228_
- L225 _public member_ `SYMS_DwExprStackNode *stack;`
- L226 _public member_ `SYMS_DwExprStackNode *free_nodes;`
- L227 _public member_ `SYMS_U64 count;`

#### struct `SYMS_DwExprCall`  
`typedef struct SYMS_DwExprCall`  
_L230-235_
- L231 _public member_ `struct SYMS_DwExprCall *next;`
- L232 _public member_ `void *ptr;`
- L233 _public member_ `SYMS_U64 size;`
- L234 _public member_ `SYMS_U64 cursor;`

#### struct `SYMS_DwExprCallStack`  
`typedef struct SYMS_DwExprCallStack`  
_L237-241_
- L238 _public member_ `SYMS_DwExprCall *stack;`
- L239 _public member_ `SYMS_DwExprCall *free_calls;`
- L240 _public member_ `SYMS_U64 depth;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DWARF_EXPR_H`
- L18 _member_ `SYMS_U64 rax;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L19 _member_ `SYMS_U64 rdx;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L20 _member_ `SYMS_U64 rcx;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L21 _member_ `SYMS_U64 rbx;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L22 _member_ `SYMS_U64 rsi;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L23 _member_ `SYMS_U64 rdi;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L24 _member_ `SYMS_U64 rbp;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L25 _member_ `SYMS_U64 rsp;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L26 _member_ `SYMS_U64 r8;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L27 _member_ `SYMS_U64 r9;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L28 _member_ `SYMS_U64 r10;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L29 _member_ `SYMS_U64 r11;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L30 _member_ `SYMS_U64 r12;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L31 _member_ `SYMS_U64 r13;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L32 _member_ `SYMS_U64 r14;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L33 _member_ `SYMS_U64 r15;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L34 _member_ `SYMS_U64 rip;` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a::__anon4e7f9f440208`)
- L36 _member_ `SYMS_U64 r[17];` (scope `SYMS_DwRegsX64::__anon4e7f9f44010a`)
- L38 _typedef_ `} SYMS_DwRegsX64;`
- L40 _variable_ `SYMS_GLOBAL SYMS_READ_ONLY SYMS_RegID syms_dw_reg_table_x64[] = { SYMS_RegX64Code_rax, SYMS_RegX64Code_rdx, SYMS_RegX64Code_rcx, SYMS_RegX64Code_rbx, SYMS_RegX64Code_rsi, SYMS_RegX64Code_rdi, SYMS_RegX64Code_rbp, SYMS_RegX64Code_rsp, SYMS_RegX64Code_r8, SYMS_RegX64Code_r9, SYMS_RegX64Code_r10, SYMS_RegX64Code_r11, SYMS_RegX64Code_r12, SYMS_RegX64Code_r13, SYMS_RegX64Code_r14, SYMS_RegX64Code_r15, SYMS_RegX64Code_rip, };`
- L60 _variable_ `SYMS_GLOBAL SYMS_READ_ONLY SYMS_RegID syms_dw_reg_table_x86[] = { SYMS_RegX86Code_eax, SYMS_RegX86Code_edx, SYMS_RegX86Code_ecx, SYMS_RegX86Code_ebx, SYMS_RegX86Code_esi, SYMS_RegX86Code_edi, SYMS_RegX86Code_ebp, SYMS_RegX86Code_esp, SYMS_RegX86Code_eip, };`
- L76 _typedef_ `typedef SYMS_String8 SYMS_DwExprResolveCallFunc(void *call_user_ptr, SYMS_U64 p);` — - machine configuration types
- L81 _typedef_ `} SYMS_DwExprMachineCallConfig;`
- L94 _typedef_ `} SYMS_DwExprMachineConfig;`
- L98 _typedef_ `typedef SYMS_U32 SYMS_DwExprFlags;` — - detail analysis types
- L100 _enumerator_ `SYMS_DwExprFlag_UsesTextBase = (1 << 0)` (scope `__anon4e7f9f440303`)
- L101 _enumerator_ `SYMS_DwExprFlag_UsesMemory = (1 << 1)` (scope `__anon4e7f9f440303`)
- L102 _enumerator_ `SYMS_DwExprFlag_UsesRegisters = (1 << 2)` (scope `__anon4e7f9f440303`)
- L103 _enumerator_ `SYMS_DwExprFlag_UsesFrameBase = (1 << 3)` (scope `__anon4e7f9f440303`)
- L104 _enumerator_ `SYMS_DwExprFlag_UsesObjectAddress = (1 << 4)` (scope `__anon4e7f9f440303`)
- L105 _enumerator_ `SYMS_DwExprFlag_UsesTLSAddress = (1 << 5)` (scope `__anon4e7f9f440303`)
- L106 _enumerator_ `SYMS_DwExprFlag_UsesCFA = (1 << 6)` (scope `__anon4e7f9f440303`)
- L107 _enumerator_ `SYMS_DwExprFlag_UsesCallResolution = (1 << 7)` (scope `__anon4e7f9f440303`)
- L108 _enumerator_ `SYMS_DwExprFlag_UsesComposite = (1 << 8)` (scope `__anon4e7f9f440303`)
- L110 _enumerator_ `SYMS_DwExprFlag_NotSupported = (1 << 16)` (scope `__anon4e7f9f440303`)
- L111 _enumerator_ `SYMS_DwExprFlag_BadData = (1 << 17)` (scope `__anon4e7f9f440303`)
- L112 _enumerator_ `SYMS_DwExprFlag_NonLinearFlow = (1 << 18)` (scope `__anon4e7f9f440303`)
- L117 _typedef_ `} SYMS_DwExprAnalysis;`
- L123 _typedef_ `} SYMS_DwExprAnalysisTask;`
- L134 _typedef_ `SYMS_DwSimpleLocKind_ValueLong, SYMS_DwSimpleLocKind_Empty, SYMS_DwSimpleLocKind_Fail, } SYMS_DwSimpleLocKind;`
- L157 _typedef_ `SYMS_DwLocFailKind_MissingCFA, SYMS_DwLocFailKind_MissingCallResolution, SYMS_DwLocFailKind_MissingArenaForComposite, } SYMS_DwLocFailKind;`
- L162 _member_ `SYMS_U64 addr;` (scope `SYMS_DwSimpleLoc::__anon4e7f9f44040a`)
- L163 _member_ `SYMS_U64 reg_idx;` (scope `SYMS_DwSimpleLoc::__anon4e7f9f44040a`)
- L164 _member_ `SYMS_U64 val;` (scope `SYMS_DwSimpleLoc::__anon4e7f9f44040a`)
- L165 _member_ `SYMS_String8 val_long;` (scope `SYMS_DwSimpleLoc::__anon4e7f9f44040a`)
- L167 _member_ `SYMS_DwLocFailKind fail_kind;` (scope `SYMS_DwSimpleLoc::__anon4e7f9f44040a::__anon4e7f9f440508`)
- L168 _member_ `SYMS_U64 fail_data;` (scope `SYMS_DwSimpleLoc::__anon4e7f9f44040a::__anon4e7f9f440508`)
- L171 _typedef_ `} SYMS_DwSimpleLoc;`
- L184 _typedef_ `} SYMS_DwPiece;`
- L215 _typedef_ `} SYMS_DwLocation;`
- L222 _typedef_ `} SYMS_DwExprStackNode;`
- L228 _typedef_ `} SYMS_DwExprStack;`
- L235 _typedef_ `} SYMS_DwExprCall;`
- L241 _typedef_ `} SYMS_DwExprCallStack;`
- L265 _prototype_ `SYMS_DwSimpleLoc syms_dw_expr__analyze_fast(void *base, SYMS_U64Range range, SYMS_U64 text_section_base);`
- L299 _prototype_ `SYMS_DwExprAnalysis syms_dw_expr__analyze_details(void *base, SYMS_U64Range range, SYMS_DwExprMachineCallConfig *call_config);`
- L306 _prototype_ `SYMS_DwLocation syms_dw_expr__eval(SYMS_Arena *arena_optional, void *base, SYMS_U64Range range, SYMS_DwExprMachineConfig *config);` — - full eval
- L311 _prototype_ `SYMS_DwExprStack syms_dw_expr__stack_make(SYMS_Arena *arena);` — - dw expr val stack
- L312 _prototype_ `void syms_dw_expr__stack_push(SYMS_Arena *arena, SYMS_DwExprStack *stack, SYMS_U64 x);`
- L313 _prototype_ `SYMS_U64 syms_dw_expr__stack_pop(SYMS_DwExprStack *stack);`
- L314 _prototype_ `SYMS_U64 syms_dw_expr__stack_pick(SYMS_DwExprStack *stack, SYMS_U64 idx);`
- L315 _prototype_ `SYMS_B32 syms_dw_expr__stack_is_empty(SYMS_DwExprStack *stack);`
- L318 _prototype_ `SYMS_DwExprCall* syms_dw_expr__call_top(SYMS_DwExprCallStack *stack);` — - dw expr call stack
- L319 _prototype_ `void syms_dw_expr__call_push(SYMS_Arena *arena, SYMS_DwExprCallStack *stack, void *ptr, SYMS_U64 size);`
- L321 _prototype_ `void syms_dw_expr__call_pop(SYMS_DwExprCallStack *stack);`
- L325 _prototype_ `SYMS_DwExprAnalysisTask* syms_dw_expr__analysis_task_from_p(SYMS_DwExprAnalysisTask *first, SYMS_U64 p);` — - analysis tasks

### `Source/Runtime/SymsLib/syms/core/dwarf/syms_dwarf_parser.h` (Other)


#### struct `SYMS_DwUnitRangePoint`  
`struct SYMS_DwUnitRangePoint`  
_L23-28_
- L25 _public member_ `SYMS_U64 p;`
- L26 _public member_ `SYMS_UnitID uid;`
- L27 _public member_ `SYMS_B32 is_min;`

#### struct `SYMS_DwSymbolIDChunk`  
`struct SYMS_DwSymbolIDChunk`  
_L31-36_
- L33 _public member_ `SYMS_DwSymbolIDChunk *next;`
- L34 _public member_ `SYMS_U64 count;`
- L35 _public member_ `SYMS_SymbolID ids[1022];`

#### struct `SYMS_DwSymbolIDChunkList`  
`struct SYMS_DwSymbolIDChunkList`  
_L39-45_
- L41 _public member_ `SYMS_U64 chunk_count;`
- L42 _public member_ `SYMS_U64 total_id_count;`
- L43 _public member_ `SYMS_DwSymbolIDChunk *first;`
- L44 _public member_ `SYMS_DwSymbolIDChunk *last;`

#### struct `SYMS_DwExtDebugRef`  
`struct SYMS_DwExtDebugRef`  
_L51-56_
- L54 _public member_ `SYMS_String8 dwo_path;` — NOTE(rjf): .dwo => an external DWARF V5 .dwo file
- L55 _public member_ `SYMS_U64 dwo_id;`

#### struct `SYMS_DwAbbrevTableEntry`  
`struct SYMS_DwAbbrevTableEntry`  
_L62-66_
- L64 _public member_ `SYMS_U64 id;`
- L65 _public member_ `SYMS_U64 off;`

#### struct `SYMS_DwAbbrevTable`  
`struct SYMS_DwAbbrevTable`  
_L69-73_
- L71 _public member_ `SYMS_U64 count;`
- L72 _public member_ `SYMS_DwAbbrevTableEntry *entries;`

#### struct `SYMS_DwSection`  
`struct SYMS_DwSection`  
_L79-82_
- L81 _public member_ `SYMS_U64Range range;`

#### struct `SYMS_DwUnitRangeInfo`  
`struct SYMS_DwUnitRangeInfo`  
_L85-90_
- L87 _public member_ `SYMS_UnitID uid;`
- L88 _public member_ `SYMS_U64Range frange;` — rjf: .debug_info range in file
- L89 _public member_ `SYMS_U64RangeArray addr_ranges;` — rjf: .debug_aranges

#### struct `SYMS_DwDbgAccel`  
`struct SYMS_DwDbgAccel`  
_L93-105_
- L95 _public member_ `SYMS_FileFormat format;`
- L96 _public member_ `SYMS_Arch arch;`
- L97 _public member_ `SYMS_U64 vbase;`
- L98 _public member_ `SYMS_SecInfoArray sections;`
- L99 _public member_ `SYMS_U64 text_section_idx;`
- L100 _public member_ `SYMS_U64Range acceptable_vrange;`
- L101 _public member_ `SYMS_DwSection *section_map;` — NOTE(rjf): treat as [SYMS_DwSectionKind_COUNT] array
- L102 _public member_ `SYMS_U64 unit_count;`
- L103 _public member_ `SYMS_DwUnitRangeInfo *unit_range_info;`
- L104 _public member_ `SYMS_B32 is_dwo;`

#### struct `SYMS_DwLineFile`  
`struct SYMS_DwLineFile`  
_L111-118_
- L113 _public member_ `SYMS_String8 file_name;`
- L114 _public member_ `SYMS_U64 dir_idx;`
- L115 _public member_ `SYMS_U64 modify_time;`
- L116 _public member_ `SYMS_U64 md5_digest[2];`
- L117 _public member_ `SYMS_U64 file_size;`

#### struct `SYMS_DwLineVMFileNode`  
`struct SYMS_DwLineVMFileNode`  
_L121-125_
- L123 _public member_ `SYMS_DwLineVMFileNode *next;`
- L124 _public member_ `SYMS_DwLineFile file;`

#### struct `SYMS_DwLineVMFileList`  
`struct SYMS_DwLineVMFileList`  
_L128-133_
- L130 _public member_ `SYMS_U64 node_count;`
- L131 _public member_ `SYMS_DwLineVMFileNode *first;`
- L132 _public member_ `SYMS_DwLineVMFileNode *last;`

#### struct `SYMS_DwLineVMFileArray`  
`struct SYMS_DwLineVMFileArray`  
_L136-140_
- L138 _public member_ `SYMS_U64 count;`
- L139 _public member_ `SYMS_DwLineFile *v;`

#### enum `SYMS_DwAbbrevKind`  
`typedef enum SYMS_DwAbbrevKind`  
_L145-153_
- L147 _public enumerator_ `SYMS_DwAbbrevKind_Null`
- L148 _public enumerator_ `SYMS_DwAbbrevKind_Tag`
- L149 _public enumerator_ `SYMS_DwAbbrevKind_Attrib`
- L150 _public enumerator_ `SYMS_DwAbbrevKind_AttribSequenceEnd`
- L151 _public enumerator_ `SYMS_DwAbbrevKind_DIEBegin`
- L152 _public enumerator_ `SYMS_DwAbbrevKind_DIEEnd`

#### enum `(anonymous)`  
`enum`  
_L157-160_

#### struct `SYMS_DwAbbrev`  
`struct SYMS_DwAbbrev`  
_L163-171_
- L165 _public member_ `SYMS_DwAbbrevKind kind;`
- L166 _public member_ `SYMS_U64Range abbrev_range;`
- L167 _public member_ `SYMS_U64 sub_kind;`
- L168 _public member_ `SYMS_U64 id;`
- L169 _public member_ `SYMS_U64 const_value;`
- L170 _public member_ `SYMS_DwAbbrevFlags flags;`

#### struct `SYMS_DwAttribValueResolveParams`  
`struct SYMS_DwAttribValueResolveParams`  
_L177-187_
- L179 _public member_ `SYMS_DwVersion version;`
- L180 _public member_ `SYMS_DwLanguage language;`
- L181 _public member_ `SYMS_U64 addr_size;` — NOTE(rjf): size in bytes of containing compilation unit's addresses
- L182 _public member_ `SYMS_U64 containing_unit_info_off;` — NOTE(rjf): containing compilation unit's offset into the .debug_info section
- L183 _public member_ `SYMS_U64 debug_addrs_base;` — NOTE(rjf): containing compilation unit's offset into the .debug_addrs section       (DWARF V5 ONLY)
- L184 _public member_ `SYMS_U64 debug_rnglists_base;` — NOTE(rjf): containing compilation unit's offset into the .debug_rnglists section    (DWARF V5 ONLY)
- L185 _public member_ `SYMS_U64 debug_str_offs_base;` — NOTE(rjf): containing compilation unit's offset into the .debug_str_offsets section (DWARF V5 ONLY)
- L186 _public member_ `SYMS_U64 debug_loclists_base;` — NOTE(rjf): containing compilation unit's offset into the .debug_loclists section    (DWARF V5 ONLY)

#### struct `SYMS_DwAttribValue`  
`struct SYMS_DwAttribValue`  
_L190-194_
- L192 _public member_ `SYMS_DwSectionKind section;`
- L193 _public member_ `SYMS_U64 v[2];`

#### struct `SYMS_DwAttrib`  
`struct SYMS_DwAttrib`  
_L197-205_
- L199 _public member_ `SYMS_U64 info_off;`
- L200 _public member_ `SYMS_U64 abbrev_id;`
- L201 _public member_ `SYMS_DwAttribKind attrib_kind;`
- L202 _public member_ `SYMS_DwFormKind form_kind;`
- L203 _public member_ `SYMS_DwAttribClass value_class;`
- L204 _public member_ `SYMS_DwAttribValue form_value;`

#### struct `SYMS_DwAttribArray`  
`struct SYMS_DwAttribArray`  
_L208-212_
- L210 _public member_ `SYMS_DwAttrib *v;`
- L211 _public member_ `SYMS_U64 count;`

#### struct `SYMS_DwAttribNode`  
`struct SYMS_DwAttribNode`  
_L215-219_
- L217 _public member_ `SYMS_DwAttribNode *next;`
- L218 _public member_ `SYMS_DwAttrib attrib;`

#### struct `SYMS_DwAttribList`  
`struct SYMS_DwAttribList`  
_L222-227_
- L224 _public member_ `SYMS_DwAttribNode *first;`
- L225 _public member_ `SYMS_DwAttribNode *last;`
- L226 _public member_ `SYMS_U64 count;`

#### struct `SYMS_DwAttribListParseResult`  
`struct SYMS_DwAttribListParseResult`  
_L230-235_
- L232 _public member_ `SYMS_DwAttribList attribs;`
- L233 _public member_ `SYMS_U64 max_info_off;`
- L234 _public member_ `SYMS_U64 max_abbrev_off;`

#### struct `SYMS_DwCompRoot`  
`struct SYMS_DwCompRoot`  
_L241-278_
- L244 _public member_ `SYMS_U64 size;` — NOTE(rjf): Header Data
- L245 _public member_ `SYMS_DwCompUnitKind kind;`
- L246 _public member_ `SYMS_DwVersion version;`
- L247 _public member_ `SYMS_U64 address_size;`
- L248 _public member_ `SYMS_U64 abbrev_off;`
- L249 _public member_ `SYMS_U64 info_off;`
- L250 _public member_ `SYMS_U64 index;`
- L251 _public member_ `SYMS_U64Range tags_info_range;`
- L252 _public member_ `SYMS_DwAbbrevTable abbrev_table;`
- L255 _public member_ `SYMS_U64 rnglist_base;` — NOTE(rjf): [parsed from DWARF attributes] Offsets For More Info (DWARF V5 ONLY)
- L256 _public member_ `SYMS_U64 loclist_base;` — NOTE(rjf): Offset into the .debug_loclists section where this comp unit's data is.
- L257 _public member_ `SYMS_U64 addrs_base;` — NOTE(rjf): Offset into the .debug_addr section where this comp unit's data is.
- L258 _public member_ `SYMS_U64 stroffs_base;` — NOTE(rjf): Offset into the .debug_str_offsets section where this comp unit's data is.
- L261 _public member_ `SYMS_String8 name;` — NOTE(rjf): [parsed from DWARF attributes] General Info
- L262 _public member_ `SYMS_String8 producer;`
- L263 _public member_ `SYMS_String8 compile_dir;`
- L264 _public member_ `SYMS_String8 external_dwo_name;`
- L265 _public member_ `SYMS_U64 dwo_id;`
- L266 _public member_ `SYMS_DwLanguage language;`
- L267 _public member_ `SYMS_U64 name_case;`
- L268 _public member_ `SYMS_B32 use_utf8;`
- L269 _public member_ `SYMS_U64 line_off;`
- L270 _public member_ `SYMS_U64 low_pc;`
- L271 _public member_ `SYMS_U64 high_pc;`
- L272 _public member_ `SYMS_DwAttribValue ranges_attrib_value;`
- L273 _public member_ `SYMS_U64 base_addr;`
- L276 _public member_ `SYMS_String8Array dir_table;` — NOTE(rjf): Line/File Info For This Comp Unit
- L277 _public member_ `SYMS_DwLineVMFileArray file_table;`

#### struct `SYMS_DwUnitSetAccelBucket`  
`struct SYMS_DwUnitSetAccelBucket`  
_L281-286_
- L283 _public member_ `SYMS_DwUnitSetAccelBucket *next;`
- L284 _public member_ `SYMS_U64 comp_root_idx;`
- L285 _public member_ `SYMS_DwCompRoot root;`

#### struct `SYMS_DwUnitSetAccel`  
`struct SYMS_DwUnitSetAccel`  
_L289-294_
- L291 _public member_ `SYMS_FileFormat format;`
- L292 _public member_ `SYMS_U64 root_count;`
- L293 _public member_ `SYMS_DwCompRoot *roots;`

#### struct `SYMS_DwTag`  
`struct SYMS_DwTag`  
_L300-314_
- L302 _public member_ `SYMS_DwTag *next_sibling;`
- L303 _public member_ `SYMS_DwTag *first_child;`
- L304 _public member_ `SYMS_DwTag *last_child;`
- L305 _public member_ `SYMS_DwTag *parent;`
- L306 _public member_ `SYMS_U64Range info_range;`
- L307 _public member_ `SYMS_U64Range abbrev_range;`
- L308 _public member_ `SYMS_B32 has_children;`
- L309 _public member_ `SYMS_U64 abbrev_id;`
- L310 _public member_ `SYMS_DwTagKind kind;`
- L311 _public member_ `SYMS_U64 attribs_info_off;`
- L312 _public member_ `SYMS_U64 attribs_abbrev_off;`
- L313 _public member_ `SYMS_DwAttribList attribs;`

#### enum `(anonymous)`  
``  
_L318-323_

#### struct `SYMS_DwTagStub`  
`struct SYMS_DwTagStub`  
_L326-353_
- L328 _public member_ `SYMS_SymbolID sid;`
- L329 _public member_ `SYMS_DwTagKind kind;`
- L330 _public member_ `SYMS_DwTagStubFlags flags;`
- L331 _public member_ `SYMS_U64 children_info_off;`
- L332 _public member_ `SYMS_U64 attribs_info_off;`
- L333 _public member_ `SYMS_U64 attribs_abbrev_off;`
- L342 _public member_ `SYMS_SymbolID ref;` — NOTE(rjf): SYMS_DwAttribKind_SPECIFICATION is tacked onto definitions that are filling out more info about a "prototype". That attribute is a reference that points back at the declaration tag. The declaration tag has the SYMS_DwAttribKind_DECLARATION attribute, which is sort of like the reverse of that, except there's no reference. So what we're doing here is just storing a reference on both, that point back to each other, so it's always easy to get from decl => spec, or from spec => decl.
- L350 _public member_ `SYMS_SymbolID abstract_origin;` — NOTE(rjf): SYMS_DwAttribKind_ABSTRACT_ORIGIN is tacked onto some definitions that are used to specify information more specific to inlining, while wanting to refer to an "abstract" function DIE, that is not specific to any inline sites. The DWARF generator will not duplicate information across these, so we will occasionally need to look at an abstract origin to get abstract information, like name/linkage-name/etc.
- L352 _public member_ `SYMS_U64 _unused_;`

#### struct `SYMS_DwTagStubNode`  
`struct SYMS_DwTagStubNode`  
_L356-360_
- L358 _public member_ `SYMS_DwTagStubNode *next;`
- L359 _public member_ `SYMS_DwTagStub stub;`

#### struct `SYMS_DwTagStubList`  
`struct SYMS_DwTagStubList`  
_L363-368_
- L365 _public member_ `SYMS_DwTagStubNode *first;`
- L366 _public member_ `SYMS_DwTagStubNode *last;`
- L367 _public member_ `SYMS_U64 count;`

#### struct `SYMS_DwLineVMHeader`  
`struct SYMS_DwLineVMHeader`  
_L374-393_
- L376 _public member_ `SYMS_U64 unit_length;`
- L377 _public member_ `SYMS_U64 unit_opl;`
- L378 _public member_ `SYMS_U16 version;`
- L379 _public member_ `SYMS_U8 address_size;` — NOTE(nick): duplicates size from the compilation unit but is needed to support stripped exe that just have .debug_line and .debug_line_str.
- L380 _public member_ `SYMS_U8 segment_selector_size;`
- L381 _public member_ `SYMS_U64 header_length;`
- L382 _public member_ `SYMS_U64 program_off;`
- L383 _public member_ `SYMS_U8 min_inst_len;`
- L384 _public member_ `SYMS_U8 max_ops_for_inst;`
- L385 _public member_ `SYMS_U8 default_is_stmt;`
- L386 _public member_ `SYMS_S8 line_base;`
- L387 _public member_ `SYMS_U8 line_range;`
- L388 _public member_ `SYMS_U8 opcode_base;`
- L389 _public member_ `SYMS_U64 num_opcode_lens;`
- L390 _public member_ `SYMS_U8 *opcode_lens;`
- L391 _public member_ `SYMS_String8Array dir_table;`
- L392 _public member_ `SYMS_DwLineVMFileArray file_table;`

#### struct `SYMS_DwLineVMState`  
`struct SYMS_DwLineVMState`  
_L396-426_
- L398 _public member_ `SYMS_U64 address;` — NOTE(nick): Address of a machine instruction.
- L399 _public member_ `SYMS_U32 op_index;` — NOTE(nick): This is used by the VLIW instructions to indicate index of operation inside the instruction.
- L404 _public member_ `SYMS_U32 file_index;` — NOTE(nick): Line table doesn't contain full path to a file, instead DWARF encodes path as two indices. First index will point into a directory table,  and second points into a file name table.
- L406 _public member_ `SYMS_U32 line;`
- L407 _public member_ `SYMS_U32 column;`
- L409 _public member_ `SYMS_B32 is_stmt;` — NOTE(nick): Indicates that "va" points to place suitable for a breakpoint.
- L410 _public member_ `SYMS_B32 basic_block;` — NOTE(nick): Indicates that the "va" is inside a basic block.
- L415 _public member_ `SYMS_B32 prologue_end;` — NOTE(nick): Indicates that "va" points to place where function starts. Usually prologue is the place where compiler emits instructions to prepare stack for a function.
- L417 _public member_ `SYMS_B32 epilogue_begin;` — NOTE(nick): Indicates that "va" points to section where function exits and unwinds stack.
- L418 _public member_ `SYMS_U64 isa;` — NOTE(nick): Instruction set that is used.
- L419 _public member_ `SYMS_U64 discriminator;` — NOTE(nick): Arbitrary id that indicates to which block these instructions belong.
- L420 _public member_ `SYMS_B32 end_sequence;` — NOTE(nick): Indicates that "va" points to the first instruction in the instruction block that follows.
- L425 _public member_ `SYMS_B32 busted_seq;` — NOTE(rjf): it looks like LTO might sometimes zero out high PC and low PCs, causing a swath of line info to map to a range starting at 0. This causes overlapping ranges which we do not want to report. So this B32 will turn on emission.

#### struct `SYMS_DwLineNode`  
`struct SYMS_DwLineNode`  
_L429-433_
- L431 _public member_ `SYMS_DwLineNode *next;`
- L432 _public member_ `SYMS_Line line;`

#### struct `SYMS_DwLineSeqNode`  
`struct SYMS_DwLineSeqNode`  
_L436-442_
- L438 _public member_ `SYMS_DwLineSeqNode *next;`
- L439 _public member_ `SYMS_U64 count;`
- L440 _public member_ `SYMS_DwLineNode *first;`
- L441 _public member_ `SYMS_DwLineNode *last;`

#### struct `SYMS_DwLineTableParseResult`  
`struct SYMS_DwLineTableParseResult`  
_L445-450_
- L447 _public member_ `SYMS_U64 seq_count;`
- L448 _public member_ `SYMS_DwLineSeqNode *first_seq;`
- L449 _public member_ `SYMS_DwLineSeqNode *last_seq;`

#### struct `SYMS_DwPubStringsBucket`  
`struct SYMS_DwPubStringsBucket`  
_L456-462_
- L458 _public member_ `SYMS_DwPubStringsBucket *next;`
- L459 _public member_ `SYMS_String8 string;`
- L460 _public member_ `SYMS_SymbolID sid;`
- L461 _public member_ `SYMS_UnitID uid;`

#### struct `SYMS_DwPubStringsTable`  
`struct SYMS_DwPubStringsTable`  
_L465-469_
- L467 _public member_ `SYMS_U64 size;`
- L468 _public member_ `SYMS_DwPubStringsBucket **buckets;`

#### struct `SYMS_DwTagRefNode`  
`struct SYMS_DwTagRefNode`  
_L475-480_
- L477 _public member_ `SYMS_DwTagRefNode *hash_next;`
- L478 _public member_ `SYMS_SymbolID dst;`
- L479 _public member_ `SYMS_SymbolID src;`

#### struct `SYMS_DwTagRefTable`  
`struct SYMS_DwTagRefTable`  
_L483-487_
- L485 _public member_ `SYMS_U64 size;`
- L486 _public member_ `SYMS_DwTagRefNode **v;`

#### struct `SYMS_DwTagStubCacheNode`  
`struct SYMS_DwTagStubCacheNode`  
_L493-501_
- L495 _public member_ `SYMS_DwTagStubCacheNode *hash_next;`
- L496 _public member_ `SYMS_DwTagStubCacheNode *next;`
- L497 _public member_ `SYMS_DwTagStubCacheNode *first;`
- L498 _public member_ `SYMS_DwTagStubCacheNode *last;`
- L499 _public member_ `SYMS_U64 children_count;`
- L500 _public member_ `SYMS_DwTagStub stub;`

#### struct `SYMS_DwUnitAccel`  
`struct SYMS_DwUnitAccel`  
_L504-536_
- L506 _public member_ `SYMS_FileFormat format;`
- L509 _public member_ `SYMS_UnitID uid;` — - rjf: header information (from comp root)
- L510 _public member_ `SYMS_DwVersion version;`
- L511 _public member_ `SYMS_U64 address_size;`
- L512 _public member_ `SYMS_U64 base_addr;`
- L513 _public member_ `SYMS_U64 addrs_base;`
- L514 _public member_ `SYMS_DwLanguage language;`
- L515 _public member_ `SYMS_DwAbbrevTable abbrev_table;`
- L518 _public member_ `SYMS_U64 stub_table_size;` — - rjf: tag stub hash table
- L519 _public member_ `SYMS_DwTagStubCacheNode **stub_table;`
- L522 _public member_ `SYMS_DwTagRefTable ref_table;` — - rjf: tag reference tables
- L523 _public member_ `SYMS_DwTagRefTable parent_table;`
- L526 _public member_ `SYMS_DwTagStubCacheNode *stub_root;` — - rjf: tag stub tree
- L529 _public member_ `SYMS_SymbolIDArray all_top_ids;` — - rjf: top-level symbol IDs
- L530 _public member_ `SYMS_SymbolIDArray proc_ids;`
- L531 _public member_ `SYMS_SymbolIDArray var_ids;`
- L532 _public member_ `SYMS_SymbolIDArray type_ids;`
- L535 _public member_ `SYMS_DwAttribValueResolveParams resolve_params;` — TODO(rjf): hack hack hack, merge with above info

#### struct `SYMS_DwMemsAccel`  
`struct SYMS_DwMemsAccel`  
_L542-550_
- L544 _public member_ `SYMS_FileFormat format;`
- L545 _public member_ `SYMS_U64 count;`
- L546 _public member_ `SYMS_MemInfo *mem_infos;`
- L547 _public member_ `SYMS_USID *type_symbols;`
- L548 _public member_ `SYMS_USID *full_symbols;`
- L549 _public member_ `SYMS_SymbolID *sig_symbols;`

#### struct `SYMS_DwMapAccel`  
`struct SYMS_DwMapAccel`  
_L556-560_
- L558 _public member_ `SYMS_FileFormat format;`
- L559 _public member_ `SYMS_DwPubStringsTable tbl;`

#### struct `SYMS_DwLinkMapAccel`  
`struct SYMS_DwLinkMapAccel`  
_L563-567_
- L565 _public member_ `SYMS_FileFormat format;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DWARF_PARSER_H`
- L17 _macro_ `#define SYMS_DWARF_VOID_TYPE_ID 0xffffffffffffffffull`
- L22 _typedef_ `typedef struct SYMS_DwUnitRangePoint SYMS_DwUnitRangePoint;`
- L30 _typedef_ `typedef struct SYMS_DwSymbolIDChunk SYMS_DwSymbolIDChunk;`
- L38 _typedef_ `typedef struct SYMS_DwSymbolIDChunkList SYMS_DwSymbolIDChunkList;`
- L50 _typedef_ `typedef struct SYMS_DwExtDebugRef SYMS_DwExtDebugRef;`
- L61 _typedef_ `typedef struct SYMS_DwAbbrevTableEntry SYMS_DwAbbrevTableEntry;`
- L68 _typedef_ `typedef struct SYMS_DwAbbrevTable SYMS_DwAbbrevTable;`
- L78 _typedef_ `typedef struct SYMS_DwSection SYMS_DwSection;`
- L84 _typedef_ `typedef struct SYMS_DwUnitRangeInfo SYMS_DwUnitRangeInfo;`
- L92 _typedef_ `typedef struct SYMS_DwDbgAccel SYMS_DwDbgAccel;`
- L110 _typedef_ `typedef struct SYMS_DwLineFile SYMS_DwLineFile;`
- L120 _typedef_ `typedef struct SYMS_DwLineVMFileNode SYMS_DwLineVMFileNode;`
- L127 _typedef_ `typedef struct SYMS_DwLineVMFileList SYMS_DwLineVMFileList;`
- L135 _typedef_ `typedef struct SYMS_DwLineVMFileArray SYMS_DwLineVMFileArray;`
- L154 _typedef_ `SYMS_DwAbbrevKind;`
- L156 _typedef_ `typedef SYMS_U32 SYMS_DwAbbrevFlags;`
- L158 _enumerator_ `SYMS_DwAbbrevFlag_HasImplicitConst = (1<<0)` (scope `__anon2e17f4120103`)
- L159 _enumerator_ `SYMS_DwAbbrevFlag_HasChildren = (1<<1)` (scope `__anon2e17f4120103`)
- L162 _typedef_ `typedef struct SYMS_DwAbbrev SYMS_DwAbbrev;`
- L176 _typedef_ `typedef struct SYMS_DwAttribValueResolveParams SYMS_DwAttribValueResolveParams;`
- L189 _typedef_ `typedef struct SYMS_DwAttribValue SYMS_DwAttribValue;`
- L196 _typedef_ `typedef struct SYMS_DwAttrib SYMS_DwAttrib;`
- L207 _typedef_ `typedef struct SYMS_DwAttribArray SYMS_DwAttribArray;`
- L214 _typedef_ `typedef struct SYMS_DwAttribNode SYMS_DwAttribNode;`
- L221 _typedef_ `typedef struct SYMS_DwAttribList SYMS_DwAttribList;`
- L229 _typedef_ `typedef struct SYMS_DwAttribListParseResult SYMS_DwAttribListParseResult;`
- L240 _typedef_ `typedef struct SYMS_DwCompRoot SYMS_DwCompRoot;`
- L280 _typedef_ `typedef struct SYMS_DwUnitSetAccelBucket SYMS_DwUnitSetAccelBucket;`
- L288 _typedef_ `typedef struct SYMS_DwUnitSetAccel SYMS_DwUnitSetAccel;`
- L299 _typedef_ `typedef struct SYMS_DwTag SYMS_DwTag;`
- L316 _typedef_ `typedef SYMS_U32 SYMS_DwTagStubFlags;`
- L319 _enumerator_ `SYMS_DwTagStubFlag_HasObjectPointerArg = (1<<0)` (scope `__anon2e17f4120203`)
- L320 _enumerator_ `SYMS_DwTagStubFlag_HasLocation = (1<<1)` (scope `__anon2e17f4120203`)
- L321 _enumerator_ `SYMS_DwTagStubFlag_HasExternal = (1<<2)` (scope `__anon2e17f4120203`)
- L322 _enumerator_ `SYMS_DwTagStubFlag_HasSpecification = (1<<3)` (scope `__anon2e17f4120203`)
- L325 _typedef_ `typedef struct SYMS_DwTagStub SYMS_DwTagStub;`
- L355 _typedef_ `typedef struct SYMS_DwTagStubNode SYMS_DwTagStubNode;`
- L362 _typedef_ `typedef struct SYMS_DwTagStubList SYMS_DwTagStubList;`
- L373 _typedef_ `typedef struct SYMS_DwLineVMHeader SYMS_DwLineVMHeader;`
- L395 _typedef_ `typedef struct SYMS_DwLineVMState SYMS_DwLineVMState;`
- L428 _typedef_ `typedef struct SYMS_DwLineNode SYMS_DwLineNode;`
- L435 _typedef_ `typedef struct SYMS_DwLineSeqNode SYMS_DwLineSeqNode;`
- L444 _typedef_ `typedef struct SYMS_DwLineTableParseResult SYMS_DwLineTableParseResult;`
- L455 _typedef_ `typedef struct SYMS_DwPubStringsBucket SYMS_DwPubStringsBucket;`
- L464 _typedef_ `typedef struct SYMS_DwPubStringsTable SYMS_DwPubStringsTable;`
- L474 _typedef_ `typedef struct SYMS_DwTagRefNode SYMS_DwTagRefNode;`
- L482 _typedef_ `typedef struct SYMS_DwTagRefTable SYMS_DwTagRefTable;`
- L492 _typedef_ `typedef struct SYMS_DwTagStubCacheNode SYMS_DwTagStubCacheNode;`
- L503 _typedef_ `typedef struct SYMS_DwUnitAccel SYMS_DwUnitAccel;`
- L541 _typedef_ `typedef struct SYMS_DwMemsAccel SYMS_DwMemsAccel;`
- L555 _typedef_ `typedef struct SYMS_DwMapAccel SYMS_DwMapAccel;`
- L562 _typedef_ `typedef struct SYMS_DwLinkMapAccel SYMS_DwLinkMapAccel;`
- L574 _prototype_ `SYMS_U64 syms_dw_hash_from_string(SYMS_String8 string);`
- L575 _prototype_ `SYMS_U64 syms_dw_hash_from_sid(SYMS_SymbolID sid);`
- L577 _prototype_ `SYMS_SymbolID syms_dw_sid_from_info_offset(SYMS_U64 info_offset);`
- L578 _prototype_ `SYMS_DwAttribClass syms_dw_pick_attrib_value_class(SYMS_DwLanguage lang, SYMS_DwVersion ver, SYMS_DwAttribKind attrib, SYMS_DwFormKind form_kind);`
- L579 _prototype_ `SYMS_SymbolKind syms_dw_symbol_kind_from_tag_stub(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwAttribValueResolveParams resolve_params, SYMS_DwTagStub *stub);`
- L581 _prototype_ `SYMS_SecInfoArray syms_dw_copy_sec_info_array(SYMS_Arena *arena, SYMS_SecInfoArray array);`
- L583 _prototype_ `SYMS_String8 syms_dw_path_from_dir_and_filename(SYMS_Arena *arena, SYMS_String8 dir, SYMS_String8 filename);`
- L584 _prototype_ `void syms_dw_symbol_id_chunk_list_push(SYMS_Arena *arena, SYMS_DwSymbolIDChunkList *list, SYMS_SymbolID sid);`
- L585 _prototype_ `SYMS_SymbolIDArray syms_dw_sid_array_from_chunk_list(SYMS_Arena *arena, SYMS_DwSymbolIDChunkList list);`
- L590 _prototype_ `SYMS_U64 syms_dw_based_range_read_length(void *base, SYMS_U64Range range, SYMS_U64 offset, SYMS_U64 *out_value);`
- L591 _prototype_ `SYMS_U64 syms_dw_based_range_read_abbrev_tag(void *base, SYMS_U64Range range, SYMS_U64 offset, SYMS_DwAbbrev *out_abbrev);`
- L592 _prototype_ `SYMS_U64 syms_dw_based_range_read_abbrev_attrib_info(void *base, SYMS_U64Range range, SYMS_U64 offset, SYMS_DwAbbrev *out_abbrev);`
- L593 _prototype_ `SYMS_U64 syms_dw_based_range_read_attrib_form_value(void *base, SYMS_U64Range range, SYMS_U64 offset, SYMS_DwMode mode, SYMS_U64 address_size, SYMS_DwFormKind form_kind, SYMS_U64 implicit_const, SYMS_DwAttribValue *form_value_out);`
- L599 _prototype_ `SYMS_B32 syms_dw_elf_bin_accel_is_dbg(SYMS_ElfBinAccel *bin_accel);` — - rjf: debug info and interaction with bin accels
- L600 _prototype_ `SYMS_B32 syms_dw_mach_bin_accel_is_dbg(SYMS_MachBinAccel *bin_accel);`
- L601 _prototype_ `SYMS_DwDbgAccel *syms_dw_dbg_accel_from_sec_info_array(SYMS_Arena *arena, SYMS_String8 data, SYMS_U64 vbase, SYMS_Arch arch, SYMS_SecInfoArray sections);`
- L602 _prototype_ `SYMS_DwDbgAccel *syms_dw_dbg_accel_from_elf_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_ElfBinAccel *bin);`
- L603 _prototype_ `SYMS_DwDbgAccel *syms_dw_dbg_accel_from_mach_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_MachBinAccel *bin);`
- L604 _prototype_ `SYMS_ExtFileList syms_dw_ext_file_list_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg);`
- L606 _prototype_ `SYMS_SecInfoArray syms_dw_sec_info_array_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg);`
- L607 _prototype_ `SYMS_ExtMatchKey syms_dw_ext_match_key_from_dbg(SYMS_String8 data, SYMS_DwDbgAccel *dbg);`
- L608 _prototype_ `SYMS_U64 syms_dw_default_vbase_from_dbg(SYMS_DwDbgAccel *dbg);`
- L611 _prototype_ `SYMS_UnitID syms_dw_uid_from_foff(SYMS_DwDbgAccel *dbg, SYMS_U64 foff);` — - rjf: top-level unit info
- L614 _prototype_ `SYMS_DwMode syms_dw_mode_from_sec(SYMS_DwSection *section_map, SYMS_DwSectionKind kind);` — - rjf: important DWARF section base/range accessors
- L616 _prototype_ `SYMS_B32 syms_dw_sec_is_present(SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind kind);`
- L617 _prototype_ `void* syms_dw_sec_base_from_dbg(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind kind);`
- L619 _prototype_ `SYMS_U64Range syms_dw_sec_range_from_dbg(SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind kind);`
- L624 _prototype_ `SYMS_DwAbbrevTable syms_dw_make_abbrev_table(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_U64 start_abbrev_off);`
- L626 _prototype_ `SYMS_U64 syms_dw_abbrev_offset_from_abbrev_id(SYMS_DwAbbrevTable table, SYMS_U64 abbrev_id);`
- L632 _prototype_ `SYMS_U64RangeList syms_dw_v4_range_list_from_range_offset(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_U64 addr_size, SYMS_U64 comp_unit_base_addr, SYMS_U64 range_off);` — - rjf: .debug_ranges (DWARF V4)
- L635 _prototype_ `SYMS_LocRangeList syms_dw_v4_location_ranges_from_loc_offset(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_U64 addr_size, SYMS_U64 comp_unit_base_addr, SYMS_U64 offset);` — - rjf: .debug_loc (DWARF V4)
- L636 _prototype_ `SYMS_Location syms_dw_v4_location_from_loc_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_LocID loc);`
- L639 _prototype_ `SYMS_DwPubStringsTable syms_dw_v4_pub_strings_table_from_section_kind(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section_kind);` — - rjf: .debug_pubtypes + .debug_pubnames (DWARF V4)
- L642 _prototype_ `SYMS_USIDList syms_dw_v4_usid_list_from_pub_table_string(SYMS_Arena *arena, SYMS_DwPubStringsTable tbl, SYMS_String8 string);`
- L647 _prototype_ `SYMS_U64 syms_dw_v5_offset_from_offs_section_base_index(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section, SYMS_U64 base, SYMS_U64 index);` — - rjf: .debug_str_offsets (DWARF V5)
- L650 _prototype_ `SYMS_U64 syms_dw_v5_addr_from_addrs_section_base_index(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section, SYMS_U64 base, SYMS_U64 index);` — - rjf: .debug_addr (DWARF V5)
- L653 _prototype_ `SYMS_U64 syms_dw_v5_sec_offset_from_rnglist_or_loclist_section_base_index(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section_kind, SYMS_U64 base, SYMS_U64 index);` — - rjf: .debug_rnglists parsing (DWARF V5)
- L654 _prototype_ `SYMS_U64RangeList syms_dw_v5_range_list_from_rnglist_offset(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section, SYMS_U64 addr_size, SYMS_U64 addr_section_base, SYMS_U64 offset);`
- L657 _prototype_ `SYMS_LocRangeList syms_dw_v5_location_ranges_from_loclist_offset(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section, SYMS_U64 addr_size, SYMS_U64 addr_section_base, SYMS_U64 offset);` — - rjf: .debug_loclists parsing (DWARF V5)
- L658 _prototype_ `SYMS_Location syms_dw_v5_location_from_loclist_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section, SYMS_LocID id);`
- L663 _prototype_ `SYMS_DwAttribValueResolveParams syms_dw_attrib_value_resolve_params_from_comp_root(SYMS_DwCompRoot *root);`
- L664 _prototype_ `SYMS_DwAttribValue syms_dw_attrib_value_from_form_value(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwAttribValueResolveParams resolve_params, SYMS_DwFormKind form_kind, SYMS_DwAttribClass value_class, SYMS_DwAttribValue form_value);`
- L669 _prototype_ `SYMS_String8 syms_dw_string_from_attrib_value(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwAttribValue value);`
- L671 _prototype_ `SYMS_U64RangeList syms_dw_range_list_from_high_low_pc_and_ranges_attrib_value(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_U64 address_size, SYMS_U64 comp_unit_base_addr, SYMS_U64 addr_section_base, SYMS_U64 low_pc, SYMS_U64 high_pc, SYMS_DwAttribValue ranges_value);`
- L676 _prototype_ `SYMS_DwAttribListParseResult syms_dw_parse_attrib_list_from_info_abbrev_offsets(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwLanguage lang, SYMS_DwVersion ver, SYMS_U64 address_size, SYMS_U64 info_off, SYMS_U64 abbrev_off);`
- L677 _prototype_ `SYMS_DwTag *syms_dw_tag_from_info_offset(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwAbbrevTable abbrev_table, SYMS_DwLanguage lang, SYMS_DwVersion ver, SYMS_U64 address_size, SYMS_U64 info_offset);`
- L684 _prototype_ `SYMS_DwTagStub syms_dw_stub_from_tag(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwAttribValueResolveParams resolve_params, SYMS_DwTag *tag);`
- L690 _prototype_ `SYMS_U64 syms_dw_v5_header_offset_from_table_offset(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwSectionKind section, SYMS_U64 table_off);`
- L693 _prototype_ `SYMS_DwCompRoot syms_dw_comp_root_from_range(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_U64 index, SYMS_U64Range range);`
- L696 _prototype_ `SYMS_DwExtDebugRef syms_dw_ext_debug_ref_from_comp_root(SYMS_DwCompRoot *root);`
- L697 _prototype_ `SYMS_DwUnitSetAccel*syms_dw_unit_set_accel_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg);`
- L699 _prototype_ `SYMS_U64 syms_dw_unit_count_from_set(SYMS_DwUnitSetAccel *unit_set);`
- L700 _prototype_ `SYMS_DwCompRoot* syms_dw_comp_root_from_uid(SYMS_DwUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L701 _prototype_ `SYMS_UnitID syms_dw_uid_from_number(SYMS_DwUnitSetAccel *unit_set, SYMS_U64 n);`
- L702 _prototype_ `SYMS_U64 syms_dw_unit_number_from_uid(SYMS_DwUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L703 _prototype_ `SYMS_UnitInfo syms_dw_unit_info_from_uid(SYMS_DwUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L704 _prototype_ `SYMS_UnitNames syms_dw_unit_names_from_uid(SYMS_Arena *arena, SYMS_DwUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L706 _prototype_ `void syms_dw_sort_unit_range_point_array_in_place__merge(SYMS_DwUnitRangePoint *a, SYMS_U64 left, SYMS_U64 right, SYMS_U64 end, SYMS_DwUnitRangePoint *b);`
- L707 _prototype_ `void syms_dw_sort_unit_range_point_array_in_place(SYMS_DwUnitRangePoint *a, SYMS_U64 count);`
- L708 _prototype_ `SYMS_UnitRangeArray syms_dw_unit_ranges_from_set(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitSetAccel *unit_set);`
- L711 _prototype_ `SYMS_String8Array syms_dw_file_table_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L718 _prototype_ `SYMS_DwTagRefTable syms_dw_tag_ref_table_make(SYMS_Arena *arena, SYMS_U64 size);`
- L719 _prototype_ `void syms_dw_tag_ref_table_insert(SYMS_Arena *arena, SYMS_DwTagRefTable *table, SYMS_SymbolID src, SYMS_SymbolID dst);`
- L720 _prototype_ `SYMS_SymbolID syms_dw_tag_ref_table_lookup_src(SYMS_DwTagRefTable table, SYMS_SymbolID dst);`
- L725 _prototype_ `SYMS_U64 syms_dw_primify_table_size(SYMS_U64 v);`
- L726 _prototype_ `SYMS_U64 syms_dw_predict_good_stub_table_size_from_range_size(SYMS_U64 size);`
- L727 _prototype_ `SYMS_DwUnitAccel* syms_dw_unit_accel_from_comp_root(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwCompRoot *comp_root);`
- L730 _prototype_ `SYMS_DwUnitAccel* syms_dw_unit_accel_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L734 _prototype_ `SYMS_UnitID syms_dw_uid_from_accel(SYMS_DwUnitAccel *unit);`
- L735 _prototype_ `SYMS_DwTagStubCacheNode * syms_dw_tag_stub_cache_node_from_sid(SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L736 _prototype_ `SYMS_DwTagStub syms_dw_tag_stub_from_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L737 _prototype_ `SYMS_DwTagStub syms_dw_cached_tag_stub_from_sid__parse_fallback(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L738 _prototype_ `SYMS_DwTagStubList syms_dw_children_from_tag_stub(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_DwTagStub stub);`
- L739 _prototype_ `SYMS_DwAttribList syms_dw_attrib_list_from_stub(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwLanguage lang, SYMS_DwVersion ver, SYMS_U64 addr_size, SYMS_DwTagStub *stub);`
- L740 _prototype_ `SYMS_SymbolIDArray syms_dw_copy_sid_array_if_needed(SYMS_Arena *arena, SYMS_SymbolIDArray arr);`
- L741 _prototype_ `SYMS_SymbolIDArray syms_dw_proc_sid_array_from_unit(SYMS_Arena *arena, SYMS_DwUnitAccel *unit);`
- L742 _prototype_ `SYMS_SymbolIDArray syms_dw_var_sid_array_from_unit(SYMS_Arena *arena, SYMS_DwUnitAccel *unit);`
- L743 _prototype_ `SYMS_SymbolIDArray syms_dw_type_sid_array_from_unit(SYMS_Arena *arena, SYMS_DwUnitAccel *unit);`
- L748 _prototype_ `SYMS_DwMemsAccel* syms_dw_mems_accel_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L751 _prototype_ `SYMS_U64 syms_dw_mem_count_from_mems(SYMS_DwMemsAccel *mems);`
- L752 _prototype_ `SYMS_MemInfo syms_dw_mem_info_from_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_DwMemsAccel *mems, SYMS_U64 n);`
- L755 _prototype_ `SYMS_USID syms_dw_type_from_mem_number(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_DwMemsAccel *mems, SYMS_U64 n);`
- L758 _prototype_ `SYMS_SigInfo syms_dw_sig_info_from_mem_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_DwMemsAccel *mems, SYMS_U64 n);`
- L761 _prototype_ `SYMS_USID syms_dw_symbol_from_mem_number(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_DwMemsAccel *mems, SYMS_U64 n);`
- L764 _prototype_ `SYMS_EnumMemberArray syms_dw_enum_member_array_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L766 _prototype_ `SYMS_USID syms_dw_containing_type_from_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L767 _prototype_ `SYMS_String8 syms_dw_linkage_name_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L772 _prototype_ `SYMS_String8 syms_dw_attrib_string_from_sid__unstable(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_DwAttribKind kind, SYMS_SymbolID sid);`
- L775 _prototype_ `SYMS_String8 syms_dw_attrib_string_from_sid__unstable_chain(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_DwAttribKind kind, SYMS_SymbolID sid);`
- L778 _prototype_ `SYMS_SymbolKind syms_dw_symbol_kind_from_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L780 _prototype_ `SYMS_String8 syms_dw_symbol_name_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L782 _prototype_ `SYMS_TypeInfo syms_dw_type_info_from_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L784 _prototype_ `SYMS_ConstInfo syms_dw_const_info_from_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L786 _prototype_ `SYMS_USID syms_dw_type_from_var_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L788 _prototype_ `SYMS_U64 syms_dw_voff_from_var_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L790 _prototype_ `SYMS_SymbolIDList syms_dw_children_from_sid_with_kinds(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid, SYMS_DwTagKind *kinds, SYMS_U64 count);`
- L793 _prototype_ `SYMS_Location syms_dw_location_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid, SYMS_DwAttribKind loc_attrib);` — - rjf: location information
- L794 _prototype_ `SYMS_LocRangeArray syms_dw_location_ranges_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid, SYMS_DwAttribKind loc_attrib);`
- L796 _prototype_ `SYMS_Location syms_dw_location_from_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_LocID loc_id);`
- L800 _prototype_ `SYMS_DwAttribKind syms_dw_attrib_kind_from_proc_loc(SYMS_ProcLoc proc_loc);` — - rjf: location information helpers
- L801 _prototype_ `SYMS_Location syms_dw_location_from_var_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L802 _prototype_ `SYMS_LocRangeArray syms_dw_location_ranges_from_var_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L804 _prototype_ `SYMS_Location syms_dw_location_from_proc_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid, SYMS_ProcLoc proc_loc);`
- L805 _prototype_ `SYMS_LocRangeArray syms_dw_location_ranges_from_proc_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid, SYMS_ProcLoc proc_loc);`
- L809 _prototype_ `SYMS_U64 syms_dw_file_index_from_id(SYMS_FileID file_id);` — - rjf: files
- L810 _prototype_ `SYMS_FileID syms_dw_file_id_from_index(SYMS_U64 idx);`
- L811 _prototype_ `SYMS_String8 syms_dw_file_name_from_id(SYMS_Arena *arena, SYMS_DwUnitSetAccel *unit_set, SYMS_UnitID uid, SYMS_FileID file_id);`
- L815 _prototype_ `SYMS_U64RangeArray syms_dw_scope_vranges_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);` — - rjf: procedures
- L818 _prototype_ `SYMS_SigInfo syms_dw_sig_info_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L820 _prototype_ `SYMS_UnitIDAndSig syms_dw_proc_sig_handle_from_sid(SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID sid);`
- L822 _prototype_ `SYMS_SigInfo syms_dw_sig_info_from_handle(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SigHandle handle);`
- L823 _prototype_ `SYMS_SymbolIDArray syms_dw_scope_children_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitAccel *unit, SYMS_SymbolID id);`
- L826 _prototype_ `void syms_dw_line_vm_reset(SYMS_DwLineVMState *state, SYMS_B32 default_is_stmt);` — - rjf: line info
- L827 _prototype_ `void syms_dw_line_vm_advance(SYMS_DwLineVMState *state, SYMS_U64 advance, SYMS_U64 min_inst_len, SYMS_U64 max_ops_for_inst);`
- L830 _prototype_ `SYMS_DwLineSeqNode *syms_dw_push_line_seq(SYMS_Arena* arena, SYMS_DwLineTableParseResult *parsed_tbl);`
- L831 _prototype_ `SYMS_DwLineNode *syms_dw_push_line(SYMS_Arena *arena, SYMS_DwLineTableParseResult *tbl, SYMS_DwLineVMState *vm_state, SYMS_B32 start_of_sequence);`
- L832 _prototype_ `SYMS_DwLineTableParseResult syms_dw_parsed_line_table_from_comp_root(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwCompRoot *root);`
- L834 _prototype_ `SYMS_LineParseOut syms_dw_line_parse_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg, SYMS_DwUnitSetAccel *set, SYMS_UnitID uid);`
- L836 _prototype_ `SYMS_U64 syms_dw_read_line_file(void *line_base, SYMS_U64Range line_rng, SYMS_U64 line_off, SYMS_DwMode mode, SYMS_DwDbgAccel *dbg, SYMS_String8 data, SYMS_DwCompRoot *unit, SYMS_U8 address_size, SYMS_U64 format_count, SYMS_U64Range *formats, SYMS_DwLineFile *line_file_out);`
- L841 _prototype_ `SYMS_U64 syms_dw_read_line_vm_header(SYMS_Arena *arena, void *line_base, SYMS_U64Range line_rng, SYMS_U64 line_off, SYMS_String8 data, SYMS_DwMode mode, SYMS_DwDbgAccel *dbg, SYMS_DwCompRoot *unit, SYMS_DwLineVMHeader *header_out);`
- L846 _prototype_ `SYMS_DwMapAccel* syms_dw_type_map_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg);` — - rjf: name maps
- L847 _prototype_ `SYMS_DwMapAccel* syms_dw_image_symbol_map_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DwDbgAccel *dbg);`
- L848 _prototype_ `SYMS_USIDList syms_dw_usid_list_from_string(SYMS_Arena *arena, SYMS_DwMapAccel *map, SYMS_String8 string);`

### `Source/Runtime/SymsLib/syms/core/dwarf/syms_dwarf_transpiler.h` (Other)


#### struct `SYMS_DwEvalIRGraphNode`  
`typedef struct SYMS_DwEvalIRGraphNode`  
_L15-24_
- L17 _public member_ `struct SYMS_DwEvalIRGraphNode *next;` — contents
- L18 _public member_ `struct SYMS_DwEvalIRGraphNode *cnext;`
- L19 _public member_ `SYMS_U32 op;`
- L20 _public member_ `SYMS_EvalOpParams params;`
- L23 _public member_ `SYMS_B8 in_stack;` — analysis

#### struct `SYMS_DwEvalIRGraph`  
`typedef struct SYMS_DwEvalIRGraph`  
_L26-32_
- L27 _public member_ `SYMS_DwEvalIRGraphNode *first;`
- L28 _public member_ `SYMS_DwEvalIRGraphNode *last;`
- L30 _public member_ `SYMS_DwEvalIRGraphNode **tbl;`
- L31 _public member_ `SYMS_U64 count;`

#### struct `SYMS_DwEvalJumpPatch`  
`typedef struct SYMS_DwEvalJumpPatch`  
_L34-38_
- L35 _public member_ `struct SYMS_DwEvalJumpPatch *next;`
- L36 _public member_ `SYMS_DwEvalIRGraphNode *node;`
- L37 _public member_ `SYMS_U64 cnext_dw_off;`

#### struct `SYMS_DwEvalIRGraphStackNode`  
`typedef struct SYMS_DwEvalIRGraphStackNode`  
_L40-44_
- L41 _public member_ `struct SYMS_DwEvalIRGraphStackNode *next;`
- L42 _public member_ `SYMS_DwEvalIRGraphNode *node;`
- L43 _public member_ `SYMS_U64 stage;`

#### struct `SYMS_DwEvalIRGraphStack`  
`typedef struct SYMS_DwEvalIRGraphStack`  
_L46-49_
- L47 _public member_ `SYMS_DwEvalIRGraphStackNode *stack;`
- L48 _public member_ `SYMS_DwEvalIRGraphStackNode *free;`

#### struct `SYMS_DwEvalIRGraphBlock`  
`typedef struct SYMS_DwEvalIRGraphBlock`  
_L51-61_
- L53 _public member_ `struct SYMS_DwEvalIRGraphBlock *next;` — content
- L54 _public member_ `struct SYMS_DwEvalIRGraphBlock *cnext;`
- L56 _public member_ `SYMS_DwEvalIRGraphNode *first;`
- L57 _public member_ `SYMS_DwEvalIRGraphNode *last;`
- L60 _public member_ `struct SYMS_DwEvalIRGraphBlock *order;` — analysis

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DWARF_TRANSPILER_H`
- L24 _typedef_ `} SYMS_DwEvalIRGraphNode;`
- L32 _typedef_ `} SYMS_DwEvalIRGraph;`
- L38 _typedef_ `} SYMS_DwEvalJumpPatch;`
- L44 _typedef_ `} SYMS_DwEvalIRGraphStackNode;`
- L49 _typedef_ `} SYMS_DwEvalIRGraphStack;`
- L61 _typedef_ `} SYMS_DwEvalIRGraphBlock;`
- L66 _prototype_ `SYMS_RegID syms_reg_id_from_dw_reg(SYMS_Arch arch, SYMS_U64 reg_idx);`
- L67 _prototype_ `SYMS_U64 syms_reg_off_from_dw_reg(SYMS_Arch arch, SYMS_U64 reg_idx);`
- L69 _prototype_ `SYMS_DwEvalIRGraphNode* syms_dw_expr__ir_push_node(SYMS_Arena *arena, SYMS_DwEvalIRGraph *graph, SYMS_EvalOp op, SYMS_EvalOpParams params);`
- L72 _prototype_ `SYMS_DwEvalIRGraphNode* syms_dw_expr__ir_encode_u(SYMS_Arena *arena, SYMS_DwEvalIRGraph *graph, SYMS_U64 u);`
- L74 _prototype_ `SYMS_DwEvalIRGraphNode* syms_dw_expr__ir_encode_s(SYMS_Arena *arena, SYMS_DwEvalIRGraph *graph, SYMS_S64 s);`
- L77 _prototype_ `SYMS_DwEvalIRGraph syms_dw_expr__ir_graph_from_dw_expr(SYMS_Arena *arena, SYMS_DwDbgAccel *dbg, void *base, SYMS_U64Range range);`
- L80 _prototype_ `void syms_dw_expr__ir_graph_stack_push(SYMS_Arena *arena, SYMS_DwEvalIRGraphStack *stack, SYMS_DwEvalIRGraphNode *node);`
- L82 _prototype_ `void syms_dw_expr__ir_graph_stack_pop(SYMS_DwEvalIRGraphStack *stack);`
- L83 _prototype_ `SYMS_B32 syms_dw_expr__ir_contains_cycle(SYMS_DwEvalIRGraphNode *node);`
- L85 _prototype_ `SYMS_DwEvalIRGraphBlock* syms_dw_expr__ir_blocks_from_graph(SYMS_Arena *arena, SYMS_DwEvalIRGraph graph);`
- L88 _prototype_ `SYMS_String8 syms_dw_expr__transpile_to_eval(SYMS_Arena *arena, SYMS_DwDbgAccel *dbg, void *base, SYMS_U64Range range);`

### `Source/Runtime/SymsLib/syms/core/elf/syms_elf.h` (Other)


#### enum `SYMS_ElfIdentifier`  
`typedef enum SYMS_ElfIdentifier`  
_L15-26_
- L16 _public enumerator_ `SYMS_ElfIdentifier_MAG0 = 0`
- L17 _public enumerator_ `SYMS_ElfIdentifier_MAG1 = 1`
- L18 _public enumerator_ `SYMS_ElfIdentifier_MAG2 = 2`
- L19 _public enumerator_ `SYMS_ElfIdentifier_MAG3 = 3`
- L20 _public enumerator_ `SYMS_ElfIdentifier_CLASS = 4`
- L21 _public enumerator_ `SYMS_ElfIdentifier_DATA = 5`
- L22 _public enumerator_ `SYMS_ElfIdentifier_VERSION = 6`
- L23 _public enumerator_ `SYMS_ElfIdentifier_OSABI = 7`
- L24 _public enumerator_ `SYMS_ElfIdentfiier_ABIVERSION = 8`
- L25 _public enumerator_ `SYMS_ElfIdentifier_NIDENT = 16`

#### struct `SYMS_ElfEhdr64`  
`struct SYMS_ElfEhdr64`  
_L29-45_
- L31 _public member_ `SYMS_U8 e_ident[SYMS_ElfIdentifier_NIDENT];`
- L32 _public member_ `SYMS_U16 e_type;`
- L33 _public member_ `SYMS_U16 e_machine;`
- L34 _public member_ `SYMS_U32 e_version;`
- L35 _public member_ `SYMS_U64 e_entry;`
- L36 _public member_ `SYMS_U64 e_phoff;`
- L37 _public member_ `SYMS_U64 e_shoff;`
- L38 _public member_ `SYMS_U32 e_flags;`
- L39 _public member_ `SYMS_U16 e_ehsize;`
- L40 _public member_ `SYMS_U16 e_phentsize;`
- L41 _public member_ `SYMS_U16 e_phnum;`
- L42 _public member_ `SYMS_U16 e_shentsize;`
- L43 _public member_ `SYMS_U16 e_shnum;`
- L44 _public member_ `SYMS_U16 e_shstrndx;`

#### struct `SYMS_ElfEhdr32`  
`struct SYMS_ElfEhdr32`  
_L48-64_
- L50 _public member_ `SYMS_U8 e_ident[SYMS_ElfIdentifier_NIDENT];`
- L51 _public member_ `SYMS_U16 e_type;`
- L52 _public member_ `SYMS_U16 e_machine;`
- L53 _public member_ `SYMS_U32 e_version;`
- L54 _public member_ `SYMS_U32 e_entry;`
- L55 _public member_ `SYMS_U32 e_phoff;`
- L56 _public member_ `SYMS_U32 e_shoff;`
- L57 _public member_ `SYMS_U32 e_flags;`
- L58 _public member_ `SYMS_U16 e_ehsize;`
- L59 _public member_ `SYMS_U16 e_phentsize;`
- L60 _public member_ `SYMS_U16 e_phnum;`
- L61 _public member_ `SYMS_U16 e_shentsize;`
- L62 _public member_ `SYMS_U16 e_shnum;`
- L63 _public member_ `SYMS_U16 e_shstrndx;`

#### struct `SYMS_ElfShdr64`  
`struct SYMS_ElfShdr64`  
_L67-79_
- L69 _public member_ `SYMS_U32 sh_name;`
- L70 _public member_ `SYMS_U32 sh_type;`
- L71 _public member_ `SYMS_U64 sh_flags;`
- L72 _public member_ `SYMS_U64 sh_addr;`
- L73 _public member_ `SYMS_U64 sh_offset;`
- L74 _public member_ `SYMS_U64 sh_size;`
- L75 _public member_ `SYMS_U32 sh_link;`
- L76 _public member_ `SYMS_U32 sh_info;`
- L77 _public member_ `SYMS_U64 sh_addralign;`
- L78 _public member_ `SYMS_U64 sh_entsize;`

#### struct `SYMS_ElfShdr32`  
`struct SYMS_ElfShdr32`  
_L82-94_
- L84 _public member_ `SYMS_U32 sh_name;`
- L85 _public member_ `SYMS_U32 sh_type;`
- L86 _public member_ `SYMS_U32 sh_flags;`
- L87 _public member_ `SYMS_U32 sh_addr;`
- L88 _public member_ `SYMS_U32 sh_offset;`
- L89 _public member_ `SYMS_U32 sh_size;`
- L90 _public member_ `SYMS_U32 sh_link;`
- L91 _public member_ `SYMS_U32 sh_info;`
- L92 _public member_ `SYMS_U32 sh_addralign;`
- L93 _public member_ `SYMS_U32 sh_entsize;`

#### struct `SYMS_ElfPhdr64`  
`struct SYMS_ElfPhdr64`  
_L97-107_
- L99 _public member_ `SYMS_U32 p_type;`
- L100 _public member_ `SYMS_U32 p_flags;`
- L101 _public member_ `SYMS_U64 p_offset;`
- L102 _public member_ `SYMS_U64 p_vaddr;`
- L103 _public member_ `SYMS_U64 p_paddr;`
- L104 _public member_ `SYMS_U64 p_filesz;`
- L105 _public member_ `SYMS_U64 p_memsz;`
- L106 _public member_ `SYMS_U64 p_align;`

#### struct `SYMS_ElfPhdr32`  
`struct SYMS_ElfPhdr32`  
_L110-120_
- L112 _public member_ `SYMS_U32 p_type;`
- L113 _public member_ `SYMS_U32 p_offset;`
- L114 _public member_ `SYMS_U32 p_vaddr;`
- L115 _public member_ `SYMS_U32 p_paddr;`
- L116 _public member_ `SYMS_U32 p_filesz;`
- L117 _public member_ `SYMS_U32 p_memsz;`
- L118 _public member_ `SYMS_U32 p_flags;`
- L119 _public member_ `SYMS_U32 p_align;`

#### struct `SYMS_ElfAuxv32`  
`typedef struct SYMS_ElfAuxv32`  
_L127-130_
- L128 _public member_ `SYMS_U32 a_type;`
- L129 _public member_ `SYMS_U32 a_val;`

#### struct `SYMS_ElfAuxv64`  
`typedef struct SYMS_ElfAuxv64`  
_L132-135_
- L133 _public member_ `SYMS_U64 a_type;`
- L134 _public member_ `SYMS_U64 a_val;`

#### struct `SYMS_ElfDyn32`  
`typedef struct SYMS_ElfDyn32`  
_L142-145_
- L143 _public member_ `SYMS_U32 tag;`
- L144 _public member_ `SYMS_U32 val;`

#### struct `SYMS_ElfDyn64`  
`typedef struct SYMS_ElfDyn64`  
_L147-150_
- L148 _public member_ `SYMS_U64 tag;`
- L149 _public member_ `SYMS_U64 val;`

#### struct `SYMS_ElfLinkMap32`  
`typedef struct SYMS_ElfLinkMap32`  
_L152-157_
- L153 _public member_ `SYMS_U32 base;`
- L154 _public member_ `SYMS_U32 name;`
- L155 _public member_ `SYMS_U32 ld;`
- L156 _public member_ `SYMS_U32 next;`

#### struct `SYMS_ElfLinkMap64`  
`typedef struct SYMS_ElfLinkMap64`  
_L159-164_
- L160 _public member_ `SYMS_U64 base;`
- L161 _public member_ `SYMS_U64 name;`
- L162 _public member_ `SYMS_U64 ld;`
- L163 _public member_ `SYMS_U64 next;`

#### struct `(anonymous)`  
``  
_L170-177_

#### struct `(anonymous)`  
``  
_L180-187_

#### struct `(anonymous)`  
``  
_L195-198_

#### struct `(anonymous)`  
``  
_L201-205_

#### struct `(anonymous)`  
``  
_L208-211_

#### struct `(anonymous)`  
``  
_L214-218_

#### struct `(anonymous)`  
``  
_L233-241_

#### struct `(anonymous)`  
``  
_L245-248_

#### struct `(anonymous)`  
``  
_L252-258_

#### struct `(anonymous)`  
``  
_L262-268_

#### struct `(anonymous)`  
``  
_L272-274_

#### struct `(anonymous)`  
``  
_L277-283_

#### enum `SYMS_ElfCompressTypeEnum`  
`enum SYMS_ElfCompressTypeEnum`  
_L289-300_
- L291 _public enumerator_ `SYMS_ElfCompressType_None = 0`
- L292 _public enumerator_ `SYMS_ElfCompressType_ZLib = 1`
- L293 _public enumerator_ `SYMS_ElfCompressType_ZStd = 2`
- L295 _public enumerator_ `SYMS_ElfCompressType_LoOs = 0x60000000`
- L296 _public enumerator_ `SYMS_ElfCompressType_HiOs = 0x6fffffff`
- L298 _public enumerator_ `SYMS_ElfCompressType_LoProc = 0x70000000`
- L299 _public enumerator_ `SYMS_ElfCompressType_HiProc = 0x7fffffff`

#### struct `SYMS_ElfChdr32`  
`typedef struct SYMS_ElfChdr32`  
_L302-307_
- L304 _public member_ `SYMS_U32 ch_type;`
- L305 _public member_ `SYMS_U32 ch_size;`
- L306 _public member_ `SYMS_U32 ch_addr_align;`

#### struct `SYMS_ElfChdr64`  
`typedef struct SYMS_ElfChdr64`  
_L309-315_
- L311 _public member_ `SYMS_U32 ch_type;`
- L312 _public member_ `SYMS_U32 ch_reserved;`
- L313 _public member_ `SYMS_U64 ch_size;`
- L314 _public member_ `SYMS_U64 ch_addr_align;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_ELF_H`
- L26 _typedef_ `SYMS_ElfIdentifier_OSABI = 7, SYMS_ElfIdentfiier_ABIVERSION = 8, SYMS_ElfIdentifier_NIDENT = 16, }SYMS_ElfIdentifier;`
- L28 _typedef_ `typedef struct SYMS_ElfEhdr64 SYMS_ElfEhdr64;`
- L47 _typedef_ `typedef struct SYMS_ElfEhdr32 SYMS_ElfEhdr32;`
- L66 _typedef_ `typedef struct SYMS_ElfShdr64 SYMS_ElfShdr64;`
- L81 _typedef_ `typedef struct SYMS_ElfShdr32 SYMS_ElfShdr32;`
- L96 _typedef_ `typedef struct SYMS_ElfPhdr64 SYMS_ElfPhdr64;`
- L109 _typedef_ `typedef struct SYMS_ElfPhdr32 SYMS_ElfPhdr32;`
- L130 _typedef_ `} SYMS_ElfAuxv32;`
- L135 _typedef_ `} SYMS_ElfAuxv64;`
- L145 _typedef_ `} SYMS_ElfDyn32;`
- L150 _typedef_ `} SYMS_ElfDyn64;`
- L157 _typedef_ `} SYMS_ElfLinkMap32;`
- L164 _typedef_ `} SYMS_ElfLinkMap64;`
- L171 _member_ `SYMS_U32 st_name;` (scope `__anonf734c62c0108`) — Holds index into files string table.
- L172 _member_ `SYMS_U32 st_value;` (scope `__anonf734c62c0108`) — Depending on the context, this may be address, size, etc.
- L173 _member_ `SYMS_U32 st_size;` (scope `__anonf734c62c0108`) — Data size in bytes. Zero when size is unknown.
- L174 _member_ `SYMS_U8 st_info;` (scope `__anonf734c62c0108`) — Contains symbols type and binding.
- L175 _member_ `SYMS_U8 st_other;` (scope `__anonf734c62c0108`) — Reserved for future use, currenly zero.
- L176 _member_ `SYMS_U16 st_shndx;` (scope `__anonf734c62c0108`) — Section index to which symbol is relevant.
- L177 _typedef_ `} SYMS_ElfSym32;`
- L181 _member_ `SYMS_U32 st_name;` (scope `__anonf734c62c0208`)
- L182 _member_ `SYMS_U8 st_info;` (scope `__anonf734c62c0208`)
- L183 _member_ `SYMS_U8 st_other;` (scope `__anonf734c62c0208`)
- L184 _member_ `SYMS_U16 st_shndx;` (scope `__anonf734c62c0208`)
- L185 _member_ `SYMS_U64 st_value;` (scope `__anonf734c62c0208`)
- L186 _member_ `SYMS_U64 st_size;` (scope `__anonf734c62c0208`)
- L187 _typedef_ `} SYMS_ElfSym64;`
- L189 _macro_ `#define SYMS_ELF_ST_INFO(b,t) (((b) << 4) + ((t) & 0xF))`
- L190 _macro_ `#define SYMS_ELF_ST_BIND(x) ((x) >> 4)`
- L191 _macro_ `#define SYMS_ELF_ST_TYPE(x) ((x) & 0xF)`
- L192 _macro_ `#define SYMS_ELF_ST_VISIBILITY(v) ((v) & 0x3)`
- L196 _member_ `SYMS_U32 r_offset;` (scope `__anonf734c62c0308`)
- L197 _member_ `SYMS_U32 r_info;` (scope `__anonf734c62c0308`)
- L198 _typedef_ `} SYMS_ElfRel32;`
- L202 _member_ `SYMS_U32 r_offset;` (scope `__anonf734c62c0408`)
- L203 _member_ `SYMS_U32 r_info;` (scope `__anonf734c62c0408`)
- L204 _member_ `SYMS_S32 r_addend;` (scope `__anonf734c62c0408`)
- L205 _typedef_ `} SYMS_ElfRela32;`
- L209 _member_ `SYMS_U64 r_offset;` (scope `__anonf734c62c0508`)
- L210 _member_ `SYMS_U64 r_info;` (scope `__anonf734c62c0508`)
- L211 _typedef_ `} SYMS_ElfRel64;`
- L215 _member_ `SYMS_U64 r_offset;` (scope `__anonf734c62c0608`)
- L216 _member_ `SYMS_U64 r_info;` (scope `__anonf734c62c0608`)
- L217 _member_ `SYMS_S64 r_addend;` (scope `__anonf734c62c0608`)
- L218 _typedef_ `} SYMS_ElfRela64;`
- L220 _macro_ `#define SYMS_ELF32_R_SYM(x) ((x) >> 8)`
- L221 _macro_ `#define SYMS_ELF32_R_TYPE(x) ((x) & 0xFF)`
- L223 _macro_ `#define SYMS_ELF64_R_INFO(s,t) (((SYMS_U64)(s) << 32) | (SYMS_U64)t)`
- L224 _macro_ `#define SYMS_ELF64_R_SYM(x) ((x) >> 32)`
- L225 _macro_ `#define SYMS_ELF64_R_TYPE(x) ((x) & 0xffffffff)`
- L228 _macro_ `#define SYMS_ELF_EXTERNAL_VERSYM_HIDDEN 0x8000` — This flag is set to indicate that symbol is not available outside the shared object
- L229 _macro_ `#define SYMS_ELF_EXTERNAL_VERSYM_MASK 0x7FFF`
- L234 _member_ `SYMS_U16 vd_version;` (scope `__anonf734c62c0708`)
- L235 _member_ `SYMS_U16 vd_flags;` (scope `__anonf734c62c0708`)
- L236 _member_ `SYMS_U16 vd_ndx;` (scope `__anonf734c62c0708`)
- L237 _member_ `SYMS_U16 vd_cnt;` (scope `__anonf734c62c0708`)
- L238 _member_ `SYMS_U32 vd_hash;` (scope `__anonf734c62c0708`)
- L239 _member_ `SYMS_U32 vd_aux;` (scope `__anonf734c62c0708`)
- L240 _member_ `SYMS_U32 vd_next;` (scope `__anonf734c62c0708`)
- L241 _typedef_ `} SYMS_ElfExternalVerdef;`
- L246 _member_ `SYMS_U32 vda_name;` (scope `__anonf734c62c0808`)
- L247 _member_ `SYMS_U32 vda_next;` (scope `__anonf734c62c0808`)
- L248 _typedef_ `} SYMS_ElfExternalVerdaux;`
- L253 _member_ `SYMS_U16 vn_version;` (scope `__anonf734c62c0908`)
- L254 _member_ `SYMS_U16 vn_cnt;` (scope `__anonf734c62c0908`)
- L255 _member_ `SYMS_U32 vn_file;` (scope `__anonf734c62c0908`)
- L256 _member_ `SYMS_U32 vn_aux;` (scope `__anonf734c62c0908`)
- L257 _member_ `SYMS_U32 vn_next;` (scope `__anonf734c62c0908`)
- L258 _typedef_ `} SYMS_ElfExternalVerneed;`
- L263 _member_ `SYMS_U32 vna_hash;` (scope `__anonf734c62c0a08`)
- L264 _member_ `SYMS_U16 vna_flags;` (scope `__anonf734c62c0a08`)
- L265 _member_ `SYMS_U16 vna_other;` (scope `__anonf734c62c0a08`)
- L266 _member_ `SYMS_U32 vna_name;` (scope `__anonf734c62c0a08`)
- L267 _member_ `SYMS_U32 vna_next;` (scope `__anonf734c62c0a08`)
- L268 _typedef_ `} SYMS_ElfExternalVernaux;`
- L273 _member_ `SYMS_U16 vs_vers;` (scope `__anonf734c62c0b08`)
- L274 _typedef_ `} SYMS_ElfExternalVersym;`
- L278 _member_ `SYMS_U32 name_size;` (scope `__anonf734c62c0c08`)
- L279 _member_ `SYMS_U32 desc_size;` (scope `__anonf734c62c0c08`)
- L280 _member_ `SYMS_U32 type;` (scope `__anonf734c62c0c08`)
- L283 _typedef_ `} SYMS_ElfNote;` — name + desc SYMS_U8  data[1];
- L288 _typedef_ `typedef SYMS_U8 SYMS_ElfCompressType;`
- L307 _typedef_ `} SYMS_ElfChdr32;`
- L315 _typedef_ `} SYMS_ElfChdr64;`
- L323 _prototype_ `SYMS_ElfEhdr64 syms_elf_ehdr64_from_ehdr32(SYMS_ElfEhdr32 h32);` — TODO(allen): avoid extra copies (use pointers where convenient)
- L324 _prototype_ `SYMS_ElfShdr64 syms_elf_shdr64_from_shdr32(SYMS_ElfShdr32 h32);`
- L325 _prototype_ `SYMS_ElfPhdr64 syms_elf_phdr64_from_phdr32(SYMS_ElfPhdr32 h32);`
- L326 _prototype_ `SYMS_ElfDyn64 syms_elf_dyn64_from_dyn32(SYMS_ElfDyn32 h32);`
- L327 _prototype_ `SYMS_ElfSym64 syms_elf_sym64_from_sym32(SYMS_ElfSym32 sym32);`
- L328 _prototype_ `SYMS_ElfRel64 syms_elf_rel64_from_rel32(SYMS_ElfRel32 rel32);`
- L329 _prototype_ `SYMS_ElfRela64 syms_elf_rela64_from_rela32(SYMS_ElfRela32 rela32);`
- L336 _prototype_ `SYMS_U32 syms_elf_gnu_debuglink_crc32(SYMS_U32 crc, SYMS_String8 data);`

### `Source/Runtime/SymsLib/syms/core/elf/syms_elf_parser.h` (Other)


#### struct `SYMS_ElfImgHeader`  
`struct SYMS_ElfImgHeader`  
_L11-21_
- L13 _public member_ `SYMS_B32 valid;`
- L14 _public member_ `SYMS_B32 is_32bit;`
- L15 _public member_ `SYMS_ElfEhdr64 ehdr;`
- L16 _public member_ `SYMS_Arch arch;`
- L17 _public member_ `SYMS_U64 sh_name_low_offset;`
- L18 _public member_ `SYMS_U64 sh_name_high_offset;`
- L19 _public member_ `SYMS_U64 base_address;`
- L20 _public member_ `SYMS_U64 entry_point;`

#### struct `SYMS_ElfSection`  
`struct SYMS_ElfSection`  
_L24-30_
- L26 _public member_ `SYMS_ElfShdr64 header;`
- L27 _public member_ `SYMS_U64Range virtual_range;`
- L28 _public member_ `SYMS_U64Range file_range;`
- L29 _public member_ `SYMS_String8 name;`

#### struct `SYMS_ElfSectionArray`  
`struct SYMS_ElfSectionArray`  
_L33-37_
- L35 _public member_ `SYMS_U64 count;`
- L36 _public member_ `SYMS_ElfSection *v;`

#### struct `SYMS_ElfSegmentArray`  
`struct SYMS_ElfSegmentArray`  
_L40-44_
- L42 _public member_ `SYMS_U64 count;`
- L43 _public member_ `SYMS_ElfPhdr64 *v;`

#### struct `SYMS_ElfExtDebugRef`  
`struct SYMS_ElfExtDebugRef`  
_L47-51_
- L49 _public member_ `SYMS_String8 path;`
- L50 _public member_ `SYMS_U32 external_file_checksum;`

#### struct `SYMS_ElfFileAccel`  
`struct SYMS_ElfFileAccel`  
_L57-61_
- L59 _public member_ `SYMS_FileFormat format;`
- L60 _public member_ `SYMS_ElfImgHeader header;`

#### struct `SYMS_ElfBinAccel`  
`struct SYMS_ElfBinAccel`  
_L67-73_
- L69 _public member_ `SYMS_FileFormat format;`
- L70 _public member_ `SYMS_ElfImgHeader header;`
- L71 _public member_ `SYMS_ElfSectionArray sections;`
- L72 _public member_ `SYMS_ElfSegmentArray segments;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_ELF_PARSER_H`
- L10 _typedef_ `typedef struct SYMS_ElfImgHeader SYMS_ElfImgHeader;`
- L23 _typedef_ `typedef struct SYMS_ElfSection SYMS_ElfSection;`
- L32 _typedef_ `typedef struct SYMS_ElfSectionArray SYMS_ElfSectionArray;`
- L39 _typedef_ `typedef struct SYMS_ElfSegmentArray SYMS_ElfSegmentArray;`
- L46 _typedef_ `typedef struct SYMS_ElfExtDebugRef SYMS_ElfExtDebugRef;`
- L56 _typedef_ `typedef struct SYMS_ElfFileAccel SYMS_ElfFileAccel;`
- L66 _typedef_ `typedef struct SYMS_ElfBinAccel SYMS_ElfBinAccel;`
- L80 _prototype_ `SYMS_ElfImgHeader syms_elf_img_header_from_file(SYMS_String8 file);`
- L81 _prototype_ `SYMS_ElfExtDebugRef syms_elf_ext_debug_ref_from_elf_section_array(SYMS_String8 file, SYMS_ElfSectionArray sections);`
- L82 _prototype_ `SYMS_ElfSectionArray syms_elf_section_array_from_img_header(SYMS_Arena *arena, SYMS_String8 file, SYMS_ElfImgHeader img);`
- L83 _prototype_ `SYMS_ElfSegmentArray syms_elf_segment_array_from_img_header(SYMS_Arena *arena, SYMS_String8 file, SYMS_ElfImgHeader img);`
- L88 _prototype_ `SYMS_SecInfo syms_elf_section_info_from_elf_section(SYMS_ElfSection elf_section);`
- L93 _prototype_ `SYMS_ElfFileAccel *syms_elf_file_accel_from_data(SYMS_Arena *arena, SYMS_String8 string);`
- L98 _prototype_ `SYMS_ElfBinAccel *syms_elf_bin_accel_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_ElfFileAccel *file_accel);`
- L99 _prototype_ `SYMS_ExtFileList syms_elf_ext_file_list_from_bin(SYMS_Arena *arena, SYMS_String8 file, SYMS_ElfBinAccel *bin_accel);`
- L100 _prototype_ `SYMS_SecInfoArray syms_elf_sec_info_array_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_ElfBinAccel *bin);`
- L101 _prototype_ `SYMS_U64 syms_elf_default_vbase_from_bin(SYMS_ElfBinAccel *bin);`
- L102 _prototype_ `SYMS_U64 syms_elf_entry_point_voff_from_bin(SYMS_ElfBinAccel *bin);`
- L104 _prototype_ `SYMS_Arch syms_elf_arch_from_bin(SYMS_ElfBinAccel *bin);`
- L109 _prototype_ `SYMS_ElfSection* syms_elf_sec_from_bin_name__unstable(SYMS_ElfBinAccel *bin, SYMS_String8 name);`
- L114 _prototype_ `SYMS_ImportArray syms_elf_imports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_ElfBinAccel *bin);`
- L115 _prototype_ `SYMS_ExportArray syms_elf_exports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_ElfBinAccel *bin);`

### `Source/Runtime/SymsLib/syms/core/extras/syms_aggregate_proc_map.h` (Other)


#### struct `SYMS_AggregatedProcedureMap`  
`typedef struct SYMS_AggregatedProcedureMap`  
_L9-12_
- L10 _public member_ `SYMS_USIDArray procs;`
- L11 _public member_ `SYMS_SpatialMultiMap1D map;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_AGGREGATE_PROC_MAP_H`
- L12 _typedef_ `} SYMS_AggregatedProcedureMap;`
- L14 _prototype_ `SYMS_AggregatedProcedureMap syms_aggregated_procedure_map_from_group(SYMS_Arena *arena, SYMS_Group *group);`

### `Source/Runtime/SymsLib/syms/core/file_inf/syms_file_inf.h` (Other)


#### struct `SYMS_FileLoadCtx`  
`typedef struct SYMS_FileLoadCtx`  
_L12-15_
- L13 _public member_ `SYMS_FileLoadFunc *file_load_func;`
- L14 _public member_ `void *file_load_user;`

#### struct `SYMS_FileInfNode`  
`typedef struct SYMS_FileInfNode`  
_L17-31_
- L18 _public member_ `struct SYMS_FileInfNode *next;`
- L19 _public member_ `SYMS_String8 file_name;`
- L20 _public member_ `SYMS_String8 data;`
- L22 _public member_ `SYMS_FileAccel *file;`
- L23 _public member_ `SYMS_BinAccel *bin;`
- L24 _public member_ `SYMS_DbgAccel *dbg;`
- L26 _public member_ `SYMS_B32 is_selected_bin;`
- L27 _public member_ `SYMS_B32 is_selected_dbg;`
- L28 _public member_ `SYMS_B32 inferred;`
- L30 _public member_ `struct SYMS_FileInfNode *fallback_to;`

#### struct `SYMS_FileInfTask`  
`typedef struct SYMS_FileInfTask`  
_L33-37_
- L34 _public member_ `struct SYMS_FileInfTask *next;`
- L35 _public member_ `SYMS_String8 file_name;`
- L36 _public member_ `SYMS_FileInfNode *inferred_from_node;`

#### struct `SYMS_FileInfState`  
`typedef struct SYMS_FileInfState`  
_L39-45_
- L40 _public member_ `SYMS_FileInfNode *first_loaded;`
- L41 _public member_ `SYMS_FileInfNode *last_loaded;`
- L42 _public member_ `SYMS_FileInfTask *first_task;`
- L43 _public member_ `SYMS_FileInfTask *last_task;`
- L44 _public member_ `SYMS_FileInfTask *free_task;`

#### struct `SYMS_FileInfOptions`  
`typedef struct SYMS_FileInfOptions`  
_L47-52_
- L48 _public member_ `SYMS_B32 disable_inference;`
- L49 _public member_ `SYMS_B32 disable_fallback;`
- L50 _public member_ `SYMS_String8 fallback_path;`
- L51 _public member_ `SYMS_Arch preferred_arch;`

#### struct `SYMS_FileInfResult`  
`typedef struct SYMS_FileInfResult`  
_L54-60_
- L55 _public member_ `SYMS_FileInfNode *first_inf_node;`
- L56 _public member_ `SYMS_FileInfNode *last_inf_node;`
- L57 _public member_ `SYMS_FileInfNode *selected_bin;`
- L58 _public member_ `SYMS_FileInfNode *selected_dbg;`
- L59 _public member_ `SYMS_ParseBundle data_parsed;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_FILE_INF_H`
- L10 _typedef_ `typedef SYMS_String8 SYMS_FileLoadFunc(void *user, SYMS_Arena *arena, SYMS_String8 file_name);`
- L15 _typedef_ `} SYMS_FileLoadCtx;`
- L31 _typedef_ `} SYMS_FileInfNode;`
- L37 _typedef_ `} SYMS_FileInfTask;`
- L45 _typedef_ `} SYMS_FileInfState;`
- L52 _typedef_ `} SYMS_FileInfOptions;`
- L60 _typedef_ `} SYMS_FileInfResult;`
- L65 _prototype_ `SYMS_FileInfResult syms_file_inf_infer_from_file_list(SYMS_Arena *arena, SYMS_FileLoadCtx ctx, SYMS_String8List file_name_list, SYMS_FileInfOptions *opts);`
- L68 _prototype_ `SYMS_FileInfResult syms_file_inf_infer_from_file(SYMS_Arena *arena, SYMS_FileLoadCtx ctx, SYMS_String8 file_name, SYMS_FileInfOptions *opts);`
- L71 _prototype_ `SYMS_FileInfState syms_file_inf_begin(void);`
- L72 _prototype_ `SYMS_FileInfNode* syms_file_inf_node_from_name(SYMS_FileInfState *state, SYMS_String8 file_name);`
- L73 _prototype_ `SYMS_FileInfNode* syms_file_inf_insert_node(SYMS_Arena *arena, SYMS_FileInfState *state);`
- L75 _prototype_ `SYMS_FileInfTask* syms_file_inf_push_task(SYMS_Arena *arena, SYMS_FileInfState *state);`
- L76 _prototype_ `void syms_file_inf_pop_task(SYMS_FileInfState *state);`
- L78 _prototype_ `SYMS_B32 syms_file_inf_state_step(SYMS_Arena *arena, SYMS_FileInfState *state);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_base.h` (Other)


#### enum `SYMS_Arch`  
`typedef enum SYMS_Arch`  
_L6-16_
- L7 _public enumerator_ `SYMS_Arch_Null`
- L8 _public enumerator_ `SYMS_Arch_X64`
- L9 _public enumerator_ `SYMS_Arch_X86`
- L10 _public enumerator_ `SYMS_Arch_ARM`
- L11 _public enumerator_ `SYMS_Arch_ARM32`
- L12 _public enumerator_ `SYMS_Arch_PPC64`
- L13 _public enumerator_ `SYMS_Arch_PPC`
- L14 _public enumerator_ `SYMS_Arch_IA64`
- L15 _public enumerator_ `SYMS_Arch_COUNT = 8`

#### enum `SYMS_OperatingSystem`  
`typedef enum SYMS_OperatingSystem`  
_L17-23_
- L18 _public enumerator_ `SYMS_OperatingSystem_Null`
- L19 _public enumerator_ `SYMS_OperatingSystem_Win`
- L20 _public enumerator_ `SYMS_OperatingSystem_Linux`
- L21 _public enumerator_ `SYMS_OperatingSystem_Mac`
- L22 _public enumerator_ `SYMS_OperatingSystem_COUNT = 4`

#### enum `SYMS_Language`  
`typedef enum SYMS_Language`  
_L24-93_
- L25 _public enumerator_ `SYMS_Language_Null`
- L27 _public enumerator_ `SYMS_Language_C89` — NOTE(rjf): C and C++
- L28 _public enumerator_ `SYMS_Language_C99`
- L29 _public enumerator_ `SYMS_Language_C11`
- L30 _public enumerator_ `SYMS_Language_C`
- L31 _public enumerator_ `SYMS_Language_CPlusPlus`
- L32 _public enumerator_ `SYMS_Language_CPlusPlus03`
- L33 _public enumerator_ `SYMS_Language_CPlusPlus11`
- L34 _public enumerator_ `SYMS_Language_CPlusPlus14`
- L35 _public enumerator_ `SYMS_Language_CSharp`
- L37 _public enumerator_ `SYMS_Language_ObjectiveC` — NOTE(rjf): Apple languages
- L38 _public enumerator_ `SYMS_Language_ObjectiveCPlusPlus`
- L39 _public enumerator_ `SYMS_Language_Swift`
- L41 _public enumerator_ `SYMS_Language_Java` — NOTE(rjf): Super Cool Kids languages
- L42 _public enumerator_ `SYMS_Language_JavaScript`
- L43 _public enumerator_ `SYMS_Language_Python`
- L44 _public enumerator_ `SYMS_Language_Go`
- L45 _public enumerator_ `SYMS_Language_Rust`
- L46 _public enumerator_ `SYMS_Language_Julia`
- L48 _public enumerator_ `SYMS_Language_D` — NOTE(rjf): Community-Torn-By-GC languages
- L50 _public enumerator_ `SYMS_Language_Fortran` — NOTE(rjf): Languages that everyone jokes about being old, or their derivatives
- L51 _public enumerator_ `SYMS_Language_Fortran77`
- L52 _public enumerator_ `SYMS_Language_Fortran90`
- L53 _public enumerator_ `SYMS_Language_Fortran95`
- L54 _public enumerator_ `SYMS_Language_Fortran03`
- L55 _public enumerator_ `SYMS_Language_Fortran08`
- L56 _public enumerator_ `SYMS_Language_Pascal`
- L57 _public enumerator_ `SYMS_Language_Pascal83`
- L58 _public enumerator_ `SYMS_Language_Ada83`
- L59 _public enumerator_ `SYMS_Language_Ada95`
- L60 _public enumerator_ `SYMS_Language_Cobol`
- L61 _public enumerator_ `SYMS_Language_Cobol74`
- L62 _public enumerator_ `SYMS_Language_Cobol85`
- L63 _public enumerator_ `SYMS_Language_Modula2`
- L64 _public enumerator_ `SYMS_Language_Modula3`
- L66 _public enumerator_ `SYMS_Language_MASM` — NOTE(rjf): ASM, or other bytecode
- L67 _public enumerator_ `SYMS_Language_ILASM`
- L69 _public enumerator_ `SYMS_Language_MSIL` — NOTE(rjf): IL ASM (Common Language Runtime)
- L71 _public enumerator_ `SYMS_Language_Basic` — NOTE(rjf): "Has 'Basic' in the name" languages
- L72 _public enumerator_ `SYMS_Language_VisualBasic`
- L74 _public enumerator_ `SYMS_Language_Link` — NOTE(rjf): Languages I would've never heard about, were it not for DWARF/PDB specs
- L75 _public enumerator_ `SYMS_Language_CVTRES`
- L76 _public enumerator_ `SYMS_Language_CVTPGD`
- L77 _public enumerator_ `SYMS_Language_UPC`
- L78 _public enumerator_ `SYMS_Language_PLI`
- L79 _public enumerator_ `SYMS_Language_Dylan`
- L80 _public enumerator_ `SYMS_Language_BLISS`
- L82 _public enumerator_ `SYMS_Language_HLSL` — NOTE(rjf): GPU Stuff
- L83 _public enumerator_ `SYMS_Language_OpenCL`
- L84 _public enumerator_ `SYMS_Language_RenderScript`
- L86 _public enumerator_ `SYMS_Language_Haskell` — NOTE(rjf): Misc
- L87 _public enumerator_ `SYMS_Language_OCaml`
- L88 _public enumerator_ `SYMS_Language_MipsAssembler`
- L89 _public enumerator_ `SYMS_Language_GoogleRenderScript`
- L90 _public enumerator_ `SYMS_Language_SunAssembler`
- L91 _public enumerator_ `SYMS_Language_BorlandDelphi`
- L92 _public enumerator_ `SYMS_Language_COUNT = 56`

#### enum `SYMS_FileFormat`  
`typedef enum SYMS_FileFormat`  
_L94-102_
- L95 _public enumerator_ `SYMS_FileFormat_Null`
- L96 _public enumerator_ `SYMS_FileFormat_PE`
- L97 _public enumerator_ `SYMS_FileFormat_ELF`
- L98 _public enumerator_ `SYMS_FileFormat_MACH`
- L99 _public enumerator_ `SYMS_FileFormat_PDB`
- L100 _public enumerator_ `SYMS_FileFormat_DWARF`
- L101 _public enumerator_ `SYMS_FileFormat_COUNT = 6`

#### enum `SYMS_ChecksumAlgorithm`  
`typedef enum SYMS_ChecksumAlgorithm`  
_L103-110_
- L104 _public enumerator_ `SYMS_ChecksumAlgorithm_Null`
- L105 _public enumerator_ `SYMS_ChecksumAlgorithm_MD5`
- L106 _public enumerator_ `SYMS_ChecksumAlgorithm_SHA1`
- L107 _public enumerator_ `SYMS_ChecksumAlgorithm_SHA256`
- L108 _public enumerator_ `SYMS_ChecksumAlgorithm_CRC32_IEEE_802_3`
- L109 _public enumerator_ `SYMS_ChecksumAlgorithm_COUNT = 5`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_BASE_H`
- L16 _typedef_ `} SYMS_Arch;`
- L23 _typedef_ `} SYMS_OperatingSystem;`
- L93 _typedef_ `} SYMS_Language;`
- L102 _typedef_ `} SYMS_FileFormat;`
- L110 _typedef_ `} SYMS_ChecksumAlgorithm;`
- L114 _prototype_ `SYMS_U32 syms_address_size_from_arch(SYMS_Arch v);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_coff.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L7-24_

#### enum `(anonymous)`  
`enum`  
_L26-53_

#### struct `SYMS_CoffHeader`  
`typedef struct SYMS_CoffHeader`  
_L55-66_
- L56 _public member_ `SYMS_CoffMachineType machine;`
- L57 _public member_ `SYMS_U16 section_count;`
- L58 _public member_ `SYMS_U32 time_date_stamp;`
- L60 _public member_ `SYMS_U32 pointer_to_symbol_table;` — TODO: rename to "unix_timestamp"
- L61 _public member_ `SYMS_U32 number_of_symbols;`
- L63 _public member_ `SYMS_U16 size_of_optional_header;` — TODO: rename to "symbol_count"
- L65 _public member_ `SYMS_CoffFlags flags;` — TODO: rename to "optional_header_size"

#### enum `(anonymous)`  
`enum`  
_L68-84_

#### enum `(anonymous)`  
`enum`  
_L86-108_

#### struct `SYMS_CoffSectionHeader`  
`typedef struct SYMS_CoffSectionHeader`  
_L110-121_
- L111 _public member_ `SYMS_U8 name[8];`
- L112 _public member_ `SYMS_U32 virt_size;`
- L113 _public member_ `SYMS_U32 virt_off;`
- L114 _public member_ `SYMS_U32 file_size;`
- L115 _public member_ `SYMS_U32 file_off;`
- L116 _public member_ `SYMS_U32 relocs_file_off;`
- L117 _public member_ `SYMS_U32 lines_file_off;`
- L118 _public member_ `SYMS_U16 reloc_count;`
- L119 _public member_ `SYMS_U16 line_count;`
- L120 _public member_ `SYMS_CoffSectionFlags flags;`

#### enum `(anonymous)`  
`enum`  
_L123-145_

#### enum `(anonymous)`  
`enum`  
_L147-179_

#### enum `(anonymous)`  
`enum`  
_L181-203_

#### enum `(anonymous)`  
`enum`  
_L205-224_

#### enum `(anonymous)`  
`enum`  
_L226-245_

#### enum `(anonymous)`  
`enum`  
_L247-276_

#### enum `(anonymous)`  
`enum`  
_L278-283_

#### enum `(anonymous)`  
`enum`  
_L285-291_

#### enum `(anonymous)`  
`enum`  
_L293-298_

#### enum `(anonymous)`  
`enum`  
_L300-305_

#### enum `(anonymous)`  
`enum`  
_L307-313_

#### enum `(anonymous)`  
`enum`  
_L315-330_

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_COFF_H`
- L6 _typedef_ `typedef SYMS_U16 SYMS_CoffFlags;`
- L8 _enumerator_ `SYMS_CoffFlag_RELOC_STRIPPED = (1 << 0)` (scope `__anon3a9ae3b10103`)
- L9 _enumerator_ `SYMS_CoffFlag_EXECUTABLE_IMAGE = (1 << 1)` (scope `__anon3a9ae3b10103`)
- L10 _enumerator_ `SYMS_CoffFlag_LINE_NUMS_STRIPPED = (1 << 2)` (scope `__anon3a9ae3b10103`)
- L11 _enumerator_ `SYMS_CoffFlag_SYM_STRIPPED = (1 << 3)` (scope `__anon3a9ae3b10103`)
- L12 _enumerator_ `SYMS_CoffFlag_RESERVED_0 = (1 << 4)` (scope `__anon3a9ae3b10103`)
- L13 _enumerator_ `SYMS_CoffFlag_LARGE_ADDRESS_AWARE = (1 << 5)` (scope `__anon3a9ae3b10103`)
- L14 _enumerator_ `SYMS_CoffFlag_RESERVED_1 = (1 << 6)` (scope `__anon3a9ae3b10103`)
- L15 _enumerator_ `SYMS_CoffFlag_RESERVED_2 = (1 << 7)` (scope `__anon3a9ae3b10103`)
- L16 _enumerator_ `SYMS_CoffFlag_32BIT_MACHINE = (1 << 8)` (scope `__anon3a9ae3b10103`)
- L17 _enumerator_ `SYMS_CoffFlag_DEBUG_STRIPPED = (1 << 9)` (scope `__anon3a9ae3b10103`)
- L18 _enumerator_ `SYMS_CoffFlag_REMOVABLE_RUN_FROM_SWAP = (1 << 10)` (scope `__anon3a9ae3b10103`)
- L19 _enumerator_ `SYMS_CoffFlag_NET_RUN_FROM_SWAP = (1 << 11)` (scope `__anon3a9ae3b10103`)
- L20 _enumerator_ `SYMS_CoffFlag_SYSTEM = (1 << 12)` (scope `__anon3a9ae3b10103`)
- L21 _enumerator_ `SYMS_CoffFlag_DLL = (1 << 13)` (scope `__anon3a9ae3b10103`)
- L22 _enumerator_ `SYMS_CoffFlag_UP_SYSTEM_ONLY = (1 << 14)` (scope `__anon3a9ae3b10103`)
- L23 _enumerator_ `SYMS_CoffFlag_BYTES_RESERVED_HI = (1 << 15)` (scope `__anon3a9ae3b10103`)
- L25 _typedef_ `typedef SYMS_U16 SYMS_CoffMachineType;`
- L27 _enumerator_ `SYMS_CoffMachineType_UNKNOWN = 0x0` (scope `__anon3a9ae3b10203`)
- L28 _enumerator_ `SYMS_CoffMachineType_X86 = 0x14c` (scope `__anon3a9ae3b10203`)
- L29 _enumerator_ `SYMS_CoffMachineType_X64 = 0x8664` (scope `__anon3a9ae3b10203`)
- L30 _enumerator_ `SYMS_CoffMachineType_ARM33 = 0x1d3` (scope `__anon3a9ae3b10203`)
- L31 _enumerator_ `SYMS_CoffMachineType_ARM = 0x1c0` (scope `__anon3a9ae3b10203`)
- L32 _enumerator_ `SYMS_CoffMachineType_ARM64 = 0xaa64` (scope `__anon3a9ae3b10203`)
- L33 _enumerator_ `SYMS_CoffMachineType_ARMNT = 0x1c4` (scope `__anon3a9ae3b10203`)
- L34 _enumerator_ `SYMS_CoffMachineType_EBC = 0xebc` (scope `__anon3a9ae3b10203`)
- L35 _enumerator_ `SYMS_CoffMachineType_IA64 = 0x200` (scope `__anon3a9ae3b10203`)
- L36 _enumerator_ `SYMS_CoffMachineType_M32R = 0x9041` (scope `__anon3a9ae3b10203`)
- L37 _enumerator_ `SYMS_CoffMachineType_MIPS16 = 0x266` (scope `__anon3a9ae3b10203`)
- L38 _enumerator_ `SYMS_CoffMachineType_MIPSFPU = 0x366` (scope `__anon3a9ae3b10203`)
- L39 _enumerator_ `SYMS_CoffMachineType_MIPSFPU16 = 0x466` (scope `__anon3a9ae3b10203`)
- L40 _enumerator_ `SYMS_CoffMachineType_POWERPC = 0x1f0` (scope `__anon3a9ae3b10203`)
- L41 _enumerator_ `SYMS_CoffMachineType_POWERPCFP = 0x1f1` (scope `__anon3a9ae3b10203`)
- L42 _enumerator_ `SYMS_CoffMachineType_R4000 = 0x166` (scope `__anon3a9ae3b10203`)
- L43 _enumerator_ `SYMS_CoffMachineType_RISCV32 = 0x5032` (scope `__anon3a9ae3b10203`)
- L44 _enumerator_ `SYMS_CoffMachineType_RISCV64 = 0x5064` (scope `__anon3a9ae3b10203`)
- L45 _enumerator_ `SYMS_CoffMachineType_RISCV128 = 0x5128` (scope `__anon3a9ae3b10203`)
- L46 _enumerator_ `SYMS_CoffMachineType_SH3 = 0x1a2` (scope `__anon3a9ae3b10203`)
- L47 _enumerator_ `SYMS_CoffMachineType_SH3DSP = 0x1a3` (scope `__anon3a9ae3b10203`)
- L48 _enumerator_ `SYMS_CoffMachineType_SH4 = 0x1a6` (scope `__anon3a9ae3b10203`)
- L49 _enumerator_ `SYMS_CoffMachineType_SH5 = 0x1a8` (scope `__anon3a9ae3b10203`)
- L50 _enumerator_ `SYMS_CoffMachineType_THUMB = 0x1c2` (scope `__anon3a9ae3b10203`)
- L51 _enumerator_ `SYMS_CoffMachineType_WCEMIPSV2 = 0x169` (scope `__anon3a9ae3b10203`)
- L52 _enumerator_ `SYMS_CoffMachineType_COUNT = 25` (scope `__anon3a9ae3b10203`)
- L66 _typedef_ `} SYMS_CoffHeader;`
- L67 _typedef_ `typedef SYMS_U32 SYMS_CoffSectionAlign;`
- L69 _enumerator_ `SYMS_CoffSectionAlign_1BYTES = 0x1` (scope `__anon3a9ae3b10303`)
- L70 _enumerator_ `SYMS_CoffSectionAlign_2BYTES = 0x2` (scope `__anon3a9ae3b10303`)
- L71 _enumerator_ `SYMS_CoffSectionAlign_4BYTES = 0x3` (scope `__anon3a9ae3b10303`)
- L72 _enumerator_ `SYMS_CoffSectionAlign_8BYTES = 0x4` (scope `__anon3a9ae3b10303`)
- L73 _enumerator_ `SYMS_CoffSectionAlign_16BYTES = 0x5` (scope `__anon3a9ae3b10303`)
- L74 _enumerator_ `SYMS_CoffSectionAlign_32BYTES = 0x6` (scope `__anon3a9ae3b10303`)
- L75 _enumerator_ `SYMS_CoffSectionAlign_64BYTES = 0x7` (scope `__anon3a9ae3b10303`)
- L76 _enumerator_ `SYMS_CoffSectionAlign_128BYTES = 0x8` (scope `__anon3a9ae3b10303`)
- L77 _enumerator_ `SYMS_CoffSectionAlign_256BYTES = 0x9` (scope `__anon3a9ae3b10303`)
- L78 _enumerator_ `SYMS_CoffSectionAlign_512BYTES = 0xA` (scope `__anon3a9ae3b10303`)
- L79 _enumerator_ `SYMS_CoffSectionAlign_1024BYTES = 0xB` (scope `__anon3a9ae3b10303`)
- L80 _enumerator_ `SYMS_CoffSectionAlign_2048BYTES = 0xC` (scope `__anon3a9ae3b10303`)
- L81 _enumerator_ `SYMS_CoffSectionAlign_4096BYTES = 0xD` (scope `__anon3a9ae3b10303`)
- L82 _enumerator_ `SYMS_CoffSectionAlign_8192BYTES = 0xE` (scope `__anon3a9ae3b10303`)
- L83 _enumerator_ `SYMS_CoffSectionAlign_COUNT = 14` (scope `__anon3a9ae3b10303`)
- L85 _typedef_ `typedef SYMS_U32 SYMS_CoffSectionFlags;`
- L87 _enumerator_ `SYMS_CoffSectionFlag_TYPE_NO_PAD = (1 << 3)` (scope `__anon3a9ae3b10403`)
- L88 _enumerator_ `SYMS_CoffSectionFlag_CNT_CODE = (1 << 5)` (scope `__anon3a9ae3b10403`)
- L89 _enumerator_ `SYMS_CoffSectionFlag_CNT_INITIALIZED_DATA = (1 << 6)` (scope `__anon3a9ae3b10403`)
- L90 _enumerator_ `SYMS_CoffSectionFlag_CNT_UNINITIALIZED_DATA = (1 << 7)` (scope `__anon3a9ae3b10403`)
- L91 _enumerator_ `SYMS_CoffSectionFlag_LNK_OTHER = (1 << 8)` (scope `__anon3a9ae3b10403`)
- L92 _enumerator_ `SYMS_CoffSectionFlag_LNK_INFO = (1 << 9)` (scope `__anon3a9ae3b10403`)
- L93 _enumerator_ `SYMS_CoffSectionFlag_LNK_REMOVE = (1 << 11)` (scope `__anon3a9ae3b10403`)
- L94 _enumerator_ `SYMS_CoffSectionFlag_LNK_COMDAT = (1 << 12)` (scope `__anon3a9ae3b10403`)
- L95 _enumerator_ `SYMS_CoffSectionFlag_GPREL = (1 << 15)` (scope `__anon3a9ae3b10403`)
- L96 _enumerator_ `SYMS_CoffSectionFlag_MEM_16BIT = (1 << 17)` (scope `__anon3a9ae3b10403`)
- L97 _enumerator_ `SYMS_CoffSectionFlag_MEM_LOCKED = (1 << 18)` (scope `__anon3a9ae3b10403`)
- L98 _enumerator_ `SYMS_CoffSectionFlag_MEM_PRELOAD = (1 << 19)` (scope `__anon3a9ae3b10403`)
- L99 _enumerator_ `SYMS_CoffSectionFlag_ALIGN_SHIFT = 20` (scope `__anon3a9ae3b10403`)
- L99 _enumerator_ `SYMS_CoffSectionFlag_ALIGN_SHIFT = 20` (scope `__anon3a9ae3b10403`)
- L100 _enumerator_ `SYMS_CoffSectionFlag_LNK_NRELOC_OVFL = (1 << 24)` (scope `__anon3a9ae3b10403`)
- L101 _enumerator_ `SYMS_CoffSectionFlag_MEM_DISCARDABLE = (1 << 25)` (scope `__anon3a9ae3b10403`)
- L102 _enumerator_ `SYMS_CoffSectionFlag_MEM_NOT_CACHED = (1 << 26)` (scope `__anon3a9ae3b10403`)
- L103 _enumerator_ `SYMS_CoffSectionFlag_MEM_NOT_PAGED = (1 << 27)` (scope `__anon3a9ae3b10403`)
- L104 _enumerator_ `SYMS_CoffSectionFlag_MEM_SHARED = (1 << 28)` (scope `__anon3a9ae3b10403`)
- L105 _enumerator_ `SYMS_CoffSectionFlag_MEM_EXECUTE = (1 << 29)` (scope `__anon3a9ae3b10403`)
- L106 _enumerator_ `SYMS_CoffSectionFlag_MEM_READ = (1 << 30)` (scope `__anon3a9ae3b10403`)
- L107 _enumerator_ `SYMS_CoffSectionFlag_MEM_WRITE = (1 << 31)` (scope `__anon3a9ae3b10403`)
- L109 _macro_ `#define SYMS_CoffSectionFlags_Extract_ALIGN(f) (SYMS_CoffSectionAlign)(((f) >> SYMS_CoffSectionFlag_ALIGN_SHIFT) & SYMS_CoffSectionFlag_ALIGN_MASK)`
- L121 _typedef_ `} SYMS_CoffSectionHeader;`
- L122 _typedef_ `typedef SYMS_U16 SYMS_CoffRelocTypeX64;`
- L124 _enumerator_ `SYMS_CoffRelocTypeX64_ABS = 0x0` (scope `__anon3a9ae3b10503`)
- L125 _enumerator_ `SYMS_CoffRelocTypeX64_ADDR64 = 0x1` (scope `__anon3a9ae3b10503`)
- L126 _enumerator_ `SYMS_CoffRelocTypeX64_ADDR32 = 0x2` (scope `__anon3a9ae3b10503`)
- L127 _enumerator_ `SYMS_CoffRelocTypeX64_ADDR32NB = 0x3` (scope `__anon3a9ae3b10503`)
- L129 _enumerator_ `SYMS_CoffRelocTypeX64_REL32 = 0x4` (scope `__anon3a9ae3b10503`) — NB => No Base
- L130 _enumerator_ `SYMS_CoffRelocTypeX64_REL32_1 = 0x5` (scope `__anon3a9ae3b10503`)
- L131 _enumerator_ `SYMS_CoffRelocTypeX64_REL32_2 = 0x6` (scope `__anon3a9ae3b10503`)
- L132 _enumerator_ `SYMS_CoffRelocTypeX64_REL32_3 = 0x7` (scope `__anon3a9ae3b10503`)
- L133 _enumerator_ `SYMS_CoffRelocTypeX64_REL32_4 = 0x8` (scope `__anon3a9ae3b10503`)
- L134 _enumerator_ `SYMS_CoffRelocTypeX64_REL32_5 = 0x9` (scope `__anon3a9ae3b10503`)
- L135 _enumerator_ `SYMS_CoffRelocTypeX64_SECTION = 0xA` (scope `__anon3a9ae3b10503`)
- L136 _enumerator_ `SYMS_CoffRelocTypeX64_SECREL = 0xB` (scope `__anon3a9ae3b10503`)
- L137 _enumerator_ `SYMS_CoffRelocTypeX64_SECREL7 = 0xC` (scope `__anon3a9ae3b10503`)
- L139 _enumerator_ `SYMS_CoffRelocTypeX64_TOKEN = 0xD` (scope `__anon3a9ae3b10503`) — TODO(nick): MSDN doesn't specify size for CLR token
- L140 _enumerator_ `SYMS_CoffRelocTypeX64_SREL32 = 0xE` (scope `__anon3a9ae3b10503`)
- L142 _enumerator_ `SYMS_CoffRelocTypeX64_PAIR = 0xF` (scope `__anon3a9ae3b10503`) — TODO(nick): MSDN doesn't specify size for PAIR
- L143 _enumerator_ `SYMS_CoffRelocTypeX64_SSPAN32 = 0x10` (scope `__anon3a9ae3b10503`)
- L144 _enumerator_ `SYMS_CoffRelocTypeX64_COUNT = 17` (scope `__anon3a9ae3b10503`)
- L146 _typedef_ `typedef SYMS_U16 SYMS_CoffRelocTypeX86;`
- L148 _enumerator_ `SYMS_CoffRelocTypeX86_ABS = 0x0` (scope `__anon3a9ae3b10603`)
- L150 _enumerator_ `SYMS_CoffRelocTypeX86_DIR16 = 0x1` (scope `__anon3a9ae3b10603`) — relocation is ignored
- L152 _enumerator_ `SYMS_CoffRelocTypeX86_REL16 = 0x2` (scope `__anon3a9ae3b10603`) — no support
- L154 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN0 = 0x3` (scope `__anon3a9ae3b10603`) — no support
- L155 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN2 = 0x4` (scope `__anon3a9ae3b10603`)
- L156 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN3 = 0x5` (scope `__anon3a9ae3b10603`)
- L157 _enumerator_ `SYMS_CoffRelocTypeX86_DIR32 = 0x6` (scope `__anon3a9ae3b10603`)
- L159 _enumerator_ `SYMS_CoffRelocTypeX86_DIR32NB = 0x7` (scope `__anon3a9ae3b10603`) — 32-bit virtual address
- L161 _enumerator_ `SYMS_CoffRelocTypeX86_SEG12 = 0x9` (scope `__anon3a9ae3b10603`) — 32-bit virtual offset
- L163 _enumerator_ `SYMS_CoffRelocTypeX86_SECTION = 0xA` (scope `__anon3a9ae3b10603`) — no support
- L165 _enumerator_ `SYMS_CoffRelocTypeX86_SECREL = 0xB` (scope `__anon3a9ae3b10603`) — 16-bit section index, used for debug info purposes
- L167 _enumerator_ `SYMS_CoffRelocTypeX86_TOKEN = 0xC` (scope `__anon3a9ae3b10603`) — 32-bit offset from start of a section
- L169 _enumerator_ `SYMS_CoffRelocTypeX86_SECREL7 = 0xD` (scope `__anon3a9ae3b10603`) — CLR token? (for managed languages)
- L171 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN4 = 0xE` (scope `__anon3a9ae3b10603`) — 7-bit offset from the base of the section that contains the target.
- L172 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN5 = 0xF` (scope `__anon3a9ae3b10603`)
- L173 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN6 = 0x10` (scope `__anon3a9ae3b10603`)
- L174 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN7 = 0x11` (scope `__anon3a9ae3b10603`)
- L175 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN8 = 0x12` (scope `__anon3a9ae3b10603`)
- L176 _enumerator_ `SYMS_CoffRelocTypeX86_UNKNOWN9 = 0x13` (scope `__anon3a9ae3b10603`)
- L177 _enumerator_ `SYMS_CoffRelocTypeX86_REL32 = 0x14` (scope `__anon3a9ae3b10603`)
- L178 _enumerator_ `SYMS_CoffRelocTypeX86_COUNT = 20` (scope `__anon3a9ae3b10603`)
- L180 _typedef_ `typedef SYMS_U16 SYMS_CoffRelocTypeARM;`
- L182 _enumerator_ `SYMS_CoffRelocTypeARM_ABS = 0x0` (scope `__anon3a9ae3b10703`)
- L183 _enumerator_ `SYMS_CoffRelocTypeARM_ADDR32 = 0x1` (scope `__anon3a9ae3b10703`)
- L184 _enumerator_ `SYMS_CoffRelocTypeARM_ADDR32NB = 0x2` (scope `__anon3a9ae3b10703`)
- L185 _enumerator_ `SYMS_CoffRelocTypeARM_BRANCH24 = 0x3` (scope `__anon3a9ae3b10703`)
- L186 _enumerator_ `SYMS_CoffRelocTypeARM_BRANCH11 = 0x4` (scope `__anon3a9ae3b10703`)
- L187 _enumerator_ `SYMS_CoffRelocTypeARM_UNKNOWN1 = 0x5` (scope `__anon3a9ae3b10703`)
- L188 _enumerator_ `SYMS_CoffRelocTypeARM_UNKNOWN2 = 0x6` (scope `__anon3a9ae3b10703`)
- L189 _enumerator_ `SYMS_CoffRelocTypeARM_UNKNOWN3 = 0x7` (scope `__anon3a9ae3b10703`)
- L190 _enumerator_ `SYMS_CoffRelocTypeARM_UNKNOWN4 = 0x8` (scope `__anon3a9ae3b10703`)
- L191 _enumerator_ `SYMS_CoffRelocTypeARM_UNKNOWN5 = 0x9` (scope `__anon3a9ae3b10703`)
- L192 _enumerator_ `SYMS_CoffRelocTypeARM_REL32 = 0xA` (scope `__anon3a9ae3b10703`)
- L193 _enumerator_ `SYMS_CoffRelocTypeARM_SECTION = 0xE` (scope `__anon3a9ae3b10703`)
- L194 _enumerator_ `SYMS_CoffRelocTypeARM_SECREL = 0xF` (scope `__anon3a9ae3b10703`)
- L195 _enumerator_ `SYMS_CoffRelocTypeARM_MOV32 = 0x10` (scope `__anon3a9ae3b10703`)
- L196 _enumerator_ `SYMS_CoffRelocTypeARM_THUMB_MOV32 = 0x11` (scope `__anon3a9ae3b10703`)
- L197 _enumerator_ `SYMS_CoffRelocTypeARM_THUMB_BRANCH20 = 0x12` (scope `__anon3a9ae3b10703`)
- L198 _enumerator_ `SYMS_CoffRelocTypeARM_UNUSED = 0x13` (scope `__anon3a9ae3b10703`)
- L199 _enumerator_ `SYMS_CoffRelocTypeARM_THUMB_BRANCH24 = 0x14` (scope `__anon3a9ae3b10703`)
- L200 _enumerator_ `SYMS_CoffRelocTypeARM_THUMB_BLX23 = 0x15` (scope `__anon3a9ae3b10703`)
- L201 _enumerator_ `SYMS_CoffRelocTypeARM_PAIR = 0x16` (scope `__anon3a9ae3b10703`)
- L202 _enumerator_ `SYMS_CoffRelocTypeARM_COUNT = 20` (scope `__anon3a9ae3b10703`)
- L204 _typedef_ `typedef SYMS_U16 SYMS_CoffRelocTypeARM64;`
- L206 _enumerator_ `SYMS_CoffRelocTypeARM64_ABS = 0x0` (scope `__anon3a9ae3b10803`)
- L207 _enumerator_ `SYMS_CoffRelocTypeARM64_ADDR32 = 0x1` (scope `__anon3a9ae3b10803`)
- L208 _enumerator_ `SYMS_CoffRelocTypeARM64_ADDR32NB = 0x2` (scope `__anon3a9ae3b10803`)
- L209 _enumerator_ `SYMS_CoffRelocTypeARM64_BRANCH26 = 0x3` (scope `__anon3a9ae3b10803`)
- L210 _enumerator_ `SYMS_CoffRelocTypeARM64_PAGEBASE_REL21 = 0x4` (scope `__anon3a9ae3b10803`)
- L211 _enumerator_ `SYMS_CoffRelocTypeARM64_REL21 = 0x5` (scope `__anon3a9ae3b10803`)
- L212 _enumerator_ `SYMS_CoffRelocTypeARM64_PAGEOFFSET_12A = 0x6` (scope `__anon3a9ae3b10803`)
- L213 _enumerator_ `SYMS_CoffRelocTypeARM64_SECREL = 0x8` (scope `__anon3a9ae3b10803`)
- L214 _enumerator_ `SYMS_CoffRelocTypeARM64_SECREL_LOW12A = 0x9` (scope `__anon3a9ae3b10803`)
- L215 _enumerator_ `SYMS_CoffRelocTypeARM64_SECREL_HIGH12A = 0xA` (scope `__anon3a9ae3b10803`)
- L216 _enumerator_ `SYMS_CoffRelocTypeARM64_SECREL_LOW12L = 0xB` (scope `__anon3a9ae3b10803`)
- L217 _enumerator_ `SYMS_CoffRelocTypeARM64_TOKEN = 0xC` (scope `__anon3a9ae3b10803`)
- L218 _enumerator_ `SYMS_CoffRelocTypeARM64_SECTION = 0xD` (scope `__anon3a9ae3b10803`)
- L219 _enumerator_ `SYMS_CoffRelocTypeARM64_ADDR64 = 0xE` (scope `__anon3a9ae3b10803`)
- L220 _enumerator_ `SYMS_CoffRelocTypeARM64_BRANCH19 = 0xF` (scope `__anon3a9ae3b10803`)
- L221 _enumerator_ `SYMS_CoffRelocTypeARM64_BRANCH14 = 0x10` (scope `__anon3a9ae3b10803`)
- L222 _enumerator_ `SYMS_CoffRelocTypeARM64_REL32 = 0x11` (scope `__anon3a9ae3b10803`)
- L223 _enumerator_ `SYMS_CoffRelocTypeARM64_COUNT = 17` (scope `__anon3a9ae3b10803`)
- L225 _typedef_ `typedef SYMS_U8 SYMS_CoffSymType;`
- L227 _enumerator_ `SYMS_CoffSymType_NULL` (scope `__anon3a9ae3b10903`)
- L228 _enumerator_ `SYMS_CoffSymType_VOID` (scope `__anon3a9ae3b10903`)
- L229 _enumerator_ `SYMS_CoffSymType_CHAR` (scope `__anon3a9ae3b10903`)
- L230 _enumerator_ `SYMS_CoffSymType_SHORT` (scope `__anon3a9ae3b10903`)
- L231 _enumerator_ `SYMS_CoffSymType_INT` (scope `__anon3a9ae3b10903`)
- L232 _enumerator_ `SYMS_CoffSymType_LONG` (scope `__anon3a9ae3b10903`)
- L233 _enumerator_ `SYMS_CoffSymType_FLOAT` (scope `__anon3a9ae3b10903`)
- L234 _enumerator_ `SYMS_CoffSymType_DOUBLE` (scope `__anon3a9ae3b10903`)
- L235 _enumerator_ `SYMS_CoffSymType_STRUCT` (scope `__anon3a9ae3b10903`)
- L236 _enumerator_ `SYMS_CoffSymType_UNION` (scope `__anon3a9ae3b10903`)
- L237 _enumerator_ `SYMS_CoffSymType_ENUM` (scope `__anon3a9ae3b10903`)
- L238 _enumerator_ `SYMS_CoffSymType_MOE` (scope `__anon3a9ae3b10903`)
- L240 _enumerator_ `SYMS_CoffSymType_BYTE` (scope `__anon3a9ae3b10903`) — member of enumeration
- L241 _enumerator_ `SYMS_CoffSymType_WORD` (scope `__anon3a9ae3b10903`)
- L242 _enumerator_ `SYMS_CoffSymType_UINT` (scope `__anon3a9ae3b10903`)
- L243 _enumerator_ `SYMS_CoffSymType_DWORD` (scope `__anon3a9ae3b10903`)
- L244 _enumerator_ `SYMS_CoffSymType_COUNT = 16` (scope `__anon3a9ae3b10903`)
- L246 _typedef_ `typedef SYMS_U8 SYMS_CoffSymStorageClass;`
- L248 _enumerator_ `SYMS_CoffSymStorageClass_END_OF_FUNCTION = 0xff` (scope `__anon3a9ae3b10a03`)
- L249 _enumerator_ `SYMS_CoffSymStorageClass_NULL = 0` (scope `__anon3a9ae3b10a03`)
- L250 _enumerator_ `SYMS_CoffSymStorageClass_AUTOMATIC = 1` (scope `__anon3a9ae3b10a03`)
- L251 _enumerator_ `SYMS_CoffSymStorageClass_EXTERNAL = 2` (scope `__anon3a9ae3b10a03`)
- L252 _enumerator_ `SYMS_CoffSymStorageClass_STATIC = 3` (scope `__anon3a9ae3b10a03`)
- L253 _enumerator_ `SYMS_CoffSymStorageClass_REGISTER = 4` (scope `__anon3a9ae3b10a03`)
- L254 _enumerator_ `SYMS_CoffSymStorageClass_EXTERNAL_DEF = 5` (scope `__anon3a9ae3b10a03`)
- L255 _enumerator_ `SYMS_CoffSymStorageClass_LABEL = 6` (scope `__anon3a9ae3b10a03`)
- L256 _enumerator_ `SYMS_CoffSymStorageClass_UNDEFINED_LABEL = 7` (scope `__anon3a9ae3b10a03`)
- L257 _enumerator_ `SYMS_CoffSymStorageClass_MEMBER_OF_STRUCT = 8` (scope `__anon3a9ae3b10a03`)
- L258 _enumerator_ `SYMS_CoffSymStorageClass_ARGUMENT = 9` (scope `__anon3a9ae3b10a03`)
- L259 _enumerator_ `SYMS_CoffSymStorageClass_STRUCT_TAG = 10` (scope `__anon3a9ae3b10a03`)
- L260 _enumerator_ `SYMS_CoffSymStorageClass_MEMBER_OF_UNION = 11` (scope `__anon3a9ae3b10a03`)
- L261 _enumerator_ `SYMS_CoffSymStorageClass_UNION_TAG = 12` (scope `__anon3a9ae3b10a03`)
- L262 _enumerator_ `SYMS_CoffSymStorageClass_TYPE_DEFINITION = 13` (scope `__anon3a9ae3b10a03`)
- L263 _enumerator_ `SYMS_CoffSymStorageClass_UNDEFINED_STATIC = 14` (scope `__anon3a9ae3b10a03`)
- L264 _enumerator_ `SYMS_CoffSymStorageClass_ENUM_TAG = 15` (scope `__anon3a9ae3b10a03`)
- L265 _enumerator_ `SYMS_CoffSymStorageClass_MEMBER_OF_ENUM = 16` (scope `__anon3a9ae3b10a03`)
- L266 _enumerator_ `SYMS_CoffSymStorageClass_REGISTER_PARAM = 17` (scope `__anon3a9ae3b10a03`)
- L267 _enumerator_ `SYMS_CoffSymStorageClass_BIT_FIELD = 18` (scope `__anon3a9ae3b10a03`)
- L268 _enumerator_ `SYMS_CoffSymStorageClass_BLOCK = 100` (scope `__anon3a9ae3b10a03`)
- L269 _enumerator_ `SYMS_CoffSymStorageClass_FUNCTION = 101` (scope `__anon3a9ae3b10a03`)
- L270 _enumerator_ `SYMS_CoffSymStorageClass_END_OF_STRUCT = 102` (scope `__anon3a9ae3b10a03`)
- L271 _enumerator_ `SYMS_CoffSymStorageClass_FILE = 103` (scope `__anon3a9ae3b10a03`)
- L272 _enumerator_ `SYMS_CoffSymStorageClass_SECTION = 104` (scope `__anon3a9ae3b10a03`)
- L273 _enumerator_ `SYMS_CoffSymStorageClass_WEAK_EXTERNAL = 105` (scope `__anon3a9ae3b10a03`)
- L274 _enumerator_ `SYMS_CoffSymStorageClass_CLR_TOKEN = 107` (scope `__anon3a9ae3b10a03`)
- L275 _enumerator_ `SYMS_CoffSymStorageClass_COUNT = 27` (scope `__anon3a9ae3b10a03`)
- L277 _typedef_ `typedef SYMS_U16 SYMS_CoffSymSecNumber;`
- L279 _enumerator_ `SYMS_CoffSymSecNumber_NUMBER_UNDEFINED = 0` (scope `__anon3a9ae3b10b03`)
- L280 _enumerator_ `SYMS_CoffSymSecNumber_ABSOLUTE = 0xffff` (scope `__anon3a9ae3b10b03`)
- L281 _enumerator_ `SYMS_CoffSymSecNumber_DEBUG = 0xfffe` (scope `__anon3a9ae3b10b03`)
- L282 _enumerator_ `SYMS_CoffSymSecNumber_COUNT = 3` (scope `__anon3a9ae3b10b03`)
- L284 _typedef_ `typedef SYMS_U8 SYMS_CoffSymDType;`
- L286 _enumerator_ `SYMS_CoffSymDType_NULL = 0` (scope `__anon3a9ae3b10c03`)
- L287 _enumerator_ `SYMS_CoffSymDType_PTR = 16` (scope `__anon3a9ae3b10c03`)
- L288 _enumerator_ `SYMS_CoffSymDType_FUNC = 32` (scope `__anon3a9ae3b10c03`)
- L289 _enumerator_ `SYMS_CoffSymDType_ARRAY = 48` (scope `__anon3a9ae3b10c03`)
- L290 _enumerator_ `SYMS_CoffSymDType_COUNT = 4` (scope `__anon3a9ae3b10c03`)
- L292 _typedef_ `typedef SYMS_U32 SYMS_CoffWeakExtType;`
- L294 _enumerator_ `SYMS_CoffWeakExtType_NOLIBRARY = 1` (scope `__anon3a9ae3b10d03`)
- L295 _enumerator_ `SYMS_CoffWeakExtType_SEARCH_LIBRARY = 2` (scope `__anon3a9ae3b10d03`)
- L296 _enumerator_ `SYMS_CoffWeakExtType_SEARCH_ALIAS = 3` (scope `__anon3a9ae3b10d03`)
- L297 _enumerator_ `SYMS_CoffWeakExtType_COUNT = 3` (scope `__anon3a9ae3b10d03`)
- L299 _typedef_ `typedef SYMS_U32 SYMS_CoffImportHeaderType;`
- L301 _enumerator_ `SYMS_CoffImportHeaderType_CODE = 0` (scope `__anon3a9ae3b10e03`)
- L302 _enumerator_ `SYMS_CoffImportHeaderType_DATA = 1` (scope `__anon3a9ae3b10e03`)
- L303 _enumerator_ `SYMS_CoffImportHeaderType_CONST = 2` (scope `__anon3a9ae3b10e03`)
- L304 _enumerator_ `SYMS_CoffImportHeaderType_COUNT = 3` (scope `__anon3a9ae3b10e03`)
- L306 _typedef_ `typedef SYMS_U32 SYMS_CoffImportHeaderNameType;`
- L308 _enumerator_ `SYMS_CoffImportHeaderNameType_ORDINAL = 0` (scope `__anon3a9ae3b10f03`)
- L309 _enumerator_ `SYMS_CoffImportHeaderNameType_NAME = 1` (scope `__anon3a9ae3b10f03`)
- L310 _enumerator_ `SYMS_CoffImportHeaderNameType_NAME_NOPREFIX = 2` (scope `__anon3a9ae3b10f03`)
- L311 _enumerator_ `SYMS_CoffImportHeaderNameType_UNDECORATE = 3` (scope `__anon3a9ae3b10f03`)
- L312 _enumerator_ `SYMS_CoffImportHeaderNameType_COUNT = 4` (scope `__anon3a9ae3b10f03`)
- L314 _typedef_ `typedef SYMS_U8 SYMS_CoffComdatSelectType;`
- L316 _enumerator_ `SYMS_CoffComdatSelectType_NULL = 0` (scope `__anon3a9ae3b11003`)
- L318 _enumerator_ `SYMS_CoffComdatSelectType_NODUPLICATES = 1` (scope `__anon3a9ae3b11003`) — Only one symbol is allowed to be in global symbol table, otherwise multiply defintion error is thrown.
- L320 _enumerator_ `SYMS_CoffComdatSelectType_ANY = 2` (scope `__anon3a9ae3b11003`) — Select any symbol, even if there are multiple definitions. (we default to first declaration)
- L322 _enumerator_ `SYMS_CoffComdatSelectType_SAME_SIZE = 3` (scope `__anon3a9ae3b11003`) — Sections that symbols reference must match in size, otherwise multiply definition error is thrown.
- L324 _enumerator_ `SYMS_CoffComdatSelectType_EXACT_MATCH = 4` (scope `__anon3a9ae3b11003`) — Sections that symbols reference must have identical checksums, otherwise multiply defintion error is thrown.
- L326 _enumerator_ `SYMS_CoffComdatSelectType_ASSOCIATIVE = 5` (scope `__anon3a9ae3b11003`) — Symbols with associative type form a chain of sections are related to each other. (next link is indicated in SYMS_CoffSecDef in 'number')
- L328 _enumerator_ `SYMS_CoffComdatSelectType_LARGEST = 6` (scope `__anon3a9ae3b11003`) — Linker selects section with largest size.
- L329 _enumerator_ `SYMS_CoffComdatSelectType_COUNT = 7` (scope `__anon3a9ae3b11003`)
- L335 _prototype_ `SYMS_Arch syms_arch_from_coff_machine_type(SYMS_CoffMachineType v);`
- L336 _prototype_ `SYMS_U32 syms_coff_reloc_size_for_x64(SYMS_CoffRelocTypeX64 v);`
- L337 _prototype_ `SYMS_U32 syms_coff_reloc_size_for_x86(SYMS_CoffRelocTypeX86 v);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_cv.h` (Other)


#### struct `SYMS_CvGuid`  
`typedef struct SYMS_CvGuid`  
_L7-13_
- L8 _public member_ `SYMS_U32 data1;`
- L9 _public member_ `SYMS_U16 data2;`
- L10 _public member_ `SYMS_U16 data3;`
- L11 _public member_ `SYMS_U32 data4;`
- L12 _public member_ `SYMS_U32 data5;`

#### enum `(anonymous)`  
`enum`  
_L15-70_

#### enum `(anonymous)`  
`enum`  
_L72-81_

#### enum `(anonymous)`  
`enum`  
_L83-150_

#### enum `(anonymous)`  
`enum`  
_L152-167_

#### enum `(anonymous)`  
`enum`  
_L169-419_

#### enum `(anonymous)`  
`enum`  
_L421-1056_

#### enum `(anonymous)`  
`enum`  
_L1058-1065_

#### enum `(anonymous)`  
`enum`  
_L1067-1418_

#### struct `SYMS_CvAnnotation`  
`typedef struct SYMS_CvAnnotation`  
_L1419-1423_
- L1420 _public member_ `SYMS_U32 off;`
- L1421 _public member_ `SYMS_U16 seg;`
- L1422 _public member_ `SYMS_U16 count;`

#### struct `SYMS_CvRegister`  
`typedef struct SYMS_CvRegister`  
_L1424-1427_
- L1425 _public member_ `SYMS_CvTypeId type;`
- L1426 _public member_ `SYMS_U16 reg;`

#### struct `SYMS_CvBPRelSym32`  
`typedef struct SYMS_CvBPRelSym32`  
_L1428-1431_
- L1429 _public member_ `SYMS_U32 off;`
- L1430 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvVPathSym32`  
`typedef struct SYMS_CvVPathSym32`  
_L1432-1440_
- L1433 _public member_ `SYMS_CvTypeId root;`
- L1435 _public member_ `SYMS_CvTypeId path;` — "type index of the root path"
- L1437 _public member_ `SYMS_U32 off;` — "type nidex of the path record"
- L1439 _public member_ `SYMS_U16 seg;` — "offset of virtual function table"

#### struct `SYMS_CvOEM`  
`typedef struct SYMS_CvOEM`  
_L1441-1444_
- L1442 _public member_ `SYMS_CvGuid id;`
- L1443 _public member_ `SYMS_CvTypeId itype;` — data[] 4 byte aligned

#### struct `SYMS_CvSLink32`  
`typedef struct SYMS_CvSLink32`  
_L1445-1449_
- L1446 _public member_ `SYMS_U32 frame_size;`
- L1447 _public member_ `SYMS_U32 offset;`
- L1448 _public member_ `SYMS_U16 reg;`

#### enum `(anonymous)`  
`enum`  
_L1451-1466_

#### enum `(anonymous)`  
`enum`  
_L1468-1471_

#### struct `SYMS_CvReturn`  
`typedef struct SYMS_CvReturn`  
_L1472-1475_
- L1473 _public member_ `SYMS_CvGenericFlags flags;`
- L1474 _public member_ `SYMS_CvGenericStyle style;`

#### struct `SYMS_CvStartSearch`  
`typedef struct SYMS_CvStartSearch`  
_L1476-1480_
- L1477 _public member_ `SYMS_U32 start_symbol;`
- L1479 _public member_ `SYMS_U16 segment;` — offset where to start search (procedure)

#### enum `(anonymous)`  
`enum`  
_L1482-1501_

#### struct `SYMS_CvThread32`  
`typedef struct SYMS_CvThread32`  
_L1502-1507_
- L1503 _public member_ `SYMS_CvTypeId itype;`
- L1504 _public member_ `SYMS_U32 tls_off;`
- L1505 _public member_ `SYMS_U16 tls_seg;`

#### enum `(anonymous)`  
`enum`  
_L1509-1518_

#### struct `SYMS_CvCompile`  
`typedef struct SYMS_CvCompile`  
_L1525-1529_
- L1526 _public member_ `SYMS_U8 machine;`
- L1527 _public member_ `SYMS_CvCompileFlags flags;`

#### enum `(anonymous)`  
`enum`  
_L1532-1543_

#### struct `SYMS_CvCompile2`  
`typedef struct SYMS_CvCompile2`  
_L1545-1555_
- L1546 _public member_ `SYMS_CvCompile2Flags flags;`
- L1547 _public member_ `SYMS_CvArch machine;`
- L1548 _public member_ `SYMS_U16 ver_fe_major;`
- L1549 _public member_ `SYMS_U16 ver_fe_minor;`
- L1550 _public member_ `SYMS_U16 ver_fe_build;`
- L1551 _public member_ `SYMS_U16 ver_major;`
- L1552 _public member_ `SYMS_U16 ver_minor;`
- L1553 _public member_ `SYMS_U16 ver_build;`

#### enum `(anonymous)`  
`enum`  
_L1557-1571_

#### struct `SYMS_CvCompile3`  
`typedef struct SYMS_CvCompile3`  
_L1573-1585_
- L1574 _public member_ `SYMS_CvCompile3Flags flags;`
- L1575 _public member_ `SYMS_CvArch machine;`
- L1576 _public member_ `SYMS_U16 ver_fe_major;`
- L1577 _public member_ `SYMS_U16 ver_fe_minor;`
- L1578 _public member_ `SYMS_U16 ver_fe_build;`
- L1579 _public member_ `SYMS_U16 ver_feqfe;`
- L1580 _public member_ `SYMS_U16 ver_major;`
- L1581 _public member_ `SYMS_U16 ver_minor;`
- L1582 _public member_ `SYMS_U16 ver_build;`
- L1583 _public member_ `SYMS_U16 ver_qfe;`

#### struct `SYMS_CvObjname`  
`typedef struct SYMS_CvObjname`  
_L1586-1589_
- L1587 _public member_ `SYMS_U32 sig;`

#### struct `SYMS_CvRef2`  
`typedef struct SYMS_CvRef2`  
_L1591-1599_
- desc: struct SYMS_CvUNamespace{} skipped - no fixed width members
- L1592 _public member_ `SYMS_U32 sum_name;`
- L1594 _public member_ `SYMS_U32 sym_off;` — SUC of the name
- L1596 _public member_ `SYMS_CvModIndex imod;` — Offset of actual symbol in $$Symbols

#### enum `(anonymous)`  
`enum`  
_L1601-1604_

#### struct `SYMS_CvSepcode`  
`typedef struct SYMS_CvSepcode`  
_L1605-1615_
- L1606 _public member_ `SYMS_U32 parent;`
- L1607 _public member_ `SYMS_U32 end;`
- L1608 _public member_ `SYMS_U32 len;`
- L1609 _public member_ `SYMS_CvSepcodeFlags flags;`
- L1610 _public member_ `SYMS_U32 sec_off;`
- L1611 _public member_ `SYMS_U32 sec_parent_off;`
- L1613 _public member_ `SYMS_U16 sec;` — parent relative offset to enclosing scope.
- L1614 _public member_ `SYMS_U16 sec_parent;`

#### struct `SYMS_CvSlotsym32`  
`typedef struct SYMS_CvSlotsym32`  
_L1616-1619_
- L1617 _public member_ `SYMS_U32 slot_index;`
- L1618 _public member_ `SYMS_CvTypeId type;`

#### struct `SYMS_CvPogoInfo`  
`typedef struct SYMS_CvPogoInfo`  
_L1620-1625_
- L1621 _public member_ `SYMS_U32 invocations;`
- L1622 _public member_ `SYMS_U64 dynamic_inst_count;`
- L1623 _public member_ `SYMS_U32 static_inst_count;`
- L1624 _public member_ `SYMS_U32 post_inline_static_inst_count;`

#### struct `SYMS_CvManyreg`  
`typedef struct SYMS_CvManyreg`  
_L1626-1629_
- L1627 _public member_ `SYMS_CvTypeId type;`
- L1628 _public member_ `SYMS_U8 count;`

#### struct `SYMS_CvManyreg2`  
`typedef struct SYMS_CvManyreg2`  
_L1630-1633_
- L1631 _public member_ `SYMS_CvTypeId type;`
- L1632 _public member_ `SYMS_U16 count;`

#### enum `(anonymous)`  
`enum`  
_L1635-1641_

#### enum `(anonymous)`  
`enum`  
_L1643-1665_

#### struct `SYMS_CvFrameproc`  
`typedef struct SYMS_CvFrameproc`  
_L1668-1678_
- L1669 _public member_ `SYMS_U32 frame_size;`
- L1670 _public member_ `SYMS_U32 pad_size;`
- L1671 _public member_ `SYMS_U32 pad_off;`
- L1673 _public member_ `SYMS_U32 save_reg_size;` — frame pointer relative offset to where padding begins
- L1674 _public member_ `SYMS_U32 eh_off;`
- L1676 _public member_ `SYMS_CvSectionIndex eh_sec;` — offset of exception handler
- L1677 _public member_ `SYMS_CvFrameprocFlags flags;`

#### enum `(anonymous)`  
`enum`  
_L1680-1692_

#### struct `SYMS_CvThunk32`  
`typedef struct SYMS_CvThunk32`  
_L1693-1702_
- L1694 _public member_ `SYMS_U32 parent;`
- L1695 _public member_ `SYMS_U32 end;`
- L1696 _public member_ `SYMS_U32 next;`
- L1697 _public member_ `SYMS_U32 off;`
- L1698 _public member_ `SYMS_U16 sec;`
- L1699 _public member_ `SYMS_U16 len;`
- L1700 _public member_ `SYMS_CvThunkOrdinal ord;`

#### struct `SYMS_CvBlock32`  
`typedef struct SYMS_CvBlock32`  
_L1703-1710_
- L1704 _public member_ `SYMS_U32 par;`
- L1705 _public member_ `SYMS_U32 end;`
- L1706 _public member_ `SYMS_U32 len;`
- L1707 _public member_ `SYMS_U32 off;`
- L1708 _public member_ `SYMS_U16 sec;`

#### enum `(anonymous)`  
`enum`  
_L1712-1721_

#### struct `SYMS_CvLabel32`  
`typedef struct SYMS_CvLabel32`  
_L1722-1727_
- L1723 _public member_ `SYMS_U32 off;`
- L1724 _public member_ `SYMS_U16 sec;`
- L1725 _public member_ `SYMS_CvProcFlags flags;`

#### struct `SYMS_CvConstant`  
`typedef struct SYMS_CvConstant`  
_L1728-1732_
- L1729 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvUDT`  
`typedef struct SYMS_CvUDT`  
_L1733-1736_
- L1734 _public member_ `SYMS_CvTypeId itype;`

#### enum `(anonymous)`  
`enum`  
_L1738-1742_

#### struct `SYMS_CvTrampoline`  
`typedef struct SYMS_CvTrampoline`  
_L1743-1750_
- L1744 _public member_ `SYMS_CvTrampolineKind type;`
- L1745 _public member_ `SYMS_U16 thunk_size;`
- L1746 _public member_ `SYMS_U32 thunk_sec_off;`
- L1747 _public member_ `SYMS_U32 target_sec_off;`
- L1748 _public member_ `SYMS_CvSectionIndex thunk_sec;`
- L1749 _public member_ `SYMS_CvSectionIndex target_sec;`

#### struct `SYMS_CvSection`  
`typedef struct SYMS_CvSection`  
_L1751-1759_
- L1752 _public member_ `SYMS_U16 sec_index;`
- L1753 _public member_ `SYMS_U8 align;`
- L1754 _public member_ `SYMS_U8 pad;`
- L1755 _public member_ `SYMS_U32 rva;`
- L1756 _public member_ `SYMS_U32 size;`
- L1757 _public member_ `SYMS_U32 characteristics;`

#### struct `SYMS_CvCoffGroup`  
`typedef struct SYMS_CvCoffGroup`  
_L1760-1766_
- L1761 _public member_ `SYMS_U32 size;`
- L1762 _public member_ `SYMS_U32 characteristics;`
- L1763 _public member_ `SYMS_U32 off;`
- L1764 _public member_ `SYMS_U16 sec;`

#### enum `(anonymous)`  
`enum`  
_L1768-1775_

#### struct `SYMS_CvExport`  
`typedef struct SYMS_CvExport`  
_L1776-1780_
- L1777 _public member_ `SYMS_U16 ordinal;`
- L1778 _public member_ `SYMS_CvExportFlags flags;`

#### struct `SYMS_CvCallSiteInfo`  
`typedef struct SYMS_CvCallSiteInfo`  
_L1781-1789_
- L1782 _public member_ `SYMS_U32 off;`
- L1784 _public member_ `SYMS_U16 sec;` — call site section offset
- L1786 _public member_ `SYMS_U16 pad;` — call site section index
- L1788 _public member_ `SYMS_CvTypeId itype;` — padding

#### enum `(anonymous)`  
`enum`  
_L1791-1797_

#### struct `SYMS_CvFrameCookie`  
`typedef struct SYMS_CvFrameCookie`  
_L1798-1803_
- L1799 _public member_ `SYMS_U32 off;`
- L1800 _public member_ `SYMS_CvReg reg;`
- L1801 _public member_ `SYMS_CvFrameCookieKind kind;`
- L1802 _public member_ `SYMS_U8 flags;`

#### struct `SYMS_CvEnvblock`  
`typedef struct SYMS_CvEnvblock`  
_L1804-1807_
- L1805 _public member_ `SYMS_U8 flags;`

#### enum `(anonymous)`  
`enum`  
_L1809-1821_

#### struct `SYMS_CvLocal`  
`typedef struct SYMS_CvLocal`  
_L1822-1827_
- L1823 _public member_ `SYMS_CvTypeId itype;`
- L1824 _public member_ `SYMS_CvLocalFlags flags;`

#### struct `SYMS_CvLvarAddrRange`  
`typedef struct SYMS_CvLvarAddrRange`  
_L1828-1832_
- L1829 _public member_ `SYMS_U32 off;`
- L1830 _public member_ `SYMS_U16 sec;`
- L1831 _public member_ `SYMS_U16 len;`

#### struct `SYMS_CvLvarAddrGap`  
`typedef struct SYMS_CvLvarAddrGap`  
_L1833-1836_
- L1834 _public member_ `SYMS_U16 off;`
- L1835 _public member_ `SYMS_U16 len;`

#### enum `(anonymous)`  
`enum`  
_L1838-1840_

#### struct `SYMS_CvDefrange`  
`typedef struct SYMS_CvDefrange`  
_L1841-1845_
- L1842 _public member_ `SYMS_U32 program;`
- L1843 _public member_ `SYMS_CvLvarAddrRange range;`

#### struct `SYMS_CvDefrangeSubfield`  
`typedef struct SYMS_CvDefrangeSubfield`  
_L1846-1851_
- L1847 _public member_ `SYMS_U32 program;`
- L1848 _public member_ `SYMS_U32 off_in_parent;`
- L1849 _public member_ `SYMS_CvLvarAddrRange range;`

#### struct `SYMS_CvDefrangeRegister`  
`typedef struct SYMS_CvDefrangeRegister`  
_L1852-1857_
- L1853 _public member_ `SYMS_CvReg reg;`
- L1854 _public member_ `SYMS_CvRangeAttribs attribs;`
- L1855 _public member_ `SYMS_CvLvarAddrRange range;`

#### struct `SYMS_CvDefrangeFramepointerRel`  
`typedef struct SYMS_CvDefrangeFramepointerRel`  
_L1858-1862_
- L1859 _public member_ `SYMS_U32 off;`
- L1860 _public member_ `SYMS_CvLvarAddrRange range;`

#### struct `SYMS_CvDefrangeSubfieldRegister`  
`typedef struct SYMS_CvDefrangeSubfieldRegister`  
_L1863-1869_
- L1864 _public member_ `SYMS_CvReg reg;`
- L1865 _public member_ `SYMS_CvRangeAttribs attribs;`
- L1866 _public member_ `SYMS_U32 off_parent;`
- L1867 _public member_ `SYMS_CvLvarAddrRange range;`

#### struct `SYMS_CvDefrangeFramepointerRelFullScope`  
`typedef struct SYMS_CvDefrangeFramepointerRelFullScope`  
_L1870-1872_
- L1871 _public member_ `SYMS_U32 off;`

#### enum `(anonymous)`  
`enum`  
_L1874-1880_

#### struct `SYMS_CvDefrangeRegisterRel`  
`typedef struct SYMS_CvDefrangeRegisterRel`  
_L1882-1888_
- L1883 _public member_ `SYMS_CvReg reg;`
- L1884 _public member_ `SYMS_CvDefrangeRegisterRelFlags flags;`
- L1885 _public member_ `SYMS_U32 reg_off;`
- L1886 _public member_ `SYMS_CvLvarAddrRange range;`

#### struct `SYMS_CvData32`  
`typedef struct SYMS_CvData32`  
_L1889-1894_
- L1890 _public member_ `SYMS_CvTypeId itype;`
- L1891 _public member_ `SYMS_U32 sec_off;`
- L1892 _public member_ `SYMS_CvSectionIndex sec;`

#### enum `(anonymous)`  
`enum`  
_L1896-1901_

#### struct `SYMS_CvPubsym32`  
`typedef struct SYMS_CvPubsym32`  
_L1902-1908_
- L1903 _public member_ `SYMS_CvPubsymFlags flags;`
- L1904 _public member_ `SYMS_U32 off;`
- L1905 _public member_ `SYMS_U16 sec;`

#### struct `SYMS_CvProc32`  
`typedef struct SYMS_CvProc32`  
_L1911-1923_
- desc: struct SYMS_CvGProc16{} skipped - no fixed width members struct SYMS_CvGProc3216t{} skipped - no fixed width members
- L1912 _public member_ `SYMS_U32 parent;`
- L1913 _public member_ `SYMS_U32 end;`
- L1914 _public member_ `SYMS_U32 next;`
- L1915 _public member_ `SYMS_U32 len;`
- L1916 _public member_ `SYMS_U32 dbg_start;`
- L1917 _public member_ `SYMS_U32 dbg_end;`
- L1918 _public member_ `SYMS_CvTypeId itype;`
- L1919 _public member_ `SYMS_U32 off;`
- L1920 _public member_ `SYMS_U16 sec;`
- L1921 _public member_ `SYMS_CvProcFlags flags;`

#### struct `SYMS_CvRegrel32`  
`typedef struct SYMS_CvRegrel32`  
_L1924-1929_
- L1925 _public member_ `SYMS_U32 reg_off;`
- L1926 _public member_ `SYMS_CvTypeId itype;`
- L1927 _public member_ `SYMS_CvReg reg;`

#### struct `SYMS_CvBuildInfo`  
`typedef struct SYMS_CvBuildInfo`  
_L1930-1932_
- L1931 _public member_ `SYMS_CvItemId id;`

#### struct `SYMS_CvFunctionList`  
`typedef struct SYMS_CvFunctionList`  
_L1933-1938_
- L1934 _public member_ `SYMS_U32 count;`

#### enum `SYMS_CvBAOpcode`  
`typedef enum SYMS_CvBAOpcode`  
_L1939-1955_
- L1940 _public enumerator_ `SYMS_CvBAOpcode_Invalid`
- L1941 _public enumerator_ `SYMS_CvBAOpcode_CodeOffset`
- L1942 _public enumerator_ `SYMS_CvBAOpcode_ChangeCodeOffsetBase`
- L1943 _public enumerator_ `SYMS_CvBAOpcode_ChangeCodeOffset`
- L1944 _public enumerator_ `SYMS_CvBAOpcode_ChangeCodeLength`
- L1945 _public enumerator_ `SYMS_CvBAOpcode_ChangeFile`
- L1946 _public enumerator_ `SYMS_CvBAOpcode_ChangeLineOffset`
- L1947 _public enumerator_ `SYMS_CvBAOpcode_ChangeLineEndDelta`
- L1948 _public enumerator_ `SYMS_CvBAOpcode_ChangeRangeKind`
- L1949 _public enumerator_ `SYMS_CvBAOpcode_ChangeColumnStart`
- L1950 _public enumerator_ `SYMS_CvBAOpcode_ChangeColumnEndDelta`
- L1951 _public enumerator_ `SYMS_CvBAOpcode_ChangeCodeOffsetAndLineOffset`
- L1952 _public enumerator_ `SYMS_CvBAOpcode_ChangeCodeLengthAndCodeOffset`
- L1953 _public enumerator_ `SYMS_CvBAOpcode_ChangeColumnEnd`
- L1954 _public enumerator_ `SYMS_CvBAOpcode_COUNT = 14`

#### struct `SYMS_CvInlineSite`  
`typedef struct SYMS_CvInlineSite`  
_L1956-1961_
- L1957 _public member_ `SYMS_U32 parent_offset;`
- L1958 _public member_ `SYMS_U32 end_offset;`
- L1959 _public member_ `SYMS_CvItemId inlinee;`

#### struct `SYMS_CvInlineSite2`  
`typedef struct SYMS_CvInlineSite2`  
_L1962-1968_
- L1963 _public member_ `SYMS_U32 parent_offset;`
- L1964 _public member_ `SYMS_U32 end_offset;`
- L1965 _public member_ `SYMS_CvItemId inlinee;`
- L1966 _public member_ `SYMS_U32 invocations;`

#### struct `SYMS_CvInlinees`  
`typedef struct SYMS_CvInlinees`  
_L1970-1973_
- desc: struct SYMS_CvInlineSiteEnd{} skipped - no fixed width members
- L1971 _public member_ `SYMS_U32 count;`

#### struct `SYMS_CvFileStatic`  
`typedef struct SYMS_CvFileStatic`  
_L1974-1979_
- L1975 _public member_ `SYMS_CvTypeId itype;`
- L1976 _public member_ `SYMS_U32 mod_offset;`
- L1977 _public member_ `SYMS_CvLocalFlags flags;`

#### struct `SYMS_CvHeapAllocSite`  
`typedef struct SYMS_CvHeapAllocSite`  
_L1980-1988_
- L1981 _public member_ `SYMS_U32 off;`
- L1983 _public member_ `SYMS_U16 sec;` — call site offset
- L1985 _public member_ `SYMS_U16 call_inst_len;` — call site section
- L1987 _public member_ `SYMS_CvTypeId itype;` — length of heap allocation call instruction (in bytes)

#### struct `SYMS_CvLocalVarAttr`  
`typedef struct SYMS_CvLocalVarAttr`  
_L1989-1993_
- L1990 _public member_ `SYMS_U32 off;`
- L1991 _public member_ `SYMS_U16 seg;`
- L1992 _public member_ `SYMS_CvLocalFlags flags;`

#### struct `SYMS_CvFramerel`  
`typedef struct SYMS_CvFramerel`  
_L1994-1998_
- L1995 _public member_ `SYMS_U32 off;`
- L1996 _public member_ `SYMS_CvTypeId itype;`
- L1997 _public member_ `SYMS_CvLocalVarAttr attr;`

#### struct `SYMS_CvAttrReg`  
`typedef struct SYMS_CvAttrReg`  
_L1999-2003_
- L2000 _public member_ `SYMS_CvTypeId itype;`
- L2001 _public member_ `SYMS_CvLocalVarAttr attr;`
- L2002 _public member_ `SYMS_U16 reg;`

#### struct `SYMS_CvAttrRegrel`  
`typedef struct SYMS_CvAttrRegrel`  
_L2004-2009_
- L2005 _public member_ `SYMS_U32 off;`
- L2006 _public member_ `SYMS_CvTypeId itype;`
- L2007 _public member_ `SYMS_U16 reg;`
- L2008 _public member_ `SYMS_CvLocalVarAttr attr;`

#### struct `SYMS_CvAttrManyreg`  
`typedef struct SYMS_CvAttrManyreg`  
_L2010-2014_
- L2011 _public member_ `SYMS_CvTypeId itype;`
- L2012 _public member_ `SYMS_CvLocalVarAttr attr;`
- L2013 _public member_ `SYMS_U8 reg_count;`

#### enum `(anonymous)`  
`enum`  
_L2016-2024_

#### struct `SYMS_CvFastLink`  
`typedef struct SYMS_CvFastLink`  
_L2025-2028_
- L2026 _public member_ `SYMS_CvTypeId itype;`
- L2027 _public member_ `SYMS_CvFastLinkFlags flags;`

#### enum `(anonymous)`  
`enum`  
_L2030-2045_

#### struct `SYMS_CvArmSwitchTable`  
`typedef struct SYMS_CvArmSwitchTable`  
_L2046-2059_
- L2047 _public member_ `SYMS_U32 off_base;`
- L2049 _public member_ `SYMS_U16 sec_base;` — "Section-relative offset to the base for switch offsets"
- L2051 _public member_ `SYMS_CvArmSwitchType switch_type;` — "Section index of the base for switch offsets"
- L2052 _public member_ `SYMS_U32 off_branch;`
- L2054 _public member_ `SYMS_U32 off_table;` — "Section-relative offset to the table branch instruction"
- L2056 _public member_ `SYMS_U16 sec_branch;` — "Section-relative offset to the start of the table"
- L2057 _public member_ `SYMS_U16 sec_table;`
- L2058 _public member_ `SYMS_U32 entry_count;`

#### enum `(anonymous)`  
`enum`  
_L2061-2067_

#### struct `SYMS_CvRefMiniPdb`  
`typedef struct SYMS_CvRefMiniPdb`  
_L2068-2073_
- L2069 _public member_ `SYMS_U32 data;`
- L2071 _public member_ `SYMS_U16 imod;` — If UDT flag is set then this is SYMS_CvTypeId, otherwise coff section index
- L2072 _public member_ `SYMS_CvRefMiniPdbFlags flags;`

#### enum `(anonymous)`  
`enum`  
_L2075-2082_

#### struct `SYMS_CvModTypeRef`  
`typedef struct SYMS_CvModTypeRef`  
_L2083-2088_
- L2084 _public member_ `SYMS_CvModTypeRefFlags flags;`
- L2086 _public member_ `SYMS_U16 word0;` — "these two words contain SN or module index depending on above flags"
- L2087 _public member_ `SYMS_U16 word1;`

#### enum `(anonymous)`  
`enum`  
_L2090-2095_

#### enum `(anonymous)`  
`enum`  
_L2097-2099_

#### struct `SYMS_CvDiscarded`  
`typedef struct SYMS_CvDiscarded`  
_L2101-2106_
- L2102 _public member_ `SYMS_CvDiscardedFlags flags;`
- L2103 _public member_ `SYMS_U32 file_id;`
- L2105 _public member_ `SYMS_U32 file_ln;` — "First FILEID if line number info present"

#### enum `(anonymous)`  
`enum`  
_L2108-2313_

#### enum `(anonymous)`  
`enum`  
_L2315-2319_

#### enum `(anonymous)`  
`enum`  
_L2321-2327_

#### enum `(anonymous)`  
`enum`  
_L2329-2335_

#### enum `(anonymous)`  
`enum`  
_L2337-2352_

#### enum `(anonymous)`  
`enum`  
_L2356-2385_

#### enum `(anonymous)`  
`enum`  
_L2387-2402_

#### enum `(anonymous)`  
`enum`  
_L2404-2416_

#### enum `(anonymous)`  
`enum`  
_L2421-2440_

#### enum `(anonymous)`  
`enum`  
_L2442-2459_

#### enum `(anonymous)`  
`enum`  
_L2461-2470_

#### enum `(anonymous)`  
`enum`  
_L2472-2478_

#### enum `(anonymous)`  
`enum`  
_L2480-2488_

#### enum `(anonymous)`  
`enum`  
_L2492-2496_

#### enum `(anonymous)`  
`enum`  
_L2498-2502_

#### enum `(anonymous)`  
`enum`  
_L2504-2557_

#### struct `SYMS_CvLeafPreComp`  
`typedef struct SYMS_CvLeafPreComp`  
_L2558-2563_
- L2559 _public member_ `SYMS_U32 start_index;`
- L2560 _public member_ `SYMS_U32 count;`
- L2561 _public member_ `SYMS_U32 signature;`

#### struct `SYMS_CvLeafTypeServer`  
`typedef struct SYMS_CvLeafTypeServer`  
_L2564-2568_
- L2565 _public member_ `SYMS_U32 sig;`
- L2566 _public member_ `SYMS_U32 age;`

#### struct `SYMS_CvLeafTypeServer2`  
`typedef struct SYMS_CvLeafTypeServer2`  
_L2569-2573_
- L2570 _public member_ `SYMS_CvGuid sig70;`
- L2571 _public member_ `SYMS_U32 age;`

#### struct `SYMS_CvLeafBuildInfo`  
`typedef struct SYMS_CvLeafBuildInfo`  
_L2574-2577_
- L2575 _public member_ `SYMS_U16 count;`

#### struct `SYMS_CvLeafSkip_16t`  
`typedef struct SYMS_CvLeafSkip_16t`  
_L2578-2580_
- L2579 _public member_ `SYMS_U16 type;` — pad data

#### struct `SYMS_CvLeafSkip`  
`typedef struct SYMS_CvLeafSkip`  
_L2581-2583_
- L2582 _public member_ `SYMS_CvTypeIndex type;` — pad data

#### struct `SYMS_CvLeafVTShape`  
`typedef struct SYMS_CvLeafVTShape`  
_L2584-2586_
- L2585 _public member_ `SYMS_U16 count;`

#### struct `SYMS_CvLeafLabel`  
`typedef struct SYMS_CvLeafLabel`  
_L2587-2589_
- L2588 _public member_ `SYMS_CvLabelKind mode;`

#### struct `SYMS_CvLeafModifier`  
`typedef struct SYMS_CvLeafModifier`  
_L2590-2593_
- L2591 _public member_ `SYMS_CvTypeId itype;`
- L2592 _public member_ `SYMS_CvModifierFlags flags;`

#### struct `SYMS_CvLeafPointer`  
`typedef struct SYMS_CvLeafPointer`  
_L2594-2597_
- L2595 _public member_ `SYMS_CvTypeId itype;`
- L2596 _public member_ `SYMS_CvPointerAttribs attr;`

#### struct `SYMS_CvLeafProcedure`  
`typedef struct SYMS_CvLeafProcedure`  
_L2598-2604_
- L2599 _public member_ `SYMS_CvTypeId ret_itype;`
- L2600 _public member_ `SYMS_CvCallKind call_kind;`
- L2601 _public member_ `SYMS_CvFunctionAttribs funcattr;`
- L2602 _public member_ `SYMS_U16 arg_count;`
- L2603 _public member_ `SYMS_CvTypeId arg_itype;`

#### struct `SYMS_CvLeafMFunction`  
`typedef struct SYMS_CvLeafMFunction`  
_L2605-2614_
- L2606 _public member_ `SYMS_CvTypeId ret_itype;`
- L2607 _public member_ `SYMS_CvTypeId class_itype;`
- L2608 _public member_ `SYMS_CvTypeId this_itype;`
- L2609 _public member_ `SYMS_CvCallKind call_kind;`
- L2610 _public member_ `SYMS_CvFunctionAttribs funcattr;`
- L2611 _public member_ `SYMS_U16 arg_count;`
- L2612 _public member_ `SYMS_CvTypeId arg_itype;`
- L2613 _public member_ `SYMS_S32 thisadjust;`

#### struct `SYMS_CvLeafArgList`  
`typedef struct SYMS_CvLeafArgList`  
_L2615-2617_
- L2616 _public member_ `SYMS_U32 count;`

#### struct `SYMS_CvLeafBitField`  
`typedef struct SYMS_CvLeafBitField`  
_L2618-2622_
- L2619 _public member_ `SYMS_CvTypeId itype;`
- L2620 _public member_ `SYMS_U8 len;`
- L2621 _public member_ `SYMS_U8 pos;`

#### struct `SYMS_CvLeafIndex`  
`typedef struct SYMS_CvLeafIndex`  
_L2623-2626_
- L2624 _public member_ `SYMS_U16 pad;`
- L2625 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafArray`  
`typedef struct SYMS_CvLeafArray`  
_L2627-2630_
- L2628 _public member_ `SYMS_CvTypeId entry_itype;`
- L2629 _public member_ `SYMS_CvTypeId index_itype;`

#### struct `SYMS_CvLeafStruct`  
`typedef struct SYMS_CvLeafStruct`  
_L2631-2637_
- L2632 _public member_ `SYMS_U16 count;`
- L2633 _public member_ `SYMS_CvTypeProps props;`
- L2634 _public member_ `SYMS_CvTypeId field;`
- L2635 _public member_ `SYMS_CvTypeId derived;`
- L2636 _public member_ `SYMS_CvTypeId vshape;`

#### struct `SYMS_CvLeafUnion`  
`typedef struct SYMS_CvLeafUnion`  
_L2638-2642_
- L2639 _public member_ `SYMS_U16 count;`
- L2640 _public member_ `SYMS_CvTypeProps props;`
- L2641 _public member_ `SYMS_CvTypeId field;`

#### struct `SYMS_CvLeafEnum`  
`typedef struct SYMS_CvLeafEnum`  
_L2643-2648_
- L2644 _public member_ `SYMS_U16 count;`
- L2645 _public member_ `SYMS_CvTypeProps props;`
- L2646 _public member_ `SYMS_CvTypeId itype;`
- L2647 _public member_ `SYMS_CvTypeId field;`

#### struct `SYMS_CvLeafAlias`  
`typedef struct SYMS_CvLeafAlias`  
_L2649-2651_
- L2650 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafMember`  
`typedef struct SYMS_CvLeafMember`  
_L2652-2657_
- L2653 _public member_ `SYMS_CvFieldAttribs attribs;`
- L2654 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafStMember`  
`typedef struct SYMS_CvLeafStMember`  
_L2658-2662_
- L2659 _public member_ `SYMS_CvFieldAttribs attribs;`
- L2660 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafMethodListMember`  
`typedef struct SYMS_CvLeafMethodListMember`  
_L2663-2667_
- L2664 _public member_ `SYMS_CvFieldAttribs attribs;`
- L2665 _public member_ `SYMS_U16 pad;`
- L2666 _public member_ `SYMS_CvTypeId index;`

#### struct `SYMS_CvLeafMethod`  
`typedef struct SYMS_CvLeafMethod`  
_L2668-2671_
- L2669 _public member_ `SYMS_U16 count;`
- L2670 _public member_ `SYMS_CvTypeId itype_list;`

#### struct `SYMS_CvLeafOneMethod`  
`typedef struct SYMS_CvLeafOneMethod`  
_L2672-2675_
- L2673 _public member_ `SYMS_CvFieldAttribs attribs;`
- L2674 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafEnumerate`  
`typedef struct SYMS_CvLeafEnumerate`  
_L2676-2678_
- L2677 _public member_ `SYMS_CvFieldAttribs attribs;`

#### struct `SYMS_CvLeafNestType`  
`typedef struct SYMS_CvLeafNestType`  
_L2679-2682_
- L2680 _public member_ `SYMS_U16 pad;`
- L2681 _public member_ `SYMS_CvTypeId index;`

#### struct `SYMS_CvLeafNestTypeEx`  
`typedef struct SYMS_CvLeafNestTypeEx`  
_L2683-2686_
- L2684 _public member_ `SYMS_CvFieldAttribs attribs;`
- L2685 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafBClass`  
`typedef struct SYMS_CvLeafBClass`  
_L2687-2690_
- L2688 _public member_ `SYMS_CvFieldAttribs attribs;`
- L2689 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafVBClass`  
`typedef struct SYMS_CvLeafVBClass`  
_L2691-2695_
- L2692 _public member_ `SYMS_CvFieldAttribs attribs;`
- L2693 _public member_ `SYMS_CvTypeId itype;`
- L2694 _public member_ `SYMS_CvTypeId vbptr_itype;`

#### struct `SYMS_CvLeafVFuncTab`  
`typedef struct SYMS_CvLeafVFuncTab`  
_L2696-2699_
- L2697 _public member_ `SYMS_U16 pad;`
- L2698 _public member_ `SYMS_CvTypeId itype;`

#### struct `SYMS_CvLeafVFuncOff`  
`typedef struct SYMS_CvLeafVFuncOff`  
_L2700-2704_
- L2701 _public member_ `SYMS_U16 pad;`
- L2702 _public member_ `SYMS_CvTypeId itype;`
- L2703 _public member_ `SYMS_U32 off;`

#### struct `SYMS_CvLeafVFTable`  
`typedef struct SYMS_CvLeafVFTable`  
_L2705-2710_
- L2706 _public member_ `SYMS_CvTypeId owner_itype;`
- L2707 _public member_ `SYMS_CvTypeId base_table_itype;`
- L2708 _public member_ `SYMS_U32 offset_in_object_layout;`
- L2709 _public member_ `SYMS_U32 names_len;`

#### struct `SYMS_CvLeafVFPath`  
`typedef struct SYMS_CvLeafVFPath`  
_L2711-2713_
- L2712 _public member_ `SYMS_U32 count;`

#### struct `SYMS_CvLeafFuncId`  
`typedef struct SYMS_CvLeafFuncId`  
_L2714-2718_
- L2715 _public member_ `SYMS_CvItemId scope_id;`
- L2717 _public member_ `SYMS_CvTypeId itype;` — parent scope of the ID, 0 if global

#### struct `SYMS_CvLeafMFuncId`  
`typedef struct SYMS_CvLeafMFuncId`  
_L2719-2722_
- L2720 _public member_ `SYMS_CvItemId parent_itype;`
- L2721 _public member_ `SYMS_CvItemId itype;`

#### struct `SYMS_CvLeafStringId`  
`typedef struct SYMS_CvLeafStringId`  
_L2723-2727_
- L2725 _public member_ `SYMS_CvItemId id;` — TODO(allen): Whose "id" is this??

#### struct `SYMS_CvLeafUDTSrcLine`  
`typedef struct SYMS_CvLeafUDTSrcLine`  
_L2728-2734_
- L2729 _public member_ `SYMS_CvTypeId udt_itype;`
- L2731 _public member_ `SYMS_CvItemId src;` — itype which this source line references.
- L2733 _public member_ `SYMS_U32 ln;` — cvinfo.h: "index to LF_STRING_ID record where file name is saved"

#### struct `SYMS_CvLeafModSrcLine`  
`typedef struct SYMS_CvLeafModSrcLine`  
_L2735-2740_
- L2736 _public member_ `SYMS_CvTypeId udt_itype;`
- L2737 _public member_ `SYMS_CvItemId src;`
- L2738 _public member_ `SYMS_U32 ln;`
- L2739 _public member_ `SYMS_U16 comp_unit;`

#### struct `SYMS_CvLeafClassPtr`  
`typedef struct SYMS_CvLeafClassPtr`  
_L2741-2748_
- L2742 _public member_ `SYMS_CvTypeProps props;`
- L2743 _public member_ `SYMS_U16 padding;`
- L2744 _public member_ `SYMS_CvTypeId field;`
- L2745 _public member_ `SYMS_U32 unknown2;`
- L2746 _public member_ `SYMS_U32 unknown3;`
- L2747 _public member_ `SYMS_U16 unknown4;`

#### enum `(anonymous)`  
`enum`  
_L2750-2767_

#### struct `SYMS_CvSubSectionHeader`  
`typedef struct SYMS_CvSubSectionHeader`  
_L2768-2771_
- L2769 _public member_ `SYMS_CvSubSectionKind kind;`
- L2770 _public member_ `SYMS_U32 size;`

#### enum `(anonymous)`  
`enum`  
_L2773-2779_

#### enum `SYMS_CvInlineeSourceLineSig`  
`typedef enum SYMS_CvInlineeSourceLineSig`  
_L2780-2785_
- L2781 _public enumerator_ `SYMS_CvInlineeSourceLineSig_REGULAR = 0`
- L2783 _public enumerator_ `SYMS_CvInlineeSourceLineSig_EXTENDED = 1` — SYMS_CvInlineeSourceLine
- L2784 _public enumerator_ `SYMS_CvInlineeSourceLineSig_COUNT = 2`

#### struct `SYMS_CvInlineeSourceLine`  
`typedef struct SYMS_CvInlineeSourceLine`  
_L2786-2792_
- L2787 _public member_ `SYMS_CvItemId inlinee;`
- L2789 _public member_ `SYMS_U32 file_id;` — function id
- L2791 _public member_ `SYMS_U32 base_line_number;` — offset into FILECHKSMS subsection

#### struct `SYMS_CvInlineeSourceLineEx`  
`typedef struct SYMS_CvInlineeSourceLineEx`  
_L2793-2799_
- L2794 _public member_ `SYMS_CvItemId inlinee;`
- L2795 _public member_ `SYMS_CvItemId file_id;`
- L2796 _public member_ `SYMS_U32 base_line_number;`
- L2797 _public member_ `SYMS_U32 extra_file_count;`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_CV_H`
- L13 _typedef_ `} SYMS_CvGuid;`
- L14 _typedef_ `typedef SYMS_U8 SYMS_CvBasicType;`
- L16 _enumerator_ `SYMS_CvBasicType_NOTYPE = 0x00` (scope `__anon43fde12c0103`)
- L17 _enumerator_ `SYMS_CvBasicType_ABS = 0x01` (scope `__anon43fde12c0103`)
- L18 _enumerator_ `SYMS_CvBasicType_SEGMENT = 0x02` (scope `__anon43fde12c0103`)
- L19 _enumerator_ `SYMS_CvBasicType_VOID = 0x03` (scope `__anon43fde12c0103`)
- L20 _enumerator_ `SYMS_CvBasicType_CURRENCY = 0x04` (scope `__anon43fde12c0103`)
- L21 _enumerator_ `SYMS_CvBasicType_NBASICSTR = 0x05` (scope `__anon43fde12c0103`)
- L22 _enumerator_ `SYMS_CvBasicType_FBASICSTR = 0x06` (scope `__anon43fde12c0103`)
- L23 _enumerator_ `SYMS_CvBasicType_NOTTRANS = 0x07` (scope `__anon43fde12c0103`)
- L24 _enumerator_ `SYMS_CvBasicType_HRESULT = 0x08` (scope `__anon43fde12c0103`)
- L25 _enumerator_ `SYMS_CvBasicType_CHAR = 0x10` (scope `__anon43fde12c0103`)
- L26 _enumerator_ `SYMS_CvBasicType_SHORT = 0x11` (scope `__anon43fde12c0103`)
- L27 _enumerator_ `SYMS_CvBasicType_LONG = 0x12` (scope `__anon43fde12c0103`)
- L28 _enumerator_ `SYMS_CvBasicType_QUAD = 0x13` (scope `__anon43fde12c0103`)
- L29 _enumerator_ `SYMS_CvBasicType_OCT = 0x14` (scope `__anon43fde12c0103`)
- L30 _enumerator_ `SYMS_CvBasicType_UCHAR = 0x20` (scope `__anon43fde12c0103`)
- L31 _enumerator_ `SYMS_CvBasicType_USHORT = 0x21` (scope `__anon43fde12c0103`)
- L32 _enumerator_ `SYMS_CvBasicType_ULONG = 0x22` (scope `__anon43fde12c0103`)
- L33 _enumerator_ `SYMS_CvBasicType_UQUAD = 0x23` (scope `__anon43fde12c0103`)
- L34 _enumerator_ `SYMS_CvBasicType_UOCT = 0x24` (scope `__anon43fde12c0103`)
- L35 _enumerator_ `SYMS_CvBasicType_BOOL8 = 0x30` (scope `__anon43fde12c0103`)
- L36 _enumerator_ `SYMS_CvBasicType_BOOL16 = 0x31` (scope `__anon43fde12c0103`)
- L37 _enumerator_ `SYMS_CvBasicType_BOOL32 = 0x32` (scope `__anon43fde12c0103`)
- L38 _enumerator_ `SYMS_CvBasicType_BOOL64 = 0x33` (scope `__anon43fde12c0103`)
- L39 _enumerator_ `SYMS_CvBasicType_FLOAT32 = 0x40` (scope `__anon43fde12c0103`)
- L40 _enumerator_ `SYMS_CvBasicType_FLOAT64 = 0x41` (scope `__anon43fde12c0103`)
- L41 _enumerator_ `SYMS_CvBasicType_FLOAT80 = 0x42` (scope `__anon43fde12c0103`)
- L42 _enumerator_ `SYMS_CvBasicType_FLOAT128 = 0x43` (scope `__anon43fde12c0103`)
- L43 _enumerator_ `SYMS_CvBasicType_FLOAT48 = 0x44` (scope `__anon43fde12c0103`)
- L44 _enumerator_ `SYMS_CvBasicType_FLOAT32PP = 0x45` (scope `__anon43fde12c0103`)
- L45 _enumerator_ `SYMS_CvBasicType_FLOAT16 = 0x46` (scope `__anon43fde12c0103`)
- L46 _enumerator_ `SYMS_CvBasicType_COMPLEX32 = 0x50` (scope `__anon43fde12c0103`)
- L47 _enumerator_ `SYMS_CvBasicType_COMPLEX64 = 0x51` (scope `__anon43fde12c0103`)
- L48 _enumerator_ `SYMS_CvBasicType_COMPLEX80 = 0x52` (scope `__anon43fde12c0103`)
- L49 _enumerator_ `SYMS_CvBasicType_COMPLEX128 = 0x53` (scope `__anon43fde12c0103`)
- L50 _enumerator_ `SYMS_CvBasicType_BIT = 0x60` (scope `__anon43fde12c0103`)
- L51 _enumerator_ `SYMS_CvBasicType_PASCHAR = 0x61` (scope `__anon43fde12c0103`)
- L52 _enumerator_ `SYMS_CvBasicType_BOOL32FF = 0x62` (scope `__anon43fde12c0103`)
- L53 _enumerator_ `SYMS_CvBasicType_INT8 = 0x68` (scope `__anon43fde12c0103`)
- L54 _enumerator_ `SYMS_CvBasicType_UINT8 = 0x69` (scope `__anon43fde12c0103`)
- L55 _enumerator_ `SYMS_CvBasicType_RCHAR = 0x70` (scope `__anon43fde12c0103`)
- L56 _enumerator_ `SYMS_CvBasicType_WCHAR = 0x71` (scope `__anon43fde12c0103`)
- L57 _enumerator_ `SYMS_CvBasicType_INT16 = 0x72` (scope `__anon43fde12c0103`)
- L58 _enumerator_ `SYMS_CvBasicType_UINT16 = 0x73` (scope `__anon43fde12c0103`)
- L59 _enumerator_ `SYMS_CvBasicType_INT32 = 0x74` (scope `__anon43fde12c0103`)
- L60 _enumerator_ `SYMS_CvBasicType_UINT32 = 0x75` (scope `__anon43fde12c0103`)
- L61 _enumerator_ `SYMS_CvBasicType_INT64 = 0x76` (scope `__anon43fde12c0103`)
- L62 _enumerator_ `SYMS_CvBasicType_UINT64 = 0x77` (scope `__anon43fde12c0103`)
- L63 _enumerator_ `SYMS_CvBasicType_INT128 = 0x78` (scope `__anon43fde12c0103`)
- L64 _enumerator_ `SYMS_CvBasicType_UINT128 = 0x79` (scope `__anon43fde12c0103`)
- L65 _enumerator_ `SYMS_CvBasicType_CHAR16 = 0x7a` (scope `__anon43fde12c0103`)
- L66 _enumerator_ `SYMS_CvBasicType_CHAR32 = 0x7b` (scope `__anon43fde12c0103`)
- L67 _enumerator_ `SYMS_CvBasicType_CHAR8 = 0x7c` (scope `__anon43fde12c0103`)
- L68 _enumerator_ `SYMS_CvBasicType_PTR = 0xf0` (scope `__anon43fde12c0103`)
- L69 _enumerator_ `SYMS_CvBasicType_COUNT = 53` (scope `__anon43fde12c0103`)
- L71 _typedef_ `typedef SYMS_U8 SYMS_CvBasicPointerKind;`
- L73 _enumerator_ `SYMS_CvBasicPointerKind_VALUE = 0x0` (scope `__anon43fde12c0203`)
- L74 _enumerator_ `SYMS_CvBasicPointerKind_16BIT = 0x1` (scope `__anon43fde12c0203`)
- L75 _enumerator_ `SYMS_CvBasicPointerKind_FAR_16BIT = 0x2` (scope `__anon43fde12c0203`)
- L76 _enumerator_ `SYMS_CvBasicPointerKind_HUGE_16BIT = 0x3` (scope `__anon43fde12c0203`)
- L77 _enumerator_ `SYMS_CvBasicPointerKind_32BIT = 0x4` (scope `__anon43fde12c0203`)
- L78 _enumerator_ `SYMS_CvBasicPointerKind_16_32BIT = 0x5` (scope `__anon43fde12c0203`)
- L79 _enumerator_ `SYMS_CvBasicPointerKind_64BIT = 0x6` (scope `__anon43fde12c0203`)
- L80 _enumerator_ `SYMS_CvBasicPointerKind_COUNT = 7` (scope `__anon43fde12c0203`)
- L82 _typedef_ `typedef SYMS_U16 SYMS_CvArch;`
- L84 _enumerator_ `SYMS_CvArch_8080 = 0x00` (scope `__anon43fde12c0303`)
- L85 _enumerator_ `SYMS_CvArch_8086 = 0x01` (scope `__anon43fde12c0303`)
- L86 _enumerator_ `SYMS_CvArch_80286 = 0x02` (scope `__anon43fde12c0303`)
- L87 _enumerator_ `SYMS_CvArch_80386 = 0x03` (scope `__anon43fde12c0303`)
- L88 _enumerator_ `SYMS_CvArch_80486 = 0x04` (scope `__anon43fde12c0303`)
- L89 _enumerator_ `SYMS_CvArch_PENTIUM = 0x05` (scope `__anon43fde12c0303`)
- L90 _enumerator_ `SYMS_CvArch_PENTIUMII = 0x06` (scope `__anon43fde12c0303`)
- L91 _enumerator_ `SYMS_CvArch_PENTIUMPRO = SYMS_CvArch_PENTIUMII` (scope `__anon43fde12c0303`)
- L92 _enumerator_ `SYMS_CvArch_PENTIUMIII = 0x07` (scope `__anon43fde12c0303`)
- L93 _enumerator_ `SYMS_CvArch_MIPS = 0x10` (scope `__anon43fde12c0303`)
- L94 _enumerator_ `SYMS_CvArch_MIPSR4000 = SYMS_CvArch_MIPS` (scope `__anon43fde12c0303`)
- L95 _enumerator_ `SYMS_CvArch_MIPS16 = 0x11` (scope `__anon43fde12c0303`)
- L96 _enumerator_ `SYMS_CvArch_MIPS32 = 0x12` (scope `__anon43fde12c0303`)
- L97 _enumerator_ `SYMS_CvArch_MIPS64 = 0x13` (scope `__anon43fde12c0303`)
- L98 _enumerator_ `SYMS_CvArch_MIPSI = 0x14` (scope `__anon43fde12c0303`)
- L99 _enumerator_ `SYMS_CvArch_MIPSII = 0x15` (scope `__anon43fde12c0303`)
- L100 _enumerator_ `SYMS_CvArch_MIPSIII = 0x16` (scope `__anon43fde12c0303`)
- L101 _enumerator_ `SYMS_CvArch_MIPSIV = 0x17` (scope `__anon43fde12c0303`)
- L102 _enumerator_ `SYMS_CvArch_MIPSV = 0x18` (scope `__anon43fde12c0303`)
- L103 _enumerator_ `SYMS_CvArch_M68000 = 0x20` (scope `__anon43fde12c0303`)
- L104 _enumerator_ `SYMS_CvArch_M68010 = 0x21` (scope `__anon43fde12c0303`)
- L105 _enumerator_ `SYMS_CvArch_M68020 = 0x22` (scope `__anon43fde12c0303`)
- L106 _enumerator_ `SYMS_CvArch_M68030 = 0x23` (scope `__anon43fde12c0303`)
- L107 _enumerator_ `SYMS_CvArch_M68040 = 0x24` (scope `__anon43fde12c0303`)
- L108 _enumerator_ `SYMS_CvArch_ALPHA = 0x30` (scope `__anon43fde12c0303`)
- L109 _enumerator_ `SYMS_CvArch_ALPHA_21064 = SYMS_CvArch_ALPHA` (scope `__anon43fde12c0303`)
- L110 _enumerator_ `SYMS_CvArch_ALPHA_21164 = 0x31` (scope `__anon43fde12c0303`)
- L111 _enumerator_ `SYMS_CvArch_ALPHA_21164A = 0x32` (scope `__anon43fde12c0303`)
- L112 _enumerator_ `SYMS_CvArch_ALPHA_21264 = 0x33` (scope `__anon43fde12c0303`)
- L113 _enumerator_ `SYMS_CvArch_ALPHA_21364 = 0x34` (scope `__anon43fde12c0303`)
- L114 _enumerator_ `SYMS_CvArch_PPC601 = 0x40` (scope `__anon43fde12c0303`)
- L115 _enumerator_ `SYMS_CvArch_PPC603 = 0x41` (scope `__anon43fde12c0303`)
- L116 _enumerator_ `SYMS_CvArch_PPC604 = 0x42` (scope `__anon43fde12c0303`)
- L117 _enumerator_ `SYMS_CvArch_PPC620 = 0x43` (scope `__anon43fde12c0303`)
- L118 _enumerator_ `SYMS_CvArch_PPCFP = 0x44` (scope `__anon43fde12c0303`)
- L119 _enumerator_ `SYMS_CvArch_PPCBE = 0x45` (scope `__anon43fde12c0303`)
- L120 _enumerator_ `SYMS_CvArch_SH3 = 0x50` (scope `__anon43fde12c0303`)
- L121 _enumerator_ `SYMS_CvArch_SH3E = 0x51` (scope `__anon43fde12c0303`)
- L122 _enumerator_ `SYMS_CvArch_SH3DSP = 0x52` (scope `__anon43fde12c0303`)
- L123 _enumerator_ `SYMS_CvArch_SH4 = 0x53` (scope `__anon43fde12c0303`)
- L124 _enumerator_ `SYMS_CvArch_SHMEDIA = 0x54` (scope `__anon43fde12c0303`)
- L125 _enumerator_ `SYMS_CvArch_ARM3 = 0x60` (scope `__anon43fde12c0303`)
- L126 _enumerator_ `SYMS_CvArch_ARM4 = 0x61` (scope `__anon43fde12c0303`)
- L127 _enumerator_ `SYMS_CvArch_ARM4T = 0x62` (scope `__anon43fde12c0303`)
- L128 _enumerator_ `SYMS_CvArch_ARM5 = 0x63` (scope `__anon43fde12c0303`)
- L129 _enumerator_ `SYMS_CvArch_ARM5T = 0x64` (scope `__anon43fde12c0303`)
- L130 _enumerator_ `SYMS_CvArch_ARM6 = 0x65` (scope `__anon43fde12c0303`)
- L131 _enumerator_ `SYMS_CvArch_ARM_XMAC = 0x66` (scope `__anon43fde12c0303`)
- L132 _enumerator_ `SYMS_CvArch_ARM_WMMX = 0x67` (scope `__anon43fde12c0303`)
- L133 _enumerator_ `SYMS_CvArch_ARM7 = 0x68` (scope `__anon43fde12c0303`)
- L134 _enumerator_ `SYMS_CvArch_OMNI = 0x70` (scope `__anon43fde12c0303`)
- L135 _enumerator_ `SYMS_CvArch_IA64 = 0x80` (scope `__anon43fde12c0303`)
- L136 _enumerator_ `SYMS_CvArch_IA64_1 = 0x80` (scope `__anon43fde12c0303`)
- L137 _enumerator_ `SYMS_CvArch_IA64_2 = 0x81` (scope `__anon43fde12c0303`)
- L138 _enumerator_ `SYMS_CvArch_CEE = 0x90` (scope `__anon43fde12c0303`)
- L139 _enumerator_ `SYMS_CvArch_AM33 = 0xA0` (scope `__anon43fde12c0303`)
- L140 _enumerator_ `SYMS_CvArch_M32R = 0xB0` (scope `__anon43fde12c0303`)
- L141 _enumerator_ `SYMS_CvArch_TRICORE = 0xC0` (scope `__anon43fde12c0303`)
- L142 _enumerator_ `SYMS_CvArch_X64 = 0xD0` (scope `__anon43fde12c0303`)
- L143 _enumerator_ `SYMS_CvArch_AMD64 = SYMS_CvArch_X64` (scope `__anon43fde12c0303`)
- L144 _enumerator_ `SYMS_CvArch_EBC = 0xE0` (scope `__anon43fde12c0303`)
- L145 _enumerator_ `SYMS_CvArch_THUMB = 0xF0` (scope `__anon43fde12c0303`)
- L146 _enumerator_ `SYMS_CvArch_ARMNT = 0xF4` (scope `__anon43fde12c0303`)
- L147 _enumerator_ `SYMS_CvArch_ARM64 = 0xF6` (scope `__anon43fde12c0303`)
- L148 _enumerator_ `SYMS_CvArch_D3D11_SHADER = 0x100` (scope `__anon43fde12c0303`)
- L149 _enumerator_ `SYMS_CvArch_COUNT = 65` (scope `__anon43fde12c0303`)
- L151 _typedef_ `typedef SYMS_U16 SYMS_CvAllReg;`
- L153 _enumerator_ `SYMS_CvAllReg_ERR = 30000` (scope `__anon43fde12c0403`)
- L154 _enumerator_ `SYMS_CvAllReg_TEB = 30001` (scope `__anon43fde12c0403`)
- L155 _enumerator_ `SYMS_CvAllReg_TIMER = 30002` (scope `__anon43fde12c0403`)
- L156 _enumerator_ `SYMS_CvAllReg_EFAD1 = 30003` (scope `__anon43fde12c0403`)
- L157 _enumerator_ `SYMS_CvAllReg_EFAD2 = 30004` (scope `__anon43fde12c0403`)
- L158 _enumerator_ `SYMS_CvAllReg_EFAD3 = 30005` (scope `__anon43fde12c0403`)
- L159 _enumerator_ `SYMS_CvAllReg_VFRAME = 30006` (scope `__anon43fde12c0403`)
- L160 _enumerator_ `SYMS_CvAllReg_HANDLE = 30007` (scope `__anon43fde12c0403`)
- L161 _enumerator_ `SYMS_CvAllReg_PARAMS = 30008` (scope `__anon43fde12c0403`)
- L162 _enumerator_ `SYMS_CvAllReg_LOCALS = 30009` (scope `__anon43fde12c0403`)
- L163 _enumerator_ `SYMS_CvAllReg_TID = 30010` (scope `__anon43fde12c0403`)
- L164 _enumerator_ `SYMS_CvAllReg_ENV = 30011` (scope `__anon43fde12c0403`)
- L165 _enumerator_ `SYMS_CvAllReg_CMDLN = 30012` (scope `__anon43fde12c0403`)
- L166 _enumerator_ `SYMS_CvAllReg_COUNT = 13` (scope `__anon43fde12c0403`)
- L168 _typedef_ `typedef SYMS_U16 SYMS_CvRegx86;`
- L171 _enumerator_ `SYMS_CvRegx86_NONE = 0` (scope `__anon43fde12c0503`) — CODE REG-ID BYTE-OFFSET BYTE-SIZE
- L172 _enumerator_ `SYMS_CvRegx86_AL = 1` (scope `__anon43fde12c0503`)
- L173 _enumerator_ `SYMS_CvRegx86_CL = 2` (scope `__anon43fde12c0503`)
- L174 _enumerator_ `SYMS_CvRegx86_DL = 3` (scope `__anon43fde12c0503`)
- L175 _enumerator_ `SYMS_CvRegx86_BL = 4` (scope `__anon43fde12c0503`)
- L176 _enumerator_ `SYMS_CvRegx86_AH = 5` (scope `__anon43fde12c0503`)
- L177 _enumerator_ `SYMS_CvRegx86_CH = 6` (scope `__anon43fde12c0503`)
- L178 _enumerator_ `SYMS_CvRegx86_DH = 7` (scope `__anon43fde12c0503`)
- L179 _enumerator_ `SYMS_CvRegx86_BH = 8` (scope `__anon43fde12c0503`)
- L180 _enumerator_ `SYMS_CvRegx86_AX = 9` (scope `__anon43fde12c0503`)
- L181 _enumerator_ `SYMS_CvRegx86_CX = 10` (scope `__anon43fde12c0503`)
- L182 _enumerator_ `SYMS_CvRegx86_DX = 11` (scope `__anon43fde12c0503`)
- L183 _enumerator_ `SYMS_CvRegx86_BX = 12` (scope `__anon43fde12c0503`)
- L184 _enumerator_ `SYMS_CvRegx86_SP = 13` (scope `__anon43fde12c0503`)
- L185 _enumerator_ `SYMS_CvRegx86_BP = 14` (scope `__anon43fde12c0503`)
- L186 _enumerator_ `SYMS_CvRegx86_SI = 15` (scope `__anon43fde12c0503`)
- L187 _enumerator_ `SYMS_CvRegx86_DI = 16` (scope `__anon43fde12c0503`)
- L188 _enumerator_ `SYMS_CvRegx86_EAX = 17` (scope `__anon43fde12c0503`)
- L189 _enumerator_ `SYMS_CvRegx86_ECX = 18` (scope `__anon43fde12c0503`)
- L190 _enumerator_ `SYMS_CvRegx86_EDX = 19` (scope `__anon43fde12c0503`)
- L191 _enumerator_ `SYMS_CvRegx86_EBX = 20` (scope `__anon43fde12c0503`)
- L192 _enumerator_ `SYMS_CvRegx86_ESP = 21` (scope `__anon43fde12c0503`)
- L193 _enumerator_ `SYMS_CvRegx86_EBP = 22` (scope `__anon43fde12c0503`)
- L194 _enumerator_ `SYMS_CvRegx86_ESI = 23` (scope `__anon43fde12c0503`)
- L195 _enumerator_ `SYMS_CvRegx86_EDI = 24` (scope `__anon43fde12c0503`)
- L196 _enumerator_ `SYMS_CvRegx86_ES = 25` (scope `__anon43fde12c0503`)
- L197 _enumerator_ `SYMS_CvRegx86_CS = 26` (scope `__anon43fde12c0503`)
- L198 _enumerator_ `SYMS_CvRegx86_SS = 27` (scope `__anon43fde12c0503`)
- L199 _enumerator_ `SYMS_CvRegx86_DS = 28` (scope `__anon43fde12c0503`)
- L200 _enumerator_ `SYMS_CvRegx86_FS = 29` (scope `__anon43fde12c0503`)
- L201 _enumerator_ `SYMS_CvRegx86_GS = 30` (scope `__anon43fde12c0503`)
- L202 _enumerator_ `SYMS_CvRegx86_IP = 31` (scope `__anon43fde12c0503`)
- L203 _enumerator_ `SYMS_CvRegx86_FLAGS = 32` (scope `__anon43fde12c0503`)
- L204 _enumerator_ `SYMS_CvRegx86_EIP = 33` (scope `__anon43fde12c0503`)
- L205 _enumerator_ `SYMS_CvRegx86_EFLAGS = 34` (scope `__anon43fde12c0503`)
- L206 _enumerator_ `SYMS_CvRegx86_MM0 = 146` (scope `__anon43fde12c0503`)
- L207 _enumerator_ `SYMS_CvRegx86_MM1 = 147` (scope `__anon43fde12c0503`)
- L208 _enumerator_ `SYMS_CvRegx86_MM2 = 148` (scope `__anon43fde12c0503`)
- L209 _enumerator_ `SYMS_CvRegx86_MM3 = 149` (scope `__anon43fde12c0503`)
- L210 _enumerator_ `SYMS_CvRegx86_MM4 = 150` (scope `__anon43fde12c0503`)
- L211 _enumerator_ `SYMS_CvRegx86_MM5 = 151` (scope `__anon43fde12c0503`)
- L212 _enumerator_ `SYMS_CvRegx86_MM6 = 152` (scope `__anon43fde12c0503`)
- L213 _enumerator_ `SYMS_CvRegx86_MM7 = 153` (scope `__anon43fde12c0503`)
- L214 _enumerator_ `SYMS_CvRegx86_XMM0 = 154` (scope `__anon43fde12c0503`)
- L215 _enumerator_ `SYMS_CvRegx86_XMM1 = 155` (scope `__anon43fde12c0503`)
- L216 _enumerator_ `SYMS_CvRegx86_XMM2 = 156` (scope `__anon43fde12c0503`)
- L217 _enumerator_ `SYMS_CvRegx86_XMM3 = 157` (scope `__anon43fde12c0503`)
- L218 _enumerator_ `SYMS_CvRegx86_XMM4 = 158` (scope `__anon43fde12c0503`)
- L219 _enumerator_ `SYMS_CvRegx86_XMM5 = 159` (scope `__anon43fde12c0503`)
- L220 _enumerator_ `SYMS_CvRegx86_XMM6 = 160` (scope `__anon43fde12c0503`)
- L221 _enumerator_ `SYMS_CvRegx86_XMM7 = 161` (scope `__anon43fde12c0503`)
- L222 _enumerator_ `SYMS_CvRegx86_XMM00 = 162` (scope `__anon43fde12c0503`)
- L223 _enumerator_ `SYMS_CvRegx86_XMM01 = 163` (scope `__anon43fde12c0503`)
- L224 _enumerator_ `SYMS_CvRegx86_XMM02 = 164` (scope `__anon43fde12c0503`)
- L225 _enumerator_ `SYMS_CvRegx86_XMM03 = 165` (scope `__anon43fde12c0503`)
- L226 _enumerator_ `SYMS_CvRegx86_XMM10 = 166` (scope `__anon43fde12c0503`)
- L227 _enumerator_ `SYMS_CvRegx86_XMM11 = 167` (scope `__anon43fde12c0503`)
- L228 _enumerator_ `SYMS_CvRegx86_XMM12 = 168` (scope `__anon43fde12c0503`)
- L229 _enumerator_ `SYMS_CvRegx86_XMM13 = 169` (scope `__anon43fde12c0503`)
- L230 _enumerator_ `SYMS_CvRegx86_XMM20 = 170` (scope `__anon43fde12c0503`)
- L231 _enumerator_ `SYMS_CvRegx86_XMM21 = 171` (scope `__anon43fde12c0503`)
- L232 _enumerator_ `SYMS_CvRegx86_XMM22 = 172` (scope `__anon43fde12c0503`)
- L233 _enumerator_ `SYMS_CvRegx86_XMM23 = 173` (scope `__anon43fde12c0503`)
- L234 _enumerator_ `SYMS_CvRegx86_XMM30 = 174` (scope `__anon43fde12c0503`)
- L235 _enumerator_ `SYMS_CvRegx86_XMM31 = 175` (scope `__anon43fde12c0503`)
- L236 _enumerator_ `SYMS_CvRegx86_XMM32 = 176` (scope `__anon43fde12c0503`)
- L237 _enumerator_ `SYMS_CvRegx86_XMM33 = 177` (scope `__anon43fde12c0503`)
- L238 _enumerator_ `SYMS_CvRegx86_XMM40 = 178` (scope `__anon43fde12c0503`)
- L239 _enumerator_ `SYMS_CvRegx86_XMM41 = 179` (scope `__anon43fde12c0503`)
- L240 _enumerator_ `SYMS_CvRegx86_XMM42 = 180` (scope `__anon43fde12c0503`)
- L241 _enumerator_ `SYMS_CvRegx86_XMM43 = 181` (scope `__anon43fde12c0503`)
- L242 _enumerator_ `SYMS_CvRegx86_XMM50 = 182` (scope `__anon43fde12c0503`)
- L243 _enumerator_ `SYMS_CvRegx86_XMM51 = 183` (scope `__anon43fde12c0503`)
- L244 _enumerator_ `SYMS_CvRegx86_XMM52 = 184` (scope `__anon43fde12c0503`)
- L245 _enumerator_ `SYMS_CvRegx86_XMM53 = 185` (scope `__anon43fde12c0503`)
- L246 _enumerator_ `SYMS_CvRegx86_XMM60 = 186` (scope `__anon43fde12c0503`)
- L247 _enumerator_ `SYMS_CvRegx86_XMM61 = 187` (scope `__anon43fde12c0503`)
- L248 _enumerator_ `SYMS_CvRegx86_XMM62 = 188` (scope `__anon43fde12c0503`)
- L249 _enumerator_ `SYMS_CvRegx86_XMM63 = 189` (scope `__anon43fde12c0503`)
- L250 _enumerator_ `SYMS_CvRegx86_XMM70 = 190` (scope `__anon43fde12c0503`)
- L251 _enumerator_ `SYMS_CvRegx86_XMM71 = 191` (scope `__anon43fde12c0503`)
- L252 _enumerator_ `SYMS_CvRegx86_XMM72 = 192` (scope `__anon43fde12c0503`)
- L253 _enumerator_ `SYMS_CvRegx86_XMM73 = 193` (scope `__anon43fde12c0503`)
- L254 _enumerator_ `SYMS_CvRegx86_XMM0L = 194` (scope `__anon43fde12c0503`)
- L255 _enumerator_ `SYMS_CvRegx86_XMM1L = 195` (scope `__anon43fde12c0503`)
- L256 _enumerator_ `SYMS_CvRegx86_XMM2L = 196` (scope `__anon43fde12c0503`)
- L257 _enumerator_ `SYMS_CvRegx86_XMM3L = 197` (scope `__anon43fde12c0503`)
- L258 _enumerator_ `SYMS_CvRegx86_XMM4L = 198` (scope `__anon43fde12c0503`)
- L259 _enumerator_ `SYMS_CvRegx86_XMM5L = 199` (scope `__anon43fde12c0503`)
- L260 _enumerator_ `SYMS_CvRegx86_XMM6L = 200` (scope `__anon43fde12c0503`)
- L261 _enumerator_ `SYMS_CvRegx86_XMM7L = 201` (scope `__anon43fde12c0503`)
- L262 _enumerator_ `SYMS_CvRegx86_XMM0H = 202` (scope `__anon43fde12c0503`)
- L263 _enumerator_ `SYMS_CvRegx86_XMM1H = 203` (scope `__anon43fde12c0503`)
- L264 _enumerator_ `SYMS_CvRegx86_XMM2H = 204` (scope `__anon43fde12c0503`)
- L265 _enumerator_ `SYMS_CvRegx86_XMM3H = 205` (scope `__anon43fde12c0503`)
- L266 _enumerator_ `SYMS_CvRegx86_XMM4H = 206` (scope `__anon43fde12c0503`)
- L267 _enumerator_ `SYMS_CvRegx86_XMM5H = 207` (scope `__anon43fde12c0503`)
- L268 _enumerator_ `SYMS_CvRegx86_XMM6H = 208` (scope `__anon43fde12c0503`)
- L269 _enumerator_ `SYMS_CvRegx86_XMM7H = 209` (scope `__anon43fde12c0503`)
- L271 _enumerator_ `SYMS_CvRegx86_YMM0 = 252` (scope `__anon43fde12c0503`) — AVX registers
- L272 _enumerator_ `SYMS_CvRegx86_YMM1 = 253` (scope `__anon43fde12c0503`)
- L273 _enumerator_ `SYMS_CvRegx86_YMM2 = 254` (scope `__anon43fde12c0503`)
- L274 _enumerator_ `SYMS_CvRegx86_YMM3 = 255` (scope `__anon43fde12c0503`)
- L275 _enumerator_ `SYMS_CvRegx86_YMM4 = 256` (scope `__anon43fde12c0503`)
- L276 _enumerator_ `SYMS_CvRegx86_YMM5 = 257` (scope `__anon43fde12c0503`)
- L277 _enumerator_ `SYMS_CvRegx86_YMM6 = 258` (scope `__anon43fde12c0503`)
- L278 _enumerator_ `SYMS_CvRegx86_YMM7 = 259` (scope `__anon43fde12c0503`)
- L279 _enumerator_ `SYMS_CvRegx86_YMM0H = 260` (scope `__anon43fde12c0503`)
- L280 _enumerator_ `SYMS_CvRegx86_YMM1H = 261` (scope `__anon43fde12c0503`)
- L281 _enumerator_ `SYMS_CvRegx86_YMM2H = 262` (scope `__anon43fde12c0503`)
- L282 _enumerator_ `SYMS_CvRegx86_YMM3H = 263` (scope `__anon43fde12c0503`)
- L283 _enumerator_ `SYMS_CvRegx86_YMM4H = 264` (scope `__anon43fde12c0503`)
- L284 _enumerator_ `SYMS_CvRegx86_YMM5H = 265` (scope `__anon43fde12c0503`)
- L285 _enumerator_ `SYMS_CvRegx86_YMM6H = 266` (scope `__anon43fde12c0503`)
- L286 _enumerator_ `SYMS_CvRegx86_YMM7H = 267` (scope `__anon43fde12c0503`)
- L288 _enumerator_ `SYMS_CvRegx86_YMM0I0 = 268` (scope `__anon43fde12c0503`) — AVX integer registers
- L289 _enumerator_ `SYMS_CvRegx86_YMM0I1 = 269` (scope `__anon43fde12c0503`)
- L290 _enumerator_ `SYMS_CvRegx86_YMM0I2 = 270` (scope `__anon43fde12c0503`)
- L291 _enumerator_ `SYMS_CvRegx86_YMM0I3 = 271` (scope `__anon43fde12c0503`)
- L292 _enumerator_ `SYMS_CvRegx86_YMM1I0 = 272` (scope `__anon43fde12c0503`)
- L293 _enumerator_ `SYMS_CvRegx86_YMM1I1 = 273` (scope `__anon43fde12c0503`)
- L294 _enumerator_ `SYMS_CvRegx86_YMM1I2 = 274` (scope `__anon43fde12c0503`)
- L295 _enumerator_ `SYMS_CvRegx86_YMM1I3 = 275` (scope `__anon43fde12c0503`)
- L296 _enumerator_ `SYMS_CvRegx86_YMM2I0 = 276` (scope `__anon43fde12c0503`)
- L297 _enumerator_ `SYMS_CvRegx86_YMM2I1 = 277` (scope `__anon43fde12c0503`)
- L298 _enumerator_ `SYMS_CvRegx86_YMM2I2 = 278` (scope `__anon43fde12c0503`)
- L299 _enumerator_ `SYMS_CvRegx86_YMM2I3 = 279` (scope `__anon43fde12c0503`)
- L300 _enumerator_ `SYMS_CvRegx86_YMM3I0 = 280` (scope `__anon43fde12c0503`)
- L301 _enumerator_ `SYMS_CvRegx86_YMM3I1 = 281` (scope `__anon43fde12c0503`)
- L302 _enumerator_ `SYMS_CvRegx86_YMM3I2 = 282` (scope `__anon43fde12c0503`)
- L303 _enumerator_ `SYMS_CvRegx86_YMM3I3 = 283` (scope `__anon43fde12c0503`)
- L304 _enumerator_ `SYMS_CvRegx86_YMM4I0 = 284` (scope `__anon43fde12c0503`)
- L305 _enumerator_ `SYMS_CvRegx86_YMM4I1 = 285` (scope `__anon43fde12c0503`)
- L306 _enumerator_ `SYMS_CvRegx86_YMM4I2 = 286` (scope `__anon43fde12c0503`)
- L307 _enumerator_ `SYMS_CvRegx86_YMM4I3 = 287` (scope `__anon43fde12c0503`)
- L308 _enumerator_ `SYMS_CvRegx86_YMM5I0 = 288` (scope `__anon43fde12c0503`)
- L309 _enumerator_ `SYMS_CvRegx86_YMM5I1 = 289` (scope `__anon43fde12c0503`)
- L310 _enumerator_ `SYMS_CvRegx86_YMM5I2 = 290` (scope `__anon43fde12c0503`)
- L311 _enumerator_ `SYMS_CvRegx86_YMM5I3 = 291` (scope `__anon43fde12c0503`)
- L312 _enumerator_ `SYMS_CvRegx86_YMM6I0 = 292` (scope `__anon43fde12c0503`)
- L313 _enumerator_ `SYMS_CvRegx86_YMM6I1 = 293` (scope `__anon43fde12c0503`)
- L314 _enumerator_ `SYMS_CvRegx86_YMM6I2 = 294` (scope `__anon43fde12c0503`)
- L315 _enumerator_ `SYMS_CvRegx86_YMM6I3 = 295` (scope `__anon43fde12c0503`)
- L316 _enumerator_ `SYMS_CvRegx86_YMM7I0 = 296` (scope `__anon43fde12c0503`)
- L317 _enumerator_ `SYMS_CvRegx86_YMM7I1 = 297` (scope `__anon43fde12c0503`)
- L318 _enumerator_ `SYMS_CvRegx86_YMM7I2 = 298` (scope `__anon43fde12c0503`)
- L319 _enumerator_ `SYMS_CvRegx86_YMM7I3 = 299` (scope `__anon43fde12c0503`)
- L321 _enumerator_ `SYMS_CvRegx86_YMM0F0 = 300` (scope `__anon43fde12c0503`) — AVX floating-point single precise registers
- L322 _enumerator_ `SYMS_CvRegx86_YMM0F1 = 301` (scope `__anon43fde12c0503`)
- L323 _enumerator_ `SYMS_CvRegx86_YMM0F2 = 302` (scope `__anon43fde12c0503`)
- L324 _enumerator_ `SYMS_CvRegx86_YMM0F3 = 303` (scope `__anon43fde12c0503`)
- L325 _enumerator_ `SYMS_CvRegx86_YMM0F4 = 304` (scope `__anon43fde12c0503`)
- L326 _enumerator_ `SYMS_CvRegx86_YMM0F5 = 305` (scope `__anon43fde12c0503`)
- L327 _enumerator_ `SYMS_CvRegx86_YMM0F6 = 306` (scope `__anon43fde12c0503`)
- L328 _enumerator_ `SYMS_CvRegx86_YMM0F7 = 307` (scope `__anon43fde12c0503`)
- L329 _enumerator_ `SYMS_CvRegx86_YMM1F0 = 308` (scope `__anon43fde12c0503`)
- L330 _enumerator_ `SYMS_CvRegx86_YMM1F1 = 309` (scope `__anon43fde12c0503`)
- L331 _enumerator_ `SYMS_CvRegx86_YMM1F2 = 310` (scope `__anon43fde12c0503`)
- L332 _enumerator_ `SYMS_CvRegx86_YMM1F3 = 311` (scope `__anon43fde12c0503`)
- L333 _enumerator_ `SYMS_CvRegx86_YMM1F4 = 312` (scope `__anon43fde12c0503`)
- L334 _enumerator_ `SYMS_CvRegx86_YMM1F5 = 313` (scope `__anon43fde12c0503`)
- L335 _enumerator_ `SYMS_CvRegx86_YMM1F6 = 314` (scope `__anon43fde12c0503`)
- L336 _enumerator_ `SYMS_CvRegx86_YMM1F7 = 315` (scope `__anon43fde12c0503`)
- L337 _enumerator_ `SYMS_CvRegx86_YMM2F0 = 316` (scope `__anon43fde12c0503`)
- L338 _enumerator_ `SYMS_CvRegx86_YMM2F1 = 317` (scope `__anon43fde12c0503`)
- L339 _enumerator_ `SYMS_CvRegx86_YMM2F2 = 318` (scope `__anon43fde12c0503`)
- L340 _enumerator_ `SYMS_CvRegx86_YMM2F3 = 319` (scope `__anon43fde12c0503`)
- L341 _enumerator_ `SYMS_CvRegx86_YMM2F4 = 320` (scope `__anon43fde12c0503`)
- L342 _enumerator_ `SYMS_CvRegx86_YMM2F5 = 321` (scope `__anon43fde12c0503`)
- L343 _enumerator_ `SYMS_CvRegx86_YMM2F6 = 322` (scope `__anon43fde12c0503`)
- L344 _enumerator_ `SYMS_CvRegx86_YMM2F7 = 323` (scope `__anon43fde12c0503`)
- L345 _enumerator_ `SYMS_CvRegx86_YMM3F0 = 324` (scope `__anon43fde12c0503`)
- L346 _enumerator_ `SYMS_CvRegx86_YMM3F1 = 325` (scope `__anon43fde12c0503`)
- L347 _enumerator_ `SYMS_CvRegx86_YMM3F2 = 326` (scope `__anon43fde12c0503`)
- L348 _enumerator_ `SYMS_CvRegx86_YMM3F3 = 327` (scope `__anon43fde12c0503`)
- L349 _enumerator_ `SYMS_CvRegx86_YMM3F4 = 328` (scope `__anon43fde12c0503`)
- L350 _enumerator_ `SYMS_CvRegx86_YMM3F5 = 329` (scope `__anon43fde12c0503`)
- L351 _enumerator_ `SYMS_CvRegx86_YMM3F6 = 330` (scope `__anon43fde12c0503`)
- L352 _enumerator_ `SYMS_CvRegx86_YMM3F7 = 331` (scope `__anon43fde12c0503`)
- L353 _enumerator_ `SYMS_CvRegx86_YMM4F0 = 332` (scope `__anon43fde12c0503`)
- L354 _enumerator_ `SYMS_CvRegx86_YMM4F1 = 333` (scope `__anon43fde12c0503`)
- L355 _enumerator_ `SYMS_CvRegx86_YMM4F2 = 334` (scope `__anon43fde12c0503`)
- L356 _enumerator_ `SYMS_CvRegx86_YMM4F3 = 335` (scope `__anon43fde12c0503`)
- L357 _enumerator_ `SYMS_CvRegx86_YMM4F4 = 336` (scope `__anon43fde12c0503`)
- L358 _enumerator_ `SYMS_CvRegx86_YMM4F5 = 337` (scope `__anon43fde12c0503`)
- L359 _enumerator_ `SYMS_CvRegx86_YMM4F6 = 338` (scope `__anon43fde12c0503`)
- L360 _enumerator_ `SYMS_CvRegx86_YMM4F7 = 339` (scope `__anon43fde12c0503`)
- L361 _enumerator_ `SYMS_CvRegx86_YMM5F0 = 340` (scope `__anon43fde12c0503`)
- L362 _enumerator_ `SYMS_CvRegx86_YMM5F1 = 341` (scope `__anon43fde12c0503`)
- L363 _enumerator_ `SYMS_CvRegx86_YMM5F2 = 342` (scope `__anon43fde12c0503`)
- L364 _enumerator_ `SYMS_CvRegx86_YMM5F3 = 343` (scope `__anon43fde12c0503`)
- L365 _enumerator_ `SYMS_CvRegx86_YMM5F4 = 344` (scope `__anon43fde12c0503`)
- L366 _enumerator_ `SYMS_CvRegx86_YMM5F5 = 345` (scope `__anon43fde12c0503`)
- L367 _enumerator_ `SYMS_CvRegx86_YMM5F6 = 346` (scope `__anon43fde12c0503`)
- L368 _enumerator_ `SYMS_CvRegx86_YMM5F7 = 347` (scope `__anon43fde12c0503`)
- L369 _enumerator_ `SYMS_CvRegx86_YMM6F0 = 348` (scope `__anon43fde12c0503`)
- L370 _enumerator_ `SYMS_CvRegx86_YMM6F1 = 349` (scope `__anon43fde12c0503`)
- L371 _enumerator_ `SYMS_CvRegx86_YMM6F2 = 350` (scope `__anon43fde12c0503`)
- L372 _enumerator_ `SYMS_CvRegx86_YMM6F3 = 351` (scope `__anon43fde12c0503`)
- L373 _enumerator_ `SYMS_CvRegx86_YMM6F4 = 352` (scope `__anon43fde12c0503`)
- L374 _enumerator_ `SYMS_CvRegx86_YMM6F5 = 353` (scope `__anon43fde12c0503`)
- L375 _enumerator_ `SYMS_CvRegx86_YMM6F6 = 354` (scope `__anon43fde12c0503`)
- L376 _enumerator_ `SYMS_CvRegx86_YMM6F7 = 355` (scope `__anon43fde12c0503`)
- L377 _enumerator_ `SYMS_CvRegx86_YMM7F0 = 356` (scope `__anon43fde12c0503`)
- L378 _enumerator_ `SYMS_CvRegx86_YMM7F1 = 357` (scope `__anon43fde12c0503`)
- L379 _enumerator_ `SYMS_CvRegx86_YMM7F2 = 358` (scope `__anon43fde12c0503`)
- L380 _enumerator_ `SYMS_CvRegx86_YMM7F3 = 359` (scope `__anon43fde12c0503`)
- L381 _enumerator_ `SYMS_CvRegx86_YMM7F4 = 360` (scope `__anon43fde12c0503`)
- L382 _enumerator_ `SYMS_CvRegx86_YMM7F5 = 361` (scope `__anon43fde12c0503`)
- L383 _enumerator_ `SYMS_CvRegx86_YMM7F6 = 362` (scope `__anon43fde12c0503`)
- L384 _enumerator_ `SYMS_CvRegx86_YMM7F7 = 363` (scope `__anon43fde12c0503`)
- L386 _enumerator_ `SYMS_CvRegx86_YMM0D0 = 364` (scope `__anon43fde12c0503`) — AVX floating-point double precise registers
- L387 _enumerator_ `SYMS_CvRegx86_YMM0D1 = 365` (scope `__anon43fde12c0503`)
- L388 _enumerator_ `SYMS_CvRegx86_YMM0D2 = 366` (scope `__anon43fde12c0503`)
- L389 _enumerator_ `SYMS_CvRegx86_YMM0D3 = 367` (scope `__anon43fde12c0503`)
- L390 _enumerator_ `SYMS_CvRegx86_YMM1D0 = 368` (scope `__anon43fde12c0503`)
- L391 _enumerator_ `SYMS_CvRegx86_YMM1D1 = 369` (scope `__anon43fde12c0503`)
- L392 _enumerator_ `SYMS_CvRegx86_YMM1D2 = 370` (scope `__anon43fde12c0503`)
- L393 _enumerator_ `SYMS_CvRegx86_YMM1D3 = 371` (scope `__anon43fde12c0503`)
- L394 _enumerator_ `SYMS_CvRegx86_YMM2D0 = 372` (scope `__anon43fde12c0503`)
- L395 _enumerator_ `SYMS_CvRegx86_YMM2D1 = 373` (scope `__anon43fde12c0503`)
- L396 _enumerator_ `SYMS_CvRegx86_YMM2D2 = 374` (scope `__anon43fde12c0503`)
- L397 _enumerator_ `SYMS_CvRegx86_YMM2D3 = 375` (scope `__anon43fde12c0503`)
- L398 _enumerator_ `SYMS_CvRegx86_YMM3D0 = 376` (scope `__anon43fde12c0503`)
- L399 _enumerator_ `SYMS_CvRegx86_YMM3D1 = 377` (scope `__anon43fde12c0503`)
- L400 _enumerator_ `SYMS_CvRegx86_YMM3D2 = 378` (scope `__anon43fde12c0503`)
- L401 _enumerator_ `SYMS_CvRegx86_YMM3D3 = 379` (scope `__anon43fde12c0503`)
- L402 _enumerator_ `SYMS_CvRegx86_YMM4D0 = 380` (scope `__anon43fde12c0503`)
- L403 _enumerator_ `SYMS_CvRegx86_YMM4D1 = 381` (scope `__anon43fde12c0503`)
- L404 _enumerator_ `SYMS_CvRegx86_YMM4D2 = 382` (scope `__anon43fde12c0503`)
- L405 _enumerator_ `SYMS_CvRegx86_YMM4D3 = 383` (scope `__anon43fde12c0503`)
- L406 _enumerator_ `SYMS_CvRegx86_YMM5D0 = 384` (scope `__anon43fde12c0503`)
- L407 _enumerator_ `SYMS_CvRegx86_YMM5D1 = 385` (scope `__anon43fde12c0503`)
- L408 _enumerator_ `SYMS_CvRegx86_YMM5D2 = 386` (scope `__anon43fde12c0503`)
- L409 _enumerator_ `SYMS_CvRegx86_YMM5D3 = 387` (scope `__anon43fde12c0503`)
- L410 _enumerator_ `SYMS_CvRegx86_YMM6D0 = 388` (scope `__anon43fde12c0503`)
- L411 _enumerator_ `SYMS_CvRegx86_YMM6D1 = 389` (scope `__anon43fde12c0503`)
- L412 _enumerator_ `SYMS_CvRegx86_YMM6D2 = 390` (scope `__anon43fde12c0503`)
- L413 _enumerator_ `SYMS_CvRegx86_YMM6D3 = 391` (scope `__anon43fde12c0503`)
- L414 _enumerator_ `SYMS_CvRegx86_YMM7D0 = 392` (scope `__anon43fde12c0503`)
- L415 _enumerator_ `SYMS_CvRegx86_YMM7D1 = 393` (scope `__anon43fde12c0503`)
- L416 _enumerator_ `SYMS_CvRegx86_YMM7D2 = 394` (scope `__anon43fde12c0503`)
- L417 _enumerator_ `SYMS_CvRegx86_YMM7D3 = 395` (scope `__anon43fde12c0503`)
- L418 _enumerator_ `SYMS_CvRegx86_COUNT = 243` (scope `__anon43fde12c0503`)
- L420 _typedef_ `typedef SYMS_U16 SYMS_CvRegx64;`
- L423 _enumerator_ `SYMS_CvRegx64_NONE = 0` (scope `__anon43fde12c0603`) — CODE REG-ID BYTE-OFFSET BYTE-SIZE
- L424 _enumerator_ `SYMS_CvRegx64_AL = 1` (scope `__anon43fde12c0603`)
- L425 _enumerator_ `SYMS_CvRegx64_CL = 2` (scope `__anon43fde12c0603`)
- L426 _enumerator_ `SYMS_CvRegx64_DL = 3` (scope `__anon43fde12c0603`)
- L427 _enumerator_ `SYMS_CvRegx64_BL = 4` (scope `__anon43fde12c0603`)
- L428 _enumerator_ `SYMS_CvRegx64_AH = 5` (scope `__anon43fde12c0603`)
- L429 _enumerator_ `SYMS_CvRegx64_CH = 6` (scope `__anon43fde12c0603`)
- L430 _enumerator_ `SYMS_CvRegx64_DH = 7` (scope `__anon43fde12c0603`)
- L431 _enumerator_ `SYMS_CvRegx64_BH = 8` (scope `__anon43fde12c0603`)
- L432 _enumerator_ `SYMS_CvRegx64_AX = 9` (scope `__anon43fde12c0603`)
- L433 _enumerator_ `SYMS_CvRegx64_CX = 10` (scope `__anon43fde12c0603`)
- L434 _enumerator_ `SYMS_CvRegx64_DX = 11` (scope `__anon43fde12c0603`)
- L435 _enumerator_ `SYMS_CvRegx64_BX = 12` (scope `__anon43fde12c0603`)
- L436 _enumerator_ `SYMS_CvRegx64_SP = 13` (scope `__anon43fde12c0603`)
- L437 _enumerator_ `SYMS_CvRegx64_BP = 14` (scope `__anon43fde12c0603`)
- L438 _enumerator_ `SYMS_CvRegx64_SI = 15` (scope `__anon43fde12c0603`)
- L439 _enumerator_ `SYMS_CvRegx64_DI = 16` (scope `__anon43fde12c0603`)
- L440 _enumerator_ `SYMS_CvRegx64_EAX = 17` (scope `__anon43fde12c0603`)
- L441 _enumerator_ `SYMS_CvRegx64_ECX = 18` (scope `__anon43fde12c0603`)
- L442 _enumerator_ `SYMS_CvRegx64_EDX = 19` (scope `__anon43fde12c0603`)
- L443 _enumerator_ `SYMS_CvRegx64_EBX = 20` (scope `__anon43fde12c0603`)
- L444 _enumerator_ `SYMS_CvRegx64_ESP = 21` (scope `__anon43fde12c0603`)
- L445 _enumerator_ `SYMS_CvRegx64_EBP = 22` (scope `__anon43fde12c0603`)
- L446 _enumerator_ `SYMS_CvRegx64_ESI = 23` (scope `__anon43fde12c0603`)
- L447 _enumerator_ `SYMS_CvRegx64_EDI = 24` (scope `__anon43fde12c0603`)
- L448 _enumerator_ `SYMS_CvRegx64_ES = 25` (scope `__anon43fde12c0603`)
- L449 _enumerator_ `SYMS_CvRegx64_CS = 26` (scope `__anon43fde12c0603`)
- L450 _enumerator_ `SYMS_CvRegx64_SS = 27` (scope `__anon43fde12c0603`)
- L451 _enumerator_ `SYMS_CvRegx64_DS = 28` (scope `__anon43fde12c0603`)
- L452 _enumerator_ `SYMS_CvRegx64_FS = 29` (scope `__anon43fde12c0603`)
- L453 _enumerator_ `SYMS_CvRegx64_GS = 30` (scope `__anon43fde12c0603`)
- L454 _enumerator_ `SYMS_CvRegx64_FLAGS = 32` (scope `__anon43fde12c0603`)
- L455 _enumerator_ `SYMS_CvRegx64_RIP = 33` (scope `__anon43fde12c0603`)
- L456 _enumerator_ `SYMS_CvRegx64_EFLAGS = 34` (scope `__anon43fde12c0603`)
- L458 _enumerator_ `SYMS_CvRegx64_CR0 = 80` (scope `__anon43fde12c0603`) — Control registers
- L459 _enumerator_ `SYMS_CvRegx64_CR1 = 81` (scope `__anon43fde12c0603`)
- L460 _enumerator_ `SYMS_CvRegx64_CR2 = 82` (scope `__anon43fde12c0603`)
- L461 _enumerator_ `SYMS_CvRegx64_CR3 = 83` (scope `__anon43fde12c0603`)
- L462 _enumerator_ `SYMS_CvRegx64_CR4 = 84` (scope `__anon43fde12c0603`)
- L463 _enumerator_ `SYMS_CvRegx64_CR8 = 88` (scope `__anon43fde12c0603`)
- L465 _enumerator_ `SYMS_CvRegx64_DR0 = 90` (scope `__anon43fde12c0603`) — Debug registers
- L466 _enumerator_ `SYMS_CvRegx64_DR1 = 91` (scope `__anon43fde12c0603`)
- L467 _enumerator_ `SYMS_CvRegx64_DR2 = 92` (scope `__anon43fde12c0603`)
- L468 _enumerator_ `SYMS_CvRegx64_DR3 = 93` (scope `__anon43fde12c0603`)
- L469 _enumerator_ `SYMS_CvRegx64_DR4 = 94` (scope `__anon43fde12c0603`)
- L470 _enumerator_ `SYMS_CvRegx64_DR5 = 95` (scope `__anon43fde12c0603`)
- L471 _enumerator_ `SYMS_CvRegx64_DR6 = 96` (scope `__anon43fde12c0603`)
- L472 _enumerator_ `SYMS_CvRegx64_DR7 = 97` (scope `__anon43fde12c0603`)
- L474 _enumerator_ `SYMS_CvRegx64_DR8 = 98` (scope `__anon43fde12c0603`) — TODO(allen): Are we missing dr8-dr15 in the x64 register definitions?
- L475 _enumerator_ `SYMS_CvRegx64_DR9 = 99` (scope `__anon43fde12c0603`)
- L476 _enumerator_ `SYMS_CvRegx64_DR10 = 100` (scope `__anon43fde12c0603`)
- L477 _enumerator_ `SYMS_CvRegx64_DR11 = 101` (scope `__anon43fde12c0603`)
- L478 _enumerator_ `SYMS_CvRegx64_DR12 = 102` (scope `__anon43fde12c0603`)
- L479 _enumerator_ `SYMS_CvRegx64_DR13 = 103` (scope `__anon43fde12c0603`)
- L480 _enumerator_ `SYMS_CvRegx64_DR14 = 104` (scope `__anon43fde12c0603`)
- L481 _enumerator_ `SYMS_CvRegx64_DR15 = 105` (scope `__anon43fde12c0603`)
- L483 _enumerator_ `SYMS_CvRegx64_GDTR = 110` (scope `__anon43fde12c0603`) — TODO(allen): Are we missing these in the x64 register definitions?
- L484 _enumerator_ `SYMS_CvRegx64_GDTL = 111` (scope `__anon43fde12c0603`)
- L485 _enumerator_ `SYMS_CvRegx64_IDTR = 112` (scope `__anon43fde12c0603`)
- L486 _enumerator_ `SYMS_CvRegx64_IDTL = 113` (scope `__anon43fde12c0603`)
- L487 _enumerator_ `SYMS_CvRegx64_LDTR = 114` (scope `__anon43fde12c0603`)
- L488 _enumerator_ `SYMS_CvRegx64_TR = 115` (scope `__anon43fde12c0603`)
- L489 _enumerator_ `SYMS_CvRegx64_ST0 = 128` (scope `__anon43fde12c0603`)
- L490 _enumerator_ `SYMS_CvRegx64_ST1 = 129` (scope `__anon43fde12c0603`)
- L491 _enumerator_ `SYMS_CvRegx64_ST2 = 130` (scope `__anon43fde12c0603`)
- L492 _enumerator_ `SYMS_CvRegx64_ST3 = 131` (scope `__anon43fde12c0603`)
- L493 _enumerator_ `SYMS_CvRegx64_ST4 = 132` (scope `__anon43fde12c0603`)
- L494 _enumerator_ `SYMS_CvRegx64_ST5 = 133` (scope `__anon43fde12c0603`)
- L495 _enumerator_ `SYMS_CvRegx64_ST6 = 134` (scope `__anon43fde12c0603`)
- L496 _enumerator_ `SYMS_CvRegx64_ST7 = 135` (scope `__anon43fde12c0603`)
- L498 _enumerator_ `SYMS_CvRegx64_CTRL = 136` (scope `__anon43fde12c0603`) — TODO(allen): Figure out how these map to our registers (looks like a different naming scheme)
- L499 _enumerator_ `SYMS_CvRegx64_STAT = 137` (scope `__anon43fde12c0603`)
- L500 _enumerator_ `SYMS_CvRegx64_TAG = 138` (scope `__anon43fde12c0603`)
- L501 _enumerator_ `SYMS_CvRegx64_FPIP = 139` (scope `__anon43fde12c0603`)
- L502 _enumerator_ `SYMS_CvRegx64_FPCS = 140` (scope `__anon43fde12c0603`)
- L503 _enumerator_ `SYMS_CvRegx64_FPDO = 141` (scope `__anon43fde12c0603`)
- L504 _enumerator_ `SYMS_CvRegx64_FPDS = 142` (scope `__anon43fde12c0603`)
- L505 _enumerator_ `SYMS_CvRegx64_ISEM = 143` (scope `__anon43fde12c0603`)
- L506 _enumerator_ `SYMS_CvRegx64_FPEIP = 144` (scope `__anon43fde12c0603`)
- L507 _enumerator_ `SYMS_CvRegx64_FPEDO = 145` (scope `__anon43fde12c0603`)
- L508 _enumerator_ `SYMS_CvRegx64_MM0 = 146` (scope `__anon43fde12c0603`)
- L509 _enumerator_ `SYMS_CvRegx64_MM1 = 147` (scope `__anon43fde12c0603`)
- L510 _enumerator_ `SYMS_CvRegx64_MM2 = 148` (scope `__anon43fde12c0603`)
- L511 _enumerator_ `SYMS_CvRegx64_MM3 = 149` (scope `__anon43fde12c0603`)
- L512 _enumerator_ `SYMS_CvRegx64_MM4 = 150` (scope `__anon43fde12c0603`)
- L513 _enumerator_ `SYMS_CvRegx64_MM5 = 151` (scope `__anon43fde12c0603`)
- L514 _enumerator_ `SYMS_CvRegx64_MM6 = 152` (scope `__anon43fde12c0603`)
- L515 _enumerator_ `SYMS_CvRegx64_MM7 = 153` (scope `__anon43fde12c0603`)
- L516 _enumerator_ `SYMS_CvRegx64_XMM0 = 154` (scope `__anon43fde12c0603`)
- L517 _enumerator_ `SYMS_CvRegx64_XMM1 = 155` (scope `__anon43fde12c0603`)
- L518 _enumerator_ `SYMS_CvRegx64_XMM2 = 156` (scope `__anon43fde12c0603`)
- L519 _enumerator_ `SYMS_CvRegx64_XMM3 = 157` (scope `__anon43fde12c0603`)
- L520 _enumerator_ `SYMS_CvRegx64_XMM4 = 158` (scope `__anon43fde12c0603`)
- L521 _enumerator_ `SYMS_CvRegx64_XMM5 = 159` (scope `__anon43fde12c0603`)
- L522 _enumerator_ `SYMS_CvRegx64_XMM6 = 160` (scope `__anon43fde12c0603`)
- L523 _enumerator_ `SYMS_CvRegx64_XMM7 = 161` (scope `__anon43fde12c0603`)
- L524 _enumerator_ `SYMS_CvRegx64_XMM0_0 = 162` (scope `__anon43fde12c0603`)
- L525 _enumerator_ `SYMS_CvRegx64_XMM0_1 = 163` (scope `__anon43fde12c0603`)
- L526 _enumerator_ `SYMS_CvRegx64_XMM0_2 = 164` (scope `__anon43fde12c0603`)
- L527 _enumerator_ `SYMS_CvRegx64_XMM0_3 = 165` (scope `__anon43fde12c0603`)
- L528 _enumerator_ `SYMS_CvRegx64_XMM1_0 = 166` (scope `__anon43fde12c0603`)
- L529 _enumerator_ `SYMS_CvRegx64_XMM1_1 = 167` (scope `__anon43fde12c0603`)
- L530 _enumerator_ `SYMS_CvRegx64_XMM1_2 = 168` (scope `__anon43fde12c0603`)
- L531 _enumerator_ `SYMS_CvRegx64_XMM1_3 = 169` (scope `__anon43fde12c0603`)
- L532 _enumerator_ `SYMS_CvRegx64_XMM2_0 = 170` (scope `__anon43fde12c0603`)
- L533 _enumerator_ `SYMS_CvRegx64_XMM2_1 = 171` (scope `__anon43fde12c0603`)
- L534 _enumerator_ `SYMS_CvRegx64_XMM2_2 = 172` (scope `__anon43fde12c0603`)
- L535 _enumerator_ `SYMS_CvRegx64_XMM2_3 = 173` (scope `__anon43fde12c0603`)
- L536 _enumerator_ `SYMS_CvRegx64_XMM3_0 = 174` (scope `__anon43fde12c0603`)
- L537 _enumerator_ `SYMS_CvRegx64_XMM3_1 = 175` (scope `__anon43fde12c0603`)
- L538 _enumerator_ `SYMS_CvRegx64_XMM3_2 = 176` (scope `__anon43fde12c0603`)
- L539 _enumerator_ `SYMS_CvRegx64_XMM3_3 = 177` (scope `__anon43fde12c0603`)
- L540 _enumerator_ `SYMS_CvRegx64_XMM4_0 = 178` (scope `__anon43fde12c0603`)
- L541 _enumerator_ `SYMS_CvRegx64_XMM4_1 = 179` (scope `__anon43fde12c0603`)
- L542 _enumerator_ `SYMS_CvRegx64_XMM4_2 = 180` (scope `__anon43fde12c0603`)
- L543 _enumerator_ `SYMS_CvRegx64_XMM4_3 = 181` (scope `__anon43fde12c0603`)
- L544 _enumerator_ `SYMS_CvRegx64_XMM5_0 = 182` (scope `__anon43fde12c0603`)
- L545 _enumerator_ `SYMS_CvRegx64_XMM5_1 = 183` (scope `__anon43fde12c0603`)
- L546 _enumerator_ `SYMS_CvRegx64_XMM5_2 = 184` (scope `__anon43fde12c0603`)
- L547 _enumerator_ `SYMS_CvRegx64_XMM5_3 = 185` (scope `__anon43fde12c0603`)
- L548 _enumerator_ `SYMS_CvRegx64_XMM6_0 = 186` (scope `__anon43fde12c0603`)
- L549 _enumerator_ `SYMS_CvRegx64_XMM6_1 = 187` (scope `__anon43fde12c0603`)
- L550 _enumerator_ `SYMS_CvRegx64_XMM6_2 = 188` (scope `__anon43fde12c0603`)
- L551 _enumerator_ `SYMS_CvRegx64_XMM6_3 = 189` (scope `__anon43fde12c0603`)
- L552 _enumerator_ `SYMS_CvRegx64_XMM7_0 = 190` (scope `__anon43fde12c0603`)
- L553 _enumerator_ `SYMS_CvRegx64_XMM7_1 = 191` (scope `__anon43fde12c0603`)
- L554 _enumerator_ `SYMS_CvRegx64_XMM7_2 = 192` (scope `__anon43fde12c0603`)
- L555 _enumerator_ `SYMS_CvRegx64_XMM7_3 = 193` (scope `__anon43fde12c0603`)
- L556 _enumerator_ `SYMS_CvRegx64_XMM0L = 194` (scope `__anon43fde12c0603`)
- L557 _enumerator_ `SYMS_CvRegx64_XMM1L = 195` (scope `__anon43fde12c0603`)
- L558 _enumerator_ `SYMS_CvRegx64_XMM2L = 196` (scope `__anon43fde12c0603`)
- L559 _enumerator_ `SYMS_CvRegx64_XMM3L = 197` (scope `__anon43fde12c0603`)
- L560 _enumerator_ `SYMS_CvRegx64_XMM4L = 198` (scope `__anon43fde12c0603`)
- L561 _enumerator_ `SYMS_CvRegx64_XMM5L = 199` (scope `__anon43fde12c0603`)
- L562 _enumerator_ `SYMS_CvRegx64_XMM6L = 200` (scope `__anon43fde12c0603`)
- L563 _enumerator_ `SYMS_CvRegx64_XMM7L = 201` (scope `__anon43fde12c0603`)
- L564 _enumerator_ `SYMS_CvRegx64_XMM0H = 202` (scope `__anon43fde12c0603`)
- L565 _enumerator_ `SYMS_CvRegx64_XMM1H = 203` (scope `__anon43fde12c0603`)
- L566 _enumerator_ `SYMS_CvRegx64_XMM2H = 204` (scope `__anon43fde12c0603`)
- L567 _enumerator_ `SYMS_CvRegx64_XMM3H = 205` (scope `__anon43fde12c0603`)
- L568 _enumerator_ `SYMS_CvRegx64_XMM4H = 206` (scope `__anon43fde12c0603`)
- L569 _enumerator_ `SYMS_CvRegx64_XMM5H = 207` (scope `__anon43fde12c0603`)
- L570 _enumerator_ `SYMS_CvRegx64_XMM6H = 208` (scope `__anon43fde12c0603`)
- L571 _enumerator_ `SYMS_CvRegx64_XMM7H = 209` (scope `__anon43fde12c0603`)
- L573 _enumerator_ `SYMS_CvRegx64_MXCSR = 211` (scope `__anon43fde12c0603`) — XMM status register
- L575 _enumerator_ `SYMS_CvRegx64_EMM0L = 220` (scope `__anon43fde12c0603`) — XMM sub-registers (WNI integer)
- L576 _enumerator_ `SYMS_CvRegx64_EMM1L = 221` (scope `__anon43fde12c0603`)
- L577 _enumerator_ `SYMS_CvRegx64_EMM2L = 222` (scope `__anon43fde12c0603`)
- L578 _enumerator_ `SYMS_CvRegx64_EMM3L = 223` (scope `__anon43fde12c0603`)
- L579 _enumerator_ `SYMS_CvRegx64_EMM4L = 224` (scope `__anon43fde12c0603`)
- L580 _enumerator_ `SYMS_CvRegx64_EMM5L = 225` (scope `__anon43fde12c0603`)
- L581 _enumerator_ `SYMS_CvRegx64_EMM6L = 226` (scope `__anon43fde12c0603`)
- L582 _enumerator_ `SYMS_CvRegx64_EMM7L = 227` (scope `__anon43fde12c0603`)
- L583 _enumerator_ `SYMS_CvRegx64_EMM0H = 228` (scope `__anon43fde12c0603`)
- L584 _enumerator_ `SYMS_CvRegx64_EMM1H = 229` (scope `__anon43fde12c0603`)
- L585 _enumerator_ `SYMS_CvRegx64_EMM2H = 230` (scope `__anon43fde12c0603`)
- L586 _enumerator_ `SYMS_CvRegx64_EMM3H = 231` (scope `__anon43fde12c0603`)
- L587 _enumerator_ `SYMS_CvRegx64_EMM4H = 232` (scope `__anon43fde12c0603`)
- L588 _enumerator_ `SYMS_CvRegx64_EMM5H = 233` (scope `__anon43fde12c0603`)
- L589 _enumerator_ `SYMS_CvRegx64_EMM6H = 234` (scope `__anon43fde12c0603`)
- L590 _enumerator_ `SYMS_CvRegx64_EMM7H = 235` (scope `__anon43fde12c0603`)
- L591 _enumerator_ `SYMS_CvRegx64_MM00 = 236` (scope `__anon43fde12c0603`)
- L592 _enumerator_ `SYMS_CvRegx64_MM01 = 237` (scope `__anon43fde12c0603`)
- L593 _enumerator_ `SYMS_CvRegx64_MM10 = 238` (scope `__anon43fde12c0603`)
- L594 _enumerator_ `SYMS_CvRegx64_MM11 = 239` (scope `__anon43fde12c0603`)
- L595 _enumerator_ `SYMS_CvRegx64_MM20 = 240` (scope `__anon43fde12c0603`)
- L596 _enumerator_ `SYMS_CvRegx64_MM21 = 241` (scope `__anon43fde12c0603`)
- L597 _enumerator_ `SYMS_CvRegx64_MM30 = 242` (scope `__anon43fde12c0603`)
- L598 _enumerator_ `SYMS_CvRegx64_MM31 = 243` (scope `__anon43fde12c0603`)
- L599 _enumerator_ `SYMS_CvRegx64_MM40 = 244` (scope `__anon43fde12c0603`)
- L600 _enumerator_ `SYMS_CvRegx64_MM41 = 245` (scope `__anon43fde12c0603`)
- L601 _enumerator_ `SYMS_CvRegx64_MM50 = 246` (scope `__anon43fde12c0603`)
- L602 _enumerator_ `SYMS_CvRegx64_MM51 = 247` (scope `__anon43fde12c0603`)
- L603 _enumerator_ `SYMS_CvRegx64_MM60 = 248` (scope `__anon43fde12c0603`)
- L604 _enumerator_ `SYMS_CvRegx64_MM61 = 249` (scope `__anon43fde12c0603`)
- L605 _enumerator_ `SYMS_CvRegx64_MM70 = 250` (scope `__anon43fde12c0603`)
- L606 _enumerator_ `SYMS_CvRegx64_MM71 = 251` (scope `__anon43fde12c0603`)
- L607 _enumerator_ `SYMS_CvRegx64_XMM8 = 252` (scope `__anon43fde12c0603`)
- L608 _enumerator_ `SYMS_CvRegx64_XMM9 = 253` (scope `__anon43fde12c0603`)
- L609 _enumerator_ `SYMS_CvRegx64_XMM10 = 254` (scope `__anon43fde12c0603`)
- L610 _enumerator_ `SYMS_CvRegx64_XMM11 = 255` (scope `__anon43fde12c0603`)
- L611 _enumerator_ `SYMS_CvRegx64_XMM12 = 256` (scope `__anon43fde12c0603`)
- L612 _enumerator_ `SYMS_CvRegx64_XMM13 = 257` (scope `__anon43fde12c0603`)
- L613 _enumerator_ `SYMS_CvRegx64_XMM14 = 258` (scope `__anon43fde12c0603`)
- L614 _enumerator_ `SYMS_CvRegx64_XMM15 = 259` (scope `__anon43fde12c0603`)
- L615 _enumerator_ `SYMS_CvRegx64_XMM8_0 = 260` (scope `__anon43fde12c0603`)
- L616 _enumerator_ `SYMS_CvRegx64_XMM8_1 = 261` (scope `__anon43fde12c0603`)
- L617 _enumerator_ `SYMS_CvRegx64_XMM8_2 = 262` (scope `__anon43fde12c0603`)
- L618 _enumerator_ `SYMS_CvRegx64_XMM8_3 = 263` (scope `__anon43fde12c0603`)
- L619 _enumerator_ `SYMS_CvRegx64_XMM9_0 = 264` (scope `__anon43fde12c0603`)
- L620 _enumerator_ `SYMS_CvRegx64_XMM9_1 = 265` (scope `__anon43fde12c0603`)
- L621 _enumerator_ `SYMS_CvRegx64_XMM9_2 = 266` (scope `__anon43fde12c0603`)
- L622 _enumerator_ `SYMS_CvRegx64_XMM9_3 = 267` (scope `__anon43fde12c0603`)
- L623 _enumerator_ `SYMS_CvRegx64_XMM10_0 = 268` (scope `__anon43fde12c0603`)
- L624 _enumerator_ `SYMS_CvRegx64_XMM10_1 = 269` (scope `__anon43fde12c0603`)
- L625 _enumerator_ `SYMS_CvRegx64_XMM10_2 = 270` (scope `__anon43fde12c0603`)
- L626 _enumerator_ `SYMS_CvRegx64_XMM10_3 = 271` (scope `__anon43fde12c0603`)
- L627 _enumerator_ `SYMS_CvRegx64_XMM11_0 = 272` (scope `__anon43fde12c0603`)
- L628 _enumerator_ `SYMS_CvRegx64_XMM11_1 = 273` (scope `__anon43fde12c0603`)
- L629 _enumerator_ `SYMS_CvRegx64_XMM11_2 = 274` (scope `__anon43fde12c0603`)
- L630 _enumerator_ `SYMS_CvRegx64_XMM11_3 = 275` (scope `__anon43fde12c0603`)
- L631 _enumerator_ `SYMS_CvRegx64_XMM12_0 = 276` (scope `__anon43fde12c0603`)
- L632 _enumerator_ `SYMS_CvRegx64_XMM12_1 = 277` (scope `__anon43fde12c0603`)
- L633 _enumerator_ `SYMS_CvRegx64_XMM12_2 = 278` (scope `__anon43fde12c0603`)
- L634 _enumerator_ `SYMS_CvRegx64_XMM12_3 = 279` (scope `__anon43fde12c0603`)
- L635 _enumerator_ `SYMS_CvRegx64_XMM13_0 = 280` (scope `__anon43fde12c0603`)
- L636 _enumerator_ `SYMS_CvRegx64_XMM13_1 = 281` (scope `__anon43fde12c0603`)
- L637 _enumerator_ `SYMS_CvRegx64_XMM13_2 = 282` (scope `__anon43fde12c0603`)
- L638 _enumerator_ `SYMS_CvRegx64_XMM13_3 = 283` (scope `__anon43fde12c0603`)
- L639 _enumerator_ `SYMS_CvRegx64_XMM14_0 = 284` (scope `__anon43fde12c0603`)
- L640 _enumerator_ `SYMS_CvRegx64_XMM14_1 = 285` (scope `__anon43fde12c0603`)
- L641 _enumerator_ `SYMS_CvRegx64_XMM14_2 = 286` (scope `__anon43fde12c0603`)
- L642 _enumerator_ `SYMS_CvRegx64_XMM14_3 = 287` (scope `__anon43fde12c0603`)
- L643 _enumerator_ `SYMS_CvRegx64_XMM15_0 = 288` (scope `__anon43fde12c0603`)
- L644 _enumerator_ `SYMS_CvRegx64_XMM15_1 = 289` (scope `__anon43fde12c0603`)
- L645 _enumerator_ `SYMS_CvRegx64_XMM15_2 = 290` (scope `__anon43fde12c0603`)
- L646 _enumerator_ `SYMS_CvRegx64_XMM15_3 = 291` (scope `__anon43fde12c0603`)
- L647 _enumerator_ `SYMS_CvRegx64_XMM8L = 292` (scope `__anon43fde12c0603`)
- L648 _enumerator_ `SYMS_CvRegx64_XMM9L = 293` (scope `__anon43fde12c0603`)
- L649 _enumerator_ `SYMS_CvRegx64_XMM10L = 294` (scope `__anon43fde12c0603`)
- L650 _enumerator_ `SYMS_CvRegx64_XMM11L = 295` (scope `__anon43fde12c0603`)
- L651 _enumerator_ `SYMS_CvRegx64_XMM12L = 296` (scope `__anon43fde12c0603`)
- L652 _enumerator_ `SYMS_CvRegx64_XMM13L = 297` (scope `__anon43fde12c0603`)
- L653 _enumerator_ `SYMS_CvRegx64_XMM14L = 298` (scope `__anon43fde12c0603`)
- L654 _enumerator_ `SYMS_CvRegx64_XMM15L = 299` (scope `__anon43fde12c0603`)
- L655 _enumerator_ `SYMS_CvRegx64_XMM8H = 300` (scope `__anon43fde12c0603`)
- L656 _enumerator_ `SYMS_CvRegx64_XMM9H = 301` (scope `__anon43fde12c0603`)
- L657 _enumerator_ `SYMS_CvRegx64_XMM10H = 302` (scope `__anon43fde12c0603`)
- L658 _enumerator_ `SYMS_CvRegx64_XMM11H = 303` (scope `__anon43fde12c0603`)
- L659 _enumerator_ `SYMS_CvRegx64_XMM12H = 304` (scope `__anon43fde12c0603`)
- L660 _enumerator_ `SYMS_CvRegx64_XMM13H = 305` (scope `__anon43fde12c0603`)
- L661 _enumerator_ `SYMS_CvRegx64_XMM14H = 306` (scope `__anon43fde12c0603`)
- L662 _enumerator_ `SYMS_CvRegx64_XMM15H = 307` (scope `__anon43fde12c0603`)
- L664 _enumerator_ `SYMS_CvRegx64_EMM8L = 308` (scope `__anon43fde12c0603`) — XMM sub-registers (WNI integer)
- L665 _enumerator_ `SYMS_CvRegx64_EMM9L = 309` (scope `__anon43fde12c0603`)
- L666 _enumerator_ `SYMS_CvRegx64_EMM10L = 310` (scope `__anon43fde12c0603`)
- L667 _enumerator_ `SYMS_CvRegx64_EMM11L = 311` (scope `__anon43fde12c0603`)
- L668 _enumerator_ `SYMS_CvRegx64_EMM12L = 312` (scope `__anon43fde12c0603`)
- L669 _enumerator_ `SYMS_CvRegx64_EMM13L = 313` (scope `__anon43fde12c0603`)
- L670 _enumerator_ `SYMS_CvRegx64_EMM14L = 314` (scope `__anon43fde12c0603`)
- L671 _enumerator_ `SYMS_CvRegx64_EMM15L = 315` (scope `__anon43fde12c0603`)
- L672 _enumerator_ `SYMS_CvRegx64_EMM8H = 316` (scope `__anon43fde12c0603`)
- L673 _enumerator_ `SYMS_CvRegx64_EMM9H = 317` (scope `__anon43fde12c0603`)
- L674 _enumerator_ `SYMS_CvRegx64_EMM10H = 318` (scope `__anon43fde12c0603`)
- L675 _enumerator_ `SYMS_CvRegx64_EMM11H = 319` (scope `__anon43fde12c0603`)
- L676 _enumerator_ `SYMS_CvRegx64_EMM12H = 320` (scope `__anon43fde12c0603`)
- L677 _enumerator_ `SYMS_CvRegx64_EMM13H = 321` (scope `__anon43fde12c0603`)
- L678 _enumerator_ `SYMS_CvRegx64_EMM14H = 322` (scope `__anon43fde12c0603`)
- L679 _enumerator_ `SYMS_CvRegx64_EMM15H = 323` (scope `__anon43fde12c0603`)
- L681 _enumerator_ `SYMS_CvRegx64_SIL = 324` (scope `__anon43fde12c0603`) — Low byte forms of some standard registers
- L682 _enumerator_ `SYMS_CvRegx64_DIL = 325` (scope `__anon43fde12c0603`)
- L683 _enumerator_ `SYMS_CvRegx64_BPL = 326` (scope `__anon43fde12c0603`)
- L684 _enumerator_ `SYMS_CvRegx64_SPL = 327` (scope `__anon43fde12c0603`)
- L686 _enumerator_ `SYMS_CvRegx64_RAX = 328` (scope `__anon43fde12c0603`) — 64-bit regular registers
- L687 _enumerator_ `SYMS_CvRegx64_RBX = 329` (scope `__anon43fde12c0603`)
- L688 _enumerator_ `SYMS_CvRegx64_RCX = 330` (scope `__anon43fde12c0603`)
- L689 _enumerator_ `SYMS_CvRegx64_RDX = 331` (scope `__anon43fde12c0603`)
- L690 _enumerator_ `SYMS_CvRegx64_RSI = 332` (scope `__anon43fde12c0603`)
- L691 _enumerator_ `SYMS_CvRegx64_RDI = 333` (scope `__anon43fde12c0603`)
- L692 _enumerator_ `SYMS_CvRegx64_RBP = 334` (scope `__anon43fde12c0603`)
- L693 _enumerator_ `SYMS_CvRegx64_RSP = 335` (scope `__anon43fde12c0603`)
- L695 _enumerator_ `SYMS_CvRegx64_R8 = 336` (scope `__anon43fde12c0603`) — 64-bit integer registers with 8-, 16-, and 32-bit forms (B, W, and D)
- L696 _enumerator_ `SYMS_CvRegx64_R9 = 337` (scope `__anon43fde12c0603`)
- L697 _enumerator_ `SYMS_CvRegx64_R10 = 338` (scope `__anon43fde12c0603`)
- L698 _enumerator_ `SYMS_CvRegx64_R11 = 339` (scope `__anon43fde12c0603`)
- L699 _enumerator_ `SYMS_CvRegx64_R12 = 340` (scope `__anon43fde12c0603`)
- L700 _enumerator_ `SYMS_CvRegx64_R13 = 341` (scope `__anon43fde12c0603`)
- L701 _enumerator_ `SYMS_CvRegx64_R14 = 342` (scope `__anon43fde12c0603`)
- L702 _enumerator_ `SYMS_CvRegx64_R15 = 343` (scope `__anon43fde12c0603`)
- L703 _enumerator_ `SYMS_CvRegx64_R8B = 344` (scope `__anon43fde12c0603`)
- L704 _enumerator_ `SYMS_CvRegx64_R9B = 345` (scope `__anon43fde12c0603`)
- L705 _enumerator_ `SYMS_CvRegx64_R10B = 346` (scope `__anon43fde12c0603`)
- L706 _enumerator_ `SYMS_CvRegx64_R11B = 347` (scope `__anon43fde12c0603`)
- L707 _enumerator_ `SYMS_CvRegx64_R12B = 348` (scope `__anon43fde12c0603`)
- L708 _enumerator_ `SYMS_CvRegx64_R13B = 349` (scope `__anon43fde12c0603`)
- L709 _enumerator_ `SYMS_CvRegx64_R14B = 350` (scope `__anon43fde12c0603`)
- L710 _enumerator_ `SYMS_CvRegx64_R15B = 351` (scope `__anon43fde12c0603`)
- L711 _enumerator_ `SYMS_CvRegx64_R8W = 352` (scope `__anon43fde12c0603`)
- L712 _enumerator_ `SYMS_CvRegx64_R9W = 353` (scope `__anon43fde12c0603`)
- L713 _enumerator_ `SYMS_CvRegx64_R10W = 354` (scope `__anon43fde12c0603`)
- L714 _enumerator_ `SYMS_CvRegx64_R11W = 355` (scope `__anon43fde12c0603`)
- L715 _enumerator_ `SYMS_CvRegx64_R12W = 356` (scope `__anon43fde12c0603`)
- L716 _enumerator_ `SYMS_CvRegx64_R13W = 357` (scope `__anon43fde12c0603`)
- L717 _enumerator_ `SYMS_CvRegx64_R14W = 358` (scope `__anon43fde12c0603`)
- L718 _enumerator_ `SYMS_CvRegx64_R15W = 359` (scope `__anon43fde12c0603`)
- L719 _enumerator_ `SYMS_CvRegx64_R8D = 360` (scope `__anon43fde12c0603`)
- L720 _enumerator_ `SYMS_CvRegx64_R9D = 361` (scope `__anon43fde12c0603`)
- L721 _enumerator_ `SYMS_CvRegx64_R10D = 362` (scope `__anon43fde12c0603`)
- L722 _enumerator_ `SYMS_CvRegx64_R11D = 363` (scope `__anon43fde12c0603`)
- L723 _enumerator_ `SYMS_CvRegx64_R12D = 364` (scope `__anon43fde12c0603`)
- L724 _enumerator_ `SYMS_CvRegx64_R13D = 365` (scope `__anon43fde12c0603`)
- L725 _enumerator_ `SYMS_CvRegx64_R14D = 366` (scope `__anon43fde12c0603`)
- L726 _enumerator_ `SYMS_CvRegx64_R15D = 367` (scope `__anon43fde12c0603`)
- L728 _enumerator_ `SYMS_CvRegx64_YMM0 = 368` (scope `__anon43fde12c0603`) — AVX registers 256 bits
- L729 _enumerator_ `SYMS_CvRegx64_YMM1 = 369` (scope `__anon43fde12c0603`)
- L730 _enumerator_ `SYMS_CvRegx64_YMM2 = 370` (scope `__anon43fde12c0603`)
- L731 _enumerator_ `SYMS_CvRegx64_YMM3 = 371` (scope `__anon43fde12c0603`)
- L732 _enumerator_ `SYMS_CvRegx64_YMM4 = 372` (scope `__anon43fde12c0603`)
- L733 _enumerator_ `SYMS_CvRegx64_YMM5 = 373` (scope `__anon43fde12c0603`)
- L734 _enumerator_ `SYMS_CvRegx64_YMM6 = 374` (scope `__anon43fde12c0603`)
- L735 _enumerator_ `SYMS_CvRegx64_YMM7 = 375` (scope `__anon43fde12c0603`)
- L736 _enumerator_ `SYMS_CvRegx64_YMM8 = 376` (scope `__anon43fde12c0603`)
- L737 _enumerator_ `SYMS_CvRegx64_YMM9 = 377` (scope `__anon43fde12c0603`)
- L738 _enumerator_ `SYMS_CvRegx64_YMM10 = 378` (scope `__anon43fde12c0603`)
- L739 _enumerator_ `SYMS_CvRegx64_YMM11 = 379` (scope `__anon43fde12c0603`)
- L740 _enumerator_ `SYMS_CvRegx64_YMM12 = 380` (scope `__anon43fde12c0603`)
- L741 _enumerator_ `SYMS_CvRegx64_YMM13 = 381` (scope `__anon43fde12c0603`)
- L742 _enumerator_ `SYMS_CvRegx64_YMM14 = 382` (scope `__anon43fde12c0603`)
- L743 _enumerator_ `SYMS_CvRegx64_YMM15 = 383` (scope `__anon43fde12c0603`)
- L745 _enumerator_ `SYMS_CvRegx64_YMM0H = 384` (scope `__anon43fde12c0603`) — AVX registers upper 128 bits
- L746 _enumerator_ `SYMS_CvRegx64_YMM1H = 385` (scope `__anon43fde12c0603`)
- L747 _enumerator_ `SYMS_CvRegx64_YMM2H = 386` (scope `__anon43fde12c0603`)
- L748 _enumerator_ `SYMS_CvRegx64_YMM3H = 387` (scope `__anon43fde12c0603`)
- L749 _enumerator_ `SYMS_CvRegx64_YMM4H = 388` (scope `__anon43fde12c0603`)
- L750 _enumerator_ `SYMS_CvRegx64_YMM5H = 389` (scope `__anon43fde12c0603`)
- L751 _enumerator_ `SYMS_CvRegx64_YMM6H = 390` (scope `__anon43fde12c0603`)
- L752 _enumerator_ `SYMS_CvRegx64_YMM7H = 391` (scope `__anon43fde12c0603`)
- L753 _enumerator_ `SYMS_CvRegx64_YMM8H = 392` (scope `__anon43fde12c0603`)
- L754 _enumerator_ `SYMS_CvRegx64_YMM9H = 393` (scope `__anon43fde12c0603`)
- L755 _enumerator_ `SYMS_CvRegx64_YMM10H = 394` (scope `__anon43fde12c0603`)
- L756 _enumerator_ `SYMS_CvRegx64_YMM11H = 395` (scope `__anon43fde12c0603`)
- L757 _enumerator_ `SYMS_CvRegx64_YMM12H = 396` (scope `__anon43fde12c0603`)
- L758 _enumerator_ `SYMS_CvRegx64_YMM13H = 397` (scope `__anon43fde12c0603`)
- L759 _enumerator_ `SYMS_CvRegx64_YMM14H = 398` (scope `__anon43fde12c0603`)
- L760 _enumerator_ `SYMS_CvRegx64_YMM15H = 399` (scope `__anon43fde12c0603`)
- L764 _enumerator_ `SYMS_CvRegx64_XMM0IL = 400` (scope `__anon43fde12c0603`) — Lower/upper 8 bytes of XMM registers.  Unlike CV_AMD64_XMM<regnum><H/L>, these ** values reprsesent the bit patterns of the registers as 64-bit integers, not ** the representation of these registers as a double.
- L765 _enumerator_ `SYMS_CvRegx64_XMM1IL = 401` (scope `__anon43fde12c0603`)
- L766 _enumerator_ `SYMS_CvRegx64_XMM2IL = 402` (scope `__anon43fde12c0603`)
- L767 _enumerator_ `SYMS_CvRegx64_XMM3IL = 403` (scope `__anon43fde12c0603`)
- L768 _enumerator_ `SYMS_CvRegx64_XMM4IL = 404` (scope `__anon43fde12c0603`)
- L769 _enumerator_ `SYMS_CvRegx64_XMM5IL = 405` (scope `__anon43fde12c0603`)
- L770 _enumerator_ `SYMS_CvRegx64_XMM6IL = 406` (scope `__anon43fde12c0603`)
- L771 _enumerator_ `SYMS_CvRegx64_XMM7IL = 407` (scope `__anon43fde12c0603`)
- L772 _enumerator_ `SYMS_CvRegx64_XMM8IL = 408` (scope `__anon43fde12c0603`)
- L773 _enumerator_ `SYMS_CvRegx64_XMM9IL = 409` (scope `__anon43fde12c0603`)
- L774 _enumerator_ `SYMS_CvRegx64_XMM10IL = 410` (scope `__anon43fde12c0603`)
- L775 _enumerator_ `SYMS_CvRegx64_XMM11IL = 411` (scope `__anon43fde12c0603`)
- L776 _enumerator_ `SYMS_CvRegx64_XMM12IL = 412` (scope `__anon43fde12c0603`)
- L777 _enumerator_ `SYMS_CvRegx64_XMM13IL = 413` (scope `__anon43fde12c0603`)
- L778 _enumerator_ `SYMS_CvRegx64_XMM14IL = 414` (scope `__anon43fde12c0603`)
- L779 _enumerator_ `SYMS_CvRegx64_XMM15IL = 415` (scope `__anon43fde12c0603`)
- L780 _enumerator_ `SYMS_CvRegx64_XMM0IH = 416` (scope `__anon43fde12c0603`)
- L781 _enumerator_ `SYMS_CvRegx64_XMM1IH = 417` (scope `__anon43fde12c0603`)
- L782 _enumerator_ `SYMS_CvRegx64_XMM2IH = 418` (scope `__anon43fde12c0603`)
- L783 _enumerator_ `SYMS_CvRegx64_XMM3IH = 419` (scope `__anon43fde12c0603`)
- L784 _enumerator_ `SYMS_CvRegx64_XMM4IH = 420` (scope `__anon43fde12c0603`)
- L785 _enumerator_ `SYMS_CvRegx64_XMM5IH = 421` (scope `__anon43fde12c0603`)
- L786 _enumerator_ `SYMS_CvRegx64_XMM6IH = 422` (scope `__anon43fde12c0603`)
- L787 _enumerator_ `SYMS_CvRegx64_XMM7IH = 423` (scope `__anon43fde12c0603`)
- L788 _enumerator_ `SYMS_CvRegx64_XMM8IH = 424` (scope `__anon43fde12c0603`)
- L789 _enumerator_ `SYMS_CvRegx64_XMM9IH = 425` (scope `__anon43fde12c0603`)
- L790 _enumerator_ `SYMS_CvRegx64_XMM10IH = 426` (scope `__anon43fde12c0603`)
- L791 _enumerator_ `SYMS_CvRegx64_XMM11IH = 427` (scope `__anon43fde12c0603`)
- L792 _enumerator_ `SYMS_CvRegx64_XMM12IH = 428` (scope `__anon43fde12c0603`)
- L793 _enumerator_ `SYMS_CvRegx64_XMM13IH = 429` (scope `__anon43fde12c0603`)
- L794 _enumerator_ `SYMS_CvRegx64_XMM14IH = 430` (scope `__anon43fde12c0603`)
- L795 _enumerator_ `SYMS_CvRegx64_XMM15IH = 431` (scope `__anon43fde12c0603`)
- L797 _enumerator_ `SYMS_CvRegx64_YMM0I0 = 432` (scope `__anon43fde12c0603`) — AVX integer registers
- L798 _enumerator_ `SYMS_CvRegx64_YMM0I1 = 433` (scope `__anon43fde12c0603`)
- L799 _enumerator_ `SYMS_CvRegx64_YMM0I2 = 434` (scope `__anon43fde12c0603`)
- L800 _enumerator_ `SYMS_CvRegx64_YMM0I3 = 435` (scope `__anon43fde12c0603`)
- L801 _enumerator_ `SYMS_CvRegx64_YMM1I0 = 436` (scope `__anon43fde12c0603`)
- L802 _enumerator_ `SYMS_CvRegx64_YMM1I1 = 437` (scope `__anon43fde12c0603`)
- L803 _enumerator_ `SYMS_CvRegx64_YMM1I2 = 438` (scope `__anon43fde12c0603`)
- L804 _enumerator_ `SYMS_CvRegx64_YMM1I3 = 439` (scope `__anon43fde12c0603`)
- L805 _enumerator_ `SYMS_CvRegx64_YMM2I0 = 440` (scope `__anon43fde12c0603`)
- L806 _enumerator_ `SYMS_CvRegx64_YMM2I1 = 441` (scope `__anon43fde12c0603`)
- L807 _enumerator_ `SYMS_CvRegx64_YMM2I2 = 442` (scope `__anon43fde12c0603`)
- L808 _enumerator_ `SYMS_CvRegx64_YMM2I3 = 443` (scope `__anon43fde12c0603`)
- L809 _enumerator_ `SYMS_CvRegx64_YMM3I0 = 444` (scope `__anon43fde12c0603`)
- L810 _enumerator_ `SYMS_CvRegx64_YMM3I1 = 445` (scope `__anon43fde12c0603`)
- L811 _enumerator_ `SYMS_CvRegx64_YMM3I2 = 446` (scope `__anon43fde12c0603`)
- L812 _enumerator_ `SYMS_CvRegx64_YMM3I3 = 447` (scope `__anon43fde12c0603`)
- L813 _enumerator_ `SYMS_CvRegx64_YMM4I0 = 448` (scope `__anon43fde12c0603`)
- L814 _enumerator_ `SYMS_CvRegx64_YMM4I1 = 449` (scope `__anon43fde12c0603`)
- L815 _enumerator_ `SYMS_CvRegx64_YMM4I2 = 450` (scope `__anon43fde12c0603`)
- L816 _enumerator_ `SYMS_CvRegx64_YMM4I3 = 451` (scope `__anon43fde12c0603`)
- L817 _enumerator_ `SYMS_CvRegx64_YMM5I0 = 452` (scope `__anon43fde12c0603`)
- L818 _enumerator_ `SYMS_CvRegx64_YMM5I1 = 453` (scope `__anon43fde12c0603`)
- L819 _enumerator_ `SYMS_CvRegx64_YMM5I2 = 454` (scope `__anon43fde12c0603`)
- L820 _enumerator_ `SYMS_CvRegx64_YMM5I3 = 455` (scope `__anon43fde12c0603`)
- L821 _enumerator_ `SYMS_CvRegx64_YMM6I0 = 456` (scope `__anon43fde12c0603`)
- L822 _enumerator_ `SYMS_CvRegx64_YMM6I1 = 457` (scope `__anon43fde12c0603`)
- L823 _enumerator_ `SYMS_CvRegx64_YMM6I2 = 458` (scope `__anon43fde12c0603`)
- L824 _enumerator_ `SYMS_CvRegx64_YMM6I3 = 459` (scope `__anon43fde12c0603`)
- L825 _enumerator_ `SYMS_CvRegx64_YMM7I0 = 460` (scope `__anon43fde12c0603`)
- L826 _enumerator_ `SYMS_CvRegx64_YMM7I1 = 461` (scope `__anon43fde12c0603`)
- L827 _enumerator_ `SYMS_CvRegx64_YMM7I2 = 462` (scope `__anon43fde12c0603`)
- L828 _enumerator_ `SYMS_CvRegx64_YMM7I3 = 463` (scope `__anon43fde12c0603`)
- L829 _enumerator_ `SYMS_CvRegx64_YMM8I0 = 464` (scope `__anon43fde12c0603`)
- L830 _enumerator_ `SYMS_CvRegx64_YMM8I1 = 465` (scope `__anon43fde12c0603`)
- L831 _enumerator_ `SYMS_CvRegx64_YMM8I2 = 466` (scope `__anon43fde12c0603`)
- L832 _enumerator_ `SYMS_CvRegx64_YMM8I3 = 467` (scope `__anon43fde12c0603`)
- L833 _enumerator_ `SYMS_CvRegx64_YMM9I0 = 468` (scope `__anon43fde12c0603`)
- L834 _enumerator_ `SYMS_CvRegx64_YMM9I1 = 469` (scope `__anon43fde12c0603`)
- L835 _enumerator_ `SYMS_CvRegx64_YMM9I2 = 470` (scope `__anon43fde12c0603`)
- L836 _enumerator_ `SYMS_CvRegx64_YMM9I3 = 471` (scope `__anon43fde12c0603`)
- L837 _enumerator_ `SYMS_CvRegx64_YMM10I0 = 472` (scope `__anon43fde12c0603`)
- L838 _enumerator_ `SYMS_CvRegx64_YMM10I1 = 473` (scope `__anon43fde12c0603`)
- L839 _enumerator_ `SYMS_CvRegx64_YMM10I2 = 474` (scope `__anon43fde12c0603`)
- L840 _enumerator_ `SYMS_CvRegx64_YMM10I3 = 475` (scope `__anon43fde12c0603`)
- L841 _enumerator_ `SYMS_CvRegx64_YMM11I0 = 476` (scope `__anon43fde12c0603`)
- L842 _enumerator_ `SYMS_CvRegx64_YMM11I1 = 477` (scope `__anon43fde12c0603`)
- L843 _enumerator_ `SYMS_CvRegx64_YMM11I2 = 478` (scope `__anon43fde12c0603`)
- L844 _enumerator_ `SYMS_CvRegx64_YMM11I3 = 479` (scope `__anon43fde12c0603`)
- L845 _enumerator_ `SYMS_CvRegx64_YMM12I0 = 480` (scope `__anon43fde12c0603`)
- L846 _enumerator_ `SYMS_CvRegx64_YMM12I1 = 481` (scope `__anon43fde12c0603`)
- L847 _enumerator_ `SYMS_CvRegx64_YMM12I2 = 482` (scope `__anon43fde12c0603`)
- L848 _enumerator_ `SYMS_CvRegx64_YMM12I3 = 483` (scope `__anon43fde12c0603`)
- L849 _enumerator_ `SYMS_CvRegx64_YMM13I0 = 484` (scope `__anon43fde12c0603`)
- L850 _enumerator_ `SYMS_CvRegx64_YMM13I1 = 485` (scope `__anon43fde12c0603`)
- L851 _enumerator_ `SYMS_CvRegx64_YMM13I2 = 486` (scope `__anon43fde12c0603`)
- L852 _enumerator_ `SYMS_CvRegx64_YMM13I3 = 487` (scope `__anon43fde12c0603`)
- L853 _enumerator_ `SYMS_CvRegx64_YMM14I0 = 488` (scope `__anon43fde12c0603`)
- L854 _enumerator_ `SYMS_CvRegx64_YMM14I1 = 489` (scope `__anon43fde12c0603`)
- L855 _enumerator_ `SYMS_CvRegx64_YMM14I2 = 490` (scope `__anon43fde12c0603`)
- L856 _enumerator_ `SYMS_CvRegx64_YMM14I3 = 491` (scope `__anon43fde12c0603`)
- L857 _enumerator_ `SYMS_CvRegx64_YMM15I0 = 492` (scope `__anon43fde12c0603`)
- L858 _enumerator_ `SYMS_CvRegx64_YMM15I1 = 493` (scope `__anon43fde12c0603`)
- L859 _enumerator_ `SYMS_CvRegx64_YMM15I2 = 494` (scope `__anon43fde12c0603`)
- L860 _enumerator_ `SYMS_CvRegx64_YMM15I3 = 495` (scope `__anon43fde12c0603`)
- L862 _enumerator_ `SYMS_CvRegx64_YMM0F0 = 496` (scope `__anon43fde12c0603`) — AVX floating-point single precise registers
- L863 _enumerator_ `SYMS_CvRegx64_YMM0F1 = 497` (scope `__anon43fde12c0603`)
- L864 _enumerator_ `SYMS_CvRegx64_YMM0F2 = 498` (scope `__anon43fde12c0603`)
- L865 _enumerator_ `SYMS_CvRegx64_YMM0F3 = 499` (scope `__anon43fde12c0603`)
- L866 _enumerator_ `SYMS_CvRegx64_YMM0F4 = 500` (scope `__anon43fde12c0603`)
- L867 _enumerator_ `SYMS_CvRegx64_YMM0F5 = 501` (scope `__anon43fde12c0603`)
- L868 _enumerator_ `SYMS_CvRegx64_YMM0F6 = 502` (scope `__anon43fde12c0603`)
- L869 _enumerator_ `SYMS_CvRegx64_YMM0F7 = 503` (scope `__anon43fde12c0603`)
- L870 _enumerator_ `SYMS_CvRegx64_YMM1F0 = 504` (scope `__anon43fde12c0603`)
- L871 _enumerator_ `SYMS_CvRegx64_YMM1F1 = 505` (scope `__anon43fde12c0603`)
- L872 _enumerator_ `SYMS_CvRegx64_YMM1F2 = 506` (scope `__anon43fde12c0603`)
- L873 _enumerator_ `SYMS_CvRegx64_YMM1F3 = 507` (scope `__anon43fde12c0603`)
- L874 _enumerator_ `SYMS_CvRegx64_YMM1F4 = 508` (scope `__anon43fde12c0603`)
- L875 _enumerator_ `SYMS_CvRegx64_YMM1F5 = 509` (scope `__anon43fde12c0603`)
- L876 _enumerator_ `SYMS_CvRegx64_YMM1F6 = 510` (scope `__anon43fde12c0603`)
- L877 _enumerator_ `SYMS_CvRegx64_YMM1F7 = 511` (scope `__anon43fde12c0603`)
- L878 _enumerator_ `SYMS_CvRegx64_YMM2F0 = 512` (scope `__anon43fde12c0603`)
- L879 _enumerator_ `SYMS_CvRegx64_YMM2F1 = 513` (scope `__anon43fde12c0603`)
- L880 _enumerator_ `SYMS_CvRegx64_YMM2F2 = 514` (scope `__anon43fde12c0603`)
- L881 _enumerator_ `SYMS_CvRegx64_YMM2F3 = 515` (scope `__anon43fde12c0603`)
- L882 _enumerator_ `SYMS_CvRegx64_YMM2F4 = 516` (scope `__anon43fde12c0603`)
- L883 _enumerator_ `SYMS_CvRegx64_YMM2F5 = 517` (scope `__anon43fde12c0603`)
- L884 _enumerator_ `SYMS_CvRegx64_YMM2F6 = 518` (scope `__anon43fde12c0603`)
- L885 _enumerator_ `SYMS_CvRegx64_YMM2F7 = 519` (scope `__anon43fde12c0603`)
- L886 _enumerator_ `SYMS_CvRegx64_YMM3F0 = 520` (scope `__anon43fde12c0603`)
- L887 _enumerator_ `SYMS_CvRegx64_YMM3F1 = 521` (scope `__anon43fde12c0603`)
- L888 _enumerator_ `SYMS_CvRegx64_YMM3F2 = 522` (scope `__anon43fde12c0603`)
- L889 _enumerator_ `SYMS_CvRegx64_YMM3F3 = 523` (scope `__anon43fde12c0603`)
- L890 _enumerator_ `SYMS_CvRegx64_YMM3F4 = 524` (scope `__anon43fde12c0603`)
- L891 _enumerator_ `SYMS_CvRegx64_YMM3F5 = 525` (scope `__anon43fde12c0603`)
- L892 _enumerator_ `SYMS_CvRegx64_YMM3F6 = 526` (scope `__anon43fde12c0603`)
- L893 _enumerator_ `SYMS_CvRegx64_YMM3F7 = 527` (scope `__anon43fde12c0603`)
- L894 _enumerator_ `SYMS_CvRegx64_YMM4F0 = 528` (scope `__anon43fde12c0603`)
- L895 _enumerator_ `SYMS_CvRegx64_YMM4F1 = 529` (scope `__anon43fde12c0603`)
- L896 _enumerator_ `SYMS_CvRegx64_YMM4F2 = 530` (scope `__anon43fde12c0603`)
- L897 _enumerator_ `SYMS_CvRegx64_YMM4F3 = 531` (scope `__anon43fde12c0603`)
- L898 _enumerator_ `SYMS_CvRegx64_YMM4F4 = 532` (scope `__anon43fde12c0603`)
- L899 _enumerator_ `SYMS_CvRegx64_YMM4F5 = 533` (scope `__anon43fde12c0603`)
- L900 _enumerator_ `SYMS_CvRegx64_YMM4F6 = 534` (scope `__anon43fde12c0603`)
- L901 _enumerator_ `SYMS_CvRegx64_YMM4F7 = 535` (scope `__anon43fde12c0603`)
- L902 _enumerator_ `SYMS_CvRegx64_YMM5F0 = 536` (scope `__anon43fde12c0603`)
- L903 _enumerator_ `SYMS_CvRegx64_YMM5F1 = 537` (scope `__anon43fde12c0603`)
- L904 _enumerator_ `SYMS_CvRegx64_YMM5F2 = 538` (scope `__anon43fde12c0603`)
- L905 _enumerator_ `SYMS_CvRegx64_YMM5F3 = 539` (scope `__anon43fde12c0603`)
- L906 _enumerator_ `SYMS_CvRegx64_YMM5F4 = 540` (scope `__anon43fde12c0603`)
- L907 _enumerator_ `SYMS_CvRegx64_YMM5F5 = 541` (scope `__anon43fde12c0603`)
- L908 _enumerator_ `SYMS_CvRegx64_YMM5F6 = 542` (scope `__anon43fde12c0603`)
- L909 _enumerator_ `SYMS_CvRegx64_YMM5F7 = 543` (scope `__anon43fde12c0603`)
- L910 _enumerator_ `SYMS_CvRegx64_YMM6F0 = 544` (scope `__anon43fde12c0603`)
- L911 _enumerator_ `SYMS_CvRegx64_YMM6F1 = 545` (scope `__anon43fde12c0603`)
- L912 _enumerator_ `SYMS_CvRegx64_YMM6F2 = 546` (scope `__anon43fde12c0603`)
- L913 _enumerator_ `SYMS_CvRegx64_YMM6F3 = 547` (scope `__anon43fde12c0603`)
- L914 _enumerator_ `SYMS_CvRegx64_YMM6F4 = 548` (scope `__anon43fde12c0603`)
- L915 _enumerator_ `SYMS_CvRegx64_YMM6F5 = 549` (scope `__anon43fde12c0603`)
- L916 _enumerator_ `SYMS_CvRegx64_YMM6F6 = 550` (scope `__anon43fde12c0603`)
- L917 _enumerator_ `SYMS_CvRegx64_YMM6F7 = 551` (scope `__anon43fde12c0603`)
- L918 _enumerator_ `SYMS_CvRegx64_YMM7F0 = 552` (scope `__anon43fde12c0603`)
- L919 _enumerator_ `SYMS_CvRegx64_YMM7F1 = 553` (scope `__anon43fde12c0603`)
- L920 _enumerator_ `SYMS_CvRegx64_YMM7F2 = 554` (scope `__anon43fde12c0603`)
- L921 _enumerator_ `SYMS_CvRegx64_YMM7F3 = 555` (scope `__anon43fde12c0603`)
- L922 _enumerator_ `SYMS_CvRegx64_YMM7F4 = 556` (scope `__anon43fde12c0603`)
- L923 _enumerator_ `SYMS_CvRegx64_YMM7F5 = 557` (scope `__anon43fde12c0603`)
- L924 _enumerator_ `SYMS_CvRegx64_YMM7F6 = 558` (scope `__anon43fde12c0603`)
- L925 _enumerator_ `SYMS_CvRegx64_YMM7F7 = 559` (scope `__anon43fde12c0603`)
- L926 _enumerator_ `SYMS_CvRegx64_YMM8F0 = 560` (scope `__anon43fde12c0603`)
- L927 _enumerator_ `SYMS_CvRegx64_YMM8F1 = 561` (scope `__anon43fde12c0603`)
- L928 _enumerator_ `SYMS_CvRegx64_YMM8F2 = 562` (scope `__anon43fde12c0603`)
- L929 _enumerator_ `SYMS_CvRegx64_YMM8F3 = 563` (scope `__anon43fde12c0603`)
- L930 _enumerator_ `SYMS_CvRegx64_YMM8F4 = 564` (scope `__anon43fde12c0603`)
- L931 _enumerator_ `SYMS_CvRegx64_YMM8F5 = 565` (scope `__anon43fde12c0603`)
- L932 _enumerator_ `SYMS_CvRegx64_YMM8F6 = 566` (scope `__anon43fde12c0603`)
- L933 _enumerator_ `SYMS_CvRegx64_YMM8F7 = 567` (scope `__anon43fde12c0603`)
- L934 _enumerator_ `SYMS_CvRegx64_YMM9F0 = 568` (scope `__anon43fde12c0603`)
- L935 _enumerator_ `SYMS_CvRegx64_YMM9F1 = 569` (scope `__anon43fde12c0603`)
- L936 _enumerator_ `SYMS_CvRegx64_YMM9F2 = 570` (scope `__anon43fde12c0603`)
- L937 _enumerator_ `SYMS_CvRegx64_YMM9F3 = 571` (scope `__anon43fde12c0603`)
- L938 _enumerator_ `SYMS_CvRegx64_YMM9F4 = 572` (scope `__anon43fde12c0603`)
- L939 _enumerator_ `SYMS_CvRegx64_YMM9F5 = 573` (scope `__anon43fde12c0603`)
- L940 _enumerator_ `SYMS_CvRegx64_YMM9F6 = 574` (scope `__anon43fde12c0603`)
- L941 _enumerator_ `SYMS_CvRegx64_YMM9F7 = 575` (scope `__anon43fde12c0603`)
- L942 _enumerator_ `SYMS_CvRegx64_YMM10F0 = 576` (scope `__anon43fde12c0603`)
- L943 _enumerator_ `SYMS_CvRegx64_YMM10F1 = 577` (scope `__anon43fde12c0603`)
- L944 _enumerator_ `SYMS_CvRegx64_YMM10F2 = 578` (scope `__anon43fde12c0603`)
- L945 _enumerator_ `SYMS_CvRegx64_YMM10F3 = 579` (scope `__anon43fde12c0603`)
- L946 _enumerator_ `SYMS_CvRegx64_YMM10F4 = 580` (scope `__anon43fde12c0603`)
- L947 _enumerator_ `SYMS_CvRegx64_YMM10F5 = 581` (scope `__anon43fde12c0603`)
- L948 _enumerator_ `SYMS_CvRegx64_YMM10F6 = 582` (scope `__anon43fde12c0603`)
- L949 _enumerator_ `SYMS_CvRegx64_YMM10F7 = 583` (scope `__anon43fde12c0603`)
- L950 _enumerator_ `SYMS_CvRegx64_YMM11F0 = 584` (scope `__anon43fde12c0603`)
- L951 _enumerator_ `SYMS_CvRegx64_YMM11F1 = 585` (scope `__anon43fde12c0603`)
- L952 _enumerator_ `SYMS_CvRegx64_YMM11F2 = 586` (scope `__anon43fde12c0603`)
- L953 _enumerator_ `SYMS_CvRegx64_YMM11F3 = 587` (scope `__anon43fde12c0603`)
- L954 _enumerator_ `SYMS_CvRegx64_YMM11F4 = 588` (scope `__anon43fde12c0603`)
- L955 _enumerator_ `SYMS_CvRegx64_YMM11F5 = 589` (scope `__anon43fde12c0603`)
- L956 _enumerator_ `SYMS_CvRegx64_YMM11F6 = 590` (scope `__anon43fde12c0603`)
- L957 _enumerator_ `SYMS_CvRegx64_YMM11F7 = 591` (scope `__anon43fde12c0603`)
- L958 _enumerator_ `SYMS_CvRegx64_YMM12F0 = 592` (scope `__anon43fde12c0603`)
- L959 _enumerator_ `SYMS_CvRegx64_YMM12F1 = 593` (scope `__anon43fde12c0603`)
- L960 _enumerator_ `SYMS_CvRegx64_YMM12F2 = 594` (scope `__anon43fde12c0603`)
- L961 _enumerator_ `SYMS_CvRegx64_YMM12F3 = 595` (scope `__anon43fde12c0603`)
- L962 _enumerator_ `SYMS_CvRegx64_YMM12F4 = 596` (scope `__anon43fde12c0603`)
- L963 _enumerator_ `SYMS_CvRegx64_YMM12F5 = 597` (scope `__anon43fde12c0603`)
- L964 _enumerator_ `SYMS_CvRegx64_YMM12F6 = 598` (scope `__anon43fde12c0603`)
- L965 _enumerator_ `SYMS_CvRegx64_YMM12F7 = 599` (scope `__anon43fde12c0603`)
- L966 _enumerator_ `SYMS_CvRegx64_YMM13F0 = 600` (scope `__anon43fde12c0603`)
- L967 _enumerator_ `SYMS_CvRegx64_YMM13F1 = 601` (scope `__anon43fde12c0603`)
- L968 _enumerator_ `SYMS_CvRegx64_YMM13F2 = 602` (scope `__anon43fde12c0603`)
- L969 _enumerator_ `SYMS_CvRegx64_YMM13F3 = 603` (scope `__anon43fde12c0603`)
- L970 _enumerator_ `SYMS_CvRegx64_YMM13F4 = 604` (scope `__anon43fde12c0603`)
- L971 _enumerator_ `SYMS_CvRegx64_YMM13F5 = 605` (scope `__anon43fde12c0603`)
- L972 _enumerator_ `SYMS_CvRegx64_YMM13F6 = 606` (scope `__anon43fde12c0603`)
- L973 _enumerator_ `SYMS_CvRegx64_YMM13F7 = 607` (scope `__anon43fde12c0603`)
- L974 _enumerator_ `SYMS_CvRegx64_YMM14F0 = 608` (scope `__anon43fde12c0603`)
- L975 _enumerator_ `SYMS_CvRegx64_YMM14F1 = 609` (scope `__anon43fde12c0603`)
- L976 _enumerator_ `SYMS_CvRegx64_YMM14F2 = 610` (scope `__anon43fde12c0603`)
- L977 _enumerator_ `SYMS_CvRegx64_YMM14F3 = 611` (scope `__anon43fde12c0603`)
- L978 _enumerator_ `SYMS_CvRegx64_YMM14F4 = 612` (scope `__anon43fde12c0603`)
- L979 _enumerator_ `SYMS_CvRegx64_YMM14F5 = 613` (scope `__anon43fde12c0603`)
- L980 _enumerator_ `SYMS_CvRegx64_YMM14F6 = 614` (scope `__anon43fde12c0603`)
- L981 _enumerator_ `SYMS_CvRegx64_YMM14F7 = 615` (scope `__anon43fde12c0603`)
- L982 _enumerator_ `SYMS_CvRegx64_YMM15F0 = 616` (scope `__anon43fde12c0603`)
- L983 _enumerator_ `SYMS_CvRegx64_YMM15F1 = 617` (scope `__anon43fde12c0603`)
- L984 _enumerator_ `SYMS_CvRegx64_YMM15F2 = 618` (scope `__anon43fde12c0603`)
- L985 _enumerator_ `SYMS_CvRegx64_YMM15F3 = 619` (scope `__anon43fde12c0603`)
- L986 _enumerator_ `SYMS_CvRegx64_YMM15F4 = 620` (scope `__anon43fde12c0603`)
- L987 _enumerator_ `SYMS_CvRegx64_YMM15F5 = 621` (scope `__anon43fde12c0603`)
- L988 _enumerator_ `SYMS_CvRegx64_YMM15F6 = 622` (scope `__anon43fde12c0603`)
- L989 _enumerator_ `SYMS_CvRegx64_YMM15F7 = 623` (scope `__anon43fde12c0603`)
- L991 _enumerator_ `SYMS_CvRegx64_YMM0D0 = 624` (scope `__anon43fde12c0603`) — AVX floating-point double precise registers
- L992 _enumerator_ `SYMS_CvRegx64_YMM0D1 = 625` (scope `__anon43fde12c0603`)
- L993 _enumerator_ `SYMS_CvRegx64_YMM0D2 = 626` (scope `__anon43fde12c0603`)
- L994 _enumerator_ `SYMS_CvRegx64_YMM0D3 = 627` (scope `__anon43fde12c0603`)
- L995 _enumerator_ `SYMS_CvRegx64_YMM1D0 = 628` (scope `__anon43fde12c0603`)
- L996 _enumerator_ `SYMS_CvRegx64_YMM1D1 = 629` (scope `__anon43fde12c0603`)
- L997 _enumerator_ `SYMS_CvRegx64_YMM1D2 = 630` (scope `__anon43fde12c0603`)
- L998 _enumerator_ `SYMS_CvRegx64_YMM1D3 = 631` (scope `__anon43fde12c0603`)
- L999 _enumerator_ `SYMS_CvRegx64_YMM2D0 = 632` (scope `__anon43fde12c0603`)
- L1000 _enumerator_ `SYMS_CvRegx64_YMM2D1 = 633` (scope `__anon43fde12c0603`)
- L1001 _enumerator_ `SYMS_CvRegx64_YMM2D2 = 634` (scope `__anon43fde12c0603`)
- L1002 _enumerator_ `SYMS_CvRegx64_YMM2D3 = 635` (scope `__anon43fde12c0603`)
- L1003 _enumerator_ `SYMS_CvRegx64_YMM3D0 = 636` (scope `__anon43fde12c0603`)
- L1004 _enumerator_ `SYMS_CvRegx64_YMM3D1 = 637` (scope `__anon43fde12c0603`)
- L1005 _enumerator_ `SYMS_CvRegx64_YMM3D2 = 638` (scope `__anon43fde12c0603`)
- L1006 _enumerator_ `SYMS_CvRegx64_YMM3D3 = 639` (scope `__anon43fde12c0603`)
- L1007 _enumerator_ `SYMS_CvRegx64_YMM4D0 = 640` (scope `__anon43fde12c0603`)
- L1008 _enumerator_ `SYMS_CvRegx64_YMM4D1 = 641` (scope `__anon43fde12c0603`)
- L1009 _enumerator_ `SYMS_CvRegx64_YMM4D2 = 642` (scope `__anon43fde12c0603`)
- L1010 _enumerator_ `SYMS_CvRegx64_YMM4D3 = 643` (scope `__anon43fde12c0603`)
- L1011 _enumerator_ `SYMS_CvRegx64_YMM5D0 = 644` (scope `__anon43fde12c0603`)
- L1012 _enumerator_ `SYMS_CvRegx64_YMM5D1 = 645` (scope `__anon43fde12c0603`)
- L1013 _enumerator_ `SYMS_CvRegx64_YMM5D2 = 646` (scope `__anon43fde12c0603`)
- L1014 _enumerator_ `SYMS_CvRegx64_YMM5D3 = 647` (scope `__anon43fde12c0603`)
- L1015 _enumerator_ `SYMS_CvRegx64_YMM6D0 = 648` (scope `__anon43fde12c0603`)
- L1016 _enumerator_ `SYMS_CvRegx64_YMM6D1 = 649` (scope `__anon43fde12c0603`)
- L1017 _enumerator_ `SYMS_CvRegx64_YMM6D2 = 650` (scope `__anon43fde12c0603`)
- L1018 _enumerator_ `SYMS_CvRegx64_YMM6D3 = 651` (scope `__anon43fde12c0603`)
- L1019 _enumerator_ `SYMS_CvRegx64_YMM7D0 = 652` (scope `__anon43fde12c0603`)
- L1020 _enumerator_ `SYMS_CvRegx64_YMM7D1 = 653` (scope `__anon43fde12c0603`)
- L1021 _enumerator_ `SYMS_CvRegx64_YMM7D2 = 654` (scope `__anon43fde12c0603`)
- L1022 _enumerator_ `SYMS_CvRegx64_YMM7D3 = 655` (scope `__anon43fde12c0603`)
- L1023 _enumerator_ `SYMS_CvRegx64_YMM8D0 = 656` (scope `__anon43fde12c0603`)
- L1024 _enumerator_ `SYMS_CvRegx64_YMM8D1 = 657` (scope `__anon43fde12c0603`)
- L1025 _enumerator_ `SYMS_CvRegx64_YMM8D2 = 658` (scope `__anon43fde12c0603`)
- L1026 _enumerator_ `SYMS_CvRegx64_YMM8D3 = 659` (scope `__anon43fde12c0603`)
- L1027 _enumerator_ `SYMS_CvRegx64_YMM9D0 = 660` (scope `__anon43fde12c0603`)
- L1028 _enumerator_ `SYMS_CvRegx64_YMM9D1 = 661` (scope `__anon43fde12c0603`)
- L1029 _enumerator_ `SYMS_CvRegx64_YMM9D2 = 662` (scope `__anon43fde12c0603`)
- L1030 _enumerator_ `SYMS_CvRegx64_YMM9D3 = 663` (scope `__anon43fde12c0603`)
- L1031 _enumerator_ `SYMS_CvRegx64_YMM10D0 = 664` (scope `__anon43fde12c0603`)
- L1032 _enumerator_ `SYMS_CvRegx64_YMM10D1 = 665` (scope `__anon43fde12c0603`)
- L1033 _enumerator_ `SYMS_CvRegx64_YMM10D2 = 666` (scope `__anon43fde12c0603`)
- L1034 _enumerator_ `SYMS_CvRegx64_YMM10D3 = 667` (scope `__anon43fde12c0603`)
- L1035 _enumerator_ `SYMS_CvRegx64_YMM11D0 = 668` (scope `__anon43fde12c0603`)
- L1036 _enumerator_ `SYMS_CvRegx64_YMM11D1 = 669` (scope `__anon43fde12c0603`)
- L1037 _enumerator_ `SYMS_CvRegx64_YMM11D2 = 670` (scope `__anon43fde12c0603`)
- L1038 _enumerator_ `SYMS_CvRegx64_YMM11D3 = 671` (scope `__anon43fde12c0603`)
- L1039 _enumerator_ `SYMS_CvRegx64_YMM12D0 = 672` (scope `__anon43fde12c0603`)
- L1040 _enumerator_ `SYMS_CvRegx64_YMM12D1 = 673` (scope `__anon43fde12c0603`)
- L1041 _enumerator_ `SYMS_CvRegx64_YMM12D2 = 674` (scope `__anon43fde12c0603`)
- L1042 _enumerator_ `SYMS_CvRegx64_YMM12D3 = 675` (scope `__anon43fde12c0603`)
- L1043 _enumerator_ `SYMS_CvRegx64_YMM13D0 = 676` (scope `__anon43fde12c0603`)
- L1044 _enumerator_ `SYMS_CvRegx64_YMM13D1 = 677` (scope `__anon43fde12c0603`)
- L1045 _enumerator_ `SYMS_CvRegx64_YMM13D2 = 678` (scope `__anon43fde12c0603`)
- L1046 _enumerator_ `SYMS_CvRegx64_YMM13D3 = 679` (scope `__anon43fde12c0603`)
- L1047 _enumerator_ `SYMS_CvRegx64_YMM14D0 = 680` (scope `__anon43fde12c0603`)
- L1048 _enumerator_ `SYMS_CvRegx64_YMM14D1 = 681` (scope `__anon43fde12c0603`)
- L1049 _enumerator_ `SYMS_CvRegx64_YMM14D2 = 682` (scope `__anon43fde12c0603`)
- L1050 _enumerator_ `SYMS_CvRegx64_YMM14D3 = 683` (scope `__anon43fde12c0603`)
- L1051 _enumerator_ `SYMS_CvRegx64_YMM15D0 = 684` (scope `__anon43fde12c0603`)
- L1052 _enumerator_ `SYMS_CvRegx64_YMM15D1 = 685` (scope `__anon43fde12c0603`)
- L1053 _enumerator_ `SYMS_CvRegx64_YMM15D2 = 686` (scope `__anon43fde12c0603`)
- L1054 _enumerator_ `SYMS_CvRegx64_YMM15D3 = 687` (scope `__anon43fde12c0603`)
- L1055 _enumerator_ `SYMS_CvRegx64_COUNT = 613` (scope `__anon43fde12c0603`)
- L1057 _typedef_ `typedef SYMS_U32 SYMS_CvSignature;`
- L1059 _enumerator_ `SYMS_CvSignature_C6 = 0` (scope `__anon43fde12c0703`)
- L1060 _enumerator_ `SYMS_CvSignature_C7 = 1` (scope `__anon43fde12c0703`)
- L1061 _enumerator_ `SYMS_CvSignature_C11 = 2` (scope `__anon43fde12c0703`)
- L1062 _enumerator_ `SYMS_CvSignature_C13 = 4` (scope `__anon43fde12c0703`)
- L1063 _enumerator_ `SYMS_CvSignature_RESERVED = 5` (scope `__anon43fde12c0703`)
- L1064 _enumerator_ `SYMS_CvSignature_COUNT = 5` (scope `__anon43fde12c0703`)
- L1066 _typedef_ `typedef SYMS_U16 SYMS_CvSymKind;`
- L1068 _enumerator_ `SYMS_CvSymKind_NULL = 0` (scope `__anon43fde12c0803`)
- L1069 _enumerator_ `SYMS_CvSymKind_COMPILE = 0x0001` (scope `__anon43fde12c0803`)
- L1071 _enumerator_ `SYMS_CvSymKind_REGISTER_16t = 0x0002` (scope `__anon43fde12c0803`) — Compile flags symbol
- L1073 _enumerator_ `SYMS_CvSymKind_CONSTANT_16t = 0x0003` (scope `__anon43fde12c0803`) — Register variable
- L1075 _enumerator_ `SYMS_CvSymKind_UDT_16t = 0x0004` (scope `__anon43fde12c0803`) — constant symbol
- L1077 _enumerator_ `SYMS_CvSymKind_SSEARCH = 0x0005` (scope `__anon43fde12c0803`) — User defined type
- L1079 _enumerator_ `SYMS_CvSymKind_END = 0x0006` (scope `__anon43fde12c0803`) — Start Search
- L1081 _enumerator_ `SYMS_CvSymKind_SKIP = 0x0007` (scope `__anon43fde12c0803`) — Block, procedure, "with" or thunk end
- L1083 _enumerator_ `SYMS_CvSymKind_CVRESERVE = 0x0008` (scope `__anon43fde12c0803`) — Reserve symbol space in $$Symbols table
- L1085 _enumerator_ `SYMS_CvSymKind_OBJNAME_ST = 0x0009` (scope `__anon43fde12c0803`) — Reserved symbol for CV internal use
- L1087 _enumerator_ `SYMS_CvSymKind_ENDARG = 0x000a` (scope `__anon43fde12c0803`) — path to object file name
- L1089 _enumerator_ `SYMS_CvSymKind_COBOLUDT_16t = 0x000b` (scope `__anon43fde12c0803`) — end of argument/return list
- L1091 _enumerator_ `SYMS_CvSymKind_MANYREG_16t = 0x000c` (scope `__anon43fde12c0803`) — special UDT for cobol that does not symbol pack
- L1093 _enumerator_ `SYMS_CvSymKind_RETURN = 0x000d` (scope `__anon43fde12c0803`) — multiple register variable
- L1095 _enumerator_ `SYMS_CvSymKind_ENTRYTHIS = 0x000e` (scope `__anon43fde12c0803`) — return description symbol
- L1097 _enumerator_ `SYMS_CvSymKind_BPREL16 = 0x0100` (scope `__anon43fde12c0803`) — description of this pointer on entry
- L1099 _enumerator_ `SYMS_CvSymKind_LDATA16 = 0x0101` (scope `__anon43fde12c0803`) — BP-relative
- L1101 _enumerator_ `SYMS_CvSymKind_GDATA16 = 0x0102` (scope `__anon43fde12c0803`) — Module-static symbol
- L1103 _enumerator_ `SYMS_CvSymKind_PUB16 = 0x0103` (scope `__anon43fde12c0803`) — Global data symbol
- L1105 _enumerator_ `SYMS_CvSymKind_LPROC16 = 0x0104` (scope `__anon43fde12c0803`) — a public symbol
- L1107 _enumerator_ `SYMS_CvSymKind_GPROC16 = 0x0105` (scope `__anon43fde12c0803`) — Local procedure start
- L1109 _enumerator_ `SYMS_CvSymKind_THUNK16 = 0x0106` (scope `__anon43fde12c0803`) — Global procedure start
- L1111 _enumerator_ `SYMS_CvSymKind_BLOCK16 = 0x0107` (scope `__anon43fde12c0803`) — Thunk Start
- L1113 _enumerator_ `SYMS_CvSymKind_WITH16 = 0x0108` (scope `__anon43fde12c0803`) — block start
- L1115 _enumerator_ `SYMS_CvSymKind_LABEL16 = 0x0109` (scope `__anon43fde12c0803`) — with start
- L1117 _enumerator_ `SYMS_CvSymKind_CEXMODEL16 = 0x010a` (scope `__anon43fde12c0803`) — code label
- L1119 _enumerator_ `SYMS_CvSymKind_VFTABLE16 = 0x010b` (scope `__anon43fde12c0803`) — change execution model
- L1121 _enumerator_ `SYMS_CvSymKind_REGREL16 = 0x010c` (scope `__anon43fde12c0803`) — address of virtual function table
- L1123 _enumerator_ `SYMS_CvSymKind_BPREL32_16t = 0x0200` (scope `__anon43fde12c0803`) — register relative address
- L1125 _enumerator_ `SYMS_CvSymKind_LDATA32_16t = 0x0201` (scope `__anon43fde12c0803`) — BP-relative
- L1127 _enumerator_ `SYMS_CvSymKind_GDATA32_16t = 0x0202` (scope `__anon43fde12c0803`) — Module-static symbol
- L1129 _enumerator_ `SYMS_CvSymKind_PUB32_16t = 0x0203` (scope `__anon43fde12c0803`) — Global data symbol
- L1131 _enumerator_ `SYMS_CvSymKind_LPROC32_16t = 0x0204` (scope `__anon43fde12c0803`) — a public symbol (CV internal reserved)
- L1133 _enumerator_ `SYMS_CvSymKind_GPROC32_16t = 0x0205` (scope `__anon43fde12c0803`) — Local procedure start
- L1135 _enumerator_ `SYMS_CvSymKind_THUNK32_ST = 0x0206` (scope `__anon43fde12c0803`) — Global procedure start
- L1137 _enumerator_ `SYMS_CvSymKind_BLOCK32_ST = 0x0207` (scope `__anon43fde12c0803`) — Thunk Start
- L1139 _enumerator_ `SYMS_CvSymKind_WITH32_ST = 0x0208` (scope `__anon43fde12c0803`) — block start
- L1141 _enumerator_ `SYMS_CvSymKind_LABEL32_ST = 0x0209` (scope `__anon43fde12c0803`) — with start
- L1143 _enumerator_ `SYMS_CvSymKind_CEXMODEL32 = 0x020a` (scope `__anon43fde12c0803`) — code label
- L1145 _enumerator_ `SYMS_CvSymKind_VFTABLE32_16t = 0x020b` (scope `__anon43fde12c0803`) — change execution model
- L1147 _enumerator_ `SYMS_CvSymKind_REGREL32_16t = 0x020c` (scope `__anon43fde12c0803`) — address of virtual function table
- L1149 _enumerator_ `SYMS_CvSymKind_LTHREAD32_16t = 0x020d` (scope `__anon43fde12c0803`) — register relative address
- L1151 _enumerator_ `SYMS_CvSymKind_GTHREAD32_16t = 0x020e` (scope `__anon43fde12c0803`) — static thread storage
- L1153 _enumerator_ `SYMS_CvSymKind_SLINK32 = 0x020f` (scope `__anon43fde12c0803`) — static thread storage
- L1155 _enumerator_ `SYMS_CvSymKind_LPROCMIPS_16t = 0x0300` (scope `__anon43fde12c0803`) — static link for MIPS EH implementation
- L1157 _enumerator_ `SYMS_CvSymKind_GPROCMIPS_16t = 0x0301` (scope `__anon43fde12c0803`) — Local procedure start
- L1159 _enumerator_ `SYMS_CvSymKind_PROCREF_ST = 0x0400` (scope `__anon43fde12c0803`) — Global procedure start
- L1161 _enumerator_ `SYMS_CvSymKind_DATAREF_ST = 0x0401` (scope `__anon43fde12c0803`) — Reference to a procedure
- L1163 _enumerator_ `SYMS_CvSymKind_ALIGN = 0x0402` (scope `__anon43fde12c0803`) — Reference to data
- L1165 _enumerator_ `SYMS_CvSymKind_LPROCREF_ST = 0x0403` (scope `__anon43fde12c0803`) — Used for page alignment of symbols
- L1167 _enumerator_ `SYMS_CvSymKind_OEM = 0x0404` (scope `__anon43fde12c0803`) — Local Reference to a procedure
- L1169 _enumerator_ `SYMS_CvSymKind_TI16_MAX = 0x1000` (scope `__anon43fde12c0803`) — OEM defined symbol
- L1171 _enumerator_ `SYMS_CvSymKind_CONSTANT_ST = 0x1002` (scope `__anon43fde12c0803`) — Register variable
- L1173 _enumerator_ `SYMS_CvSymKind_UDT_ST = 0x1003` (scope `__anon43fde12c0803`) — constant symbol
- L1175 _enumerator_ `SYMS_CvSymKind_COBOLUDT_ST = 0x1004` (scope `__anon43fde12c0803`) — User defined type
- L1177 _enumerator_ `SYMS_CvSymKind_MANYREG_ST = 0x1005` (scope `__anon43fde12c0803`) — special UDT for cobol that does not symbol pack
- L1179 _enumerator_ `SYMS_CvSymKind_BPREL32_ST = 0x1006` (scope `__anon43fde12c0803`) — multiple register variable
- L1181 _enumerator_ `SYMS_CvSymKind_LDATA32_ST = 0x1007` (scope `__anon43fde12c0803`) — BP-relative
- L1183 _enumerator_ `SYMS_CvSymKind_GDATA32_ST = 0x1008` (scope `__anon43fde12c0803`) — Module-static symbol
- L1185 _enumerator_ `SYMS_CvSymKind_PUB32_ST = 0x1009` (scope `__anon43fde12c0803`) — Global data symbol
- L1187 _enumerator_ `SYMS_CvSymKind_LPROC32_ST = 0x100a` (scope `__anon43fde12c0803`) — a public symbol (CV internal reserved)
- L1189 _enumerator_ `SYMS_CvSymKind_GPROC32_ST = 0x100b` (scope `__anon43fde12c0803`) — Local procedure start
- L1191 _enumerator_ `SYMS_CvSymKind_VFTABLE32 = 0x100c` (scope `__anon43fde12c0803`) — Global procedure start
- L1193 _enumerator_ `SYMS_CvSymKind_REGREL32_ST = 0x100d` (scope `__anon43fde12c0803`) — address of virtual function table
- L1195 _enumerator_ `SYMS_CvSymKind_LTHREAD32_ST = 0x100e` (scope `__anon43fde12c0803`) — register relative address
- L1197 _enumerator_ `SYMS_CvSymKind_GTHREAD32_ST = 0x100f` (scope `__anon43fde12c0803`) — static thread storage
- L1199 _enumerator_ `SYMS_CvSymKind_LPROCMIPS_ST = 0x1010` (scope `__anon43fde12c0803`) — static thread storage
- L1201 _enumerator_ `SYMS_CvSymKind_GPROCMIPS_ST = 0x1011` (scope `__anon43fde12c0803`) — Local procedure start
- L1203 _enumerator_ `SYMS_CvSymKind_FRAMEPROC = 0x1012` (scope `__anon43fde12c0803`) — Global procedure start
- L1205 _enumerator_ `SYMS_CvSymKind_COMPILE2_ST = 0x1013` (scope `__anon43fde12c0803`) — extra frame and proc information
- L1207 _enumerator_ `SYMS_CvSymKind_MANYREG2_ST = 0x1014` (scope `__anon43fde12c0803`) — extended compile flags and info
- L1209 _enumerator_ `SYMS_CvSymKind_LPROCIA64_ST = 0x1015` (scope `__anon43fde12c0803`) — multiple register variable
- L1211 _enumerator_ `SYMS_CvSymKind_GPROCIA64_ST = 0x1016` (scope `__anon43fde12c0803`) — Local procedure start (IA64)
- L1213 _enumerator_ `SYMS_CvSymKind_LOCALSLOT_ST = 0x1017` (scope `__anon43fde12c0803`) — Global procedure start (IA64)
- L1215 _enumerator_ `SYMS_CvSymKind_PARAMSLOT_ST = 0x1018` (scope `__anon43fde12c0803`) — static IL sym with field for static slot index
- L1217 _enumerator_ `SYMS_CvSymKind_ANNOTATION = 0x1019` (scope `__anon43fde12c0803`) — static IL sym with field for parameter slot index
- L1219 _enumerator_ `SYMS_CvSymKind_GMANPROC_ST = 0x101a` (scope `__anon43fde12c0803`) — Annotation string literals
- L1221 _enumerator_ `SYMS_CvSymKind_LMANPROC_ST = 0x101b` (scope `__anon43fde12c0803`) — Global proc
- L1223 _enumerator_ `SYMS_CvSymKind_RESERVED1 = 0x101c` (scope `__anon43fde12c0803`) — Local proc
- L1225 _enumerator_ `SYMS_CvSymKind_RESERVED2 = 0x101d` (scope `__anon43fde12c0803`) — reserved
- L1227 _enumerator_ `SYMS_CvSymKind_RESERVED3 = 0x101e` (scope `__anon43fde12c0803`) — reserved
- L1229 _enumerator_ `SYMS_CvSymKind_RESERVED4 = 0x101f` (scope `__anon43fde12c0803`) — reserved
- L1231 _enumerator_ `SYMS_CvSymKind_LMANDATA_ST = 0x1020` (scope `__anon43fde12c0803`) — reserved
- L1232 _enumerator_ `SYMS_CvSymKind_GMANDATA_ST = 0x1021` (scope `__anon43fde12c0803`)
- L1233 _enumerator_ `SYMS_CvSymKind_MANFRAMEREL_ST = 0x1022` (scope `__anon43fde12c0803`)
- L1234 _enumerator_ `SYMS_CvSymKind_MANREGISTER_ST = 0x1023` (scope `__anon43fde12c0803`)
- L1235 _enumerator_ `SYMS_CvSymKind_MANSLOT_ST = 0x1024` (scope `__anon43fde12c0803`)
- L1236 _enumerator_ `SYMS_CvSymKind_MANMANYREG_ST = 0x1025` (scope `__anon43fde12c0803`)
- L1237 _enumerator_ `SYMS_CvSymKind_MANREGREL_ST = 0x1026` (scope `__anon43fde12c0803`)
- L1238 _enumerator_ `SYMS_CvSymKind_MANMANYREG2_ST = 0x1027` (scope `__anon43fde12c0803`)
- L1239 _enumerator_ `SYMS_CvSymKind_MANTYPREF = 0x1028` (scope `__anon43fde12c0803`)
- L1241 _enumerator_ `SYMS_CvSymKind_UNAMESPACE_ST = 0x1029` (scope `__anon43fde12c0803`) — Index for type referenced by name from metadata
- L1243 _enumerator_ `SYMS_CvSymKind_ST_MAX = 0x1100` (scope `__anon43fde12c0803`) — Using namespace
- L1245 _enumerator_ `SYMS_CvSymKind_OBJNAME = 0x1101` (scope `__anon43fde12c0803`) — starting point for SZ name symbols
- L1247 _enumerator_ `SYMS_CvSymKind_THUNK32 = 0x1102` (scope `__anon43fde12c0803`) — path to object file name
- L1249 _enumerator_ `SYMS_CvSymKind_BLOCK32 = 0x1103` (scope `__anon43fde12c0803`) — Thunk Start
- L1251 _enumerator_ `SYMS_CvSymKind_WITH32 = 0x1104` (scope `__anon43fde12c0803`) — block start
- L1253 _enumerator_ `SYMS_CvSymKind_LABEL32 = 0x1105` (scope `__anon43fde12c0803`) — with start
- L1255 _enumerator_ `SYMS_CvSymKind_REGISTER = 0x1106` (scope `__anon43fde12c0803`) — code label
- L1257 _enumerator_ `SYMS_CvSymKind_CONSTANT = 0x1107` (scope `__anon43fde12c0803`) — Register variable
- L1259 _enumerator_ `SYMS_CvSymKind_UDT = 0x1108` (scope `__anon43fde12c0803`) — constant symbol
- L1261 _enumerator_ `SYMS_CvSymKind_COBOLUDT = 0x1109` (scope `__anon43fde12c0803`) — User defined type
- L1263 _enumerator_ `SYMS_CvSymKind_MANYREG = 0x110a` (scope `__anon43fde12c0803`) — special UDT for cobol that does not symbol pack
- L1265 _enumerator_ `SYMS_CvSymKind_BPREL32 = 0x110b` (scope `__anon43fde12c0803`) — multiple register variable
- L1267 _enumerator_ `SYMS_CvSymKind_LDATA32 = 0x110c` (scope `__anon43fde12c0803`) — BP-relative
- L1269 _enumerator_ `SYMS_CvSymKind_GDATA32 = 0x110d` (scope `__anon43fde12c0803`) — Module-static symbol
- L1271 _enumerator_ `SYMS_CvSymKind_PUB32 = 0x110e` (scope `__anon43fde12c0803`) — Global data symbol
- L1273 _enumerator_ `SYMS_CvSymKind_LPROC32 = 0x110f` (scope `__anon43fde12c0803`) — a public symbol (CV internal reserved)
- L1275 _enumerator_ `SYMS_CvSymKind_GPROC32 = 0x1110` (scope `__anon43fde12c0803`) — Local procedure start
- L1277 _enumerator_ `SYMS_CvSymKind_REGREL32 = 0x1111` (scope `__anon43fde12c0803`) — Global procedure start
- L1279 _enumerator_ `SYMS_CvSymKind_LTHREAD32 = 0x1112` (scope `__anon43fde12c0803`) — register relative address
- L1281 _enumerator_ `SYMS_CvSymKind_GTHREAD32 = 0x1113` (scope `__anon43fde12c0803`) — static thread storage
- L1283 _enumerator_ `SYMS_CvSymKind_LPROCMIPS = 0x1114` (scope `__anon43fde12c0803`) — static thread storage
- L1285 _enumerator_ `SYMS_CvSymKind_GPROCMIPS = 0x1115` (scope `__anon43fde12c0803`) — Local procedure start
- L1287 _enumerator_ `SYMS_CvSymKind_COMPILE2 = 0x1116` (scope `__anon43fde12c0803`) — Global procedure start
- L1289 _enumerator_ `SYMS_CvSymKind_MANYREG2 = 0x1117` (scope `__anon43fde12c0803`) — extended compile flags and info
- L1291 _enumerator_ `SYMS_CvSymKind_LPROCIA64 = 0x1118` (scope `__anon43fde12c0803`) — multiple register variable
- L1293 _enumerator_ `SYMS_CvSymKind_GPROCIA64 = 0x1119` (scope `__anon43fde12c0803`) — Local procedure start (IA64)
- L1295 _enumerator_ `SYMS_CvSymKind_LOCALSLOT = 0x111a` (scope `__anon43fde12c0803`) — Global procedure start (IA64)
- L1297 _enumerator_ `SYMS_CvSymKind_PARAMSLOT = 0x111b` (scope `__anon43fde12c0803`) — static IL sym with field for static slot index
- L1299 _enumerator_ `SYMS_CvSymKind_LMANDATA = 0x111c` (scope `__anon43fde12c0803`) — static IL sym with field for parameter slot index
- L1300 _enumerator_ `SYMS_CvSymKind_GMANDATA = 0x111d` (scope `__anon43fde12c0803`)
- L1301 _enumerator_ `SYMS_CvSymKind_MANFRAMEREL = 0x111e` (scope `__anon43fde12c0803`)
- L1302 _enumerator_ `SYMS_CvSymKind_MANREGISTER = 0x111f` (scope `__anon43fde12c0803`)
- L1303 _enumerator_ `SYMS_CvSymKind_MANSLOT = 0x1120` (scope `__anon43fde12c0803`)
- L1304 _enumerator_ `SYMS_CvSymKind_MANMANYREG = 0x1121` (scope `__anon43fde12c0803`)
- L1305 _enumerator_ `SYMS_CvSymKind_MANREGREL = 0x1122` (scope `__anon43fde12c0803`)
- L1306 _enumerator_ `SYMS_CvSymKind_MANMANYREG2 = 0x1123` (scope `__anon43fde12c0803`)
- L1307 _enumerator_ `SYMS_CvSymKind_UNAMESPACE = 0x1124` (scope `__anon43fde12c0803`)
- L1309 _enumerator_ `SYMS_CvSymKind_PROCREF = 0x1125` (scope `__anon43fde12c0803`) — Using namespace
- L1311 _enumerator_ `SYMS_CvSymKind_DATAREF = 0x1126` (scope `__anon43fde12c0803`) — Reference to a procedure
- L1313 _enumerator_ `SYMS_CvSymKind_LPROCREF = 0x1127` (scope `__anon43fde12c0803`) — Reference to data
- L1315 _enumerator_ `SYMS_CvSymKind_ANNOTATIONREF = 0x1128` (scope `__anon43fde12c0803`) — Local Reference to a procedure
- L1317 _enumerator_ `SYMS_CvSymKind_TOKENREF = 0x1129` (scope `__anon43fde12c0803`) — Reference to an S_ANNOTATION symbol
- L1319 _enumerator_ `SYMS_CvSymKind_GMANPROC = 0x112a` (scope `__anon43fde12c0803`) — Reference to one of the many MANPROCSYM's
- L1321 _enumerator_ `SYMS_CvSymKind_LMANPROC = 0x112b` (scope `__anon43fde12c0803`) — Global proc
- L1323 _enumerator_ `SYMS_CvSymKind_TRAMPOLINE = 0x112c` (scope `__anon43fde12c0803`) — Local proc
- L1325 _enumerator_ `SYMS_CvSymKind_MANCONSTANT = 0x112d` (scope `__anon43fde12c0803`) — trampoline thunks
- L1327 _enumerator_ `SYMS_CvSymKind_ATTR_FRAMEREL = 0x112e` (scope `__anon43fde12c0803`) — constants with metadata type info
- L1329 _enumerator_ `SYMS_CvSymKind_ATTR_REGISTER = 0x112f` (scope `__anon43fde12c0803`) — relative to virtual frame ptr
- L1331 _enumerator_ `SYMS_CvSymKind_ATTR_REGREL = 0x1130` (scope `__anon43fde12c0803`) — stored in a register
- L1333 _enumerator_ `SYMS_CvSymKind_ATTR_MANYREG = 0x1131` (scope `__anon43fde12c0803`) — relative to register (alternate frame ptr)
- L1335 _enumerator_ `SYMS_CvSymKind_SEPCODE = 0x1132` (scope `__anon43fde12c0803`) — stored in >1 register
- L1337 _enumerator_ `SYMS_CvSymKind_DEFRANGE_2005 = 0x1134` (scope `__anon43fde12c0803`) — defines a static symbol in optimized code
- L1339 _enumerator_ `SYMS_CvSymKind_DEFRANGE2_2005 = 0x1135` (scope `__anon43fde12c0803`) — defines a single range of addresses in which symbol can be evaluated
- L1341 _enumerator_ `SYMS_CvSymKind_SECTION = 0x1136` (scope `__anon43fde12c0803`) — defines ranges of addresses in which symbol can be evaluated
- L1343 _enumerator_ `SYMS_CvSymKind_COFFGROUP = 0x1137` (scope `__anon43fde12c0803`) — A COFF section in a PE executable
- L1345 _enumerator_ `SYMS_CvSymKind_EXPORT = 0x1138` (scope `__anon43fde12c0803`) — A COFF group
- L1347 _enumerator_ `SYMS_CvSymKind_CALLSITEINFO = 0x1139` (scope `__anon43fde12c0803`) — A export
- L1349 _enumerator_ `SYMS_CvSymKind_FRAMECOOKIE = 0x113a` (scope `__anon43fde12c0803`) — Indirect call site information
- L1351 _enumerator_ `SYMS_CvSymKind_DISCARDED = 0x113b` (scope `__anon43fde12c0803`) — Security cookie information
- L1353 _enumerator_ `SYMS_CvSymKind_COMPILE3 = 0x113c` (scope `__anon43fde12c0803`) — Discarded by LINK /OPT:REF (experimental, see richards)
- L1355 _enumerator_ `SYMS_CvSymKind_ENVBLOCK = 0x113d` (scope `__anon43fde12c0803`) — Replacement for S_COMPILE2
- L1357 _enumerator_ `SYMS_CvSymKind_LOCAL = 0x113e` (scope `__anon43fde12c0803`) — Environment block split off from S_COMPILE2
- L1359 _enumerator_ `SYMS_CvSymKind_DEFRANGE = 0x113f` (scope `__anon43fde12c0803`) — defines a local symbol in optimized code
- L1361 _enumerator_ `SYMS_CvSymKind_DEFRANGE_SUBFIELD = 0x1140` (scope `__anon43fde12c0803`) — defines a single range of addresses in which symbol can be evaluated
- L1363 _enumerator_ `SYMS_CvSymKind_DEFRANGE_REGISTER = 0x1141` (scope `__anon43fde12c0803`) — ranges for a subfield
- L1365 _enumerator_ `SYMS_CvSymKind_DEFRANGE_FRAMEPOINTER_REL = 0x1142` (scope `__anon43fde12c0803`) — ranges for en-registered symbol
- L1367 _enumerator_ `SYMS_CvSymKind_DEFRANGE_SUBFIELD_REGISTER = 0x1143` (scope `__anon43fde12c0803`) — range for stack symbol.
- L1369 _enumerator_ `SYMS_CvSymKind_DEFRANGE_FRAMEPOINTER_REL_FULL_SCOPE = 0x1144` (scope `__anon43fde12c0803`) — ranges for en-registered field of symbol
- L1371 _enumerator_ `SYMS_CvSymKind_DEFRANGE_REGISTER_REL = 0x1145` (scope `__anon43fde12c0803`) — range for stack symbol span valid full scope of function body, gap might apply.
- L1373 _enumerator_ `SYMS_CvSymKind_LPROC32_ID = 0x1146` (scope `__anon43fde12c0803`) — range for symbol address as register + offset.
- L1374 _enumerator_ `SYMS_CvSymKind_GPROC32_ID = 0x1147` (scope `__anon43fde12c0803`)
- L1375 _enumerator_ `SYMS_CvSymKind_LPROCMIPS_ID = 0x1148` (scope `__anon43fde12c0803`)
- L1376 _enumerator_ `SYMS_CvSymKind_GPROCMIPS_ID = 0x1149` (scope `__anon43fde12c0803`)
- L1377 _enumerator_ `SYMS_CvSymKind_LPROCIA64_ID = 0x114a` (scope `__anon43fde12c0803`)
- L1378 _enumerator_ `SYMS_CvSymKind_GPROCIA64_ID = 0x114b` (scope `__anon43fde12c0803`)
- L1379 _enumerator_ `SYMS_CvSymKind_BUILDINFO = 0x114c` (scope `__anon43fde12c0803`)
- L1381 _enumerator_ `SYMS_CvSymKind_INLINESITE = 0x114d` (scope `__anon43fde12c0803`) — build information.
- L1383 _enumerator_ `SYMS_CvSymKind_INLINESITE_END = 0x114e` (scope `__anon43fde12c0803`) — inlined function callsite.
- L1384 _enumerator_ `SYMS_CvSymKind_PROC_ID_END = 0x114f` (scope `__anon43fde12c0803`)
- L1385 _enumerator_ `SYMS_CvSymKind_DEFRANGE_HLSL = 0x1150` (scope `__anon43fde12c0803`)
- L1386 _enumerator_ `SYMS_CvSymKind_GDATA_HLSL = 0x1151` (scope `__anon43fde12c0803`)
- L1387 _enumerator_ `SYMS_CvSymKind_LDATA_HLSL = 0x1152` (scope `__anon43fde12c0803`)
- L1388 _enumerator_ `SYMS_CvSymKind_FILESTATIC = 0x1153` (scope `__anon43fde12c0803`)
- L1390 _enumerator_ `SYMS_CvSymKind_LPROC32_DPC = 0x1155` (scope `__anon43fde12c0803`) — DPC groupshared variable
- L1392 _enumerator_ `SYMS_CvSymKind_LPROC32_DPC_ID = 0x1156` (scope `__anon43fde12c0803`) — DPC static procedure start
- L1393 _enumerator_ `SYMS_CvSymKind_DEFRANGE_DPC_PTR_TAG = 0x1157` (scope `__anon43fde12c0803`)
- L1395 _enumerator_ `SYMS_CvSymKind_DPC_SYM_TAG_MAP = 0x1158` (scope `__anon43fde12c0803`) — DPC pointer tag definition range
- L1397 _enumerator_ `SYMS_CvSymKind_ARMSWITCHTABLE = 0x1159` (scope `__anon43fde12c0803`) — DPC pointer tag value to symbol record map
- L1398 _enumerator_ `SYMS_CvSymKind_CALLEES = 0x115a` (scope `__anon43fde12c0803`)
- L1399 _enumerator_ `SYMS_CvSymKind_CALLERS = 0x115b` (scope `__anon43fde12c0803`)
- L1400 _enumerator_ `SYMS_CvSymKind_POGODATA = 0x115c` (scope `__anon43fde12c0803`)
- L1401 _enumerator_ `SYMS_CvSymKind_INLINESITE2 = 0x115d` (scope `__anon43fde12c0803`)
- L1403 _enumerator_ `SYMS_CvSymKind_HEAPALLOCSITE = 0x115e` (scope `__anon43fde12c0803`) — extended inline site information
- L1405 _enumerator_ `SYMS_CvSymKind_MOD_TYPEREF = 0x115f` (scope `__anon43fde12c0803`) — heap allocation site
- L1407 _enumerator_ `SYMS_CvSymKind_REF_MINIPDB = 0x1160` (scope `__anon43fde12c0803`) — only generated at link time
- L1409 _enumerator_ `SYMS_CvSymKind_PDBMAP = 0x1161` (scope `__anon43fde12c0803`) — only generated at link time for mini PDB
- L1411 _enumerator_ `SYMS_CvSymKind_GDATA_HLSL32 = 0x1162` (scope `__anon43fde12c0803`) — only generated at link time for mini PDB
- L1412 _enumerator_ `SYMS_CvSymKind_LDATA_HLSL32 = 0x1163` (scope `__anon43fde12c0803`)
- L1413 _enumerator_ `SYMS_CvSymKind_GDATA_HLSL32_EX = 0x1164` (scope `__anon43fde12c0803`)
- L1414 _enumerator_ `SYMS_CvSymKind_LDATA_HLSL32_EX = 0x1165` (scope `__anon43fde12c0803`)
- L1415 _enumerator_ `SYMS_CvSymKind_FASTLINK = 0x1167` (scope `__anon43fde12c0803`)
- L1416 _enumerator_ `SYMS_CvSymKind_INLINEES = 0x1168` (scope `__anon43fde12c0803`)
- L1417 _enumerator_ `SYMS_CvSymKind_COUNT = 194` (scope `__anon43fde12c0803`)
- L1423 _typedef_ `} SYMS_CvAnnotation;`
- L1427 _typedef_ `} SYMS_CvRegister;`
- L1431 _typedef_ `} SYMS_CvBPRelSym32;`
- L1440 _typedef_ `} SYMS_CvVPathSym32;`
- L1444 _typedef_ `} SYMS_CvOEM;`
- L1449 _typedef_ `} SYMS_CvSLink32;`
- L1450 _typedef_ `typedef SYMS_U8 SYMS_CvGenericStyle;`
- L1452 _enumerator_ `SYMS_CvGenericStyle_VOID` (scope `__anon43fde12c0903`)
- L1454 _enumerator_ `SYMS_CvGenericStyle_REG` (scope `__anon43fde12c0903`) — "void return type"
- L1456 _enumerator_ `SYMS_CvGenericStyle_ICAN` (scope `__anon43fde12c0903`) — "return data is in register"
- L1458 _enumerator_ `SYMS_CvGenericStyle_ICAF` (scope `__anon43fde12c0903`) — "indirect caller allocated near"
- L1460 _enumerator_ `SYMS_CvGenericStyle_IRAN` (scope `__anon43fde12c0903`) — "indirect caller allocated far"
- L1462 _enumerator_ `SYMS_CvGenericStyle_IRAF` (scope `__anon43fde12c0903`) — "indirect returnee allocated near"
- L1464 _enumerator_ `SYMS_CvGenericStyle_UNUSED` (scope `__anon43fde12c0903`) — "indirect returnee allocated far"
- L1465 _enumerator_ `SYMS_CvGenericStyle_COUNT = 7` (scope `__anon43fde12c0903`)
- L1467 _typedef_ `typedef SYMS_U16 SYMS_CvGenericFlags;`
- L1469 _enumerator_ `SYMS_CvGenericFlags_CSTYLE = (1 << 0)` (scope `__anon43fde12c0a03`)
- L1470 _enumerator_ `SYMS_CvGenericFlags_RSCLEAN = (1 << 1)` (scope `__anon43fde12c0a03`) — "true if returnee stack cleanup"
- L1475 _typedef_ `} SYMS_CvReturn;`
- L1480 _typedef_ `} SYMS_CvStartSearch;`
- L1481 _typedef_ `typedef SYMS_U8 SYMS_CvLanguage;`
- L1483 _enumerator_ `SYMS_CvLanguage_C = 0x00` (scope `__anon43fde12c0b03`)
- L1484 _enumerator_ `SYMS_CvLanguage_CXX = 0x01` (scope `__anon43fde12c0b03`)
- L1485 _enumerator_ `SYMS_CvLanguage_FORTRAN = 0x02` (scope `__anon43fde12c0b03`)
- L1486 _enumerator_ `SYMS_CvLanguage_MASM = 0x03` (scope `__anon43fde12c0b03`)
- L1487 _enumerator_ `SYMS_CvLanguage_PASCAL = 0x04` (scope `__anon43fde12c0b03`)
- L1488 _enumerator_ `SYMS_CvLanguage_BASIC = 0x05` (scope `__anon43fde12c0b03`)
- L1489 _enumerator_ `SYMS_CvLanguage_COBOL = 0x06` (scope `__anon43fde12c0b03`)
- L1490 _enumerator_ `SYMS_CvLanguage_LINK = 0x07` (scope `__anon43fde12c0b03`)
- L1491 _enumerator_ `SYMS_CvLanguage_CVTRES = 0x08` (scope `__anon43fde12c0b03`)
- L1492 _enumerator_ `SYMS_CvLanguage_CVTPGD = 0x09` (scope `__anon43fde12c0b03`)
- L1493 _enumerator_ `SYMS_CvLanguage_CSHARP = 0x0A` (scope `__anon43fde12c0b03`)
- L1494 _enumerator_ `SYMS_CvLanguage_VB = 0x0B` (scope `__anon43fde12c0b03`)
- L1495 _enumerator_ `SYMS_CvLanguage_ILASM = 0x0C` (scope `__anon43fde12c0b03`)
- L1496 _enumerator_ `SYMS_CvLanguage_JAVA = 0x0D` (scope `__anon43fde12c0b03`)
- L1497 _enumerator_ `SYMS_CvLanguage_JSCRIPT = 0x0E` (scope `__anon43fde12c0b03`)
- L1498 _enumerator_ `SYMS_CvLanguage_MSIL = 0x0F` (scope `__anon43fde12c0b03`)
- L1499 _enumerator_ `SYMS_CvLanguage_HLSL = 0x10` (scope `__anon43fde12c0b03`)
- L1500 _enumerator_ `SYMS_CvLanguage_COUNT = 17` (scope `__anon43fde12c0b03`)
- L1507 _typedef_ `} SYMS_CvThread32;` — variable-width: SYMS_U8 name;
- L1508 _typedef_ `typedef SYMS_U32 SYMS_CvCompileFlags;`
- L1510 _enumerator_ `SYMS_CvCompileFlags_Language_SHIFT = 0` (scope `__anon43fde12c0c03`)
- L1510 _enumerator_ `SYMS_CvCompileFlags_Language_SHIFT = 0` (scope `__anon43fde12c0c03`)
- L1511 _enumerator_ `SYMS_CvCompileFlags_Pcode = (1 << 8)` (scope `__anon43fde12c0c03`)
- L1512 _enumerator_ `SYMS_CvCompileFlags_FloatPrec_SHIFT = 9` (scope `__anon43fde12c0c03`)
- L1512 _enumerator_ `SYMS_CvCompileFlags_FloatPrec_SHIFT = 9` (scope `__anon43fde12c0c03`)
- L1513 _enumerator_ `SYMS_CvCompileFlags_FloatPkg_SHIFT = 11` (scope `__anon43fde12c0c03`)
- L1513 _enumerator_ `SYMS_CvCompileFlags_FloatPkg_SHIFT = 11` (scope `__anon43fde12c0c03`)
- L1514 _enumerator_ `SYMS_CvCompileFlags_AmbientData_SHIFT = 13` (scope `__anon43fde12c0c03`)
- L1514 _enumerator_ `SYMS_CvCompileFlags_AmbientData_SHIFT = 13` (scope `__anon43fde12c0c03`)
- L1515 _enumerator_ `SYMS_CvCompileFlags_AmbientCode_SHIFT = 16` (scope `__anon43fde12c0c03`)
- L1515 _enumerator_ `SYMS_CvCompileFlags_AmbientCode_SHIFT = 16` (scope `__anon43fde12c0c03`)
- L1516 _enumerator_ `SYMS_CvCompileFlags_Mode = (1 << 19)` (scope `__anon43fde12c0c03`)
- L1517 _enumerator_ `SYMS_CvCompileFlags_pad_SHIFT = 20` (scope `__anon43fde12c0c03`)
- L1517 _enumerator_ `SYMS_CvCompileFlags_pad_SHIFT = 20` (scope `__anon43fde12c0c03`)
- L1519 _macro_ `#define SYMS_CvCompileFlags_Extract_Language(f) (SYMS_CvLanguage)(((f) >> SYMS_CvCompileFlags_Language_SHIFT) & SYMS_CvCompileFlags_Language_MASK)`
- L1520 _macro_ `#define SYMS_CvCompileFlags_Extract_FloatPrec(f) (SYMS_U8)(((f) >> SYMS_CvCompileFlags_FloatPrec_SHIFT) & SYMS_CvCompileFlags_FloatPrec_MASK)`
- L1521 _macro_ `#define SYMS_CvCompileFlags_Extract_FloatPkg(f) (SYMS_U8)(((f) >> SYMS_CvCompileFlags_FloatPkg_SHIFT) & SYMS_CvCompileFlags_FloatPkg_MASK)`
- L1522 _macro_ `#define SYMS_CvCompileFlags_Extract_AmbientData(f) (SYMS_U8)(((f) >> SYMS_CvCompileFlags_AmbientData_SHIFT) & SYMS_CvCompileFlags_AmbientData_MASK)`
- L1523 _macro_ `#define SYMS_CvCompileFlags_Extract_AmbientCode(f) (SYMS_U8)(((f) >> SYMS_CvCompileFlags_AmbientCode_SHIFT) & SYMS_CvCompileFlags_AmbientCode_MASK)`
- L1524 _macro_ `#define SYMS_CvCompileFlags_Extract_pad(f) (SYMS_U8)(((f) >> SYMS_CvCompileFlags_pad_SHIFT) & SYMS_CvCompileFlags_pad_MASK)`
- L1529 _typedef_ `} SYMS_CvCompile;` — variable-width: SYMS_U8 ver_str;
- L1531 _typedef_ `typedef SYMS_U32 SYMS_CvCompile2Flags;` — struct SYMS_CvEnd{} skipped - no fixed width members
- L1533 _enumerator_ `SYMS_CvCompile2Flag_Language_SHIFT = 0` (scope `__anon43fde12c0d03`)
- L1533 _enumerator_ `SYMS_CvCompile2Flag_Language_SHIFT = 0` (scope `__anon43fde12c0d03`)
- L1534 _enumerator_ `SYMS_CvCompile2Flag_EC = (1 << 8)` (scope `__anon43fde12c0d03`)
- L1535 _enumerator_ `SYMS_CvCompile2Flag_NoDbgInfo = (1 << 9)` (scope `__anon43fde12c0d03`)
- L1536 _enumerator_ `SYMS_CvCompile2Flag_LTCG = (1 << 10)` (scope `__anon43fde12c0d03`)
- L1537 _enumerator_ `SYMS_CvCompile2Flag_NoDataAlign = (1 << 11)` (scope `__anon43fde12c0d03`)
- L1538 _enumerator_ `SYMS_CvCompile2Flag_ManagedPresent = (1 << 12)` (scope `__anon43fde12c0d03`)
- L1539 _enumerator_ `SYMS_CvCompile2Flag_SecurityChecks = (1 << 13)` (scope `__anon43fde12c0d03`)
- L1540 _enumerator_ `SYMS_CvCompile2Flag_HotPatch = (1 << 14)` (scope `__anon43fde12c0d03`)
- L1541 _enumerator_ `SYMS_CvCompile2Flag_CVTCIL = (1 << 15)` (scope `__anon43fde12c0d03`)
- L1542 _enumerator_ `SYMS_CvCompile2Flag_MSILModule = (1 << 16)` (scope `__anon43fde12c0d03`)
- L1544 _macro_ `#define SYMS_CvCompile2Flags_Extract_Language(f) (SYMS_CvLanguage)(((f) >> SYMS_CvCompile2Flag_Language_SHIFT) & SYMS_CvCompile2Flag_Language_MASK)`
- L1555 _typedef_ `} SYMS_CvCompile2;` — variable-width: SYMS_U8 ver_str;
- L1556 _typedef_ `typedef SYMS_U32 SYMS_CvCompile3Flags;`
- L1558 _enumerator_ `SYMS_CvCompile3Flag_Language_SHIFT = 0` (scope `__anon43fde12c0e03`)
- L1558 _enumerator_ `SYMS_CvCompile3Flag_Language_SHIFT = 0` (scope `__anon43fde12c0e03`)
- L1559 _enumerator_ `SYMS_CvCompile3Flag_EC = (1 << 8)` (scope `__anon43fde12c0e03`)
- L1560 _enumerator_ `SYMS_CvCompile3Flag_NoDbgInfo = (1 << 9)` (scope `__anon43fde12c0e03`)
- L1561 _enumerator_ `SYMS_CvCompile3Flag_LTCG = (1 << 10)` (scope `__anon43fde12c0e03`)
- L1562 _enumerator_ `SYMS_CvCompile3Flag_NoDataAlign = (1 << 11)` (scope `__anon43fde12c0e03`)
- L1563 _enumerator_ `SYMS_CvCompile3Flag_ManagedPresent = (1 << 12)` (scope `__anon43fde12c0e03`)
- L1564 _enumerator_ `SYMS_CvCompile3Flag_SecurityChecks = (1 << 13)` (scope `__anon43fde12c0e03`)
- L1565 _enumerator_ `SYMS_CvCompile3Flag_HotPatch = (1 << 14)` (scope `__anon43fde12c0e03`)
- L1566 _enumerator_ `SYMS_CvCompile3Flag_CVTCIL = (1 << 15)` (scope `__anon43fde12c0e03`)
- L1567 _enumerator_ `SYMS_CvCompile3Flag_MSILModule = (1 << 16)` (scope `__anon43fde12c0e03`)
- L1568 _enumerator_ `SYMS_CvCompile3Flag_SDL = (1 << 17)` (scope `__anon43fde12c0e03`)
- L1569 _enumerator_ `SYMS_CvCompile3Flag_PGO = (1 << 18)` (scope `__anon43fde12c0e03`)
- L1570 _enumerator_ `SYMS_CvCompile3Flag_EXP = (1 << 19)` (scope `__anon43fde12c0e03`)
- L1572 _macro_ `#define SYMS_CvCompile3Flags_Extract_Language(f) (SYMS_CvLanguage)(((f) >> SYMS_CvCompile3Flag_Language_SHIFT) & SYMS_CvCompile3Flag_Language_MASK)`
- L1585 _typedef_ `} SYMS_CvCompile3;` — variable-width: SYMS_U8 version;
- L1589 _typedef_ `} SYMS_CvObjname;` — variable-width: SYMS_U8 name;
- L1599 _typedef_ `} SYMS_CvRef2;` — Module containing the actual symbol variable-width: SYMS_U8 name;
- L1600 _typedef_ `typedef SYMS_U32 SYMS_CvSepcodeFlags;`
- L1602 _enumerator_ `SYMS_CvSepcodeFlags_IS_LEXICAL_SCOPE = (1 << 0)` (scope `__anon43fde12c0f03`)
- L1603 _enumerator_ `SYMS_CvSepcodeFlags_RETURNS_TO_PARENT = (1 << 1)` (scope `__anon43fde12c0f03`) — "code frag returns to parent"
- L1615 _typedef_ `} SYMS_CvSepcode;`
- L1619 _typedef_ `} SYMS_CvSlotsym32;`
- L1625 _typedef_ `} SYMS_CvPogoInfo;`
- L1629 _typedef_ `} SYMS_CvManyreg;`
- L1633 _typedef_ `} SYMS_CvManyreg2;`
- L1634 _typedef_ `typedef SYMS_U8 SYMS_CvEncodedFramePtrReg;`
- L1636 _enumerator_ `SYMS_CvEncodedFramePtrReg_None = 0` (scope `__anon43fde12c1003`)
- L1637 _enumerator_ `SYMS_CvEncodedFramePtrReg_StackPtr = 1` (scope `__anon43fde12c1003`)
- L1638 _enumerator_ `SYMS_CvEncodedFramePtrReg_FramePtr = 2` (scope `__anon43fde12c1003`)
- L1639 _enumerator_ `SYMS_CvEncodedFramePtrReg_BasePtr = 3` (scope `__anon43fde12c1003`)
- L1640 _enumerator_ `SYMS_CvEncodedFramePtrReg_COUNT = 4` (scope `__anon43fde12c1003`)
- L1642 _typedef_ `typedef SYMS_U32 SYMS_CvFrameprocFlags;`
- L1644 _enumerator_ `SYMS_CvFrameprocFlag_UsesAlloca = (1 << 0)` (scope `__anon43fde12c1103`)
- L1645 _enumerator_ `SYMS_CvFrameprocFlag_UsesSetJmp = (1 << 1)` (scope `__anon43fde12c1103`)
- L1646 _enumerator_ `SYMS_CvFrameprocFlag_UsesLongJmp = (1 << 2)` (scope `__anon43fde12c1103`)
- L1647 _enumerator_ `SYMS_CvFrameprocFlag_UsesInlAsm = (1 << 3)` (scope `__anon43fde12c1103`)
- L1648 _enumerator_ `SYMS_CvFrameprocFlag_UsesEH = (1 << 4)` (scope `__anon43fde12c1103`)
- L1649 _enumerator_ `SYMS_CvFrameprocFlag_Inline = (1 << 5)` (scope `__anon43fde12c1103`)
- L1650 _enumerator_ `SYMS_CvFrameprocFlag_HasSEH = (1 << 6)` (scope `__anon43fde12c1103`)
- L1651 _enumerator_ `SYMS_CvFrameprocFlag_Naked = (1 << 7)` (scope `__anon43fde12c1103`)
- L1652 _enumerator_ `SYMS_CvFrameprocFlag_HasSecurityChecks = (1 << 8)` (scope `__anon43fde12c1103`)
- L1653 _enumerator_ `SYMS_CvFrameprocFlag_AsyncEH = (1 << 9)` (scope `__anon43fde12c1103`)
- L1654 _enumerator_ `SYMS_CvFrameprocFlag_GSNoStackOrdering = (1 << 10)` (scope `__anon43fde12c1103`)
- L1655 _enumerator_ `SYMS_CvFrameprocFlag_WasInlined = (1 << 11)` (scope `__anon43fde12c1103`)
- L1656 _enumerator_ `SYMS_CvFrameprocFlag_GSCheck = (1 << 12)` (scope `__anon43fde12c1103`)
- L1657 _enumerator_ `SYMS_CvFrameprocFlag_SafeBuffers = (1 << 13)` (scope `__anon43fde12c1103`)
- L1658 _enumerator_ `SYMS_CvFrameprocFlag_LocalBasePointer_SHIFT = 14` (scope `__anon43fde12c1103`)
- L1658 _enumerator_ `SYMS_CvFrameprocFlag_LocalBasePointer_SHIFT = 14` (scope `__anon43fde12c1103`)
- L1659 _enumerator_ `SYMS_CvFrameprocFlag_ParamBasePointer_SHIFT = 16` (scope `__anon43fde12c1103`)
- L1659 _enumerator_ `SYMS_CvFrameprocFlag_ParamBasePointer_SHIFT = 16` (scope `__anon43fde12c1103`)
- L1660 _enumerator_ `SYMS_CvFrameprocFlag_PogoOn = (1 << 18)` (scope `__anon43fde12c1103`)
- L1661 _enumerator_ `SYMS_CvFrameprocFlag_PogoCountsValid = (1 << 19)` (scope `__anon43fde12c1103`)
- L1662 _enumerator_ `SYMS_CvFrameprocFlag_OptSpeed = (1 << 20)` (scope `__anon43fde12c1103`)
- L1663 _enumerator_ `SYMS_CvFrameprocFlag_HasCFG = (1 << 21)` (scope `__anon43fde12c1103`)
- L1664 _enumerator_ `SYMS_CvFrameprocFlag_HasCFW = (1 << 22)` (scope `__anon43fde12c1103`)
- L1666 _macro_ `#define SYMS_CvFrameprocFlags_Extract_LocalBasePointer(f) (SYMS_CvEncodedFramePtrReg)(((f) >> SYMS_CvFrameprocFlag_LocalBasePointer_SHIFT) & SYMS_CvFrameprocFlag_LocalBasePointer_MASK)`
- L1667 _macro_ `#define SYMS_CvFrameprocFlags_Extract_ParamBasePointer(f) (SYMS_CvEncodedFramePtrReg)(((f) >> SYMS_CvFrameprocFlag_ParamBasePointer_SHIFT) & SYMS_CvFrameprocFlag_ParamBasePointer_MASK)`
- L1678 _typedef_ `} SYMS_CvFrameproc;`
- L1679 _typedef_ `typedef SYMS_U8 SYMS_CvThunkOrdinal;`
- L1681 _enumerator_ `SYMS_CvThunkOrdinal_NOTYPE` (scope `__anon43fde12c1203`)
- L1683 _enumerator_ `SYMS_CvThunkOrdinal_ADJUSTOR` (scope `__anon43fde12c1203`) — standard thunk
- L1685 _enumerator_ `SYMS_CvThunkOrdinal_VCALL` (scope `__anon43fde12c1203`) — adjustor for "this"
- L1686 _enumerator_ `SYMS_CvThunkOrdinal_PCODE` (scope `__anon43fde12c1203`)
- L1687 _enumerator_ `SYMS_CvThunkOrdinal_LOAD` (scope `__anon43fde12c1203`)
- L1689 _enumerator_ `SYMS_CvThunkOrdinal_TRAMP_INCREMENTAL` (scope `__anon43fde12c1203`) — "thunk which loads the address to jump to via unknwon means"
- L1690 _enumerator_ `SYMS_CvThunkOrdinal_TRAMP_BRANCHISLAND` (scope `__anon43fde12c1203`)
- L1691 _enumerator_ `SYMS_CvThunkOrdinal_COUNT = 7` (scope `__anon43fde12c1203`)
- L1702 _typedef_ `} SYMS_CvThunk32;` — variable-width: SYMS_U8 name;
- L1710 _typedef_ `} SYMS_CvBlock32;` — variable-width: SYMS_U8 name;
- L1711 _typedef_ `typedef SYMS_U8 SYMS_CvProcFlags;`
- L1713 _enumerator_ `SYMS_CvProcFlag_NOFPO = (1 << 0)` (scope `__anon43fde12c1303`)
- L1714 _enumerator_ `SYMS_CvProcFlag_INT_RETURN = (1 << 1)` (scope `__anon43fde12c1303`)
- L1715 _enumerator_ `SYMS_CvProcFlag_FAR_RETURN = (1 << 2)` (scope `__anon43fde12c1303`)
- L1716 _enumerator_ `SYMS_CvProcFlag_NEVER_RETURN = (1 << 3)` (scope `__anon43fde12c1303`)
- L1717 _enumerator_ `SYMS_CvProcFlag_NOTREACHED = (1 << 4)` (scope `__anon43fde12c1303`)
- L1718 _enumerator_ `SYMS_CvProcFlag_CUSTOM_CALL = (1 << 5)` (scope `__anon43fde12c1303`)
- L1719 _enumerator_ `SYMS_CvProcFlag_NOINLINE = (1 << 6)` (scope `__anon43fde12c1303`)
- L1720 _enumerator_ `SYMS_CvProcFlag_OPTDBGINFO = (1 << 7)` (scope `__anon43fde12c1303`)
- L1727 _typedef_ `} SYMS_CvLabel32;` — variable-width: SYMS_U8 name;
- L1732 _typedef_ `} SYMS_CvConstant;` — variable-width: SYMS_PdbNumeric num; variable-width: SYMS_U8 name;
- L1736 _typedef_ `} SYMS_CvUDT;` — variable-width: SYMS_U8 name;
- L1737 _typedef_ `typedef SYMS_U16 SYMS_CvTrampolineKind;`
- L1739 _enumerator_ `SYMS_CvTrampolineKind_INCREMENTAL` (scope `__anon43fde12c1403`)
- L1740 _enumerator_ `SYMS_CvTrampolineKind_BRANCH_ISLAND` (scope `__anon43fde12c1403`)
- L1741 _enumerator_ `SYMS_CvTrampolineKind_COUNT = 2` (scope `__anon43fde12c1403`)
- L1750 _typedef_ `} SYMS_CvTrampoline;`
- L1759 _typedef_ `} SYMS_CvSection;` — variable-width: SYMS_U8 name;
- L1766 _typedef_ `} SYMS_CvCoffGroup;` — variable-width: SYMS_U8 name;
- L1767 _typedef_ `typedef SYMS_U16 SYMS_CvExportFlags;`
- L1769 _enumerator_ `SYMS_CvExportFlag_CONSTANT = (1 << 0)` (scope `__anon43fde12c1503`)
- L1770 _enumerator_ `SYMS_CvExportFlag_DATA = (1 << 1)` (scope `__anon43fde12c1503`)
- L1771 _enumerator_ `SYMS_CvExportFlag_PRIVATE = (1 << 2)` (scope `__anon43fde12c1503`)
- L1772 _enumerator_ `SYMS_CvExportFlag_NONAME = (1 << 3)` (scope `__anon43fde12c1503`)
- L1773 _enumerator_ `SYMS_CvExportFlag_ORDINAL = (1 << 4)` (scope `__anon43fde12c1503`)
- L1774 _enumerator_ `SYMS_CvExportFlag_FORWARDER = (1 << 5)` (scope `__anon43fde12c1503`)
- L1780 _typedef_ `} SYMS_CvExport;` — variable-width: SYMS_U8 name;
- L1789 _typedef_ `} SYMS_CvCallSiteInfo;`
- L1790 _typedef_ `typedef SYMS_U32 SYMS_CvFrameCookieKind;`
- L1792 _enumerator_ `SYMS_CvFrameCookieKind_COPY` (scope `__anon43fde12c1603`)
- L1793 _enumerator_ `SYMS_CvFrameCookieKind_XOR_SP` (scope `__anon43fde12c1603`)
- L1794 _enumerator_ `SYMS_CvFrameCookieKind_XOR_BP` (scope `__anon43fde12c1603`)
- L1795 _enumerator_ `SYMS_CvFrameCookieKind_XOR_R13` (scope `__anon43fde12c1603`)
- L1796 _enumerator_ `SYMS_CvFrameCookieKind_COUNT = 4` (scope `__anon43fde12c1603`)
- L1803 _typedef_ `} SYMS_CvFrameCookie;`
- L1807 _typedef_ `} SYMS_CvEnvblock;` — variable-width: SYMS_U8 rgsz;
- L1808 _typedef_ `typedef SYMS_U16 SYMS_CvLocalFlags;`
- L1810 _enumerator_ `SYMS_CvLocalFlag_PARAM = (1 << 0)` (scope `__anon43fde12c1703`)
- L1811 _enumerator_ `SYMS_CvLocalFlag_ADDR_TAKEN = (1 << 1)` (scope `__anon43fde12c1703`)
- L1812 _enumerator_ `SYMS_CvLocalFlag_COMPGEN = (1 << 2)` (scope `__anon43fde12c1703`)
- L1813 _enumerator_ `SYMS_CvLocalFlag_AGGREGATE = (1 << 3)` (scope `__anon43fde12c1703`)
- L1814 _enumerator_ `SYMS_CvLocalFlag_PARTOF_ARGGREGATE = (1 << 4)` (scope `__anon43fde12c1703`)
- L1815 _enumerator_ `SYMS_CvLocalFlag_ALIASED = (1 << 5)` (scope `__anon43fde12c1703`)
- L1816 _enumerator_ `SYMS_CvLocalFlag_ALIAS = (1 << 6)` (scope `__anon43fde12c1703`)
- L1817 _enumerator_ `SYMS_CvLocalFlag_RETVAL = (1 << 7)` (scope `__anon43fde12c1703`)
- L1818 _enumerator_ `SYMS_CvLocalFlag_OPTOUT = (1 << 8)` (scope `__anon43fde12c1703`)
- L1819 _enumerator_ `SYMS_CvLocalFlag_GLOBAL = (1 << 9)` (scope `__anon43fde12c1703`)
- L1820 _enumerator_ `SYMS_CvLocalFlag_STATIC = (1 << 10)` (scope `__anon43fde12c1703`)
- L1827 _typedef_ `} SYMS_CvLocal;` — Name of this symbol, a null terminated array of UTF8 characters. variable-width: SYMS_U8 name;
- L1832 _typedef_ `} SYMS_CvLvarAddrRange;`
- L1836 _typedef_ `} SYMS_CvLvarAddrGap;`
- L1837 _typedef_ `typedef SYMS_U16 SYMS_CvRangeAttribs;`
- L1839 _enumerator_ `SYMS_CvRangeAttrib_MAYBE = (1 << 0)` (scope `__anon43fde12c1803`)
- L1845 _typedef_ `} SYMS_CvDefrange;` — variable-width: SYMS_CvLvarAddrGap gaps;
- L1851 _typedef_ `} SYMS_CvDefrangeSubfield;` — variable-width: SYMS_CvLvarAddrGap gaps;
- L1857 _typedef_ `} SYMS_CvDefrangeRegister;` — variable-width: SYMS_CvLvarAddrGap gaps;
- L1862 _typedef_ `} SYMS_CvDefrangeFramepointerRel;` — variable-width: SYMS_CvLvarAddrGap gaps;
- L1869 _typedef_ `} SYMS_CvDefrangeSubfieldRegister;` — variable-width: SYMS_CvLvarAddrGap gaps;
- L1872 _typedef_ `} SYMS_CvDefrangeFramepointerRelFullScope;`
- L1873 _typedef_ `typedef SYMS_U16 SYMS_CvDefrangeRegisterRelFlags;`
- L1875 _enumerator_ `SYMS_CvDefrangeRegisterRelFlag_SPILLED_OUT_UDT_MEMBER = (1 << 0)` (scope `__anon43fde12c1903`)
- L1876 _enumerator_ `SYMS_CvDefrangeRegisterRelFlag_unused_1 = (1 << 1)` (scope `__anon43fde12c1903`)
- L1877 _enumerator_ `SYMS_CvDefrangeRegisterRelFlag_unused_2 = (1 << 2)` (scope `__anon43fde12c1903`)
- L1878 _enumerator_ `SYMS_CvDefrangeRegisterRelFlag_unused_3 = (1 << 3)` (scope `__anon43fde12c1903`)
- L1879 _enumerator_ `SYMS_CvDefrangeRegisterRelFlag_OFFSET_PARENT_SHIFT = 4` (scope `__anon43fde12c1903`)
- L1879 _enumerator_ `SYMS_CvDefrangeRegisterRelFlag_OFFSET_PARENT_SHIFT = 4` (scope `__anon43fde12c1903`)
- L1881 _macro_ `#define SYMS_CvDefrangeRegisterRelFlags_Extract_OFFSET_PARENT(f) (SYMS_U16)(((f) >> SYMS_CvDefrangeRegisterRelFlag_OFFSET_PARENT_SHIFT) & SYMS_CvDefrangeRegisterRelFlag_OFFSET_PARENT_MASK)`
- L1888 _typedef_ `} SYMS_CvDefrangeRegisterRel;` — variable-width: SYMS_CvLvarAddrGap gaps;
- L1894 _typedef_ `} SYMS_CvData32;` — variable-width: SYMS_U8 name;
- L1895 _typedef_ `typedef SYMS_U32 SYMS_CvPubsymFlags;`
- L1897 _enumerator_ `SYMS_CvPubsymFlags_CODE = (1 << 0)` (scope `__anon43fde12c1a03`)
- L1898 _enumerator_ `SYMS_CvPubsymFlags_FUNCTION = (1 << 1)` (scope `__anon43fde12c1a03`)
- L1899 _enumerator_ `SYMS_CvPubsymFlags_MANAGED_CODE = (1 << 2)` (scope `__anon43fde12c1a03`)
- L1900 _enumerator_ `SYMS_CvPubsymFlags_MSIL = (1 << 3)` (scope `__anon43fde12c1a03`) — "set if managed IL code"
- L1908 _typedef_ `} SYMS_CvPubsym32;` — "seg" in the reference code - but it's just a section number variable-width: SYMS_U8 name;
- L1923 _typedef_ `} SYMS_CvProc32;` — variable-width: SYMS_U8 name;
- L1929 _typedef_ `} SYMS_CvRegrel32;` — variable-width: SYMS_U8 name;
- L1932 _typedef_ `} SYMS_CvBuildInfo;`
- L1938 _typedef_ `} SYMS_CvFunctionList;` — variable-width: SYMS_CvTypeId func; this should be like "array_clamped_to_stream" or something. variable-width: SYMS_U32 invocations;
- L1955 _typedef_ `} SYMS_CvBAOpcode;`
- L1961 _typedef_ `} SYMS_CvInlineSite;` — variable-width: SYMS_PdbBinaryAnnotation binaryAnnotations;
- L1968 _typedef_ `} SYMS_CvInlineSite2;` — variable-width: SYMS_PdbBinaryAnnotation binaryAnnotations;
- L1973 _typedef_ `} SYMS_CvInlinees;` — variable-width: SYMS_U32 desc;
- L1979 _typedef_ `} SYMS_CvFileStatic;` — variable-width: SYMS_U8 name;
- L1988 _typedef_ `} SYMS_CvHeapAllocSite;`
- L1993 _typedef_ `} SYMS_CvLocalVarAttr;`
- L1998 _typedef_ `} SYMS_CvFramerel;`
- L2003 _typedef_ `} SYMS_CvAttrReg;`
- L2009 _typedef_ `} SYMS_CvAttrRegrel;`
- L2014 _typedef_ `} SYMS_CvAttrManyreg;`
- L2015 _typedef_ `typedef SYMS_U16 SYMS_CvFastLinkFlags;`
- L2017 _enumerator_ `SYMS_CvFastLinkFlag_IS_GLOBAL_DATA = (1 << 0)` (scope `__anon43fde12c1b03`)
- L2018 _enumerator_ `SYMS_CvFastLinkFlag_IS_DATA = (1 << 1)` (scope `__anon43fde12c1b03`)
- L2019 _enumerator_ `SYMS_CvFastLinkFlag_IS_UDT = (1 << 2)` (scope `__anon43fde12c1b03`)
- L2020 _enumerator_ `SYMS_CvFastLinkFlag_unused_1 = (1 << 3)` (scope `__anon43fde12c1b03`)
- L2021 _enumerator_ `SYMS_CvFastLinkFlag_IS_CONST = (1 << 4)` (scope `__anon43fde12c1b03`)
- L2022 _enumerator_ `SYMS_CvFastLinkFlag_unused_2 = (1 << 5)` (scope `__anon43fde12c1b03`)
- L2023 _enumerator_ `SYMS_CvFastLinkFlag_IS_NAMESPACE = (1 << 6)` (scope `__anon43fde12c1b03`)
- L2028 _typedef_ `} SYMS_CvFastLink;`
- L2029 _typedef_ `typedef SYMS_U16 SYMS_CvArmSwitchType;`
- L2031 _enumerator_ `SYMS_CvArmSwitchType_INT1` (scope `__anon43fde12c1c03`)
- L2032 _enumerator_ `SYMS_CvArmSwitchType_UINT1` (scope `__anon43fde12c1c03`)
- L2033 _enumerator_ `SYMS_CvArmSwitchType_INT2` (scope `__anon43fde12c1c03`)
- L2034 _enumerator_ `SYMS_CvArmSwitchType_UINT2` (scope `__anon43fde12c1c03`)
- L2035 _enumerator_ `SYMS_CvArmSwitchType_INT4` (scope `__anon43fde12c1c03`)
- L2036 _enumerator_ `SYMS_CvArmSwitchType_UINT5` (scope `__anon43fde12c1c03`)
- L2037 _enumerator_ `SYMS_CvArmSwitchType_POINTER` (scope `__anon43fde12c1c03`)
- L2038 _enumerator_ `SYMS_CvArmSwitchType_UINT1SHL1` (scope `__anon43fde12c1c03`)
- L2039 _enumerator_ `SYMS_CvArmSwitchType_UINT2SHL1` (scope `__anon43fde12c1c03`)
- L2040 _enumerator_ `SYMS_CvArmSwitchType_INT1SSHL1` (scope `__anon43fde12c1c03`)
- L2041 _enumerator_ `SYMS_CvArmSwitchType_INT2SSHL1` (scope `__anon43fde12c1c03`)
- L2042 _enumerator_ `SYMS_CvArmSwitchType_TBB = SYMS_CvArmSwitchType_UINT1SHL1` (scope `__anon43fde12c1c03`)
- L2043 _enumerator_ `SYMS_CvArmSwitchType_TBH = SYMS_CvArmSwitchType_UINT2SHL1` (scope `__anon43fde12c1c03`)
- L2044 _enumerator_ `SYMS_CvArmSwitchType_COUNT = 13` (scope `__anon43fde12c1c03`)
- L2059 _typedef_ `} SYMS_CvArmSwitchTable;`
- L2060 _typedef_ `typedef SYMS_U16 SYMS_CvRefMiniPdbFlags;`
- L2062 _enumerator_ `SYMS_CvRefMiniPdbFlags_LOCAL = (1 << 0)` (scope `__anon43fde12c1d03`)
- L2063 _enumerator_ `SYMS_CvRefMiniPdbFlags_DATA = (1 << 1)` (scope `__anon43fde12c1d03`)
- L2064 _enumerator_ `SYMS_CvRefMiniPdbFlags_UDT = (1 << 2)` (scope `__anon43fde12c1d03`)
- L2065 _enumerator_ `SYMS_CvRefMiniPdbFlags_LABEL = (1 << 3)` (scope `__anon43fde12c1d03`)
- L2066 _enumerator_ `SYMS_CvRefMiniPdbFlags_CONST = (1 << 4)` (scope `__anon43fde12c1d03`)
- L2073 _typedef_ `} SYMS_CvRefMiniPdb;`
- L2074 _typedef_ `typedef SYMS_U32 SYMS_CvModTypeRefFlags;`
- L2076 _enumerator_ `SYMS_CvModTypeRefFlags_NONE = (1 << 0)` (scope `__anon43fde12c1e03`)
- L2077 _enumerator_ `SYMS_CvModTypeRefFlags_REF_TMPCT = (1 << 1)` (scope `__anon43fde12c1e03`)
- L2078 _enumerator_ `SYMS_CvModTypeRefFlags_OWN_TMPCT = (1 << 2)` (scope `__anon43fde12c1e03`)
- L2079 _enumerator_ `SYMS_CvModTypeRefFlags_OWN_TMR = (1 << 3)` (scope `__anon43fde12c1e03`)
- L2080 _enumerator_ `SYMS_CvModTypeRefFlags_OWN_TM = (1 << 4)` (scope `__anon43fde12c1e03`)
- L2081 _enumerator_ `SYMS_CvModTypeRefFlags_REF_TM = (1 << 5)` (scope `__anon43fde12c1e03`)
- L2088 _typedef_ `} SYMS_CvModTypeRef;`
- L2089 _typedef_ `typedef SYMS_U8 SYMS_CvDiscardedType;`
- L2091 _enumerator_ `SYMS_CvDiscardedType_UNKNOWN` (scope `__anon43fde12c1f03`)
- L2092 _enumerator_ `SYMS_CvDiscardedType_NOT_SELECTED` (scope `__anon43fde12c1f03`)
- L2093 _enumerator_ `SYMS_CvDiscardedType_NOT_REFERENCED` (scope `__anon43fde12c1f03`)
- L2094 _enumerator_ `SYMS_CvDiscardedType_COUNT = 3` (scope `__anon43fde12c1f03`)
- L2096 _typedef_ `typedef SYMS_U32 SYMS_CvDiscardedFlags;`
- L2098 _enumerator_ `SYMS_CvDiscardedFlags_TYPE_SHIFT = 0` (scope `__anon43fde12c2003`)
- L2098 _enumerator_ `SYMS_CvDiscardedFlags_TYPE_SHIFT = 0` (scope `__anon43fde12c2003`)
- L2100 _macro_ `#define SYMS_CvDiscardedFlags_Extract_TYPE(f) (SYMS_CvDiscardedType)(((f) >> SYMS_CvDiscardedFlags_TYPE_SHIFT) & SYMS_CvDiscardedFlags_TYPE_MASK)`
- L2106 _typedef_ `} SYMS_CvDiscarded;`
- L2107 _typedef_ `typedef SYMS_U16 SYMS_CvLeaf;`
- L2110 _enumerator_ `SYMS_CvLeaf_MODIFIER_16t = 0x0001` (scope `__anon43fde12c2103`) — leaf indices starting records but referenced from symbol records
- L2111 _enumerator_ `SYMS_CvLeaf_POINTER_16t = 0x0002` (scope `__anon43fde12c2103`)
- L2112 _enumerator_ `SYMS_CvLeaf_ARRAY_16t = 0x0003` (scope `__anon43fde12c2103`)
- L2113 _enumerator_ `SYMS_CvLeaf_CLASS_16t = 0x0004` (scope `__anon43fde12c2103`)
- L2114 _enumerator_ `SYMS_CvLeaf_STRUCTURE_16t = 0x0005` (scope `__anon43fde12c2103`)
- L2115 _enumerator_ `SYMS_CvLeaf_UNION_16t = 0x0006` (scope `__anon43fde12c2103`)
- L2116 _enumerator_ `SYMS_CvLeaf_ENUM_16t = 0x0007` (scope `__anon43fde12c2103`)
- L2117 _enumerator_ `SYMS_CvLeaf_PROCEDURE_16t = 0x0008` (scope `__anon43fde12c2103`)
- L2118 _enumerator_ `SYMS_CvLeaf_MFUNCTION_16t = 0x0009` (scope `__anon43fde12c2103`)
- L2119 _enumerator_ `SYMS_CvLeaf_VTSHAPE = 0x000a` (scope `__anon43fde12c2103`)
- L2120 _enumerator_ `SYMS_CvLeaf_COBOL0_16t = 0x000b` (scope `__anon43fde12c2103`)
- L2121 _enumerator_ `SYMS_CvLeaf_COBOL1 = 0x000c` (scope `__anon43fde12c2103`)
- L2122 _enumerator_ `SYMS_CvLeaf_BARRAY_16t = 0x000d` (scope `__anon43fde12c2103`)
- L2123 _enumerator_ `SYMS_CvLeaf_LABEL = 0x000e` (scope `__anon43fde12c2103`)
- L2124 _enumerator_ `SYMS_CvLeaf_NULL = 0x000f` (scope `__anon43fde12c2103`)
- L2125 _enumerator_ `SYMS_CvLeaf_NOTTRAN = 0x0010` (scope `__anon43fde12c2103`)
- L2126 _enumerator_ `SYMS_CvLeaf_DIMARRAY_16t = 0x0011` (scope `__anon43fde12c2103`)
- L2127 _enumerator_ `SYMS_CvLeaf_VFTPATH_16t = 0x0012` (scope `__anon43fde12c2103`)
- L2128 _enumerator_ `SYMS_CvLeaf_PRECOMP_16t = 0x0013` (scope `__anon43fde12c2103`)
- L2130 _enumerator_ `SYMS_CvLeaf_ENDPRECOMP = 0x0014` (scope `__anon43fde12c2103`) — not referenced from symbol
- L2132 _enumerator_ `SYMS_CvLeaf_OEM_16t = 0x0015` (scope `__anon43fde12c2103`) — not referenced from symbol
- L2134 _enumerator_ `SYMS_CvLeaf_TYPESERVER_ST = 0x0016` (scope `__anon43fde12c2103`) — oem definable type string
- L2136 _enumerator_ `SYMS_CvLeaf_SKIP_16t = 0x0200` (scope `__anon43fde12c2103`) — leaf indices starting records but referenced only from type records
- L2137 _enumerator_ `SYMS_CvLeaf_ARGLIST_16t = 0x0201` (scope `__anon43fde12c2103`)
- L2138 _enumerator_ `SYMS_CvLeaf_DEFARG_16t = 0x0202` (scope `__anon43fde12c2103`)
- L2139 _enumerator_ `SYMS_CvLeaf_LIST = 0x0203` (scope `__anon43fde12c2103`)
- L2140 _enumerator_ `SYMS_CvLeaf_FIELDLIST_16t = 0x0204` (scope `__anon43fde12c2103`)
- L2141 _enumerator_ `SYMS_CvLeaf_DERIVED_16t = 0x0205` (scope `__anon43fde12c2103`)
- L2142 _enumerator_ `SYMS_CvLeaf_BITFIELD_16t = 0x0206` (scope `__anon43fde12c2103`)
- L2143 _enumerator_ `SYMS_CvLeaf_METHODLIST_16t = 0x0207` (scope `__anon43fde12c2103`)
- L2144 _enumerator_ `SYMS_CvLeaf_DIMCONU_16t = 0x0208` (scope `__anon43fde12c2103`)
- L2145 _enumerator_ `SYMS_CvLeaf_DIMCONLU_16t = 0x0209` (scope `__anon43fde12c2103`)
- L2146 _enumerator_ `SYMS_CvLeaf_DIMVARU_16t = 0x020a` (scope `__anon43fde12c2103`)
- L2147 _enumerator_ `SYMS_CvLeaf_DIMVARLU_16t = 0x020b` (scope `__anon43fde12c2103`)
- L2148 _enumerator_ `SYMS_CvLeaf_REFSYM = 0x020c` (scope `__anon43fde12c2103`)
- L2149 _enumerator_ `SYMS_CvLeaf_BCLASS_16t = 0x0400` (scope `__anon43fde12c2103`)
- L2150 _enumerator_ `SYMS_CvLeaf_VBCLASS_16t = 0x0401` (scope `__anon43fde12c2103`)
- L2151 _enumerator_ `SYMS_CvLeaf_IVBCLASS_16t = 0x0402` (scope `__anon43fde12c2103`)
- L2152 _enumerator_ `SYMS_CvLeaf_ENUMERATE_ST = 0x0403` (scope `__anon43fde12c2103`)
- L2153 _enumerator_ `SYMS_CvLeaf_FRIENDFCN_16t = 0x0404` (scope `__anon43fde12c2103`)
- L2154 _enumerator_ `SYMS_CvLeaf_INDEX_16t = 0x0405` (scope `__anon43fde12c2103`)
- L2155 _enumerator_ `SYMS_CvLeaf_MEMBER_16t = 0x0406` (scope `__anon43fde12c2103`)
- L2156 _enumerator_ `SYMS_CvLeaf_STMEMBER_16t = 0x0407` (scope `__anon43fde12c2103`)
- L2157 _enumerator_ `SYMS_CvLeaf_METHOD_16t = 0x0408` (scope `__anon43fde12c2103`)
- L2158 _enumerator_ `SYMS_CvLeaf_NESTTYPE_16t = 0x0409` (scope `__anon43fde12c2103`)
- L2159 _enumerator_ `SYMS_CvLeaf_VFUNCTAB_16t = 0x040a` (scope `__anon43fde12c2103`)
- L2160 _enumerator_ `SYMS_CvLeaf_FRIENDCLS_16t = 0x040b` (scope `__anon43fde12c2103`)
- L2161 _enumerator_ `SYMS_CvLeaf_ONEMETHOD_16t = 0x040c` (scope `__anon43fde12c2103`)
- L2162 _enumerator_ `SYMS_CvLeaf_VFUNCOFF_16t = 0x040d` (scope `__anon43fde12c2103`)
- L2163 _enumerator_ `SYMS_CvLeaf_TI16_MAX = 0x1000` (scope `__anon43fde12c2103`)
- L2165 _enumerator_ `SYMS_CvLeaf_MODIFIER = 0x1001` (scope `__anon43fde12c2103`) — 32-bit type index versions of leaves, all have the 0x1000 bit set
- L2166 _enumerator_ `SYMS_CvLeaf_POINTER = 0x1002` (scope `__anon43fde12c2103`)
- L2167 _enumerator_ `SYMS_CvLeaf_ARRAY_ST = 0x1003` (scope `__anon43fde12c2103`)
- L2168 _enumerator_ `SYMS_CvLeaf_CLASS_ST = 0x1004` (scope `__anon43fde12c2103`)
- L2169 _enumerator_ `SYMS_CvLeaf_STRUCTURE_ST = 0x1005` (scope `__anon43fde12c2103`)
- L2170 _enumerator_ `SYMS_CvLeaf_UNION_ST = 0x1006` (scope `__anon43fde12c2103`)
- L2171 _enumerator_ `SYMS_CvLeaf_ENUM_ST = 0x1007` (scope `__anon43fde12c2103`)
- L2172 _enumerator_ `SYMS_CvLeaf_PROCEDURE = 0x1008` (scope `__anon43fde12c2103`)
- L2173 _enumerator_ `SYMS_CvLeaf_MFUNCTION = 0x1009` (scope `__anon43fde12c2103`)
- L2174 _enumerator_ `SYMS_CvLeaf_COBOL0 = 0x100a` (scope `__anon43fde12c2103`)
- L2175 _enumerator_ `SYMS_CvLeaf_BARRAY = 0x100b` (scope `__anon43fde12c2103`)
- L2176 _enumerator_ `SYMS_CvLeaf_DIMARRAY_ST = 0x100c` (scope `__anon43fde12c2103`)
- L2177 _enumerator_ `SYMS_CvLeaf_VFTPATH = 0x100d` (scope `__anon43fde12c2103`)
- L2178 _enumerator_ `SYMS_CvLeaf_PRECOMP_ST = 0x100e` (scope `__anon43fde12c2103`)
- L2180 _enumerator_ `SYMS_CvLeaf_OEM = 0x100f` (scope `__anon43fde12c2103`) — not referenced from symbol
- L2182 _enumerator_ `SYMS_CvLeaf_ALIAS_ST = 0x1010` (scope `__anon43fde12c2103`) — oem definable type string
- L2184 _enumerator_ `SYMS_CvLeaf_OEM2 = 0x1011` (scope `__anon43fde12c2103`) — alias (typedef) type
- L2186 _enumerator_ `SYMS_CvLeaf_SKIP = 0x1200` (scope `__anon43fde12c2103`) — leaf indices starting records but referenced only from type records
- L2187 _enumerator_ `SYMS_CvLeaf_ARGLIST = 0x1201` (scope `__anon43fde12c2103`)
- L2188 _enumerator_ `SYMS_CvLeaf_DEFARG_ST = 0x1202` (scope `__anon43fde12c2103`)
- L2189 _enumerator_ `SYMS_CvLeaf_FIELDLIST = 0x1203` (scope `__anon43fde12c2103`)
- L2190 _enumerator_ `SYMS_CvLeaf_DERIVED = 0x1204` (scope `__anon43fde12c2103`)
- L2191 _enumerator_ `SYMS_CvLeaf_BITFIELD = 0x1205` (scope `__anon43fde12c2103`)
- L2192 _enumerator_ `SYMS_CvLeaf_METHODLIST = 0x1206` (scope `__anon43fde12c2103`)
- L2193 _enumerator_ `SYMS_CvLeaf_DIMCONU = 0x1207` (scope `__anon43fde12c2103`)
- L2194 _enumerator_ `SYMS_CvLeaf_DIMCONLU = 0x1208` (scope `__anon43fde12c2103`)
- L2195 _enumerator_ `SYMS_CvLeaf_DIMVARU = 0x1209` (scope `__anon43fde12c2103`)
- L2196 _enumerator_ `SYMS_CvLeaf_DIMVARLU = 0x120a` (scope `__anon43fde12c2103`)
- L2197 _enumerator_ `SYMS_CvLeaf_BCLASS = 0x1400` (scope `__anon43fde12c2103`)
- L2198 _enumerator_ `SYMS_CvLeaf_VBCLASS = 0x1401` (scope `__anon43fde12c2103`)
- L2199 _enumerator_ `SYMS_CvLeaf_IVBCLASS = 0x1402` (scope `__anon43fde12c2103`)
- L2200 _enumerator_ `SYMS_CvLeaf_FRIENDFCN_ST = 0x1403` (scope `__anon43fde12c2103`)
- L2201 _enumerator_ `SYMS_CvLeaf_INDEX = 0x1404` (scope `__anon43fde12c2103`)
- L2202 _enumerator_ `SYMS_CvLeaf_MEMBER_ST = 0x1405` (scope `__anon43fde12c2103`)
- L2203 _enumerator_ `SYMS_CvLeaf_STMEMBER_ST = 0x1406` (scope `__anon43fde12c2103`)
- L2204 _enumerator_ `SYMS_CvLeaf_METHOD_ST = 0x1407` (scope `__anon43fde12c2103`)
- L2205 _enumerator_ `SYMS_CvLeaf_NESTTYPE_ST = 0x1408` (scope `__anon43fde12c2103`)
- L2206 _enumerator_ `SYMS_CvLeaf_VFUNCTAB = 0x1409` (scope `__anon43fde12c2103`)
- L2207 _enumerator_ `SYMS_CvLeaf_FRIENDCLS = 0x140a` (scope `__anon43fde12c2103`)
- L2208 _enumerator_ `SYMS_CvLeaf_ONEMETHOD_ST = 0x140b` (scope `__anon43fde12c2103`)
- L2209 _enumerator_ `SYMS_CvLeaf_VFUNCOFF = 0x140c` (scope `__anon43fde12c2103`)
- L2210 _enumerator_ `SYMS_CvLeaf_NESTTYPEEX_ST = 0x140d` (scope `__anon43fde12c2103`)
- L2211 _enumerator_ `SYMS_CvLeaf_MEMBERMODIFY_ST = 0x140e` (scope `__anon43fde12c2103`)
- L2212 _enumerator_ `SYMS_CvLeaf_MANAGED_ST = 0x140f` (scope `__anon43fde12c2103`)
- L2213 _enumerator_ `SYMS_CvLeaf_ST_MAX = 0x1500` (scope `__anon43fde12c2103`)
- L2215 _enumerator_ `SYMS_CvLeaf_TYPESERVER = 0x1501` (scope `__anon43fde12c2103`) — Types w/ SZ names
- L2217 _enumerator_ `SYMS_CvLeaf_ENUMERATE = 0x1502` (scope `__anon43fde12c2103`) — not referenced from symbol
- L2218 _enumerator_ `SYMS_CvLeaf_ARRAY = 0x1503` (scope `__anon43fde12c2103`)
- L2219 _enumerator_ `SYMS_CvLeaf_CLASS = 0x1504` (scope `__anon43fde12c2103`)
- L2220 _enumerator_ `SYMS_CvLeaf_STRUCTURE = 0x1505` (scope `__anon43fde12c2103`)
- L2221 _enumerator_ `SYMS_CvLeaf_UNION = 0x1506` (scope `__anon43fde12c2103`)
- L2222 _enumerator_ `SYMS_CvLeaf_ENUM = 0x1507` (scope `__anon43fde12c2103`)
- L2223 _enumerator_ `SYMS_CvLeaf_DIMARRAY = 0x1508` (scope `__anon43fde12c2103`)
- L2224 _enumerator_ `SYMS_CvLeaf_PRECOMP = 0x1509` (scope `__anon43fde12c2103`)
- L2226 _enumerator_ `SYMS_CvLeaf_ALIAS = 0x150a` (scope `__anon43fde12c2103`) — not referenced from symbol
- L2228 _enumerator_ `SYMS_CvLeaf_DEFARG = 0x150b` (scope `__anon43fde12c2103`) — alias (typedef) type
- L2229 _enumerator_ `SYMS_CvLeaf_FRIENDFCN = 0x150c` (scope `__anon43fde12c2103`)
- L2230 _enumerator_ `SYMS_CvLeaf_MEMBER = 0x150d` (scope `__anon43fde12c2103`)
- L2231 _enumerator_ `SYMS_CvLeaf_STMEMBER = 0x150e` (scope `__anon43fde12c2103`)
- L2232 _enumerator_ `SYMS_CvLeaf_METHOD = 0x150f` (scope `__anon43fde12c2103`)
- L2233 _enumerator_ `SYMS_CvLeaf_NESTTYPE = 0x1510` (scope `__anon43fde12c2103`)
- L2234 _enumerator_ `SYMS_CvLeaf_ONEMETHOD = 0x1511` (scope `__anon43fde12c2103`)
- L2235 _enumerator_ `SYMS_CvLeaf_NESTTYPEEX = 0x1512` (scope `__anon43fde12c2103`)
- L2236 _enumerator_ `SYMS_CvLeaf_MEMBERMODIFY = 0x1513` (scope `__anon43fde12c2103`)
- L2237 _enumerator_ `SYMS_CvLeaf_MANAGED = 0x1514` (scope `__anon43fde12c2103`)
- L2238 _enumerator_ `SYMS_CvLeaf_TYPESERVER2 = 0x1515` (scope `__anon43fde12c2103`)
- L2239 _enumerator_ `SYMS_CvLeaf_STRIDED_ARRAY = 0x1516` (scope `__anon43fde12c2103`)
- L2241 _enumerator_ `SYMS_CvLeaf_HLSL = 0x1517` (scope `__anon43fde12c2103`) — same as LF_ARRAY, but with stride between adjacent elements
- L2242 _enumerator_ `SYMS_CvLeaf_MODIFIER_EX = 0x1518` (scope `__anon43fde12c2103`)
- L2243 _enumerator_ `SYMS_CvLeaf_INTERFACE = 0x1519` (scope `__anon43fde12c2103`)
- L2244 _enumerator_ `SYMS_CvLeaf_BINTERFACE = 0x151a` (scope `__anon43fde12c2103`)
- L2245 _enumerator_ `SYMS_CvLeaf_VECTOR = 0x151b` (scope `__anon43fde12c2103`)
- L2246 _enumerator_ `SYMS_CvLeaf_MATRIX = 0x151c` (scope `__anon43fde12c2103`)
- L2247 _enumerator_ `SYMS_CvLeaf_VFTABLE = 0x151d` (scope `__anon43fde12c2103`)
- L2249 _enumerator_ `SYMS_CvLeaf_ENDOFLEAFRECORD = SYMS_CvLeaf_VFTABLE` (scope `__anon43fde12c2103`) — a virtual function table
- L2250 _enumerator_ `SYMS_CvLeaf_TYPE_LAST` (scope `__anon43fde12c2103`)
- L2252 _enumerator_ `SYMS_CvLeaf_TYPE_MAX = SYMS_CvLeaf_TYPE_LAST` (scope `__anon43fde12c2103`) — one greater than the last type record
- L2253 _enumerator_ `SYMS_CvLeaf_FUNC_ID = 0x1601` (scope `__anon43fde12c2103`)
- L2255 _enumerator_ `SYMS_CvLeaf_MFUNC_ID = 0x1602` (scope `__anon43fde12c2103`) — static func ID
- L2257 _enumerator_ `SYMS_CvLeaf_BUILDINFO = 0x1603` (scope `__anon43fde12c2103`) — member func ID
- L2259 _enumerator_ `SYMS_CvLeaf_SUBSTR_LIST = 0x1604` (scope `__anon43fde12c2103`) — build info: tool, version, command line, src/pdb file
- L2261 _enumerator_ `SYMS_CvLeaf_STRING_ID = 0x1605` (scope `__anon43fde12c2103`) — similar to LF_ARGLIST, for list of sub strings
- L2263 _enumerator_ `SYMS_CvLeaf_UDT_SRC_LINE = 0x1606` (scope `__anon43fde12c2103`) — string ID
- L2265 _enumerator_ `SYMS_CvLeaf_UDT_MOD_SRC_LINE = 0x1607` (scope `__anon43fde12c2103`) — only generated by compiler
- L2267 _enumerator_ `SYMS_CvLeaf_CLASSPTR = 0x1608` (scope `__anon43fde12c2103`) — only generated by linker
- L2268 _enumerator_ `SYMS_CvLeaf_CLASSPTR2 = 0x1609` (scope `__anon43fde12c2103`)
- L2269 _enumerator_ `SYMS_CvLeaf_ID_LAST` (scope `__anon43fde12c2103`)
- L2271 _enumerator_ `SYMS_CvLeaf_ID_MAX = SYMS_CvLeaf_ID_LAST` (scope `__anon43fde12c2103`) — one greater than the last ID record
- L2272 _enumerator_ `SYMS_CvLeaf_NUMERIC = 0x8000` (scope `__anon43fde12c2103`)
- L2273 _enumerator_ `SYMS_CvLeaf_CHAR = 0x8000` (scope `__anon43fde12c2103`)
- L2274 _enumerator_ `SYMS_CvLeaf_SHORT = 0x8001` (scope `__anon43fde12c2103`)
- L2275 _enumerator_ `SYMS_CvLeaf_USHORT = 0x8002` (scope `__anon43fde12c2103`)
- L2276 _enumerator_ `SYMS_CvLeaf_LONG = 0x8003` (scope `__anon43fde12c2103`)
- L2277 _enumerator_ `SYMS_CvLeaf_ULONG = 0x8004` (scope `__anon43fde12c2103`)
- L2278 _enumerator_ `SYMS_CvLeaf_FLOAT32 = 0x8005` (scope `__anon43fde12c2103`)
- L2279 _enumerator_ `SYMS_CvLeaf_FLOAT64 = 0x8006` (scope `__anon43fde12c2103`)
- L2280 _enumerator_ `SYMS_CvLeaf_FLOAT80 = 0x8007` (scope `__anon43fde12c2103`)
- L2281 _enumerator_ `SYMS_CvLeaf_FLOAT128 = 0x8008` (scope `__anon43fde12c2103`)
- L2282 _enumerator_ `SYMS_CvLeaf_QUADWORD = 0x8009` (scope `__anon43fde12c2103`)
- L2283 _enumerator_ `SYMS_CvLeaf_UQUADWORD = 0x800a` (scope `__anon43fde12c2103`)
- L2284 _enumerator_ `SYMS_CvLeaf_FLOAT48 = 0x800b` (scope `__anon43fde12c2103`)
- L2285 _enumerator_ `SYMS_CvLeaf_COMPLEX32 = 0x800c` (scope `__anon43fde12c2103`)
- L2286 _enumerator_ `SYMS_CvLeaf_COMPLEX64 = 0x800d` (scope `__anon43fde12c2103`)
- L2287 _enumerator_ `SYMS_CvLeaf_COMPLEX80 = 0x800e` (scope `__anon43fde12c2103`)
- L2288 _enumerator_ `SYMS_CvLeaf_COMPLEX128 = 0x800f` (scope `__anon43fde12c2103`)
- L2289 _enumerator_ `SYMS_CvLeaf_VARSTRING = 0x8010` (scope `__anon43fde12c2103`)
- L2290 _enumerator_ `SYMS_CvLeaf_OCTWORD = 0x8017` (scope `__anon43fde12c2103`)
- L2291 _enumerator_ `SYMS_CvLeaf_UOCTWORD = 0x8018` (scope `__anon43fde12c2103`)
- L2292 _enumerator_ `SYMS_CvLeaf_DECIMAL = 0x8019` (scope `__anon43fde12c2103`)
- L2293 _enumerator_ `SYMS_CvLeaf_DATE = 0x801a` (scope `__anon43fde12c2103`)
- L2294 _enumerator_ `SYMS_CvLeaf_UTF8STRING = 0x801b` (scope `__anon43fde12c2103`)
- L2295 _enumerator_ `SYMS_CvLeaf_FLOAT16 = 0x801c` (scope `__anon43fde12c2103`)
- L2296 _enumerator_ `SYMS_CvLeaf_PAD0 = 0xf0` (scope `__anon43fde12c2103`)
- L2297 _enumerator_ `SYMS_CvLeaf_PAD1 = 0xf1` (scope `__anon43fde12c2103`)
- L2298 _enumerator_ `SYMS_CvLeaf_PAD2 = 0xf2` (scope `__anon43fde12c2103`)
- L2299 _enumerator_ `SYMS_CvLeaf_PAD3 = 0xf3` (scope `__anon43fde12c2103`)
- L2300 _enumerator_ `SYMS_CvLeaf_PAD4 = 0xf4` (scope `__anon43fde12c2103`)
- L2301 _enumerator_ `SYMS_CvLeaf_PAD5 = 0xf5` (scope `__anon43fde12c2103`)
- L2302 _enumerator_ `SYMS_CvLeaf_PAD6 = 0xf6` (scope `__anon43fde12c2103`)
- L2303 _enumerator_ `SYMS_CvLeaf_PAD7 = 0xf7` (scope `__anon43fde12c2103`)
- L2304 _enumerator_ `SYMS_CvLeaf_PAD8 = 0xf8` (scope `__anon43fde12c2103`)
- L2305 _enumerator_ `SYMS_CvLeaf_PAD9 = 0xf9` (scope `__anon43fde12c2103`)
- L2306 _enumerator_ `SYMS_CvLeaf_PAD10 = 0xfa` (scope `__anon43fde12c2103`)
- L2307 _enumerator_ `SYMS_CvLeaf_PAD11 = 0xfb` (scope `__anon43fde12c2103`)
- L2308 _enumerator_ `SYMS_CvLeaf_PAD12 = 0xfc` (scope `__anon43fde12c2103`)
- L2309 _enumerator_ `SYMS_CvLeaf_PAD13 = 0xfd` (scope `__anon43fde12c2103`)
- L2310 _enumerator_ `SYMS_CvLeaf_PAD14 = 0xfe` (scope `__anon43fde12c2103`)
- L2311 _enumerator_ `SYMS_CvLeaf_PAD15 = 0xff` (scope `__anon43fde12c2103`)
- L2312 _enumerator_ `SYMS_CvLeaf_COUNT = 178` (scope `__anon43fde12c2103`)
- L2314 _typedef_ `typedef SYMS_U16 SYMS_CvModifierFlags;`
- L2316 _enumerator_ `SYMS_CvModifierFlag_CONST = (1 << 0)` (scope `__anon43fde12c2203`)
- L2317 _enumerator_ `SYMS_CvModifierFlag_VOLATILE = (1 << 1)` (scope `__anon43fde12c2203`)
- L2318 _enumerator_ `SYMS_CvModifierFlag_UNALIGNED = (1 << 2)` (scope `__anon43fde12c2203`)
- L2320 _typedef_ `typedef SYMS_U8 SYMS_CvHFAKind;`
- L2322 _enumerator_ `SYMS_CvHFAKind_NONE` (scope `__anon43fde12c2303`)
- L2323 _enumerator_ `SYMS_CvHFAKind_FLOAT` (scope `__anon43fde12c2303`)
- L2324 _enumerator_ `SYMS_CvHFAKind_DOUBLE` (scope `__anon43fde12c2303`)
- L2325 _enumerator_ `SYMS_CvHFAKind_OTHER` (scope `__anon43fde12c2303`)
- L2326 _enumerator_ `SYMS_CvHFAKind_COUNT = 4` (scope `__anon43fde12c2303`)
- L2328 _typedef_ `typedef SYMS_U8 SYMS_CvMoComUDTKind;`
- L2330 _enumerator_ `SYMS_CvMoComUDTKind_NONE` (scope `__anon43fde12c2403`)
- L2331 _enumerator_ `SYMS_CvMoComUDTKind_REF` (scope `__anon43fde12c2403`)
- L2332 _enumerator_ `SYMS_CvMoComUDTKind_VALUE` (scope `__anon43fde12c2403`)
- L2333 _enumerator_ `SYMS_CvMoComUDTKind_INTERFACE` (scope `__anon43fde12c2403`)
- L2334 _enumerator_ `SYMS_CvMoComUDTKind_COUNT = 4` (scope `__anon43fde12c2403`)
- L2336 _typedef_ `typedef SYMS_U16 SYMS_CvTypeProps;`
- L2338 _enumerator_ `SYMS_CvTypeProp_PACKED = (1 << 0)` (scope `__anon43fde12c2503`)
- L2339 _enumerator_ `SYMS_CvTypeProp_CTOR = (1 << 1)` (scope `__anon43fde12c2503`)
- L2340 _enumerator_ `SYMS_CvTypeProp_OVLOPS = (1 << 2)` (scope `__anon43fde12c2503`)
- L2341 _enumerator_ `SYMS_CvTypeProp_ISNSESTED = (1 << 3)` (scope `__anon43fde12c2503`)
- L2342 _enumerator_ `SYMS_CvTypeProp_CNESTED = (1 << 4)` (scope `__anon43fde12c2503`)
- L2343 _enumerator_ `SYMS_CvTypeProp_OPASSIGN = (1 << 5)` (scope `__anon43fde12c2503`)
- L2344 _enumerator_ `SYMS_CvTypeProp_OPCAST = (1 << 6)` (scope `__anon43fde12c2503`)
- L2345 _enumerator_ `SYMS_CvTypeProp_FWDREF = (1 << 7)` (scope `__anon43fde12c2503`)
- L2346 _enumerator_ `SYMS_CvTypeProp_SCOPED = (1 << 8)` (scope `__anon43fde12c2503`)
- L2347 _enumerator_ `SYMS_CvTypeProp_HAS_UNIQUE_NAME = (1 << 9)` (scope `__anon43fde12c2503`)
- L2348 _enumerator_ `SYMS_CvTypeProp_SEALED = (1 << 10)` (scope `__anon43fde12c2503`)
- L2349 _enumerator_ `SYMS_CvTypeProp_HFA_SHIFT = 11` (scope `__anon43fde12c2503`)
- L2349 _enumerator_ `SYMS_CvTypeProp_HFA_SHIFT = 11` (scope `__anon43fde12c2503`)
- L2350 _enumerator_ `SYMS_CvTypeProp_INTRINSIC = (1 << 13)` (scope `__anon43fde12c2503`)
- L2351 _enumerator_ `SYMS_CvTypeProp_MOCOM_SHIFT = 14` (scope `__anon43fde12c2503`)
- L2351 _enumerator_ `SYMS_CvTypeProp_MOCOM_SHIFT = 14` (scope `__anon43fde12c2503`)
- L2353 _macro_ `#define SYMS_CvTypeProps_Extract_HFA(f) (SYMS_CvHFAKind)(((f) >> SYMS_CvTypeProp_HFA_SHIFT) & SYMS_CvTypeProp_HFA_MASK)`
- L2354 _macro_ `#define SYMS_CvTypeProps_Extract_MOCOM(f) (SYMS_CvMoComUDTKind)(((f) >> SYMS_CvTypeProp_MOCOM_SHIFT) & SYMS_CvTypeProp_MOCOM_MASK)`
- L2355 _typedef_ `typedef SYMS_U8 SYMS_CvPointerKind;`
- L2357 _enumerator_ `SYMS_CvPointerKind_NEAR = 0x00` (scope `__anon43fde12c2603`)
- L2359 _enumerator_ `SYMS_CvPointerKind_FAR = 0x01` (scope `__anon43fde12c2603`) — 16 bit pointer
- L2361 _enumerator_ `SYMS_CvPointerKind_HUGE = 0x02` (scope `__anon43fde12c2603`) — 16:16 far pointer
- L2363 _enumerator_ `SYMS_CvPointerKind_BASE_SEG = 0x03` (scope `__anon43fde12c2603`) — 16:16 huge pointer
- L2365 _enumerator_ `SYMS_CvPointerKind_BASE_VAL = 0x04` (scope `__anon43fde12c2603`) — based on segment
- L2367 _enumerator_ `SYMS_CvPointerKind_BASE_SEGVAL = 0x05` (scope `__anon43fde12c2603`) — based on value of base
- L2369 _enumerator_ `SYMS_CvPointerKind_BASE_ADDR = 0x06` (scope `__anon43fde12c2603`) — based on segment value of base
- L2371 _enumerator_ `SYMS_CvPointerKind_BASE_SEGADDR = 0x07` (scope `__anon43fde12c2603`) — based on address of base
- L2373 _enumerator_ `SYMS_CvPointerKind_BASE_TYPE = 0x08` (scope `__anon43fde12c2603`) — based on segment address of base
- L2375 _enumerator_ `SYMS_CvPointerKind_BASE_SELF = 0x09` (scope `__anon43fde12c2603`) — based on type
- L2377 _enumerator_ `SYMS_CvPointerKind_NEAR32 = 0x0a` (scope `__anon43fde12c2603`) — based on self
- L2379 _enumerator_ `SYMS_CvPointerKind_FAR32 = 0x0b` (scope `__anon43fde12c2603`) — 32 bit pointer
- L2381 _enumerator_ `SYMS_CvPointerKind_64 = 0x0c` (scope `__anon43fde12c2603`) — 16:32 pointer
- L2383 _enumerator_ `SYMS_CvPointerKind_UNUSEDPTR = 0x0d` (scope `__anon43fde12c2603`) — 64 bit pointer
- L2384 _enumerator_ `SYMS_CvPointerKind_COUNT = 14` (scope `__anon43fde12c2603`)
- L2386 _typedef_ `typedef SYMS_U8 SYMS_CvPointerMode;`
- L2388 _enumerator_ `SYMS_CvPointerMode_PTR = 0x00` (scope `__anon43fde12c2703`)
- L2390 _enumerator_ `SYMS_CvPointerMode_REF = 0x01` (scope `__anon43fde12c2703`) — "normal" pointer
- L2392 _enumerator_ `SYMS_CvPointerMode_LVREF = 0x01` (scope `__anon43fde12c2703`) — "old" reference
- L2394 _enumerator_ `SYMS_CvPointerMode_PMEM = 0x02` (scope `__anon43fde12c2703`) — l-value reference
- L2396 _enumerator_ `SYMS_CvPointerMode_PMFUNC = 0x03` (scope `__anon43fde12c2703`) — pointer to data member
- L2398 _enumerator_ `SYMS_CvPointerMode_RVREF = 0x04` (scope `__anon43fde12c2703`) — pointer to member function
- L2400 _enumerator_ `SYMS_CvPointerMode_RESERVED = 0x05` (scope `__anon43fde12c2703`) — r-value reference
- L2401 _enumerator_ `SYMS_CvPointerMode_COUNT = 7` (scope `__anon43fde12c2703`)
- L2403 _typedef_ `typedef SYMS_U32 SYMS_CvPointerAttribs;`
- L2405 _enumerator_ `SYMS_CvPointerAttrib_KIND_SHIFT = 0` (scope `__anon43fde12c2803`)
- L2405 _enumerator_ `SYMS_CvPointerAttrib_KIND_SHIFT = 0` (scope `__anon43fde12c2803`)
- L2406 _enumerator_ `SYMS_CvPointerAttrib_MODE_SHIFT = 5` (scope `__anon43fde12c2803`)
- L2406 _enumerator_ `SYMS_CvPointerAttrib_MODE_SHIFT = 5` (scope `__anon43fde12c2803`)
- L2407 _enumerator_ `SYMS_CvPointerAttrib_IS_FLAT = (1 << 8)` (scope `__anon43fde12c2803`)
- L2408 _enumerator_ `SYMS_CvPointerAttrib_IS_VOLATILE = (1 << 9)` (scope `__anon43fde12c2803`)
- L2409 _enumerator_ `SYMS_CvPointerAttrib_IS_CONST = (1 << 10)` (scope `__anon43fde12c2803`)
- L2410 _enumerator_ `SYMS_CvPointerAttrib_IS_UNALIGNED = (1 << 11)` (scope `__anon43fde12c2803`)
- L2411 _enumerator_ `SYMS_CvPointerAttrib_IS_RESTRICTED = (1 << 12)` (scope `__anon43fde12c2803`)
- L2412 _enumerator_ `SYMS_CvPointerAttrib_SIZE_SHIFT = 13` (scope `__anon43fde12c2803`)
- L2412 _enumerator_ `SYMS_CvPointerAttrib_SIZE_SHIFT = 13` (scope `__anon43fde12c2803`)
- L2413 _enumerator_ `SYMS_CvPointerAttrib_IS_MOCOM = (1 << 19)` (scope `__anon43fde12c2803`)
- L2414 _enumerator_ `SYMS_CvPointerAttrib_IS_LREF = (1 << 20)` (scope `__anon43fde12c2803`)
- L2415 _enumerator_ `SYMS_CvPointerAttrib_IS_RREF = (1 << 21)` (scope `__anon43fde12c2803`)
- L2417 _macro_ `#define SYMS_CvPointerAttribs_Extract_KIND(f) (SYMS_CvPointerKind)(((f) >> SYMS_CvPointerAttrib_KIND_SHIFT) & SYMS_CvPointerAttrib_KIND_MASK)`
- L2418 _macro_ `#define SYMS_CvPointerAttribs_Extract_MODE(f) (SYMS_CvPointerMode)(((f) >> SYMS_CvPointerAttrib_MODE_SHIFT) & SYMS_CvPointerAttrib_MODE_MASK)`
- L2419 _macro_ `#define SYMS_CvPointerAttribs_Extract_SIZE(f) (SYMS_U32)(((f) >> SYMS_CvPointerAttrib_SIZE_SHIFT) & SYMS_CvPointerAttrib_SIZE_MASK)`
- L2420 _typedef_ `typedef SYMS_U16 SYMS_CvMemberPointerKind;`
- L2422 _enumerator_ `SYMS_CvMemberPointerKind_Undef = 0x00` (scope `__anon43fde12c2903`)
- L2424 _enumerator_ `SYMS_CvMemberPointerKind_D_Single = 0x01` (scope `__anon43fde12c2903`) — not specified (pre VC8)
- L2426 _enumerator_ `SYMS_CvMemberPointerKind_D_Multiple = 0x02` (scope `__anon43fde12c2903`) — member data, single inheritance
- L2428 _enumerator_ `SYMS_CvMemberPointerKind_D_Virtual = 0x03` (scope `__anon43fde12c2903`) — member data, multiple inheritance
- L2430 _enumerator_ `SYMS_CvMemberPointerKind_D_General = 0x04` (scope `__anon43fde12c2903`) — member data, virtual inheritance
- L2432 _enumerator_ `SYMS_CvMemberPointerKind_F_Single = 0x05` (scope `__anon43fde12c2903`) — member data, most general
- L2434 _enumerator_ `SYMS_CvMemberPointerKind_F_Multiple = 0x06` (scope `__anon43fde12c2903`) — member function, single inheritance
- L2436 _enumerator_ `SYMS_CvMemberPointerKind_F_Virtual = 0x07` (scope `__anon43fde12c2903`) — member function, multiple inheritance
- L2438 _enumerator_ `SYMS_CvMemberPointerKind_F_General = 0x08` (scope `__anon43fde12c2903`) — member function, virtual inheritance
- L2439 _enumerator_ `SYMS_CvMemberPointerKind_COUNT = 9` (scope `__anon43fde12c2903`)
- L2441 _typedef_ `typedef SYMS_U32 SYMS_CvVirtualTableShape;`
- L2443 _enumerator_ `SYMS_CvVirtualTableShape_NEAR` (scope `__anon43fde12c2a03`)
- L2445 _enumerator_ `SYMS_CvVirtualTableShape_FAR` (scope `__anon43fde12c2a03`) — 16 bit pointer
- L2447 _enumerator_ `SYMS_CvVirtualTableShape_THIN` (scope `__anon43fde12c2a03`) — 16:16 bit pointer
- L2449 _enumerator_ `SYMS_CvVirtualTableShape_OUTER` (scope `__anon43fde12c2a03`) — ??
- L2451 _enumerator_ `SYMS_CvVirtualTableShape_META` (scope `__anon43fde12c2a03`) — MS pdf (page 36): Address point displacement to outermost class. This is at entry[-1] from table entry
- L2453 _enumerator_ `SYMS_CvVirtualTableShape_NEAR32` (scope `__anon43fde12c2a03`) — MS pdf (page 36): Far pointer to metaclass descriptor. This is at entry[-2] from table address.
- L2455 _enumerator_ `SYMS_CvVirtualTableShape_FAR32` (scope `__anon43fde12c2a03`) — 32bit pointer
- L2457 _enumerator_ `SYMS_CvVirtualTableShape_UNUSED` (scope `__anon43fde12c2a03`) — ??
- L2458 _enumerator_ `SYMS_CvVirtualTableShape_COUNT = 8` (scope `__anon43fde12c2a03`)
- L2460 _typedef_ `typedef SYMS_U8 SYMS_CvMethodProp;`
- L2462 _enumerator_ `SYMS_CvMethodProp_VANILLA = 0` (scope `__anon43fde12c2b03`)
- L2463 _enumerator_ `SYMS_CvMethodProp_VIRTUAL = 1` (scope `__anon43fde12c2b03`)
- L2464 _enumerator_ `SYMS_CvMethodProp_STATIC = 2` (scope `__anon43fde12c2b03`)
- L2465 _enumerator_ `SYMS_CvMethodProp_FRIEND = 3` (scope `__anon43fde12c2b03`)
- L2466 _enumerator_ `SYMS_CvMethodProp_INTRO = 4` (scope `__anon43fde12c2b03`)
- L2467 _enumerator_ `SYMS_CvMethodProp_PUREVIRT = 5` (scope `__anon43fde12c2b03`)
- L2468 _enumerator_ `SYMS_CvMethodProp_PUREINTRO = 6` (scope `__anon43fde12c2b03`)
- L2469 _enumerator_ `SYMS_CvMethodProp_COUNT = 7` (scope `__anon43fde12c2b03`)
- L2471 _typedef_ `typedef SYMS_U8 SYMS_CvMemberAccess;`
- L2473 _enumerator_ `SYMS_CvMemberAccess_NULL = 0` (scope `__anon43fde12c2c03`)
- L2474 _enumerator_ `SYMS_CvMemberAccess_PRIVATE = 1` (scope `__anon43fde12c2c03`)
- L2475 _enumerator_ `SYMS_CvMemberAccess_PROTECTED = 2` (scope `__anon43fde12c2c03`)
- L2476 _enumerator_ `SYMS_CvMemberAccess_PUBLIC = 3` (scope `__anon43fde12c2c03`)
- L2477 _enumerator_ `SYMS_CvMemberAccess_COUNT = 4` (scope `__anon43fde12c2c03`)
- L2479 _typedef_ `typedef SYMS_U16 SYMS_CvFieldAttribs;`
- L2481 _enumerator_ `SYMS_CvFieldAttrib_ACCESS_SHIFT = 0` (scope `__anon43fde12c2d03`)
- L2481 _enumerator_ `SYMS_CvFieldAttrib_ACCESS_SHIFT = 0` (scope `__anon43fde12c2d03`)
- L2482 _enumerator_ `SYMS_CvFieldAttrib_MPROP_SHIFT = 2` (scope `__anon43fde12c2d03`)
- L2482 _enumerator_ `SYMS_CvFieldAttrib_MPROP_SHIFT = 2` (scope `__anon43fde12c2d03`)
- L2483 _enumerator_ `SYMS_CvFieldAttrib_PSEUDO = (1 << 5)` (scope `__anon43fde12c2d03`)
- L2484 _enumerator_ `SYMS_CvFieldAttrib_NOINHERIT = (1 << 6)` (scope `__anon43fde12c2d03`)
- L2485 _enumerator_ `SYMS_CvFieldAttrib_NOCONSTRUCT = (1 << 7)` (scope `__anon43fde12c2d03`)
- L2486 _enumerator_ `SYMS_CvFieldAttrib_COMPGENX = (1 << 8)` (scope `__anon43fde12c2d03`)
- L2487 _enumerator_ `SYMS_CvFieldAttrib_SEALED = (1 << 9)` (scope `__anon43fde12c2d03`)
- L2489 _macro_ `#define SYMS_CvFieldAttribs_Extract_ACCESS(f) (SYMS_CvMemberAccess)(((f) >> SYMS_CvFieldAttrib_ACCESS_SHIFT) & SYMS_CvFieldAttrib_ACCESS_MASK)`
- L2490 _macro_ `#define SYMS_CvFieldAttribs_Extract_MPROP(f) (SYMS_CvMethodProp)(((f) >> SYMS_CvFieldAttrib_MPROP_SHIFT) & SYMS_CvFieldAttrib_MPROP_MASK)`
- L2491 _typedef_ `typedef SYMS_U16 SYMS_CvLabelKind;`
- L2493 _enumerator_ `SYMS_CvLabelKind_NEAR = 0` (scope `__anon43fde12c2e03`)
- L2494 _enumerator_ `SYMS_CvLabelKind_FAR = 4` (scope `__anon43fde12c2e03`)
- L2495 _enumerator_ `SYMS_CvLabelKind_COUNT = 2` (scope `__anon43fde12c2e03`)
- L2497 _typedef_ `typedef SYMS_U8 SYMS_CvFunctionAttribs;`
- L2499 _enumerator_ `SYMS_CvFunctionAttrib_CXXRETURNUDT = (1 << 0)` (scope `__anon43fde12c2f03`)
- L2500 _enumerator_ `SYMS_CvFunctionAttrib_CTOR = (1 << 1)` (scope `__anon43fde12c2f03`)
- L2501 _enumerator_ `SYMS_CvFunctionAttrib_CTORVBASE = (1 << 2)` (scope `__anon43fde12c2f03`)
- L2503 _typedef_ `typedef SYMS_U8 SYMS_CvCallKind;`
- L2505 _enumerator_ `SYMS_CvCallKind_NEAR_C = 0x00` (scope `__anon43fde12c3003`)
- L2507 _enumerator_ `SYMS_CvCallKind_FAR_C = 0x01` (scope `__anon43fde12c3003`) — near right to left push, caller pops stack
- L2509 _enumerator_ `SYMS_CvCallKind_NEAR_PASCAL = 0x02` (scope `__anon43fde12c3003`) — far right to left push, caller pops stack
- L2511 _enumerator_ `SYMS_CvCallKind_FAR_PASCAL = 0x03` (scope `__anon43fde12c3003`) — near left to right push, callee pops stack
- L2513 _enumerator_ `SYMS_CvCallKind_NEAR_FAST = 0x04` (scope `__anon43fde12c3003`) — far left to right push, callee pops stack
- L2515 _enumerator_ `SYMS_CvCallKind_FAR_FAST = 0x05` (scope `__anon43fde12c3003`) — near left to right push with regs, callee pops stack
- L2517 _enumerator_ `SYMS_CvCallKind_SKIPPED = 0x06` (scope `__anon43fde12c3003`) — far left to right push with regs, callee pops stack
- L2519 _enumerator_ `SYMS_CvCallKind_NEAR_STD = 0x07` (scope `__anon43fde12c3003`) — skipped (unused) call index
- L2521 _enumerator_ `SYMS_CvCallKind_FAR_STD = 0x08` (scope `__anon43fde12c3003`) — near standard call
- L2523 _enumerator_ `SYMS_CvCallKind_NEAR_SYS = 0x09` (scope `__anon43fde12c3003`) — far standard call
- L2525 _enumerator_ `SYMS_CvCallKind_FAR_SYS = 0x0a` (scope `__anon43fde12c3003`) — near sys call
- L2527 _enumerator_ `SYMS_CvCallKind_THISCALL = 0x0b` (scope `__anon43fde12c3003`) — far sys call
- L2529 _enumerator_ `SYMS_CvCallKind_MIPSCALL = 0x0c` (scope `__anon43fde12c3003`) — this call (this passed in register)
- L2531 _enumerator_ `SYMS_CvCallKind_GENERIC = 0x0d` (scope `__anon43fde12c3003`) — Mips call
- L2533 _enumerator_ `SYMS_CvCallKind_ALPHACALL = 0x0e` (scope `__anon43fde12c3003`) — Generic call sequence
- L2535 _enumerator_ `SYMS_CvCallKind_PPCCALL = 0x0f` (scope `__anon43fde12c3003`) — Alpha call
- L2537 _enumerator_ `SYMS_CvCallKind_SHCALL = 0x10` (scope `__anon43fde12c3003`) — PPC call
- L2539 _enumerator_ `SYMS_CvCallKind_ARMCALL = 0x11` (scope `__anon43fde12c3003`) — Hitachi SuperH call
- L2541 _enumerator_ `SYMS_CvCallKind_AM33CALL = 0x12` (scope `__anon43fde12c3003`) — ARM call
- L2543 _enumerator_ `SYMS_CvCallKind_TRICALL = 0x13` (scope `__anon43fde12c3003`) — AM33 call
- L2545 _enumerator_ `SYMS_CvCallKind_SH5CALL = 0x14` (scope `__anon43fde12c3003`) — TriCore Call
- L2547 _enumerator_ `SYMS_CvCallKind_M32RCALL = 0x15` (scope `__anon43fde12c3003`) — Hitachi SuperH-5 call
- L2549 _enumerator_ `SYMS_CvCallKind_CLRCALL = 0x16` (scope `__anon43fde12c3003`) — M32R Call
- L2551 _enumerator_ `SYMS_CvCallKind_INLINE = 0x17` (scope `__anon43fde12c3003`) — clr call
- L2553 _enumerator_ `SYMS_CvCallKind_NEAR_VECTOR = 0x18` (scope `__anon43fde12c3003`) — Marker for routines always inlined and thus lacking a convention
- L2555 _enumerator_ `SYMS_CvCallKind_RESERVED = 0x19` (scope `__anon43fde12c3003`) — near left to right push with regs, callee pops stack
- L2556 _enumerator_ `SYMS_CvCallKind_COUNT = 26` (scope `__anon43fde12c3003`)
- L2563 _typedef_ `} SYMS_CvLeafPreComp;` — variable-width: SYMS_U8 name;
- L2568 _typedef_ `} SYMS_CvLeafTypeServer;` — variable-width: SYMS_U8 name;
- L2573 _typedef_ `} SYMS_CvLeafTypeServer2;` — variable-width: SYMS_U8 name;
- L2577 _typedef_ `} SYMS_CvLeafBuildInfo;` — variable-width: SYMS_CvItemId arg;
- L2580 _typedef_ `} SYMS_CvLeafSkip_16t;`
- L2583 _typedef_ `} SYMS_CvLeafSkip;`
- L2586 _typedef_ `} SYMS_CvLeafVTShape;`
- L2589 _typedef_ `} SYMS_CvLeafLabel;`
- L2593 _typedef_ `} SYMS_CvLeafModifier;`
- L2597 _typedef_ `} SYMS_CvLeafPointer;`
- L2604 _typedef_ `} SYMS_CvLeafProcedure;`
- L2614 _typedef_ `} SYMS_CvLeafMFunction;`
- L2617 _typedef_ `} SYMS_CvLeafArgList;`
- L2622 _typedef_ `} SYMS_CvLeafBitField;`
- L2626 _typedef_ `} SYMS_CvLeafIndex;`
- L2630 _typedef_ `} SYMS_CvLeafArray;`
- L2637 _typedef_ `} SYMS_CvLeafStruct;`
- L2642 _typedef_ `} SYMS_CvLeafUnion;`
- L2648 _typedef_ `} SYMS_CvLeafEnum;`
- L2651 _typedef_ `} SYMS_CvLeafAlias;`
- L2657 _typedef_ `} SYMS_CvLeafMember;` — variable-width: SYMS_PdbNumeric offset; variable-width: SYMS_U8 name;
- L2662 _typedef_ `} SYMS_CvLeafStMember;` — variable-width: SYMS_U8 name;
- L2667 _typedef_ `} SYMS_CvLeafMethodListMember;`
- L2671 _typedef_ `} SYMS_CvLeafMethod;`
- L2675 _typedef_ `} SYMS_CvLeafOneMethod;`
- L2678 _typedef_ `} SYMS_CvLeafEnumerate;`
- L2682 _typedef_ `} SYMS_CvLeafNestType;`
- L2686 _typedef_ `} SYMS_CvLeafNestTypeEx;`
- L2690 _typedef_ `} SYMS_CvLeafBClass;`
- L2695 _typedef_ `} SYMS_CvLeafVBClass;`
- L2699 _typedef_ `} SYMS_CvLeafVFuncTab;`
- L2704 _typedef_ `} SYMS_CvLeafVFuncOff;`
- L2710 _typedef_ `} SYMS_CvLeafVFTable;`
- L2713 _typedef_ `} SYMS_CvLeafVFPath;`
- L2718 _typedef_ `} SYMS_CvLeafFuncId;`
- L2722 _typedef_ `} SYMS_CvLeafMFuncId;`
- L2727 _typedef_ `} SYMS_CvLeafStringId;` — variable-width: SYMS_U8 name;
- L2734 _typedef_ `} SYMS_CvLeafUDTSrcLine;`
- L2740 _typedef_ `} SYMS_CvLeafModSrcLine;`
- L2748 _typedef_ `} SYMS_CvLeafClassPtr;`
- L2749 _typedef_ `typedef SYMS_U32 SYMS_CvSubSectionKind;`
- L2751 _enumerator_ `SYMS_CvSubSectionKind_SYMBOLS = 0xf1` (scope `__anon43fde12c3103`)
- L2752 _enumerator_ `SYMS_CvSubSectionKind_LINES = 0xf2` (scope `__anon43fde12c3103`)
- L2753 _enumerator_ `SYMS_CvSubSectionKind_STRINGTABLE = 0xf3` (scope `__anon43fde12c3103`)
- L2754 _enumerator_ `SYMS_CvSubSectionKind_FILECHKSMS = 0xf4` (scope `__anon43fde12c3103`)
- L2755 _enumerator_ `SYMS_CvSubSectionKind_FRAMEDATA = 0xf5` (scope `__anon43fde12c3103`)
- L2756 _enumerator_ `SYMS_CvSubSectionKind_INLINEELINES = 0xf6` (scope `__anon43fde12c3103`)
- L2757 _enumerator_ `SYMS_CvSubSectionKind_CROSSSCOPEIMPORTS = 0xf7` (scope `__anon43fde12c3103`)
- L2758 _enumerator_ `SYMS_CvSubSectionKind_CROSSSCOPEEXPORTS = 0xf8` (scope `__anon43fde12c3103`)
- L2759 _enumerator_ `SYMS_CvSubSectionKind_IL_LINES = 0xf9` (scope `__anon43fde12c3103`)
- L2760 _enumerator_ `SYMS_CvSubSectionKind_FUNC_MDTOKEN_MAP = 0xfa` (scope `__anon43fde12c3103`)
- L2761 _enumerator_ `SYMS_CvSubSectionKind_TYPE_MDTOKEN_MAP = 0xfb` (scope `__anon43fde12c3103`)
- L2762 _enumerator_ `SYMS_CvSubSectionKind_MERGED_ASSEMBLY_INPUT = 0xfc` (scope `__anon43fde12c3103`)
- L2763 _enumerator_ `SYMS_CvSubSectionKind_COFF_SYMBOL_RVA = 0xfd` (scope `__anon43fde12c3103`)
- L2764 _enumerator_ `SYMS_CvSubSectionKind_XFG_HASH_TYPE = 0xff` (scope `__anon43fde12c3103`)
- L2765 _enumerator_ `SYMS_CvSubSectionKind_XFG_HASH_VRITUAL = 0x100` (scope `__anon43fde12c3103`)
- L2766 _enumerator_ `SYMS_CvSubSectionKind_COUNT = 15` (scope `__anon43fde12c3103`)
- L2771 _typedef_ `} SYMS_CvSubSectionHeader;`
- L2772 _typedef_ `typedef SYMS_U8 SYMS_CvChecksumKind;`
- L2774 _enumerator_ `SYMS_CvChecksumKind_NULL` (scope `__anon43fde12c3203`)
- L2775 _enumerator_ `SYMS_CvChecksumKind_MD5` (scope `__anon43fde12c3203`)
- L2776 _enumerator_ `SYMS_CvChecksumKind_SHA1` (scope `__anon43fde12c3203`)
- L2777 _enumerator_ `SYMS_CvChecksumKind_SHA256` (scope `__anon43fde12c3203`)
- L2778 _enumerator_ `SYMS_CvChecksumKind_COUNT = 4` (scope `__anon43fde12c3203`)
- L2785 _typedef_ `} SYMS_CvInlineeSourceLineSig;`
- L2792 _typedef_ `} SYMS_CvInlineeSourceLine;`
- L2799 _typedef_ `} SYMS_CvInlineeSourceLineEx;` — variable-width: SYMS_U32 extra_file_id;
- L2804 _prototype_ `SYMS_Language syms_cv_base_language_from_cv_language(SYMS_CvLanguage v);`
- L2805 _prototype_ `SYMS_MemVisibility syms_mem_visibility_from_member_access(SYMS_CvMemberAccess v);`
- L2813 _variable_ `SYMS_GLOBAL SYMS_RegSlice syms_reg_slices_X86[396] = { {SYMS_RegX86Code_nil, 0, 0}, {SYMS_RegX86Code_eax, 0, 1}, {SYMS_RegX86Code_ecx, 0, 1}, {SYMS_RegX86Code_edx, 0, 1}, {SYMS_RegX86Code_ebx, 0, 1}, {SYMS_RegX86Code_eax, 1, 1}, {SYMS_RegX86Code_ecx, 1, 1}, {SYMS_RegX86Code_edx, 1, 1}, {SYMS_RegX86Code_ebx, 1, 1}, {SYMS_RegX86Code_eax, 0, 2}, {SYMS_RegX86Code_ecx, 0, 2}, {SYMS_RegX86Code_edx, 0, 2}, {SYMS_RegX86Code_ebx, 0, 2}, {SYMS_RegX86Code_esp, 0, 2}, {SYMS_RegX86Code_ebp, 0, 2}, {SYMS_RegX86Code_esi, 0, 2}, {SYMS_RegX86Code_edi, 0, 2}, {SYMS_RegX86Code_eax, 0, 4}, {SYMS_RegX86Code_ecx, 0, 4}, {SYMS_RegX86Code_edx, 0, 4}, {SYMS_RegX86Code_ebx, 0, 4}, {SYMS_RegX86Code_esp, 0, 4}, {SYMS_RegX86Code_ebp, 0, 4}, {SYMS_RegX86Code_esi, 0, 4}, {SYMS_RegX86Code_edi, 0, 4}, {SYMS_RegX86Code_es, 0, 2}, {SYMS_RegX86Code_cs, 0, 2}, {SYMS_RegX86Code_ss, 0, 2}, {SYMS_RegX86Code_ds, 0, 2}, {SYMS_RegX86Code_fs, 0, 2}, {SYMS_RegX86Code_gs, 0, 2}, {SYMS_RegX86Code_eip, 0, 2}, {SYMS_RegX86Code_eflags, 0, 2}, {SYMS_RegX86Code_eip, 0, 4}, {SYMS_RegX86Code_eflags, 0, 4}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},`
- L3211 _variable_ `SYMS_GLOBAL SYMS_RegSlice syms_reg_slices_X64[688] = { {SYMS_RegX64Code_nil, 0, 0}, {SYMS_RegX64Code_rax, 0, 1}, {SYMS_RegX64Code_rcx, 0, 1}, {SYMS_RegX64Code_rdx, 0, 1}, {SYMS_RegX64Code_rbx, 0, 1}, {SYMS_RegX64Code_rax, 1, 1}, {SYMS_RegX64Code_rcx, 1, 1}, {SYMS_RegX64Code_rdx, 1, 1}, {SYMS_RegX64Code_rbx, 1, 1}, {SYMS_RegX64Code_rax, 0, 2}, {SYMS_RegX64Code_rcx, 0, 2}, {SYMS_RegX64Code_rdx, 0, 2}, {SYMS_RegX64Code_rbx, 0, 2}, {SYMS_RegX64Code_rsp, 0, 2}, {SYMS_RegX64Code_rbp, 0, 2}, {SYMS_RegX64Code_rsi, 0, 2}, {SYMS_RegX64Code_rdi, 0, 2}, {SYMS_RegX64Code_rax, 0, 4}, {SYMS_RegX64Code_rax, 0, 4}, {SYMS_RegX64Code_rdx, 0, 4}, {SYMS_RegX64Code_rbx, 0, 4}, {SYMS_RegX64Code_rsp, 0, 4}, {SYMS_RegX64Code_rbp, 0, 4}, {SYMS_RegX64Code_rsi, 0, 4}, {SYMS_RegX64Code_rdi, 0, 4}, {SYMS_RegX64Code_es, 0, 2}, {SYMS_RegX64Code_cs, 0, 2}, {SYMS_RegX64Code_ss, 0, 2}, {SYMS_RegX64Code_ds, 0, 2}, {SYMS_RegX64Code_fs, 0, 2}, {SYMS_RegX64Code_gs, 0, 2}, {0, 0, 0}, {SYMS_RegX64Code_rflags, 0, 2}, {SYMS_RegX64Code_rip, 0, 8}, {SYMS_RegX64Code_rflags, 0, 4}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_debug_info.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L7-14_

#### enum `SYMS_SymbolKind`  
`typedef enum SYMS_SymbolKind`  
_L15-26_
- L16 _public enumerator_ `SYMS_SymbolKind_Null`
- L17 _public enumerator_ `SYMS_SymbolKind_Type`
- L18 _public enumerator_ `SYMS_SymbolKind_Procedure`
- L19 _public enumerator_ `SYMS_SymbolKind_ImageRelativeVariable`
- L20 _public enumerator_ `SYMS_SymbolKind_LocalVariable`
- L21 _public enumerator_ `SYMS_SymbolKind_TLSVariable`
- L22 _public enumerator_ `SYMS_SymbolKind_Const`
- L23 _public enumerator_ `SYMS_SymbolKind_Scope`
- L24 _public enumerator_ `SYMS_SymbolKind_Inline`
- L25 _public enumerator_ `SYMS_SymbolKind_COUNT = 9`

#### enum `SYMS_TypeKind`  
`typedef enum SYMS_TypeKind`  
_L27-80_
- L28 _public enumerator_ `SYMS_TypeKind_Null`
- L29 _public enumerator_ `SYMS_TypeKind_Stub`
- L31 _public enumerator_ `SYMS_TypeKind_Int8` — @maintenance(allen) sync with 'syms_type_kind_is_basic'
- L32 _public enumerator_ `SYMS_TypeKind_Int16`
- L33 _public enumerator_ `SYMS_TypeKind_Int32`
- L34 _public enumerator_ `SYMS_TypeKind_Int64`
- L35 _public enumerator_ `SYMS_TypeKind_Int128`
- L36 _public enumerator_ `SYMS_TypeKind_Int256`
- L37 _public enumerator_ `SYMS_TypeKind_Int512`
- L38 _public enumerator_ `SYMS_TypeKind_UInt8`
- L39 _public enumerator_ `SYMS_TypeKind_UInt16`
- L40 _public enumerator_ `SYMS_TypeKind_UInt32`
- L41 _public enumerator_ `SYMS_TypeKind_UInt64`
- L42 _public enumerator_ `SYMS_TypeKind_UInt128`
- L43 _public enumerator_ `SYMS_TypeKind_UInt256`
- L44 _public enumerator_ `SYMS_TypeKind_UInt512`
- L45 _public enumerator_ `SYMS_TypeKind_Bool`
- L46 _public enumerator_ `SYMS_TypeKind_Float16`
- L47 _public enumerator_ `SYMS_TypeKind_Float32`
- L48 _public enumerator_ `SYMS_TypeKind_Float32PP`
- L49 _public enumerator_ `SYMS_TypeKind_Float48`
- L50 _public enumerator_ `SYMS_TypeKind_Float64`
- L51 _public enumerator_ `SYMS_TypeKind_Float80`
- L52 _public enumerator_ `SYMS_TypeKind_Float128`
- L53 _public enumerator_ `SYMS_TypeKind_Complex32`
- L54 _public enumerator_ `SYMS_TypeKind_Complex64`
- L55 _public enumerator_ `SYMS_TypeKind_Complex80`
- L56 _public enumerator_ `SYMS_TypeKind_Complex128`
- L57 _public enumerator_ `SYMS_TypeKind_Void`
- L59 _public enumerator_ `SYMS_TypeKind_Struct` — 'syms_type_kind_is_record'
- L60 _public enumerator_ `SYMS_TypeKind_Class`
- L61 _public enumerator_ `SYMS_TypeKind_Union`
- L62 _public enumerator_ `SYMS_TypeKind_Enum`
- L63 _public enumerator_ `SYMS_TypeKind_Typedef`
- L65 _public enumerator_ `SYMS_TypeKind_ForwardStruct` — @maintenance(allen) sync with 'syms_type_kind_is_forward'
- L66 _public enumerator_ `SYMS_TypeKind_ForwardClass`
- L67 _public enumerator_ `SYMS_TypeKind_ForwardUnion`
- L68 _public enumerator_ `SYMS_TypeKind_ForwardEnum`
- L69 _public enumerator_ `SYMS_TypeKind_Modifier`
- L70 _public enumerator_ `SYMS_TypeKind_Ptr`
- L71 _public enumerator_ `SYMS_TypeKind_LValueReference`
- L72 _public enumerator_ `SYMS_TypeKind_RValueReference`
- L73 _public enumerator_ `SYMS_TypeKind_MemberPtr`
- L74 _public enumerator_ `SYMS_TypeKind_Array`
- L75 _public enumerator_ `SYMS_TypeKind_Proc`
- L76 _public enumerator_ `SYMS_TypeKind_Bitfield`
- L77 _public enumerator_ `SYMS_TypeKind_Variadic`
- L78 _public enumerator_ `SYMS_TypeKind_Label`
- L79 _public enumerator_ `SYMS_TypeKind_COUNT = 48`

#### enum `(anonymous)`  
`enum`  
_L82-91_

#### enum `SYMS_MemVisibility`  
`typedef enum SYMS_MemVisibility`  
_L92-98_
- L93 _public enumerator_ `SYMS_MemVisibility_Null`
- L94 _public enumerator_ `SYMS_MemVisibility_Private`
- L95 _public enumerator_ `SYMS_MemVisibility_Public`
- L96 _public enumerator_ `SYMS_MemVisibility_Protected`
- L97 _public enumerator_ `SYMS_MemVisibility_COUNT = 4`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_DEBUG_INFO_H`
- L6 _typedef_ `typedef SYMS_U32 SYMS_UnitFeatures;`
- L8 _enumerator_ `SYMS_UnitFeature_CompilationUnit = (1 << 0)` (scope `__anon043c09c50103`)
- L9 _enumerator_ `SYMS_UnitFeature_Types = (1 << 1)` (scope `__anon043c09c50103`)
- L10 _enumerator_ `SYMS_UnitFeature_StaticVariables = (1 << 2)` (scope `__anon043c09c50103`)
- L11 _enumerator_ `SYMS_UnitFeature_ExternVariables = (1 << 3)` (scope `__anon043c09c50103`)
- L12 _enumerator_ `SYMS_UnitFeature_Functions = (1 << 4)` (scope `__anon043c09c50103`)
- L13 _enumerator_ `SYMS_UnitFeature_FunctionStubs = (1 << 5)` (scope `__anon043c09c50103`)
- L26 _typedef_ `} SYMS_SymbolKind;`
- L80 _typedef_ `} SYMS_TypeKind;`
- L81 _typedef_ `typedef SYMS_U32 SYMS_TypeModifiers;`
- L83 _enumerator_ `SYMS_TypeModifier_Const = (1 << 0)` (scope `__anon043c09c50203`)
- L84 _enumerator_ `SYMS_TypeModifier_Packed = (1 << 1)` (scope `__anon043c09c50203`)
- L85 _enumerator_ `SYMS_TypeModifier_Restrict = (1 << 2)` (scope `__anon043c09c50203`)
- L86 _enumerator_ `SYMS_TypeModifier_Shared = (1 << 3)` (scope `__anon043c09c50203`)
- L87 _enumerator_ `SYMS_TypeModifier_Volatile = (1 << 4)` (scope `__anon043c09c50203`)
- L88 _enumerator_ `SYMS_TypeModifier_Char = (1 << 5)` (scope `__anon043c09c50203`)
- L89 _enumerator_ `SYMS_TypeModifier_Reference = (1 << 6)` (scope `__anon043c09c50203`)
- L90 _enumerator_ `SYMS_TypeModifier_RValueReference = (1 << 7)` (scope `__anon043c09c50203`)
- L98 _typedef_ `} SYMS_MemVisibility;`
- L102 _prototype_ `SYMS_U32 syms_bit_size_from_type_kind(SYMS_TypeKind v);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_dwarf.h` (Other)


#### enum `SYMS_DwMode`  
`typedef enum SYMS_DwMode`  
_L6-11_
- L7 _public enumerator_ `SYMS_DwMode_Null`
- L8 _public enumerator_ `SYMS_DwMode_32Bit`
- L9 _public enumerator_ `SYMS_DwMode_64Bit`
- L10 _public enumerator_ `SYMS_DwMode_COUNT = 3`

#### enum `SYMS_DwVersion`  
`typedef enum SYMS_DwVersion`  
_L12-21_
- L13 _public enumerator_ `SYMS_DwVersion_Null`
- L14 _public enumerator_ `SYMS_DwVersion_V1`
- L15 _public enumerator_ `SYMS_DwVersion_V2`
- L16 _public enumerator_ `SYMS_DwVersion_V3`
- L17 _public enumerator_ `SYMS_DwVersion_V4`
- L18 _public enumerator_ `SYMS_DwVersion_V5`
- L19 _public enumerator_ `SYMS_DwVersion_LastVersion = SYMS_DwVersion_V5`
- L20 _public enumerator_ `SYMS_DwVersion_COUNT = 7`

#### enum `SYMS_DwSectionKind`  
`typedef enum SYMS_DwSectionKind`  
_L22-42_
- L23 _public enumerator_ `SYMS_DwSectionKind_Null`
- L24 _public enumerator_ `SYMS_DwSectionKind_Abbrev`
- L25 _public enumerator_ `SYMS_DwSectionKind_ARanges`
- L26 _public enumerator_ `SYMS_DwSectionKind_Frame`
- L27 _public enumerator_ `SYMS_DwSectionKind_Info`
- L28 _public enumerator_ `SYMS_DwSectionKind_Line`
- L29 _public enumerator_ `SYMS_DwSectionKind_Loc`
- L30 _public enumerator_ `SYMS_DwSectionKind_MacInfo`
- L31 _public enumerator_ `SYMS_DwSectionKind_PubNames`
- L32 _public enumerator_ `SYMS_DwSectionKind_PubTypes`
- L33 _public enumerator_ `SYMS_DwSectionKind_Ranges`
- L34 _public enumerator_ `SYMS_DwSectionKind_Str`
- L35 _public enumerator_ `SYMS_DwSectionKind_Addr`
- L36 _public enumerator_ `SYMS_DwSectionKind_LocLists`
- L37 _public enumerator_ `SYMS_DwSectionKind_RngLists`
- L38 _public enumerator_ `SYMS_DwSectionKind_StrOffsets`
- L39 _public enumerator_ `SYMS_DwSectionKind_LineStr`
- L40 _public enumerator_ `SYMS_DwSectionKind_Names`
- L41 _public enumerator_ `SYMS_DwSectionKind_COUNT = 18`

#### enum `SYMS_DwLanguage`  
`typedef enum SYMS_DwLanguage`  
_L43-89_
- L44 _public enumerator_ `SYMS_DwLanguage_NULL = 0x00`
- L45 _public enumerator_ `SYMS_DwLanguage_C89 = 0x01`
- L46 _public enumerator_ `SYMS_DwLanguage_C = 0x02`
- L47 _public enumerator_ `SYMS_DwLanguage_Ada83 = 0x03`
- L48 _public enumerator_ `SYMS_DwLanguage_CPlusPlus = 0x04`
- L49 _public enumerator_ `SYMS_DwLanguage_Cobol74 = 0x05`
- L50 _public enumerator_ `SYMS_DwLanguage_Cobol85 = 0x06`
- L51 _public enumerator_ `SYMS_DwLanguage_Fortran77 = 0x07`
- L52 _public enumerator_ `SYMS_DwLanguage_Fortran90 = 0x08`
- L53 _public enumerator_ `SYMS_DwLanguage_Pascal83 = 0x09`
- L54 _public enumerator_ `SYMS_DwLanguage_Modula2 = 0x0A`
- L55 _public enumerator_ `SYMS_DwLanguage_Java = 0x0B`
- L56 _public enumerator_ `SYMS_DwLanguage_C99 = 0x0C`
- L57 _public enumerator_ `SYMS_DwLanguage_Ada95 = 0x0D`
- L58 _public enumerator_ `SYMS_DwLanguage_Fortran95 = 0x0E`
- L59 _public enumerator_ `SYMS_DwLanguage_PLI = 0x0F`
- L60 _public enumerator_ `SYMS_DwLanguage_ObjectiveC = 0x10`
- L61 _public enumerator_ `SYMS_DwLanguage_ObjectiveCPlusPlus = 0x11`
- L62 _public enumerator_ `SYMS_DwLanguage_UPC = 0x12`
- L63 _public enumerator_ `SYMS_DwLanguage_D = 0x13`
- L64 _public enumerator_ `SYMS_DwLanguage_Python = 0x14`
- L65 _public enumerator_ `SYMS_DwLanguage_OpenCL = 0x15`
- L66 _public enumerator_ `SYMS_DwLanguage_Go = 0x16`
- L67 _public enumerator_ `SYMS_DwLanguage_Modula3 = 0x17`
- L68 _public enumerator_ `SYMS_DwLanguage_Haskell = 0x18`
- L69 _public enumerator_ `SYMS_DwLanguage_CPlusPlus03 = 0x19`
- L70 _public enumerator_ `SYMS_DwLanguage_CPlusPlus11 = 0x1a`
- L71 _public enumerator_ `SYMS_DwLanguage_OCaml = 0x1b`
- L72 _public enumerator_ `SYMS_DwLanguage_Rust = 0x1c`
- L73 _public enumerator_ `SYMS_DwLanguage_C11 = 0x1d`
- L74 _public enumerator_ `SYMS_DwLanguage_Swift = 0x1e`
- L75 _public enumerator_ `SYMS_DwLanguage_Julia = 0x1f`
- L76 _public enumerator_ `SYMS_DwLanguage_Dylan = 0x20`
- L77 _public enumerator_ `SYMS_DwLanguage_CPlusPlus14 = 0x21`
- L78 _public enumerator_ `SYMS_DwLanguage_Fortran03 = 0x22`
- L79 _public enumerator_ `SYMS_DwLanguage_Fortran08 = 0x23`
- L80 _public enumerator_ `SYMS_DwLanguage_RenderScript = 0x24`
- L81 _public enumerator_ `SYMS_DwLanguage_BLISS = 0x25`
- L82 _public enumerator_ `SYMS_DwLanguage_MIPS_ASSEMBLER = 0x8001`
- L83 _public enumerator_ `SYMS_DwLanguage_GOOGLE_RENDER_SCRIPT = 0x8E57`
- L84 _public enumerator_ `SYMS_DwLanguage_SUN_ASSEMBLER = 0x9001`
- L85 _public enumerator_ `SYMS_DwLanguage_BORLAND_DELPHI = 0xB000`
- L86 _public enumerator_ `SYMS_DwLanguage_LO_USER = 0x8000`
- L87 _public enumerator_ `SYMS_DwLanguage_HI_USER = 0xffff`
- L88 _public enumerator_ `SYMS_DwLanguage_COUNT = 44`

#### enum `SYMS_DwStdOpcode`  
`typedef enum SYMS_DwStdOpcode`  
_L90-105_
- L91 _public enumerator_ `SYMS_DwStdOpcode_EXTENDED_OPCODE = 0x00`
- L92 _public enumerator_ `SYMS_DwStdOpcode_COPY = 0x01`
- L93 _public enumerator_ `SYMS_DwStdOpcode_ADVANCE_PC = 0x02`
- L94 _public enumerator_ `SYMS_DwStdOpcode_ADVANCE_LINE = 0x03`
- L95 _public enumerator_ `SYMS_DwStdOpcode_SET_FILE = 0x04`
- L96 _public enumerator_ `SYMS_DwStdOpcode_SET_COLUMN = 0x05`
- L97 _public enumerator_ `SYMS_DwStdOpcode_NEGATE_STMT = 0x06`
- L98 _public enumerator_ `SYMS_DwStdOpcode_SET_BASIC_BLOCK = 0x07`
- L99 _public enumerator_ `SYMS_DwStdOpcode_CONST_ADD_PC = 0x08`
- L100 _public enumerator_ `SYMS_DwStdOpcode_FIXED_ADVANCE_PC = 0x09`
- L101 _public enumerator_ `SYMS_DwStdOpcode_SET_PROLOGUE_END = 0x0A`
- L102 _public enumerator_ `SYMS_DwStdOpcode_SET_EPILOGUE_BEGIN = 0x0B`
- L103 _public enumerator_ `SYMS_DwStdOpcode_SET_ISA = 0x0C`
- L104 _public enumerator_ `SYMS_DwStdOpcode_COUNT = 13`

#### enum `SYMS_DwExtOpcode`  
`typedef enum SYMS_DwExtOpcode`  
_L106-115_
- L107 _public enumerator_ `SYMS_DwExtOpcode_UNDEFINED = 0x00`
- L108 _public enumerator_ `SYMS_DwExtOpcode_END_SEQUENCE = 0x01`
- L109 _public enumerator_ `SYMS_DwExtOpcode_SET_ADDRESS = 0x02`
- L110 _public enumerator_ `SYMS_DwExtOpcode_DEFINE_FILE = 0x03`
- L111 _public enumerator_ `SYMS_DwExtOpcode_SET_DISCRIMINATOR = 0x04`
- L112 _public enumerator_ `SYMS_DwExtOpcode_LO_USER = 0x80`
- L113 _public enumerator_ `SYMS_DwExtOpcode_HI_USER = 0xff`
- L114 _public enumerator_ `SYMS_DwExtOpcode_COUNT = 7`

#### enum `SYMS_DwNameCase`  
`typedef enum SYMS_DwNameCase`  
_L116-122_
- L117 _public enumerator_ `SYMS_DwNameCase_Sensitive = 0x00`
- L118 _public enumerator_ `SYMS_DwNameCase_Upper = 0x01`
- L119 _public enumerator_ `SYMS_DwNameCase_Lower = 0x02`
- L120 _public enumerator_ `SYMS_DwNameCase_Insensitive = 0x03`
- L121 _public enumerator_ `SYMS_DwNameCase_COUNT = 4`

#### enum `SYMS_DwTagKind`  
`typedef enum SYMS_DwTagKind`  
_L123-198_
- L124 _public enumerator_ `SYMS_DwTagKind_NULL`
- L125 _public enumerator_ `SYMS_DwTagKind_ARRAY_TYPE = 0x01`
- L126 _public enumerator_ `SYMS_DwTagKind_CLASS_TYPE = 0x02`
- L127 _public enumerator_ `SYMS_DwTagKind_ENTRY_POINT = 0x03`
- L128 _public enumerator_ `SYMS_DwTagKind_ENUMERATION_TYPE = 0x04`
- L129 _public enumerator_ `SYMS_DwTagKind_FORMAL_PARAMETER = 0x05`
- L130 _public enumerator_ `SYMS_DwTagKind_IMPORTED_DECLARATION = 0x08`
- L131 _public enumerator_ `SYMS_DwTagKind_LABEL = 0x0a`
- L132 _public enumerator_ `SYMS_DwTagKind_LEXICAL_BLOCK = 0x0b`
- L133 _public enumerator_ `SYMS_DwTagKind_MEMBER = 0x0d`
- L134 _public enumerator_ `SYMS_DwTagKind_POINTER_TYPE = 0x0f`
- L135 _public enumerator_ `SYMS_DwTagKind_REFERENCE_TYPE = 0x10`
- L136 _public enumerator_ `SYMS_DwTagKind_COMPILE_UNIT = 0x11`
- L137 _public enumerator_ `SYMS_DwTagKind_STRING_TYPE = 0x12`
- L138 _public enumerator_ `SYMS_DwTagKind_STRUCTURE_TYPE = 0x13`
- L139 _public enumerator_ `SYMS_DwTagKind_SUBROUTINE_TYPE = 0x15`
- L140 _public enumerator_ `SYMS_DwTagKind_TYPEDEF = 0x16`
- L141 _public enumerator_ `SYMS_DwTagKind_UNION_TYPE = 0x17`
- L142 _public enumerator_ `SYMS_DwTagKind_UNSPECIFIED_PARAMETERS = 0x18`
- L143 _public enumerator_ `SYMS_DwTagKind_VARIANT = 0x19`
- L144 _public enumerator_ `SYMS_DwTagKind_COMMON_BLOCK = 0x1a`
- L145 _public enumerator_ `SYMS_DwTagKind_COMMON_INCLUSION = 0x1b`
- L146 _public enumerator_ `SYMS_DwTagKind_INHERITANCE = 0x1c`
- L147 _public enumerator_ `SYMS_DwTagKind_INLINED_SUBROUTINE = 0x1d`
- L148 _public enumerator_ `SYMS_DwTagKind_MODULE = 0x1e`
- L149 _public enumerator_ `SYMS_DwTagKind_PTR_TO_MEMBER_TYPE = 0x1f`
- L150 _public enumerator_ `SYMS_DwTagKind_SET_TYPE = 0x20`
- L151 _public enumerator_ `SYMS_DwTagKind_SUBRANGE_TYPE = 0x21`
- L152 _public enumerator_ `SYMS_DwTagKind_WITH_STMT = 0x22`
- L153 _public enumerator_ `SYMS_DwTagKind_ACCESS_DECLARATION = 0x23`
- L154 _public enumerator_ `SYMS_DwTagKind_BASE_TYPE = 0x24`
- L155 _public enumerator_ `SYMS_DwTagKind_CATCH_BLOCK = 0x25`
- L156 _public enumerator_ `SYMS_DwTagKind_CONST_TYPE = 0x26`
- L157 _public enumerator_ `SYMS_DwTagKind_CONSTANT = 0x27`
- L158 _public enumerator_ `SYMS_DwTagKind_ENUMERATOR = 0x28`
- L159 _public enumerator_ `SYMS_DwTagKind_FILE_TYPE = 0x29`
- L160 _public enumerator_ `SYMS_DwTagKind_FRIEND = 0x2a`
- L161 _public enumerator_ `SYMS_DwTagKind_NAMELIST = 0x2b`
- L162 _public enumerator_ `SYMS_DwTagKind_NAMELIST_ITEM = 0x2c`
- L163 _public enumerator_ `SYMS_DwTagKind_PACKED_TYPE = 0x2d`
- L164 _public enumerator_ `SYMS_DwTagKind_SUBPROGRAM = 0x2e`
- L165 _public enumerator_ `SYMS_DwTagKind_TEMPLATE_TYPE_PARAMETER = 0x2f`
- L166 _public enumerator_ `SYMS_DwTagKind_TEMPLATE_VALUE_PARAMETER = 0x30`
- L167 _public enumerator_ `SYMS_DwTagKind_THROWN_TYPE = 0x31`
- L168 _public enumerator_ `SYMS_DwTagKind_TRY_BLOCK = 0x32`
- L169 _public enumerator_ `SYMS_DwTagKind_VARIANT_PART = 0x33`
- L170 _public enumerator_ `SYMS_DwTagKind_VARIABLE = 0x34`
- L171 _public enumerator_ `SYMS_DwTagKind_VOLATILE_TYPE = 0x35`
- L172 _public enumerator_ `SYMS_DwTagKind_DWARF_PROCEDURE = 0x36`
- L173 _public enumerator_ `SYMS_DwTagKind_RESTRICT_TYPE = 0x37`
- L174 _public enumerator_ `SYMS_DwTagKind_INTERFACE_TYPE = 0x38`
- L175 _public enumerator_ `SYMS_DwTagKind_NAMESPACE = 0x39`
- L176 _public enumerator_ `SYMS_DwTagKind_IMPORTED_MODULE = 0x3a`
- L177 _public enumerator_ `SYMS_DwTagKind_UNSPECIFIED_TYPE = 0x3b`
- L178 _public enumerator_ `SYMS_DwTagKind_PARTIAL_UNIT = 0x3c`
- L179 _public enumerator_ `SYMS_DwTagKind_IMPORTED_UNIT = 0x3d`
- L180 _public enumerator_ `SYMS_DwTagKind_CONDITION = 0x3f`
- L181 _public enumerator_ `SYMS_DwTagKind_SHARED_TYPE = 0x40`
- L182 _public enumerator_ `SYMS_DwTagKind_TYPE_UNIT = 0x41`
- L183 _public enumerator_ `SYMS_DwTagKind_RVALUE_REFERENCE_TYPE = 0x42`
- L184 _public enumerator_ `SYMS_DwTagKind_TEMPLATE_ALIAS = 0x43`
- L185 _public enumerator_ `SYMS_DwTagKind_COARRAY_TYPE = 0x44`
- L186 _public enumerator_ `SYMS_DwTagKind_GENERIC_SUBRANGE = 0x45`
- L187 _public enumerator_ `SYMS_DwTagKind_DYNAMIC_TYPE = 0x46`
- L188 _public enumerator_ `SYMS_DwTagKind_ATOMIC_TYPE = 0x47`
- L189 _public enumerator_ `SYMS_DwTagKind_CALL_SITE = 0x48`
- L190 _public enumerator_ `SYMS_DwTagKind_CALL_SITE_PARAMETER = 0x49`
- L191 _public enumerator_ `SYMS_DwTagKind_SKELETON_UNIT = 0x4A`
- L192 _public enumerator_ `SYMS_DwTagKind_IMMUTABLE_TYPE = 0x4B`
- L193 _public enumerator_ `SYMS_DwTagKind_GNU_CALL_SITE = 0x4109`
- L194 _public enumerator_ `SYMS_DwTagKind_GNU_CALL_SITE_PARAMETER = 0x410a`
- L195 _public enumerator_ `SYMS_DwTagKind_LO_USER = 0x4080`
- L196 _public enumerator_ `SYMS_DwTagKind_HI_USER = 0xffff`
- L197 _public enumerator_ `SYMS_DwTagKind_COUNT = 73`

#### enum `(anonymous)`  
`enum`  
_L200-217_

#### enum `SYMS_DwFormKind`  
`typedef enum SYMS_DwFormKind`  
_L218-264_
- L219 _public enumerator_ `SYMS_DwFormKind_ADDR = 0x01`
- L220 _public enumerator_ `SYMS_DwFormKind_BLOCK2 = 0x03`
- L221 _public enumerator_ `SYMS_DwFormKind_BLOCK4 = 0x04`
- L222 _public enumerator_ `SYMS_DwFormKind_DATA2 = 0x05`
- L223 _public enumerator_ `SYMS_DwFormKind_DATA4 = 0x06`
- L224 _public enumerator_ `SYMS_DwFormKind_DATA8 = 0x07`
- L225 _public enumerator_ `SYMS_DwFormKind_STRING = 0x08`
- L226 _public enumerator_ `SYMS_DwFormKind_BLOCK = 0x09`
- L227 _public enumerator_ `SYMS_DwFormKind_BLOCK1 = 0x0a`
- L228 _public enumerator_ `SYMS_DwFormKind_DATA1 = 0x0b`
- L229 _public enumerator_ `SYMS_DwFormKind_FLAG = 0x0c`
- L230 _public enumerator_ `SYMS_DwFormKind_SDATA = 0x0d`
- L231 _public enumerator_ `SYMS_DwFormKind_STRP = 0x0e`
- L232 _public enumerator_ `SYMS_DwFormKind_UDATA = 0x0f`
- L233 _public enumerator_ `SYMS_DwFormKind_REF_ADDR = 0x10`
- L234 _public enumerator_ `SYMS_DwFormKind_REF1 = 0x11`
- L235 _public enumerator_ `SYMS_DwFormKind_REF2 = 0x12`
- L236 _public enumerator_ `SYMS_DwFormKind_REF4 = 0x13`
- L237 _public enumerator_ `SYMS_DwFormKind_REF8 = 0x14`
- L238 _public enumerator_ `SYMS_DwFormKind_REF_UDATA = 0x15`
- L239 _public enumerator_ `SYMS_DwFormKind_INDIRECT = 0x16`
- L240 _public enumerator_ `SYMS_DwFormKind_SEC_OFFSET = 0x17`
- L241 _public enumerator_ `SYMS_DwFormKind_EXPRLOC = 0x18`
- L242 _public enumerator_ `SYMS_DwFormKind_FLAG_PRESENT = 0x19`
- L243 _public enumerator_ `SYMS_DwFormKind_REF_SIG8 = 0x20`
- L244 _public enumerator_ `SYMS_DwFormKind_STRX = 0x1a`
- L245 _public enumerator_ `SYMS_DwFormKind_ADDRX = 0x1b`
- L246 _public enumerator_ `SYMS_DwFormKind_REF_SUP4 = 0x1c`
- L247 _public enumerator_ `SYMS_DwFormKind_STRP_SUP = 0x1d`
- L248 _public enumerator_ `SYMS_DwFormKind_DATA16 = 0x1e`
- L249 _public enumerator_ `SYMS_DwFormKind_LINE_STRP = 0x1f`
- L250 _public enumerator_ `SYMS_DwFormKind_IMPLICIT_CONST = 0x21`
- L251 _public enumerator_ `SYMS_DwFormKind_LOCLISTX = 0x22`
- L252 _public enumerator_ `SYMS_DwFormKind_RNGLISTX = 0x23`
- L253 _public enumerator_ `SYMS_DwFormKind_REF_SUP8 = 0x24`
- L254 _public enumerator_ `SYMS_DwFormKind_STRX1 = 0x25`
- L255 _public enumerator_ `SYMS_DwFormKind_STRX2 = 0x26`
- L256 _public enumerator_ `SYMS_DwFormKind_STRX3 = 0x27`
- L257 _public enumerator_ `SYMS_DwFormKind_STRX4 = 0x28`
- L258 _public enumerator_ `SYMS_DwFormKind_ADDRX1 = 0x29`
- L259 _public enumerator_ `SYMS_DwFormKind_ADDRX2 = 0x2a`
- L260 _public enumerator_ `SYMS_DwFormKind_ADDRX3 = 0x2b`
- L261 _public enumerator_ `SYMS_DwFormKind_ADDRX4 = 0x2c`
- L262 _public enumerator_ `SYMS_DwFormKind_INVALID`
- L263 _public enumerator_ `SYMS_DwFormKind_COUNT = 44`

#### enum `SYMS_DwAttribKind`  
`typedef enum SYMS_DwAttribKind`  
_L265-466_
- L266 _public enumerator_ `SYMS_DwAttribKind_SIBLING = 0x01`
- L267 _public enumerator_ `SYMS_DwAttribKind_LOCATION = 0x02`
- L268 _public enumerator_ `SYMS_DwAttribKind_NAME = 0x03`
- L269 _public enumerator_ `SYMS_DwAttribKind_ORDERING = 0x09`
- L270 _public enumerator_ `SYMS_DwAttribKind_BYTE_SIZE = 0x0B`
- L271 _public enumerator_ `SYMS_DwAttribKind_BIT_OFFSET = 0x0C`
- L272 _public enumerator_ `SYMS_DwAttribKind_BIT_SIZE = 0x0D`
- L273 _public enumerator_ `SYMS_DwAttribKind_STMT_LIST = 0x10`
- L274 _public enumerator_ `SYMS_DwAttribKind_LOW_PC = 0x11`
- L275 _public enumerator_ `SYMS_DwAttribKind_HIGH_PC = 0x12`
- L276 _public enumerator_ `SYMS_DwAttribKind_LANGUAGE = 0x13`
- L277 _public enumerator_ `SYMS_DwAttribKind_DISCR = 0x15`
- L278 _public enumerator_ `SYMS_DwAttribKind_DISCR_VALUE = 0x16`
- L279 _public enumerator_ `SYMS_DwAttribKind_VISIBILITY = 0x17`
- L280 _public enumerator_ `SYMS_DwAttribKind_IMPORT = 0x18`
- L281 _public enumerator_ `SYMS_DwAttribKind_STRING_LENGTH = 0x19`
- L282 _public enumerator_ `SYMS_DwAttribKind_COMMON_REFERENCE = 0x1a`
- L283 _public enumerator_ `SYMS_DwAttribKind_COMP_DIR = 0x1b`
- L284 _public enumerator_ `SYMS_DwAttribKind_CONST_VALUE = 0x1c`
- L285 _public enumerator_ `SYMS_DwAttribKind_CONTAINING_TYPE = 0x1d`
- L286 _public enumerator_ `SYMS_DwAttribKind_DEFAULT_VALUE = 0x1e`
- L287 _public enumerator_ `SYMS_DwAttribKind_INLINE = 0x20`
- L288 _public enumerator_ `SYMS_DwAttribKind_IS_OPTIONAL = 0x21`
- L289 _public enumerator_ `SYMS_DwAttribKind_LOWER_BOUND = 0x22`
- L290 _public enumerator_ `SYMS_DwAttribKind_PRODUCER = 0x25`
- L291 _public enumerator_ `SYMS_DwAttribKind_PROTOTYPED = 0x27`
- L292 _public enumerator_ `SYMS_DwAttribKind_RETURN_ADDR = 0x2a`
- L293 _public enumerator_ `SYMS_DwAttribKind_START_SCOPE = 0x2c`
- L294 _public enumerator_ `SYMS_DwAttribKind_BIT_STRIDE = 0x2e`
- L295 _public enumerator_ `SYMS_DwAttribKind_UPPER_BOUND = 0x2f`
- L296 _public enumerator_ `SYMS_DwAttribKind_ABSTRACT_ORIGIN = 0x31`
- L297 _public enumerator_ `SYMS_DwAttribKind_ACCESSIBILITY = 0x32`
- L298 _public enumerator_ `SYMS_DwAttribKind_ADDRESS_CLASS = 0x33`
- L299 _public enumerator_ `SYMS_DwAttribKind_ARTIFICIAL = 0x34`
- L300 _public enumerator_ `SYMS_DwAttribKind_BASE_TYPES = 0x35`
- L301 _public enumerator_ `SYMS_DwAttribKind_CALLING_CONVENTION = 0x36`
- L302 _public enumerator_ `SYMS_DwAttribKind_ARR_COUNT = 0x37`
- L303 _public enumerator_ `SYMS_DwAttribKind_DATA_MEMBER_LOCATION = 0x38`
- L304 _public enumerator_ `SYMS_DwAttribKind_DECL_COLUMN = 0x39`
- L305 _public enumerator_ `SYMS_DwAttribKind_DECL_FILE = 0x3a`
- L306 _public enumerator_ `SYMS_DwAttribKind_DECL_LINE = 0x3b`
- L307 _public enumerator_ `SYMS_DwAttribKind_DECLARATION = 0x3c`
- L308 _public enumerator_ `SYMS_DwAttribKind_DISCR_LIST = 0x3d`
- L309 _public enumerator_ `SYMS_DwAttribKind_ENCODING = 0x3e`
- L310 _public enumerator_ `SYMS_DwAttribKind_EXTERNAL = 0x3f`
- L311 _public enumerator_ `SYMS_DwAttribKind_FRAME_BASE = 0x40`
- L312 _public enumerator_ `SYMS_DwAttribKind_FRIEND = 0x41`
- L313 _public enumerator_ `SYMS_DwAttribKind_IDENTIFIER_CASE = 0x42`
- L314 _public enumerator_ `SYMS_DwAttribKind_MACRO_INFO = 0x43`
- L315 _public enumerator_ `SYMS_DwAttribKind_NAMELIST_ITEM = 0x44`
- L316 _public enumerator_ `SYMS_DwAttribKind_PRIORITY = 0x45`
- L317 _public enumerator_ `SYMS_DwAttribKind_SEGMENT = 0x46`
- L318 _public enumerator_ `SYMS_DwAttribKind_SPECIFICATION = 0x47`
- L319 _public enumerator_ `SYMS_DwAttribKind_STATIC_LINK = 0x48`
- L320 _public enumerator_ `SYMS_DwAttribKind_TYPE = 0x49`
- L321 _public enumerator_ `SYMS_DwAttribKind_USE_LOCATION = 0x4a`
- L322 _public enumerator_ `SYMS_DwAttribKind_VARIABLE_PARAMETER = 0x4b`
- L323 _public enumerator_ `SYMS_DwAttribKind_VIRTUALITY = 0x4c`
- L324 _public enumerator_ `SYMS_DwAttribKind_VTABLE_ELEM_LOCATION = 0x4d`
- L325 _public enumerator_ `SYMS_DwAttribKind_ALLOCATED = 0x4e`
- L326 _public enumerator_ `SYMS_DwAttribKind_ASSOCIATED = 0x4f`
- L327 _public enumerator_ `SYMS_DwAttribKind_DATA_LOCATION = 0x50`
- L328 _public enumerator_ `SYMS_DwAttribKind_BYTE_STRIDE = 0x51`
- L329 _public enumerator_ `SYMS_DwAttribKind_ENTRY_PC = 0x52`
- L330 _public enumerator_ `SYMS_DwAttribKind_USE_UTF8 = 0x53`
- L331 _public enumerator_ `SYMS_DwAttribKind_EXTENSION = 0x54`
- L332 _public enumerator_ `SYMS_DwAttribKind_RANGES = 0x55`
- L333 _public enumerator_ `SYMS_DwAttribKind_TRAMPOLINE = 0x56`
- L334 _public enumerator_ `SYMS_DwAttribKind_CALL_COLUMN = 0x57`
- L335 _public enumerator_ `SYMS_DwAttribKind_CALL_FILE = 0x58`
- L336 _public enumerator_ `SYMS_DwAttribKind_CALL_LINE = 0x59`
- L337 _public enumerator_ `SYMS_DwAttribKind_DESCRIPTION = 0x5a`
- L338 _public enumerator_ `SYMS_DwAttribKind_BINARY_SCALE = 0x5b`
- L339 _public enumerator_ `SYMS_DwAttribKind_DECIMAL_SCALE = 0x5c`
- L340 _public enumerator_ `SYMS_DwAttribKind_SMALL = 0x5d`
- L341 _public enumerator_ `SYMS_DwAttribKind_DECIMAL_SIGN = 0x5e`
- L342 _public enumerator_ `SYMS_DwAttribKind_DIGIT_COUNT = 0x5f`
- L343 _public enumerator_ `SYMS_DwAttribKind_PICTURE_STRING = 0x60`
- L344 _public enumerator_ `SYMS_DwAttribKind_MUTABLE = 0x61`
- L345 _public enumerator_ `SYMS_DwAttribKind_THREADS_SCALED = 0x62`
- L346 _public enumerator_ `SYMS_DwAttribKind_EXPLICIT = 0x63`
- L347 _public enumerator_ `SYMS_DwAttribKind_OBJECT_POINTER = 0x64`
- L348 _public enumerator_ `SYMS_DwAttribKind_ENDIANITY = 0x65`
- L349 _public enumerator_ `SYMS_DwAttribKind_ELEMENTAL = 0x66`
- L350 _public enumerator_ `SYMS_DwAttribKind_PURE = 0x67`
- L351 _public enumerator_ `SYMS_DwAttribKind_RECURSIVE = 0x68`
- L352 _public enumerator_ `SYMS_DwAttribKind_SIGNATURE = 0x69`
- L353 _public enumerator_ `SYMS_DwAttribKind_MAIN_SUBPROGRAM = 0x6a`
- L354 _public enumerator_ `SYMS_DwAttribKind_DATA_BIT_OFFSET = 0x6b`
- L355 _public enumerator_ `SYMS_DwAttribKind_CONST_EXPR = 0x6c`
- L356 _public enumerator_ `SYMS_DwAttribKind_ENUM_CLASS = 0x6d`
- L357 _public enumerator_ `SYMS_DwAttribKind_LINKAGE_NAME = 0x6e`
- L358 _public enumerator_ `SYMS_DwAttribKind_STRING_LENGTH_BIT_SIZE = 0x6f`
- L359 _public enumerator_ `SYMS_DwAttribKind_STRING_LENGTH_BYTE_SIZE = 0x70`
- L360 _public enumerator_ `SYMS_DwAttribKind_RANK = 0x71`
- L361 _public enumerator_ `SYMS_DwAttribKind_STR_OFFSETS_BASE = 0x72`
- L362 _public enumerator_ `SYMS_DwAttribKind_ADDR_BASE = 0x73`
- L363 _public enumerator_ `SYMS_DwAttribKind_RNGLISTS_BASE = 0x74`
- L364 _public enumerator_ `SYMS_DwAttribKind_DWO_NAME = 0x76`
- L365 _public enumerator_ `SYMS_DwAttribKind_REFERENCE = 0x77`
- L366 _public enumerator_ `SYMS_DwAttribKind_RVALUE_REFERENCE = 0x78`
- L367 _public enumerator_ `SYMS_DwAttribKind_MACROS = 0x79`
- L368 _public enumerator_ `SYMS_DwAttribKind_CALL_ALL_CALLS = 0x7a`
- L369 _public enumerator_ `SYMS_DwAttribKind_CALL_ALL_SOURCE_CALLS = 0x7b`
- L370 _public enumerator_ `SYMS_DwAttribKind_CALL_ALL_TAIL_CALLS = 0x7c`
- L371 _public enumerator_ `SYMS_DwAttribKind_CALL_RETURN_PC = 0x7d`
- L372 _public enumerator_ `SYMS_DwAttribKind_CALL_VALUE = 0x7e` — NOTE(nick): According to spec this is attribute has EXPRLOC class, but in newton_ps5.elf these are defined as REFERENCE
- L373 _public enumerator_ `SYMS_DwAttribKind_CALL_ORIGIN = 0x7f`
- L374 _public enumerator_ `SYMS_DwAttribKind_CALL_PARAMETER = 0x80`
- L375 _public enumerator_ `SYMS_DwAttribKind_CALL_PC = 0x81`
- L376 _public enumerator_ `SYMS_DwAttribKind_CALL_TAIL_CALL = 0x82`
- L377 _public enumerator_ `SYMS_DwAttribKind_CALL_TARGET = 0x83`
- L378 _public enumerator_ `SYMS_DwAttribKind_CALL_TARGET_CLOBBERED = 0x84`
- L379 _public enumerator_ `SYMS_DwAttribKind_CALL_DATA_LOCATION = 0x85`
- L380 _public enumerator_ `SYMS_DwAttribKind_CALL_DATA_VALUE = 0x86`
- L381 _public enumerator_ `SYMS_DwAttribKind_NORETURN = 0x87`
- L382 _public enumerator_ `SYMS_DwAttribKind_ALIGNMENT = 0x88`
- L383 _public enumerator_ `SYMS_DwAttribKind_EXPORT_SYMBOLS = 0x89`
- L384 _public enumerator_ `SYMS_DwAttribKind_DELETED = 0x8a`
- L385 _public enumerator_ `SYMS_DwAttribKind_DEFAULTED = 0x8b`
- L386 _public enumerator_ `SYMS_DwAttribKind_LOCLISTS_BASE = 0x8c`
- L387 _public enumerator_ `SYMS_DwAttribKind_GNU_VECTOR = 0x2107`
- L388 _public enumerator_ `SYMS_DwAttribKind_GNU_GUARDED_BY = 0x2108`
- L389 _public enumerator_ `SYMS_DwAttribKind_GNU_PT_GUARDED_BY = 0x2109`
- L390 _public enumerator_ `SYMS_DwAttribKind_GNU_GUARDED = 0x210a`
- L391 _public enumerator_ `SYMS_DwAttribKind_GNU_PT_GUARDED = 0x210b`
- L392 _public enumerator_ `SYMS_DwAttribKind_GNU_LOCKS_EXCLUDED = 0x210c`
- L393 _public enumerator_ `SYMS_DwAttribKind_GNU_EXCLUSIVE_LOCKS_REQUIRED = 0x210d`
- L394 _public enumerator_ `SYMS_DwAttribKind_GNU_SHARED_LOCKS_REQUIRED = 0x210e`
- L395 _public enumerator_ `SYMS_DwAttribKind_GNU_ODR_SIGNATURE = 0x210f`
- L396 _public enumerator_ `SYMS_DwAttribKind_GNU_TEMPLATE_NAME = 0x2110`
- L397 _public enumerator_ `SYMS_DwAttribKind_GNU_CALL_SITE_VALUE = 0x2111`
- L398 _public enumerator_ `SYMS_DwAttribKind_GNU_CALL_SITE_DATA_VALUE = 0x2112`
- L399 _public enumerator_ `SYMS_DwAttribKind_GNU_CALL_SITE_TARGET = 0x2113`
- L400 _public enumerator_ `SYMS_DwAttribKind_GNU_CALL_SITE_TARGET_CLOBBERED = 0x2114`
- L401 _public enumerator_ `SYMS_DwAttribKind_GNU_TAIL_CALL = 0x2115`
- L402 _public enumerator_ `SYMS_DwAttribKind_GNU_ALL_TAIL_CALL_SITES = 0x2116`
- L403 _public enumerator_ `SYMS_DwAttribKind_GNU_ALL_CALL_SITES = 0x2117`
- L404 _public enumerator_ `SYMS_DwAttribKind_GNU_ALL_SOURCE_CALL_SITES = 0x2118`
- L405 _public enumerator_ `SYMS_DwAttribKind_GNU_MACROS = 0x2119`
- L406 _public enumerator_ `SYMS_DwAttribKind_GNU_DELETED = 0x211a`
- L407 _public enumerator_ `SYMS_DwAttribKind_GNU_DWO_NAME = 0x2130`
- L408 _public enumerator_ `SYMS_DwAttribKind_GNU_DWO_ID = 0x2131`
- L409 _public enumerator_ `SYMS_DwAttribKind_GNU_RANGES_BASE = 0x2132`
- L410 _public enumerator_ `SYMS_DwAttribKind_GNU_ADDR_BASE = 0x2133`
- L411 _public enumerator_ `SYMS_DwAttribKind_GNU_PUBNAMES = 0x2134`
- L412 _public enumerator_ `SYMS_DwAttribKind_GNU_PUBTYPES = 0x2135`
- L413 _public enumerator_ `SYMS_DwAttribKind_GNU_DISCRIMINATOR = 0x2136`
- L414 _public enumerator_ `SYMS_DwAttribKind_GNU_LOCVIEWS = 0x2137`
- L415 _public enumerator_ `SYMS_DwAttribKind_GNU_ENTRY_VIEW = 0x2138`
- L416 _public enumerator_ `SYMS_DwAttribKind_VMS_RTNBEG_PD_ADDRESS = 0x2201`
- L417 _public enumerator_ `SYMS_DwAttribKind_USE_GNAT_DESCRIPTIVE_TYPE = 0x2301`
- L418 _public enumerator_ `SYMS_DwAttribKind_GNAT_DESCRIPTIVE_TYPE = 0x2302`
- L419 _public enumerator_ `SYMS_DwAttribKind_GNU_NUMERATOR = 0x2303`
- L420 _public enumerator_ `SYMS_DwAttribKind_GNU_DENOMINATOR = 0x2304`
- L421 _public enumerator_ `SYMS_DwAttribKind_GNU_BIAS = 0x2305`
- L422 _public enumerator_ `SYMS_DwAttribKind_UPC_THREADS_SCALED = 0x3210`
- L423 _public enumerator_ `SYMS_DwAttribKind_PGI_LBASE = 0x3a00`
- L424 _public enumerator_ `SYMS_DwAttribKind_PGI_SOFFSET = 0x3a01`
- L425 _public enumerator_ `SYMS_DwAttribKind_PGI_LSTRIDE = 0x3a02`
- L426 _public enumerator_ `SYMS_DwAttribKind_LLVM_INCLUDE_PATH = 0x3e00`
- L427 _public enumerator_ `SYMS_DwAttribKind_LLVM_CONFIG_MACROS = 0x3e01`
- L428 _public enumerator_ `SYMS_DwAttribKind_LLVM_SYSROOT = 0x3e02`
- L429 _public enumerator_ `SYMS_DwAttribKind_LLVM_API_NOTES = 0x3e07`
- L430 _public enumerator_ `SYMS_DwAttribKind_LLVM_TAG_OFFSET = 0x3e03`
- L431 _public enumerator_ `SYMS_DwAttribKind_APPLE_OPTIMIZED = 0x3fe1`
- L432 _public enumerator_ `SYMS_DwAttribKind_APPLE_FLAGS = 0x3fe2`
- L433 _public enumerator_ `SYMS_DwAttribKind_APPLE_ISA = 0x3fe3`
- L434 _public enumerator_ `SYMS_DwAttribKind_APPLE_BLOCK = 0x3fe4`
- L435 _public enumerator_ `SYMS_DwAttribKind_APPLE_MAJOR_RUNTIME_VERS = 0x3fe5`
- L436 _public enumerator_ `SYMS_DwAttribKind_APPLE_RUNTIME_CLASS = 0x3fe6`
- L437 _public enumerator_ `SYMS_DwAttribKind_APPLE_OMIT_FRAME_PTR = 0x3fe7`
- L438 _public enumerator_ `SYMS_DwAttribKind_APPLE_PROPERTY_NAME = 0x3fe8`
- L439 _public enumerator_ `SYMS_DwAttribKind_APPLE_PROPERTY_GETTER = 0x3fe9`
- L440 _public enumerator_ `SYMS_DwAttribKind_APPLE_PROPERTY_SETTER = 0x3fea`
- L441 _public enumerator_ `SYMS_DwAttribKind_APPLE_PROPERTY_ATTRIBUTE = 0x3feb`
- L442 _public enumerator_ `SYMS_DwAttribKind_APPLE_OBJC_COMPLETE_TYPE = 0x3fec`
- L443 _public enumerator_ `SYMS_DwAttribKind_APPLE_PROPERTY = 0x3fed`
- L444 _public enumerator_ `SYMS_DwAttribKind_APPLE_OBJ_DIRECT = 0x3fee`
- L445 _public enumerator_ `SYMS_DwAttribKind_APPLE_SDK = 0x3fef` — llvm/BinaryFormat/Dwarf.def
- L446 _public enumerator_ `SYMS_DwAttribKind_MIPS_FDE = 0x2001`
- L447 _public enumerator_ `SYMS_DwAttribKind_MIPS_LOOP_BEGIN = 0x2002`
- L448 _public enumerator_ `SYMS_DwAttribKind_MIPS_TAIL_LOOP_BEGIN = 0x2003`
- L449 _public enumerator_ `SYMS_DwAttribKind_MIPS_EPILOG_BEGIN = 0x2004`
- L450 _public enumerator_ `SYMS_DwAttribKind_MIPS_LOOP_UNROLL_FACTOR = 0x2005`
- L451 _public enumerator_ `SYMS_DwAttribKind_MIPS_SOFTWARE_PIPELINE_DEPTH = 0x2006`
- L452 _public enumerator_ `SYMS_DwAttribKind_MIPS_LINKAGE_NAME = 0x2007`
- L453 _public enumerator_ `SYMS_DwAttribKind_MIPS_STRIDE = 0x2008`
- L454 _public enumerator_ `SYMS_DwAttribKind_MIPS_ABSTRACT_NAME = 0x2009`
- L455 _public enumerator_ `SYMS_DwAttribKind_MIPS_CLONE_ORIGIN = 0x200a`
- L456 _public enumerator_ `SYMS_DwAttribKind_MIPS_HAS_INLINES = 0x200b`
- L457 _public enumerator_ `SYMS_DwAttribKind_MIPS_STRIDE_BYTE = 0x200c`
- L458 _public enumerator_ `SYMS_DwAttribKind_MIPS_STRIDE_ELEM = 0x200d`
- L459 _public enumerator_ `SYMS_DwAttribKind_MIPS_PTR_DOPETYPE = 0x200e`
- L460 _public enumerator_ `SYMS_DwAttribKind_MIPS_ALLOCATABLE_DOPETYPE = 0x200f`
- L461 _public enumerator_ `SYMS_DwAttribKind_MIPS_ASSUMED_SHAPE_DOPETYPE = 0x2010`
- L462 _public enumerator_ `SYMS_DwAttribKind_MIPS_ASSUMED_SIZE = 0x2011`
- L463 _public enumerator_ `SYMS_DwAttribKind_LO_USER = 0x2000`
- L464 _public enumerator_ `SYMS_DwAttribKind_HI_USER = 0x3fff`
- L465 _public enumerator_ `SYMS_DwAttribKind_COUNT = 199`

#### enum `SYMS_DwAttribTypeEncoding`  
`typedef enum SYMS_DwAttribTypeEncoding`  
_L467-488_
- L468 _public enumerator_ `SYMS_DwAttribTypeEncoding_Null`
- L469 _public enumerator_ `SYMS_DwAttribTypeEncoding_ADDRESS = 0X01`
- L470 _public enumerator_ `SYMS_DwAttribTypeEncoding_BOOLEAN = 0X02`
- L471 _public enumerator_ `SYMS_DwAttribTypeEncoding_COMPLEX_FLOAT = 0X03`
- L472 _public enumerator_ `SYMS_DwAttribTypeEncoding_FLOAT = 0X04`
- L473 _public enumerator_ `SYMS_DwAttribTypeEncoding_SIGNED = 0X05`
- L474 _public enumerator_ `SYMS_DwAttribTypeEncoding_SIGNED_CHAR = 0X06`
- L475 _public enumerator_ `SYMS_DwAttribTypeEncoding_UNSIGNED = 0X07`
- L476 _public enumerator_ `SYMS_DwAttribTypeEncoding_UNSIGNED_CHAR = 0X08`
- L477 _public enumerator_ `SYMS_DwAttribTypeEncoding_IMAGINARY_FLOAT = 0X09`
- L478 _public enumerator_ `SYMS_DwAttribTypeEncoding_PACKED_DECIMAL = 0X0A`
- L479 _public enumerator_ `SYMS_DwAttribTypeEncoding_NUMERIC_STRING = 0X0B`
- L480 _public enumerator_ `SYMS_DwAttribTypeEncoding_EDITED = 0X0C`
- L481 _public enumerator_ `SYMS_DwAttribTypeEncoding_SIGNED_FIXED = 0X0D`
- L482 _public enumerator_ `SYMS_DwAttribTypeEncoding_UNSIGNED_FIXED = 0X0E`
- L483 _public enumerator_ `SYMS_DwAttribTypeEncoding_DECIMAL_FLOAT = 0X0F`
- L484 _public enumerator_ `SYMS_DwAttribTypeEncoding_UTF = 0X10`
- L485 _public enumerator_ `SYMS_DwAttribTypeEncoding_UCS = 0X11`
- L486 _public enumerator_ `SYMS_DwAttribTypeEncoding_ASCII = 0X12`
- L487 _public enumerator_ `SYMS_DwAttribTypeEncoding_COUNT = 19`

#### enum `SYMS_DwCallingConvention`  
`typedef enum SYMS_DwCallingConvention`  
_L489-496_
- L490 _public enumerator_ `SYMS_DwCallingConvention_Normal = 0x0`
- L491 _public enumerator_ `SYMS_DwCallingConvention_Program = 0x1`
- L492 _public enumerator_ `SYMS_DwCallingConvention_NoCall = 0x2`
- L493 _public enumerator_ `SYMS_DwCallingConvention_PassByValue = 0x1`
- L494 _public enumerator_ `SYMS_DwCallingConvention_PassByReference = 0x2`
- L495 _public enumerator_ `SYMS_DwCallingConvention_COUNT = 5`

#### enum `SYMS_DwAccess`  
`typedef enum SYMS_DwAccess`  
_L497-502_
- L498 _public enumerator_ `SYMS_DwAccess_Public = 0x00`
- L499 _public enumerator_ `SYMS_DwAccess_Private = 0x01`
- L500 _public enumerator_ `SYMS_DwAccess_Protected = 0x02`
- L501 _public enumerator_ `SYMS_DwAccess_COUNT = 3`

#### enum `SYMS_DwVirtuality`  
`typedef enum SYMS_DwVirtuality`  
_L503-508_
- L504 _public enumerator_ `SYMS_DwVirtuality_None = 0x00`
- L505 _public enumerator_ `SYMS_DwVirtuality_Virtual = 0x01`
- L506 _public enumerator_ `SYMS_DwVirtuality_PureVirtual = 0x02`
- L507 _public enumerator_ `SYMS_DwVirtuality_COUNT = 3`

#### enum `SYMS_DwRngListEntryKind`  
`typedef enum SYMS_DwRngListEntryKind`  
_L509-519_
- L510 _public enumerator_ `SYMS_DwRngListEntryKind_EndOfList = 0x00`
- L511 _public enumerator_ `SYMS_DwRngListEntryKind_BaseAddressX = 0x01`
- L512 _public enumerator_ `SYMS_DwRngListEntryKind_StartxEndx = 0x02`
- L513 _public enumerator_ `SYMS_DwRngListEntryKind_StartxLength = 0x03`
- L514 _public enumerator_ `SYMS_DwRngListEntryKind_OffsetPair = 0x04`
- L515 _public enumerator_ `SYMS_DwRngListEntryKind_BaseAddress = 0x05`
- L516 _public enumerator_ `SYMS_DwRngListEntryKind_StartEnd = 0x06`
- L517 _public enumerator_ `SYMS_DwRngListEntryKind_StartLength = 0x07`
- L518 _public enumerator_ `SYMS_DwRngListEntryKind_COUNT = 8`

#### enum `SYMS_DwLocListEntryKind`  
`typedef enum SYMS_DwLocListEntryKind`  
_L520-531_
- L521 _public enumerator_ `SYMS_DwLocListEntryKind_EndOfList = 0x00`
- L522 _public enumerator_ `SYMS_DwLocListEntryKind_BaseAddressX = 0x01`
- L523 _public enumerator_ `SYMS_DwLocListEntryKind_StartXEndX = 0x02`
- L524 _public enumerator_ `SYMS_DwLocListEntryKind_StartXLength = 0x03`
- L525 _public enumerator_ `SYMS_DwLocListEntryKind_OffsetPair = 0x04`
- L526 _public enumerator_ `SYMS_DwLocListEntryKind_DefaultLocation = 0x05`
- L527 _public enumerator_ `SYMS_DwLocListEntryKind_BaseAddress = 0x06`
- L528 _public enumerator_ `SYMS_DwLocListEntryKind_StartEnd = 0x07`
- L529 _public enumerator_ `SYMS_DwLocListEntryKind_StartLength = 0x08`
- L530 _public enumerator_ `SYMS_DwLocListEntryKind_COUNT = 9`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_DWARF_H`
- L11 _typedef_ `} SYMS_DwMode;`
- L21 _typedef_ `} SYMS_DwVersion;`
- L42 _typedef_ `} SYMS_DwSectionKind;`
- L89 _typedef_ `} SYMS_DwLanguage;`
- L105 _typedef_ `} SYMS_DwStdOpcode;`
- L115 _typedef_ `} SYMS_DwExtOpcode;`
- L122 _typedef_ `} SYMS_DwNameCase;`
- L198 _typedef_ `} SYMS_DwTagKind;`
- L199 _typedef_ `typedef SYMS_U32 SYMS_DwAttribClass;`
- L201 _enumerator_ `SYMS_DwAttribClass_ADDRESS = (1 << 0)` (scope `__anoned47dcc70103`)
- L202 _enumerator_ `SYMS_DwAttribClass_BLOCK = (1 << 1)` (scope `__anoned47dcc70103`)
- L203 _enumerator_ `SYMS_DwAttribClass_CONST = (1 << 2)` (scope `__anoned47dcc70103`)
- L204 _enumerator_ `SYMS_DwAttribClass_EXPRLOC = (1 << 3)` (scope `__anoned47dcc70103`)
- L205 _enumerator_ `SYMS_DwAttribClass_FLAG = (1 << 4)` (scope `__anoned47dcc70103`)
- L206 _enumerator_ `SYMS_DwAttribClass_LINEPTR = (1 << 5)` (scope `__anoned47dcc70103`)
- L207 _enumerator_ `SYMS_DwAttribClass_LOCLIST = (1 << 6)` (scope `__anoned47dcc70103`)
- L208 _enumerator_ `SYMS_DwAttribClass_LOCLISTPTR = (1 << 7)` (scope `__anoned47dcc70103`)
- L209 _enumerator_ `SYMS_DwAttribClass_MACPTR = (1 << 8)` (scope `__anoned47dcc70103`)
- L210 _enumerator_ `SYMS_DwAttribClass_RNGLISTPTR = (1 << 9)` (scope `__anoned47dcc70103`)
- L211 _enumerator_ `SYMS_DwAttribClass_RNGLIST = (1 << 10)` (scope `__anoned47dcc70103`)
- L212 _enumerator_ `SYMS_DwAttribClass_REFERENCE = (1 << 11)` (scope `__anoned47dcc70103`)
- L213 _enumerator_ `SYMS_DwAttribClass_STRING = (1 << 12)` (scope `__anoned47dcc70103`)
- L214 _enumerator_ `SYMS_DwAttribClass_STROFFSETSPTR = (1 << 13)` (scope `__anoned47dcc70103`)
- L215 _enumerator_ `SYMS_DwAttribClass_ADDRPTR = (1 << 14)` (scope `__anoned47dcc70103`)
- L216 _enumerator_ `SYMS_DwAttribClass_UNDEFINED = (1 << 15)` (scope `__anoned47dcc70103`)
- L264 _typedef_ `} SYMS_DwFormKind;`
- L466 _typedef_ `} SYMS_DwAttribKind;`
- L488 _typedef_ `} SYMS_DwAttribTypeEncoding;`
- L496 _typedef_ `} SYMS_DwCallingConvention;`
- L502 _typedef_ `} SYMS_DwAccess;`
- L508 _typedef_ `} SYMS_DwVirtuality;`
- L519 _typedef_ `} SYMS_DwRngListEntryKind;`
- L531 _typedef_ `} SYMS_DwLocListEntryKind;`
- L535 _prototype_ `SYMS_Language syms_dw_base_language_from_dw_language(SYMS_DwLanguage v);`
- L536 _prototype_ `SYMS_DwVersion syms_dw_version_from_form_kind(SYMS_DwFormKind v);`
- L537 _prototype_ `SYMS_DwAttribClass syms_dw_attrib_class_from_form_kind(SYMS_DwFormKind v);`
- L538 _prototype_ `SYMS_DwVersion syms_dw_version_from_attrib_kind(SYMS_DwAttribKind v);`
- L539 _prototype_ `SYMS_DwAttribClass syms_dw_attrib_class_from_attrib_kind(SYMS_DwAttribKind v);`
- L540 _prototype_ `SYMS_DwVersion syms_dw_version_from_attrib_type_encoding(SYMS_DwAttribTypeEncoding v);`
- L541 _prototype_ `SYMS_CallConvention syms_dw_base_call_convention_from_dw_calling_convention(SYMS_DwCallingConvention v);`
- L542 _prototype_ `SYMS_MemVisibility syms_dw_mem_visibility_from_access(SYMS_DwAccess v);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_dwarf_cfi.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L7-37_

#### enum `(anonymous)`  
`enum`  
_L39-43_

#### enum `(anonymous)`  
`enum`  
_L45-50_

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_DWARF_CFI_H`
- L6 _typedef_ `typedef SYMS_U8 SYMS_DwCFA;`
- L9 _enumerator_ `SYMS_DwCFA_NOP = 0x0` (scope `__anon4612e8380103`) — kind1
- L10 _enumerator_ `SYMS_DwCFA_SET_LOC = 0x1` (scope `__anon4612e8380103`)
- L11 _enumerator_ `SYMS_DwCFA_ADVANCE_LOC1 = 0x2` (scope `__anon4612e8380103`)
- L12 _enumerator_ `SYMS_DwCFA_ADVANCE_LOC2 = 0x3` (scope `__anon4612e8380103`)
- L13 _enumerator_ `SYMS_DwCFA_ADVANCE_LOC4 = 0x4` (scope `__anon4612e8380103`)
- L14 _enumerator_ `SYMS_DwCFA_OFFSET_EXT = 0x5` (scope `__anon4612e8380103`)
- L15 _enumerator_ `SYMS_DwCFA_RESTORE_EXT = 0x6` (scope `__anon4612e8380103`)
- L16 _enumerator_ `SYMS_DwCFA_UNDEFINED = 0x7` (scope `__anon4612e8380103`)
- L17 _enumerator_ `SYMS_DwCFA_SAME_VALUE = 0x8` (scope `__anon4612e8380103`)
- L18 _enumerator_ `SYMS_DwCFA_REGISTER = 0x9` (scope `__anon4612e8380103`)
- L19 _enumerator_ `SYMS_DwCFA_REMEMBER_STATE = 0xA` (scope `__anon4612e8380103`)
- L20 _enumerator_ `SYMS_DwCFA_RESTORE_STATE = 0xB` (scope `__anon4612e8380103`)
- L21 _enumerator_ `SYMS_DwCFA_DEF_CFA = 0xC` (scope `__anon4612e8380103`)
- L22 _enumerator_ `SYMS_DwCFA_DEF_CFA_REGISTER = 0xD` (scope `__anon4612e8380103`)
- L23 _enumerator_ `SYMS_DwCFA_DEF_CFA_OFFSET = 0xE` (scope `__anon4612e8380103`)
- L24 _enumerator_ `SYMS_DwCFA_DEF_CFA_EXPR = 0xF` (scope `__anon4612e8380103`)
- L25 _enumerator_ `SYMS_DwCFA_EXPR = 0x10` (scope `__anon4612e8380103`)
- L26 _enumerator_ `SYMS_DwCFA_OFFSET_EXT_SF = 0x11` (scope `__anon4612e8380103`)
- L27 _enumerator_ `SYMS_DwCFA_DEF_CFA_SF = 0x12` (scope `__anon4612e8380103`)
- L28 _enumerator_ `SYMS_DwCFA_DEF_CFA_OFFSET_SF = 0x13` (scope `__anon4612e8380103`)
- L29 _enumerator_ `SYMS_DwCFA_VAL_OFFSET = 0x14` (scope `__anon4612e8380103`)
- L30 _enumerator_ `SYMS_DwCFA_VAL_OFFSET_SF = 0x15` (scope `__anon4612e8380103`)
- L31 _enumerator_ `SYMS_DwCFA_VAL_EXPR = 0x16` (scope `__anon4612e8380103`)
- L33 _enumerator_ `SYMS_DwCFA_ADVANCE_LOC = 0x40` (scope `__anon4612e8380103`) — kind2
- L34 _enumerator_ `SYMS_DwCFA_OFFSET = 0x80` (scope `__anon4612e8380103`)
- L35 _enumerator_ `SYMS_DwCFA_RESTORE = 0xC0` (scope `__anon4612e8380103`)
- L36 _enumerator_ `SYMS_DwCFA_COUNT = 26` (scope `__anon4612e8380103`)
- L38 _typedef_ `typedef SYMS_U8 SYMS_DwCFADetail;`
- L40 _enumerator_ `SYMS_DwCFADetail_OPL_KIND1 = SYMS_DwCFA_VAL_EXPR` (scope `__anon4612e8380203`)
- L41 _enumerator_ `SYMS_DwCFADetail_OPL_KIND2 = SYMS_DwCFA_RESTORE` (scope `__anon4612e8380203`)
- L42 _enumerator_ `SYMS_DwCFADetail_COUNT = 2` (scope `__anon4612e8380203`)
- L44 _typedef_ `typedef SYMS_U8 SYMS_DwCFAMask;`
- L47 _enumerator_ `SYMS_DwCFAMask_HI_OPCODE = 0xC0` (scope `__anon4612e8380303`) — kind1:  opcode: [0,5] zeroes:[6,7]; kind2:  operand:[0,5] opcode:[6,7]
- L48 _enumerator_ `SYMS_DwCFAMask_OPERAND = 0x3F` (scope `__anon4612e8380303`)
- L49 _enumerator_ `SYMS_DwCFAMask_COUNT = 2` (scope `__anon4612e8380303`)

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_dwarf_expr.h` (Other)


#### enum `SYMS_DwRegX86`  
`typedef enum SYMS_DwRegX86`  
_L6-54_
- L7 _public enumerator_ `SYMS_DwRegX86_EAX = 0`
- L8 _public enumerator_ `SYMS_DwRegX86_ECX = 1`
- L9 _public enumerator_ `SYMS_DwRegX86_EDX = 2`
- L10 _public enumerator_ `SYMS_DwRegX86_EBX = 3`
- L11 _public enumerator_ `SYMS_DwRegX86_ESP = 4`
- L12 _public enumerator_ `SYMS_DwRegX86_EBP = 5`
- L13 _public enumerator_ `SYMS_DwRegX86_ESI = 6`
- L14 _public enumerator_ `SYMS_DwRegX86_EDI = 7`
- L15 _public enumerator_ `SYMS_DwRegX86_EIP = 8`
- L16 _public enumerator_ `SYMS_DwRegX86_EFLAGS = 9`
- L17 _public enumerator_ `SYMS_DwRegX86_TRAPNO = 10`
- L18 _public enumerator_ `SYMS_DwRegX86_ST0 = 11`
- L19 _public enumerator_ `SYMS_DwRegX86_ST1 = 12`
- L20 _public enumerator_ `SYMS_DwRegX86_ST2 = 13`
- L21 _public enumerator_ `SYMS_DwRegX86_ST3 = 14`
- L22 _public enumerator_ `SYMS_DwRegX86_ST4 = 15`
- L23 _public enumerator_ `SYMS_DwRegX86_ST5 = 16`
- L24 _public enumerator_ `SYMS_DwRegX86_ST6 = 17`
- L25 _public enumerator_ `SYMS_DwRegX86_ST7 = 18`
- L26 _public enumerator_ `SYMS_DwRegX86_XMM0 = 21`
- L27 _public enumerator_ `SYMS_DwRegX86_XMM1 = 22`
- L28 _public enumerator_ `SYMS_DwRegX86_XMM2 = 23`
- L29 _public enumerator_ `SYMS_DwRegX86_XMM3 = 24`
- L30 _public enumerator_ `SYMS_DwRegX86_XMM4 = 25`
- L31 _public enumerator_ `SYMS_DwRegX86_XMM5 = 26`
- L32 _public enumerator_ `SYMS_DwRegX86_XMM6 = 27`
- L33 _public enumerator_ `SYMS_DwRegX86_XMM7 = 28`
- L34 _public enumerator_ `SYMS_DwRegX86_MM0 = 29`
- L35 _public enumerator_ `SYMS_DwRegX86_MM1 = 30`
- L36 _public enumerator_ `SYMS_DwRegX86_MM2 = 31`
- L37 _public enumerator_ `SYMS_DwRegX86_MM3 = 32`
- L38 _public enumerator_ `SYMS_DwRegX86_MM4 = 33`
- L39 _public enumerator_ `SYMS_DwRegX86_MM5 = 34`
- L40 _public enumerator_ `SYMS_DwRegX86_MM6 = 35`
- L41 _public enumerator_ `SYMS_DwRegX86_MM7 = 36`
- L42 _public enumerator_ `SYMS_DwRegX86_FCW = 37`
- L43 _public enumerator_ `SYMS_DwRegX86_FSW = 38`
- L44 _public enumerator_ `SYMS_DwRegX86_MXCSR = 39`
- L45 _public enumerator_ `SYMS_DwRegX86_ES = 40`
- L46 _public enumerator_ `SYMS_DwRegX86_CS = 41`
- L47 _public enumerator_ `SYMS_DwRegX86_SS = 42`
- L48 _public enumerator_ `SYMS_DwRegX86_DS = 43`
- L49 _public enumerator_ `SYMS_DwRegX86_FS = 44`
- L50 _public enumerator_ `SYMS_DwRegX86_GS = 45`
- L51 _public enumerator_ `SYMS_DwRegX86_TR = 48`
- L52 _public enumerator_ `SYMS_DwRegX86_LDTR = 49`
- L53 _public enumerator_ `SYMS_DwRegX86_COUNT = 46`

#### enum `(anonymous)`  
`enum`  
_L56-118_

#### enum `SYMS_DwOp`  
`typedef enum SYMS_DwOp`  
_L119-290_
- L120 _public enumerator_ `SYMS_DwOp_NULL`
- L121 _public enumerator_ `SYMS_DwOp_ADDR = 0x03`
- L122 _public enumerator_ `SYMS_DwOp_DEREF = 0x06`
- L123 _public enumerator_ `SYMS_DwOp_CONST1U = 0x08`
- L124 _public enumerator_ `SYMS_DwOp_CONST1S = 0x09`
- L125 _public enumerator_ `SYMS_DwOp_CONST2U = 0x0a`
- L126 _public enumerator_ `SYMS_DwOp_CONST2S = 0x0b`
- L127 _public enumerator_ `SYMS_DwOp_CONST4U = 0x0c`
- L128 _public enumerator_ `SYMS_DwOp_CONST4S = 0x0d`
- L129 _public enumerator_ `SYMS_DwOp_CONST8U = 0x0e`
- L130 _public enumerator_ `SYMS_DwOp_CONST8S = 0x0f`
- L131 _public enumerator_ `SYMS_DwOp_CONSTU = 0x10`
- L132 _public enumerator_ `SYMS_DwOp_CONSTS = 0x11`
- L133 _public enumerator_ `SYMS_DwOp_DUP = 0x12`
- L134 _public enumerator_ `SYMS_DwOp_DROP = 0x13`
- L135 _public enumerator_ `SYMS_DwOp_OVER = 0x14`
- L136 _public enumerator_ `SYMS_DwOp_PICK = 0x15`
- L137 _public enumerator_ `SYMS_DwOp_SWAP = 0x16`
- L138 _public enumerator_ `SYMS_DwOp_ROT = 0x17`
- L139 _public enumerator_ `SYMS_DwOp_XDEREF = 0x18`
- L140 _public enumerator_ `SYMS_DwOp_ABS = 0x19`
- L141 _public enumerator_ `SYMS_DwOp_AND = 0x1a`
- L142 _public enumerator_ `SYMS_DwOp_DIV = 0x1b`
- L143 _public enumerator_ `SYMS_DwOp_MINUS = 0x1c`
- L144 _public enumerator_ `SYMS_DwOp_MOD = 0x1d`
- L145 _public enumerator_ `SYMS_DwOp_MUL = 0x1e`
- L146 _public enumerator_ `SYMS_DwOp_NEG = 0x1f`
- L147 _public enumerator_ `SYMS_DwOp_NOT = 0x20`
- L148 _public enumerator_ `SYMS_DwOp_OR = 0x21`
- L149 _public enumerator_ `SYMS_DwOp_PLUS = 0x22`
- L150 _public enumerator_ `SYMS_DwOp_PLUS_UCONST = 0x23`
- L151 _public enumerator_ `SYMS_DwOp_SHL = 0x24`
- L152 _public enumerator_ `SYMS_DwOp_SHR = 0x25`
- L153 _public enumerator_ `SYMS_DwOp_SHRA = 0x26`
- L154 _public enumerator_ `SYMS_DwOp_XOR = 0x27`
- L155 _public enumerator_ `SYMS_DwOp_SKIP = 0x2f`
- L156 _public enumerator_ `SYMS_DwOp_BRA = 0x28`
- L157 _public enumerator_ `SYMS_DwOp_EQ = 0x29`
- L158 _public enumerator_ `SYMS_DwOp_GE = 0x2a`
- L159 _public enumerator_ `SYMS_DwOp_GT = 0x2b`
- L160 _public enumerator_ `SYMS_DwOp_LE = 0x2c`
- L161 _public enumerator_ `SYMS_DwOp_LT = 0x2d`
- L162 _public enumerator_ `SYMS_DwOp_NE = 0x2e`
- L163 _public enumerator_ `SYMS_DwOp_LIT0 = 0x30`
- L164 _public enumerator_ `SYMS_DwOp_LIT1 = 0x31`
- L165 _public enumerator_ `SYMS_DwOp_LIT2 = 0x32`
- L166 _public enumerator_ `SYMS_DwOp_LIT3 = 0x33`
- L167 _public enumerator_ `SYMS_DwOp_LIT4 = 0x34`
- L168 _public enumerator_ `SYMS_DwOp_LIT5 = 0x35`
- L169 _public enumerator_ `SYMS_DwOp_LIT6 = 0x36`
- L170 _public enumerator_ `SYMS_DwOp_LIT7 = 0x37`
- L171 _public enumerator_ `SYMS_DwOp_LIT8 = 0x38`
- L172 _public enumerator_ `SYMS_DwOp_LIT9 = 0x39`
- L173 _public enumerator_ `SYMS_DwOp_LIT10 = 0x3a`
- L174 _public enumerator_ `SYMS_DwOp_LIT11 = 0x3b`
- L175 _public enumerator_ `SYMS_DwOp_LIT12 = 0x3c`
- L176 _public enumerator_ `SYMS_DwOp_LIT13 = 0x3d`
- L177 _public enumerator_ `SYMS_DwOp_LIT14 = 0x3e`
- L178 _public enumerator_ `SYMS_DwOp_LIT15 = 0x3f`
- L179 _public enumerator_ `SYMS_DwOp_LIT16 = 0x40`
- L180 _public enumerator_ `SYMS_DwOp_LIT17 = 0x41`
- L181 _public enumerator_ `SYMS_DwOp_LIT18 = 0x42`
- L182 _public enumerator_ `SYMS_DwOp_LIT19 = 0x43`
- L183 _public enumerator_ `SYMS_DwOp_LIT20 = 0x44`
- L184 _public enumerator_ `SYMS_DwOp_LIT21 = 0x45`
- L185 _public enumerator_ `SYMS_DwOp_LIT22 = 0x46`
- L186 _public enumerator_ `SYMS_DwOp_LIT23 = 0x47`
- L187 _public enumerator_ `SYMS_DwOp_LIT24 = 0x48`
- L188 _public enumerator_ `SYMS_DwOp_LIT25 = 0x49`
- L189 _public enumerator_ `SYMS_DwOp_LIT26 = 0x4a`
- L190 _public enumerator_ `SYMS_DwOp_LIT27 = 0x4b`
- L191 _public enumerator_ `SYMS_DwOp_LIT28 = 0x4c`
- L192 _public enumerator_ `SYMS_DwOp_LIT29 = 0x4d`
- L193 _public enumerator_ `SYMS_DwOp_LIT30 = 0x4e`
- L194 _public enumerator_ `SYMS_DwOp_LIT31 = 0x4f`
- L195 _public enumerator_ `SYMS_DwOp_REG0 = 0x50`
- L196 _public enumerator_ `SYMS_DwOp_REG1 = 0x51`
- L197 _public enumerator_ `SYMS_DwOp_REG2 = 0x52`
- L198 _public enumerator_ `SYMS_DwOp_REG3 = 0x53`
- L199 _public enumerator_ `SYMS_DwOp_REG4 = 0x54`
- L200 _public enumerator_ `SYMS_DwOp_REG5 = 0x55`
- L201 _public enumerator_ `SYMS_DwOp_REG6 = 0x56`
- L202 _public enumerator_ `SYMS_DwOp_REG7 = 0x57`
- L203 _public enumerator_ `SYMS_DwOp_REG8 = 0x58`
- L204 _public enumerator_ `SYMS_DwOp_REG9 = 0x59`
- L205 _public enumerator_ `SYMS_DwOp_REG10 = 0x5a`
- L206 _public enumerator_ `SYMS_DwOp_REG11 = 0x5b`
- L207 _public enumerator_ `SYMS_DwOp_REG12 = 0x5c`
- L208 _public enumerator_ `SYMS_DwOp_REG13 = 0x5d`
- L209 _public enumerator_ `SYMS_DwOp_REG14 = 0x5e`
- L210 _public enumerator_ `SYMS_DwOp_REG15 = 0x5f`
- L211 _public enumerator_ `SYMS_DwOp_REG16 = 0x60`
- L212 _public enumerator_ `SYMS_DwOp_REG17 = 0x61`
- L213 _public enumerator_ `SYMS_DwOp_REG18 = 0x62`
- L214 _public enumerator_ `SYMS_DwOp_REG19 = 0x63`
- L215 _public enumerator_ `SYMS_DwOp_REG20 = 0x64`
- L216 _public enumerator_ `SYMS_DwOp_REG21 = 0x65`
- L217 _public enumerator_ `SYMS_DwOp_REG22 = 0x66`
- L218 _public enumerator_ `SYMS_DwOp_REG23 = 0x67`
- L219 _public enumerator_ `SYMS_DwOp_REG24 = 0x68`
- L220 _public enumerator_ `SYMS_DwOp_REG25 = 0x69`
- L221 _public enumerator_ `SYMS_DwOp_REG26 = 0x6a`
- L222 _public enumerator_ `SYMS_DwOp_REG27 = 0x6b`
- L223 _public enumerator_ `SYMS_DwOp_REG28 = 0x6c`
- L224 _public enumerator_ `SYMS_DwOp_REG29 = 0x6d`
- L225 _public enumerator_ `SYMS_DwOp_REG30 = 0x6e`
- L226 _public enumerator_ `SYMS_DwOp_REG31 = 0x6f`
- L227 _public enumerator_ `SYMS_DwOp_BREG0 = 0x70`
- L228 _public enumerator_ `SYMS_DwOp_BREG1 = 0x71`
- L229 _public enumerator_ `SYMS_DwOp_BREG2 = 0x72`
- L230 _public enumerator_ `SYMS_DwOp_BREG3 = 0x73`
- L231 _public enumerator_ `SYMS_DwOp_BREG4 = 0x74`
- L232 _public enumerator_ `SYMS_DwOp_BREG5 = 0x75`
- L233 _public enumerator_ `SYMS_DwOp_BREG6 = 0x76`
- L234 _public enumerator_ `SYMS_DwOp_BREG7 = 0x77`
- L235 _public enumerator_ `SYMS_DwOp_BREG8 = 0x78`
- L236 _public enumerator_ `SYMS_DwOp_BREG9 = 0x79`
- L237 _public enumerator_ `SYMS_DwOp_BREG10 = 0x7a`
- L238 _public enumerator_ `SYMS_DwOp_BREG11 = 0x7b`
- L239 _public enumerator_ `SYMS_DwOp_BREG12 = 0x7c`
- L240 _public enumerator_ `SYMS_DwOp_BREG13 = 0x7d`
- L241 _public enumerator_ `SYMS_DwOp_BREG14 = 0x7e`
- L242 _public enumerator_ `SYMS_DwOp_BREG15 = 0x7f`
- L243 _public enumerator_ `SYMS_DwOp_BREG16 = 0x80`
- L244 _public enumerator_ `SYMS_DwOp_BREG17 = 0x81`
- L245 _public enumerator_ `SYMS_DwOp_BREG18 = 0x82`
- L246 _public enumerator_ `SYMS_DwOp_BREG19 = 0x83`
- L247 _public enumerator_ `SYMS_DwOp_BREG20 = 0x84`
- L248 _public enumerator_ `SYMS_DwOp_BREG21 = 0x85`
- L249 _public enumerator_ `SYMS_DwOp_BREG22 = 0x86`
- L250 _public enumerator_ `SYMS_DwOp_BREG23 = 0x87`
- L251 _public enumerator_ `SYMS_DwOp_BREG24 = 0x88`
- L252 _public enumerator_ `SYMS_DwOp_BREG25 = 0x89`
- L253 _public enumerator_ `SYMS_DwOp_BREG26 = 0x8a`
- L254 _public enumerator_ `SYMS_DwOp_BREG27 = 0x8b`
- L255 _public enumerator_ `SYMS_DwOp_BREG28 = 0x8c`
- L256 _public enumerator_ `SYMS_DwOp_BREG29 = 0x8d`
- L257 _public enumerator_ `SYMS_DwOp_BREG30 = 0x8e`
- L258 _public enumerator_ `SYMS_DwOp_BREG31 = 0x8f`
- L259 _public enumerator_ `SYMS_DwOp_REGX = 0x90`
- L260 _public enumerator_ `SYMS_DwOp_FBREG = 0x91`
- L261 _public enumerator_ `SYMS_DwOp_BREGX = 0x92`
- L262 _public enumerator_ `SYMS_DwOp_PIECE = 0x93`
- L263 _public enumerator_ `SYMS_DwOp_DEREF_SIZE = 0x94`
- L264 _public enumerator_ `SYMS_DwOp_XDEREF_SIZE = 0x95`
- L265 _public enumerator_ `SYMS_DwOp_NOP = 0x96`
- L266 _public enumerator_ `SYMS_DwOp_PUSH_OBJECT_ADDRESS = 0x97`
- L267 _public enumerator_ `SYMS_DwOp_CALL2 = 0x98`
- L268 _public enumerator_ `SYMS_DwOp_CALL4 = 0x99`
- L269 _public enumerator_ `SYMS_DwOp_CALL_REF = 0x9a`
- L270 _public enumerator_ `SYMS_DwOp_FORM_TLS_ADDRESS = 0x9b`
- L271 _public enumerator_ `SYMS_DwOp_CALL_FRAME_CFA = 0x9c`
- L272 _public enumerator_ `SYMS_DwOp_BIT_PIECE = 0x9d`
- L273 _public enumerator_ `SYMS_DwOp_IMPLICIT_VALUE = 0x9e`
- L274 _public enumerator_ `SYMS_DwOp_STACK_VALUE = 0x9f`
- L275 _public enumerator_ `SYMS_DwOp_IMPLICIT_POINTER = 0xa0`
- L276 _public enumerator_ `SYMS_DwOp_ADDRX = 0xa1`
- L277 _public enumerator_ `SYMS_DwOp_CONSTX = 0xa2`
- L278 _public enumerator_ `SYMS_DwOp_ENTRY_VALUE = 0xa3`
- L279 _public enumerator_ `SYMS_DwOp_CONST_TYPE = 0xa4`
- L280 _public enumerator_ `SYMS_DwOp_REGVAL_TYPE = 0xa5`
- L281 _public enumerator_ `SYMS_DwOp_DEREF_TYPE = 0xa6`
- L282 _public enumerator_ `SYMS_DwOp_XDEREF_TYPE = 0xa7`
- L283 _public enumerator_ `SYMS_DwOp_CONVERT = 0xa8`
- L284 _public enumerator_ `SYMS_DwOp_REINTERPRET = 0xa9`
- L285 _public enumerator_ `SYMS_DwOp_GNU_PUSH_TLS_ADDRESS = 0xe0`
- L286 _public enumerator_ `SYMS_DwOp_GNU_UNINIT = 0xf0`
- L287 _public enumerator_ `SYMS_DwOp_LO_USER = SYMS_DwOp_GNU_PUSH_TLS_ADDRESS`
- L288 _public enumerator_ `SYMS_DwOp_HI_USER = 0xff`
- L289 _public enumerator_ `SYMS_DwOp_COUNT = 169`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_DWARF_EXPR_H`
- L54 _typedef_ `} SYMS_DwRegX86;`
- L55 _typedef_ `typedef SYMS_U32 SYMS_DwRegX64;`
- L57 _enumerator_ `SYMS_DwRegX64_RAX = 0` (scope `__anon0e64ea650103`)
- L58 _enumerator_ `SYMS_DwRegX64_RDX = 1` (scope `__anon0e64ea650103`)
- L59 _enumerator_ `SYMS_DwRegX64_RCX = 2` (scope `__anon0e64ea650103`)
- L60 _enumerator_ `SYMS_DwRegX64_RBX = 3` (scope `__anon0e64ea650103`)
- L61 _enumerator_ `SYMS_DwRegX64_RSI = 4` (scope `__anon0e64ea650103`)
- L62 _enumerator_ `SYMS_DwRegX64_RDI = 5` (scope `__anon0e64ea650103`)
- L63 _enumerator_ `SYMS_DwRegX64_RBP = 6` (scope `__anon0e64ea650103`)
- L64 _enumerator_ `SYMS_DwRegX64_RSP = 7` (scope `__anon0e64ea650103`)
- L65 _enumerator_ `SYMS_DwRegX64_R8 = 8` (scope `__anon0e64ea650103`)
- L66 _enumerator_ `SYMS_DwRegX64_R9 = 9` (scope `__anon0e64ea650103`)
- L67 _enumerator_ `SYMS_DwRegX64_R10 = 10` (scope `__anon0e64ea650103`)
- L68 _enumerator_ `SYMS_DwRegX64_R11 = 11` (scope `__anon0e64ea650103`)
- L69 _enumerator_ `SYMS_DwRegX64_R12 = 12` (scope `__anon0e64ea650103`)
- L70 _enumerator_ `SYMS_DwRegX64_R13 = 13` (scope `__anon0e64ea650103`)
- L71 _enumerator_ `SYMS_DwRegX64_R14 = 14` (scope `__anon0e64ea650103`)
- L72 _enumerator_ `SYMS_DwRegX64_R15 = 15` (scope `__anon0e64ea650103`)
- L73 _enumerator_ `SYMS_DwRegX64_RIP = 16` (scope `__anon0e64ea650103`)
- L74 _enumerator_ `SYMS_DwRegX64_XMM0 = 17` (scope `__anon0e64ea650103`)
- L75 _enumerator_ `SYMS_DwRegX64_XMM1 = 18` (scope `__anon0e64ea650103`)
- L76 _enumerator_ `SYMS_DwRegX64_XMM2 = 19` (scope `__anon0e64ea650103`)
- L77 _enumerator_ `SYMS_DwRegX64_XMM3 = 20` (scope `__anon0e64ea650103`)
- L78 _enumerator_ `SYMS_DwRegX64_XMM4 = 21` (scope `__anon0e64ea650103`)
- L79 _enumerator_ `SYMS_DwRegX64_XMM5 = 22` (scope `__anon0e64ea650103`)
- L80 _enumerator_ `SYMS_DwRegX64_XMM6 = 23` (scope `__anon0e64ea650103`)
- L81 _enumerator_ `SYMS_DwRegX64_XMM7 = 24` (scope `__anon0e64ea650103`)
- L82 _enumerator_ `SYMS_DwRegX64_XMM8 = 25` (scope `__anon0e64ea650103`)
- L83 _enumerator_ `SYMS_DwRegX64_XMM9 = 26` (scope `__anon0e64ea650103`)
- L84 _enumerator_ `SYMS_DwRegX64_XMM10 = 27` (scope `__anon0e64ea650103`)
- L85 _enumerator_ `SYMS_DwRegX64_XMM11 = 28` (scope `__anon0e64ea650103`)
- L86 _enumerator_ `SYMS_DwRegX64_XMM12 = 29` (scope `__anon0e64ea650103`)
- L87 _enumerator_ `SYMS_DwRegX64_XMM13 = 30` (scope `__anon0e64ea650103`)
- L88 _enumerator_ `SYMS_DwRegX64_XMM14 = 31` (scope `__anon0e64ea650103`)
- L89 _enumerator_ `SYMS_DwRegX64_XMM15 = 32` (scope `__anon0e64ea650103`)
- L90 _enumerator_ `SYMS_DwRegX64_ST0 = 33` (scope `__anon0e64ea650103`)
- L91 _enumerator_ `SYMS_DwRegX64_ST1 = 34` (scope `__anon0e64ea650103`)
- L92 _enumerator_ `SYMS_DwRegX64_ST2 = 35` (scope `__anon0e64ea650103`)
- L93 _enumerator_ `SYMS_DwRegX64_ST3 = 36` (scope `__anon0e64ea650103`)
- L94 _enumerator_ `SYMS_DwRegX64_ST4 = 37` (scope `__anon0e64ea650103`)
- L95 _enumerator_ `SYMS_DwRegX64_ST5 = 38` (scope `__anon0e64ea650103`)
- L96 _enumerator_ `SYMS_DwRegX64_ST6 = 39` (scope `__anon0e64ea650103`)
- L97 _enumerator_ `SYMS_DwRegX64_ST7 = 40` (scope `__anon0e64ea650103`)
- L98 _enumerator_ `SYMS_DwRegX64_MM0 = 41` (scope `__anon0e64ea650103`)
- L99 _enumerator_ `SYMS_DwRegX64_MM1 = 42` (scope `__anon0e64ea650103`)
- L100 _enumerator_ `SYMS_DwRegX64_MM2 = 43` (scope `__anon0e64ea650103`)
- L101 _enumerator_ `SYMS_DwRegX64_MM3 = 44` (scope `__anon0e64ea650103`)
- L102 _enumerator_ `SYMS_DwRegX64_MM4 = 45` (scope `__anon0e64ea650103`)
- L103 _enumerator_ `SYMS_DwRegX64_MM5 = 46` (scope `__anon0e64ea650103`)
- L104 _enumerator_ `SYMS_DwRegX64_MM6 = 47` (scope `__anon0e64ea650103`)
- L105 _enumerator_ `SYMS_DwRegX64_MM7 = 48` (scope `__anon0e64ea650103`)
- L106 _enumerator_ `SYMS_DwRegX64_RFLAGS = 49` (scope `__anon0e64ea650103`)
- L107 _enumerator_ `SYMS_DwRegX64_ES = 50` (scope `__anon0e64ea650103`)
- L108 _enumerator_ `SYMS_DwRegX64_CS = 51` (scope `__anon0e64ea650103`)
- L109 _enumerator_ `SYMS_DwRegX64_SS = 52` (scope `__anon0e64ea650103`)
- L110 _enumerator_ `SYMS_DwRegX64_DS = 53` (scope `__anon0e64ea650103`)
- L111 _enumerator_ `SYMS_DwRegX64_FS = 54` (scope `__anon0e64ea650103`)
- L112 _enumerator_ `SYMS_DwRegX64_GS = 55` (scope `__anon0e64ea650103`)
- L113 _enumerator_ `SYMS_DwRegX64_FS_BASE = 58` (scope `__anon0e64ea650103`)
- L114 _enumerator_ `SYMS_DwRegX64_GS_BASE = 59` (scope `__anon0e64ea650103`)
- L115 _enumerator_ `SYMS_DwRegX64_TR = 62` (scope `__anon0e64ea650103`)
- L116 _enumerator_ `SYMS_DwRegX64_LDTR = 63` (scope `__anon0e64ea650103`)
- L117 _enumerator_ `SYMS_DwRegX64_COUNT = 60` (scope `__anon0e64ea650103`)
- L290 _typedef_ `} SYMS_DwOp;`
- L294 _prototype_ `SYMS_RegID syms_reg_from_dw_reg_x86(SYMS_DwRegX86 v);`
- L295 _prototype_ `SYMS_RegID syms_reg_from_dw_reg_x64(SYMS_DwRegX64 v);`
- L296 _prototype_ `SYMS_DwVersion syms_dw_version_from_op_code(SYMS_DwOp v);`
- L297 _prototype_ `SYMS_U64 syms_dw_num_operands_from_op_code(SYMS_DwOp v);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_elf.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L7-12_

#### enum `(anonymous)`  
`enum`  
_L14-28_

#### enum `(anonymous)`  
`enum`  
_L30-34_

#### enum `(anonymous)`  
`enum`  
_L36-94_

#### enum `(anonymous)`  
`enum`  
_L96-103_

#### enum `(anonymous)`  
`enum`  
_L105-110_

#### enum `(anonymous)`  
`enum`  
_L112-138_

#### enum `(anonymous)`  
`enum`  
_L140-144_

#### enum `(anonymous)`  
`enum`  
_L146-189_

#### enum `(anonymous)`  
`enum`  
_L191-212_

#### enum `(anonymous)`  
`enum`  
_L214-231_

#### enum `(anonymous)`  
`enum`  
_L235-282_

#### enum `(anonymous)`  
`enum`  
_L284-362_

#### enum `(anonymous)`  
`enum`  
_L364-370_

#### enum `(anonymous)`  
`enum`  
_L372-375_

#### enum `(anonymous)`  
`enum`  
_L377-387_

#### enum `(anonymous)`  
`enum`  
_L389-405_

#### enum `(anonymous)`  
`enum`  
_L407-413_

#### enum `(anonymous)`  
`enum`  
_L415-462_

#### enum `(anonymous)`  
`enum`  
_L464-511_

#### enum `(anonymous)`  
`enum`  
_L513-517_

#### enum `(anonymous)`  
`enum`  
_L519-526_

#### enum `(anonymous)`  
`enum`  
_L528-537_

#### enum `(anonymous)`  
`enum`  
_L539-549_

#### enum `(anonymous)`  
`enum`  
_L551-556_

#### enum `(anonymous)`  
`enum`  
_L558-576_

#### enum `(anonymous)`  
`enum`  
_L578-603_

#### enum `(anonymous)`  
`enum`  
_L605-620_

#### enum `(anonymous)`  
`enum`  
_L622-627_

#### enum `(anonymous)`  
`enum`  
_L629-642_

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_ELF_H`
- L6 _typedef_ `typedef SYMS_U8 SYMS_ElfClass;`
- L8 _enumerator_ `SYMS_ElfClass_None = 0` (scope `__anonc3d9a30a0103`)
- L9 _enumerator_ `SYMS_ElfClass_32 = 1` (scope `__anonc3d9a30a0103`)
- L10 _enumerator_ `SYMS_ElfClass_64 = 2` (scope `__anonc3d9a30a0103`)
- L11 _enumerator_ `SYMS_ElfClass_COUNT = 3` (scope `__anonc3d9a30a0103`)
- L13 _typedef_ `typedef SYMS_U8 SYMS_ElfOsAbi;`
- L15 _enumerator_ `SYMS_ElfOsAbi_NONE` (scope `__anonc3d9a30a0203`)
- L16 _enumerator_ `SYMS_ElfOsAbi_SYSV` (scope `__anonc3d9a30a0203`)
- L17 _enumerator_ `SYMS_ElfOsAbi_HPUX` (scope `__anonc3d9a30a0203`)
- L18 _enumerator_ `SYMS_ElfOsAbi_NETBSD` (scope `__anonc3d9a30a0203`)
- L19 _enumerator_ `SYMS_ElfOsAbi_GNU` (scope `__anonc3d9a30a0203`)
- L20 _enumerator_ `SYMS_ElfOsAbi_LINUX` (scope `__anonc3d9a30a0203`)
- L21 _enumerator_ `SYMS_ElfOsAbi_SOLARIS` (scope `__anonc3d9a30a0203`)
- L22 _enumerator_ `SYMS_ElfOsAbi_IRIX` (scope `__anonc3d9a30a0203`)
- L23 _enumerator_ `SYMS_ElfOsAbi_FREEBSD` (scope `__anonc3d9a30a0203`)
- L24 _enumerator_ `SYMS_ElfOsAbi_TRU64` (scope `__anonc3d9a30a0203`)
- L25 _enumerator_ `SYMS_ElfOsAbi_ARM = 97` (scope `__anonc3d9a30a0203`)
- L26 _enumerator_ `SYMS_ElfOsAbi_STANDALONE = 255` (scope `__anonc3d9a30a0203`)
- L27 _enumerator_ `SYMS_ElfOsAbi_COUNT = 12` (scope `__anonc3d9a30a0203`)
- L29 _typedef_ `typedef SYMS_U8 SYMS_ElfVersion;`
- L31 _enumerator_ `SYMS_ElfVersion_NONE` (scope `__anonc3d9a30a0303`)
- L32 _enumerator_ `SYMS_ElfVersion_CURRENT` (scope `__anonc3d9a30a0303`)
- L33 _enumerator_ `SYMS_ElfVersion_COUNT = 2` (scope `__anonc3d9a30a0303`)
- L35 _typedef_ `typedef SYMS_U16 SYMS_ElfMachineKind;`
- L37 _enumerator_ `SYMS_ElfMachineKind_NONE = 0` (scope `__anonc3d9a30a0403`)
- L38 _enumerator_ `SYMS_ElfMachineKind_M32 = 1` (scope `__anonc3d9a30a0403`)
- L39 _enumerator_ `SYMS_ElfMachineKind_SPARC = 2` (scope `__anonc3d9a30a0403`)
- L40 _enumerator_ `SYMS_ElfMachineKind_386 = 3` (scope `__anonc3d9a30a0403`)
- L41 _enumerator_ `SYMS_ElfMachineKind_68K = 4` (scope `__anonc3d9a30a0403`)
- L42 _enumerator_ `SYMS_ElfMachineKind_88K = 5` (scope `__anonc3d9a30a0403`)
- L43 _enumerator_ `SYMS_ElfMachineKind_IAMCU = 6` (scope `__anonc3d9a30a0403`)
- L44 _enumerator_ `SYMS_ElfMachineKind_860 = 7` (scope `__anonc3d9a30a0403`)
- L45 _enumerator_ `SYMS_ElfMachineKind_MIPS = 8` (scope `__anonc3d9a30a0403`)
- L46 _enumerator_ `SYMS_ElfMachineKind_S370 = 9` (scope `__anonc3d9a30a0403`)
- L47 _enumerator_ `SYMS_ElfMachineKind_MIPS_RS3_LE = 10` (scope `__anonc3d9a30a0403`)
- L49 _enumerator_ `SYMS_ElfMachineKind_PARISC = 15` (scope `__anonc3d9a30a0403`) — 11-14 reserved
- L51 _enumerator_ `SYMS_ElfMachineKind_VPP500 = 17` (scope `__anonc3d9a30a0403`) — 16 reserved
- L52 _enumerator_ `SYMS_ElfMachineKind_SPARC32PLUS = 18` (scope `__anonc3d9a30a0403`)
- L54 _enumerator_ `SYMS_ElfMachineKind_INTEL960 = 19` (scope `__anonc3d9a30a0403`) — nick: Sun's "v8plus"
- L55 _enumerator_ `SYMS_ElfMachineKind_PPC = 20` (scope `__anonc3d9a30a0403`)
- L56 _enumerator_ `SYMS_ElfMachineKind_PPC64 = 21` (scope `__anonc3d9a30a0403`)
- L57 _enumerator_ `SYMS_ElfMachineKind_S390 = 22` (scope `__anonc3d9a30a0403`)
- L58 _enumerator_ `SYMS_ElfMachineKind_SPU = 23` (scope `__anonc3d9a30a0403`)
- L60 _enumerator_ `SYMS_ElfMachineKind_V800 = 36` (scope `__anonc3d9a30a0403`) — 24-35 reserved
- L61 _enumerator_ `SYMS_ElfMachineKind_FR20 = 37` (scope `__anonc3d9a30a0403`)
- L62 _enumerator_ `SYMS_ElfMachineKind_RH32 = 38` (scope `__anonc3d9a30a0403`)
- L63 _enumerator_ `SYMS_ElfMachineKind_MCORE = 39` (scope `__anonc3d9a30a0403`)
- L64 _enumerator_ `SYMS_ElfMachineKind_ARM = 40` (scope `__anonc3d9a30a0403`)
- L65 _enumerator_ `SYMS_ElfMachineKind_SH = 42` (scope `__anonc3d9a30a0403`)
- L66 _enumerator_ `SYMS_ElfMachineKind_ALPHA = 41` (scope `__anonc3d9a30a0403`)
- L67 _enumerator_ `SYMS_ElfMachineKind_SPARCV9 = 43` (scope `__anonc3d9a30a0403`)
- L68 _enumerator_ `SYMS_ElfMachineKind_TRICORE = 44` (scope `__anonc3d9a30a0403`)
- L69 _enumerator_ `SYMS_ElfMachineKind_ARC = 45` (scope `__anonc3d9a30a0403`)
- L70 _enumerator_ `SYMS_ElfMachineKind_H8_300 = 46` (scope `__anonc3d9a30a0403`)
- L71 _enumerator_ `SYMS_ElfMachineKind_H8_300H = 47` (scope `__anonc3d9a30a0403`)
- L72 _enumerator_ `SYMS_ElfMachineKind_H8S = 48` (scope `__anonc3d9a30a0403`)
- L73 _enumerator_ `SYMS_ElfMachineKind_H8_500 = 49` (scope `__anonc3d9a30a0403`)
- L74 _enumerator_ `SYMS_ElfMachineKind_IA_64 = 50` (scope `__anonc3d9a30a0403`)
- L75 _enumerator_ `SYMS_ElfMachineKind_MIPS_X = 51` (scope `__anonc3d9a30a0403`)
- L76 _enumerator_ `SYMS_ElfMachineKind_COLDFILE = 52` (scope `__anonc3d9a30a0403`)
- L77 _enumerator_ `SYMS_ElfMachineKind_68HC12 = 53` (scope `__anonc3d9a30a0403`)
- L78 _enumerator_ `SYMS_ElfMachineKind_MMA = 54` (scope `__anonc3d9a30a0403`)
- L79 _enumerator_ `SYMS_ElfMachineKind_PCP = 55` (scope `__anonc3d9a30a0403`)
- L80 _enumerator_ `SYMS_ElfMachineKind_NCPU = 56` (scope `__anonc3d9a30a0403`)
- L81 _enumerator_ `SYMS_ElfMachineKind_NDR1 = 57` (scope `__anonc3d9a30a0403`)
- L82 _enumerator_ `SYMS_ElfMachineKind_STARCORE = 58` (scope `__anonc3d9a30a0403`)
- L83 _enumerator_ `SYMS_ElfMachineKind_ME16 = 59` (scope `__anonc3d9a30a0403`)
- L84 _enumerator_ `SYMS_ElfMachineKind_ST100 = 60` (scope `__anonc3d9a30a0403`)
- L85 _enumerator_ `SYMS_ElfMachineKind_TINYJ = 61` (scope `__anonc3d9a30a0403`)
- L86 _enumerator_ `SYMS_ElfMachineKind_X86_64 = 62` (scope `__anonc3d9a30a0403`)
- L87 _enumerator_ `SYMS_ElfMachineKind_AARCH64 = 183` (scope `__anonc3d9a30a0403`)
- L88 _enumerator_ `SYMS_ElfMachineKind_TI_C6000 = 140` (scope `__anonc3d9a30a0403`)
- L89 _enumerator_ `SYMS_ElfMachineKind_L1OM = 180` (scope `__anonc3d9a30a0403`)
- L90 _enumerator_ `SYMS_ElfMachineKind_K1OM = 181` (scope `__anonc3d9a30a0403`)
- L91 _enumerator_ `SYMS_ElfMachineKind_RISCV = 243` (scope `__anonc3d9a30a0403`)
- L92 _enumerator_ `SYMS_ElfMachineKind_S390_OLD = 0xA390` (scope `__anonc3d9a30a0403`)
- L93 _enumerator_ `SYMS_ElfMachineKind_COUNT = 52` (scope `__anonc3d9a30a0403`)
- L95 _typedef_ `typedef SYMS_U16 SYMS_ElfType;`
- L97 _enumerator_ `SYMS_ElfType_NONE` (scope `__anonc3d9a30a0503`)
- L98 _enumerator_ `SYMS_ElfType_REL` (scope `__anonc3d9a30a0503`)
- L99 _enumerator_ `SYMS_ElfType_EXEC` (scope `__anonc3d9a30a0503`)
- L100 _enumerator_ `SYMS_ElfType_DYN` (scope `__anonc3d9a30a0503`)
- L101 _enumerator_ `SYMS_ElfType_CORE` (scope `__anonc3d9a30a0503`)
- L102 _enumerator_ `SYMS_ElfType_COUNT = 5` (scope `__anonc3d9a30a0503`)
- L104 _typedef_ `typedef SYMS_U8 SYMS_ElfData;`
- L106 _enumerator_ `SYMS_ElfData_None = 0` (scope `__anonc3d9a30a0603`)
- L107 _enumerator_ `SYMS_ElfData_2LSB = 1` (scope `__anonc3d9a30a0603`)
- L108 _enumerator_ `SYMS_ElfData_2MSB = 2` (scope `__anonc3d9a30a0603`)
- L109 _enumerator_ `SYMS_ElfData_COUNT = 3` (scope `__anonc3d9a30a0603`)
- L111 _typedef_ `typedef SYMS_U32 SYMS_ElfPKind;`
- L114 _enumerator_ `SYMS_ElfPKind_Null = 0` (scope `__anonc3d9a30a0703`) — TODO(nick): This is actually PType
- L115 _enumerator_ `SYMS_ElfPKind_Load = 1` (scope `__anonc3d9a30a0703`)
- L116 _enumerator_ `SYMS_ElfPKind_Dynamic = 2` (scope `__anonc3d9a30a0703`)
- L117 _enumerator_ `SYMS_ElfPKind_Interp = 3` (scope `__anonc3d9a30a0703`)
- L118 _enumerator_ `SYMS_ElfPKind_Note = 4` (scope `__anonc3d9a30a0703`)
- L119 _enumerator_ `SYMS_ElfPKind_SHLib = 5` (scope `__anonc3d9a30a0703`)
- L120 _enumerator_ `SYMS_ElfPKind_PHDR = 6` (scope `__anonc3d9a30a0703`)
- L121 _enumerator_ `SYMS_ElfPKind_TLS = 7` (scope `__anonc3d9a30a0703`)
- L122 _enumerator_ `SYMS_ElfPKind_LOOS = 0x60000000` (scope `__anonc3d9a30a0703`)
- L123 _enumerator_ `SYMS_ElfPKind_HIOS = 0x6fffffff` (scope `__anonc3d9a30a0703`)
- L124 _enumerator_ `SYMS_ElfPKind_LowProc = 0x70000000` (scope `__anonc3d9a30a0703`)
- L125 _enumerator_ `SYMS_ElfPKind_HighProc = 0x7fffffff` (scope `__anonc3d9a30a0703`)
- L127 _enumerator_ `SYMS_ElfPKind_LowSunW = 0x6ffffffa` (scope `__anonc3d9a30a0703`) — - specific to Sun
- L128 _enumerator_ `SYMS_ElfPKind_SunWBSS = 0x6ffffffb` (scope `__anonc3d9a30a0703`)
- L129 _enumerator_ `SYMS_ElfPKind_GnuEHFrame = 0x6474E550` (scope `__anonc3d9a30a0703`)
- L131 _enumerator_ `SYMS_ElfPKind_GnuStack = 0x6474E551` (scope `__anonc3d9a30a0703`) — SYMS_ElfPKind_LOOS + 0x474e550, // frame unwind information
- L133 _enumerator_ `SYMS_ElfPKind_GnuRelro = 0x6474E552` (scope `__anonc3d9a30a0703`) — SYMS_ElfPKind_LOOS + 0x474e551, // stack flags
- L135 _enumerator_ `SYMS_ElfPKind_GnuProperty = 0x6474E553` (scope `__anonc3d9a30a0703`) — SYMS_ElfPKind_LOOS + 0x474e552, // read-only after relocations
- L136 _enumerator_ `SYMS_ElfPKind_SunEHFrame = SYMS_ElfPKind_GnuEHFrame` (scope `__anonc3d9a30a0703`)
- L137 _enumerator_ `SYMS_ElfPKind_COUNT = 19` (scope `__anonc3d9a30a0703`)
- L139 _typedef_ `typedef SYMS_U32 SYMS_ElfPFlag;`
- L141 _enumerator_ `SYMS_ElfPFlag_Exec = (1 << 0)` (scope `__anonc3d9a30a0803`)
- L142 _enumerator_ `SYMS_ElfPFlag_Write = (1 << 1)` (scope `__anonc3d9a30a0803`)
- L143 _enumerator_ `SYMS_ElfPFlag_Read = (1 << 2)` (scope `__anonc3d9a30a0803`)
- L145 _typedef_ `typedef SYMS_U32 SYMS_ElfSectionCode;`
- L147 _enumerator_ `SYMS_ElfSectionCode_NULL = 0` (scope `__anonc3d9a30a0903`)
- L148 _enumerator_ `SYMS_ElfSectionCode_PROGBITS = 1` (scope `__anonc3d9a30a0903`)
- L149 _enumerator_ `SYMS_ElfSectionCode_SYMTAB = 2` (scope `__anonc3d9a30a0903`)
- L150 _enumerator_ `SYMS_ElfSectionCode_STRTAB = 3` (scope `__anonc3d9a30a0903`)
- L151 _enumerator_ `SYMS_ElfSectionCode_RELA = 4` (scope `__anonc3d9a30a0903`)
- L152 _enumerator_ `SYMS_ElfSectionCode_HASH = 5` (scope `__anonc3d9a30a0903`)
- L153 _enumerator_ `SYMS_ElfSectionCode_DYNAMIC = 6` (scope `__anonc3d9a30a0903`)
- L154 _enumerator_ `SYMS_ElfSectionCode_NOTE = 7` (scope `__anonc3d9a30a0903`)
- L155 _enumerator_ `SYMS_ElfSectionCode_NOBITS = 8` (scope `__anonc3d9a30a0903`)
- L156 _enumerator_ `SYMS_ElfSectionCode_REL = 9` (scope `__anonc3d9a30a0903`)
- L157 _enumerator_ `SYMS_ElfSectionCode_SHLIB = 10` (scope `__anonc3d9a30a0903`)
- L158 _enumerator_ `SYMS_ElfSectionCode_DYNSYM = 11` (scope `__anonc3d9a30a0903`)
- L159 _enumerator_ `SYMS_ElfSectionCode_INIT_ARRAY = 14` (scope `__anonc3d9a30a0903`)
- L161 _enumerator_ `SYMS_ElfSectionCode_FINI_ARRAY = 15` (scope `__anonc3d9a30a0903`) — nick: Array of ptrs to init functions
- L163 _enumerator_ `SYMS_ElfSectionCode_PREINIT_ARRAY = 16` (scope `__anonc3d9a30a0903`) — nick: Array of ptrs to finish functions
- L165 _enumerator_ `SYMS_ElfSectionCode_GROUP = 17` (scope `__anonc3d9a30a0903`) — nick: Array of ptrs to pre-init funcs
- L167 _enumerator_ `SYMS_ElfSectionCode_SYMTAB_SHNDX = 18` (scope `__anonc3d9a30a0903`) — nick: Section contains a section group
- L169 _enumerator_ `SYMS_ElfSectionCode_GNU_INCREMENTAL_INPUTS = 0x6fff4700` (scope `__anonc3d9a30a0903`) — nick: Indices for SHN_XINDEX entries
- L171 _enumerator_ `SYMS_ElfSectionCode_GNU_ATTRIBUTES = 0x6ffffff5` (scope `__anonc3d9a30a0903`) — nick: incremental build data
- L173 _enumerator_ `SYMS_ElfSectionCode_GNU_HASH = 0x6ffffff6` (scope `__anonc3d9a30a0903`) — nick: Object attributes
- L175 _enumerator_ `SYMS_ElfSectionCode_GNU_LIBLIST = 0x6ffffff7` (scope `__anonc3d9a30a0903`) — nick: GNU style symbol hash table
- L177 _enumerator_ `SYMS_ElfSectionCode_SUNW_verdef = 0x6ffffffd` (scope `__anonc3d9a30a0903`) — versions.
- L179 _enumerator_ `SYMS_ElfSectionCode_SUNW_verneed = 0x6ffffffe` (scope `__anonc3d9a30a0903`) — nick: Versions defined by file
- L181 _enumerator_ `SYMS_ElfSectionCode_SUNW_versym = 0x6fffffff` (scope `__anonc3d9a30a0903`) — nick: Versions needed by file
- L183 _enumerator_ `SYMS_ElfSectionCode_GNU_verdef = SYMS_ElfSectionCode_SUNW_verdef` (scope `__anonc3d9a30a0903`) — nick: Symbol versions
- L184 _enumerator_ `SYMS_ElfSectionCode_GNU_verneed = SYMS_ElfSectionCode_SUNW_verneed` (scope `__anonc3d9a30a0903`)
- L185 _enumerator_ `SYMS_ElfSectionCode_GNU_versym = SYMS_ElfSectionCode_SUNW_versym` (scope `__anonc3d9a30a0903`)
- L186 _enumerator_ `SYMS_ElfSectionCode_PROC` (scope `__anonc3d9a30a0903`)
- L187 _enumerator_ `SYMS_ElfSectionCode_USER` (scope `__anonc3d9a30a0903`)
- L188 _enumerator_ `SYMS_ElfSectionCode_COUNT = 29` (scope `__anonc3d9a30a0903`)
- L190 _typedef_ `typedef SYMS_U32 SYMS_ElfSectionIndex;`
- L193 _enumerator_ `SYMS_ElfSectionIndex_UNDEF = 0` (scope `__anonc3d9a30a0a03`) — Symbol with section index is undefined and must be resolved by the link editor.
- L195 _enumerator_ `SYMS_ElfSectionIndex_ABS = 0xfff1` (scope `__anonc3d9a30a0a03`) — Symbol has absolute value and wont change after relocations.
- L197 _enumerator_ `SYMS_ElfSectionIndex_COMMON = 0xfff2` (scope `__anonc3d9a30a0a03`) — This symbol indicates to linker to allocate the storage at address multiple of st_value.
- L198 _enumerator_ `SYMS_ElfSectionIndex_LO_RESERVE = 0xff00` (scope `__anonc3d9a30a0a03`)
- L199 _enumerator_ `SYMS_ElfSectionIndex_HI_RESERVE = 0xffff` (scope `__anonc3d9a30a0a03`)
- L201 _enumerator_ `SYMS_ElfSectionIndex_LO_PROC = SYMS_ElfSectionIndex_LO_RESERVE` (scope `__anonc3d9a30a0a03`) — Processor specific
- L202 _enumerator_ `SYMS_ElfSectionIndex_HI_PROC = 0xff1f` (scope `__anonc3d9a30a0a03`)
- L204 _enumerator_ `SYMS_ElfSectionIndex_LO_OS = 0xff20` (scope `__anonc3d9a30a0a03`) — Reserved for OS
- L205 _enumerator_ `SYMS_ElfSectionIndex_HI_OS = 0xff3f` (scope `__anonc3d9a30a0a03`)
- L206 _enumerator_ `SYMS_ElfSectionIndex_IA_64_ASNI_COMMON = SYMS_ElfSectionIndex_LO_PROC` (scope `__anonc3d9a30a0a03`)
- L207 _enumerator_ `SYMS_ElfSectionIndex_X86_64_LCOMMON = 0xff02` (scope `__anonc3d9a30a0a03`)
- L208 _enumerator_ `SYMS_ElfSectionIndex_MIPS_SCOMMON = 0xff03` (scope `__anonc3d9a30a0a03`)
- L209 _enumerator_ `SYMS_ElfSectionIndex_TIC6X_COMMON = SYMS_ElfSectionIndex_LO_RESERVE` (scope `__anonc3d9a30a0a03`)
- L210 _enumerator_ `SYMS_ElfSectionIndex_MIPS_SUNDEFINED = 0xff04` (scope `__anonc3d9a30a0a03`)
- L211 _enumerator_ `SYMS_ElfSectionIndex_COUNT = 14` (scope `__anonc3d9a30a0a03`)
- L213 _typedef_ `typedef SYMS_U32 SYMS_ElfSectionFlag;`
- L215 _enumerator_ `SYMS_ElfSectionFlag_WRITE = (1 << 0)` (scope `__anonc3d9a30a0b03`)
- L216 _enumerator_ `SYMS_ElfSectionFlag_ALLOC = (1 << 1)` (scope `__anonc3d9a30a0b03`)
- L217 _enumerator_ `SYMS_ElfSectionFlag_EXECINSTR = (1 << 2)` (scope `__anonc3d9a30a0b03`)
- L218 _enumerator_ `SYMS_ElfSectionFlag_MERGE = (1 << 4)` (scope `__anonc3d9a30a0b03`)
- L219 _enumerator_ `SYMS_ElfSectionFlag_STRINGS = (1 << 5)` (scope `__anonc3d9a30a0b03`)
- L220 _enumerator_ `SYMS_ElfSectionFlag_INFO_LINK = (1 << 6)` (scope `__anonc3d9a30a0b03`)
- L221 _enumerator_ `SYMS_ElfSectionFlag_LINK_ORDER = (1 << 7)` (scope `__anonc3d9a30a0b03`)
- L222 _enumerator_ `SYMS_ElfSectionFlag_OS_NONCONFORMING = (1 << 8)` (scope `__anonc3d9a30a0b03`)
- L223 _enumerator_ `SYMS_ElfSectionFlag_GROUP = (1 << 9)` (scope `__anonc3d9a30a0b03`)
- L224 _enumerator_ `SYMS_ElfSectionFlag_TLS = (1 << 10)` (scope `__anonc3d9a30a0b03`)
- L225 _enumerator_ `SYMS_ElfSectionFlag_COMPRESSED = (1 << 11)` (scope `__anonc3d9a30a0b03`)
- L226 _enumerator_ `SYMS_ElfSectionFlag_MASKOS_SHIFT = 16` (scope `__anonc3d9a30a0b03`)
- L226 _enumerator_ `SYMS_ElfSectionFlag_MASKOS_SHIFT = 16` (scope `__anonc3d9a30a0b03`)
- L227 _enumerator_ `SYMS_ElfSectionFlag_AMD64_LARGE = (1 << 28)` (scope `__anonc3d9a30a0b03`)
- L228 _enumerator_ `SYMS_ElfSectionFlag_ORDERED = (1 << 30)` (scope `__anonc3d9a30a0b03`)
- L229 _enumerator_ `SYMS_ElfSectionFlag_EXCLUDE = (1 << 31)` (scope `__anonc3d9a30a0b03`)
- L230 _enumerator_ `SYMS_ElfSectionFlag_MASKPROC_SHIFT = 28` (scope `__anonc3d9a30a0b03`)
- L230 _enumerator_ `SYMS_ElfSectionFlag_MASKPROC_SHIFT = 28` (scope `__anonc3d9a30a0b03`)
- L232 _macro_ `#define SYMS_ElfSectionFlag_Extract_MASKOS(f) (SYMS_U8)(((f) >> SYMS_ElfSectionFlag_MASKOS_SHIFT) & SYMS_ElfSectionFlag_MASKOS_MASK)`
- L233 _macro_ `#define SYMS_ElfSectionFlag_Extract_MASKPROC(f) (SYMS_U8)(((f) >> SYMS_ElfSectionFlag_MASKPROC_SHIFT) & SYMS_ElfSectionFlag_MASKPROC_MASK)`
- L234 _typedef_ `typedef SYMS_U32 SYMS_ElfAuxType;`
- L236 _enumerator_ `SYMS_ElfAuxType_NULL = 0` (scope `__anonc3d9a30a0c03`)
- L237 _enumerator_ `SYMS_ElfAuxType_PHDR = 3` (scope `__anonc3d9a30a0c03`)
- L239 _enumerator_ `SYMS_ElfAuxType_PHENT = 4` (scope `__anonc3d9a30a0c03`) — program headers
- L241 _enumerator_ `SYMS_ElfAuxType_PHNUM = 5` (scope `__anonc3d9a30a0c03`) — size of a program header
- L243 _enumerator_ `SYMS_ElfAuxType_PAGESZ = 6` (scope `__anonc3d9a30a0c03`) — number of program headers
- L245 _enumerator_ `SYMS_ElfAuxType_BASE = 7` (scope `__anonc3d9a30a0c03`) — system page size
- L247 _enumerator_ `SYMS_ElfAuxType_FLAGS = 8` (scope `__anonc3d9a30a0c03`) — interpreter base address
- L248 _enumerator_ `SYMS_ElfAuxType_ENTRY = 9` (scope `__anonc3d9a30a0c03`)
- L250 _enumerator_ `SYMS_ElfAuxType_UID = 11` (scope `__anonc3d9a30a0c03`) — program entry point
- L251 _enumerator_ `SYMS_ElfAuxType_EUID = 12` (scope `__anonc3d9a30a0c03`)
- L252 _enumerator_ `SYMS_ElfAuxType_GID = 13` (scope `__anonc3d9a30a0c03`)
- L253 _enumerator_ `SYMS_ElfAuxType_EGID = 14` (scope `__anonc3d9a30a0c03`)
- L254 _enumerator_ `SYMS_ElfAuxType_PLATFORM = 15` (scope `__anonc3d9a30a0c03`)
- L256 _enumerator_ `SYMS_ElfAuxType_HWCAP = 16` (scope `__anonc3d9a30a0c03`) — 'platform' as a string (TODO(allen): study)
- L257 _enumerator_ `SYMS_ElfAuxType_CLKTCK = 17` (scope `__anonc3d9a30a0c03`)
- L258 _enumerator_ `SYMS_ElfAuxType_DCACHEBSIZE = 19` (scope `__anonc3d9a30a0c03`)
- L259 _enumerator_ `SYMS_ElfAuxType_ICACHEBSIZE = 20` (scope `__anonc3d9a30a0c03`)
- L260 _enumerator_ `SYMS_ElfAuxType_UCACHEBSIZE = 21` (scope `__anonc3d9a30a0c03`)
- L261 _enumerator_ `SYMS_ElfAuxType_IGNOREPPC = 22` (scope `__anonc3d9a30a0c03`)
- L262 _enumerator_ `SYMS_ElfAuxType_SECURE = 23` (scope `__anonc3d9a30a0c03`)
- L263 _enumerator_ `SYMS_ElfAuxType_BASE_PLATFORM = 24` (scope `__anonc3d9a30a0c03`)
- L265 _enumerator_ `SYMS_ElfAuxType_RANDOM = 25` (scope `__anonc3d9a30a0c03`) — 'platform' as a string (different) (TODO(allen): study)
- L267 _enumerator_ `SYMS_ElfAuxType_HWCAP2 = 26` (scope `__anonc3d9a30a0c03`) — addres to 16 random bytes
- L268 _enumerator_ `SYMS_ElfAuxType_EXECFN = 31` (scope `__anonc3d9a30a0c03`)
- L270 _enumerator_ `SYMS_ElfAuxType_SYSINFO = 32` (scope `__anonc3d9a30a0c03`) — file name of executable
- L271 _enumerator_ `SYMS_ElfAuxType_SYSINFO_EHDR = 33` (scope `__anonc3d9a30a0c03`)
- L273 _enumerator_ `SYMS_ElfAuxType_L1I_CACHESIZE = 40` (scope `__anonc3d9a30a0c03`) — cool info about caches? (TODO(allen): study)
- L274 _enumerator_ `SYMS_ElfAuxType_L1I_CACHEGEOMETRY = 41` (scope `__anonc3d9a30a0c03`)
- L275 _enumerator_ `SYMS_ElfAuxType_L1D_CACHESIZE = 42` (scope `__anonc3d9a30a0c03`)
- L276 _enumerator_ `SYMS_ElfAuxType_L1D_CACHEGEOMETRY = 43` (scope `__anonc3d9a30a0c03`)
- L277 _enumerator_ `SYMS_ElfAuxType_L2_CACHESIZE = 44` (scope `__anonc3d9a30a0c03`)
- L278 _enumerator_ `SYMS_ElfAuxType_L2_CACHEGEOMETRY = 45` (scope `__anonc3d9a30a0c03`)
- L279 _enumerator_ `SYMS_ElfAuxType_L3_CACHESIZE = 46` (scope `__anonc3d9a30a0c03`)
- L280 _enumerator_ `SYMS_ElfAuxType_L3_CACHEGEOMETRY = 47` (scope `__anonc3d9a30a0c03`)
- L281 _enumerator_ `SYMS_ElfAuxType_COUNT = 34` (scope `__anonc3d9a30a0c03`)
- L283 _typedef_ `typedef SYMS_U32 SYMS_ElfDynTag;`
- L285 _enumerator_ `SYMS_ElfDynTag_NULL = 0` (scope `__anonc3d9a30a0d03`)
- L286 _enumerator_ `SYMS_ElfDynTag_NEEDED = 1` (scope `__anonc3d9a30a0d03`)
- L287 _enumerator_ `SYMS_ElfDynTag_PLTRELSZ = 2` (scope `__anonc3d9a30a0d03`)
- L288 _enumerator_ `SYMS_ElfDynTag_PLTGOT = 3` (scope `__anonc3d9a30a0d03`)
- L289 _enumerator_ `SYMS_ElfDynTag_HASH = 4` (scope `__anonc3d9a30a0d03`)
- L290 _enumerator_ `SYMS_ElfDynTag_STRTAB = 5` (scope `__anonc3d9a30a0d03`)
- L291 _enumerator_ `SYMS_ElfDynTag_SYMTAB = 6` (scope `__anonc3d9a30a0d03`)
- L292 _enumerator_ `SYMS_ElfDynTag_RELA = 7` (scope `__anonc3d9a30a0d03`)
- L293 _enumerator_ `SYMS_ElfDynTag_RELASZ = 8` (scope `__anonc3d9a30a0d03`)
- L294 _enumerator_ `SYMS_ElfDynTag_RELAENT = 9` (scope `__anonc3d9a30a0d03`)
- L295 _enumerator_ `SYMS_ElfDynTag_STRSZ = 10` (scope `__anonc3d9a30a0d03`)
- L296 _enumerator_ `SYMS_ElfDynTag_SYMENT = 11` (scope `__anonc3d9a30a0d03`)
- L297 _enumerator_ `SYMS_ElfDynTag_INIT = 12` (scope `__anonc3d9a30a0d03`)
- L298 _enumerator_ `SYMS_ElfDynTag_FINI = 13` (scope `__anonc3d9a30a0d03`)
- L299 _enumerator_ `SYMS_ElfDynTag_SONAME = 14` (scope `__anonc3d9a30a0d03`)
- L300 _enumerator_ `SYMS_ElfDynTag_RPATH = 15` (scope `__anonc3d9a30a0d03`)
- L301 _enumerator_ `SYMS_ElfDynTag_SYMBOLIC = 16` (scope `__anonc3d9a30a0d03`)
- L302 _enumerator_ `SYMS_ElfDynTag_REL = 17` (scope `__anonc3d9a30a0d03`)
- L303 _enumerator_ `SYMS_ElfDynTag_RELSZ = 18` (scope `__anonc3d9a30a0d03`)
- L304 _enumerator_ `SYMS_ElfDynTag_RELENT = 19` (scope `__anonc3d9a30a0d03`)
- L305 _enumerator_ `SYMS_ElfDynTag_PLTREL = 20` (scope `__anonc3d9a30a0d03`)
- L306 _enumerator_ `SYMS_ElfDynTag_DEBUG = 21` (scope `__anonc3d9a30a0d03`)
- L307 _enumerator_ `SYMS_ElfDynTag_TEXTREL = 22` (scope `__anonc3d9a30a0d03`)
- L308 _enumerator_ `SYMS_ElfDynTag_JMPREL = 23` (scope `__anonc3d9a30a0d03`)
- L309 _enumerator_ `SYMS_ElfDynTag_BIND_NOW = 24` (scope `__anonc3d9a30a0d03`)
- L310 _enumerator_ `SYMS_ElfDynTag_INIT_ARRAY = 25` (scope `__anonc3d9a30a0d03`)
- L311 _enumerator_ `SYMS_ElfDynTag_FINI_ARRAY = 26` (scope `__anonc3d9a30a0d03`)
- L312 _enumerator_ `SYMS_ElfDynTag_INIT_ARRAYSZ = 27` (scope `__anonc3d9a30a0d03`)
- L313 _enumerator_ `SYMS_ElfDynTag_FINI_ARRAYSZ = 28` (scope `__anonc3d9a30a0d03`)
- L314 _enumerator_ `SYMS_ElfDynTag_RUNPATH = 29` (scope `__anonc3d9a30a0d03`)
- L315 _enumerator_ `SYMS_ElfDynTag_FLAGS = 30` (scope `__anonc3d9a30a0d03`)
- L316 _enumerator_ `SYMS_ElfDynTag_PREINIT_ARRAY = 32` (scope `__anonc3d9a30a0d03`)
- L317 _enumerator_ `SYMS_ElfDynTag_PREINIT_ARRAYSZ = 33` (scope `__anonc3d9a30a0d03`)
- L318 _enumerator_ `SYMS_ElfDynTag_SYMTAB_SHNDX = 34` (scope `__anonc3d9a30a0d03`)
- L319 _enumerator_ `SYMS_ElfDynTag_LOOS = 0x6000000D` (scope `__anonc3d9a30a0d03`)
- L320 _enumerator_ `SYMS_ElfDynTag_HIOS = 0x6ffff000` (scope `__anonc3d9a30a0d03`)
- L321 _enumerator_ `SYMS_ElfDynTag_VALRNGLO = 0x6ffffd00` (scope `__anonc3d9a30a0d03`)
- L322 _enumerator_ `SYMS_ElfDynTag_GNU_PRELINKED = 0x6ffffdf5` (scope `__anonc3d9a30a0d03`)
- L323 _enumerator_ `SYMS_ElfDynTag_GNU_CONFLICTSZ = 0x6ffffdf6` (scope `__anonc3d9a30a0d03`)
- L324 _enumerator_ `SYMS_ElfDynTag_GNU_LIBLISTSZ = 0x6ffffdf7` (scope `__anonc3d9a30a0d03`)
- L325 _enumerator_ `SYMS_ElfDynTag_CHECKSUM = 0x6ffffdf8` (scope `__anonc3d9a30a0d03`)
- L326 _enumerator_ `SYMS_ElfDynTag_PLTPADSZ = 0x6ffffdf9` (scope `__anonc3d9a30a0d03`)
- L327 _enumerator_ `SYMS_ElfDynTag_MOVEENT = 0x6ffffdfa` (scope `__anonc3d9a30a0d03`)
- L328 _enumerator_ `SYMS_ElfDynTag_MOVESZ = 0x6ffffdfb` (scope `__anonc3d9a30a0d03`)
- L329 _enumerator_ `SYMS_ElfDynTag_FEATURE = 0x6ffffdfc` (scope `__anonc3d9a30a0d03`)
- L330 _enumerator_ `SYMS_ElfDynTag_POSFLAG_1 = 0x6ffffdfd` (scope `__anonc3d9a30a0d03`)
- L331 _enumerator_ `SYMS_ElfDynTag_SYMINSZ = 0x6ffffdfe` (scope `__anonc3d9a30a0d03`)
- L332 _enumerator_ `SYMS_ElfDynTag_SYMINENT = 0x6ffffdff` (scope `__anonc3d9a30a0d03`)
- L333 _enumerator_ `SYMS_ElfDynTag_VALRNGHI = SYMS_ElfDynTag_SYMINENT` (scope `__anonc3d9a30a0d03`)
- L334 _enumerator_ `SYMS_ElfDynTag_ADDRRNGLO = 0x6ffffe00` (scope `__anonc3d9a30a0d03`)
- L335 _enumerator_ `SYMS_ElfDynTag_GNU_HASH = 0x6ffffef5` (scope `__anonc3d9a30a0d03`)
- L336 _enumerator_ `SYMS_ElfDynTag_TLSDESC_PLT = 0x6ffffef6` (scope `__anonc3d9a30a0d03`)
- L337 _enumerator_ `SYMS_ElfDynTag_TLSDESC_GOT = 0x6ffffef7` (scope `__anonc3d9a30a0d03`)
- L338 _enumerator_ `SYMS_ElfDynTag_GNU_CONFLICT = 0x6ffffef8` (scope `__anonc3d9a30a0d03`)
- L339 _enumerator_ `SYMS_ElfDynTag_GNU_LIBLIST = 0x6ffffef9` (scope `__anonc3d9a30a0d03`)
- L340 _enumerator_ `SYMS_ElfDynTag_CONFIG = 0x6ffffefa` (scope `__anonc3d9a30a0d03`)
- L341 _enumerator_ `SYMS_ElfDynTag_DEPAUDIT = 0x6ffffefb` (scope `__anonc3d9a30a0d03`)
- L342 _enumerator_ `SYMS_ElfDynTag_AUDIT = 0x6ffffefc` (scope `__anonc3d9a30a0d03`)
- L343 _enumerator_ `SYMS_ElfDynTag_PLTPAD = 0x6ffffefd` (scope `__anonc3d9a30a0d03`)
- L344 _enumerator_ `SYMS_ElfDynTag_MOVETAB = 0x6ffffefe` (scope `__anonc3d9a30a0d03`)
- L345 _enumerator_ `SYMS_ElfDynTag_SYMINFO = 0x6ffffeff` (scope `__anonc3d9a30a0d03`)
- L346 _enumerator_ `SYMS_ElfDynTag_ADDRRNGHI = SYMS_ElfDynTag_SYMINFO` (scope `__anonc3d9a30a0d03`)
- L347 _enumerator_ `SYMS_ElfDynTag_RELACOUNT = 0x6ffffff9` (scope `__anonc3d9a30a0d03`)
- L348 _enumerator_ `SYMS_ElfDynTag_RELCOUNT = 0x6ffffffa` (scope `__anonc3d9a30a0d03`)
- L349 _enumerator_ `SYMS_ElfDynTag_FLAGS_1 = 0x6ffffffb` (scope `__anonc3d9a30a0d03`)
- L350 _enumerator_ `SYMS_ElfDynTag_VERDEF = 0x6ffffffc` (scope `__anonc3d9a30a0d03`)
- L351 _enumerator_ `SYMS_ElfDynTag_VERDEFNUM = 0x6ffffffd` (scope `__anonc3d9a30a0d03`)
- L352 _enumerator_ `SYMS_ElfDynTag_VERNEED = 0x6ffffffe` (scope `__anonc3d9a30a0d03`)
- L353 _enumerator_ `SYMS_ElfDynTag_VERNEEDNUM = 0x6fffffff` (scope `__anonc3d9a30a0d03`)
- L354 _enumerator_ `SYMS_ElfDynTag_VERSYM = 0x6ffffff0` (scope `__anonc3d9a30a0d03`)
- L356 _enumerator_ `SYMS_ElfDynTag_LOPROC = 0x70000000` (scope `__anonc3d9a30a0d03`) — gdb: These section tags are used on Solaris.  We support them everywhere, and hope they do not conflict.
- L357 _enumerator_ `SYMS_ElfDynTag_AUXILIARY = 0x7ffffffd` (scope `__anonc3d9a30a0d03`)
- L358 _enumerator_ `SYMS_ElfDynTag_USED = 0x7ffffffe` (scope `__anonc3d9a30a0d03`)
- L359 _enumerator_ `SYMS_ElfDynTag_FILTER = 0x7fffffff` (scope `__anonc3d9a30a0d03`)
- L360 _enumerator_ `SYMS_ElfDynTag_HIPROC = SYMS_ElfDynTag_FILTER` (scope `__anonc3d9a30a0d03`)
- L361 _enumerator_ `SYMS_ElfDynTag_COUNT = 75` (scope `__anonc3d9a30a0d03`)
- L363 _typedef_ `typedef SYMS_U32 SYMS_ElfDynFlag;`
- L365 _enumerator_ `SYMS_ElfDynFlag_ORIGIN = (1 << 0)` (scope `__anonc3d9a30a0e03`)
- L366 _enumerator_ `SYMS_ElfDynFlag_SYMBOLIC = (1 << 1)` (scope `__anonc3d9a30a0e03`)
- L367 _enumerator_ `SYMS_ElfDynFlag_TEXTREL = (1 << 2)` (scope `__anonc3d9a30a0e03`)
- L368 _enumerator_ `SYMS_ElfDynFlag_BIND_NOW = (1 << 3)` (scope `__anonc3d9a30a0e03`)
- L369 _enumerator_ `SYMS_ElfDynFlag_STATIC_TLS = (1 << 4)` (scope `__anonc3d9a30a0e03`)
- L371 _typedef_ `typedef SYMS_U32 SYMS_ElfDynFeatureFlag;`
- L373 _enumerator_ `SYMS_ElfDynFeatureFlag_PARINIT = (1 << 0)` (scope `__anonc3d9a30a0f03`)
- L374 _enumerator_ `SYMS_ElfDynFeatureFlag_CONFEXP = (1 << 1)` (scope `__anonc3d9a30a0f03`)
- L376 _typedef_ `typedef SYMS_U8 SYMS_ElfSymBind;`
- L379 _enumerator_ `SYMS_ElfSymBind_LOCAL = 0` (scope `__anonc3d9a30a1003`) — the same name may exists in multiple files without interfering with each other.
- L381 _enumerator_ `SYMS_ElfSymBind_GLOBAL = 1` (scope `__anonc3d9a30a1003`) — Visible to all objects that are linked together.
- L383 _enumerator_ `SYMS_ElfSymBind_WEAK = 2` (scope `__anonc3d9a30a1003`) — If there is a global symbol with identical name linker doesn't issue an error.
- L384 _enumerator_ `SYMS_ElfSymBind_LOPROC = 13` (scope `__anonc3d9a30a1003`)
- L385 _enumerator_ `SYMS_ElfSymBind_HIPROC = 15` (scope `__anonc3d9a30a1003`)
- L386 _enumerator_ `SYMS_ElfSymBind_COUNT = 5` (scope `__anonc3d9a30a1003`)
- L388 _typedef_ `typedef SYMS_U8 SYMS_ElfSymType;`
- L390 _enumerator_ `SYMS_ElfSymType_NOTYPE = 0` (scope `__anonc3d9a30a1103`)
- L392 _enumerator_ `SYMS_ElfSymType_OBJECT = 1` (scope `__anonc3d9a30a1103`) — Type is not specified.
- L394 _enumerator_ `SYMS_ElfSymType_FUNC = 2` (scope `__anonc3d9a30a1103`) — Symbol is associated with data object, such as a variable, an array, etc.
- L396 _enumerator_ `SYMS_ElfSymType_SECTION = 3` (scope `__anonc3d9a30a1103`) — Symbol is associated with a function.
- L398 _enumerator_ `SYMS_ElfSymType_FILE = 4` (scope `__anonc3d9a30a1103`) — Symbol is used to relocate sections and normally have LOCAL binding.
- L400 _enumerator_ `SYMS_ElfSymType_COMMON = 5` (scope `__anonc3d9a30a1103`) — Gives name of the source file associated with object.
- L401 _enumerator_ `SYMS_ElfSymType_TLS = 6` (scope `__anonc3d9a30a1103`)
- L402 _enumerator_ `SYMS_ElfSymType_LOPROC = 13` (scope `__anonc3d9a30a1103`)
- L403 _enumerator_ `SYMS_ElfSymType_HIPROC = 15` (scope `__anonc3d9a30a1103`)
- L404 _enumerator_ `SYMS_ElfSymType_COUNT = 9` (scope `__anonc3d9a30a1103`)
- L406 _typedef_ `typedef SYMS_U8 SYMS_ElfSymVisibility;`
- L408 _enumerator_ `SYMS_ElfSymVisibility_DEFAULT = 0` (scope `__anonc3d9a30a1203`)
- L409 _enumerator_ `SYMS_ElfSymVisibility_INTERNAL = 1` (scope `__anonc3d9a30a1203`)
- L410 _enumerator_ `SYMS_ElfSymVisibility_HIDDEN = 2` (scope `__anonc3d9a30a1203`)
- L411 _enumerator_ `SYMS_ElfSymVisibility_PROTECTED = 3` (scope `__anonc3d9a30a1203`)
- L412 _enumerator_ `SYMS_ElfSymVisibility_COUNT = 4` (scope `__anonc3d9a30a1203`)
- L414 _typedef_ `typedef SYMS_U32 SYMS_ElfRelocI386;`
- L416 _enumerator_ `SYMS_ElfRelocI386_NONE = 0` (scope `__anonc3d9a30a1303`)
- L417 _enumerator_ `SYMS_ElfRelocI386_32 = 1` (scope `__anonc3d9a30a1303`)
- L418 _enumerator_ `SYMS_ElfRelocI386_PC32 = 2` (scope `__anonc3d9a30a1303`)
- L419 _enumerator_ `SYMS_ElfRelocI386_GOT32 = 3` (scope `__anonc3d9a30a1303`)
- L420 _enumerator_ `SYMS_ElfRelocI386_PLT32 = 4` (scope `__anonc3d9a30a1303`)
- L421 _enumerator_ `SYMS_ElfRelocI386_COPY = 5` (scope `__anonc3d9a30a1303`)
- L422 _enumerator_ `SYMS_ElfRelocI386_GLOB_DAT = 6` (scope `__anonc3d9a30a1303`)
- L423 _enumerator_ `SYMS_ElfRelocI386_JUMP_SLOT = 7` (scope `__anonc3d9a30a1303`)
- L424 _enumerator_ `SYMS_ElfRelocI386_RELATIVE = 8` (scope `__anonc3d9a30a1303`)
- L425 _enumerator_ `SYMS_ElfRelocI386_GOTOFF = 9` (scope `__anonc3d9a30a1303`)
- L426 _enumerator_ `SYMS_ElfRelocI386_GOTPC = 10` (scope `__anonc3d9a30a1303`)
- L427 _enumerator_ `SYMS_ElfRelocI386_32PLT = 11` (scope `__anonc3d9a30a1303`)
- L428 _enumerator_ `SYMS_ElfRelocI386_TLS_TPOFF = 14` (scope `__anonc3d9a30a1303`)
- L429 _enumerator_ `SYMS_ElfRelocI386_TLS_IE = 15` (scope `__anonc3d9a30a1303`)
- L430 _enumerator_ `SYMS_ElfRelocI386_TLS_GOTIE = 16` (scope `__anonc3d9a30a1303`)
- L431 _enumerator_ `SYMS_ElfRelocI386_TLS_LE = 17` (scope `__anonc3d9a30a1303`)
- L432 _enumerator_ `SYMS_ElfRelocI386_TLS_GD = 18` (scope `__anonc3d9a30a1303`)
- L433 _enumerator_ `SYMS_ElfRelocI386_TLS_LDM = 19` (scope `__anonc3d9a30a1303`)
- L434 _enumerator_ `SYMS_ElfRelocI386_16 = 20` (scope `__anonc3d9a30a1303`)
- L435 _enumerator_ `SYMS_ElfRelocI386_PC16 = 21` (scope `__anonc3d9a30a1303`)
- L436 _enumerator_ `SYMS_ElfRelocI386_8 = 22` (scope `__anonc3d9a30a1303`)
- L437 _enumerator_ `SYMS_ElfRelocI386_PC8 = 23` (scope `__anonc3d9a30a1303`)
- L438 _enumerator_ `SYMS_ElfRelocI386_TLS_GD_32 = 24` (scope `__anonc3d9a30a1303`)
- L439 _enumerator_ `SYMS_ElfRelocI386_TLS_GD_PUSH = 25` (scope `__anonc3d9a30a1303`)
- L440 _enumerator_ `SYMS_ElfRelocI386_TLS_GD_CALL = 26` (scope `__anonc3d9a30a1303`)
- L441 _enumerator_ `SYMS_ElfRelocI386_TLS_GD_POP = 27` (scope `__anonc3d9a30a1303`)
- L442 _enumerator_ `SYMS_ElfRelocI386_TLS_LDM_32 = 28` (scope `__anonc3d9a30a1303`)
- L443 _enumerator_ `SYMS_ElfRelocI386_TLS_LDM_PUSH = 29` (scope `__anonc3d9a30a1303`)
- L444 _enumerator_ `SYMS_ElfRelocI386_TLS_LDM_CALL = 30` (scope `__anonc3d9a30a1303`)
- L445 _enumerator_ `SYMS_ElfRelocI386_TLS_LDM_POP = 31` (scope `__anonc3d9a30a1303`)
- L446 _enumerator_ `SYMS_ElfRelocI386_TLS_LDO_32 = 32` (scope `__anonc3d9a30a1303`)
- L447 _enumerator_ `SYMS_ElfRelocI386_TLS_IE_32 = 33` (scope `__anonc3d9a30a1303`)
- L448 _enumerator_ `SYMS_ElfRelocI386_TLS_LE_32 = 34` (scope `__anonc3d9a30a1303`)
- L449 _enumerator_ `SYMS_ElfRelocI386_TLS_DTPMOD32 = 35` (scope `__anonc3d9a30a1303`)
- L450 _enumerator_ `SYMS_ElfRelocI386_TLS_DTPOFF32 = 36` (scope `__anonc3d9a30a1303`)
- L451 _enumerator_ `SYMS_ElfRelocI386_TLS_TPOFF32 = 37` (scope `__anonc3d9a30a1303`)
- L453 _enumerator_ `SYMS_ElfRelocI386_TLS_GOTDESC = 39` (scope `__anonc3d9a30a1303`) — 38 is not taken
- L454 _enumerator_ `SYMS_ElfRelocI386_TLS_DESC_CALL = 40` (scope `__anonc3d9a30a1303`)
- L455 _enumerator_ `SYMS_ElfRelocI386_TLS_DESC = 41` (scope `__anonc3d9a30a1303`)
- L456 _enumerator_ `SYMS_ElfRelocI386_IRELATIVE = 42` (scope `__anonc3d9a30a1303`)
- L457 _enumerator_ `SYMS_ElfRelocI386_GOTX32X = 43` (scope `__anonc3d9a30a1303`)
- L458 _enumerator_ `SYMS_ElfRelocI386_USED_BY_INTEL_200 = 200` (scope `__anonc3d9a30a1303`)
- L459 _enumerator_ `SYMS_ElfRelocI386_GNU_VTINHERIT = 250` (scope `__anonc3d9a30a1303`)
- L460 _enumerator_ `SYMS_ElfRelocI386_GNU_VTENTRY = 251` (scope `__anonc3d9a30a1303`)
- L461 _enumerator_ `SYMS_ElfRelocI386_COUNT = 44` (scope `__anonc3d9a30a1303`)
- L463 _typedef_ `typedef SYMS_U32 SYMS_ElfRelocX8664;`
- L465 _enumerator_ `SYMS_ElfRelocX8664_NONE = 0` (scope `__anonc3d9a30a1403`)
- L466 _enumerator_ `SYMS_ElfRelocX8664_64 = 1` (scope `__anonc3d9a30a1403`)
- L467 _enumerator_ `SYMS_ElfRelocX8664_PC32 = 2` (scope `__anonc3d9a30a1403`)
- L468 _enumerator_ `SYMS_ElfRelocX8664_GOT32 = 3` (scope `__anonc3d9a30a1403`)
- L469 _enumerator_ `SYMS_ElfRelocX8664_PLT32 = 4` (scope `__anonc3d9a30a1403`)
- L470 _enumerator_ `SYMS_ElfRelocX8664_COPY = 5` (scope `__anonc3d9a30a1403`)
- L471 _enumerator_ `SYMS_ElfRelocX8664_GLOB_DAT = 6` (scope `__anonc3d9a30a1403`)
- L472 _enumerator_ `SYMS_ElfRelocX8664_JUMP_SLOT = 7` (scope `__anonc3d9a30a1403`)
- L473 _enumerator_ `SYMS_ElfRelocX8664_RELATIVE = 8` (scope `__anonc3d9a30a1403`)
- L474 _enumerator_ `SYMS_ElfRelocX8664_GOTPCREL = 9` (scope `__anonc3d9a30a1403`)
- L475 _enumerator_ `SYMS_ElfRelocX8664_32 = 10` (scope `__anonc3d9a30a1403`)
- L476 _enumerator_ `SYMS_ElfRelocX8664_32S = 11` (scope `__anonc3d9a30a1403`)
- L477 _enumerator_ `SYMS_ElfRelocX8664_16 = 12` (scope `__anonc3d9a30a1403`)
- L478 _enumerator_ `SYMS_ElfRelocX8664_PC16 = 13` (scope `__anonc3d9a30a1403`)
- L479 _enumerator_ `SYMS_ElfRelocX8664_8 = 14` (scope `__anonc3d9a30a1403`)
- L480 _enumerator_ `SYMS_ElfRelocX8664_PC8 = 15` (scope `__anonc3d9a30a1403`)
- L481 _enumerator_ `SYMS_ElfRelocX8664_DTPMOD64 = 16` (scope `__anonc3d9a30a1403`)
- L482 _enumerator_ `SYMS_ElfRelocX8664_DTPOFF64 = 17` (scope `__anonc3d9a30a1403`)
- L483 _enumerator_ `SYMS_ElfRelocX8664_TPOFF64 = 18` (scope `__anonc3d9a30a1403`)
- L484 _enumerator_ `SYMS_ElfRelocX8664_TLSGD = 19` (scope `__anonc3d9a30a1403`)
- L485 _enumerator_ `SYMS_ElfRelocX8664_TLSLD = 20` (scope `__anonc3d9a30a1403`)
- L486 _enumerator_ `SYMS_ElfRelocX8664_DTPOFF32 = 21` (scope `__anonc3d9a30a1403`)
- L487 _enumerator_ `SYMS_ElfRelocX8664_GOTTPOFF = 22` (scope `__anonc3d9a30a1403`)
- L488 _enumerator_ `SYMS_ElfRelocX8664_TPOFF32 = 23` (scope `__anonc3d9a30a1403`)
- L489 _enumerator_ `SYMS_ElfRelocX8664_PC64 = 24` (scope `__anonc3d9a30a1403`)
- L490 _enumerator_ `SYMS_ElfRelocX8664_GOTOFF64 = 25` (scope `__anonc3d9a30a1403`)
- L491 _enumerator_ `SYMS_ElfRelocX8664_GOTPC32 = 26` (scope `__anonc3d9a30a1403`)
- L492 _enumerator_ `SYMS_ElfRelocX8664_GOT64 = 27` (scope `__anonc3d9a30a1403`)
- L493 _enumerator_ `SYMS_ElfRelocX8664_GOTPCREL64 = 28` (scope `__anonc3d9a30a1403`)
- L494 _enumerator_ `SYMS_ElfRelocX8664_GOTPC64 = 29` (scope `__anonc3d9a30a1403`)
- L495 _enumerator_ `SYMS_ElfRelocX8664_GOTPLT64 = 30` (scope `__anonc3d9a30a1403`)
- L496 _enumerator_ `SYMS_ElfRelocX8664_PLTOFF64 = 31` (scope `__anonc3d9a30a1403`)
- L497 _enumerator_ `SYMS_ElfRelocX8664_SIZE32 = 32` (scope `__anonc3d9a30a1403`)
- L498 _enumerator_ `SYMS_ElfRelocX8664_SIZE64 = 33` (scope `__anonc3d9a30a1403`)
- L499 _enumerator_ `SYMS_ElfRelocX8664_GOTPC32_TLSDESC = 34` (scope `__anonc3d9a30a1403`)
- L500 _enumerator_ `SYMS_ElfRelocX8664_TLSDESC_CALL = 35` (scope `__anonc3d9a30a1403`)
- L501 _enumerator_ `SYMS_ElfRelocX8664_TLSDESC = 36` (scope `__anonc3d9a30a1403`)
- L502 _enumerator_ `SYMS_ElfRelocX8664_IRELATIVE = 37` (scope `__anonc3d9a30a1403`)
- L503 _enumerator_ `SYMS_ElfRelocX8664_RELATIVE64 = 38` (scope `__anonc3d9a30a1403`)
- L504 _enumerator_ `SYMS_ElfRelocX8664_PC32_BND = 39` (scope `__anonc3d9a30a1403`)
- L505 _enumerator_ `SYMS_ElfRelocX8664_PLT32_BND = 40` (scope `__anonc3d9a30a1403`)
- L506 _enumerator_ `SYMS_ElfRelocX8664_GOTPCRELX = 41` (scope `__anonc3d9a30a1403`)
- L507 _enumerator_ `SYMS_ElfRelocX8664_REX_GOTPCRELX = 42` (scope `__anonc3d9a30a1403`)
- L508 _enumerator_ `SYMS_ElfRelocX8664_GNU_VTINHERIT = 250` (scope `__anonc3d9a30a1403`)
- L509 _enumerator_ `SYMS_ElfRelocX8664_GNU_VTENTRY = 251` (scope `__anonc3d9a30a1403`)
- L510 _enumerator_ `SYMS_ElfRelocX8664_COUNT = 45` (scope `__anonc3d9a30a1403`)
- L512 _typedef_ `typedef SYMS_U32 SYMS_ElfExternalVerFlag;`
- L514 _enumerator_ `SYMS_ElfExternalVerFlag_BASE = (1 << 0)` (scope `__anonc3d9a30a1503`)
- L515 _enumerator_ `SYMS_ElfExternalVerFlag_WEAK = (1 << 1)` (scope `__anonc3d9a30a1503`)
- L516 _enumerator_ `SYMS_ElfExternalVerFlag_INFO = (1 << 2)` (scope `__anonc3d9a30a1503`)
- L518 _typedef_ `typedef SYMS_U32 SYMS_ElfNoteType;`
- L520 _enumerator_ `SYMS_ElfNoteType_GNU_ABI = 1` (scope `__anonc3d9a30a1603`)
- L521 _enumerator_ `SYMS_ElfNoteType_GNU_HWCAP = 2` (scope `__anonc3d9a30a1603`)
- L522 _enumerator_ `SYMS_ElfNoteType_GNU_BUILD_ID = 3` (scope `__anonc3d9a30a1603`)
- L523 _enumerator_ `SYMS_ElfNoteType_GNU_GOLD_VERSION = 4` (scope `__anonc3d9a30a1603`)
- L524 _enumerator_ `SYMS_ElfNoteType_GNU_PROPERTY_TYPE_0 = 5` (scope `__anonc3d9a30a1603`)
- L525 _enumerator_ `SYMS_ElfNoteType_COUNT = 5` (scope `__anonc3d9a30a1603`)
- L527 _typedef_ `typedef SYMS_U32 SYMS_ElfGnuABITag;`
- L529 _enumerator_ `SYMS_ElfGnuABITag_LINUX = 0` (scope `__anonc3d9a30a1703`)
- L530 _enumerator_ `SYMS_ElfGnuABITag_HURD = 1` (scope `__anonc3d9a30a1703`)
- L531 _enumerator_ `SYMS_ElfGnuABITag_SOLARIS = 2` (scope `__anonc3d9a30a1703`)
- L532 _enumerator_ `SYMS_ElfGnuABITag_FREEBSD = 3` (scope `__anonc3d9a30a1703`)
- L533 _enumerator_ `SYMS_ElfGnuABITag_NETBSD = 4` (scope `__anonc3d9a30a1703`)
- L534 _enumerator_ `SYMS_ElfGnuABITag_SYLLABLE = 5` (scope `__anonc3d9a30a1703`)
- L535 _enumerator_ `SYMS_ElfGnuABITag_NACL = 6` (scope `__anonc3d9a30a1703`)
- L536 _enumerator_ `SYMS_ElfGnuABITag_COUNT = 7` (scope `__anonc3d9a30a1703`)
- L538 _typedef_ `typedef SYMS_S32 SYMS_ElfGnuProperty;`
- L540 _enumerator_ `SYMS_ElfGnuProperty_LOPROC = 0xc0000000` (scope `__anonc3d9a30a1803`)
- L542 _enumerator_ `SYMS_ElfGnuProperty_HIPROC = 0xdfffffff` (scope `__anonc3d9a30a1803`) — processor-specific range
- L543 _enumerator_ `SYMS_ElfGnuProperty_LOUSER = 0xe0000000` (scope `__anonc3d9a30a1803`)
- L545 _enumerator_ `SYMS_ElfGnuProperty_HIUSER = 0xffffffff` (scope `__anonc3d9a30a1803`) — application-specific range
- L546 _enumerator_ `SYMS_ElfGnuProperty_STACK_SIZE = 1` (scope `__anonc3d9a30a1803`)
- L547 _enumerator_ `SYMS_ElfGnuProperty_NO_COPY_ON_PROTECTED = 2` (scope `__anonc3d9a30a1803`)
- L548 _enumerator_ `SYMS_ElfGnuProperty_COUNT = 6` (scope `__anonc3d9a30a1803`)
- L550 _typedef_ `typedef SYMS_U32 SYMS_ElfGnuPropertyX86Isa1;`
- L552 _enumerator_ `SYMS_ElfGnuPropertyX86Isa1_BASE_LINE = (1 << 0)` (scope `__anonc3d9a30a1903`)
- L553 _enumerator_ `SYMS_ElfGnuPropertyX86Isa1_V2 = (1 << 1)` (scope `__anonc3d9a30a1903`)
- L554 _enumerator_ `SYMS_ElfGnuPropertyX86Isa1_V3 = (1 << 2)` (scope `__anonc3d9a30a1903`)
- L555 _enumerator_ `SYMS_ElfGnuPropertyX86Isa1_V4 = (1 << 3)` (scope `__anonc3d9a30a1903`)
- L557 _typedef_ `typedef SYMS_U32 SYMS_ElfGnuPropertyX86Compat1Isa1;`
- L559 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_486 = (1 << 0)` (scope `__anonc3d9a30a1a03`)
- L560 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_586 = (1 << 1)` (scope `__anonc3d9a30a1a03`)
- L561 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_686 = (1 << 2)` (scope `__anonc3d9a30a1a03`)
- L562 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_SSE = (1 << 3)` (scope `__anonc3d9a30a1a03`)
- L563 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_SSE2 = (1 << 4)` (scope `__anonc3d9a30a1a03`)
- L564 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_SSE3 = (1 << 5)` (scope `__anonc3d9a30a1a03`)
- L565 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_SSSE3 = (1 << 6)` (scope `__anonc3d9a30a1a03`)
- L566 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_SSE4_1 = (1 << 7)` (scope `__anonc3d9a30a1a03`)
- L567 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_SSE4_2 = (1 << 8)` (scope `__anonc3d9a30a1a03`)
- L568 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX = (1 << 9)` (scope `__anonc3d9a30a1a03`)
- L569 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX2 = (1 << 10)` (scope `__anonc3d9a30a1a03`)
- L570 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX512F = (1 << 11)` (scope `__anonc3d9a30a1a03`)
- L571 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX512ER = (1 << 12)` (scope `__anonc3d9a30a1a03`)
- L572 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX512PF = (1 << 13)` (scope `__anonc3d9a30a1a03`)
- L573 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX512VL = (1 << 14)` (scope `__anonc3d9a30a1a03`)
- L574 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX512DQ = (1 << 15)` (scope `__anonc3d9a30a1a03`)
- L575 _enumerator_ `SYMS_ElfGnuPropertyX86Compat1Isa1_AVX512BW = (1 << 16)` (scope `__anonc3d9a30a1a03`)
- L577 _typedef_ `typedef SYMS_U32 SYMS_ElfGnuPropertyX86Compat2Isa1;`
- L579 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_CMOVE = (1 << 0)` (scope `__anonc3d9a30a1b03`)
- L580 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_SSE = (1 << 1)` (scope `__anonc3d9a30a1b03`)
- L581 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_SSE2 = (1 << 2)` (scope `__anonc3d9a30a1b03`)
- L582 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_SSE3 = (1 << 3)` (scope `__anonc3d9a30a1b03`)
- L583 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_SSE4_1 = (1 << 4)` (scope `__anonc3d9a30a1b03`)
- L584 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_SSE4_2 = (1 << 5)` (scope `__anonc3d9a30a1b03`)
- L585 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX = (1 << 6)` (scope `__anonc3d9a30a1b03`)
- L586 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX2 = (1 << 7)` (scope `__anonc3d9a30a1b03`)
- L587 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_FMA = (1 << 8)` (scope `__anonc3d9a30a1b03`)
- L588 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512F = (1 << 9)` (scope `__anonc3d9a30a1b03`)
- L589 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512CD = (1 << 10)` (scope `__anonc3d9a30a1b03`)
- L590 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512ER = (1 << 11)` (scope `__anonc3d9a30a1b03`)
- L591 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512PF = (1 << 12)` (scope `__anonc3d9a30a1b03`)
- L592 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512VL = (1 << 13)` (scope `__anonc3d9a30a1b03`)
- L593 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512DQ = (1 << 14)` (scope `__anonc3d9a30a1b03`)
- L594 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512BW = (1 << 15)` (scope `__anonc3d9a30a1b03`)
- L595 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_4FMAPS = (1 << 16)` (scope `__anonc3d9a30a1b03`)
- L596 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_4VNNIW = (1 << 17)` (scope `__anonc3d9a30a1b03`)
- L597 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_BITALG = (1 << 18)` (scope `__anonc3d9a30a1b03`)
- L598 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_IFMA = (1 << 19)` (scope `__anonc3d9a30a1b03`)
- L599 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_VBMI = (1 << 20)` (scope `__anonc3d9a30a1b03`)
- L600 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_VBMI2 = (1 << 21)` (scope `__anonc3d9a30a1b03`)
- L601 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_VNNI = (1 << 22)` (scope `__anonc3d9a30a1b03`)
- L602 _enumerator_ `SYMS_ElfGnuPropertyX86Compat2Isa1_AVX512_BF16 = (1 << 23)` (scope `__anonc3d9a30a1b03`)
- L604 _typedef_ `typedef SYMS_S32 SYMS_ElfGnuPropertyX86;`
- L606 _enumerator_ `SYMS_ElfGnuPropertyX86_FEATURE_1_AND = 0xc0000002` (scope `__anonc3d9a30a1c03`)
- L607 _enumerator_ `SYMS_ElfGnuPropertyX86_FEATURE_2_USED = 0xc0010001` (scope `__anonc3d9a30a1c03`)
- L608 _enumerator_ `SYMS_ElfGnuPropertyX86_ISA_1_NEEDED = 0xc0008002` (scope `__anonc3d9a30a1c03`)
- L609 _enumerator_ `SYMS_ElfGnuPropertyX86_ISA_2_NEEDED = 0xc0008001` (scope `__anonc3d9a30a1c03`)
- L610 _enumerator_ `SYMS_ElfGnuPropertyX86_ISA_1_USED = 0xc0010002` (scope `__anonc3d9a30a1c03`)
- L611 _enumerator_ `SYMS_ElfGnuPropertyX86_COMPAT_ISA_1_USED = 0xc0000000` (scope `__anonc3d9a30a1c03`)
- L612 _enumerator_ `SYMS_ElfGnuPropertyX86_COMPAT_ISA_1_NEEDED = 0xc0000001` (scope `__anonc3d9a30a1c03`)
- L613 _enumerator_ `SYMS_ElfGnuPropertyX86_UINT32_AND_LO = SYMS_ElfGnuPropertyX86_FEATURE_1_AND` (scope `__anonc3d9a30a1c03`)
- L614 _enumerator_ `SYMS_ElfGnuPropertyX86_UINT32_AND_HI = 0xc0007fff` (scope `__anonc3d9a30a1c03`)
- L615 _enumerator_ `SYMS_ElfGnuPropertyX86_UINT32_OR_LO = 0xc0008000` (scope `__anonc3d9a30a1c03`)
- L616 _enumerator_ `SYMS_ElfGnuPropertyX86_UINT32_OR_HI = 0xc000ffff` (scope `__anonc3d9a30a1c03`)
- L617 _enumerator_ `SYMS_ElfGnuPropertyX86_UINT32_OR_AND_LO = 0xc0010000` (scope `__anonc3d9a30a1c03`)
- L618 _enumerator_ `SYMS_ElfGnuPropertyX86_UINT32_OR_AND_HI = 0xc0017fff` (scope `__anonc3d9a30a1c03`)
- L619 _enumerator_ `SYMS_ElfGnuPropertyX86_COUNT = 13` (scope `__anonc3d9a30a1c03`)
- L621 _typedef_ `typedef SYMS_U32 SYMS_ElfGnuPropertyX86Feature1;`
- L623 _enumerator_ `SYMS_ElfGnuPropertyX86Feature1_IBT = (1 << 0)` (scope `__anonc3d9a30a1d03`)
- L624 _enumerator_ `SYMS_ElfGnuPropertyX86Feature1_SHSTK = (1 << 1)` (scope `__anonc3d9a30a1d03`)
- L625 _enumerator_ `SYMS_ElfGnuPropertyX86Feature1_LAM_U48 = (1 << 2)` (scope `__anonc3d9a30a1d03`)
- L626 _enumerator_ `SYMS_ElfGnuPropertyX86Feature1_LAM_U57 = (1 << 3)` (scope `__anonc3d9a30a1d03`)
- L628 _typedef_ `typedef SYMS_U32 SYMS_ElfGnuPropertyX86Feature2;`
- L630 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_X86 = (1 << 0)` (scope `__anonc3d9a30a1e03`)
- L631 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_X87 = (1 << 1)` (scope `__anonc3d9a30a1e03`)
- L632 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_MMX = (1 << 2)` (scope `__anonc3d9a30a1e03`)
- L633 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_XMM = (1 << 3)` (scope `__anonc3d9a30a1e03`)
- L634 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_YMM = (1 << 4)` (scope `__anonc3d9a30a1e03`)
- L635 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_ZMM = (1 << 5)` (scope `__anonc3d9a30a1e03`)
- L636 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_FXSR = (1 << 6)` (scope `__anonc3d9a30a1e03`)
- L637 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_XSAVE = (1 << 7)` (scope `__anonc3d9a30a1e03`)
- L638 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_XSAVEOPT = (1 << 8)` (scope `__anonc3d9a30a1e03`)
- L639 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_XSAVEC = (1 << 9)` (scope `__anonc3d9a30a1e03`)
- L640 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_TMM = (1 << 10)` (scope `__anonc3d9a30a1e03`)
- L641 _enumerator_ `SYMS_ElfGnuPropertyX86Feature2_MASK = (1 << 11)` (scope `__anonc3d9a30a1e03`)
- L646 _prototype_ `SYMS_Arch syms_arch_from_elf_machine_type(SYMS_ElfMachineKind v);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_eval.h` (Other)


#### enum `(anonymous)`  
`typedef enum`  
_L6-51_

#### enum `(anonymous)`  
`enum`  
_L53-60_

#### enum `(anonymous)`  
`typedef enum`  
_L62-69_

#### enum `(anonymous)`  
`typedef enum`  
_L71-78_

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_EVAL_H`
- L7 _enumerator_ `SYMS_EvalOp_Stop` (scope `__anon3fc13c1b0103`)
- L8 _enumerator_ `SYMS_EvalOp_Cond` (scope `__anon3fc13c1b0103`)
- L9 _enumerator_ `SYMS_EvalOp_Skip` (scope `__anon3fc13c1b0103`)
- L10 _enumerator_ `SYMS_EvalOp_MemRead` (scope `__anon3fc13c1b0103`)
- L11 _enumerator_ `SYMS_EvalOp_RegRead` (scope `__anon3fc13c1b0103`)
- L12 _enumerator_ `SYMS_EvalOp_RegReadDyn` (scope `__anon3fc13c1b0103`)
- L13 _enumerator_ `SYMS_EvalOp_FrameOff` (scope `__anon3fc13c1b0103`)
- L14 _enumerator_ `SYMS_EvalOp_ModuleOff` (scope `__anon3fc13c1b0103`)
- L15 _enumerator_ `SYMS_EvalOp_TLSOff` (scope `__anon3fc13c1b0103`)
- L16 _enumerator_ `SYMS_EvalOp_ObjectOff` (scope `__anon3fc13c1b0103`)
- L17 _enumerator_ `SYMS_EvalOp_CFA` (scope `__anon3fc13c1b0103`)
- L18 _enumerator_ `SYMS_EvalOp_ConstU8` (scope `__anon3fc13c1b0103`)
- L19 _enumerator_ `SYMS_EvalOp_ConstU16` (scope `__anon3fc13c1b0103`)
- L20 _enumerator_ `SYMS_EvalOp_ConstU32` (scope `__anon3fc13c1b0103`)
- L21 _enumerator_ `SYMS_EvalOp_ConstU64` (scope `__anon3fc13c1b0103`)
- L22 _enumerator_ `SYMS_EvalOp_Abs` (scope `__anon3fc13c1b0103`)
- L23 _enumerator_ `SYMS_EvalOp_Neg` (scope `__anon3fc13c1b0103`)
- L24 _enumerator_ `SYMS_EvalOp_Add` (scope `__anon3fc13c1b0103`)
- L25 _enumerator_ `SYMS_EvalOp_Sub` (scope `__anon3fc13c1b0103`)
- L26 _enumerator_ `SYMS_EvalOp_Mul` (scope `__anon3fc13c1b0103`)
- L27 _enumerator_ `SYMS_EvalOp_Div` (scope `__anon3fc13c1b0103`)
- L28 _enumerator_ `SYMS_EvalOp_Mod` (scope `__anon3fc13c1b0103`)
- L29 _enumerator_ `SYMS_EvalOp_LShift` (scope `__anon3fc13c1b0103`)
- L30 _enumerator_ `SYMS_EvalOp_RShift` (scope `__anon3fc13c1b0103`)
- L31 _enumerator_ `SYMS_EvalOp_BitAnd` (scope `__anon3fc13c1b0103`)
- L32 _enumerator_ `SYMS_EvalOp_BitOr` (scope `__anon3fc13c1b0103`)
- L33 _enumerator_ `SYMS_EvalOp_BitXor` (scope `__anon3fc13c1b0103`)
- L34 _enumerator_ `SYMS_EvalOp_BitNot` (scope `__anon3fc13c1b0103`)
- L35 _enumerator_ `SYMS_EvalOp_LogAnd` (scope `__anon3fc13c1b0103`)
- L36 _enumerator_ `SYMS_EvalOp_LogOr` (scope `__anon3fc13c1b0103`)
- L37 _enumerator_ `SYMS_EvalOp_LogNot` (scope `__anon3fc13c1b0103`)
- L38 _enumerator_ `SYMS_EvalOp_EqEq` (scope `__anon3fc13c1b0103`)
- L39 _enumerator_ `SYMS_EvalOp_NtEq` (scope `__anon3fc13c1b0103`)
- L40 _enumerator_ `SYMS_EvalOp_LsEq` (scope `__anon3fc13c1b0103`)
- L41 _enumerator_ `SYMS_EvalOp_GrEq` (scope `__anon3fc13c1b0103`)
- L42 _enumerator_ `SYMS_EvalOp_Less` (scope `__anon3fc13c1b0103`)
- L43 _enumerator_ `SYMS_EvalOp_Grtr` (scope `__anon3fc13c1b0103`)
- L44 _enumerator_ `SYMS_EvalOp_Trunc` (scope `__anon3fc13c1b0103`)
- L45 _enumerator_ `SYMS_EvalOp_TruncSigned` (scope `__anon3fc13c1b0103`)
- L46 _enumerator_ `SYMS_EvalOp_Convert` (scope `__anon3fc13c1b0103`)
- L47 _enumerator_ `SYMS_EvalOp_Pick` (scope `__anon3fc13c1b0103`)
- L48 _enumerator_ `SYMS_EvalOp_Pop` (scope `__anon3fc13c1b0103`)
- L49 _enumerator_ `SYMS_EvalOp_Insert` (scope `__anon3fc13c1b0103`)
- L50 _enumerator_ `SYMS_EvalOp_COUNT` (scope `__anon3fc13c1b0103`)
- L51 _typedef_ `SYMS_EvalOp_Pop, SYMS_EvalOp_Insert, SYMS_EvalOp_COUNT, } SYMS_EvalOp;`
- L54 _enumerator_ `SYMS_EvalOpCtrlBits_DecodeMask = 0xf` (scope `__anon3fc13c1b0203`)
- L55 _enumerator_ `SYMS_EvalOpCtrlBits_DecodeShft = 4` (scope `__anon3fc13c1b0203`)
- L56 _enumerator_ `SYMS_EvalOpCtrlBits_PopMask = 0x3` (scope `__anon3fc13c1b0203`)
- L57 _enumerator_ `SYMS_EvalOpCtrlBits_PopShft = 2` (scope `__anon3fc13c1b0203`)
- L58 _enumerator_ `SYMS_EvalOpCtrlBits_PushMask = 0x3` (scope `__anon3fc13c1b0203`)
- L59 _enumerator_ `SYMS_EvalOpCtrlBits_PushShft = 0` (scope `__anon3fc13c1b0203`)
- L63 _enumerator_ `SYMS_EvalTypeGroup_Other` (scope `__anon3fc13c1b0303`)
- L64 _enumerator_ `SYMS_EvalTypeGroup_U` (scope `__anon3fc13c1b0303`)
- L65 _enumerator_ `SYMS_EvalTypeGroup_S` (scope `__anon3fc13c1b0303`)
- L66 _enumerator_ `SYMS_EvalTypeGroup_F32` (scope `__anon3fc13c1b0303`)
- L67 _enumerator_ `SYMS_EvalTypeGroup_F64` (scope `__anon3fc13c1b0303`)
- L68 _enumerator_ `SYMS_EvalTypeGroup_COUNT` (scope `__anon3fc13c1b0303`)
- L69 _typedef_ `SYMS_EvalTypeGroup_F32, SYMS_EvalTypeGroup_F64, SYMS_EvalTypeGroup_COUNT, } SYMS_EvalTypeGroup;`
- L72 _enumerator_ `SYMS_EvalConversionKind_Noop` (scope `__anon3fc13c1b0403`)
- L73 _enumerator_ `SYMS_EvalConversionKind_Legal` (scope `__anon3fc13c1b0403`)
- L74 _enumerator_ `SYMS_EvalConversionKind_OtherToOther` (scope `__anon3fc13c1b0403`)
- L75 _enumerator_ `SYMS_EvalConversionKind_ToOther` (scope `__anon3fc13c1b0403`)
- L76 _enumerator_ `SYMS_EvalConversionKind_FromOther` (scope `__anon3fc13c1b0403`)
- L77 _enumerator_ `SYMS_EvalConversionKind_COUNT` (scope `__anon3fc13c1b0403`)
- L78 _typedef_ `SYMS_EvalConversionKind_ToOther, SYMS_EvalConversionKind_FromOther, SYMS_EvalConversionKind_COUNT, } SYMS_EvalConversionKind;`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_mach.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L7-32_

#### enum `(anonymous)`  
`enum`  
_L34-65_

#### enum `(anonymous)`  
`enum`  
_L67-70_

#### enum `(anonymous)`  
`enum`  
_L72-87_

#### enum `(anonymous)`  
`enum`  
_L89-95_

#### enum `(anonymous)`  
`enum`  
_L97-120_

#### enum `(anonymous)`  
`enum`  
_L122-137_

#### enum `(anonymous)`  
`enum`  
_L139-143_

#### enum `(anonymous)`  
`enum`  
_L145-167_

#### enum `(anonymous)`  
`enum`  
_L169-200_

#### enum `(anonymous)`  
`enum`  
_L202-258_

#### enum `(anonymous)`  
`enum`  
_L260-287_

#### enum `(anonymous)`  
`enum`  
_L289-303_

#### enum `(anonymous)`  
`enum`  
_L305-311_

#### enum `(anonymous)`  
`enum`  
_L313-318_

#### enum `(anonymous)`  
`enum`  
_L320-325_

#### enum `(anonymous)`  
`enum`  
_L327-344_

#### enum `(anonymous)`  
`enum`  
_L346-349_

#### enum `(anonymous)`  
`enum`  
_L351-356_

#### enum `(anonymous)`  
`enum`  
_L358-365_

#### enum `(anonymous)`  
`enum`  
_L367-399_

#### enum `(anonymous)`  
`enum`  
_L401-406_

#### enum `(anonymous)`  
`enum`  
_L408-413_

#### struct `SYMS_MachLCStr`  
`typedef struct SYMS_MachLCStr`  
_L415-417_
- L416 _public member_ `SYMS_U32 offset;`

#### struct `SYMS_MachUUID`  
`typedef struct SYMS_MachUUID`  
_L418-422_
- L419 _public member_ `SYMS_U32 cmd;`
- L420 _public member_ `SYMS_U32 cmdsize;`
- L421 _public member_ `SYMS_U8 uuid[16];`

#### struct `SYMS_MachDylib`  
`typedef struct SYMS_MachDylib`  
_L423-428_
- L424 _public member_ `SYMS_MachLCStr name;`
- L425 _public member_ `SYMS_U32 timestamp;`
- L426 _public member_ `SYMS_U32 current_version;`
- L427 _public member_ `SYMS_U32 compatability_version;`

#### struct `SYMS_MachDylibCommand`  
`typedef struct SYMS_MachDylibCommand`  
_L429-433_
- L430 _public member_ `SYMS_U32 cmd;`
- L431 _public member_ `SYMS_U32 cmdsize;`
- L432 _public member_ `SYMS_MachDylib dylib;`

#### struct `SYMS_MachDyldInfoCommand`  
`typedef struct SYMS_MachDyldInfoCommand`  
_L434-447_
- L435 _public member_ `SYMS_U32 cmd;`
- L436 _public member_ `SYMS_U32 cmdsize;`
- L437 _public member_ `SYMS_U32 rebase_off;`
- L438 _public member_ `SYMS_U32 rebase_size;`
- L439 _public member_ `SYMS_U32 bind_off;`
- L440 _public member_ `SYMS_U32 bind_size;`
- L441 _public member_ `SYMS_U32 weak_bind_off;`
- L442 _public member_ `SYMS_U32 weak_bind_size;`
- L443 _public member_ `SYMS_U32 lazy_bind_off;`
- L444 _public member_ `SYMS_U32 lazy_bind_size;`
- L445 _public member_ `SYMS_U32 export_off;`
- L446 _public member_ `SYMS_U32 export_size;`

#### struct `SYMS_MachLoadCommand`  
`typedef struct SYMS_MachLoadCommand`  
_L448-451_
- L449 _public member_ `SYMS_MachLoadCommandType type;`
- L450 _public member_ `SYMS_U32 size;`

#### struct `SYMS_MachFatHeader`  
`typedef struct SYMS_MachFatHeader`  
_L452-455_
- L453 _public member_ `SYMS_U32 magic;`
- L454 _public member_ `SYMS_U32 nfat_arch;`

#### struct `SYMS_MachFatArch`  
`typedef struct SYMS_MachFatArch`  
_L456-462_
- L457 _public member_ `SYMS_MachCpuType cputype;`
- L458 _public member_ `SYMS_MachCpuSubtype cpusubtype;`
- L459 _public member_ `SYMS_U32 offset;`
- L460 _public member_ `SYMS_U32 size;`
- L461 _public member_ `SYMS_U32 align;`

#### struct `SYMS_MachHeader32`  
`typedef struct SYMS_MachHeader32`  
_L463-471_
- L464 _public member_ `SYMS_U32 magic;`
- L465 _public member_ `SYMS_MachCpuType cputype;`
- L466 _public member_ `SYMS_MachCpuSubtype cpusubtype;`
- L467 _public member_ `SYMS_MachFiletype filetype;`
- L468 _public member_ `SYMS_U32 ncmds;`
- L469 _public member_ `SYMS_U32 sizeofcmds;`
- L470 _public member_ `SYMS_MachFlags flags;`

#### struct `SYMS_MachHeader64`  
`typedef struct SYMS_MachHeader64`  
_L472-481_
- L473 _public member_ `SYMS_U32 magic;`
- L474 _public member_ `SYMS_MachCpuType cputype;`
- L475 _public member_ `SYMS_MachCpuSubtype cpusubtype;`
- L476 _public member_ `SYMS_MachFiletype filetype;`
- L477 _public member_ `SYMS_U32 ncmds;`
- L478 _public member_ `SYMS_U32 sizeofcmds;`
- L479 _public member_ `SYMS_MachFlags flags;`
- L480 _public member_ `SYMS_U32 reserved;`

#### struct `SYMS_MachSegmentCommand32`  
`typedef struct SYMS_MachSegmentCommand32`  
_L482-493_
- L483 _public member_ `SYMS_MachLoadCommand cmd;`
- L484 _public member_ `SYMS_U8 segname[16];`
- L485 _public member_ `SYMS_U32 vmaddr;`
- L486 _public member_ `SYMS_U32 vmsize;`
- L487 _public member_ `SYMS_U32 fileoff;`
- L488 _public member_ `SYMS_U32 filesize;`
- L489 _public member_ `SYMS_MachVMProt maxprot;`
- L490 _public member_ `SYMS_MachVMProt initprot;`
- L491 _public member_ `SYMS_U32 nsects;`
- L492 _public member_ `SYMS_U32 flags;`

#### struct `SYMS_MachSegmentCommand64`  
`typedef struct SYMS_MachSegmentCommand64`  
_L494-505_
- L495 _public member_ `SYMS_MachLoadCommand cmd;`
- L496 _public member_ `SYMS_U8 segname[16];`
- L497 _public member_ `SYMS_U64 vmaddr;`
- L498 _public member_ `SYMS_U64 vmsize;`
- L499 _public member_ `SYMS_U64 fileoff;`
- L500 _public member_ `SYMS_U64 filesize;`
- L501 _public member_ `SYMS_MachVMProt maxprot;`
- L502 _public member_ `SYMS_MachVMProt initprot;`
- L503 _public member_ `SYMS_U32 nsects;`
- L504 _public member_ `SYMS_U32 flags;`

#### struct `SYMS_MachSection32`  
`typedef struct SYMS_MachSection32`  
_L506-518_
- L507 _public member_ `SYMS_U8 sectname[16];`
- L508 _public member_ `SYMS_U8 segname[16];`
- L509 _public member_ `SYMS_U32 addr;`
- L510 _public member_ `SYMS_U32 size;`
- L511 _public member_ `SYMS_U32 offset;`
- L512 _public member_ `SYMS_U32 align;`
- L513 _public member_ `SYMS_U32 relocoff;`
- L514 _public member_ `SYMS_U32 nreloc;`
- L515 _public member_ `SYMS_U32 flags;`
- L516 _public member_ `SYMS_U32 reserved1;`
- L517 _public member_ `SYMS_U32 reserved2;`

#### struct `SYMS_MachSection64`  
`typedef struct SYMS_MachSection64`  
_L519-532_
- L520 _public member_ `SYMS_U8 sectname[16];`
- L521 _public member_ `SYMS_U8 segname[16];`
- L522 _public member_ `SYMS_U64 addr;`
- L523 _public member_ `SYMS_U64 size;`
- L524 _public member_ `SYMS_U32 offset;`
- L525 _public member_ `SYMS_U32 align;`
- L526 _public member_ `SYMS_U32 relocoff;`
- L527 _public member_ `SYMS_U32 nreloc;`
- L528 _public member_ `SYMS_U32 flags;`
- L529 _public member_ `SYMS_U32 reserved1;`
- L530 _public member_ `SYMS_U32 reserved2;`
- L531 _public member_ `SYMS_U32 pad;`

#### struct `SYMS_MachSymtabCommand`  
`typedef struct SYMS_MachSymtabCommand`  
_L533-543_
- L534 _public member_ `SYMS_U32 cmd;`
- L535 _public member_ `SYMS_U32 cmdsize;`
- L536 _public member_ `SYMS_U32 symoff;`
- L538 _public member_ `SYMS_U32 nsyms;` — offset from the image base to array of SYMS_MachNList32
- L540 _public member_ `SYMS_U32 stroff;` — symbol count
- L542 _public member_ `SYMS_U32 strsize;` — offset from the image base to string table

#### struct `SYMS_MachDySymtabCommand`  
`typedef struct SYMS_MachDySymtabCommand`  
_L544-565_
- L545 _public member_ `SYMS_U32 cmd;`
- L546 _public member_ `SYMS_U32 cmdsize;`
- L547 _public member_ `SYMS_U32 ilocalsym;`
- L548 _public member_ `SYMS_U32 nlocalsym;`
- L549 _public member_ `SYMS_U32 iextdefsym;`
- L550 _public member_ `SYMS_U32 nextdefsym;`
- L551 _public member_ `SYMS_U32 iundefsym;`
- L552 _public member_ `SYMS_U32 nundefsym;`
- L553 _public member_ `SYMS_U32 tocoff;`
- L554 _public member_ `SYMS_U32 ntoc;`
- L555 _public member_ `SYMS_U32 modtaboff;`
- L556 _public member_ `SYMS_U32 nmodtab;`
- L557 _public member_ `SYMS_U32 extrefsymoff;`
- L558 _public member_ `SYMS_U32 nextrefsyms;`
- L559 _public member_ `SYMS_U32 indirectsymoff;`
- L560 _public member_ `SYMS_U32 nindirectsyms;`
- L561 _public member_ `SYMS_U32 extreloff;`
- L562 _public member_ `SYMS_U32 nextrel;`
- L563 _public member_ `SYMS_U32 locreloff;`
- L564 _public member_ `SYMS_U32 nlocrel;`

#### struct `SYMS_MachNList32`  
`typedef struct SYMS_MachNList32`  
_L566-572_
- L567 _public member_ `SYMS_U32 n_strx;`
- L568 _public member_ `SYMS_U8 n_type;`
- L569 _public member_ `SYMS_U8 n_sect;`
- L570 _public member_ `SYMS_U16 n_desc;`
- L571 _public member_ `SYMS_U32 n_value;`

#### struct `SYMS_MachNList64`  
`typedef struct SYMS_MachNList64`  
_L573-579_
- L574 _public member_ `SYMS_U32 n_strx;`
- L575 _public member_ `SYMS_U8 n_type;`
- L576 _public member_ `SYMS_U8 n_sect;`
- L577 _public member_ `SYMS_U16 n_desc;`
- L578 _public member_ `SYMS_U64 n_value;`

#### struct `SYMS_MachBuildVersionCommand`  
`typedef struct SYMS_MachBuildVersionCommand`  
_L580-587_
- L581 _public member_ `SYMS_U32 cmd;`
- L582 _public member_ `SYMS_U32 cmdsize;`
- L583 _public member_ `SYMS_MachPlatformType platform;`
- L584 _public member_ `SYMS_U32 minos;`
- L585 _public member_ `SYMS_U32 sdk;`
- L586 _public member_ `SYMS_U32 ntools;`

#### struct `SYMS_MachBuildToolVersion`  
`typedef struct SYMS_MachBuildToolVersion`  
_L588-591_
- L589 _public member_ `SYMS_MachToolType tool;`
- L590 _public member_ `SYMS_U32 version;`

#### struct `SYMS_MachVersionMin`  
`typedef struct SYMS_MachVersionMin`  
_L592-597_
- L593 _public member_ `SYMS_U32 cmd;`
- L594 _public member_ `SYMS_U32 cmdsize;`
- L595 _public member_ `SYMS_U32 version;`
- L596 _public member_ `SYMS_U32 sdk;`

#### struct `SYMS_MachDylinker`  
`typedef struct SYMS_MachDylinker`  
_L598-602_
- L599 _public member_ `SYMS_U32 cmd;`
- L600 _public member_ `SYMS_U32 cmdsize;`
- L601 _public member_ `SYMS_MachLCStr name;`

#### struct `SYMS_MachPreboundDylibCommand`  
`typedef struct SYMS_MachPreboundDylibCommand`  
_L603-608_
- L604 _public member_ `SYMS_U32 cmd;`
- L605 _public member_ `SYMS_U32 cmdsize;`
- L606 _public member_ `SYMS_MachLCStr name;`
- L607 _public member_ `SYMS_U32 nmodules;`

#### struct `SYMS_MachRoutinesCommand`  
`typedef struct SYMS_MachRoutinesCommand`  
_L609-620_
- L610 _public member_ `SYMS_U32 cmd;`
- L611 _public member_ `SYMS_U32 cmdsize;`
- L612 _public member_ `SYMS_U32 init_address;`
- L613 _public member_ `SYMS_U32 init_module;`
- L614 _public member_ `SYMS_U32 reserved1;`
- L615 _public member_ `SYMS_U32 reserved2;`
- L616 _public member_ `SYMS_U32 reserved3;`
- L617 _public member_ `SYMS_U32 reserved4;`
- L618 _public member_ `SYMS_U32 reserved5;`
- L619 _public member_ `SYMS_U32 reserved6;`

#### struct `SYMS_MachRoutines64Command`  
`typedef struct SYMS_MachRoutines64Command`  
_L621-632_
- L622 _public member_ `SYMS_U32 cmd;`
- L623 _public member_ `SYMS_U32 cmdsize;`
- L624 _public member_ `SYMS_U64 init_address;`
- L625 _public member_ `SYMS_U64 init_module;`
- L626 _public member_ `SYMS_U64 reserved1;`
- L627 _public member_ `SYMS_U64 reserved2;`
- L628 _public member_ `SYMS_U64 reserved3;`
- L629 _public member_ `SYMS_U64 reserved4;`
- L630 _public member_ `SYMS_U64 reserved5;`
- L631 _public member_ `SYMS_U64 reserved6;`

#### struct `SYMS_MachSubFrameworkCommand`  
`typedef struct SYMS_MachSubFrameworkCommand`  
_L633-637_
- L634 _public member_ `SYMS_U32 cmd;`
- L635 _public member_ `SYMS_U32 cmdsize;`
- L636 _public member_ `SYMS_MachLCStr umbrella;`

#### struct `SYMS_MachSubUmbrellaCommand`  
`typedef struct SYMS_MachSubUmbrellaCommand`  
_L638-642_
- L639 _public member_ `SYMS_U32 cmd;`
- L640 _public member_ `SYMS_U32 cmdsize;`
- L641 _public member_ `SYMS_MachLCStr sub_umbrella;`

#### struct `SYMS_MachSubClientCommand`  
`typedef struct SYMS_MachSubClientCommand`  
_L643-647_
- L644 _public member_ `SYMS_U32 cmd;`
- L645 _public member_ `SYMS_U32 cmdsize;`
- L646 _public member_ `SYMS_MachLCStr client;`

#### struct `SYMS_MachSubLibraryCommand`  
`typedef struct SYMS_MachSubLibraryCommand`  
_L648-652_
- L649 _public member_ `SYMS_U32 cmd;`
- L650 _public member_ `SYMS_U32 cmdsize;`
- L651 _public member_ `SYMS_MachLCStr sub_library;`

#### struct `SYMS_MachTwoLevelHintsCommand`  
`typedef struct SYMS_MachTwoLevelHintsCommand`  
_L653-658_
- L654 _public member_ `SYMS_U32 cmd;`
- L655 _public member_ `SYMS_U32 cmdsize;`
- L656 _public member_ `SYMS_U32 offset;`
- L657 _public member_ `SYMS_U32 nhints;`

#### enum `(anonymous)`  
`enum`  
_L660-663_

#### struct `SYMS_MachPrebindChecksumCommand`  
`typedef struct SYMS_MachPrebindChecksumCommand`  
_L666-670_
- L667 _public member_ `SYMS_U32 cmd;`
- L668 _public member_ `SYMS_U32 cmdsize;`
- L669 _public member_ `SYMS_U32 chksum;`

#### struct `SYMS_MachRPathCommand`  
`typedef struct SYMS_MachRPathCommand`  
_L671-675_
- L672 _public member_ `SYMS_U32 cmd;`
- L673 _public member_ `SYMS_U32 cmdsize;`
- L674 _public member_ `SYMS_MachLCStr path;`

#### struct `SYMS_MachLinkeditDataCommand`  
`typedef struct SYMS_MachLinkeditDataCommand`  
_L676-681_
- L677 _public member_ `SYMS_U32 cmd;`
- L678 _public member_ `SYMS_U32 cmdsize;`
- L679 _public member_ `SYMS_U32 dataoff;`
- L680 _public member_ `SYMS_U32 datasize;`

#### struct `SYMS_MachEncryptionInfoCommand`  
`typedef struct SYMS_MachEncryptionInfoCommand`  
_L682-688_
- L683 _public member_ `SYMS_U32 cmd;`
- L684 _public member_ `SYMS_U32 cmdsize;`
- L685 _public member_ `SYMS_U32 cryptoff;`
- L686 _public member_ `SYMS_U32 cryptsize;`
- L687 _public member_ `SYMS_U32 cryptid;`

#### struct `SYMS_MachEncryptionInfo64Command`  
`typedef struct SYMS_MachEncryptionInfo64Command`  
_L689-696_
- L690 _public member_ `SYMS_U32 cmd;`
- L691 _public member_ `SYMS_U32 cmdsize;`
- L692 _public member_ `SYMS_U32 cryptoff;`
- L693 _public member_ `SYMS_U32 cryptsize;`
- L694 _public member_ `SYMS_U32 cryptid;`
- L695 _public member_ `SYMS_U32 pad;`

#### struct `SYMS_MachEntryPointCommand`  
`typedef struct SYMS_MachEntryPointCommand`  
_L697-702_
- L698 _public member_ `SYMS_U32 cmd;`
- L699 _public member_ `SYMS_U32 cmdsize;`
- L700 _public member_ `SYMS_U64 entryoff;`
- L701 _public member_ `SYMS_U64 stacksize;`

#### struct `SYMS_MachSourceVersionCommand`  
`typedef struct SYMS_MachSourceVersionCommand`  
_L703-707_
- L704 _public member_ `SYMS_U32 cmd;`
- L705 _public member_ `SYMS_U32 cmdsize;`
- L706 _public member_ `SYMS_U64 version;`

#### struct `SYMS_MachLinkerOptionCommand`  
`typedef struct SYMS_MachLinkerOptionCommand`  
_L708-712_
- L709 _public member_ `SYMS_U32 cmd;`
- L710 _public member_ `SYMS_U32 cmdsize;`
- L711 _public member_ `SYMS_U32 count;`

#### struct `SYMS_MachNoteCommand`  
`typedef struct SYMS_MachNoteCommand`  
_L713-719_
- L714 _public member_ `SYMS_U32 cmd;`
- L715 _public member_ `SYMS_U32 cmdsize;`
- L716 _public member_ `SYMS_U8 data_owner[16];`
- L717 _public member_ `SYMS_U64 offset;`
- L718 _public member_ `SYMS_U64 size;`

#### struct `SYMS_MachSymSegCommand`  
`typedef struct SYMS_MachSymSegCommand`  
_L720-725_
- L721 _public member_ `SYMS_U32 cmd;`
- L722 _public member_ `SYMS_U32 cmdsize;`
- L723 _public member_ `SYMS_U32 offset;`
- L724 _public member_ `SYMS_U32 size;`

#### struct `SYMS_MachFvmlib`  
`typedef struct SYMS_MachFvmlib`  
_L726-730_
- L727 _public member_ `SYMS_MachLCStr name;`
- L728 _public member_ `SYMS_U32 minor_version;`
- L729 _public member_ `SYMS_U32 header_addr;`

#### struct `SYMS_MachFvmlibCommand`  
`typedef struct SYMS_MachFvmlibCommand`  
_L731-735_
- L732 _public member_ `SYMS_U32 cmd;`
- L733 _public member_ `SYMS_U32 cmdsize;`
- L734 _public member_ `SYMS_MachFvmlib fvmlib;`

#### struct `SYMS_MachThreadCommand`  
`typedef struct SYMS_MachThreadCommand`  
_L736-739_
- L737 _public member_ `SYMS_U32 cmd;`
- L738 _public member_ `SYMS_U32 cmdsize;`

#### enum `(anonymous)`  
`enum`  
_L741-747_

#### enum `(anonymous)`  
`enum`  
_L749-758_

#### enum `(anonymous)`  
`enum`  
_L760-769_

#### enum `(anonymous)`  
`enum`  
_L776-782_

#### enum `(anonymous)`  
`enum`  
_L784-793_

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_MACH_H`
- L6 _typedef_ `typedef SYMS_S32 SYMS_MachCpuType;`
- L8 _enumerator_ `SYMS_MachCpuType_ANY = 0xFFFFFFFF` (scope `__anon50ef864c0103`)
- L9 _enumerator_ `SYMS_MachCpuType_VAX = 0x1` (scope `__anon50ef864c0103`)
- L10 _enumerator_ `SYMS_MachCpuType_RESERVED2 = 0x2` (scope `__anon50ef864c0103`)
- L11 _enumerator_ `SYMS_MachCpuType_RESERVED3 = 0x3` (scope `__anon50ef864c0103`)
- L12 _enumerator_ `SYMS_MachCpuType_RESERVED4 = 0x4` (scope `__anon50ef864c0103`)
- L13 _enumerator_ `SYMS_MachCpuType_RESERVED5 = 0x5` (scope `__anon50ef864c0103`)
- L14 _enumerator_ `SYMS_MachCpuType_MC680x0 = 0x6` (scope `__anon50ef864c0103`)
- L15 _enumerator_ `SYMS_MachCpuType_X86 = 0x7` (scope `__anon50ef864c0103`)
- L16 _enumerator_ `SYMS_MachCpuType_I386 = SYMS_MachCpuType_X86` (scope `__anon50ef864c0103`)
- L17 _enumerator_ `SYMS_MachCpuType_X86_64 = 0x01000007` (scope `__anon50ef864c0103`)
- L18 _enumerator_ `SYMS_MachCpuType_RESERVED8 = 0x8` (scope `__anon50ef864c0103`)
- L19 _enumerator_ `SYMS_MachCpuType_RESERVED9 = 0x9` (scope `__anon50ef864c0103`)
- L20 _enumerator_ `SYMS_MachCpuType_MC98000 = 0xA` (scope `__anon50ef864c0103`)
- L21 _enumerator_ `SYMS_MachCpuType_HPPA = 0xB` (scope `__anon50ef864c0103`)
- L22 _enumerator_ `SYMS_MachCpuType_ARM = 0xC` (scope `__anon50ef864c0103`)
- L23 _enumerator_ `SYMS_MachCpuType_ARM64 = 0x0100000C` (scope `__anon50ef864c0103`)
- L24 _enumerator_ `SYMS_MachCpuType_MC88000 = 0xD` (scope `__anon50ef864c0103`)
- L25 _enumerator_ `SYMS_MachCpuType_SPARC = 0xE` (scope `__anon50ef864c0103`)
- L26 _enumerator_ `SYMS_MachCpuType_I860 = 0xF` (scope `__anon50ef864c0103`)
- L27 _enumerator_ `SYMS_MachCpuType_ALPHA = 0x10` (scope `__anon50ef864c0103`)
- L28 _enumerator_ `SYMS_MachCpuType_RESERVED17 = 0x11` (scope `__anon50ef864c0103`)
- L29 _enumerator_ `SYMS_MachCpuType_POWERPC = 0x12` (scope `__anon50ef864c0103`)
- L30 _enumerator_ `SYMS_MachCpuType_POWERPC64 = 0x01000012` (scope `__anon50ef864c0103`)
- L31 _enumerator_ `SYMS_MachCpuType_COUNT = 23` (scope `__anon50ef864c0103`)
- L33 _typedef_ `typedef SYMS_S32 SYMS_MachCpuFamily;`
- L35 _enumerator_ `SYMS_MachCpuFamily_UNKNOWN = 0x0` (scope `__anon50ef864c0203`)
- L36 _enumerator_ `SYMS_MachCpuFamily_POWERPC_G3 = 0xCEE41549` (scope `__anon50ef864c0203`)
- L37 _enumerator_ `SYMS_MachCpuFamily_POWERPC_G4 = 0x77C184AE` (scope `__anon50ef864c0203`)
- L38 _enumerator_ `SYMS_MachCpuFamily_POWERPC_G5 = 0xED76D8AA` (scope `__anon50ef864c0203`)
- L39 _enumerator_ `SYMS_MachCpuFamily_INTEL_6_13 = 0xAA33392B` (scope `__anon50ef864c0203`)
- L40 _enumerator_ `SYMS_MachCpuFamily_INTEL_PENRYN = 0x78EA4FBC` (scope `__anon50ef864c0203`)
- L41 _enumerator_ `SYMS_MachCpuFamily_INTEL_NEHALEM = 0x6B5a4CD2` (scope `__anon50ef864c0203`)
- L42 _enumerator_ `SYMS_MachCpuFamily_INTEL_WESTMERE = 0x573B4EEC` (scope `__anon50ef864c0203`)
- L43 _enumerator_ `SYMS_MachCpuFamily_INTEL_SANDYBRIDGE = 0x5490B78C` (scope `__anon50ef864c0203`)
- L44 _enumerator_ `SYMS_MachCpuFamily_INTEL_IVYBRIDGE = 0x1F65E835` (scope `__anon50ef864c0203`)
- L45 _enumerator_ `SYMS_MachCpuFamily_INTEL_HASWELL = 0x10B282DC` (scope `__anon50ef864c0203`)
- L46 _enumerator_ `SYMS_MachCpuFamily_INTEL_BROADWELL = 0x582ED09C` (scope `__anon50ef864c0203`)
- L47 _enumerator_ `SYMS_MachCpuFamily_INTEL_SKYLAKE = 0x37FC219F` (scope `__anon50ef864c0203`)
- L48 _enumerator_ `SYMS_MachCpuFamily_INTEL_KABYLAKE = 0x0F817246` (scope `__anon50ef864c0203`)
- L49 _enumerator_ `SYMS_MachCpuFamily_ARM_9 = 0xE73283AE` (scope `__anon50ef864c0203`)
- L50 _enumerator_ `SYMS_MachCpuFamily_ARM_11 = 0x8FF620D8` (scope `__anon50ef864c0203`)
- L51 _enumerator_ `SYMS_MachCpuFamily_ARM_XSCALE = 0x53B005F5` (scope `__anon50ef864c0203`)
- L52 _enumerator_ `SYMS_MachCpuFamily_ARM_12 = 0xBD1B0AE9` (scope `__anon50ef864c0203`)
- L53 _enumerator_ `SYMS_MachCpuFamily_ARM_13 = 0x0CC90E64` (scope `__anon50ef864c0203`)
- L54 _enumerator_ `SYMS_MachCpuFamily_ARM_14 = 0x96077EF1` (scope `__anon50ef864c0203`)
- L55 _enumerator_ `SYMS_MachCpuFamily_ARM_15 = 0xA8511BCA` (scope `__anon50ef864c0203`)
- L56 _enumerator_ `SYMS_MachCpuFamily_ARM_SWIFT = 0x1E2D6381` (scope `__anon50ef864c0203`)
- L57 _enumerator_ `SYMS_MachCpuFamily_ARM_CYCLONE = 0x37A09642` (scope `__anon50ef864c0203`)
- L58 _enumerator_ `SYMS_MachCpuFamily_ARM_TYPHOON = 0x2C91A47E` (scope `__anon50ef864c0203`)
- L59 _enumerator_ `SYMS_MachCpuFamily_ARM_TWISTER = 0x92FB37C8` (scope `__anon50ef864c0203`)
- L60 _enumerator_ `SYMS_MachCpuFamily_ARM_HURRICANE = 0x67CEEE93` (scope `__anon50ef864c0203`)
- L62 _enumerator_ `SYMS_MachCpuFamily_INTEL_6_23 = SYMS_MachCpuFamily_INTEL_PENRYN` (scope `__anon50ef864c0203`) — deprecated
- L63 _enumerator_ `SYMS_MachCpuFamily_INTEL_6_26 = SYMS_MachCpuFamily_INTEL_NEHALEM` (scope `__anon50ef864c0203`)
- L64 _enumerator_ `SYMS_MachCpuFamily_COUNT = 28` (scope `__anon50ef864c0203`)
- L66 _typedef_ `typedef SYMS_U32 SYMS_MachCpuSubtype;`
- L68 _enumerator_ `SYMS_MachCpuSubtype_ALL = 0` (scope `__anon50ef864c0303`)
- L69 _enumerator_ `SYMS_MachCpuSubtype_COUNT = 1` (scope `__anon50ef864c0303`)
- L71 _typedef_ `typedef SYMS_U32 SYMS_MachCpuSubtypeVAX;`
- L73 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX_ALL = 0x0` (scope `__anon50ef864c0403`)
- L74 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX780 = 0x1` (scope `__anon50ef864c0403`)
- L75 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX785 = 0x2` (scope `__anon50ef864c0403`)
- L76 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX750 = 0x3` (scope `__anon50ef864c0403`)
- L77 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX730 = 0x4` (scope `__anon50ef864c0403`)
- L78 _enumerator_ `SYMS_MachCpuSubtypeVAX_UVAXI = 0x5` (scope `__anon50ef864c0403`)
- L79 _enumerator_ `SYMS_MachCpuSubtypeVAX_UVAXII = 0x6` (scope `__anon50ef864c0403`)
- L80 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX8200 = 0x7` (scope `__anon50ef864c0403`)
- L81 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX8500 = 0x8` (scope `__anon50ef864c0403`)
- L82 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX8600 = 0x9` (scope `__anon50ef864c0403`)
- L83 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX8650 = 0xA` (scope `__anon50ef864c0403`)
- L84 _enumerator_ `SYMS_MachCpuSubtypeVAX_VAX8800 = 0xB` (scope `__anon50ef864c0403`)
- L85 _enumerator_ `SYMS_MachCpuSubtypeVAX_UVAXIII = 0xC` (scope `__anon50ef864c0403`)
- L86 _enumerator_ `SYMS_MachCpuSubtypeVAX_COUNT = 13` (scope `__anon50ef864c0403`)
- L88 _typedef_ `typedef SYMS_U32 SYMS_MachCpuSubtypeX86;`
- L90 _enumerator_ `SYMS_MachCpuSubtypeX86_X86_ALL = 0x3` (scope `__anon50ef864c0503`)
- L91 _enumerator_ `SYMS_MachCpuSubtypeX86_X86_64_ALL = SYMS_MachCpuSubtypeX86_X86_ALL` (scope `__anon50ef864c0503`)
- L92 _enumerator_ `SYMS_MachCpuSubtypeX86_X86_ARCH1 = 0x4` (scope `__anon50ef864c0503`)
- L93 _enumerator_ `SYMS_MachCpuSubtypeX86_X86_64_HASWELL = 0x8` (scope `__anon50ef864c0503`)
- L94 _enumerator_ `SYMS_MachCpuSubtypeX86_COUNT = 4` (scope `__anon50ef864c0503`)
- L96 _typedef_ `typedef SYMS_U32 SYMS_MachCpuSubtypeIntel;`
- L98 _enumerator_ `SYMS_MachCpuSubtypeIntel_I386_ALL = 0x03` (scope `__anon50ef864c0603`)
- L99 _enumerator_ `SYMS_MachCpuSubtypeIntel_I386 = SYMS_MachCpuSubtypeIntel_I386_ALL` (scope `__anon50ef864c0603`)
- L100 _enumerator_ `SYMS_MachCpuSubtypeIntel_I486 = 0x04` (scope `__anon50ef864c0603`)
- L101 _enumerator_ `SYMS_MachCpuSubtypeIntel_I486SX = 0x84` (scope `__anon50ef864c0603`)
- L102 _enumerator_ `SYMS_MachCpuSubtypeIntel_I586 = 0x05` (scope `__anon50ef864c0603`)
- L103 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENT = SYMS_MachCpuSubtypeIntel_I586` (scope `__anon50ef864c0603`)
- L104 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTPRO = 0x16` (scope `__anon50ef864c0603`)
- L105 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTII_M3 = 0x36` (scope `__anon50ef864c0603`)
- L106 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTII_M5 = 0x56` (scope `__anon50ef864c0603`)
- L107 _enumerator_ `SYMS_MachCpuSubtypeIntel_CELERON = 0x67` (scope `__anon50ef864c0603`)
- L108 _enumerator_ `SYMS_MachCpuSubtypeIntel_CELERON_MOBILE = 0x77` (scope `__anon50ef864c0603`)
- L109 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_3 = 0x08` (scope `__anon50ef864c0603`)
- L110 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_3_M = 0x18` (scope `__anon50ef864c0603`)
- L111 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_3_XENON = 0x28` (scope `__anon50ef864c0603`)
- L112 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_M = 0x09` (scope `__anon50ef864c0603`)
- L113 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_4 = 0x0A` (scope `__anon50ef864c0603`)
- L114 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_4_M = 0x1A` (scope `__anon50ef864c0603`)
- L115 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_ITANIUM = 0x0B` (scope `__anon50ef864c0603`)
- L116 _enumerator_ `SYMS_MachCpuSubtypeIntel_PENTIUM_ITANIUM_2 = 0x1B` (scope `__anon50ef864c0603`)
- L117 _enumerator_ `SYMS_MachCpuSubtypeIntel_XEON = 0x0C` (scope `__anon50ef864c0603`)
- L118 _enumerator_ `SYMS_MachCpuSubtypeIntel_XEON_MP = 0x1C` (scope `__anon50ef864c0603`)
- L119 _enumerator_ `SYMS_MachCpuSubtypeIntel_COUNT = 21` (scope `__anon50ef864c0603`)
- L121 _typedef_ `typedef SYMS_U32 SYMS_MachCpuSubtypeARM;`
- L123 _enumerator_ `SYMS_MachCpuSubtypeARM_ALL = 0x0` (scope `__anon50ef864c0703`)
- L124 _enumerator_ `SYMS_MachCpuSubtypeARM_V4T = 0x5` (scope `__anon50ef864c0703`)
- L125 _enumerator_ `SYMS_MachCpuSubtypeARM_V6 = 0x6` (scope `__anon50ef864c0703`)
- L126 _enumerator_ `SYMS_MachCpuSubtypeARM_V5TEJ = 0x7` (scope `__anon50ef864c0703`)
- L127 _enumerator_ `SYMS_MachCpuSubtypeARM_XSCALE = 0x8` (scope `__anon50ef864c0703`)
- L128 _enumerator_ `SYMS_MachCpuSubtypeARM_V7 = 0x9` (scope `__anon50ef864c0703`)
- L129 _enumerator_ `SYMS_MachCpuSubtypeARM_V7F = 0xA` (scope `__anon50ef864c0703`)
- L130 _enumerator_ `SYMS_MachCpuSubtypeARM_V7S = 0xB` (scope `__anon50ef864c0703`)
- L131 _enumerator_ `SYMS_MachCpuSubtypeARM_V7K = 0xC` (scope `__anon50ef864c0703`)
- L132 _enumerator_ `SYMS_MachCpuSubtypeARM_V6M = 0xE` (scope `__anon50ef864c0703`)
- L133 _enumerator_ `SYMS_MachCpuSubtypeARM_V7M = 0xF` (scope `__anon50ef864c0703`)
- L134 _enumerator_ `SYMS_MachCpuSubtypeARM_V7EM = 0x10` (scope `__anon50ef864c0703`)
- L135 _enumerator_ `SYMS_MachCpuSubtypeARM_V8 = 0xD` (scope `__anon50ef864c0703`)
- L136 _enumerator_ `SYMS_MachCpuSubtypeARM_COUNT = 13` (scope `__anon50ef864c0703`)
- L138 _typedef_ `typedef SYMS_U32 SYMS_MachCpuSubtypeARM64;`
- L140 _enumerator_ `SYMS_MachCpuSubtypeARM64_ALL = 0` (scope `__anon50ef864c0803`)
- L141 _enumerator_ `SYMS_MachCpuSubtypeARM64_V8 = 1` (scope `__anon50ef864c0803`)
- L142 _enumerator_ `SYMS_MachCpuSubtypeARM64_COUNT = 2` (scope `__anon50ef864c0803`)
- L144 _typedef_ `typedef SYMS_U32 SYMS_MachFiletype;`
- L146 _enumerator_ `SYMS_MachFiletype_OBJECT = 0x1` (scope `__anon50ef864c0903`)
- L148 _enumerator_ `SYMS_MachFiletype_EXECUTE = 0x2` (scope `__anon50ef864c0903`) — object file
- L150 _enumerator_ `SYMS_MachFiletype_FVMLIB = 0x3` (scope `__anon50ef864c0903`) — executable file
- L152 _enumerator_ `SYMS_MachFiletype_CORE = 0x4` (scope `__anon50ef864c0903`) — fixed vm shared library file
- L153 _enumerator_ `SYMS_MachFiletype_PRELOAD = 0x5` (scope `__anon50ef864c0903`)
- L155 _enumerator_ `SYMS_MachFiletype_DYLIB = 0x6` (scope `__anon50ef864c0903`) — preloaded executable
- L157 _enumerator_ `SYMS_MachFiletype_DYLINKER = 0x7` (scope `__anon50ef864c0903`) — dynamic library
- L159 _enumerator_ `SYMS_MachFiletype_BUNDLE = 0x8` (scope `__anon50ef864c0903`) — dynamic link editor
- L161 _enumerator_ `SYMS_MachFiletype_DYLIB_STUB = 0x9` (scope `__anon50ef864c0903`) — executable file that program can load at runtime through dynamic linker
- L163 _enumerator_ `SYMS_MachFiletype_DSYM = 0xA` (scope `__anon50ef864c0903`) — stub for linking with dynamic lib, contains info for linking only, no section data
- L165 _enumerator_ `SYMS_MachFiletype_KEXT_BUNDLE = 0xB` (scope `__anon50ef864c0903`) — External debug symbols
- L166 _enumerator_ `SYMS_MachFiletype_COUNT = 11` (scope `__anon50ef864c0903`)
- L168 _typedef_ `typedef SYMS_U32 SYMS_MachFlags;`
- L170 _enumerator_ `SYMS_MachFlags_NOUNDEFS = 0x1` (scope `__anon50ef864c0a03`)
- L171 _enumerator_ `SYMS_MachFlags_INCRLINK = 0x2` (scope `__anon50ef864c0a03`)
- L173 _enumerator_ `SYMS_MachFlags_DYLDLINK = 0x4` (scope `__anon50ef864c0a03`) — object was processed by linker and cannot be linked again
- L175 _enumerator_ `SYMS_MachFlags_BINDATLOAD = 0x8` (scope `__anon50ef864c0a03`) — object is input for dynamic linker and cannot be statically linked
- L177 _enumerator_ `SYMS_MachFlags_PREBOUND = 0x10` (scope `__anon50ef864c0a03`) — undefined references are resolved at load
- L178 _enumerator_ `SYMS_MachFlags_SPLIT_SEGS = 0x20` (scope `__anon50ef864c0a03`)
- L180 _enumerator_ `SYMS_MachFlags_LAZY_INIT = 0x40` (scope `__anon50ef864c0a03`) — read-only and write-only segment is split
- L181 _enumerator_ `SYMS_MachFlags_TWOLEVEL = 0x80` (scope `__anon50ef864c0a03`)
- L182 _enumerator_ `SYMS_MachFlags_FORCE_FLAT = 0x100` (scope `__anon50ef864c0a03`)
- L183 _enumerator_ `SYMS_MachFlags_NOMULTIDEFS = 0x200` (scope `__anon50ef864c0a03`)
- L184 _enumerator_ `SYMS_MachFlags_NOFIXPREBOUNDING = 0x400` (scope `__anon50ef864c0a03`)
- L185 _enumerator_ `SYMS_MachFlags_PREBINDABLE = 0x800` (scope `__anon50ef864c0a03`)
- L186 _enumerator_ `SYMS_MachFlags_ALLMODSBOUND = 0x1000` (scope `__anon50ef864c0a03`)
- L187 _enumerator_ `SYMS_MachFlags_SUBSECTIONS_VIA_SYMBOLS = 0x2000` (scope `__anon50ef864c0a03`)
- L188 _enumerator_ `SYMS_MachFlags_CANONICAL = 0x4000` (scope `__anon50ef864c0a03`)
- L189 _enumerator_ `SYMS_MachFlags_WEAK_DEFINES = 0x8000` (scope `__anon50ef864c0a03`)
- L190 _enumerator_ `SYMS_MachFlags_BINDS_TO_WEAK = 0x10000` (scope `__anon50ef864c0a03`)
- L191 _enumerator_ `SYMS_MachFlags_ALLOW_STACK_EXECUTION = 0x20000` (scope `__anon50ef864c0a03`)
- L192 _enumerator_ `SYMS_MachFlags_ROOT_SAFE = 0x40000` (scope `__anon50ef864c0a03`)
- L193 _enumerator_ `SYMS_MachFlags_SETUID_SAFE = 0x80000` (scope `__anon50ef864c0a03`)
- L194 _enumerator_ `SYMS_MachFlags_NO_REEXPORTED_DYLIBS = 0x100000` (scope `__anon50ef864c0a03`)
- L195 _enumerator_ `SYMS_MachFlags_PIE = 0x200000` (scope `__anon50ef864c0a03`)
- L196 _enumerator_ `SYMS_MachFlags_STRIPPABLE_DYLIB = 0x400000` (scope `__anon50ef864c0a03`)
- L197 _enumerator_ `SYMS_MachFlags_HAS_TLV_DESRIPTORS = 0x800000` (scope `__anon50ef864c0a03`)
- L198 _enumerator_ `SYMS_MachFlags_NO_HEAP_EXECUTION = 0x1000000` (scope `__anon50ef864c0a03`)
- L199 _enumerator_ `SYMS_MachFlags_COUNT = 25` (scope `__anon50ef864c0a03`)
- L201 _typedef_ `typedef SYMS_S32 SYMS_MachLoadCommandType;`
- L203 _enumerator_ `SYMS_MachLoadCommandType_SEGMENT = 0x1` (scope `__anon50ef864c0b03`)
- L204 _enumerator_ `SYMS_MachLoadCommandType_SYMTAB = 0x2` (scope `__anon50ef864c0b03`)
- L205 _enumerator_ `SYMS_MachLoadCommandType_SYMSEG = 0x3` (scope `__anon50ef864c0b03`)
- L207 _enumerator_ `SYMS_MachLoadCommandType_THREAD = 0x4` (scope `__anon50ef864c0b03`) — gdb symbol table (obsolete)
- L208 _enumerator_ `SYMS_MachLoadCommandType_UNIXTHREAD = 0x5` (scope `__anon50ef864c0b03`)
- L209 _enumerator_ `SYMS_MachLoadCommandType_LOADFVMLIB = 0x6` (scope `__anon50ef864c0b03`)
- L210 _enumerator_ `SYMS_MachLoadCommandType_IDFVMLIB = 0x7` (scope `__anon50ef864c0b03`)
- L211 _enumerator_ `SYMS_MachLoadCommandType_IDENT = 0x8` (scope `__anon50ef864c0b03`)
- L213 _enumerator_ `SYMS_MachLoadCommandType_FVMFILE = 0x9` (scope `__anon50ef864c0b03`) — object identification info (obsolete)
- L214 _enumerator_ `SYMS_MachLoadCommandType_PREPAGE = 0xA` (scope `__anon50ef864c0b03`)
- L215 _enumerator_ `SYMS_MachLoadCommandType_DYSYMTAB = 0xB` (scope `__anon50ef864c0b03`)
- L216 _enumerator_ `SYMS_MachLoadCommandType_LOAD_DYLIB = 0xC` (scope `__anon50ef864c0b03`)
- L217 _enumerator_ `SYMS_MachLoadCommandType_ID_DYLIB = 0xD` (scope `__anon50ef864c0b03`)
- L218 _enumerator_ `SYMS_MachLoadCommandType_LOAD_DYLINKER = 0xE` (scope `__anon50ef864c0b03`)
- L219 _enumerator_ `SYMS_MachLoadCommandType_ID_DYLINKER = 0xF` (scope `__anon50ef864c0b03`)
- L220 _enumerator_ `SYMS_MachLoadCommandType_PREBOUND_DYLIB = 0x10` (scope `__anon50ef864c0b03`)
- L221 _enumerator_ `SYMS_MachLoadCommandType_ROUTINES = 0x11` (scope `__anon50ef864c0b03`)
- L222 _enumerator_ `SYMS_MachLoadCommandType_SUB_FRAMEWORK = 0x12` (scope `__anon50ef864c0b03`)
- L223 _enumerator_ `SYMS_MachLoadCommandType_SUB_UMBRELLA = 0x13` (scope `__anon50ef864c0b03`)
- L224 _enumerator_ `SYMS_MachLoadCommandType_SUB_CLIENT = 0x14` (scope `__anon50ef864c0b03`)
- L225 _enumerator_ `SYMS_MachLoadCommandType_SUB_LIBRARY = 0x15` (scope `__anon50ef864c0b03`)
- L226 _enumerator_ `SYMS_MachLoadCommandType_TWOLEVEL_HINTS = 0x16` (scope `__anon50ef864c0b03`)
- L227 _enumerator_ `SYMS_MachLoadCommandType_PREBIND_CHKSUM = 0x17` (scope `__anon50ef864c0b03`)
- L228 _enumerator_ `SYMS_MachLoadCommandType_LOAD_WEAK_DYLIB = 0x80000018` (scope `__anon50ef864c0b03`)
- L230 _enumerator_ `SYMS_MachLoadCommandType_SEGMENT_64 = 0x19` (scope `__anon50ef864c0b03`) — dylib is allowed to be missing
- L231 _enumerator_ `SYMS_MachLoadCommandType_ROUTINES_64 = 0x1A` (scope `__anon50ef864c0b03`)
- L232 _enumerator_ `SYMS_MachLoadCommandType_UUID = 0x1B` (scope `__anon50ef864c0b03`)
- L233 _enumerator_ `SYMS_MachLoadCommandType_RPATH = 0x8000001C` (scope `__anon50ef864c0b03`)
- L234 _enumerator_ `SYMS_MachLoadCommandType_CODE_SIGNATURE = 0x1D` (scope `__anon50ef864c0b03`)
- L235 _enumerator_ `SYMS_MachLoadCommandType_SEGMENT_SPLIT_INFO = 0x1E` (scope `__anon50ef864c0b03`)
- L236 _enumerator_ `SYMS_MachLoadCommandType_REEXPORT_DYLIB = 0x8000001F` (scope `__anon50ef864c0b03`)
- L237 _enumerator_ `SYMS_MachLoadCommandType_LAZY_LOAD_DYLIB = 0x20` (scope `__anon50ef864c0b03`)
- L238 _enumerator_ `SYMS_MachLoadCommandType_ENCRYPTION_INFO = 0x21` (scope `__anon50ef864c0b03`)
- L239 _enumerator_ `SYMS_MachLoadCommandType_DYLD_INFO = 0x22` (scope `__anon50ef864c0b03`)
- L240 _enumerator_ `SYMS_MachLoadCommandType_DYLD_INFO_ONLY = 0x80000022` (scope `__anon50ef864c0b03`)
- L241 _enumerator_ `SYMS_MachLoadCommandType_LOAD_UPWARD_DYLIB = 0x80000023` (scope `__anon50ef864c0b03`)
- L242 _enumerator_ `SYMS_MachLoadCommandType_VERSION_MIN_MACOSX = 0x24` (scope `__anon50ef864c0b03`)
- L243 _enumerator_ `SYMS_MachLoadCommandType_VERSION_MIN_IPHONES = 0x25` (scope `__anon50ef864c0b03`)
- L244 _enumerator_ `SYMS_MachLoadCommandType_FUNCTION_STARTS = 0x26` (scope `__anon50ef864c0b03`)
- L245 _enumerator_ `SYMS_MachLoadCommandType_DYLD_ENVIORNMENT = 0x27` (scope `__anon50ef864c0b03`)
- L246 _enumerator_ `SYMS_MachLoadCommandType_MAIN = 0x80000028` (scope `__anon50ef864c0b03`)
- L247 _enumerator_ `SYMS_MachLoadCommandType_DATA_IN_CODE = 0x29` (scope `__anon50ef864c0b03`)
- L248 _enumerator_ `SYMS_MachLoadCommandType_SOURCE_VERSION = 0x2A` (scope `__anon50ef864c0b03`)
- L249 _enumerator_ `SYMS_MachLoadCommandType_DYLIB_CODE_SIGN_DRS = 0x2B` (scope `__anon50ef864c0b03`)
- L250 _enumerator_ `SYMS_MachLoadCommandType_ENCRYPTION_INFO_64 = 0x2C` (scope `__anon50ef864c0b03`)
- L251 _enumerator_ `SYMS_MachLoadCommandType_LINKER_OPTION = 0x2D` (scope `__anon50ef864c0b03`)
- L252 _enumerator_ `SYMS_MachLoadCommandType_LINKER_OPTIMIZATION_HINT = 0x2E` (scope `__anon50ef864c0b03`)
- L253 _enumerator_ `SYMS_MachLoadCommandType_VERSION_MIN_TVOS = 0x2F` (scope `__anon50ef864c0b03`)
- L254 _enumerator_ `SYMS_MachLoadCommandType_VERSION_MIN_WATCHOS = 0x30` (scope `__anon50ef864c0b03`)
- L255 _enumerator_ `SYMS_MachLoadCommandType_NOTE = 0x31` (scope `__anon50ef864c0b03`)
- L256 _enumerator_ `SYMS_MachLoadCommandType_BUILD_VERSION = 0x32` (scope `__anon50ef864c0b03`)
- L257 _enumerator_ `SYMS_MachLoadCommandType_COUNT = 51` (scope `__anon50ef864c0b03`)
- L259 _typedef_ `typedef SYMS_U32 SYMS_MachSectionType;`
- L261 _enumerator_ `SYMS_MachSectionType_REGULAR = 0x0` (scope `__anon50ef864c0c03`)
- L262 _enumerator_ `SYMS_MachSectionType_ZEROFILL = 0x1` (scope `__anon50ef864c0c03`)
- L263 _enumerator_ `SYMS_MachSectionType_CSTRING_LITERAL = 0x2` (scope `__anon50ef864c0c03`)
- L264 _enumerator_ `SYMS_MachSectionType_FOUR_BYTE_LITERALS = 0x3` (scope `__anon50ef864c0c03`)
- L266 _enumerator_ `SYMS_MachSectionType_EIGHT_BYTE_LITERALS = 0x4` (scope `__anon50ef864c0c03`) — TODO: number prefix
- L268 _enumerator_ `SYMS_MachSectionType_LITERAL_POINTERS = 0x5` (scope `__anon50ef864c0c03`) — TODO: number prefix
- L269 _enumerator_ `SYMS_MachSectionType_NON_LAZY_SYMBOL_POINTERS = 0x6` (scope `__anon50ef864c0c03`)
- L270 _enumerator_ `SYMS_MachSectionType_LAZY_SYMBOL_POINTERS = 0x7` (scope `__anon50ef864c0c03`)
- L271 _enumerator_ `SYMS_MachSectionType_SYMBOL_STUBS = 0x8` (scope `__anon50ef864c0c03`)
- L272 _enumerator_ `SYMS_MachSectionType_MOD_INIT_FUNC_POINTERS = 0x9` (scope `__anon50ef864c0c03`)
- L273 _enumerator_ `SYMS_MachSectionType_MOD_TERM_FUNC_POINTERS = 0xA` (scope `__anon50ef864c0c03`)
- L274 _enumerator_ `SYMS_MachSectionType_COALESCED = 0xB` (scope `__anon50ef864c0c03`)
- L275 _enumerator_ `SYMS_MachSectionType_GB_ZERO_FILL = 0xC` (scope `__anon50ef864c0c03`)
- L276 _enumerator_ `SYMS_MachSectionType_INTERPOSING = 0xD` (scope `__anon50ef864c0c03`)
- L277 _enumerator_ `SYMS_MachSectionType_SIXTEENBYTE_LITERALS = 0xE` (scope `__anon50ef864c0c03`)
- L279 _enumerator_ `SYMS_MachSectionType_DTRACE_DOF = 0xF` (scope `__anon50ef864c0c03`) — TODO: number prefix
- L280 _enumerator_ `SYMS_MachSectionType_LAZY_DLIB_SYMBOL_POINTERS = 0x10` (scope `__anon50ef864c0c03`)
- L281 _enumerator_ `SYMS_MachSectionType_THREAD_LOCAL_REGULAR = 0x11` (scope `__anon50ef864c0c03`)
- L282 _enumerator_ `SYMS_MachSectionType_THREAD_LOCAL_ZEROFILL = 0x12` (scope `__anon50ef864c0c03`)
- L283 _enumerator_ `SYMS_MachSectionType_THREAD_LOCAL_VARIABLES = 0x13` (scope `__anon50ef864c0c03`)
- L284 _enumerator_ `SYMS_MachSectionType_THREAD_LOCAL_VARIABLES_POINTERS = 0x14` (scope `__anon50ef864c0c03`)
- L285 _enumerator_ `SYMS_MachSectionType_LOCAL_INIT_FUNCTION_POINTERS = 0x15` (scope `__anon50ef864c0c03`)
- L286 _enumerator_ `SYMS_MachSectionType_COUNT = 22` (scope `__anon50ef864c0c03`)
- L288 _typedef_ `typedef SYMS_S32 SYMS_MachSectionAttr;`
- L290 _enumerator_ `SYMS_MachSectionAttr_USR = 0xff000000` (scope `__anon50ef864c0d03`)
- L291 _enumerator_ `SYMS_MachSectionAttr_SYSTEM = 0x00ffff00` (scope `__anon50ef864c0d03`)
- L292 _enumerator_ `SYMS_MachSectionAttr_PURE_INSTRUCTIONS = 0x80000000` (scope `__anon50ef864c0d03`)
- L293 _enumerator_ `SYMS_MachSectionAttr_NO_TOC = 0x40000000` (scope `__anon50ef864c0d03`)
- L294 _enumerator_ `SYMS_MachSectionAttr_STRIP_STATIC_SYMS = 0x20000000` (scope `__anon50ef864c0d03`)
- L295 _enumerator_ `SYMS_MachSectionAttr_NO_DEAD_STRIP = 0x10000000` (scope `__anon50ef864c0d03`)
- L296 _enumerator_ `SYMS_MachSectionAttr_LIVE_SUPPORT = 0x08000000` (scope `__anon50ef864c0d03`)
- L297 _enumerator_ `SYMS_MachSectionAttr_SELF_MODIFYING_CODE = 0x04000000` (scope `__anon50ef864c0d03`)
- L298 _enumerator_ `SYMS_MachSectionAttr_DEBUG = 0x02000000` (scope `__anon50ef864c0d03`)
- L299 _enumerator_ `SYMS_MachSectionAttr_SOME_INSTRUCTIONS = 0x00000400` (scope `__anon50ef864c0d03`)
- L300 _enumerator_ `SYMS_MachSectionAttr_SECTION_RELOC = 0x00000200` (scope `__anon50ef864c0d03`)
- L301 _enumerator_ `SYMS_MachSectionAttr_LOC_RELOC = 0x00000100` (scope `__anon50ef864c0d03`)
- L302 _enumerator_ `SYMS_MachSectionAttr_COUNT = 12` (scope `__anon50ef864c0d03`)
- L304 _typedef_ `typedef SYMS_U32 SYMS_MachPlatformType;`
- L306 _enumerator_ `SYMS_MachPlatformType_MACOS = 0x1` (scope `__anon50ef864c0e03`)
- L307 _enumerator_ `SYMS_MachPlatformType_IOS = 0x2` (scope `__anon50ef864c0e03`)
- L308 _enumerator_ `SYMS_MachPlatformType_TVOS = 0x3` (scope `__anon50ef864c0e03`)
- L309 _enumerator_ `SYMS_MachPlatformType_WATCHOS = 0x4` (scope `__anon50ef864c0e03`)
- L310 _enumerator_ `SYMS_MachPlatformType_COUNT = 4` (scope `__anon50ef864c0e03`)
- L312 _typedef_ `typedef SYMS_U32 SYMS_MachToolType;`
- L314 _enumerator_ `SYMS_MachToolType_CLANG = 0x1` (scope `__anon50ef864c0f03`)
- L315 _enumerator_ `SYMS_MachToolType_SWITFT = 0x2` (scope `__anon50ef864c0f03`)
- L316 _enumerator_ `SYMS_MachToolType_LD = 0x3` (scope `__anon50ef864c0f03`)
- L317 _enumerator_ `SYMS_MachToolType_COUNT = 3` (scope `__anon50ef864c0f03`)
- L319 _typedef_ `typedef SYMS_U8 SYMS_MachBindType;`
- L321 _enumerator_ `SYMS_MachBindType_POINTER = 0x1` (scope `__anon50ef864c1003`)
- L322 _enumerator_ `SYMS_MachBindType_TEXT_ABSOLUTE32 = 0x2` (scope `__anon50ef864c1003`)
- L323 _enumerator_ `SYMS_MachBindType_PCREL32 = 0x3` (scope `__anon50ef864c1003`)
- L324 _enumerator_ `SYMS_MachBindType_COUNT = 3` (scope `__anon50ef864c1003`)
- L326 _typedef_ `typedef SYMS_U8 SYMS_MachBindOpcode;`
- L328 _enumerator_ `SYMS_MachBindOpcode_DONE = 0x00` (scope `__anon50ef864c1103`)
- L329 _enumerator_ `SYMS_MachBindOpcode_SET_DYLIB_ORDINAL_IMM = 0x10` (scope `__anon50ef864c1103`)
- L330 _enumerator_ `SYMS_MachBindOpcode_SET_DYLIB_ORDINAL_ULEB = 0x20` (scope `__anon50ef864c1103`)
- L331 _enumerator_ `SYMS_MachBindOpcode_SET_DYLIB_SPECIAL_IMM = 0x30` (scope `__anon50ef864c1103`)
- L332 _enumerator_ `SYMS_MachBindOpcode_SET_SYMBOL_TRAILING_FLAGS_IMM = 0x40` (scope `__anon50ef864c1103`)
- L333 _enumerator_ `SYMS_MachBindOpcode_SET_TYPE_IMM = 0x50` (scope `__anon50ef864c1103`)
- L334 _enumerator_ `SYMS_MachBindOpcode_SET_ADDEND_SLEB = 0x60` (scope `__anon50ef864c1103`)
- L335 _enumerator_ `SYMS_MachBindOpcode_SET_SEGMENT_AND_OFFSET_ULEB = 0x70` (scope `__anon50ef864c1103`)
- L336 _enumerator_ `SYMS_MachBindOpcode_ADD_ADDR_ULEB = 0x80` (scope `__anon50ef864c1103`)
- L337 _enumerator_ `SYMS_MachBindOpcode_DO_BIND = 0x90` (scope `__anon50ef864c1103`)
- L338 _enumerator_ `SYMS_MachBindOpcode_DO_BIND_ADD_ADDR_ULEB = 0xA0` (scope `__anon50ef864c1103`)
- L339 _enumerator_ `SYMS_MachBindOpcode_DO_BIND_ADD_ADDR_IMM_SCALED = 0xB0` (scope `__anon50ef864c1103`)
- L340 _enumerator_ `SYMS_MachBindOpcode_DO_BIND_ULEB_TIMES_SKIPPING_ULEB = 0xC0` (scope `__anon50ef864c1103`)
- L341 _enumerator_ `SYMS_MachBindOpcode_MASK = 0xF0` (scope `__anon50ef864c1103`)
- L342 _enumerator_ `SYMS_MachBindOpcode_IMM_MASK = 0xF` (scope `__anon50ef864c1103`)
- L343 _enumerator_ `SYMS_MachBindOpcode_COUNT = 15` (scope `__anon50ef864c1103`)
- L345 _typedef_ `typedef SYMS_U32 SYMS_MachBindSymbolFlags;`
- L347 _enumerator_ `SYMS_MachBindSymbolFlags_WEAK_IMPORT = (1 << 0)` (scope `__anon50ef864c1203`)
- L348 _enumerator_ `SYMS_MachBindSymbolFlags_NON_WEAK_DEFINITION = (1 << 3)` (scope `__anon50ef864c1203`)
- L350 _typedef_ `typedef SYMS_S8 SYMS_MachBindSpecialDylib;`
- L352 _enumerator_ `SYMS_MachBindSpecialDylib_SELF = 0` (scope `__anon50ef864c1303`)
- L353 _enumerator_ `SYMS_MachBindSpecialDylib_MAIN_EXECUTABLE = 0xff` (scope `__anon50ef864c1303`)
- L354 _enumerator_ `SYMS_MachBindSpecialDylib_FLAT_LOOKUP = 0xfe` (scope `__anon50ef864c1303`)
- L355 _enumerator_ `SYMS_MachBindSpecialDylib_COUNT = 3` (scope `__anon50ef864c1303`)
- L357 _typedef_ `typedef SYMS_U32 SYMS_MachNListType;`
- L359 _enumerator_ `SYMS_MachNListType_UNDF = 0x0` (scope `__anon50ef864c1403`)
- L360 _enumerator_ `SYMS_MachNListType_ABS = 0x2` (scope `__anon50ef864c1403`)
- L361 _enumerator_ `SYMS_MachNListType_SECT = 0xE` (scope `__anon50ef864c1403`)
- L362 _enumerator_ `SYMS_MachNListType_PBUD = 0xC` (scope `__anon50ef864c1403`)
- L363 _enumerator_ `SYMS_MachNListType_INDR = 0xA` (scope `__anon50ef864c1403`)
- L364 _enumerator_ `SYMS_MachNListType_COUNT = 5` (scope `__anon50ef864c1403`)
- L366 _typedef_ `typedef SYMS_U32 SYMS_MachStabType;`
- L368 _enumerator_ `SYMS_MachStabType_GSYM = 0x20` (scope `__anon50ef864c1503`)
- L369 _enumerator_ `SYMS_MachStabType_FNAME = 0x22` (scope `__anon50ef864c1503`)
- L370 _enumerator_ `SYMS_MachStabType_FUN = 0x24` (scope `__anon50ef864c1503`)
- L371 _enumerator_ `SYMS_MachStabType_STSYM = 0x26` (scope `__anon50ef864c1503`)
- L372 _enumerator_ `SYMS_MachStabType_LCSYM = 0x28` (scope `__anon50ef864c1503`)
- L373 _enumerator_ `SYMS_MachStabType_BNSYM = 0x2E` (scope `__anon50ef864c1503`)
- L374 _enumerator_ `SYMS_MachStabType_AST = 0x32` (scope `__anon50ef864c1503`)
- L375 _enumerator_ `SYMS_MachStabType_OPT = 0x3C` (scope `__anon50ef864c1503`)
- L376 _enumerator_ `SYMS_MachStabType_RSYM = 0x40` (scope `__anon50ef864c1503`)
- L377 _enumerator_ `SYMS_MachStabType_SLINE = 0x44` (scope `__anon50ef864c1503`)
- L378 _enumerator_ `SYMS_MachStabType_ENSYM = 0x4E` (scope `__anon50ef864c1503`)
- L379 _enumerator_ `SYMS_MachStabType_SSYM = 0x60` (scope `__anon50ef864c1503`)
- L380 _enumerator_ `SYMS_MachStabType_SO = 0x64` (scope `__anon50ef864c1503`)
- L381 _enumerator_ `SYMS_MachStabType_OSO = 0x66` (scope `__anon50ef864c1503`)
- L382 _enumerator_ `SYMS_MachStabType_LSYM = 0x80` (scope `__anon50ef864c1503`)
- L383 _enumerator_ `SYMS_MachStabType_BINCL = 0x82` (scope `__anon50ef864c1503`)
- L384 _enumerator_ `SYMS_MachStabType_SOL = 0x84` (scope `__anon50ef864c1503`)
- L385 _enumerator_ `SYMS_MachStabType_PARAMS = 0x86` (scope `__anon50ef864c1503`)
- L386 _enumerator_ `SYMS_MachStabType_VERSION = 0x88` (scope `__anon50ef864c1503`)
- L387 _enumerator_ `SYMS_MachStabType_OLEVEL = 0x8A` (scope `__anon50ef864c1503`)
- L388 _enumerator_ `SYMS_MachStabType_PSYM = 0xA0` (scope `__anon50ef864c1503`)
- L389 _enumerator_ `SYMS_MachStabType_EINCL = 0xA2` (scope `__anon50ef864c1503`)
- L390 _enumerator_ `SYMS_MachStabType_ENTRY = 0xA4` (scope `__anon50ef864c1503`)
- L391 _enumerator_ `SYMS_MachStabType_LBRAC = 0xC0` (scope `__anon50ef864c1503`)
- L392 _enumerator_ `SYMS_MachStabType_EXCL = 0xC2` (scope `__anon50ef864c1503`)
- L393 _enumerator_ `SYMS_MachStabType_RBRAC = 0xE0` (scope `__anon50ef864c1503`)
- L394 _enumerator_ `SYMS_MachStabType_BCOMM = 0xE2` (scope `__anon50ef864c1503`)
- L395 _enumerator_ `SYMS_MachStabType_ECOMM = 0xE4` (scope `__anon50ef864c1503`)
- L396 _enumerator_ `SYMS_MachStabType_ECOML = 0xE8` (scope `__anon50ef864c1503`)
- L397 _enumerator_ `SYMS_MachStabType_LENG = 0xFE` (scope `__anon50ef864c1503`)
- L398 _enumerator_ `SYMS_MachStabType_COUNT = 30` (scope `__anon50ef864c1503`)
- L400 _typedef_ `typedef SYMS_U64 SYMS_MachExportSymbolKind;`
- L402 _enumerator_ `SYMS_MachExportSymbolKind_REGULAR = 0` (scope `__anon50ef864c1603`)
- L403 _enumerator_ `SYMS_MachExportSymbolKind_THREAD_LOCAL = 1` (scope `__anon50ef864c1603`)
- L404 _enumerator_ `SYMS_MachExportSymbolKind_ABSOLUTE = 2` (scope `__anon50ef864c1603`)
- L405 _enumerator_ `SYMS_MachExportSymbolKind_COUNT = 3` (scope `__anon50ef864c1603`)
- L407 _typedef_ `typedef SYMS_U64 SYMS_MachExportSymbolFlags;`
- L409 _enumerator_ `SYMS_MachExportSymbolFlags_KIND_MASK = (1 << 2)` (scope `__anon50ef864c1703`)
- L410 _enumerator_ `SYMS_MachExportSymbolFlags_WEAK_DEFINITION = (1 << 2)` (scope `__anon50ef864c1703`)
- L411 _enumerator_ `SYMS_MachExportSymbolFlags_REEXPORT = (1 << 3)` (scope `__anon50ef864c1703`)
- L412 _enumerator_ `SYMS_MachExportSymbolFlags_STUB_AND_RESOLVED = (1 << 4)` (scope `__anon50ef864c1703`)
- L417 _typedef_ `} SYMS_MachLCStr;`
- L422 _typedef_ `} SYMS_MachUUID;`
- L428 _typedef_ `} SYMS_MachDylib;`
- L433 _typedef_ `} SYMS_MachDylibCommand;`
- L447 _typedef_ `} SYMS_MachDyldInfoCommand;`
- L451 _typedef_ `} SYMS_MachLoadCommand;`
- L455 _typedef_ `} SYMS_MachFatHeader;`
- L462 _typedef_ `} SYMS_MachFatArch;`
- L471 _typedef_ `} SYMS_MachHeader32;`
- L481 _typedef_ `} SYMS_MachHeader64;`
- L493 _typedef_ `} SYMS_MachSegmentCommand32;`
- L505 _typedef_ `} SYMS_MachSegmentCommand64;`
- L518 _typedef_ `} SYMS_MachSection32;`
- L532 _typedef_ `} SYMS_MachSection64;`
- L543 _typedef_ `} SYMS_MachSymtabCommand;`
- L565 _typedef_ `} SYMS_MachDySymtabCommand;`
- L572 _typedef_ `} SYMS_MachNList32;`
- L579 _typedef_ `} SYMS_MachNList64;`
- L587 _typedef_ `} SYMS_MachBuildVersionCommand;`
- L591 _typedef_ `} SYMS_MachBuildToolVersion;`
- L597 _typedef_ `} SYMS_MachVersionMin;`
- L602 _typedef_ `} SYMS_MachDylinker;`
- L608 _typedef_ `} SYMS_MachPreboundDylibCommand;`
- L620 _typedef_ `} SYMS_MachRoutinesCommand;`
- L632 _typedef_ `} SYMS_MachRoutines64Command;`
- L637 _typedef_ `} SYMS_MachSubFrameworkCommand;`
- L642 _typedef_ `} SYMS_MachSubUmbrellaCommand;`
- L647 _typedef_ `} SYMS_MachSubClientCommand;`
- L652 _typedef_ `} SYMS_MachSubLibraryCommand;`
- L658 _typedef_ `} SYMS_MachTwoLevelHintsCommand;`
- L659 _typedef_ `typedef SYMS_U32 SYMS_MachTwoLevelHint;`
- L661 _enumerator_ `SYMS_MachTwoLevelHint_isub_image_SHIFT = 0` (scope `__anon50ef864c1803`)
- L661 _enumerator_ `SYMS_MachTwoLevelHint_isub_image_SHIFT = 0` (scope `__anon50ef864c1803`)
- L662 _enumerator_ `SYMS_MachTwoLevelHint_itoc_SHIFT = 8` (scope `__anon50ef864c1803`)
- L662 _enumerator_ `SYMS_MachTwoLevelHint_itoc_SHIFT = 8` (scope `__anon50ef864c1803`)
- L664 _macro_ `#define SYMS_MachTwoLevelHint_Extract_isub_image(f) (SYMS_U32)(((f) >> SYMS_MachTwoLevelHint_isub_image_SHIFT) & SYMS_MachTwoLevelHint_isub_image_MASK)`
- L665 _macro_ `#define SYMS_MachTwoLevelHint_Extract_itoc(f) (SYMS_U32)(((f) >> SYMS_MachTwoLevelHint_itoc_SHIFT) & SYMS_MachTwoLevelHint_itoc_MASK)`
- L670 _typedef_ `} SYMS_MachPrebindChecksumCommand;`
- L675 _typedef_ `} SYMS_MachRPathCommand;`
- L681 _typedef_ `} SYMS_MachLinkeditDataCommand;`
- L688 _typedef_ `} SYMS_MachEncryptionInfoCommand;`
- L696 _typedef_ `} SYMS_MachEncryptionInfo64Command;`
- L702 _typedef_ `} SYMS_MachEntryPointCommand;`
- L707 _typedef_ `} SYMS_MachSourceVersionCommand;`
- L712 _typedef_ `} SYMS_MachLinkerOptionCommand;`
- L719 _typedef_ `} SYMS_MachNoteCommand;`
- L725 _typedef_ `} SYMS_MachSymSegCommand;`
- L730 _typedef_ `} SYMS_MachFvmlib;`
- L735 _typedef_ `} SYMS_MachFvmlibCommand;`
- L739 _typedef_ `} SYMS_MachThreadCommand;`
- L740 _typedef_ `typedef SYMS_U32 SYMS_MachUnwindEncModeX86;`
- L742 _enumerator_ `SYMS_MachUnwindEncModeX86_EBP_FRAME = 1` (scope `__anon50ef864c1903`)
- L743 _enumerator_ `SYMS_MachUnwindEncModeX86_STACK_IMMD = 2` (scope `__anon50ef864c1903`)
- L744 _enumerator_ `SYMS_MachUnwindEncModeX86_STACK_IND = 3` (scope `__anon50ef864c1903`)
- L745 _enumerator_ `SYMS_MachUnwindEncModeX86_DWARF = 4` (scope `__anon50ef864c1903`)
- L746 _enumerator_ `SYMS_MachUnwindEncModeX86_COUNT = 4` (scope `__anon50ef864c1903`)
- L748 _typedef_ `typedef SYMS_U32 SYMS_MachUnwindRegisterX86;`
- L750 _enumerator_ `SYMS_MachUnwindRegisterX86_NONE = 0` (scope `__anon50ef864c1a03`)
- L751 _enumerator_ `SYMS_MachUnwindRegisterX86_EBX = 1` (scope `__anon50ef864c1a03`)
- L752 _enumerator_ `SYMS_MachUnwindRegisterX86_ECX = 2` (scope `__anon50ef864c1a03`)
- L753 _enumerator_ `SYMS_MachUnwindRegisterX86_EDX = 3` (scope `__anon50ef864c1a03`)
- L754 _enumerator_ `SYMS_MachUnwindRegisterX86_EDI = 4` (scope `__anon50ef864c1a03`)
- L755 _enumerator_ `SYMS_MachUnwindRegisterX86_ESI = 5` (scope `__anon50ef864c1a03`)
- L756 _enumerator_ `SYMS_MachUnwindRegisterX86_EBP = 6` (scope `__anon50ef864c1a03`)
- L757 _enumerator_ `SYMS_MachUnwindRegisterX86_COUNT = 7` (scope `__anon50ef864c1a03`)
- L759 _typedef_ `typedef SYMS_U32 SYMS_MachUnwindEncX86;`
- L761 _enumerator_ `SYMS_MachUnwindEncX86_MODE_MASK_SHIFT = 4` (scope `__anon50ef864c1b03`)
- L761 _enumerator_ `SYMS_MachUnwindEncX86_MODE_MASK_SHIFT = 4` (scope `__anon50ef864c1b03`)
- L762 _enumerator_ `SYMS_MachUnwindEncX86_EBP_FRAME_REGISTER = (1 << 15)` (scope `__anon50ef864c1b03`)
- L763 _enumerator_ `SYMS_MachUnwindEncX86_EBP_FRAME_OFFSET_SHIFT = 8` (scope `__anon50ef864c1b03`)
- L763 _enumerator_ `SYMS_MachUnwindEncX86_EBP_FRAME_OFFSET_SHIFT = 8` (scope `__anon50ef864c1b03`)
- L764 _enumerator_ `SYMS_MachUnwindEncX86_FRAMELESS_STACK_SIZE_SHIFT = 8` (scope `__anon50ef864c1b03`)
- L764 _enumerator_ `SYMS_MachUnwindEncX86_FRAMELESS_STACK_SIZE_SHIFT = 8` (scope `__anon50ef864c1b03`)
- L765 _enumerator_ `SYMS_MachUnwindEncX86_FRAMELESS_STACK_ADJUST_SHIFT = 3` (scope `__anon50ef864c1b03`)
- L765 _enumerator_ `SYMS_MachUnwindEncX86_FRAMELESS_STACK_ADJUST_SHIFT = 3` (scope `__anon50ef864c1b03`)
- L766 _enumerator_ `SYMS_MachUnwindEncX86_FRAMELESS_REG_COUNT_SHIFT = 3` (scope `__anon50ef864c1b03`)
- L766 _enumerator_ `SYMS_MachUnwindEncX86_FRAMELESS_REG_COUNT_SHIFT = 3` (scope `__anon50ef864c1b03`)
- L767 _enumerator_ `SYMS_MachUnwindEncX86_FRAMELESS_REG_PERMUTATION = (1 << 10)` (scope `__anon50ef864c1b03`)
- L768 _enumerator_ `SYMS_MachUnwindEncX86_DWARF_SECTION_OFFSET = (1 << 24)` (scope `__anon50ef864c1b03`)
- L770 _macro_ `#define SYMS_MachUnwindEncX86_Extract_MODE_MASK(f) (SYMS_MachUnwindEncModeX86)(((f) >> SYMS_MachUnwindEncX86_MODE_MASK_SHIFT) & SYMS_MachUnwindEncX86_MODE_MASK_MASK)`
- L771 _macro_ `#define SYMS_MachUnwindEncX86_Extract_EBP_FRAME_OFFSET(f) (SYMS_U32)(((f) >> SYMS_MachUnwindEncX86_EBP_FRAME_OFFSET_SHIFT) & SYMS_MachUnwindEncX86_EBP_FRAME_OFFSET_MASK)`
- L772 _macro_ `#define SYMS_MachUnwindEncX86_Extract_FRAMELESS_STACK_SIZE(f) (SYMS_U32)(((f) >> SYMS_MachUnwindEncX86_FRAMELESS_STACK_SIZE_SHIFT) & SYMS_MachUnwindEncX86_FRAMELESS_STACK_SIZE_MASK)`
- L773 _macro_ `#define SYMS_MachUnwindEncX86_Extract_FRAMELESS_STACK_ADJUST(f) (SYMS_U32)(((f) >> SYMS_MachUnwindEncX86_FRAMELESS_STACK_ADJUST_SHIFT) & SYMS_MachUnwindEncX86_FRAMELESS_STACK_ADJUST_MASK)`
- L774 _macro_ `#define SYMS_MachUnwindEncX86_Extract_FRAMELESS_REG_COUNT(f) (SYMS_U32)(((f) >> SYMS_MachUnwindEncX86_FRAMELESS_REG_COUNT_SHIFT) & SYMS_MachUnwindEncX86_FRAMELESS_REG_COUNT_MASK)`
- L775 _typedef_ `typedef SYMS_U32 SYMS_MachUnwindEncModeX64;`
- L777 _enumerator_ `SYMS_MachUnwindEncModeX64_RBP_FRAME = 1` (scope `__anon50ef864c1c03`)
- L778 _enumerator_ `SYMS_MachUnwindEncModeX64_STACK_IMMD = 2` (scope `__anon50ef864c1c03`)
- L779 _enumerator_ `SYMS_MachUnwindEncModeX64_STACK_IND = 3` (scope `__anon50ef864c1c03`)
- L780 _enumerator_ `SYMS_MachUnwindEncModeX64_DWARF = 4` (scope `__anon50ef864c1c03`)
- L781 _enumerator_ `SYMS_MachUnwindEncModeX64_COUNT = 4` (scope `__anon50ef864c1c03`)
- L783 _typedef_ `typedef SYMS_U32 SYMS_MachUnwindRegisterX64;`
- L785 _enumerator_ `SYMS_MachUnwindRegisterX64_NONE = 0` (scope `__anon50ef864c1d03`)
- L786 _enumerator_ `SYMS_MachUnwindRegisterX64_RBX = 1` (scope `__anon50ef864c1d03`)
- L787 _enumerator_ `SYMS_MachUnwindRegisterX64_R12 = 2` (scope `__anon50ef864c1d03`)
- L788 _enumerator_ `SYMS_MachUnwindRegisterX64_R13 = 3` (scope `__anon50ef864c1d03`)
- L789 _enumerator_ `SYMS_MachUnwindRegisterX64_R14 = 4` (scope `__anon50ef864c1d03`)
- L790 _enumerator_ `SYMS_MachUnwindRegisterX64_R15 = 5` (scope `__anon50ef864c1d03`)
- L791 _enumerator_ `SYMS_MachUnwindRegisterX64_RBP = 6` (scope `__anon50ef864c1d03`)
- L792 _enumerator_ `SYMS_MachUnwindRegisterX64_COUNT = 7` (scope `__anon50ef864c1d03`)
- L798 _prototype_ `SYMS_Arch syms_mach_arch_from_cputype(SYMS_MachCpuType v);`
- L803 _prototype_ `void syms_bswap_in_place__SYMS_MachLCStr(SYMS_MachLCStr *v);`
- L804 _prototype_ `void syms_bswap_in_place__SYMS_MachUUID(SYMS_MachUUID *v);`
- L805 _prototype_ `void syms_bswap_in_place__SYMS_MachDylib(SYMS_MachDylib *v);`
- L806 _prototype_ `void syms_bswap_in_place__SYMS_MachDylibCommand(SYMS_MachDylibCommand *v);`
- L807 _prototype_ `void syms_bswap_in_place__SYMS_MachDyldInfoCommand(SYMS_MachDyldInfoCommand *v);`
- L808 _prototype_ `void syms_bswap_in_place__SYMS_MachLoadCommand(SYMS_MachLoadCommand *v);`
- L809 _prototype_ `void syms_bswap_in_place__SYMS_MachFatHeader(SYMS_MachFatHeader *v);`
- L810 _prototype_ `void syms_bswap_in_place__SYMS_MachFatArch(SYMS_MachFatArch *v);`
- L811 _prototype_ `void syms_bswap_in_place__SYMS_MachHeader32(SYMS_MachHeader32 *v);`
- L812 _prototype_ `void syms_bswap_in_place__SYMS_MachHeader64(SYMS_MachHeader64 *v);`
- L813 _prototype_ `void syms_bswap_in_place__SYMS_MachSegmentCommand32(SYMS_MachSegmentCommand32 *v);`
- L814 _prototype_ `void syms_bswap_in_place__SYMS_MachSegmentCommand64(SYMS_MachSegmentCommand64 *v);`
- L815 _prototype_ `void syms_bswap_in_place__SYMS_MachSection32(SYMS_MachSection32 *v);`
- L816 _prototype_ `void syms_bswap_in_place__SYMS_MachSection64(SYMS_MachSection64 *v);`
- L817 _prototype_ `void syms_bswap_in_place__SYMS_MachSymtabCommand(SYMS_MachSymtabCommand *v);`
- L818 _prototype_ `void syms_bswap_in_place__SYMS_MachDySymtabCommand(SYMS_MachDySymtabCommand *v);`
- L819 _prototype_ `void syms_bswap_in_place__SYMS_MachNList32(SYMS_MachNList32 *v);`
- L820 _prototype_ `void syms_bswap_in_place__SYMS_MachNList64(SYMS_MachNList64 *v);`
- L821 _prototype_ `void syms_bswap_in_place__SYMS_MachBuildVersionCommand(SYMS_MachBuildVersionCommand *v);`
- L822 _prototype_ `void syms_bswap_in_place__SYMS_MachBuildToolVersion(SYMS_MachBuildToolVersion *v);`
- L823 _prototype_ `void syms_bswap_in_place__SYMS_MachVersionMin(SYMS_MachVersionMin *v);`
- L824 _prototype_ `void syms_bswap_in_place__SYMS_MachDylinker(SYMS_MachDylinker *v);`
- L825 _prototype_ `void syms_bswap_in_place__SYMS_MachPreboundDylibCommand(SYMS_MachPreboundDylibCommand *v);`
- L826 _prototype_ `void syms_bswap_in_place__SYMS_MachRoutinesCommand(SYMS_MachRoutinesCommand *v);`
- L827 _prototype_ `void syms_bswap_in_place__SYMS_MachRoutines64Command(SYMS_MachRoutines64Command *v);`
- L828 _prototype_ `void syms_bswap_in_place__SYMS_MachSubFrameworkCommand(SYMS_MachSubFrameworkCommand *v);`
- L829 _prototype_ `void syms_bswap_in_place__SYMS_MachSubUmbrellaCommand(SYMS_MachSubUmbrellaCommand *v);`
- L830 _prototype_ `void syms_bswap_in_place__SYMS_MachSubClientCommand(SYMS_MachSubClientCommand *v);`
- L831 _prototype_ `void syms_bswap_in_place__SYMS_MachSubLibraryCommand(SYMS_MachSubLibraryCommand *v);`
- L832 _prototype_ `void syms_bswap_in_place__SYMS_MachTwoLevelHintsCommand(SYMS_MachTwoLevelHintsCommand *v);`
- L833 _prototype_ `void syms_bswap_in_place__SYMS_MachPrebindChecksumCommand(SYMS_MachPrebindChecksumCommand *v);`
- L834 _prototype_ `void syms_bswap_in_place__SYMS_MachRPathCommand(SYMS_MachRPathCommand *v);`
- L835 _prototype_ `void syms_bswap_in_place__SYMS_MachLinkeditDataCommand(SYMS_MachLinkeditDataCommand *v);`
- L836 _prototype_ `void syms_bswap_in_place__SYMS_MachEncryptionInfoCommand(SYMS_MachEncryptionInfoCommand *v);`
- L837 _prototype_ `void syms_bswap_in_place__SYMS_MachEncryptionInfo64Command(SYMS_MachEncryptionInfo64Command *v);`
- L838 _prototype_ `void syms_bswap_in_place__SYMS_MachEntryPointCommand(SYMS_MachEntryPointCommand *v);`
- L839 _prototype_ `void syms_bswap_in_place__SYMS_MachSourceVersionCommand(SYMS_MachSourceVersionCommand *v);`
- L840 _prototype_ `void syms_bswap_in_place__SYMS_MachLinkerOptionCommand(SYMS_MachLinkerOptionCommand *v);`
- L841 _prototype_ `void syms_bswap_in_place__SYMS_MachNoteCommand(SYMS_MachNoteCommand *v);`
- L842 _prototype_ `void syms_bswap_in_place__SYMS_MachSymSegCommand(SYMS_MachSymSegCommand *v);`
- L843 _prototype_ `void syms_bswap_in_place__SYMS_MachFvmlib(SYMS_MachFvmlib *v);`
- L844 _prototype_ `void syms_bswap_in_place__SYMS_MachFvmlibCommand(SYMS_MachFvmlibCommand *v);`
- L845 _prototype_ `void syms_bswap_in_place__SYMS_MachThreadCommand(SYMS_MachThreadCommand *v);`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_pe.h` (Other)


#### struct `SYMS_DosHeader`  
`typedef struct SYMS_DosHeader`  
_L7-27_
- L8 _public member_ `SYMS_U16 magic;`
- L9 _public member_ `SYMS_U16 last_page_size;`
- L10 _public member_ `SYMS_U16 page_count;`
- L11 _public member_ `SYMS_U16 reloc_count;`
- L12 _public member_ `SYMS_U16 paragraph_header_size;`
- L13 _public member_ `SYMS_U16 min_paragraph;`
- L14 _public member_ `SYMS_U16 max_paragraph;`
- L15 _public member_ `SYMS_U16 init_ss;`
- L16 _public member_ `SYMS_U16 init_sp;`
- L17 _public member_ `SYMS_U16 checksum;`
- L18 _public member_ `SYMS_U16 init_ip;`
- L19 _public member_ `SYMS_U16 init_cs;`
- L20 _public member_ `SYMS_U16 reloc_table_file_off;`
- L21 _public member_ `SYMS_U16 overlay_number;`
- L22 _public member_ `SYMS_U16 reserved[4];`
- L23 _public member_ `SYMS_U16 oem_id;`
- L24 _public member_ `SYMS_U16 oem_info;`
- L25 _public member_ `SYMS_U16 reserved2[10];`
- L26 _public member_ `SYMS_U32 coff_file_offset;`

#### enum `(anonymous)`  
`enum`  
_L29-45_

#### enum `(anonymous)`  
`enum`  
_L47-64_

#### enum `(anonymous)`  
`enum`  
_L66-78_

#### struct `SYMS_PeOptionalHeader32`  
`typedef struct SYMS_PeOptionalHeader32`  
_L79-110_
- L80 _public member_ `SYMS_U16 magic;`
- L81 _public member_ `SYMS_U8 major_linker_version;`
- L82 _public member_ `SYMS_U8 minor_linker_version;`
- L83 _public member_ `SYMS_U32 sizeof_code;`
- L84 _public member_ `SYMS_U32 sizeof_inited_data;`
- L85 _public member_ `SYMS_U32 sizeof_uninited_data;`
- L86 _public member_ `SYMS_U32 entry_point_va;`
- L87 _public member_ `SYMS_U32 code_base;`
- L88 _public member_ `SYMS_U32 data_base;`
- L89 _public member_ `SYMS_U32 image_base;`
- L90 _public member_ `SYMS_U32 section_alignment;`
- L91 _public member_ `SYMS_U32 file_alignment;`
- L92 _public member_ `SYMS_U16 major_os_ver;`
- L93 _public member_ `SYMS_U16 minor_os_ver;`
- L94 _public member_ `SYMS_U16 major_img_ver;`
- L95 _public member_ `SYMS_U16 minor_img_ver;`
- L96 _public member_ `SYMS_U16 major_subsystem_ver;`
- L97 _public member_ `SYMS_U16 minor_subsystem_ver;`
- L98 _public member_ `SYMS_U32 win32_version_value;`
- L99 _public member_ `SYMS_U32 sizeof_image;`
- L100 _public member_ `SYMS_U32 sizeof_headers;`
- L101 _public member_ `SYMS_U32 check_sum;`
- L102 _public member_ `SYMS_PeWindowsSubsystem subsystem;`
- L103 _public member_ `SYMS_DllCharacteristics dll_characteristics;`
- L104 _public member_ `SYMS_U32 sizeof_stack_reserve;`
- L105 _public member_ `SYMS_U32 sizeof_stack_commit;`
- L106 _public member_ `SYMS_U32 sizeof_heap_reserve;`
- L107 _public member_ `SYMS_U32 sizeof_heap_commit;`
- L108 _public member_ `SYMS_U32 loader_flags;`
- L109 _public member_ `SYMS_U32 data_dir_count;`

#### struct `SYMS_PeOptionalHeader32Plus`  
`typedef struct SYMS_PeOptionalHeader32Plus`  
_L111-141_
- L112 _public member_ `SYMS_U16 magic;`
- L113 _public member_ `SYMS_U8 major_linker_version;`
- L114 _public member_ `SYMS_U8 minor_linker_version;`
- L115 _public member_ `SYMS_U32 sizeof_code;`
- L116 _public member_ `SYMS_U32 sizeof_inited_data;`
- L117 _public member_ `SYMS_U32 sizeof_uninited_data;`
- L118 _public member_ `SYMS_U32 entry_point_va;`
- L119 _public member_ `SYMS_U32 code_base;`
- L120 _public member_ `SYMS_U64 image_base;`
- L121 _public member_ `SYMS_U32 section_alignment;`
- L122 _public member_ `SYMS_U32 file_alignment;`
- L123 _public member_ `SYMS_U16 major_os_ver;`
- L124 _public member_ `SYMS_U16 minor_os_ver;`
- L125 _public member_ `SYMS_U16 major_img_ver;`
- L126 _public member_ `SYMS_U16 minor_img_ver;`
- L127 _public member_ `SYMS_U16 major_subsystem_ver;`
- L128 _public member_ `SYMS_U16 minor_subsystem_ver;`
- L129 _public member_ `SYMS_U32 win32_version_value;`
- L130 _public member_ `SYMS_U32 sizeof_image;`
- L131 _public member_ `SYMS_U32 sizeof_headers;`
- L132 _public member_ `SYMS_U32 check_sum;`
- L133 _public member_ `SYMS_PeWindowsSubsystem subsystem;`
- L134 _public member_ `SYMS_DllCharacteristics dll_characteristics;`
- L135 _public member_ `SYMS_U64 sizeof_stack_reserve;`
- L136 _public member_ `SYMS_U64 sizeof_stack_commit;`
- L137 _public member_ `SYMS_U64 sizeof_heap_reserve;`
- L138 _public member_ `SYMS_U64 sizeof_heap_commit;`
- L139 _public member_ `SYMS_U32 loader_flags;`
- L140 _public member_ `SYMS_U32 data_dir_count;`

#### enum `SYMS_PeDataDirectoryIndex`  
`typedef enum SYMS_PeDataDirectoryIndex`  
_L142-160_
- L143 _public enumerator_ `SYMS_PeDataDirectoryIndex_EXPORT`
- L144 _public enumerator_ `SYMS_PeDataDirectoryIndex_IMPORT`
- L145 _public enumerator_ `SYMS_PeDataDirectoryIndex_RESOURCES`
- L146 _public enumerator_ `SYMS_PeDataDirectoryIndex_EXCEPTIONS`
- L147 _public enumerator_ `SYMS_PeDataDirectoryIndex_CERT`
- L148 _public enumerator_ `SYMS_PeDataDirectoryIndex_BASE_RELOC`
- L149 _public enumerator_ `SYMS_PeDataDirectoryIndex_DEBUG`
- L150 _public enumerator_ `SYMS_PeDataDirectoryIndex_ARCH`
- L151 _public enumerator_ `SYMS_PeDataDirectoryIndex_GLOBAL_PTR`
- L152 _public enumerator_ `SYMS_PeDataDirectoryIndex_TLS`
- L153 _public enumerator_ `SYMS_PeDataDirectoryIndex_LOAD_CONFIG`
- L154 _public enumerator_ `SYMS_PeDataDirectoryIndex_BOUND_IMPORT`
- L155 _public enumerator_ `SYMS_PeDataDirectoryIndex_IMPORT_ADDR`
- L156 _public enumerator_ `SYMS_PeDataDirectoryIndex_DELAY_IMPORT`
- L157 _public enumerator_ `SYMS_PeDataDirectoryIndex_COM_DESCRIPTOR`
- L158 _public enumerator_ `SYMS_PeDataDirectoryIndex_RESERVED`
- L159 _public enumerator_ `SYMS_PeDataDirectoryIndex_COUNT = 16`

#### struct `SYMS_PeDataDirectory`  
`typedef struct SYMS_PeDataDirectory`  
_L161-164_
- L162 _public member_ `SYMS_U32 virt_off;`
- L163 _public member_ `SYMS_U32 virt_size;`

#### enum `(anonymous)`  
`enum`  
_L166-186_

#### enum `(anonymous)`  
`enum`  
_L188-193_

#### enum `(anonymous)`  
`enum`  
_L195-200_

#### enum `(anonymous)`  
`enum`  
_L206-212_

#### enum `(anonymous)`  
`enum`  
_L214-218_

#### struct `SYMS_PeDebugDirectory`  
`typedef struct SYMS_PeDebugDirectory`  
_L219-228_
- L220 _public member_ `SYMS_U32 characteristics;`
- L221 _public member_ `SYMS_U32 time_stamp;`
- L222 _public member_ `SYMS_U16 major_ver;`
- L223 _public member_ `SYMS_U16 minor_ver;`
- L224 _public member_ `SYMS_PeDebugDirectoryType type;`
- L225 _public member_ `SYMS_U32 size;`
- L226 _public member_ `SYMS_U32 virtual_offset;`
- L227 _public member_ `SYMS_U32 file_offset;`

#### enum `(anonymous)`  
`enum`  
_L230-262_

#### enum `(anonymous)`  
`enum`  
_L264-276_

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_PE_H`
- L27 _typedef_ `} SYMS_DosHeader;`
- L28 _typedef_ `typedef SYMS_U16 SYMS_PeWindowsSubsystem;`
- L30 _enumerator_ `SYMS_PeWindowsSubsystem_UNKNOWN = 0` (scope `__anon4404b9c80103`)
- L31 _enumerator_ `SYMS_PeWindowsSubsystem_NATIVE = 1` (scope `__anon4404b9c80103`)
- L32 _enumerator_ `SYMS_PeWindowsSubsystem_WINDOWS_GUI = 2` (scope `__anon4404b9c80103`)
- L33 _enumerator_ `SYMS_PeWindowsSubsystem_WINDOWS_CUI = 3` (scope `__anon4404b9c80103`)
- L34 _enumerator_ `SYMS_PeWindowsSubsystem_OS2_CUI = 5` (scope `__anon4404b9c80103`)
- L35 _enumerator_ `SYMS_PeWindowsSubsystem_POSIX_CUI = 7` (scope `__anon4404b9c80103`)
- L36 _enumerator_ `SYMS_PeWindowsSubsystem_NATIVE_WINDOWS = 8` (scope `__anon4404b9c80103`)
- L37 _enumerator_ `SYMS_PeWindowsSubsystem_WINDOWS_CE_GUI = 9` (scope `__anon4404b9c80103`)
- L38 _enumerator_ `SYMS_PeWindowsSubsystem_EFI_APPLICATION = 10` (scope `__anon4404b9c80103`)
- L39 _enumerator_ `SYMS_PeWindowsSubsystem_EFI_BOOT_SERVICE_DRIVER = 11` (scope `__anon4404b9c80103`)
- L40 _enumerator_ `SYMS_PeWindowsSubsystem_EFI_RUNTIME_DRIVER = 12` (scope `__anon4404b9c80103`)
- L41 _enumerator_ `SYMS_PeWindowsSubsystem_EFI_ROM = 13` (scope `__anon4404b9c80103`)
- L42 _enumerator_ `SYMS_PeWindowsSubsystem_XBOX = 14` (scope `__anon4404b9c80103`)
- L43 _enumerator_ `SYMS_PeWindowsSubsystem_WINDOWS_BOOT_APPLICATION = 16` (scope `__anon4404b9c80103`)
- L44 _enumerator_ `SYMS_PeWindowsSubsystem_COUNT = 14` (scope `__anon4404b9c80103`)
- L46 _typedef_ `typedef SYMS_U16 SYMS_ImageFileCharacteristics;`
- L48 _enumerator_ `SYMS_ImageFileCharacteristic_STRIPPED = (1 << 0)` (scope `__anon4404b9c80203`)
- L49 _enumerator_ `SYMS_ImageFileCharacteristic_EXE = (1 << 1)` (scope `__anon4404b9c80203`)
- L50 _enumerator_ `SYMS_ImageFileCharacteristic_NUMS_STRIPPED = (1 << 2)` (scope `__anon4404b9c80203`)
- L51 _enumerator_ `SYMS_ImageFileCharacteristic_SYMS_STRIPPED = (1 << 3)` (scope `__anon4404b9c80203`)
- L52 _enumerator_ `SYMS_ImageFileCharacteristic_AGGRESIVE_WS_TRIM = (1 << 4)` (scope `__anon4404b9c80203`)
- L53 _enumerator_ `SYMS_ImageFileCharacteristic_LARGE_ADDRESS_AWARE = (1 << 5)` (scope `__anon4404b9c80203`)
- L54 _enumerator_ `SYMS_ImageFileCharacteristic_UNUSED1 = (1 << 6)` (scope `__anon4404b9c80203`)
- L55 _enumerator_ `SYMS_ImageFileCharacteristic_BYTES_RESERVED_LO = (1 << 7)` (scope `__anon4404b9c80203`)
- L56 _enumerator_ `SYMS_ImageFileCharacteristic_32BIT_MACHINE = (1 << 8)` (scope `__anon4404b9c80203`)
- L57 _enumerator_ `SYMS_ImageFileCharacteristic_DEBUG_STRIPPED = (1 << 9)` (scope `__anon4404b9c80203`)
- L58 _enumerator_ `SYMS_ImageFileCharacteristic_FILE_REMOVABLE_RUN_FROM_SWAP = (1 << 10)` (scope `__anon4404b9c80203`)
- L59 _enumerator_ `SYMS_ImageFileCharacteristic_NET_RUN_FROM_SWAP = (1 << 11)` (scope `__anon4404b9c80203`)
- L60 _enumerator_ `SYMS_ImageFileCharacteristic_FILE_SYSTEM = (1 << 12)` (scope `__anon4404b9c80203`)
- L61 _enumerator_ `SYMS_ImageFileCharacteristic_FILE_DLL = (1 << 13)` (scope `__anon4404b9c80203`)
- L62 _enumerator_ `SYMS_ImageFileCharacteristic_FILE_UP_SYSTEM_ONLY = (1 << 14)` (scope `__anon4404b9c80203`)
- L63 _enumerator_ `SYMS_ImageFileCharacteristic_BYTES_RESERVED_HI = (1 << 15)` (scope `__anon4404b9c80203`)
- L65 _typedef_ `typedef SYMS_U16 SYMS_DllCharacteristics;`
- L67 _enumerator_ `SYMS_DllCharacteristic_HIGH_ENTROPY_VA = (1 << 5)` (scope `__anon4404b9c80303`)
- L68 _enumerator_ `SYMS_DllCharacteristic_DYNAMIC_BASE = (1 << 6)` (scope `__anon4404b9c80303`)
- L69 _enumerator_ `SYMS_DllCharacteristic_FORCE_INTEGRITY = (1 << 7)` (scope `__anon4404b9c80303`)
- L70 _enumerator_ `SYMS_DllCharacteristic_NX_COMPAT = (1 << 8)` (scope `__anon4404b9c80303`)
- L71 _enumerator_ `SYMS_DllCharacteristic_NO_ISOLATION = (1 << 9)` (scope `__anon4404b9c80303`)
- L72 _enumerator_ `SYMS_DllCharacteristic_NO_SEH = (1 << 10)` (scope `__anon4404b9c80303`)
- L73 _enumerator_ `SYMS_DllCharacteristic_NO_BIND = (1 << 11)` (scope `__anon4404b9c80303`)
- L74 _enumerator_ `SYMS_DllCharacteristic_APPCONTAINER = (1 << 12)` (scope `__anon4404b9c80303`)
- L75 _enumerator_ `SYMS_DllCharacteristic_WDM_DRIVER = (1 << 13)` (scope `__anon4404b9c80303`)
- L76 _enumerator_ `SYMS_DllCharacteristic_GUARD_CF = (1 << 14)` (scope `__anon4404b9c80303`)
- L77 _enumerator_ `SYMS_DllCharacteristic_TERMINAL_SERVER_AWARE = (1 << 15)` (scope `__anon4404b9c80303`)
- L110 _typedef_ `} SYMS_PeOptionalHeader32;`
- L141 _typedef_ `} SYMS_PeOptionalHeader32Plus;`
- L160 _typedef_ `} SYMS_PeDataDirectoryIndex;`
- L164 _typedef_ `} SYMS_PeDataDirectory;`
- L165 _typedef_ `typedef SYMS_U32 SYMS_PeDebugDirectoryType;`
- L167 _enumerator_ `SYMS_PeDebugDirectoryType_UNKNOWN = 0` (scope `__anon4404b9c80403`)
- L168 _enumerator_ `SYMS_PeDebugDirectoryType_COFF = 1` (scope `__anon4404b9c80403`)
- L169 _enumerator_ `SYMS_PeDebugDirectoryType_CODEVIEW = 2` (scope `__anon4404b9c80403`)
- L170 _enumerator_ `SYMS_PeDebugDirectoryType_FPO = 3` (scope `__anon4404b9c80403`)
- L171 _enumerator_ `SYMS_PeDebugDirectoryType_MISC = 4` (scope `__anon4404b9c80403`)
- L172 _enumerator_ `SYMS_PeDebugDirectoryType_EXCEPTION = 5` (scope `__anon4404b9c80403`)
- L173 _enumerator_ `SYMS_PeDebugDirectoryType_FIXUP = 6` (scope `__anon4404b9c80403`)
- L174 _enumerator_ `SYMS_PeDebugDirectoryType_OMAP_TO_SRC = 7` (scope `__anon4404b9c80403`)
- L175 _enumerator_ `SYMS_PeDebugDirectoryType_OMAP_FROM_SRC = 8` (scope `__anon4404b9c80403`)
- L176 _enumerator_ `SYMS_PeDebugDirectoryType_BORLAND = 9` (scope `__anon4404b9c80403`)
- L177 _enumerator_ `SYMS_PeDebugDirectoryType_RESERVED10 = 10` (scope `__anon4404b9c80403`)
- L178 _enumerator_ `SYMS_PeDebugDirectoryType_CLSID = 11` (scope `__anon4404b9c80403`)
- L179 _enumerator_ `SYMS_PeDebugDirectoryType_VC_FEATURE = 12` (scope `__anon4404b9c80403`)
- L180 _enumerator_ `SYMS_PeDebugDirectoryType_POGO = 13` (scope `__anon4404b9c80403`)
- L181 _enumerator_ `SYMS_PeDebugDirectoryType_ILTCG = 14` (scope `__anon4404b9c80403`)
- L182 _enumerator_ `SYMS_PeDebugDirectoryType_MPX = 15` (scope `__anon4404b9c80403`)
- L183 _enumerator_ `SYMS_PeDebugDirectoryType_REPRO = 16` (scope `__anon4404b9c80403`)
- L184 _enumerator_ `SYMS_PeDebugDirectoryType_EX_DLLCHARACTERISTICS = 20` (scope `__anon4404b9c80403`)
- L185 _enumerator_ `SYMS_PeDebugDirectoryType_COUNT = 18` (scope `__anon4404b9c80403`)
- L187 _typedef_ `typedef SYMS_U8 SYMS_PeFPOFlags;`
- L189 _enumerator_ `SYMS_PeFPOFlags_HAS_SEH = 0x800` (scope `__anon4404b9c80503`)
- L190 _enumerator_ `SYMS_PeFPOFlags_USE_BP_REG = 0x1000` (scope `__anon4404b9c80503`)
- L191 _enumerator_ `SYMS_PeFPOFlags_RESERVED = 0x2000` (scope `__anon4404b9c80503`)
- L192 _enumerator_ `SYMS_PeFPOFlags_COUNT = 3` (scope `__anon4404b9c80503`)
- L194 _typedef_ `typedef SYMS_U16 SYMS_PeFPOEncoded;`
- L196 _enumerator_ `SYMS_PeFPOEncoded_PROLOG_SIZE_SHIFT = 0` (scope `__anon4404b9c80603`)
- L196 _enumerator_ `SYMS_PeFPOEncoded_PROLOG_SIZE_SHIFT = 0` (scope `__anon4404b9c80603`)
- L197 _enumerator_ `SYMS_PeFPOEncoded_SAVED_REGS_SIZE_SHIFT = 8` (scope `__anon4404b9c80603`)
- L197 _enumerator_ `SYMS_PeFPOEncoded_SAVED_REGS_SIZE_SHIFT = 8` (scope `__anon4404b9c80603`)
- L198 _enumerator_ `SYMS_PeFPOEncoded_FLAGS_SHIFT = 11` (scope `__anon4404b9c80603`)
- L198 _enumerator_ `SYMS_PeFPOEncoded_FLAGS_SHIFT = 11` (scope `__anon4404b9c80603`)
- L199 _enumerator_ `SYMS_PeFPOEncoded_FRAME_TYPE_SHIFT = 14` (scope `__anon4404b9c80603`)
- L199 _enumerator_ `SYMS_PeFPOEncoded_FRAME_TYPE_SHIFT = 14` (scope `__anon4404b9c80603`)
- L201 _macro_ `#define SYMS_PeFPOEncoded_Extract_PROLOG_SIZE(f) (SYMS_U8)(((f) >> SYMS_PeFPOEncoded_PROLOG_SIZE_SHIFT) & SYMS_PeFPOEncoded_PROLOG_SIZE_MASK)`
- L202 _macro_ `#define SYMS_PeFPOEncoded_Extract_SAVED_REGS_SIZE(f) (SYMS_U8)(((f) >> SYMS_PeFPOEncoded_SAVED_REGS_SIZE_SHIFT) & SYMS_PeFPOEncoded_SAVED_REGS_SIZE_MASK)`
- L203 _macro_ `#define SYMS_PeFPOEncoded_Extract_FLAGS(f) (SYMS_U8)(((f) >> SYMS_PeFPOEncoded_FLAGS_SHIFT) & SYMS_PeFPOEncoded_FLAGS_MASK)`
- L204 _macro_ `#define SYMS_PeFPOEncoded_Extract_FRAME_TYPE(f) (SYMS_U8)(((f) >> SYMS_PeFPOEncoded_FRAME_TYPE_SHIFT) & SYMS_PeFPOEncoded_FRAME_TYPE_MASK)`
- L205 _typedef_ `typedef SYMS_U8 SYMS_PeFPOType;`
- L207 _enumerator_ `SYMS_PeFPOType_FPO = 0` (scope `__anon4404b9c80703`)
- L208 _enumerator_ `SYMS_PeFPOType_TRAP = 1` (scope `__anon4404b9c80703`)
- L209 _enumerator_ `SYMS_PeFPOType_TSS = 2` (scope `__anon4404b9c80703`)
- L210 _enumerator_ `SYMS_PeFPOType_NOFPO = 3` (scope `__anon4404b9c80703`)
- L211 _enumerator_ `SYMS_PeFPOType_COUNT = 4` (scope `__anon4404b9c80703`)
- L213 _typedef_ `typedef SYMS_U32 SYMS_PeDebugMiscType;`
- L215 _enumerator_ `SYMS_PeDebugMiscType_NULL` (scope `__anon4404b9c80803`)
- L216 _enumerator_ `SYMS_PeDebugMiscType_EXE_NAME` (scope `__anon4404b9c80803`)
- L217 _enumerator_ `SYMS_PeDebugMiscType_COUNT = 2` (scope `__anon4404b9c80803`)
- L228 _typedef_ `} SYMS_PeDebugDirectory;`
- L229 _typedef_ `typedef SYMS_U32 SYMS_PeGlobalFlags;`
- L231 _enumerator_ `SYMS_PeGlobalFlags_STOP_ON_EXCEPTION = (1 << 0)` (scope `__anon4404b9c80903`)
- L232 _enumerator_ `SYMS_PeGlobalFlags_SHOW_LDR_SNAPS = (1 << 1)` (scope `__anon4404b9c80903`)
- L233 _enumerator_ `SYMS_PeGlobalFlags_DEBUG_INITIAL_COMMAND = (1 << 2)` (scope `__anon4404b9c80903`)
- L234 _enumerator_ `SYMS_PeGlobalFlags_STOP_ON_HUNG_GUI = (1 << 3)` (scope `__anon4404b9c80903`)
- L235 _enumerator_ `SYMS_PeGlobalFlags_HEAP_ENABLE_TAIL_CHECK = (1 << 4)` (scope `__anon4404b9c80903`)
- L236 _enumerator_ `SYMS_PeGlobalFlags_HEAP_ENABLE_FREE_CHECK = (1 << 5)` (scope `__anon4404b9c80903`)
- L237 _enumerator_ `SYMS_PeGlobalFlags_HEAP_VALIDATE_PARAMETERS = (1 << 6)` (scope `__anon4404b9c80903`)
- L238 _enumerator_ `SYMS_PeGlobalFlags_HEAP_VALIDATE_ALL = (1 << 7)` (scope `__anon4404b9c80903`)
- L239 _enumerator_ `SYMS_PeGlobalFlags_APPLICATION_VERIFIER = (1 << 8)` (scope `__anon4404b9c80903`)
- L240 _enumerator_ `SYMS_PeGlobalFlags_POOL_ENABLE_TAGGING = (1 << 10)` (scope `__anon4404b9c80903`)
- L241 _enumerator_ `SYMS_PeGlobalFlags_HEAP_ENABLE_TAGGING = (1 << 11)` (scope `__anon4404b9c80903`)
- L242 _enumerator_ `SYMS_PeGlobalFlags_STACK_TRACE_DB = (1 << 12)` (scope `__anon4404b9c80903`)
- L243 _enumerator_ `SYMS_PeGlobalFlags_KERNEL_STACK_TRACE_DB = (1 << 13)` (scope `__anon4404b9c80903`)
- L244 _enumerator_ `SYMS_PeGlobalFlags_MAINTAIN_OBJECT_TYPELIST = (1 << 14)` (scope `__anon4404b9c80903`)
- L245 _enumerator_ `SYMS_PeGlobalFlags_HEAP_ENABLE_TAG_BY_DLL = (1 << 15)` (scope `__anon4404b9c80903`)
- L246 _enumerator_ `SYMS_PeGlobalFlags_DISABLE_STACK_EXTENSION = (1 << 16)` (scope `__anon4404b9c80903`)
- L247 _enumerator_ `SYMS_PeGlobalFlags_ENABLE_CSRDEBUG = (1 << 17)` (scope `__anon4404b9c80903`)
- L248 _enumerator_ `SYMS_PeGlobalFlags_ENABLE_KDEBUG_SYMBOL_LOAD = (1 << 18)` (scope `__anon4404b9c80903`)
- L249 _enumerator_ `SYMS_PeGlobalFlags_DISABLE_PAGE_KERNEL_STACKS = (1 << 19)` (scope `__anon4404b9c80903`)
- L250 _enumerator_ `SYMS_PeGlobalFlags_ENABLE_SYSTEM_CRIT_BREAKS = (1 << 20)` (scope `__anon4404b9c80903`)
- L251 _enumerator_ `SYMS_PeGlobalFlags_HEAP_DISABLE_COALESCING = (1 << 21)` (scope `__anon4404b9c80903`)
- L252 _enumerator_ `SYMS_PeGlobalFlags_ENABLE_CLOSE_EXCEPTIONS = (1 << 22)` (scope `__anon4404b9c80903`)
- L253 _enumerator_ `SYMS_PeGlobalFlags_ENABLE_EXCEPTION_LOGGING = (1 << 23)` (scope `__anon4404b9c80903`)
- L254 _enumerator_ `SYMS_PeGlobalFlags_ENABLE_HANDLE_TYPE_TAGGING = (1 << 24)` (scope `__anon4404b9c80903`)
- L255 _enumerator_ `SYMS_PeGlobalFlags_HEAP_PAGE_ALLOCS = (1 << 25)` (scope `__anon4404b9c80903`)
- L256 _enumerator_ `SYMS_PeGlobalFlags_DEBUG_INITIAL_COMMAND_EX = (1 << 26)` (scope `__anon4404b9c80903`)
- L257 _enumerator_ `SYMS_PeGlobalFlags_DISABLE_DBGPRINT = (1 << 27)` (scope `__anon4404b9c80903`)
- L258 _enumerator_ `SYMS_PeGlobalFlags_CRITSEC_EVENT_CREATION = (1 << 28)` (scope `__anon4404b9c80903`)
- L259 _enumerator_ `SYMS_PeGlobalFlags_LDR_TOP_DOWN = (1 << 29)` (scope `__anon4404b9c80903`)
- L260 _enumerator_ `SYMS_PeGlobalFlags_ENABLE_HANDLE_EXCEPTIONS = (1 << 30)` (scope `__anon4404b9c80903`)
- L261 _enumerator_ `SYMS_PeGlobalFlags_DISABLE_PROTDLLS = (1 << 31)` (scope `__anon4404b9c80903`)
- L263 _typedef_ `typedef SYMS_U32 SYMS_PeLoadConfigGuardFlags;`
- L265 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CF_INSTRUMENTED = (1 << 8)` (scope `__anon4404b9c80a03`)
- L266 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CFW_INSTRUMENTED = (1 << 9)` (scope `__anon4404b9c80a03`)
- L267 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CF_FUNCTION_TABLE_PRESENT = (1 << 10)` (scope `__anon4404b9c80a03`)
- L268 _enumerator_ `SYMS_PeLoadConfigGuardFlags_SECURITY_COOKIE_UNUSED = (1 << 11)` (scope `__anon4404b9c80a03`)
- L269 _enumerator_ `SYMS_PeLoadConfigGuardFlags_PROTECT_DELAYLOAD_IAT = (1 << 12)` (scope `__anon4404b9c80a03`)
- L270 _enumerator_ `SYMS_PeLoadConfigGuardFlags_DELAYLOAD_IAT_IN_ITS_OWN_SECTION = (1 << 13)` (scope `__anon4404b9c80a03`)
- L271 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CF_EXPORT_SUPPRESSION_INFO_PRESENT = (1 << 14)` (scope `__anon4404b9c80a03`)
- L272 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CF_ENABLE_EXPORT_SUPPRESSION = (1 << 15)` (scope `__anon4404b9c80a03`)
- L273 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CF_LONGJUMP_TABLE_PRESENT = (1 << 16)` (scope `__anon4404b9c80a03`)
- L274 _enumerator_ `SYMS_PeLoadConfigGuardFlags_EH_CONTINUATION_TABLE_PRESENT = (1 << 22)` (scope `__anon4404b9c80a03`)
- L275 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CF_FUNCTION_TABLE_SIZE_SHIFT = 28` (scope `__anon4404b9c80a03`)
- L275 _enumerator_ `SYMS_PeLoadConfigGuardFlags_CF_FUNCTION_TABLE_SIZE_SHIFT = 28` (scope `__anon4404b9c80a03`)
- L277 _macro_ `#define SYMS_PeLoadConfigGuardFlags_Extract_CF_FUNCTION_TABLE_SIZE(f) (SYMS_U32)(((f) >> SYMS_PeLoadConfigGuardFlags_CF_FUNCTION_TABLE_SIZE_SHIFT) & SYMS_PeLoadConfigGuardFlags_CF_FUNCTION_TABLE_SIZE_MASK)`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_regs_x64.h` (Other)


#### struct `SYMS_RegX64`  
`typedef struct SYMS_RegX64`  
_L6-83_
- L7 _public member_ `SYMS_Reg64 rax;`
- L8 _public member_ `SYMS_Reg64 rcx;`
- L9 _public member_ `SYMS_Reg64 rdx;`
- L10 _public member_ `SYMS_Reg64 rbx;`
- L11 _public member_ `SYMS_Reg64 rsp;`
- L12 _public member_ `SYMS_Reg64 rbp;`
- L13 _public member_ `SYMS_Reg64 rsi;`
- L14 _public member_ `SYMS_Reg64 rdi;`
- L15 _public member_ `SYMS_Reg64 r8;`
- L16 _public member_ `SYMS_Reg64 r9;`
- L17 _public member_ `SYMS_Reg64 r10;`
- L18 _public member_ `SYMS_Reg64 r11;`
- L19 _public member_ `SYMS_Reg64 r12;`
- L20 _public member_ `SYMS_Reg64 r13;`
- L21 _public member_ `SYMS_Reg64 r14;`
- L22 _public member_ `SYMS_Reg64 r15;`
- L23 _public member_ `SYMS_Reg64 fsbase;`
- L24 _public member_ `SYMS_Reg64 gsbase;`
- L25 _public member_ `SYMS_Reg64 rip;`
- L26 _public member_ `SYMS_Reg64 rflags;`
- L27 _public member_ `SYMS_Reg32 dr0;`
- L28 _public member_ `SYMS_Reg32 dr1;`
- L29 _public member_ `SYMS_Reg32 dr2;`
- L30 _public member_ `SYMS_Reg32 dr3;`
- L31 _public member_ `SYMS_Reg32 dr4;`
- L32 _public member_ `SYMS_Reg32 dr5;`
- L33 _public member_ `SYMS_Reg32 dr6;`
- L34 _public member_ `SYMS_Reg32 dr7;`
- L35 _public member_ `SYMS_Reg80 fpr0;`
- L36 _public member_ `SYMS_Reg80 fpr1;`
- L37 _public member_ `SYMS_Reg80 fpr2;`
- L38 _public member_ `SYMS_Reg80 fpr3;`
- L39 _public member_ `SYMS_Reg80 fpr4;`
- L40 _public member_ `SYMS_Reg80 fpr5;`
- L41 _public member_ `SYMS_Reg80 fpr6;`
- L42 _public member_ `SYMS_Reg80 fpr7;`
- L43 _public member_ `SYMS_Reg80 st0;`
- L44 _public member_ `SYMS_Reg80 st1;`
- L45 _public member_ `SYMS_Reg80 st2;`
- L46 _public member_ `SYMS_Reg80 st3;`
- L47 _public member_ `SYMS_Reg80 st4;`
- L48 _public member_ `SYMS_Reg80 st5;`
- L49 _public member_ `SYMS_Reg80 st6;`
- L50 _public member_ `SYMS_Reg80 st7;`
- L51 _public member_ `SYMS_Reg16 fcw;`
- L52 _public member_ `SYMS_Reg16 fsw;`
- L53 _public member_ `SYMS_Reg16 ftw;`
- L54 _public member_ `SYMS_Reg16 fop;`
- L55 _public member_ `SYMS_Reg16 fcs;`
- L56 _public member_ `SYMS_Reg16 fds;`
- L57 _public member_ `SYMS_Reg32 fip;`
- L58 _public member_ `SYMS_Reg32 fdp;`
- L59 _public member_ `SYMS_Reg32 mxcsr;`
- L60 _public member_ `SYMS_Reg32 mxcsr_mask;`
- L61 _public member_ `SYMS_Reg16 ss;`
- L62 _public member_ `SYMS_Reg16 cs;`
- L63 _public member_ `SYMS_Reg16 ds;`
- L64 _public member_ `SYMS_Reg16 es;`
- L65 _public member_ `SYMS_Reg16 fs;`
- L66 _public member_ `SYMS_Reg16 gs;`
- L67 _public member_ `SYMS_Reg256 ymm0;`
- L68 _public member_ `SYMS_Reg256 ymm1;`
- L69 _public member_ `SYMS_Reg256 ymm2;`
- L70 _public member_ `SYMS_Reg256 ymm3;`
- L71 _public member_ `SYMS_Reg256 ymm4;`
- L72 _public member_ `SYMS_Reg256 ymm5;`
- L73 _public member_ `SYMS_Reg256 ymm6;`
- L74 _public member_ `SYMS_Reg256 ymm7;`
- L75 _public member_ `SYMS_Reg256 ymm8;`
- L76 _public member_ `SYMS_Reg256 ymm9;`
- L77 _public member_ `SYMS_Reg256 ymm10;`
- L78 _public member_ `SYMS_Reg256 ymm11;`
- L79 _public member_ `SYMS_Reg256 ymm12;`
- L80 _public member_ `SYMS_Reg256 ymm13;`
- L81 _public member_ `SYMS_Reg256 ymm14;`
- L82 _public member_ `SYMS_Reg256 ymm15;`

#### enum `SYMS_RegX64Code`  
`typedef enum SYMS_RegX64Code`  
_L85-245_
- L87 _public enumerator_ `SYMS_RegX64Code_nil`
- L88 _public enumerator_ `SYMS_RegX64Code_rax`
- L89 _public enumerator_ `SYMS_RegX64Code_rcx`
- L90 _public enumerator_ `SYMS_RegX64Code_rdx`
- L91 _public enumerator_ `SYMS_RegX64Code_rbx`
- L92 _public enumerator_ `SYMS_RegX64Code_rsp`
- L93 _public enumerator_ `SYMS_RegX64Code_rbp`
- L94 _public enumerator_ `SYMS_RegX64Code_rsi`
- L95 _public enumerator_ `SYMS_RegX64Code_rdi`
- L96 _public enumerator_ `SYMS_RegX64Code_r8`
- L97 _public enumerator_ `SYMS_RegX64Code_r9`
- L98 _public enumerator_ `SYMS_RegX64Code_r10`
- L99 _public enumerator_ `SYMS_RegX64Code_r11`
- L100 _public enumerator_ `SYMS_RegX64Code_r12`
- L101 _public enumerator_ `SYMS_RegX64Code_r13`
- L102 _public enumerator_ `SYMS_RegX64Code_r14`
- L103 _public enumerator_ `SYMS_RegX64Code_r15`
- L104 _public enumerator_ `SYMS_RegX64Code_fsbase`
- L105 _public enumerator_ `SYMS_RegX64Code_gsbase`
- L106 _public enumerator_ `SYMS_RegX64Code_rip`
- L107 _public enumerator_ `SYMS_RegX64Code_rflags`
- L108 _public enumerator_ `SYMS_RegX64Code_dr0`
- L109 _public enumerator_ `SYMS_RegX64Code_dr1`
- L110 _public enumerator_ `SYMS_RegX64Code_dr2`
- L111 _public enumerator_ `SYMS_RegX64Code_dr3`
- L112 _public enumerator_ `SYMS_RegX64Code_dr4`
- L113 _public enumerator_ `SYMS_RegX64Code_dr5`
- L114 _public enumerator_ `SYMS_RegX64Code_dr6`
- L115 _public enumerator_ `SYMS_RegX64Code_dr7`
- L116 _public enumerator_ `SYMS_RegX64Code_fpr0`
- L117 _public enumerator_ `SYMS_RegX64Code_fpr1`
- L118 _public enumerator_ `SYMS_RegX64Code_fpr2`
- L119 _public enumerator_ `SYMS_RegX64Code_fpr3`
- L120 _public enumerator_ `SYMS_RegX64Code_fpr4`
- L121 _public enumerator_ `SYMS_RegX64Code_fpr5`
- L122 _public enumerator_ `SYMS_RegX64Code_fpr6`
- L123 _public enumerator_ `SYMS_RegX64Code_fpr7`
- L124 _public enumerator_ `SYMS_RegX64Code_st0`
- L125 _public enumerator_ `SYMS_RegX64Code_st1`
- L126 _public enumerator_ `SYMS_RegX64Code_st2`
- L127 _public enumerator_ `SYMS_RegX64Code_st3`
- L128 _public enumerator_ `SYMS_RegX64Code_st4`
- L129 _public enumerator_ `SYMS_RegX64Code_st5`
- L130 _public enumerator_ `SYMS_RegX64Code_st6`
- L131 _public enumerator_ `SYMS_RegX64Code_st7`
- L132 _public enumerator_ `SYMS_RegX64Code_fcw`
- L133 _public enumerator_ `SYMS_RegX64Code_fsw`
- L134 _public enumerator_ `SYMS_RegX64Code_ftw`
- L135 _public enumerator_ `SYMS_RegX64Code_fop`
- L136 _public enumerator_ `SYMS_RegX64Code_fcs`
- L137 _public enumerator_ `SYMS_RegX64Code_fds`
- L138 _public enumerator_ `SYMS_RegX64Code_fip`
- L139 _public enumerator_ `SYMS_RegX64Code_fdp`
- L140 _public enumerator_ `SYMS_RegX64Code_mxcsr`
- L141 _public enumerator_ `SYMS_RegX64Code_mxcsr_mask`
- L142 _public enumerator_ `SYMS_RegX64Code_ss`
- L143 _public enumerator_ `SYMS_RegX64Code_cs`
- L144 _public enumerator_ `SYMS_RegX64Code_ds`
- L145 _public enumerator_ `SYMS_RegX64Code_es`
- L146 _public enumerator_ `SYMS_RegX64Code_fs`
- L147 _public enumerator_ `SYMS_RegX64Code_gs`
- L148 _public enumerator_ `SYMS_RegX64Code_ymm0`
- L149 _public enumerator_ `SYMS_RegX64Code_ymm1`
- L150 _public enumerator_ `SYMS_RegX64Code_ymm2`
- L151 _public enumerator_ `SYMS_RegX64Code_ymm3`
- L152 _public enumerator_ `SYMS_RegX64Code_ymm4`
- L153 _public enumerator_ `SYMS_RegX64Code_ymm5`
- L154 _public enumerator_ `SYMS_RegX64Code_ymm6`
- L155 _public enumerator_ `SYMS_RegX64Code_ymm7`
- L156 _public enumerator_ `SYMS_RegX64Code_ymm8`
- L157 _public enumerator_ `SYMS_RegX64Code_ymm9`
- L158 _public enumerator_ `SYMS_RegX64Code_ymm10`
- L159 _public enumerator_ `SYMS_RegX64Code_ymm11`
- L160 _public enumerator_ `SYMS_RegX64Code_ymm12`
- L161 _public enumerator_ `SYMS_RegX64Code_ymm13`
- L162 _public enumerator_ `SYMS_RegX64Code_ymm14`
- L163 _public enumerator_ `SYMS_RegX64Code_ymm15`
- L165 _public enumerator_ `SYMS_RegX64Code_eax` — ALIASES BEGIN
- L166 _public enumerator_ `SYMS_RegX64Code_ecx`
- L167 _public enumerator_ `SYMS_RegX64Code_edx`
- L168 _public enumerator_ `SYMS_RegX64Code_ebx`
- L169 _public enumerator_ `SYMS_RegX64Code_esp`
- L170 _public enumerator_ `SYMS_RegX64Code_ebp`
- L171 _public enumerator_ `SYMS_RegX64Code_esi`
- L172 _public enumerator_ `SYMS_RegX64Code_edi`
- L173 _public enumerator_ `SYMS_RegX64Code_r8d`
- L174 _public enumerator_ `SYMS_RegX64Code_r9d`
- L175 _public enumerator_ `SYMS_RegX64Code_r10d`
- L176 _public enumerator_ `SYMS_RegX64Code_r11d`
- L177 _public enumerator_ `SYMS_RegX64Code_r12d`
- L178 _public enumerator_ `SYMS_RegX64Code_r13d`
- L179 _public enumerator_ `SYMS_RegX64Code_r14d`
- L180 _public enumerator_ `SYMS_RegX64Code_r15d`
- L181 _public enumerator_ `SYMS_RegX64Code_eip`
- L182 _public enumerator_ `SYMS_RegX64Code_eflags`
- L183 _public enumerator_ `SYMS_RegX64Code_ax`
- L184 _public enumerator_ `SYMS_RegX64Code_cx`
- L185 _public enumerator_ `SYMS_RegX64Code_dx`
- L186 _public enumerator_ `SYMS_RegX64Code_bx`
- L187 _public enumerator_ `SYMS_RegX64Code_si`
- L188 _public enumerator_ `SYMS_RegX64Code_di`
- L189 _public enumerator_ `SYMS_RegX64Code_sp`
- L190 _public enumerator_ `SYMS_RegX64Code_bp`
- L191 _public enumerator_ `SYMS_RegX64Code_ip`
- L192 _public enumerator_ `SYMS_RegX64Code_r8w`
- L193 _public enumerator_ `SYMS_RegX64Code_r9w`
- L194 _public enumerator_ `SYMS_RegX64Code_r10w`
- L195 _public enumerator_ `SYMS_RegX64Code_r11w`
- L196 _public enumerator_ `SYMS_RegX64Code_r12w`
- L197 _public enumerator_ `SYMS_RegX64Code_r13w`
- L198 _public enumerator_ `SYMS_RegX64Code_r14w`
- L199 _public enumerator_ `SYMS_RegX64Code_r15w`
- L200 _public enumerator_ `SYMS_RegX64Code_al`
- L201 _public enumerator_ `SYMS_RegX64Code_cl`
- L202 _public enumerator_ `SYMS_RegX64Code_dl`
- L203 _public enumerator_ `SYMS_RegX64Code_bl`
- L204 _public enumerator_ `SYMS_RegX64Code_sil`
- L205 _public enumerator_ `SYMS_RegX64Code_dil`
- L206 _public enumerator_ `SYMS_RegX64Code_bpl`
- L207 _public enumerator_ `SYMS_RegX64Code_spl`
- L208 _public enumerator_ `SYMS_RegX64Code_r8b`
- L209 _public enumerator_ `SYMS_RegX64Code_r9b`
- L210 _public enumerator_ `SYMS_RegX64Code_r10b`
- L211 _public enumerator_ `SYMS_RegX64Code_r11b`
- L212 _public enumerator_ `SYMS_RegX64Code_r12b`
- L213 _public enumerator_ `SYMS_RegX64Code_r13b`
- L214 _public enumerator_ `SYMS_RegX64Code_r14b`
- L215 _public enumerator_ `SYMS_RegX64Code_r15b`
- L216 _public enumerator_ `SYMS_RegX64Code_ah`
- L217 _public enumerator_ `SYMS_RegX64Code_ch`
- L218 _public enumerator_ `SYMS_RegX64Code_dh`
- L219 _public enumerator_ `SYMS_RegX64Code_bh`
- L220 _public enumerator_ `SYMS_RegX64Code_xmm0`
- L221 _public enumerator_ `SYMS_RegX64Code_xmm1`
- L222 _public enumerator_ `SYMS_RegX64Code_xmm2`
- L223 _public enumerator_ `SYMS_RegX64Code_xmm3`
- L224 _public enumerator_ `SYMS_RegX64Code_xmm4`
- L225 _public enumerator_ `SYMS_RegX64Code_xmm5`
- L226 _public enumerator_ `SYMS_RegX64Code_xmm6`
- L227 _public enumerator_ `SYMS_RegX64Code_xmm7`
- L228 _public enumerator_ `SYMS_RegX64Code_xmm8`
- L229 _public enumerator_ `SYMS_RegX64Code_xmm9`
- L230 _public enumerator_ `SYMS_RegX64Code_xmm10`
- L231 _public enumerator_ `SYMS_RegX64Code_xmm11`
- L232 _public enumerator_ `SYMS_RegX64Code_xmm12`
- L233 _public enumerator_ `SYMS_RegX64Code_xmm13`
- L234 _public enumerator_ `SYMS_RegX64Code_xmm14`
- L235 _public enumerator_ `SYMS_RegX64Code_xmm15`
- L236 _public enumerator_ `SYMS_RegX64Code_mm0`
- L237 _public enumerator_ `SYMS_RegX64Code_mm1`
- L238 _public enumerator_ `SYMS_RegX64Code_mm2`
- L239 _public enumerator_ `SYMS_RegX64Code_mm3`
- L240 _public enumerator_ `SYMS_RegX64Code_mm4`
- L241 _public enumerator_ `SYMS_RegX64Code_mm5`
- L242 _public enumerator_ `SYMS_RegX64Code_mm6`
- L243 _public enumerator_ `SYMS_RegX64Code_mm7`
- L244 _public enumerator_ `SYMS_RegX64Code_COUNT`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_REGS_X64_H`
- L83 _typedef_ `} SYMS_RegX64;`
- L245 _typedef_ `} SYMS_RegX64Code;`
- L247 _variable_ `static SYMS_RegSection syms_reg_section_X64[SYMS_RegX64Code_COUNT] = { {0, 0}, {0, 8}, {8, 8}, {16, 8}, {24, 8}, {32, 8}, {40, 8}, {48, 8}, {56, 8}, {64, 8}, {72, 8}, {80, 8}, {88, 8}, {96, 8}, {104, 8}, {112, 8}, {120, 8}, {128, 8}, {136, 8}, {144, 8}, {152, 8}, {160, 4}, {164, 4}, {168, 4}, {172, 4}, {176, 4}, {180, 4}, {184, 4}, {188, 4}, {192, 10}, {202, 10}, {212, 10}, {222, 10}, {232, 10}, {242, 10}, {252, 10}, {262, 10}, {272, 10}, {282, 10},`
- L407 _variable_ `static SYMS_String8 syms_reg_names_X64[SYMS_RegX64Code_COUNT] = { {(SYMS_U8*)"nil", 3}, {(SYMS_U8*)"rax", 3}, {(SYMS_U8*)"rcx", 3}, {(SYMS_U8*)"rdx", 3}, {(SYMS_U8*)"rbx", 3}, {(SYMS_U8*)"rsp", 3}, {(SYMS_U8*)"rbp", 3}, {(SYMS_U8*)"rsi", 3}, {(SYMS_U8*)"rdi", 3}, {(SYMS_U8*)"r8", 2}, {(SYMS_U8*)"r9", 2}, {(SYMS_U8*)"r10", 3}, {(SYMS_U8*)"r11", 3}, {(SYMS_U8*)"r12", 3}, {(SYMS_U8*)"r13", 3}, {(SYMS_U8*)"r14", 3}, {(SYMS_U8*)"r15", 3}, {(SYMS_U8*)"fsbase", 6}, {(SYMS_U8*)"gsbase", 6}, {(SYMS_U8*)"rip", 3}, {(SYMS_U8*)"rflags", 6}, {(SYMS_U8*)"dr0", 3}, {(SYMS_U8*)"dr1", 3}, {(SYMS_U8*)"dr2", 3}, {(SYMS_U8*)"dr3", 3}, {(SYMS_U8*)"dr4", 3}, {(SYMS_U8*)"dr5", 3}, {(SYMS_U8*)"dr6", 3}, {(SYMS_U8*)"dr7", 3}, {(SYMS_U8*)"fpr0", 4}, {(SYMS_U8*)"fpr1", 4}, {(SYMS_U8*)"fpr2", 4}, {(SYMS_U8*)"fpr3", 4}, {(SYMS_U8*)"fpr4", 4}, {(SYMS_U8*)"fpr5", 4}, {(SYMS_U8*)"fpr6", 4}, {(SYMS_U8*)"fpr7", 4}, {(SYMS_U8*)"st0", 3}, {(SYMS_U8*)"st1", 3},`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_regs_x86.h` (Other)


#### struct `SYMS_RegX86`  
`typedef struct SYMS_RegX86`  
_L6-67_
- L7 _public member_ `SYMS_Reg32 eax;`
- L8 _public member_ `SYMS_Reg32 ecx;`
- L9 _public member_ `SYMS_Reg32 edx;`
- L10 _public member_ `SYMS_Reg32 ebx;`
- L11 _public member_ `SYMS_Reg32 esp;`
- L12 _public member_ `SYMS_Reg32 ebp;`
- L13 _public member_ `SYMS_Reg32 esi;`
- L14 _public member_ `SYMS_Reg32 edi;`
- L15 _public member_ `SYMS_Reg32 fsbase;`
- L16 _public member_ `SYMS_Reg32 gsbase;`
- L17 _public member_ `SYMS_Reg32 eflags;`
- L18 _public member_ `SYMS_Reg32 eip;`
- L19 _public member_ `SYMS_Reg32 dr0;`
- L20 _public member_ `SYMS_Reg32 dr1;`
- L21 _public member_ `SYMS_Reg32 dr2;`
- L22 _public member_ `SYMS_Reg32 dr3;`
- L23 _public member_ `SYMS_Reg32 dr4;`
- L24 _public member_ `SYMS_Reg32 dr5;`
- L25 _public member_ `SYMS_Reg32 dr6;`
- L26 _public member_ `SYMS_Reg32 dr7;`
- L27 _public member_ `SYMS_Reg80 fpr0;`
- L28 _public member_ `SYMS_Reg80 fpr1;`
- L29 _public member_ `SYMS_Reg80 fpr2;`
- L30 _public member_ `SYMS_Reg80 fpr3;`
- L31 _public member_ `SYMS_Reg80 fpr4;`
- L32 _public member_ `SYMS_Reg80 fpr5;`
- L33 _public member_ `SYMS_Reg80 fpr6;`
- L34 _public member_ `SYMS_Reg80 fpr7;`
- L35 _public member_ `SYMS_Reg80 st0;`
- L36 _public member_ `SYMS_Reg80 st1;`
- L37 _public member_ `SYMS_Reg80 st2;`
- L38 _public member_ `SYMS_Reg80 st3;`
- L39 _public member_ `SYMS_Reg80 st4;`
- L40 _public member_ `SYMS_Reg80 st5;`
- L41 _public member_ `SYMS_Reg80 st6;`
- L42 _public member_ `SYMS_Reg80 st7;`
- L43 _public member_ `SYMS_Reg16 fcw;`
- L44 _public member_ `SYMS_Reg16 fsw;`
- L45 _public member_ `SYMS_Reg16 ftw;`
- L46 _public member_ `SYMS_Reg16 fop;`
- L47 _public member_ `SYMS_Reg16 fcs;`
- L48 _public member_ `SYMS_Reg16 fds;`
- L49 _public member_ `SYMS_Reg32 fip;`
- L50 _public member_ `SYMS_Reg32 fdp;`
- L51 _public member_ `SYMS_Reg32 mxcsr;`
- L52 _public member_ `SYMS_Reg32 mxcsr_mask;`
- L53 _public member_ `SYMS_Reg16 ss;`
- L54 _public member_ `SYMS_Reg16 cs;`
- L55 _public member_ `SYMS_Reg16 ds;`
- L56 _public member_ `SYMS_Reg16 es;`
- L57 _public member_ `SYMS_Reg16 fs;`
- L58 _public member_ `SYMS_Reg16 gs;`
- L59 _public member_ `SYMS_Reg256 ymm0;`
- L60 _public member_ `SYMS_Reg256 ymm1;`
- L61 _public member_ `SYMS_Reg256 ymm2;`
- L62 _public member_ `SYMS_Reg256 ymm3;`
- L63 _public member_ `SYMS_Reg256 ymm4;`
- L64 _public member_ `SYMS_Reg256 ymm5;`
- L65 _public member_ `SYMS_Reg256 ymm6;`
- L66 _public member_ `SYMS_Reg256 ymm7;`

#### enum `SYMS_RegX86Code`  
`typedef enum SYMS_RegX86Code`  
_L69-169_
- L71 _public enumerator_ `SYMS_RegX86Code_nil`
- L72 _public enumerator_ `SYMS_RegX86Code_eax`
- L73 _public enumerator_ `SYMS_RegX86Code_ecx`
- L74 _public enumerator_ `SYMS_RegX86Code_edx`
- L75 _public enumerator_ `SYMS_RegX86Code_ebx`
- L76 _public enumerator_ `SYMS_RegX86Code_esp`
- L77 _public enumerator_ `SYMS_RegX86Code_ebp`
- L78 _public enumerator_ `SYMS_RegX86Code_esi`
- L79 _public enumerator_ `SYMS_RegX86Code_edi`
- L80 _public enumerator_ `SYMS_RegX86Code_fsbase`
- L81 _public enumerator_ `SYMS_RegX86Code_gsbase`
- L82 _public enumerator_ `SYMS_RegX86Code_eflags`
- L83 _public enumerator_ `SYMS_RegX86Code_eip`
- L84 _public enumerator_ `SYMS_RegX86Code_dr0`
- L85 _public enumerator_ `SYMS_RegX86Code_dr1`
- L86 _public enumerator_ `SYMS_RegX86Code_dr2`
- L87 _public enumerator_ `SYMS_RegX86Code_dr3`
- L88 _public enumerator_ `SYMS_RegX86Code_dr4`
- L89 _public enumerator_ `SYMS_RegX86Code_dr5`
- L90 _public enumerator_ `SYMS_RegX86Code_dr6`
- L91 _public enumerator_ `SYMS_RegX86Code_dr7`
- L92 _public enumerator_ `SYMS_RegX86Code_fpr0`
- L93 _public enumerator_ `SYMS_RegX86Code_fpr1`
- L94 _public enumerator_ `SYMS_RegX86Code_fpr2`
- L95 _public enumerator_ `SYMS_RegX86Code_fpr3`
- L96 _public enumerator_ `SYMS_RegX86Code_fpr4`
- L97 _public enumerator_ `SYMS_RegX86Code_fpr5`
- L98 _public enumerator_ `SYMS_RegX86Code_fpr6`
- L99 _public enumerator_ `SYMS_RegX86Code_fpr7`
- L100 _public enumerator_ `SYMS_RegX86Code_st0`
- L101 _public enumerator_ `SYMS_RegX86Code_st1`
- L102 _public enumerator_ `SYMS_RegX86Code_st2`
- L103 _public enumerator_ `SYMS_RegX86Code_st3`
- L104 _public enumerator_ `SYMS_RegX86Code_st4`
- L105 _public enumerator_ `SYMS_RegX86Code_st5`
- L106 _public enumerator_ `SYMS_RegX86Code_st6`
- L107 _public enumerator_ `SYMS_RegX86Code_st7`
- L108 _public enumerator_ `SYMS_RegX86Code_fcw`
- L109 _public enumerator_ `SYMS_RegX86Code_fsw`
- L110 _public enumerator_ `SYMS_RegX86Code_ftw`
- L111 _public enumerator_ `SYMS_RegX86Code_fop`
- L112 _public enumerator_ `SYMS_RegX86Code_fcs`
- L113 _public enumerator_ `SYMS_RegX86Code_fds`
- L114 _public enumerator_ `SYMS_RegX86Code_fip`
- L115 _public enumerator_ `SYMS_RegX86Code_fdp`
- L116 _public enumerator_ `SYMS_RegX86Code_mxcsr`
- L117 _public enumerator_ `SYMS_RegX86Code_mxcsr_mask`
- L118 _public enumerator_ `SYMS_RegX86Code_ss`
- L119 _public enumerator_ `SYMS_RegX86Code_cs`
- L120 _public enumerator_ `SYMS_RegX86Code_ds`
- L121 _public enumerator_ `SYMS_RegX86Code_es`
- L122 _public enumerator_ `SYMS_RegX86Code_fs`
- L123 _public enumerator_ `SYMS_RegX86Code_gs`
- L124 _public enumerator_ `SYMS_RegX86Code_ymm0`
- L125 _public enumerator_ `SYMS_RegX86Code_ymm1`
- L126 _public enumerator_ `SYMS_RegX86Code_ymm2`
- L127 _public enumerator_ `SYMS_RegX86Code_ymm3`
- L128 _public enumerator_ `SYMS_RegX86Code_ymm4`
- L129 _public enumerator_ `SYMS_RegX86Code_ymm5`
- L130 _public enumerator_ `SYMS_RegX86Code_ymm6`
- L131 _public enumerator_ `SYMS_RegX86Code_ymm7`
- L133 _public enumerator_ `SYMS_RegX86Code_ax` — ALIASES BEGIN
- L134 _public enumerator_ `SYMS_RegX86Code_cx`
- L135 _public enumerator_ `SYMS_RegX86Code_bx`
- L136 _public enumerator_ `SYMS_RegX86Code_dx`
- L137 _public enumerator_ `SYMS_RegX86Code_sp`
- L138 _public enumerator_ `SYMS_RegX86Code_bp`
- L139 _public enumerator_ `SYMS_RegX86Code_si`
- L140 _public enumerator_ `SYMS_RegX86Code_di`
- L141 _public enumerator_ `SYMS_RegX86Code_ip`
- L142 _public enumerator_ `SYMS_RegX86Code_ah`
- L143 _public enumerator_ `SYMS_RegX86Code_ch`
- L144 _public enumerator_ `SYMS_RegX86Code_dh`
- L145 _public enumerator_ `SYMS_RegX86Code_bh`
- L146 _public enumerator_ `SYMS_RegX86Code_al`
- L147 _public enumerator_ `SYMS_RegX86Code_cl`
- L148 _public enumerator_ `SYMS_RegX86Code_dl`
- L149 _public enumerator_ `SYMS_RegX86Code_bl`
- L150 _public enumerator_ `SYMS_RegX86Code_bpl`
- L151 _public enumerator_ `SYMS_RegX86Code_spl`
- L152 _public enumerator_ `SYMS_RegX86Code_xmm0`
- L153 _public enumerator_ `SYMS_RegX86Code_xmm1`
- L154 _public enumerator_ `SYMS_RegX86Code_xmm2`
- L155 _public enumerator_ `SYMS_RegX86Code_xmm3`
- L156 _public enumerator_ `SYMS_RegX86Code_xmm4`
- L157 _public enumerator_ `SYMS_RegX86Code_xmm5`
- L158 _public enumerator_ `SYMS_RegX86Code_xmm6`
- L159 _public enumerator_ `SYMS_RegX86Code_xmm7`
- L160 _public enumerator_ `SYMS_RegX86Code_mm0`
- L161 _public enumerator_ `SYMS_RegX86Code_mm1`
- L162 _public enumerator_ `SYMS_RegX86Code_mm2`
- L163 _public enumerator_ `SYMS_RegX86Code_mm3`
- L164 _public enumerator_ `SYMS_RegX86Code_mm4`
- L165 _public enumerator_ `SYMS_RegX86Code_mm5`
- L166 _public enumerator_ `SYMS_RegX86Code_mm6`
- L167 _public enumerator_ `SYMS_RegX86Code_mm7`
- L168 _public enumerator_ `SYMS_RegX86Code_COUNT`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_REGS_X86_H`
- L67 _typedef_ `} SYMS_RegX86;`
- L169 _typedef_ `} SYMS_RegX86Code;`
- L171 _variable_ `static SYMS_RegSection syms_reg_section_X86[SYMS_RegX86Code_COUNT] = { {0, 0}, {0, 4}, {4, 4}, {8, 4}, {12, 4}, {16, 4}, {20, 4}, {24, 4}, {28, 4}, {32, 4}, {36, 4}, {40, 4}, {44, 4}, {48, 4}, {52, 4}, {56, 4}, {60, 4}, {64, 4}, {68, 4}, {72, 4}, {76, 4}, {80, 10}, {90, 10}, {100, 10}, {110, 10}, {120, 10}, {130, 10}, {140, 10}, {150, 10}, {160, 10}, {170, 10}, {180, 10}, {190, 10}, {200, 10}, {210, 10}, {220, 10}, {230, 10}, {240, 2}, {242, 2},`
- L271 _variable_ `static SYMS_String8 syms_reg_names_X86[SYMS_RegX86Code_COUNT] = { {(SYMS_U8*)"nil", 3}, {(SYMS_U8*)"eax", 3}, {(SYMS_U8*)"ecx", 3}, {(SYMS_U8*)"edx", 3}, {(SYMS_U8*)"ebx", 3}, {(SYMS_U8*)"esp", 3}, {(SYMS_U8*)"ebp", 3}, {(SYMS_U8*)"esi", 3}, {(SYMS_U8*)"edi", 3}, {(SYMS_U8*)"fsbase", 6}, {(SYMS_U8*)"gsbase", 6}, {(SYMS_U8*)"eflags", 6}, {(SYMS_U8*)"eip", 3}, {(SYMS_U8*)"dr0", 3}, {(SYMS_U8*)"dr1", 3}, {(SYMS_U8*)"dr2", 3}, {(SYMS_U8*)"dr3", 3}, {(SYMS_U8*)"dr4", 3}, {(SYMS_U8*)"dr5", 3}, {(SYMS_U8*)"dr6", 3}, {(SYMS_U8*)"dr7", 3}, {(SYMS_U8*)"fpr0", 4}, {(SYMS_U8*)"fpr1", 4}, {(SYMS_U8*)"fpr2", 4}, {(SYMS_U8*)"fpr3", 4}, {(SYMS_U8*)"fpr4", 4}, {(SYMS_U8*)"fpr5", 4}, {(SYMS_U8*)"fpr6", 4}, {(SYMS_U8*)"fpr7", 4}, {(SYMS_U8*)"st0", 3}, {(SYMS_U8*)"st1", 3}, {(SYMS_U8*)"st2", 3}, {(SYMS_U8*)"st3", 3}, {(SYMS_U8*)"st4", 3}, {(SYMS_U8*)"st5", 3}, {(SYMS_U8*)"st6", 3}, {(SYMS_U8*)"st7", 3}, {(SYMS_U8*)"fcw", 3}, {(SYMS_U8*)"fsw", 3},`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_serial_base.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_SERIAL_BASE_H`
- L7 _prototype_ `SYMS_U64 syms_enum_index_from_cvbasictype(SYMS_U64 v);`
- L11 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvBasicType;`
- L19 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_TypeKind;`
- L23 _prototype_ `SYMS_U64 syms_enum_index_from_dw_c_fa(SYMS_U64 v);`
- L27 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwCFA;`

### `Source/Runtime/SymsLib/syms/core/generated/syms_meta_serial_ext.h` (Other)


#### enum `SYMS_CoffHeaderMember`  
`typedef enum SYMS_CoffHeaderMember`  
_L48-57_
- L49 _public enumerator_ `SYMS_CoffHeaderMember_machine`
- L50 _public enumerator_ `SYMS_CoffHeaderMember_section_count`
- L51 _public enumerator_ `SYMS_CoffHeaderMember_time_date_stamp`
- L52 _public enumerator_ `SYMS_CoffHeaderMember_pointer_to_symbol_table`
- L53 _public enumerator_ `SYMS_CoffHeaderMember_number_of_symbols`
- L54 _public enumerator_ `SYMS_CoffHeaderMember_size_of_optional_header`
- L55 _public enumerator_ `SYMS_CoffHeaderMember_flags`
- L56 _public enumerator_ `SYMS_CoffHeaderMember_COUNT`

#### enum `SYMS_CoffSectionHeaderMember`  
`typedef enum SYMS_CoffSectionHeaderMember`  
_L58-70_
- L59 _public enumerator_ `SYMS_CoffSectionHeaderMember_name`
- L60 _public enumerator_ `SYMS_CoffSectionHeaderMember_virt_size`
- L61 _public enumerator_ `SYMS_CoffSectionHeaderMember_virt_off`
- L62 _public enumerator_ `SYMS_CoffSectionHeaderMember_file_size`
- L63 _public enumerator_ `SYMS_CoffSectionHeaderMember_file_off`
- L64 _public enumerator_ `SYMS_CoffSectionHeaderMember_relocs_file_off`
- L65 _public enumerator_ `SYMS_CoffSectionHeaderMember_lines_file_off`
- L66 _public enumerator_ `SYMS_CoffSectionHeaderMember_reloc_count`
- L67 _public enumerator_ `SYMS_CoffSectionHeaderMember_line_count`
- L68 _public enumerator_ `SYMS_CoffSectionHeaderMember_flags`
- L69 _public enumerator_ `SYMS_CoffSectionHeaderMember_COUNT`

#### enum `SYMS_CvGuidMember`  
`typedef enum SYMS_CvGuidMember`  
_L117-124_
- L118 _public enumerator_ `SYMS_CvGuidMember_data1`
- L119 _public enumerator_ `SYMS_CvGuidMember_data2`
- L120 _public enumerator_ `SYMS_CvGuidMember_data3`
- L121 _public enumerator_ `SYMS_CvGuidMember_data4`
- L122 _public enumerator_ `SYMS_CvGuidMember_data5`
- L123 _public enumerator_ `SYMS_CvGuidMember_COUNT`

#### enum `SYMS_CvAnnotationMember`  
`typedef enum SYMS_CvAnnotationMember`  
_L125-130_
- L126 _public enumerator_ `SYMS_CvAnnotationMember_off`
- L127 _public enumerator_ `SYMS_CvAnnotationMember_seg`
- L128 _public enumerator_ `SYMS_CvAnnotationMember_count`
- L129 _public enumerator_ `SYMS_CvAnnotationMember_COUNT`

#### enum `SYMS_CvRegisterMember`  
`typedef enum SYMS_CvRegisterMember`  
_L131-135_
- L132 _public enumerator_ `SYMS_CvRegisterMember_type`
- L133 _public enumerator_ `SYMS_CvRegisterMember_reg`
- L134 _public enumerator_ `SYMS_CvRegisterMember_COUNT`

#### enum `SYMS_CvBPRelSym32Member`  
`typedef enum SYMS_CvBPRelSym32Member`  
_L136-140_
- L137 _public enumerator_ `SYMS_CvBPRelSym32Member_off`
- L138 _public enumerator_ `SYMS_CvBPRelSym32Member_itype`
- L139 _public enumerator_ `SYMS_CvBPRelSym32Member_COUNT`

#### enum `SYMS_CvVPathSym32Member`  
`typedef enum SYMS_CvVPathSym32Member`  
_L141-147_
- L142 _public enumerator_ `SYMS_CvVPathSym32Member_root`
- L143 _public enumerator_ `SYMS_CvVPathSym32Member_path`
- L144 _public enumerator_ `SYMS_CvVPathSym32Member_off`
- L145 _public enumerator_ `SYMS_CvVPathSym32Member_seg`
- L146 _public enumerator_ `SYMS_CvVPathSym32Member_COUNT`

#### enum `SYMS_CvOEMMember`  
`typedef enum SYMS_CvOEMMember`  
_L148-152_
- L149 _public enumerator_ `SYMS_CvOEMMember_id`
- L150 _public enumerator_ `SYMS_CvOEMMember_itype`
- L151 _public enumerator_ `SYMS_CvOEMMember_COUNT`

#### enum `SYMS_CvSLink32Member`  
`typedef enum SYMS_CvSLink32Member`  
_L153-158_
- L154 _public enumerator_ `SYMS_CvSLink32Member_frame_size`
- L155 _public enumerator_ `SYMS_CvSLink32Member_offset`
- L156 _public enumerator_ `SYMS_CvSLink32Member_reg`
- L157 _public enumerator_ `SYMS_CvSLink32Member_COUNT`

#### enum `SYMS_CvReturnMember`  
`typedef enum SYMS_CvReturnMember`  
_L159-163_
- L160 _public enumerator_ `SYMS_CvReturnMember_flags`
- L161 _public enumerator_ `SYMS_CvReturnMember_style`
- L162 _public enumerator_ `SYMS_CvReturnMember_COUNT`

#### enum `SYMS_CvStartSearchMember`  
`typedef enum SYMS_CvStartSearchMember`  
_L164-168_
- L165 _public enumerator_ `SYMS_CvStartSearchMember_start_symbol`
- L166 _public enumerator_ `SYMS_CvStartSearchMember_segment`
- L167 _public enumerator_ `SYMS_CvStartSearchMember_COUNT`

#### enum `SYMS_CvThread32Member`  
`typedef enum SYMS_CvThread32Member`  
_L169-175_
- L170 _public enumerator_ `SYMS_CvThread32Member_itype`
- L171 _public enumerator_ `SYMS_CvThread32Member_tls_off`
- L172 _public enumerator_ `SYMS_CvThread32Member_tls_seg`
- L173 _public enumerator_ `SYMS_CvThread32Member_name`
- L174 _public enumerator_ `SYMS_CvThread32Member_COUNT`

#### enum `SYMS_CvCompileMember`  
`typedef enum SYMS_CvCompileMember`  
_L176-181_
- L177 _public enumerator_ `SYMS_CvCompileMember_machine`
- L178 _public enumerator_ `SYMS_CvCompileMember_flags`
- L179 _public enumerator_ `SYMS_CvCompileMember_ver_str`
- L180 _public enumerator_ `SYMS_CvCompileMember_COUNT`

#### enum `SYMS_CvEndMember`  
`typedef enum SYMS_CvEndMember`  
_L182-184_
- L183 _public enumerator_ `SYMS_CvEndMember_COUNT`

#### enum `SYMS_CvCompile2Member`  
`typedef enum SYMS_CvCompile2Member`  
_L185-196_
- L186 _public enumerator_ `SYMS_CvCompile2Member_flags`
- L187 _public enumerator_ `SYMS_CvCompile2Member_machine`
- L188 _public enumerator_ `SYMS_CvCompile2Member_ver_fe_major`
- L189 _public enumerator_ `SYMS_CvCompile2Member_ver_fe_minor`
- L190 _public enumerator_ `SYMS_CvCompile2Member_ver_fe_build`
- L191 _public enumerator_ `SYMS_CvCompile2Member_ver_major`
- L192 _public enumerator_ `SYMS_CvCompile2Member_ver_minor`
- L193 _public enumerator_ `SYMS_CvCompile2Member_ver_build`
- L194 _public enumerator_ `SYMS_CvCompile2Member_ver_str`
- L195 _public enumerator_ `SYMS_CvCompile2Member_COUNT`

#### enum `SYMS_CvCompile3Member`  
`typedef enum SYMS_CvCompile3Member`  
_L197-210_
- L198 _public enumerator_ `SYMS_CvCompile3Member_flags`
- L199 _public enumerator_ `SYMS_CvCompile3Member_machine`
- L200 _public enumerator_ `SYMS_CvCompile3Member_ver_fe_major`
- L201 _public enumerator_ `SYMS_CvCompile3Member_ver_fe_minor`
- L202 _public enumerator_ `SYMS_CvCompile3Member_ver_fe_build`
- L203 _public enumerator_ `SYMS_CvCompile3Member_ver_feqfe`
- L204 _public enumerator_ `SYMS_CvCompile3Member_ver_major`
- L205 _public enumerator_ `SYMS_CvCompile3Member_ver_minor`
- L206 _public enumerator_ `SYMS_CvCompile3Member_ver_build`
- L207 _public enumerator_ `SYMS_CvCompile3Member_ver_qfe`
- L208 _public enumerator_ `SYMS_CvCompile3Member_version`
- L209 _public enumerator_ `SYMS_CvCompile3Member_COUNT`

#### enum `SYMS_CvObjnameMember`  
`typedef enum SYMS_CvObjnameMember`  
_L211-215_
- L212 _public enumerator_ `SYMS_CvObjnameMember_sig`
- L213 _public enumerator_ `SYMS_CvObjnameMember_name`
- L214 _public enumerator_ `SYMS_CvObjnameMember_COUNT`

#### enum `SYMS_CvUNamespaceMember`  
`typedef enum SYMS_CvUNamespaceMember`  
_L216-219_
- L217 _public enumerator_ `SYMS_CvUNamespaceMember_name`
- L218 _public enumerator_ `SYMS_CvUNamespaceMember_COUNT`

#### enum `SYMS_CvRef2Member`  
`typedef enum SYMS_CvRef2Member`  
_L220-226_
- L221 _public enumerator_ `SYMS_CvRef2Member_sum_name`
- L222 _public enumerator_ `SYMS_CvRef2Member_sym_off`
- L223 _public enumerator_ `SYMS_CvRef2Member_imod`
- L224 _public enumerator_ `SYMS_CvRef2Member_name`
- L225 _public enumerator_ `SYMS_CvRef2Member_COUNT`

#### enum `SYMS_CvSepcodeMember`  
`typedef enum SYMS_CvSepcodeMember`  
_L227-237_
- L228 _public enumerator_ `SYMS_CvSepcodeMember_parent`
- L229 _public enumerator_ `SYMS_CvSepcodeMember_end`
- L230 _public enumerator_ `SYMS_CvSepcodeMember_len`
- L231 _public enumerator_ `SYMS_CvSepcodeMember_flags`
- L232 _public enumerator_ `SYMS_CvSepcodeMember_sec_off`
- L233 _public enumerator_ `SYMS_CvSepcodeMember_sec_parent_off`
- L234 _public enumerator_ `SYMS_CvSepcodeMember_sec`
- L235 _public enumerator_ `SYMS_CvSepcodeMember_sec_parent`
- L236 _public enumerator_ `SYMS_CvSepcodeMember_COUNT`

#### enum `SYMS_CvSlotsym32Member`  
`typedef enum SYMS_CvSlotsym32Member`  
_L238-242_
- L239 _public enumerator_ `SYMS_CvSlotsym32Member_slot_index`
- L240 _public enumerator_ `SYMS_CvSlotsym32Member_type`
- L241 _public enumerator_ `SYMS_CvSlotsym32Member_COUNT`

#### enum `SYMS_CvPogoInfoMember`  
`typedef enum SYMS_CvPogoInfoMember`  
_L243-249_
- L244 _public enumerator_ `SYMS_CvPogoInfoMember_invocations`
- L245 _public enumerator_ `SYMS_CvPogoInfoMember_dynamic_inst_count`
- L246 _public enumerator_ `SYMS_CvPogoInfoMember_static_inst_count`
- L247 _public enumerator_ `SYMS_CvPogoInfoMember_post_inline_static_inst_count`
- L248 _public enumerator_ `SYMS_CvPogoInfoMember_COUNT`

#### enum `SYMS_CvManyregMember`  
`typedef enum SYMS_CvManyregMember`  
_L250-254_
- L251 _public enumerator_ `SYMS_CvManyregMember_type`
- L252 _public enumerator_ `SYMS_CvManyregMember_count`
- L253 _public enumerator_ `SYMS_CvManyregMember_COUNT`

#### enum `SYMS_CvManyreg2Member`  
`typedef enum SYMS_CvManyreg2Member`  
_L255-259_
- L256 _public enumerator_ `SYMS_CvManyreg2Member_type`
- L257 _public enumerator_ `SYMS_CvManyreg2Member_count`
- L258 _public enumerator_ `SYMS_CvManyreg2Member_COUNT`

#### enum `SYMS_CvFrameprocMember`  
`typedef enum SYMS_CvFrameprocMember`  
_L260-269_
- L261 _public enumerator_ `SYMS_CvFrameprocMember_frame_size`
- L262 _public enumerator_ `SYMS_CvFrameprocMember_pad_size`
- L263 _public enumerator_ `SYMS_CvFrameprocMember_pad_off`
- L264 _public enumerator_ `SYMS_CvFrameprocMember_save_reg_size`
- L265 _public enumerator_ `SYMS_CvFrameprocMember_eh_off`
- L266 _public enumerator_ `SYMS_CvFrameprocMember_eh_sec`
- L267 _public enumerator_ `SYMS_CvFrameprocMember_flags`
- L268 _public enumerator_ `SYMS_CvFrameprocMember_COUNT`

#### enum `SYMS_CvThunk32Member`  
`typedef enum SYMS_CvThunk32Member`  
_L270-280_
- L271 _public enumerator_ `SYMS_CvThunk32Member_parent`
- L272 _public enumerator_ `SYMS_CvThunk32Member_end`
- L273 _public enumerator_ `SYMS_CvThunk32Member_next`
- L274 _public enumerator_ `SYMS_CvThunk32Member_off`
- L275 _public enumerator_ `SYMS_CvThunk32Member_sec`
- L276 _public enumerator_ `SYMS_CvThunk32Member_len`
- L277 _public enumerator_ `SYMS_CvThunk32Member_ord`
- L278 _public enumerator_ `SYMS_CvThunk32Member_name`
- L279 _public enumerator_ `SYMS_CvThunk32Member_COUNT`

#### enum `SYMS_CvBlock32Member`  
`typedef enum SYMS_CvBlock32Member`  
_L281-289_
- L282 _public enumerator_ `SYMS_CvBlock32Member_par`
- L283 _public enumerator_ `SYMS_CvBlock32Member_end`
- L284 _public enumerator_ `SYMS_CvBlock32Member_len`
- L285 _public enumerator_ `SYMS_CvBlock32Member_off`
- L286 _public enumerator_ `SYMS_CvBlock32Member_sec`
- L287 _public enumerator_ `SYMS_CvBlock32Member_name`
- L288 _public enumerator_ `SYMS_CvBlock32Member_COUNT`

#### enum `SYMS_CvLabel32Member`  
`typedef enum SYMS_CvLabel32Member`  
_L290-296_
- L291 _public enumerator_ `SYMS_CvLabel32Member_off`
- L292 _public enumerator_ `SYMS_CvLabel32Member_sec`
- L293 _public enumerator_ `SYMS_CvLabel32Member_flags`
- L294 _public enumerator_ `SYMS_CvLabel32Member_name`
- L295 _public enumerator_ `SYMS_CvLabel32Member_COUNT`

#### enum `SYMS_CvConstantMember`  
`typedef enum SYMS_CvConstantMember`  
_L297-302_
- L298 _public enumerator_ `SYMS_CvConstantMember_itype`
- L299 _public enumerator_ `SYMS_CvConstantMember_num`
- L300 _public enumerator_ `SYMS_CvConstantMember_name`
- L301 _public enumerator_ `SYMS_CvConstantMember_COUNT`

#### enum `SYMS_CvUDTMember`  
`typedef enum SYMS_CvUDTMember`  
_L303-307_
- L304 _public enumerator_ `SYMS_CvUDTMember_itype`
- L305 _public enumerator_ `SYMS_CvUDTMember_name`
- L306 _public enumerator_ `SYMS_CvUDTMember_COUNT`

#### enum `SYMS_CvTrampolineMember`  
`typedef enum SYMS_CvTrampolineMember`  
_L308-316_
- L309 _public enumerator_ `SYMS_CvTrampolineMember_type`
- L310 _public enumerator_ `SYMS_CvTrampolineMember_thunk_size`
- L311 _public enumerator_ `SYMS_CvTrampolineMember_thunk_sec_off`
- L312 _public enumerator_ `SYMS_CvTrampolineMember_target_sec_off`
- L313 _public enumerator_ `SYMS_CvTrampolineMember_thunk_sec`
- L314 _public enumerator_ `SYMS_CvTrampolineMember_target_sec`
- L315 _public enumerator_ `SYMS_CvTrampolineMember_COUNT`

#### enum `SYMS_CvSectionMember`  
`typedef enum SYMS_CvSectionMember`  
_L317-326_
- L318 _public enumerator_ `SYMS_CvSectionMember_sec_index`
- L319 _public enumerator_ `SYMS_CvSectionMember_align`
- L320 _public enumerator_ `SYMS_CvSectionMember_pad`
- L321 _public enumerator_ `SYMS_CvSectionMember_rva`
- L322 _public enumerator_ `SYMS_CvSectionMember_size`
- L323 _public enumerator_ `SYMS_CvSectionMember_characteristics`
- L324 _public enumerator_ `SYMS_CvSectionMember_name`
- L325 _public enumerator_ `SYMS_CvSectionMember_COUNT`

#### enum `SYMS_CvCoffGroupMember`  
`typedef enum SYMS_CvCoffGroupMember`  
_L327-334_
- L328 _public enumerator_ `SYMS_CvCoffGroupMember_size`
- L329 _public enumerator_ `SYMS_CvCoffGroupMember_characteristics`
- L330 _public enumerator_ `SYMS_CvCoffGroupMember_off`
- L331 _public enumerator_ `SYMS_CvCoffGroupMember_sec`
- L332 _public enumerator_ `SYMS_CvCoffGroupMember_name`
- L333 _public enumerator_ `SYMS_CvCoffGroupMember_COUNT`

#### enum `SYMS_CvExportMember`  
`typedef enum SYMS_CvExportMember`  
_L335-340_
- L336 _public enumerator_ `SYMS_CvExportMember_ordinal`
- L337 _public enumerator_ `SYMS_CvExportMember_flags`
- L338 _public enumerator_ `SYMS_CvExportMember_name`
- L339 _public enumerator_ `SYMS_CvExportMember_COUNT`

#### enum `SYMS_CvCallSiteInfoMember`  
`typedef enum SYMS_CvCallSiteInfoMember`  
_L341-347_
- L342 _public enumerator_ `SYMS_CvCallSiteInfoMember_off`
- L343 _public enumerator_ `SYMS_CvCallSiteInfoMember_sec`
- L344 _public enumerator_ `SYMS_CvCallSiteInfoMember_pad`
- L345 _public enumerator_ `SYMS_CvCallSiteInfoMember_itype`
- L346 _public enumerator_ `SYMS_CvCallSiteInfoMember_COUNT`

#### enum `SYMS_CvFrameCookieMember`  
`typedef enum SYMS_CvFrameCookieMember`  
_L348-354_
- L349 _public enumerator_ `SYMS_CvFrameCookieMember_off`
- L350 _public enumerator_ `SYMS_CvFrameCookieMember_reg`
- L351 _public enumerator_ `SYMS_CvFrameCookieMember_kind`
- L352 _public enumerator_ `SYMS_CvFrameCookieMember_flags`
- L353 _public enumerator_ `SYMS_CvFrameCookieMember_COUNT`

#### enum `SYMS_CvEnvblockMember`  
`typedef enum SYMS_CvEnvblockMember`  
_L355-359_
- L356 _public enumerator_ `SYMS_CvEnvblockMember_flags`
- L357 _public enumerator_ `SYMS_CvEnvblockMember_rgsz`
- L358 _public enumerator_ `SYMS_CvEnvblockMember_COUNT`

#### enum `SYMS_CvLocalMember`  
`typedef enum SYMS_CvLocalMember`  
_L360-365_
- L361 _public enumerator_ `SYMS_CvLocalMember_itype`
- L362 _public enumerator_ `SYMS_CvLocalMember_flags`
- L363 _public enumerator_ `SYMS_CvLocalMember_name`
- L364 _public enumerator_ `SYMS_CvLocalMember_COUNT`

#### enum `SYMS_CvLvarAddrRangeMember`  
`typedef enum SYMS_CvLvarAddrRangeMember`  
_L366-371_
- L367 _public enumerator_ `SYMS_CvLvarAddrRangeMember_off`
- L368 _public enumerator_ `SYMS_CvLvarAddrRangeMember_sec`
- L369 _public enumerator_ `SYMS_CvLvarAddrRangeMember_len`
- L370 _public enumerator_ `SYMS_CvLvarAddrRangeMember_COUNT`

#### enum `SYMS_CvLvarAddrGapMember`  
`typedef enum SYMS_CvLvarAddrGapMember`  
_L372-376_
- L373 _public enumerator_ `SYMS_CvLvarAddrGapMember_off`
- L374 _public enumerator_ `SYMS_CvLvarAddrGapMember_len`
- L375 _public enumerator_ `SYMS_CvLvarAddrGapMember_COUNT`

#### enum `SYMS_CvDefrangeMember`  
`typedef enum SYMS_CvDefrangeMember`  
_L377-382_
- L378 _public enumerator_ `SYMS_CvDefrangeMember_program`
- L379 _public enumerator_ `SYMS_CvDefrangeMember_range`
- L380 _public enumerator_ `SYMS_CvDefrangeMember_gaps`
- L381 _public enumerator_ `SYMS_CvDefrangeMember_COUNT`

#### enum `SYMS_CvDefrangeSubfieldMember`  
`typedef enum SYMS_CvDefrangeSubfieldMember`  
_L383-389_
- L384 _public enumerator_ `SYMS_CvDefrangeSubfieldMember_program`
- L385 _public enumerator_ `SYMS_CvDefrangeSubfieldMember_off_in_parent`
- L386 _public enumerator_ `SYMS_CvDefrangeSubfieldMember_range`
- L387 _public enumerator_ `SYMS_CvDefrangeSubfieldMember_gaps`
- L388 _public enumerator_ `SYMS_CvDefrangeSubfieldMember_COUNT`

#### enum `SYMS_CvDefrangeRegisterMember`  
`typedef enum SYMS_CvDefrangeRegisterMember`  
_L390-396_
- L391 _public enumerator_ `SYMS_CvDefrangeRegisterMember_reg`
- L392 _public enumerator_ `SYMS_CvDefrangeRegisterMember_attribs`
- L393 _public enumerator_ `SYMS_CvDefrangeRegisterMember_range`
- L394 _public enumerator_ `SYMS_CvDefrangeRegisterMember_gaps`
- L395 _public enumerator_ `SYMS_CvDefrangeRegisterMember_COUNT`

#### enum `SYMS_CvDefrangeFramepointerRelMember`  
`typedef enum SYMS_CvDefrangeFramepointerRelMember`  
_L397-402_
- L398 _public enumerator_ `SYMS_CvDefrangeFramepointerRelMember_off`
- L399 _public enumerator_ `SYMS_CvDefrangeFramepointerRelMember_range`
- L400 _public enumerator_ `SYMS_CvDefrangeFramepointerRelMember_gaps`
- L401 _public enumerator_ `SYMS_CvDefrangeFramepointerRelMember_COUNT`

#### enum `SYMS_CvDefrangeSubfieldRegisterMember`  
`typedef enum SYMS_CvDefrangeSubfieldRegisterMember`  
_L403-410_
- L404 _public enumerator_ `SYMS_CvDefrangeSubfieldRegisterMember_reg`
- L405 _public enumerator_ `SYMS_CvDefrangeSubfieldRegisterMember_attribs`
- L406 _public enumerator_ `SYMS_CvDefrangeSubfieldRegisterMember_off_parent`
- L407 _public enumerator_ `SYMS_CvDefrangeSubfieldRegisterMember_range`
- L408 _public enumerator_ `SYMS_CvDefrangeSubfieldRegisterMember_gaps`
- L409 _public enumerator_ `SYMS_CvDefrangeSubfieldRegisterMember_COUNT`

#### enum `SYMS_CvDefrangeFramepointerRelFullScopeMember`  
`typedef enum SYMS_CvDefrangeFramepointerRelFullScopeMember`  
_L411-414_
- L412 _public enumerator_ `SYMS_CvDefrangeFramepointerRelFullScopeMember_off`
- L413 _public enumerator_ `SYMS_CvDefrangeFramepointerRelFullScopeMember_COUNT`

#### enum `SYMS_CvDefrangeRegisterRelMember`  
`typedef enum SYMS_CvDefrangeRegisterRelMember`  
_L415-422_
- L416 _public enumerator_ `SYMS_CvDefrangeRegisterRelMember_reg`
- L417 _public enumerator_ `SYMS_CvDefrangeRegisterRelMember_flags`
- L418 _public enumerator_ `SYMS_CvDefrangeRegisterRelMember_reg_off`
- L419 _public enumerator_ `SYMS_CvDefrangeRegisterRelMember_range`
- L420 _public enumerator_ `SYMS_CvDefrangeRegisterRelMember_gaps`
- L421 _public enumerator_ `SYMS_CvDefrangeRegisterRelMember_COUNT`

#### enum `SYMS_CvData32Member`  
`typedef enum SYMS_CvData32Member`  
_L423-429_
- L424 _public enumerator_ `SYMS_CvData32Member_itype`
- L425 _public enumerator_ `SYMS_CvData32Member_sec_off`
- L426 _public enumerator_ `SYMS_CvData32Member_sec`
- L427 _public enumerator_ `SYMS_CvData32Member_name`
- L428 _public enumerator_ `SYMS_CvData32Member_COUNT`

#### enum `SYMS_CvPubsym32Member`  
`typedef enum SYMS_CvPubsym32Member`  
_L430-436_
- L431 _public enumerator_ `SYMS_CvPubsym32Member_flags`
- L432 _public enumerator_ `SYMS_CvPubsym32Member_off`
- L433 _public enumerator_ `SYMS_CvPubsym32Member_sec`
- L434 _public enumerator_ `SYMS_CvPubsym32Member_name`
- L435 _public enumerator_ `SYMS_CvPubsym32Member_COUNT`

#### enum `SYMS_CvGProc16Member`  
`typedef enum SYMS_CvGProc16Member`  
_L437-439_
- L438 _public enumerator_ `SYMS_CvGProc16Member_COUNT`

#### enum `SYMS_CvGProc3216tMember`  
`typedef enum SYMS_CvGProc3216tMember`  
_L440-442_
- L441 _public enumerator_ `SYMS_CvGProc3216tMember_COUNT`

#### enum `SYMS_CvProc32Member`  
`typedef enum SYMS_CvProc32Member`  
_L443-456_
- L444 _public enumerator_ `SYMS_CvProc32Member_parent`
- L445 _public enumerator_ `SYMS_CvProc32Member_end`
- L446 _public enumerator_ `SYMS_CvProc32Member_next`
- L447 _public enumerator_ `SYMS_CvProc32Member_len`
- L448 _public enumerator_ `SYMS_CvProc32Member_dbg_start`
- L449 _public enumerator_ `SYMS_CvProc32Member_dbg_end`
- L450 _public enumerator_ `SYMS_CvProc32Member_itype`
- L451 _public enumerator_ `SYMS_CvProc32Member_off`
- L452 _public enumerator_ `SYMS_CvProc32Member_sec`
- L453 _public enumerator_ `SYMS_CvProc32Member_flags`
- L454 _public enumerator_ `SYMS_CvProc32Member_name`
- L455 _public enumerator_ `SYMS_CvProc32Member_COUNT`

#### enum `SYMS_CvRegrel32Member`  
`typedef enum SYMS_CvRegrel32Member`  
_L457-463_
- L458 _public enumerator_ `SYMS_CvRegrel32Member_reg_off`
- L459 _public enumerator_ `SYMS_CvRegrel32Member_itype`
- L460 _public enumerator_ `SYMS_CvRegrel32Member_reg`
- L461 _public enumerator_ `SYMS_CvRegrel32Member_name`
- L462 _public enumerator_ `SYMS_CvRegrel32Member_COUNT`

#### enum `SYMS_CvBuildInfoMember`  
`typedef enum SYMS_CvBuildInfoMember`  
_L464-467_
- L465 _public enumerator_ `SYMS_CvBuildInfoMember_id`
- L466 _public enumerator_ `SYMS_CvBuildInfoMember_COUNT`

#### enum `SYMS_CvFunctionListMember`  
`typedef enum SYMS_CvFunctionListMember`  
_L468-473_
- L469 _public enumerator_ `SYMS_CvFunctionListMember_count`
- L470 _public enumerator_ `SYMS_CvFunctionListMember_func`
- L471 _public enumerator_ `SYMS_CvFunctionListMember_invocations`
- L472 _public enumerator_ `SYMS_CvFunctionListMember_COUNT`

#### enum `SYMS_CvInlineSiteMember`  
`typedef enum SYMS_CvInlineSiteMember`  
_L474-480_
- L475 _public enumerator_ `SYMS_CvInlineSiteMember_parent_offset`
- L476 _public enumerator_ `SYMS_CvInlineSiteMember_end_offset`
- L477 _public enumerator_ `SYMS_CvInlineSiteMember_inlinee`
- L478 _public enumerator_ `SYMS_CvInlineSiteMember_binaryAnnotations`
- L479 _public enumerator_ `SYMS_CvInlineSiteMember_COUNT`

#### enum `SYMS_CvInlineSite2Member`  
`typedef enum SYMS_CvInlineSite2Member`  
_L481-488_
- L482 _public enumerator_ `SYMS_CvInlineSite2Member_parent_offset`
- L483 _public enumerator_ `SYMS_CvInlineSite2Member_end_offset`
- L484 _public enumerator_ `SYMS_CvInlineSite2Member_inlinee`
- L485 _public enumerator_ `SYMS_CvInlineSite2Member_invocations`
- L486 _public enumerator_ `SYMS_CvInlineSite2Member_binaryAnnotations`
- L487 _public enumerator_ `SYMS_CvInlineSite2Member_COUNT`

#### enum `SYMS_CvInlineSiteEndMember`  
`typedef enum SYMS_CvInlineSiteEndMember`  
_L489-491_
- L490 _public enumerator_ `SYMS_CvInlineSiteEndMember_COUNT`

#### enum `SYMS_CvInlineesMember`  
`typedef enum SYMS_CvInlineesMember`  
_L492-496_
- L493 _public enumerator_ `SYMS_CvInlineesMember_count`
- L494 _public enumerator_ `SYMS_CvInlineesMember_desc`
- L495 _public enumerator_ `SYMS_CvInlineesMember_COUNT`

#### enum `SYMS_CvFileStaticMember`  
`typedef enum SYMS_CvFileStaticMember`  
_L497-503_
- L498 _public enumerator_ `SYMS_CvFileStaticMember_itype`
- L499 _public enumerator_ `SYMS_CvFileStaticMember_mod_offset`
- L500 _public enumerator_ `SYMS_CvFileStaticMember_flags`
- L501 _public enumerator_ `SYMS_CvFileStaticMember_name`
- L502 _public enumerator_ `SYMS_CvFileStaticMember_COUNT`

#### enum `SYMS_CvHeapAllocSiteMember`  
`typedef enum SYMS_CvHeapAllocSiteMember`  
_L504-510_
- L505 _public enumerator_ `SYMS_CvHeapAllocSiteMember_off`
- L506 _public enumerator_ `SYMS_CvHeapAllocSiteMember_sec`
- L507 _public enumerator_ `SYMS_CvHeapAllocSiteMember_call_inst_len`
- L508 _public enumerator_ `SYMS_CvHeapAllocSiteMember_itype`
- L509 _public enumerator_ `SYMS_CvHeapAllocSiteMember_COUNT`

#### enum `SYMS_CvLocalVarAttrMember`  
`typedef enum SYMS_CvLocalVarAttrMember`  
_L511-516_
- L512 _public enumerator_ `SYMS_CvLocalVarAttrMember_off`
- L513 _public enumerator_ `SYMS_CvLocalVarAttrMember_seg`
- L514 _public enumerator_ `SYMS_CvLocalVarAttrMember_flags`
- L515 _public enumerator_ `SYMS_CvLocalVarAttrMember_COUNT`

#### enum `SYMS_CvFramerelMember`  
`typedef enum SYMS_CvFramerelMember`  
_L517-522_
- L518 _public enumerator_ `SYMS_CvFramerelMember_off`
- L519 _public enumerator_ `SYMS_CvFramerelMember_itype`
- L520 _public enumerator_ `SYMS_CvFramerelMember_attr`
- L521 _public enumerator_ `SYMS_CvFramerelMember_COUNT`

#### enum `SYMS_CvAttrRegMember`  
`typedef enum SYMS_CvAttrRegMember`  
_L523-528_
- L524 _public enumerator_ `SYMS_CvAttrRegMember_itype`
- L525 _public enumerator_ `SYMS_CvAttrRegMember_attr`
- L526 _public enumerator_ `SYMS_CvAttrRegMember_reg`
- L527 _public enumerator_ `SYMS_CvAttrRegMember_COUNT`

#### enum `SYMS_CvAttrRegrelMember`  
`typedef enum SYMS_CvAttrRegrelMember`  
_L529-535_
- L530 _public enumerator_ `SYMS_CvAttrRegrelMember_off`
- L531 _public enumerator_ `SYMS_CvAttrRegrelMember_itype`
- L532 _public enumerator_ `SYMS_CvAttrRegrelMember_reg`
- L533 _public enumerator_ `SYMS_CvAttrRegrelMember_attr`
- L534 _public enumerator_ `SYMS_CvAttrRegrelMember_COUNT`

#### enum `SYMS_CvAttrManyregMember`  
`typedef enum SYMS_CvAttrManyregMember`  
_L536-541_
- L537 _public enumerator_ `SYMS_CvAttrManyregMember_itype`
- L538 _public enumerator_ `SYMS_CvAttrManyregMember_attr`
- L539 _public enumerator_ `SYMS_CvAttrManyregMember_reg_count`
- L540 _public enumerator_ `SYMS_CvAttrManyregMember_COUNT`

#### enum `SYMS_CvFastLinkMember`  
`typedef enum SYMS_CvFastLinkMember`  
_L542-546_
- L543 _public enumerator_ `SYMS_CvFastLinkMember_itype`
- L544 _public enumerator_ `SYMS_CvFastLinkMember_flags`
- L545 _public enumerator_ `SYMS_CvFastLinkMember_COUNT`

#### enum `SYMS_CvArmSwitchTableMember`  
`typedef enum SYMS_CvArmSwitchTableMember`  
_L547-557_
- L548 _public enumerator_ `SYMS_CvArmSwitchTableMember_off_base`
- L549 _public enumerator_ `SYMS_CvArmSwitchTableMember_sec_base`
- L550 _public enumerator_ `SYMS_CvArmSwitchTableMember_switch_type`
- L551 _public enumerator_ `SYMS_CvArmSwitchTableMember_off_branch`
- L552 _public enumerator_ `SYMS_CvArmSwitchTableMember_off_table`
- L553 _public enumerator_ `SYMS_CvArmSwitchTableMember_sec_branch`
- L554 _public enumerator_ `SYMS_CvArmSwitchTableMember_sec_table`
- L555 _public enumerator_ `SYMS_CvArmSwitchTableMember_entry_count`
- L556 _public enumerator_ `SYMS_CvArmSwitchTableMember_COUNT`

#### enum `SYMS_CvRefMiniPdbMember`  
`typedef enum SYMS_CvRefMiniPdbMember`  
_L558-563_
- L559 _public enumerator_ `SYMS_CvRefMiniPdbMember_data`
- L560 _public enumerator_ `SYMS_CvRefMiniPdbMember_imod`
- L561 _public enumerator_ `SYMS_CvRefMiniPdbMember_flags`
- L562 _public enumerator_ `SYMS_CvRefMiniPdbMember_COUNT`

#### enum `SYMS_CvModTypeRefMember`  
`typedef enum SYMS_CvModTypeRefMember`  
_L564-569_
- L565 _public enumerator_ `SYMS_CvModTypeRefMember_flags`
- L566 _public enumerator_ `SYMS_CvModTypeRefMember_word0`
- L567 _public enumerator_ `SYMS_CvModTypeRefMember_word1`
- L568 _public enumerator_ `SYMS_CvModTypeRefMember_COUNT`

#### enum `SYMS_CvDiscardedMember`  
`typedef enum SYMS_CvDiscardedMember`  
_L570-575_
- L571 _public enumerator_ `SYMS_CvDiscardedMember_flags`
- L572 _public enumerator_ `SYMS_CvDiscardedMember_file_id`
- L573 _public enumerator_ `SYMS_CvDiscardedMember_file_ln`
- L574 _public enumerator_ `SYMS_CvDiscardedMember_COUNT`

#### enum `SYMS_CvLeafPreCompMember`  
`typedef enum SYMS_CvLeafPreCompMember`  
_L576-582_
- L577 _public enumerator_ `SYMS_CvLeafPreCompMember_start_index`
- L578 _public enumerator_ `SYMS_CvLeafPreCompMember_count`
- L579 _public enumerator_ `SYMS_CvLeafPreCompMember_signature`
- L580 _public enumerator_ `SYMS_CvLeafPreCompMember_name`
- L581 _public enumerator_ `SYMS_CvLeafPreCompMember_COUNT`

#### enum `SYMS_CvLeafTypeServerMember`  
`typedef enum SYMS_CvLeafTypeServerMember`  
_L583-588_
- L584 _public enumerator_ `SYMS_CvLeafTypeServerMember_sig`
- L585 _public enumerator_ `SYMS_CvLeafTypeServerMember_age`
- L586 _public enumerator_ `SYMS_CvLeafTypeServerMember_name`
- L587 _public enumerator_ `SYMS_CvLeafTypeServerMember_COUNT`

#### enum `SYMS_CvLeafTypeServer2Member`  
`typedef enum SYMS_CvLeafTypeServer2Member`  
_L589-594_
- L590 _public enumerator_ `SYMS_CvLeafTypeServer2Member_sig70`
- L591 _public enumerator_ `SYMS_CvLeafTypeServer2Member_age`
- L592 _public enumerator_ `SYMS_CvLeafTypeServer2Member_name`
- L593 _public enumerator_ `SYMS_CvLeafTypeServer2Member_COUNT`

#### enum `SYMS_CvLeafBuildInfoMember`  
`typedef enum SYMS_CvLeafBuildInfoMember`  
_L595-599_
- L596 _public enumerator_ `SYMS_CvLeafBuildInfoMember_count`
- L597 _public enumerator_ `SYMS_CvLeafBuildInfoMember_arg`
- L598 _public enumerator_ `SYMS_CvLeafBuildInfoMember_COUNT`

#### enum `SYMS_CvLeafSkip_16tMember`  
`typedef enum SYMS_CvLeafSkip_16tMember`  
_L600-603_
- L601 _public enumerator_ `SYMS_CvLeafSkip_16tMember_type`
- L602 _public enumerator_ `SYMS_CvLeafSkip_16tMember_COUNT`

#### enum `SYMS_CvLeafSkipMember`  
`typedef enum SYMS_CvLeafSkipMember`  
_L604-607_
- L605 _public enumerator_ `SYMS_CvLeafSkipMember_type`
- L606 _public enumerator_ `SYMS_CvLeafSkipMember_COUNT`

#### enum `SYMS_CvLeafVTShapeMember`  
`typedef enum SYMS_CvLeafVTShapeMember`  
_L608-611_
- L609 _public enumerator_ `SYMS_CvLeafVTShapeMember_count`
- L610 _public enumerator_ `SYMS_CvLeafVTShapeMember_COUNT`

#### enum `SYMS_CvLeafLabelMember`  
`typedef enum SYMS_CvLeafLabelMember`  
_L612-615_
- L613 _public enumerator_ `SYMS_CvLeafLabelMember_mode`
- L614 _public enumerator_ `SYMS_CvLeafLabelMember_COUNT`

#### enum `SYMS_CvLeafModifierMember`  
`typedef enum SYMS_CvLeafModifierMember`  
_L616-620_
- L617 _public enumerator_ `SYMS_CvLeafModifierMember_itype`
- L618 _public enumerator_ `SYMS_CvLeafModifierMember_flags`
- L619 _public enumerator_ `SYMS_CvLeafModifierMember_COUNT`

#### enum `SYMS_CvLeafPointerMember`  
`typedef enum SYMS_CvLeafPointerMember`  
_L621-625_
- L622 _public enumerator_ `SYMS_CvLeafPointerMember_itype`
- L623 _public enumerator_ `SYMS_CvLeafPointerMember_attr`
- L624 _public enumerator_ `SYMS_CvLeafPointerMember_COUNT`

#### enum `SYMS_CvLeafProcedureMember`  
`typedef enum SYMS_CvLeafProcedureMember`  
_L626-633_
- L627 _public enumerator_ `SYMS_CvLeafProcedureMember_ret_itype`
- L628 _public enumerator_ `SYMS_CvLeafProcedureMember_call_kind`
- L629 _public enumerator_ `SYMS_CvLeafProcedureMember_funcattr`
- L630 _public enumerator_ `SYMS_CvLeafProcedureMember_arg_count`
- L631 _public enumerator_ `SYMS_CvLeafProcedureMember_arg_itype`
- L632 _public enumerator_ `SYMS_CvLeafProcedureMember_COUNT`

#### enum `SYMS_CvLeafMFunctionMember`  
`typedef enum SYMS_CvLeafMFunctionMember`  
_L634-644_
- L635 _public enumerator_ `SYMS_CvLeafMFunctionMember_ret_itype`
- L636 _public enumerator_ `SYMS_CvLeafMFunctionMember_class_itype`
- L637 _public enumerator_ `SYMS_CvLeafMFunctionMember_this_itype`
- L638 _public enumerator_ `SYMS_CvLeafMFunctionMember_call_kind`
- L639 _public enumerator_ `SYMS_CvLeafMFunctionMember_funcattr`
- L640 _public enumerator_ `SYMS_CvLeafMFunctionMember_arg_count`
- L641 _public enumerator_ `SYMS_CvLeafMFunctionMember_arg_itype`
- L642 _public enumerator_ `SYMS_CvLeafMFunctionMember_thisadjust`
- L643 _public enumerator_ `SYMS_CvLeafMFunctionMember_COUNT`

#### enum `SYMS_CvLeafArgListMember`  
`typedef enum SYMS_CvLeafArgListMember`  
_L645-648_
- L646 _public enumerator_ `SYMS_CvLeafArgListMember_count`
- L647 _public enumerator_ `SYMS_CvLeafArgListMember_COUNT`

#### enum `SYMS_CvLeafBitFieldMember`  
`typedef enum SYMS_CvLeafBitFieldMember`  
_L649-654_
- L650 _public enumerator_ `SYMS_CvLeafBitFieldMember_itype`
- L651 _public enumerator_ `SYMS_CvLeafBitFieldMember_len`
- L652 _public enumerator_ `SYMS_CvLeafBitFieldMember_pos`
- L653 _public enumerator_ `SYMS_CvLeafBitFieldMember_COUNT`

#### enum `SYMS_CvLeafIndexMember`  
`typedef enum SYMS_CvLeafIndexMember`  
_L655-659_
- L656 _public enumerator_ `SYMS_CvLeafIndexMember_pad`
- L657 _public enumerator_ `SYMS_CvLeafIndexMember_itype`
- L658 _public enumerator_ `SYMS_CvLeafIndexMember_COUNT`

#### enum `SYMS_CvLeafArrayMember`  
`typedef enum SYMS_CvLeafArrayMember`  
_L660-664_
- L661 _public enumerator_ `SYMS_CvLeafArrayMember_entry_itype`
- L662 _public enumerator_ `SYMS_CvLeafArrayMember_index_itype`
- L663 _public enumerator_ `SYMS_CvLeafArrayMember_COUNT`

#### enum `SYMS_CvLeafStructMember`  
`typedef enum SYMS_CvLeafStructMember`  
_L665-672_
- L666 _public enumerator_ `SYMS_CvLeafStructMember_count`
- L667 _public enumerator_ `SYMS_CvLeafStructMember_props`
- L668 _public enumerator_ `SYMS_CvLeafStructMember_field`
- L669 _public enumerator_ `SYMS_CvLeafStructMember_derived`
- L670 _public enumerator_ `SYMS_CvLeafStructMember_vshape`
- L671 _public enumerator_ `SYMS_CvLeafStructMember_COUNT`

#### enum `SYMS_CvLeafUnionMember`  
`typedef enum SYMS_CvLeafUnionMember`  
_L673-678_
- L674 _public enumerator_ `SYMS_CvLeafUnionMember_count`
- L675 _public enumerator_ `SYMS_CvLeafUnionMember_props`
- L676 _public enumerator_ `SYMS_CvLeafUnionMember_field`
- L677 _public enumerator_ `SYMS_CvLeafUnionMember_COUNT`

#### enum `SYMS_CvLeafEnumMember`  
`typedef enum SYMS_CvLeafEnumMember`  
_L679-685_
- L680 _public enumerator_ `SYMS_CvLeafEnumMember_count`
- L681 _public enumerator_ `SYMS_CvLeafEnumMember_props`
- L682 _public enumerator_ `SYMS_CvLeafEnumMember_itype`
- L683 _public enumerator_ `SYMS_CvLeafEnumMember_field`
- L684 _public enumerator_ `SYMS_CvLeafEnumMember_COUNT`

#### enum `SYMS_CvLeafAliasMember`  
`typedef enum SYMS_CvLeafAliasMember`  
_L686-689_
- L687 _public enumerator_ `SYMS_CvLeafAliasMember_itype`
- L688 _public enumerator_ `SYMS_CvLeafAliasMember_COUNT`

#### enum `SYMS_CvLeafMemberMember`  
`typedef enum SYMS_CvLeafMemberMember`  
_L690-696_
- L691 _public enumerator_ `SYMS_CvLeafMemberMember_attribs`
- L692 _public enumerator_ `SYMS_CvLeafMemberMember_itype`
- L693 _public enumerator_ `SYMS_CvLeafMemberMember_offset`
- L694 _public enumerator_ `SYMS_CvLeafMemberMember_name`
- L695 _public enumerator_ `SYMS_CvLeafMemberMember_COUNT`

#### enum `SYMS_CvLeafStMemberMember`  
`typedef enum SYMS_CvLeafStMemberMember`  
_L697-702_
- L698 _public enumerator_ `SYMS_CvLeafStMemberMember_attribs`
- L699 _public enumerator_ `SYMS_CvLeafStMemberMember_itype`
- L700 _public enumerator_ `SYMS_CvLeafStMemberMember_name`
- L701 _public enumerator_ `SYMS_CvLeafStMemberMember_COUNT`

#### enum `SYMS_CvLeafMethodListMemberMember`  
`typedef enum SYMS_CvLeafMethodListMemberMember`  
_L703-708_
- L704 _public enumerator_ `SYMS_CvLeafMethodListMemberMember_attribs`
- L705 _public enumerator_ `SYMS_CvLeafMethodListMemberMember_pad`
- L706 _public enumerator_ `SYMS_CvLeafMethodListMemberMember_index`
- L707 _public enumerator_ `SYMS_CvLeafMethodListMemberMember_COUNT`

#### enum `SYMS_CvLeafMethodMember`  
`typedef enum SYMS_CvLeafMethodMember`  
_L709-713_
- L710 _public enumerator_ `SYMS_CvLeafMethodMember_count`
- L711 _public enumerator_ `SYMS_CvLeafMethodMember_itype_list`
- L712 _public enumerator_ `SYMS_CvLeafMethodMember_COUNT`

#### enum `SYMS_CvLeafOneMethodMember`  
`typedef enum SYMS_CvLeafOneMethodMember`  
_L714-718_
- L715 _public enumerator_ `SYMS_CvLeafOneMethodMember_attribs`
- L716 _public enumerator_ `SYMS_CvLeafOneMethodMember_itype`
- L717 _public enumerator_ `SYMS_CvLeafOneMethodMember_COUNT`

#### enum `SYMS_CvLeafEnumerateMember`  
`typedef enum SYMS_CvLeafEnumerateMember`  
_L719-722_
- L720 _public enumerator_ `SYMS_CvLeafEnumerateMember_attribs`
- L721 _public enumerator_ `SYMS_CvLeafEnumerateMember_COUNT`

#### enum `SYMS_CvLeafNestTypeMember`  
`typedef enum SYMS_CvLeafNestTypeMember`  
_L723-727_
- L724 _public enumerator_ `SYMS_CvLeafNestTypeMember_pad`
- L725 _public enumerator_ `SYMS_CvLeafNestTypeMember_index`
- L726 _public enumerator_ `SYMS_CvLeafNestTypeMember_COUNT`

#### enum `SYMS_CvLeafNestTypeExMember`  
`typedef enum SYMS_CvLeafNestTypeExMember`  
_L728-732_
- L729 _public enumerator_ `SYMS_CvLeafNestTypeExMember_attribs`
- L730 _public enumerator_ `SYMS_CvLeafNestTypeExMember_itype`
- L731 _public enumerator_ `SYMS_CvLeafNestTypeExMember_COUNT`

#### enum `SYMS_CvLeafBClassMember`  
`typedef enum SYMS_CvLeafBClassMember`  
_L733-737_
- L734 _public enumerator_ `SYMS_CvLeafBClassMember_attribs`
- L735 _public enumerator_ `SYMS_CvLeafBClassMember_itype`
- L736 _public enumerator_ `SYMS_CvLeafBClassMember_COUNT`

#### enum `SYMS_CvLeafVBClassMember`  
`typedef enum SYMS_CvLeafVBClassMember`  
_L738-743_
- L739 _public enumerator_ `SYMS_CvLeafVBClassMember_attribs`
- L740 _public enumerator_ `SYMS_CvLeafVBClassMember_itype`
- L741 _public enumerator_ `SYMS_CvLeafVBClassMember_vbptr_itype`
- L742 _public enumerator_ `SYMS_CvLeafVBClassMember_COUNT`

#### enum `SYMS_CvLeafVFuncTabMember`  
`typedef enum SYMS_CvLeafVFuncTabMember`  
_L744-748_
- L745 _public enumerator_ `SYMS_CvLeafVFuncTabMember_pad`
- L746 _public enumerator_ `SYMS_CvLeafVFuncTabMember_itype`
- L747 _public enumerator_ `SYMS_CvLeafVFuncTabMember_COUNT`

#### enum `SYMS_CvLeafVFuncOffMember`  
`typedef enum SYMS_CvLeafVFuncOffMember`  
_L749-754_
- L750 _public enumerator_ `SYMS_CvLeafVFuncOffMember_pad`
- L751 _public enumerator_ `SYMS_CvLeafVFuncOffMember_itype`
- L752 _public enumerator_ `SYMS_CvLeafVFuncOffMember_off`
- L753 _public enumerator_ `SYMS_CvLeafVFuncOffMember_COUNT`

#### enum `SYMS_CvLeafVFTableMember`  
`typedef enum SYMS_CvLeafVFTableMember`  
_L755-761_
- L756 _public enumerator_ `SYMS_CvLeafVFTableMember_owner_itype`
- L757 _public enumerator_ `SYMS_CvLeafVFTableMember_base_table_itype`
- L758 _public enumerator_ `SYMS_CvLeafVFTableMember_offset_in_object_layout`
- L759 _public enumerator_ `SYMS_CvLeafVFTableMember_names_len`
- L760 _public enumerator_ `SYMS_CvLeafVFTableMember_COUNT`

#### enum `SYMS_CvLeafVFPathMember`  
`typedef enum SYMS_CvLeafVFPathMember`  
_L762-765_
- L763 _public enumerator_ `SYMS_CvLeafVFPathMember_count`
- L764 _public enumerator_ `SYMS_CvLeafVFPathMember_COUNT`

#### enum `SYMS_CvLeafFuncIdMember`  
`typedef enum SYMS_CvLeafFuncIdMember`  
_L766-770_
- L767 _public enumerator_ `SYMS_CvLeafFuncIdMember_scope_id`
- L768 _public enumerator_ `SYMS_CvLeafFuncIdMember_itype`
- L769 _public enumerator_ `SYMS_CvLeafFuncIdMember_COUNT`

#### enum `SYMS_CvLeafMFuncIdMember`  
`typedef enum SYMS_CvLeafMFuncIdMember`  
_L771-775_
- L772 _public enumerator_ `SYMS_CvLeafMFuncIdMember_parent_itype`
- L773 _public enumerator_ `SYMS_CvLeafMFuncIdMember_itype`
- L774 _public enumerator_ `SYMS_CvLeafMFuncIdMember_COUNT`

#### enum `SYMS_CvLeafStringIdMember`  
`typedef enum SYMS_CvLeafStringIdMember`  
_L776-780_
- L777 _public enumerator_ `SYMS_CvLeafStringIdMember_id`
- L778 _public enumerator_ `SYMS_CvLeafStringIdMember_name`
- L779 _public enumerator_ `SYMS_CvLeafStringIdMember_COUNT`

#### enum `SYMS_CvLeafUDTSrcLineMember`  
`typedef enum SYMS_CvLeafUDTSrcLineMember`  
_L781-786_
- L782 _public enumerator_ `SYMS_CvLeafUDTSrcLineMember_udt_itype`
- L783 _public enumerator_ `SYMS_CvLeafUDTSrcLineMember_src`
- L784 _public enumerator_ `SYMS_CvLeafUDTSrcLineMember_ln`
- L785 _public enumerator_ `SYMS_CvLeafUDTSrcLineMember_COUNT`

#### enum `SYMS_CvLeafModSrcLineMember`  
`typedef enum SYMS_CvLeafModSrcLineMember`  
_L787-793_
- L788 _public enumerator_ `SYMS_CvLeafModSrcLineMember_udt_itype`
- L789 _public enumerator_ `SYMS_CvLeafModSrcLineMember_src`
- L790 _public enumerator_ `SYMS_CvLeafModSrcLineMember_ln`
- L791 _public enumerator_ `SYMS_CvLeafModSrcLineMember_comp_unit`
- L792 _public enumerator_ `SYMS_CvLeafModSrcLineMember_COUNT`

#### enum `SYMS_CvLeafClassPtrMember`  
`typedef enum SYMS_CvLeafClassPtrMember`  
_L794-802_
- L795 _public enumerator_ `SYMS_CvLeafClassPtrMember_props`
- L796 _public enumerator_ `SYMS_CvLeafClassPtrMember_padding`
- L797 _public enumerator_ `SYMS_CvLeafClassPtrMember_field`
- L798 _public enumerator_ `SYMS_CvLeafClassPtrMember_unknown2`
- L799 _public enumerator_ `SYMS_CvLeafClassPtrMember_unknown3`
- L800 _public enumerator_ `SYMS_CvLeafClassPtrMember_unknown4`
- L801 _public enumerator_ `SYMS_CvLeafClassPtrMember_COUNT`

#### enum `SYMS_CvSubSectionHeaderMember`  
`typedef enum SYMS_CvSubSectionHeaderMember`  
_L803-807_
- L804 _public enumerator_ `SYMS_CvSubSectionHeaderMember_kind`
- L805 _public enumerator_ `SYMS_CvSubSectionHeaderMember_size`
- L806 _public enumerator_ `SYMS_CvSubSectionHeaderMember_COUNT`

#### enum `SYMS_CvInlineeSourceLineMember`  
`typedef enum SYMS_CvInlineeSourceLineMember`  
_L808-813_
- L809 _public enumerator_ `SYMS_CvInlineeSourceLineMember_inlinee`
- L810 _public enumerator_ `SYMS_CvInlineeSourceLineMember_file_id`
- L811 _public enumerator_ `SYMS_CvInlineeSourceLineMember_base_line_number`
- L812 _public enumerator_ `SYMS_CvInlineeSourceLineMember_COUNT`

#### enum `SYMS_CvInlineeSourceLineExMember`  
`typedef enum SYMS_CvInlineeSourceLineExMember`  
_L814-821_
- L815 _public enumerator_ `SYMS_CvInlineeSourceLineExMember_inlinee`
- L816 _public enumerator_ `SYMS_CvInlineeSourceLineExMember_file_id`
- L817 _public enumerator_ `SYMS_CvInlineeSourceLineExMember_base_line_number`
- L818 _public enumerator_ `SYMS_CvInlineeSourceLineExMember_extra_file_count`
- L819 _public enumerator_ `SYMS_CvInlineeSourceLineExMember_extra_file_id`
- L820 _public enumerator_ `SYMS_CvInlineeSourceLineExMember_COUNT`

#### enum `SYMS_MachLCStrMember`  
`typedef enum SYMS_MachLCStrMember`  
_L1194-1197_
- L1195 _public enumerator_ `SYMS_MachLCStrMember_offset`
- L1196 _public enumerator_ `SYMS_MachLCStrMember_COUNT`

#### enum `SYMS_MachUUIDMember`  
`typedef enum SYMS_MachUUIDMember`  
_L1198-1203_
- L1199 _public enumerator_ `SYMS_MachUUIDMember_cmd`
- L1200 _public enumerator_ `SYMS_MachUUIDMember_cmdsize`
- L1201 _public enumerator_ `SYMS_MachUUIDMember_uuid`
- L1202 _public enumerator_ `SYMS_MachUUIDMember_COUNT`

#### enum `SYMS_MachDylibMember`  
`typedef enum SYMS_MachDylibMember`  
_L1204-1210_
- L1205 _public enumerator_ `SYMS_MachDylibMember_name`
- L1206 _public enumerator_ `SYMS_MachDylibMember_timestamp`
- L1207 _public enumerator_ `SYMS_MachDylibMember_current_version`
- L1208 _public enumerator_ `SYMS_MachDylibMember_compatability_version`
- L1209 _public enumerator_ `SYMS_MachDylibMember_COUNT`

#### enum `SYMS_MachDylibCommandMember`  
`typedef enum SYMS_MachDylibCommandMember`  
_L1211-1216_
- L1212 _public enumerator_ `SYMS_MachDylibCommandMember_cmd`
- L1213 _public enumerator_ `SYMS_MachDylibCommandMember_cmdsize`
- L1214 _public enumerator_ `SYMS_MachDylibCommandMember_dylib`
- L1215 _public enumerator_ `SYMS_MachDylibCommandMember_COUNT`

#### enum `SYMS_MachDyldInfoCommandMember`  
`typedef enum SYMS_MachDyldInfoCommandMember`  
_L1217-1231_
- L1218 _public enumerator_ `SYMS_MachDyldInfoCommandMember_cmd`
- L1219 _public enumerator_ `SYMS_MachDyldInfoCommandMember_cmdsize`
- L1220 _public enumerator_ `SYMS_MachDyldInfoCommandMember_rebase_off`
- L1221 _public enumerator_ `SYMS_MachDyldInfoCommandMember_rebase_size`
- L1222 _public enumerator_ `SYMS_MachDyldInfoCommandMember_bind_off`
- L1223 _public enumerator_ `SYMS_MachDyldInfoCommandMember_bind_size`
- L1224 _public enumerator_ `SYMS_MachDyldInfoCommandMember_weak_bind_off`
- L1225 _public enumerator_ `SYMS_MachDyldInfoCommandMember_weak_bind_size`
- L1226 _public enumerator_ `SYMS_MachDyldInfoCommandMember_lazy_bind_off`
- L1227 _public enumerator_ `SYMS_MachDyldInfoCommandMember_lazy_bind_size`
- L1228 _public enumerator_ `SYMS_MachDyldInfoCommandMember_export_off`
- L1229 _public enumerator_ `SYMS_MachDyldInfoCommandMember_export_size`
- L1230 _public enumerator_ `SYMS_MachDyldInfoCommandMember_COUNT`

#### enum `SYMS_MachLoadCommandMember`  
`typedef enum SYMS_MachLoadCommandMember`  
_L1232-1236_
- L1233 _public enumerator_ `SYMS_MachLoadCommandMember_type`
- L1234 _public enumerator_ `SYMS_MachLoadCommandMember_size`
- L1235 _public enumerator_ `SYMS_MachLoadCommandMember_COUNT`

#### enum `SYMS_MachFatHeaderMember`  
`typedef enum SYMS_MachFatHeaderMember`  
_L1237-1241_
- L1238 _public enumerator_ `SYMS_MachFatHeaderMember_magic`
- L1239 _public enumerator_ `SYMS_MachFatHeaderMember_nfat_arch`
- L1240 _public enumerator_ `SYMS_MachFatHeaderMember_COUNT`

#### enum `SYMS_MachFatArchMember`  
`typedef enum SYMS_MachFatArchMember`  
_L1242-1249_
- L1243 _public enumerator_ `SYMS_MachFatArchMember_cputype`
- L1244 _public enumerator_ `SYMS_MachFatArchMember_cpusubtype`
- L1245 _public enumerator_ `SYMS_MachFatArchMember_offset`
- L1246 _public enumerator_ `SYMS_MachFatArchMember_size`
- L1247 _public enumerator_ `SYMS_MachFatArchMember_align`
- L1248 _public enumerator_ `SYMS_MachFatArchMember_COUNT`

#### enum `SYMS_MachHeader32Member`  
`typedef enum SYMS_MachHeader32Member`  
_L1250-1259_
- L1251 _public enumerator_ `SYMS_MachHeader32Member_magic`
- L1252 _public enumerator_ `SYMS_MachHeader32Member_cputype`
- L1253 _public enumerator_ `SYMS_MachHeader32Member_cpusubtype`
- L1254 _public enumerator_ `SYMS_MachHeader32Member_filetype`
- L1255 _public enumerator_ `SYMS_MachHeader32Member_ncmds`
- L1256 _public enumerator_ `SYMS_MachHeader32Member_sizeofcmds`
- L1257 _public enumerator_ `SYMS_MachHeader32Member_flags`
- L1258 _public enumerator_ `SYMS_MachHeader32Member_COUNT`

#### enum `SYMS_MachHeader64Member`  
`typedef enum SYMS_MachHeader64Member`  
_L1260-1270_
- L1261 _public enumerator_ `SYMS_MachHeader64Member_magic`
- L1262 _public enumerator_ `SYMS_MachHeader64Member_cputype`
- L1263 _public enumerator_ `SYMS_MachHeader64Member_cpusubtype`
- L1264 _public enumerator_ `SYMS_MachHeader64Member_filetype`
- L1265 _public enumerator_ `SYMS_MachHeader64Member_ncmds`
- L1266 _public enumerator_ `SYMS_MachHeader64Member_sizeofcmds`
- L1267 _public enumerator_ `SYMS_MachHeader64Member_flags`
- L1268 _public enumerator_ `SYMS_MachHeader64Member_reserved`
- L1269 _public enumerator_ `SYMS_MachHeader64Member_COUNT`

#### enum `SYMS_MachSegmentCommand32Member`  
`typedef enum SYMS_MachSegmentCommand32Member`  
_L1271-1283_
- L1272 _public enumerator_ `SYMS_MachSegmentCommand32Member_cmd`
- L1273 _public enumerator_ `SYMS_MachSegmentCommand32Member_segname`
- L1274 _public enumerator_ `SYMS_MachSegmentCommand32Member_vmaddr`
- L1275 _public enumerator_ `SYMS_MachSegmentCommand32Member_vmsize`
- L1276 _public enumerator_ `SYMS_MachSegmentCommand32Member_fileoff`
- L1277 _public enumerator_ `SYMS_MachSegmentCommand32Member_filesize`
- L1278 _public enumerator_ `SYMS_MachSegmentCommand32Member_maxprot`
- L1279 _public enumerator_ `SYMS_MachSegmentCommand32Member_initprot`
- L1280 _public enumerator_ `SYMS_MachSegmentCommand32Member_nsects`
- L1281 _public enumerator_ `SYMS_MachSegmentCommand32Member_flags`
- L1282 _public enumerator_ `SYMS_MachSegmentCommand32Member_COUNT`

#### enum `SYMS_MachSegmentCommand64Member`  
`typedef enum SYMS_MachSegmentCommand64Member`  
_L1284-1296_
- L1285 _public enumerator_ `SYMS_MachSegmentCommand64Member_cmd`
- L1286 _public enumerator_ `SYMS_MachSegmentCommand64Member_segname`
- L1287 _public enumerator_ `SYMS_MachSegmentCommand64Member_vmaddr`
- L1288 _public enumerator_ `SYMS_MachSegmentCommand64Member_vmsize`
- L1289 _public enumerator_ `SYMS_MachSegmentCommand64Member_fileoff`
- L1290 _public enumerator_ `SYMS_MachSegmentCommand64Member_filesize`
- L1291 _public enumerator_ `SYMS_MachSegmentCommand64Member_maxprot`
- L1292 _public enumerator_ `SYMS_MachSegmentCommand64Member_initprot`
- L1293 _public enumerator_ `SYMS_MachSegmentCommand64Member_nsects`
- L1294 _public enumerator_ `SYMS_MachSegmentCommand64Member_flags`
- L1295 _public enumerator_ `SYMS_MachSegmentCommand64Member_COUNT`

#### enum `SYMS_MachSection32Member`  
`typedef enum SYMS_MachSection32Member`  
_L1297-1310_
- L1298 _public enumerator_ `SYMS_MachSection32Member_sectname`
- L1299 _public enumerator_ `SYMS_MachSection32Member_segname`
- L1300 _public enumerator_ `SYMS_MachSection32Member_addr`
- L1301 _public enumerator_ `SYMS_MachSection32Member_size`
- L1302 _public enumerator_ `SYMS_MachSection32Member_offset`
- L1303 _public enumerator_ `SYMS_MachSection32Member_align`
- L1304 _public enumerator_ `SYMS_MachSection32Member_relocoff`
- L1305 _public enumerator_ `SYMS_MachSection32Member_nreloc`
- L1306 _public enumerator_ `SYMS_MachSection32Member_flags`
- L1307 _public enumerator_ `SYMS_MachSection32Member_reserved1`
- L1308 _public enumerator_ `SYMS_MachSection32Member_reserved2`
- L1309 _public enumerator_ `SYMS_MachSection32Member_COUNT`

#### enum `SYMS_MachSection64Member`  
`typedef enum SYMS_MachSection64Member`  
_L1311-1325_
- L1312 _public enumerator_ `SYMS_MachSection64Member_sectname`
- L1313 _public enumerator_ `SYMS_MachSection64Member_segname`
- L1314 _public enumerator_ `SYMS_MachSection64Member_addr`
- L1315 _public enumerator_ `SYMS_MachSection64Member_size`
- L1316 _public enumerator_ `SYMS_MachSection64Member_offset`
- L1317 _public enumerator_ `SYMS_MachSection64Member_align`
- L1318 _public enumerator_ `SYMS_MachSection64Member_relocoff`
- L1319 _public enumerator_ `SYMS_MachSection64Member_nreloc`
- L1320 _public enumerator_ `SYMS_MachSection64Member_flags`
- L1321 _public enumerator_ `SYMS_MachSection64Member_reserved1`
- L1322 _public enumerator_ `SYMS_MachSection64Member_reserved2`
- L1323 _public enumerator_ `SYMS_MachSection64Member_pad`
- L1324 _public enumerator_ `SYMS_MachSection64Member_COUNT`

#### enum `SYMS_MachSymtabCommandMember`  
`typedef enum SYMS_MachSymtabCommandMember`  
_L1326-1334_
- L1327 _public enumerator_ `SYMS_MachSymtabCommandMember_cmd`
- L1328 _public enumerator_ `SYMS_MachSymtabCommandMember_cmdsize`
- L1329 _public enumerator_ `SYMS_MachSymtabCommandMember_symoff`
- L1330 _public enumerator_ `SYMS_MachSymtabCommandMember_nsyms`
- L1331 _public enumerator_ `SYMS_MachSymtabCommandMember_stroff`
- L1332 _public enumerator_ `SYMS_MachSymtabCommandMember_strsize`
- L1333 _public enumerator_ `SYMS_MachSymtabCommandMember_COUNT`

#### enum `SYMS_MachDySymtabCommandMember`  
`typedef enum SYMS_MachDySymtabCommandMember`  
_L1335-1357_
- L1336 _public enumerator_ `SYMS_MachDySymtabCommandMember_cmd`
- L1337 _public enumerator_ `SYMS_MachDySymtabCommandMember_cmdsize`
- L1338 _public enumerator_ `SYMS_MachDySymtabCommandMember_ilocalsym`
- L1339 _public enumerator_ `SYMS_MachDySymtabCommandMember_nlocalsym`
- L1340 _public enumerator_ `SYMS_MachDySymtabCommandMember_iextdefsym`
- L1341 _public enumerator_ `SYMS_MachDySymtabCommandMember_nextdefsym`
- L1342 _public enumerator_ `SYMS_MachDySymtabCommandMember_iundefsym`
- L1343 _public enumerator_ `SYMS_MachDySymtabCommandMember_nundefsym`
- L1344 _public enumerator_ `SYMS_MachDySymtabCommandMember_tocoff`
- L1345 _public enumerator_ `SYMS_MachDySymtabCommandMember_ntoc`
- L1346 _public enumerator_ `SYMS_MachDySymtabCommandMember_modtaboff`
- L1347 _public enumerator_ `SYMS_MachDySymtabCommandMember_nmodtab`
- L1348 _public enumerator_ `SYMS_MachDySymtabCommandMember_extrefsymoff`
- L1349 _public enumerator_ `SYMS_MachDySymtabCommandMember_nextrefsyms`
- L1350 _public enumerator_ `SYMS_MachDySymtabCommandMember_indirectsymoff`
- L1351 _public enumerator_ `SYMS_MachDySymtabCommandMember_nindirectsyms`
- L1352 _public enumerator_ `SYMS_MachDySymtabCommandMember_extreloff`
- L1353 _public enumerator_ `SYMS_MachDySymtabCommandMember_nextrel`
- L1354 _public enumerator_ `SYMS_MachDySymtabCommandMember_locreloff`
- L1355 _public enumerator_ `SYMS_MachDySymtabCommandMember_nlocrel`
- L1356 _public enumerator_ `SYMS_MachDySymtabCommandMember_COUNT`

#### enum `SYMS_MachNList32Member`  
`typedef enum SYMS_MachNList32Member`  
_L1358-1365_
- L1359 _public enumerator_ `SYMS_MachNList32Member_n_strx`
- L1360 _public enumerator_ `SYMS_MachNList32Member_n_type`
- L1361 _public enumerator_ `SYMS_MachNList32Member_n_sect`
- L1362 _public enumerator_ `SYMS_MachNList32Member_n_desc`
- L1363 _public enumerator_ `SYMS_MachNList32Member_n_value`
- L1364 _public enumerator_ `SYMS_MachNList32Member_COUNT`

#### enum `SYMS_MachNList64Member`  
`typedef enum SYMS_MachNList64Member`  
_L1366-1373_
- L1367 _public enumerator_ `SYMS_MachNList64Member_n_strx`
- L1368 _public enumerator_ `SYMS_MachNList64Member_n_type`
- L1369 _public enumerator_ `SYMS_MachNList64Member_n_sect`
- L1370 _public enumerator_ `SYMS_MachNList64Member_n_desc`
- L1371 _public enumerator_ `SYMS_MachNList64Member_n_value`
- L1372 _public enumerator_ `SYMS_MachNList64Member_COUNT`

#### enum `SYMS_MachBuildVersionCommandMember`  
`typedef enum SYMS_MachBuildVersionCommandMember`  
_L1374-1382_
- L1375 _public enumerator_ `SYMS_MachBuildVersionCommandMember_cmd`
- L1376 _public enumerator_ `SYMS_MachBuildVersionCommandMember_cmdsize`
- L1377 _public enumerator_ `SYMS_MachBuildVersionCommandMember_platform`
- L1378 _public enumerator_ `SYMS_MachBuildVersionCommandMember_minos`
- L1379 _public enumerator_ `SYMS_MachBuildVersionCommandMember_sdk`
- L1380 _public enumerator_ `SYMS_MachBuildVersionCommandMember_ntools`
- L1381 _public enumerator_ `SYMS_MachBuildVersionCommandMember_COUNT`

#### enum `SYMS_MachBuildToolVersionMember`  
`typedef enum SYMS_MachBuildToolVersionMember`  
_L1383-1387_
- L1384 _public enumerator_ `SYMS_MachBuildToolVersionMember_tool`
- L1385 _public enumerator_ `SYMS_MachBuildToolVersionMember_version`
- L1386 _public enumerator_ `SYMS_MachBuildToolVersionMember_COUNT`

#### enum `SYMS_MachVersionMinMember`  
`typedef enum SYMS_MachVersionMinMember`  
_L1388-1394_
- L1389 _public enumerator_ `SYMS_MachVersionMinMember_cmd`
- L1390 _public enumerator_ `SYMS_MachVersionMinMember_cmdsize`
- L1391 _public enumerator_ `SYMS_MachVersionMinMember_version`
- L1392 _public enumerator_ `SYMS_MachVersionMinMember_sdk`
- L1393 _public enumerator_ `SYMS_MachVersionMinMember_COUNT`

#### enum `SYMS_MachDylinkerMember`  
`typedef enum SYMS_MachDylinkerMember`  
_L1395-1400_
- L1396 _public enumerator_ `SYMS_MachDylinkerMember_cmd`
- L1397 _public enumerator_ `SYMS_MachDylinkerMember_cmdsize`
- L1398 _public enumerator_ `SYMS_MachDylinkerMember_name`
- L1399 _public enumerator_ `SYMS_MachDylinkerMember_COUNT`

#### enum `SYMS_MachPreboundDylibCommandMember`  
`typedef enum SYMS_MachPreboundDylibCommandMember`  
_L1401-1407_
- L1402 _public enumerator_ `SYMS_MachPreboundDylibCommandMember_cmd`
- L1403 _public enumerator_ `SYMS_MachPreboundDylibCommandMember_cmdsize`
- L1404 _public enumerator_ `SYMS_MachPreboundDylibCommandMember_name`
- L1405 _public enumerator_ `SYMS_MachPreboundDylibCommandMember_nmodules`
- L1406 _public enumerator_ `SYMS_MachPreboundDylibCommandMember_COUNT`

#### enum `SYMS_MachRoutinesCommandMember`  
`typedef enum SYMS_MachRoutinesCommandMember`  
_L1408-1420_
- L1409 _public enumerator_ `SYMS_MachRoutinesCommandMember_cmd`
- L1410 _public enumerator_ `SYMS_MachRoutinesCommandMember_cmdsize`
- L1411 _public enumerator_ `SYMS_MachRoutinesCommandMember_init_address`
- L1412 _public enumerator_ `SYMS_MachRoutinesCommandMember_init_module`
- L1413 _public enumerator_ `SYMS_MachRoutinesCommandMember_reserved1`
- L1414 _public enumerator_ `SYMS_MachRoutinesCommandMember_reserved2`
- L1415 _public enumerator_ `SYMS_MachRoutinesCommandMember_reserved3`
- L1416 _public enumerator_ `SYMS_MachRoutinesCommandMember_reserved4`
- L1417 _public enumerator_ `SYMS_MachRoutinesCommandMember_reserved5`
- L1418 _public enumerator_ `SYMS_MachRoutinesCommandMember_reserved6`
- L1419 _public enumerator_ `SYMS_MachRoutinesCommandMember_COUNT`

#### enum `SYMS_MachRoutines64CommandMember`  
`typedef enum SYMS_MachRoutines64CommandMember`  
_L1421-1433_
- L1422 _public enumerator_ `SYMS_MachRoutines64CommandMember_cmd`
- L1423 _public enumerator_ `SYMS_MachRoutines64CommandMember_cmdsize`
- L1424 _public enumerator_ `SYMS_MachRoutines64CommandMember_init_address`
- L1425 _public enumerator_ `SYMS_MachRoutines64CommandMember_init_module`
- L1426 _public enumerator_ `SYMS_MachRoutines64CommandMember_reserved1`
- L1427 _public enumerator_ `SYMS_MachRoutines64CommandMember_reserved2`
- L1428 _public enumerator_ `SYMS_MachRoutines64CommandMember_reserved3`
- L1429 _public enumerator_ `SYMS_MachRoutines64CommandMember_reserved4`
- L1430 _public enumerator_ `SYMS_MachRoutines64CommandMember_reserved5`
- L1431 _public enumerator_ `SYMS_MachRoutines64CommandMember_reserved6`
- L1432 _public enumerator_ `SYMS_MachRoutines64CommandMember_COUNT`

#### enum `SYMS_MachSubFrameworkCommandMember`  
`typedef enum SYMS_MachSubFrameworkCommandMember`  
_L1434-1439_
- L1435 _public enumerator_ `SYMS_MachSubFrameworkCommandMember_cmd`
- L1436 _public enumerator_ `SYMS_MachSubFrameworkCommandMember_cmdsize`
- L1437 _public enumerator_ `SYMS_MachSubFrameworkCommandMember_umbrella`
- L1438 _public enumerator_ `SYMS_MachSubFrameworkCommandMember_COUNT`

#### enum `SYMS_MachSubUmbrellaCommandMember`  
`typedef enum SYMS_MachSubUmbrellaCommandMember`  
_L1440-1445_
- L1441 _public enumerator_ `SYMS_MachSubUmbrellaCommandMember_cmd`
- L1442 _public enumerator_ `SYMS_MachSubUmbrellaCommandMember_cmdsize`
- L1443 _public enumerator_ `SYMS_MachSubUmbrellaCommandMember_sub_umbrella`
- L1444 _public enumerator_ `SYMS_MachSubUmbrellaCommandMember_COUNT`

#### enum `SYMS_MachSubClientCommandMember`  
`typedef enum SYMS_MachSubClientCommandMember`  
_L1446-1451_
- L1447 _public enumerator_ `SYMS_MachSubClientCommandMember_cmd`
- L1448 _public enumerator_ `SYMS_MachSubClientCommandMember_cmdsize`
- L1449 _public enumerator_ `SYMS_MachSubClientCommandMember_client`
- L1450 _public enumerator_ `SYMS_MachSubClientCommandMember_COUNT`

#### enum `SYMS_MachSubLibraryCommandMember`  
`typedef enum SYMS_MachSubLibraryCommandMember`  
_L1452-1457_
- L1453 _public enumerator_ `SYMS_MachSubLibraryCommandMember_cmd`
- L1454 _public enumerator_ `SYMS_MachSubLibraryCommandMember_cmdsize`
- L1455 _public enumerator_ `SYMS_MachSubLibraryCommandMember_sub_library`
- L1456 _public enumerator_ `SYMS_MachSubLibraryCommandMember_COUNT`

#### enum `SYMS_MachTwoLevelHintsCommandMember`  
`typedef enum SYMS_MachTwoLevelHintsCommandMember`  
_L1458-1464_
- L1459 _public enumerator_ `SYMS_MachTwoLevelHintsCommandMember_cmd`
- L1460 _public enumerator_ `SYMS_MachTwoLevelHintsCommandMember_cmdsize`
- L1461 _public enumerator_ `SYMS_MachTwoLevelHintsCommandMember_offset`
- L1462 _public enumerator_ `SYMS_MachTwoLevelHintsCommandMember_nhints`
- L1463 _public enumerator_ `SYMS_MachTwoLevelHintsCommandMember_COUNT`

#### enum `SYMS_MachPrebindChecksumCommandMember`  
`typedef enum SYMS_MachPrebindChecksumCommandMember`  
_L1465-1470_
- L1466 _public enumerator_ `SYMS_MachPrebindChecksumCommandMember_cmd`
- L1467 _public enumerator_ `SYMS_MachPrebindChecksumCommandMember_cmdsize`
- L1468 _public enumerator_ `SYMS_MachPrebindChecksumCommandMember_chksum`
- L1469 _public enumerator_ `SYMS_MachPrebindChecksumCommandMember_COUNT`

#### enum `SYMS_MachRPathCommandMember`  
`typedef enum SYMS_MachRPathCommandMember`  
_L1471-1476_
- L1472 _public enumerator_ `SYMS_MachRPathCommandMember_cmd`
- L1473 _public enumerator_ `SYMS_MachRPathCommandMember_cmdsize`
- L1474 _public enumerator_ `SYMS_MachRPathCommandMember_path`
- L1475 _public enumerator_ `SYMS_MachRPathCommandMember_COUNT`

#### enum `SYMS_MachLinkeditDataCommandMember`  
`typedef enum SYMS_MachLinkeditDataCommandMember`  
_L1477-1483_
- L1478 _public enumerator_ `SYMS_MachLinkeditDataCommandMember_cmd`
- L1479 _public enumerator_ `SYMS_MachLinkeditDataCommandMember_cmdsize`
- L1480 _public enumerator_ `SYMS_MachLinkeditDataCommandMember_dataoff`
- L1481 _public enumerator_ `SYMS_MachLinkeditDataCommandMember_datasize`
- L1482 _public enumerator_ `SYMS_MachLinkeditDataCommandMember_COUNT`

#### enum `SYMS_MachEncryptionInfoCommandMember`  
`typedef enum SYMS_MachEncryptionInfoCommandMember`  
_L1484-1491_
- L1485 _public enumerator_ `SYMS_MachEncryptionInfoCommandMember_cmd`
- L1486 _public enumerator_ `SYMS_MachEncryptionInfoCommandMember_cmdsize`
- L1487 _public enumerator_ `SYMS_MachEncryptionInfoCommandMember_cryptoff`
- L1488 _public enumerator_ `SYMS_MachEncryptionInfoCommandMember_cryptsize`
- L1489 _public enumerator_ `SYMS_MachEncryptionInfoCommandMember_cryptid`
- L1490 _public enumerator_ `SYMS_MachEncryptionInfoCommandMember_COUNT`

#### enum `SYMS_MachEncryptionInfo64CommandMember`  
`typedef enum SYMS_MachEncryptionInfo64CommandMember`  
_L1492-1500_
- L1493 _public enumerator_ `SYMS_MachEncryptionInfo64CommandMember_cmd`
- L1494 _public enumerator_ `SYMS_MachEncryptionInfo64CommandMember_cmdsize`
- L1495 _public enumerator_ `SYMS_MachEncryptionInfo64CommandMember_cryptoff`
- L1496 _public enumerator_ `SYMS_MachEncryptionInfo64CommandMember_cryptsize`
- L1497 _public enumerator_ `SYMS_MachEncryptionInfo64CommandMember_cryptid`
- L1498 _public enumerator_ `SYMS_MachEncryptionInfo64CommandMember_pad`
- L1499 _public enumerator_ `SYMS_MachEncryptionInfo64CommandMember_COUNT`

#### enum `SYMS_MachEntryPointCommandMember`  
`typedef enum SYMS_MachEntryPointCommandMember`  
_L1501-1507_
- L1502 _public enumerator_ `SYMS_MachEntryPointCommandMember_cmd`
- L1503 _public enumerator_ `SYMS_MachEntryPointCommandMember_cmdsize`
- L1504 _public enumerator_ `SYMS_MachEntryPointCommandMember_entryoff`
- L1505 _public enumerator_ `SYMS_MachEntryPointCommandMember_stacksize`
- L1506 _public enumerator_ `SYMS_MachEntryPointCommandMember_COUNT`

#### enum `SYMS_MachSourceVersionCommandMember`  
`typedef enum SYMS_MachSourceVersionCommandMember`  
_L1508-1513_
- L1509 _public enumerator_ `SYMS_MachSourceVersionCommandMember_cmd`
- L1510 _public enumerator_ `SYMS_MachSourceVersionCommandMember_cmdsize`
- L1511 _public enumerator_ `SYMS_MachSourceVersionCommandMember_version`
- L1512 _public enumerator_ `SYMS_MachSourceVersionCommandMember_COUNT`

#### enum `SYMS_MachLinkerOptionCommandMember`  
`typedef enum SYMS_MachLinkerOptionCommandMember`  
_L1514-1519_
- L1515 _public enumerator_ `SYMS_MachLinkerOptionCommandMember_cmd`
- L1516 _public enumerator_ `SYMS_MachLinkerOptionCommandMember_cmdsize`
- L1517 _public enumerator_ `SYMS_MachLinkerOptionCommandMember_count`
- L1518 _public enumerator_ `SYMS_MachLinkerOptionCommandMember_COUNT`

#### enum `SYMS_MachNoteCommandMember`  
`typedef enum SYMS_MachNoteCommandMember`  
_L1520-1527_
- L1521 _public enumerator_ `SYMS_MachNoteCommandMember_cmd`
- L1522 _public enumerator_ `SYMS_MachNoteCommandMember_cmdsize`
- L1523 _public enumerator_ `SYMS_MachNoteCommandMember_data_owner`
- L1524 _public enumerator_ `SYMS_MachNoteCommandMember_offset`
- L1525 _public enumerator_ `SYMS_MachNoteCommandMember_size`
- L1526 _public enumerator_ `SYMS_MachNoteCommandMember_COUNT`

#### enum `SYMS_MachSymSegCommandMember`  
`typedef enum SYMS_MachSymSegCommandMember`  
_L1528-1534_
- L1529 _public enumerator_ `SYMS_MachSymSegCommandMember_cmd`
- L1530 _public enumerator_ `SYMS_MachSymSegCommandMember_cmdsize`
- L1531 _public enumerator_ `SYMS_MachSymSegCommandMember_offset`
- L1532 _public enumerator_ `SYMS_MachSymSegCommandMember_size`
- L1533 _public enumerator_ `SYMS_MachSymSegCommandMember_COUNT`

#### enum `SYMS_MachFvmlibMember`  
`typedef enum SYMS_MachFvmlibMember`  
_L1535-1540_
- L1536 _public enumerator_ `SYMS_MachFvmlibMember_name`
- L1537 _public enumerator_ `SYMS_MachFvmlibMember_minor_version`
- L1538 _public enumerator_ `SYMS_MachFvmlibMember_header_addr`
- L1539 _public enumerator_ `SYMS_MachFvmlibMember_COUNT`

#### enum `SYMS_MachFvmlibCommandMember`  
`typedef enum SYMS_MachFvmlibCommandMember`  
_L1541-1546_
- L1542 _public enumerator_ `SYMS_MachFvmlibCommandMember_cmd`
- L1543 _public enumerator_ `SYMS_MachFvmlibCommandMember_cmdsize`
- L1544 _public enumerator_ `SYMS_MachFvmlibCommandMember_fvmlib`
- L1545 _public enumerator_ `SYMS_MachFvmlibCommandMember_COUNT`

#### enum `SYMS_MachThreadCommandMember`  
`typedef enum SYMS_MachThreadCommandMember`  
_L1547-1551_
- L1548 _public enumerator_ `SYMS_MachThreadCommandMember_cmd`
- L1549 _public enumerator_ `SYMS_MachThreadCommandMember_cmdsize`
- L1550 _public enumerator_ `SYMS_MachThreadCommandMember_COUNT`

#### enum `SYMS_DosHeaderMember`  
`typedef enum SYMS_DosHeaderMember`  
_L1664-1685_
- L1665 _public enumerator_ `SYMS_DosHeaderMember_magic`
- L1666 _public enumerator_ `SYMS_DosHeaderMember_last_page_size`
- L1667 _public enumerator_ `SYMS_DosHeaderMember_page_count`
- L1668 _public enumerator_ `SYMS_DosHeaderMember_reloc_count`
- L1669 _public enumerator_ `SYMS_DosHeaderMember_paragraph_header_size`
- L1670 _public enumerator_ `SYMS_DosHeaderMember_min_paragraph`
- L1671 _public enumerator_ `SYMS_DosHeaderMember_max_paragraph`
- L1672 _public enumerator_ `SYMS_DosHeaderMember_init_ss`
- L1673 _public enumerator_ `SYMS_DosHeaderMember_init_sp`
- L1674 _public enumerator_ `SYMS_DosHeaderMember_checksum`
- L1675 _public enumerator_ `SYMS_DosHeaderMember_init_ip`
- L1676 _public enumerator_ `SYMS_DosHeaderMember_init_cs`
- L1677 _public enumerator_ `SYMS_DosHeaderMember_reloc_table_file_off`
- L1678 _public enumerator_ `SYMS_DosHeaderMember_overlay_number`
- L1679 _public enumerator_ `SYMS_DosHeaderMember_reserved`
- L1680 _public enumerator_ `SYMS_DosHeaderMember_oem_id`
- L1681 _public enumerator_ `SYMS_DosHeaderMember_oem_info`
- L1682 _public enumerator_ `SYMS_DosHeaderMember_reserved2`
- L1683 _public enumerator_ `SYMS_DosHeaderMember_coff_file_offset`
- L1684 _public enumerator_ `SYMS_DosHeaderMember_COUNT`

#### enum `SYMS_PeOptionalHeader32Member`  
`typedef enum SYMS_PeOptionalHeader32Member`  
_L1686-1718_
- L1687 _public enumerator_ `SYMS_PeOptionalHeader32Member_magic`
- L1688 _public enumerator_ `SYMS_PeOptionalHeader32Member_major_linker_version`
- L1689 _public enumerator_ `SYMS_PeOptionalHeader32Member_minor_linker_version`
- L1690 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_code`
- L1691 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_inited_data`
- L1692 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_uninited_data`
- L1693 _public enumerator_ `SYMS_PeOptionalHeader32Member_entry_point_va`
- L1694 _public enumerator_ `SYMS_PeOptionalHeader32Member_code_base`
- L1695 _public enumerator_ `SYMS_PeOptionalHeader32Member_data_base`
- L1696 _public enumerator_ `SYMS_PeOptionalHeader32Member_image_base`
- L1697 _public enumerator_ `SYMS_PeOptionalHeader32Member_section_alignment`
- L1698 _public enumerator_ `SYMS_PeOptionalHeader32Member_file_alignment`
- L1699 _public enumerator_ `SYMS_PeOptionalHeader32Member_major_os_ver`
- L1700 _public enumerator_ `SYMS_PeOptionalHeader32Member_minor_os_ver`
- L1701 _public enumerator_ `SYMS_PeOptionalHeader32Member_major_img_ver`
- L1702 _public enumerator_ `SYMS_PeOptionalHeader32Member_minor_img_ver`
- L1703 _public enumerator_ `SYMS_PeOptionalHeader32Member_major_subsystem_ver`
- L1704 _public enumerator_ `SYMS_PeOptionalHeader32Member_minor_subsystem_ver`
- L1705 _public enumerator_ `SYMS_PeOptionalHeader32Member_win32_version_value`
- L1706 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_image`
- L1707 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_headers`
- L1708 _public enumerator_ `SYMS_PeOptionalHeader32Member_check_sum`
- L1709 _public enumerator_ `SYMS_PeOptionalHeader32Member_subsystem`
- L1710 _public enumerator_ `SYMS_PeOptionalHeader32Member_dll_characteristics`
- L1711 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_stack_reserve`
- L1712 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_stack_commit`
- L1713 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_heap_reserve`
- L1714 _public enumerator_ `SYMS_PeOptionalHeader32Member_sizeof_heap_commit`
- L1715 _public enumerator_ `SYMS_PeOptionalHeader32Member_loader_flags`
- L1716 _public enumerator_ `SYMS_PeOptionalHeader32Member_data_dir_count`
- L1717 _public enumerator_ `SYMS_PeOptionalHeader32Member_COUNT`

#### enum `SYMS_PeOptionalHeader32PlusMember`  
`typedef enum SYMS_PeOptionalHeader32PlusMember`  
_L1719-1750_
- L1720 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_magic`
- L1721 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_major_linker_version`
- L1722 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_minor_linker_version`
- L1723 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_code`
- L1724 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_inited_data`
- L1725 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_uninited_data`
- L1726 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_entry_point_va`
- L1727 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_code_base`
- L1728 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_image_base`
- L1729 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_section_alignment`
- L1730 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_file_alignment`
- L1731 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_major_os_ver`
- L1732 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_minor_os_ver`
- L1733 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_major_img_ver`
- L1734 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_minor_img_ver`
- L1735 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_major_subsystem_ver`
- L1736 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_minor_subsystem_ver`
- L1737 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_win32_version_value`
- L1738 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_image`
- L1739 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_headers`
- L1740 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_check_sum`
- L1741 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_subsystem`
- L1742 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_dll_characteristics`
- L1743 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_stack_reserve`
- L1744 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_stack_commit`
- L1745 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_heap_reserve`
- L1746 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_sizeof_heap_commit`
- L1747 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_loader_flags`
- L1748 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_data_dir_count`
- L1749 _public enumerator_ `SYMS_PeOptionalHeader32PlusMember_COUNT`

#### enum `SYMS_PeDataDirectoryMember`  
`typedef enum SYMS_PeDataDirectoryMember`  
_L1751-1755_
- L1752 _public enumerator_ `SYMS_PeDataDirectoryMember_virt_off`
- L1753 _public enumerator_ `SYMS_PeDataDirectoryMember_virt_size`
- L1754 _public enumerator_ `SYMS_PeDataDirectoryMember_COUNT`

#### enum `SYMS_PeDebugDirectoryMember`  
`typedef enum SYMS_PeDebugDirectoryMember`  
_L1756-1766_
- L1757 _public enumerator_ `SYMS_PeDebugDirectoryMember_characteristics`
- L1758 _public enumerator_ `SYMS_PeDebugDirectoryMember_time_stamp`
- L1759 _public enumerator_ `SYMS_PeDebugDirectoryMember_major_ver`
- L1760 _public enumerator_ `SYMS_PeDebugDirectoryMember_minor_ver`
- L1761 _public enumerator_ `SYMS_PeDebugDirectoryMember_type`
- L1762 _public enumerator_ `SYMS_PeDebugDirectoryMember_size`
- L1763 _public enumerator_ `SYMS_PeDebugDirectoryMember_virtual_offset`
- L1764 _public enumerator_ `SYMS_PeDebugDirectoryMember_file_offset`
- L1765 _public enumerator_ `SYMS_PeDebugDirectoryMember_COUNT`

#### Free symbols / members of external scopes

- L4 _macro_ `#define _SYMS_META_SERIAL_EXT_H`
- L19 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_S8;`
- L20 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_S16;`
- L21 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_S32;`
- L22 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_S64;`
- L23 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_U8;`
- L24 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_U16;`
- L25 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_U32;`
- L26 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_U64;`
- L27 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSectionIndex;`
- L28 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvModIndex;`
- L29 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvTypeIndex;`
- L30 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvTypeId;`
- L31 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvItemId;`
- L32 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvReg;`
- L33 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PdbBinaryAnnotation;`
- L34 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PdbNumeric;`
- L35 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_Arch;`
- L36 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_OperatingSystem;`
- L37 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_Language;`
- L38 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_FileFormat;`
- L39 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ChecksumAlgorithm;`
- L57 _typedef_ `} SYMS_CoffHeaderMember;`
- L70 _typedef_ `} SYMS_CoffSectionHeaderMember;`
- L74 _prototype_ `SYMS_U64 syms_enum_index_from_coffmachinetype(SYMS_U64 v);`
- L75 _prototype_ `SYMS_U64 syms_enum_index_from_coffsectionalign(SYMS_U64 v);`
- L77 _prototype_ `SYMS_U64 syms_enum_index_from_coffreloctypex86(SYMS_U64 v);` — syms_enum_index_from_coffreloctypex64 - skipped identity mapping
- L78 _prototype_ `SYMS_U64 syms_enum_index_from_coffreloctypearm(SYMS_U64 v);`
- L79 _prototype_ `SYMS_U64 syms_enum_index_from_coffreloctypearm64(SYMS_U64 v);`
- L81 _prototype_ `SYMS_U64 syms_enum_index_from_coffsymstorageclass(SYMS_U64 v);` — syms_enum_index_from_coffsymtype - skipped identity mapping
- L82 _prototype_ `SYMS_U64 syms_enum_index_from_coffsymsecnumber(SYMS_U64 v);`
- L83 _prototype_ `SYMS_U64 syms_enum_index_from_coffsymdtype(SYMS_U64 v);`
- L84 _prototype_ `SYMS_U64 syms_enum_index_from_coff_weak_ext_type(SYMS_U64 v);`
- L91 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffFlags;`
- L92 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffMachineType;`
- L93 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffHeader;`
- L94 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffSectionAlign;`
- L95 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffSectionFlags;`
- L96 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffSectionHeader;`
- L97 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffRelocTypeX64;`
- L98 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffRelocTypeX86;`
- L99 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffRelocTypeARM;`
- L100 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffRelocTypeARM64;`
- L101 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffSymType;`
- L102 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffSymStorageClass;`
- L103 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffSymSecNumber;`
- L104 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffSymDType;`
- L105 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffWeakExtType;`
- L106 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffImportHeaderType;`
- L107 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffImportHeaderNameType;`
- L108 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CoffComdatSelectType;`
- L124 _typedef_ `} SYMS_CvGuidMember;`
- L130 _typedef_ `} SYMS_CvAnnotationMember;`
- L135 _typedef_ `} SYMS_CvRegisterMember;`
- L140 _typedef_ `} SYMS_CvBPRelSym32Member;`
- L147 _typedef_ `} SYMS_CvVPathSym32Member;`
- L152 _typedef_ `} SYMS_CvOEMMember;`
- L158 _typedef_ `} SYMS_CvSLink32Member;`
- L163 _typedef_ `} SYMS_CvReturnMember;`
- L168 _typedef_ `} SYMS_CvStartSearchMember;`
- L175 _typedef_ `} SYMS_CvThread32Member;`
- L181 _typedef_ `} SYMS_CvCompileMember;`
- L184 _typedef_ `} SYMS_CvEndMember;`
- L196 _typedef_ `} SYMS_CvCompile2Member;`
- L210 _typedef_ `} SYMS_CvCompile3Member;`
- L215 _typedef_ `} SYMS_CvObjnameMember;`
- L219 _typedef_ `} SYMS_CvUNamespaceMember;`
- L226 _typedef_ `} SYMS_CvRef2Member;`
- L237 _typedef_ `} SYMS_CvSepcodeMember;`
- L242 _typedef_ `} SYMS_CvSlotsym32Member;`
- L249 _typedef_ `} SYMS_CvPogoInfoMember;`
- L254 _typedef_ `} SYMS_CvManyregMember;`
- L259 _typedef_ `} SYMS_CvManyreg2Member;`
- L269 _typedef_ `} SYMS_CvFrameprocMember;`
- L280 _typedef_ `} SYMS_CvThunk32Member;`
- L289 _typedef_ `} SYMS_CvBlock32Member;`
- L296 _typedef_ `} SYMS_CvLabel32Member;`
- L302 _typedef_ `} SYMS_CvConstantMember;`
- L307 _typedef_ `} SYMS_CvUDTMember;`
- L316 _typedef_ `} SYMS_CvTrampolineMember;`
- L326 _typedef_ `} SYMS_CvSectionMember;`
- L334 _typedef_ `} SYMS_CvCoffGroupMember;`
- L340 _typedef_ `} SYMS_CvExportMember;`
- L347 _typedef_ `} SYMS_CvCallSiteInfoMember;`
- L354 _typedef_ `} SYMS_CvFrameCookieMember;`
- L359 _typedef_ `} SYMS_CvEnvblockMember;`
- L365 _typedef_ `} SYMS_CvLocalMember;`
- L371 _typedef_ `} SYMS_CvLvarAddrRangeMember;`
- L376 _typedef_ `} SYMS_CvLvarAddrGapMember;`
- L382 _typedef_ `} SYMS_CvDefrangeMember;`
- L389 _typedef_ `} SYMS_CvDefrangeSubfieldMember;`
- L396 _typedef_ `} SYMS_CvDefrangeRegisterMember;`
- L402 _typedef_ `} SYMS_CvDefrangeFramepointerRelMember;`
- L410 _typedef_ `} SYMS_CvDefrangeSubfieldRegisterMember;`
- L414 _typedef_ `} SYMS_CvDefrangeFramepointerRelFullScopeMember;`
- L422 _typedef_ `} SYMS_CvDefrangeRegisterRelMember;`
- L429 _typedef_ `} SYMS_CvData32Member;`
- L436 _typedef_ `} SYMS_CvPubsym32Member;`
- L439 _typedef_ `} SYMS_CvGProc16Member;`
- L442 _typedef_ `} SYMS_CvGProc3216tMember;`
- L456 _typedef_ `} SYMS_CvProc32Member;`
- L463 _typedef_ `} SYMS_CvRegrel32Member;`
- L467 _typedef_ `} SYMS_CvBuildInfoMember;`
- L473 _typedef_ `} SYMS_CvFunctionListMember;`
- L480 _typedef_ `} SYMS_CvInlineSiteMember;`
- L488 _typedef_ `} SYMS_CvInlineSite2Member;`
- L491 _typedef_ `} SYMS_CvInlineSiteEndMember;`
- L496 _typedef_ `} SYMS_CvInlineesMember;`
- L503 _typedef_ `} SYMS_CvFileStaticMember;`
- L510 _typedef_ `} SYMS_CvHeapAllocSiteMember;`
- L516 _typedef_ `} SYMS_CvLocalVarAttrMember;`
- L522 _typedef_ `} SYMS_CvFramerelMember;`
- L528 _typedef_ `} SYMS_CvAttrRegMember;`
- L535 _typedef_ `} SYMS_CvAttrRegrelMember;`
- L541 _typedef_ `} SYMS_CvAttrManyregMember;`
- L546 _typedef_ `} SYMS_CvFastLinkMember;`
- L557 _typedef_ `} SYMS_CvArmSwitchTableMember;`
- L563 _typedef_ `} SYMS_CvRefMiniPdbMember;`
- L569 _typedef_ `} SYMS_CvModTypeRefMember;`
- L575 _typedef_ `} SYMS_CvDiscardedMember;`
- L582 _typedef_ `} SYMS_CvLeafPreCompMember;`
- L588 _typedef_ `} SYMS_CvLeafTypeServerMember;`
- L594 _typedef_ `} SYMS_CvLeafTypeServer2Member;`
- L599 _typedef_ `} SYMS_CvLeafBuildInfoMember;`
- L603 _typedef_ `} SYMS_CvLeafSkip_16tMember;`
- L607 _typedef_ `} SYMS_CvLeafSkipMember;`
- L611 _typedef_ `} SYMS_CvLeafVTShapeMember;`
- L615 _typedef_ `} SYMS_CvLeafLabelMember;`
- L620 _typedef_ `} SYMS_CvLeafModifierMember;`
- L625 _typedef_ `} SYMS_CvLeafPointerMember;`
- L633 _typedef_ `} SYMS_CvLeafProcedureMember;`
- L644 _typedef_ `} SYMS_CvLeafMFunctionMember;`
- L648 _typedef_ `} SYMS_CvLeafArgListMember;`
- L654 _typedef_ `} SYMS_CvLeafBitFieldMember;`
- L659 _typedef_ `} SYMS_CvLeafIndexMember;`
- L664 _typedef_ `} SYMS_CvLeafArrayMember;`
- L672 _typedef_ `} SYMS_CvLeafStructMember;`
- L678 _typedef_ `} SYMS_CvLeafUnionMember;`
- L685 _typedef_ `} SYMS_CvLeafEnumMember;`
- L689 _typedef_ `} SYMS_CvLeafAliasMember;`
- L696 _typedef_ `} SYMS_CvLeafMemberMember;`
- L702 _typedef_ `} SYMS_CvLeafStMemberMember;`
- L708 _typedef_ `} SYMS_CvLeafMethodListMemberMember;`
- L713 _typedef_ `} SYMS_CvLeafMethodMember;`
- L718 _typedef_ `} SYMS_CvLeafOneMethodMember;`
- L722 _typedef_ `} SYMS_CvLeafEnumerateMember;`
- L727 _typedef_ `} SYMS_CvLeafNestTypeMember;`
- L732 _typedef_ `} SYMS_CvLeafNestTypeExMember;`
- L737 _typedef_ `} SYMS_CvLeafBClassMember;`
- L743 _typedef_ `} SYMS_CvLeafVBClassMember;`
- L748 _typedef_ `} SYMS_CvLeafVFuncTabMember;`
- L754 _typedef_ `} SYMS_CvLeafVFuncOffMember;`
- L761 _typedef_ `} SYMS_CvLeafVFTableMember;`
- L765 _typedef_ `} SYMS_CvLeafVFPathMember;`
- L770 _typedef_ `} SYMS_CvLeafFuncIdMember;`
- L775 _typedef_ `} SYMS_CvLeafMFuncIdMember;`
- L780 _typedef_ `} SYMS_CvLeafStringIdMember;`
- L786 _typedef_ `} SYMS_CvLeafUDTSrcLineMember;`
- L793 _typedef_ `} SYMS_CvLeafModSrcLineMember;`
- L802 _typedef_ `} SYMS_CvLeafClassPtrMember;`
- L807 _typedef_ `} SYMS_CvSubSectionHeaderMember;`
- L813 _typedef_ `} SYMS_CvInlineeSourceLineMember;`
- L821 _typedef_ `} SYMS_CvInlineeSourceLineExMember;`
- L826 _prototype_ `SYMS_U64 syms_enum_index_from_cvarch(SYMS_U64 v);` — syms_enum_index_from_cvbasicpointerkind - skipped identity mapping
- L827 _prototype_ `SYMS_U64 syms_enum_index_from_cv_all_reg(SYMS_U64 v);`
- L828 _prototype_ `SYMS_U64 syms_enum_index_from_cvregx86(SYMS_U64 v);`
- L829 _prototype_ `SYMS_U64 syms_enum_index_from_cvregx64(SYMS_U64 v);`
- L830 _prototype_ `SYMS_U64 syms_enum_index_from_cvsignature(SYMS_U64 v);`
- L831 _prototype_ `SYMS_U64 syms_enum_index_from_cvsymkind(SYMS_U64 v);`
- L841 _prototype_ `SYMS_U64 syms_enum_index_from_cvleaf(SYMS_U64 v);` — syms_enum_index_from_cv_generic_style - skipped identity mapping syms_enum_index_from_cvlanguage - skipped identity mapping syms_enum_index_from_cvencodedframeptrreg - skipped identity mapping syms_enum_index_from_cv_thunk_ordinal - skipped identity mapping syms_enum_index_from_cvtrampolinekind - skipped identity mapping syms_enum_index_from_cvframecookiekind - skipped identity mapping syms_enum_index_from_cv_b_a_opcode - skipped identity mapping syms_enum_index_from_cv_arm_switch_type - skipped identity mapping syms_enum_index_from_cv_discarded_type - skipped identity mapping
- L845 _prototype_ `SYMS_U64 syms_enum_index_from_cvpointermode(SYMS_U64 v);` — syms_enum_index_from_cvhfakind - skipped identity mapping syms_enum_index_from_cvmocomudtkind - skipped identity mapping syms_enum_index_from_cvpointerkind - skipped identity mapping
- L850 _prototype_ `SYMS_U64 syms_enum_index_from_cvlabelkind(SYMS_U64 v);` — syms_enum_index_from_cv_member_pointer_kind - skipped identity mapping syms_enum_index_from_cvvirtualtableshape - skipped identity mapping syms_enum_index_from_cvmethodprop - skipped identity mapping syms_enum_index_from_cvmemberaccess - skipped identity mapping
- L852 _prototype_ `SYMS_U64 syms_enum_index_from_cvsubsectionkind(SYMS_U64 v);` — syms_enum_index_from_cvcallkind - skipped identity mapping
- L859 _prototype_ `SYMS_SerialType* syms_type_info_from_sym_kind(SYMS_CvSymKind v);`
- L860 _prototype_ `SYMS_SerialType* syms_type_info_from_cv_leaf(SYMS_CvLeaf v);`
- L864 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvGuid;`
- L865 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvBasicPointerKind;`
- L866 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvArch;`
- L867 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvAllReg;`
- L868 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRegx86;`
- L869 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRegx64;`
- L870 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSignature;`
- L871 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSymKind;`
- L872 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvAnnotation;`
- L873 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRegister;`
- L874 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvBPRelSym32;`
- L875 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvVPathSym32;`
- L876 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvOEM;`
- L877 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSLink32;`
- L878 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvGenericStyle;`
- L879 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvGenericFlags;`
- L880 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvReturn;`
- L881 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvStartSearch;`
- L882 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLanguage;`
- L883 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvThread32;`
- L884 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCompileFlags;`
- L885 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCompile;`
- L886 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvEnd;`
- L887 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCompile2Flags;`
- L888 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCompile2;`
- L889 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCompile3Flags;`
- L890 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCompile3;`
- L891 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvObjname;`
- L892 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvUNamespace;`
- L893 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRef2;`
- L894 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSepcodeFlags;`
- L895 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSepcode;`
- L896 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSlotsym32;`
- L897 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvPogoInfo;`
- L898 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvManyreg;`
- L899 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvManyreg2;`
- L900 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvEncodedFramePtrReg;`
- L901 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFrameprocFlags;`
- L902 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFrameproc;`
- L903 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvThunkOrdinal;`
- L904 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvThunk32;`
- L905 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvBlock32;`
- L906 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvProcFlags;`
- L907 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLabel32;`
- L908 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvConstant;`
- L909 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvUDT;`
- L910 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvTrampolineKind;`
- L911 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvTrampoline;`
- L912 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSection;`
- L913 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCoffGroup;`
- L914 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvExportFlags;`
- L915 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvExport;`
- L916 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCallSiteInfo;`
- L917 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFrameCookieKind;`
- L918 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFrameCookie;`
- L919 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvEnvblock;`
- L920 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLocalFlags;`
- L921 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLocal;`
- L922 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLvarAddrRange;`
- L923 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLvarAddrGap;`
- L924 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRangeAttribs;`
- L925 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrange;`
- L926 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrangeSubfield;`
- L927 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrangeRegister;`
- L928 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrangeFramepointerRel;`
- L929 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrangeSubfieldRegister;`
- L930 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrangeFramepointerRelFullScope;`
- L931 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrangeRegisterRelFlags;`
- L932 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDefrangeRegisterRel;`
- L933 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvData32;`
- L934 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvPubsymFlags;`
- L935 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvPubsym32;`
- L936 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvGProc16;`
- L937 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvGProc3216t;`
- L938 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvProc32;`
- L939 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRegrel32;`
- L940 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvBuildInfo;`
- L941 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFunctionList;`
- L942 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvBAOpcode;`
- L943 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvInlineSite;`
- L944 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvInlineSite2;`
- L945 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvInlineSiteEnd;`
- L946 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvInlinees;`
- L947 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFileStatic;`
- L948 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvHeapAllocSite;`
- L949 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLocalVarAttr;`
- L950 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFramerel;`
- L951 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvAttrReg;`
- L952 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvAttrRegrel;`
- L953 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvAttrManyreg;`
- L954 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFastLinkFlags;`
- L955 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFastLink;`
- L956 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvArmSwitchType;`
- L957 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvArmSwitchTable;`
- L958 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRefMiniPdbFlags;`
- L959 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvRefMiniPdb;`
- L960 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvModTypeRefFlags;`
- L961 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvModTypeRef;`
- L962 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDiscardedType;`
- L963 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDiscardedFlags;`
- L964 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvDiscarded;`
- L965 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeaf;`
- L966 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvModifierFlags;`
- L967 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvHFAKind;`
- L968 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvMoComUDTKind;`
- L969 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvTypeProps;`
- L970 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvPointerKind;`
- L971 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvPointerMode;`
- L972 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvPointerAttribs;`
- L973 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvMemberPointerKind;`
- L974 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvVirtualTableShape;`
- L975 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvMethodProp;`
- L976 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvMemberAccess;`
- L977 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFieldAttribs;`
- L978 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLabelKind;`
- L979 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvFunctionAttribs;`
- L980 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvCallKind;`
- L981 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafPreComp;`
- L982 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafTypeServer;`
- L983 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafTypeServer2;`
- L984 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafBuildInfo;`
- L985 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafSkip_16t;`
- L986 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafSkip;`
- L987 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafVTShape;`
- L988 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafLabel;`
- L989 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafModifier;`
- L990 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafPointer;`
- L991 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafProcedure;`
- L992 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafMFunction;`
- L993 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafArgList;`
- L994 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafBitField;`
- L995 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafIndex;`
- L996 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafArray;`
- L997 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafStruct;`
- L998 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafUnion;`
- L999 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafEnum;`
- L1000 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafAlias;`
- L1001 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafMember;`
- L1002 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafStMember;`
- L1003 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafMethodListMember;`
- L1004 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafMethod;`
- L1005 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafOneMethod;`
- L1006 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafEnumerate;`
- L1007 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafNestType;`
- L1008 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafNestTypeEx;`
- L1009 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafBClass;`
- L1010 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafVBClass;`
- L1011 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafVFuncTab;`
- L1012 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafVFuncOff;`
- L1013 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafVFTable;`
- L1014 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafVFPath;`
- L1015 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafFuncId;`
- L1016 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafMFuncId;`
- L1017 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafStringId;`
- L1018 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafUDTSrcLine;`
- L1019 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafModSrcLine;`
- L1020 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvLeafClassPtr;`
- L1021 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSubSectionKind;`
- L1022 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvSubSectionHeader;`
- L1023 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvChecksumKind;`
- L1024 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvInlineeSourceLineSig;`
- L1025 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvInlineeSourceLine;`
- L1026 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_CvInlineeSourceLineEx;`
- L1041 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_UnitFeatures;`
- L1042 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_SymbolKind;`
- L1043 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_TypeModifiers;`
- L1044 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MemVisibility;`
- L1057 _prototype_ `SYMS_U64 syms_enum_index_from_dwlanguage(SYMS_U64 v);` — syms_enum_index_from_dw_mode - skipped identity mapping syms_enum_index_from_dw_version - skipped identity mapping syms_enum_index_from_dw_section_kind - skipped identity mapping
- L1059 _prototype_ `SYMS_U64 syms_enum_index_from_dwextopcode(SYMS_U64 v);` — syms_enum_index_from_dwstdopcode - skipped identity mapping
- L1061 _prototype_ `SYMS_U64 syms_enum_index_from_dwtagkind(SYMS_U64 v);` — syms_enum_index_from_dw_name_case - skipped identity mapping
- L1062 _prototype_ `SYMS_U64 syms_enum_index_from_dwformkind(SYMS_U64 v);`
- L1063 _prototype_ `SYMS_U64 syms_enum_index_from_dwattribkind(SYMS_U64 v);`
- L1064 _prototype_ `SYMS_U64 syms_enum_index_from_dw_attrib_type_encoding(SYMS_U64 v);`
- L1073 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwMode;`
- L1074 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwVersion;`
- L1075 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwSectionKind;`
- L1076 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwLanguage;`
- L1077 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwStdOpcode;`
- L1078 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwExtOpcode;`
- L1079 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwNameCase;`
- L1080 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwTagKind;`
- L1081 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwAttribClass;`
- L1082 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwFormKind;`
- L1083 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwAttribKind;`
- L1084 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwAttribTypeEncoding;`
- L1085 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwCallingConvention;`
- L1086 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwAccess;`
- L1087 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwVirtuality;`
- L1088 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwRngListEntryKind;`
- L1089 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwLocListEntryKind;`
- L1099 _prototype_ `SYMS_U64 syms_enum_index_from_dw_c_f_a_detail(SYMS_U64 v);`
- L1100 _prototype_ `SYMS_U64 syms_enum_index_from_dw_c_f_a_mask(SYMS_U64 v);`
- L1104 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwCFADetail;`
- L1105 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwCFAMask;`
- L1115 _prototype_ `SYMS_U64 syms_enum_index_from_dwregx86(SYMS_U64 v);`
- L1116 _prototype_ `SYMS_U64 syms_enum_index_from_dwregx64(SYMS_U64 v);`
- L1117 _prototype_ `SYMS_U64 syms_enum_index_from_dw_op(SYMS_U64 v);`
- L1121 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwRegX86;`
- L1122 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwRegX64;`
- L1123 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DwOp;`
- L1134 _prototype_ `SYMS_U64 syms_enum_index_from_elf_os_abi(SYMS_U64 v);` — syms_enum_index_from_elf_class - skipped identity mapping
- L1136 _prototype_ `SYMS_U64 syms_enum_index_from_elf_machine_kind(SYMS_U64 v);` — syms_enum_index_from_elf_version - skipped identity mapping
- L1139 _prototype_ `SYMS_U64 syms_enum_index_from_elf_p_kind(SYMS_U64 v);` — syms_enum_index_from_elf_type - skipped identity mapping syms_enum_index_from_elf_data - skipped identity mapping
- L1140 _prototype_ `SYMS_U64 syms_enum_index_from_elfsectioncode(SYMS_U64 v);`
- L1141 _prototype_ `SYMS_U64 syms_enum_index_from_elf_section_index(SYMS_U64 v);`
- L1142 _prototype_ `SYMS_U64 syms_enum_index_from_elfauxtype(SYMS_U64 v);`
- L1143 _prototype_ `SYMS_U64 syms_enum_index_from_elfdyntag(SYMS_U64 v);`
- L1144 _prototype_ `SYMS_U64 syms_enum_index_from_elf_sym_bind(SYMS_U64 v);`
- L1145 _prototype_ `SYMS_U64 syms_enum_index_from_elf_sym_type(SYMS_U64 v);`
- L1147 _prototype_ `SYMS_U64 syms_enum_index_from_elf_reloc_i386(SYMS_U64 v);` — syms_enum_index_from_elf_sym_visibility - skipped identity mapping
- L1148 _prototype_ `SYMS_U64 syms_enum_index_from_elf_reloc_x8664(SYMS_U64 v);`
- L1149 _prototype_ `SYMS_U64 syms_enum_index_from_elf_note_type(SYMS_U64 v);`
- L1151 _prototype_ `SYMS_U64 syms_enum_index_from_elf_gnu_property(SYMS_U64 v);` — syms_enum_index_from_elf_gnu_a_b_i_tag - skipped identity mapping
- L1152 _prototype_ `SYMS_U64 syms_enum_index_from_elf_gnu_property_x86(SYMS_U64 v);`
- L1156 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfClass;`
- L1157 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfOsAbi;`
- L1158 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfVersion;`
- L1159 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfMachineKind;`
- L1160 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfType;`
- L1161 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfData;`
- L1162 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfPKind;`
- L1163 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfPFlag;`
- L1164 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfSectionCode;`
- L1165 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfSectionIndex;`
- L1166 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfSectionFlag;`
- L1167 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfAuxType;`
- L1168 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfDynTag;`
- L1169 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfDynFlag;`
- L1170 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfDynFeatureFlag;`
- L1171 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfSymBind;`
- L1172 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfSymType;`
- L1173 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfSymVisibility;`
- L1174 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfRelocI386;`
- L1175 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfRelocX8664;`
- L1176 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfExternalVerFlag;`
- L1177 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfNoteType;`
- L1178 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuABITag;`
- L1179 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuProperty;`
- L1180 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuPropertyX86Isa1;`
- L1181 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuPropertyX86Compat1Isa1;`
- L1182 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuPropertyX86Compat2Isa1;`
- L1183 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuPropertyX86;`
- L1184 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuPropertyX86Feature1;`
- L1185 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ElfGnuPropertyX86Feature2;`
- L1197 _typedef_ `} SYMS_MachLCStrMember;`
- L1203 _typedef_ `} SYMS_MachUUIDMember;`
- L1210 _typedef_ `} SYMS_MachDylibMember;`
- L1216 _typedef_ `} SYMS_MachDylibCommandMember;`
- L1231 _typedef_ `} SYMS_MachDyldInfoCommandMember;`
- L1236 _typedef_ `} SYMS_MachLoadCommandMember;`
- L1241 _typedef_ `} SYMS_MachFatHeaderMember;`
- L1249 _typedef_ `} SYMS_MachFatArchMember;`
- L1259 _typedef_ `} SYMS_MachHeader32Member;`
- L1270 _typedef_ `} SYMS_MachHeader64Member;`
- L1283 _typedef_ `} SYMS_MachSegmentCommand32Member;`
- L1296 _typedef_ `} SYMS_MachSegmentCommand64Member;`
- L1310 _typedef_ `} SYMS_MachSection32Member;`
- L1325 _typedef_ `} SYMS_MachSection64Member;`
- L1334 _typedef_ `} SYMS_MachSymtabCommandMember;`
- L1357 _typedef_ `} SYMS_MachDySymtabCommandMember;`
- L1365 _typedef_ `} SYMS_MachNList32Member;`
- L1373 _typedef_ `} SYMS_MachNList64Member;`
- L1382 _typedef_ `} SYMS_MachBuildVersionCommandMember;`
- L1387 _typedef_ `} SYMS_MachBuildToolVersionMember;`
- L1394 _typedef_ `} SYMS_MachVersionMinMember;`
- L1400 _typedef_ `} SYMS_MachDylinkerMember;`
- L1407 _typedef_ `} SYMS_MachPreboundDylibCommandMember;`
- L1420 _typedef_ `} SYMS_MachRoutinesCommandMember;`
- L1433 _typedef_ `} SYMS_MachRoutines64CommandMember;`
- L1439 _typedef_ `} SYMS_MachSubFrameworkCommandMember;`
- L1445 _typedef_ `} SYMS_MachSubUmbrellaCommandMember;`
- L1451 _typedef_ `} SYMS_MachSubClientCommandMember;`
- L1457 _typedef_ `} SYMS_MachSubLibraryCommandMember;`
- L1464 _typedef_ `} SYMS_MachTwoLevelHintsCommandMember;`
- L1470 _typedef_ `} SYMS_MachPrebindChecksumCommandMember;`
- L1476 _typedef_ `} SYMS_MachRPathCommandMember;`
- L1483 _typedef_ `} SYMS_MachLinkeditDataCommandMember;`
- L1491 _typedef_ `} SYMS_MachEncryptionInfoCommandMember;`
- L1500 _typedef_ `} SYMS_MachEncryptionInfo64CommandMember;`
- L1507 _typedef_ `} SYMS_MachEntryPointCommandMember;`
- L1513 _typedef_ `} SYMS_MachSourceVersionCommandMember;`
- L1519 _typedef_ `} SYMS_MachLinkerOptionCommandMember;`
- L1527 _typedef_ `} SYMS_MachNoteCommandMember;`
- L1534 _typedef_ `} SYMS_MachSymSegCommandMember;`
- L1540 _typedef_ `} SYMS_MachFvmlibMember;`
- L1546 _typedef_ `} SYMS_MachFvmlibCommandMember;`
- L1551 _typedef_ `} SYMS_MachThreadCommandMember;`
- L1555 _prototype_ `SYMS_U64 syms_enum_index_from_mach_cpu_type(SYMS_U64 v);`
- L1556 _prototype_ `SYMS_U64 syms_enum_index_from_mach_cpu_family(SYMS_U64 v);`
- L1559 _prototype_ `SYMS_U64 syms_enum_index_from_mach_cpu_subtype_x86(SYMS_U64 v);` — syms_enum_index_from_mach_cpu_subtype - skipped identity mapping syms_enum_index_from_mach_cpu_subtype_v_ax - skipped identity mapping
- L1560 _prototype_ `SYMS_U64 syms_enum_index_from_mach_cpu_subtype_intel(SYMS_U64 v);`
- L1561 _prototype_ `SYMS_U64 syms_enum_index_from_mach_cpu_subtype_a_rm(SYMS_U64 v);`
- L1563 _prototype_ `SYMS_U64 syms_enum_index_from_mach_filetype(SYMS_U64 v);` — syms_enum_index_from_mach_cpu_subtype_a_r_m64 - skipped identity mapping
- L1564 _prototype_ `SYMS_U64 syms_enum_index_from_mach_flags(SYMS_U64 v);`
- L1565 _prototype_ `SYMS_U64 syms_enum_index_from_mach_load_command_type(SYMS_U64 v);`
- L1567 _prototype_ `SYMS_U64 syms_enum_index_from_mach_section_attr(SYMS_U64 v);` — syms_enum_index_from_mach_section_type - skipped identity mapping
- L1568 _prototype_ `SYMS_U64 syms_enum_index_from_mach_platform_type(SYMS_U64 v);`
- L1569 _prototype_ `SYMS_U64 syms_enum_index_from_mach_tool_type(SYMS_U64 v);`
- L1570 _prototype_ `SYMS_U64 syms_enum_index_from_mach_bind_type(SYMS_U64 v);`
- L1571 _prototype_ `SYMS_U64 syms_enum_index_from_mach_bind_opcode(SYMS_U64 v);`
- L1572 _prototype_ `SYMS_U64 syms_enum_index_from_mach_bind_special_dylib(SYMS_U64 v);`
- L1573 _prototype_ `SYMS_U64 syms_enum_index_from_mach_n_list_type(SYMS_U64 v);`
- L1574 _prototype_ `SYMS_U64 syms_enum_index_from_mach_stab_type(SYMS_U64 v);`
- L1576 _prototype_ `SYMS_U64 syms_enum_index_from_mach_unwind_enc_mode_x86(SYMS_U64 v);` — syms_enum_index_from_mach_export_symbol_kind - skipped identity mapping
- L1578 _prototype_ `SYMS_U64 syms_enum_index_from_mach_unwind_enc_mode_x64(SYMS_U64 v);` — syms_enum_index_from_mach_unwind_register_x86 - skipped identity mapping
- L1583 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuType;`
- L1584 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuFamily;`
- L1585 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuSubtype;`
- L1586 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuSubtypeVAX;`
- L1587 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuSubtypeX86;`
- L1588 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuSubtypeIntel;`
- L1589 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuSubtypeARM;`
- L1590 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachCpuSubtypeARM64;`
- L1591 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachVMProt;`
- L1592 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachFiletype;`
- L1593 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachFlags;`
- L1594 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachLoadCommandType;`
- L1595 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSectionType;`
- L1596 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSectionAttr;`
- L1597 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachPlatformType;`
- L1598 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachToolType;`
- L1599 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachBindType;`
- L1600 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachBindOpcode;`
- L1601 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachBindSymbolFlags;`
- L1602 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachBindSpecialDylib;`
- L1603 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachNListType;`
- L1604 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachStabType;`
- L1605 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachExportSymbolKind;`
- L1606 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachExportSymbolFlags;`
- L1607 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachLCStr;`
- L1608 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachUUID;`
- L1609 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachDylib;`
- L1610 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachDylibCommand;`
- L1611 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachDyldInfoCommand;`
- L1612 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachLoadCommand;`
- L1613 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachFatHeader;`
- L1614 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachFatArch;`
- L1615 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachHeader32;`
- L1616 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachHeader64;`
- L1617 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSegmentCommand32;`
- L1618 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSegmentCommand64;`
- L1619 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSection32;`
- L1620 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSection64;`
- L1621 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSymtabCommand;`
- L1622 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachDySymtabCommand;`
- L1623 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachNList32;`
- L1624 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachNList64;`
- L1625 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachBuildVersionCommand;`
- L1626 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachBuildToolVersion;`
- L1627 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachVersionMin;`
- L1628 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachDylinker;`
- L1629 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachPreboundDylibCommand;`
- L1630 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachRoutinesCommand;`
- L1631 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachRoutines64Command;`
- L1632 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSubFrameworkCommand;`
- L1633 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSubUmbrellaCommand;`
- L1634 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSubClientCommand;`
- L1635 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSubLibraryCommand;`
- L1636 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachTwoLevelHintsCommand;`
- L1637 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachTwoLevelHint;`
- L1638 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachPrebindChecksumCommand;`
- L1639 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachRPathCommand;`
- L1640 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachLinkeditDataCommand;`
- L1641 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachEncryptionInfoCommand;`
- L1642 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachEncryptionInfo64Command;`
- L1643 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachEntryPointCommand;`
- L1644 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSourceVersionCommand;`
- L1645 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachLinkerOptionCommand;`
- L1646 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachNoteCommand;`
- L1647 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachSymSegCommand;`
- L1648 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachFvmlib;`
- L1649 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachFvmlibCommand;`
- L1650 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachThreadCommand;`
- L1651 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachUnwindEncModeX86;`
- L1652 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachUnwindRegisterX86;`
- L1653 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachUnwindEncX86;`
- L1654 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachUnwindEncModeX64;`
- L1655 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_MachUnwindRegisterX64;`
- L1685 _typedef_ `} SYMS_DosHeaderMember;`
- L1718 _typedef_ `} SYMS_PeOptionalHeader32Member;`
- L1750 _typedef_ `} SYMS_PeOptionalHeader32PlusMember;`
- L1755 _typedef_ `} SYMS_PeDataDirectoryMember;`
- L1766 _typedef_ `} SYMS_PeDebugDirectoryMember;`
- L1770 _prototype_ `SYMS_U64 syms_enum_index_from_pe_windows_subsystem(SYMS_U64 v);`
- L1772 _prototype_ `SYMS_U64 syms_enum_index_from_pe_debug_directory_type(SYMS_U64 v);` — syms_enum_index_from_pe_data_directory_index - skipped identity mapping
- L1773 _prototype_ `SYMS_U64 syms_enum_index_from_pe_f_p_o_flags(SYMS_U64 v);`
- L1779 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DosHeader;`
- L1780 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeWindowsSubsystem;`
- L1781 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_ImageFileCharacteristics;`
- L1782 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_DllCharacteristics;`
- L1783 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeOptionalHeader32;`
- L1784 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeOptionalHeader32Plus;`
- L1785 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeDataDirectoryIndex;`
- L1786 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeDataDirectory;`
- L1787 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeDebugDirectoryType;`
- L1788 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeFPOFlags;`
- L1789 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeFPOEncoded;`
- L1790 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeFPOType;`
- L1791 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeDebugMiscType;`
- L1792 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeDebugDirectory;`
- L1793 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeGlobalFlags;`
- L1794 _variable_ `SYMS_EXTERN SYMS_SerialType _syms_serial_type_SYMS_PeLoadConfigGuardFlags;`

### `Source/Runtime/SymsLib/syms/core/group/syms_functions.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_FUNCTIONS_H`
- L11 _prototype_ `SYMS_SpatialMap1D syms_spatial_map_from_line_table(SYMS_Arena *arena, SYMS_LineTable *table);` — creates a map of (voff -> line_sequence_index)
- L15 _prototype_ `syms_spatial_map_for_procs_from_sid_array(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolIDArray *sid_array);`
- L22 _prototype_ `syms_name_map_from_sid_array(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID *sids, SYMS_U64 sid_count);`

### `Source/Runtime/SymsLib/syms/core/group/syms_group.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L11-24_

#### struct `SYMS_Group`  
`typedef struct SYMS_Group`  
_L26-103_
- L27 _public member_ `SYMS_Arena *arena;`
- L30 _public member_ `SYMS_Arena **lane_arenas;` — - thread lanes
- L31 _public member_ `SYMS_U64 lane_count;`
- L32 _public member_ `SYMS_U64 lane_max;`
- L35 _public member_ `SYMS_String8 bin_data;` — - data for binary and debug files
- L36 _public member_ `SYMS_String8 dbg_data;`
- L37 _public member_ `SYMS_BinAccel *bin;`
- L38 _public member_ `SYMS_DbgAccel *dbg;`
- L41 _public member_ `SYMS_Arch arch;` — - top-level accelerators and info
- L42 _public member_ `SYMS_U64 address_size;`
- L43 _public member_ `SYMS_U64 default_vbase;`
- L44 _public member_ `SYMS_SecInfoArray sec_info_array;`
- L45 _public member_ `SYMS_UnitSetAccel *unit_set;`
- L46 _public member_ `SYMS_U64 unit_count;`
- L49 _public member_ `SYMS_String8 *sec_names;` — - basic section caches
- L52 _public member_ `SYMS_GroupUnitCacheFlags *unit_cache_flags;` — - basic unit caches
- L53 _public member_ `SYMS_UnitAccel **units;`
- L54 _public member_ `SYMS_SymbolIDArray *proc_sid_arrays;`
- L55 _public member_ `SYMS_SymbolIDArray *var_sid_arrays;`
- L56 _public member_ `SYMS_SymbolIDArray *thread_sid_arrays;`
- L57 _public member_ `SYMS_SymbolIDArray *type_sid_arrays;`
- L58 _public member_ `SYMS_String8Array *file_tables;`
- L59 _public member_ `SYMS_String8Array *inferred_file_tables;`
- L60 _public member_ `SYMS_LineParseOut *line_tables;`
- L61 _public member_ `SYMS_SpatialMap1D *unit_proc_maps;`
- L62 _public member_ `SYMS_SpatialMap1D *unit_var_maps;`
- L63 _public member_ `SYMS_SpatialMap1D *line_sequence_maps;`
- L64 _public member_ `SYMS_FileToLineToAddrMap *file_to_line_to_addr_maps;`
- L67 _public member_ `SYMS_SymbolNameMap *unit_type_maps;` — TODO(allen): we probably don't need to do this as the type graph does it better
- L70 _public member_ `SYMS_StringCons string_cons;` — - hash tables caches
- L71 _public member_ `SYMS_FileID2NameMap file_id_2_name_map;`
- L74 _public member_ `SYMS_TypeGraph type_graph;` — - type graph
- L77 _public member_ `SYMS_B8 unit_ranges_is_filled;` — - one-time fills/builds
- L78 _public member_ `SYMS_B8 type_map_unit_is_filled;`
- L79 _public member_ `SYMS_B8 symbol_map_unit_is_filled;`
- L80 _public member_ `SYMS_B8 mangled_symbol_map_unit_is_filled;`
- L81 _public member_ `SYMS_B8 sec_map_v_is_built;`
- L82 _public member_ `SYMS_B8 sec_map_f_is_built;`
- L83 _public member_ `SYMS_B8 unit_map_is_built;`
- L84 _public member_ `SYMS_B8 name_2_file_id_map_is_built;`
- L85 _public member_ `SYMS_B8 link_name_record_array_is_filled;`
- L86 _public member_ `SYMS_B8 link_name_spatial_map_is_built;`
- L87 _public member_ `SYMS_B8 link_map_is_built;`
- L88 _public member_ `SYMS_B8 link_name_unit_is_filled;`
- L90 _public member_ `SYMS_UnitRangeArray unit_ranges;`
- L91 _public member_ `SYMS_SpatialMap1D sec_map_v;`
- L92 _public member_ `SYMS_SpatialMap1D sec_map_f;`
- L93 _public member_ `SYMS_SpatialMap1D unit_map;`
- L94 _public member_ `SYMS_Name2FileIDMap name_2_file_id_map;`
- L95 _public member_ `SYMS_LinkNameRecArray link_name_record_array;`
- L96 _public member_ `SYMS_SpatialMap1D link_name_spatial_map;`
- L97 _public member_ `SYMS_LinkMapAccel *link_map;`
- L98 _public member_ `SYMS_UnitAccel *link_name_unit;`
- L101 _public member_ `SYMS_MapAndUnit type_mau;` — - map & units
- L102 _public member_ `SYMS_MapAndUnit symbol_mau;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_GROUP_H`
- L10 _typedef_ `typedef SYMS_U32 SYMS_GroupUnitCacheFlags;`
- L12 _enumerator_ `SYMS_GroupUnitCacheFlag_HasProcSidArray = (1 << 0)` (scope `__anonfafcf4580103`)
- L13 _enumerator_ `SYMS_GroupUnitCacheFlag_HasVarSidArray = (1 << 1)` (scope `__anonfafcf4580103`)
- L14 _enumerator_ `SYMS_GroupUnitCacheFlag_HasTlsVarSidArray = (1 << 2)` (scope `__anonfafcf4580103`)
- L15 _enumerator_ `SYMS_GroupUnitCacheFlag_HasTypeSidArray = (1 << 3)` (scope `__anonfafcf4580103`)
- L16 _enumerator_ `SYMS_GroupUnitCacheFlag_HasFileTable = (1 << 4)` (scope `__anonfafcf4580103`)
- L17 _enumerator_ `SYMS_GroupUnitCacheFlag_HasInfFileTable = (1 << 5)` (scope `__anonfafcf4580103`)
- L18 _enumerator_ `SYMS_GroupUnitCacheFlag_HasLineTable = (1 << 6)` (scope `__anonfafcf4580103`)
- L19 _enumerator_ `SYMS_GroupUnitCacheFlag_HasProcMap = (1 << 7)` (scope `__anonfafcf4580103`)
- L20 _enumerator_ `SYMS_GroupUnitCacheFlag_HasVarMap = (1 << 8)` (scope `__anonfafcf4580103`)
- L21 _enumerator_ `SYMS_GroupUnitCacheFlag_HasLineSeqMap = (1 << 9)` (scope `__anonfafcf4580103`)
- L22 _enumerator_ `SYMS_GroupUnitCacheFlag_HasLineToAddrMap = (1 << 10)` (scope `__anonfafcf4580103`)
- L23 _enumerator_ `SYMS_GroupUnitCacheFlag_HasTypeNameMap = (1 << 11)` (scope `__anonfafcf4580103`)
- L103 _typedef_ `} SYMS_Group;`
- L108 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_SymbolIDArray syms_sid_array_nil = {0};`
- L109 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_String8Array syms_string_array_nil = {0};`
- L110 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_LineParseOut syms_line_parse_nil = {{0}};`
- L111 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_SpatialMap1D syms_spatial_map_1d_nil = {0};`
- L112 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_LineToAddrMap syms_line_to_addr_map_nil = {0};`
- L117 _prototype_ `SYMS_Group* syms_group_alloc(void);`
- L118 _prototype_ `void syms_group_release(SYMS_Group *group);`
- L120 _prototype_ `void syms_group_init(SYMS_Group *group, SYMS_ParseBundle *params);`
- L122 _prototype_ `void syms_group_parse_all_units__single_thread(SYMS_Group *group);`
- L123 _prototype_ `void syms_group_parse_all_top_level(SYMS_Group *group);`
- L125 _prototype_ `void syms_group_begin_multilane(SYMS_Group *group, SYMS_U64 lane_count);`
- L126 _prototype_ `void syms_group_end_multilane(SYMS_Group *group);`
- L128 _prototype_ `SYMS_Arena* syms_group_get_lane_arena(SYMS_Group *group);`
- L135 _prototype_ `SYMS_String8 syms_group_bin_data(SYMS_Group *group);`
- L136 _prototype_ `SYMS_BinAccel* syms_group_bin(SYMS_Group *group);`
- L137 _prototype_ `SYMS_String8 syms_group_dbg_data(SYMS_Group *group);`
- L138 _prototype_ `SYMS_DbgAccel* syms_group_dbg(SYMS_Group *group);`
- L139 _prototype_ `SYMS_Arch syms_group_arch(SYMS_Group *group);`
- L140 _prototype_ `SYMS_UnitSetAccel* syms_group_unit_set(SYMS_Group *group);`
- L142 _prototype_ `SYMS_U64 syms_group_address_size(SYMS_Group *group);`
- L143 _prototype_ `SYMS_U64 syms_group_default_vbase(SYMS_Group *group);`
- L145 _prototype_ `SYMS_SecInfoArray syms_group_sec_info_array(SYMS_Group *group);`
- L146 _prototype_ `SYMS_SecInfo* syms_group_sec_info_from_number(SYMS_Group *group, SYMS_U64 n);`
- L148 _prototype_ `SYMS_U64 syms_group_unit_count(SYMS_Group *group);`
- L149 _prototype_ `SYMS_UnitInfo syms_group_unit_info_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L150 _prototype_ `SYMS_UnitNames syms_group_unit_names_from_uid(SYMS_Arena *arena, SYMS_Group *group, SYMS_UnitID uid);`
- L153 _prototype_ `SYMS_UnitAccel* syms_group_unit_from_uid(SYMS_Group *group, SYMS_UnitID uid);` — thread safe (with lanes equipped to group)
- L154 _prototype_ `SYMS_SymbolIDArray*syms_group_proc_sid_array_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L155 _prototype_ `SYMS_SymbolIDArray*syms_group_var_sid_array_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L156 _prototype_ `SYMS_SymbolIDArray*syms_group_tls_var_sid_array_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L157 _prototype_ `SYMS_SymbolIDArray*syms_group_type_sid_array_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L158 _prototype_ `SYMS_String8Array* syms_group_file_table_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L159 _prototype_ `SYMS_LineParseOut* syms_group_line_parse_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L160 _prototype_ `SYMS_LineTable* syms_group_line_table_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L161 _prototype_ `SYMS_String8Array* syms_group_inferred_file_table_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L163 _prototype_ `SYMS_String8Array* syms_group_file_table_from_uid_with_fallbacks(SYMS_Group *group, SYMS_UnitID uid);`
- L165 _prototype_ `SYMS_UnitRangeArray syms_group_unit_ranges(SYMS_Group *group);`
- L167 _prototype_ `SYMS_SymbolKind syms_group_symbol_kind_from_sid(SYMS_Group *group, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L169 _prototype_ `SYMS_String8 syms_group_symbol_name_from_sid(SYMS_Arena *arena, SYMS_Group *group, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L172 _prototype_ `SYMS_String8 syms_group_file_name_from_id(SYMS_Group *group, SYMS_UnitID uid, SYMS_FileID file_id);`
- L174 _prototype_ `SYMS_MapAndUnit* syms_group_type_map(SYMS_Group *group);`
- L175 _prototype_ `SYMS_MapAndUnit* syms_group_unmangled_symbol_map(SYMS_Group *group);`
- L177 _prototype_ `SYMS_LinkNameRecArray syms_group_link_name_records(SYMS_Group *group);`
- L178 _prototype_ `SYMS_LinkMapAccel* syms_group_link_name_map(SYMS_Group *group);`
- L179 _prototype_ `SYMS_UnitAccel* syms_group_link_name_unit(SYMS_Group *group);`
- L186 _prototype_ `SYMS_U64 syms_group_sec_number_from_voff__linear_scan(SYMS_Group *group, SYMS_U64 voff);` — - linear scan versions
- L187 _prototype_ `SYMS_U64 syms_group_sec_number_from_foff__linear_scan(SYMS_Group *group, SYMS_U64 foff);`
- L189 _prototype_ `SYMS_U64Maybe syms_group_voff_from_foff__linear_scan(SYMS_Group *group, SYMS_U64 foff);`
- L190 _prototype_ `SYMS_U64Maybe syms_group_foff_from_voff__linear_scan(SYMS_Group *group, SYMS_U64 voff);`
- L192 _prototype_ `SYMS_UnitID syms_group_uid_from_voff__linear_scan(SYMS_Group *group, SYMS_U64 voff);`
- L193 _prototype_ `SYMS_SymbolID syms_group_proc_sid_from_uid_voff__linear_scan(SYMS_Group *group, SYMS_UnitID uid, SYMS_U64 voff);`
- L196 _prototype_ `SYMS_Line syms_group_line_from_uid_voff__linear_scan(SYMS_Group *group, SYMS_UnitID uid, SYMS_U64 voff);`
- L198 _prototype_ `SYMS_U64RangeList syms_group_vranges_from_uid_line__linear_scan(SYMS_Arena *arena, SYMS_Group *group, SYMS_UnitID uid, SYMS_FileID file_id, SYMS_U32 line);`
- L203 _prototype_ `SYMS_SpatialMap1D* syms_group_sec_map_v(SYMS_Group *group);` — - map getters
- L204 _prototype_ `SYMS_SpatialMap1D* syms_group_sec_map_f(SYMS_Group *group);`
- L206 _prototype_ `SYMS_SpatialMap1D* syms_group_unit_map(SYMS_Group *group);`
- L209 _prototype_ `SYMS_SpatialMap1D* syms_group_proc_map_from_uid(SYMS_Group *group, SYMS_UnitID uid);` — thread safe (with lanes equipped to group)
- L210 _prototype_ `SYMS_SpatialMap1D* syms_group_line_sequence_map_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L212 _prototype_ `void syms_group_fetch_line_to_addr_maps_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L213 _prototype_ `SYMS_LineToAddrMap* syms_group_line_to_addr_map_from_uid_file_id(SYMS_Group *group, SYMS_UnitID uid, SYMS_FileID file_id);`
- L216 _prototype_ `SYMS_SymbolNameMap* syms_group_type_map_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L218 _prototype_ `SYMS_SpatialMap1D* syms_group_link_name_spatial_map(SYMS_Group *group);`
- L219 _prototype_ `void syms_group__link_names_sort_in_place(SYMS_LinkNameRec *recs, SYMS_U64 count);`
- L222 _prototype_ `SYMS_U64 syms_group_sec_number_from_voff__accelerated(SYMS_Group *group, SYMS_U64 voff);` — - accelerated versions
- L223 _prototype_ `SYMS_U64 syms_group_sec_number_from_foff__accelerated(SYMS_Group *group, SYMS_U64 foff);`
- L225 _prototype_ `SYMS_U64Maybe syms_group_sec_voff_from_foff__accelerated(SYMS_Group *group, SYMS_U64 voff);`
- L226 _prototype_ `SYMS_U64Maybe syms_group_sec_foff_from_voff__accelerated(SYMS_Group *group, SYMS_U64 foff);`
- L228 _prototype_ `SYMS_UnitID syms_group_uid_from_voff__accelerated(SYMS_Group *group, SYMS_U64 voff);`
- L229 _prototype_ `SYMS_SymbolID syms_group_proc_sid_from_uid_voff__accelerated(SYMS_Group *group, SYMS_UnitID uid, SYMS_U64 voff);`
- L232 _prototype_ `SYMS_Line syms_group_line_from_uid_voff__accelerated(SYMS_Group *group, SYMS_UnitID uid, SYMS_U64 voff);`
- L234 _prototype_ `SYMS_U64RangeArray syms_group_vranges_from_uid_line__accelerated(SYMS_Group *group, SYMS_UnitID uid, SYMS_FileID file_id, SYMS_U32 line);`
- L238 _prototype_ `SYMS_ResolvedLine syms_group_resolved_location_from_proc_sid(SYMS_Group *group, SYMS_UnitAccel *unit, SYMS_SymbolID sid);` — - higher level mapping functions
- L245 _prototype_ `SYMS_USID syms_group_usid_from_unmangled_name(SYMS_Group *group, SYMS_String8 name);`
- L246 _prototype_ `SYMS_USIDList syms_group_all_usid_from_unmangled_name(SYMS_Arena *arena, SYMS_Group *group, SYMS_String8 name);`
- L249 _prototype_ `SYMS_U64 syms_group_voff_from_link_name(SYMS_Group *group, SYMS_String8 name);`
- L250 _prototype_ `SYMS_ResolvedLine syms_group_resolved_location_from_link_name(SYMS_Group *group, SYMS_String8 name);`
- L255 _prototype_ `SYMS_TypeGraph* syms_group_type_graph(SYMS_Group *group);`
- L264 _prototype_ `SYMS_SymbolID syms_group_var_sid_from_uid_voff__linear_scan(SYMS_Group *group, SYMS_UnitID uid, SYMS_U64 voff);`
- L267 _prototype_ `SYMS_SpatialMap1D* syms_group_var_map_from_uid(SYMS_Group *group, SYMS_UnitID uid);`
- L269 _prototype_ `SYMS_SymbolID syms_group_var_sid_from_uid_voff__accelerated(SYMS_Group *group, SYMS_UnitID uid, SYMS_U64 voff);`
- L276 _prototype_ `SYMS_TypeNode* syms_group_type_from_usid(SYMS_Group *group, SYMS_USID usid);`
- L279 _prototype_ `SYMS_USIDList syms_group_type_list_from_name_accelerated(SYMS_Arena *arena, SYMS_Group *group, SYMS_String8 name);` — TODO(allen): sort with name maps?
- L281 _prototype_ `SYMS_SymbolIDArray syms_group_types_from_unit_name(SYMS_Group *group, SYMS_UnitID uid, SYMS_String8 name);`
- L283 _prototype_ `SYMS_U64 syms_group_type_size_from_usid(SYMS_Group *group, SYMS_USID usid);`
- L285 _prototype_ `SYMS_TypeMemberArray syms_group_type_members_from_type(SYMS_Group *group, SYMS_TypeNode *type);`
- L286 _prototype_ `SYMS_EnumMemberArray syms_group_type_enum_members_from_type(SYMS_Group *group, SYMS_TypeNode *type);`
- L291 _prototype_ `SYMS_Name2FileIDMap* syms_group_file_map(SYMS_Group *group);`

### `Source/Runtime/SymsLib/syms/core/group/syms_type_graph.h` (Other)


#### struct `SYMS_TypeConsMember`  
`typedef struct SYMS_TypeConsMember`  
_L12-16_
- L13 _public member_ `struct SYMS_TypeConsMember *next;`
- L14 _public member_ `SYMS_String8 name;`
- L15 _public member_ `struct SYMS_TypeNode *type;`

#### struct `SYMS_TypeConsMemberList`  
`typedef struct SYMS_TypeConsMemberList`  
_L18-22_
- L19 _public member_ `SYMS_TypeConsMember *first;`
- L20 _public member_ `SYMS_TypeConsMember *last;`
- L21 _public member_ `SYMS_U64 count;`

#### struct `SYMS_TypeUSIDPlaceHolder`  
`typedef struct SYMS_TypeUSIDPlaceHolder`  
_L29-31_
- L30 _public member_ `struct SYMS_TypeUSIDNode *usid_node;`

#### struct `SYMS_TypeContentNode`  
`typedef struct SYMS_TypeContentNode`  
_L39-44_
- desc: modifiers,ptrs,arrays,procs -> type node
- L40 _public member_ `struct SYMS_TypeContentNode *next;`
- L41 _public member_ `SYMS_String8 key;`
- L42 _public member_ `SYMS_U64 hash;`
- L43 _public member_ `struct SYMS_TypeNode *type;`

#### struct `SYMS_TypeContentBuckets`  
`typedef struct SYMS_TypeContentBuckets`  
_L46-48_
- L47 _public member_ `SYMS_TypeContentNode **buckets;`

#### struct `SYMS_TypeUSIDNode`  
`typedef struct SYMS_TypeUSIDNode`  
_L51-55_
- desc: usid -> type node
- L52 _public member_ `struct SYMS_TypeUSIDNode *next;`
- L53 _public member_ `SYMS_USID key;`
- L54 _public member_ `struct SYMS_TypeNode *type;`

#### struct `SYMS_TypeUSIDBuckets`  
`typedef struct SYMS_TypeUSIDBuckets`  
_L57-60_
- L58 _public member_ `SYMS_TypeUSIDNode **buckets;`
- L59 _public member_ `SYMS_U64 *bucket_counts;`

#### struct `SYMS_TypeChainNode`  
`typedef struct SYMS_TypeChainNode`  
_L63-66_
- desc: consed name -> chain of type nodes
- L64 _public member_ `struct SYMS_TypeChainNode *next;`
- L65 _public member_ `struct SYMS_TypeNode *type;`

#### struct `SYMS_TypeChain`  
`typedef struct SYMS_TypeChain`  
_L68-72_
- L69 _public member_ `SYMS_TypeChainNode *first;`
- L70 _public member_ `SYMS_TypeChainNode *last;`
- L71 _public member_ `SYMS_U64 count;`

#### struct `SYMS_TypeNameNode`  
`typedef struct SYMS_TypeNameNode`  
_L74-78_
- L75 _public member_ `struct SYMS_TypeNameNode *next;`
- L76 _public member_ `SYMS_U8 *name_ptr;`
- L77 _public member_ `SYMS_TypeChain chain;`

#### struct `SYMS_TypeNameBuckets`  
`typedef struct SYMS_TypeNameBuckets`  
_L80-82_
- L81 _public member_ `SYMS_TypeNameNode **buckets;`

#### struct `SYMS_TypeMember`  
`typedef struct SYMS_TypeMember`  
_L88-96_
- L89 _public member_ `SYMS_MemKind kind;`
- L90 _public member_ `SYMS_MemVisibility visibility;`
- L91 _public member_ `SYMS_MemFlags flags;`
- L92 _public member_ `SYMS_String8 name;`
- L93 _public member_ `SYMS_U32 off;`
- L94 _public member_ `SYMS_U32 virtual_off;`
- L95 _public member_ `struct SYMS_TypeNode *type;`

#### struct `SYMS_TypeUniqueInfo`  
`typedef struct SYMS_TypeUniqueInfo`  
_L98-101_
- L99 _public member_ `SYMS_USID usid;`
- L100 _public member_ `SYMS_SrcCoord src_coord;`

#### struct `SYMS_TypeMemberArray`  
`typedef struct SYMS_TypeMemberArray`  
_L103-106_
- L104 _public member_ `SYMS_TypeMember *mems;`
- L105 _public member_ `SYMS_U64 count;`

#### struct `SYMS_TypeNode`  
`typedef struct SYMS_TypeNode`  
_L108-151_
- L112 _public member_ `SYMS_TypeKind kind;`
- L113 _public member_ `SYMS_String8 name;`
- L114 _public member_ `SYMS_U64 byte_size;`
- L117 _public member_ `SYMS_TypeUniqueInfo *unique;` — when non-null contains the type's usid and/or source location of the type's definition
- L121 _public member_ `struct SYMS_TypeNode *direct_type;` — (in addition to interpretations of SYMS_TypeInfo 'direct_type') SYMS_TypeKind_Forward*   -> the concrete type referenced by the forward reference
- L126 _public member_ `struct SYMS_TypeNode *this_type;` — 'this_type' meaning depends on kind: SYMS_TypeKind_MemberPtr  -> the container type of the member pointer SYMS_TypeKind_Proc       -> if non-nil this is the type of an implicit 'this' in a C++ method

#### union `SYMS_TypeNode::(anonymous)`  
`union`  
_L128-150_

#### struct `SYMS_TypeNode::__anona06a0d7e010a::(anonymous)`  
`struct`  
_L136-139_
- desc: kind: SYMS_TypeKind_Bitfield

#### struct `SYMS_TypeNode::__anona06a0d7e010a::(anonymous)`  
`struct`  
_L142-145_
- desc: kind: SYMS_TypeKind_Proc

#### struct `SYMS_TypeGraph`  
`typedef struct SYMS_TypeGraph`  
_L153-175_
- L154 _public member_ `SYMS_Arena *arena;`
- L155 _public member_ `SYMS_StringCons *string_cons;`
- L156 _public member_ `SYMS_U64 address_size;`
- L157 _public member_ `SYMS_TypeContentBuckets content_buckets;`
- L158 _public member_ `SYMS_TypeUSIDBuckets usid_buckets;`
- L159 _public member_ `SYMS_TypeNameBuckets name_buckets;`
- L161 _public member_ `SYMS_TypeNode *type_void;`
- L162 _public member_ `SYMS_TypeNode *type_bool;`
- L163 _public member_ `SYMS_TypeNode *type_u8;`
- L164 _public member_ `SYMS_TypeNode *type_u16;`
- L165 _public member_ `SYMS_TypeNode *type_u32;`
- L166 _public member_ `SYMS_TypeNode *type_u64;`
- L167 _public member_ `SYMS_TypeNode *type_u128;`
- L168 _public member_ `SYMS_TypeNode *type_s8;`
- L169 _public member_ `SYMS_TypeNode *type_s16;`
- L170 _public member_ `SYMS_TypeNode *type_s32;`
- L171 _public member_ `SYMS_TypeNode *type_s64;`
- L172 _public member_ `SYMS_TypeNode *type_s128;`
- L173 _public member_ `SYMS_TypeNode *type_f32;`
- L174 _public member_ `SYMS_TypeNode *type_f64;`

#### struct `SYMS_TypeParseParams`  
`typedef struct SYMS_TypeParseParams`  
_L180-189_
- L181 _public member_ `SYMS_String8 data;`
- L182 _public member_ `SYMS_DbgAccel *dbg;`
- L183 _public member_ `SYMS_UnitSetAccel *unit_set;`
- L184 _public member_ `SYMS_UnitAccel *unit;`
- L185 _public member_ `SYMS_UnitID uid;`
- L188 _public member_ `SYMS_MapAndUnit *type_map;` — needed for PDBs to correctly resolve forward types

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_TYPE_GRAPH_H`
- L16 _typedef_ `} SYMS_TypeConsMember;`
- L22 _typedef_ `} SYMS_TypeConsMemberList;`
- L31 _typedef_ `} SYMS_TypeUSIDPlaceHolder;`
- L36 _macro_ `#define SYMS_TYPE_GRAPH_TABLE_BUCKET_COUNT 1024`
- L44 _typedef_ `} SYMS_TypeContentNode;`
- L48 _typedef_ `} SYMS_TypeContentBuckets;`
- L55 _typedef_ `} SYMS_TypeUSIDNode;`
- L60 _typedef_ `} SYMS_TypeUSIDBuckets;`
- L66 _typedef_ `} SYMS_TypeChainNode;`
- L72 _typedef_ `} SYMS_TypeChain;`
- L78 _typedef_ `} SYMS_TypeNameNode;`
- L82 _typedef_ `} SYMS_TypeNameBuckets;`
- L96 _typedef_ `} SYMS_TypeMember;`
- L101 _typedef_ `} SYMS_TypeUniqueInfo;`
- L106 _typedef_ `} SYMS_TypeMemberArray;`
- L130 _member_ `SYMS_TypeModifiers mods;` (scope `SYMS_TypeNode::__anona06a0d7e010a`) — kind: SYMS_TypeKind_Modifier
- L133 _member_ `SYMS_U64 array_count;` (scope `SYMS_TypeNode::__anona06a0d7e010a`) — kind: SYMS_TypeKind_Array
- L137 _member_ `SYMS_U32 off;` (scope `SYMS_TypeNode::__anona06a0d7e010a::__anona06a0d7e0208`)
- L138 _member_ `SYMS_U32 count;` (scope `SYMS_TypeNode::__anona06a0d7e010a::__anona06a0d7e0208`)
- L139 _member_ `} bits;` (scope `SYMS_TypeNode::__anona06a0d7e010a`)
- L143 _member_ `struct SYMS_TypeNode **params;` (scope `SYMS_TypeNode::__anona06a0d7e010a::__anona06a0d7e0308`)
- L144 _member_ `SYMS_U64 param_count;` (scope `SYMS_TypeNode::__anona06a0d7e010a::__anona06a0d7e0308`)
- L145 _member_ `} proc;` (scope `SYMS_TypeNode::__anona06a0d7e010a`)
- L149 _member_ `void *lazy_ptr;` (scope `SYMS_TypeNode::__anona06a0d7e010a`) — kind: SYMS_TypeKind_Struct, SYMS_TypeKind_Union, SYMS_TypeKind_Class, SYMS_TypeKind_Enum opaque pointer for lazy eval attachments to the type node.
- L151 _typedef_ `} SYMS_TypeNode;`
- L175 _typedef_ `} SYMS_TypeGraph;`
- L189 _typedef_ `} SYMS_TypeParseParams;`
- L194 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_TypeNode syms_type_node_nil = { SYMS_TypeKind_Null,`
- L203 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_TypeMemberArray syms_type_member_array_nil = {0};`
- L204 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_EnumMemberArray syms_type_enum_member_array_nil = {0};`
- L215 _prototype_ `void syms_type_graph_init(SYMS_TypeGraph *graph, SYMS_Arena *graph_arena, SYMS_StringCons *graph_string_cons, SYMS_U64 address_size_bytes);`
- L222 _prototype_ `SYMS_String8 syms_type_string_cons(SYMS_TypeGraph *graph, SYMS_String8 name);`
- L224 _prototype_ `SYMS_TypeNode* syms_type_from_usid(SYMS_TypeGraph *graph, SYMS_USID usid);`
- L225 _prototype_ `SYMS_TypeChain syms_type_from_name(SYMS_TypeGraph *graph, SYMS_String8 name);`
- L230 _prototype_ `SYMS_TypeMemberArray syms_type_members_from_type(SYMS_TypeGraph *graph, SYMS_TypeNode *node);`
- L231 _prototype_ `SYMS_EnumMemberArray syms_type_enum_members_from_type(SYMS_TypeGraph *graph, SYMS_TypeNode *node);`
- L234 _prototype_ `SYMS_B32 syms_type_members_are_equipped(SYMS_TypeGraph *graph, SYMS_TypeNode *node);`
- L239 _prototype_ `SYMS_TypeNode* syms_type_void(SYMS_TypeGraph *graph);`
- L241 _prototype_ `SYMS_TypeNode* syms_type_bool(SYMS_TypeGraph *graph);`
- L243 _prototype_ `SYMS_TypeNode* syms_type_u8(SYMS_TypeGraph *graph);`
- L244 _prototype_ `SYMS_TypeNode* syms_type_u16(SYMS_TypeGraph *graph);`
- L245 _prototype_ `SYMS_TypeNode* syms_type_u32(SYMS_TypeGraph *graph);`
- L246 _prototype_ `SYMS_TypeNode* syms_type_u64(SYMS_TypeGraph *graph);`
- L247 _prototype_ `SYMS_TypeNode* syms_type_u128(SYMS_TypeGraph *graph);`
- L249 _prototype_ `SYMS_TypeNode* syms_type_s8(SYMS_TypeGraph *graph);`
- L250 _prototype_ `SYMS_TypeNode* syms_type_s16(SYMS_TypeGraph *graph);`
- L251 _prototype_ `SYMS_TypeNode* syms_type_s32(SYMS_TypeGraph *graph);`
- L252 _prototype_ `SYMS_TypeNode* syms_type_s64(SYMS_TypeGraph *graph);`
- L253 _prototype_ `SYMS_TypeNode* syms_type_s128(SYMS_TypeGraph *graph);`
- L255 _prototype_ `SYMS_TypeNode* syms_type_f32(SYMS_TypeGraph *graph);`
- L256 _prototype_ `SYMS_TypeNode* syms_type_f64(SYMS_TypeGraph *graph);`
- L262 _prototype_ `SYMS_TypeNode* syms_type_cons_basic(SYMS_TypeGraph *graph, SYMS_TypeKind kind, SYMS_U64 size, SYMS_String8 name);` — - deduplicated types
- L264 _prototype_ `SYMS_TypeNode* syms_type_cons_mod(SYMS_TypeGraph *graph, SYMS_TypeNode *type, SYMS_TypeModifiers mods);`
- L265 _prototype_ `SYMS_TypeNode* syms_type_cons_ptr(SYMS_TypeGraph *graph, SYMS_TypeKind ptr_kind, SYMS_TypeNode *type);`
- L266 _prototype_ `SYMS_TypeNode* syms_type_cons_array(SYMS_TypeGraph *graph, SYMS_TypeNode *type, SYMS_U64 count);`
- L267 _prototype_ `SYMS_TypeNode* syms_type_cons_proc(SYMS_TypeGraph *graph, SYMS_TypeNode *ret_type, SYMS_TypeNode *this_type, SYMS_TypeNode **params, SYMS_U64 count);`
- L270 _prototype_ `SYMS_TypeNode* syms_type_cons_mem_ptr(SYMS_TypeGraph *graph, SYMS_TypeNode *container, SYMS_TypeNode *type);`
- L272 _prototype_ `SYMS_TypeNode* syms_type_cons_bitfield(SYMS_TypeGraph *graph, SYMS_TypeNode *underlying_type, SYMS_U32 bitoff, SYMS_U32 bitcount);`
- L276 _prototype_ `SYMS_TypeNode* syms_type_cons_record_stub(SYMS_TypeGraph *graph);` — - record types from member lists
- L277 _prototype_ `void syms_type_cons_mem_list_push(SYMS_Arena *arena, SYMS_TypeConsMemberList *list, SYMS_String8 name, SYMS_TypeNode *type);`
- L279 _prototype_ `void syms_type_cons_record_with_members(SYMS_TypeGraph *graph, SYMS_TypeNode *stub, SYMS_TypeKind kind, SYMS_String8 name, SYMS_TypeConsMemberList *list);`
- L284 _prototype_ `SYMS_TypeNode* syms_type_cons_record_defer_members(SYMS_TypeGraph *graph, SYMS_TypeKind kind, SYMS_String8 name, SYMS_U64 byte_size, SYMS_TypeUniqueInfo *unique_opt);` — - record types with defered member lists
- L290 _prototype_ `SYMS_TypeNode* syms_type_cons_enum_defer_members(SYMS_TypeGraph *graph, SYMS_String8 name, SYMS_TypeNode *underlying_type, SYMS_TypeUniqueInfo *unique_opt);` — - other UDTs
- L293 _prototype_ `SYMS_TypeNode* syms_type_cons_typedef(SYMS_TypeGraph *graph, SYMS_String8 name, SYMS_TypeNode *type, SYMS_TypeUniqueInfo *unique_opt);`
- L296 _prototype_ `SYMS_TypeNode* syms_type_cons_fwd(SYMS_TypeGraph *graph, SYMS_TypeKind kind, SYMS_String8 name, SYMS_TypeNode *type, SYMS_TypeUniqueInfo *unique_opt);`
- L301 _prototype_ `SYMS_TypeUSIDPlaceHolder syms_type_usid_place_holder_insert(SYMS_TypeGraph *graph, SYMS_USID usid);` — - usid place holders
- L302 _prototype_ `void syms_type_usid_place_holder_replace(SYMS_TypeGraph *graph, SYMS_TypeUSIDPlaceHolder *place, SYMS_TypeNode *node);`
- L307 _prototype_ `SYMS_TypeMember* syms_type_equip_mems_pre_allocate(SYMS_TypeGraph *graph, SYMS_TypeNode *node, SYMS_U64 member_count);` — - equipping record members
- L312 _prototype_ `SYMS_EnumMember* syms_type_equip_enum_mems_pre_allocate(SYMS_TypeGraph *graph, SYMS_TypeNode *node, SYMS_U64 member_count);` — - equipping enum members
- L316 _prototype_ `SYMS_TypeUniqueInfo* syms_type_unique_copy(SYMS_Arena *arena, SYMS_TypeUniqueInfo *unique_opt);` — - unique info helpers
- L317 _prototype_ `SYMS_TypeUniqueInfo syms_type_unique_from_usid_src_coord(SYMS_USID usid, SYMS_SrcCoord *src_coord);`
- L323 _prototype_ `SYMS_TypeNode* syms_type_resolved(SYMS_TypeNode *type);`
- L324 _prototype_ `SYMS_B32 syms_type_node_match(SYMS_TypeNode *l, SYMS_TypeNode *r);`
- L326 _prototype_ `SYMS_TypeNode* syms_type_resolve_enum_to_basic(SYMS_TypeGraph *graph, SYMS_TypeNode *t);`
- L328 _prototype_ `SYMS_TypeNode* syms_type_promoted_from_type_node(SYMS_TypeGraph *graph, SYMS_TypeNode *c);`
- L329 _prototype_ `SYMS_TypeNode* syms_type_auto_casted_from_type_nodes(SYMS_TypeGraph *graph, SYMS_TypeNode *l, SYMS_TypeNode *r);`
- L336 _prototype_ `SYMS_String8 syms_type_string_from_type(SYMS_Arena *arena, SYMS_TypeNode *type);`
- L338 _prototype_ `void syms_type_lhs_string_from_type(SYMS_Arena *arena, SYMS_TypeNode *type, SYMS_String8List *out);`
- L340 _prototype_ `void syms_type_rhs_string_from_type(SYMS_Arena *arena, SYMS_TypeNode *type, SYMS_String8List *out);`
- L343 _prototype_ `void syms_type_lhs_string_from_type_skip_return(SYMS_Arena *arena, SYMS_TypeNode *type, SYMS_String8List *out);`
- L347 _prototype_ `void syms_type_lhs_string_from_type__internal(SYMS_Arena *arena, SYMS_TypeNode *type, SYMS_String8List *out, SYMS_U32 prec, SYMS_B32 skip);`
- L351 _prototype_ `void syms_type_rhs_string_from_type__internal(SYMS_Arena *arena, SYMS_TypeNode *type, SYMS_String8List *out, SYMS_U32 prec);`
- L359 _prototype_ `SYMS_TypeNode* syms_type_from_dbg_sid(SYMS_TypeGraph *graph, SYMS_TypeParseParams *params, SYMS_SymbolID sid);`
- L362 _prototype_ `SYMS_TypeNode* syms_type_from_dbg_sid__rec(SYMS_TypeGraph *graph, SYMS_TypeParseParams *params, SYMS_SymbolID sid);`
- L368 _prototype_ `void syms_type_equip_members_from_dbg(SYMS_TypeGraph *graph, SYMS_TypeParseParams *params, SYMS_TypeNode *node);` — NOTE(allen): The "node" must be one that was returned by "syms_type_from_dbg_sid". The "params" used here must match the "params" used from that call (same debug data, same unit). This function has no mechanism for checking this - so it's up to the user to arrange this correctly!
- L374 _prototype_ `SYMS_U64 syms_type_content_hash(SYMS_String8 data);`
- L375 _prototype_ `SYMS_TypeNode* syms_type_from_content_buckets(SYMS_TypeContentBuckets *buckets, SYMS_String8 data);`
- L376 _prototype_ `SYMS_String8 syms_type_content_insert(SYMS_Arena *arena, SYMS_TypeContentBuckets *buckets, SYMS_String8 key, SYMS_TypeNode *type);`
- L382 _prototype_ `SYMS_U64 syms_type_usid_hash(SYMS_USID usid);`
- L383 _prototype_ `SYMS_TypeNode* syms_type_from_usid_buckets(SYMS_TypeUSIDBuckets *buckets, SYMS_USID usid);`
- L384 _prototype_ `SYMS_TypeUSIDNode* syms_type_usid_insert(SYMS_Arena *arena, SYMS_TypeUSIDBuckets *buckets, SYMS_USID key, SYMS_TypeNode *type);`
- L390 _prototype_ `SYMS_U64 syms_type_name_hash(SYMS_U8 *ptr);`
- L391 _prototype_ `SYMS_TypeChain*syms_type_chain_from_name_buckets(SYMS_TypeNameBuckets *buckets, SYMS_U8 *name_ptr);`
- L392 _prototype_ `void syms_type_name_insert(SYMS_Arena *arena, SYMS_TypeNameBuckets *buckets, SYMS_U8 *name_ptr, SYMS_TypeNode *type);`

### `Source/Runtime/SymsLib/syms/core/mach/syms_mach.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_MACH_H`
- L17 _macro_ `#define SYMS_MACH_CPU_ABI64 0x01000000`
- L18 _macro_ `#define SYMS_MACH_CPU_ABI64_MAS 0xff000000`
- L20 _macro_ `#define SYMS_MACH_CPU_SUBTYPE_MASK 0xff000000`
- L21 _macro_ `#define SYMS_MACH_CPU_SUBTYPE_LIB64 0x80000000`
- L26 _typedef_ `typedef SYMS_S32 SYMS_MachVMProt;`
- L29 _macro_ `#define SYMS_MACH_MAGIC_32 0xFEEDFACE` — - magic numbers
- L30 _macro_ `#define SYMS_MACH_CIGAM_32 0xCEFAEDFE`
- L32 _macro_ `#define SYMS_MACH_MAGIC_64 0xFEEDFACF`
- L33 _macro_ `#define SYMS_MACH_CIGAM_64 0xCFFAEDFE`
- L35 _macro_ `#define SYMS_MACH_FAT_MAGIC 0xCAFEBABE`
- L36 _macro_ `#define SYMS_MACH_FAT_CIGAM 0xBEBAFECA`
- L38 _macro_ `#define SYMS_MACH_IS_HEADER_32(x) ((x) == SYMS_MACH_MAGIC_32 || (x) == SYMS_MACH_CIGAM_32)`
- L39 _macro_ `#define SYMS_MACH_IS_HEADER_64(x) ((x) == SYMS_MACH_MAGIC_64 || (x) == SYMS_MACH_CIGAM_64)`
- L40 _macro_ `#define SYMS_MACH_HEADER_IS_SWAPPED(x) ((x) == SYMS_MACH_CIGAM_64 || (x) == SYMS_MACH_CIGAM_32)`
- L41 _macro_ `#define SYMS_MACH_IS_FAT(x) ((x) == SYMS_MACH_FAT_MAGIC || (x) == SYMS_MACH_FAT_CIGAM)`
- L42 _macro_ `#define SYMS_MACH_FAT_IS_SWAPPED(x) ((x) == SYMS_MACH_FAT_CIGAM)`
- L46 _macro_ `#define SYMS_MACH_VERSION_NIBBLE_A(x) (((x) & 0xFFFF0000) >> 16)`
- L47 _macro_ `#define SYMS_MACH_VERSION_NIBBLE_B(x) (((x) & 0x0000FF00) >> 8)`
- L48 _macro_ `#define SYMS_MACH_VERSION_NIBBLE_C(x) (((x) & 0x000000FF) >> 0)`
- L58 _macro_ `#define SYMS_MACH_NLIST_STAB(x) ((x) & 0xE0)`
- L59 _macro_ `#define SYMS_MACH_NLIST_PEXT(x) ((x) & 0x10)`
- L60 _macro_ `#define SYMS_MACH_NLIST_TYPE(x) ((x) & 0x0E)`
- L61 _macro_ `#define SYMS_MACH_NLIST_EXT(x) ((x) & 0x01)`
- L68 _prototype_ `void syms_mach_header64_from_header32(SYMS_MachHeader64 *dst, SYMS_MachHeader32 *header32);`
- L69 _prototype_ `void syms_mach_nlist64_from_nlist32(SYMS_MachNList64 *dst, SYMS_MachNList32 *nlist32);`
- L70 _prototype_ `void syms_mach_segment64_from_segment32(SYMS_MachSegmentCommand64 *dst, SYMS_MachSegmentCommand32 *seg32);`
- L71 _prototype_ `void syms_mach_section64_from_section32(SYMS_MachSection64 *dst, SYMS_MachSection32 *sect32);`

### `Source/Runtime/SymsLib/syms/core/mach/syms_mach_parser.h` (Other)


#### struct `SYMS_MachFileAccel`  
`typedef struct SYMS_MachFileAccel`  
_L9-13_
- L10 _public member_ `SYMS_FileFormat format;`
- L11 _public member_ `SYMS_B32 is_swapped;`
- L12 _public member_ `SYMS_B32 is_fat;`

#### struct `SYMS_MachBinListAccel`  
`typedef struct SYMS_MachBinListAccel`  
_L15-19_
- L16 _public member_ `SYMS_FileFormat format;`
- L17 _public member_ `SYMS_MachFatArch *fats;`
- L18 _public member_ `SYMS_U32 count;`

#### struct `SYMS_MachSegmentNode`  
`typedef struct SYMS_MachSegmentNode`  
_L21-24_
- L22 _public member_ `struct SYMS_MachSegmentNode *next;`
- L23 _public member_ `SYMS_MachSegmentCommand64 data;`

#### struct `SYMS_MachSectionNode`  
`typedef struct SYMS_MachSectionNode`  
_L26-29_
- L27 _public member_ `struct SYMS_MachSectionNode *next;`
- L28 _public member_ `SYMS_MachSection64 data;`

#### enum `(anonymous)`  
``  
_L32-37_

#### struct `SYMS_MachBinAccel`  
`typedef struct SYMS_MachBinAccel`  
_L40-63_
- L41 _public member_ `SYMS_FileFormat format;`
- L43 _public member_ `SYMS_Arch arch;`
- L45 _public member_ `SYMS_B32 is_swapped;`
- L47 _public member_ `SYMS_U32 load_command_count;`
- L48 _public member_ `SYMS_U64Range load_commands;`
- L50 _public member_ `SYMS_MachSymtabCommand symtab;`
- L52 _public member_ `SYMS_MachSegmentCommand64 *segments;`
- L53 _public member_ `SYMS_U32 segment_count;`
- L55 _public member_ `SYMS_MachSection64 *sections;`
- L56 _public member_ `SYMS_U32 section_count;`
- L58 _public member_ `SYMS_U64Range bind_ranges[SYMS_MachBindTable_COUNT];`
- L59 _public member_ `SYMS_U64Range export_range;`
- L61 _public member_ `SYMS_U32 dylib_count;`
- L62 _public member_ `struct SYMS_MachParsedDylib *dylibs;`

#### struct `SYMS_MachParsedDylib`  
`typedef struct SYMS_MachParsedDylib`  
_L68-72_
- L70 _public member_ `SYMS_MachDylib header;`
- L71 _public member_ `SYMS_U64Range name;`

#### struct `SYMS_MachDylibNode`  
`typedef struct SYMS_MachDylibNode`  
_L75-79_
- L77 _public member_ `struct SYMS_MachDylibNode *next;`
- L78 _public member_ `SYMS_MachParsedDylib data;`

#### struct `(anonymous)`  
``  
_L82-86_

#### struct `(anonymous)`  
``  
_L92-100_

#### struct `SYMS_MachBindNode`  
`typedef struct SYMS_MachBindNode`  
_L102-106_
- L104 _public member_ `SYMS_MachBind data;`
- L105 _public member_ `struct SYMS_MachBindNode *next;`

#### struct `(anonymous)`  
``  
_L109-113_

#### struct `SYMS_MachExport`  
`typedef struct SYMS_MachExport`  
_L118-135_
- L120 _public member_ `struct SYMS_MachExport **children;`
- L121 _public member_ `SYMS_U8 child_count;`
- L123 _public member_ `SYMS_B32 is_export_info;`
- L125 _public member_ `SYMS_String8 name;`
- L126 _public member_ `SYMS_U64 flags;`
- L127 _public member_ `SYMS_U64 address;`
- L130 _public member_ `SYMS_U64 dylib_ordinal;` — SYMS_MachExportSymbolFlags_REEXPORT
- L131 _public member_ `SYMS_String8 import_name;`
- L134 _public member_ `SYMS_U64 resolver;` — SYMS_MachExportSymbolFlags_STUB_AND_RESOLVER

#### struct `SYMS_MachExportNode`  
`typedef struct SYMS_MachExportNode`  
_L137-141_
- L139 _public member_ `struct SYMS_MachExportNode *next;`
- L140 _public member_ `SYMS_MachExport data;`

#### struct `SYMS_MachExportFrame`  
`typedef struct SYMS_MachExportFrame`  
_L143-148_
- L145 _public member_ `struct SYMS_MachExportFrame *next;`
- L146 _public member_ `SYMS_U8 child_idx;`
- L147 _public member_ `SYMS_MachExport *node;`

#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_MACH_PARSER_H`
- L13 _typedef_ `} SYMS_MachFileAccel;`
- L19 _typedef_ `} SYMS_MachBinListAccel;`
- L24 _typedef_ `} SYMS_MachSegmentNode;`
- L29 _typedef_ `} SYMS_MachSectionNode;`
- L33 _enumerator_ `SYMS_MachBindTable_REGULAR` (scope `__anon3901d01c0103`)
- L34 _enumerator_ `SYMS_MachBindTable_LAZY` (scope `__anon3901d01c0103`)
- L35 _enumerator_ `SYMS_MachBindTable_WEAK` (scope `__anon3901d01c0103`)
- L36 _enumerator_ `SYMS_MachBindTable_COUNT` (scope `__anon3901d01c0103`)
- L38 _typedef_ `typedef SYMS_U32 SYMS_MachBindTable;`
- L63 _typedef_ `} SYMS_MachBinAccel;`
- L72 _typedef_ `} SYMS_MachParsedDylib;`
- L79 _typedef_ `} SYMS_MachDylibNode;`
- L83 _member_ `SYMS_MachDylibNode *first;` (scope `__anon3901d01c0208`)
- L84 _member_ `SYMS_MachDylibNode *last;` (scope `__anon3901d01c0208`)
- L85 _member_ `SYMS_U32 count;` (scope `__anon3901d01c0208`)
- L86 _typedef_ `} SYMS_MachDylibList;`
- L93 _member_ `SYMS_U32 segment;` (scope `__anon3901d01c0308`)
- L94 _member_ `SYMS_U64 segment_offset;` (scope `__anon3901d01c0308`)
- L95 _member_ `SYMS_U64 dylib;` (scope `__anon3901d01c0308`)
- L96 _member_ `SYMS_String8 symbol_name;` (scope `__anon3901d01c0308`)
- L97 _member_ `SYMS_U8 flags;` (scope `__anon3901d01c0308`)
- L98 _member_ `SYMS_MachBindType type;` (scope `__anon3901d01c0308`)
- L99 _member_ `SYMS_S64 addend;` (scope `__anon3901d01c0308`)
- L100 _typedef_ `} SYMS_MachBind;`
- L106 _typedef_ `} SYMS_MachBindNode;`
- L110 _member_ `SYMS_MachBindNode *first;` (scope `__anon3901d01c0408`)
- L111 _member_ `SYMS_MachBindNode *last;` (scope `__anon3901d01c0408`)
- L112 _member_ `SYMS_U32 count;` (scope `__anon3901d01c0408`)
- L113 _typedef_ `} SYMS_MachBindList;`
- L135 _typedef_ `} SYMS_MachExport;`
- L141 _typedef_ `} SYMS_MachExportNode;`
- L148 _typedef_ `} SYMS_MachExportFrame;`
- L155 _prototype_ `SYMS_MachBinAccel* syms_mach_bin_from_base_range(SYMS_Arena *arena, void *base, SYMS_U64Range range);` — accelerators mach specific
- L158 _prototype_ `SYMS_MachFileAccel* syms_mach_file_accel_from_data(SYMS_Arena *arena, SYMS_String8 data);` — main api
- L159 _prototype_ `SYMS_B32 syms_mach_file_is_bin(SYMS_MachFileAccel *file);`
- L160 _prototype_ `SYMS_MachBinAccel* syms_mach_bin_accel_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_MachFileAccel *file);`
- L162 _prototype_ `SYMS_B32 syms_mach_file_is_bin_list(SYMS_MachFileAccel *file_accel);`
- L163 _prototype_ `SYMS_MachBinListAccel* syms_mach_bin_list_accel_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_MachFileAccel *file);`
- L167 _prototype_ `SYMS_Arch syms_mach_arch_from_bin(SYMS_MachBinAccel *bin);` — arch
- L170 _prototype_ `SYMS_BinInfoArray syms_mach_bin_info_array_from_bin_list(SYMS_Arena *arena, SYMS_MachBinListAccel *bin_list);` — bin list
- L172 _prototype_ `SYMS_MachBinAccel* syms_mach_bin_accel_from_bin_list_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_MachBinListAccel *bin_list, SYMS_U64 n);`
- L177 _prototype_ `SYMS_SecInfoArray syms_mach_sec_info_array_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_MachBinAccel *bin);` — binary secs
- L180 _prototype_ `SYMS_U64 syms_mach_default_vbase_from_bin(SYMS_MachBinAccel *bin);`
- L183 _prototype_ `void syms_mach_dylib_list_push(SYMS_Arena *arena, SYMS_MachDylibList *list, SYMS_MachDylib *dylib, SYMS_U64Range name);` — dylib
- L186 _prototype_ `SYMS_MachBindList syms_mach_binds_from_base_range(SYMS_Arena *arena, void *base, SYMS_U64Range range, SYMS_U32 address_size, SYMS_MachBindTable bind_type);` — binds
- L187 _prototype_ `SYMS_ImportArray syms_mach_imports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_MachBinAccel *bin);`
- L190 _prototype_ `SYMS_MachExport * syms_build_mach_export_trie(SYMS_Arena *arena, void *base, SYMS_U64Range range);` — exports
- L191 _prototype_ `SYMS_ExportArray syms_mach_exports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_MachBinAccel *bin);`

### `Source/Runtime/SymsLib/syms/core/pdb/syms_cv.h` (Other)


#### struct `SYMS_CvChecksum`  
`typedef struct SYMS_CvChecksum`  
_L43-47_
- L44 _public member_ `SYMS_U32 name_off;`
- L45 _public member_ `SYMS_U8 len;`
- L46 _public member_ `SYMS_CvChecksumKind kind;`

#### enum `(anonymous)`  
`enum`  
_L52-999_

#### struct `SYMS_CvSymbolHelper`  
`typedef struct SYMS_CvSymbolHelper`  
_L1006-1009_
- desc: TODO(allen): rename SYMS_CvElementHeader SYMS_CvSubSecKind_SYMBOLS
- L1007 _public member_ `SYMS_U16 size;`
- L1008 _public member_ `SYMS_U16 type;`

#### struct `SYMS_CvMethod`  
`typedef struct SYMS_CvMethod`  
_L1015-1020_
- L1016 _public member_ `SYMS_CvFieldAttribs attribs;`
- L1017 _public member_ `SYMS_U16 pad;`
- L1018 _public member_ `SYMS_CvTypeId itype;`

#### enum `(anonymous)`  
`enum`  
_L1030-1032_

#### struct `SYMS_CvSubSecLinesHeader`  
`typedef struct SYMS_CvSubSecLinesHeader`  
_L1035-1040_
- desc: SYMS_CvSubSecKind_LINES
- L1036 _public member_ `SYMS_U32 sec_off;`
- L1037 _public member_ `SYMS_CvSectionIndex sec;`
- L1038 _public member_ `SYMS_CvSubSecLinesFlags flags;`
- L1039 _public member_ `SYMS_U32 len;`

#### struct `SYMS_CvFile`  
`typedef struct SYMS_CvFile`  
_L1042-1048_
- L1043 _public member_ `SYMS_U32 file_off;`
- L1044 _public member_ `SYMS_U32 num_lines;`
- L1045 _public member_ `SYMS_U32 block_size;`

#### enum `(anonymous)`  
`enum`  
_L1051-1057_

#### struct `SYMS_CvLine`  
`typedef struct SYMS_CvLine`  
_L1059-1062_
- L1060 _public member_ `SYMS_U32 off;`
- L1061 _public member_ `SYMS_CvLineFlags flags;`

#### struct `SYMS_CvColumn`  
`typedef struct SYMS_CvColumn`  
_L1064-1067_
- L1065 _public member_ `SYMS_U16 start;`
- L1066 _public member_ `SYMS_U16 end;`

#### enum `(anonymous)`  
`enum`  
_L1072-1076_

#### struct `SYMS_CvFrameData`  
`typedef struct SYMS_CvFrameData`  
_L1079-1089_
- L1080 _public member_ `SYMS_U32 start_voff;`
- L1081 _public member_ `SYMS_U32 code_size;`
- L1082 _public member_ `SYMS_U32 local_size;`
- L1083 _public member_ `SYMS_U32 params_size;`
- L1084 _public member_ `SYMS_U32 max_stack_size;`
- L1085 _public member_ `SYMS_U32 frame_func;`
- L1086 _public member_ `SYMS_U16 prolog_size;`
- L1087 _public member_ `SYMS_U16 saved_reg_size;`
- L1088 _public member_ `SYMS_CvFrameDataFlags flags;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_CV_H`
- L10 _typedef_ `typedef SYMS_U32 SYMS_CvTypeIndex;`
- L12 _typedef_ `typedef SYMS_U32 SYMS_CvTypeId;` — "TPI"
- L14 _typedef_ `typedef SYMS_U32 SYMS_CvItemId;` — "IPI" leaf kinds: FUNC_ID,MFUNC_ID,BUILDINFO,SUBSTR_LIST,STRING_ID
- L16 _variable_ `SYMS_GLOBAL SYMS_CvTypeId syms_cv_type_id_variadic = SYMS_U32_MAX;`
- L18 _typedef_ `typedef SYMS_U16 SYMS_CvModIndex;`
- L19 _typedef_ `typedef SYMS_U16 SYMS_CvSectionIndex;`
- L24 _typedef_ `typedef SYMS_U16 SYMS_CvReg;`
- L34 _macro_ `#define SYMS_CvBasicTypeFromTypeId(x) (((x) )&0xff)`
- L35 _macro_ `#define SYMS_CvBasicPointerKindFromTypeId(x) (((x)>>8)&0xff)`
- L47 _typedef_ `} SYMS_CvChecksum;`
- L53 _enumerator_ `SYMS_CvReg_NONE = 0` (scope `__anon2117d08d0103`)
- L58 _enumerator_ `SYMS_CvReg_X86_AL = 1` (scope `__anon2117d08d0103`)
- L59 _enumerator_ `SYMS_CvReg_X86_CL = 2` (scope `__anon2117d08d0103`)
- L60 _enumerator_ `SYMS_CvReg_X86_DL = 3` (scope `__anon2117d08d0103`)
- L61 _enumerator_ `SYMS_CvReg_X86_BL = 4` (scope `__anon2117d08d0103`)
- L62 _enumerator_ `SYMS_CvReg_X86_AH = 5` (scope `__anon2117d08d0103`)
- L63 _enumerator_ `SYMS_CvReg_X86_CH = 6` (scope `__anon2117d08d0103`)
- L64 _enumerator_ `SYMS_CvReg_X86_DH = 7` (scope `__anon2117d08d0103`)
- L65 _enumerator_ `SYMS_CvReg_X86_BH = 8` (scope `__anon2117d08d0103`)
- L66 _enumerator_ `SYMS_CvReg_X86_AX = 9` (scope `__anon2117d08d0103`)
- L67 _enumerator_ `SYMS_CvReg_X86_CX = 10` (scope `__anon2117d08d0103`)
- L68 _enumerator_ `SYMS_CvReg_X86_DX = 11` (scope `__anon2117d08d0103`)
- L69 _enumerator_ `SYMS_CvReg_X86_BX = 12` (scope `__anon2117d08d0103`)
- L70 _enumerator_ `SYMS_CvReg_X86_SP = 13` (scope `__anon2117d08d0103`)
- L71 _enumerator_ `SYMS_CvReg_X86_BP = 14` (scope `__anon2117d08d0103`)
- L72 _enumerator_ `SYMS_CvReg_X86_SI = 15` (scope `__anon2117d08d0103`)
- L73 _enumerator_ `SYMS_CvReg_X86_DI = 16` (scope `__anon2117d08d0103`)
- L74 _enumerator_ `SYMS_CvReg_X86_EAX = 17` (scope `__anon2117d08d0103`)
- L75 _enumerator_ `SYMS_CvReg_X86_ECX = 18` (scope `__anon2117d08d0103`)
- L76 _enumerator_ `SYMS_CvReg_X86_EDX = 19` (scope `__anon2117d08d0103`)
- L77 _enumerator_ `SYMS_CvReg_X86_EBX = 20` (scope `__anon2117d08d0103`)
- L78 _enumerator_ `SYMS_CvReg_X86_ESP = 21` (scope `__anon2117d08d0103`)
- L79 _enumerator_ `SYMS_CvReg_X86_EBP = 22` (scope `__anon2117d08d0103`)
- L80 _enumerator_ `SYMS_CvReg_X86_ESI = 23` (scope `__anon2117d08d0103`)
- L81 _enumerator_ `SYMS_CvReg_X86_EDI = 24` (scope `__anon2117d08d0103`)
- L82 _enumerator_ `SYMS_CvReg_X86_ES = 25` (scope `__anon2117d08d0103`)
- L83 _enumerator_ `SYMS_CvReg_X86_CS = 26` (scope `__anon2117d08d0103`)
- L84 _enumerator_ `SYMS_CvReg_X86_SS = 27` (scope `__anon2117d08d0103`)
- L85 _enumerator_ `SYMS_CvReg_X86_DS = 28` (scope `__anon2117d08d0103`)
- L86 _enumerator_ `SYMS_CvReg_X86_FS = 29` (scope `__anon2117d08d0103`)
- L87 _enumerator_ `SYMS_CvReg_X86_GS = 30` (scope `__anon2117d08d0103`)
- L88 _enumerator_ `SYMS_CvReg_X86_IP = 31` (scope `__anon2117d08d0103`)
- L89 _enumerator_ `SYMS_CvReg_X86_FLAGS = 32` (scope `__anon2117d08d0103`)
- L90 _enumerator_ `SYMS_CvReg_X86_EIP = 33` (scope `__anon2117d08d0103`)
- L91 _enumerator_ `SYMS_CvReg_X86_EFLAGS = 34` (scope `__anon2117d08d0103`)
- L93 _enumerator_ `SYMS_CvReg_X86_MM0 = 146` (scope `__anon2117d08d0103`)
- L94 _enumerator_ `SYMS_CvReg_X86_MM1 = 147` (scope `__anon2117d08d0103`)
- L95 _enumerator_ `SYMS_CvReg_X86_MM2 = 148` (scope `__anon2117d08d0103`)
- L96 _enumerator_ `SYMS_CvReg_X86_MM3 = 149` (scope `__anon2117d08d0103`)
- L97 _enumerator_ `SYMS_CvReg_X86_MM4 = 150` (scope `__anon2117d08d0103`)
- L98 _enumerator_ `SYMS_CvReg_X86_MM5 = 151` (scope `__anon2117d08d0103`)
- L99 _enumerator_ `SYMS_CvReg_X86_MM6 = 152` (scope `__anon2117d08d0103`)
- L100 _enumerator_ `SYMS_CvReg_X86_MM7 = 153` (scope `__anon2117d08d0103`)
- L101 _enumerator_ `SYMS_CvReg_X86_XMM0 = 154` (scope `__anon2117d08d0103`)
- L102 _enumerator_ `SYMS_CvReg_X86_XMM1 = 155` (scope `__anon2117d08d0103`)
- L103 _enumerator_ `SYMS_CvReg_X86_XMM2 = 156` (scope `__anon2117d08d0103`)
- L104 _enumerator_ `SYMS_CvReg_X86_XMM3 = 157` (scope `__anon2117d08d0103`)
- L105 _enumerator_ `SYMS_CvReg_X86_XMM4 = 158` (scope `__anon2117d08d0103`)
- L106 _enumerator_ `SYMS_CvReg_X86_XMM5 = 159` (scope `__anon2117d08d0103`)
- L107 _enumerator_ `SYMS_CvReg_X86_XMM6 = 160` (scope `__anon2117d08d0103`)
- L108 _enumerator_ `SYMS_CvReg_X86_XMM7 = 161` (scope `__anon2117d08d0103`)
- L110 _enumerator_ `SYMS_CvReg_X86_XMM00 = 162` (scope `__anon2117d08d0103`)
- L111 _enumerator_ `SYMS_CvReg_X86_XMM01 = 163` (scope `__anon2117d08d0103`)
- L112 _enumerator_ `SYMS_CvReg_X86_XMM02 = 164` (scope `__anon2117d08d0103`)
- L113 _enumerator_ `SYMS_CvReg_X86_XMM03 = 165` (scope `__anon2117d08d0103`)
- L114 _enumerator_ `SYMS_CvReg_X86_XMM10 = 166` (scope `__anon2117d08d0103`)
- L115 _enumerator_ `SYMS_CvReg_X86_XMM11 = 167` (scope `__anon2117d08d0103`)
- L116 _enumerator_ `SYMS_CvReg_X86_XMM12 = 168` (scope `__anon2117d08d0103`)
- L117 _enumerator_ `SYMS_CvReg_X86_XMM13 = 169` (scope `__anon2117d08d0103`)
- L118 _enumerator_ `SYMS_CvReg_X86_XMM20 = 170` (scope `__anon2117d08d0103`)
- L119 _enumerator_ `SYMS_CvReg_X86_XMM21 = 171` (scope `__anon2117d08d0103`)
- L120 _enumerator_ `SYMS_CvReg_X86_XMM22 = 172` (scope `__anon2117d08d0103`)
- L121 _enumerator_ `SYMS_CvReg_X86_XMM23 = 173` (scope `__anon2117d08d0103`)
- L122 _enumerator_ `SYMS_CvReg_X86_XMM30 = 174` (scope `__anon2117d08d0103`)
- L123 _enumerator_ `SYMS_CvReg_X86_XMM31 = 175` (scope `__anon2117d08d0103`)
- L124 _enumerator_ `SYMS_CvReg_X86_XMM32 = 176` (scope `__anon2117d08d0103`)
- L125 _enumerator_ `SYMS_CvReg_X86_XMM33 = 177` (scope `__anon2117d08d0103`)
- L126 _enumerator_ `SYMS_CvReg_X86_XMM40 = 178` (scope `__anon2117d08d0103`)
- L127 _enumerator_ `SYMS_CvReg_X86_XMM41 = 179` (scope `__anon2117d08d0103`)
- L128 _enumerator_ `SYMS_CvReg_X86_XMM42 = 180` (scope `__anon2117d08d0103`)
- L129 _enumerator_ `SYMS_CvReg_X86_XMM43 = 181` (scope `__anon2117d08d0103`)
- L130 _enumerator_ `SYMS_CvReg_X86_XMM50 = 182` (scope `__anon2117d08d0103`)
- L131 _enumerator_ `SYMS_CvReg_X86_XMM51 = 183` (scope `__anon2117d08d0103`)
- L132 _enumerator_ `SYMS_CvReg_X86_XMM52 = 184` (scope `__anon2117d08d0103`)
- L133 _enumerator_ `SYMS_CvReg_X86_XMM53 = 185` (scope `__anon2117d08d0103`)
- L134 _enumerator_ `SYMS_CvReg_X86_XMM60 = 186` (scope `__anon2117d08d0103`)
- L135 _enumerator_ `SYMS_CvReg_X86_XMM61 = 187` (scope `__anon2117d08d0103`)
- L136 _enumerator_ `SYMS_CvReg_X86_XMM62 = 188` (scope `__anon2117d08d0103`)
- L137 _enumerator_ `SYMS_CvReg_X86_XMM63 = 189` (scope `__anon2117d08d0103`)
- L138 _enumerator_ `SYMS_CvReg_X86_XMM70 = 190` (scope `__anon2117d08d0103`)
- L139 _enumerator_ `SYMS_CvReg_X86_XMM71 = 191` (scope `__anon2117d08d0103`)
- L140 _enumerator_ `SYMS_CvReg_X86_XMM72 = 192` (scope `__anon2117d08d0103`)
- L141 _enumerator_ `SYMS_CvReg_X86_XMM73 = 193` (scope `__anon2117d08d0103`)
- L143 _enumerator_ `SYMS_CvReg_X86_XMM0L = 194` (scope `__anon2117d08d0103`)
- L144 _enumerator_ `SYMS_CvReg_X86_XMM1L = 195` (scope `__anon2117d08d0103`)
- L145 _enumerator_ `SYMS_CvReg_X86_XMM2L = 196` (scope `__anon2117d08d0103`)
- L146 _enumerator_ `SYMS_CvReg_X86_XMM3L = 197` (scope `__anon2117d08d0103`)
- L147 _enumerator_ `SYMS_CvReg_X86_XMM4L = 198` (scope `__anon2117d08d0103`)
- L148 _enumerator_ `SYMS_CvReg_X86_XMM5L = 199` (scope `__anon2117d08d0103`)
- L149 _enumerator_ `SYMS_CvReg_X86_XMM6L = 200` (scope `__anon2117d08d0103`)
- L150 _enumerator_ `SYMS_CvReg_X86_XMM7L = 201` (scope `__anon2117d08d0103`)
- L151 _enumerator_ `SYMS_CvReg_X86_XMM0H = 202` (scope `__anon2117d08d0103`)
- L152 _enumerator_ `SYMS_CvReg_X86_XMM1H = 203` (scope `__anon2117d08d0103`)
- L153 _enumerator_ `SYMS_CvReg_X86_XMM2H = 204` (scope `__anon2117d08d0103`)
- L154 _enumerator_ `SYMS_CvReg_X86_XMM3H = 205` (scope `__anon2117d08d0103`)
- L155 _enumerator_ `SYMS_CvReg_X86_XMM4H = 206` (scope `__anon2117d08d0103`)
- L156 _enumerator_ `SYMS_CvReg_X86_XMM5H = 207` (scope `__anon2117d08d0103`)
- L157 _enumerator_ `SYMS_CvReg_X86_XMM6H = 208` (scope `__anon2117d08d0103`)
- L158 _enumerator_ `SYMS_CvReg_X86_XMM7H = 209` (scope `__anon2117d08d0103`)
- L162 _enumerator_ `SYMS_CvReg_X86_YMM0 = 252` (scope `__anon2117d08d0103`)
- L163 _enumerator_ `SYMS_CvReg_X86_YMM1 = 253` (scope `__anon2117d08d0103`)
- L164 _enumerator_ `SYMS_CvReg_X86_YMM2 = 254` (scope `__anon2117d08d0103`)
- L165 _enumerator_ `SYMS_CvReg_X86_YMM3 = 255` (scope `__anon2117d08d0103`)
- L166 _enumerator_ `SYMS_CvReg_X86_YMM4 = 256` (scope `__anon2117d08d0103`)
- L167 _enumerator_ `SYMS_CvReg_X86_YMM5 = 257` (scope `__anon2117d08d0103`)
- L168 _enumerator_ `SYMS_CvReg_X86_YMM6 = 258` (scope `__anon2117d08d0103`)
- L169 _enumerator_ `SYMS_CvReg_X86_YMM7 = 259` (scope `__anon2117d08d0103`)
- L170 _enumerator_ `SYMS_CvReg_X86_YMM0H = 260` (scope `__anon2117d08d0103`)
- L171 _enumerator_ `SYMS_CvReg_X86_YMM1H = 261` (scope `__anon2117d08d0103`)
- L172 _enumerator_ `SYMS_CvReg_X86_YMM2H = 262` (scope `__anon2117d08d0103`)
- L173 _enumerator_ `SYMS_CvReg_X86_YMM3H = 263` (scope `__anon2117d08d0103`)
- L174 _enumerator_ `SYMS_CvReg_X86_YMM4H = 264` (scope `__anon2117d08d0103`)
- L175 _enumerator_ `SYMS_CvReg_X86_YMM5H = 265` (scope `__anon2117d08d0103`)
- L176 _enumerator_ `SYMS_CvReg_X86_YMM6H = 266` (scope `__anon2117d08d0103`)
- L177 _enumerator_ `SYMS_CvReg_X86_YMM7H = 267` (scope `__anon2117d08d0103`)
- L181 _enumerator_ `SYMS_CvReg_X86_YMM0I0 = 268` (scope `__anon2117d08d0103`)
- L182 _enumerator_ `SYMS_CvReg_X86_YMM0I1 = 269` (scope `__anon2117d08d0103`)
- L183 _enumerator_ `SYMS_CvReg_X86_YMM0I2 = 270` (scope `__anon2117d08d0103`)
- L184 _enumerator_ `SYMS_CvReg_X86_YMM0I3 = 271` (scope `__anon2117d08d0103`)
- L185 _enumerator_ `SYMS_CvReg_X86_YMM1I0 = 272` (scope `__anon2117d08d0103`)
- L186 _enumerator_ `SYMS_CvReg_X86_YMM1I1 = 273` (scope `__anon2117d08d0103`)
- L187 _enumerator_ `SYMS_CvReg_X86_YMM1I2 = 274` (scope `__anon2117d08d0103`)
- L188 _enumerator_ `SYMS_CvReg_X86_YMM1I3 = 275` (scope `__anon2117d08d0103`)
- L189 _enumerator_ `SYMS_CvReg_X86_YMM2I0 = 276` (scope `__anon2117d08d0103`)
- L190 _enumerator_ `SYMS_CvReg_X86_YMM2I1 = 277` (scope `__anon2117d08d0103`)
- L191 _enumerator_ `SYMS_CvReg_X86_YMM2I2 = 278` (scope `__anon2117d08d0103`)
- L192 _enumerator_ `SYMS_CvReg_X86_YMM2I3 = 279` (scope `__anon2117d08d0103`)
- L193 _enumerator_ `SYMS_CvReg_X86_YMM3I0 = 280` (scope `__anon2117d08d0103`)
- L194 _enumerator_ `SYMS_CvReg_X86_YMM3I1 = 281` (scope `__anon2117d08d0103`)
- L195 _enumerator_ `SYMS_CvReg_X86_YMM3I2 = 282` (scope `__anon2117d08d0103`)
- L196 _enumerator_ `SYMS_CvReg_X86_YMM3I3 = 283` (scope `__anon2117d08d0103`)
- L197 _enumerator_ `SYMS_CvReg_X86_YMM4I0 = 284` (scope `__anon2117d08d0103`)
- L198 _enumerator_ `SYMS_CvReg_X86_YMM4I1 = 285` (scope `__anon2117d08d0103`)
- L199 _enumerator_ `SYMS_CvReg_X86_YMM4I2 = 286` (scope `__anon2117d08d0103`)
- L200 _enumerator_ `SYMS_CvReg_X86_YMM4I3 = 287` (scope `__anon2117d08d0103`)
- L201 _enumerator_ `SYMS_CvReg_X86_YMM5I0 = 288` (scope `__anon2117d08d0103`)
- L202 _enumerator_ `SYMS_CvReg_X86_YMM5I1 = 289` (scope `__anon2117d08d0103`)
- L203 _enumerator_ `SYMS_CvReg_X86_YMM5I2 = 290` (scope `__anon2117d08d0103`)
- L204 _enumerator_ `SYMS_CvReg_X86_YMM5I3 = 291` (scope `__anon2117d08d0103`)
- L205 _enumerator_ `SYMS_CvReg_X86_YMM6I0 = 292` (scope `__anon2117d08d0103`)
- L206 _enumerator_ `SYMS_CvReg_X86_YMM6I1 = 293` (scope `__anon2117d08d0103`)
- L207 _enumerator_ `SYMS_CvReg_X86_YMM6I2 = 294` (scope `__anon2117d08d0103`)
- L208 _enumerator_ `SYMS_CvReg_X86_YMM6I3 = 295` (scope `__anon2117d08d0103`)
- L209 _enumerator_ `SYMS_CvReg_X86_YMM7I0 = 296` (scope `__anon2117d08d0103`)
- L210 _enumerator_ `SYMS_CvReg_X86_YMM7I1 = 297` (scope `__anon2117d08d0103`)
- L211 _enumerator_ `SYMS_CvReg_X86_YMM7I2 = 298` (scope `__anon2117d08d0103`)
- L212 _enumerator_ `SYMS_CvReg_X86_YMM7I3 = 299` (scope `__anon2117d08d0103`)
- L216 _enumerator_ `SYMS_CvReg_X86_YMM0F0 = 300` (scope `__anon2117d08d0103`)
- L217 _enumerator_ `SYMS_CvReg_X86_YMM0F1 = 301` (scope `__anon2117d08d0103`)
- L218 _enumerator_ `SYMS_CvReg_X86_YMM0F2 = 302` (scope `__anon2117d08d0103`)
- L219 _enumerator_ `SYMS_CvReg_X86_YMM0F3 = 303` (scope `__anon2117d08d0103`)
- L220 _enumerator_ `SYMS_CvReg_X86_YMM0F4 = 304` (scope `__anon2117d08d0103`)
- L221 _enumerator_ `SYMS_CvReg_X86_YMM0F5 = 305` (scope `__anon2117d08d0103`)
- L222 _enumerator_ `SYMS_CvReg_X86_YMM0F6 = 306` (scope `__anon2117d08d0103`)
- L223 _enumerator_ `SYMS_CvReg_X86_YMM0F7 = 307` (scope `__anon2117d08d0103`)
- L224 _enumerator_ `SYMS_CvReg_X86_YMM1F0 = 308` (scope `__anon2117d08d0103`)
- L225 _enumerator_ `SYMS_CvReg_X86_YMM1F1 = 309` (scope `__anon2117d08d0103`)
- L226 _enumerator_ `SYMS_CvReg_X86_YMM1F2 = 310` (scope `__anon2117d08d0103`)
- L227 _enumerator_ `SYMS_CvReg_X86_YMM1F3 = 311` (scope `__anon2117d08d0103`)
- L228 _enumerator_ `SYMS_CvReg_X86_YMM1F4 = 312` (scope `__anon2117d08d0103`)
- L229 _enumerator_ `SYMS_CvReg_X86_YMM1F5 = 313` (scope `__anon2117d08d0103`)
- L230 _enumerator_ `SYMS_CvReg_X86_YMM1F6 = 314` (scope `__anon2117d08d0103`)
- L231 _enumerator_ `SYMS_CvReg_X86_YMM1F7 = 315` (scope `__anon2117d08d0103`)
- L232 _enumerator_ `SYMS_CvReg_X86_YMM2F0 = 316` (scope `__anon2117d08d0103`)
- L233 _enumerator_ `SYMS_CvReg_X86_YMM2F1 = 317` (scope `__anon2117d08d0103`)
- L234 _enumerator_ `SYMS_CvReg_X86_YMM2F2 = 318` (scope `__anon2117d08d0103`)
- L235 _enumerator_ `SYMS_CvReg_X86_YMM2F3 = 319` (scope `__anon2117d08d0103`)
- L236 _enumerator_ `SYMS_CvReg_X86_YMM2F4 = 320` (scope `__anon2117d08d0103`)
- L237 _enumerator_ `SYMS_CvReg_X86_YMM2F5 = 321` (scope `__anon2117d08d0103`)
- L238 _enumerator_ `SYMS_CvReg_X86_YMM2F6 = 322` (scope `__anon2117d08d0103`)
- L239 _enumerator_ `SYMS_CvReg_X86_YMM2F7 = 323` (scope `__anon2117d08d0103`)
- L240 _enumerator_ `SYMS_CvReg_X86_YMM3F0 = 324` (scope `__anon2117d08d0103`)
- L241 _enumerator_ `SYMS_CvReg_X86_YMM3F1 = 325` (scope `__anon2117d08d0103`)
- L242 _enumerator_ `SYMS_CvReg_X86_YMM3F2 = 326` (scope `__anon2117d08d0103`)
- L243 _enumerator_ `SYMS_CvReg_X86_YMM3F3 = 327` (scope `__anon2117d08d0103`)
- L244 _enumerator_ `SYMS_CvReg_X86_YMM3F4 = 328` (scope `__anon2117d08d0103`)
- L245 _enumerator_ `SYMS_CvReg_X86_YMM3F5 = 329` (scope `__anon2117d08d0103`)
- L246 _enumerator_ `SYMS_CvReg_X86_YMM3F6 = 330` (scope `__anon2117d08d0103`)
- L247 _enumerator_ `SYMS_CvReg_X86_YMM3F7 = 331` (scope `__anon2117d08d0103`)
- L248 _enumerator_ `SYMS_CvReg_X86_YMM4F0 = 332` (scope `__anon2117d08d0103`)
- L249 _enumerator_ `SYMS_CvReg_X86_YMM4F1 = 333` (scope `__anon2117d08d0103`)
- L250 _enumerator_ `SYMS_CvReg_X86_YMM4F2 = 334` (scope `__anon2117d08d0103`)
- L251 _enumerator_ `SYMS_CvReg_X86_YMM4F3 = 335` (scope `__anon2117d08d0103`)
- L252 _enumerator_ `SYMS_CvReg_X86_YMM4F4 = 336` (scope `__anon2117d08d0103`)
- L253 _enumerator_ `SYMS_CvReg_X86_YMM4F5 = 337` (scope `__anon2117d08d0103`)
- L254 _enumerator_ `SYMS_CvReg_X86_YMM4F6 = 338` (scope `__anon2117d08d0103`)
- L255 _enumerator_ `SYMS_CvReg_X86_YMM4F7 = 339` (scope `__anon2117d08d0103`)
- L256 _enumerator_ `SYMS_CvReg_X86_YMM5F0 = 340` (scope `__anon2117d08d0103`)
- L257 _enumerator_ `SYMS_CvReg_X86_YMM5F1 = 341` (scope `__anon2117d08d0103`)
- L258 _enumerator_ `SYMS_CvReg_X86_YMM5F2 = 342` (scope `__anon2117d08d0103`)
- L259 _enumerator_ `SYMS_CvReg_X86_YMM5F3 = 343` (scope `__anon2117d08d0103`)
- L260 _enumerator_ `SYMS_CvReg_X86_YMM5F4 = 344` (scope `__anon2117d08d0103`)
- L261 _enumerator_ `SYMS_CvReg_X86_YMM5F5 = 345` (scope `__anon2117d08d0103`)
- L262 _enumerator_ `SYMS_CvReg_X86_YMM5F6 = 346` (scope `__anon2117d08d0103`)
- L263 _enumerator_ `SYMS_CvReg_X86_YMM5F7 = 347` (scope `__anon2117d08d0103`)
- L264 _enumerator_ `SYMS_CvReg_X86_YMM6F0 = 348` (scope `__anon2117d08d0103`)
- L265 _enumerator_ `SYMS_CvReg_X86_YMM6F1 = 349` (scope `__anon2117d08d0103`)
- L266 _enumerator_ `SYMS_CvReg_X86_YMM6F2 = 350` (scope `__anon2117d08d0103`)
- L267 _enumerator_ `SYMS_CvReg_X86_YMM6F3 = 351` (scope `__anon2117d08d0103`)
- L268 _enumerator_ `SYMS_CvReg_X86_YMM6F4 = 352` (scope `__anon2117d08d0103`)
- L269 _enumerator_ `SYMS_CvReg_X86_YMM6F5 = 353` (scope `__anon2117d08d0103`)
- L270 _enumerator_ `SYMS_CvReg_X86_YMM6F6 = 354` (scope `__anon2117d08d0103`)
- L271 _enumerator_ `SYMS_CvReg_X86_YMM6F7 = 355` (scope `__anon2117d08d0103`)
- L272 _enumerator_ `SYMS_CvReg_X86_YMM7F0 = 356` (scope `__anon2117d08d0103`)
- L273 _enumerator_ `SYMS_CvReg_X86_YMM7F1 = 357` (scope `__anon2117d08d0103`)
- L274 _enumerator_ `SYMS_CvReg_X86_YMM7F2 = 358` (scope `__anon2117d08d0103`)
- L275 _enumerator_ `SYMS_CvReg_X86_YMM7F3 = 359` (scope `__anon2117d08d0103`)
- L276 _enumerator_ `SYMS_CvReg_X86_YMM7F4 = 360` (scope `__anon2117d08d0103`)
- L277 _enumerator_ `SYMS_CvReg_X86_YMM7F5 = 361` (scope `__anon2117d08d0103`)
- L278 _enumerator_ `SYMS_CvReg_X86_YMM7F6 = 362` (scope `__anon2117d08d0103`)
- L279 _enumerator_ `SYMS_CvReg_X86_YMM7F7 = 363` (scope `__anon2117d08d0103`)
- L283 _enumerator_ `SYMS_CvReg_X86_YMM0D0 = 364` (scope `__anon2117d08d0103`)
- L284 _enumerator_ `SYMS_CvReg_X86_YMM0D1 = 365` (scope `__anon2117d08d0103`)
- L285 _enumerator_ `SYMS_CvReg_X86_YMM0D2 = 366` (scope `__anon2117d08d0103`)
- L286 _enumerator_ `SYMS_CvReg_X86_YMM0D3 = 367` (scope `__anon2117d08d0103`)
- L287 _enumerator_ `SYMS_CvReg_X86_YMM1D0 = 368` (scope `__anon2117d08d0103`)
- L288 _enumerator_ `SYMS_CvReg_X86_YMM1D1 = 369` (scope `__anon2117d08d0103`)
- L289 _enumerator_ `SYMS_CvReg_X86_YMM1D2 = 370` (scope `__anon2117d08d0103`)
- L290 _enumerator_ `SYMS_CvReg_X86_YMM1D3 = 371` (scope `__anon2117d08d0103`)
- L291 _enumerator_ `SYMS_CvReg_X86_YMM2D0 = 372` (scope `__anon2117d08d0103`)
- L292 _enumerator_ `SYMS_CvReg_X86_YMM2D1 = 373` (scope `__anon2117d08d0103`)
- L293 _enumerator_ `SYMS_CvReg_X86_YMM2D2 = 374` (scope `__anon2117d08d0103`)
- L294 _enumerator_ `SYMS_CvReg_X86_YMM2D3 = 375` (scope `__anon2117d08d0103`)
- L295 _enumerator_ `SYMS_CvReg_X86_YMM3D0 = 376` (scope `__anon2117d08d0103`)
- L296 _enumerator_ `SYMS_CvReg_X86_YMM3D1 = 377` (scope `__anon2117d08d0103`)
- L297 _enumerator_ `SYMS_CvReg_X86_YMM3D2 = 378` (scope `__anon2117d08d0103`)
- L298 _enumerator_ `SYMS_CvReg_X86_YMM3D3 = 379` (scope `__anon2117d08d0103`)
- L299 _enumerator_ `SYMS_CvReg_X86_YMM4D0 = 380` (scope `__anon2117d08d0103`)
- L300 _enumerator_ `SYMS_CvReg_X86_YMM4D1 = 381` (scope `__anon2117d08d0103`)
- L301 _enumerator_ `SYMS_CvReg_X86_YMM4D2 = 382` (scope `__anon2117d08d0103`)
- L302 _enumerator_ `SYMS_CvReg_X86_YMM4D3 = 383` (scope `__anon2117d08d0103`)
- L303 _enumerator_ `SYMS_CvReg_X86_YMM5D0 = 384` (scope `__anon2117d08d0103`)
- L304 _enumerator_ `SYMS_CvReg_X86_YMM5D1 = 385` (scope `__anon2117d08d0103`)
- L305 _enumerator_ `SYMS_CvReg_X86_YMM5D2 = 386` (scope `__anon2117d08d0103`)
- L306 _enumerator_ `SYMS_CvReg_X86_YMM5D3 = 387` (scope `__anon2117d08d0103`)
- L307 _enumerator_ `SYMS_CvReg_X86_YMM6D0 = 388` (scope `__anon2117d08d0103`)
- L308 _enumerator_ `SYMS_CvReg_X86_YMM6D1 = 389` (scope `__anon2117d08d0103`)
- L309 _enumerator_ `SYMS_CvReg_X86_YMM6D2 = 390` (scope `__anon2117d08d0103`)
- L310 _enumerator_ `SYMS_CvReg_X86_YMM6D3 = 391` (scope `__anon2117d08d0103`)
- L311 _enumerator_ `SYMS_CvReg_X86_YMM7D0 = 392` (scope `__anon2117d08d0103`)
- L312 _enumerator_ `SYMS_CvReg_X86_YMM7D1 = 393` (scope `__anon2117d08d0103`)
- L313 _enumerator_ `SYMS_CvReg_X86_YMM7D2 = 394` (scope `__anon2117d08d0103`)
- L314 _enumerator_ `SYMS_CvReg_X86_YMM7D3 = 395` (scope `__anon2117d08d0103`)
- L316 _enumerator_ `SYMS_CvReg_X86_COUNT` (scope `__anon2117d08d0103`)
- L321 _enumerator_ `SYMS_CvReg_X64_AL = 1` (scope `__anon2117d08d0103`)
- L322 _enumerator_ `SYMS_CvReg_X64_CL = 2` (scope `__anon2117d08d0103`)
- L323 _enumerator_ `SYMS_CvReg_X64_DL = 3` (scope `__anon2117d08d0103`)
- L324 _enumerator_ `SYMS_CvReg_X64_BL = 4` (scope `__anon2117d08d0103`)
- L325 _enumerator_ `SYMS_CvReg_X64_AH = 5` (scope `__anon2117d08d0103`)
- L326 _enumerator_ `SYMS_CvReg_X64_CH = 6` (scope `__anon2117d08d0103`)
- L327 _enumerator_ `SYMS_CvReg_X64_DH = 7` (scope `__anon2117d08d0103`)
- L328 _enumerator_ `SYMS_CvReg_X64_BH = 8` (scope `__anon2117d08d0103`)
- L329 _enumerator_ `SYMS_CvReg_X64_AX = 9` (scope `__anon2117d08d0103`)
- L330 _enumerator_ `SYMS_CvReg_X64_CX = 10` (scope `__anon2117d08d0103`)
- L331 _enumerator_ `SYMS_CvReg_X64_DX = 11` (scope `__anon2117d08d0103`)
- L332 _enumerator_ `SYMS_CvReg_X64_BX = 12` (scope `__anon2117d08d0103`)
- L333 _enumerator_ `SYMS_CvReg_X64_SP = 13` (scope `__anon2117d08d0103`)
- L334 _enumerator_ `SYMS_CvReg_X64_BP = 14` (scope `__anon2117d08d0103`)
- L335 _enumerator_ `SYMS_CvReg_X64_SI = 15` (scope `__anon2117d08d0103`)
- L336 _enumerator_ `SYMS_CvReg_X64_DI = 16` (scope `__anon2117d08d0103`)
- L337 _enumerator_ `SYMS_CvReg_X64_EAX = 17` (scope `__anon2117d08d0103`)
- L338 _enumerator_ `SYMS_CvReg_X64_ECX = 18` (scope `__anon2117d08d0103`)
- L339 _enumerator_ `SYMS_CvReg_X64_EDX = 19` (scope `__anon2117d08d0103`)
- L340 _enumerator_ `SYMS_CvReg_X64_EBX = 20` (scope `__anon2117d08d0103`)
- L341 _enumerator_ `SYMS_CvReg_X64_ESP = 21` (scope `__anon2117d08d0103`)
- L342 _enumerator_ `SYMS_CvReg_X64_EBP = 22` (scope `__anon2117d08d0103`)
- L343 _enumerator_ `SYMS_CvReg_X64_ESI = 23` (scope `__anon2117d08d0103`)
- L344 _enumerator_ `SYMS_CvReg_X64_EDI = 24` (scope `__anon2117d08d0103`)
- L345 _enumerator_ `SYMS_CvReg_X64_ES = 25` (scope `__anon2117d08d0103`)
- L346 _enumerator_ `SYMS_CvReg_X64_CS = 26` (scope `__anon2117d08d0103`)
- L347 _enumerator_ `SYMS_CvReg_X64_SS = 27` (scope `__anon2117d08d0103`)
- L348 _enumerator_ `SYMS_CvReg_X64_DS = 28` (scope `__anon2117d08d0103`)
- L349 _enumerator_ `SYMS_CvReg_X64_FS = 29` (scope `__anon2117d08d0103`)
- L350 _enumerator_ `SYMS_CvReg_X64_GS = 30` (scope `__anon2117d08d0103`)
- L351 _enumerator_ `SYMS_CvReg_X64_FLAGS = 32` (scope `__anon2117d08d0103`)
- L352 _enumerator_ `SYMS_CvReg_X64_RIP = 33` (scope `__anon2117d08d0103`)
- L353 _enumerator_ `SYMS_CvReg_X64_EFLAGS = 34` (scope `__anon2117d08d0103`)
- L357 _enumerator_ `SYMS_CvReg_X64_CR0 = 80` (scope `__anon2117d08d0103`)
- L358 _enumerator_ `SYMS_CvReg_X64_CR1 = 81` (scope `__anon2117d08d0103`)
- L359 _enumerator_ `SYMS_CvReg_X64_CR2 = 82` (scope `__anon2117d08d0103`)
- L360 _enumerator_ `SYMS_CvReg_X64_CR3 = 83` (scope `__anon2117d08d0103`)
- L361 _enumerator_ `SYMS_CvReg_X64_CR4 = 84` (scope `__anon2117d08d0103`)
- L362 _enumerator_ `SYMS_CvReg_X64_CR8 = 88` (scope `__anon2117d08d0103`)
- L366 _enumerator_ `SYMS_CvReg_X64_DR0 = 90` (scope `__anon2117d08d0103`)
- L367 _enumerator_ `SYMS_CvReg_X64_DR1 = 91` (scope `__anon2117d08d0103`)
- L368 _enumerator_ `SYMS_CvReg_X64_DR2 = 92` (scope `__anon2117d08d0103`)
- L369 _enumerator_ `SYMS_CvReg_X64_DR3 = 93` (scope `__anon2117d08d0103`)
- L370 _enumerator_ `SYMS_CvReg_X64_DR4 = 94` (scope `__anon2117d08d0103`)
- L371 _enumerator_ `SYMS_CvReg_X64_DR5 = 95` (scope `__anon2117d08d0103`)
- L372 _enumerator_ `SYMS_CvReg_X64_DR6 = 96` (scope `__anon2117d08d0103`)
- L373 _enumerator_ `SYMS_CvReg_X64_DR7 = 97` (scope `__anon2117d08d0103`)
- L374 _enumerator_ `SYMS_CvReg_X64_DR8 = 98` (scope `__anon2117d08d0103`)
- L375 _enumerator_ `SYMS_CvReg_X64_DR9 = 99` (scope `__anon2117d08d0103`)
- L376 _enumerator_ `SYMS_CvReg_X64_DR10 = 100` (scope `__anon2117d08d0103`)
- L377 _enumerator_ `SYMS_CvReg_X64_DR11 = 101` (scope `__anon2117d08d0103`)
- L378 _enumerator_ `SYMS_CvReg_X64_DR12 = 102` (scope `__anon2117d08d0103`)
- L379 _enumerator_ `SYMS_CvReg_X64_DR13 = 103` (scope `__anon2117d08d0103`)
- L380 _enumerator_ `SYMS_CvReg_X64_DR14 = 104` (scope `__anon2117d08d0103`)
- L381 _enumerator_ `SYMS_CvReg_X64_DR15 = 105` (scope `__anon2117d08d0103`)
- L383 _enumerator_ `SYMS_CvReg_X64_GDTR = 110` (scope `__anon2117d08d0103`)
- L384 _enumerator_ `SYMS_CvReg_X64_GDTL = 111` (scope `__anon2117d08d0103`)
- L385 _enumerator_ `SYMS_CvReg_X64_IDTR = 112` (scope `__anon2117d08d0103`)
- L386 _enumerator_ `SYMS_CvReg_X64_IDTL = 113` (scope `__anon2117d08d0103`)
- L387 _enumerator_ `SYMS_CvReg_X64_LDTR = 114` (scope `__anon2117d08d0103`)
- L388 _enumerator_ `SYMS_CvReg_X64_TR = 115` (scope `__anon2117d08d0103`)
- L390 _enumerator_ `SYMS_CvReg_X64_ST0 = 128` (scope `__anon2117d08d0103`)
- L391 _enumerator_ `SYMS_CvReg_X64_ST1 = 129` (scope `__anon2117d08d0103`)
- L392 _enumerator_ `SYMS_CvReg_X64_ST2 = 130` (scope `__anon2117d08d0103`)
- L393 _enumerator_ `SYMS_CvReg_X64_ST3 = 131` (scope `__anon2117d08d0103`)
- L394 _enumerator_ `SYMS_CvReg_X64_ST4 = 132` (scope `__anon2117d08d0103`)
- L395 _enumerator_ `SYMS_CvReg_X64_ST5 = 133` (scope `__anon2117d08d0103`)
- L396 _enumerator_ `SYMS_CvReg_X64_ST6 = 134` (scope `__anon2117d08d0103`)
- L397 _enumerator_ `SYMS_CvReg_X64_ST7 = 135` (scope `__anon2117d08d0103`)
- L398 _enumerator_ `SYMS_CvReg_X64_CTRL = 136` (scope `__anon2117d08d0103`)
- L399 _enumerator_ `SYMS_CvReg_X64_STAT = 137` (scope `__anon2117d08d0103`)
- L400 _enumerator_ `SYMS_CvReg_X64_TAG = 138` (scope `__anon2117d08d0103`)
- L401 _enumerator_ `SYMS_CvReg_X64_FPIP = 139` (scope `__anon2117d08d0103`)
- L402 _enumerator_ `SYMS_CvReg_X64_FPCS = 140` (scope `__anon2117d08d0103`)
- L403 _enumerator_ `SYMS_CvReg_X64_FPDO = 141` (scope `__anon2117d08d0103`)
- L404 _enumerator_ `SYMS_CvReg_X64_FPDS = 142` (scope `__anon2117d08d0103`)
- L405 _enumerator_ `SYMS_CvReg_X64_ISEM = 143` (scope `__anon2117d08d0103`)
- L406 _enumerator_ `SYMS_CvReg_X64_FPEIP = 144` (scope `__anon2117d08d0103`)
- L407 _enumerator_ `SYMS_CvReg_X64_FPEDO = 145` (scope `__anon2117d08d0103`)
- L409 _enumerator_ `SYMS_CvReg_X64_MM0 = 146` (scope `__anon2117d08d0103`)
- L410 _enumerator_ `SYMS_CvReg_X64_MM1 = 147` (scope `__anon2117d08d0103`)
- L411 _enumerator_ `SYMS_CvReg_X64_MM2 = 148` (scope `__anon2117d08d0103`)
- L412 _enumerator_ `SYMS_CvReg_X64_MM3 = 149` (scope `__anon2117d08d0103`)
- L413 _enumerator_ `SYMS_CvReg_X64_MM4 = 150` (scope `__anon2117d08d0103`)
- L414 _enumerator_ `SYMS_CvReg_X64_MM5 = 151` (scope `__anon2117d08d0103`)
- L415 _enumerator_ `SYMS_CvReg_X64_MM6 = 152` (scope `__anon2117d08d0103`)
- L416 _enumerator_ `SYMS_CvReg_X64_MM7 = 153` (scope `__anon2117d08d0103`)
- L418 _enumerator_ `SYMS_CvReg_X64_XMM0 = 154` (scope `__anon2117d08d0103`)
- L419 _enumerator_ `SYMS_CvReg_X64_XMM1 = 155` (scope `__anon2117d08d0103`)
- L420 _enumerator_ `SYMS_CvReg_X64_XMM2 = 156` (scope `__anon2117d08d0103`)
- L421 _enumerator_ `SYMS_CvReg_X64_XMM3 = 157` (scope `__anon2117d08d0103`)
- L422 _enumerator_ `SYMS_CvReg_X64_XMM4 = 158` (scope `__anon2117d08d0103`)
- L423 _enumerator_ `SYMS_CvReg_X64_XMM5 = 159` (scope `__anon2117d08d0103`)
- L424 _enumerator_ `SYMS_CvReg_X64_XMM6 = 160` (scope `__anon2117d08d0103`)
- L425 _enumerator_ `SYMS_CvReg_X64_XMM7 = 161` (scope `__anon2117d08d0103`)
- L427 _enumerator_ `SYMS_CvReg_X64_XMM0_0 = 162` (scope `__anon2117d08d0103`)
- L428 _enumerator_ `SYMS_CvReg_X64_XMM0_1 = 163` (scope `__anon2117d08d0103`)
- L429 _enumerator_ `SYMS_CvReg_X64_XMM0_2 = 164` (scope `__anon2117d08d0103`)
- L430 _enumerator_ `SYMS_CvReg_X64_XMM0_3 = 165` (scope `__anon2117d08d0103`)
- L431 _enumerator_ `SYMS_CvReg_X64_XMM1_0 = 166` (scope `__anon2117d08d0103`)
- L432 _enumerator_ `SYMS_CvReg_X64_XMM1_1 = 167` (scope `__anon2117d08d0103`)
- L433 _enumerator_ `SYMS_CvReg_X64_XMM1_2 = 168` (scope `__anon2117d08d0103`)
- L434 _enumerator_ `SYMS_CvReg_X64_XMM1_3 = 169` (scope `__anon2117d08d0103`)
- L435 _enumerator_ `SYMS_CvReg_X64_XMM2_0 = 170` (scope `__anon2117d08d0103`)
- L436 _enumerator_ `SYMS_CvReg_X64_XMM2_1 = 171` (scope `__anon2117d08d0103`)
- L437 _enumerator_ `SYMS_CvReg_X64_XMM2_2 = 172` (scope `__anon2117d08d0103`)
- L438 _enumerator_ `SYMS_CvReg_X64_XMM2_3 = 173` (scope `__anon2117d08d0103`)
- L439 _enumerator_ `SYMS_CvReg_X64_XMM3_0 = 174` (scope `__anon2117d08d0103`)
- L440 _enumerator_ `SYMS_CvReg_X64_XMM3_1 = 175` (scope `__anon2117d08d0103`)
- L441 _enumerator_ `SYMS_CvReg_X64_XMM3_2 = 176` (scope `__anon2117d08d0103`)
- L442 _enumerator_ `SYMS_CvReg_X64_XMM3_3 = 177` (scope `__anon2117d08d0103`)
- L443 _enumerator_ `SYMS_CvReg_X64_XMM4_0 = 178` (scope `__anon2117d08d0103`)
- L444 _enumerator_ `SYMS_CvReg_X64_XMM4_1 = 179` (scope `__anon2117d08d0103`)
- L445 _enumerator_ `SYMS_CvReg_X64_XMM4_2 = 180` (scope `__anon2117d08d0103`)
- L446 _enumerator_ `SYMS_CvReg_X64_XMM4_3 = 181` (scope `__anon2117d08d0103`)
- L447 _enumerator_ `SYMS_CvReg_X64_XMM5_0 = 182` (scope `__anon2117d08d0103`)
- L448 _enumerator_ `SYMS_CvReg_X64_XMM5_1 = 183` (scope `__anon2117d08d0103`)
- L449 _enumerator_ `SYMS_CvReg_X64_XMM5_2 = 184` (scope `__anon2117d08d0103`)
- L450 _enumerator_ `SYMS_CvReg_X64_XMM5_3 = 185` (scope `__anon2117d08d0103`)
- L451 _enumerator_ `SYMS_CvReg_X64_XMM6_0 = 186` (scope `__anon2117d08d0103`)
- L452 _enumerator_ `SYMS_CvReg_X64_XMM6_1 = 187` (scope `__anon2117d08d0103`)
- L453 _enumerator_ `SYMS_CvReg_X64_XMM6_2 = 188` (scope `__anon2117d08d0103`)
- L454 _enumerator_ `SYMS_CvReg_X64_XMM6_3 = 189` (scope `__anon2117d08d0103`)
- L455 _enumerator_ `SYMS_CvReg_X64_XMM7_0 = 190` (scope `__anon2117d08d0103`)
- L456 _enumerator_ `SYMS_CvReg_X64_XMM7_1 = 191` (scope `__anon2117d08d0103`)
- L457 _enumerator_ `SYMS_CvReg_X64_XMM7_2 = 192` (scope `__anon2117d08d0103`)
- L458 _enumerator_ `SYMS_CvReg_X64_XMM7_3 = 193` (scope `__anon2117d08d0103`)
- L460 _enumerator_ `SYMS_CvReg_X64_XMM0L = 194` (scope `__anon2117d08d0103`)
- L461 _enumerator_ `SYMS_CvReg_X64_XMM1L = 195` (scope `__anon2117d08d0103`)
- L462 _enumerator_ `SYMS_CvReg_X64_XMM2L = 196` (scope `__anon2117d08d0103`)
- L463 _enumerator_ `SYMS_CvReg_X64_XMM3L = 197` (scope `__anon2117d08d0103`)
- L464 _enumerator_ `SYMS_CvReg_X64_XMM4L = 198` (scope `__anon2117d08d0103`)
- L465 _enumerator_ `SYMS_CvReg_X64_XMM5L = 199` (scope `__anon2117d08d0103`)
- L466 _enumerator_ `SYMS_CvReg_X64_XMM6L = 200` (scope `__anon2117d08d0103`)
- L467 _enumerator_ `SYMS_CvReg_X64_XMM7L = 201` (scope `__anon2117d08d0103`)
- L469 _enumerator_ `SYMS_CvReg_X64_XMM0H = 202` (scope `__anon2117d08d0103`)
- L470 _enumerator_ `SYMS_CvReg_X64_XMM1H = 203` (scope `__anon2117d08d0103`)
- L471 _enumerator_ `SYMS_CvReg_X64_XMM2H = 204` (scope `__anon2117d08d0103`)
- L472 _enumerator_ `SYMS_CvReg_X64_XMM3H = 205` (scope `__anon2117d08d0103`)
- L473 _enumerator_ `SYMS_CvReg_X64_XMM4H = 206` (scope `__anon2117d08d0103`)
- L474 _enumerator_ `SYMS_CvReg_X64_XMM5H = 207` (scope `__anon2117d08d0103`)
- L475 _enumerator_ `SYMS_CvReg_X64_XMM6H = 208` (scope `__anon2117d08d0103`)
- L476 _enumerator_ `SYMS_CvReg_X64_XMM7H = 209` (scope `__anon2117d08d0103`)
- L479 _enumerator_ `SYMS_CvReg_X64_MXCSR = 211` (scope `__anon2117d08d0103`) — XMM status register
- L482 _enumerator_ `SYMS_CvReg_X64_EMM0L = 220` (scope `__anon2117d08d0103`) — XMM sub-registers (WNI integer)
- L483 _enumerator_ `SYMS_CvReg_X64_EMM1L = 221` (scope `__anon2117d08d0103`)
- L484 _enumerator_ `SYMS_CvReg_X64_EMM2L = 222` (scope `__anon2117d08d0103`)
- L485 _enumerator_ `SYMS_CvReg_X64_EMM3L = 223` (scope `__anon2117d08d0103`)
- L486 _enumerator_ `SYMS_CvReg_X64_EMM4L = 224` (scope `__anon2117d08d0103`)
- L487 _enumerator_ `SYMS_CvReg_X64_EMM5L = 225` (scope `__anon2117d08d0103`)
- L488 _enumerator_ `SYMS_CvReg_X64_EMM6L = 226` (scope `__anon2117d08d0103`)
- L489 _enumerator_ `SYMS_CvReg_X64_EMM7L = 227` (scope `__anon2117d08d0103`)
- L491 _enumerator_ `SYMS_CvReg_X64_EMM0H = 228` (scope `__anon2117d08d0103`)
- L492 _enumerator_ `SYMS_CvReg_X64_EMM1H = 229` (scope `__anon2117d08d0103`)
- L493 _enumerator_ `SYMS_CvReg_X64_EMM2H = 230` (scope `__anon2117d08d0103`)
- L494 _enumerator_ `SYMS_CvReg_X64_EMM3H = 231` (scope `__anon2117d08d0103`)
- L495 _enumerator_ `SYMS_CvReg_X64_EMM4H = 232` (scope `__anon2117d08d0103`)
- L496 _enumerator_ `SYMS_CvReg_X64_EMM5H = 233` (scope `__anon2117d08d0103`)
- L497 _enumerator_ `SYMS_CvReg_X64_EMM6H = 234` (scope `__anon2117d08d0103`)
- L498 _enumerator_ `SYMS_CvReg_X64_EMM7H = 235` (scope `__anon2117d08d0103`)
- L502 _enumerator_ `SYMS_CvReg_X64_MM00 = 236` (scope `__anon2117d08d0103`)
- L503 _enumerator_ `SYMS_CvReg_X64_MM01 = 237` (scope `__anon2117d08d0103`)
- L504 _enumerator_ `SYMS_CvReg_X64_MM10 = 238` (scope `__anon2117d08d0103`)
- L505 _enumerator_ `SYMS_CvReg_X64_MM11 = 239` (scope `__anon2117d08d0103`)
- L506 _enumerator_ `SYMS_CvReg_X64_MM20 = 240` (scope `__anon2117d08d0103`)
- L507 _enumerator_ `SYMS_CvReg_X64_MM21 = 241` (scope `__anon2117d08d0103`)
- L508 _enumerator_ `SYMS_CvReg_X64_MM30 = 242` (scope `__anon2117d08d0103`)
- L509 _enumerator_ `SYMS_CvReg_X64_MM31 = 243` (scope `__anon2117d08d0103`)
- L510 _enumerator_ `SYMS_CvReg_X64_MM40 = 244` (scope `__anon2117d08d0103`)
- L511 _enumerator_ `SYMS_CvReg_X64_MM41 = 245` (scope `__anon2117d08d0103`)
- L512 _enumerator_ `SYMS_CvReg_X64_MM50 = 246` (scope `__anon2117d08d0103`)
- L513 _enumerator_ `SYMS_CvReg_X64_MM51 = 247` (scope `__anon2117d08d0103`)
- L514 _enumerator_ `SYMS_CvReg_X64_MM60 = 248` (scope `__anon2117d08d0103`)
- L515 _enumerator_ `SYMS_CvReg_X64_MM61 = 249` (scope `__anon2117d08d0103`)
- L516 _enumerator_ `SYMS_CvReg_X64_MM70 = 250` (scope `__anon2117d08d0103`)
- L517 _enumerator_ `SYMS_CvReg_X64_MM71 = 251` (scope `__anon2117d08d0103`)
- L519 _enumerator_ `SYMS_CvReg_X64_XMM8 = 252` (scope `__anon2117d08d0103`)
- L520 _enumerator_ `SYMS_CvReg_X64_XMM9 = 253` (scope `__anon2117d08d0103`)
- L521 _enumerator_ `SYMS_CvReg_X64_XMM10 = 254` (scope `__anon2117d08d0103`)
- L522 _enumerator_ `SYMS_CvReg_X64_XMM11 = 255` (scope `__anon2117d08d0103`)
- L523 _enumerator_ `SYMS_CvReg_X64_XMM12 = 256` (scope `__anon2117d08d0103`)
- L524 _enumerator_ `SYMS_CvReg_X64_XMM13 = 257` (scope `__anon2117d08d0103`)
- L525 _enumerator_ `SYMS_CvReg_X64_XMM14 = 258` (scope `__anon2117d08d0103`)
- L526 _enumerator_ `SYMS_CvReg_X64_XMM15 = 259` (scope `__anon2117d08d0103`)
- L528 _enumerator_ `SYMS_CvReg_X64_XMM8_0 = 260` (scope `__anon2117d08d0103`)
- L529 _enumerator_ `SYMS_CvReg_X64_XMM8_1 = 261` (scope `__anon2117d08d0103`)
- L530 _enumerator_ `SYMS_CvReg_X64_XMM8_2 = 262` (scope `__anon2117d08d0103`)
- L531 _enumerator_ `SYMS_CvReg_X64_XMM8_3 = 263` (scope `__anon2117d08d0103`)
- L532 _enumerator_ `SYMS_CvReg_X64_XMM9_0 = 264` (scope `__anon2117d08d0103`)
- L533 _enumerator_ `SYMS_CvReg_X64_XMM9_1 = 265` (scope `__anon2117d08d0103`)
- L534 _enumerator_ `SYMS_CvReg_X64_XMM9_2 = 266` (scope `__anon2117d08d0103`)
- L535 _enumerator_ `SYMS_CvReg_X64_XMM9_3 = 267` (scope `__anon2117d08d0103`)
- L536 _enumerator_ `SYMS_CvReg_X64_XMM10_0 = 268` (scope `__anon2117d08d0103`)
- L537 _enumerator_ `SYMS_CvReg_X64_XMM10_1 = 269` (scope `__anon2117d08d0103`)
- L538 _enumerator_ `SYMS_CvReg_X64_XMM10_2 = 270` (scope `__anon2117d08d0103`)
- L539 _enumerator_ `SYMS_CvReg_X64_XMM10_3 = 271` (scope `__anon2117d08d0103`)
- L540 _enumerator_ `SYMS_CvReg_X64_XMM11_0 = 272` (scope `__anon2117d08d0103`)
- L541 _enumerator_ `SYMS_CvReg_X64_XMM11_1 = 273` (scope `__anon2117d08d0103`)
- L542 _enumerator_ `SYMS_CvReg_X64_XMM11_2 = 274` (scope `__anon2117d08d0103`)
- L543 _enumerator_ `SYMS_CvReg_X64_XMM11_3 = 275` (scope `__anon2117d08d0103`)
- L544 _enumerator_ `SYMS_CvReg_X64_XMM12_0 = 276` (scope `__anon2117d08d0103`)
- L545 _enumerator_ `SYMS_CvReg_X64_XMM12_1 = 277` (scope `__anon2117d08d0103`)
- L546 _enumerator_ `SYMS_CvReg_X64_XMM12_2 = 278` (scope `__anon2117d08d0103`)
- L547 _enumerator_ `SYMS_CvReg_X64_XMM12_3 = 279` (scope `__anon2117d08d0103`)
- L548 _enumerator_ `SYMS_CvReg_X64_XMM13_0 = 280` (scope `__anon2117d08d0103`)
- L549 _enumerator_ `SYMS_CvReg_X64_XMM13_1 = 281` (scope `__anon2117d08d0103`)
- L550 _enumerator_ `SYMS_CvReg_X64_XMM13_2 = 282` (scope `__anon2117d08d0103`)
- L551 _enumerator_ `SYMS_CvReg_X64_XMM13_3 = 283` (scope `__anon2117d08d0103`)
- L552 _enumerator_ `SYMS_CvReg_X64_XMM14_0 = 284` (scope `__anon2117d08d0103`)
- L553 _enumerator_ `SYMS_CvReg_X64_XMM14_1 = 285` (scope `__anon2117d08d0103`)
- L554 _enumerator_ `SYMS_CvReg_X64_XMM14_2 = 286` (scope `__anon2117d08d0103`)
- L555 _enumerator_ `SYMS_CvReg_X64_XMM14_3 = 287` (scope `__anon2117d08d0103`)
- L556 _enumerator_ `SYMS_CvReg_X64_XMM15_0 = 288` (scope `__anon2117d08d0103`)
- L557 _enumerator_ `SYMS_CvReg_X64_XMM15_1 = 289` (scope `__anon2117d08d0103`)
- L558 _enumerator_ `SYMS_CvReg_X64_XMM15_2 = 290` (scope `__anon2117d08d0103`)
- L559 _enumerator_ `SYMS_CvReg_X64_XMM15_3 = 291` (scope `__anon2117d08d0103`)
- L561 _enumerator_ `SYMS_CvReg_X64_XMM8L = 292` (scope `__anon2117d08d0103`)
- L562 _enumerator_ `SYMS_CvReg_X64_XMM9L = 293` (scope `__anon2117d08d0103`)
- L563 _enumerator_ `SYMS_CvReg_X64_XMM10L = 294` (scope `__anon2117d08d0103`)
- L564 _enumerator_ `SYMS_CvReg_X64_XMM11L = 295` (scope `__anon2117d08d0103`)
- L565 _enumerator_ `SYMS_CvReg_X64_XMM12L = 296` (scope `__anon2117d08d0103`)
- L566 _enumerator_ `SYMS_CvReg_X64_XMM13L = 297` (scope `__anon2117d08d0103`)
- L567 _enumerator_ `SYMS_CvReg_X64_XMM14L = 298` (scope `__anon2117d08d0103`)
- L568 _enumerator_ `SYMS_CvReg_X64_XMM15L = 299` (scope `__anon2117d08d0103`)
- L570 _enumerator_ `SYMS_CvReg_X64_XMM8H = 300` (scope `__anon2117d08d0103`)
- L571 _enumerator_ `SYMS_CvReg_X64_XMM9H = 301` (scope `__anon2117d08d0103`)
- L572 _enumerator_ `SYMS_CvReg_X64_XMM10H = 302` (scope `__anon2117d08d0103`)
- L573 _enumerator_ `SYMS_CvReg_X64_XMM11H = 303` (scope `__anon2117d08d0103`)
- L574 _enumerator_ `SYMS_CvReg_X64_XMM12H = 304` (scope `__anon2117d08d0103`)
- L575 _enumerator_ `SYMS_CvReg_X64_XMM13H = 305` (scope `__anon2117d08d0103`)
- L576 _enumerator_ `SYMS_CvReg_X64_XMM14H = 306` (scope `__anon2117d08d0103`)
- L577 _enumerator_ `SYMS_CvReg_X64_XMM15H = 307` (scope `__anon2117d08d0103`)
- L581 _enumerator_ `SYMS_CvReg_X64_EMM8L = 308` (scope `__anon2117d08d0103`)
- L582 _enumerator_ `SYMS_CvReg_X64_EMM9L = 309` (scope `__anon2117d08d0103`)
- L583 _enumerator_ `SYMS_CvReg_X64_EMM10L = 310` (scope `__anon2117d08d0103`)
- L584 _enumerator_ `SYMS_CvReg_X64_EMM11L = 311` (scope `__anon2117d08d0103`)
- L585 _enumerator_ `SYMS_CvReg_X64_EMM12L = 312` (scope `__anon2117d08d0103`)
- L586 _enumerator_ `SYMS_CvReg_X64_EMM13L = 313` (scope `__anon2117d08d0103`)
- L587 _enumerator_ `SYMS_CvReg_X64_EMM14L = 314` (scope `__anon2117d08d0103`)
- L588 _enumerator_ `SYMS_CvReg_X64_EMM15L = 315` (scope `__anon2117d08d0103`)
- L590 _enumerator_ `SYMS_CvReg_X64_EMM8H = 316` (scope `__anon2117d08d0103`)
- L591 _enumerator_ `SYMS_CvReg_X64_EMM9H = 317` (scope `__anon2117d08d0103`)
- L592 _enumerator_ `SYMS_CvReg_X64_EMM10H = 318` (scope `__anon2117d08d0103`)
- L593 _enumerator_ `SYMS_CvReg_X64_EMM11H = 319` (scope `__anon2117d08d0103`)
- L594 _enumerator_ `SYMS_CvReg_X64_EMM12H = 320` (scope `__anon2117d08d0103`)
- L595 _enumerator_ `SYMS_CvReg_X64_EMM13H = 321` (scope `__anon2117d08d0103`)
- L596 _enumerator_ `SYMS_CvReg_X64_EMM14H = 322` (scope `__anon2117d08d0103`)
- L597 _enumerator_ `SYMS_CvReg_X64_EMM15H = 323` (scope `__anon2117d08d0103`)
- L600 _enumerator_ `SYMS_CvReg_X64_SIL = 324` (scope `__anon2117d08d0103`) — Low byte forms of some standard registers
- L601 _enumerator_ `SYMS_CvReg_X64_DIL = 325` (scope `__anon2117d08d0103`)
- L602 _enumerator_ `SYMS_CvReg_X64_BPL = 326` (scope `__anon2117d08d0103`)
- L603 _enumerator_ `SYMS_CvReg_X64_SPL = 327` (scope `__anon2117d08d0103`)
- L606 _enumerator_ `SYMS_CvReg_X64_RAX = 328` (scope `__anon2117d08d0103`) — 64-bit regular registers
- L607 _enumerator_ `SYMS_CvReg_X64_RBX = 329` (scope `__anon2117d08d0103`)
- L608 _enumerator_ `SYMS_CvReg_X64_RCX = 330` (scope `__anon2117d08d0103`)
- L609 _enumerator_ `SYMS_CvReg_X64_RDX = 331` (scope `__anon2117d08d0103`)
- L610 _enumerator_ `SYMS_CvReg_X64_RSI = 332` (scope `__anon2117d08d0103`)
- L611 _enumerator_ `SYMS_CvReg_X64_RDI = 333` (scope `__anon2117d08d0103`)
- L612 _enumerator_ `SYMS_CvReg_X64_RBP = 334` (scope `__anon2117d08d0103`)
- L613 _enumerator_ `SYMS_CvReg_X64_RSP = 335` (scope `__anon2117d08d0103`)
- L616 _enumerator_ `SYMS_CvReg_X64_R8 = 336` (scope `__anon2117d08d0103`) — 64-bit integer registers with 8-, 16-, and 32-bit forms (B, W, and D)
- L617 _enumerator_ `SYMS_CvReg_X64_R9 = 337` (scope `__anon2117d08d0103`)
- L618 _enumerator_ `SYMS_CvReg_X64_R10 = 338` (scope `__anon2117d08d0103`)
- L619 _enumerator_ `SYMS_CvReg_X64_R11 = 339` (scope `__anon2117d08d0103`)
- L620 _enumerator_ `SYMS_CvReg_X64_R12 = 340` (scope `__anon2117d08d0103`)
- L621 _enumerator_ `SYMS_CvReg_X64_R13 = 341` (scope `__anon2117d08d0103`)
- L622 _enumerator_ `SYMS_CvReg_X64_R14 = 342` (scope `__anon2117d08d0103`)
- L623 _enumerator_ `SYMS_CvReg_X64_R15 = 343` (scope `__anon2117d08d0103`)
- L625 _enumerator_ `SYMS_CvReg_X64_R8B = 344` (scope `__anon2117d08d0103`)
- L626 _enumerator_ `SYMS_CvReg_X64_R9B = 345` (scope `__anon2117d08d0103`)
- L627 _enumerator_ `SYMS_CvReg_X64_R10B = 346` (scope `__anon2117d08d0103`)
- L628 _enumerator_ `SYMS_CvReg_X64_R11B = 347` (scope `__anon2117d08d0103`)
- L629 _enumerator_ `SYMS_CvReg_X64_R12B = 348` (scope `__anon2117d08d0103`)
- L630 _enumerator_ `SYMS_CvReg_X64_R13B = 349` (scope `__anon2117d08d0103`)
- L631 _enumerator_ `SYMS_CvReg_X64_R14B = 350` (scope `__anon2117d08d0103`)
- L632 _enumerator_ `SYMS_CvReg_X64_R15B = 351` (scope `__anon2117d08d0103`)
- L634 _enumerator_ `SYMS_CvReg_X64_R8W = 352` (scope `__anon2117d08d0103`)
- L635 _enumerator_ `SYMS_CvReg_X64_R9W = 353` (scope `__anon2117d08d0103`)
- L636 _enumerator_ `SYMS_CvReg_X64_R10W = 354` (scope `__anon2117d08d0103`)
- L637 _enumerator_ `SYMS_CvReg_X64_R11W = 355` (scope `__anon2117d08d0103`)
- L638 _enumerator_ `SYMS_CvReg_X64_R12W = 356` (scope `__anon2117d08d0103`)
- L639 _enumerator_ `SYMS_CvReg_X64_R13W = 357` (scope `__anon2117d08d0103`)
- L640 _enumerator_ `SYMS_CvReg_X64_R14W = 358` (scope `__anon2117d08d0103`)
- L641 _enumerator_ `SYMS_CvReg_X64_R15W = 359` (scope `__anon2117d08d0103`)
- L643 _enumerator_ `SYMS_CvReg_X64_R8D = 360` (scope `__anon2117d08d0103`)
- L644 _enumerator_ `SYMS_CvReg_X64_R9D = 361` (scope `__anon2117d08d0103`)
- L645 _enumerator_ `SYMS_CvReg_X64_R10D = 362` (scope `__anon2117d08d0103`)
- L646 _enumerator_ `SYMS_CvReg_X64_R11D = 363` (scope `__anon2117d08d0103`)
- L647 _enumerator_ `SYMS_CvReg_X64_R12D = 364` (scope `__anon2117d08d0103`)
- L648 _enumerator_ `SYMS_CvReg_X64_R13D = 365` (scope `__anon2117d08d0103`)
- L649 _enumerator_ `SYMS_CvReg_X64_R14D = 366` (scope `__anon2117d08d0103`)
- L650 _enumerator_ `SYMS_CvReg_X64_R15D = 367` (scope `__anon2117d08d0103`)
- L654 _enumerator_ `SYMS_CvReg_X64_YMM0 = 368` (scope `__anon2117d08d0103`)
- L655 _enumerator_ `SYMS_CvReg_X64_YMM1 = 369` (scope `__anon2117d08d0103`)
- L656 _enumerator_ `SYMS_CvReg_X64_YMM2 = 370` (scope `__anon2117d08d0103`)
- L657 _enumerator_ `SYMS_CvReg_X64_YMM3 = 371` (scope `__anon2117d08d0103`)
- L658 _enumerator_ `SYMS_CvReg_X64_YMM4 = 372` (scope `__anon2117d08d0103`)
- L659 _enumerator_ `SYMS_CvReg_X64_YMM5 = 373` (scope `__anon2117d08d0103`)
- L660 _enumerator_ `SYMS_CvReg_X64_YMM6 = 374` (scope `__anon2117d08d0103`)
- L661 _enumerator_ `SYMS_CvReg_X64_YMM7 = 375` (scope `__anon2117d08d0103`)
- L662 _enumerator_ `SYMS_CvReg_X64_YMM8 = 376` (scope `__anon2117d08d0103`)
- L663 _enumerator_ `SYMS_CvReg_X64_YMM9 = 377` (scope `__anon2117d08d0103`)
- L664 _enumerator_ `SYMS_CvReg_X64_YMM10 = 378` (scope `__anon2117d08d0103`)
- L665 _enumerator_ `SYMS_CvReg_X64_YMM11 = 379` (scope `__anon2117d08d0103`)
- L666 _enumerator_ `SYMS_CvReg_X64_YMM12 = 380` (scope `__anon2117d08d0103`)
- L667 _enumerator_ `SYMS_CvReg_X64_YMM13 = 381` (scope `__anon2117d08d0103`)
- L668 _enumerator_ `SYMS_CvReg_X64_YMM14 = 382` (scope `__anon2117d08d0103`)
- L669 _enumerator_ `SYMS_CvReg_X64_YMM15 = 383` (scope `__anon2117d08d0103`)
- L672 _enumerator_ `SYMS_CvReg_X64_YMM0H = 384` (scope `__anon2117d08d0103`) — AVX registers upper 128 bits
- L673 _enumerator_ `SYMS_CvReg_X64_YMM1H = 385` (scope `__anon2117d08d0103`)
- L674 _enumerator_ `SYMS_CvReg_X64_YMM2H = 386` (scope `__anon2117d08d0103`)
- L675 _enumerator_ `SYMS_CvReg_X64_YMM3H = 387` (scope `__anon2117d08d0103`)
- L676 _enumerator_ `SYMS_CvReg_X64_YMM4H = 388` (scope `__anon2117d08d0103`)
- L677 _enumerator_ `SYMS_CvReg_X64_YMM5H = 389` (scope `__anon2117d08d0103`)
- L678 _enumerator_ `SYMS_CvReg_X64_YMM6H = 390` (scope `__anon2117d08d0103`)
- L679 _enumerator_ `SYMS_CvReg_X64_YMM7H = 391` (scope `__anon2117d08d0103`)
- L680 _enumerator_ `SYMS_CvReg_X64_YMM8H = 392` (scope `__anon2117d08d0103`)
- L681 _enumerator_ `SYMS_CvReg_X64_YMM9H = 393` (scope `__anon2117d08d0103`)
- L682 _enumerator_ `SYMS_CvReg_X64_YMM10H = 394` (scope `__anon2117d08d0103`)
- L683 _enumerator_ `SYMS_CvReg_X64_YMM11H = 395` (scope `__anon2117d08d0103`)
- L684 _enumerator_ `SYMS_CvReg_X64_YMM12H = 396` (scope `__anon2117d08d0103`)
- L685 _enumerator_ `SYMS_CvReg_X64_YMM13H = 397` (scope `__anon2117d08d0103`)
- L686 _enumerator_ `SYMS_CvReg_X64_YMM14H = 398` (scope `__anon2117d08d0103`)
- L687 _enumerator_ `SYMS_CvReg_X64_YMM15H = 399` (scope `__anon2117d08d0103`)
- L692 _enumerator_ `SYMS_CvReg_X64_XMM0IL = 400` (scope `__anon2117d08d0103`) — Lower/upper 8 bytes of XMM registers.  Unlike CV_AMD64_XMM<regnum><H/L>, these values reprsesent the bit patterns of the registers as 64-bit integers, not the representation of these registers as a double.
- L693 _enumerator_ `SYMS_CvReg_X64_XMM1IL = 401` (scope `__anon2117d08d0103`)
- L694 _enumerator_ `SYMS_CvReg_X64_XMM2IL = 402` (scope `__anon2117d08d0103`)
- L695 _enumerator_ `SYMS_CvReg_X64_XMM3IL = 403` (scope `__anon2117d08d0103`)
- L696 _enumerator_ `SYMS_CvReg_X64_XMM4IL = 404` (scope `__anon2117d08d0103`)
- L697 _enumerator_ `SYMS_CvReg_X64_XMM5IL = 405` (scope `__anon2117d08d0103`)
- L698 _enumerator_ `SYMS_CvReg_X64_XMM6IL = 406` (scope `__anon2117d08d0103`)
- L699 _enumerator_ `SYMS_CvReg_X64_XMM7IL = 407` (scope `__anon2117d08d0103`)
- L700 _enumerator_ `SYMS_CvReg_X64_XMM8IL = 408` (scope `__anon2117d08d0103`)
- L701 _enumerator_ `SYMS_CvReg_X64_XMM9IL = 409` (scope `__anon2117d08d0103`)
- L702 _enumerator_ `SYMS_CvReg_X64_XMM10IL = 410` (scope `__anon2117d08d0103`)
- L703 _enumerator_ `SYMS_CvReg_X64_XMM11IL = 411` (scope `__anon2117d08d0103`)
- L704 _enumerator_ `SYMS_CvReg_X64_XMM12IL = 412` (scope `__anon2117d08d0103`)
- L705 _enumerator_ `SYMS_CvReg_X64_XMM13IL = 413` (scope `__anon2117d08d0103`)
- L706 _enumerator_ `SYMS_CvReg_X64_XMM14IL = 414` (scope `__anon2117d08d0103`)
- L707 _enumerator_ `SYMS_CvReg_X64_XMM15IL = 415` (scope `__anon2117d08d0103`)
- L709 _enumerator_ `SYMS_CvReg_X64_XMM0IH = 416` (scope `__anon2117d08d0103`)
- L710 _enumerator_ `SYMS_CvReg_X64_XMM1IH = 417` (scope `__anon2117d08d0103`)
- L711 _enumerator_ `SYMS_CvReg_X64_XMM2IH = 418` (scope `__anon2117d08d0103`)
- L712 _enumerator_ `SYMS_CvReg_X64_XMM3IH = 419` (scope `__anon2117d08d0103`)
- L713 _enumerator_ `SYMS_CvReg_X64_XMM4IH = 420` (scope `__anon2117d08d0103`)
- L714 _enumerator_ `SYMS_CvReg_X64_XMM5IH = 421` (scope `__anon2117d08d0103`)
- L715 _enumerator_ `SYMS_CvReg_X64_XMM6IH = 422` (scope `__anon2117d08d0103`)
- L716 _enumerator_ `SYMS_CvReg_X64_XMM7IH = 423` (scope `__anon2117d08d0103`)
- L717 _enumerator_ `SYMS_CvReg_X64_XMM8IH = 424` (scope `__anon2117d08d0103`)
- L718 _enumerator_ `SYMS_CvReg_X64_XMM9IH = 425` (scope `__anon2117d08d0103`)
- L719 _enumerator_ `SYMS_CvReg_X64_XMM10IH = 426` (scope `__anon2117d08d0103`)
- L720 _enumerator_ `SYMS_CvReg_X64_XMM11IH = 427` (scope `__anon2117d08d0103`)
- L721 _enumerator_ `SYMS_CvReg_X64_XMM12IH = 428` (scope `__anon2117d08d0103`)
- L722 _enumerator_ `SYMS_CvReg_X64_XMM13IH = 429` (scope `__anon2117d08d0103`)
- L723 _enumerator_ `SYMS_CvReg_X64_XMM14IH = 430` (scope `__anon2117d08d0103`)
- L724 _enumerator_ `SYMS_CvReg_X64_XMM15IH = 431` (scope `__anon2117d08d0103`)
- L728 _enumerator_ `SYMS_CvReg_X64_YMM0I0 = 432` (scope `__anon2117d08d0103`)
- L729 _enumerator_ `SYMS_CvReg_X64_YMM0I1 = 433` (scope `__anon2117d08d0103`)
- L730 _enumerator_ `SYMS_CvReg_X64_YMM0I2 = 434` (scope `__anon2117d08d0103`)
- L731 _enumerator_ `SYMS_CvReg_X64_YMM0I3 = 435` (scope `__anon2117d08d0103`)
- L732 _enumerator_ `SYMS_CvReg_X64_YMM1I0 = 436` (scope `__anon2117d08d0103`)
- L733 _enumerator_ `SYMS_CvReg_X64_YMM1I1 = 437` (scope `__anon2117d08d0103`)
- L734 _enumerator_ `SYMS_CvReg_X64_YMM1I2 = 438` (scope `__anon2117d08d0103`)
- L735 _enumerator_ `SYMS_CvReg_X64_YMM1I3 = 439` (scope `__anon2117d08d0103`)
- L736 _enumerator_ `SYMS_CvReg_X64_YMM2I0 = 440` (scope `__anon2117d08d0103`)
- L737 _enumerator_ `SYMS_CvReg_X64_YMM2I1 = 441` (scope `__anon2117d08d0103`)
- L738 _enumerator_ `SYMS_CvReg_X64_YMM2I2 = 442` (scope `__anon2117d08d0103`)
- L739 _enumerator_ `SYMS_CvReg_X64_YMM2I3 = 443` (scope `__anon2117d08d0103`)
- L740 _enumerator_ `SYMS_CvReg_X64_YMM3I0 = 444` (scope `__anon2117d08d0103`)
- L741 _enumerator_ `SYMS_CvReg_X64_YMM3I1 = 445` (scope `__anon2117d08d0103`)
- L742 _enumerator_ `SYMS_CvReg_X64_YMM3I2 = 446` (scope `__anon2117d08d0103`)
- L743 _enumerator_ `SYMS_CvReg_X64_YMM3I3 = 447` (scope `__anon2117d08d0103`)
- L744 _enumerator_ `SYMS_CvReg_X64_YMM4I0 = 448` (scope `__anon2117d08d0103`)
- L745 _enumerator_ `SYMS_CvReg_X64_YMM4I1 = 449` (scope `__anon2117d08d0103`)
- L746 _enumerator_ `SYMS_CvReg_X64_YMM4I2 = 450` (scope `__anon2117d08d0103`)
- L747 _enumerator_ `SYMS_CvReg_X64_YMM4I3 = 451` (scope `__anon2117d08d0103`)
- L748 _enumerator_ `SYMS_CvReg_X64_YMM5I0 = 452` (scope `__anon2117d08d0103`)
- L749 _enumerator_ `SYMS_CvReg_X64_YMM5I1 = 453` (scope `__anon2117d08d0103`)
- L750 _enumerator_ `SYMS_CvReg_X64_YMM5I2 = 454` (scope `__anon2117d08d0103`)
- L751 _enumerator_ `SYMS_CvReg_X64_YMM5I3 = 455` (scope `__anon2117d08d0103`)
- L752 _enumerator_ `SYMS_CvReg_X64_YMM6I0 = 456` (scope `__anon2117d08d0103`)
- L753 _enumerator_ `SYMS_CvReg_X64_YMM6I1 = 457` (scope `__anon2117d08d0103`)
- L754 _enumerator_ `SYMS_CvReg_X64_YMM6I2 = 458` (scope `__anon2117d08d0103`)
- L755 _enumerator_ `SYMS_CvReg_X64_YMM6I3 = 459` (scope `__anon2117d08d0103`)
- L756 _enumerator_ `SYMS_CvReg_X64_YMM7I0 = 460` (scope `__anon2117d08d0103`)
- L757 _enumerator_ `SYMS_CvReg_X64_YMM7I1 = 461` (scope `__anon2117d08d0103`)
- L758 _enumerator_ `SYMS_CvReg_X64_YMM7I2 = 462` (scope `__anon2117d08d0103`)
- L759 _enumerator_ `SYMS_CvReg_X64_YMM7I3 = 463` (scope `__anon2117d08d0103`)
- L760 _enumerator_ `SYMS_CvReg_X64_YMM8I0 = 464` (scope `__anon2117d08d0103`)
- L761 _enumerator_ `SYMS_CvReg_X64_YMM8I1 = 465` (scope `__anon2117d08d0103`)
- L762 _enumerator_ `SYMS_CvReg_X64_YMM8I2 = 466` (scope `__anon2117d08d0103`)
- L763 _enumerator_ `SYMS_CvReg_X64_YMM8I3 = 467` (scope `__anon2117d08d0103`)
- L764 _enumerator_ `SYMS_CvReg_X64_YMM9I0 = 468` (scope `__anon2117d08d0103`)
- L765 _enumerator_ `SYMS_CvReg_X64_YMM9I1 = 469` (scope `__anon2117d08d0103`)
- L766 _enumerator_ `SYMS_CvReg_X64_YMM9I2 = 470` (scope `__anon2117d08d0103`)
- L767 _enumerator_ `SYMS_CvReg_X64_YMM9I3 = 471` (scope `__anon2117d08d0103`)
- L768 _enumerator_ `SYMS_CvReg_X64_YMM10I0 = 472` (scope `__anon2117d08d0103`)
- L769 _enumerator_ `SYMS_CvReg_X64_YMM10I1 = 473` (scope `__anon2117d08d0103`)
- L770 _enumerator_ `SYMS_CvReg_X64_YMM10I2 = 474` (scope `__anon2117d08d0103`)
- L771 _enumerator_ `SYMS_CvReg_X64_YMM10I3 = 475` (scope `__anon2117d08d0103`)
- L772 _enumerator_ `SYMS_CvReg_X64_YMM11I0 = 476` (scope `__anon2117d08d0103`)
- L773 _enumerator_ `SYMS_CvReg_X64_YMM11I1 = 477` (scope `__anon2117d08d0103`)
- L774 _enumerator_ `SYMS_CvReg_X64_YMM11I2 = 478` (scope `__anon2117d08d0103`)
- L775 _enumerator_ `SYMS_CvReg_X64_YMM11I3 = 479` (scope `__anon2117d08d0103`)
- L776 _enumerator_ `SYMS_CvReg_X64_YMM12I0 = 480` (scope `__anon2117d08d0103`)
- L777 _enumerator_ `SYMS_CvReg_X64_YMM12I1 = 481` (scope `__anon2117d08d0103`)
- L778 _enumerator_ `SYMS_CvReg_X64_YMM12I2 = 482` (scope `__anon2117d08d0103`)
- L779 _enumerator_ `SYMS_CvReg_X64_YMM12I3 = 483` (scope `__anon2117d08d0103`)
- L780 _enumerator_ `SYMS_CvReg_X64_YMM13I0 = 484` (scope `__anon2117d08d0103`)
- L781 _enumerator_ `SYMS_CvReg_X64_YMM13I1 = 485` (scope `__anon2117d08d0103`)
- L782 _enumerator_ `SYMS_CvReg_X64_YMM13I2 = 486` (scope `__anon2117d08d0103`)
- L783 _enumerator_ `SYMS_CvReg_X64_YMM13I3 = 487` (scope `__anon2117d08d0103`)
- L784 _enumerator_ `SYMS_CvReg_X64_YMM14I0 = 488` (scope `__anon2117d08d0103`)
- L785 _enumerator_ `SYMS_CvReg_X64_YMM14I1 = 489` (scope `__anon2117d08d0103`)
- L786 _enumerator_ `SYMS_CvReg_X64_YMM14I2 = 490` (scope `__anon2117d08d0103`)
- L787 _enumerator_ `SYMS_CvReg_X64_YMM14I3 = 491` (scope `__anon2117d08d0103`)
- L788 _enumerator_ `SYMS_CvReg_X64_YMM15I0 = 492` (scope `__anon2117d08d0103`)
- L789 _enumerator_ `SYMS_CvReg_X64_YMM15I1 = 493` (scope `__anon2117d08d0103`)
- L790 _enumerator_ `SYMS_CvReg_X64_YMM15I2 = 494` (scope `__anon2117d08d0103`)
- L791 _enumerator_ `SYMS_CvReg_X64_YMM15I3 = 495` (scope `__anon2117d08d0103`)
- L795 _enumerator_ `SYMS_CvReg_X64_YMM0F0 = 496` (scope `__anon2117d08d0103`)
- L796 _enumerator_ `SYMS_CvReg_X64_YMM0F1 = 497` (scope `__anon2117d08d0103`)
- L797 _enumerator_ `SYMS_CvReg_X64_YMM0F2 = 498` (scope `__anon2117d08d0103`)
- L798 _enumerator_ `SYMS_CvReg_X64_YMM0F3 = 499` (scope `__anon2117d08d0103`)
- L799 _enumerator_ `SYMS_CvReg_X64_YMM0F4 = 500` (scope `__anon2117d08d0103`)
- L800 _enumerator_ `SYMS_CvReg_X64_YMM0F5 = 501` (scope `__anon2117d08d0103`)
- L801 _enumerator_ `SYMS_CvReg_X64_YMM0F6 = 502` (scope `__anon2117d08d0103`)
- L802 _enumerator_ `SYMS_CvReg_X64_YMM0F7 = 503` (scope `__anon2117d08d0103`)
- L803 _enumerator_ `SYMS_CvReg_X64_YMM1F0 = 504` (scope `__anon2117d08d0103`)
- L804 _enumerator_ `SYMS_CvReg_X64_YMM1F1 = 505` (scope `__anon2117d08d0103`)
- L805 _enumerator_ `SYMS_CvReg_X64_YMM1F2 = 506` (scope `__anon2117d08d0103`)
- L806 _enumerator_ `SYMS_CvReg_X64_YMM1F3 = 507` (scope `__anon2117d08d0103`)
- L807 _enumerator_ `SYMS_CvReg_X64_YMM1F4 = 508` (scope `__anon2117d08d0103`)
- L808 _enumerator_ `SYMS_CvReg_X64_YMM1F5 = 509` (scope `__anon2117d08d0103`)
- L809 _enumerator_ `SYMS_CvReg_X64_YMM1F6 = 510` (scope `__anon2117d08d0103`)
- L810 _enumerator_ `SYMS_CvReg_X64_YMM1F7 = 511` (scope `__anon2117d08d0103`)
- L811 _enumerator_ `SYMS_CvReg_X64_YMM2F0 = 512` (scope `__anon2117d08d0103`)
- L812 _enumerator_ `SYMS_CvReg_X64_YMM2F1 = 513` (scope `__anon2117d08d0103`)
- L813 _enumerator_ `SYMS_CvReg_X64_YMM2F2 = 514` (scope `__anon2117d08d0103`)
- L814 _enumerator_ `SYMS_CvReg_X64_YMM2F3 = 515` (scope `__anon2117d08d0103`)
- L815 _enumerator_ `SYMS_CvReg_X64_YMM2F4 = 516` (scope `__anon2117d08d0103`)
- L816 _enumerator_ `SYMS_CvReg_X64_YMM2F5 = 517` (scope `__anon2117d08d0103`)
- L817 _enumerator_ `SYMS_CvReg_X64_YMM2F6 = 518` (scope `__anon2117d08d0103`)
- L818 _enumerator_ `SYMS_CvReg_X64_YMM2F7 = 519` (scope `__anon2117d08d0103`)
- L819 _enumerator_ `SYMS_CvReg_X64_YMM3F0 = 520` (scope `__anon2117d08d0103`)
- L820 _enumerator_ `SYMS_CvReg_X64_YMM3F1 = 521` (scope `__anon2117d08d0103`)
- L821 _enumerator_ `SYMS_CvReg_X64_YMM3F2 = 522` (scope `__anon2117d08d0103`)
- L822 _enumerator_ `SYMS_CvReg_X64_YMM3F3 = 523` (scope `__anon2117d08d0103`)
- L823 _enumerator_ `SYMS_CvReg_X64_YMM3F4 = 524` (scope `__anon2117d08d0103`)
- L824 _enumerator_ `SYMS_CvReg_X64_YMM3F5 = 525` (scope `__anon2117d08d0103`)
- L825 _enumerator_ `SYMS_CvReg_X64_YMM3F6 = 526` (scope `__anon2117d08d0103`)
- L826 _enumerator_ `SYMS_CvReg_X64_YMM3F7 = 527` (scope `__anon2117d08d0103`)
- L828 _enumerator_ `SYMS_CvReg_X64_YMM4F0 = 528` (scope `__anon2117d08d0103`)
- L829 _enumerator_ `SYMS_CvReg_X64_YMM4F1 = 529` (scope `__anon2117d08d0103`)
- L830 _enumerator_ `SYMS_CvReg_X64_YMM4F2 = 530` (scope `__anon2117d08d0103`)
- L831 _enumerator_ `SYMS_CvReg_X64_YMM4F3 = 531` (scope `__anon2117d08d0103`)
- L832 _enumerator_ `SYMS_CvReg_X64_YMM4F4 = 532` (scope `__anon2117d08d0103`)
- L833 _enumerator_ `SYMS_CvReg_X64_YMM4F5 = 533` (scope `__anon2117d08d0103`)
- L834 _enumerator_ `SYMS_CvReg_X64_YMM4F6 = 534` (scope `__anon2117d08d0103`)
- L835 _enumerator_ `SYMS_CvReg_X64_YMM4F7 = 535` (scope `__anon2117d08d0103`)
- L836 _enumerator_ `SYMS_CvReg_X64_YMM5F0 = 536` (scope `__anon2117d08d0103`)
- L837 _enumerator_ `SYMS_CvReg_X64_YMM5F1 = 537` (scope `__anon2117d08d0103`)
- L838 _enumerator_ `SYMS_CvReg_X64_YMM5F2 = 538` (scope `__anon2117d08d0103`)
- L839 _enumerator_ `SYMS_CvReg_X64_YMM5F3 = 539` (scope `__anon2117d08d0103`)
- L840 _enumerator_ `SYMS_CvReg_X64_YMM5F4 = 540` (scope `__anon2117d08d0103`)
- L841 _enumerator_ `SYMS_CvReg_X64_YMM5F5 = 541` (scope `__anon2117d08d0103`)
- L842 _enumerator_ `SYMS_CvReg_X64_YMM5F6 = 542` (scope `__anon2117d08d0103`)
- L843 _enumerator_ `SYMS_CvReg_X64_YMM5F7 = 543` (scope `__anon2117d08d0103`)
- L844 _enumerator_ `SYMS_CvReg_X64_YMM6F0 = 544` (scope `__anon2117d08d0103`)
- L845 _enumerator_ `SYMS_CvReg_X64_YMM6F1 = 545` (scope `__anon2117d08d0103`)
- L846 _enumerator_ `SYMS_CvReg_X64_YMM6F2 = 546` (scope `__anon2117d08d0103`)
- L847 _enumerator_ `SYMS_CvReg_X64_YMM6F3 = 547` (scope `__anon2117d08d0103`)
- L848 _enumerator_ `SYMS_CvReg_X64_YMM6F4 = 548` (scope `__anon2117d08d0103`)
- L849 _enumerator_ `SYMS_CvReg_X64_YMM6F5 = 549` (scope `__anon2117d08d0103`)
- L850 _enumerator_ `SYMS_CvReg_X64_YMM6F6 = 550` (scope `__anon2117d08d0103`)
- L851 _enumerator_ `SYMS_CvReg_X64_YMM6F7 = 551` (scope `__anon2117d08d0103`)
- L852 _enumerator_ `SYMS_CvReg_X64_YMM7F0 = 552` (scope `__anon2117d08d0103`)
- L853 _enumerator_ `SYMS_CvReg_X64_YMM7F1 = 553` (scope `__anon2117d08d0103`)
- L854 _enumerator_ `SYMS_CvReg_X64_YMM7F2 = 554` (scope `__anon2117d08d0103`)
- L855 _enumerator_ `SYMS_CvReg_X64_YMM7F3 = 555` (scope `__anon2117d08d0103`)
- L856 _enumerator_ `SYMS_CvReg_X64_YMM7F4 = 556` (scope `__anon2117d08d0103`)
- L857 _enumerator_ `SYMS_CvReg_X64_YMM7F5 = 557` (scope `__anon2117d08d0103`)
- L858 _enumerator_ `SYMS_CvReg_X64_YMM7F6 = 558` (scope `__anon2117d08d0103`)
- L859 _enumerator_ `SYMS_CvReg_X64_YMM7F7 = 559` (scope `__anon2117d08d0103`)
- L861 _enumerator_ `SYMS_CvReg_X64_YMM8F0 = 560` (scope `__anon2117d08d0103`)
- L862 _enumerator_ `SYMS_CvReg_X64_YMM8F1 = 561` (scope `__anon2117d08d0103`)
- L863 _enumerator_ `SYMS_CvReg_X64_YMM8F2 = 562` (scope `__anon2117d08d0103`)
- L864 _enumerator_ `SYMS_CvReg_X64_YMM8F3 = 563` (scope `__anon2117d08d0103`)
- L865 _enumerator_ `SYMS_CvReg_X64_YMM8F4 = 564` (scope `__anon2117d08d0103`)
- L866 _enumerator_ `SYMS_CvReg_X64_YMM8F5 = 565` (scope `__anon2117d08d0103`)
- L867 _enumerator_ `SYMS_CvReg_X64_YMM8F6 = 566` (scope `__anon2117d08d0103`)
- L868 _enumerator_ `SYMS_CvReg_X64_YMM8F7 = 567` (scope `__anon2117d08d0103`)
- L869 _enumerator_ `SYMS_CvReg_X64_YMM9F0 = 568` (scope `__anon2117d08d0103`)
- L870 _enumerator_ `SYMS_CvReg_X64_YMM9F1 = 569` (scope `__anon2117d08d0103`)
- L871 _enumerator_ `SYMS_CvReg_X64_YMM9F2 = 570` (scope `__anon2117d08d0103`)
- L872 _enumerator_ `SYMS_CvReg_X64_YMM9F3 = 571` (scope `__anon2117d08d0103`)
- L873 _enumerator_ `SYMS_CvReg_X64_YMM9F4 = 572` (scope `__anon2117d08d0103`)
- L874 _enumerator_ `SYMS_CvReg_X64_YMM9F5 = 573` (scope `__anon2117d08d0103`)
- L875 _enumerator_ `SYMS_CvReg_X64_YMM9F6 = 574` (scope `__anon2117d08d0103`)
- L876 _enumerator_ `SYMS_CvReg_X64_YMM9F7 = 575` (scope `__anon2117d08d0103`)
- L877 _enumerator_ `SYMS_CvReg_X64_YMM10F0 = 576` (scope `__anon2117d08d0103`)
- L878 _enumerator_ `SYMS_CvReg_X64_YMM10F1 = 577` (scope `__anon2117d08d0103`)
- L879 _enumerator_ `SYMS_CvReg_X64_YMM10F2 = 578` (scope `__anon2117d08d0103`)
- L880 _enumerator_ `SYMS_CvReg_X64_YMM10F3 = 579` (scope `__anon2117d08d0103`)
- L881 _enumerator_ `SYMS_CvReg_X64_YMM10F4 = 580` (scope `__anon2117d08d0103`)
- L882 _enumerator_ `SYMS_CvReg_X64_YMM10F5 = 581` (scope `__anon2117d08d0103`)
- L883 _enumerator_ `SYMS_CvReg_X64_YMM10F6 = 582` (scope `__anon2117d08d0103`)
- L884 _enumerator_ `SYMS_CvReg_X64_YMM10F7 = 583` (scope `__anon2117d08d0103`)
- L885 _enumerator_ `SYMS_CvReg_X64_YMM11F0 = 584` (scope `__anon2117d08d0103`)
- L886 _enumerator_ `SYMS_CvReg_X64_YMM11F1 = 585` (scope `__anon2117d08d0103`)
- L887 _enumerator_ `SYMS_CvReg_X64_YMM11F2 = 586` (scope `__anon2117d08d0103`)
- L888 _enumerator_ `SYMS_CvReg_X64_YMM11F3 = 587` (scope `__anon2117d08d0103`)
- L889 _enumerator_ `SYMS_CvReg_X64_YMM11F4 = 588` (scope `__anon2117d08d0103`)
- L890 _enumerator_ `SYMS_CvReg_X64_YMM11F5 = 589` (scope `__anon2117d08d0103`)
- L891 _enumerator_ `SYMS_CvReg_X64_YMM11F6 = 590` (scope `__anon2117d08d0103`)
- L892 _enumerator_ `SYMS_CvReg_X64_YMM11F7 = 591` (scope `__anon2117d08d0103`)
- L894 _enumerator_ `SYMS_CvReg_X64_YMM12F0 = 592` (scope `__anon2117d08d0103`)
- L895 _enumerator_ `SYMS_CvReg_X64_YMM12F1 = 593` (scope `__anon2117d08d0103`)
- L896 _enumerator_ `SYMS_CvReg_X64_YMM12F2 = 594` (scope `__anon2117d08d0103`)
- L897 _enumerator_ `SYMS_CvReg_X64_YMM12F3 = 595` (scope `__anon2117d08d0103`)
- L898 _enumerator_ `SYMS_CvReg_X64_YMM12F4 = 596` (scope `__anon2117d08d0103`)
- L899 _enumerator_ `SYMS_CvReg_X64_YMM12F5 = 597` (scope `__anon2117d08d0103`)
- L900 _enumerator_ `SYMS_CvReg_X64_YMM12F6 = 598` (scope `__anon2117d08d0103`)
- L901 _enumerator_ `SYMS_CvReg_X64_YMM12F7 = 599` (scope `__anon2117d08d0103`)
- L902 _enumerator_ `SYMS_CvReg_X64_YMM13F0 = 600` (scope `__anon2117d08d0103`)
- L903 _enumerator_ `SYMS_CvReg_X64_YMM13F1 = 601` (scope `__anon2117d08d0103`)
- L904 _enumerator_ `SYMS_CvReg_X64_YMM13F2 = 602` (scope `__anon2117d08d0103`)
- L905 _enumerator_ `SYMS_CvReg_X64_YMM13F3 = 603` (scope `__anon2117d08d0103`)
- L906 _enumerator_ `SYMS_CvReg_X64_YMM13F4 = 604` (scope `__anon2117d08d0103`)
- L907 _enumerator_ `SYMS_CvReg_X64_YMM13F5 = 605` (scope `__anon2117d08d0103`)
- L908 _enumerator_ `SYMS_CvReg_X64_YMM13F6 = 606` (scope `__anon2117d08d0103`)
- L909 _enumerator_ `SYMS_CvReg_X64_YMM13F7 = 607` (scope `__anon2117d08d0103`)
- L910 _enumerator_ `SYMS_CvReg_X64_YMM14F0 = 608` (scope `__anon2117d08d0103`)
- L911 _enumerator_ `SYMS_CvReg_X64_YMM14F1 = 609` (scope `__anon2117d08d0103`)
- L912 _enumerator_ `SYMS_CvReg_X64_YMM14F2 = 610` (scope `__anon2117d08d0103`)
- L913 _enumerator_ `SYMS_CvReg_X64_YMM14F3 = 611` (scope `__anon2117d08d0103`)
- L914 _enumerator_ `SYMS_CvReg_X64_YMM14F4 = 612` (scope `__anon2117d08d0103`)
- L915 _enumerator_ `SYMS_CvReg_X64_YMM14F5 = 613` (scope `__anon2117d08d0103`)
- L916 _enumerator_ `SYMS_CvReg_X64_YMM14F6 = 614` (scope `__anon2117d08d0103`)
- L917 _enumerator_ `SYMS_CvReg_X64_YMM14F7 = 615` (scope `__anon2117d08d0103`)
- L918 _enumerator_ `SYMS_CvReg_X64_YMM15F0 = 616` (scope `__anon2117d08d0103`)
- L919 _enumerator_ `SYMS_CvReg_X64_YMM15F1 = 617` (scope `__anon2117d08d0103`)
- L920 _enumerator_ `SYMS_CvReg_X64_YMM15F2 = 618` (scope `__anon2117d08d0103`)
- L921 _enumerator_ `SYMS_CvReg_X64_YMM15F3 = 619` (scope `__anon2117d08d0103`)
- L922 _enumerator_ `SYMS_CvReg_X64_YMM15F4 = 620` (scope `__anon2117d08d0103`)
- L923 _enumerator_ `SYMS_CvReg_X64_YMM15F5 = 621` (scope `__anon2117d08d0103`)
- L924 _enumerator_ `SYMS_CvReg_X64_YMM15F6 = 622` (scope `__anon2117d08d0103`)
- L925 _enumerator_ `SYMS_CvReg_X64_YMM15F7 = 623` (scope `__anon2117d08d0103`)
- L930 _enumerator_ `SYMS_CvReg_X64_YMM0D0 = 624` (scope `__anon2117d08d0103`)
- L931 _enumerator_ `SYMS_CvReg_X64_YMM0D1 = 625` (scope `__anon2117d08d0103`)
- L932 _enumerator_ `SYMS_CvReg_X64_YMM0D2 = 626` (scope `__anon2117d08d0103`)
- L933 _enumerator_ `SYMS_CvReg_X64_YMM0D3 = 627` (scope `__anon2117d08d0103`)
- L934 _enumerator_ `SYMS_CvReg_X64_YMM1D0 = 628` (scope `__anon2117d08d0103`)
- L935 _enumerator_ `SYMS_CvReg_X64_YMM1D1 = 629` (scope `__anon2117d08d0103`)
- L936 _enumerator_ `SYMS_CvReg_X64_YMM1D2 = 630` (scope `__anon2117d08d0103`)
- L937 _enumerator_ `SYMS_CvReg_X64_YMM1D3 = 631` (scope `__anon2117d08d0103`)
- L938 _enumerator_ `SYMS_CvReg_X64_YMM2D0 = 632` (scope `__anon2117d08d0103`)
- L939 _enumerator_ `SYMS_CvReg_X64_YMM2D1 = 633` (scope `__anon2117d08d0103`)
- L940 _enumerator_ `SYMS_CvReg_X64_YMM2D2 = 634` (scope `__anon2117d08d0103`)
- L941 _enumerator_ `SYMS_CvReg_X64_YMM2D3 = 635` (scope `__anon2117d08d0103`)
- L942 _enumerator_ `SYMS_CvReg_X64_YMM3D0 = 636` (scope `__anon2117d08d0103`)
- L943 _enumerator_ `SYMS_CvReg_X64_YMM3D1 = 637` (scope `__anon2117d08d0103`)
- L944 _enumerator_ `SYMS_CvReg_X64_YMM3D2 = 638` (scope `__anon2117d08d0103`)
- L945 _enumerator_ `SYMS_CvReg_X64_YMM3D3 = 639` (scope `__anon2117d08d0103`)
- L946 _enumerator_ `SYMS_CvReg_X64_YMM4D0 = 640` (scope `__anon2117d08d0103`)
- L947 _enumerator_ `SYMS_CvReg_X64_YMM4D1 = 641` (scope `__anon2117d08d0103`)
- L948 _enumerator_ `SYMS_CvReg_X64_YMM4D2 = 642` (scope `__anon2117d08d0103`)
- L949 _enumerator_ `SYMS_CvReg_X64_YMM4D3 = 643` (scope `__anon2117d08d0103`)
- L950 _enumerator_ `SYMS_CvReg_X64_YMM5D0 = 644` (scope `__anon2117d08d0103`)
- L951 _enumerator_ `SYMS_CvReg_X64_YMM5D1 = 645` (scope `__anon2117d08d0103`)
- L952 _enumerator_ `SYMS_CvReg_X64_YMM5D2 = 646` (scope `__anon2117d08d0103`)
- L953 _enumerator_ `SYMS_CvReg_X64_YMM5D3 = 647` (scope `__anon2117d08d0103`)
- L954 _enumerator_ `SYMS_CvReg_X64_YMM6D0 = 648` (scope `__anon2117d08d0103`)
- L955 _enumerator_ `SYMS_CvReg_X64_YMM6D1 = 649` (scope `__anon2117d08d0103`)
- L956 _enumerator_ `SYMS_CvReg_X64_YMM6D2 = 650` (scope `__anon2117d08d0103`)
- L957 _enumerator_ `SYMS_CvReg_X64_YMM6D3 = 651` (scope `__anon2117d08d0103`)
- L958 _enumerator_ `SYMS_CvReg_X64_YMM7D0 = 652` (scope `__anon2117d08d0103`)
- L959 _enumerator_ `SYMS_CvReg_X64_YMM7D1 = 653` (scope `__anon2117d08d0103`)
- L960 _enumerator_ `SYMS_CvReg_X64_YMM7D2 = 654` (scope `__anon2117d08d0103`)
- L961 _enumerator_ `SYMS_CvReg_X64_YMM7D3 = 655` (scope `__anon2117d08d0103`)
- L963 _enumerator_ `SYMS_CvReg_X64_YMM8D0 = 656` (scope `__anon2117d08d0103`)
- L964 _enumerator_ `SYMS_CvReg_X64_YMM8D1 = 657` (scope `__anon2117d08d0103`)
- L965 _enumerator_ `SYMS_CvReg_X64_YMM8D2 = 658` (scope `__anon2117d08d0103`)
- L966 _enumerator_ `SYMS_CvReg_X64_YMM8D3 = 659` (scope `__anon2117d08d0103`)
- L967 _enumerator_ `SYMS_CvReg_X64_YMM9D0 = 660` (scope `__anon2117d08d0103`)
- L968 _enumerator_ `SYMS_CvReg_X64_YMM9D1 = 661` (scope `__anon2117d08d0103`)
- L969 _enumerator_ `SYMS_CvReg_X64_YMM9D2 = 662` (scope `__anon2117d08d0103`)
- L970 _enumerator_ `SYMS_CvReg_X64_YMM9D3 = 663` (scope `__anon2117d08d0103`)
- L971 _enumerator_ `SYMS_CvReg_X64_YMM10D0 = 664` (scope `__anon2117d08d0103`)
- L972 _enumerator_ `SYMS_CvReg_X64_YMM10D1 = 665` (scope `__anon2117d08d0103`)
- L973 _enumerator_ `SYMS_CvReg_X64_YMM10D2 = 666` (scope `__anon2117d08d0103`)
- L974 _enumerator_ `SYMS_CvReg_X64_YMM10D3 = 667` (scope `__anon2117d08d0103`)
- L975 _enumerator_ `SYMS_CvReg_X64_YMM11D0 = 668` (scope `__anon2117d08d0103`)
- L976 _enumerator_ `SYMS_CvReg_X64_YMM11D1 = 669` (scope `__anon2117d08d0103`)
- L977 _enumerator_ `SYMS_CvReg_X64_YMM11D2 = 670` (scope `__anon2117d08d0103`)
- L978 _enumerator_ `SYMS_CvReg_X64_YMM11D3 = 671` (scope `__anon2117d08d0103`)
- L979 _enumerator_ `SYMS_CvReg_X64_YMM12D0 = 672` (scope `__anon2117d08d0103`)
- L980 _enumerator_ `SYMS_CvReg_X64_YMM12D1 = 673` (scope `__anon2117d08d0103`)
- L981 _enumerator_ `SYMS_CvReg_X64_YMM12D2 = 674` (scope `__anon2117d08d0103`)
- L982 _enumerator_ `SYMS_CvReg_X64_YMM12D3 = 675` (scope `__anon2117d08d0103`)
- L983 _enumerator_ `SYMS_CvReg_X64_YMM13D0 = 676` (scope `__anon2117d08d0103`)
- L984 _enumerator_ `SYMS_CvReg_X64_YMM13D1 = 677` (scope `__anon2117d08d0103`)
- L985 _enumerator_ `SYMS_CvReg_X64_YMM13D2 = 678` (scope `__anon2117d08d0103`)
- L986 _enumerator_ `SYMS_CvReg_X64_YMM13D3 = 679` (scope `__anon2117d08d0103`)
- L987 _enumerator_ `SYMS_CvReg_X64_YMM14D0 = 680` (scope `__anon2117d08d0103`)
- L988 _enumerator_ `SYMS_CvReg_X64_YMM14D1 = 681` (scope `__anon2117d08d0103`)
- L989 _enumerator_ `SYMS_CvReg_X64_YMM14D2 = 682` (scope `__anon2117d08d0103`)
- L990 _enumerator_ `SYMS_CvReg_X64_YMM14D3 = 683` (scope `__anon2117d08d0103`)
- L991 _enumerator_ `SYMS_CvReg_X64_YMM15D0 = 684` (scope `__anon2117d08d0103`)
- L992 _enumerator_ `SYMS_CvReg_X64_YMM15D1 = 685` (scope `__anon2117d08d0103`)
- L993 _enumerator_ `SYMS_CvReg_X64_YMM15D2 = 686` (scope `__anon2117d08d0103`)
- L994 _enumerator_ `SYMS_CvReg_X64_YMM15D3 = 687` (scope `__anon2117d08d0103`)
- L996 _enumerator_ `SYMS_CvReg_X64_COUNT` (scope `__anon2117d08d0103`)
- L998 _enumerator_ `SYMS_CvReg_MAX_COUNT = SYMS_CvReg_X64_COUNT` (scope `__anon2117d08d0103`)
- L1009 _typedef_ `} SYMS_CvSymbolHelper;`
- L1020 _typedef_ `} SYMS_CvMethod;` — unsigned long vbaseoff[0];
- L1025 _macro_ `#define SYMS_CvSubSectionKind_IGNORE_FLAG 0x80000000`
- L1029 _typedef_ `typedef SYMS_U16 SYMS_CvSubSecLinesFlags;`
- L1031 _enumerator_ `SYMS_CvSubSecLinesFlag_HasColumns = (1 << 0)` (scope `__anon2117d08d0203`)
- L1040 _typedef_ `} SYMS_CvSubSecLinesHeader;`
- L1048 _typedef_ `} SYMS_CvFile;` — SYMS_CvLine   lines[num_lines]; SYMS_CvColumn columns[num_columns]; // num_columns?
- L1050 _typedef_ `typedef SYMS_U32 SYMS_CvLineFlags;`
- L1052 _enumerator_ `SYMS_CvLineFlag_LINE_NUMBER_MASK = 0xffffff` (scope `__anon2117d08d0303`)
- L1053 _enumerator_ `SYMS_CvLineFlag_LINE_NUMBER_SHIFT = 0` (scope `__anon2117d08d0303`)
- L1054 _enumerator_ `SYMS_CvLineFlag_DELTA_TO_END_MASK = 0x7f` (scope `__anon2117d08d0303`)
- L1055 _enumerator_ `SYMS_CvLineFlag_DELTA_TO_END_SHIFT = 24` (scope `__anon2117d08d0303`)
- L1056 _enumerator_ `SYMS_CvLineFlag_STATEMENT = (1 << 31)` (scope `__anon2117d08d0303`)
- L1062 _typedef_ `} SYMS_CvLine;`
- L1067 _typedef_ `} SYMS_CvColumn;`
- L1073 _enumerator_ `SYMS_CvFrameDataFlag_HAS_SEH = (1 << 0)` (scope `__anon2117d08d0403`)
- L1074 _enumerator_ `SYMS_CvFrameDataFlag_HAS_EH = (1 << 1)` (scope `__anon2117d08d0403`)
- L1075 _enumerator_ `SYMS_CvFrameDataFlag_IS_FUNC_START = (1 << 2)` (scope `__anon2117d08d0403`)
- L1077 _typedef_ `typedef SYMS_U32 SYMS_CvFrameDataFlags;`
- L1089 _typedef_ `} SYMS_CvFrameData;`

### `Source/Runtime/SymsLib/syms/core/pdb/syms_cv_helpers.h` (Other)


#### enum `SYMS_CvSymbolIDKind`  
`typedef enum SYMS_CvSymbolIDKind`  
_L12-15_
- L13 _public enumerator_ `SYMS_CvSymbolIDKind_Off`
- L14 _public enumerator_ `SYMS_CvSymbolIDKind_Index`

#### enum `SYMS_CvFileIDKind`  
`typedef enum SYMS_CvFileIDKind`  
_L17-23_
- L18 _public enumerator_ `SYMS_CvFileIDKind_Null`
- L19 _public enumerator_ `SYMS_CvFileIDKind_IPIOff`
- L20 _public enumerator_ `SYMS_CvFileIDKind_IPIStringID`
- L21 _public enumerator_ `SYMS_CvFileIDKind_StrTblOff`
- L22 _public enumerator_ `SYMS_CvFileIDKind_C11Off`

#### struct `SYMS_CvElement`  
`typedef struct SYMS_CvElement`  
_L28-32_
- L29 _public member_ `SYMS_MsfRange range;`
- L30 _public member_ `SYMS_U32 next_off;`
- L31 _public member_ `SYMS_U16 kind;`

#### struct `SYMS_CvNumeric`  
`typedef struct SYMS_CvNumeric`  
_L34-37_
- L35 _public member_ `SYMS_TypeKind kind;`
- L36 _public member_ `SYMS_U8 data[32];`

#### struct `SYMS_CvC13SubSection`  
`typedef struct SYMS_CvC13SubSection`  
_L42-47_
- L43 _public member_ `struct SYMS_CvC13SubSection *next;`
- L44 _public member_ `SYMS_CvSubSectionKind kind;`
- L45 _public member_ `SYMS_U32 off;`
- L46 _public member_ `SYMS_U32 size;`

#### struct `SYMS_CvC13SubSectionList`  
`typedef struct SYMS_CvC13SubSectionList`  
_L49-53_
- L50 _public member_ `SYMS_CvC13SubSection *first;`
- L51 _public member_ `SYMS_CvC13SubSection *last;`
- L52 _public member_ `SYMS_U64 count;`

#### struct `SYMS_CvFileNode`  
`typedef struct SYMS_CvFileNode`  
_L58-62_
- L59 _public member_ `struct SYMS_CvFileNode *next;`
- L60 _public member_ `SYMS_U64 count;`
- L61 _public member_ `SYMS_FileID file_ids[6];`

#### struct `SYMS_CvLineSequence`  
`typedef struct SYMS_CvLineSequence`  
_L64-68_
- L65 _public member_ `struct SYMS_CvLineSequence *next;`
- L66 _public member_ `SYMS_Line *lines;`
- L67 _public member_ `SYMS_U64 line_count;`

#### struct `SYMS_CvLineTableLoose`  
`typedef struct SYMS_CvLineTableLoose`  
_L70-79_
- L71 _public member_ `SYMS_CvFileNode *first_file_node;`
- L72 _public member_ `SYMS_CvFileNode *last_file_node;`
- L73 _public member_ `SYMS_U64 file_count;`
- L75 _public member_ `SYMS_CvLineSequence *first_seq;`
- L76 _public member_ `SYMS_CvLineSequence *last_seq;`
- L77 _public member_ `SYMS_U64 seq_count;`
- L78 _public member_ `SYMS_U64 line_count;`

#### struct `SYMS_CvStub`  
`typedef struct SYMS_CvStub`  
_L84-97_
- L85 _public member_ `struct SYMS_CvStub *bucket_next;`
- L86 _public member_ `struct SYMS_CvStub *parent;`
- L87 _public member_ `struct SYMS_CvStub *sibling_next;`
- L88 _public member_ `struct SYMS_CvStub *first;`
- L89 _public member_ `struct SYMS_CvStub *last;`
- L90 _public member_ `SYMS_U32 off;`
- L91 _public member_ `SYMS_U32 index;`
- L92 _public member_ `SYMS_U32 num;`
- L93 _public member_ `SYMS_U32 num2;`

#### union `SYMS_CvStub::(anonymous)`  
`union`  
_L94-96_

#### struct `SYMS_CvStubRef`  
`typedef struct SYMS_CvStubRef`  
_L99-102_
- L100 _public member_ `struct SYMS_CvStubRef *next;`
- L101 _public member_ `SYMS_CvStub *stub;`

#### struct `SYMS_CvUnitAccel`  
`typedef struct SYMS_CvUnitAccel`  
_L104-128_
- L105 _public member_ `SYMS_FileFormat format;`
- L106 _public member_ `SYMS_B32 leaf_set;`
- L107 _public member_ `SYMS_MsfStreamNumber sn;`
- L108 _public member_ `SYMS_CvStub **top_stubs;`
- L109 _public member_ `SYMS_U64 top_count;`
- L110 _public member_ `SYMS_U64 top_min_index;`
- L111 _public member_ `SYMS_CvStub **buckets;`
- L112 _public member_ `SYMS_U64 bucket_count;`
- L113 _public member_ `SYMS_U64 all_count;`
- L114 _public member_ `SYMS_CvStub **ti_indirect_stubs;`
- L115 _public member_ `SYMS_U64 ti_count;`
- L116 _public member_ `SYMS_UnitID uid;`
- L118 _public member_ `SYMS_CvStub **proc_stubs;`
- L119 _public member_ `SYMS_U64 proc_count;`
- L120 _public member_ `SYMS_CvStub **var_stubs;`
- L121 _public member_ `SYMS_U64 var_count;`
- L122 _public member_ `SYMS_CvStub **tls_var_stubs;`
- L123 _public member_ `SYMS_U64 tls_var_count;`
- L124 _public member_ `SYMS_CvStub **thunk_stubs;`
- L125 _public member_ `SYMS_U64 thunk_count;`
- L126 _public member_ `SYMS_CvStub **pub_stubs;`
- L127 _public member_ `SYMS_U64 pub_count;`

#### struct `SYMS_CvResolvedElement`  
`typedef struct SYMS_CvResolvedElement`  
_L130-136_
- L131 _public member_ `SYMS_CvStub *stub;`
- L132 _public member_ `SYMS_U16 kind;`
- L133 _public member_ `SYMS_B8 is_leaf;`
- L134 _public member_ `SYMS_B8 is_index;`
- L135 _public member_ `SYMS_MsfRange range;`

#### struct `SYMS_CvMemStubNode`  
`typedef struct SYMS_CvMemStubNode`  
_L141-147_
- L142 _public member_ `struct SYMS_CvMemStubNode *next;`
- L143 _public member_ `SYMS_String8 name;`
- L144 _public member_ `SYMS_U32 num;`
- L145 _public member_ `SYMS_U32 off;`
- L146 _public member_ `SYMS_U32 off2;`

#### struct `SYMS_PdbMemStubList`  
`typedef struct SYMS_PdbMemStubList`  
_L149-153_
- L150 _public member_ `SYMS_CvMemStubNode *first;`
- L151 _public member_ `SYMS_CvMemStubNode *last;`
- L152 _public member_ `SYMS_U64 mem_count;`

#### struct `SYMS_CvMemsAccel`  
`typedef struct SYMS_CvMemsAccel`  
_L155-160_
- L156 _public member_ `SYMS_FileFormat format;`
- L157 _public member_ `SYMS_String8 type_name;`
- L158 _public member_ `SYMS_U64 count;`
- L159 _public member_ `SYMS_CvMemStubNode **members;`

#### struct `SYMS_CvLeafConsParams`  
`typedef struct SYMS_CvLeafConsParams`  
_L165-170_
- L166 _public member_ `SYMS_FileFormat format;`
- L167 _public member_ `SYMS_UnitID uid;`
- L168 _public member_ `SYMS_CvTypeIndex first_ti;`
- L169 _public member_ `SYMS_U32 align;`

#### struct `SYMS_CvSymConsParams`  
`typedef struct SYMS_CvSymConsParams`  
_L172-176_
- L173 _public member_ `SYMS_FileFormat format;`
- L174 _public member_ `SYMS_U32 align;`
- L175 _public member_ `SYMS_UnitID uid;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_CV_HELPERS_H`
- L15 _typedef_ `SYMS_CvSymbolIDKind_Off, SYMS_CvSymbolIDKind_Index, } SYMS_CvSymbolIDKind;`
- L23 _typedef_ `SYMS_CvFileIDKind_IPIStringID, SYMS_CvFileIDKind_StrTblOff, SYMS_CvFileIDKind_C11Off, } SYMS_CvFileIDKind;`
- L32 _typedef_ `} SYMS_CvElement;`
- L37 _typedef_ `} SYMS_CvNumeric;`
- L47 _typedef_ `} SYMS_CvC13SubSection;`
- L53 _typedef_ `} SYMS_CvC13SubSectionList;`
- L62 _typedef_ `} SYMS_CvFileNode;`
- L68 _typedef_ `} SYMS_CvLineSequence;`
- L79 _typedef_ `} SYMS_CvLineTableLoose;`
- L95 _member_ `SYMS_String8 name;` (scope `SYMS_CvStub::__anon0ea8571f010a`)
- L97 _typedef_ `} SYMS_CvStub;`
- L102 _typedef_ `} SYMS_CvStubRef;`
- L128 _typedef_ `} SYMS_CvUnitAccel;`
- L136 _typedef_ `} SYMS_CvResolvedElement;`
- L147 _typedef_ `} SYMS_CvMemStubNode;`
- L153 _typedef_ `} SYMS_PdbMemStubList;`
- L160 _typedef_ `} SYMS_CvMemsAccel;`
- L170 _typedef_ `} SYMS_CvLeafConsParams;`
- L176 _typedef_ `} SYMS_CvSymConsParams;`
- L182 _prototype_ `SYMS_CvElement syms_cv_element(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range, SYMS_U32 off, SYMS_U32 align);` — cv parse helers
- L185 _prototype_ `SYMS_U32 syms_cv_read_numeric(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range, SYMS_U32 off, SYMS_CvNumeric *out);`
- L187 _prototype_ `SYMS_U32 syms_cv_u32_from_numeric(SYMS_CvNumeric num);`
- L189 _prototype_ `SYMS_CvStubRef*syms_cv_alloc_ref(SYMS_Arena *arena, SYMS_CvStubRef **free_list);`
- L191 _prototype_ `void syms_cv_c13_sub_sections_from_range(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range, SYMS_CvC13SubSectionList *list_out);`
- L195 _prototype_ `SYMS_SecInfoArray syms_cv_sec_info_array_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range);`
- L199 _prototype_ `void sym_cv_loose_push_file_id(SYMS_Arena *arena, SYMS_CvLineTableLoose *loose, SYMS_FileID id);` — cv line info
- L201 _prototype_ `SYMS_Line* sym_cv_loose_push_sequence(SYMS_Arena *arena, SYMS_CvLineTableLoose *loose, SYMS_U64 line_count);`
- L203 _prototype_ `SYMS_LineParseOut sym_cv_line_parse_from_loose(SYMS_Arena *arena, SYMS_CvLineTableLoose *loose);`
- L206 _prototype_ `void sym_cv_loose_lines_from_c13(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange c13_range, SYMS_CvC13SubSection *sub_sections, SYMS_U64 *section_voffs, SYMS_U64 section_count, SYMS_CvLineTableLoose *loose);`
- L211 _prototype_ `void sym_cv_loose_lines_from_c11(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange c11_range, SYMS_U64 *section_voffs, SYMS_U64 section_count, SYMS_CvLineTableLoose *loose);`
- L218 _prototype_ `SYMS_CvUnitAccel*syms_cv_leaf_unit_from_range(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn, SYMS_U64Range range, SYMS_CvLeafConsParams *params);` — cv parsers
- L223 _prototype_ `SYMS_CvUnitAccel*syms_cv_sym_unit_from_ranges(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn, SYMS_U64RangeArray ranges, SYMS_CvSymConsParams *params);`
- L230 _prototype_ `SYMS_CvStub* syms_cv_stub_from_unit_off(SYMS_CvUnitAccel *unit, SYMS_U32 off);` — cv extract helpers
- L231 _prototype_ `SYMS_CvStub* syms_cv_stub_from_unit_index(SYMS_CvUnitAccel *unit, SYMS_U32 index);`
- L232 _prototype_ `SYMS_CvStub* syms_cv_stub_from_unit_sid(SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L233 _prototype_ `SYMS_CvResolvedElement syms_cv_resolve_from_id(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);`
- L236 _prototype_ `SYMS_U64 syms_cv_type_index_first(SYMS_CvUnitAccel *unit);`
- L237 _prototype_ `SYMS_U64 syms_cv_type_index_count(SYMS_CvUnitAccel *unit);`
- L239 _macro_ `#define syms_cv_sid_from_type_index(idx) SYMS_ID_u32_u32(SYMS_CvSymbolIDKind_Index, idx)`
- L242 _prototype_ `SYMS_UnitID syms_cv_uid_from_accel(SYMS_CvUnitAccel *unit);` — main api
- L244 _prototype_ `SYMS_SymbolIDArray syms_cv_proc_sid_array_from_unit(SYMS_Arena *arena, SYMS_CvUnitAccel *unit);`
- L245 _prototype_ `SYMS_SymbolIDArray syms_cv_var_sid_array_from_unit(SYMS_Arena *arena, SYMS_CvUnitAccel *unit);`
- L246 _prototype_ `SYMS_SymbolIDArray syms_cv_type_sid_array_from_unit(SYMS_Arena *arena, SYMS_CvUnitAccel *unit);`
- L248 _prototype_ `SYMS_SymbolKind syms_cv_symbol_kind_from_sid(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L250 _prototype_ `SYMS_String8 syms_cv_symbol_name_from_sid(SYMS_Arena *arena, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L253 _prototype_ `SYMS_TypeInfo syms_cv_type_info_from_sid(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L256 _prototype_ `SYMS_ConstInfo syms_cv_const_info_from_sid(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`

### `Source/Runtime/SymsLib/syms/core/pdb/syms_msf.h` (Other)


#### struct `SYMS_MsfHeader20`  
`typedef struct SYMS_MsfHeader20`  
_L20-27_
- L21 _public member_ `SYMS_U32 block_size;`
- L22 _public member_ `SYMS_U16 free_block_map_block;`
- L23 _public member_ `SYMS_U16 block_count;`
- L24 _public member_ `SYMS_U32 directory_size;`
- L25 _public member_ `SYMS_U32 unknown;`
- L26 _public member_ `SYMS_U16 directory_map;`

#### struct `SYMS_MsfHeader70`  
`typedef struct SYMS_MsfHeader70`  
_L29-36_
- L30 _public member_ `SYMS_U32 block_size;`
- L31 _public member_ `SYMS_U32 free_block_map_block;`
- L32 _public member_ `SYMS_U32 block_count;`
- L33 _public member_ `SYMS_U32 directory_size;`
- L34 _public member_ `SYMS_U32 unknown;`
- L35 _public member_ `SYMS_U32 directory_super_map;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_MSF_H`
- L10 _macro_ `#define SYMS_MSF_INVALID_STREAM_NUMBER SYMS_U16_MAX`
- L11 _typedef_ `typedef SYMS_U16 SYMS_MsfStreamNumber;`
- L13 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL char syms_msf20_magic[] = "Mi`
- L14 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL char syms_msf70_magic[] = "Mi`
- L16 _macro_ `#define SYMS_MSF20_MAGIC_SIZE 44`
- L17 _macro_ `#define SYMS_MSF70_MAGIC_SIZE 32`
- L18 _macro_ `#define SYMS_MSF_MAX_MAGIC_SIZE 44`
- L27 _typedef_ `} SYMS_MsfHeader20;`
- L36 _typedef_ `} SYMS_MsfHeader70;`

### `Source/Runtime/SymsLib/syms/core/pdb/syms_msf_parser.h` (Other)


#### struct `SYMS_MsfHeaderInfo`  
`typedef struct SYMS_MsfHeaderInfo`  
_L10-16_
- L11 _public member_ `SYMS_U32 index_size;`
- L12 _public member_ `SYMS_U32 block_size;`
- L13 _public member_ `SYMS_U32 block_count;`
- L14 _public member_ `SYMS_U32 directory_size;`
- L15 _public member_ `SYMS_U32 directory_super_map;`

#### struct `SYMS_MsfStreamInfo`  
`typedef struct SYMS_MsfStreamInfo`  
_L18-22_
- L19 _public member_ `SYMS_MsfStreamNumber sn;`
- L20 _public member_ `SYMS_U8 *stream_indices;`
- L21 _public member_ `SYMS_U32 size;`

#### struct `SYMS_MsfRange`  
`typedef struct SYMS_MsfRange`  
_L24-28_
- L25 _public member_ `SYMS_MsfStreamNumber sn;`
- L26 _public member_ `SYMS_U32 off;`
- L27 _public member_ `SYMS_U32 size;`

#### struct `SYMS_MsfAccelStreamInfo`  
`typedef struct SYMS_MsfAccelStreamInfo`  
_L33-36_
- L34 _public member_ `SYMS_U8 *stream_indices;`
- L35 _public member_ `SYMS_U32 size;`

#### struct `SYMS_MsfAccel`  
`typedef struct SYMS_MsfAccel`  
_L38-42_
- L39 _public member_ `SYMS_MsfHeaderInfo header;`
- L40 _public member_ `SYMS_U32 stream_count;`
- L41 _public member_ `SYMS_MsfAccelStreamInfo *stream_info;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_MSF_PARSER_H`
- L16 _typedef_ `} SYMS_MsfHeaderInfo;`
- L22 _typedef_ `} SYMS_MsfStreamInfo;`
- L28 _typedef_ `} SYMS_MsfRange;`
- L36 _typedef_ `} SYMS_MsfAccelStreamInfo;`
- L42 _typedef_ `} SYMS_MsfAccel;`
- L47 _prototype_ `SYMS_MsfHeaderInfo syms_msf_header_info_from_data_slow(SYMS_String8 data);`
- L52 _prototype_ `SYMS_MsfAccel* syms_msf_accel_from_data(SYMS_Arena *arena, SYMS_String8 data);`
- L53 _prototype_ `SYMS_MsfAccel* syms_msf_deep_copy(SYMS_Arena *arena, SYMS_MsfAccel *msf);`
- L55 _prototype_ `SYMS_MsfAccel* syms_msf_accel_dummy_from_raw_data(SYMS_Arena *arena, SYMS_String8 data);`
- L60 _prototype_ `SYMS_MsfHeaderInfo syms_msf_header_info_from_msf(SYMS_MsfAccel *msf);`
- L62 _prototype_ `SYMS_U32 syms_msf_get_stream_count(SYMS_MsfAccel *msf);`
- L64 _prototype_ `SYMS_MsfStreamInfo syms_msf_stream_info_from_sn(SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn);`
- L66 _prototype_ `SYMS_B32 syms_msf_bounds_check(SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn, SYMS_U32 off);`
- L67 _prototype_ `SYMS_B32 syms_msf_read(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn, SYMS_U32 off, SYMS_U32 size, void *out);`
- L70 _macro_ `#define syms_msf_read_struct(d,a,sn,off,p) syms_msf_read((d),(a),(sn),(off),sizeof(*(p)),(p))`
- L72 _prototype_ `SYMS_MsfRange syms_msf_make_range(SYMS_MsfStreamNumber sn, SYMS_U32 off, SYMS_U32 len);`
- L73 _prototype_ `SYMS_MsfRange syms_msf_range_from_sn(SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn);`
- L74 _prototype_ `SYMS_MsfRange syms_msf_sub_range(SYMS_MsfRange range, SYMS_U32 off, SYMS_U32 size);`
- L75 _prototype_ `SYMS_MsfRange syms_msf_sub_range_from_off_range(SYMS_MsfRange range, SYMS_U32Range off_range);`
- L80 _prototype_ `SYMS_B32 syms_msf_bounds_check_in_range(SYMS_MsfRange range, SYMS_U32 off);`
- L81 _prototype_ `SYMS_B32 syms_msf_read_in_range(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range, SYMS_U32 off, SYMS_U32 size, void *out);`
- L84 _prototype_ `SYMS_String8 syms_msf_read_whole_range(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range);`
- L87 _macro_ `#define syms_msf_read_struct_in_range(d,a,rn,off,p) syms_msf_read_in_range((d),(a),(rn),(off),sizeof(*(p)),(p))`
- L89 _prototype_ `SYMS_String8 syms_msf_read_zstring_in_range(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range, SYMS_U32 off);`

### `Source/Runtime/SymsLib/syms/core/pdb/syms_pdb.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L23-34_

#### struct `SYMS_PdbOffAndSize`  
`typedef struct SYMS_PdbOffAndSize`  
_L39-42_
- L40 _public member_ `SYMS_U32 off;`
- L41 _public member_ `SYMS_U32 size;`

#### enum `SYMS_PdbFixedStream`  
`typedef enum SYMS_PdbFixedStream`  
_L44-49_
- L45 _public enumerator_ `SYMS_PdbFixedStream_PDB = 1`
- L46 _public enumerator_ `SYMS_PdbFixedStream_TPI = 2`
- L47 _public enumerator_ `SYMS_PdbFixedStream_DBI = 3`
- L48 _public enumerator_ `SYMS_PdbFixedStream_IPI = 4`

#### enum `SYMS_PdbNamedStream`  
`typedef enum SYMS_PdbNamedStream`  
_L53-58_
- L54 _public enumerator_ `SYMS_PdbNamedStream_HEADER_BLOCK`
- L55 _public enumerator_ `SYMS_PdbNamedStream_STRTABLE`
- L56 _public enumerator_ `SYMS_PdbNamedStream_LINK_INFO`
- L57 _public enumerator_ `SYMS_PdbNamedStream_COUNT`

#### struct `SYMS_PdbInfoHeader`  
`typedef struct SYMS_PdbInfoHeader`  
_L60-64_
- L61 _public member_ `SYMS_PdbVersion version;`
- L62 _public member_ `SYMS_U32 time;`
- L63 _public member_ `SYMS_U32 age;`

#### enum `(anonymous)`  
`enum`  
_L71-73_

#### struct `SYMS_PdbDbiStrTableHeader`  
`typedef struct SYMS_PdbDbiStrTableHeader`  
_L75-78_
- L76 _public member_ `SYMS_U32 magic;`
- L77 _public member_ `SYMS_U32 version;`

#### enum `(anonymous)`  
`enum`  
_L83-96_

#### enum `(anonymous)`  
`enum`  
_L99-101_

#### enum `(anonymous)`  
`enum`  
_L104-110_

#### enum `(anonymous)`  
`enum`  
_L121-125_

#### struct `SYMS_PdbDbiHeader`  
`typedef struct SYMS_PdbDbiHeader`  
_L127-154_
- L128 _public member_ `SYMS_PdbDbiHeaderSig sig;`
- L129 _public member_ `SYMS_PdbDbiVersion version;`
- L130 _public member_ `SYMS_U32 age;`
- L131 _public member_ `SYMS_MsfStreamNumber gsi_sn;`
- L132 _public member_ `SYMS_PdbDbiBuildNumber build_number;`
- L134 _public member_ `SYMS_MsfStreamNumber psi_sn;`
- L135 _public member_ `SYMS_U16 pdb_version;`
- L137 _public member_ `SYMS_MsfStreamNumber sym_sn;`
- L138 _public member_ `SYMS_U16 pdb_version2;`
- L140 _public member_ `SYMS_U32 module_info_size;`
- L141 _public member_ `SYMS_U32 sec_con_size;`
- L142 _public member_ `SYMS_U32 sec_map_size;`
- L143 _public member_ `SYMS_U32 file_info_size;`
- L145 _public member_ `SYMS_U32 tsm_size;`
- L146 _public member_ `SYMS_U32 mfc_index;`
- L147 _public member_ `SYMS_U32 dbg_header_size;`
- L148 _public member_ `SYMS_U32 ec_info_size;`
- L150 _public member_ `SYMS_PdbDbiHeaderFlags flags;`
- L151 _public member_ `SYMS_U16 machine;`
- L153 _public member_ `SYMS_U32 reserved;`

#### enum `SYMS_PdbDbiRange`  
`typedef enum SYMS_PdbDbiRange`  
_L157-166_
- desc: NOTE(allen): This is not "literally" defined by the format.
- L158 _public enumerator_ `SYMS_PdbDbiRange_ModuleInfo`
- L159 _public enumerator_ `SYMS_PdbDbiRange_SecCon`
- L160 _public enumerator_ `SYMS_PdbDbiRange_SecMap`
- L161 _public enumerator_ `SYMS_PdbDbiRange_FileInfo`
- L162 _public enumerator_ `SYMS_PdbDbiRange_TSM`
- L163 _public enumerator_ `SYMS_PdbDbiRange_EcInfo`
- L164 _public enumerator_ `SYMS_PdbDbiRange_DbgHeader`
- L165 _public enumerator_ `SYMS_PdbDbiRange_COUNT`

#### struct `SYMS_PdbDbiSectionContrib40`  
`typedef struct SYMS_PdbDbiSectionContrib40`  
_L176-182_
- desc: any other version number
- L177 _public member_ `SYMS_CvSectionIndex sec;`
- L178 _public member_ `SYMS_U32 sec_off;`
- L179 _public member_ `SYMS_U32 size;`
- L180 _public member_ `SYMS_U32 flags;`
- L181 _public member_ `SYMS_PdbModIndex mod;`

#### struct `SYMS_PdbDbiSectionContrib`  
`typedef struct SYMS_PdbDbiSectionContrib`  
_L185-189_
- desc: SYMS_PdbDbiPdbDbiSectionContribVersion_1
- L186 _public member_ `SYMS_PdbDbiSectionContrib40 base;`
- L187 _public member_ `SYMS_U32 data_crc;`
- L188 _public member_ `SYMS_U32 reloc_crc;`

#### struct `SYMS_PdbDbiSectionContrib2`  
`typedef struct SYMS_PdbDbiSectionContrib2`  
_L192-197_
- desc: SYMS_PdbDbiPdbDbiSectionContribVersion_2
- L193 _public member_ `SYMS_PdbDbiSectionContrib40 base;`
- L194 _public member_ `SYMS_U32 data_crc;`
- L195 _public member_ `SYMS_U32 reloc_crc;`
- L196 _public member_ `SYMS_U32 sec_coff;`

#### struct `SYMS_PdbDbiCompUnitHeader`  
`typedef struct SYMS_PdbDbiCompUnitHeader`  
_L201-221_
- desc: TODO(allen): changes when sc version changes to 40. (see MODI50) (MODI_60_Persist)
- L202 _public member_ `SYMS_U8 unused[4];`
- L203 _public member_ `SYMS_PdbDbiSectionContrib section_contribution;`
- L205 _public member_ `SYMS_U16 flags;` — TODO(allen): type info on these flags.
- L207 _public member_ `SYMS_MsfStreamNumber sn;`
- L208 _public member_ `SYMS_U32 symbol_bytes;`
- L209 _public member_ `SYMS_U32 c11_lines_size;`
- L210 _public member_ `SYMS_U32 c13_lines_size;`
- L212 _public member_ `SYMS_U16 num_contrib_files;`
- L213 _public member_ `SYMS_U8 padding1[2];`
- L214 _public member_ `SYMS_U32 file_names_offset;`
- L216 _public member_ `SYMS_PdbStringIndex src_file;`
- L217 _public member_ `SYMS_PdbStringIndex pdb_file;`

#### enum `SYMS_PdbCompUnitRange`  
`typedef enum SYMS_PdbCompUnitRange`  
_L224-229_
- desc: NOTE(allen): This is not "literally" defined by the format.
- L225 _public enumerator_ `SYMS_PdbCompUnitRange_Symbols`
- L226 _public enumerator_ `SYMS_PdbCompUnitRange_C11`
- L227 _public enumerator_ `SYMS_PdbCompUnitRange_C13`
- L228 _public enumerator_ `SYMS_PdbCompUnitRange_COUNT`

#### enum `(anonymous)`  
`enum`  
_L237-245_

#### struct `SYMS_PdbTpiHeader`  
`typedef struct SYMS_PdbTpiHeader`  
_L247-263_
- L249 _public member_ `SYMS_PdbTpiVersion version;` — (PDB/dbi/tpi.h: HDR)
- L250 _public member_ `SYMS_U32 header_size;`
- L251 _public member_ `SYMS_U32 ti_lo;`
- L252 _public member_ `SYMS_U32 ti_hi;`
- L253 _public member_ `SYMS_U32 types_size;`
- L256 _public member_ `SYMS_MsfStreamNumber hash_sn;` — (PDB/dbi/tpi.h: PdbTpiHash)
- L257 _public member_ `SYMS_MsfStreamNumber hash_sn_aux;`
- L258 _public member_ `SYMS_U32 hash_key_size;`
- L259 _public member_ `SYMS_U32 hash_bucket_count;`
- L260 _public member_ `SYMS_PdbOffAndSize hash_vals;`
- L261 _public member_ `SYMS_PdbOffAndSize ti_off;`
- L262 _public member_ `SYMS_PdbOffAndSize hash_adj;`

#### struct `SYMS_PdbTpiOffHint`  
`typedef struct SYMS_PdbTpiOffHint`  
_L265-268_
- L266 _public member_ `SYMS_CvTypeIndex ti;`
- L267 _public member_ `SYMS_U32 off;`

#### enum `(anonymous)`  
`enum`  
_L276-278_

#### enum `(anonymous)`  
`enum`  
_L281-283_

#### struct `SYMS_PdbGsiHeader`  
`typedef struct SYMS_PdbGsiHeader`  
_L285-290_
- L286 _public member_ `SYMS_PdbGsiSignature sig;`
- L287 _public member_ `SYMS_PdbGsiVersion ver;`
- L288 _public member_ `SYMS_U32 hr_len;`
- L289 _public member_ `SYMS_U32 num_buckets;`

#### struct `SYMS_PdbGsiHashRecord`  
`typedef struct SYMS_PdbGsiHashRecord`  
_L292-295_
- L293 _public member_ `SYMS_U32 off;` — Offset in the symbol record stream
- L294 _public member_ `SYMS_U32 cref;`

#### struct `SYMS_PdbGsiHrOffsetCalc`  
`typedef struct SYMS_PdbGsiHrOffsetCalc`  
_L299-303_
- desc: TODO(allen): ? NOTE(nick): This is a crutch that helps serialize in-memory GSI buckets that use 64bit pointers for next HR.
- L300 _public member_ `SYMS_U32 next;`
- L301 _public member_ `SYMS_U32 off;`
- L302 _public member_ `SYMS_U32 cref;`

#### struct `SYMS_PdbPsiHeader`  
`typedef struct SYMS_PdbPsiHeader`  
_L305-314_
- L306 _public member_ `SYMS_U32 sym_hash_size;`
- L307 _public member_ `SYMS_U32 addr_map_size;`
- L308 _public member_ `SYMS_U32 thunk_count;`
- L309 _public member_ `SYMS_U32 thunk_size;`
- L310 _public member_ `SYMS_CvSectionIndex isec_thunk_table;`
- L311 _public member_ `SYMS_U8 padding[2];`
- L312 _public member_ `SYMS_U32 sec_thunk_tabl_off;`
- L313 _public member_ `SYMS_U32 sec_count;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_PDB_H`
- L22 _typedef_ `typedef SYMS_U32 SYMS_PdbVersion;`
- L24 _enumerator_ `SYMS_PdbVersion_VC2 = 19941610` (scope `__anon44f4180a0103`)
- L25 _enumerator_ `SYMS_PdbVersion_VC4 = 19950623` (scope `__anon44f4180a0103`)
- L26 _enumerator_ `SYMS_PdbVersion_VC41 = 19950814` (scope `__anon44f4180a0103`)
- L27 _enumerator_ `SYMS_PdbVersion_VC50 = 19960307` (scope `__anon44f4180a0103`)
- L28 _enumerator_ `SYMS_PdbVersion_VC98 = 19970604` (scope `__anon44f4180a0103`)
- L29 _enumerator_ `SYMS_PdbVersion_VC70_DEP = 19990604` (scope `__anon44f4180a0103`)
- L30 _enumerator_ `SYMS_PdbVersion_VC70 = 20000404` (scope `__anon44f4180a0103`)
- L31 _enumerator_ `SYMS_PdbVersion_VC80 = 20030901` (scope `__anon44f4180a0103`)
- L32 _enumerator_ `SYMS_PdbVersion_VC110 = 20091201` (scope `__anon44f4180a0103`)
- L33 _enumerator_ `SYMS_PdbVersion_VC140 = 20140508` (scope `__anon44f4180a0103`)
- L36 _typedef_ `typedef SYMS_U16 SYMS_PdbModIndex;`
- L37 _typedef_ `typedef SYMS_U32 SYMS_PdbStringIndex;`
- L42 _typedef_ `} SYMS_PdbOffAndSize;`
- L49 _typedef_ `} SYMS_PdbFixedStream;`
- L58 _typedef_ `} SYMS_PdbNamedStream;`
- L64 _typedef_ `} SYMS_PdbInfoHeader;`
- L72 _enumerator_ `SYMS_PdbDbiStrTableHeader_MAGIC = 0xEFFEEFFE` (scope `__anon44f4180a0203`)
- L78 _typedef_ `} SYMS_PdbDbiStrTableHeader;`
- L82 _typedef_ `typedef SYMS_U32 SYMS_PdbDbiStream;`
- L84 _enumerator_ `SYMS_PdbDbiStream_FPO` (scope `__anon44f4180a0303`)
- L85 _enumerator_ `SYMS_PdbDbiStream_EXCEPTION` (scope `__anon44f4180a0303`)
- L86 _enumerator_ `SYMS_PdbDbiStream_FIXUP` (scope `__anon44f4180a0303`)
- L87 _enumerator_ `SYMS_PdbDbiStream_OMAP_TO_SRC` (scope `__anon44f4180a0303`)
- L88 _enumerator_ `SYMS_PdbDbiStream_OMAP_FROM_SRC` (scope `__anon44f4180a0303`)
- L89 _enumerator_ `SYMS_PdbDbiStream_SECTION_HEADER` (scope `__anon44f4180a0303`)
- L90 _enumerator_ `SYMS_PdbDbiStream_TOKEN_RDI_MAP` (scope `__anon44f4180a0303`)
- L91 _enumerator_ `SYMS_PdbDbiStream_XDATA` (scope `__anon44f4180a0303`)
- L92 _enumerator_ `SYMS_PdbDbiStream_PDATA` (scope `__anon44f4180a0303`)
- L93 _enumerator_ `SYMS_PdbDbiStream_NEW_FPO` (scope `__anon44f4180a0303`)
- L94 _enumerator_ `SYMS_PdbDbiStream_SECTION_HEADER_ORIG` (scope `__anon44f4180a0303`)
- L95 _enumerator_ `SYMS_PdbDbiStream_COUNT` (scope `__anon44f4180a0303`)
- L98 _typedef_ `typedef SYMS_U32 SYMS_PdbDbiHeaderSig;`
- L100 _enumerator_ `SYMS_PdbDbiHeaderSignature_V1 = 0xFFFFFFFF` (scope `__anon44f4180a0403`)
- L103 _typedef_ `typedef SYMS_U32 SYMS_PdbDbiVersion;`
- L105 _enumerator_ `SYMS_PdbDbiVersion_41 = 930803` (scope `__anon44f4180a0503`)
- L106 _enumerator_ `SYMS_PdbDbiVersion_50 = 19960307` (scope `__anon44f4180a0503`)
- L107 _enumerator_ `SYMS_PdbDbiVersion_60 = 19970606` (scope `__anon44f4180a0503`)
- L108 _enumerator_ `SYMS_PdbDbiVersion_70 = 19990903` (scope `__anon44f4180a0503`)
- L109 _enumerator_ `SYMS_PdbDbiVersion_110 = 20091201` (scope `__anon44f4180a0503`)
- L112 _typedef_ `typedef SYMS_U16 SYMS_PdbDbiBuildNumber;`
- L113 _macro_ `#define SYMS_PdbDbiBuildNumberNewFormatFlag 0x8000`
- L114 _macro_ `#define SYMS_PdbDbiBuildNumberMinor(bn) ((bn)&0xFF)`
- L115 _macro_ `#define SYMS_PdbDbiBuildNumberMajor(bn) (((bn) >> 8)&0x7F)`
- L116 _macro_ `#define SYMS_PdbDbiBuildNumberNewFormat(bn) (!!((bn)&SYMS_PdbDbiBuildNumberNewFormatFlag))`
- L117 _macro_ `#define SYMS_PdbDbiBuildNumber(maj, min) \`
- L120 _typedef_ `typedef SYMS_U16 SYMS_PdbDbiHeaderFlags;`
- L122 _enumerator_ `SYMS_PdbDbiHeaderFlag_INCREMENTAL = 0x1` (scope `__anon44f4180a0603`)
- L123 _enumerator_ `SYMS_PdbDbiHeaderFlag_STRIPPED = 0x2` (scope `__anon44f4180a0603`)
- L124 _enumerator_ `SYMS_PdbDbiHeaderFlag_CTYPES = 0x4` (scope `__anon44f4180a0603`)
- L154 _typedef_ `} SYMS_PdbDbiHeader;`
- L166 _typedef_ `} SYMS_PdbDbiRange;`
- L170 _typedef_ `typedef SYMS_U32 SYMS_PdbDbiSectionContribVersion;`
- L172 _macro_ `#define SYMS_PdbDbiSectionContribVersion_1 (0xeffe0000u + 19970605u)` — NOTE(allen): these are too big for an enum on some compilers (they are interpreted as signed)
- L173 _macro_ `#define SYMS_PdbDbiSectionContribVersion_2 (0xeffe0000u + 20140516u)`
- L182 _typedef_ `} SYMS_PdbDbiSectionContrib40;`
- L189 _typedef_ `} SYMS_PdbDbiSectionContrib;`
- L197 _typedef_ `} SYMS_PdbDbiSectionContrib2;`
- L221 _typedef_ `} SYMS_PdbDbiCompUnitHeader;` — char module_name[]; - null terminated char obj_name[]; - null terminated
- L229 _typedef_ `} SYMS_PdbCompUnitRange;`
- L236 _typedef_ `typedef SYMS_U32 SYMS_PdbTpiVersion;`
- L238 _enumerator_ `SYMS_PdbTpiVersion_INTV_VC2 = 920924` (scope `__anon44f4180a0703`)
- L239 _enumerator_ `SYMS_PdbTpiVersion_IMPV40 = 19950410` (scope `__anon44f4180a0703`)
- L240 _enumerator_ `SYMS_PdbTpiVersion_IMPV41 = 19951122` (scope `__anon44f4180a0703`)
- L241 _enumerator_ `SYMS_PdbTpiVersion_IMPV50_INTERIM = 19960307` (scope `__anon44f4180a0703`)
- L242 _enumerator_ `SYMS_PdbTpiVersion_IMPV50 = 19961031` (scope `__anon44f4180a0703`)
- L243 _enumerator_ `SYMS_PdbTpiVersion_IMPV70 = 19990903` (scope `__anon44f4180a0703`)
- L244 _enumerator_ `SYMS_PdbTpiVersion_IMPV80 = 20040203` (scope `__anon44f4180a0703`)
- L263 _typedef_ `} SYMS_PdbTpiHeader;`
- L268 _typedef_ `} SYMS_PdbTpiOffHint;`
- L275 _typedef_ `typedef SYMS_U32 SYMS_PdbGsiSignature;`
- L277 _enumerator_ `SYMS_PdbGsiSignature_Basic = 0xffffffff` (scope `__anon44f4180a0803`)
- L280 _typedef_ `typedef SYMS_U32 SYMS_PdbGsiVersion;`
- L282 _enumerator_ `SYMS_PdbGsiVersion_V70 = 0xeffe0000 + 19990810` (scope `__anon44f4180a0903`)
- L290 _typedef_ `} SYMS_PdbGsiHeader;`
- L295 _typedef_ `} SYMS_PdbGsiHashRecord;`
- L303 _typedef_ `} SYMS_PdbGsiHrOffsetCalc;`
- L314 _typedef_ `} SYMS_PdbPsiHeader;`
- L319 _prototype_ `SYMS_U32 syms_pdb_hashV1(SYMS_String8 string);`

### `Source/Runtime/SymsLib/syms/core/pdb/syms_pdb_parser.h` (Other)


#### struct `SYMS_PdbChain`  
`typedef struct SYMS_PdbChain`  
_L11-14_
- desc: TODO(allen): version of this with optimized memory locality could be pretty useful.
- L12 _public member_ `struct SYMS_PdbChain *next;`
- L13 _public member_ `SYMS_U32 v;`

#### enum `SYMS_PdbPseudoUnit`  
`typedef enum SYMS_PdbPseudoUnit`  
_L16-22_
- L17 _public enumerator_ `SYMS_PdbPseudoUnit_Null`
- L18 _public enumerator_ `SYMS_PdbPseudoUnit_SYM`
- L19 _public enumerator_ `SYMS_PdbPseudoUnit_TPI`
- L20 _public enumerator_ `SYMS_PdbPseudoUnit_COUNT = SYMS_PdbPseudoUnit_TPI`
- L21 _public enumerator_ `SYMS_PdbPseudoUnit_FIRST_COMP_UNIT`

#### struct `SYMS_PdbDbiAccel`  
`typedef struct SYMS_PdbDbiAccel`  
_L27-36_
- L28 _public member_ `SYMS_B16 valid;`
- L29 _public member_ `SYMS_CoffMachineType machine_type;`
- L30 _public member_ `SYMS_MsfStreamNumber gsi_sn;`
- L31 _public member_ `SYMS_MsfStreamNumber psi_sn;`
- L32 _public member_ `SYMS_MsfStreamNumber sym_sn;`
- L34 _public member_ `SYMS_U64 range_off[(SYMS_U64)(SYMS_PdbDbiRange_COUNT) + 1];`
- L35 _public member_ `SYMS_MsfStreamNumber dbg_sn[SYMS_PdbDbiStream_COUNT];`

#### struct `SYMS_PdbInfoSlot`  
`typedef struct SYMS_PdbInfoSlot`  
_L38-42_
- L39 _public member_ `struct SYMS_PdbInfoSlot *next;`
- L40 _public member_ `SYMS_String8 string;`
- L41 _public member_ `SYMS_MsfStreamNumber sn;`

#### struct `SYMS_PdbInfoTable`  
`typedef struct SYMS_PdbInfoTable`  
_L44-48_
- L45 _public member_ `SYMS_PdbInfoSlot *first;`
- L46 _public member_ `SYMS_PdbInfoSlot *last;`
- L47 _public member_ `SYMS_PeGuid auth_guid;`

#### struct `SYMS_PdbNamedStreamArray`  
`typedef struct SYMS_PdbNamedStreamArray`  
_L50-52_
- L51 _public member_ `SYMS_MsfStreamNumber sn[SYMS_PdbNamedStream_COUNT];`

#### struct `SYMS_PdbStrtblAccel`  
`typedef struct SYMS_PdbStrtblAccel`  
_L54-59_
- L55 _public member_ `SYMS_U32 bucket_count;`
- L56 _public member_ `SYMS_MsfStreamNumber sn;`
- L57 _public member_ `SYMS_U32Range strblock;`
- L58 _public member_ `SYMS_U32Range buckets;`

#### struct `SYMS_PdbCompUnit`  
`typedef struct SYMS_PdbCompUnit`  
_L64-73_
- L65 _public member_ `SYMS_MsfStreamNumber sn;`
- L66 _public member_ `SYMS_U64 range_off[(SYMS_U64)(SYMS_PdbCompUnitRange_COUNT) + 1];`
- L68 _public member_ `SYMS_PdbStringIndex src_file;`
- L69 _public member_ `SYMS_PdbStringIndex pdb_file;`
- L71 _public member_ `SYMS_String8 obj_name;`
- L72 _public member_ `SYMS_String8 group_name;`

#### struct `SYMS_PdbCompUnitNode`  
`typedef struct SYMS_PdbCompUnitNode`  
_L75-78_
- L76 _public member_ `struct SYMS_PdbCompUnitNode *next;`
- L77 _public member_ `SYMS_PdbCompUnit comp_unit;`

#### struct `SYMS_PdbUnitSetAccel`  
`typedef struct SYMS_PdbUnitSetAccel`  
_L80-84_
- L81 _public member_ `SYMS_FileFormat format;`
- L82 _public member_ `SYMS_PdbCompUnit **comp_units;`
- L83 _public member_ `SYMS_U64 comp_count;`

#### struct `SYMS_PdbTpiOffRange`  
`typedef struct SYMS_PdbTpiOffRange`  
_L89-93_
- L90 _public member_ `SYMS_U32 first_off;`
- L91 _public member_ `SYMS_CvTypeIndex first_ti;`
- L92 _public member_ `SYMS_CvTypeIndex opl_ti;`

#### struct `SYMS_PdbTpiAccel`  
`typedef struct SYMS_PdbTpiAccel`  
_L95-106_
- L96 _public member_ `SYMS_MsfStreamNumber type_sn;`
- L98 _public member_ `SYMS_PdbTpiOffHint *hints;` — TODO(allen): Stop playing this TPI hints game.
- L99 _public member_ `SYMS_PdbChain **buckets;`
- L100 _public member_ `SYMS_U32 bucket_count;`
- L101 _public member_ `SYMS_U64 count;`
- L102 _public member_ `SYMS_U32 base_off;`
- L103 _public member_ `SYMS_CvTypeIndex first_ti;`
- L104 _public member_ `SYMS_CvTypeIndex opl_ti;`
- L105 _public member_ `SYMS_U32 *off;`

#### struct `SYMS_PdbGsiAccel`  
`typedef struct SYMS_PdbGsiAccel`  
_L111-114_
- L112 _public member_ `SYMS_PdbChain **buckets;`
- L113 _public member_ `SYMS_U32 bucket_count;`

#### struct `SYMS_PdbFileAccel`  
`typedef struct SYMS_PdbFileAccel`  
_L119-122_
- L120 _public member_ `SYMS_FileFormat format;`
- L121 _public member_ `SYMS_MsfAccel *msf;`

#### struct `SYMS_PdbDbgAccel`  
`typedef struct SYMS_PdbDbgAccel`  
_L124-152_
- L125 _public member_ `SYMS_FileFormat format;`
- L128 _public member_ `SYMS_MsfAccel *msf;` — MSF view into the data
- L131 _public member_ `SYMS_PdbDbiAccel dbi;` — specific to true PDB file
- L132 _public member_ `SYMS_PdbNamedStreamArray named;`
- L133 _public member_ `SYMS_PdbStrtblAccel strtbl;`
- L134 _public member_ `SYMS_PdbTpiAccel tpi;`
- L135 _public member_ `SYMS_PdbTpiAccel ipi;`
- L136 _public member_ `SYMS_PdbGsiAccel gsi;`
- L137 _public member_ `SYMS_PdbGsiAccel psi;`
- L138 _public member_ `SYMS_PeGuid auth_guid;`
- L143 _public member_ `SYMS_Arch arch;` — arch
- L146 _public member_ `SYMS_UnitID type_uid;` — type uid
- L149 _public member_ `SYMS_MsfRange section_data_range;` — section data
- L150 _public member_ `SYMS_U64 *section_voffs;`
- L151 _public member_ `SYMS_U64 section_count;`

#### struct `SYMS_PdbMapAccel`  
`typedef struct SYMS_PdbMapAccel`  
_L157-160_
- L158 _public member_ `SYMS_FileFormat format;`
- L159 _public member_ `SYMS_UnitID uid;`

#### struct `SYMS_PdbLinkMapAccel`  
`typedef struct SYMS_PdbLinkMapAccel`  
_L162-164_
- L163 _public member_ `SYMS_FileFormat format;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_PDB_PARSER_H`
- L14 _typedef_ `} SYMS_PdbChain;`
- L22 _typedef_ `SYMS_PdbPseudoUnit_TPI, SYMS_PdbPseudoUnit_COUNT = SYMS_PdbPseudoUnit_TPI, SYMS_PdbPseudoUnit_FIRST_COMP_UNIT, } SYMS_PdbPseudoUnit;`
- L36 _typedef_ `} SYMS_PdbDbiAccel;`
- L42 _typedef_ `} SYMS_PdbInfoSlot;`
- L48 _typedef_ `} SYMS_PdbInfoTable;`
- L52 _typedef_ `} SYMS_PdbNamedStreamArray;`
- L59 _typedef_ `} SYMS_PdbStrtblAccel;`
- L73 _typedef_ `} SYMS_PdbCompUnit;`
- L78 _typedef_ `} SYMS_PdbCompUnitNode;`
- L84 _typedef_ `} SYMS_PdbUnitSetAccel;`
- L93 _typedef_ `} SYMS_PdbTpiOffRange;`
- L106 _typedef_ `} SYMS_PdbTpiAccel;`
- L114 _typedef_ `} SYMS_PdbGsiAccel;`
- L122 _typedef_ `} SYMS_PdbFileAccel;`
- L152 _typedef_ `} SYMS_PdbDbgAccel;`
- L160 _typedef_ `} SYMS_PdbMapAccel;`
- L164 _typedef_ `} SYMS_PdbLinkMapAccel;`
- L169 _macro_ `#define SYMS_CV_SYMBOL_ALIGN_IN_PDB 4`
- L175 _prototype_ `SYMS_PdbTpiOffRange syms_pdb_tpi__hint_from_index(SYMS_PdbTpiAccel *tpi, SYMS_CvTypeIndex ti);` — - tpi accel helpers
- L176 _prototype_ `void syms_pdb_tpi__fill_off_range(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_PdbTpiAccel *tpi, SYMS_PdbTpiOffRange *fill);`
- L180 _prototype_ `SYMS_PdbTpiAccel syms_pdb_tpi_accel_from_sn(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn);` — - tpi accel
- L182 _prototype_ `SYMS_U32 syms_pdb_tpi_off_from_ti(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_PdbTpiAccel *tpi, SYMS_CvTypeIndex ti);`
- L184 _prototype_ `SYMS_U32 syms_pdb_tpi_base_off(SYMS_PdbTpiAccel *tpi);`
- L185 _prototype_ `SYMS_MsfRange syms_pdb_tpi_range(SYMS_MsfAccel *msf, SYMS_PdbTpiAccel *tpi);`
- L188 _prototype_ `SYMS_USIDList syms_pdb_types_from_name(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_String8 name);` — - tpi name lookups
- L196 _prototype_ `SYMS_PdbGsiAccel syms_pdb_gsi_accel_from_range(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfRange range);`
- L198 _prototype_ `SYMS_MsfRange syms_pdb_gsi_part_from_psi_range(SYMS_MsfRange psi_range);`
- L200 _prototype_ `SYMS_USIDList syms_pdb_symbols_from_name(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_PdbGsiAccel *gsi, SYMS_CvUnitAccel *unit, SYMS_String8 name);`
- L209 _prototype_ `SYMS_PdbDbiAccel syms_pdb_dbi_from_msf(SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn);` — pdb specific parsing
- L211 _prototype_ `SYMS_MsfRange syms_pdb_dbi_sub_range(SYMS_PdbDbiAccel *dbi, SYMS_MsfStreamNumber sn, SYMS_PdbDbiRange n);`
- L213 _prototype_ `SYMS_MsfRange syms_pdb_dbi_stream(SYMS_MsfAccel *msf, SYMS_PdbDbiAccel *dbi, SYMS_PdbDbiStream n);`
- L215 _prototype_ `SYMS_PdbInfoTable syms_pdb_parse_info(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf);`
- L216 _prototype_ `SYMS_PdbNamedStreamArray syms_pdb_named_stream_array(SYMS_PdbInfoTable *table);`
- L217 _prototype_ `SYMS_PdbStrtblAccel syms_pdb_dbi_parse_strtbl(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_MsfStreamNumber sn);`
- L221 _prototype_ `SYMS_String8 syms_pdb_strtbl_string_from_off(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_U32 off);` — pdb specific api
- L223 _prototype_ `SYMS_String8 syms_pdb_strtbl_string_from_index(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_PdbStringIndex n);`
- L227 _prototype_ `SYMS_PdbFileAccel* syms_pdb_file_accel_from_data(SYMS_Arena *arena, SYMS_String8 data);` — main api
- L228 _prototype_ `SYMS_PdbDbgAccel* syms_pdb_dbg_accel_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbFileAccel *file);`
- L236 _prototype_ `SYMS_Arch syms_pdb_arch_from_dbg(SYMS_PdbDbgAccel *dbg);` — main api
- L242 _prototype_ `SYMS_ExtMatchKey syms_pdb_ext_match_key_from_dbg(SYMS_String8 data, SYMS_PdbDbgAccel *dbg);`
- L249 _prototype_ `SYMS_CoffSectionHeader syms_pdb_coff_section_header(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_U64 n);` — pdb specific
- L251 _prototype_ `SYMS_U64 syms_pdb_voff_from_section_n(SYMS_PdbDbgAccel *dbg, SYMS_U64 n);`
- L254 _prototype_ `SYMS_SecInfoArray syms_pdb_sec_info_array_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg);` — main api
- L261 _prototype_ `SYMS_PdbCompUnit* syms_pdb_comp_unit_from_id(SYMS_PdbUnitSetAccel *unit_set, SYMS_UnitID id);` — pdb specific
- L262 _prototype_ `SYMS_MsfRange syms_pdb_msf_range_from_comp_unit(SYMS_PdbCompUnit *unit, SYMS_PdbCompUnitRange n);`
- L266 _prototype_ `SYMS_PdbUnitSetAccel*syms_pdb_unit_set_accel_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg);` — main api
- L268 _prototype_ `SYMS_U64 syms_pdb_unit_count_from_set(SYMS_PdbUnitSetAccel *unit_set);`
- L269 _prototype_ `SYMS_UnitInfo syms_pdb_unit_info_from_uid(SYMS_PdbUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L271 _prototype_ `SYMS_UnitNames syms_pdb_unit_names_from_uid(SYMS_Arena *arena, SYMS_PdbUnitSetAccel *unit_set, SYMS_UnitID uid);`
- L275 _prototype_ `SYMS_UnitRangeArray syms_pdb_unit_ranges_from_set(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_PdbUnitSetAccel *unit_set);`
- L279 _prototype_ `SYMS_UnitFeatures syms_pdb_unit_features_from_number(SYMS_PdbUnitSetAccel *unit_set, SYMS_U64 n);`
- L286 _prototype_ `SYMS_CvUnitAccel* syms_pdb_pub_sym_accel_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg);` — cv parse
- L289 _prototype_ `SYMS_CvUnitAccel* syms_pdb_leaf_accel_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_UnitID uid);`
- L292 _prototype_ `SYMS_TypeInfo syms_pdb_leaf_type_info_from_id(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);`
- L294 _prototype_ `SYMS_ConstInfo syms_pdb_leaf_const_info_from_id(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);`
- L298 _prototype_ `SYMS_CvUnitAccel*syms_pdb_unit_accel_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_PdbUnitSetAccel *set, SYMS_UnitID uid);` — main api
- L302 _prototype_ `SYMS_UnitID syms_pdb_tls_var_uid_from_dbg(SYMS_PdbDbgAccel *dbg);`
- L303 _prototype_ `SYMS_SymbolIDArray syms_pdb_tls_var_sid_array_from_unit(SYMS_Arena *arena, SYMS_CvUnitAccel *unit);`
- L305 _prototype_ `SYMS_U64 syms_pdb_symbol_count_from_unit(SYMS_CvUnitAccel *unit);`
- L307 _prototype_ `SYMS_SymbolKind syms_pdb_symbol_kind_from_sid(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);`
- L310 _prototype_ `SYMS_TypeInfo syms_pdb_type_info_from_sid(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L312 _prototype_ `SYMS_ConstInfo syms_pdb_const_info_from_id(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);`
- L319 _prototype_ `SYMS_USID syms_pdb_sym_type_from_var_id(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);` — cv parse
- L322 _prototype_ `SYMS_U64 syms_pdb_sym_voff_from_var_sid(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L325 _prototype_ `SYMS_RegSection syms_pdb_reg_section_from_x86_reg(SYMS_CvReg cv_reg);`
- L326 _prototype_ `SYMS_RegSection syms_pdb_reg_section_from_x64_reg(SYMS_CvReg cv_reg);`
- L327 _prototype_ `SYMS_RegSection syms_pdb_reg_section_from_arch_reg(SYMS_Arch arch, SYMS_CvReg cv_reg);`
- L329 _prototype_ `SYMS_RegSection syms_pdb_reg_section_from_framepointer(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_MsfRange range, SYMS_CvStub *framepointer_stub);`
- L334 _prototype_ `SYMS_USID syms_pdb_type_from_var_id(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);` — main api
- L337 _prototype_ `SYMS_U64 syms_pdb_voff_from_var_sid(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L340 _prototype_ `SYMS_Location syms_pdb_location_from_var_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L343 _prototype_ `SYMS_LocRangeArray syms_pdb_location_ranges_from_var_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L347 _prototype_ `SYMS_Location syms_pdb_location_from_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_LocID loc_id);`
- L356 _prototype_ `void syms_pdb__field_list_parse(SYMS_Arena *arena, SYMS_String8 data, SYMS_MsfAccel *msf, SYMS_CvUnitAccel *unit, SYMS_U32 index, SYMS_PdbMemStubList *out);` — cv parse
- L361 _prototype_ `SYMS_CvMemsAccel*syms_pdb_mems_accel_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);` — main api
- L365 _prototype_ `SYMS_U64 syms_pdb_mem_count_from_mems(SYMS_CvMemsAccel *mems);`
- L366 _prototype_ `SYMS_MemInfo syms_pdb_mem_info_from_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_CvMemsAccel *mems, SYMS_U64 n);`
- L370 _prototype_ `SYMS_USID syms_pdb_type_from_mem_number(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_CvMemsAccel *mems, SYMS_U64 n);`
- L374 _prototype_ `SYMS_SigInfo syms_pdb_sig_info_from_mem_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_CvMemsAccel*mems, SYMS_U64 n);`
- L378 _prototype_ `SYMS_EnumMemberArray syms_pdb_enum_member_array_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L387 _prototype_ `SYMS_UnitIDAndSig syms_pdb_proc_sig_handle_from_id(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);`
- L389 _prototype_ `SYMS_SigInfo syms_pdb_sig_info_from_handle(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SigHandle handle);`
- L393 _prototype_ `SYMS_U64RangeArray syms_pdb_scope_vranges_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID sid);`
- L396 _prototype_ `SYMS_SymbolIDArray syms_pdb_scope_children_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);`
- L404 _prototype_ `SYMS_SigInfo syms_pdb_sig_info_from_sig_index(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_CvTypeIndex index);` — pdb specific helper
- L408 _prototype_ `SYMS_SigInfo syms_pdb_sig_info_from_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_SymbolID id);` — main api
- L416 _prototype_ `SYMS_String8 syms_pdb_file_name_from_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_PdbUnitSetAccel *unit_set, SYMS_UnitID uid, SYMS_FileID id);` — main api
- L420 _prototype_ `SYMS_LineParseOut syms_pdb_line_parse_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_PdbUnitSetAccel *set, SYMS_UnitID uid);`
- L428 _prototype_ `SYMS_PdbMapAccel* syms_pdb_type_map_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg);` — main api
- L429 _prototype_ `SYMS_PdbMapAccel* syms_pdb_unmangled_symbol_map_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg);`
- L431 _prototype_ `SYMS_UnitID syms_pdb_partner_uid_from_map(SYMS_PdbMapAccel *map);`
- L432 _prototype_ `SYMS_USIDList syms_pdb_usid_list_from_string(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit, SYMS_PdbMapAccel *map, SYMS_String8 string);`
- L440 _prototype_ `SYMS_UnitID syms_pdb_link_names_uid(void);` — main api
- L442 _prototype_ `SYMS_PdbLinkMapAccel* syms_pdb_link_map_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg);`
- L444 _prototype_ `SYMS_U64 syms_pdb_voff_from_link_name(SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_PdbLinkMapAccel *map, SYMS_CvUnitAccel *link_unit, SYMS_String8 name);`
- L447 _prototype_ `SYMS_LinkNameRecArray syms_pdb_link_name_array_from_unit(SYMS_Arena *arena, SYMS_String8 data, SYMS_PdbDbgAccel *dbg, SYMS_CvUnitAccel *unit);`
- L453 _prototype_ `SYMS_TypeKind syms_pdb_type_kind_from_cv_pointer_mode(SYMS_CvPointerMode mode);`
- L454 _prototype_ `SYMS_TypeModifiers syms_pdb_modifier_from_cv_pointer_attribs(SYMS_CvPointerAttribs attribs);`
- L455 _prototype_ `SYMS_TypeModifiers syms_pdb_modifier_from_cv_modifier_flags(SYMS_CvModifierFlags flags);`
- L456 _prototype_ `SYMS_CallConvention syms_pdb_call_convention_from_cv_call_kind(SYMS_CvCallKind kind);`

### `Source/Runtime/SymsLib/syms/core/pe/syms_coff.h` (Other)


#### struct `SYMS_CoffHeaderBigObj`  
`typedef struct SYMS_CoffHeaderBigObj`  
_L21-32_
- L22 _public member_ `SYMS_U16 sig1;` — SYMS_CoffMachineType_UNKNOWN
- L23 _public member_ `SYMS_U16 sig2;` — SYMS_U16_MAX
- L24 _public member_ `SYMS_U16 version;`
- L25 _public member_ `SYMS_U16 machine;`
- L26 _public member_ `SYMS_U32 time_stamp;`
- L27 _public member_ `SYMS_U8 magic[16];`
- L28 _public member_ `SYMS_U32 unused[4];`
- L29 _public member_ `SYMS_U32 section_count;`
- L30 _public member_ `SYMS_U32 pointer_to_symbol_table;`
- L31 _public member_ `SYMS_U32 number_of_symbols;`

#### union `SYMS_CoffSymbolName`  
`typedef union SYMS_CoffSymbolName`  
_L43-52_
- L44 _public member_ `SYMS_U8 short_name[8];`
- L51 _public member_ `} long_name;`

#### struct `SYMS_CoffSymbolName::(anonymous)`  
`struct`  
_L45-51_

#### struct `SYMS_CoffSymbol16`  
`typedef struct SYMS_CoffSymbol16`  
_L54-67_
- L55 _public member_ `SYMS_CoffSymbolName name;`
- L56 _public member_ `SYMS_U32 value;`
- L57 _public member_ `SYMS_U16 section_number;`
- L64 _public member_ `} type;`
- L65 _public member_ `SYMS_CoffSymStorageClass storage_class;`
- L66 _public member_ `SYMS_U8 aux_symbol_count;`

#### union `SYMS_CoffSymbol16::(anonymous)`  
`union`  
_L58-64_

#### struct `SYMS_CoffSymbol16::__anon7223b931020a::(anonymous)`  
`struct`  
_L59-62_

#### struct `SYMS_CoffSymbol32`  
`typedef struct SYMS_CoffSymbol32`  
_L69-82_
- L70 _public member_ `SYMS_CoffSymbolName name;`
- L71 _public member_ `SYMS_U32 value;`
- L72 _public member_ `SYMS_U32 section_number;`
- L79 _public member_ `} type;`
- L80 _public member_ `SYMS_CoffSymStorageClass storage_class;`
- L81 _public member_ `SYMS_U8 aux_symbol_count;`

#### union `SYMS_CoffSymbol32::(anonymous)`  
`union`  
_L73-79_

#### struct `SYMS_CoffSymbol32::__anon7223b931040a::(anonymous)`  
`struct`  
_L74-77_

#### struct `SYMS_CoffReloc`  
`typedef struct SYMS_CoffReloc`  
_L85-89_
- desc: specifies how section data should be modified when placed in the image file.
- L86 _public member_ `SYMS_U32 apply_off;` — section relative offset where relocation is placed
- L87 _public member_ `SYMS_U32 isymbol;` — zero based index into coff symbol table
- L88 _public member_ `SYMS_U16 type;` — relocation type that depends on the arch

#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_COFF_H`
- L14 _macro_ `#define SYMS_COFF_MIN_BIG_OBJ_VERSION 2`
- L16 _variable_ `SYMS_GLOBAL SYMS_U8 syms_coff_big_obj_magic[] = { 0xC7,0xA1,0xBA,0xD1,0xEE,0xBA,0xA9,0x4B, 0xAF,0x20,0xFA,0xF6,0x6A,0xA4,0xDC,0xB8, };`
- L32 _typedef_ `} SYMS_CoffHeaderBigObj;`
- L37 _macro_ `#define SYMS_COFF_SYMBOL_UNDEFINED_SECTION 0` — Special values for section number field in coff symbol
- L38 _macro_ `#define SYMS_COFF_SYMBOL_ABS_SECTION ((SYMS_U32)-1)`
- L39 _macro_ `#define SYMS_COFF_SYMBOL_DEBUG_SECTION ((SYMS_U32)-2)`
- L40 _macro_ `#define SYMS_COFF_SYMBOL_ABS_SECTION_16 ((SYMS_U16)-1)`
- L41 _macro_ `#define SYMS_COFF_SYMBOL_DEBUG_SECTION_16 ((SYMS_U16)-2)`
- L49 _member_ `SYMS_U32 zeroes;` (scope `SYMS_CoffSymbolName::__anon7223b9310108`) — if this field is filled with zeroes we have a long name, which means name is stored in the string table and we need to use the offset to look it up...
- L50 _member_ `SYMS_U32 string_table_offset;` (scope `SYMS_CoffSymbolName::__anon7223b9310108`)
- L52 _typedef_ `} SYMS_CoffSymbolName;`
- L60 _member_ `SYMS_CoffSymDType msb;` (scope `SYMS_CoffSymbol16::__anon7223b931020a::__anon7223b9310308`)
- L61 _member_ `SYMS_CoffSymType lsb;` (scope `SYMS_CoffSymbol16::__anon7223b931020a::__anon7223b9310308`)
- L62 _member_ `} u;` (scope `SYMS_CoffSymbol16::__anon7223b931020a`)
- L63 _member_ `SYMS_U16 v;` (scope `SYMS_CoffSymbol16::__anon7223b931020a`)
- L67 _typedef_ `} SYMS_CoffSymbol16;`
- L75 _member_ `SYMS_CoffSymDType msb;` (scope `SYMS_CoffSymbol32::__anon7223b931040a::__anon7223b9310508`)
- L76 _member_ `SYMS_CoffSymType lsb;` (scope `SYMS_CoffSymbol32::__anon7223b931040a::__anon7223b9310508`)
- L77 _member_ `} u;` (scope `SYMS_CoffSymbol32::__anon7223b931040a`)
- L78 _member_ `SYMS_U16 v;` (scope `SYMS_CoffSymbol32::__anon7223b931040a`)
- L82 _typedef_ `} SYMS_CoffSymbol32;`
- L89 _typedef_ `} SYMS_CoffReloc;`
- L96 _prototype_ `void syms_coff_symbol32_from_coff_symbol16(SYMS_CoffSymbol32 *sym32, SYMS_CoffSymbol16 *sym16);`

### `Source/Runtime/SymsLib/syms/core/pe/syms_pe.h` (Other)


#### struct `SYMS_PeMipsPdata`  
`typedef struct SYMS_PeMipsPdata`  
_L43-49_
- desc: TODO(allen): renaming pass here.
- L44 _public member_ `SYMS_U32 voff_first;`
- L45 _public member_ `SYMS_U32 voff_one_past_last;`
- L46 _public member_ `SYMS_U32 voff_exception_handler;`
- L47 _public member_ `SYMS_U32 voff_exception_handler_data;`
- L48 _public member_ `SYMS_U32 voff_one_past_prolog;`

#### struct `SYMS_PeArmPdata`  
`typedef struct SYMS_PeArmPdata`  
_L51-60_
- L52 _public member_ `SYMS_U32 voff_first;`
- L59 _public member_ `SYMS_U32 combined;` — NOTE(allen): bits    | meaning [0:7]   | prolog length [8:29]  | function length [30:30] | instructions_are_32bits (otherwise they are 16 bits) [31:31] | has_exception_handler

#### struct `SYMS_PeIntelPdata`  
`typedef struct SYMS_PeIntelPdata`  
_L62-66_
- L63 _public member_ `SYMS_U32 voff_first;`
- L64 _public member_ `SYMS_U32 voff_one_past_last;`
- L65 _public member_ `SYMS_U32 voff_unwind_info;`

#### struct `SYMS_PeGuid`  
`typedef struct SYMS_PeGuid`  
_L71-76_
- L72 _public member_ `SYMS_U32 data1;`
- L73 _public member_ `SYMS_U16 data2;`
- L74 _public member_ `SYMS_U16 data3;`
- L75 _public member_ `SYMS_U8 data4[8];`

#### struct `SYMS_PeCvHeaderPDB20`  
`typedef struct SYMS_PeCvHeaderPDB20`  
_L82-88_
- L83 _public member_ `SYMS_U32 magic;`
- L84 _public member_ `SYMS_U32 offset;`
- L85 _public member_ `SYMS_U32 time;`
- L86 _public member_ `SYMS_U32 age;`

#### struct `SYMS_PeCvHeaderPDB70`  
`typedef struct SYMS_PeCvHeaderPDB70`  
_L91-96_
- L92 _public member_ `SYMS_U32 magic;`
- L93 _public member_ `SYMS_PeGuid guid;`
- L94 _public member_ `SYMS_U32 age;`

#### struct `SYMS_PeImportEntry`  
`typedef struct SYMS_PeImportEntry`  
_L102-108_
- L103 _public member_ `SYMS_U32 lookup_table_voff;`
- L104 _public member_ `SYMS_U32 timestamp;`
- L105 _public member_ `SYMS_U32 forwarder_chain;`
- L106 _public member_ `SYMS_U32 name_voff;`
- L107 _public member_ `SYMS_U32 import_addr_table_voff;`

#### struct `SYMS_PeDelayedImportEntry`  
`typedef struct SYMS_PeDelayedImportEntry`  
_L110-124_
- L113 _public member_ `SYMS_U32 attributes;` — According to PE/COFF spec this field is unused and should be set zero, but when I compile mule with MSVC 2019 this is set to 1.
- L114 _public member_ `SYMS_U32 name_voff;` — Name of the DLL
- L115 _public member_ `SYMS_U32 module_handle_voff;` — Place where module handle from LoadLibrary is stored
- L116 _public member_ `SYMS_U32 iat_voff;`
- L117 _public member_ `SYMS_U32 name_table_voff;` — Array of hint/name or oridnals
- L118 _public member_ `SYMS_U32 bound_table_voff;` — (Optional) Points to an array of SYMS_PeThunkData
- L119 _public member_ `SYMS_U32 unload_table_voff;` — (Optional) Copy of iat_voff
- L123 _public member_ `SYMS_U32 timestamp;` — 0 not bound -1 if bound and real timestamp located in bounded import directory Otherwise time when dll was bound

#### struct `SYMS_PeExportTable`  
`typedef struct SYMS_PeExportTable`  
_L126-138_
- L127 _public member_ `SYMS_U32 flags;` — must be zero
- L128 _public member_ `SYMS_U32 timestamp;` — time and date when export table was created
- L129 _public member_ `SYMS_U16 major_ver;` — table version, user can change major and minor version
- L130 _public member_ `SYMS_U16 minor_ver;`
- L131 _public member_ `SYMS_U32 name_voff;` — ASCII name of the dll
- L132 _public member_ `SYMS_U32 ordinal_base;` — Starting oridnal number
- L133 _public member_ `SYMS_U32 export_address_table_count;`
- L134 _public member_ `SYMS_U32 name_pointer_table_count;`
- L135 _public member_ `SYMS_U32 export_address_table_voff;`
- L136 _public member_ `SYMS_U32 name_pointer_table_voff;`
- L137 _public member_ `SYMS_U32 ordinal_table_voff;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_PE_H`
- L30 _macro_ `#define SYMS_DOS_MAGIC 0x5a4d` — this is the "MZ" as a 16-bit short
- L35 _macro_ `#define SYMS_PE_MAGIC 0x00004550u`
- L36 _macro_ `#define SYMS_PE32_MAGIC 0x010bu`
- L37 _macro_ `#define SYMS_PE32PLUS_MAGIC 0x020bu`
- L49 _typedef_ `} SYMS_PeMipsPdata;`
- L60 _typedef_ `} SYMS_PeArmPdata;`
- L66 _typedef_ `} SYMS_PeIntelPdata;`
- L76 _typedef_ `} SYMS_PeGuid;`
- L79 _macro_ `#define SYMS_CODEVIEW_PDB20_MAGIC 0x3031424e`
- L80 _macro_ `#define SYMS_CODEVIEW_PDB70_MAGIC 0x53445352`
- L88 _typedef_ `} SYMS_PeCvHeaderPDB20;` — file name packed after struct
- L96 _typedef_ `} SYMS_PeCvHeaderPDB70;` — file name packed after struct
- L108 _typedef_ `} SYMS_PeImportEntry;`
- L124 _typedef_ `} SYMS_PeDelayedImportEntry;`
- L138 _typedef_ `} SYMS_PeExportTable;`

### `Source/Runtime/SymsLib/syms/core/pe/syms_pe_parser.h` (Other)


#### struct `SYMS_PeFileAccel`  
`typedef struct SYMS_PeFileAccel`  
_L10-13_
- L11 _public member_ `SYMS_FileFormat format;`
- L12 _public member_ `SYMS_U32 coff_off;`

#### struct `SYMS_PeBinAccel`  
`typedef struct SYMS_PeBinAccel`  
_L15-35_
- L16 _public member_ `SYMS_FileFormat format;`
- L17 _public member_ `SYMS_U64 image_base;`
- L18 _public member_ `SYMS_U64 entry_point;`
- L19 _public member_ `SYMS_B32 is_pe32;`
- L20 _public member_ `SYMS_U64 virt_section_align;`
- L21 _public member_ `SYMS_U64 file_section_align;`
- L22 _public member_ `SYMS_U64 section_array_off;`
- L23 _public member_ `SYMS_U64 section_count;`
- L24 _public member_ `SYMS_U64 symbol_array_off;`
- L25 _public member_ `SYMS_U64 symbol_count;`
- L26 _public member_ `SYMS_U64 string_table_off;`
- L27 _public member_ `SYMS_U64 dbg_path_off;`
- L28 _public member_ `SYMS_U64 dbg_path_size;`
- L29 _public member_ `SYMS_PeGuid dbg_guid;`
- L30 _public member_ `SYMS_U32 dbg_age;`
- L31 _public member_ `SYMS_U32 dbg_time;`
- L32 _public member_ `SYMS_Arch arch;`
- L33 _public member_ `SYMS_U64Range *data_dir_franges;`
- L34 _public member_ `SYMS_U32 data_dir_count;`

#### enum `SYMS_PeImportLookup`  
`typedef enum SYMS_PeImportLookup`  
_L40-45_
- L41 _public enumerator_ `SYMS_PeImportLookup_NULL`
- L42 _public enumerator_ `SYMS_PeImportLookup_Ordinal`
- L43 _public enumerator_ `SYMS_PeImportLookup_NameHint`
- L44 _public enumerator_ `SYMS_PeImportLookup_COUNT`

#### struct `SYMS_PeImportName`  
`typedef struct SYMS_PeImportName`  
_L47-52_
- L48 _public member_ `SYMS_String8 name;`
- L49 _public member_ `SYMS_PeImportLookup lookup;`
- L50 _public member_ `SYMS_U16 ordinal;`
- L51 _public member_ `SYMS_U16 _padding_;`

#### struct `SYMS_PeImportNameArray`  
`typedef struct SYMS_PeImportNameArray`  
_L54-57_
- L55 _public member_ `SYMS_PeImportName *names;`
- L56 _public member_ `SYMS_U64 count;`

#### struct `SYMS_PeImportDll`  
`typedef struct SYMS_PeImportDll`  
_L59-63_
- L60 _public member_ `SYMS_String8 name;`
- L61 _public member_ `SYMS_PeImportNameArray name_table;`
- L62 _public member_ `SYMS_U64Array bound_table;`

#### struct `SYMS_PeImportDllArray`  
`typedef struct SYMS_PeImportDllArray`  
_L65-68_
- L66 _public member_ `SYMS_PeImportDll *import_dlls;`
- L67 _public member_ `SYMS_U64 count;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_PE_PARSER_H`
- L13 _typedef_ `} SYMS_PeFileAccel;`
- L35 _typedef_ `} SYMS_PeBinAccel;`
- L45 _typedef_ `SYMS_PeImportLookup_Ordinal, SYMS_PeImportLookup_NameHint, SYMS_PeImportLookup_COUNT, } SYMS_PeImportLookup;`
- L52 _typedef_ `} SYMS_PeImportName;`
- L57 _typedef_ `} SYMS_PeImportNameArray;`
- L63 _typedef_ `} SYMS_PeImportDll;`
- L68 _typedef_ `} SYMS_PeImportDllArray;`
- L75 _prototype_ `SYMS_PeFileAccel* syms_pe_file_accel_from_data(SYMS_Arena *arena, SYMS_String8 data);` — accelerators
- L76 _prototype_ `SYMS_PeBinAccel* syms_pe_bin_accel_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeFileAccel *file);`
- L79 _prototype_ `SYMS_Arch syms_pe_arch_from_bin(SYMS_PeBinAccel *bin);`
- L80 _prototype_ `SYMS_ExtFileList syms_pe_ext_file_list_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin);`
- L82 _prototype_ `SYMS_SecInfoArray syms_pe_sec_info_array_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin);`
- L84 _prototype_ `SYMS_U64 syms_pe_entry_point_voff_from_bin(SYMS_PeBinAccel *bin);`
- L85 _prototype_ `SYMS_ImportArray syms_pe_imports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin);`
- L86 _prototype_ `SYMS_ExportArray syms_pe_exports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin);`
- L92 _prototype_ `SYMS_U64 syms_pe_binary_search_intel_pdata(SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 voff);` — pdata
- L94 _prototype_ `SYMS_U64 syms_pe_sec_number_from_voff(SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 voff);` — sections
- L96 _prototype_ `void* syms_pe_ptr_from_sec_number(SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 n);`
- L97 _prototype_ `void* syms_pe_ptr_from_foff(SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 foff);`
- L98 _prototype_ `void* syms_pe_ptr_from_voff(SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 voff);`
- L100 _prototype_ `SYMS_U64 syms_pe_foff_from_voff(SYMS_CoffSectionHeader *sections, SYMS_U32 section_count, SYMS_U64 voff);`
- L101 _prototype_ `SYMS_U64 syms_pe_bin_foff_from_voff(SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 voff);`
- L104 _prototype_ `SYMS_U64Array syms_u64_array_from_null_term_u64_string(SYMS_Arena *arena, SYMS_U64 *src, SYMS_U64 *opl);` — imports & exports
- L105 _prototype_ `SYMS_U64Array syms_u64_array_from_null_term_u32_string(SYMS_Arena *arena, SYMS_U32 *src, SYMS_U32 *opl);`
- L106 _prototype_ `SYMS_U64Array syms_pe_u64_array_from_null_term_addr_string(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 foff);`
- L109 _prototype_ `SYMS_PeImportName syms_pe_import_name_from_name_entry(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64 name_entry);`
- L111 _prototype_ `SYMS_PeImportNameArray syms_pe_import_name_array_from_name_entries(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin, SYMS_U64Array name_entries);`
- L116 _prototype_ `SYMS_PeImportDllArray syms_pe_regular_imports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin);`
- L118 _prototype_ `SYMS_PeImportDllArray syms_pe_delayed_imports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin);`
- L121 _prototype_ `SYMS_String8 syms_pe_binary_name_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_PeBinAccel *bin);`

### `Source/Runtime/SymsLib/syms/core/pe/syms_pecoff_helpers.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_PECOFF_HELPERS_H`
- L10 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_CoffSectionHeader syms_pecoff_sec_hdr_nil = {0};`
- L12 _prototype_ `SYMS_CoffSectionHeader* syms_pecoff_sec_hdr_from_n(SYMS_String8 data, SYMS_U64 sec_hrds_off, SYMS_U64 n);`
- L15 _prototype_ `SYMS_U64Range syms_pecoff_name_range_from_hdr_off(SYMS_String8 data, SYMS_U64 sec_hdr_off);`
- L16 _prototype_ `SYMS_String8 syms_pecoff_name_from_hdr_off(SYMS_Arena *arena, SYMS_String8 data, SYMS_U64 sec_hdr_off);`
- L19 _prototype_ `SYMS_U64Array syms_pecoff_voff_accelerator_from_coff_hdr_array(SYMS_Arena *arena, SYMS_CoffSectionHeader *sec_hdrs, SYMS_U64 sec_count);`
- L23 _prototype_ `SYMS_SecInfoArray syms_pecoff_sec_info_from_coff_sec(SYMS_Arena *arena, SYMS_String8 data, SYMS_U64 sec_hdrs_off, SYMS_U64 sec_count);`

### `Source/Runtime/SymsLib/syms/core/regs/syms_dwarf_regs_helper.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DWARF_REGS_HELPER_H`
- L10 _prototype_ `void syms_dw_regs__set_unwind_regs_from_full_regs(SYMS_DwRegsX64 *dst, SYMS_RegX64 *src);`
- L11 _prototype_ `void syms_dw_regs__set_full_regs_from_unwind_regs(SYMS_RegX64 *dst, SYMS_DwRegsX64 *src);`

### `Source/Runtime/SymsLib/syms/core/regs/syms_regs.h` (Other)


#### union `SYMS_Reg16`  
`typedef union SYMS_Reg16`  
_L9-12_
- L10 _public member_ `SYMS_U8 v[2];`
- L11 _public member_ `SYMS_U16 u16;`

#### union `SYMS_Reg32`  
`typedef union SYMS_Reg32`  
_L14-18_
- L15 _public member_ `SYMS_U8 v[4];`
- L16 _public member_ `SYMS_U32 u32;`
- L17 _public member_ `SYMS_F32 f32;`

#### union `SYMS_Reg64`  
`typedef union SYMS_Reg64`  
_L20-24_
- L21 _public member_ `SYMS_U8 v[8];`
- L22 _public member_ `SYMS_U64 u64;`
- L23 _public member_ `SYMS_F64 f64;`

#### struct `SYMS_Reg80`  
`typedef struct SYMS_Reg80`  
_L27-30_
- L28 _public member_ `SYMS_U64 int1_frac63;`
- L29 _public member_ `SYMS_U16 sign1_exp15;`

#### union `SYMS_Reg128`  
`typedef union SYMS_Reg128`  
_L33-39_
- L34 _public member_ `SYMS_U8 v[16];`
- L35 _public member_ `SYMS_U32 u32[4];`
- L36 _public member_ `SYMS_F32 f32[4];`
- L37 _public member_ `SYMS_U64 u64[2];`
- L38 _public member_ `SYMS_F64 f64[2];`

#### union `SYMS_Reg256`  
`typedef union SYMS_Reg256`  
_L41-47_
- L42 _public member_ `SYMS_U8 v[32];`
- L43 _public member_ `SYMS_U32 u32[8];`
- L44 _public member_ `SYMS_F32 f32[8];`
- L45 _public member_ `SYMS_U64 u64[4];`
- L46 _public member_ `SYMS_F64 f64[4];`

#### struct `SYMS_RegSection`  
`typedef struct SYMS_RegSection`  
_L49-53_
- L51 _public member_ `SYMS_U16 off;` — TODO(allen): naming pass byte_*; double check these are encoded as byte sizes
- L52 _public member_ `SYMS_U16 size;`

#### struct `SYMS_RegSlice`  
`typedef struct SYMS_RegSlice`  
_L55-59_
- L56 _public member_ `SYMS_U16 reg_id;`
- L57 _public member_ `SYMS_U8 byte_off;`
- L58 _public member_ `SYMS_U8 byte_size;`

#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_REGS_H`
- L12 _typedef_ `} SYMS_Reg16;`
- L18 _typedef_ `} SYMS_Reg32;`
- L24 _typedef_ `} SYMS_Reg64;`
- L30 _typedef_ `} SYMS_Reg80;`
- L39 _typedef_ `} SYMS_Reg128;`
- L47 _typedef_ `} SYMS_Reg256;`
- L53 _typedef_ `} SYMS_RegSection;`
- L59 _typedef_ `} SYMS_RegSlice;`

### `Source/Runtime/SymsLib/syms/core/regs/syms_regs_helpers.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_REGS_HELPERS_H`
- L7 _prototype_ `SYMS_U64 syms_reg_count_from_arch(SYMS_Arch arch);`
- L8 _prototype_ `SYMS_String8 *syms_reg_name_table_from_arch(SYMS_Arch arch);`
- L9 _prototype_ `SYMS_RegSection *syms_reg_section_table_from_arch(SYMS_Arch arch);`
- L11 _prototype_ `SYMS_RegSection syms_reg_section_from_reg_id(SYMS_Arch arch, SYMS_RegID reg_id);`

### `Source/Runtime/SymsLib/syms/core/regs/syms_regs_x64.h` (Other)


#### struct `SYMS_FSave`  
`struct SYMS_FSave`  
_L11-28_
- desc: (32-Bit Protected Mode Format)
- L13 _public member_ `SYMS_U16 fcw;` — control registers
- L14 _public member_ `SYMS_U16 _pad0;`
- L15 _public member_ `SYMS_U16 fsw;`
- L16 _public member_ `SYMS_U16 _pad1;`
- L17 _public member_ `SYMS_U16 ftw;`
- L18 _public member_ `SYMS_U16 _pad2;`
- L19 _public member_ `SYMS_U32 fip;`
- L20 _public member_ `SYMS_U16 fips;`
- L21 _public member_ `SYMS_U16 fop;`
- L22 _public member_ `SYMS_U32 fdp;`
- L23 _public member_ `SYMS_U16 fds;`
- L24 _public member_ `SYMS_U16 _pad3;`
- L27 _public member_ `SYMS_U8 st[80];` — data registers

#### struct `SYMS_XSaveLegacy`  
`typedef struct SYMS_XSaveLegacy`  
_L30-52_
- L31 _public member_ `SYMS_U16 fcw;`
- L32 _public member_ `SYMS_U16 fsw;`
- L33 _public member_ `SYMS_U16 ftw;`
- L34 _public member_ `SYMS_U16 fop;`
- L47 _public member_ `SYMS_U32 mxcsr;`
- L48 _public member_ `SYMS_U32 mxcsr_mask;`
- L49 _public member_ `SYMS_U8 st_space[128];`
- L50 _public member_ `SYMS_U8 xmm_space[256];`
- L51 _public member_ `SYMS_U8 padding[96];`

#### union `SYMS_XSaveLegacy::(anonymous)`  
`union`  
_L35-46_

#### struct `SYMS_XSaveLegacy::__anoncb635d61010a::(anonymous)`  
`struct`  
_L36-39_

#### struct `SYMS_XSaveLegacy::__anoncb635d61010a::(anonymous)`  
`struct`  
_L40-45_

#### struct `SYMS_XSaveHeader`  
`typedef struct SYMS_XSaveHeader`  
_L54-58_
- L55 _public member_ `SYMS_U64 xstate_bv;`
- L56 _public member_ `SYMS_U64 xcomp_bv;`
- L57 _public member_ `SYMS_U8 reserved[48];`

#### struct `SYMS_XSave`  
`struct SYMS_XSave`  
_L63-67_
- desc: TODO(allen): this one is hacked; ymmh is not gauranteed to be at a fixed location and there can be more after that. Requires CPUID to be totally compliant to the standard. See intel's manual on the xsave format for more info.
- L64 _public member_ `SYMS_XSaveLegacy legacy;`
- L65 _public member_ `SYMS_XSaveHeader header;`
- L66 _public member_ `SYMS_U8 ymmh[256];`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_REGS_X64_H`
- L37 _member_ `SYMS_U64 fip;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610208`)
- L38 _member_ `SYMS_U64 fdp;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610208`)
- L39 _member_ `} b64;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a`)
- L41 _member_ `SYMS_U32 fip;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610308`)
- L42 _member_ `SYMS_U16 fcs, _pad0;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610308`)
- L42 _member_ `SYMS_U16 fcs, _pad0;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610308`)
- L43 _member_ `SYMS_U32 fdp;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610308`)
- L44 _member_ `SYMS_U16 fds, _pad1;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610308`)
- L44 _member_ `SYMS_U16 fds, _pad1;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a::__anoncb635d610308`)
- L45 _member_ `} b32;` (scope `SYMS_XSaveLegacy::__anoncb635d61010a`)
- L52 _typedef_ `} SYMS_XSaveLegacy;`
- L58 _typedef_ `} SYMS_XSaveHeader;`
- L72 _prototype_ `void syms_x64_regs__set_full_regs_from_xsave_legacy(SYMS_RegX64 *dst, SYMS_XSaveLegacy *src);`
- L73 _prototype_ `void syms_x64_regs__set_xsave_legacy_from_full_regs(SYMS_XSaveLegacy *dst, SYMS_RegX64 *src);`
- L74 _prototype_ `void syms_x64_regs__set_full_regs_from_xsave_avx_extension(SYMS_RegX64 *dst, void *src);`
- L75 _prototype_ `void syms_x64_regs__set_xsave_avx_extension_from_full_regs(void *dst, SYMS_RegX64 *src);`

### `Source/Runtime/SymsLib/syms/core/syms_debug_info.h` (Other)


#### struct `SYMS_SecInfo`  
`typedef struct SYMS_SecInfo`  
_L15-19_
- L16 _public member_ `SYMS_String8 name;`
- L17 _public member_ `SYMS_U64Range vrange;`
- L18 _public member_ `SYMS_U64Range frange;`

#### struct `SYMS_SecInfoArray`  
`typedef struct SYMS_SecInfoArray`  
_L21-24_
- L22 _public member_ `SYMS_SecInfo *sec_info;`
- L23 _public member_ `SYMS_U64 count;`

#### struct `SYMS_BinInfo`  
`typedef struct SYMS_BinInfo`  
_L26-29_
- L27 _public member_ `SYMS_Arch arch;`
- L28 _public member_ `SYMS_U64Range range;`

#### struct `SYMS_BinInfoArray`  
`typedef struct SYMS_BinInfoArray`  
_L31-34_
- L32 _public member_ `SYMS_BinInfo *bin_info;`
- L33 _public member_ `SYMS_U64 count;`

#### struct `SYMS_Import`  
`typedef struct SYMS_Import`  
_L39-43_
- L40 _public member_ `SYMS_String8 name;`
- L41 _public member_ `SYMS_String8 library_name;`
- L42 _public member_ `SYMS_U16 ordinal;`

#### struct `SYMS_Export`  
`typedef struct SYMS_Export`  
_L45-52_
- L46 _public member_ `SYMS_String8 name;`
- L47 _public member_ `SYMS_U64 address;`
- L48 _public member_ `SYMS_U32 ordinal;`
- L49 _public member_ `SYMS_U32 unused_;`
- L50 _public member_ `SYMS_String8 forwarder_library_name;`
- L51 _public member_ `SYMS_String8 forwarder_import_name;`

#### struct `SYMS_ImportNode`  
`typedef struct SYMS_ImportNode`  
_L54-57_
- L55 _public member_ `struct SYMS_ImportNode *next;`
- L56 _public member_ `SYMS_Import data;`

#### struct `SYMS_ExportNode`  
`typedef struct SYMS_ExportNode`  
_L59-62_
- L60 _public member_ `struct SYMS_ExportNode *next;`
- L61 _public member_ `SYMS_Export data;`

#### struct `SYMS_ImportArray`  
`typedef struct SYMS_ImportArray`  
_L64-67_
- L65 _public member_ `SYMS_Import *imports;`
- L66 _public member_ `SYMS_U64 count;`

#### struct `SYMS_ExportArray`  
`typedef struct SYMS_ExportArray`  
_L69-72_
- L70 _public member_ `SYMS_Export *exports;`
- L71 _public member_ `SYMS_U64 count;`

#### struct `SYMS_UnitInfo`  
`typedef struct SYMS_UnitInfo`  
_L79-82_
- L80 _public member_ `SYMS_UnitFeatures features;`
- L81 _public member_ `SYMS_Language language;`

#### struct `SYMS_UnitNames`  
`typedef struct SYMS_UnitNames`  
_L84-90_
- L85 _public member_ `SYMS_String8 source_file;`
- L86 _public member_ `SYMS_String8 object_file;`
- L87 _public member_ `SYMS_String8 archive_file;`
- L88 _public member_ `SYMS_String8 compiler;`
- L89 _public member_ `SYMS_String8 compile_dir;`

#### struct `SYMS_UnitRange`  
`typedef struct SYMS_UnitRange`  
_L92-95_
- L93 _public member_ `SYMS_U64Range vrange;`
- L94 _public member_ `SYMS_UnitID uid;`

#### struct `SYMS_UnitRangeArray`  
`typedef struct SYMS_UnitRangeArray`  
_L97-100_
- L98 _public member_ `SYMS_UnitRange *ranges;`
- L99 _public member_ `SYMS_U64 count;`

#### struct `SYMS_ExtMatchKey`  
`typedef struct SYMS_ExtMatchKey`  
_L105-107_
- L106 _public member_ `SYMS_U8 v[16];`

#### struct `SYMS_ExtFile`  
`typedef struct SYMS_ExtFile`  
_L109-112_
- L110 _public member_ `SYMS_String8 file_name;`
- L111 _public member_ `SYMS_ExtMatchKey match_key;`

#### struct `SYMS_ExtFileNode`  
`typedef struct SYMS_ExtFileNode`  
_L114-117_
- L115 _public member_ `struct SYMS_ExtFileNode *next;`
- L116 _public member_ `SYMS_ExtFile ext_file;`

#### struct `SYMS_ExtFileList`  
`typedef struct SYMS_ExtFileList`  
_L119-123_
- L120 _public member_ `SYMS_ExtFileNode *first;`
- L121 _public member_ `SYMS_ExtFileNode *last;`
- L122 _public member_ `SYMS_U64 node_count;`

#### struct `SYMS_SrcCoord`  
`typedef struct SYMS_SrcCoord`  
_L130-134_
- L131 _public member_ `SYMS_FileID file_id;`
- L132 _public member_ `SYMS_U32 line;`
- L133 _public member_ `SYMS_U32 col;`

#### struct `SYMS_Line`  
`typedef struct SYMS_Line`  
_L136-139_
- L137 _public member_ `SYMS_SrcCoord src_coord;`
- L138 _public member_ `SYMS_U64 voff;`

#### struct `SYMS_ResolvedLine`  
`typedef struct SYMS_ResolvedLine`  
_L141-146_
- L142 _public member_ `SYMS_String8 file_name;`
- L143 _public member_ `SYMS_U32 line;`
- L144 _public member_ `SYMS_U32 col;`
- L145 _public member_ `SYMS_U64 voff;`

#### struct `SYMS_FileIDArray`  
`typedef struct SYMS_FileIDArray`  
_L148-151_
- L149 _public member_ `SYMS_FileID *ids;`
- L150 _public member_ `SYMS_U64 count;`

#### struct `SYMS_LineTable`  
`typedef struct SYMS_LineTable`  
_L153-162_
- L157 _public member_ `SYMS_U64 *sequence_index_array;` — sequence_index_array ranges from [0,sequence_count] inclusive so that: for-all i in [0,sequence_count): (sequence_index_array[i + 1] - sequence_index_array[i]) == # of lines in sequence i
- L158 _public member_ `SYMS_U64 sequence_count;`
- L160 _public member_ `SYMS_Line *line_array;`
- L161 _public member_ `SYMS_U64 line_count;`

#### struct `SYMS_LineParseOut`  
`typedef struct SYMS_LineParseOut`  
_L164-168_
- L165 _public member_ `SYMS_LineTable line_table;`
- L166 _public member_ `SYMS_String8Array file_table;`
- L167 _public member_ `SYMS_FileIDArray file_id_array;`

#### enum `SYMS_CallConvention`  
`typedef enum SYMS_CallConvention`  
_L176-203_
- desc: TODO(allen): go to the mc file TODO(allen): just yanked right from PDB more interpretation should be applied to these name choices
- L177 _public enumerator_ `SYMS_CallConvention_NULL`
- L178 _public enumerator_ `SYMS_CallConvention_NEAR_C`
- L179 _public enumerator_ `SYMS_CallConvention_FAR_C`
- L180 _public enumerator_ `SYMS_CallConvention_NEAR_PASCAL`
- L181 _public enumerator_ `SYMS_CallConvention_FAR_PASCAL`
- L182 _public enumerator_ `SYMS_CallConvention_NEAR_FAST`
- L183 _public enumerator_ `SYMS_CallConvention_FAR_FAST`
- L184 _public enumerator_ `SYMS_CallConvention_NEAR_STD`
- L185 _public enumerator_ `SYMS_CallConvention_FAR_STD`
- L186 _public enumerator_ `SYMS_CallConvention_NEAR_SYS`
- L187 _public enumerator_ `SYMS_CallConvention_FAR_SYS`
- L188 _public enumerator_ `SYMS_CallConvention_THISCALL`
- L189 _public enumerator_ `SYMS_CallConvention_MIPSCALL`
- L190 _public enumerator_ `SYMS_CallConvention_GENERIC`
- L191 _public enumerator_ `SYMS_CallConvention_ALPHACALL`
- L192 _public enumerator_ `SYMS_CallConvention_PPCCALL`
- L193 _public enumerator_ `SYMS_CallConvention_SHCALL`
- L194 _public enumerator_ `SYMS_CallConvention_ARMCALL`
- L195 _public enumerator_ `SYMS_CallConvention_AM33CALL`
- L196 _public enumerator_ `SYMS_CallConvention_TRICALL`
- L197 _public enumerator_ `SYMS_CallConvention_SH5CALL`
- L198 _public enumerator_ `SYMS_CallConvention_M32RCALL`
- L199 _public enumerator_ `SYMS_CallConvention_CLRCALL`
- L200 _public enumerator_ `SYMS_CallConvention_INLINE`
- L201 _public enumerator_ `SYMS_CallConvention_NEAR_VECTOR`
- L202 _public enumerator_ `SYMS_CallConvention_COUNT`

#### enum `SYMS_SizeInterpretation`  
`typedef enum SYMS_SizeInterpretation`  
_L205-210_
- L206 _public enumerator_ `SYMS_SizeInterpretation_Null`
- L207 _public enumerator_ `SYMS_SizeInterpretation_ByteCount`
- L208 _public enumerator_ `SYMS_SizeInterpretation_Multiplier`
- L209 _public enumerator_ `SYMS_SizeInterpretation_ResolveForwardReference`

#### struct `SYMS_SymbolIDNode`  
`typedef struct SYMS_SymbolIDNode`  
_L217-220_
- L218 _public member_ `struct SYMS_SymbolIDNode *next;`
- L219 _public member_ `SYMS_SymbolID id;`

#### struct `SYMS_SymbolIDList`  
`typedef struct SYMS_SymbolIDList`  
_L222-226_
- L223 _public member_ `SYMS_SymbolIDNode *first;`
- L224 _public member_ `SYMS_SymbolIDNode *last;`
- L225 _public member_ `SYMS_U64 count;`

#### struct `SYMS_SymbolIDArray`  
`typedef struct SYMS_SymbolIDArray`  
_L228-231_
- L229 _public member_ `SYMS_SymbolID *ids;`
- L230 _public member_ `SYMS_U64 count;`

#### struct `SYMS_USID`  
`typedef struct SYMS_USID`  
_L234-237_
- desc: unit and symbol ID
- L235 _public member_ `SYMS_UnitID uid;`
- L236 _public member_ `SYMS_SymbolID sid;`

#### struct `SYMS_USIDNode`  
`typedef struct SYMS_USIDNode`  
_L239-242_
- L240 _public member_ `struct SYMS_USIDNode *next;`
- L241 _public member_ `SYMS_USID usid;`

#### struct `SYMS_USIDList`  
`typedef struct SYMS_USIDList`  
_L244-248_
- L245 _public member_ `SYMS_USIDNode *first;`
- L246 _public member_ `SYMS_USIDNode *last;`
- L247 _public member_ `SYMS_U64 count;`

#### struct `SYMS_USIDArray`  
`typedef struct SYMS_USIDArray`  
_L250-253_
- L251 _public member_ `SYMS_USID *usid;`
- L252 _public member_ `SYMS_U64 count;`

#### struct `SYMS_SigHandle`  
`typedef struct SYMS_SigHandle`  
_L255-257_
- L256 _public member_ `SYMS_U64 v;`

#### struct `SYMS_UnitIDAndSig`  
`typedef struct SYMS_UnitIDAndSig`  
_L259-262_
- L260 _public member_ `SYMS_UnitID uid;`
- L261 _public member_ `SYMS_SigHandle sig;`

#### struct `SYMS_TypeInfo`  
`typedef struct SYMS_TypeInfo`  
_L264-298_
- L265 _public member_ `SYMS_TypeKind kind;`
- L271 _public member_ `SYMS_TypeModifiers mods;` — 'mods' gives modifier information applied to this type after inferring the rest of it's structure. When (kind == SYMS_TypeKind_Modifier) this type symbol only exists to apply modifiers to another type symbol, but in certain cases a non-modifier type symbol contains it's own modifiers.
- L274 _public member_ `SYMS_SizeInterpretation reported_size_interp;` — 'reported_size_interp', & 'reported_size' together describe the size of the type.
- L275 _public member_ `SYMS_U64 reported_size;`
- L278 _public member_ `SYMS_SrcCoord src_coord;` — filled for any type that has definition location information.
- L290 _public member_ `SYMS_USID direct_type;` — 'direct_type' meaning depends on kind. SYMS_TypeKind_Bitfield   -> the underlying type of the bitfield SYMS_TypeKind_Enum       -> the underlying type of the enum SYMS_TypeKind_Typedef    -> the underlying type of the typedef SYMS_TypeKind_Modifier   -> the modified type SYMS_TypeKind_Ptr        -> the type pointed to SYMS_TypeKind_*Reference -> the type referenced SYMS_TypeKind_MemberPtr  -> the type pointed to SYMS_TypeKind_Array      -> the type of an element in the array SYMS_TypeKind_Proc       -> the return type of the procedure

#### union `SYMS_TypeInfo::(anonymous)`  
`union`  
_L292-297_

#### struct `SYMS_ConstInfo`  
`typedef struct SYMS_ConstInfo`  
_L300-304_
- L302 _public member_ `SYMS_TypeKind kind;` — TODO(allen): look at more complex constants
- L303 _public member_ `SYMS_U64 val;`

#### enum `SYMS_MemKind`  
`typedef enum SYMS_MemKind`  
_L306-316_
- L307 _public enumerator_ `SYMS_MemKind_Null`
- L308 _public enumerator_ `SYMS_MemKind_DataField`
- L309 _public enumerator_ `SYMS_MemKind_StaticData`
- L310 _public enumerator_ `SYMS_MemKind_Method`
- L311 _public enumerator_ `SYMS_MemKind_StaticMethod`
- L312 _public enumerator_ `SYMS_MemKind_VTablePtr`
- L313 _public enumerator_ `SYMS_MemKind_BaseClass`
- L314 _public enumerator_ `SYMS_MemKind_VBaseClassPtr`
- L315 _public enumerator_ `SYMS_MemKind_NestedType`

#### enum `(anonymous)`  
`enum`  
_L319-323_

#### struct `SYMS_MemInfo`  
`typedef struct SYMS_MemInfo`  
_L325-332_
- L326 _public member_ `SYMS_MemKind kind;`
- L327 _public member_ `SYMS_MemVisibility visibility;`
- L328 _public member_ `SYMS_MemFlags flags;`
- L329 _public member_ `SYMS_String8 name;`
- L330 _public member_ `SYMS_U32 off;`
- L331 _public member_ `SYMS_U32 virtual_off;`

#### struct `SYMS_SigInfo`  
`typedef struct SYMS_SigInfo`  
_L334-339_
- L335 _public member_ `SYMS_UnitID uid;`
- L336 _public member_ `SYMS_SymbolIDArray param_type_ids;`
- L337 _public member_ `SYMS_SymbolID return_type_id;`
- L338 _public member_ `SYMS_SymbolID this_type_id;`

#### struct `SYMS_EnumMember`  
`typedef struct SYMS_EnumMember`  
_L341-344_
- L342 _public member_ `SYMS_String8 name;`
- L343 _public member_ `SYMS_U64 val;`

#### struct `SYMS_EnumMemberArray`  
`typedef struct SYMS_EnumMemberArray`  
_L346-349_
- L347 _public member_ `SYMS_EnumMember *enum_members;`
- L348 _public member_ `SYMS_U64 count;`

#### struct `SYMS_LocRange`  
`typedef struct SYMS_LocRange`  
_L356-359_
- L357 _public member_ `SYMS_U64Range vrange;`
- L358 _public member_ `SYMS_LocID loc_id;`

#### struct `SYMS_LocRangeArray`  
`typedef struct SYMS_LocRangeArray`  
_L361-364_
- L362 _public member_ `SYMS_LocRange *loc_ranges;`
- L363 _public member_ `SYMS_U64 count;`

#### struct `SYMS_LocRangeNode`  
`typedef struct SYMS_LocRangeNode`  
_L366-369_
- L367 _public member_ `struct SYMS_LocRangeNode *next;`
- L368 _public member_ `SYMS_LocRange loc_range;`

#### struct `SYMS_LocRangeList`  
`typedef struct SYMS_LocRangeList`  
_L371-375_
- L372 _public member_ `SYMS_LocRangeNode *first;`
- L373 _public member_ `SYMS_LocRangeNode *last;`
- L374 _public member_ `SYMS_U64 count;`

#### enum `SYMS_ProcLoc`  
`typedef enum SYMS_ProcLoc`  
_L377-380_
- L378 _public enumerator_ `SYMS_ProcLoc_FrameBase`
- L379 _public enumerator_ `SYMS_ProcLoc_ReturnAddress`

#### struct `SYMS_LinkNameRec`  
`typedef struct SYMS_LinkNameRec`  
_L385-388_
- L386 _public member_ `SYMS_String8 name;`
- L387 _public member_ `SYMS_U64 voff;`

#### struct `SYMS_LinkNameRecArray`  
`typedef struct SYMS_LinkNameRecArray`  
_L390-393_
- L391 _public member_ `SYMS_LinkNameRec *recs;`
- L392 _public member_ `SYMS_U64 count;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_DEBUG_INFO_H`
- L19 _typedef_ `} SYMS_SecInfo;`
- L24 _typedef_ `} SYMS_SecInfoArray;`
- L29 _typedef_ `} SYMS_BinInfo;`
- L34 _typedef_ `} SYMS_BinInfoArray;`
- L43 _typedef_ `} SYMS_Import;`
- L52 _typedef_ `} SYMS_Export;`
- L57 _typedef_ `} SYMS_ImportNode;`
- L62 _typedef_ `} SYMS_ExportNode;`
- L67 _typedef_ `} SYMS_ImportArray;`
- L72 _typedef_ `} SYMS_ExportArray;`
- L77 _typedef_ `typedef SYMS_U64 SYMS_UnitID;`
- L82 _typedef_ `} SYMS_UnitInfo;`
- L90 _typedef_ `} SYMS_UnitNames;`
- L95 _typedef_ `} SYMS_UnitRange;`
- L100 _typedef_ `} SYMS_UnitRangeArray;`
- L107 _typedef_ `} SYMS_ExtMatchKey;`
- L112 _typedef_ `} SYMS_ExtFile;`
- L117 _typedef_ `} SYMS_ExtFileNode;`
- L123 _typedef_ `} SYMS_ExtFileList;`
- L128 _typedef_ `typedef SYMS_U64 SYMS_FileID;`
- L134 _typedef_ `} SYMS_SrcCoord;`
- L139 _typedef_ `} SYMS_Line;`
- L146 _typedef_ `} SYMS_ResolvedLine;`
- L151 _typedef_ `} SYMS_FileIDArray;`
- L162 _typedef_ `} SYMS_LineTable;`
- L168 _typedef_ `} SYMS_LineParseOut;`
- L203 _typedef_ `} SYMS_CallConvention;`
- L210 _typedef_ `SYMS_SizeInterpretation_ByteCount, SYMS_SizeInterpretation_Multiplier, SYMS_SizeInterpretation_ResolveForwardReference, } SYMS_SizeInterpretation;`
- L215 _typedef_ `typedef SYMS_U64 SYMS_SymbolID;`
- L220 _typedef_ `} SYMS_SymbolIDNode;`
- L226 _typedef_ `} SYMS_SymbolIDList;`
- L231 _typedef_ `} SYMS_SymbolIDArray;`
- L237 _typedef_ `} SYMS_USID;`
- L242 _typedef_ `} SYMS_USIDNode;`
- L248 _typedef_ `} SYMS_USIDList;`
- L253 _typedef_ `} SYMS_USIDArray;`
- L257 _typedef_ `} SYMS_SigHandle;`
- L262 _typedef_ `} SYMS_UnitIDAndSig;`
- L294 _member_ `SYMS_CallConvention call_convention;` (scope `SYMS_TypeInfo::__anonb909b3e1010a`) — kind == SYMS_TypeKind_Proc
- L296 _member_ `SYMS_USID containing_type;` (scope `SYMS_TypeInfo::__anonb909b3e1010a`) — kind == SYMS_TypeKind_MemberPtr
- L298 _typedef_ `} SYMS_TypeInfo;`
- L304 _typedef_ `} SYMS_ConstInfo;`
- L316 _typedef_ `SYMS_MemKind_BaseClass, SYMS_MemKind_VBaseClassPtr, SYMS_MemKind_NestedType, } SYMS_MemKind;`
- L318 _typedef_ `typedef SYMS_U32 SYMS_MemFlags;`
- L320 _enumerator_ `SYMS_MemFlag_Virtual = (1 << 0)` (scope `__anonb909b3e10203`)
- L321 _enumerator_ `SYMS_MemFlag_Constructor = (1 << 1)` (scope `__anonb909b3e10203`)
- L322 _enumerator_ `SYMS_MemFlag_Destructor = (1 << 2)` (scope `__anonb909b3e10203`)
- L332 _typedef_ `} SYMS_MemInfo;`
- L339 _typedef_ `} SYMS_SigInfo;`
- L344 _typedef_ `} SYMS_EnumMember;`
- L349 _typedef_ `} SYMS_EnumMemberArray;`
- L354 _typedef_ `typedef SYMS_U64 SYMS_LocID;`
- L359 _typedef_ `} SYMS_LocRange;`
- L364 _typedef_ `} SYMS_LocRangeArray;`
- L369 _typedef_ `} SYMS_LocRangeNode;`
- L375 _typedef_ `} SYMS_LocRangeList;`
- L380 _typedef_ `SYMS_ProcLoc_FrameBase, SYMS_ProcLoc_ReturnAddress, } SYMS_ProcLoc;`
- L388 _typedef_ `} SYMS_LinkNameRec;`
- L393 _typedef_ `} SYMS_LinkNameRecArray;`
- L398 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_FileFormat syms_format_nil = SYMS_FileFormat_Null;`
- L405 _prototype_ `SYMS_B32 syms_ext_match_key_match(SYMS_ExtMatchKey *a, SYMS_ExtMatchKey *b);`
- L407 _prototype_ `SYMS_USID syms_make_usid(SYMS_UnitID uid, SYMS_SymbolID sid);`
- L409 _prototype_ `SYMS_TypeKind syms_type_kind_fwd_from_main(SYMS_TypeKind type_kind);`
- L410 _prototype_ `SYMS_TypeKind syms_type_kind_main_from_fwd(SYMS_TypeKind type_kind);`
- L411 _prototype_ `SYMS_B32 syms_type_kind_is_basic(SYMS_TypeKind kind);`
- L412 _prototype_ `SYMS_B32 syms_type_kind_is_basic_or_enum(SYMS_TypeKind kind);`
- L413 _prototype_ `SYMS_B32 syms_type_kind_is_integer(SYMS_TypeKind kind);`
- L414 _prototype_ `SYMS_B32 syms_type_kind_is_signed(SYMS_TypeKind kind);`
- L415 _prototype_ `SYMS_B32 syms_type_kind_is_complex(SYMS_TypeKind kind);`
- L416 _prototype_ `SYMS_B32 syms_type_kind_is_user_defined(SYMS_TypeKind kind);`
- L417 _prototype_ `SYMS_B32 syms_type_kind_is_record(SYMS_TypeKind kind);`
- L418 _prototype_ `SYMS_B32 syms_type_kind_is_enum(SYMS_TypeKind kind);`
- L419 _prototype_ `SYMS_B32 syms_type_kind_is_forward(SYMS_TypeKind kind);`
- L421 _prototype_ `SYMS_SymbolIDArray syms_sid_array_from_list(SYMS_Arena *arena, SYMS_SymbolIDList *list);`

### `Source/Runtime/SymsLib/syms/core/syms_eval.h` (Other)


#### enum `SYMS_EvalMode`  
`typedef enum SYMS_EvalMode`  
_L15-20_
- L16 _public enumerator_ `SYMS_EvalMode_Nil`
- L17 _public enumerator_ `SYMS_EvalMode_Value`
- L18 _public enumerator_ `SYMS_EvalMode_Address`
- L19 _public enumerator_ `SYMS_EvalMode_Register`

#### enum `(anonymous)`  
`enum`  
_L22-30_

#### union `SYMS_EvalOpParams`  
`typedef union SYMS_EvalOpParams`  
_L32-38_
- L33 _public member_ `SYMS_U8 u8[8];`
- L34 _public member_ `SYMS_U16 u16[4];`
- L35 _public member_ `SYMS_U32 u32[2];`
- L36 _public member_ `SYMS_U64 u64[1];`
- L37 _public member_ `SYMS_String8 data;`

#### struct `SYMS_EvalIRTree`  
`typedef struct SYMS_EvalIRTree`  
_L40-48_
- L41 _public member_ `SYMS_U32 op;`

#### union `SYMS_EvalIRTree::(anonymous)`  
`union`  
_L42-47_

#### struct `SYMS_EvalIRTree::__anonb7908137020a::(anonymous)`  
`struct`  
_L43-46_

#### struct `SYMS_EvalOpNode`  
`typedef struct SYMS_EvalOpNode`  
_L50-54_
- L51 _public member_ `struct SYMS_EvalOpNode *next;`
- L52 _public member_ `SYMS_U8 op;`
- L53 _public member_ `SYMS_EvalOpParams params;`

#### struct `SYMS_EvalOpList`  
`typedef struct SYMS_EvalOpList`  
_L56-60_
- L57 _public member_ `SYMS_EvalOpNode *first;`
- L58 _public member_ `SYMS_EvalOpNode *last;`
- L59 _public member_ `SYMS_U64 byte_count;`

#### struct `SYMS_Location`  
`typedef struct SYMS_Location`  
_L62-66_
- L63 _public member_ `SYMS_EvalOpList op_list;`
- L64 _public member_ `SYMS_EvalMode mode;`
- L65 _public member_ `SYMS_B32 is_parameter;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_EVAL_H`
- L20 _typedef_ `SYMS_EvalMode_Value, SYMS_EvalMode_Address, SYMS_EvalMode_Register, } SYMS_EvalMode;`
- L24 _enumerator_ `SYMS_EvalIRExtKind_Bytecode = SYMS_EvalOp_COUNT` (scope `__anonb79081370103`) — apears in IR tree
- L27 _enumerator_ `SYMS_EvalIRExtKind_Noop` (scope `__anonb79081370103`) — apears in IR graph
- L29 _enumerator_ `SYMS_EvalIRExtKind_COUNT` (scope `__anonb79081370103`)
- L38 _typedef_ `} SYMS_EvalOpParams;`
- L44 _member_ `struct SYMS_EvalIRTree *children[3];` (scope `SYMS_EvalIRTree::__anonb7908137020a::__anonb79081370308`)
- L45 _member_ `SYMS_EvalOpParams params;` (scope `SYMS_EvalIRTree::__anonb7908137020a::__anonb79081370308`)
- L48 _typedef_ `} SYMS_EvalIRTree;`
- L54 _typedef_ `} SYMS_EvalOpNode;`
- L60 _typedef_ `} SYMS_EvalOpList;`
- L66 _typedef_ `} SYMS_Location;`
- L71 _variable_ `SYMS_READ_ONLY SYMS_GLOBAL SYMS_EvalIRTree syms_eval_ir_tree_nil = {0};`
- L78 _prototype_ `SYMS_EvalOpParams syms_eval_op_params(SYMS_U64 p);`
- L79 _prototype_ `SYMS_EvalOpParams syms_eval_op_params_2u8(SYMS_U8 p1, SYMS_U8 p2);`
- L80 _prototype_ `SYMS_EvalOpParams syms_eval_op_params_2u16(SYMS_U16 p1, SYMS_U16 p2);`
- L82 _prototype_ `void syms_eval_op_push(SYMS_Arena *arena, SYMS_EvalOpList *list, SYMS_EvalOp op, SYMS_EvalOpParams params);`
- L84 _prototype_ `void syms_eval_op_push_bytecode(SYMS_Arena *arena, SYMS_EvalOpList *list, SYMS_String8 bytecode);`
- L85 _prototype_ `void syms_eval_op_list_concat_in_place(SYMS_EvalOpList *left_dst, SYMS_EvalOpList *right_destroyed);`
- L87 _prototype_ `void syms_eval_op_encode_u(SYMS_Arena *arena, SYMS_EvalOpList *list, SYMS_U64 u);`
- L88 _prototype_ `void syms_eval_op_encode_s(SYMS_Arena *arena, SYMS_EvalOpList *list, SYMS_S64 s);`
- L90 _prototype_ `void syms_eval_op_encode_reg_section(SYMS_Arena *arena, SYMS_EvalOpList *list, SYMS_RegSection sec);`
- L91 _prototype_ `void syms_eval_op_encode_reg(SYMS_Arena *arena, SYMS_EvalOpList *list, SYMS_Arch arch, SYMS_RegID reg_id);`
- L96 _prototype_ `SYMS_B32 syms_eval_opcode_type_compatible(SYMS_EvalOp op, SYMS_EvalTypeGroup group);`
- L100 _prototype_ `SYMS_String8 syms_eval_bytecode_from_op_list(SYMS_Arena *arena, SYMS_EvalOpList *list);`
- L104 _prototype_ `SYMS_EvalIRTree* syms_eval_ir_tree_const_u(SYMS_Arena *arena, SYMS_U64 v);`
- L105 _prototype_ `SYMS_EvalIRTree* syms_eval_ir_tree_unary_op(SYMS_Arena *arena, SYMS_EvalOp op, SYMS_EvalTypeGroup group, SYMS_EvalIRTree *c);`
- L107 _prototype_ `SYMS_EvalIRTree* syms_eval_ir_tree_binary_op(SYMS_Arena *arena, SYMS_EvalOp op, SYMS_EvalTypeGroup group, SYMS_EvalIRTree *l, SYMS_EvalIRTree *r);`
- L110 _prototype_ `SYMS_EvalIRTree* syms_eval_ir_tree_binary_op_u(SYMS_Arena *arena, SYMS_EvalOp op, SYMS_EvalIRTree *l, SYMS_EvalIRTree *r);`
- L112 _prototype_ `SYMS_EvalIRTree* syms_eval_ir_tree_conditional(SYMS_Arena *arena, SYMS_EvalIRTree *c, SYMS_EvalIRTree *l, SYMS_EvalIRTree *r);`
- L114 _prototype_ `SYMS_EvalIRTree* syms_eval_ir_tree_bytecode_no_copy(SYMS_Arena *arena, SYMS_String8 bytecode);`

### `Source/Runtime/SymsLib/syms/core/syms_parser.h` (Other)


#### union `SYMS_FileAccel`  
`typedef union SYMS_FileAccel`  
_L10-16_
- L11 _public member_ `SYMS_FileFormat format;`
- L12 _public member_ `SYMS_ElfFileAccel elf_accel;`
- L13 _public member_ `SYMS_PeFileAccel pe_accel;`
- L14 _public member_ `SYMS_PdbFileAccel pdb_accel;`
- L15 _public member_ `SYMS_MachFileAccel mach_accel;`

#### union `SYMS_BinAccel`  
`typedef union SYMS_BinAccel`  
_L18-23_
- L19 _public member_ `SYMS_FileFormat format;`
- L20 _public member_ `SYMS_PeBinAccel pe_accel;`
- L21 _public member_ `SYMS_ElfBinAccel elf_accel;`
- L22 _public member_ `SYMS_MachBinAccel mach_accel;`

#### union `SYMS_BinListAccel`  
`typedef union SYMS_BinListAccel`  
_L25-28_
- L26 _public member_ `SYMS_FileFormat format;`
- L27 _public member_ `SYMS_MachBinListAccel mach_accel;`

#### union `SYMS_DbgAccel`  
`typedef union SYMS_DbgAccel`  
_L30-34_
- L31 _public member_ `SYMS_FileFormat format;`
- L32 _public member_ `SYMS_DwDbgAccel dw_accel;`
- L33 _public member_ `SYMS_PdbDbgAccel pdb_accel;`

#### union `SYMS_UnitSetAccel`  
`typedef union SYMS_UnitSetAccel`  
_L36-40_
- L37 _public member_ `SYMS_FileFormat format;`
- L38 _public member_ `SYMS_DwUnitSetAccel dw_accel;`
- L39 _public member_ `SYMS_PdbUnitSetAccel pdb_accel;`

#### union `SYMS_UnitAccel`  
`typedef union SYMS_UnitAccel`  
_L42-46_
- L43 _public member_ `SYMS_FileFormat format;`
- L44 _public member_ `SYMS_DwUnitAccel dw_accel;`
- L45 _public member_ `SYMS_CvUnitAccel cv_accel;`

#### union `SYMS_MemsAccel`  
`typedef union SYMS_MemsAccel`  
_L48-52_
- L49 _public member_ `SYMS_FileFormat format;`
- L50 _public member_ `SYMS_DwMemsAccel dw_accel;`
- L51 _public member_ `SYMS_CvMemsAccel cv_accel;`

#### union `SYMS_MapAccel`  
`typedef union SYMS_MapAccel`  
_L54-58_
- L55 _public member_ `SYMS_FileFormat format;`
- L56 _public member_ `SYMS_DwMapAccel dw_accel;`
- L57 _public member_ `SYMS_PdbMapAccel pdb_accel;`

#### union `SYMS_LinkMapAccel`  
`typedef union SYMS_LinkMapAccel`  
_L60-64_
- L61 _public member_ `SYMS_FileFormat format;`
- L62 _public member_ `SYMS_DwLinkMapAccel dw_accel;`
- L63 _public member_ `SYMS_PdbLinkMapAccel pdb_accel;`

#### struct `SYMS_MapAndUnit`  
`typedef struct SYMS_MapAndUnit`  
_L69-72_
- L70 _public member_ `SYMS_MapAccel *map;`
- L71 _public member_ `SYMS_UnitAccel *unit;`

#### struct `SYMS_ParseBundle`  
`typedef struct SYMS_ParseBundle`  
_L74-79_
- L75 _public member_ `SYMS_String8 bin_data;`
- L76 _public member_ `SYMS_String8 dbg_data;`
- L77 _public member_ `SYMS_BinAccel *bin;`
- L78 _public member_ `SYMS_DbgAccel *dbg;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_PARSER_H`
- L16 _typedef_ `} SYMS_FileAccel;`
- L23 _typedef_ `} SYMS_BinAccel;`
- L28 _typedef_ `} SYMS_BinListAccel;`
- L34 _typedef_ `} SYMS_DbgAccel;`
- L40 _typedef_ `} SYMS_UnitSetAccel;`
- L46 _typedef_ `} SYMS_UnitAccel;`
- L52 _typedef_ `} SYMS_MemsAccel;`
- L58 _typedef_ `} SYMS_MapAccel;`
- L64 _typedef_ `} SYMS_LinkMapAccel;`
- L72 _typedef_ `} SYMS_MapAndUnit;`
- L79 _typedef_ `} SYMS_ParseBundle;`
- L87 _macro_ `#define syms_accel_is_good(a) ((a) != 0 && (a)->format != SYMS_FileFormat_Null)`
- L92 _prototype_ `SYMS_FileAccel* syms_file_accel_from_data(SYMS_Arena *arena, SYMS_String8 data);`
- L93 _prototype_ `SYMS_FileFormat syms_file_format_from_file(SYMS_FileAccel *file);`
- L98 _prototype_ `SYMS_B32 syms_file_is_bin(SYMS_FileAccel *file);`
- L99 _prototype_ `SYMS_BinAccel* syms_bin_accel_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_FileAccel *file);`
- L103 _prototype_ `SYMS_Arch syms_arch_from_bin(SYMS_BinAccel *bin);` — arch
- L106 _prototype_ `SYMS_ExtFileList syms_ext_file_list_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_BinAccel *bin);` — external info
- L110 _prototype_ `SYMS_SecInfoArray syms_sec_info_array_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_BinAccel *bin);` — binary secs
- L114 _prototype_ `SYMS_U64 syms_default_vbase_from_bin(SYMS_BinAccel *bin);` — default vbase
- L117 _prototype_ `SYMS_U64 syms_entry_point_voff_from_bin(SYMS_BinAccel *bin);` — entry point
- L120 _prototype_ `SYMS_ImportArray syms_imports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_BinAccel *bin);` — imports & exports
- L122 _prototype_ `SYMS_ExportArray syms_exports_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_BinAccel *bin);`
- L128 _prototype_ `SYMS_B32 syms_file_is_bin_list(SYMS_FileAccel *file);`
- L129 _prototype_ `SYMS_BinListAccel*syms_bin_list_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_FileAccel *file);`
- L131 _prototype_ `SYMS_BinInfoArray syms_bin_info_array_from_bin_list(SYMS_Arena *arena, SYMS_BinListAccel *list);`
- L132 _prototype_ `SYMS_BinAccel* syms_bin_accel_from_bin_list_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_BinListAccel *list, SYMS_U64 n);`
- L138 _prototype_ `SYMS_B32 syms_file_is_dbg(SYMS_FileAccel *file);`
- L139 _prototype_ `SYMS_DbgAccel* syms_dbg_accel_from_file(SYMS_Arena *arena, SYMS_String8 data, SYMS_FileAccel *file);`
- L142 _prototype_ `SYMS_B32 syms_bin_is_dbg(SYMS_BinAccel *bin);`
- L143 _prototype_ `SYMS_DbgAccel* syms_dbg_accel_from_bin(SYMS_Arena *arena, SYMS_String8 data, SYMS_BinAccel *bin);`
- L147 _prototype_ `SYMS_Arch syms_arch_from_dbg(SYMS_DbgAccel *dbg);` — arch
- L150 _prototype_ `SYMS_ExtFileList syms_ext_file_list_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg);` — external info
- L154 _prototype_ `SYMS_ExtMatchKey syms_ext_match_key_from_dbg(SYMS_String8 data, SYMS_DbgAccel *dbg);` — match key
- L157 _prototype_ `SYMS_SecInfoArray syms_sec_info_array_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg);` — binary secs
- L161 _prototype_ `SYMS_U64 syms_default_vbase_from_dbg(SYMS_DbgAccel *dbg);` — default vbase
- L164 _prototype_ `SYMS_UnitSetAccel*syms_unit_set_accel_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg);` — compilation units
- L166 _prototype_ `SYMS_U64 syms_unit_count_from_set(SYMS_UnitSetAccel *unit_set);`
- L167 _prototype_ `SYMS_UnitInfo syms_unit_info_from_uid(SYMS_UnitSetAccel *unit_set, SYMS_UnitID uid);`
- L168 _prototype_ `SYMS_UnitNames syms_unit_names_from_uid(SYMS_Arena *arena, SYMS_UnitSetAccel *unit_set, SYMS_UnitID uid);`
- L171 _prototype_ `SYMS_UnitRangeArray syms_unit_ranges_from_set(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitSetAccel *unit_set);`
- L174 _prototype_ `SYMS_UnitID syms_uid_collated_types_from_set(SYMS_UnitSetAccel *unit_set);`
- L175 _prototype_ `SYMS_UnitID syms_uid_collated_public_symbols_from_set(SYMS_UnitSetAccel *unit_set);`
- L178 _prototype_ `SYMS_UnitAccel* syms_unit_accel_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitSetAccel *unit_set, SYMS_UnitID uid);` — symbol parsing
- L182 _prototype_ `SYMS_UnitID syms_uid_from_unit(SYMS_UnitAccel *unit);`
- L184 _prototype_ `SYMS_SymbolIDArray syms_proc_sid_array_from_unit(SYMS_Arena *arena, SYMS_UnitAccel *unit);`
- L185 _prototype_ `SYMS_SymbolIDArray syms_var_sid_array_from_unit(SYMS_Arena *arena, SYMS_UnitAccel *unit);`
- L186 _prototype_ `SYMS_SymbolIDArray syms_type_sid_array_from_unit(SYMS_Arena *arena, SYMS_UnitAccel *unit);`
- L189 _prototype_ `SYMS_SymbolKind syms_symbol_kind_from_sid(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L191 _prototype_ `SYMS_String8 syms_symbol_name_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L196 _prototype_ `SYMS_TypeInfo syms_type_info_from_sid(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L199 _prototype_ `SYMS_ConstInfo syms_const_info_from_sid(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L203 _prototype_ `SYMS_USID syms_type_from_var_sid(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);` — variable info
- L206 _prototype_ `SYMS_U64 syms_voff_from_var_sid(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L209 _prototype_ `SYMS_Location syms_location_from_var_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L212 _prototype_ `SYMS_LocRangeArray syms_location_ranges_from_var_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L215 _prototype_ `SYMS_Location syms_location_from_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_LocID loc_id);`
- L219 _prototype_ `SYMS_MemsAccel* syms_mems_accel_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);` — member info
- L223 _prototype_ `SYMS_U64 syms_mem_count_from_mems(SYMS_MemsAccel *mems);`
- L224 _prototype_ `SYMS_MemInfo syms_mem_info_from_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_MemsAccel *mems, SYMS_U64 n);`
- L228 _prototype_ `SYMS_USID syms_type_from_mem_number(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_MemsAccel *mems, SYMS_U64 n);`
- L231 _prototype_ `SYMS_SigInfo syms_sig_info_from_mem_number(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_MemsAccel *mems, SYMS_U64 n);`
- L235 _prototype_ `SYMS_USID syms_symbol_from_mem_number(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_MemsAccel *mems, SYMS_U64 n);`
- L238 _prototype_ `SYMS_USID syms_containing_type_from_sid(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L241 _prototype_ `SYMS_String8 syms_linkage_name_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L245 _prototype_ `SYMS_EnumMemberArray syms_enum_member_array_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L250 _prototype_ `SYMS_UnitIDAndSig syms_sig_handle_from_proc_sid(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID proc_sid);` — procedure info
- L252 _prototype_ `SYMS_SigInfo syms_sig_info_from_handle(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SigHandle handle);`
- L256 _macro_ `#define syms_proc_vranges_from_sid syms_scope_vranges_from_sid`
- L257 _prototype_ `SYMS_U64RangeArray syms_scope_vranges_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L260 _prototype_ `SYMS_SymbolIDArray syms_scope_children_from_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);`
- L264 _prototype_ `SYMS_Location syms_location_from_proc_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid, SYMS_ProcLoc proc_loc);`
- L267 _prototype_ `SYMS_LocRangeArray syms_location_ranges_from_proc_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid, SYMS_ProcLoc proc_loc);`
- L272 _prototype_ `SYMS_SigInfo syms_sig_info_from_type_sid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit, SYMS_SymbolID sid);` — signature info
- L277 _prototype_ `SYMS_String8 syms_file_name_from_id(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitSetAccel *unit_set, SYMS_UnitID uid, SYMS_FileID file_id);` — line info
- L280 _prototype_ `SYMS_String8Array syms_file_table_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitSetAccel *unit_set, SYMS_UnitID uid);`
- L283 _prototype_ `SYMS_LineParseOut syms_line_parse_from_uid(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitSetAccel *unit_set, SYMS_UnitID uid);`
- L289 _prototype_ `SYMS_MapAccel* syms_type_map_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg);` — name maps
- L291 _prototype_ `SYMS_MapAccel* syms_unmangled_symbol_map_from_dbg(SYMS_Arena *arena,SYMS_String8 data,SYMS_DbgAccel *dbg);`
- L292 _prototype_ `SYMS_UnitID syms_partner_uid_from_map(SYMS_MapAccel *map);`
- L293 _prototype_ `SYMS_USIDList syms_usid_list_from_string(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_MapAndUnit *map_and_unit, SYMS_String8 string);`
- L298 _prototype_ `SYMS_UnitID syms_link_names_uid(SYMS_DbgAccel *dbg);` — linker names
- L300 _prototype_ `SYMS_LinkMapAccel*syms_link_map_from_dbg(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg);`
- L302 _prototype_ `SYMS_B32 syms_link_map_is_complete(SYMS_LinkMapAccel *map);`
- L303 _prototype_ `SYMS_U64 syms_voff_from_link_name(SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_LinkMapAccel *map, SYMS_UnitAccel *link_unit, SYMS_String8 name);`
- L306 _prototype_ `SYMS_LinkNameRecArray syms_link_name_array_from_unit(SYMS_Arena *arena, SYMS_String8 data, SYMS_DbgAccel *dbg, SYMS_UnitAccel *unit);`
- L310 _prototype_ `SYMS_UnitID syms_tls_var_uid_from_dbg(SYMS_DbgAccel *dbg);` — thread vars
- L311 _prototype_ `SYMS_SymbolIDArray syms_tls_var_sid_array_from_unit(SYMS_Arena *arena, SYMS_UnitAccel *thread_unit);`

### `Source/Runtime/SymsLib/syms/core/syms_parser_invariants.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_PARSER_INVARIANTS_H`
- L17 _prototype_ `SYMS_B32 syms_parser_api_invariants(void);` — invariants that apply to the global state of the syms parser API.
- L20 _prototype_ `SYMS_B32 syms_unit_ranges_low_level_invariants(SYMS_UnitRangeArray *ranges);` — invariants that apply to the unit ranges returned by the syms parser API.
- L21 _prototype_ `SYMS_B32 syms_unit_ranges_high_level_invariants(SYMS_UnitRangeArray *ranges, SYMS_UnitSetAccel *unit_set);`
- L24 _prototype_ `SYMS_B32 syms_line_table_low_level_invariants(SYMS_LineTable *line_table);` — invariants that apply to the line tables returned by the syms parser API;
- L25 _prototype_ `SYMS_B32 syms_line_table_high_level_invariants(SYMS_LineTable *line_table);`

### `Source/Runtime/SymsLib/syms/core/unwind/syms_unwind_elf_x64.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L18-30_

#### enum `(anonymous)`  
`enum`  
_L31-38_

#### enum `(anonymous)`  
`enum`  
_L39-43_

#### struct `SYMS_DwEhPtrCtx`  
`typedef struct SYMS_DwEhPtrCtx`  
_L45-50_
- L46 _public member_ `SYMS_U64 raw_base_vaddr;` — address where pointer is being read
- L47 _public member_ `SYMS_U64 text_vaddr;` — base address of section with instructions (used for encoding pointer on SH and IA64)
- L48 _public member_ `SYMS_U64 data_vaddr;` — base address of data section (used for encoding pointer on x86-64)
- L49 _public member_ `SYMS_U64 func_vaddr;` — base address of function where IP is located

#### struct `SYMS_DwCIEUnpacked`  
`typedef struct SYMS_DwCIEUnpacked`  
_L53-69_
- desc: CIE: Common Information Entry
- L54 _public member_ `SYMS_U8 version;`
- L55 _public member_ `SYMS_DwEhPtrEnc lsda_encoding;`
- L56 _public member_ `SYMS_DwEhPtrEnc addr_encoding;`
- L58 _public member_ `SYMS_B8 has_augmentation_size;`
- L59 _public member_ `SYMS_U64 augmentation_size;`
- L60 _public member_ `SYMS_String8 augmentation;`
- L62 _public member_ `SYMS_U64 code_align_factor;`
- L63 _public member_ `SYMS_S64 data_align_factor;`
- L64 _public member_ `SYMS_U64 ret_addr_reg;`
- L66 _public member_ `SYMS_U64 handler_ip;`
- L68 _public member_ `SYMS_U64Range cfi_range;`

#### struct `SYMS_DwCIEUnpackedNode`  
`typedef struct SYMS_DwCIEUnpackedNode`  
_L71-75_
- L72 _public member_ `struct SYMS_DwCIEUnpackedNode *next;`
- L73 _public member_ `SYMS_DwCIEUnpacked cie;`
- L74 _public member_ `SYMS_U64 offset;`

#### struct `SYMS_DwFDEUnpacked`  
`typedef struct SYMS_DwFDEUnpacked`  
_L78-83_
- desc: FDE: Frame Description Entry
- L79 _public member_ `SYMS_U64Range ip_voff_range;`
- L80 _public member_ `SYMS_U64 lsda_ip;`
- L82 _public member_ `SYMS_U64Range cfi_range;`

#### struct `SYMS_DwCFIRecords`  
`typedef struct SYMS_DwCFIRecords`  
_L86-90_
- desc: CFI: Call Frame Information
- L87 _public member_ `SYMS_B32 valid;`
- L88 _public member_ `SYMS_DwCIEUnpacked cie;`
- L89 _public member_ `SYMS_DwFDEUnpacked fde;`

#### enum `SYMS_DwCFICFARule`  
`typedef enum SYMS_DwCFICFARule`  
_L92-95_
- L93 _public enumerator_ `SYMS_DwCFICFARule_REGOFF`
- L94 _public enumerator_ `SYMS_DwCFICFARule_EXPR`

#### struct `SYMS_DwCFICFACell`  
`typedef struct SYMS_DwCFICFACell`  
_L97-106_
- L98 _public member_ `SYMS_DwCFICFARule rule;`

#### union `SYMS_DwCFICFACell::(anonymous)`  
`union`  
_L99-105_

#### struct `SYMS_DwCFICFACell::__anone8606e1f040a::(anonymous)`  
`struct`  
_L100-103_

#### enum `SYMS_DwCFIRegisterRule`  
`typedef enum SYMS_DwCFIRegisterRule`  
_L108-116_
- L109 _public enumerator_ `SYMS_DwCFIRegisterRule_SAME_VALUE`
- L110 _public enumerator_ `SYMS_DwCFIRegisterRule_UNDEFINED`
- L111 _public enumerator_ `SYMS_DwCFIRegisterRule_OFFSET`
- L112 _public enumerator_ `SYMS_DwCFIRegisterRule_VAL_OFFSET`
- L113 _public enumerator_ `SYMS_DwCFIRegisterRule_REGISTER`
- L114 _public enumerator_ `SYMS_DwCFIRegisterRule_EXPRESSION`
- L115 _public enumerator_ `SYMS_DwCFIRegisterRule_VAL_EXPRESSION`

#### struct `SYMS_DwCFICell`  
`typedef struct SYMS_DwCFICell`  
_L118-124_
- L119 _public member_ `SYMS_DwCFIRegisterRule rule;`

#### union `SYMS_DwCFICell::(anonymous)`  
`union`  
_L120-123_

#### struct `SYMS_DwCFIRow`  
`typedef struct SYMS_DwCFIRow`  
_L126-130_
- L127 _public member_ `struct SYMS_DwCFIRow *next;`
- L128 _public member_ `SYMS_DwCFICell *cells;`
- L129 _public member_ `SYMS_DwCFICFACell cfa_cell;`

#### struct `SYMS_DwCFIMachine`  
`typedef struct SYMS_DwCFIMachine`  
_L132-138_
- L133 _public member_ `SYMS_U64 cells_per_row;`
- L134 _public member_ `SYMS_DwCIEUnpacked *cie;`
- L135 _public member_ `SYMS_DwEhPtrCtx *ptr_ctx;`
- L136 _public member_ `SYMS_DwCFIRow *initial_row;`
- L137 _public member_ `SYMS_U64 fde_ip;`

#### enum `(anonymous)`  
`enum`  
_L141-147_

#### enum `(anonymous)`  
`enum`  
_L150-157_

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_UNWIND_ELF_X64_H`
- L17 _typedef_ `typedef SYMS_U8 SYMS_DwEhPtrEnc;`
- L19 _enumerator_ `SYMS_DwEhPtrEnc_TYPE_MASK = 0x0F` (scope `__anone8606e1f0103`)
- L20 _enumerator_ `SYMS_DwEhPtrEnc_PTR = 0x00` (scope `__anone8606e1f0103`) — Pointer sized unsigned value
- L21 _enumerator_ `SYMS_DwEhPtrEnc_ULEB128 = 0x01` (scope `__anone8606e1f0103`) — Unsigned LE base-128 value
- L22 _enumerator_ `SYMS_DwEhPtrEnc_UDATA2 = 0x02` (scope `__anone8606e1f0103`) — Unsigned 16-bit value
- L23 _enumerator_ `SYMS_DwEhPtrEnc_UDATA4 = 0x03` (scope `__anone8606e1f0103`) — Unsigned 32-bit value
- L24 _enumerator_ `SYMS_DwEhPtrEnc_UDATA8 = 0x04` (scope `__anone8606e1f0103`) — Unsigned 64-bit value
- L25 _enumerator_ `SYMS_DwEhPtrEnc_SIGNED = 0x08` (scope `__anone8606e1f0103`) — Signed pointer
- L26 _enumerator_ `SYMS_DwEhPtrEnc_SLEB128 = 0x09` (scope `__anone8606e1f0103`) — Signed LE base-128 value
- L27 _enumerator_ `SYMS_DwEhPtrEnc_SDATA2 = 0x0A` (scope `__anone8606e1f0103`) — Signed 16-bit value
- L28 _enumerator_ `SYMS_DwEhPtrEnc_SDATA4 = 0x0B` (scope `__anone8606e1f0103`) — Signed 32-bit value
- L29 _enumerator_ `SYMS_DwEhPtrEnc_SDATA8 = 0x0C` (scope `__anone8606e1f0103`) — Signed 64-bit value
- L32 _enumerator_ `SYMS_DwEhPtrEnc_MODIF_MASK = 0x70` (scope `__anone8606e1f0203`)
- L33 _enumerator_ `SYMS_DwEhPtrEnc_PCREL = 0x10` (scope `__anone8606e1f0203`) — Value is relative to the current program counter.
- L34 _enumerator_ `SYMS_DwEhPtrEnc_TEXTREL = 0x20` (scope `__anone8606e1f0203`) — Value is relative to the .text section.
- L35 _enumerator_ `SYMS_DwEhPtrEnc_DATAREL = 0x30` (scope `__anone8606e1f0203`) — Value is relative to the .got or .eh_frame_hdr section.
- L36 _enumerator_ `SYMS_DwEhPtrEnc_FUNCREL = 0x40` (scope `__anone8606e1f0203`) — Value is relative to the function.
- L37 _enumerator_ `SYMS_DwEhPtrEnc_ALIGNED = 0x50` (scope `__anone8606e1f0203`) — Value is aligned to an address unit sized boundary.
- L40 _enumerator_ `SYMS_DwEhPtrEnc_INDIRECT = 0x80` (scope `__anone8606e1f0303`) — This flag indicates that value is stored in virtual memory.
- L42 _enumerator_ `SYMS_DwEhPtrEnc_OMIT = 0xFF` (scope `__anone8606e1f0303`)
- L50 _typedef_ `} SYMS_DwEhPtrCtx;`
- L69 _typedef_ `} SYMS_DwCIEUnpacked;`
- L75 _typedef_ `} SYMS_DwCIEUnpackedNode;`
- L83 _typedef_ `} SYMS_DwFDEUnpacked;`
- L90 _typedef_ `} SYMS_DwCFIRecords;`
- L95 _typedef_ `SYMS_DwCFICFARule_REGOFF, SYMS_DwCFICFARule_EXPR, } SYMS_DwCFICFARule;`
- L101 _member_ `SYMS_U64 reg_idx;` (scope `SYMS_DwCFICFACell::__anone8606e1f040a::__anone8606e1f0508`)
- L102 _member_ `SYMS_S64 offset;` (scope `SYMS_DwCFICFACell::__anone8606e1f040a::__anone8606e1f0508`)
- L104 _member_ `SYMS_U64Range expr;` (scope `SYMS_DwCFICFACell::__anone8606e1f040a`)
- L106 _typedef_ `} SYMS_DwCFICFACell;`
- L116 _typedef_ `SYMS_DwCFIRegisterRule_REGISTER, SYMS_DwCFIRegisterRule_EXPRESSION, SYMS_DwCFIRegisterRule_VAL_EXPRESSION, } SYMS_DwCFIRegisterRule;`
- L121 _member_ `SYMS_S64 n;` (scope `SYMS_DwCFICell::__anone8606e1f060a`)
- L122 _member_ `SYMS_U64Range expr;` (scope `SYMS_DwCFICell::__anone8606e1f060a`)
- L124 _typedef_ `} SYMS_DwCFICell;`
- L130 _typedef_ `} SYMS_DwCFIRow;`
- L138 _typedef_ `} SYMS_DwCFIMachine;`
- L140 _typedef_ `typedef SYMS_U8 SYMS_DwCFADecode;`
- L142 _enumerator_ `SYMS_DwCFADecode_NOP = 0x0` (scope `__anone8606e1f0703`)
- L144 _enumerator_ `SYMS_DwCFADecode_ADDRESS = 0x9` (scope `__anone8606e1f0703`) — 1,2,4,8 reserved for literal byte sizes
- L145 _enumerator_ `SYMS_DwCFADecode_ULEB128 = 0xA` (scope `__anone8606e1f0703`)
- L146 _enumerator_ `SYMS_DwCFADecode_SLEB128 = 0xB` (scope `__anone8606e1f0703`)
- L149 _typedef_ `typedef SYMS_U16 SYMS_DwCFAControlBits;`
- L151 _enumerator_ `SYMS_DwCFAControlBits_DEC1_MASK = 0x00F` (scope `__anone8606e1f0803`)
- L152 _enumerator_ `SYMS_DwCFAControlBits_DEC2_MASK = 0x0F0` (scope `__anone8606e1f0803`)
- L153 _enumerator_ `SYMS_DwCFAControlBits_IS_REG_0 = 0x100` (scope `__anone8606e1f0803`)
- L154 _enumerator_ `SYMS_DwCFAControlBits_IS_REG_1 = 0x200` (scope `__anone8606e1f0803`)
- L155 _enumerator_ `SYMS_DwCFAControlBits_IS_REG_2 = 0x400` (scope `__anone8606e1f0803`)
- L156 _enumerator_ `SYMS_DwCFAControlBits_NEW_ROW = 0x800` (scope `__anone8606e1f0803`)
- L159 _variable_ `SYMS_GLOBAL SYMS_DwCFAControlBits syms_unwind_elf__cfa_control_bits_kind1[SYMS_DwCFADetail_OPL_KIND1 + 1];`
- L160 _variable_ `SYMS_GLOBAL SYMS_DwCFAControlBits syms_unwind_elf__cfa_control_bits_kind2[SYMS_DwCFADetail_OPL_KIND2 + 1];`
- L163 _macro_ `#define SYMS_UNWIND_ELF_X64__REG_SLOT_COUNT 17` — NOTE(allen): register codes for unwinding match the SYMS_DwRegX64 register codes
- L168 _prototype_ `SYMS_UnwindResult syms_unwind_elf_x64(SYMS_String8 bin_data, SYMS_ElfBinAccel *bin, SYMS_U64 bin_base, SYMS_MemoryView *memview, SYMS_U64 stack_pointer, SYMS_DwRegsX64 *regs_in_out);`
- L172 _prototype_ `SYMS_UnwindResult syms_unwind_elf_x64__apply_rules(SYMS_String8 bin_data, SYMS_DwCFIRow *row, SYMS_U64 text_base_vaddr, SYMS_MemoryView *memview, SYMS_U64 stack_pointer, SYMS_DwRegsX64 *regs_in_out);`
- L180 _prototype_ `void syms_unwind_elf_x64__init(void);`
- L182 _prototype_ `SYMS_U64 syms_unwind_elf_x64__parse_pointer(void *base, SYMS_U64Range range, SYMS_DwEhPtrCtx *ptr_ctx, SYMS_DwEhPtrEnc ptr_enc, SYMS_U64 off, SYMS_U64 *ptr_out);`
- L187 _prototype_ `void syms_unwind_elf_x64__eh_frame_parse_cie(void *base,SYMS_U64Range range,SYMS_DwEhPtrCtx *ptr_ctx, SYMS_U64 off, SYMS_DwCIEUnpacked *cie_out);` — - eh_frame parsing
- L189 _prototype_ `void syms_unwind_elf_x64__eh_frame_parse_fde(void *base,SYMS_U64Range range,SYMS_DwEhPtrCtx *ptr_ctx, SYMS_DwCIEUnpacked *parent_cie, SYMS_U64 off, SYMS_DwFDEUnpacked *fde_out);`
- L193 _prototype_ `syms_unwind_elf_x64__eh_frame_cfi_from_ip__sloppy(void *base, SYMS_U64Range range, SYMS_DwEhPtrCtx *ptr_ctx, SYMS_U64 ip_voff);`
- L196 _prototype_ `syms_unwind_elf_x64__eh_frame_hdr_from_ip(void *base, SYMS_U64Range eh_frame_hdr_range, SYMS_U64Range eh_frame_range, SYMS_DwEhPtrCtx *ptr_ctx, SYMS_U64 ip_voff);`
- L204 _prototype_ `SYMS_DwCFIMachine syms_unwind_elf_x64__machine_make(SYMS_U64 cells_per_row, SYMS_DwCIEUnpacked *cie, SYMS_DwEhPtrCtx *ptr_ctx);`
- L206 _prototype_ `void syms_unwind_elf_x64__machine_equip_initial_row(SYMS_DwCFIMachine *machine, SYMS_DwCFIRow *initial_row);`
- L208 _prototype_ `void syms_unwind_elf_x64__machine_equip_fde_ip(SYMS_DwCFIMachine *machine, SYMS_U64 fde_ip);`
- L211 _prototype_ `SYMS_DwCFIRow*syms_unwind_elf_x64__row_alloc(SYMS_Arena *arena, SYMS_U64 cells_per_row);`
- L212 _prototype_ `void syms_unwind_elf_x64__row_zero(SYMS_DwCFIRow *row, SYMS_U64 cells_per_row);`
- L213 _prototype_ `void syms_unwind_elf_x64__row_copy(SYMS_DwCFIRow *dst, SYMS_DwCFIRow *src, SYMS_U64 cells_per_row);`
- L216 _prototype_ `SYMS_B32 syms_unwind_elf_x64__machine_run_to_ip(void *base, SYMS_U64Range range, SYMS_DwCFIMachine *machine, SYMS_U64 target_ip, SYMS_DwCFIRow *row_out);`

### `Source/Runtime/SymsLib/syms/core/unwind/syms_unwind_pe_x64.h` (Other)


#### enum `(anonymous)`  
`enum`  
_L11-23_

#### union `SYMS_UnwindPeCode`  
`typedef union SYMS_UnwindPeCode`  
_L28-34_
- L33 _public member_ `SYMS_U16 u16;`

#### struct `SYMS_UnwindPeCode::(anonymous)`  
`struct`  
_L29-32_

#### enum `(anonymous)`  
`enum`  
_L37-42_

#### struct `SYMS_UnwindPeInfo`  
`typedef struct SYMS_UnwindPeInfo`  
_L49-54_
- L50 _public member_ `SYMS_U8 header;`
- L51 _public member_ `SYMS_U8 prolog_size;`
- L52 _public member_ `SYMS_U8 codes_num;`
- L53 _public member_ `SYMS_U8 frame;`

#### enum `(anonymous)`  
`enum`  
_L60-77_

#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_UNWIND_PE_X64_H`
- L10 _typedef_ `typedef SYMS_U32 SYMS_UnwindPeOpCode;`
- L12 _enumerator_ `SYMS_UnwindPeOpCode_PUSH_NONVOL = 0` (scope `__anon51e69d5d0103`)
- L13 _enumerator_ `SYMS_UnwindPeOpCode_ALLOC_LARGE = 1` (scope `__anon51e69d5d0103`)
- L14 _enumerator_ `SYMS_UnwindPeOpCode_ALLOC_SMALL = 2` (scope `__anon51e69d5d0103`)
- L15 _enumerator_ `SYMS_UnwindPeOpCode_SET_FPREG = 3` (scope `__anon51e69d5d0103`)
- L16 _enumerator_ `SYMS_UnwindPeOpCode_SAVE_NONVOL = 4` (scope `__anon51e69d5d0103`)
- L17 _enumerator_ `SYMS_UnwindPeOpCode_SAVE_NONVOL_FAR = 5` (scope `__anon51e69d5d0103`)
- L18 _enumerator_ `SYMS_UnwindPeOpCode_EPILOG = 6` (scope `__anon51e69d5d0103`)
- L19 _enumerator_ `SYMS_UnwindPeOpCode_SPARE_CODE = 7` (scope `__anon51e69d5d0103`)
- L20 _enumerator_ `SYMS_UnwindPeOpCode_SAVE_XMM128 = 8` (scope `__anon51e69d5d0103`)
- L21 _enumerator_ `SYMS_UnwindPeOpCode_SAVE_XMM128_FAR = 9` (scope `__anon51e69d5d0103`)
- L22 _enumerator_ `SYMS_UnwindPeOpCode_PUSH_MACHFRAME = 10` (scope `__anon51e69d5d0103`)
- L25 _macro_ `#define SYMS_UnwindPeCode_CodeFromFlags(x) ((x) & 0xf)`
- L26 _macro_ `#define SYMS_UnwindPeCode_InfoFromFlags(x) (((x) & 0xf0) >> 4)`
- L30 _member_ `SYMS_U8 off_in_prolog;` (scope `SYMS_UnwindPeCode::__anon51e69d5d0208`)
- L31 _member_ `SYMS_U8 flags;` (scope `SYMS_UnwindPeCode::__anon51e69d5d0208`)
- L34 _typedef_ `} SYMS_UnwindPeCode;`
- L36 _typedef_ `typedef SYMS_U8 SYMS_UnwindPeInfoFlags;`
- L38 _enumerator_ `SYMS_UnwindPeInfoFlag_EHANDLER = (1 << 0)` (scope `__anon51e69d5d0303`)
- L39 _enumerator_ `SYMS_UnwindPeInfoFlag_UHANDLER = (1 << 1)` (scope `__anon51e69d5d0303`)
- L40 _enumerator_ `SYMS_UnwindPeInfoFlag_FHANDLER = SYMS_UnwindPeInfoFlag_EHANDLER|SYMS_UnwindPeInfoFlag_UHANDLER` (scope `__anon51e69d5d0303`)
- L41 _enumerator_ `SYMS_UnwindPeInfoFlag_CHAINED = (1 << 2)` (scope `__anon51e69d5d0303`)
- L44 _macro_ `#define SYMS_UnwindPeInfo_VersionFromHeader(x) ((x) & 0x07)`
- L45 _macro_ `#define SYMS_UnwindPeInfo_FlagsFromHeader(x) (((x) & 0xf8) >> 3)`
- L46 _macro_ `#define SYMS_UnwindPeInfo_RegFromFrame(x) ((x) & 0x0f)`
- L47 _macro_ `#define SYMS_UnwindPeInfo_OffFromFrame(x) (((x) & 0xf0) >> 4)`
- L54 _typedef_ `} SYMS_UnwindPeInfo;`
- L59 _typedef_ `typedef SYMS_U8 SYMS_UnwindPeX64GprReg;`
- L61 _enumerator_ `SYMS_UnwindPeX64GprReg_RAX = 0` (scope `__anon51e69d5d0403`)
- L62 _enumerator_ `SYMS_UnwindPeX64GprReg_RCX = 1` (scope `__anon51e69d5d0403`)
- L63 _enumerator_ `SYMS_UnwindPeX64GprReg_RDX = 2` (scope `__anon51e69d5d0403`)
- L64 _enumerator_ `SYMS_UnwindPeX64GprReg_RBX = 3` (scope `__anon51e69d5d0403`)
- L65 _enumerator_ `SYMS_UnwindPeX64GprReg_RSP = 4` (scope `__anon51e69d5d0403`)
- L66 _enumerator_ `SYMS_UnwindPeX64GprReg_RBP = 5` (scope `__anon51e69d5d0403`)
- L67 _enumerator_ `SYMS_UnwindPeX64GprReg_RSI = 6` (scope `__anon51e69d5d0403`)
- L68 _enumerator_ `SYMS_UnwindPeX64GprReg_RDI = 7` (scope `__anon51e69d5d0403`)
- L69 _enumerator_ `SYMS_UnwindPeX64GprReg_R8 = 8` (scope `__anon51e69d5d0403`)
- L70 _enumerator_ `SYMS_UnwindPeX64GprReg_R9 = 9` (scope `__anon51e69d5d0403`)
- L71 _enumerator_ `SYMS_UnwindPeX64GprReg_R10 = 10` (scope `__anon51e69d5d0403`)
- L72 _enumerator_ `SYMS_UnwindPeX64GprReg_R11 = 11` (scope `__anon51e69d5d0403`)
- L73 _enumerator_ `SYMS_UnwindPeX64GprReg_R12 = 12` (scope `__anon51e69d5d0403`)
- L74 _enumerator_ `SYMS_UnwindPeX64GprReg_R13 = 13` (scope `__anon51e69d5d0403`)
- L75 _enumerator_ `SYMS_UnwindPeX64GprReg_R14 = 14` (scope `__anon51e69d5d0403`)
- L76 _enumerator_ `SYMS_UnwindPeX64GprReg_R15 = 15` (scope `__anon51e69d5d0403`)
- L84 _prototype_ `SYMS_UnwindResult syms_unwind_pe_x64(SYMS_String8 bin_data, SYMS_PeBinAccel *bin, SYMS_U64 bin_base, SYMS_MemoryView *memview, SYMS_RegX64 *regs_in_out);`
- L87 _prototype_ `SYMS_UnwindResult syms_unwind_pe_x64__epilog(SYMS_String8 bin_data, SYMS_PeBinAccel *bin, SYMS_U64 base, SYMS_MemoryView *memview, SYMS_RegX64 *regs_in_out);`
- L94 _prototype_ `SYMS_U32 syms_unwind_pe_x64__slot_count_from_op_code(SYMS_UnwindPeOpCode op_code);`
- L95 _prototype_ `SYMS_B32 syms_unwind_pe_x64__voff_is_in_epilog(SYMS_String8 bin_data, SYMS_PeBinAccel *bin, SYMS_U64 voff, SYMS_PeIntelPdata *final_pdata);`
- L98 _prototype_ `SYMS_Reg64* syms_unwind_pe_x64__gpr_reg(SYMS_RegX64 *regs, SYMS_UnwindPeX64GprReg reg_id);`

### `Source/Runtime/SymsLib/syms/overrides/syms_crt_overrides.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_CRT_DEFAULT_OVERRIDES_H`
- L7 _macro_ `# define SYMS_OVERRIDE_FUNC`
- L14 _typedef_ `typedef __int8 SYMS_S8;`
- L15 _typedef_ `typedef __int16 SYMS_S16;`
- L16 _typedef_ `typedef __int32 SYMS_S32;`
- L17 _typedef_ `typedef __int64 SYMS_S64;`
- L18 _typedef_ `typedef unsigned __int8 SYMS_U8;`
- L19 _typedef_ `typedef unsigned __int16 SYMS_U16;`
- L20 _typedef_ `typedef unsigned __int32 SYMS_U32;`
- L21 _typedef_ `typedef unsigned __int64 SYMS_U64;`
- L23 _macro_ `#define SYMS_PRIu64 "I64u"`
- L24 _macro_ `#define SYMS_PRId64 "I64d"`
- L25 _macro_ `#define SYMS_PRIx64 "I64x"`
- L32 _typedef_ `typedef int8_t SYMS_S8;`
- L33 _typedef_ `typedef int16_t SYMS_S16;`
- L34 _typedef_ `typedef int32_t SYMS_S32;`
- L35 _typedef_ `typedef int64_t SYMS_S64;`
- L36 _typedef_ `typedef uint8_t SYMS_U8;`
- L37 _typedef_ `typedef uint16_t SYMS_U16;`
- L38 _typedef_ `typedef uint32_t SYMS_U32;`
- L39 _typedef_ `typedef uint64_t SYMS_U64;`
- L41 _macro_ `#define SYMS_PRIu64 PRIu64`
- L42 _macro_ `#define SYMS_PRId64 PRId64`
- L43 _macro_ `#define SYMS_PRIx64 PRIx64`
- L47 _macro_ `#define SYMS_S8 SYMS_S8`
- L48 _macro_ `#define SYMS_S16 SYMS_S16`
- L49 _macro_ `#define SYMS_S32 SYMS_S32`
- L50 _macro_ `#define SYMS_S64 SYMS_S64`
- L51 _macro_ `#define SYMS_U8 SYMS_U8`
- L52 _macro_ `#define SYMS_U16 SYMS_U16`
- L53 _macro_ `#define SYMS_U32 SYMS_U32`
- L54 _macro_ `#define SYMS_U64 SYMS_U64`
- L58 _macro_ `#define SYMS_ASSERT_BREAK(m) assert(!(#m))`
- L65 _macro_ `#define syms_memmove memmove`
- L66 _macro_ `#define syms_memset memset`
- L67 _macro_ `#define syms_memcmp memcmp`
- L68 _macro_ `#define syms_strlen strlen`
- L69 _macro_ `#define syms_memisnull(ptr,sz) (memchr(ptr,0,sz)!=NULL)`
- L73 _macro_ `#define syms_mem_reserve(s) malloc(s)`
- L74 _macro_ `#define syms_mem_commit(p,s) (1)`
- L75 _macro_ `#define syms_mem_decommit(p,s) ((void)0)`
- L76 _macro_ `#define syms_mem_release(p,s) free(p)`
- L83 _macro_ `#define SYMS_ARENA_RESERVE_SIZE (1 << 20)` — @notes Since we are relying on malloc & free, and not using commit/decommit, we want a smaller reserve chunk size than the default, because malloc automatically reserves and commits everything it allocates. And wasting too much commit isn't very great. We also want to set the commit size equal to the reserve size to avoid wasting time on commit logic that won't matter.
- L84 _macro_ `#define SYMS_ARENA_COMMIT_SIZE (1 << 20)`

### `Source/Runtime/SymsLib/syms/overrides/syms_default_arena.h` (Other)


#### struct `SYMS_DefArena`  
`typedef struct SYMS_DefArena`  
_L42-51_
- L43 _public member_ `struct SYMS_DefArena *prev;`
- L44 _public member_ `struct SYMS_DefArena *current;`
- L45 _public member_ `SYMS_U64 base_pos;`
- L46 _public member_ `SYMS_U64 pos;`
- L47 _public member_ `SYMS_U64 cmt;`
- L48 _public member_ `SYMS_U64 cap;`
- L49 _public member_ `SYMS_U64 align;`
- L50 _public member_ `struct SYMS_ArenaDev *dev;`

#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_DEFAULT_ARENA_H`
- L23 _macro_ `# define SYMS_ENABLE_DEV_ARENA 0`
- L29 _macro_ `#define SYMS_ARENA_HEADER_SIZE 128`
- L36 _macro_ `# define SYMS_ARENA_RESERVE_SIZE (64 << 20)`
- L39 _macro_ `# define SYMS_ARENA_COMMIT_SIZE (64 << 10)`
- L51 _typedef_ `} SYMS_DefArena;`
- L53 _prototype_ `SYMS_OVERRIDE_FUNC SYMS_DefArena* syms_arena_def_alloc__sized(SYMS_U64 init_res, SYMS_U64 init_cmt);`
- L54 _prototype_ `SYMS_OVERRIDE_FUNC SYMS_DefArena* syms_arena_def_alloc(void);`
- L55 _prototype_ `SYMS_OVERRIDE_FUNC void syms_arena_def_release(SYMS_DefArena *arena);`
- L56 _prototype_ `SYMS_OVERRIDE_FUNC void* syms_arena_def_push(SYMS_DefArena *arena, SYMS_U64 size);`
- L57 _prototype_ `SYMS_OVERRIDE_FUNC void syms_arena_def_pop_to(SYMS_DefArena *arena, SYMS_U64 pos);`
- L58 _prototype_ `SYMS_OVERRIDE_FUNC void syms_arena_def_set_auto_align(SYMS_DefArena *arena, SYMS_U64 pow2_align);`
- L59 _prototype_ `SYMS_OVERRIDE_FUNC void syms_arena_def_absorb(SYMS_DefArena *arena, SYMS_DefArena *sub);`
- L61 _macro_ `#define SYMS_Arena SYMS_DefArena`
- L62 _macro_ `#define syms_arena_alloc__impl syms_arena_def_alloc`
- L63 _macro_ `#define syms_arena_release__impl syms_arena_def_release`
- L64 _macro_ `#define syms_arena_get_pos__impl syms_arena_def_pos`
- L65 _macro_ `#define syms_arena_push__impl syms_arena_def_push`
- L66 _macro_ `#define syms_arena_pop_to__impl syms_arena_def_pop_to`
- L67 _macro_ `#define syms_arena_set_auto_align__impl syms_arena_def_set_auto_align`
- L68 _macro_ `#define syms_arena_absorb__impl syms_arena_def_absorb`
- L69 _macro_ `#define syms_arena_tidy__impl(a) ((void)(a))`

### `Source/Runtime/SymsLib/syms/overrides/syms_default_helpers.h` (Other)


#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_DEFAULT_HELPERS_H`
- L9 _prototype_ `static SYMS_U32 syms_override_memisnull(void*ptr, SYMS_U64 size);`

### `Source/Runtime/SymsLib/syms/overrides/syms_default_scratch.h` (Other)


#### struct `SYMS_DefaultScratchPool`  
`typedef struct SYMS_DefaultScratchPool`  
_L9-11_
- L10 _public member_ `SYMS_Arena *arenas[2];`

#### Free symbols / members of external scopes

- L4 _macro_ `#define SYMS_DEFAULT_SCRATCH_H`
- L11 _typedef_ `} SYMS_DefaultScratchPool;`
- L16 _prototype_ `SYMS_OVERRIDE_FUNC SYMS_Arena* syms_default_get_implicit_thread_arena(SYMS_Arena **conflicts, SYMS_U64 conflict_count);`
- L17 _macro_ `#define syms_get_implicit_thread_arena__impl syms_default_get_implicit_thread_arena`
- L18 _macro_ `#define syms_scratch_pool_tidy__impl() ((void)0)`

### `Source/Runtime/SymsLib/syms/syms_inc.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_INC_H`

### `Source/Runtime/SymsLib/syms/syms_serial_inc.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_SERIAL_INC_H`

### `Source/Runtime/SymsLib/syms/symslib.h` (Other)


#### Free symbols / members of external scopes

- L5 _macro_ `#define SYMS_API`
- L11 _macro_ `#define SYMS_READ_ONLY`
