# Plugins / UAFStateTree

- module root: `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree`
- headers: 17; symbols: 255
- symbol kinds: class=5, enum=6, enumerator=13, function=26, macro=3, member=71, namespace=27, prototype=70, struct=28, typedef=6
- PrivateDependencyModuleNames: RigVM, RigVMDeveloper, StateTreeEditorModule, UAFAnimGraph, UAFAnimGraphUncookedOnly, UAFAnimNode, UAFEditor, UAFUncookedOnly, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, HierarchyTableAnimationRuntime, HierarchyTableRuntime, StateTreeModule, UAF

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/AnimNextStateTree.h` (Internal)


#### struct `FAnimNextStateTreeCustomVersion`  
`struct FAnimNextStateTreeCustomVersion`  
_L16-35_
- L31 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L34 _private prototype_ `FAnimNextStateTreeCustomVersion() = default;`

#### enum `FAnimNextStateTreeCustomVersion::Type`  
`enum Type`  
_L18-28_
- L21 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L23 _public enumerator_ `InnerStateTreeUniqueName` — Added unique name to inner state tree
- L26 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L27 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### class `UAnimNextStateTree`  
`class UAnimNextStateTree : public UUAFAnimGraph`  
_L38-55_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UUAFAnimGraph`
- L48 _public member_ `TObjectPtr<UStateTree> StateTree;` — `UPROPERTY()`
- L53 _public prototype_ `virtual void PostLoad() override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace UncookedOnly` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/AnimNextStateTreeEditorOnlyTypes.h` (Internal)


#### struct `FAnimNextStateTreeProgrammaticFunctionHeaderParams`  
`struct FAnimNextStateTreeProgrammaticFunctionHeaderParams`  
_L19-33_
- desc: Helper struct to contain info needed to compile RigVM Variables
- L21 _public function_ `FAnimNextStateTreeProgrammaticFunctionHeaderParams(const UUAFSharedVariables_EditorData* InEditorData, const FRigVMCompileSettings& InSettings, const FRigVMClient& InRigVMClient, FAnimNextGetFunctionHeaderCompileContext& InOutCompileContext) : EditorData(InEditorData) , Settings(InSettings) , RigVMClient(InRigVMClient) , OutCompileContext(InOutCompileContext)`
- L29 _public member_ `const UUAFSharedVariables_EditorData* EditorData;`
- L30 _public member_ `const FRigVMCompileSettings& Settings;`
- L31 _public member_ `const FRigVMClient& RigVMClient;`
- L32 _public member_ `FAnimNextGetFunctionHeaderCompileContext& OutCompileContext;`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/AnimNextStateTreeSchema.h` (Internal)


