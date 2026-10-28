# Plugins / GlobalConfigurationData

- module root: `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationData`
- headers: 1; symbols: 13
- symbol kinds: class=1, prototype=12
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject, GlobalConfigurationDataCore

### `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationData/Public/GlobalConfigurationDataBlueprintLibrary.h` (Public)


#### class `UGlobalConfigurationDataBlueprintLibrary`  
`class UGlobalConfigurationDataBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L11-51_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public prototype_ `static bool GetConfigDataBool(const FString& EntryName, bool &bValueOut);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L20 _public prototype_ `static bool GetConfigDataInt(const FString& EntryName, int32& ValueOut);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L23 _public prototype_ `static bool GetConfigDataFloat(const FString& EntryName, float& ValueOut);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L26 _public prototype_ `static bool GetConfigDataString(const FString& EntryName, FString& ValueOut);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L29 _public prototype_ `static bool GetConfigDataText(const FString& EntryName, FText& ValueOut);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L32 _public prototype_ `static bool GetConfigDataStruct(const FString& EntryName, UScriptStruct* StructType, FInstancedStruct& ValueOut);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L35 _public prototype_ `static bool GetConfigDataObject(const FString& EntryName, UObject* ValueInOut);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L38 _public prototype_ `static bool GetConfigDataBoolWithDefault(const FString& EntryName, bool bDefaultValue);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L41 _public prototype_ `static int32 GetConfigDataIntWithDefault(const FString& EntryName, int32 DefaultValue);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L44 _public prototype_ `static float GetConfigDataFloatWithDefault(const FString& EntryName, float DefaultValue);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L47 _public prototype_ `static FString GetConfigDataStringWithDefault(const FString& EntryName, FString DefaultValue);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
- L50 _public prototype_ `static FText GetConfigDataTextWithDefault(const FString& EntryName, FText DefaultValue);` — `UFUNCTION(BlueprintPure, Category="Global Configuration Data")`
