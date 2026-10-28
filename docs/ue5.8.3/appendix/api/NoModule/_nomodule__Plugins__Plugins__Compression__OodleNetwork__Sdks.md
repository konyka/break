# NoModule / _nomodule__Plugins__Plugins__Compression__OodleNetwork__Sdks

- module root: `.`
- headers: 6; symbols: 318
- symbol kinds: macro=144, prototype=99, typedef=75

### `Plugins/Compression/OodleNetwork/Sdks/2.9.14/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2025, Epic Games Tools LLC"`
- L29 _typedef_ `typedef int8_t OO_S8;` — Typedefs
- L30 _typedef_ `typedef uint8_t OO_U8;`
- L31 _typedef_ `typedef int16_t OO_S16;`
- L32 _typedef_ `typedef uint16_t OO_U16;`
- L33 _typedef_ `typedef int32_t OO_S32;`
- L34 _typedef_ `typedef uint32_t OO_U32;`
- L35 _typedef_ `typedef int64_t OO_S64;`
- L36 _typedef_ `typedef uint64_t OO_U64;`
- L37 _typedef_ `typedef float OO_F32;`
- L38 _typedef_ `typedef double OO_F64;`
- L39 _typedef_ `typedef intptr_t OO_SINTa;`
- L40 _typedef_ `typedef uintptr_t OO_UINTa;`
- L41 _typedef_ `typedef int32_t OO_BOOL;`
- L45 _macro_ `#define OOSTRUCT struct __attribute__((__packed__))`
- L46 _macro_ `#define OOINLINEFUNC inline`
- L49 _macro_ `#define OOSTRUCT struct` — on VC++, we use pragmas for the struct packing
- L50 _macro_ `#define OOINLINEFUNC __inline`
- L55 _macro_ `#define OOLINK __stdcall`
- L56 _macro_ `#define OOEXPLINK __stdcall`
- L58 _macro_ `#define OOLINK`
- L59 _macro_ `#define OOEXPLINK`
- L64 _macro_ `#define OODEFFUNC extern "C"`
- L65 _macro_ `#define OODEFSTART extern "C" {`
- L66 _macro_ `#define OODEFEND }`
- L67 _macro_ `#define OODEFAULT( val ) =val`
- L69 _macro_ `#define OODEFFUNC`
- L70 _macro_ `#define OODEFSTART`
- L71 _macro_ `#define OODEFEND`
- L72 _macro_ `#define OODEFAULT( val )`
- L77 _macro_ `#define OOEXPFUNC OODEFFUNC` — Exported function declarations
- L81 _macro_ `#define OO_STRING_JOIN(arg1, arg2) OO_STRING_JOIN_DELAY(arg1, arg2)` — OO_STRING_JOIN joins strings in the preprocessor and works with LINESTRING
- L82 _macro_ `#define OO_STRING_JOIN_DELAY(arg1, arg2) OO_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L83 _macro_ `#define OO_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L91 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__COUNTER__)`
- L93 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__LINE__)`
- L101 _macro_ `#define OO_COMPILER_ASSERT(exp) static_assert(exp, "Assert " #exp)`
- L104 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L106 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L109 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L121 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L123 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L124 _macro_ `#define OOFUNC2 OOEXPLINK`
- L125 _macro_ `#define OOFUNCSTART`
- L126 _macro_ `#define OODLE_CALLBACK OOLINK`
- L134 _macro_ `#define NULL (0)`
- L138 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L140 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L145 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L150 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L153 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L159 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Plugins/Compression/OodleNetwork/Sdks/2.9.14/include/oodle2net.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2_NET_H_INCLUDED__`
- L11 _macro_ `#define OODLE2NET_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2NET_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2NET_VERSION_MINOR 14`
- L34 _macro_ `#define OodleNetworkVersion "2.9.14" /*`
- L39 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleNet_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L52 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_Free)( void * ptr );`
- L59 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetAllocators( t_fp_OodleNet_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleNet_Plugin_Free * fp_OodleFree);`
- L81 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleNet_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L103 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L123 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetJobSystem( t_fp_OodleNet_Plugin_RunJob * fp_RunJob, t_fp_OodleNet_Plugin_WaitJob * fp_WaitJob);`
- L132 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetJobSystemAndCount( t_fp_OodleNet_Plugin_RunJob * fp_RunJob, t_fp_OodleNet_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L171 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L184 _prototype_ `OOFUNC1 t_fp_OodleNet_Plugin_Printf * OOFUNC2 OodleNet_Plugins_SetPrintf(t_fp_OodleNet_Plugin_Printf * fp_rrRawPrintf);`
- L203 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleNet_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L219 _prototype_ `OOFUNC1 t_fp_OodleNet_Plugin_DisplayAssertion * OOFUNC2 OodleNet_Plugins_SetAssertion(t_fp_OodleNet_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L238 _prototype_ `OOFUNC1 void * OOFUNC2 OodleNet_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L239 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Free_Default(void * ptr);`
- L240 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L241 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L242 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNet_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L243 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleNet_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L244 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L250 _macro_ `#define OODLENETWORK1_MAX_DICTIONARY_SIZE (1<<24) /* Maximum size of dictionary for OodleNetwork1`
- L256 _typedef_ `typedef struct OodleNetwork1_Shared OodleNetwork1_Shared;`
- L269 _typedef_ `typedef struct OodleNetwork1TCP_State OodleNetwork1TCP_State;`
- L285 _macro_ `#define OODLENETWORK1_HASH_BITS_DEFAULT (19) /* Good default value for OodleNetwork1 hash table size log2`
- L293 _macro_ `#define OODLENETWORK1_DECOMP_BUF_OVERREAD_LEN (5) /* compressed buffer must be sized to at least compLen+OODLENETWORK1_DECOMP_BUF_OVERREAD_LEN`
- L299 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1_Shared_Size(OO_S32 htbits);`
- L308 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1TCP_State_Size(void);`
- L315 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1_CompressedBufferSizeNeeded(OO_SINTa rawLen);`
- L320 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1_Shared_SetWindow( OodleNetwork1_Shared * data, OO_S32 htbits, const void * window, OO_S32 window_size );`
- L343 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_State_Reset( OodleNetwork1TCP_State * state);`
- L355 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_State_InitAsCopy( OodleNetwork1TCP_State * state, const OodleNetwork1TCP_State * from );`
- L367 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_Train( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void ** training_packet_pointers, const OO_S32 * training_packet_sizes, OO_S32 num_training_packets);`
- L390 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1TCP_Encode( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void * raw, OO_SINTa rawLen, void * comp );`
- L410 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1TCP_Decode( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void * comp, OO_SINTa compLen, void * raw, OO_SINTa rawLen );`
- L444 _typedef_ `typedef struct OodleNetwork1UDP_State OodleNetwork1UDP_State;`
- L450 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1UDP_Train( OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void ** training_packet_pointers, const OO_S32 * training_packet_sizes, OO_S32 num_training_packets);`
- L475 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Size(void);`
- L482 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_Encode( const OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void * raw, OO_SINTa rawLen, void * comp );`
- L504 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_Decode( const OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void * comp, OO_SINTa compLen, void * raw, OO_SINTa rawLen );`
- L540 _typedef_ `typedef struct OodleNetwork1UDP_StateCompacted OodleNetwork1UDP_StateCompacted;`
- L549 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_StateCompacted_MaxSize(void);`
- L556 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Compact_ForVersion( OodleNetwork1UDP_StateCompacted * to, const OodleNetwork1UDP_State * from, OO_S32 for_oodle_major_version);`
- L565 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Compact( OodleNetwork1UDP_StateCompacted * to, const OodleNetwork1UDP_State * from );`
- L580 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_State_Uncompact_ForVersion( OodleNetwork1UDP_State * to, const OodleNetwork1UDP_StateCompacted * from, OO_S32 for_oodle_major_version);`
- L589 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_State_Uncompact( OodleNetwork1UDP_State * to, const OodleNetwork1UDP_StateCompacted * from );`
- L606 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionarySupported(void);`
- L613 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionaryFromPackets( void * dictionary_to_fill, OO_S32 dictionary_size, OO_S32 htbits, const void ** dictionary_packet_pointers, const OO_S32 * dictionary_packet_sizes, OO_S32 num_dictionary_packets, const void ** test_packet_pointers, const OO_S32 * test_packet_sizes, OO_S32 num_test_packets );`
- L662 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionaryFromPackets_Trials( void * dictionary_to_fill, OO_S32 dictionary_size, OO_S32 htbits, const void ** dictionary_packet_pointers, const OO_S32 * dictionary_packet_sizes, OO_S32 num_dictionary_packets, const void ** test_packet_pointers, const OO_S32 * test_packet_sizes, OO_S32 num_test_packets, OO_S32 num_trials, double randomness_percent, OO_S32 num_generations );`

### `Plugins/Compression/OodleNetwork/Sdks/2.9.15/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2026, Epic Games Tools LLC"`
- L29 _typedef_ `typedef int8_t OO_S8;` — Typedefs
- L30 _typedef_ `typedef uint8_t OO_U8;`
- L31 _typedef_ `typedef int16_t OO_S16;`
- L32 _typedef_ `typedef uint16_t OO_U16;`
- L33 _typedef_ `typedef int32_t OO_S32;`
- L34 _typedef_ `typedef uint32_t OO_U32;`
- L35 _typedef_ `typedef int64_t OO_S64;`
- L36 _typedef_ `typedef uint64_t OO_U64;`
- L37 _typedef_ `typedef float OO_F32;`
- L38 _typedef_ `typedef double OO_F64;`
- L39 _typedef_ `typedef intptr_t OO_SINTa;`
- L40 _typedef_ `typedef uintptr_t OO_UINTa;`
- L41 _typedef_ `typedef int32_t OO_BOOL;`
- L45 _macro_ `#define OOSTRUCT struct __attribute__((__packed__))`
- L46 _macro_ `#define OOINLINEFUNC inline`
- L49 _macro_ `#define OOSTRUCT struct` — on VC++, we use pragmas for the struct packing
- L50 _macro_ `#define OOINLINEFUNC __inline`
- L55 _macro_ `#define OOLINK __stdcall`
- L56 _macro_ `#define OOEXPLINK __stdcall`
- L58 _macro_ `#define OOLINK`
- L59 _macro_ `#define OOEXPLINK`
- L64 _macro_ `#define OODEFFUNC extern "C"`
- L65 _macro_ `#define OODEFSTART extern "C" {`
- L66 _macro_ `#define OODEFEND }`
- L67 _macro_ `#define OODEFAULT( val ) =val`
- L69 _macro_ `#define OODEFFUNC`
- L70 _macro_ `#define OODEFSTART`
- L71 _macro_ `#define OODEFEND`
- L72 _macro_ `#define OODEFAULT( val )`
- L77 _macro_ `#define OOEXPFUNC OODEFFUNC` — Exported function declarations
- L81 _macro_ `#define OO_STRING_JOIN(arg1, arg2) OO_STRING_JOIN_DELAY(arg1, arg2)` — OO_STRING_JOIN joins strings in the preprocessor and works with LINESTRING
- L82 _macro_ `#define OO_STRING_JOIN_DELAY(arg1, arg2) OO_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L83 _macro_ `#define OO_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L91 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__COUNTER__)`
- L93 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__LINE__)`
- L101 _macro_ `#define OO_COMPILER_ASSERT(exp) static_assert(exp, "Assert " #exp)`
- L104 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L106 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L109 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L121 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L123 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L124 _macro_ `#define OOFUNC2 OOEXPLINK`
- L125 _macro_ `#define OOFUNCSTART`
- L126 _macro_ `#define OODLE_CALLBACK OOLINK`
- L134 _macro_ `#define NULL (0)`
- L138 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L140 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L145 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L150 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L153 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L159 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Plugins/Compression/OodleNetwork/Sdks/2.9.15/include/oodle2net.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2_NET_H_INCLUDED__`
- L11 _macro_ `#define OODLE2NET_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2NET_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2NET_VERSION_MINOR 15`
- L34 _macro_ `#define OodleNetworkVersion "2.9.15" /*`
- L39 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleNet_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L52 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_Free)( void * ptr );`
- L59 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetAllocators( t_fp_OodleNet_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleNet_Plugin_Free * fp_OodleFree);`
- L81 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleNet_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L103 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L123 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetJobSystem( t_fp_OodleNet_Plugin_RunJob * fp_RunJob, t_fp_OodleNet_Plugin_WaitJob * fp_WaitJob);`
- L132 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetJobSystemAndCount( t_fp_OodleNet_Plugin_RunJob * fp_RunJob, t_fp_OodleNet_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L171 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L184 _prototype_ `OOFUNC1 t_fp_OodleNet_Plugin_Printf * OOFUNC2 OodleNet_Plugins_SetPrintf(t_fp_OodleNet_Plugin_Printf * fp_rrRawPrintf);`
- L203 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleNet_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L219 _prototype_ `OOFUNC1 t_fp_OodleNet_Plugin_DisplayAssertion * OOFUNC2 OodleNet_Plugins_SetAssertion(t_fp_OodleNet_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L238 _prototype_ `OOFUNC1 void * OOFUNC2 OodleNet_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L239 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Free_Default(void * ptr);`
- L240 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L241 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L242 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNet_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L243 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleNet_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L244 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L250 _macro_ `#define OODLENETWORK1_MAX_DICTIONARY_SIZE (1<<24) /* Maximum size of dictionary for OodleNetwork1`
- L256 _typedef_ `typedef struct OodleNetwork1_Shared OodleNetwork1_Shared;`
- L269 _typedef_ `typedef struct OodleNetwork1TCP_State OodleNetwork1TCP_State;`
- L285 _macro_ `#define OODLENETWORK1_HASH_BITS_DEFAULT (19) /* Good default value for OodleNetwork1 hash table size log2`
- L293 _macro_ `#define OODLENETWORK1_DECOMP_BUF_OVERREAD_LEN (5) /* compressed buffer must be sized to at least compLen+OODLENETWORK1_DECOMP_BUF_OVERREAD_LEN`
- L299 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1_Shared_Size(OO_S32 htbits);`
- L308 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1TCP_State_Size(void);`
- L315 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1_CompressedBufferSizeNeeded(OO_SINTa rawLen);`
- L320 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1_Shared_SetWindow( OodleNetwork1_Shared * data, OO_S32 htbits, const void * window, OO_S32 window_size );`
- L343 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_State_Reset( OodleNetwork1TCP_State * state);`
- L355 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_State_InitAsCopy( OodleNetwork1TCP_State * state, const OodleNetwork1TCP_State * from );`
- L367 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_Train( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void ** training_packet_pointers, const OO_S32 * training_packet_sizes, OO_S32 num_training_packets);`
- L390 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1TCP_Encode( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void * raw, OO_SINTa rawLen, void * comp );`
- L410 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1TCP_Decode( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void * comp, OO_SINTa compLen, void * raw, OO_SINTa rawLen );`
- L444 _typedef_ `typedef struct OodleNetwork1UDP_State OodleNetwork1UDP_State;`
- L450 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1UDP_Train( OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void ** training_packet_pointers, const OO_S32 * training_packet_sizes, OO_S32 num_training_packets);`
- L475 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Size(void);`
- L482 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_Encode( const OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void * raw, OO_SINTa rawLen, void * comp );`
- L504 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_Decode( const OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void * comp, OO_SINTa compLen, void * raw, OO_SINTa rawLen );`
- L540 _typedef_ `typedef struct OodleNetwork1UDP_StateCompacted OodleNetwork1UDP_StateCompacted;`
- L549 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_StateCompacted_MaxSize(void);`
- L556 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Compact_ForVersion( OodleNetwork1UDP_StateCompacted * to, const OodleNetwork1UDP_State * from, OO_S32 for_oodle_major_version);`
- L565 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Compact( OodleNetwork1UDP_StateCompacted * to, const OodleNetwork1UDP_State * from );`
- L580 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_State_Uncompact_ForVersion( OodleNetwork1UDP_State * to, const OodleNetwork1UDP_StateCompacted * from, OO_S32 for_oodle_major_version);`
- L589 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_State_Uncompact( OodleNetwork1UDP_State * to, const OodleNetwork1UDP_StateCompacted * from );`
- L606 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionarySupported(void);`
- L613 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionaryFromPackets( void * dictionary_to_fill, OO_S32 dictionary_size, OO_S32 htbits, const void ** dictionary_packet_pointers, const OO_S32 * dictionary_packet_sizes, OO_S32 num_dictionary_packets, const void ** test_packet_pointers, const OO_S32 * test_packet_sizes, OO_S32 num_test_packets );`
- L662 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionaryFromPackets_Trials( void * dictionary_to_fill, OO_S32 dictionary_size, OO_S32 htbits, const void ** dictionary_packet_pointers, const OO_S32 * dictionary_packet_sizes, OO_S32 num_dictionary_packets, const void ** test_packet_pointers, const OO_S32 * test_packet_sizes, OO_S32 num_test_packets, OO_S32 num_trials, double randomness_percent, OO_S32 num_generations );`

### `Plugins/Compression/OodleNetwork/Sdks/2.9.16/include/oodle2base.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2BASE_H_INCLUDED__`
- L11 _macro_ `#define OODLE2BASE_PUBLIC_HEADER 1`
- L22 _macro_ `#define OODLE_BASE_TYPES_H`
- L26 _macro_ `#define OOCOPYRIGHT "Copyright (C) 1994-2026, Epic Games Tools LLC"`
- L29 _typedef_ `typedef int8_t OO_S8;` — Typedefs
- L30 _typedef_ `typedef uint8_t OO_U8;`
- L31 _typedef_ `typedef int16_t OO_S16;`
- L32 _typedef_ `typedef uint16_t OO_U16;`
- L33 _typedef_ `typedef int32_t OO_S32;`
- L34 _typedef_ `typedef uint32_t OO_U32;`
- L35 _typedef_ `typedef int64_t OO_S64;`
- L36 _typedef_ `typedef uint64_t OO_U64;`
- L37 _typedef_ `typedef float OO_F32;`
- L38 _typedef_ `typedef double OO_F64;`
- L39 _typedef_ `typedef intptr_t OO_SINTa;`
- L40 _typedef_ `typedef uintptr_t OO_UINTa;`
- L41 _typedef_ `typedef int32_t OO_BOOL;`
- L45 _macro_ `#define OOSTRUCT struct __attribute__((__packed__))`
- L46 _macro_ `#define OOINLINEFUNC inline`
- L49 _macro_ `#define OOSTRUCT struct` — on VC++, we use pragmas for the struct packing
- L50 _macro_ `#define OOINLINEFUNC __inline`
- L55 _macro_ `#define OOLINK __stdcall`
- L56 _macro_ `#define OOEXPLINK __stdcall`
- L58 _macro_ `#define OOLINK`
- L59 _macro_ `#define OOEXPLINK`
- L64 _macro_ `#define OODEFFUNC extern "C"`
- L65 _macro_ `#define OODEFSTART extern "C" {`
- L66 _macro_ `#define OODEFEND }`
- L67 _macro_ `#define OODEFAULT( val ) =val`
- L69 _macro_ `#define OODEFFUNC`
- L70 _macro_ `#define OODEFSTART`
- L71 _macro_ `#define OODEFEND`
- L72 _macro_ `#define OODEFAULT( val )`
- L77 _macro_ `#define OOEXPFUNC OODEFFUNC` — Exported function declarations
- L81 _macro_ `#define OO_STRING_JOIN(arg1, arg2) OO_STRING_JOIN_DELAY(arg1, arg2)` — OO_STRING_JOIN joins strings in the preprocessor and works with LINESTRING
- L82 _macro_ `#define OO_STRING_JOIN_DELAY(arg1, arg2) OO_STRING_JOIN_IMMEDIATE(arg1, arg2)`
- L83 _macro_ `#define OO_STRING_JOIN_IMMEDIATE(arg1, arg2) arg1 ## arg2`
- L91 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__COUNTER__)`
- L93 _macro_ `#define OO_NUMBERNAME(name) OO_STRING_JOIN(name,__LINE__)`
- L101 _macro_ `#define OO_COMPILER_ASSERT(exp) static_assert(exp, "Assert " #exp)`
- L104 _macro_ `#define OO_COMPILER_ASSERT_UNUSED __attribute__((unused)) // hides warnings when compiler_asserts are in a local scope`
- L106 _macro_ `#define OO_COMPILER_ASSERT_UNUSED`
- L109 _macro_ `#define OO_COMPILER_ASSERT(exp) typedef char OO_NUMBERNAME(_dummy_array) [ (exp) ? 1 : -1 ] OO_COMPILER_ASSERT_UNUSED`
- L121 _macro_ `#define OODLE2_PUBLIC_CORE_DEFINES 1`
- L123 _macro_ `#define OOFUNC1 OOEXPFUNC`
- L124 _macro_ `#define OOFUNC2 OOEXPLINK`
- L125 _macro_ `#define OOFUNCSTART`
- L126 _macro_ `#define OODLE_CALLBACK OOLINK`
- L134 _macro_ `#define NULL (0)`
- L138 _macro_ `#define OODLE_MALLOC_MINIMUM_ALIGNMENT ((OO_SINTa)(2*sizeof(void *)))` — OODLE_MALLOC_MINIMUM_ALIGNMENT is 8 in 32-bit, 16 in 64-bit
- L140 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoid)(void);`
- L145 _typedef_ `typedef void (OODLE_CALLBACK t_OodleFPVoidVoidStar)(void *);`
- L150 _macro_ `#define OODLE_JOB_MAX_DEPENDENCIES (4) /* Maximum number of dependencies Oodle will ever pass to a RunJob callback`
- L153 _macro_ `#define OODLE_JOB_NULL_HANDLE (0) /* Value 0 of Jobify handles is reserved to mean none`
- L159 _macro_ `#define t_fp_Oodle_Job t_OodleFPVoidVoidStar /* Job function pointer for Plugin Jobify system`