#### class `UStateTreeAnimNextSchema`  
`class UStateTreeAnimNextSchema : public UStateTreeSchema`  
_L11-35_
- reflection: `UCLASS(HideDropDown)`
- inherits: `UStateTreeSchema`
- L15 _public prototype_ `UStateTreeAnimNextSchema();`
- L17 _public member_ `static const FName AnimStateTreeExecutionContextName;`
- L19 _public prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;`
- L20 _public prototype_ `virtual bool IsClassAllowed(const UClass* InScriptStruct) const override;`
- L21 _public prototype_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override;`
- L23 _public function_ `virtual TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const override`
- L24 _public prototype_ `virtual EStateTreeParameterDataType GetGlobalParameterDataType() const override;`
- L27 _public function_ `virtual bool AllowUtilityConsiderations() const override`
- L28 _public function_ `virtual bool AllowEvaluators() const override`
- L29 _public function_ `virtual bool AllowQueuedCompilation() const override`
- L34 _protected member_ `TArray<FStateTreeExternalDataDesc> ContextDataDescs;` — `UPROPERTY()` — List of named external data required by schema and provided to the state tree through the execution context.

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/AnimNextStateTreeTypes.h` (Internal)


#### struct `FAnimNextStateTreeEvaluatorBase`  
`struct FAnimNextStateTreeEvaluatorBase : public FStateTreeEvaluatorBase`  
_L15-18_
- reflection: `USTRUCT(meta = (DisplayName = "UAF Evaluator Base", Hidden))`
- inherits: `FStateTreeEvaluatorBase`
- desc: Base struct for all AnimNext StateTree Evaluators.

#### struct `FAnimNextStateTreeTaskBase`  
`struct FAnimNextStateTreeTaskBase : public FStateTreeTaskBase`  
_L24-31_
- reflection: `USTRUCT(meta = (DisplayName = "UAF Task Base", Hidden))`
- inherits: `FStateTreeTaskBase`
- desc: Base struct for all AnimNext StateTree Tasks.
- L29 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects, const FStateTreeDataView InstanceDataView) const`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/AnimNode/UAFStateTreeNode.h` (Internal)


#### class `UE::UAF::StateTree::FUAFStateTreeNode`  
`class FUAFStateTreeNode : public FUAFBlendStack`  
_L25-45_
- inherits: `FUAFBlendStack`
- desc: Anim Node for playing a State tree
- L28 _public prototype_ `FUAFStateTreeNode(FUAFAnimGraphUpdateContext& Context, TObjectPtr<const UStateTree> StateTree);`
- L30 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& Context) override;`
- L31 _public prototype_ `static void AddReferencedObjects(FUAFAnimNode* This, FReferenceCollector& Collector);`
- L33 _public prototype_ `void BlendTo(FUAFAnimGraphUpdateContext& Context, TConstStructView<FUAFGraphFactoryAsset> AssetData, FUAFTransitionNodeData* TransitionBlend = nullptr);`
- L36 _public prototype_ `virtual FString GetDebugName() const override;`
- L37 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L42 _private member_ `TObjectPtr<const UStateTree> StateTree = nullptr;`
- L43 _private member_ `FStateTreeInstanceData InstanceData;`
- L44 _private member_ `FStateTreeExecutionContext::FExternalGlobalParameters StateTreeExternalParameters;`

#### struct `UE::UAF::StateTree::FUAFStateTreeNodeData`  
`struct FUAFStateTreeNodeData : public FUAFAnimNodeData #if CPP , public IUAFAnimNodeDataHasAsset #endif`  
_L48-78_
- reflection: `USTRUCT(DisplayName = "State Tree")`
- inherits: `FUAFAnimNodeData,IUAFAnimNodeDataHasAsset`
- L55 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;`
- L56 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`
- L59 _public function_ `virtual UObject* GetAsset() const override` — HasAsset interface
- L64 _public function_ `const UStateTree* GetStateTree() const`
- L69 _public function_ `void SetStateTree(UAnimNextStateTree* InStateTree)`
- L77 _private member_ `TObjectPtr<UAnimNextStateTree> StateTree;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/AnimNode/UAFStateTreeNodeConditions.h` (Internal)


#### struct `UE::UAF::StateTree::FUAFDummyInstanceData`  
`struct FUAFDummyInstanceData`  
_L23-26_
- reflection: `USTRUCT()`

#### struct `UE::UAF::StateTree::FUAFVariableConditionBase`  
`struct FUAFVariableConditionBase : public FStateTreeConditionBase`  
_L31-48_
- reflection: `USTRUCT(MinimalAPI, Meta = (Hidden))`
- inherits: `FStateTreeConditionBase`
- L35 _public typedef_ `using FInstanceDataType = FUAFDummyInstanceData;`
- L37 _public prototype_ `FUAFVariableConditionBase() = default;`
- L39 _public function_ `virtual bool Link(FStateTreeLinker& Linker) override`
- L45 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L47 _public member_ `TStateTreeExternalDataHandle<FUAFStateTreeContext> ContextHandle;`

#### enum `UE::UAF::StateTree::EUAFFloatCompareConditionType`  
`enum class EUAFFloatCompareConditionType`  
_L51-55_
- reflection: `UENUM()`
- L53 _public enumerator_ `Less`
- L54 _public enumerator_ `Greater`

