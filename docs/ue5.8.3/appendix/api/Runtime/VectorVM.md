# Runtime / VectorVM

- module root: `Source/Runtime/VectorVM`
- headers: 10; symbols: 340
- symbol kinds: class=1, delegate=1, enum=7, enumerator=32, function=46, macro=14, member=166, namespace=16, prototype=22, struct=26, typedef=5, union=3, variable=1
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/VectorVM/Private/Platforms/VectorVMPlatformARM.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define VVM_pshufb(Src, Mask) vqtbl1q_u8(Src, Mask)`
- L11 _function_ `static VM_FORCEINLINE void VVM_floatToHalf(void* output, float const* input)`
- L18 _function_ `VM_FORCEINLINE VectorRegister4i VVMIntRShift(VectorRegister4i v0, VectorRegister4i v1)`
- L24 _function_ `VM_FORCEINLINE VectorRegister4i VVMIntLShift(VectorRegister4i v0, VectorRegister4i v1)`

### `Source/Runtime/VectorVM/Private/Platforms/VectorVMPlatformBase.h` (Private)


#### struct `FVVM_VUI4`  
`struct FVVM_VUI4`  
_L8-16_

#### union `FVVM_VUI4::(anonymous)`  
``  
_L11-15_

#### Free symbols / members of external scopes

- L12 _member_ `VectorRegister4i v;` (scope `FVVM_VUI4::__anon39034a4b010a`)
- L13 _member_ `uint32 u4[4];` (scope `FVVM_VUI4::__anon39034a4b010a`)
- L14 _member_ `int32 i4[4];` (scope `FVVM_VUI4::__anon39034a4b010a`)

### `Source/Runtime/VectorVM/Private/Platforms/VectorVMPlatformGeneric.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define VVM_pshufb(Src, Mask) _mm_shuffle_epi8(Src, Mask)`
- L11 _function_ `static void VVM_floatToHalf(void* output, float const* input)` — Fabian's round-to-nearest-even float to half
- L61 _function_ `VM_FORCEINLINE VectorRegister4i VVMIntRShift(VectorRegister4i v0, VectorRegister4i v1)`
- L76 _function_ `VM_FORCEINLINE VectorRegister4i VVMIntLShift(VectorRegister4i v0, VectorRegister4i v1)`

### `Source/Runtime/VectorVM/Private/VectorVMEditor.h` (Private)


#### enum `EVectorVMOpCategory`  
`#define VVM_OP_CAT_XM(Category, ...) Category, enum class EVectorVMOpCategory : uint8`  
_L18-21_
- L19 _public enumerator_ `VVM_OP_CAT_XM_LIST MAX`

