# Plugins / CommonLaunchExtensions

- module root: `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions`
- headers: 14; symbols: 344
- symbol kinds: class=27, delegate=2, enum=3, enumerator=11, function=10, macro=3, member=88, namespace=1, prototype=193, struct=4, typedef=2

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/AdvancedCook/AdvancedCookLaunchExtension.h` (Private)


#### class `FAdvancedCookLaunchExtensionInstance`  
`class FAdvancedCookLaunchExtensionInstance : public ProjectLauncher::FBuildCookRunCommandExtensionInstance`  
_L13-83_
- inherits: `ProjectLauncher::FBuildCookRunCommandExtensionInstance`
- L16 _public prototype_ `FAdvancedCookLaunchExtensionInstance( FArgs& InArgs );`
- L17 _public prototype_ `virtual ~FAdvancedCookLaunchExtensionInstance() = default;`
- L19 _public prototype_ `virtual TSharedRef<ProjectLauncher::FBuildCookRunExtension> CreateBuildCookRunExtension( const ProjectLauncher::FBuildCookRunExtension::FArgs& InArgs ) override;`
- L21 _public prototype_ `virtual bool IsBuildCookRunExtensionEnabledByDefault( const ILauncherProfileBuildCookRunRef& InBuildCookRun ) const override;`
- L22 _public prototype_ `virtual bool CanToggleBuildCookRunExtension( const ILauncherProfileBuildCookRunRef& InBuildCookRun, bool bWantToEnable ) const override;`
- L26 _protected member_ `TSharedRef<class FAdvancedCookLaunchExtension> Owner;`

#### class `FAdvancedCookLaunchExtensionInstance::FBuildCookRunInstance`  
`class FBuildCookRunInstance : public ProjectLauncher::FBuildCookRunExtension`  
_L28-82_
- inherits: `ProjectLauncher::FBuildCookRunExtension`
- L31 _public prototype_ `FBuildCookRunInstance(const ProjectLauncher::FBuildCookRunExtension::FArgs& InArgs );`
- L32 _public prototype_ `virtual void CustomizeTree( ProjectLauncher::FLaunchProfileTreeNode& ProfileTreeNode ) override;`
- L35 _public member_ `TArray<FString> CachedMapsToCook;`
- L41 _public member_ `EMapOption MapOption = EMapOption::Startup;`
- L43 _public prototype_ `void SetMapsToCook(TArray<FString> MapsToCook);`
- L44 _public prototype_ `TArray<FString> GetMapsToCook() const;`
- L45 _public prototype_ `EMapOption GetMapOption() const;`
- L46 _public prototype_ `void SetMapOption( EMapOption MapOption );`
- L47 _public prototype_ `float GetMapListHeight() const;`
- L48 _public prototype_ `void SetMapListHeight( float NewHeight );`
- L49 _public prototype_ `TSharedRef<SWidget> CreateMapListWidget();`
- L51 _public member_ `float MapListHeight = 300.0f;`
- L52 _public member_ `TSharedPtr<SCustomLaunchMapListView> MapListView;`
- L55 _public member_ `EMapSourceFlags MapSourceFlags = EMapSourceFlags::None;` — Map filter state
- L56 _public prototype_ `void OnMapFilterChanged(EMapSourceFlags NewFlags);`
- L57 _public prototype_ `void LoadMapFilterState();`
- L58 _public prototype_ `void SaveMapFilterState();`
- L61 _public member_ `TArray<FString> CachedCulturesToCook;`
- L67 _public member_ `ECultureOption CultureOption = ECultureOption::Default;`
- L69 _public prototype_ `void SetCulturesToCook(TArray<FString> CulturesToCook);`
- L70 _public prototype_ `TArray<FString> GetCulturesToCook() const;`
- L71 _public prototype_ `ECultureOption GetCultureOption() const;`
- L72 _public prototype_ `void SetCultureOption( ECultureOption CultureOption );`
- L73 _public prototype_ `float GetCultureListHeight() const;`
- L74 _public prototype_ `void SetCultureListHeight( float NewHeight );`
- L75 _public prototype_ `TSharedRef<SWidget> CreateCultureListWidget();`
- L77 _public member_ `float CultureListHeight = 150.0f;`
- L78 _public member_ `TSharedPtr<SCustomLaunchCultureListView> CultureListView;`
- L81 _public prototype_ `virtual void OnProjectChanged() override;`

#### enum `FAdvancedCookLaunchExtensionInstance::FBuildCookRunInstance::EMapOption`  
`enum class EMapOption : uint8`  
_L36-40_
- L38 _public enumerator_ `Startup`
- L39 _public enumerator_ `Selected`

#### enum `FAdvancedCookLaunchExtensionInstance::FBuildCookRunInstance::ECultureOption`  
`enum class ECultureOption : uint8`  
_L62-66_
- L64 _public enumerator_ `Default`
- L65 _public enumerator_ `Custom`

#### class `FAdvancedCookLaunchExtension`  
`class FAdvancedCookLaunchExtension : public ProjectLauncher::FBuildCookRunCommandExtension`  
_L86-96_
- inherits: `ProjectLauncher::FBuildCookRunCommandExtension`
- L89 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L90 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L91 _public prototype_ `virtual FText GetDisplayName() const override;`
- L92 _public prototype_ `virtual bool IsCreatedByDefault( ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel ) const override;`
- L94 _public prototype_ `bool HasAdvancedCookOptions(const ILauncherProfileBuildCookRunRef& InBuildCookRun) const;`
- L95 _public prototype_ `bool HasAdvancedCookOptions(ILauncherProfileRef InProfile) const;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/BootTest/BootTestLaunchExtension.h` (Private)


#### class `FBootTestLaunchExtensionInstance`  
`class FBootTestLaunchExtensionInstance : public ProjectLauncher::FAutomatedTestLaunchExtensionInstance`  
_L9-23_
- inherits: `ProjectLauncher::FAutomatedTestLaunchExtensionInstance`
- L12 _public function_ `FBootTestLaunchExtensionInstance( FArgs& InArgs ) : ProjectLauncher::FAutomatedTestLaunchExtensionInstance(InArgs)`
- L13 _public prototype_ `virtual ~FBootTestLaunchExtensionInstance() = default;`
- L15 _public prototype_ `virtual void OnTestAdded( ILauncherProfileAutomatedTestRef AutomatedTest ) override;`
- L17 _public prototype_ `virtual void CustomizeTree( ProjectLauncher::FLaunchProfileTreeData& ProfileTreeData ) override;`
- L18 _public prototype_ `virtual void CustomizeUATCommandLine( FString& InOutCommandLine ) override;`
- L21 _private member_ `static const TCHAR* BootTestInternalName;`

#### class `FBootTestLaunchExtension`  
`class FBootTestLaunchExtension : public ProjectLauncher::FAutomatedTestLaunchExtension`  
_L26-32_
- inherits: `ProjectLauncher::FAutomatedTestLaunchExtension`
- L29 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L30 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/DeprecatedProperties/DeprecatedPropertiesLaunchExtension.h` (Private)


