# Plugins / NNERuntimeIREEShader

- module root: `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader`
- headers: 9; symbols: 173
- symbol kinds: class=11, delegate=1, enum=1, enumerator=4, externvar=1, function=37, member=45, namespace=3, prototype=59, struct=9, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Projects, RHI, RenderCore

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Internal/NNERuntimeIREEShader.h` (Internal)


#### class `FNNERuntimeIREEShader`  
`class FNNERuntimeIREEShader : public FShader`  
_L12-23_
- inherits: `FShader`
- L14 _private prototype_ `DECLARE_SHADER_TYPE(FNNERuntimeIREEShader, NNERuntimeIREE);`
- L17 _public prototype_ `FNNERuntimeIREEShader() = default;`
- L18 _public prototype_ `FNNERuntimeIREEShader(const FNNERuntimeIREEShaderType::CompiledShaderInitializerType & Initializer);`

#### struct `FNNERuntimeIREEShader::FParameters`  
`MS_ALIGN(SHADER_PARAMETER_STRUCT_ALIGNMENT) struct FParameters`  
_L20-22_

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Internal/NNERuntimeIREEShaderCompileResult.h` (Internal)


#### struct `FNNERuntimeIREEShaderCompileMessage`  
`struct FNNERuntimeIREEShaderCompileMessage`  
_L10-33_
- desc: Struct containing a message returned by shader compilation.
- L20 _public member_ `EMessageType Type = EMessageType::None;`
- L21 _public member_ `FString Text;`
- L22 _public member_ `FString VirtualFilePath;`
- L23 _public member_ `FString RealFilePath;`
- L24 _public member_ `int32 Line = -1;`
- L25 _public member_ `int32 ColumnStart = -1;`
- L26 _public member_ `int32 ColumnEnd = -1;`
- L29 _public function_ `bool operator==(FNNERuntimeIREEShaderCompileMessage const& Rhs) const` — Equality operator used to deduplicate messages.

#### enum `FNNERuntimeIREEShaderCompileMessage::EMessageType`  
`enum class EMessageType`  
_L12-18_
- L14 _public enumerator_ `None`
- L15 _public enumerator_ `Info`
- L16 _public enumerator_ `Warning`
- L17 _public enumerator_ `Error`

#### struct `FNNERuntimeIREEShaderCompileResults`  
`struct FNNERuntimeIREEShaderCompileResults`  
_L36-39_
- desc: Struct containing all of the messages returned by shader compilation.
- L38 _public member_ `TArray<FNNERuntimeIREEShaderCompileMessage> Messages;`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Internal/NNERuntimeIREEShaderFillBufferCS.h` (Internal)


#### class `UE::NNERuntimeIREEShader::Internal::FFillBufferConstants`  
`class FFillBufferConstants`  
_L14-18_
- L17 _public member_ `static const uint32 THREAD_GROUP_SIZE{ 256 };`

#### class `UE::NNERuntimeIREEShader::Internal::FFillBufferCS`  
`class FFillBufferCS : public FGlobalShader`  
_L20-34_
- inherits: `FGlobalShader`
- L22 _private prototype_ `DECLARE_GLOBAL_SHADER(FFillBufferCS);`
- L27 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_UAV(RWByteAddressBuffer, TargetBuffer) SHADER_PARAMETER(FUintVector4, Fill) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L33 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNERuntimeIREEShader` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNERuntimeIREEShader`)

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Internal/NNERuntimeIREEShaderLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeIREEShader, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeIREEShader, Log, All);`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Internal/NNERuntimeIREEShaderMetadataAllocations.h` (Internal)


#### struct `FNNERuntimeIREEShaderParametersMetadataAllocations`  
`struct FNNERuntimeIREEShaderParametersMetadataAllocations`  
_L12-23_
- L15 _public member_ `TUniquePtr<FShaderParametersMetadata> ShaderParameterMetadatas;` — Allocated metadata. Should include the parent metadata allocation.
- L17 _public member_ `TArray<FString> Names;` — Allocated name dictionary.
- L19 _public prototype_ `FNNERuntimeIREEShaderParametersMetadataAllocations() = default;`
- L20 _public prototype_ `FNNERuntimeIREEShaderParametersMetadataAllocations(FNNERuntimeIREEShaderParametersMetadataAllocations& Other) = delete;`
- L22 _public prototype_ `~FNNERuntimeIREEShaderParametersMetadataAllocations();`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Internal/NNERuntimeIREEShaderShared.h` (Internal)