#### struct `UE::UAF::StateTree::FUAFFloatCompareCondition`  
`struct FUAFFloatCompareCondition : public FUAFVariableConditionBase`  
_L58-74_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "(PROTOTYPE) UAF Float Variable Compare")`
- inherits: `FUAFVariableConditionBase`
- L62 _public prototype_ `FUAFFloatCompareCondition() = default;`
- L64 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L67 _public member_ `FAnimNextVariableReference Left;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L70 _public member_ `EUAFFloatCompareConditionType Compare = EUAFFloatCompareConditionType::Less;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L73 _public member_ `double Right = 0;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### struct `UE::UAF::StateTree::FUAFEnumCompareCondition`  
`struct FUAFEnumCompareCondition : public FUAFVariableConditionBase`  
_L78-91_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "(PROTOTYPE) UAF Enum Variable Compare")`
- inherits: `FUAFVariableConditionBase`
- L82 _public prototype_ `FUAFEnumCompareCondition() = default;`
- L84 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L87 _public member_ `FAnimNextVariableReference Left;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L90 _public member_ `uint8 Right = 0;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L17 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/AnimStateTreeTrait.h` (Internal)


#### struct `FAnimNextStateTreeTraitSharedData`  
`struct FAnimNextStateTreeTraitSharedData : public FAnimNextTraitSharedData`  
_L19-36_
- reflection: `USTRUCT(meta = (DisplayName = "State Tree"))`
- inherits: `FAnimNextTraitSharedData`
- L24 _public member_ `FStateTreeReference StateTreeReference;` — `UPROPERTY(EditAnywhere, Category = "Default", DisplayName = "State Tree", meta=(ExportAsReference="true"))`
- L27 _public member_ `FStateTreeReferenceOverrides LinkedStateTreeOverrides;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `UE::UAF::FStateTreeTrait`  
`struct FStateTreeTrait : FAdditiveTrait, IUpdate, IGarbageCollection`  
_L40-62_
- inherits: `FAdditiveTrait,IUpdate,IGarbageCollection`
- L44 _public typedef_ `using FSharedData = FAnimNextStateTreeTraitSharedData;`
- L57 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L58 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L61 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### struct `UE::UAF::FStateTreeTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L46-53_
- inherits: `FTrait::FInstanceData`
- L48 _public member_ `TObjectPtr<const UStateTree> StateTree;`
- L49 _public member_ `FStateTreeInstanceData InstanceData;`
- L50 _public member_ `FStateTreeExecutionContext::FExternalGlobalParameters StateTreeExternalParameters;`
- L52 _public prototype_ `void Destruct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L30 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/Conditions/AnimNextStateTreeRigVMConditionBase.h` (Internal)


#### struct `FAnimNextStateTreeRigVMConditionInstanceData`  
`struct FAnimNextStateTreeRigVMConditionInstanceData`  
_L28-38_
- reflection: `USTRUCT()`
- L34 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category = "Parameters", Meta = (FixedLayout, ShowOnlyInnerProperties))` — Parameters to use to call the function
- L37 _public member_ `UE::UAF::FFunctionHandle FunctionHandle;` — Cached function handle

#### struct `FAnimNextStateTreeRigVMConditionBase`  
`struct FAnimNextStateTreeRigVMConditionBase : public FStateTreeConditionBase`  
_L44-109_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FStateTreeConditionBase`
- desc: Wrapper for RigVM based Conditions.
- L48 _public typedef_ `using FInstanceDataType = FAnimNextStateTreeRigVMConditionInstanceData;`
- L53 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L54 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;`
- L58 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L60 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L61 _public prototype_ `virtual void PostEditNodeChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent, FStateTreeDataView InstanceDataView) override;`
- L67 _public prototype_ `virtual void GetProgrammaticFunctionHeaders(FAnimNextStateTreeProgrammaticFunctionHeaderParams& InProgrammaticFunctionHeaderParams, UStateTreeState* State, FStateTreeDataView InstanceDataView, const FStateTreeBindableStructDesc& Desc);` — Adds condition function headers to parent StateTree RigVM
- L70 _public prototype_ `void RegenerateInstanceDataFunctionParams(TNotNull<FInstanceDataType*> InstanceData);` — Regenerates the instance data params
- L77 _public member_ `FRigVMGraphFunctionHeader RigVMFunctionHeader = FRigVMGraphFunctionHeader();` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "RigVMFunctionHeader is deprecated, use CallFunctionInfo.FunctionHeader"))`
- L80 _public member_ `FName ConditionFunctionName = NAME_None;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "ConditionFunctionName is deprecated, use CallFunctionInfo.Function"))`
- L83 _public member_ `FName InternalEventName = NAME_None;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "InternalEventName is deprecated, use CallFunctionInfo.FunctionEvent"))`
- L87 _public member_ `FInstancedPropertyBag DefaultValues;` — `UPROPERTY()` — Bag to hold defaults for function signature. Used to perform manual delta serialization for defaults as InstancedPropertyBag doesn't support that
- L92 _public member_ `FUAFCallFunctionInfo CallFunctionInfo;` — `UPROPERTY(EditAnywhere, Category = "Call Function", meta = (Hidden))` — Info needed to call a UAF function. Also has a custom function picker.
- L96 _public member_ `FName StateName = NAME_None;` — `UPROPERTY()` — Owning state name, populated during programmatic graph creation
- L100 _public member_ `FGuid NodeId = FGuid();` — `UPROPERTY()` — External node ID defined by owning state tree, populated during programmatic graph creation
- L103 _public member_ `int32 ResultIndex = INDEX_NONE;` — `UPROPERTY()`
- L105 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L108 _public member_ `TStateTreeExternalDataHandle<FUAFStateTreeContext> TraitContextHandle;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextStateTreeRigVMConditionBase> : public TStructOpsTypeTraitsBase2<FAnimNextStateTreeRigVMConditionBase>`  
_L113-119_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextStateTreeRigVMConditionBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L116-118_

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API UAFSTATETREE_API`
- L117 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonbdcfd58e0103`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/IAnimNextStateTreeModule.h` (Internal)


#### class `UE::UAF::StateTree::IAnimNextStateTreeModule`  
`class IAnimNextStateTreeModule : public IModuleInterface`  
_L11-13_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/Tasks/AnimNextStateTreeGraphInstanceTask.h` (Internal)


