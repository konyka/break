# Plugins / ComputeFramework

- module root: `Plugins/Runtime/ComputeFramework/Source/ComputeFramework`
- headers: 29; symbols: 652
- symbol kinds: class=24, delegate=2, enum=9, enumerator=38, externvar=1, function=109, macro=12, member=206, namespace=2, prototype=196, struct=47, typedef=3, union=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Projects, RenderCore, Renderer
- PrivateIncludePathModuleNames: DerivedDataCache
- PublicDependencyModuleNames: RHI

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeFrameworkModule.h` (Private)


#### class `FComputeFrameworkModule`  
`class FComputeFrameworkModule : public IComputeFrameworkModule`  
_L10-22_
- inherits: `IComputeFrameworkModule`
- desc: ComputeFramework module implementation.
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public function_ `static FComputeFrameworkSystem* GetComputeSystem()` — Get the instantiation of the compute system associated with the module.
- L21 _private member_ `static FComputeFrameworkSystem* ComputeSystem;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeGraphRenderProxy.h` (Private)


#### class `FComputeGraphRenderProxy`  
`class FComputeGraphRenderProxy`  
_L17-57_
- desc: Render thread proxy object for a UComputeGraph. Owns a self contained copy of everything that needs to be read from the render thread.
- L50 _public member_ `FName GraphName;` — Friendly name for the owner graph.
- L52 _public member_ `TArray<FKernelInvocation> KernelInvocations;` — Kernel invocation information per kernel.
- L54 _public member_ `TArray<FComputeKernelPermutationVector> ShaderPermutationVectors;` — Shader permutations vector per kernel.
- L56 _public member_ `TUniquePtr<FShaderParametersMetadataAllocations> ShaderParameterMetadataAllocations;` — Container for allocations from the building of all of the kernel FShaderParametersMetadata objects.

#### struct `FComputeGraphRenderProxy::FKernelInvocation`  
`struct FKernelInvocation`  
_L21-47_
- desc: Description for each kernel in the graph.
- L24 _public member_ `FString KernelName;` — Friendly kernel name.
- L26 _public member_ `FIntVector KernelGroupSize = FIntVector(1, 1, 1);` — Group thread size for kernel.
- L28 _public member_ `FComputeKernelResource const* KernelResource = nullptr;` — Kernel resource object. Owned by the UComputeGraph but contains render thread safe accessible shader map.
- L30 _public member_ `FShaderParametersMetadata* ShaderParameterMetadata = nullptr;` — Shader parameter metadata.
- L32 _public member_ `TArray<int32> BoundProviderIndices;` — Array of indices into the full graph data provider array. Contains only the indices to data providers that this kernel references.
- L34 _public member_ `TArray<int32> ReadbackProviderIndices;` — Array of indices for data providers that should trigger a readback.
- L36 _public member_ `TArray<int32> PreSubmitProviderIndices;` — Indices of data providers that require PreSubmit call.
- L38 _public member_ `TArray<int32> PostSubmitProviderIndices;` — Indices of data providers that require PostSubmit call.
- L40 _public member_ `TArray<bool> BoundProviderIsPrimary;` — Same size as BoundProviderIndices, non-primary data providers will be forced to present a full view to its data (unified)
- L42 _public member_ `int32 ExecutionProviderIndex = -1;` — The index of the special execution data provider in the full graph data provider array.
- L44 _public member_ `bool bSupportsUnifiedDispatch = false;` — Whether the kernel can combine multiple supports combined sub-invocations.
- L46 _public member_ `bool bTriggerRenderCapture = false;` — Whether a render capture should be triggered in the scope around this kernel invocation.

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeGraphWorker.h` (Private)


#### class `FComputeGraphTaskWorker`  
`class FComputeGraphTaskWorker : public IComputeTaskWorker`  
_L22-133_
- inherits: `IComputeTaskWorker`
- desc: Class that manages the scheduling of Compute Graph work. Work can be enqueued on the render thread for the execution at the next call to ExecuteBatches().
- L26 _public prototype_ `void Enqueue( FName InExecutionGroupName, FName InOwnerName, uint8 InGraphSortPriority, FComputeGraphRenderProxy const* InGraphRenderProxy, TArray<FComputeDataProviderRenderProxy*> InDataProviderRenderProxies, FSimpleDelegate InFallbackDelegate, bool bInEnableRenderCaptures, #if HAS_GPU_STATS TArray<TPromise<FComputeFrameworkKernelTiming>> InKernelTimingPromises, #endif const UObject* OwnerPointer = nullptr);` — Enqueue a compute graph for execution.
- L39 _public prototype_ `void Abort(const UObject* OwnerPointer);`
- L42 _public prototype_ `bool HasWork(FName InExecutionGroupName) const override;` — Has enqueued compute graph work.
- L45 _public prototype_ `void SubmitWork(FComputeContext& Context) override;` — Submit enqueued compute graph work.
- L49 _private prototype_ `void UpdateReadbacks();` — Poll active readbacks and execute callbacks for ready ones.
- L82 _private member_ `TMap<FName, TArray<FGraphInvocation> > GraphInvocationsPerGroup;` — Map of enqueued work per execution group .
- L115 _private member_ `TArray<FSubmitDescription> SubmitDescs;` — These arrays could be local to FComputeGraphTaskWorker::SubmitWork() but we store them with class and Reset() them at each usage to avoid per frame array allocations.
- L116 _private member_ `TArray<TShaderRef<FComputeKernelShader>> Shaders;`
- L117 _private member_ `TArray<int32> PermutationIds;`
- L118 _private member_ `TArray<FIntVector> ThreadCounts;`
- L119 _private member_ `TArray<FComputeDataProviderRenderProxy::FReadbackData> ReadbackDatas;`
- L132 _private member_ `TArray<FAsyncReadback> ActiveAsyncReadbacks;`

#### struct `FComputeGraphTaskWorker::FGraphInvocation`  
`struct FGraphInvocation`  
_L53-79_
- desc: Description of each graph that is enqueued.
- L56 _public member_ `FName OwnerName;` — Name of owner object that invoked the graph.
- L58 _public member_ `const UObject* OwnerPointer = nullptr;` — Pointer to an owning UObject.
- L60 _public member_ `uint8 GraphSortPriority = 0;` — Priority used when sorting work.
- L62 _public member_ `FComputeGraphRenderProxy const* GraphRenderProxy = nullptr;` — Graph render proxy.
- L64 _public member_ `TArray<FComputeDataProviderRenderProxy*> DataProviderRenderProxies;` — Data provider render proxies.
- L66 _public member_ `FSimpleDelegate FallbackDelegate;` — Render thread fallback logic for invocations that are invalid.
- L68 _public member_ `bool bEnableRenderCaptures = false;` — Whether render captures are enabled.
- L71 _public member_ `mutable TArray<TPromise<FComputeFrameworkKernelTiming>> KernelTimingPromises;` — One TPromise per kernel (parallel to graph kernels). Moved into FComputeFrameworkGPUStat objects during SubmitWork.
- L75 _public prototype_ `void SendNullKernelTimings() const;` — Fulfills any remaining promises with a zero result so consumers don't block, then clears the array. Called on validation failure (!bIsValid path) and explicitly from Abort() before the invocation is removed.
- L78 _public prototype_ `~FGraphInvocation();`

#### struct `FComputeGraphTaskWorker::FSubmitDescription`  
`struct FSubmitDescription`  
_L85-111_
- desc: Description of a single dispatch group to be submitted.
- L106 _public member_ `uint32 ShaderIndex : 15;` — Track the index into our collected shader array.
- L108 _public member_ `uint32 bIsUnified : 1;` — Track if this is Unified Dispatch.
- L110 _public member_ `uint32 bTriggerRenderCapture : 1;` — Whether a render capture should be triggered in the scope around this submit.

#### union `FComputeGraphTaskWorker::FSubmitDescription::(anonymous)`  
``  
_L95-103_

#### struct `FComputeGraphTaskWorker::FSubmitDescription::__anon0ad1bb31010a::(anonymous)`  
``  
_L98-102_

#### struct `FComputeGraphTaskWorker::FAsyncReadback`  
`struct FAsyncReadback`  
_L122-130_
- desc: Data for tracking active asynchronous readbacks.
- L124 _public prototype_ `~FAsyncReadback();`
- L126 _public member_ `class FRHIGPUBufferReadback* Readback = nullptr;`
- L127 _public member_ `uint32 NumBytes = 0;`
- L128 _public member_ `const UObject* OwnerPointer = nullptr;`
- L129 _public member_ `FComputeDataProviderRenderProxy::FReadbackCallback OnDataAvailable;`

#### Free symbols / members of external scopes

- L96 _member_ `uint32 PackedSortKey = 0;` (scope `FComputeGraphTaskWorker::FSubmitDescription::__anon0ad1bb31010a`)
- L99 _member_ `uint32 GraphIndex : 12;` (scope `FComputeGraphTaskWorker::FSubmitDescription::__anon0ad1bb31010a::__anon0ad1bb310208`) — Graph index.
- L100 _member_ `uint32 KernelIndex : 12;` (scope `FComputeGraphTaskWorker::FSubmitDescription::__anon0ad1bb31010a::__anon0ad1bb310208`) — Kernel index within the graph.
- L101 _member_ `uint32 GraphSortPriority : 8;` (scope `FComputeGraphTaskWorker::FSubmitDescription::__anon0ad1bb31010a::__anon0ad1bb310208`) — Externally defined sort priority to maintain inter-graph dependencies.

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeKernelDerivedDataVersion.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define COMPUTEKERNEL_DERIVEDDATA_VER TEXT("F4E7148D-2146-4CFA-B831-B8DB48382101")` — In case of merge conflicts with DDC versions, you MUST generate a new GUID and set this new guid as version

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeKernelShader.h` (Private)


#### class `FComputeKernelShader`  
`class FComputeKernelShader : public FShader`  
_L15-28_
- inherits: `FShader`
- L17 _private prototype_ `DECLARE_SHADER_TYPE(FComputeKernelShader, ComputeKernel);`
- L20 _public prototype_ `FComputeKernelShader() = default;`
- L21 _public prototype_ `FComputeKernelShader( const FComputeKernelShaderType::CompiledShaderInitializerType & Initializer );`

