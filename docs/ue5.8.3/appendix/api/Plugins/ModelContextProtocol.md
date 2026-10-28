# Plugins / ModelContextProtocol

- module root: `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol`
- headers: 13; symbols: 274
- symbol kinds: class=3, delegate=1, enum=4, enumerator=17, externvar=4, function=19, macro=9, member=70, namespace=11, prototype=102, struct=26, typedef=1, variable=7
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Analytics, AnalyticsET, Core, HTTPServer, Json, JsonUtilities

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Private/ModelContextProtocolModule.h` (Private)


#### class `FModelContextProtocolModule`  
`class FModelContextProtocolModule : public IModelContextProtocolModule, FGCObject`  
_L14-63_
- inherits: `IModelContextProtocolModule,FGCObject`
- L18 _public prototype_ `virtual const TArray<TSharedRef<IModelContextProtocolTool>>& GetTools() const override;`
- L19 _public prototype_ `[[nodiscard]] virtual TSharedPtr<IModelContextProtocolTool> FindTool(const FString& ToolName) const override;`
- L20 _public prototype_ `virtual bool AddTool(const TSharedRef<IModelContextProtocolTool>& Tool) override;`
- L21 _public prototype_ `virtual bool RemoveTool(const TSharedRef<IModelContextProtocolTool>& Tool) override;`
- L22 _public function_ `virtual FOnRefreshTools& OnRefreshTools() override`
- L23 _public prototype_ `virtual void RefreshTools() override;`
- L25 _public prototype_ `[[nodiscard]] virtual FModelContextProtocolServer* GetServer() override;`
- L26 _public prototype_ `virtual void StartServer(uint32 Port = UE::ModelContextProtocol::DefaultServerPort, const FString& UrlPath = UE::ModelContextProtocol::DefaultServerUrlPath) override;`
- L27 _public prototype_ `virtual void StopServer() override;`
- L29 _public prototype_ `virtual void SetAnalyticsProvider(const TSharedPtr<IAnalyticsProviderET>& InAnalyticsProvider) override;`
- L30 _public prototype_ `[[nodiscard]] virtual TSharedPtr<IAnalyticsProviderET> GetAnalyticsProvider() const override;`
- L31 _public prototype_ `virtual void SetAnalyticsEventNamespace(const FString& InNamespace) override;`
- L32 _public prototype_ `[[nodiscard]] virtual FString GetAnalyticsEventNamespace() const override;`
- L33 _public prototype_ `virtual void RecordAnalyticsEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;`
- L35 _public prototype_ `virtual const TArray<TSharedRef<IModelContextProtocolResourceProvider>>& GetResourceProviders() const override;`
- L36 _public prototype_ `virtual void AddResourceProvider(const TSharedRef<IModelContextProtocolResourceProvider>& ResourceProvider) override;`
- L37 _public prototype_ `virtual bool RemoveResourceProvider(const TSharedRef<IModelContextProtocolResourceProvider>& ResourceProvider) override;`
- L41 _public prototype_ `virtual void StartupModule() override;`
- L42 _public prototype_ `virtual void ShutdownModule() override;`
- L46 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L47 _public prototype_ `virtual FString GetReferencerName() const override;`
- L51 _protected member_ `FOnRefreshTools OnRefreshToolsDelegate;`
- L52 _protected member_ `TArray<TSharedRef<IModelContextProtocolTool>> Tools;`
- L53 _protected member_ `TArray<TSharedRef<IModelContextProtocolResourceProvider>> ResourceProviders;`
- L54 _protected member_ `TUniquePtr<FModelContextProtocolServer> Server;`
- L55 _protected member_ `FDelegateHandle OnRefreshToolsDelegateHandle;`
- L60 _protected member_ `mutable FCriticalSection AnalyticsMutex;` — Guards AnalyticsProvider and AnalyticsEventNamespace. Reads (RecordAnalyticsEvent) may occur from any thread via tool-completion callbacks; writes come from setter calls which are typically main-thread but not guaranteed.
- L61 _protected member_ `TSharedPtr<IAnalyticsProviderET> AnalyticsProvider;`
- L62 _protected member_ `FString AnalyticsEventNamespace = TEXT("Mod`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/IModelContextProtocolModule.h` (Public)


#### class `IModelContextProtocolModule`  
`class IModelContextProtocolModule : public IModuleInterface`  
_L17-120_
- inherits: `IModuleInterface`
- L21 _public prototype_ `[[nodiscard]] static IModelContextProtocolModule* Get();`
- L22 _public prototype_ `[[nodiscard]] static IModelContextProtocolModule& GetChecked();`
- L25 _public prototype_ `virtual const TArray<TSharedRef<IModelContextProtocolTool>>& GetTools() const = 0;` — Returns current list of registered tools being served
- L31 _public prototype_ `[[nodiscard]] virtual TSharedPtr<IModelContextProtocolTool> FindTool(const FString& ToolName) const = 0;` — Find tool by name (case-insensitive) @see IModelContextProtocolTool::GetName
- L39 _public prototype_ `virtual bool AddTool(const TSharedRef<IModelContextProtocolTool>& Tool) = 0;` — Add tool to server, ensuring no tool is already registered by the same name (case-insensitive). Note: Tool providers *should* listen for OnRefreshTools to re-add tools. @see IModelContextProtocolTool::GetName @return true if the tool was successfully registered, false if there is already a tool by this name being served.
- L46 _public prototype_ `virtual bool RemoveTool(const TSharedRef<IModelContextProtocolTool>& Tool) = 0;` — Remove Tool from server (by pointer) @param Tool	The tool to remove @return true if Tool was found and removed from the collection, false if Tool wasn't found in the collection.
- L48 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRefreshTools);`
- L54 _public prototype_ `virtual FOnRefreshTools& OnRefreshTools() = 0;` — @return	A multicast delegate which is executed whenever the ModelContextProtocol.RefreshTools console command is run to release all current tools and rebuild tool registrations.
- L60 _public prototype_ `virtual void RefreshTools() = 0;` — Called by ModelContextProtocol.RefreshTools console command. Releases all currently registered tools and broadcasts OnRefreshTools for tool providers to re-add tools.
- L63 _public prototype_ `[[nodiscard]] virtual FModelContextProtocolServer* GetServer() = 0;` — Returns the MCP server instance, or nullptr if not created.
- L66 _public prototype_ `virtual void StartServer(uint32 Port = UE::ModelContextProtocol::DefaultServerPort, const FString& UrlPath = UE::ModelContextProtocol::DefaultServerUrlPath) = 0;` — Creates and starts the MCP HTTP server on the specified port and URL path.
- L69 _public prototype_ `virtual void StopServer() = 0;` — Stops and destroys the MCP HTTP server.
- L76 _public prototype_ `virtual void SetAnalyticsProvider(const TSharedPtr<IAnalyticsProviderET>& AnalyticsProvider) = 0;` — Sets the analytics provider used to record MCP telemetry events. A strong reference to the provider is held until a new or null provider is set. @param AnalyticsProvider The provider to use, or nullptr to clear.
- L81 _public prototype_ `[[nodiscard]] virtual TSharedPtr<IAnalyticsProviderET> GetAnalyticsProvider() const = 0;` — @return The currently installed analytics provider, or nullptr if none is set.
- L87 _public prototype_ `virtual void SetAnalyticsEventNamespace(const FString& Namespace) = 0;` — Sets the namespace prepended (with "." separator) to all MCP analytics event names. Default is "ModelContextProtocol". Pass an empty string to emit events without a prefix.
- L93 _public prototype_ `[[nodiscard]] virtual FString GetAnalyticsEventNamespace() const = 0;` — @return A copy of the current analytics event namespace. Returned by value so callers don't hold a reference across racing Set calls.
- L99 _public prototype_ `virtual void RecordAnalyticsEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) = 0;` — Records an MCP analytics event via the currently installed provider. No-op if no provider is set. The event name is prepended with the namespace returned by GetAnalyticsEventNamespace.
- L105 _public prototype_ `virtual const TArray<TSharedRef<IModelContextProtocolResourceProvider>>& GetResourceProviders() const = 0;` — Returns current list of registered resource providers. @see AddResourceProvider, FindResourceProvider
- L112 _public prototype_ `virtual void AddResourceProvider(const TSharedRef<IModelContextProtocolResourceProvider>& ResourceProvider) = 0;` — Add a resource provider. Subsequent MCP resources/list commands will call upon this provider to list resources in response. @param ResourceProvider The provider to register.
- L119 _public prototype_ `virtual bool RemoveResourceProvider(const TSharedRef<IModelContextProtocolResourceProvider>& ResourceProvider) = 0;` — Remove / deregister resource provider. @param ResourceProvider The provider to remove / de-register. @return true if ResourceProvider was found and deregistered, false if ResourceProvider wasn't registered.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRefreshTools);`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/IModelContextProtocolResourceProvider.h` (Public)


#### struct `IModelContextProtocolResourceProvider`  
`struct IModelContextProtocolResourceProvider : TSharedFromThis<IModelContextProtocolResourceProvider>`  
_L20-34_
- inherits: `TSharedFromThis<IModelContextProtocolResourceProvider>`
- desc: Abstract interface for exposing MCP (Anthropic's Model Context Protocol) resources. Resource providers must be registered via IModelContextProtocolModule::GetChecked().AddResourceProvider(MyProvider) @see https://modelcontextprotocol.io/specification/2025-06-18/server/resources
- L22 _public prototype_ `virtual ~IModelContextProtocolResourceProvider();`
- L30 _public prototype_ `virtual void ListResources(FModelContextProtocolResourceDescriptorList& OutResourceDescriptors) const = 0;` — List / describe all resources this provider can currently provide. Any listed resource Uri's which are then requested for read, will be routed back to this provider for reading via this provider's ReadResource implementation.
- L33 _public prototype_ `virtual TValueOrError<FModelContextProtocolResource, FString> ReadResource(const FString& Uri) const = 0;` — Read the contents of a previously listed resource

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/IModelContextProtocolTool.h` (Public)