#### struct `FAnimNextGraphInstanceTaskInstanceData`  
`struct FAnimNextGraphInstanceTaskInstanceData`  
_L20-99_
- reflection: `USTRUCT()`
- L26 _public prototype_ `FAnimNextGraphInstanceTaskInstanceData() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L27 _public prototype_ `~FAnimNextGraphInstanceTaskInstanceData() = default;`
- L28 _public prototype_ `FAnimNextGraphInstanceTaskInstanceData(const FAnimNextGraphInstanceTaskInstanceData&) = default;`
- L29 _public prototype_ `FAnimNextGraphInstanceTaskInstanceData(FAnimNextGraphInstanceTaskInstanceData&&) = default;`
- L30 _public prototype_ `FAnimNextGraphInstanceTaskInstanceData& operator=(const FAnimNextGraphInstanceTaskInstanceData&) = default;`
- L31 _public prototype_ `FAnimNextGraphInstanceTaskInstanceData& operator=(FAnimNextGraphInstanceTaskInstanceData&&) = default;`
- L45 _public member_ `TObjectPtr<UObject> Asset_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.8, "Use AssetData instead")` — `UPROPERTY()` — The asset to instantiate
- L49 _public member_ `TInstancedStruct<FUAFGraphFactoryAsset> AssetData;` — `UPROPERTY(EditAnywhere, Category = Animation)`
- L53 _public member_ `FInstancedPropertyBag Payload_DEPRECATED;` — `UPROPERTY()`
- L60 _public member_ `FAnimNextFactoryParams Parameters_DEPRECATED;` — `UE_DEPRECATED(5.8, "Use AssetData instead")` — `UPROPERTY()` — Factory params for procedural graphs
- L65 _public member_ `FAlphaBlendArgs BlendOptions;` — `UPROPERTY(EditAnywhere, Category = Animation)` — Blend options for when the state is pushed
- L69 _public member_ `TObjectPtr<UUAFBlendProfile> BlendProfile;` — `UPROPERTY(EditAnywhere, Category = Animation)` — Optional blend profile to use when the state is pushed
- L73 _public member_ `bool bContinueTicking = true;` — `UPROPERTY(EditAnywhere, Category = Animation)` — Whether this task should continue to tick once state is entered
- L77 _public member_ `float CompleteBlendOutTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Animation)` — How early to trigger complete. Setting this allows for a blend out while the timeline is still playing.
- L81 _public member_ `float PlaybackRatio = 1.0f;` — `UPROPERTY(VisibleAnywhere, Category = Animation)` — Current playback ratio
- L85 _public member_ `float TimeLeft = std::numeric_limits<float>::infinity();` — `UPROPERTY(VisibleAnywhere, Category = Animation)` — Current time remaining
- L89 _public member_ `float Duration = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Animation)` — Current graph duration
- L93 _public member_ `bool bIsLooping = false;` — `UPROPERTY(VisibleAnywhere, Category = Animation)` — Current looping status
- L96 _public prototype_ `bool Serialize(FArchive& Ar);`
- L97 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextGraphInstanceTaskInstanceData> : public TStructOpsTypeTraitsBase2<FAnimNextGraphInstanceTaskInstanceData>`  
_L102-111_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextGraphInstanceTaskInstanceData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L106-109_

