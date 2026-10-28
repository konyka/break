# Plugins / ChooserUncooked

- module root: `Plugins/Chooser/Source/ChooserUncooked`
- headers: 4; symbols: 121
- symbol kinds: class=5, enum=2, enumerator=4, function=14, member=15, namespace=2, prototype=79
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AssetDefinition, AssetTools, BlendStack, BlendStackEditor, BlueprintGraph, Core, CoreUObject, Engine, GameplayTags, KismetCompiler, UnrealEd
- PublicDependencyModuleNames: Chooser

### `Plugins/Chooser/Source/ChooserUncooked/Private/ChooserUncookedModule.h` (Private)


#### class `UE::Chooser::FChooserUncookedModule`  
`class FChooserUncookedModule : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- L14 _private prototype_ `virtual void StartupModule() override;`
- L15 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Chooser` (scope `UE`)

### `Plugins/Chooser/Source/ChooserUncooked/Private/EvaluateChooserNode.h` (Private)


#### enum `EEvaluateChooserMode`  
`enum class EEvaluateChooserMode`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `FirstResult`
- L21 _public enumerator_ `AllResults`

#### enum `EEvaluateChooserStructOutputMode`  
`enum class EEvaluateChooserStructOutputMode`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `Default`
- L28 _public enumerator_ `SingleOutputStruct`

#### class `UK2Node_EvaluateChooser`  
`class UK2Node_EvaluateChooser : public UK2Node`  
_L35-87_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UK2Node`
- desc: UK2Node_EvaluateChooser old implementation of this node for backwards compatibility - not currently accessible to create new instances in content
- L40 _private prototype_ `virtual void BeginDestroy() override;`
- L41 _private prototype_ `virtual void PostEditUndo() override;`
- L42 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _private prototype_ `virtual void PostLoad() override;`
- L47 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L48 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L49 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L50 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L51 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L52 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L53 _private prototype_ `virtual FText GetTooltipText() const override;`
- L54 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L58 _private function_ `virtual bool IsNodePure() const override`
- L59 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L60 _private prototype_ `virtual void PostReconstructNode() override;`
- L61 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L62 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L63 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L64 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L65 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L66 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L67 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L69 _private prototype_ `virtual void DestroyNode() override;`
- L74 _private prototype_ `void ChooserChanged();`
- L75 _private prototype_ `void ResultTypeChanged(const UClass*);`
- L76 _private prototype_ `void UnregisterChooserCallback();`
- L77 _private member_ `UChooserTable* CurrentCallbackChooser = nullptr;`
- L80 _private member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Category = "Chooser")`
- L83 _private member_ `EEvaluateChooserMode Mode;` — `UPROPERTY(EditAnywhere, Category = "Chooser")`
- L86 _private member_ `FText NodeTooltip;` — Tooltip text for this node.