#### class `FDeprecatedPropertiesLaunchExtensionInstance`  
`class FDeprecatedPropertiesLaunchExtensionInstance : public ProjectLauncher::FBuildCookRunCommandExtensionInstance`  
_L8-28_
- inherits: `ProjectLauncher::FBuildCookRunCommandExtensionInstance`
- L11 _public prototype_ `FDeprecatedPropertiesLaunchExtensionInstance( FArgs& InArgs );`
- L12 _public prototype_ `virtual ~FDeprecatedPropertiesLaunchExtensionInstance() = default;`
- L14 _public prototype_ `virtual TSharedRef<ProjectLauncher::FBuildCookRunExtension> CreateBuildCookRunExtension( const ProjectLauncher::FBuildCookRunExtension::FArgs& InArgs ) override;`
- L15 _public prototype_ `virtual bool IsBuildCookRunExtensionEnabledByDefault( const ILauncherProfileBuildCookRunRef& InBuildCookRun ) const override;`
- L16 _public prototype_ `virtual bool CanToggleBuildCookRunExtension( const ILauncherProfileBuildCookRunRef& InBuildCookRun, bool bWantToEnable ) const override;`
- L19 _protected member_ `TSharedRef<class FDeprecatedPropertiesLaunchExtension> Owner;`

#### class `FDeprecatedPropertiesLaunchExtensionInstance::FBuildCookRunInstance`  
`class FBuildCookRunInstance : public ProjectLauncher::FBuildCookRunExtension`  
_L20-26_
- inherits: `ProjectLauncher::FBuildCookRunExtension`
- L23 _public prototype_ `FBuildCookRunInstance(const ProjectLauncher::FBuildCookRunExtension::FArgs& InArgs );`
- L24 _public prototype_ `virtual void CustomizeTree( ProjectLauncher::FLaunchProfileTreeNode& ProfileTreeNode ) override;`
- L25 _public member_ `TSharedRef<class FDeprecatedPropertiesLaunchExtension> Owner;`

#### class `FDeprecatedPropertiesLaunchExtension`  
`class FDeprecatedPropertiesLaunchExtension : public ProjectLauncher::FBuildCookRunCommandExtension`  
_L31-43_
- inherits: `ProjectLauncher::FBuildCookRunCommandExtension`
- L34 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L35 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L36 _public prototype_ `virtual FText GetDisplayName() const override;`
- L37 _public prototype_ `virtual bool IsCreatedByDefault( ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel ) const override;`
- L38 _public prototype_ `virtual void GetExtensionsMenuEntry( FExtensionsMenuEntry& MenuEntry ) const override;`
- L39 _public prototype_ `virtual void MakeCustomExtensionSubmenu(FMenuBuilder& MenuBuilder, ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel) override;`
- L41 _public prototype_ `bool HasDeprecatedProperties(const ILauncherProfileBuildCookRunRef& InBuildCookRun, TSharedRef<ProjectLauncher::FModel> InModel) const;`
- L42 _public prototype_ `bool HasDeprecatedProperties(ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel) const;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/Globals/GlobalsLaunchExtension.h` (Private)


