# Plugins / MemoryUsageQueries

- module root: `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries`
- headers: 6; symbols: 93
- symbol kinds: class=5, enum=2, enumerator=5, function=2, macro=2, member=11, namespace=3, prototype=61, struct=1, typedef=1
- PrivateDependencyModuleNames: AssetRegistry, Engine, EngineSettings, PakFile
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries/Private/MemoryUsageInfoProviderLLM.h` (Private)


#### class `FMemoryUsageInfoProviderLLM`  
`class FMemoryUsageInfoProviderLLM : public IMemoryUsageInfoProvider`  
_L14-23_
- inherits: `IMemoryUsageInfoProvider`
- L17 _public prototype_ `virtual bool IsProviderAvailable() const override;`
- L18 _public prototype_ `virtual uint64 GetAssetMemoryUsage(FName Asset) const override;`
- L19 _public prototype_ `virtual uint64 GetAssetsMemoryUsage(const TSet<FName>& Assets) const override;`
- L20 _public prototype_ `virtual void GetAllAssetsWithSize(TMap<FName, uint64>& OutAssets) const override;`
- L21 _public prototype_ `virtual uint64 GetAssetsMemoryUsageWithSize(const TSet<FName>& Assets, TMap<FName, uint64>& OutSizes) const override;`
- L22 _public prototype_ `virtual void GetFilteredTagsWithSize(TMap<FName, uint64>& OutTags, ELLMTracker Tracker, ELLMTagSet TagSet, TArray<FLLMTagSetAllocationFilter>& Filters) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEMORYUSAGEQUERIES_API`

### `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries/Private/MemoryUsageQueriesPrivate.h` (Private)


#### class `MemoryUsageQueries::Internal::FMemoryUsageReferenceProcessor`  
`class FMemoryUsageReferenceProcessor : public FSimpleReferenceProcessorBase`  
_L11-39_
- inherits: `FSimpleReferenceProcessorBase`
- L21 _private member_ `TBitArray<> Excluded;`
- L23 _private member_ `TBitArray<> ReachableFull;`
- L24 _private member_ `TBitArray<> ReachableExcluded;`
- L26 _private member_ `TArray<UObject*> RootSetPackages;`
- L28 _private member_ `EMode Mode;`
- L31 _public prototype_ `FMemoryUsageReferenceProcessor();`
- L33 _public prototype_ `void Init(const TArray<FName>& PackageNames);`
- L34 _public prototype_ `TArray<UObject*>& GetRootSet();`
- L35 _public prototype_ `void HandleTokenStreamObjectReference(UE::GC::FWorkerContext& Context, const UObject* ReferencingObject, UObject*& Object, UE::GC::FTokenId TokenIndex, const EGCTokenType TokenType, bool bAllowReferenceElimination);`
- L36 _public prototype_ `void GetUnreachablePackages(TSet<FName>& OutUnreachablePackages);`
- L38 _public function_ `void SetMode(EMode InMode)`

#### enum `MemoryUsageQueries::Internal::FMemoryUsageReferenceProcessor::EMode`  
`enum EMode`  
_L14-18_
- L16 _public enumerator_ `Full`
- L17 _public enumerator_ `Excluding`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace MemoryUsageQueries`
- L8 _namespace_ `namespace Internal` (scope `MemoryUsageQueries`)
- L41 _typedef_ `using FMemoryUsageReferenceCollector = UE::GC::TDefaultCollector<FMemoryUsageReferenceProcessor>;` (scope `MemoryUsageQueries::Internal`)
- L43 _prototype_ `bool GetLongName(FStringView ShortPackageName, FName& OutLongPackageName, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries::Internal`)
- L44 _prototype_ `bool GetLongNames(const TArray<FString>& PackageNames, TSet<FName>& OutLongPackageNames, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries::Internal`)
- L46 _prototype_ `void GetDependenciesCombined(const TArray<FName>& PackageNames, TSet<FName>& OutDependencies);` (scope `MemoryUsageQueries::Internal`)
- L47 _prototype_ `void GetDependenciesShared(const TArray<FName>& PackageNames, TSet<FName>& OutDependencies);` (scope `MemoryUsageQueries::Internal`)
- L50 _prototype_ `void GetRemovablePackages(const TArray<FName>& PackagesToUnload, TSet<FName>& OutRemovablePackages);` (scope `MemoryUsageQueries::Internal`) — Get Packages that would be GC'd if PackagesToUnload were unloaded
- L53 _prototype_ `void GetUnremovablePackages(const TArray<FName>& PackagesToUnload, TSet<FName>& OutUnremovablePackages);` (scope `MemoryUsageQueries::Internal`) — Get Packages that would not be GC'd if PackagesToUnload were unloaded
- L55 _prototype_ `void GetTransitiveDependencies(FName PackageName, TSet<FName>& OutDependencies);` (scope `MemoryUsageQueries::Internal`)
- L57 _prototype_ `void SortPackagesBySize(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TSet<FName>& Packages, TMap<FName, uint64>& OutPackagesWithSize);` (scope `MemoryUsageQueries::Internal`)
- L58 _prototype_ `void GetPackagesSize(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TSet<FName>& Packages, TMap<FName, uint64>& OutPackagesWithSize);` (scope `MemoryUsageQueries::Internal`)
- L60 _prototype_ `void RemoveNonExistentPackages(TMap<FName, uint64>& OutPackagesWithSize);` (scope `MemoryUsageQueries::Internal`)
- L61 _prototype_ `void RemoveFilteredPackages(TMap<FName, uint64>& OutPackagesWithSize, const FString& AssetSubstring);` (scope `MemoryUsageQueries::Internal`)
- L63 _prototype_ `void PrintTagsWithSize(FOutputDevice& Ar, const TMap<FName, uint64>& TagsWithSize, const TCHAR* Name, bool bTruncate = false, int32 Limit = -1, bool bCSV = false);` (scope `MemoryUsageQueries::Internal`)

