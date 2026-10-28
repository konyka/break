# Developer / VulkanShaderFormat

- module root: `Source/Developer/VulkanShaderFormat`
- headers: 2; symbols: 79
- symbol kinds: class=1, enum=2, enumerator=6, externvar=3, function=34, macro=1, member=21, namespace=1, prototype=7, struct=1, variable=2
- PrivateDependencyModuleNames: Core, RHI, RenderCore, ShaderCompilerCommon, ShaderPreprocessor
- PrivateIncludePathModuleNames: TargetPlatform
- PublicIncludePathModuleNames: VulkanRHI

### `Source/Developer/VulkanShaderFormat/Private/SpirVShaderCompiler.inl` (Private)


#### class `FSpirvShaderCompilerInternalState`  
`class FSpirvShaderCompilerInternalState`  
_L18-140_
- desc: A collection of states and data that is locked in at the top level call and doesn't change throughout the compilation process
- L21 _public function_ `FSpirvShaderCompilerInternalState(const FShaderCompilerInput& InInput, const FShaderParameterParser* InParameterParser) : Input(InInput) , ParameterParser(InParameterParser) , bUseBindlessUniformBuffer(InInput.IsRayTracingShader() && ((EShaderFrequency)InInput.Target.Frequency != SF_RayGen)) , bUseStaticUniformBufferBindings((EShaderFrequency)InInput.Target.Frequency == SF_RayGen) , bIsRayHitGroupShader(InInput.IsRayTracingShader() && ((EShaderFrequency)InInput.Target.Frequency == SF_RayHitGroup)) , bSupportsBindless(InInput.IsBindlessEnabled()) , bDebugDump(InInput.DumpDebugInfoEnabled())`
- L37 _public prototype_ `virtual ~FSpirvShaderCompilerInternalState() = default;`
- L39 _public member_ `const FShaderCompilerInput& Input;`
- L40 _public member_ `const FShaderParameterParser* ParameterParser;`
- L42 _public member_ `const bool bUseBindlessUniformBuffer;`
- L43 _public member_ `const bool bUseStaticUniformBufferBindings;`
- L44 _public member_ `const bool bIsRayHitGroupShader;`
- L46 _public member_ `const bool bSupportsBindless;`
- L47 _public member_ `const bool bDebugDump;`
- L57 _public member_ `EHitGroupShaderType HitGroupShaderType = EHitGroupShaderType::None;`
- L58 _public member_ `FString ClosestHitEntry;`
- L59 _public member_ `FString AnyHitEntry;`
- L60 _public member_ `FString IntersectionEntry;`
- L62 _public member_ `TArray<FString> AllBindlessUBs;`
- L63 _public member_ `TArray<FString> PushConstantUBs;`
- L64 _public member_ `bool bHasShaderRecordGlobals = false;`
- L67 _public function_ `inline EShaderFrequency GetShaderFrequency() const` — Forwarded calls for convenience
- L71 _public function_ `inline const FString& GetEntryPointName() const`
- L95 _public function_ `inline bool IsRayTracingShader() const`
- L99 _public function_ `inline bool UseRootParametersStructure() const`
- L104 _public function_ `inline FString GetDebugName() const`
- L108 _public function_ `inline bool HasMultipleEntryPoints() const`
- L112 _public function_ `inline FString GetSPVExtension() const`
- L128 _public function_ `inline bool ShouldStripReflect() const`
- L134 _public prototype_ `virtual bool IsSM6() const = 0;` — Provided by the platform that is compiling Spirv
- L135 _public prototype_ `virtual bool IsSM5() const = 0;`
- L136 _public prototype_ `virtual bool IsMobileES31() const = 0;`
- L137 _public prototype_ `virtual CrossCompiler::FShaderConductorOptions::ETargetEnvironment GetMinimumTargetEnvironment() const = 0;`
- L138 _public prototype_ `virtual bool IsAndroid() const = 0;`
- L139 _public prototype_ `virtual bool SupportsOfflineCompiler() const = 0;`

