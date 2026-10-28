# Plugins / UAF

- module root: `Plugins/Experimental/UAF/UAF/Source/UAF`
- headers: 166; symbols: 3750
- symbol kinds: class=60, delegate=19, enum=40, enumerator=86, externvar=2, function=826, macro=100, member=620, namespace=322, prototype=1193, struct=271, typedef=207, variable=4
- DynamicallyLoadedModuleNames: UAFUncookedOnly
- PrivateDependencyModuleNames: AssetRegistry, LiveCoding, RigVMDeveloper, Slate, SlateCore, ToolMenus, TraceLog, UniversalObjectLocator, UnrealEd
- PrivateIncludePathModuleNames: UAFUncookedOnly
- PublicDependencyModuleNames: Core, CoreUObject, Engine, HierarchyTableAnimationRuntime, HierarchyTableRuntime, PropertyBindingUtils, RenderCore, RewindDebuggerRuntimeInterface, RigVM

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/AnimNextConfig.h` (Internal)


#### class `UAnimNextConfig`  
`class UAnimNextConfig : public UObject`  
_L10-24_
- reflection: `UCLASS(MinimalAPI, Config=AnimNext)`
- inherits: `UObject`
- L17 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L23 _public prototype_ `static TArray<UClass*> GetAllowedAssetClasses();` — `UFUNCTION()` — Gets all allowed asset classes that users can reference that map via GetGraphFromObject

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/AnimNextDebugDraw.h` (Internal)


#### class `UE::UAF::Debug::FAnimNextDebugSceneProxy`  
`class FAnimNextDebugSceneProxy : public FPrimitiveSceneProxy`  
_L28-42_
- inherits: `FPrimitiveSceneProxy`
- desc: Simple scene proxy to perform debug drawing with
- L30 _private prototype_ `explicit FAnimNextDebugSceneProxy(const FPrimitiveSceneProxyDesc& InProxyDesc);`
- L32 _private prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L33 _private prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L34 _private prototype_ `virtual uint32 GetMemoryFootprint() const override;`
- L35 _private prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L37 _private member_ `FRigVMDrawInterface DrawInterface;`
- L38 _private member_ `bool bIsEnabled = false;`

#### struct `UE::UAF::Debug::FDebugDraw`  
`struct FDebugDraw`  
_L45-95_
- desc: Render data for debug drawing
- L48 _public prototype_ `explicit FDebugDraw(UObject* InOwner);`
- L51 _public prototype_ `void Draw();` — Draw any debug items in DrawInterface
- L55 _public prototype_ `void SetEnabled(bool bInIsEnabled);` — Enable/disable debug drawing Enqueues a render command to update the enabled state
- L68 _private prototype_ `void CalcBounds();`
- L71 _private prototype_ `void RemovePrimitive();` — Unregister the primitive from the RT
- L73 _private member_ `FCustomSceneProxyDesc SceneProxyDesc;`
- L74 _private member_ `FPrimitiveSceneDesc SceneDesc;`
- L75 _private member_ `FPrimitiveSceneInfoData* SceneInfoData = nullptr;`
- L76 _private member_ `FAnimNextDebugSceneProxy* SceneProxy = nullptr;`
- L78 _private member_ `FSceneInterface* Scene = nullptr;`
- L81 _private member_ `FRigVMDrawInterface DrawInterface;` — Anim thread accessible draw interface
- L84 _private member_ `bool bIsEnabled = false;` — Anim thread accessible enabled flag
- L87 _private member_ `bool bIsRegistered = false;` — Flag indicating whether we are registered with the RT
- L90 _private member_ `FTransactionallySafeRWLock Lock;` — Lock to prevent unregistration during WT drawing

#### struct `UE::UAF::Debug::FDebugDraw::FCustomSceneProxyDesc`  
`struct FCustomSceneProxyDesc : FPrimitiveSceneProxyDesc`  
_L58-66_
- inherits: `FPrimitiveSceneProxyDesc`
- L60 _public prototype_ `explicit FCustomSceneProxyDesc(UObject* InOwner);`
- L63 _public function_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override` — FPrimitiveSceneProxyDesc interface
- L65 _public member_ `FCustomPrimitiveData DummyCustomPrimitiveData;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace Debug` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/AnimNextExecuteContext.h` (Internal)


#### struct `FAnimNextExecuteContext`  
`struct FAnimNextExecuteContext : public FRigVMExecuteContext`  
_L22-77_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMExecuteContext`
- L26 _public prototype_ `FAnimNextExecuteContext() = default;`
- L28 _public function_ `virtual void Copy(const FRigVMExecuteContext* InOtherContext) override`
- L36 _public function_ `virtual void Log(const FRigVMLogSettings& InLogSettings, const FString& InMessage) const override`
- L61 _public function_ `template<typename ContextType> const ContextType& GetContextData() const` — Get the context data as the specified type. This will assert if the type differs from the last call to SetContextData.
- L68 _protected function_ `void SetContextData(TConstStructView<FUAFScriptContextData> InContextData)` — Setup the context data to the specified type
- L74 _protected member_ `TConstStructView<FUAFScriptContextData> ContextData;` — Context data for this execution

#### struct `UE::UAF::FScopedExecuteContextData`  
`struct FScopedExecuteContextData`  
_L83-99_
- desc: Helper for applying context data prior to RigVM execution
- L85 _public prototype_ `FScopedExecuteContextData() = delete;`
- L87 _public function_ `explicit FScopedExecuteContextData(FAnimNextExecuteContext& InContext, TConstStructView<FUAFScriptContextData> InContextData) : Context(InContext)`
- L93 _public function_ `~FScopedExecuteContextData()`
- L98 _public member_ `FAnimNextExecuteContext& Context;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L79 _namespace_ `namespace UE`
- L79 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/AnimNextModuleImpl.h` (Internal)


#### class `UE::UAF::FAnimNextModuleImpl`  
`class FAnimNextModuleImpl : public IModuleInterface`  
_L12-24_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `void RegisterAssets();`
- L21 _private prototype_ `void UnregisterAssets();`
- L23 _private member_ `FTopLevelAssetPath UAFSystemClassPath;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/AnimNextPool.h` (Internal)


#### class `UE::UAF::TPool`  
`template<typename ElementType> class TPool`  
_L14-234_
- L23 _private member_ `TPagedArray<FEntry> Entries;`
- L26 _private member_ `uint32 NumAllocatedEntries = 0;` — The number of active entries allocasted from the pool
- L28 _private member_ `uint32 HeadFreeIndex = MAX_uint32;`
- L31 _private member_ `static inline uint32 SerialNumber = 0;` — Serial number is global to reduce collisions with multiple pools
- L35 _public function_ `template<typename... ArgsType> TPoolHandle<ElementType> Emplace(ArgsType&&... InArgs)`
- L71 _public function_ `void Release(TPoolHandle<ElementType> InHandle, EAllowShrinking InAllowShrinking = EAllowShrinking::Default)`
- L94 _public function_ `ElementType& Get(TPoolHandle<ElementType> InHandle)`
- L100 _public function_ `const ElementType& Get(TPoolHandle<ElementType> InHandle) const`
- L106 _public function_ `ElementType* TryGet(TPoolHandle<ElementType> InHandle)`
- L115 _public function_ `const ElementType* TryGet(TPoolHandle<ElementType> InHandle) const`
- L124 _public function_ `uint32 Num() const`
- L129 _public function_ `bool IsValidHandle(TPoolHandle<ElementType> InHandle) const`
- L216 _public typedef_ `typedef TIterator< ElementType, false> RangedForIteratorType;`
- L217 _public typedef_ `typedef TIterator<const ElementType, false> RangedForConstIteratorType;`
- L218 _public typedef_ `typedef TIterator< ElementType, true > RangedForReverseIteratorType;`
- L219 _public typedef_ `typedef TIterator<const ElementType, true > RangedForConstReverseIteratorType;`
- L226 _public function_ `FORCEINLINE RangedForIteratorType begin ()`
- L227 _public function_ `FORCEINLINE RangedForConstIteratorType begin () const`
- L228 _public function_ `FORCEINLINE RangedForIteratorType end ()`
- L229 _public function_ `FORCEINLINE RangedForConstIteratorType end () const`
- L230 _public function_ `FORCEINLINE RangedForReverseIteratorType rbegin()`
- L231 _public function_ `FORCEINLINE RangedForConstReverseIteratorType rbegin() const`
- L232 _public function_ `FORCEINLINE RangedForReverseIteratorType rend ()`
- L233 _public function_ `FORCEINLINE RangedForConstReverseIteratorType rend () const`

#### struct `UE::UAF::TPool::FEntry`  
`struct FEntry`  
_L17-21_
- L19 _public member_ `TVariant<ElementType, uint32> ValueOrNextFreeIndex;`
- L20 _public member_ `uint32 SerialNumber = 0;`

#### class `UE::UAF::TPool::TIterator`  
`template<typename IteratorElementType, bool bReverse = false> class TIterator`  
_L135-214_
- L138 _public function_ `TIterator(TPool<IteratorElementType>& InPool, uint32 StartIndex = 0) : Pool(InPool) , Index(StartIndex)`
- L149 _public function_ `TIterator& operator++()` — Advances iterator to the next valid element in the pool.
- L154 _public function_ `TIterator operator++(int)`
- L161 _public function_ `FORCEINLINE IteratorElementType& operator* () const`
- L166 _public function_ `FORCEINLINE IteratorElementType* operator->() const`
- L172 _public function_ `FORCEINLINE explicit operator bool() const` — conversion to "bool" returning true if the iterator has not reached the last element.
- L177 _public function_ `FORCEINLINE bool operator==(const TIterator& Rhs) const`
- L182 _public function_ `FORCEINLINE bool operator!=(const TIterator& Rhs) const`
- L188 _private function_ `void Increment()`
- L212 _private member_ `TPool<IteratorElementType>& Pool;`
- L213 _private member_ `uint32 Index;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/AnimNextRigVMFunctionData.h` (Internal)


#### struct `FAnimNextRigVMFunctionData`  
`struct FAnimNextRigVMFunctionData`  
_L8-27_
- reflection: `USTRUCT()`
- L14 _public member_ `FGuid FunctionGuid;` — `UPROPERTY()` — Stable GUID identifying the function (survives renames). This corresponds to the RigVM function's GUID
- L18 _public member_ `FName Name;` — `UPROPERTY()` — The name of the function
- L22 _public member_ `FName EventName;` — `UPROPERTY()` — The mangled event name of the function
- L26 _public member_ `TArray<int32> ArgIndices;` — `UPROPERTY()` — Indices into RigVM external variables for each arg

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Component/SkinnedMeshComponentExtensions.h` (Internal)


#### struct `UE::Anim::FSkinnedMeshComponentExtensions`  
`struct FSkinnedMeshComponentExtensions`  
_L15-22_
- desc: Extensions to skinned meshes that are not public API yet
- L18 _public prototype_ `static void CompleteAndDispatch( USkinnedMeshComponent* InComponent, const UE::UAF::FLODPoseHeap& InLODPose, TUniqueFunction<void(USkinnedMeshComponent*)>&& InGameThreadCallback);` — Converts local to component space, flips buffers, updates bounds and dispatches to renderer

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Anim` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/CrashReporter/CrashReporterHandler.h` (Internal)


#### struct `UE::UAF::FCrashReporterHandler`  
`struct FCrashReporterHandler`  
_L12-16_
- L14 _public prototype_ `static void Register();`
- L15 _public prototype_ `static void Unregister();`

#### class `UE::UAF::FCrashReporterScope`  
`class FCrashReporterScope`  
_L18-31_
- L21 _public prototype_ `explicit FCrashReporterScope(TNotNull<const UObject*> InOwner, TNotNull<const UObject*> ObjectOfInterest, FName Context);`
- L22 _public prototype_ `~FCrashReporterScope();`
- L24 _public prototype_ `FCrashReporterScope() = delete;`
- L25 _public prototype_ `FCrashReporterScope(const FCrashReporterScope&) = delete;`
- L26 _public prototype_ `FCrashReporterScope& operator=(const FCrashReporterScope&) = delete;`
- L29 _private member_ `bool bWasEnabled = false;`
- L30 _private member_ `uint32 ID = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L35 _macro_ `#define UAF_CRASH_REPORTER_SCOPE(InOwner, InObjectOfInterest, InContextName) ::UE::UAF::FCrashReporterScope ANONYMOUS_VARIABLE(AddCrashContext) {(InOwner), (InObjectOfInterest), (#InContextName)}`
- L38 _macro_ `#define UE_WORKSPACE_EDITOR_CRASH_REPORTER_SCOPE()`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/DataInterface/AnimNextNativeDataInterface.h` (Internal)


#### struct `FAnimNextNativeDataInterface`  
`struct FAnimNextNativeDataInterface`  
_L12-37_
- reflection: `USTRUCT()`
- desc: DEPRECATED - no longer in use
- L16 _public prototype_ `FAnimNextNativeDataInterface() = default;`
- L17 _public prototype_ `virtual ~FAnimNextNativeDataInterface() = default;`
- L32 _public function_ `virtual void BindToFactoryObject(const FBindToFactoryObjectContext& InContext)` — Initialize this native interface during factory object creation. Called once on worker threads to set up this native interface's properties after it has been default-constructed. The data interface instance that it will manage has not yet been constructed at this point.
- L35 _public function_ `virtual const UScriptStruct* GetUpgradeTraitStruct() const` — Use to upgrade older content to the trait-based approach

#### struct `FAnimNextNativeDataInterface::FBindToFactoryObjectContext`  
`struct FBindToFactoryObjectContext`  
_L20-27_
- desc: Context passed to Initialize()
- L23 _public member_ `const UObject* FactoryObject = nullptr;` — If this native interface was created as a result of a factory, then this is the object that the factor used as a source. Can be nullptr.
- L26 _public member_ `const UUAFSharedVariables* DataInterface = nullptr;` — The data interface that this native interface was constructed for

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Factory/SystemBuilderContext.h` (Internal)


#### struct `UE::UAF::FSystemBuilderContext`  
`struct FSystemBuilderContext`  
_L23-43_
- L29 _private prototype_ `const UUAFSystem* Build();` — Builds a system using the populated ComponentStructs & VariableStructs
- L33 _public member_ `TSet<const UScriptStruct*> ComponentStructs;` — Component structs used to run the system
- L36 _public member_ `TSet<const UScriptStruct*> VariableStructs;` — Variable structs used to communicate with the system
- L39 _public member_ `TSet<TScriptInterface<const IRigVMRuntimeAssetInterface>> ReferencedVariableRigVMAssets;` — All the IRigVMRuntimeAssetInterface whose variables we will reference/instance at runtime
- L42 _public member_ `TSet<TObjectPtr<const UUAFRigVMAsset>> ReferencedVariableAssets;` — All the assets whose variables we will reference/instance at runtime

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/AnimNext_LODPose.h` (Internal)


#### struct `FAnimNextGraphReferencePose`  
`struct FAnimNextGraphReferencePose`  
_L16-28_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "ReferencePose"))`
- L20 _public prototype_ `FAnimNextGraphReferencePose() = default;`
- L22 _public function_ `explicit FAnimNextGraphReferencePose(UE::UAF::FDataHandle& InReferencePose) : ReferencePose(InReferencePose)`
- L27 _public member_ `UE::UAF::FDataHandle ReferencePose;`

#### struct `FAnimNextGraphLODPose`  
`struct FAnimNextGraphLODPose`  
_L31-58_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "LODPose"))`
- L36 _public member_ `UE::UAF::FLODPoseHeap LODPose;` — Joint transforms
- L39 _public member_ `FBlendedHeapCurve Curves;` — Float curves
- L43 _public member_ `UE::Anim::FHeapAttributeContainer Attributes;` — Attributes Note that attribute bone indices are LOD bone indices matching the LOD pose
- L49 _public prototype_ `static void CopyPose( const UE::UAF::FLODPoseHeap& InSourcePose, const FBlendedHeapCurve& InSourceCurves, const UE::Anim::FHeapAttributeContainer& InSourceAttributes, UE::UAF::FLODPoseHeap& OutTargetPose, FBlendedHeapCurve& OutTargetCurves, UE::Anim::FHeapAttributeContainer& OutTargetAttributes);` — Copy source pose into target pose, automatically remapping bones and attributes if skeletons differ. Curves are always copied directly (no skeleton dependency).
- L54 _public prototype_ `void CopyFrom(const UE::UAF::FLODPoseHeap& InPose, const FBlendedHeapCurve& InCurves, const UE::Anim::FHeapAttributeContainer& InAttributes);` — Copy from individual source components, automatically remapping bones and attributes via FRemapPoseDataPool if skeletons differ.
- L57 _public prototype_ `void CopyFrom(const FAnimNextGraphLODPose& Source);` — Copy from source, automatically remapping bones and attributes via FRemapPoseDataPool if skeletons differ.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/RigUnit_AnimNextBase.h` (Internal)


#### struct `FRigUnit_AnimNextBase`  
`struct FRigUnit_AnimNextBase : public FRigVMStruct`  
_L14-17_
- reflection: `USTRUCT(meta=(ExecuteContext="FAnimNextExecuteContext", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: base class for all UAF rigvm nodes

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/RigUnit_AnimNextBeginExecution.h` (Internal)


#### struct `FRigUnit_AnimNextBeginExecution`  
`struct FRigUnit_AnimNextBeginExecution : public FRigUnit_AnimNextBase`  
_L15-30_
- reflection: `USTRUCT(meta=(DisplayName="Execute", Category="Events", NodeColor="1, 0, 0", Keywords="Begin,Update,Tick,Forward,Event"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Event for driving the skeleton hierarchy with variables and rig elements
- L19 _public prototype_ `RIGVM_METHOD() void Execute();`
- L22 _public function_ `virtual FName GetEventName() const override`
- L23 _public function_ `virtual bool CanOnlyExistOnce() const override`
- L27 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Output))` — The execution result
- L29 _public member_ `static FName EventName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/RigUnit_AnimNextWriteSkeletalMeshComponentPose.h` (Internal)


#### struct `FRigUnit_AnimNextWriteSkeletalMeshComponentPose`  
`struct FRigUnit_AnimNextWriteSkeletalMeshComponentPose : public FRigUnit_AnimNextBase`  
_L15-37_
- reflection: `USTRUCT(meta=(DisplayName="Write Pose", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Output,Pose,Port", RequiredComponents="AnimNextSkeletalMeshComponentReferenceComponent"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Writes a pose to a skeletal mesh component
- L19 _public prototype_ `RIGVM_METHOD() void Execute();`
- L22 _public prototype_ `static void WritePose(USkeletalMeshComponent* InOutputComponent, const FAnimNextGraphLODPose& InPose);`
- L24 _public function_ `virtual FString GetUnitSubTitle() const`
- L28 _public member_ `FAnimNextGraphLODPose Pose;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Pose to write
- L32 _public member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Mesh to write to. If this is not supplied, then the first skeletal mesh component of the current actor will be used
- L36 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/RigUnit_UAFWriteInstancedSkinnedMeshPose.h` (Internal)


#### struct `FRigUnit_UAFWriteInstancedSkinnedMeshPose`  
`struct FRigUnit_UAFWriteInstancedSkinnedMeshPose : public FRigUnit_AnimNextBase`  
_L16-36_
- reflection: `USTRUCT(meta=(DisplayName="Write Pose Instanced", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Output,Pose,Port"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Writes a pose to an instanced skinned mesh component
- L20 _public prototype_ `RIGVM_METHOD() void Execute();`
- L23 _public function_ `virtual FString GetUnitSubTitle() const`
- L27 _public member_ `FAnimNextGraphLODPose Pose;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Pose to write
- L31 _public member_ `TObjectPtr<class UInstancedSkinnedMeshComponent> SkinnedMeshComponent;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Mesh to write to.
- L35 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/RigUnit_UAFWriteSystemOutput.h` (Internal)


#### struct `FRigUnit_UAFWriteSystemOutput`  
`struct FRigUnit_UAFWriteSystemOutput : public FRigUnit_AnimNextBase`  
_L16-30_
- reflection: `USTRUCT(meta=(DisplayName="Write System Output", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Output,Pose,Port", RequiredComponents="UAFSystemOutputComponent"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Writes the output for a system
- L20 _public prototype_ `RIGVM_METHOD() void Execute();`
- L25 _public member_ `FUAFValueBundle Value;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Value to write to output
- L29 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/RigVMTrait_AnimNextPublicVariables.h` (Internal)


#### struct `FRigVMTrait_AnimNextPublicVariables`  
`struct FRigVMTrait_AnimNextPublicVariables : public FRigVMTrait`  
_L17-40_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait`
- desc: Represents public variables of an asset via a trait
- L23 _public member_ `TObjectPtr<UUAFSharedVariables> InternalAsset = nullptr;` — `UPROPERTY(meta = (Hidden))` — The asset that any programmatic pins will be derived from, if any
- L27 _public member_ `TArray<FName> InternalVariableNames;` — `UPROPERTY(meta = (Hidden))` — Variable names that are exposed
- L31 _public prototype_ `virtual FString GetDisplayName() const override;`
- L32 _public prototype_ `virtual void GetProgrammaticPins(URigVMController* InController, int32 InParentPinIndex, const URigVMPin* InTraitPin, const FString& InDefaultValue, FRigVMPinInfoArray& OutPinArray) const override;`
- L33 _public prototype_ `virtual bool ShouldCreatePinForProperty(const FProperty* InProperty) const override;`
- L36 _public member_ `static FString (*GetDisplayNameFunc)(const FRigVMTrait_AnimNextPublicVariables& InTrait);` — Editor-implemented function ptrs
- L37 _public member_ `static void (*GetProgrammaticPinsFunc)(const FRigVMTrait_AnimNextPublicVariables& InTrait, URigVMController* InController, int32 InParentPinIndex, const FString& InDefaultValue, FRigVMPinInfoArray& OutPinArray);`
- L38 _public member_ `static bool (*ShouldCreatePinForPropertyFunc)(const FRigVMTrait_AnimNextPublicVariables& InTrait, const FProperty* InProperty);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Graph/UAFSystemOutputComponent.h` (Internal)


#### struct `FUAFSystemOutputComponent`  
`struct FUAFSystemOutputComponent : public FUAFModuleInstanceComponent`  
_L32-135_
- reflection: `USTRUCT()`
- inherits: `FUAFModuleInstanceComponent`
- desc: System component used to identify output values
- L35 _public function_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT()`
- L44 _public function_ `int32 GetLOD() const` — Get the LOD we are currently outputting as
- L50 _public function_ `USkeletalMesh* GetSkeletalMesh() const` — Get the mesh we are currently outputting to
- L56 _public function_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const` — Get the legacy mesh component we are currently outputting to
- L62 _public typedef_ `using FReadOutputFunc = TFunctionRef<void(uint32 InSerialNumber, const FAnimNextGraphLODPose& InPose, const FAnimNextGraphReferencePose& InRefPose)>;` — Function used to callback into
- L66 _public prototype_ `void RemapLODPoseToOutput(const FAnimNextGraphLODPose& InInputPose, FAnimNextGraphLODPose& InOutputPose);` — Helper function used to remap a LOD pose to the output pose's refpose Temporary until the value runtime is ready
- L70 _private prototype_ `virtual void OnBeginExecution(float InDeltaTime) override;` — FUAFModuleInstanceComponent interface
- L74 _private prototype_ `void WriteOutput(const FUAFValueBundle& InValue);` — Write the output @param    InValue    The value to write
- L84 _private prototype_ `bool GenerateRenderData(uint32 InSerialNumber, FReadOutputFunc InFunction) const;` — Generate the pose etc. for rendering by a mesh. If the serial numbers differ, a callback to the InFunction occurs, otherwise the call is skipped. If the supplied serial number matches the one held in this component, then the pose is assumed to have not been written, so no work needs to occur If the serial number supplied is zero, then the GenerateRenderData call will always be made InFunction can also be skipped if other invariants are not satisfied (e.g. null or mismatched mesh) @param    InSerialNumber    The current serial number that the reader holds @param    InFunction        Function that will be called if conditions are met @return true if the read was successful (i.e. the serial numbers were mismatched)
- L93 _private prototype_ `bool ReadOutput(uint32 InSerialNumber, FReadOutputFunc InFunction) const;` — Read the output value etc. for internal UAF use If the serial numbers differ, a callback to the InFunction occurs, otherwise the call is skipped. If the supplied serial number matches the one held in this component, then the pose is assumed to have not been written, so no work needs to occur If the serial number supplied is zero, then the GenerateRenderData call will always be made @param    InSerialNumber    The current serial number that the reader holds @param    InFunction        Function that will be called if conditions are met @return true if the read was successful (i.e. the serial numbers were mismatched)
- L96 _private prototype_ `void BindSystemOutputAdapter(UE::UAF::ISystemOutputAdapter& InSystemOutputAdapter);` — Called to bind this component to a specific system output adapter (e.g. mesh component)
- L99 _private prototype_ `void UnbindSystemOutputAdapter();` — Unbinds from any system output adapter we are currently bound to
- L110 _private member_ `FAnimNextGraphLODPose Pose;` — The output pose that was written this time around
- L114 _private member_ `TObjectPtr<USkeletalMesh> Mesh;` — `UPROPERTY(Transient)` — The mesh we use to determine the final pose format
- L118 _private member_ `TObjectPtr<USkeletalMeshComponent> MeshComponent;` — `UPROPERTY(Transient)` — Legacy skeletal mesh component, if any
- L122 _private member_ `FAnimNextGraphReferencePose RefPose;` — `UPROPERTY(Transient)` — Refpose generated from the mesh
- L125 _private member_ `UE::UAF::ISystemOutputAdapter* SystemOutputAdapter = nullptr;` — Adapter to use for output
- L128 _private member_ `int32 LOD = 0;` — The LOD that our system is running at this tick
- L131 _private member_ `uint32 SerialNumber = 0;` — Serial number updated each time we write the output
- L134 _private member_ `uint32 CurrentRequiredBonesSerial = 0;` — Serial number for required bones

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace Tests` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Module/AnimNextActorComponentReferenceComponent.h` (Internal)


#### struct `FAnimNextActorComponentReferenceComponent`  
`struct FAnimNextActorComponentReferenceComponent : public FUAFModuleInstanceComponent`  
_L16-32_
- reflection: `USTRUCT()`
- inherits: `FUAFModuleInstanceComponent`
- desc: Module instance component used to provide a reference to an actor component Note that this does not support dynamic component updates (e.g. if we have multiple, or changing components). It grabs a ptr to the component on initialization and does not update it.
- L19 _public prototype_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT() protected:`
- L27 _public member_ `TObjectPtr<UActorComponent> Component;` — `UPROPERTY()` — The component we reference
- L31 _public member_ `TSubclassOf<UActorComponent> ComponentType;` — `UPROPERTY()` — The type of the component to find

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Module/AnimNextModuleContextData.h` (Internal)


#### struct `FAnimNextModuleContextData`  
`struct FAnimNextModuleContextData : public FUAFAssetContextData`  
_L14-27_
- reflection: `USTRUCT()`
- inherits: `FUAFAssetContextData`
- desc: Context structure passed to script calls
- L18 _public prototype_ `FAnimNextModuleContextData() = default;`
- L20 _public prototype_ `FAnimNextModuleContextData(FAnimNextModuleInstance& InInstance, FName InEventName, float InDeltaTime);`
- L23 _public prototype_ `UObject* GetObject() const;` — Get the object that the module instance is bound to, if any
- L26 _public prototype_ `FAnimNextModuleInstance& GetModuleInstance() const;` — Get the currently executing module.

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Module/AnimNextModuleInstance.h` (Internal)


#### struct `FAnimNextModuleInstance`  
`struct FAnimNextModuleInstance : public FUAFAssetInstance #if CPP , TSharedFromThis<FAnimNextModuleInstance> #endif`  
_L61-316_
- reflection: `USTRUCT()`
- inherits: `FUAFAssetInstance,TSharedFromThis<FAnimNextModuleInstance>`
- desc: Represents an instance of a UAF system.
- L68 _public prototype_ `FAnimNextModuleInstance();`
- L71 _public prototype_ `FAnimNextModuleInstance( const UUAFSystem* InModule, EAnimNextModuleInitMethod InInitMethod);` — Standalone constructor
- L76 _public prototype_ `FAnimNextModuleInstance( const UUAFSystem* InModule, UObject* InObject, EAnimNextModuleInitMethod InInitMethod);` — Standalone constructor, UObject host
- L81 _public prototype_ `~FAnimNextModuleInstance();`
- L84 _public prototype_ `bool IsEnabled() const;` — Checks to see if this entry is ticking
- L87 _public prototype_ `void SetEnabled(bool bInEnabled);` — Enables/disables the ticking of this entry
- L91 _public prototype_ `void QueueInputTraitEvent(FAnimNextTraitEventPtr Event);` — Queues an input trait event Input events will be processed in the next graph update after they are queued
- L95 _public prototype_ `void QueueOutputTraitEvent(FAnimNextTraitEventPtr Event);` — Queues an output trait event Output events will be processed at the end of the schedule tick
- L98 _public function_ `UObject* GetObject() const` — Get the object that this module is bound to
- L101 _public prototype_ `const UUAFSystem* GetSystem() const;` — Get the system that this instance represents
- L105 _public prototype_ `FRigVMDrawInterface* GetDebugDrawInterface();` — Get the debug draw interface
- L108 _public prototype_ `void ShowDebugDrawing(bool bInShowDebugDrawing);` — Set whether to show the module's debug drawing instructions in the viewport
- L112 _public prototype_ `static void RunTaskOnGameThread(TUniqueFunction<void(void)>&& InFunction);` — Run a simple task on the GT via FFunctionGraphTask::CreateAndDispatchWhenReady
- L115 _public prototype_ `UE::UAF::FModuleEventTickFunction* FindTickFunctionByName(FName InEventName);` — Find the tick function for the specified event
- L116 _public prototype_ `const UE::UAF::FModuleEventTickFunction* FindTickFunctionByName(FName InEventName) const;`
- L119 _public prototype_ `UE::UAF::FModuleEventTickFunction* FindFirstUserTickFunction();` — Find the first 'user' tick function
- L122 _public prototype_ `UE::UAF::FModuleEventTickFunction* FindLastUserTickFunction();` — Find the last 'user' tick function
- L125 _public prototype_ `void RunScriptEvent(const UE::UAF::FScriptEvent& InEvent, float InDeltaTime);` — Run the specified script event using a module context
- L128 _public prototype_ `void RunScriptEventByName(FName InEventName, float InDeltaTime);` — Run the specified script event using a module context, using name lookup alone (slower)
- L131 _public function_ `EWorldType::Type GetWorldType() const` — Get the world type that this module was instantiated within
- L134 _public prototype_ `TArrayView<UE::UAF::FModuleEventTickFunction> GetTickFunctions();` — Get tick functions for this module instance
- L137 _public prototype_ `FUAFWeakSystemReference GetReference() const;` — Get a weak, non-owning reference to this instance
- L141 _public function_ `void QueueTask(UE::UAF::FUniqueSystemTask&& InTaskFunction)` — Queue a task to run before the first user event @param	InTaskFunction		The function to run
- L150 _public prototype_ `void QueueTask(FName InEventName, UE::UAF::FUniqueSystemTask&& InTaskFunction, UE::UAF::ETaskRunLocation InLocation = UE::UAF::ETaskRunLocation::Before);` — Queue a task to run at a particular system event @param	InEventName			The event in the system to run the supplied task relative to. If this is NAME_None or not found then the first 'user' event will be used. @param	InTaskFunction		The function to run @param	InLocation			Where to run the task, before or after
- L154 _public prototype_ `void Trace();` — trace this module if it hasn't already been traced this frame
- L160 _private prototype_ `void Initialize(const FUAFSystemFactoryParams& InFactoryParams);` — Setup the entry Note that we perform initialization in two phases because we may need to access weak references to 'this' during initialization
- L163 _private prototype_ `void ResetBindingsAndInstanceData();` — Clear data that binds the schedule to a runtime (e.g. tick functions) and any instance data
- L166 _private prototype_ `void RemoveAllTickDependencies();` — Remove all of our tick function's dependencies
- L169 _private prototype_ `void CopyProxyVariables();` — Flip proxy variable buffers then copy any dirty values
- L173 _private prototype_ `void OnCompileJobFinished();` — Resets internal state if the module we are bound to is recompiled in editor
- L177 _private prototype_ `void BeginExecution(float InDeltaTime);` — Call module components' OnBeginExecution extension point
- L180 _private prototype_ `void EndExecution(float InDeltaTime);` — Give the module components a chance to handle events and call their OnEndExecution extension point
- L184 _private prototype_ `void RaiseTraitEvents(const UE::UAF::FTraitEventList& EventList);` — Handles trait events at the module level. Called in the module end tick function before any events are dispatched.
- L187 _private prototype_ `EPropertyBagResult SetProxyVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InData);` — Set the value of the specified variable via the proxy double-buffer. Called from any thread.
- L190 _private prototype_ `EPropertyBagResult WriteProxyVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TArrayView<uint8>)> InFunction);` — Accesses value of the specified variable via the proxy double-buffer. Called from any thread.
- L200 _private prototype_ `EPropertyBagResult ReadVariableFromExternal(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TConstArrayView<uint8>)> InFunction);` — Access a variable's value given its reference via a raw memory view. This performs non-recursive locks on the system instance to ensure that concurrent access is respected, so care must be taken calling this from animation worker tasks as deadlocks can occur. Type must match strictly, no conversions are performed. @param	InVariable			The variable to get the value of @param	InType				The type of the variable @param	InFunction			Function that will be called if no errors occur @return see EPropertyBagResult
- L206 _private prototype_ `bool ReadComponentFromExternal(UScriptStruct* InComponentType, TFunctionRef<void(FConstStructView InComponentStruct)> InFunction);` — Access the supplied system component for reading. Component will not be lazily created. @param	InComponentType		The type of the component we want ot access @param	InFunction			Function that will be called to access the struct @return true if the struct was available, otherwise false
- L227 _private member_ `TObjectPtr<UObject> Object = nullptr;` — `UPROPERTY(Transient)` — Object this entry is bound to
- L230 _private member_ `TArray<UE::UAF::FModuleEventTickFunction> TickFunctions;` — Pre-allocated graph of tick functions
- L233 _private member_ `UE::UAF::FTraitEventList InputEventList;` — Input event list to be processed on the next update
- L236 _private member_ `UE::UAF::FTraitEventList OutputEventList;` — Output event list to be processed at the end of the schedule tick
- L239 _private member_ `FTransactionallySafeRWLock EventListLock;` — Lock to ensure event list actions are thread safe
- L242 _private member_ `FTransactionallySafeRWLock ProxyLock;` — Lock to ensure proxy access is thread safe
- L245 _private member_ `FTransactionallySafeRWLock SystemReferenceLock;` — Lock guarding against gross concurrent access via system references (safety only: should rarely contend if dependencies are set correctly)
- L249 _private member_ `FUAFInstanceVariableDataProxy ProxyVariables[2];` — `UPROPERTY(Transient)` — Proxy public variables, double-buffered
- L252 _private member_ `int32 ProxyWriteIndex = 0;` — Index into current buffer to write the proxy variables
- L257 _private member_ `TUniquePtr<UE::UAF::Debug::FDebugDraw> DebugDraw;` — Debug draw support TODO: Move this to a 'module component' once that code is checked in
- L278 _private member_ `EInitState InitState = EInitState::NotInitialized;` — Current initialization state
- L290 _private member_ `ERunState RunState = ERunState::NotInitialized;` — Current running state
- L293 _private prototype_ `void TransitionToInitState(EInitState InNewState);` — Transition to the specified init state, verifying that the current state is valid
- L296 _private prototype_ `void TransitionToRunState(ERunState InNewState);` — Transition to the specified run state, verifying that the current state is valid
- L299 _private member_ `EAnimNextModuleInitMethod InitMethod = EAnimNextModuleInitMethod::InitializeAndPauseInEditor;` — How this entry initializes
- L302 _private member_ `EWorldType::Type WorldType = EWorldType::None;` — Whether this represents an editor object
- L306 _private member_ `bool bIsRecreatingOnCompile : 1 = false;` — Whether we are currently recreating this instance because of compilation/reinstancing
- L309 _private member_ `bool bHasBeenQueuedForRelease : 1 = false;` — Whether the module instance has had its custom destructor called (queueing it up for release at the end of the frame)
- L314 _private member_ `bool bTracedThisFrame = false;`

#### enum `FAnimNextModuleInstance::EInitState`  
`enum class EInitState : uint8`  
_L260-275_
- L262 _public enumerator_ `NotInitialized`
- L264 _public enumerator_ `CreatingTasks`
- L266 _public enumerator_ `BindingTasks`
- L268 _public enumerator_ `SetupVariables`
- L270 _public enumerator_ `PendingInitializeEvent`
- L272 _public enumerator_ `FirstUpdate`
- L274 _public enumerator_ `Initialized`

#### enum `FAnimNextModuleInstance::ERunState`  
`enum class ERunState : uint8`  
_L280-287_
- L282 _public enumerator_ `NotInitialized`
- L284 _public enumerator_ `Running`
- L286 _public enumerator_ `Paused`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextModuleInstance> : public TStructOpsTypeTraitsBase2<FAnimNextModuleInstance>`  
_L319-325_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextModuleInstance>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L322-324_

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API UAF_API`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace UAF` (scope `UE`)
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace UAF` (scope `UE`)
- L43 _namespace_ `namespace Debug` (scope `UE::UAF`)
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace UAF` (scope `UE`)
- L50 _typedef_ `using ModuleInstanceComponentMapType = TMap<FName, TInstancedStruct<FUAFModuleInstanceComponent>>;` (scope `UE::UAF`)
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace UAF` (scope `UE`)
- L53 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L323 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anone89a24db0103`)
- L329 _macro_ `#define TRACE_UAF_MODULE(ModuleInstance) ModuleInstance.Trace();`
- L331 _macro_ `#define TRACE_UAF_MODULE(ModuleInstance)`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Module/AnimNextSkeletalMeshComponentReferenceComponent.h` (Internal)


#### struct `FAnimNextSkeletalMeshComponentReferenceComponent`  
`struct FAnimNextSkeletalMeshComponentReferenceComponent : public FAnimNextActorComponentReferenceComponent`  
_L13-24_
- reflection: `USTRUCT()`
- inherits: `FAnimNextActorComponentReferenceComponent`
- desc: Module instance component used to fetch data about the current actor's skeletal mesh component
- L17 _public prototype_ `FAnimNextSkeletalMeshComponentReferenceComponent();`
- L19 _public prototype_ `USkeletalMeshComponent* GetComponent() const;`
- L23 _private prototype_ `virtual void OnBindToInstance() override;` — FUAFAssetInstanceComponent interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Module/ModuleTickFunction.h` (Internal)


#### struct `UE::UAF::FModuleEventTickFunction`  
`struct FModuleEventTickFunction : public FTickFunction`  
_L29-97_
- inherits: `FTickFunction`
- L31 _public function_ `FModuleEventTickFunction()`
- L40 _public prototype_ `virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;` — FTickFunction interface
- L41 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L43 _public prototype_ `void Initialize(float DeltaTime);`
- L44 _public prototype_ `void ExecuteBindings_WT(float DeltaTime);`
- L45 _public prototype_ `void Run(float DeltaTime);`
- L46 _public prototype_ `void EndTick(float DeltaTime);`
- L51 _public prototype_ `static void InitializeAndRunModule(FAnimNextModuleInstance& InModuleInstance);` — Called standalone to run a whole module's init & work in one call. Expensive and editor only. Intended to be used outside of a ticking context, such as a non-ticking world or forced initialization.
- L54 _public prototype_ `void AddSubsequent(UObject* InObject, FTickFunction& InTickFunction);`
- L55 _public prototype_ `void RemoveSubsequent(UObject* InObject, FTickFunction& InTickFunction);`
- L56 _public prototype_ `void RemoveAllExternalSubsequents();`
- L57 _public prototype_ `void InitializeBatchedWork(class UWorld* World);`
- L59 _public prototype_ `static void RunTaskOnGameThread(TUniqueFunction<void(void)>&& InFunction);`
- L61 _public member_ `FAnimNextModuleInstance* ModuleInstance = nullptr;`
- L65 _public typedef_ `using FTaskQueueType = TTransactionallySafeSpscQueue<UE::UAF::FUniqueSystemTask>;`
- L67 _public typedef_ `using FTaskQueueType = TMpscQueue<UE::UAF::FUniqueSystemTask>;`
- L70 _public member_ `FTaskQueueType PreExecuteTasks;`
- L71 _public member_ `FTaskQueueType PostExecuteTasks;`
- L74 _public member_ `TArray<TUniqueFunction<void()>> PostExecuteGameThreadTaskList;` — Tasks queued to execute on the game thread after the current tick completes
- L77 _public member_ `UE::Tick::FActiveSyncWorkHandle BatchedWorkHandle;` — Handle to use for submitting batched work to the task sync manager
- L80 _public member_ `FOnPreModuleEvent OnPreModuleEvent;` — Multicast delegate called before this event
- L83 _public member_ `FScriptEvent Event;` — The event itself
- L86 _public member_ `FScriptEvent InitializeEvent;` — Initialize event - will be called if valid
- L89 _public member_ `FScriptEvent ExecuteBindings_WTEvent;` — WT bindings event - will be called if valid
- L91 _public member_ `uint8 bLastUserEvent : 1 = false;`
- L92 _public member_ `uint8 bFirstUserEvent : 1 = false;`
- L93 _public member_ `uint8 bUserEvent : 1 = false;`
- L96 _public member_ `TArray<FTickPrerequisite> ExternalSubsequents;` — External dependencies that this tick function needs to unregister when it is destroyed

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L27 _typedef_ `using FOnPreModuleEvent = TTSMulticastDelegate<void(const FModuleTaskContext& InContext)>;` (scope `UE::UAF`) — Multicast delegate called before module events

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Module/RigUnit_AnimNextModuleEventDependencies.h` (Internal)


#### class `UAnimNextAddDependencyMenuContext`  
`class UAnimNextAddDependencyMenuContext : public UObject`  
_L14-20_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `TObjectPtr<URigVMController> Controller = nullptr;`
- L19 _public member_ `TObjectPtr<URigVMNode> Node = nullptr;`

#### struct `FRigUnit_AnimNextModuleDependenciesBase`  
`struct FRigUnit_AnimNextModuleDependenciesBase : public FRigUnit_AnimNextBase`  
_L26-38_
- reflection: `USTRUCT(meta=(Hidden, Category="Dependencies", NodeColor="0, 1, 1", Keywords="Prerequisite,Subsequent,TickFunction"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: the base class for all dependencies nodes
- L30 _public prototype_ `FRigUnit_AnimNextModuleDependenciesBase() = default;`
- L33 _public prototype_ `virtual TArray<FRigVMUserWorkflow> GetSupportedWorkflows(const UObject* InSubject) const override;` — FRigVMStruct interface
- L37 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "Events", meta = (Input, Output))` — The execution result

#### struct `FRigUnit_AnimNextModuleAddDependencies`  
`struct FRigUnit_AnimNextModuleAddDependencies : public FRigUnit_AnimNextModuleDependenciesBase`  
_L42-50_
- reflection: `USTRUCT(meta=(DisplayName="Add Dependencies"))`
- inherits: `FRigUnit_AnimNextModuleDependenciesBase`
- desc: Adds execution dependencies between module events and other systems
- L46 _public prototype_ `FRigUnit_AnimNextModuleAddDependencies() = default;`
- L48 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigUnit_AnimNextModuleRemoveDependencies`  
`struct FRigUnit_AnimNextModuleRemoveDependencies : public FRigUnit_AnimNextModuleDependenciesBase`  
_L54-62_
- reflection: `USTRUCT(meta=(DisplayName="Remove Dependencies"))`
- inherits: `FRigUnit_AnimNextModuleDependenciesBase`
- desc: Removes execution dependencies between module events and some systems
- L58 _public prototype_ `FRigUnit_AnimNextModuleRemoveDependencies() = default;`
- L60 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Module/RigUnit_AnimNextModuleEvents.h` (Internal)


#### struct `FRigUnit_AnimNextModuleEventBase`  
`struct FRigUnit_AnimNextModuleEventBase : public FRigUnit_AnimNextBase`  
_L16-53_
- reflection: `USTRUCT(meta=(Abstract, Category="Events", NodeColor="1, 0, 0", Keywords="Begin,Update,Tick,Forward,Event"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Base schedule-level event, never instantiated
- L20 _public prototype_ `FRigUnit_AnimNextModuleEventBase() = default;`
- L23 _public function_ `virtual FString GetUnitLabel() const override` — FRigUnit interface
- L24 _public function_ `virtual bool CanOnlyExistOnce() const override`
- L27 _public function_ `virtual UE::UAF::EScriptEventPhase GetEventPhase() const` — Get the general ordering phase of this event, used for linearization
- L30 _public function_ `virtual UE::UAF::FTickFunctionBindingFunction GetBindingFunction() const` — Overriden in derived classes to provide binding function
- L33 _public function_ `virtual ETickingGroup GetTickGroup() const` — Get the tick group for this event
- L36 _public function_ `virtual ETickingGroup GetEndTickGroup() const` — Get the end tick group for this event
- L39 _public function_ `virtual int32 GetSortOrder() const` — Get the integer sort key for this event (used to sort events in tick groups - smaller values get sorted earlier)
- L42 _public function_ `virtual bool IsUserEvent() const` — Get whether this is a user-generated event (as opposed to a compiler-generated event)
- L45 _public function_ `virtual bool IsTask() const` — Get whether this event corresponds to a separate task (so tick functions will be generated to run it)
- L48 _public function_ `virtual bool IsGameThreadTask() const` — Get whether this event is limited to the game thread only
- L52 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "Events", meta = (Output))` — The execution result

#### struct `FRigUnit_AnimNextExecuteBindings_GT`  
`struct FRigUnit_AnimNextExecuteBindings_GT : public FRigUnit_AnimNextModuleEventBase`  
_L57-75_
- reflection: `USTRUCT(meta=(Hidden, Category="Internal", NodeColor="1, 0, 0"))`
- inherits: `FRigUnit_AnimNextModuleEventBase`
- desc: Synthetic event injected by the compiler to process any variable bindings on the game thread, not user instantiated
- L61 _public prototype_ `FRigUnit_AnimNextExecuteBindings_GT() = default;`
- L63 _public member_ `static inline const FLazyName EventName = FLazyName("Exe`
- L65 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L67 _public function_ `virtual FName GetEventName() const override final`
- L68 _public function_ `virtual int32 GetSortOrder() const override final` — Sort before WT bindings
- L69 _public function_ `virtual bool IsUserEvent() const override final`
- L70 _public function_ `virtual bool IsGameThreadTask() const override final`
- L73 _public function_ `virtual UE::UAF::EScriptEventPhase GetEventPhase() const override final` — FRigUnit_AnimNextModuleEventBase interface
- L74 _public prototype_ `virtual UE::UAF::FTickFunctionBindingFunction GetBindingFunction() const override final;`

#### struct `FRigUnit_AnimNextExecuteBindings_WT`  
`struct FRigUnit_AnimNextExecuteBindings_WT : public FRigUnit_AnimNextModuleEventBase`  
_L79-97_
- reflection: `USTRUCT(meta=(Hidden, Category="Internal", NodeColor="1, 0, 0"))`
- inherits: `FRigUnit_AnimNextModuleEventBase`
- desc: Synthetic event injected by the compiler to process any variable bindings on a worker thread, not user instantiated
- L83 _public prototype_ `FRigUnit_AnimNextExecuteBindings_WT() = default;`
- L85 _public member_ `static inline const FLazyName EventName = FLazyName("Exe`
- L87 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L89 _public function_ `virtual FName GetEventName() const override final`
- L90 _public function_ `virtual int32 GetSortOrder() const override final` — Sort after GT bindings
- L91 _public function_ `virtual bool IsUserEvent() const override final`
- L92 _public function_ `virtual bool IsTask() const override final`
- L95 _public function_ `virtual UE::UAF::EScriptEventPhase GetEventPhase() const override final` — FRigUnit_AnimNextModuleEventBase interface
- L96 _public prototype_ `virtual UE::UAF::FTickFunctionBindingFunction GetBindingFunction() const override final;`

#### struct `FRigUnit_AnimNextInitializeEvent`  
`struct FRigUnit_AnimNextInitializeEvent : public FRigUnit_AnimNextModuleEventBase`  
_L101-111_
- reflection: `USTRUCT(meta=(DisplayName="Initialize", Keywords="Setup,Startup,Create"))`
- inherits: `FRigUnit_AnimNextModuleEventBase`
- desc: Schedule event called to set up a module
- L105 _public member_ `static inline const FLazyName EventName = FLazyName("Ini`
- L107 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L109 _public function_ `virtual FName GetEventName() const override final`
- L110 _public function_ `virtual bool IsTask() const override final`

#### struct `FRigUnit_AnimNextUserEvent`  
`struct FRigUnit_AnimNextUserEvent : public FRigUnit_AnimNextModuleEventBase`  
_L115-145_
- reflection: `USTRUCT(meta=(Abstract))`
- inherits: `FRigUnit_AnimNextModuleEventBase`
- desc: Base event for all user-authored events. Can execute in a particular tick group (e.g. TG_PrePhysics)
- L120 _public function_ `virtual FName GetEventName() const override final` — FRigUnit_AnimNextModuleEventBase interface
- L121 _public function_ `virtual FString GetUnitLabel() const override`
- L122 _public prototype_ `virtual FString GetUnitSubTitle() const override;`
- L123 _public function_ `virtual bool CanOnlyExistOnce() const override`
- L124 _public function_ `virtual UE::UAF::EScriptEventPhase GetEventPhase() const override final`
- L125 _public prototype_ `virtual UE::UAF::FTickFunctionBindingFunction GetBindingFunction() const override final;`
- L126 _public function_ `virtual ETickingGroup GetTickGroup() const override final`
- L127 _public function_ `virtual ETickingGroup GetEndTickGroup() const override final`
- L128 _public function_ `virtual int32 GetSortOrder() const override final`
- L132 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Event", meta = (Input, Constant, DetailsOnly))` — The name of the event
- L136 _public member_ `int32 SortOrder = 0;` — `UPROPERTY(EditAnywhere, Category = "Event", meta = (Input, Constant, DetailsOnly))` — Sort index for ordering with other events in this tick group - smaller values get sorted earlier
- L140 _public member_ `TEnumAsByte<ETickingGroup> TickGroup = ETickingGroup::TG_PrePhysics;` — `UPROPERTY()` — The tick group the event executes in
- L144 _public member_ `TEnumAsByte<ETickingGroup> EndTickGroup = ETickingGroup::TG_PrePhysics;` — `UPROPERTY(EditAnywhere, Category = "Tick", meta = (Input, Constant, DetailsOnly))` — The tick group the event completes by

#### struct `FRigUnit_AnimNextPrePhysicsEvent`  
`struct FRigUnit_AnimNextPrePhysicsEvent : public FRigUnit_AnimNextUserEvent`  
_L149-163_
- reflection: `USTRUCT(meta=(DisplayName="PrePhysics", Keywords="Start,Before"))`
- inherits: `FRigUnit_AnimNextUserEvent`
- desc: Schedule event called before world physics is updated
- L153 _public member_ `static inline const FLazyName DefaultEventName = FLazyName("Pre`
- L155 _public function_ `FRigUnit_AnimNextPrePhysicsEvent()`
- L161 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### struct `FRigUnit_AnimNextPostPhysicsEvent`  
`struct FRigUnit_AnimNextPostPhysicsEvent : public FRigUnit_AnimNextUserEvent`  
_L167-182_
- reflection: `USTRUCT(meta=(DisplayName="PostPhysics", Keywords="End,After"))`
- inherits: `FRigUnit_AnimNextUserEvent`
- desc: Schedule event called after world physics is updated
- L171 _public member_ `static inline const FLazyName DefaultEventName = FLazyName("Pos`
- L173 _public function_ `FRigUnit_AnimNextPostPhysicsEvent()`
- L179 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L30 _function_ `virtual UE::UAF::FTickFunctionBindingFunction GetBindingFunction() const` (scope `FRigUnit_AnimNextModuleEventBase::GetBindingFunction`) — Overriden in derived classes to provide binding function

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/AnimNextActorLocatorFragment.h` (Internal)


#### struct `FAnimNextActorLocatorFragment`  
`struct FAnimNextActorLocatorFragment`  
_L11-34_
- reflection: `USTRUCT()`
- desc: Exposes the 'current' actor as a UOL fragment
- L15 _public prototype_ `FAnimNextActorLocatorFragment() = default;`
- L17 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FAnimNextActorLocatorFragment> FragmentType;`
- L29 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L30 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L31 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L32 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L33 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextActorLocatorFragment> : public TStructOpsTypeTraitsBase2<FAnimNextActorLocatorFragment>`  
_L37-43_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextActorLocatorFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L40-42_

#### Free symbols / members of external scopes

- L19 _function_ `friend uint32 GetTypeHash(const FAnimNextActorLocatorFragment& A)`
- L24 _function_ `friend bool operator==(const FAnimNextActorLocatorFragment& A, const FAnimNextActorLocatorFragment& B)`
- L41 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon9e14b84c0103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/AnimNextComponentLocatorFragment.h` (Internal)


#### struct `FAnimNextComponentLocatorFragment`  
`struct FAnimNextComponentLocatorFragment`  
_L12-41_
- reflection: `USTRUCT()`
- L16 _public prototype_ `FAnimNextComponentLocatorFragment() = default;`
- L18 _public prototype_ `explicit FAnimNextComponentLocatorFragment(TSubclassOf<UActorComponent> InClass);`
- L22 _public member_ `FSoftObjectPath Path;` — `UPROPERTY()` — Path to the component class
- L24 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FAnimNextComponentLocatorFragment> FragmentType;`
- L36 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L37 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L38 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L39 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L40 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextComponentLocatorFragment> : public TStructOpsTypeTraitsBase2<FAnimNextComponentLocatorFragment>`  
_L44-50_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextComponentLocatorFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L47-49_

#### Free symbols / members of external scopes

- L26 _function_ `friend uint32 GetTypeHash(const FAnimNextComponentLocatorFragment& A)`
- L31 _function_ `friend bool operator==(const FAnimNextComponentLocatorFragment& A, const FAnimNextComponentLocatorFragment& B)`
- L48 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon90ba2ee60103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/AnimNextObjectCastLocatorFragment.h` (Internal)


#### struct `FAnimNextObjectCastLocatorFragment`  
`struct FAnimNextObjectCastLocatorFragment`  
_L10-39_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FAnimNextObjectCastLocatorFragment() = default;`
- L16 _public prototype_ `explicit FAnimNextObjectCastLocatorFragment(UClass* InClass);`
- L20 _public member_ `FSoftObjectPath Path;` — `UPROPERTY()` — Path to the class to cast to
- L22 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FAnimNextObjectCastLocatorFragment> FragmentType;`
- L34 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L35 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L36 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L37 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L38 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextObjectCastLocatorFragment> : public TStructOpsTypeTraitsBase2<FAnimNextObjectCastLocatorFragment>`  
_L42-48_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextObjectCastLocatorFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L45-47_

#### Free symbols / members of external scopes

- L24 _function_ `friend uint32 GetTypeHash(const FAnimNextObjectCastLocatorFragment& A)`
- L29 _function_ `friend bool operator==(const FAnimNextObjectCastLocatorFragment& A, const FAnimNextObjectCastLocatorFragment& B)`
- L46 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonfd80acf50103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/AnimNextObjectFunctionLocatorFragment.h` (Internal)


#### struct `FAnimNextObjectFunctionLocatorFragment`  
`struct FAnimNextObjectFunctionLocatorFragment`  
_L10-39_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FAnimNextObjectFunctionLocatorFragment() = default;`
- L16 _public prototype_ `FAnimNextObjectFunctionLocatorFragment(UFunction* InFunction);`
- L20 _public member_ `FSoftObjectPath Path;` — `UPROPERTY()` — Path to the function
- L22 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FAnimNextObjectFunctionLocatorFragment> FragmentType;`
- L34 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L35 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L36 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L37 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L38 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextObjectFunctionLocatorFragment> : public TStructOpsTypeTraitsBase2<FAnimNextObjectFunctionLocatorFragment>`  
_L42-48_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextObjectFunctionLocatorFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L45-47_

#### Free symbols / members of external scopes

- L24 _function_ `friend uint32 GetTypeHash(const FAnimNextObjectFunctionLocatorFragment& A)`
- L29 _function_ `friend bool operator==(const FAnimNextObjectFunctionLocatorFragment& A, const FAnimNextObjectFunctionLocatorFragment& B)`
- L46 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon9d03ed300103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/AnimNextObjectPropertyLocatorFragment.h` (Internal)


#### struct `FAnimNextObjectPropertyLocatorFragment`  
`struct FAnimNextObjectPropertyLocatorFragment`  
_L10-43_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FAnimNextObjectPropertyLocatorFragment() = default;`
- L16 _public prototype_ `FAnimNextObjectPropertyLocatorFragment(TArrayView<FProperty*> InPropertyPath);`
- L20 _public member_ `TArray<TFieldPath<FProperty>> Path;` — `UPROPERTY()` — Path to the property, including any nested struct properties
- L22 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FAnimNextObjectPropertyLocatorFragment> FragmentType;`
- L34 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L35 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L36 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L37 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L38 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`
- L41 _private prototype_ `FObjectProperty* GetLeafProperty() const;`
- L42 _private prototype_ `UClass* GetRootClass() const;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextObjectPropertyLocatorFragment> : public TStructOpsTypeTraitsBase2<FAnimNextObjectPropertyLocatorFragment>`  
_L46-52_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextObjectPropertyLocatorFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L49-51_

#### Free symbols / members of external scopes

- L24 _function_ `friend uint32 GetTypeHash(const FAnimNextObjectPropertyLocatorFragment& A)`
- L29 _function_ `friend bool operator==(const FAnimNextObjectPropertyLocatorFragment& A, const FAnimNextObjectPropertyLocatorFragment& B)`
- L50 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anona1059a0f0103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/ParamUtils.h` (Internal)


#### struct `UE::UAF::FParamUtils`  
`struct FParamUtils`  
_L15-41_
- L20 _public prototype_ `static FParamCompatibility GetCompatibility(const FAnimNextParamType& InLHS, const FAnimNextParamType& InRHS);` — Check to see if a parameter handle is compatible with another. The order of the parameters imply directionality, e.g. IsCompatible((int64)InLHS, (int32)InRHS) is allowed as no data loss occurs, but IsCompatible((int32)InLHS, (int64)InRHS) is not as B could be truncated.
- L25 _public prototype_ `static bool CanUseFunction(const UFunction* InFunction, const UClass* InExpectedClass);` — Check whether the supplied function can be used to access/map parameters. Does not check type for validity. @param	InFunction	The function to check @param	InClass		The expected class to check - used to determine if hoisted functions are valid in this context.
- L31 _public prototype_ `static bool CanUseFunction(const UFunction* InFunction, const UClass* InExpectedClass, FAnimNextParamType& OutType);` — Check whether the supplied function can be used to access/map parameters. Checks type and returns it in OutType @param	InFunction		The function to check @param	InClass			The expected class to check - used to determine if hoisted functions are valid in this context. @param	OutType			Type of the function's return value
- L34 _public prototype_ `static bool CanUseProperty(const FProperty* InProperty);` — Check (via flags only) the supplied property can be used to access/map parameters
- L37 _public prototype_ `static bool CanUseProperty(const FProperty* InProperty, FAnimNextParamType& OutType);` — Check whether the supplied property can be used to access/map parameters. Checks type and returns it in OutType
- L40 _public prototype_ `static FName LocatorToName(const FUniversalObjectLocator& InLocator);` — Convert a UOL to an FName

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/RigUnit_AnimNextParameterBase.h` (Internal)


#### struct `FRigUnit_AnimNextParameterBase`  
`struct FRigUnit_AnimNextParameterBase : public FRigVMStruct`  
_L11-14_
- reflection: `USTRUCT(meta = (ExecuteContext = "FAnimNextExecuteContext"))`
- inherits: `FRigVMStruct`
- desc: Deprecated stub - remove once content is updated

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/RigUnit_AnimNextParameterBeginExecution.h` (Internal)


#### struct `FRigUnit_AnimNextParameterBeginExecution`  
`struct FRigUnit_AnimNextParameterBeginExecution : public FRigUnit_AnimNextParameterBase`  
_L13-33_
- reflection: `USTRUCT(meta=(DisplayName="Execute", Category="Events", NodeColor="1, 0, 0", Keywords="Begin,Update,Tick,Forward,Event"))`
- inherits: `FRigUnit_AnimNextParameterBase`
- desc: Deprecated stub - remove once content is updated
- L17 _public prototype_ `RIGVM_METHOD() void Execute();`
- L20 _public function_ `virtual FString GetUnitLabel() const override`
- L21 _public function_ `virtual FName GetEventName() const override`
- L22 _public function_ `virtual bool CanOnlyExistOnce() const override`
- L26 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "Entry Point", meta = (Output))` — The execution result
- L30 _public member_ `FName EntryPoint = DefaultEntryPoint;` — `UPROPERTY(VisibleAnywhere, Category = "Entry Point", meta = (Hidden))` — The name of the entry point
- L32 _public member_ `static FName DefaultEntryPoint;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/RigVMDispatch_GetLayerParameter.h` (Internal)


#### struct `FRigVMDispatch_GetLayerParameter`  
`struct FRigVMDispatch_GetLayerParameter : public FRigVMDispatchFactory`  
_L20-49_
- reflection: `USTRUCT(meta = (Deprecated, DisplayName = "Get Graph Parameter", Category="Parameters", NodeColor = "0.8, 0, 0.2, 1"))`
- inherits: `FRigVMDispatchFactory`
- desc: Gets a parameter's current value from the graph
- L24 _public prototype_ `FRigVMDispatch_GetLayerParameter();`
- L29 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const override`
- L30 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L31 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L33 _private prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L35 _private prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L36 _private function_ `virtual bool IsSingleton() const override`
- L38 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L42 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L44 _private member_ `static const FName ExecuteContextName;`
- L45 _private member_ `static const FName ParameterName;`
- L46 _private member_ `static const FName ParameterIdName;`
- L47 _private member_ `static const FName TypeHandleName;`
- L48 _private member_ `static const FName ValueName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/RigVMDispatch_GetParameter.h` (Internal)


#### struct `FRigVMDispatch_GetParameter`  
`struct FRigVMDispatch_GetParameter : public FRigVMDispatchFactory`  
_L20-50_
- reflection: `USTRUCT(meta = (Deprecated, DisplayName = "Get Parameter", Category="Parameters", NodeColor = "0.8, 0, 0.2, 1"))`
- inherits: `FRigVMDispatchFactory`
- desc: Gets a parameter's value
- L24 _public prototype_ `FRigVMDispatch_GetParameter();`
- L26 _public member_ `static const FName ParameterName;`
- L27 _public member_ `static const FName ValueName;`
- L32 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const`
- L33 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L34 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L36 _private prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L38 _private prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L39 _private function_ `virtual bool IsSingleton() const override`
- L41 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L45 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L47 _private member_ `static const FName ExecuteContextName;`
- L48 _private member_ `static const FName ParameterIdName;`
- L49 _private member_ `static const FName TypeHandleName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/RigVMDispatch_GetScopedParameter.h` (Internal)


#### struct `FRigVMDispatch_GetScopedParameter`  
`struct FRigVMDispatch_GetScopedParameter : public FRigVMDispatchFactory`  
_L25-54_
- reflection: `USTRUCT(meta = (Deprecated, DisplayName = "Get Parameter", Category="Parameters", NodeColor = "0.8, 0, 0.2, 1"))`
- inherits: `FRigVMDispatchFactory`
- desc: Gets a parameter's value
- L29 _public prototype_ `FRigVMDispatch_GetScopedParameter();`
- L35 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const`
- L36 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L37 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L39 _private prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L41 _private prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L42 _private function_ `virtual bool IsSingleton() const override`
- L44 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L48 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L50 _private member_ `static const FName ParameterName;`
- L51 _private member_ `static const FName ValueName;`
- L52 _private member_ `static const FName ParameterIdName;`
- L53 _private member_ `static const FName TypeHandleName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Param/RigVMDispatch_SetLayerParameter.h` (Internal)


#### struct `FRigVMDispatch_SetLayerParameter`  
`struct FRigVMDispatch_SetLayerParameter : public FRigVMDispatchFactory`  
_L20-50_
- reflection: `USTRUCT(meta=(Deprecated, DisplayName = "Set Graph Parameter", Category="Parameters", NodeColor = "0.8, 0, 0.2, 1"))`
- inherits: `FRigVMDispatchFactory`
- desc: Sets a parameter's value
- L24 _public prototype_ `FRigVMDispatch_SetLayerParameter();`
- L29 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const`
- L30 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L31 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L33 _private prototype_ `virtual FString GetArgumentMetaData(const FName& InArgumentName, const FName& InMetaDataKey) const override;`
- L35 _private prototype_ `virtual TArray<FRigVMExecuteArgument>& GetExecuteArguments_Impl(const FRigVMDispatchContext& InContext) const override;`
- L36 _private prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L37 _private function_ `virtual bool IsSingleton() const override`
- L39 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L43 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L45 _private member_ `static const FName ExecuteContextName;`
- L46 _private member_ `static const FName ParameterName;`
- L47 _private member_ `static const FName ParameterIdName;`
- L48 _private member_ `static const FName TypeHandleName;`
- L49 _private member_ `static const FName ValueName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/RigVMRuntimeDataRegistry.h` (Internal)


#### struct `UE::UAF::FRigVMRuntimeData`  
`struct FRigVMRuntimeData`  
_L16-19_
- L18 _public member_ `FRigVMExtendedExecuteContext Context;`

#### struct `UE::UAF::FRigVMRuntimeDataRegistry`  
`struct FRigVMRuntimeDataRegistry final`  
_L28-84_
- desc: RigVMRuntimeDataRegistry A global registry of all existing VMs that require TLS data instantiation
- L40 _public prototype_ `static TWeakPtr<FRigVMRuntimeData> FindOrAddLocalRuntimeData(const FRigVMRuntimeDataID& RigVMRuntimeDataID, const FRigVMExtendedExecuteContext& ReferenceContext);` — Finds or adds one VM runtime data instance for the passed ID in the TLS. If it exists and the Context hash is correct, returns the TLS weak pointer. If not found or the context hash is not correct, it creates a new instance in the Global storage and adds a Weak pointer to the TLS. @param RigVMRuntimeDataID The key to find or associate (if created) the instance with. @param ReferenceContext Reference context to copy data from (if not found or found but the context hash is not correct) @param bOutHasBeenUpdated Out : True If the ID did not exist or existed but the Context hash was not correct @return A weak pointer to the data as stored in the TLS map.
- L48 _public prototype_ `static TWeakPtr<FRigVMRuntimeData> FindLocalRuntimeData(const FRigVMRuntimeDataID& RigVMRuntimeDataID);` — Finds the instance VM runtime data ID in the TLS storage @param RigVMRuntimeDataID The key to find the associated data with. @return A pointer to the data as stored in the TLS map.
- L58 _public prototype_ `static TWeakPtr<FRigVMRuntimeData> AddRuntimeData(const FRigVMRuntimeDataID& RigVMRuntimeDataID, const FRigVMExtendedExecuteContext& ReferenceContext);` — Adds one VM runtime data instance for the passed ID in the Global storage and adds a Weak pointer to the TLS. Adding a new instance is only allowed if it does not already exist in the TLS @param RigVMRuntimeDataID The key to associate the data with. @param ReferenceContext Reference context to copy data from @return A weak pointer to the data as stored in the TLS map.
- L65 _public prototype_ `static void ReleaseAllVMRuntimeData(const FRigVMRuntimeDataID& RigVMRuntimeDataID);` — Destroys all the VM runtime data instances for the passed ID. This should be only called when the VM is destroyed. @param RigVMRuntimeDataID The key to find the associated data with.
- L68 _private prototype_ `static TSharedPtr<FRigVMRuntimeData> AddGlobalRuntimeData(const FRigVMRuntimeDataID& RigVMRuntimeDataID, const FRigVMExtendedExecuteContext& ReferenceContext);`
- L69 _private prototype_ `static void ReleaseAllGlobalRuntimeData(const FRigVMRuntimeDataID& RigVMRuntimeDataID);`
- L72 _private prototype_ `static void HandlePostGarbageCollect();` — Post GC callback to signal a compaction has to be done (and perform it on game thread)
- L75 _private prototype_ `static void PerformGlobalStorageCompaction();` — Checks if any of the stored VM datas have been deleted and removes deleted elements. Main thread only.
- L77 _private prototype_ `static void PerformLocalStorageCompaction();` — Checks if any of the stored VM datas have been deleted and removes deleted elements in the TLS storage.
- L80 _private prototype_ `static void Init();` — Module lifetime functions
- L81 _private prototype_ `static void Destroy();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L14 _typedef_ `using FRigVMRuntimeDataID = TObjectKey<URigVM>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Script/UAFAssetContextData.h` (Internal)


#### struct `FUAFAssetContextData`  
`struct FUAFAssetContextData : public FUAFScriptContextData`  
_L14-48_
- reflection: `USTRUCT()`
- inherits: `FUAFScriptContextData`
- desc: Context structure passed to script calls
- L18 _public prototype_ `FUAFAssetContextData() = default;`
- L20 _public function_ `FUAFAssetContextData(FUAFAssetInstance& InInstance, FName InEventName, float InDeltaTime) : FUAFScriptContextData(InEventName) , Instance(&InInstance) , DeltaTime(InDeltaTime)`
- L28 _public function_ `float GetDeltaTime() const` — Get the current delta time for this execution
- L34 _public function_ `FUAFAssetInstance& GetInstance() const` — Get the instance that is currently executing.
- L42 _private member_ `FUAFAssetInstance* Instance = nullptr;` — Instance that is currently executing.
- L45 _private member_ `float DeltaTime = 0.0f;` — The current delta time for this execution

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Script/UAFScriptContextData.h` (Internal)


#### struct `FUAFScriptContextData`  
`struct FUAFScriptContextData`  
_L11-30_
- reflection: `USTRUCT()`
- desc: Base context for all scripted events
- L15 _public prototype_ `FUAFScriptContextData() = default;`
- L17 _public function_ `explicit FUAFScriptContextData(FName InEventName) : EventName(InEventName)`
- L22 _public function_ `FName GetEventName() const` — Get the currently-executing event
- L29 _private member_ `FName EventName;` — The name of the event that is currently being executed

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/UAF/ValueRuntime/IVirtualValueBundle.h` (Internal)


#### class `UE::UAF::IVirtualValueBundle`  
`class IVirtualValueBundle`  
_L26-42_
- desc: Implementation of a value bundle 'virtual value' that can represent a number of underlying concepts, e.g.: - A concrete value bundle - A legacy LOD pose - The result of reading a referenced system's output - An inline or owned graph instance
- L29 _public prototype_ `virtual ~IVirtualValueBundle() = default;`
- L32 _public function_ `virtual const FAnimNextGraphLODPose* GetLODPose() const` — Get the LOD pose this bundle represents
- L35 _public function_ `virtual const FValueBundleHeap* GetValueBundle() const` — Get a value bundle - valid if this bundle is a concrete value
- L38 _public function_ `virtual const FWeakAnimGraphReference* GetAnimGraphReference() const` — Get an anim graph reference that represents a 'virtual' value bundle - i.e. the result of evaluating the graph in-line
- L41 _public function_ `virtual const FTraitPtr* GetInlineGraph() const` — Get an inline child ptr that represents a 'virtual' value bundle - i.e. the result of evaluating the graph fragment in-line

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/UAFLogging.h` (Internal)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UAF_RIGUNIT_LOG(Severity, Format, ...) \` — Calls Log on the existing ExecuteContext within the current RigVMStruct scope. This will either call the bound LogFunction on the ExecuteContext or fallback to a regular UE_LOG and automatically prefixes the function name to the message
- L14 _macro_ `#define UAF_TRAIT_LOG(Verbosity, Format, ...) \` — If logging is disabled, we follow UE_LOG's behavior and only log fatal messages

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/AnimNextFieldPath.h` (Internal)


#### struct `FAnimNextFieldPath`  
`struct FAnimNextFieldPath`  
_L9-15_
- reflection: `USTRUCT()`
- desc: Struct wrapper around TFieldPath, used to allow RigVM support
- L14 _public member_ `TFieldPath<FProperty> FieldPath;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/AnimNextSoftFunctionPtr.h` (Internal)


#### struct `FAnimNextSoftFunctionPtr`  
`struct FAnimNextSoftFunctionPtr`  
_L10-16_
- reflection: `USTRUCT()`
- desc: Struct wrapper around TSoftObjectPtr<UFunction>, used to allow RigVM support
- L15 _public member_ `TSoftObjectPtr<UFunction> SoftObjectPtr;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/AnimNextVariableOverridesCollection.h` (Internal)


#### struct `FAnimNextVariableOverridesCollection`  
`struct FAnimNextVariableOverridesCollection`  
_L16-35_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public function_ `TWeakPtr<const UE::UAF::FVariableOverridesCollection> GetOverrides() const` — Access the overrides for reading only
- L26 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`
- L34 _private member_ `TWeakPtr<UE::UAF::FVariableOverridesCollection> Collection;` — Overrides that this structure wraps - ownership is with a module/graph's execute context (held in work data)

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextVariableOverridesCollection> : public TStructOpsTypeTraitsBase2<FAnimNextVariableOverridesCollection>`  
_L38-44_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextVariableOverridesCollection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L41-43_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L42 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon50aa10d80103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/RigUnit_CopyModuleProxyVariables.h` (Internal)


#### struct `FRigUnit_CopyModuleProxyVariables`  
`struct FRigUnit_CopyModuleProxyVariables : public FRigUnit_AnimNextBase`  
_L12-24_
- reflection: `USTRUCT(meta=(Hidden, DisplayName = "Copy Proxy Variables", Category="Internal"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Synthetic node injected by the compiler to copy proxy variables to a module instance, not user instantiated
- L16 _public prototype_ `FRigUnit_CopyModuleProxyVariables() = default;`
- L18 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L23 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "Events", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/RigUnit_ResolveUniversalObjectLocator.h` (Internal)


#### struct `FRigUnit_ResolveUniversalObjectLocator`  
`struct FRigUnit_ResolveUniversalObjectLocator : public FRigUnit_AnimNextBase`  
_L13-29_
- reflection: `USTRUCT(meta=(Hidden, DisplayName = "Resolve Locator", Category="Internal"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Synthetic node injected by the compiler to resolve a UOL to an object, not user instantiated
- L17 _public prototype_ `FRigUnit_ResolveUniversalObjectLocator() = default;`
- L19 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L24 _public member_ `FUniversalObjectLocator Locator;` — `UPROPERTY(meta = (Input))` — The object locator to resolve
- L28 _public member_ `TObjectPtr<UObject> Object;` — `UPROPERTY(meta = (Output))` — The resulting resolved object

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/RigVMDispatch_CallHoistedAccessorFunction.h` (Internal)


#### struct `FRigVMDispatch_CallHoistedAccessorFunctionBase`  
`struct FRigVMDispatch_CallHoistedAccessorFunctionBase : public FRigVMDispatchFactory`  
_L13-30_
- reflection: `USTRUCT(meta = (Hidden, Category="Internal"))`
- inherits: `FRigVMDispatchFactory`
- desc: Synthetic dispatch injected by the compiler to get a value via a hoisted accessor UFunction, not user instantiated
- L17 _public prototype_ `FRigVMDispatch_CallHoistedAccessorFunctionBase();`
- L19 _public member_ `static inline const FLazyName ObjectName = FLazyName("Obj`
- L20 _public member_ `static inline const FLazyName FunctionName = FLazyName("Fun`
- L21 _public member_ `static inline const FLazyName ValueName = FLazyName("Val`
- L24 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const override`
- L25 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L26 _private prototype_ `virtual void RegisterDependencyTypes_NoLock(FRigVMRegistryHandle& InRegistry) const override;`
- L27 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L28 _private prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L29 _private function_ `virtual bool IsSingleton() const override`

#### struct `FRigVMDispatch_CallHoistedAccessorFunctionNative`  
`struct FRigVMDispatch_CallHoistedAccessorFunctionNative : public FRigVMDispatch_CallHoistedAccessorFunctionBase`  
_L34-46_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Call Hoisted Native Function"))`
- inherits: `FRigVMDispatch_CallHoistedAccessorFunctionBase`
- desc: Script function specialization of FRigVMDispatch_CallHoistedAccessorFunctionBase
- L38 _public prototype_ `FRigVMDispatch_CallHoistedAccessorFunctionNative();`
- L41 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L45 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`

#### struct `FRigVMDispatch_CallHoistedAccessorFunctionScript`  
`struct FRigVMDispatch_CallHoistedAccessorFunctionScript : public FRigVMDispatch_CallHoistedAccessorFunctionBase`  
_L50-62_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Call Hoisted Script Function"))`
- inherits: `FRigVMDispatch_CallHoistedAccessorFunctionBase`
- desc: Script function specialization of FRigVMDispatch_CallHoistedAccessorFunctionBase
- L54 _public prototype_ `FRigVMDispatch_CallHoistedAccessorFunctionScript();`
- L57 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L61 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/RigVMDispatch_CallObjectAccessorFunction.h` (Internal)


#### struct `FRigVMDispatch_CallObjectAccessorFunctionBase`  
`struct FRigVMDispatch_CallObjectAccessorFunctionBase : public FRigVMDispatchFactory`  
_L13-30_
- reflection: `USTRUCT(meta = (Hidden, Category="Internal"))`
- inherits: `FRigVMDispatchFactory`
- desc: Synthetic dispatch injected by the compiler to get a value via an accessor UFunction, not user instantiated
- L17 _public prototype_ `FRigVMDispatch_CallObjectAccessorFunctionBase();`
- L19 _public member_ `static inline const FLazyName ObjectName = FLazyName("Obj`
- L20 _public member_ `static inline const FLazyName FunctionName = FLazyName("Fun`
- L21 _public member_ `static inline const FLazyName ValueName = FLazyName("Val`
- L24 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const override`
- L25 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L26 _private prototype_ `virtual void RegisterDependencyTypes_NoLock(FRigVMRegistryHandle& InRegistry) const override;`
- L27 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L28 _private prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L29 _private function_ `virtual bool IsSingleton() const override`

#### struct `FRigVMDispatch_CallObjectAccessorFunctionNative`  
`struct FRigVMDispatch_CallObjectAccessorFunctionNative : public FRigVMDispatch_CallObjectAccessorFunctionBase`  
_L34-46_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Call Native Function"))`
- inherits: `FRigVMDispatch_CallObjectAccessorFunctionBase`
- desc: Script function specialization of FRigVMDispatch_CallObjectAccessorFunctionBase
- L38 _public prototype_ `FRigVMDispatch_CallObjectAccessorFunctionNative();`
- L41 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L45 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`

#### struct `FRigVMDispatch_CallObjectAccessorFunctionScript`  
`struct FRigVMDispatch_CallObjectAccessorFunctionScript : public FRigVMDispatch_CallObjectAccessorFunctionBase`  
_L50-62_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Call Script Function"))`
- inherits: `FRigVMDispatch_CallObjectAccessorFunctionBase`
- desc: Script function specialization of FRigVMDispatch_CallObjectAccessorFunctionBase
- L54 _public prototype_ `FRigVMDispatch_CallObjectAccessorFunctionScript();`
- L57 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L61 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/RigVMDispatch_GetObjectProperty.h` (Internal)


#### struct `FRigVMDispatch_GetObjectProperty`  
`struct FRigVMDispatch_GetObjectProperty : public FRigVMDispatchFactory`  
_L13-36_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Get Property", Category="Internal"))`
- inherits: `FRigVMDispatchFactory`
- desc: Synthetic dispatch injected by the compiler to get a value from an object's property, not user instantiated
- L17 _public prototype_ `FRigVMDispatch_GetObjectProperty();`
- L19 _public member_ `static inline const FLazyName ObjectName = FLazyName("Obj`
- L20 _public member_ `static inline const FLazyName PropertyName = FLazyName("Pro`
- L21 _public member_ `static inline const FLazyName ValueName = FLazyName("Val`
- L24 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const override`
- L25 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L26 _private prototype_ `virtual void RegisterDependencyTypes_NoLock(FRigVMRegistryHandle& InRegistry) const override;`
- L27 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L28 _private prototype_ `virtual FRigVMTemplateTypeMap OnNewArgumentType(const FName& InArgumentName, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const override;`
- L29 _private function_ `virtual bool IsSingleton() const override`
- L31 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L35 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/StructDataCache.h` (Internal)


#### struct `UE::UAF::FStructDataCache`  
`struct FStructDataCache`  
_L17-55_
- desc: Cache of struct data to allow for easy indexing of struct properties
- L20 _public prototype_ `static void Init();` — Initialize the cache
- L23 _public prototype_ `static void Destroy();` — Destroy the cache
- L26 _public prototype_ `static TSharedRef<FStructDataCache> GetStructInfo(const UScriptStruct* InStruct);` — Get/cache info about a struct
- L36 _public function_ `TConstArrayView<FPropertyInfo> GetProperties() const` — Access indexed property data
- L46 _private prototype_ `explicit FStructDataCache(const UScriptStruct* InStruct);`
- L48 _private prototype_ `void Rebuild();`
- L51 _private member_ `TWeakObjectPtr<const UScriptStruct> WeakStruct;` — The struct that this data is for
- L54 _private member_ `TArray<FPropertyInfo> Properties;` — Info about properties of a struct sorted by offset

#### struct `UE::UAF::FStructDataCache::FPropertyInfo`  
`struct FPropertyInfo`  
_L29-33_
- desc: Information about an indexed property in a struct
- L31 _public member_ `const FProperty* Property = nullptr;`
- L32 _public member_ `FAnimNextParamType Type;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::UAF`)
- L13 _prototype_ `void HandleLiveCodingPatchComplete();` (scope `UE::UAF::Private`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/UAFInstanceVariableContainer.h` (Internal)


#### struct `FUAFInstanceVariableContainer`  
`struct FUAFInstanceVariableContainer`  
_L34-126_
- reflection: `USTRUCT()`
- desc: A 'shared' variable container, either a user-defined FInstancedPropertyBag or a natively-defined struct wrapped in a FInstancedStruct Defines a block of asset data that: - Is owned by a particular asset instance - Is visible to nested instances (i.e. can be passed-by-reference or 'shared') - Can be overriden by nested instances
- L38 _public prototype_ `FUAFInstanceVariableContainer() = default;`
- L41 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);` — GC support
- L55 _private prototype_ `explicit FUAFInstanceVariableContainer(const FUAFAssetInstance& InHostInstance, const UScriptStruct* InStruct, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides = nullptr, int32 InOverridesIndex = INDEX_NONE);` — Construct from struct data, copying the defaults. Optional overrides provided.
- L58 _private prototype_ `explicit FUAFInstanceVariableContainer(const FUAFAssetInstance& InHostInstance, const UUAFRigVMAsset* InAsset, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides = nullptr, int32 InOverridesIndex = INDEX_NONE);` — Construct from an asset, copying the variables. Optional overrides provided.
- L61 _private prototype_ `explicit FUAFInstanceVariableContainer(const FUAFAssetInstance& InHostInstance, const IRigVMRuntimeAssetInterface* InAsset, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides = nullptr, int32 InOverridesIndex = INDEX_NONE);` — Construct from a IRigVMRuntimeAssetInterface, copying the variables. Optional overrides provided.
- L64 _private prototype_ `EPropertyBagResult GetVariable(int32 InVariableIndex, const FAnimNextParamType& InType, TArrayView<uint8> OutResult) const;` — Gets the value of the specified variable. If the type does not match exactly then a conversion will be attempted.
- L67 _private prototype_ `EPropertyBagResult AccessVariable(int32 InVariableIndex, const FAnimNextParamType& InType, TArrayView<uint8>& OutResult);` — Access the memory of the variable directly. Type must match strictly, no conversions are performed
- L70 _private prototype_ `EPropertyBagResult SetVariable(int32 InVariableIndex, const FAnimNextParamType& InType, TConstArrayView<uint8> InNewValue);` — Sets the value of the specified variable. If the type does not match exactly then a conversion will be attempted.
- L73 _private prototype_ `void GetAllVariablesOfType(const FAnimNextParamType& InType, TArray<FAnimNextVariableReference>& OutVariables) const;` — Find references to all variables of the specified type
- L76 _private prototype_ `bool ForEachVariable(TFunctionRef<bool(FName, const FAnimNextParamType&, int32)> InFunction, int32& InOutVariableIndex) const;` — Iterate over all variables calling InFunction
- L79 _private prototype_ `FAnimNextParamType GetVariableType(int32 InVariableIndex) const;` — Get the type of the variable at the specified index
- L82 _private prototype_ `void AccessVariableUnchecked(int32 InVariableIndex, const FProperty*& OutProperty, TArrayView<uint8>& OutResult);` — Unchecked, non-type converting version of AccessVariable
- L85 _private prototype_ `FName GetFName() const;` — Get the name of the underlying object (asset, struct etc) that this instance variable container is initialized from
- L89 _private prototype_ `void Migrate();` — Used during compilation, migrate all variables to new bags according to new defaults.
- L93 _private prototype_ `void ResolveOverrides();` — Resolve any overrides from an outer host
- L96 _private prototype_ `void GetRigVMMemoryForVariables(TConstArrayView<FRigVMExternalVariableDef> InVariableDefs, TArray<FRigVMExternalVariableRuntimeData>& OutRuntimeData);` — Indirect RigVM memory handles to either variables or overrides, filling the supplied array
- L99 _private member_ `const FUAFAssetInstance* HostInstance = nullptr;` — The instance that hosts these variables
- L102 _private typedef_ `using FAssetType = TObjectPtr<const UUAFRigVMAsset>;` — The asset or struct these variables came from, if any
- L103 _private typedef_ `using FStructType = TObjectPtr<const UScriptStruct>;`
- L104 _private typedef_ `using FRigVMAssetType = TScriptInterface<const IRigVMRuntimeAssetInterface>;`
- L105 _private typedef_ `using FAssetOrStructType = TVariant<FAssetType, FStructType, FRigVMAssetType>;`
- L106 _private member_ `FAssetOrStructType AssetOrStructData;`
- L109 _private typedef_ `using FVariablesContainerType = TVariant<FInstancedPropertyBag, FInstancedStruct>;` — Instance of the asset's variables or resolved overrides for the asset's variables
- L110 _private member_ `FVariablesContainerType VariablesContainer;`
- L113 _private member_ `TWeakPtr<const UE::UAF::FVariableOverridesCollection> Overrides;` — Cached overrides collection, if any are to be applied
- L116 _private member_ `int32 OverridesIndex = INDEX_NONE;` — Index into overrides collection to apply
- L119 _private member_ `TArray<uint8*> ResolvedOverrides;` — Cached resolved overrides derived from Overrides
- L122 _private member_ `TSharedPtr<UE::UAF::FStructDataCache> StructDataCache;` — Reference to cached struct data, if required
- L125 _private member_ `int32 NumVariables = 0;` — Cached variable count

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFInstanceVariableContainer> : public TStructOpsTypeTraitsBase2<FUAFInstanceVariableContainer>`  
_L129-135_
- inherits: `TStructOpsTypeTraitsBase2<FUAFInstanceVariableContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L132-134_

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L133 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon302982090103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/Variables/UAFInstanceVariableDataProxy.h` (Internal)


#### struct `FUAFInstanceVariableContainerProxy`  
`struct FUAFInstanceVariableContainerProxy : public FUAFInstanceVariableContainer`  
_L14-30_
- reflection: `USTRUCT()`
- inherits: `FUAFInstanceVariableContainer`
- L18 _public prototype_ `FUAFInstanceVariableContainerProxy() = default;`
- L20 _public prototype_ `explicit FUAFInstanceVariableContainerProxy(const FUAFInstanceVariableContainer& InVariables);`
- L23 _public prototype_ `EPropertyBagResult AccessVariableWithDirtyFlag(int32 InVariableIndex, const FAnimNextParamType& InType, TArrayView<uint8>& OutResult);` — Accesses the value of the specified variable, setting the dirty flag
- L26 _public prototype_ `EPropertyBagResult SetVariableWithDirtyFlag(int32 InVariableIndex, const FAnimNextParamType& InType, TConstArrayView<uint8> InNewValue);` — Sets the value of the specified variable, setting the dirty flag
- L29 _public member_ `TBitArray<> DirtyFlags;` — Dirty flags for each variable

#### struct `FUAFInstanceVariableDataProxy`  
`struct FUAFInstanceVariableDataProxy`  
_L37-77_
- reflection: `USTRUCT()`
- desc: Proxy struct for public variables for modules. Held double-buffered on module instances We double-buffer so updates to variables can occur during graph evaluation, with the actual update deferred to later. This double-buffering prevents read-back via the same mechanism at the time of writing @see FRigUnit_CopyModuleProxyVariables
- L42 _public prototype_ `void Initialize(const FUAFInstanceVariableData& InVariables);` — Sets up this proxy variable array from the supplied variables array
- L45 _public prototype_ `void Reset();` — Resets this proxy variables array to its default state
- L48 _public prototype_ `EPropertyBagResult WriteVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TArrayView<uint8>& OutResult);` — Access the memory of the variable directly for writing. Type must match strictly, no conversions are performed.
- L51 _public prototype_ `EPropertyBagResult SetVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InNewValue);` — Sets the value of the specified variable. If the type does not match exactly then a conversion will be attempted.
- L54 _public prototype_ `EPropertyBagResult AccessVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TArrayView<uint8>& OutValue);` — Access the memory of the variable directly. Type must match strictly, no conversions are performed.
- L57 _public prototype_ `bool WriteVariables(const UScriptStruct* InStruct, TFunctionRef<void(FStructView)> InFunction);` — Access the memory of the variables set directly for writing. All variables in the set are dirtied.
- L60 _public prototype_ `void CopyDirty();` — Copies any dirty variables over to the corresponding Variables
- L63 _public prototype_ `bool IsVariableDirty(const FAnimNextVariableReference& InVariable) const;` — Returns whether the variable has been marked as dirty
- L66 _public member_ `const FUAFInstanceVariableData* Variables = nullptr;` — Variables that this proxy corresponds to
- L70 _public member_ `TArray<FUAFInstanceVariableContainerProxy> ProxyVariableSets;` — `UPROPERTY()` — Proxy shared variable sets
- L73 _public member_ `TBitArray<> DirtyFlags;` — Dirty flags for each variable set
- L76 _public member_ `bool bIsDirty = false;` — Global dirty flag

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Graph/RigUnit_AnimNextRemapPose.h` (Private)


#### struct `FRigUnit_AnimNextRemapPose`  
`struct FRigUnit_AnimNextRemapPose : public FRigUnit_AnimNextBase`  
_L20-41_
- reflection: `USTRUCT(meta=(DisplayName="Remap Pose", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Output,Pose,Port"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Remaps an anim graph pose from to another skeletal mesh component. Note: Cross-skeleton remapping now happens automatically in FAnimNextGraphLODPose::CopyFrom and FKeyframeState::CopyFrom via the FRemapPoseDataPool. This node is only needed for explicit control over where remapping occurs in the system and might be deprecated later on.
- L24 _public prototype_ `RIGVM_METHOD() void Execute();`
- L29 _public member_ `FAnimNextGraphLODPose Pose;` — `UPROPERTY(EditAnywhere, DisplayName = "Input Pose", Category = "Graph", meta = (Input))` — Pose to read
- L32 _public member_ `FAnimNextGraphLODPose Result;` — `UPROPERTY(EditAnywhere, DisplayName = "Converted Pose", Category = "Graph", meta = (Output))`
- L35 _public member_ `FAnimNextGraphReferencePose TargetAnimGraphRefPose;` — `UPROPERTY(EditAnywhere, DisplayName = "Target Ref Pose", Category = "Graph", meta = (Input))`
- L39 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF RigUnit: Remap Pose"), STAT_AnimNext_RigUnit_RemapPose, STATGR`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Graph/RigUnit_AnimNextRetargetPose.h` (Private)


#### struct `FRetargetPoseData`  
`struct FRetargetPoseData`  
_L16-29_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `BoneTrackArray SkeletonPairs;`
- L21 _public member_ `BoneTrackArray AnimScalePairs;`
- L22 _public member_ `BoneTrackArray AnimRelativePairs;`
- L23 _public member_ `BoneTrackArray OrientAndScalePairs;`
- L27 _public member_ `int32 PairsInitForSourcePoseLOD = -1;` — Pairs initialized for the given source and target pose LODs. These are used to determine if we need to re-initialize the pairs after a LOD switch in either of the two poses.
- L28 _public member_ `int32 PairsInitForTargetPoseLOD = -1;`

#### struct `FRigUnit_AnimNextRetargetPose`  
`struct FRigUnit_AnimNextRetargetPose : public FRigUnit_AnimNextBase`  
_L33-55_
- reflection: `USTRUCT(meta=(DisplayName="Retarget Pose", Category="Animation Graph", NodeColor="1, 0, 1", Keywords="Output,Pose,Port"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Translational retargeting node.
- L37 _public prototype_ `RIGVM_METHOD() void Execute();`
- L41 _public member_ `FAnimNextGraphLODPose Pose;` — `UPROPERTY(EditAnywhere, DisplayName = "Source Pose", Category = "Graph", meta = (Input))`
- L44 _public member_ `FAnimNextGraphLODPose Result;` — `UPROPERTY(EditAnywhere, DisplayName = "Retargeted Pose", Category = "Graph", meta = (Output))`
- L47 _public member_ `FAnimNextGraphReferencePose TargetAnimGraphRefPose;` — `UPROPERTY(EditAnywhere, DisplayName = "Target Ref Pose", Category = "Graph", meta = (Input))`
- L51 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result
- L54 _public member_ `FRetargetPoseData RetargetPoseData;` — `UPROPERTY(meta = (Hidden))`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF RigUnit: Retarget Pose"), STAT_AnimNext_RigUnit_RetargetPose, STA`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Graph/RigUnit_GetActorTransform.h` (Private)


#### struct `FAnimNextActorTransformComponent`  
`struct FAnimNextActorTransformComponent : public FUAFModuleInstanceComponent`  
_L15-29_
- reflection: `USTRUCT()`
- inherits: `FUAFModuleInstanceComponent`
- desc: Module component used to marshal actor transform data for RigVM units to use
- L18 _public function_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT()`
- L25 _private prototype_ `virtual void OnBindToInstance() override;` — FUAFAssetInstanceComponent interface
- L28 _private member_ `FTransform ActorTransform = FTransform::Identity;` — Cached actor transform

#### struct `FRigUnit_GetActorTransform`  
`struct FRigUnit_GetActorTransform : public FRigUnit_AnimNextBase`  
_L33-45_
- reflection: `USTRUCT(meta=(DisplayName="Get Host Transform", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Actor, Transform", RequiredComponents="AnimNextActorTransformComponent"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Gets the transform of the actor hosting this AnimNext module
- L37 _public prototype_ `RIGVM_METHOD() void Execute();`
- L40 _public function_ `virtual FString GetUnitSubTitle() const`
- L44 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — The transform of our host actor

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Graph/RigUnit_GetSocketTransform.h` (Private)


#### struct `FRigUnit_GetSocketTransform`  
`struct FRigUnit_GetSocketTransform : public FRigUnit_AnimNextBase`  
_L13-35_
- reflection: `USTRUCT(meta=(DisplayName="Get Socket Transform", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Socket, Bone, Transform"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Returns the transform for the specified socket. Note that this is not thread-safe, so must be called at a point where you know that the target socket is not being updated.
- L17 _public prototype_ `RIGVM_METHOD() void Execute();`
- L22 _public member_ `TObjectPtr<USceneComponent> SceneComponent = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — The scene component to look up a socket transform for
- L26 _public member_ `FName SocketName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — The name of the socket transform to retrieve
- L30 _public member_ `TEnumAsByte<ERelativeTransformSpace> TransformSpace = ERelativeTransformSpace::RTS_World;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — The space to retrieve the transform in
- L34 _public member_ `FTransform Result = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — The resulting socket transform

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Graph/RigUnit_IsAnimBPDriven.h` (Private)


#### struct `FRigUnit_IsAnimBPDriven`  
`struct FRigUnit_IsAnimBPDriven : public FRigUnit_AnimNextBase`  
_L12-26_
- reflection: `USTRUCT(meta = (DisplayName = "Is AnimBP Driven", Category = "Mesh", NodeColor = "0, 1, 1", Keywords = "Mesh"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Gets whether or not a skeletal mesh component is being driven by an Animation Blueprint
- L16 _public prototype_ `RIGVM_METHOD() void Execute();`
- L21 _public member_ `TObjectPtr<USkeletalMeshComponent> MeshComponent;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — The mesh component to check
- L25 _public member_ `bool Result = false;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — True if the skeletal mesh component is being driven by an Animation Blueprint

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Graph/RigUnit_IsRecentlyRendered.h` (Private)


#### struct `FRigUnit_IsRecentlyRendered`  
`struct FRigUnit_IsRecentlyRendered : public FRigUnit_AnimNextBase`  
_L12-26_
- reflection: `USTRUCT(meta = (DisplayName = "Is Recently Rendered", Category = "Mesh", NodeColor = "0, 1, 1", Keywords = "Mesh"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Gets recently rendered flag from the input skinned mesh component
- L16 _public prototype_ `RIGVM_METHOD() void Execute();`
- L21 _public member_ `TObjectPtr<USkinnedMeshComponent> MeshComponent;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Mesh to query
- L25 _public member_ `bool Result = false;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — The recently rendered flag of the input mesh

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Graph/RigUnit_MakeReferencePoseFromSkeletalMeshComponent.h` (Private)


#### struct `FRigUnit_MakeReferencePoseFromSkeletalMeshComponent`  
`struct FRigUnit_MakeReferencePoseFromSkeletalMeshComponent : public FRigUnit_AnimNextBase`  
_L13-33_
- reflection: `USTRUCT(meta=(DisplayName="Make Reference Pose", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Output,Pose,Port", RequiredComponents="AnimNextSkeletalMeshComponentReferenceComponent"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Makes a reference pose from a skeletal mesh component
- L17 _public prototype_ `RIGVM_METHOD() void Execute();`
- L20 _public function_ `virtual FString GetUnitSubTitle() const`
- L24 _public member_ `FAnimNextGraphReferencePose ReferencePose;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input, Output))` — Reference pose to write
- L28 _public member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Mesh to use to generate the reference pose. If this is not supplied, then the first skeletal mesh component of the current actor will be used
- L32 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Module/RigVMTrait_ModuleEventDependency_ActorComponentClassPrimaryTickFunction.h` (Private)


#### struct `FRigVMTrait_ModuleEventDependency_ActorComponentClassPrimaryTickFunction`  
`struct FRigVMTrait_ModuleEventDependency_ActorComponentClassPrimaryTickFunction : public FRigVMTrait_ModuleEventDependency`  
_L13-29_
- reflection: `USTRUCT(DisplayName="Actor Component by Class", meta=(ShowTooltip=true))`
- inherits: `FRigVMTrait_ModuleEventDependency`
- desc: A dependency on the primary tick function of the first-found actor component of the specified class
- L19 _public prototype_ `virtual FString GetDisplayName() const override;`
- L23 _public prototype_ `virtual void OnAddDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;` — FAnimNextModuleEventDependency interface
- L24 _public prototype_ `virtual void OnRemoveDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;`
- L28 _public member_ `TSubclassOf<UActorComponent> ComponentClass;` — `UPROPERTY(EditAnywhere, Category = "Dependency")` — The component class to look for when establishing the dependency

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Module/RigVMTrait_ModuleEventDependency_ActorComponentPrimaryTickFunction.h` (Private)


#### struct `FRigVMTrait_ModuleEventDependency_ActorComponentPrimaryTickFunction`  
`struct FRigVMTrait_ModuleEventDependency_ActorComponentPrimaryTickFunction : public FRigVMTrait_ModuleEventDependency`  
_L12-28_
- reflection: `USTRUCT(DisplayName="Actor Component", meta=(ShowTooltip=true))`
- inherits: `FRigVMTrait_ModuleEventDependency`
- desc: A dependency on an actor component's primary tick function
- L18 _public prototype_ `virtual FString GetDisplayName() const override;`
- L22 _public prototype_ `virtual void OnAddDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;` — FAnimNextModuleEventDependency interface
- L23 _public prototype_ `virtual void OnRemoveDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;`
- L27 _public member_ `TObjectPtr<UActorComponent> Component;` — `UPROPERTY(EditAnywhere, Category = "Dependency")` — The component on whose primary tick function we will depend

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Module/RigVMTrait_ModuleEventDependency_ActorPrimaryTickFunction.h` (Private)


#### struct `FRigVMTrait_ModuleEventDependency_ActorPrimaryTickFunction`  
`struct FRigVMTrait_ModuleEventDependency_ActorPrimaryTickFunction : public FRigVMTrait_ModuleEventDependency`  
_L12-24_
- reflection: `USTRUCT(DisplayName="Actor", meta=(ShowTooltip=true))`
- inherits: `FRigVMTrait_ModuleEventDependency`
- desc: A dependency on the primary tick function of the host actor
- L18 _public prototype_ `virtual FString GetDisplayName() const override;`
- L22 _public prototype_ `virtual void OnAddDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;` — FAnimNextModuleEventDependency interface
- L23 _public prototype_ `virtual void OnRemoveDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Param/AnimNextWorldLibrary.h` (Private)


#### class `UAnimNextWorldLibrary`  
`class UAnimNextWorldLibrary : public UBlueprintFunctionLibrary`  
_L14-34_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Access to non-UProperty/UFunction data on UWorld
- L21 _public prototype_ `static double GetTimeSeconds(UWorld* InWorld);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)` — Returns time in seconds since world was brought up for play, IS stopped when game pauses, IS dilated/clamped
- L25 _public prototype_ `static double GetUnpausedTimeSeconds(UWorld* InWorld);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)` — Returns time in seconds since world was brought up for play, IS NOT stopped when game pauses, IS dilated/clamped
- L29 _public prototype_ `static double GetRealTimeSeconds(UWorld* InWorld);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)` — Returns time in seconds since world was brought up for play, does NOT stop when game pauses, NOT dilated/clamped
- L33 _public prototype_ `static float GetDeltaSeconds(UWorld* InWorld);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)` — Returns the frame delta time in seconds adjusted by e.g. time dilation.

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/RewindDebugger/RewindDebuggerUAFRuntime.h` (Private)


#### class `UE::UAF::FRewindDebuggerUAFRuntime`  
`class FRewindDebuggerUAFRuntime : public IRewindDebuggerRuntimeExtension`  
_L14-21_
- inherits: `IRewindDebuggerRuntimeExtension`
- L17 _public prototype_ `virtual void RecordingStarted() override;`
- L18 _public prototype_ `virtual void RecordingStopped() override;`
- L20 _public prototype_ `virtual void Clear() override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/UAF/AbstractSkeleton/Utils.h` (Private)


#### struct `UE::UAF::Util::SortByProperty::Node`  
`struct Node`  
_L13-24_
- L15 _public member_ `FName AttributeName;`
- L16 _public member_ `TArray<FName> Children;`
- L17 _public member_ `int32 InDegree;`
- L19 _public function_ `Node(const FName InAttributeName) : AttributeName(InAttributeName) , InDegree(0)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Util` (scope `UE::UAF`)
- L11 _function_ `template <typename ArrayType> void SortByProperty(TArray<ArrayType>& Array, FName ArrayType::* NameProperty, FName ArrayType::* ParentNameProperty, TFunctionRef<ArrayType* (FName)> FindArrayItem)` (scope `UE::UAF::Util`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/UAF/ValueRuntime/VirtualValueBundle_ComponentOutput.h` (Private)


#### struct `UE::UAF::FVirtualValueBundle_ComponentOutput`  
`struct FVirtualValueBundle_ComponentOutput : public IVirtualValueBundle`  
_L18-32_
- inherits: `IVirtualValueBundle`
- L20 _public function_ `explicit FVirtualValueBundle_ComponentOutput(TWeakObjectPtr<USkeletalMeshComponent> InWeakSMC) : WeakSMC(InWeakSMC)`
- L26 _private prototype_ `virtual const FAnimNextGraphLODPose* GetLODPose() const override;` — IVirtualValueBundle interface
- L27 _private prototype_ `virtual const FValueBundleHeap* GetValueBundle() const override;`
- L29 _private member_ `mutable FAnimNextGraphLODPose CachedPose;`
- L30 _private member_ `mutable FValueBundleHeap CachedValueBundle;`
- L31 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> WeakSMC;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAF_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/UAF/ValueRuntime/VirtualValueBundle_SystemOutput.h` (Private)


#### struct `UE::UAF::FVirtualValueBundle_SystemOutput`  
`struct FVirtualValueBundle_SystemOutput : public IVirtualValueBundle`  
_L15-33_
- inherits: `IVirtualValueBundle`
- L17 _public function_ `explicit FVirtualValueBundle_SystemOutput(const FUAFWeakSystemReference& InSystemReference) : SystemReference(InSystemReference)`
- L23 _private prototype_ `virtual const FAnimNextGraphLODPose* GetLODPose() const override;` — IVirtualValueBundle interface
- L24 _private prototype_ `virtual const FValueBundleHeap* GetValueBundle() const override;`
- L27 _private prototype_ `void ReadSystemOutput() const;` — Read the output value bundle of the system
- L29 _private member_ `mutable FAnimNextGraphLODPose CachedPose;`
- L30 _private member_ `mutable FValueBundleHeap CachedValueBundle;`
- L31 _private member_ `FUAFWeakSystemReference SystemReference;`
- L32 _private member_ `mutable uint32 SerialNumber = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Variables/RigUnit_OverrideVariables.h` (Private)


#### class `UAnimNextOverrideVariablesMenuContext`  
`class UAnimNextOverrideVariablesMenuContext : public UObject`  
_L17-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public member_ `TObjectPtr<URigVMController> Controller = nullptr;`
- L22 _public member_ `TObjectPtr<URigVMNode> Node = nullptr;`

#### struct `FAnimNextOverrideVariablesWorkData`  
`struct FAnimNextOverrideVariablesWorkData`  
_L26-32_
- reflection: `USTRUCT()`
- L31 _public member_ `TSharedPtr<UE::UAF::FVariableOverridesCollection> Collection;` — Strong reference held in work data

#### struct `FRigUnit_OverrideVariables`  
`struct FRigUnit_OverrideVariables : public FRigUnit_AnimNextBase`  
_L36-52_
- reflection: `USTRUCT(meta = (DisplayName = "Override Variables", NodeColor="0, 1, 1", Category="Variables"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Hosts a number of traits that allow overrides of variables for specific assets/structs
- L40 _public prototype_ `RIGVM_METHOD() void Execute();`
- L44 _public prototype_ `virtual TArray<FRigVMUserWorkflow> GetSupportedWorkflows(const UObject* InSubject) const override;` — FRigVMStruct interface
- L48 _public member_ `FAnimNextVariableOverridesCollection Overrides;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta = (Output))` — Variable overrides to be applied to subgraphs
- L51 _public member_ `FAnimNextOverrideVariablesWorkData WorkData;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Variables/RigVMTrait_OverrideVariables.h` (Private)


#### struct `FAnimNextVariableOverrideInfo`  
`struct FAnimNextVariableOverrideInfo`  
_L20-40_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Override info for a single variable
- L24 _public prototype_ `FAnimNextVariableOverrideInfo() = default;`
- L26 _public function_ `FAnimNextVariableOverrideInfo(FName InName, const FAnimNextParamType& InType, const FString& InDefaultValue) : Name(InName) , Type(InType) , DefaultValue(InDefaultValue)`
- L33 _public member_ `FName Name = "Va` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L36 _public member_ `FAnimNextParamType Type = FAnimNextParamType(FAnimNextParamType::EValueType::Bool);` — `UPROPERTY(EditAnywhere, Category = "Variables")`
- L39 _public member_ `FString DefaultValue;` — `UPROPERTY()`

#### struct `FRigVMTrait_OverrideVariables`  
`struct FRigVMTrait_OverrideVariables : public FRigVMTrait`  
_L44-60_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FRigVMTrait`
- desc: A trait that allows insertion of specific asset/struct variable overrides onto an override variables node
- L50 _public prototype_ `virtual void GetProgrammaticPins(URigVMController* InController, int32 InParentPinIndex, const URigVMPin* InTraitPin, const FString& InDefaultValue, FRigVMPinInfoArray& OutPinArray) const override;`
- L51 _public prototype_ `virtual bool ShouldCreatePinForProperty(const FProperty* InProperty) const override;`
- L55 _public function_ `virtual void GenerateOverrides(const FRigVMTraitScope& InTraitScope, TArray<UE::UAF::FVariableOverrides>& OutOverrides) const` — Override point for derived types to generate overrides
- L59 _public member_ `TArray<FAnimNextVariableOverrideInfo> Overrides;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta=(Input, DetailsOnly, TitleProperty = "Name"))` — Cached override data

#### struct `FRigVMTrait_OverrideVariablesForAsset`  
`struct FRigVMTrait_OverrideVariablesForAsset : public FRigVMTrait_OverrideVariables`  
_L66-78_
- reflection: `USTRUCT()`
- inherits: `FRigVMTrait_OverrideVariables`
- desc: A trait to generate overrides for an asset
- L71 _public prototype_ `virtual FString GetDisplayName() const override;`
- L73 _public prototype_ `virtual void GenerateOverrides(const FRigVMTraitScope& InTraitScope, TArray<UE::UAF::FVariableOverrides>& OutOverrides) const override;`
- L77 _public member_ `TObjectPtr<const UUAFRigVMAsset> Asset;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta=(Input, Constant, DetailsOnly))` — The asset to use to generate overrides

#### struct `FRigVMTrait_OverrideVariablesForStruct`  
`struct FRigVMTrait_OverrideVariablesForStruct : public FRigVMTrait_OverrideVariables`  
_L84-96_
- reflection: `USTRUCT()`
- inherits: `FRigVMTrait_OverrideVariables`
- desc: A trait to generate overrides for a a struct
- L89 _public prototype_ `virtual FString GetDisplayName() const override;`
- L91 _public prototype_ `virtual void GenerateOverrides(const FRigVMTraitScope& InTraitScope, TArray<UE::UAF::FVariableOverrides>& OutOverrides) const override;`
- L95 _public member_ `TObjectPtr<const UScriptStruct> Struct;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta=(Input, Constant, DetailsOnly))` — The asset to use to generate overrides

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Variables/VariableOverrides.h` (Private)


#### struct `UE::UAF::FVariableOverrides`  
`struct FVariableOverrides`  
_L21-84_
- desc: Information about a set of variable overrides. These supply an indirection for variables to host RigVM memory handle memory. We always ensure we override the 'whole asset's variables' so we adhere to copy-in rules when running inner instances
- L44 _public prototype_ `FVariableOverrides(const UUAFRigVMAsset* InAsset, TArray<FOverride>&& InOverrides);` — Construct a set of overrides for an asset
- L47 _public prototype_ `FVariableOverrides(const UScriptStruct* InStruct, TArray<FOverride>&& InOverrides);` — Construct a set of overrides for a struct
- L50 _public prototype_ `FVariableOverrides(const IRigVMRuntimeAssetInterface* InRigVMAsset, TArray<FOverride>&& InOverrides);` — Construct a set of overrides for a IRigVMRuntimeAssetInterface
- L52 _public function_ `bool IsOverrideFor(const UUAFRigVMAsset* InAsset) const`
- L58 _public function_ `bool IsOverrideFor(const UScriptStruct* InStruct) const`
- L64 _public function_ `bool IsOverrideFor(const IRigVMRuntimeAssetInterface* InRigVMAsset) const`
- L76 _private typedef_ `using FAssetType = TObjectPtr<const UUAFRigVMAsset>;` — Asset or struct to override variables for
- L77 _private typedef_ `using FStructType = TObjectPtr<const UScriptStruct>;`
- L78 _private typedef_ `using FRigVMAssetType = TScriptInterface<const IRigVMRuntimeAssetInterface>;`
- L79 _private typedef_ `using FAssetOrStructType = TVariant<FAssetType, FStructType, FRigVMAssetType>;`
- L80 _private member_ `FAssetOrStructType AssetOrStructData;`
- L83 _private member_ `TArray<FOverride> Overrides;` — Individual variable overrides

#### struct `UE::UAF::FVariableOverrides::FOverride`  
`struct FOverride`  
_L24-41_
- desc: Override for a specific variable
- L26 _public function_ `FOverride(FName InName, const FAnimNextParamType& InType, uint8* InMemory) : Name(InName) , Type(InType) , Memory(InMemory)`
- L33 _public member_ `FName Name;` — The name of the variable
- L36 _public member_ `FAnimNextParamType Type;` — The type of the variable
- L40 _public member_ `uint8* Memory = nullptr;` — Ptr to the variable's memory override. This should be owned by the outer scope (i.e. its lifetime should match) that is supplying the shared variable

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Private/Variables/VariableOverridesCollection.h` (Private)


#### struct `UE::UAF::FVariableOverridesCollection`  
`struct FVariableOverridesCollection`  
_L11-14_
- desc: A collection of overrides for asset/struct variables
- L13 _public member_ `TArray<FVariableOverrides> Collection;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/AnimNextFunctionHandle.h` (Public)


#### struct `UE::UAF::FFunctionHandle`  
`struct FFunctionHandle`  
_L13-36_
- desc: Opaque handle that can be used to call RigVM functions on UUAFRigVMAsset
- L16 _public function_ `bool IsValid() const` — Check to see if this is a valid handle
- L23 _public function_ `bool IsValidForVM(uint32 InVMHash) const` — Check to see if this is a valid handle and that it can be used for the specified VM (hash comparison)
- L32 _private member_ `int32 FunctionIndex = INDEX_NONE;`
- L34 _private member_ `uint32 VMHash = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/AnimNextFunctionReference.h` (Public)


#### struct `FAnimNextFunctionReference`  
`struct FAnimNextFunctionReference`  
_L19-109_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public prototype_ `FAnimNextFunctionReference() = default;`
- L26 _public prototype_ `static FAnimNextFunctionReference FromHeader(const FRigVMGraphFunctionHeader& InHeader, const UObject* InAsset);` — Construct a reference from a function header and owning asset. Stores the GUID for rename robustness.
- L30 _public prototype_ `static FAnimNextFunctionReference FromEventName(FName InEventName, const UObject* InAsset);`
- L34 _public function_ `const FGuid& GetFunctionGuid() const` — Get the stable function GUID (survives renames). Invalid for old serialized data.
- L38 _public function_ `FName GetEventName() const` — Get the mangled event name (editor only, used for display fallback).
- L42 _public function_ `TObjectPtr<const UObject> GetObject() const` — Get the asset that owns the function.
- L45 _public function_ `bool IsNone() const` — Check whether this can ever refer to a valid function.
- L55 _public function_ `void Reset()` — Reset this reference to None.
- L64 _public function_ `bool operator==(const FAnimNextFunctionReference& Other) const`
- L77 _public function_ `bool operator!=(const FAnimNextFunctionReference& Other) const`
- L98 _private member_ `FGuid FunctionGuid;` — `UPROPERTY(EditAnywhere, Category = "Function")` — Stable GUID identifying the function (survives renames). Invalid for legacy data.
- L103 _private member_ `FName EventName;` — `UPROPERTY(EditAnywhere, Category = "Function")` — The mangled event name (editor only, used for display fallback with legacy data).
- L108 _private member_ `TObjectPtr<const UObject> Object;` — `UPROPERTY(EditAnywhere, Category = "Function")` — The asset that owns the function.

#### Free symbols / members of external scopes

- L82 _function_ `friend uint32 GetTypeHash(const FAnimNextFunctionReference& Key)`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/AnimNextPoolHandle.h` (Public)


#### struct `UE::UAF::TPoolHandle`  
`template<typename ElementType> struct TPoolHandle`  
_L16-40_
- desc: Generational handle to a TPool entry
- L19 _private member_ `uint32 Index = MAX_uint32;`
- L20 _private member_ `uint32 SerialNumber = 0;`
- L24 _public function_ `void Reset()`
- L29 _public function_ `uint64 GetUniqueId() const`
- L31 _public function_ `bool IsValid() const`
- L36 _public function_ `bool operator==(const TPoolHandle& InOther) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/AnimNextRigVMAsset.h` (Public)


#### enum `EAnimNextRigVMAssetState`  
`enum class EAnimNextRigVMAssetState : uint8`  
_L50-56_
- reflection: `UENUM(BlueprintType)`
- L52 _public enumerator_ `CompiledWithErrors`
- L53 _public enumerator_ `CompiledWithWarnings`
- L54 _public enumerator_ `CompiledWithSuccess`
- L55 _public enumerator_ `Invalid`

#### class `UUAFRigVMAsset`  
`class UUAFRigVMAsset : public URigVMHost`  
_L61-186_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `URigVMHost`
- desc: Base class for all AnimNext assets that can host RigVM logic
- L84 _protected prototype_ `UUAFRigVMAsset(const FObjectInitializer& ObjectInitializer);`
- L87 _protected prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L88 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L89 _protected prototype_ `virtual void PostLoad() override;`
- L90 _protected prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L91 _protected prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L95 _public function_ `const FInstancedPropertyBag& GetVariableDefaults() const` — Get variable defaults property bag
- L98 _public function_ `const URigVM* GetRigVM() const` — Get the RigVM object we host
- L101 _public prototype_ `void CallFunctionHandle(UE::UAF::FFunctionHandle InHandle, FRigVMExtendedExecuteContext& InContext, FInstancedPropertyBag& InArgs);` — Call a function handle using a property bag as arguments.
- L105 _public prototype_ `bool ExecuteParameterlessFunction(UE::UAF::FFunctionHandle InHandle, FRigVMExtendedExecuteContext& InContext, void* OutReturnValue, int32 ReturnValueSize);` — Execute a parameterless function and copy its return value into OutReturnValue. The function must have exactly 1 arg (the return value output). Returns true on success.
- L108 _public prototype_ `UE::UAF::FFunctionHandle GetFunctionHandle(const FGuid& InFunctionGuid) const;` — Get a function handle given its stable GUID
- L111 _public prototype_ `UE::UAF::FFunctionHandle GetFunctionHandle(FName InEventName) const;` — Get a function handle given its mangled event name (backward compat)
- L115 _public typedef_ `using FOnCompileJobEvent = TTSMulticastDelegate<void(UUAFRigVMAsset*)>;` — Delegate called in editor when an asset's compilation has started (i.e. asset data that instances rely on is going to change)
- L116 _public prototype_ `static FOnCompileJobEvent& OnCompileJobStarted();`
- L119 _public prototype_ `static FOnCompileJobEvent& OnCompileJobFinished();` — Delegate called in editor when an asset's compilation has finished (and instances can be re-allocated)
- L123 _public function_ `TConstArrayView<TObjectPtr<const UUAFRigVMAsset>> GetReferencedVariableAssets() const` — Get all the assets whose variables we will reference/instance at runtime
- L126 _public function_ `TConstArrayView<TObjectPtr<const UScriptStruct>> GetReferencedVariableStructs() const` — Get all the native structs whose variables we will reference/instance at runtime
- L129 _public function_ `TConstArrayView<TScriptInterface<const IRigVMRuntimeAssetInterface>> GetReferencedVariableRigVMAssets() const` — Get all the IRigVMRuntimeAssetInterfaces whose variables we will reference/instance at runtime
- L133 _private prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariablesImpl(bool bFallbackToBlueprint) const;` — URigVMHost interface
- L141 _protected member_ `FRigVMExtendedExecuteContext ExtendedExecuteContext;` — `UPROPERTY(Transient)` — The ExtendedExecuteContext object holds the common work data used by the RigVM internals. It is populated during the initial VM initialization. Each instance of an AnimGraph requires a copy of this context and a call to initialize the VM instance with the context copy, so the cached memory handles are updated to the correct memory addresses. This context is used as a reference to copy the common data for all instances created.
- L144 _protected member_ `TObjectPtr<URigVM> RigVM;` — `UPROPERTY()`
- L148 _protected member_ `FInstancedPropertyBag VariableDefaults;` — `UPROPERTY()` — Variables and their defaults (including public variables, sorted first)
- L153 _protected member_ `FInstancedPropertyBag CombinedPropertyBag;` — `UPROPERTY()` — Variables property bag (including all variables from referenced assets, as external variables need stable property ptrs). Default values are not valid, this is just stored here for FProperty stability
- L157 _protected member_ `TArray<TObjectPtr<const UUAFRigVMAsset>> ReferencedVariableAssets;` — `UPROPERTY()` — All the assets whose variables we will reference/instance at runtime
- L161 _protected member_ `TArray<TObjectPtr<const UScriptStruct>> ReferencedVariableStructs;` — `UPROPERTY()` — All the native structs whose variables we will reference/instance at runtime
- L165 _protected member_ `TArray<TScriptInterface<const IRigVMRuntimeAssetInterface>> ReferencedVariableRigVMAssets;` — `UPROPERTY()` — All the IRigVMRuntimeAssetInterface whose variables we will reference/instance at runtime
- L169 _protected member_ `TArray<FAnimNextRigVMFunctionData> FunctionData;` — `UPROPERTY()` — All the natively-callable RigVM functions
- L173 _protected member_ `FAnimNextVariableReference DefaultInjectionSite;` — `UPROPERTY()` — Reference to the default injection site
- L177 _protected member_ `TArray<TInstancedStruct<FUAFAssetInstanceComponent>> Components;` — `UPROPERTY()` — Default components that are required for instances of this asset
- L181 _protected member_ `TObjectPtr<UObject> EditorData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Editor Data", meta = (ShowInnerProperties))`
- L184 _protected member_ `EAnimNextRigVMAssetState CompilationState = EAnimNextRigVMAssetState::CompiledWithSuccess;` — `UPROPERTY(transient)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UAF` (scope `UE`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace UAF` (scope `UE`)
- L37 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace UAF` (scope `UE`)
- L42 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/AnimNextStats.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_STATS_GROUP(TEXT("UAF"), STATGROUP_AnimNext, STATCAT_Advance`
- L9 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Module Event Tick"), STAT_AnimNext_Module_EventTick, STATGRO`
- L10 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Module End Tick"), STAT_AnimNext_Module_EndTick, STATGROUP`
- L12 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Initialize Instance"), STAT_AnimNext_InitializeInstance, STATG`
- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Create Instance Data"), STAT_AnimNext_CreateInstanceData, STAT`
- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Make RefPose"), STAT_AnimNext_Make_RefPose, STATGROUP_An`
- L16 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Write Pose"), STAT_AnimNext_Write_Pose, STATGROUP_Anim`
- L18 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Copy Transforms (SoA)"), STAT_AnimNext_CopyTransforms_SoA, STA`
- L19 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Normalize Rotations (SoA)"), STAT_AnimNext_NormalizeRotations_SoA,`
- L20 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Blend Overwrite (SoA)"), STAT_AnimNext_BlendOverwrite_SoA, STA`
- L21 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Blend Accumulate (SoA)"), STAT_AnimNext_BlendAccumulate_SoA, ST`
- L23 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Generate Reference Pose"), STAT_AnimNext_GenerateReferencePose, S`
- L24 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Remap Pose (From AnimBP)"), STAT_AnimNext_RemapPose_FromAnimBP,`
- L25 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Remap Pose (To AnimBP)"), STAT_AnimNext_RemapPose_ToAnimBP, ST`
- L26 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Remap Pose (To LocalTransforms)"), STAT_AnimNext_RemapPose_ToLocalTrans`
- L27 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Remap Pose (Mesh->Mesh)"), STAT_AnimNext_RemapPose_Mesh2Mesh, S`
- L28 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Convert Local Space To Component Space"), STAT_AnimNext_ConvertLocalSpaceToCo`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/BindableValue/UAFBindableTypes.h` (Public)


#### struct `FBindableValueBase`  
`struct FBindableValueBase`  
_L27-116_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Base struct for all strongly-typed bindable value wrappers. Each concrete subclass (FBindableBool, FBindableFloat, etc.) co-locates a constant fallback value with an optional runtime Binding. Call HasBinding() to check whether a binding is set. To read the resolved value at runtime, call GetValue(Instance): - If Instance is null or no binding is set, returns ConstantValue (the fallback). - Otherwise resolves the binding against the given FUAFAssetInstance, falling back to ConstantValue on failure.
- L31 _public prototype_ `FBindableValueBase() = default;`
- L32 _public prototype_ `~FBindableValueBase() = default;`
- L34 _public function_ `FBindableValueBase(const FBindableValueBase& Other) : Binding(Other.Binding ? MakeUnique<FUAFPropertyBinding>(*Other.Binding) : nullptr)`
- L38 _public function_ `FBindableValueBase& operator=(const FBindableValueBase& Other)`
- L47 _public prototype_ `FBindableValueBase(FBindableValueBase&&) = default;`
- L48 _public prototype_ `FBindableValueBase& operator=(FBindableValueBase&&) = default;`
- L50 _public function_ `bool HasBinding() const`
- L51 _public function_ `const FUAFPropertyBinding* GetBinding() const`
- L56 _public function_ `void SetBinding(const FUAFPropertyBinding& InBinding)`
- L69 _public function_ `void SetBinding(FUAFPropertyBinding&& InBinding)`
- L82 _public function_ `void ClearBinding()`
- L96 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serialization is required because the Binding field is stored as a TUniquePtr<FUAFPropertyBinding>, which is not supported by UPROPERTY serialization. Three serialization paths are needed: - Serialize(FArchive&): binary path (WithSerializer trait) - ExportTextItem/ImportTextItem: text path (WithExportTextItem/WithImportTextItem traits), used by RigVM text round-trip and property copy/paste The binding is exported as a __Binding=(...) pseudo-property appended to the struct's text. Each concrete subclass must declare its own TStructOpsTypeTraits (UE does not inherit traits).
- L97 _public prototype_ `bool ExportTextItem(FString& ValueStr, const FBindableValueBase& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;`
- L99 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);`
- L107 _public prototype_ `bool BindingsIdentical(const FBindableValueBase* Other, const UScriptStruct* ConcreteStruct, uint32 PortFlags) const;` — Compares this bindable value against Other, including the non-UPROPERTY Binding. Without this, delta serialization skips the struct when all UPROPERTYs match defaults, silently dropping the binding. Called by per-type Identical() via DECLARE_BINDABLE_IDENTICAL.
- L111 _protected prototype_ `static void ExportBindingText(FString& ValueStr, const FUAFPropertyBinding* InBinding, int32 PortFlags);` — Shared helpers for text serialization — called by concrete subclasses via IMPLEMENT_BINDABLE_TEXT_SERIALIZATION.
- L112 _protected prototype_ `static bool ImportBindingText(const TCHAR*& Buffer, TUniquePtr<FUAFPropertyBinding>& OutBinding, int32 PortFlags);`
- L115 _protected member_ `TUniquePtr<FUAFPropertyBinding> Binding;` — Optional binding. Null = no binding; non-null = GetValue() resolves from a UAF variable at runtime.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FBindableValueBase> : public TStructOpsTypeTraitsBase2<FBindableValueBase>`  
_L165-174_
- inherits: `TStructOpsTypeTraitsBase2<FBindableValueBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L168-173_

#### struct `FBindableBool`  
`struct FBindableBool : public FBindableValueBase`  
_L181-199_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L185 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableBool) FBindableBool() = default;`
- L188 _public function_ `FBindableBool(bool InValue) : ConstantValue(InValue)`
- L191 _public prototype_ `bool GetValue(FUAFAssetInstance* Instance) const;` — Resolve the binding against Instance (may be null), falling back to ConstantValue.
- L193 _public function_ `bool GetConstantValue() const`
- L194 _public function_ `void SetConstantValue(bool InValue)`
- L198 _private member_ `bool ConstantValue = false;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableFloat`  
`struct FBindableFloat : public FBindableValueBase`  
_L208-225_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L212 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableFloat) FBindableFloat() = default;`
- L215 _public function_ `FBindableFloat(float InValue) : ConstantValue(InValue)`
- L217 _public prototype_ `float GetValue(FUAFAssetInstance* Instance) const;`
- L219 _public function_ `float GetConstantValue() const`
- L220 _public function_ `void SetConstantValue(float InValue)`
- L224 _private member_ `float ConstantValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableDouble`  
`struct FBindableDouble : public FBindableValueBase`  
_L234-251_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L238 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableDouble) FBindableDouble() = default;`
- L241 _public function_ `FBindableDouble(double InValue) : ConstantValue(InValue)`
- L243 _public prototype_ `double GetValue(FUAFAssetInstance* Instance) const;`
- L245 _public function_ `double GetConstantValue() const`
- L246 _public function_ `void SetConstantValue(double InValue)`
- L250 _private member_ `double ConstantValue = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableInt32`  
`struct FBindableInt32 : public FBindableValueBase`  
_L260-277_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L264 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableInt32) FBindableInt32() = default;`
- L267 _public function_ `FBindableInt32(int32 InValue) : ConstantValue(InValue)`
- L269 _public prototype_ `int32 GetValue(FUAFAssetInstance* Instance) const;`
- L271 _public function_ `int32 GetConstantValue() const`
- L272 _public function_ `void SetConstantValue(int32 InValue)`
- L276 _private member_ `int32 ConstantValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableInt64`  
`struct FBindableInt64 : public FBindableValueBase`  
_L286-303_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L290 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableInt64) FBindableInt64() = default;`
- L293 _public function_ `FBindableInt64(int64 InValue) : ConstantValue(InValue)`
- L295 _public prototype_ `int64 GetValue(FUAFAssetInstance* Instance) const;`
- L297 _public function_ `int64 GetConstantValue() const`
- L298 _public function_ `void SetConstantValue(int64 InValue)`
- L302 _private member_ `int64 ConstantValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableByte`  
`struct FBindableByte : public FBindableValueBase`  
_L312-329_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L316 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableByte) FBindableByte() = default;`
- L319 _public function_ `FBindableByte(uint8 InValue) : ConstantValue(InValue)`
- L321 _public prototype_ `uint8 GetValue(FUAFAssetInstance* Instance) const;`
- L323 _public function_ `uint8 GetConstantValue() const`
- L324 _public function_ `void SetConstantValue(uint8 InValue)`
- L328 _private member_ `uint8 ConstantValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableName`  
`struct FBindableName : public FBindableValueBase`  
_L338-355_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L342 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableName) FBindableName() = default;`
- L345 _public function_ `FBindableName(FName InValue) : ConstantValue(InValue)`
- L347 _public prototype_ `FName GetValue(FUAFAssetInstance* Instance) const;`
- L349 _public function_ `const FName& GetConstantValue() const`
- L350 _public function_ `void SetConstantValue(const FName& InValue)`
- L354 _private member_ `FName ConstantValue;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableVector`  
`struct FBindableVector : public FBindableValueBase`  
_L364-381_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L368 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableVector) FBindableVector() = default;`
- L371 _public function_ `FBindableVector(const FVector& InValue) : ConstantValue(InValue)`
- L373 _public prototype_ `FVector GetValue(FUAFAssetInstance* Instance) const;`
- L375 _public function_ `const FVector& GetConstantValue() const`
- L376 _public function_ `void SetConstantValue(const FVector& InValue)`
- L380 _private member_ `FVector ConstantValue = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableQuat`  
`struct FBindableQuat : public FBindableValueBase`  
_L390-407_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L394 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableQuat) FBindableQuat() = default;`
- L397 _public function_ `FBindableQuat(const FQuat& InValue) : ConstantValue(InValue)`
- L399 _public prototype_ `FQuat GetValue(FUAFAssetInstance* Instance) const;`
- L401 _public function_ `const FQuat& GetConstantValue() const`
- L402 _public function_ `void SetConstantValue(const FQuat& InValue)`
- L406 _private member_ `FQuat ConstantValue = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableTransform`  
`struct FBindableTransform : public FBindableValueBase`  
_L416-433_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- L420 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableTransform) FBindableTransform() = default;`
- L423 _public function_ `FBindableTransform(const FTransform& InValue) : ConstantValue(InValue)`
- L425 _public prototype_ `FTransform GetValue(FUAFAssetInstance* Instance) const;`
- L427 _public function_ `const FTransform& GetConstantValue() const`
- L428 _public function_ `void SetConstantValue(const FTransform& InValue)`
- L432 _private member_ `FTransform ConstantValue = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableEnum`  
`struct FBindableEnum : public FBindableValueBase`  
_L454-516_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- desc: Bindable enum value. Stores the raw int32 fallback alongside the UEnum class so that the editor binding picker can filter compatible enum variables. The declaring node data type should initialize EnumClass and ConstantValue in its default constructor, e.g.: LoopMode.SetConstantValue((int32)EAnimAssetLoopMode::Auto); LoopMode.EnumClass = StaticEnum<EAnimAssetLoopMode>(); Enums whose underlying type exceeds 32 bits are not supported; a runtime ensure will fire if such an enum is bound.
- L458 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableEnum) FBindableEnum() = default;`
- L461 _public function_ `explicit FBindableEnum(UEnum* InEnumClass) : EnumClass(InEnumClass)`
- L465 _public function_ `template<typename T> requires (bool(TIsUEnumClass<T>::Value)) explicit FBindableEnum(T InValue) : EnumClass(StaticEnum<T>()) , ConstantValue(static_cast<int32>(InValue))` — Constructs with EnumClass and ConstantValue both derived from the enum value.
- L473 _public prototype_ `int32 GetValue(FUAFAssetInstance* Instance) const;`
- L477 _public function_ `template<typename T> requires (bool(TIsUEnumClass<T>::Value)) T GetValue(FUAFAssetInstance* Instance) const` — Type-safe getter — T must be a UENUM.
- L484 _public function_ `int32 GetConstantValue() const`
- L485 _public function_ `void SetConstantValue(int32 InValue)`
- L489 _public function_ `template<typename T> requires (bool(TIsUEnumClass<T>::Value)) T GetConstantValue() const` — Type-safe constant value getter — T must be a UENUM.
- L498 _public function_ `template<typename T> requires (bool(TIsUEnumClass<T>::Value)) void SetConstantValue(T InValue)` — Type-safe constant value setter — T must be a UENUM.
- L505 _public function_ `UEnum* GetEnumClass() const`
- L506 _public function_ `void SetEnumClass(UEnum* InEnumClass)`
- L512 _private member_ `TObjectPtr<UEnum> EnumClass = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Enum class for variable-picker filtering. Set by the declaring node's constructor.
- L515 _private member_ `int32 ConstantValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableStruct`  
`struct FBindableStruct : public FBindableValueBase`  
_L536-580_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- desc: Bindable struct value. Call GetValue<T>(Instance, OutValue) to resolve the binding into caller-provided storage: - No binding (or null Instance): copies ConstantValue into OutValue, or zero-initializes OutValue if ConstantValue is empty. - Variable binding: reads the named variable from Instance into OutValue. - SubProperty binding: reads the leaf sub-property from a struct variable into OutValue. T must be a USTRUCT. A runtime ensure verifies that T matches the bound or constant struct type.
- L540 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableStruct) FBindableStruct() = default;`
- L543 _public function_ `explicit FBindableStruct(UScriptStruct* InStructClass) : StructClass(InStructClass)`
- L547 _public function_ `template<typename T> explicit FBindableStruct(const T& InValue) : StructClass(TBaseStructure<T>::Get()) , ConstantValue(FInstancedStruct::Make(InValue))` — Constructs with StructClass and ConstantValue both derived from T.
- L558 _public function_ `template<typename T> void GetValue(FUAFAssetInstance* Instance, T& OutValue) const` — Resolves the binding into OutValue, falling back to ConstantValue on failure. T must be a USTRUCT. Runtime-asserts that T matches the bound or constant struct type.
- L563 _public function_ `const FInstancedStruct& GetConstantValue() const`
- L564 _public function_ `void SetConstantValue(const FInstancedStruct& InValue)`
- L565 _public function_ `void SetConstantValue(FInstancedStruct&& InValue)`
- L567 _public function_ `UScriptStruct* GetStructClass() const`
- L568 _public function_ `void SetStructClass(UScriptStruct* InStructClass)`
- L572 _private prototype_ `void GetValueToMem(FUAFAssetInstance* Instance, const UScriptStruct* ExpectedStruct, void* OutMem) const;` — Non-templated implementation; called by GetValue<T>.
- L576 _private member_ `TObjectPtr<UScriptStruct> StructClass = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Struct class for variable-picker filtering. Set by the declaring node's constructor.
- L579 _private member_ `FInstancedStruct ConstantValue;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FBindableObject`  
`struct FBindableObject : public FBindableValueBase`  
_L596-633_
- reflection: `USTRUCT(BlueprintType, MinimalAPI)`
- inherits: `FBindableValueBase`
- desc: Bindable UObject reference. Stores a hard TObjectPtr<UObject> constant alongside an optional ObjectClass filter for the editor variable picker. The declaring node data type should set ObjectClass in its constructor to restrict which object variables are shown in the picker.
- L600 _public prototype_ `DECLARE_BINDABLE_IDENTICAL(FBindableObject) FBindableObject() = default;`
- L603 _public function_ `explicit FBindableObject(UObject* InValue) : ConstantValue(InValue)`
- L604 _public function_ `explicit FBindableObject(UClass* InObjectClass) : ObjectClass(InObjectClass)`
- L605 _public function_ `FBindableObject(UObject* InValue, UClass* InObjectClass) : ObjectClass(InObjectClass) , ConstantValue(InValue)`
- L611 _public prototype_ `UObject* GetValue(FUAFAssetInstance* Instance) const;`
- L614 _public function_ `template<class T> requires(std::is_base_of_v<UObject, std::decay_t<T>>) T* GetValue(FUAFAssetInstance* Instance) const`
- L620 _public function_ `UObject* GetConstantValue() const`
- L621 _public function_ `void SetConstantValue(UObject* InValue)`
- L623 _public function_ `UClass* GetObjectClass() const`
- L624 _public function_ `void SetObjectClass(UClass* InClass)`
- L629 _private member_ `TObjectPtr<UClass> ObjectClass = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Class filter for variable-picker. Set by the declaring node's constructor.
- L632 _private member_ `TObjectPtr<UObject> ConstantValue = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### Free symbols / members of external scopes

- L119 _namespace_ `namespace UE`
- L119 _namespace_ `namespace UAF` (scope `UE`)
- L119 _namespace_ `namespace Private` (scope `UE::UAF`)
- L122 _prototype_ `template<typename T, typename BindableType> static T ResolveBindableValue(const BindableType& Bindable, FUAFAssetInstance* Instance);` (scope `UE::UAF::Private`)
- L130 _macro_ `#define DECLARE_BINDABLE_TEXT_SERIALIZATION(StructType) \` — Declares ExportTextItem/ImportTextItem on a concrete FBindableXxx type. Also grants friend access to the shared ResolveBindableValue helper (uses GET_MEMBER_NAME_CHECKED on ConstantValue). Place inside the struct body. Implementation is provided by IMPLEMENT_BINDABLE_TEXT_SERIALIZATION in the .cpp.
- L143 _macro_ `#define DECLARE_BINDABLE_IDENTICAL(StructType) \` — Declares Identical() on a concrete FBindableXxx type, delegating to the base BindingsIdentical helper. Required so that delta serialization includes the non-UPROPERTY binding in its comparison. Place inside the struct body alongside DECLARE_BINDABLE_TEXT_SERIALIZATION.
- L150 _macro_ `#define DECLARE_BINDABLE_STRUCT_OPS(StructType) \` — Declares TStructOpsTypeTraits for a concrete FBindableXxx type. UE does not inherit traits from base structs, so each subclass must declare its own.
- L169 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon47179cc80103`)
- L170 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon47179cc80103`)
- L171 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon47179cc80103`)
- L172 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon47179cc80103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/BindableValue/UAFPropertyBinding.h` (Public)


#### enum `EUAFBindingSourceType`  
`enum class EUAFBindingSourceType : uint8`  
_L16-26_
- reflection: `UENUM()`
- desc: Describes how to source a bound property value.
- L19 _public enumerator_ `Variable` — Direct UAF variable (top-level, with type-match or type-promotion).
- L22 _public enumerator_ `SubProperty` — A dot-separated path into a struct-type UAF variable.
- L25 _public enumerator_ `Function` — A 0-parameter RigVM function whose return value is used.

#### struct `FUAFPropertyBinding`  
`struct FUAFPropertyBinding`  
_L33-61_
- reflection: `USTRUCT()`
- desc: Describes the source side of a property binding: where to read a value from at runtime. The target is implicit — determined by which FBindableXxx member holds this struct.
- L42 _public member_ `FAnimNextVariableReference SourceVariable;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — The UAF variable to read from. Used when SourceType is Variable or SubProperty.
- L49 _public member_ `FPropertyBindingPath SubPropertyPath;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Dot-separated path into the struct variable to the leaf property. Used only when SourceType is SubProperty.
- L56 _public member_ `FAnimNextFunctionReference SourceFunction;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Reference to the parameterless RigVM function whose return value is used. Used only when SourceType is Function.
- L60 _public member_ `EUAFBindingSourceType SourceType = EUAFBindingSourceType::Variable;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — How to source the bound value.

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Component/AnimNextComponent.h` (Public)


#### struct `FUAFComponentInputDesc`  
`struct FUAFComponentInputDesc`  
_L50-61_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: Description of a UAF component input
- L56 _public member_ `FComponentReference Component;` — `UPROPERTY(EditAnywhere, Category="Input", meta = (UseComponentPicker, AllowedClasses = "/Script/UAF.UAFComponent,/Script/Engine.SkeletalMeshComponent"))` — The component that this input uses for its input pose
- L60 _public member_ `FAnimNextVariableReference Input;` — `UPROPERTY(EditAnywhere, Category="Input", meta = (AllowedType = "FUAFValueBundle"))` — The input pose variable that this input maps to

#### enum `EUAFSkeletalMeshComponentOutputMode`  
`enum class EUAFSkeletalMeshComponentOutputMode : uint8`  
_L65-74_
- reflection: `UENUM()`
- desc: The operation to perform when outputting values with respect to a skeletal mesh component
- L68 _public enumerator_ `WriteToSkeletalMeshComponentPose` — Write the pose to the skeletal mesh component (i.e. animate it directly)
- L73 _public enumerator_ `SkipWriteToSkeletalMeshComponentPose` — Do not write the pose to the skeletal mesh component. This can be useful to avoid unnecessary work if the skeletal mesh component's output is not rendered, or if this component is generating an intermediate output

#### class `UUAFComponent`  
`class UUAFComponent : public UActorComponent, public UE::UAF::ISystemOutputAdapter`  
_L77-370_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,UE::UAF::ISystemOutputAdapter`
- L82 _private prototype_ `virtual void OnRegister() override;` — UActorComponent interface
- L83 _private prototype_ `virtual void OnUnregister() override;`
- L84 _private prototype_ `virtual void BeginPlay() override;`
- L85 _private prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L86 _private prototype_ `virtual void Activate(bool bReset = false) override;`
- L87 _private prototype_ `virtual void Deactivate() override;`
- L90 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L93 _private prototype_ `virtual FInputData GetInputData() const override;` — ISystemOutputAdapter interface
- L94 _private prototype_ `virtual void SignalOutputWritten(const UE::UAF::FModuleTaskContext& InContext) override;`
- L102 _public prototype_ `void BlueprintSetVariable(FName Name, int32 Value);` — `UE_DEPRECATED(5.6, "This function is no longer used, please use SetVariableReference (for Blueprint) or SetVariable that takes a FAnimNextVariableReference")` — `UFUNCTION(BlueprintCallable, Category = "UAF", DisplayName = "Set Variable", CustomThunk, meta = (CustomStructureParam = Value, UnsafeDuringActorConstruction, DeprecatedFunction, DeprecationMessage = "This function has been deprecated, please use Set Variable that takes a variable reference instead"))` — Sets a system variable's value. @param    Name     The name of the variable to set @param    Value    The value to set the variable to
- L108 _public prototype_ `void BlueprintSetVariableReference(const FAnimNextVariableReference& Variable, const int32& Value);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "UAF", DisplayName = "Set Variable", CustomThunk, meta = (CustomStructureParam = Value, AutoCreateRefTerm = "Variable, Value", UnsafeDuringActorConstruction))` — Sets a system variable's value. @param    Variable The variable to set @param    Value    The value to set the variable to
- L114 _public prototype_ `void BlueprintGetVariableReference(const FAnimNextVariableReference& Variable, int32& Value);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "UAF", DisplayName = "Get Variable", CustomThunk, meta = (CustomStructureParam = Value, AutoCreateRefTerm = "Variable, Value", UnsafeDuringActorConstruction))` — Gets a system variable's value. @param    Variable The variable to get @param    Value    The return value of the variable
- L120 _public prototype_ `void BlueprintSetInputBinding(const FAnimNextVariableReference& Variable, UActorComponent* Component);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "UAF", DisplayName = "Set Input Binding", meta = (AutoCreateRefTerm = "Variable, Component", UnsafeDuringActorConstruction))` — Sets a system's (of FValueBundle type) variable. @param    Variable The variable to set @param    Component    The component to use as input source
- L127 _public function_ `template<typename ValueType> bool SetVariable(const FAnimNextVariableReference& InVariable, const ValueType& InValue)` — Set a variable. @param    InVariable         The variable to set @param    InValue            The value to set the variable to @return true if the variable was set correctly
- L137 _public function_ `template <typename ValueType> bool GetVariable(const FAnimNextVariableReference& InVariable, ValueType& OutValue)` — Get a variable. @param    InVariable         The variable to get @param    OutValue           The return value of the variable @return true if the variable was gotten correctly
- L148 _public function_ `template<typename ValueType> bool WriteVariable(const FAnimNextVariableReference& InVariable, TFunctionRef<void(ValueType&)> InFunction)` — Accesses a variable for writing. This is intended to allow for copy-free writing of larger data structures & arrays, rather than read access. @param    InVariable         The variable to set @param    InFunction         The function used to modify the variable, called back immediately on the game thread if the variable exists. @return true if the variable was accessed successfully
- L158 _public prototype_ `void ShowDebugDrawing(bool bShowDebugDrawing);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Enable or disable debug drawing. Note only works in builds with UE_ENABLE_DEBUG_DRAWING enabled
- L161 _public prototype_ `void QueueTask(FName InModuleEventName, TUniqueFunction<void(const UE::UAF::FModuleTaskContext&)>&& InTaskFunction, UE::UAF::ETaskRunLocation InLocation = UE::UAF::ETaskRunLocation::Before);` — Queue a task to run during execution
- L165 _public prototype_ `void QueueInputTraitEvent(FAnimNextTraitEventPtr Event);` — Queues an input trait event Input events will be processed in the next graph update after they are queued
- L169 _public prototype_ `FUAFWeakSystemReference GetSystemReference() const;` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Get a reference to the registered system
- L173 _public prototype_ `const FTickFunction* FindTickFunction(FName InEventName) const;` — Find the tick function for the specified event @param	InEventName			The event associated to the wanted tick function
- L179 _public prototype_ `void AddPrerequisite(UObject* InObject, FTickFunction& InTickFunction, FName InEventName);` — Add a prerequisite tick function dependency to the specified event @param	InObject			The object that owns the tick function @param	InTickFunction		The tick function to depend on @param	InEventName			The event to add the dependency to
- L186 _public prototype_ `void AddComponentPrerequisite(UActorComponent* Component, FName EventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Add a prerequisite dependency on the component's primary tick function to the specified event The component will tick before the event @param	Component			The component to add as a prerequisite @param	EventName			The event to add the dependency to
- L192 _public prototype_ `void AddSubsequent(UObject* InObject, FTickFunction& InTickFunction, FName InEventName);` — Add a subsequent tick function dependency to the specified event @param	InObject			The object that owns the tick function @param	InTickFunction		The tick function to depend on @param	InEventName			The event to add the dependency to
- L199 _public prototype_ `void AddComponentSubsequent(UActorComponent* Component, FName EventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Add a subsequent dependency on the component's primary tick function to the specified event The component will tick after the event @param	Component			The component to add as a subsequent of the event @param	EventName			The event to add the dependency to
- L205 _public prototype_ `void RemovePrerequisite(UObject* InObject, FTickFunction& InTickFunction, FName InEventName);` — Remove a prerequisite tick function dependency from the specified event @param	InObject			The object that owns the tick function @param	InTickFunction		The tick function that was depended on @param	InEventName			The event to remove the dependency from
- L211 _public prototype_ `void RemoveComponentPrerequisite(UActorComponent* Component, FName EventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Remove a prerequisite on the component's primary tick function from the specified event @param	Component			The component to remove as a prerequisite @param	EventName			The event to add the dependency to
- L217 _public prototype_ `void RemoveSubsequent(UObject* InObject, FTickFunction& InTickFunction, FName InEventName);` — Remove a prerequisite tick function dependency from the specified event @param	InObject			The object that owns the tick function @param	InTickFunction		The tick function that was depended on @param	InEventName			The event to remove the dependency from
- L223 _public prototype_ `void RemoveComponentSubsequent(UActorComponent* Component, FName EventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Remove a subsequent dependency on the component's primary tick function from the specified event @param	Component			The component to remove as a subsequent of the event @param	EventName			The event to add the dependency to
- L230 _public prototype_ `void AddModuleEventPrerequisite(FName InEventName, UUAFComponent* OtherAnimNextComponent, FName OtherEventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Add a prerequisite anim next event dependency to the specified event @param	InEventName			The event name in this component @param	InTickFunction		The other component we want a prerequisite on @param	InEventName			The other component's event name
- L237 _public prototype_ `void AddModuleEventSubsequent(FName InEventName, UUAFComponent* OtherAnimNextComponent, FName OtherEventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Add a subsequent anim next event dependency to the specified event @param	InEventName			The event name in this component @param	InTickFunction		The other component we want to add a prerequisite to @param	InEventName			The other component's event name
- L244 _public prototype_ `void RemoveModuleEventPrerequisite(FName InEventName, UUAFComponent* OtherAnimNextComponent, FName OtherEventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Remove a prerequisite anim next event dependency from the specified event @param	InEventName			The event name in this component @param	InTickFunction		The other component we want to remove a prerequisite from @param	InEventName			The other component's event name
- L251 _public prototype_ `void RemoveModuleEventSubsequent(FName InEventName, UUAFComponent* OtherAnimNextComponent, FName OtherEventName);` — `UFUNCTION(BlueprintCallable, Category = "UAF")` — Remove a subsequent anim next event dependency from the specified event @param	InEventName			The event name in this component @param	InTickFunction		The other component we want to remove a prerequisite to @param	InEventName			The other component's event name
- L253 _public function_ `TConstStructView<FUAFSystemFactoryAsset> GetAssetData() const`
- L256 _public prototype_ `void SetAsset(TInstancedStruct<FUAFSystemFactoryAsset>&& AssetData);` — can only be called when component is not registered
- L259 _private prototype_ `void SetAssetFromObject(const UObject* InAsset);`
- L260 _private prototype_ `void SetAssetInternal(TConstStructView<FUAFSystemFactoryAsset> AssetData);`
- L261 _private prototype_ `void SetAssetInternal(TInstancedStruct<FUAFSystemFactoryAsset>&& AssetData);`
- L263 _private prototype_ `void RegisterSystem();`
- L264 _private prototype_ `void UnregisterSystem();`
- L266 _private prototype_ `bool IsModuleValid();`
- L273 _private prototype_ `EPropertyBagResult SetVariableInternal(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InNewValue);` — Sets the value of the specified variable
- L276 _private prototype_ `EPropertyBagResult GetVariableInternal(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TArrayView<uint8> OutNewValue);` — Gets the value of the specified variable, expects OutNewValue to be correctly sized
- L279 _private prototype_ `EPropertyBagResult WriteVariableInternal(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TArrayView<uint8>)> InFunction);` — Accesses value of the specified variable for writing
- L282 _private prototype_ `EPropertyBagResult ReadVariableInternal(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TConstArrayView<uint8>)> InFunction);` — Accesses value of the specified variable for reading
- L285 _private prototype_ `USkeletalMeshComponent* DetermineSkeletalMeshComponent() const;` — Determine what skeletal mesh component to write to
- L288 _private prototype_ `void SetupInputOutput();` — Called on registration, sets up IO
- L291 _private prototype_ `void AllocateSystem();` — Called on registration, or lazily on dependent registration, as component registration order is not guaranteed
- L295 _private prototype_ `void SetupCharacterMovementDependency();` — If applicable, sets up a tick order dependency between this UAF System and the Character Movement Component Only set up for characters and if this component targets the character mesh and bSetupCharacterMovementDependency is set
- L297 _private prototype_ `void ReleaseCharacterMovementDependency();` — Removes the tick dependency between the system this component runs and the character movement component, if it was previously set
- L314 _private member_ `TObjectPtr<UObject> Asset_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.8, "UAnimNextComponent::Asset is replaced by AssetData")` — `UPROPERTY()`
- L318 _private member_ `TInstancedStruct<FUAFSystemFactoryAsset> AssetData;` — `UPROPERTY(EditAnywhere, Category="Animation", meta=(ExcludeBaseStruct))`
- L322 _private member_ `TObjectPtr<UUAFSystem> Module_DEPRECATED = nullptr;` — `UPROPERTY()`
- L329 _private member_ `TArray<FUAFComponentInputDesc> Inputs;` — `UPROPERTY(EditDefaultsOnly, Category="Input")`
- L337 _private member_ `FComponentReference OutputComponent;` — `UPROPERTY(EditDefaultsOnly, Category="Output", meta = (UseComponentPicker, AllowedClasses = "/Script/Engine.SkeletalMeshComponent"))`
- L341 _private member_ `EUAFSkeletalMeshComponentOutputMode SkeletalMeshComponentOutputMode = EUAFSkeletalMeshComponentOutputMode::WriteToSkeletalMeshComponentPose;` — `UPROPERTY(EditDefaultsOnly, Category="Output")` — The operation to perform when outputting values with respect to a skeletal mesh component
- L344 _private member_ `TObjectPtr<USkeletalMeshComponent> CachedSkeletalMeshComponent;` — `UPROPERTY()`
- L347 _private member_ `UE::UAF::FSystemReference SystemReference;` — Owning reference to the registered system
- L351 _private member_ `TMap<FAnimNextVariableReference, TWeakObjectPtr<UActorComponent>> InputToComponentMappings;` — `UPROPERTY(transient)` — Cached mapping between publicly exposed FValueBundle variables and their currently bound actor-components
- L354 _private member_ `uint32 SerialNumber = 0;` — Serial number, updated on worker threads when output is written
- L358 _private member_ `EAnimNextModuleInitMethod InitMethod = EAnimNextModuleInitMethod::InitializeAndPauseInEditor;` — `UPROPERTY(EditAnywhere, Category="Animation")` — How to initialize the system
- L362 _private member_ `uint8 bShowDebugDrawing : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "Animation")` — When checked, the system's debug drawing instructions are drawn in the viewport
- L368 _private member_ `uint8 bSetupCharacterMovementDependency : 1 = true;` — `UPROPERTY(EditAnywhere, Category = "Animation")` — When checked, the system's debug drawing instructions are drawn in the viewport UPROPERTY(EditAnywhere, Category = "Animation") uint8 bShowDebugDrawing : 1 = false; When set, this component automatically adds a tick prerequisite to ensure the owning character's movement component ticks before this system. Only takes effect if the owner is or inherits from ACharacter and this component outputs to its Mesh component. This mimics the default behavior on a character when animation blueprints are used.
- L369 _private member_ `uint8 bCharacterMovementDependencyHasBeenSet : 1 = false;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Workspace` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace UAF` (scope `UE`)
- L30 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace UAF` (scope `UE`)
- L35 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace UAF` (scope `UE`)
- L43 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L151 _function_ `` (scope `UUAFComponent::WriteVariable`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/ConstExprUID.h` (Public)


#### struct `UE::UAF::FConstExprUID`  
`struct FConstExprUID final`  
_L22-74_
- desc: A constexpr safe UID Encapsulates an constexpr UID. The string is exposed in non-shipping builds for logging and debugging purposes. The UID should be generated from the provided string using FNV1a with 32 bits. The whole struct is meant to be 'constexpr' to allow inlining.
- L25 _public function_ `constexpr FConstExprUID() noexcept : UID(INVALID_UID) #if !UE_BUILD_SHIPPING , DebugName(TEXT("<Invalid ConstExprUID UID>")) #endif` — Constructs an invalid UID
- L34 _public function_ `[[nodiscard]] explicit constexpr FConstExprUID(FFConstExprUIDRaw InUID, const TCHAR* InDebugName = TEXT("<Unknown ConstExprUID Name>")) noexcept : UID(InUID) #if !UE_BUILD_SHIPPING , DebugName(InDebugName) #endif` — Constructs a UID
- L43 _public function_ `[[nodiscard]] static constexpr FConstExprUID MakeFromString(const TCHAR* InName) noexcept` — Constructs a UID
- L50 _public function_ `[[nodiscard]] constexpr const TCHAR* GetDebugName() const noexcept` — Returns a literal string to the debug name
- L54 _public function_ `[[nodiscard]] constexpr FFConstExprUIDRaw GetUID() const noexcept` — Returns the raw UID
- L57 _public function_ `[[nodiscard]] constexpr bool IsValid() const noexcept` — Returns whether this UID is valid or not
- L67 _private member_ `static constexpr FFConstExprUIDRaw INVALID_UID = 0;`
- L69 _private member_ `FFConstExprUIDRaw UID;`
- L72 _private member_ `const TCHAR* DebugName;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L11 _typedef_ `using FFConstExprUIDRaw = uint32;` (scope `UE::UAF`) — Type alias for a raw UID, not typesafe
- L60 _function_ `[[nodiscard]] constexpr friend uint32 GetTypeHash(FConstExprUID InUID)` (scope `UE::UAF`) — Returns the hash of this UID
- L77 _function_ `constexpr bool operator==(FConstExprUID LHS, FConstExprUID RHS) noexcept` (scope `UE::UAF`) — Compares for equality and inequality
- L78 _function_ `constexpr bool operator!=(FConstExprUID LHS, FConstExprUID RHS) noexcept` (scope `UE::UAF`)
- L79 _function_ `constexpr bool operator==(FConstExprUID LHS, FFConstExprUIDRaw RHS) noexcept` (scope `UE::UAF`)
- L80 _function_ `constexpr bool operator!=(FConstExprUID LHS, FFConstExprUIDRaw RHS) noexcept` (scope `UE::UAF`)
- L81 _function_ `constexpr bool operator==(FFConstExprUIDRaw LHS, FConstExprUID RHS) noexcept` (scope `UE::UAF`)
- L82 _function_ `constexpr bool operator!=(FFConstExprUIDRaw LHS, FConstExprUID RHS) noexcept` (scope `UE::UAF`)
- L85 _function_ `constexpr bool operator<(FConstExprUID LHS, FConstExprUID RHS)` (scope `UE::UAF`) — For sorting

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/DataRegistry.h` (Public)


#### class `UE::UAF::FDataRegistry`  
`class FDataRegistry`  
_L26-270_
- desc: Global registry of animation data Holds ref counted data that gets released when the last DataHandle of that element goes out of scope Calling public functions from multiple threads is expected. Data races are guarded by a FRWLock. TODO : Memory management will have to be implemented to avoid fragmentation and performance reasons
- L31 _public prototype_ `static FDataRegistry* Get();` — Access the global registry
- L39 _public prototype_ `FDataHandle RegisterReferencePose(USkeletalMeshComponent* SkeletalMeshComponent);` — Generates and registers a reference pose for the SkeletalMesh asset of the SkeletalMeshComponent and modifies it with the additional required bones or the visibility state of the bones of the SkeletalMeshComponent
- L42 _public prototype_ `FDataHandle GetOrGenerateReferencePose(USkeletalMeshComponent* SkeletalMeshComponent);` — Returns a ref counted handle to the refence pose of the given skeletal mesh component
- L45 _public prototype_ `void RemoveReferencePose(USkeletalMeshComponent* SkeletalMeshComponent);` — Removes a previously registered reference pose for the given SkeletalMeshComponent
- L48 _public prototype_ `FDataHandle RegisterReferencePose(USkeletalMesh* SkeletalMesh);` — Generates and registers a reference pose for a SkeletalMesh asset
- L51 _public prototype_ `FDataHandle GetOrGenerateReferencePose(USkeletalMesh* SkeletalMesh);` — Returns a ref counted handle to the reference pose of the given skeletal mesh
- L54 _public prototype_ `void RemoveReferencePose(USkeletalMesh* SkeletalMesh);` — Removes a previously registered reference pose for the given SkeletalMesh
- L60 _public prototype_ `void RegisterData(const FName& Id, const FDataHandle& AnimationDataHandle);` — Registers an anim data handle with arbitrary data using an FName Note that AnimDataHandles are refcounted, so this makes them permanent until unregistered
- L63 _public prototype_ `void UnregisterData(const FName& Id);` — Unregisters a previously registered anim data handle
- L67 _public prototype_ `FDataHandle GetRegisteredData(const FName& Id) const;` — Obtains the data hanle for the passed Id, if it exists. If there is no anim data handle registered, the handle IsValid will be false
- L75 _public function_ `template<typename DataType> inline void RegisterDataType(int32 AllocationBlockSize)` — Registers a type and sets the desired preallocation block size If a type is allocated without registering, a default block size of 32 will be used
- L86 _public function_ `template<typename DataType> FDataHandle PreAllocateMemory(const int32 NumElements)` — Allocates uninitialized memory for a type (leaving the initialization to the caller) Returns a refcounted animation data handle Allocated memory will be released once the refcount reaches 0
- L132 _public function_ `template<typename DataType, typename... ArgTypes> FDataHandle AllocateData(const int32 NumElements, ArgTypes&&... Args)` — Allocates memory for a type, initialized with the default constructor (with optional passed arguments) Returns a refcounted animation data handle Allocated memory will be released once the refcount reaches 0
- L147 _private typedef_ `typedef void (*DestroyFnSignature)(uint8* TargetBuffer, int32 NumElem);`
- L149 _private member_ `static constexpr int32 DEFAULT_BLOCK_SIZE = 32;`
- L182 _private member_ `TMap<FAnimNextParamType, FDataTypeDef> DataTypeDefs;` — Map holding registered types
- L184 _private member_ `FRWLock DataTypeDefsLock;` — Lock for registered types map
- L186 _private member_ `TSet<Private::FAllocatedBlock*> AllocatedBlocks;`
- L188 _private member_ `FRWLock AllocatedBlocksLock;` — Lock for allocated blocks
- L191 _private member_ `TMap <FName, FDataHandle> StoredData;` — Map holding named data
- L192 _private member_ `mutable FRWLock StoredDataLock;`
- L195 _private member_ `TMap <TObjectKey<USkeletalMeshComponent>, FReferencePoseData> SkeletalMeshComponentReferencePoses;` — Map holding reference poses for Skeletal Mesh Components
- L196 _private member_ `mutable FRWLock SkeletalMeshComponentReferencePosesLock;`
- L198 _private member_ `TMap <TObjectKey<USkeletalMesh>, FReferencePoseData> SkeletalMeshReferencePoses;`
- L199 _private member_ `mutable FRWLock SkeletalMeshReferencePosesLock;`
- L202 _private member_ `FTSTicker::FDelegateHandle GCCleanupTickerHandle;` — A handle to our ticker when GC runs and we need to clean things up
- L205 _private member_ `TArray<TObjectKey<USkeletalMeshComponent>> GCComponentKeysToCleanup;` — Array of keys to clean up post-GC
- L206 _private member_ `TArray<TObjectKey<USkeletalMesh>> GCMeshKeysToCleanup;`
- L209 _private member_ `int32 GCComponentKeysProcessedIndex = 0;` — The current index of GC keys to process
- L210 _private member_ `int32 GCMeshKeysProcessedIndex = 0;`
- L214 _private function_ `template<typename DataType> FDataTypeDef RegisterDataType_Impl(int32 AllocationBlockSize)` — Registers a type and sets the allocation block size
- L242 _private prototype_ `void OnLODRequiredBonesUpdate(USkeletalMeshComponent* SkeletalMeshComponent, int32 LODLevel, const TArray<FBoneIndexType>& LODRequiredBones);`
- L244 _private prototype_ `void FreeAllocatedBlock(Private::FAllocatedBlock * AllocatedBlock);`
- L246 _private prototype_ `void ReleaseReferencePoseData();`
- L248 _private prototype_ `static bool GCCleanupTicker(float DeltaTime);`
- L249 _private prototype_ `bool RunGCCleanup(double TimeBudget);`
- L257 _private prototype_ `static void Init();` — Initialize the global registry
- L260 _private prototype_ `static void Destroy();` — Shutdown the global registry
- L263 _private prototype_ `static void OnPreExit();` — Called before engine shutdown to clear internal state while UObjects are still valid
- L265 _private member_ `volatile int32 HandleCounter = 0;`
- L269 _private prototype_ `static void HandlePostGarbageCollect();`

#### struct `UE::UAF::FDataRegistry::FDataTypeDef`  
`struct FDataTypeDef`  
_L152-159_
- desc: structure holding each registered type information
- L154 _public member_ `FAnimNextParamType ParamType;`
- L155 _public member_ `DestroyFnSignature DestroyTypeFn = nullptr;`
- L156 _public member_ `int32 ElementSize = 0;`
- L157 _public member_ `int32 ElementAlign = 0;`
- L158 _public member_ `int32 AllocationBlockSize = 0;`

#### struct `UE::UAF::FDataRegistry::FReferencePoseData`  
`struct FReferencePoseData`  
_L161-179_
- L163 _public prototype_ `FReferencePoseData() = default;`
- L165 _public function_ `FReferencePoseData(const FDataHandle& InAnimationDataHandle, const FDelegateHandle& InDelegateHandle) : AnimationDataHandle(InAnimationDataHandle) , DelegateHandle(InDelegateHandle)`
- L171 _public function_ `FReferencePoseData(FDataHandle&& InAnimationDataHandle, FDelegateHandle&& InDelegateHandle) : AnimationDataHandle(MoveTemp(InAnimationDataHandle)) , DelegateHandle(MoveTemp(InDelegateHandle))`
- L177 _public member_ `FDataHandle AnimationDataHandle;`
- L178 _public member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L224 _function_ `` (scope `UE::UAF::FDataRegistry::RegisterDataType_Impl`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/DataRegistryTypes.h` (Public)


#### struct `UE::UAF::Private::FAllocatedBlock`  
`struct FAllocatedBlock`  
_L20-58_
- L22 _public member_ `void* Memory = nullptr;`
- L23 _public member_ `int32 NumElem = 0;`
- L24 _public member_ `mutable int32 NumRefs = 0;`
- L25 _public member_ `FAnimNextParamType Type;`
- L27 _public function_ `FAllocatedBlock(void* InMemory, int32 InNumElem, FAnimNextParamType InType) : Memory(InMemory) , NumElem(InNumElem) , Type(InType)`
- L34 _public function_ `inline uint32 AddRef() const`
- L39 _public function_ `inline uint32 Release() const`
- L49 _public function_ `inline uint32 GetRefCount() const`
- L55 _private prototype_ `FAllocatedBlock() = delete;`
- L56 _private prototype_ `FAllocatedBlock(const FAllocatedBlock& Other) = delete;`
- L57 _private prototype_ `FAllocatedBlock(FAllocatedBlock&& Other) = delete;`

#### struct `UE::UAF::FDataHandle`  
`struct FDataHandle`  
_L62-164_
- L64 _public prototype_ `FDataHandle() = default;`
- L66 _public function_ `FDataHandle(Private::FAllocatedBlock* InAllocatedBlock) : AllocatedBlock(InAllocatedBlock)`
- L71 _public prototype_ `~FDataHandle();`
- L73 _public function_ `FDataHandle(const FDataHandle& Other) : AllocatedBlock(Other.AllocatedBlock)`
- L83 _public function_ `FDataHandle& operator= (const FDataHandle& Other)`
- L91 _public function_ `FDataHandle(FDataHandle&& Other) : FDataHandle()`
- L97 _public function_ `FDataHandle& operator= (FDataHandle&& Other)`
- L103 _public function_ `inline bool IsValid() const`
- L109 _public function_ `template<typename DataType> inline TArrayView<DataType> AsArrayView()`
- L116 _public function_ `template<typename DataType> inline TArrayView<DataType> AsArrayView() const`
- L123 _public function_ `template<typename DataType> inline DataType* GetPtr()`
- L132 _public function_ `template<typename DataType> inline const DataType* GetPtr() const`
- L140 _public function_ `template<typename DataType> inline DataType& GetRef()`
- L149 _public function_ `template<typename DataType> inline const DataType& GetRef() const`
- L157 _public function_ `inline FAnimNextParamType GetType() const`
- L163 _private member_ `Private::FAllocatedBlock* AllocatedBlock = nullptr;`

#### enum `UE::UAF::ETransformFlags`  
`enum class ETransformFlags : uint8`  
_L166-170_
- L168 _public enumerator_ `None = 0`
- L169 _public enumerator_ `ComponentSpaceSet = 1 << 0`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Factory/SystemFactory.h` (Public)


#### struct `UE::UAF::FSystemFactory`  
`struct FSystemFactory`  
_L30-77_
- desc: Creates or recycles programmatically-generated systems Uses the hash of the recipe to determine if the system has been created already. If the hash matches one that has already been created but the system has already been GCed it will be re-created as needed.
- L33 _public prototype_ `static const UUAFSystem* BuildSystem(const ISystemBuilder& InBuilder);` — Make a system from the specified recipe
- L37 _public prototype_ `static FUAFSystemFactoryParams GetDefaultParamsForAsset(TConstStructView<FUAFSystemFactoryAsset> Asset);` — Get default params used to build & initialize a system according to registered object class, copying InObject via the registered initializer Effective equivalent of GetDefaultParamsForClass and InitializeDefaultParamsForObject.
- L40 _public typedef_ `using FParamsInitializer = TFunction<void(const TConstStructView<FUAFSystemFactoryAsset>&, FUAFSystemFactoryParams&)>;` — Function used to initialize the object for the factory-generated system
- L43 _public typedef_ `template<typename TAssetData> using TParamsInitializer = TFunction<void(const TAssetData&, FUAFSystemFactoryParams&)>;`
- L45 _public prototype_ `static void RegisterAsset(const TSubScriptStructOf<FUAFSystemFactoryAsset>& AssetStructType, FUAFSystemFactoryParams&& InParams, FParamsInitializer&& InInitializer);`
- L48 _public function_ `template<typename TAssetData> static void RegisterAsset(FUAFSystemFactoryParams&& InParams, TParamsInitializer<TAssetData>&& InInitializer = nullptr)`
- L64 _public prototype_ `static TConstArrayView<TSubScriptStructOf<FUAFSystemFactoryAsset>> GetRegisteredAssetDataTypes();` — Get all registered classes used to generate factory systems
- L70 _private prototype_ `static void Init();` — Called on module init
- L73 _private prototype_ `static void Destroy();` — Called on module shutdown to unload everything
- L76 _private prototype_ `static void OnPreExit();` — Called before engine shutdown to clear internal state while UObjects are still valid

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L53 _function_ `` (scope `UE::UAF::FSystemFactory::RegisterAsset`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Factory/UAFSimpleSystemBuilder.h` (Public)


#### struct `FUAFSimpleSystemBuilder`  
`struct FUAFSimpleSystemBuilder : public FUAFSystemBuilder`  
_L23-79_
- reflection: `USTRUCT()`
- inherits: `FUAFSystemBuilder`
- L28 _public prototype_ `void AddVariablesInstancedStruct(FInstancedStruct&& InInstancedStruct);` — Add a variables struct to this builder
- L29 _public prototype_ `void AddVariablesStructView(FConstStructView InStructView);`
- L32 _public prototype_ `void AddVariablesStruct(const TObjectPtr<const UScriptStruct>& InScriptStruct);` — Add a struct by type, initializing to default
- L34 _public prototype_ `void AddVariablesRigVMAsset(const TScriptInterface<const IRigVMRuntimeAssetInterface>& RigVMAssetInterface);`
- L35 _public prototype_ `void AddVariablesAsset(const TObjectPtr<const UUAFRigVMAsset>& UAFAsset);`
- L38 _public prototype_ `void AddComponentInstancedStruct(TInstancedStruct<FUAFAssetInstanceComponent>&& InInstancedStruct);` — Add a component struct to this builder
- L39 _public prototype_ `void AddComponentStructView(TConstStructView<FUAFAssetInstanceComponent> InStructView);`
- L42 _public function_ `bool IsValid() const` — Check whether this method is empty or not
- L48 _public function_ `void Reset()` — Reset back to empty state
- L61 _private prototype_ `virtual bool Build(UE::UAF::FSystemBuilderContext& InContext) const override;` — FUAFSystemBuilder interface
- L62 _private prototype_ `virtual uint64 RecalculateKey() const override;`
- L66 _private member_ `TArray<TInstancedStruct<FUAFAssetInstanceComponent>> ComponentStructs;` — `UPROPERTY()` — The structs we used to generate the system's components
- L70 _private member_ `TArray<FInstancedStruct> VariablesStructs;` — `UPROPERTY()` — The structs we used to generate the system's variables
- L74 _private member_ `TArray<TScriptInterface<const IRigVMRuntimeAssetInterface>> ReferencedVariableRigVMAssets;` — `UPROPERTY()` — All the IRigVMRuntimeAssetInterface whose variables we will reference/instance at runtime
- L78 _private member_ `TArray<TObjectPtr<const UUAFRigVMAsset>> ReferencedVariableAssets;` — `UPROPERTY()` — All the assets whose variables we will reference/instance at runtime

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Factory/UAFSystemBuilder.h` (Public)


#### struct `UE::UAF::ISystemBuilder`  
`struct ISystemBuilder`  
_L21-38_
- desc: A method for making a system in FSystemFactory procedurally
- L23 _public prototype_ `virtual ~ISystemBuilder() = default;`
- L26 _protected member_ `static constexpr uint64 InvalidKey = 0;`
- L34 _private function_ `virtual bool Build(FSystemBuilderContext& InContext) const` — Primary entry point for factory method for procedurally generating systems Fills the supplied context used to generate the system @return true if the system factory context was written successfully, false otherwise
- L37 _private prototype_ `virtual uint64 GetKey() const;` — Get a uniquely-identifying key that we use to avoid rebuilding systems

#### struct `FUAFSystemBuilder`  
`struct FUAFSystemBuilder #if CPP : public UE::UAF::ISystemBuilder #endif`  
_L44-67_
- reflection: `USTRUCT()`
- inherits: `UE::UAF::ISystemBuilder`
- desc: Base struct for procedural system methods that need to persist or be referenced in data
- L53 _protected function_ `void InvalidateKey()` — Invalidate the key if the method's params change, it will be lazily recalculated
- L59 _protected function_ `virtual uint64 RecalculateKey() const` — Recalculates the key - called lazily when the key is retrieved
- L62 _protected prototype_ `virtual uint64 GetKey() const override;` — ISystemBuilder interface
- L66 _private member_ `mutable uint64 CachedKey = UE::UAF::ISystemBuilder::InvalidKey;` — Cached key based on serialized properties

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAF_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Factory/UAFSystemFactoryParams.h` (Public)


#### struct `FUAFSystemFactoryParams`  
`struct FUAFSystemFactoryParams`  
_L23-145_
- reflection: `USTRUCT(BlueprintType)`
- desc: Set of parameters that describe a way of generating & initializing a UAF system
- L27 _public prototype_ `FUAFSystemFactoryParams() = default;`
- L30 _public function_ `bool IsValid() const` — Whether these params are valid for application
- L37 _public function_ `template<typename StructType> bool AccessComponentStruct(TFunctionRef<void(StructType&)> InFunction)` — Access a component struct during initialization
- L52 _public function_ `template<typename StructType> bool AccessVariablesStruct(TFunctionRef<void(StructType&)> InFunction)` — Access a variables struct during initialization
- L68 _public function_ `template<typename StructType> void AddPublicVariablesStruct()` — Add a public variables struct to these params. This will act as part of the public API of the system. If a struct already exists of this type then its values be overriden by virtue of the initializer running later
- L77 _public function_ `template<typename StructType> TStructView<StructType> AddPublicVariablesStruct(const StructType& InStruct)` — Add a public variables struct to these params. This will act as part of the public API of the system. If a struct already exists of this type then its values be overriden by virtue of the initializer running later
- L82 _public function_ `void AddPublicVariablesStructByType(const TObjectPtr<const UScriptStruct>& InStruct)`
- L89 _public function_ `void AddPublicVariablesRigVMAsset(const TScriptInterface<const IRigVMRuntimeAssetInterface>& RigVMAsset)` — Add a public variables rig VM asset to these params. This will act as part of the public API of the system. If a asset reference already exists of this type then its values be overriden by virtue of the initializer running later
- L96 _public function_ `void AddPublicVariablesAsset(const TObjectPtr<const UUAFRigVMAsset>& UAFAsset)` — Add a public shared variables asset to these params. This will act as part of the public API of the system. If a asset reference already exists of this type then its values be overriden by virtue of the initializer running later
- L102 _public function_ `template<typename ComponentType> void AddComponent()`
- L110 _public function_ `template<typename ComponentType> void AddComponent(const ComponentType& InStruct)`
- L117 _public function_ `const UE::UAF::ISystemBuilder& GetBuilder() const` — Get the builder that these params hold
- L123 _public function_ `FUAFSystemFactoryParams& AddInitializeTask(UE::UAF::FInstanceTask&& InTask)` — Add an initialize task used to set up an instance when these params are applied
- L130 _public prototype_ `void Reset();` — Clear these parameters back to empty
- L137 _private prototype_ `void InitializeInstance(FUAFAssetInstance& InInstance) const;` — Apply these params to the supplied instance.
- L141 _private member_ `FUAFSimpleSystemBuilder Builder;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Method used to create a system
- L144 _private member_ `TArray<UE::UAF::FInstanceTask> InitializeTasks;` — Tasks to run on the factory-generated system instance via InitializeInstance, used for initial setup of variables etc.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/GenerationTools.h` (Public)


#### struct `UE::UAF::FGenerationLODData`  
`struct FGenerationLODData`  
_L22-27_
- L24 _public member_ `TArray<FBoneIndexType> RequiredBones;` — All the bones required for the LOD
- L25 _public member_ `TArray<FBoneIndexType> ExcludedBones;` — List of bones excluded from LOD 0
- L26 _public member_ `TArray<FBoneIndexType> ExcludedBonesFromPrevLOD;` — list of bones excluded from previous LOD

#### class `UE::UAF::FGenerationTools`  
`class FGenerationTools`  
_L29-156_
- L36 _public prototype_ `static bool GenerateReferencePose(const USkeletalMeshComponent* SkeletalMeshComponent , USkeletalMesh* SkeletalMesh , UE::UAF::FReferencePose& OutAnimationReferencePose);` — Generates the reference pose data from a SkeletalMeshComponent and / or Skeletal Mesh asset If no SkeletalMeshComponent is passed, the reference pose will not exclude invisible bones and will not include shadow shapes required bones If no SkeletalMesh asset is passed, there will be no generation
- L43 _public prototype_ `static void GenerateRawLODData(const USkeletalMeshComponent* SkeletalMeshComponent , const USkeletalMesh* SkeletalMesh , const int32 LODIndex , const TIndirectArray<FSkeletalMeshLODRenderData>& LODRenderData , TArray<FBoneIndexType>& OutRequiredBones , TArray<FBoneIndexType>& OutFillComponentSpaceTransformsRequiredBones);` — Generates the full list of bones required by a LOD, based on the SkeletalRetrieve RequiredBones Compute ExcludedBones versus LOD0 and PreviousLOD Remove ExcludedBonesFromPrevLOD from BonesInAllLODS
- L53 _public prototype_ `static void GenerateLODData(const USkeletalMeshComponent* SkeletalMeshComponent , const USkeletalMesh* SkeletalMesh , const int32 StartLOD , const int32 NumLODs , const TIndirectArray<FSkeletalMeshLODRenderData>& LODRenderData , const TArray<FBoneIndexType>& RequiredBones_LOD0 , TArray<FGenerationLODData>& GenerationLODData , TArray<FGenerationLODData>& GenerationComponentSpaceLODData);` — For each LOD > 0: Retrieve RequiredBones Compute ExcludedBones versus LOD0 and PreviousLOD
- L63 _public prototype_ `static void CalculateDifferenceFromParentLOD(int32 LODIndex, TArray<FGenerationLODData>& GenerationLODData);` — Calculate the bone indexes difference from LOD0 for LODIndex
- L67 _public prototype_ `static void FixLODRequiredBones(const int32 NumLODs , const USkeletalMesh* SkeletalMesh , TArray<FGenerationLODData>& GenerationLODData , TArray<FGenerationLODData>& GenerationComponentSpaceLODData);` — Check the required bones in LOD(N) are required in LOD(N-1) and add missing bones at LOD(N-1), to enable fast path on malformed LODs
- L74 _public prototype_ `static bool CheckExcludedBones(const int32 NumLODs , const TArray<FGenerationLODData>& GenerationLODData , const USkeletalMesh* SkeletalMesh);` — For each LOD : Check the excluded bones in LOD(N) contain all the bones excluded in LOD(N-1)
- L81 _public prototype_ `static bool GenerateOrderedBoneList(const USkeletalMesh* SkeletalMesh , TArray<FGenerationLODData>& GenerationLODData , TArray<FBoneIndexType>& OrderedBoneList);` — For each LOD : Generates an unified list of bones, in LOD order (if possible) Returns true if the unified list could be created, false otherwise
- L89 _public prototype_ `static void DifferenceBoneIndexArrays(const TArray<FBoneIndexType>& A, const TArray<FBoneIndexType>& B, TArray<FBoneIndexType>& Output);` — Utility for taking two arrays of bone indices, which must be strictly increasing, and finding the A - B. That is - any items left in A, after removing B.
- L93 _public prototype_ `static bool CheckSkeletalAllMeshSocketsAlwaysAnimate(const USkeletalMesh* SkeletalMesh);` — Checks if all sockets of a skeletal mesh are set to always animate, as it is a requirement for generating a single reference pose, where the local space pose and the component space pose use the same bone indexes
- L98 _public prototype_ `static void RemapPose(const FPoseContext& SourcePose, FLODPose& TargetPose);` — Converts AnimBP pose to AnimNext Pose This function expects both poses to have the same LOD (number of bones and indexes) The target pose should be assigned to the correct reference pose prior to this call
- L103 _public prototype_ `static void RemapPose(const FLODPose& SourcePose, FPoseContext& TargetPose);` — Converts AnimNext pose to AnimBP Pose This function expects both poses to have the same LOD (number of bones and indexes) The target pose should be assigned to the correct reference pose prior to this call
- L110 _public prototype_ `static void RemapPose(const FLODPose& SourcePose, TArrayView<FTransform> TargetTransforms);` — Converts AnimNext pose to local space transform array This function expects the output pose to have the same or a greater number of bones (as it may be being calculated for a lower LOD) The target pose should be assigned to the correct reference pose prior to this call, as transforms will not be filled in by this call if they are not affected by the current LOD.
- L113 _public prototype_ `static void RemapAttributes( const FLODPose& LODPose, const UE::Anim::FHeapAttributeContainer& InAttributes, UE::Anim::FMeshAttributeContainer& OutAttributes);` — Converts AnimNext attributes to AnimBP attributes
- L118 _public prototype_ `static void RemapAttributes( const FLODPose& LODPose, const UE::Anim::FStackAttributeContainer& InAttributes, UE::Anim::FMeshAttributeContainer& OutAttributes);`
- L123 _public prototype_ `static void RemapAttributes( const FLODPose& LODPose, const UE::Anim::FMeshAttributeContainer& InAttributes, UE::Anim::FStackAttributeContainer& OutAttributes);`
- L129 _public prototype_ `static void RemapAttributes( const FLODPose& LODPose, const UE::Anim::FHeapAttributeContainer& InAttributes, FPoseContext& OutPose);` — Converts AnimNext attributes to AnimBP attributes
- L135 _public prototype_ `static void RemapAttributes( const FLODPose& LODPose, const UE::Anim::FStackAttributeContainer& InAttributes, FPoseContext& OutPose);` — Converts AnimNext attributes to AnimBP attributes
- L141 _public prototype_ `static void RemapAttributes( const FPoseContext& OutPose, const FLODPose& LODPose, UE::Anim::FHeapAttributeContainer& OutAttributes );` — Converts AnimBP attributes to AnimNext attributes
- L148 _public prototype_ `static void RemapAttributes( const FPoseContext& OutPose, const FLODPose& LODPose, UE::Anim::FStackAttributeContainer& OutAttributes );` — Converts AnimBP attributes to AnimNext attributes
- L155 _public prototype_ `static void ConvertLocalSpaceToComponentSpace(TConstArrayView<FBoneIndexType> InParentIndices, TConstArrayView<FTransform> InBoneSpaceTransforms, TConstArrayView<FBoneIndexType> InRequiredBoneIndices, TArrayView<FTransform> OutComponentSpaceTransforms);` — Converts a local space to component space buffer given a number of required bones

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Graph/AnimNextGraphState.h` (Public)


#### struct `FAnimNextGraphState`  
`struct FAnimNextGraphState`  
_L11-30_
- reflection: `USTRUCT()`
- desc: Default state for a graph entry point
- L16 _public function_ `void Reset()`
- L25 _public member_ `FInstancedPropertyBag State;` — `UPROPERTY()` — All state, both public and private
- L29 _public member_ `int32 PublicParameterStartIndex = INDEX_NONE;` — `UPROPERTY()` — Index of the first public parameter, of INDEX_NONE if no public parameter is present

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/ISystemOutputAdapter.h` (Public)


#### class `UE::UAF::ISystemOutputAdapter`  
`class ISystemOutputAdapter`  
_L25-64_
- desc: Interface used by any host that wants to read an output from a UAF system Register this with FUAFSystemOutputComponent
- L28 _public prototype_ `virtual ~ISystemOutputAdapter() = default;`
- L60 _private prototype_ `virtual FInputData GetInputData() const = 0;` — Called back on a worker thread by FUAFSystemOutputComponent to retrieve the LOD and mesh to use when system execution begins The mesh & LOD is then consistent across a system's execution Consistency is validated with an ensure() in FUAFSystemOutputComponent prior to calling back via GenerateRenderData
- L63 _private prototype_ `virtual void SignalOutputWritten(const UE::UAF::FModuleTaskContext& InContext) = 0;` — Called back on a worker thread by FUAFSystemOutputComponent when an output is written

#### struct `UE::UAF::ISystemOutputAdapter::FInputData`  
`struct FInputData`  
_L31-52_
- desc: All input data required to generate an output value
- L33 _public function_ `FInputData(TNonNullPtr<USkeletalMesh> InSkeletalMesh, int32 InLOD) : SkeletalMesh(InSkeletalMesh) , LOD(InLOD)`
- L38 _public function_ `FInputData(TNonNullPtr<USkeletalMeshComponent> InSkeletalMeshComponent) : SkeletalMesh(InSkeletalMeshComponent->GetSkeletalMeshAsset()) , SkeletalMeshComponent(InSkeletalMeshComponent) , LOD(InSkeletalMeshComponent->GetPredictedLODLevel())`
- L45 _public member_ `USkeletalMesh* SkeletalMesh = nullptr;` — Mesh to use, can be nullptr when using SkeletalMeshComponent (as the component can have a null mesh), but must be valid when not
- L48 _public member_ `USkeletalMeshComponent* SkeletalMeshComponent = nullptr;` — Legacy mesh component to use, can be nullptr
- L51 _public member_ `int32 LOD = 0;` — LOD to run at

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/InstanceTask.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L12 _typedef_ `using FInstanceTask = TFunction<void(const FInstanceTaskContext&)>;` (scope `UE::UAF`) — A task that can be queued on an instance
- L15 _typedef_ `using FUniqueInstanceTask = TUniqueFunction<void(const FInstanceTaskContext&)>;` (scope `UE::UAF`) — A unique task that can be queued on an instance

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/InstanceTaskContext.h` (Public)


#### struct `UE::UAF::FInstanceTaskContext`  
`struct FInstanceTaskContext`  
_L28-93_
- desc: Context struct passed to instance tasks, allowing setting of variables etc. @see FInjectionRequest::QueueTask @see FModuleTaskContext
- L37 _public function_ `template<typename ValueType> bool AccessVariable(const FAnimNextVariableReference& InVariable, TFunctionRef<void(ValueType&)> InFunction) const` — Access a variable's value. Type must match strictly, no conversions are performed. @param	InVariable			The variable to get the value of @param	InFunction			Function that will be called if no errors occur @return true if successful
- L51 _public function_ `template<typename ValueType> bool SetVariable(const FAnimNextVariableReference& InVariable, const ValueType& InNewValue) const` — Set a variable's value. If the type does not match exactly then a conversion will be attempted. @param	InVariable			The variable to set the value of @param	OutResult			Result that will be filled if no errors occur @return see EPropertyBagResult
- L60 _public function_ `template<typename StructType> bool AccessVariablesStruct(TFunctionRef<void(StructType&)> InFunction) const` — Access the memory of the shared variable struct directly. @param	InFunction			Function called with a reference to the variable's struct @return true if the variables could be accessed. Variables can exist but be unable to be accessed if user overrides are set
- L69 _public function_ `FUAFAssetInstance& GetAssetInstance() const` — Get the asset instance
- L81 _protected prototype_ `FInstanceTaskContext(FUAFAssetInstance& InInstance);`
- L84 _protected prototype_ `bool AccessVariableInternal(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TArrayView<uint8>&)> InFunction) const;` — Access a variable's value.
- L87 _protected prototype_ `bool SetVariableInternal(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InNewValue) const;` — Set a variable's value.
- L90 _protected prototype_ `bool AccessVariablesStructInternal(const UScriptStruct* InStruct, TFunctionRef<void(FStructView)> InFunction) const;` — Access the memory of the shared variable struct directly.
- L92 _protected member_ `FUAFAssetInstance& Instance;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L40 _function_ `` (scope `UE::UAF::FInstanceTaskContext::AccessVariable`)
- L63 _function_ `` (scope `UE::UAF::FInstanceTaskContext::AccessVariablesStruct`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/LODPose.h` (Public)


#### enum `UE::UAF::ELODPoseFlags`  
`enum class ELODPoseFlags : uint8`  
_L18-27_
- L20 _public enumerator_ `None = 0`
- L21 _public enumerator_ `Additive = 1 << 0`
- L22 _public enumerator_ `DisableRetargeting = 1 << 1`
- L23 _public enumerator_ `UseRawData = 1 << 2`
- L24 _public enumerator_ `UseSourceData = 1 << 3`
- L25 _public enumerator_ `MeshSpaceAdditive = 1 << 4`
- L26 _public enumerator_ `LocalSpaceAdditive = 1 << 5`

#### struct `UE::UAF::FLODPose`  
`struct FLODPose`  
_L31-342_
- L33 _public member_ `static constexpr int32 INVALID_LOD_LEVEL = -1;`
- L35 _public member_ `FTransformArrayView LocalTransformsView;`
- L36 _public member_ `const FReferencePose* RefPose = nullptr;`
- L37 _public member_ `int32 LODLevel = INVALID_LOD_LEVEL;`
- L38 _public member_ `ELODPoseFlags Flags = ELODPoseFlags::None;`
- L40 _public prototype_ `FLODPose() = default;`
- L42 _public function_ `void CopyFrom(const FLODPose& SourcePose)`
- L79 _public function_ `template<typename OtherAllocator> void CopyTransformsFrom(const TArray<FTransform, OtherAllocator>& SourceTransforms)` — This function copies transforms from a AoS source Warning : The source number of transforms has to match the local pose size
- L102 _public function_ `template<typename OtherAllocator> void CopyTransformsTo(TArray<FTransform, OtherAllocator>& OutTransforms) const` — This function copies transforms to an AoS target array Warning : The target number of transforms has to match the local pose size
- L113 _public function_ `void SetRefPose(bool bAdditive = false, int32 StartIndex = 0, int32 NumTransformsToCopy = -1)`
- L137 _public function_ `const FReferencePose& GetRefPose() const`
- L143 _public function_ `void SetIdentity(bool bAdditive = false, int32 StartIndex = 0, int32 NumTransformsToSet = -1)`
- L148 _public function_ `int32 GetNumBones() const`
- L153 _public function_ `const TArrayView<const FBoneIndexType> GetLODBoneIndexToParentLODBoneIndexMap() const`
- L165 _public function_ `const TArrayView<const FBoneIndexType> GetLODBoneIndexToMeshBoneIndexMap() const`
- L177 _public function_ `const TArrayView<const FBoneIndexType> GetLODBoneIndexToSkeletonBoneIndexMap() const`
- L189 _public function_ `const TArrayView<const FBoneIndexType> GetMeshBoneIndexToLODBoneIndexMap() const`
- L202 _public function_ `const TArrayView<const FBoneIndexType> GetMeshBoneIndexToParentMeshBoneIndexMap() const`
- L214 _public function_ `const TArrayView<const FBoneIndexType> GetSkeletonBoneIndexToLODBoneIndexMap() const`
- L228 _public function_ `FBoneIndexType FindLODBoneIndexFromBoneName(FName BoneName) const` — Query to find a LODBoneIndex for an associated BoneName Returns INVALID_BONE_INDEX if missing ReferencePose or if no bone found for a given name
- L241 _public function_ `bool IsBoneChildOf(FBoneIndexType ChildLODBoneIndex, FBoneIndexType ParentLODBoneIndex) const` — Query whether bone with LODIndex ChildLODBoneIndex is a child of bone with LODIndex ParentLODBoneIndex Returns: True - ChildLODBoneIndex is a child of ParentLODBoneIndex False - ChildLODBoneIndex is not a child of ParentLODBoneIndex
- L272 _public function_ `FBoneIndexType GetLODBoneParentIndex(FBoneIndexType ChildLODBoneIndex) const` — Get the LODBoneIndex of the parent of the bone at ChildLODBoneIndex Returns INVALID_BONE_INDEX if no reference pose or if ChilddLODBoneIndex is the root
- L282 _public function_ `const USkeleton* GetSkeletonAsset() const`
- L287 _public function_ `bool IsValid() const`
- L292 _public function_ `bool IsAdditive() const`
- L297 _public function_ `bool IsMeshSpaceAdditive() const`
- L302 _public function_ `bool IsLocalSpaceAdditive() const`
- L308 _public function_ `void SetDisableRetargeting(bool bDisableRetargeting)` — Disable Retargeting
- L314 _public function_ `bool GetDisableRetargeting() const` — True if retargeting is disabled
- L320 _public function_ `void SetUseRAWData(bool bUseRAWData)` — Ignore compressed data and use RAW data instead, for debugging.
- L326 _public function_ `bool ShouldUseRawData() const` — True if we're requesting RAW data instead of compressed data. For debugging.
- L332 _public function_ `void SetUseSourceData(bool bUseSourceData)` — Use Source data instead.
- L338 _public function_ `bool ShouldUseSourceData() const` — True if we're requesting Source data instead of RawAnimationData. For debugging.

#### struct `UE::UAF::TLODPose`  
`template <typename AllocatorType> struct TLODPose : public FLODPose`  
_L345-402_
- inherits: `FLODPose`
- L347 _public member_ `TTransformArray<AllocatorType> LocalTransforms;`
- L349 _public prototype_ `TLODPose() = default;`
- L351 _public function_ `TLODPose(const TLODPose& Other) : FLODPose(Other), LocalTransforms(Other.LocalTransforms)`
- L356 _public function_ `TLODPose(const FReferencePose& InRefPose, int32 InLODLevel, bool bSetRefPose = true, bool bAdditive = false)`
- L361 _public function_ `TLODPose& operator=(const TLODPose& Other)`
- L369 _public function_ `bool ShouldPrepareForLOD(const FReferencePose& InRefPose, int32 InLODLevel, bool bAdditive = false) const`
- L377 _public function_ `void PrepareForLOD(const FReferencePose& InRefPose, int32 InLODLevel, bool bSetRefPose = true, bool bAdditive = false)`

#### struct `FAnimNextLODPose`  
`struct FAnimNextLODPose #if CPP : UE::UAF::FLODPoseHeap #endif`  
_L411-417_
- reflection: `USTRUCT()`
- inherits: `UE::UAF::FLODPoseHeap`
- desc: USTRUCT wrapper for LOD pose

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_ENABLE_POSE_DEBUG_FILL 0` — Handy define to set uninitialized pose buffers to 0xCDCDCDCD to help find issues
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L29 _prototype_ `ENUM_CLASS_FLAGS(ELODPoseFlags);` (scope `UE::UAF`)
- L404 _typedef_ `using FLODPoseHeap = TLODPose<FDefaultAllocator>;` (scope `UE::UAF`)
- L405 _typedef_ `using FLODPoseStack = TLODPose<FAnimStackAllocator>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/AnimNextModule.h` (Public)


#### class `UUAFSystem`  
`class UUAFSystem : public UUAFSharedVariables`  
_L49-88_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DisplayName="UAF System")`
- inherits: `UUAFSharedVariables`
- desc: Root asset represented by a component when instantiated
- L54 _public prototype_ `UUAFSystem(const FObjectInitializer& ObjectInitializer);`
- L57 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L76 _protected member_ `TArray<TInstancedStruct<FRigVMTrait_ModuleEventDependency>> Dependencies;` — `UPROPERTY()` — All dependencies that should be set up when the module initializes
- L80 _protected member_ `TArray<TObjectPtr<UScriptStruct>> RequiredComponents_DEPRECATED;` — `UPROPERTY()`
- L83 _protected member_ `FAnimNextGraphState DefaultState_DEPRECATED;` — `UPROPERTY()`
- L86 _protected member_ `FInstancedPropertyBag PropertyBag_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UAF_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UAF` (scope `UE`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace UAF` (scope `UE`)
- L36 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace UAF` (scope `UE`)
- L41 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/AnimNextModuleInitMethod.h` (Public)


#### enum `EAnimNextModuleInitMethod`  
`enum class EAnimNextModuleInitMethod : uint8`  
_L9-22_
- reflection: `UENUM()`
- L12 _public enumerator_ `None` — Do not perform any initial update, set up data structures only
- L15 _public enumerator_ `InitializeAndPause` — Set up data structures, perform an initial update and then pause
- L18 _public enumerator_ `InitializeAndPauseInEditor` — Set up data structures, perform an initial update and then pause in editor only, otherwise act like InitializeAndRun
- L21 _public enumerator_ `InitializeAndRun` — Set up data structures then continue updating

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/ModuleEvents.h` (Public)


#### struct `FAnimNextModule_ActionEvent`  
`struct FAnimNextModule_ActionEvent : public FAnimNextTraitEvent`  
_L13-39_
- inherits: `FAnimNextTraitEvent`
- desc: Module Action Event Module action events are trait events that are processed at the end of a module's execution. If the event is not thread-safe, it is dispatched to execute on the main thread.
- L15 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FAnimNextModule_ActionEvent, FAnimNextTraitEvent) FAnimNextModule_ActionEvent() = default;`
- L19 _public function_ `FAnimNextModule_ActionEvent(TUniqueFunction<void(void)>&& InActionFunction) : ActionFunction(MoveTemp(InActionFunction))`
- L25 _public function_ `virtual bool IsThreadSafe() const` — Whether or not this event is thread-safe and can execute on any thread Events that are not thread-safe will execute on the main thread
- L29 _public function_ `virtual void Execute() const` — Executes the schedule action Derived types can override this and implement whatever they wish instead of using a lambda
- L38 _public member_ `TUniqueFunction<void(void)> ActionFunction;` — The optional action to execute

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/ModuleTaskContext.h` (Public)


#### struct `UE::UAF::FModuleTaskContext`  
`struct FModuleTaskContext : public FInstanceTaskContext`  
_L27-77_
- inherits: `FInstanceTaskContext`
- desc: Context passed to schedule task callbacks
- L32 _public prototype_ `void QueueInputTraitEvent(FAnimNextTraitEventPtr Event) const;` — Queues an input trait event Input events will be processed in the next graph update after they are queued
- L36 _public prototype_ `void QueueOutputTraitEvent(FAnimNextTraitEventPtr Event) const;` — Queues an output trait event Output events will be processed at the end of the schedule tick
- L39 _public prototype_ `void TryAccessComponent(UScriptStruct* InComponentType, TFunctionRef<void(FUAFAssetInstanceComponent&)> InFunction) const;` — Access a module instance component of the specified type. If the component exists, then InFunction will be called
- L43 _public prototype_ `void AccessComponent(UScriptStruct* InComponentType, TFunctionRef<void(FUAFAssetInstanceComponent&)> InFunction) const;` — Access a module instance component of the specified type. If the component does not exist, it will be created.
- L47 _public function_ `template<typename ComponentType> void TryAccessComponent(TFunctionRef<void(ComponentType&)> InFunction) const` — Access a module instance component of the specified type. If the component exists, then InFunction will be called
- L58 _public function_ `template<typename ComponentType> void AccessComponent(TFunctionRef<void(ComponentType&)> InFunction) const` — Access a module instance component of the specified type. If the component does not exist, it will be created.
- L66 _public prototype_ `FAnimNextModuleInstance* const GetModuleInstance() const;`
- L69 _private prototype_ `FModuleTaskContext(FAnimNextModuleInstance& InModuleInstance);`
- L72 _private member_ `FAnimNextModuleInstance& ModuleInstance;` — The module instance currently running

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L50 _function_ `` (scope `UE::UAF::FModuleTaskContext::TryAccessComponent`)
- L61 _function_ `` (scope `UE::UAF::FModuleTaskContext::AccessComponent`)
- L79 _typedef_ `using FUniqueSystemTask = TUniqueFunction<void(const UE::UAF::FModuleTaskContext&)>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/RigVMTrait_ModuleEventDependency.h` (Public)


#### enum `EAnimNextModuleEventDependencyOrdering`  
`enum class EAnimNextModuleEventDependencyOrdering : uint8`  
_L15-22_
- reflection: `UENUM()`
- desc: The relative ordering of a module dependency
- L18 _public enumerator_ `Before` — This dependency executes before the specified module event
- L21 _public enumerator_ `After` — This dependency executes after the specified module event

#### struct `UE::UAF::FModuleDependencyContext`  
`struct FModuleDependencyContext`  
_L27-39_
- desc: Context passed to module dependency functions
- L29 _public function_ `FModuleDependencyContext(UObject* InObject, FTickFunction& InTickFunction) : Object(InObject) , TickFunction(InTickFunction)`
- L35 _public member_ `UObject* Object = nullptr;` — The object that the module is bound to
- L38 _public member_ `FTickFunction& TickFunction;` — The module's tick function that we want to depend on

#### struct `FRigVMTrait_ModuleEventDependency`  
`struct FRigVMTrait_ModuleEventDependency : public FRigVMTrait`  
_L44-63_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FRigVMTrait`
- desc: A trait that acts as dependency that can be established between an external system and an AnimNext event
- L48 _public prototype_ `FRigVMTrait_ModuleEventDependency();`
- L51 _public function_ `virtual void OnAddDependency(const UE::UAF::FModuleDependencyContext& InContext) const` — Override point that adds the dependency
- L54 _public function_ `virtual void OnRemoveDependency(const UE::UAF::FModuleDependencyContext& InContext) const` — Override point that removes the dependency
- L58 _public member_ `EAnimNextModuleEventDependencyOrdering Ordering;` — `UPROPERTY(EditAnywhere, Category="Dependency")` — How to execute relative to the event
- L62 _public member_ `FName EventName;` — `UPROPERTY(EditAnywhere, Category="Dependency", meta=(CustomWidget=AnimNextModuleEvent))` — The event to execute relative to

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/SystemDependency.h` (Public)


#### enum `UE::UAF::ESystemDependency`  
`enum class ESystemDependency : uint8`  
_L11-17_
- desc: Dependency type passed to AddDependency in FSystemReference/FUAFWeakSystemReference etc.
- L14 _public enumerator_ `Prerequisite` — Dependency runs before the specified event
- L16 _public enumerator_ `Subsequent` — Dependency runs after the specified event

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/SystemReference.h` (Public)


#### struct `UE::UAF::FSystemReference`  
`struct FSystemReference`  
_L53-242_
- desc: An owning reference to a UAF system. Provides a partially thread-safe API for interacting with UAF systems. Check individual methods for thread-safety. Methods that can only be called on the game thread will assert when called from non-game threads.
- L56 _public prototype_ `FSystemReference() = default;` — Default-constructable only because it needs to be embedded in UObjects/UStructs
- L59 _public prototype_ `FSystemReference(const FSystemReference&) = delete;` — Move only, non-copyable
- L60 _public prototype_ `FSystemReference& operator=(const FSystemReference&) = delete;`
- L61 _public prototype_ `FSystemReference(FSystemReference&&);`
- L62 _public prototype_ `FSystemReference& operator=(FSystemReference&&);`
- L82 _private prototype_ `FSystemReference(TConstStructView<FUAFSystemFactoryAsset> InAsset, UObject* InObject, EAnimNextModuleInitMethod InitMethod);` — Construct an owning handle to a system instance. Constructs a FAnimNextModuleInstance for use by worker threads. Should be called only from the game thread
- L85 _private prototype_ `static void Init();` — Starts up system pool
- L88 _private prototype_ `static void Destroy();` — Shuts down the system pool
- L92 _private prototype_ `void Reset();` — Reset this handle to invalid - gives up ownership Should be called only from the game thread
- L96 _private prototype_ `bool IsValid() const;` — Check if this handle is valid Can be called on any thread.
- L100 _private prototype_ `const UUAFSystem* GetSystem() const;` — Get the system that this handle references Can be called on any thread.
- L105 _private prototype_ `void SetEnabled(bool bInEnabled) const;` — Enables or disables the system This operation is deferred until just before the next world tick (FWorldDelegates::OnWorldPreActorTick) Can be called on any thread.
- L111 _private prototype_ `void ShowDebugDrawing(bool bInShowDebugDrawing) const;` — Enables or disables the system's debug drawing This operation is deferred until just before the next world tick (FWorldDelegates::OnWorldPreActorTick) Can be called on any thread.
- L117 _private function_ `void QueueTask(TUniqueFunction<void(const UE::UAF::FModuleTaskContext&)>&& InTaskFunction) const` — Queue a task to run before the first user event Can be called on any thread. @param	InTaskFunction		The function to run
- L127 _private prototype_ `void QueueTask(FName InSystemEventName, TUniqueFunction<void(const UE::UAF::FModuleTaskContext&)>&& InTaskFunction, UE::UAF::ETaskRunLocation InLocation = UE::UAF::ETaskRunLocation::Before) const;` — Queue a task to run at a particular point in a system's execution Can be called on any thread. @param	InSystemEventName	The name of the event in the system to run the supplied task relative to. If this is NAME_None, then the first user event will be used. @param	InTaskFunction		The function to run @param	InLocation			Where to run the task, before or after
- L132 _private prototype_ `void QueueInputTraitEvent(TSharedPtr<FAnimNextTraitEvent> Event) const;` — Queue an input trait event to be fired before the first user event Can be called on any thread. @param	InEvent				The event to queue
- L137 _private prototype_ `const FTickFunction* FindTickFunction(FName InEventName) const;` — Find the const tick function for the specified event. Useful to analyze/log prerequisites. Use AddDependency, RemoveDependency to actually modify dependencies Should be called only from the game thread @param	InEventName			The event associated to the wanted tick function
- L141 _private prototype_ `FName GetFirstUserEventName() const;` — Get the event name of the first user event Should be called only from the game thread
- L145 _private prototype_ `FName GetLastUserEventName() const;` — Get the event name of the last user event Should be called only from the game thread
- L150 _private prototype_ `void RunEvent(FName InEventName, float DeltaTime) const;` — Run a specific Event in-place. @TODO: Should only be called on unregistered tick functions. @param	InEventName		The event we want to run.
- L158 _private prototype_ `void AddDependency(UObject* InObject, FTickFunction& InTickFunction, FName InSystemEventName, UE::UAF::ESystemDependency InDependency) const;` — Add a dependency on a tick function to the specified event Should be called only from the game thread @param	InObject			The object that owns the tick function @param	InTickFunction		The tick function to depend on @param	InSystemEventName	The event to add the dependency to @param	InDependency		The kind of dependency to add
- L166 _private prototype_ `void RemoveDependency(UObject* InObject, FTickFunction& InTickFunction, FName InSystemEventName, UE::UAF::ESystemDependency InDependency) const;` — Remove a dependency on a tick function from the specified event Should be called only from the game thread @param	InObject			The object that owns the tick function @param	InTickFunction		The tick function that was depended on @param	InSystemEventName	The event to remove the dependency from @param	InDependency		The kind of dependency to remove
- L174 _private prototype_ `void AddSystemEventDependency(FName InSystemEventName, FUAFWeakSystemReference InOtherSystem, FName InOtherSystemEventName, UE::UAF::ESystemDependency InDependency) const;` — Add a dependency on a system event to the specified system event Should be called only from the game thread @param	InSystemEventName		The event to add the dependency to/from @param	InOtherSystem			The reference to the other system whose dependencies are being modified @param	InOtherSystemEventName	The other system's event to add the dependency to/from @param	InDependency			The kind of dependency to add
- L182 _private prototype_ `void RemoveSystemEventDependency(FName InSystemEventName, FUAFWeakSystemReference InOtherSystem, FName InOtherSystemEventName, UE::UAF::ESystemDependency InDependency) const;` — Remove a dependency on a system event from the specified system event Should be called only from the game thread @param	InSystemEventName		The event to remove the dependency to/from @param	InOtherSystem			The reference to the other system whose dependencies are being modified @param	InOtherSystemEventName	The other system's event to remove the dependency to/from @param	InDependency			The kind of dependency to remove
- L190 _private prototype_ `EPropertyBagResult SetVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InData) const;` — Set the value of the specified variable Can be called on any thread. @param	InVariable			The variable we want to set @param	InType				The type of the variable we want to set @param	InData				The data to set the variable with @return see EPropertyBagResult
- L200 _private prototype_ `EPropertyBagResult WriteVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TArrayView<uint8>)> InFunction) const;` — Accesses the variable of the specified name for writing. General read access is not provided via this API due to the current double-buffering strategy used to communicate variable writes to worker threads. This is intended to allow for copy-free writing of larger data structures & arrays, rather than read access. Can be called on any thread. @param	InVariable			The variable we want to access @param	InType				The type of the variable we want to access @param	InFunction			Function that will be called to allow modification of the variables @return see EPropertyBagResult
- L211 _private prototype_ `EPropertyBagResult ReadVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TConstArrayView<uint8>)> InFunction) const;` — Access a variable's value for read only. This performs non-recursive locks on the system instance to ensure that concurrent access is respected, so care must be taken calling this from animation worker tasks as deadlocks can occur. Type must match strictly, no conversions are performed. Can be called on any thread. @param	InVariable			The variable to get the value of @param	InType				The type of the variable @param	InFunction			Function that will be called if no errors occur @return see EPropertyBagResult
- L218 _private function_ `template<typename ComponentType> bool ReadComponent(TFunctionRef<void(TConstStructView<ComponentType> InComponentStruct)> InFunction) const` — Access the supplied system component for reading. Can be called on any thread. @param	InFunction			Function that will be called to access the struct @return true if the struct was available, otherwise false
- L230 _private prototype_ `void RunInitialTickInEditor() const;` — Runs a linearized version of the initial tick of the system to support generating an output pose for editor worlds that dont tick Should be called only from the game thread
- L235 _private prototype_ `bool ReadComponent(UScriptStruct* InComponentType, TFunctionRef<void(FConstStructView InComponentStruct)> InFunction) const;` — Access the supplied system component for reading.
- L238 _private prototype_ `explicit FSystemReference(FAnimNextModuleInstance& InInstance);` — Internal only constructor for selective access to owned-ref APIs
- L241 _private member_ `TSharedPtr<FAnimNextModuleInstance> Ptr;` — Pointer to the instance

#### class `UUAFEngineSubsystem`  
`class UUAFEngineSubsystem : public UEngineSubsystem`  
_L248-272_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: Engine subsystem used to manage system compilation routing, ticking and GC
- L253 _private prototype_ `UUAFEngineSubsystem();`
- L255 _private prototype_ `virtual void BeginDestroy() override;`
- L259 _private prototype_ `void OnCompileJobFinished(UUAFRigVMAsset* InAsset);` — Refresh any entries that use the provided asset as it has been recompiled.
- L264 _private member_ `FDelegateHandle OnCompileJobFinishedHandle;` — Handle used to hook asset compilation
- L268 _private member_ `FDelegateHandle OnWorldPreActorTickHandle;` — Handle used to hook world tick
- L271 _private member_ `FDelegateHandle OnPreGarbageCollectHandle;` — Handle used to hook into GC

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UAF` (scope `UE`)
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace UAF` (scope `UE`)
- L42 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace UAF` (scope `UE`)
- L222 _function_ `` (scope `UE::UAF::FSystemReference::ReadComponent`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/TaskRunLocation.h` (Public)


#### enum `UE::UAF::ETaskRunLocation`  
`enum class ETaskRunLocation : int32`  
_L10-17_
- L13 _public enumerator_ `Before` — Run the task before the specified task
- L16 _public enumerator_ `After` — Run the task after the specified task

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/UAFModuleInstanceComponent.h` (Public)


#### struct `FUAFModuleInstanceComponent`  
`struct FUAFModuleInstanceComponent : public FUAFAssetInstanceComponent`  
_L17-49_
- reflection: `USTRUCT(meta=(Hidden, Abstract))`
- inherits: `FUAFAssetInstanceComponent`
- desc: A system instance component is attached to and owned by a system instance.
- L22 _public typedef_ `using ContainerType = FAnimNextModuleInstance;`
- L24 _public prototype_ `virtual ~FUAFModuleInstanceComponent() override = default;`
- L28 _public prototype_ `FAnimNextModuleInstance* GetModuleInstancePtr();` — Returns the owning system instance this component lives on. Can return nullptr if an owning system instance has not been created (such as a default component on an asset)
- L32 _public prototype_ `FAnimNextModuleInstance& GetModuleInstance();` — Returns the owning system instance this component lives on Will assert if an owning system instance has not been created (such as a default component on an asset)
- L36 _public prototype_ `const FAnimNextModuleInstance& GetModuleInstance() const;` — Returns the owning system instance this component lives on Will assert if an owning system instance has not been created (such as a default component on an asset)
- L39 _public function_ `virtual void OnTraitEvent(FAnimNextTraitEvent& Event)` — Called during system execution for any events to be handled
- L42 _public function_ `virtual void OnBeginExecution(float InDeltaTime)` — Called at start of system execution each frame (this runs during the first user event - prior events, e.g. bindings will run before this)
- L45 _public function_ `virtual void OnEndExecution(float InDeltaTime)` — Called at end of system execution each frame

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/UAFNotifyDispatcherComponent.h` (Public)


#### struct `FUAFNotifyDispatcherComponent`  
`struct FUAFNotifyDispatcherComponent : public FUAFModuleInstanceComponent`  
_L22-49_
- reflection: `USTRUCT()`
- inherits: `FUAFModuleInstanceComponent`
- L25 _public prototype_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT()`
- L29 _public prototype_ `virtual void OnEndExecution(float InDeltaTime) override;`
- L32 _public prototype_ `void TriggerSingleAnimNotify(float InDeltaTime, UE::UAF::FNotifyQueueDispatchEvent* InDispatcher, const FAnimNotifyEventReference& EventReference);` — Triggers a single anim notify in the dispatcher
- L35 _public prototype_ `virtual void OnBindToInstance() override;` — FUAFAssetInstanceComponent interface
- L39 _public member_ `FAnimNotifyQueue NotifyQueue;` — `UPROPERTY()` — Notify queue to dispatch
- L41 _public member_ `TArray<const FAnimNotifyEvent*> ActiveAnimNotifyState;`
- L44 _public member_ `TArray<FAnimNotifyEventReference> ActiveAnimNotifyEventReference;` — `UPROPERTY()`
- L48 _public member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY()` — Skeletal mesh component to 'fake' dispatch from

#### struct `UE::UAF::FNotifyDispatchEvent`  
`struct FNotifyDispatchEvent : public FAnimNextTraitEvent`  
_L54-63_
- inherits: `FAnimNextTraitEvent`
- desc: Event that dispatches to the module
- L56 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FNotifyDispatchEvent, FAnimNextTraitEvent)`
- L62 _public member_ `float Weight = 1.0f;` — Weight at dispatch time

#### struct `UE::UAF::FNotifyQueueDispatchEvent`  
`struct FNotifyQueueDispatchEvent : public FAnimNextModule_ActionEvent`  
_L66-88_
- inherits: `FAnimNextModule_ActionEvent`
- desc: Event that dispatches from the module to gameplay
- L68 _public function_ `DECLARE_ANIM_TRAIT_EVENT(FNotifyQueueDispatchEvent, FAnimNextModule_ActionEvent)`
- L72 _public prototype_ `virtual void Execute() const override;`
- L75 _public member_ `TArray<FAnimNotifyEventReference> EventsToNotify;` — The various events to dispatch
- L76 _public member_ `TArray<FAnimNotifyEventReference> EventsToEnd;`
- L77 _public member_ `TArray<FAnimNotifyEventReference> EventsToBegin;`
- L78 _public member_ `TArray<FAnimNotifyEventReference> EventsToTick;`
- L81 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> WeakSkeletalMeshComponent;` — Skeletal mesh component to dispatch as
- L84 _public member_ `float DeltaSeconds = 0.0f;` — Delta time to apply to notifies
- L87 _public member_ `bool bIsThreadSafe = false;` — Whether this queue thread safe to dispatch

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L19 _macro_ `#define UE_API UAF_API`
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/UAFSystemAssetData.h` (Public)


#### struct `FUAFSystemFactoryAsset_System`  
`struct FUAFSystemFactoryAsset_System : public FUAFSystemFactoryAsset`  
_L15-28_
- reflection: `USTRUCT(DisplayName="System Asset")`
- inherits: `FUAFSystemFactoryAsset`
- L19 _public function_ `FUAFSystemFactoryAsset_System(const UUAFSystem* InSystem) : System(InSystem)`
- L20 _public prototype_ `FUAFSystemFactoryAsset_System() = default;`
- L22 _public function_ `virtual bool Validate() const override`
- L24 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const override`
- L27 _public member_ `TObjectPtr<const UUAFSystem> System;` — `UPROPERTY(EditAnywhere, Category = System)`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Module/UAFWeakSystemReference.h` (Public)


#### struct `FUAFWeakSystemReference`  
`struct FUAFWeakSystemReference`  
_L28-126_
- reflection: `USTRUCT(BlueprintType, DisplayName="UAF System Reference")`
- L32 _public prototype_ `FUAFWeakSystemReference() = default;`
- L34 _public prototype_ `explicit FUAFWeakSystemReference(const UE::UAF::FSystemReference& InHandle);`
- L36 _public function_ `bool operator==(const FUAFWeakSystemReference& InOther) const`
- L43 _public function_ `bool IsValid() const` — Check to see if this handle is for a valid instance Can be called on any thread.
- L51 _public function_ `void QueueTask(TUniqueFunction<void(const UE::UAF::FModuleTaskContext&)>&& InTaskFunction) const` — Queue a task to run before the first user event Can be called on any thread. @param	InTaskFunction		The function to run
- L61 _public prototype_ `void QueueTask(FName InSystemEventName, TUniqueFunction<void(const UE::UAF::FModuleTaskContext&)>&& InTaskFunction, UE::UAF::ETaskRunLocation InLocation = UE::UAF::ETaskRunLocation::Before) const;` — Queue a task to run at a particular point in a system's execution Can be called on any thread. @param	InSystemEventName	The name of the event in the system to run the supplied task relative to. If this is NAME_None, then the first user event will be used. @param	InTaskFunction		The function to run @param	InLocation			Where to run the task, before or after
- L66 _public prototype_ `void QueueInputTraitEvent(TSharedPtr<FAnimNextTraitEvent> InEvent) const;` — Queue an input trait event to be fired before the first user event Can be called on any thread. @param	InEvent				The event to queue
- L75 _public prototype_ `EPropertyBagResult SetVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InData) const;` — Set the value of the specified variable. Note: Sets the proxy variables that will be deferred-transferred to the system on its next ExecuteBindings_WT call. Can be called on any thread. @param	InVariable			The variable we want to set @param	InType				The type of the variable we want to set @param	InData				The data to set the variable with @return see EPropertyBagResult
- L86 _public prototype_ `EPropertyBagResult WriteVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TArrayView<uint8>)> InFunction) const;` — Accesses the variable of the specified name for writing. Note: Sets the proxy variables that will be deferred-transferred to the system on its next ExecuteBindings_WT call. General read access is not provided via this API due to the current double-buffering strategy used to communicate variable writes to worker threads. This is intended to allow for copy-free writing of larger data structures & arrays, rather than read access. Can be called on any thread. @param	InVariable			The variable we want to access @param	InType				The type of the variable we want to access @param	InFunction			Function that will be called to allow modification of the variables @return see EPropertyBagResult
- L97 _public prototype_ `EPropertyBagResult ReadVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TFunctionRef<void(TConstArrayView<uint8>)> InFunction) const;` — Access a variable's value for read only. This performs non-recursive locks on the system instance to ensure that concurrent access is respected, so care must be taken calling this from animation worker tasks as deadlocks can occur. Type must match strictly, no conversions are performed. Can be called on any thread. @param	InVariable			The variable to get the value of @param	InType				The type of the variable @param	InFunction			Function that will be called if no errors occur @return see EPropertyBagResult
- L104 _public function_ `template<typename ComponentType> bool ReadComponent(TFunctionRef<void(TConstStructView<ComponentType> InComponentStruct)> InFunction) const` — Access the supplied system component for reading. Can be called on any thread. @param	InFunction			Function that will be called to access the struct @return true if the struct was available, otherwise false
- L113 _public prototype_ `const UUAFSystem* GetSystem() const;`
- L122 _private prototype_ `bool ReadComponent(UScriptStruct* InComponentType, TFunctionRef<void(FConstStructView InComponentStruct)> InFunction) const;`
- L125 _private member_ `TWeakPtr<FAnimNextModuleInstance> WeakPtr;` — Ptr to the instance

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L108 _function_ `` (scope `FUAFWeakSystemReference::ReadComponent`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Param/AnimNextTag.h` (Public)


#### struct `FAnimNextTag`  
`struct FAnimNextTag`  
_L9-12_
- reflection: `USTRUCT(BlueprintType)`
- desc: Empty struct to act as a named tag for parameters

#### struct `FAnimNextScope`  
`struct FAnimNextScope : public FAnimNextTag`  
_L16-19_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNextTag`
- desc: Empty struct to tag named scopes

#### struct `FAnimNextEntryPoint`  
`struct FAnimNextEntryPoint : public FAnimNextTag`  
_L23-26_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNextTag`
- desc: Empty struct to tag named entry points

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Param/ParamCompatibility.h` (Public)


#### enum `UE::UAF::EParamCompatibility`  
`enum class EParamCompatibility : int32`  
_L10-26_
- L13 _public enumerator_ `Incompatible` — Parameters types are incompatble, completely unrelated (e.g. Vector -> bool)
- L16 _public enumerator_ `Incompatible_DataLoss` — Parameters types are incompatible because data loss can occur (e.g. int32 -> int16)
- L19 _public enumerator_ `Compatible_Promotion` — Parameters types are compatible with a type promotion (e.g. int32 -> int64)
- L22 _public enumerator_ `Compatible_Cast` — Parameters types are compatible with an object cast (e.g. UAnimSequence -> UAnimationAsset)
- L25 _public enumerator_ `Compatible_Equal` — Parameter types are the same

#### struct `UE::UAF::FParamCompatibility`  
`struct FParamCompatibility`  
_L28-95_
- L30 _public function_ `FParamCompatibility(EParamCompatibility InCompatibility) : Compatibility(InCompatibility)`
- L34 _public member_ `EParamCompatibility Compatibility;`
- L36 _public function_ `static FParamCompatibility Equal()`
- L41 _public function_ `static FParamCompatibility Compatible()`
- L46 _public function_ `static FParamCompatibility IncompatibleWithDataLoss()`
- L51 _public function_ `bool IsEqual() const`
- L56 _public function_ `bool IsCompatible() const`
- L61 _public function_ `bool IsCompatibleWithDataLoss() const`
- L66 _public function_ `bool operator<(const FParamCompatibility& InOther) const`
- L71 _public function_ `bool operator<=(const FParamCompatibility& InOther) const`
- L76 _public function_ `bool operator==(const FParamCompatibility& InOther) const`
- L81 _public function_ `bool operator!=(const FParamCompatibility& InOther) const`
- L86 _public function_ `bool operator>=(const FParamCompatibility& InOther) const`
- L91 _public function_ `bool operator>(const FParamCompatibility& InOther) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Param/ParamType.h` (Public)


#### struct `UE::UAF::Private::TIsSoftObjectPtr`  
`template <typename T> struct TIsSoftObjectPtr`  
_L30-33_

#### enum `UE::UAF::Private::TIsSoftObjectPtr::(anonymous)`  
`enum`  
_L32-32_

#### enum `UE::UAF::Private::TIsSoftObjectPtr::(anonymous)`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L35-35_

#### struct `UE::UAF::Private::TIsSoftObjectPtr`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L35-35_

#### enum `UE::UAF::Private::TIsSoftObjectPtr::(anonymous)`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L36-36_

#### struct `UE::UAF::Private::TIsSoftObjectPtr`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L36-36_

#### enum `UE::UAF::Private::TIsSoftObjectPtr::(anonymous)`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L37-37_

#### struct `UE::UAF::Private::TIsSoftObjectPtr`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L37-37_

#### enum `UE::UAF::Private::TIsSoftObjectPtr::(anonymous)`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L38-38_

#### struct `UE::UAF::Private::TIsSoftObjectPtr`  
`template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>>`  
_L38-38_

#### struct `UE::UAF::Private::TIsSoftClassPtr`  
`template <typename T> struct TIsSoftClassPtr`  
_L41-44_

#### enum `UE::UAF::Private::TIsSoftClassPtr::(anonymous)`  
`enum`  
_L43-43_

#### enum `UE::UAF::Private::TIsSoftClassPtr::(anonymous)`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L46-46_

#### struct `UE::UAF::Private::TIsSoftClassPtr`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L46-46_

#### enum `UE::UAF::Private::TIsSoftClassPtr::(anonymous)`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L47-47_

#### struct `UE::UAF::Private::TIsSoftClassPtr`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L47-47_

#### enum `UE::UAF::Private::TIsSoftClassPtr::(anonymous)`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L48-48_

#### struct `UE::UAF::Private::TIsSoftClassPtr`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L48-48_

#### enum `UE::UAF::Private::TIsSoftClassPtr::(anonymous)`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L49-49_

#### struct `UE::UAF::Private::TIsSoftClassPtr`  
`template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>>`  
_L49-49_

#### struct `FAnimNextParamType`  
`struct FAnimNextParamType`  
_L56-322_
- reflection: `USTRUCT(BlueprintType, DisplayName = "UAF Variable Type")`
- desc: Representation of a UAF variable's type.
- L61 _public typedef_ `using EValueType = ::EPropertyBagPropertyType;`
- L62 _public typedef_ `using EContainerType = ::EPropertyBagContainerType;`
- L67 _public prototype_ `FAnimNextParamType() = default;`
- L70 _public function_ `FAnimNextParamType(EValueType InValueType, EContainerType InContainerType = EContainerType::None, const UObject* InValueTypeObject = nullptr) : ValueTypeObject(InValueTypeObject) , ValueType(InValueType) , ContainerType(InContainerType)` — Construct a parameter type from the passed in value, container and object type.
- L80 _private member_ `TObjectPtr<const UObject> ValueTypeObject = nullptr;` — `UPROPERTY()` — Pointer to object that defines the Enum, Struct, or Class.
- L84 _private member_ `EPropertyBagPropertyType ValueType = EPropertyBagPropertyType::None;` — `UPROPERTY()` — Type of the value described by this parameter.
- L88 _private member_ `EPropertyBagContainerType ContainerType = EPropertyBagContainerType::None;` — `UPROPERTY()` — Type of the container described by this parameter.
- L93 _private function_ `template<typename ParamType> static FAnimNextParamType GetTypeInner(EContainerType InContainerType)` — Helper function for GetType
- L195 _private prototype_ `bool IsValidObject() const;` — Helper function for IsValid
- L200 _public function_ `template<typename ParamType> static FAnimNextParamType GetType()` — Get a parameter type based on the passed-in built-in type
- L215 _public function_ `const UObject* GetValueTypeObject() const` — Get the pointer to the object that defines the Enum, Struct, or Class.
- L221 _public function_ `EValueType GetValueType() const` — Get the type of the value described by this parameter.
- L227 _public function_ `EContainerType GetContainerType() const` — Get the type of the container described by this parameter.
- L237 _public prototype_ `size_t GetSize() const;` — Helper function returning the size of the type. @returns Size in bytes of the type.
- L245 _public prototype_ `size_t GetValueTypeSize() const;` — Helper function returning the size of the value type. This is identical to GetSize for non containers @returns Size in bytes of the value type.
- L252 _public prototype_ `size_t GetAlignment() const;` — Helper function returning the alignment of the type. @returns Alignment of the type.
- L260 _public prototype_ `size_t GetValueTypeAlignment() const;` — Helper function returning the alignment of the value type. This is identical to GetAlignment for non containers @returns Alignment of the value type.
- L263 _public prototype_ `void ToString(FStringBuilderBase& InStringBuilder) const;` — Append a string representing this type to the supplied string builder
- L266 _public prototype_ `FString ToString() const;` — Get a string representing this type
- L269 _public prototype_ `static FAnimNextParamType FromString(const FString& InString);` — Get a type from a string
- L272 _public prototype_ `FRigVMTemplateArgumentType ToRigVMTemplateArgument() const;` — Get a FRigVMTemplateArgumentType from this type
- L275 _public prototype_ `static FAnimNextParamType FromRigVMTemplateArgument(const FRigVMTemplateArgumentType& RigVMType);` — Construct a parameter type from the passed in FRigVMTemplateArgumentType.
- L278 _public prototype_ `static FAnimNextParamType FromProperty(const FProperty* InProperty);` — Construct a parameter type from the passed in FProperty.
- L281 _public function_ `static FAnimNextParamType FromPropertyBagPropertyDesc(const FPropertyBagPropertyDesc& InPropertyDesc)` — Construct a parameter type from the passed in FProperty.
- L306 _public function_ `bool IsNone() const` — @return whether this type is explicitly none
- L312 _public function_ `bool IsValid() const` — @return whether this type actually describes a type
- L321 _public prototype_ `bool IsObjectType() const;` — @return whether this type represents an object (object/class/softobject/softclass)

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UAF_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UAF` (scope `UE`)
- L27 _namespace_ `namespace Private` (scope `UE::UAF`)
- L32 _enumerator_ `enum { Value = false };` (scope `UE::UAF::Private::TIsSoftObjectPtr::__anon129e08dc0103`)
- L35 _enumerator_ `template <typename T> struct TIsSoftObjectPtr< TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftObjectPtr<const TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftObjectPtr< volatile TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftObjectPtr<const volatile TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr {` (scope `UE::UAF::Private::TIsSoftObjectPtr::__anon129e08dc0203`)
- L36 _enumerator_ `template <typename T> struct TIsSoftObjectPtr<const TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftObjectPtr< volatile TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftObjectPtr<const volatile TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr { enum { Value = false };` (scope `UE::UAF::Private::TIsSoftObjectPtr::__anon129e08dc0303`)
- L37 _enumerator_ `template <typename T> struct TIsSoftObjectPtr< volatile TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftObjectPtr<const volatile TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr { enum { Value = false }; };` (scope `UE::UAF::Private::TIsSoftObjectPtr::__anon129e08dc0403`)
- L38 _enumerator_ `template <typename T> struct TIsSoftObjectPtr<const volatile TSoftObjectPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr { enum { Value = false }; };` (scope `UE::UAF::Private::TIsSoftObjectPtr::__anon129e08dc0503`)
- L43 _enumerator_ `enum { Value = false };` (scope `UE::UAF::Private::TIsSoftClassPtr::__anon129e08dc0603`)
- L46 _enumerator_ `template <typename T> struct TIsSoftClassPtr< TSoftClassPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr<const TSoftClassPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr< volatile TSoftClassPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr<const volatile TSoftClassPtr<T>> { enum { Value = true }; };` (scope `UE::UAF::Private::TIsSoftClassPtr::__anon129e08dc0703`)
- L47 _enumerator_ `template <typename T> struct TIsSoftClassPtr<const TSoftClassPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr< volatile TSoftClassPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr<const volatile TSoftClassPtr<T>> { enum { Value = true }; };` (scope `UE::UAF::Private::TIsSoftClassPtr::__anon129e08dc0803`)
- L48 _enumerator_ `template <typename T> struct TIsSoftClassPtr< volatile TSoftClassPtr<T>> { enum { Value = true }; }; template <typename T> struct TIsSoftClassPtr<const volatile TSoftClassPtr<T>> { enum { Value = true }; };` (scope `UE::UAF::Private::TIsSoftClassPtr::__anon129e08dc0903`)
- L49 _enumerator_ `template <typename T> struct TIsSoftClassPtr<const volatile TSoftClassPtr<T>> { enum { Value = true }; };` (scope `UE::UAF::Private::TIsSoftClassPtr::__anon129e08dc0a03`)
- L95 _typedef_ `using NonPtrParamType = std::remove_pointer_t<ParamType>;` (scope `FAnimNextParamType::GetTypeInner`)
- L202 _typedef_ `using NonConstType = std::remove_const_t<ParamType>;` (scope `FAnimNextParamType::GetType`)
- L288 _function_ `friend bool operator==(const FAnimNextParamType& InLHS, const FAnimNextParamType& InRHS)` — Equality operator
- L294 _function_ `friend bool operator!=(const FAnimNextParamType& InLHS, const FAnimNextParamType& InRHS)` — Inequality operator
- L300 _function_ `friend uint32 GetTypeHash(const FAnimNextParamType& InType)` — Type hash for TMap storage

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/ReferencePose.h` (Public)


#### enum `UE::UAF::EReferencePoseGenerationFlags`  
`enum class EReferencePoseGenerationFlags : uint8`  
_L23-27_
- L25 _public enumerator_ `None = 0`
- L26 _public enumerator_ `FastPath = 1 << 0`

#### struct `UE::UAF::TReferencePose`  
`template <typename AllocatorType, typename SetAllocator> struct TReferencePose`  
_L32-330_
- L36 _public member_ `TTransformArray<AllocatorType> ReferenceLocalTransforms;` — Transform array of our bind pose sorted by LOD, allows us to truncate the array for a specific LOD Higher LOD come first
- L41 _public member_ `TArray<TArray<FBoneIndexType, AllocatorType>, AllocatorType> LODBoneIndexToParentLODBoneIndexMapPerLOD;` — A mapping of LOD sorted bone indices to their parent LOD sorted bone indices per LOD Each list of bone indices is a mapping of: LODSortedBoneIndex -> LODSortedBoneIndex When fast path is enabled, we have a single LOD entry that we truncate to the number of bones for each LOD
- L46 _public member_ `TArray<TArray<FBoneIndexType, AllocatorType>, AllocatorType> LODBoneIndexToMeshBoneIndexMapPerLOD;` — A mapping of LOD sorted bone indices to skeletal mesh indices per LOD Each list of bone indices is a mapping of: LODSortedBoneIndex -> SkeletalMeshBoneIndex When fast path is enabled, we have a single LOD entry that we truncate to the number of bones for each LOD
- L51 _public member_ `TArray<TArray<FBoneIndexType, AllocatorType>, AllocatorType> LODBoneIndexToSkeletonBoneIndexMapPerLOD;` — A mapping of LOD sorted bone indices to skeleton indices per LOD Each list of bone indices is a mapping of: LODSortedBoneIndex -> SkeletonBoneIndex When fast path is enabled, we have a single LOD entry that we truncate to the number of bones for each LOD
- L57 _public member_ `TArray<FBoneIndexType, AllocatorType> SkeletonBoneIndexToLODBoneIndexMap;` — List of skeleton bone indices Each list of skeleton bone indices is a mapping of: SkeletonBoneIndex -> LODSortedBoneIndex Size of the map equals the number of mesh bones. Mesh bones that are not part of the pose hold a INDEX_NONE. Note: This map is LOD independent. Please use IsBoneEnabled() to check if a given bone is part of a LOD level.
- L63 _public member_ `TArray<FBoneIndexType, AllocatorType> MeshBoneIndexToLODBoneIndexMap;` — List of pose bone indices by mesh bone index List of bone indices is a mapping of: SkeletalMeshBoneIndex -> LODSortedBoneIndex Size of the map equals the number of mesh bones. Mesh bones that are not part of the pose hold a INDEX_NONE. Note: This map is LOD independent. Please use IsBoneEnabled() to check if a given bone is part of a LOD level.
- L66 _public member_ `TArray<int32, AllocatorType> LODNumBones;` — Number of bones for each LOD
- L69 _public member_ `TArray<FBoneIndexType, AllocatorType> MeshBoneIndexToParentMeshBoneIndexMap;` — Mapping of mesh bone indices to mesh parent indices for each bone
- L72 _public member_ `TMap<FName, FBoneIndexType, SetAllocator> BoneNameToLODBoneIndexMap;` — Mapping of bone names to LOD Bone Indices
- L75 _public member_ `UE::Anim::FBulkCurveFlags CurveFlags;` — Curves of interest (material/morph target)
- L77 _public member_ `TWeakObjectPtr<const USkeletalMeshComponent> SkeletalMeshComponent = nullptr;`
- L78 _public member_ `TWeakObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;`
- L79 _public member_ `TWeakObjectPtr<const USkeleton> Skeleton = nullptr;`
- L80 _public member_ `EReferencePoseGenerationFlags GenerationFlags = EReferencePoseGenerationFlags::None;`
- L82 _public member_ `static constexpr FBoneIndexType RootBoneIndex = 0;`
- L84 _public prototype_ `TReferencePose() = default;`
- L86 _public function_ `bool IsValid() const`
- L91 _public function_ `int32 GetNumBonesForLOD(int32 LODLevel) const`
- L98 _public function_ `bool IsBoneEnabled(int32 BoneIndex, int32 LODLevel) const`
- L103 _public function_ `bool IsFastPath() const`
- L108 _public function_ `void Initialize(const FReferenceSkeleton& RefSkeleton , const TArray<TArray<FBoneIndexType>>& InLODBoneIndexToParentLODBoneIndexMapPerLOD , const TArray<TArray<FBoneIndexType>>& InLODBoneIndexToMeshBoneIndexMapPerLOD , const TArray<TArray<FBoneIndexType>>& InLODBoneIndexToSkeletonBoneIndexMapPerLOD , const TArray<FBoneIndexType>& InSkeletonBoneIndexToLODBoneIndexMap , const TArray<FBoneIndexType>& InMeshBoneIndexToLODBoneIndexMap , const TArray<int32, AllocatorType>& InLODNumBones , const TMap<FName, FBoneIndexType>& InNameToLODBoneIndexMap , const UE::Anim::FBulkCurveFlags& InCurveFlags , bool bFastPath)`
- L152 _public function_ `const TArrayView<const FBoneIndexType> GetLODBoneIndexToParentLODBoneIndexMap(int32 LODLevel) const` — Returns a list of LOD sorted parent bone indices, a mapping of: LODSortedBoneIndex -> LODSortedBoneIndex
- L168 _public function_ `const TArrayView<const FBoneIndexType> GetLODBoneIndexToMeshBoneIndexMap(int32 LODLevel) const` — Returns a list of LOD sorted skeletal mesh bone indices, a mapping of: LODSortedBoneIndex -> SkeletalMeshBoneIndex
- L184 _public function_ `const TArrayView<const FBoneIndexType> GetLODBoneIndexToSkeletonBoneIndexMap(int32 LODLevel) const` — Returns a list of LOD sorted skeleton bone indices, a mapping of: LODSortedBoneIndex -> SkeletonBoneIndex
- L200 _public function_ `const TArrayView<const FBoneIndexType> GetSkeletonBoneIndexToLODBoneIndexMap() const` — Returns a list of LOD bone indices, a mapping of: SkeletonBoneIndex -> LODSortedBoneIndex
- L206 _public function_ `const TArrayView<const FBoneIndexType> GetMeshBoneIndexToLODBoneIndexMap() const` — Return a list of LOD bone indices, a mapping of: SkeletalMeshBoneIndex -> LODSortedBoneIndex
- L211 _public function_ `const TMap<FName, FBoneIndexType>& GetBoneNameToLODBoneIndexMap() const`
- L218 _public function_ `FBoneIndexType FindLODBoneIndexFromBoneName(FName BoneName) const` — Query to find a LODBoneIndex for an associated BoneName Returns INVALID_BONE_INDEX if no bone found for a given name
- L227 _public function_ `int32 GetMeshBoneIndexFromLODBoneIndex(FBoneIndexType LODBoneIndex) const`
- L235 _public function_ `TConstArrayView<FBoneIndexType> GetMeshBoneIndexToParentMeshBoneIndexMap() const` — Returns a mapping of mesh bone indices to mesh parent indices for each bone
- L241 _public function_ `FBoneIndexType GetSkeletonBoneIndexFromLODBoneIndex(FBoneIndexType LODBoneIndex) const` — Returns the corresponding skeleton Bone Index to a LOD Bone Index
- L249 _public function_ `FBoneIndexType GetLODBoneIndexFromMeshBoneIndex(FBoneIndexType MeshBoneIndex) const` — Translate a skeletal mesh bone index to a pose bone index.
- L255 _public function_ `FBoneIndexType GetLODBoneIndexFromSkeletonBoneIndex(FBoneIndexType SkeletionBoneIndex) const`
- L261 _public function_ `FBoneIndexType GetLODParentBoneIndex(int32 LODLevel, FBoneIndexType LODBoneIndex) const`
- L275 _public function_ `const USkeletalMesh* GetSkeletalMeshAsset() const`
- L279 _public function_ `const USkeleton* GetSkeletonAsset() const`
- L284 _public function_ `FTransform GetRefPoseTransform(FBoneIndexType LODBoneIndex) const`
- L292 _public function_ `const FQuat GetRefPoseRotation(FBoneIndexType LODBoneIndex) const`
- L300 _public function_ `const FVector GetRefPoseTranslation(FBoneIndexType LODBoneIndex) const`
- L308 _public function_ `const FVector GetRefPoseScale3D(FBoneIndexType LODBoneIndex) const`
- L321 _public function_ `int32 GetSourceLODLevel() const` — Get the LOD level of the 'source' of this pose. If this pose is generated from a dynamic source, such as a skeletal mesh component, returns the LOD of the component TODO: As the predicted LOD level can vary across the frame, the LOD should be cached at a module-component level so modules have a consistent view of the current LOD across the frame. For now we are OK as the LOD level is precalculated in the mesh component and we have manual tick dependencies set up to prevent races on the value

#### struct `FAnimNextReferencePose`  
`struct FAnimNextReferencePose #if CPP : UE::UAF::FReferencePose #endif`  
_L341-347_
- reflection: `USTRUCT()`
- inherits: `UE::UAF::FReferencePose`
- desc: USTRUCT wrapper for reference pose

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L29 _prototype_ `ENUM_CLASS_FLAGS(EReferencePoseGenerationFlags);` (scope `UE::UAF`)
- L335 _typedef_ `using FReferencePose = TReferencePose<FDefaultAllocator, FDefaultSetAllocator>;` (scope `UE::UAF`) — Hide the allocator usage

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/RemapPoseData.h` (Public)


#### struct `FRemappedBone`  
`struct FRemappedBone`  
_L13-19_
- reflection: `USTRUCT()`
- L17 _public member_ `FBoneIndexType SourceBoneIndex = INVALID_BONE_INDEX;`
- L18 _public member_ `FBoneIndexType TargetBoneIndex = INVALID_BONE_INDEX;`

#### struct `FBoneRemapping`  
`struct FBoneRemapping`  
_L22-37_
- reflection: `USTRUCT()`
- L30 _public member_ `TArray<FRemappedBone> BoneIndexMap;` — Source to target bone index array for bones from the target pose that are also present in the source pose are stored. This is a subset of the bones from the target pose. The smaller the subset, the less bones to remap.
- L36 _public member_ `int32 TargetRootToSourceBoneIndex = INDEX_NONE;` — Target root bone with index 0 mapped to the source skeletal mesh. The bone index stored here represents the bone index on the source skeletal mesh of the bone with the same name as the root bone on the target. This is used as bone attachment point.

#### struct `FRemapPoseData`  
`struct FRemapPoseData`  
_L40-101_
- reflection: `USTRUCT()`
- L48 _public prototype_ `bool ShouldReinit(const UE::UAF::FReferencePose& InSourceRefPose, const UE::UAF::FReferencePose& InTargetRefPose) const;` — Check if we need to re-initialize the mapping. This will return true in case of first time usage of the data, or in the case that either the source or target pose changed.
- L55 _public prototype_ `void Reinit(const UE::UAF::FReferencePose& InSourceRefPose, const UE::UAF::FReferencePose& InTargetRefPose);` — Re-initializes the mapping for each LOD. Call ShouldReinit() before to avoid unnecessary compute. Compare the bones from the source and target pose and find the subset of the target that is also present in the source.
- L62 _public prototype_ `void RemapPose(const UE::UAF::FLODPoseHeap& SourcePose, UE::UAF::FLODPoseHeap& OutTargetPose) const;` — Remap a pose using the previously cached mapping. Call this at runtime. Prepares the target pose internally (allocates, fills ref pose for unmapped bones).
- L70 _public prototype_ `void RemapBones(const UE::UAF::FLODPose& SourcePose, UE::UAF::FLODPose& OutTargetPose) const;` — Remap bone transforms from source into an already-prepared target pose. The target must already have memory allocated and ref pose set for unmapped bones. Operates on FLODPose base, works with any allocator (heap or stack).
- L79 _public prototype_ `template<typename OutContainerType> void RemapAttributes(const UE::UAF::FLODPose& SourceLODPose, const UE::Anim::FHeapAttributeContainer& InAttributes, const UE::UAF::FLODPose& TargetLODPose, OutContainerType& OutAttributes) const;` — Remap attributes from source into an already-prepared target attribute container. Bone indices are translated from source LOD pose space to target LOD pose space via the skeleton bone name. Attributes whose source bone has no counterpart in the target skeleton are silently dropped. Templated to support both heap (FHeapAttributeContainer) and stack (FStackAttributeContainer) output containers.
- L87 _public prototype_ `FTransform RecursiveCalcModelspaceTransform(const UE::UAF::FLODPose& Pose, FBoneIndexType BoneIndex) const;` — Temporary calculate modelspace transform, until the LODPose is able to do that.
- L89 _public member_ `const UE::UAF::FReferencePose* SourceRefPose = nullptr;`
- L90 _public member_ `const UE::UAF::FReferencePose* TargetRefPose = nullptr;`
- L100 _public member_ `TArray<TArray<FBoneRemapping>> SourceToTargetBoneIndexMapPerLOD;` — Bone mapping from the source to the target skeletal mesh per LOD level combination. The array's length equals the number of source skeletal mesh LODs available. Each of the elements will contain a bone mapping based on the given source LOD for the target skeletal mesh LOD. The number of elements of the sub-array equals to the number of LOD levels of the target skeletal mesh. Example: SourceToTargetBoneIndexMapPerLOD[4][2] gives a bone mapping from source LOD 4 to target LOD 2 and will usually contain less elements than the target skeletal mesh has bones.

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/RemapPoseDataPool.h` (Public)


#### class `UE::UAF::FRemapPoseDataPool`  
`class FRemapPoseDataPool`  
_L19-67_
- desc: Shared pool for FRemapPoseData instances, keyed by (source, target) reference pose pairs. Avoids per-node caching and provides fast lookup with minimal locking. Uses a read-write lock: concurrent reads are lock-free, writes only lock when a new pair is first encountered or needs to be reinited.
- L23 _public prototype_ `static FRemapPoseDataPool& Get();` — Access the singleton pool instance.
- L29 _public function_ `[[nodiscard]] static bool NeedsRemapping(const FReferencePose& InSourceRefPose, const FReferencePose& InTargetRefPose)` — Returns true if the source and target reference poses refer to different skeletons, meaning a copy between them requires remapping. This is a cheap reference pose pointer comparison, no locking or pool access.
- L43 _public prototype_ `const FRemapPoseData& GetRemapData(const FReferencePose& InSourceRefPose, const FReferencePose& InTargetRefPose);` — Get or create remap data for a source->target reference pose pair. On first access for a given pair, FRemapPoseData::Reinit() is called to build the bone mapping. Subsequent calls with the same pair return the cached data. If either reference pose's skeletal mesh has changed since the last Reinit, the data is refreshed. Thread safety notes: GetRemapData() returns a reference to the cached FRemapPoseData. The read lock is released before the reference is used by the caller. This is safe because: 1. GarbageCollect() only runs from FDataRegistry::HandlePostGarbageCollect, which executes on the game thread between frames and never during animation evaluation. 2. ShouldReinit() only returns true if the skeletal mesh pointer changed, which doesn't happen mid-frame. 3. All animation evaluation completes within a single frame before GC can run. Therefore, returned references remain valid for the duration of their use during evaluation.
- L46 _public prototype_ `void GarbageCollect();` — Remove pool entries that reference stale skeletal meshes. Call periodically (e.g. on GC).
- L59 _private function_ `friend uint32 GetTypeHash(const FRefPosePair& Pair)`
- L65 _private member_ `TMap<FRefPosePair, TUniquePtr<FRemapPoseData>> Pool;`
- L66 _private member_ `mutable FRWLock PoolLock;`

#### struct `UE::UAF::FRemapPoseDataPool::FRefPosePair`  
`struct FRefPosePair`  
_L49-63_
- L51 _public member_ `const FReferencePose* Source;`
- L52 _public member_ `const FReferencePose* Target;`
- L54 _public function_ `bool operator==(const FRefPosePair& Other) const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/RetargetingTools.h` (Public)


#### class `UE::UAF::FRetargetingTools`  
`class FRetargetingTools`  
_L16-216_
- L35 _public prototype_ `static void BuildRetargetingPairs( const FLODPose& SourcePose, const FLODPose& TargetPose, const FRemapPoseData& RemapPoseData, const USkeleton* SourceSkeleton, const USkeleton* TargetSkeleton, bool bUseSourceRetargetModes, bool bDisableRetargeting, BoneTrackArray& OutSkeletonPairs, BoneTrackArray& OutAnimScalePairs, BoneTrackArray& OutAnimRelativePairs, BoneTrackArray& OutOrientAndScalePairs);` — Build sparse bone-track pairs for each translation retargeting mode. Pre-filters Source to target bone relations into three lists: AnimationScaled, AnimationRelative, and OrientAndScale. @param SourcePose                Source pose to retarget from. @param TargetPose                Retargeting target pose. @param RemapPoseData             Cached source to target bone mapping per LOD. @param SourceSkeleton            Source skeleton to retarget from. @param TargetSkeleton            Retargeting target skeleton. @param bUseSourceRetargetModes   Set to true when you wish to extract the retarget mode from the source skeleton instead of the target skeleton. @param bDisableRetargeting       Is translational retargeting disabled? @param OutSkeletonPairs          Output pairs for EBoneTranslationRetargetingMode::Skeleton retargeting mode where bones use ref pose translation but rotate along with the source. @param OutAnimScalePairs         Output pairs for AnimationScaled. @param OutAnimRelativePairs      Output pairs for AnimationRelative. @param OutOrientAndScalePairs    Output pairs for OrientAndScale.
- L63 _public function_ `template<bool bIsAdditive> static FORCEINLINE void TranslationRetargetReferencePoseBone( const USkeleton* SourceSkeleton, const USkeleton* TargetSkeleton, const FSkeletonRemapping& SkeletonRemapping, bool bUseSourceRetargetModes, bool bDisableRetargeting, const int32 PoseBoneIndex, const int32 TargetSkeletonBoneIndex, FLODPose& OutPose)` — Per-bone reference-pose translation correction. This is the step that moves authored offsets across differing proportions without touching rotation. @tparam bIsAdditive              True if the source pose is additive (deltas relative to a reference pose), in which case additive-space retargeting is applied. False for absolute poses. @param SourceSkeleton            Source skeleton to retarget from. @param TargetSkeleton            Retargeting target skeleton. @param SkeletonRemapping         Maps source and target skeleton bone indices. @param bUseSourceRetargetModes   Set to true when you wish to extract the retarget mode from the source skeleton instead of the target skeleton. @param bDisableRetargeting       Is translational retargeting disabled? @param PoseBoneIndex             Target pose bone index. @param TargetSkeletonBoneIndex   Target skeleton bone index. @param OutPose                   Target pose receiving the translation fix.
- L108 _public prototype_ `static void ReferencePoseRetarget( const USkeleton* SourceSkeleton, const USkeleton* TargetSkeleton, const FSkeletonRemapping& SkeletonRemapping, bool bUseSourceRetargetModes, bool bDisableRetargeting, FLODPose& OutPose);` — Reference-pose correction per bone. @param SourceSkeleton            Source skeleton to retarget from. @param TargetSkeleton            Retargeting target skeleton. @param SkeletonRemapping         Maps source and target skeleton bone indices. @param bUseSourceRetargetModes   Set to true when you wish to extract the retarget mode from the source skeleton instead of the target skeleton. @param bDisableRetargeting       Is translational retargeting disabled? @param OutPose                   Target pose to work on.
- L133 _public prototype_ `static void RetargetBoneTransform( const FReferencePose& TargetReferencePose, const USkeleton* SourceSkeleton, const USkeleton* TargetSkeleton, const FName& SourceName, const TArray<FTransform>& RetargetTransforms, FTransform& BoneTransform, const int32 SkeletonBoneIndex, const int32 LODBoneIndex, const bool bIsBakedAdditive, const bool bDisableRetargeting);` — Translation retarget a pose. Applies the bone’s EBoneTranslationRetargetingMode: - AnimationScaled: scale local translation by source/target ref-length ratio. - AnimationRelative: transfer delta from authored base into target basis. and add to current transform (skip if baked additive upstream). - OrientAndScale: orientation-aware scaling when enabled. @param TargetReferencePose       Target reference pose. @param SourceSkeleton            Source skeleton to retarget from. @param TargetSkeleton            Retargeting target skeleton. @param RetargetTransforms        The name of the retarget source to find. @param BoneTransform             . @param SkeletonBoneIndex         Target skeleton bone index. @param LODBoneIndex              Bone index in current LOD view. @param bIsBakedAdditive          Treat input as baked additive. @param bDisableRetargeting       Early-out passthrough.
- L159 _public function_ `static FORCEINLINE void RetargetBoneTransform( const FReferencePose& TargetReferencePose, const USkeleton* SourceSkeleton, const USkeleton* TargetSkeleton, const FName& RetargetSource, FTransform& BoneTransform, const int32 SkeletonBoneIndex, const int32 LODBoneIndex, const bool bIsBakedAdditive, const bool bDisableRetargeting)` — Translation retarget a pose. Convenience path that pulls the source’s ref local poses (RetargetSource) and forwards to the explicit-transform overload. @param TargetReferencePose       Target reference pose. @param SourceSkeleton            Source skeleton to retarget from. @param TargetSkeleton            Retargeting target skeleton. @param RetargetTransforms        The name of the retarget source to find. @param BoneTransform             . @param SkeletonBoneIndex         Target skeleton bone index. @param LODBoneIndex              Bone index in current LOD view. @param bIsBakedAdditive          Treat input as baked additive. @param bDisableRetargeting       Early-out passthrough.
- L186 _public prototype_ `static void RetargetBone_AnimRelative( const int32 TargetPoseBoneIndex, const int32 TargetSkeletonBoneIndex, const FReferencePose& TargetReferencePose, const FSkeletonRemapping& SourceToTargetRemapping, FTransform BaseTransform, FTransform& InOutBoneTransform);` — AnimationRelative path: apply authored-base delta in target basis. @param TargetPoseBoneIndex       Bone index of the bone on the target pose. @param TargetSkeletonBoneIndex   Corresponding bone index in the target's skeleton. @param TargetReferencePose       Target reference pose. @param SourceToTargetRemapping   Maps source and target skeleton bone indices. @param BaseTransform             Authored base (source) local-space transform. @param InOutBoneTransform        In/out current local transform to receive delta.
- L207 _public prototype_ `static void RetargetPose( const FReferencePose& TargetReferencePose, const FSkeletonRemapping& SourceToTargetRemapping, BoneTrackArray& SkeletonRetargetingPairs, BoneTrackArray& AnimScaleRetargetingPairs, BoneTrackArray& AnimRelativeRetargetingPairs, BoneTrackArray& OrientAndScaleRetargetingPairs, const TArray<FTransform>& SourceReferencePoseTransforms, FLODPose& OutPose);` — Translation retarget a pose. Runs the three per-mode passes (Scaled, Relative, Orient+Scale) over OutPose. Work scales with number of pairs, not bones. @param TargetReferencePose			Target reference pose. @param SourceToTargetRemapping		Maps source and target skeleton bone indices. @param SkeletonRetargetingPairs		Pairs used for retargeting where bones use ref pose translation but rotate along with the source. @param AnimScaleRetargetingPairs		Pairs for AnimationScaled pass. @param AnimRelativeRetargetingPairs	Pairs for AnimationRelative pass. @param OrientAndScaleRetargetingPairs Pairs for OrientAndScale pass. @param SourceReferencePoseTransforms  Source reference pose transforms. @param OutPose						Target pose to work on in-place.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/RewindDebugger/UAFTrace.h` (Public)


#### struct `UE::UAF::FUAFTrace`  
`struct FUAFTrace`  
_L31-42_
- L33 _public member_ `static const FGuid CustomVersionGUID;`
- L35 _public prototype_ `static void Reset();`
- L37 _public prototype_ `static void OutputUAFInstance(const FUAFAssetInstance* DataInterface, const UObject* OuterObject);`
- L38 _public prototype_ `static void OutputUAFVariables(const FUAFAssetInstance* DataInterface, const UObject* OuterObject);`
- L41 _private prototype_ `static bool OutputUAFVariableSet(const TSharedRef<FUAFInstanceVariableContainer>& VariableSet, uint64 InstanceId, const UObject* OuterObject);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UAF_TRACE_ENABLED (OBJECT_TRACE_ENABLED && !(UE_BUILD_SHIPPING || UE_BUILD_TEST))`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)
- L47 _macro_ `#define TRACE_UAF_INSTANCE(DataInterface, OuterObject) UE::UAF::FUAFTrace::OutputUAFInstance(DataInterface, OuterObject);`
- L48 _macro_ `#define TRACE_UAF_VARIABLES(DataInterface, OuterObject) UE::UAF::FUAFTrace::OutputUAFVariables(DataInterface, OuterObject);`
- L50 _macro_ `#define TRACE_UAF_INSTANCE(DataInterface, OuterObject)`
- L51 _macro_ `#define TRACE_UAF_VARIABLES(DataInterface, OuterObject)`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Script/ScriptEventPhase.h` (Public)


#### enum `UE::UAF::EScriptEventPhase`  
`enum class EScriptEventPhase : uint8`  
_L11-18_
- desc: Phase is used as a general ordering constraint on event execution
- L14 _public enumerator_ `PreExecute` — Before any execution, e.g. for copying data from the game thread
- L17 _public enumerator_ `Execute` — General execution, e.g. a prephysics event

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Script/ScriptEventTickFunctionBindings.h` (Public)


#### struct `UE::UAF::FTickFunctionBindingContext`  
`struct FTickFunctionBindingContext`  
_L15-31_
- desc: Binding context for tick functions
- L17 _public function_ `FTickFunctionBindingContext(FUAFAssetInstance& InAssetInstance, UObject* InObject, UWorld* InWorld) : AssetInstance(InAssetInstance) , Object(InObject) , World(InWorld)`
- L24 _public member_ `FUAFAssetInstance& AssetInstance;` — The asset instance
- L27 _public member_ `UObject* Object = nullptr;` — Object that a asset instance is bound on (e.g. a component)
- L30 _public member_ `UWorld* World = nullptr;` — World that the object is contained within

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L34 _typedef_ `using FTickFunctionBindingFunction = TFunction<void(const FTickFunctionBindingContext& InContext, FTickFunction& InTickFunction)>;` (scope `UE::UAF`) — Function called to bind a tick function to a script event, set up prerequisites etc.

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Script/UAFRigVMComponent.h` (Public)


#### struct `FUAFRigVMComponent`  
`struct FUAFRigVMComponent : public FUAFScriptComponent`  
_L16-63_
- reflection: `USTRUCT()`
- inherits: `FUAFScriptComponent`
- desc: Asset instance component supplying work memory for RigVM execution
- L19 _public function_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT()`
- L32 _public function_ `virtual void CallEventByName(TConstStructView<FUAFScriptContextData> InContextData) override` — FUAFScriptComponent interface
- L36 _public prototype_ `virtual TConstArrayView<UE::UAF::FScriptEventInfo> GetScriptEvents() override;`
- L40 _private prototype_ `static void StaticCallEvent(TStructView<FUAFScriptComponent> InScriptComponent, TConstStructView<FUAFScriptContextData> InContextData);` — Calls an event in RigVM with appropriate context setup
- L43 _private prototype_ `virtual void OnBindToInstance() override;` — FUAFAssetInstanceComponent interface
- L49 _private member_ `TArray<UE::UAF::FScriptEventInfo> ImplementedEvents;` — Cached events
- L53 _private member_ `FRigVMExtendedExecuteContext ExtendedExecuteContext;` — `UPROPERTY(Transient)` — Extended execute context instance for our asset instance, we own it
- L57 _private member_ `TObjectPtr<URigVM> VM;` — `UPROPERTY(Transient)` — VM used for execution
- L61 _private member_ `bool bIsInitialized = false;` — Flag for initialization checks

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Script/UAFScriptComponent.h` (Public)


#### struct `UE::UAF::FScriptEvent`  
`struct FScriptEvent`  
_L23-55_
- desc: Implemented script event
- L26 _public typedef_ `using FEventFunc = void (*)(TStructView<FUAFScriptComponent> , TConstStructView<FUAFScriptContextData> );` — Function used to call an event
- L28 _public prototype_ `FScriptEvent() = default;`
- L30 _public function_ `FScriptEvent(FEventFunc InEventFunc, FName InEventName) : EventFunc(InEventFunc) , EventName(InEventName)`
- L36 _public function_ `bool IsCallable() const` — Check whether this even can be called
- L42 _public function_ `FName GetEventName() const` — Get the name of this event
- L51 _private member_ `FEventFunc EventFunc = nullptr;` — Function ptr used to call the event
- L54 _private member_ `FName EventName;` — The name of the event

#### struct `UE::UAF::FScriptEventInfo`  
`struct FScriptEventInfo`  
_L58-89_
- desc: Implemented script event wrapper
- L61 _public member_ `FScriptEvent Event;` — The event function itself (can be nullptr for non-native events)
- L64 _public member_ `UScriptStruct* Struct = nullptr;` — Associated event's struct (e.g. for RigVM events)
- L67 _public member_ `FTickFunctionBindingFunction Binding;` — Binding callback, called when event is first set up for a system
- L70 _public member_ `int32 SortOrder = 0;` — Sort order used to determine the order withing a tick group the event runs in
- L73 _public member_ `EScriptEventPhase Phase = EScriptEventPhase::Execute;` — The phase of execution that the event runs in
- L76 _public member_ `ETickingGroup TickGroup = ETickingGroup::TG_PrePhysics;` — The tick group the event runs in
- L79 _public member_ `ETickingGroup EndTickGroup = ETickingGroup::TG_PrePhysics;` — The tick group the event completes in
- L82 _public member_ `uint8 bUserEvent : 1 = true;` — Whether this is a user-authored event, or a compiler-generated event
- L85 _public member_ `uint8 bIsTask : 1 = true;` — Whether this event is a 'task' that runs in a tick function, or whether it will run attached to another tick function
- L88 _public member_ `uint8 bIsGameThreadTask : 1 = false;` — Whether this is a task that runs on the game thread, as opposed to a worker thread

#### struct `FUAFScriptComponent`  
`struct FUAFScriptComponent : public FUAFAssetInstanceComponent`  
_L95-112_
- reflection: `USTRUCT(meta=(Hidden, Abstract))`
- inherits: `FUAFAssetInstanceComponent`
- desc: Asset instance component supplying user-authored scripting
- L98 _public function_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT()`
- L108 _public prototype_ `virtual void CallEventByName(TConstStructView<FUAFScriptContextData> InContextData) PURE_VIRTUAL(FUAFScriptComponent::CallEventByName, );` — Call an event with just its name, left up to derived components to implement (usually slower due to lookup)

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFScriptComponent> : public TStructOpsTypeTraitsBase2<FUAFScriptComponent>`  
_L115-121_
- inherits: `TStructOpsTypeTraitsBase2<FUAFScriptComponent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L118-120_

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L119 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anona334def10103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/TraitCore/TraitEvent.h` (Public)


#### struct `FAnimNextTraitEvent`  
`struct FAnimNextTraitEvent`  
_L37-123_
- reflection: `USTRUCT(BlueprintType)`
- desc: Trait Event Encapsulates an event in the trait system. Events can be marked as handled to signal to future handlers that no further action needs to be taken. Consuming an event prevents it from propagating to other handlers.
- L42 _public prototype_ `FAnimNextTraitEvent() = default;` — Creates a transient event
- L45 _public prototype_ `virtual ~FAnimNextTraitEvent() = default;` — Allow typesafe destruction of derived types
- L48 _public function_ `virtual UE::UAF::FTraitEventUID GetTypeUID() const` — Returns the event type UID
- L52 _public function_ `template<class EventType> bool IsA() const` — Returns whether or not this event derives from the specified type
- L55 _public function_ `virtual bool IsA(UE::UAF::FTraitEventUID InTypeUID) const` — Returns whether or not this event derives from the specified type
- L59 _public function_ `bool IsValid() const` — Returns whether or not this event is valid An event is valid if it hasn't been consumed and if it isn't expired
- L62 _public function_ `UE::UAF::FTraitEventLifetime GetLifetime() const` — Returns the lifetime of this event
- L65 _public function_ `void SetLifetime(UE::UAF::FTraitEventLifetime InLifetime)` — Sets the desired lifetime for this event
- L70 _public function_ `bool MarkHandled()` — Marks this event as being handled. Subsequent handlers can use this to determine if they should take action or not. Returns whether or not this thread succeeded in marking this event as handled
- L73 _public function_ `bool IsHandled() const` — Returns whether or not this event has been handled by a previous handler
- L78 _public function_ `bool MarkConsumed()` — Marks this event as being consumed. This event won't be forward to any other handlers. Returns whether or not this thread succeeded in marking this event as consumed
- L81 _public function_ `bool IsConsumed() const` — Returns whether or not this event has been consumed by a previous handler
- L84 _public function_ `bool IsExpired() const` — Returns whether or not this event has expired
- L87 _public function_ `bool IsInfinite() const` — Returns whether or not this event has infinite duration
- L90 _public function_ `bool IsTransient() const` — Returns whether or not this event has transient duration
- L94 _public prototype_ `bool DecrementLifetime(UE::UAF::FTraitEventList& OutputEventList);` — Decrements the lifetime count and returns whether or not this event has expired in the process OnExpired will be called on the derived type if we expire and new output events can be appended
- L98 _public function_ `template<class EventType> EventType* AsType()` — Returns a pointer to this event cast to the specified type if the TypeUIDs match, nullptr otherwise
- L102 _public function_ `template<class EventType> const EventType* AsType() const` — Returns a pointer to this event cast to the specified type if the TypeUIDs match, nullptr otherwise
- L106 _protected function_ `explicit FAnimNextTraitEvent(UE::UAF::FTraitEventLifetime InLifetime) : Lifetime(InLifetime)` — Creates an event of the specified type and associated lifetime
- L112 _protected function_ `virtual void OnExpired(UE::UAF::FTraitEventList& OutputEventList)` — Called when an events' lifetime expires
- L116 _private member_ `UE::UAF::FTraitEventLifetime Lifetime = UE::UAF::FTraitEventLifetime::MakeTransient();` — The specified lifetime of this event
- L119 _private member_ `int8 bIsHandled = 0;` — Signals whether someone has opted to handle this event
- L122 _private member_ `int8 bIsConsumed = 0;` — Signals whether someone consumed this event and it thus shouldn't be forwarded to other handlers

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L17 _typedef_ `using FTraitEventUID = UE::UAF::FConstExprUID;` (scope `UE::UAF`) — Create an alias to improve readability
- L22 _macro_ `#define DECLARE_ANIM_TRAIT_EVENT(EventName, SuperEventName) \` — Helper macros In a trait event struct declaration, this macro declares the necessary boilerplate we require
- L126 _typedef_ `using FAnimNextTraitEventPtr = TSharedPtr<FAnimNextTraitEvent, ESPMode::ThreadSafe>;` — Create a shared pointer alias for trait events
- L129 _function_ `template<class EventType, typename... TArgs> inline TSharedPtr<EventType, ESPMode::ThreadSafe> MakeTraitEvent(TArgs&&... Args)`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/TraitCore/TraitEventLifetime.h` (Public)


#### struct `UE::UAF::FTraitEventLifetime`  
`struct FTraitEventLifetime final`  
_L14-68_
- desc: Trait Event Lifetime This encapsulates a specific lifetime duration.
- L17 _public function_ `static constexpr FTraitEventLifetime MakeTransient() noexcept` — Creates a lifetime that extends until the next graph update terminates
- L23 _public function_ `static constexpr FTraitEventLifetime MakeUntil(uint32 LifetimeCount) noexcept` — Creates a lifetime that extends for the specified number of graph updates
- L29 _public function_ `static constexpr FTraitEventLifetime MakeInfinite() noexcept` — Creates a lifetime that extends forever
- L35 _public function_ `constexpr FTraitEventLifetime() noexcept : LifetimeCount(EXPIRED_LIFETIME)` — Creates an expired lifetime
- L41 _public function_ `constexpr bool IsExpired() const` — Returns whether or not this lifetime has expired
- L44 _public function_ `constexpr bool IsInfinite() const` — Returns whether or not this lifetime is infinite
- L47 _public function_ `constexpr bool IsTransient() const` — Returns whether or not this lifetime is transient
- L50 _public prototype_ `bool Decrement();` — Decrements the lifetime count and returns whether or not it has expired in the process
- L54 _private member_ `static constexpr uint32 INFINITE_LIFETIME = ~0;` — Infinite lifetime duration
- L57 _private member_ `static constexpr uint32 TRANSIENT_LIFETIME = 1;` — Transient lifetime duration
- L60 _private member_ `static constexpr uint32 EXPIRED_LIFETIME = 0;` — Expired lifetime duration
- L62 _private function_ `constexpr explicit FTraitEventLifetime(uint32 InLifetimeCount) noexcept : LifetimeCount(InLifetimeCount)`
- L67 _private member_ `uint32 LifetimeCount;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/TraitCore/TraitEventList.h` (Public)


#### struct `UE::UAF::FTraitEventList`  
`struct FTraitEventList`  
_L16-43_
- desc: Trait Event List Encapsulates a list of trait events.
- L18 _public typedef_ `using IteratorType = TArray<FAnimNextTraitEventPtr>::RangedForIteratorType;`
- L19 _public typedef_ `using ConstIteratorType = TArray<FAnimNextTraitEventPtr>::RangedForConstIteratorType;`
- L21 _public prototype_ `FTraitEventList() = default;`
- L23 _public function_ `void Push(FAnimNextTraitEventPtr Event)`
- L24 _public function_ `void Reset()`
- L25 _public function_ `int32 Num() const`
- L26 _public function_ `bool IsEmpty() const`
- L28 _public function_ `void SetNum(int32 NewNum, EAllowShrinking AllowShrinking = EAllowShrinking::Default)`
- L30 _public function_ `void Append(const FTraitEventList& Source)`
- L32 _public function_ `FAnimNextTraitEventPtr& operator[](int32 EventIndex)`
- L33 _public function_ `const FAnimNextTraitEventPtr& operator[](int32 EventIndex) const`
- L35 _public function_ `IteratorType begin()`
- L36 _public function_ `ConstIteratorType begin() const`
- L37 _public function_ `IteratorType end()`
- L38 _public function_ `ConstIteratorType end() const`
- L42 _private member_ `TArray<FAnimNextTraitEventPtr, TInlineAllocator<4>> Events;` — A list of events

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L47 _prototype_ `void DecrementLifetimeAndPurgeExpired(FTraitEventList& EventList, FTraitEventList& OutputEventList);` (scope `UE::UAF`) — Decrements and purges expired entries from the specified event list Expired events can generate new output events if they wish

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/TransformArray.h` (Public)


#### struct `UE::UAF::TTransformArrayAoS`  
`template <typename AllocatorType> struct TTransformArrayAoS`  
_L19-255_
- L21 _public member_ `TArray<FTransform, AllocatorType> Transforms;`
- L24 _public prototype_ `TTransformArrayAoS() = default;` — Default empty (no memory) Transform
- L27 _public function_ `explicit TTransformArrayAoS(const int NumTransforms)` — Create a TransformArray of N elements
- L32 _public prototype_ `~TTransformArrayAoS() = default;`
- L33 _public prototype_ `TTransformArrayAoS(const TTransformArrayAoS& Other) = default;`
- L34 _public prototype_ `TTransformArrayAoS& operator= (const TTransformArrayAoS& Other) = default;`
- L35 _public prototype_ `TTransformArrayAoS(TTransformArrayAoS&& Other) = default;`
- L36 _public prototype_ `TTransformArrayAoS& operator= (TTransformArrayAoS&& Other) = default;`
- L38 _public function_ `inline void Reset(int NumTransforms)`
- L43 _public function_ `void SetNum(int32 NumTransforms, EAllowShrinking AllowShrinking = UE::Core::Private::AllowShrinkingByDefault<AllocatorType>())`
- L48 _public function_ `void SetNumUninitialized(int32 NumTransforms, EAllowShrinking AllowShrinking = UE::Core::Private::AllowShrinkingByDefault<AllocatorType>())`
- L53 _public function_ `inline void SetIdentity(bool bAdditiveIdentity = false)`
- L58 _public function_ `inline void CopyTransforms(const TTransformArrayAoS& Other, int32 Index, int32 NumTransforms)`
- L66 _public function_ `inline int32 Num() const`
- L71 _public function_ `inline TArray<FTransform>& GetTransforms()`
- L75 _public function_ `inline const TArray<FTransform>& GetTransforms() const`
- L80 _public function_ `inline FTransform& operator[](int32 Index)`
- L85 _public function_ `inline const FTransform& operator[](int32 Index) const`
- L90 _public function_ `FTransformArrayAoSView GetView()`
- L95 _public function_ `FTransformArrayAoSConstView GetConstView() const`
- L101 _public function_ `void Blend(const TTransformArrayAoS& AtomArray1, const TTransformArrayAoS& AtomArray2, float BlendWeight)` — Set this transform array to the weighted blend of the supplied two transforms.
- L158 _public function_ `bool ContainsNaN() const`
- L179 _public function_ `bool IsValid() const`
- L198 _public function_ `void DebugFill()` — Sets the whole array to 0xCDCDCDCD to aid debugging
- L205 _private function_ `inline static void DiagnosticCheckNaN_Rotate(const FQuat& Rotation)`
- L213 _private function_ `inline static void DiagnosticCheckNaN_Scale3D(const FVector& Scale3D)`
- L221 _private function_ `inline static void DiagnosticCheckNaN_Translate(const FVector& Translation)`
- L229 _private function_ `inline void DiagnosticCheckNaN_All() const`
- L239 _private function_ `inline void DiagnosticCheck_IsValid() const`

#### struct `UE::UAF::TTransformArraySoA`  
`template <typename AllocatorType> struct TTransformArraySoA`  
_L267-648_
- desc: Transform Array Test using StructOfArrays model
- L271 _public member_ `static constexpr int32 PaddingSize = sizeof(double);` — We add a bit of padding at the end of our buffer to allow 32-byte wide load/stores without the risk of triggering access exceptions
- L272 _public member_ `static constexpr int32 TransformSize = sizeof(FVector) + sizeof(FQuat) + sizeof(FVector);`
- L274 _public member_ `TArrayView<FVector> Translations;`
- L275 _public member_ `TArrayView<FQuat> Rotations;`
- L276 _public member_ `TArrayView<FVector> Scales3D;`
- L279 _public function_ `TTransformArraySoA()` — Default empty (no memory) Transform
- L285 _public function_ `explicit TTransformArraySoA(int NumTransforms, bool bSetIdentity = true, bool bAdditiveIdentity = false)` — Create a TransformArray of N elements. Optionally initializes to identity (default)
- L295 _public prototype_ `~TTransformArraySoA() = default;`
- L297 _public function_ `TTransformArraySoA(const TTransformArraySoA& Other)`
- L306 _public function_ `TTransformArraySoA& operator= (const TTransformArraySoA& Other)`
- L317 _public function_ `TTransformArraySoA(TTransformArraySoA&& Other)`
- L322 _public function_ `TTransformArraySoA& operator= (TTransformArraySoA&& Other)`
- L328 _public function_ `inline bool IsEmpty() const`
- L333 _public function_ `inline void Empty(int32 Slack = 0)`
- L340 _public function_ `inline void Reset(int32 NumTransforms)`
- L346 _public function_ `void SetNum(int32 NumTransforms, EAllowShrinking AllowShrinking = UE::Core::Private::AllowShrinkingByDefault<AllocatorType>())`
- L354 _public function_ `void SetNumUninitialized(int32 NumTransforms, EAllowShrinking AllowShrinking = UE::Core::Private::AllowShrinkingByDefault<AllocatorType>())`
- L362 _public function_ `inline void SetIdentity(bool bAdditiveIdentity = false)`
- L369 _public function_ `inline void CopyTransforms(const TTransformArraySoA& Other, int32 Index, int32 NumTransforms)`
- L381 _public function_ `inline void CopyTransforms(const FTransformArraySoAConstView& Other, int32 Index, int32 NumTransforms)`
- L394 _public function_ `void Blend(const TTransformArraySoA& AtomArray1, const TTransformArraySoA& AtomArray2, float BlendWeight)` — Set this transform array to the weighted blend of the supplied two transforms.
- L483 _public function_ `inline int32 Num() const`
- L488 _public function_ `FTransformSoAAdapter operator[] (int Index)`
- L493 _public function_ `const FTransformSoAAdapterConst operator[] (int Index) const`
- L498 _public function_ `FTransformArraySoAView GetView()`
- L507 _public function_ `FTransformArraySoAConstView GetConstView() const`
- L516 _public function_ `bool ContainsNaN() const`
- L543 _public function_ `bool IsValid() const`
- L562 _public function_ `void DebugFill()` — Sets the whole array to 0xCDCDCDCD to aid debugging
- L568 _private member_ `TArray<uint8, AllocatorType> AllocatedMemory;` — TODO : use the allocator directly
- L570 _private function_ `void UpdateViews(uint8* Memory, int32 NumTransforms)`
- L591 _private function_ `inline static void DiagnosticCheckNaN_Scale3D(const FVector& Scale3D)`
- L599 _private function_ `inline static void DiagnosticCheckNaN_Translate(const FVector& Translation)`
- L607 _private function_ `inline static void DiagnosticCheckNaN_Rotate(const FQuat& Rotation)`
- L615 _private function_ `inline void DiagnosticCheckNaN_All() const`
- L631 _private function_ `inline void DiagnosticCheck_IsValid() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define ANIM_ENABLE_POINTER_ITERATION 1`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L16 _externvar_ `extern const FTransform TransformAdditiveIdentity;` (scope `UE::UAF`)
- L260 _typedef_ `using FTransformArrayAoSHeap = TTransformArrayAoS<FDefaultAllocator>;` (scope `UE::UAF`) — Transform Array using ArrayOfStructs model
- L261 _typedef_ `using FTransformArrayAoSStack = TTransformArrayAoS<FAnimStackAllocator>;` (scope `UE::UAF`)
- L413 _typedef_ `using TransformVectorRegister = TVectorRegisterType<double>;` (scope `UE::UAF::TTransformArraySoA::Blend`)
- L653 _typedef_ `using FTransformArraySoAHeap = TTransformArraySoA<FDefaultAllocator>;` (scope `UE::UAF`) — Transform Array using StructsOfArrays model
- L654 _typedef_ `using FTransformArraySoAStack = TTransformArraySoA<FAnimStackAllocator>;` (scope `UE::UAF`)
- L659 _macro_ `#define DEFAULT_SOA 1`
- L662 _typedef_ `template <typename AllocatorType> using TTransformArray = TTransformArraySoA<AllocatorType>;` (scope `UE::UAF`)
- L664 _typedef_ `using FTransformArrayHeap = FTransformArraySoAHeap;` (scope `UE::UAF`)
- L665 _typedef_ `using FTransformArrayStack = FTransformArraySoAStack;` (scope `UE::UAF`)
- L667 _typedef_ `using FTransformArray = FTransformArraySoAHeap;` (scope `UE::UAF`)
- L671 _typedef_ `template <typename AllocatorType> using TTransformArray = TTransformArrayAoS<AllocatorType>;` (scope `UE::UAF`)
- L673 _typedef_ `using FTransformArrayHeap = FTransformArrayAoSHeap;` (scope `UE::UAF`)
- L674 _typedef_ `using FTransformArrayStack = FTransformArrayAoSStack;` (scope `UE::UAF`)
- L676 _typedef_ `using FTransformArray = FTransformArrayAoSHeap;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/TransformArrayOperations.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L12 _prototype_ `void SetIdentity(const FTransformArrayAoSView& Dest, bool bIsAdditive);` (scope `UE::UAF`) — Sets the identity (regular or additive) over the whole destination array
- L13 _prototype_ `void SetIdentity(const FTransformArrayAoSView& Dest, bool bIsAdditive, int32 StartIndex, int32 NumTransformsToSet);` (scope `UE::UAF`)
- L14 _prototype_ `void SetIdentity(const FTransformArraySoAView& Dest, bool bIsAdditive);` (scope `UE::UAF`)
- L15 _prototype_ `void SetIdentity(const FTransformArraySoAView& Dest, bool bIsAdditive, int32 StartIndex, int32 NumTransformsToSet);` (scope `UE::UAF`)
- L19 _prototype_ `void CopyTransforms(const FTransformArrayAoSView& Dest, const FTransformArrayAoSConstView& Source, int32 StartIndex = 0, int32 NumToCopy = -1);` (scope `UE::UAF`) — Copies the specified number of transforms from a source into a destination starting at the specified start index If NumToCopy is -1, we copy until the end
- L20 _prototype_ `void CopyTransforms(const FTransformArraySoAView& Dest, const FTransformArraySoAConstView& Source, int32 StartIndex = 0, int32 NumToCopy = -1);` (scope `UE::UAF`)
- L23 _prototype_ `void NormalizeRotations(const FTransformArrayAoSView& Input);` (scope `UE::UAF`) — Normalizes rotations in input transform view
- L24 _prototype_ `void NormalizeRotations(const FTransformArraySoAView& Input);` (scope `UE::UAF`)
- L27 _prototype_ `void ConvertPoseLocalToMeshRotation(const FTransformArrayAoSView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`) — Convert a pose from local space to mesh space (rotations only)
- L28 _prototype_ `void ConvertPoseLocalToMeshRotation(const FTransformArraySoAView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`)
- L31 _prototype_ `void ConvertPoseMeshToLocalRotation(const FTransformArrayAoSView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`) — Convert a pose from mesh space to local space (rotations only)
- L32 _prototype_ `void ConvertPoseMeshToLocalRotation(const FTransformArraySoAView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`)
- L35 _prototype_ `void ConvertPoseLocalToMeshRotationTranslation(const FTransformArrayAoSView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`) — Convert a pose from local space to mesh space (rotation and translation only)
- L36 _prototype_ `void ConvertPoseLocalToMeshRotationTranslation(const FTransformArraySoAView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`)
- L39 _prototype_ `void ConvertPoseMeshToLocalRotationTranslation(const FTransformArrayAoSView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`) — Convert a pose from mesh space to local space (rotation and translation only)
- L40 _prototype_ `void ConvertPoseMeshToLocalRotationTranslation(const FTransformArraySoAView& Input, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap);` (scope `UE::UAF`)
- L46 _prototype_ `void BlendWithIdentityAndAccumulate(const FTransformArrayAoSView& Base, const FTransformArrayAoSConstView& Additive, const float BlendWeight);` (scope `UE::UAF`) — The additive transform view is blended with the additive identity using the provided blend weight We then accumulate the resulting transforms on top of the base transforms Delta = Blend(Identity, Additive, BlendWeight) Base.Accumulate(Delta);
- L47 _prototype_ `void BlendWithIdentityAndAccumulate(const FTransformArraySoAView& Base, const FTransformArraySoAConstView& Additive, const float BlendWeight);` (scope `UE::UAF`)
- L50 _prototype_ `void BlendWithIdentityAndAccumulateMesh( const FTransformArrayAoSView& Base, const FTransformArrayAoSConstView& Additive, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap, const float BlendWeight);` (scope `UE::UAF`) — Performs a BlendWithIdentityAndAccumulate in mesh space, result is in local space
- L53 _prototype_ `void BlendWithIdentityAndAccumulateMesh( const FTransformArraySoAView& Base, const FTransformArraySoAConstView& Additive, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap, const float BlendWeight);` (scope `UE::UAF`)
- L58 _prototype_ `void BlendWithIdentityAndAccumulatePerBoneWeight(const FTransformArrayAoSView& Base, const FTransformArrayAoSConstView& Additive, const TArrayView<const int32>& TransformIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultBlendWeight);` (scope `UE::UAF`) — @TODO: AoS version is untested because AoS currently does not compile in UAF.
- L60 _prototype_ `void BlendWithIdentityAndAccumulatePerBoneWeight(const FTransformArraySoAView& Base, const FTransformArraySoAConstView& Additive, const TArrayView<const int32>& TransformIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultBlendWeight);` (scope `UE::UAF`)
- L65 _prototype_ `void BlendWithIdentityAndAccumulatePerBoneWeightMesh( const FTransformArrayAoSView& Base, const FTransformArrayAoSConstView& Additive, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap, const TArrayView<const int32>& TransformIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultBlendWeight);` (scope `UE::UAF`) — Performs a BlendWithIdentityAndAccumulatePerBoneWeight in mesh space, result is in local space @TODO: AoS version is untested because AoS currently does not compile in UAF.
- L69 _prototype_ `void BlendWithIdentityAndAccumulatePerBoneWeightMesh( const FTransformArraySoAView& Base, const FTransformArraySoAConstView& Additive, const TArrayView<const FBoneIndexType>& LODBoneIndexToParentLODBoneIndexMap, const TArrayView<const int32>& TransformIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultBlendWeight);` (scope `UE::UAF`) — Performs a BlendWithIdentityAndAccumulatePerBoneWeight in mesh space, result is in local space
- L75 _prototype_ `void BlendOverwriteWithScale(const FTransformArrayAoSView& Dest, const FTransformArrayAoSConstView& Source, const float ScaleWeight);` (scope `UE::UAF`) — The source transforms are scaled by the provided weight and the result is written in the destination Dest = Source * ScaleWeight
- L76 _prototype_ `void BlendOverwriteWithScale(const FTransformArraySoAView& Dest, const FTransformArraySoAConstView& Source, const float ScaleWeight);` (scope `UE::UAF`)
- L80 _prototype_ `void BlendAddWithScale(const FTransformArrayAoSView& Dest, const FTransformArrayAoSConstView& Source, const float ScaleWeight);` (scope `UE::UAF`) — The source transforms are scaled by the provided weight and the result is added to the destination Dest = Dest + (Source * ScaleWeight)
- L81 _prototype_ `void BlendAddWithScale(const FTransformArraySoAView& Dest, const FTransformArraySoAConstView& Source, const float ScaleWeight);` (scope `UE::UAF`)
- L86 _prototype_ `void BlendOverwritePerBoneWithScale( const FTransformArrayAoSView& Dest, const FTransformArrayAoSConstView& Source, const TArrayView<const int32>& LODBoneIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultScaleWeight, const bool bInvert = false);` (scope `UE::UAF`) — The source transforms are scaled by the provided per bone weight and the result is written in the destination If bInvert is set, the bone weights are set to (1 - weight), DefaultScaleWeight remains unchanged, i.e. it is not inverted Dest = Source * (WeightIndex != INDEX_NONE ? Weights[WeightIndex] : DefaultScaleWeight)
- L89 _prototype_ `void BlendOverwritePerBoneWithScale( const FTransformArraySoAView& Dest, const FTransformArraySoAConstView& Source, const TArrayView<const int32>& LODBoneIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultScaleWeight, const bool bInvert = false);` (scope `UE::UAF`)
- L95 _prototype_ `void BlendAddPerBoneWithScale( const FTransformArrayAoSView& Dest, const FTransformArrayAoSConstView& Source, const TArrayView<const int32>& LODBoneIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultScaleWeight);` (scope `UE::UAF`) — The source transforms are scaled by the provided per bone weight and the result is added to the destination Dest = Dest + (Source * (WeightIndex != INDEX_NONE ? Weights[WeightIndex] : DefaultScaleWeight))
- L98 _prototype_ `void BlendAddPerBoneWithScale( const FTransformArraySoAView& Dest, const FTransformArraySoAConstView& Source, const TArrayView<const int32>& LODBoneIndexToWeightIndexMap, const TArrayView<const float>& BoneWeights, const float DefaultScaleWeight);` (scope `UE::UAF`)
- L104 _prototype_ `void ConvertToAdditive(const FTransformArrayAoSConstView& Input, const FTransformArrayAoSConstView& Base, const FTransformArrayAoSView& Output);` (scope `UE::UAF`) — Convert Input into an Additive Pose, by doing Output = Input - Base @TODO: AoS version is untested because AoS currently does not compile in UAF.
- L105 _prototype_ `void ConvertToAdditive(const FTransformArraySoAConstView& Input, const FTransformArraySoAConstView& Base, const FTransformArraySoAView& Output);` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/TransformArrayView.h` (Public)


#### struct `UE::UAF::TTransformSoAAdapter`  
`template <class RotationType, class TranslationType, class ScaleType> struct TTransformSoAAdapter`  
_L11-82_
- desc: This enables using a SoA array with operator[]
- L13 _public member_ `RotationType& Rotation;`
- L14 _public member_ `TranslationType& Translation;`
- L15 _public member_ `ScaleType& Scale3D;`
- L17 _public function_ `TTransformSoAAdapter(RotationType& InRotation, TranslationType& InTranslation, ScaleType& InScale3D) : Rotation(InRotation) , Translation(InTranslation) , Scale3D(InScale3D)`
- L24 _public function_ `inline RotationType& GetRotation() const`
- L29 _public function_ `inline void SetRotation(const FQuat& InRotation)`
- L34 _public function_ `inline TranslationType& GetTranslation() const`
- L39 _public function_ `inline void SetTranslation(const FVector& InTranslation)`
- L44 _public function_ `inline ScaleType& GetScale3D() const`
- L49 _public function_ `inline void SetScale3D(const FVector& InScale3D)`
- L54 _public function_ `inline operator FTransform()`
- L59 _public function_ `inline operator FTransform() const`
- L64 _public function_ `inline void operator= (const FTransform& Transform)`
- L71 _public function_ `inline void ScaleTranslation(const FVector::FReal& Scale)`
- L77 _public function_ `inline void NormalizeRotation()`

#### struct `UE::UAF::FTransformArraySoAView`  
`struct FTransformArraySoAView`  
_L90-137_
- L92 _public member_ `TArrayView<FVector> Translations;`
- L93 _public member_ `TArrayView<FQuat> Rotations;`
- L94 _public member_ `TArrayView<FVector> Scales3D;`
- L96 _public function_ `bool IsEmpty() const`
- L97 _public function_ `int32 Num() const`
- L99 _public function_ `inline FTransformSoAAdapter operator[](int32 Index)`
- L104 _public function_ `inline const FTransformSoAAdapterConst operator[](int32 Index) const`
- L109 _public function_ `bool IsValid() const`

#### struct `UE::UAF::FTransformArraySoAConstView`  
`struct FTransformArraySoAConstView`  
_L139-188_
- L141 _public member_ `TArrayView<const FVector> Translations;`
- L142 _public member_ `TArrayView<const FQuat> Rotations;`
- L143 _public member_ `TArrayView<const FVector> Scales3D;`
- L145 _public prototype_ `FTransformArraySoAConstView() = default;`
- L146 _public function_ `FTransformArraySoAConstView(const FTransformArraySoAView& Other)` — Safely coerce from mutable view
- L152 _public function_ `bool IsEmpty() const`
- L153 _public function_ `int32 Num() const`
- L155 _public function_ `inline const FTransformSoAAdapterConst operator[](int32 Index) const`
- L160 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L84 _typedef_ `using FTransformSoAAdapter = TTransformSoAAdapter<FQuat, FVector, FVector>;` (scope `UE::UAF`)
- L85 _typedef_ `using FTransformSoAAdapterConst = TTransformSoAAdapter<const FQuat, const FVector, const FVector>;` (scope `UE::UAF`)
- L87 _typedef_ `using FTransformArrayAoSView = TArrayView<FTransform>;` (scope `UE::UAF`)
- L88 _typedef_ `using FTransformArrayAoSConstView = TArrayView<const FTransform>;` (scope `UE::UAF`)
- L190 _macro_ `#define DEFAULT_SOA_VIEW 1`
- L192 _typedef_ `using FTransformArrayView = FTransformArraySoAView;` (scope `UE::UAF`)
- L193 _typedef_ `using FTransformArrayConstView = FTransformArraySoAConstView;` (scope `UE::UAF`)
- L195 _typedef_ `using FTransformArrayView = FTransformArrayAoSView;` (scope `UE::UAF`)
- L196 _typedef_ `using FTransformArrayConstView = FTransformArrayAoSConstView;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/AbstractSkeleton/AbstractSkeletonLabelBinding.h` (Public)


#### struct `FAbstractSkeleton_LabelBinding`  
`struct FAbstractSkeleton_LabelBinding`  
_L15-27_
- reflection: `USTRUCT()`
- L20 _public member_ `FName Label;` — `UPROPERTY()`
- L23 _public member_ `FName BoneName;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<const UAbstractSkeletonLabelCollection> SourceCollection;` — `UPROPERTY()`

#### class `UAbstractSkeletonLabelBinding`  
`class UAbstractSkeletonLabelBinding : public UObject`  
_L30-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L36 _public prototype_ `bool BindBoneToLabel(const TObjectPtr<const UAbstractSkeletonLabelCollection> InCollection, const FName BoneName, const FName Label);`
- L38 _public prototype_ `bool UnbindBoneFromLabel(const TObjectPtr<const UAbstractSkeletonLabelCollection> InCollection, const FName BoneName, const FName Label);`
- L40 _public prototype_ `bool AddLabelCollection(const TObjectPtr<const UAbstractSkeletonLabelCollection> InCollection);`
- L42 _public prototype_ `bool RemoveLabelCollection(const TObjectPtr<const UAbstractSkeletonLabelCollection> InCollection);`
- L44 _public prototype_ `bool SetSkeleton(const TObjectPtr<USkeleton> InSkeleton);`
- L48 _public prototype_ `bool IsLabelBound(const TObjectPtr<const UAbstractSkeletonLabelCollection> InCollection, const FName LabelName) const;`
- L50 _public prototype_ `FName GetLabelBinding(const TObjectPtr<const UAbstractSkeletonLabelCollection> InCollection, const FName LabelName) const;`
- L52 _public prototype_ `TConstArrayView<FAbstractSkeleton_LabelBinding> GetLabelBindings() const;`
- L54 _public prototype_ `TObjectPtr<USkeleton> GetSkeleton() const;`
- L56 _public prototype_ `TConstArrayView<TObjectPtr<const UAbstractSkeletonLabelCollection>> GetLabelCollections() const;`
- L60 _private member_ `TArray<TObjectPtr<const UAbstractSkeletonLabelCollection>> LabelCollections;` — `UPROPERTY()`
- L63 _private member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(AssetRegistrySearchable)`
- L66 _private member_ `TArray<FAbstractSkeleton_LabelBinding> LabelBindings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/AbstractSkeleton/AbstractSkeletonLabelCollection.h` (Public)


#### class `UAbstractSkeletonLabelCollection`  
`class UAbstractSkeletonLabelCollection : public UObject`  
_L12-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L18 _public prototype_ `bool AddLabel(const FName InLabel);`
- L20 _public prototype_ `bool RenameLabel(const FName InOldLabel, const FName InNewLabel);`
- L22 _public prototype_ `bool RemoveLabel(const FName InLabel);`
- L24 _public prototype_ `TArray<FName>& GetMutableLabels();`
- L27 _public prototype_ `bool HasLabel(const FName InLabel) const;`
- L29 _public prototype_ `TConstArrayView<FName> GetLabels() const;`
- L33 _private member_ `TArray<FName> Labels;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/AbstractSkeleton/AbstractSkeletonSetBinding.h` (Public)


#### struct `FAbstractSkeleton_BoneBinding`  
`struct FAbstractSkeleton_BoneBinding`  
_L20-29_
- reflection: `USTRUCT()`
- L25 _public member_ `FName SetName;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L28 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### struct `FAbstractSkeleton_AttributeBinding`  
`struct FAbstractSkeleton_AttributeBinding`  
_L33-42_
- reflection: `USTRUCT()`
- desc: Curves are represented as float attributes detached from any bone
- L38 _public member_ `FName SetName;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L41 _public member_ `FAnimationAttributeIdentifier Attribute;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### class `UAbstractSkeletonSetBinding`  
`class UAbstractSkeletonSetBinding : public UObject`  
_L45-146_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L51 _public prototype_ `virtual void PostLoad() override;` — UObject implementation
- L52 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L54 _public prototype_ `bool SetSkeleton(const TObjectPtr<USkeleton> InSkeleton);`
- L56 _public prototype_ `TObjectPtr<USkeleton> GetSkeleton() const;`
- L58 _public prototype_ `bool SetSetCollection(const TObjectPtr<UAbstractSkeletonSetCollection> InSetCollection);`
- L60 _public prototype_ `TObjectPtr<const UAbstractSkeletonSetCollection> GetSetCollection() const;`
- L64 _public prototype_ `bool AddBoneToSet(const FName BoneName, const FName SetName);`
- L66 _public prototype_ `bool RemoveBoneFromSet(const FName BoneName);`
- L68 _public prototype_ `bool IsBoneInSet(const FName BoneName) const;`
- L70 _public prototype_ `bool IsBoneInSet(const FName BoneName, const FName SetName) const;`
- L73 _public prototype_ `FName GetBoneSet(const FName BoneName);` — Returns the name of the set that the provided bone is in or NAME_None if bone is unbound.
- L75 _public prototype_ `const TConstArrayView<FAbstractSkeleton_BoneBinding> GetBoneBindings() const;`
- L80 _public prototype_ `void AddDefaultAttributes();` — Adds all the default attributes that should always be present
- L82 _public prototype_ `bool AddAttributeToSet(const FAnimationAttributeIdentifier Attribute, const FName SetName);`
- L89 _public prototype_ `bool RemoveAttributeFromSet(const FAnimationAttributeIdentifier Attribute);` — Note this function does two different things depending on the type of attribute provided. If the attribute is bound then it is unbound from its set. This does not remove it from the set binding and instead just assigns it to the NANE_None set. If the attribute is unbound then it is completely removed from the set binding. TODO: This function needs to be changed to avoid confusion
- L92 _public prototype_ `bool RemoveAllFromSet(const FName SetName);` — Unbinds all attributes bound to a set. Returns whether or not any attributes were removed.
- L96 _public prototype_ `[[nodiscard]] bool ContainsAttribute(const FName AttributeName) const;` — Returns if an attribute with the given name is currently stored in this set binding. Note that an attribute existing does not mean it is bound to a set.
- L99 _public prototype_ `bool IsAttributeInSet(const FAnimationAttributeIdentifier Attribute) const;` — Returns true if the provided attribute is in ANY set
- L102 _public prototype_ `bool IsAttributeInSet(const FAnimationAttributeIdentifier Attribute, const FName SetName) const;` — Returns true if the provided attribute is in the provided set
- L104 _public prototype_ `const TConstArrayView<FAbstractSkeleton_AttributeBinding> GetAttributeBindings() const;`
- L107 _public prototype_ `FDelegateHandle RegisterOnBindingsChanged(FSimpleMulticastDelegate::FDelegate&& InDelegate);`
- L108 _public prototype_ `bool UnregisterOnBindingsChanged(const FDelegateHandle InHandle);`
- L113 _private prototype_ `void OnSkeletonChanged();`
- L115 _private prototype_ `void OnSetCollectionChanged();`
- L119 _private prototype_ `void FilterOrphanedBindings();` — If a change is made to the set collection while we are loaded/unloaded we need to remove any bindings that are bound to invalid sets
- L123 _private prototype_ `void OnBindingsChanged();` — Called internally whenever a change is made to the attribute bindings (bones + attributes)
- L125 _private prototype_ `void RebuildBindingData();`
- L128 _private member_ `TObjectPtr<UAbstractSkeletonSetCollection> SetCollection;` — `UPROPERTY()`
- L131 _private member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(AssetRegistrySearchable)`
- L134 _private member_ `TArray<FAbstractSkeleton_BoneBinding> BoneBindings;` — `UPROPERTY()`
- L137 _private member_ `TArray<FAbstractSkeleton_AttributeBinding> AttributeBindings;` — `UPROPERTY()`
- L142 _private member_ `FDelegateHandle SetCollectionChangedHandle;`
- L144 _private member_ `FSimpleMulticastDelegate OnBindingsChangedDelegate;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/AbstractSkeleton/AbstractSkeletonSetCollection.h` (Public)


#### struct `FAbstractSkeletonSet`  
`struct FAbstractSkeletonSet`  
_L12-21_
- reflection: `USTRUCT()`
- L17 _public member_ `FName SetName;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L20 _public member_ `FName ParentSetName;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### class `UAbstractSkeletonSetCollection`  
`class UAbstractSkeletonSetCollection : public UObject`  
_L24-69_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L29 _public prototype_ `bool AddSet(const FName SetName, const FName ParentSetName = NAME_None);`
- L31 _public prototype_ `bool HasSet(const FName SetName) const;`
- L33 _public prototype_ `bool RenameSet(const FName OldSetName, const FName NewSetName);`
- L36 _public prototype_ `bool RemoveSet(const FName SetName);` — Removes this set and moves its children to this set's parent
- L38 _public prototype_ `bool ReparentSet(const FName SetName, const FName NewParentName);`
- L41 _public prototype_ `const TArrayView<const FAbstractSkeletonSet> GetSetHierarchy() const;` — Returns the sets in this set collection sorted topologically
- L43 _public prototype_ `FName GetParentSetName(const FName SetName) const;`
- L47 _public prototype_ `bool IsDescendantOf(const FName SetName, const FName AncestorSetName) const;` — Returns true if SetName is a descendant of AncestorSetName. This is for strict descendants, i.e. a set is not a descendant of itself.
- L50 _public prototype_ `FDelegateHandle RegisterOnSetsChanged(FSimpleMulticastDelegate::FDelegate&& InDelegate);`
- L51 _public prototype_ `bool UnregisterOnSetsChanged(const FDelegateHandle InHandle);`
- L55 _private prototype_ `bool IsValidSetName(const FName SetName) const;`
- L57 _private prototype_ `int32 GetSetIndex(const FName SetName) const;`
- L59 _private prototype_ `void SortSetHierarchy();`
- L61 _private prototype_ `FAbstractSkeletonSet& GetSetRef(const FName SetName);`
- L64 _private member_ `TArray<FAbstractSkeletonSet> SetHierarchy;` — `UPROPERTY()`
- L67 _private member_ `FSimpleMulticastDelegate OnSetsChanged;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeBindingData.h` (Public)


#### class `UE::UAF::FAttributeBindingData`  
`class FAttributeBindingData : public UE::Private::FQueryableRefCountedObject`  
_L23-139_
- inherits: `UE::Private::FQueryableRefCountedObject`
- desc: Our baked abstract skeleton binding data This class is ref counted and all named/typed sets increment/decrement its ref count
- L26 _public typedef_ `using NamedSetMapType = TSortedMap<FName, FAttributeNamedSet*, FDefaultAllocator, FNameFastLess>;`
- L72 _public prototype_ `[[nodiscard]] int32 NumNamedSets() const;` — Returns the number of named sets, O(1)
- L75 _public prototype_ `[[nodiscard]] int32 NumLODs() const;` — Returns the number of LODs, O(1)
- L78 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not this binding is empty, O(1)
- L82 _public prototype_ `[[nodiscard]] int32 NumAttributes(UScriptStruct* AttributeType) const;` — Returns the number of attributes of the specified type, O(1) Note that some attributes might not be part of any named/typed sets
- L86 _public prototype_ `[[nodiscard]] FAttributeNamedSetPtr FindNamedSet(FName SetName) const;` — Returns the named set with the specified name, O(logN) Returns null if no set with that name is found
- L89 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT FNamedSetIterator CreateNamedSetIterator() const` — Returns an iterator over all named sets contained within
- L93 _public prototype_ `[[nodiscard]] FAttributeBindingIndex FindBindingIndex(FName AttributeName, UScriptStruct* AttributeType) const;` — Returns the attribute binding index for the specified attribute, O(N) Returns an invalid index if the attribute isn't found
- L96 _public prototype_ `[[nodiscard]] FPoseValueBundlePtr GetDefaultAttributeValues(FName SetName) const;` — Returns a collection of the default attribute values for the specified named set
- L99 _public prototype_ `uint32 Release() const;` — UE::Private::FQueryableRefCountedObject API
- L104 _private prototype_ `FAttributeBindingData(TNonNullPtr<const UAbstractSkeletonSetBinding> Binding, const USkeletalMesh* SkeletalMesh);`
- L105 _private prototype_ `void ResetInternalReferences();`
- L112 _private member_ `TArray<FAttributeNamedSet> NamedSets;` — A named set entry per LOD (NumSets * NumLODs) Using the LOD index within the named set, we can quickly navigate to other LODs using a pointer offset
- L116 _private member_ `TArray<FAttributeTypedSet> TypedSets;` — A typed set entry per type and LOD for each named set (NumSets * NumTypes * NumLODs) Using the LOD index within the outer named set, we can quickly navigate to other LODs using a pointer offset
- L119 _private member_ `NamedSetMapType NamedSetMap;` — A map of set names to its named set data (at LOD 0)
- L124 _private member_ `TMap<UScriptStruct*, TArray<FName>> AttributeNamesByType;` — A map of attribute type to a map of their name to their attribute binding index Bone attribute names aren't sorted, they are in the same order as in the skeleton All other attribute names are sorted by FName
- L127 _private member_ `TMap<FName, FPoseValueBundlePtr> DefaultAttributeValuesByName;` — Default attribute values for each named set
- L130 _private member_ `TMap<FSkeletonPoseBoneIndex, FMeshPoseBoneIndex> SkeletonToMeshIndicesMap;` — Only filled when executing with a skeletal mesh
- L133 _private member_ `TWeakObjectPtr<const UAbstractSkeletonSetBinding> BindingAsset;` — The source binding asset used to create this binding data
- L136 _private member_ `uint32 NumInternalReferences = 0;` — The number of internal references for the purposes of reference counting

#### class `UE::UAF::FAttributeBindingData::FNamedSetIterator`  
`class FNamedSetIterator`  
_L28-69_
- L31 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT explicit FNamedSetIterator(const NamedSetMapType& NamedSetMap) : Iterator(NamedSetMap.CreateConstIterator())`
- L36 _public function_ `UE_FORCEINLINE_HINT FNamedSetIterator& operator++()`
- L43 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT explicit operator bool() const` — conversion to "bool" returning true if the iterator is valid.
- L48 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool operator==(const FNamedSetIterator& Rhs) const`
- L52 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool operator!=(const FNamedSetIterator& Rhs) const`
- L57 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT FAttributeNamedSetPtr operator*() const`
- L62 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT const FAttributeNamedSet* operator->() const`
- L68 _private member_ `NamedSetMapType::TConstIterator Iterator;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L19 _typedef_ `using FAttributeBindingDataPtr = TRefCountPtr<const class FAttributeBindingData>;` (scope `UE::UAF`)
- L143 _prototype_ `[[nodiscard]] FAttributeBindingDataPtr MakeAttributeBindingData(TNonNullPtr<const UAbstractSkeletonSetBinding> Binding, const USkeletalMesh* SkeletalMesh);` (scope `UE::UAF`) — Creates a new attribute binding data instance from the specified binding Returns null if the binding isn't valid

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeBindingDataCache.h` (Public)


#### class `UE::UAF::Private::FSetBindingAttributeBindingDataCache`  
`class FSetBindingAttributeBindingDataCache`  
_L16-30_
- L19 _public prototype_ `FSetBindingAttributeBindingDataCache() = delete;`
- L20 _public prototype_ `explicit FSetBindingAttributeBindingDataCache(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding);`
- L22 _public prototype_ `FAttributeBindingDataPtr GetOrAdd(const USkeletalMesh* SkeletalMesh);`
- L25 _private member_ `const FAttributeBindingDataPtr SkeletonBindingData;`
- L26 _private member_ `const TWeakObjectPtr<const UAbstractSkeletonSetBinding> WeakSetBinding;`
- L28 _private member_ `TMap<FObjectKey, FAttributeBindingDataPtr> SkeletalMeshBindingData;`
- L29 _private member_ `FTransactionallySafeRWLock CacheLock;`

#### class `UE::UAF::FAttributeBindingDataCache`  
`class FAttributeBindingDataCache`  
_L36-47_
- desc: A thread-safe global cache for mapping set bindings to the cache of attribute data for each skeletal mesh using that binding
- L39 _public prototype_ `FAttributeBindingDataPtr GetOrAdd(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding, const USkeletalMesh* SkeletalMesh);`
- L41 _public prototype_ `void ResetSetBinding(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding);`
- L42 _public prototype_ `void Reset();`
- L45 _private member_ `FTransactionallySafeRWLock CacheLock;`
- L46 _private member_ `TMap<FObjectKey, FSetBindingAttributeBindingDataCachePtr> SetBindingToCache;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::UAF`)
- L33 _typedef_ `using FSetBindingAttributeBindingDataCachePtr = TSharedPtr<Private::FSetBindingAttributeBindingDataCache>;` (scope `UE::UAF`)
- L49 _externvar_ `extern FAttributeBindingDataCache GAttributeBindingDataCache;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeBindingIndex.h` (Public)


#### struct `UE::UAF::FAttributeBindingIndex`  
`struct FAttributeBindingIndex final : public FBoneIndexBase`  
_L11-42_
- inherits: `FBoneIndexBase`
- desc: This represents an attribute index within a binding asset
- L15 _public prototype_ `FAttributeBindingIndex() = default;` — Constructs an invalid index
- L18 _public function_ `explicit FAttributeBindingIndex(int32 InAttributeBindingIndex)` — Constructs an index with the specified value
- L21 _public function_ `explicit FAttributeBindingIndex(FSkeletonPoseBoneIndex SkeletonBoneIndex)` — Constructs an index with the specified skeleton bone index
- L28 _public function_ `FSkeletonPoseBoneIndex GetSkeletonBoneIndex() const` — Returns the skeleton bone index that maps to this binding index (only valid for bones)
- L35 _public function_ `operator FSkeletonPoseBoneIndex() const` — Returns the skeleton bone index that maps to this binding index (only valid for bones)

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeDescription.h` (Public)


#### struct `UE::UAF::FAttributeDescription`  
`struct FAttributeDescription`  
_L10-33_
- desc: An attribute description
- L13 _public member_ `FName Name;` — Our attribute name
- L16 _public member_ `FName ParentName;` — The attribute name of our parent (or None if we are at the root)
- L19 _public member_ `UScriptStruct* Type = nullptr;` — The attribute type
- L22 _public member_ `int32 LOD = 0;` — The LOD at which this attribute is active
- L24 _public prototype_ `FAttributeDescription() = default;`
- L26 _public function_ `FAttributeDescription(FName InName, FName InParentName, UScriptStruct* InType, int32 InLOD) : Name(InName) , ParentName(InParentName) , Type(InType) , LOD(InLOD)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeNamedSet.h` (Public)


#### class `UE::UAF::FAttributeNamedSet`  
`class FAttributeNamedSet`  
_L19-129_
- L22 _public typedef_ `using TypedSetMapType = TSortedMap<UScriptStruct*, FAttributeTypedSet*>;`
- L68 _public prototype_ `[[nodiscard]] FAttributeBindingDataPtr GetBindingData() const;` — Returns the owning binding data this named set is part of
- L71 _public prototype_ `[[nodiscard]] FName GetName() const;` — Returns the name of this set, O(1)
- L74 _public prototype_ `[[nodiscard]] int32 GetLOD() const;` — Returns the LOD of this set, O(1)
- L77 _public prototype_ `[[nodiscard]] int32 NumTypedSets() const;` — Returns the number of typed sets within this set, O(1)
- L80 _public prototype_ `[[nodiscard]] int32 NumLODs() const;` — Returns the number of distinct LODs in this set, O(1)
- L83 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not this set is empty, O(1)
- L87 _public prototype_ `template <class AttributeType> [[nodiscard]] FAttributeTypedSetPtr FindTypedSet() const;` — Returns the typed set associated with the specified type, O(logN)
- L90 _public prototype_ `[[nodiscard]] FAttributeTypedSetPtr FindTypedSet(UScriptStruct* Type) const;` — Returns the typed set associated with the specified type, O(logN)
- L94 _public prototype_ `[[nodiscard]] FAttributeNamedSetPtr AtLOD(int32 LOD) const;` — Returns this named set at the specified LOD, O(1) Returns null if the LOD specified is invalid
- L97 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT FTypedSetIterator CreateTypedSetIterator() const` — Returns an iterator over all typed sets contained within
- L100 _public prototype_ `[[nodiscard]] FPoseValueBundlePtr GetDefaultAttributeValues() const;` — Returns a collection of the default attribute values for this named set
- L103 _public prototype_ `void AddRef() const;` — Reference counting API
- L104 _public prototype_ `uint32 Release() const;`
- L105 _public prototype_ `[[nodiscard]] uint32 GetRefCount() const;`
- L110 _private prototype_ `FAttributeNamedSet();`
- L113 _private member_ `FName Name;` — The name of this set
- L116 _private member_ `int32 LOD = 0;` — The LOD of this named set instance
- L119 _private member_ `int32 SetNumLODs = 0;` — The number of LODs within this named set instance
- L122 _private member_ `FAttributeBindingData* Owner = nullptr;` — The binding data that owns our memory
- L125 _private member_ `TypedSetMapType TypedSetMap;` — A map of attribute type to its typed set within our named set
- L135 _function_ `template <class AttributeType> inline FAttributeTypedSetPtr FAttributeNamedSet::FindTypedSet() const`

#### class `UE::UAF::FAttributeNamedSet::FTypedSetIterator`  
`class FTypedSetIterator`  
_L24-65_
- L27 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT explicit FTypedSetIterator(const TypedSetMapType& TypedSetMap) : Iterator(TypedSetMap.CreateConstIterator())`
- L32 _public function_ `UE_FORCEINLINE_HINT FTypedSetIterator& operator++()`
- L39 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT explicit operator bool() const` — conversion to "bool" returning true if the iterator is valid.
- L44 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool operator==(const FTypedSetIterator& Rhs) const`
- L48 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool operator!=(const FTypedSetIterator& Rhs) const`
- L53 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT FAttributeTypedSetPtr operator*() const`
- L58 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT const FAttributeTypedSet* operator->() const`
- L64 _private member_ `TypedSetMapType::TConstIterator Iterator;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L15 _typedef_ `using FAttributeBindingDataPtr = TRefCountPtr<const class FAttributeBindingData>;` (scope `UE::UAF`)
- L16 _typedef_ `using FPoseValueBundlePtr = TSharedPtr<class FPoseValueBundle, ESPMode::ThreadSafe>;` (scope `UE::UAF`)
- L17 _typedef_ `using FAttributeNamedSetPtr = TRefCountPtr<const class FAttributeNamedSet>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeSetIndex.h` (Public)


#### struct `UE::UAF::FAttributeSetIndex`  
`struct FAttributeSetIndex final : public FBoneIndexBase`  
_L11-21_
- inherits: `FBoneIndexBase`
- desc: This represents an attribute index within an attribute set
- L15 _public prototype_ `FAttributeSetIndex() = default;` — Constructs an invalid index
- L18 _public function_ `explicit FAttributeSetIndex(int32 InAttributeIndex)` — Constructs an index with the specified value

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeSetKey.h` (Public)


#### class `UE::UAF::FAttributeSetKey`  
`class FAttributeSetKey final`  
_L23-60_
- desc: The key by which to sort out attributes within a set We want attributes with a higher LOD value to come first (e.g. LOD 0 before LOD 1) to allow us to truncate the attribute array for a specific LOD We want parent attributes to come before their children to facilitate space conversion It has the following format: - Bits [0, 15]:	Attribute binding index (1-based) (16 bits) - Bits [16, 31]:	Parent attribute binding index (1-based, 0 if we have no parent) (16 bits) - Bits [32, 39]:	LOD (8 bits) This allows us to sort smaller values first This means that set keys are consistent within a binding and can be used by multiple named/typed sets within and compared accordingly. However, they cannot be used across binding assets.
- L26 _public prototype_ `constexpr FAttributeSetKey() = default;`
- L27 _public function_ `constexpr FAttributeSetKey(const FAttributeSetKey& Other) : Value(Other.Value)`
- L28 _public function_ `constexpr FAttributeSetKey(FAttributeSetKey&& Other) : Value(Other.Value)`
- L30 _public prototype_ `[[nodiscard]] FAttributeSetKey(FAttributeBindingIndex BindingIndex, FAttributeBindingIndex ParentBindingIndex, int32 LOD);`
- L32 _public function_ `[[nodiscard]] bool IsValid() const`
- L34 _public function_ `[[nodiscard]] int32 GetLOD() const`
- L35 _public function_ `[[nodiscard]] FAttributeBindingIndex GetBindingIndex() const`
- L36 _public function_ `[[nodiscard]] FAttributeBindingIndex GetParentBindingIndex() const`
- L38 _public function_ `FAttributeSetKey& operator=(const FAttributeSetKey& Rhs)`
- L39 _public function_ `FAttributeSetKey& operator=(FAttributeSetKey&& Rhs)`
- L41 _public function_ `[[nodiscard]] explicit operator bool() const`
- L46 _public function_ `[[nodiscard]] bool operator==(FAttributeSetKey Rhs) const` — Relational operators
- L47 _public function_ `[[nodiscard]] bool operator!=(FAttributeSetKey Rhs) const`
- L48 _public function_ `[[nodiscard]] bool operator>(FAttributeSetKey Rhs) const`
- L49 _public function_ `[[nodiscard]] bool operator>=(FAttributeSetKey Rhs) const`
- L50 _public function_ `[[nodiscard]] bool operator<(FAttributeSetKey Rhs) const`
- L51 _public function_ `[[nodiscard]] bool operator<=(FAttributeSetKey Rhs) const`
- L54 _private member_ `static constexpr uint64 kLODShift = 32;`
- L55 _private member_ `static constexpr uint64 kParentIndexShift = 16;`
- L56 _private member_ `static constexpr uint64 kIndexMask = 0x0000FFFFULL;`
- L57 _private member_ `static constexpr uint64 kLODMask = 0x000000FFULL;`
- L59 _private member_ `uint64 Value = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAF_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L43 _function_ `[[nodiscard]] friend uint32 GetTypeHash(FAttributeSetKey SetKey)` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/AttributeTypedSet.h` (Public)


#### class `UE::UAF::FAttributeTypedSet`  
`class FAttributeTypedSet`  
_L23-131_
- L29 _public prototype_ `[[nodiscard]] FAttributeNamedSetPtr GetNamedSet() const;` — Returns the named set this typed set is part of
- L32 _public prototype_ `[[nodiscard]] FAttributeBindingDataPtr GetBindingData() const;` — Returns the owning binding data this typed set is part of
- L35 _public prototype_ `[[nodiscard]] UScriptStruct* GetType() const;` — Returns the type of attributes held in this set, O(1)
- L38 _public prototype_ `[[nodiscard]] int32 GetLOD() const;` — Returns the LOD of this set, O(1)
- L41 _public prototype_ `[[nodiscard]] int32 Num() const;` — Returns the number of attributes in this set, O(1)
- L44 _public prototype_ `[[nodiscard]] int32 NumLODs() const;` — Returns the number of distinct LODs in this set, O(1)
- L47 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not this set is empty, O(1)
- L51 _public prototype_ `[[nodiscard]] FAttributeTypedSetPtr AtLOD(int32 LOD) const;` — Returns the typed set of the same type at the specified LOD, O(1) Returns null if the LOD specified is invalid
- L55 _public prototype_ `[[nodiscard]] FAttributeSetKey FindKey(FName AttributeName) const;` — Searches for an attribute set key using an attribute name, O(logN) Returns an invalid key if the attribute isn't found within the set
- L59 _public prototype_ `[[nodiscard]] FName FindName(FAttributeSetKey AttributeKey) const;` — Searches for an attribute name using an attribute set key, O(logN) Returns None if the attribute isn't found within the set
- L63 _public prototype_ `[[nodiscard]] FAttributeSetIndex FindIndex(FName AttributeName) const;` — Searches for an attribute set index using an attribute name, O(logN) Returns an invalid index if the attribute isn't found within the set
- L67 _public prototype_ `[[nodiscard]] FAttributeSetIndex FindIndex(FAttributeSetKey AttributeKey) const;` — Searches for an attribute set index using an attribute set key, O(logN) Returns an invalid index if the attribute isn't found within the set
- L71 _public prototype_ `[[nodiscard]] FAttributeBindingIndex FindBindingIndex(FName AttributeName) const;` — Searches for an attribute binding index using an attribute name, O(N) Returns an invalid index if the attribute isn't found within the binding
- L75 _public prototype_ `[[nodiscard]] FAttributeSetIndex GetIndex(FAttributeBindingIndex BindingIndex) const;` — Retrieve an attribute set index using an attribute binding index, O(1) Returns an invalid index if the attribute isn't found within the set
- L79 _public prototype_ `[[nodiscard]] FAttributeBindingIndex GetBindingIndex(FAttributeSetIndex AttributeIndex) const;` — Retrieve an attribute binding index using an attribute set index, O(1) Returns an invalid index if the attribute set index is invalid
- L83 _public prototype_ `[[nodiscard]] FAttributeSetIndex GetParentIndex(FAttributeSetIndex AttributeIndex) const;` — Retrieves the parent attribute index of the specified attribute, O(1) Returns an invalid index if the child attribute index is invalid or the parent isn't within this set
- L87 _public prototype_ `[[nodiscard]] FName GetName(FAttributeSetIndex AttributeIndex) const;` — Retrieve the name of the specified attribute, O(1) Returns None if the attribute set index is invalid
- L91 _public prototype_ `[[nodiscard]] FAttributeSetKey GetKey(FAttributeSetIndex AttributeIndex) const;` — Retrieves the set key of the specified attribute, O(1) Returns an invalid set key if the attribute set index is invalid
- L94 _public prototype_ `void AddRef() const;` — Reference counting API
- L95 _public prototype_ `uint32 Release() const;`
- L96 _public prototype_ `[[nodiscard]] uint32 GetRefCount() const;`
- L99 _private prototype_ `FAttributeTypedSet();`
- L100 _private prototype_ `void Init(TConstArrayView<FAttributeDescription> SetAttributes, TConstArrayView<FName> BindingAttributes);`
- L101 _private prototype_ `void Reset();`
- L104 _private member_ `UScriptStruct* Type = nullptr;` — The type that attributes in this set have
- L107 _private member_ `FAttributeBindingData* Owner = nullptr;` — The outer container that owns our memory
- L110 _private member_ `FAttributeNamedSet* NamedSet = nullptr;` — The named set that contains us
- L113 _private member_ `TArray<TTuple<FName, uint16>> AttributeNameToIndexMap;` — Sorted list of attribute names, maps a name to its attribute index
- L116 _private member_ `TArray<FAttributeSetKey> AttributeKeys;` — List of attributes (sorted by key)
- L119 _private member_ `TArray<FName> AttributeNames;` — List of attribute names (sorted by key)
- L122 _private member_ `TArray<uint16> ParentAttributeIndices;` — List of parent attribute set indices (sorted by key)
- L125 _private member_ `TArray<uint16> BindingIndices;` — List of attribute binding indices (sorted by key)
- L128 _private member_ `TArray<uint16> BindingIndexToSetIndexMap;` — Maps each attribute binding index to an attribute set index

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L19 _typedef_ `using FAttributeBindingDataPtr = TRefCountPtr<const class FAttributeBindingData>;` (scope `UE::UAF`)
- L20 _typedef_ `using FAttributeNamedSetPtr = TRefCountPtr<const class FAttributeNamedSet>;` (scope `UE::UAF`)
- L21 _typedef_ `using FAttributeTypedSetPtr = TRefCountPtr<const class FAttributeTypedSet>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/Attributes/EngineAttributes.h` (Public)


#### struct `FBoneTransformAnimationAttribute`  
`struct FBoneTransformAnimationAttribute : public FTransformAnimationAttribute`  
_L14-20_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTransformAnimationAttribute`
- desc: A bone transform is a special attribute type that allows for template specialization

#### struct `UE::Anim::TAttributeTypeTraits`  
`template<> struct TAttributeTypeTraits<FBoneTransformAnimationAttribute> : public TAttributeTypeTraits<FTransformAnimationAttribute>`  
_L25-28_
- inherits: `TAttributeTypeTraits<FTransformAnimationAttribute>`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Anim` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace UAF` (scope `UE`)
- L34 _prototype_ `void RegisterEngineAttributes();` (scope `UE::UAF`) — Handles registration for built-in engine attributes and value types

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/BlendMask/UAFBlendMask.h` (Public)


#### class `UUAFBlendMask`  
`class UUAFBlendMask : public UObject`  
_L21-73_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, BlueprintType)`
- inherits: `UObject`
- desc: An asset to define what parts to include in a blend when layering.
- L26 _public typedef_ `using FSkeletonBoneWeightArray = TArray<float>;`
- L27 _public typedef_ `using FSkeletonCurveWeightArray = UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement>;`
- L28 _public typedef_ `using FSkeletonAttributeWeightArray = TArray<FBlendProfileStandaloneCachedData::FMaskedAttributeWeight>;`
- L31 _public prototype_ `virtual void PostLoad() override;`
- L33 _public prototype_ `virtual void BeginDestroy() override;`
- L34 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L39 _public prototype_ `void UpdateHierarchy();`
- L41 _public prototype_ `void UpdateCachedData();`
- L44 _public prototype_ `TObjectPtr<USkeleton> GetSkeleton() const;`
- L46 _public prototype_ `const FSkeletonBoneWeightArray& GetSkeletonBoneWeights() const;`
- L47 _public prototype_ `const FSkeletonCurveWeightArray& GetSkeletonCurveWeights() const;`
- L48 _public prototype_ `const FSkeletonAttributeWeightArray& GetSkeletonAttributeWeights() const;`
- L53 _private member_ `TObjectPtr<UHierarchyTable> Table;` — `UPROPERTY()`
- L59 _private member_ `FBlendProfileStandaloneCachedData CachedBlendProfileData;` — `UPROPERTY()` — The flattened version of the table data for use at runtime instead of, slowly traversing the table tree.
- L63 _private prototype_ `void SetSkeleton(TObjectPtr<USkeleton> InSkeleton);`
- L65 _private prototype_ `void HandleSkeletonHierarchyChanged();`
- L69 _private member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = Default)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/BlendProfile/UAFBlendProfile.h` (Public)


#### enum `EUAFBlendProfileType`  
`enum class EUAFBlendProfileType`  
_L24-28_
- reflection: `UENUM()`
- L26 _public enumerator_ `WeightFactor`
- L27 _public enumerator_ `TimeFactor`

#### class `UUAFBlendProfile`  
`class UUAFBlendProfile : public UObject`  
_L32-96_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, BlueprintType)`
- inherits: `UObject`
- desc: An asset to define how a blend should be applied in a transition with per-bone controls.
- L37 _public typedef_ `using FSkeletonBoneWeightArray = TArray<float>;`
- L38 _public typedef_ `using FSkeletonCurveWeightArray = UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement>;`
- L39 _public typedef_ `using FSkeletonAttributeWeightArray = TArray<FBlendProfileStandaloneCachedData::FMaskedAttributeWeight>;`
- L42 _public prototype_ `virtual void PostLoad() override;`
- L44 _public prototype_ `virtual void BeginDestroy() override;`
- L45 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L46 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L51 _public prototype_ `void UpdateHierarchy();`
- L53 _public prototype_ `void UpdateCachedData();`
- L56 _public prototype_ `TObjectPtr<USkeleton> GetSkeleton() const;`
- L59 _public prototype_ `EUAFBlendProfileType GetType() const;` — Returns whether this blend profile is a time-based or weight-based time profile.
- L64 _public prototype_ `EBlendProfileMode GetEngineType() const;` — Similar to GetType but returns the value in terms of the engine blend profile mode. Used for reusing UBlendProfile engine code for UAF blend profiles. Will never return EBlendProfileMode::BlendMask.
- L66 _public prototype_ `const FSkeletonBoneWeightArray& GetSkeletonBoneWeights() const;`
- L67 _public prototype_ `const FSkeletonCurveWeightArray& GetSkeletonCurveWeights() const;`
- L68 _public prototype_ `const FSkeletonAttributeWeightArray& GetSkeletonAttributeWeights() const;`
- L72 _private member_ `EUAFBlendProfileType Type;` — `UPROPERTY(VisibleAnywhere, Category = Default, AssetRegistrySearchable)`
- L76 _private member_ `TObjectPtr<UHierarchyTable> Table;` — `UPROPERTY()`
- L82 _private member_ `FBlendProfileStandaloneCachedData CachedBlendProfileData;` — `UPROPERTY()` — The flattened version of the table data for use at runtime instead of, slowly traversing the table tree.
- L86 _private prototype_ `void SetSkeleton(TObjectPtr<USkeleton> InSkeleton);`
- L88 _private prototype_ `void HandleSkeletonHierarchyChanged();`
- L92 _private member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = Default)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L18 _variable_ `inline const FName AssetRegistryTag_BlendProfileType = TEXT("Ble` (scope `UE::UAF`)
- L19 _variable_ `inline const FString AssetRegistryTag_BlendProfileType_TimeProfile = TEXT("Tim` (scope `UE::UAF`)
- L20 _variable_ `inline const FString AssetRegistryTag_BlendProfileType_WeightProfile = TEXT("Wei` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/UAFAssetData.h` (Public)


#### struct `FUAFAssetData`  
`struct FUAFAssetData`  
_L21-38_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: FUAFAssetData is the encapsulation of a UAF compatible asset. It is used by the System and Graph factories to produce UAF assets. Generally a UAFAssetData will correspond to e.g. an animation sequence, a blend space, a chooser table etc. Plugins can define their own asset data types and register them with the appropriate factories (e.g. FAnimGraphFactory, FSystemFactory) to define how the asset should be transformed into a UAF. It can also be registered with the UAF::FAssetDataFactory to enable drag and drop functionality from UObject
- L24 _public function_ `virtual ~FUAFAssetData()`
- L27 _public function_ `virtual bool Validate() const` — If false, this data is not valid to attempt to construct a UAF asset from
- L29 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const`
- L31 _public function_ `virtual bool CompareAsset(const TConstStructView<FUAFAssetData>& Other) const`
- L33 _public function_ `virtual uint32 GetAssetTypeHash() const`
- L36 _public prototype_ `virtual FString GetName() const;`

#### struct `FUAFSystemFactoryAsset`  
`struct FUAFSystemFactoryAsset : public FUAFAssetData`  
_L42-45_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FUAFAssetData`
- desc: Assets deriving from this type can be used to create an animation system via the system factory

#### struct `FUAFGraphFactoryAsset`  
`struct FUAFGraphFactoryAsset : public FUAFSystemFactoryAsset`  
_L49-52_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FUAFSystemFactoryAsset`
- desc: Assets deriving from this type can be used to create an animation graph via the animation graph factory

#### Free symbols / members of external scopes

- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace UAF` (scope `UE`)
- L57 _typedef_ `using FAssetHandle = TInstancedStruct<FUAFAssetData>;` (scope `UE::UAF`)
- L59 _typedef_ `using FSystemAssetHandle = TInstancedStruct<FUAFSystemFactoryAsset>;` (scope `UE::UAF`)
- L60 _typedef_ `using FSystemAssetHandleConstView = TConstStructView<FUAFSystemFactoryAsset>;` (scope `UE::UAF`)
- L62 _typedef_ `using FGraphAssetHandle = TInstancedStruct<FUAFGraphFactoryAsset>;` (scope `UE::UAF`)
- L63 _typedef_ `using FGraphAssetHandleConstView = TConstStructView<FUAFGraphFactoryAsset>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/UAFAssetFactory.h` (Public)


#### struct `UE::UAF::FAssetDataFactory`  
`struct FAssetDataFactory`  
_L22-117_
- desc: The FAssetDataFactory is used to produce FUAFAssetData from UObjects. This is mostly used for UI interactions in editor when users drop objects on to FUAFAssetData slots, for deprecation and also for some legacy API that takes UObject* directly to create UAF graphs + systems. This factory links UObject class types to FUAFAssetData types. Note: It is not a requirement for a FUAFAssetData be created from a UObject. It could also be created manually
- L27 _public prototype_ `static TInstancedStruct<FUAFAssetData> CreateUAFAssetDataFromObject(const UObject* Object);` — Create a UAFAssetData object from the supplied Object
- L32 _public function_ `template<typename TAssetDataType> static TInstancedStruct<TAssetDataType> CreateUAFAssetDataFromObject(const UObject* Object)` — Attempt to create a typed version of a UAF asset data from a UObject. This checks that the desired TAssetDataType Is a base class of the found initializer that corresponds to the UObject class supplied
- L57 _public typedef_ `template<typename TAssetDataType, typename TObjectType> using TAssetInitializer = TFunction<TAssetDataType(const TObjectType*)>;`
- L64 _public function_ `template<typename TAssetDataType, typename TObjectType> [[nodiscard]] static FTopLevelAssetPath RegisterAsset(TAssetInitializer<TAssetDataType, TObjectType>&& Initializer)` — Register an UAF asset with the factory This defines a relationship between the TObjectType and the TAssetDataType. The initializer definnes how to create a TAssetDataType from a TObjectType instance @return a FTopLevelAssetPath that can be used to unregister the asset type via UnregisterAsset
- L74 _public prototype_ `static void UnregisterAsset(const FTopLevelAssetPath& InObjectClassPath);` — Unregister an UAF asset with the factory
- L77 _public prototype_ `static TArray<UClass*> GetRegisteredObjectClasses();` — Get all registered UClass types
- L80 _public prototype_ `static TArray<UClass*> GetRegisteredObjectClasses(TSubScriptStructOf<FUAFAssetData> BaseAssetType);` — Get registered UClass types that correspond to a specific baseclass of FUUAFAssetData
- L83 _public function_ `template<typename TAssetDataType> static TArray<UClass*> GetRegisteredObjectClasses()`
- L91 _private typedef_ `using FAssetInitializer = TFunction<TInstancedStruct<FUAFAssetData>(const UObject*)>;` — Untyped UObject initializer
- L106 _private prototype_ `static FTopLevelAssetPath RegisterAsset(TSubScriptStructOf<FUAFAssetData> AssetDataType, UClass* ObjectClass, FAssetInitializer&& Initializer);` — Register how to create a FUAFAssetReference from a ObjectClass
- L107 _private prototype_ `static const FInitializerInfo* FindAssetInitializer(const UClass* Class);`
- L108 _private member_ `static TMap<FTopLevelAssetPath, FInitializerInfo> AssetInitializers;`
- L109 _private member_ `static TArray<FTopLevelAssetPath> AllSupportedObjectClassPaths;`
- L114 _private prototype_ `static void GatherDerivedCompatibleObjectClasses(const UClass* SuperClass, TArray<UClass*>& InOutCompatibleClasses);` — Helper function to recursively gather all valid non-registered subclasses of SuperClass and add them into InOutCompatibleClasses Stops each branch at the first subclass that has its own registered initializer in AssetInitializers to avoid adding subclasses that have their own or closer related registered initializer already

#### struct `UE::UAF::FAssetDataFactory::FInitializerInfo`  
`struct FInitializerInfo`  
_L93-102_
- L95 _public function_ `FInitializerInfo(TSubScriptStructOf<FUAFAssetData> Type, FAssetInitializer Initializer) : AssetDataType(Type), Initializer(Initializer)`
- L98 _public prototype_ `FInitializerInfo() = default;`
- L100 _public member_ `TSubScriptStructOf<FUAFAssetData> AssetDataType;`
- L101 _public member_ `FAssetInitializer Initializer;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L68 _function_ `` (scope `UE::UAF::FAssetDataFactory::RegisterAsset`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/UAFSkeletonUserData.h` (Public)


#### class `UUAFSkeletonUserData`  
`class UUAFSkeletonUserData : public UAssetUserData`  
_L18-41_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "UAF Skeleton Data"))`
- inherits: `UAssetUserData`
- desc: Encapsulates the extra skeleton user data necessary for UAF
- L25 _public prototype_ `static UUAFSkeletonUserData* FromSkeleton(TNonNullPtr<USkeleton> Skeleton);` — Returns the UAF skeleton user data associated with the specified skeleton If one isn't set by the user, a new one is allocated on demand and cached
- L28 _public prototype_ `UAbstractSkeletonLabelBinding* GetLabelBinding() const;` — The default abstract skeleton label binding asset to use
- L31 _public prototype_ `UAbstractSkeletonSetBinding* GetSetBinding() const;` — The default abstract skeleton set binding asset to use
- L36 _private member_ `TObjectPtr<UAbstractSkeletonLabelBinding> LabelBinding;` — `UPROPERTY(EditAnywhere, Category = AbstractSkeleton)` — The default abstract skeleton label binding asset to use
- L40 _private member_ `TObjectPtr<UAbstractSkeletonSetBinding> SetBinding;` — `UPROPERTY(EditAnywhere, Category = AbstractSkeleton)` — The default abstract skeleton set binding asset to use

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/AttributeMappingKey.h` (Public)


#### class `UE::UAF::FAttributeMappingKey`  
`class FAttributeMappingKey`  
_L14-92_
- desc: An attribute mapping key encodes a mapping from an attribute type to a value type akin to the key in something like TMap<TPair<AttributeType, ValueType>, TArray<ValueType>> Mapping keys have a default sort order where we first sort by ValueType then by AttributeType
- L18 _public member_ `static const FAttributeMappingKey SMALLEST_VALUE;` — Smallest possible value for a mapping key
- L21 _public member_ `static const FAttributeMappingKey LARGEST_VALUE;` — Largest possible value for a mapping key
- L24 _public prototype_ `constexpr FAttributeMappingKey() = default;` — Creates a default mapping key which will have the smallest value possible (aka zero)
- L27 _public prototype_ `[[nodiscard]] explicit constexpr FAttributeMappingKey(UScriptStruct* AttributeAndValueType);` — Creates a mapping key from the specified type which maps onto itself
- L30 _public prototype_ `[[nodiscard]] constexpr FAttributeMappingKey(UScriptStruct* AttributeType, UScriptStruct* ValueType);` — Creates a mapping key from the specified values
- L34 _public prototype_ `template<class AttributeType> [[nodiscard]] static FAttributeMappingKey MakeFrom();` — Returns a new mapping key where we map from the specified attribute type to nothing
- L37 _public prototype_ `[[nodiscard]] static constexpr FAttributeMappingKey MakeFrom(UScriptStruct* AttributeType);` — Returns a new mapping key where we map from the specified attribute type to nothing
- L41 _public prototype_ `template<class ValueType> [[nodiscard]] static FAttributeMappingKey MakeTo();` — Returns a new mapping key where we map from nothing to the specified value type
- L44 _public prototype_ `[[nodiscard]] static constexpr FAttributeMappingKey MakeTo(UScriptStruct* ValueType);` — Returns a new mapping key where we map from nothing to the specified value type
- L48 _public prototype_ `template<class AttributeAndValueType> [[nodiscard]] static FAttributeMappingKey MakeFromTo();` — Returns a new mapping key where we map onto itself
- L51 _public prototype_ `[[nodiscard]] static constexpr FAttributeMappingKey MakeFromTo(UScriptStruct* AttributeAndValueType);` — Returns a new mapping key where we map onto itself
- L55 _public prototype_ `template<class FromAttributeType, class ToValueType> [[nodiscard]] static FAttributeMappingKey MakeFromTo();` — Returns a new mapping key where we map from the specified attribute type to the specified value type
- L58 _public prototype_ `[[nodiscard]] static constexpr FAttributeMappingKey MakeFromTo(UScriptStruct* FromAttributeType, UScriptStruct* ToValueType);` — Returns a new mapping key where we map from the specified attribute type to the specified value type
- L62 _public prototype_ `template<class FromAttributeType> [[nodiscard]] FAttributeMappingKey From() const;` — Returns a new mapping key where we map from the specified attribute type
- L65 _public prototype_ `[[nodiscard]] constexpr FAttributeMappingKey From(UScriptStruct* FromAttributeType) const;` — Returns a new mapping key where we map from the specified attribute type
- L69 _public prototype_ `template<class ToValueType> [[nodiscard]] FAttributeMappingKey To() const;` — Returns a new mapping key where we map to the specified value type
- L72 _public prototype_ `[[nodiscard]] constexpr FAttributeMappingKey To(UScriptStruct* ToValueType) const;` — Returns a new mapping key where we map to the specified value type
- L75 _public function_ `[[nodiscard]] constexpr UScriptStruct* GetAttributeType() const` — Returns the attribute type that we map from
- L78 _public function_ `[[nodiscard]] constexpr UScriptStruct* GetValueType() const` — Returns the value type that we map to
- L81 _public prototype_ `[[nodiscard]] bool operator<(const FAttributeMappingKey& Other) const;` — LessThan operator for sorting and searching operations
- L84 _public prototype_ `[[nodiscard]] bool operator==(const FAttributeMappingKey& Other) const;` — Equality operator
- L88 _private member_ `UScriptStruct* AttributeType = nullptr;` — The attribute type of our typed set whose values we map to
- L91 _private member_ `UScriptStruct* ValueType = nullptr;` — The type of values we map onto our set
- L97 _function_ `constexpr FAttributeMappingKey::FAttributeMappingKey(UScriptStruct* AttributeAndValueType) : AttributeType(AttributeAndValueType) , ValueType(AttributeAndValueType)`
- L103 _function_ `constexpr FAttributeMappingKey::FAttributeMappingKey(UScriptStruct* InAttributeType, UScriptStruct* InValueType) : AttributeType(InAttributeType) , ValueType(InValueType)`
- L110 _function_ `template<class AttributeType> inline FAttributeMappingKey FAttributeMappingKey::MakeFrom()`
- L115 _function_ `constexpr FAttributeMappingKey FAttributeMappingKey::MakeFrom(UScriptStruct* AttributeType)`
- L121 _function_ `template<class ValueType> inline FAttributeMappingKey FAttributeMappingKey::MakeTo()`
- L126 _function_ `constexpr FAttributeMappingKey FAttributeMappingKey::MakeTo(UScriptStruct* ValueType)`
- L132 _function_ `template<class AttributeAndValueType> inline FAttributeMappingKey FAttributeMappingKey::MakeFromTo()`
- L137 _function_ `constexpr FAttributeMappingKey FAttributeMappingKey::MakeFromTo(UScriptStruct* AttributeAndValueType)`
- L143 _function_ `template<class FromAttributeType, class ToValueType> inline FAttributeMappingKey FAttributeMappingKey::MakeFromTo()`
- L148 _function_ `constexpr FAttributeMappingKey FAttributeMappingKey::MakeFromTo(UScriptStruct* FromAttributeType, UScriptStruct* ToValueType)`
- L154 _function_ `template<class FromAttributeType> inline FAttributeMappingKey FAttributeMappingKey::From() const`
- L159 _function_ `constexpr FAttributeMappingKey FAttributeMappingKey::From(UScriptStruct* FromAttributeType) const`
- L165 _function_ `template<class ToValueType> inline FAttributeMappingKey FAttributeMappingKey::To() const`
- L170 _function_ `constexpr FAttributeMappingKey FAttributeMappingKey::To(UScriptStruct* ToValueType) const`
- L175 _function_ `inline bool FAttributeMappingKey::operator<(const FAttributeMappingKey& Other) const`
- L186 _function_ `inline bool FAttributeMappingKey::operator==(const FAttributeMappingKey& Other) const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAF_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/BoundMapCollection.h` (Public)


#### class `UE::UAF::TBoundMapCollectionIterator`  
`template<class ContainerType> class TBoundMapCollectionIterator`  
_L17-55_
- desc: A iterator that iterates over all bound value maps within a bound map collection
- L20 _public member_ `static constexpr bool bIsContainerConst = std::is_const_v<ContainerType>;`
- L22 _public typedef_ `using EntryPtrType = typename std::conditional<bIsContainerConst, const typename ContainerType::FMapEntry*, typename ContainerType::FMapEntry*>::type;`
- L23 _public typedef_ `using MapType = typename std::conditional<bIsContainerConst, const FBoundValueMap*, FBoundValueMap*>::type;`
- L26 _public prototype_ `[[nodiscard]] TBoundMapCollectionIterator() = default;` — Creates an empty iterator
- L29 _public prototype_ `[[nodiscard]] TBoundMapCollectionIterator(ContainerType& Collection);` — Creates an iterator over the map entries within the specified collection
- L32 _public prototype_ `TBoundMapCollectionIterator& operator++();` — Increments and moves the iterator to the next map entry
- L35 _public prototype_ `[[nodiscard]] explicit operator bool() const;` — Returns whether or not the iterator still contains values
- L38 _public prototype_ `[[nodiscard]] const FAttributeMappingKey& GetKey() const;` — Returns the mapping key of the current map entry
- L41 _public prototype_ `[[nodiscard]] UScriptStruct* GetAttributeType() const;` — Returns the attribute type of the current map entry
- L44 _public prototype_ `[[nodiscard]] UScriptStruct* GetValueType() const;` — Returns the value type of the current map entry
- L47 _public prototype_ `[[nodiscard]] MapType GetMap() const;` — Returns the map from the current entry
- L51 _private member_ `EntryPtrType EntryPtr = nullptr;` — Current map entry
- L54 _private member_ `EntryPtrType EntryEndPtr = nullptr;` — One past the last map entry
- L338 _function_ `template<class ContainerType> inline TBoundMapCollectionIterator<ContainerType>::TBoundMapCollectionIterator(ContainerType& Collection) : EntryPtr(Collection.Maps) , EntryEndPtr(Collection.Maps + Collection.MapCount)`
- L345 _function_ `template<class ContainerType> inline TBoundMapCollectionIterator<ContainerType>& TBoundMapCollectionIterator<ContainerType>::operator++()`
- L352 _function_ `template<class ContainerType> inline TBoundMapCollectionIterator<ContainerType>::operator bool() const`
- L358 _function_ `template<class ContainerType> inline const FAttributeMappingKey& TBoundMapCollectionIterator<ContainerType>::GetKey() const`
- L364 _function_ `template<class ContainerType> inline UScriptStruct* TBoundMapCollectionIterator<ContainerType>::GetAttributeType() const`
- L370 _function_ `template<class ContainerType> inline UScriptStruct* TBoundMapCollectionIterator<ContainerType>::GetValueType() const`
- L376 _function_ `template<class ContainerType> inline typename TBoundMapCollectionIterator<ContainerType>::MapType TBoundMapCollectionIterator<ContainerType>::GetMap() const`

#### class `UE::UAF::FBoundMapCollection`  
`class FBoundMapCollection`  
_L63-178_
- desc: Bound Value Map Collection Holds a sorted collection of bound value maps. Entries are sorted by value type, then by attribute type.
- L76 _public prototype_ `FBoundMapCollection(const FAttributeNamedSetPtr& NamedSet, FReallocFun InReallocFun);`
- L77 _public prototype_ `FBoundMapCollection(const FBoundMapCollection& Other);`
- L78 _public prototype_ `FBoundMapCollection(FBoundMapCollection&& Other);`
- L79 _public prototype_ `~FBoundMapCollection();`
- L81 _public prototype_ `FBoundMapCollection& operator=(const FBoundMapCollection& Other);`
- L82 _public prototype_ `FBoundMapCollection& operator=(FBoundMapCollection&& Other);`
- L85 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not we are empty
- L88 _public prototype_ `[[nodiscard]] const FAttributeNamedSetPtr& GetNamedSet() const;` — Returns the named set this collection maps to
- L91 _public prototype_ `void Reset(const FAttributeNamedSetPtr& NamedSet);` — Resets the collection with the specified named set
- L94 _public prototype_ `void Empty();` — Clears the collection of any content
- L97 _public prototype_ `[[nodiscard]] FReallocFun GetAllocator() const;` — Returns the allocator function this collection was initialized with
- L100 _public prototype_ `[[nodiscard]] int32 Num() const;` — Returns the number of maps contained within
- L104 _public prototype_ `template <class ValueType, typename... TArgs> [[nodiscard]] TBoundValueMap<ValueType>* Add(const FAttributeMappingKey& MappingKey, TArgs... Args);` — Constructs and adds a new bound value map with the specified mapping (attribute -> value type). Returns nullptr if we fail to add an entry (e.g. duplicate)
- L108 _public prototype_ `[[nodiscard]] FBoundValueMap* Add(const FAttributeMappingKey& MappingKey);` — Constructs and adds a new bound value map with the specified mapping (attribute -> value type). Returns nullptr if we fail to add an entry (e.g. duplicate)
- L112 _public prototype_ `bool Add(FBoundValueMap* Map);` — Adds a map to this collection. Returns false if we fail to add an entry (e.g. duplicate, mismatched allocator)
- L116 _public prototype_ `bool Append(FBoundValueMap* Map);` — Appends a new map to this collection (the input must belong at the end of the sorted map list). Returns false if we fail to add an entry (e.g. duplicate, mismatched allocator, not sorted)
- L120 _public prototype_ `bool Remove(FBoundValueMap* Map);` — Removes the specified map from this collection Returns whether or not the entry was successfully removed
- L124 _public prototype_ `bool Remove(const FAttributeMappingKey& MappingKey);` — Removes the specified mapping from this collection Returns whether or not the entry was successfully removed
- L128 _public prototype_ `template <class ValueType> [[nodiscard]] TBoundValueMap<ValueType>* Find(const FAttributeMappingKey& MappingKey);` — Finds a map of ValueType to a set of AttributeType in this collection Returns nullptr if this collection does not contain such a mapping
- L132 _public prototype_ `template <class ValueType> [[nodiscard]] const TBoundValueMap<ValueType>* Find(const FAttributeMappingKey& MappingKey) const;` — Finds a map of ValueType to a set of AttributeType in this collection Returns nullptr if this collection does not contain such a mapping
- L136 _public prototype_ `[[nodiscard]] FBoundValueMap* Find(const FAttributeMappingKey& MappingKey);` — Finds a map of ValueType to a set of AttributeType in this collection Returns nullptr if this collection does not contain such a mapping
- L140 _public prototype_ `[[nodiscard]] const FBoundValueMap* Find(const FAttributeMappingKey& MappingKey) const;` — Finds a map of ValueType to a set of AttributeType in this collection Returns nullptr if this collection does not contain such a mapping
- L144 _public prototype_ `template <class ValueType, typename... TArgs> [[nodiscard]] TBoundValueMap<ValueType>* FindOrAdd(const FAttributeMappingKey& MappingKey, TArgs... Args);` — Finds or adds a map of ValueType to a set of AttributeType in this collection Returns nullptr if we fail to add an entry (e.g. duplicate)
- L148 _public prototype_ `[[nodiscard]] FBoundValueMap* FindOrAdd(const FAttributeMappingKey& MappingKey);` — Finds or adds a map of ValueType to a set of AttributeType in this collection Returns nullptr if we fail to add an entry (e.g. duplicate)
- L151 _public typedef_ `using FIterator = TBoundMapCollectionIterator<FBoundMapCollection>;` — Iterators
- L152 _public typedef_ `using FConstIterator = TBoundMapCollectionIterator<const FBoundMapCollection>;`
- L155 _public prototype_ `[[nodiscard]] FIterator CreateIterator();` — Returns an iterator over all maps contained within, sorted by their key (value type first, then attribute type)
- L156 _public prototype_ `[[nodiscard]] FConstIterator CreateConstIterator() const;`
- L159 _private prototype_ `FBoundValueMap** AddImpl(const FBoundValueMap::FConstructArgs& Args, bool bConstructMap);`
- L162 _private member_ `FAttributeNamedSetPtr NamedSet;` — The named set we are based on, every map uses a typed set within it
- L165 _private member_ `FMapEntry* Maps = nullptr;` — An array of maps (sorted by mapping key)
- L168 _private member_ `int32 MapCount = 0;` — How many maps are contained within this collection
- L171 _private member_ `int32 MapCapacity = 0;` — How many maps we can contain within this collection
- L174 _private member_ `FReallocFun ReallocFun = nullptr;` — The indirect allocator function pointer
- L225 _function_ `template <class ValueType, typename... TArgs> inline TBoundValueMap<ValueType>* FBoundMapCollection::Add(const FAttributeMappingKey& MappingKey, TArgs... Args)`
- L267 _function_ `template <class ValueType> inline TBoundValueMap<ValueType>* FBoundMapCollection::Find(const FAttributeMappingKey& MappingKey)`
- L279 _function_ `template <class ValueType> inline const TBoundValueMap<ValueType>* FBoundMapCollection::Find(const FAttributeMappingKey& MappingKey) const`
- L291 _function_ `template <class ValueType, typename... TArgs> inline TBoundValueMap<ValueType>* FBoundMapCollection::FindOrAdd(const FAttributeMappingKey& MappingKey, TArgs... Args)`
- L307 _function_ `inline typename FBoundMapCollection::FIterator FBoundMapCollection::CreateIterator()`
- L312 _function_ `inline typename FBoundMapCollection::FConstIterator FBoundMapCollection::CreateConstIterator() const`

#### struct `UE::UAF::FBoundMapCollection::FMapEntry`  
`struct FMapEntry`  
_L66-73_
- L69 _public member_ `FAttributeMappingKey Key;` — The mapping key that identifies this entry
- L72 _public member_ `FBoundValueMap* Map = nullptr;` — The map containing our values

#### class `UE::UAF::FBoundMapCollectionHeap`  
`class FBoundMapCollectionHeap : public FBoundMapCollection`  
_L181-191_
- inherits: `FBoundMapCollection`
- desc: A heap allocated bound map collection
- L185 _public prototype_ `FBoundMapCollectionHeap();` — Constructs an empty collection
- L188 _public prototype_ `explicit FBoundMapCollectionHeap(const FAttributeNamedSetPtr& NamedSet);` — Constructs an empty collection based on the specified named set
- L317 _function_ `inline FBoundMapCollectionHeap::FBoundMapCollectionHeap() : FBoundMapCollection(nullptr, &FAllocatorTypeTrait<FDefaultAllocator>::Realloc)`
- L322 _function_ `inline FBoundMapCollectionHeap::FBoundMapCollectionHeap(const FAttributeNamedSetPtr& InNamedSet) : FBoundMapCollection(InNamedSet, &FAllocatorTypeTrait<FDefaultAllocator>::Realloc)`

#### class `UE::UAF::FBoundMapCollectionStack`  
`class FBoundMapCollectionStack : public FBoundMapCollection`  
_L194-204_
- inherits: `FBoundMapCollection`
- desc: A Mem-Stack allocated bound map collection
- L198 _public prototype_ `FBoundMapCollectionStack();` — Constructs an empty collection
- L201 _public prototype_ `explicit FBoundMapCollectionStack(const FAttributeNamedSetPtr& NamedSet);` — Constructs an empty collection based on the specified named set
- L327 _function_ `inline FBoundMapCollectionStack::FBoundMapCollectionStack() : FBoundMapCollection(nullptr, &FAllocatorTypeTrait<TMemStackAllocator<>>::Realloc)`
- L332 _function_ `inline FBoundMapCollectionStack::FBoundMapCollectionStack(const FAttributeNamedSetPtr& InNamedSet) : FBoundMapCollection(InNamedSet, &FAllocatorTypeTrait<TMemStackAllocator<>>::Realloc)`

#### struct `UE::UAF::FBoundMapCollectionJoinOp`  
`struct FBoundMapCollectionJoinOp`  
_L207-216_
- desc: An operator structure to join bound map collections using InnerJoin/OuterJoin/etc
- L209 _public function_ `const FAttributeMappingKey& GetLargestKey() const`
- L211 _public function_ `const FAttributeMappingKey& GetKey(const FBoundMapCollection::FIterator& It) const`
- L212 _public function_ `const FAttributeMappingKey& GetKey(const FBoundMapCollection::FConstIterator& It) const`
- L214 _public function_ `FBoundValueMap* GetValue(const FBoundMapCollection::FIterator& It) const`
- L215 _public function_ `const FBoundValueMap* GetValue(const FBoundMapCollection::FConstIterator& It) const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L222 _namespace_ `namespace UE`
- L222 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/BoundValueMap.h` (Public)


#### class `UE::UAF::FBoundValueMap`  
`class FBoundValueMap`  
_L17-127_
- desc: Untyped base class for TBoundValueMap
- L36 _public typedef_ `using FConstructArgs = FDefaultConstructArgs;`
- L39 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not this map has any values
- L42 _public prototype_ `[[nodiscard]] int32 Num() const;` — Returns the number of mapped values
- L45 _public prototype_ `[[nodiscard]] const FAttributeTypedSetPtr& GetTypedSet() const;` — Returns the attribute typed set we map to
- L48 _public prototype_ `[[nodiscard]] UScriptStruct* GetAttributeType() const;` — Returns the attribute type we map to
- L51 _public prototype_ `[[nodiscard]] UScriptStruct* GetValueType() const;` — Returns the mapped value type
- L54 _public prototype_ `[[nodiscard]] FAttributeMappingKey GetMappingKey() const;` — Returns the mapping key represented by this map
- L57 _public prototype_ `[[nodiscard]] int32 GetAllocatedSize() const;` — Returns the total allocated size for this map
- L60 _public prototype_ `[[nodiscard]] FReallocFun GetAllocator() const;` — Returns the allocator function this map was initialized with
- L63 _public prototype_ `[[nodiscard]] virtual FBoundValueMap* Duplicate(FReallocFun InReallocFun) const = 0;` — Returns a copy of this map using the specified allocator
- L66 _public prototype_ `virtual void FillWithIdentity(bool bIsAdditive) = 0;` — Initializes every value to its identity, optionally additive
- L70 _public prototype_ `virtual void CopyTo(FBoundValueMap& Other) const = 0;` — Copies the content of this map into another Both must have matching typed sets and value types
- L74 _public prototype_ `virtual void SetValueWithSetter(FAttributeSetIndex Index, const TFunctionRef<void(UScriptStruct* ValueType, uint8* OutValuePtr)>& ValueSetter) = 0;` — Sets a value at the specified index using a value setter function The value setter (and/or caller) is responsible for validating the value type
- L78 _public prototype_ `virtual void GetValueWithGetter(FAttributeSetIndex Index, const TFunctionRef<void(UScriptStruct* ValueType, const uint8* ValuePtr)>& ValueGetter) const = 0;` — Gets a value at the specified index using a value getter function The value getter (and/or caller) is responsible for validating the value type
- L83 _public prototype_ `template <class ValueType> void SetValue(FAttributeSetIndex Index, const ValueType& Value);` — Sets a value at the specified index The called is responsible for validating the value type matches the one contained within this map
- L88 _public prototype_ `template <class ValueType> [[nodiscard]] ValueType GetValue(FAttributeSetIndex Index) const;` — Gets a value from the specified index The called is responsible for validating the value type matches the one contained within this map
- L92 _protected prototype_ `FBoundValueMap();` — Default construction for an empty map
- L95 _protected prototype_ `FBoundValueMap(const FConstructArgs& Args, int32 AllocatedSize);` — Constructs a map but does not allocate its memory, derived types are responsible for it
- L98 _protected prototype_ `virtual ~FBoundValueMap();` — Destroys the map and frees its memory
- L101 _protected prototype_ `virtual void SetValueImpl(FAttributeSetIndex Index, const void* ValuePtr) = 0;` — Sets a value at the specified index
- L104 _protected prototype_ `virtual void GetValueImpl(FAttributeSetIndex Index, void* OutValuePtr) const = 0;` — Gets a value from the specified index
- L107 _protected member_ `FAttributeTypedSetPtr TypedSet;` — The set whose attributes we map values to
- L110 _protected member_ `UScriptStruct* ValueTypeStruct = nullptr;` — The type of values this map contains
- L113 _protected member_ `int32 AllocatedSize = 0;` — The total allocated size of this map
- L116 _protected member_ `int32 NumValues = 0;` — The number of values allocated in our buffer
- L119 _protected member_ `uint8* ValuesPtr = nullptr;` — The base untyped pointer for our values
- L122 _protected member_ `FReallocFun ReallocFun = nullptr;` — The indirect allocator function pointer
- L240 _function_ `template<class ValueType> inline void FBoundValueMap::SetValue(FAttributeSetIndex Index, const ValueType& Value)`
- L247 _function_ `template<class ValueType> inline ValueType FBoundValueMap::GetValue(FAttributeSetIndex Index) const`

#### struct `UE::UAF::FBoundValueMap::FDefaultConstructArgs`  
`struct FDefaultConstructArgs`  
_L22-34_
- L24 _public member_ `const FAttributeTypedSetPtr& TypedSet;`
- L25 _public member_ `UScriptStruct* ValueType = nullptr;`
- L26 _public member_ `FReallocFun ReallocFun = nullptr;`
- L28 _public function_ `FDefaultConstructArgs(const FAttributeTypedSetPtr& InTypedSet, UScriptStruct* InValueType, FReallocFun InReallocFun) : TypedSet(InTypedSet) , ValueType(InValueType) , ReallocFun(InReallocFun)`

#### class `UE::UAF::TBoundValueMap`  
`template<class InValueType> class TBoundValueMap : public FBoundValueMap`  
_L134-194_
- inherits: `FBoundValueMap`
- desc: Encapsulates a mapping of a value type to a specific attribute set (of any attribute type) Our keys are held by the attribute set we point to (keys are shared) while we hold the mapped values internally. Bound value maps and their values are allocated together in a contiguous buffer. Value types must be a UStruct
- L138 _public typedef_ `using ValueType = InValueType;` — The type of values held in this map
- L141 _public prototype_ `[[nodiscard]] virtual FBoundValueMap* Duplicate(FReallocFun InReallocFun) const override;` — Returns a copy of this map using the specified allocator
- L144 _public prototype_ `void FillWithValue(InValueType Value);` — Initializes every value to the specified one
- L147 _public prototype_ `virtual void FillWithIdentity(bool bIsAdditive) override;` — Initializes every value to its identity, optionally additive
- L151 _public prototype_ `virtual void CopyTo(FBoundValueMap& Other) const override;` — Copies the content of this map into another Both must have matching typed sets and value types
- L154 _public prototype_ `[[nodiscard]] InValueType& operator[](FAttributeSetIndex Index);` — Value accessors by index
- L157 _public prototype_ `[[nodiscard]] const InValueType& operator[](FAttributeSetIndex Index) const;` — Value accessors by index
- L160 _public prototype_ `[[nodiscard]] InValueType* GetData();` — Returns a pointer to the contiguous values held within
- L163 _public prototype_ `[[nodiscard]] const InValueType* GetData() const;` — Returns a pointer to the contiguous values held within
- L166 _public prototype_ `[[nodiscard]] static int32 CalculateAllocationSize(int32 NumAttributes);` — Returns the total size required for an instance of a map of this type
- L169 _public function_ `void SetValue(FAttributeSetIndex Index, const InValueType& Value)` — Typed equivalent for FBoundValueMap::SetValue
- L175 _public function_ `[[nodiscard]] InValueType GetValue(FAttributeSetIndex Index) const` — Typed equivalent for FBoundValueMap::GetValue
- L182 _protected prototype_ `TBoundValueMap(const FConstructArgs& Args, int32 AllocatedSize);` — Constructs a map
- L187 _protected prototype_ `virtual void SetValueWithSetter(FAttributeSetIndex Index, const TFunctionRef<void(UScriptStruct* ValueType, uint8* OutValuePtr)>& ValueSetter) override;`
- L188 _protected prototype_ `virtual void GetValueWithGetter(FAttributeSetIndex Index, const TFunctionRef<void(UScriptStruct* ValueType, const uint8* ValuePtr)>& ValueGetter) const override;`
- L189 _protected prototype_ `virtual void SetValueImpl(FAttributeSetIndex Index, const void* ValuePtr) override;`
- L190 _protected prototype_ `virtual void GetValueImpl(FAttributeSetIndex Index, void* OutValuePtr) const override;`
- L258 _function_ `template<class InValueType> inline TBoundValueMap<InValueType>::TBoundValueMap(const FConstructArgs& Args, int32 InAllocatedSize) : FBoundValueMap(Args, InAllocatedSize)`
- L275 _function_ `template<class InValueType> inline TBoundValueMap<InValueType>::~TBoundValueMap()`
- L287 _function_ `template<class InValueType> inline FBoundValueMap* TBoundValueMap<InValueType>::Duplicate(FReallocFun InReallocFun) const`
- L300 _function_ `template<class InValueType> inline void TBoundValueMap<InValueType>::FillWithValue(InValueType Value)`
- L318 _function_ `template<class InValueType> inline void TBoundValueMap<InValueType>::FillWithIdentity(bool bIsAdditive)`
- L343 _function_ `template<class InValueType> inline void TBoundValueMap<InValueType>::CopyTo(FBoundValueMap& Other) const`
- L354 _function_ `template<class InValueType> inline InValueType& TBoundValueMap<InValueType>::operator[](FAttributeSetIndex Index)`
- L361 _function_ `template<class InValueType> inline const InValueType& TBoundValueMap<InValueType>::operator[](FAttributeSetIndex Index) const`
- L368 _function_ `template<class InValueType> inline InValueType* TBoundValueMap<InValueType>::GetData()`
- L374 _function_ `template<class InValueType> inline const InValueType* TBoundValueMap<InValueType>::GetData() const`
- L380 _function_ `template<class InValueType> inline void TBoundValueMap<InValueType>::SetValueWithSetter(FAttributeSetIndex Index, const TFunctionRef<void(UScriptStruct* ValueType, uint8* OutValuePtr)>& ValueSetter)`
- L388 _function_ `template<class InValueType> inline void TBoundValueMap<InValueType>::GetValueWithGetter(FAttributeSetIndex Index, const TFunctionRef<void(UScriptStruct* ValueType, const uint8* ValuePtr)>& ValueGetter) const`
- L396 _function_ `template<class InValueType> inline void TBoundValueMap<InValueType>::SetValueImpl(FAttributeSetIndex Index, const void* ValuePtr)`
- L404 _function_ `template<class InValueType> inline void TBoundValueMap<InValueType>::GetValueImpl(FAttributeSetIndex Index, void* OutValuePtr) const`
- L412 _function_ `template<class InValueType> inline int32 TBoundValueMap<InValueType>::CalculateAllocationSize(int32 NumAttributes)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAF_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L199 _prototype_ `template<class ValueType> TBoundValueMap<ValueType>* MakeBoundValueMap(const typename TBoundValueMap<ValueType>::FConstructArgs& Args);` (scope `UE::UAF`) — Allocates and constructs a new bound value map for the specified value type Bound value maps and their values are contiguous in memory
- L202 _prototype_ `void ReleaseBoundValueMap(FBoundValueMap* Map);` (scope `UE::UAF`) — Releases and destroys the specified bound value map
- L206 _function_ `template<class ValueType> UE_FORCEINLINE_HINT TBoundValueMap<ValueType>* Cast(FBoundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped map to a typed map
- L213 _function_ `template<class ValueType> UE_FORCEINLINE_HINT const TBoundValueMap<ValueType>* Cast(const FBoundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped map to a typed map
- L220 _function_ `template<class ValueType> inline TBoundValueMap<ValueType>* CastChecked(FBoundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped map to a typed map with an assert if the types mismatch
- L229 _function_ `template<class ValueType> inline const TBoundValueMap<ValueType>* CastChecked(const FBoundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped map to a typed map with an assert if the types mismatch
- L418 _function_ `template<class ValueType> inline TBoundValueMap<ValueType>* MakeBoundValueMap(const typename TBoundValueMap<ValueType>::FConstructArgs& Args)` (scope `UE::UAF`)
- L431 _function_ `inline void ReleaseBoundValueMap(FBoundValueMap* Map)` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/IndirectAllocator.h` (Public)


#### struct `UE::UAF::FAllocatorTypeTrait`  
`template<class AllocatorType> struct FAllocatorTypeTrait`  
_L25-29_
- desc: This type can be specialized for template style allocators for easy interop with the engine allocator types. Note that we cannot support some allocators that require 'NeedsElementType' such as the inline allocator.
- L28 _public prototype_ `static uint8* Realloc(uint8* OldPtr, size_t OldSize, size_t NewSize) = delete;` — Specialize this struct for your allocator by implementing this function
- L34 _public function_ `static uint8* Realloc(uint8* OldPtr, size_t OldSize, size_t NewSize)`

#### struct `UE::UAF::FAllocatorTypeTrait`  
`template<int IndexSize> struct FAllocatorTypeTrait<TSizedDefaultAllocator<IndexSize>>`  
_L32-44_
- L28 _public prototype_ `static uint8* Realloc(uint8* OldPtr, size_t OldSize, size_t NewSize) = delete;` — Specialize this struct for your allocator by implementing this function
- L34 _public function_ `static uint8* Realloc(uint8* OldPtr, size_t OldSize, size_t NewSize)`

#### struct `UE::UAF::FAllocatorTypeTrait`  
`template<uint32 Alignment> struct FAllocatorTypeTrait<TMemStackAllocator<Alignment>>`  
_L47-69_
- L28 _public prototype_ `static uint8* Realloc(uint8* OldPtr, size_t OldSize, size_t NewSize) = delete;` — Specialize this struct for your allocator by implementing this function
- L34 _public function_ `static uint8* Realloc(uint8* OldPtr, size_t OldSize, size_t NewSize)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L18 _typedef_ `typedef uint8* (*FReallocFun)(uint8* OldPtr, size_t OldSize, size_t NewSize);` (scope `UE::UAF`) — Use allocator pointer instead of template argument The allocator should behave as follows: - When Ptr is nullptr (and OldSize is 0), we are allocating memory - When Ptr is valid but NewSize is 0, we are freeing memory - When Ptr is valid and NewSize is not 0, we are re-allocating memory - It assumes that the elements that live in said memory can be trivially copyable - Allocations use default alignment

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/IteratorUtils.h` (Public)


#### struct `UE::UAF::Private::CHasFuzzyMatching`  
`struct CHasFuzzyMatching`  
_L82-88_
- desc: Concept used to detect whether or not a Join Operator uses fuzzy matching
- L85 _public prototype_ `template <typename T> auto Requires(T& Val) -> decltype( Val.IsMatch({}, {}) );`

#### struct `UE::UAF::Private::CHasCustomLessThan`  
`struct CHasCustomLessThan`  
_L91-97_
- desc: Concept used to detect whether or not a Join Operator specifies a custom LessThan operator
- L94 _public prototype_ `template <typename T> auto Requires(T& Val) -> decltype( Val.IsLessThan({}, {}) );`

#### struct `UE::UAF::Private::CHasPredicateWithKey`  
`struct CHasPredicateWithKey`  
_L100-106_
- desc: Concept used to detect whether or not a Join Operator specifies a HasPredicateWithKey function
- L103 _public prototype_ `template <typename T> auto Requires(T& Val) -> decltype( Val.HasPredicateWithKey() );`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L57 _prototype_ `template<class JoinOpType, class PredicateType, class... IteratorTypes> void InnerJoinBy(JoinOpType&& JoinOp, PredicateType&& Predicate, IteratorTypes&&... Iterators);` (scope `UE::UAF`) — An inner join will call the predicate for the union of all iterators When an entry is missing from an iterator, it is skipped This assumes that each iterator is sorted The JoinOpType is used to control which key is used and what value is produced for the predicate e.g. InnerJoinBy(.., A, B) Where: - A: [(123, 'foo'), (456, 'bar')] - B: [(456, 'bar'), (888, 'wow')] Predicate is invoked with: - [(456, 'bar'), (456, 'bar')]		(Both entries matching) See [Join Operators] above for details on the Join Operator argument.
- L74 _prototype_ `template<class JoinOpType, class PredicateType, class... IteratorTypes> void OuterJoinBy(JoinOpType&& JoinOp, PredicateType&& Predicate, IteratorTypes&&... Iterators);` (scope `UE::UAF`) — An outer join will call the predicate for the union of all iterators When an entry is missing from an iterator, it is replaced by nullptr This assumes that each iterator is sorted The JoinOpType is used to control which key is used and what value is produced for the predicate e.g. OuterJoinBy(.., A, B) Where: - A: [(123, 'foo'), (456, 'bar')] - B: [(456, 'bar'), (888, 'wow')] Predicate is invoked with: - [(123, 'foo'), null]				(No matching entry in B) - [(456, 'bar'), (456, 'bar')]		(Both entries matching) - [null, (888, 'wow')]				(No matching entry in A) See [Join Operators] above for details on the Join Operator argument.
- L79 _namespace_ `namespace Private` (scope `UE::UAF`)
- L110 _function_ `template<class JoinOpType> constexpr bool HasPredicateWithKey()` (scope `UE::UAF::Private`) — Returns whether or not the predicate requires the Key as its first argument
- L124 _function_ `template<class... IteratorTypes> inline bool AnyIteratorEmpty(const IteratorTypes&... Iterators)` (scope `UE::UAF::Private`) — Returns whether or not one of the specified iterators has reached the end and is empty
- L131 _function_ `template<class... IteratorTypes> inline bool AllIteratorsEmpty(const IteratorTypes&... Iterators)` (scope `UE::UAF::Private`) — Returns whether or not all iterators have reached the end and are empty
- L138 _function_ `template<class JoinOpType, typename KeyType, class... IteratorTypes> inline bool AllIteratorEqual(JoinOpType& JoinOp, KeyType Key, const IteratorTypes&... Iterators)` (scope `UE::UAF::Private`) — Returns whether or not all iterators have a key with the specified value
- L155 _function_ `template<bool bTestIfEmpty, class JoinOpType, class HeadIteratorType> inline auto IteratorMin(JoinOpType& JoinOp, const HeadIteratorType& HeadIterator)` (scope `UE::UAF::Private`) — Returns the smallest iterator key from the specified iterator list When bTestIfEmpty is enabled, empty iterators return the largest value otherwise we assume that at all iterators are valid and can provide a key Handles the last iterator in the template list
- L175 _function_ `template<bool bTestIfEmpty, class JoinOpType, class HeadIteratorType, class... TailIteratorTypes> inline auto IteratorMin(JoinOpType& JoinOp, const HeadIteratorType& HeadIterator, const TailIteratorTypes&... TailIterators)` (scope `UE::UAF::Private`) — Returns the smallest iterator key from the specified iterator list When bTestIfEmpty is enabled, empty iterators return the largest value otherwise we assume that at all iterators are valid and can provide a key Handles an intermediate iterator in the template list
- L204 _function_ `template<bool bTestIfEmpty, class JoinOpType, typename KeyType, class HeadIteratorType> inline uint32 ConditionalIncrement(JoinOpType& JoinOp, KeyType Key, HeadIteratorType& HeadIterator)` (scope `UE::UAF::Private`) — Conditionally increment iterators that match the specified key Returns how many iterators are empty Handles the last iterator in the template list
- L231 _function_ `template<bool bTestIfEmpty, class JoinOpType, typename KeyType, class HeadIteratorType, class... TailIteratorTypes> inline uint32 ConditionalIncrement(JoinOpType& JoinOp, KeyType Key, HeadIteratorType& HeadIterator, TailIteratorTypes&... TailIterators)` (scope `UE::UAF::Private`) — Conditionally increment iterators that match the specified key Returns how many iterators are empty
- L264 _function_ `template<class JoinOpType, typename KeyType, class IteratorType> inline auto ConditionalGetValue(JoinOpType& JoinOp, KeyType Key, IteratorType& Iterator)` (scope `UE::UAF::Private`) — Conditionally retrieves an iterator value when its key matches the specified value The iterator value is returned when the key matches and the iterator isn't empty otherwise we return nullptr
- L274 _function_ `template<class JoinOpType, class PredicateType, class... IteratorTypes> inline void InnerJoinBy(JoinOpType&& JoinOp, PredicateType&& Predicate, IteratorTypes&&... Iterators)` (scope `UE::UAF`)
- L332 _function_ `template<class JoinOpType, class PredicateType, class... IteratorTypes> inline void OuterJoinBy(JoinOpType&& JoinOp, PredicateType&& Predicate, IteratorTypes&&... Iterators)` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/PoseValueBundle.h` (Public)


#### class `UE::UAF::FPoseValueBundle`  
`class FPoseValueBundle : public FValueBundle`  
_L20-147_
- inherits: `FValueBundle`
- desc: FPoseValueBundle A non-owning typed overlay on FValueBundle that adds convenient accessors for common animation pose data (bone transforms, float curves, etc.). This class is not meant to be constructed directly. It adds no data members and FValueBundle has no v-table, so it can be safely reinterpret-cast from any FValueBundle regardless of allocator (stack or heap). Use the static From(), AsMutable(), or AsConst() helpers to obtain a FPoseValueBundle reference from an existing FValueBundle.
- L24 _public prototype_ `FPoseValueBundle(const FAttributeNamedSetPtr& NamedSet, FReallocFun ReallocFun);` — A helper which forwards the arguments to FValueBundle
- L69 _public prototype_ `[[nodiscard]] TBoundValueMap<FBoneTransformAnimationAttribute>* FindBoneTransforms();` — Returns the bone transform map, or nullptr if this bundle doesn't contain bone transforms. Example: Read/write a single bone by index @code TBoundValueMap<FBoneTransformAnimationAttribute>* BoneTransforms = Pose->FindBoneTransforms(); // Read FTransform CurrentTransform = (*BoneTransforms)[Mapping.BoneIndex].Value; // Write (*BoneTransforms)[Mapping.BoneIndex].Value = NewTransform; @endcode Example: Look up a bone by name @code TBoundValueMap<FBoneTransformAnimationAttribute>* BoneTransforms = Pose->FindBoneTransforms(); FAttributeTypedSetPtr BoneTypedSet = BoneTransforms->GetTypedSet(); FAttributeSetIndex HeadIndex = BoneTypedSet->FindIndex(FName("head")); if (HeadIndex.IsValid()) { FTransform HeadTransform = (*BoneTransforms)[HeadIndex].Value; } @endcode Example: Iterate through all bones: @code TBoundValueMap<FBoneTransformAnimationAttribute>* BoneTransforms = Pose->FindBoneTransforms(); const int32 NumBones = BoneTransforms->Num(); FBoneTransformAnimationAttribute* BoneData = BoneTransforms->GetData(); for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex) { FTransform& BoneTransform = BoneData[BoneIndex].Value; // Read or modify BoneTransform } @endcode
- L70 _public prototype_ `[[nodiscard]] const TBoundValueMap<FBoneTransformAnimationAttribute>* FindBoneTransforms() const;`
- L99 _public prototype_ `[[nodiscard]] TBoundValueMap<FFloatAnimationAttribute>* FindFloatCurves();` — Returns the float curve map (morph targets, control curves, material params), or nullptr if not present. To look up curves by name, use GetTypedSet() on the returned map for the name-to-index mapping. Example: Read/write a curve by name @code TBoundValueMap<FFloatAnimationAttribute>* FloatCurves = Pose->FindFloatCurves(); FAttributeTypedSetPtr FloatTypedSet = FloatCurves->GetTypedSet(); FAttributeSetIndex Index = FloatTypedSet->FindIndex(FName("smile_left")); if (Index.IsValid()) { float Value = (*FloatCurves)[Index].Value;        // Read (*FloatCurves)[Index].Value = 0.75f;              // Write } @endcode Example: Iterate all curves and scale them: @code TBoundValueMap<FFloatAnimationAttribute>* FloatCurves = Pose->FindFloatCurves(); const int32 NumCurves = FloatCurves->Num(); FFloatAnimationAttribute* CurveData = FloatCurves->GetData(); for (int32 CurveIndex = 0; CurveIndex < NumCurves; ++CurveIndex) { CurveData[CurveIndex].Value *= 0.5f; } @endcode
- L100 _public prototype_ `[[nodiscard]] const TBoundValueMap<FFloatAnimationAttribute>* FindFloatCurves() const;`
- L107 _public prototype_ `[[nodiscard]] bool HasBoneTransforms() const;` — Returns whether this bundle contains bone transforms. @note Performs a map lookup internally (O(log N) where N is the number of bound value maps, typically very small). Cache the result rather than calling per-iteration in tight loops.
- L114 _public prototype_ `[[nodiscard]] bool HasFloatCurves() const;` — Returns whether this bundle contains float curves. @note Performs a map lookup internally (O(log N) where N is the number of bound value maps, typically very small). Cache the result rather than calling per-iteration in tight loops.
- L124 _public prototype_ `[[nodiscard]] static FPoseValueBundle& From(FValueBundle& Bundle);` — Reinterpret a FValueBundle reference as a FPoseValueBundle. Safe because FPoseValueBundle adds no data members and FValueBundle has no vtable.
- L127 _public prototype_ `[[nodiscard]] static const FPoseValueBundle& From(const FValueBundle& Bundle);` — @copydoc From(FValueBundle&)
- L140 _public prototype_ `template<typename CoWRefType> [[nodiscard]] static FPoseValueBundle* AsMutable(CoWRefType& Ref);` — Cast a CoW reference to a mutable FPoseValueBundle, returning nullptr if the bundle is empty. Checks mutability internally so the caller doesn't have to. Typical usage: @code FValueBundleCoWRef InputRef = Evaluator.GetEvaluationStack().Pop(); FPoseValueBundle* Pose = FPoseValueBundle::AsMutable(InputRef); @endcode
- L146 _public prototype_ `template<typename CoWRefType> [[nodiscard]] static const FPoseValueBundle* AsConst(const CoWRefType& Ref);` — Cast a CoW reference to a const FPoseValueBundle, returning nullptr if the bundle is empty.
- L182 _function_ `inline FPoseValueBundle::FPoseValueBundle(const FAttributeNamedSetPtr& InNamedSet, FReallocFun InReallocFun) : FValueBundle(InNamedSet, InReallocFun)`
- L187 _function_ `inline TBoundValueMap<FBoneTransformAnimationAttribute>* FPoseValueBundle::FindBoneTransforms()`
- L193 _function_ `inline const TBoundValueMap<FBoneTransformAnimationAttribute>* FPoseValueBundle::FindBoneTransforms() const`
- L199 _function_ `inline TBoundValueMap<FFloatAnimationAttribute>* FPoseValueBundle::FindFloatCurves()`
- L205 _function_ `inline const TBoundValueMap<FFloatAnimationAttribute>* FPoseValueBundle::FindFloatCurves() const`
- L211 _function_ `inline bool FPoseValueBundle::HasBoneTransforms() const`
- L216 _function_ `inline bool FPoseValueBundle::HasFloatCurves() const`
- L221 _function_ `inline FPoseValueBundle& FPoseValueBundle::From(FValueBundle& Bundle)`
- L226 _function_ `inline const FPoseValueBundle& FPoseValueBundle::From(const FValueBundle& Bundle)`
- L232 _function_ `template<typename CoWRefType> inline FPoseValueBundle* FPoseValueBundle::AsMutable(CoWRefType& Ref)`
- L239 _function_ `template<typename CoWRefType> inline const FPoseValueBundle* FPoseValueBundle::AsConst(const CoWRefType& Ref)`

#### class `UE::UAF::FPoseValueBundleHeap`  
`class FPoseValueBundleHeap : public FPoseValueBundle`  
_L152-162_
- inherits: `FPoseValueBundle`
- desc: A heap allocated pose value bundle
- L156 _public prototype_ `FPoseValueBundleHeap();` — Constructs an empty pose bundle
- L159 _public prototype_ `explicit FPoseValueBundleHeap(const FAttributeNamedSetPtr& NamedSet);` — Constructs an empty pose bundle based on the specified named set
- L244 _function_ `inline FPoseValueBundleHeap::FPoseValueBundleHeap() : FPoseValueBundle(nullptr, &FAllocatorTypeTrait<FDefaultAllocator>::Realloc)`
- L249 _function_ `inline FPoseValueBundleHeap::FPoseValueBundleHeap(const FAttributeNamedSetPtr& NamedSet) : FPoseValueBundle(NamedSet, &FAllocatorTypeTrait<FDefaultAllocator>::Realloc)`

#### class `UE::UAF::FPoseValueBundleStack`  
`class FPoseValueBundleStack : public FPoseValueBundle`  
_L165-175_
- inherits: `FPoseValueBundle`
- desc: A Mem-Stack allocated pose value bundle
- L169 _public prototype_ `FPoseValueBundleStack();` — Constructs an empty pose bundle
- L172 _public prototype_ `explicit FPoseValueBundleStack(const FAttributeNamedSetPtr& NamedSet);` — Constructs an empty pose bundle based on the specified named set
- L254 _function_ `inline FPoseValueBundleStack::FPoseValueBundleStack() : FPoseValueBundle(nullptr, &FAllocatorTypeTrait<TMemStackAllocator<>>::Realloc)`
- L259 _function_ `inline FPoseValueBundleStack::FPoseValueBundleStack(const FAttributeNamedSetPtr& NamedSet) : FPoseValueBundle(NamedSet, &FAllocatorTypeTrait<TMemStackAllocator<>>::Realloc)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L177 _typedef_ `using FPoseValueBundlePtr = TSharedPtr<FPoseValueBundle, ESPMode::ThreadSafe>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/Accumulate.h` (Public)


#### struct `UE::UAF::Transformers::FAccumulate`  
`struct FAccumulate final : public FValueTransformer`  
_L17-37_
- inherits: `FValueTransformer`
- desc: Attribute value transformer to accumulate values Accumulate is the repeating step within an N-step interpolation: Overwrite, Accumulate0, Accumulate1, ... Make sure to also implement variations for Overwrite and Interpolate
- L19 _public member_ `static FName TransformerName;`
- L24 _public typedef_ `using FTransformBoundValueMapFunc = void (*)(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);` — If the output buffer is nullptr, an allocator is provided and the implementation is responsible for allocating the output buffer and returning it Per-value map is optional, when not present, the default weight should be used Unbound values do not support per-value weights
- L25 _public typedef_ `using FTransformUnboundValueMapFunc = void (*)(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L30 _public prototype_ `static void Apply(const FValueTransformerMapPtr& TransformerMap, const FValueBundle& InputA, const FValueBundle& InputB, float WeightB, FValueBundle& Output);` — Accumulate attribute values Output = A + (B * WeightB) This function supports outputting to either input
- L36 _public prototype_ `static void Apply(const FValueTransformerMapPtr& TransformerMap, const FValueBundle& InputA, const FValueBundle& InputB, const FValueBundle& PerValueWeightsB, float DefaultWeightB, FValueBundle& Output);` — Accumulate attribute values If a weight isn't specified, the default weight will be used Output = A + (B * (HasValueWeightB ? ValueWeightB : DefaultWeightB)) This function supports outputting to either input

#### struct `UE::UAF::Transformers::Private::FAccumulate_BoneTransformAttribute`  
`struct FAccumulate_BoneTransformAttribute`  
_L44-51_
- L46 _public typedef_ `using TransformerType = FAccumulate;`
- L47 _public typedef_ `using ValueType = FBoneTransformAnimationAttribute;`
- L49 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L50 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FAccumulate_FloatAttribute`  
`struct FAccumulate_FloatAttribute`  
_L53-60_
- L55 _public typedef_ `using TransformerType = FAccumulate;`
- L56 _public typedef_ `using ValueType = FFloatAnimationAttribute;`
- L58 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L59 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FAccumulate_IntegerAttribute`  
`struct FAccumulate_IntegerAttribute`  
_L62-69_
- L64 _public typedef_ `using TransformerType = FAccumulate;`
- L65 _public typedef_ `using ValueType = FIntegerAnimationAttribute;`
- L67 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L68 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FAccumulate_TransformAttribute`  
`struct FAccumulate_TransformAttribute`  
_L71-78_
- L73 _public typedef_ `using TransformerType = FAccumulate;`
- L74 _public typedef_ `using ValueType = FTransformAnimationAttribute;`
- L76 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L77 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FAccumulate_VectorAttribute`  
`struct FAccumulate_VectorAttribute`  
_L80-87_
- L82 _public typedef_ `using TransformerType = FAccumulate;`
- L83 _public typedef_ `using ValueType = FVectorAnimationAttribute;`
- L85 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L86 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FAccumulate_QuaternionAttribute`  
`struct FAccumulate_QuaternionAttribute`  
_L89-96_
- L91 _public typedef_ `using TransformerType = FAccumulate;`
- L92 _public typedef_ `using ValueType = FQuaternionAnimationAttribute;`
- L94 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L95 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Transformers` (scope `UE::UAF`)
- L42 _namespace_ `namespace Private` (scope `UE::UAF::Transformers`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/AdditiveSpace.h` (Public)


#### struct `UE::UAF::Transformers::FMakeAdditiveSpace`  
`struct FMakeAdditiveSpace final : public FValueTransformer`  
_L15-30_
- inherits: `FValueTransformer`
- desc: Attribute value transformer to create additive values
- L17 _public member_ `static FName TransformerName;`
- L21 _public typedef_ `using FTransformBoundValueMapFunc = void (*)(const FBoundValueMap* Base, const FBoundValueMap* Input, FBoundValueMap*& Output, FReallocFun OutputAllocator);` — If the output buffer is nullptr, an allocator is provided and the implementation is responsible for allocating the output buffer and returning it If the base map is missing, transformers should use a default value
- L22 _public typedef_ `using FTransformUnboundValueMapFunc = void (*)(const FUnboundValueMap* Base, const FUnboundValueMap* Input, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`
- L25 _public prototype_ `static void Apply( const FValueTransformerMapPtr& TransformerMap, const FValueBundle& Base, const FValueBundle& Input, FValueBundle& AdditiveOutput);` — Creates a new additive collection by subtracting the base from the specified Input

#### struct `UE::UAF::Transformers::FApplyAdditiveSpace`  
`struct FApplyAdditiveSpace final : public FValueTransformer`  
_L33-65_
- inherits: `FValueTransformer`
- desc: Attribute value transformer to apply additive values onto a base
- L35 _public member_ `static FName TransformerName;`
- L41 _public typedef_ `using FTransformBoundValueMapFunc = void (*)(const FBoundValueMap* Base, const FBoundValueMap* Additive, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& Output, FReallocFun OutputAllocator);` — If the output buffer is nullptr, an allocator is provided and the implementation is responsible for allocating the output buffer and returning it If the base map is missing, transformers should use a default value Per-value map is optional, when not present, the default weight should be used Unbound values do not support per-value weights
- L42 _public typedef_ `using FTransformUnboundValueMapFunc = void (*)(const FUnboundValueMap* Base, const FUnboundValueMap* Additive, float AdditiveWeight, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`
- L47 _public prototype_ `static void Apply( const FValueTransformerMapPtr& TransformerMap, const FValueBundle& Base, const FValueBundle& Additive, float AdditiveWeight, FValueBundle& Output);` — Applies an additive collection onto a base by adding it Output = Base + Lerp(Identity, Additive, Weight) This function supports outputting to either input
- L58 _public prototype_ `static void Apply( const FValueTransformerMapPtr& TransformerMap, const FValueBundle& Base, const FValueBundle& Additive, const FValueBundle& PerValueWeights, float DefaultWeight, FValueBundle& Output);` — Applies an additive collection onto a base by adding it using per value weights (must be of type FFloatAnimationAttribute) If a weight isn't specified, the default weight will be used Output = Base + Lerp(Identity, Additive, HasValueWeight ? ValueWeight : DefaultWeight) This function supports outputting to either input

#### struct `UE::UAF::Transformers::Private::FMakeAdditiveSpace_BoneTransformAttribute`  
`struct FMakeAdditiveSpace_BoneTransformAttribute`  
_L72-79_
- L74 _public typedef_ `using TransformerType = FMakeAdditiveSpace;`
- L75 _public typedef_ `using ValueType = FBoneTransformAnimationAttribute;`
- L77 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Input, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L78 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Input, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FMakeAdditiveSpace_FloatAttribute`  
`struct FMakeAdditiveSpace_FloatAttribute`  
_L81-88_
- L83 _public typedef_ `using TransformerType = FMakeAdditiveSpace;`
- L84 _public typedef_ `using ValueType = FFloatAnimationAttribute;`
- L86 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Input, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L87 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Input, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FMakeAdditiveSpace_IntegerAttribute`  
`struct FMakeAdditiveSpace_IntegerAttribute`  
_L90-97_
- L92 _public typedef_ `using TransformerType = FMakeAdditiveSpace;`
- L93 _public typedef_ `using ValueType = FIntegerAnimationAttribute;`
- L95 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Input, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L96 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Input, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FMakeAdditiveSpace_TransformAttribute`  
`struct FMakeAdditiveSpace_TransformAttribute`  
_L99-106_
- L101 _public typedef_ `using TransformerType = FMakeAdditiveSpace;`
- L102 _public typedef_ `using ValueType = FTransformAnimationAttribute;`
- L104 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Input, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L105 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Input, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FMakeAdditiveSpace_VectorAttribute`  
`struct FMakeAdditiveSpace_VectorAttribute`  
_L108-115_
- L110 _public typedef_ `using TransformerType = FMakeAdditiveSpace;`
- L111 _public typedef_ `using ValueType = FVectorAnimationAttribute;`
- L113 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Input, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L114 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Input, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FMakeAdditiveSpace_QuaternionAttribute`  
`struct FMakeAdditiveSpace_QuaternionAttribute`  
_L117-124_
- L119 _public typedef_ `using TransformerType = FMakeAdditiveSpace;`
- L120 _public typedef_ `using ValueType = FQuaternionAnimationAttribute;`
- L122 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Input, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L123 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Input, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FApplyAdditiveSpace_BoneTransformAttribute`  
`struct FApplyAdditiveSpace_BoneTransformAttribute`  
_L126-133_
- L128 _public typedef_ `using TransformerType = FApplyAdditiveSpace;`
- L129 _public typedef_ `using ValueType = FBoneTransformAnimationAttribute;`
- L131 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Additive, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L132 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Additive, float AdditiveWeight, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FApplyAdditiveSpace_FloatAttribute`  
`struct FApplyAdditiveSpace_FloatAttribute`  
_L135-142_
- L137 _public typedef_ `using TransformerType = FApplyAdditiveSpace;`
- L138 _public typedef_ `using ValueType = FFloatAnimationAttribute;`
- L140 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Additive, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L141 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Additive, float AdditiveWeight, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FApplyAdditiveSpace_IntegerAttribute`  
`struct FApplyAdditiveSpace_IntegerAttribute`  
_L144-151_
- L146 _public typedef_ `using TransformerType = FApplyAdditiveSpace;`
- L147 _public typedef_ `using ValueType = FIntegerAnimationAttribute;`
- L149 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Additive, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L150 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Additive, float AdditiveWeight, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FApplyAdditiveSpace_TransformAttribute`  
`struct FApplyAdditiveSpace_TransformAttribute`  
_L153-160_
- L155 _public typedef_ `using TransformerType = FApplyAdditiveSpace;`
- L156 _public typedef_ `using ValueType = FTransformAnimationAttribute;`
- L158 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Additive, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L159 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Additive, float AdditiveWeight, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FApplyAdditiveSpace_VectorAttribute`  
`struct FApplyAdditiveSpace_VectorAttribute`  
_L162-169_
- L164 _public typedef_ `using TransformerType = FApplyAdditiveSpace;`
- L165 _public typedef_ `using ValueType = FVectorAnimationAttribute;`
- L167 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Additive, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L168 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Additive, float AdditiveWeight, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FApplyAdditiveSpace_QuaternionAttribute`  
`struct FApplyAdditiveSpace_QuaternionAttribute`  
_L171-178_
- L173 _public typedef_ `using TransformerType = FApplyAdditiveSpace;`
- L174 _public typedef_ `using ValueType = FQuaternionAnimationAttribute;`
- L176 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Additive, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& Output, FReallocFun OutputAllocator);`
- L177 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Additive, float AdditiveWeight, FUnboundValueMap*& Output, FReallocFun OutputAllocator);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Transformers` (scope `UE::UAF`)
- L70 _namespace_ `namespace Private` (scope `UE::UAF::Transformers`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/BoneSpace.h` (Public)


#### struct `UE::UAF::Transformers::FBoneSpace`  
`struct FBoneSpace final`  
_L18-47_
- desc: Bone space conversion utility functions Not a transformer, but transformer-like
- L22 _public prototype_ `static void LocalToComponent(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);` — Converts bone transforms between Local Space and Component Space These functions support outputting to their input in place
- L23 _public prototype_ `static void ComponentToLocal(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);`
- L30 _public prototype_ `static void LocalToMeshRotation(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);` — Converts bone transforms between Local Space and Mesh Rotation Space Mesh Rotation Space assumes that bone transform scales are uniform and will yield incorrect results if non-uniform (aka 3D) scale is used. It transforms the rotations into component space by ignoring translation and scale. The output values will thus be in Mixed Space. These functions support outputting to their input in place
- L31 _public prototype_ `static void MeshRotationToLocal(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);`
- L37 _public prototype_ `static void LocalToRootRotation(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);` — Converts bone transforms between Local Space and Root Rotation Space Root Rotation Space is similar to Mesh Rotation space except that the root bone transform is ignored and assumed to be the identity transform (root corrections are ignored). These functions support outputting to their input in place
- L38 _public prototype_ `static void RootRotationToLocal(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);`
- L45 _public prototype_ `static void LocalToMeshScale(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);` — Converts bone transforms between Local Space and Mesh Scale Space Mesh Scale Space assumes that bone transform scales are uniform and will yield incorrect results if non-uniform (aka 3D) scale is used. It transforms the scales into component space by ignoring rotation and translation. The output values will thus be in a Mixed Space. These functions support outputting to their input in place
- L46 _public prototype_ `static void MeshScaleToLocal(const FPoseValueBundle& InputValues, FPoseValueBundle& OutputValues);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAF_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace Transformers` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/Interpolate.h` (Public)


#### struct `UE::UAF::Transformers::FInterpolate`  
`struct FInterpolate final : public FValueTransformer`  
_L16-38_
- inherits: `FValueTransformer`
- desc: Attribute value transformer to interpolate values Make sure to also implement variations for Overwrite and Accumulate
- L18 _public member_ `static FName TransformerName;`
- L24 _public typedef_ `using FTransformBoundValueMapFunc = void (*)(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);` — If the output buffer is nullptr, an allocator is provided and the implementation is responsible for allocating the output buffer and returning it Note that the input/output buffers can be the same buffer Per-value map is optional, when not present, the default weight should be used Unbound values do not support per-value weights
- L25 _public typedef_ `using FTransformUnboundValueMapFunc = void (*)(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L31 _public prototype_ `static void Apply(const FValueTransformerMapPtr& TransformerMap, const FValueBundle& InputA, const FValueBundle& InputB, float WeightB, FValueBundle& Output);` — Interpolate attribute values Output = lerp(A, B, WeightB) Output = (A * (1.0 - WeightB)) + (B * WeightB) This function supports outputting to either input
- L37 _public prototype_ `static void Apply(const FValueTransformerMapPtr& TransformerMap, const FValueBundle& InputA, const FValueBundle& InputB, const FValueBundle& PerValueWeightsB, float DefaultWeightB, FValueBundle& Output);` — Interpolate attribute values If a weight isn't specified, the default weight will be used Output = lerp(A, B, HasValueWeightB ? ValueWeightB : DefaultWeightB) This function supports outputting to either input

#### struct `UE::UAF::Transformers::Private::FInterpolate_BoneTransformAttribute`  
`struct FInterpolate_BoneTransformAttribute`  
_L45-52_
- L47 _public typedef_ `using TransformerType = FInterpolate;`
- L48 _public typedef_ `using ValueType = FBoneTransformAnimationAttribute;`
- L50 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L51 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FInterpolate_FloatAttribute`  
`struct FInterpolate_FloatAttribute`  
_L54-61_
- L56 _public typedef_ `using TransformerType = FInterpolate;`
- L57 _public typedef_ `using ValueType = FFloatAnimationAttribute;`
- L59 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L60 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FInterpolate_IntegerAttribute`  
`struct FInterpolate_IntegerAttribute`  
_L63-70_
- L65 _public typedef_ `using TransformerType = FInterpolate;`
- L66 _public typedef_ `using ValueType = FIntegerAnimationAttribute;`
- L68 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L69 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FInterpolate_TransformAttribute`  
`struct FInterpolate_TransformAttribute`  
_L72-79_
- L74 _public typedef_ `using TransformerType = FInterpolate;`
- L75 _public typedef_ `using ValueType = FTransformAnimationAttribute;`
- L77 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L78 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FInterpolate_VectorAttribute`  
`struct FInterpolate_VectorAttribute`  
_L81-88_
- L83 _public typedef_ `using TransformerType = FInterpolate;`
- L84 _public typedef_ `using ValueType = FVectorAnimationAttribute;`
- L86 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L87 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FInterpolate_QuaternionAttribute`  
`struct FInterpolate_QuaternionAttribute`  
_L90-97_
- L92 _public typedef_ `using TransformerType = FInterpolate;`
- L93 _public typedef_ `using ValueType = FQuaternionAnimationAttribute;`
- L95 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* MapA, const FBoundValueMap* MapB, const FBoundValueMap* PerValueWeightMapB, float DefaultWeightB, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L96 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* MapA, const FUnboundValueMap* MapB, float WeightB, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Transformers` (scope `UE::UAF`)
- L43 _namespace_ `namespace Private` (scope `UE::UAF::Transformers`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/Layer.h` (Public)


#### struct `UE::UAF::Transformers::FLayer`  
`struct FLayer final : public FValueTransformer`  
_L15-49_
- inherits: `FValueTransformer`
- desc: Attribute value transformer to layer values
- L17 _public member_ `static FName TransformerName;`
- L23 _public typedef_ `using FTransformBoundValueMapFunc = void (*)(const FBoundValueMap* Base, const FBoundValueMap* Layer, const FBoundValueMap* PerValueWeights, float DefaultLayerWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);` — If the output buffer is nullptr, an allocator is provided and the implementation is responsible for allocating the output buffer and returning it Note that the input/output buffers can be the same buffer Per-value map is optional, when not present, the default weight should be used Unbound values do not support per-value weights
- L24 _public typedef_ `using FTransformUnboundValueMapFunc = void (*)(const FUnboundValueMap* Base, const FUnboundValueMap* Layer, float LayerWeight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L31 _public prototype_ `static void Apply( const FValueTransformerMapPtr& TransformerMap, const FValueBundle& Base, const FValueBundle& Layer, float LayerWeight, FValueBundle& Output);` — Layer values onto a base Output = layer(Base, Layer, LayerWeight) Output = ValueInLayer ? lerp(BaseValue, LayerValue, LayerWeight) : BaseValue Layer values do not have to be present in the Base and extra values are dropped This function supports outputting to either input
- L42 _public prototype_ `static void Apply( const FValueTransformerMapPtr& TransformerMap, const FValueBundle& Base, const FValueBundle& Layer, const FValueBundle& PerValueLayerWeights, float DefaultLayerWeight, FValueBundle& Output);` — Layer values onto a base Output = ValueInLayer ? lerp(BaseValue, LayerValue, HasLayerValueWeight ? LayerValueWeight : DefaultLayerWeight) : BaseValue Layer values do not have to be present in the Base and extra values are dropped This function supports outputting to either input

#### struct `UE::UAF::Transformers::Private::FLayer_BoneTransformAttribute`  
`struct FLayer_BoneTransformAttribute`  
_L56-63_
- L58 _public typedef_ `using TransformerType = FLayer;`
- L59 _public typedef_ `using ValueType = FBoneTransformAnimationAttribute;`
- L61 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Layer, const FBoundValueMap* PerValueWeights, float DefaultLayerWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L62 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Layer, float LayerWeight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FLayer_FloatAttribute`  
`struct FLayer_FloatAttribute`  
_L65-72_
- L67 _public typedef_ `using TransformerType = FLayer;`
- L68 _public typedef_ `using ValueType = FFloatAnimationAttribute;`
- L70 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Layer, const FBoundValueMap* PerValueWeights, float DefaultLayerWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L71 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Layer, float LayerWeight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FLayer_IntegerAttribute`  
`struct FLayer_IntegerAttribute`  
_L74-81_
- L76 _public typedef_ `using TransformerType = FLayer;`
- L77 _public typedef_ `using ValueType = FIntegerAnimationAttribute;`
- L79 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Layer, const FBoundValueMap* PerValueWeights, float DefaultLayerWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L80 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Layer, float LayerWeight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FLayer_TransformAttribute`  
`struct FLayer_TransformAttribute`  
_L83-90_
- L85 _public typedef_ `using TransformerType = FLayer;`
- L86 _public typedef_ `using ValueType = FTransformAnimationAttribute;`
- L88 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Layer, const FBoundValueMap* PerValueWeights, float DefaultLayerWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L89 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Layer, float LayerWeight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FLayer_VectorAttribute`  
`struct FLayer_VectorAttribute`  
_L92-99_
- L94 _public typedef_ `using TransformerType = FLayer;`
- L95 _public typedef_ `using ValueType = FVectorAnimationAttribute;`
- L97 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Layer, const FBoundValueMap* PerValueWeights, float DefaultLayerWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L98 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Layer, float LayerWeight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FLayer_QuaternionAttribute`  
`struct FLayer_QuaternionAttribute`  
_L101-108_
- L103 _public typedef_ `using TransformerType = FLayer;`
- L104 _public typedef_ `using ValueType = FQuaternionAnimationAttribute;`
- L106 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* Base, const FBoundValueMap* Layer, const FBoundValueMap* PerValueWeights, float DefaultLayerWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L107 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* Base, const FUnboundValueMap* Layer, float LayerWeight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Transformers` (scope `UE::UAF`)
- L54 _namespace_ `namespace Private` (scope `UE::UAF::Transformers`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/Overwrite.h` (Public)


#### struct `UE::UAF::Transformers::FOverwrite`  
`struct FOverwrite final : public FValueTransformer`  
_L17-38_
- inherits: `FValueTransformer`
- desc: Attribute value transformer to overwrite values Overwrite is the initial step within an N-step interpolation: Overwrite, Accumulate0, Accumulate1, ... Make sure to also implement variations for Accumulate and Interpolate
- L19 _public member_ `static FName TransformerName;`
- L25 _public typedef_ `using FTransformBoundValueMapFunc = void (*)(const FBoundValueMap* InputMap, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);` — If the output buffer is nullptr, an allocator is provided and the implementation is responsible for allocating the output buffer and returning it Note that the input/output buffers can be the same buffer Per-value map is optional, when not present, the default weight should be used Unbound values do not support per-value weights
- L26 _public typedef_ `using FTransformUnboundValueMapFunc = void (*)(const FUnboundValueMap* InputMap, float Weight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L31 _public prototype_ `static void Apply(const FValueTransformerMapPtr& TransformerMap, const FValueBundle& Input, float Weight, FValueBundle& Output);` — Overwrite attribute values Output = (A * Weight) This function supports outputting to its input
- L37 _public prototype_ `static void Apply(const FValueTransformerMapPtr& TransformerMap, const FValueBundle& Input, const FValueBundle& PerValueWeights, float DefaultWeight, FValueBundle& Output);` — Overwrite attribute values using per value weights (must be of type FFloatAnimationAttribute) If a weight isn't specified, the default weight will be used Output = A * (HasValueWeight ? ValueWeight : DefaultWeight) This function supports outputting to its input

#### struct `UE::UAF::Transformers::Private::FOverwrite_BoneTransformAttribute`  
`struct FOverwrite_BoneTransformAttribute`  
_L45-52_
- L47 _public typedef_ `using TransformerType = FOverwrite;`
- L48 _public typedef_ `using ValueType = FBoneTransformAnimationAttribute;`
- L50 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* InputMap, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L51 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* InputMap, float Weight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FOverwrite_FloatAttribute`  
`struct FOverwrite_FloatAttribute`  
_L54-61_
- L56 _public typedef_ `using TransformerType = FOverwrite;`
- L57 _public typedef_ `using ValueType = FFloatAnimationAttribute;`
- L59 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* InputMap, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L60 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* InputMap, float Weight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FOverwrite_IntegerAttribute`  
`struct FOverwrite_IntegerAttribute`  
_L63-70_
- L65 _public typedef_ `using TransformerType = FOverwrite;`
- L66 _public typedef_ `using ValueType = FIntegerAnimationAttribute;`
- L68 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* InputMap, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L69 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* InputMap, float Weight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FOverwrite_TransformAttribute`  
`struct FOverwrite_TransformAttribute`  
_L72-79_
- L74 _public typedef_ `using TransformerType = FOverwrite;`
- L75 _public typedef_ `using ValueType = FTransformAnimationAttribute;`
- L77 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* InputMap, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L78 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* InputMap, float Weight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FOverwrite_VectorAttribute`  
`struct FOverwrite_VectorAttribute`  
_L81-88_
- L83 _public typedef_ `using TransformerType = FOverwrite;`
- L84 _public typedef_ `using ValueType = FVectorAnimationAttribute;`
- L86 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* InputMap, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L87 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* InputMap, float Weight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### struct `UE::UAF::Transformers::Private::FOverwrite_QuaternionAttribute`  
`struct FOverwrite_QuaternionAttribute`  
_L90-97_
- L92 _public typedef_ `using TransformerType = FOverwrite;`
- L93 _public typedef_ `using ValueType = FQuaternionAnimationAttribute;`
- L95 _public prototype_ `static void TransformBoundValueMap(const FBoundValueMap* InputMap, const FBoundValueMap* PerValueWeightMap, float DefaultWeight, FBoundValueMap*& OutputMap, FReallocFun OutputAllocator);`
- L96 _public prototype_ `static void TransformUnboundValueMap(const FUnboundValueMap* InputMap, float Weight, FUnboundValueMap*& OutputMap, FReallocFun OutputAllocator);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAF_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Transformers` (scope `UE::UAF`)
- L43 _namespace_ `namespace Private` (scope `UE::UAF::Transformers`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/Sanitize.h` (Public)


#### struct `UE::UAF::Transformers::FSanitize`  
`struct FSanitize final : public FValueTransformer`  
_L19-29_
- inherits: `FValueTransformer`
- desc: Attribute value transformer to sanitize values This can be used to normalize rotations and other like values as well as check for NaN/Inf values
- L21 _public member_ `static FName TransformerName;`
- L23 _public typedef_ `using FTransformBoundValueMapFunc = void (*)(FBoundValueMap* Map);`
- L24 _public typedef_ `using FTransformUnboundValueMapFunc = void (*)(FUnboundValueMap* Map);`
- L28 _public prototype_ `static void Apply(const FValueTransformerMapPtr& TransformerMap, FValueBundle& Collection);` — Sanitize attribute values This can be used to normalize rotations (and other like values) as well as check for NaN/Inf values

#### struct `UE::UAF::Transformers::Private::FSanitize_BoneTransformAttribute`  
`struct FSanitize_BoneTransformAttribute`  
_L37-44_
- desc: Sanitize bone transforms (normalize rotation, ensure finite)
- L39 _public typedef_ `using TransformerType = FSanitize;`
- L40 _public typedef_ `using ValueType = FBoneTransformAnimationAttribute;`
- L42 _public prototype_ `static void TransformBoundValueMap(FBoundValueMap* Map);`
- L43 _public prototype_ `static void TransformUnboundValueMap(FUnboundValueMap* Map);`

#### struct `UE::UAF::Transformers::Private::FSanitize_FloatAttribute`  
`struct FSanitize_FloatAttribute`  
_L48-55_
- desc: Ensure values are not NaN (but Inf is valid)
- L50 _public typedef_ `using TransformerType = FSanitize;`
- L51 _public typedef_ `using ValueType = FFloatAnimationAttribute;`
- L53 _public prototype_ `static void TransformBoundValueMap(FBoundValueMap* Map);`
- L54 _public prototype_ `static void TransformUnboundValueMap(FUnboundValueMap* Map);`

#### struct `UE::UAF::Transformers::Private::FSanitize_TransformAttribute`  
`struct FSanitize_TransformAttribute`  
_L58-65_
- L60 _public typedef_ `using TransformerType = FSanitize;`
- L61 _public typedef_ `using ValueType = FTransformAnimationAttribute;`
- L63 _public prototype_ `static void TransformBoundValueMap(FBoundValueMap* Map);`
- L64 _public prototype_ `static void TransformUnboundValueMap(FUnboundValueMap* Map);`

#### struct `UE::UAF::Transformers::Private::FSanitize_QuaternionAttribute`  
`struct FSanitize_QuaternionAttribute`  
_L67-74_
- L69 _public typedef_ `using TransformerType = FSanitize;`
- L70 _public typedef_ `using ValueType = FQuaternionAnimationAttribute;`
- L72 _public prototype_ `static void TransformBoundValueMap(FBoundValueMap* Map);`
- L73 _public prototype_ `static void TransformUnboundValueMap(FUnboundValueMap* Map);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_UAF_VALIDATE_MAPPED_VALUES !(UE_BUILD_SHIPPING || UE_BUILD_TEST)` — We validate mapped values in development and debug builds
- L13 _macro_ `#define UE_API UAF_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Transformers` (scope `UE::UAF`)
- L34 _namespace_ `namespace Private` (scope `UE::UAF::Transformers`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/Transformers/Transformer.h` (Public)


#### struct `UE::UAF::FValueTransformer`  
`struct FValueTransformer`  
_L21-31_
- desc: Value transformer base type All transformer types must derive from this

#### class `UE::UAF::FValueTransformerListIterator`  
`class FValueTransformerListIterator`  
_L34-55_
- desc: An iterator over a transformer list within the value runtime registry
- L37 _public prototype_ `[[nodiscard]] FValueTransformerListIterator(const FValueTransformerList& TransformerList, int32 StartOffset, int32 Count);`
- L40 _public prototype_ `FValueTransformerListIterator& operator++();` — Increments and moves the iterator to the next transformer entry
- L43 _public prototype_ `[[nodiscard]] explicit operator bool() const;` — Returns whether or not the iterator still contains values
- L46 _public prototype_ `[[nodiscard]] UScriptStruct* GetValueType() const;` — Returns the value type that the transformer operates on for the current entry
- L49 _public prototype_ `[[nodiscard]] FRawTransformerFunc GetTransformerFunc() const;` — Returns the transformer for the current entry
- L52 _private member_ `UScriptStruct* const* ValueTypePtr = nullptr;`
- L53 _private member_ `const FRawTransformerFunc* TransformerFuncPtr = nullptr;`
- L54 _private member_ `UScriptStruct* const* ValueTypeEndPtr = nullptr;`
- L181 _function_ `inline FValueTransformerListIterator::FValueTransformerListIterator(const FValueTransformerList& TransformerList, int32 StartOffset, int32 Count) : ValueTypePtr(TransformerList.ValueTypes.GetData() + StartOffset) , TransformerFuncPtr(TransformerList.Transformers.GetData() + StartOffset) , ValueTypeEndPtr(ValueTypePtr + Count)`
- L188 _function_ `inline FValueTransformerListIterator& FValueTransformerListIterator::operator++()`
- L196 _function_ `inline FValueTransformerListIterator::operator bool() const`
- L201 _function_ `inline UScriptStruct* FValueTransformerListIterator::GetValueType() const`
- L206 _function_ `inline FRawTransformerFunc FValueTransformerListIterator::GetTransformerFunc() const`

#### class `UE::UAF::FValueTransformerList`  
`class FValueTransformerList`  
_L61-110_
- desc: A list of transformer specializations that operators over various value types. Transformers have a base type (e.g. interpolate, sanitize) and can be specialized to operate on arbitrary value types (e.g. FFloatAnimationAttribute). They can also transform two types of containers: bound value maps and unbound value maps.
- L65 _public prototype_ `FValueTransformerList();` — Creates an empty transformer list
- L68 _public prototype_ `[[nodiscard]] explicit FValueTransformerList(FName TransformerName);` — Creates a transformer list for the specified transformer type
- L71 _public prototype_ `[[nodiscard]] FName GetTransformerName() const;` — Returns the transformer name
- L74 _public function_ `[[nodiscard]] int32 NumBoundValueMapTransformers() const` — Returns the number of bound value map transformers in this list
- L77 _public function_ `[[nodiscard]] int32 NumUnboundValueMapTransformers() const` — Returns the number of unbound value map transformers in this list
- L80 _public prototype_ `bool AddBoundValueMapTransformer(UScriptStruct* ValueType, FRawTransformerFunc TransformerFunc);` — Adds a new bound value map transformer entry
- L83 _public prototype_ `bool AddUnboundValueMapTransformer(UScriptStruct* ValueType, FRawTransformerFunc TransformerFunc);` — Adds a new unbound value map transformer entry
- L86 _public function_ `[[nodiscard]] FValueTransformerListIterator CreateBoundValueMapTransformerIterator() const` — Returns an iterator over all bound value map transformer specializations within
- L89 _public function_ `[[nodiscard]] FValueTransformerListIterator CreateUnboundValueMapTransformerIterator() const` — Returns an iterator over all unbound value map transformer specializations within
- L93 _private member_ `FName TransformerName;` — The type of the transformer (e.g. interpolate, sanitize)
- L96 _private member_ `int32 BoundValueMapTransformerCount = 0;` — The number of bound value map transformers in this list
- L101 _private member_ `TArray<UScriptStruct*> ValueTypes;` — List of value types for which we have transformers registered (e.g. FTransformAnimationAttribute, FFloatAnimationAttribute) (sorted by container type, then by value type) This list is split in two, bound value map transformers come first, then unbound value map transformers Each sub-list is sorted by value type
- L106 _private member_ `TArray<FRawTransformerFunc> Transformers;` — List of transformer functions for each value type (sorted by container type, then by value type) This list is split in two, bound value map transformers come first, then unbound value map transformers Each sub-list is sorted by value type

#### struct `UE::UAF::FValueTransformerListWithBoundMapCollectionJoinOp`  
`struct FValueTransformerListWithBoundMapCollectionJoinOp`  
_L116-154_
- desc: An operator structure to join value transformer lists and attribute collections using InnerJoin/OuterJoin/etc Ensures that the predicate is called for each bound value map with a value type that has a corresponding transformer
- L119 _public member_ `static constexpr intptr_t WILDCARD_ATTRIBUTE_TYPE_VALUE = static_cast<intptr_t>(static_cast<uintptr_t>(~0ULL) >> 1);` — Key sorting uses signed comparison, use the largest signed value regardless of pointer size
- L122 _public function_ `bool IsMatch(FAttributeMappingKey ReferenceKey, FAttributeMappingKey TestKey) const` — We enable fuzzy matching by implementing its API
- L136 _public function_ `FAttributeMappingKey GetLargestKey() const`
- L139 _public function_ `FAttributeMappingKey GetKey(const FValueTransformerListIterator& It) const` — FAttributeValueTransformerListIterator entries
- L145 _public function_ `FRawTransformerFunc GetValue(const FValueTransformerListIterator& It) const`
- L149 _public function_ `template<class IteratorType> FAttributeMappingKey GetKey(const IteratorType& It) const` — Normal FBoundMapCollectionJoinOp
- L152 _public prototype_ `template<class IteratorType> requires requires (const IteratorType& It)`
- L153 _public function_ `template<class IteratorType> requires requires (const IteratorType& It)`

#### struct `UE::UAF::FValueTransformerListWithUnboundMapCollectionJoinOp`  
`struct FValueTransformerListWithUnboundMapCollectionJoinOp`  
_L158-176_
- desc: An operator structure to join value transformer lists and attribute collections using InnerJoin/OuterJoin/etc Ensures that the predicate is called for each unbound value map with a value type that has a corresponding transformer
- L161 _public member_ `static constexpr intptr_t KEY_LARGEST_VALUE = static_cast<intptr_t>(static_cast<uintptr_t>(~0ULL) >> 1);` — Key sorting uses signed comparison, use the largest signed value regardless of pointer size
- L163 _public function_ `UScriptStruct* GetLargestKey() const`
- L166 _public function_ `UScriptStruct* GetKey(const FValueTransformerListIterator& It) const` — FAttributeValueTransformerListIterator entries
- L167 _public function_ `FRawTransformerFunc GetValue(const FValueTransformerListIterator& It) const`
- L171 _public function_ `template<class IteratorType> UScriptStruct* GetKey(const IteratorType& It) const` — Normal FUnboundMapCollectionJoinOp
- L174 _public prototype_ `template<class IteratorType> requires requires (const IteratorType& It)`
- L175 _public function_ `template<class IteratorType> requires requires (const IteratorType& It)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAF_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L17 _typedef_ `using FRawTransformerFunc = void(*)();` (scope `UE::UAF`) — A raw function pointer for all transformers (static functions) Only used for storage purposes, NEVER CALL THIS!
- L112 _typedef_ `using FValueTransformerMapPtr = TSharedPtr<TMap<FName, FValueTransformerList>>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/UnboundMapCollection.h` (Public)


#### class `UE::UAF::TUnboundMapCollectionIterator`  
`template<class ContainerType> class TUnboundMapCollectionIterator`  
_L15-47_
- desc: A iterator that iterates over all unbound value maps within an unbound map collection
- L18 _public member_ `static constexpr bool bIsContainerConst = std::is_const_v<ContainerType>;`
- L20 _public typedef_ `using EntryPtrType = typename std::conditional<bIsContainerConst, const typename ContainerType::FMapEntry*, typename ContainerType::FMapEntry*>::type;`
- L21 _public typedef_ `using MapType = typename std::conditional<bIsContainerConst, const FUnboundValueMap*, FUnboundValueMap*>::type;`
- L24 _public prototype_ `[[nodiscard]] TUnboundMapCollectionIterator() = default;` — Creates an empty iterator
- L27 _public prototype_ `[[nodiscard]] TUnboundMapCollectionIterator(ContainerType& Collection);` — Creates an iterator over the map entries within the specified collection
- L30 _public prototype_ `TUnboundMapCollectionIterator& operator++();` — Increments and moves the iterator to the next map entry
- L33 _public prototype_ `[[nodiscard]] explicit operator bool() const;` — Returns whether or not the iterator still contains values
- L36 _public prototype_ `[[nodiscard]] UScriptStruct* GetValueType() const;` — Returns the value type of the current map entry
- L39 _public prototype_ `[[nodiscard]] MapType GetMap() const;` — Returns the map from the current entry
- L43 _private member_ `EntryPtrType EntryPtr = nullptr;` — Current map entry
- L46 _private member_ `EntryPtrType EntryEndPtr = nullptr;` — One past the last map entry
- L273 _function_ `template<class ContainerType> inline TUnboundMapCollectionIterator<ContainerType>::TUnboundMapCollectionIterator(ContainerType& Collection) : EntryPtr(Collection.Maps) , EntryEndPtr(Collection.Maps + Collection.MapCount)`
- L280 _function_ `template<class ContainerType> inline TUnboundMapCollectionIterator<ContainerType>& TUnboundMapCollectionIterator<ContainerType>::operator++()`
- L287 _function_ `template<class ContainerType> inline TUnboundMapCollectionIterator<ContainerType>::operator bool() const`
- L293 _function_ `template<class ContainerType> inline UScriptStruct* TUnboundMapCollectionIterator<ContainerType>::GetValueType() const`
- L299 _function_ `template<class ContainerType> inline typename TUnboundMapCollectionIterator<ContainerType>::MapType TUnboundMapCollectionIterator<ContainerType>::GetMap() const`

#### class `UE::UAF::FUnboundMapCollection`  
`class FUnboundMapCollection`  
_L55-164_
- desc: Unbound Value Map Collection Holds a sorted collection of unbound value maps. Entries are sorted by value type.
- L68 _public prototype_ `FUnboundMapCollection(FReallocFun InReallocFun);`
- L69 _public prototype_ `FUnboundMapCollection(const FUnboundMapCollection& Other);`
- L70 _public prototype_ `FUnboundMapCollection(FUnboundMapCollection&& Other);`
- L71 _public prototype_ `~FUnboundMapCollection();`
- L73 _public prototype_ `FUnboundMapCollection& operator=(const FUnboundMapCollection& Other);`
- L74 _public prototype_ `FUnboundMapCollection& operator=(FUnboundMapCollection&& Other);`
- L77 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not we are empty
- L80 _public prototype_ `void Reset();` — Resets the collection while retaining our capacity
- L83 _public prototype_ `void Empty();` — Clears the collection of any content
- L86 _public prototype_ `[[nodiscard]] FReallocFun GetAllocator() const;` — Returns the allocator function this collection was initialized with
- L89 _public prototype_ `[[nodiscard]] int32 Num() const;` — Returns the number of maps contained within
- L93 _public prototype_ `template <class ValueType> [[nodiscard]] TUnboundValueMap<ValueType>* Add();` — Constructs and adds a new map to this collection. Returns nullptr if we fail to add an entry (e.g. duplicate)
- L97 _public prototype_ `[[nodiscard]] FUnboundValueMap* Add(UScriptStruct* ValueType);` — Constructs and adds a new map to this collection. Returns nullptr if we fail to add an entry (e.g. duplicate)
- L101 _public prototype_ `bool Add(FUnboundValueMap* Map);` — Adds a new map to this collection. Returns false if we fail to add an entry (e.g. duplicate, mismatched allocator)
- L105 _public prototype_ `bool Append(FUnboundValueMap* Map);` — Appends a new map to this collection (the input must belong at the end of the sorted map list). Returns false if we fail to add an entry (e.g. duplicate, mismatched allocator, not sorted)
- L109 _public prototype_ `bool Remove(FUnboundValueMap* Map);` — Removes the specified map from this collection Returns whether or not the entry was successfully removed
- L113 _public prototype_ `bool Remove(UScriptStruct* ValueType);` — Removes the specified map from this collection Returns whether or not the entry was successfully removed
- L117 _public prototype_ `template <class ValueType> [[nodiscard]] TUnboundValueMap<ValueType>* Find();` — Finds a map of the specified ValueType in this collection Returns nullptr if this collection does not contain such a mapping
- L121 _public prototype_ `template <class ValueType> [[nodiscard]] const TUnboundValueMap<ValueType>* Find() const;` — Finds a map of the specified ValueType in this collection Returns nullptr if this collection does not contain such a mapping
- L125 _public prototype_ `[[nodiscard]] FUnboundValueMap* Find(UScriptStruct* ValueType);` — Finds a map of the specified ValueType in this collection Returns nullptr if this collection does not contain such a mapping
- L129 _public prototype_ `[[nodiscard]] const FUnboundValueMap* Find(UScriptStruct* ValueType) const;` — Finds a map of the specified ValueType in this collection Returns nullptr if this collection does not contain such a mapping
- L133 _public prototype_ `template <class ValueType> [[nodiscard]] TUnboundValueMap<ValueType>* FindOrAdd();` — Finds or adds a map of the specified ValueType in this collection Returns nullptr if we fail to add an entry (e.g. duplicate)
- L137 _public prototype_ `[[nodiscard]] FUnboundValueMap* FindOrAdd(UScriptStruct* ValueType);` — Finds or adds a map of the specified ValueType in this collection Returns nullptr if we fail to add an entry (e.g. duplicate)
- L140 _public typedef_ `using FIterator = TUnboundMapCollectionIterator<FUnboundMapCollection>;` — Iterators
- L141 _public typedef_ `using FConstIterator = TUnboundMapCollectionIterator<const FUnboundMapCollection>;`
- L144 _public prototype_ `[[nodiscard]] FIterator CreateIterator();` — Returns an iterator over all maps contained within, sorted by their key (value type)
- L145 _public prototype_ `[[nodiscard]] FConstIterator CreateConstIterator() const;`
- L148 _private prototype_ `FUnboundValueMap** AddImpl(UScriptStruct* ValueType, bool bConstructMap);`
- L151 _private member_ `FMapEntry* Maps = nullptr;` — An array of maps (sorted by value type)
- L154 _private member_ `int32 MapCount = 0;` — How many maps are contained within this collection
- L157 _private member_ `int32 MapCapacity = 0;` — How many maps we can contain within this collection
- L160 _private member_ `FReallocFun ReallocFun = nullptr;` — The indirect allocator function pointer
- L208 _function_ `template <class ValueType> inline TUnboundValueMap<ValueType>* FUnboundMapCollection::Add()`
- L230 _function_ `template <class ValueType> inline TUnboundValueMap<ValueType>* FUnboundMapCollection::Find()`
- L236 _function_ `template <class ValueType> inline const TUnboundValueMap<ValueType>* FUnboundMapCollection::Find() const`
- L242 _function_ `template <class ValueType> inline TUnboundValueMap<ValueType>* FUnboundMapCollection::FindOrAdd()`
- L252 _function_ `inline typename FUnboundMapCollection::FIterator FUnboundMapCollection::CreateIterator()`
- L257 _function_ `inline typename FUnboundMapCollection::FConstIterator FUnboundMapCollection::CreateConstIterator() const`

#### struct `UE::UAF::FUnboundMapCollection::FMapEntry`  
`struct FMapEntry`  
_L58-65_
- L61 _public member_ `UScriptStruct* ValueType = nullptr;` — The value type (key) that identifies this entry
- L64 _public member_ `FUnboundValueMap* Map = nullptr;` — The map containing our values

#### class `UE::UAF::FUnboundMapCollectionHeap`  
`class FUnboundMapCollectionHeap : public FUnboundMapCollection`  
_L167-174_
- inherits: `FUnboundMapCollection`
- desc: A heap allocated unbound map collection
- L171 _public prototype_ `FUnboundMapCollectionHeap();` — Constructs an empty collection
- L262 _function_ `inline FUnboundMapCollectionHeap::FUnboundMapCollectionHeap() : FUnboundMapCollection(&FAllocatorTypeTrait<FDefaultAllocator>::Realloc)`

#### class `UE::UAF::FUnboundMapCollectionStack`  
`class FUnboundMapCollectionStack : public FUnboundMapCollection`  
_L177-184_
- inherits: `FUnboundMapCollection`
- desc: A Mem-Stack allocated unbound map collection
- L181 _public prototype_ `FUnboundMapCollectionStack();` — Constructs an empty collection
- L267 _function_ `inline FUnboundMapCollectionStack::FUnboundMapCollectionStack() : FUnboundMapCollection(&FAllocatorTypeTrait<TMemStackAllocator<>>::Realloc)`

#### struct `UE::UAF::FUnboundMapCollectionJoinOp`  
`struct FUnboundMapCollectionJoinOp`  
_L187-199_
- desc: An operator structure to join unbound map collections using InnerJoin/OuterJoin/etc
- L190 _public member_ `static constexpr intptr_t LARGEST_KEY_VALUE = static_cast<intptr_t>(static_cast<uintptr_t>(~0ULL) >> 1);` — Key sorting uses signed comparison, use the largest signed value regardless of pointer size
- L192 _public function_ `UScriptStruct* GetLargestKey() const`
- L194 _public function_ `UScriptStruct* GetKey(const FUnboundMapCollection::FIterator& It) const`
- L195 _public function_ `UScriptStruct* GetKey(const FUnboundMapCollection::FConstIterator& It) const`
- L197 _public function_ `FUnboundValueMap* GetValue(const FUnboundMapCollection::FIterator& It) const`
- L198 _public function_ `const FUnboundValueMap* GetValue(const FUnboundMapCollection::FConstIterator& It) const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L205 _namespace_ `namespace UE`
- L205 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/UnboundValueMap.h` (Public)


#### class `UE::UAF::FUnboundValueMap`  
`class FUnboundValueMap`  
_L16-106_
- desc: Untyped base class for TUnboundValueMap
- L22 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not this map has any values
- L25 _public prototype_ `[[nodiscard]] int32 Num() const;` — Returns the number of mapped values
- L28 _public prototype_ `[[nodiscard]] int32 Max() const;` — Returns the maximum number of values we can map
- L31 _public prototype_ `[[nodiscard]] UScriptStruct* GetValueType() const;` — Returns the mapped value type
- L34 _public prototype_ `[[nodiscard]] int32 GetAllocatedSize() const;` — Returns the total allocated size for this map
- L37 _public prototype_ `[[nodiscard]] FReallocFun GetAllocator() const;` — Returns the allocator function this map was initialized with
- L40 _public prototype_ `[[nodiscard]] virtual FUnboundValueMap* Duplicate(FReallocFun InReallocFun) const = 0;` — Returns a copy of this map using the specified allocator
- L44 _public prototype_ `virtual void CopyTo(FUnboundValueMap& Other) const = 0;` — Copies the content of this map into another Both must have matching value types
- L49 _public prototype_ `virtual void MoveTo(FUnboundValueMap& Other);` — Moves the content of this map to another Both must have matching value types The content of this map after the move is undefined, just like with move assignment
- L52 _public prototype_ `[[nodiscard]] int32 IndexOf(FName Name) const;` — Finds a mapping and returns its index or INDEX_NONE if not found, O(logN)
- L55 _public prototype_ `[[nodiscard]] bool Contains(FName Name) const;` — Returns whether or not this map contains the specified mapped value, O(logN)
- L58 _public prototype_ `[[nodiscard]] FName GetName(int32 Index) const;` — Retrieves a mapping name by index, O(1)
- L63 _public prototype_ `virtual bool AddWithSetter(FName Name, const TFunctionRef<void(UScriptStruct* ValueType, uint8* OutValuePtr)>& ValueSetter) = 0;` — Adds a new mapping, sets the value using the provided setter, O(logN) Returns whether or not we inserted (we can fail if a value with that name already exists) The value setter (and/or caller) is responsible for validating the value type
- L67 _public prototype_ `virtual void GetValueWithGetter(int32 Index, const TFunctionRef<void(UScriptStruct* ValueType, const uint8* ValuePtr)>& ValueGetter) const = 0;` — Gets a value at the specified index using a value getter function, O(1) The value getter (and/or caller) is responsible for validating the value type
- L71 _protected prototype_ `FUnboundValueMap();` — Default construction for an empty map
- L74 _protected prototype_ `FUnboundValueMap(UScriptStruct* ValueType, FReallocFun ReallocFun, int32 ContainerSize);` — Constructs a map but does not allocate its memory, derived types are responsible for it
- L77 _protected prototype_ `virtual ~FUnboundValueMap();` — Destroys the map and frees its memory
- L80 _protected prototype_ `[[nodiscard]] FName* GetNames();` — Returns a pointer to the start of the names
- L81 _protected prototype_ `[[nodiscard]] const FName* GetNames() const;`
- L84 _protected member_ `UScriptStruct* ValueTypeStruct = nullptr;` — The type of values this map contains
- L87 _protected member_ `int32 NumValues = 0;` — The number of values mapped in our buffer
- L90 _protected member_ `int32 MaxValues = 0;` — The maximum number of values that we can map in our buffer
- L95 _protected member_ `uint8* DataPtr = nullptr;` — The base untyped pointer for our names/values Names and values are allocated together within the same contiguous memory buffer Names are first within the buffer followed by value types using default alignment
- L98 _protected member_ `FReallocFun ReallocFun = nullptr;` — The indirect allocator function pointer
- L101 _protected member_ `int32 ContainerSize = 0;` — The size in bytes of this container (excluding any externally allocated data)
- L293 _function_ `inline int32 FUnboundValueMap::IndexOf(FName Name) const`
- L307 _function_ `inline bool FUnboundValueMap::Contains(FName Name) const`
- L312 _function_ `inline FName FUnboundValueMap::GetName(int32 Index) const`
- L318 _function_ `inline FName* FUnboundValueMap::GetNames()`
- L323 _function_ `inline const FName* FUnboundValueMap::GetNames() const`

#### class `UE::UAF::TUnboundValueMapIterator`  
`template<class ContainerType> class TUnboundValueMapIterator`  
_L110-143_
- desc: A iterator that iterates over all name/value pairs within an unbound value map
- L113 _public member_ `static constexpr bool bIsContainerConst = std::is_const_v<ContainerType>;`
- L115 _public typedef_ `using NamePtrType = typename std::conditional<bIsContainerConst, const FName*, FName*>::type;`
- L116 _public typedef_ `using ValuePtrType = typename std::conditional<bIsContainerConst, const typename ContainerType::ValueType*, typename ContainerType::ValueType*>::type;`
- L119 _public prototype_ `[[nodiscard]] TUnboundValueMapIterator() = default;` — Creates an empty iterator
- L122 _public prototype_ `[[nodiscard]] TUnboundValueMapIterator(ContainerType& Map);` — Creates an iterator over the name/value map entries within the specified unbound value map
- L125 _public prototype_ `TUnboundValueMapIterator& operator++();` — Increments and moves the iterator to the next name/value pair
- L128 _public prototype_ `[[nodiscard]] explicit operator bool() const;` — Returns whether or not the iterator still contains values
- L131 _public prototype_ `[[nodiscard]] FName GetName() const;` — Returns the name of the current name/value pair
- L134 _public prototype_ `[[nodiscard]] ValuePtrType GetValue() const;` — Returns the value of the current name/value pair
- L138 _private member_ `NamePtrType NamePtr = nullptr;` — Current name/value pair
- L139 _private member_ `ValuePtrType ValuePtr = nullptr;`
- L142 _private member_ `NamePtrType NameEndPtr = nullptr;` — One past the last name/value pair
- L754 _function_ `template<class ContainerType> inline TUnboundValueMapIterator<ContainerType>::TUnboundValueMapIterator(ContainerType& Map) : NamePtr(Map.GetNames()) , ValuePtr(Map.GetValues()) , NameEndPtr(NamePtr + Map.Num())`
- L762 _function_ `template<class ContainerType> inline TUnboundValueMapIterator<ContainerType>& TUnboundValueMapIterator<ContainerType>::operator++()`
- L770 _function_ `template<class ContainerType> inline TUnboundValueMapIterator<ContainerType>::operator bool() const`
- L776 _function_ `template<class ContainerType> inline FName TUnboundValueMapIterator<ContainerType>::GetName() const`
- L782 _function_ `template<class ContainerType> inline typename TUnboundValueMapIterator<ContainerType>::ValuePtrType TUnboundValueMapIterator<ContainerType>::GetValue() const`

#### class `UE::UAF::TUnboundValueMap`  
`template<class InValueType> class TUnboundValueMap : public FUnboundValueMap`  
_L148-228_
- inherits: `FUnboundValueMap`
- desc: Encapsulates a mapping of FName to value type Value types must be a UStruct
- L152 _public typedef_ `using ValueType = InValueType;` — The type of values held in this map
- L155 _public prototype_ `[[nodiscard]] virtual FUnboundValueMap* Duplicate(FReallocFun InReallocFun) const override;` — Returns a copy of this map using the specified allocator
- L159 _public prototype_ `virtual void CopyTo(FUnboundValueMap& Other) const override;` — Copies the content of this map into another Both must have matching value types
- L164 _public prototype_ `virtual bool AddWithSetter(FName Name, const TFunctionRef<void(UScriptStruct* ValueType, uint8* OutValuePtr)>& ValueSetter) override;` — Adds a new mapping, sets the value using the provided setter, O(logN) Returns whether or not we inserted (we can fail if a value with that name already exists) The value setter (and/or caller) is responsible for validating the value type
- L168 _public prototype_ `virtual void GetValueWithGetter(int32 Index, const TFunctionRef<void(UScriptStruct* ValueType, const uint8* ValuePtr)>& ValueGetter) const override;` — Gets a value at the specified index using a value getter function, O(1) The value getter (and/or caller) is responsible for validating the value type
- L172 _public prototype_ `bool Add(FName Name, const InValueType& Value);` — Adds a new mapping, O(logN) Returns whether or not we inserted (we can fail if a value with that name already exists)
- L176 _public prototype_ `bool Append(FName Name, const InValueType& Value);` — Adds a new mapping at the end of the map, must be sorted, O(1) Returns whether or not we inserted (we can fail if the value isn't sorted to land at the end of the map)
- L180 _public prototype_ `bool Remove(FName Name);` — Removes a mapping, O(logN) Returns whether or not we removed the value (we can fail if the name isn't found)
- L183 _public prototype_ `void RemoveAt(int32 Index);` — Removes a mapping, O(1)
- L186 _public prototype_ `[[nodiscard]] InValueType* Find(FName Name);` — Finds a mapping and returns a pointer to it or nullptr if not found, O(logN)
- L187 _public prototype_ `[[nodiscard]] const InValueType* Find(FName Name) const;`
- L190 _public prototype_ `[[nodiscard]] InValueType& GetValue(int32 Index);` — Retrieves a mapping value by index, O(1)
- L191 _public prototype_ `[[nodiscard]] const InValueType& GetValue(int32 Index) const;`
- L195 _public prototype_ `template<class GetNamePredicateType, class GetValuePredicateType> void SetSorted(int32 NumValues, GetNamePredicateType GetNamePredicate, GetValuePredicateType GetValuePredicate);` — Initializes the mapping using sorted inputs, O(N)
- L199 _public prototype_ `template<class GetNamePredicateType, class GetValuePredicateType> void SetUnsorted(int32 NumValues, GetNamePredicateType GetNamePredicate, GetValuePredicateType GetValuePredicate);` — Initializes the mapping using unsorted inputs, O(NlogN)
- L202 _public typedef_ `using FIterator = TUnboundValueMapIterator<TUnboundValueMap<InValueType>>;` — Iterators
- L203 _public typedef_ `using FConstIterator = TUnboundValueMapIterator<const TUnboundValueMap<InValueType>>;`
- L206 _public prototype_ `[[nodiscard]] FIterator CreateIterator();` — Returns an iterator over all name/value pairs contained within, sorted by their name
- L207 _public prototype_ `[[nodiscard]] FConstIterator CreateConstIterator() const;`
- L210 _protected member_ `static const int32 ValueTypeAlignment = sizeof(InValueType) >= 16 ? 16 : 8;`
- L213 _protected prototype_ `TUnboundValueMap(UScriptStruct* ValueType, FReallocFun ReallocFun, int32 ContainerSize);` — Constructs a map
- L218 _protected prototype_ `void Grow();`
- L221 _protected prototype_ `InValueType* GetValues();` — Returns a pointer to the start of the values
- L222 _protected prototype_ `const InValueType* GetValues() const;`
- L329 _function_ `template<class InValueType> inline TUnboundValueMap<InValueType>::TUnboundValueMap(UScriptStruct* ValueTypeStruct, FReallocFun InReallocFun, int32 InContainerSize) : FUnboundValueMap(ValueTypeStruct, InReallocFun, InContainerSize)`
- L337 _function_ `template<class InValueType> inline TUnboundValueMap<InValueType>::~TUnboundValueMap()`
- L350 _function_ `template<class InValueType> inline FUnboundValueMap* TUnboundValueMap<InValueType>::Duplicate(FReallocFun InReallocFun) const`
- L372 _function_ `template<class InValueType> inline void TUnboundValueMap<InValueType>::CopyTo(FUnboundValueMap& Other) const`
- L406 _function_ `template<class InValueType> inline bool TUnboundValueMap<InValueType>::AddWithSetter(FName Name, const TFunctionRef<void(UScriptStruct* ValueType, uint8* OutValuePtr)>& ValueSetter)`
- L439 _function_ `template<class InValueType> inline void TUnboundValueMap<InValueType>::GetValueWithGetter(int32 Index, const TFunctionRef<void(UScriptStruct* ValueType, const uint8* ValuePtr)>& ValueGetter) const`
- L447 _function_ `template<class InValueType> inline bool TUnboundValueMap<InValueType>::Add(FName Name, const InValueType& Value)`
- L480 _function_ `template<class InValueType> inline bool TUnboundValueMap<InValueType>::Append(FName Name, const InValueType& Value)`
- L509 _function_ `template<class InValueType> inline bool TUnboundValueMap<InValueType>::Remove(FName Name)`
- L526 _function_ `template<class InValueType> inline void TUnboundValueMap<InValueType>::RemoveAt(int32 Index)`
- L543 _function_ `template<class InValueType> inline InValueType* TUnboundValueMap<InValueType>::Find(FName Name)`
- L558 _function_ `template<class InValueType> inline const InValueType* TUnboundValueMap<InValueType>::Find(FName Name) const`
- L573 _function_ `template<class InValueType> inline InValueType& TUnboundValueMap<InValueType>::GetValue(int32 Index)`
- L581 _function_ `template<class InValueType> inline const InValueType& TUnboundValueMap<InValueType>::GetValue(int32 Index) const`
- L590 _function_ `template<class InValueType> template<class GetNamePredicateType, class GetValuePredicateType> inline void TUnboundValueMap<InValueType>::SetSorted(int32 InNumValues, GetNamePredicateType GetNamePredicate, GetValuePredicateType GetValuePredicate)`
- L628 _function_ `template<class InValueType> template<class GetNamePredicateType, class GetValuePredicateType> inline void TUnboundValueMap<InValueType>::SetUnsorted(int32 InNumValues, GetNamePredicateType GetNamePredicate, GetValuePredicateType GetValuePredicate)`
- L689 _function_ `template<class InValueType> inline typename TUnboundValueMap<InValueType>::FIterator TUnboundValueMap<InValueType>::CreateIterator()`
- L695 _function_ `template<class InValueType> inline typename TUnboundValueMap<InValueType>::FConstIterator TUnboundValueMap<InValueType>::CreateConstIterator() const`
- L701 _function_ `template<class InValueType> FORCENOINLINE void TUnboundValueMap<InValueType>::Grow()`
- L740 _function_ `template<class InValueType> inline InValueType* TUnboundValueMap<InValueType>::GetValues()`
- L747 _function_ `template<class InValueType> inline const InValueType* TUnboundValueMap<InValueType>::GetValues() const`

#### struct `UE::UAF::FUnboundValueMapJoinOp`  
`struct FUnboundValueMapJoinOp`  
_L231-249_
- desc: An operator structure to join unbound value maps using InnerJoin/OuterJoin/etc
- L234 _public function_ `static constexpr bool HasPredicateWithKey()` — We generally want the key in our predicate since the values by themselves have little meaning
- L236 _public function_ `bool IsLessThan(FName LHS, FName RHS) const`
- L242 _public function_ `FName GetLargestKey() const` — Special dummy FName that is larger than all other FNames in fast sorted order
- L245 _public function_ `template<typename IteratorType> FName GetKey(const IteratorType& It) const`
- L248 _public function_ `template<typename IteratorType> typename IteratorType::ValuePtrType GetValue(const IteratorType& It) const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L253 _prototype_ `template<class ValueType> TUnboundValueMap<ValueType>* MakeUnboundValueMap(FReallocFun ReallocFun);` (scope `UE::UAF`) — Allocates and constructs a new unbound value map for the specified value type
- L256 _prototype_ `void ReleaseUnboundValueMap(FUnboundValueMap* Map);` (scope `UE::UAF`) — Releases and destroys the specified unbound value map
- L260 _function_ `template<class ValueType> UE_FORCEINLINE_HINT TUnboundValueMap<ValueType>* Cast(FUnboundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped name/value map to a typed name/value map
- L267 _function_ `template<class ValueType> UE_FORCEINLINE_HINT const TUnboundValueMap<ValueType>* Cast(const FUnboundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped name/value map to a typed name/value map
- L274 _function_ `template<class ValueType> inline TUnboundValueMap<ValueType>* CastChecked(FUnboundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped name/value map to a typed name/value map with an assert if the types mismatch
- L283 _function_ `template<class ValueType> inline const TUnboundValueMap<ValueType>* CastChecked(const FUnboundValueMap* Src)` (scope `UE::UAF`) — Cast from an untyped name/value map to a typed name/value map with an assert if the types mismatch
- L656 _typedef_ `using FTmpElementType = TPair<FName, InValueType>;` (scope `UE::UAF::TUnboundValueMap::SetUnsorted`) — TODO: We don't appear to have a version of Algo::Sort that works on iterators and so we can't sort our two arrays in tandem, use a temporary array instead
- L665 _function_ `Algo::Sort(TmpElements, [](const FTmpElementType& LHS, const FTmpElementType& RHS) { return LHS.Key.FastLess(RHS.Key); });` (scope `UE::UAF::TUnboundValueMap::SetUnsorted`) — Sort our temporary elements
- L788 _function_ `template<class ValueType> inline TUnboundValueMap<ValueType>* MakeUnboundValueMap(FReallocFun ReallocFun)` (scope `UE::UAF`)
- L799 _function_ `inline void ReleaseUnboundValueMap(FUnboundValueMap* Map)` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/ValueBundle.h` (Public)


#### class `UE::UAF::FValueBundle`  
`class FValueBundle`  
_L32-98_
- desc: Value Bundle This struct holds values produced by UAF. They come in two flavors: bound and unbound. Bound values are fast and defined up front in the skeleton set binding asset. Unbound values are slower but produced on demand during evaluation.
- L35 _public prototype_ `FValueBundle(const FAttributeNamedSetPtr& NamedSet, FReallocFun InReallocFun);`
- L36 _public prototype_ `FValueBundle(const FValueBundle& Other);`
- L37 _public prototype_ `FValueBundle(FValueBundle&& Other);`
- L38 _public prototype_ `~FValueBundle();`
- L40 _public prototype_ `FValueBundle& operator=(const FValueBundle& Other);`
- L41 _public prototype_ `FValueBundle& operator=(FValueBundle&& Other);`
- L44 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — Returns whether or not we are empty
- L47 _public prototype_ `[[nodiscard]] const FAttributeNamedSetPtr& GetNamedSet() const;` — Returns the named set this collection maps to
- L50 _public prototype_ `[[nodiscard]] FValueSpace GetValueSpace() const;` — Returns the space our values live in
- L54 _public prototype_ `void SetValueSpace(FValueSpace ValueSpace);` — Sets the space our values live in Note that care must be taken when changing the value space as all values within the collection must be migrated accordingly
- L61 _public prototype_ `void InitWithValueSpace(FValueSpace ValueSpace);` — Sets the space our values line in and default initializes this collection For local/component space, we initialize with the reference pose For additive space, we initialize with the additive identity Other spaces initialize to their identity Note that only bound values are default initialized
- L64 _public prototype_ `[[nodiscard]] bool IsAdditive() const;` — Returns whether or not the space our values live in is additive
- L67 _public prototype_ `void Reset(const FAttributeNamedSetPtr& NamedSet);` — Resets the collection with the specified named set
- L70 _public prototype_ `void Empty();` — Clears the collection of any content
- L73 _public prototype_ `[[nodiscard]] FReallocFun GetAllocator() const;` — Returns the allocator function this collection was initialized with
- L76 _public prototype_ `[[nodiscard]] FBoundMapCollection& GetBoundValueMaps();` — Returns a collection of bound value maps
- L77 _public prototype_ `[[nodiscard]] const FBoundMapCollection& GetBoundValueMaps() const;`
- L80 _public prototype_ `[[nodiscard]] FUnboundMapCollection& GetUnboundValueMaps();` — Returns a collection of unbound value maps
- L81 _public prototype_ `[[nodiscard]] const FUnboundMapCollection& GetUnboundValueMaps() const;`
- L85 _private member_ `FAttributeNamedSetPtr NamedSet;` — The named set we are based on, every set mapping uses a typed set within it
- L88 _private member_ `FBoundMapCollection BoundMaps;` — A collection of bound value maps
- L91 _private member_ `FUnboundMapCollection UnboundMaps;` — A collection of unbound value maps
- L94 _private member_ `FValueSpace ValueSpace;` — The space in which our values live
- L97 _private member_ `FReallocFun ReallocFun = nullptr;` — The indirect allocator function pointer

#### class `UE::UAF::FValueBundleHeap`  
`class FValueBundleHeap : public FValueBundle`  
_L101-111_
- inherits: `FValueBundle`
- desc: A heap allocated value bundle
- L105 _public prototype_ `FValueBundleHeap();` — Constructs an empty bundle
- L108 _public prototype_ `explicit FValueBundleHeap(const FAttributeNamedSetPtr& NamedSet);` — Constructs an empty bundle based on the specified named set
- L186 _function_ `inline FValueBundleHeap::FValueBundleHeap() : FValueBundle(nullptr, &FAllocatorTypeTrait<FDefaultAllocator>::Realloc)`
- L191 _function_ `inline FValueBundleHeap::FValueBundleHeap(const FAttributeNamedSetPtr& NamedSet) : FValueBundle(NamedSet, &FAllocatorTypeTrait<FDefaultAllocator>::Realloc)`

#### class `UE::UAF::FValueBundleStack`  
`class FValueBundleStack : public FValueBundle`  
_L114-124_
- inherits: `FValueBundle`
- desc: A Mem-Stack allocated value bundle
- L118 _public prototype_ `FValueBundleStack();` — Constructs an empty bundle
- L121 _public prototype_ `explicit FValueBundleStack(const FAttributeNamedSetPtr& NamedSet);` — Constructs an empty bundle based on the specified named set
- L196 _function_ `inline FValueBundleStack::FValueBundleStack() : FValueBundle(nullptr, &FAllocatorTypeTrait<TMemStackAllocator<>>::Realloc)`
- L201 _function_ `inline FValueBundleStack::FValueBundleStack(const FAttributeNamedSetPtr& NamedSet) : FValueBundle(NamedSet, &FAllocatorTypeTrait<TMemStackAllocator<>>::Realloc)`

#### struct `FUAFValueBundle`  
`struct FUAFValueBundle`  
_L139-179_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Value Bundle"))`
- desc: Value Bundle This struct holds attributes produced by UAF. They come in two flavors: static (set map) and dynamic (map). Static attributes are fast and defined up front in the skeleton set binding asset. Dynamic attributes are slower but produced on demand during evaluation. This struct can also represent a 'virtual value', for instance an inlined, or owned graph instance
- L144 _public function_ `void SetAsRefPose()` — Set as a reference pose (the assumed value of an empty value bundle)
- L150 _public function_ `bool IsRefPose() const` — Get whether this is a reference pose
- L157 _public function_ `template<typename ImplType, typename... ArgsType> void SetAs(ArgsType&&... InArgs)` — Set as an implementation - @see UE::UAF::IVirtualValueBundle
- L164 _public function_ `const UE::UAF::IVirtualValueBundle* GetImpl() const` — Access the implementation
- L170 _public function_ `UE::UAF::IVirtualValueBundle& GetImplChecked() const` — Access the implementation, asserting if it is invalid/refpose
- L178 _private member_ `TSharedPtr<UE::UAF::IVirtualValueBundle> Impl;` — Implementation

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UAF_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L126 _typedef_ `using FValueBundlePtr = TSharedPtr<FValueBundle, ESPMode::ThreadSafe>;` (scope `UE::UAF`)
- L184 _namespace_ `namespace UE`
- L184 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/ValueRuntimeRegistry.h` (Public)


#### class `UE::UAF::FValueRuntimeRegistry`  
`class FValueRuntimeRegistry`  
_L16-73_
- desc: A global registry to store value runtime metadata
- L21 _public typedef_ `using BoundValueMapConstructorFun = TFunction<FBoundValueMap*(const FBoundValueMap::FConstructArgs& Args)>;`
- L22 _public typedef_ `using UnboundValueMapConstructorFun = TFunction<FUnboundValueMap*(FReallocFun ReallocFun)>;`
- L25 _public prototype_ `[[nodiscard]] static FValueRuntimeRegistry& Get();` — Returns the value runtime registry instance
- L28 _public prototype_ `[[nodiscard]] FBoundValueMap* ConstructBoundValueMap(const FBoundValueMap::FConstructArgs& Args) const;` — Constructs a bound value map from its UStruct value type
- L31 _public prototype_ `[[nodiscard]] FUnboundValueMap* ConstructUnboundValueMap(UScriptStruct* ValueType, FReallocFun ReallocFun) const;` — Constructs a name/value map from its UStruct value type
- L34 _public prototype_ `[[nodiscard]] FValueTransformerMapPtr GetTransformerMap() const;` — Returns the map of known value transformers
- L38 _public prototype_ `template<class ValueType> void RegisterBoundValueMapInitializer();` — Registers a bound value map of the specified value type
- L42 _public prototype_ `template<class ValueType> void RegisterUnboundValueMapInitializer();` — Registers a name/value map of the specified value type
- L45 _public prototype_ `template<class TransformerSpecializationType> bool RegisterValueTransformer();`
- L48 _private prototype_ `FValueRuntimeRegistry();`
- L49 _private prototype_ `void RegisterBoundValueMapInitializer(UScriptStruct* ValueType, BoundValueMapConstructorFun Initializer);`
- L50 _private prototype_ `void RegisterUnboundValueMapInitializer(UScriptStruct* ValueType, UnboundValueMapConstructorFun Initializer);`
- L51 _private prototype_ `bool RegisterBouneValueMapTransformer(FName TransformerName, UScriptStruct* ValueType, FRawTransformerFunc TransformerFunc);`
- L52 _private prototype_ `bool RegisterUnboundValueMapTransformer(FName TransformerName, UScriptStruct* ValueType, FRawTransformerFunc TransformerFunc);`
- L55 _private prototype_ `static void Init();` — Initialize/destroy the global registry
- L56 _private prototype_ `static void Destroy();`
- L60 _private member_ `TMap<UScriptStruct*, BoundValueMapConstructorFun> BoundValueMapInitializers;` — A map of ValueType -> Bound Value Map constructors This is used for indirect construction when we have a UScriptStruct value type
- L61 _private member_ `mutable FRWLock BoundValueMapInitializerLock;`
- L65 _private member_ `TMap<UScriptStruct*, UnboundValueMapConstructorFun> UnboundValueMapInitializers;` — A map of ValueType -> Map constructors This is used for indirect construction when we have a UScriptStruct value type
- L66 _private member_ `mutable FRWLock UnboundValueMapInitializerLock;`
- L69 _private member_ `FValueTransformerMapPtr TransformerMap;` — A shared pointer to a map of transformer name -> transformer list (a transformer per value type)
- L70 _private member_ `mutable FRWLock TransformerMapLock;`
- L79 _function_ `template<class ValueType> inline void FValueRuntimeRegistry::RegisterBoundValueMapInitializer()`
- L90 _function_ `template<class ValueType> inline void FValueRuntimeRegistry::RegisterUnboundValueMapInitializer()`
- L99 _function_ `template<class TransformerSpecializationType> inline bool FValueRuntimeRegistry::RegisterValueTransformer()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAF_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L82 _function_ `` (scope `UE::UAF::FValueRuntimeRegistry::RegisterBoundValueMapInitializer`)
- L93 _function_ `` (scope `UE::UAF::FValueRuntimeRegistry::RegisterUnboundValueMapInitializer`)
- L101 _typedef_ `using TransformerCppType = typename TransformerSpecializationType::TransformerType;` (scope `UE::UAF::FValueRuntimeRegistry::RegisterValueTransformer`)
- L102 _typedef_ `using ValueType = typename TransformerSpecializationType::ValueType;` (scope `UE::UAF::FValueRuntimeRegistry::RegisterValueTransformer`)
- L114 _typedef_ `using FTransformBoundValueMapFunc = typename TransformerCppType::FTransformBoundValueMapFunc;` (scope `UE::UAF::FValueRuntimeRegistry::RegisterValueTransformer`) — Signature must match our transformer
- L131 _typedef_ `using FTransformUnboundValueMapFunc = typename TransformerCppType::FTransformUnboundValueMapFunc;` (scope `UE::UAF::FValueRuntimeRegistry::RegisterValueTransformer`) — Signature must match our transformer

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAF/ValueRuntime/ValueSpace.h` (Public)


#### enum `UE::UAF::EValueSpaceType`  
`enum class EValueSpaceType : uint16`  
_L12-33_
- desc: Encodes the possible spaces values can live in
- L15 _public enumerator_ `None = 0x0000` — Unknown value space
- L19 _public enumerator_ `Local = 0x0001` — Bone transforms: relative to their parent bone Everything else: normal space (no parent/child relationships)
- L23 _public enumerator_ `Component = 0x0002` — Bone transforms: relative to the owning component Everything else: normal space (no parent/child relationships)
- L28 _public enumerator_ `Mixed = 0x0003` — Bone transforms: rotations/translations/scales can be in individual spaces, @see EMixedSpaceFlags Only safe with uniform scale Everything else: normal space (no parent/child relationships)
- L32 _public enumerator_ `AI = 0x0004` — Values are in machine learning latent space Value types will dictate which space they are in

#### enum `UE::UAF::EMixedSpaceFlags`  
`enum class EMixedSpaceFlags : uint16`  
_L36-52_
- desc: Encodes the possible permutations of mixed spaces that bone transforms can live in
- L39 _public enumerator_ `None = 0x0000` — No mixed space, equivalent to Local Space
- L43 _public enumerator_ `MeshRotation = 0x0010` — Rotations are relative to the owning component Only safe with uniform scale
- L47 _public enumerator_ `MeshScale = 0x0020` — Scales are relative to the owning component Only safe with uniform scale
- L51 _public enumerator_ `RootRotation = 0x0040` — Rotations are relative to the root bone Only safe with uniform scale

#### class `UE::UAF::FValueSpace`  
`class FValueSpace`  
_L57-101_
- desc: Encapsulates the possible spaces that values can live in
- L61 _public prototype_ `FValueSpace() = default;` — Constructs an unknown space
- L64 _public prototype_ `explicit FValueSpace(EValueSpaceType Type, bool bIsAdditive = false);` — Constructs with the specified space type and additive flag
- L67 _public prototype_ `explicit FValueSpace(EMixedSpaceFlags Flags, bool bIsAdditive = false);` — Constructs a mixed space with the specified flags and additive flag
- L70 _public prototype_ `[[nodiscard]] EValueSpaceType GetType() const;` — Returns the value space type
- L73 _public prototype_ `void SetType(EValueSpaceType Type);` — Sets the value space type, preserving whether we are additive or not
- L76 _public prototype_ `[[nodiscard]] EMixedSpaceFlags GetMixedSpaceFlags() const;` — Returns the mixed space flags
- L79 _public prototype_ `void SetMixedSpaceFlags(EMixedSpaceFlags Flags);` — Sets the value space type to mixed along with the specified flags, preserving whether we are additive or not
- L82 _public prototype_ `[[nodiscard]] bool IsAdditive() const;` — Returns whether we are additive or not
- L85 _public prototype_ `void SetIsAdditive(bool bIsAdditive);` — Sets whether we are additive or not, preserving the type and mixed flags
- L88 _public prototype_ `bool operator==(FValueSpace Other) const;` — Equality operators
- L89 _public prototype_ `bool operator!=(FValueSpace Other) const;`
- L92 _public prototype_ `[[nodiscard]] FString ToString() const;` — Converts this value space into a string representation
- L95 _private member_ `static constexpr uint16 SPACE_CATEGORY_MASK = 0x000F;`
- L96 _private member_ `static constexpr uint16 MIXED_SPACE_FLAGS_MASK = 0x00F0;`
- L97 _private member_ `static constexpr uint16 IS_ADDITIVE_MASK = 0x8000;`
- L100 _private member_ `uint16 Packed = static_cast<uint16>(EValueSpaceType::None);` — Our internal value is opaque and packed
- L106 _function_ `inline FValueSpace::FValueSpace(EValueSpaceType Type, bool bIsAdditive) : Packed(static_cast<uint16>(Type) | (bIsAdditive ? IS_ADDITIVE_MASK : 0))`
- L111 _function_ `inline FValueSpace::FValueSpace(EMixedSpaceFlags Flags, bool bIsAdditive) : Packed(static_cast<uint16>(EValueSpaceType::Mixed) | static_cast<uint16>(Flags) | (bIsAdditive ? IS_ADDITIVE_MASK : 0))`
- L116 _function_ `inline EValueSpaceType FValueSpace::GetType() const`
- L121 _function_ `inline void FValueSpace::SetType(EValueSpaceType Type)`
- L127 _function_ `inline EMixedSpaceFlags FValueSpace::GetMixedSpaceFlags() const`
- L132 _function_ `inline void FValueSpace::SetMixedSpaceFlags(EMixedSpaceFlags Flags)`
- L138 _function_ `inline bool FValueSpace::IsAdditive() const`
- L143 _function_ `inline void FValueSpace::SetIsAdditive(bool bIsAdditive)`
- L149 _function_ `inline bool FValueSpace::operator==(FValueSpace Other) const`
- L154 _function_ `inline bool FValueSpace::operator!=(FValueSpace Other) const`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAF_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L54 _prototype_ `ENUM_CLASS_FLAGS(EMixedSpaceFlags);` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAFAssetInstance.h` (Public)


#### struct `FUAFAssetInstance`  
`struct FUAFAssetInstance`  
_L40-400_
- reflection: `USTRUCT()`
- desc: Base struct for instances of UAF assets
- L44 _public prototype_ `FUAFAssetInstance() = default;`
- L46 _public prototype_ `explicit FUAFAssetInstance(UScriptStruct* InScriptStruct);`
- L50 _public function_ `template<typename AssetType> const AssetType* GetAsset() const` — Get the asset that this instance represents
- L56 _public function_ `FName GetAssetName() const` — Safely get the name of the asset that this host provides
- L67 _public function_ `template<typename ValueType> EPropertyBagResult GetVariable(const FAnimNextVariableReference& InVariable, ValueType& OutResult) const` — Get a variable's value given its name, copying the value to OutResult. If the type does not match exactly then a conversion will be attempted. @param	InVariable			The variable to get the value of @param	OutResult			Result that will be filled if no errors occur @return see EPropertyBagResult
- L72 _public function_ `FUAFInstanceVariableData& GetVariables()`
- L73 _public function_ `const FUAFInstanceVariableData& GetVariables() const`
- L81 _public function_ `template<typename ValueType> EPropertyBagResult AccessVariable(const FAnimNextVariableReference& InVariable, TFunctionRef<void(ValueType&)> InFunction) const` — Access a variable's value given its name. Type must match strictly, no conversions are performed. @param	InVariable			The variable to get the value of @param	InFunction			Function that will be called if no errors occur @return see EPropertyBagResult
- L98 _public function_ `template<typename ValueType> EPropertyBagResult SetVariable(const FAnimNextVariableReference& InVariable, const ValueType& InNewValue) const` — Set a variable's value given a reference. If the type does not match exactly then a conversion will be attempted. @param	InVariable			The variable to set the value of @param	InNewValue			The value to set the variable to @return see EPropertyBagResult
- L109 _public function_ `EPropertyBagResult GetVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TArrayView<uint8> OutResult) const` — Get a variable's value given its name, copying the value to OutResult. If the type does not match exactly then a conversion will be attempted. @param	InVariable			The variable to get the value of @param	InType				The type to read as (conversions will be attempted) @param	OutResult			Raw byte view to receive the value @return see EPropertyBagResult
- L120 _public function_ `EPropertyBagResult SetVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InNewValue) const` — Set a variable's value given a reference. If the type does not match exactly then a conversion will be attempted. @param	InVariable			The variable to set the value of @param	InType				The type of the variable @param	InNewValue			The value to set the variable to @return see EPropertyBagResult
- L129 _public function_ `template<typename StructType> bool AccessVariablesStruct(TFunctionRef<void(StructType&)> InFunction) const` — Access the memory of the shared variable struct directly. @param	InFunction			Function called with a reference to the variable's struct @return true if the variables could be accessed. Variables can exist but be unable to be accessed if user overrides are set
- L141 _public function_ `bool AccessVariablesStruct(const UScriptStruct* InStruct, TFunctionRef<void(FStructView)> InFunction) const` — Access the memory of the shared variable struct directly. @param	InStruct			The variable struct type to access @param	InFunction			Function called with a reference to the variable's struct @return true if the variables could be accessed. Variables can exist but be unable to be accessed if user overrides are set
- L152 _public function_ `void ForEachVariablesStruct(TFunctionRef<void(FStructView)> InFunction) const` — Access the memory of the shared variable struct directly. @param	InFunction			Function called with a reference to the variable's struct @return true if the variables could be accessed. Variables can exist but be unable to be accessed if user overrides are set
- L160 _public function_ `template<typename ValueType> void GetAllVariablesOfType(TArray<FAnimNextVariableReference>& OutVariables) const` — Find references to all variables of the specified type @param	OutVariables		The variable references we found
- L169 _public prototype_ `bool ExecuteParameterlessFunction(const FAnimNextFunctionReference& InFunction, void* OutReturnValue, int32 ReturnValueSize);` — Execute a bound parameterless function and copy the return value into OutReturnValue. Resolves the function across the instance hierarchy by matching the function reference's owning asset, so functions on a parent System asset can be called from a child Graph instance. Returns true on success
- L174 _public function_ `template<typename ComponentType> [[nodiscard]] ComponentType& GetOrAddComponent()` — Returns a typed instance component, creating it lazily the first time it is queried. When querying for structs of a base type, existing derived types will be returned, rather than a new base struct created.
- L194 _public function_ `[[nodiscard]] FUAFAssetInstanceComponent& GetOrAddComponent(TSubScriptStructOf<FUAFAssetInstanceComponent> InScriptStruct)` — Returns an instance component of the requested type, creating it lazily the first time it is queried. When querying for structs of a base type, existing derived types will be returned, rather than a new base struct created.
- L214 _public function_ `template<typename ComponentType> ComponentType* TryGetComponent()` — Returns a typed instance component pointer if found or nullptr otherwise. When querying for structs of a base type, existing derived types will be returned.
- L223 _public function_ `template<typename ComponentType> const ComponentType* TryGetComponent() const` — Returns a typed instance component pointer if found or nullptr otherwise (const). When querying for structs of a base type, existing derived types will be returned.
- L231 _public prototype_ `FUAFAssetInstanceComponent* TryGetComponent(const UScriptStruct* InStruct);` — Returns a typed instance component pointer if found or nullptr otherwise. When querying for structs of a base type, existing derived types will be returned.
- L235 _public function_ `template<typename ComponentType> void ForEachComponent(TFunctionRef<bool(ComponentType&)> InFunction)` — Iterates all components, calling the supplied predicate. If the predicate returns false, iteration stops.
- L252 _public function_ `FUAFAssetInstance* GetHost() const` — Get the instance (graph, module etc.) that owns/hosts us
- L258 _public prototype_ `FAnimNextModuleInstance* GetRootInstance();` — Get the root module instance that owns us. Can be nullptr in some cases, such as automated tests.
- L260 _public function_ `uint64 GetUniqueId() const`
- L271 _public prototype_ `bool LayoutMatches(const FInstancedPropertyBag& InPropertyBag) const;` — Validate that the supplied property bag is of the same layout as this instance's variables
- L275 _public function_ `const UScriptStruct* GetScriptStruct() const` — Get the struct type of this instance
- L282 _public function_ `template<typename DerivedType> DerivedType* AsPtr()` — Returns this instance as the specified derived type, if our struct type is a child type
- L294 _public function_ `template<typename DerivedType> const DerivedType* AsPtr() const` — Returns this instance as the specified derived type, if our struct type is a child type
- L306 _public function_ `template<typename DerivedType> DerivedType& As()` — Returns this instance as the specified derived type. Asserts if our type is not a child type.
- L315 _public function_ `template<typename DerivedType> const DerivedType& As() const` — Returns this instance as the specified derived type. Asserts if our type is not a child type.
- L323 _public function_ `void SetDebugName(FName Name)` — Sets the debug name for the instance, used for tracing etc.
- L332 _protected prototype_ `void InitializeVariables(const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides = nullptr);` — Used during initialization. Creates variables or references those of the outer host and applies any overrides
- L336 _protected prototype_ `void MigrateVariables();` — Used during compilation, migrate all variables to new bags according to new defaults. Reapplies any cached overrides.
- L340 _protected prototype_ `void CopyDefaultComponents();` — Used on instance initialization to copy default components from the asset
- L343 _protected prototype_ `void BindDefaultComponents();` — Binds all components during initialization (once instance has been set up, variables created etc.)
- L346 _protected prototype_ `void ReleaseComponents();` — Releases any components this instance hosts
- L349 _protected function_ `void AccessVariablePropertyByIndex(int32 InIndex, TFunctionRef<void(const FProperty*, TArrayView<uint8>)> InFunction)` — Access the variable by index directly.
- L357 _protected member_ `TArray<TInstancedStruct<FUAFAssetInstanceComponent>> Components;` — `UPROPERTY(Transient)` — Array of components
- L361 _protected member_ `FUAFInstanceVariableData Variables;` — `UPROPERTY(Transient)` — Container for all variables and overrides
- L365 _protected member_ `TObjectPtr<const UObject> Asset;` — `UPROPERTY(Transient)` — Hard reference to the asset used to create this instance to ensure we can release it safely
- L369 _protected member_ `TObjectPtr<const UScriptStruct> ScriptStruct;` — `UPROPERTY(Transient)` — The struct type of this instance
- L372 _protected member_ `TWeakPtr<FUAFAssetInstance> HostInstance;` — The instance (graph, module etc.) that owns/hosts us
- L384 _protected function_ `FName GetDebugName() const`
- L396 _protected member_ `FName DebugName;`
- L397 _protected member_ `uint64 UniqueId;`
- L398 _protected member_ `volatile static int64 NextUniqueId;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API UAF_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace UAF` (scope `UE`)
- L132 _function_ `` (scope `FUAFAssetInstance::AccessVariablesStruct`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/UAFAssetInstanceComponent.h` (Public)


#### struct `FUAFAssetInstanceComponent`  
`struct FUAFAssetInstanceComponent`  
_L21-72_
- reflection: `USTRUCT(meta=(Hidden, Abstract))`
- desc: An asset instance component is attached and owned by an asset instance.
- L25 _public typedef_ `using ContainerType = FUAFAssetInstance;`
- L27 _public prototype_ `FUAFAssetInstanceComponent() = default;`
- L29 _public prototype_ `virtual ~FUAFAssetInstanceComponent() = default;`
- L33 _public function_ `FUAFAssetInstance* GetAssetInstancePtr()` — Returns the owning asset instance this component lives on Can return nullptr if an owning asset instance has not been created (such as a default component on an asset)
- L40 _public function_ `FUAFAssetInstance& GetAssetInstance()` — Returns the owning asset instance this component lives on Will assert if an owning asset instance has not been created (such as a default component on an asset)
- L48 _public function_ `const FUAFAssetInstance& GetAssetInstance() const` — Returns the owning asset instance this component lives on Will assert if an owning asset instance has not been created (such as a default component on an asset)
- L62 _private function_ `virtual void OnBindToInstance()` — Override point for derived components to hook into instance-binding. Called after the instance back-ptr is set: - When an instance first copies the default components from an asset - When an instance lazily creates a component on the fly
- L66 _protected member_ `FUAFAssetInstance* Instance = nullptr;` — The owning asset instance this component lives on

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFAssetInstanceComponent> : public TStructOpsTypeTraitsBase2<FUAFAssetInstanceComponent>`  
_L75-81_
- inherits: `TStructOpsTypeTraitsBase2<FUAFAssetInstanceComponent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L78-80_

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAF_API`
- L16 _macro_ `#define DECLARE_UAF_ASSET_INSTANCE_COMPONENT() \` — Macro used to provide basic RTTI via UScriptStruct for asset instance components
- L79 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anona5cb9fad0103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Variables/AnimNextSharedVariables.h` (Public)


#### class `UUAFSharedVariables`  
`class UUAFSharedVariables : public UUAFRigVMAsset`  
_L26-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UUAFRigVMAsset`
- desc: Shared variables are just bundles of variables and their default values
- L31 _public prototype_ `UUAFSharedVariables(const FObjectInitializer& ObjectInitializer);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAF_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Variables/AnimNextSoftVariableReference.h` (Public)


#### struct `FAnimNextSoftVariableReference`  
`struct FAnimNextSoftVariableReference`  
_L13-103_
- desc: A soft reference to an AnimNext variable
- L15 _public prototype_ `FAnimNextSoftVariableReference() = default;`
- L18 _public function_ `static FAnimNextSoftVariableReference FromName(FName InName, const FSoftObjectPath& InSoftObjectPath)` — Construct a soft reference from a FName
- L24 _public function_ `static FAnimNextSoftVariableReference FromNameAndType(FName InName, const FSoftObjectPath& InSoftObjectPath, FAnimNextParamType InType)`
- L30 _public function_ `explicit FAnimNextSoftVariableReference(const FAnimNextVariableReference& VariableReference) : Name(VariableReference.GetName()), SoftObjectPath(VariableReference.GetObject())`
- L36 _public function_ `FName GetName() const` — Get the name of the variable
- L42 _public function_ `const FSoftObjectPath& GetSoftObjectPath() const` — Get the asset or struct that the variable reference is contained in
- L48 _public function_ `bool IsNone() const` — Check whether this can ever refer to a valid variable
- L54 _public function_ `void Reset()` — Set this reference to None
- L62 _public function_ `bool HasType() const` — Whether parameter type was set
- L68 _public function_ `FAnimNextParamType GetType() const` — Return reference parameter type, only when set otherwise will assert (use HasType for checking validity)
- L73 _public function_ `bool operator==(const FAnimNextSoftVariableReference& InOther) const`
- L78 _public function_ `bool operator!=(const FAnimNextSoftVariableReference& InOther) const`
- L88 _private function_ `FAnimNextSoftVariableReference(FName InName, const FSoftObjectPath& InSoftObjectPath, const TOptional<FAnimNextParamType> InType = TOptional<FAnimNextParamType>()) : Name(InName) , SoftObjectPath(InSoftObjectPath) , OptionalType(InType)`
- L96 _private member_ `FName Name;` — The name of the variable
- L99 _private member_ `FSoftObjectPath SoftObjectPath;` — The asset or struct that the variable reference is contained in
- L102 _private member_ `TOptional<FAnimNextParamType> OptionalType;` — (Expected) type when used for searching references

#### Free symbols / members of external scopes

- L83 _function_ `friend uint32 GetTypeHash(const FAnimNextSoftVariableReference& InKey)`

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Variables/AnimNextVariableReference.h` (Public)


#### struct `FAnimNextVariableReference`  
`struct FAnimNextVariableReference`  
_L26-146_
- reflection: `USTRUCT(BlueprintType)`
- desc: A reference to a specific variable (UAnimNextVariableEntry) on UUAFRigVMAsset derived class or FProperty on UScriptStruct (NativeSharedVariables).
- L30 _public prototype_ `FAnimNextVariableReference() = default;`
- L36 _public prototype_ `static FAnimNextVariableReference FromProperty(const FProperty* InProperty, const UScriptStruct* InStruct);` — Construct a reference to a struct variable.
- L39 _public prototype_ `static FAnimNextVariableReference FromName(FName InName, const UObject* InObject);` — Construct a reference to an asset/struct variable using its name.
- L43 _public prototype_ `static FAnimNextVariableReference FromNameAndGuid(FName InName, FGuid InGuid, const UObject* InObject);` — Construct a reference to an asset/struct variable using its guid and name. (Editor only)
- L45 _public prototype_ `bool Serialize(FArchive& Ar);`
- L46 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L49 _public prototype_ `bool Identical(const FAnimNextVariableReference* Other, uint32 PortFlags) const;`
- L53 _public function_ `explicit FAnimNextVariableReference(FName InName) : Name(InName)` — `UE_DEPRECATED(5.6, "Constructor should no longer be used, please use constructor that takes an asset or a struct")` — Legacy constructor from an FName
- L59 _public prototype_ `explicit FAnimNextVariableReference(FName InName, const UUAFRigVMAsset* InAsset);` — `UE_DEPRECATED(5.8, "FAnimNextVariableReference constructor will become private please use FAnimNextVariableReference::From* APIs instead")`
- L62 _public prototype_ `explicit FAnimNextVariableReference(FName InName, const UScriptStruct* InStruct);` — `UE_DEPRECATED(5.8, "FAnimNextVariableReference constructor will become private please use FAnimNextVariableReference::From* APIs instead")`
- L64 _public prototype_ `explicit FAnimNextVariableReference(const FAnimNextSoftVariableReference& InSoftReference);`
- L67 _public function_ `FName GetName() const` — Get the name of the variable
- L73 _public function_ `TObjectPtr<const UObject> GetObject() const` — Get the asset or struct that the variable reference is contained in
- L79 _public function_ `bool IsNone() const` — Check whether this can ever refer to a valid variable
- L86 _public function_ `void Reset()` — Set this reference to None
- L97 _public prototype_ `bool IsValid() const;` — Check whether refers to a valid variable
- L99 _public function_ `bool operator==(const FAnimNextVariableReference& InOther) const`
- L105 _public function_ `bool operator!=(const FAnimNextVariableReference& InOther) const`
- L117 _public prototype_ `const FProperty* ResolveProperty() const;` — Get the property associated with this variable. Returns null for invalid variables.
- L120 _private prototype_ `FAnimNextVariableReference(FName InName, FGuid InGuid, const UObject* InObject);`
- L123 _private prototype_ `static void ValidateVariableNameAndGuid(FName& InOutName, FGuid& InOutGuid, const UObject* InSourceObject, const FString& OwnerName);`
- L129 _private member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = Variable)` — The name of the variable
- L134 _private member_ `TObjectPtr<const UObject> Object;` — `UPROPERTY(EditAnywhere, Category = Variable)` — The asset or struct that the variable reference is contained in Note: Only deprecated paths allow this to be empty, so all variables in a context will be searched
- L137 _private member_ `mutable TFieldPath<const FProperty> CachedProperty;` — Cached property used for resolving in GetProperty
- L142 _private member_ `FGuid CachedGuid;` — `UPROPERTY(VisibleAnywhere, Category = Variable)` — GUID of the variable

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextVariableReference> : public TStructOpsTypeTraitsBase2<FAnimNextVariableReference>`  
_L149-159_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextVariableReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L153-157_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L19 _variable_ `static const FString InternalVariablePrefix(TEXT("__In` (scope `UE::UAF`)
- L21 _function_ `static bool IsInternalVariableName(FName InVariableName)` (scope `UE::UAF`) — Whether the variable is a function internal one
- L110 _function_ `friend uint32 GetTypeHash(const FAnimNextVariableReference& InKey)`
- L154 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon2338618a0103`)
- L155 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon2338618a0103`)
- L156 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon2338618a0103`)

### `Plugins/Experimental/UAF/UAF/Source/UAF/Public/Variables/UAFInstanceVariableData.h` (Public)


#### struct `FUAFInstanceVariableData`  
`struct FUAFInstanceVariableData`  
_L38-163_
- reflection: `USTRUCT()`
- L42 _public prototype_ `FUAFInstanceVariableData() = default;`
- L45 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);` — GC support
- L59 _private prototype_ `void Initialize(const FUAFAssetInstance& InHostInstance, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides);` — Initialize from a host's asset and its references
- L61 _private prototype_ `void AddVariablesContainerForAsset(const UUAFRigVMAsset* InAsset, const FUAFAssetInstance& InInstance, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides);`
- L62 _private prototype_ `void AddVariablesContainerForStruct(const UScriptStruct* InStruct, const FUAFAssetInstance& InInstance, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides);`
- L63 _private prototype_ `void AddVariablesContainerForRigVMAsset(const TScriptInterface<const IRigVMRuntimeAssetInterface>& InRigVMAsset, const FUAFAssetInstance& InInstance, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides);`
- L66 _private prototype_ `void Reset();` — Reset to the default state
- L69 _private prototype_ `void RebuildNameMaps();` — Helper function used during initialization & migration
- L73 _private prototype_ `void Migrate(const FUAFAssetInstance& InHostInstance);` — Used during compilation, migrate all variables to new bags according to new defaults.
- L77 _private prototype_ `void ResolveOverrides();` — Resolve any VariableOverrides to FUAFInstanceVariableContainer::ResolvedOverrides
- L80 _private prototype_ `EPropertyBagResult GetVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TArrayView<uint8> OutResult) const;` — Gets the value of the specified variable. If the type does not match exactly then a conversion will be attempted.
- L83 _private prototype_ `EPropertyBagResult AccessVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TArrayView<uint8>& OutResult) const;` — Access the memory of the variable directly. Type must match strictly, no conversions are performed.
- L86 _private prototype_ `EPropertyBagResult SetVariable(const FAnimNextVariableReference& InVariable, const FAnimNextParamType& InType, TConstArrayView<uint8> InNewValue) const;` — Sets the value of the specified variable. If the type does not match exactly then a conversion will be attempted.
- L90 _private function_ `template<typename StructType> bool AccessVariablesStruct(TFunctionRef<void(StructType&)> InFunction) const` — Access the memory of the shared variable struct directly.
- L100 _private prototype_ `bool AccessVariablesStructInternal(const UScriptStruct* InStruct, TFunctionRef<void(FStructView)> InFunction) const;` — Access the memory of the shared variable container directly. @return false if the struct was not present in our set of variable containers
- L103 _private prototype_ `void ForEachVariablesStructInternal(TFunctionRef<void(FStructView)> InFunction) const;` — Access the memory of each shared variable struct directly.
- L106 _private prototype_ `void GetAllVariablesOfType(const FAnimNextParamType& InType, TArray<FAnimNextVariableReference>& OutVariables) const;` — Find references to all variables of the specified type
- L109 _private prototype_ `void ForEachVariable(TFunctionRef<bool(FName, const FAnimNextParamType&, int32)> InFunction) const;` — Iterate over all variables calling InFunction
- L112 _private prototype_ `void AccessVariablePropertyByIndex(int32 InIndex, TFunctionRef<void(const FProperty*, TArrayView<uint8>)> InFunction);` — Access the variable by index directly.
- L115 _private prototype_ `EPropertyBagResult AccessVariableProperty(const FAnimNextVariableReference& InVariable, TFunctionRef<void(const FProperty*, TArrayView<uint8>)> InFunction);` — Access a variable via a FAnimNextVariableReference
- L118 _private member_ `TArray<TSharedRef<FUAFInstanceVariableContainer>> OwnedVariableContainers;` — Variable containers owned by the containing instance
- L121 _private member_ `TArray<TWeakPtr<FUAFInstanceVariableContainer>> InternalSharedVariableContainers;` — User variables used to operate the graph/module (i.e. does not include variables overriden at this level in the instance hierarchy)
- L124 _private member_ `TArray<TWeakPtr<FUAFInstanceVariableContainer>> AllSharedVariableContainers;` — All shared variables at this scope in the instance hierarchy
- L128 _private member_ `TMap<TObjectPtr<const UObject>, int32> AllSharedVariableContainersMap;` — `UPROPERTY(Transient)` — Map from asset/struct to index in SharedVariableSets
- L145 _private prototype_ `const FVariableMapping* FindMapping(const FAnimNextVariableReference& InVariable) const;` — Helper function for variable access
- L148 _private member_ `TMap<FName, FVariableMapping> LegacyVariableNameMap;` — Legacy name-based mappings of variables
- L151 _private member_ `TMap<FAnimNextVariableReference, FVariableMapping> VariablesMap;` — Map of variable ref -> FVariableMapping
- L154 _private member_ `int32 NumAllVariables = 0;` — Total count of all variables
- L157 _private member_ `int32 NumInternalVariables = 0;` — Total count of all variables used to operate the graph/module
- L161 _private member_ `bool bHasBeenInitialized = false;` — Whether Initialize() has been called at least once

#### struct `FUAFInstanceVariableData::FVariableMapping`  
`struct FVariableMapping`  
_L130-142_
- L132 _public function_ `FVariableMapping(uint16 InAllSharedVariableContainersIndex, uint16 InVariableIndex) : AllSharedVariableContainersIndex(InAllSharedVariableContainersIndex) , VariableIndex(InVariableIndex)`
- L138 _public member_ `uint16 AllSharedVariableContainersIndex = 0;` — AllSharedVariableContainers index
- L141 _public member_ `uint16 VariableIndex = 0;` — Index into the FUAFInstanceVariableContainer property bag/struct/overrides

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFInstanceVariableData> : public TStructOpsTypeTraitsBase2<FUAFInstanceVariableData>`  
_L166-172_
- inherits: `TStructOpsTypeTraitsBase2<FUAFInstanceVariableData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L169-171_

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace Tests` (scope `UE::UAF`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UAF` (scope `UE`)
- L93 _function_ `` (scope `FUAFInstanceVariableData::AccessVariablesStruct`)
- L170 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon811ef1420203`)