#### class `FGlobalsLaunchExtensionInstance`  
`class FGlobalsLaunchExtensionInstance : public ProjectLauncher::FLaunchExtensionInstance`  
_L7-25_
- inherits: `ProjectLauncher::FLaunchExtensionInstance`
- L10 _public function_ `FGlobalsLaunchExtensionInstance( FArgs& InArgs ) : ProjectLauncher::FLaunchExtensionInstance(InArgs)`
- L11 _public prototype_ `virtual ~FGlobalsLaunchExtensionInstance() = default;`
- L13 _public prototype_ `virtual bool GetExtensionVariables( TArray<FString>& OutVariables ) const override;`
- L14 _public prototype_ `virtual bool GetExtensionVariableValue( const FString& InVariable, FString& OutValue ) const override;`
- L18 _private member_ `static const TCHAR* LocalHostVariable;`
- L19 _private member_ `static const TCHAR* LocalHostsVariable;`
- L20 _private member_ `static const TCHAR* ProjectNameVariable;`
- L21 _private member_ `static const TCHAR* ProjectPathVariable;`
- L22 _private member_ `static const TCHAR* TargetNameVariable;`
- L23 _private member_ `static const TCHAR* PlatformNameVariable;`
- L24 _private member_ `static const TCHAR* ConfigurationVariable;`

#### class `FGlobalsLaunchExtension`  
`class FGlobalsLaunchExtension : public ProjectLauncher::FLaunchExtension`  
_L27-34_
- inherits: `ProjectLauncher::FLaunchExtension`
- L30 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L31 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`
- L33 _public function_ `virtual bool IsAlwaysCreated(ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel) const`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/Insights/InsightsLaunchExtension.h` (Private)


#### class `FInsightsLaunchExtensionInstance`  
`class FInsightsLaunchExtensionInstance : public ProjectLauncher::FLaunchExtensionInstance, public ProjectLauncher::ICmdLineParametersExtensionFactory`  
_L9-42_
- inherits: `ProjectLauncher::FLaunchExtensionInstance,ProjectLauncher::ICmdLineParametersExtensionFactory`
- L12 _public function_ `FInsightsLaunchExtensionInstance( FArgs& InArgs ) : FLaunchExtensionInstance(InArgs)`
- L13 _public prototype_ `virtual ~FInsightsLaunchExtensionInstance() = default;`
- L15 _public function_ `virtual class ProjectLauncher::ICmdLineParametersExtensionFactory* AsCmdLineParametersFactory() override`
- L18 _public prototype_ `virtual TSharedRef<ProjectLauncher::FCmdLineParametersExtension> Create( const ProjectLauncher::FCmdLineParametersExtension::FArgs& InArgs ) override;` — ... ICmdLineParametersExtensionFactory
- L19 _public prototype_ `virtual void GetCmdLineParameters( TArray<FString>& OutParameters ) const override;`
- L20 _public prototype_ `virtual FText GetCmdLineParameterDisplayName( const FString& InParameter ) const override;`
- L38 _private member_ `static const TCHAR* FileParam;`
- L39 _private member_ `static const TCHAR* HostParam;`
- L40 _private member_ `static const TCHAR* TraceParam;`
- L41 _private member_ `static const TCHAR* StatNamedEventsParam;`

#### class `FInsightsLaunchExtensionInstance::FInsightsCommandLineExtension`  
`class FInsightsCommandLineExtension : public ProjectLauncher::FCmdLineParametersExtension`  
_L23-36_
- inherits: `ProjectLauncher::FCmdLineParametersExtension`
- L26 _public prototype_ `FInsightsCommandLineExtension( const ProjectLauncher::FCmdLineParametersExtension::FArgs& InArgs );`
- L29 _public prototype_ `virtual void CustomizeParametersSubmenu( FMenuBuilder& MenuBuilder ) override;`
- L31 _public prototype_ `void CacheTraceChannels();`
- L32 _public prototype_ `void ToggleTraceChannel( const FString& InChannel );`
- L33 _public prototype_ `bool IsTraceChannelEnabled( const FString InChannel ) const;`
- L35 _public member_ `TArray<FString> TraceChannels;`

