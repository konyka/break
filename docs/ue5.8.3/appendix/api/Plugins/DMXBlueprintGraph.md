# Plugins / DMXBlueprintGraph

- module root: `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph`
- headers: 13; symbols: 151
- symbol kinds: class=12, delegate=2, function=14, macro=2, member=16, prototype=105
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, CoreUObject, DMXEditor, EditorFramework, Engine, GraphEditor, InputCore, Json, Kismet, KismetCompiler, KismetWidgets, Projects, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, DMXProtocol, DMXRuntime

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Private/Customizations/K2Node_CastPatchToTypeCustomization.h` (Private)


#### class `K2Node_CastPatchToTypeCustomization`  
`class K2Node_CastPatchToTypeCustomization : public IDetailCustomization`  
_L12-33_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L23 _private prototype_ `FReply ExposeAttributesClicked();`
- L25 _private prototype_ `FReply ResetAttributesClicked();`
- L27 _private prototype_ `UDEPRECATED_K2Node_CastPatchToType* GetK2Node_CastPatchToType() const;`
- L32 _private member_ `IDetailLayoutBuilder* DetailLayout;` — Cached off reference to the layout builder

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Private/Customizations/K2Node_GetDMXAttributeValuesCustomization.h` (Private)


#### class `FK2Node_GetDMXAttributeValuesCustomization`  
`class FK2Node_GetDMXAttributeValuesCustomization : public IDetailCustomization`  
_L12-36_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L24 _private prototype_ `FReply ExposeAttributesClicked();` — Handles the Expose button's on click event
- L27 _private prototype_ `FReply ResetAttributesClicked();` — Handles the Reset button's on click event
- L30 _private prototype_ `UK2Node_GetDMXAttributeValues* GetK2Node_DMXAttributeValues() const;` — Get the pointer to GetDMXAttributeValues node
- L35 _private member_ `IDetailLayoutBuilder* DetailLayout;` — Cached off reference to the layout builder

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Private/DMXBlueprintGraphLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXBlueprintGraph, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXBlueprintGraph, Log, All);`
- L9 _macro_ `#define UE_LOG_DMXBLUEPRINTGRAPH(Verbosity, Format, ...) \`
- L14 _macro_ `#define UE_CLOG_DMXBLUEPRINTGRAPH(Conditional, Verbosity, Format, ...) \`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Private/Widgets/SDMXAttributeNameGraphPin.h` (Private)


#### class `SDMXAttributeNameGraphPin`  
`class SDMXAttributeNameGraphPin : public SGraphPin`  
_L10-31_
- inherits: `SGraphPin`
- L14 _public function_ `SLATE_BEGIN_ARGS(SDMXAttributeNameGraphPin)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L27 _private prototype_ `FName GetValue() const;` — Gets the currently selected value
- L30 _private prototype_ `void SetValue(FName NewValue);` — Sets the currently selected value

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Private/Widgets/SDMXEntityReferenceGraphPin.h` (Private)


#### class `SDMXEntityReferenceGraphPin`  
`class SDMXEntityReferenceGraphPin : public SGraphPin`  
_L17-45_
- inherits: `SGraphPin`
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXEntityReferenceGraphPin)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L32 _private prototype_ `FDMXEntityReference GetPinValue() const;`
- L33 _private prototype_ `void SetPinValue(const FDMXEntityReference& NewEntityRef) const;`
- L35 _private prototype_ `TWeakObjectPtr<UDMXEntity> GetEntity() const;`
- L36 _private prototype_ `void OnEntitySelected(UDMXEntity* NewEntity) const;`
- L37 _private prototype_ `TSubclassOf<UDMXEntity> GetEntityType() const;`
- L38 _private prototype_ `TWeakObjectPtr<UDMXLibrary> GetDMXLibrary() const;`
- L40 _private prototype_ `FLinearColor GetComboForeground() const;`
- L43 _private prototype_ `TWeakObjectPtr<UObject> GetCurrentDMXLibrary() const;`
- L44 _private prototype_ `void OnDMXLibrarySelected(const FAssetData& InAssetData) const;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEntitySelected, UDMXEntity*);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnEntitySelected, UDMXEntity*);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Private/Widgets/SDMXFixtureCategoryGraphPin.h` (Private)


#### class `SDMXFixtureCategoryGraphPin`  
`class SDMXFixtureCategoryGraphPin : public SGraphPin`  
_L10-31_
- inherits: `SGraphPin`
- L14 _public function_ `SLATE_BEGIN_ARGS(SDMXFixtureCategoryGraphPin)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L27 _private prototype_ `FName GetValue() const;` — Gets the currently selected value
- L30 _private prototype_ `void SetValue(FName NewValue);` — Sets the currently selected value

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Private/Widgets/SNullGraphPin.h` (Private)


