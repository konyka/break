# Runtime / ExternalRpcRegistry

- module root: `Source/Runtime/ExternalRPCRegistry`
- headers: 2; symbols: 90
- symbol kinds: class=2, delegate=1, function=12, macro=2, member=33, prototype=34, struct=6
- PrivateDependencyModuleNames: Core, CoreUObject, HTTP, HTTPServer, Json

### `Source/Runtime/ExternalRPCRegistry/Public/ExternalRpcRegistrationComponent.h` (Public)


#### class `UExternalRpcRegistrationComponent`  
`class UExternalRpcRegistrationComponent : public UObject`  
_L26-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L31 _public member_ `TArray<FName> RegisteredRoutes;`
- L32 _public member_ `FString SecuritySecret;`
- L36 _public member_ `FString SenderID;` — Outgoing RPC info
- L37 _public member_ `FString ListenerAddress;`
- L39 _public prototype_ `UExternalRpcRegistrationComponent();`
- L48 _public prototype_ `TSharedPtr<FJsonObject> GetJsonObjectFromRequestBody(const TArray<uint8>& InRequestBody);` — Deserializes the incoming request body into a JSON object @param  InRequestBody  Incoming array of bytes from the request @return Valid JSON object on a successful deserialization; otherwise returns a nullptr
- L53 _public prototype_ `virtual void DeregisterHttpCallbacks();` — Deregisters and cleans up all routes managed by this component.
- L58 _public prototype_ `virtual void RegisterAlwaysOnHttpCallbacks();` — Registration function for RPCs that should always be enabled as long as this Registration Component is active.
- L63 _public prototype_ `void BroadcastRpcListChanged();` — Function called when RPCs are registered or deregistered to notify any listeners that they need to refresh their RPC list.
- L71 _public prototype_ `void RegisterHttpCallback(FExternalRouteInfo InRouteInfo, const FHttpRequestHandler& Handler, bool bOverrideIfBound = false);` — Hooks up a given delegate to the assigned route for external access. Use if you already have an FExternalRouteInfo object. @param  InRouteInfo A fully initialized FExternalRouteInfo object that describes the overall endpoint. @param  Handler  The function delegate to call when this route is accessed. @param  bOverrideIfBound  Whether or not this registry should override any previously registered route.
- L84 _public prototype_ `void RegisterHttpCallback(FName RouteName, const FHttpPath& HttpPath, const EHttpServerRequestVerbs& RequestVerbs, const FHttpRequestHandler& Handler, bool bOverrideIfBound = false, FString OptionalCategory = TEXT(""), FString OptionalContentType = {}, TArray<FExternalRpcArgumentDesc> OptionalInArguments = TArray<FExternalRpcArgumentDesc>());` — Hooks up a given delegate to the assigned route for external access. Handles creation of FExternalRouteInfo from its core parts. @param  RouteName   The friendly name of the route - used frequently in gauntlet for easier use. @param  HttpPath  Desired route for this delegate. Will be appended onto http://<host>:<listenport> @param  RequestVerbs  Verbs that should be accepted on this route. @param  Handler  The function delegate to call when this route is accessed. @param  bOverrideIfBound  Whether or not this registry should override any previously registered delegate at this route. @param  OptionalCategory  An optional category that can be added for organizational purposes @param  OptionalContentType  The sort of content type that is expected for the request body @param  OptionalInArguments  A list of arguments expected by this route. Can be set to optional or mandatory.
- L95 _public prototype_ `bool HttpSendMessageToListener(FString MessageCategory, FString MessagePayload);` — Send a message to all listeners with a custom category and payload for consumption by external processes. @param  MessageCategory   The category of the message to be sent. @param  MessagePayload  The payload of the message to be sent. @return Always needs to return true because of how the HttpRequest works.
- L105 _public prototype_ `bool HttpUpdateIpOnListener(FString TargetName, FString MessagePayload);` — Send a message to all listeners describing the game IP of the current process. Mostly used when dealing with devices that have more than one IP to signify what its hostname should be. @param  TargetName   The name of the target process updating its ip. @param  MessagePayload  The IP of the process. @return Always needs to return true because of how the HttpRequest works.
- L111 _public prototype_ `FHttpRequestHandler CreateRouteHandle(TDelegate<bool(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)> InFunc);` — Creates an Http Request Handler that gets routed through the additional handling of the ExternalRpcRegistry @param  InFunc   A delegate to be prepared for attachment to a route. @return An FHttpRequestHandler delegate object that can be assigned a route in RegisterHttpCallback
- L120 _public prototype_ `TUniquePtr<FHttpServerResponse> CreateSimpleResponse(bool bInWasSuccessful, FString InValue = "", bool bInFatal = false);` — Generates a simple Json response object with success and reason for use when returning a response. @param  bInWasSuccessful   Whether or not the Rpc completed successfully @param  InValue  Optional result description string that will be returned with the success bool @param  bInFatal  Whether or not the response should be considered fatal and not worth retrying.
- L130 _protected prototype_ `void AppendTimingContextToResponse(TUniquePtr<FHttpServerResponse>& InResponse, FRpcTimingContext& InTimingContext);` — Appends timing context information to a response @param  InResponse		The response to append execution time to @param  InTimingContext  Handle to the timing context that was used to measure the execution time

