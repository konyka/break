# Plugins / ModelContextProtocolEditor

- module root: `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor`
- headers: 7; symbols: 91
- symbol kinds: class=8, function=10, macro=3, member=12, namespace=4, prototype=43, struct=5, typedef=3, variable=3
- PrivateDependencyModuleNames: BlueprintGraph, CoreUObject, DeveloperSettings, EditorFramework, Engine, InputCore, Json, JsonUtilities, JsonUtilitiesEditor, KismetCompiler, Projects, Slate, SlateCore, ToolMenus, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: AssetDefinition, Blutility, Core, EngineAssetDefinitions, ModelContextProtocol, ModelContextProtocolEngine

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor/Private/ModelContextProtocolToolHashMappingCommandlet.h` (Private)


#### class `UModelContextProtocolToolHashMappingCommandlet`  
`class UModelContextProtocolToolHashMappingCommandlet : public UCommandlet`  
_L30-43_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Writes a JSON mapping of blake3 tool and toolset identifier hashes (as emitted by UE::ModelContextProtocol::Analytics::HashToolIdentifier) to their human-readable names. The mapping lets downstream consumers decode ToolNameHash / ToolsetNameHash fields in analytics events. Usage: UnrealEditor-Cmd.exe <uproject> <TargetName> -run=ModelContextProtocolToolHashMapping [-Output=<path>] [-TickEngineSeconds=<float>] [-Print] Default output path is <ProjectSavedDir>/ModelContextProtocol/ToolHashMapping.json. Only tools registered with IModelContextProtocolModule at enumeration time are captured. Toolsets packaged as explicitly-loaded Game Feature Plugins are not active by default and must be activated before enumeration via -ExecCmds (use the `LoadGameFeaturePlugin` console command). Because commandlets do not run the normal editor tick loop, the commandlet manually drives engine frames for -TickEngineSeconds (default 20.0) so async GFP activations and their downstream toolset registrations can complete before the mapping is built. Pass -TickEngineSeconds=0 to skip the loop entirely. The default is sized for a typical GFP activation; bump it higher for larger aggregates or cold caches. Example that activates a toolset aggregate GFP before enumerating: UnrealEditor-Cmd.exe <uproject> <EditorTarget> -run=ModelContextProtocolToolHashMapping -ExecCmds="LoadGameFeaturePlugin <YourToolsetsPluginName>"
- L36 _public prototype_ `virtual int32 Main(const FString& Params) override;`
- L42 _public prototype_ `static void BuildHashMaps(const TSet<FString>& Names, TSortedMap<FString, FString>& OutTools, TSortedMap<FString, FString>& OutToolsets);` — Builds the hash -> name maps from a deduplicated set of tool names. Exposed as a static method so tests can exercise the split-at-last-dot, top-level-sentinel, and sorted-output behavior without driving a full commandlet run.

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor/Private/ModelContextProtocolToolSearch.h` (Private)


#### struct `FListToolsetsTool`  
`struct FListToolsetsTool : IModelContextProtocolTool`  
_L28-39_
- inherits: `IModelContextProtocolTool`
- desc: Lists all available toolsets with their names and descriptions. Use this to discover what toolsets are available before describing or calling their tools.
- L30 _public prototype_ `explicit FListToolsetsTool(FListToolsetsDelegate InDelegate);`
- L32 _public function_ `virtual FString GetName() const override`
- L33 _public function_ `virtual FString GetDescription() const override`
- L34 _public prototype_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const override;`
- L35 _public prototype_ `virtual FModelContextProtocolToolResult Run(const TSharedPtr<FJsonObject>& Params) override;`
- L38 _private member_ `FListToolsetsDelegate ListDelegate;`

#### struct `FDescribeToolsetTool`  
`struct FDescribeToolsetTool : IModelContextProtocolTool`  
_L45-59_
- inherits: `IModelContextProtocolTool`
- desc: Returns detailed information about a specific toolset including all tool names, descriptions, and input schemas. Use this to inspect a toolset before calling its tools.
- L47 _public prototype_ `explicit FDescribeToolsetTool(FDescribeToolsetDelegate InDelegate);`
- L49 _public function_ `virtual FString GetName() const override`
- L50 _public function_ `virtual FString GetDescription() const override`
- L54 _public prototype_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const override;`
- L55 _public prototype_ `virtual FModelContextProtocolToolResult Run(const TSharedPtr<FJsonObject>& Params) override;`
- L58 _private member_ `FDescribeToolsetDelegate DescribeDelegate;`

