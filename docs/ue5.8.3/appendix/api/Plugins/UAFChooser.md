# Plugins / UAFChooser

- module root: `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser`
- headers: 9; symbols: 162
- symbol kinds: class=2, enum=4, enumerator=8, function=11, macro=2, member=44, namespace=7, prototype=59, struct=23, typedef=2
- PrivateDependencyModuleNames: Chooser, ControlRig, Core, CoreUObject, Engine, RigVM, UAFAnimGraph, UAFAnimNode, UAFChooserUncookedOnly, UAFEditor, UAFUncookedOnly, WorkspaceEditor
- PublicDependencyModuleNames: Chooser, UAF

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Internal/AnimNode/UAFChooserPlayerNode.h` (Internal)


#### struct `UE::UAF::Chooser::FUAFChooserPlayerNodeSettings`  
`struct FUAFChooserPlayerNodeSettings : public FUAFChooserPlayerSettings`  
_L26-31_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FUAFChooserPlayerSettings`
- L30 _public member_ `const FUAFAnimNodeData* AnimNodeData = nullptr;`

#### class `UE::UAF::Chooser::FUAFChooserPlayerNode`  
`class FUAFChooserPlayerNode : public FUAFAnimNode`  
_L33-72_
- inherits: `FUAFAnimNode`
- L36 _public prototype_ `FUAFChooserPlayerNode(FUAFAnimGraphUpdateContext& Context, const UUAFAnimChooserTable* Chooser, EChooserEvaluationFrequency EvaluationFrequency = EChooserEvaluationFrequency::OnBecomeRelevant, const TInstancedStruct<FUAFTransitionNodeData>* TransitionData = nullptr);`
- L37 _public prototype_ `FUAFChooserPlayerNode(FUAFAnimGraphUpdateContext& Context, const FUAFChooserPlayerNodeData* InData);`
- L39 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;`
- L40 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`
- L41 _public prototype_ `static void AddReferencedObjects(FUAFAnimNode* This, FReferenceCollector& Collector);`
- L45 _public prototype_ `static FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context, TObjectPtr<const UUAFAnimChooserTable> Chooser, EChooserEvaluationFrequency EvaluationFrequency = EChooserEvaluationFrequency::OnInitialUpdate, const TInstancedStruct<FUAFTransitionNodeData>* Transition = nullptr);` — helper function for creating an instance from a Chooser. if EvaluationFrequency is not set to OnLoop or OnUpdate, this functuin will evaluate the chooser immediately, and create an instance for the selected result
- L51 _public prototype_ `virtual FString GetDebugName() const override;`
- L52 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L56 _private prototype_ `void ChooseNewAnimation(FUAFAnimGraphUpdateContext& Context);`
- L59 _private member_ `const FUAFAnimNodeData* CurrentSelectionNodeData = nullptr;` — properties for determining if a new selection is actually new
- L60 _private member_ `const FUAFGraphFactoryAsset* CurrentSelectionAssetData = nullptr;`
- L61 _private member_ `const UObject* CurrentSelectionObject = nullptr;`
- L62 _private member_ `float CurrentStartTime = 0;`
- L63 _private member_ `bool CurrentMirror = false;`
- L64 _private member_ `uint32 CurrentCurveOverridesHash = 0;`
- L66 _private member_ `float CachedCurrentTime = 0;`
- L67 _private member_ `TObjectPtr<const UUAFAnimChooserTable> Chooser;`
- L68 _private member_ `EChooserEvaluationFrequency EvaluationFrequency = EChooserEvaluationFrequency::OnBecomeRelevant;`
- L69 _private member_ `TInstancedStruct<FUAFTransitionNodeData> Transition;`
- L71 _private member_ `TUAFInlineAnimNode<FUAFBlendStack> BlendStack;`