#### enum `VectorVM::Optimizer::(anonymous)`  
``  
_L36-42_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction`  
`struct FVectorVMOptimizeInstruction`  
_L50-102_
- desc: Optimization
- L52 _public member_ `EVectorVMOp OpCode;`
- L53 _public member_ `EVectorVMOpCategory OpCat;`
- L54 _public member_ `uint32 PtrOffsetInOrigBytecode;`
- L55 _public member_ `uint32 PtrOffsetInOptimizedBytecode;`
- L56 _public member_ `int Index;` — initial index.  Instructions are moved around and removed and dependency chains are created based on index, so we need to store this.
- L57 _public member_ `int InsMergedIdx;` — if not -1, then the instruction index that this is merged with.  Instructions with a set InsMergedIdx are not written to the final bytecode
- L58 _public member_ `int OutputMergeIdx[2];` — if not -1 then this instruction writes directly to an output, not a temp register
- L59 _public member_ `uint16 RegPtrOffset;`
- L60 _public member_ `int NumInputRegisters;`
- L61 _public member_ `int NumOutputRegisters;`

#### union `VectorVM::Optimizer::FVectorVMOptimizeInstruction::(anonymous)`  
``  
_L63-101_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L65-68_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L70-75_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L77-79_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L81-83_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L85-89_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L91-93_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L95-97_

#### struct `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::(anonymous)`  
``  
_L99-100_

#### enum `VectorVM::Optimizer::EVectorVMOptimizeError`  
`enum EVectorVMOptimizeError`  
_L104-120_
- L106 _public enumerator_ `VVMOptErr_OutOfMemory = 1 << 0`
- L107 _public enumerator_ `VVMOptErr_Overflow = 1 << 1`
- L108 _public enumerator_ `VVMOptErr_Bytecode = 1 << 2`
- L109 _public enumerator_ `VVMOptErr_RegisterUsage = 1 << 3`
- L110 _public enumerator_ `VVMOptErr_ConstRemap = 1 << 4`
- L111 _public enumerator_ `VVMOptErr_Instructions = 1 << 5`
- L112 _public enumerator_ `VVMOptErr_InputMergeBuffer = 1 << 6`
- L113 _public enumerator_ `VVMOptErr_InstructionReOrder = 1 << 7`
- L114 _public enumerator_ `VVMOptErr_SSARemap = 1 << 8`
- L115 _public enumerator_ `VVMOptErr_OptimizedBytecode = 1 << 9`
- L116 _public enumerator_ `VVMOptErr_ExternalFunction = 1 << 10`
- L117 _public enumerator_ `VVMOptErr_RedundantInstruction = 1 << 11`
- L119 _public enumerator_ `VVMOptErr_Fatal = 1 << 31`

#### struct `VectorVM::Optimizer::FVectorVMOptimizerContext`  
`struct FVectorVMOptimizerContext : public VectorVM::Runtime::FVectorVMRuntimeContext`  
_L125-154_
- inherits: `VectorVM::Runtime::FVectorVMRuntimeContext`
- L127 _public prototype_ `~FVectorVMOptimizerContext();`
- L134 _public member_ `} Init;` — Set this stuff when calling Optimize()
- L141 _public member_ `} Error;`
- L153 _public member_ `} Intermediate;` — these are freed and NULL after optimize() unless SaveIntermediateData is true when calling OptimizeVectorVMScript

#### struct `VectorVM::Optimizer::FVectorVMOptimizerContext::(anonymous)`  
``  
_L130-134_

#### struct `VectorVM::Optimizer::FVectorVMOptimizerContext::(anonymous)`  
``  
_L137-141_

#### struct `VectorVM::Optimizer::FVectorVMOptimizerContext::(anonymous)`  
``  
_L144-153_

#### Free symbols / members of external scopes

- L7 _macro_ `#define VVM_OP_CAT_XM_LIST \`
- L17 _macro_ `#define VVM_OP_CAT_XM(Category, ...) Category,`
- L24 _variable_ `static const EVectorVMOpCategory VVM_OP_CATEGORIES[] = { #define VVM_OP_XM(op, cat, ...) EVectorVMOpCategory::cat, VVM_OP_XM_LIST #undef VVM_OP_XM };`
- L25 _macro_ `#define VVM_OP_XM(op, cat, ...) EVectorVMOpCategory::cat,`
- L32 _namespace_ `namespace VectorVM`
- L32 _namespace_ `namespace Optimizer` (scope `VectorVM`)
- L37 _enumerator_ `VVM_RT_TEMPREG` (scope `VectorVM::Optimizer::__anone316a82b0103`)
- L38 _enumerator_ `VVM_RT_CONST` (scope `VectorVM::Optimizer::__anone316a82b0103`)
- L39 _enumerator_ `VVM_RT_INPUT` (scope `VectorVM::Optimizer::__anone316a82b0103`)
- L40 _enumerator_ `VVM_RT_OUTPUT` (scope `VectorVM::Optimizer::__anone316a82b0103`)
- L41 _enumerator_ `VVM_RT_INVALID` (scope `VectorVM::Optimizer::__anone316a82b0103`)
- L47 _typedef_ `typedef uint32 (VectorVMOptimizerErrorCallback) (FVectorVMOptimizerContext* OptimizeContext, uint32 ErrorFlags);` (scope `VectorVM::Optimizer`) — prototypes for optimizer
- L66 _member_ `uint16 DataSetIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0308`)
- L67 _member_ `uint16 InputIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0308`)
- L68 _member_ `} Input;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L71 _member_ `uint16 DataSetIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0408`)
- L72 _member_ `uint16 DstRegIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0408`)
- L73 _member_ `int MergeIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0408`) — if not -1 then this instruction index is merged with an output or an op, if it's -2 then it's already been taken care of
- L74 _member_ `uint16 SerialIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0408`)
- L75 _member_ `} Output;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L79 _member_ `} Op;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L82 _member_ `uint16 DataSetIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0608`)
- L83 _member_ `} IndexGen;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L86 _member_ `uint16 ExtFnIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0708`)
- L87 _member_ `uint16 NumInputs;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0708`)
- L88 _member_ `uint16 NumOutputs;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0708`)
- L89 _member_ `} ExtFnCall;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L92 _member_ `uint16 DataSetIdx;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0808`)
- L93 _member_ `} RWBuffer;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L96 _member_ `uint16 ID;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a::__anone316a82b0908`)
- L97 _member_ `} Stat;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L100 _member_ `} Other;` (scope `VectorVM::Optimizer::FVectorVMOptimizeInstruction::__anone316a82b020a`)
- L122 _typedef_ `typedef void* (VectorVMReallocFn)(void* Ptr, size_t NumBytes, const char* Filename, int LineNumber);` (scope `VectorVM::Optimizer`)
- L123 _typedef_ `typedef void (VectorVMFreeFn)(void* Ptr, const char* Filename, int LineNumber);` (scope `VectorVM::Optimizer`)
- L131 _member_ `VectorVMReallocFn * ReallocFn = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0b08`)
- L132 _member_ `VectorVMFreeFn * FreeFn = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0b08`)
- L133 _member_ `const char * ScriptName = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0b08`)
- L138 _member_ `uint32 Flags = 0;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0c08`) — zero is good
- L139 _member_ `uint32 Line = 0;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0c08`)
- L140 _member_ `VectorVMOptimizerErrorCallback* CallbackFn = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0c08`) — set this to get a callback whenever there's an error
- L145 _member_ `FVectorVMOptimizeInstruction* Instructions = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)
- L146 _member_ `uint8* RegisterUsageType = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)
- L147 _member_ `uint16* RegisterUsageBuffer = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)
- L148 _member_ `uint16* SSARegisterUsageBuffer = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)
- L149 _member_ `uint16* ParentInstructionIdx = nullptr;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)
- L150 _member_ `uint32 NumInstructions = 0;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)
- L151 _member_ `uint32 NumInstructionsAlloced = 0;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)
- L152 _member_ `uint32 NumRegistersUsed = 0;` (scope `VectorVM::Optimizer::FVectorVMOptimizerContext::__anone316a82b0d08`)

