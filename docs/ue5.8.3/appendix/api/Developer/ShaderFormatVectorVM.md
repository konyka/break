# Developer / ShaderFormatVectorVM

- module root: `Source/Developer/ShaderFormatVectorVM`
- headers: 4; symbols: 62
- symbol kinds: class=1, delegate=1, enum=1, enumerator=4, function=13, macro=5, member=13, namespace=1, prototype=20, struct=3
- PrivateDependencyModuleNames: Core, RenderCore, ShaderCompilerCommon, ShaderPreprocessor, VectorVM
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Developer/ShaderFormatVectorVM/Internal/VectorVMTestCompile.h` (Internal)


#### Free symbols / members of external scopes

- L7 _prototype_ `extern bool TestCompileVectorVMShader(const FShaderCompilerInput& Input, FVectorVMCompilationOutput& VMCompilationOutput, bool bSkipBackendOptimizations);`

### `Source/Developer/ShaderFormatVectorVM/Private/VectorVMBackend.h` (Private)


#### class `FVectorVMLanguageSpec`  
`class FVectorVMLanguageSpec : public ILanguageSpec`  
_L12-32_
- inherits: `ILanguageSpec`
- L17 _public function_ `virtual bool LowerSubToAddNeg() const override`
- L18 _public function_ `virtual bool SupportsFusedMultiplyAdd() const override`
- L19 _public function_ `virtual bool SupportsDeterminantIntrinsic() const override`
- L20 _public function_ `virtual bool SupportsTransposeIntrinsic() const override`
- L21 _public function_ `virtual bool SupportsIntegerModulo() const override`
- L22 _public function_ `virtual bool SupportsMatrixConversions() const override`
- L25 _public function_ `virtual bool AllowsSharingSamplers() const override` — #todo-rco: Enable
- L27 _public function_ `FVectorVMLanguageSpec()`
- L31 _public prototype_ `virtual void SetupLanguageIntrinsics(_mesa_glsl_parse_state* State, exec_list* ir) override;`

#### struct `FVectorVMCodeBackend`  
`struct FVectorVMCodeBackend : public FCodeBackend`  
_L37-57_
- inherits: `FCodeBackend`
- desc: Generates VectorVM compliant code from IR tokens
- L39 _public function_ `FVectorVMCodeBackend(unsigned int InHlslCompileFlags, EHlslCompileTarget InTarget, FVectorVMCompilationOutput& InCompilerOutput) : FCodeBackend(InHlslCompileFlags, InTarget), CompilationOutput(InCompilerOutput)`
- L45 _public prototype_ `virtual bool GenerateMain(EHlslShaderFrequency Frequency, const char* EntryPoint, exec_list* Instructions, _mesa_glsl_parse_state* ParseState);`
- L47 _public prototype_ `virtual char* GenerateCode(struct exec_list* ir, struct _mesa_glsl_parse_state* ParseState, EHlslShaderFrequency Frequency) override;`
- L56 _public member_ `FVectorVMCompilationOutput& CompilationOutput;`

#### enum `ECallScalarizeMode`  
`enum class ECallScalarizeMode : uint8`  
_L63-69_
- L65 _public enumerator_ `SplitCalls` — simple calls for things like Random(), split the call into separate scalar calls
- L66 _public enumerator_ `SplitParams` — External function calls, split all the params up into a new function
- L67 _public enumerator_ `None`
- L68 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L71 _prototype_ `ECallScalarizeMode get_scalarize_mode(ir_function_signature* in_sig);`
- L72 _prototype_ `EVectorVMOp get_special_vm_opcode(ir_function_signature* signature);`
- L74 _prototype_ `void vm_remove_self_ref_assignments(exec_list* instructions, _mesa_glsl_parse_state *state);`
- L75 _prototype_ `void vm_matrices_to_vectors(exec_list* instructions, _mesa_glsl_parse_state *state);`
- L76 _prototype_ `bool do_vec_op_to_scalar(exec_list *instructions, _mesa_glsl_parse_state* parse_state);`
- L77 _prototype_ `bool vm_flatten_branches_to_selects(exec_list *instructions, _mesa_glsl_parse_state *state);`
- L78 _prototype_ `void vm_to_single_op(exec_list *ir, _mesa_glsl_parse_state *state);`
- L79 _prototype_ `void vm_merge_ops(exec_list *ir, _mesa_glsl_parse_state *state);`
- L80 _prototype_ `void vm_scalarize_ops(exec_list* ir, _mesa_glsl_parse_state* state);`
- L81 _prototype_ `bool vm_extract_scalar_ops(exec_list* ir, _mesa_glsl_parse_state* state);`
- L82 _prototype_ `void vm_propagate_non_expressions_visitor(exec_list* ir, _mesa_glsl_parse_state* state);`
- L83 _prototype_ `void vm_gen_bytecode(exec_list *ir, _mesa_glsl_parse_state *state, FVectorVMCompilationOutput& InCompOutput);`
- L86 _prototype_ `void DebugDumpIR(struct exec_list* ir, struct _mesa_glsl_parse_state* State);`
- L90 _macro_ `#define VM_VERBOSE_LOGGING 0` — Enable verbose debug dumps.
- L92 _macro_ `#define vm_debug_dump(ir, state) DebugDumpIR(ir, state)`
- L93 _macro_ `#define vm_debug_print dprintf`
- L95 _macro_ `#define vm_debug_dump(ir, state)`
- L99 _macro_ `#define vm_debug_print(...)`
- L102 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVVMBackend, All, All);`
- L102 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVVMBackend, All, All);`

