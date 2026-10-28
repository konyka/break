# Developer / ShaderPreprocessor

- module root: `Source/Developer/ShaderPreprocessor`
- headers: 8; symbols: 299
- symbol kinds: enum=5, enumerator=38, function=9, macro=164, member=26, prototype=41, struct=6, typedef=10
- PrivateDependencyModuleNames: Core, RenderCore

### `Source/Developer/ShaderPreprocessor/Private/PreprocessorPrivate.h` (Private)


#### enum `EMessageType`  
`enum class EMessageType`  
_L10-15_
- L12 _public enumerator_ `Error = 0`
- L13 _public enumerator_ `Warn = 1`
- L14 _public enumerator_ `ShaderMetaData = 2`

#### Free symbols / members of external scopes

- L22 _function_ `inline EMessageType FilterPreprocessorError(const FString& ErrorMsg)` — Filter preprocessor errors. @param ErrorMsg - The error message. @returns true if the message is valid and has not been filtered out.
- L47 _function_ `static void ExtractDirective(FString& OutString, FString WarningString)`

### `Source/Developer/ShaderPreprocessor/Private/StbConfig.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `void* StbMalloc(size_t Size);`
- L12 _prototype_ `void* StbRealloc(void* Pointer, size_t Size);`
- L13 _prototype_ `void StbFree(void* Pointer);`
- L14 _prototype_ `char* StbStrDup(const char* String);`
- L15 _prototype_ `size_t StbLcgNext();`
- L16 _prototype_ `void StbAssertFailed(const char* File, int Line, const char* Expression, const char* Format, ...);`
- L21 _macro_ `#define STB_COMMON_MALLOC(Size) StbMalloc(Size)`
- L22 _macro_ `#define STB_COMMON_REALLOC(Pointer, Size) StbRealloc(Pointer, Size)`
- L23 _macro_ `#define STB_COMMON_FREE(Pointer) StbFree(Pointer)`
- L24 _macro_ `#define STB_COMMON_STRDUP(String) StbStrDup(String)`
- L25 _macro_ `#define STB_LCG_NEXT() StbLcgNext()`
- L27 _macro_ `#define STB_COMMON_ASSERT(expr) \`
- L29 _macro_ `#define STB_COMMON_ASSERTF(expr, fmt, ...) \`

### `Source/Developer/ShaderPreprocessor/Private/stb_preprocess/cond_expr.h` (Private)


#### enum `(anonymous)`  
``  
_L6-11_

#### Free symbols / members of external scopes

- L7 _enumerator_ `CE_RESULT_ok` (scope `__anoncd121ff70103`)
- L8 _enumerator_ `CE_RESULT_syntax_error` (scope `__anoncd121ff70103`)
- L9 _enumerator_ `CE_RESULT_division_by_zero` (scope `__anoncd121ff70103`)
- L10 _enumerator_ `CE_RESULT_overflow` (scope `__anoncd121ff70103`)
- L14 _macro_ `#define CONDEXPR_DEF extern "C"`
- L16 _macro_ `#define CONDEXPR_DEF extern`
- L19 _prototype_ `CONDEXPR_DEF int evaluate_integer_constant_expression(char* p, int* error);`
- L20 _prototype_ `CONDEXPR_DEF int evaluate_integer_constant_expression_as_condition(char* p, int* error);`

### `Source/Developer/ShaderPreprocessor/Private/stb_preprocess/preprocessor.h` (Private)


#### enum `(anonymous)`  
``  
_L7-34_

#### enum `(anonymous)`  
``  
_L37-44_

#### struct `(anonymous)`  
``  
_L51-55_

#### struct `(anonymous)`  
``  
_L58-63_

#### Free symbols / members of external scopes

