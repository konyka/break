# Plugins / ProxyTableUncooked

- module root: `Plugins/Chooser/Source/ProxyTableUncooked`
- headers: 2; symbols: 75
- symbol kinds: class=3, enum=2, enumerator=4, function=8, member=9, namespace=2, prototype=47
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, BlueprintGraph, Chooser, Core, CoreUObject, Engine, GameplayTags, KismetCompiler, UnrealEd
- PublicDependencyModuleNames: ProxyTable

### `Plugins/Chooser/Source/ProxyTableUncooked/Private/EvaluateProxyNode.h` (Private)


#### enum `EEvaluateProxyMode`  
`enum class EEvaluateProxyMode`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `FirstResult`
- L21 _public enumerator_ `AllResults`

#### enum `EEvaluateProxyStructOutputMode`  
`enum class EEvaluateProxyStructOutputMode`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `Default`
- L28 _public enumerator_ `SingleOutputStruct`

#### class `UK2Node_EvaluateProxy`  
`class UK2Node_EvaluateProxy : public UK2Node`  
_L32-82_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UK2Node`
- L35 _private prototype_ `virtual void BeginDestroy() override;`
- L38 _private prototype_ `virtual void PostEditUndo() override;`
- L39 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _private prototype_ `virtual void PostLoad() override;`
- L44 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L45 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L46 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L47 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L48 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L49 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L50 _private prototype_ `virtual FText GetTooltipText() const override;`
- L51 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L55 _private function_ `virtual bool IsNodePure() const override`
- L56 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L57 _private prototype_ `virtual void PostReconstructNode() override;`
- L58 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L59 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L60 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L61 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L62 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L63 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L64 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L66 _private prototype_ `virtual void DestroyNode() override;`
- L71 _private prototype_ `void ProxyChanged();`
- L72 _private prototype_ `void TypeChanged(const UClass*);`
- L73 _private prototype_ `void UnregisterProxyCallback();`
- L74 _private member_ `UProxyAsset* CurrentCallbackProxy = nullptr;`
- L78 _private member_ `TObjectPtr<UProxyAsset> Proxy;` — `UPROPERTY(EditAnywhere, Category = "Proxy")`
- L81 _private member_ `FText NodeTooltip;` — Tooltip text for this node.

#### class `UK2Node_EvaluateProxy2`  
`class UK2Node_EvaluateProxy2 : public UK2Node`  
_L88-149_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- desc: UK2Node_EvaluateChooser2 New Implementation of EvaluateChooser with support for passing in/out multiple objects and structs
- L93 _private prototype_ `virtual void BeginDestroy() override;`
- L94 _private prototype_ `virtual void PostEditUndo() override;`
- L95 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L96 _private prototype_ `virtual void PostLoad() override;`
- L100 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L101 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L102 _private function_ `virtual bool ShouldShowNodeProperties() const override`
- L103 _private prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L104 _private prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L105 _private prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L106 _private prototype_ `virtual FText GetTooltipText() const override;`
- L107 _private prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L108 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L112 _private function_ `virtual bool IsNodePure() const override`
- L113 _private function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L114 _private prototype_ `virtual void PostReconstructNode() override;`
- L115 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L116 _private prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L117 _private prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L118 _private prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L119 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L120 _private function_ `virtual int32 GetNodeRefreshPriority() const override`
- L121 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L123 _private prototype_ `virtual void DestroyNode() override;`
- L128 _private prototype_ `void ProxyChanged();`
- L129 _private prototype_ `void ResultTypeChanged(const UClass*);`
- L130 _private prototype_ `void UnregisterProxyCallback();`
- L131 _private member_ `UProxyAsset* CurrentCallbackProxy = nullptr;`
- L134 _private member_ `TObjectPtr<UProxyAsset> Proxy;` — `UPROPERTY(EditAnywhere, Category = "Proxy")`
- L137 _private member_ `EEvaluateProxyMode Mode;` — `UPROPERTY(EditAnywhere, Category = "Proxy")`
- L142 _private member_ `EEvaluateProxyStructOutputMode StructOutputMode = EEvaluateProxyStructOutputMode::SingleOutputStruct;` — `UPROPERTY(EditAnywhere, Category = "Proxy")` — This property exist for backwards compatibility with old content (where only single output struct was supported). New content should use "Default" setting to stay in sync with the regular output mode.
- L145 _private member_ `bool bReturnSoftObjectReference = false;` — `UPROPERTY(EditAnywhere, Category = "Proxy")`
- L148 _private member_ `FText NodeTooltip;` — Tooltip text for this node.

### `Plugins/Chooser/Source/ProxyTableUncooked/Private/ProxyTableUncookedModule.h` (Private)


#### class `UE::ProxyTable::FProxyTableUncookedModule`  
`class FProxyTableUncookedModule : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- L14 _private prototype_ `virtual void StartupModule() override;`
- L15 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ProxyTable` (scope `UE`)