#### struct `FCallTool`  
`struct FCallTool : IModelContextProtocolTool`  
_L66-80_
- inherits: `IModelContextProtocolTool`
- desc: Calls a single tool by name without registering it as a native MCP tool. Provide toolset_name to call a tool inside a toolset; omit it to call a top-level MCP tool. Use list_toolsets and describe_toolset to discover available tools and their input schemas.
- L68 _public prototype_ `explicit FCallTool(FCallToolDelegate InDelegate);`
- L70 _public function_ `virtual FString GetName() const override`
- L71 _public function_ `virtual FString GetDescription() const override`
- L75 _public prototype_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const override;`
- L76 _public prototype_ `virtual void RunAsync(const FModelContextProtocolToolRequestId& RequestId, const TSharedPtr<FJsonObject>& Params, const FResultCallback& OnComplete) override;`
- L79 _private member_ `FCallToolDelegate CallDelegate;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L10 _variable_ `inline constexpr TCHAR ListToolsetsName[] = TEXT("lis` (scope `UE::ModelContextProtocol`)
- L11 _variable_ `inline constexpr TCHAR DescribeToolsetName[] = TEXT("des` (scope `UE::ModelContextProtocol`)
- L12 _variable_ `inline constexpr TCHAR CallToolName[] = TEXT("cal` (scope `UE::ModelContextProtocol`)
- L16 _typedef_ `using FListToolsetsDelegate = TFunction<FString()>;` — Callback: returns a text listing of all available toolsets (name + description).
- L19 _typedef_ `using FDescribeToolsetDelegate = TFunction<TValueOrError<FString, FString>(const FString& ToolsetName)>;` — Callback: returns the full JSON schema for a named toolset, or an error string.
- L22 _typedef_ `using FCallToolDelegate = TFunction<void(const FString& ToolsetName, const FString& ToolName, const TSharedPtr<FJsonObject>& Arguments, const FModelContextProtocolToolRequestId& RequestId, const IModelContextProtocolTool::FResultCallback& OnComplete)>;` — Callback: dispatches a tool call. ToolsetName may be empty (top-level tool). Arguments may be null (interpreted as empty object). Result is delivered asynchronously via OnComplete.

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor/Private/ModelContextProtocolToolsetRegistryAdapter.h` (Private)


#### struct `FToolsetRegistryToolAdapter`  
`struct FToolsetRegistryToolAdapter : IModelContextProtocolTool`  
_L13-26_
- inherits: `IModelContextProtocolTool`
- desc: Adapts a ToolsetRegistry tool to the IModelContextProtocolTool interface. Created by the Editor module to bridge ToolsetRegistry tools into the MCP server.
- L15 _public prototype_ `FToolsetRegistryToolAdapter(const FString& InToolName, const FString& InDescription, TSharedPtr<FJsonObject> InInputSchema);`
- L17 _public function_ `virtual FString GetName() const override`
- L18 _public function_ `virtual FString GetDescription() const override`
- L19 _public function_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const override`
- L20 _public prototype_ `virtual void RunAsync(const FModelContextProtocolToolRequestId& RequestId, const TSharedPtr<FJsonObject>& Params, const FResultCallback& OnComplete) override;`
- L23 _private member_ `FString ToolName;`
- L24 _private member_ `FString Description;`
- L25 _private member_ `TSharedPtr<FJsonObject> InputSchema;`

#### struct `FToolsetRegistryToolAdapterManager`  
`struct FToolsetRegistryToolAdapterManager`  
_L33-64_
- desc: Registers and manages ToolsetRegistry tool adapters with the MCP module. In eager mode (bEnableToolSearch = false), every toolset tool is registered as a native MCP tool at startup. In tool-search mode (bEnableToolSearch = true), only list_toolsets, describe_toolset, and call_tool are registered; toolset tools are dispatched through call_tool without being registered.
- L35 _public function_ `~FToolsetRegistryToolAdapterManager()`
- L44 _public prototype_ `void RegisterTools();` — Enumerates ToolsetRegistry tools and registers them with the MCP module. In eager mode, registers all tool adapters directly. In tool-search mode, registers list_toolsets, describe_toolset, and call_tool for on-demand discovery and dispatch.
- L47 _public prototype_ `void DeregisterTools(bool bBroadcast = true);` — Removes all previously registered adapter tools. Optionally broadcasts tools/list_changed.
- L51 _private prototype_ `int32 RegisterToolsFromSchema(const FString& ToolsetSchemaJson);` — Register all tools from a toolset's JSON schema string. Returns the number of tools registered.
- L54 _private prototype_ `FString GetToolsetCatalogText() const;` — Returns a compact text listing of all toolsets (name + description).
- L57 _private prototype_ `TValueOrError<FString, FString> GetToolsetSchemaText(const FString& ToolsetName) const;` — Returns the full JSON schema for a named toolset, or an error.
- L60 _private prototype_ `void DispatchToolCall(const FString& ToolsetName, const FString& ToolName, const TSharedPtr<FJsonObject>& Arguments, const FModelContextProtocolToolRequestId& RequestId, const IModelContextProtocolTool::FResultCallback& OnComplete) const;` — Dispatches a tool call through ToolsetRegistry (when ToolsetName is non-empty) or through the MCP module's top-level tool table (otherwise). Result is delivered via OnComplete.
- L62 _private member_ `TArray<TSharedRef<FToolsetRegistryToolAdapter>> RegisteredAdapters;`
- L63 _private member_ `TArray<TSharedRef<IModelContextProtocolTool>> MetaTools;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor/Public/ModelContextProtocolAssetDefinitions.h` (Public)


