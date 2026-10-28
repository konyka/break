# Plugins / DisplayClusterLaunchEditor

- module root: `Plugins/Editor/DisplayClusterLaunch/Source/DisplayClusterLaunchEditor`
- headers: 4; symbols: 100
- symbol kinds: class=3, delegate=1, enum=2, enumerator=11, function=1, member=28, prototype=52, struct=2
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, Concert, ConcertClient, ConcertSyncClient, ConcertTransport, ConsoleVariablesEditor, ConsoleVariablesEditorRuntime, ContentBrowser, CoreUObject, DisplayCluster, DisplayClusterConfiguration, EditorStyle, EditorWidgets, Engine, InputCore, Kismet, Messaging, MultiUserClient, Networking, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UdpMessaging, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, OutputLog, PlacementMode

### `Plugins/Editor/DisplayClusterLaunch/Source/DisplayClusterLaunchEditor/Public/DisplayClusterLaunchEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogDisplayClusterLaunchEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogDisplayClusterLaunchEditor, Log, All);`

### `Plugins/Editor/DisplayClusterLaunch/Source/DisplayClusterLaunchEditor/Public/DisplayClusterLaunchEditorModule.h` (Public)


#### class `FDisplayClusterLaunchEditorModule`  
`class FDisplayClusterLaunchEditorModule : public IModuleInterface`  
_L31-143_
- inherits: `IModuleInterface`
- L50 _public prototype_ `static FDisplayClusterLaunchEditorModule& Get();`
- L53 _public prototype_ `virtual void StartupModule() override;`
- L54 _public prototype_ `virtual void ShutdownModule() override;`
- L57 _public prototype_ `static void OpenProjectSettings();`
- L64 _public prototype_ `void TryLaunchDisplayClusterProcess();` — Performs a sanity check to determine if nDisplay can be launched and if so, gets Concert parameters async if Concert is enabled for the launch. Ultimately, LaunchDisplayClusterProcess will be called when Concert parameters are skipped or returned.
- L65 _public prototype_ `void TerminateActiveDisplayClusterProcesses();`
- L68 _private prototype_ `void EnsureMultiUserDiscovery();`
- L69 _private prototype_ `void StopMultiUserDiscovery();`
- L71 _private prototype_ `void OnFEngineLoopInitComplete();`
- L73 _private prototype_ `void LaunchConcertServer();`
- L75 _private prototype_ `void FindOrLaunchConcertServer();`
- L76 _private prototype_ `void OnServersAssumedReady();`
- L77 _private prototype_ `void FindAppropriateServer();`
- L78 _private prototype_ `void ConnectToSession();`
- L80 _private prototype_ `void LaunchDisplayClusterProcess();`
- L82 _private prototype_ `void RegisterToolbarItem();`
- L83 _private prototype_ `FText GetToolbarButtonTooltipText();`
- L84 _private prototype_ `FSlateIcon GetToolbarButtonIcon();`
- L85 _private prototype_ `void OnClickToolbarButton();`
- L86 _private prototype_ `void RemoveToolbarItem();`
- L88 _private prototype_ `void RegisterProjectSettings() const;`
- L90 _private prototype_ `static void RegisterPlacementModeItemsIfTheyExist();`
- L91 _private prototype_ `static const FPlacementCategoryInfo* GetDisplayClusterPlacementCategoryInfo();`
- L94 _private prototype_ `FText GetSelectedNodesListText() const;` — Returns a list of selected nodes as FText separated by new lines with the Primary Node marked.
- L96 _private prototype_ `void GetProjectSettingsArguments( const UDisplayClusterLaunchEditorProjectSettings* ProjectSettings, FString& ConcatenatedCommandLineArguments, FString& ConcatenatedConsoleCommands, TSet<FString>& DPCvars, FString& ConcatenatedLogCommands);`
- L100 _private prototype_ `TArray<TWeakObjectPtr<ADisplayClusterRootActor>> GetAllDisplayClusterConfigsInWorld();`
- L101 _private prototype_ `bool DoesCurrentWorldHaveDisplayClusterConfig();`
- L102 _private prototype_ `void ApplyDisplayClusterConfigOverrides(class UDisplayClusterConfigurationData* ConfigDataCopy);`
- L105 _private prototype_ `void RefreshSelectedDisplayActor();` — Updates the selected nDisplay actor if invalid or unresolvable
- L107 _private prototype_ `void SetSelectedDisplayClusterConfigActor(ADisplayClusterRootActor* SelectedActor);`
- L108 _private prototype_ `void ToggleDisplayClusterConfigActorNodeSelected(FString InNodeName);`
- L109 _private prototype_ `bool IsDisplayClusterConfigActorNodeSelected(FString InNodeName);`
- L110 _private prototype_ `void SetSelectedConsoleVariablesAsset(const FAssetData InConsoleVariablesAsset);`
- L112 _private prototype_ `void SelectFirstNode(ADisplayClusterRootActor* InConfig);`
- L114 _private prototype_ `TSharedRef<SWidget> CreateToolbarMenuEntries();`
- L115 _private prototype_ `void AddDisplayClusterLaunchConfigurations( IAssetRegistry* AssetRegistry, FMenuBuilder& MenuBuilder, TArray<TWeakObjectPtr<ADisplayClusterRootActor>>& DisplayClusterConfigs);`
- L117 _private prototype_ `void AddDisplayClusterLaunchNodes(class IAssetRegistry* AssetRegistry, FMenuBuilder& MenuBuilder);`
- L118 _private prototype_ `void AddConsoleVariablesEditorAssetsToToolbarMenu(IAssetRegistry* AssetRegistry, FMenuBuilder& MenuBuilder);`
- L119 _private prototype_ `void AddOptionsToToolbarMenu(FMenuBuilder& MenuBuilder);`
- L121 _private prototype_ `bool GetConnectToMultiUser() const;`
- L122 _private prototype_ `const FString& GetConcertServerName();`
- L123 _private prototype_ `const FString& GetConcertSessionName();`
- L125 _private prototype_ `void RemoveTerminatedNodeProcesses();`
- L127 _private member_ `bool bAreConfigsFoundInWorld = false;`
- L129 _private member_ `FSoftObjectPath SelectedDisplayClusterConfigActor;`
- L130 _private member_ `TArray<FString> SelectedDisplayClusterConfigActorNodes;`
- L131 _private member_ `FString SelectedDisplayClusterConfigActorPrimaryNode;`
- L133 _private member_ `FSoftObjectPath SelectedAdditionalConsoleVariablesAsset;`
- L135 _private member_ `FDisplayClusterLaunchMultiUserServerTrackingData ServerTrackingData;`
- L136 _private member_ `FString CachedConcertSessionName;`
- L138 _private member_ `TArray<FProcHandle> ActiveDisplayClusterProcesses;`
- L140 _private member_ `EConcertServerRequestStatus ConcertServerRequestStatus = EConcertServerRequestStatus::None;`
- L142 _private member_ `bool bDidStartDiscovery = false;`

