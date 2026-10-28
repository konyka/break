# Runtime / PreLoadScreen

- module root: `Source/Runtime/PreLoadScreen`
- headers: 7; symbols: 254
- symbol kinds: class=9, delegate=3, enum=1, enumerator=3, function=40, member=70, prototype=123, struct=5
- PrivateDependencyModuleNames: BuildPatchServices, Core, CoreUObject, InputCore, Projects, RHI, RenderCore, Slate, SlateCore
- PrivateIncludePathModuleNames: Launch
- PublicDependencyModuleNames: Analytics, AnalyticsET, ApplicationCore, Engine

### `Source/Runtime/PreLoadScreen/Public/BuildPatchServicesPreLoadManager.h` (Public)


#### class `FBuildPatchServicesPreLoadManagerBase`  
`class FBuildPatchServicesPreLoadManagerBase : public TSharedFromThis<FBuildPatchServicesPreLoadManagerBase>`  
_L19-70_
- inherits: `TSharedFromThis<FBuildPatchServicesPreLoadManagerBase>`
- desc: This class is used to help manage a PreLoadScreen based on a BuildPatchServices install.
- L22 _public prototype_ `FBuildPatchServicesPreLoadManagerBase();`
- L23 _public prototype_ `virtual ~FBuildPatchServicesPreLoadManagerBase() = default;`
- L25 _public prototype_ `virtual void Init();`
- L28 _public prototype_ `virtual void StartBuildPatchServices(BuildPatchServices::FBuildInstallerConfiguration Settings);` — Setup BPT with everything now loaded
- L31 _public prototype_ `virtual void OnContentBuildInstallerComplete(const IBuildInstallerRef& Installer);` — BPT finished
- L33 _public prototype_ `virtual bool IsDone() const;`
- L35 _public function_ `virtual int64 GetDownloadSize()`
- L36 _public function_ `virtual int64 GetDownloadProgress()`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildPatchCompleted, bool );`
- L39 _public member_ `FOnBuildPatchCompleted OnBuildPatchCompletedDelegate;`
- L41 _public prototype_ `virtual void PauseBuildPatchInstall();`
- L42 _public prototype_ `virtual void ResumeBuildPatchInstall();`
- L43 _public prototype_ `virtual void CancelBuildPatchInstall();`
- L45 _public function_ `float GetProgressPercent() const`
- L46 _public function_ `EBuildPatchDownloadHealth GetDownloadHealth() const`
- L47 _public prototype_ `const FText& GetStatusText() const;`
- L48 _public function_ `BuildPatchServices::EBuildPatchState GetState() const`
- L50 _public function_ `FText GetErrorMessageBody() const`
- L51 _public function_ `EBuildPatchInstallError GetErrorType() const`
- L52 _public function_ `FString GetErrorCode() const`
- L54 _public function_ `virtual bool IsActive()`
- L62 _public function_ `IBuildInstallerPtr GetInstaller()`
- L65 _protected member_ `bool bPatchingStarted;`
- L66 _protected member_ `bool bPatchingFinished;`
- L68 _protected member_ `IBuildPatchServicesModule* BuildPatchServicesModule;`
- L69 _protected member_ `IBuildInstallerPtr ContentBuildInstaller;`

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildPatchCompleted, bool );`

### `Source/Runtime/PreLoadScreen/Public/PreLoadScreen.h` (Public)


#### enum `EPreLoadScreenTypes`  
`enum class EPreLoadScreenTypes : uint8`  
_L9-14_
- L11 _public enumerator_ `CustomSplashScreen`
- L12 _public enumerator_ `EarlyStartupScreen`
- L13 _public enumerator_ `EngineLoadingScreen`

