# Plugins / RiderSourceCodeAccess

- module root: `Plugins/Developer/RiderSourceCodeAccess/Source/RiderSourceCodeAccess`
- headers: 4; symbols: 99
- symbol kinds: class=4, enum=4, enumerator=10, function=17, member=18, prototype=44, struct=2
- PrivateDependencyModuleNames: EditorFramework, GameProjectGeneration, UnrealEd

### `Plugins/Developer/RiderSourceCodeAccess/Source/RiderSourceCodeAccess/Private/RiderPathLocator/RiderPathLocator.h` (Private)


#### struct `FVersion`  
`struct FVersion`  
_L8-89_
- L10 _public function_ `bool IsInitialized() const`
- L12 _public function_ `FVersion()`
- L14 _public function_ `explicit FVersion(const FString& VersionString)`
- L19 _public function_ `void operator=(const FString& VersionString)`
- L29 _public function_ `int32 Major() const`
- L38 _public function_ `int32 Minor() const`
- L47 _public function_ `int32 Patch() const`
- L56 _public function_ `bool operator<(const FVersion& rhs) const`
- L71 _public function_ `bool operator==(const FVersion& rhs) const`
- L76 _public function_ `bool operator!=(const FVersion& rhs) const`
- L81 _public function_ `FString ToString() const`
- L87 _public member_ `TArray<int32> Versions;`
- L88 _public member_ `static const int32 INVALID_VERSION = -1;`

#### struct `FInstallInfo`  
`struct FInstallInfo`  
_L91-137_
- L107 _public member_ `FString Path;`
- L108 _public member_ `FVersion Version;`
- L109 _public member_ `ESupportUproject SupportUprojectState = ESupportUproject::None;`
- L110 _public member_ `EInstallType InstallType;`
- L112 _public prototype_ `FInstallInfo() = default;`
- L114 _public function_ `bool operator<(const FInstallInfo& InstallInfo) const`
- L119 _public function_ `bool operator==(const FInstallInfo& InstallInfo) const`

#### enum `FInstallInfo::ESupportUproject`  
`enum class ESupportUproject`  
_L93-98_
- L95 _public enumerator_ `None`
- L96 _public enumerator_ `Beta`
- L97 _public enumerator_ `Release`

#### enum `FInstallInfo::EInstallType`  
`enum class EInstallType`  
_L100-105_
- L102 _public enumerator_ `Installed`
- L103 _public enumerator_ `Toolbox`
- L104 _public enumerator_ `Custom`

#### class `FRiderPathLocator`  
`template <typename OptionalType> struct TOptional;`  
_L140-155_
- L144 _public prototype_ `static TOptional<FInstallInfo> GetInstallInfoFromRiderPath(const FString& Path, FInstallInfo::EInstallType InstallType);` — Platform specific implementation
- L145 _public prototype_ `static bool DirectoryExistsAndNonEmpty(const FString& Path);`
- L146 _public prototype_ `static TSet<FInstallInfo> CollectAllPaths();`
- L148 _private prototype_ `static void ParseProductInfoJson(FInstallInfo& Info, const FString& ProductInfoJsonPath);`
- L149 _private prototype_ `static FString GetDefaultIDEInstallLocationForToolboxV2();`
- L150 _private prototype_ `static TArray<FInstallInfo> GetInstallInfosFromToolbox(const FString& ToolboxPath, const FString& Pattern);`
- L151 _private prototype_ `static TArray<FInstallInfo> GetInstallInfosFromResourceFile();`
- L152 _private prototype_ `static TArray<FInstallInfo> GetInstallInfos(const FString& ToolboxRiderRootPath, const FString& Pattern, FInstallInfo::EInstallType InstallType);`
- L153 _private prototype_ `static FString GetHistoryJsonPath(const FString& RiderPath);`
- L154 _private prototype_ `static FVersion GetLastBuildVersion(const FString& HistoryJsonPath);`

#### Free symbols / members of external scopes