#### struct `FComputeKernelShader::FParameters`  
`MS_ALIGN(SHADER_PARAMETER_STRUCT_ALIGNMENT) struct FParameters`  
_L25-27_

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeKernelShaderCompilationManager.h` (Private)


#### struct `FComputeKernelShaderMapCompileResults`  
`struct FComputeKernelShaderMapCompileResults`  
_L9-21_
- desc: Results for a single compiled shader map.
- L11 _public function_ `FComputeKernelShaderMapCompileResults() : NumJobsQueued(0), bAllJobsSucceeded(true), bRecreateComponentRenderStateOnCompletion(false)`
- L17 _public member_ `int32 NumJobsQueued;`
- L18 _public member_ `bool bAllJobsSucceeded;`
- L19 _public member_ `bool bRecreateComponentRenderStateOnCompletion;`
- L20 _public member_ `TArray<FShaderCommonCompileJobPtr> FinishedJobs;`

#### struct `FComputeKernelShaderMapFinalizeResults`  
`struct FComputeKernelShaderMapFinalizeResults : public FComputeKernelShaderMapCompileResults`  
_L24-33_
- inherits: `FComputeKernelShaderMapCompileResults`
- desc: Results for a single compiled and finalized shader map.
- L27 _public member_ `int32 FinalizeJobIndex;` — Tracks finalization progress on this shader map.
- L29 _public function_ `FComputeKernelShaderMapFinalizeResults(const FComputeKernelShaderMapCompileResults& InCompileResults) : FComputeKernelShaderMapCompileResults(InCompileResults), FinalizeJobIndex(0)`

#### class `FComputeKernelShaderCompilationManager`  
`class FComputeKernelShaderCompilationManager`  
_L38-57_
- desc: Handles finished shader compile jobs, applying of the shaders to their config asset, and some error handling.
- L41 _public prototype_ `void Tick(float DeltaSeconds);`
- L42 _public prototype_ `void AddJobs(TArray<FShaderCommonCompileJobPtr> InNewJobs);`
- L43 _public prototype_ `void FinishCompilation(const TCHAR* InKernelName, const TArray<int32>& ShaderMapIdsToFinishCompiling);`
- L44 _public prototype_ `void CancelCompilation(const TCHAR* InKernelName, const TArray<int32>& ShaderMapIdsToCancelCompiling);`
- L47 _private prototype_ `void ProcessAsyncResults();`
- L48 _private prototype_ `void ProcessCompiledComputeKernelShaderMaps(TMap<int32, FComputeKernelShaderMapFinalizeResults>& CompiledShaderMaps, float TimeBudget);`
- L50 _private member_ `TArray<FShaderCommonCompileJobPtr> JobQueue;`
- L53 _private member_ `TMap<int32, FComputeKernelShaderMapCompileResults> ComputeKernelShaderMapJobs;` — Map from shader map Id to the compile results for that map, used to gather compiled results.
- L56 _private member_ `TMap<int32, FComputeKernelShaderMapFinalizeResults> PendingFinalizeComputeKernelShaderMaps;` — Map from shader map id to results being finalized.  Used to track shader finalizations over multiple frames.

#### Free symbols / members of external scopes

- L59 _externvar_ `extern FComputeKernelShaderCompilationManager GComputeKernelShaderCompilationManager;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeKernelShaderType.h` (Private)


#### struct `FComputeKernelShaderPermutationParameters`  
`struct FComputeKernelShaderPermutationParameters : public FShaderPermutationParameters`  
_L18-24_
- inherits: `FShaderPermutationParameters`
- L20 _public function_ `FComputeKernelShaderPermutationParameters(EShaderPlatform InPlatform) : FShaderPermutationParameters(InPlatform)`

#### class `FComputeKernelShaderType`  
`class FComputeKernelShaderType : public FShaderType`  
_L26-167_
- inherits: `FShaderType`
- L67 _public function_ `FComputeKernelShaderType( FTypeLayoutDesc& InTypeLayout, const TCHAR* InName, const TCHAR* InSourceFilename, const TCHAR* InFunctionName, uint32 InFrequency,`
- L126 _public prototype_ `void BeginCompileShader( uint32 ShaderMapId, int32 PermutationId, const FComputeKernelResource* InKernel, FSharedShaderCompilerEnvironment* InCompilationEnvironment, EShaderPlatform Platform, TArray<FShaderCommonCompileJobPtr>& InOutNewJobs, FShaderTarget Target );`
- L139 _public prototype_ `FShader* FinishCompileShader( uint64 InComputeKernelShaderMapHash, const FShaderCompileJob& CurrentJob, const FString& InDebugDescription ) const;` — Either creates a new instance of this type or returns an equivalent existing shader.
- L150 _public function_ `bool ShouldCache(EShaderPlatform InPlatform, const FComputeKernelResource* Kernel) const` — Checks if the shader type should be cached. @return True if this shader type should be cached.
- L162 _protected function_ `void SetupCompileEnvironment(EShaderPlatform InPlatform, const FComputeKernelResource* Kernel, FShaderCompilerEnvironment& OutEnvironment) const` — Sets up the environment used to compile an instance of this shader type. @param InPlatform - Platform to compile for. @param OutEnvironment - The shader compile environment that the function modifies.

#### struct `FComputeKernelShaderType::FParameters`  
`struct FParameters : public FShaderType::FParameters`  
_L29-39_
- inherits: `FShaderType::FParameters`
- L31 _public member_ `const FShaderParametersMetadata& ShaderParamMetadata;`
- L33 _public function_ `FParameters( const FShaderParametersMetadata& InShaderParamMetadata ) : ShaderParamMetadata(InShaderParamMetadata)`

#### struct `FComputeKernelShaderType::CompiledShaderInitializerType`  
`struct CompiledShaderInitializerType : FGlobalShaderType::CompiledShaderInitializerType`  
_L41-65_
- inherits: `FGlobalShaderType::CompiledShaderInitializerType`
- L43 _public member_ `const FString DebugDescription;`
- L45 _public function_ `CompiledShaderInitializerType( const FShaderType* InType, const FParameters* InParameters, int32 InPermutationId, const FShaderCompilerOutput& CompilerOutput, uint64 InComputeKernelShaderMapHash, const FString& InDebugDescription ) : FGlobalShaderType::CompiledShaderInitializerType( InType, InParameters, InPermutationId, CompilerOutput, InComputeKernelShaderMapHash, nullptr, nullptr ) , DebugDescription(InDebugDescription)`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeKernelShared.h` (Private)


#### class `FComputeKernelCompilationOutput`  
`class FComputeKernelCompilationOutput`  
_L28-34_
- desc: Stores outputs from the  kernel compile that need to be saved.
- L32 _public function_ `FComputeKernelCompilationOutput()`

#### class `FComputeKernelShaderMapId`  
`class FComputeKernelShaderMapId`  
_L37-103_
- desc: Contains all the information needed to uniquely identify a FComputeKernelShaderMapID.
- L58 _public function_ `FComputeKernelShaderMapId() : FeatureLevel(ERHIFeatureLevel::SM5)`
- L62 _public prototype_ `~FComputeKernelShaderMapId() = default;`
- L65 _public prototype_ `void SetShaderDependencies(const TArray<FShaderType*>& InShaderTypes, EShaderPlatform InShaderPlatform);`
- L75 _public function_ `SIZE_T GetSizeBytes() const`
- L81 _public prototype_ `uint64 GetComputeKernelHash() const;` — Hashes the kernel specific part of this shader map Id.
- L89 _public prototype_ `bool operator==(const FComputeKernelShaderMapId& InReferenceSet) const;` — Tests this set against another for equality, disregarding override settings. @param InReferenceSet	The set to compare against @return					true if the sets are equal
- L91 _public function_ `bool operator!=(const FComputeKernelShaderMapId& InReferenceSet) const`
- L98 _public prototype_ `void AppendKeyString(FString& OutKeyString) const;` — Appends string representations of this Id to a key string.
- L102 _public prototype_ `bool ContainsShaderType(const FShaderType* ShaderType) const;` — Returns true if the requested shader type is a dependency of this shader map Id.

#### class `FComputeKernelShaderMapContent`  
`class FComputeKernelShaderMapContent : public FShaderMapContent`  
_L105-121_
- inherits: `FShaderMapContent`
- L107 _private typedef_ `using Super = FShaderMapContent;`
- L111 _private function_ `explicit FComputeKernelShaderMapContent(EShaderPlatform InPlatform) : Super(InPlatform)`

#### class `FComputeKernelShaderMap`  
`class FComputeKernelShaderMap : public TShaderMap<FComputeKernelShaderMapContent, FShaderMapPointerTable>, public FDeferredCleanupInterface`  
_L127-296_
- inherits: `TShaderMap<FComputeKernelShaderMapContent,FShaderMapPointerTable>,FDeferredCleanupInterface`
- desc: All the shader permutations for a kernel.
- L130 _public typedef_ `using Super = TShaderMap<FComputeKernelShaderMapContent, FShaderMapPointerTable>;`
- L138 _public prototype_ `static TRefCountPtr<FComputeKernelShaderMap> FindId(const FComputeKernelShaderMapId& InShaderMapId, EShaderPlatform InPlatform);` — Finds the shader map for a kernel. @param InShaderMapId - Id to find @param Platform - The platform to lookup for @return nullptr if no cached shader map was found.
- L141 _public function_ `template<typename ShaderType> TShaderRef<ShaderType> GetShader(int32 PermutationId) const` — ShaderMap interface
- L149 _public prototype_ `static void LoadFromDerivedDataCache(const FComputeKernelResource* InKernel, const FComputeKernelShaderMapId& InShaderMapId, EShaderPlatform InPlatform, TRefCountPtr<FComputeKernelShaderMap>& InOutShaderMap);` — Attempts to load the shader map for the given kernel from the Derived Data Cache. If InOutShaderMap is valid, attempts to load the individual missing shaders instead.
- L152 _public prototype_ `FComputeKernelShaderMap();`
- L153 _public prototype_ `~FComputeKernelShaderMap();`
- L162 _public prototype_ `void Compile( FComputeKernelResource* InKernel, const FComputeKernelShaderMapId& InShaderMapId, TRefCountPtr<FSharedShaderCompilerEnvironment> InCompilationEnvironment, const FComputeKernelCompilationOutput& InCompilationOutput, EShaderPlatform InPlatform, bool bSynchronousCompile, bool bApplyCompletedShaderMapForRendering );` — Compiles the shaders for a kernel and caches them in this shader map. @param InKernel - The kernel to compile shaders for. @param InShaderMapId - the set of static parameters to compile for @param InPlatform - The platform to compile to
- L173 _public prototype_ `bool ProcessCompilationResults(const TArray<FShaderCommonCompileJobPtr>& InCompilationResults, int32& InOutResultIndex, float& InOutTimeBudget);` — Sorts the incoming compiled jobs into the appropriate shader maps, and finalizes this shader map so that it can be used for rendering.
- L181 _public prototype_ `bool IsComplete(const FComputeKernelResource* InKernel, bool bSilent);` — Checks whether the shader map is missing any shader types necessary for the given kernel. @param InKernel - The ComputeKernel which is checked. @return True if the shader map has all of the shader types necessary.
- L190 _public prototype_ `bool TryToAddToExistingCompilationTask(FComputeKernelResource* InKernel);` — Checks to see if the shader map is already being compiled for another kernel, and if so adds the specified kernel to the list to be applied to once the compile finishes. @param InKernel - The ComputeKernel we also wish to apply the compiled shader map to. @return True if the shader map was being compiled and we added it to the list to be applied.
- L194 _public prototype_ `void GetShaderList(TMap<FShaderId, TShaderRef<FShader>>& OutShaders) const;` — Builds a list of the shaders in a shader map.
- L195 _public prototype_ `virtual void GetShaderList(TMap<FHashedName, TShaderRef<FShader>>& OutShaders) const override;`
- L196 _public prototype_ `virtual void GetShaderPipelineList(TArray<FShaderPipelineRef>& OutShaderPipelines) const override;`
- L199 _public prototype_ `void Register(EShaderPlatform InShaderPlatform);` — Registers a ComputeKernel shader map in the global map so it can be used.
- L202 _public prototype_ `void AddRef();` — Reference counting.
- L203 _public prototype_ `void Release();`
- L207 _public prototype_ `static void RemovePending(FComputeKernelResource* InKernel);` — Removes a kernel from ComputeKernelShaderMapsBeingCompiled.
- L211 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes the shader map.
- L215 _public prototype_ `void SaveToDerivedDataCache();` — Saves this shader map to the derived data cache.
- L219 _public function_ `const FComputeKernelShaderMapId& GetShaderMapId() const` — Accessors.
- L220 _public function_ `EShaderPlatform GetShaderPlatform() const`
- L221 _public function_ `const FMemoryImageString& GetFriendlyName() const`
- L222 _public function_ `uint32 GetCompilingId() const`
- L223 _public function_ `bool IsCompilationFinalized() const`
- L224 _public function_ `bool CompiledSuccessfully() const`
- L226 _public function_ `bool IsValid() const`
- L231 _public function_ `int32 GetNumRefs() const`
- L232 _public function_ `uint32 GetCompilingId()`
- L235 _public function_ `static TMap<TRefCountPtr<FComputeKernelShaderMap>, TArray<FComputeKernelResource*> > &GetInFlightShaderMaps()`
- L242 _public function_ `void SetCompiledSuccessfully(bool bSuccess)`
- L252 _private member_ `static TMap<FComputeKernelShaderMapId, FComputeKernelShaderMap*> GIdToComputeKernelShaderMap[SP_NumPlatforms];` — A global map from a kernel's ID and static switch set to any shader map cached for that kernel. Note: this does not necessarily contain all kernel shader maps in memory.  Shader maps with the same key can evict each other. No ref counting needed as these are removed on destruction of the shader map.
- L257 _private member_ `static FCriticalSection ShaderMapRegistryMutex;` — Protects GIdToComputeKernelShaderMap plus associated state. These are mutated from any thread that constructs/destroys/registers/unregisters a FComputeKernelShaderMap including async-loading worker threads.
- L262 _private member_ `static TMap<TRefCountPtr<FComputeKernelShaderMap>, TArray<FComputeKernelResource*> > ComputeKernelShaderMapsBeingCompiled;` — Tracks resources and their shader maps that are being compiled. Game-thread only, asserted by check(IsInGameThread()) at every access point.
- L266 _private member_ `uint32 CompilingId;` — Uniquely identifies this shader map during compilation, needed for deferred compilation where shaders from multiple shader maps are compiled together.
- L268 _private member_ `mutable int32 NumRefs;`
- L271 _private member_ `std::atomic<bool> bDeletedThroughDeferredCleanup;` — Used to catch errors where the shader map is deleted directly.
- L274 _private member_ `std::atomic<bool> bRegistered;` — Indicates whether this shader map has been registered in GIdToComputeKernelShaderMap
- L280 _private member_ `std::atomic<bool> bCompilationFinalized;` — Indicates whether this shader map has had ProcessCompilationResults called after Compile. The shader map must not be used on the rendering thread unless bCompilationFinalized is true.
- L282 _private member_ `std::atomic<bool> bCompiledSuccessfully;`
- L285 _private member_ `uint32 bIsPersistent : 1;` — Indicates whether the shader map should be stored in the shader cache.
- L287 _private member_ `uint32 bHasFrozenContent : 1;`
- L290 _private prototype_ `FShader* ProcessCompilationResultsForSingleJob(FShaderCompileJob& InSingleJob, uint64 InShaderMapHash);`
- L293 _private prototype_ `bool IsComputeKernelShaderComplete(const FComputeKernelResource* InKernel, const FComputeKernelShaderType* InShaderType, bool bSilent);`

#### class `FComputeKernelResource`  
`class FComputeKernelResource`  
_L304-582_
- desc: FComputeKernelResource represents a UComputeKernel to the shader compilation process
- L307 _public prototype_ `FComputeKernelResource();`
- L308 _public prototype_ `virtual ~FComputeKernelResource();`
- L314 _public prototype_ `bool CacheShaders(EShaderPlatform InPlatform, const ITargetPlatform* TargetPlatform, bool bApplyCompletedShaderMapForRendering, bool bSynchronous);` — Caches the shaders for this kernel with no static parameters on the given platform. This is used by UComputeKernel
- L315 _public prototype_ `bool CacheShaders(const FComputeKernelShaderMapId& InShaderMapId, EShaderPlatform InPlatform, bool bApplyCompletedShaderMapForRendering, bool bSynchronous);`
- L316 _public prototype_ `bool CacheInlineShaders(EShaderPlatform InPlatform);`
- L326 _public prototype_ `virtual bool ShouldCache(EShaderPlatform InPlatform, const FShaderType* InShaderType) const;` — Should the shader for this kernel with the given platform and shader type combination be compiled @param InPlatform		The platform currently being compiled for @param InShaderType		Which shader is being compiled @return true if the shader should be compiled
- L328 _public prototype_ `void SerializeShaderMap(FArchive& Ar);`
- L331 _public prototype_ `void ReleaseShaderMap();` — Releases this kernel's shader map.  Must only be called on ComputeKernels not exposed to the rendering thread!
- L334 _public prototype_ `void DiscardShaderMap();` — Discards loaded shader maps if the application can't render
- L336 _public prototype_ `void GetDependentShaderTypes(EShaderPlatform InPlatform, TArray<FShaderType*>& OutShaderTypes) const;`
- L337 _public prototype_ `virtual void GetShaderMapId(EShaderPlatform InPlatform, const ITargetPlatform* TargetPlatform, FComputeKernelShaderMapId& OutId) const;`
- L339 _public prototype_ `void Invalidate();`
- L344 _public function_ `virtual bool IsPersistent() const` — Should shaders compiled for this kernel be saved to disk?
- L349 _public prototype_ `virtual void NotifyCompilationFinished(FString const& ResultMessage);` — Called when compilation finishes, after the GameThreadShaderMap is set and the render command to set the RenderThreadShaderMap is queued
- L355 _public prototype_ `void CancelCompilation();` — Cancels all outstanding compilation jobs
- L360 _public prototype_ `void FinishCompilation();` — Blocks until compilation has completed. Returns immediately if a compilation is not outstanding.
- L368 _public prototype_ `bool IsCompilationFinished() const;` — Checks if the compilation for this shader is finished @return returns true if compilation is complete false otherwise
- L371 _public function_ `FComputeKernelCompileResults const& GetCompilationResults() const` — Accessors.
- L372 _public function_ `void SetCompilationResults(FComputeKernelCompileResults const& InCompilationResults)`
- L374 _public function_ `ERHIFeatureLevel::Type GetFeatureLevel() const`
- L376 _public function_ `FComputeKernelShaderMap* GetGameThreadShaderMap() const`
- L383 _public function_ `FName GetOwnerFName() const` — Returns owner name for tracking
- L389 _public function_ `void SetGameThreadShaderMap(FComputeKernelShaderMap* InShaderMap)` — Note: SetRenderingThreadShaderMap must also be called with the same value, but from the rendering thread.
- L400 _public prototype_ `void SetRenderingThreadShaderMap(FComputeKernelShaderMap* InShaderMap);` — Note: SetGameThreadShaderMap must also be called with the same value, but from the game thread.
- L402 _public function_ `void AddCompileId(uint32 InIdentifier)`
- L407 _public function_ `void SetInlineShaderMap(FComputeKernelShaderMap* InShaderMap)`
- L420 _public prototype_ `void RemoveOutstandingCompileId(const int32 InOldOutstandingCompileShaderMapId);`
- L427 _public function_ `bool GetHLSLSource(FString& OutSource) const` — Get generated or written source code for the shader @param OutSource - generated source code @return - true on Success
- L433 _public function_ `const FString& GetHLSLSource() const`
- L438 _public function_ `const FString& GetEntryPoint() const`
- L443 _public function_ `const FString& GetFriendlyName() const`
- L445 _public prototype_ `int32 GetNumPermutations() const;`
- L447 _public prototype_ `void SetupResource( ERHIFeatureLevel::Type InFeatureLevel, FString const& InFriendlyName, FString const& InShaderEntryPoint, FString const& InShaderHashKey, FString const& InShaderSource, TMap<FString, FString> const& InAdditionalSources, TMap<FString, FString> const& InGeneratedSources, TSharedPtr<FComputeKernelDefinitionSet>& InShaderDefinitionSet, TSharedPtr<FComputeKernelPermutationVector>& InShaderPermutationVector, TUniquePtr<FShaderParametersMetadataAllocations>& InShaderParameterMetadataAllocations, FShaderParametersMetadata* InShaderParameterMetadata, FName const& InAssetPath );`
- L463 _public prototype_ `void SetupCompileEnvironment(int32 InPermutationId, FShaderCompilerEnvironment& OutShaderEnvironment) const;`
- L466 _public function_ `const FShaderParametersMetadata* GetShaderParamMetadata() const`
- L471 _public prototype_ `TShaderRef<FComputeKernelShader> GetShader(int32 PermutationId) const;`
- L472 _public prototype_ `TShaderRef<FComputeKernelShader> GetShaderGameThread(int32 PermutationId) const;`
- L474 _public prototype_ `bool IsSame(const FComputeKernelShaderMapId& InId) const;`
- L476 _public function_ `uint32 GetKernelFlags() const`
- L478 _public function_ `FOnComputeKernelCompilationComplete& OnCompilationComplete()`
- L485 _protected prototype_ `void GetShaderMapIDsWithUnfinishedCompilation(TArray<int32>& OutShaderMapIds);` — Fills the passed array with IDs of shader maps unfinished compilation jobs.
- L489 _private member_ `FComputeKernelCompileResults CompilationResults;`
- L497 _private member_ `TRefCountPtr<FComputeKernelShaderMap> GameThreadShaderMap = nullptr;` — Game thread tracked shader map, which is ref counted and manages shader map lifetime. The shader map uses deferred deletion so that the rendering thread has a chance to process a release command when the shader map is no longer referenced. Code that sets this is responsible for updating RenderingThreadShaderMap in a thread safe way. During an async compile, this will be NULL and will not contain the actual shader map until compilation is complete.
- L503 _private member_ `FComputeKernelShaderMap* RenderingThreadShaderMap = nullptr;` — Shader map for this FComputeKernelResource which is accessible by the rendering thread. This must be updated along with GameThreadShaderMap, but on the rendering thread.
- L506 _private member_ `FString ShaderEntryPoint;` — Name of shader main function.
- L509 _private member_ `FString ShaderSource;` — Cached shader source for compilation.
- L515 _private member_ `uint64 ShaderCodeHash = 0;` — Hash computed from shader code. If multiple kernels give the same output, same shader resource will be shared
- L518 _private member_ `TMap<FString, FString> AdditionalSources;` — Additional source code. Stored as a map from a virtual source file name to the shader source.
- L520 _private member_ `TMap<FString, FString> GeneratedSources;` — Generated source code. Stored as a map from a virtual source file name to the shader source.
- L523 _private member_ `TSharedPtr<FComputeKernelDefinitionSet> ShaderDefinitionSet;` — Defines used when compiling shaders. Object can be shared across a number of shader formats during cook.
- L526 _private member_ `TSharedPtr<FComputeKernelPermutationVector> ShaderPermutationVector;` — Permutations used for compiling shaders. Object can be shared across a number of shader formats during cook.
- L529 _private member_ `TUniquePtr<FShaderParametersMetadataAllocations> ShaderParameterMetadataAllocations;` — Allocations for the ShaderParameterMetadata
- L532 _private member_ `FShaderParametersMetadata const* ShaderParameterMetadata;` — Shader parameter metadata. It is expected that object is owned by ShaderParameterMetadataAllocations.
- L535 _private member_ `uint32 KernelFlags = 0;` — Compilation flags.
- L541 _private member_ `TArray<int32, TInlineAllocator<1> > OutstandingCompileShaderMapIds;` — Contains the compiling id of this shader map when it is being compiled asynchronously. This can be used to access the shader map during async compiling, since GameThreadShaderMap will not have been set yet.
- L544 _private member_ `ERHIFeatureLevel::Type FeatureLevel = ERHIFeatureLevel::SM5;` — Feature level that this kernel is representing.
- L551 _private member_ `uint32 bContainsInlineShaders : 1;`
- L552 _private member_ `uint32 bLoadedCookedShaderMapId : 1;`
- L553 _private member_ `FComputeKernelShaderMapId CookedShaderMapId;`
- L555 _private member_ `FOnComputeKernelCompilationComplete OnCompilationCompleteDelegate;`
- L561 _private prototype_ `bool BeginCompileShaderMap( const FComputeKernelShaderMapId& InShaderMapId, EShaderPlatform InPlatform, TRefCountPtr<FComputeKernelShaderMap>& OutShaderMap, bool bApplyCompletedShaderMapForRendering, bool bSynchronous = false);` — Compiles this kernel for InPlatform, storing the result in OutShaderMap if the compile was synchronous
- L569 _private prototype_ `void SetupShaderCompilationEnvironment( EShaderPlatform InPlatform, FShaderCompilerEnvironment& OutEnvironment ) const;` — Populates OutEnvironment with defines needed to compile shaders for this kernel.
- L575 _private member_ `FString FriendlyName;`
- L578 _private member_ `FName AssetPath;` — Asset using this resource

#### Free symbols / members of external scopes

- L70 _function_ `friend uint32 GetTypeHash(const FComputeKernelShaderMapId& Ref)`
- L299 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComputeKernelCompilationComplete, FComputeKernelResource const*);` — Delegate for kernel compile completion.
- L299 _prototype_ `DECLARE_DELEGATE_OneParam(FOnComputeKernelCompilationComplete, FComputeKernelResource const*);` — Delegate for kernel compile completion.

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeSystem.h` (Private)