### `Source/Runtime/VectorVM/Private/VectorVMTypes.h` (Private)


#### union `VectorVM::FVecReg`  
`union FVecReg`  
_L12-16_
- L14 _public member_ `VectorRegister4f v;`
- L15 _public member_ `VectorRegister4i i;`

#### struct `VectorVM::Runtime::FVectorVMState`  
`struct FVectorVMState`  
_L23-75_
- L25 _public member_ `uint8* Bytecode;`
- L26 _public member_ `uint32 NumBytecodeBytes;`
- L28 _public member_ `FVecReg* ConstantBuffers;` — the last OptimizeCtx->NumNoAdvanceInputs are no advance inputs that are copied in the table setup
- L29 _public member_ `FVectorVMExtFunctionData* ExtFunctionTable;`
- L30 _public member_ `int32* NumOutputPerDataSet;`
- L32 _public member_ `uint16* ConstRemapTable;`
- L33 _public member_ `uint16* InputRemapTable;`
- L34 _public member_ `uint16* InputDataSetOffsets;`
- L35 _public member_ `uint8* OutputRemapDataSetIdx;`
- L36 _public member_ `uint16* OutputRemapDataType;`
- L37 _public member_ `uint16* OutputRemapDst;`
- L39 _public member_ `uint8* ConstMapCacheIdx;` — these don't get filled out until Exec() is called because they can't be filled out until the state
- L40 _public member_ `uint16* ConstMapCacheSrc;` — of const and input buffers from Niagara is unknown until exec() is called.
- L41 _public member_ `uint8* InputMapCacheIdx;`
- L42 _public member_ `uint16* InputMapCacheSrc;`
- L43 _public member_ `int32 NumInstancesExecCached;`
- L45 _public member_ `uint32 Flags;`
- L47 _public member_ `uint32 NumExtFunctions;`
- L48 _public member_ `uint32 MaxExtFnRegisters;`
- L50 _public member_ `uint32 NumTempRegisters;`
- L51 _public member_ `uint32 NumConstBuffers;`
- L52 _public member_ `uint32 NumInputBuffers;`
- L53 _public member_ `uint32 NumInputDataSets;`
- L54 _public member_ `uint32 NumOutputsRemapped;`
- L55 _public member_ `uint32 NumOutputBuffers;`
- L56 _public member_ `uint32 MaxOutputDataSet;`
- L57 _public member_ `uint32 NumDummyRegsRequired;`
- L60 _public member_ `uint32 BatchOverheadSize;` — batch stuff
- L61 _public member_ `uint32 ChunkLocalDataOutputIdxNumBytes;`
- L62 _public member_ `uint32 ChunkLocalNumOutputNumBytes;`
- L63 _public member_ `uint32 ChunkLocalOutputMaskIdxNumBytes;`
- L65 _public member_ `uint64 OptimizerHashId;`
- L66 _public member_ `uint32 TotalNumBytes;`
- L74 _public member_ `} ExecCtxCache;`