#### Free symbols / members of external scopes

- L13 _macro_ `#define WITH_RPC_REGISTRY (USE_RPC_REGISTRY_IN_SHIPPING || !UE_BUILD_SHIPPING )`
- L16 _macro_ `#define UE_API EXTERNALRPCREGISTRY_API`

### `Source/Runtime/ExternalRPCRegistry/Public/ExternalRpcRegistry.h` (Public)


#### struct `FExternalRpcArgumentDesc`  
`struct FExternalRpcArgumentDesc`  
_L25-56_
- reflection: `USTRUCT()`
- L29 _public member_ `FString Name;`
- L30 _public member_ `FString Type;`
- L31 _public member_ `FString Desc;`
- L32 _public member_ `bool bIsOptional = false;`
- L34 _public prototype_ `FExternalRpcArgumentDesc() = default;`
- L35 _public function_ `FExternalRpcArgumentDesc(FString InName, FString InType, FString InDesc, bool bInIsOptional = false)`
- L43 _public function_ `bool operator==(const FExternalRpcArgumentDesc& Other) const`
- L52 _public function_ `bool operator!=(const FExternalRpcArgumentDesc& Other) const`

#### struct `FExternalRouteInfo`  
`struct FExternalRouteInfo`  
_L59-100_
- reflection: `USTRUCT()`
- L63 _public member_ `FName RouteName;`
- L64 _public member_ `FHttpPath RoutePath;`
- L65 _public member_ `EHttpServerRequestVerbs RequestVerbs = EHttpServerRequestVerbs::VERB_NONE;`
- L66 _public member_ `FString InputContentType;`
- L67 _public member_ `TArray<FExternalRpcArgumentDesc> ExpectedArguments;`
- L68 _public member_ `FString RpcCategory = "Un`
- L69 _public member_ `bool bAlwaysOn = false;`
- L71 _public prototype_ `FExternalRouteInfo() = default;`
- L73 _public function_ `FExternalRouteInfo(FName InRouteName, FHttpPath InRoutePath, EHttpServerRequestVerbs InRequestVerbs, FString InCategory = TEXT("Unknown"), bool bInAlwaysOn = false, FString InContentType = {}, TArray<FExternalRpcArgumentDesc> InArguments = TArray<FExternalRpcArgumentDesc>())`
- L84 _public function_ `bool operator==(const FExternalRouteInfo& Other) const`
- L96 _public function_ `bool operator!=(const FExternalRouteInfo& Other) const`

#### struct `FExternalRouteDesc`  
`struct FExternalRouteDesc`  
_L103-119_
- reflection: `USTRUCT()`
- L107 _public member_ `FHttpRouteHandle Handle;`
- L108 _public member_ `FString InputContentType;`
- L109 _public member_ `FString RpcCategory;`
- L110 _public member_ `TArray<FExternalRpcArgumentDesc> ExpectedArguments;`
- L111 _public prototype_ `FExternalRouteDesc() = default;`
- L112 _public function_ `FExternalRouteDesc(FHttpRouteHandle InHandle, FString InContentType, TArray<FExternalRpcArgumentDesc> InArguments, FString InCategory = "")`

#### struct `FRpcLedgerEntry`  
`struct FRpcLedgerEntry`  
_L122-136_
- reflection: `USTRUCT()`
- L126 _public member_ `FString RpcName;`
- L127 _public member_ `FString RequestBody;`
- L128 _public member_ `FDateTime RequestTime;`
- L129 _public prototype_ `FRpcLedgerEntry() = default;`
- L130 _public function_ `FRpcLedgerEntry(FString InName, FString InBody)`

#### struct `FRpcConfig`  
`struct FRpcConfig`  
_L140-149_
- reflection: `USTRUCT()`
- L143 _public prototype_ `FRpcConfig() = default;`
- L145 _public member_ `TMap<FString, int> PortMapping;`
- L148 _public member_ `TArray<int> ActiveHostPorts;` — it is valid to have mappings, but no active ports, in the case of a client with multiple endpoint hosts

