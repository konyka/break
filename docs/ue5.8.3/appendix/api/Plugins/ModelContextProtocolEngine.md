# Plugins / ModelContextProtocolEngine

- module root: `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine`
- headers: 8; symbols: 141
- symbol kinds: class=5, delegate=1, enum=1, enumerator=5, function=34, macro=3, member=30, namespace=13, prototype=47, struct=2
- PrivateDependencyModuleNames: Analytics, AnalyticsET, BlueprintGraph, CoreUObject, Engine, HTTPServer, Json, JsonUtilities, JsonUtilitiesEditor, UnrealEd
- PublicDependencyModuleNames: Core, DeveloperSettings, ModelContextProtocol

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Private/EngineAnalyticsProviderProxy.h` (Private)


#### class `UE::ModelContextProtocol::Private::FEngineAnalyticsProviderProxy`  
`class FEngineAnalyticsProviderProxy : public IAnalyticsProviderET`  
_L28-80_
- inherits: `IAnalyticsProviderET`
- desc: IAnalyticsProviderET implementation dedicated to forwarding RecordEvent calls to FEngineAnalytics. FEngineAnalytics owns a real IAnalyticsProviderET internally but exposes it only by reference (FEngineAnalytics::GetProvider()). Wrapping that reference in a TSharedPtr with a no-op deleter produces a dangling reference if the underlying provider is destroyed first. This proxy owns no analytics state of its own (just the empty-default fields used when callers unexpectedly query the unused parts of the interface); callers own it via a normal TSharedPtr with clean lifetime semantics. RecordEvent is the only load-bearing method. The remaining IAnalyticsProviderET / IAnalyticsProvider surface is stubbed to safe defaults rather than forwarded: MCP never calls them, and forwarding would expose a silent path to mutate engine-global analytics state through a proxy that callers might mistake for a pass-through. This proxy is not intended to be a general-purpose FEngineAnalytics facade.
- L32 _public function_ `virtual void RecordEvent(FString&& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override`
- L40 _public function_ `virtual void RecordEvent(FString&& EventName, const TArray<FAnalyticsEventAttribute>& Attributes, EAnalyticsRecordEventMode Mode) override`
- L49 _public function_ `virtual void SetAppID(FString&&) override` — Unused IAnalyticsProviderET members: safe defaults, no forwarding.
- L50 _public function_ `virtual void SetAppVersion(FString&&) override`
- L51 _public function_ `virtual bool StartSession(FString, const TArray<FAnalyticsEventAttribute>&) override`
- L52 _public function_ `virtual bool ShouldRecordEvent(const FString&) const override`
- L53 _public function_ `virtual void SetUrlDomain(const FString&, const TArray<FString>&) override`
- L54 _public function_ `virtual void SetUrlPath(const FString&) override`
- L55 _public function_ `virtual void SetHeader(const FString&, const FString&) override`
- L56 _public function_ `virtual void SetEventCallback(const OnEventRecorded&) override`
- L57 _public function_ `virtual void BlockUntilFlushed(float) override`
- L58 _public function_ `virtual const FAnalyticsET::Config& GetConfig() const override`
- L59 _public function_ `virtual void SetShouldRecordEventFunc(const ShouldRecordEventFunction&) override`
- L60 _public function_ `virtual FOnPreAnalyticsEventProcessed& OnPreAnalyticsEventProcessed() override`
- L61 _public function_ `virtual FOnAnalyticsEventQueued& OnAnalyticsEventQueued() override`
- L64 _public function_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>&) override` — Unused IAnalyticsProvider members: safe defaults, no forwarding.
- L65 _public function_ `virtual void EndSession() override`
- L66 _public function_ `virtual FString GetSessionID() const override`
- L67 _public function_ `virtual bool SetSessionID(const FString&) override`
- L68 _public function_ `virtual void FlushEvents() override`
- L69 _public function_ `virtual void SetUserID(const FString&) override`
- L70 _public function_ `virtual FString GetUserID() const override`
- L71 _public function_ `virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&&) override`
- L72 _public function_ `virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const override`
- L73 _public function_ `virtual int32 GetDefaultEventAttributeCount() const override`
- L74 _public function_ `virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int) const override`
- L77 _private member_ `FAnalyticsET::Config EmptyConfig;`
- L78 _private member_ `FOnPreAnalyticsEventProcessed PreProcessedDelegate;`
- L79 _private member_ `FOnAnalyticsEventQueued QueuedDelegate;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::ModelContextProtocol`)

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolClientConfig.h` (Public)


#### enum `EModelContextProtocolClient`  
`enum class EModelContextProtocolClient : uint8`  
_L9-21_
- reflection: `UENUM()`
- desc: Supported AI coding clients for MCP configuration file generation.
- L12 _public enumerator_ `ClaudeCode` — Claude Code: `.mcp.json` in project root
- L14 _public enumerator_ `Cursor` — Cursor: `.cursor/mcp.json` in project root
- L16 _public enumerator_ `VSCode` — VS Code / Copilot: `.vscode/mcp.json` in project root
- L18 _public enumerator_ `Gemini` — Gemini CLI: `.gemini/settings.json` in project root
- L20 _public enumerator_ `Codex` — Codex CLI: `.codex/config.toml` in project root (TOML, write-once)

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L38 _prototype_ `bool WriteClientConfiguration(EModelContextProtocolClient Client, uint32 Port, const FString& UrlPath, const FString& BaseDirectory = FString());` (scope `UE::ModelContextProtocol`) — Generates an MCP client configuration file. JSON formats (ClaudeCode, Cursor, VSCode, Gemini) are created or updated, preserving existing entries. TOML format (Codex) is written once; logs error and returns false if file already exists. @param Client The target AI client. @param Port The MCP server port number. @param UrlPath The MCP server URL path (e.g., "/mcp"). @param BaseDirectory The root directory for config files. Defaults to FPaths::RootDir() in source builds or FPaths::ProjectDir() in installed builds if empty. @return true if the file was written successfully. @see EModelContextProtocolClient
- L48 _prototype_ `int32 WriteAllClientConfigurations(uint32 Port, const FString& UrlPath, const FString& BaseDirectory = FString());` (scope `UE::ModelContextProtocol`) — Generates MCP client configuration files for all supported clients. @param Port The MCP server port number. @param UrlPath The MCP server URL path (e.g., "/mcp"). @param BaseDirectory The root directory for config files. Defaults to FPaths::RootDir() in source builds or FPaths::ProjectDir() in installed builds if empty. @return Number of files successfully written.

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolEngineMetaData.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L20 _prototype_ `FModelContextProtocolFunctionMetaData CollectFunctionMetaData(const UFunction* Function, const FJsonSchemaPropertyFilter& PropertyFilter);` (scope `UE::ModelContextProtocol`) — Collects editor-only metadata for a UFunction, storing it in cookable form. @param Function The function to collect metadata for. @param PropertyFilter Property filter for schema generation. @return Collected function metadata.
- L29 _prototype_ `FJsonSchemaEditorMetadata ConvertToCachedEditorMetadata(const FModelContextProtocolFunctionMetaData& FunctionMetaData);` (scope `UE::ModelContextProtocol`) — Converts cookable function metadata back into FJsonSchemaEditorMetadata for passing to FJsonSchemaGenerator. @param FunctionMetaData The cookable metadata to convert. @return Engine editor metadata suitable for schema generation.

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolEngineToolResults.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L15 _prototype_ `FModelContextProtocolToolResult MakeImageResult(const UTexture2D* Texture, const TCHAR* ToFormatExtension = TEXT("jpeg"), EModelContextProtocolAudience Audience = EModelContextProtocolAudience::A` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#image-content
- L16 _prototype_ `FModelContextProtocolToolResult MakeImageResult(const FImageView& Image, const TCHAR* ToFormatExtension = TEXT("jpeg"), EModelContextProtocolAudience Audience = EModelContextProtocolAudience::A` (scope `UE::ModelContextProtocol`)
- L19 _prototype_ `FModelContextProtocolToolResult MakeAudioResult(USoundWave* SoundWave);` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#audio-content

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolSettings.h` (Public)


#### class `UModelContextProtocolSettings`  
`class UModelContextProtocolSettings : public UDeveloperSettings`  
_L18-47_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta=(DisplayName="Model Context Protocol"))`
- inherits: `UDeveloperSettings`
- L25 _public member_ `FString ServerUrlPath = UE::ModelContextProtocol::DefaultServerUrlPath;` — `UPROPERTY(Config, EditAnywhere, Category="Server")` — The URL base path to serve from e.g: "/mcp" -> http://localhost/mcp
- L28 _public prototype_ `static void EnforceValidServerUrlPath(FString& InOutPath);` — If InOutPath fails FHttpPath::IsValidPath, replaces it with UE::ModelContextProtocol::DefaultServerUrlPath and logs a warning. Exposed so the editor-side guard and direct tests can share the same logic.
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public member_ `uint32 ServerPortNumber = 8000;` — `UPROPERTY(Config, EditAnywhere, Category="Server")` — The port number to serve from e.g: 8000 -> http://localhost:8000/mcp
- L42 _public member_ `bool bAutoStartServer = false;` — `UPROPERTY(Config, EditAnywhere, Category="Server")` — If true, the HTTP server route will be automatically registered and HTTP listeners started during module startup.
- L46 _public member_ `bool bEnableToolSearch = true;` — `UPROPERTY(Config, EditAnywhere, Category="Tools")` — If true, tools/list returns only list_toolsets, describe_toolset, and call_tool. The LLM discovers toolset tools on demand and dispatches them through call_tool without ever registering them as native MCP tools. If false, every toolset tool is registered natively at startup.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L12 _prototype_ `FString GetServerUrlPath();` (scope `UE::ModelContextProtocol`)
- L13 _prototype_ `uint32 GetServerPortNumber();` (scope `UE::ModelContextProtocol`)
- L14 _prototype_ `bool ShouldAutoStartServer();` (scope `UE::ModelContextProtocol`)

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolToolAsyncAction.h` (Public)


#### class `UModelContextProtocolToolAsyncAction`  
`class UModelContextProtocolToolAsyncAction : public UCancellableAsyncAction`  
_L24-72_
- reflection: `UCLASS(Abstract, MinimalAPI, meta=(DeprecatedNode, DeprecationMessage="Use UToolsetDefinition (ToolsetRegistry plugin) instead."))`
- inherits: `UCancellableAsyncAction`
- desc: @deprecated Use UToolsetDefinition (ToolsetRegistry plugin) instead. UModelContextProtocolToolAsyncAction is maintained as a legacy fallback and will be removed in a future release.
- L29 _public prototype_ `virtual void SetReadyToDestroy() override;`
- L31 _public function_ `virtual FName GetToolFunctionName() const`
- L32 _public function_ `virtual FName GetToolResultPropertyName() const`
- L34 _public function_ `const FModelContextProtocolFunctionMetaData* GetToolFunctionMetaData() const`
- L35 _public function_ `const FModelContextProtocolFunctionMetaData* GetToolResultMetaData() const`
- L37 _public function_ `bool ShouldAutoRegisterTool() const`
- L39 _public prototype_ `void RegisterTool();`
- L40 _public prototype_ `void DeregisterTool();`
- L43 _public prototype_ `virtual void PostInitProperties() override;`
- L44 _public prototype_ `virtual void FinishDestroy() override;`
- L47 _public member_ `FOnModelContextProtocolAsyncToolComplete OnAsyncToolComplete;`
- L49 _public member_ `FModelContextProtocolToolRequestId ToolRequestId;`
- L57 _protected member_ `bool bAutoRegisterTool = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Model Context Protocol")` — If true, automatically registers on module load. If false, RegisterTool must manually be called.
- L60 _protected member_ `FModelContextProtocolFunctionMetaData ToolFunctionMetaData;` — `UPROPERTY(VisibleDefaultsOnly, Category = "Model Context Protocol")`
- L63 _protected member_ `FModelContextProtocolFunctionMetaData ToolResultMetaData;` — `UPROPERTY(VisibleDefaultsOnly, Category = "Model Context Protocol")`
- L65 _protected member_ `TSharedPtr<FModelContextProtocolAsyncActionTool> Tool;`
- L67 _protected member_ `IModelContextProtocolTool::FResultCallback OnComplete;`
- L70 _protected prototype_ `void CollectToolMetaData();`

#### struct `FModelContextProtocolAsyncActionTool`  
`struct FModelContextProtocolAsyncActionTool: public IModelContextProtocolTool`  
_L80-107_
- inherits: `IModelContextProtocolTool`
- desc: IModelContextProtocolTool implementation, automatically derived from reflected UModelContextProtocolToolAsyncAction, using UFUNCTION comment to derived tool & parameter descriptions. @see IModelContextProtocolTool @see UModelContextProtocolToolAsyncAction
- L83 _public prototype_ `FModelContextProtocolAsyncActionTool(UModelContextProtocolToolAsyncAction* InAsyncAction, UFunction* InFunction);`
- L86 _public prototype_ `virtual FString GetName() const override;`
- L87 _public prototype_ `virtual FString GetDescription() const override;`
- L88 _public prototype_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const override;`
- L89 _public prototype_ `virtual TSharedPtr<FJsonObject> GetOutputJsonSchema() const override;`
- L90 _public prototype_ `virtual void RunAsync(const FModelContextProtocolToolRequestId& RequestId, const TSharedPtr<FJsonObject>& Params, const FResultCallback& OnComplete) override;`
- L91 _public prototype_ `virtual void CancelAsync(const FModelContextProtocolToolRequestId& RequestId) override;`
- L92 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L97 _protected member_ `TObjectPtr<UModelContextProtocolToolAsyncAction> AsyncAction;` — UModelContextProtocolToolAsyncAction subclass CDO
- L98 _protected member_ `TObjectPtr<UFunction> Function;`
- L99 _protected member_ `TArray<TObjectPtr<UModelContextProtocolToolAsyncAction>> InProgressActions;`
- L101 _protected member_ `mutable TSharedPtr<FJsonObject> InputJsonSchema;`
- L102 _protected member_ `mutable TOptional<EModelContextProtocolToolResultType> ResultType;`
- L103 _protected member_ `mutable TSharedPtr<FJsonObject> OutputJsonSchema;`
- L104 _protected member_ `FStructOnScope FunctionParamsContainer;`
- L106 _protected prototype_ `void CacheResultTypeInfo() const;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MODELCONTEXTPROTOCOLENGINE_API`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelContextProtocolAsyncToolComplete, UModelContextProtocolToolAsyncAction* );`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModelContextProtocolAsyncToolComplete, UModelContextProtocolToolAsyncAction* );`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolToolLibrary.h` (Public)