#### struct `VectorVM::Runtime::FVectorVMState::(anonymous)`  
``  
_L69-74_

#### struct `VectorVM::Runtime::FVectorVMRuntimeContext`  
`struct FVectorVMRuntimeContext`  
_L77-105_
- L79 _public member_ `uint8* OutputBytecode = nullptr;`
- L80 _public member_ `uint16* ConstRemap[2] = { nullptr, nullptr };`
- L81 _public member_ `uint16* InputRemapTable = nullptr;`
- L82 _public member_ `uint16* InputDataSetOffsets = nullptr;`
- L83 _public member_ `uint8* OutputRemapDataSetIdx = nullptr;`
- L84 _public member_ `uint16* OutputRemapDataType = nullptr;`
- L85 _public member_ `uint16* OutputRemapDst = nullptr;`
- L87 _public member_ `FVectorVMExtFunctionData* ExtFnTable = nullptr;`
- L89 _public member_ `uint32 NumBytecodeBytes = 0;`
- L90 _public member_ `uint32 MaxOutputDataSet = 0;`
- L91 _public member_ `uint16 NumConstsAlloced = 0;` — upper bound to alloc
- L92 _public member_ `uint32 NumTempRegisters = 0;`
- L93 _public member_ `uint16 NumConstsRemapped = 0;`
- L94 _public member_ `uint16 NumInputsRemapped = 0;`
- L95 _public member_ `uint16 NumNoAdvanceInputs = 0;`
- L96 _public member_ `uint16 NumInputDataSets = 0;`
- L97 _public member_ `uint16 NumOutputsRemapped = 0;`
- L98 _public member_ `uint16 NumOutputInstructions = 0;`
- L99 _public member_ `uint32 NumExtFns = 0;`
- L100 _public member_ `uint32 MaxExtFnRegisters = 0;`
- L101 _public member_ `uint32 NumDummyRegsReq = 0;` — External function "null" registers
- L102 _public member_ `int32 MaxExtFnUsed = 0;`
- L103 _public member_ `uint32 Flags = 0;`
- L104 _public member_ `uint64 HashId = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace VectorVM`
- L20 _namespace_ `namespace VectorVM`
- L20 _namespace_ `namespace Runtime` (scope `VectorVM`)
- L70 _member_ `uint32 NumBytesRequiredPerBatch;` (scope `VectorVM::Runtime::FVectorVMState::__anonf14b9a390108`)
- L71 _member_ `uint32 PerBatchRegisterDataBytesRequired;` (scope `VectorVM::Runtime::FVectorVMState::__anonf14b9a390108`)
- L72 _member_ `uint32 MaxChunksPerBatch;` (scope `VectorVM::Runtime::FVectorVMState::__anonf14b9a390108`)
- L73 _member_ `uint32 MaxInstancesPerChunk;` (scope `VectorVM::Runtime::FVectorVMState::__anonf14b9a390108`)

