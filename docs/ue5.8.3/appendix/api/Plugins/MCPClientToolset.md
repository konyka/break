# Plugins / MCPClientToolset

- module root: `Plugins/Experimental/Toolsets/MCPClientToolset/Source/MCPClientToolset`
- headers: 4; symbols: 118
- symbol kinds: class=4, delegate=1, enum=3, enumerator=10, function=3, macro=1, member=46, namespace=4, prototype=42, struct=4
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, EditorSubsystem, Engine, HTTP, HTTPServer, Json, UnrealEd
- PublicDependencyModuleNames: Core, ToolsetRegistry

### `Plugins/Experimental/Toolsets/MCPClientToolset/Source/MCPClientToolset/Private/MCPClientToolset/Module.h` (Private)


#### class `FMCPClientToolsetModule`  
`class FMCPClientToolsetModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMCPClientToolset, Log, Log);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMCPClientToolset, Log, Log);`

### `Plugins/Experimental/Toolsets/MCPClientToolset/Source/MCPClientToolset/Public/MCPClientToolset/MCPClientToolset.h` (Public)


#### class `UE::ToolsetRegistry::FMCPClientToolset`  
`class FMCPClientToolset : public FToolset, public TSharedFromThis<FMCPClientToolset>`  
_L45-176_
- inherits: `FToolset,TSharedFromThis<FMCPClientToolset>`
- desc: A toolset that connects to an external MCP (Model Context Protocol) server. Use the async factory Create() to construct an instance. Depending on the FConfig settings the factory will use one of three startup paths: - OAuth 2.0 Authorization Code + PKCE  (bOAuth = true) - Streamable HTTP transport             (bStreamableHTTP = true) - Legacy HTTP+SSE transport             (default) Transport options: Legacy SSE (MCP pre-2025-03-26): GET  /sse      — server→client event stream (long-lived) POST /message  — client→server JSON-RPC requests Streamable HTTP (MCP 2025-03-26): POST {ServerUrl}  — single endpoint; response is application/json or text/event-stream
- L74 _public prototype_ `FMCPClientToolset(FPrivateToken, FConfig InConfig);`
- L75 _public prototype_ `virtual ~FMCPClientToolset();`
- L81 _public prototype_ `static TFuture<TValueOrError<TSharedPtr<FMCPClientToolset>, FString>> Create(FConfig Config);` — Async factory. Runs the appropriate startup sequence (OAuth → handshake, or direct handshake), then resolves the future with the ready toolset or an error string.
- L84 _public prototype_ `virtual TFuture<TValueOrError<FString, FString>> ExecuteToolInternal( const FString& ToolName, const FString& JsonInput) override;` — FToolset interface
- L86 _public prototype_ `virtual FString GetJsonSchemaInternal() const override;`
- L87 _public prototype_ `virtual FString GetToolsetName() const override;`
- L88 _public prototype_ `virtual FString GetToolsetVersion() const override;`
- L89 _public prototype_ `virtual FString GetToolsetDescription() const override;`
- L93 _private prototype_ `void StartSSEConnection();` — ---- SSE connection ----
- L94 _private prototype_ `bool OnSSETick(float DeltaTime);`
- L95 _private prototype_ `void OnSSEComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);`
- L96 _private prototype_ `void FlushSSEBuffer();`
- L97 _private prototype_ `void DispatchSSEEvent(const FString& EventType, const FString& Data);`
- L100 _private prototype_ `TFuture<TSharedPtr<FJsonObject>> SendRequest(const FString& Method, TSharedPtr<FJsonObject> Params);` — ---- JSON-RPC helpers ----
- L101 _private prototype_ `FString BuildSchemaFromMCPTools(const TArray<TSharedPtr<FJsonValue>>& Tools);`
- L102 _private prototype_ `FString MCPResultToString(TSharedPtr<FJsonObject> Result);`
- L103 _private prototype_ `void RejectAllPendingRequests();`
- L106 _private prototype_ `FString GetAuthHeader() const;` — ---- Unified auth header (OAuth token > static API key > empty) ----
- L109 _private prototype_ `void StartStreamableHTTPHandshake();` — ---- Streamable HTTP transport ----
- L110 _private prototype_ `TFuture<TSharedPtr<FJsonObject>> SendStreamableHTTPRequest( const FString& Method, TSharedPtr<FJsonObject> Params);`
- L114 _private prototype_ `void StartOAuthFlow();` — ---- OAuth 2.0 Authorization Code + PKCE ----
- L115 _private prototype_ `void OnOAuthDiscoveryComplete(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess);`
- L116 _private prototype_ `void AllocateOAuthPort();`
- L117 _private prototype_ `void RegisterOAuthClient();`
- L118 _private prototype_ `void OnOAuthClientRegistered(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess);`
- L119 _private prototype_ `void LaunchOAuthBrowser();`
- L120 _private prototype_ `bool HandleOAuthCallback(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L121 _private prototype_ `void ExchangeOAuthCode(const FString& Code);`
- L122 _private prototype_ `void OnOAuthTokenExchangeComplete(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess);`
- L123 _private prototype_ `bool OnOAuthTimeout(float DeltaTime);`
- L124 _private prototype_ `void FailOAuth(const FString& Reason);`
- L125 _private prototype_ `void TryRefreshToken();`
- L126 _private prototype_ `void OnRefreshTokenComplete(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess);`
- L127 _private prototype_ `void SaveTokensToConfig();`
- L128 _private prototype_ `void LoadTokensFromConfig();`
- L131 _private member_ `FConfig Config;` — ---- Config / capabilities ----
- L132 _private member_ `FString ServerVersion;`
- L140 _private member_ `TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> SSERequest;`
- L141 _private member_ `FTSTicker::FDelegateHandle SSETickerHandle;`
- L142 _private member_ `FString MessageEndpointUrl;`
- L143 _private member_ `FString SSEBuffer;`
- L144 _private member_ `TSharedPtr<FSSEStreamState, ESPMode::ThreadSafe> SSEStreamState;`
- L147 _private member_ `FString StreamableSessionId;` — ---- Streamable HTTP state ----
- L150 _private member_ `int32 NextRequestId = 0;` — ---- Request tracking ----
- L151 _private member_ `TMap<int32, TSharedPtr<TPromise<TSharedPtr<FJsonObject>>>> PendingRequests;`
- L154 _private member_ `FString CachedSchemaJson;` — ---- Cached schema ----
- L157 _private member_ `TSharedPtr<TPromise<TValueOrError<TSharedPtr<FMCPClientToolset>, FString>>> CreatePromise;` — ---- Create() promise, fulfilled after handshake ----
- L158 _private member_ `TSharedPtr<FMCPClientToolset> Self;`
- L163 _private member_ `EOAuthState OAuthState = EOAuthState::Idle;`
- L164 _private member_ `FString AccessToken;`
- L165 _private member_ `FString RefreshToken;`
- L166 _private member_ `FDateTime TokenExpiresAt;`
- L167 _private member_ `FString OAuthCodeVerifier;`
- L168 _private member_ `FString OAuthCSRFState;`
- L169 _private member_ `FString OAuthAuthEndpoint;`
- L170 _private member_ `FString OAuthTokenEndpoint;`
- L171 _private member_ `FString OAuthRegistrationEndpoint;`
- L172 _private member_ `int32 OAuthLocalPort = 0;`
- L173 _private member_ `TSharedPtr<IHttpRouter> OAuthRouter;`
- L174 _private member_ `FHttpRouteHandle OAuthRouteHandle;`
- L175 _private member_ `FTSTicker::FDelegateHandle OAuthTimeoutHandle;`

#### struct `UE::ToolsetRegistry::FMCPClientToolset::FConfig`  
`struct FConfig`  
_L49-67_
- desc: Configuration for one MCP server connection.
- L52 _public member_ `FString Name;` — Display name used as the toolset name in the registry.
- L54 _public member_ `FString Description;` — Human-readable description of the toolset. Falls back to Name if empty.
- L56 _public member_ `FString ServerUrl;` — Base URL of the server, e.g. "http://localhost:3000".
- L58 _public member_ `FString ApiKey;` — Optional API key sent as "Authorization: Bearer <ApiKey>".
- L60 _public member_ `bool bStreamableHTTP = false;` — Use Streamable HTTP transport (MCP spec 2025-03-26) instead of legacy SSE.
- L62 _public member_ `bool bOAuth = false;` — Use OAuth 2.0 Authorization Code + PKCE instead of a static API key.
- L64 _public member_ `FString OAuthClientId;` — OAuth 2.0 client ID (optional — leave empty for dynamic client registration).
- L66 _public member_ `FString OAuthScope;` — OAuth 2.0 scope string, e.g. "read:me offline_access".

#### struct `UE::ToolsetRegistry::FMCPClientToolset::FPrivateToken`  
`struct FPrivateToken`  
_L73-73_
- desc: Opaque tag used so MakeShared can invoke the private-intent constructor. Call Create() instead of constructing directly.
- L73 _public prototype_ `struct FPrivateToken` — Opaque tag used so MakeShared can invoke the private-intent constructor. Call Create() instead of constructing directly.

#### struct `UE::ToolsetRegistry::FMCPClientToolset::FSSEStreamState`  
`struct FSSEStreamState`  
_L135-138_
- desc: ---- SSE state ----
- L137 _public member_ `TQueue<TArray<uint8>, EQueueMode::Spsc> Queue;`

#### enum `UE::ToolsetRegistry::FMCPClientToolset::EOAuthState`  
`enum class EOAuthState : uint8`  
_L161-161_
- desc: ---- OAuth 2.0 state ----
- L161 _public enumerator_ `enum class EOAuthState : uint8 { Idle, Discovering, WaitingForCode, Exchanging, Complete }; EOAuthState OAuthState = EOAuthState::Idle; FString AccessToken; FString RefreshToken; FDateTime TokenExpiresAt; FString OAuthCodeVerifier; FString OAuthCSRFState;` — ---- OAuth 2.0 state ----
- L161 _public enumerator_ `enum class EOAuthState : uint8 { Idle, Discovering, WaitingForCode, Exchanging, Complete }; EOAuthState OAuthState = EOAuthState::Idle; FString AccessToken; FString RefreshToken; FDateTime TokenExpiresAt; FString OAuthCodeVerifier; FString OAuthCSRFState;` — ---- OAuth 2.0 state ----
- L161 _public enumerator_ `enum class EOAuthState : uint8 { Idle, Discovering, WaitingForCode, Exchanging, Complete }; EOAuthState OAuthState = EOAuthState::Idle; FString AccessToken; FString RefreshToken; FDateTime TokenExpiresAt; FString OAuthCodeVerifier; FString OAuthCSRFState;` — ---- OAuth 2.0 state ----
- L161 _public enumerator_ `enum class EOAuthState : uint8 { Idle, Discovering, WaitingForCode, Exchanging, Complete }; EOAuthState OAuthState = EOAuthState::Idle; FString AccessToken; FString RefreshToken; FDateTime TokenExpiresAt; FString OAuthCodeVerifier; FString OAuthCSRFState;` — ---- OAuth 2.0 state ----
- L161 _public enumerator_ `enum class EOAuthState : uint8 { Idle, Discovering, WaitingForCode, Exchanging, Complete }; EOAuthState OAuthState = EOAuthState::Idle; FString AccessToken; FString RefreshToken; FDateTime TokenExpiresAt; FString OAuthCodeVerifier; FString OAuthCSRFState;` — ---- OAuth 2.0 state ----

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API MCPCLIENTTOOLSET_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/Toolsets/MCPClientToolset/Source/MCPClientToolset/Public/MCPClientToolset/MCPClientToolsetSubsystem.h` (Public)