- L8 _enumerator_ `PP_RESULT_ok` (scope `__anon463d12fc0103`)
- L9 _enumerator_ `PP_RESULT_supplementary` (scope `__anon463d12fc0103`) — extra information associated with previous warning/error
- L10 _enumerator_ `PP_RESULT_undef_of_undefined_macro` (scope `__anon463d12fc0103`) — by default this is not an error
- L11 _enumerator_ `PP_RESULT_explicit_warning` (scope `__anon463d12fc0103`)
- L13 _enumerator_ `PP_RESULT_internal_error_out_of_memory` (scope `__anon463d12fc0103`)
- L15 _enumerator_ `PP_RESULT_ERROR = 5` (scope `__anon463d12fc0103`)
- L17 _enumerator_ `PP_RESULT_counter_overflowed` (scope `__anon463d12fc0103`)
- L18 _enumerator_ `PP_RESULT_too_many_arguments_to_macro` (scope `__anon463d12fc0103`)
- L19 _enumerator_ `PP_RESULT_invalid_char` (scope `__anon463d12fc0103`)
- L20 _enumerator_ `PP_RESULT_unrecognized_directive` (scope `__anon463d12fc0103`)
- L21 _enumerator_ `PP_RESULT_directive_not_at_start_of_line` (scope `__anon463d12fc0103`)
- L22 _enumerator_ `PP_RESULT_unexpected_character_in_directive` (scope `__anon463d12fc0103`)
- L23 _enumerator_ `PP_RESULT_unexpected_character_after_end_of_directive` (scope `__anon463d12fc0103`)
- L24 _enumerator_ `PP_RESULT_undef_of_predefined_macro` (scope `__anon463d12fc0103`)
- L25 _enumerator_ `PP_RESULT_identifier_too_long` (scope `__anon463d12fc0103`)
- L26 _enumerator_ `PP_RESULT_malformed_pragma_message` (scope `__anon463d12fc0103`)
- L27 _enumerator_ `PP_RESULT_malformed_line_filename` (scope `__anon463d12fc0103`)
- L28 _enumerator_ `PP_RESULT_invalid_line_linenumber` (scope `__anon463d12fc0103`)
- L29 _enumerator_ `PP_RESULT_syntax_error_conditional_expression` (scope `__anon463d12fc0103`)
- L30 _enumerator_ `PP_RESULT_conditional_expression_overflow` (scope `__anon463d12fc0103`)
- L31 _enumerator_ `PP_RESULT_conditional_expression_division_by_zero` (scope `__anon463d12fc0103`)
- L33 _enumerator_ `PP_RESULT_count` (scope `__anon463d12fc0103`)
- L38 _enumerator_ `PP_RESULT_MODE_error` (scope `__anon463d12fc0203`) — default error type is 0 to simplify initialization
- L39 _enumerator_ `PP_RESULT_MODE_warning` (scope `__anon463d12fc0203`)
- L40 _enumerator_ `PP_RESULT_MODE_supplementary` (scope `__anon463d12fc0203`)
- L42 _enumerator_ `PP_RESULT_MODE_warning_fast` (scope `__anon463d12fc0203`)
- L43 _enumerator_ `PP_RESULT_MODE_no_warning` (scope `__anon463d12fc0203`)
- L52 _member_ `char* filename;` (scope `__anon463d12fc0308`)
- L53 _member_ `int line_number;` (scope `__anon463d12fc0308`)
- L54 _member_ `int column;` (scope `__anon463d12fc0308`)
- L55 _typedef_ `} pp_where;`
- L59 _member_ `char* message;` (scope `__anon463d12fc0408`)
- L60 _member_ `int diagnostic_code;` (scope `__anon463d12fc0408`)
- L61 _member_ `int error_level;` (scope `__anon463d12fc0408`)
- L62 _member_ `pp_where* where;` (scope `__anon463d12fc0408`)
- L63 _typedef_ `} pp_diagnostic;`
- L67 _macro_ `#define STB_PP_DEF extern "C"`
- L69 _macro_ `#define STB_PP_DEF extern`
- L73 _typedef_ `typedef const char* (*loadfile_callback_func)(const char* filename, void* custom_context, size_t* out_length);` — callback function required to be passed to init_preprocessor for implementation of file loading functionality
- L76 _typedef_ `typedef void (*freefile_callback_func)(const char* filename, const char* loaded_file, void* custom_context);` — callback function required to be passed to init_preprocessor for implementation of freeing loaded files
- L82 _typedef_ `typedef const char* (*resolveinclude_callback_func)(const char* path, unsigned int path_len, const char* parent, void* custom_context);` — callback function required to be passed to init_preprocessor for implementation of include resolution the callback is expected to handle both absolute and relative paths (the latter relative to the given "parent" file path) note: returned resolved paths must remain valid for the lifetime of a single preprocessor execution
- L93 _typedef_ `typedef const char* (*custommacro_begin_callback_func)(const char* original_text, void* custom_context);` — Callback functions for custom macros.  Custom macros return their own substitution text, which is then further preprocessed. The substitution text must include 15 bytes of padding past the null terminator, as the preprocessor uses SSE reads which may read past the null terminator.  The text passed to the callback includes the macro identifier and its arguments, with backslashes removed.  A function is called when entering the macro, and again when complete, allowing stateful logic based on whether parsing is inside a certain custom macro.  Any custom macro will automatically be disabled inside itself, with the idea that this allows a singleton buffer for the substitution text, as there's no concern about nested calls.  If text is dynamically allocated, the caller is responsible for freeing it.  It's also valid to return the original text passed in as the substitution text, if you just want to set some state inside the context, and not actually change the macro text -- since the macro is disabled, it will then be echoed as non-macro text.
- L94 _typedef_ `typedef void (*custommacro_end_callback_func)(const char* original_text, void* custom_context, const char* substitution_text);`
- L97 _prototype_ `STB_PP_DEF void init_preprocessor( loadfile_callback_func load_callback, freefile_callback_func free_callback, resolveinclude_callback_func resolve_callback, custommacro_begin_callback_func custommacro_begin_callback, custommacro_end_callback_func custommacro_end_callback);` — init function must be called once before any invocations of preprocess_file
- L107 _prototype_ `STB_PP_DEF char* preprocess_file( const char* filename, void* custom_context, struct macro_definition** predefined_macros, int num_predefined_macros, pp_diagnostic** pd, int* num_pd, char* output_inlinebuffer, size_t output_inlinebuffersize);` — main preprocessing execution function; returns the preprocessed string and sets any diagnostic messages in the pd array (setting num_pd to the diagnostic count). preprocessor_file_free should be called for each invocation to free any allocated memory.
- L117 _prototype_ `STB_PP_DEF int preprocessor_file_size(char* text);`
- L118 _prototype_ `STB_PP_DEF int preprocessor_file_capacity(char* text);`
- L122 _prototype_ `STB_PP_DEF char* preprocessor_file_append(char* text, const char* appended_text, int appended_text_len);` — Append text to the end of a file generated with preprocess_file.  Can save reallocation overhead relative to appending the text later, as there will usually be slack space available.
- L125 _prototype_ `STB_PP_DEF void preprocessor_file_free(char* text, pp_diagnostic* pd);` — frees memory allocated by preprocess_file (preprocessed results and diagnostic messages)
- L129 _prototype_ `STB_PP_DEF struct macro_definition* pp_define(struct stb_arena* a, const char* def);` — constructs a preprocessor definition, allocating on the given arena. "def" should be in the format: DEFINE_NAME DEFINE_VALUE
- L133 _prototype_ `STB_PP_DEF struct macro_definition* pp_define_custom_macro(struct stb_arena* a, const char* identifier, unsigned char preprocess_args_first);` — specifies a custom macro name, with substitution to be handled by the custom macro callback functions.  If "preprocess_args_first" is set, args of macro are preprocessed before begin callback (and again afterwards).
- L137 _prototype_ `STB_PP_DEF void pp_set_warning_mode(int result_code, int result_mode);` — override behaviour of a particular error result (can be used to, for instance, downgrade an error to a warning or a "no warning" i.e. valid case).
- L140 _prototype_ `STB_PP_DEF unsigned int preprocessor_hash(const char* data, size_t len);` — hash function for string of length 'len', roughly xxhash32