#### class `FInsightsLaunchExtension`  
`class FInsightsLaunchExtension : public ProjectLauncher::FLaunchExtension`  
_L45-52_
- inherits: `ProjectLauncher::FLaunchExtension`
- L48 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L49 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L50 _public prototype_ `virtual FText GetDisplayName() const override;`
- L51 _public function_ `virtual bool IsAlwaysCreated(ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel) const override`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/ProfileWizard/ProfileWizardLaunchExtension.h` (Private)


#### class `FProfileWizardLaunchExtension`  
`class FProfileWizardLaunchExtension : public ProjectLauncher::FLaunchExtension`  
_L7-17_
- inherits: `ProjectLauncher::FLaunchExtension`
- L10 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L11 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L12 _public prototype_ `virtual FText GetDisplayName() const override;`
- L13 _public function_ `virtual bool IsAlwaysCreated(ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel) const override`
- L14 _public prototype_ `virtual void GetExtensionsMenuEntry( FExtensionsMenuEntry& MenuEntry ) const override;`
- L15 _public prototype_ `virtual void MakeCustomExtensionSubmenu(FMenuBuilder& MenuBuilder, ILauncherProfileRef InProfile, TSharedRef<ProjectLauncher::FModel> InModel) override;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/UserUATArgs/UserUATArgsLaunchExtension.h` (Private)


#### class `FUserUATArgsLaunchExtensionInstance`  
`class FUserUATArgsLaunchExtensionInstance : public ProjectLauncher::FBuildCookRunCommandExtensionInstance`  
_L8-27_
- inherits: `ProjectLauncher::FBuildCookRunCommandExtensionInstance`
- L11 _public prototype_ `FUserUATArgsLaunchExtensionInstance( FArgs& InArgs );`
- L12 _public prototype_ `virtual ~FUserUATArgsLaunchExtensionInstance() = default;`
- L14 _public prototype_ `virtual TSharedRef<ProjectLauncher::FBuildCookRunExtension> CreateBuildCookRunExtension( const ProjectLauncher::FBuildCookRunExtension::FArgs& InArgs ) override;`
- L17 _protected member_ `TSharedRef<class FUserUATArgsLaunchExtension> Owner;`

#### class `FUserUATArgsLaunchExtensionInstance::FBuildCookRunInstance`  
`class FBuildCookRunInstance : public ProjectLauncher::FBuildCookRunExtension`  
_L19-26_
- inherits: `ProjectLauncher::FBuildCookRunExtension`
- L22 _public prototype_ `FBuildCookRunInstance(const ProjectLauncher::FBuildCookRunExtension::FArgs& InArgs );`
- L23 _public prototype_ `virtual void CustomizeTree( ProjectLauncher::FLaunchProfileTreeNode& ProfileTreeNode ) override;`
- L24 _public prototype_ `virtual void CustomizeUATCommandLine(FString& InOutCommandLine) override;`

#### class `FUserUATArgsLaunchExtension`  
`class FUserUATArgsLaunchExtension : public ProjectLauncher::FBuildCookRunCommandExtension`  
_L30-36_
- inherits: `ProjectLauncher::FBuildCookRunCommandExtension`
- L33 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L34 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L35 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Private/UserUATCommand/UserUATCommandLaunchExtension.h` (Private)


#### class `FUserUATCommandLaunchExtensionInstance`  
`class FUserUATCommandLaunchExtensionInstance : public ProjectLauncher::FCustomUATCommandLaunchExtensionInstance`  
_L7-18_
- inherits: `ProjectLauncher::FCustomUATCommandLaunchExtensionInstance`
- L10 _public prototype_ `FUserUATCommandLaunchExtensionInstance(FArgs& InArgs);`
- L12 _public prototype_ `virtual void CustomizeTree(ProjectLauncher::FLaunchProfileTreeData& ProfileTreeData) override;`
- L13 _public prototype_ `virtual void CustomizeUATCommandLine(FString& InOutCommandLine) override;`
- L16 _protected prototype_ `virtual void OnUATCommandAdded(ILauncherProfileUATCommandRef InUATCommand) override;`
- L17 _protected prototype_ `virtual void OnValidateProfile() override;`

#### class `FUserUATCommandLaunchExtension`  
`class FUserUATCommandLaunchExtension: public ProjectLauncher::FCustomUATCommandLaunchExtension`  
_L20-26_
- inherits: `ProjectLauncher::FCustomUATCommandLaunchExtension`
- L23 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile(ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs) override;`
- L24 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Public/BuildSync/BuildInfoHelper.h` (Public)