#### class `UK2Node_EvaluateChooser2`  
`class UK2Node_EvaluateChooser2 : public UK2Node`  
_L93-157_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- desc: UK2Node_EvaluateChooser2 New Implementation of EvaluateChooser with support for passing in/out multiple objects and structs
- L98 _private prototype_ `virtual void BeginDestroy() override;`
- L99 _private prototype_ `virtual void PostEditUndo() override;`
- L100 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L101 _private prototype_ `virtual void PostLoad() override;`
- L105 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L106 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L107 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L108 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L109 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L110 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L111 _private prototype_ `virtual FText GetTooltipText() const override;`
- L112 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L113 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L117 _private function_ `virtual bool IsNodePure() const override`
- L118 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L119 _private prototype_ `virtual void PostReconstructNode() override;`
- L120 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L121 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L122 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L123 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L124 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L125 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L126 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L128 _private prototype_ `virtual void DestroyNode() override;`
- L133 _private prototype_ `void ChooserChanged();`
- L134 _private prototype_ `void ResultTypeChanged(const UClass*);`
- L135 _private prototype_ `void UnregisterChooserCallback();`
- L136 _private member_ `UChooserTable* CurrentCallbackChooser = nullptr;`
- L139 _private member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Category = "Chooser")`
- L142 _private member_ `EEvaluateChooserMode Mode;` — `UPROPERTY(EditAnywhere, Category = "Chooser", Meta = (HideEditConditionToggle, EditCondition="bShowModeSetting"))`
- L147 _private member_ `EEvaluateChooserStructOutputMode StructOutputMode = EEvaluateChooserStructOutputMode::SingleOutputStruct;` — `UPROPERTY(EditAnywhere, Category = "Chooser", Meta = (HideEditConditionToggle, EditCondition="bShowModeSetting"))` — This property exist for backwards compatibility with old content (where only single output struct was supported). New content should use "Default" setting to stay in sync with the regular output mode.
- L150 _private member_ `bool bReturnSoftObjectReference = false;` — `UPROPERTY(EditAnywhere, Category = "Chooser", Meta = (HideEditConditionToggle, EditCondition="bShowModeSetting"))`
- L153 _private member_ `bool bShowModeSetting = false;` — `UPROPERTY()`
- L156 _private member_ `FText NodeTooltip;` — Tooltip text for this node.

### `Plugins/Chooser/Source/ChooserUncooked/Private/GetChooserContextParametersNode.h` (Private)


#### class `UK2Node_GetChooserContextParameters`  
`class UK2Node_GetChooserContextParameters : public UK2Node`  
_L22-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- desc: UK2Node_GetChooserContextParameters exposes pins from a chooser context, based on a Chooser Signature
- L27 _private prototype_ `virtual void BeginDestroy() override;`
- L28 _private prototype_ `virtual void PostEditUndo() override;`
- L29 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L30 _private prototype_ `virtual void PostLoad() override;`
- L34 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L36 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L37 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L38 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L39 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L40 _private prototype_ `virtual FText GetTooltipText() const override;`
- L41 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L45 _private function_ `virtual bool IsNodePure() const override`
- L46 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L47 _private prototype_ `virtual void PostReconstructNode() override;`
- L48 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L49 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L50 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L51 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L52 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L53 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L54 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L56 _private prototype_ `virtual void DestroyNode() override;`
- L60 _private prototype_ `void ChooserSignatureChanged();`
- L61 _private prototype_ `void UnregisterCallback();`
- L62 _private member_ `UChooserSignature* CurrentCallbackObject = nullptr;`
- L65 _private member_ `TObjectPtr<UChooserSignature> ChooserSignature;` — `UPROPERTY(EditAnywhere, Category = "ChooserSignature")`
- L68 _private member_ `FText NodeTooltip;` — Tooltip text for this node.

### `Plugins/Chooser/Source/ChooserUncooked/Public/AnimGraphNode_ChooserPlayer.h` (Public)


#### class `UAnimGraphNode_ChooserPlayer`  
`class UAnimGraphNode_ChooserPlayer : public UAnimGraphNode_BlendStack_Base, public IHasContextClass`  
_L14-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_BlendStack_Base,IHasContextClass`
- L21 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L25 _public member_ `FAnimNode_ChooserPlayer Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L28 _public function_ `virtual TConstArrayView<FInstancedStruct> GetContextData() const` — IHasContextClass interface
- L32 _public prototype_ `virtual void PostPlacedNewNode() override;` — UEdGraphNode interface
- L33 _public prototype_ `virtual void PostPasteNode() override;`
- L34 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L35 _public prototype_ `virtual FText GetTooltipText() const override;`
- L36 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L37 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L38 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L41 _public function_ `virtual FAnimNode_BlendStack_Standalone* GetBlendStackNode() const override`
- L44 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — UAnimGraphNode_Base interface
- L45 _public prototype_ `virtual void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L50 _private prototype_ `void UpdateContextData();`