#### class `UMCPClientToolsetSubsystem`  
`class UMCPClientToolsetSubsystem : public UEditorSubsystem`  
_L18-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Editor subsystem that reads UMCPToolsetSettings on startup, creates FMCPClientToolset instances, and registers them with UToolsetRegistrySubsystem.
- L23 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L24 _public prototype_ `virtual void Deinitialize() override;`
- L27 _private member_ `TArray<TSharedPtr<UE::ToolsetRegistry::FMCPClientToolset>> Toolsets;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ToolsetRegistry` (scope `UE`)

### `Plugins/Experimental/Toolsets/MCPClientToolset/Source/MCPClientToolset/Public/MCPClientToolset/MCPToolsetSettings.h` (Public)


#### enum `EMCPTransport`  
`enum class EMCPTransport : uint8`  
_L11-15_
- reflection: `UENUM(BlueprintType)`
- desc: Transport protocol for an MCP server connection.
- L13 _public enumerator_ `SSE UMETA(DisplayName="Legacy SSE (HTTP+SSE)")`
- L14 _public enumerator_ `StreamableHTTP UMETA(DisplayName="Streamable HTTP")`

#### enum `EMCPAuth`  
`enum class EMCPAuth : uint8`  
_L19-24_
- reflection: `UENUM(BlueprintType)`
- desc: Authentication method for an MCP server connection.
- L21 _public enumerator_ `None UMETA(DisplayName="None")`
- L22 _public enumerator_ `BearerToken UMETA(DisplayName="Bearer Token (API Key)")`
- L23 _public enumerator_ `OAuth2 UMETA(DisplayName="OAuth 2.0 (Authorization Code + PKCE)")`