#### struct `IModelContextProtocolTool`  
`struct IModelContextProtocolTool : TSharedFromThis<IModelContextProtocolTool>`  
_L23-101_
- inherits: `TSharedFromThis<IModelContextProtocolTool>`
- desc: Abstract interface for a describable MCP (Anthropic's Model Context Protocol) tool. Tools can be registered for use via IModelContextProtocolModule::GetChecked().AddTool and must implement either Run or RunAsync for execution. @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools
- L34 _public typedef_ `typedef TFunction<void(const FModelContextProtocolToolResult& Result)> FResultCallback;` — Tool result object or error. Result json object must be complete MCP result object with either content array or structuredContent @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#tool-result Threading: tool implementations may invoke this callback from any thread. The MCP server hops to the game thread before consuming the result, so per-tool work that completes off the game thread does not need to marshal back itself. The callback must be invoked exactly once per tool call. Subsequent invocations after the request has been served (or cancelled) are silently dropped.
- L36 _public prototype_ `virtual ~IModelContextProtocolTool() = default;`
- L39 _public prototype_ `virtual FString GetName() const = 0;` — Returns the identifier name for this tool e.g: select_object
- L42 _public prototype_ `virtual FString GetDescription() const = 0;` — Returns a description of what this tool does when executed, and when it should be used
- L52 _public function_ `virtual TSharedPtr<FJsonObject> GetInputJsonSchema() const` — Returns the JSON Schema definition which the input parameters to this tool must adhere to. Per the MCP specification, inputSchema is required and must be a JSON Schema object with "type": "object". The default returns {"type": "object"} (accepts any parameters). @return A valid JSON Schema definition. @see https://json-schema.org @see FJsonSchemaGenerator::UStructToJsonSchemaObject
- L65 _public function_ `virtual TSharedPtr<FJsonObject> GetOutputJsonSchema() const` — Returns an optional JSON Schema definition which the results of this tool must adhere to. @return A valid JSON Schema definition or invalid shared pointer for undefined output. @see https://json-schema.org @see FJsonSchemaGenerator::UStructToJsonSchemaObject
- L74 _public function_ `virtual FModelContextProtocolToolResult Run(const TSharedPtr<FJsonObject>& Params)` — Executes this tool, performing the described operations, using Params as input, immediately returning a result. @param Params	Input parameters. If GetInputJsonSchema returns a valid schema object, these parameters *should* adhere to said schema. Note: Schema adherence by MCP clients is assumed, not strictly checked internally. @return @see RunAsync
- L91 _public function_ `virtual void RunAsync(const FModelContextProtocolToolRequestId& RequestId, const TSharedPtr<FJsonObject>& Params, const FResultCallback& OnComplete)` — Executes this tool asynchronously, performing the described operations over time, using Params as input. Once operations are complete, OnComplete is called with any results. Note: Calls synchronous Run by default, immediately executing OnComplete with the synchronous result. @param RequestId The request id from the client request for identifying this particular tool call. @param Params	Input parameters. If GetInputJsonSchema returns a valid schema object, these parameters *should* adhere to said schema. Note: Schema adherence by MCP clients is assumed, not strictly checked internally. @param OnComplete	Once the operation is complete, implementations must call OnComplete, passing in their JSON formatted tool results. Implementations returning a valid schema from GetOutputJsonSchema *MUST* ensure results adhere to this schema. @see Run
- L97 _public function_ `virtual void CancelAsync(const FModelContextProtocolToolRequestId& RequestId)`
- L100 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector)` — Called by FModelContextProtocolToolCollection to allow tools to report UObject dependencies for reference tracking

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocol.h` (Public)