#### struct `UE::UAF::Chooser::FUAFChooserPlayerNodeData`  
`struct FUAFChooserPlayerNodeData : public FUAFAnimNodeData #if CPP , public IUAFAnimNodeDataHasAsset #endif`  
_L75-97_
- reflection: `USTRUCT(DisplayName="Chooser Player")`
- inherits: `FUAFAnimNodeData,IUAFAnimNodeDataHasAsset`
- L83 _public member_ `TObjectPtr<UUAFAnimChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Category="Chooser")`
- L87 _public member_ `EChooserEvaluationFrequency EvaluationFrequency = EChooserEvaluationFrequency::OnBecomeRelevant;` — `UPROPERTY(EditAnywhere, Category = "Chooser")` — How often the chooser should be evaluated
- L91 _public member_ `TInstancedStruct<FUAFTransitionNodeData> Transition;` — `UPROPERTY(EditAnywhere, Category = "Chooser")` — How to transition between animations
- L93 _public function_ `virtual UObject* GetAsset() const override`
- L95 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;`
- L96 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeDataInterfaceId InterfaceId) override;`

#### struct `UE::UAF::Chooser::FAnimNodeResult`  
`struct FAnimNodeResult : public FObjectChooserBase`  
_L100-124_
- reflection: `USTRUCT()`
- inherits: `FObjectChooserBase`
- L105 _public member_ `FUAFAnimNodeDataEx NodeData;` — `UPROPERTY(EditAnywhere, Category = "NodeData", meta = (ExcludeBaseStruct))`
- L108 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;` — FObjectChooserBase interface
- L109 _public prototype_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const final override;`
- L112 _public function_ `virtual UObject* GetReferencedObject() const override`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace Chooser` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Internal/ChooserParameters.h` (Internal)


#### struct `FBoolAnimProperty`  
`struct FBoolAnimProperty : public FChooserParameterBoolBase`  
_L14-35_
- reflection: `USTRUCT(DisplayName = "Bool Anim Param")`
- inherits: `FChooserParameterBoolBase`
- L21 _public member_ `FName VariableName_DEPRECATED;` — `UPROPERTY()`
- L25 _public member_ `FAnimNextVariableReference Variable;` — `UPROPERTY(DisplayName = "Variable", EditAnywhere, Category="Variable", meta = (AllowedType = "bool"))`
- L27 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, bool& OutResult) const override;`
- L28 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, bool InValue) const override;`
- L29 _public prototype_ `virtual void GetDisplayName(FText& OutName) const override;`
- L32 _public prototype_ `bool Serialize(FArchive& Ar);`
- L33 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FBoolAnimProperty> : public TStructOpsTypeTraitsBase2<FBoolAnimProperty>`  
_L38-47_
- inherits: `TStructOpsTypeTraitsBase2<FBoolAnimProperty>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L42-45_

#### struct `FFloatAnimProperty`  
`struct FFloatAnimProperty : public FChooserParameterFloatBase`  
_L50-71_
- reflection: `USTRUCT(DisplayName = "Float Anim Param")`
- inherits: `FChooserParameterFloatBase`
- L57 _public member_ `FName VariableName_DEPRECATED;` — `UPROPERTY()`
- L61 _public member_ `FAnimNextVariableReference Variable;` — `UPROPERTY(DisplayName = "Variable", EditAnywhere, Category="Variable", meta = (AllowedType = "float"))`
- L63 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, double& OutResult) const override;`
- L64 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, double InValue) const override;`
- L65 _public prototype_ `virtual void GetDisplayName(FText& OutName) const override;`
- L68 _public prototype_ `bool Serialize(FArchive& Ar);`
- L69 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FFloatAnimProperty> : public TStructOpsTypeTraitsBase2<FFloatAnimProperty>`  
_L74-83_
- inherits: `TStructOpsTypeTraitsBase2<FFloatAnimProperty>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L78-81_