### `Plugins/Compression/OodleNetwork/Sdks/2.9.16/include/oodle2net.h` (Other)


#### Free symbols / members of external scopes

- L8 _macro_ `#define __OODLE2_NET_H_INCLUDED__`
- L11 _macro_ `#define OODLE2NET_PUBLIC_HEADER 1`
- L28 _macro_ `#define OODLE2NET_VERSION_MAJOR 9` — header version : the DLL is incompatible when MAJOR is bumped MINOR is for internal revs and bug fixes that don't affect API compatibility
- L29 _macro_ `#define OODLE2NET_VERSION_MINOR 16`
- L34 _macro_ `#define OodleNetworkVersion "2.9.16" /*`
- L39 _typedef_ `OODEFFUNC typedef void * (OODLE_CALLBACK t_fp_OodleNet_Plugin_MallocAligned)( OO_SINTa bytes, OO_S32 alignment);`
- L52 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_Free)( void * ptr );`
- L59 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetAllocators( t_fp_OodleNet_Plugin_MallocAligned * fp_OodleMallocAligned, t_fp_OodleNet_Plugin_Free * fp_OodleFree);`
- L81 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_OodleNet_Plugin_RunJob)( t_fp_Oodle_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L103 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L123 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetJobSystem( t_fp_OodleNet_Plugin_RunJob * fp_RunJob, t_fp_OodleNet_Plugin_WaitJob * fp_WaitJob);`
- L132 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugins_SetJobSystemAndCount( t_fp_OodleNet_Plugin_RunJob * fp_RunJob, t_fp_OodleNet_Plugin_WaitJob * fp_WaitJob, int target_parallelism);`
- L171 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_OodleNet_Plugin_Printf)(int verboseLevel,const char * file,int line,const char * fmt,...);` — the main func pointer for log :
- L184 _prototype_ `OOFUNC1 t_fp_OodleNet_Plugin_Printf * OOFUNC2 OodleNet_Plugins_SetPrintf(t_fp_OodleNet_Plugin_Printf * fp_rrRawPrintf);`
- L203 _typedef_ `OODEFFUNC typedef OO_BOOL (OODLE_CALLBACK t_fp_OodleNet_Plugin_DisplayAssertion)(const char * file,const int line,const char * function,const char * message);`
- L219 _prototype_ `OOFUNC1 t_fp_OodleNet_Plugin_DisplayAssertion * OOFUNC2 OodleNet_Plugins_SetAssertion(t_fp_OodleNet_Plugin_DisplayAssertion * fp_rrDisplayAssertion);`
- L238 _prototype_ `OOFUNC1 void * OOFUNC2 OodleNet_Plugin_MallocAligned_Default(OO_SINTa size,OO_S32 alignment);`
- L239 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Free_Default(void * ptr);`
- L240 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Printf_Default(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L241 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_Printf_Verbose(int verboseLevel,const char * file,int line,const char * fmt,...);`
- L242 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNet_Plugin_DisplayAssertion_Default(const char * file,const int line,const char * function,const char * message);`
- L243 _prototype_ `OOFUNC1 OO_U64 OOFUNC2 OodleNet_Plugin_RunJob_Default( t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L244 _prototype_ `OOFUNC1 void OOFUNC2 OodleNet_Plugin_WaitJob_Default( OO_U64 job_handle, void * user_ptr );`
- L250 _macro_ `#define OODLENETWORK1_MAX_DICTIONARY_SIZE (1<<24) /* Maximum size of dictionary for OodleNetwork1`
- L256 _typedef_ `typedef struct OodleNetwork1_Shared OodleNetwork1_Shared;`
- L269 _typedef_ `typedef struct OodleNetwork1TCP_State OodleNetwork1TCP_State;`
- L285 _macro_ `#define OODLENETWORK1_HASH_BITS_DEFAULT (19) /* Good default value for OodleNetwork1 hash table size log2`
- L293 _macro_ `#define OODLENETWORK1_DECOMP_BUF_OVERREAD_LEN (5) /* compressed buffer must be sized to at least compLen+OODLENETWORK1_DECOMP_BUF_OVERREAD_LEN`
- L299 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1_Shared_Size(OO_S32 htbits);`
- L308 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1TCP_State_Size(void);`
- L315 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1_CompressedBufferSizeNeeded(OO_SINTa rawLen);`
- L320 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1_Shared_SetWindow( OodleNetwork1_Shared * data, OO_S32 htbits, const void * window, OO_S32 window_size );`
- L343 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_State_Reset( OodleNetwork1TCP_State * state);`
- L355 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_State_InitAsCopy( OodleNetwork1TCP_State * state, const OodleNetwork1TCP_State * from );`
- L367 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1TCP_Train( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void ** training_packet_pointers, const OO_S32 * training_packet_sizes, OO_S32 num_training_packets);`
- L390 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1TCP_Encode( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void * raw, OO_SINTa rawLen, void * comp );`
- L410 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1TCP_Decode( OodleNetwork1TCP_State * state, const OodleNetwork1_Shared * shared, const void * comp, OO_SINTa compLen, void * raw, OO_SINTa rawLen );`
- L444 _typedef_ `typedef struct OodleNetwork1UDP_State OodleNetwork1UDP_State;`
- L450 _prototype_ `OOFUNC1 void OOFUNC2 OodleNetwork1UDP_Train( OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void ** training_packet_pointers, const OO_S32 * training_packet_sizes, OO_S32 num_training_packets);`
- L475 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Size(void);`
- L482 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_Encode( const OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void * raw, OO_SINTa rawLen, void * comp );`
- L504 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_Decode( const OodleNetwork1UDP_State * state, const OodleNetwork1_Shared * shared, const void * comp, OO_SINTa compLen, void * raw, OO_SINTa rawLen );`
- L540 _typedef_ `typedef struct OodleNetwork1UDP_StateCompacted OodleNetwork1UDP_StateCompacted;`
- L549 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_StateCompacted_MaxSize(void);`
- L556 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Compact_ForVersion( OodleNetwork1UDP_StateCompacted * to, const OodleNetwork1UDP_State * from, OO_S32 for_oodle_major_version);`
- L565 _prototype_ `OOFUNC1 OO_SINTa OOFUNC2 OodleNetwork1UDP_State_Compact( OodleNetwork1UDP_StateCompacted * to, const OodleNetwork1UDP_State * from );`
- L580 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_State_Uncompact_ForVersion( OodleNetwork1UDP_State * to, const OodleNetwork1UDP_StateCompacted * from, OO_S32 for_oodle_major_version);`
- L589 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1UDP_State_Uncompact( OodleNetwork1UDP_State * to, const OodleNetwork1UDP_StateCompacted * from );`
- L606 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionarySupported(void);`
- L613 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionaryFromPackets( void * dictionary_to_fill, OO_S32 dictionary_size, OO_S32 htbits, const void ** dictionary_packet_pointers, const OO_S32 * dictionary_packet_sizes, OO_S32 num_dictionary_packets, const void ** test_packet_pointers, const OO_S32 * test_packet_sizes, OO_S32 num_test_packets );`
- L662 _prototype_ `OOFUNC1 OO_BOOL OOFUNC2 OodleNetwork1_SelectDictionaryFromPackets_Trials( void * dictionary_to_fill, OO_S32 dictionary_size, OO_S32 htbits, const void ** dictionary_packet_pointers, const OO_S32 * dictionary_packet_sizes, OO_S32 num_dictionary_packets, const void ** test_packet_pointers, const OO_S32 * test_packet_sizes, OO_S32 num_test_packets, OO_S32 num_trials, double randomness_percent, OO_S32 num_generations );`
