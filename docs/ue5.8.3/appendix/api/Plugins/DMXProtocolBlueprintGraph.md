# Plugins / DMXProtocolBlueprintGraph

- module root: `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolBlueprintGraph`
- headers: 5; symbols: 30
- symbol kinds: class=4, delegate=1, function=4, macro=2, member=4, prototype=15
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, CoreUObject, DMXProtocolEditor, Engine, GraphEditor, InputCore, Json, Kismet, KismetCompiler, KismetWidgets, Projects, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, DMXProtocol

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolBlueprintGraph/Private/DMXProtocolBlueprintGraphLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXProtocolBlueprintGraph, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXProtocolBlueprintGraph, Log, All);`
- L9 _macro_ `#define UE_LOG_DMXPROTOCOLBLUEPRINTGRAPH(Verbosity, Format, ...) \`
- L14 _macro_ `#define UE_CLOG_DMXPROTOCOLBLUEPRINTGRAPH(Conditional, Verbosity, Format, ...) \`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolBlueprintGraph/Private/Widgets/SDMXInputPortReferenceGraphPin.h` (Private)


#### class `SDMXInputPortReferenceGraphPin`  
`class SDMXInputPortReferenceGraphPin : public SGraphPin`  
_L13-37_
- inherits: `SGraphPin`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXInputPortReferenceGraphPin)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L26 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L30 _private prototype_ `void OnPortSelected() const;`
- L32 _private prototype_ `FDMXInputPortReference GetPinValue() const;`
- L34 _private prototype_ `void SetPinValue(const FDMXInputPortReference& InputPortReference, bool bMarkAsModified) const;`
- L36 _private member_ `TSharedPtr<SDMXPortSelector> PortSelector;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolBlueprintGraph/Private/Widgets/SDMXOutputPortReferenceGraphPin.h` (Private)


#### class `SDMXOutputPortReferenceGraphPin`  
`class SDMXOutputPortReferenceGraphPin : public SGraphPin`  
_L13-37_
- inherits: `SGraphPin`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXOutputPortReferenceGraphPin)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L26 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L30 _private prototype_ `void OnPortSelected() const;`
- L32 _private prototype_ `FDMXOutputPortReference GetPinValue() const;`
- L34 _private prototype_ `void SetPinValue(const FDMXOutputPortReference& OutputPortReference, bool bMarkAsModified = true) const;`
- L36 _private member_ `TSharedPtr<SDMXPortSelector> PortSelector;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolBlueprintGraph/Public/DMXProtocolBlueprintGraphModule.h` (Public)


#### class `FDMXProtocolBlueprintGraphModule`  
`class FDMXProtocolBlueprintGraphModule : public IModuleInterface`  
_L12-51_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L19 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public function_ `static FDMXProtocolBlueprintGraphModule& Get()`
- L30 _public function_ `static bool IsAvailable()`
- L42 _private prototype_ `void RegisterCustomClassLayout(FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate);` — Registers a custom class @param ClassName				The class name to register for property customization @param DetailLayoutDelegate	The delegate to call to get the custom detail layout instance
- L47 _private member_ `TSharedPtr<FDMXProtocolGraphPanelPinFactory> DMXProtocolGraphPanelPinFactory;` — FDMXProtocolName and Custom nodes Graph Pin customizations
- L50 _private member_ `TSet< FName > RegisteredClassNames;` — List of registered class that we must unregister when the module shuts down

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocolBlueprintGraph/Public/DMXProtocolGraphPanelPinFactory.h` (Public)


#### class `FDMXProtocolGraphPanelPinFactory`  
`class FDMXProtocolGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L9-14_
- inherits: `FGraphPanelPinFactory`
- L12 _private prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;`