#### enum `FSpirvShaderCompilerInternalState::EHitGroupShaderType`  
`enum class EHitGroupShaderType`  
_L50-56_
- desc: Ray tracing specific states
- L52 _public enumerator_ `None`
- L53 _public enumerator_ `ClosestHit`
- L54 _public enumerator_ `AnyHit`
- L55 _public enumerator_ `Intersection`

#### struct `SpirvShaderCompilerSerializedOutput`  
`struct SpirvShaderCompilerSerializedOutput`  
_L144-161_
- desc: Data structures that will get serialized into ShaderCompilerOutput
- L146 _public function_ `SpirvShaderCompilerSerializedOutput() : Header(FVulkanShaderHeader::EZero)`
- L152 _public member_ `FVulkanShaderHeader Header;` — TODO: Convert descriptors into more generic Spirv information
- L154 _public member_ `FShaderResourceTable ShaderResourceTable;`
- L155 _public member_ `FSpirv Spirv;`
- L156 _public member_ `uint32 SpirvCRC = 0;`
- L157 _public member_ `const ANSICHAR* SpirvEntryPointName = nullptr;`
- L158 _public member_ `FShaderCodePackedResourceCounts PackedResourceCounts;`
- L160 _public member_ `TSet<FString> UsedBindlessUB;`

#### enum `SpirvShaderCompiler::EBindlessUniformBufferType`  
`enum class EBindlessUniformBufferType`  
_L1555-1559_
- L1557 _public enumerator_ `ShaderRecord`
- L1558 _public enumerator_ `PushConstant`

#### Free symbols / members of external scopes