#### enum `UE::ModelContextProtocol::EToolNameValidation`  
`enum class EToolNameValidation : uint8`  
_L50-56_
- desc: Tool name validation result per MCP spec (2025-11-25).
- L52 _public enumerator_ `Valid`
- L53 _public enumerator_ `Empty`
- L54 _public enumerator_ `ExceedsMaxLength`
- L55 _public enumerator_ `InvalidCharacters`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogModelContextProtocol, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L16 _variable_ `static constexpr const TCHAR* JsonRpcVersion = TEXT("2.0` (scope `UE::ModelContextProtocol`)
- L19 _variable_ `static constexpr const TCHAR* ProtocolVersion = TEXT("202` (scope `UE::ModelContextProtocol`) — The latest protocol version supported by this server.
- L22 _function_ `inline const TArray<FString>& GetSupportedProtocolVersions()` (scope `UE::ModelContextProtocol`) — All protocol versions this server supports, ordered newest-first.
- L33 _function_ `inline FString NegotiateProtocolVersion(const FString& ClientRequestedVersion)` (scope `UE::ModelContextProtocol`) — Returns the negotiated protocol version: the client's version if supported, otherwise the server's latest.
- L45 _variable_ `static constexpr uint32 DefaultServerPort = 8000;` (scope `UE::ModelContextProtocol`)
- L46 _variable_ `static constexpr const TCHAR* DefaultServerUrlPath = TEXT("/mc` (scope `UE::ModelContextProtocol`)
- L47 _variable_ `static constexpr const TCHAR* DefaultServerName = TEXT("unr` (scope `UE::ModelContextProtocol`)
- L63 _prototype_ `EToolNameValidation ValidateToolName(const FString& ToolName);` (scope `UE::ModelContextProtocol`) — Validates a tool name per MCP spec (2025-11-25) tool name rules. Names SHOULD be 1-128 chars using only A-Z, a-z, 0-9, underscore, hyphen, and dot. @see https://modelcontextprotocol.io/specification/2025-11-25/server/tools#tool-names
- L65 _variable_ `static constexpr const TCHAR* PODWrapperResultPropertyName = TEXT("res` (scope `UE::ModelContextProtocol`)
- L67 _variable_ `static constexpr const TCHAR* ContentTypeEventStream = TEXT("tex` (scope `UE::ModelContextProtocol`)
- L70 _externvar_ `extern bool bWrapPODResultsInObject;` (scope `UE::ModelContextProtocol`) — CVars
- L71 _externvar_ `extern bool bAudioResultOggFormat;` (scope `UE::ModelContextProtocol`)
- L72 _externvar_ `extern float ProgressIntervalSeconds;` (scope `UE::ModelContextProtocol`)
- L73 _externvar_ `extern int32 PaginationPageSize;` (scope `UE::ModelContextProtocol`)

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolAnalytics.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L12 _namespace_ `namespace Analytics` (scope `UE::ModelContextProtocol`)
- L22 _prototype_ `bool IsToolResultSuccess(const TSharedPtr<FJsonObject>& ResultJson);` (scope `UE::ModelContextProtocol::Analytics`) — Resolves the success/error outcome of a tool call from its result JSON. Per the MCP spec, "isError" is optional and defaults to false. - Null JsonObject: Error (malformed or missing result). - No "isError" field: Success (MCP default). - "isError" is a bool: follow it. - "isError" is present but not a bool: Error (malformed).
- L30 _prototype_ `FString HashToolIdentifier(const FString& Identifier);` (scope `UE::ModelContextProtocol::Analytics`) — Returns a lowercase-hex Blake3 hash of an MCP tool or toolset identifier. Input is encoded as UTF-8 before hashing so the result is stable across platforms. Used to anonymize tool names in analytics payloads: Epic resolves known hashes against its own lookup table; licensee-private tool names stay opaque.
- L36 _prototype_ `FString ParseToolsetName(const FString& FullToolName);` (scope `UE::ModelContextProtocol::Analytics`) — Extracts the toolset portion of an MCP tool name by splitting at the last dot. Matches the semantics of `UE::ToolsetRegistry::FToolDescriptor::FromString`. Returns an empty string for top-level tools (no dot present).
- L39 _prototype_ `void RecordToolCallEvent(const FString& SessionId, const FString& ToolName, double DurationSeconds, bool bSuccess);` (scope `UE::ModelContextProtocol::Analytics`) — Records a tool call completion event.
- L42 _prototype_ `void RecordSessionStartEvent(const FString& SessionId, const FString& NegotiatedProtocolVersion);` (scope `UE::ModelContextProtocol::Analytics`) — Records a session start event (called on notifications/initialized).
- L45 _prototype_ `void RecordSessionEndEvent(const FString& SessionId);` (scope `UE::ModelContextProtocol::Analytics`) — Records a session end event (called on DELETE or server shutdown).

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolCapabilities.h` (Public)


#### struct `FModelContextProtocolRootsCapability`  
`struct FModelContextProtocolRootsCapability`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `TOptional<bool> ListChanged;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`

#### struct `FModelContextProtocolSamplingCapability`  
`struct FModelContextProtocolSamplingCapability`  
_L19-22_
- reflection: `USTRUCT()`

#### struct `FModelContextProtocolElicitationCapability`  
`struct FModelContextProtocolElicitationCapability`  
_L25-28_
- reflection: `USTRUCT()`

#### struct `FModelContextProtocolClientCapabilities`  
`struct FModelContextProtocolClientCapabilities`  
_L31-43_
- reflection: `USTRUCT()`
- L36 _public member_ `TOptional<FModelContextProtocolRootsCapability> Roots;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`
- L39 _public member_ `TOptional<FModelContextProtocolSamplingCapability> Sampling;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`
- L42 _public member_ `TOptional<FModelContextProtocolElicitationCapability> Elicitation;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`

#### struct `FModelContextProtocolLoggingCapability`  
`struct FModelContextProtocolLoggingCapability`  
_L46-49_
- reflection: `USTRUCT()`

#### struct `FModelContextProtocolPromptsCapability`  
`struct FModelContextProtocolPromptsCapability`  
_L52-58_
- reflection: `USTRUCT()`
- L57 _public member_ `TOptional<bool> ListChanged;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`

#### struct `FModelContextProtocolResourcesCapability`  
`struct FModelContextProtocolResourcesCapability`  
_L61-70_
- reflection: `USTRUCT()`
- L66 _public member_ `TOptional<bool> Subscribe;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`
- L69 _public member_ `TOptional<bool> ListChanged;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`

#### struct `FModelContextProtocolToolsCapability`  
`struct FModelContextProtocolToolsCapability`  
_L73-79_
- reflection: `USTRUCT()`
- L78 _public member_ `TOptional<bool> ListChanged;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`

#### struct `FModelContextProtocolServerCapabilities`  
`struct FModelContextProtocolServerCapabilities`  
_L82-97_
- reflection: `USTRUCT()`
- L87 _public member_ `TOptional<FModelContextProtocolLoggingCapability> Logging;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`
- L90 _public member_ `TOptional<FModelContextProtocolPromptsCapability> Prompts;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`
- L93 _public member_ `TOptional<FModelContextProtocolResourcesCapability> Resources;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`
- L96 _public member_ `TOptional<FModelContextProtocolToolsCapability> Tools;` — `UPROPERTY(VisibleAnywhere, Category="Capabilities")`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolMetaData.h` (Public)