### `Source/Runtime/VectorVM/Public/VectorVM.h` (Public)


#### enum `EVectorVMBaseTypes`  
`enum class EVectorVMBaseTypes : uint8`  
_L33-39_
- reflection: `UENUM()`
- L35 _public enumerator_ `Float`
- L36 _public enumerator_ `Int`
- L37 _public enumerator_ `Bool`
- L38 _public enumerator_ `Num UMETA(Hidden)`

#### enum `EVectorVMOperandLocation`  
`enum class EVectorVMOperandLocation : uint8`  
_L42-47_
- reflection: `UENUM()`
- L44 _public enumerator_ `Register`
- L45 _public enumerator_ `Constant`
- L46 _public enumerator_ `Num`

#### enum `EVectorVMOp`  
`#define VVM_OP_XM(n, ...) n, enum class EVectorVMOp : uint8`  
_L236-240_
- L238 _public enumerator_ `VVM_OP_XM_LIST NumOpcodes`

#### struct `FDataSetMeta`  
`struct FDataSetMeta`  
_L246-313_
- desc: TODO: All of this stuff can be handled by the VM compiler rather than dirtying the VM code. Some require RWBuffer like support.
- L248 _public typedef_ `using FInputRegisterView = TArrayView<uint8 const* RESTRICT const>;`
- L249 _public typedef_ `using FOutputRegisterView = TArrayView<uint8* RESTRICT const>;`
- L251 _public member_ `FInputRegisterView InputRegisters;`
- L252 _public member_ `FOutputRegisterView OutputRegisters;`
- L254 _public member_ `uint32 InputRegisterTypeOffsets[3];`
- L255 _public member_ `uint32 OutputRegisterTypeOffsets[3];`
- L257 _public member_ `int32 DataSetAccessIndex = INDEX_NONE;` — index for individual elements of this set
- L259 _public member_ `int32 InstanceOffset = INDEX_NONE;` — offset of the first instance processed
- L261 _public member_ `TArray<int32>* RESTRICT IDTable = nullptr;`
- L262 _public member_ `TArray<int32>* RESTRICT FreeIDTable = nullptr;`
- L263 _public member_ `TArray<int32>* RESTRICT SpawnedIDsTable = nullptr;`
- L266 _public member_ `int32* NumFreeIDs = nullptr;` — Number of free IDs in the FreeIDTable
- L269 _public member_ `int32* MaxUsedID = nullptr;` — MaxID used in this execution.
- L271 _public member_ `int32 *NumSpawnedIDs = nullptr;`
- L273 _public member_ `int32 IDAcquireTag = INDEX_NONE;`
- L275 _public prototype_ `FDataSetMeta() = default;`
- L277 _public function_ `inline void Reset()`
- L291 _public function_ `inline void Init(FInputRegisterView InInputRegisters, FOutputRegisterView InOutputRegisters, int32 InInstanceOffset, TArray<int32>* InIDTable, TArray<int32>* InFreeIDTable, int32* InNumFreeIDs, int32 *InNumSpawnedIDs, int32* InMaxUsedID, int32 InIDAcquireTag, TArray<int32>* InSpawnedIDsTable)`
- L309 _private prototype_ `FDataSetMeta(FDataSetMeta&&) = delete;` — Non-copyable and non-movable
- L310 _private prototype_ `FDataSetMeta(const FDataSetMeta&) = delete;`
- L311 _private prototype_ `FDataSetMeta& operator=(FDataSetMeta&&) = delete;`
- L312 _private prototype_ `FDataSetMeta& operator=(const FDataSetMeta&) = delete;`

