# Plugins / UAFAnimGraph

- module root: `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph`
- headers: 183; symbols: 3253
- symbol kinds: class=12, delegate=13, enum=35, enumerator=97, externvar=3, function=462, macro=145, member=796, namespace=341, prototype=942, struct=338, typedef=68, union=1
- PrivateDependencyModuleNames: AssetRegistry, RigVMDeveloper, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, HierarchyTableAnimationRuntime, HierarchyTableRuntime, RigVM, TraceLog, UAF

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/AnimNextAnimGraphSettings.h` (Internal)


#### class `UAnimNextAnimGraphSettings`  
`class UAnimNextAnimGraphSettings : public UObject`  
_L17-25_
- reflection: `UCLASS(MinimalAPI, Config=AnimNextAnimGraph, defaultconfig)`
- inherits: `UObject`
- L24 _public prototype_ `static TArray<UClass*> GetAllowedAssetClasses();` — `UFUNCTION()` — Gets all allowed asset classes that users can reference that map via GetGraphFromObject

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Factory/AnimGraphBuilderContext.h` (Internal)


#### struct `UE::UAF::FAnimGraphBuilderContext`  
`struct FAnimGraphBuilderContext`  
_L22-49_
- L29 _private prototype_ `const UUAFAnimGraph* Build();` — Builds a graph using the populated TraitWriter and VariableStructs
- L33 _public member_ `FAnimNextEntryPointHandle RootTraitHandle;` — Root trait handle
- L36 _public member_ `FTraitWriter TraitWriter;` — Trait writer used to build the graph
- L39 _public member_ `TArray<const UScriptStruct*> VariableStructs;` — Variable structs used to communicate with the graph
- L42 _public member_ `TArray<const UScriptStruct*> ComponentStructs;` — Component structs used to communicate with the graph instance
- L45 _public member_ `TSet<TScriptInterface<const IRigVMRuntimeAssetInterface>> ReferencedVariableRigVMAssets;` — All the IRigVMRuntimeAssetInterface whose variables we will reference/instance at runtime
- L48 _public member_ `TSet<TObjectPtr<const UUAFRigVMAsset>> ReferencedVariableAssets;` — All the assets whose variables we will reference/instance at runtime

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/AnimGraph/AnimNode_AnimNextGraph.h` (Internal)


#### struct `FAnimNode_AnimNextGraph`  
`struct FAnimNode_AnimNextGraph : public FAnimNode_CustomProperty`  
_L16-68_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_CustomProperty`
- desc: Animation node that allows a AnimNextGraph output to be used in an animation graph
- L20 _public prototype_ `FAnimNode_AnimNextGraph();`
- L23 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;` — FAnimNode_Base interface
- L24 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L25 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L26 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L27 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L28 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext & Output) override;`
- L29 _public function_ `virtual int32 GetLODThreshold() const override`
- L31 _public prototype_ `virtual void InitializeProperties(const UObject* InSourceInstance, UClass* InTargetClass) override;`
- L32 _public prototype_ `virtual void PropagateInputProperties(const UObject* InSourceInstance) override;`
- L36 _private prototype_ `virtual void HandleObjectsReinstanced_Impl(UObject* InSourceObject, UObject* InTargetObject, const TMap<UObject*, UObject*>& OldToNewInstanceMap) override;`
- L42 _private member_ `FPoseLink SourceLink;` — `UPROPERTY(EditAnywhere, Category = Links, meta = (DisplayName = "Source"))` — The input pose we will pass to the graph
- L45 _private member_ `TObjectPtr<UUAFAnimGraph> AnimationGraph;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))`
- L48 _private member_ `TSharedPtr<FAnimNextGraphInstance> GraphInstance;` — Our graph instance, we own it
- L57 _private member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, Category = Performance, meta = (DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L60 _protected function_ `virtual UClass* GetTargetClass() const override`
- L64 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L65 _public prototype_ `void AddStructReferencedObjects(class FReferenceCollector& Collector);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_AnimNextGraph> : public TStructOpsTypeTraitsBase2<FAnimNode_AnimNextGraph>`  
_L71-79_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_AnimNextGraph>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L74-78_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L75 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anond2ed869c0103`)
- L76 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anond2ed869c0103`)
- L77 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anond2ed869c0103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/AnimNextGraphContextData.h` (Internal)


#### struct `FAnimNextGraphContextData`  
`struct FAnimNextGraphContextData : public FUAFAssetContextData`  
_L16-32_
- reflection: `USTRUCT()`
- inherits: `FUAFAssetContextData`
- L20 _public prototype_ `FAnimNextGraphContextData() = default;`
- L22 _public function_ `FAnimNextGraphContextData(FAnimNextGraphInstance& InInstance, FName InEventName, float InDeltaTime) : FUAFAssetContextData(InInstance, InEventName, InDeltaTime)`
- L27 _public function_ `const FAnimNextGraphInstance& GetGraphInstance() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/AnimNextGraphLatentPropertiesContextData.h` (Internal)


#### struct `FAnimNextGraphLatentPropertiesContextData`  
`struct FAnimNextGraphLatentPropertiesContextData : public FAnimNextGraphContextData`  
_L18-46_
- reflection: `USTRUCT()`
- inherits: `FAnimNextGraphContextData`
- L22 _public prototype_ `FAnimNextGraphLatentPropertiesContextData() = default;`
- L24 _public function_ `FAnimNextGraphLatentPropertiesContextData(FAnimNextGraphInstance& InInstance, const TConstArrayView<UE::UAF::FLatentPropertyHandle>& InLatentHandles, void* InDestinationBasePtr, float InDeltaTime, bool bInIsFrozen, bool bInJustBecameRelevant) : FAnimNextGraphContextData(InInstance, FRigUnit_AnimNextShimRoot::EventName, InDeltaTime) , LatentHandles(InLatentHandles) , DestinationBasePtr(InDestinationBasePtr) , bIsFrozen(bInIsFrozen) , bJustBecameRelevant(bInJustBecameRelevant)`
- L33 _public function_ `const TConstArrayView<UE::UAF::FLatentPropertyHandle>& GetLatentHandles() const`
- L34 _public function_ `void* GetDestinationBasePtr() const`
- L35 _public function_ `bool IsFrozen() const`
- L36 _public function_ `bool JustBecameRelevant() const`
- L39 _private member_ `TConstArrayView<UE::UAF::FLatentPropertyHandle> LatentHandles;`
- L40 _private member_ `void* DestinationBasePtr = nullptr;`
- L41 _private member_ `bool bIsFrozen = false;`
- L42 _private member_ `bool bJustBecameRelevant = false;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/AnimNextModuleAnimGraphComponent.h` (Internal)


#### struct `FAnimNextModuleAnimGraphComponent`  
`struct FAnimNextModuleAnimGraphComponent : public FUAFModuleInstanceComponent`  
_L21-35_
- reflection: `USTRUCT()`
- inherits: `FUAFModuleInstanceComponent`
- desc: Module component that owns/allocates/release all animation graph instances on a module
- L24 _public prototype_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT() TWeakPtr<FAnimNextGraphInstance> AllocateInstance(const UUAFAnimGraph* InAnimationGraph, const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides);`
- L28 _public prototype_ `void ReleaseInstance(TWeakPtr<FAnimNextGraphInstance> InInstance);`
- L30 _public prototype_ `void AddStructReferencedObjects(class FReferenceCollector& Collector);`
- L34 _private member_ `TArray<TSharedPtr<FAnimNextGraphInstance>> GraphInstances;` — All the owned graph instances for the module

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextModuleAnimGraphComponent> : public TStructOpsTypeTraitsBase2<FAnimNextModuleAnimGraphComponent>`  
_L38-44_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextModuleAnimGraphComponent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L41-43_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L42 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon08cddc8a0103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigDecorator_AnimNextCppTrait.h` (Internal)


#### struct `FRigDecorator_AnimNextCppDecorator`  
`struct FRigDecorator_AnimNextCppDecorator : public FRigVMTrait`  
_L18-38_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRigVMTrait`
- desc: AnimNext RigDecorator for all C++ traits. The trait shared data UScriptStruct determines which properties are exposed.
- L24 _public member_ `TObjectPtr<UScriptStruct> DecoratorSharedDataStruct = nullptr;` — `UPROPERTY(meta = (Hidden))` — The struct the trait exposes with its shared data. Each one of its properties will be added as a pin.
- L27 _public prototype_ `virtual void GetProgrammaticPins(URigVMController* InController, int32 InParentPinIndex, const URigVMPin* InTraitPin, const FString& InDefaultValue, struct FRigVMPinInfoArray& OutPinArray) const override;`
- L29 _public function_ `virtual UScriptStruct* GetTraitSharedDataStruct() const override`
- L34 _public prototype_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`
- L36 _public prototype_ `const UE::UAF::FTrait* GetTrait() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigUnit_AnimNextGraphEvaluator.h` (Internal)


#### struct `FRigUnit_AnimNextGraphEvaluator`  
`struct FRigUnit_AnimNextGraphEvaluator : public FRigUnit_AnimNextBase`  
_L20-36_
- reflection: `USTRUCT(meta=(Hidden, DisplayName="Animation Runtime Output", Category="Events", NodeColor="1, 0, 0"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Animation graph evaluator This node is only used at runtime. It performs the animation graph update and evaluation through the data provided in the execution context. It also holds all latent/lazy pins that the graph references in the editor.
- L26 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(meta = (Input, Output))` — The execute context used for the execution flow
- L28 _public prototype_ `static void StaticExecute(FRigVMExtendedExecuteContext& RigVMExecuteContext, FRigVMMemoryHandleArray RigVMMemoryHandles, FRigVMPredicateBranchArray RigVMBranches);`
- L32 _public prototype_ `static void RegisterExecuteMethod(const FAnimNextGraphEvaluatorExecuteDefinition& ExecuteDefinition);` — The graph evaluator entry point is dynamically registered because it can have any number of latent pins with their own name/type RigVM requires a mapping between argument list and method name and so we register things manually
- L35 _public prototype_ `static const FAnimNextGraphEvaluatorExecuteDefinition* FindExecuteMethod(uint32 ExecuteMethodHash);` — Returns an existing execute method, if found. Otherwise, nullptr is returned.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigUnit_AnimNextGraphRoot.h` (Internal)


#### struct `FRigUnit_AnimNextGraphRoot`  
`struct FRigUnit_AnimNextGraphRoot : public FRigUnit_AnimNextBase`  
_L20-49_
- reflection: `USTRUCT(meta=(Hidden, DisplayName="Animation Output", Category="Events", NodeColor="1, 0, 0", Keywords="Root,Output"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Animation graph output This is a synthetic node that represents the entry point for an animation graph for RigVM. The graph editor will see this as the graph output in which to hook up the first animation node to evaluate. This node isn't used at runtime.
- L24 _public prototype_ `RIGVM_METHOD() void DummyExecute();`
- L27 _public function_ `virtual FName GetEventName() const override`
- L28 _public function_ `virtual FString GetUnitSubTitle() const override`
- L29 _public function_ `virtual bool CanOnlyExistOnce() const override`
- L33 _public member_ `FAnimNextTraitHandle Result;` — `UPROPERTY(EditAnywhere, Category = Result, meta = (Input, HideSubPins))` — The execution result
- L38 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY()` — In order for this node to be considered an executable RigUnit, it needs a pin to derive from FRigVMExecuteContext We keep it hidden it since we don't need it
- L42 _public member_ `FName EntryPoint = DefaultEntryPoint;` — `UPROPERTY(VisibleAnywhere, Category = Result, meta = (Hidden))` — The name of the entry point
- L45 _public member_ `static FName EventName;` — This unit is our graph entry point, it needs an event so we can call it
- L48 _public member_ `static FName DefaultEntryPoint;` — Default entry point name

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigUnit_AnimNextRunAnimationGraph_v1.h` (Internal)


#### struct `FAnimNextRunGraphWorkData_v1`  
`struct FAnimNextRunGraphWorkData_v1`  
_L16-22_
- reflection: `USTRUCT()`
- L21 _public member_ `TWeakPtr<FAnimNextGraphInstance> WeakInstance;` — Weak ptr to the instance we run (ownership is with the module component)

#### struct `FRigUnit_AnimNextRunAnimationGraph_v1`  
`struct FRigUnit_AnimNextRunAnimationGraph_v1 : public FRigUnit_AnimNextBase`  
_L26-63_
- reflection: `USTRUCT(meta=(Hidden, DisplayName="Run Graph (Deprecated)", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Trait,Stack"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Runs an animation graph
- L30 _public prototype_ `RIGVM_METHOD() void Execute();`
- L35 _public member_ `TObjectPtr<UUAFAnimGraph> Graph;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input, ExportAsReference="true"))` — Graph to run
- L39 _public member_ `FAnimNextAnimGraph Instance;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input, Output))` — Instance used to hold graph state
- L43 _public member_ `int32 LOD = -1;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — LOD to run the graph at. If this is -1 then the reference pose's source LOD will be used
- L47 _public member_ `FAnimNextGraphReferencePose ReferencePose;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Reference pose for the graph
- L51 _public member_ `FAnimNextVariableOverridesCollection Overrides;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Variable overrides to be applied to subgraphs
- L55 _public member_ `FAnimNextGraphLODPose Result;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — Pose result
- L58 _public member_ `FAnimNextRunGraphWorkData_v1 WorkData;` — `UPROPERTY(Transient)`
- L62 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigUnit_AnimNextRunAnimationGraph_v2.h` (Internal)


#### struct `FAnimNextRunGraphWorkData_v2`  
`struct FAnimNextRunGraphWorkData_v2`  
_L16-26_
- reflection: `USTRUCT()`
- L21 _public member_ `TWeakPtr<FAnimNextGraphInstance> WeakHost;` — Weak ptr to the instance we run (ownership is with the module component)
- L25 _public member_ `FAnimNextVariableReference InjectedGraphReference;` — `UPROPERTY(transient)` — Graph we are injecting into the host

#### struct `FRigUnit_AnimNextRunAnimationGraph_v2`  
`struct FRigUnit_AnimNextRunAnimationGraph_v2 : public FRigUnit_AnimNextBase`  
_L30-73_
- reflection: `USTRUCT(meta=(DisplayName="Run Graph", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="Trait,Stack", RequiredComponents="AnimNextModuleInjectionComponent"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Runs an animation graph
- L34 _public prototype_ `RIGVM_METHOD() void Execute();`
- L37 _public prototype_ `static const UUAFAnimGraph* GetHostGraphToRun(FAnimNextExecuteContext& InExecuteContext);`
- L41 _public member_ `FAnimNextAnimGraph Graph;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input, ShowOnlyInnerProperties, ExportAsReference="true"))` — The graph to run
- L45 _public member_ `int32 LOD = -1;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — LOD to run the graph at. If this is -1 then the reference pose's source LOD will be used
- L49 _public member_ `FAnimNextGraphReferencePose ReferencePose;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — Reference pose for the graph
- L53 _public member_ `FAnimNextVariableOverridesCollection Overrides;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — Variable overrides to be applied to subgraphs
- L57 _public member_ `FName AttributeSet;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — The name of the attribute set to execute with, if 'None' will include everything
- L61 _public member_ `FAnimNextGraphLODPose Result;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Output))` — Pose result
- L65 _public member_ `FAnimNextRunGraphWorkData_v2 WorkData;` — `UPROPERTY(transient)` — Internal work data
- L69 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result
- L71 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigUnit_AnimNextShimRoot.h` (Internal)


#### struct `FRigUnit_AnimNextShimRoot`  
`struct FRigUnit_AnimNextShimRoot : public FRigUnit_AnimNextBase`  
_L18-36_
- reflection: `USTRUCT(meta=(Hidden, DisplayName="Animation Output Shim", Category="Events", NodeColor="1, 0, 0", Keywords="Root,Output"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Animation graph output This is a synthetic node that represents the entry point for an animation graph for RigVM. The graph editor will not see this node. It is added during compilation as a shim to start the evaluation process. This node is only used at runtime.
- L22 _public prototype_ `RIGVM_METHOD() void Execute();`
- L25 _public function_ `virtual FName GetEventName() const override`
- L26 _public function_ `virtual bool CanOnlyExistOnce() const override`
- L32 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(meta = (Output))` — In order for this node to be considered an executable RigUnit, it needs a pin to derive from FRigVMExecuteContext Although the anim graph flows from left to right with the graph output being on the right hand side with a single input as the final output, RigVM execution flows from outputs to inputs and as such an entry point has a single output.
- L35 _public member_ `static FName EventName;` — This unit is our graph entry point, it needs an event so we can call it

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigUnit_AnimNextTraitStack.h` (Internal)


#### struct `FRigUnit_AnimNextTraitStack`  
`struct FRigUnit_AnimNextTraitStack : public FRigUnit_AnimNextBase`  
_L20-30_
- reflection: `USTRUCT(meta=(DisplayName="Trait Stack", Category="Animation", NodeColor="0, 1, 1", Keywords="Trait,Stack"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Animation graph trait container It contains a stack of traits which are used during compilation to output a cooked graph This node is synthetic and only present in the editor. During compilation, it is disconnected from the graph and replaced by the cooked trait metadata.
- L24 _public prototype_ `RIGVM_METHOD() void Execute();`
- L29 _public member_ `FAnimNextTraitHandle Result;` — `UPROPERTY(EditAnywhere, Category = Result, meta = (Output))` — The execution result

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/RigUnit_UAFRunAsset.h` (Internal)


#### struct `FUAFRunAssetWorkData`  
`struct FUAFRunAssetWorkData`  
_L17-27_
- reflection: `USTRUCT()`
- L22 _public member_ `TWeakPtr<FAnimNextGraphInstance> WeakHost;` — Weak ptr to the instance we run (ownership is with the module component)
- L26 _public member_ `FAnimNextVariableReference InjectedGraphReference;` — `UPROPERTY(transient)` — Graph we are injecting into the host

#### struct `FRigUnit_UAFRunAsset`  
`struct FRigUnit_UAFRunAsset : public FRigUnit_AnimNextBase`  
_L31-63_
- reflection: `USTRUCT(meta=(DisplayName="Run Asset", Category="Anim", NodeColor="0, 1, 1", Keywords="Trait,Stack", RequiredComponents="AnimNextModuleInjectionComponent"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Runs a UAF asset to generate an output value
- L35 _public prototype_ `RIGVM_METHOD() void Execute();`
- L38 _public prototype_ `static const UUAFAnimGraph* GetHostGraphToRun(FAnimNextExecuteContext& InExecuteContext);`
- L42 _public member_ `FAnimNextAnimGraph Graph;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input, ShowOnlyInnerProperties, ExportAsReference="true"))` — The graph to run
- L46 _public member_ `FAnimNextVariableOverridesCollection Overrides;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — Variable overrides to be applied to subgraphs
- L50 _public member_ `FName AttributeSet;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Input))` — The name of the attribute set to execute with, if 'None' will include everything
- L54 _public member_ `FUAFValueBundle Result;` — `UPROPERTY(EditAnywhere, Category = "Run", meta = (Output))` — Result value
- L58 _public member_ `FUAFRunAssetWorkData WorkData;` — `UPROPERTY(transient)` — Internal work data
- L62 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/VirtualValueBundle_ExternalGraph.h` (Internal)


#### struct `UE::UAF::FVirtualValueBundle_ExternalGraph`  
`struct FVirtualValueBundle_ExternalGraph : public IVirtualValueBundle`  
_L13-28_
- inherits: `IVirtualValueBundle`
- L15 _public function_ `explicit FVirtualValueBundle_ExternalGraph(const FWeakAnimGraphReference& InGraphReference) : WeakGraphReference(InGraphReference)`
- L19 _public function_ `explicit FVirtualValueBundle_ExternalGraph(const FAnimGraphReference& InGraphReference) : WeakGraphReference(InGraphReference)`
- L25 _private prototype_ `virtual const FWeakAnimGraphReference* GetAnimGraphReference() const override;` — IVirtualValueBundle interface
- L27 _private member_ `FWeakAnimGraphReference WeakGraphReference;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/VirtualValueBundle_InlineGraph.h` (Internal)


#### struct `UE::UAF::FVirtualValueBundle_InlineGraph`  
`struct FVirtualValueBundle_InlineGraph : public IVirtualValueBundle`  
_L14-25_
- inherits: `IVirtualValueBundle`
- L16 _public function_ `explicit FVirtualValueBundle_InlineGraph(const FTraitPtr& InTraitPtr) : TraitPtr(InTraitPtr)`
- L22 _private prototype_ `virtual const FTraitPtr* GetInlineGraph() const override;` — IVirtualValueBundle interface
- L24 _private member_ `FTraitPtr TraitPtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Graph/VirtualValueBundle_ValueBundle.h` (Internal)


#### struct `UE::UAF::FVirtualValueBundle_ValueBundle`  
`struct FVirtualValueBundle_ValueBundle : public IVirtualValueBundle`  
_L15-40_
- inherits: `IVirtualValueBundle`
- L17 _public function_ `explicit FVirtualValueBundle_ValueBundle(const FAnimNextGraphLODPose& InPose) : Pose(InPose)`
- L21 _public function_ `explicit FVirtualValueBundle_ValueBundle(FAnimNextGraphLODPose&& InPose) : Pose(MoveTemp(InPose))`
- L25 _public function_ `explicit FVirtualValueBundle_ValueBundle(const FValueBundleHeap& InValueBundle) : ValueBundle(InValueBundle)`
- L29 _public function_ `explicit FVirtualValueBundle_ValueBundle(FValueBundleHeap&& InValueBundle) : ValueBundle(MoveTemp(InValueBundle))`
- L34 _public prototype_ `virtual const FAnimNextGraphLODPose* GetLODPose() const override;` — IVirtualValueBundle interface
- L35 _public prototype_ `virtual const FValueBundleHeap* GetValueBundle() const override;`
- L38 _private member_ `FAnimNextGraphLODPose Pose;`
- L39 _private member_ `FValueBundleHeap ValueBundle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Injection/InjectionCallbackProxy.h` (Internal)


#### enum `EUninjectionResult`  
`enum class EUninjectionResult : uint8`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `Succeeded`
- L19 _public enumerator_ `Failed`

#### class `UInjectionCallbackProxy`  
`class UInjectionCallbackProxy : public UCancellableAsyncAction`  
_L23-87_
- reflection: `UCLASS(MinimalAPI, meta=(ExposedAsyncProxy = "AsyncTask", HasDedicatedAsyncNode))`
- inherits: `UCancellableAsyncAction`
- L30 _public member_ `FOnInjectionDelegate OnCompleted;` — `UPROPERTY(BlueprintAssignable)` — Called when the provided animation object finished playing and hasn't been interrupted
- L34 _public member_ `FOnInjectionDelegate OnBlendOut;` — `UPROPERTY(BlueprintAssignable)` — Called when the provided animation object starts blending out and hasn't been interrupted
- L38 _public member_ `FOnInjectionDelegate OnInterrupted;` — `UPROPERTY(BlueprintAssignable)` — Called when the provided animation object has been interrupted (or failed to play)
- L42 _public prototype_ `static UInjectionCallbackProxy* CreateProxyObjectForInjection( UUAFComponent* AnimNextComponent, UPARAM(meta=(AllowedType=FAnimNextAnimGraph)) FAnimNextVariableReference Site, UObject* Object, FAnimNextFactoryParams FactoryParams = FAnimNextFactoryParams(), FAnimNextInjectionBlendSettings BlendInSettings = FAnimNextInjectionBlendSettings(), FAnimNextInjectionBlendSettings BlendOutSettings = FAnimNextInjectionBlendSettings());` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))` — Called to perform the query internally
- L52 _public prototype_ `EUninjectionResult Uninject();` — `UFUNCTION(BlueprintCallable, Category="Animation|UAF", meta=(ExpandEnumAsExecs = "ReturnValue"))` — Un-inject a previously injected object. Cancelling this async tasks will also un-inject.
- L58 _public prototype_ `void SetVariable(const FAnimNextVariableReference& Variable, const int32& Value);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "UAF", DisplayName = "Set Variable", CustomThunk, meta = (CustomStructureParam = Value, AutoCreateRefTerm = "Variable, Value", UnsafeDuringActorConstruction))` — Sets a variable's value. @param    Name     The variable to set @param    Value    The value to set the variable to
- L61 _public prototype_ `virtual void BeginDestroy() override;` — UObject Interface
- L64 _public prototype_ `virtual void Cancel() override;` — UCancellableAsyncAction interface
- L67 _protected prototype_ `void OnInjectionCompleted(const UE::UAF::FInjectionRequest& Request);`
- L68 _protected prototype_ `void OnInjectionInterrupted(const UE::UAF::FInjectionRequest& Request);`
- L69 _protected prototype_ `void OnInjectionBlendingOut(const UE::UAF::FInjectionRequest& Request);`
- L72 _protected prototype_ `bool Inject( UUAFComponent* AnimNextComponent, FAnimNextVariableReference Site, UObject* Object, FAnimNextFactoryParams&& FactoryParams, const UE::UAF::FInjectionBlendSettings& BlendInSettings, const UE::UAF::FInjectionBlendSettings& BlendOutSettings);` — Attempts to play an object with the specified payload. Returns whether it started or not.
- L81 _private prototype_ `void Reset();`
- L85 _private member_ `UE::UAF::FInjectionRequestPtr PlayingRequest;`
- L86 _private member_ `bool bWasInterrupted = false;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInjectionDelegate);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInjectionDelegate);`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Injection/InjectionSiteTrait.h` (Internal)


#### struct `FAnimNextInjectionSiteTraitSharedData`  
`struct FAnimNextInjectionSiteTraitSharedData : public FAnimNextTraitSharedData`  
_L27-55_
- reflection: `USTRUCT(meta = (DisplayName = "Injection Site"))`
- inherits: `FAnimNextTraitSharedData`
- L33 _public member_ `FAnimNextTraitHandle Source;` — `UPROPERTY()` — Default input when no animation request has been made on this slot.
- L37 _public member_ `FAnimNextAnimGraph Graph;` — `UPROPERTY(EditAnywhere, Category = "Graph")` — The graph to inject
- L41 _public member_ `FAnimNextInjectionBlendSettings DefaultBlendInSettings;` — `UPROPERTY(EditAnywhere, Category = "Blending")` — The default blend settings to use when blending in
- L45 _public member_ `FAnimNextInjectionBlendSettings DefaultBlendOutSettings;` — `UPROPERTY(EditAnywhere, Category = "Blending")` — The default blend settings to use when blending out

#### struct `UE::UAF::FInjectionSiteTrait`  
`struct FInjectionSiteTrait : FAdditiveTrait, IUpdate, IDiscreteBlend, IGarbageCollection, IEvaluate`  
_L72-172_
- inherits: `FAdditiveTrait,IUpdate,IDiscreteBlend,IGarbageCollection,IEvaluate`
- desc: FInjectionSiteTrait A trait that provides a site into which animation graph logic can be 'injected'. It allows for this trait to act as a pass-through when not actively used and when an injection request is made to start playing a child instance, we blend to it.
- L132 _public typedef_ `using FSharedData = FAnimNextInjectionSiteTraitSharedData;`
- L153 _public prototype_ `static void TrackPendingInjectionRequest(int32 InChildIndex, FInstanceData& InstanceData);` — Internal impl - ensure that we have a pending request that we have dispatched to the blend stack, reserves space for tracking, then commits the pending tracking request
- L156 _public prototype_ `ETraitStackPropagation OnInjectEvent(const FExecutionContext& Context, FTraitBinding& Binding, FInjection_InjectEvent& Event) const;` — Event handling impl
- L157 _public prototype_ `ETraitStackPropagation OnUninjectEvent(const FExecutionContext& Context, FTraitBinding& Binding, FInjection_UninjectEvent& Event) const;`
- L160 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L163 _public prototype_ `virtual void OnBlendInitiated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;` — IDiscreteBlend impl
- L164 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L167 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl
- L170 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L171 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;`

#### enum `UE::UAF::FInjectionSiteTrait::EInjectionTrackerState`  
`enum class EInjectionTrackerState : uint8`  
_L77-90_
- desc: Injection tracker state
- L80 _public enumerator_ `Inactive` — Injection request is inactive
- L83 _public enumerator_ `ActiveEvent` — Injection request is active and using a sub-graph that came from an event
- L86 _public enumerator_ `ActivePin` — Injection request is active and using a sub-graph that came from a change to our pinned input
- L89 _public enumerator_ `ActiveSource` — Injection request is active and using the source input

#### struct `UE::UAF::FInjectionSiteTrait::FPendingInjectionRequest`  
`struct FPendingInjectionRequest`  
_L92-109_
- L95 _public member_ `FInjectionRequestPtr Request;` — The injection request
- L98 _public member_ `bool bStop = false;` — Whether or not a Stop request was issued
- L101 _public function_ `bool IsValid() const` — Returns whether or not we have a pending request
- L104 _public function_ `void Reset()` — Resets the pending request

#### struct `UE::UAF::FInjectionSiteTrait::FInjectionTracker`  
`struct FInjectionTracker`  
_L111-130_
- L114 _public member_ `FInjectionRequestPtr Request;` — The Injection request
- L117 _public member_ `EInjectionTrackerState State = EInjectionTrackerState::Inactive;` — The current tracker state
- L120 _public prototype_ `void Initialize(FInjectionRequestPtr InRequest, EInjectionTrackerState InState);` — Initializes a tracker to the specified state
- L123 _public prototype_ `void Reset();` — Resets the tracker for re-use
- L126 _public function_ `bool IsRequestValid() const` — Check whether this pending request is valid for tracking

#### struct `UE::UAF::FInjectionSiteTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L134-149_
- inherits: `FTrait::FInstanceData`
- L137 _public member_ `FInjectionTracker PendingTracker;` — Pending tracker
- L140 _public member_ `TArray<FInjectionTracker> InjectionTrackers;` — List of Injection slot requests
- L143 _public member_ `FPendingInjectionRequest PendingRequest;` — Pending injection request
- L146 _public member_ `FAnimNextAnimGraph CachedGraph;` — Cached graph to use to compare pin equality
- L148 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L48 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace UAF` (scope `UE`)
- L60 _typedef_ `using FInjectionSiteTraitData = FAnimNextInjectionSiteTraitSharedData;` (scope `UE::UAF`) — Namespaced alias
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Injection/MontageTrait.h` (Internal)


#### struct `FUAFMontageTraitSharedData`  
`struct FUAFMontageTraitSharedData : public FAnimNextTraitSharedData`  
_L27-55_
- reflection: `USTRUCT(meta = (DisplayName = "Montage Trait", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can play a montage based on the provided slot name
- L32 _public member_ `FAnimNextTraitHandle Source;` — `UPROPERTY()`
- L36 _public member_ `FName SlotName;` — `UPROPERTY(EditAnywhere, Category = "Montage")` — The name of this slot
- L40 _public member_ `bool bAlwaysUpdateSource = false;` — `UPROPERTY(EditAnywhere, Category = "Montage")` — If true it will always update the source input, even when montages are fully blended in
- L44 _public member_ `bool bDisableSynchronization = false;` — `UPROPERTY(EditAnywhere, Category = "Montage")` — Disables synchronization for this slot even if the playing montage has a sync group setup

#### struct `UE::UAF::FMontageTrait`  
`struct FMontageTrait : FBaseTrait, IUpdate, IEvaluate, IHierarchy, IUpdateTraversal, ITimeline, IGroupSynchronization, IGarbageCollection`  
_L59-163_
- inherits: `FBaseTrait,IUpdate,IEvaluate,IHierarchy,IUpdateTraversal,ITimeline,IGroupSynchronization,IGarbageCollection`
- L138 _public typedef_ `using FSharedData = FUAFMontageTraitSharedData;`
- L141 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L144 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L147 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L148 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L151 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L154 _public prototype_ `virtual void GetSyncMarkers(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineSyncMarkerArray& OutSyncMarkers) const override;` — ITimeline impl
- L155 _public prototype_ `virtual bool GetState(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineState& OutTimelineState) const override;`
- L158 _public prototype_ `virtual FSyncGroupParameters GetGroupParameters(FExecutionContext& Context, const TTraitBinding<IGroupSynchronization>& Binding) const override;` — IGroupSynchronization impl
- L159 _public prototype_ `virtual void AdvanceBy(FExecutionContext& Context, const TTraitBinding<IGroupSynchronization>& Binding, float DeltaTime, bool bDispatchEvents) const override;`
- L162 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### struct `UE::UAF::FMontageTrait::FMontageEvalTaskData`  
`struct FMontageEvalTaskData`  
_L63-73_
- L65 _public function_ `FMontageEvalTaskData(float InAnimPosition, UAnimSequence* InAnimSequence) : AnimPosition(InAnimPosition) , WeakAnimationSequence(InAnimSequence)`
- L71 _public member_ `float AnimPosition = 0.0f;`
- L72 _public member_ `TWeakObjectPtr<UAnimSequence> WeakAnimationSequence = nullptr;`

#### struct `UE::UAF::FMontageTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L75-136_
- inherits: `FTrait::FInstanceData`
- L78 _public member_ `bool bReturnPreUpdateState = true;` — If the pre-update or post-update state should be returned on GetState()
- L84 _public member_ `bool bUsesBlendProfiles = false;` — If any of the active montages are using blend profiles, this will affect what blend is performed and what blend data is created
- L87 _public member_ `FUAFMontageComponent* MontageComponent = nullptr;` — Cached Ptr to the montage component
- L90 _public member_ `int32 SyncCandidateIndex = INDEX_NONE;` — The eval data index into the montage component for the active synchronization candidate
- L93 _public member_ `float DeltaTime = 0.f;` — Delta in seconds between updates, populated during PreUpdate
- L96 _public member_ `float SourceWeight = 1.0f;` — The current blend weight of the source input
- L99 _public member_ `float LastUpdateSourceWeight = 0.0f;` — The source weight of the previous update, used to calculate if the source is blending out
- L102 _public member_ `FTraitPtr Source;` — Input node from which we receive the source pose to blend montages against during blend windows
- L105 _public member_ `FTimelineState PreMontageUpdateState = FTimelineState();` — The state representing the timeline before the montage update
- L108 _public member_ `FTimelineState PostMontageUpdateState = FTimelineState();` — The state representing the timeline after the montage update
- L111 _public member_ `FSyncGroupParameters SyncGroupParams;` — The sync group params used to participate in synchronization
- L114 _public member_ `TArray<float> PoseWeights;` — The individual weights for each montage animation, plus source if relevant
- L117 _public member_ `TArray<float> AdditivePoseWeights;` — The individual weights for each additive montage animation
- L120 _public member_ `TArray<FMontageEvalTaskData> EvalTaskDataForSlot;` — The anim data needed for the evaluation task for this slot
- L123 _public member_ `TArray<FMontageEvalTaskData> AdditiveEvalTaskDataForSlot;` — The additive anim data needed for the evaluation task for this slot
- L126 _public member_ `TArray<FBlendSampleData> BlendDataForBlendProfiles;` — Blend data for non-additive poses if blend profiles are used
- L129 _public member_ `TArray<FBlendSampleData> AdditiveBlendDataForBlendProfiles;` — Blend data for additive poses if blend profiles are used
- L132 _public member_ `TArray<TObjectPtr<const USkeleton>> SkeletonDataForBlendProfiles;` — The skeleton that owns each blend profile used, or nullptr if montage doesn't use a blend profile
- L134 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L135 _public prototype_ `void ResetData();`

#### Free symbols / members of external scopes

- L47 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Injection/UAFMontageComponent.h` (Internal)


#### struct `FUAFUpdateMontageTickFunction`  
`struct FUAFUpdateMontageTickFunction : public FTickFunction`  
_L17-32_
- inherits: `FTickFunction`
- L21 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L22 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L23 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;`
- L27 _private member_ `TWeakObjectPtr<class UUAFComponent> Target = nullptr;`
- L28 _private member_ `TWeakObjectPtr<class UAnimInstance> WeakAnimInstance = nullptr;`
- L29 _private member_ `FUAFMontageComponent* MontageComponent = nullptr;`

#### struct `FUAFMontageEvalData`  
`struct FUAFMontageEvalData`  
_L35-75_
- reflection: `USTRUCT()`
- L40 _public prototype_ `FUAFMontageEvalData() = default;`
- L41 _public function_ `FUAFMontageEvalData(UAnimMontage* InMontage, float InPosition, float InPlayRate, float InBlendStartAlpha, const FAlphaBlend& InBlendInfo, const UBlendProfile* InBlendProfile) : Montage(InMontage) , BlendInfo(InBlendInfo) , ActiveBlendProfile(InBlendProfile) , MontagePosition(InPosition) , MontagePlayRate(InPlayRate) , BlendStartAlpha(InBlendStartAlpha)`
- L52 _public function_ `bool IsActive() const` — Returns true if the montage in this eval data is active (valid and not blending out)
- L55 _public function_ `const UAnimMontage* GetMontage() const` — Returns the montage for this eval data
- L58 _public function_ `const FAlphaBlend& GetBlendInfo() const` — Returns the alpha blend info for this eval data
- L62 _private member_ `TObjectPtr<UAnimMontage> Montage = nullptr;` — `UPROPERTY(Transient)`
- L65 _private member_ `FAlphaBlend BlendInfo = FAlphaBlend();` — `UPROPERTY(Transient)`
- L68 _private member_ `TObjectPtr<const UBlendProfile> ActiveBlendProfile = nullptr;` — `UPROPERTY(Transient)`
- L70 _private member_ `float MontagePosition = 0.0f;`
- L71 _private member_ `float MontagePlayRate = 1.0f;`
- L72 _private member_ `float BlendStartAlpha = 0.0f;`

#### struct `FUAFMontageComponent`  
`struct FUAFMontageComponent : public FUAFModuleInstanceComponent`  
_L80-139_
- reflection: `USTRUCT()`
- inherits: `FUAFModuleInstanceComponent`
- desc: This module instance component is responsible for supporting montages within UAF. It handles required setup, update logic and provides relevant information to montage traits.
- L86 _public prototype_ `FUAFMontageComponent() = default;`
- L89 _public prototype_ `bool IsSlotActive(FName SlotNodeName) const;`
- L90 _public prototype_ `float GetSlotLocalWeight(FName SlotNodeName) const;`
- L91 _public prototype_ `TObjectPtr<const UAnimMontage> GetActiveMontageForSlot(FName SlotNodeName) const;`
- L94 _private prototype_ `virtual void OnBindToInstance() override;`
- L98 _private prototype_ `bool GetActiveNotifiesForSlot(FName SlotName, TArray<FAnimNotifyEventReference>& OutNotifies) const;` — Retrieves all active montage animation notifies for a specific slot name returns true if any notifies for the given slot name exist
- L100 _private prototype_ `bool HasActiveInertializationRequests() const;`
- L101 _private prototype_ `const FInertializationRequest* GetInertializationRequestForGroupName(FName SlotGroupName) const;`
- L106 _private member_ `TArray<FUAFMontageEvalData> MontageEvalData;` — `UPROPERTY(Transient)` — All active and weighted montages, copied from the Anim Instance
- L110 _private member_ `TMap<FName, FAnimNotifyArray> ActiveSlotNotifies;` — `UPROPERTY(Transient)` — Active animation notifies per slot, used to have them easily accessible in montage traits
- L113 _private member_ `TMap<FName, FInertializationRequest> ActiveInertializationRequests;` — `UPROPERTY(Transient)`
- L116 _private member_ `FUAFUpdateMontageTickFunction MontageTickFunction;` — The tick function that is used to update montages on the game thread
- L121 _private member_ `FName TickMontagesBeforeEventName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Montages, meta = (CustomWidget = AnimNextModuleEvent))` — The event name for the module event tick function that the montage tick function will be enqueued as prerequisite for If None is set, it will fall back to DefaultTickDependencyEventName
- L125 _private member_ `TSubclassOf<UAnimInstance> LegacyMontageAnimInstanceClass = nullptr;` — `UPROPERTY(EditAnywhere, Category= Montages, DisplayName="Legacy Montage AnimInstance")` — The Instance Class that Montages will run on
- L130 _private member_ `FName TickDependencyEventName = NAME_None;` — `UPROPERTY(Transient)` — The event name of the module tick function used at runtime to enqueue the montage tick function as a prerequisite to. If the exposed TickMontagesBeforeEventName does not provide an override, it will fall back to DefaultTickDependencyEventName
- L132 _private member_ `bool bHasTickDependencyRegistered = false;`
- L135 _private member_ `static inline const FLazyName DefaultTickDependencyEventName = FLazyName("Pre` — The event name to fall back to for the module event tick function that the montage tick function will be enqueued as prerequisite for

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFMontageComponent> : public TStructOpsTypeTraitsBase2<FUAFMontageComponent>`  
_L142-148_
- inherits: `TStructOpsTypeTraitsBase2<FUAFMontageComponent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L145-147_

#### struct `FRigUnit_IsSlotActive`  
`struct FRigUnit_IsSlotActive : public FRigUnit_AnimNextBase`  
_L152-166_
- reflection: `USTRUCT(meta=(DisplayName="Is Slot Active", Category="Injection", NodeColor="0, 1, 1", Keywords="Slot, Active, Montage"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Returns true if the running UAF System has an active montage in the given slot. A UAnimMontage that is playing in the slot and blending out is not determined to be "active".
- L156 _public prototype_ `RIGVM_METHOD() void Execute();`
- L161 _public member_ `FName SlotNodeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — The name of the slot
- L165 _public member_ `bool Result = false;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — True if the running UAF System has an active montage in the given slot, and it's not blending out

#### struct `FRigUnit_GetSlotLocalWeight`  
`struct FRigUnit_GetSlotLocalWeight : public FRigUnit_AnimNextBase`  
_L170-184_
- reflection: `USTRUCT(meta=(DisplayName="Get Slot Local Weight", Category="Injection", NodeColor="0, 1, 1", Keywords="Slot, Weight, Montage"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Gets the local weight of any montages this slot node is playing. If this slot is not currently playing a montage, it will return 0.
- L174 _public prototype_ `RIGVM_METHOD() void Execute();`
- L179 _public member_ `FName SlotNodeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — The name of the slot
- L183 _public member_ `float LocalWeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — The local weight of any montages this slot is playing

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L146 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon73c868c10103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/PlayAnim/PlayAnimCallbackProxy.h` (Internal)


#### class `UPlayAnimCallbackProxy`  
`class UPlayAnimCallbackProxy : public UObject`  
_L15-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _private member_ `FOnPlayAnimPlayDelegate OnCompleted;` — `UPROPERTY(BlueprintAssignable)` — Called when the provided animation object finished playing and hasn't been interrupted
- L25 _private member_ `FOnPlayAnimPlayDelegate OnBlendOut;` — `UPROPERTY(BlueprintAssignable)` — Called when the provided animation object starts blending out and hasn't been interrupted
- L29 _private member_ `FOnPlayAnimPlayDelegate OnInterrupted;` — `UPROPERTY(BlueprintAssignable)` — Called when the provided animation object has been interrupted (or failed to play)
- L33 _private prototype_ `static UPlayAnimCallbackProxy* CreateProxyObjectForPlayAnim( UUAFComponent* AnimNextComponent, FName SiteName, UAnimSequence* AnimSequence, float PlayRate = 1.0f, float StartPosition = 0.0f, FAnimNextInjectionBlendSettings BlendInSettings = FAnimNextInjectionBlendSettings(), FAnimNextInjectionBlendSettings BlendOutSettings = FAnimNextInjectionBlendSettings());` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))` — Called to perform the query internally
- L43 _private function_ `static UPlayAnimCallbackProxy* CreateProxyObjectForPlayAsset( UUAFComponent* AnimNextComponent, FName SiteName, UObject* Object, const FInstancedStruct& Payload, FAnimNextInjectionBlendSettings BlendInSettings = FAnimNextInjectionBlendSettings(), FAnimNextInjectionBlendSettings BlendOutSettings = FAnimNextInjectionBlendSettings())` — `UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", DeprecatedFunction, DeprecatedMessage="Please use Inject instead."))`
- L56 _public prototype_ `virtual void BeginDestroy() override;`
- L60 _protected prototype_ `void OnPlayAnimCompleted(const UE::UAF::FInjectionRequest& Request);`
- L61 _protected prototype_ `void OnPlayAnimInterrupted(const UE::UAF::FInjectionRequest& Request);`
- L62 _protected prototype_ `void OnPlayAnimBlendingOut(const UE::UAF::FInjectionRequest& Request);`
- L65 _protected prototype_ `bool Play( UUAFComponent* AnimNextComponent, FName SiteName, UAnimSequence* AnimSequence, float PlayRate, float StartPosition, const UE::UAF::FInjectionBlendSettings& BlendInSettings, const UE::UAF::FInjectionBlendSettings& BlendOutSettings);` — Attempts to play an animation with the specified settings. Returns whether it started or not.
- L75 _private prototype_ `void Reset();`
- L77 _private member_ `UE::UAF::FInjectionRequestPtr PlayingRequest;`
- L78 _private member_ `bool bWasInterrupted = false;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayAnimPlayDelegate);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayAnimPlayDelegate);`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/TraitCore/NodeTemplateBuilder.h` (Internal)


#### struct `UE::UAF::FNodeTemplateBuilder`  
`struct FNodeTemplateBuilder`  
_L19-44_
- desc: FNodeTemplateBuilder Utility to help construct node templates.
- L21 _public prototype_ `FNodeTemplateBuilder() = default;`
- L24 _public prototype_ `void AddTrait(FTraitUID TraitUID);` — Adds the specified trait type to the node template
- L28 _public prototype_ `FNodeTemplate* BuildNodeTemplate(TArray<uint8>& NodeTemplateBuffer) const;` — Returns a node template for the provided list of traits The node template will be built into the provided buffer and a pointer to it is returned
- L32 _public prototype_ `static FNodeTemplate* BuildNodeTemplate(TConstArrayView<FTraitUID> InTraitUIDs, TArray<uint8>& NodeTemplateBuffer);` — Returns a node template for the provided list of traits The node template will be built into the provided buffer and a pointer to it is returned
- L35 _public prototype_ `void Reset();` — Resets the node template builder
- L38 _private prototype_ `static uint32 GetNodeTemplateUID(TConstArrayView<FTraitUID> InTraitUIDs);`
- L39 _private prototype_ `static void AppendTemplateTrait( TConstArrayView<FTraitUID>, int32 TraitIndex, TArray<uint8>& NodeTemplateBuffer);`
- L43 _private member_ `TArray<FTraitUID> TraitUIDs;` — The list of traits to use when building the node template

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/TraitCore/NodeTemplateRegistry.h` (Internal)


#### struct `UE::UAF::FNodeTemplateRegistry`  
`struct FNodeTemplateRegistry final`  
_L27-83_
- desc: FNodeTemplateRegistry A global registry of all existing node templates that can be shared between animation graph instances. @see FNodeTemplate
- L32 _public prototype_ `static FNodeTemplateRegistry& Get();` — Access the global registry
- L35 _public prototype_ `FNodeTemplateRegistryHandle Find(uint32 NodeTemplateUID) const;` — Finds the specified node template from its UID and returns its offset
- L38 _public prototype_ `FNodeTemplateRegistryHandle FindOrAdd(const FNodeTemplate* NodeTemplate);` — Finds or adds the specified node template and returns its offset
- L41 _public prototype_ `const FNodeTemplate* Find(FNodeTemplateRegistryHandle TemplateHandle) const;` — Finds and returns a node template based on its handle or nullptr if the handle is invalid
- L44 _public prototype_ `uint32 GetNum() const;` — Returns the number of registered node templates
- L47 _public prototype_ `void Unregister(const FNodeTemplate* NodeTemplate);` — Removes the specified node template from the registry
- L50 _private prototype_ `FNodeTemplateRegistry() = default;`
- L53 _private prototype_ `FNodeTemplate* FindMutable(FNodeTemplateRegistryHandle TemplateHandle);` — Finds and returns a node template based on its handle or nullptr if the handle is invalid
- L56 _private prototype_ `static void Init();` — Module lifetime functions
- L57 _private prototype_ `static void Destroy();`
- L62 _private prototype_ `static FNodeTemplateRegistry* Swap(FNodeTemplateRegistry* Other);` — Swaps the global node template registry with the specified instance Swap it back for the original once tests are done
- L72 _private member_ `TPagedArray<uint8> TemplateBuffer;` — We only ever append node templates to this contiguous buffers This is an optimization, we share these and by being contiguous we improve cache locality and cache line density Because node templates are trivially copyable, we could remove from this buffer when there are holes and coalesce everything. To do so, we would have to fix-up any outstanding handles within the shared data of loaded anim graphs.
- L73 _private member_ `TMap<uint32, FNodeTemplateRegistryHandle> TemplateUIDToHandleMap;`
- L74 _private member_ `mutable FRWLock TemplateLock;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/TraitCore/TraitInterfaceRegistry.h` (Internal)


#### struct `UE::UAF::FTraitInterfaceRegistry`  
`struct FTraitInterfaceRegistry final`  
_L25-72_
- desc: FTraitInterfaceRegistry A global registry of all existing trait interfaces that can be used in animation graph traits. @see FTraitInterface
- L28 _public prototype_ `static FTraitInterfaceRegistry& Get();` — Access the global registry
- L32 _public prototype_ `const ITraitInterface* Find(FTraitInterfaceUID InterfaceUID) const;` — Finds and returns the trait interface associated with the provided trait interface UID. If the trait interface is not registered, nullptr is returned.
- L35 _public prototype_ `void Register(const TSharedPtr<ITraitInterface>& TraitInterface);` — Registers a trait interface dynamically
- L38 _public prototype_ `void Unregister(const TSharedPtr<ITraitInterface>& TraitInterface);` — Unregisters a trait intrerface dynamically
- L41 _public prototype_ `TArray<const ITraitInterface*> GetTraitInterfaces() const;` — Returns a list of all registered trait interfaces
- L44 _public prototype_ `uint32 GetNum() const;` — Returns the number of registered trait interfaces
- L47 _private prototype_ `FTraitInterfaceRegistry() = default;`
- L48 _private prototype_ `FTraitInterfaceRegistry(const FTraitInterfaceRegistry&) = delete;`
- L49 _private prototype_ `FTraitInterfaceRegistry(FTraitInterfaceRegistry&&) = default;`
- L50 _private prototype_ `FTraitInterfaceRegistry& operator=(const FTraitInterfaceRegistry&) = delete;`
- L51 _private prototype_ `FTraitInterfaceRegistry& operator=(FTraitInterfaceRegistry&&) = default;`
- L54 _private prototype_ `static void StaticRegister(const TSharedPtr<ITraitInterface>& TraitInterface);` — Static init lifetime functions
- L55 _private prototype_ `static void StaticUnregister(const TSharedPtr<ITraitInterface>& TraitInterface);`
- L58 _private prototype_ `static void Init();` — Module lifetime functions
- L59 _private prototype_ `static void Destroy();`
- L68 _private member_ `TMap<FTraitInterfaceUIDRaw, FRegistryEntry> TraitInterfaceUIDToEntryMap;`

#### struct `UE::UAF::FTraitInterfaceRegistry::FRegistryEntry`  
`struct FRegistryEntry`  
_L62-66_
- desc: Holds information for each registered trait
- L65 _public member_ `TSharedPtr<ITraitInterface> TraitInterface = nullptr;` — A pointer to the trait

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/TraitCore/TraitReader.h` (Internal)


#### class `UE::UAF::FTraitReader`  
`class FTraitReader final : public FArchiveProxy`  
_L23-78_
- inherits: `FArchiveProxy`
- desc: FTraitReader The trait reader is used to read from a serialized binary blob that contains the anim graph data. An anim graph contains the following: - A list of FNodeTemplates that the nodes use - The graph shared data (FNodeDescription for every node)
- L30 _public member_ `static constexpr uint32 MAXIMUM_GRAPH_SHARED_DATA_SIZE = (1 << 24) - 1;` — The largest size allowed for the shared data of a single graph Node/trait handles use an unsigned 24 bits value to represent graph offsets which limits us to 16 MB We could extend this range by leveraging the fact that nodes have a minimum required alignment
- L41 _public prototype_ `explicit FTraitReader(const TArray<TObjectPtr<UObject>>& InGraphReferencedObjects, const TArray<FSoftObjectPath>& InGraphReferencedSoftObjects, FArchive& Ar);`
- L43 _public prototype_ `[[nodiscard]] EErrorState ReadGraph(TArray<uint8>& GraphSharedData);`
- L47 _public prototype_ `[[nodiscard]] FNodeHandle ResolveNodeHandle(FNodeHandle NodeHandle) const;` — Takes a node handle representing a node index and resolves it into a node handle representing a shared data offset Must be called after ReadGraphSharedData as it populates the necessary data
- L51 _public prototype_ `[[nodiscard]] FAnimNextTraitHandle ResolveTraitHandle(FAnimNextTraitHandle TraitHandle) const;` — Takes a trait handle representing a node index and resolves it into a node handle representing a shared data offset Must be called after ReadGraphSharedData as it populates the necessary data
- L55 _public prototype_ `[[nodiscard]] FAnimNextTraitHandle ResolveEntryPointHandle(FAnimNextEntryPointHandle EntryPointHandle) const;` — Takes an entry point handle representing a node index and resolves it into a node handle representing a shared data offset Must be called after ReadGraphSharedData as it populates the necessary data
- L58 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;` — FArchive implementation
- L59 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Obj) override;`
- L60 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& Value) override;`
- L61 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPtr& Value) override;`
- L62 _public prototype_ `virtual FArchive& operator<<(FWeakObjectPtr& Value) override;`
- L66 _private prototype_ `[[nodiscard]] EErrorState ReadGraphSharedData(TArray<uint8>& GraphSharedData);` — Call first to read the graph shared data
- L69 _private member_ `const TArray<TObjectPtr<UObject>>& GraphReferencedObjects;` — A list of UObject references within the graph
- L72 _private member_ `const TArray<FSoftObjectPath>& GraphReferencedSoftObjects;` — A list of soft object references within the graph
- L75 _private member_ `TArray<FNodeHandle> NodeHandles;` — A list of node handles for each node within the archive

#### enum `UE::UAF::FTraitReader::EErrorState`  
`enum class EErrorState`  
_L32-39_
- L34 _public enumerator_ `None` — All good, no error
- L35 _public enumerator_ `GraphTooLarge` — Exceeded the maximum graph size, @see FTraitReader::MAXIMUM_GRAPH_SHARED_DATA_SIZE
- L36 _public enumerator_ `NodeSharedDataTooLarge` — Exceeded the maximum node shared data size, @see FNodeDescription::MAXIMUM_NODE_SHARED_DATA_SIZE
- L37 _public enumerator_ `NodeInstanceDataTooLarge` — Exceeded the maximum node instance data size, @see FNodeInstance::MAXIMUM_NODE_INSTANCE_DATA_SIZE
- L38 _public enumerator_ `InvalidData` — Unexpected or corrupted data

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/TraitCore/TraitRegistry.h` (Internal)


#### struct `UE::UAF::FTraitRegistry`  
`struct FTraitRegistry final`  
_L26-117_
- desc: FTraitRegistry A global registry of all existing traits that can be used in animation graphs. @see FTrait
- L29 _public prototype_ `static FTraitRegistry& Get();` — Access the global registry
- L33 _public prototype_ `FTraitRegistryHandle FindHandle(FTraitUID TraitUID) const;` — Finds and returns the trait handle for the provided trait UID or an invalid handle if that trait hasn't been registered yet.
- L37 _public prototype_ `const FTrait* Find(FTraitRegistryHandle TraitHandle) const;` — Finds and returns the trait associated with the provided handle. If the handle is not valid, nullptr is returned.
- L41 _public prototype_ `const FTrait* Find(FTraitUID TraitUID) const;` — Finds and returns the trait associated with the provided trait UID. If the trait is not registered, nullptr is returned.
- L45 _public prototype_ `const FTrait* Find(const UScriptStruct* TraitSharedDataStruct) const;` — Finds and returns the trait associated with the provided trait shared data UScriptStruct. If the matching trait is not registered, nullptr is returned.
- L49 _public prototype_ `const FTrait* Find(FName TraitTypeName) const;` — Finds and returns the trait associated with the provided trait name. If the matching trait is not registered, nullptr is returned.
- L52 _public prototype_ `void Register(FTrait* Trait);` — Registers a trait dynamically
- L55 _public prototype_ `void Unregister(FTrait* Trait);` — Unregisters a trait dynamically
- L58 _public prototype_ `TArray<const FTrait*> GetTraits() const;` — Returns a list of all registered traits
- L61 _public prototype_ `uint32 GetNum() const;` — Returns the number of registered traits
- L64 _private prototype_ `FTraitRegistry() = default;`
- L65 _private prototype_ `FTraitRegistry(const FTraitRegistry&) = delete;`
- L66 _private prototype_ `FTraitRegistry(FTraitRegistry&&) = default;`
- L67 _private prototype_ `FTraitRegistry& operator=(const FTraitRegistry&) = delete;`
- L68 _private prototype_ `FTraitRegistry& operator=(FTraitRegistry&&) = default;`
- L71 _private prototype_ `static void StaticRegister(TraitConstructorFunc TraitConstructor);` — Static init lifetime functions
- L72 _private prototype_ `static void StaticUnregister(TraitConstructorFunc TraitConstructor);`
- L73 _private prototype_ `void AutoRegisterImpl(TraitConstructorFunc TraitConstructor);`
- L74 _private prototype_ `void AutoUnregisterImpl(TraitConstructorFunc TraitConstructor);`
- L77 _private prototype_ `static void Init();` — Module lifetime functions
- L78 _private prototype_ `static void Destroy();`
- L104 _private member_ `static constexpr uint32 STATIC_TRAIT_BUFFER_SIZE = 8 * 1024;` — For performance reasons, we store static traits that never unload into a single contiguous memory buffer. However, traits cannot be guaranteed to be trivially copyable because they contain virtual functions. As such, we cannot resize the buffer once they have been allocated. We reserve a fixed amount of space that should easily cover our needs. Static traits are generally stateless and only contain a few v-tables. Their size is usually less than 32 bytes. Additionally, we will likely only ever load a few hundred traits. If we exceed the size of the buffer, additional traits will be treated as dynamic. Dynamic traits are instead allocated on the heap.
- L106 _private member_ `uint8 StaticTraitBuffer[STATIC_TRAIT_BUFFER_SIZE] = { 0 };`
- L107 _private member_ `int32 StaticTraitBufferOffset = 0;`
- L109 _private member_ `TArray<intptr_t> DynamicTraits;`
- L110 _private member_ `int32 DynamicTraitFreeIndexHead = INDEX_NONE;`
- L112 _private member_ `TMap<FTraitUIDRaw, FRegistryEntry> TraitUIDToEntryMap;`
- L113 _private member_ `TMap<FName, FTraitUIDRaw> TraitNameToUIDMap;`

#### struct `UE::UAF::FTraitRegistry::FRegistryEntry`  
`struct FRegistryEntry`  
_L81-93_
- desc: Holds information for each registered trait
- L85 _public member_ `FTrait* Trait = nullptr;` — A pointer to the trait TODO: Do we want a shared ptr here? we don't always own it
- L89 _public member_ `TraitConstructorFunc TraitConstructor = nullptr;` — A pointer to the constructor function Only valid when the trait has been auto-registered
- L92 _public member_ `FTraitRegistryHandle TraitHandle;` — The trait handle

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/TraitCore/TraitWriter.h` (Internal)


#### class `UE::UAF::FTraitWriter`  
`class FTraitWriter final : public FMemoryWriter`  
_L29-114_
- inherits: `FMemoryWriter`
- desc: FTraitWriter The trait writer is used to write a serialized binary blob that contains the anim graph data. An anim graph contains the following: - A list of FNodeTemplates that the nodes use - The graph shared data (FNodeDescription for every node)
- L41 _public prototype_ `FTraitWriter();`
- L44 _public prototype_ `[[nodiscard]] FNodeHandle RegisterNode(const FNodeTemplate& NodeTemplate);` — Registers an instance of the provided node template and assigns a node handle and node UID to it
- L47 _public prototype_ `void BeginNodeWriting();` — Called before node writing can begin
- L50 _public prototype_ `void EndNodeWriting();` — Called once node writing has terminated
- L55 _public prototype_ `void WriteNode( const FNodeHandle NodeHandle, const TFunction<FString(uint32 TraitIndex, FName PropertyName)>& GetTraitProperty, const TFunction<uint16(uint32 TraitIndex, FName PropertyName)>& GetTraitLatentPropertyIndex );` — Writes out the provided node using the trait properties Nodes must be written in the same order they were registered in
- L64 _public prototype_ `void WriteNode( const FNodeHandle NodeHandle, TFunctionRef<uint16(uint32 TraitIndex, FName PropertyName)> GetTraitLatentPropertyIndex, TFunctionRef<TConstStructView<FAnimNextTraitSharedData>(uint32 TraitIndex)> GetTraitData);` — Writes out the provided node using the trait properties Nodes must be written in the same order they were registered in
- L70 _public prototype_ `[[nodiscard]] EErrorState GetErrorState() const;` — Returns the error state
- L73 _public prototype_ `[[nodiscard]] const TArray<uint8>& GetGraphSharedData() const;` — Returns the populated raw graph shared data buffer
- L76 _public prototype_ `[[nodiscard]] const TArray<UObject*>& GetGraphReferencedObjects() const;` — Returns the list of referenced UObjects in this graph
- L79 _public prototype_ `[[nodiscard]] const TArray<FSoftObjectPath>& GetGraphReferencedSoftObjects() const;` — Returns the list of referenced soft objects in this graph
- L82 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;` — FArchive implementation
- L83 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Obj) override;`
- L84 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& Value) override;`
- L85 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPtr& Value) override;`
- L86 _public prototype_ `virtual FArchive& operator<<(FWeakObjectPtr& Value) override;`
- L101 _private member_ `TArray<uint8> GraphSharedDataArchiveBuffer;`
- L102 _private member_ `TArray<FNodeMapping> NodeMappings;`
- L105 _private member_ `FNodeID NextNodeID;` — To track the node registration process
- L108 _private member_ `TArray<UObject*> GraphReferencedObjects;` — To track node writing
- L109 _private member_ `TArray<FSoftObjectPath> GraphReferencedSoftObjects;`
- L110 _private member_ `uint32 NumNodesWritten;`
- L111 _private member_ `bool bIsNodeWriting;`
- L113 _private member_ `EErrorState ErrorState;`

#### enum `UE::UAF::FTraitWriter::EErrorState`  
`enum class EErrorState`  
_L32-39_
- L34 _public enumerator_ `None` — All good, no error
- L35 _public enumerator_ `TooManyNodes` — Exceeded the maximum number of nodes in a graph, @see FNodeDescription::MAXIMUM_COUNT
- L36 _public enumerator_ `NodeTemplateNotFound` — Failed to find a necessary node template
- L37 _public enumerator_ `NodeTemplateTooLarge` — Exceeded the maximum node template size, @see FNodeTemplate::MAXIMUM_SIZE
- L38 _public enumerator_ `NodeHandleNotFound` — Failed to find the mapping for a node handle, it was likely not registered

#### struct `UE::UAF::FTraitWriter::FNodeMapping`  
`struct FNodeMapping`  
_L89-99_
- L92 _public member_ `FNodeHandle NodeHandle;` — The node handle for this entry (encoded as a node ID)
- L95 _public member_ `FNodeTemplateRegistryHandle NodeTemplateHandle;` — The node template handle the node uses
- L98 _public member_ `uint32 NodeTemplateIndex;` — The unique node template index that we'll serialize

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Traits/BlendByBool.h` (Internal)


#### struct `FAnimNextBlendByBoolTraitSharedData`  
`struct FAnimNextBlendByBoolTraitSharedData : public FAnimNextTraitSharedData`  
_L16-42_
- reflection: `USTRUCT(meta = (DisplayName = "Blend By Bool", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can blend two discrete inputs through a boolean.
- L22 _public member_ `FAnimNextTraitHandle TrueChild;` — `UPROPERTY()` — First output to be blended.
- L26 _public member_ `FAnimNextTraitHandle FalseChild;` — `UPROPERTY()` — Second output to be blended.
- L30 _public member_ `bool bCondition = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — The boolean condition that decides which child is active.
- L34 _public member_ `bool bAlwaysUpdateTrueChild = false;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))` — Always update TrueChild, regardless of whether or not that child has weight.

#### struct `UE::UAF::FBlendByBoolTrait`  
`struct FBlendByBoolTrait : FBaseTrait, IUpdate, IUpdateTraversal, IHierarchy, IDiscreteBlend`  
_L51-83_
- inherits: `FBaseTrait,IUpdate,IUpdateTraversal,IHierarchy,IDiscreteBlend`
- desc: FBlendByBoolTrait A trait that can blend two discrete inputs through a boolean.
- L55 _public typedef_ `using FSharedData = FAnimNextBlendByBoolTraitSharedData;`
- L68 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L71 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L74 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L75 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L78 _public prototype_ `virtual float GetBlendWeight(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;` — IDiscreteBlend impl
- L79 _public prototype_ `virtual int32 GetBlendDestinationChildIndex(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding) const override;`
- L80 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;`
- L81 _public prototype_ `virtual void OnBlendInitiated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L82 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`

#### struct `UE::UAF::FBlendByBoolTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L57-65_
- inherits: `FTrait::FInstanceData`
- L59 _public member_ `FTraitPtr TrueChild;`
- L60 _public member_ `FTraitPtr FalseChild;`
- L62 _public member_ `int32 PreviousChildIndex = INDEX_NONE;`
- L63 _public member_ `bool bWasTrueChildRelevant = false;`
- L64 _public member_ `bool bWasFalseChildRelevant = false;`

#### Free symbols / members of external scopes

- L37 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Traits/BlendStackTrait.h` (Internal)


#### struct `FAnimNextBlendStackCoreTraitSharedData`  
`struct FAnimNextBlendStackCoreTraitSharedData : public FAnimNextTraitSharedData`  
_L22-27_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Stack Core", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: Used as base trait in state machine-like setups where state machine is the additive trait that pushes graphs and blend settings to the blend stack.

#### struct `FAnimNextBlendStackTraitSharedData`  
`struct FAnimNextBlendStackTraitSharedData : public FAnimNextBlendStackCoreTraitSharedData`  
_L40-64_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Stack", ShowTooltip=true))`
- inherits: `FAnimNextBlendStackCoreTraitSharedData`
- desc: Standalone blend stack that exposes desired object and blend time as pins. A new graph will be pushed every time the newest object does not match the pin (or bForceBlend is true).
- L46 _public member_ `TObjectPtr<const UObject> Object;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Asset to use as a sub-graph
- L50 _public member_ `float BlendTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Blend time to use when sub-graph pin input changes
- L54 _public member_ `bool bForceBlend = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Force a blend to the current graph, even if there's been no change in selection.

#### struct `FAnimNextBlendStackRequesterTraitSharedData`  
`struct FAnimNextBlendStackRequesterTraitSharedData : public FAnimNextTraitSharedData`  
_L71-95_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Stack Requester", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: Example additive trait used to push graphs to a Blend Stack base trait. Same behavior as FBlendStackTrait, but as additive (i.e. FBlendStackCoreTrait base + FBlendStackRequesterTrait as additive).
- L77 _public member_ `TObjectPtr<UObject> Object;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Asset to use as a sub-graph
- L81 _public member_ `float BlendTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Blend time to use when sub-graph pin input changes
- L85 _public member_ `bool bForceBlend = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Force a blend to the current graph, even if there's been no change in selection.

#### struct `UE::UAF::FBlendStackCoreTrait`  
`struct FBlendStackCoreTrait : FBaseTrait, IUpdate, IUpdateTraversal, IHierarchy, IDiscreteBlend, ISmoothBlend, IInertializerBlend, ITimeline, IGarbageCollection, IBlendStack, ISmoothBlendPerBone`  
_L104-217_
- inherits: `FBaseTrait,IUpdate,IUpdateTraversal,IHierarchy,IDiscreteBlend,ISmoothBlend,IInertializerBlend,ITimeline,IGarbageCollection,IBlendStack,ISmoothBlendPerBone`
- desc: FBlendStackCoreTrait Used as base trait in state machine-like setups where state machine is the additive trait that pushes graphs and blend settings to the blend stack.
- L167 _public typedef_ `using FSharedData = FAnimNextBlendStackCoreTraitSharedData;`
- L170 _public prototype_ `static int32 FindFreeGraphIndexOrAdd(FInstanceData& InstanceData);` — Internal impl
- L173 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L176 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L179 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L180 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L181 _public prototype_ `virtual FWeakTraitPtr GetStackForwardingChild(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;`
- L184 _public prototype_ `virtual float GetBlendWeight(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;` — IDiscreteBlend impl
- L185 _public prototype_ `virtual int32 GetBlendDestinationChildIndex(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding) const override;`
- L186 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;`
- L187 _public prototype_ `virtual void OnBlendInitiated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L188 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L191 _public prototype_ `virtual float GetBlendTime(FExecutionContext& Context, const TTraitBinding<IInertializerBlend>& Binding, int32 ChildIndex) const override;` — IInertializerBlend impl
- L194 _public prototype_ `virtual float GetBlendTime(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;` — ISmoothBlend impl
- L195 _public prototype_ `virtual EAlphaBlendOption GetBlendType(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;`
- L196 _public prototype_ `virtual UCurveFloat* GetCustomBlendCurve(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;`
- L199 _public prototype_ `virtual bool GetState(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineState& OutTimelineState) const override;` — ITimeline impl
- L202 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl
- L205 _public prototype_ `virtual int32 PushGraph(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, IBlendStack::FGraphRequest&& GraphRequest) const override;` — IBlendStack impl
- L206 _public prototype_ `virtual int32 GetActiveGraph(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, IBlendStack::FGraphRequestPtr& OutGraphRequest) const override;`
- L207 _public prototype_ `virtual int32 GetActiveGraphInstance(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, FAnimNextGraphInstance*& OutGraphInstance) const override;`
- L208 _public prototype_ `virtual IBlendStack::FGraphRequestPtr GetGraph(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, int32 InChildIndex) const override;`
- L209 _public prototype_ `virtual FAnimNextGraphInstance* GetGraphInstance(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, int32 InChildIndex) const override;`
- L212 _public prototype_ `virtual const UUAFBlendProfile* GetBlendProfile(FExecutionContext& Context, const TTraitBinding<ISmoothBlendPerBone>& Binding, int32 ChildIndex) const;` — ISmoothBlendPerBone impl
- L215 _public function_ `virtual bool IsHidden() const override`

#### enum `UE::UAF::FBlendStackCoreTrait::EGraphState`  
`enum class EGraphState : uint8`  
_L108-112_
- L110 _public enumerator_ `Inactive`
- L111 _public enumerator_ `Active`

#### struct `UE::UAF::FBlendStackCoreTrait::FGraphState`  
`struct FGraphState`  
_L114-155_
- L117 _public member_ `IBlendStack::FGraphRequest Request;` — The blend settings to use
- L120 _public member_ `TSharedPtr<FAnimNextGraphInstance> Instance;` — The graph instance
- L123 _public member_ `float Lifetime;` — The length of time this subgraph has been alive
- L125 _public member_ `FBlendStackCoreTrait::EGraphState State;`
- L128 _public member_ `bool bNewlyCreated = false;` — Whether or not this graph was previously relevant
- L130 _public prototype_ `void Initialize(IBlendStack::FGraphRequest&& GraphRequest);`
- L131 _public prototype_ `void Terminate();`
- L133 _public function_ `FWeakTraitPtr GetChildPtr() const`
- L146 _public function_ `void SetChildPtr(FWeakTraitPtr InChildPtr)`
- L154 _private member_ `FTraitPtr ChildPtr;` — Our child handle Weak handle to the graph instance's root

#### struct `UE::UAF::FBlendStackCoreTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L157-165_
- inherits: `FTrait::FInstanceData`
- L160 _public member_ `TArray<FGraphState> ChildGraphs;` — List of current graphs in the blend stack
- L164 _public member_ `int32 CurrentlyActiveGraphIndex = INDEX_NONE;` — The index of the currently active graph All other graphs are blending out

#### struct `UE::UAF::FBlendStackTrait`  
`struct FBlendStackTrait : FBlendStackCoreTrait`  
_L225-237_
- inherits: `FBlendStackCoreTrait`
- desc: FBlendStackTrait Standalone blend stack that exposes desired object and blend time as pins. A new graph will be pushed every time the newest object does not match the pin (or bForceBlend is true).
- L229 _public typedef_ `using FSharedData = FAnimNextBlendStackTraitSharedData;`
- L232 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L235 _public function_ `virtual bool IsHidden() const override`

#### struct `UE::UAF::FBlendStackRequesterTrait`  
`struct FBlendStackRequesterTrait : FAdditiveTrait, IUpdate, IGarbageCollection`  
_L245-256_
- inherits: `FAdditiveTrait,IUpdate,IGarbageCollection`
- desc: FBlendStackRequesterTrait Example additive trait used to push graphs to a Blend Stack base trait. Same behavior as FBlendStackTrait, but as additive (i.e. FBlendStackCoreTrait base + FBlendStackRequesterTrait as additive).
- L249 _public typedef_ `using FSharedData = FAnimNextBlendStackRequesterTraitSharedData;`
- L252 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L255 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)
- L32 _typedef_ `using FBlendStackCoreTraitData = FAnimNextBlendStackCoreTraitSharedData;` (scope `UE::UAF`) — Namespaced alias
- L57 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L97 _namespace_ `namespace UE`
- L97 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Traits/CallFunction.h` (Internal)


#### enum `EAnimNextCallFunctionCallSite`  
`enum class EAnimNextCallFunctionCallSite : uint8`  
_L14-24_
- reflection: `UENUM()`
- L17 _public enumerator_ `BecomeRelevant` — Called each time the trait becomes relevant
- L20 _public enumerator_ `PreUpdate` — Called on update before the trait and any stack super-traits update
- L23 _public enumerator_ `PostUpdate` — Called on update after the trait and any stack super-traits update

#### struct `FUAFCallFunctionInfo`  
`struct FUAFCallFunctionInfo`  
_L29-45_
- reflection: `USTRUCT(meta = (DisplayName = "UAF Function"))`
- desc: Struct used to help call / pick functions across UAF
- L35 _public member_ `FRigVMGraphFunctionHeader FunctionHeader;` — `UPROPERTY(VisibleAnywhere, Category = "Call Function", meta = (PinHiddenByDefault, Hidden))`
- L40 _public member_ `FName Function;` — `UPROPERTY(EditAnywhere, Category = "Call Function", meta = (PinHiddenByDefault, Hidden))` — The function to call
- L44 _public member_ `FName FunctionEvent;` — `UPROPERTY(VisibleAnywhere, Category = "Call Function", meta = (PinHiddenByDefault, Hidden))` — Internal event name derived from Function above

#### struct `FAnimNextCallFunctionSharedData`  
`struct FAnimNextCallFunctionSharedData : public FAnimNextTraitSharedData`  
_L50-79_
- reflection: `USTRUCT(meta = (DisplayName = "Call RigVM Function", AllowDuplicates = "true"))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that calls a RigVM function at the specified update point
- L58 _public member_ `FRigVMGraphFunctionHeader FunctionHeader;` — `UPROPERTY(VisibleAnywhere, Category = "Call Function", meta=(Hidden))`
- L63 _public member_ `FName Function;` — `UPROPERTY(EditAnywhere, Category = "Call Function", meta=(Hidden))` — The function to call
- L67 _public member_ `FName FunctionEvent;` — `UPROPERTY(VisibleAnywhere, Category = "Call Function", meta=(Hidden))` — Internal event name derived from Function above
- L71 _public member_ `EAnimNextCallFunctionCallSite CallSite = EAnimNextCallFunctionCallSite::BecomeRelevant;` — `UPROPERTY(EditAnywhere, Category = "Call Function", meta=(PinHiddenByDefault))` — The call site to use

#### struct `UE::UAF::FCallFunctionTrait`  
`struct FCallFunctionTrait : FAdditiveTrait, IUpdate`  
_L88-105_
- inherits: `FAdditiveTrait,IUpdate`
- desc: FCallFunctionTrait A trait that calls a RigVM function at the specified update point
- L92 _public typedef_ `using FSharedData = FAnimNextCallFunctionSharedData;`
- L99 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L100 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L101 _public prototype_ `virtual void PostUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L104 _public prototype_ `void CallFunctionForMatchingSite(const TTraitBinding<IUpdate>& InBinding, const FTraitUpdateState& InTraitState, EAnimNextCallFunctionCallSite InCallSite) const;` — Calls the RigVM function that is assigned to us

#### struct `UE::UAF::FCallFunctionTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L94-96_
- inherits: `FTrait::FInstanceData`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L74 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L81 _namespace_ `namespace UE`
- L81 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/Traits/InputValueTrait.h` (Internal)


#### struct `FUAFInputValueTraitSharedData`  
`struct FUAFInputValueTraitSharedData : public FAnimNextTraitSharedData`  
_L15-29_
- reflection: `USTRUCT(meta = (DisplayName = "Input Value", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- L21 _public member_ `FAnimNextVariableReference Input;` — `UPROPERTY(EditAnywhere, Category="Input Value", meta=(Input, HideSubPins, AllowedType = FUAFValueBundle))` — The variable to use as an input value

#### struct `UE::UAF::FInputValueTrait`  
`struct FInputValueTrait : FBaseTrait, IUpdate, IEvaluate, IUpdateTraversal, IHierarchy`  
_L33-60_
- inherits: `FBaseTrait,IUpdate,IEvaluate,IUpdateTraversal,IHierarchy`
- L37 _public typedef_ `using FSharedData = FUAFInputValueTraitSharedData;`
- L46 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L47 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L50 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L53 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L56 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L57 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L59 _public prototype_ `const FInstanceData* UpdateInstanceData(const FTraitBinding& InBinding) const;`

#### struct `UE::UAF::FInputValueTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L39-43_
- inherits: `FTrait::FInstanceData`
- L41 _public member_ `FAnimNextVariableReference VariableReference;`
- L42 _public member_ `FAnimNextGraphInstance* GraphInstance = nullptr;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/AnimNextAnimGraphModule.h` (Private)


#### class `UE::UAF::AnimGraph::FAnimNextAnimGraphModule`  
`class FAnimNextAnimGraphModule : public IModuleInterface, public FGCObject`  
_L18-53_
- inherits: `IModuleInterface,FGCObject`
- L21 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L22 _private prototype_ `virtual void ShutdownModule() override;`
- L25 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L26 _private prototype_ `virtual FString GetReferencerName() const override;`
- L29 _private prototype_ `void RegisterGraphFactories();` — Register asset class -> graph factory mappings
- L32 _private prototype_ `void RegisterSystemFactories();` — Register asset class -> system factory mappings
- L34 _private prototype_ `void RegisterAssetData();`
- L35 _private prototype_ `void UnregisterAssetData();`
- L41 _private member_ `TArray<TObjectPtr<const UUAFAnimGraph>> LoadedGraphs;` — References to loaded default graphs to prevent GC. They must exist here rather than on the UAnimNextAnimGraphSettings CDO to avoid breaking DisregardForGC assumptions
- L44 _private prototype_ `void ListNodeTemplates(const TArray<FString>& Args);`
- L45 _private prototype_ `void ListAnimationGraphs(const TArray<FString>& Args);`
- L47 _private member_ `TArray<IConsoleObject*> ConsoleCommands;`
- L50 _private member_ `FTopLevelAssetPath UAFAnimGraphClassPath;`
- L51 _private member_ `FTopLevelAssetPath AnimSequenceClassPath;`
- L52 _private member_ `FTopLevelAssetPath BlendSpaceClassPath;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define WITH_ANIMNEXT_CONSOLE_COMMANDS (!UE_BUILD_SHIPPING && !NO_LOGGING)` — Enable console commands only in development builds when logging is enabled
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/EvaluationVM/Tasks/ConvertRotationSpaceDefs.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_ANIM_CONVERT_ROTATION_SPACE_TASKS_ISPC INTEL_ISPC`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/EvaluationVM/Tasks/CopyBones.h` (Private)


#### struct `FAnimNextCopyBonesComponentSpaceTask`  
`struct FAnimNextCopyBonesComponentSpaceTask : public FAnimNextEvaluationTask`  
_L19-32_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: FAnimNextCopyBonesComponentSpaceTask Copies bones in component space
- L23 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextCopyBonesComponentSpaceTask)`
- L29 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L31 _public member_ `TArray<FAnimNextBoneMapping> Mapping;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Graph/AnimNextSkeletalMeshComponentLibrary.h` (Private)


#### class `UAnimNextSkeletalMeshComponentLibrary`  
`class UAnimNextSkeletalMeshComponentLibrary : public UBlueprintFunctionLibrary`  
_L14-22_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Access to non-UProperty/UFunction data on USkeletalMeshComponent
- L21 _public prototype_ `static FAnimNextGraphReferencePose GetReferencePose(USkeletalMeshComponent* InComponent);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)` — Returns the reference pose for the specified component

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Graph/RigUnit_AnimNextSetNotifyContext.h` (Private)


#### struct `FRigUnit_AnimNextSetNotifyContext`  
`struct FRigUnit_AnimNextSetNotifyContext : public FRigUnit_AnimNextBase`  
_L13-27_
- reflection: `USTRUCT(meta=(DisplayName="Set Notify Context", Category="Notifies", NodeColor="0, 1, 1", Keywords="Event,Output"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Sets up the context in which notifies are called
- L17 _public prototype_ `RIGVM_METHOD() void Execute();`
- L22 _public member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY(meta = (Input))` — The mesh component to supply to any notify dispatches
- L26 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(meta = (Input, Output))` — The execute context to use for the given skeletal mesh component

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Graph/RigUnit_GetPostProcessAnimation.h` (Private)


#### struct `FRigUnit_GetPostProcessAnimation`  
`struct FRigUnit_GetPostProcessAnimation : public FRigUnit_AnimNextBase`  
_L13-42_
- reflection: `USTRUCT(meta=(DisplayName="Get Post-Process Animation", Category="Animation Graph", NodeColor="0.5, 1, 1", Keywords="Graph,Port"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Get post process animation data for a given skeletal mesh.
- L17 _public prototype_ `RIGVM_METHOD() void Execute();`
- L22 _public member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY(EditAnywhere, Category = "Post-Process Animation", meta = (Input))` — Skeletal mesh component to be used to read the post-process animation from the assigned skeletal mesh.
- L26 _public member_ `int32 LODLevel = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Post-Process Animation", meta = (Input))` — Current LOD we run animation with on the given skeletal mesh component.
- L30 _public member_ `FAnimNextAnimGraph Graph;` — `UPROPERTY(EditAnywhere, Category = "Post-Process Animation", meta = (Output))` — Post-process animation graph to run, read from the given skeletal mesh.
- L34 _public member_ `bool bShouldEvaluate = true;` — `UPROPERTY(EditAnywhere, Category = "Post-Process Animation", meta = (Output))` — Can we skip or should we run the output animation graph based on the given input LOD and the skeletal mesh's post-process LOD threshold.
- L38 _public member_ `int32 LODThreshold = -1;` — `UPROPERTY(EditAnywhere, Category = "Post-Process Animation", meta = (Output))` — Raw post-process animation LOD threshold read from the given skeletal mesh. This can be used for custom thresholding when the "Should Evaluate" is not sufficient.
- L41 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Graph/RigUnit_HasValidEvaluationModifier.h` (Private)


#### struct `FRigUnit_HasValidEvaluationModifier`  
`struct FRigUnit_HasValidEvaluationModifier : public FRigUnit_AnimNextBase`  
_L13-27_
- reflection: `USTRUCT(meta=(DisplayName="Has Valid Evaluation Modifier", Category="Animation Next Injection", NodeColor="0, 1, 1"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Used to determine whether an evaluation modifier is valid (indicates active injection)
- L17 _public prototype_ `RIGVM_METHOD() void Execute();`
- L22 _public member_ `FAnimNextGraphInjectionData InjectionData;` — `UPROPERTY(EditAnywhere, Category = "Struct", meta = (Input))` — The Injection Data instance to check
- L26 _public member_ `bool bValue = false;` — `UPROPERTY(EditAnywhere, Category = "Struct", meta = (Output))` — Whether Evaluation Modifier is valid (indicates active injection)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Graph/SyncGroup_GraphInstanceComponent.h` (Private)


#### struct `FSyncGroupGraphInstanceComponent`  
`struct FSyncGroupGraphInstanceComponent : public FUAFGraphInstanceComponent`  
_L28-72_
- reflection: `USTRUCT()`
- inherits: `FUAFGraphInstanceComponent`
- desc: FSyncGroupGraphInstanceComponent This component maintains the necessary state to support group based synchronization.
- L34 _public prototype_ `FSyncGroupGraphInstanceComponent();` — Defaulted constructors/copy-operators in cpp so fwd decls of members can work
- L35 _public prototype_ `FSyncGroupGraphInstanceComponent(FSyncGroupGraphInstanceComponent&&);`
- L36 _public prototype_ `FSyncGroupGraphInstanceComponent(const FSyncGroupGraphInstanceComponent&);`
- L37 _public prototype_ `FSyncGroupGraphInstanceComponent& operator=(const FSyncGroupGraphInstanceComponent&);`
- L38 _public prototype_ `FSyncGroupGraphInstanceComponent& operator=(FSyncGroupGraphInstanceComponent&&);`
- L40 _public prototype_ `virtual ~FSyncGroupGraphInstanceComponent();`
- L43 _public prototype_ `void RegisterWithGroup(const UE::UAF::FSyncGroupParameters& GroupParameters, const UE::UAF::FWeakTraitPtr& TraitPtr, const UE::UAF::FTraitUpdateState& TraitState);` — Registers the specified trait with group based synchronization
- L47 _public prototype_ `FName CreateUniqueGroupName();` — Create a unique group name suitable for spawned sub-graphs to self-synchronize Unique group names are a limited resource, when no longed needed they must be released
- L51 _public prototype_ `void ReleaseUniqueGroupName(FName GroupName);` — Releases a unique group name that is no longer needed. It will be recycled the next time one is needed
- L54 _public prototype_ `virtual void PreUpdate(UE::UAF::FExecutionContext& Context) override;` — FGraphInstanceComponent impl
- L55 _public prototype_ `virtual void PostUpdate(UE::UAF::FExecutionContext& Context) override;`
- L59 _private member_ `TMap<FName, int32> SyncGroupMap;` — A map of sync group name -> group index
- L62 _private member_ `TArray<UE::UAF::Private::FSyncGroupState> SyncGroups;` — A list of groups and their data
- L65 _private member_ `UE::UAF::Private::FSyncGroupUniqueName* FirstFreeUniqueGroupName = nullptr;` — The first free unique group name
- L68 _private member_ `TMap<FName, UE::UAF::Private::FSyncGroupUniqueName*> UsedUniqueGroupNames;` — The map of currently used group names
- L71 _private member_ `int32 UniqueGroupNameCounter = 0;` — A counter tracking the next unique group name to allocate

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Graph/UAFAnimGraphInitializerComponent.h` (Private)


#### struct `FUAFAnimGraphInitializerComponent`  
`struct FUAFAnimGraphInitializerComponent : public FUAFGraphInstanceComponent`  
_L18-33_
- reflection: `USTRUCT(meta=(Hidden, Abstract))`
- inherits: `FUAFGraphInstanceComponent`
- desc: Internal component used for initial UAF graph setup
- L23 _public prototype_ `FUAFAnimGraphInitializerComponent() = default;`
- L24 _public function_ `explicit FUAFAnimGraphInitializerComponent(FAnimNextFactoryParams&& InFactoryParams) : FactoryParams(MoveTemp(InFactoryParams))`
- L29 _public member_ `FAnimNextFactoryParams FactoryParams;` — Factory params used to construct the graph instance
- L32 _public member_ `TArray<UE::UAF::FUniqueAnimGraphTask> TaskQueue;` — Tasks queue to be applied on construction

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFAnimGraphInitializerComponent> : public TStructOpsTypeTraitsBase2<FUAFAnimGraphInitializerComponent>`  
_L36-42_
- inherits: `TStructOpsTypeTraitsBase2<FUAFAnimGraphInitializerComponent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L39-41_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L40 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon24a091de0103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/GraphInterfaces/AnimNextNativeDataInterface_AnimSequencePlayer.h` (Private)


#### struct `FAnimNextNativeDataInterface_AnimSequencePlayer`  
`struct FAnimNextNativeDataInterface_AnimSequencePlayer : public FAnimNextNativeDataInterface`  
_L16-41_
- reflection: `USTRUCT()`
- inherits: `FAnimNextNativeDataInterface`
- desc: DEPRECATED - no longer in use
- L21 _public prototype_ `virtual void BindToFactoryObject(const FBindToFactoryObjectContext& InContext) override;` — FAnimNextNativeDataInterface interface
- L23 _public function_ `virtual const UScriptStruct* GetUpgradeTraitStruct() const`
- L28 _public member_ `TObjectPtr<const UAnimSequence> AnimSequence;` — `UPROPERTY()` — The animation object to play
- L32 _public member_ `double PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Anim Sequence", meta = (EnableCategories))` — The play rate to use
- L36 _public member_ `double StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Anim Sequence", meta = (EnableCategories))` — The timeline's start position
- L40 _public member_ `bool Loop = false;` — `UPROPERTY(EditAnywhere, Category = "Anim Sequence", meta = (EnableCategories))` — Whether to loop the animation

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/GraphInterfaces/AnimNextNativeDataInterface_BlendSpacePlayer.h` (Private)


#### struct `FAnimNextNativeDataInterface_BlendSpacePlayer`  
`struct FAnimNextNativeDataInterface_BlendSpacePlayer : public FAnimNextNativeDataInterface`  
_L16-49_
- reflection: `USTRUCT()`
- inherits: `FAnimNextNativeDataInterface`
- desc: DEPRECATED - no longer in use
- L21 _public prototype_ `virtual void BindToFactoryObject(const FBindToFactoryObjectContext& InContext) override;` — FAnimNextNativeDataInterface interface
- L23 _public function_ `virtual const UScriptStruct* GetUpgradeTraitStruct() const`
- L28 _public member_ `TObjectPtr<const UBlendSpace> BlendSpace;` — `UPROPERTY()` — The animation object to play
- L32 _public member_ `double XAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space", meta = (EnableCategories))` — The location on the x-axis to sample.
- L36 _public member_ `double YAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space", meta = (EnableCategories))` — The location on the y-axis to sample.
- L40 _public member_ `double PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space", meta = (EnableCategories))` — The play rate to use
- L44 _public member_ `double StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space", meta = (EnableCategories))` — The timeline's start position. This is normalized in the [0,1] range.
- L48 _public member_ `bool Loop = false;` — `UPROPERTY(EditAnywhere, Category = "Blend Space", meta = (EnableCategories))` — Whether to loop the animation

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/GraphInterfaces/AnimNextNativeDataInterface_SynchronizeUsingGroups.h` (Private)


#### struct `FAnimNextNativeDataInterface_SynchronizeUsingGroups`  
`struct FAnimNextNativeDataInterface_SynchronizeUsingGroups : public FAnimNextNativeDataInterface`  
_L16-42_
- reflection: `USTRUCT()`
- inherits: `FAnimNextNativeDataInterface`
- desc: DEPRECATED - no longer in use
- L22 _public function_ `virtual const UScriptStruct* GetUpgradeTraitStruct() const`
- L28 _public member_ `FName GroupName;` — `UPROPERTY(EditAnywhere, Category = "Group Synchronization", meta = (EnableCategories))` — The group name If no name is provided, no synchronization occurs
- L32 _public member_ `EAnimGroupSynchronizationRole GroupRole = EAnimGroupSynchronizationRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = "Group Synchronization", meta = (EnableCategories))` — The role this player can assume within the group
- L36 _public member_ `EAnimGroupSynchronizationMode SyncMode = EAnimGroupSynchronizationMode::NoSynchronization;` — `UPROPERTY(EditAnywhere, Category = "Group Synchronization", meta = (EnableCategories))` — The synchronization mode
- L41 _public member_ `bool MatchSyncPoint = true;` — `UPROPERTY(EditAnywhere, Category = "Group Synchronization", meta = (EnableCategories))` — Whether or not to match the group sync point when joining as leader When disabled, the leader will snap the position of the group to its current position

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Injection/AnimNextModuleInjectionComponent.h` (Private)


#### struct `FAnimNextModuleInjectionComponent`  
`struct FAnimNextModuleInjectionComponent : public FUAFModuleInstanceComponent`  
_L22-69_
- reflection: `USTRUCT()`
- inherits: `FUAFModuleInstanceComponent`
- desc: Module component that holds info about injection sites and routes injection requests
- L25 _public function_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT()`
- L30 _public prototype_ `void AddStructReferencedObjects(class FReferenceCollector& Collector);`
- L34 _private prototype_ `virtual void OnTraitEvent(FAnimNextTraitEvent& Event) override;` — FUAFModuleInstanceComponent interface
- L36 _private prototype_ `void OnInjectionEvent(UE::UAF::FInjection_InjectEvent& InEvent);`
- L37 _private prototype_ `void OnUninjectionEvent(UE::UAF::FInjection_UninjectEvent& InEvent);`
- L39 _private prototype_ `static void OnReapplyInjection(const UE::UAF::FModuleTaskContext& InContext);`
- L41 _private prototype_ `uint32 IncrementSerialNumber();`
- L45 _private prototype_ `virtual void OnBindToInstance() override;` — FUAFAssetInstanceComponent interface
- L48 _private member_ `UE::UAF::FInjectionInfo InjectionInfo;` — Info for injection
- L65 _private member_ `TMap<FAnimNextVariableReference, FInjectionRecord> CurrentRequests;` — Currently-injected requests
- L68 _private member_ `uint32 SerialNumber = 0;` — Serial number used to identify forwarded requests

#### struct `FAnimNextModuleInjectionComponent::FInjectionRecord`  
`struct FInjectionRecord`  
_L50-62_
- L52 _public function_ `bool IsValid() const`
- L57 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L59 _public member_ `TSharedPtr<UE::UAF::FInjectionRequest> GraphRequest;`
- L60 _public member_ `TSharedPtr<UE::UAF::FInjectionRequest> ModifierRequest;`
- L61 _public member_ `uint32 SerialNumber = 0;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextModuleInjectionComponent> : public TStructOpsTypeTraitsBase2<FAnimNextModuleInjectionComponent>`  
_L72-78_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextModuleInjectionComponent>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L75-77_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L76 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon926ab6a50103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Injection/GraphInstanceInjectionComponent.h` (Private)


#### struct `FGraphInstanceInjectionComponent`  
`struct FGraphInstanceInjectionComponent : public FUAFGraphInstanceComponent`  
_L15-30_
- reflection: `USTRUCT()`
- inherits: `FUAFGraphInstanceComponent`
- desc: FGraphInstanceInjectionComponent This component maintains injection info for a graph
- L18 _public function_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT() const UE::UAF::FInjectionInfo& GetInjectionInfo() const`
- L27 _private prototype_ `virtual void OnBindToInstance() override;` — FUAFAssetInstanceComponent interface
- L29 _private member_ `UE::UAF::FInjectionInfo InjectionInfo;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Injection/InjectionEvents.h` (Private)


#### struct `UE::UAF::FInjection_InjectEvent`  
`struct FInjection_InjectEvent : public FAnimNextTraitEvent`  
_L23-34_
- inherits: `FAnimNextTraitEvent`
- desc: Injection Inject Event Event raised when an injection request is made. It encapsulates everything needed to service an injection request. If no valid data is provided, this event will request that the input source plays instead.
- L25 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FInjection_PlayEvent, FAnimNextTraitEvent) FInjectionRequestPtr Request;`
- L29 _public member_ `int32 SerialNumber = 0;`
- L33 _protected prototype_ `virtual void OnExpired(FTraitEventList& OutputEventList) override;` — FAnimNextTraitEvent impl

#### struct `UE::UAF::FInjection_UninjectEvent`  
`struct FInjection_UninjectEvent : public FAnimNextTraitEvent`  
_L41-48_
- inherits: `FAnimNextTraitEvent`
- desc: Injection Uninject Event Event raised when an uninject request is made.
- L43 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FInjection_StopEvent, FAnimNextTraitEvent) FInjectionRequestPtr Request;`
- L47 _public member_ `int32 SerialNumber = 0;`

#### struct `UE::UAF::FInjection_StatusUpdateEvent`  
`struct FInjection_StatusUpdateEvent : public FAnimNextModule_ActionEvent`  
_L55-67_
- inherits: `FAnimNextModule_ActionEvent`
- desc: Injection Status Update Event raised when the status of a request changes.
- L57 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FInjection_StatusUpdateEvent, FAnimNextModule_ActionEvent)`
- L63 _public member_ `FInjectionRequestPtr Request;` — The request to update
- L66 _public member_ `EInjectionStatus Status = EInjectionStatus::None;` — The current request status

#### struct `UE::UAF::FInjection_TimelineUpdateEvent`  
`struct FInjection_TimelineUpdateEvent : public FAnimNextModule_ActionEvent`  
_L74-86_
- inherits: `FAnimNextModule_ActionEvent`
- desc: Injection Timeline Update Event raised when a request is playing with its updated timeline progress.
- L76 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FInjection_TimelineUpdateEvent, FAnimNextModule_ActionEvent)`
- L82 _public member_ `FInjectionRequestPtr Request;` — The request to update
- L85 _public member_ `FTimelineState TimelineState;` — The current request timeline state

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Injection/InjectionInfo.h` (Private)


#### struct `UE::UAF::FInjectionInfo`  
`struct FInjectionInfo`  
_L18-49_
- desc: Info used to track injection sites for an AnimNext instance (graph, module etc)
- L20 _public prototype_ `FInjectionInfo() = default;`
- L22 _public prototype_ `explicit FInjectionInfo(const FUAFAssetInstance& InInstance);`
- L25 _public function_ `FAnimNextVariableReference GetDefaultInjectionSite() const` — Get the default injection site
- L33 _public prototype_ `FAnimNextVariableReference FindInjectionSite(const FInjectionSite& InSite) const;` — Find an injectable graph variable by name. @param   InSite            The injection site. @return The actual injection site we found (in the case an injection site of None was passed)
- L36 _private prototype_ `void CacheInfo() const;`
- L42 _private member_ `mutable TArray<FAnimNextVariableReference> InjectionSites;` — All injection site variables
- L45 _private member_ `const FUAFAssetInstance* Instance = nullptr;` — Instance we are tracking
- L48 _private member_ `mutable FAnimNextVariableReference DefaultInjectionSite;` — The default injection site for our instance (user-adjustable via SetDefaultInjectionSite)

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L15 _typedef_ `using FInjectionSite = FAnimNextInjectionSite;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/PlayAnim/PlayAnimSlotTrait.h` (Private)


#### struct `FAnimNextPlayAnimSlotTraitSharedData`  
`struct FAnimNextPlayAnimSlotTraitSharedData : public FAnimNextTraitSharedData`  
_L21-39_
- reflection: `USTRUCT(meta = (DisplayName = "PlayAnim Slot", Hidden))`
- inherits: `FAnimNextTraitSharedData`
- L27 _public member_ `FAnimNextTraitHandle Source;` — `UPROPERTY()` — Default input when no animation request has been made on this slot.
- L31 _public member_ `FName SlotName;` — `UPROPERTY(EditAnywhere, Category = "Default")` — The name of this slot that the PlayAnim API refers to.

#### struct `UE::UAF::FPlayAnimSlotTrait`  
`struct FPlayAnimSlotTrait : FBaseTrait, IUpdate, IUpdateTraversal, IHierarchy, IDiscreteBlend, ISmoothBlend, IInertializerBlend, IGarbageCollection`  
_L50-176_
- inherits: `FBaseTrait,IUpdate,IUpdateTraversal,IHierarchy,IDiscreteBlend,ISmoothBlend,IInertializerBlend,IGarbageCollection`
- desc: FPlayAnimSlotTrait A trait that provides a slot onto which a PlayAnim request can be processed. It allows for this trait to act as a pass-through when not actively used and when a PlayAnim request is made to start playing a child instance, we blend to it.
- L127 _public typedef_ `using FSharedData = FAnimNextPlayAnimSlotTraitSharedData;`
- L143 _public prototype_ `static int32 FindFreeRequestIndexOrAdd(FInstanceData& InstanceData);` — Internal impl
- L146 _public prototype_ `ETraitStackPropagation OnInjectEvent(const FExecutionContext& Context, FTraitBinding& Binding, FInjection_InjectEvent& Event) const;` — Event handling impl
- L147 _public prototype_ `ETraitStackPropagation OnUninjectEvent(const FExecutionContext& Context, FTraitBinding& Binding, FInjection_UninjectEvent& Event) const;`
- L150 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L153 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L156 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L157 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L160 _public prototype_ `virtual float GetBlendWeight(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;` — IDiscreteBlend impl
- L161 _public prototype_ `virtual int32 GetBlendDestinationChildIndex(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding) const override;`
- L162 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;`
- L163 _public prototype_ `virtual void OnBlendInitiated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L164 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L167 _public prototype_ `virtual float GetBlendTime(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;` — ISmoothBlend impl
- L168 _public prototype_ `virtual EAlphaBlendOption GetBlendType(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;`
- L169 _public prototype_ `virtual UCurveFloat* GetCustomBlendCurve(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;`
- L172 _public prototype_ `virtual float GetBlendTime(FExecutionContext& Context, const TTraitBinding<IInertializerBlend>& Binding, int32 ChildIndex) const override;` — IInertializerBlend impl
- L175 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### enum `UE::UAF::FPlayAnimSlotTrait::EPlayAnimRequestState`  
`enum class EPlayAnimRequestState : uint8`  
_L55-65_
- desc: Slot request state
- L58 _public enumerator_ `Inactive` — Slot request is inactive
- L61 _public enumerator_ `Active` — Slot request is active and using a sub-graph
- L64 _public enumerator_ `ActiveSource` — Slot request is active and using the source input

#### struct `UE::UAF::FPlayAnimSlotTrait::FPlayAnimPendingRequest`  
`struct FPlayAnimPendingRequest`  
_L67-84_
- L70 _public member_ `FInjectionRequestPtr Request;` — The PlayAnim request
- L73 _public member_ `bool bStop = false;` — Whether or not a Stop request was issued
- L76 _public function_ `bool IsValid() const` — Returns whether or not we have a pending request
- L79 _public function_ `void Reset()` — Resets the pending request

#### struct `UE::UAF::FPlayAnimSlotTrait::FPlayAnimSlotRequest`  
`struct FPlayAnimSlotRequest`  
_L86-125_
- L89 _public member_ `FInjectionRequestPtr Request;` — The PlayAnim request
- L92 _public member_ `FInjectionBlendSettings BlendSettings;` — The blend settings to use
- L95 _public member_ `TObjectPtr<const UUAFAnimGraph> AnimationGraph;` — The module used by the graph instance, as selected by the chooser
- L98 _public member_ `TSharedPtr<FAnimNextGraphInstance> GraphInstance;` — The graph instance
- L102 _public member_ `FTraitPtr ChildPtr;` — Our child handle If we use the source input, this is a strong handle to it, otherwise we are a weak handle to the graph instance's root
- L105 _public member_ `EPlayAnimRequestState State = EPlayAnimRequestState::Inactive;` — The current request state
- L108 _public member_ `bool bWasRelevant = false;` — Whether or not this slot state was previously relevant
- L111 _public prototype_ `void Initialize(FInjectionRequestPtr InRequest, const FInjectionBlendSettings& InBlendSettings, const UUAFAnimGraph* InAnimationGraph);` — Initializes a request to begin playing
- L113 _public function_ `FWeakTraitPtr GetChildPtr() const`

#### struct `UE::UAF::FPlayAnimSlotTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L129-140_
- inherits: `FTrait::FInstanceData`
- L132 _public member_ `TArray<FPlayAnimSlotRequest> SlotRequests;` — List of PlayAnim slot requests
- L135 _public member_ `FPlayAnimPendingRequest PendingRequest;` — PlayAnim pending request
- L139 _public member_ `int32 CurrentlyActiveRequestIndex = INDEX_NONE;` — The index of the currently active request All other requests are blending out

#### Free symbols / members of external scopes

- L34 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/ApplyAdditivePerBoneTrait.h` (Private)


#### struct `UE::UAF::FApplyAdditivePerBoneTrait`  
`struct FApplyAdditivePerBoneTrait : FBaseTrait, IEvaluate, IUpdate, IUpdateTraversal, IHierarchy, IContinuousBlend, IGarbageCollection`  
_L21-55_
- inherits: `FBaseTrait,IEvaluate,IUpdate,IUpdateTraversal,IHierarchy,IContinuousBlend,IGarbageCollection`
- desc: FApplyAdditivePerBone Trait A trait that can apply an additive animation with a hierarchy table based mask
- L25 _public typedef_ `using FSharedData = FApplyAdditivePerBoneTraitSharedData;`
- L38 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L41 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L44 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L47 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L48 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L51 _public prototype_ `virtual float GetBlendWeight(const FExecutionContext& Context, const TTraitBinding<IContinuousBlend>& Binding, int32 ChildIndex) const override;` — IContinuousBlend impl
- L54 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### struct `UE::UAF::FApplyAdditivePerBoneTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L27-34_
- inherits: `FTrait::FInstanceData`
- L29 _public member_ `FTraitPtr Base;`
- L30 _public member_ `FTraitPtr Additive;`
- L32 _public member_ `bool bWasBaseRelevant = false;`
- L33 _public member_ `bool bWasAdditiveRelevant = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/ApplyAdditiveTrait.h` (Private)


#### struct `UE::UAF::FApplyAdditiveTrait`  
`struct FApplyAdditiveTrait : FBaseTrait, IEvaluate, IUpdate, IUpdateTraversal, IHierarchy, IContinuousBlend`  
_L22-57_
- inherits: `FBaseTrait,IEvaluate,IUpdate,IUpdateTraversal,IHierarchy,IContinuousBlend`
- desc: A trait that can apply a mesh or local space additive to this trait stack. Ex: LookAt's, minor hit reactions, up-down floating, etc.
- L26 _public typedef_ `using FSharedData = FAnimNextApplyAdditiveTraitSharedData;`
- L43 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L46 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L49 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L52 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L53 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L56 _public prototype_ `virtual float GetBlendWeight(const FExecutionContext& Context, const TTraitBinding<IContinuousBlend>& Binding, int32 ChildIndex) const override;` — IContinuousBlend impl

#### struct `UE::UAF::FApplyAdditiveTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L28-40_
- inherits: `FTrait::FInstanceData`
- L31 _public member_ `FTraitPtr Base;` — Reference to base for additive we are applying
- L34 _public member_ `FTraitPtr Additive;` — Reference to additive we are applying
- L37 _public member_ `bool bWasAdditiveRelevant = false;` — True if Additive branch has any contribution (Alpha non-zero)
- L39 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/ApplyNamedSetTrait.h` (Private)


#### struct `UE::UAF::FApplyNamedSetTrait`  
`struct FApplyNamedSetTrait : FBaseTrait, IEvaluate, IHierarchy`  
_L21-41_
- inherits: `FBaseTrait,IEvaluate,IHierarchy`
- desc: FApplyNamedSetTrait A trait that applies a new named set to evaluate with. Traits upstream will use the new named set to evaluate. The trait that consumes its output must handle mismatched named sets (e.g. layering).
- L25 _public typedef_ `using FSharedData = FApplyNamedSetSharedData;`
- L35 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L36 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;`
- L39 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L40 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`

#### struct `UE::UAF::FApplyNamedSetTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L27-32_
- inherits: `FTrait::FInstanceData`
- L29 _public member_ `FTraitPtr Input;`
- L31 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/Args/AlphaInputArgCoreTrait.h` (Private)


#### struct `UE::UAF::FAlphaInputArgCoreTrait`  
`struct FAlphaInputArgCoreTrait : FAdditiveTrait, IUpdate, IAlphaInputArgs`  
_L45-72_
- inherits: `FAdditiveTrait,IUpdate,IAlphaInputArgs`
- desc: FAlphaInputArgCoreTrait Additive trait that provides configurable alpha input args for another trait to use. Ex: as a weight. This trait's API calls mutate internal state, so it should not be used by multiple traits concurrently. In particular, curve evaluation will not make sense as curves may differ per trait keyframe & DeltaTime will be updated multiple per consumer trait. Note: Does not implement IContinousBlend as cannot resolve trait-specific child index handling.
- L49 _public typedef_ `using FSharedData = FAlphaInputTraitArgs;`
- L63 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate
- L64 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L67 _public prototype_ `virtual FAlphaInputTraitArgs Get(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;` — IAlphaInputArgs
- L68 _public prototype_ `virtual EAnimAlphaInputType GetAlphaInputType(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L69 _public prototype_ `virtual FName GetAlphaCurveName(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L70 _public prototype_ `virtual float GetCurrentAlphaValue(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L71 _public prototype_ `virtual TFunction<float(float)> GetInputScaleBiasClampCallback(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`

#### struct `UE::UAF::FAlphaInputArgCoreTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L51-60_
- inherits: `FTrait::FInstanceData`
- L53 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;`
- L54 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;`
- L56 _public member_ `float DeltaTime = 0.f;`
- L57 _public member_ `float ComputedAlphaValue = 0.f;`
- L59 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace AlphaInput` (scope `UE::UAF`)
- L15 _prototype_ `extern float ComputeAlphaValueForFloat(FInputScaleBiasClamp& InAlphaScaleBiasClamp , const FInputScaleBias& InAlphaScaleBias , const float InBaseAlpha , const float InDeltaTime);` (scope `UE::UAF::AlphaInput`)
- L20 _prototype_ `extern float ComputeAlphaValueForBool(FInputAlphaBoolBlend& InAlphaBoolBlend , const bool bInAlphaBoolEnabled , const float InDeltaTime);` (scope `UE::UAF::AlphaInput`)
- L24 _prototype_ `extern float ComputeAlphaValueForType(const EAnimAlphaInputType InAlphaInputType , FInputScaleBiasClamp& InAlphaScaleBiasClamp , const FInputScaleBias& InAlphaScaleBias , const float InBaseAlpha , FInputAlphaBoolBlend& InAlphaBoolBlend , const bool bInAlphaBoolEnabled , const float InDeltaTime);` (scope `UE::UAF::AlphaInput`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/Args/BoolAlphaInputArgTrait.h` (Private)


#### struct `FBoolAlphaInputTraitArgs`  
`struct FBoolAlphaInputTraitArgs : public FAnimNextTraitSharedData`  
_L14-31_
- reflection: `USTRUCT(meta = (DisplayName = "Bool Alpha Input Args"))`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `bool bAlphaBoolEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "bEnabled"))`
- L22 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden, DisplayName = "Blend Settings"))`

#### struct `UE::UAF::FBoolAlphaInputArgTrait`  
`struct FBoolAlphaInputArgTrait : FAdditiveTrait, IUpdate, IAlphaInputArgs`  
_L40-63_
- inherits: `FAdditiveTrait,IUpdate,IAlphaInputArgs`
- desc: FBoolAlphaInputArgTrait See 'FAlphaInputArgCoreTrait'. Bool input only version.
- L44 _public typedef_ `using FSharedData = FBoolAlphaInputTraitArgs;`
- L56 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate
- L57 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L60 _public prototype_ `virtual FAlphaInputTraitArgs Get(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;` — IAlphaInputArgs
- L61 _public prototype_ `virtual EAnimAlphaInputType GetAlphaInputType(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L62 _public prototype_ `virtual float GetCurrentAlphaValue(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`

#### struct `UE::UAF::FBoolAlphaInputArgTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L46-53_
- inherits: `FTrait::FInstanceData`
- L48 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;`
- L50 _public member_ `float ComputedAlphaValue = 0.f;`
- L52 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L25 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/Args/CurveAlphaInputArgTrait.h` (Private)


#### struct `FCurveAlphaInputTraitArgs`  
`struct FCurveAlphaInputTraitArgs : public FAnimNextTraitSharedData`  
_L14-31_
- reflection: `USTRUCT(meta = (DisplayName = "Curve Alpha Input Args"))`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden, DisplayAfter = "AlphaCurveName"))`
- L23 _public member_ `FName AlphaCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Note: For curve types, the additive branch will always be evaluated. Curve weight blending will occur at task evaluation time.

#### struct `UE::UAF::FCurveAlphaInputArgTrait`  
`struct FCurveAlphaInputArgTrait : FAdditiveTrait, IUpdate, IAlphaInputArgs`  
_L41-65_
- inherits: `FAdditiveTrait,IUpdate,IAlphaInputArgs`
- desc: FCurveAlphaInputArgTrait See 'FAlphaInputArgCoreTrait'. Curve input only version.
- L45 _public typedef_ `using FSharedData = FCurveAlphaInputTraitArgs;`
- L57 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate
- L58 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L61 _public prototype_ `virtual FAlphaInputTraitArgs Get(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;` — IAlphaInputArgs
- L62 _public prototype_ `virtual EAnimAlphaInputType GetAlphaInputType(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L63 _public prototype_ `virtual FName GetAlphaCurveName(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L64 _public prototype_ `virtual TFunction<float(float)> GetInputScaleBiasClampCallback(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`

#### struct `UE::UAF::FCurveAlphaInputArgTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L47-54_
- inherits: `FTrait::FInstanceData`
- L49 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;`
- L51 _public member_ `float DeltaTime = 0.f;`
- L53 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L26 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/Args/FloatAlphaInputArgTrait.h` (Private)


#### struct `FFloatAlphaInputTraitArgs`  
`struct FFloatAlphaInputTraitArgs : public FAnimNextTraitSharedData`  
_L14-33_
- reflection: `USTRUCT(meta = (DisplayName = "Float Alpha Input Args"))`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `float Alpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden))`
- L25 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden))`

#### struct `UE::UAF::FFloatAlphaInputArgTrait`  
`struct FFloatAlphaInputArgTrait : FAdditiveTrait, IUpdate, IAlphaInputArgs`  
_L43-66_
- inherits: `FAdditiveTrait,IUpdate,IAlphaInputArgs`
- desc: FFloatAlphaInputArgTrait See 'FAlphaInputArgCoreTrait'. Float input only version.
- L47 _public typedef_ `using FSharedData = FFloatAlphaInputTraitArgs;`
- L59 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate
- L60 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L63 _public prototype_ `virtual FAlphaInputTraitArgs Get(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;` — IAlphaInputArgs
- L64 _public prototype_ `virtual EAnimAlphaInputType GetAlphaInputType(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L65 _public prototype_ `virtual float GetCurrentAlphaValue(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`

#### struct `UE::UAF::FFloatAlphaInputArgTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L49-56_
- inherits: `FTrait::FInstanceData`
- L51 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;`
- L53 _public member_ `float ComputedAlphaValue = 0.f;`
- L55 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L28 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/Args/SimpleFloatAlphaInputArgTrait.h` (Private)


#### struct `FSimpleFloatAlphaInputTraitArgs`  
`struct FSimpleFloatAlphaInputTraitArgs : public FAnimNextTraitSharedData`  
_L14-27_
- reflection: `USTRUCT(meta = (DisplayName = "Simple Float Alpha Input Args"))`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `float Alpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### struct `UE::UAF::FSimpleFloatAlphaInputArgTrait`  
`struct FSimpleFloatAlphaInputArgTrait : FAdditiveTrait, IAlphaInputArgs`  
_L37-51_
- inherits: `FAdditiveTrait,IAlphaInputArgs`
- desc: FSimpleFloatAlphaInputArgTrait See 'FAlphaInputArgCoreTrait'. Simple Float input only version. Alpha is always updated.
- L41 _public typedef_ `using FSharedData = FSimpleFloatAlphaInputTraitArgs;`
- L48 _public prototype_ `virtual FAlphaInputTraitArgs Get(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;` — IAlphaInputArgs
- L49 _public prototype_ `virtual EAnimAlphaInputType GetAlphaInputType(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`
- L50 _public prototype_ `virtual float GetCurrentAlphaValue(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const override;`

#### struct `UE::UAF::FSimpleFloatAlphaInputArgTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L43-45_
- inherits: `FTrait::FInstanceData`

#### Free symbols / members of external scopes

- L22 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/BlendInertializer.h` (Private)


#### struct `FAnimNextBlendInertializerCoreTraitSharedData`  
`struct FAnimNextBlendInertializerCoreTraitSharedData : public FAnimNextTraitSharedData`  
_L19-24_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Inertializer Core", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that converts a normal smooth blend into an inertializing blend. It only implements the inertializing logic, it queries its required arguments using the IInertializerBlend interface.

#### struct `FAnimNextBlendInertializerTraitSharedData`  
`struct FAnimNextBlendInertializerTraitSharedData : public FAnimNextBlendInertializerCoreTraitSharedData`  
_L31-38_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Inertializer", ShowTooltip=true))`
- inherits: `FAnimNextBlendInertializerCoreTraitSharedData`
- desc: A trait that converts a normal smooth blend into an inertializing blend. This trait implements both the logic and contains the arguments necessary.
- L37 _public member_ `float BlendTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))` — Inertialization Blend Time

#### struct `UE::UAF::FBlendInertializerCoreTrait`  
`struct FBlendInertializerCoreTrait : FAdditiveTrait, IDiscreteBlend, ISmoothBlend`  
_L48-63_
- inherits: `FAdditiveTrait,IDiscreteBlend,ISmoothBlend`
- desc: FBlendInertializerCoreTrait A trait that converts a normal smooth blend into an inertializing blend. It only implements the inertializing logic, it queries its required arguments using the IInertializerBlend interface.
- L52 _public typedef_ `using FSharedData = FAnimNextBlendInertializerCoreTraitSharedData;`
- L55 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;` — IDiscreteBlend impl
- L58 _public prototype_ `virtual float GetBlendTime(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;` — ISmoothBlend impl
- L61 _public function_ `virtual bool IsHidden() const override`

#### struct `UE::UAF::FBlendInertializerTrait`  
`struct FBlendInertializerTrait : FBlendInertializerCoreTrait, IInertializerBlend`  
_L71-86_
- inherits: `FBlendInertializerCoreTrait,IInertializerBlend`
- desc: FBlendInertializerTrait A trait that converts a normal smooth blend into an inertializing blend. This trait implements both the logic and contains the arguments necessary.
- L75 _public typedef_ `using FSharedData = FAnimNextBlendInertializerTraitSharedData;`
- L81 _public prototype_ `virtual float GetBlendTime(FExecutionContext& Context, const TTraitBinding<IInertializerBlend>& Binding, int32 ChildIndex) const override;` — IInertializerBlend impl
- L84 _public function_ `virtual bool IsHidden() const override` — overrdie the base, as it is hidden

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/BlendLayer.h` (Private)


#### struct `UE::UAF::FBlendLayerTrait`  
`struct FBlendLayerTrait : FBaseTrait, IEvaluate, IUpdate, IUpdateTraversal, IHierarchy, IContinuousBlend`  
_L22-54_
- inherits: `FBaseTrait,IEvaluate,IUpdate,IUpdateTraversal,IHierarchy,IContinuousBlend`
- desc: FBlendLayerTrait A trait that can blend a layer into an input.
- L27 _public typedef_ `using FSharedData = FUAFBlendLayerTraitSharedData;`
- L40 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L43 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L46 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L49 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L50 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L53 _public prototype_ `virtual float GetBlendWeight(const FExecutionContext& Context, const TTraitBinding<IContinuousBlend>& Binding, int32 ChildIndex) const override;` — IContinuousBlend impl

#### struct `UE::UAF::FBlendLayerTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L29-36_
- inherits: `FTrait::FInstanceData`
- L31 _public member_ `FTraitPtr ChildBase;`
- L32 _public member_ `FTraitPtr ChildBlend;`
- L34 _public member_ `bool bWasChildBaseRelevant = false;`
- L35 _public member_ `bool bWasChildBlendRelevant = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/BlendSmootherPerBone.h` (Private)


#### struct `FUAFBlendSmootherPerBoneTraitSharedData`  
`struct FUAFBlendSmootherPerBoneTraitSharedData : public FAnimNextBlendSmootherPerBoneCoreTraitSharedData`  
_L22-28_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Smoother Per Bone"))`
- inherits: `FAnimNextBlendSmootherPerBoneCoreTraitSharedData`
- L27 _public member_ `TArray<TObjectPtr<UUAFBlendProfile>> BlendProfiles;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))`

#### struct `UE::UAF::FBlendSmootherPerBoneCoreTrait`  
`struct FBlendSmootherPerBoneCoreTrait : FAdditiveTrait, IEvaluate, IUpdate, IDiscreteBlend`  
_L37-93_
- inherits: `FAdditiveTrait,IEvaluate,IUpdate,IDiscreteBlend`
- desc: FBlendSmootherPerBoneCoreTrait An additive trait that smoothly blends with per-bone weights.
- L41 _public typedef_ `using FSharedData = FAnimNextBlendSmootherPerBoneCoreTraitSharedData;`
- L75 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L78 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L81 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;` — IDiscreteBlend impl
- L82 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const;`
- L85 _public function_ `virtual bool IsHidden() const override`
- L90 _private prototype_ `static void InitializeInstanceData(FExecutionContext& Context, const FTraitBinding& Binding, const FSharedData* SharedData, FInstanceData* InstanceData);` — Internal impl
- L91 _private prototype_ `static void SetBlendProfileSkeleton(const USkeleton* Skeleton, const FSharedData* SharedData, FInstanceData* InstanceData);`
- L92 _private prototype_ `static void NormalizeChildPerBoneWeights(TNonNullPtr<FInstanceData> InstanceData);`

#### struct `UE::UAF::FBlendSmootherPerBoneCoreTrait::FBlendData`  
`struct FBlendData`  
_L44-55_
- desc: Struct for tracking blends for each pose
- L48 _public member_ `const UUAFBlendProfile* BlendProfile = nullptr;` — The blend profile to use to blend this child in with All blend profiles must use the same skeleton
- L51 _public member_ `float OldWeight = 0.0f;` — The cached value of this child's weight last update
- L54 _public member_ `bool bIsBlending = false;` — Flag to skip a child if its fully blended out

#### struct `UE::UAF::FBlendSmootherPerBoneCoreTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L57-72_
- inherits: `FTrait::FInstanceData`
- L59 _public member_ `TArray<FBlendData> PerChildBlendData;`
- L62 _public member_ `TArray<FBlendSampleData> PerBoneSampleData;` — Per-bone blending data for each child
- L65 _public member_ `TArray<float> PerBoneTotals;` — Scratch data for norma
- L68 _public member_ `TArray<int32> ChildOrdering;` — The ordering of children
- L71 _public member_ `const USkeleton* BlendProfileSkeleton;` — The common skeleton all blend profiles must share

#### struct `UE::UAF::FBlendSmootherPerBoneTrait`  
`struct FBlendSmootherPerBoneTrait : public FBlendSmootherPerBoneCoreTrait, ISmoothBlendPerBone`  
_L95-103_
- inherits: `FBlendSmootherPerBoneCoreTrait,ISmoothBlendPerBone`
- L99 _public typedef_ `using FSharedData = FUAFBlendSmootherPerBoneTraitSharedData;`
- L102 _public prototype_ `virtual const UUAFBlendProfile* GetBlendProfile(FExecutionContext& Context, const TTraitBinding<ISmoothBlendPerBone>& Binding, int32 ChildIndex) const override;` — ISmoothBlendPerBone

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/BlendSpacePlayer.h` (Private)


#### struct `UE::UAF::FBlendSpacePlayerTrait`  
`struct FBlendSpacePlayerTrait : FBaseTrait, IEvaluate, IUpdate, IUpdateTraversal, IHierarchy, ITimeline, IContinuousBlend, IGarbageCollection`  
_L24-94_
- inherits: `FBaseTrait,IEvaluate,IUpdate,IUpdateTraversal,IHierarchy,ITimeline,IContinuousBlend,IGarbageCollection`
- desc: FBlendSpacePlayerTrait A trait that can play a blend space
- L28 _public typedef_ `using FSharedData = FAnimNextBlendSpacePlayerTraitSharedData;`
- L72 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L75 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L76 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L79 _public prototype_ `virtual float GetBlendWeight(const FExecutionContext& Context, const TTraitBinding<IContinuousBlend>& Binding, int32 ChildIndex) const override;` — IContinuousBlend impl
- L82 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L83 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L86 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L89 _public prototype_ `virtual bool GetState(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineState& OutTimelineState) const override;` — ITimeline impl
- L92 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### struct `UE::UAF::FBlendSpacePlayerTrait::FSampleGraphState`  
`struct FSampleGraphState`  
_L30-49_
- L33 _public member_ `TSharedPtr<FAnimNextGraphInstance> Instance;` — The graph instance
- L37 _public member_ `FTraitPtr ChildPtr;` — Our child handle Weak handle to the graph instance's root
- L40 _public member_ `float Weight = 0.0f;` — The weight of this sample
- L43 _public member_ `float DeltaTime = 0.0f;` — The scaled delta time for this sample
- L45 _public member_ `bool bSampledLastFrame = false;`
- L47 _public member_ `bool bSampledThisFrame = false;`

#### struct `UE::UAF::FBlendSpacePlayerTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L51-69_
- inherits: `FTrait::FInstanceData`
- L54 _public member_ `TArray<FSampleGraphState> SampleGraphs;` — List of anim next graphs that represent each sample in the blend space
- L57 _public member_ `TObjectPtr<const UBlendSpace> BlendSpace;` — Cached value of the blend space we are playing
- L60 _public member_ `TArray<FBlendSampleData> BlendSamplesData;` — Cached blend samples updated by task and used to interpolate between points over time
- L63 _public member_ `int32 CachedTriangulationIndex = INDEX_NONE;` — Previous position in the triangulation/segmentation
- L66 _public member_ `FBlendFilter BlendFilter;` — Filter used to dampen coordinate changes
- L68 _public member_ `int32 NumChildren = 0;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/BlendTwoWay.h` (Private)


#### struct `UE::UAF::FBlendTwoWayTrait`  
`struct FBlendTwoWayTrait : FBaseTrait, IEvaluate, IUpdate, IUpdateTraversal, IHierarchy, IContinuousBlend`  
_L21-54_
- inherits: `FBaseTrait,IEvaluate,IUpdate,IUpdateTraversal,IHierarchy,IContinuousBlend`
- desc: FBlendTwoWayTrait A trait that can blend two inputs.
- L25 _public typedef_ `using FSharedData = FAnimNextBlendTwoWayTraitSharedData;`
- L40 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L43 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L46 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L49 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L50 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L53 _public prototype_ `virtual float GetBlendWeight(const FExecutionContext& Context, const TTraitBinding<IContinuousBlend>& Binding, int32 ChildIndex) const override;` — IContinuousBlend impl

#### struct `UE::UAF::FBlendTwoWayTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L27-37_
- inherits: `FTrait::FInstanceData`
- L29 _public member_ `FTraitPtr ChildA;`
- L30 _public member_ `FTraitPtr ChildB;`
- L32 _public member_ `bool bIsChildANewlyRelevant : 1 = false;`
- L33 _public member_ `bool bIsChildBNewlyRelevant : 1 = false;`
- L35 _public member_ `bool bWasChildARelevant : 1 = false;`
- L36 _public member_ `bool bWasChildBRelevant : 1 = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/CopyBonesComponentSpace.h` (Private)


#### struct `FAnimNextCopyBonesComponentSpaceTraitSharedData`  
`struct FAnimNextCopyBonesComponentSpaceTraitSharedData : public FAnimNextTraitSharedData`  
_L15-22_
- reflection: `USTRUCT(meta = (DisplayName = "Copy Bones in Component Space", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that allows you to copy bone transforms in component space.
- L21 _public member_ `TArray<FAnimNextBoneMapping> BoneMapping;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline))` — Bones to copy transforms between

#### struct `UE::UAF::FCopyBonesComponentSpaceTrait`  
`struct FCopyBonesComponentSpaceTrait : FAdditiveTrait, IEvaluate`  
_L31-41_
- inherits: `FAdditiveTrait,IEvaluate`
- desc: FCopyBonesComponentSpaceTrait A trait that allows bone transforms to be copied in component space.
- L35 _public typedef_ `using FSharedData = FAnimNextCopyBonesComponentSpaceTraitSharedData;`
- L40 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### struct `UE::UAF::FCopyBonesComponentSpaceTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L37-37_
- inherits: `FTrait::FInstanceData`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/InertializationDeadBlend.h` (Private)


#### struct `FAnimNextInertializationDeadBlendTraitSharedData`  
`struct FAnimNextInertializationDeadBlendTraitSharedData : public FAnimNextTraitSharedData`  
_L21-88_
- reflection: `USTRUCT(meta = (DisplayName = "Dead Blending", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that inertializes animation by extrapolating from the point of transition.
- L27 _public member_ `float DefaultBlendDuration = 0.25f;` — `UPROPERTY(EditAnywhere, Category = Blending, meta = (Inline))` — The default blend duration to use when "Always Use Default Blend Settings" is set to true.
- L31 _public member_ `EAlphaBlendOption DefaultBlendMode = EAlphaBlendOption::Linear;` — `UPROPERTY(EditAnywhere, Category = Blending, meta = (Inline))` — Default blend mode to use when no blend mode is supplied with the inertialization request.
- L35 _public member_ `TObjectPtr<UCurveFloat> DefaultCustomBlendCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = Blending, meta = (Inline))` — Default custom blend curve to use along with the default blend mode.
- L43 _public member_ `float ExtrapolationHalfLife = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Extrapolation, meta = (Inline, Min = "0.0", UIMin = "0.0"), DisplayName = "Extrapolation Half Life")` — The average half-life of decay in seconds to use when extrapolating the animation. To get the final half-life of decay, this value will be scaled by the amount to which the velocities of the animation being transitioned from are moving toward the animation being transitioned to.
- L51 _public member_ `float ExtrapolationHalfLifeMin = 0.05f;` — `UPROPERTY(EditAnywhere, Category = Extrapolation, meta = (Inline, Min = "0.0", UIMin = "0.0"), DisplayName = "Minimum Extrapolation Half Life")` — The minimum half-life of decay in seconds to use when extrapolating the animation. This will be used when the velocities of the animation being transitioned from are very small or moving away from the animation being transitioned to.
- L59 _public member_ `float ExtrapolationHalfLifeMax = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Extrapolation, meta = (Inline, Min = "0.0", UIMin = "0.0"), DisplayName = "Maximum Extrapolation Half Life")` — The maximum half-life of decay in seconds to use when extrapolating the animation. This will dictate the longest decay duration possible when velocities of the animation being transitioned from are small and moving towards the animation being transitioned to.
- L66 _public member_ `float MaximumTranslationVelocity = 500.0f;` — `UPROPERTY(EditAnywhere, Category = Extrapolation, meta = (Inline, Min = "0.0", UIMin = "0.0"))` — The maximum velocity to allow for extrapolation of bone translations in centimeters per second. Smaller values may help prevent the pose breaking during blending but too small values can make the blend less smooth.
- L73 _public member_ `float MaximumRotationVelocity = 360.0f;` — `UPROPERTY(EditAnywhere, Category = Extrapolation, meta = (Inline, Min = "0.0", UIMin = "0.0"))` — The maximum velocity to allow for extrapolation of bone rotations in degrees per second. Smaller values may help prevent the pose breaking during blending but too small values can make the blend less smooth.
- L80 _public member_ `float MaximumScaleVelocity = 4.0f;` — `UPROPERTY(EditAnywhere, Category = Extrapolation, meta = (Inline, Min = "0.0", UIMin = "0.0"))` — The maximum velocity to allow for extrapolation of bone scales. Smaller values may help prevent the pose breaking during blending but too small values can make the blend less smooth.
- L87 _public member_ `float MaximumCurveVelocity = 100.0f;` — `UPROPERTY(EditAnywhere, Category = Extrapolation, meta = (Inline, Min = "0.0", UIMin = "0.0"))` — The maximum velocity to allow for extrapolation of curves. Smaller values may help prevent extreme curve values during blending but too small values can make the blending of curves less smooth.

#### struct `UE::UAF::FInertializationDeadBlendTrait`  
`struct FInertializationDeadBlendTrait : FAdditiveTrait, IUpdate, IEvaluate`  
_L97-141_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate`
- desc: FInertializationDeadBlendTrait A trait that inertializes animation by extrapolating from the point of transition.
- L101 _public typedef_ `using FSharedData = FAnimNextInertializationDeadBlendTraitSharedData;`
- L133 _public prototype_ `ETraitStackPropagation OnInertializationRequestEvent(const FExecutionContext& Context, FTraitBinding& Binding, FAnimNextInertializationRequestEvent& Event) const;` — InertializationRequestTrait handler
- L136 _public prototype_ `virtual void PostUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L139 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### struct `UE::UAF::FInertializationDeadBlendTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L103-130_
- inherits: `FTrait::FInstanceData`
- L106 _public member_ `bool bRequestPending = false;` — Pending request details
- L107 _public member_ `FInertializationRequest PendingRequest;`
- L110 _public member_ `bool bRequestActive = false;` — Current active request details
- L111 _public member_ `FInertializationRequest ActiveRequest;`
- L114 _public member_ `float TimeSinceTransition = 0.0f;` — Time since the last transition
- L117 _public member_ `float EvaluateDeltaTime = 0.0f;` — Delta Time since the last evaluation
- L120 _public member_ `float PoseDeltaTime = 0.0f;` — Delta Time between the storage of Curr and Prev Poses
- L123 _public member_ `FTransformArraySoAHeap CurrPose;` — Recorded Current Pose State
- L126 _public member_ `FTransformArraySoAHeap PrevPose;` — Recorded Previous Pose State
- L129 _public member_ `FDeadBlendingState State;` — Extrapolation State Data

#### Free symbols / members of external scopes

- L90 _namespace_ `namespace UE`
- L90 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/InlineSubGraph.h` (Private)


#### struct `UE::UAF::FUAFInlineSubGraphTrait`  
`struct FUAFInlineSubGraphTrait : FBaseTrait , IUpdate , IUpdateTraversal , IHierarchy , IDiscreteBlend , IGarbageCollection`  
_L27-111_
- inherits: `FBaseTrait,IUpdate,IUpdateTraversal,IHierarchy,IDiscreteBlend,IGarbageCollection`
- desc: FUAFInlineSubGraphTrait A trait that hosts and manages a sub-graph instance while maintaining a set of inline child handles that act as passthrough connections to the outer owning graph. Each blending slot owns its own set of allocated input child ptrs so that blending-in and blending-out instances remain independent.
- L65 _public typedef_ `using FSharedData = FUAFInlineSubGraphTraitSharedData;`
- L87 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L88 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L91 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L94 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L95 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L98 _public prototype_ `virtual float GetBlendWeight(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;` — IDiscreteBlend impl
- L99 _public prototype_ `virtual int32 GetBlendDestinationChildIndex(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding) const override;`
- L100 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;`
- L101 _public prototype_ `virtual void OnBlendInitiated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L102 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L105 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl
- L110 _private prototype_ `void PushInputsToInnerGraph(const FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, const FSubGraphSlot& InSlot) const;` — For each entry in ResolvedInputs, wraps the slot's corresponding FTraitPtr as a FVirtualValueBundle_InlineGraph and writes it into the inner graph instance via AccessVariable.

#### enum `UE::UAF::FUAFInlineSubGraphTrait::ESlotState`  
`enum class ESlotState : uint8`  
_L37-42_
- L39 _public enumerator_ `ActiveWithGraph`
- L40 _public enumerator_ `ActiveWithReferencePose`
- L41 _public enumerator_ `Inactive`

#### struct `UE::UAF::FUAFInlineSubGraphTrait::FSubGraphSlot`  
`struct FSubGraphSlot`  
_L44-63_
- L47 _public member_ `TObjectPtr<const UUAFAnimGraph> AnimationGraph;` — The animation graph asset for this slot
- L50 _public member_ `TSharedPtr<FAnimNextGraphInstance> GraphInstance;` — The live graph instance for this slot
- L56 _public member_ `TArray<FTraitPtr> InputChildPtrs;` — FTraitPtrs allocated from ResolvedInputs during OnBlendInitiated, one per Inputs entry. Each ptr is wrapped as a FVirtualValueBundle_InlineGraph and written into the inner graph's corresponding interface variable. Allocated per slot so blending-in and blending-out instances each hold an independent set.
- L59 _public member_ `ESlotState State = ESlotState::Inactive;` — Current lifecycle state of the slot
- L62 _public member_ `bool bWasRelevant = false;` — Whether this slot was relevant on the previous update tick

#### struct `UE::UAF::FUAFInlineSubGraphTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L67-84_
- inherits: `FTrait::FInstanceData`
- L69 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L72 _public member_ `TArray<FSubGraphSlot> SubGraphSlots;` — Sub-graph slots managing hosted inner graph instances
- L75 _public member_ `int32 CurrentlyActiveSubGraphIndex = INDEX_NONE;` — Index of the currently active sub-graph slot (INDEX_NONE if none)
- L78 _public member_ `FTraitPtr ReferencePoseChildPtr;` — Child used to output the reference pose when no graph is provided
- L83 _public member_ `TArray<FUAFInlineSubGraphInputBinding> ResolvedInputs;` — Inputs resolved from the latent pin during OnBecomeRelevant, cached here so that OnBlendInitiated (which runs in an execution context) can use them without re-accessing the latent system outside of update traversal.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/InputPoseTrait.h` (Private)


#### struct `FAnimNextInputPoseTraitSharedData`  
`struct FAnimNextInputPoseTraitSharedData : public FAnimNextTraitSharedData`  
_L14-27_
- reflection: `USTRUCT(meta = (Deprecated = "5.8", DisplayName = "Input Pose (Outdated)", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `FAnimNextGraphLODPose Input;` — `UPROPERTY()`

#### struct `UE::UAF::FInputPoseTrait`  
`struct FInputPoseTrait : FBaseTrait, IEvaluate`  
_L31-42_
- inherits: `FBaseTrait,IEvaluate`
- L35 _public typedef_ `using FSharedData = FAnimNextInputPoseTraitSharedData;`
- L38 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L41 _public prototype_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;` — FTrait interface

#### Free symbols / members of external scopes

- L22 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/MakeDynamicAdditiveTrait.h` (Private)


#### struct `UE::UAF::FMakeDynamicAdditiveTrait`  
`struct FMakeDynamicAdditiveTrait : FBaseTrait, IEvaluate, IHierarchy`  
_L21-41_
- inherits: `FBaseTrait,IEvaluate,IHierarchy`
- desc: Make Dynamic Additive Trait A trait that can generate an additive pose based on the input poses The Additive input is the pose to be turned additive The Base input is the base to generate the additive against
- L25 _public typedef_ `using FSharedData = FMakeDynamicAdditiveTraitSharedData;`
- L36 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L39 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L40 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`

#### struct `UE::UAF::FMakeDynamicAdditiveTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L27-33_
- inherits: `FTrait::FInstanceData`
- L29 _public member_ `FTraitPtr Base;`
- L30 _public member_ `FTraitPtr Additive;`
- L32 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/ModifyCurveTrait.h` (Private)


#### enum `EAnimNext_ModifyCurveApplyMode`  
`enum class EAnimNext_ModifyCurveApplyMode : uint8`  
_L17-27_
- reflection: `UENUM()`
- L20 _public enumerator_ `Add` — Add new value to input curve value
- L23 _public enumerator_ `Scale` — Scale input value by new value
- L26 _public enumerator_ `Blend` — Blend input with new curve value, using Alpha setting on the node

#### struct `FModifyCurveParameters`  
`struct FModifyCurveParameters`  
_L30-40_
- reflection: `USTRUCT()`
- L35 _public member_ `FName CurveName;` — `UPROPERTY(Category=CurveData, EditAnywhere)`
- L38 _public member_ `float CurveValue = 0.0f;` — `UPROPERTY(Category=CurveData, EditAnywhere)`

#### struct `FAnimNextModifyCurveTraitSharedData`  
`struct FAnimNextModifyCurveTraitSharedData : public FAnimNextTraitSharedData`  
_L44-64_
- reflection: `USTRUCT(meta = (DisplayName = "Modify Curve", ShowTooltip=true, AllowDuplicates = "true"))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can write to a specific float curve value
- L49 _public member_ `EAnimNext_ModifyCurveApplyMode ApplyMode = EAnimNext_ModifyCurveApplyMode::Add;` — `UPROPERTY(Category=Settings, EditAnywhere)`
- L52 _public member_ `TArray<FModifyCurveParameters> ModifyCurveParameters;` — `UPROPERTY(Category=Settings, EditAnywhere)`
- L55 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(Category=Settings, EditAnywhere, meta=(ClampMin=0, ClampMax=1))`

#### struct `UE::UAF::FModifyCurveTrait`  
`struct FModifyCurveTrait : FAdditiveTrait, IEvaluate`  
_L74-90_
- inherits: `FAdditiveTrait,IEvaluate`
- desc: FModifyCurveTrait A trait that can write to a specific float curve value
- L78 _public typedef_ `using FSharedData = FAnimNextModifyCurveTraitSharedData;`
- L89 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### struct `UE::UAF::FModifyCurveTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L80-86_
- inherits: `FTrait::FInstanceData`
- L84 _public member_ `TObjectPtr<const UObject> HostObject = nullptr;` — Debug Object for VisualLogger

#### struct `FModifyCurveTask`  
`struct FModifyCurveTask : public FAnimNextEvaluationTask`  
_L94-111_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L98 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FModifyCurveTask) static FModifyCurveTask Make(float Alpha, EAnimNext_ModifyCurveApplyMode ApplyMode, TConstArrayView<FModifyCurveParameters> CurveParameters);`
- L103 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L106 _private prototype_ `static float ProcessCurveOperation(float CurrentValue, float NewValue, float Alpha, EAnimNext_ModifyCurveApplyMode ApplyMode);`
- L108 _private member_ `float Alpha = 1.0f;`
- L109 _private member_ `EAnimNext_ModifyCurveApplyMode ApplyMode = EAnimNext_ModifyCurveApplyMode::Add;`
- L110 _private member_ `TArray<FModifyCurveParameters, TInlineAllocator<8>> ModifyCurveParameters;`

#### Free symbols / members of external scopes

- L57 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \`
- L66 _namespace_ `namespace UE`
- L66 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/NotifyDispatcher.h` (Private)


#### struct `UE::UAF::FNotifyDispatcherTrait`  
`struct FNotifyDispatcherTrait : FAdditiveTrait, ITimelinePlayer`  
_L18-30_
- inherits: `FAdditiveTrait,ITimelinePlayer`
- desc: FNotifyDispatcherTrait A trait that dispatches notifies according to a timeline advancing
- L22 _public typedef_ `using FSharedData = FAnimNextNotifyDispatcherTraitSharedData;`
- L29 _public prototype_ `virtual void AdvanceBy(FExecutionContext& Context, const TTraitBinding<ITimelinePlayer>& Binding, float DeltaTime, bool bDispatchEvents) const override;` — ITimelinePlayer impl

#### struct `UE::UAF::FNotifyDispatcherTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L24-26_
- inherits: `FTrait::FInstanceData`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/NotifyFilterTrait.h` (Private)


#### struct `FAnimNextNotifyFilterTraitSharedData`  
`struct FAnimNextNotifyFilterTraitSharedData : public FAnimNextTraitSharedData`  
_L14-27_
- reflection: `USTRUCT(meta = (DisplayName = "Notify Filter"))`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `bool bShouldDisableNotifies = false;` — `UPROPERTY(EditAnywhere, Category = "Filtering")`

#### struct `UE::UAF::FNotifyFilterTrait`  
`struct FNotifyFilterTrait : FAdditiveTrait, IScopedTagInterface, IUpdate`  
_L31-69_
- inherits: `FAdditiveTrait,IScopedTagInterface,IUpdate`
- L35 _public typedef_ `using FSharedData = FAnimNextNotifyFilterTraitSharedData;`
- L37 _public prototype_ `static bool AreNotifiesEnabledInScope(const FExecutionContext& Context);`
- L40 _public function_ `virtual FName GetTag(const FExecutionContext& Context, const TTraitBinding<IScopedTagInterface>& Binding) const override` — IScopedTagInterface impl
- L46 _public function_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override` — IUpdate impl
- L57 _public function_ `virtual void PostUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override`
- L68 _private member_ `static FLazyName DisableNotifiesTag;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/Passthrough.h` (Private)


#### struct `UE::UAF::FPassthroughTrait`  
`struct FPassthroughTrait : FBaseTrait, IHierarchy`  
_L19-35_
- inherits: `FBaseTrait,IHierarchy`
- desc: FPassthroughTrait A trait that passes through the input without modification.
- L23 _public typedef_ `using FSharedData = FAnimNextPassthroughSharedData;`
- L33 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L34 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`

#### struct `UE::UAF::FPassthroughTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L25-30_
- inherits: `FTrait::FInstanceData`
- L27 _public member_ `FTraitPtr Input;`
- L29 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/ReferencePoseTrait.h` (Private)


#### enum `EAnimNextReferencePoseType`  
`enum class EAnimNextReferencePoseType : int32`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `MeshLocalSpace`
- L21 _public enumerator_ `AdditiveIdentity`

#### struct `FAnimNextReferencePoseTraitSharedData`  
`struct FAnimNextReferencePoseTraitSharedData : public FAnimNextTraitSharedData`  
_L26-33_
- reflection: `USTRUCT(meta = (DisplayName = "Reference Pose", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that outputs a reference pose.
- L32 _public member_ `EAnimNextReferencePoseType ReferencePoseType = EAnimNextReferencePoseType::MeshLocalSpace;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))` — The type of the reference pose.

#### struct `UE::UAF::FReferencePoseTrait`  
`struct FReferencePoseTrait : FBaseTrait, IEvaluate`  
_L42-50_
- inherits: `FBaseTrait,IEvaluate`
- desc: FReferencePoseTrait A trait that outputs a reference pose.
- L46 _public typedef_ `using FSharedData = FAnimNextReferencePoseTraitSharedData;`
- L49 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### Free symbols / members of external scopes

- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/SequencePlayer.h` (Private)


#### struct `UE::UAF::FSequencePlayerTrait`  
`struct FSequencePlayerTrait : FBaseTrait, IEvaluate, IAttributeProvider, ITimeline, ITimelinePlayer, IUpdate, IGarbageCollection, INotifySource`  
_L24-68_
- inherits: `FBaseTrait,IEvaluate,IAttributeProvider,ITimeline,ITimelinePlayer,IUpdate,IGarbageCollection,INotifySource`
- desc: FSequencePlayerTrait A trait that can play an animation sequence.
- L28 _public typedef_ `using FSharedData = FAnimNextSequencePlayerTraitSharedData;`
- L46 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L49 _public prototype_ `virtual FOnExtractRootMotionAttribute GetOnExtractRootMotionAttribute(FExecutionContext& Context, const TTraitBinding<IAttributeProvider>& Binding) const override;` — IAttributeProvider impl
- L52 _public prototype_ `virtual void GetSyncMarkers(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineSyncMarkerArray& OutSyncMarkers) const override;` — ITimeline impl
- L53 _public prototype_ `virtual bool GetState(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineState& OutTimelineState) const override;`
- L54 _public prototype_ `virtual bool GetDelta(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineDelta& OutTimelineDelta) const override;`
- L57 _public prototype_ `virtual void AdvanceBy(FExecutionContext& Context, const TTraitBinding<ITimelinePlayer>& Binding, float DeltaTime, bool bDispatchEvents) const override;` — ITimelinePlayer impl
- L60 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L61 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L64 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl
- L67 _public prototype_ `virtual void GetNotifies(FExecutionContext& Context, const TTraitBinding<INotifySource>& Binding, float StartPosition, float Duration, bool bLooping, TArray<FAnimNotifyEventReference>& OutNotifies) const override;` — INotifySource impl

#### struct `UE::UAF::FSequencePlayerTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L30-43_
- inherits: `FTrait::FInstanceData`
- L33 _public member_ `TObjectPtr<const UAnimSequence> AnimSequence;` — Cached value of the anim sequence we are playing
- L36 _public member_ `FDeltaTimeRecord DeltaTimeRecord;` — Delta time range required for root motion extraction
- L39 _public member_ `float InternalTimeAccumulator = 0.0f;` — Current time accumulator
- L42 _public member_ `ETypeAdvanceAnim LastAdvanceType = ETAA_Default;` — The last advance type when FAnimationRuntime::AdvanceTime was called

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/SubGraphHost.h` (Private)


#### struct `UE::UAF::FSubGraphHostTrait`  
`struct FSubGraphHostTrait : FBaseTrait, IUpdate, IUpdateTraversal, IHierarchy, IDiscreteBlend, IGarbageCollection`  
_L23-88_
- inherits: `FBaseTrait,IUpdate,IUpdateTraversal,IHierarchy,IDiscreteBlend,IGarbageCollection`
- desc: FSubGraphHostTrait A trait that hosts and manages a sub-graph instance.
- L52 _public typedef_ `using FSharedData = FAnimNextSubGraphHostTraitSharedData;`
- L70 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L73 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L76 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L77 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L80 _public prototype_ `virtual float GetBlendWeight(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;` — IDiscreteBlend impl
- L81 _public prototype_ `virtual int32 GetBlendDestinationChildIndex(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding) const override;`
- L82 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;`
- L83 _public prototype_ `virtual void OnBlendInitiated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L84 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L87 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### enum `UE::UAF::FSubGraphHostTrait::ESlotState`  
`enum class ESlotState : uint8`  
_L27-32_
- L29 _public enumerator_ `ActiveWithGraph`
- L30 _public enumerator_ `ActiveWithReferencePose`
- L31 _public enumerator_ `Inactive`

#### struct `UE::UAF::FSubGraphHostTrait::FSubGraphSlot`  
`struct FSubGraphSlot`  
_L34-50_
- L37 _public member_ `TObjectPtr<const UUAFAnimGraph> AnimationGraph;` — The animation graph to use
- L40 _public member_ `TSharedPtr<FAnimNextGraphInstance> GraphInstance;` — The graph instance
- L43 _public member_ `FName EntryPoint;` — The entry point to use
- L46 _public member_ `ESlotState State = ESlotState::Inactive;` — The current slot state
- L49 _public member_ `bool bWasRelevant = false;` — Whether or not this slot state was previously relevant

#### struct `UE::UAF::FSubGraphHostTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L54-67_
- inherits: `FTrait::FInstanceData`
- L56 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L59 _public member_ `TArray<FSubGraphSlot> SubGraphSlots;` — List of sub-graph slots
- L63 _public member_ `int32 CurrentlyActiveSubGraphIndex = INDEX_NONE;` — The index of the currently active sub-graph slot All other sub-graphs are blending out
- L66 _public member_ `FTraitPtr ReferencePoseChildPtr;` — Our child node pointer. This child is shared between all slots that have no graph provided.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Private/Traits/SynchronizeUsingGroups.h` (Private)


#### struct `UE::UAF::FSynchronizeUsingGroupsTrait`  
`struct FSynchronizeUsingGroupsTrait : FAdditiveTrait, IUpdate, IGroupSynchronization, ITimelinePlayer, IGraphFactory`  
_L22-62_
- inherits: `FAdditiveTrait,IUpdate,IGroupSynchronization,ITimelinePlayer,IGraphFactory`
- desc: FSynchronizeUsingGroupsTrait A trait that synchronizes animation sequence playback using named groups.
- L26 _public typedef_ `using FSharedData = FAnimNextSynchronizeUsingGroupsTraitSharedData;`
- L46 _public function_ `virtual bool MultipleInstanceSupport() const override` — A trait stack has a single timeline, we can't support multiple instances
- L50 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L51 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L54 _public prototype_ `virtual FSyncGroupParameters GetGroupParameters(FExecutionContext& Context, const TTraitBinding<IGroupSynchronization>& Binding) const override;` — IGroupSynchronization impl
- L55 _public prototype_ `virtual void AdvanceBy(FExecutionContext& Context, const TTraitBinding<IGroupSynchronization>& Binding, float DeltaTime, bool bDispatchEvents) const override;`
- L58 _public prototype_ `virtual void AdvanceBy(FExecutionContext& Context, const TTraitBinding<ITimelinePlayer>& Binding, float DeltaTime, bool bDispatchEvents) const override;` — ITimelinePlayer impl
- L61 _public prototype_ `virtual void GetFactoryParams(FExecutionContext& Context, const TTraitBinding<IGraphFactory>& Binding, FGraphAssetHandleConstView AssetHandle, FAnimNextFactoryParams& InOutParams) const override;` — IGraphFactory impl

#### struct `UE::UAF::FSynchronizeUsingGroupsTrait::FInstanceData`  
`struct FInstanceData : FTraitInstanceData`  
_L28-42_
- inherits: `FTraitInstanceData`
- L30 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L31 _public prototype_ `void Destruct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L34 _public member_ `FSyncGroupGraphInstanceComponent* SyncGroupComponent = nullptr;` — Cached pointer to our sync group component
- L37 _public member_ `FName UniqueGroupName;` — If our sync mode requires a unique group name, we'll cache it and re-use it as it is unique to our instance
- L39 _public member_ `bool bFreezeTimeline = false;`
- L40 _public member_ `bool bHasReachedFullWeight = false;`
- L41 _public member_ `bool bHasTimelinePlayer = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/AnimNextAnimGraphStats.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Allocate Graph Instance"), STAT_AnimNext_Graph_AllocateInstance, STATGROUP_`
- L9 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Graph RigVM"), STAT_AnimNext_Graph_RigVM, STATGROUP_AnimNext, UA`
- L10 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Execute Evaluation Program"), STAT_AnimNext_EvaluationProgram_Execute, STATGRO`
- L12 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Call Function"), STAT_AnimNext_CallFunction, STATGROUP_AnimNext,`
- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF: Keyframe CopyFrom"), STAT_AnimNext_Keyframe_CopyFrom, STATGROUP_AnimNe`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Asset/UAFAnimGraphAssetData.h` (Public)


#### struct `FUAFGraphFactoryAsset_Graph`  
`struct FUAFGraphFactoryAsset_Graph : public FUAFGraphFactoryAsset`  
_L15-28_
- reflection: `USTRUCT(DisplayName="Graph Asset")`
- inherits: `FUAFGraphFactoryAsset`
- L19 _public prototype_ `FUAFGraphFactoryAsset_Graph() = default;`
- L20 _public function_ `FUAFGraphFactoryAsset_Graph(const UUAFAnimGraph* Graph) : AnimationGraph(Graph)`
- L22 _public function_ `virtual bool Validate() const override`
- L24 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const override`
- L27 _public member_ `TObjectPtr<const UUAFAnimGraph> AnimationGraph;` — `UPROPERTY(EditAnywhere, Category = AssetData)`

#### enum `EAnimationStartTimeType`  
`enum class EAnimationStartTimeType : uint8`  
_L31-35_
- reflection: `UENUM()`
- L33 _public enumerator_ `TimeInSeconds`
- L34 _public enumerator_ `TimePercent`

#### struct `FUAFGraphFactoryAsset_Animation`  
`struct FUAFGraphFactoryAsset_Animation : public FUAFGraphFactoryAsset`  
_L38-96_
- reflection: `USTRUCT(DisplayName="Animation Asset")`
- inherits: `FUAFGraphFactoryAsset`
- L42 _public function_ `FUAFGraphFactoryAsset_Animation(const UAnimSequence* AnimSequence)`
- L43 _public prototype_ `FUAFGraphFactoryAsset_Animation() = default;`
- L45 _public function_ `virtual bool Validate() const override`
- L47 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const override`
- L49 _public function_ `float CalculateStartTime() const`
- L80 _public member_ `TObjectPtr<const UAnimSequence> AnimationSequence;` — `UPROPERTY(EditAnywhere, Category = AssetData)`
- L83 _public member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category ="Playback Options")`
- L86 _public member_ `UE::UAF::EAnimAssetLoopMode LoopMode = UE::UAF::EAnimAssetLoopMode::Auto;` — `UPROPERTY(EditAnywhere, Category ="Playback Options")`
- L89 _public member_ `EAnimationStartTimeType StartTimeType = EAnimationStartTimeType::TimeInSeconds;` — `UPROPERTY(EditAnywhere, Category ="Playback Options")`
- L92 _public member_ `float StartTimeSeconds = 0.0f;` — `UPROPERTY(EditAnywhere, Category ="Playback Options", meta=(EditConditionHides, EditCondition="StartTimeType==EAnimationStartTimeType::TimeInSeconds", Units="s", ClampMin = "0.0", UIMin = "0.0"))`
- L95 _public member_ `float StartTimePercent = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Playback Options", meta=(EditConditionHides, EditCondition="StartTimeType==EAnimationStartTimeType::TimePercent", Units="Percent", ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))`

#### struct `FUAFGraphFactoryAsset_BlendSpace`  
`struct FUAFGraphFactoryAsset_BlendSpace : public FUAFGraphFactoryAsset`  
_L99-121_
- reflection: `USTRUCT(DisplayName="Blend Space Asset")`
- inherits: `FUAFGraphFactoryAsset`
- L103 _public function_ `FUAFGraphFactoryAsset_BlendSpace(const UBlendSpace* BlendSpace) : BlendSpace(BlendSpace)`
- L104 _public prototype_ `FUAFGraphFactoryAsset_BlendSpace() = default;`
- L106 _public function_ `virtual bool Validate() const override`
- L108 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const override`
- L111 _public member_ `TObjectPtr<const UBlendSpace> BlendSpace;` — `UPROPERTY(EditAnywhere, Category = AssetData)`
- L114 _public member_ `float XAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Options")`
- L117 _public member_ `float YAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Options")`
- L120 _public member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Options")`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/EvaluationFlags.h` (Public)


#### enum `UE::UAF::EEvaluationFlags`  
`enum class EEvaluationFlags`  
_L10-29_
- desc: Flags to control what to compute when evaluating an animation node
- L13 _public enumerator_ `None = 0x00` — Empty flags
- L16 _public enumerator_ `Trajectory = 0x01` — Evaluates the trajectory of the root bone
- L19 _public enumerator_ `Bones = 0x02` — Evaluates the animation pose of all bones
- L22 _public enumerator_ `Curves = 0x04` — Evaluates the animation curves
- L25 _public enumerator_ `Attributes = 0x08` — Evaluates the animation attributes
- L28 _public enumerator_ `All = 0xff` — Evaluates everything

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/EvaluationProgram.h` (Public)


#### struct `UE::UAF::FEvaluationProgram`  
`struct FEvaluationProgram`  
_L27-62_
- desc: Evaluation Program This struct holds a sequence of evaluation tasks that form a program within our evaluation virtual machine framework. Programs are immutable once written. @see FAnimNextEvaluationTask
- L29 _public prototype_ `FEvaluationProgram() = default;`
- L32 _public prototype_ `FEvaluationProgram(FEvaluationProgram&&) = default;` — Allow moving
- L33 _public prototype_ `FEvaluationProgram& operator=(FEvaluationProgram&&) = default;`
- L36 _public prototype_ `bool IsEmpty() const;` — Returns whether or not this program is empty
- L42 _public prototype_ `template<class TaskType> void AppendTask(TaskType&& Task);` — Appends a new task into the program, tasks mutate state in the order they have been appended in This means that child nodes need to evaluate first, tasks will usually be appended in IEvaluate::PostEvaluate Tasks are moved into their final memory location, caller can allocate the task anywhere, it is no longer needed after this operation
- L46 _public prototype_ `template<class TaskType> void AppendTaskPtr(const TSharedPtr<TaskType>& TaskPtr);` — Same as above, but uses TaskType copy constructor to move the task into the program.
- L49 _public prototype_ `void Execute(FEvaluationVM& VM) const;` — Executes the current program on the provided virtual machine
- L52 _public prototype_ `FString ToString() const;` — Returns the program as a string suitable for debug purposes
- L57 _private prototype_ `FEvaluationProgram(const FEvaluationProgram&) = delete;` — Disallow copy
- L58 _private prototype_ `FEvaluationProgram& operator=(const FEvaluationProgram&) = delete;`
- L61 _private member_ `TArray<TSharedPtr<FAnimNextEvaluationTask>> Tasks;` — List of tasks
- L68 _function_ `template<class TaskType> inline void FEvaluationProgram::AppendTask(TaskType&& Task)`
- L78 _function_ `template<class TaskType> inline void FEvaluationProgram::AppendTaskPtr(const TSharedPtr<TaskType>& TaskPtr)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/EvaluationTask.h` (Public)


#### struct `FAnimNextEvaluationTask`  
`struct FAnimNextEvaluationTask`  
_L28-39_
- reflection: `USTRUCT()`
- desc: Evaluation Task This is the base class for our evaluation program tasks. They represent macro instructions within our evaluation virtual machine system. They operate on the VM internal state to generate inputs and produce outputs. @see FEvaluationProgram, FEvaluationVM
- L32 _public function_ `virtual ~FAnimNextEvaluationTask()`
- L35 _public function_ `virtual const UScriptStruct* GetStruct() const` — Returns the derived type for the task
- L38 _public function_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const` — Task entry point

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L15 _macro_ `#define DECLARE_ANIM_EVALUATION_TASK(TaskName) \` — Implements various implementation details for an animation evaluation task

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/EvaluationTaskContext.h` (Public)


#### class `UE::UAF::FEvaluationTaskContext`  
`class FEvaluationTaskContext final`  
_L21-67_
- desc: Evaluation Task Context Encapsulates the state that controls what values tasks should produce.
- L24 _public prototype_ `FEvaluationTaskContext();`
- L25 _public prototype_ `FEvaluationTaskContext(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding, const USkeletalMesh* SkeletalMesh, FName SetName);`
- L28 _public prototype_ `[[nodiscard]] bool IsValid() const;` — Returns whether or not this context is valid
- L31 _public prototype_ `[[nodiscard]] const UAbstractSkeletonSetBinding* GetSetBinding() const;` — Returns the abstract skeleton set binding asset we are evaluating with (or nullptr if we aren't valid)
- L34 _public prototype_ `[[nodiscard]] const USkeleton* GetSkeleton() const;` — Returns the concrete skeleton we are evaluating with (or nullptr if we aren't valid)
- L37 _public prototype_ `[[nodiscard]] const USkeletalMesh* GetSkeletalMesh() const;` — Returns the skeletal mesh we are evaluating with, may be nullptr)
- L40 _public prototype_ `[[nodiscard]] const FAttributeNamedSetPtr& GetNamedSet() const;` — Returns the named set we are currently evaluating with (or nullptr if we aren't valid)
- L44 _public prototype_ `[[nodiscard]] bool SetNamedSet(FName SetName);` — Sets the named set Returns true if we succeeded and the set exists in the current binding, false otherwise
- L47 _public prototype_ `[[nodiscard]] const FValueBundlePtr& GetDefaultAttributeValues() const;` — Returns the default attribute values for the current named set (or nullptr if we aren't valid)
- L51 _private member_ `const UAbstractSkeletonSetBinding* SetBinding = nullptr;` — The set binding we are evaluating with
- L54 _private member_ `const USkeletalMesh* SkeletalMesh = nullptr;` — The target skeletal mesh with are evaluating with, may be nullptr
- L57 _private member_ `const USkeleton* Skeleton = nullptr;` — The target skeleton we are evaluating with
- L60 _private member_ `FAttributeBindingDataPtr BindingData;` — Binding data owned by the set binding
- L63 _private member_ `FAttributeNamedSetPtr NamedSet;` — Named set instance to produce an output for
- L66 _private member_ `FValueBundlePtr DefaultAttributeValues;` — Default values as specified by the current set binding and named set

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/EvaluationVM.h` (Public)


#### struct `UE::UAF::FEvaluationVMStackName`  
`struct FEvaluationVMStackName final`  
_L69-79_
- desc: Evaluation VM Stack Name A small struct to wrap an FName and cache its type hash.
- L72 _public function_ `FEvaluationVMStackName(const FName& InName) : Name(InName) , NameHash(GetTypeHash(InName))` — Implicitly coerce or construct a stack name from an FName
- L77 _public member_ `FName Name;`
- L78 _public member_ `uint32 NameHash = 0;`

#### struct `UE::UAF::FEvaluationVMStackEntry`  
`struct alignas(16) FEvaluationVMStackEntry final`  
_L86-107_
- desc: Evaluation VM Stack Entry A small header for each stack entry.
- L98 _public member_ `uint32 Size = 0;` — Allocated size of this entry, includes sizeof(FEvaluationVMStackEntry)
- L101 _public member_ `uint32 Flags = 0;` — Metadata flags
- L105 _public function_ `void* GetValuePtr()`
- L106 _public function_ `const void* GetValuePtr() const`

#### union `UE::UAF::FEvaluationVMStackEntry::(anonymous)`  
``  
_L89-95_

#### struct `UE::UAF::FEvaluationVMStack`  
`struct FEvaluationVMStack final`  
_L116-142_
- desc: Evaluation VM Stack Represents a named and typed VM stack.
- L119 _public member_ `FName Name;` — Name of the stack
- L123 _public member_ `uint32 TypeID = 0;` — Type ID used for runtime checks to make sure we always read/write using the same type @see ANIM_NEXT_ENABLE_EVALUATION_STACK_USAGE
- L126 _public member_ `FEvaluationVMStackEntry* Top = nullptr;` — Pointer to the entry on top of the stack or nullptr if the stack is empty
- L130 _public member_ `TFunction<void(void*)> TypeDestructor;` — For non-trivially destructible types, the destructor to call Only used if the stack is not empty when it is destroyed
- L132 _public prototype_ `FEvaluationVMStack() = default;`
- L135 _public prototype_ `FEvaluationVMStack(const FEvaluationVMStack&) = delete;` — Disable copy but enable move
- L136 _public prototype_ `FEvaluationVMStack(FEvaluationVMStack&&) = default;`
- L137 _public prototype_ `FEvaluationVMStack& operator=(const FEvaluationVMStack&) = delete;`
- L138 _public prototype_ `FEvaluationVMStack& operator=(FEvaluationVMStack&&) = default;`
- L141 _public prototype_ `~FEvaluationVMStack();` — The destructor will free remaining entries

#### struct `UE::UAF::FEvaluationVM`  
`struct FEvaluationVM`  
_L152-261_
- desc: Evaluation VM This struct holds the internal state when we execute and FEvaluationProgram. Our virtual machine is stack based, values are generally pushed and popped. @see FEvaluationProgram
- L154 _public prototype_ `FEvaluationVM(EEvaluationFlags InEvaluationFlags, const FReferencePose& InReferencePose, int32 InCurrentLOD);`
- L155 _public prototype_ `FEvaluationVM(EEvaluationFlags EvaluationFlags, TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding, const USkeletalMesh* SkeletalMesh, FName SetName, int32 CurrentLOD);`
- L158 _public prototype_ `FEvaluationVM(EEvaluationFlags InEvaluationFlags, const FReferencePose& IReferencePose, const UAbstractSkeletonSetBinding* SetBinding, const USkeletalMesh* SkeletalMesh, FName SetName, int32 InCurrentLOD);` — REMOVE ME: Exclusively for testing that before/after yields the same results
- L161 _public prototype_ `FEvaluationVM(FEvaluationVM&&) = default;` — Allow move
- L162 _public prototype_ `FEvaluationVM& operator=(FEvaluationVM&&) = default;`
- L165 _public prototype_ `[[nodiscard]] bool IsValid() const;` — Returns true if we are fully initialized
- L168 _public function_ `[[nodiscard]] EEvaluationFlags GetFlags() const` — Returns the evaluation flags
- L172 _public prototype_ `template<typename ValueType> void PushValue(const FEvaluationVMStackName& StackName, ValueType&& Value);` — Pushes and moves the specified value on its evaluation stack
- L177 _public prototype_ `template<typename ValueType> [[nodiscard]] bool PopValue(const FEvaluationVMStackName& StackName, ValueType& OutValue);` — Pops the top value from the evaluation stack Returns true if the stack was not empty and a value is returned, false otherwise
- L183 _public prototype_ `template<typename ValueType> [[nodiscard]] const ValueType* PeekValue(const FEvaluationVMStackName& StackName, uint32 Offset) const;` — Returns an immutable pointer to a value at some offset from the top of the evaluation stack An offset of 0 means the top of the stack Returns valid pointer if an entry exists, nullptr otherwise
- L189 _public prototype_ `template<typename ValueType> [[nodiscard]] ValueType* PeekValueMutable(const FEvaluationVMStackName& StackName, uint32 Offset);` — Returns a mutable pointer to a value at some offset from the top of the evaluation stack An offset of 0 means the top of the stack Returns valid pointer if an entry exists, nullptr otherwise
- L192 _public prototype_ `void Shrink();` — Trims internal containers to only use as much memory as required to avoid slack
- L195 _public prototype_ `[[nodiscard]] FKeyframeState MakeReferenceKeyframe(bool bAdditiveKeyframe) const;` — Returns a reference keyframe (bind pose or additive identity)
- L198 _public prototype_ `[[nodiscard]] FKeyframeState MakeUninitializedKeyframe(bool bAdditiveKeyframe) const;` — Returns an uninitialized keyframe with memory pre-allocated
- L201 _public prototype_ `[[nodiscard]] const FEvaluationTaskContext& GetActiveEvaluationContext() const;` — Returns the evaluation context that controls what state we produce
- L204 _public prototype_ `[[nodiscard]] const FAttributeNamedSetPtr& GetActiveNamedSet() const;` — Returns the named set we are currently evaluating with
- L208 _public prototype_ `[[nodiscard]] bool PushEvaluationContext(TNonNullPtr<const UAbstractSkeletonSetBinding> SetBinding, const USkeletalMesh* SkeletalMesh, FName SetName);` — Pushes a new binding and named set to evaluate with Returns true if we succeeded and the set exists in the specified binding, false otherwise
- L212 _public prototype_ `[[nodiscard]] bool PushEvaluationContext(FName SetName);` — Pushes a new named set to evaluate with Returns true if we succeeded and the set exists in the currently active binding, false otherwise
- L216 _public prototype_ `bool PopEvaluationContext();` — Pops the current active named set Returns whether or not we succeeded (we need to retain at least one named set)
- L219 _public function_ `[[nodiscard]] int32 GetCurrentLOD() const` — Returns the current LOD
- L222 _public prototype_ `[[nodiscard]] const FValueTransformerMapPtr& GetTransformerMap() const;` — Returns the value transformer map
- L226 _private prototype_ `FEvaluationVM(const FEvaluationVM&) = delete;` — Disallow copy
- L227 _private prototype_ `FEvaluationVM& operator=(const FEvaluationVM&) = delete;`
- L230 _private prototype_ `FEvaluationVMStack& GetOrCreateStack(const FEvaluationVMStackName& StackName, uint32 TypeID);` — Retrieves and optionally creates the stack (if not found) by the specified name
- L233 _private prototype_ `FEvaluationVMStack* FindStack(const FEvaluationVMStackName& StackName, uint32 TypeID);` — Returns the specified stack if found, nullptr otherwise
- L234 _private prototype_ `const FEvaluationVMStack* FindStack(const FEvaluationVMStackName& StackName, uint32 TypeID) const;`
- L236 _private prototype_ `const void* PeekValueImpl(const FEvaluationVMStackName& StackName, uint32 TypeID, uint32 Offset) const;`
- L239 _private member_ `TMap<FName, FEvaluationVMStack> InternalStacks;` — Various internal stacks that tasks can use (e.g. keyframe state)
- L242 _private member_ `const FReferencePose* ReferencePose = nullptr;` — Reference pose
- L245 _private member_ `TArray<FEvaluationTaskContext> EvaluationContextStack;` — The internal context that controls what state we are producing
- L248 _private member_ `FValueTransformerMapPtr ValueTransformerMap;` — Shared map of value transformers
- L251 _private member_ `int32 CurrentLOD = 0;` — Current LOD we are evaluating at
- L254 _private member_ `EEvaluationFlags EvaluationFlags = EEvaluationFlags::All;` — Flags that control what we wish to evaluate
- L257 _private member_ `UE::Anim::FCurveFilter CurveFilter;` — Default curve filter
- L267 _function_ `template<typename ValueType> inline void FEvaluationVM::PushValue(const FEvaluationVMStackName& StackName, ValueType&& Value)`
- L297 _function_ `template<typename ValueType> [[nodiscard]] inline bool FEvaluationVM::PopValue(const FEvaluationVMStackName& StackName, ValueType& OutValue)`
- L325 _function_ `template<typename ValueType> [[nodiscard]] inline const ValueType* FEvaluationVM::PeekValue(const FEvaluationVMStackName& StackName, uint32 Offset) const`
- L331 _function_ `template<typename ValueType> [[nodiscard]] inline ValueType* FEvaluationVM::PeekValueMutable(const FEvaluationVMStackName& StackName, uint32 Offset)`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L25 _macro_ `#define ANIM_NEXT_ENABLE_EVALUATION_STACK_USAGE(Type) \` — If you wish to use a custom type with a stack in the FEvaluationVM, you'll have to enable its usage through this macro to ensure that UE::UAF::GetTypeID() is declared. Use this macro inside the UE::UAF namespace
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace UAF` (scope `UE`)
- L37 _function_ `template<typename Type> constexpr uint32 GetTypeID()` (scope `UE::UAF`) — Helper function that returns a UID for the specified type @see ANIM_NEXT_ENABLE_EVALUATION_STACK_USAGE
- L46 _function_ `template<typename Type> inline void DestructType(void* Ptr)` (scope `UE::UAF`) — Helper function that destructs a pointer of the provided type
- L52 _function_ `template<typename Type> inline TFunction<void(void*)> GetTypeDestructor()` (scope `UE::UAF`)
- L91 _member_ `FEvaluationVMStackEntry* Prev = nullptr;` (scope `UE::UAF::FEvaluationVMStackEntry::__anonf10e9a1c010a`) — Pointer to the previous entry beneath us on the stack
- L94 _member_ `uint64 DummyPadding;` (scope `UE::UAF::FEvaluationVMStackEntry::__anonf10e9a1c010a`) — Dummy padding to ensure this structure remains 16 bytes even on 32-bit architectures
- L341 _externvar_ `extern const FEvaluationVMStackName KEYFRAME_STACK_NAME;` (scope `UE::UAF`) — A stack of FKeyframeState instances used when sampling sequences and blending their results
- L342 _prototype_ `ANIM_NEXT_ENABLE_EVALUATION_STACK_USAGE(TUniquePtr<FKeyframeState>)` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/KeyframeState.h` (Public)


#### struct `UE::UAF::FKeyframeState`  
`struct FKeyframeState`  
_L24-40_
- desc: Key Frame State This struct holds sampled keyframe state or interpolated keyframe state. It holds a pose, trajectory, curves, attributes, etc that one might find in an animation sequence or as an output of an animation node.
- L27 _public member_ `FLODPoseStack Pose;` — Joint transforms at a particular LOD (on memstack)
- L30 _public member_ `FBlendedCurve Curves;` — Float curves at a particular LOD (on memstack)
- L33 _public member_ `UE::Anim::FStackAttributeContainer Attributes;` — Attributes at a particular LOD (on memstack)
- L35 _public function_ `[[nodiscard]] bool IsValid() const`
- L36 _public function_ `[[nodiscard]] bool IsAdditive() const`
- L39 _public prototype_ `void CopyFrom(const FAnimNextGraphLODPose& Source);` — Copy from a graph pose, transparently handling cross-skeleton remapping.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/SerializableEvaluationProgram.h` (Public)


#### struct `FSerializableEvaluationProgram`  
`struct FSerializableEvaluationProgram`  
_L16-28_
- reflection: `USTRUCT()`
- L20 _public function_ `FSerializableEvaluationProgram()`
- L24 _public prototype_ `FSerializableEvaluationProgram(const UE::UAF::FEvaluationProgram& Other);`
- L27 _public member_ `TArray<FInstancedStruct> Tasks;` — `UPROPERTY(EditAnywhere, Category = "Tasks", meta = (ExpandByDefault))`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/ApplyAdditiveKeyframe.h` (Public)


#### struct `FAnimNextApplyAdditiveKeyframeTask`  
`struct FAnimNextApplyAdditiveKeyframeTask : public FAnimNextEvaluationTask`  
_L28-55_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Apply Additive Keyframe Task This pops the top two keyframes from the VM keyframe stack, it applies an additive keyframe onto its base, and pushes back the result onto the stack. The top pose should be the additive keyframe and the second to the top the base keyframe.
- L32 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextApplyAdditiveKeyframeTask) static FAnimNextApplyAdditiveKeyframeTask Make(float BlendWeight);`
- L35 _public prototype_ `static FAnimNextApplyAdditiveKeyframeTask Make(const FName& AlphaSourceCurveName, const int8 AlphaCurveInputIndex, TFunction<float(float)> InputScaleBiasClampFn);`
- L38 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L42 _public prototype_ `float GetInterpolationAlpha(const UE::UAF::FKeyframeState* KeyframeA, const UE::UAF::FKeyframeState* KeyframeB) const;` — @TODO: Move this into shared method Compute the current alpha value for curves or return the interpolation alpha otherwise
- L43 _public prototype_ `float GetInterpolationAlpha(const UE::UAF::FValueBundle& CollectionA, const UE::UAF::FValueBundle& CollectionB) const;`
- L47 _public member_ `float BlendWeight = 0.0f;` — `UPROPERTY()` — How much weight between the additive identity and the additive pose to apply: lerp(identity, additive, weight)
- L50 _public member_ `FName AlphaSourceCurveName = NAME_None;` — The curve to evaluate and extract the interpolation alpha between the two input keyframes
- L52 _public member_ `int8 AlphaCurveInputIndex = INDEX_NONE;`
- L54 _public member_ `TFunction<float(float)> InputScaleBiasClampFn = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/ApplyAdditiveKeyframePerBone.h` (Public)


#### struct `FUAFApplyAdditiveKeyframePerBoneTask`  
`struct FUAFApplyAdditiveKeyframePerBoneTask : public FAnimNextApplyAdditiveKeyframeTask`  
_L26-39_
- reflection: `USTRUCT()`
- inherits: `FAnimNextApplyAdditiveKeyframeTask`
- desc: Apply Additive Keyframe Per Bone Task This pops the top two keyframes from the VM keyframe stack, it applies an additive keyframe with a weight per bone onto its base, and pushes back the result onto the stack. If no valid blend data is provided it will revert back to a full pose additive application. The top pose should be the additive keyframe and the second to the top the base keyframe.
- L30 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FUAFApplyAdditiveKeyframePerBoneTask) static FUAFApplyAdditiveKeyframePerBoneTask Make(const float BlendWeight, const FBlendSampleData& BlendData, bool bPerBoneDataUsesSkeletonIndex);`
- L33 _public prototype_ `static FUAFApplyAdditiveKeyframePerBoneTask Make(const FName& AlphaSourceCurveName, const int8 AlphaCurveInputIndex, TFunction<float(float)> InputScaleBiasClampFn, const FBlendSampleData& BlendData, bool bPerBoneDataUsesSkeletonIndex);`
- L35 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L37 _public member_ `const FBlendSampleData* BlendData = nullptr;`
- L38 _public member_ `bool bPerBoneDataUsesSkeletonIndex = false;`

#### struct `FUAFApplyAdditiveKeyframeWithBlendMaskTask`  
`struct FUAFApplyAdditiveKeyframeWithBlendMaskTask : public FAnimNextApplyAdditiveKeyframeTask`  
_L53-65_
- reflection: `USTRUCT()`
- inherits: `FAnimNextApplyAdditiveKeyframeTask`
- desc: Apply Additive Keyframe Per Bone Task This pops the top two keyframes from the VM keyframe stack, it applies an additive keyframe with a weight per bone based on the given blend mask onto its base and pushes back the result onto the stack. If no valid blend mask is provided it will revert back to a full pose additive application. The top pose should be the additive keyframe and the second to the top the base keyframe. This task currently only supports skeleton-based blend masks.
- L57 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FUAFApplyAdditiveKeyframeWithBlendMaskTask) static FUAFApplyAdditiveKeyframeWithBlendMaskTask Make(const float InBlendWeight, const UUAFBlendMask* InBlendMask);`
- L61 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L64 _public member_ `TObjectPtr<const UUAFBlendMask> BlendMask = nullptr;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/ApplyNamedSetTask.h` (Public)


#### struct `UE::UAF::FPushNamedSetTask`  
`struct FPushNamedSetTask : public FAnimNextEvaluationTask`  
_L20-33_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Push Named Set Task This pushes a new named set to evaluate with. Subsequent tasks will use that set to evaluate.
- L24 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FPushNamedSetTask) static FPushNamedSetTask Make(FName SetName);`
- L29 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L32 _public member_ `FName SetName = NAME_None;` — The named set to push

#### struct `UE::UAF::FPopNamedSetTask`  
`struct FPopNamedSetTask : public FAnimNextEvaluationTask`  
_L42-55_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Pop Named Set Task This pops the current active named set. Subsequent tasks will no longer use that named set. We only pop the active named set if it is the one we expect.
- L46 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FPopNamedSetTask) static FPopNamedSetTask Make(FName ExpectedSetName);`
- L51 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L54 _public member_ `FName ExpectedSetName = NAME_None;` — The named set expected to pop

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/BlendKeyframes.h` (Public)


#### struct `FAnimNextBlendTwoKeyframesTask`  
`struct FAnimNextBlendTwoKeyframesTask : public FAnimNextEvaluationTask`  
_L41-68_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L45 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextBlendTwoKeyframesTask) static FAnimNextBlendTwoKeyframesTask Make(float InterpolationAlpha);`
- L48 _public prototype_ `static FAnimNextBlendTwoKeyframesTask Make(const FName& AlphaSourceCurveName, const int8 AlphaCurveInputIndex, TFunction<float(float)> InputScaleBiasClampFn);`
- L52 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L55 _public prototype_ `float GetInterpolationAlpha(const UE::UAF::FKeyframeState* KeyframeA, const UE::UAF::FKeyframeState* KeyframeB) const;` — Compute the current alpha value for curves or return the interpolation alpha otherwise
- L56 _public prototype_ `float GetInterpolationAlpha(const UE::UAF::FValueBundle& CollectionA, const UE::UAF::FValueBundle& CollectionB) const;`
- L60 _public member_ `float InterpolationAlpha = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The interpolation alpha between the two input keyframes
- L63 _public member_ `FName AlphaSourceCurveName = NAME_None;` — The curve to evaluate and extract the interpolation alpha between the two input keyframes
- L65 _public member_ `int8 AlphaCurveInputIndex = INDEX_NONE;`
- L67 _public member_ `TFunction<float(float)> InputScaleBiasClampFn = nullptr;`

#### struct `FAnimNextBlendOverwriteKeyframeWithScaleTask`  
`struct FAnimNextBlendOverwriteKeyframeWithScaleTask : public FAnimNextEvaluationTask`  
_L80-94_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Blend Overwrite Keyframe With Scale Task This pops the top keyframe from the VM keyframe stack, it scales it by a factor, and pushes back the result onto the stack. Top = Top * ScaleFactor Note that rotations will not be normalized after this task.
- L84 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextBlendOverwriteKeyframeWithScaleTask) static FAnimNextBlendOverwriteKeyframeWithScaleTask Make(float ScaleFactor);`
- L89 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L93 _public member_ `float ScaleFactor = 1.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The scale factor to apply to the keyframe

#### struct `FAnimNextBlendAddKeyframeWithScaleTask`  
`struct FAnimNextBlendAddKeyframeWithScaleTask : public FAnimNextEvaluationTask`  
_L107-121_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Blend Add Keyframe With Scale Task This pops the top two keyframes (A and B) from the VM keyframe stack (let B be at the top). B is our intermediary result that we add on top of; while A is the keyframe we scale. The result is pushed back onto the stack. Top = Top + (Top-1 * ScaleFactor) Note that rotations will not be normalized after this task.
- L111 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextBlendAddKeyframeWithScaleTask) static FAnimNextBlendAddKeyframeWithScaleTask Make(float ScaleFactor);`
- L116 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L120 _public member_ `float ScaleFactor = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The scale factor to apply to the keyframe

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/BlendKeyframesPerBone.h` (Public)


#### struct `FAnimNextBlendOverwriteKeyframePerBoneWithScaleTask`  
`struct FAnimNextBlendOverwriteKeyframePerBoneWithScaleTask : public FAnimNextBlendOverwriteKeyframeWithScaleTask`  
_L35-53_
- reflection: `USTRUCT()`
- inherits: `FAnimNextBlendOverwriteKeyframeWithScaleTask`
- desc: Blend Overwrite Keyframe Per Bone With Scale Task This pops the top keyframe from the VM keyframe stack, it scales each bone by a factor, and pushes back the result onto the stack. Top = Top * ScaleFactor If no blend profile is provided but the blend data contains valid per bone blend weights, it will try to use that data to blend each bone together with the assumption the provided data encompasses the full pose. If neither is provided. this task behaves like FAnimNextBlendOverwriteKeyframeWithScaleTask Note that rotations will not be normalized after this task.
- L39 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextBlendOverwriteKeyframePerBoneWithScaleTask) static FAnimNextBlendOverwriteKeyframePerBoneWithScaleTask Make(const USkeleton* Skeleton, const FBlendSampleData& BlendData, float ScaleFactor);`
- L44 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L49 _public member_ `const FBlendSampleData* BlendData = nullptr;` — `UPROPERTY()` — The blend data associated with the keyframe to overwrite Cannot use a UPROPERTY with a pointer to a struct
- L52 _public member_ `const USkeleton* SourceSkeleton = nullptr;` — Optional skeleton to perform skeleton remapping with

#### struct `FAnimNextBlendAddKeyframePerBoneWithScaleTask`  
`struct FAnimNextBlendAddKeyframePerBoneWithScaleTask : public FAnimNextBlendAddKeyframeWithScaleTask`  
_L70-93_
- reflection: `USTRUCT()`
- inherits: `FAnimNextBlendAddKeyframeWithScaleTask`
- desc: Blend Add Keyframe Per Bone With Scale Task This pops the top two keyframes (A and B) from the VM keyframe stack (let B be at the top). B is our intermediary result that we add on top of; while A is the keyframe we scale. The result is pushed back onto the stack. Top = Top + (Top-1 * ScaleFactor) If no blend profile is provided but the blend data contains valid per bone blend weights, it will try to use that data to blend each bone together with the assumption the provided data encompasses the full pose. If neither is provided, this task behaves like FAnimNextBlendAddKeyframeWithScaleTask Note that rotations will not be normalized after this task.
- L74 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextBlendAddKeyframePerBoneWithScaleTask) static FAnimNextBlendAddKeyframePerBoneWithScaleTask Make(const USkeleton* Skeleton, const FBlendSampleData& BlendDataA, const FBlendSampleData& BlendDataB, float ScaleFactor);`
- L79 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L84 _public member_ `const FBlendSampleData* BlendDataA = nullptr;` — `UPROPERTY()` — The blend data associated with the keyframe A Cannot use a UPROPERTY with a pointer to a struct
- L89 _public member_ `const FBlendSampleData* BlendDataB = nullptr;` — `UPROPERTY()` — The blend data associated with the keyframe B Cannot use a UPROPERTY with a pointer to a struct
- L92 _public member_ `const USkeleton* SourceSkeleton = nullptr;` — Optional skeleton to perform skeleton remapping with

#### struct `FAnimNextBlendKeyframePerBoneWithScaleTask`  
`struct FAnimNextBlendKeyframePerBoneWithScaleTask : public FAnimNextBlendAddKeyframeWithScaleTask`  
_L97-122_
- reflection: `USTRUCT()`
- inherits: `FAnimNextBlendAddKeyframeWithScaleTask`
- L101 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextBlendKeyframePerBoneWithScaleTask) static FAnimNextBlendKeyframePerBoneWithScaleTask Make(const UUAFBlendMask* InBlendMask, const float ScaleFactor);`
- L106 _public prototype_ `static FAnimNextBlendKeyframePerBoneWithScaleTask Make( const USkeleton* Skeleton, const UUAFBlendMask::FSkeletonBoneWeightArray* InBoneWeights, const UUAFBlendMask::FSkeletonCurveWeightArray* InCurveWeights, const UUAFBlendMask::FSkeletonAttributeWeightArray* InAttributeWeights, float ScaleFactor);` — Curve Weights and Attribute Weights can be provided as empty views
- L114 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L117 _private member_ `const UUAFBlendMask::FSkeletonBoneWeightArray* BoneMaskWeights;`
- L118 _private member_ `const UUAFBlendMask::FSkeletonCurveWeightArray* CurveMaskWeights;`
- L119 _private member_ `const UUAFBlendMask::FSkeletonAttributeWeightArray* AttributeMaskWeights;`
- L121 _private member_ `const USkeleton* SourceSkeleton = nullptr;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/ConvertRotationsToLocalSpace.h` (Public)


#### struct `FAnimNextConvertRotationsToLocalSpaceTask`  
`struct FAnimNextConvertRotationsToLocalSpaceTask : public FAnimNextEvaluationTask`  
_L13-27_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L17 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextConvertRotationsToLocalSpaceTask) static FAnimNextConvertRotationsToLocalSpaceTask Make(const int32 NumPoses);`
- L21 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L26 _private member_ `int32 NumPoses = 0;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The number of poses on the stack to convert

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/ConvertRotationsToMeshSpace.h` (Public)


#### struct `FAnimNextConvertRotationsToMeshSpaceTask`  
`struct FAnimNextConvertRotationsToMeshSpaceTask : public FAnimNextEvaluationTask`  
_L13-27_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L17 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextConvertRotationsToMeshSpaceTask) static FAnimNextConvertRotationsToMeshSpaceTask Make(const int32 NumPoses);`
- L21 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L26 _private member_ `int32 NumPoses = 0;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The number of poses on the stack to convert

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/DeadBlending.h` (Public)


#### struct `UE::UAF::FDeadBlendTransitionTaskParameters`  
`struct FDeadBlendTransitionTaskParameters`  
_L25-33_
- desc: FDeadBlendTransitionTaskParameters Parameters for the Dead Blending Transition Task. This should be filled according to the values provided by the Dead Blending Trait shared data.
- L27 _public member_ `float ExtrapolationHalfLife = 0.0f;`
- L28 _public member_ `float ExtrapolationHalfLifeMin = 0.0f;`
- L29 _public member_ `float ExtrapolationHalfLifeMax = 0.0f;`
- L30 _public member_ `float MaximumTranslationVelocity = 0.0f;`
- L31 _public member_ `float MaximumRotationVelocity = 0.0f;`
- L32 _public member_ `float MaximumScaleVelocity = 0.0f;`

#### struct `FAnimNextDeadBlendingTransitionTask`  
`struct FAnimNextDeadBlendingTransitionTask : public FAnimNextEvaluationTask`  
_L46-82_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: FAnimNextDeadBlendingTransitionTask Task for performing a Dead Blending transition. Stores the current pose state, computes the velocity using finite difference, and fits extrapolation half-lives based on the state being transitioned to.
- L50 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextDeadBlendingTransitionTask)`
- L61 _public prototype_ `static FAnimNextDeadBlendingTransitionTask Make( UE::UAF::FDeadBlendingState* State, const UE::UAF::FTransformArraySoAHeap* CurrPose, const UE::UAF::FDeadBlendTransitionTaskParameters& Parameters);` — Make a DeadBlendingTransitionTask using only a single previous poses
- L67 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L71 _public member_ `UE::UAF::FDeadBlendingState* State = nullptr;`
- L75 _public member_ `const UE::UAF::FTransformArraySoAHeap* CurrPose = nullptr;`
- L76 _public member_ `const UE::UAF::FTransformArraySoAHeap* PrevPose = nullptr;`
- L80 _public member_ `float DeltaTime = 0.0f;`
- L81 _public member_ `UE::UAF::FDeadBlendTransitionTaskParameters Parameters;`

#### struct `FAnimNextDeadBlendingApplyTask`  
`struct FAnimNextDeadBlendingApplyTask : public FAnimNextEvaluationTask`  
_L92-121_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: FAnimNextDeadBlendingApplyTask Task for applying dead blending to remove a discontinuity. Will extrapolate the FDeadBlendingState forward in time and then blend it with the Keyframe which is on top of the stack according to the BlendDuration. Part of the FDeadBlendingState will be updated to ensure the blend does not "flip sides" part way through.
- L96 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextDeadBlendingApplyTask)`
- L107 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L111 _public member_ `UE::UAF::FDeadBlendingState* State = nullptr;`
- L115 _public member_ `float BlendDuration = 0.0f;`
- L116 _public member_ `float TimeSinceTransition = 0.0f;`
- L117 _public member_ `EAlphaBlendOption BlendMode = EAlphaBlendOption::Linear;`
- L120 _public member_ `TWeakObjectPtr<UCurveFloat> CustomBlendCurve = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/DecompressionTools.h` (Public)


#### class `UE::UAF::FDecompressionTools`  
`class FDecompressionTools`  
_L25-87_
- L29 _public prototype_ `static bool ShouldUseRawData(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext);` — Returns whether decompression should use raw data or not
- L33 _public prototype_ `static void GetAnimationPose(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, FLODPose& OutAnimationPoseData, bool bForceUseRawData = false);` — Extracted from UAnimSequence Extracts Animation Data from the provided AnimSequence, using AnimExtractContext extraction parameters
- L34 _public prototype_ `static void GetAnimationPose(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, const FEvaluationTaskContext& VMContext, FValueBundle& OutCollection, bool bForceUseRawData = false);`
- L41 _public prototype_ `static void GetAnimationPose( const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, FLODPose& OutAnimationPoseData, bool bForceUseRawData, bool bSuppressForceRootLock);` — Extracts a pose, optionally leaving the root bone animated even when the anim sequence has Force Root Lock enabled. Pass true for bSuppressForceRootLock only when the caller takes over root bone handling and pins the root itself.
- L52 _public prototype_ `static void GetBonePose(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, FLODPose& OutAnimationPoseData, bool bForceUseRawData = false);` — Get Bone Transform of the Time given, relative to Parent for all RequiredBones This returns different transform based on additive or not. Or what kind of additive.
- L54 _public prototype_ `static void GetBonePose_Additive(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, FLODPose& OutAnimationPoseData);`
- L55 _public prototype_ `static void GetBonePose_AdditiveMeshRotationOnly(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, FLODPose& OutAnimationPoseData);`
- L57 _public prototype_ `static void GetAnimationCurves(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, FBlendedCurve& OutCurves, bool bForceUseRawData = false);`
- L58 _public prototype_ `static void GetAnimationCurves(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, const FEvaluationTaskContext& VMContext, FValueBundle& OutCollection, bool bForceUseRawData = false);`
- L60 _public prototype_ `static void GetAnimationAttributes(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, const FReferencePose& RefPose, UE::Anim::FStackAttributeContainer& OutAttributes, bool bForceUseRawData = false);`
- L61 _public prototype_ `static void GetAnimationAttributes(const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, const FEvaluationTaskContext& VMContext, FValueBundle& OutCollection, bool bForceUseRawData = false);`
- L64 _public prototype_ `static void DecompressPose(FLODPose& OutAnimationPoseData, const FCompressedAnimSequence& CompressedData, const FAnimExtractContext& ExtractionContext, FAnimSequenceDecompressionContext& DecompressionContext, const TArray<FTransform>& RetargetTransforms, const FRootMotionReset& RootMotionReset);` — Decompress and retarget animation data using provided RetargetTransforms
- L72 _public prototype_ `static void DecompressPose(FLODPose& OutAnimationPoseData, const FCompressedAnimSequence& CompressedData, const FAnimExtractContext& ExtractionContext, FAnimSequenceDecompressionContext& DecompressionContext, FName RetargetSource, const FRootMotionReset& RootMotionReset);` — Decompress and retarget animation data
- L81 _private prototype_ `static void GetBonePose( const UAnimSequence* AnimSequence, const FAnimExtractContext& ExtractionContext, FLODPose& OutAnimationPoseData, bool bForceUseRawData, bool bSuppressForceRootLock);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/ExecuteProgram.h` (Public)


#### struct `FAnimNextExecuteProgramTask`  
`struct FAnimNextExecuteProgramTask : public FAnimNextEvaluationTask`  
_L24-37_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Execute Program Task This allows external caching of evaluation programs by deferring evaluation or repeated evaluations.
- L28 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextExecuteProgramTask) static FAnimNextExecuteProgramTask Make(TSharedPtr<const UE::UAF::FEvaluationProgram> Program);`
- L33 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L36 _public member_ `TSharedPtr<const UE::UAF::FEvaluationProgram> Program = nullptr;` — The program to execute

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/MakeDynamicAdditive.h` (Public)


#### struct `FUAFMakeDynamicAdditiveTask`  
`struct FUAFMakeDynamicAdditiveTask : public FAnimNextEvaluationTask`  
_L18-28_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Make Dynamic Additive Task Pops the top two keyframes of the stack, creates a new additive pose and pushes it back onto the stack. The top pose should be the keyframe to turn into an additive and the second to the top should be the base keyframe.
- L22 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FUAFMakeDynamicAdditiveTask) static FUAFMakeDynamicAdditiveTask Make(const EAdditiveAnimationType InAdditiveType);`
- L25 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L27 _public member_ `EAdditiveAnimationType AdditiveType = AAT_LocalSpaceBase;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/NormalizeRotations.h` (Public)


#### struct `FAnimNextNormalizeKeyframeRotationsTask`  
`struct FAnimNextNormalizeKeyframeRotationsTask : public FAnimNextEvaluationTask`  
_L19-27_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Normalize Keyframe Rotations Task This pop the top keyframe from the VM keyframe stack, it normalizes its rotations, and pushes back the result onto the stack.
- L23 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextNormalizeKeyframeRotationsTask)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/PushAnimSequenceKeyframe.h` (Public)


#### struct `FAnimNextAnimSequenceKeyframeTask`  
`struct FAnimNextAnimSequenceKeyframeTask : public FAnimNextEvaluationTask`  
_L21-61_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Push Anim Sequence Keyframe Task This pushes an anim sequence keyframe onto the top of the VM keyframe stack.
- L25 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextAnimSequenceKeyframeTask) static FAnimNextAnimSequenceKeyframeTask MakeFromSampleTime(TWeakObjectPtr<const UAnimSequence> AnimSequence, double SampleTime, bool bInterpolate);`
- L28 _public prototype_ `static FAnimNextAnimSequenceKeyframeTask MakeFromKeyframeIndex(TWeakObjectPtr<const UAnimSequence> AnimSequence, uint32 KeyframeIndex);`
- L31 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L35 _public member_ `TWeakObjectPtr<const UAnimSequence> AnimSequence;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Anim Sequence to grab the keyframe from
- L38 _public member_ `FDeltaTimeRecord DeltaTimeRecord;` — Delta time range required for root motion extraction
- L43 _public member_ `double SampleTime = -1.0;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The point in time within the animation sequence at which we sample the keyframe. If negative, the sample time hasn't been provided and we should use the keyframe index.
- L48 _public member_ `uint32 KeyframeIndex = ~0;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — The specific keyframe within the animation sequence to retrieve. If ~0, the keyframe index hasn't been provided and we should use the sample time.
- L53 _public member_ `bool bInterpolate = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Whether to interpolate or step the animation sequence. Only used when the sample time is used.
- L57 _public member_ `bool bExtractTrajectory = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Whether to extract trajectory or not
- L60 _public member_ `bool bLooping = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/PushPose.h` (Public)


#### struct `FAnimNextPushPoseTask`  
`struct FAnimNextPushPoseTask : public FAnimNextEvaluationTask`  
_L17-33_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L23 _public prototype_ `FAnimNextPushPoseTask() = default;`
- L24 _public prototype_ `FAnimNextPushPoseTask(const FAnimNextGraphLODPose* InGraphPose);`
- L26 _public prototype_ `static FAnimNextPushPoseTask Make(const FAnimNextGraphLODPose* InGraphPose);`
- L28 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L30 _public prototype_ `FAnimNextPushPoseTask& operator=(const FAnimNextPushPoseTask& Other);`
- L32 _public member_ `const FAnimNextGraphLODPose* GraphPose = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF Task: PushPose"), STAT_AnimNext_Task_PushPose, STATGROUP_AnimNext,`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/PushReferenceKeyframe.h` (Public)


#### struct `FAnimNextPushReferenceKeyframeTask`  
`struct FAnimNextPushReferenceKeyframeTask : public FAnimNextEvaluationTask`  
_L20-35_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Push Reference Keyframe Task This pushes a reference keyframe onto the top of the VM keyframe stack. This task can be used to push the reference keyframe from a source skeleton or the additive identity.
- L24 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextPushReferenceKeyframeTask) static FAnimNextPushReferenceKeyframeTask MakeFromSkeleton();`
- L27 _public prototype_ `static FAnimNextPushReferenceKeyframeTask MakeFromAdditiveIdentity();`
- L30 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L34 _public member_ `bool bIsAdditive = false;` — `UPROPERTY(VisibleAnywhere, Category = Properties)` — Whether or not the reference pose comes from the skeleton or is the additive identity

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/EvaluationVM/Tasks/StoreKeyframe.h` (Public)


#### struct `FAnimNextSwapTransformsTask`  
`struct FAnimNextSwapTransformsTask : public FAnimNextEvaluationTask`  
_L17-30_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Swap the two given Transform Arrays
- L21 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextSwapTransformsTask) static FAnimNextSwapTransformsTask Make(UE::UAF::FTransformArraySoAHeap* A, UE::UAF::FTransformArraySoAHeap* B);`
- L26 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L28 _public member_ `UE::UAF::FTransformArraySoAHeap* A = nullptr;`
- L29 _public member_ `UE::UAF::FTransformArraySoAHeap* B = nullptr;`

#### struct `FAnimNextStoreKeyframeTransformsTask`  
`struct FAnimNextStoreKeyframeTransformsTask : public FAnimNextEvaluationTask`  
_L36-48_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Store the pose on top of the stack in the given Transform Array
- L40 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextStoreKeyframeTransformsTask) static FAnimNextStoreKeyframeTransformsTask Make(UE::UAF::FTransformArraySoAHeap* Dest);`
- L45 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L47 _public member_ `UE::UAF::FTransformArraySoAHeap* Dest = nullptr;`

#### struct `FAnimNextDuplicateTopKeyframeTask`  
`struct FAnimNextDuplicateTopKeyframeTask : public FAnimNextEvaluationTask`  
_L54-64_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Duplicates the pose on top of the stack and pushes it as new top
- L58 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextDuplicateTopKeyframeTask) static FAnimNextDuplicateTopKeyframeTask Make();`
- L63 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Factory/AnimAssetParams.h` (Public)


#### enum `UE::UAF::EAnimAssetLoopMode`  
`enum class EAnimAssetLoopMode : uint8`  
_L10-20_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Auto` — Asset will use the looping value defined in the asset.
- L16 _public enumerator_ `ForceLoop` — Asset will loop regardless of the value defined in the asset.
- L19 _public enumerator_ `ForceNonLoop` — Asset will NOT loop regardless of the value defined in the asset.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Factory/AnimGraphFactory.h` (Public)


#### struct `UE::UAF::FAnimGraphFactory`  
`struct FAnimGraphFactory`  
_L32-97_
- desc: Creates or recycles programmatically-generated graphs Uses the hash of the recipe to determine if the graph has been created already. If the hash matches one that has already been created but graph has already been GCed it will be re-created as needed.
- L35 _public prototype_ `static const UUAFAnimGraph* GetOrBuildGraph(UE::UAF::FGraphAssetHandleConstView InAsset, const FAnimNextFactoryParams& Params = FAnimNextFactoryParams());` — warning: duplicate functionality with IGraphFactory
- L38 _public prototype_ `static const UUAFAnimGraph* BuildGraph(const IAnimGraphBuilder& InBuilder);` — Make a graph from the specified recipe
- L41 _public prototype_ `static const UUAFAnimGraph* GetDefaultGraphHost();` — Make the default graph for running a UUAFAnimGraph asset (allowing graphs to blend between each other)
- L43 _public prototype_ `static FAnimNextFactoryParams GetDefaultParamsForAsset(FGraphAssetHandleConstView Asset);`
- L46 _public prototype_ `static void InitializeDefaultParamsForAsset(FGraphAssetHandleConstView Asset, FAnimNextFactoryParams& InOutParams);` — Applies default initializer to the params (usually injecting the object pointer)
- L49 _public typedef_ `template<typename TAssetData> using TParamsInitializer = TFunction<void(const TAssetData&, FAnimNextFactoryParams&)>;`
- L52 _public function_ `template<typename TAssetData> static void RegisterAsset(FAnimNextFactoryParams&& InParams, TParamsInitializer<TAssetData>&& InInitializer = nullptr)`
- L73 _public function_ `static TConstArrayView<TSoftObjectPtr<UScriptStruct>> GetSupportedAssetDataTypes()`
- L77 _private prototype_ `static void Init();` — Called on module init
- L80 _private prototype_ `static void Destroy();` — Called on module shutdown to unload everything
- L83 _private prototype_ `static void OnPreExit();` — Called before engine shutdown to clear internal state while UObjects are still valid
- L86 _private typedef_ `using FParamsInitializer = TFunction<void(const TConstStructView<FUAFGraphFactoryAsset>&, FAnimNextFactoryParams&)>;` — Function used to initialize the object for the factory-generated graph
- L89 _private prototype_ `static void RegisterAsset(const TSubScriptStructOf<FUAFGraphFactoryAsset>& AssetStructType, FAnimNextFactoryParams&& InParams, FParamsInitializer&& InInitializer);` — Register default params used to build & initialize a graph according to the supplied asset class
- L91 _private prototype_ `static const TPair<FAnimNextFactoryParams, FParamsInitializer>* FindGraphParamsForAssetData(FGraphAssetHandleConstView AssetData);`
- L92 _private member_ `static TMap<FTopLevelAssetPath, TPair<FAnimNextFactoryParams, FParamsInitializer>> DefaultParamsForObject;`
- L94 _private member_ `static TArray<TSoftObjectPtr<UScriptStruct>> AllFactoryStructs;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)
- L59 _function_ `` (scope `UE::UAF::FAnimGraphFactory::RegisterAsset`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Factory/AnimNextAnimGraphBuilder.h` (Public)


#### enum `UE::UAF::ETraitVariableMapping`  
`enum class ETraitVariableMapping : uint8`  
_L21-27_
- L24 _public enumerator_ `None` — Dont add trait's variables to the public variables of the graph
- L26 _public enumerator_ `All` — Add the trait's variables to the public variables and map all of them to the trait

#### struct `UE::UAF::IAnimGraphBuilder`  
`struct IAnimGraphBuilder`  
_L30-44_
- desc: A method for making a graph in FAnimGraphFactory procedurally
- L32 _public prototype_ `virtual ~IAnimGraphBuilder() = default;`
- L40 _private function_ `virtual bool Build(FAnimGraphBuilderContext& InContext) const` — Primary entry point for factory method for procedurally generating graphs Fills the supplied context used to generate the graph @return true if the graph factory context was written successfully, false otherwise
- L43 _private prototype_ `virtual uint64 GetKey() const;` — Get a uniquely-identifying key that we use to avoid rebuilding graphs

#### struct `FAnimNextAnimGraphBuilder`  
`struct FAnimNextAnimGraphBuilder #if CPP : public UE::UAF::IAnimGraphBuilder #endif`  
_L50-73_
- reflection: `USTRUCT()`
- inherits: `UE::UAF::IAnimGraphBuilder`
- desc: Base struct for procedural graph methods that need to persist or be referenced in data
- L59 _protected function_ `void InvalidateKey()` — Invalidate the key if the method's params change, it will be lazily recalculated
- L65 _protected function_ `virtual uint64 RecalculateKey() const` — Recalculates the key - called lazily when the key is retrieved
- L68 _protected prototype_ `virtual uint64 GetKey() const override;` — IAnimGraphBuilder interface
- L72 _private member_ `mutable uint64 CachedKey = 0;` — Cached key based on serialized properties

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Factory/AnimNextFactoryParams.h` (Public)


#### struct `FAnimNextFactoryParams`  
`struct FAnimNextFactoryParams`  
_L34-172_
- reflection: `USTRUCT(BlueprintType)`
- desc: Set of parameters that describe a way of generating & initializing an animation graph TODO: To add an internal trait, use AddInternalTrait. TODO: Interface to map public interface to internal traits
- L38 _public prototype_ `FAnimNextFactoryParams() = default;`
- L41 _public function_ `bool IsValid() const` — Whether these params are valid for application
- L50 _public function_ `template<typename StructType> void AddTraitStruct(UE::UAF::ETraitVariableMapping InMapping, int32 InStackIndex)` — Push a trait struct onto the specified stack in the graph builder, initialized to the struct's defaults. The trait struct forms part of the created instance's 'public interface' if InMapping is 'All'. If a trait already exists of this type then its values be overriden
- L59 _public function_ `template<typename StructType> bool AccessTraitStruct(int32 InStackIndex, TFunctionRef<void(StructType&)> InFunction)` — Access a trait's struct during initialization (for instance to inject an AnimSequence)
- L77 _public function_ `void AddPublicVariablesStructByType(const TObjectPtr<const UScriptStruct>& InStruct)`
- L84 _public function_ `void AddPublicVariablesRigVMAsset(const TScriptInterface<const IRigVMRuntimeAssetInterface>& RigVMAsset)` — Add a public variables rig VM asset to these params. This will act as part of the public API of the system. If a asset reference already exists of this type then its values be overriden by virtue of the initializer running later
- L91 _public function_ `void AddPublicVariablesAsset(const TObjectPtr<const UUAFRigVMAsset>& UAFAsset)` — Add a public shared variables asset to these params. This will act as part of the public API of the system. If a asset reference already exists of this type then its values be overriden by virtue of the initializer running later
- L100 _public function_ `template<typename StructType> void AddTrait(UE::UAF::ETraitVariableMapping InMapping, int32 InStackIndex, const StructType& InValue)` — Push a trait struct onto the specified stack in the graph builder, initialized to the supplied value The trait struct forms part of the created instance's 'public interface' if InMapping is 'All'. If a trait already exists of this type then its values be overriden
- L106 _public function_ `void AddLink(int32 InOutputStackIndex, int32 InInputStackIndex, int32 InInputTraitIndex, FName InInputChildName)` — Add a link between the output of the specified stack and the input stack's child
- L113 _public function_ `template<typename StructType> void AddVariableStruct()` — Add a variable struct
- L119 _public function_ `FAnimNextFactoryParams& AddVariableMapping(FAnimNextVariableReference InVariable, int32 InInputStackIndex, int32 InInputTraitIndex, FName InInputPropertyName)` — Add a variable mapping between a public variable and a specific trait's latent property
- L126 _public function_ `FAnimNextFactoryParams& AddVariableMappingToAll(FAnimNextVariableReference InVariable, FName InInputPropertyName)` — Add a variable mapping between a public variable and all trait latent properties of the specified name
- L134 _public function_ `template<typename ComponentType> void AddComponent()` — Add a component
- L141 _public function_ `const UE::UAF::IAnimGraphBuilder& GetBuilder() const` — Get the builder that these params hold
- L147 _public function_ `FAnimNextFactoryParams& AddInitializeTask(UE::UAF::FInstanceTask&& InTask)` — Add an initialize task used to set up an instance when these params are applied
- L154 _public prototype_ `void Reset();` — Clear these parameters back to empty
- L164 _private prototype_ `void InitializeInstance(FUAFAssetInstance& InInstance) const;` — Apply these params to the supplied instance.
- L168 _private member_ `FAnimNextSimpleAnimGraphBuilder Builder;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Method used to create a graph
- L171 _private member_ `TArray<UE::UAF::FInstanceTask> InitializeTasks;` — Tasks to run on the factory-generated graph instance via InitializeInstance, used for initial setup of variables etc.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Factory/AnimNextSimpleAnimGraphBuilder.h` (Public)


#### struct `FAnimNextSimpleAnimGraphBuilderLinkDesc`  
`struct FAnimNextSimpleAnimGraphBuilderLinkDesc`  
_L31-50_
- reflection: `USTRUCT()`
- L41 _private member_ `int32 StackIndex = INDEX_NONE;` — `UPROPERTY()` — The index of the stack this stack's output is linked to
- L45 _private member_ `int32 TraitIndex = INDEX_NONE;` — `UPROPERTY()` — The index of the trait this stack's output is linked to
- L49 _private member_ `FName ChildName;` — `UPROPERTY()` — The name of the child this stack's output is linked to

#### struct `FAnimNextSimpleAnimGraphBuilderVariableMapping`  
`struct FAnimNextSimpleAnimGraphBuilderVariableMapping`  
_L53-67_
- reflection: `USTRUCT()`
- L62 _private member_ `FAnimNextVariableReference VariableReference;` — `UPROPERTY()`
- L66 _private member_ `FName PropertyName;` — `UPROPERTY()` — The name of the property the variable should be applied to

#### struct `FAnimNextSimpleAnimGraphBuilderTraitDesc`  
`struct FAnimNextSimpleAnimGraphBuilderTraitDesc`  
_L70-87_
- reflection: `USTRUCT()`
- L83 _private member_ `TInstancedStruct<FAnimNextTraitSharedData> TraitData;` — `UPROPERTY(EditAnywhere, Category = Parameters)`
- L86 _private member_ `TArray<FAnimNextSimpleAnimGraphBuilderVariableMapping> VariableMappings;` — `UPROPERTY()`

#### struct `FAnimNextSimpleAnimGraphBuilderTraitStackDesc`  
`struct FAnimNextSimpleAnimGraphBuilderTraitStackDesc`  
_L90-115_
- reflection: `USTRUCT()`
- L105 _private member_ `TArray<TInstancedStruct<FAnimNextTraitSharedData>> TraitStructs_DEPRECATED;` — `UPROPERTY()` — Traits for this stack
- L110 _private member_ `TArray<FAnimNextSimpleAnimGraphBuilderTraitDesc> TraitDescs;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Traits for this stack
- L114 _private member_ `FAnimNextSimpleAnimGraphBuilderLinkDesc Link;` — `UPROPERTY()` — The link for this stack's output pose

#### struct `FAnimNextSimpleAnimGraphBuilder`  
`struct FAnimNextSimpleAnimGraphBuilder : public FAnimNextAnimGraphBuilder`  
_L118-205_
- reflection: `USTRUCT()`
- inherits: `FAnimNextAnimGraphBuilder`
- L124 _public prototype_ `void AddTraitStructView(int32 InStackIndex, UE::UAF::ETraitVariableMapping InMapping, TConstStructView<FAnimNextTraitSharedData> InStruct);` — Push a trait struct onto the supplied stack. Traits are ordered from bottom to top, stack-wise. Struct must be a sub-struct of FAnimNextTraitSharedData
- L125 _public prototype_ `void AddTraitInstancedStruct(int32 InStackIndex, UE::UAF::ETraitVariableMapping InMapping, TInstancedStruct<FAnimNextTraitSharedData>&& InStruct);`
- L128 _public prototype_ `void AddLink(int32 InOutputStackIndex, int32 InInputStackIndex, int32 InInputTraitIndex, FName InInputChildName);` — Add a link between the output of the specified stack and the input stack's child
- L131 _public prototype_ `void AddVariableMapping(FAnimNextVariableReference InVariable, int32 InInputStackIndex, int32 InInputTraitIndex, FName InInputPropertyName);` — Add a variable mapping between a public variable and a trait's latent property
- L134 _public prototype_ `void AddVariableMappingToAll(FAnimNextVariableReference InVariable, FName InInputPropertyName);` — Add a variable mapping between a public variable and all trait latent properties of the specified name
- L137 _public prototype_ `void AddVariableStruct(const UScriptStruct* InStruct);` — Add a variable struct
- L139 _public prototype_ `void AddVariablesRigVMAsset(const TScriptInterface<const IRigVMRuntimeAssetInterface>& RigVMAssetInterface);`
- L140 _public prototype_ `void AddVariablesAsset(const TObjectPtr<const UUAFRigVMAsset>& UAFAsset);`
- L143 _public prototype_ `void AddComponentStruct(const UScriptStruct* InStruct);` — Add a component struct to this builder
- L146 _public function_ `int32 GetNumStacks() const` — Get the number of stacks from this graph
- L152 _public function_ `bool IsValid() const` — Check whether this method is empty or not
- L158 _public function_ `void Reset()` — Reset back to empty state
- L176 _private prototype_ `bool Validate() const;` — Internal helpers
- L177 _private prototype_ `bool ValidateTraitStruct(int32 InStackIndex, int32 InTraitIndex, TConstStructView<FAnimNextTraitSharedData> InStruct) const;`
- L178 _private prototype_ `bool ValidateLink(int32 InOutputStackIndex, int32 InInputStackIndex, int32 InInputTraitIndex, FName InInputChildName) const;`
- L179 _private prototype_ `bool ValidateVariableMapping(FAnimNextVariableReference InVariable, int32 InInputStackIndex, int32 InInputTraitIndex, FName InInputPropertyName) const;`
- L180 _private prototype_ `void AutoMapTraitHelper(int32 InStackIndex, const UScriptStruct* TraitStruct);`
- L183 _private prototype_ `virtual bool Build(UE::UAF::FAnimGraphBuilderContext& InContext) const override;` — FAnimNextAnimGraphBuilder interface
- L184 _private prototype_ `virtual uint64 RecalculateKey() const override;`
- L188 _private member_ `TArray<FAnimNextSimpleAnimGraphBuilderTraitStackDesc> Stacks;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — The trait stacks we will use to generate our data
- L192 _private member_ `TArray<TObjectPtr<const UScriptStruct>> VariableStructs;` — `UPROPERTY()` — All variable structs that form the public interface
- L196 _private member_ `TArray<TObjectPtr<const UScriptStruct>> ComponentStructs;` — `UPROPERTY()` — The structs we used to generate the graph's components
- L200 _private member_ `TArray<TScriptInterface<const IRigVMRuntimeAssetInterface>> ReferencedVariableRigVMAssets;` — `UPROPERTY()` — All the IRigVMRuntimeAssetInterface whose variables we will reference/instance at runtime
- L204 _private member_ `TArray<TObjectPtr<const UUAFRigVMAsset>> ReferencedVariableAssets;` — `UPROPERTY()` — All the assets whose variables we will reference/instance at runtime

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/AnimGraphReference.h` (Public)


#### struct `UE::UAF::FAnimGraphReference`  
`struct FAnimGraphReference`  
_L31-82_
- desc: An owning reference to a UAF graph. Provides a way for external systems to own an anim graph, but not have to fully allocate the graph before use
- L34 _public prototype_ `FAnimGraphReference() = default;` — Default-constructable only because it needs to be embedded in UObjects/UStructs
- L42 _public prototype_ `explicit FAnimGraphReference(TNonNullPtr<const UUAFAnimGraph> InAnimGraph, const FUAFWeakSystemReference& InSystemReference, FAnimNextFactoryParams&& InFactoryParams = FAnimNextFactoryParams());` — Construct an owning handle to a graph instance. Constructs a FAnimNextGraphInstance for use by worker threads and minimally pre-allocates it Can be called on any thread @param    InAnimGraph        The graph asset to create this instance from @param    InSystemReference  The system that the graph will be used with. Graphs can only be used within a single system @param    InFactoryParams    The factory params to construct the instance with
- L45 _public prototype_ `FWeakAnimGraphReference ToWeakRef() const;` — Make a weak reference from this owning reference
- L49 _public prototype_ `void Reset();` — Reset this handle to invalid - gives up ownership Can be called on any thread
- L53 _public prototype_ `bool IsValid() const;` — Check if this handle is valid Can be called on any thread.
- L57 _public prototype_ `[[nodiscard]] const UUAFAnimGraph* GetAnimGraph() const;` — Get the anim graph that this handle references Can be called on any thread.
- L62 _public prototype_ `void QueueTask(FUniqueAnimGraphTask&& InTaskFunction) const;` — Queue task to execute on the instance Can be called on any thread. @param	InTaskFunction		The function to run
- L65 _public prototype_ `void SetDebugName(FName InName) const;` — Sets the debug name for the instance, used for tracing etc.
- L68 _public prototype_ `void AddReferencedObjects(FReferenceCollector& InCollector) const;` — GC support
- L75 _private prototype_ `[[nodiscard]] TSharedPtr<FAnimNextGraphInstance> GetOrAllocate(FExecutionContext& InContext, const FTraitBinding& InBinding) const;` — Gets or allocate & binds the graph instance Fully allocates the graph if it is only preallocated Can be called on any thread. @param    InBinding    The current binding (this must be called during a graph execution)
- L81 _private member_ `TSharedPtr<FAnimNextGraphInstance> Ptr;` — Pointer to the instance

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/AnimGraphTaskContext.h` (Public)


#### struct `UE::UAF::FAnimGraphTaskContext`  
`struct FAnimGraphTaskContext : public FInstanceTaskContext`  
_L22-34_
- inherits: `FInstanceTaskContext`
- desc: Context struct passed to graph instance tasks, allowing setting of variables etc.
- L26 _public prototype_ `FAnimNextGraphInstance& GetAnimGraphInstance() const;` — Get the graph instance
- L33 _private prototype_ `FAnimGraphTaskContext(FAnimNextGraphInstance& InGraphInstance);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L36 _typedef_ `using FUniqueAnimGraphTask = ::TUniqueFunction<void(const FAnimGraphTaskContext& InContext)>;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/AnimNextAnimGraph.h` (Public)


#### struct `FAnimNextGraphInjectionData`  
`struct FAnimNextGraphInjectionData`  
_L51-65_
- reflection: `USTRUCT(BlueprintType)`
- desc: Injection data for an AnimNext Graph
- L55 _public function_ `bool HasValidEvaluationModifier() const`
- L58 _private member_ `TWeakPtr<UE::UAF::IEvaluationModifier> EvaluationModifier;` — Evaluation modifier to allow IEvaluate pass to be controlled
- L61 _private member_ `uint32 InjectionSerialNumber = 0;` — Serial number for the last injection that was made to this struct

#### struct `FAnimNextAnimGraph`  
`struct FAnimNextAnimGraph`  
_L74-109_
- reflection: `USTRUCT(BlueprintType, DisplayName="UAF Graph")`
- L79 _public prototype_ `FAnimNextAnimGraph() = default;` — Creates an empty graph instance that doesn't reference anything
- L83 _public member_ `TObjectPtr<const UObject> Asset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Graph, meta=(GetAllowedClasses="/Script/UAFAnimGraph.AnimNextAnimGraphSettings:GetAllowedAssetClasses", AllowPrivateAccess))` — The asset to run as an animation graph
- L87 _private prototype_ `bool IsEqualForInjectionSiteChange(const FAnimNextAnimGraph& InOther) const;` — Check if this graph is 'equal' when applied to an injection site (i.e. whether a change should trigger a re-injection)
- L91 _private member_ `FAnimNextGraphInjectionData InjectionData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Graph, meta=(AllowPrivateAccess))` — Injection data used to override the supplied graph
- L97 _private member_ `TObjectPtr<UUAFAnimGraph> HostGraph;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Graph, AdvancedDisplay, meta=(AllowPrivateAccess))` — The host graph to use to run the asset. Applies only to top-level graphs being run in modules. We use a host graph to be able to blend between graph sources at the top level of a module when a RunGraph's input graph changes. If this is unset, then the project's default host graph will be used.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace UAF` (scope `UE`)
- L39 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace UAF` (scope `UE`)
- L44 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/AnimNextAnimationGraph.h` (Public)


#### struct `UE::UAF::FGraphAllocationParams`  
`struct FGraphAllocationParams`  
_L73-83_
- desc: Parameters to AllocateInstance
- L76 _public member_ `FUAFWeakSystemReference SystemReference;` — The system to use as our outermost host
- L78 _public member_ `TWeakPtr<FAnimNextGraphInstance> ParentGraphInstance;` — The hosting/parent graph instance
- L80 _public member_ `FName EntryPoint = NAME_None;` — The entry point to use (deprecated)
- L82 _public member_ `TSharedPtr<const UE::UAF::FVariableOverridesCollection> Overrides;` — Any variable overrides to apply to this graph

#### class `UUAFAnimGraph`  
`class UUAFAnimGraph : public UUAFSharedVariables`  
_L88-202_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UUAFSharedVariables`
- desc: A user-created collection of animation logic & data
- L93 _public prototype_ `UUAFAnimGraph(const FObjectInitializer& ObjectInitializer);`
- L96 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L98 _public prototype_ `virtual void BeginDestroy() override;`
- L101 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L108 _public prototype_ `TSharedPtr<FAnimNextGraphInstance> PreAllocateInstance(const UE::UAF::FGraphAllocationParams& InParams = UE::UAF::FGraphAllocationParams(), FAnimNextFactoryParams&& InFactoryParams = FAnimNextFactoryParams()) const;` — Pre-allocates an instance of the graph @param	InParams		Parameters to pre-allocate the graph with @param	InFactoryParams	Factory parameters to apply to the graph when allocated @return the pre-allocated instance.
- L114 _public prototype_ `TSharedPtr<FAnimNextGraphInstance> AllocateInstance(const UE::UAF::FGraphAllocationParams& InParams = UE::UAF::FGraphAllocationParams(), FAnimNextFactoryParams&& InFactoryParams = FAnimNextFactoryParams()) const;` — Allocates an instance of the graph according to the supplied parameters @param	InParams		Parameters to allocate the graph with @param	InFactoryParams	Factory parameters to apply to the graph when allocated @return the allocated instance. This can be invalid if the entry point was not found or the graph's root trait is invalid.
- L118 _private prototype_ `bool LoadFromArchiveBuffer(const TArray<uint8>& SharedDataArchiveBuffer);` — Loads the graph data from the provided archive buffer and returns true on success, false otherwise
- L121 _private prototype_ `void OnPreForceDeleteObjects(const TArray<UObject*>& ObjectsToDelete);`
- L127 _private prototype_ `void FreezeGraphInstances();` — During graph compilation, if we have existing graph instances, we freeze them by releasing their memory before thawing them Freezing is a partial release of resources that retains the necessary information to re-create things safely
- L130 _private prototype_ `void ThawGraphInstances();` — During graph compilation, once compilation is done we thaw existing graph instances to reallocate their memory
- L153 _protected member_ `mutable FCriticalSection GraphInstancesLock;`
- L156 _protected member_ `mutable TSet<FAnimNextGraphInstance*> GraphInstances;` — This is a list of live graph instances that have been allocated, used in the editor to reset instances when we re-compile/live edit
- L161 _protected member_ `FAnimNextGraphEvaluatorExecuteDefinition ExecuteDefinition;` — `UPROPERTY()` — This is the execute method definition used by a graph to evaluate latent pins
- L165 _protected member_ `TArray<FAnimNextGraphEntryPoint> EntryPoints;` — `UPROPERTY()` — Data for each entry point in this graph
- L168 _protected member_ `TMap<FName, FAnimNextTraitHandle> ResolvedRootTraitHandles;` — This is a resolved handle to the root trait in our graph, for each entry point
- L171 _protected member_ `TMap<FName, int32> ResolvedEntryPoints;` — This is an index into EntryPoints, for each entry point
- L175 _protected member_ `TArray<uint8> SharedDataBuffer;` — This is the graph shared data used by the trait system, the output of FTraitReader We de-serialize manually into this buffer from the archive buffer, this is never saved on disk
- L182 _protected member_ `TArray<TObjectPtr<UObject>> GraphReferencedObjects;` — `UPROPERTY()` — This is a list of all referenced UObjects in the graph shared data We collect all the references here to make it quick and easy for the GC to query them It means that object references in the graph shared data are not visited at runtime by the GC (they are immutable) The shared data serialization archive stores indices to these to perform UObject serialization
- L187 _protected member_ `TArray<FSoftObjectPath> GraphReferencedSoftObjects;` — `UPROPERTY()` — This is a list of all referenced soft objects in the graph shared data Used to serialize the soft objects correctly as we dont use FArchiveUObject
- L191 _protected member_ `FName DefaultEntryPoint = TEXT("Roo` — `UPROPERTY(EditAnywhere, Category = "Graph")` — The entry point that this graph defaults to using
- L195 _protected member_ `FAnimNextGraphState DefaultState;` — `UPROPERTY()` — Default state for this graph
- L200 _protected member_ `TArray<uint8> SharedDataArchiveBuffer;` — This buffer holds the output of the FTraitWriter post compilation We serialize it manually and it is discarded at runtime

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UAF` (scope `UE`)
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace UAF` (scope `UE`)
- L48 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace UAF` (scope `UE`)
- L53 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L59 _namespace_ `namespace UE`
- L59 _namespace_ `namespace UAF` (scope `UE`)
- L59 _namespace_ `namespace AnimGraph` (scope `UE::UAF`)
- L64 _namespace_ `namespace UE`
- L64 _namespace_ `namespace UAF` (scope `UE`)
- L64 _namespace_ `namespace Graph` (scope `UE::UAF`)
- L66 _externvar_ `extern const FName EntryPointName;` (scope `UE::UAF::Graph`)
- L67 _externvar_ `extern const FName ResultName;` (scope `UE::UAF::Graph`)
- L70 _namespace_ `namespace UE`
- L70 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/AnimNextGraphEntryPoint.h` (Public)


#### struct `FAnimNextGraphEntryPoint`  
`struct FAnimNextGraphEntryPoint`  
_L11-22_
- reflection: `USTRUCT()`
- L17 _public member_ `FName EntryPointName;` — `UPROPERTY()` — The name of the entry point
- L21 _public member_ `FAnimNextEntryPointHandle RootTraitHandle;` — `UPROPERTY()` — This is a handle to the root trait for a graph

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/AnimNextGraphEvaluatorExecuteDefinition.h` (Public)


#### struct `FAnimNextGraphEvaluatorExecuteArgument`  
`struct FAnimNextGraphEvaluatorExecuteArgument`  
_L9-18_
- reflection: `USTRUCT()`
- desc: Represents an argument to a FRigUnit_AnimNextGraphEvaluator entry point
- L14 _public member_ `FString Name;` — `UPROPERTY()`
- L17 _public member_ `FString CPPType;` — `UPROPERTY()`

#### struct `FAnimNextGraphEvaluatorExecuteDefinition`  
`struct FAnimNextGraphEvaluatorExecuteDefinition`  
_L22-34_
- reflection: `USTRUCT()`
- desc: Represents an entry point of FRigUnit_AnimNextGraphEvaluator
- L27 _public member_ `uint32 Hash = 0;` — `UPROPERTY()`
- L30 _public member_ `FString MethodName;` — `UPROPERTY()`
- L33 _public member_ `TArray<FAnimNextGraphEvaluatorExecuteArgument> Arguments;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/AnimNextGraphInstance.h` (Public)


#### struct `FAnimNextGraphInstance`  
`struct FAnimNextGraphInstance : public FUAFAssetInstance #if CPP , public TSharedFromThis<FAnimNextGraphInstance> #endif`  
_L60-220_
- reflection: `USTRUCT()`
- inherits: `FUAFAssetInstance,TSharedFromThis<FAnimNextGraphInstance>`
- desc: Represents an instance of an AnimNext graph This struct uses UE reflection because we wish for the GC to keep the graph alive while we own a reference to it. It is not intended to be serialized on disk with a live instance.
- L68 _public prototype_ `FAnimNextGraphInstance();` — Creates an empty graph instance that doesn't reference anything
- L71 _public prototype_ `FAnimNextGraphInstance(const FAnimNextGraphInstance&) = delete;` — No copying, no moving
- L72 _public prototype_ `FAnimNextGraphInstance& operator=(const FAnimNextGraphInstance&) = delete;`
- L75 _public prototype_ `~FAnimNextGraphInstance();` — If the graph instance is allocated, we release it during destruction
- L78 _public prototype_ `void Release();` — Releases the graph instance and frees all corresponding memory
- L81 _public prototype_ `bool IsValid() const;` — Returns true if we have a live graph instance, false otherwise
- L84 _public prototype_ `const UUAFAnimGraph* GetAnimationGraph() const;` — Returns the animation graph used by this instance or nullptr if the instance is invalid
- L87 _public prototype_ `FName GetEntryPoint() const;` — Returns the entry point in Graph that this instance corresponds to
- L90 _public prototype_ `UE::UAF::FWeakTraitPtr GetGraphRootPtr() const;` — Returns a weak handle to the root trait instance
- L93 _public prototype_ `FAnimNextModuleInstance* GetModuleInstance() const;` — Returns the module instance that owns us or nullptr if we are invalid
- L96 _public prototype_ `FUAFWeakSystemReference GetModuleInstanceReference() const;` — Returns the system instance that owns us as a weak reference. Can be invalid if we are not owned by a system.
- L99 _public prototype_ `FAnimNextGraphInstance* GetParentGraphInstance() const;` — Returns the parent graph instance that owns us or nullptr for the root graph instance or if we are invalid
- L102 _public prototype_ `FAnimNextGraphInstance* GetRootGraphInstance() const;` — Returns the root graph instance that owns us and the components or nullptr if we are invalid
- L105 _public prototype_ `bool UsesAnimationGraph(const UUAFAnimGraph* InAnimationGraph) const;` — Check to see if this instance data matches the provided animation graph
- L108 _public prototype_ `bool UsesEntryPoint(FName InEntryPoint) const;` — Check to see if this instance data matches the provided graph entry point
- L111 _public prototype_ `bool IsRoot() const;` — Returns whether or not this graph instance is the root graph instance or false otherwise
- L114 _public prototype_ `bool HasUpdated() const;` — Returns whether or not this graph instance has updated at least once
- L117 _public prototype_ `void MarkAsUpdated();` — Called each time the graph updates to mark the instance as updated
- L122 _private prototype_ `void ExecuteLatentPins(const TConstArrayView<UE::UAF::FLatentPropertyHandle>& LatentHandles, void* DestinationBasePtr, float DeltaTime, bool bIsFrozen, bool bJustBecameRelevant);` — Executes a list of latent RigVM pins and writes the result into the destination pointer (latent handle offsets are using the destination as base) When frozen, latent handles that can freeze are skipped, all others will execute
- L126 _private prototype_ `void CopyVariablesToLatentPins(const TConstArrayView<UE::UAF::FLatentPropertyHandle>& LatentHandles, void* DestinationBasePtr, bool bIsFrozen, bool bJustBecameRelevant);` — When a group of latent pins do not require RigVM to operate, this copies the values directly from variables rather than calling ExecuteLatentPins. When frozen, latent handles that can freeze are skipped, all others will execute
- L129 _private prototype_ `void AllocateVariablesInternal(const TSharedPtr<const UE::UAF::FVariableOverridesCollection>& InOverrides, TWeakPtr<FAnimNextGraphInstance> InParentGraphInstance);` — Performs allocation of internal variable data structures
- L132 _private prototype_ `void AllocateGraphInternal();` — Performs allocation of graph root ptr
- L137 _private prototype_ `void Freeze();` — During graph compilation, if we have existing graph instances, we freeze them by releasing their memory before thawing them Freezing is a partial release of resources that retains the necessary information to re-create things safely
- L140 _private prototype_ `void Thaw();` — During graph compilation, once compilation is done we thaw existing graph instances to reallocate their memory
- L145 _private prototype_ `void RegisterWithGC(const UE::UAF::FWeakTraitPtr& InTraitPtr);` — Registers the provided trait with the GC system Once registered, IGarbageCollection::AddReferencedObjects will be called on it during GC
- L148 _private prototype_ `void UnregisterWithGC(const UE::UAF::FWeakTraitPtr& InTraitPtr);` — Unregisters the provided trait from the GC system
- L151 _private prototype_ `void RunOrQueueTask(UE::UAF::FUniqueAnimGraphTask&& InTaskFunction);` — Runs a task or queues it until AllocateVariablesInternal
- L170 _private member_ `} GCHandler;`
- L173 _private member_ `FName EntryPoint;` — The entry point in Graph that this instance corresponds to
- L176 _private member_ `UE::UAF::FTraitPtr GraphInstancePtr;` — Hard reference to the graph instance data, we own it
- L179 _private member_ `TWeakPtr<FAnimNextModuleInstance> ModuleInstance;` — The module instance that owns the root, us and the components
- L182 _private member_ `FAnimNextGraphInstance* RootGraphInstance = nullptr;` — The root graph instance that owns us and the components
- L197 _private member_ `Allocated, } AllocationState = EAllocationState::Empty;` — Has all internal structures allocated
- L200 _private member_ `bool bHasUpdatedOnce : 1 = false;` — Whether or not this graph has updated once

#### struct `FAnimNextGraphInstance::FGCHandler`  
`struct FGCHandler : public FGCObject`  
_L155-170_
- inherits: `FGCObject`
- desc: GC handler. This is nested to avoid having to bubble the polymorphism it introduces up to super-structs
- L157 _public function_ `explicit FGCHandler(FAnimNextGraphInstance& InOwner) : Owner(InOwner)`
- L162 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject implementation
- L163 _public prototype_ `virtual FString GetReferencerName() const override;`
- L166 _public member_ `FAnimNextGraphInstance& Owner;` — Owner instance
- L169 _public member_ `TArray<UE::UAF::FWeakTraitPtr> TraitsWithReferences;` — List of trait handles that contain UObject references and implement IGarbageCollection

#### enum `FAnimNextGraphInstance::EAllocationState`  
`enum EAllocationState`  
_L184-197_
- L187 _public enumerator_ `Empty` — Default-initialized graph instance
- L190 _public enumerator_ `PreAllocated` — Has a reference to its graph, but has no internal other structures allocated
- L193 _public enumerator_ `VariablesAllocated` — Has internal variables & components allocated
- L196 _public enumerator_ `Allocated` — Has all internal structures allocated

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextGraphInstance> : public TStructOpsTypeTraitsBase2<FAnimNextGraphInstance>`  
_L223-229_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextGraphInstance>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L226-228_

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace UAF` (scope `UE`)
- L227 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anona878e3630103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/PostProcessAnimationAssetUserData.h` (Public)


#### class `UPostProcessAnimationUserAssetData`  
`class UPostProcessAnimationUserAssetData : public UAssetUserData`  
_L12-19_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Post-process Animation User Data"))`
- inherits: `UAssetUserData`
- desc: Asset user data used to store post-process animation data for a skeletal mesh asset.
- L18 _public member_ `TObjectPtr<UObject> AnimationAsset;` — `UPROPERTY(EditAnywhere, Category = Animation)`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/UAFAnimGraphTrace.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L15 _prototype_ `void TraceGraphInstances(const FAnimNextGraphInstance& RootGraph);` (scope `UE::UAF`)
- L16 _prototype_ `void TraceEvaluationProgram(const FEvaluationProgram& Program, const FAnimNextGraphInstance& RootGraph);` (scope `UE::UAF`)
- L17 _prototype_ `void TraceEvaluationProgram(const FEvaluationProgram& Program, const FUAFAssetInstance& AssetInstance, const UObject* OuterObject);` (scope `UE::UAF`)
- L20 _macro_ `#define TRACE_UAF_GRAPHINSTANCES(RootGraph) UE::UAF::TraceGraphInstances(RootGraph);`
- L21 _macro_ `#define TRACE_UAF_EVALUATIONPROGRAM(Program, RootGraph) UE::UAF::TraceEvaluationProgram(Program, RootGraph);`
- L22 _macro_ `#define TRACE_UAF_EVALUATIONPROGRAM_WITHOWNER(Program, AssetInstance, Object) UE::UAF::TraceEvaluationProgram(Program, AssetInstance, Object);`
- L26 _macro_ `#define TRACE_UAF_GRAPHINSTANCES(RootGraph)`
- L27 _macro_ `#define TRACE_UAF_EVALUATIONPROGRAM(Program, RootGraph)`
- L28 _macro_ `#define TRACE_UAF_EVALUATIONPROGRAM_WITHOWNER(Program, AssetInstance, Object)`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/UAFGraphInstanceComponent.h` (Public)


#### struct `FUAFGraphInstanceComponent`  
`struct FUAFGraphInstanceComponent : public FUAFAssetInstanceComponent`  
_L26-54_
- reflection: `USTRUCT(meta=(Hidden, Abstract))`
- inherits: `FUAFAssetInstanceComponent`
- desc: FGraphInstanceComponent A graph instance component is attached and owned by a graph instance. It persists as long as it is needed.
- L31 _public typedef_ `using ContainerType = FAnimNextGraphInstance;`
- L33 _public prototype_ `FUAFGraphInstanceComponent() = default;`
- L35 _public prototype_ `virtual ~FUAFGraphInstanceComponent() override = default;`
- L38 _public prototype_ `FAnimNextGraphInstance& GetGraphInstance();` — Returns the owning graph instance this component lives on
- L41 _public prototype_ `const FAnimNextGraphInstance& GetGraphInstance() const;` — Returns the owning graph instance this component lives on
- L46 _public function_ `virtual void PreUpdate(UE::UAF::FExecutionContext& Context)` — Called before the update traversal begins, before any node has been visited Note that PreUpdate won't be called if a component is created during the update traversal until the next update The execution context provided is bound to the graph root and can be bound to anything the component wishes
- L50 _public function_ `virtual void PostUpdate(UE::UAF::FExecutionContext& Context)` — Called after the update traversal completes, after every node has been visited The execution context provided is bound to the graph root and can be bound to anything the component wishes
- L53 _public function_ `virtual void OnTraitEvent(UE::UAF::FExecutionContext& Context, FAnimNextTraitEvent& Event)` — Called before PreUpdate with input events and before PostUpdate with output events

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Graph/WeakAnimGraphReference.h` (Public)


#### struct `UE::UAF::FWeakAnimGraphReference`  
`struct FWeakAnimGraphReference`  
_L30-79_
- desc: A non-owning reference to a UAF graph.
- L33 _public prototype_ `FWeakAnimGraphReference() = default;` — Default-constructable only because it needs to be embedded in UObjects/UStructs
- L37 _public prototype_ `explicit FWeakAnimGraphReference(const FAnimGraphReference& InAnimGraphReference);` — Construct a non-owning reference to a graph instance. Can be called on any thread
- L41 _public prototype_ `explicit FWeakAnimGraphReference(const TSharedPtr<FAnimNextGraphInstance>& InAnimGraphInstance);` — Construct a non-owning reference to a graph instance. Can be called on any thread
- L45 _public prototype_ `void Reset();` — Reset this handle to invalid - gives up ownership Can be called on any thread
- L49 _public prototype_ `bool IsValid() const;` — Check if this handle is valid Can be called on any thread.
- L53 _public prototype_ `[[nodiscard]] const UUAFAnimGraph* GetAnimGraph() const;` — Get the anim graph that this handle references Can be called on any thread.
- L58 _public prototype_ `void QueueTask(FUniqueAnimGraphTask&& InTaskFunction) const;` — Queue task to execute on the instance Can be called on any thread. @param	InTaskFunction		The function to run
- L61 _public prototype_ `void SetDebugName(FName InName) const;` — Sets the debug name for the instance, used for tracing etc.
- L64 _public prototype_ `void AddReferencedObjects(FReferenceCollector& InCollector) const;` — GC support
- L74 _private prototype_ `[[nodiscard]] TSharedPtr<FAnimNextGraphInstance> GetOrAllocate(const FExecutionContext& InContext, const FTraitBinding& InBinding) const;` — Gets or allocate & binds the graph instance Fully allocates the graph if it is only preallocated Can be called on any thread. @param    InBinding    The current binding (this must be called during a graph execution)
- L78 _private member_ `TWeakPtr<FAnimNextGraphInstance> Ptr;` — Pointer to the instance

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Injection/IEvaluationModifier.h` (Public)


#### struct `UE::UAF::IEvaluationModifier`  
`struct IEvaluationModifier`  
_L13-22_
- desc: Override point allowing injection sites to take over evaluation and inject their own tasks
- L15 _public prototype_ `virtual ~IEvaluationModifier() = default;`
- L18 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context) const = 0;` — Called before an injection site trait's children are evaluated
- L21 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context) const = 0;` — Called after an injection site trait's children are evaluated

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Injection/InjectionLibrary.h` (Public)


#### class `UUAFInjectionLibrary`  
`class UUAFInjectionLibrary : public UBlueprintFunctionLibrary`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static bool IsSlotActive(const UUAFComponent* UAFComponent, FName SlotNodeName);` — `UFUNCTION(BlueprintPure, Category = "UAF|Injection", meta=(ScriptMethod))` — Return true if the running UAF System has an active montage in the given slot. A UAnimMontage that is playing in the slot and blending out is not determined to be "active".

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Injection/InjectionRequest.h` (Public)


#### enum `EAnimNextInjectionBlendMode`  
`enum class EAnimNextInjectionBlendMode : uint8`  
_L42-49_
- reflection: `UENUM()`
- L45 _public enumerator_ `Standard` — Uses standard weight based blend
- L48 _public enumerator_ `Inertialization` — Uses inertialization. Requires an inertialization trait somewhere earlier in the graph.

#### struct `FAnimNextInjectionBlendSettings`  
`struct FAnimNextInjectionBlendSettings`  
_L57-72_
- reflection: `USTRUCT(BlueprintType)`
- desc: Injection Blend Settings Encapsulates the blend settings used by injection requests.
- L67 _public member_ `FAlphaBlendArgs Blend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend", meta = (DisplayAfter = "BlendMode"))` — AlphaBlend options (time, curve, etc.)
- L71 _public member_ `EAnimNextInjectionBlendMode BlendMode = EAnimNextInjectionBlendMode::Standard;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend")` — Type of blend mode (Standard vs Inertial)

#### enum `EAnimNextInjectionType`  
`enum class EAnimNextInjectionType : uint8`  
_L76-83_
- reflection: `UENUM()`
- desc: What to do when performing an injection
- L79 _public enumerator_ `InjectObject` — Inject an object to be instantiated via factory at the injection site. Optionally this can bind to an external module.
- L82 _public enumerator_ `EvaluationModifier` — Apply an evaluation modifier at the specified injection site. Does not affect the currently-provided object.

#### enum `EAnimNextInjectionLifetimeType`  
`enum class EAnimNextInjectionLifetimeType : uint8`  
_L87-97_
- reflection: `UENUM()`
- desc: Lifetime behavior for injection requests
- L91 _public enumerator_ `Auto` — Automatically un-inject this request when the timeline of the injection request expires. Looping/infinite timelines will never auto-expire and must be uninjected manually.
- L96 _public enumerator_ `ForcePersistent` — Injection request persists and must be un-injected manually. Blending out to the source animation at the injection site does not occur. Useful when you want to just push a chain of animations to an injection site, never seeing the source/passthrough pose.

#### struct `FAnimNextInjectionRequestArgs`  
`struct FAnimNextInjectionRequestArgs`  
_L105-151_
- reflection: `USTRUCT()`
- desc: Injection Request Arguments Encapsulates the parameters required to initiate an injection request.
- L120 _private member_ `FAnimNextInjectionSite Site;` — `UPROPERTY()` — The injection site to target with this request.
- L124 _private member_ `FAnimNextInjectionBlendSettings BlendInSettings;` — `UPROPERTY()` — The blend settings to use when blending in
- L128 _private member_ `FAnimNextInjectionBlendSettings BlendOutSettings;` — `UPROPERTY()` — The blend settings to use when blending out (if not interrupted)
- L132 _private member_ `TObjectPtr<UObject> Object;` — `UPROPERTY()` — Object to inject. The animation graph to be instantiated for this request will be chosen via a factory
- L135 _private member_ `TSharedPtr<UE::UAF::IEvaluationModifier> EvaluationModifier;` — Evaluation modifier to apply at the injection site. Shared ownership, references can persist in worker threads until un-injected.
- L138 _private member_ `EAnimNextInjectionType Type = EAnimNextInjectionType::InjectObject;` — `UPROPERTY()`
- L142 _private member_ `EAnimNextInjectionLifetimeType LifetimeType = EAnimNextInjectionLifetimeType::Auto;` — `UPROPERTY()` — Lifetime behavior for the request
- L146 _private member_ `bool bTrackTimelineProgress = false;` — `UPROPERTY()` — Whether or not the request should track the timeline progress
- L150 _private member_ `FAnimNextFactoryParams FactoryParams;` — `UPROPERTY()` — Set of assets & structs that describe the required variables for factory-generating injected graphs

#### struct `UE::UAF::FInjectionLifetimeEvents`  
`struct FInjectionLifetimeEvents`  
_L168-181_
- desc: Delegates called for various lifetime events
- L171 _public member_ `FAnimNextOnInjectionStarted OnStarted;` — Callback called when the request starts playing (status transitions from pending to playing)
- L174 _public member_ `FAnimNextOnInjectionCompleted OnCompleted;` — Callback called when the request completes (status transitions from playing to completed)
- L177 _public member_ `FAnimNextOnInjectionInterrupted OnInterrupted;` — Callback called when the request is interrupted (either by calling Stop on it or by another request)
- L180 _public member_ `FAnimNextOnInjectionBlendingOut OnBlendingOut;` — Callback called when the request starts blending out (if it wasn't interrupted)

#### struct `UE::UAF::FInjectionRequest`  
`struct FInjectionRequest : public TSharedFromThis<FInjectionRequest, ESPMode::ThreadSafe>`  
_L193-319_
- inherits: `TSharedFromThis<FInjectionRequest,ESPMode::ThreadSafe>`
- desc: Injection Request Instances of this class represent individual requests to the injection system. They are allocated as shared pointers and ownership is split between gameplay (until it no longer cares about a particular request) and the injection site that hosts it (until the request completes). Use MakeInjectionRequest(...) to construct instances of this type.
- L196 _public prototype_ `const FInjectionRequestArgs& GetArgs() const;` — Returns the arguments this request is using
- L199 _public prototype_ `const FInjectionLifetimeEvents& GetLifetimeEvents() const;` — Returns the lifetime delegates this request is using
- L202 _public prototype_ `EInjectionStatus GetStatus() const;` — Returns the request status
- L205 _public prototype_ `const FTimelineState& GetTimelineState() const;` — Returns the current timeline state (make sure to enable FInjectionRequestArgs::bTrackTimelineProgress to use this)
- L208 _public prototype_ `bool HasExpired() const;` — Returns whether or not this request has expired
- L211 _public prototype_ `bool HasCompleted() const;` — Returns whether or not this request has completed (might have been interrupted)
- L214 _public prototype_ `bool IsPlaying() const;` — Returns whether or not this request is playing (might be blending out or interrupted)
- L217 _public prototype_ `bool IsBlendingOut() const;` — Returns whether or not this request is blending out
- L220 _public prototype_ `bool WasInterrupted() const;` — Returns whether or not this request was interrupted (by Stop or by another request)
- L222 _public prototype_ `void ExternalAddReferencedObjects(FReferenceCollector& Collector);`
- L228 _public function_ `template<typename ValueType> void SetVariable(const FAnimNextVariableReference& InVariable, const ValueType& InValue)` — Set a variable on the running injected instance. @param    InVariable         The variable to set @param    InValue            The value to set the variable to
- L240 _public function_ `template<typename ValueType> void AccessVariable(const FAnimNextVariableReference& InVariable, TUniqueFunction<void(ValueType&)> InFunction)` — Access a variable on the running injected instance for modification. Can avoid excess copies for larger structures/arrays. @param    InVariable         The variable to set @param    InFunction         The function used to modify the variable. Note: called back at some later time on a worker thread
- L251 _public function_ `template<typename StructType> void AccessVariablesStruct(TUniqueFunction<void(StructType&)> InFunction) const` — Access the memory of the shared variable struct directly on the running injected instance. @param	InFunction			Function called with a reference to the variable's struct. Note: called back at some later time on a worker thread
- L260 _public prototype_ `void QueueTask(FUniqueInstanceTask&& InTask);` — Queues a task to run on the injected instance prior to execution. Use this to set variables etc.
- L264 _private prototype_ `bool Inject(FInjectionRequestArgs&& InRequestArgs, FInjectionLifetimeEvents&& InLifetimeEvents, UObject* InHost, FUAFWeakSystemReference InReference);` — Sends this request to the specified host and it will attempt to play with the requested arguments
- L267 _private prototype_ `void Uninject();` — Interrupts this request and request that we transition to the source input on the playing injection site
- L270 _private prototype_ `FInjectionRequestArgs& GetMutableArgs();` — Returns the arguments this request is using
- L273 _private prototype_ `FInjectionLifetimeEvents& GetMutableLifetimeEvents();` — Returns the lifetime delegates this request is using
- L275 _private prototype_ `void OnStatusUpdate(EInjectionStatus NewStatus);`
- L277 _private prototype_ `void OnTimelineUpdate(const FTimelineState& NewTimelineState);`
- L280 _private prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — GC API
- L283 _private prototype_ `static bool ValidateArgs(const FInjectionRequestArgs& InRequestArgs);` — Validate this set of args is set up correctly for injection
- L286 _private prototype_ `void FlushTasks(const FInstanceTaskContext& InContext);` — Flush any pending tasks, with the initialize task on the request args getting run once first
- L289 _private member_ `FInjectionRequestArgs RequestArgs;` — The request arguments
- L292 _private member_ `FInjectionLifetimeEvents LifetimeEvents;` — Callbacks for lifetime events
- L295 _private member_ `TWeakObjectPtr<UObject> WeakHost;` — The object we are playing on
- L298 _private member_ `FUAFWeakSystemReference Reference;` — Reference to the system instance
- L301 _private member_ `TWeakPtr<FAnimNextTraitEvent> InjectionEvent;` — The injection event if we have injected already
- L304 _private member_ `TSpscQueue<FUniqueInstanceTask> TaskQueue;` — Queue of tasks to be executed next time this injection updates
- L307 _private member_ `EInjectionStatus Status = EInjectionStatus::None;` — The current request status
- L310 _private member_ `FTimelineState TimelineState;` — The current timeline state

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UAF` (scope `UE`)
- L153 _namespace_ `namespace UE`
- L153 _namespace_ `namespace UAF` (scope `UE`)
- L156 _typedef_ `using EInjectionBlendMode = EAnimNextInjectionBlendMode;` (scope `UE::UAF`) — Create a namespaced aliases to simplify usage
- L157 _typedef_ `using FInjectionBlendSettings = FAnimNextInjectionBlendSettings;` (scope `UE::UAF`)
- L158 _typedef_ `using FInjectionRequestArgs = FAnimNextInjectionRequestArgs;` (scope `UE::UAF`)
- L162 _delegate_ `DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionStarted, const FInjectionRequest&) DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionCompleted, const FInjectionRequest&) DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionInterrupted, const FInjectionRequest&) DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionBlendingOut, const FInjectionRequest&)`
- L163 _delegate_ `DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionCompleted, const FInjectionRequest&) DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionInterrupted, const FInjectionRequest&) DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionBlendingOut, const FInjectionRequest&)`
- L164 _delegate_ `DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionInterrupted, const FInjectionRequest&) DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionBlendingOut, const FInjectionRequest&)`
- L165 _delegate_ `DECLARE_DELEGATE_OneParam(FAnimNextOnInjectionBlendingOut, const FInjectionRequest&)`
- L231 _function_ `` (scope `UE::UAF::FInjectionRequest::SetVariable`)
- L243 _function_ `` (scope `UE::UAF::FInjectionRequest::AccessVariable`)
- L254 _function_ `` (scope `UE::UAF::FInjectionRequest::AccessVariablesStruct`)
- L322 _typedef_ `using FInjectionRequestPtr = TSharedPtr<FInjectionRequest, ESPMode::ThreadSafe>;` (scope `UE::UAF`) — Create a shared pointer alias for injection requests
- L325 _function_ `inline FInjectionRequestPtr MakeInjectionRequest()` (scope `UE::UAF`) — Constructs a injection request object

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Injection/InjectionSite.h` (Public)


#### struct `FAnimNextInjectionSite`  
`struct FAnimNextInjectionSite`  
_L15-48_
- reflection: `USTRUCT()`
- desc: Specifies the desired injection site for an injection request. Optionally allows for fallback to the Default Injection Site specified by the module if DesiredSiteName is none, or does not exist in the graph
- L19 _public function_ `FAnimNextInjectionSite() : bUseModuleFallback(true)`
- L24 _public function_ `explicit FAnimNextInjectionSite(const FAnimNextVariableReference& InDesiredSite) : DesiredSite(InDesiredSite) , bUseModuleFallback(!InDesiredSite.IsNone())`
- L33 _public member_ `FName DesiredSiteName_DEPRECATED;` — `UPROPERTY()` — The name of the site to inject into
- L37 _public member_ `FAnimNextVariableReference DesiredSite;` — `UPROPERTY()`
- L42 _public member_ `uint8 bUseModuleFallback : 1;` — `UPROPERTY()` — Flag specifying whether the request can (or should) fallback to the Default Injection Site specified in the module if DesiredSiteName was not found
- L45 _public prototype_ `bool Serialize(FArchive& Ar);`
- L46 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextInjectionSite> : public TStructOpsTypeTraitsBase2<FAnimNextInjectionSite>`  
_L51-60_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextInjectionSite>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L55-58_

#### Free symbols / members of external scopes

- L56 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon73be36210103`)
- L57 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon73be36210103`)
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace UAF` (scope `UE`)
- L64 _typedef_ `using FInjectionSite = FAnimNextInjectionSite;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Injection/InjectionStatus.h` (Public)


#### enum `EAnimNextInjectionStatus`  
`enum class EAnimNextInjectionStatus : uint8`  
_L13-43_
- reflection: `UENUM()`
- desc: Injection Request Status
- L20 _public enumerator_ `None = 0x00` — No current status
- L23 _public enumerator_ `Pending = 0x01` — Animation request has been queue but hasn't been processed yet
- L26 _public enumerator_ `Playing = 0x02` — Animation is playing (may be blending in or out, may be interrupted)
- L29 _public enumerator_ `Completed = 0x04` — Animation has finished playing (may have the interrupted flag to signal that it didn't stop on its own)
- L32 _public enumerator_ `Expired = 0x10` — Animation request expired without playing
- L39 _public enumerator_ `Interrupted = 0x40` — Animation was interrupted by another animation request (or a stop request)
- L42 _public enumerator_ `BlendingOut = 0x80` — Animation is blending out

#### Free symbols / members of external scopes

- L45 _prototype_ `ENUM_CLASS_FLAGS(EAnimNextInjectionStatus);`
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace UAF` (scope `UE`)
- L50 _typedef_ `using EInjectionStatus = EAnimNextInjectionStatus;` (scope `UE::UAF`) — Create a namespaced alias to simplify usage

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Injection/InjectionUtils.h` (Public)


#### struct `UE::UAF::FPlayAnimArgs`  
`struct FPlayAnimArgs`  
_L22-29_
- desc: Optional arguments to PlayAnim
- L24 _public member_ `FAnimNextFactoryParams FactoryParams;`
- L25 _public member_ `float PlayRate = 1.0f;`
- L26 _public member_ `float StartPosition = 0.0f;`
- L27 _public member_ `EAnimAssetLoopMode LoopMode = EAnimAssetLoopMode::Auto;`
- L28 _public member_ `EAnimNextInjectionLifetimeType LifetimeType = EAnimNextInjectionLifetimeType::Auto;`

#### struct `UE::UAF::FInjectionUtils`  
`struct FInjectionUtils`  
_L32-138_
- desc: A collection of wrapper functions for common injection operations
- L45 _public prototype_ `static FInjectionRequestPtr PlayAnim( UUAFComponent* InComponent, const FInjectionSite& InSite, UAnimSequence* InAnimSequence, FPlayAnimArgs&& InArgs = FPlayAnimArgs(), const FInjectionBlendSettings& InBlendInSettings = FInjectionBlendSettings(), const FInjectionBlendSettings& InBlendOutSettings = FInjectionBlendSettings(), FInjectionLifetimeEvents&& InLifetimeEvents = FInjectionLifetimeEvents());` — Injects an animation sequence into a running AnimNext module @param InComponent          The UAnimNextComponent that hosts the module being played on @param InHost               The object that hosts the module (e.g. UAnimNextComponent) being played on @param InSystemReference    The system reference being injected into @param InSite               The injection site to 'play' the animation sequence on @param InAnimSequence       The animation sequence to play @param InArgs               Optional args to use @param InBlendInSettings    The blend in settings @param InBlendOutSettings   The blend in settings @param InLifetimeEvents     Delegates called for various request lifetime events @return the new injection request for tracking, or an invalid request if injection failed. This can be discarded for fire-and-forget style behavior.
- L55 _public prototype_ `static FInjectionRequestPtr PlayAnimHandle( UObject* InHost, FUAFWeakSystemReference InSystemReference, const FInjectionSite& InSite, UAnimSequence* InAnimSequence, FPlayAnimArgs&& InArgs = FPlayAnimArgs(), const FInjectionBlendSettings& InBlendInSettings = FInjectionBlendSettings(), const FInjectionBlendSettings& InBlendOutSettings = FInjectionBlendSettings(), FInjectionLifetimeEvents&& InLifetimeEvents = FInjectionLifetimeEvents());` — @see PlayAnim
- L76 _public prototype_ `static FInjectionRequestPtr InjectAsset( UUAFComponent* InComponent, const FInjectionSite& InSite, UObject* InAsset, FAnimNextFactoryParams&& InFactoryParams = FAnimNextFactoryParams(), const FInjectionBlendSettings& InBlendInSettings = FInjectionBlendSettings(), const FInjectionBlendSettings& InBlendOutSettings = FInjectionBlendSettings(), FInjectionLifetimeEvents&& InLifetimeEvents = FInjectionLifetimeEvents());` — Injects an asset into a running AnimNext module @param InComponent          The UAnimNextComponent that hosts the module being played on @param InHost               The object that hosts the module (e.g. UAnimNextComponent) being played on @param InSystemReference    The system reference being injected into @param InSite               The injection site to 'play' the asset on @param InAsset              The asset to 'play' @param InFactoryParams      The params used to manufacture a graph to run the injected object @param InBlendInSettings    The blend in settings @param InBlendOutSettings   The blend in settings @param InLifetimeEvents     Delegates called for various request lifetime events @return the new injection request for tracking, or an invalid request if injection failed. This can be discarded for fire-and-forget style behavior.
- L86 _public prototype_ `static FInjectionRequestPtr InjectAsset( UObject* InHost, FUAFWeakSystemReference InSystemReference, const FInjectionSite& InSite, UObject* InAsset, FAnimNextFactoryParams&& InFactoryParams = FAnimNextFactoryParams(), const FInjectionBlendSettings& InBlendInSettings = FInjectionBlendSettings(), const FInjectionBlendSettings& InBlendOutSettings = FInjectionBlendSettings(), FInjectionLifetimeEvents&& InLifetimeEvents = FInjectionLifetimeEvents());` — @see InjectAsset
- L104 _public prototype_ `static FInjectionRequestPtr InjectEvaluationModifier( UUAFComponent* InComponent, const TSharedRef<IEvaluationModifier>& InEvaluationModifier, const FInjectionSite& InSite = FInjectionSite());` — Inject an evaluation modifier into a running AnimNext module to control animation evaluation at a low level. Does not require that injection sites are publicly visible. @param InComponent          The UAnimNextComponent that hosts the module being injected into @param InHost               The object that hosts the module (e.g. UAnimNextComponent) being injected into @param InSystemReference    The system reference being injected into @param InEvaluationModifier The evaluation modifier to inject @param InSite               The injection site to use. If this is NAME_None, then the first site will be used. @return the new injection request for tracking, or an invalid request if injection failed. This can be discarded for fire-and-forget style behavior.
- L110 _public prototype_ `static FInjectionRequestPtr InjectEvaluationModifier( UObject* InHost, FUAFWeakSystemReference InSystemReference, const TSharedRef<IEvaluationModifier>& InEvaluationModifier, const FInjectionSite& InSite = FInjectionSite());` — @see InjectEvaluationModifier
- L123 _public prototype_ `static FInjectionRequestPtr Inject( UUAFComponent* InComponent, FInjectionRequestArgs&& InArgs, FInjectionLifetimeEvents&& InLifetimeEvents = FInjectionLifetimeEvents());` — Inject into a running AnimNext module (raw custom args) @param InComponent          The UAnimNextComponent that hosts the module being injected into @param InHost               The object that hosts the module (e.g. UAnimNextComponent) being injected into @param InSystemReference    The system reference being injected into @param InArgs               Arguments to the injection request @param InLifetimeEvents     Delegates called for various request lifetime events @return the new injection request for tracking, or an invalid request if injection failed. This can be discarded for fire-and-forget style behavior.
- L129 _public prototype_ `static FInjectionRequestPtr Inject( UObject* InHost, FUAFWeakSystemReference InSystemReference, FInjectionRequestArgs&& InArgs, FInjectionLifetimeEvents&& InLifetimeEvents = FInjectionLifetimeEvents());` — @see Inject
- L137 _public prototype_ `static void Uninject(FInjectionRequestPtr InInjectionRequest);` — Uninject a previously injected request @param InInjectionRequest   The injection request to uninject

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Native/UAFSimplePrePhysicsGraphComponent.h` (Public)


#### struct `FUAFSimplePrePhysicsGraphComponent`  
`struct FUAFSimplePrePhysicsGraphComponent : public FUAFScriptComponent`  
_L19-44_
- reflection: `USTRUCT()`
- inherits: `FUAFScriptComponent`
- desc: Script component that can run a prephysics event to run a graph
- L22 _public prototype_ `DECLARE_UAF_ASSET_INSTANCE_COMPONENT() private: static void PrePhysics(TStructView<FUAFScriptComponent> InScriptComponent, TConstStructView<FUAFScriptContextData> InContextData);`
- L28 _public prototype_ `virtual void CallEventByName(TConstStructView<FUAFScriptContextData> InContextData) override;` — FUAFScriptComponent interface
- L29 _public prototype_ `virtual TConstArrayView<UE::UAF::FScriptEventInfo> GetScriptEvents() override;`
- L32 _public prototype_ `virtual void OnBindToInstance() override;` — FUAFAssetInstanceComponent interface
- L36 _public member_ `FUAFValueBundle Output;` — `UPROPERTY(Transient)` — Output value
- L40 _public member_ `FUAFRunAssetWorkData WorkData;` — `UPROPERTY(Transient)` — Work data for the 'run asset node'
- L43 _public member_ `FAnimNextAnimGraph* Graph = nullptr;` — Reference to injected graph data in variables

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMGRAPH_API`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/EntryPointHandle.h` (Public)


#### struct `FAnimNextEntryPointHandle`  
`struct FAnimNextEntryPointHandle final`  
_L22-62_
- reflection: `USTRUCT(BlueprintType)`
- desc: Entry Point Handle An entry point handle is equivalent to a trait handle but it will not resolve automatically on load. As such, it is safe to use outside of an AnimNext graph. They must be manually resolved through FTraitReader. Internally, it contains a node handle (as a node ID) and a trait index. @see FAnimNextTraitHandle, FTraitReader
- L27 _public function_ `constexpr FAnimNextEntryPointHandle() noexcept : PackedTraitIndexAndNodeHandle(UE::UAF::FNodeHandle::INVALID_NODE_HANDLE_RAW_VALUE)` — Creates an invalid entry point handle
- L32 _public function_ `explicit FAnimNextEntryPointHandle(UE::UAF::FNodeHandle NodeHandle) : PackedTraitIndexAndNodeHandle(NodeHandle.GetPackedValue() & NODE_HANDLE_MASK)` — Creates an entry point handle pointing to the first trait of the specified node
- L39 _public function_ `FAnimNextEntryPointHandle(UE::UAF::FNodeHandle NodeHandle, uint32 TraitIndex) : PackedTraitIndexAndNodeHandle((NodeHandle.GetPackedValue() & NODE_HANDLE_MASK) | (TraitIndex << 24))` — Creates an entry point handle pointing to the specified trait on the specified node
- L47 _public function_ `constexpr bool IsValid() const noexcept` — Returns true if this entry point handle is valid, false otherwise
- L50 _public function_ `constexpr uint32 GetTraitIndex() const noexcept` — Returns the trait index
- L53 _public function_ `constexpr UE::UAF::FNodeHandle GetNodeHandle() const noexcept` — Returns a handle to the node referenced (its node ID)
- L57 _private member_ `static constexpr uint32 TRAIT_INDEX_SHIFT = 24;` — Bottom 24 bits are used by the node handle while the top 8 bits by the trait index
- L58 _private member_ `static constexpr uint32 NODE_HANDLE_MASK = ~0u >> (32 - TRAIT_INDEX_SHIFT);`
- L61 _private member_ `uint32 PackedTraitIndexAndNodeHandle;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/ExecutionContext.h` (Public)


#### struct `UE::UAF::FExecutionContext`  
`struct FExecutionContext`  
_L50-256_
- desc: Execution Context The execution context aims to centralize the trait query API. It is meant to be bound to a graph instance and re-used by the nodes/traits within.
- L53 _public prototype_ `FExecutionContext();` — Creates an unbound execution context
- L56 _public prototype_ `explicit FExecutionContext(FAnimNextGraphInstance& InGraphInstance);` — Creates an execution context and binds it to the specified graph instance
- L59 _public prototype_ `virtual ~FExecutionContext() = default;` — Derived types can control various features
- L62 _public prototype_ `const class UObject* GetHostObject() const;` — Owner object our module instance belongs to. Usually the Anim Next Component. This access is NOT thread-safe.
- L67 _public prototype_ `const FTransform GetHostTransform() const;` — The world transform of our host. Usually the actor containing our Anim Next Component @TODO: Not thread-safe and should be replaced ASAP by a subsystem so we can use this in scene graph/mass. Doesn't work for non-actors.
- L75 _public prototype_ `void BindTo(FAnimNextGraphInstance& InGraphInstance);` — Binds the execution context to the specified graph instance if it differs from the currently bound instance
- L78 _public prototype_ `void BindTo(const FWeakTraitPtr& TraitPtr);` — Binds the execution context to the graph instance that owns the specified trait if it differs from the currently bound instance
- L81 _public prototype_ `bool IsBound() const;` — Returns whether or not this execution context is bound to a graph instance
- L85 _public prototype_ `bool IsBoundTo(const FAnimNextGraphInstance& InGraphInstance) const;` — Returns whether or not this execution context is bound to the specified graph instance Returns true if the root graphs match
- L92 _public prototype_ `bool GetStack(const FWeakTraitPtr& TraitPtr, FTraitStackBinding& OutStackBinding) const;` — Returns a trait stack binding to the stack that contains the specified trait pointer. Returns false if we failed to do so.
- L104 _public prototype_ `template<class ScopedTraitInterface> void PushScopedInterface(const FTraitBinding& Binding);` — Pushed a scoped interface with the specified interface owned by the specified trait Scoped interfaces automatically pop when the owned trait finishes its update
- L110 _public prototype_ `template<class ScopedTraitInterface> void PushOptionalScopedInterface(bool bCondition, const FTraitBinding& Binding);` — Pushed an optional scoped interface with the specified interface owned by the specified trait The scoped interface is only pushed if the condition is true Scoped interfaces automatically pop when the owned trait finishes its update
- L117 _public prototype_ `template<class ScopedTraitInterface> bool PopScopedInterface(const FTraitBinding& Binding);` — Pops a scoped interface owned by the specified trait An interface can only be popped if it lives at the top of the stack Returns false if we failed to pop the specified interface Failure can occur if the scoped interface is missing or not present on top of the stack
- L122 _public prototype_ `bool PopStackScopedInterfaces(const FTraitBinding& Binding);` — Pops all scoped interfaces owned by the trait stack that contains the specified trait An interface can only be popped if it lives at the top of the stack Returns true if any scoped interfaces were popped, false otherwise
- L127 _public prototype_ `bool PopStackScopedInterfaces(const FTraitStackBinding& StackBinding);` — Pops all scoped interfaces owned by the specified trait stack An interface can only be popped if it lives at the top of the stack Returns true if any scoped interfaces were popped, false otherwise
- L132 _public prototype_ `template<class ScopedTraitInterface> bool GetScopedInterface(TTraitBinding<ScopedTraitInterface>& OutBinding) const;` — Queries the scoped interface stack starting at the top for a trait that implements the specified interface. If no such trait exists, false is returned.
- L138 _public prototype_ `template<class ScopedTraitInterface> void ForEachScopedInterface(TFunctionRef<bool(TTraitBinding<ScopedTraitInterface>& Binding)> InFunction) const;` — Queries the scoped interface stack starting at the top for a trait that implements the specified interface. When found, the provided callback will be called with the scoped interface binding. Iteration will continue as long as the callback returns true.
- L141 _public function_ `bool HasScopedInterfaces() const` — Returns whether or not any scoped interfaces have been pushed onto our stack
- L150 _public prototype_ `FTraitPtr AllocateNodeInstance(FAnimNextGraphInstance& GraphInstance, FAnimNextTraitHandle ChildTraitHandle) const;` — Allocates a new node instance from a trait handle using the specified graph instance If the desired trait lives in the current parent, a weak handle to it will be returned
- L154 _public prototype_ `FTraitPtr AllocateNodeInstance(const FTraitBinding& ParentBinding, FAnimNextTraitHandle ChildTraitHandle) const;` — Allocates a new node instance from a trait handle If the desired trait lives in the current parent, a weak handle to it will be returned
- L158 _public prototype_ `FTraitPtr AllocateNodeInstance(const FWeakTraitPtr& ParentBinding, FAnimNextTraitHandle ChildTraitHandle) const;` — Allocates a new node instance from a trait handle If the desired trait lives in the current parent, a weak handle to it will be returned
- L162 _public prototype_ `void ReleaseNodeInstance(FTraitPtr& NodePtr) const;` — Decrements the reference count of the provided node pointer and releases it if there are no more references remaining, reseting the pointer in the process
- L173 _public prototype_ `template<class ComponentType> ComponentType& GetOrAddComponent() const;` — Returns a typed graph instance component, creating it lazily the first time it is queried
- L177 _public prototype_ `template<class ComponentType> ComponentType* TryGetComponent() const;` — Returns a typed graph instance component pointer if found or nullptr otherwise
- L180 _public prototype_ `void ForEachComponent(TFunctionRef<bool(FUAFGraphInstanceComponent&)> InFunction) const;` — Iterates each of the graph instance components
- L190 _public prototype_ `virtual void RaiseInputTraitEvent(FAnimNextTraitEventPtr Event);` — Raises an input trait event Behavior is traversal dependent, see the derived type for your current traversal (e.g. IUpdate) Default behavior asserts
- L195 _public prototype_ `virtual void RaiseOutputTraitEvent(FAnimNextTraitEventPtr Event);` — Raises an output trait event Behavior is traversal dependent, see the derived type for your current traversal (e.g. IUpdate) Default behavior asserts
- L203 _public function_ `FAnimNextGraphInstance& GetRootGraphInstance() const` — Returns the bound root graph instance
- L206 _public prototype_ `TWeakObjectPtr<const USkeletalMeshComponent> GetBindingObject() const;` — Returns the skeletal mesh component associated to the graph execution, if any
- L209 _public function_ `FMemStack& GetMemStack() const` — Returns the local thread memstack
- L213 _public prototype_ `FRigVMDrawInterface* GetDebugDrawInterface() const;` — Get the debug draw interface
- L216 _public prototype_ `void Log(ELogVerbosity::Type Verbosity, const FString& Message, const FString& TraitName) const;`
- L220 _private prototype_ `FExecutionContext(const FExecutionContext&) = delete;` — No copy or move
- L221 _private prototype_ `FExecutionContext& operator=(const FExecutionContext&) = delete;`
- L223 _private prototype_ `void PushScopedInterfaceImpl(FTraitInterfaceUID InterfaceUID, const FTraitBinding& Binding);`
- L224 _private prototype_ `bool PopScopedInterfaceImpl(FTraitInterfaceUID InterfaceUID, const FTraitBinding& Binding);`
- L225 _private prototype_ `bool GetScopedInterfaceImpl(FTraitInterfaceUID InterfaceUID, FTraitBinding& OutBinding) const;`
- L226 _private prototype_ `void ForEachScopedInterfaceImpl(FTraitInterfaceUID InterfaceUID, TFunctionRef<bool(FTraitBinding& Binding)> InFunction) const;`
- L228 _private prototype_ `const FNodeDescription& GetNodeDescription(const FAnimNextGraphInstance& GraphInstance, FNodeHandle NodeHandle) const;`
- L229 _private prototype_ `const FNodeDescription& GetNodeDescription(const FNodeInstance& NodeInstance) const;`
- L230 _private prototype_ `const FNodeTemplate* GetNodeTemplate(const FNodeDescription& NodeDesc) const;`
- L231 _private prototype_ `const FTrait* GetTrait(const FTraitTemplate& TraitDesc) const;`
- L235 _protected member_ `FMemStack& MemStack;` — The memstack of the local thread
- L239 _private member_ `const FNodeTemplateRegistry& NodeTemplateRegistry;` — Cached references to the registries we need
- L240 _private member_ `const FTraitRegistry& TraitRegistry;`
- L243 _private member_ `FAnimNextGraphInstance* RootGraphInstance = nullptr;` — Root graph instance we are bound to
- L246 _private member_ `Private::FScopedInterfaceEntry* ScopedInterfaceStackHead = nullptr;` — The head pointer of the scoped interface stack
- L251 _private member_ `Private::FScopedInterfaceEntry* FreeScopedInterfaceEntryStackHead = nullptr;` — The head pointer of the free scoped interface entry stack Entries are allocated from the memstack and are re-used in LIFO since they'll be warmer in the CPU cache
- L262 _function_ `template<class ScopedTraitInterface> inline void FExecutionContext::PushScopedInterface(const FTraitBinding& Binding)`
- L271 _function_ `template<class ScopedTraitInterface> inline void FExecutionContext::PushOptionalScopedInterface(bool bCondition, const FTraitBinding& Binding)`
- L284 _function_ `template<class ScopedTraitInterface> inline bool FExecutionContext::PopScopedInterface(const FTraitBinding& Binding)`
- L292 _function_ `inline bool FExecutionContext::PopStackScopedInterfaces(const FTraitBinding& Binding)`
- L303 _function_ `template<class ScopedTraitInterface> inline bool FExecutionContext::GetScopedInterface(TTraitBinding<ScopedTraitInterface>& OutBinding) const`
- L312 _function_ `template<class ScopedTraitInterface> inline void FExecutionContext::ForEachScopedInterface(TFunctionRef<bool(TTraitBinding<ScopedTraitInterface>& Binding)> InFunction) const`
- L326 _function_ `inline FTraitPtr FExecutionContext::AllocateNodeInstance(const FTraitBinding& ParentBinding, FAnimNextTraitHandle ChildTraitHandle) const`
- L332 _function_ `template<class ComponentType> ComponentType& FExecutionContext::GetOrAddComponent() const`
- L340 _function_ `template<class ComponentType> ComponentType* FExecutionContext::TryGetComponent() const`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)
- L31 _namespace_ `namespace Private` (scope `UE::UAF`)
- L320 _function_ `` (scope `UE::UAF::FExecutionContext::ForEachScopedInterface`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/IScopedTraitInterface.h` (Public)


#### struct `UE::UAF::IScopedTraitInterface`  
`struct IScopedTraitInterface : ITraitInterface`  
_L15-18_
- inherits: `ITraitInterface`
- desc: IScopedTraitInterface Base type for all scoped trait interfaces. Used for type safety.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/ITraitInterface.h` (Public)


#### struct `UE::UAF::ITraitInterface`  
`struct ITraitInterface`  
_L38-59_
- desc: ITraitInterface Base type for all trait interfaces. Used for type safety.
- L40 _public function_ `virtual ~ITraitInterface()`
- L45 _public member_ `static constexpr FTraitInterfaceUID InterfaceUID = FTraitInterfaceUID::MakeUID(TEXT("ITra` — The globally unique UID for this interface Derived types will have their own InterfaceUID member that hides/aliases/shadows this one @see DECLARE_ANIM_TRAIT_INTERFACE
- L48 _public function_ `virtual FTraitInterfaceUID GetInterfaceUID() const` — Returns the globally unique UID for this interface
- L52 _public function_ `virtual bool IsInternal() const` — Internal interfaces are only displayed in the Traits Editor in the Advanced View
- L55 _public function_ `virtual const FText& GetDisplayName() const` — Human readable interface names, in long and short format
- L57 _public function_ `virtual const FText& GetDisplayShortName() const` — Human readable interface names, in short format (ideally 3 or 4 letters, due to space restrictions in the editor)

#### enum `UE::UAF::ETraitStackPropagation`  
`enum class ETraitStackPropagation`  
_L68-75_
- desc: Trait Stack Propagation This enum can be used to signal whether an interface call should be forwarded to its parent on the trait stack or not.
- L71 _public enumerator_ `Continue` — Forward the call to our parent on the trait stack (if we have one)
- L74 _public enumerator_ `Stop` — Do not forward the call to our parent, execution stops

#### struct `UE::UAF::FTraitInterfaceStaticInitHook`  
`struct FTraitInterfaceStaticInitHook final`  
_L84-91_
- desc: FTraitInterfaceStaticInitHook Allows trait interfaces to automatically register/unregister within the current scope. This can be used during static init. See AUTO_REGISTER_ANIM_TRAIT_INTERFACE
- L86 _public prototype_ `explicit FTraitInterfaceStaticInitHook(const TSharedPtr<UE::UAF::ITraitInterface>& InTraitInterface);`
- L87 _public prototype_ `~FTraitInterfaceStaticInitHook();`
- L90 _private member_ `TSharedPtr<ITraitInterface> TraitInterface = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L18 _macro_ `#define DECLARE_ANIM_TRAIT_INTERFACE(InterfaceName) \` — In a trait interface struct declaration, this macro declares the necessary boilerplate we require
- L25 _macro_ `#define AUTO_REGISTER_ANIM_TRAIT_INTERFACE(Interface) \` — Allows a trait interface to auto-register and unregister within the current execution scope The trait interface must be found in the current scope without a namespace qualification
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/LatentPropertyHandle.h` (Public)


#### struct `UE::UAF::FLatentPropertyMetadata`  
`struct FLatentPropertyMetadata final`  
_L17-34_
- desc: Latent Property Metadata The metadata we serialize in the archive for each latent property.
- L20 _public member_ `FName Name;` — The name of the latent property
- L24 _public member_ `uint16 RigVMIndex = MAX_uint16;` — The index of the RigVM memory handle to evaluate to compute our latent value An invalid index of ~0 means that the latent property has a hardcoded inline value
- L27 _public member_ `bool bCanFreeze = false;` — Whether or not the property supports freezing
- L30 _public member_ `bool bUsesVariableCopy = false;` — Whether or not the property is a simple variable copy
- L33 _public member_ `bool bOnBecomeRelevant = false;` — Whether or not the property evaluates only once on become relevant

#### struct `UE::UAF::FLatentPropertiesHeader`  
`struct alignas(uint16) FLatentPropertiesHeader final`  
_L54-67_
- desc: Latent Properties Header Holds metadata about the stored latent properties @see FExecutionContext
- L57 _public member_ `uint8 bHasValidLatentProperties : 1 = false;` — Whether or not this base trait has any bound latent properties that can evaluate
- L60 _public member_ `uint8 bCanAllPropertiesFreeze : 1 = false;` — Whether or not this base trait has all its latent properties support freezing
- L63 _public member_ `uint8 bAllLatentPropertiesOnBecomeRelevant : 1 = false;` — Whether or not this base trait has all its latent properties only evaluate on first frame
- L66 _public member_ `uint8 bAreAllPropertiesVariableAccesses : 1 = false;` — Whether the latent properties for this trait are all simple variable accesses

#### struct `UE::UAF::FLatentPropertyHandle`  
`struct FLatentPropertyHandle final`  
_L88-148_
- desc: Latent Property Handle A latent property handle represents: - A 1-based index into the RigVM memory handles array during execution - A flag that specifies if the latent property should always update or if it supports freezing - A node instance local offset to the cached latent property value A latent property can be in one of 3 states: - Invalid (property is inline and not latent) - Latent and Cached (property is latent and is cached at some offset) - Cached Only (property is not latent but is cached at some offset) The Cached Only state can occur if a base trait has duplicate entries within its property handles. Duplicate entries would have the same RigVM index but different offsets and thus evaluate it repeatedly. To avoid the waste of cycles and space, subsequent properties are marked as Cached Only with the same offset as the first property that is Latent and Cached (it will update the cached location). @see FExecutionContext
- L91 _public prototype_ `constexpr FLatentPropertyHandle() noexcept = default;` — Creates an invalid latent property handle
- L94 _public function_ `constexpr bool IsIndexValid() const noexcept` — Returns true if this latent property handle has a valid RigVM index, false otherwise
- L97 _public function_ `constexpr bool IsOffsetValid() const noexcept` — Returns true if this latent property handle has a valid property offset, false otherwise
- L100 _public function_ `constexpr int32 GetLatentPropertyIndex() const noexcept` — Returns the latent property RigVM index represented by this handle if valid, -1 otherwise
- L104 _public function_ `constexpr uint32 GetLatentPropertyOffset() const noexcept` — Returns the latent property offset represented by this handle if valid, 0 otherwise This offset is relative to the start of the node instance data
- L108 _public function_ `constexpr bool CanFreeze() const noexcept` — Returns whether or not the latent property supports freezing during snapshots Latent properties that do not support freezing always update in a snapshot
- L111 _public function_ `constexpr bool OnBecomeRelevant() const noexcept` — Returns whether or not the latent property evaluates only on become relevant
- L115 _private function_ `FLatentPropertyHandle(uint16 InRigRMIndex, uint32 InPropertyOffset, bool bInCanFreeze, bool bInOnBecomeRelevant) : PackedIndexCanFreezeValue((InRigRMIndex & HANDLE_INDEX_MASK) | (uint16(bInCanFreeze) << HANDLE_CAN_FREEZE_SHIFT_OFFSET) | (uint16(bInOnBecomeRelevant) << HANDLE_ON_BECOME_RELEVANT_SHIFT_OFFSET)) , OffsetValue(uint16(InPropertyOffset))` — Constructs a FLatentPropertyHandle instance
- L124 _private member_ `static constexpr uint16 HANDLE_INDEX_MASK = 0x3FFF;` — A mask for the RigVM index portion of the packed value
- L127 _private member_ `static constexpr uint16 HANDLE_CAN_FREEZE_MASK = 0x8000;` — A mask for the CanFreeze metadata flag in the packed value
- L128 _private member_ `static constexpr uint16 HANDLE_ON_BECOME_RELEVANT_MASK = 0x4000;`
- L131 _private member_ `static constexpr uint16 HANDLE_CAN_FREEZE_SHIFT_OFFSET = 15;` — A shift offset for the CanFreeze metadata flag in the packed value
- L132 _private member_ `static constexpr uint16 HANDLE_ON_BECOME_RELEVANT_SHIFT_OFFSET = 14;`
- L135 _private member_ `static constexpr uint16 INVALID_HANDLE_VALUE = 0x3FFF;` — Latent property handles are a 15 bit index and a 1 bit flag to denote if the property can freeze, ~0 is invalid
- L138 _private member_ `static constexpr uint16 INVALID_OFFSET_VALUE = 0;` — Latent property offsets are relative to the start of the node instance data, 0 is invalid
- L141 _private member_ `uint16 PackedIndexCanFreezeValue = INVALID_HANDLE_VALUE;` — A packed RigVM index and metadata flag for whether or not this property can be frozen
- L144 _private member_ `uint16 OffsetValue = INVALID_OFFSET_VALUE;` — An offset relative to the start of the node instance where the latent property is cached

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L38 _function_ `inline FArchive& operator<<(FArchive& Ar, FLatentPropertyMetadata& Metadata)` (scope `UE::UAF`) — Serializes latent property metadata
- L153 _function_ `inline FArchive& operator<<(FArchive& Ar, FLatentPropertyHandle& Handle)` (scope `UE::UAF`) — Serializes a latent handle value

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/NodeDescription.h` (Public)


#### struct `UE::UAF::FNodeDescription`  
`struct alignas(alignof(uint32)) FNodeDescription`  
_L28-87_
- desc: Node Description A node description represents a unique instance in the authored static graph. A node description may have any number of runtime instances in the dynamically executed graph. As such, a node description is read-only at runtime while a node instance is read/write. A node description is followed in memory by the trait descriptions (their shared read-only data) that live within it. Trait descriptions include things like hard-coded/inline properties, pin links, etc. A node description is itself an instance of a node template. @see FNodeTemplate
- L32 _public member_ `static constexpr uint32 MAXIMUM_NODE_SHARED_DATA_SIZE = 64 * 1024;` — Largest allowed size for a node description and the shared data of its traits We use unsigned 16 bit offsets within the NodeTemplate/TraitTemplate
- L34 _public function_ `FNodeDescription(FNodeID InNodeID, FNodeTemplateRegistryHandle InTemplateHandle) : NodeID(InNodeID) , TemplateHandle(InTemplateHandle) , NodeInstanceDataSize(0) , Padding0(0)`
- L42 _public function_ `FNodeID GetUID() const` — Returns the node UID, unique to the owning sub-graph
- L45 _public function_ `FNodeTemplateRegistryHandle GetTemplateHandle() const` — Returns the handle of the node's template in the node template registry
- L48 _public function_ `uint32 GetNodeInstanceDataSize() const` — Returns the node instance data size factoring in any cached latent properties
- L51 _public prototype_ `void Serialize(FArchive& Ar);` — Serializes this node description instance and the shared data of each trait that follows
- L55 _private member_ `FNodeID NodeID;` — Assigned during export/cook, unique to current sub-graph (16 bits)
- L58 _private member_ `FNodeTemplateRegistryHandle TemplateHandle;` — Offset of the node template within the global list (16 bits)
- L61 _private member_ `uint16 NodeInstanceDataSize;` — The node instance data size, includes latent properties (not serialized, @see FNodeTemplate::Finalize)
- L63 _private member_ `uint16 Padding0;` — Unused

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/NodeHandle.h` (Public)


#### struct `UE::UAF::FNodeHandle`  
`struct FNodeHandle final`  
_L26-95_
- desc: Node Handle A node handle represents a reference to a specific node instance in the shared/read-only portion of a sub-graph. It points to a FNodeDescription when resolved. Internally, it contains either a shared data offset into the parent graph (at runtime) or a FNodeID (during compilation and on disk). Shared offsets must be computed at runtime and as such we use the FNodeID to resolve into our final offset on load. We only use the bottom 24 bits. If the LSB is 0, the packed value represents a shared offset (due to alignment) but if the LSB is 1, the packed value represents a node ID shifted left by 1. @see FNodeDescription, FNodeID
- L29 _public function_ `constexpr FNodeHandle() noexcept : PackedSharedOffsetOrID(INVALID_NODE_HANDLE_RAW_VALUE)` — Creates an invalid node handle
- L34 _public function_ `static constexpr FNodeHandle FromSharedOffset(uint32 SharedOffset) noexcept` — Creates a node handle for the specified shared offset
- L45 _public function_ `static constexpr FNodeHandle FromNodeID(FNodeID NodeID) noexcept` — Creates a node handle from a node ID
- L56 _public function_ `constexpr bool IsValid() const noexcept` — Returns true if this node handle is valid, false otherwise
- L59 _public function_ `constexpr bool IsSharedOffset() const noexcept` — Returns whether this node handle encodes a shared offset or not
- L62 _public function_ `constexpr bool IsNodeID() const noexcept` — Returns whether this node handle encodes a node ID or not
- L65 _public function_ `uint32 GetSharedOffset() const` — Returns the offset into the shared data relative to the root of the owning sub-graph
- L68 _public function_ `FNodeID GetNodeID() const` — Returns the node ID encoded by the handle
- L71 _public function_ `constexpr bool operator==(FNodeHandle RHS) const noexcept` — Equality and inequality tests
- L72 _public function_ `constexpr bool operator!=(FNodeHandle RHS) const noexcept`
- L75 _private function_ `explicit constexpr FNodeHandle(uint32 PackedValue) noexcept : PackedSharedOffsetOrID(PackedValue)`
- L80 _private function_ `constexpr uint32 GetPackedValue() const` — Returns the packed raw value
- L83 _private function_ `static constexpr FNodeHandle FromPackedValue(uint32 PackedValue) noexcept` — Creates a node handle from a raw packed value
- L86 _private member_ `static constexpr uint32 INVALID_NODE_HANDLE_RAW_VALUE = ~0u >> (32 - 24);` — We pack the shared offset on 24 bits, the top 8 bits are unused and they can have any value (zero by default)
- L87 _private member_ `static constexpr uint32 NODE_HANDLE_MASK = INVALID_NODE_HANDLE_RAW_VALUE;`
- L88 _private member_ `static constexpr uint32 NODE_ID_MARKER_BIT_MASK = 0x01u;` — When valid, a LSB of 1 means we encode a node ID, 0 means a shared offset
- L89 _private member_ `static constexpr uint32 NODE_ID_SHIFT = 1;` — Our LSB is reserved as a marker, the node ID is shifted left by 1
- L91 _private member_ `uint32 PackedSharedOffsetOrID;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/NodeID.h` (Public)


#### struct `UE::UAF::FNodeID`  
`struct FNodeID final`  
_L23-70_
- desc: Node ID A node ID fits on 16 bits and is used to encode a node index. The zero ID is reserved as an invalid value, this means that the node index is 1-based. Node IDs are assigned during compilation of an AnimNext graph to each node. The trait reader is then used to convert them into a shared offset within the graph. @see FTraitReader
- L26 _public function_ `constexpr FNodeID() noexcept : ID(INVALID_NODE_ID)` — Constructs an invalid FNodeID
- L29 _public function_ `constexpr bool IsValid() const noexcept` — Returns whether or not this ID is valid
- L33 _public function_ `constexpr uint32 GetNodeIndex() const noexcept` — Returns the node index represented by this node ID If the node ID is invalid, the index returned is 0xFFFFFFFF
- L36 _public function_ `static constexpr FNodeID GetFirstID() noexcept` — The first valid node ID
- L42 _public function_ `constexpr FNodeID GetNextID() const noexcept` — Returns the next node ID If the current ID is invalid, the next is invalid as well Note that this function does not handle wrapping if more than 65536 IDs are used If wrapping occurs, the next ID returned will be invalid and all subsequent IDs will be invalid
- L45 _public function_ `constexpr bool operator==(const FNodeID RHS) const noexcept` — Equality and inequality tests
- L46 _public function_ `constexpr bool operator!=(const FNodeID RHS) const noexcept`
- L57 _private function_ `explicit constexpr FNodeID(uint16 InID) noexcept : ID(InID)` — Constructs a FNodeID instance from a raw value
- L60 _private function_ `constexpr uint32 GetRawValue() const` — Returns the packed raw value
- L63 _private function_ `static constexpr FNodeID FromRawValue(uint32 InID) noexcept` — Creates a node handle from a raw packed value
- L65 _private member_ `static constexpr uint16 INVALID_NODE_ID = 0;`
- L67 _private member_ `uint16 ID;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L49 _function_ `friend FArchive& operator<<(FArchive& Ar, FNodeID& Value)` (scope `UE::UAF`) — Serialization operator

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/NodeInstance.h` (Public)


#### struct `UE::UAF::FNodeInstance`  
`struct FNodeInstance`  
_L21-84_
- desc: Node Instance A node instance represents allocated data for specific node. In order to access the trati instance data, the offsets need to be looked up in the node template. @see FNodeTemplate, FTraitTemplate
- L25 _public member_ `static constexpr uint32 MAXIMUM_NODE_INSTANCE_DATA_SIZE = 64 * 1024;` — Largest allowed size for a node instance and the instance data of its traits We use unsigned 16 bit offsets within the NodeTemplate/TraitTemplate
- L28 _public function_ `bool IsValid() const` — Returns whether the node instance is valid or not
- L31 _public function_ `bool IsOwnedBy(const FAnimNextGraphInstance& GraphInstance) const` — Returns whether or not this node instance is owned by the specified graph instance
- L34 _public function_ `FAnimNextGraphInstance& GetOwner() const` — Returns the graph instance that owns this node instance
- L37 _public function_ `FNodeHandle GetNodeHandle() const` — Returns a handle to the shared data for this node
- L40 _public function_ `uint32 GetReferenceCount() const` — Returns the number of live references to this node instance, does not include weak handles
- L43 _private function_ `FNodeInstance(FAnimNextGraphInstance& InOwner, FNodeHandle InNodeHandle) : Owner(InOwner), ReferenceCount(0), NodeHandle(InNodeHandle)`
- L44 _private function_ `~FNodeInstance()`
- L47 _private prototype_ `FNodeInstance(const FNodeInstance&) = delete;` — Cannot move or copy node instances
- L48 _private prototype_ `FNodeInstance& operator=(const FNodeInstance&) = delete;`
- L51 _private function_ `void AddReference()` — Increments the reference count
- L54 _private function_ `bool RemoveReference()` — Decrements the reference count and returns true if any references remain
- L56 _private member_ `FAnimNextGraphInstance& Owner;` — The graph instance that owns this node instance
- L58 _private member_ `uint32 ReferenceCount;` — how many non-weak FTraitPtr handles point to us, not thread safe
- L59 _private member_ `FNodeHandle NodeHandle;` — relative to root of sub-graph, should this be a pointer?

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/NodeTemplate.h` (Public)


#### struct `UE::UAF::FNodeTemplate`  
`struct FNodeTemplate`  
_L28-92_
- desc: Node Template A node template represents a specific combination and ordering of traits on a node. For example, a sequence player + sync group trait + output caching trait Multiple node descriptions can share the same template each with their own property/pin values. Templates can exist in multiple sub-graphs on disk. On load, a single unique copy is retained in memory and shared between ALL graphs. Node templates are created through the FNodeTemplateBuilder. @see FNodeDescription, FNodeTemplateBuilder
- L33 _public member_ `static constexpr uint32 MAXIMUM_SIZE = 64 * 1024;` — The largest size allowed for a node template Node templates are just a lightweight descriptor, in theory they can have any size We artificially specify a conservative upper bound
- L36 _public function_ `uint32 GetUID() const` — Returns the globally unique template identifier (a hash of all the trait UIDs present in this node)
- L39 _public function_ `uint32 GetNodeTemplateSize() const` — Returns the size in bytes of this node template
- L42 _public function_ `uint32 GetNodeSharedDataSize() const` — Returns the size in bytes of a node shared data
- L45 _public function_ `uint32 GetNodeInstanceDataSize() const` — Returns the size in bytes of a node instance (how much space to allocate to hold a node instance of this template)
- L48 _public function_ `uint32 GetNumTraits() const` — Returns the number of traits present in the node template
- L51 _public function_ `uint32 GetMinAlignment() const` — Returns the required alignment of this node
- L54 _public function_ `bool IsValid() const` — Returns whether the node template is valid or not
- L57 _public function_ `FTraitTemplate* GetTraits()` — Returns a pointer to the list of trait template descriptions
- L60 _public function_ `const FTraitTemplate* GetTraits() const` — Returns a pointer to the list of trait template descriptions
- L63 _public prototype_ `void Serialize(FArchive& Ar);` — Serializes this node template instance and each trait template that follows
- L68 _private function_ `FNodeTemplate(uint32 InUID, uint32 InNumTraits) : UID(InUID) , NodeSharedDataSize(0) , NodeInstanceDataSize(0) , NumTraits(static_cast<uint8>(InNumTraits))`
- L77 _private prototype_ `void Finalize();` — This function performs the necessary fix-ups once all trait templates have been populated Call this function whenever a new node template has been constructed before using it
- L79 _private member_ `uint32 UID;` — globally unique template identifier or hash
- L81 _private member_ `uint16 NodeSharedDataSize;` — size in bytes of a node shared data (not serialized, @see FNodeTemplate::Finalize)
- L82 _private member_ `uint16 NodeInstanceDataSize;` — size in bytes of a node instance, excludes optional latent properties (not serialized, @see FNodeTemplate::Finalize)
- L84 _private member_ `uint8 NumTraits;`
- L85 _private member_ `uint8 MinAlignment;`
- L86 _private member_ `uint8 Padding[2];`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/NodeTemplateRegistryHandle.h` (Public)


#### struct `UE::UAF::FNodeTemplateRegistryHandle`  
`struct FNodeTemplateRegistryHandle final`  
_L15-47_
- desc: FNodeTemplateRegistryHandle Encapsulates a value used as a handle in the node template registry. When valid, it can be used to retrieve a pointer to the corresponding node template.
- L18 _public prototype_ `FNodeTemplateRegistryHandle() = default;` — Default constructed handles are invalid
- L21 _public function_ `bool IsValid() const` — Returns whether or not this handle points to a valid node template
- L24 _public function_ `int32 GetTemplateOffset() const` — Returns the template offset for this handle when valid, otherwise INDEX_NONE
- L27 _public function_ `bool operator==(FNodeTemplateRegistryHandle RHS) const` — Compares for equality and inequality
- L28 _public function_ `bool operator!=(FNodeTemplateRegistryHandle RHS) const`
- L31 _private function_ `explicit FNodeTemplateRegistryHandle(int16 TemplateOffset_) : TemplateOffset(TemplateOffset_)`
- L36 _private function_ `static FNodeTemplateRegistryHandle MakeHandle(int32 TemplateOffset_)` — Creates a handle based on a note template offset in the static buffer
- L44 _private member_ `int16 TemplateOffset = 0;` — When 0, the handle is invalid Otherwise it is a 1-based offset in the registry's static buffer

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/Trait.h` (Public)


#### struct `UE::UAF::Private::EventHandlerTypeTrait`  
`template<typename HandlerEventType> struct EventHandlerTypeTrait<ETraitStackPropagation(*)(FExecutionContext&, FTraitBinding&, HandlerEventType&)>`  
_L187-190_
- L189 _public typedef_ `using EventType = std::remove_const_t<HandlerEventType>;`

#### struct `UE::UAF::Private::EventHandlerTypeTrait`  
`template<typename HandlerEventType> struct EventHandlerTypeTrait<ETraitStackPropagation(*)(const FExecutionContext&, FTraitBinding&, HandlerEventType&)>`  
_L193-196_
- L189 _public typedef_ `using EventType = std::remove_const_t<HandlerEventType>;`

#### struct `UE::UAF::Private::EventHandlerTypeTrait`  
`template<typename BaseType, typename HandlerEventType> struct EventHandlerTypeTrait<ETraitStackPropagation(BaseType::*)(FExecutionContext&, FTraitBinding&, HandlerEventType&) const>`  
_L199-202_
- L189 _public typedef_ `using EventType = std::remove_const_t<HandlerEventType>;`

#### struct `UE::UAF::Private::EventHandlerTypeTrait`  
`template<typename BaseType, typename HandlerEventType> struct EventHandlerTypeTrait<ETraitStackPropagation(BaseType::*)(const FExecutionContext&, FTraitBinding&, HandlerEventType&) const>`  
_L205-208_
- L189 _public typedef_ `using EventType = std::remove_const_t<HandlerEventType>;`

#### struct `UE::UAF::Private::TPaddedDerivedType`  
`template<class BaseType> struct TPaddedDerivedType : public BaseType`  
_L211-211_
- inherits: `BaseType`
- L211 _public member_ `template<class BaseType> struct TPaddedDerivedType : public BaseType { uint8 Dummy; };`

#### struct `UE::UAF::Private::TGetEffectiveSize`  
`template<class StructType> struct TGetEffectiveSize`  
_L219-223_
- desc: Helper to find the effective size of a struct If a struct contains no members, its size as defined by C++ is 1 byte to allow for pointer arithmetic However, if we don't use pointer arithmetic (e.g. have them in an array), then we can avoid this waste by computing its effective size. The effective size of a struct is its size when you derive from it. A struct that has no members ends up with an effective size of zero bytes.
- L222 _public member_ `static constexpr uint32 Value = sizeof(TPaddedDerivedType<StructType>) == sizeof(uint8) ? 0 : sizeof(StructType);` — The effective size of the specified struct

#### struct `UE::UAF::FTraitMemoryLayout`  
`struct FTraitMemoryLayout`  
_L309-328_
- desc: FTraitMemoryLayout Encapsulates size/alignment details for a trait.
- L312 _public member_ `uint32 TraitSize = 0;` — The size in bytes of an instance of the trait class which derives from FTrait
- L315 _public member_ `uint32 TraitAlignment = 1;` — The alignment in bytes of an instance of the trait class which derives from FTrait
- L318 _public member_ `uint32 SharedDataSize = 0;` — The size in bytes of the shared data for the trait which derives from FAnimNextTraitSharedData
- L321 _public member_ `uint32 SharedDataAlignment = 1;` — The alignment in bytes of the shared data for the trait which derives from FAnimNextTraitSharedData
- L324 _public member_ `uint32 InstanceDataSize = 0;` — The size in bytes of the instance data for the trait which derives from FTraitInstanceData
- L327 _public member_ `uint32 InstanceDataAlignment = 1;` — The alignment in bytes of the instance data for the trait which derives from FTraitInstanceData

#### struct `UE::UAF::FTraitLatentPropertyMemoryLayout`  
`struct FTraitLatentPropertyMemoryLayout`  
_L335-345_
- desc: FTraitLatentPropertyMemoryLayout Encapsulates size/alignment details for a latent property.
- L338 _public member_ `uint32 Size = 0;` — The size in bytes of the latent property
- L341 _public member_ `uint32 Alignment = 1;` — The alignment in bytes of the latent property
- L344 _public member_ `int32 LatentPropertyIndex = INDEX_NONE;` — The latent property index that matches the enumerator macro, @see FTrait::GetLatentPropertyIndex

#### struct `UE::UAF::FTrait`  
`struct FTrait`  
_L365-507_
- desc: FTrait Base class for all traits. A trait can implement any number of interfaces based on ITraitInterface. A trait may derive from another trait. A trait should implement GetInterface(..) and test against the interfaces that it supports. Traits should NOT have any internal state, hence why all API functions are 'const'. The reason for this is that at runtime, a single instance of every trait exists. That single instance is used by all instances of a trait on a node and concurrently on all worker threads. Traits can have shared read-only data that all instances of a graph can use (e.g. hard-coded properties). Shared data must derive from FAnimNextTraitSharedData. Traits can have instance data (e.g. blend weight). Instance data must derive from FTraitInstanceData.
- L367 _public function_ `virtual ~FTrait()`
- L371 _public typedef_ `using FSharedData = FAnimNextTraitSharedData;` — Empty shared/instance data types Derived types must define an alias for these
- L372 _public typedef_ `using FInstanceData = FTraitInstanceData;` — Trait instance data must derive from FTraitInstanceData
- L377 _public member_ `static constexpr FTraitUID TraitUID = FTraitUID::MakeUID(TEXT("FTra` — The globally unique UID for this trait Derived types will have their own TraitUID member that hides/aliases/shadows this one @see DECLARE_ANIM_TRAIT
- L380 _public function_ `virtual FTraitUID GetTraitUID() const` — Returns the globally unique UID for this trait
- L383 _public function_ `virtual FString GetTraitName() const` — Returns the trait name
- L386 _public prototype_ `virtual FTraitMemoryLayout GetTraitMemoryDescription() const = 0;` — Returns the memory requirements of the derived trait instance
- L389 _public function_ `virtual UScriptStruct* GetTraitSharedDataStruct() const` — Returns the UScriptStruct associated with the shared data for the trait
- L393 _public prototype_ `virtual void ConstructTraitInstance(const FExecutionContext& Context, const FTraitBinding& Binding) const = 0;` — Called when a new instance of the trait is created or destroyed Derived types must override this and forward to the instance data constructor/destructor
- L394 _public prototype_ `virtual void DestructTraitInstance(const FExecutionContext& Context, const FTraitBinding& Binding) const = 0;`
- L397 _public prototype_ `virtual ETraitMode GetTraitMode() const = 0;` — Returns the trait mode.
- L401 _public function_ `virtual const ITraitInterface* GetTraitInterface(FTraitInterfaceUID InterfaceUID) const` — Returns a pointer to the specified interface if it is supported. Derived types must override this.
- L426 _public function_ `virtual TConstArrayView<FTraitInterfaceUID> GetTraitInterfaces() const` — Returns a list of interfaces that this trait supports
- L429 _public function_ `virtual TConstArrayView<FTraitInterfaceUID> GetTraitRequiredInterfaces() const` — Returns a list of interfaces that this trait reqquires
- L432 _public function_ `virtual ETraitStackPropagation OnTraitEvent(FExecutionContext& Context, FTraitBinding& Binding, FAnimNextTraitEvent& Event) const` — Called when an event reaches an instance of this trait
- L435 _public function_ `virtual TConstArrayView<FTraitEventUID> GetTraitEvents() const` — Returns a list of events that this trait handles
- L438 _public function_ `virtual uint32 GetNumLatentTraitProperties() const` — The number of latent property properties in the shared data of this trait
- L441 _public function_ `virtual FTraitLatentPropertyMemoryLayout GetLatentPropertyMemoryLayout(const FAnimNextTraitSharedData& SharedData, FName PropertyName, uint32 PropertyIndex) const` — Returns the memory layout of the specified latent property
- L444 _public prototype_ `virtual void SerializeTraitSharedData(FArchive& Ar, FAnimNextTraitSharedData& SharedData) const;` — Called to serialize trait shared data
- L451 _public prototype_ `virtual void SaveTraitSharedData(const TFunction<FString(FName PropertyName)>& GetTraitProperty, FAnimNextTraitSharedData& OutSharedData) const;` — Takes the editor properties as authored in the graph and converts them into an instance of the FAnimNextTraitSharedData derived type using UE reflection. Traits can override this function to control how editor only properties are coerced into the runtime shared data instance.
- L455 _public prototype_ `virtual uint32 GetLatentPropertyHandles( const FAnimNextTraitSharedData* InSharedData, TArray<FLatentPropertyMetadata>& OutLatentPropertyHandles, bool bFilterEditorOnly, const TFunction<uint16(FName PropertyName)>& GetTraitLatentPropertyIndex) const;` — Takes the trait shared data and the editor properties as authored in the graph and generates the latent property metadata using UE reflection. Returns the number of latent property metadatas added to OutLatentPropertyHandles
- L462 _public function_ `virtual bool IsHidden() const` — Makes the Trait Editor only display this Trait in Advanced view
- L465 _public function_ `virtual bool MultipleInstanceSupport() const` — Whether or not this trait can be placed multiple times on a trait stack
- L468 _public function_ `virtual void GetProgrammaticPins(FAnimNextTraitSharedData* InSharedData, URigVMController* InController, int32 InParentPinIndex, const URigVMPin* InTraitPin, const FString& InDefaultValue, struct FRigVMPinInfoArray& OutPinArray) const` — Enable Traits to generate TraitStack pins
- L473 _public prototype_ `uint32 GetVariableMappedLatentPropertyHandles( const FAnimNextTraitSharedData* InSharedData, TArray<FLatentPropertyMetadata>& OutLatentPropertyHandles, bool bFilterEditorOnly, const TFunction<uint16(FName PropertyName)>& GetTraitLatentPropertyIndex) const;` — Takes the trait shared data and the editor properties as authored in the graph and generates the latent property metadata using UE reflection. Returns the number of latent property metadatas added to OutLatentPropertyHandles
- L480 _public function_ `bool IsPropertyLatent(const FAnimNextTraitSharedData& InSharedData, FName PropertyName) const` — Returns whether or not the specified property has been marked as latent
- L485 _public function_ `virtual int32 GetLatentPropertyIndex(const FAnimNextTraitSharedData& InSharedData, FName PropertyName) const` — Returns the latent property index or INDEX_NONE if the property isn't found or if it isn't latent WARNING: Latent property handles are in the order defined by the enumerator macro within the shared data, @see FAnimNextTraitSharedData::GetLatentPropertyIndex
- L488 _public prototype_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const;` — Get any upgrade info needed (e.g. to resolve deprecation)
- L492 _protected prototype_ `FTraitLatentPropertyMemoryLayout GetLatentPropertyMemoryLayoutImpl( const FAnimNextTraitSharedData& SharedData, FName PropertyName, uint32 PropertyIndex, TArray<FTraitLatentPropertyMemoryLayout>& LatentPropertyMemoryLayouts) const;` — Implements GetLatentPropertyMemoryLayout() by allowing a map to be provided for caching purposes to speed up repeated queries
- L499 _protected prototype_ `static TArray<FTraitInterfaceUID> BuildTraitInterfaceList( const TConstArrayView<FTraitInterfaceUID>& SuperInterfaces, std::initializer_list<FTraitInterfaceUID> InterfaceList);` — Builds a list of interfaces with the provided super interfaces and current interfaces as an initializer list
- L504 _protected prototype_ `static TArray<FTraitEventUID> BuildTraitEventList( const TConstArrayView<FTraitEventUID>& SuperEvents, std::initializer_list<FTraitEventUID> EventList);` — Builds a list of events with the provided super events and current events as an initializer list

#### struct `UE::UAF::FBaseTrait`  
`struct FBaseTrait : FTrait`  
_L510-515_
- inherits: `FTrait`
- desc: Base class for base traits that are standalone
- L512 _public function_ `DECLARE_ABSTRACT_ANIM_TRAIT(FBaseTrait, FTrait) virtual ETraitMode GetTraitMode() const override`

#### struct `UE::UAF::FAdditiveTrait`  
`struct FAdditiveTrait : FTrait`  
_L518-527_
- inherits: `FTrait`
- desc: Base class for additive traits that override behavior of other traits
- L520 _public function_ `DECLARE_ABSTRACT_ANIM_TRAIT(FAdditiveTrait, FTrait) virtual ETraitMode GetTraitMode() const override`
- L525 _public function_ `virtual bool MultipleInstanceSupport() const override`

#### struct `UE::UAF::FTraitStaticInitHook`  
`struct FTraitStaticInitHook final`  
_L535-542_
- desc: FTraitStaticInitHook Allows traits to automatically register/unregister within the current scope. This can be used during static init.
- L537 _public prototype_ `explicit FTraitStaticInitHook(TraitConstructorFunc InTraitConstructor);`
- L538 _public prototype_ `~FTraitStaticInitHook();`
- L541 _private member_ `TraitConstructorFunc TraitConstructor;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L27 _macro_ `#define ANIM_NEXT_IMPL_DECLARE_ANIM_TRAIT_BASIC(TraitName, SuperTraitName) \`
- L34 _macro_ `#define ANIM_NEXT_IMPL_DECLARE_ANIM_TRAIT_INSTANCING_SUPPORT() \`
- L41 _macro_ `#define ANIM_NEXT_IMPL_DECLARE_ANIM_TRAIT_INTERFACE_SUPPORT() \`
- L46 _macro_ `#define ANIM_NEXT_IMPL_DECLARE_ANIM_TRAIT_EVENT_SUPPORT() \`
- L50 _macro_ `#define ANIM_NEXT_IMPL_DECLARE_ANIM_TRAIT_LATENT_PROPERTY_SUPPORT() \`
- L58 _macro_ `#define DECLARE_ANIM_TRAIT(TraitName, SuperTraitName) \` — Helper macros In the trait class declaration, this macro declares the Super alias and base functions we override We use use FNV1A32 to hash entire TraitName, including 'F' part (Currently must be manually done).
- L65 _macro_ `#define DECLARE_ABSTRACT_ANIM_TRAIT(TraitName, SuperTraitName) \`
- L79 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT(TraitName) \` — Implements various parts of FTrait
- L108 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT_GET_LATENT_PROPERTY_MEMORY_LAYOUT(TraitName) \` — Implements GetLatentPropertyMemoryLayout()
- L116 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT_IS_PROPERTY_LATENT(TraitName) \`
- L136 _macro_ `#define ANIM_NEXT_IMPL_GET_INTERFACE_IMPL_FOR_INTERFACE(InterfaceName) \` — Helper that handles the GetTraitInterface() details for each interface specified by the generator macro
- L143 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT_GET_INTERFACE(TraitName, InterfaceEnumeratorMacro) \` — Implements GetTraitInterface()
- L152 _macro_ `#define ANIM_NEXT_IMPL_GET_INTERFACES_IMPL_FOR_INTERFACE(InterfaceName) InterfaceName::InterfaceUID,` — Helper that handles the GetTraitInterfaces() details for each interface specified by the generator macro
- L155 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT_GET_INTERFACES(TraitName, InterfaceEnumeratorMacro) \` — Implements GetTraitInterfaces()
- L168 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT_GET_REQUIRED_INTERFACES(TraitName, RequiredInterfaceEnumeratorMacro) \` — Implements GetTraitRequiredInterfaces()
- L180 _namespace_ `namespace UE`
- L180 _namespace_ `namespace UAF` (scope `UE`)
- L180 _namespace_ `namespace Private` (scope `UE::UAF`)
- L227 _macro_ `#define ANIM_NEXT_IMPL_ON_TRAIT_EVENT_IMPL_FOR_EVENT(EventHandler) \` — Helper that handles the OnTraitEvent() details for each event specified by the generator macro
- L234 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT_ON_TRAIT_EVENT(TraitName, EventEnumeratorMacro) \` — Implements OnTraitEvent()
- L244 _macro_ `#define ANIM_NEXT_IMPL_GET_TRAIT_EVENTS_IMPL_FOR_EVENT(EventHandler) \` — Helper that handles the GetTraitEvents() details for each event specified by the generator macro
- L248 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_ANIM_TRAIT_GET_TRAIT_EVENTS(TraitName, EventEnumeratorMacro) \` — Implements GetTraitEvents()
- L261 _macro_ `#define NULL_ANIM_TRAIT_INTERFACE_ENUMERATOR(GeneratorMacro)` — A dummy trait interface generator for traits that do not implement any interfaces
- L264 _macro_ `#define NULL_ANIM_TRAIT_EVENT_ENUMERATOR(GeneratorMacro)` — A dummy trait event generator for traits that do not handle any events
- L269 _macro_ `#define GENERATE_ANIM_TRAIT_IMPLEMENTATION(TraitName, InterfaceEnumeratorMacro, RequiredInterfaceEnumeratorMacro, EventEnumeratorMacro) \` — This macro defines the necessary boilerplate for implementing FTrait. See above for usage example.
- L281 _macro_ `#define AUTO_REGISTER_ANIM_TRAIT(TraitName) \` — Allows a trait to auto-register and unregister within the current execution scope The trait must be found in the current scope without a namespace qualification
- L289 _namespace_ `namespace UE`
- L289 _namespace_ `namespace UAF` (scope `UE`)
- L302 _typedef_ `using TraitConstructorFunc = FTrait * (*)(void* DestPtr, FTraitMemoryLayout& MemoryDesc);` (scope `UE::UAF`) — A function pointer to a shim to construct a trait into the desired memory location When called with a nullptr DestPtr, the function returns nullptr and only populates the memory description output argument. This allows the caller to determine how much space to reserve and how to properly align it. This is similar in spirit to various Windows SDK functions.

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitBinding.h` (Public)


#### struct `UE::UAF::FTraitBinding`  
`struct FTraitBinding`  
_L37-272_
- desc: FTraitBinding Base class for all trait bindings. A trait binding contains untyped data about a specific trait instance.
- L40 _public prototype_ `FTraitBinding() = default;` — Creates an empty/invalid binding.
- L43 _public function_ `bool IsValid() const` — Returns whether or not this binding is valid.
- L46 _public function_ `void Reset()` — Resets the trait binding to an invalid state.
- L54 _public function_ `template<class SharedDataType> const SharedDataType* GetSharedData() const` — Queries a node for a pointer to its trait shared data. If the trait handle is invalid, a null pointer is returned.
- L74 _public function_ `template<class InstanceDataType> InstanceDataType* GetInstanceData() const` — Queries a node for a pointer to its trait instance data. If the trait handle is invalid, a null pointer is returned.
- L93 _public function_ `const FLatentPropertyHandle* GetLatentPropertyHandles() const` — Queries a node for a pointer to its trait latent properties. If the trait handle is invalid or if we have no latent properties, a null pointer is returned. WARNING: Latent property handles are in the order defined by the enumerator macro within the shared data, @see FAnimNextTraitSharedData::GetLatentPropertyIndex
- L113 _public function_ `template<typename PropertyType> const PropertyType* GetLatentProperty(FLatentPropertyHandle Handle) const` — Returns a pointer to the latent property specified by the provided handle or nullptr if the binding/handle are invalid
- L132 _public function_ `template<class TraitInterface> bool GetStackInterface(TTraitBinding<TraitInterface>& OutBinding) const` — Queries the trait stack for a trait that implements the specified interface. If no such trait exists, false is returned.
- L140 _public function_ `template<class TraitInterface> bool GetStackInterfaceSuper(TTraitBinding<TraitInterface>& OutSuperBinding) const` — Queries the trait stack for a trait lower on the stack that implements the specified interface. If no such trait exists, false is returned.
- L148 _public function_ `template<class TraitInterface> bool AsInterface(TTraitBinding<TraitInterface>& OutBinding) const` — Queries the current trait for a new interface. If no such interface is found, false it returned.
- L159 _public function_ `template<class TraitInterface> bool HasInterface() const` — Queries the current trait for the presence of the specified interface. If no such interface is found, false it returned.
- L170 _public function_ `template<class TraitInterface> bool HasStackInterface() const` — Queries the trait stack for the presence of a trait that implements the specified interface. If no such trait exists, false is returned.
- L178 _public function_ `template<class TraitInterface> bool HasStackInterfaceSuper() const` — Queries the trait stack for the presence of a trait lower on the stack that implements the specified interface. If no such trait exists, false is returned.
- L184 _public function_ `const FTraitStackBinding* GetStack() const` — Returns the trait stack binding backing this trait binding.
- L188 _public function_ `bool GetStackBaseTrait(FTraitBinding& OutBinding) const` — Returns a trait binding to the base of the stack. Returns true on success, false otherwise.
- L194 _public function_ `FWeakTraitPtr GetTraitPtr() const` — Returns the trait pointer we are bound to.
- L197 _public function_ `uint32 GetTraitIndex() const` — Returns the trait index on the stack we are bound to.
- L200 _public function_ `const FTrait* GetTrait() const` — Returns a pointer to the trait implementation if valid and if the trait is present at runtime
- L203 _public prototype_ `FTraitInterfaceUID GetInterfaceUID() const;` — Returns the trait interface UID when bound, an invalid UID otherwise.
- L206 _public function_ `bool operator==(const FTraitBinding& RHS) const` — Equality and inequality tests
- L207 _public function_ `bool operator!=(const FTraitBinding& RHS) const`
- L210 _protected function_ `FTraitBinding(const FTraitStackBinding* InStack, const FTrait* InTraitImpl, uint32 InTraitIndex, int32 InInterfaceThisOffset = -1) : Stack(InStack) , TraitImpl(InTraitImpl) , TraitIndex(InTraitIndex) , InterfaceThisOffset(InInterfaceThisOffset)`
- L220 _protected function_ `template<class TraitInterfaceType> const TraitInterfaceType* GetInterfaceTyped() const` — Performs a naked cast to the desired interface type
- L227 _protected function_ `bool AsInterfaceImpl(FTraitInterfaceUID InterfaceUID, FTraitBinding& OutBinding) const`
- L245 _protected function_ `bool HasInterfaceImpl(FTraitInterfaceUID InterfaceUID) const`
- L256 _protected member_ `const FTraitStackBinding* Stack = nullptr;` — A pointer to the bound trait stack or nullptr if we are not bound
- L260 _protected member_ `const FTrait* TraitImpl = nullptr;` — A pointer to the trait implementation from which interfaces are found Can be null if the trait is present at runtime but the trait implementation hasn't been registered/found
- L263 _protected member_ `uint32 TraitIndex = 0;` — The index of the trait on the bound stack relative to the base of the stack (not relative to the base of the node)
- L267 _protected member_ `int32 InterfaceThisOffset = -1;` — The offset of the typed interface we are bound to or -1 if we are untyped The offset is relative to the trait implementation pointer

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitEventRaising.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L18 _prototype_ `void RaiseTraitEvent(FExecutionContext& Context, const FTraitStackBinding& StackBinding, FAnimNextTraitEvent& Event);` (scope `UE::UAF`) — Raises a trait event on the specified trait stack This calls OnTraitEvent on each trait of the stack following propagation rules
- L22 _prototype_ `void RaiseTraitEvents(FExecutionContext& Context, const FTraitStackBinding& StackBinding, const FTraitEventList& EventList);` (scope `UE::UAF`) — Raises every trait event from the input list on the specified trait stack This calls OnTraitEvent on each trait of the stack following propagation rules
- L25 _prototype_ `void RaiseTraitEvents(FExecutionContext& Context, FUAFGraphInstanceComponent& Component, const FTraitEventList& EventList);` (scope `UE::UAF`) — Raises every trait event from the input list on the specified component

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitHandle.h` (Public)


#### struct `FAnimNextTraitHandle`  
`struct FAnimNextTraitHandle final`  
_L22-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Trait Handle A trait handle represents a reference to a specific trait instance in the shared/read-only portion of a sub-graph. It points to a FNodeDescription when resolved. Internally, it contains a node handle and a trait index. Trait handles can only be used within an AnimNext graph serialized with FTraitWriter. @see FNodeDescription, FNodeHandle
- L27 _public function_ `constexpr FAnimNextTraitHandle() noexcept : PackedTraitIndexAndNodeHandle(UE::UAF::FNodeHandle::INVALID_NODE_HANDLE_RAW_VALUE)` — Creates an invalid trait handle
- L32 _public function_ `explicit constexpr FAnimNextTraitHandle(UE::UAF::FNodeHandle NodeHandle) noexcept : PackedTraitIndexAndNodeHandle(NodeHandle.GetPackedValue() & NODE_HANDLE_MASK)` — Creates a trait handle pointing to the first trait of the specified node
- L37 _public function_ `FAnimNextTraitHandle(UE::UAF::FNodeHandle NodeHandle, uint32 TraitIndex) : PackedTraitIndexAndNodeHandle((NodeHandle.GetPackedValue() & NODE_HANDLE_MASK) | (TraitIndex << 24))` — Creates a trait handle pointing to the specified trait on the specified node
- L44 _public function_ `constexpr bool IsValid() const noexcept` — Returns true if this trait handle is valid, false otherwise
- L47 _public function_ `constexpr uint32 GetTraitIndex() const noexcept` — Returns the trait index
- L50 _public function_ `constexpr UE::UAF::FNodeHandle GetNodeHandle() const noexcept` — Returns a handle to the node referenced
- L52 _public prototype_ `bool Serialize(class FArchive& Ar);`
- L56 _private member_ `static constexpr uint32 TRAIT_INDEX_SHIFT = 24;` — Bottom 24 bits are used by the node handle while the top 8 bits by the trait index
- L57 _private member_ `static constexpr uint32 NODE_HANDLE_MASK = ~0u >> (32 - TRAIT_INDEX_SHIFT);`
- L60 _private member_ `uint32 PackedTraitIndexAndNodeHandle;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextTraitHandle> : public TStructOpsTypeTraitsBase2<FAnimNextTraitHandle>`  
_L64-70_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextTraitHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L67-69_

#### Free symbols / members of external scopes

- L68 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonbddc12230103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitInstanceData.h` (Public)


#### struct `UE::UAF::FTraitInstanceData`  
`struct FTraitInstanceData`  
_L21-40_
- desc: FTraitInstanceData A trait instance represents allocated data for specific trait instance. @see FNodeInstance A FTraitInstanceData is the base type that trait instance data derives from.
- L28 _public function_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding) noexcept` — Called after the constructor has been called when a new instance is created. This is called after the default constructor. You can override this function by adding a new one with the same name on your derived type. Traits are constructed from the bottom to the top.
- L37 _public function_ `void Destruct(const FExecutionContext& Context, const FTraitBinding& Binding) noexcept` — Called before the destructor has been called when an instance is destroyed. This is called before the default destructor. You can override this function by adding a new one with the same name on your derived type. Traits are destructed from the top to the bottom.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitInterfaceUID.h` (Public)


#### struct `UE::UAF::FTraitInterfaceUID`  
`struct FTraitInterfaceUID final`  
_L20-74_
- desc: FTraitInterfaceUID Encapsulates an interface global UID. The whole struct is meant to be 'constexpr' to allow inlining within the assembly as constants.
- L23 _public function_ `constexpr FTraitInterfaceUID() : UID(INVALID_UID) #if !UE_BUILD_SHIPPING || WITH_EDITOR , InterfaceName(TEXT("<Invalid Interface UID>")) #endif` — Constructs an invalid UID
- L31 _public function_ `explicit constexpr FTraitInterfaceUID(FTraitInterfaceUIDRaw InUID) : UID(InUID) #if !UE_BUILD_SHIPPING || WITH_EDITOR , InterfaceName(TEXT("<Unknown Trait Interface Name>")) #endif` — Constructs an interface UID from its raw value
- L41 _public function_ `template<typename CharType, int32 Len> static UE_CONSTEVAL FTraitInterfaceUID MakeUID(const CharType(&InInterfaceName)[Len]) noexcept` — Constructs a trait UID from a string literal
- L48 _public function_ `constexpr const TCHAR* GetInterfaceName() const` — Returns a string literal to the interface name
- L52 _public function_ `constexpr FTraitInterfaceUIDRaw GetUID() const` — Returns the interface global UID
- L55 _public function_ `constexpr bool IsValid() const` — Returns whether this UID is valid or not
- L58 _private member_ `static constexpr FTraitInterfaceUIDRaw INVALID_UID = 0;`
- L61 _private function_ `explicit constexpr FTraitInterfaceUID(FTraitInterfaceUIDRaw InUID, const TCHAR* InInterfaceName) noexcept : UID(InUID) #if !UE_BUILD_SHIPPING || WITH_EDITOR , InterfaceName(InInterfaceName) #endif` — Constructs an interface UID
- L69 _private member_ `FTraitInterfaceUIDRaw UID;`
- L72 _private member_ `const TCHAR* InterfaceName = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L11 _typedef_ `using FTraitInterfaceUIDRaw = uint32;` (scope `UE::UAF`) — Type alias for a raw trait UID, not typesafe
- L77 _function_ `constexpr bool operator==(FTraitInterfaceUID LHS, FTraitInterfaceUID RHS)` (scope `UE::UAF`) — Compares for equality and inequality
- L78 _function_ `constexpr bool operator!=(FTraitInterfaceUID LHS, FTraitInterfaceUID RHS)` (scope `UE::UAF`)
- L81 _function_ `constexpr bool operator<(FTraitInterfaceUID LHS, FTraitInterfaceUID RHS)` (scope `UE::UAF`) — For sorting

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitMode.h` (Public)


#### enum `UE::UAF::ETraitMode`  
`enum class ETraitMode`  
_L14-41_
- desc: ETraitMode Describes how a trait behaves once attached to an animation node.
- L19 _public enumerator_ `Invalid = 0` — Invalid value is used for default variable initialization
- L27 _public enumerator_ `Base` — Base traits can live on their own in an animation node and have no 'Super'. As a result, calls to GetInterface() do not forward to other traits below them on the node stack. Multiple base traits can exist in a single animation node but they behave as independent nodes (functionally speaking).
- L35 _public enumerator_ `Additive` — Additive traits override or augment behavior on prior traits on the node stack. At least one base trait must be present for an additive trait to be added on top. Calls to GetInterface() will pass-through to other traits below on the stack until a base trait is found.
- L40 _public enumerator_ `Num = Additive` — Max value is used for iteration / static checks

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitPtr.h` (Public)


#### struct `UE::UAF::FTraitPtr`  
`struct FTraitPtr`  
_L27-86_
- desc: Trait Pointer A trait pointer represents a shared pointer to allocated instance data. It manages reference counting. It points to a FTraitInstanceData or FNodeInstance when resolved. A node pointer can also be weak, meaning that it does not update reference counting. Note that weak pointers will point to garbage if the trait instance is destroyed. Weak trait pointers should be used carefully! @see FNodeInstance, FTraitInstanceData
- L30 _public prototype_ `constexpr FTraitPtr() noexcept = default;` — Constructs an invalid pointer handle
- L33 _public prototype_ `FTraitPtr(FNodeInstance* InNodeInstance, uint32 InTraitIndex);` — Constructs a pointer handle to the provided instance
- L35 _public prototype_ `FTraitPtr(const FTraitPtr& TraitPtr);`
- L36 _public prototype_ `explicit FTraitPtr(const FWeakTraitPtr& TraitPtr);`
- L37 _public prototype_ `FTraitPtr(FTraitPtr&& TraitPtr) noexcept;`
- L38 _public prototype_ `~FTraitPtr();`
- L40 _public prototype_ `FTraitPtr& operator=(const FWeakTraitPtr& TraitPtr);`
- L41 _public prototype_ `FTraitPtr& operator=(const FTraitPtr& TraitPtr);`
- L42 _public prototype_ `FTraitPtr& operator=(FTraitPtr&& TraitPtr) noexcept;`
- L45 _public function_ `FNodeInstance* GetNodeInstance() const noexcept` — Returns a pointer to the node instance
- L48 _public function_ `constexpr uint32 GetTraitIndex() const noexcept` — Returns the trait index this pointer handle references
- L51 _public function_ `constexpr bool IsValid() const noexcept` — Returns true when the pointer is valid, false otherwise
- L54 _public function_ `constexpr bool IsWeak() const noexcept` — Returns true if this pointer handle is weak, false otherwise
- L57 _public prototype_ `void Reset();` — Clears the handle and renders it invalid
- L60 _public function_ `bool operator==(const FTraitPtr& RHS) const` — Equality and inequality tests
- L61 _public function_ `bool operator!=(const FTraitPtr& RHS) const`
- L62 _public prototype_ `bool operator==(const FWeakTraitPtr& RHS) const;`
- L63 _public prototype_ `bool operator!=(const FWeakTraitPtr& RHS) const;`
- L77 _private prototype_ `FTraitPtr(FNodeInstance* InNodeInstance, EFlags InFlags, uint32 InTraitIndex);` — Constructs a pointer handle to the provided instance
- L81 _private member_ `uintptr_t PackedPointerAndFlags = 0;` — Packed pointer value contains a pointer along with flags in the alignment bits The pointer part points to a node instance
- L82 _private member_ `uint32 TraitIndex = 0;` — Only need 8 bits, but use 32 since we have ample padding, avoids truncation
- L135 _function_ `inline bool FTraitPtr::operator==(const FWeakTraitPtr& RHS) const`
- L136 _function_ `inline bool FTraitPtr::operator!=(const FWeakTraitPtr& RHS) const`

#### enum `UE::UAF::FTraitPtr::EFlags`  
`enum EFlags : uintptr_t`  
_L67-74_
- desc: Various flags stored in the pointer alignment bits, assumes an alignment of at least 4 bytes
- L70 _public enumerator_ `IS_WEAK_BIT = 0x01` — When true, this handle is weak and it will not update the instance reference count
- L73 _public enumerator_ `FLAGS_MASK = 0x03` — Bit mask to clear all flags from the packed pointer value

#### struct `UE::UAF::FWeakTraitPtr`  
`struct FWeakTraitPtr`  
_L96-131_
- desc: Weak Trait Pointer Same as a FTraitPtr but is strongly typed to be weak. Weak trait pointers should be used carefully! @see FTraitPtr
- L99 _public prototype_ `constexpr FWeakTraitPtr() noexcept = default;` — Constructs an invalid weak pointer handle
- L102 _public function_ `FWeakTraitPtr(const FTraitPtr& TraitPtr) noexcept : NodeInstance(TraitPtr.GetNodeInstance()) , TraitIndex(TraitPtr.TraitIndex)` — Constructs a weak pointer handle from a shared pointer handle
- L108 _public prototype_ `FWeakTraitPtr(FNodeInstance* InNodeInstance, uint32 InTraitIndex);` — Constructs a weak pointer handle to the provided instance
- L111 _public function_ `constexpr FNodeInstance* GetNodeInstance() const noexcept` — Returns a pointer to the node instance
- L114 _public function_ `constexpr uint32 GetTraitIndex() const noexcept` — Returns the trait index this pointer handle references
- L117 _public function_ `constexpr bool IsValid() const noexcept` — Returns true when the pointer is valid, false otherwise
- L120 _public prototype_ `void Reset();` — Clears the handle and renders it invalid
- L123 _public function_ `bool operator==(const FWeakTraitPtr& RHS) const` — Equality and inequality tests
- L124 _public function_ `bool operator!=(const FWeakTraitPtr& RHS) const`
- L125 _public function_ `bool operator==(const FTraitPtr& RHS) const`
- L126 _public function_ `bool operator!=(const FTraitPtr& RHS) const`
- L129 _private member_ `FNodeInstance* NodeInstance = nullptr;`
- L130 _private member_ `uint32 TraitIndex = 0;` — Only need 8 bits, but use 32 since we have ample padding, avoids truncation

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitRegistryHandle.h` (Public)


#### struct `UE::UAF::FTraitRegistryHandle`  
`struct FTraitRegistryHandle final`  
_L15-65_
- desc: FTraitRegistryHandle Encapsulates a value used as a handle in the trait registry. When valid, it can be used to retrieve a pointer to the corresponding trait.
- L18 _public prototype_ `FTraitRegistryHandle() noexcept = default;` — Default constructed handles are invalid
- L21 _public function_ `bool IsValid() const noexcept` — Returns whether or not this handle points to a valid trait
- L24 _public function_ `bool IsStatic() const noexcept` — Returns whether or not this handle is valid and points to a static trait
- L27 _public function_ `bool IsDynamic() const noexcept` — Returns whether or not this handle is valid and points to a dynamic trait
- L30 _public function_ `int32 GetStaticOffset() const noexcept` — Returns the static buffer offset for this handle when valid, otherwise INDEX_NONE
- L33 _public function_ `int32 GetDynamicIndex() const noexcept` — Returns the dynamic array index for this handle when valid, otherwise INDEX_NONE
- L36 _public function_ `bool operator==(FTraitRegistryHandle RHS) const noexcept` — Compares for equality and inequality
- L37 _public function_ `bool operator!=(FTraitRegistryHandle RHS) const noexcept`
- L40 _private function_ `explicit FTraitRegistryHandle(int16 HandleValue_) noexcept : HandleValue(HandleValue_)`
- L45 _private function_ `static FTraitRegistryHandle MakeStatic(int32 TraitOffset)` — Creates a static handle based on a trait offset in the static buffer
- L52 _private function_ `static FTraitRegistryHandle MakeDynamic(int32 TraitIndex)` — Creates a dynamic handle based on a trait index in the dynamic array
- L62 _private member_ `int16 HandleValue = 0;` — When 0, the handle is invalid When positive, it is a 1-based offset in the registry's static buffer When negative, it is a 1-based index in the registry's dynamic array

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitSharedData.h` (Public)


#### struct `FAnimNextTraitSharedData`  
`struct FAnimNextTraitSharedData`  
_L131-154_
- reflection: `USTRUCT()`
- desc: FAnimNextTraitSharedData Trait shared data represents a unique instance in the authored static graph. Each instance of a graph will share instances of the read-only shared data. Shared data typically contains hardcoded properties, RigVM latent pin information, or pooled properties shared between multiple traits. @see FNodeDescription A FAnimNextTraitSharedData is the base type that trait shared data derives from.
- L138 _public function_ `static void ConstructLatentProperties(const UE::UAF::FTraitBinding& Binding)` — Constructs the latent properties on the bound trait instance
- L143 _public function_ `static void DestructLatentProperties(const UE::UAF::FTraitBinding& Binding)` — Destructs the latent properties on the bound trait instance
- L153 _public function_ `static constexpr int32 GetLatentPropertyIndex(const size_t LatentPropertyOffset)` — Returns the latent property index from a latent property offset If the property is found within this type, its latent property 1-based index is returned (a positive value) If the property isn't found, this function returns the number of latent properties (as a zero or negative value) Derived types will have latent property indices higher than their base type Note that the property index is derived from the order specified in the GENERATE_TRAIT_LATENT_PROPERTIES enumerator macro which might not match the order of the UStruct

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L17 _macro_ `#define ANIM_NEXT_IMPL_EXECUTE_LATENT_CONSTRUCTOR_FOR_PROPERTY(PropertyName) \`
- L29 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_LATENT_CONSTRUCTOR(EnumeratorMacro) \`
- L38 _macro_ `#define ANIM_NEXT_IMPL_EXECUTE_LATENT_DESTRUCTOR_FOR_PROPERTY(PropertyName) \`
- L50 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_LATENT_DESTRUCTOR(EnumeratorMacro) \`
- L59 _macro_ `#define ANIM_NEXT_IMPL_GET_LATENT_PROPERTY_INDEX_FOR_PROPERTY(PropertyName) \`
- L66 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_GET_LATENT_PROPERTY_INDEX(EnumeratorMacro) \`
- L84 _macro_ `#define ANIM_NEXT_IMPL_DEFINE_LATENT_GETTER(PropertyName) \`
- L112 _macro_ `#define GENERATE_TRAIT_LATENT_PROPERTIES(SharedDataType, EnumeratorMacro) \` — This macro defines the necessary boilerplate for latent property support. It takes as arguments the shared data struct name that owns the latent properties and an enumerator macro. The enumerator macro should accept one argument which will be a macro to apply to each latent property. We then use it to define what we need.

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitStackBinding.h` (Public)


#### struct `UE::UAF::FTraitStackBinding`  
`struct FTraitStackBinding`  
_L31-146_
- desc: FTraitStackBinding To keep the node instance cost as low as possible, data such as pointers to the shared data are not stored per node and are instead fetched on demand. In order to be able to query for interfaces on a trait stack from a trait pointer, a trait stack binding must first be created.
- L34 _public prototype_ `FTraitStackBinding() = default;` — Creates an empty/invalid binding.
- L37 _public function_ `bool IsValid() const` — Returns whether or not this binding is valid.
- L48 _public prototype_ `void SnapshotLatentProperties(float DeltaTime, bool bIsFrozen, bool bIsFirstUpdate);` — Takes a snapshot of all latent properties on this trait stack. Delta time supplied so that RigVM execution can access it Properties can be marked as always updating or as supporting freezing (e.g. when a branch of the graph blends out). A freezable property does not update when a snapshot is taken of a frozen stack.
- L51 _public function_ `FWeakTraitPtr GetBaseTraitPtr() const` — Returns a trait pointer to the base of the trait stack.
- L54 _public prototype_ `void Reset();` — Resets the stack binding to an invalid state.
- L57 _public prototype_ `bool operator==(const FTraitStackBinding& Other) const;` — Equality testing
- L58 _public function_ `bool operator!=(const FTraitStackBinding& Other) const`
- L67 _public prototype_ `bool GetTopTrait(FTraitBinding& OutBinding) const;` — Returns a trait binding to the top of the stack. Returns true on success, false otherwise.
- L71 _public prototype_ `bool GetParentTrait(const FTraitBinding& ChildBinding, FTraitBinding& OutParentBinding) const;` — Returns a trait binding to the trait below the specified one (its parent). Returns true on success, false otherwise.
- L75 _public prototype_ `bool GetBaseTrait(FTraitBinding& OutBinding) const;` — Returns a trait binding to the base of the stack. Returns true on success, false otherwise.
- L79 _public prototype_ `bool GetChildTrait(const FTraitBinding& ParentBinding, FTraitBinding& OutChildBinding) const;` — Returns a trait binding to the trait above the specified one (its child). Returns true on success, false otherwise.
- L83 _public prototype_ `bool GetTrait(uint32 TraitIndex, FTraitBinding& OutBinding) const;` — Returns a trait binding to the trait at the specified index (relative to the start of the stack). Returns true on success, false otherwise.
- L86 _public prototype_ `uint32 GetNumTraits() const;` — Returns the number of traits on this stack.
- L97 _public prototype_ `template<class TraitInterface> bool GetInterface(TTraitBinding<TraitInterface>& OutBinding) const;` — Queries the trait stack for a trait that implements the specified interface. The search begins at the top of the stack. Returns true on success, false otherwise.
- L102 _public prototype_ `template<class TraitInterface> bool GetInterfaceSuper(const FTraitBinding& Binding, TTraitBinding<TraitInterface>& OutSuperBinding) const;` — Queries the trait stack for a trait lower on the stack that implements the specified interface. Returns true on success, false otherwise.
- L108 _public prototype_ `template<class TraitInterface> bool HasInterface() const;` — Queries the trait stack for the presence of a trait that implements the specified interface. The search begins at the top of the stack. Returns true on success, false otherwise.
- L113 _public prototype_ `template<class TraitInterface> bool HasInterfaceSuper(const FTraitBinding& Binding) const;` — Queries the trait stack for the presence of a trait lower on the stack that implements the specified interface. Returns true on success, false otherwise.
- L118 _private prototype_ `FTraitStackBinding(const FExecutionContext& InContext, const FWeakTraitPtr& TraitPtr);` — Creates a trait stack binding with the stack that owns the specified trait pointer.
- L120 _private prototype_ `bool GetInterfaceImpl(FTraitInterfaceUID InterfaceUID, FTraitBinding& OutBinding) const;`
- L121 _private prototype_ `bool GetInterfaceSuperImpl(FTraitInterfaceUID InterfaceUID, const FTraitBinding& Binding, FTraitBinding& OutSuperBinding) const;`
- L122 _private prototype_ `bool HasInterfaceImpl(FTraitInterfaceUID InterfaceUID) const;`
- L123 _private prototype_ `bool HasInterfaceSuperImpl(FTraitInterfaceUID InterfaceUID, const FTraitBinding& Binding) const;`
- L126 _private member_ `const FExecutionContext* Context = nullptr;` — A pointer to the execution context that created the binding
- L129 _private member_ `FNodeInstance* NodeInstance = nullptr;` — A pointer to the node instance data we are bound to
- L132 _private member_ `const FNodeDescription* NodeDescription = nullptr;` — A pointer to the node shared data we are bound to
- L135 _private member_ `const FNodeTemplate* NodeTemplate = nullptr;` — A pointer to the node template used by the node we are bound to
- L139 _private member_ `uint32 BaseTraitIndex = 0;` — The base trait index of the bound trait stack on the node A node can contain multiple independent trait stacks by having multiple base traits
- L142 _private member_ `uint32 TopTraitIndex = 0;` — The top trait index of the bound trait stack on the node
- L152 _function_ `template<class TraitInterface> inline bool FTraitStackBinding::GetInterface(TTraitBinding<TraitInterface>& OutBinding) const`
- L161 _function_ `template<class TraitInterface> inline bool FTraitStackBinding::GetInterfaceSuper(const FTraitBinding& Binding, TTraitBinding<TraitInterface>& OutSuperBinding) const`
- L170 _function_ `template<class TraitInterface> inline bool FTraitStackBinding::HasInterface() const`
- L179 _function_ `template<class TraitInterface> inline bool FTraitStackBinding::HasInterfaceSuper(const FTraitBinding& Binding) const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitTemplate.h` (Public)


#### struct `UE::UAF::FTraitTemplate`  
`struct FTraitTemplate`  
_L28-212_
- desc: Trait Template A trait template represents a specific trait within a FNodeTemplate. @see FNodeTemplate
- L31 _public function_ `FTraitUID GetUID() const noexcept` — Returns the globally unique identifier for the trait
- L34 _public function_ `FTraitRegistryHandle GetRegistryHandle() const noexcept` — Returns the trait registry handle
- L38 _public function_ `bool IsValid() const noexcept` — Returns whether or not this trait template is valid A trait template is invalid if the trait implementation hasn't been registered
- L41 _public function_ `ETraitMode GetMode() const noexcept` — Returns the trait mode
- L44 _public function_ `bool IsGCAware() const noexcept` — Returns whether this trait template needs be registered with the reference collector
- L47 _public function_ `uint32 GetNumStackTraits() const` — For base traits only, returns the number of traits on the sub-stack
- L54 _public function_ `uint32 GetTraitIndex() const` — Returns the trait index relative to the base trait on the sub-stack
- L60 _public function_ `uint32 GetNumLatentPropreties() const noexcept` — Returns the number of latent properties on this trait
- L64 _public function_ `uint32 GetNumSubStackLatentPropreties() const` — Returns the number of latent properties on the trait sub-stack Only available on the base trait of the sub-stack
- L71 _public function_ `uint32 GetNodeSharedOffset() const noexcept` — Returns the offset into the shared data where the descriptor begins, relative to the root of the node's shared data
- L77 _public function_ `uint32 GetNodeSharedLatentPropertyHandlesOffset() const noexcept` — Returns the offset into the shared data where the latent property handles begin, relative to the root of the node's shared data The base trait has an instance of FLatentPropertiesHeader preceding its latent handles of type FLatentPropertyHandle Additive traits just have a list of FLatentPropertyHandle Note that the offset might not be zero even if no latent properties live on this trait
- L80 _public function_ `uint32 GetNodeInstanceOffset() const noexcept` — Returns the offset into the instance data where the descriptor begins, relative to the root of the node's instance data
- L83 _public function_ `bool HasLatentProperties() const noexcept` — Returns whether or not we have latent properties on this trait
- L86 _public function_ `FAnimNextTraitSharedData* GetTraitDescription(FNodeDescription& NodeDescription) const noexcept` — Returns a pointer to the specified trait description on the current node
- L92 _public function_ `const FAnimNextTraitSharedData* GetTraitDescription(const FNodeDescription& NodeDescription) const noexcept` — Returns a pointer to the specified trait description on the current node
- L98 _public function_ `FLatentPropertiesHeader& GetTraitLatentPropertiesHeader(FNodeDescription& NodeDescription) const noexcept` — Returns a reference to the specified trait latent properties header on the current node
- L105 _public function_ `const FLatentPropertiesHeader& GetTraitLatentPropertiesHeader(const FNodeDescription& NodeDescription) const noexcept` — Returns a reference to the specified trait latent properties header on the current node
- L114 _public function_ `FLatentPropertyHandle* GetTraitLatentPropertyHandles(FNodeDescription& NodeDescription) const noexcept` — Returns a pointer to the specified trait latent property handles on the current node WARNING: Latent property handles are in the order defined by the enumerator macro within the shared data, @see FAnimNextTraitSharedData::GetLatentPropertyIndex
- L122 _public function_ `const FLatentPropertyHandle* GetTraitLatentPropertyHandles(const FNodeDescription& NodeDescription) const noexcept` — Returns a pointer to the specified trait latent property handles on the current node WARNING: Latent property handles are in the order defined by the enumerator macro within the shared data, @see FAnimNextTraitSharedData::GetLatentPropertyIndex
- L128 _public function_ `FTraitInstanceData* GetTraitInstance(FNodeInstance& NodeInstance) const noexcept` — Returns a pointer to the specified trait instance on the current node
- L134 _public function_ `const FTraitInstanceData* GetTraitInstance(const FNodeInstance& NodeInstance) const noexcept` — Returns a pointer to the specified trait instance on the current node
- L140 _public prototype_ `void Serialize(FArchive& Ar);` — Serializes this trait template instance
- L146 _private function_ `FTraitTemplate(FTraitUID InUID, FTraitRegistryHandle InRegistryHandle, ETraitMode InMode, bool bInGCAware, uint32 InTraitIndexOrNumTraits) noexcept : UID(InUID.GetUID()) , RegistryHandle(InRegistryHandle) , Mode(static_cast<uint8>(InMode)) , bGCAware(bInGCAware) , Padding0(0) , TraitIndexOrNumTraits(InTraitIndexOrNumTraits) , NumLatentProperties(0) , NumSubStackLatentProperties(0)`
- L164 _private member_ `FTraitUIDRaw UID;` — Trait globally unique identifier (32 bits)
- L167 _private member_ `FTraitRegistryHandle RegistryHandle;` — Cached trait registry handle (16 bits)
- L170 _private member_ `uint8 Mode : 2;` — Trait mode (we only need 2 bits)
- L174 _private member_ `uint8 bGCAware : 1;` — Flag set if a trait implements IGarbageCollection
- L177 _private member_ `uint8 Padding0 : 5;` — (Padding for extra flags)
- L182 _private member_ `uint8 TraitIndexOrNumTraits;` — For base traits, this contains the number of traits on our sub-stack For additive traits, this contains the trait index relative to the base trait The first additive trait has index 1, there is no index 0 (we re-purpose the value for the base trait)
- L192 _private member_ `uint16 NumLatentProperties;` — How many latent properties are defined on this trait (cached value of FTrait::GetNumLatentPropreties to avoid repeated lookups) Not serialized, @see FNodeTemplate::Finalize
- L196 _private member_ `uint16 NumSubStackLatentProperties;` — How many latent properties are defined on this trait sub-stack (stored on base trait only) Not serialized, @see FNodeTemplate::Finalize
- L204 _private member_ `uint16 NodeSharedOffset;` — Start of shared data for this trait
- L205 _private member_ `uint16 NodeSharedLatentPropertyHandlesOffset;` — Start of shared latent property handles for this trait
- L206 _private member_ `uint16 NodeInstanceOffset;` — Start of instance data for this trait
- L208 _private member_ `uint16 Padding1;` — Unused for now

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitCore/TraitUID.h` (Public)


#### struct `UE::UAF::FTraitUID`  
`struct FTraitUID final`  
_L20-75_
- desc: FTraitUID Encapsulates a trait global UID. The whole struct is meant to be 'constexpr' to allow inlining within the assembly as constants.
- L23 _public function_ `constexpr FTraitUID() noexcept : UID(INVALID_UID) #if !UE_BUILD_SHIPPING , TraitName(TEXT("<Invalid trait UID>")) #endif` — Constructs an invalid UID
- L32 _public function_ `explicit constexpr FTraitUID(FTraitUIDRaw InUID) noexcept : UID(InUID) #if !UE_BUILD_SHIPPING , TraitName(TEXT("<Unknown Trait Name>")) #endif` — Constructs a trait UID from its raw value
- L42 _public function_ `template<typename CharType, int32 Len> static UE_CONSTEVAL FTraitUID MakeUID(const CharType(&InTraitName)[Len]) noexcept` — Constructs a trait UID from a string literal
- L49 _public function_ `constexpr const TCHAR* GetTraitName() const noexcept` — Returns a string literal to the trait name
- L53 _public function_ `constexpr FTraitUIDRaw GetUID() const noexcept` — Returns the trait global UID
- L56 _public function_ `constexpr bool IsValid() const noexcept` — Returns whether this UID is valid or not
- L59 _private member_ `static constexpr FTraitUIDRaw INVALID_UID = 0;`
- L62 _private function_ `explicit constexpr FTraitUID(FTraitUIDRaw InUID, const TCHAR* InTraitName) noexcept : UID(InUID) #if !UE_BUILD_SHIPPING , TraitName(InTraitName) #endif` — Constructs a trait UID
- L70 _private member_ `FTraitUIDRaw UID;`
- L73 _private member_ `const TCHAR* TraitName;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L11 _typedef_ `using FTraitUIDRaw = uint32;` (scope `UE::UAF`) — Type alias for a raw trait UID, not typesafe
- L78 _function_ `constexpr bool operator==(FTraitUID LHS, FTraitUID RHS) noexcept` (scope `UE::UAF`) — Compares for equality and inequality
- L79 _function_ `constexpr bool operator!=(FTraitUID LHS, FTraitUID RHS) noexcept` (scope `UE::UAF`)
- L80 _function_ `constexpr bool operator==(FTraitUID LHS, FTraitUIDRaw RHS) noexcept` (scope `UE::UAF`)
- L81 _function_ `constexpr bool operator!=(FTraitUID LHS, FTraitUIDRaw RHS) noexcept` (scope `UE::UAF`)
- L82 _function_ `constexpr bool operator==(FTraitUIDRaw LHS, FTraitUID RHS) noexcept` (scope `UE::UAF`)
- L83 _function_ `constexpr bool operator!=(FTraitUIDRaw LHS, FTraitUID RHS) noexcept` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/Args/IAlphaInputArgs.h` (Public)


#### struct `FAlphaInputTraitArgs`  
`struct FAlphaInputTraitArgs : public FAnimNextTraitSharedData`  
_L16-52_
- reflection: `USTRUCT(meta = (DisplayName = "Alpha Input Args"))`
- inherits: `FAnimNextTraitSharedData`
- L21 _public member_ `float Alpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Float"))`
- L24 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden, EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Float"))`
- L27 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden, DisplayAfter = "AlphaCurveName", EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Float || AlphaInputType == EAnimAlphaInputType::Curve"))`
- L30 _public member_ `bool bAlphaBoolEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "bEnabled", EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Bool"))`
- L33 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden, DisplayName = "Blend Settings", EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Bool"))`
- L37 _public member_ `FName AlphaCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Curve"))` — Note: For curve types, the additive branch will always be evaluated. Curve weight blending will occur at task evaluation time.
- L40 _public member_ `EAnimAlphaInputType AlphaInputType = EAnimAlphaInputType::Float;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### struct `UE::UAF::IAlphaInputArgs`  
`struct IAlphaInputArgs : ITraitInterface`  
_L65-102_
- inherits: `ITraitInterface`
- desc: IAlphaInputArgs This interface exposes alpha input args & convience methods for operating on those args Alpha input is typically a curve / float / bool that controls the strength of some other trait. Ex: 0 - no effect, 1 - full effect.
- L67 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IAlphaInputArgs) virtual FAlphaInputTraitArgs Get(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const;`
- L78 _public prototype_ `virtual EAnimAlphaInputType GetAlphaInputType(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const;` — Returns current alpha input type
- L83 _public prototype_ `virtual FName GetAlphaCurveName(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const;` — Returns current alpha curve name, if any
- L90 _public prototype_ `virtual float GetCurrentAlphaValue(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const;` — Returns alpha value for current input. For curve types this will be 1.0, so curves should use trait args to resolve alpha in a task. @param DeltaTime - Time since last API call using DeltaTime (Ex: Time since last 'ComputeAlphaValue' call).
- L96 _public prototype_ `virtual TFunction<float(float)> GetInputScaleBiasClampCallback(const FExecutionContext& Context, const TTraitBinding<IAlphaInputArgs>& Binding) const;` — Returns callback to clamp alpha values, typically used for curve sampling Note: Callback may perform a deferred write to alpha input instance data.
- L99 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L100 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IAlphaInputArgs> : FTraitBinding`  
_L108-142_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L111 _public function_ `FAlphaInputTraitArgs Get(const FExecutionContext& Context) const` — @see IAlphaInputArgs::Get
- L117 _public function_ `EAnimAlphaInputType GetAlphaInputType(const FExecutionContext& Context) const` — @see IAlphaInputArgs::GetAlphaInputType
- L123 _public function_ `FName GetAlphaCurveName(const FExecutionContext& Context) const` — @see IAlphaInputArgs::GetAlphaCurveName
- L129 _public function_ `float GetCurrentAlphaValue(const FExecutionContext& Context) const` — @see IAlphaInputArgs::GetCurrentAlphaValue
- L135 _public function_ `TFunction<float(float)> GetInputScaleBiasClampCallback(const FExecutionContext& Context) const` — @see IAlphaInputArgs::GetInputScaleBiasClampCallback
- L141 _protected function_ `const IAlphaInputArgs* GetInterface() const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L43 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IAttributeProvider.h` (Public)


#### struct `UE::UAF::IAttributeProvider`  
`struct IAttributeProvider : ITraitInterface`  
_L26-37_
- inherits: `ITraitInterface`
- desc: IAttributeProvider This interface provides access to animation attributes such as root motion
- L28 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IAttributeProvider)`
- L34 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L35 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IAttributeProvider> : FTraitBinding`  
_L43-53_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L46 _public function_ `FOnExtractRootMotionAttribute GetOnExtractRootMotionAttribute(FExecutionContext& Context) const` — @see IAttributeProvider::GetOnExtractRootMotionAttribute
- L52 _protected function_ `const IAttributeProvider* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FTransform, FOnExtractRootMotionAttribute, float , float , bool );` — Root motion attribute sampling may occur during execution (Ex: Conditionally sampling attributes based on active root motion). This signature is used to support that deferred execution, each implementing trait is responsible for ensuring callback lifetimes.
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FTransform, FOnExtractRootMotionAttribute, float , float , bool );` (scope `UE::UAF`) — Root motion attribute sampling may occur during execution (Ex: Conditionally sampling attributes based on active root motion). This signature is used to support that deferred execution, each implementing trait is responsible for ensuring callback lifetimes.

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IBlendStack.h` (Public)


#### struct `UE::UAF::IBlendStack`  
`struct IBlendStack : ITraitInterface`  
_L26-106_
- inherits: `ITraitInterface`
- desc: IBlendStack This interface exposes anything needed to push a new subgraph
- L80 _public typedef_ `typedef FGraphRequest* FGraphRequestPtr;`
- L84 _public prototype_ `virtual int32 PushGraph(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, IBlendStack::FGraphRequest&& GraphRequest) const;` — Pushes a new subgraph along with blend settings defined in GraphRequest. Outputs the in-place created subgraph OutGraphInstance. @return the child index of the new graph, or INDEX_NONE if we could not push a graph
- L88 _public prototype_ `virtual int32 GetActiveGraph(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, IBlendStack::FGraphRequestPtr& OutGraphRequest) const;` — Gets the graph request info from the most recent PushGraph @return the child index of the active graph, or INDEX_NONE if no active graph was found
- L91 _public prototype_ `virtual IBlendStack::FGraphRequestPtr GetGraph(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, int32 InChildIndex) const;` — Gets the graph request for the specified child index
- L95 _public prototype_ `virtual FAnimNextGraphInstance* GetGraphInstance(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, int32 InChildIndex) const;` — Gets the graph instance for the specified child index. Instance's lifetime may not persist after this call, so do not store the returned ptr
- L100 _public prototype_ `virtual int32 GetActiveGraphInstance(FExecutionContext& Context, const TTraitBinding<IBlendStack>& Binding, FAnimNextGraphInstance*& OutGraphInstance) const;` — Gets the graph instance from the most recent PushGraph Note that if a child graph instance was passed, the instance returned will be the same as that of the hosting trait stack @return the child index of the active graph instance, or INDEX_NONE if no active graph instance was found
- L103 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L104 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### enum `UE::UAF::IBlendStack::EBlendMode`  
`enum class EBlendMode : uint8`  
_L30-37_
- L33 _public enumerator_ `Standard` — Uses standard weight based blend
- L36 _public enumerator_ `Inertialization` — Uses inertialization. Requires an inertialization trait somewhere earlier in the graph.

#### enum `UE::UAF::IBlendStack::EGraphRequestType`  
`enum class EGraphRequestType : uint8`  
_L39-46_
- L42 _public enumerator_ `Owned` — Graph is allocated and owned by the blend stack
- L45 _public enumerator_ `Child` — Graph is a child handle in the blend stacks graph instance

#### struct `UE::UAF::IBlendStack::FGraphRequest`  
`struct FGraphRequest`  
_L48-78_
- L56 _public member_ `FAlphaBlendArgs BlendArgs;` — Blend-in duration for this graph request
- L59 _public member_ `TObjectPtr<const UUAFBlendProfile> BlendProfile;` — Optional blend profile for this graph request
- L62 _public member_ `TObjectPtr<const UUAFAnimGraph> AnimationGraph;` — The template graph to use for the new graph instance
- L65 _public member_ `TObjectPtr<const UObject> FactoryObject;` — The object that was used for factory generation of the graph.
- L68 _public member_ `FAnimNextFactoryParams FactoryParams;` — The additional params used for factory generation of the graph.
- L71 _public member_ `FTraitPtr ChildPtr;` — Child ptr when Type == Child
- L74 _public member_ `EBlendMode BlendMode = EBlendMode::Standard;` — The Blend mode to use
- L77 _public member_ `EGraphRequestType Type = EGraphRequestType::Owned;` — What type of request this is

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IBlendStack> : FTraitBinding`  
_L112-147_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L115 _public function_ `int32 PushGraph(FExecutionContext& Context, IBlendStack::FGraphRequest&& GraphRequest) const` — @see IBlendStack::PushGraph
- L121 _public function_ `int32 GetActiveGraph(FExecutionContext& Context, IBlendStack::FGraphRequestPtr& OutGraphRequest) const` — @see IBlendStack::GetActiveGraph
- L128 _public function_ `IBlendStack::FGraphRequestPtr GetGraph(FExecutionContext& Context, int32 InChildIndex) const` — @see IBlendStack::GetGraph
- L134 _public function_ `virtual int32 GetActiveGraphInstance(FExecutionContext& Context, FAnimNextGraphInstance*& OutGraphInstance) const` — @see IBlendStack::GetGraphInstance
- L140 _public function_ `virtual FAnimNextGraphInstance* GetGraphInstance(FExecutionContext& Context, int32 InChildIndex) const` — @see IBlendStack::GetGraphInstance
- L146 _protected function_ `const IBlendStack* GetInterface() const`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IContinuousBlend.h` (Public)


#### struct `UE::UAF::IContinuousBlend`  
`struct IContinuousBlend : ITraitInterface`  
_L22-35_
- inherits: `ITraitInterface`
- desc: IContinuousBlend This interface exposes continuous blend related information. Assuming that each blend source is temporally coherent (Has no snaps or pops in itself). Then, a continuous blend's poses should be temporally coherent from one pose to the next. Hence these poses will have no need for things like smoothing between each other.
- L24 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IContinuousBlend)`
- L32 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L33 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IContinuousBlend> : FTraitBinding`  
_L41-51_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L44 _public function_ `float GetBlendWeight(const FExecutionContext& Context, int32 ChildIndex) const` — @see IContinuousBlend::GetBlendWeight
- L50 _protected function_ `const IContinuousBlend* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IDiscreteBlend.h` (Public)


#### struct `UE::UAF::IDiscreteBlend`  
`struct IDiscreteBlend : ITraitInterface`  
_L22-57_
- inherits: `ITraitInterface`
- desc: IDiscreteBlend This interface exposes discrete blend related information. Discrete blends may snap or pop from one blend source to another, they may be non-continuous.
- L24 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IDiscreteBlend)`
- L34 _public prototype_ `virtual const FAlphaBlend* GetBlendState(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const;` — Returns the blend alpha for the specified child Returns nullptr if the child index is invalid Allows additive traits to query the internal state of the base trait
- L38 _public prototype_ `virtual int32 GetBlendDestinationChildIndex(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding) const;` — Returns the blend destination child index (aka the active child index) Returns INDEX_NONE if no child is active
- L45 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const;` — Called when a blend transition between children occurs OldChildIndex can be INDEX_NONE if there was no previously active child NewChildIndex can be larger than the current number of known children to support a dynamic number of children at runtime When this occurs, the number of children increments by one The number of children never shrinks
- L48 _public prototype_ `virtual void OnBlendInitiated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const;` — Called when the blend for specified child is initiated
- L51 _public prototype_ `virtual void OnBlendTerminated(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const;` — Called when the blend for specified child terminates
- L54 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L55 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IDiscreteBlend> : FTraitBinding`  
_L63-103_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L66 _public function_ `float GetBlendWeight(FExecutionContext& Context, int32 ChildIndex) const` — @see IDiscreteBlend::GetBlendWeight
- L72 _public function_ `const FAlphaBlend* GetBlendState(FExecutionContext& Context, int32 ChildIndex) const` — @see IDiscreteBlend::GetBlendState
- L78 _public function_ `int32 GetBlendDestinationChildIndex(FExecutionContext& Context) const` — @see IDiscreteBlend::GetBlendDestinationChildIndex
- L84 _public function_ `void OnBlendTransition(FExecutionContext& Context, int32 OldChildIndex, int32 NewChildIndex) const` — @see IDiscreteBlend::OnBlendTransition
- L90 _public function_ `void OnBlendInitiated(FExecutionContext& Context, int32 ChildIndex) const` — @see IDiscreteBlend::OnBlendInitiated
- L96 _public function_ `void OnBlendTerminated(FExecutionContext& Context, int32 ChildIndex) const` — @see IDiscreteBlend::OnBlendTerminated
- L102 _protected function_ `const IDiscreteBlend* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IEvaluate.h` (Public)


#### struct `UE::UAF::FEvaluateGraphContext`  
`struct FEvaluateGraphContext`  
_L29-73_
- desc: FEvaluateGraphContext Data required to perform an EvaluateGraph
- L31 _public prototype_ `FEvaluateGraphContext() = delete;`
- L32 _public function_ `FEvaluateGraphContext(FAnimNextGraphInstance& InGraphInstance, const FReferencePose& InRefPose, int32 InGraphLODLevel) : GraphInstance(InGraphInstance) , RefPose(InRefPose) , GraphLODLevel(InGraphLODLevel)`
- L39 _public function_ `FAnimNextGraphInstance& GetGraphInstance() const`
- L40 _public function_ `const FReferencePose& GetRefPose() const`
- L41 _public function_ `int32 GetGraphLODLevel() const`
- L44 _public function_ `UAbstractSkeletonSetBinding* GetSkeletonSetBinding() const` — Only set if the new abstract skeleton runtime is enabled
- L45 _public function_ `FName GetSkeletonSetName() const`
- L46 _public function_ `USkeletalMesh* GetSkeletalMesh() const`
- L49 _protected prototype_ `TWeakObjectPtr<const USkeletalMeshComponent> GetBindingObject() const;`
- L51 _protected function_ `void SetSkeletonSet(UAbstractSkeletonSetBinding* InSkeletonSetBinding, USkeletalMesh* InSkeletalMesh, FName InSkeletonSetName)`
- L58 _protected member_ `FAnimNextGraphInstance& GraphInstance;`
- L60 _protected member_ `const FReferencePose& RefPose;`
- L62 _protected member_ `UAbstractSkeletonSetBinding* SkeletonSetBinding = nullptr;`
- L63 _protected member_ `USkeletalMesh* SkeletalMesh = nullptr;`
- L64 _protected member_ `FName SkeletonSetName;`
- L66 _protected member_ `int32 GraphLODLevel = 0;`

#### struct `UE::UAF::FEvaluateTraversalContext`  
`struct FEvaluateTraversalContext final : FExecutionContext`  
_L80-98_
- inherits: `FExecutionContext`
- desc: FEvaluateTraversalContext Contains all relevant transient data for an evaluate traversal and wraps the execution context.
- L87 _public function_ `template<class TaskType> void AppendTask(TaskType&& Task)` — Appends a new task into the evaluation program, tasks mutate state in the order they have been appended in This means that child nodes need to evaluate first, tasks will usually be appended in IEvaluate::PostEvaluate Tasks are moved into their final memory location, caller can allocate the task anywhere, it is no longer needed after this operation @see FEvaluationProgram, FEvaluationTask, FEvaluationVM
- L90 _public function_ `template<class TaskType> void AppendTaskPtr(const TSharedPtr<TaskType>& TaskPtr)`
- L93 _private prototype_ `explicit FEvaluateTraversalContext(FEvaluationProgram& InEvaluationProgram);`
- L95 _private member_ `FEvaluationProgram& EvaluationProgram;`

#### struct `UE::UAF::IEvaluate`  
`struct IEvaluate : ITraitInterface`  
_L114-128_
- inherits: `ITraitInterface`
- desc: IEvaluate This interface is called during the evaluation traversal. It aims to produce an evaluation program. When a node is visited, PreEvaluate is first called on its top trait. It is responsible for forwarding the call to the next trait that implements this interface on the trait stack of the node. Once all traits have had the chance to PreEvaluate, the children of the trait are queried through the IHierarchy interface. The children will then evaluate and PostEvaluate will then be called afterwards on the original trait. The execution context contains what to evaluate. @see FEvaluationProgram
- L116 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IEvaluate)`
- L122 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const;` — Called after a traits children have been evaluated
- L125 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L126 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IEvaluate> : FTraitBinding`  
_L134-150_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L137 _public function_ `void PreEvaluate(FEvaluateTraversalContext& Context) const` — @see IEvaluate::PreEvaluate
- L143 _public function_ `void PostEvaluate(FEvaluateTraversalContext& Context) const` — @see IEvaluate::PostEvaluate
- L149 _protected function_ `const IEvaluate* GetInterface() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace UAF` (scope `UE`)
- L164 _prototype_ `[[nodiscard]] FEvaluationProgram EvaluateGraph(const FEvaluateGraphContext& EvaluateGraphContext);` (scope `UE::UAF`) — Evaluates a sub-graph starting at its root and produces an evaluation program. Evaluation should be deterministic and repeated calls should yield the same evaluation program. For each node: - We call PreEvaluate on all its traits - We call GetChildren on all its traits - We evaluate all children found - We call PostEvaluate on all its traits @see IEvaluate::PreEvaluate, IEvaluate::PostEvaluate, IHierarchy::GetChildren
- L179 _prototype_ `[[nodiscard]] FEvaluationProgram EvaluateGraph(const FEvaluateGraphContext& EvaluateGraphContext, const FWeakTraitPtr& GraphRootPtr);` (scope `UE::UAF`) — Evaluates a sub-graph starting at its root and produces an evaluation program. Evaluation starts at the top of the stack that includes the graph root trait. Evaluation should be deterministic and repeated calls should yield the same evaluation program. For each node: - We call PreEvaluate on all its traits - We call GetChildren on all its traits - We evaluate all children found - We call PostEvaluate on all its traits @see IEvaluate::PreEvaluate, IEvaluate::PostEvaluate, IHierarchy::GetChildren
- L184 _prototype_ `void EvaluateGraph(const FEvaluateGraphContext& EvaluateGraphContext, FAnimNextGraphLODPose& OutputPose);` (scope `UE::UAF`) — Evaluates a sub-graph starting at its root and produces an output pose
- L187 _prototype_ `bool UseAbstractSkeletonRuntime();` (scope `UE::UAF`) — Returns whether or not we should use the new abstract skeleton runtime

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IGarbageCollection.h` (Public)


#### struct `UE::UAF::IGarbageCollection`  
`struct IGarbageCollection : ITraitInterface`  
_L20-34_
- inherits: `ITraitInterface`
- desc: IGarbageCollection This interface exposes garbage collection reference tracking.
- L22 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IGarbageCollection)`
- L29 _public function_ `virtual bool IsInternal() const override`
- L31 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L32 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IGarbageCollection> : FTraitBinding`  
_L40-50_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L43 _public function_ `void AddReferencedObjects(const FExecutionContext& Context, FReferenceCollector& Collector) const` — @see IGarbageCollection::AddReferencedObjects
- L49 _protected function_ `const IGarbageCollection* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IGraphFactory.h` (Public)


#### struct `UE::UAF::IGraphFactory`  
`struct IGraphFactory : ITraitInterface`  
_L24-44_
- inherits: `ITraitInterface`
- desc: IGraphFactory This interface allows traits to participate in graph building via FAnimGraphFactory
- L26 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IGraphFactory)`
- L36 _public prototype_ `static const UUAFAnimGraph* GetOrBuildGraph(FExecutionContext& Context, const FTraitBinding& Binding, FGraphAssetHandleConstView AssetHandle, FAnimNextFactoryParams& InOutParams);` — If the supplied object is a UUAFAnimGraph, returns it If not then uses the parameters (od the default parameters if they are not valid) combined with the current trait stack's collective calls to GetFactoryParams to build the graph procedurally
- L38 _public prototype_ `static const UUAFAnimGraph* GetOrBuildGraph(FExecutionContext& Context, const FTraitBinding& Binding, const UObject* Asset, FAnimNextFactoryParams& InOutParams);`
- L41 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L42 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IGraphFactory> : FTraitBinding`  
_L50-60_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L53 _public function_ `void GetFactoryParams(FExecutionContext& Context, FGraphAssetHandleConstView AssetHandle, FAnimNextFactoryParams& InOutParams) const` — @see IGraphFactory::GetFactoryParams
- L59 _protected function_ `const IGraphFactory* GetInterface() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IGroupSynchronization.h` (Public)


#### enum `EAnimGroupSynchronizationRole`  
`enum class EAnimGroupSynchronizationRole : uint8`  
_L24-43_
- reflection: `UENUM(BlueprintType)`
- desc: Synchronization Role Timelines part of a named group will synchronize together. To do so, a leader is first identified. The remaining members of the group will be followers. The synchronization role for a member of the group determines which role it can play within that group.
- L27 _public enumerator_ `CanBeLeader` — This timeline host can be the leader, as long as it has a higher blend weight than the previous best leader.
- L30 _public enumerator_ `AlwaysFollower` — This timeline host will always be a follower (unless there are only followers, in which case the first one ticked wins).
- L33 _public enumerator_ `AlwaysLeader` — This timeline host will always be a leader (if more than one timeline host is AlwaysLeader, the last one ticked wins).
- L36 _public enumerator_ `TransitionLeader` — This timeline host will be excluded from the sync group while blending in. Once blended in it will be the sync group leader until blended out
- L39 _public enumerator_ `TransitionFollower` — This timeline host will be excluded from the sync group while blending in. Once blended in it will be a follower until blended out
- L42 _public enumerator_ `ExclusiveAlwaysLeader` — This timeline host will always be a leader. If it fails to be ticked as a leader it will be run as ungrouped (EAnimGroupSynchronizationMode::NoSynchronization) .

#### enum `EAnimGroupSynchronizationMode`  
`enum class EAnimGroupSynchronizationMode : uint8`  
_L63-73_
- reflection: `UENUM(BlueprintType)`
- desc: Synchronization Mode Timelines part of a named group can be synchronized together. When synchronization is enabled, two options are presented: - A user specified group name can be used - A uniquely generated group name can be used Having an explicitly specified group name is useful to synchronize different things together (e.g. two anim sequences). However, sometimes we want certain things to synchronize only within themselves (e.g. blend space). This is called self-synchronization. This arises when we want to specify the synchronization behavior at a higher level than individual timelines. In such cases, we cannot use a user supplied group because every instance would then attempt to use the same group name, which can be problematic. Consider a blend space embedded within a sub-graph that can blend with itself (e.g. is re-entrant). This commonly occurs when blend stacks are used (e.g. through motion matching). We would like the anim sequences within the blend space to self-synchronize but we do not want those to synchronize with other instances of the same blend space. To solve this, every instance of the blend space needs a unique group name.
- L66 _public enumerator_ `NoSynchronization` — This timeline host will not synchronize.
- L69 _public enumerator_ `SynchronizeUsingGroupName` — This timeline host will synchronize and use the provided group name.
- L72 _public enumerator_ `SynchronizeUsingUniqueGroupName` — This timeline host will synchronize and use a uniquely generated group name.

#### struct `UE::UAF::FSyncGroupParameters`  
`struct FSyncGroupParameters`  
_L78-92_
- desc: Encapsulates the parameters that control sync group behavior
- L81 _public member_ `FName GroupName;` — The group name to belong to (if None, syncing is disabled)
- L84 _public member_ `EAnimGroupSynchronizationRole GroupRole = EAnimGroupSynchronizationRole::CanBeLeader;` — The role within the group
- L87 _public member_ `EAnimGroupSynchronizationMode SyncMode = EAnimGroupSynchronizationMode::NoSynchronization;` — The synchronization mode
- L91 _public member_ `bool bMatchSyncPoint = true;` — Whether or not to match the group sync point when joining as leader or follower with markers When disabled, the start position of synced sequences must be properly set to avoid pops

#### struct `UE::UAF::IGroupSynchronization`  
`struct IGroupSynchronization : ITraitInterface`  
_L99-113_
- inherits: `ITraitInterface`
- desc: IGroupSynchronization This interface exposes group synchronization related information and behavior.
- L101 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IGroupSynchronization)`
- L107 _public prototype_ `virtual void AdvanceBy(FExecutionContext& Context, const TTraitBinding<IGroupSynchronization>& Binding, float DeltaTime, bool bDispatchEvents) const;` — Called by the sync group graph instance component to advance time
- L110 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L111 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IGroupSynchronization> : FTraitBinding`  
_L119-135_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L122 _public function_ `FSyncGroupParameters GetGroupParameters(FExecutionContext& Context) const` — @see IGroupSynchronization::GetGroupParameters
- L128 _public function_ `void AdvanceBy(FExecutionContext& Context, float DeltaTime, bool bDispatchEvents) const` — @see IGroupSynchronization::AdvanceBy
- L134 _protected function_ `const IGroupSynchronization* GetInterface() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IHierarchy.h` (Public)


#### struct `UE::UAF::IHierarchy`  
`struct IHierarchy : ITraitInterface`  
_L22-69_
- inherits: `ITraitInterface`
- desc: IHierarchy This interface exposes hierarchy traversal information to navigate the graph.
- L24 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IHierarchy)`
- L32 _public prototype_ `virtual FWeakTraitPtr GetStackForwardingChild(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const;` — Returns the child trait to forward stack forwarding interface requests to Default implementation will return the first child of single child hierarchies, and not forward at all for multi child hierarchies
- L37 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const;` — Appends weak handles to any children we wish to traverse on the trait implementation (not the whole stack). Traits are responsible for allocating and releasing child instance data. Empty handles can be appended.
- L40 _public prototype_ `static void GetStackChildren(const FExecutionContext& Context, const FTraitStackBinding& Binding, FChildrenArray& Children);` — Queries the trait stack and calls GetChildren for each trait, appending the result.
- L43 _public prototype_ `static void GetStackChildren(const FExecutionContext& Context, const FTraitBinding& Binding, FChildrenArray& Children);` — Queries the trait stack of the specified binding and calls GetChildren for each trait, appending the result.
- L46 _public prototype_ `static uint32 GetNumStackChildren(const FExecutionContext& Context, const FTraitStackBinding& Binding);` — Queries the trait stack and calls GetNumChildren for each trait, accumulating the result.
- L49 _public prototype_ `static uint32 GetNumStackChildren(const FExecutionContext& Context, const FTraitBinding& Binding);` — Queries the trait stack of the specified binding and calls GetNumChildren for each trait, accumulating the result.
- L54 _public prototype_ `template<class TraitInterface> static bool GetForwardedStackInterface(const FExecutionContext& Context, const FTraitStackBinding& StackBinding, FTraitStackBinding& OutStackBinding, TTraitBinding<TraitInterface>& OutBinding);` — Queries the trait stack and then its forwarding children for a trait implementing the specified interface. The trait child found implementing the interface is returned
- L59 _public function_ `template<class TraitInterface> static bool GetForwardedStackInterface(const FExecutionContext& Context, const FTraitBinding& Binding, FTraitStackBinding& OutStackBinding, TTraitBinding<TraitInterface>& OutBinding)` — Queries the trait's forwarding children for a trait implementing the specified interface. The first child found implementing the interface is returned
- L66 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L67 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`
- L101 _function_ `inline void IHierarchy::GetStackChildren(const FExecutionContext& Context, const FTraitBinding& Binding, FChildrenArray& Children)`
- L109 _function_ `inline uint32 IHierarchy::GetNumStackChildren(const FExecutionContext& Context, const FTraitBinding& Binding)`
- L114 _function_ `template<class TraitInterface> inline bool IHierarchy::GetForwardedStackInterface(const FExecutionContext& Context, const FTraitStackBinding& StackBinding, FTraitStackBinding& OutStackBinding, TTraitBinding<TraitInterface>& OutBinding)`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IHierarchy> : FTraitBinding`  
_L75-96_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L78 _public function_ `uint32 GetNumChildren(const FExecutionContext& Context) const` — @see IHierarchy::GetNumChildren
- L84 _public function_ `void GetChildren(const FExecutionContext& Context, FChildrenArray& Children) const` — @see IHierarchy::GetChildren
- L89 _public function_ `FWeakTraitPtr GetStackForwardingChild(const FExecutionContext& Context)`
- L95 _protected function_ `const IHierarchy* GetInterface() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L15 _typedef_ `using FChildrenArray = TArray<FWeakTraitPtr, TInlineAllocator<8, TMemStackAllocator<>>>;` (scope `UE::UAF`) — An array of children pointers We reserve a small amount inline and spill on the memstack

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IInertializerBlend.h` (Public)


#### struct `UE::UAF::IInertializerBlend`  
`struct IInertializerBlend : ITraitInterface`  
_L22-33_
- inherits: `ITraitInterface`
- desc: IInertializerBlend This interface exposes inertializing blend related information. Inertialization is a process in which the delta between two blend sources is made to eventually be zero over time. It can be used as a form of blend smoothing. Examples: Storing pose deltas and fading out over time, dead blending.
- L24 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IInertializerBlend)`
- L30 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L31 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IInertializerBlend> : FTraitBinding`  
_L39-49_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L42 _public function_ `float GetBlendTime(FExecutionContext& Context, int32 ChildIndex) const` — @see IInertializerBlend::GetBlendTime
- L48 _protected function_ `const IInertializerBlend* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/INotifySource.h` (Public)


#### struct `UE::UAF::INotifySource`  
`struct INotifySource : ITraitInterface`  
_L20-31_
- inherits: `ITraitInterface`
- desc: INotifySource This interface exposes a source of animation notify events
- L22 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(INotifySource)`
- L28 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L29 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<INotifySource> : FTraitBinding`  
_L37-47_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L40 _public function_ `void GetNotifies(FExecutionContext& Context, float StartPosition, float Duration, bool bLooping, TArray<FAnimNotifyEventReference>& OutNotifies) const` — @see INotifySource::GetNotifies
- L46 _protected function_ `const INotifySource* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IScopedTag.h` (Public)


#### struct `UE::UAF::IScopedTagInterface`  
`struct IScopedTagInterface : IScopedTraitInterface`  
_L12-19_
- inherits: `IScopedTraitInterface`
- L14 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IScopedTagInterface) virtual FName GetTag(const FExecutionContext& Context, const TTraitBinding<IScopedTagInterface>& Binding) const;`
- L18 _public prototype_ `static bool IsTagInScope(const FExecutionContext& Context, FName Tag);`
- L33 _function_ `inline FName IScopedTagInterface::GetTag(const FExecutionContext& Context, const TTraitBinding<IScopedTagInterface>& Binding) const`
- L44 _function_ `inline bool IScopedTagInterface::IsTagInScope(const FExecutionContext& Context, FName Tag)`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IScopedTagInterface> : FTraitBinding`  
_L22-31_
- inherits: `FTraitBinding`
- L24 _public function_ `FName GetTag(const FExecutionContext& Context) const`
- L30 _protected function_ `const IScopedTagInterface* GetInterface() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L49 _function_ `` (scope `UE::UAF::IScopedTagInterface::IsTagInScope`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/ISmoothBlend.h` (Public)


#### struct `UE::UAF::ISmoothBlend`  
`struct ISmoothBlend : ITraitInterface`  
_L23-40_
- inherits: `ITraitInterface`
- desc: ISmoothBlend This interface exposes blend smoothing related information. Blend smoothing is a process that may be needed for discrete blends to make their pose transition appear continuous (IE: smooth).
- L25 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(ISmoothBlend)`
- L31 _public prototype_ `virtual EAlphaBlendOption GetBlendType(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const;` — Returns the desired blend type for the specified child
- L34 _public prototype_ `virtual UCurveFloat* GetCustomBlendCurve(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const;` — Returns the desired blend curve for the specified child
- L37 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L38 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<ISmoothBlend> : FTraitBinding`  
_L46-68_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L49 _public function_ `float GetBlendTime(FExecutionContext& Context, int32 ChildIndex) const` — @see ISmoothBlend::GetBlendTime
- L55 _public function_ `EAlphaBlendOption GetBlendType(FExecutionContext& Context, int32 ChildIndex) const` — @see ISmoothBlend::GetBlendType
- L61 _public function_ `UCurveFloat* GetCustomBlendCurve(FExecutionContext& Context, int32 ChildIndex) const` — @see ISmoothBlend::GetCustomBlendCurve
- L67 _protected function_ `const ISmoothBlend* GetInterface() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/ISmoothBlendPerBone.h` (Public)


#### struct `UE::UAF::ISmoothBlendPerBone`  
`struct ISmoothBlendPerBone : ITraitInterface`  
_L22-33_
- inherits: `ITraitInterface`
- desc: ISmoothBlendPerBone This interface exposes blend smoothing per bone related information.
- L24 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(ISmoothBlendPerBone)`
- L30 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L31 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<ISmoothBlendPerBone> : FTraitBinding`  
_L39-49_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L42 _public function_ `const UUAFBlendProfile* GetBlendProfile(FExecutionContext& Context, int32 ChildIndex) const` — @see ISmoothBlendPerBone::GetBlendProfile
- L48 _protected function_ `const ISmoothBlendPerBone* GetInterface() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/ITimeline.h` (Public)


#### struct `UE::UAF::FTimelineSyncMarker`  
`struct FTimelineSyncMarker`  
_L16-40_
- L19 _public prototype_ `FTimelineSyncMarker() = default;` — Default construct empty
- L22 _public function_ `FTimelineSyncMarker(FName InName, float InPosition) : Name(InName) , Position(InPosition)` — Construct with a specific sync marker name and position
- L29 _public function_ `FName GetName() const` — Returns the sync marker name
- L32 _public function_ `float GetPosition() const` — Returns the sync marker position (in seconds) on the timeline between [0.0, TimelineDuration]
- L36 _private member_ `FName Name;` — The sync marker name
- L39 _private member_ `float Position = 0.0f;` — The sync marker position

#### struct `UE::UAF::FTimelineState`  
`struct FTimelineState`  
_L51-187_
- desc: Timeline State Encapsulates the state of a timeline.
- L54 _public prototype_ `FTimelineState() = default;` — Default construct with no state
- L57 _public function_ `FTimelineState(float InPosition, float InDuration, float InPlayRate, bool bInIsLooping) : Position(InPosition) , Duration(InDuration) , PlayRate(InPlayRate) , bIsLooping(bInIsLooping)` — Construct with a specific state
- L66 _public function_ `void Reset()` — Resets the timeline state to its default state
- L79 _public function_ `FName GetDebugName() const` — Returns the timeline name
- L89 _public function_ `float GetPosition() const` — Returns the timeline position in seconds
- L93 _public function_ `float GetPositionRatio() const` — Returns the timeline position as a ratio (0.0 = start of timeline, 1.0 = end of timeline) For infinite timelines, this will return infinity
- L104 _public function_ `float GetTimeLeft() const` — Returns the time left to play in the timeline For infinite timelines this will return infinity
- L115 _public function_ `float GetDuration() const` — Returns the timeline duration in seconds For infinite timelines this will return infinity
- L118 _public function_ `float GetPlayRate() const` — Returns the play rate of the timeline
- L121 _public function_ `bool IsLooping() const` — Returns whether or not the timeline is looping
- L124 _public function_ `bool IsFinite() const` — Returns whether or not this timeline is finite
- L127 _public function_ `[[nodiscard]] FTimelineState WithDebugName(FName InDebugName) const` — Creates a new instance of the timeline state with the supplied debug name
- L139 _public function_ `[[nodiscard]] FTimelineState WithPosition(float InPosition) const` — Creates a new instance of the timeline state with the supplied position
- L147 _public function_ `[[nodiscard]] FTimelineState WithDuration(float InDuration) const` — Creates a new instance of the timeline state with the supplied duration
- L155 _public function_ `[[nodiscard]] FTimelineState WithPlayRate(float InPlayRate) const` — Creates a new instance of the timeline state with the supplied play rate
- L163 _public function_ `[[nodiscard]] FTimelineState AsLooping(bool InAsLooping = true) const` — Creates a new instance of the timeline state with the supplied looping flag
- L173 _private member_ `FName DebugName;` — A debug name associated with this timeline
- L177 _private member_ `float Position = 0.0f;` — Timeline position in seconds
- L180 _private member_ `float Duration = 0.0f;` — Timeline duration in seconds
- L183 _private member_ `float PlayRate = 0.0f;` — Timeline play rate
- L186 _private member_ `bool bIsLooping = false;` — Timeline looping status

#### struct `UE::UAF::FTimelineDelta`  
`struct FTimelineDelta`  
_L194-218_
- desc: Timeline Delta Encapsulates the delta state of a timeline, i.e. the changes that occured during the last AdvanceBy call.
- L197 _public prototype_ `FTimelineDelta() = default;` — Default construct with no delta
- L200 _public function_ `FTimelineDelta(float InDeltaTime, ETypeAdvanceAnim InAdvanceType) : DeltaTime(InDeltaTime) , AdvanceType(InAdvanceType)` — Construct with a specific delta
- L207 _public function_ `float GetDeltaTime() const` — Returns the delta time in seconds when last advanced
- L210 _public function_ `ETypeAdvanceAnim GetAdvanceType() const` — Returns the result of the last advance
- L214 _private member_ `float DeltaTime = 0.0f;` — Delta time in seconds when last advanced
- L217 _private member_ `ETypeAdvanceAnim AdvanceType = ETAA_Default;` — The result of the last advance

#### struct `UE::UAF::ITimeline`  
`struct ITimeline : ITraitInterface`  
_L225-246_
- inherits: `ITraitInterface`
- desc: ITimeline This interface exposes timeline related information.
- L227 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(ITimeline)`
- L235 _public prototype_ `virtual bool GetState(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineState& OutTimelineState) const;` — Returns the state of this timeline It is possible for the timeline to be in an 'unknown' state if this is called before supporting data is copied/read, in which case this function will return false and the state will not be filled
- L240 _public prototype_ `virtual bool GetDelta(const FExecutionContext& Context, const TTraitBinding<ITimeline>& Binding, FTimelineDelta& OutTimelineDelta) const;` — Returns the last change in state of this timeline It is possible for the timeline to be in an 'unknown' state if this is called before supporting data is copied/read, in which case this function will return false and the delta will not be filled
- L243 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L244 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<ITimeline> : FTraitBinding`  
_L252-274_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L255 _public function_ `void GetSyncMarkers(const FExecutionContext& Context, FTimelineSyncMarkerArray& OutSyncMarkers) const` — @see ITimeline::GetSyncMarkers
- L261 _public function_ `bool GetState(const FExecutionContext& Context, FTimelineState& OutTimelineState) const` — @see ITimeline::GetState
- L267 _public function_ `bool GetDelta(const FExecutionContext& Context, FTimelineDelta& OutTimelineDelta) const` — @see ITimeline::GetDelta
- L273 _protected function_ `const ITimeline* GetInterface() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L44 _typedef_ `using FTimelineSyncMarkerArray = TArray<FTimelineSyncMarker, TInlineAllocator<8, TMemStackAllocator<>>>;` (scope `UE::UAF`) — An array of sync markers We reserve a small amount inline and spill on the memstack

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/ITimelinePlayer.h` (Public)


#### struct `UE::UAF::ITimelinePlayer`  
`struct ITimelinePlayer : ITraitInterface`  
_L18-29_
- inherits: `ITraitInterface`
- desc: ITimelinePlayer This interface exposes timeline playing behavior.
- L20 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(ITimelinePlayer)`
- L26 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L27 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<ITimelinePlayer> : FTraitBinding`  
_L35-45_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L38 _public function_ `void AdvanceBy(FExecutionContext& Context, float DeltaTime, bool bDispatchEvents) const` — @see ITimelinePlayer::AdvanceBy
- L44 _protected function_ `const ITimelinePlayer* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/TraitInterfaces/IUpdate.h` (Public)


#### struct `UE::UAF::FUpdateGraphContext`  
`struct FUpdateGraphContext`  
_L38-72_
- desc: FUpdateGraphContext Data required to perform an UpdateGraph
- L40 _public prototype_ `FUpdateGraphContext() = delete;`
- L41 _public function_ `FUpdateGraphContext(FAnimNextGraphInstance& InGraphInstance, float InDeltaTime) : GraphInstance(InGraphInstance) , DeltaTime(InDeltaTime)`
- L47 _public function_ `void PushInputEvent(FAnimNextTraitEventPtr Event)`
- L49 _public function_ `const FAnimNextGraphInstance& GetGraphInstance() const`
- L50 _public function_ `FAnimNextGraphInstance& GetGraphInstance()`
- L52 _public function_ `const FTraitEventList& GetInputEventList() const`
- L53 _public function_ `FTraitEventList& GetInputEventList()`
- L55 _public function_ `const FTraitEventList& GetOutputEventList() const`
- L56 _public function_ `FTraitEventList& GetOutputEventList()`
- L58 _public function_ `float GetDeltaTime() const`
- L61 _protected prototype_ `TWeakObjectPtr<const USkeletalMeshComponent> GetBindingObject() const;`
- L63 _protected member_ `FAnimNextGraphInstance& GraphInstance;`
- L64 _protected member_ `FTraitEventList InputEventList;`
- L65 _protected member_ `FTraitEventList OutputEventList;`
- L66 _protected member_ `float DeltaTime = 0.f;`

#### struct `UE::UAF::FTraitUpdateState`  
`struct alignas(16) FTraitUpdateState final`  
_L81-167_
- desc: FTraitUpdateState State that propagates down the graph during the update traversal. We align this to 16 bytes and maintain that same size to ensure efficient copying.
- L83 _public prototype_ `FTraitUpdateState() = default;`
- L85 _public function_ `explicit FTraitUpdateState(float InDeltaTime) : DeltaTime(InDeltaTime)`
- L90 _public function_ `float GetDeltaTime() const` — Returns the delta time for this trait
- L93 _public function_ `float GetTotalWeight() const` — Returns the total weight for this trait
- L96 _public function_ `float GetTotalTrajectoryWeight() const` — Returns the total trajectory weight for this trait
- L99 _public function_ `bool IsBlendingOut() const` — Returns whether or not this trait is blending out
- L102 _public function_ `bool IsNewlyRelevant() const` — Returns whether or not this trait is newly relevant
- L105 _public function_ `[[nodiscard]] FTraitUpdateState WithWeight(float Weight) const` — Creates a new instance of the update state with the total weight scaled by the supplied weight
- L113 _public function_ `[[nodiscard]] FTraitUpdateState WithTrajectoryWeight(float Weight) const` — Creates a new instance of the update state with the total trajectory weight scaled by the supplied weight
- L121 _public function_ `[[nodiscard]] FTraitUpdateState WithTimeScale(float TimeScale) const` — Creates a new instance of the update state with the delta time scaled by the supplied scale factor
- L129 _public function_ `[[nodiscard]] FTraitUpdateState WithDeltaTime(float InDeltaTime) const` — Creates a new instance of the update state with the specified delta time
- L137 _public function_ `[[nodiscard]] FTraitUpdateState AsBlendingOut(bool InIsBlendingOut = true) const` — Creates a new instance of the update state marking it as blending out
- L145 _public function_ `[[nodiscard]] FTraitUpdateState AsNewlyRelevant(bool InIsNewlyRelevant = true) const` — Creates a new instance of the update state marking it as newly relevant
- L154 _private member_ `float DeltaTime = 0.0f;` — The amount of time to move forward by at allowing parents to time scale their children
- L157 _private member_ `float TotalWeight = 1.0f;` — The current total weight factoring in all inherited blend weights
- L160 _private member_ `float TotalTrajectoryWeight = 1.0f;` — The current total trajectory weight factoring in all inherited blend weights
- L163 _private member_ `int8 bIsBlendingOut = false;` — Whether or not we are blending out
- L166 _private member_ `int8 bIsNewlyRelevant = false;` — Whether or not we newly became relevant

#### struct `UE::UAF::FUpdateTraversalContext`  
`struct FUpdateTraversalContext final : FExecutionContext`  
_L176-244_
- inherits: `FExecutionContext`
- desc: FUpdateTraversalContext Contains all relevant transient data for an update traversal and wraps the execution context.
- L181 _public prototype_ `virtual void RaiseInputTraitEvent(FAnimNextTraitEventPtr Event) override;` — Raises an input trait event The raised event will be seen by every child of the currently updating trait stack Input trait events can only be raised during PreUpdate
- L185 _public prototype_ `virtual void RaiseOutputTraitEvent(FAnimNextTraitEventPtr Event) override;` — Raises an output trait event The raised event will be seen by every parent of the currently updating trait stack
- L189 _private prototype_ `FUpdateTraversalContext() = default;` — Constructs a new traversal context
- L192 _private prototype_ `void PushQueuedUpdateEntries(FUpdateTraversalQueue& TraversalQueue, Private::FUpdateEntry* ParentEntry);` — Pops entries from the traversal queue and pushes them onto the update stack
- L195 _private prototype_ `void PushUpdateEntry(Private::FUpdateEntry* Entry);` — Pushes an entry onto the update stack
- L198 _private prototype_ `Private::FUpdateEntry* PopUpdateEntry();` — Pops an entry from the top of the update stack
- L201 _private prototype_ `void PushFreeEntry(Private::FUpdateEntry* Entry);` — Pushes an entry onto the free entry stack
- L205 _private prototype_ `Private::FUpdateEntry* GetNewEntry(const FWeakTraitPtr& TraitPtr, const FTraitUpdateState& TraitState);` — Returns a new entry suitable for update queuing If an entry isn't found in the free stack, a new one is allocated from the memstack
- L209 _private prototype_ `Private::FUpdateEventBookkeepingEntry* GetNewBookkeepingEntry(Private::FUpdateEventBookkeepingAction Action, FAnimNextTraitEventPtr Event);` — Returns a new bookkeeping entry suitable for queuing If an entry isn't found in the free stack, a new one is allocated from the memstack
- L212 _private prototype_ `void PushFreeBookkeepingEntry(Private::FUpdateEventBookkeepingEntry* Entry);` — Pushes a bookkeeping entry onto the free bookkeeping entry stack
- L215 _private prototype_ `void ExecuteBookkeepingActions(Private::FUpdateEventBookkeepingList& BookkeepingList);` — Executes the event bookkeeping actions and clears the bookkeeping list
- L218 _private member_ `UE::UAF::FTraitEventList* InputEventList = nullptr;` — The input and output event lists
- L219 _private member_ `UE::UAF::FTraitEventList* OutputEventList = nullptr;`
- L222 _private member_ `Private::FUpdateEntry* ExecutingEntry = nullptr;` — The currently executing entry
- L227 _private member_ `Private::FUpdateEntry* UpdateStackHead = nullptr;` — The head pointer of the update stack This is the traversal execution stack and it contains entries that are pending their pre-update call and entries waiting for post-update to be called
- L232 _private member_ `Private::FUpdateEntry* FreeEntryStackHead = nullptr;` — The head pointer of the free entry stack Entries are allocated from the memstack and are re-used in LIFO since they'll be warmer in the CPU cache
- L237 _private member_ `Private::FUpdateEventBookkeepingEntry* FreeBookkeepingEntryStackHead = nullptr;` — The head pointer of the free bookkeeping entry stack Entries are allocated from the memstack and are re-used in LIFO since they'll be warmer in the CPU cache
- L240 _private member_ `Private::FUpdateEventBookkeepingList* RootParentBookkeepingEntryList = nullptr;` — The root node doesn't have a parent but we need a bookkeeping list regardless

#### struct `UE::UAF::FUpdateTraversalQueue`  
`struct FUpdateTraversalQueue final`  
_L252-272_
- desc: FUpdateTraversalQueue A queue of children to traverse. @see IUpdateTraversal::QueueChildrenForTraversal
- L256 _public prototype_ `void Push(const FWeakTraitPtr& ChildPtr, const FTraitUpdateState& ChildTraitState);` — Queued a child for traversal Children are processed in the same order they are queued
- L259 _private prototype_ `explicit FUpdateTraversalQueue(FUpdateTraversalContext& InTraversalContext);`
- L262 _private member_ `FUpdateTraversalContext& TraversalContext;` — The current traversal context
- L268 _private member_ `Private::FUpdateEntry* QueuedUpdateStackHead = nullptr;` — The head pointer of the queued update stack When a child is queued for traversal, it is first appended to this stack Once all children have been queued and pre-update terminates, this stack is emptied and pushed onto the update stack

#### struct `UE::UAF::IUpdate`  
`struct IUpdate : ITraitInterface`  
_L284-301_
- inherits: `ITraitInterface`
- desc: IUpdate This interface is called during the update traversal. When a node is visited, PreUpdate is first called on its top trait. It is responsible for forwarding the call to the next trait that implements this interface on the trait stack of the node. Once all traits have had the chance to PreUpdate, the children will then evaluate and PostUpdate will then be called afterwards on the original trait.
- L286 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IUpdate)`
- L292 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const;` — Called before a traits children are updated
- L295 _public prototype_ `virtual void PostUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const;` — Called after a traits children have been updated
- L298 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L299 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::IUpdateTraversal`  
`struct IUpdateTraversal : ITraitInterface`  
_L315-326_
- inherits: `ITraitInterface`
- desc: IUpdateTraversal This interface is called during the update traversal. If a trait needs to modify the update state of its children, it needs to implement this interface. There is no need to call the Super to forward the call down the trait stack as the update traversal takes care of it. If this interface is not implemented, the IHierarchy interface will be used to retrieve and queue the children with the same update state as the owning trait.
- L317 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IUpdateTraversal)`
- L323 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L324 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IUpdate> : FTraitBinding`  
_L332-354_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L335 _public function_ `void OnBecomeRelevant(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState) const` — @see IUpdate::OnBecomeRelevant
- L341 _public function_ `void PreUpdate(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState) const` — @see IUpdate::PreUpdate
- L347 _public function_ `void PostUpdate(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState) const` — @see IUpdate::PostUpdate
- L353 _protected function_ `const IUpdate* GetInterface() const`
- L363 _public function_ `void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const` — @see IUpdateTraversal::QueueChildrenForTraversal
- L369 _protected function_ `const IUpdateTraversal* GetInterface() const`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IUpdateTraversal> : FTraitBinding`  
_L360-370_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L335 _public function_ `void OnBecomeRelevant(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState) const` — @see IUpdate::OnBecomeRelevant
- L341 _public function_ `void PreUpdate(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState) const` — @see IUpdate::PreUpdate
- L347 _public function_ `void PostUpdate(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState) const` — @see IUpdate::PostUpdate
- L353 _protected function_ `const IUpdate* GetInterface() const`
- L363 _public function_ `void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const` — @see IUpdateTraversal::QueueChildrenForTraversal
- L369 _protected function_ `const IUpdateTraversal* GetInterface() const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UAFANIMGRAPH_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::UAF`)
- L384 _prototype_ `void UpdateGraph(FUpdateGraphContext& UpdateGraphContext);` (scope `UE::UAF`) — Updates a sub-graph starting at its root. For each node: - We call PreUpdate on all its traits - We update all children - We call PostUpdate on all its traits During our update, we can append new input/output events. @see IUpdate::PreUpdate, IUpdate::PostUpdate, IHierarchy::GetChildren

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/ApplyAdditivePerBoneTraitData.h` (Public)


#### struct `UE::UAF::FApplyAdditivePerBoneTraitSharedData`  
`struct FApplyAdditivePerBoneTraitSharedData : public FAnimNextTraitSharedData`  
_L17-49_
- reflection: `USTRUCT(meta = (DisplayName = "Apply Additive Per Bone", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can apply a mesh or local space additive with an additional mask.
- L23 _public member_ `FAnimNextTraitHandle Base;` — `UPROPERTY()` — Base to apply additive to.
- L27 _public member_ `FAnimNextTraitHandle Additive;` — `UPROPERTY()` — Additive to apply.
- L31 _public member_ `TObjectPtr<UUAFBlendMask> BlendMask = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Blend mask asset
- L35 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Default")` — How much to apply of the additive
- L39 _public member_ `bool bMeshSpaceBlend = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Whether to apply in mesh or local space

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L42 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/ApplyAdditiveTraitData.h` (Public)


#### struct `FAnimNextApplyAdditiveTraitSharedData`  
`struct FAnimNextApplyAdditiveTraitSharedData : public FAnimNextTraitSharedData`  
_L16-43_
- reflection: `USTRUCT(meta = (DisplayName = "Apply Additive", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can apply a mesh or local space additive to this trait stack. Ex: LookAt's, minor hit reactions, up-down floating, etc.
- L22 _public member_ `FAnimNextTraitHandle Base;` — `UPROPERTY()` — Base to apply additive too.
- L26 _public member_ `FAnimNextTraitHandle Additive;` — `UPROPERTY()` — Additive to apply.
- L35 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Deprecated. Please add an IAlphaInputArgs additive trait to set alpha. @TODO: Remove pre 5.6 once removing latents doesn't cause crash How much to apply our additive, default is 1.

#### Free symbols / members of external scopes

- L38 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/ApplyNamedSetTraitData.h` (Public)


#### struct `UE::UAF::FApplyNamedSetSharedData`  
`struct FApplyNamedSetSharedData : public FAnimNextTraitSharedData`  
_L21-38_
- reflection: `USTRUCT(meta = (DisplayName = "Apply Named Set", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that applies a new named set to evaluate with. Traits upstream will use the new named set to evaluate. The trait that consumes its output must handle mismatched named sets (e.g. layering).
- L27 _public member_ `FAnimNextTraitHandle Input;` — `UPROPERTY()` — Input to evaluate with the specified set name
- L31 _public member_ `FName SetName = NAME_None;` — `UPROPERTY(Category=Settings, EditAnywhere)` — Named set to evaluate our children with

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L33 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/BlendLayerTraitData.h` (Public)


#### struct `FUAFBlendLayerTraitSharedData`  
`struct FUAFBlendLayerTraitSharedData : public FAnimNextTraitSharedData`  
_L15-49_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Layer", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can blend a layer into an input.
- L20 _public member_ `FAnimNextTraitHandle ChildBase;` — `UPROPERTY()`
- L23 _public member_ `FAnimNextTraitHandle ChildBlend;` — `UPROPERTY()`
- L27 _public member_ `float BlendWeight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Default")` — The strength with which to apply the blend pose
- L31 _public member_ `TObjectPtr<UUAFBlendMask> BlendMask = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))` — Blend mask that configures what bones are included in the blend.
- L35 _public member_ `bool bBlendInMeshSpace = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Whether or not to blend in mesh space or local space
- L39 _public member_ `bool bAlwaysUpdateChildBlend = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — If true, this will still update the child branch even if the blend weight is 0

#### Free symbols / members of external scopes

- L41 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/BlendSmoother.h` (Public)


#### struct `FAnimNextBlendSmootherCoreTraitSharedData`  
`struct FAnimNextBlendSmootherCoreTraitSharedData : public FAnimNextTraitSharedData`  
_L23-28_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Smoother Core", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that smoothly blends between discrete states over time. It only implements the smoothing logic, it queries its required arguments using the ISmoothBlend interface.

#### struct `FAnimNextBlendSmootherTraitSharedData`  
`struct FAnimNextBlendSmootherTraitSharedData : public FAnimNextBlendSmootherCoreTraitSharedData`  
_L41-56_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Smoother"))`
- inherits: `FAnimNextBlendSmootherCoreTraitSharedData`
- desc: A trait that smoothly blends between discrete states over time. This trait implements both the logic and contains the arguments necessary.
- L47 _public member_ `TArray<float> BlendTimes;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))` — How long to take when blending into each child.
- L51 _public member_ `EAlphaBlendOption BlendType = UE::Anim::DefaultBlendOption;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))` — What type of blend equation to use when converting the time elapsed into a blend weight.
- L55 _public member_ `TObjectPtr<UCurveFloat> CustomBlendCurve;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (Inline))` — Custom curve to use when the Custom blend type is used.

#### struct `UE::UAF::FBlendSmootherCoreTrait`  
`struct FBlendSmootherCoreTrait : FAdditiveTrait, IEvaluate, IUpdate, IDiscreteBlend`  
_L66-108_
- inherits: `FAdditiveTrait,IEvaluate,IUpdate,IDiscreteBlend`
- desc: FBlendSmootherCoreTrait A trait that smoothly blends between discrete states over time. It only implements the smoothing logic, it queries its required arguments using the ISmoothBlend interface.
- L70 _public typedef_ `using FSharedData = FAnimNextBlendSmootherCoreTraitSharedData;`
- L92 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L95 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L98 _public prototype_ `virtual float GetBlendWeight(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;` — IDiscreteBlend impl
- L99 _public prototype_ `virtual const FAlphaBlend* GetBlendState(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 ChildIndex) const override;`
- L100 _public prototype_ `virtual void OnBlendTransition(FExecutionContext& Context, const TTraitBinding<IDiscreteBlend>& Binding, int32 OldChildIndex, int32 NewChildIndex) const override;`
- L103 _public prototype_ `static void InitializeInstanceData(FExecutionContext& Context, const FTraitBinding& Binding, const FSharedData* SharedData, FInstanceData* InstanceData);` — Internal impl
- L106 _public function_ `virtual bool IsHidden() const override`

#### struct `UE::UAF::FBlendSmootherCoreTrait::FBlendData`  
`struct FBlendData`  
_L73-83_
- desc: Struct for tracking blends for each pose
- L76 _public member_ `FAlphaBlend Blend;` — Helper struct to update a time based weight
- L79 _public member_ `float Weight = 0.0f;` — Current child weight (normalized with all children)
- L82 _public member_ `bool bIsBlending = false;` — Whether or not this child is actively blending

#### struct `UE::UAF::FBlendSmootherCoreTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L85-89_
- inherits: `FTrait::FInstanceData`
- L88 _public member_ `TArray<FBlendData> PerChildBlendData;` — Blend state per child

#### struct `UE::UAF::FBlendSmootherTrait`  
`struct FBlendSmootherTrait : FBlendSmootherCoreTrait, ISmoothBlend`  
_L116-130_
- inherits: `FBlendSmootherCoreTrait,ISmoothBlend`
- desc: FBlendSmootherTrait A trait that smoothly blends between discrete states over time. This trait implements both the logic and contains the arguments necessary.
- L120 _public typedef_ `using FSharedData = FAnimNextBlendSmootherTraitSharedData;`
- L123 _public prototype_ `virtual float GetBlendTime(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;` — ISmoothBlend impl
- L124 _public prototype_ `virtual EAlphaBlendOption GetBlendType(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;`
- L125 _public prototype_ `virtual UCurveFloat* GetCustomBlendCurve(FExecutionContext& Context, const TTraitBinding<ISmoothBlend>& Binding, int32 ChildIndex) const override;`
- L128 _public function_ `virtual bool IsHidden() const override` — override the base, as it is hidden

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace UAF` (scope `UE`)
- L33 _typedef_ `using FBlendSmootherCoreData = FAnimNextBlendSmootherCoreTraitSharedData;` (scope `UE::UAF`) — Namespaced alias
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/BlendSmootherPerBoneTraitData.h` (Public)


#### struct `FAnimNextBlendSmootherPerBoneCoreTraitSharedData`  
`struct FAnimNextBlendSmootherPerBoneCoreTraitSharedData : public FAnimNextTraitSharedData`  
_L12-15_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Smoother Per Bone Core", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: An additive trait that smoothly blends with per-bone weights.

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/BlendSpacePlayerTraitData.h` (Public)


#### struct `FAnimNextBlendSpacePlayerTraitSharedData`  
`struct FAnimNextBlendSpacePlayerTraitSharedData : public FAnimNextTraitSharedData`  
_L15-54_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Space Player", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can play a blend space
- L21 _public member_ `TObjectPtr<const UBlendSpace> BlendSpace;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Player", meta = (ExportAsReference = "true", FactorySource))` — The blend space to play.
- L25 _public member_ `float XAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Player", DisplayName="X")` — The location on the x-axis to sample.
- L29 _public member_ `float YAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Player", DisplayName="Y")` — The location on the y-axis to sample.
- L33 _public member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Player")` — The play rate multiplier at which this blend space plays.
- L37 _public member_ `float StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Player")` — The time at which we should start playing this blend space. This is normalized in the [0,1] range.
- L41 _public member_ `UE::UAF::EAnimAssetLoopMode LoopMode = UE::UAF::EAnimAssetLoopMode::Auto;` — `UPROPERTY(EditAnywhere, Category = "Blend Space Player")` — Whether to use the asset's default looping behavior or force an override.

#### Free symbols / members of external scopes

- L44 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L56 _namespace_ `namespace UE`
- L56 _namespace_ `namespace UAF` (scope `UE`)
- L59 _typedef_ `using FBlendSpacePlayerData = FAnimNextBlendSpacePlayerTraitSharedData;` (scope `UE::UAF`) — Namespaced alias

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/BlendTwoWayTraitData.h` (Public)


#### struct `FAnimNextBlendTwoWayTraitSharedData`  
`struct FAnimNextBlendTwoWayTraitSharedData : public FAnimNextTraitSharedData`  
_L13-45_
- reflection: `USTRUCT(meta = (DisplayName = "Blend Two Way", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can blend two inputs.
- L19 _public member_ `FAnimNextTraitHandle ChildA;` — `UPROPERTY()` — First output to be blended (full weight is 0.0).
- L23 _public member_ `FAnimNextTraitHandle ChildB;` — `UPROPERTY()` — Second output to be blended (full weight is 1.0).
- L27 _public member_ `float BlendWeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Default")` — How much to blend our two children: 0.0 is fully child A while 1.0 is fully child B.
- L31 _public member_ `bool bResetChildOnActivation = true;` — `UPROPERTY(EditAnywhere, Category = "Default")` — This reinitializes child when re-activated
- L35 _public member_ `bool bAlwaysUpdateChildren = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Always update children, regardless of whether or not that child has weight.

#### Free symbols / members of external scopes

- L38 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/BoneMapping.h` (Public)


#### struct `FAnimNextBoneMapping`  
`struct FAnimNextBoneMapping`  
_L10-21_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `FName SourceBone;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Bone to map from
- L20 _public member_ `FName TargetBone;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Bone to map to

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/Inertialization.h` (Public)


#### struct `UE::UAF::FInertializationRequest`  
`struct FInertializationRequest`  
_L20-24_
- desc: FInertializationRequest Data contained in an InertializationRequest
- L23 _public member_ `float BlendTime = 0.0f;` — Request Blend Time

#### struct `UE::UAF::FDeadBlendingState`  
`struct FDeadBlendingState`  
_L31-65_
- desc: FDeadBlendingState State data required by the DeadBlending node when extrapolating the pose.
- L33 _public function_ `inline void Empty()`
- L45 _public function_ `inline void SetNumUninitialized(const int32 NewBoneNum)`
- L57 _public member_ `TArray<FQuat4f> BoneRotationDirections;`
- L58 _public member_ `FTransformArraySoAHeap SourcePose;`
- L59 _public member_ `TArray<FVector3f> SourceBoneTranslationVelocities;`
- L60 _public member_ `TArray<FVector3f> SourceBoneRotationVelocities;`
- L61 _public member_ `TArray<FVector3f> SourceBoneScaleVelocities;`
- L62 _public member_ `TArray<FVector3f> SourceBoneTranslationDecayHalfLives;`
- L63 _public member_ `TArray<FVector3f> SourceBoneRotationDecayHalfLives;`
- L64 _public member_ `TArray<FVector3f> SourceBoneScaleDecayHalfLives;`

#### struct `FAnimNextInertializationRequestEvent`  
`struct FAnimNextInertializationRequestEvent : public FAnimNextTraitEvent`  
_L74-80_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitEvent`
- desc: FAnimNextInertializationRequestEvent Inertialization Request Event Object
- L77 _public prototype_ `DECLARE_ANIM_TRAIT_EVENT(FAnimNextInertializationRequestEvent, FAnimNextTraitEvent) UE::UAF::FInertializationRequest Request;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/InlineSubGraphTraitData.h` (Public)


#### struct `FUAFInlineSubGraphInputBinding`  
`struct FUAFInlineSubGraphInputBinding`  
_L19-33_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: A single binding that connects a child node in this graph to a Value Bundle variable on the inner sub-graph's interface.
- L25 _public member_ `FAnimNextTraitHandle Input;` — `UPROPERTY(EditAnywhere, Category = "Sub Graph")` — A child node in this graph whose output is passed into the inner sub-graph.
- L32 _public member_ `FAnimNextVariableReference Variable;` — `UPROPERTY(EditAnywhere, Category = "Sub Graph", meta = (HideSubPins, AllowedType = FUAFValueBundle))` — The Value Bundle variable on the inner sub-graph that receives the value from Input. Must match a variable declared on the inner sub-graph asset.

#### struct `FUAFInlineSubGraphTraitSharedData`  
`struct FUAFInlineSubGraphTraitSharedData : public FAnimNextTraitSharedData`  
_L46-73_
- reflection: `USTRUCT(meta = (DisplayName = "Inline Sub Graph", ShowTooltip = true))`
- inherits: `FAnimNextTraitSharedData`
- desc: Hosts an inner sub-graph and exposes a set of child nodes from this graph as typed FUAFValueBundle inputs on the inner sub-graph's interface. Each entry in Inputs maps a child node in this graph to a Value Bundle variable declared on the inner sub-graph. When the inner sub-graph becomes active those values are bound once and remain constant for the lifetime of that graph instance. The inner sub-graph can be swapped at runtime via the Graph pin - blending between instances is supported.
- L52 _public member_ `TObjectPtr<const UUAFAnimGraph> Graph;` — `UPROPERTY(EditAnywhere, Category = "Sub Graph", meta = (ExportAsReference = "true"))` — The inner sub-graph asset to host.
- L56 _public member_ `FAnimNextTraitHandle ReferencePoseChild;` — `UPROPERTY(meta = (Hidden))` — Hidden reference pose fallback child, auto-populated during graph compilation.
- L64 _public member_ `TArray<FUAFInlineSubGraphInputBinding> Inputs;` — `UPROPERTY(EditAnywhere, Category = "Sub Graph", meta = (OnBecomeRelevant))` — Connections from child nodes in this graph to Value Bundle variables on the inner sub-graph's interface. The inner sub-graph must declare each referenced variable with type FUAFValueBundle.

#### Free symbols / members of external scopes

- L67 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/MakeDynamicAdditiveTraitData.h` (Public)


#### struct `UE::UAF::FMakeDynamicAdditiveTraitSharedData`  
`struct FMakeDynamicAdditiveTraitSharedData : public FAnimNextTraitSharedData`  
_L15-37_
- reflection: `USTRUCT(meta = (DisplayName = "Make Dynamic Additive", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that creates a dynamic additive based input poses
- L21 _public member_ `FAnimNextTraitHandle Base;` — `UPROPERTY()` — Reference pose for additive delta calculation
- L25 _public member_ `FAnimNextTraitHandle Additive;` — `UPROPERTY()` — Pose to make additive
- L29 _public member_ `bool bMeshSpaceAdditive = false;` — `UPROPERTY(EditAnywhere, Category="Default")` — Do additive delta calculation in mesh space

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L32 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/NotifyDispatcherTraitData.h` (Public)


#### struct `FAnimNextNotifyDispatcherTraitSharedData`  
`struct FAnimNextNotifyDispatcherTraitSharedData : public FAnimNextTraitSharedData`  
_L12-21_
- reflection: `USTRUCT(meta = (DisplayName = "Notify Dispatcher", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that dispatches notifies according to a timeline advancing

#### Free symbols / members of external scopes

- L17 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro)` — Latent pin support boilerplate
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L26 _typedef_ `using FNotifyDispatcherData = FAnimNextNotifyDispatcherTraitSharedData;` (scope `UE::UAF`) — Namespaced alias

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/PassthroughBlendTrait.h` (Public)


#### struct `FPassthroughBlendTraitSharedData`  
`struct FPassthroughBlendTraitSharedData : public FAnimNextTraitSharedData`  
_L34-70_
- reflection: `USTRUCT(meta = (DisplayName = "Passthrough Blend", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: It will generate an output using the base trait input keyframe and the selected alpha blend type (float, bool or curve) Requires a base trait with a single input and PostEvaluate task creation (currently used to blend Control Rig Trait) If alpha type is Float or Bool Depending on the weight value - 0 (not relevant)          : The input "as is" will be the output (passthrough). No call to PostEvaluate on the base will be performed. - 1 (full weight)           : The output of the base will be used as the output without blending by calling base PostEvaluate - Any other relevant weight : Input will be duplicated (with a task) in Post Evaluate The base Post Evaluate will be called to execute on the copy (normally will create a task) Both keyframes (original and copy with base modifications) will be blended using a two keyframes blend task, passing the calculated alpha blend weight If alpha type is Curve The curve value is not known until we are in the task (because we need the keyframe to extract the curve value) Currently, the process will generate a full blend :	A task will added to duplicate input keyframe at PostEvaluate Base PostEvaluate will be called to allow task creation Resulting keyframes will be blended with a two keyframes blend task, passing the curve data so the alpha can be obtained If we try to get current alpha value of a Curve blend type, the returned value will be 1
- L40 _public member_ `float Alpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Float"))` — alpha value handler
- L43 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, Category=Settings, meta = (Hidden, EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Float"))`
- L46 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden, DisplayAfter = "AlphaCurveName", EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Float || AlphaInputType == EAnimAlphaInputType::Curve"))`
- L49 _public member_ `bool bAlphaBoolEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "bEnabled", EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Bool"))`
- L52 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Hidden, DisplayName = "Blend Settings", EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Bool"))`
- L55 _public member_ `FName AlphaCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditConditionHides, EditCondition = "AlphaInputType == EAnimAlphaInputType::Curve"))`
- L58 _public member_ `EAnimAlphaInputType AlphaInputType = EAnimAlphaInputType::Float;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### struct `UE::UAF::FPassthroughBlendTrait`  
`struct FPassthroughBlendTrait : FAdditiveTrait, IUpdate, IEvaluate`  
_L75-102_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate`
- L77 _public typedef_ `typedef FBaseTrait Super;`
- L81 _public typedef_ `using FSharedData = FPassthroughBlendTraitSharedData;`
- L95 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate
- L96 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L99 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L101 _public prototype_ `static float ComputeAlphaValue(const EAnimAlphaInputType AlphaInputType, const FPassthroughBlendTraitSharedData* SharedData, FInstanceData* InstanceData, const TTraitBinding<IUpdate>& Binding, float DeltaTime);`

#### struct `UE::UAF::FPassthroughBlendTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L83-92_
- inherits: `FTrait::FInstanceData`
- L85 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;`
- L86 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;`
- L88 _public member_ `float DeltaTime = 0.f;`
- L89 _public member_ `float ComputedAlphaValue = 0.f;`
- L91 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L61 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L72 _namespace_ `namespace UE`
- L72 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/PassthroughTraitData.h` (Public)


#### struct `FAnimNextPassthroughSharedData`  
`struct FAnimNextPassthroughSharedData : public FAnimNextTraitSharedData`  
_L12-19_
- reflection: `USTRUCT(meta = (DisplayName = "Passthrough", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that passes through the input without modification.
- L18 _public member_ `FAnimNextTraitHandle Input;` — `UPROPERTY()` — Input to pass to output

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/SequencePlayerTraitData.h` (Public)


#### struct `FAnimNextSequencePlayerTraitSharedData`  
`struct FAnimNextSequencePlayerTraitSharedData : public FAnimNextTraitSharedData`  
_L13-42_
- reflection: `USTRUCT(meta = (DisplayName = "Sequence Player", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can play an animation sequence.
- L19 _public member_ `TObjectPtr<const UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Sequence Player", meta=(ExportAsReference="true", FactorySource, OnBecomeRelevant))` — The sequence to play.
- L23 _public member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Sequence Player")` — The play rate multiplier at which this sequence plays.
- L27 _public member_ `float StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Sequence Player", meta = (OnBecomeRelevant))` — The time at which we should start playing this sequence.
- L31 _public member_ `UE::UAF::EAnimAssetLoopMode LoopMode = UE::UAF::EAnimAssetLoopMode::Auto;` — `UPROPERTY(EditAnywhere, Category = "Sequence Player", meta = (OnBecomeRelevant))` — Whether to use the asset's default looping behavior or force an override.

#### Free symbols / members of external scopes

- L34 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace UAF` (scope `UE`)
- L47 _typedef_ `using FSequencePlayerData = FAnimNextSequencePlayerTraitSharedData;` (scope `UE::UAF`) — Namespaced alias

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/SubGraphHostTraitData.h` (Public)


#### struct `FAnimNextSubGraphHostTraitSharedData`  
`struct FAnimNextSubGraphHostTraitSharedData : public FAnimNextTraitSharedData`  
_L15-38_
- reflection: `USTRUCT(meta = (DisplayName = "SubGraph", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that hosts and manages a sub-graph instance.
- L21 _public member_ `TObjectPtr<const UUAFAnimGraph> AnimationGraph;` — `UPROPERTY(EditAnywhere, Category = "Default", meta=(ExportAsReference="true"))` — Asset to use as a sub-graph
- L25 _public member_ `FAnimNextTraitHandle ReferencePoseChild;` — `UPROPERTY(meta = (Hidden))` — A dummy child that we can use to output the bind pose. This property is hidden and automatically populated during compilation.
- L29 _public member_ `FName EntryPoint;` — `UPROPERTY(EditAnywhere, Category = "Default", meta=(CustomWidget = "ParamName", AllowedParamType = "FAnimNextEntryPoint"))` — Entry point in the Subgraph that we will use

#### Free symbols / members of external scopes

- L32 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Public/Traits/SynchronizeUsingGroupsTraitData.h` (Public)


#### struct `FAnimNextSynchronizeUsingGroupsTraitSharedData`  
`struct FAnimNextSynchronizeUsingGroupsTraitSharedData : public FAnimNextTraitSharedData`  
_L13-44_
- reflection: `USTRUCT(meta = (DisplayName = "Synchronize Using Groups"))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that synchronizes animation sequence playback using named groups.
- L20 _public member_ `FName GroupName;` — `UPROPERTY(EditAnywhere, Category = "Synchronize Using Groups")` — The group name If no name is provided, this trait is inactive
- L24 _public member_ `EAnimGroupSynchronizationRole GroupRole = EAnimGroupSynchronizationRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = "Synchronize Using Groups")` — The role this player can assume within the group
- L28 _public member_ `EAnimGroupSynchronizationMode SyncMode = EAnimGroupSynchronizationMode::NoSynchronization;` — `UPROPERTY(EditAnywhere, Category = "Synchronize Using Groups")` — The synchronization mode
- L33 _public member_ `bool bMatchSyncPoint = true;` — `UPROPERTY(EditAnywhere, Category = "Synchronize Using Groups")` — Whether or not to match the group sync point when joining as leader or follower with markers When disabled, the start position of synced sequences must be properly set to avoid pops

#### Free symbols / members of external scopes

- L36 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace UAF` (scope `UE`)
- L49 _typedef_ `using FSynchronizeUsingGroupsData = FAnimNextSynchronizeUsingGroupsTraitSharedData;` (scope `UE::UAF`) — Namespaced alias
