# Plugins / GlobalConfigurationDataCore

- module root: `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationDataCore`
- headers: 5; symbols: 37
- symbol kinds: class=3, delegate=1, function=3, member=4, namespace=2, prototype=24
- PrivateDependencyModuleNames: Json, JsonUtilities
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationDataCore/Private/GlobalConfigurationDataInternal.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGlobalConfigurationData, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGlobalConfigurationData, Log, All);`

### `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationDataCore/Public/GlobalConfigurationData.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace GlobalConfigurationData` (scope `UE`)
- L20 _prototype_ `bool TryGetDataOfType(const FString& EntryName, const UStruct* Type, void* DataOut);` (scope `UE::GlobalConfigurationData`)
- L22 _prototype_ `bool TryGetData(const FString& EntryName, bool& bValueOut);` (scope `UE::GlobalConfigurationData`)
- L23 _prototype_ `bool TryGetData(const FString& EntryName, int32& ValueOut);` (scope `UE::GlobalConfigurationData`)
- L24 _prototype_ `bool TryGetData(const FString& EntryName, float& ValueOut);` (scope `UE::GlobalConfigurationData`)
- L25 _prototype_ `bool TryGetData(const FString& EntryName, FString& ValueOut);` (scope `UE::GlobalConfigurationData`)
- L26 _prototype_ `bool TryGetData(const FString& EntryName, FText& ValueOut);` (scope `UE::GlobalConfigurationData`)
- L29 _function_ `template<typename Type UE_REQUIRES(TModels_V<CStaticStructProvider, Type>)> bool TryGetData(const FString& EntryName, Type& DataOut)` (scope `UE::GlobalConfigurationData`)
- L35 _function_ `template<typename Type UE_REQUIRES(std::is_base_of_v<UObject, Type>)> bool TryGetData(const FString& EntryName, Type* DataOut)` (scope `UE::GlobalConfigurationData`)
- L41 _function_ `template <typename Type> Type GetDataWithDefault(const FString& EntryName, const Type& DefaultValue)` (scope `UE::GlobalConfigurationData`)

### `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationDataCore/Public/GlobalConfigurationRouter.h` (Public)


#### class `IGlobalConfigurationRouter`  
`class IGlobalConfigurationRouter`  
_L17-50_
- desc: The Router is a class that is used to lookup data from various systems in an order determined by their priority Data should be stored as string values. For primitive types it will use console variable parsing rules. For complex types the data should be stored in a Json format. Routers auto register themselves, so just make sure they exist somewhere and that's it.
- L20 _public prototype_ `IGlobalConfigurationRouter(FString&& InRouterName, int32 InPriority);`
- L21 _public prototype_ `virtual ~IGlobalConfigurationRouter();`
- L23 _public prototype_ `static TSharedPtr<FJsonValue> TryGetData(const FString& EntryName);`
- L26 _public prototype_ `static void GetAllRegisteredData(TMap<FString, TMap<FString, TSharedRef<FJsonValue>>>& DataOut);` — Map of Entry Name to a map of Value by Router Name
- L28 _public prototype_ `static TSharedPtr<FJsonValue> TryParseString(const FStringView& String);`
- L29 _public prototype_ `static FString TryPrintString(TSharedPtr<FJsonValue> Value);`
- L33 _protected prototype_ `static bool GetAllowFlattenJsonObject();` — If enabled allow routers to flatten json objects to a single value. The core system will allow field name references to accept single value returns.
- L35 _protected prototype_ `virtual TSharedPtr<FJsonValue> TryGetDataFromRouter(const FString& EntryName) const = 0;`
- L36 _protected prototype_ `virtual void GetAllDataFromRouter(TMap<FString, TSharedRef<FJsonValue>>& DataOut) const = 0;`
- L39 _private member_ `FString RouterName;`
- L49 _private member_ `int32 Priority;` — Arbitrary value used for sorting. The built-in routers are at the extreme ends of this range, Console Command router being the highest priority (INT32_MAX) Config Router being the lowest priority (INT32_MIN) The idea is that a config value is baseline and baked into the product where the console command is used for testing or hotfixing values at the very highest. User routers should fall in between these two extremes and manage their own priority levels to get the desired outcome.

### `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationDataCore/Public/Routers/GlobalConfigurationConfigRouter.h` (Public)


#### class `FGlobalConfigurationConfigRouter`  
`class FGlobalConfigurationConfigRouter : public IGlobalConfigurationRouter`  
_L9-23_
- inherits: `IGlobalConfigurationRouter`
- desc: Data Router that pulls from the section GlobalConfigurationData in GEngineIni
- L12 _public prototype_ `FGlobalConfigurationConfigRouter(FString&& InConfigSection, FString&& InRouterName, int32 InPriority);`
- L13 _public prototype_ `~FGlobalConfigurationConfigRouter();`
- L15 _public prototype_ `virtual TSharedPtr<FJsonValue> TryGetDataFromRouter(const FString& EntryName) const override;`
- L16 _public prototype_ `virtual void GetAllDataFromRouter(TMap<FString, TSharedRef<FJsonValue>>& DataOut) const override;`
- L19 _private prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);`
- L21 _private member_ `FString ConfigSection;`
- L22 _private member_ `TMap<FString, TSharedRef<FJsonValue>> StoredData;`

### `Plugins/Experimental/GlobalConfigurationData/Source/GlobalConfigurationDataCore/Public/Routers/GlobalConfigurationConsoleCommandRouter.h` (Public)


#### class `FGlobalConfigurationConsoleCommandRouter`  
`class FGlobalConfigurationConsoleCommandRouter : public IGlobalConfigurationRouter`  
_L11-18_
- inherits: `IGlobalConfigurationRouter`
- desc: Data router that uses console commands to register data with the system: GCD.RegisterValue Name "Value" GCD.UnregisterValue Name
- L14 _public prototype_ `FGlobalConfigurationConsoleCommandRouter();`
- L16 _public prototype_ `virtual TSharedPtr<FJsonValue> TryGetDataFromRouter(const FString& EntryName) const override;`
- L17 _public prototype_ `virtual void GetAllDataFromRouter(TMap<FString, TSharedRef<FJsonValue>>& DataOut) const override;`
