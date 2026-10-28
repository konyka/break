# Plugins / DataLinkJson

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLinkJson`
- headers: 8; symbols: 28
- symbol kinds: class=5, delegate=1, function=1, member=3, namespace=4, prototype=9, struct=1, variable=4
- PrivateDependencyModuleNames: Engine, Json, JsonUtilities
- PublicDependencyModuleNames: Core, CoreUObject, DataLink

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkJsonFromStruct.h` (Public)


#### class `UDataLinkJsonFromStruct`  
`class UDataLinkJsonFromStruct : public UDataLinkNode`  
_L10-19_
- reflection: `UCLASS(MinimalAPI, Category="JSON", DisplayName="Struct to JSON")`
- inherits: `UDataLinkNode`
- desc: Convert a struct to Json Object
- L16 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L17 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkJsonLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkJson, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkJson, Log, All);`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkJsonNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DataLinkJson` (scope `UE`)
- L9 _variable_ `const FLazyName InputJsonObject(TEXT("Inpu` (scope `UE::DataLinkJson`)
- L10 _variable_ `const FLazyName InputMappingConfig(TEXT("Inpu` (scope `UE::DataLinkJson`)
- L11 _variable_ `const FLazyName InputString(TEXT("Inpu` (scope `UE::DataLinkJson`)
- L12 _variable_ `const FLazyName InputStruct(TEXT("Inpu` (scope `UE::DataLinkJson`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkJsonStructMapping.h` (Public)


#### class `UDataLinkJsonStructMapping`  
`class UDataLinkJsonStructMapping : public UObject`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Base class for any mapping logic from a json object to a given struct
- L25 _public function_ `virtual bool Apply(const TSharedRef<FJsonObject>& InSourceJson, const FStructView& InTargetStructView) const` — Runs the mapping logic on the given Json object and the target struct view @param InSourceJson the json object to convert @param InTargetStructView the destination struct instance @return true if the mapping succeeded

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkJsonStructSimpleMapping.h` (Public)


#### class `UDataLinkJsonStructSimpleMapping`  
`class UDataLinkJsonStructSimpleMapping : public UDataLinkJsonStructMapping`  
_L9-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataLinkJsonStructMapping`
- L15 _public prototype_ `virtual bool Apply(const TSharedRef<FJsonObject>& InSourceJson, const FStructView& InTargetStructView) const override;`
- L24 _protected member_ `TMap<FString, FName> FieldMappings;` — `UPROPERTY(EditAnywhere, Category="Data Link")` — Map for how a field in the json pairs to a given property name in a struct. Nested json fields can be accessed via a dot delimiter for each path segment.

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkJsonToStruct.h` (Public)


#### struct `FDataLinkJsonStructMappingConfig`  
`struct FDataLinkJsonStructMappingConfig`  
_L11-26_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `TObjectPtr<UScriptStruct> OutputStruct;` — `UPROPERTY(EditAnywhere, Category="Data Link")` — The desired struct to convert the json object to
- L25 _public member_ `TObjectPtr<UDataLinkJsonStructMapping> CustomMapping;` — `UPROPERTY(EditAnywhere, Instanced, Category="Data Link")` — Optional custom mapping to handle converting the Json object to the Output Struct If none is specified, the default mapping method will be used where the Struct property hierarchy should match that of the Json's @see FJsonObjectConverter::JsonObjectToUStruct

#### class `UDataLinkJsonToStruct`  
`class UDataLinkJsonToStruct : public UDataLinkNode`  
_L30-39_
- reflection: `UCLASS(MinimalAPI, Category="JSON", DisplayName="JSON to Struct")`
- inherits: `UDataLinkNode`
- desc: Convert a Json Object to a particular struct
- L36 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L37 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkJsonUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DataLinkJson` (scope `UE`)
- L19 _prototype_ `TSharedPtr<FJsonValue> FindJsonValue(const TSharedRef<FJsonObject>& InJsonObject, const FString& InFieldName);` (scope `UE::DataLinkJson`) — Finds the json value that corresponds to the given field name in the given json object. @param InJsonObject the json object to look into @param InFieldName the field name to match. Can be in the format "A.B[2].C" to return nested values and array elements @return the json value if found

### `Plugins/VirtualProduction/DataLink/Source/DataLinkJson/Public/DataLinkStringToJson.h` (Public)


#### class `UDataLinkStringToJson`  
`class UDataLinkStringToJson : public UDataLinkNode`  
_L10-19_
- reflection: `UCLASS(MinimalAPI, Category="JSON", DisplayName="String to JSON")`
- inherits: `UDataLinkNode`
- desc: Convert a String to a Json Object
- L16 _protected prototype_ `virtual void OnBuildPins(FDataLinkPinBuilder& Inputs, FDataLinkPinBuilder& Outputs) const override;`
- L17 _protected prototype_ `virtual EDataLinkExecutionReply OnExecute(FDataLinkExecutor& InExecutor) const override;`
