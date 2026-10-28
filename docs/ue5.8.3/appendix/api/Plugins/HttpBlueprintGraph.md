# Plugins / HttpBlueprintGraph

- module root: `Plugins/Web/HttpBlueprint/Source/HttpBlueprintGraph`
- headers: 5; symbols: 84
- symbol kinds: class=3, delegate=1, function=6, member=9, namespace=5, prototype=55, struct=5
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, Core, CoreUObject, EditorStyle, Engine, GraphEditor, HTTP, HttpBlueprint, InputCore, JsonBlueprintUtilities, Kismet, KismetCompiler, KismetWidgets, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprintGraph/Private/HttpBlueprintGraphLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpBlueprintEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHttpBlueprintEditor, Log, All);`

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprintGraph/Private/HttpRequestHeaderPresets.h` (Private)


#### struct `UE::HttpBlueprint::HeaderPresets::FBasePreset`  
`struct FBasePreset`  
_L9-32_
- L11 _public function_ `FBasePreset()`
- L20 _public function_ `void SetDefaults(const TMap<FString, FString>& AdditionalHeaders)`
- L31 _public member_ `TMap<FString, FString> HeaderPresets;`

#### struct `UE::HttpBlueprint::HeaderPresets::FJsonPreset`  
`struct FJsonPreset : FBasePreset`  
_L34-43_
- inherits: `FBasePreset`
- L36 _public function_ `FJsonPreset()`

#### struct `UE::HttpBlueprint::HeaderPresets::FHtmlPreset`  
`struct FHtmlPreset : FBasePreset`  
_L45-54_
- inherits: `FBasePreset`
- L47 _public function_ `FHtmlPreset()`

#### struct `UE::HttpBlueprint::HeaderPresets::FUrlPreset`  
`struct FUrlPreset : FBasePreset`  
_L56-65_
- inherits: `FBasePreset`
- L58 _public function_ `FUrlPreset()`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace HttpBlueprint` (scope `UE`)
- L7 _namespace_ `namespace HeaderPresets` (scope `UE::HttpBlueprint`)

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprintGraph/Private/K2Node_AsyncMakeRequestHeader.h` (Private)