#### class `IPreLoadScreen`  
`class IPreLoadScreen : public TSharedFromThis<IPreLoadScreen>`  
_L19-76_
- inherits: `TSharedFromThis<IPreLoadScreen>`
- desc: Interface that defines the class that handles all the logic for controlling / displaying a particular PreLoadScreen. Designed to be implemented in a Plugin that calls FPreLoadScreenManager::RegisterPreLoadScreen so that functions are called by PreLoadScreenManager correctly. Really should probably inherit from FPreLoadScreenBase instead of this class for more functionality
- L22 _public prototype_ `virtual ~IPreLoadScreen() = default;`
- L24 _public prototype_ `virtual void Init() = 0;`
- L27 _public prototype_ `virtual void Tick(float DeltaTime) = 0;` — Standard tick that happens every frame
- L33 _public prototype_ `virtual float GetAddedTickDelay() = 0;` — This function is used to determine if an extra platform sleep should be performed every tick (to slow down the tick rate) keeps us from spinning super fast when we aren't doing much beyond loading data / etc on other threads.
- L36 _public prototype_ `virtual bool ShouldRender() const = 0;` — Whether an EarlyStartupLoadScreen should render
- L42 _public prototype_ `virtual void RenderTick(FRHICommandListImmediate& RHICmdList, float DeltaTime) = 0;` — This tick happens as part of the slate render tick during an EarlyStartupLoadScreen @note Called on the render thread
- L45 _public prototype_ `virtual void OnPlay(TWeakPtr<SWindow> TargetWindow) = 0;` — Callback for when a PreLoadScreen starts being displayed. Provides a reference to the SWindow that will be used to display content
- L48 _public prototype_ `virtual void OnStop() = 0;` — Callback for when a PreLoadScreen is no longer being displayed.
- L54 _public prototype_ `virtual bool IsDone() const = 0;` — Returns true when the PreLoadScreen is completed. @note This need to be thread safe
- L56 _public prototype_ `virtual void CleanUp() = 0;`
- L63 _public prototype_ `virtual EPreLoadScreenTypes GetPreLoadScreenType() const = 0;` — Should override this function to determine if this screen should be used to handle EarlyStartupScreen behavior @note IMPORTANT: This changes a LOT of functionality and implementation details. EarlyStartupScreens happen before the engine is fully initialized and block engine initialization before they finish. this means they have to forgo even the most basic of engine features like UObject support, as they are displayed before those systems are initialized.
- L69 _public prototype_ `virtual FName GetPreLoadScreenTag() const = 0;` — Allows the PreLoadScreen to register a tag that can be later used to find a specific loading screen. PreLoadScreens not using this functionality should return NAME_None
- L72 _public prototype_ `virtual void SetEngineLoadingFinished(bool IsEngineLoadingFinished) = 0;` — @See IsDone when GetPreLoadScreenType() returns EPreLoadScreenTypes::EngineLoadingScreen
- L74 _public prototype_ `virtual const TSharedPtr<const SWidget> GetWidget() const = 0;`
- L75 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget() = 0;`

### `Source/Runtime/PreLoadScreen/Public/PreLoadScreenBase.h` (Public)


#### class `FPreLoadScreenBase`  
`class FPreLoadScreenBase : public IPreLoadScreen`  
_L9-68_
- inherits: `IPreLoadScreen`
- desc: Base implementation of the IPreLoadScreen that handles all the logic for controlling / updating the UI for PreLoadScreens. Designed to be overriden by a game specific Plugin that calls FPreloadScreenManager::RegisterPreLoadScreen so that functions are called by the PreLoadScreenManager correctly.
- L15 _public function_ `virtual void Tick(float DeltaTime) override` — We don't use these in the FPreLoadScreenBase, but they are useful for game-specific implementations
- L16 _public function_ `virtual bool ShouldRender() const override`
- L17 _public function_ `virtual void RenderTick(FRHICommandListImmediate& RHICmdList, float DeltaTime) override`
- L18 _public function_ `virtual void OnStop() override`
- L21 _public function_ `virtual void OnPlay(TWeakPtr<SWindow> TargetWindow) override` — Store off TargetWindow
- L24 _public function_ `virtual float GetAddedTickDelay() override` — By default have a small added tick delay so we don't super spin out while waiting on other threads to load data / etc.
- L26 _public function_ `virtual void Init() override`
- L28 _public function_ `virtual TSharedPtr<SWidget> GetWidget() override`
- L29 _public function_ `virtual const TSharedPtr<const SWidget> GetWidget() const override`
- L33 _public function_ `virtual EPreLoadScreenTypes GetPreLoadScreenType() const override` — IMPORTANT: This changes a LOT of functionality and implementation details. EarlyStartupScreens happen before the engine is fully initialized and block engine initialization before they finish. this means they have to forgo even the most basic of engine features like UObject support, as they are displayed before those systems are initialized.
- L35 _public function_ `virtual void SetEngineLoadingFinished(bool IsEngineLoadingFinished) override`
- L38 _public function_ `virtual FName GetPreLoadScreenTag() const override` — PreLoadScreens not using this functionality should return NAME_None
- L40 _public prototype_ `virtual void CleanUp() override;`
- L43 _public prototype_ `virtual bool IsDone() const override;` — Default behavior is just to see if we have an active widget. Should really overload with our own behavior to see if we are done displaying
- L46 _public function_ `FPreLoadScreenBase() : bIsEngineLoadingFinished(false)`
- L50 _public prototype_ `virtual ~FPreLoadScreenBase() override = default;`
- L53 _public prototype_ `virtual void InitSettingsFromConfig(const FString& ConfigFileName);` — Handles constructing a FPreLoadSettingsContainerBase with the
- L57 _public function_ `virtual void SetPluginName(const FString& PluginNameIn)` — Set what plugin is creating this PreLoadScreenBase. Used to make file paths relative to that plugin as well as determining . Used for converting locations for content to be relative to the plugin calling us
- L60 _protected member_ `TWeakPtr<SWindow> OwningWindow;`
- L62 _protected member_ `TAtomic<bool> bIsEngineLoadingFinished;`
- L67 _private member_ `FString PluginName;` — The name of the Plugin creating this FPreLoadScreenBase. Important: Should be set before Initting settings from Config!

### `Source/Runtime/PreLoadScreen/Public/PreLoadScreenManager.h` (Public)


#### class `FPreLoadScreenManager`  
`class FPreLoadScreenManager`  
_L20-162_
- desc: Class that handles storing all registered PreLoadScreens and Playing/Stopping them
- L24 _public prototype_ `static FPreLoadScreenManager* Get();` — Gets the single instance of this settings object. Also creates it if needed
- L25 _public prototype_ `static void Create();`
- L26 _public prototype_ `static void Destroy();`
- L28 _public prototype_ `void Initialize(FSlateRenderer& InSlateRenderer);`
- L30 _public prototype_ `void RegisterPreLoadScreen(const TSharedPtr<IPreLoadScreen>& PreLoadScreen);`
- L31 _public prototype_ `void UnRegisterPreLoadScreen(const TSharedPtr<IPreLoadScreen>& PreLoadScreen);`
- L37 _public prototype_ `bool PlayFirstPreLoadScreen(EPreLoadScreenTypes PreLoadScreenTypeToPlay);` — Plays the first found PreLoadScreen that matches the bEarlyPreLoadScreen setting passed in. @returns false if no PreLoadScreen with that type has been registered.
- L43 _public prototype_ `bool PlayPreLoadScreenWithTag(FName InTag);` — Plays the PreLoadScreen with a tag that matches InTag @returns false if no PreLoadScreen with that tag has been registered.
- L45 _public prototype_ `void StopPreLoadScreen();`
- L46 _public prototype_ `void WaitForEngineLoadingScreenToFinish();`
- L48 _public prototype_ `void PassPreLoadScreenWindowBackToGame() const;`
- L50 _public prototype_ `bool IsUsingMainWindow() const;`
- L52 _public prototype_ `TSharedPtr<SWindow> GetRenderWindow();`
- L54 _public prototype_ `bool HasRegisteredPreLoadScreenType(EPreLoadScreenTypes PreLoadScreenTypeToCheck) const;`
- L55 _public prototype_ `bool HasActivePreLoadScreenType(EPreLoadScreenTypes PreLoadScreenTypeToCheck) const;`
- L56 _public prototype_ `bool HasValidActivePreLoadScreen() const;`
- L59 _public prototype_ `void SetEngineLoadingComplete(bool IsEngineLoadingFinished = true);`
- L60 _public function_ `bool IsEngineLoadingComplete() const`
- L62 _public prototype_ `static void EnableRendering(bool bEnabled);`
- L63 _public prototype_ `static bool ArePreLoadScreensEnabled();`
- L67 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPreLoadScreenManagerCleanUp);` — Callback for handling cleaning up any resources you would like to remove after the PreLoadScreenManager cleans up Not needed for PreLoadScreens as those have a separate CleanUp method called.
- L68 _public member_ `FOnPreLoadScreenManagerCleanUp OnPreLoadScreenManagerCleanUp;`
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FIsPreloadScreenResponsibleForRenderingMultiDelegate, bool);`
- L71 _public member_ `FIsPreloadScreenResponsibleForRenderingMultiDelegate IsResponsibleForRenderingDelegate;`
- L75 _protected prototype_ `FPreLoadScreenManager();` — Default constructor. We don't want other classes to make these. Should just rely on Get()
- L77 _protected prototype_ `~FPreLoadScreenManager() = default;`
- L79 _protected prototype_ `void PlayPreLoadScreenAtIndex(int32 Index);`
- L81 _protected prototype_ `void BeginPlay();`
- L84 _protected prototype_ `void HandleEarlyStartupPlay();` — These functions describe the flow for an EarlyPreLoadScreen where everything is blocking waiting on a call to StopPreLoadScreen
- L86 _protected prototype_ `void EarlyPlayFrameTick();` — Separate tick that handles
- L87 _protected prototype_ `void GameLogicFrameTick();`
- L88 _protected prototype_ `void EarlyPlayRenderFrameTick();`
- L89 _protected prototype_ `bool HasActivePreLoadScreenTypeForEarlyStartup() const;`
- L91 _protected prototype_ `void PlatformSpecificGameLogicFrameTick();`
- L94 _protected prototype_ `static void StaticRenderTick_RenderThread(FRHICommandListImmediate& RHICmdList);` — Creates a tick on the Render Thread that we run every
- L95 _protected prototype_ `void RenderTick_RenderThread(FRHICommandListImmediate& RHICmdList);`
- L98 _protected prototype_ `void HandleEngineLoadingPlay();` — These functions describe how everything is handled during an non-Early PreLoadPlay. Everything is handled asynchronously in this case with a standalone renderer
- L101 _protected prototype_ `void HandleCustomSplashScreenPlay();` — These functions describe the flow for showing an CustomSplashScreen
- L103 _protected prototype_ `IPreLoadScreen* GetActivePreLoadScreen();`
- L104 _protected prototype_ `const IPreLoadScreen* GetActivePreLoadScreen() const;`
- L106 _protected prototype_ `void HandleStopPreLoadScreen();`
- L107 _protected prototype_ `void CleanUpResources();`
- L109 _protected prototype_ `static void OnRequestExit();`
- L119 _protected member_ `static TUniquePtr<FPreLoadScreenManager, FPreLoadScreenManagerDelete> Instance;`
- L121 _protected member_ `static std::atomic<bool> bRenderingEnabled;`
- L123 _protected member_ `static FCriticalSection ActivePreloadScreenCriticalSection;`
- L124 _protected member_ `static TWeakPtr<IPreLoadScreen> ActivePreloadScreen;`
- L126 _protected member_ `TArray<TSharedPtr<IPreLoadScreen>> PreLoadScreens;`
- L128 _protected member_ `int32 ActivePreLoadScreenIndex;`
- L129 _protected member_ `double LastTickTime;`
- L132 _protected member_ `TSharedPtr<FPreLoadSlateWidgetRenderer> WidgetRenderer;` — Widget renderer used to tick and paint windows in a thread safe way
- L135 _protected member_ `TWeakPtr<class SWindow> MainWindow;` — The window that the loading screen resides in
- L138 _protected member_ `TSharedPtr<class SVirtualWindow> VirtualRenderWindow;` — Virtual window that we render to instead of the main slate window (for thread safety).  Shares only the same backbuffer as the main window
- L140 _protected member_ `bool bInitialized;`
- L143 _protected member_ `FPreLoadScreenSlateSynchMechanism* SyncMechanism;` — The threading mechanism with which we handle running slate on another thread
- L146 _protected member_ `bool bIsResponsibleForRendering;`
- L147 _protected member_ `bool bHasRenderPreLoadScreenFrame_RenderThread;`
- L149 _protected member_ `double LastRenderTickTime;`
- L151 _protected member_ `float OriginalSlateSleepVariableValue;`
- L152 _protected member_ `bool bIsEngineLoadingComplete;`
- L156 _private prototype_ `void Android_PlatformSpecificGameLogicFrameTick();`
- L160 _private prototype_ `void IOS_PlatformSpecificGameLogicFrameTick();`

#### struct `FPreLoadScreenManager::FPreLoadScreenManagerDelete`  
`struct FPreLoadScreenManagerDelete`  
_L112-118_
- desc: Singleton Instance
- L114 _public function_ `void operator()(FPreLoadScreenManager* Ptr) const`

#### Free symbols / members of external scopes

- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPreLoadScreenManagerCleanUp);` — Callback for handling cleaning up any resources you would like to remove after the PreLoadScreenManager cleans up Not needed for PreLoadScreens as those have a separate CleanUp method called.
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FIsPreloadScreenResponsibleForRenderingMultiDelegate, bool);`

### `Source/Runtime/PreLoadScreen/Public/PreLoadSettingsContainer.h` (Public)


#### class `FPreLoadSettingsContainerBase`  
`class FPreLoadSettingsContainerBase : public FDeferredCleanupInterface, public FGCObject`  
_L16-202_
- inherits: `FDeferredCleanupInterface,FGCObject`
- desc: This is a helper class that we use to hold values we parse from the .ini. Clean way to access things like dynamic image brushes / fonts / etc used in our UI that we want to be somewhat data driven but we can't rely on UObject support to implement(as the PreLoad stuff happens too early for UObject support) This lets us set easy to change values in our .ini that are parsed at runtime and stored in this container
- L74 _public function_ `static FPreLoadSettingsContainerBase& Get()`
- L84 _public function_ `static void Destroy()`
- L95 _private function_ `FPreLoadSettingsContainerBase() : CurrentLoadGroup(NAME_None)`
- L102 _private prototype_ `virtual ~FPreLoadSettingsContainerBase();`
- L107 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L108 _public function_ `virtual FString GetReferencerName() const override`
- L111 _public prototype_ `virtual const FSlateDynamicImageBrush* GetBrush(const FString& Identifier);`
- L112 _public prototype_ `virtual FText GetLocalizedText(const FString& Identifier);`
- L113 _public prototype_ `virtual TSharedPtr<FCompositeFont> GetFont(const FString& Identifier);`
- L114 _public prototype_ `virtual FScreenGroupingBase* GetScreenGrouping(const FString& Identifier);`
- L116 _public function_ `int GetNumScreenGroupings() const`
- L118 _public prototype_ `virtual const FScreenGroupingBase* GetScreenAtIndex(int index) const;`
- L119 _public prototype_ `virtual bool IsValidScreenIndex(int index) const;`
- L121 _public prototype_ `virtual void CreateCustomSlateImageBrush(const FString& Identifier, const FString& TexturePath, const FVector2D& ImageDimensions);`
- L122 _public prototype_ `virtual void AddLocalizedText(const FString& Identifier, FText LocalizedText);`
- L123 _public prototype_ `virtual void AddScreenGrouping(const FString& Identifier, FScreenGroupingBase& ScreenGrouping);`
- L127 _public prototype_ `virtual void BuildCustomFont(const FString& FontIdentifier, const FString& Language, const FString& FilePath);` — Maps the given font file to the given language and stores it under the FontIdentifier. Identifier maps the entire CompositeFont, so if you want to add multiple fonts  for multiple languages, just store them all under the same identifer
- L128 _public prototype_ `virtual bool BuildSystemFontFile();`
- L129 _public prototype_ `virtual const FString GetSystemFontFilePath() const;`
- L132 _public prototype_ `virtual void ParseBrushConfigEntry(const FString& BrushConfigEntry);` — Helper functions that parse a .ini config entry and call the appropriate create function to
- L133 _public prototype_ `virtual void ParseFontConfigEntry(const FString& SplitConfigEntry);`
- L134 _public prototype_ `virtual void ParseLocalizedTextConfigString(const FString& SplitConfigEntry);`
- L135 _public prototype_ `virtual void ParseScreenGroupingConfigString(const FString& SplitConfigEntry);`
- L139 _public prototype_ `virtual void ParseLoadingGroups(TArray<FString>& LoadingGroupIdentifiers);` — Helper function to parse all .ini entries for LoadingGroups and ScreenOrder. Do these together so we can assert if we don't find a matching LoadingGroup identifier in the config. Should be run after we parse all screen groupings
- L140 _public prototype_ `virtual void ParseAllScreenOrderEntries(TArray<FString>& LoadingGroups, TArray<FString>& ScreenOrderEntries);`
- L141 _public prototype_ `virtual void ParseScreenOrderConfigString(const FString& ScreenOrderEntry);`
- L144 _public function_ `virtual void SetPluginContentDir(const FString& PluginContentDirIn)` — Sets the PluginContent dir so that when parsing config entries we can accept plugin relative file paths
- L147 _public prototype_ `virtual void SetShouldLoadBrushes(bool bInShouldLoadBrushes);` — Tells the container rather it should actually load image brushes
- L149 _public member_ `float TimeToDisplayEachBackground;`
- L150 _public member_ `float TimeToUpdateDownloadedDataSize;`
- L151 _public member_ `float TimeToRecheckNotificationsPermission;`
- L152 _public member_ `float TimeToShowNotificationsPermissionModal;`
- L154 _public function_ `FName GetCurrentLoadGrouping() const`
- L155 _public prototype_ `void LoadGrouping(FName Identifier);`
- L156 _public prototype_ `void PerformInitialAssetLoad();`
- L160 _public prototype_ `virtual FString ConvertIfPluginRelativeContentPath(const FString& FilePath);` — Helper function that takes in a file path and tries to reconsile it to be Plugin Specific if applicable. Ensures if file is not found in either Plugin's content dir or the original path
- L165 _protected prototype_ `virtual bool IsValidBrushConfig(TArray<FString>& SplitConfigEntry);` — Helper functions that verify if the supplied .ini config entry is valid to create a resource out of it
- L166 _protected prototype_ `virtual bool IsValidFontConfigString(TArray<FString>& SplitConfigEntry);`
- L167 _protected prototype_ `virtual bool IsValidLocalizedTextConfigString(TArray<FString>& SplitConfigEntry);`
- L168 _protected prototype_ `virtual bool IsValidScreenGrooupingConfigString(TArray<FString>& SplitConfigEntry);`
- L171 _protected member_ `TArray<FString> ParsedLoadingGroupIdentifiers;`
- L174 _protected member_ `TMap<FName, FSlateDynamicImageBrush*> BrushResources;` — Property Storage. Ties FName to a particular resource so we can get it by identifier.
- L175 _protected member_ `TMap<FName, FText> LocalizedTextResources;`
- L176 _protected member_ `TMap<FName, TSharedPtr<FStandaloneCompositeFont>> FontResources;`
- L178 _protected member_ `TMap<FName, FScreenOrderByLoadingGroup> ScreenOrderByLoadingGroups;`
- L179 _protected member_ `TMap<FName, FScreenGroupingBase> ScreenGroupings;`
- L181 _protected member_ `TMap<FName, FCustomBrushLoadingGroup> BrushLoadingGroups;`
- L184 _protected member_ `FString PluginContentDir;` — This string is used to make file paths relative to a particular Plugin's content directory when parsing file paths.
- L187 _protected member_ `bool bShouldLoadBrushes;` — Rather we should load image brushes
- L189 _protected member_ `FName CurrentLoadGroup;`
- L191 _protected member_ `bool HasCreatedSystemFontFile;`
- L194 _protected member_ `static FString UseSystemFontOverride;` — If our Font filepath is set to this, we use the system font instead of a custom font we load in
- L197 _protected member_ `static FString DefaultInitialLoadingGroupIdentifier;` — If we supply no loading groups, use this identifier by default
- L201 _protected member_ `static FPreLoadSettingsContainerBase* Instance;` — Singleton Instance -- This is only not a TSharedPtr as it needs to be cleaned up by a deferredcleanup call which directly destroys the underlying object, causing a SharedPtr crash at shutdown.

#### struct `FPreLoadSettingsContainerBase::FScreenGroupingBase`  
`struct FScreenGroupingBase`  
_L22-35_
- desc: Helper struct to store groups of things we want to display together in the UI so that we can parse it easily in the .ini. IE: Show this background, with this text at this font size
- L26 _public member_ `FString ScreenBackgroundIdentifer;`
- L27 _public member_ `FString TextIdentifier;`
- L28 _public member_ `float FontSize;`
- L30 _public function_ `FScreenGroupingBase(const FString& ScreenBackgroundIdentifierIn, const FString& TextIdentifierIn, float FontSizeIn) : ScreenBackgroundIdentifer(ScreenBackgroundIdentifierIn) , TextIdentifier(TextIdentifierIn) , FontSize(FontSizeIn)`

#### struct `FPreLoadSettingsContainerBase::FScreenOrderByLoadingGroup`  
`struct FScreenOrderByLoadingGroup`  
_L40-48_
- desc: This is a listing of ScreenGroupings (stored by Identifier) that should be displayed in this order during a particular LoadingGroup. @TODO: TRoss, possible to move these loading groups into their own DeferreedCleanupInterface instead of the entire container being the DeferredCleanupInterface, if we want to support unloading them. For right now though, we mostly just care about loading them selectively and are ok with keeping them in memory until we clean everything up.
- L43 _public member_ `TArray<FName> ScreenGroupings;`
- L45 _public function_ `FScreenOrderByLoadingGroup() : ScreenGroupings ()`

#### struct `FPreLoadSettingsContainerBase::FCustomBrushDefine`  
`struct FCustomBrushDefine`  
_L51-63_
- desc: Helper struct  to store information required to construct a CustomSlateImageBrush. Parsed from our .ini
- L54 _public member_ `FString BrushIdentifier;`
- L55 _public member_ `FString FilePath;`
- L56 _public member_ `FVector2D Size;`
- L58 _public function_ `FCustomBrushDefine(const FString& BrushIdentifierIn, const FString& FilePathIn, FVector2D SizeIn) : BrushIdentifier(BrushIdentifierIn) , FilePath(FilePathIn) , Size(SizeIn)`

#### struct `FPreLoadSettingsContainerBase::FCustomBrushLoadingGroup`  
`struct FCustomBrushLoadingGroup`  
_L66-70_
- desc: Helper struct to store all BrushDefines we need to load for a given BrushLoadingGroup
- L69 _public member_ `TArray<FCustomBrushDefine> CustomBrushDefinesToLoad;`

### `Source/Runtime/PreLoadScreen/Public/PreLoadSlateThreading.h` (Public)


#### class `FPreLoadScreenSlateThreadTask`  
`class FPreLoadScreenSlateThreadTask : public FRunnable`  
_L29-46_
- inherits: `FRunnable`
- desc: The Slate thread is simply run on a worker thread. Slate is run on another thread because the game thread (where Slate is usually run) is blocked loading things. Slate is very modular, which makes it very easy to run on another thread with no adverse effects. It does not enqueue render commands, because the RHI is not thread safe. Thus, it waits to enqueue render commands until the render thread tickables ticks, and then it calls them there.
- L32 _public function_ `FPreLoadScreenSlateThreadTask(class FPreLoadScreenSlateSynchMechanism& InSyncMechanism) : SyncMechanism(&InSyncMechanism)`
- L38 _public prototype_ `virtual bool Init() override;`
- L39 _public prototype_ `virtual uint32 Run() override;`
- L40 _public prototype_ `virtual void Exit() override;`
- L45 _private member_ `class FPreLoadScreenSlateSynchMechanism* SyncMechanism;` — Hold a handle to our parent sync mechanism which handles all of our threading locks

#### class `FPreLoadSlateWidgetRenderer`  
`class FPreLoadSlateWidgetRenderer`  
_L48-70_
- L51 _public prototype_ `FPreLoadSlateWidgetRenderer(TSharedPtr<SWindow> InMainWindow, TSharedPtr<SVirtualWindow> InVirtualRenderWindowWindow, FSlateRenderer* InRenderer);`
- L53 _public prototype_ `void DrawWindow(float DeltaTime);`
- L55 _public function_ `SWindow* GetMainWindow_GameThread() const`
- L60 _private member_ `SWindow* MainWindow;` — Note: This is raw as we SWindows registered with SlateApplication are not thread safe
- L63 _private member_ `TSharedRef<SVirtualWindow> VirtualRenderWindow;` — Virtual window that we render to instead of the main slate window (for thread safety).  Shares only the same backbuffer as the main window
- L65 _private member_ `TSharedPtr<FHittestGrid> HittestGrid;`
- L67 _private member_ `FSlateRenderer* SlateRenderer;`
- L69 _private member_ `FViewportRHIRef ViewportRHI;`

#### class `FPreLoadScreenSlateSynchMechanism`  
`class FPreLoadScreenSlateSynchMechanism`  
_L77-117_
- desc: This class will handle all the nasty bits about running Slate on a separate thread and then trying to sync it up with the game thread and the render thread simultaneously
- L80 _public prototype_ `FPreLoadScreenSlateSynchMechanism(TSharedPtr<FPreLoadSlateWidgetRenderer, ESPMode::ThreadSafe> InWidgetRenderer);`
- L81 _public prototype_ `~FPreLoadScreenSlateSynchMechanism();`
- L83 _public prototype_ `FPreLoadScreenSlateSynchMechanism() = delete;`
- L84 _public prototype_ `FPreLoadScreenSlateSynchMechanism(const FPreLoadScreenSlateSynchMechanism&) = delete;`
- L85 _public prototype_ `FPreLoadScreenSlateSynchMechanism& operator=(const FPreLoadScreenSlateSynchMechanism&) = delete;`
- L88 _public prototype_ `void Initialize();` — Sets up the locks in their proper initial state for running
- L91 _public prototype_ `void DestroySlateThread();` — Cleans up the slate thread
- L94 _public prototype_ `bool IsSlateMainLoopRunning_AnyThread() const;` — Handles the counter to determine if the slate thread should keep running
- L98 _private prototype_ `void HandleWindowBeingDestroyed(const SWindow& WindowBeingDestroyed);` — Notified when a SWindow is being destroyed
- L101 _private prototype_ `void RunMainLoop_SlateThread();` — The main loop to be run from the Slate thread
- L104 _private member_ `TAtomic<bool> bIsRunningSlateMainLoop;` — This counter handles running the main loop of the slate thread
- L107 _private member_ `static TAtomic<int32> LoadingThreadInstanceCounter;` — This counter is used to generate a unique id for each new instance of the loading thread
- L110 _private member_ `FRunnableThread* SlateLoadingThread;` — The worker thread that will become the Slate thread
- L111 _private member_ `FRunnable* SlateRunnableTask;`
- L112 _private member_ `FEvent* SleepEvent;`
- L114 _private member_ `TSharedPtr<FPreLoadSlateWidgetRenderer, ESPMode::ThreadSafe> WidgetRenderer;`

### `Source/Runtime/PreLoadScreen/Public/SimplePreLoadScreenWidget.h` (Public)


#### class `SSimplePreLoadScreenWidget`  
`class SSimplePreLoadScreenWidget : public SCompoundWidget`  
_L20-50_
- inherits: `SCompoundWidget`
- desc: Widget that displays a very simple version of a FPreLoadScreen UI that just includes a background and localized text together. Rotates through the PreLoadScreens in the same order they are in the FPreLoadSettingsContainerBase. Uses the TimeToDisplayEachBackground variable to determine how long to display each screen before rotating. Loops back when finished.
- L23 _public function_ `SLATE_BEGIN_ARGS(SSimplePreLoadScreenWidget)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Handles updating the background every X seconds
- L33 _private prototype_ `virtual void UpdateBackgroundImage();` — Loops to the next background image
- L36 _private function_ `virtual float GetDPIScale() const` — Not used in the default simple implementation
- L38 _private prototype_ `const FSlateBrush* GetCurrentBackgroundImage() const;`
- L39 _private prototype_ `FText GetCurrentScreenText() const;`
- L40 _private prototype_ `FSlateFontInfo GetTextFont() const;`
- L41 _private prototype_ `FSlateFontInfo GetFontInfo(const FString& FontName, float FontSize) const;`
- L43 _private member_ `int CurrentPreLoadScreenIndex;`
- L44 _private member_ `float TimeToDisplayEachBackground;`
- L45 _private member_ `float TimeSinceLastBackgroundUpdate;`
- L47 _private member_ `static FCriticalSection BackgroundImageCrit;`
- L48 _private member_ `static int CurrentBackgroundImage;`