#### struct `FAnimNextStateTreeGraphInstanceTask`  
`struct FAnimNextStateTreeGraphInstanceTask : public FAnimNextStateTreeTaskBase`  
_L116-136_
- reflection: `USTRUCT(meta = (DisplayName = "UAF Graph"))`
- inherits: `FAnimNextStateTreeTaskBase`
- desc: Basic task pushing AnimationGraph onto blend stack
- L120 _public typedef_ `using FInstanceDataType = FAnimNextGraphInstanceTaskInstanceData;`
- L122 _public prototype_ `FAnimNextStateTreeGraphInstanceTask();`
- L124 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L126 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L127 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L128 _protected prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L129 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L131 _protected prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L132 _protected prototype_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects, const FStateTreeDataView InstanceDataView) const override;`
- L135 _public member_ `TStateTreeExternalDataHandle<FUAFStateTreeContext> TraitContextHandle;`

#### Free symbols / members of external scopes

- L107 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon80c2476d0103`)
- L108 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon80c2476d0103`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/Tasks/AnimNextStateTreeRigVMTaskBase.h` (Internal)


#### enum `EStateTreeFunctionCallFrequency`  
`enum class EStateTreeFunctionCallFrequency`  
_L27-32_
- reflection: `UENUM()`
- L29 _public enumerator_ `OnEnter`
- L30 _public enumerator_ `OnTick`
- L31 _public enumerator_ `OnExit`