- L166 _namespace_ `namespace SpirvShaderCompiler`
- L169 _variable_ `static const FString kBindlessCBPrefix = TEXT("__B` (scope `SpirvShaderCompiler`)
- L170 _variable_ `static const FString kBindlessHeapSuffix = TEXT("_He` (scope `SpirvShaderCompiler`)
- L171 _function_ `static FString GetBindlessUBNameFromHeap(const FString& HeapName)` (scope `SpirvShaderCompiler`)
- L183 _function_ `static uint32 GetUBLayoutHash(const FShaderCompilerInput& ShaderInput, const FString& UBName)` (scope `SpirvShaderCompiler`)
- L203 _function_ `static FVulkanShaderHeader::EGlobalSamplerType GetGlobalSamplerType(const FString& ResourceName)` (scope `SpirvShaderCompiler`) — Types of Global Samplers (see Common.ush for types) Must match EGlobalSamplerType in VulkanShaderResources.h and declarations in VulkanCommon.ush
- L205 _macro_ `#define VULKAN_GLOBAL_SAMPLER_NAME(FilterWrapName) if (ResourceName.EndsWith(TEXT(#FilterWrapName))) return FVulkanShaderHeader::EGlobalSamplerType::FilterWrapName`
- L221 _function_ `static bool HasDerivatives(const FSpirv& Spirv)` (scope `SpirvShaderCompiler`)
- L250 _function_ `static void FillShaderResourceUsageFlags(const FSpirvShaderCompilerInternalState& InternalState, SpirvShaderCompilerSerializedOutput& SerializedOutput)` (scope `SpirvShaderCompiler`)
- L278 _function_ `static void BuildShaderOutput( SpirvShaderCompilerSerializedOutput& SerializedOutput, FShaderCompilerOutput& ShaderOutput, const FSpirvShaderCompilerInternalState& InternalState, const FSpirvReflectBindings& SpirvReflectBindings, const FString& DebugName, TBitArray<>& UsedUniformBufferSlots )` (scope `SpirvShaderCompiler`)
- L354 _function_ `` (scope `SpirvShaderCompiler::BuildShaderOutput`)
- L524 _function_ `static void GatherSpirvReflectionBindings( spv_reflect::ShaderModule& Reflection, FSpirvReflectBindings& OutBindings, TSet<FString>& OutBindlessUB, const FSpirvShaderCompilerInternalState& InternalState)` (scope `SpirvShaderCompiler`)
- L572 _function_ `` (scope `SpirvShaderCompiler::GatherSpirvReflectionBindings`)
- L632 _function_ `static uint32 CalculateSpirvInstructionCount(FSpirv& Spirv)` (scope `SpirvShaderCompiler`)
- L682 _function_ `static bool BuildShaderOutputFromSpirv( CrossCompiler::FShaderConductorContext& CompilerContext, const FSpirvShaderCompilerInternalState& InternalState, SpirvShaderCompilerSerializedOutput& SerializedOutput, FShaderCompilerOutput& Output )` (scope `SpirvShaderCompiler`)
- L745 _function_ `` (scope `SpirvShaderCompiler::BuildShaderOutputFromSpirv`)
- L1041 _function_ `static void Patch64bitSamplers(FSpirv& Spirv)` (scope `SpirvShaderCompiler`) — Replaces OpImageFetch with OpImageRead for 64bit samplers
- L1167 _function_ `static void SpirvCreateDXCCompileBatchFiles( const CrossCompiler::FShaderConductorContext& CompilerContext, const FSpirvShaderCompilerInternalState& InternalState, const CrossCompiler::FShaderConductorOptions& Options)` (scope `SpirvShaderCompiler`)
- L1224 _function_ `static FString ParseEntrypointDecl(FShaderSource::FViewType PreprocessedShader, FStringView Entrypoint)` (scope `SpirvShaderCompiler`) — Quick and dirty way to get the location of the entrypoint in the source NOTE: Preprocessed shaders have macros resolved and comments removed, it makes this easier...
- L1228 _function_ `` (scope `SpirvShaderCompiler::ParseEntrypointDecl`)
- L1313 _function_ `static uint8 ParseWaveSize( const FSpirvShaderCompilerInternalState& InternalState, FShaderSource::FViewType PreprocessedShader )` (scope `SpirvShaderCompiler`)
- L1365 _function_ `static bool CompileWithShaderConductor( const FSpirvShaderCompilerInternalState& InternalState, FShaderSource::FViewType PreprocessedShader, SpirvShaderCompilerSerializedOutput& SerializedOutput, FShaderCompilerOutput& Output )` (scope `SpirvShaderCompiler`)
- L1454 _function_ `static void ModifyCompilerInput(FSpirvShaderCompilerInternalState& InternalState, FShaderCompilerInput& Input)` (scope `SpirvShaderCompiler`)
- L1535 _function_ `static void UpdateBindlessUBs(const FSpirvShaderCompilerInternalState& InternalState, SpirvShaderCompilerSerializedOutput& SerializedOutput, FShaderCompilerOutput& Output)` (scope `SpirvShaderCompiler`)
- L1562 _function_ `static TArray<FString> ConvertUBToBindless(FString& PreprocessedShaderSource, EBindlessUniformBufferType BindlessUniformBufferType = EBindlessUniformBufferType::ShaderRecord, TArrayView<FString> UBNames = {})` (scope `SpirvShaderCompiler`) — :todo-jn: TEMPORARY EXPERIMENT - will eventually move into preprocessing step
- L1569 _function_ `` (scope `SpirvShaderCompiler::ConvertUBToBindless`)
- L1780 _function_ `static bool CompileShaderGroup( FSpirvShaderCompilerInternalState& InternalState, const FShaderSource::FStringType& OriginalPreprocessedShaderSource, FShaderCompilerOutput& MergedOutput )` (scope `SpirvShaderCompiler`)
- L1793 _function_ `` (scope `SpirvShaderCompiler::CompileShaderGroup`)

### `Source/Developer/VulkanShaderFormat/Private/VulkanBackend.h` (Private)


#### Free symbols / members of external scopes

- L15 _externvar_ `extern const char* VULKAN_SUBPASS_FETCH[9];` — InputAttachments 0 - reserved for depth input, 1-8 for color
- L16 _externvar_ `extern const char* VULKAN_SUBPASS_FETCH_VAR[9];`
- L17 _externvar_ `extern const TCHAR* VULKAN_SUBPASS_FETCH_VAR_W[9];`