#### class `FNNERuntimeIREECompilationOutput`  
`class FNNERuntimeIREECompilationOutput`  
_L24-30_
- desc: Stores outputs from the shader compile that need to be saved.
- L28 _public function_ `FNNERuntimeIREECompilationOutput()`

#### class `FNNERuntimeIREEShaderMapId`  
`class FNNERuntimeIREEShaderMapId`  
_L33-99_
- desc: Contains all the information needed to uniquely identify a FNNERuntimeIREEShaderMapID.
- L54 _public function_ `FNNERuntimeIREEShaderMapId() : FeatureLevel(ERHIFeatureLevel::SM5)`
- L58 _public prototype_ `~FNNERuntimeIREEShaderMapId() = default;`
- L61 _public prototype_ `void SetShaderDependencies(const TArray<FShaderType*>& InShaderTypes, EShaderPlatform InShaderPlatform);`
- L71 _public function_ `SIZE_T GetSizeBytes() const`
- L77 _public prototype_ `uint64 GetKernelHash() const;` — Hashes the kernel specific part of this shader map Id.
- L85 _public prototype_ `bool operator==(const FNNERuntimeIREEShaderMapId& InReferenceSet) const;` — Tests this set against another for equality, disregarding override settings. @param InReferenceSet	The set to compare against @return					true if the sets are equal
- L87 _public function_ `bool operator!=(const FNNERuntimeIREEShaderMapId& InReferenceSet) const`
- L94 _public prototype_ `void AppendKeyString(FString& OutKeyString) const;` — Appends string representations of this Id to a key string.
- L98 _public prototype_ `bool ContainsShaderType(const FShaderType* ShaderType) const;` — Returns true if the requested shader type is a dependency of this shader map Id.

#### class `FNNERuntimeIREEShaderMapContent`  
`class FNNERuntimeIREEShaderMapContent : public FShaderMapContent`  
_L101-117_
- inherits: `FShaderMapContent`
- L103 _private typedef_ `using Super = FShaderMapContent;`
- L107 _private function_ `explicit FNNERuntimeIREEShaderMapContent(EShaderPlatform InPlatform) : Super(InPlatform)`