#### class `FComputeFrameworkSystem`  
`class FComputeFrameworkSystem : public IComputeSystem`  
_L12-25_
- inherits: `IComputeSystem`
- desc: Implementation of IComputeSystem which manages FComputeGraphTaskWorker objects.
- L16 _public prototype_ `void CreateWorkers(FSceneInterface const* InScene, TArray<IComputeTaskWorker*>& OutWorkers) override;` — IComputeSystem implementation
- L17 _public prototype_ `void DestroyWorkers(FSceneInterface const* InScene, TArray<IComputeTaskWorker*>& InOutWorkers) override;`
- L20 _public prototype_ `FComputeGraphTaskWorker* GetComputeWorker(FSceneInterface const* InScene) const;` — Get the FComputeGraphTaskWorker object associated with the Scene.
- L23 _private member_ `TMap<FSceneInterface const*, FComputeGraphTaskWorker*> ComputeWorkers;`
- L24 _private member_ `TMap<FSceneInterface const*, TSharedPtr<FComputeViewExtension, ESPMode::ThreadSafe>> ViewExtensions;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeFramework/ComputeViewExtension.h` (Private)


#### class `FComputeViewExtension`  
`class FComputeViewExtension : public FWorldSceneViewExtension`  
_L10-23_
- inherits: `FWorldSceneViewExtension`
- desc: Compute view extension, useful for receiving callbacks from renderer.
- L13 _public prototype_ `FComputeViewExtension(const FAutoRegister& AutoReg, UWorld* InWorld);`
- L16 _public prototype_ `virtual void PostTLASBuild_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;`
- L17 _public prototype_ `virtual ESceneViewExtensionFlags GetFlags() const override;`
- L22 _private member_ `mutable TArray<IComputeTaskWorker*> ComputeWorkers;` — Local to methods but stored here and emptied at each usage to avoid per frame array allocations.

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeDataInterface.h` (Public)


#### class `UComputeDataInterface`  
`class UComputeDataInterface : public UObject`  
_L23-67_
- reflection: `UCLASS(MinimalAPI, Abstract, Const)`
- inherits: `UObject`
- desc: Compute Data Interface required to compile a Compute Graph. Compute Kernels require Data Interfaces to fulfill their external functions. Compute Data Interfaces define how Compute Data Providers will actually marshal data in and out of Kernels.
- L29 _public function_ `virtual TCHAR const* GetClassName() const PURE_VIRTUAL(UComputeDataInterface::GetClassName, return nullptr;) virtual bool IsExecutionInterface() const` — Get a name for referencing the data interface its shader parameter structures. The InUniqueIndex is optional for use in generating the name.
- L33 _public function_ `virtual bool CanSupportUnifiedDispatch() const` — Return true if the associated UComputeDataProvider holds data that can be combined into a single dispatch invocation.
- L35 _public function_ `virtual void GetDefines(FComputeKernelDefinitionSet& OutDefinitionSet) const` — Gather compile definitions from the data interface. Any connected kernel will compile with these.
- L37 _public function_ `virtual void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const` — Gather permutations from the data interface. Any connected kernel will include these in its total compiled permutations.
- L39 _public function_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const` — Get the data interface functions available to fulfill external inputs of a kernel.
- L41 _public function_ `virtual void GetSupportedOutputs(TArray<FShaderFunctionDefinition>& OutFunctions) const` — Get the data interface functions available to fulfill external outputs of a kernel.
- L43 _public function_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const` — Gather the shader metadata exposed by the data provider payload.
- L45 _public function_ `virtual TCHAR const* GetShaderVirtualPath() const` — If the data interface HLSL comes from a file this should fill the virtual file path. This is used to resolve shader compilation errors.
- L47 _public function_ `virtual void GetShaderHash(FString& InOutKey) const` — Get a hash that changes on any data interface changes that affect kernel compilation.
- L49 _public function_ `virtual void GetStructDeclarations(TSet<FString>& OutStructsSeen, TArray<FString>& OutStructs) const` — Gather any extra struct types that this data provider relies on.
- L51 _public function_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const` — Gather the shader code for this data provider.
- L53 _public function_ `virtual bool GetRequiresReadback() const` — Whether a GPU->CPU readback should be scheduled after this data is used as a kernel output.
- L55 _public function_ `virtual bool GetRequiresPreSubmitCall() const` — Whether PreSubmit should be called when this data is used as a kernel output.
- L57 _public function_ `virtual bool GetRequiresPostSubmitCall() const` — Whether PostSubmit should be called when this data is used as a kernel output.
- L59 _public function_ `virtual bool GetRequiresPerKernelInputOutputMasks() const` — Whether to call InitializePerKernelInputOutputMasks on the provider in addition to Initialize.
- L61 _public function_ `virtual UClass* GetBindingType() const` — Get class of UObject required to instantiate a UComputeDataProvider from this interface.
- L63 _public function_ `virtual UComputeDataProvider* CreateDataProvider() const` — Instantiate an associated UComputeDataProvider.
- L66 _public function_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const` — `UE_DEPRECATED(5.6, "Use the no-argument version together with UComputeDataProvider::Initialize()")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeDataProvider.h` (Public)


#### class `UComputeDataProvider`  
`class UComputeDataProvider : public UObject`  
_L23-57_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Compute Framework Data Provider. A concrete instance of this is responsible for supplying data declared by a UComputeDataInterface. One of these must be created for each UComputeDataInterface object in an instance of a Compute Graph.
- L29 _public function_ `virtual void Initialize(UComputeDataInterface const* InDataInterface, UObject* InBinding, uint64 InInputMask, uint64 InOutputMask)` — Set up the data provider from the given data interface and binding.
- L30 _public function_ `virtual void Initialize(int32 InDataInterfaceIndex, UComputeDataInterface const* InDataInterface, UObject* InBinding, uint64 InInputMask, uint64 InOutputMask)`
- L47 _public function_ `virtual void InitializePerKernelInputOutputMasks(TMap<int32, FInputOutputMask>&& InPerKernelMasks)` — Called only when the associated UComputeDataInterface::GetRequiresPerKernelInputOutputMasks() returns true. Supplies the per-kernel breakdown of input/output bindings, which can be use by the proxy for bookkeeping data related to the currently dispatching kernel (looked up via FComputeContext::GraphKernelIndex).
- L53 _public function_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy()` — Get an associated render thread proxy object. Currently these are created and destroyed per frame by the FComputeGraphInstance.
- L56 _public function_ `virtual void Reset()` — Reset state and release any held resources.