### `Source/Developer/ShaderFormatVectorVM/Private/ir_vm_helper.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ir_vm_helper`
- L12 _prototype_ `unsigned get_component_from_matrix_array_deref(ir_dereference_array* array_deref);` (scope `ir_vm_helper`)
- L13 _prototype_ `ir_variable* get_rvalue_variable(ir_rvalue* rvalue, unsigned int& search_comp);` (scope `ir_vm_helper`)

### `Source/Developer/ShaderFormatVectorVM/Public/ShaderFormatVectorVM.h` (Public)


#### struct `FCalledVMFunction`  
`struct FCalledVMFunction`  
_L15-21_
- desc: Ordered table of functions actually called by the VM script.
- L17 _public member_ `FString Name;`
- L18 _public member_ `TArray<bool> InputParamLocations;`
- L19 _public member_ `int32 NumOutputs;`
- L20 _public function_ `FCalledVMFunction() :NumOutputs(0)`

#### struct `FVectorVMCompilationOutput`  
`struct FVectorVMCompilationOutput`  
_L24-42_
- desc: Data which is generated from the hlsl by the VectorVMBackend and fed back into the
- L26 _public function_ `FVectorVMCompilationOutput(): MaxTempRegistersUsed(0), NumOps(0)`
- L28 _public member_ `TArray<uint8> ByteCode;`
- L30 _public member_ `int32 MaxTempRegistersUsed;`
- L32 _public member_ `TArray<int32> InternalConstantOffsets;`
- L33 _public member_ `TArray<uint8> InternalConstantData;`
- L34 _public member_ `TArray<EVectorVMBaseTypes> InternalConstantTypes;`
- L36 _public member_ `TArray<FCalledVMFunction> CalledVMFunctionTable;`
- L38 _public member_ `FString AssemblyAsString;`
- L39 _public member_ `uint32 NumOps;`
- L41 _public member_ `FString Errors;`

#### Free symbols / members of external scopes

- L44 _function_ `inline FArchive& operator<<(FArchive& Ar, FCalledVMFunction& Function)`
- L52 _function_ `inline FArchive& operator<<(FArchive& Ar, FVectorVMCompilationOutput& Output)`