#### class `FBuildInfoHelper`  
`class FBuildInfoHelper : public TSharedFromThis<FBuildInfoHelper>`  
_L15-110_
- inherits: `TSharedFromThis<FBuildInfoHelper>`
- L18 _public prototype_ `FBuildInfoHelper();`
- L19 _public prototype_ `~FBuildInfoHelper();`
- L33 _public prototype_ `void SetProjectName( const FString& InProjectName );`
- L34 _public prototype_ `void SetBuildType( const FString& InBuildType );`
- L35 _public prototype_ `FString GetBuildType() const;`
- L36 _public prototype_ `void SetBuildsRefreshedHandler(TFunction<void()> OnBuildsRefreshed);`
- L40 _public prototype_ `void Connect();` — build service connection
- L41 _public prototype_ `bool IsConnected() const;`
- L42 _public prototype_ `bool IsConfigured() const;`
- L43 _public prototype_ `FText GetErrorText() const;`
- L46 _public prototype_ `void Refresh( bool bFullRefresh );` — build list refresh
- L47 _public prototype_ `bool IsRefreshing() const;`
- L55 _public prototype_ `void SetFilter( const FFilter& Filter );`
- L59 _public prototype_ `TSharedRef<UE::Zen::Build::FBuildServiceInstance> GetServiceInstance() const;`
- L61 _public prototype_ `const TArray<TSharedPtr<FBuildInfo, ESPMode::ThreadSafe>>& GetBuildInfos() const;`
- L63 _public prototype_ `const TMap<FString,TSharedRef<UE::Zen::Build::FBuildListRetriever::FBuildType, ESPMode::ThreadSafe>>& GetBuildTypesMap() const;`
- L65 _public prototype_ `const TSet<FString>& GetAllKnownNamedArtifacts() const;`
- L67 _public prototype_ `FString GetPlatformNameFromNamedArtifact( const FString& NamedArtifact, const UE::Zen::Build::FBuildServiceInstance::FBuildRecord* BuildRecord = nullptr ) const;`
- L69 _public member_ `static const TCHAR* DefaultBuildType;`
- L76 _private member_ `TFunction<void()> OnBuildsRefreshed;`
- L77 _private member_ `FString ProjectName;`
- L78 _private member_ `FString BuildType;`
- L79 _private member_ `std::atomic<bool> bBuildListRetrieverInitComplete;`
- L80 _private member_ `TSharedPtr<UE::Zen::Build::FBuildListRetriever> BuildListRetriever;`
- L81 _private member_ `TSharedPtr<FBackendRetriever> BackendRetriever;`
- L82 _private member_ `TSharedPtr<FUGSBuildInfoRetriever> UGSBuildInfoRetriever;`
- L83 _private member_ `TSet<FString> KnownPlatformNames;`
- L86 _private member_ `FFilter Filter;`
- L92 _private prototype_ `void RefreshBackend();` — build list details
- L93 _private prototype_ `void RefreshUGSBuildInfo();`
- L94 _private prototype_ `void RefreshBuildGroups();`
- L95 _private prototype_ `void CreateFilteredBuildGroups( const TArrayView<TSharedRef<UE::Zen::Build::FBuildListRetriever::FBuildGroup>>& BuildGroups );`
- L97 _private member_ `TArray<TSharedRef<UE::Zen::Build::FBuildListRetriever::FBuildGroup>> FilteredBuildGroups;`
- L98 _private member_ `std::atomic<bool> bBuildGroupsRequestComplete;`
- L101 _private member_ `std::atomic<bool> bIsRefreshing = false;` — build info
- L102 _private prototype_ `void CheckRefreshComplete();`
- L103 _private prototype_ `void RebuildBuildInfos();`
- L104 _private member_ `TArray<TSharedPtr<FBuildInfo, ESPMode::ThreadSafe>> BuildInfos;`
- L105 _private member_ `TMap<FString,TSharedRef<UE::Zen::Build::FBuildListRetriever::FBuildType, ESPMode::ThreadSafe>> BuildTypesMap;`
- L106 _private member_ `TSet<FString> AllKnownNamedArtifacts;`

#### struct `FBuildInfoHelper::FBuildInfo`  
`struct FBuildInfo : public TSharedFromThis<FBuildInfo, ESPMode::ThreadSafe>`  
_L21-30_
- inherits: `TSharedFromThis<FBuildInfo,ESPMode::ThreadSafe>`
- L23 _public member_ `TSharedPtr<UE::Zen::Build::FBuildListRetriever::FBuildGroup> Group;`
- L25 _public member_ `TSharedPtr<FUGSBuildInfoRetriever::FUGSBuildInfo> UGSBuildInfo;`
- L26 _public member_ `TArray<FString> Backends;`
- L28 _public member_ `TSet<FName> Platforms;`
- L29 _public member_ `TMap<FName,TArray<FString>> PlatformToArtifacts;`