### `Source/Developer/ShaderPreprocessor/Private/stb_preprocess/stb_alloc.h` (Private)


#### struct `stb_arena`  
`struct stb_arena`  
_L34-43_
- desc: You allocate this structure yourself; initialize to all 0s and don't mess with the innards. Optionally, you can initialize the first field to the default block size you want, e.g. stb_arena arena = { 65536 };
- L36 _public member_ `size_t default_block_size;`
- L37 _public member_ `size_t block_size;`
- L38 _public member_ `void** blocks;`
- L39 _public member_ `unsigned char* last_block;`
- L40 _public member_ `int num_blocks;`
- L41 _public member_ `size_t last_block_alloc_offset;`
- L42 _public member_ `size_t last_block_size;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define STB_ALLOC_DEF extern "C"`
- L14 _macro_ `#define STB_ALLOC_DEF extern`
- L20 _prototype_ `STB_ALLOC_DEF void* stb_arena_alloc(struct stb_arena* a, size_t size);` — allocate from an arena
- L21 _prototype_ `STB_ALLOC_DEF void* stb_arena_alloc_aligned(struct stb_arena* a, size_t size, size_t align);`
- L24 _prototype_ `STB_ALLOC_DEF char* stb_arena_alloc_string(struct stb_arena* a, const char* str);` — allocate a string from an arena
- L25 _prototype_ `STB_ALLOC_DEF char* stb_arena_alloc_string_length(struct stb_arena* a, const char* str, size_t length);`
- L28 _prototype_ `STB_ALLOC_DEF void stb_arena_free(struct stb_arena* a);` — free the entire arena, leaves arena reset so it can be used again