#### class `SNullGraphPin`  
`class SNullGraphPin : public SGraphPin`  
_L13-26_
- inherits: `SGraphPin`
- desc: Creates an empty widget for the pin, so the user can't edit the pin's default value. Useful for UObject pointer pins that would otherwise display an asset picker.
- L17 _public function_ `SLATE_BEGIN_ARGS(SNullGraphPin)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L24 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Public/DMXBlueprintGraphModule.h` (Public)


#### class `FDMXBlueprintGraphModule`  
`class FDMXBlueprintGraphModule : public IModuleInterface`  
_L14-62_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L20 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public function_ `static FDMXBlueprintGraphModule& Get()`
- L31 _public function_ `static bool IsAvailable()`
- L37 _private prototype_ `void RegisterObjectCustomizations();`
- L45 _private prototype_ `void RegisterCustomClassLayout(FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate);` — Registers a custom class @param ClassName				The class name to register for property customization @param DetailLayoutDelegate	The delegate to call to get the custom detail layout instance
- L55 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* InFixtureType);` — Called when a fixture type changed @param	InFixtureType	Fixture type UObject @param	InMode			Changed mode
- L58 _private member_ `TSharedPtr<FDMXGraphPanelPinFactory> DMXGraphPanelPinFactory;` — FDMXProtocolName and Custom nodes Graph Pin customizations
- L61 _private member_ `TSet< FName > RegisteredClassNames;` — List of registered class that we must unregister when the module shuts down

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Public/DMXGraphPanelPinFactory.h` (Public)


#### class `FDMXGraphPanelPinFactory`  
`class FDMXGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L9-14_
- inherits: `FGraphPanelPinFactory`
- L12 _private prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Public/K2Node_CastPatchToType.h` (Public)


#### class `UDEPRECATED_K2Node_CastPatchToType`  
`class UDEPRECATED_K2Node_CastPatchToType : public UK2Node_EditablePinBase`  
_L27-88_
- reflection: `UCLASS(Deprecated)`
- inherits: `UK2Node_EditablePinBase`
- desc: k2Node that checks if a FixturePatch is of a given FixtureType, and if it succeed, lets you grab the function values from the patch
- L34 _public member_ `static const FName InputPinName_FixturePatch;`
- L35 _public member_ `static const FName InputPinName_FixtureTypeRef;`
- L37 _public member_ `static const FName OutputPinName_AttributesMap;`
- L42 _public member_ `bool bIsExposed;` — `UPROPERTY()`
- L46 _public prototype_ `UDEPRECATED_K2Node_CastPatchToType();`
- L49 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L55 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L56 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L60 _public function_ `virtual bool IsNodePure() const override`
- L61 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L62 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L63 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L64 _public prototype_ `virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;`
- L68 _public prototype_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;`
- L69 _public prototype_ `virtual bool ModifyUserDefinedPinDefaultValue(TSharedPtr<FUserPinInfo> PinInfo, const FString& NewDefaultValue) override;`
- L72 _public function_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override` — We only override this to return true, otherwise we can't create the user defined pins for the Attributes
- L78 _public prototype_ `void ExposeAttributes();` — `UFUNCTION()`
- L81 _public prototype_ `void ResetAttributes();` — `UFUNCTION()`
- L83 _public prototype_ `UDMXEntityFixtureType* GetSelectedFixtureType();`
- L85 _public prototype_ `FString GetFixturePatchValueAsString() const;`
- L87 _public function_ `bool IsExposed() const`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Public/K2Node_GetDMXAttributeValues.h` (Public)


#### class `UK2Node_GetDMXAttributeValues`  
`class UK2Node_GetDMXAttributeValues : public UK2Node_EditablePinBase`  
_L22-102_
- reflection: `UCLASS()`
- inherits: `UK2Node_EditablePinBase`
- L28 _public prototype_ `UK2Node_GetDMXAttributeValues();`
- L31 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L32 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L33 _public prototype_ `virtual void PostPasteNode() override;`
- L34 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L38 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L39 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L40 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L41 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L45 _public function_ `virtual bool ShouldUseConstRefParams() const override`
- L46 _public prototype_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;`
- L47 _public prototype_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;`
- L48 _public prototype_ `virtual bool ModifyUserDefinedPinDefaultValue(TSharedPtr<FUserPinInfo> PinInfo, const FString& NewDefaultValue) override;`
- L52 _public prototype_ `void OnFixturePatchChanged();` — Triggers when FixturePatch from input pin has been changed
- L54 _public prototype_ `void RemovePinsRecursive(UEdGraphPin* Pin);`
- L55 _public prototype_ `void RemoveOutputPin(UEdGraphPin* Pin);`
- L63 _public prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* InFixtureType);` — Called when the Fixture Type changed @param	InFixtureType		The changed Fixture Type
- L67 _public prototype_ `void OnDataTypeChanged(const UDMXEntityFixtureType* InFixtureType, const FDMXFixtureMode& InMode);` — `UE_DEPRECATED(5.0, "Replaced in favor of the more generic OnFixtureTypeChanged.")` — DEPRECATED 5.0
- L70 _public function_ `bool IsExposed() const`
- L72 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatchFromPin() const;`
- L74 _public prototype_ `UEdGraphPin* GetInputDMXFixturePatchPin() const;`
- L75 _public prototype_ `UEdGraphPin* GetOutputAttributesMapPin() const;`
- L76 _public prototype_ `UEdGraphPin* GetOutputIsSuccessPin() const;`
- L79 _public prototype_ `void ExposeAttributes();` — Expose DMX function pins from fixture patch active mode
- L82 _public prototype_ `void ResetAttributes();` — Removes DMX function node pins
- L86 _private prototype_ `FName GetPinName(const FDMXFixtureFunction& Function);` — Get pin name based on FixtureFunction input
- L89 _private prototype_ `const FDMXFixtureMode* GetActiveFixtureMode() const;` — Get pinter to active mode, never cache this pointer and keep it dynamic
- L92 _private prototype_ `UDMXEntityFixtureType* GetParentFixtureType() const;` — Get the fixture type from active fixture mode
- L95 _public member_ `static const FName InputDMXFixturePatchPinName;`
- L96 _public member_ `static const FName OutputAttributesMapPinName;`
- L97 _public member_ `static const FName OutputIsSuccessPinName;`
- L101 _public member_ `bool bIsExposed;` — `UPROPERTY()`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Public/K2Node_GetDMXFixturePatch.h` (Public)


