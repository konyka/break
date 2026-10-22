# Plugins / DataLinkOAuth

- module root: `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth`
- headers: 13; symbols: 97
- symbol kinds: class=5, delegate=1, function=6, member=30, namespace=8, prototype=34, struct=8, typedef=3, variable=2
- PrivateDependencyModuleNames: Engine, HTTP, HTTPServer, Json, Sockets
- PublicDependencyModuleNames: Core, CoreUObject, DataLink, DataLinkHttp

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Private/DataLinkOAuthAuthRequest.h` (Private)


#### struct `UE::DataLinkOAuth::FAuthRequestParams`  
`struct FAuthRequestParams`  
_L17-27_
- L20 _public member_ `UDataLinkOAuthSettings* OAuthSettings;` — Settings to used for Authorization
- L23 _public member_ `TStructView<FDataLinkNodeOAuthInstance> OAuthInstanceView;` — OAuth Instance Data to Read from and Write to
- L26 _public member_ `FOnAuthResponse OnAuthResponse;` — Called when the Authorization has been granted

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DataLinkOAuth` (scope `UE`)
- L15 _typedef_ `using FOnAuthResponse = TDelegate<void(const FHttpServerRequest&)>;` (scope `UE::DataLinkOAuth`)
- L29 _prototype_ `bool RequestAuthorization(const FAuthRequestParams& InParams);` (scope `UE::DataLinkOAuth`)

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Private/DataLinkOAuthCodeAccessExchange.h` (Private)


#### struct `UE::DataLinkOAuth::FExchangeAuthCodeParams`  
`struct FExchangeAuthCodeParams`  
_L16-29_
- L19 _public member_ `UDataLinkOAuthSettings* OAuthSettings;` — Settings to used for Authorization
- L22 _public member_ `TStructView<FDataLinkNodeOAuthInstance> OAuthInstanceView;` — OAuth Instance Data to Read from and Write to
- L25 _public member_ `FStringView AuthCodeView;` — Auth Code to exchange for Access Token
- L28 _public member_ `FOnExchangeAuthCodeResponse OnResponse;` — Called when the Exchange Request has received a response

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DataLinkOAuth` (scope `UE`)
- L14 _typedef_ `using FOnExchangeAuthCodeResponse = TDelegate<void(FStringView InResponseString)>;` (scope `UE::DataLinkOAuth`)
- L31 _prototype_ `bool ExchangeAuthCodeForAccess(const FExchangeAuthCodeParams& InParams);` (scope `UE::DataLinkOAuth`)

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Private/DataLinkOAuthLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkOAuth, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkOAuth, Log, All);`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkNodeOAuth.h` (Public)


#### struct `FDataLinkOAuthSettingsWrapper`  
`struct FDataLinkOAuthSettingsWrapper`  
_L19-25_
- reflection: `USTRUCT(BlueprintType, DisplayName="Data Link OAuth Settings")`
- L24 _public member_ `TObjectPtr<UDataLinkOAuthSettings> OAuthSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link")`