- L83 _function_ `return FString::JoinBy(Versions, TEXT("."), [](int32 Item)-> FString { return FString::FromInt(Item); })` (scope `FVersion::ToString`)
- L130 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FInstallInfo& InstallInfo)`

### `Plugins/Developer/RiderSourceCodeAccess/Source/RiderSourceCodeAccess/Private/RiderSourceCodeAccessor.h` (Private)


#### class `FRiderSourceCodeAccessor`  
`class FRiderSourceCodeAccessor : public ISourceCodeAccessor`  
_L11-75_
- inherits: `ISourceCodeAccessor`
- L15 _public function_ `static FName FeatureType()`
- L29 _public prototype_ `void Init(const FInstallInfo& Info, EProjectModel ProjectModel, EAccessType Type = EAccessType::Direct);`
- L32 _public prototype_ `virtual void RefreshAvailability() override;` — ISourceCodeAccessor implementation
- L33 _public prototype_ `virtual bool CanAccessSourceCode() const override;`
- L34 _public prototype_ `virtual bool DoesSolutionExist() const override;`
- L35 _public prototype_ `virtual FName GetFName() const override;`
- L36 _public prototype_ `virtual FText GetNameText() const override;`
- L37 _public prototype_ `virtual FText GetDescriptionText() const override;`
- L38 _public prototype_ `virtual bool OpenSolution() override;`
- L39 _public prototype_ `virtual bool OpenSolutionAtPath(const FString& InSolutionPath) override;`
- L40 _public prototype_ `virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;`
- L41 _public prototype_ `virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;`
- L42 _public prototype_ `virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;`
- L43 _public prototype_ `virtual bool SaveAllOpenDocuments() const override;`
- L44 _public function_ `virtual void Tick(const float) override`
- L45 _public prototype_ `virtual FName GetOpenIconName() const override;`
- L46 _public prototype_ `virtual FName GetRefreshIconName() const override;`
- L47 _public prototype_ `virtual FName GetStyleSet() const override;`
- L49 _private prototype_ `void CachePathToUproject() const;`
- L50 _private prototype_ `void CachePathToSln() const;`
- L51 _private prototype_ `void CachePathToSolution() const;`
- L52 _private prototype_ `bool TryGenerateSlnFile() const;`
- L53 _private prototype_ `bool HandleOpeningRider(TFunction<bool()> Callback) const;`
- L55 _private prototype_ `bool TryGenerateSolutionFile() const;`
- L56 _private prototype_ `TOptional<FString> GetSolutionPath() const;`
- L58 _private member_ `FName RiderName;`
- L61 _private member_ `bool bHasRiderInstalled = false;` — Is Rider installed on this system?
- L64 _private member_ `FString ExecutablePath;` — The path to the Rider executable.
- L67 _private member_ `mutable FCriticalSection CachedSolutionPathCriticalSection;` — Critical section for updating SolutionPath
- L70 _private member_ `mutable FString CachedSolutionPath = {};` — String storing the solution path obtained from the module manager to avoid having to use it on a thread
- L73 _private member_ `mutable FString CachedSolutionPathOverride = {};` — Override for the cached solution path
- L74 _private member_ `EProjectModel Model = EProjectModel::Sln;`

#### enum `FRiderSourceCodeAccessor::EAccessType`  
`enum class EAccessType`  
_L17-21_
- L19 _public enumerator_ `Direct`
- L20 _public enumerator_ `Aggregate`

#### enum `FRiderSourceCodeAccessor::EProjectModel`  
`enum class EProjectModel`  
_L23-27_
- L25 _public enumerator_ `Sln`
- L26 _public enumerator_ `Uproject`

### `Plugins/Developer/RiderSourceCodeAccess/Source/RiderSourceCodeAccess/Private/RiderSourceCodeAccessorModule.h` (Private)


#### class `FRiderSourceCodeAccessModule`  
`class FRiderSourceCodeAccessModule : public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L13 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L15 _private prototype_ `void GenerateSlnAccessors(const TArray<struct FInstallInfo>& InstallInfos);`
- L16 _private prototype_ `void GenerateUprojectAccessors(const TArray<struct FInstallInfo>& InstallInfos);`
- L17 _private member_ `TMultiMap<FName, TSharedRef<ISourceCodeAccessor>> RiderSourceCodeAccessors;`

### `Plugins/Developer/RiderSourceCodeAccess/Source/RiderSourceCodeAccess/Private/Style/RiderSourceCodeAccessStyleSet.h` (Private)


#### class `FRiderSourceCodeAccessStyleSet`  
`class FRiderSourceCodeAccessStyleSet : public FSlateStyleSet`  
_L7-28_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `static const FRiderSourceCodeAccessStyleSet& Get();`
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public member_ `static FName RiderIconName;`
- L18 _public member_ `static FName RiderRefreshIconName;`
- L19 _public member_ `static FName StyleName;`
- L22 _private prototype_ `FRiderSourceCodeAccessStyleSet();`
- L24 _private prototype_ `virtual const FName& GetStyleSetName() const override;`
- L26 _private member_ `static TUniquePtr<FRiderSourceCodeAccessStyleSet> Inst;`