### `Source/Developer/ShaderPreprocessor/Private/stb_preprocess/stb_common.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define STB_COMMON_XSTR(s) STB_COMMON_STR(s)`
- L6 _macro_ `#define STB_COMMON_STR(s) #s`
- L20 _macro_ `#define STB_COMMON_MALLOC(s) malloc(s)`
- L21 _macro_ `#define STB_COMMON_REALLOC(p, s) realloc(p, s)`
- L22 _macro_ `#define STB_COMMON_FREE(p) free(p)`
- L23 _macro_ `#define STB_COMMON_STRDUP(s) strdup(s)`
- L31 _macro_ `#define STB_ASSUME(expr) _Analysis_assume_(expr)`
- L33 _macro_ `#define STB_ASSUME(expr)`
- L44 _macro_ `#define STB_COMMON_ASSERT(expr) assert(expr)`
- L45 _macro_ `#define STB_COMMON_ASSERTF(expr, fmt, ...) assert(expr)`

### `Source/Developer/ShaderPreprocessor/Private/stb_preprocess/stb_ds.h` (Private)


#### struct `(anonymous)`  
``  
_L661-670_

#### struct `stbds_string_block`  
`typedef struct stbds_string_block`  
_L677-681_
- L679 _public member_ `struct stbds_string_block* next;`
- L680 _public member_ `char storage[];`

#### struct `stbds_string_arena`  
`struct stbds_string_arena`  
_L687-693_
- L689 _public member_ `stbds_string_block* storage;`
- L690 _public member_ `size_t remaining;`
- L691 _public member_ `unsigned char block;`
- L692 _public member_ `unsigned char mode;` — this isn't used by the string arena itself

#### enum `(anonymous)`  
``  
_L699-704_

#### Free symbols / members of external scopes