#### struct `FModelContextProtocolPropertyMetaData`  
`struct FModelContextProtocolPropertyMetaData`  
_L15-38_
- reflection: `USTRUCT()`
- desc: Cached editor-only property meta-data in a cookable form
- L21 _public member_ `TOptional<FText> Description;` — `UPROPERTY()` — Property description derived from its tooltip / native code comment
- L25 _public member_ `TOptional<double> ClampMin;` — `UPROPERTY(Meta = (ClampMin = "1"))` — `UPROPERTY()`
- L29 _public member_ `TOptional<double> ClampMax;` — `UPROPERTY(Meta = (ClampMax = "1000"))` — `UPROPERTY()`
- L33 _public member_ `TOptional<FString> DefaultValue;` — `UPROPERTY()` — For function parameters, stores the default parameter value
- L37 _public member_ `TOptional<uint8> DefaultValueJsonType;` — `UPROPERTY()` — Original JSON type (EJson cast to uint8) of DefaultValue, used for lossless round-trip

#### struct `FModelContextProtocolFunctionMetaData`  
`struct FModelContextProtocolFunctionMetaData`  
_L42-57_
- reflection: `USTRUCT()`
- desc: Cached editor-only function meta-data in a cookable form
- L48 _public member_ `TOptional<FText> Description;` — `UPROPERTY()` — Function description derived from its tooltip / native code comment
- L52 _public member_ `TMap<FString, FModelContextProtocolPropertyMetaData> PropertyMetaData;` — `UPROPERTY()` — Per-property meta data, including inner properties e.g: Person, Person.Name, Person.Age
- L56 _public member_ `FString WorldContext;` — `UPROPERTY()` — The function's WorldContext meta-data value, if any

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolResources.h` (Public)


#### struct `FModelContextProtocolResourceDescriptor`  
`struct FModelContextProtocolResourceDescriptor`  
_L17-25_
- desc: Identifying meta-data for a potential resource to be provided by an IModelContextProtocolResourceProvider.
- L19 _public prototype_ `FModelContextProtocolResourceDescriptor(const FString& Uri, const TOptional<FString>& Name = {}, const TOptional<FString>& Title = {}, const TOptional<FString>& Description = {}, const TOptional<FString>& MimeType = {});`
- L20 _public prototype_ `FString GetUri() const;`
- L21 _public prototype_ `TSharedRef<FJsonObject> GetJsonObject() const;`
- L24 _protected member_ `FJsonDomBuilder::FObject JsonResourceObject;`

#### struct `FModelContextProtocolResource`  
`struct FModelContextProtocolResource : public FModelContextProtocolResourceDescriptor`  
_L30-34_
- inherits: `FModelContextProtocolResourceDescriptor`
- desc: A string or binary blob resource, provided by an IModelContextProtocolResourceProvider
- L32 _public prototype_ `FModelContextProtocolResource(const FString& Uri, FString&& TextContent, const TOptional<FString>& Name = {}, const TOptional<FString>& Title = {}, const TOptional<FString>& MimeType = {});`
- L33 _public prototype_ `FModelContextProtocolResource(const FString& Uri, const TArrayView<uint8>& BlobContent, const TOptional<FString>& Name = {}, const TOptional<FString>& Title = {}, const TOptional<FString>& MimeType = {});`

#### struct `FModelContextProtocolResourceDescriptorList`  
`struct FModelContextProtocolResourceDescriptorList`  
_L37-68_
- desc: List of Model Context Protocol resource descriptors that also tracks which IModelContextProtocolResourceProvider listed them
- L40 _public prototype_ `void Add( const FModelContextProtocolResourceDescriptor& ResourceDescriptor, const TSharedRef<const IModelContextProtocolResourceProvider>& ResourceProvider);` — Add a descriptor for a resource which ResourceProvider can provide
- L48 _public prototype_ `void Reset();` — Clears the list, including mapping of which provider added which descriptor. Note: To release only the cached Json descriptor list, use ReleaseJsonArray.
- L51 _public prototype_ `int32 Num() const;` — Returns the number of descriptors in the list.
- L54 _public prototype_ `TSharedRef<FJsonValueArray> GetJsonArray() const;` — Returns the cached JSON list of resource descriptors
- L60 _public prototype_ `void ReleaseJsonArray();` — Releases the cached JSON list of resource descriptors. Importantly, the mapping of which provider listed which URI is left intact for later URI to provider matching.
- L63 _public prototype_ `TSharedPtr<const IModelContextProtocolResourceProvider> FindResourceProvider(const FString& Uri) const;` — Returns the resource provider that added Uri to this list (if a resource descriptor for Uri has been added, nullptr otherwise)
- L66 _protected member_ `TMap<FString, TSharedRef<const IModelContextProtocolResourceProvider>> ResourceUriToProvider;`
- L67 _protected member_ `FJsonDomBuilder::FArray JsonResourceDescriptorArray;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolServer.h` (Public)


#### class `FModelContextProtocolServer`  
`class FModelContextProtocolServer`  
_L27-97_
- desc: MCP (Anthropic's Model Context Protocol) tool server. Serves MCP tools over HTTP per the https://modelcontextprotocol.io/ spec. @see https://modelcontextprotocol.io @see UModelContextProtocolSettings
- L34 _public prototype_ `FModelContextProtocolServer() = default;`
- L35 _public prototype_ `~FModelContextProtocolServer();`
- L37 _public prototype_ `FModelContextProtocolServer(const FModelContextProtocolServer&) = delete;`
- L38 _public prototype_ `FModelContextProtocolServer& operator=(const FModelContextProtocolServer&) = delete;`
- L43 _public prototype_ `void StartServer(uint32 Port, const FString& UrlPath);` — Starts the HTTP MCP server on the specified port and URL path.
- L48 _public prototype_ `void StopServer();` — Stops the HTTP MCP server.
- L51 _public prototype_ `bool IsServerRunning() const;` — Returns true if the HTTP MCP server is currently running.
- L54 _public prototype_ `uint32 GetServerPort() const;` — Returns the port the server is currently listening on, or 0 if not running.
- L57 _public prototype_ `void ScheduleToolsListChangedBroadcast();` — Schedules a notifications/tools/list_changed broadcast to all initialized sessions with active SSE streams on the next Tick.
- L61 _private prototype_ `void Tick(float DeltaTime);`
- L64 _private member_ `bool bToolsListChangedBroadcastScheduled = false;` — Set by ScheduleToolsListChangedBroadcast; drained on the next Tick.
- L66 _private member_ `TArray<TSharedPtr<FModelContextProtocolSession>> Sessions;`
- L68 _private prototype_ `TSharedPtr<FModelContextProtocolSession> FindSession(const FString& SessionId) const;`
- L70 _private member_ `TSharedPtr<IHttpRouter> HttpRouter;`
- L71 _private member_ `uint32 ActiveServerPort = 0;`
- L73 _private member_ `FHttpRouteHandle MainMcpRoute;`
- L74 _private member_ `FHttpRouteHandle SseMcpRoute;`
- L75 _private member_ `FHttpRouteHandle DeleteMcpRoute;`
- L77 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L80 _private member_ `TSharedPtr<bool> AliveGuard = MakeShared<bool>(true);` — Prevent use-after-free: async tool completion lambdas capture a TWeakPtr to this; Reset() in destructor invalidates all weak references.
- L82 _private member_ `FModelContextProtocolResourceDescriptorList LastResourceDescriptorList;`
- L84 _private prototype_ `bool ProcessPostRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L85 _private prototype_ `bool ProcessGetRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L86 _private prototype_ `bool ProcessDeleteRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L88 _private prototype_ `bool ProcessJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const FString& Method, const TSharedPtr<FJsonObject>& Params, const FHttpResultCallback& OnComplete);`
- L89 _private prototype_ `bool ProcessPingJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const FHttpResultCallback& OnComplete);`
- L90 _private prototype_ `bool ProcessInitializeJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const TSharedPtr<FJsonObject>& Params, const FHttpResultCallback& OnComplete);`
- L91 _private prototype_ `bool ProcessInitializedNotificationJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const TSharedPtr<FJsonObject>& Params, const TSharedRef<FModelContextProtocolSession>& Session, const FHttpResultCallback& OnComplete);`
- L92 _private prototype_ `bool ProcessNotificationCancelledJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const TSharedPtr<FJsonObject>& Params, const TSharedRef<FModelContextProtocolSession>& Session, const FHttpResultCallback& OnComplete);`
- L93 _private prototype_ `bool ProcessListToolsJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const TSharedPtr<FJsonObject>& Params, const TSharedRef<FModelContextProtocolSession>& Session, const FHttpResultCallback& OnComplete);`
- L94 _private prototype_ `bool ProcessToolCallJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const TSharedPtr<FJsonObject>& Params, const TSharedRef<FModelContextProtocolSession>& Session, const FHttpResultCallback& OnComplete);`
- L95 _private prototype_ `bool ProcessListResourcesJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const TSharedPtr<FJsonObject>& Params, const TSharedRef<FModelContextProtocolSession>& Session, const FHttpResultCallback& OnComplete);`
- L96 _private prototype_ `bool ProcessReadResourceJsonRpcCall(const FHttpServerRequest& Request, const TSharedPtr<FJsonValue>& RequestId, const TSharedPtr<FJsonObject>& Params, const TSharedRef<FModelContextProtocolSession>& Session, const FHttpResultCallback& OnComplete);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ModelContextProtocol` (scope `UE`)

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolSession.h` (Public)


#### enum `EModelContextProtocolSessionStatus`  
`enum struct EModelContextProtocolSessionStatus`  
_L18-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `Initializing` — Server and client are handshaking
- L24 _public enumerator_ `Initialized` — Server and client are both initialized

#### struct `FModelContextProtocolClientInfo`  
`struct FModelContextProtocolClientInfo`  
_L28-40_
- reflection: `USTRUCT()`
- L33 _public member_ `FString Name;` — `UPROPERTY()`
- L36 _public member_ `FString Title;` — `UPROPERTY()`
- L39 _public member_ `FString Version;` — `UPROPERTY()`

#### struct `FModelContextProtocolServerInfo`  
`struct FModelContextProtocolServerInfo`  
_L43-55_
- reflection: `USTRUCT()`
- L48 _public member_ `FString Name;` — `UPROPERTY()`
- L51 _public member_ `FString Title;` — `UPROPERTY()`
- L54 _public member_ `FString Version;` — `UPROPERTY()`

#### struct `FModelContextProtocolPingResult`  
`struct FModelContextProtocolPingResult`  
_L58-61_
- reflection: `USTRUCT()`

#### struct `FModelContextProtocolInitializeParams`  
`struct FModelContextProtocolInitializeParams`  
_L64-76_
- reflection: `USTRUCT()`
- L69 _public member_ `FString ProtocolVersion = UE::ModelContextProtocol::ProtocolVersion;` — `UPROPERTY()`
- L72 _public member_ `FModelContextProtocolClientCapabilities Capabilities;` — `UPROPERTY()`
- L75 _public member_ `FModelContextProtocolClientInfo ClientInfo;` — `UPROPERTY()`

#### struct `FModelContextProtocolInitializeResult`  
`struct FModelContextProtocolInitializeResult`  
_L79-94_
- reflection: `USTRUCT()`
- L84 _public member_ `FString ProtocolVersion = UE::ModelContextProtocol::ProtocolVersion;` — `UPROPERTY()`
- L87 _public member_ `FModelContextProtocolServerCapabilities Capabilities;` — `UPROPERTY()`
- L90 _public member_ `FModelContextProtocolServerInfo ServerInfo;` — `UPROPERTY()`
- L93 _public member_ `TOptional<FString> Instructions;` — `UPROPERTY()`

#### struct `FModelContextProtocolToolRequestId`  
`struct FModelContextProtocolToolRequestId`  
_L96-113_
- L98 _public prototype_ `FModelContextProtocolToolRequestId() = default;`
- L99 _public function_ `explicit FModelContextProtocolToolRequestId(const TSharedPtr<FJsonValue>& InRequestId) : RequestId(InRequestId)`
- L101 _public member_ `TSharedPtr<FJsonValue> RequestId;`
- L103 _public function_ `bool IsValid() const`
- L105 _public prototype_ `bool operator==(const FModelContextProtocolToolRequestId& RHS) const;`
- L107 _public function_ `bool operator!=(const FModelContextProtocolToolRequestId& RHS) const`

#### struct `FModelContextProtocolToolContext`  
`struct FModelContextProtocolToolContext`  
_L115-126_
- L117 _public prototype_ `FModelContextProtocolToolContext() = default;`
- L119 _public member_ `TSharedPtr<IModelContextProtocolTool> Tool;`
- L120 _public member_ `TSharedPtr<FJsonValue> ProgressToken;`
- L122 _public member_ `FHttpResultCallback EventStreamWrite;`
- L124 _public member_ `double LastProgressSeconds = 0.0;`
- L125 _public member_ `int32 LastProgressValue = 0;`

#### struct `FModelContextProtocolSession`  
`struct FModelContextProtocolSession : TSharedFromThis<FModelContextProtocolSession>`  
_L128-139_
- inherits: `TSharedFromThis<FModelContextProtocolSession>`
- L130 _public prototype_ `FModelContextProtocolSession() = default;`
- L132 _public member_ `FString ID;`
- L133 _public member_ `EModelContextProtocolSessionStatus Status = EModelContextProtocolSessionStatus::Initializing;`
- L134 _public member_ `FString NegotiatedProtocolVersion = UE::ModelContextProtocol::ProtocolVersion;`
- L135 _public member_ `TSharedPtr<FInternetAddr> ClientAddress;`
- L136 _public member_ `FModelContextProtocolClientCapabilities ClientCapabilities;`
- L138 _public member_ `TMap<FModelContextProtocolToolRequestId, FModelContextProtocolToolContext> ActiveRequests;`

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolToolResults.h` (Public)