#### class `FNNERuntimeIREEShaderMap`  
`class FNNERuntimeIREEShaderMap : public TShaderMap<FNNERuntimeIREEShaderMapContent, FShaderMapPointerTable>, public FDeferredCleanupInterface`  
_L123-246_
- inherits: `TShaderMap<FNNERuntimeIREEShaderMapContent,FShaderMapPointerTable>,FDeferredCleanupInterface`
- desc: All the shader permutations for a kernel.
- L126 _public typedef_ `using Super = TShaderMap<FNNERuntimeIREEShaderMapContent, FShaderMapPointerTable>;`
- L134 _public prototype_ `static FNNERuntimeIREEShaderMap* FindId(const FNNERuntimeIREEShaderMapId& InShaderMapId, EShaderPlatform InPlatform);` — Finds the shader map for a kernel. @param InShaderMapId - Id to find @param Platform - The platform to lookup for @return nullptr if no cached shader map was found.
- L137 _public function_ `template<typename ShaderType> TShaderRef<ShaderType> GetShader(int32 PermutationId) const` — ShaderMap interface
- L140 _public prototype_ `FNNERuntimeIREEShaderMap();`
- L141 _public prototype_ `~FNNERuntimeIREEShaderMap();`
- L150 _public prototype_ `void Compile( FNNERuntimeIREEResource* InKernel, const FNNERuntimeIREEShaderMapId& InShaderMapId, TRefCountPtr<FSharedShaderCompilerEnvironment> InCompilationEnvironment, const FNNERuntimeIREECompilationOutput& InCompilationOutput, EShaderPlatform InPlatform, bool bSynchronousCompile, bool bApplyCompletedShaderMapForRendering );` — Compiles the shaders for a kernel and caches them in this shader map. @param InKernel - The kernel to compile shaders for. @param InShaderMapId - the set of static parameters to compile for @param InPlatform - The platform to compile to
- L161 _public prototype_ `bool ProcessCompilationResults(const TArray<FShaderCommonCompileJobPtr>& InCompilationResults, int32& InOutResultIndex, float& InOutTimeBudget);` — Sorts the incoming compiled jobs into the appropriate shader maps, and finalizes this shader map so that it can be used for rendering.
- L169 _public prototype_ `bool IsComplete(const FNNERuntimeIREEResource* InKernel, bool bSilent);` — Checks whether the shader map is missing any shader types necessary for the given kernel. @param InKernel - The NNERuntimeIREE shader resource which is checked. @return True if the shader map has all of the shader types necessary.
- L172 _public prototype_ `void GetShaderList(TMap<FShaderId, TShaderRef<FShader>>& OutShaders) const;` — Builds a list of the shaders in a shader map.
- L173 _public prototype_ `virtual void GetShaderList(TMap<FHashedName, TShaderRef<FShader>>& OutShaders) const override;`
- L174 _public prototype_ `virtual void GetShaderPipelineList(TArray<FShaderPipelineRef>& OutShaderPipelines) const override;`
- L177 _public prototype_ `void Register(EShaderPlatform InShaderPlatform);` — Registers a NNERuntimeIREE shader map in the global map so it can be used.
- L180 _public prototype_ `void AddRef();` — Reference counting.
- L181 _public prototype_ `void Release();`
- L184 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes the shader map.
- L187 _public function_ `const FNNERuntimeIREEShaderMapId& GetShaderMapId() const` — Accessors
- L188 _public function_ `EShaderPlatform GetShaderPlatform() const`
- L189 _public function_ `const FMemoryImageString& GetFriendlyName() const`
- L190 _public function_ `bool IsCompilationFinalized() const`
- L191 _public function_ `bool CompiledSuccessfully() const`
- L194 _public function_ `static TMap<TRefCountPtr<FNNERuntimeIREEShaderMap>, TArray<FNNERuntimeIREEResource*> > &GetInFlightShaderMaps()`
- L196 _public function_ `void SetCompiledSuccessfully(bool bSuccess)`
- L199 _public function_ `int32 GetNumRefs() const`
- L200 _public function_ `uint32 GetCompilingId()`
- L204 _private prototype_ `FShader* ProcessCompilationResultsForSingleJob(FShaderCompileJob& InSingleJob, uint64 InShaderMapHash);`
- L207 _private prototype_ `bool IsIREEShaderComplete(const FNNERuntimeIREEResource* InKernel, const FNNERuntimeIREEShaderType* InShaderType, bool bSilent);`
- L214 _private member_ `static TMap<FNNERuntimeIREEShaderMapId, FNNERuntimeIREEShaderMap*> GIdToIREEShaderMap[SP_NumPlatforms];` — A global map from a kernel's ID and static switch set to any shader map cached for that kernel. Note: this does not necessarily contain all kernel shader maps in memory.  Shader maps with the same key can evict each other. No ref counting needed as these are removed on destruction of the shader map.
- L220 _private member_ `static TArray<FNNERuntimeIREEShaderMap*> AllKernelShaderMaps;` — All kernel shader maps in memory. No ref counting needed as these are removed on destruction of the shader map.
- L224 _private member_ `static TMap<TRefCountPtr<FNNERuntimeIREEShaderMap>, TArray<FNNERuntimeIREEResource*> > ShaderMapsBeingCompiled;` — Tracks resources and their shader maps that need to be compiled but whose compilation is being deferred.
- L228 _private member_ `uint32 CompilingId;` — Uniquely identifies this shader map during compilation, needed for deferred compilation where shaders from multiple shader maps are compiled together.
- L230 _private member_ `mutable int32 NumRefs;`
- L233 _private member_ `bool bDeletedThroughDeferredCleanup;` — Used to catch errors where the shader map is deleted directly.
- L236 _private member_ `uint32 bRegistered : 1;` — Indicates whether this shader map has been registered in GIdToIREEShaderMap
- L242 _private member_ `uint32 bCompilationFinalized : 1;` — Indicates whether this shader map has had ProcessCompilationResults called after Compile. The shader map must not be used on the rendering thread unless bCompilationFinalized is true.
- L244 _private member_ `uint32 bCompiledSuccessfully : 1;`