#### struct `FEnumAnimProperty`  
`struct FEnumAnimProperty : public FChooserParameterEnumBase`  
_L86-133_
- reflection: `USTRUCT(DisplayName = "Enum Anim Param")`
- inherits: `FChooserParameterEnumBase`
- L94 _public member_ `FName VariableName_DEPRECATED;` — `UPROPERTY()`
- L98 _public member_ `FAnimNextVariableReference Variable;` — `UPROPERTY(DisplayName = "Variable", EditAnywhere, Category="Variable")`
- L100 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, uint8& OutResult) const override;`
- L101 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, uint8 InValue) const override;`
- L103 _public prototype_ `virtual void GetDisplayName(FText& OutName) const override;`
- L106 _public prototype_ `bool Serialize(FArchive& Ar);`
- L107 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L111 _public function_ `virtual const UEnum* GetEnum() const override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FEnumAnimProperty> : public TStructOpsTypeTraitsBase2<FEnumAnimProperty>`  
_L136-145_
- inherits: `TStructOpsTypeTraitsBase2<FEnumAnimProperty>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L140-143_

#### struct `FNameAnimProperty`  
`struct FNameAnimProperty : public FChooserParameterNameBase`  
_L148-159_
- reflection: `USTRUCT(DisplayName = "Name Anim Param")`
- inherits: `FChooserParameterNameBase`
- L154 _public member_ `FAnimNextVariableReference Variable;` — `UPROPERTY(DisplayName = "Variable", EditAnywhere, Category="Variable", meta = (AllowedType = "FName"))`
- L156 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, FName& OutResult) const override;`
- L157 _public prototype_ `virtual bool SetValue(FChooserEvaluationContext& Context, const FName& InValue) const override;`
- L158 _public prototype_ `virtual void GetDisplayName(FText& OutName) const override;`

#### Free symbols / members of external scopes

- L43 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anoneae2a4140103`)
- L44 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anoneae2a4140103`)
- L79 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anoneae2a4140203`)
- L80 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anoneae2a4140203`)
- L141 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anoneae2a4140303`)
- L142 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anoneae2a4140303`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Internal/ObjectChooser_UAFGraph.h` (Internal)


#### struct `FUAFGraphChooser`  
`struct FUAFGraphChooser : public FObjectChooserBase`  
_L14-55_
- reflection: `USTRUCT(DisplayName = "UAFGraph", Meta = (ResultType = "Object", Category = "Basic", Tooltip = "A asset that can produce a UAF Graph"))`
- inherits: `FObjectChooserBase`
- L19 _public prototype_ `FUAFGraphChooser() = default;`
- L20 _public prototype_ `~FUAFGraphChooser() = default;`
- L21 _public prototype_ `FUAFGraphChooser(const FUAFGraphChooser&) = default;`
- L22 _public prototype_ `FUAFGraphChooser(FUAFGraphChooser&&) = default;`
- L23 _public prototype_ `FUAFGraphChooser& operator=(const FUAFGraphChooser&) = default;`
- L24 _public prototype_ `FUAFGraphChooser& operator=(FUAFGraphChooser&&) = default;`
- L28 _public prototype_ `bool Serialize(FArchive& Ar);`
- L29 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L33 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;` — FObjectChooserBase interface
- L34 _public prototype_ `virtual EIteratorStatus IterateObjects(FChooserEvaluationContext& Context, FObjectChooserIteratorCallback Callback) const final override;`
- L37 _public prototype_ `virtual UObject* GetReferencedObject() const override;`
- L40 _public prototype_ `UObject* GetObjectFromAssetData() const;`
- L43 _public member_ `TInstancedStruct<FUAFGraphFactoryAsset> AssetData;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`
- L48 _public member_ `TObjectPtr<UObject> Asset_DEPRECATED;` — `UE_DEPRECATED(5.8, "Use AssetData instead")` — `UPROPERTY()`
- L54 _public member_ `FAnimNextFactoryParams Parameters;` — `UE_DEPRECATED(5.8, "Use AssetData instead")` — `UPROPERTY()` — Factory params for procedural graphs

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFGraphChooser> : public TStructOpsTypeTraitsBase2<FUAFGraphChooser>`  
_L58-67_
- inherits: `TStructOpsTypeTraitsBase2<FUAFGraphChooser>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L62-65_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHOOSER_API`
- L63 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon928634840103`)
- L64 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon928634840103`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Private/ChooserPlayerTrait.h` (Private)