#### class `FVectorVMExternalFunctionContext`  
`class FVectorVMExternalFunctionContext`  
_L315-356_
- L318 _public member_ `MS_ALIGN(32) uint32** RegisterData GCC_ALIGN(32);`
- L319 _public member_ `uint8* RegInc;`
- L321 _public member_ `int RegReadCount;`
- L322 _public member_ `int NumRegisters;`
- L324 _public member_ `int StartInstance;`
- L325 _public member_ `int NumInstances;`
- L326 _public member_ `int NumLoops;`
- L327 _public member_ `int PerInstanceFnInstanceIdx;`
- L329 _public member_ `void** UserPtrTable;`
- L330 _public member_ `int NumUserPtrs;`
- L332 _public member_ `FRandomStream* RandStream;`
- L333 _public member_ `int32** RandCounters;`
- L334 _public member_ `TArrayView<FDataSetMeta> DataSets;`
- L336 _public function_ `VM_FORCEINLINE int32 GetStartInstance() const`
- L337 _public function_ `VM_FORCEINLINE int32 GetNumInstances() const`
- L338 _public function_ `inline int32* GetRandCounters()`
- L346 _public function_ `inline FRandomStream& GetRandStream()`
- L347 _public function_ `inline void* GetUserPtrTable(int32 UserPtrIdx)`
- L348 _public function_ `template<uint32 InstancesPerOp> inline int32 GetNumLoops() const`
- L350 _public function_ `inline float* GetNextRegister(int32* OutAdvanceOffset)`

#### struct `FVectorVMExtFunctionData`  
`struct FVectorVMExtFunctionData`  
_L360-365_
- L362 _public member_ `const FVMExternalFunction* Function;`
- L363 _public member_ `int32 NumInputs;`
- L364 _public member_ `int32 NumOutputs;`

#### struct `VectorVM::FStatScopeData`  
`struct FStatScopeData`  
_L381-396_
- L383 _public member_ `TStatId StatId;`
- L384 _public member_ `std::atomic<uint64> ExecutionCycleCount = { 0 };`
- L386 _public function_ `FStatScopeData(TStatId InStatId) : StatId(InStatId)`
- L391 _public function_ `FStatScopeData(const FStatScopeData& InObj) : StatId(InObj.StatId)`

#### struct `VectorVM::FUserPtrHandler`  
`template<typename T> struct FUserPtrHandler`  
_L406-427_
- L408 _public member_ `int32 UserPtrIdx;`
- L409 _public member_ `T* Ptr;`
- L410 _public function_ `FUserPtrHandler(FVectorVMExternalFunctionContext& Context)`
- L420 _public function_ `VM_FORCEINLINE T* Get()`
- L421 _public function_ `VM_FORCEINLINE T* operator->()`
- L422 _public function_ `VM_FORCEINLINE operator T*()`
- L424 _public function_ `VM_FORCEINLINE const T* Get() const`
- L425 _public function_ `VM_FORCEINLINE const T* operator->() const`
- L426 _public function_ `VM_FORCEINLINE operator const T* () const`

#### struct `VectorVM::FExternalFuncInputHandler`  
`template<typename T> struct FExternalFuncInputHandler`  
_L431-474_
- desc: A flexible handler that can deal with either constant or register inputs.
- L435 _private member_ `const T* RESTRICT InputPtr = nullptr;` — Either byte offset into constant table or offset into register table deepening on VVM_INPUT_LOCATION_BIT
- L436 _private member_ `const T* RESTRICT StartPtr = nullptr;`
- L437 _private member_ `int32 AdvanceOffset = 0;`
- L440 _public prototype_ `FExternalFuncInputHandler() = default;`
- L442 _public function_ `inline FExternalFuncInputHandler(FVectorVMExternalFunctionContext& Context)`
- L447 _public function_ `void Init(FVectorVMExternalFunctionContext& Context)`
- L455 _public function_ `inline bool IsConstant() const`
- L456 _public function_ `inline bool IsRegister() const`
- L457 _public function_ `inline void Reset()`
- L459 _public function_ `inline const T Get()`
- L460 _public function_ `inline const T* GetDest()`
- L461 _public function_ `inline void Advance(int32 Count=1)`
- L462 _public function_ `inline const T GetAndAdvance()`
- L468 _public function_ `inline const T* GetDestAndAdvance()`