#### class `UModelContextProtocolToolLibrary`  
`class UModelContextProtocolToolLibrary : public UBlueprintFunctionLibrary`  
_L33-79_
- reflection: `UCLASS(Abstract, MinimalAPI, meta=(DeprecatedNode, DeprecationMessage="Use UToolsetDefinition (ToolsetRegistry plugin) instead."))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Automatically registers an FModelContextProtocolLibraryTool for each public UFUNCTION on module load, using cached / cooked meta-data. UBlueprintFunctionLibrary specialization allows caching and cooking otherwise-editor-only UFUNCTION descriptions and parameter meta-data. Can be subclassed in either C++ or Blueprints. For Blueprints:	Create via Content Browser -> Add -> MCP Tool Library, then simply define public functions with a doxygen-style function tooltip. @deprecated Use UToolsetDefinition (ToolsetRegistry plugin) instead. UModelContextProtocolToolLibrary is maintained as a legacy fallback and will be removed in a future release.
- L37 _public function_ `const TMap<FName, FModelContextProtocolFunctionMetaData>& GetFunctionMetaData() const`
- L42 _public function_ `const FModelContextProtocolFunctionMetaData* FindFunctionMetaData(const FName& FunctionName) const`
- L47 _public function_ `bool ShouldAutoRegisterTools() const`
- L49 _public prototype_ `void RegisterTools();`
- L50 _public prototype_ `void DeregisterTools();`
- L53 _public prototype_ `virtual void PostInitProperties() override;`
- L54 _public prototype_ `virtual void PostLoad() override;`
- L55 _public prototype_ `virtual void FinishDestroy() override;`
- L65 _protected member_ `bool bAutoRegisterTools = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Model Context Protocol")` — If true, automatically registers an FModelContextProtocolLibraryTool for each public UFUNCTION on module load. If false, RegisterTools must manually be called.
- L69 _protected member_ `TMap<FName, FModelContextProtocolFunctionMetaData> FunctionMetaData;` — `UPROPERTY(VisibleDefaultsOnly, Category = "Model Context Protocol")` — Per-UFUNCTION cached meta-data to allow meta-data use on cooked platforms
- L71 _protected member_ `TArray<TSharedRef<FModelContextProtocolLibraryTool>> Tools;`
- L74 _protected prototype_ `virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;`
- L77 _protected prototype_ `void CollectFunctionMetaData();`

