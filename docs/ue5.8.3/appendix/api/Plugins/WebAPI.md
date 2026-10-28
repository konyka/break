# Plugins / WebAPI

- module root: `Plugins/Experimental/Web/WebAPI/Source/WebAPI`
- headers: 13; symbols: 198
- symbol kinds: class=13, delegate=2, function=38, member=35, namespace=4, prototype=70, struct=3, typedef=2, variable=31
- PrivateDependencyModuleNames: Engine, HTTP, Json, JsonUtilities, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Private/WebAPILog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPI, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPI, Log, All);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Private/WebAPIModule.h` (Private)


#### class `FWebAPIModule`  
`class FWebAPIModule final : public IWebAPIModuleInterface`  
_L8-14_
- inherits: `IWebAPIModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Private/WebAPIStats.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("WebAPI"), STATGROUP_WebAPI, STATCAT_Adva`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/IWebAPIModule.h` (Public)


#### class `IWebAPIModuleInterface`  
`class IWebAPIModuleInterface : public IModuleInterface`  
_L10-27_
- inherits: `IModuleInterface`
- L13 _public function_ `virtual void StartupModule() override`
- L14 _public function_ `virtual void ShutdownModule() override`
- L16 _public function_ `static IWebAPIModuleInterface& Get()`
- L23 _public prototype_ `template <typename PayloadType> static TSharedRequest<PayloadType> CreateRequest(const FString& InURL, const FString& Verb = TEXT("POST"), const FString& ContentType = TEXT("`
- L26 _public prototype_ `template<typename PayloadType> static TSharedRequest<PayloadType> BatchRequests(TArray<TSharedRequest<PayloadType>>&& Requests);`
- L30 _function_ `template <typename PayloadType> TSharedRequest<PayloadType> IWebAPIModuleInterface::CreateRequest(const FString& InURL, const FString& Verb, const FString& ContentType)`
- L41 _function_ `template <typename PayloadType> TSharedRequest<PayloadType> IWebAPIModuleInterface::BatchRequests(TArray<TSharedRef<TRequest<PayloadType>>>&& Requests)`

#### Free symbols / members of external scopes