#### struct `UE::UAF::FChooserPlayerTrait`  
`struct FChooserPlayerTrait : FAdditiveTrait, IUpdate, IGarbageCollection`  
_L24-50_
- inherits: `FAdditiveTrait,IUpdate,IGarbageCollection`
- desc: this trait will Evaluate a Chooser, and play an animation graph constructed from whatever asset the chooser returns
- L28 _public typedef_ `using FSharedData = FChooserPlayerData;`
- L43 _public prototype_ `void EvaluateChooser(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const;`
- L45 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L46 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L49 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### struct `UE::UAF::FChooserPlayerTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L30-41_
- inherits: `FTrait::FInstanceData`
- L32 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L33 _public prototype_ `void Destruct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L35 _public member_ `TObjectPtr<UObject> CurrentSelection = nullptr;`
- L36 _public member_ `float CurrentStartTime = 0;`
- L37 _public member_ `bool CurrentMirror = false;`
- L38 _public member_ `uint32 CurrentCurveOverridesHash = 0;`
- L40 _public member_ `float CachedTimeLeft = 0;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Private/RigUnit_EvaluateChooser.h` (Private)


#### struct `FRigVMDispatch_EvaluateChooser`  
`struct FRigVMDispatch_EvaluateChooser : public FRigVMDispatchFactory`  
_L21-46_
- reflection: `USTRUCT(meta = (DisplayName = "Evaluate Chooser", Category="Choosers", NodeColor = "0.8, 0, 0.2, 1"))`
- inherits: `FRigVMDispatchFactory`
- desc: Evaluates a chooser table and outputs either an object or an array of objects depending on what the result pin is connected to Compatible with both ControlRig and AnimNext graphs
- L25 _public prototype_ `FRigVMDispatch_EvaluateChooser();`
- L30 _private function_ `virtual UScriptStruct* GetExecuteContextStruct() const`
- L31 _private prototype_ `virtual FName GetArgumentNameForOperandIndex(int32 InOperandIndex, int32 InTotalOperands, FRigVMRegistryHandle& InRegistry) const override;`
- L32 _private prototype_ `virtual const TArray<FRigVMTemplateArgumentInfo>& GetArgumentInfos(FRigVMRegistryHandle& InRegistry) const override;`
- L34 _private function_ `virtual bool IsSingleton() const override`
- L36 _private function_ `virtual FRigVMFunctionPtr GetDispatchFunctionImpl(const FRigVMTemplateTypeMap& InTypes, const FRigVMRegistryHandle& InRegistry) const override`
- L41 _private prototype_ `static void Execute(FRigVMExtendedExecuteContext& InContext, FRigVMMemoryHandleArray Handles, FRigVMPredicateBranchArray RigVMBranches);`
- L43 _private member_ `static const FName ChooserName;`
- L44 _private member_ `static const FName ContextObjectName;`
- L45 _private member_ `static const FName ResultName;`

#### struct `FRigUnit_EvaluateChooser`  
`struct FRigUnit_EvaluateChooser : public FRigVMStruct`  
_L52-67_
- reflection: `USTRUCT(meta = (Abstract, Varying))`
- inherits: `FRigVMStruct`
- desc: Evaluates a Chooser Table and outputs the selected UObject
- L58 _public member_ `TObjectPtr<UObject> ContextObject;` — `UPROPERTY(meta = (Input))` — The context object this chooser is related to
- L62 _public member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Category = "Chooser", meta = (Input))` — The chooser to evaluate
- L66 _public member_ `TObjectPtr<UObject> Result;` — `UPROPERTY(meta = (Output))` — The resulting chosen object

#### struct `FRigUnit_EvaluateChooser_ControlRig`  
`struct FRigUnit_EvaluateChooser_ControlRig : public FRigUnit_EvaluateChooser`  
_L74-81_
- reflection: `USTRUCT(meta = (ExecuteContext="FControlRigExecuteContext"))`
- inherits: `FRigUnit_EvaluateChooser`
- desc: Evaluates a Chooser Table in the context of ControlRig deprecated in favor of RigVMDispatch_EvaluateChooser
- L79 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit

#### struct `FRigUnit_EvaluateChooser_AnimNext`  
`struct FRigUnit_EvaluateChooser_AnimNext : public FRigUnit_EvaluateChooser`  
_L88-95_
- reflection: `USTRUCT(meta = (ExecuteContext="FAnimNextExecuteContext"))`
- inherits: `FRigUnit_EvaluateChooser`
- desc: Evaluates a Chooser Table in the context of AnimNext deprecated in favor of RigVMDispatch_EvaluateChooser
- L93 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Private/RigUnit_OwningObject.h` (Private)


#### struct `FRigUnit_OwningObject`  
`struct FRigUnit_OwningObject : public FRigVMStruct`  
_L14-25_
- reflection: `USTRUCT(meta = (DisplayName="Owning Object"))`
- inherits: `FRigVMStruct`
- desc: A node to retrieve the owning object of this graph
- L20 _public member_ `TObjectPtr<UObject> Result;` — `UPROPERTY(meta = (Output))` — The object owning this graph
- L23 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Public/ChooserPlayerTraitData.h` (Public)