#### struct `UComputeDataProvider::FInputOutputMask`  
`struct FInputOutputMask`  
_L36-40_
- L38 _public member_ `uint64 InputMask = 0;`
- L39 _public member_ `uint64 OutputMask = 0;`

#### class `FComputeDataProviderRenderProxy`  
`class FComputeDataProviderRenderProxy`  
_L63-164_
- desc: Compute Framework Data Provider Proxy. A concrete instance of this is created by the UComputeDataProvider gathering of data for a Compute Kernel on the render thread.
- L66 _public prototype_ `virtual ~FComputeDataProviderRenderProxy() = default;`
- L72 _public function_ `virtual int32 GetDispatchThreadCount(TArray<FIntVector>& ThreadCounts) const` — Called on render thread to determine invocation count and dispatch thread counts per invocation. This will only be called if the associated UComputeDataInterface returned true for IsExecutionInterface().
- L85 _public function_ `virtual bool IsValid(FValidationData const& InValidationData) const` — Validates that we are OK to dispatch work. Default implementation returns false.
- L99 _public function_ `virtual void GatherPermutations(FPermutationData& InOutPermutationData) const` — Gathers permutation bits for each invocation. This is called before any calls to AllocateResources() because we validate all requested shaders before doing any further work.
- L110 _public function_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData)` — Called once before any calls to GatherDispatchData() to allow any RDG resource allocation.
- L125 _public function_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData)` — Collect parameter data required to dispatch work.
- L127 _public typedef_ `using FReadbackCallback = TFunction<void(const void* InData, int InNumBytes)>;`
- L141 _public function_ `virtual void GetReadbackData(TArray<FReadbackData>& OutReadbackData) const` — Data for any readbacks that should be performed.
- L144 _public function_ `virtual void PreSubmit(FComputeContext& Context) const` — Called immediately prior to every kernel dispatch that outputs to this data.
- L147 _public function_ `virtual void PostSubmit(FComputeContext& Context) const` — Called immediately after every kernel dispatch that outputs to this data.
- L152 _protected function_ `template <typename ElementType> TStridedView<ElementType> MakeStridedParameterView(FDispatchData const& InDispatchData)` — Helper for making an FStridedView over the FDispatchData.
- L159 _public function_ `virtual void PostGraphDispatch(FRDGBuilder& GraphBuilder) const` — `UE_DEPRECATED(5.6, "Use PostSubmit instead.")`
- L161 _public prototype_ `virtual void PreSubmit(FRDGBuilder& InGraphBuilder) const;` — `UE_DEPRECATED(5.7, "Use version that takes FComputeContext instead.")`
- L163 _public prototype_ `virtual void PostSubmit(FRDGBuilder& InGraphBuilder) const;` — `UE_DEPRECATED(5.7, "Use version that takes FComputeContext instead.")`

#### struct `FComputeDataProviderRenderProxy::FValidationData`  
`struct FValidationData`  
_L75-79_
- desc: Data needed for validation.
- L77 _public member_ `int32 NumInvocations;`
- L78 _public member_ `int32 ParameterStructSize;`

#### struct `FComputeDataProviderRenderProxy::FPermutationData`  
`struct FPermutationData`  
_L88-93_
- desc: Data needed for setting permuations.
- L90 _public member_ `const int32 NumInvocations;`
- L91 _public member_ `const FComputeKernelPermutationVector& PermutationVector;`
- L92 _public member_ `TArray<int32> PermutationIds;`

#### struct `FComputeDataProviderRenderProxy::FAllocationData`  
`struct FAllocationData`  
_L102-107_
- desc: Setup needed to allocate resources.
- L104 _public member_ `int32 NumGraphKernels = 0;`
- L106 _public member_ `FRDGExternalAccessQueue& ExternalAccessQueue;` — Queue for AllocateResources() to add any resources that need to be externally (non-RDG) managed at the end of compute graph execution.