#### struct `FMCPServerConfig`  
`struct FMCPServerConfig`  
_L28-69_
- reflection: `USTRUCT(BlueprintType)`
- desc: Configuration for a single MCP server connection.
- L34 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Config, Category = "MCP Server")` — Display name for this MCP server (used as the toolset name).
- L39 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Config, Category = "MCP Server")` — Human-readable description of this toolset, surfaced to the AI as context. If empty, the name is used instead.
- L43 _public member_ `FString ServerUrl;` — `UPROPERTY(EditAnywhere, Config, Category = "MCP Server")` — Base URL of the MCP server (e.g., http://localhost:3000).
- L47 _public member_ `FString ApiKey;` — `UPROPERTY(EditAnywhere, Config, Category = "MCP Server")` — Optional API key sent as "Authorization: Bearer <ApiKey>".
- L51 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Config, Category = "MCP Server")` — Whether this server config is active. Disabled configs are skipped on startup.
- L55 _public member_ `EMCPTransport Transport = EMCPTransport::SSE;` — `UPROPERTY(EditAnywhere, Config, Category = "Connection")` — Transport protocol to use when connecting to this server.
- L59 _public member_ `EMCPAuth Auth = EMCPAuth::BearerToken;` — `UPROPERTY(EditAnywhere, Config, Category = "Authentication")` — Authentication method to use when connecting to this server.
- L64 _public member_ `FString OAuthClientId;` — `UPROPERTY(EditAnywhere, Config, Category = "Authentication")` — OAuth 2.0 client ID. Leave empty to use RFC 7591 dynamic client registration (the server assigns a client ID automatically — no app registration required).
- L68 _public member_ `FString OAuthScope;` — `UPROPERTY(EditAnywhere, Config, Category = "Authentication")` — OAuth 2.0 scope string, e.g. "read:me offline_access" (required when Auth = OAuth2).

#### class `UMCPToolsetSettings`  
`class UMCPToolsetSettings : public UDeveloperSettings`  
_L74-88_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "MCP Toolset Servers"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Editor settings for MCP (Model Context Protocol) server connections. Configure servers under Editor Preferences > Plugins > MCP Toolset Servers.
- L79 _public prototype_ `UMCPToolsetSettings();`
- L83 _public member_ `TArray<FMCPServerConfig> MCPServers;` — `UPROPERTY(EditAnywhere, Config, Category = "MCP Servers")` — List of MCP servers to connect to on editor startup.
- L85 _public function_ `virtual FName GetContainerName() const override`
- L86 _public function_ `virtual FName GetCategoryName() const override`
- L87 _public function_ `virtual FName GetSectionName() const override`