#### enum `FDisplayClusterLaunchEditorModule::EConcertServerRequestStatus`  
`enum class EConcertServerRequestStatus`  
_L35-41_
- L37 _public enumerator_ `None`
- L38 _public enumerator_ `ShutdownRequested`
- L39 _public enumerator_ `LaunchRequested`
- L40 _public enumerator_ `ReuseExisting`

#### struct `FDisplayClusterLaunchEditorModule::FDisplayClusterLaunchMultiUserServerTrackingData`  
`struct FDisplayClusterLaunchMultiUserServerTrackingData`  
_L43-48_
- L45 _public member_ `FString GeneratedMultiUserServerName;`
- L46 _public member_ `FConcertServerInfo MultiUserServerInfo;`
- L47 _public member_ `FProcHandle MultiUserServerHandle;`

### `Plugins/Editor/DisplayClusterLaunch/Source/DisplayClusterLaunchEditor/Public/DisplayClusterLaunchEditorProjectSettings.h` (Public)


#### enum `EDisplayClusterLaunchLogVerbosity`  
`enum EDisplayClusterLaunchLogVerbosity : int`  
_L10-44_
- reflection: `UENUM()`
- L13 _public enumerator_ `Fatal` — Always prints a fatal error to console (and log file) and crashes (even if logging is disabled)
- L19 _public enumerator_ `Error` — Prints an error to console (and log file). Commandlets and the editor collect and report errors. Error messages result in commandlet failure.
- L25 _public enumerator_ `Warning` — Prints a warning to console (and log file). Commandlets and the editor collect and report warnings. Warnings can be treated as an error.
- L28 _public enumerator_ `Display` — Prints a message to console (and log file)
- L31 _public enumerator_ `Log` — Prints a message to a log file (does not print to console)
- L37 _public enumerator_ `Verbose` — Prints a verbose message to a log file (if Verbose logging is enabled for the given category, usually used for detailed logging)
- L43 _public enumerator_ `VeryVerbose` — Prints a verbose message to a log file (if VeryVerbose logging is enabled, usually used for detailed logging that would otherwise spam output)