#### struct `FBuildInfoHelper::FFilter`  
`struct FFilter`  
_L50-54_
- desc: list filtering
- L52 _public member_ `FTimespan MaxAge;`
- L53 _public member_ `int32 MaxItems = 50;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONLAUNCHEXTENSIONS_API`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Public/BuildSync/BuildSyncLaunchExtension.h` (Public)


#### class `FBuildSyncLaunchExtensionInstance`  
`class FBuildSyncLaunchExtensionInstance : public ProjectLauncher::FCustomUATCommandLaunchExtensionInstance`  
_L18-82_
- inherits: `ProjectLauncher::FCustomUATCommandLaunchExtensionInstance`
- L21 _public prototype_ `FBuildSyncLaunchExtensionInstance( FArgs& InArgs );`
- L22 _public prototype_ `virtual ~FBuildSyncLaunchExtensionInstance();`
- L24 _public prototype_ `virtual void InternalInitialize() override;`
- L26 _public prototype_ `virtual void CustomizeTree( ProjectLauncher::FLaunchProfileTreeData& ProfileTreeData ) override;`
- L27 _public prototype_ `virtual void CustomizeUATCommandLine( FString& InOutCommandLine ) override;`
- L29 _public prototype_ `virtual void OnUATCommandAdded( ILauncherProfileUATCommandRef UATCommand ) override;`
- L30 _public prototype_ `void OnOtherUATCommandAdded(const ILauncherProfileUATCommandRef& UATCommand);`
- L33 _public prototype_ `virtual void OnValidateProfile() override;`
- L34 _public prototype_ `virtual void OnProjectChanged() override;`
- L35 _public prototype_ `virtual void OnPropertyChanged() override;`
- L37 _public prototype_ `TArray<FString> GetSelectedBuildBackends() const;`
- L40 _private prototype_ `UE::Zen::Build::FBuildServiceInstance::EConnectionState GetBuildServiceConnectionState() const;`
- L41 _private prototype_ `void OnBuildsRefreshed();`
- L42 _private prototype_ `void RefreshFilteredBuilds();`
- L44 _private prototype_ `void SetBuildType( FString InBuildType );`
- L45 _private prototype_ `FString GetBuildType() const;`
- L46 _private prototype_ `void SetNamedArtifacts( TArray<FString> InNamedArtifacts );`
- L47 _private prototype_ `TArray<FString> GetNamedArtifacts() const;`
- L48 _private prototype_ `void SetDestinationDirectory(FString InPath);`
- L49 _private prototype_ `FString GetDestinationDirectory() const;`
- L51 _private prototype_ `void AutoSelectBestBuild();`
- L52 _private prototype_ `void AutoSelectNamedArtifacts();`
- L54 _private prototype_ `TSharedRef<SWidget> CreateBuildStorageConnectionWidget();`
- L55 _private prototype_ `TSharedRef<SWidget> CreateBuildFilterWidget();`
- L56 _private prototype_ `TSharedRef<SWidget> CreateBuildTypeSelectionWidget();`
- L57 _private prototype_ `TSharedRef<SWidget> CreateNamedArtifactSelectionWidget();`
- L59 _private prototype_ `void SetSelectedBuild(TSharedPtr<FBuildInfoHelper::FBuildInfo> Build);`
- L60 _private prototype_ `TSharedPtr<FBuildInfoHelper::FBuildInfo> GetSelectedBuild() const;`
- L61 _private prototype_ `TArray<FString> GetAvailableArtifactsForSelectedBuild() const;`
- L63 _private prototype_ `bool GetBuildSuitability( TSharedPtr<FBuildInfoHelper::FBuildInfo> Build, FText* OutReason ) const;`
- L64 _private prototype_ `void CacheUnsuitableBuilds();`
- L66 _private member_ `TSharedPtr<FBuildInfoHelper::FBuildInfo> SelectedBuild;`
- L68 _private member_ `TSharedPtr<FBuildInfoHelper> BuildInfo;`
- L69 _private member_ `TSharedRef<class FBuildSyncLaunchExtension> Owner;`
- L70 _private member_ `TSharedPtr<class SBuildSyncBuildCombo> BuildCombo;`
- L71 _private member_ `TArray<FString> CachedNamedArtifacts;`
- L72 _private member_ `TMap<TSharedPtr<FBuildInfoHelper::FBuildInfo>, FText> CachedUnsuitableBuilds;`
- L73 _private member_ `TArray<TSharedPtr<FBuildInfoHelper::FBuildInfo>> FilteredBuildInfos;`
- L75 _private member_ `bool bShowPreflights = false;`
- L76 _private member_ `bool bShowUnsuitable = false;`
- L77 _private member_ `FString FilterText;`
- L78 _private member_ `FString DestinationDirectory;`
- L80 _private prototype_ `TSet<const PlatformInfo::FTargetPlatformInfo*> GetCookPlatforms() const;`
- L81 _private member_ `TSet<const PlatformInfo::FTargetPlatformInfo*> CachedCookPlatforms;`

#### class `FBuildSyncLaunchExtension`  
`class FBuildSyncLaunchExtension : public ProjectLauncher::FCustomUATCommandLaunchExtension`  
_L85-93_
- inherits: `ProjectLauncher::FCustomUATCommandLaunchExtension`
- L88 _public prototype_ `FBuildSyncLaunchExtension();`
- L90 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile( ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs ) override;`
- L91 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L92 _public prototype_ `virtual FText GetDisplayName() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONLAUNCHEXTENSIONS_API`
- L13 _namespace_ `namespace PlatformInfo`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Public/BuildSync/SBuildSyncBuildCombo.h` (Public)


#### class `SBuildSyncBuildCombo`  
`class SBuildSyncBuildCombo : public SCompoundWidget`  
_L19-59_
- inherits: `SCompoundWidget`
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TSharedPtr<FBuildInfoHelper::FBuildInfo> );`
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetItemSuitability, TSharedPtr<FBuildInfoHelper::FBuildInfo>, FText* );`
- L26 _public function_ `SLATE_BEGIN_ARGS(SBuildSyncBuildCombo) : _OptionsSource() , _TextStyle( &FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "NormalText" ) )`
- L30 _public prototype_ `SLATE_ARGUMENT(const TArray<TSharedPtr<FBuildInfoHelper::FBuildInfo>>*, OptionsSource) SLATE_ARGUMENT(TSharedPtr<SWidget>, FilterWidget) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L33 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FBuildInfoHelper::FBuildInfo>, SelectedItem);`
- L41 _public prototype_ `void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `void RefreshOptions();`
- L45 _protected member_ `const TArray<TSharedPtr<FBuildInfoHelper::FBuildInfo>>* OptionsSource;`
- L46 _protected member_ `TAttribute<TSharedPtr<FBuildInfoHelper::FBuildInfo>> SelectedItem;`
- L47 _protected member_ `TAttribute<TSet<FName>> RequiredPlatforms;`
- L48 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L49 _protected member_ `FGetItemSuitability GetItemSuitability;`
- L51 _protected prototype_ `TSharedRef<ITableRow> OnGenerateBuildInfoRow( TSharedPtr<FBuildInfoHelper::FBuildInfo> BuildInfo, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L52 _protected prototype_ `void OnBuildInfoSelectionChanged( TSharedPtr<FBuildInfoHelper::FBuildInfo> BuildInfo, ESelectInfo::Type InSelectInfo );`
- L53 _protected prototype_ `FText GetSelectedBuildInfoName() const;`
- L55 _protected member_ `TSharedPtr<SComboButton> ComboButton;`
- L56 _protected member_ `TSharedPtr<SListView<TSharedPtr<FBuildInfoHelper::FBuildInfo>>> BuildInfosListView;`
- L58 _protected prototype_ `FText GetAge( const FDateTime& DateTime ) const;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API COMMONLAUNCHEXTENSIONS_API`
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TSharedPtr<FBuildInfoHelper::FBuildInfo> );`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetItemSuitability, TSharedPtr<FBuildInfoHelper::FBuildInfo>, FText* );`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Public/Shared/BackendRetriever.h` (Public)


