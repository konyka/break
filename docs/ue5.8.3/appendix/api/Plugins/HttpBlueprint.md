# Plugins / HttpBlueprint

- module root: `Plugins/Web/HttpBlueprint/Source/HttpBlueprint`
- headers: 4; symbols: 37
- symbol kinds: class=2, delegate=1, enum=2, enumerator=10, function=2, member=3, prototype=16, struct=1
- PrivateDependencyModuleNames: HTTP, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprint/Internal/HttpRequestProxyObject.h` (Internal)


#### class `UHttpRequestProxyObject`  
`class UHttpRequestProxyObject : public UObject`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L19 _public member_ `FOnRequestComplete OnRequestComplete;` — `UPROPERTY(BlueprintAssignable)`
- L22 _public prototype_ `static UHttpRequestProxyObject* CreateHttpRequestProxyObject( const FString& InUrl, const FString& InVerb, FHttpHeader InHeader, const FString& InBody);` — `UFUNCTION(BlueprintCallable, Meta = (BlueprintInternalUseOnly, DisplayName = "Http Request"), Category = "Http")`
- L29 _protected prototype_ `void ProcessRequest(const FString& InUrl, const FString& InVerb, FHttpHeader&& InHeader, const FString& InBody);`
- L30 _protected prototype_ `void ProcessComplete(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bInSuccessful);`
- L34 _private member_ `FHttpHeader CachedHeader;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRequestComplete, FString, Response, bool, bSuccessful, FHttpHeader, OutHeader);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRequestComplete, FString, Response, bool, bSuccessful, FHttpHeader, OutHeader);`

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprint/Public/HttpBlueprintFunctionLibrary.h` (Public)


#### class `UHttpBlueprintFunctionLibrary`  
`class UHttpBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L12-58_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L29 _public prototype_ `static UPARAM(DisplayName="Success") bool GetHeaderValue(const FHttpHeader& HeaderObject, FString HeaderName, FString& OutHeader` — `UFUNCTION(BlueprintPure, Category = "Http")` — Get the value associated with a Header name @Param HeaderObject: The structure that contains all of the headers @Param HeaderName: The name of the Header @Param OutHeaderValue: The value of the Header. Empty if the Header could not be found @Return Whether the operation was successful
- L33 _public prototype_ `static UPARAM(DisplayName="Headers") TArray<FString> GetAllHeaders(const FHttpHeader& HeaderO` — `UFUNCTION(BlueprintPure, Category = "Http")` — Returns all of the headers and their values by value
- L37 _public prototype_ `static UPARAM(DisplayName="Headers") TMap<FString, FString> GetAllHeaders_Map(const FHttpHeader& HeaderO` — `UFUNCTION(BlueprintPure, Category = "Http", meta = (DisplayName = "GetAllHeadersAsMap"))` — Returns all of the headers and their values as a map by value
- L47 _public prototype_ `static void AddHeader(UPARAM(Ref) FHttpHeader& HeaderObject, FString NewHeader, FString NewHeaderValue);` — `UFUNCTION(BlueprintCallable, Category = "Http")` — Adds a new Header @Param HeaderObject: The structure that contains all of the headers @Param NewHeader: The name of the header @Param NewHeaderValue: The value of the new header
- L57 _public prototype_ `static bool RemoveHeader(UPARAM(Ref) FHttpHeader& HeaderObject, FString HeaderToRemove);` — `UFUNCTION(BlueprintCallable, Category = "Http")` — Removes a header from the HeaderObject @Param HeaderObject: The structure that contains all of the headers @Param HeaderToRemove: The Key of the header to remove @Return Whether or not the operation was successful. A value of false most likely means the Key did not exist on the HeaderObject

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprint/Public/HttpBlueprintTypes.h` (Public)


#### enum `EHttpVerbs`  
`enum class EHttpVerbs : uint8`  
_L10-20_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Post = 0`
- L13 _public enumerator_ `Put = 1`
- L14 _public enumerator_ `Delete = 2`
- L15 _public enumerator_ `Patch = 3`
- L17 _public enumerator_ `Get = 4` — @note: Anything past Patch will not display the input body pin
- L19 _public enumerator_ `MAX = 255 UMETA(Hidden)`

#### enum `ERequestPresets`  
`enum class ERequestPresets : uint8`  
_L25-32_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Json UMETA(DisplayName = "Json Request")` — The order here matters.
- L29 _public enumerator_ `Http UMETA(DisplayName = "Http Request")`
- L30 _public enumerator_ `Url UMETA(DisplayName = "Url Encoded Request")`
- L31 _public enumerator_ `Custom UMETA(DisplayName = "Custom Request")`

#### Free symbols / members of external scopes

- L22 _prototype_ `ENUM_CLASS_FLAGS(EHttpVerbs);`

### `Plugins/Web/HttpBlueprint/Source/HttpBlueprint/Public/HttpHeader.h` (Public)


#### struct `FHttpHeader`  
`struct FHttpHeader`  
_L13-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: Provides a way for blueprint to create and store a map of HTTP headers
- L21 _public prototype_ `[[nodiscard]] FHttpHeader SetHeaders(const TMap<FString, FString>& NewHeaders);` — Sets the internal headers. Will overwrite any headers already in the map
- L26 _public prototype_ `[[nodiscard]] FString GetHeader(FString&& Key) const;` — Returns the header value associated with the Key
- L31 _public prototype_ `void AddHeader(TPair<FString, FString>&& NewHeader);` — Adds a new header key/value pair to the internal header map
- L36 _public prototype_ `[[nodiscard]] bool RemoveHeader(FString&& HeaderToRemove);` — Removes a header from the internal header map
- L41 _public prototype_ `[[nodiscard]] TArray<FString> GetAllHeaders() const;` — Returns the internal header map as an array
- L46 _public function_ `[[nodiscard]] const TMap<FString, FString>& GetAllHeadersAsMap() const` — Returns a copy of the internal header map
- L54 _public function_ `[[nodiscard]] bool IsValid() const` — Returns if the header is valid or not. This is done by checking the map size
- L62 _public prototype_ `void AssignHeadersToRequest(const TSharedRef<class IHttpRequest>& Request);` — Convenience function to set all of the headers in the internal header map on the request object.
- L67 _private member_ `TMap<FString, FString> Headers;` — `UPROPERTY()` — Header key/value pairs.