#### class `FNNERuntimeIREEResource`  
`class FNNERuntimeIREEResource`  
_L248-442_
- L251 _public prototype_ `FNNERuntimeIREEResource();`
- L252 _public prototype_ `virtual ~FNNERuntimeIREEResource();`
- L258 _public prototype_ `bool CacheShaders(EShaderPlatform InPlatform, const ITargetPlatform* TargetPlatform, bool bApplyCompletedShaderMapForRendering, bool bSynchronous);` — Caches the shaders for this kernel with no static parameters on the given platform. This is used by UKernel
- L259 _public prototype_ `bool CacheShaders(const FNNERuntimeIREEShaderMapId& InShaderMapId, EShaderPlatform InPlatform, bool bApplyCompletedShaderMapForRendering, bool bSynchronous);`
- L269 _public prototype_ `virtual bool ShouldCache(EShaderPlatform InPlatform, const FShaderType* InShaderType) const;` — Should the shader for this kernel with the given platform and shader type combination be compiled @param InPlatform		The platform currently being compiled for @param InShaderType		Which shader is being compiled @return true if the shader should be compiled
- L271 _public prototype_ `bool SerializeShaderMap(FArchive& Ar);`
- L273 _public prototype_ `void GetDependentShaderTypes(EShaderPlatform InPlatform, TArray<FShaderType*>& OutShaderTypes) const;`
- L274 _public prototype_ `virtual void GetShaderMapId(EShaderPlatform InPlatform, const ITargetPlatform* TargetPlatform, FNNERuntimeIREEShaderMapId& OutId) const;`
- L279 _public prototype_ `virtual void NotifyCompilationFinished(FString const& ResultMessage);` — Called when compilation finishes, after the GameThreadShaderMap is set and the render command to set the RenderThreadShaderMap is queued
- L285 _public prototype_ `void CancelCompilation();` — Cancels all outstanding compilation jobs
- L290 _public prototype_ `void FinishCompilation();` — Blocks until compilation has completed. Returns immediately if a compilation is not outstanding.
- L294 _public function_ `FNNERuntimeIREEShaderCompileResults const& GetCompilationResults() const` — Accessors.
- L295 _public function_ `void SetCompilationResults(FNNERuntimeIREEShaderCompileResults const& InCompilationResults)`
- L297 _public function_ `ERHIFeatureLevel::Type GetFeatureLevel() const`
- L299 _public function_ `FNNERuntimeIREEShaderMap* GetGameThreadShaderMap() const`
- L306 _public function_ `FName GetOwnerFName() const` — Returns owner name for tracking
- L312 _public function_ `void SetGameThreadShaderMap(FNNERuntimeIREEShaderMap* InShaderMap)` — Note: SetRenderingThreadShaderMap must also be called with the same value, but from the rendering thread.
- L323 _public prototype_ `void SetRenderingThreadShaderMap(FNNERuntimeIREEShaderMap* InShaderMap);` — Note: SetGameThreadShaderMap must also be called with the same value, but from the game thread.
- L325 _public function_ `void AddCompileId(uint32 InIdentifier)`
- L330 _public prototype_ `void RemoveOutstandingCompileId(const int32 InOldOutstandingCompileShaderMapId);`
- L332 _public function_ `const FString& GetHLSLSource() const`
- L337 _public function_ `const FString& GetEntryPoint() const`
- L342 _public function_ `const FShaderParametersMetadata* GetShaderParamMetadata() const`
- L347 _public function_ `const FString& GetFriendlyName() const`
- L349 _public function_ `int32 GetNumPermutations() const`
- L351 _public prototype_ `void SetupResource( ERHIFeatureLevel::Type InFeatureLevel, FString const& InFriendlyName, FString const& InShaderEntryPoint, FString const& InShaderHashKey, FString const& InShaderSource, TUniquePtr<FNNERuntimeIREEShaderParametersMetadataAllocations> InShaderParameterMetadataAllocations, FShaderParametersMetadata* InShaderParameterMetadata, FName const& InAssetPath, TConstArrayView<uint32> InBufferBindings );`
- L363 _public prototype_ `TShaderRef<FNNERuntimeIREEShader> GetShader(int32 PermutationId) const;`
- L365 _public prototype_ `bool IsSame(const FNNERuntimeIREEShaderMapId& InId) const;`
- L367 _public prototype_ `uint32 GetBindingIndex(uint32 BufferIdx) const;`
- L374 _protected prototype_ `void GetShaderMapIDsWithUnfinishedCompilation(TArray<int32>& OutShaderMapIds);` — Fills the passed array with IDs of shader maps unfinished compilation jobs.
- L378 _private member_ `FNNERuntimeIREEShaderCompileResults CompilationResults;`
- L386 _private member_ `TRefCountPtr<FNNERuntimeIREEShaderMap> GameThreadShaderMap = nullptr;` — Game thread tracked shader map, which is ref counted and manages shader map lifetime. The shader map uses deferred deletion so that the rendering thread has a chance to process a release command when the shader map is no longer referenced. Code that sets this is responsible for updating RenderingThreadShaderMap in a thread safe way. During an async compile, this will be NULL and will not contain the actual shader map until compilation is complete.
- L392 _private member_ `FNNERuntimeIREEShaderMap* RenderingThreadShaderMap = nullptr;` — Shader map for this FComputeKernelResource which is accessible by the rendering thread. This must be updated along with GameThreadShaderMap, but on the rendering thread.
- L395 _private member_ `FString ShaderEntryPoint;` — Name of shader main function.
- L398 _private member_ `FString ShaderSource;` — Cached shader source for compilation.
- L404 _private member_ `uint64 ShaderCodeHash = 0;` — Hash computed from shader code. If multiple kernels give the same output, same shader resource will be shared
- L406 _private member_ `TUniquePtr<FNNERuntimeIREEShaderParametersMetadataAllocations> ShaderParameterMetadataAllocations;`
- L409 _private member_ `FShaderParametersMetadata const* ShaderParameterMetadata;` — Shader parameter metadata. It is expected that object is owned by ShaderParameterMetadataAllocations.
- L412 _private member_ `TArray<uint32> BufferBindings;` — Binding indices for storage buffers, needed for IREE command buffer dispatches (buffers might alias and two of them map to the same RDG buffer)
- L418 _private prototype_ `bool BeginCompileShaderMap( const FNNERuntimeIREEShaderMapId& InShaderMapId, EShaderPlatform InPlatform, TRefCountPtr<FNNERuntimeIREEShaderMap>& OutShaderMap, bool bApplyCompletedShaderMapForRendering, bool bSynchronous = false);` — Compiles this kernel for InPlatform, storing the result in OutShaderMap if the compile was synchronous
- L426 _private member_ `FString FriendlyName;`
- L429 _private member_ `FName AssetPath;` — Asset using this resource
- L435 _private member_ `TArray<int32, TInlineAllocator<1> > OutstandingCompileShaderMapIds;` — Contains the compiling id of this shader map when it is being compiled asynchronously. This can be used to access the shader map during async compiling, since GameThreadShaderMap will not have been set yet.
- L438 _private member_ `ERHIFeatureLevel::Type FeatureLevel = ERHIFeatureLevel::SM5;` — Feature level that this kernel is representing.
- L440 _private member_ `uint32 bLoadedCookedShaderMapId : 1;`
- L441 _private member_ `FNNERuntimeIREEShaderMapId CookedShaderMapId;`