#### struct `FComputeDataProviderRenderProxy::FDispatchData`  
`struct FDispatchData`  
_L113-122_
- desc: Setup needed to gather dispatch data.
- L115 _public member_ `int32 GraphKernelIndex;`
- L116 _public member_ `int32 NumInvocations;`
- L117 _public member_ `bool bUnifiedDispatch;`
- L118 _public member_ `int32 ParameterStructSize;`
- L119 _public member_ `int32 ParameterBufferOffset;`
- L120 _public member_ `int32 ParameterBufferStride;`
- L121 _public member_ `uint8* ParameterBuffer;`

#### struct `FComputeDataProviderRenderProxy::FReadbackData`  
`struct FReadbackData`  
_L128-138_
- L131 _public member_ `FRDGBufferRef Buffer;` — The buffer to be read back.
- L134 _public member_ `uint32 NumBytes;` — The number of bytes to read back.
- L137 _public member_ `const FReadbackCallback* ReadbackCallback_RenderThread;` — Callback to execute once data is ready for CPU consumption.

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeFramework.h` (Public)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogComputeFramework, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogComputeFramework, Log, All);`
- L12 _namespace_ `namespace ComputeFramework`
- L15 _prototype_ `bool IsSupported(EShaderPlatform ShaderPlatform);` (scope `ComputeFramework`) — Returns true if ComputeFramework is supported on a platform.
- L18 _prototype_ `bool IsEnabled();` (scope `ComputeFramework`) — Returns true if ComputeFramework is currently enabled.
- L21 _prototype_ `bool IsDeferredCompilation();` (scope `ComputeFramework`) — Returns true if compute graphs are compiled on first use instead of on PostLoad().
- L24 _prototype_ `void RebuildComputeGraphs();` (scope `ComputeFramework`) — Rebuild all compute graphs.
- L27 _prototype_ `void TickCompilation(float DeltaSeconds);` (scope `ComputeFramework`) — Tick shader compilation.
- L30 _prototype_ `void FlushWork(FSceneInterface const* InScene, FName InExecutionGroupName);` (scope `ComputeFramework`) — Flush any enqueued ComputeGraph work for a given execution group.
- L33 _prototype_ `void AbortWork(FSceneInterface const* InScene, UObject* OwnerPointer);` (scope `ComputeFramework`) — Aborts any queued work associated with the scene / execution group / owner pointer tuple.

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeFrameworkKernelTiming.h` (Public)


#### struct `FComputeFrameworkKernelTiming`  
`struct FComputeFrameworkKernelTiming`  
_L7-10_
- desc: Timing result for a single compute kernel, fulfilled by the GPU profiler's end-of-pipe callback. Currently captures busy time only; idle and wait times can be added here as needed.
- L9 _public member_ `double BusyMs = 0.0;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeFrameworkObjectVersion.h` (Public)


#### struct `FComputeFrameworkObjectVersion`  
`struct FComputeFrameworkObjectVersion`  
_L8-23_
- L11 _public prototype_ `FComputeFrameworkObjectVersion() = delete;` — Not instantiable.
- L22 _public member_ `const static FGuid GUID;` — The GUID for this custom version number

#### enum `FComputeFrameworkObjectVersion::Type`  
`enum Type`  
_L13-19_
- L15 _public enumerator_ `InitialVersion = 0`
- L17 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L18 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeGraph.h` (Public)


#### struct `FComputeGraphEdge`  
`struct FComputeGraphEdge`  
_L33-63_
- reflection: `USTRUCT()`
- desc: Description of a single edge in a UComputeGraph. todo[CF]: Consider better storage for graph data structure that is easier to interrogate efficiently.
- L38 _public member_ `int32 KernelIndex;` — `UPROPERTY()`
- L40 _public member_ `int32 KernelBindingIndex;` — `UPROPERTY()`
- L42 _public member_ `int32 DataInterfaceIndex;` — `UPROPERTY()`
- L44 _public member_ `int32 DataInterfaceBindingIndex;` — `UPROPERTY()`
- L46 _public member_ `bool bKernelInput;` — `UPROPERTY()`
- L51 _public member_ `FString BindingFunctionNameOverride;` — `UPROPERTY()` — Optional name to use for the proxy generation function, in case the kernel expects something other than the interface's bind name. Leave empty to go with the default.
- L54 _public member_ `FString BindingFunctionNamespace;` — `UPROPERTY()` — Optional namespace to wrap the binding function in. A blank mean global namespace.
- L56 _public function_ `FComputeGraphEdge() : KernelIndex(0) , KernelBindingIndex(0) , DataInterfaceIndex(0) , DataInterfaceBindingIndex(0) , bKernelInput(false)`

#### class `UComputeGraph`  
`class UComputeGraph : public UObject`  
_L72-247_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Class representing a Compute Graph. This holds the basic topology of the graph and is responsible for linking Kernels with Data Interfaces and compiling the resulting shader code. Multiple Compute Graph asset types can derive from this to specialize the graph creation process. For example the Animation Deformer system provides a UI for creating UComputeGraph assets.
- L81 _protected member_ `TArray<TObjectPtr<UComputeKernel>> KernelInvocations;` — `UPROPERTY()` — Kernels in the graph.
- L85 _protected member_ `TArray<TObjectPtr<UComputeDataInterface>> DataInterfaces;` — `UPROPERTY()` — Data interfaces in the graph.
- L89 _protected member_ `TArray<FComputeGraphEdge> GraphEdges;` — `UPROPERTY()` — Edges in the graph between kernels and data interfaces.
- L93 _protected member_ `TArray<TObjectPtr<UClass>> Bindings;` — `UPROPERTY()` — Registered binding object class types.
- L97 _protected member_ `TArray<int32> DataInterfaceToBinding;` — `UPROPERTY()` — Mapping of DataInterfaces array index to Bindings index.
- L100 _public prototype_ `UComputeGraph();`
- L101 _public prototype_ `UComputeGraph(const FObjectInitializer& ObjectInitializer);`
- L102 _public prototype_ `UComputeGraph(FVTableHelper& Helper);`
- L105 _public function_ `virtual void OnKernelCompilationComplete(int32 InKernelIndex, FComputeKernelCompileResults const& InCompileResults)` — Called each time that a single kernel shader compilation is completed.
- L111 _public prototype_ `bool ValidateGraph(FString* OutErrors = nullptr);` — Returns true if graph is valid. A valid graph should be guaranteed to compile, assuming the underlying shader code is well formed.
- L114 _public function_ `int32 GetNumBindingObjects() const` — Get the number of binding objects used by the graph.
- L121 _public prototype_ `void CreateDataProviders(int32 InBindingIndex, TObjectPtr<UObject>& InBindingObject, TArray< TObjectPtr<UComputeDataProvider> >& InOutDataProviders) const;` — Create UComputeDataProvider objects to match the current UComputeDataInterface objects and initialize them. We attempt to setup bindings from the InBindingObjects. The caller is responsible for any data provider binding not handled by the default behavior.
- L124 _public prototype_ `void InitializeDataProviders(int32 InBindingIndex, TObjectPtr<UObject>& InBindingObject, TArray< TObjectPtr<UComputeDataProvider> >& InDataProviders) const;` — Initialize the data providers.
- L127 _public prototype_ `bool ValidateProviders(TArray< TObjectPtr<UComputeDataProvider> > const& DataProviders) const;` — Returns true if there is a valid DataProvider entry for each of our DataInterfaces.
- L130 _public prototype_ `FComputeGraphRenderProxy const* GetRenderProxy() const;` — Get the render proxy which is a copy of all data required by the render thread.
- L136 _public prototype_ `void UpdateResources(bool bSync = false);` — Call after changing the graph to build the graph resources for rendering. This will trigger any required shader compilation. By default it does async compilation
- L142 _public prototype_ `bool HasKernelResourcesPendingShaderCompilation() const;` — Shader compilations triggered by UpdateResources() are async, This checks if all kernel resources are ready.
- L146 _protected prototype_ `void Serialize(FArchive& Ar) override;`
- L147 _protected prototype_ `void PostLoad() override;`
- L148 _protected prototype_ `void BeginDestroy() override;`
- L150 _protected prototype_ `void OnCookEvent(UE::Cook::ECookEvent CookEvent, UE::Cook::FCookEventContext& CookContext) override;`
- L151 _protected prototype_ `void BeginCacheForCookedPlatformData(ITargetPlatform const* TargetPlatform) override;`
- L152 _protected prototype_ `bool IsCachedCookedPlatformDataLoaded(ITargetPlatform const* TargetPlatform) override;`
- L153 _protected prototype_ `void ClearCachedCookedPlatformData(ITargetPlatform const* TargetPlatform) override;`
- L154 _protected prototype_ `void ClearAllCachedCookedPlatformData() override;`
- L160 _private prototype_ `FShaderParametersMetadata* BuildKernelShaderMetadata(int32 InKernelIndex, FShaderParametersMetadataAllocations& InOutAllocations) const;` — Build the shader metadata which describes bindings for a kernel with its linked data interfaces.
- L162 _private prototype_ `void BuildShaderPermutationVectors(TArray<FComputeKernelPermutationVector>& OutShaderPermutationVectors) const;` — Build the shader permutation vectors for all kernels in the graph.
- L164 _private prototype_ `FComputeGraphRenderProxy* CreateRenderProxy() const;` — Create the render proxy.
- L166 _private prototype_ `void ReleaseRenderProxy(FComputeGraphRenderProxy* InProxy) const;` — Release the render proxy.
- L168 _private prototype_ `void GetDataInterfaceInputOutputMasks(int32 InDataInterfaceIndex, uint64& OutInputMask, uint64& OutOutputMask) const;` — Returns input and output masks for the given data interface.
- L172 _private prototype_ `FString BuildKernelSource( int32 KernelIndex, UComputeKernelSource const& InKernelSource, TMap<FString, FString> const& InAdditionalSources, FString& OutHashKey, TMap<FString, FString>& OutGeneratedSources, FComputeKernelDefinitionSet& OutDefinitionSet, FComputeKernelPermutationVector& OutPermutationVector) const;` — Build the HLSL source for a kernel with its linked data interfaces.
- L182 _private prototype_ `void CacheResourceShadersForRendering(uint32 CompilationFlags);` — Cache shader resources for all kernels in the graph.
- L185 _private prototype_ `bool CacheCookedResourceShadersForRendering();` — For cooked packages, promote inline shader maps to the render thread. Returns false if any kernel was missing an inline shader map.
- L188 _private prototype_ `static void CacheShadersForResource( EShaderPlatform ShaderPlatform, ITargetPlatform const* TargetPlatform, uint32 CompilationFlags, FComputeKernelResource* Kernel);` — Cache shader resources for a specific compute kernel. This will trigger any required shader compilation.
- L195 _private prototype_ `void ShaderCompileCompletionCallback(FComputeKernelResource const* KernelResource);` — Callback to handle result of kernel shader compilations.
- L240 _private member_ `TArray<FComputeKernelResourceSet> KernelResources;` — Kernel resources stored with the same indexing as the KernelInvocations array.
- L243 _private member_ `TSet<int32> KernelResourceIndicesPendingShaderCompilation;` — Indices of kernels pending shader compilation
- L246 _private member_ `FComputeGraphRenderProxy* RenderProxy = nullptr;` — Render proxy that owns all render thread resources.

