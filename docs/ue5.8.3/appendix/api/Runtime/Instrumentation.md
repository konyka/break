# Runtime / Instrumentation

- module root: `Source/Runtime/Instrumentation`
- headers: 4; symbols: 59
- symbol kinds: enum=1, enumerator=6, function=16, macro=24, namespace=2, prototype=10
- PrivateIncludePathModuleNames: Core

### `Source/Runtime/Instrumentation/Internal/Instrumentation/Defines.h` (Internal)


#### Free symbols / members of external scopes

- L5 _macro_ `#define INSTRUMENTATION_FUNCTION_BASE_ATTRIBUTES __declspec(safebuffers) __attribute__((disable_sanitizer_instrumentation))`
- L10 _macro_ `#define INSTRUMENTATION_ENTRYPOINT_ATTRIBUTES INSTRUMENTATION_FUNCTION_BASE_ATTRIBUTES __attribute__((autortfm(autortfm_mode_internal)))` — autortfm_mode_internal are prevented from being inlined, so we only use that attribute on entry points
- L12 _macro_ `#define INSTRUMENTATION_FUNCTION_ATTRIBUTES INSTRUMENTATION_FUNCTION_BASE_ATTRIBUTES __attribute__((autortfm(autortfm_mode_disable)))` — use autortfm disable once we're inside race detection code to allow inlining
- L14 _macro_ `#define INSTRUMENTATION_FUNCTION_ATTRIBUTES INSTRUMENTATION_FUNCTION_BASE_ATTRIBUTES`
- L15 _macro_ `#define INSTRUMENTATION_ENTRYPOINT_ATTRIBUTES INSTRUMENTATION_FUNCTION_BASE_ATTRIBUTES`
- L19 _macro_ `#define INSTRUMENTATION_HOTPATCH_TOTAL_NOPS 14` — Reserves 12 NOPs before the function and 2 NOPs at function entry so that we can patch atomically
- L20 _macro_ `#define INSTRUMENTATION_HOTPATCH_PREFIX_NOPS 12`
- L22 _macro_ `#define INSTRUMENTATION_FUNCTION_HOTPATCHABLE __attribute__((patchable_function_entry(INSTRUMENTATION_HOTPATCH_TOTAL_NOPS, INSTRUMENTATION_HOTPATCH_PREFIX_NOPS)))`

### `Source/Runtime/Instrumentation/Internal/Instrumentation/EntryPoints.h` (Internal)


#### Free symbols / members of external scopes

- L12 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__AnnotateHappensBefore(const char* f, int l, void* addr);`
- L13 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__AnnotateHappensAfter(const char* f, int l, void* addr);`
- L14 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_FuncEntry(void* ReturnAddress);`
- L15 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_FuncExit();`
- L16 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_Store(uint64 Address, uint32 Size);`
- L17 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_Load(uint64 Address, uint32 Size);`
- L18 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_VPtr_Store(void** Address, void* Value);`
- L19 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_VPtr_Load(void** Address);`
- L20 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_StoreRange(uint64 Address, uint32 Size);`
- L21 _prototype_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES void __Thunk__Instrument_LoadRange(uint64 Address, uint32 Size);`
- L23 _macro_ `#define INSTRUMENT_LOAD_FUNC(Type) \`
- L26 _macro_ `#define INSTRUMENT_STORE_FUNC(Type) \`
- L29 _macro_ `#define INSTRUMENT_EXCHANGE_FUNC(Type) \`
- L32 _macro_ `#define INSTRUMENT_COMPARE_EXCHANGE_FUNC(Type) \`
- L35 _macro_ `#define INSTRUMENT_RMW_FUNC(Func, Type) \`

### `Source/Runtime/Instrumentation/Internal/Instrumentation/PerModuleInline.inl` (Internal)


#### Free symbols / members of external scopes

- L12 _macro_ `#define INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES INSTRUMENTATION_ENTRYPOINT_ATTRIBUTES INSTRUMENTATION_FUNCTION_HOTPATCHABLE`
- L14 _macro_ `#define INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES INSTRUMENTATION_ENTRYPOINT_ATTRIBUTES`
- L21 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void AnnotateHappensBefore(const char* f, int l, void* addr)`
- L26 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void AnnotateHappensAfter(const char* f, int l, void* addr)`
- L31 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_FuncEntry(void* ReturnAddress)`
- L36 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_FuncExit()`
- L41 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_VPtr_Store(void** Address, void* Value)`
- L46 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_VPtr_Load(void** Address)`
- L51 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_Store(uint64 Address, uint32 Size)`
- L56 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_Load(uint64 Address, uint32 Size)`
- L61 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_StoreRange(uint64 Address, uint32 Size)`
- L66 _function_ `INSTRUMENTATION_PERMODULE_FUNCTION_ATTRIBUTES void __Instrument_LoadRange(uint64 Address, uint32 Size)`
- L71 _macro_ `#define INSTRUMENT_LOAD_FUNC_IMPL(Type) \`
- L77 _macro_ `#define INSTRUMENT_STORE_FUNC_IMPL(Type) \`
- L83 _macro_ `#define INSTRUMENT_EXCHANGE_FUNC_IMPL(Type) \`
- L89 _macro_ `#define INSTRUMENT_COMPARE_EXCHANGE_FUNC_IMPL(Type) \`
- L95 _macro_ `#define INSTRUMENT_FETCHADD_FUNC_IMPL(Type) \`
- L101 _macro_ `#define INSTRUMENT_FETCHSUB_FUNC_IMPL(Type) \`
- L107 _macro_ `#define INSTRUMENT_FETCHOR_FUNC_IMPL(Type) \`
- L113 _macro_ `#define INSTRUMENT_FETCHXOR_FUNC_IMPL(Type) \`
- L119 _macro_ `#define INSTRUMENT_FETCHAND_FUNC_IMPL(Type) \`

### `Source/Runtime/Instrumentation/Public/Instrumentation/Types.h` (Public)


#### enum `UE::Instrumentation::FAtomicMemoryOrder`  
`enum FAtomicMemoryOrder : int8`  
_L21-28_
- L22 _public enumerator_ `MEMORY_ORDER_RELAXED`
- L23 _public enumerator_ `MEMORY_ORDER_CONSUME`
- L24 _public enumerator_ `MEMORY_ORDER_ACQUIRE`
- L25 _public enumerator_ `MEMORY_ORDER_RELEASE`
- L26 _public enumerator_ `MEMORY_ORDER_ACQ_REL`
- L27 _public enumerator_ `MEMORY_ORDER_SEQ_CST`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Instrumentation` (scope `UE`)
- L30 _function_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES inline const TCHAR* LexToString(FAtomicMemoryOrder Order)` (scope `UE::Instrumentation`)
- L51 _function_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES inline std::memory_order ToStdMemoryOrder(FAtomicMemoryOrder MemoryOrder)` (scope `UE::Instrumentation`)
- L70 _function_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES inline bool IsAtomicOrderAcquire(FAtomicMemoryOrder Order)` (scope `UE::Instrumentation`)
- L76 _function_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES inline bool IsAtomicOrderRelease(FAtomicMemoryOrder Order)` (scope `UE::Instrumentation`)
- L82 _function_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES inline bool IsAtomicOrderAcquireRelease(FAtomicMemoryOrder Order)` (scope `UE::Instrumentation`)
- L87 _function_ `INSTRUMENTATION_FUNCTION_ATTRIBUTES FORCEINLINE bool IsAtomicOrderRelaxed(FAtomicMemoryOrder Order)` (scope `UE::Instrumentation`)