### `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries/Public/MemoryUsageInfoProvider.h` (Public)


#### class `IMemoryUsageInfoProvider`  
`class IMemoryUsageInfoProvider`  
_L11-28_
- L15 _public prototype_ `virtual uint64 GetAssetMemoryUsage(FName Asset, FOutputDevice* ErrorOutput) const;` — `UE_DEPRECATED(5.6, "Use version that do not accept FOutputDevice, check IsProviderAvailable() and do the logging yourself.")`
- L17 _public prototype_ `virtual uint64 GetAssetsMemoryUsage(const TSet<FName>& Assets, FOutputDevice* ErrorOutput) const;` — `UE_DEPRECATED(5.6, "Use version that do not accept FOutputDevice, check IsProviderAvailable() and do the logging yourself.")`
- L19 _public prototype_ `virtual void GetAllAssetsWithSize(TMap<FName, uint64>& OutAssets, FOutputDevice* ErrorOutput) const;` — `UE_DEPRECATED(5.6, "Use version that do not accept FOutputDevice, check IsProviderAvailable() and do the logging yourself.")`
- L21 _public prototype_ `virtual uint64 GetAssetsMemoryUsageWithSize(const TSet<FName>& Assets, TMap<FName, uint64>& OutSizes, FOutputDevice* ErrorOutput) const;` — `UE_DEPRECATED(5.6, "Use version that do not accept FOutputDevice, check IsProviderAvailable() and do the logging yourself.")`
- L23 _public prototype_ `virtual bool IsProviderAvailable() const = 0;`
- L24 _public prototype_ `virtual uint64 GetAssetMemoryUsage(FName Asset) const = 0;`
- L25 _public prototype_ `virtual uint64 GetAssetsMemoryUsage(const TSet<FName>& Assets) const = 0;`
- L26 _public prototype_ `virtual void GetAllAssetsWithSize(TMap<FName, uint64>& OutAssets) const = 0;`
- L27 _public prototype_ `virtual uint64 GetAssetsMemoryUsageWithSize(const TSet<FName>& Assets, TMap<FName, uint64>& OutSizes) const = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEMORYUSAGEQUERIES_API`

### `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries/Public/MemoryUsageQueries.h` (Public)