#### struct `UComputeGraph::FComputeKernelResourceSet`  
`struct FComputeKernelResourceSet`  
_L204-237_
- desc: Each kernel requires an associated FComputeKernelResource object containing the shader resources. Depending on the context (during serialization, editor, cooked game) there may me more than one object. This structure stores them all.
- L208 _public member_ `TUniquePtr<FComputeKernelResource> KernelResourcesByFeatureLevel[ERHIFeatureLevel::Num];` — Kernel resource objects stored per feature level.
- L216 _public member_ `TArray< TUniquePtr<FComputeKernelResource> > LoadedKernelResources;` — Serialized resources waiting for processing during PostLoad().
- L222 _public prototype_ `void Reset();` — Release all resources.
- L224 _public prototype_ `FComputeKernelResource const* Get() const;` — Get the appropriate kernel resource for rendering.
- L226 _public prototype_ `FComputeKernelResource* GetOrCreate();` — Get the appropriate kernel resource for rendering. Create a new empty resource if one doesn't exist.
- L228 _public prototype_ `void Serialize(FArchive& Ar);` — Serialize the resources including the shader maps.
- L230 _public prototype_ `void ProcessSerializedShaderMaps();` — Apply shader maps found in Serialize(). Call this from PostLoad().
- L232 _public prototype_ `bool CacheInlineShaders();` — Cache inline shader map for rendering. Returns false if no inline shader map was available.
- L235 _public prototype_ `void CancelCompilation();`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeGraphBuilder.h` (Public)


#### struct `FKernelHandle`  
`struct FKernelHandle`  
_L16-19_
- desc: Opaque handle to a kernel added to FComputeGraphBuilder.
- L18 _public member_ `int32 Index = INDEX_NONE;`

#### struct `FInterfaceHandle`  
`struct FInterfaceHandle`  
_L22-25_
- desc: Opaque handle to a data interface added to FComputeGraphBuilder.
- L24 _public member_ `int32 Index = INDEX_NONE;`

#### class `FComputeGraphBuilder`  
`class FComputeGraphBuilder`  
_L32-85_
- desc: Programmatic builder for UComputeGraph. Handles the direct array manipulation and name-matching that are required when directly filling the UComputeGraph properties. Expected to be used as a temporary object to do the build. Passed in UObject pointers aren't GC tracked.
- L35 _public prototype_ `FComputeGraphBuilder() = default;`
- L36 _public prototype_ `FComputeGraphBuilder(const FComputeGraphBuilder&) = delete;`
- L37 _public prototype_ `FComputeGraphBuilder& operator=(const FComputeGraphBuilder&) = delete;`
- L43 _public prototype_ `FKernelHandle AddKernel(UComputeKernelSource* Source, FName Name = NAME_None);` — Add a kernel. Source must outlive the builder (typically owned by a UObject outer). Source will be modified by Build() which resets it's inputs and outputs to the new ones applied by the builder.
- L46 _public prototype_ `FInterfaceHandle AddDataInterface(UComputeDataInterface* Interface, UClass* BindingClass, FName Name = NAME_None);` — Add a data interface. BindingClass is the UObject subclass that will be bound at runtime.
- L49 _public prototype_ `void ConnectInput(FKernelHandle Kernel, FStringView KernelFn, FInterfaceHandle Interface, FStringView InterfaceFn);` — Connect a kernel HLSL input parameter to a data interface read function.
- L52 _public prototype_ `void ConnectOutput(FKernelHandle Kernel, FStringView KernelFn, FInterfaceHandle Interface, FStringView InterfaceFn);` — Connect a kernel HLSL output parameter to a data interface write function.
- L58 _public prototype_ `void Build(UComputeGraph& OutGraph, UObject& Outer) const;` — Apply the built topology to OutGraph, resetting any existing topology first. Outer is used as the UObject outer for the UComputeKernel wrapper objects created internally.
- L83 _private member_ `TArray<FKernelEntry> KernelEntries;`
- L84 _private member_ `TArray<FInterfaceEntry> InterfaceEntries;`

#### struct `FComputeGraphBuilder::FPinEntry`  
`struct FPinEntry`  
_L61-66_
- L63 _public member_ `FString KernelFunctionName;`
- L64 _public member_ `int32 InterfaceIndex = INDEX_NONE;`
- L65 _public member_ `FString InterfaceFunctionName;`

#### struct `FComputeGraphBuilder::FKernelEntry`  
`struct FKernelEntry`  
_L68-74_
- L70 _public member_ `UComputeKernelSource* Source;`
- L71 _public member_ `FName Name;`
- L72 _public member_ `TArray<FPinEntry> Inputs;`
- L73 _public member_ `TArray<FPinEntry> Outputs;`

#### struct `FComputeGraphBuilder::FInterfaceEntry`  
`struct FInterfaceEntry`  
_L76-81_
- L78 _public member_ `UComputeDataInterface* Interface;`
- L79 _public member_ `UClass* BindingClass;`
- L80 _public member_ `FName Name;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeGraphComponent.h` (Public)


#### class `UComputeGraphComponent`  
`class UComputeGraphComponent : public UActorComponent`  
_L16-55_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Category = ComputeFramework, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Component which holds a context for a UComputeGraph. This object creates the graph data providers, and queues the execution.
- L21 _public prototype_ `UComputeGraphComponent();`
- L25 _public prototype_ `void InitializeProvider(int32 InDataInterfaceIndex, UObject* InOutDataProvider);` — `UFUNCTION(BlueprintNativeEvent, Category = "Compute")` — Initialize a Data Provider object for the ComputeGraph.
- L29 _public prototype_ `void QueueExecute();` — `UFUNCTION(BlueprintCallable, Category = "Compute")` — Queue the graph for execution at the next render update.
- L34 _protected member_ `TObjectPtr<UComputeGraph> ComputeGraph = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compute")` — The Compute Graph asset.
- L38 _protected prototype_ `UObject* GetBindingObject(int32 InBindingIndex);` — `UFUNCTION(BlueprintNativeEvent, Category = "Compute")` — Get the binding object for the ComputeGraph.
- L42 _protected member_ `TArray<TObjectPtr<UComputeDataProvider>> DataProviderTemplates;` — `UPROPERTY(EditAnywhere, Category = "Compute", Instanced, NoClear, meta = (ShowOnlyInnerProperties))` — Serialized data provider properties.
- L46 _protected member_ `FComputeGraphInstance ComputeGraphInstance;` — `UPROPERTY()` — The Instance with associated per instance settings.
- L49 _protected prototype_ `void OnRegister() override;`
- L50 _protected prototype_ `void OnUnregister() override;`
- L51 _protected prototype_ `void SendRenderDynamicData_Concurrent() override;`
- L52 _protected prototype_ `void DestroyRenderState_Concurrent() override;`
- L53 _protected function_ `bool ShouldCreateRenderState() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeGraphInstance.h` (Public)


#### struct `FComputeGraphInstance`  
`struct FComputeGraphInstance`  
_L22-82_
- reflection: `USTRUCT()`
- desc: Class to store a set of data provider bindings for UComputeGraph and to enqueue work to the ComputeFramework's compute system.
- L31 _public function_ `void SetGraphSortPriority(uint8 InPriority)` — Set the priority used when sorting work. Kernels in instances with a lower sort prioirty will always be submitted first.
- L37 _public prototype_ `void CreateDataProviders(UComputeGraph* InComputeGraph, int32 InBindingIndex, TObjectPtr<UObject> InBindingObject);` — Create and initialize the Data Provider objects for a single binding of a ComputeGraph. The type of binding object is expected to match the associated Binding on the UComputeGraph.
- L43 _public prototype_ `void InitializeDataProviders(UComputeGraph* InComputeGraph, int32 InBindingIndex, TObjectPtr<UObject> InBindingObject);` — Initialize the Data Provider objects for a single binding of a ComputeGraph. The type of binding object is expected to match the associated Binding on the UComputeGraph.
- L46 _public prototype_ `void ResetDataProviders();` — Clear the state within the Data Provider objects.
- L49 _public prototype_ `void DestroyDataProviders();` — Create the Data Provider objects.
- L52 _public function_ `TArray< TObjectPtr<UComputeDataProvider> >& GetDataProviders()` — Get the Data Provider objects.
- L55 _public function_ `int GetNumDataProviders() const` — Get the number of Data Provider objects.
- L58 _public prototype_ `bool EnqueueWork( UComputeGraph* InComputeGraph, FSceneInterface const* InScene, FName InExecutionGroupName, FName InOwnerName, FSimpleDelegate InFallbackDelegate, UObject* InOwnerPointer = nullptr, uint8 InGraphSortPriorityOffset = 0 #if HAS_GPU_STATS , TArray<TPromise<FComputeFrameworkKernelTiming>> InKernelTimingPromises = {} #endif );` — Enqueue the ComputeGraph work.
- L71 _public function_ `void SetRenderCapturesEnabled(bool bInEnable)`
- L76 _private member_ `TArray< TObjectPtr<UComputeDataProvider> > DataProviders;` — `UPROPERTY(Transient)` — The currently bound Data Provider objects.
- L79 _private member_ `uint8 GraphSortPriority = 0;` — Priority used when sorting work.
- L81 _private member_ `bool bEnableRenderCaptures = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeKernel.h` (Public)


#### enum `EComputeKernelFlags`  
`enum class EComputeKernelFlags : uint32`  
_L14-34_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Flags that convey kernel behavior to aid compilation/optimizations.
- L21 _public enumerator_ `IsDefaultKernel = 1 << 0` — Default implies that this kernel must be compiled before the system is functional. It also implies that this will be compiled synchronously. Other than a pass through kernel, default shouldn't be used.
- L28 _public enumerator_ `IsolatedMemoryWrites = 1 << 1` — Promise from the author that all memory writes will be unique per shader dispatch thread. i.e. ThreadX will be the only thread to write to MemoryY, thus no synchronization is necessary by the compute graph.
- L33 _public enumerator_ `TriggerRenderCapture = 1 << 2` — Trigger render capture when this kernel dispatches, for debugging/testing purposes.

#### class `UComputeKernel`  
`class UComputeKernel : public UObject`  
_L39-61_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Object))`
- inherits: `UObject`
- desc: Base class representing a kernel that will be run as a shader on the GPU.
- L49 _public member_ `TObjectPtr<UComputeKernelSource> KernelSource = nullptr;` — `UPROPERTY(EditAnywhere, AssetRegistrySearchable, meta = (ShowOnlyInnerProperties), Category = "Kernel")` — The compute kernel source asset. A kernel's source may be authored by different mechanisms; e.g. HLSL text, VPL graph, ML Meta Lang, etc
- L53 _public member_ `int32 KernelFlags = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "/Script/ComputeFramework.EComputeKernelFlags"), Category = "Kernel")` — Specifying certain memory access flags allows for optimizations such as kernel fusing.
- L58 _protected prototype_ `void PostLoad() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`
- L35 _prototype_ `ENUM_CLASS_FLAGS(EComputeKernelFlags);`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeKernelCompileResult.h` (Public)


#### struct `FComputeKernelCompileMessage`  
`struct FComputeKernelCompileMessage`  
_L8-31_
- desc: Struct containing a message returned by shader compilation.
- L18 _public member_ `EMessageType Type = EMessageType::None;`
- L19 _public member_ `FString Text;`
- L20 _public member_ `FString VirtualFilePath;`
- L21 _public member_ `FString RealFilePath;`
- L22 _public member_ `int32 Line = -1;`
- L23 _public member_ `int32 ColumnStart = -1;`
- L24 _public member_ `int32 ColumnEnd = -1;`
- L27 _public function_ `bool operator==(FComputeKernelCompileMessage const& Rhs) const` — Equality operator used to deduplicate messages.

