# Plugins / RPCBase

- module root: `Plugins/RPCBase/Source/RPCBase`
- headers: 2; symbols: 15
- symbol kinds: class=2, member=2, prototype=11
- PublicDependencyModuleNames: ExternalRpcRegistry, HTTPServer

### `Plugins/RPCBase/Source/RPCBase/Public/RPCBaseModule.h` (Public)


#### class `FRPCBaseModule`  
`class FRPCBaseModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/RPCBase/Source/RPCBase/Public/RPCLibraryBase.h` (Public)


#### class `URPCLibraryBase`  
`class URPCLibraryBase : public UObject`  
_L27-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L32 _private member_ `UExternalRpcRegistrationComponent* Registrator;`
- L35 _public prototype_ `URPCLibraryBase();`
- L36 _public prototype_ `~URPCLibraryBase();`
- L38 _protected prototype_ `void Initialize();`
- L39 _protected prototype_ `void StartListening();`
- L40 _protected member_ `bool RegistrationFinished = false;`
- L42 _protected prototype_ `void RegisterRPC(FName RouteName, const FHttpPath& HttpPath, const EHttpServerRequestVerbs& RequestVerb, const FHttpRequestHandler& Handler, bool bOverrideIfBound = false, FString OptionalCategory = {}, FString OptionalContentType = {}, TArray<FExternalRpcArgumentDesc> OptionalInArguments = TArray<FExternalRpcArgumentDesc>());`
- L43 _protected prototype_ `bool HandleRegistrationFinishedRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L44 _protected prototype_ `TUniquePtr<FHttpServerResponse> CreateSimpleResponse(bool bInWasSuccessful, FString InValue = "", bool bInFatal = false);`
- L45 _protected prototype_ `bool DeserializeRequest(TSharedPtr<FJsonObject>& RootObject, const TSharedRef<TJsonReader<>>& JsonReader, const TSharedRef<TJsonWriter<>>& JsonWriter);`
- L46 _protected prototype_ `bool GetStringField(TSharedPtr<FJsonObject>& RootObject, FString FiledName, FString& OutFieldValue, const TSharedRef<TJsonWriter<>>& JsonWriter);`
