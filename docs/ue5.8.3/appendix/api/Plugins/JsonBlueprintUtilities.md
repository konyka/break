# Plugins / JsonBlueprintUtilities

- module root: `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintUtilities`
- headers: 2; symbols: 14
- symbol kinds: class=1, delegate=1, prototype=12
- PrivateDependencyModuleNames: Json, JsonUtilities
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintUtilities/Private/JsonBlueprintLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogJsonBlueprintUtilities, VeryVerbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogJsonBlueprintUtilities, VeryVerbose, All);`

### `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintUtilities/Public/JsonBlueprintFunctionLibrary.h` (Public)


#### class `UJsonBlueprintFunctionLibrary`  
`class UJsonBlueprintFunctionLibrary final : public UBlueprintFunctionLibrary`  
_L13-62_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static UPARAM(DisplayName="Success") bool FromString(const FString& JsonString, UPARAM(DisplayName="JsonObject") FJsonObjectWrapper` — `UFUNCTION(BlueprintCallable, Category="Json", meta = (DisplayName="Load Json from String"))` — Creates a JsonObject from the provided Json string.
- L24 _public prototype_ `static UPARAM(DisplayName="Success") bool FromFile(const FFilePath& File, UPARAM(DisplayName="JsonObject") FJsonObjectWrapper` — `UFUNCTION(BlueprintCallable, Category="Json", meta = (DisplayName="Load Json from File"))` — Creates a JsonObject from the provided Json file.
- L28 _public prototype_ `static UPARAM(DisplayName="Success") bool ToString(const FJsonObjectWrapper& JsonObject, UPARAM(DisplayName="String") FString& Ou` — `UFUNCTION(BlueprintCallable, Category="Json", meta = (DisplayName = "Get Json String"))` — Creates a Json string from the provided JsonObject.
- L32 _public prototype_ `static UPARAM(DisplayName="Success") bool ToFile(const FJsonObjectWrapper& JsonObject, const FFilePath&` — `UFUNCTION(BlueprintCallable, Category="Json", meta = (DisplayName = "Save Json to File"))` — Creates a file from the provided JsonObject.
- L36 _public prototype_ `static UPARAM(DisplayName="Success") bool GetField(const FJsonObjectWrapper& JsonObject, const FString& FieldName, UPARAM(DisplayName="Value") int32` — `UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, Category="Json", meta = (CustomStructureParam = "OutValue", AutoCreateRefTerm = "OutValue"))` — Gets the value of the specified field.
- L41 _public prototype_ `static UPARAM(DisplayName="Success") bool SetField(const FJsonObjectWrapper& JsonObject, const FString& FieldName, const int32&` — `UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, Category="Json", meta = (CustomStructureParam = "Value", AutoCreateRefTerm = "Value"))` — Adds (new) or sets (existing) the value of the specified field.
- L45 _public prototype_ `static UPARAM(DisplayName="Success") bool StructToJsonString(const int32& Struct, FString& OutJsonS` — `UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, Category="Json", meta = (DisplayName = "Convert Struct To Json String", CustomStructureParam = "Struct", AutoCreateRefTerm = "Struct"))`
- L50 _public prototype_ `static UPARAM(DisplayName="Success") bool HasField(const FJsonObjectWrapper& JsonObject, const FString& Fiel` — `UFUNCTION(BlueprintCallable, Category="Json")` — Checks if the field exists on the object.
- L54 _public prototype_ `static UPARAM(DisplayName="Success") bool GetFieldNames(const FJsonObjectWrapper& JsonObject, TArray<FString>& Field` — `UFUNCTION(BlueprintCallable, Category="Json")` — Gets all field names on the JsonObject
- L58 _private prototype_ `static bool JsonFieldToProperty(const FString& FieldName, const FJsonObjectWrapper& SourceObject, FProperty* TargetProperty, void* TargetValuePtr);` — FieldName only used for logging, SrcValue should be the resolved field.
- L61 _private prototype_ `static bool PropertyToJsonField(const FString& FieldName, FProperty* SourceProperty, const void* SourceValuePtr, FJsonObjectWrapper& TargetObject);` — If FieldName empty, Object created as root, or created with name "Value" otherwise.