#### enum `FComputeKernelCompileMessage::EMessageType`  
`enum class EMessageType`  
_L10-16_
- L12 _public enumerator_ `None`
- L13 _public enumerator_ `Info`
- L14 _public enumerator_ `Warning`
- L15 _public enumerator_ `Error`

#### struct `FComputeKernelCompileResults`  
`struct FComputeKernelCompileResults`  
_L34-37_
- desc: Struct containing all of the messages returned by shader compilation.
- L36 _public member_ `TArray<FComputeKernelCompileMessage> Messages;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeKernelPermutationSet.h` (Public)


#### struct `FComputeKernelPermutationBool`  
`struct FComputeKernelPermutationBool`  
_L8-25_
- reflection: `USTRUCT()`
- L13 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Permutation Options")`
- L16 _public member_ `bool Value = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Permutation Options")`
- L18 _public prototype_ `FComputeKernelPermutationBool() = default;`
- L20 _public function_ `explicit FComputeKernelPermutationBool(FString InName, bool InValue) : Name(MoveTemp(InName)) , Value(InValue)`

#### struct `FComputeKernelPermutationSet`  
`struct FComputeKernelPermutationSet`  
_L28-34_
- reflection: `USTRUCT()`
- L33 _public member_ `TArray<FComputeKernelPermutationBool> BooleanOptions;` — `UPROPERTY(EditDefaultsOnly, EditFixedSize, meta = (EditFixedOrder), Category = "Permutation Options")`

#### struct `FComputeKernelDefinition`  
`struct FComputeKernelDefinition`  
_L37-55_
- reflection: `USTRUCT()`
- L43 _public member_ `FString Symbol;` — `UPROPERTY(VisibleAnywhere, Category = "Kernel")`
- L46 _public member_ `FString Define;` — `UPROPERTY(EditDefaultsOnly, Category = "Kernel")`
- L48 _public prototype_ `FComputeKernelDefinition() = default;`
- L50 _public function_ `explicit FComputeKernelDefinition(FString InSymbol, FString InDefine = FString()) : Symbol(MoveTemp(InSymbol)) , Define(MoveTemp(InDefine))`

#### struct `FComputeKernelDefinitionSet`  
`struct FComputeKernelDefinitionSet`  
_L58-65_
- reflection: `USTRUCT()`
- L64 _public member_ `TArray<FComputeKernelDefinition> Defines;` — `UPROPERTY(EditDefaultsOnly, EditFixedSize, meta = (EditFixedOrder), Category = "Permutation Options")`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeKernelPermutationVector.h` (Public)


#### struct `FComputeKernelPermutationVector`  
`struct FComputeKernelPermutationVector`  
_L12-44_
- reflection: `USTRUCT()`
- L29 _public member_ `TMap<FString, uint32> Permutations;` — `UPROPERTY()` — Map from permutation define name to packed FPermutaionBits value.
- L33 _public member_ `uint32 BitCount = 0;` — `UPROPERTY()` — Number of permutation bits allocated.
- L36 _public prototype_ `void AddPermutation(FString const& Name, uint32 NumValues);` — Add a permutation to the vector.
- L39 _public prototype_ `void AddPermutationSet(struct FComputeKernelPermutationSet const& PermutationSet);` — Add a permutation to the vector.
- L42 _public prototype_ `uint32 GetPermutationBits(FString const& Name, uint32 Value) const;` — Get the permutation bits for a given Name and Value.
- L43 _public prototype_ `uint32 GetPermutationBits(FString const& Name, uint32 PrecomputedNameHash, uint32 Value) const;`

#### union `FComputeKernelPermutationVector::FPermutationBits`  
`union FPermutationBits`  
_L16-25_
- L18 _public member_ `uint32 PackedValue = 0;`

#### struct `FComputeKernelPermutationVector::FPermutationBits::(anonymous)`  
``  
_L21-24_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`
- L22 _member_ `uint16 BitIndex;` (scope `FComputeKernelPermutationVector::FPermutationBits::__anonc22ece150108`)
- L23 _member_ `uint16 NumValues;` (scope `FComputeKernelPermutationVector::FPermutationBits::__anonc22ece150108`)

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeKernelSource.h` (Public)


#### class `UComputeKernelSource`  
`class UComputeKernelSource : public UObject`  
_L18-57_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Class representing the source for a UComputeKernel We derive from this for each authoring mechanism. (HLSL text, VPL graph, ML Meta Lang, etc.)
- L25 _public prototype_ `virtual FString GetSource() const PURE_VIRTUAL(UComputeKernelSource::GetSource, return {};);` — Get kernel source code ready for HLSL compilation.
- L30 _public member_ `FString EntryPoint;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Kernel")` — Kernel entry point.
- L34 _public member_ `FIntVector GroupSize = FIntVector(64, 1, 1);` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Kernel")` — Kernel group size.
- L39 _public member_ `FComputeKernelPermutationSet PermutationSet;` — `UPROPERTY(VisibleAnywhere, meta = (ShowOnlyInnerProperties), Category = "Kernel")` — Base permutations exposed by the kernel. These will be extended by further permutations declared in any linked data providers.
- L43 _public member_ `FComputeKernelDefinitionSet DefinitionsSet;` — `UPROPERTY(VisibleAnywhere, meta = (ShowOnlyInnerProperties), Category = "Kernel")` — Base environment defines for kernel compilation. These will be extended by further defines declared in any linked data providers.
- L47 _public member_ `TArray<TObjectPtr<UComputeSource>> AdditionalSources;` — `UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties), Category = "External")` — An array of additional independent source assets that the kernel source depends on.
- L51 _public member_ `TArray<FShaderFunctionDefinition> ExternalInputs;` — `UPROPERTY(VisibleAnywhere, EditFixedSize, Category = "External")` — Named external inputs for the kernel. These must be fulfilled by linked data providers.
- L55 _public member_ `TArray<FShaderFunctionDefinition> ExternalOutputs;` — `UPROPERTY(VisibleAnywhere, EditFixedSize, Category = "External")` — Named external outputs for the kernel. These must be fulfilled by linked data providers.

#### class `UComputeKernelSourceWithText`  
`class UComputeKernelSourceWithText final : public UComputeKernelSource`  
_L61-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UComputeKernelSource`
- desc: Simple concrete implementation of UComputeKernelSource with contained source text property.
- L69 _public member_ `FString SourceText;` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — Kernel source text.
- L74 _public prototype_ `virtual FString GetSource() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeMetadataBuilder.h` (Public)


#### struct `ComputeFramework::FTypeMetaData`  
`struct FTypeMetaData`  
_L18-28_
- desc: Helper struct to convert shader value type to shader parameter metadata
- L20 _public prototype_ `FTypeMetaData(FShaderValueTypeHandle InType);`
- L21 _public prototype_ `FTypeMetaData(const FTypeMetaData& InOther) = delete;`
- L22 _public prototype_ `FTypeMetaData& operator=(const FTypeMetaData& InOther) = delete;`
- L23 _public prototype_ `~FTypeMetaData();`
- L25 _public member_ `const FShaderParametersMetadata* Metadata;`
- L27 _public member_ `TArray<FShaderParametersMetadata*> AllocatedMetadatas;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`
- L13 _namespace_ `namespace ComputeFramework`
- L15 _prototype_ `void AddParamForType(FShaderParametersMetadataBuilder& InOutBuilder, TCHAR const* InName, FShaderValueTypeHandle const& InValueType, TArray<FShaderParametersMetadata*>& OutNestedStructs);` (scope `ComputeFramework`)

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ComputeSource.h` (Public)


#### class `UComputeSource`  
`class UComputeSource : public UObject`  
_L13-27_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Class representing some source for inclusion in a UComputeKernel. We derive from this for each authoring mechanism. (HLSL text, VPL graph, ML Meta Lang, etc.)
- L19 _public function_ `virtual FString GetSource() const` — Get source code ready for HLSL compilation.
- L21 _public function_ `virtual FString GetVirtualPath() const` — Get virtual file path for the source code. This will be the file name shown in any compilation errors.
- L26 _public member_ `TArray<TObjectPtr<UComputeSource>> AdditionalSources;` — `UPROPERTY(EditAnywhere, Category = Source)` — Array of additional source objects. This allows us to specify source dependencies.

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/IComputeFrameworkModule.h` (Public)


#### class `IComputeFrameworkModule`  
`class IComputeFrameworkModule : public IModuleInterface`  
_L8-11_
- inherits: `IModuleInterface`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ShaderParamTypeDefinition.h` (Public)


#### enum `EShaderFundamentalType`  
`enum class EShaderFundamentalType : uint8`  
_L17-25_
- reflection: `UENUM()`
- desc: The base types of data that shaders can consume/expose
- L19 _public enumerator_ `Bool = 0`
- L20 _public enumerator_ `Int = 1`
- L21 _public enumerator_ `Uint = 2`
- L22 _public enumerator_ `Float = 3`
- L23 _public enumerator_ `Struct = 4`
- L24 _public enumerator_ `None = 255u`

#### enum `EShaderFundamentalDimensionType`  
`enum class EShaderFundamentalDimensionType : uint8`  
_L33-38_
- reflection: `UENUM()`
- desc: Shader types can then be in the form of a scalar, vector, matrix. e.g Scalar: float a; 	Vector: float3 n; 		Matrix: float3x4 WVP; Note: float b[5]; is still considered scalar. It is an array of scalars.
- L35 _public enumerator_ `Scalar`
- L36 _public enumerator_ `Vector`
- L37 _public enumerator_ `Matrix`

#### enum `EShaderParamBindingType`  
`enum class EShaderParamBindingType : uint8`  
_L42-48_
- reflection: `UENUM()`
- desc: Describes how the shader parameters are bound.
- L44 _public enumerator_ `None`
- L45 _public enumerator_ `ConstantParameter`
- L46 _public enumerator_ `ReadOnlyResource` — SRV, treated as Inputs
- L47 _public enumerator_ `ReadWriteResource` — UAV, treated as Outputs

#### enum `EShaderResourceType`  
`enum class EShaderResourceType : uint8`  
_L52-62_
- reflection: `UENUM()`
- L54 _public enumerator_ `None`
- L55 _public enumerator_ `Texture1D`
- L56 _public enumerator_ `Texture2D`
- L57 _public enumerator_ `Texture3D`
- L58 _public enumerator_ `TextureCube`
- L59 _public enumerator_ `Buffer`
- L60 _public enumerator_ `StructuredBuffer`
- L61 _public enumerator_ `ByteAddressBuffer`

#### enum `EShaderParamModifier`  
`enum class EShaderParamModifier : uint8`  
_L65-71_
- reflection: `UENUM()`
- L67 _public enumerator_ `None`
- L68 _public enumerator_ `In`
- L69 _public enumerator_ `Out`
- L70 _public enumerator_ `InOut`

#### struct `FShaderValueTypeHandle`  
`struct FShaderValueTypeHandle`  
_L75-112_
- reflection: `USTRUCT()`
- L79 _public member_ `const FShaderValueType *ValueTypePtr = nullptr;`
- L81 _public function_ `bool IsValid() const`
- L86 _public function_ `explicit operator bool() const`
- L91 _public function_ `const FShaderValueType *operator->() const`
- L96 _public function_ `const FShaderValueType &operator*() const`
- L101 _public function_ `bool operator==(const FShaderValueTypeHandle &InOther) const`
- L106 _public function_ `bool operator!=(const FShaderValueTypeHandle &InOther) const`
- L111 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FShaderValueTypeHandle> : TStructOpsTypeTraitsBase2<FShaderValueTypeHandle>`  
_L116-119_
- inherits: `TStructOpsTypeTraitsBase2<FShaderValueTypeHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L118-118_