#### class `UModelContextProtocolToolLibraryBlueprint`  
`class UModelContextProtocolToolLibraryBlueprint : public UBlueprint`  
_L82-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprint`
- L86 _public prototype_ `UModelContextProtocolToolLibraryBlueprint();`
- L90 _public prototype_ `virtual bool AlwaysCompileOnLoad() const override;`

#### struct `FModelContextProtocolLibraryTool`  
`struct FModelContextProtocolLibraryTool : public IModelContextProtocolTool`  
_L101-124_
- inherits: `IModelContextProtocolTool`
- desc: IModelContextProtocolTool implementation, automatically derived from reflected UModelContextProtocolToolLibrary functions, using UFUNCTION comment to derived tool & parameter descriptions. @see IModelContextProtocolTool @see UModelContextProtocolToolLibrary
- L104 _public prototype_ `FModelContextProtocolLibraryTool(UModelContextProtocolToolLibrary* InLibrary, UFunction* InFunction);`
- L107 _public prototype_ `virtual FString GetName() const override;`
- L108 _public prototype_ `virtual FString GetDescription() const override;`
- L109 _public prototype_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const override;`
- L110 _public prototype_ `virtual TSharedPtr<FJsonObject> GetOutputJsonSchema() const override;`
- L111 _public prototype_ `virtual FModelContextProtocolToolResult Run(const TSharedPtr<FJsonObject>& Params) override;`
- L112 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L116 _protected member_ `TObjectPtr<UModelContextProtocolToolLibrary> Library;` — UModelContextProtocolToolLibrary subclass CDO
- L117 _protected member_ `TObjectPtr<UFunction> Function;`
- L118 _protected member_ `mutable TSharedPtr<FJsonObject> InputJsonSchema;`
- L119 _protected member_ `mutable TOptional<EModelContextProtocolToolResultType> ResultType;`
- L120 _protected member_ `mutable TSharedPtr<FJsonObject> OutputJsonSchema;`
- L121 _protected member_ `FStructOnScope FunctionParamsContainer;`
- L123 _protected prototype_ `void CacheResultTypeInfo() const;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MODELCONTEXTPROTOCOLENGINE_API`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolToolUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELCONTEXTPROTOCOLENGINE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L14 _prototype_ `EModelContextProtocolToolResultType GetToolResultType(FProperty* Property, const FModelContextProtocolFunctionMetaData* MetaData, TSharedPtr<FJsonObject>& OutSchema);` (scope `UE::ModelContextProtocol`)
- L15 _prototype_ `FModelContextProtocolToolResult GetToolResultFromType(EModelContextProtocolToolResultType ResultType, FProperty* Property, void* Container, uint16 ReturnValueOffset);` (scope `UE::ModelContextProtocol`)