#### struct `FDisplayClusterLaunchLoggingConstruct`  
`struct FDisplayClusterLaunchLoggingConstruct`  
_L47-56_
- reflection: `USTRUCT()`
- L52 _public member_ `FName Category;` — `UPROPERTY(config, EditAnywhere, Category="nDisplay Launch Settings")`
- L55 _public member_ `TEnumAsByte<EDisplayClusterLaunchLogVerbosity> VerbosityLevel = EDisplayClusterLaunchLogVerbosity::VeryVerbose;` — `UPROPERTY(config, EditAnywhere, Category="nDisplay Launch Settings")`

#### class `UDisplayClusterLaunchEditorProjectSettings`  
`class UDisplayClusterLaunchEditorProjectSettings : public UObject`  
_L59-151_
- reflection: `UCLASS(config = DisplayClusterLaunch, defaultconfig)`
- inherits: `UObject`
- L69 _public member_ `bool bCloseEditorOnLaunch = false;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings")` — If true, the editor will be closed on session launch to optimize session performance.
- L77 _public member_ `bool bConnectToMultiUser = false;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Multi-User")` — If true, this command will attempt to connect to an existing session or create a new Multi-User session with the options specified in the Multi-User Editing project settings.
- L84 _public member_ `FString ExplicitSessionName;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Multi-User", meta = (EditCondition="bConnectToMultiUser"))` — A specific session name to use when connecting to multi-user if bAutoGenerateSessionName is false. If left empty, a name will be generated.
- L90 _public member_ `bool bEnableUnrealInsights = false;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Unreal Insights")` — Whether or not to enable Unreal Insights for this session
- L96 _public member_ `bool bEnableStatNamedEvents = false;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Unreal Insights", meta = (EditCondition="bEnableUnrealInsights"))` — Enable support for Stat Named Events in Unreal Insights
- L104 _public member_ `FDirectoryPath ExplicitTraceFileSaveDirectory;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Unreal Insights", meta = (EditCondition="bEnableUnrealInsights"))` — Where to store the Unreal Insights Trace Files. If empty, Unreal Insights will connect to localhost (this computer) instead and you'll need to ensure Unreal Insights is launched. To specify a socket to connect to, use CommandLineArguments.
- L111 _public member_ `FSoftObjectPath ConsoleVariablesPreset;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Console", meta = (AllowedClasses="/Script/ConsoleVariablesEditorRuntime.ConsoleVariablesAsset"))` — A Console Variables Asset to always apply to your launches. All saved commands and variables will be executed before "Additional" ones specified below.
- L120 _public member_ `TSet<FString> AdditionalConsoleVariables;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Console", meta = (Keywords = "DPCvars"))` — DPCvars You can specify additional console variables here to be executed after those of the Console Variable Preset are executed. This is useful for overriding variables in your defined Console Variables Asset. Console Variables generally have a name and a value, like "r.ScreenPercentage 50"
- L128 _public member_ `TSet<FString> AdditionalConsoleCommands;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Console")` — You can specify additional console commands here to be executed after those of the Console Variable Preset are executed. This is useful for overriding commands in your defined Console Variables Asset. Console Commands generally have a name and no value (i.e. 'stat unit') though some have a value too (i.e. "r.SetNearClipPlane 500")
- L136 _public member_ `TSet<FString> CommandLineArguments;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Console")` — A list of command line arguments to append to the Switchboard command (e.g. messaging, fullscreen, handleensurepercent=0) Do not include the dash ("-") as this will be automatically added for you when calling the command. Parameters for arguments are supported, such as "handleensurepercent=0".
- L144 _public member_ `FString LogFileName;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Logging")` — The name of the log file to which to write logs for the launched node. '.log' will be automatically appended to the file name. If not specified, the nDisplay node's name will be used instead.
- L150 _public member_ `TArray<FDisplayClusterLaunchLoggingConstruct> Logging;` — `UPROPERTY(Config, EditAnywhere, Category="nDisplay Launch Settings|Logging")` — Which logs to include and with which verbosity level

### `Plugins/Editor/DisplayClusterLaunch/Source/DisplayClusterLaunchEditor/Public/DisplayClusterLaunchEditorStyle.h` (Public)


#### class `FDisplayClusterLaunchEditorStyle`  
`class FDisplayClusterLaunchEditorStyle : FSlateStyleSet`  
_L7-36_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public prototype_ `static void ReloadTextures();`
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L19 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L21 _public prototype_ `virtual const FSlateBrush* GetBrush(const FName PropertyName, const ANSICHAR* Specifier = nullptr, const ISlateStyle* RequestingStyle = nullptr) const override;`
- L24 _public function_ `template< typename WidgetStyleType > static const WidgetStyleType& GetWidgetStyle(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L31 _private prototype_ `static FString GetExternalPluginContent(const FString& PluginName, const FString& RelativePath, const ANSICHAR* Extension);`
- L33 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L35 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`