#### struct `FArrayShaderValue`  
`struct FArrayShaderValue`  
_L124-130_
- reflection: `USTRUCT()`
- L129 _public member_ `TArray<uint8> ArrayOfValues;` — `UPROPERTY()`

#### struct `FShaderValueContainer`  
`struct FShaderValueContainer`  
_L133-165_
- reflection: `USTRUCT()`
- L138 _public member_ `TArray<uint8> ShaderValue;` — `UPROPERTY()`
- L141 _public member_ `TArray<FArrayShaderValue> ArrayList;` — `UPROPERTY()`
- L143 _public prototype_ `FShaderValueContainer() = default;`
- L145 _public function_ `explicit FShaderValueContainer(int32 InShaderValueSize, int32 InNumArrays)`
- L151 _public function_ `static bool IsSameType(const FShaderValueContainer& A, const FShaderValueContainer& B)`
- L156 _public function_ `bool IsValid() const`
- L160 _public function_ `void Reset()`

#### struct `FShaderValueContainerView`  
`struct FShaderValueContainerView`  
_L167-184_
- L169 _public member_ `TArrayView<uint8> ShaderValue;`
- L170 _public member_ `TArrayView<FArrayShaderValue> ArrayList;`
- L172 _public function_ `FShaderValueContainerView( TArrayView<uint8> InShaderValue, TArrayView<FArrayShaderValue> InArrayList) : ShaderValue(InShaderValue), ArrayList(InArrayList)`
- L178 _public function_ `FShaderValueContainerView(TArrayView<uint8> InShaderValue) : ShaderValue(InShaderValue)`
- L181 _public function_ `FShaderValueContainerView(FShaderValueContainer& InValue) : ShaderValue(InValue.ShaderValue), ArrayList(InValue.ArrayList)`

#### struct `FShaderValueType`  
`struct FShaderValueType`  
_L188-298_
- reflection: `USTRUCT()`
- L215 _public prototype_ `static FShaderValueTypeHandle Get(EShaderFundamentalType InType);` — Returns a scalar value type. If the fundamental type given is invalid for scalar values (e.g. struct), then this function returns a nullptr.
- L221 _public prototype_ `static FShaderValueTypeHandle Get(EShaderFundamentalType InType, int32 InElemCount);` — Returns a vector value type. InElemCount can be any value between 1-4. If the type given is invalid for scalar values (e.g. struct) or InElemCount is out of range, then this function returns a nullptr.
- L224 _public prototype_ `static FShaderValueTypeHandle Get(EShaderFundamentalType InType, int32 InRowCount, int32 InColumnCount);` — Constructor for vector values. InElemCount can be any value between 1-4
- L227 _public prototype_ `static FShaderValueTypeHandle Get(FName InName, std::initializer_list<FStructElement> InStructElements);` — Constructor for struct types
- L230 _public prototype_ `static FShaderValueTypeHandle Get(FName InName, const TArray<FStructElement>& InStructElements);` — Constructor for struct types
- L233 _public prototype_ `static FShaderValueTypeHandle MakeDynamicArrayType(const FShaderValueTypeHandle& InElementType);` — Construct an array type from an existing type
- L238 _public prototype_ `static FShaderValueTypeHandle FromString(const FString& InTypeDecl);` — Parses the given string section and tries to convert to a shader value type. NOTE: Does not work on structs.
- L241 _public prototype_ `bool operator==(const FShaderValueType &InOtherType) const;` — Returns true if this type and the other type are exactly equal.
- L244 _public function_ `bool operator!=(const FShaderValueType& InOtherType) const` — Returns true if this type and the other type are not equal.
- L253 _public prototype_ `FString ToString(const FName& InStructTypeNameOverride = {}) const;` — Returns the type name as a string (e.g. 'vector2', 'matrix2x3' or 'struct_name') for use in variable declarations.
- L256 _public prototype_ `FString GetTypeDeclaration(const TMap<FName, FName>& InNamesToReplace = {}, bool bCommentPaddings = false) const;` — Returns the type declaration if this type is a struct, or the empty string if not.
- L259 _public prototype_ `TArray<FShaderValueTypeHandle> GetMemberStructTypes() const;` — Returns the all the struct types used in this type if the type is a struct.
- L264 _public prototype_ `int32 GetResourceElementSize() const;` — Returns the size in bytes required to hold one element of this type using HLSL sizing (which may be different from packed sizing in C++).
- L269 _public prototype_ `FString GetZeroValueAsString() const;` — Returns a zero value for the type as a string, suitable for use as a constant in HLSL code.
- L272 _public member_ `EShaderFundamentalType Type = EShaderFundamentalType::Bool;` — `UPROPERTY()`
- L275 _public member_ `EShaderFundamentalDimensionType DimensionType = EShaderFundamentalDimensionType::Scalar;` — `UPROPERTY()`
- L289 _public member_ `FName Name;` — `UPROPERTY()`
- L292 _public member_ `bool bIsDynamicArray = false;` — `UPROPERTY()`
- L294 _public member_ `TArray<FStructElement> StructElements;`
- L297 _private prototype_ `static FShaderValueTypeHandle GetOrCreate(FShaderValueType &&InValueType);`

#### struct `FShaderValueType::FStructElement`  
`struct FStructElement`  
_L193-210_
- desc: A simple container representing a single, named element in a shader value struct.
- L195 _public prototype_ `FStructElement() = default;`
- L196 _public function_ `FStructElement(FName InName, FShaderValueTypeHandle InType) : Name(InName), Type(InType)`
- L199 _public function_ `bool operator==(const FStructElement &InOther) const`
- L204 _public function_ `bool operator!=(const FStructElement& InOther) const`
- L208 _public member_ `FName Name;`
- L209 _public member_ `FShaderValueTypeHandle Type;`

#### union `FShaderValueType::(anonymous)`  
``  
_L278-286_

#### struct `FShaderValueType::__anonc98aa51f020a::(anonymous)`  
``  
_L282-285_

#### struct `FShaderParamTypeDefinition`  
`struct FShaderParamTypeDefinition`  
_L308-410_
- reflection: `USTRUCT()`
- desc: Fully describes the name and type of a parameter a shader exposes.
- L313 _public prototype_ `static EShaderFundamentalType ParseFundamental( const FString& Str );`
- L317 _public prototype_ `static EShaderFundamentalDimensionType ParseDimension( const FString& Str );`
- L321 _public prototype_ `static uint8 ParseVectorDimension( const FString& Str );`
- L325 _public prototype_ `static FIntVector2 ParseMatrixDimension( const FString& Str );`
- L329 _public prototype_ `static EShaderResourceType ParseResource( const FString& Str );`
- L335 _public member_ `FString TypeDeclaration;` — `UPROPERTY(VisibleAnywhere, Category = "Kernel")`
- L338 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "Kernel")`
- L342 _public member_ `FShaderValueTypeHandle ValueType;` — `UPROPERTY()` — The value type for this definition.
- L345 _public member_ `uint16 ArrayElementCount = 0;` — `UPROPERTY()` — 0 indicates not an array. >= 1 indicates an array
- L348 _public member_ `EShaderParamBindingType BindingType = EShaderParamBindingType::None;` — `UPROPERTY()`
- L351 _public member_ `EShaderResourceType ResourceType = EShaderResourceType::None;` — `UPROPERTY()`
- L354 _public member_ `EShaderParamModifier Modifier = EShaderParamModifier::None;` — `UPROPERTY()`
- L356 _public function_ `bool IsAnyBufferType() const`
- L364 _public function_ `bool IsAnyTextureType() const`
- L374 _public function_ `bool IsValid() const` — Determines if the type definition is valid according to HLSL rules.
- L408 _public prototype_ `void ResetTypeDeclaration( );`

#### struct `FShaderFunctionDefinition`  
`struct FShaderFunctionDefinition`  
_L415-438_
- reflection: `USTRUCT()`
- desc: Describes a shader function signature.
- L422 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Kernel")` — Function name.
- L426 _public member_ `TArray<FShaderParamTypeDefinition> ParamTypes;` — `UPROPERTY(VisibleAnywhere, Category = "Kernel")` — Function parameter types.
- L430 _public member_ `bool bHasReturnType = false;` — `UPROPERTY()` — If set to true then the first element of ParamTypes is the return type. Otherwise return type is void.
- L433 _public prototype_ `FShaderFunctionDefinition& SetName(FString InName);`
- L434 _public prototype_ `FShaderFunctionDefinition& AddParam(FShaderValueTypeHandle InValueType, EShaderParamModifier InModifier = EShaderParamModifier::None);`
- L435 _public prototype_ `FShaderFunctionDefinition& AddParam(EShaderFundamentalType InType, int32 InRowCount = 0, int32 InColumnCount = 0, EShaderParamModifier InModifier = EShaderParamModifier::None);`
- L436 _public prototype_ `FShaderFunctionDefinition& AddReturnType(FShaderValueTypeHandle InValueType);`
- L437 _public prototype_ `FShaderFunctionDefinition& AddReturnType(EShaderFundamentalType InType, int32 InRowCount = 0, int32 InColumnCount = 0);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`
- L114 _prototype_ `FArchive& operator<<(FArchive& InArchive, FShaderValueTypeHandle& InHandle);`
- L118 _enumerator_ `enum { WithSerializer = true, WithIdenticalViaEquality = true, WithCopy = false };` (scope `TStructOpsTypeTraits::__anonc98aa51f0103`)
- L118 _enumerator_ `enum { WithSerializer = true, WithIdenticalViaEquality = true, WithCopy = false };` (scope `TStructOpsTypeTraits::__anonc98aa51f0103`)
- L118 _enumerator_ `enum { WithSerializer = true, WithIdenticalViaEquality = true, WithCopy = false };` (scope `TStructOpsTypeTraits::__anonc98aa51f0103`)
- L279 _member_ `uint8 VectorElemCount;` (scope `FShaderValueType::__anonc98aa51f020a`)
- L283 _member_ `uint8 MatrixRowCount;` (scope `FShaderValueType::__anonc98aa51f020a::__anonc98aa51f0308`)
- L284 _member_ `uint8 MatrixColumnCount;` (scope `FShaderValueType::__anonc98aa51f020a::__anonc98aa51f0308`)
- L304 _prototype_ `uint32 GetTypeHash(const FShaderValueType& InShaderValueType);` — A hashing function to allow the FShaderValueType class to be used with hashing containers (e.g. TSet or TMap).

### `Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Public/ComputeFramework/ShaderParameterMetadataAllocation.h` (Public)


#### struct `FShaderParametersMetadataAllocations`  
`struct FShaderParametersMetadataAllocations`  
_L18-28_
- desc: When we build FShaderParametersMetadata at runtime it can require that we allocate additional data referenced but not owned by the FShaderParametersMetadata. This structure tracks the allocations, and should be released only after we are done with the associated FShaderParametersMetadata.
- L21 _public member_ `TArray<FShaderParametersMetadata*> ShaderParameterMetadatas;` — Allocated metadata. Should include the parent metadata allocation.
- L23 _public member_ `TChunkedArray<FString, 512> Names;` — Allocated name dictionary.
- L25 _public prototype_ `FShaderParametersMetadataAllocations() = default;`
- L26 _public prototype_ `FShaderParametersMetadataAllocations(FShaderParametersMetadataAllocations& Other) = delete;`
- L27 _public prototype_ `~FShaderParametersMetadataAllocations();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPUTEFRAMEWORK_API`
