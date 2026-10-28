# Plugins / DataLinkHttp

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLinkHttp`
- headers: 4; symbols: 20
- symbol kinds: class=2, member=9, namespace=2, prototype=5, struct=1, variable=1
- PrivateDependencyModuleNames: HTTP
- PublicDependencyModuleNames: Core, CoreUObject, DataLink

### `Plugins/VirtualProduction/DataLink/Source/DataLinkHttp/Public/DataLinkHttpNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DataLinkHttp` (scope `UE`)
- L9 _variable_ `const FLazyName InputHttpSettings(TEXT("Inpu` (scope `UE::DataLinkHttp`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkHttp/Public/DataLinkHttpSettings.h` (Public)


#### struct `FDataLinkHttpSettings`  
`struct FDataLinkHttpSettings`  
_L10-25_
- reflection: `USTRUCT(BlueprintType, DisplayName="Data Link Http Settings")`
- L15 _public member_ `FString URL;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Http")`
- L18 _public member_ `FString Verb = TEXT("GET` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Http")`
- L21 _public member_ `TMap<FString, FString> Headers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Http")`
- L24 _public member_ `FString Body;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Link Http")`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkHttp/Public/DataLinkHttpSource.h` (Public)


#### class `UDataLinkHttpSource`  
`class UDataLinkHttpSource : public UDataLinkNode`  
_L9-18_
- reflection: `UCLASS(MinimalAPI, DisplayName="Http Request", Category="Http")`
- inherits: `UDataLinkNode`
- L15 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L16 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkHttp/Public/DataLinkNodeHttpSettingsBuilder.h` (Public)


#### class `UDataLinkNodeHttpSettingsBuilder`  
`class UDataLinkNodeHttpSettingsBuilder : public UDataLinkNode`  
_L14-47_
- reflection: `UCLASS(MinimalAPI, DisplayName="Http Settings Builder", Category="Http")`
- inherits: `UDataLinkNode`
- desc: Builder Node to help layer Http Settings with a URL Builder Interface
- L20 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L21 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`
- L26 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L33 _private member_ `TArray<FString> URLSegments;` — `UPROPERTY(EditAnywhere, Category="URL", DisplayName="URL Segments", meta=(InvalidatesNode))` — Segments to build the URL from, where a token can be defined as {Token Name} in its own isolated entry
- L37 _private member_ `TArray<FDataLinkStringBuilderToken> Tokens;` — `UPROPERTY()` — The tokens found within the Segment Array
- L40 _private member_ `FString Verb = TEXT("GET` — `UPROPERTY(EditAnywhere, Category="Settings", AdvancedDisplay)`
- L43 _private member_ `TMap<FString, FString> Headers;` — `UPROPERTY(EditAnywhere, Category="Settings", AdvancedDisplay)`
- L46 _private member_ `FString Body;` — `UPROPERTY(EditAnywhere, Category="Settings", AdvancedDisplay)`