#### struct `VectorVM::FExternalFuncRegisterHandler`  
`template<typename T> struct FExternalFuncRegisterHandler`  
_L477-508_
- L480 _private member_ `T* RESTRICT Register = nullptr;`
- L481 _private member_ `int32 AdvanceOffset = 0;`
- L483 _public function_ `FExternalFuncRegisterHandler(FVectorVMExternalFunctionContext& Context)`
- L491 _public function_ `inline bool IsValid() const`
- L492 _public function_ `inline const T Get()`
- L493 _public function_ `inline T* GetDest()`
- L494 _public function_ `inline void Advance()`
- L495 _public function_ `inline void Advance(int32 Count)`
- L496 _public function_ `inline const T GetAndAdvance()`
- L502 _public function_ `inline T* GetDestAndAdvance()`

#### struct `VectorVM::FExternalFuncConstHandler`  
`template<typename T> struct FExternalFuncConstHandler`  
_L511-527_
- L513 _public member_ `T Constant;`
- L515 _public function_ `FExternalFuncConstHandler(FVectorVMExternalFunctionContext& Context)`
- L524 _public function_ `VM_FORCEINLINE const T& Get()`
- L525 _public function_ `VM_FORCEINLINE const T& GetAndAdvance()`
- L526 _public function_ `VM_FORCEINLINE void Advance()`

#### enum `VectorVM::EVectorVMFlags`  
`enum EVectorVMFlags`  
_L529-536_
- L531 _public enumerator_ `VVMFlag_OptSaveIntermediateState = 1 << 0`
- L532 _public enumerator_ `VVMFlag_OptOmitStats = 1 << 1`
- L533 _public enumerator_ `VVMFlag_LargeScript = 1 << 2` — if true register indices are 16 bit, otherwise they're 8 bit
- L534 _public enumerator_ `VVMFlag_HasRandInstruction = 1 << 3`
- L535 _public enumerator_ `VVMFlag_DataMapCacheSetup = 1 << 4`

#### Free symbols / members of external scopes

- L13 _macro_ `#define VM_FORCEINLINE FORCENOINLINE`
- L15 _macro_ `#define VM_FORCEINLINE FORCEINLINE`
- L20 _namespace_ `namespace VectorVM`
- L20 _namespace_ `namespace Runtime` (scope `VectorVM`)
- L28 _macro_ `#define VECTOR_WIDTH (128)` — TODO: move to a per platform header and have VM scale vectorization according to vector width.
- L29 _macro_ `#define VECTOR_WIDTH_BYTES (16)`
- L30 _macro_ `#define VECTOR_WIDTH_FLOATS (4)`
- L50 _macro_ `#define VVM_OP_XM_LIST \` — OpCode                         Category    #in    #out  dispatch,  merge tbl offset, merge tbl count, int/float flags
- L235 _macro_ `#define VVM_OP_XM(n, ...) n,`
- L358 _delegate_ `DECLARE_DELEGATE_OneParam(FVMExternalFunction, FVectorVMExternalFunctionContext& );`
- L358 _prototype_ `DECLARE_DELEGATE_OneParam(FVMExternalFunction, FVectorVMExternalFunctionContext& );`
- L367 _namespace_ `namespace VectorVM`
- L370 _prototype_ `uint8 GetNumOpCodes();` (scope `VectorVM`) — Get total number of op-codes
- L373 _prototype_ `FString GetOpName(EVectorVMOp Op);` (scope `VectorVM`)
- L374 _prototype_ `FString GetOperandLocationName(EVectorVMOperandLocation Location);` (scope `VectorVM`)
- L377 _prototype_ `uint8 CreateSrcOperandMask(EVectorVMOperandLocation Type0, EVectorVMOperandLocation Type1 = EVectorVMOperandLocation::Register, EVectorVMOperandLocation Type2 = EVectorVMOperandLocation::Register);` (scope `VectorVM`)
- L400 _prototype_ `void Init();` (scope `VectorVM`)
- L402 _macro_ `#define VVM_EXT_FUNC_INPUT_LOC_BIT (unsigned short)(1<<15)`
- L403 _macro_ `#define VVM_EXT_FUNC_INPUT_LOC_MASK (unsigned short)~VVM_EXT_FUNC_INPUT_LOC_BIT`