#### class `FBackendRetriever`  
`class FBackendRetriever : public TSharedFromThis<FBackendRetriever>`  
_L11-36_
- inherits: `TSharedFromThis<FBackendRetriever>`
- L14 _public typedef_ `typedef TUniqueFunction<void()> FOnBackendRetrievalComplete;`
- L16 _public prototype_ `FBackendRetriever();`
- L18 _public prototype_ `void GetBackendsAsync(FOnBackendRetrievalComplete&& InOnComplete);`
- L19 _public prototype_ `bool IsGettingBackends() const;`
- L20 _public prototype_ `bool IsConfigured() const;`
- L22 _public prototype_ `const TMap<int32, TArray<FString>>& GetBuildToBackendsMap() const;`
- L23 _public prototype_ `const FString& GetErrorMessage() const;`
- L27 _private prototype_ `void ParseBackendFromOutput(const FString& QueryResult);`
- L28 _private prototype_ `void Completed();`
- L30 _private member_ `FOnBackendRetrievalComplete OnComplete;`
- L31 _private member_ `std::atomic<bool> bIsGettingBackends = false;`
- L33 _private member_ `TMap<int32, TArray<FString>> BuildToBackendsMap;`
- L34 _private member_ `FString ErrorMessage;`
- L35 _private member_ `FString BackendQueryUrl;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Public/Shared/UGSBuildInfoRetriever.h` (Public)