#### enum `EModelContextProtocolToolResultType`  
`enum class EModelContextProtocolToolResultType`  
_L17-26_
- reflection: `UENUM(meta = (Bitflags))`
- L19 _public enumerator_ `None = 0`
- L20 _public enumerator_ `Text = 1 << 0`
- L21 _public enumerator_ `Image = 1 << 1`
- L22 _public enumerator_ `Audio = 1 << 2`
- L23 _public enumerator_ `ResourceLink = 1 << 3 UMETA(Hidden)`
- L24 _public enumerator_ `EmbeddedResource = 1 << 4 UMETA(Hidden)`
- L25 _public enumerator_ `StructuredContent = 1 << 5`

#### enum `EModelContextProtocolAudience`  
`enum class EModelContextProtocolAudience`  
_L30-36_
- reflection: `UENUM(meta = (Bitflags))`
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `User = 1 << 0`
- L34 _public enumerator_ `Assistant = 1 << 1`
- L35 _public enumerator_ `All = User | Assistant`

#### struct `FModelContextProtocolToolResult`  
`struct FModelContextProtocolToolResult : public FJsonObjectWrapper`  
_L47-56_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FJsonObjectWrapper`
- desc: IModelContextProtocolTool execution result. Wraps a JSON object adhering to https://modelcontextprotocol.io/specification/2025-06-18/server/tools#tool-result spec. Use MakeTextResult, MakeStructuredContentResult, MakeImageResult & MakeAudioResult for creating the appropriate tool result structures.
- L51 _public prototype_ `FModelContextProtocolToolResult() = default;`
- L52 _public function_ `FModelContextProtocolToolResult(const TSharedPtr<FJsonObject>& InJsonObject)`

#### struct `UE::ModelContextProtocol::FJsonExportParams`  
`struct FJsonExportParams`  
_L92-98_
- L94 _public member_ `int64 CheckFlags = CPF_None;`
- L95 _public member_ `int64 SkipFlags = CPF_None;`
- L96 _public member_ `const FJsonObjectConverter::CustomExportCallback* ExportCb = nullptr;`
- L97 _public member_ `EJsonObjectConversionFlags ConversionFlags = EJsonObjectConversionFlags::None;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L62 _function_ `template <typename TextT> TSharedPtr<FJsonObject> MakeTextContentObject(TextT Text)` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#text-content
- L71 _function_ `template <typename TextT> FModelContextProtocolToolResult MakeTextResult(TextT Text)` (scope `UE::ModelContextProtocol`)
- L81 _prototype_ `FModelContextProtocolToolResult MakeImageResult(const FString& MimeType, TArrayView<uint8> Data, EModelContextProtocolAudience Audience = EModelContextProtocolAudience::All);` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#image-content
- L82 _prototype_ `FModelContextProtocolToolResult MakeImageResult(const FString& MimeType, FString&& Base64EncodedData, EModelContextProtocolAudience Audience = EModelContextProtocolAudience::All);` (scope `UE::ModelContextProtocol`)
- L85 _prototype_ `FModelContextProtocolToolResult MakeAudioResult(const FString& MimeType, TArrayView<uint8> Data);` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#audio-content
- L86 _prototype_ `FModelContextProtocolToolResult MakeAudioResult(const FString& MimeType, FString&& Base64EncodedData);` (scope `UE::ModelContextProtocol`)
- L89 _prototype_ `FModelContextProtocolToolResult MakeResourceLinkResult(const FModelContextProtocolResourceDescriptor& ResourceDescriptor, EModelContextProtocolAudience Audience = EModelContextProtocolAudience::All);` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#resource-links
- L90 _prototype_ `FModelContextProtocolToolResult MakeResourceLinksResult(TConstArrayView<FModelContextProtocolResourceDescriptor> ResourceDescriptors, EModelContextProtocolAudience Audience = EModelContextProtocolAudience::All);` (scope `UE::ModelContextProtocol`)
- L101 _prototype_ `FModelContextProtocolToolResult MakeStructuredContentResult(const UStruct* StructDefinition, const void* Struct, const FJsonExportParams& Params = {});` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#structured-content
- L103 _function_ `template<typename T> FModelContextProtocolToolResult MakeStructuredContentResult(const T& Struct, const FJsonExportParams& Params = {})` (scope `UE::ModelContextProtocol`)
- L107 _function_ `FORCEINLINE FModelContextProtocolToolResult MakeStructuredContentResult(const UObject* Object, const FJsonExportParams& Params = {})` (scope `UE::ModelContextProtocol`)
- L111 _prototype_ `FModelContextProtocolToolResult MakeStructuredContentResult(FProperty* Property, const void* Value, const FJsonExportParams& Params = {});` (scope `UE::ModelContextProtocol`)
- L112 _prototype_ `FModelContextProtocolToolResult MakeStructuredContentResult(TSharedPtr<FJsonValue> StructuredContent);` (scope `UE::ModelContextProtocol`)
- L116 _function_ `template <typename TextT> FModelContextProtocolToolResult MakeErrorResult(TextT Text)` (scope `UE::ModelContextProtocol`) — @see https://modelcontextprotocol.io/specification/2025-06-18/server/tools#error-handling

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocol/Public/ModelContextProtocolUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELCONTEXTPROTOCOL_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ModelContextProtocol` (scope `UE`)
- L16 _function_ `bool SafeConvertRelativePathToFull(const FString& BasePath, const FString& FileName, FString& OutFilePath)` (scope `UE::ModelContextProtocol`) — Joins BasePath & Filename, ensuring the resulting path is indeed under BasePath. Useful to ensure models can't create files outside the intended BasePath using relative directory traversal e.g YourBasePath/../SomeOtherBase/MyFile.ext