#### class `UAssetDefinition_ModelContextProtocolToolLibraryBlueprint`  
`class UAssetDefinition_ModelContextProtocolToolLibraryBlueprint : public UAssetDefinition_Blueprint`  
_L12-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

#### class `UAssetDefinition_ModelContextProtocolEditorToolLibraryBlueprint`  
`class UAssetDefinition_ModelContextProtocolEditorToolLibraryBlueprint : public UAssetDefinition_Blueprint`  
_L25-35_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L30 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L31 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L32 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L33 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELCONTEXTPROTOCOLEDITOR_API`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor/Public/ModelContextProtocolEditor.h` (Public)


#### class `FModelContextProtocolEditorModule`  
`class FModelContextProtocolEditorModule : public IModuleInterface`  
_L10-25_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `void SetupEditorIntegration();`
- L21 _private member_ `FToolsetRegistryToolAdapterManager ToolsetRegistryAdapterManager;`
- L22 _private member_ `UE::ToolsetRegistry::FDelegateHandleRaii PostEngineInitHandle;`
- L23 _private member_ `FDelegateHandle OnRefreshToolsHandle;`
- L24 _private member_ `FDelegateHandle OnToolsetRegisteredHandle;`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor/Public/ModelContextProtocolEditorToolLibrary.h` (Public)


#### class `UModelContextProtocolEditorToolLibrary`  
`class UModelContextProtocolEditorToolLibrary : public UModelContextProtocolToolLibrary`  
_L23-26_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UModelContextProtocolToolLibrary`
- desc: Automatically registers an FModelContextProtocolLibraryTool for each public UFUNCTION on module load, using cached / cooked meta-data. UBlueprintFunctionLibrary specialization allows caching and cooking otherwise-editor-only UFUNCTION descriptions and parameter meta-data. Can be subclassed in either C++ or Blueprints. For Blueprints:	Create via Content Browser -> Add -> MCP Tool Library, then simply define public functions with a doxygen-style function tooltip.

#### class `UModelContextProtocolEditorToolLibraryBlueprint`  
`class UModelContextProtocolEditorToolLibraryBlueprint : public UEditorUtilityBlueprint`  
_L39-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorUtilityBlueprint`
- desc: Editor-specific UModelContextProtocolToolLibrary function library editor utility blueprint, allowing Editor-only BP node use in MCP tool functions. @see UModelContextProtocolToolLibraryBlueprint
- L43 _public prototype_ `UModelContextProtocolEditorToolLibraryBlueprint();`
- L47 _public prototype_ `virtual bool AlwaysCompileOnLoad() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditor/Public/ModelContextProtocolToolLibraryFactory.h` (Public)


#### class `UModelContextProtocolToolLibraryFactory`  
`class UModelContextProtocolToolLibraryFactory : public UBlueprintFactory`  
_L13-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFactory`
- L17 _public prototype_ `UModelContextProtocolToolLibraryFactory(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;` — UFactory interface
- L21 _public prototype_ `virtual FName GetNewAssetThumbnailOverride() const override;`
- L22 _public prototype_ `virtual FText GetToolTip() const override;`
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L24 _public prototype_ `virtual bool ConfigureProperties() override;`
- L25 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`

#### class `UModelContextProtocolEditorToolLibraryFactory`  
`class UModelContextProtocolEditorToolLibraryFactory : public UModelContextProtocolToolLibraryFactory`  
_L34-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModelContextProtocolToolLibraryFactory`
- desc: Editor-specific UModelContextProtocolToolLibrary factory which produces a UModelContextProtocolEditorToolLibraryBlueprint editor utility blueprint, allowing editor-specific BP node usage in tool function implementations.
- L38 _public prototype_ `UModelContextProtocolEditorToolLibraryFactory(const FObjectInitializer& ObjectInitializer);`
- L41 _public prototype_ `virtual FText GetDisplayName() const override;` — UFactory interface
- L42 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L43 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELCONTEXTPROTOCOLEDITOR_API`