#### class `UDataLinkNodeOAuth`  
`class UDataLinkNodeOAuth : public UDataLinkNode`  
_L28-45_
- reflection: `UCLASS(MinimalAPI, DisplayName="OAuth", Category="Authorization")`
- inherits: `UDataLinkNode`
- L33 _public prototype_ `UDataLinkNodeOAuth();`
- L37 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L38 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`
- L42 _private prototype_ `void OnAuthResponse(const FHttpServerRequest& InRequest, TWeakPtr<FDataLinkExecutor> InExecutorWeak) const;`
- L44 _private prototype_ `void OnExchangeCodeResponse(FStringView InResponse, TWeakPtr<FDataLinkExecutor> InExecutorWeak) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DataLinkOAuth` (scope `UE`)
- L14 _variable_ `const FLazyName InputHttp(TEXT("Inpu` (scope `UE::DataLinkOAuth`)
- L15 _variable_ `const FLazyName InputOAuth(TEXT("Inpu` (scope `UE::DataLinkOAuth`)

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthDefaultSettings.h` (Public)


#### class `UDataLinkOAuthDefaultSettings`  
`class UDataLinkOAuthDefaultSettings : public UDataLinkOAuthSettings`  
_L9-31_
- reflection: `UCLASS(MinimalAPI, DisplayName="OAuth Default Settings")`
- inherits: `UDataLinkOAuthSettings`
- L14 _public prototype_ `UDataLinkOAuthDefaultSettings();`
- L17 _public prototype_ `virtual bool BuildAuthRequestUrl(FUrlBuilder& OutRequestUrl, FDataLinkNodeOAuthInstance& InOAuthInstance) const override;`
- L18 _public prototype_ `virtual bool ValidateRequest(const FHttpServerRequest& InRequest, FDataLinkNodeOAuthInstance& InOAuthInstance) const override;`
- L19 _public prototype_ `virtual bool BuildExchangeCodeTokenUrl(FUrlBuilder& OutRequestUrl, FDataLinkNodeOAuthInstance& InOAuthInstance, FStringView InAuthCode) const override;`
- L24 _private member_ `FString AuthorizationURL;` — `UPROPERTY(EditAnywhere, Category="OAuth")`
- L27 _private member_ `FString TokenExchangeEndpoint;` — `UPROPERTY(EditAnywhere, Category="OAuth")`
- L30 _private member_ `TArray<FString> Scopes;` — `UPROPERTY(EditAnywhere, Category="OAuth")`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthDefaultSharedData.h` (Public)


#### struct `FDataLinkOAuthDefaultSharedData`  
`struct FDataLinkOAuthDefaultSharedData`  
_L9-17_
- reflection: `USTRUCT()`
- L13 _public prototype_ `FDataLinkOAuthDefaultSharedData();`
- L16 _public member_ `FString State;` — `UPROPERTY(meta=(IgnoreForMemberInitializationTest))`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthHandle.h` (Public)


#### class `FDataLinkOAuthHandle`  
`class FDataLinkOAuthHandle`  
_L8-33_
- L11 _public prototype_ `FDataLinkOAuthHandle() = default;`
- L13 _public prototype_ `static FDataLinkOAuthHandle GenerateHandle();`
- L16 _public prototype_ `bool IsValid() const;` — Whether this handle was ever initialized
- L19 _public prototype_ `void Reset();` — Clear handle to indicate it is no longer used
- L21 _public function_ `bool operator==(const FDataLinkOAuthHandle& InOther) const`
- L32 _private member_ `uint64 Id = 0;`

#### Free symbols / members of external scopes

- L26 _function_ `friend uint32 GetTypeHash(const FDataLinkOAuthHandle& InHandle)`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthInstance.h` (Public)


#### struct `FDataLinkNodeOAuthInstance`  
`struct FDataLinkNodeOAuthInstance`  
_L10-25_
- reflection: `USTRUCT()`
- L14 _public prototype_ `~FDataLinkNodeOAuthInstance();`
- L16 _public prototype_ `void StopListening();`
- L18 _public member_ `FDataLinkOAuthHandle ListenHandle;`
- L21 _public member_ `int32 ListenPort = 0;` — `UPROPERTY()`
- L24 _public member_ `FInstancedStruct SharedData;` — `UPROPERTY()`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthSettings.h` (Public)


#### class `UDataLinkOAuthSettings`  
`class UDataLinkOAuthSettings : public UObject`  
_L16-100_
- reflection: `UCLASS(MinimalAPI, Abstract, DisplayName="Motion Design Data Link OAuth Settings")`
- inherits: `UObject`
- L21 _public typedef_ `using FUrlBuilder = TStringBuilder<512>;`
- L27 _public prototype_ `FInstancedStruct MakeSharedData() const;` — Instantiated data of type that matches the 'SharedDataType'. This is data that will live throughout the OAuth process and used by stages to read from/write to
- L35 _public function_ `virtual bool BuildAuthRequestUrl(FUrlBuilder& OutRequestUrl, FDataLinkNodeOAuthInstance& InOAuthInstance) const` — Builds an Authorization URL @param OutRequestUrl the resulting request URL @param InOAuthInstance oauth instance data allowing different stages of OAuth to read from/write to @return true if the request URL was successfully created
- L46 _public function_ `virtual bool ValidateRequest(const FHttpServerRequest& InRequest, FDataLinkNodeOAuthInstance& InOAuthInstance) const` — Validates that the request relates to our OAuth flow @param InRequest the request containing data to validate against @param InOAuthInstance oauth instance data containing data to use for validation @return true if request is valid. False if it's a request to ignore
- L58 _public prototype_ `virtual bool FindAuthCode(const FHttpServerRequest& InRequest, FDataLinkNodeOAuthInstance& InOAuthInstance, FStringView& OutAuthCodeView) const;` — Attempts to find the Auth Code within the given Request @param InRequest the request potentially containing the authorization code to retrieve @param InOAuthInstance oauth instance data allowing different stages of OAuth to read from/write to @param OutAuthCodeView the auth code string view if it was found @return true if the Auth Code was found
- L67 _public function_ `virtual bool BuildExchangeCodeTokenUrl(FUrlBuilder& OutRequestUrl, FDataLinkNodeOAuthInstance& InOAuthInstance, FStringView InAuthCode) const` — Builds an Exchange Code for Access Token URL @param OutRequestUrl the resulting request url @param InOAuthInstance oauth instance data allowing different stages of OAuth to read from/write to @param InAuthCode the authorization code to exchange @return true if the Request URL was successfully created
- L78 _public prototype_ `virtual bool BuildAuthToken(FStringView InAccessResponse, FDataLinkOAuthToken& OutAuthToken) const;` — Builds an Auth Token based on the Access Response String @param InAccessResponse the access response @param OutAuthToken the auth token to build @return true if the token was built
- L86 _public prototype_ `virtual bool AuthorizeHttpRequest(const FDataLinkOAuthToken& InAuthToken, FDataLinkHttpSettings& InOutHttpSettings) const;` — Adds Authorization header to the given Http Settings if the Access Response is valid @param InAuthToken the auth token containing the authorization parameters @param InOutHttpSettings the http settings to add authorization to @return true if the authorization was added
- L89 _protected member_ `static constexpr const TCHAR* LoopbackAddress = TEXT("htt` — 127.0.0.1");
- L93 _protected member_ `TObjectPtr<const UScriptStruct> SharedDataType;` — `UPROPERTY()` — Optional shared data type to use across the different stages of OAuth
- L96 _protected member_ `FString ClientId;` — `UPROPERTY(EditAnywhere, Category="Client")`
- L99 _protected member_ `FString ClientSecret;` — `UPROPERTY(EditAnywhere, Category="Client")`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthSubsystem.h` (Public)


#### class `UDataLinkOAuthSubsystem`  
`class UDataLinkOAuthSubsystem : public UEngineSubsystem`  
_L16-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- L21 _public prototype_ `static UDataLinkOAuthSubsystem* Get();`
- L28 _public prototype_ `FDataLinkOAuthHandle RegisterListenInstance(FListenInstance&& InInstance);`
- L30 _public prototype_ `void UnregisterListenInstance(FDataLinkOAuthHandle InHandle);`
- L32 _public prototype_ `const FDataLinkOAuthToken* FindToken(const UDataLinkOAuthSettings* InOAuthSettings) const;`
- L34 _public prototype_ `void RegisterToken(const UDataLinkOAuthSettings* InOAuthSettings, const FDataLinkOAuthToken& InToken);`
- L36 _public prototype_ `void CleanExpiredTokens();`
- L39 _private member_ `TMap<FDataLinkOAuthHandle, FListenInstance> ListeningInstances;`
- L42 _private member_ `TMap<FDataLinkOAuthTokenHandle, FDataLinkOAuthToken> Tokens;` — `UPROPERTY()`

#### struct `UDataLinkOAuthSubsystem::FListenInstance`  
`struct FListenInstance`  
_L23-27_
- L25 _public member_ `TWeakPtr<IHttpRouter> RouterWeak;`
- L26 _public member_ `FDelegateHandle RequestPreprocessorHandle;`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthToken.h` (Public)


#### struct `FDataLinkOAuthToken`  
`struct FDataLinkOAuthToken`  
_L10-25_
- reflection: `USTRUCT()`
- L15 _public member_ `FString TokenType;` — `UPROPERTY()`
- L18 _public member_ `FString AccessToken;` — `UPROPERTY()`
- L21 _public member_ `FString RefreshToken;` — `UPROPERTY()`
- L24 _public member_ `FDateTime ExpirationDate;` — `UPROPERTY()`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthTokenHandle.h` (Public)


#### struct `FDataLinkOAuthTokenHandle`  
`struct FDataLinkOAuthTokenHandle`  
_L10-33_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FDataLinkOAuthTokenHandle() = default;`
- L16 _public prototype_ `explicit FDataLinkOAuthTokenHandle(const UDataLinkOAuthSettings* InOAuthSettings);`
- L18 _public prototype_ `bool operator==(const FDataLinkOAuthTokenHandle& InOther) const;`
- L26 _private prototype_ `void RecalculateHash();`
- L29 _private member_ `uint32 CachedHash = 0;` — `UPROPERTY()`
- L32 _private member_ `TObjectPtr<const UDataLinkOAuthSettings> OAuthSettings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L20 _function_ `friend uint32 GetTypeHash(const FDataLinkOAuthTokenHandle& InHandle)`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuth/Public/DataLinkOAuthUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DataLinkOAuth` (scope `UE`)
- L12 _prototype_ `TSharedPtr<FJsonObject> ResponseStringToJsonObject(FStringView InResponseString);` (scope `UE::DataLinkOAuth`)