- L369 _macro_ `#define _CRT_SECURE_NO_WARNINGS`
- L379 _macro_ `#define arrlen stbds_arrlen`
- L380 _macro_ `#define arrlennonull stbds_arrlennonull`
- L381 _macro_ `#define arrlenu stbds_arrlenu`
- L382 _macro_ `#define arrput stbds_arrput`
- L383 _macro_ `#define arrpush stbds_arrput`
- L384 _macro_ `#define arrpop stbds_arrpop`
- L385 _macro_ `#define arrfree stbds_arrfree`
- L386 _macro_ `#define arraddn stbds_arraddn // deprecated, use one of the following instead:`
- L387 _macro_ `#define arraddnptr stbds_arraddnptr`
- L388 _macro_ `#define arraddnindex stbds_arraddnindex`
- L389 _macro_ `#define arrsetlen stbds_arrsetlen`
- L390 _macro_ `#define arrsetlennocap stbds_arrsetlennocap`
- L391 _macro_ `#define arrinitlen stbds_arrinitlen`
- L392 _macro_ `#define arrlast stbds_arrlast`
- L393 _macro_ `#define arrins stbds_arrins`
- L394 _macro_ `#define arrinsn stbds_arrinsn`
- L395 _macro_ `#define arrdel stbds_arrdel`
- L396 _macro_ `#define arrdeln stbds_arrdeln`
- L397 _macro_ `#define arrdelswap stbds_arrdelswap`
- L398 _macro_ `#define arrcap stbds_arrcap`
- L399 _macro_ `#define arrcapnonull stbds_arrcapnonull`
- L400 _macro_ `#define arrsetcap stbds_arrsetcap`
- L402 _macro_ `#define hmput stbds_hmput`
- L403 _macro_ `#define hmputs stbds_hmputs`
- L404 _macro_ `#define hmget stbds_hmget`
- L405 _macro_ `#define hmget_ts stbds_hmget_ts`
- L406 _macro_ `#define hmgets stbds_hmgets`
- L407 _macro_ `#define hmgetp stbds_hmgetp`
- L408 _macro_ `#define hmgetp_ts stbds_hmgetp_ts`
- L409 _macro_ `#define hmgetp_null stbds_hmgetp_null`
- L410 _macro_ `#define hmgeti stbds_hmgeti`
- L411 _macro_ `#define hmgeti_ts stbds_hmgeti_ts`
- L412 _macro_ `#define hmdel stbds_hmdel`
- L413 _macro_ `#define hmlen stbds_hmlen`
- L414 _macro_ `#define hmlenu stbds_hmlenu`
- L415 _macro_ `#define hmfree stbds_hmfree`
- L416 _macro_ `#define hmdefault stbds_hmdefault`
- L417 _macro_ `#define hmdefaults stbds_hmdefaults`
- L419 _macro_ `#define shput stbds_shput`
- L420 _macro_ `#define shputi stbds_shputi`
- L421 _macro_ `#define shputs stbds_shputs`
- L422 _macro_ `#define shget stbds_shget`
- L423 _macro_ `#define shgeti stbds_shgeti`
- L424 _macro_ `#define shgets stbds_shgets`
- L425 _macro_ `#define shgetp stbds_shgetp`
- L426 _macro_ `#define shgetp_null stbds_shgetp_null`
- L427 _macro_ `#define shdel stbds_shdel`
- L428 _macro_ `#define shlen stbds_shlen`
- L429 _macro_ `#define shlenu stbds_shlenu`
- L430 _macro_ `#define shfree stbds_shfree`
- L431 _macro_ `#define shdefault stbds_shdefault`
- L432 _macro_ `#define shdefaults stbds_shdefaults`
- L433 _macro_ `#define sh_new_arena stbds_sh_new_arena`
- L434 _macro_ `#define sh_new_strdup stbds_sh_new_strdup`
- L436 _macro_ `#define stralloc stbds_stralloc`
- L437 _macro_ `#define strreset stbds_strreset`
- L441 _macro_ `#define STBDS_NOTUSED(v) (void)(v)`
- L443 _macro_ `#define STBDS_NOTUSED(v) (void)sizeof(v)`
- L452 _prototype_ `extern size_t stbds_hash_bytes(void* p, size_t len, size_t seed);` — these are the hash functions used internally if you want to test them or use them for other purposes
- L453 _prototype_ `extern size_t stbds_hash_string(char* str, size_t seed);`
- L456 _typedef_ `typedef struct stbds_string_arena stbds_string_arena;` — this is a simple string arena allocator, initialize with e.g. 'stbds_string_arena my_arena={0}'.
- L457 _prototype_ `extern char* stbds_stralloc(stbds_string_arena* a, char* str);`
- L458 _prototype_ `extern void stbds_strreset(stbds_string_arena* a);`
- L461 _prototype_ `extern void stbds_unit_tests(void);` — have to #define STBDS_UNIT_TESTS to call this
- L470 _prototype_ `extern ptrdiff_t stbds_arrcheckcount(ptrdiff_t count);` — Returns 'count' unchanged, asserting it is not negative.  Lengths here are pointer differences, so an inverted pair otherwise becomes an enormous allocation request rather than a diagnosable failure.
- L471 _prototype_ `extern void* stbds_arrinlinef(size_t* buf, size_t elemsize, size_t elemcount);`
- L472 _prototype_ `extern void* stbds_arrinline_suballocf(void* a, size_t min_capacity);`
- L473 _prototype_ `extern void* stbds_arrgrowf(void* a, size_t elemsize, size_t addlen, size_t min_cap);`
- L474 _prototype_ `extern void stbds_hmfree_func(void* p, size_t elemsize);`
- L475 _prototype_ `extern void* stbds_hmget_key(void* a, size_t elemsize, void* key, size_t keysize, int mode);`
- L476 _prototype_ `extern void* stbds_hmget_key_ts(void* a, size_t elemsize, void* key, size_t keysize, ptrdiff_t* temp, int mode);`
- L477 _prototype_ `extern void* stbds_hmput_default(void* a, size_t elemsize);`
- L478 _prototype_ `extern void* stbds_hmput_key(void* a, size_t elemsize, void* key, size_t keysize, int mode);`
- L479 _prototype_ `extern void* stbds_hmdel_key(void* a, size_t elemsize, void* key, size_t keysize, size_t keyoffset, int mode);`
- L480 _prototype_ `extern void* stbds_shmode_func(size_t elemsize, int mode);`
- L487 _macro_ `#define STBDS_HAS_TYPEOF`
- L495 _macro_ `#define STBDS_HAS_LITERAL_ARRAY`
- L502 _macro_ `#define STBDS_ADDRESSOF(typevar, value) ((__typeof__(typevar)[1]){value}) // literal array decays to pointer to value`
- L504 _macro_ `#define STBDS_ADDRESSOF(typevar, value) ((typeof(typevar)[1]){value}) // literal array decays to pointer to value`
- L507 _macro_ `#define STBDS_ADDRESSOF(typevar, value) &(value)`
- L510 _macro_ `#define STBDS_OFFSETOF(var, field) ((char*)&(var)->field - (char*)(var))`
- L512 _macro_ `#define stbds_header(t) ((stbds_array_header*)(t)-1)`
- L513 _macro_ `#define stbds_temp(t) stbds_header(t)->temp`
- L514 _macro_ `#define stbds_temp_key(t) (*(char**)stbds_header(t)->hash_table)`
- L517 _macro_ `#define stbds_arrinline(a, a_type, n) \` — Macro to reserve inline stack memory storage for an array
- L528 _macro_ `#define stbds_arrinline_suballoc(a, a_type, min_capacity) \` — Allow a single inline storage buffer to be used for multiple sub-allocations.  Trims current allocation to what's used and returns a new allocation with the remainder if enough capacity exists.
- L532 _macro_ `#define stbds_arrinline_suballoc_char(a, min_capacity) \` — Inline simplified version of above that only works on character type.  Avoids elemsize multiply/divide math and call overhead.
- L557 _macro_ `#define stbds_arrsetcap(a, n) ((!(a) || stbds_arrcheckcount(n) > stbds_header(a)->capacity) ? (stbds_arrgrow(a, 0, n), 0) : 0)`
- L558 _macro_ `#define stbds_arrsetlen(a, n) ((stbds_arrcap(a) < stbds_arrcheckcount(n) ? stbds_arrsetcap((a), (n)), 0 : 0), (a) ? stbds_header(a)->length = (n) : 0)`
- L559 _macro_ `#define stbds_arrsetlennocap(a, n) (stbds_header(a)->length = stbds_arrcheckcount(n))`
- L560 _macro_ `#define stbds_arrinitlen(a, n) ((stbds_arrsetcap((a), (n)), stbds_header(a)->length = (n)))`
- L561 _macro_ `#define stbds_arrcap(a) ((a) ? stbds_header(a)->capacity : 0)`
- L562 _macro_ `#define stbds_arrcapnonull(a) (stbds_header(a)->capacity)`
- L563 _macro_ `#define stbds_arrlen(a) ((a) ? (ptrdiff_t)stbds_header(a)->length : 0)`
- L564 _macro_ `#define stbds_arrlennonull(a) ((ptrdiff_t)stbds_header(a)->length)`
- L565 _macro_ `#define stbds_arrlenu(a) ((a) ? stbds_header(a)->length : 0)`
- L566 _macro_ `#define stbds_arrput(a, v) (stbds_arrmaybegrow(a, 1), (a)[stbds_header(a)->length++] = (v))`
- L567 _macro_ `#define stbds_arrpush stbds_arrput // synonym`
- L568 _macro_ `#define stbds_arrpop(a) (stbds_header(a)->length--, (a)[stbds_header(a)->length])`
- L569 _macro_ `#define stbds_arraddn(a, n) ((void)(stbds_arraddnoff(a, n))) // deprecated, use one of the following instead:`
- L570 _macro_ `#define stbds_arraddnptr(a, n) (stbds_arrmaybegrow(a, n), stbds_header(a)->length += (n), &(a)[stbds_header(a)->length - (n)])`
- L571 _macro_ `#define stbds_arraddnoff(a, n) (stbds_arrmaybegrow(a, n), stbds_header(a)->length += (n), stbds_header(a)->length - (n))`
- L572 _macro_ `#define stbds_arraddnindex(a, n) stbds_arraddnoff(a, n)`
- L573 _macro_ `#define stbds_arrlast(a) ((a)[stbds_header(a)->length - 1])`
- L574 _macro_ `#define stbds_arrfree(a) ((void)((a) && !stbds_header(a)->inlinealloc ? STB_COMMON_FREE(stbds_header(a)) : (void)0), (a) = NULL)`
- L575 _macro_ `#define stbds_arrdel(a, i) stbds_arrdeln(a, i, 1)`
- L576 _macro_ `#define stbds_arrdeln(a, i, n) (memmove(&(a)[i], &(a)[(i) + (n)], sizeof *(a) * (stbds_header(a)->length - (n) - (i))), stbds_header(a)->length -= (n))`
- L577 _macro_ `#define stbds_arrdelswap(a, i) ((a)[i] = stbds_arrlast(a), stbds_header(a)->length -= 1)`
- L578 _macro_ `#define stbds_arrinsn(a, i, n) \`
- L581 _macro_ `#define stbds_arrins(a, i, v) (stbds_arrinsn((a), (i), 1), (a)[i] = (v))`
- L583 _macro_ `#define stbds_arrmaybegrow(a, n) ((!(a) || stbds_header(a)->length + (n) > stbds_header(a)->capacity) ? (stbds_arrgrow(a, n, 0), 0) : 0)`
- L585 _macro_ `#define stbds_arrgrow(a, b, c) ((a) = stbds_arrgrowf_wrapper((a), sizeof *(a), (b), (c)))`
- L587 _macro_ `#define stbds_hmput(t, k, v) \`
- L591 _macro_ `#define stbds_hmputs(t, s) ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), &(s).key, sizeof(s).key, STBDS_HM_BINARY), (t)[stbds_temp((t)-1)] = (s))`
- L593 _macro_ `#define stbds_hmgeti(t, k) \`
- L596 _macro_ `#define stbds_hmgeti_ts(t, k, temp) \`
- L599 _macro_ `#define stbds_hmgetp(t, k) ((void)stbds_hmgeti(t, k), &(t)[stbds_temp((t)-1)])`
- L601 _macro_ `#define stbds_hmgetp_ts(t, k, temp) ((void)stbds_hmgeti_ts(t, k, temp), &(t)[temp])`
- L603 _macro_ `#define stbds_hmdel(t, k) \`
- L607 _macro_ `#define stbds_hmdefault(t, v) ((t) = stbds_hmput_default_wrapper((t), sizeof *(t)), (t)[-1].value = (v))`
- L609 _macro_ `#define stbds_hmdefaults(t, s) ((t) = stbds_hmput_default_wrapper((t), sizeof *(t)), (t)[-1] = (s))`
- L611 _macro_ `#define stbds_hmfree(p) ((void)((p) != NULL ? stbds_hmfree_func((p)-1, sizeof *(p)), 0 : 0), (p) = NULL)`
- L613 _macro_ `#define stbds_hmgets(t, k) (*stbds_hmgetp(t, k))`
- L614 _macro_ `#define stbds_hmget(t, k) (stbds_hmgetp(t, k)->value)`
- L615 _macro_ `#define stbds_hmget_ts(t, k, temp) (stbds_hmgetp_ts(t, k, temp)->value)`
- L616 _macro_ `#define stbds_hmlen(t) ((t) ? (ptrdiff_t)stbds_header((t)-1)->length - 1 : 0)`
- L617 _macro_ `#define stbds_hmlenu(t) ((t) ? stbds_header((t)-1)->length - 1 : 0)`
- L618 _macro_ `#define stbds_hmgetp_null(t, k) (stbds_hmgeti(t, k) == -1 ? NULL : &(t)[stbds_temp((t)-1)])`
- L620 _macro_ `#define stbds_shput(t, k, v) ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), (void*)(k), sizeof(t)->key, STBDS_HM_STRING), (t)[stbds_temp((t)-1)].value = (v))`
- L622 _macro_ `#define stbds_shputi(t, k, v) \`
- L625 _macro_ `#define stbds_shputs(t, s) \`
- L629 _macro_ `#define stbds_pshput(t, p) \`
- L632 _macro_ `#define stbds_shgeti(t, k) ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), (void*)(k), sizeof(t)->key, STBDS_HM_STRING), stbds_temp((t)-1))`
- L634 _macro_ `#define stbds_pshgeti(t, k) ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), (void*)(k), sizeof(*(t))->key, STBDS_HM_PTR_TO_STRING), stbds_temp((t)-1))`
- L636 _macro_ `#define stbds_shgetp(t, k) ((void)stbds_shgeti(t, k), &(t)[stbds_temp((t)-1)])`
- L638 _macro_ `#define stbds_pshget(t, k) ((void)stbds_pshgeti(t, k), (t)[stbds_temp((t)-1)])`
- L640 _macro_ `#define stbds_shdel(t, k) \`
- L642 _macro_ `#define stbds_pshdel(t, k) \`
- L646 _macro_ `#define stbds_sh_new_arena(t) ((t) = stbds_shmode_func_wrapper(t, sizeof *(t), STBDS_SH_ARENA))`
- L647 _macro_ `#define stbds_sh_new_strdup(t) ((t) = stbds_shmode_func_wrapper(t, sizeof *(t), STBDS_SH_STRDUP))`
- L649 _macro_ `#define stbds_shdefault(t, v) stbds_hmdefault(t, v)`
- L650 _macro_ `#define stbds_shdefaults(t, s) stbds_hmdefaults(t, s)`
- L652 _macro_ `#define stbds_shfree stbds_hmfree`
- L653 _macro_ `#define stbds_shlenu stbds_hmlenu`
- L655 _macro_ `#define stbds_shgets(t, k) (*stbds_shgetp(t, k))`
- L656 _macro_ `#define stbds_shget(t, k) (stbds_shgetp(t, k)->value)`
- L657 _macro_ `#define stbds_shgetp_null(t, k) (stbds_shgeti(t, k) == -1 ? NULL : &(t)[stbds_temp((t)-1)])`
- L658 _macro_ `#define stbds_shlen stbds_hmlen`
- L662 _member_ `int elemsize;` (scope `__anon3b3ce6b40108`)
- L663 _member_ `int inlinealloc;` (scope `__anon3b3ce6b40108`) — Allocated inline, don't free!
- L664 _member_ `void* hash_table;` (scope `__anon3b3ce6b40108`)
- L665 _member_ `ptrdiff_t temp;` (scope `__anon3b3ce6b40108`)
- L668 _member_ `ptrdiff_t capacity;` (scope `__anon3b3ce6b40108`) — Signed, so an underflowed length stays negative and trips stbds_arrcheckcount instead of wrapping to a near-SIZE_MAX value on its way to the allocator.
- L669 _member_ `ptrdiff_t length;` (scope `__anon3b3ce6b40108`)
- L670 _typedef_ `} stbds_array_header;`
- L681 _typedef_ `} stbds_string_block;`
- L695 _macro_ `#define STBDS_HM_BINARY 0`
- L696 _macro_ `#define STBDS_HM_STRING 1`
- L700 _enumerator_ `STBDS_SH_NONE` (scope `__anon3b3ce6b40203`)
- L701 _enumerator_ `STBDS_SH_DEFAULT` (scope `__anon3b3ce6b40203`)
- L702 _enumerator_ `STBDS_SH_STRDUP` (scope `__anon3b3ce6b40203`)
- L703 _enumerator_ `STBDS_SH_ARENA` (scope `__anon3b3ce6b40203`)
- L710 _function_ `template <class T> static T* stbds_arrgrowf_wrapper(T* a, size_t elemsize, size_t addlen, size_t min_cap)` — in C we use implicit assignment from these void*-returning functions to T*. in C++ these templates make the same code work
- L715 _function_ `template <class T> static T* stbds_hmget_key_wrapper(T* a, size_t elemsize, void* key, size_t keysize, int mode)`
- L720 _function_ `template <class T> static T* stbds_hmget_key_ts_wrapper(T* a, size_t elemsize, void* key, size_t keysize, ptrdiff_t* temp, int mode)`
- L725 _function_ `template <class T> static T* stbds_hmput_default_wrapper(T* a, size_t elemsize)`
- L730 _function_ `template <class T> static T* stbds_hmput_key_wrapper(T* a, size_t elemsize, void* key, size_t keysize, int mode)`
- L735 _function_ `template <class T> static T* stbds_hmdel_key_wrapper(T* a, size_t elemsize, void* key, size_t keysize, size_t keyoffset, int mode)`
- L740 _function_ `template <class T> static T* stbds_shmode_func_wrapper(T*, size_t elemsize, int mode)`
- L745 _macro_ `#define stbds_arrgrowf_wrapper stbds_arrgrowf`
- L746 _macro_ `#define stbds_hmget_key_wrapper stbds_hmget_key`
- L747 _macro_ `#define stbds_hmget_key_ts_wrapper stbds_hmget_key_ts`
- L748 _macro_ `#define stbds_hmput_default_wrapper stbds_hmput_default`
- L749 _macro_ `#define stbds_hmput_key_wrapper stbds_hmput_key`
- L750 _macro_ `#define stbds_hmdel_key_wrapper stbds_hmdel_key`
- L751 _macro_ `#define stbds_shmode_func_wrapper(t, e, m) stbds_shmode_func(e, m)`