#### struct `FUAFChooserPlayerTraitSharedData`  
`struct FUAFChooserPlayerTraitSharedData : public FAnimNextTraitSharedData`  
_L16-48_
- reflection: `USTRUCT(meta = (DisplayName = "Chooser Player", ShowTooltip=true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can evaluate a chooser and play a subggraph based on whatever entry from the chooser was selected .
- L24 _private member_ `TObjectPtr<const UUAFAnimChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Category = "Chooser", meta=(ExportAsReference="true", FactorySource, OnBecomeRelevant))` — The chooser to play.
- L28 _private member_ `EChooserEvaluationFrequency EvaluationFrequency = EChooserEvaluationFrequency::OnBecomeRelevant;` — `UPROPERTY(EditAnywhere, Category = "Chooser")` — How often the chooser should be evaluated
- L31 _public function_ `void SetChooser(const UUAFAnimChooserTable* InChooser)`
- L36 _public function_ `void SetEvaluationFrequency(EChooserEvaluationFrequency InEvaluationFrequency)`

#### struct `FUAFSharedVariablesContext`  
`struct FUAFSharedVariablesContext : public FContextObjectTypeBase`  
_L51-57_
- reflection: `USTRUCT(DisplayName = "UAF Variables Parameter")`
- inherits: `FContextObjectTypeBase`
- L56 _public member_ `TArray<TObjectPtr<UUAFSharedVariables>> SharedVariablesAssets;` — `UPROPERTY(EditAnywhere, Category="Type")`

#### struct `FUAFChooserPlayerSettings`  
`struct FUAFChooserPlayerSettings : public FChooserPlayerSettings`  
_L60-65_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FChooserPlayerSettings`
- L64 _public member_ `UE::UAF::FGraphAssetHandleConstView AssetData;`

#### Free symbols / members of external scopes

- L42 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L68 _namespace_ `namespace UE`
- L68 _namespace_ `namespace UAF` (scope `UE`)
- L71 _typedef_ `using FChooserPlayerData = FUAFChooserPlayerTraitSharedData;` (scope `UE::UAF`) — Namespaced alias

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Public/UAFAnimChooser.h` (Public)


#### class `UUAFAnimChooserTable`  
`class UUAFAnimChooserTable : public UChooserTable`  
_L11-18_
- reflection: `UCLASS()`
- inherits: `UChooserTable`
- desc: UAF specific subclass of chooser table, for selecting assets which can generate anim graphs
- L15 _public function_ `UUAFAnimChooserTable()`
- L17 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooser/Public/UAFGraphFactoryAsset_Chooser.h` (Public)


#### struct `FUAFGraphFactoryAsset_Chooser`  
`struct FUAFGraphFactoryAsset_Chooser : public FUAFGraphFactoryAsset`  
_L14-31_
- reflection: `USTRUCT(DisplayName="Chooser Asset")`
- inherits: `FUAFGraphFactoryAsset`
- L18 _public prototype_ `FUAFGraphFactoryAsset_Chooser() = default;`
- L19 _public function_ `FUAFGraphFactoryAsset_Chooser(const UUAFAnimChooserTable* InChooserTable) : ChooserTable(InChooserTable)`
- L21 _public function_ `virtual bool Validate() const override`
- L23 _public prototype_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const override;`
- L26 _public member_ `TObjectPtr<const UUAFAnimChooserTable> ChooserTable;` — `UPROPERTY(EditAnywhere, Category = Chooser)`
- L30 _public member_ `EChooserEvaluationFrequency EvaluationFrequency = EChooserEvaluationFrequency::OnBecomeRelevant;` — `UPROPERTY(EditAnywhere, Category = Settings)` — How often the chooser should be evaluated