#### struct `FAnimNextStateTreeRigVMTaskInstanceData`  
`struct FAnimNextStateTreeRigVMTaskInstanceData`  
_L35-45_
- reflection: `USTRUCT()`
- L41 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category = "Parameters", Meta = (FixedLayout, ShowOnlyInnerProperties))` — Parameters to use to call the function
- L44 _public member_ `UE::UAF::FFunctionHandle FunctionHandle;` — Cached function handle

#### struct `FAnimNextStateTreeRigVMTaskBase`  
`struct FAnimNextStateTreeRigVMTaskBase : public FAnimNextStateTreeTaskBase`  
_L51-129_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FAnimNextStateTreeTaskBase`
- desc: Wrapper for RigVM based Tasks.
- L55 _public typedef_ `using FInstanceDataType = FAnimNextStateTreeRigVMTaskInstanceData;`
- L60 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L61 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L62 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L63 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L67 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L69 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L70 _public prototype_ `virtual void PostEditNodeChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent, FStateTreeDataView InstanceDataView) override;`
- L76 _public prototype_ `virtual void GetProgrammaticFunctionHeaders(FAnimNextStateTreeProgrammaticFunctionHeaderParams& InProgrammaticFunctionHeaderParams, UStateTreeState* State, FStateTreeDataView InstanceDataView, const FStateTreeBindableStructDesc& Desc);` — Adds Task function headers to parent StateTree RigVM
- L79 _public prototype_ `void RegenerateInstanceDataFunctionParams(TNotNull<FInstanceDataType*> InstanceData);` — Regenerates the instance data params
- L86 _public member_ `FRigVMGraphFunctionHeader RigVMFunctionHeader = FRigVMGraphFunctionHeader();` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "RigVMFunctionHeader is deprecated, use CallFunctionInfo.FunctionHeader"))`
- L89 _public member_ `FName TaskFunctionName = NAME_None;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "TaskFunctionName is deprecated, use CallFunctionInfo.Function"))`
- L92 _public member_ `FName InternalEventName = NAME_None;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "InternalEventName is deprecated, use CallFunctionInfo.FunctionEvent"))`
- L96 _public member_ `FInstancedPropertyBag DefaultValues;` — `UPROPERTY()` — Bag to hold defaults for function signature. Used to perform manual delta serialization for defaults as InstancedPropertyBag doesn't support that
- L101 _public member_ `FUAFCallFunctionInfo CallFunctionInfo;` — `UPROPERTY(EditAnywhere, Category = "Call Function", meta = (Hidden))` — Info needed to call a UAF function. Also has a custom function picker.
- L104 _public member_ `EStateTreeFunctionCallFrequency CallFunctionFrequency = EStateTreeFunctionCallFrequency::OnEnter;` — `UPROPERTY(EditAnywhere, Category = "Call Function")`
- L108 _public member_ `FName StateName = NAME_None;` — `UPROPERTY()` — Owning state name, populated during programmatic graph creation
- L112 _public member_ `FGuid NodeId = FGuid();` — `UPROPERTY()` — External node ID defined by owning state tree, populated during programmatic graph creation
- L115 _public member_ `int32 ResultIndex = INDEX_NONE;` — `UPROPERTY()`
- L119 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L123 _public member_ `TStateTreeExternalDataHandle<FUAFStateTreeContext> TraitContextHandle;`
- L128 _protected prototype_ `EStateTreeRunStatus CallFunction(FStateTreeExecutionContext& Context) const;` — Internal impl to call some RigVM function

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNextStateTreeRigVMTaskBase> : public TStructOpsTypeTraitsBase2<FAnimNextStateTreeRigVMTaskBase>`  
_L133-139_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNextStateTreeRigVMTaskBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L136-138_

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API UAFSTATETREE_API`
- L137 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon094f69860103`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Internal/Tasks/UAFStateTreeSetVariableTask.h` (Internal)


#### struct `FUAFStateTreeSetVariableTaskInstanceData`  
`struct FUAFStateTreeSetVariableTaskInstanceData`  
_L19-30_
- reflection: `USTRUCT()`
- desc: Instance data for FUAFStateTreeSetVariableTask.
- L25 _public member_ `FAnimNextVariableReference Variable;` — `UPROPERTY(EditAnywhere, Category = Variable)` — Which UAF variable to write.
- L29 _public member_ `FInstancedPropertyBag Value;` — `UPROPERTY(EditAnywhere, Category = Variable, Meta = (FixedLayout, ShowOnlyInnerProperties))` — Value to write. Automatically reshaped to match Variable's type when Variable changes.

#### struct `FUAFStateTreeSetVariableTask`  
`struct FUAFStateTreeSetVariableTask : public FAnimNextStateTreeTaskBase`  
_L37-56_
- reflection: `USTRUCT(MinimalAPI, DisplayName = "UAF Set Variable")`
- inherits: `FAnimNextStateTreeTaskBase`
- desc: StateTree task that writes a single UAF shared variable on state entry. Stack multiple instances of this task in one state to write multiple variables independently.
- L41 _public typedef_ `using FInstanceDataType = FUAFStateTreeSetVariableTaskInstanceData;`
- L44 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L45 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L49 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L51 _public prototype_ `virtual void PostEditInstanceDataChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent, FStateTreeDataView InstanceDataView) override;`
- L55 _public member_ `TStateTreeExternalDataHandle<FUAFStateTreeContext> ContextHandle;`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Private/AnimNextStateTreeModule.h` (Private)


#### class `UE::UAF::StateTree::FAnimNextStateTreeModule`  
`class FAnimNextStateTreeModule : public IAnimNextStateTreeModule`  
_L11-19_
- inherits: `IAnimNextStateTreeModule`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L18 _private member_ `FTopLevelAssetPath UAFStateTreeClassPath;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Private/AnimNode/UAFStateTreeNodeContext.h` (Private)