#### class `UK2Node_GetDMXFixturePatch`  
`class UK2Node_GetDMXFixturePatch : public UK2Node`  
_L17-58_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L24 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L35 _public function_ `virtual bool IsNodePure() const override`
- L36 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L37 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L38 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _public prototype_ `UEdGraphPin* GetInputDMXFixturePatchPin() const;`
- L43 _public prototype_ `UEdGraphPin* GetOutputDMXFixturePatchPin() const;`
- L46 _public prototype_ `FString GetFixturePatchValueAsString() const;` — Gets the DMX Fixture Patch pin value as String
- L48 _public prototype_ `FDMXEntityFixturePatchRef GetFixturePatchRefFromPin() const;` — Gets the DMX Fixture Patch Reference from input pin
- L50 _public prototype_ `void SetInFixturePatchPinValue(const FDMXEntityFixturePatchRef& InPatchRef) const;` — Updates values in the Fixture Patch input pin struct
- L53 _protected prototype_ `void NotifyInputChanged();`
- L56 _public member_ `static const FName InputDMXFixturePatchPinName;`
- L57 _public member_ `static const FName OutputDMXFixturePatchPinName;`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXBlueprintGraph/Public/K2Node_GetDMXFixtureType.h` (Public)


#### class `UK2Node_GetDMXFixtureType`  
`class UK2Node_GetDMXFixtureType : public UK2Node`  
_L17-55_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L24 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L28 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _public prototype_ `virtual FText GetTooltipText() const override;`
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L35 _public function_ `virtual bool IsNodePure() const override`
- L36 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L37 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L38 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _public prototype_ `UEdGraphPin* GetInputDMXFixtureTypePin() const;`
- L43 _public prototype_ `UEdGraphPin* GetOutputDMXFixtureTypePin() const;`
- L46 _public prototype_ `FString GetFixtureTypeValueAsString() const;` — Gets the DMX Fixture Type pin value as String
- L48 _public prototype_ `FDMXEntityFixtureTypeRef GetFixtureTypeRefFromPin() const;` — Gets the DMX Fixture Type Reference from input pin
- L50 _public prototype_ `void SetInFixtureTypePinValue(const FDMXEntityFixtureTypeRef& InTypeRef) const;` — Updates values in the Fixture Type input pin struct
- L53 _public member_ `static const FName InputDMXFixtureTypePinName;`
- L54 _public member_ `static const FName OutputDMXFixtureTypePinName;`
