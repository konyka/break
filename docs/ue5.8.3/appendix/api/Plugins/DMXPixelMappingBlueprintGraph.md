# Plugins / DMXPixelMappingBlueprintGraph

- module root: `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingBlueprintGraph`
- headers: 4; symbols: 58
- symbol kinds: class=4, function=22, member=8, prototype=23, struct=1
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, DMXPixelMappingRuntime, Engine, GraphEditor, InputCore, KismetCompiler, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingBlueprintGraph/Private/DMXPixelMappingPinFactory.h` (Private)


#### class `FDMXPixelMappingPinFactory`  
`class FDMXPixelMappingPinFactory : public FGraphPanelPinFactory`  
_L12-18_
- inherits: `FGraphPanelPinFactory`
- desc: Custom Pixel Mapping pins factory
- L16 _private prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingBlueprintGraph/Private/Widgets/SDMXPixelMappingComponentPin.h` (Private)


#### class `SDMXPixelMappingComponentPin`  
`template<typename TComponentClass> class SDMXPixelMappingComponentPin : public SGraphPin`  
_L18-233_
- inherits: `SGraphPin`
- desc: Cusotom widget for Pixel Mapping component pin.
- L22 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingComponentPin)`
- L23 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, UDMXPixelMapping* InDMXPixelMapping)`
- L41 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — Function to create class specific widget. @return Reference to the newly created widget object
- L93 _protected function_ `void ComboBoxSelectionChanged(TSharedPtr<FString> UserNameItem, ESelectInfo::Type SelectInfo)` — Function to set the newly selected index @param NameItem The newly selected item in the combo box @param SelectInfo Provides context on how the selection changed
- L105 _private function_ `TSharedRef<SWidget> GenerateComboBoxEntry(TSharedPtr<FString> UserName)`
- L112 _private function_ `FText GetSelectedUserName() const`
- L124 _private function_ `void SetNameToPin(const FName& Name)` — Set name from Combo Box to input pin
- L141 _private member_ `TWeakObjectPtr<UDMXPixelMapping> DMXPixelMappingWeakPtr;` — Weak pointer to Pixel Mapping Object
- L144 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;` — Reference to Combo Box object
- L146 _private member_ `TArray<TSharedPtr<FString>> UserNameList;`
- L232 _private member_ `FComponentUserNameTable NameTable;` — List of available component names

#### struct `SDMXPixelMappingComponentPin::FComponentUserNameTable`  
`struct FComponentUserNameTable`  
_L149-229_
- desc: Maps component FNames to the corresponding User Name displayed in pixel mapping designer
- L151 _public function_ `FComponentUserNameTable()`
- L154 _public function_ `FComponentUserNameTable(UDMXPixelMapping* PixelMapping)`
- L172 _public function_ `bool Contains(const FName& ComponentName) const`
- L180 _public function_ `void GetUserNames(TArray<TSharedPtr<FString>>& OutUserNames)`
- L189 _public function_ `FString GetUserName(const FName& ComponentName) const`
- L203 _public function_ `FName GetComponentName(const FString& UserName) const`
- L216 _public function_ `int32 Num() const`
- L221 _public function_ `TTuple<FName, FString> First() const`
- L228 _private member_ `TArray<TTuple<FName, FString>> ComponentUserNameArr;`

#### Free symbols / members of external scopes

- L47 _function_ `` (scope `SDMXPixelMappingComponentPin::GetDefaultValueWidget`)
- L68 _function_ `const TSharedPtr<FString>* SelectedUserNamePtr = UserNameList.FindByPredicate([UserName](const TSharedPtr<FString>& TestedUserName) { return TestedUserName->Equals(UserName); });` (scope `SDMXPixelMappingComponentPin::GetDefaultValueWidget`)
- L174 _function_ `int32 Index = ComponentUserNameArr.IndexOfByPredicate([&ComponentName](const TTuple<FName, FString>& ComponentUserKvp) { return ComponentUserKvp.Key == ComponentName; });` (scope `SDMXPixelMappingComponentPin::FComponentUserNameTable::Contains`)
- L191 _function_ `int32 Index = ComponentUserNameArr.IndexOfByPredicate([&ComponentName](const TTuple<FName, FString>& ComponentUserKvp) { return ComponentUserKvp.Key == ComponentName; });` (scope `SDMXPixelMappingComponentPin::FComponentUserNameTable::GetUserName`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingBlueprintGraph/Public/K2Node_PixelMappingBaseComponent.h` (Public)