#### struct `UE::UAF::StateTree::FUAFStateTreeNodeContext`  
`struct FUAFStateTreeNodeContext : public FUAFStateTreeContext`  
_L20-52_
- reflection: `USTRUCT()`
- inherits: `FUAFStateTreeContext`
- L24 _public function_ `FUAFStateTreeNodeContext() : Context(nullptr), AnimNode(nullptr)`
- L29 _public function_ `FUAFStateTreeNodeContext(FUAFAnimGraphUpdateContext& InContext, FUAFStateTreeNode* InAnimNode) : Context(&InContext), AnimNode(InAnimNode)`
- L34 _public prototype_ `virtual bool PushAssetOntoBlendStack(FGraphAssetHandleConstView InAsset, const FAlphaBlendArgs& InBlendArguments, const UUAFBlendProfile* BlendProfile) const override;`
- L35 _public prototype_ `virtual void QueryPlaybackInfo(FPlaybackInfo& OutPlaybackInfo) const override;`
- L36 _public prototype_ `virtual FUAFAssetInstance* GetVariablesOwner() const override;`
- L38 _public function_ `UE::UAF::FUAFAnimGraphUpdateContext* GetContext() const`
- L43 _public function_ `FUAFStateTreeNode* GetAnimNode() const`
- L50 _private member_ `FUAFAnimGraphUpdateContext* Context;`
- L51 _private member_ `FUAFStateTreeNode* AnimNode;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Private/UAFStateTreeContext.h` (Private)


#### struct `FUAFStateTreeContext`  
`struct FUAFStateTreeContext`  
_L14-30_
- reflection: `USTRUCT()`
- L17 _public function_ `virtual ~FUAFStateTreeContext()`
- L27 _public function_ `virtual bool PushAssetOntoBlendStack(UE::UAF::FGraphAssetHandleConstView InAsset, const FAlphaBlendArgs& InBlendArguments, const UUAFBlendProfile* InBlendProfile) const`
- L28 _public function_ `virtual void QueryPlaybackInfo(FPlaybackInfo& OutPlaybackInfo) const`
- L29 _public function_ `virtual FUAFAssetInstance* GetVariablesOwner() const`

#### struct `FUAFStateTreeContext::FPlaybackInfo`  
`struct FPlaybackInfo`  
_L19-25_
- L21 _public member_ `float PlaybackRatio = 0.f;`
- L22 _public member_ `float TimeLeft = 0.f;`
- L23 _public member_ `float Duration = 0.f;`
- L24 _public member_ `bool bIsLooping = false;`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Private/UAFStateTreeRigVMUtils.h` (Private)


#### struct `UE::UAF::StateTree::FUtils`  
`struct FUtils`  
_L12-21_
- L16 _public prototype_ `static bool IsBindingOutDated(FUAFCallFunctionInfo& CallFunctionInfo, FInstancedPropertyBag& DefaultValues, FInstancedPropertyBag& Parameters);` — True if parameters or default values no longer match the given function header.
- L19 _public prototype_ `static void RegenerateParameterPropertyBag(FUAFCallFunctionInfo& CallFunctionInfo, FInstancedPropertyBag& DefaultValues, FInstancedPropertyBag& Parameters, int32& ResultIndex);` — Repopulates parameters and default values with the given function header.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTree/Private/UAFStateTreeTraitContext.h` (Private)


#### struct `FUAFStateTreeTraitContext`  
`struct FUAFStateTreeTraitContext : public FUAFStateTreeContext`  
_L20-55_
- reflection: `USTRUCT()`
- inherits: `FUAFStateTreeContext`
- L27 _public prototype_ `FUAFStateTreeTraitContext() = default;`
- L29 _public function_ `FUAFStateTreeTraitContext(UE::UAF::FExecutionContext& InContext, const UE::UAF::FTraitBinding& InBinding) : Context(&InContext) , Binding(&InBinding)`
- L34 _public prototype_ `virtual bool PushAssetOntoBlendStack(UE::UAF::FGraphAssetHandleConstView InAsset, const FAlphaBlendArgs& InBlendArguments, const UUAFBlendProfile* BlendProfile) const override;`
- L36 _public prototype_ `virtual void QueryPlaybackInfo(FPlaybackInfo& OutPlaybackInfo) const override;`
- L37 _public prototype_ `virtual FUAFAssetInstance* GetVariablesOwner() const override;`
- L39 _public function_ `UE::UAF::FExecutionContext& GetContext() const`
- L45 _public function_ `const UE::UAF::FTraitBinding& GetBinding() const`
- L53 _private member_ `UE::UAF::FExecutionContext* Context = nullptr;`
- L54 _private member_ `const UE::UAF::FTraitBinding* Binding = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