#### struct `FRpcTimingContext`  
`struct FRpcTimingContext`  
_L156-180_
- reflection: `USTRUCT()`
- desc: Context struct used to measure execution time of RPCs Execution time can be returned in the response to measure actual runtime of the RPC minus the network traffic
- L161 _public member_ `double ExecutionTimeMs;`
- L163 _public function_ `FRpcTimingContext() : ExecutionTimeMs(-1.0)`
- L167 _public function_ `void StartTiming()`
- L172 _public function_ `double StopTiming()`
- L179 _private member_ `FDateTime StartTime;`

#### class `UExternalRpcRegistry`  
`class UExternalRpcRegistry : public UObject`  
_L188-276_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This class is designed to be a singleton that handles registry, maintenance, and cleanup of any REST endpoints exposed on the process for use in communicating with the process externally.
- L192 _protected member_ `static UExternalRpcRegistry * ObjectInstance;`
- L193 _protected member_ `TMap<FName, FExternalRouteDesc> RegisteredRoutes;`
- L194 _protected member_ `TArray<FString> ActiveRpcCategories;`
- L195 _protected member_ `TArray<FRpcLedgerEntry> RequestLedger;`
- L196 _protected member_ `TMap<FName, FName> MultiPortRouteMapping;`
- L197 _protected member_ `TArray<int> PortsToUse;`
- L200 _public prototype_ `static UExternalRpcRegistry * GetInstance();`
- L201 _public prototype_ `static bool IsEnabled();`
- L202 _public prototype_ `static const FRpcConfig& GetRpcConfig();`
- L203 _public prototype_ `~UExternalRpcRegistry();`
- L205 _public member_ `int RequestLedgerCapacity = 10;`
- L207 _public function_ `int GetPortToUse()`
- L215 _public prototype_ `bool IsActiveRpcCategory(FString InCategory);` — Check if this Rpc is from a category that is meant to be enabled.
- L220 _public prototype_ `bool GetRegisteredRoute(FName RouteName, FExternalRouteInfo& OutRouteInfo);` — Try to get a route registered under given friendly name. Returns false if could not be found.
- L222 _public prototype_ `void RegisterNewRoute(FExternalRouteInfo InRouteInfo, const FHttpRequestHandler& Handler, bool bOverrideIfBound = false);`
- L228 _public prototype_ `void RegisterNewRouteWithArguments(FName RouteName, const FHttpPath& HttpPath, const EHttpServerRequestVerbs& RequestVerbs, const FHttpRequestHandler& Handler, TArray<FExternalRpcArgumentDesc> InArguments, bool bOverrideIfBound = false, bool bIsAlwaysOn = false, FString OptionalCategory = TEXT("Unknown"), FString OptionalContentType` — Register a new route. Will override existing routes if option is set, otherwise will error and fail to bind.
- L234 _public prototype_ `void RegisterNewRoute(FName RouteName, const FHttpPath& HttpPath, const EHttpServerRequestVerbs& RequestVerbs, const FHttpRequestHandler& Handler, bool bOverrideIfBound = false, bool bIsAlwaysOn = false, FString OptionalCategory = TEXT("Unknown"), FString OptionalContentType = {}, FString OptionalExpectedFormat` — Deprecated way to register a new route. Will override existing routes if option is set, otherwise will error and fail to bind.
- L239 _public prototype_ `void CleanUpAllRoutes();` — Clean up all routes - generally called as part of the destructor to make sure we don't have any function pointers dangling around.
- L245 _public prototype_ `void CleanUpRoute(FName RouteName, bool bFailIfUnbound = false);` — Clean up a route. Can be set to fail if trying to unbind an unbound route.
- L251 _public prototype_ `bool HttpListOpenRoutes(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Default Route Listing http call. Spits out all registered routes and describes them via a REST API call. Always registered at /listrpcs GET by default
- L255 _public prototype_ `void AddRequestToLedger(const FHttpServerRequest& Request);` — Records an RPC call into the ledger, plus trims the ledger if it is too large.
- L261 _public prototype_ `bool HttpPrintRequestLedger(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Default request history call. Lists all calls recorded in the ledger, showing RPC name, request time, request body Always registered at /requesthistory GET by default
- L267 _public prototype_ `bool HttpListOASv3JSONRoutes(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Route Listing http, formatted for Swagger OASv3. Spits out all registered routes and describes them via a REST API call. Always registered at /swagger.json GET by default
- L274 _public prototype_ `bool HttpSwaggerUI(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Route Showing SwaggerUI using /swagger.json to describe the current REST API. Always registered at /swagger/html.index GET by default

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogExternalRpcRegistry, Log, All);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogExternalRpcRegistry, Log, All);`