### `Source/Runtime/VectorVM/Public/VectorVMBridge.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace VectorVM`
- L10 _namespace_ `namespace Optimizer` (scope `VectorVM`)
- L16 _namespace_ `namespace Runtime` (scope `VectorVM`)
- L21 _namespace_ `namespace Bridge` (scope `VectorVM`)
- L25 _prototype_ `void FreezeOptimizerContext(const Optimizer::FVectorVMOptimizerContext& Context, TArray<uint8>& ContextData);` (scope `VectorVM::Bridge`)
- L28 _prototype_ `void ThawRuntimeContext(TConstArrayView<uint8> ContextData, Runtime::FVectorVMRuntimeContext& Context);` (scope `VectorVM::Bridge`)

### `Source/Runtime/VectorVM/Public/VectorVMDataObject.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/VectorVM/Public/VectorVMOptimizer.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace VectorVM`
- L10 _namespace_ `namespace Optimizer` (scope `VectorVM`)
- L14 _prototype_ `FVectorVMOptimizerContext* AllocOptimizerContext();` (scope `VectorVM::Optimizer`)
- L15 _prototype_ `void FreeOptimizerContext(FVectorVMOptimizerContext* Context);` (scope `VectorVM::Optimizer`)
- L17 _prototype_ `uint32 OptimizeVectorVMScript(const uint8* Bytecode, int BytecodeLen, FVectorVMExtFunctionData* ExtFnIOData, int NumExtFns, FVectorVMOptimizerContext* OptContext, uint64 HashId, uint32 Flags);` (scope `VectorVM::Optimizer`) — OutContext must be zeroed except the Init struct
- L18 _prototype_ `void GenerateHumanReadableScript(const FVectorVMOptimizerContext& Context, FString& VMScript);` (scope `VectorVM::Optimizer`)

### `Source/Runtime/VectorVM/Public/VectorVMRuntime.h` (Public)


#### struct `VectorVM::Runtime::FVectorVMExecContext`  
`struct FVectorVMExecContext`  
_L10-28_
- L18 _public member_ `} Internal;`
- L20 _public member_ `FVectorVMState* VVMState;` — created with AllocVectorVMState()
- L21 _public member_ `TArrayView<FDataSetMeta> DataSets;`
- L22 _public member_ `TArrayView<const FVMExternalFunction*> ExtFunctionTable;`
- L23 _public member_ `TArrayView<void*> UserPtrTable;`
- L24 _public member_ `int32 NumInstances;`
- L25 _public member_ `const uint8* const* ConstantTableData;` — constant tables consist of an array of pointers
- L26 _public member_ `const int* ConstantTableNumBytes;` — an array of sizes in bytes
- L27 _public member_ `int32 ConstantTableCount;` — how many constant tables.  These tables must match the ones used with OptimizeVectorVMScript()

#### struct `VectorVM::Runtime::FVectorVMExecContext::(anonymous)`  
``  
_L13-18_

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace VectorVM`
- L6 _namespace_ `namespace Runtime` (scope `VectorVM`)
- L14 _member_ `uint32 NumBytesRequiredPerBatch;` (scope `VectorVM::Runtime::FVectorVMExecContext::__anon1079a0ac0108`)
- L15 _member_ `uint32 PerBatchRegisterDataBytesRequired;` (scope `VectorVM::Runtime::FVectorVMExecContext::__anon1079a0ac0108`)
- L16 _member_ `uint32 MaxChunksPerBatch;` (scope `VectorVM::Runtime::FVectorVMExecContext::__anon1079a0ac0108`)
- L17 _member_ `uint32 MaxInstancesPerChunk;` (scope `VectorVM::Runtime::FVectorVMExecContext::__anon1079a0ac0108`)
- L30 _prototype_ `FVectorVMState* AllocVectorVMState(TConstArrayView<uint8> ContextData);` (scope `VectorVM::Runtime`)
- L31 _prototype_ `void FreeVectorVMState(FVectorVMState* State);` (scope `VectorVM::Runtime`)
- L33 _prototype_ `void ExecVectorVMState(FVectorVMExecContext* ExecCtx);` (scope `VectorVM::Runtime`)