#### class `UK2Node_AsyncMakeRequestHeader`  
`class UK2Node_AsyncMakeRequestHeader final : public UK2Node_BaseAsyncTask`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `UK2Node_BaseAsyncTask`
- L15 _public prototype_ `UK2Node_AsyncMakeRequestHeader();`
- L17 _public prototype_ `UEdGraphPin* GetVerbPin() const;`
- L18 _public prototype_ `UEdGraphPin* GetBodyPin() const;`
- L19 _public prototype_ `UEdGraphPin* GetHeaderPin() const;`
- L20 _public prototype_ `UEdGraphPin* GetUrlPin() const;`
- L23 _protected prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprintGraph/Private/K2Node_HttpRequest.h` (Private)


#### class `UK2Node_HttpRequest`  
`class UK2Node_HttpRequest : public UK2Node`  
_L12-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L17 _public prototype_ `explicit UK2Node_HttpRequest(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual void AllocateDefaultPins() override;` — Begin UEdGraphNode Interface
- L21 _public prototype_ `virtual FText GetTooltipText() const override;`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* Graph) const override;`
- L24 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L25 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L26 _public prototype_ `virtual void PinTypeChanged(UEdGraphPin* Pin) override;`
- L30 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;` — Begin UK2Node Interface
- L31 _public prototype_ `virtual void ReconstructNode() override;`
- L32 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L33 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L34 _public function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L35 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L36 _public prototype_ `virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;`
- L40 _protected prototype_ `void SetPinToolTip(UEdGraphPin* const& InPin, const FText& ToolTip) const;`
- L42 _protected prototype_ `void HandleBodyInputPin();`
- L43 _protected prototype_ `UEnum* GetVerbEnum() const;`
- L45 _protected prototype_ `void SyncBodyPinType(UEdGraphPin* const Pin) const;`
- L47 _protected prototype_ `UEdGraphPin* GetVerbPin() const;`
- L48 _protected prototype_ `UEdGraphPin* GetOutBodyPin() const;`
- L49 _protected prototype_ `UEdGraphPin* GetBodyPin() const;`
- L50 _protected prototype_ `UEdGraphPin* GetHeaderPin() const;`
- L51 _protected prototype_ `UEdGraphPin* GetOutHeaderPin() const;`
- L52 _protected prototype_ `UEdGraphPin* GetUrlPin() const;`
- L53 _protected prototype_ `UEdGraphPin* GetSuccessPin() const;`
- L54 _protected prototype_ `UEdGraphPin* GetErrorPin() const;`
- L58 _private member_ `TObjectPtr<UEnum> VerbEnum;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprintGraph/Private/K2Node_MakeRequestHeader.h` (Private)


#### struct `FOptionalPin`  
`struct FOptionalPin`  
_L18-33_
- reflection: `USTRUCT()`
- desc: Stores pin connections to restore after a node rebuild.
- L24 _public member_ `FName PinName;` — `UPROPERTY()` — Pin Name.
- L28 _public member_ `FString PinDefaultValue;` — `UPROPERTY()` — Default value, stored as a string.
- L32 _public member_ `FEdGraphPinReference LinkedTo;` — `UPROPERTY()` — Optional, use if something was previously linked to the pin.

#### class `UK2Node_MakeRequestHeader`  
`class UK2Node_MakeRequestHeader : public UK2Node , public IK2Node_AddPinInterface`  
_L37-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node,IK2Node_AddPinInterface`
- desc: Node to create an Http header, with presets.
- L44 _public prototype_ `UK2Node_MakeRequestHeader(const FObjectInitializer& ObjectInitializer);`
- L47 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;` — Begin UEdGraphNode Interface
- L48 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L49 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L50 _public prototype_ `virtual FText GetTooltipText() const override;`
- L51 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L55 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;` — Begin UK2Node Interface
- L56 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L57 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L58 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L59 _public prototype_ `virtual bool NodeCausesStructuralBlueprintChange() const override;`
- L60 _public prototype_ `virtual bool IsNodePure() const override;`
- L64 _public prototype_ `virtual bool CanAddPin() const override;` — Begin IK2Node_AddPinInterface
- L65 _public prototype_ `virtual bool CanRemovePin(const UEdGraphPin* Pin) const override;`
- L66 _public prototype_ `virtual void AddInputPin() override;`
- L67 _public prototype_ `virtual void RemoveInputPin(UEdGraphPin* Pin) override;`
- L71 _public prototype_ `UEdGraphPin* GetOutputPin() const;` — Returns the singular output pin containing the created http header.
- L75 _protected prototype_ `void ConstructDefaultPinsForPreset();` — Creates the default pin layout for the currently selected preset.
- L78 _protected prototype_ `void SyncPinNames();` — Updates the pin names according to their type and input index.
- L81 _protected prototype_ `virtual void GetKeyAndValuePins(TArrayView<UEdGraphPin*> InPins, TArray<UEdGraphPin*>& KeyPins, TArray<UEdGraphPin*>& ValuePins) const;` — Separates and returns the Key and Value pins corresponding to each input Key/Value pair.
- L84 _protected prototype_ `void ForEachInputPin(TArrayView<UEdGraphPin*> InPins, TUniqueFunction<void(UEdGraphPin*,int32)>&& PinFunc);` — Iterates over the provided Pins.
- L87 _protected prototype_ `static FOptionalPin MakeOptionalPin(UEdGraphPin* InPinToCopy);` — Creates a copy of the input Pin as an Optional Pin.
- L91 _private member_ `TObjectPtr<UEnum> PresetEnum;` — The UEnum type containing preset names.
- L95 _private member_ `int32 PresetEnumIndex;` — `UPROPERTY()` — The currently selected preset index.
- L99 _private member_ `int32 NumInputs;` — `UPROPERTY()` — Number of key/value inputs.
- L103 _private member_ `TArray<FOptionalPin> OptionalPins;` — `UPROPERTY()` — Used to store hidden or pins to be later restored.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`