#### class `UK2Node_PixelMappingBaseComponent`  
`class UK2Node_PixelMappingBaseComponent : public UK2Node`  
_L17-79_
- reflection: `UCLASS(abstract)`
- inherits: `UK2Node`
- desc: Base Pixel Mapping node. Never use directly
- L24 _public function_ `virtual bool IsNodePure() const override`
- L25 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L30 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L31 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L37 _public function_ `virtual void OnPixelMappingChanged(UDMXPixelMapping* InDMXPixelMapping)` — Listener of Pixel Mapping object changes.
- L40 _public prototype_ `UEdGraphPin* GetInPixelMappingPin() const;` — Pixel Mapping Input Pin
- L44 _protected prototype_ `UEdGraphPin* GetPixelMappingPin(const TArray<UEdGraphPin*>* InPinsToSearch = nullptr) const;` — Safe method to get Pixel Mapping pin. It skips the checked pointer
- L47 _protected prototype_ `void AddBlueprintAction(UClass* InClass, FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;` — Serves as an extensible way for new nodes
- L50 _protected prototype_ `void RefreshGraph();` — Asking to change blueprint graph
- L53 _protected prototype_ `void ModifyBlueprint();` — Mark Blueprint graph as Modified
- L56 _protected prototype_ `void TryModifyBlueprintOnNameChanged(UDMXPixelMapping* InDMXPixelMapping, UEdGraphPin* InPin);` — Modify blueprint if we have the component name change
- L59 _protected prototype_ `void TryRefreshGraphCheckInputPins(UEdGraphPin* TryPixelMappingPin, UEdGraphPin* TryComponentNamePin);` — Refresh blueprint graph if input pins is valid
- L62 _protected prototype_ `void ExecuteEarlyValidation(FCompilerResultsLog& MessageLog, UEdGraphPin* InComponentPin) const;` — Execute valisation for the connected pins
- L74 _protected prototype_ `void ExecuteExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const FName& SubsystemFuncitonName, UEdGraphPin* InComponentNamePin, UEdGraphPin* OutComponentPin);` — Add Execution for blueprint node That is the place where we set a compiler and spawn extra node for blueprint execution @param CompilerContext			Kismet blueprint compiler @param SourceGraph				Current blueprint graph pointer @param SubsystemFuncitonName		C++ subsustem function to execute @param InComponentNamePin		Input component FName pin pointer @param OutComponentPin			Out component UObject pin
- L78 _protected member_ `static const FName InPixelMappingPinName;` — Input Pixel Mapping pin name

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingBlueprintGraph/Public/K2Node_PixelMappingRendererComponent.h` (Public)


#### class `UK2Node_PixelMappingRendererComponent`  
`class UK2Node_PixelMappingRendererComponent : public UK2Node_PixelMappingBaseComponent`  
_L13-57_
- reflection: `UCLASS()`
- inherits: `UK2Node_PixelMappingBaseComponent`
- desc: Node for getting Renderer Component from PixelMapping object and Renderer FName
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L23 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* ChangedPin) override;`
- L27 _public function_ `virtual bool IsNodePure() const override`
- L28 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L29 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L30 _public prototype_ `virtual void EarlyValidation(class FCompilerResultsLog& MessageLog) const override;`
- L34 _public prototype_ `virtual void OnPixelMappingChanged(UDMXPixelMapping* InDMXPixelMapping) override;`
- L43 _public prototype_ `UEdGraphPin* GetInRendererComponentPin() const;` — Pointer to the input Renderer group pin. The pin holds the FName of the non Public UObject component. Since it not possible to save NonPublic UObject references outside uasset it should be used as FName
- L49 _public prototype_ `UEdGraphPin* GetOutRendererComponentPin() const;` — Pointer to the output Renderer group pin. It dynamically returns a pointer to Renderer Component by input FName of the component.
- L53 _public member_ `static const FName InRendererComponentPinName;` — Input Renderer Component pin name. It holds a FName of the component.
- L56 _public member_ `static const FName OutRendererComponentPinName;` — Output Renderer Component pin name. It holds a pointer to the component.
