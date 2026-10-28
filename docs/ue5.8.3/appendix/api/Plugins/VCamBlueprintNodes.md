# Plugins / VCamBlueprintNodes

- module root: `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamBlueprintNodes`
- headers: 4; symbols: 41
- symbol kinds: class=3, delegate=1, function=6, member=2, prototype=29
- PrivateDependencyModuleNames: BlueprintGraph, CoreUObject, Engine, InputCore, Slate, SlateCore, VCamCore
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamBlueprintNodes/Private/SwitchNode/VCamK2Node_SwitchConnectionSystemBase.h` (Private)


#### class `UVCamK2Node_SwitchConnectionSystemBase`  
`class UVCamK2Node_SwitchConnectionSystemBase : public UK2Node_Switch`  
_L15-66_
- reflection: `UCLASS(Abstract)`
- inherits: `UK2Node_Switch`
- desc: Base functionality for a switch node for the connections & connection points system. It updates automatically when connections or connections points are added from a target object. Subclasses define how to obtain connections & connection points.
- L20 _public prototype_ `UVCamK2Node_SwitchConnectionSystemBase();`
- L22 _public prototype_ `void RefreshPins();`
- L25 _public prototype_ `virtual void BeginDestroy() override;`
- L26 _public prototype_ `virtual void PostLoad() override;`
- L27 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L32 _public prototype_ `virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;`
- L33 _public prototype_ `virtual void ReconstructNode() override;`
- L34 _public function_ `virtual bool CanEverInsertExecutionPin() const override`
- L35 _public function_ `virtual bool CanEverRemoveExecutionPin() const override`
- L36 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L40 _public prototype_ `virtual FEdGraphPinType GetPinType() const override;` — UK2Node_Switch Interface
- L41 _public function_ `virtual bool SupportsAddPinButton() const override`
- L46 _protected function_ `virtual bool SupportsBlueprintClass(UClass* Class) const`
- L47 _protected function_ `virtual TArray<FName> GetPinsToCreate() const`
- L50 _protected prototype_ `virtual void CreateSelectionPin() override;`
- L51 _protected prototype_ `virtual void CreateCasePins() override;`
- L56 _private member_ `FDelegateHandle DelegateHandle;`
- L58 _private prototype_ `void RemoveOrOrphanInvalidCases(const TArray<FName>& PinData);`
- L59 _private prototype_ `void AddMissingCasePins(const TArray<FName>& PinData);`
- L60 _private prototype_ `void SortCasePinsToHaveSameOrderAsPinData(const TArray<FName>& PinData);`
- L62 _private prototype_ `void SetupBlueprintModifiedCallbacks();`
- L63 _private prototype_ `void CleanUpCallbacks();`
- L65 _private prototype_ `void OnObjectTransacted(UObject* Object, const class FTransactionObjectEvent&);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamBlueprintNodes/Private/SwitchNode/VCamK2Node_SwitchOnModifierConnectionPoints.h` (Private)


#### class `UVCamK2Node_SwitchOnModifierConnectionPoints`  
`class UVCamK2Node_SwitchOnModifierConnectionPoints : public UVCamK2Node_SwitchConnectionSystemBase`  
_L14-32_
- reflection: `UCLASS()`
- inherits: `UVCamK2Node_SwitchConnectionSystemBase`
- L20 _protected prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L21 _protected prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _protected prototype_ `virtual bool SupportsBlueprintClass(UClass*) const override;`
- L26 _protected prototype_ `virtual TArray<FName> GetPinsToCreate() const override;`
- L31 _private prototype_ `void AccessBlueprintCDO(TFunctionRef<void(UVCamModifier*)> Func) const;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamBlueprintNodes/Private/SwitchNode/VCamK2Node_SwitchOnWidgetConnections.h` (Private)


#### class `UVCamK2Node_SwitchOnWidgetConnections`  
`class UVCamK2Node_SwitchOnWidgetConnections : public UVCamK2Node_SwitchConnectionSystemBase`  
_L15-43_
- reflection: `UCLASS()`
- inherits: `UVCamK2Node_SwitchConnectionSystemBase`
- L22 _public member_ `FVCamChildWidgetReference TargetWidget;` — `UPROPERTY(EditAnywhere, Category = PinOptions)` — A child VCamWidget from which to generate the pins. If left None, this Blueprint's widget will be used.
- L27 _protected prototype_ `virtual FText GetTooltipText() const override;` — UEdGraphNode interface
- L28 _protected prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L32 _protected prototype_ `virtual bool SupportsBlueprintClass(UClass*) const override;`
- L33 _protected prototype_ `virtual TArray<FName> GetPinsToCreate() const override;`
- L37 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L42 _private prototype_ `void AccessBlueprintCDO(TFunctionRef<void(UVCamWidget*)> Func) const;`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamBlueprintNodes/Private/VCamBlueprintNodesLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamBlueprintNodes, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamBlueprintNodes, Log, All);`