### `Source/Developer/ShaderPreprocessor/Public/ShaderPreprocessor.h` (Public)


#### Free symbols / members of external scopes

- L25 _prototype_ `extern bool PreprocessShader( FShaderPreprocessOutput& Output, const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& MergedEnvironment, const FShaderCompilerDefinitions& AdditionalDefines);` — Preprocess a shader. @param Output - Preprocess output struct. Source, directives and possibly errors will be populated. @param Input - The shader compiler input. @param MergedEnvironment - The result of merging the Environment and SharedEnvironment from the FShaderCompilerInput (it is assumed this overload is called outside of the worker process which merges this in-place, so this merge step must be performed by the caller) @param AdditionalDefines - Additional defines with which to preprocess the shader. @returns true if the shader is preprocessed without error.
- L40 _prototype_ `extern bool PreprocessShader( FShaderPreprocessOutput& Output, const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& MergedEnvironment);` — Preprocess a shader. @param Output - Preprocess output struct. Source, directives and possibly errors will be populated. @param Input - The shader compiler input. @param MergedEnvironment - The result of merging the Environment and SharedEnvironment from the FShaderCompilerInput (it is assumed this overload is called outside of the worker process which merges this in-place, so this merge step must be performed by the caller) @returns true if the shader is preprocessed without error.