- L51 _typedef_ `using FTRequestPayloadRef = TSharedRef<TRequest<PayloadType>>;` (scope `IWebAPIModuleInterface::BatchRequests`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/Security/WebAPIAuthentication.h` (Public)


#### class `UWebAPIAuthenticationSettings`  
`class UWebAPIAuthenticationSettings : public UDeveloperSettings`  
_L20-28_
- reflection: `UCLASS(Abstract, Config="Engine")`
- inherits: `UDeveloperSettings`
- L27 _public member_ `FName SchemeName;` — `UPROPERTY(BlueprintReadOnly, Category = "Security")` — Public client identifier.

#### class `UWebAPIOAuthSettings`  
`class UWebAPIOAuthSettings : public UWebAPIAuthenticationSettings`  
_L34-75_
- reflection: `UCLASS(Config="Engine", PerObjectConfig)`
- inherits: `UWebAPIAuthenticationSettings`
- L39 _public prototype_ `UWebAPIOAuthSettings();`
- L43 _public member_ `FString ClientId;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Security")` — Public client identifier.
- L47 _public member_ `FString ClientSecret;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Security")` — Private client secret.
- L51 _public member_ `FString TokenType = TEXT("Bea` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Security")` — Token type, ie. Bearer
- L55 _public member_ `FString AccessToken;` — `UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "Security")` — Private token returned by the server.
- L59 _public member_ `FDateTime ExpiresOn;` — `UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "Security")` — Private token expiration returned by the server.
- L63 _public member_ `FString AuthenticationServer;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Security")` — Authentication endpoint.
- L67 _public member_ `TMap<FString, FString> AdditionalRequestQueryParameters;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Security")` — Additional query parameters to add to auth request. Each key should be present in the Url.
- L71 _public member_ `TMap<FString, FString> AdditionalRequestBodyParameters;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Security")` — Additional content key/value pairs to add to auth request.
- L74 _public prototype_ `bool IsValid() const;` — Returns true if this contains sufficient information to request authentication.

#### class `FWebAPIAuthenticationSchemeHandler`  
`class FWebAPIAuthenticationSchemeHandler : public FWebAPIHttpRequestHandlerInterface , public FWebAPIHttpResponseHandlerInterface`  
_L77-86_
- inherits: `FWebAPIHttpRequestHandlerInterface,FWebAPIHttpResponseHandlerInterface`
- L82 _public prototype_ `virtual ~FWebAPIAuthenticationSchemeHandler() override = default;`
- L84 _public prototype_ `virtual bool HandleHttpRequest(TSharedPtr<IHttpRequest> InRequest, UWebAPIDeveloperSettings* InSettings) override = 0;`
- L85 _public prototype_ `virtual bool HandleHttpResponse(EHttpResponseCodes::Type InResponseCode, TSharedPtr<IHttpResponse> InResponse, bool bInWasSuccessful, UWebAPIDeveloperSettings* InSettings) override = 0;`

#### class `FWebAPIOAuthSchemeHandler`  
`class FWebAPIOAuthSchemeHandler : public FWebAPIAuthenticationSchemeHandler`  
_L88-99_
- inherits: `FWebAPIAuthenticationSchemeHandler`
- L92 _public prototype_ `virtual bool HandleHttpRequest(TSharedPtr<IHttpRequest> InRequest, UWebAPIDeveloperSettings* InSettings) override;`
- L93 _public prototype_ `virtual bool HandleHttpResponse(EHttpResponseCodes::Type InResponseCode, TSharedPtr<IHttpResponse> InResponse, bool bInWasSuccessful, UWebAPIDeveloperSettings* InSettings) override;`
- L96 _private prototype_ `UWebAPIOAuthSettings* GetAuthSettings(const UWebAPIDeveloperSettings* InSettings);`
- L98 _private member_ `TWeakObjectPtr<UWebAPIOAuthSettings> CachedAuthSettings;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPIDeveloperSettings.h` (Public)


#### class `UWebAPIDeveloperSettings`  
`class UWebAPIDeveloperSettings : public UDeveloperSettings , public FWebAPIHttpResponseHandlerInterface`  
_L19-85_
- reflection: `UCLASS(Abstract, Config="Engine", DefaultConfig)`
- inherits: `UDeveloperSettings,FWebAPIHttpResponseHandlerInterface`
- desc: The base class of any auto generated WebAPI settings object.
- L26 _public prototype_ `UWebAPIDeveloperSettings();`
- L30 _public member_ `FString Host;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings")` — The default host address to access this API.
- L34 _public member_ `FString BaseUrl;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings")` — The Url path relative to the host address, ie. "/V1".
- L38 _public member_ `FString UserAgent = TEXT("X-U` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings")` — The UserAgent to encode in Http request headers.
- L42 _public member_ `FString DateTimeFormat;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings")` — The date-time format this API uses to encode/decode from string.
- L46 _public member_ `bool bOverrideScheme = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))` — Whether to override the URI scheme.
- L50 _public member_ `FString URISchemeOverride = TEXT("htt` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverrideScheme"))` — User specified Uniform Resource Identifier scheme.
- L54 _public member_ `TArray<FString> URISchemes;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")` — Uniform Resource Identifier schemes (ie. https, http).
- L58 _public member_ `bool bLogRequests = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Developer")` — Whether to print requests to the output log, useful for debugging.
- L62 _public member_ `TArray<TObjectPtr<UWebAPIAuthenticationSettings>> AuthenticationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, NoClear, EditFixedSize, Category = "Security", meta = (TitleProperty = "SchemeName"))` — Authentication settings per security scheme.
- L65 _public prototype_ `FString FormatUrl(const FString& InSubPath) const;` — Returns a fully formatted Url, including the sub-path.
- L68 _public prototype_ `FString GetURI() const;` — Returns the most secure URI, or the user specified URI if enabled.
- L70 _public prototype_ `virtual TMap<FString, FString> MakeDefaultHeaders(const FName& InVerb) const;`
- L72 _public prototype_ `virtual const TArray<TSharedPtr<FWebAPIAuthenticationSchemeHandler>>& GetAuthenticationHandlers() const;`
- L75 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L81 _protected member_ `TArray<TSharedPtr<FWebAPIAuthenticationSchemeHandler>> AuthenticationHandlers;`
- L84 _protected prototype_ `virtual bool HandleHttpResponse(EHttpResponseCodes::Type InResponseCode, TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> InResponse, bool bInWasSuccessful, UWebAPIDeveloperSettings* InSettings) override;` — Called for all responses, providing the opportunity for custom interception.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPIHttpMessageHandlers.h` (Public)


#### class `FWebAPIHttpRequestHandlerInterface`  
`class FWebAPIHttpRequestHandlerInterface`  
_L12-20_
- desc: Implementers receive any Http Request for their owning API.
- L15 _protected prototype_ `virtual ~FWebAPIHttpRequestHandlerInterface() = default;`
- L19 _public prototype_ `virtual bool HandleHttpRequest(TSharedPtr<IHttpRequest> InRequest, UWebAPIDeveloperSettings* InSettings) = 0;` — Return true if the request was handled, subsequent handlers won't be called.

#### class `FWebAPIHttpResponseHandlerInterface`  
`class FWebAPIHttpResponseHandlerInterface`  
_L24-32_
- desc: Implementers receive any Http Response for their owning API.
- L27 _protected prototype_ `virtual ~FWebAPIHttpResponseHandlerInterface() = default;`
- L31 _public prototype_ `virtual bool HandleHttpResponse(EHttpResponseCodes::Type InResponseCode, TSharedPtr<IHttpResponse> InResponse, bool bInWasSuccessful, UWebAPIDeveloperSettings* InSettings) = 0;` — Return true if the response was handled, subsequent handlers won't be called.

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPIHttpRequest.h` (Public)


#### class `TRequest`  
`template <typename PayloadType> class TRequest : public TSharedFromThis<TRequest<PayloadType>>, public FNoncopyable`  
_L12-69_
- inherits: `TSharedFromThis<TRequest<PayloadType>>,FNoncopyable`
- L15 _public prototype_ `void InitializeRequest(const FString& Route, const FString& InVerb = TEXT("POST"), const FString& InContentType = TEXT("`
- L17 _public prototype_ `[[nodiscard]] static TSharedRef<TRequest<PayloadType>> CopyHeadersToNewRequest(const TSharedRef<TRequest<PayloadType>>& Original);`
- L19 _public prototype_ `void Post() const;`
- L20 _public prototype_ `void Post(PayloadType&& InPayload);`
- L21 _public prototype_ `void Post(PayloadType&& InPayload, TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)> CompletionCallback);`
- L23 _public prototype_ `void Get() const;`
- L25 _public prototype_ `[[nodiscard]] TRequest<PayloadType>& AddHeader(TPair<FString, FString> NewHeader) const;`
- L26 _public prototype_ `[[nodiscard]] TRequest<PayloadType>& BindCompletionCallback(TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)> CompletionCallback);`
- L28 _public prototype_ `[[nodiscard]] TRequest<PayloadType>& BindProgressCallback(TFunction<void(FHttpRequestPtr, int32 , int32 )> ProgressCallback);` — `UE_DEPRECATED(5.3, "BindProgressCallback has been deprecated, use BindProgressCallback64 instead")`
- L29 _public prototype_ `[[nodiscard]] TRequest<PayloadType>& BindProgressCallback64(TFunction<void(FHttpRequestPtr, uint64 , uint64 )> ProgressCallback);`
- L30 _public prototype_ `[[nodiscard]] TRequest<PayloadType>& BindRetryCallback(TFunction<void(FHttpRequestPtr, FHttpResponsePtr, float )> RetryCallback);`
- L31 _public prototype_ `[[nodiscard]] TRequest<PayloadType>& BindHeaderReceivedCallback(TFunction<void(FHttpRequestPtr, const FString& , const FString& )> HeaderReceivedCallback);`
- L32 _public prototype_ `TRequest<PayloadType>& SetPayloadData(const PayloadType& InPayloadData);`
- L33 _public prototype_ `TRequest<PayloadType>& SetPayloadData(TArray<uint8>& InPayloadData);`
- L35 _public prototype_ `[[nodiscard]] bool HasPayload() const;`
- L37 _public function_ `[[nodiscard]] inline FString GetVerb() const`
- L38 _public function_ `[[nodiscard]] inline FString GetContentType() const`
- L39 _public function_ `[[nodiscard]] inline FString GetRoute() const`
- L41 _public prototype_ `void SetHeaders(const TMap<FString, FString>& Headers) const;`
- L42 _public prototype_ `[[nodiscard]] TMap<FString, FString> GetAllHeaders() const;`
- L44 _public prototype_ `void SetRoute(const FString& InURL) const;`
- L45 _public prototype_ `void SetVerb(const FString& InVerb) const;`
- L47 _public prototype_ `TValueOrError<FString, FString> PayloadToString() const;`
- L49 _public function_ `bool operator==(const TRequest<PayloadType>& Rhs) const`
- L54 _public function_ `bool operator!=(const TRequest<PayloadType>& Rhs) const`
- L59 _public function_ `void operator()() const`
- L66 _private prototype_ `TValueOrError<FString, FString> PayloadToString_Internal(const PayloadType& InContent) const;`
- L68 _private member_ `TSharedRef<IHttpRequest> InternalRequest = FHttpModule::Get().CreateRequest();`
- L72 _function_ `template <typename PayloadType> TValueOrError<FString, FString> TRequest<PayloadType>::PayloadToString() const`
- L105 _function_ `template <typename PayloadType> void TRequest<PayloadType>::SetHeaders(const TMap<FString, FString>& Headers) const`
- L114 _function_ `template <typename PayloadType> TMap<FString, FString> TRequest<PayloadType>::GetAllHeaders() const`
- L138 _function_ `template <typename PayloadType> void TRequest<PayloadType>::SetRoute(const FString& InURL) const`
- L144 _function_ `template <typename PayloadType> void TRequest<PayloadType>::SetVerb(const FString& InVerb) const`
- L150 _function_ `template <typename PayloadType> void TRequest<PayloadType>::InitializeRequest(const FString& Route, const FString& InVerb, const FString& InContentType)`
- L163 _function_ `template <typename PayloadType> TSharedRef<TRequest<PayloadType>> TRequest<PayloadType>::CopyHeadersToNewRequest(const TSharedRef<TRequest<PayloadType>>& Original)`
- L173 _function_ `template <typename PayloadType> void TRequest<PayloadType>::Post() const`
- L180 _function_ `template <typename PayloadType> void TRequest<PayloadType>::Post(PayloadType&& InPayload)`
- L188 _function_ `template <typename PayloadType> void TRequest<PayloadType>::Post(PayloadType&& InPayload, TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)> CompletionCallback)`
- L198 _function_ `template <typename PayloadType> void TRequest<PayloadType>::Get() const`
- L205 _function_ `template <typename PayloadType> TRequest<PayloadType>& TRequest<PayloadType>::AddHeader(TPair<FString, FString> NewHeader) const`
- L212 _function_ `template <typename PayloadType> TRequest<PayloadType>& TRequest<PayloadType>::BindCompletionCallback(TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)> CompletionCallback)`
- L219 _function_ `template <typename PayloadType> TRequest<PayloadType>& TRequest<PayloadType>::BindProgressCallback64(TFunction<void(FHttpRequestPtr, uint64, uint64)> ProgressCallback)`
- L226 _function_ `template <typename PayloadType> TRequest<PayloadType>& TRequest<PayloadType>::BindRetryCallback(TFunction<void(FHttpRequestPtr, FHttpResponsePtr, float)> RetryCallback)`
- L233 _function_ `template <typename PayloadType> TRequest<PayloadType>& TRequest<PayloadType>::BindHeaderReceivedCallback(TFunction<void(FHttpRequestPtr, const FString&, const FString&)> HeaderReceivedCallback)`
- L240 _function_ `template <typename PayloadType> TRequest<PayloadType>& TRequest<PayloadType>::SetPayloadData(const PayloadType& InPayloadData)`
- L252 _function_ `template <typename PayloadType> TRequest<PayloadType>& TRequest<PayloadType>::SetPayloadData(TArray<uint8>& InPayloadData)`
- L259 _function_ `template <typename PayloadType> bool TRequest<PayloadType>::HasPayload() const`
- L265 _function_ `template <typename PayloadType> TValueOrError<FString, FString> TRequest<PayloadType>::PayloadToString_Internal(const PayloadType& InContent) const`

#### Free symbols / members of external scopes

- L80 _function_ `` (scope `TRequest::PayloadToString`)
- L279 _typedef_ `template<typename T> using TSharedRequest = TSharedRef<TRequest<T>>;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPIMessageResponse.h` (Public)


#### struct `FWebAPIMessageResponse`  
`struct FWebAPIMessageResponse`  
_L12-19_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public prototype_ `virtual ~FWebAPIMessageResponse() = default;`
- L18 _public prototype_ `virtual const FText& GetMessage() const;`
- L21 _function_ `inline const FText& FWebAPIMessageResponse::GetMessage() const`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPIOperationObject.h` (Public)


#### class `UWebAPIOperationObject`  
`class UWebAPIOperationObject : public UObject`  
_L17-78_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Baseclass for an asynchronous Http request/response operation.
- L26 _public member_ `FText Message;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")` — Can contain a response or status message.
- L29 _public prototype_ `virtual void Reset();` — Reset to initial state.
- L69 _protected member_ `TSharedPtr<IHttpRequest> HttpRequest;` — Active HttpRequest.
- L72 _protected member_ `TSharedPtr<TPromise<FRawResponse>, ESPMode::ThreadSafe> Promise;` — Pending Response Promise.
- L74 _protected prototype_ `void OnResponse(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bInWasSuccessful, UWebAPIDeveloperSettings* InSettings) const;`
- L77 _protected prototype_ `TFuture<FRawResponse> RequestInternal(const FName& InVerb, UWebAPIDeveloperSettings* InSettings, TUniqueFunction<void(const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>)> OnRequestCreated);` — Creates and dispatches a Request, then returns the Response. Use OnRequestCreated callback to inject Request properties.

#### struct `UWebAPIOperationObject::FRawResponse`  
`struct FRawResponse`  
_L32-66_
- L34 _public function_ `FRawResponse(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bInWasSuccessful, bool bInWasCancelled = false) : Request(InRequest) , Response(InResponse) , bWasSuccessful(bInWasSuccessful) , bWasCancelled(bInWasCancelled)`
- L45 _public prototype_ `FRawResponse(const FRawResponse& Other) = default;`
- L47 _public function_ `FRawResponse(FRawResponse&& Other) noexcept : bWasSuccessful(Other.bWasSuccessful) , bWasCancelled(Other.bWasCancelled)`
- L62 _public member_ `FHttpRequestPtr Request = nullptr;`
- L63 _public member_ `FHttpResponsePtr Response = nullptr;`
- L64 _public member_ `bool bWasSuccessful = false;`
- L65 _public member_ `bool bWasCancelled = false;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPISubsystem.h` (Public)


#### struct `FWebAPIPooledOperation`  
`struct FWebAPIPooledOperation`  
_L20-41_
- reflection: `USTRUCT()`
- desc: Container for an Operation object pool, per operation type (class).
- L26 _public member_ `TSoftClassPtr<UWebAPIOperationObject> ItemClass;` — `UPROPERTY()` — Operation Class (also acts as a key).
- L30 _public member_ `TArray<TObjectPtr<UWebAPIOperationObject>> AvailableItems;` — `UPROPERTY()` — Pool of un-used operations.
- L34 _public member_ `TArray<TObjectPtr<UWebAPIOperationObject>> ItemsInUse;` — `UPROPERTY()` — Pool of operations currently in use.
- L37 _public prototype_ `TObjectPtr<UWebAPIOperationObject> Pop();` — Returns a new or pooled Item.
- L40 _public prototype_ `bool Push(const TObjectPtr<UWebAPIOperationObject>& InItem);` — Returns the item back to the pool.

#### class `UWebAPISubsystem`  
`class UWebAPISubsystem : public UEngineSubsystem , public FTickableGameObject , public FWebAPIHttpRequestHandlerInterface , public FWebAPIHttpResponseHandlerInterface`  
_L45-110_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem,FTickableGameObject,FWebAPIHttpRequestHandlerInterface,FWebAPIHttpResponseHandlerInterface`
- desc: Common functionality and top-level parent for shared objects.
- L54 _public prototype_ `UWebAPISubsystem();`
- L57 _public prototype_ `TObjectPtr<UWebAPIOperationObject> MakeOperation(const UWebAPIDeveloperSettings* InSettings, const TSubclassOf<UWebAPIOperationObject>& InClass);` — Get or create pooled operation for the given OperationType.
- L61 _public prototype_ `template <typename OperationType> TObjectPtr<OperationType> MakeOperation(const UWebAPIDeveloperSettings* InSettings);` — Get or create pooled operation for the given OperationType.
- L64 _public prototype_ `void ReleaseOperation(const TSubclassOf<UWebAPIOperationObject>& InClass, const TObjectPtr<UWebAPIOperationObject>& InOperation);` — Returns the provided operation to the pool, making it available for re-use.
- L68 _public prototype_ `template <typename OperationType> void ReleaseOperation(const TObjectPtr<OperationType>& InOperation);` — Returns the provided operation to the pool, making it available for re-use.
- L71 _public prototype_ `TFuture<TTuple<TSharedPtr<IHttpResponse, ESPMode::ThreadSafe>, bool>> MakeHttpRequest(const FString& InVerb, TUniqueFunction<void(const TSharedRef<class IHttpRequest, ESPMode::ThreadSafe>)> OnRequestCreated);` — Convenience function to create a simple Http request.
- L74 _public prototype_ `void RetryRequestsForHost(const FString& InHost);` — Retry any failed and buffered requests for the given host.
- L77 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L78 _public prototype_ `virtual void Deinitialize() override;`
- L82 _public function_ `virtual UWorld* GetTickableGameObjectWorld() const override` — FTickableGameObject implementation Begin
- L83 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L84 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L85 _public prototype_ `virtual TStatId GetStatId() const override;`
- L92 _private member_ `bool bUsePooling = false;` — `UPROPERTY()`
- L95 _private member_ `TMap<FName, FWebAPIPooledOperation> OperationPool;` — `UPROPERTY(Transient)`
- L98 _private member_ `TArray<TSharedRef<IHttpRequest>> RequestBuffer;` — Requests to process.
- L101 _private member_ `TMap<FString, TArray<TSharedRef<IHttpRequest>>> HostRequestBuffer;` — Requests retained per host for retry when response code indicates an auth error.
- L104 _private prototype_ `virtual bool HandleHttpRequest(TSharedPtr<IHttpRequest> InRequest, UWebAPIDeveloperSettings* InSettings) override;` — Return true if the request was handled, subsequent handlers won't be called.
- L107 _private prototype_ `virtual bool HandleHttpResponse(EHttpResponseCodes::Type InResponseCode, TSharedPtr<IHttpResponse> InResponse, bool bInWasSuccessful, UWebAPIDeveloperSettings* InSettings) override;` — Called for all responses, providing the opportunity for custom interception.
- L109 _private prototype_ `void OnEndPlayMap();`
- L113 _function_ `template <typename OperationType> TObjectPtr<OperationType> UWebAPISubsystem::MakeOperation(const UWebAPIDeveloperSettings* InSettings)`
- L120 _function_ `template <typename OperationType> void UWebAPISubsystem::ReleaseOperation(const TObjectPtr<OperationType>& InOperation)`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPITypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace WebAPI` (scope `UE`)
- L9 _namespace_ `namespace HttpVerb` (scope `UE::WebAPI`)
- L11 _variable_ `static const FName NAME_Post = FName(TEXT("POST` (scope `UE::WebAPI::HttpVerb`)
- L12 _variable_ `static const FName NAME_Get = FName(TEXT("GET"` (scope `UE::WebAPI::HttpVerb`)
- L13 _variable_ `static const FName NAME_Put = FName(TEXT("PUT"` (scope `UE::WebAPI::HttpVerb`)
- L14 _variable_ `static const FName NAME_Patch = FName(TEXT("PATC` (scope `UE::WebAPI::HttpVerb`)
- L15 _variable_ `static const FName NAME_Delete = FName(TEXT("DELE` (scope `UE::WebAPI::HttpVerb`)
- L16 _variable_ `static const FName NAME_Head = FName(TEXT("HEAD` (scope `UE::WebAPI::HttpVerb`)
- L17 _variable_ `static const FName NAME_Options = FName(TEXT("OPTI` (scope `UE::WebAPI::HttpVerb`)
- L18 _variable_ `static const FName NAME_Trace = FName(TEXT("TRAC` (scope `UE::WebAPI::HttpVerb`)
- L21 _namespace_ `namespace MimeType` (scope `UE::WebAPI`)
- L26 _variable_ `static const FName NAME_Html = FName(TEXT("text` (scope `UE::WebAPI::MimeType`) — Web
- L27 _variable_ `static const FName NAME_Css = FName(TEXT("text` (scope `UE::WebAPI::MimeType`)
- L28 _variable_ `static const FName NAME_Js = FName(TEXT("appl` (scope `UE::WebAPI::MimeType`)
- L31 _variable_ `static const FName NAME_Avi = FName(TEXT("vide` (scope `UE::WebAPI::MimeType`) — Video
- L32 _variable_ `static const FName NAME_Mpeg = FName(TEXT("vide` (scope `UE::WebAPI::MimeType`)
- L35 _variable_ `static const FName NAME_Bmp = FName(TEXT("imag` (scope `UE::WebAPI::MimeType`) — Image
- L36 _variable_ `static const FName NAME_Gif = FName(TEXT("imag` (scope `UE::WebAPI::MimeType`)
- L37 _variable_ `static const FName NAME_Jpg = FName(TEXT("imag` (scope `UE::WebAPI::MimeType`)
- L38 _variable_ `static const FName NAME_Jpeg = FName(TEXT("imag` (scope `UE::WebAPI::MimeType`)
- L39 _variable_ `static const FName NAME_Png = FName(TEXT("imag` (scope `UE::WebAPI::MimeType`)
- L40 _variable_ `static const FName NAME_Svg = FName(TEXT("imag` (scope `UE::WebAPI::MimeType`)
- L41 _variable_ `static const FName NAME_Tiff = FName(TEXT("imag` (scope `UE::WebAPI::MimeType`)
- L44 _variable_ `static const FName NAME_Midi = FName(TEXT("audi` (scope `UE::WebAPI::MimeType`) — Audio
- L45 _variable_ `static const FName NAME_Mp3 = FName(TEXT("audi` (scope `UE::WebAPI::MimeType`)
- L46 _variable_ `static const FName NAME_Ogg = FName(TEXT("audi` (scope `UE::WebAPI::MimeType`)
- L47 _variable_ `static const FName NAME_Wav = FName(TEXT("audi` (scope `UE::WebAPI::MimeType`)
- L50 _variable_ `static const FName NAME_Xml = FName(TEXT("appl` (scope `UE::WebAPI::MimeType`) — Documents
- L51 _variable_ `static const FName NAME_Txt = FName(TEXT("text` (scope `UE::WebAPI::MimeType`)
- L52 _variable_ `static const FName NAME_Tsv = FName(TEXT("text` (scope `UE::WebAPI::MimeType`)
- L53 _variable_ `static const FName NAME_Csv = FName(TEXT("text` (scope `UE::WebAPI::MimeType`)
- L54 _variable_ `static const FName NAME_Json = FName(TEXT("appl` (scope `UE::WebAPI::MimeType`)
- L57 _variable_ `static const FName NAME_Zip = FName(TEXT("appl` (scope `UE::WebAPI::MimeType`) — Compressed
- L59 _variable_ `static const FName NAME_Unknown = FName(TEXT("appl` (scope `UE::WebAPI::MimeType`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPIUtilities.h` (Public)


#### class `UWebAPIUtilities`  
`class UWebAPIUtilities : public UBlueprintFunctionLibrary`  
_L15-27_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L22 _public prototype_ `static const FText& GetResponseMessage(const FWebAPIMessageResponse& MessageResponse);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="WebAPI")` — Return the message from the provided response.
- L26 _public prototype_ `static FString GetHostFromUrl(const FString& InUrl);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="WebAPI")` — Return the host (only) from the provided Url.