#### enum `MemoryUsageQueries::EDependencyType`  
`enum EDependencyType`  
_L15-20_
- L17 _public enumerator_ `EDep_All`
- L18 _public enumerator_ `EDep_Removable`
- L19 _public enumerator_ `EDep_NonRemovable`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace MemoryUsageQueries`
- L21 _prototype_ `IMemoryUsageInfoProvider* GetCurrentMemoryUsageInfoProvider();` (scope `MemoryUsageQueries`)
- L23 _prototype_ `bool GetMemoryUsage(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const FString& PackageName, uint64& OutExclusiveSize, uint64& OutInclusiveSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use FName version instead, resolve user input using GetLongName if needed")`
- L25 _prototype_ `bool GetMemoryUsageCombined(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, uint64& OutTotalSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L27 _prototype_ `bool GetMemoryUsageShared(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, uint64& OutTotalSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L29 _prototype_ `bool GetMemoryUsageUnique(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, uint64& OutUniqueSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L31 _prototype_ `bool GetMemoryUsageCommon(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, uint64& OutCommonSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L34 _prototype_ `bool GetDependenciesWithSize(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const FString& PackageName, TMap<FName, uint64>& OutDependenciesWithSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use FName version instead, resolve user input using GetLongName if needed")`
- L36 _prototype_ `bool GetDependenciesWithSizeCombined(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L38 _prototype_ `bool GetDependenciesWithSizeShared(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L40 _prototype_ `bool GetDependenciesWithSizeUnique(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L42 _prototype_ `bool GetDependenciesWithSizeCommon(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L44 _prototype_ `void GetMemoryUsage(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const FName& PackageName, uint64& OutExclusiveSize, uint64& OutInclusiveSize);` (scope `MemoryUsageQueries`)
- L45 _prototype_ `void GetMemoryUsageCombined(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, uint64& OutTotalSize);` (scope `MemoryUsageQueries`)
- L46 _prototype_ `void GetMemoryUsageShared(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, uint64& OutTotalSize);` (scope `MemoryUsageQueries`)
- L47 _prototype_ `void GetMemoryUsageUnique(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, uint64& OutUniqueSize);` (scope `MemoryUsageQueries`)
- L48 _prototype_ `void GetMemoryUsageCommon(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, uint64& OutCommonSize);` (scope `MemoryUsageQueries`)
- L50 _prototype_ `void GetDependenciesWithSize(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const FName& PackageName, TMap<FName, uint64>& OutDependenciesWithSize);` (scope `MemoryUsageQueries`)
- L51 _prototype_ `void GetDependenciesWithSizeCombined(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize);` (scope `MemoryUsageQueries`)
- L52 _prototype_ `void GetDependenciesWithSizeShared(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize);` (scope `MemoryUsageQueries`)
- L53 _prototype_ `void GetDependenciesWithSizeUnique(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize);` (scope `MemoryUsageQueries`)
- L54 _prototype_ `void GetDependenciesWithSizeCommon(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, TMap<FName, uint64>& OutDependenciesWithSize);` (scope `MemoryUsageQueries`)
- L58 _prototype_ `bool GetFilteredPackagesWithSize(TMap<FName, uint64>& OutPackagesWithSize, FName GroupName = NAME_None, FString AssetSubstring = FString(), FName ClassName = NAME_None, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`)
- L59 _prototype_ `bool GetFilteredPackagesCategorizedWithSize(TMap<FName, uint64>& OutPackagesWithSize, FName GroupName = NAME_None, FString AssetSubstring = FString(), FName ClassName = NAME_None, FName CategoryName = NAME_None, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`)
- L60 _prototype_ `bool GetFilteredClassesWithSize(TMap<FName, uint64>& OutClassesWithSize, FName GroupName = NAME_None, FString AssetName = FString(), FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`)
- L61 _prototype_ `bool GetFilteredGroupsWithSize(TMap<FName, uint64>& OutGroupsWithSize, FString AssetName = FString(), FName ClassName = NAME_None, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`)
- L63 _prototype_ `bool GatherDependenciesForPackages(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FString>& PackageNames, TMap<FName, uint64>& OutInternalDeps, TMap<FName, uint64>& OutExternalDeps, MemoryUsageQueries::EDependencyType DependencyType = MemoryUsageQueries::EDependencyType::EDep_All, FOutputDevice* ErrorOutput = GLog);` (scope `MemoryUsageQueries`) — `UE_DEPRECATED(5.6, "Use TArray<FName> version instead, resolve user input using GetLongNames if needed")`
- L64 _prototype_ `void GatherDependenciesForPackages(const IMemoryUsageInfoProvider* MemoryUsageInfoProvider, const TArray<FName>& PackageNames, TMap<FName, uint64>& OutInternalDeps, TMap<FName, uint64>& OutExternalDeps, MemoryUsageQueries::EDependencyType DependencyType = MemoryUsageQueries::EDependencyType::EDep_All);` (scope `MemoryUsageQueries`)

### `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries/Public/MemoryUsageQueriesConfig.h` (Public)


#### struct `FCollectionInfo`  
`struct FCollectionInfo`  
_L32-56_
- reflection: `USTRUCT()`
- L36 _public function_ `FCollectionInfo() : BudgetMB(0.0f)`
- L43 _public member_ `FString Name;` — `UPROPERTY()` — Name of the collection
- L47 _public member_ `TArray<FString> Includes;` — `UPROPERTY()` — Collection of substrings to include whne matching against asset package paths
- L51 _public member_ `TArray<FString> Excludes;` — `UPROPERTY()` — Paths of asset package paths to exclude from the results
- L55 _public member_ `float BudgetMB;` — `UPROPERTY()` — Budget in MB

#### class `UMemoryUsageQueriesConfig`  
`class UMemoryUsageQueriesConfig : public UObject`  
_L59-69_
- reflection: `UCLASS(config = MemoryUsageQueries)`
- inherits: `UObject`
- L65 _public member_ `TArray<FCollectionInfo> Collections;` — `UPROPERTY(config)`
- L68 _public member_ `TMap<FString, FString> SavingsPresets;` — `UPROPERTY(config)`

### `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries/Public/MemoryUsageQueriesModule.h` (Public)


#### class `FMemoryUsageQueriesModule`  
`class FMemoryUsageQueriesModule : public IModuleInterface`  
_L8-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