#### class `FUGSBuildInfoRetriever`  
`class FUGSBuildInfoRetriever : public TSharedFromThis<FUGSBuildInfoRetriever>`  
_L12-66_
- inherits: `TSharedFromThis<FUGSBuildInfoRetriever>`
- L43 _public typedef_ `typedef TUniqueFunction<void()> FOnUGSBuildInfoRetrievalComplete;`
- L45 _public prototype_ `FUGSBuildInfoRetriever();`
- L47 _public prototype_ `void GetUGSBuildInfoAsync( const FString& InProjectName, const TArrayView<int32>& InChangelists, FOnUGSBuildInfoRetrievalComplete&& InOnComplete );`
- L48 _public prototype_ `bool IsGettingUGSBuildInfo() const;`
- L49 _public prototype_ `bool IsConfigured() const;`
- L51 _public prototype_ `const TMap<int32, TSharedRef<FUGSBuildInfo>>& GetBuildToUGSBuildInfoMap();`
- L52 _public prototype_ `const FString& GetErrorMessage() const;`
- L56 _private prototype_ `void ParseUGSBuildInfoFromQuery(const FString& Text, const FString& ProjectName);`
- L57 _private prototype_ `FUGSBadge::EState ParseUGSBadgeState(const FString& Text);`
- L58 _private prototype_ `void Completed();`
- L60 _private member_ `FOnUGSBuildInfoRetrievalComplete OnComplete;`
- L61 _private member_ `std::atomic<bool> bIsGettingUGSBuildInfo = false;`
- L63 _private member_ `TMap<int32, TSharedRef<FUGSBuildInfo>> BuildToUGSBuildInfoMap;`
- L64 _private member_ `FString ErrorMessage;`
- L65 _private member_ `FString HordeMetadataUrl;`

#### struct `FUGSBuildInfoRetriever::FUGSBadge`  
`struct FUGSBadge`  
_L15-32_
- L29 _public member_ `FString Name;`
- L30 _public member_ `FString URL;`
- L31 _public member_ `EState State;`

#### enum `FUGSBuildInfoRetriever::FUGSBadge::EState`  
`enum class EState : uint8`  
_L17-27_
- L19 _public enumerator_ `Starting`
- L20 _public enumerator_ `Failure`
- L21 _public enumerator_ `Warning`
- L22 _public enumerator_ `Success`
- L23 _public enumerator_ `Skipped`
- L25 _public enumerator_ `Unknown`
- L26 _public enumerator_ `MAX`

#### struct `FUGSBuildInfoRetriever::FUGSBuildInfo`  
`struct FUGSBuildInfo : public TSharedFromThis<FUGSBuildInfo, ESPMode::ThreadSafe>`  
_L34-41_
- inherits: `TSharedFromThis<FUGSBuildInfo,ESPMode::ThreadSafe>`
- L36 _public member_ `int32 NumUsers = 0;`
- L37 _public member_ `int32 NumSuccess = 0;`
- L38 _public member_ `int32 NumFailed = 0;`
- L40 _public member_ `TArray<FUGSBadge> Badges;`

### `Plugins/Developer/ProjectLauncher/Source/CommonLaunchExtensions/Public/UgsSync/UgsSyncLaunchExtension.h` (Public)


#### class `FUGSSyncLaunchExtensionInstance`  
`class FUGSSyncLaunchExtensionInstance : public ProjectLauncher::FCustomUATCommandLaunchExtensionInstance`  
_L7-34_
- inherits: `ProjectLauncher::FCustomUATCommandLaunchExtensionInstance`
- L10 _public prototype_ `FUGSSyncLaunchExtensionInstance(FArgs& InArgs);`
- L11 _public prototype_ `virtual ~FUGSSyncLaunchExtensionInstance();`
- L13 _public prototype_ `virtual void InternalInitialize() override;`
- L15 _public prototype_ `virtual void CustomizeTree(ProjectLauncher::FLaunchProfileTreeData& ProfileTreeData) override;`
- L16 _public prototype_ `virtual void CustomizeUATCommandLine(FString& InOutCommandLine) override;`
- L18 _public prototype_ `const FString GetUATCommandInternalName() const;`
- L21 _protected prototype_ `virtual void OnUATCommandAdded(ILauncherProfileUATCommandRef InUATCommand) override;`
- L24 _private prototype_ `void OnSelectedChangelistCommitted(const FText& InText, ETextCommit::Type CommitType);`
- L25 _private prototype_ `void RefreshLatestSyncedState();`
- L27 _private function_ `bool IsDryRunEnabled() const`
- L28 _private function_ `void SetDryRunEnabled(bool Val)`
- L31 _private member_ `int32 SelectedChangelist = 0;`
- L32 _private member_ `int32 SyncedChangelist = 0;`
- L33 _private member_ `bool bDryRun = false;`

#### class `FUGSSyncLaunchExtension`  
`class FUGSSyncLaunchExtension: public ProjectLauncher::FCustomUATCommandLaunchExtension`  
_L36-43_
- inherits: `ProjectLauncher::FCustomUATCommandLaunchExtension`
- L39 _public prototype_ `FUGSSyncLaunchExtension();`
- L40 _public prototype_ `virtual TSharedPtr<ProjectLauncher::FLaunchExtensionInstance> CreateInstanceForProfile(ProjectLauncher::FLaunchExtensionInstance::FArgs& InArgs) override;`
- L41 _public prototype_ `virtual const TCHAR* GetInternalName() const override;`
- L42 _public prototype_ `virtual FText GetDisplayName() const override;`
