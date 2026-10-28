# Plugins / InterchangeAnalytics

- module root: `Plugins/Interchange/Runtime/Source/Analytics`
- headers: 3; symbols: 22
- symbol kinds: class=3, function=2, macro=2, member=4, prototype=11
- PrivateDependencyModuleNames: GeometryCache, HairStrandsCore, LevelSequence
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCommon, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes

### `Plugins/Interchange/Runtime/Source/Analytics/Public/InterchangeAnalyticsAssetTypeTracker.h` (Public)


#### class `FInterchangeAnalyticsAssetTypeTracker`  
`class FInterchangeAnalyticsAssetTypeTracker`  
_L14-26_
- L17 _public prototype_ `static void RegisterAssetType(UClass* AssetClass, const FString& DisplayName);`
- L19 _public prototype_ `static TMap<FString, int32> GetAssetTypeFrequenceMap(const TArray<TObjectPtr<UObject>>& InObjects, bool bIncludeUntrackedClasses = false);`
- L21 _public prototype_ `static void AppendAssetTypeFrequenceMap(const TArray<TObjectPtr<UObject>>& InObjects, TMap<FString, int32>& OutFreqMap, bool bIncludeUntrackedClasses = false);`
- L24 _private member_ `static TSet<UClass*> RegisteredAssetClasses;`
- L25 _private member_ `static TMap<UClass*, FString> AssetClassPathToDisplayNameMap;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEANALYTICS_API`

### `Plugins/Interchange/Runtime/Source/Analytics/Public/InterchangeAnalyticsHandlerDefault.h` (Public)


#### class `UInterchangeAnalyticsHandlerDefault`  
`class UInterchangeAnalyticsHandlerDefault : public UInterchangeAnalyticsHandlerBase`  
_L22-49_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `UInterchangeAnalyticsHandlerBase`
- L27 _public prototype_ `virtual void Send(const TArray<UInterchangePipelineBase*>& Pipelines, const int32 AsyncHelperUniqueId) override;`
- L29 _public prototype_ `virtual void Send(const FInterchangeImportResultAnalyticsInfo& ImportResultAnalyticsInfo) override;`
- L32 _protected prototype_ `void SendImmediate(const FString& Identifier, TArray<FAnalyticsEventAttribute> Attributes) const;`
- L34 _protected prototype_ `virtual void Execute_Append(const FString& Identifier, const TArray<FAnalyticsEventAttribute>& ToAdd) override;`
- L36 _protected prototype_ `virtual void Execute_Add(const FString& Identifier, const FAnalyticsEventAttribute& Entry) override;`
- L38 _protected prototype_ `virtual void Execute_Clear(const FString& Identifier) override;`
- L40 _protected prototype_ `virtual void Execute_Flush() override;`
- L43 _private prototype_ `void SendPipelineAnalytics(UInterchangePipelineBase& Pipeline, const int32 AsyncHelperUniqueId, const FString& ParentPipeline) const;`
- L47 _protected member_ `TMap<FString, TArray<FAnalyticsEventAttribute>> AnalyticsAttributes;` — Analytics Attributes to share with the Translators. (to be sent when Import is finished)
- L48 _protected member_ `FCriticalSection CriticalSection;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API INTERCHANGEANALYTICS_API`

### `Plugins/Interchange/Runtime/Source/Analytics/Public/InterchangeAnalyticsModule.h` (Public)


#### class `IInterchangeAnalyticsModule`  
`class IInterchangeAnalyticsModule : public IModuleInterface`  
_L11-34_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L20 _public function_ `static inline IInterchangeAnalyticsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L30 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