#### Free symbols / members of external scopes

- L66 _function_ `friend uint32 GetTypeHash(const FNNERuntimeIREEShaderMapId& Ref)`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Internal/NNERuntimeIREEShaderType.h` (Internal)


#### struct `FNNERuntimeIREEShaderPermutationParameters`  
`struct FNNERuntimeIREEShaderPermutationParameters : public FShaderPermutationParameters`  
_L22-28_
- inherits: `FShaderPermutationParameters`
- L24 _public function_ `FNNERuntimeIREEShaderPermutationParameters(EShaderPlatform InPlatform) : FShaderPermutationParameters(InPlatform)`

#### class `FNNERuntimeIREEShaderType`  
`class FNNERuntimeIREEShaderType : public FShaderType`  
_L30-179_
- inherits: `FShaderType`
- L71 _public function_ `FNNERuntimeIREEShaderType( FTypeLayoutDesc& InTypeLayout, const TCHAR* InName, const TCHAR* InSourceFilename, const TCHAR* InFunctionName, uint32 InFrequency,`
- L130 _public prototype_ `void BeginCompileShader( uint32 ShaderMapId, int32 PermutationId, const FNNERuntimeIREEResource* InKernel, FSharedShaderCompilerEnvironment* InCompilationEnvironment, EShaderPlatform Platform, TArray<FShaderCommonCompileJobPtr>& InOutNewJobs, FShaderTarget Target );`
- L143 _public prototype_ `FShader* FinishCompileShader( uint64 InKernelShaderMapHash, const FShaderCompileJob& CurrentJob, const FString& InDebugDescription ) const;` — Either creates a new instance of this type or returns an equivalent existing shader.
- L154 _public function_ `bool ShouldCache(EShaderPlatform InPlatform, const FNNERuntimeIREEResource* Kernel) const` — Checks if the shader type should be cached. @return True if this shader type should be cached.
- L166 _protected function_ `void SetupCompileEnvironment(EShaderPlatform InPlatform, const FNNERuntimeIREEResource* Kernel, FShaderCompilerEnvironment& OutEnvironment) const` — Sets up the environment used to compile an instance of this shader type. @param InPlatform - Platform to compile for. @param OutEnvironment - The shader compile environment that the function modifies.

#### struct `FNNERuntimeIREEShaderType::FParameters`  
`struct FParameters : public FShaderType::FParameters`  
_L33-43_
- inherits: `FShaderType::FParameters`
- L35 _public member_ `const FShaderParametersMetadata& ShaderParamMetadata;`
- L37 _public function_ `FParameters( const FShaderParametersMetadata& InShaderParamMetadata ) : ShaderParamMetadata(InShaderParamMetadata)`

#### struct `FNNERuntimeIREEShaderType::CompiledShaderInitializerType`  
`struct CompiledShaderInitializerType : FGlobalShaderType::CompiledShaderInitializerType`  
_L45-69_
- inherits: `FGlobalShaderType::CompiledShaderInitializerType`
- L47 _public member_ `const FString DebugDescription;`
- L49 _public function_ `CompiledShaderInitializerType( const FShaderType* InType, const FParameters* InParameters, int32 InPermutationId, const FShaderCompilerOutput& CompilerOutput, uint64 InKernelShaderMapHash, const FString& InDebugDescription ) : FGlobalShaderType::CompiledShaderInitializerType( InType, InParameters, InPermutationId, CompilerOutput, InKernelShaderMapHash, nullptr, nullptr ) , DebugDescription(InDebugDescription)`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Private/NNERuntimeIREEShaderCompilationManager.h` (Private)


#### struct `FNNERuntimeIREEShaderMapCompileResults`  
`struct FNNERuntimeIREEShaderMapCompileResults`  
_L11-23_
- desc: Results for a single compiled shader map.
- L13 _public function_ `FNNERuntimeIREEShaderMapCompileResults() : NumJobsQueued(0), bAllJobsSucceeded(true), bRecreateComponentRenderStateOnCompletion(false)`
- L19 _public member_ `int32 NumJobsQueued;`
- L20 _public member_ `bool bAllJobsSucceeded;`
- L21 _public member_ `bool bRecreateComponentRenderStateOnCompletion;`
- L22 _public member_ `TArray<FShaderCommonCompileJobPtr> FinishedJobs;`

#### struct `FNNERuntimeIREEShaderMapFinalizeResults`  
`struct FNNERuntimeIREEShaderMapFinalizeResults : public FNNERuntimeIREEShaderMapCompileResults`  
_L26-35_
- inherits: `FNNERuntimeIREEShaderMapCompileResults`
- desc: Results for a single compiled and finalized shader map.
- L29 _public member_ `int32 FinalizeJobIndex;` — Tracks finalization progress on this shader map.
- L31 _public function_ `FNNERuntimeIREEShaderMapFinalizeResults(const FNNERuntimeIREEShaderMapCompileResults& InCompileResults) : FNNERuntimeIREEShaderMapCompileResults(InCompileResults), FinalizeJobIndex(0)`

#### class `FNNERuntimeIREEShaderCompilationManager`  
`class FNNERuntimeIREEShaderCompilationManager`  
_L40-58_
- desc: Handles finished shader compile jobs, applying of the shaders to their config asset, and some error handling.
- L43 _public prototype_ `void Tick(float DeltaSeconds);`
- L44 _public prototype_ `void AddJobs(TArray<FShaderCommonCompileJobPtr> InNewJobs);`
- L45 _public prototype_ `void FinishCompilation(const TCHAR* InKernelName, const TArray<int32>& ShaderMapIdsToFinishCompiling);`
- L48 _private prototype_ `void ProcessAsyncResults();`
- L49 _private prototype_ `void ProcessCompiledNNERuntimeIREEShaderMaps(TMap<int32, FNNERuntimeIREEShaderMapFinalizeResults>& CompiledShaderMaps, float TimeBudget);`
- L51 _private member_ `TArray<FShaderCommonCompileJobPtr> JobQueue;`
- L54 _private member_ `TMap<int32, FNNERuntimeIREEShaderMapCompileResults> NNERuntimeIREEShaderMapJobs;` — Map from shader map Id to the compile results for that map, used to gather compiled results.
- L57 _private member_ `TMap<int32, FNNERuntimeIREEShaderMapFinalizeResults> PendingFinalizeNNERuntimeIREEShaderMaps;` — Map from shader map id to results being finalized.  Used to track shader finalizations over multiple frames.

#### Free symbols / members of external scopes

- L60 _externvar_ `extern FNNERuntimeIREEShaderCompilationManager GNNERuntimeIREEShaderCompilationManager;`

### `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Private/NNERuntimeIREEShaderModule.h` (Private)


#### class `FNNERuntimeIREEShaderModule`  
`class FNNERuntimeIREEShaderModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`
