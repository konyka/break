# Plugins / RenderDocPlugin

- module root: `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin`
- headers: 9; symbols: 99
- symbol kinds: class=9, delegate=1, function=10, macro=1, member=32, prototype=45, typedef=1
- DynamicallyLoadedModuleNames: LevelEditor
- PublicDependencyModuleNames: Core, CoreUObject, DesktopPlatform, DeveloperSettings, EditorFramework, Engine, GameProjectGeneration, InputCore, InputDevice, MainFrame, Projects, RHI, RenderCore, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Private/RenderDocPluginCommands.h` (Private)


#### class `FRenderDocPluginCommands`  
`class FRenderDocPluginCommands : public TCommands<FRenderDocPluginCommands>`  
_L10-21_
- inherits: `TCommands<FRenderDocPluginCommands>`
- L13 _public function_ `FRenderDocPluginCommands() : TCommands<FRenderDocPluginCommands>(TEXT("RenderDocPlugin"), NSLOCTEXT("Contexts", "RenderDocPlugin", "RenderDoc Plugin"), NAME_None, FRenderDocPluginStyle::Get()->GetStyleSetName())`
- L18 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<class FUICommandInfo> CaptureFrame;`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Private/RenderDocPluginLoader.h` (Private)


#### class `FRenderDocPluginLoader`  
`class FRenderDocPluginLoader`  
_L7-24_
- L10 _public prototype_ `void Initialize();`
- L11 _public prototype_ `void Release();`
- L13 _public typedef_ `typedef RENDERDOC_API_1_0_0 RENDERDOC_API_CONTEXT;`
- L16 _public prototype_ `static void* GetRenderDocLibrary();`
- L22 _private member_ `void* RenderDocDLL;`
- L23 _private member_ `RENDERDOC_API_CONTEXT* RenderDocAPI;`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Private/RenderDocPluginModule.h` (Private)


#### class `FRenderDocPluginModule`  
`class FRenderDocPluginModule : public IRenderDocPlugin`  
_L13-86_
- inherits: `IRenderDocPlugin`
- L20 _public function_ `virtual bool CanSupportSubmissionThread() const`
- L21 _public prototype_ `virtual void CaptureFrame(FViewport* InViewport, uint32 InFlags, FString const& InDestFileName) override;`
- L22 _public prototype_ `virtual void BeginCapture(FRHICommandListImmediate* InRHICommandList, uint32 InFlags, FString const& InDestFileName) override;`
- L23 _public prototype_ `virtual void EndCapture(FRHICommandListImmediate* InRHICommandList) override;`
- L28 _protected prototype_ `virtual void StartupModule() override;`
- L29 _protected prototype_ `virtual void ShutdownModule() override;`
- L33 _protected prototype_ `virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L37 _private prototype_ `void Tick(float DeltaTime);`
- L40 _private prototype_ `void InjectDebugExecKeybind();` — Injects a debug key bind into the local player so that the hot key works the same in game
- L43 _private prototype_ `void CaptureFrame();` — Helper function for CVar command binding.
- L46 _private prototype_ `void OnMainFrameCreationFinished(TSharedPtr<SWindow> ParentWindow, bool bIsRunningStartupDialog);`
- L47 _private prototype_ `void CapturePIE(const TArray<FString>& Args);`
- L50 _private prototype_ `void OnPostEngineInit();`
- L52 _private prototype_ `void DoFrameCaptureCurrentViewport(FViewport* InViewport, uint32 InFlags, FString const& InDestFileName);`
- L54 _private prototype_ `void BeginFrameCapture();`
- L55 _private prototype_ `void EndFrameCapture(void* HWnd, uint32 Flags, FString const& DestFileName);`
- L57 _private prototype_ `void BeginCapture_RenderThread(FRHICommandListImmediate* InRHICommandList);`
- L58 _private prototype_ `void EndCapture_RenderThread(FRHICommandListImmediate* InRHICommandList, uint32 InFlags, FString const& InDestFileName);`
- L60 _private prototype_ `bool ShouldCaptureAllActivity() const;`
- L61 _private prototype_ `FString GetNewestCapture();`
- L62 _private prototype_ `void ShowNotification(const FText& Message, bool bForceNewNotification);`
- L63 _private prototype_ `void StartRenderDoc(FString CapturePath);`
- L66 _private member_ `FRenderDocPluginLoader Loader;`
- L67 _private member_ `FRenderDocPluginLoader::RENDERDOC_API_CONTEXT* RenderDocAPI;`
- L69 _private member_ `void* MainWindowHandle = nullptr;` — Keep a handle of the main window so that programmatic captures (i.e. BeginCapture_RenderThread / EndCapture_RenderThread) can still pass a valid window handle to RenderDoc
- L70 _private member_ `uint64 DelayedCaptureTick;` — Tracks on which frame a delayed capture should trigger, if any (when bCaptureDelayInSeconds == false)
- L71 _private member_ `double DelayedCaptureSeconds;` — Tracks at which time a delayed capture should trigger, if any (when bCaptureDelayInSeconds == true)
- L72 _private member_ `uint64 CaptureFrameCount;` — Tracks how many frames should be captured
- L73 _private member_ `uint64 CaptureEndTick;` — Tracks the tick at which the capture currently in progress should end
- L74 _private member_ `bool bCaptureDelayInSeconds:1;` — Is the capture delay in seconds or ticks?
- L75 _private member_ `bool bShouldCaptureAllActivity : 1;` — true if all the whole frame should be captured, not just the active viewport
- L76 _private member_ `bool bPendingCapture : 1;` — true when a delayed capture has been triggered but hasn't started yet
- L77 _private member_ `bool bCaptureInProgress:1;` — true after BeginCapture() has been called and we're waiting for the end of the capture
- L79 _private member_ `uint32 CaptureFlags;` — Store the capture flags that are known at BeginCapture() for use at EndCapture()
- L80 _private member_ `FString CaptureFileName;` — Store the capture file name that is known at BeginCapture() for use at EndCapture()
- L83 _private member_ `TSharedPtr<FRenderDocPluginEditorExtension> EditorExtension;`
- L84 _private member_ `int StartPIEDelayFrames = -1;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(RenderDocPlugin, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(RenderDocPlugin, Log, All);`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Private/RenderDocPluginNotification.h` (Private)


#### class `FRenderDocPluginNotification`  
`class FRenderDocPluginNotification : public FTickableGameObject`  
_L10-38_
- inherits: `FTickableGameObject`
- L13 _public function_ `static FRenderDocPluginNotification& Get()`
- L19 _public prototype_ `void ShowNotification(const FText& Message, bool bForceNewNotification);`
- L20 _public prototype_ `void HideNotification();`
- L24 _protected prototype_ `virtual void Tick(float DeltaTime);` — FTickableGameObject interface
- L25 _protected function_ `virtual ETickableTickType GetTickableTickType() const`
- L26 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L27 _protected function_ `virtual bool IsTickableWhenPaused() const override`
- L28 _protected function_ `virtual bool IsTickableInEditor() const override`
- L31 _private prototype_ `FRenderDocPluginNotification();`
- L32 _private prototype_ `FRenderDocPluginNotification(FRenderDocPluginNotification const& Notification);`
- L33 _private prototype_ `void operator=(FRenderDocPluginNotification const&);`
- L36 _private member_ `TWeakPtr<SNotificationItem> RenderDocNotificationPtr;` — The source code symbol query in progress message
- L37 _private member_ `double LastEnableTime;`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Private/RenderDocPluginStyle.h` (Private)


#### class `FRenderDocPluginStyle`  
`class FRenderDocPluginStyle`  
_L9-21_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L17 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L20 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Private/SRenderDocPluginEditorExtension.h` (Private)


#### class `FRenderDocPluginEditorExtension`  
`class FRenderDocPluginEditorExtension`  
_L15-23_
- L18 _public prototype_ `FRenderDocPluginEditorExtension(FRenderDocPluginModule* ThePlugin);`
- L19 _public prototype_ `~FRenderDocPluginEditorExtension();`
- L22 _private prototype_ `void Initialize(FRenderDocPluginModule* ThePlugin);`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Private/SRenderDocPluginHelpWindow.h` (Private)


#### class `SRenderDocPluginHelpWindow`  
`class SRenderDocPluginHelpWindow : public SWindow`  
_L9-24_
- inherits: `SWindow`
- L12 _public function_ `SLATE_BEGIN_ARGS(SRenderDocPluginHelpWindow)`
- L17 _public function_ `SRenderDocPluginHelpWindow()`
- L20 _public prototype_ `void Construct(const FArguments& Args);` — Widget constructor
- L23 _private prototype_ `FReply Close();`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Public/IRenderDocPlugin.h` (Public)


#### class `IRenderDocPlugin`  
`class IRenderDocPlugin : public IInputDeviceModule, public IRenderCaptureProvider`  
_L16-28_
- inherits: `IInputDeviceModule,IRenderCaptureProvider`
- desc: The RenderDoc plugin works as an input plugin. Regular plugins built upon IModuleInterface lack the ability of ticking, while IInputDeviceModule instantiates and manages an IInputDevice object that is capable of ticking. By responding to tick events, the RenderDoc plugin is able to intercept the entire frame activity, including Editor (Slate) UI rendering and SceneCapture updates.
- L19 _public function_ `static inline IRenderDocPlugin& Get()`
- L24 _public function_ `static inline bool IsAvailable()`

### `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Public/RenderDocPluginSettings.h` (Public)


#### class `URenderDocPluginSettings`  
`class URenderDocPluginSettings : public UDeveloperSettings`  
_L11-91_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta = (DisplayName = "RenderDoc"))`
- inherits: `UDeveloperSettings`
- L20 _public member_ `uint32 bCaptureAllActivity : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Capture Settings", meta = ( ConsoleVariable = "renderdoc.CaptureAllActivity", DisplayName = "Capture all activity", ToolTip = "If checked, RenderDoc will capture all activity in all viewports and editor windows for the entire frame instead of only the current viewport.", ConfigRestartRequired = false))`
- L26 _public member_ `uint32 bCaptureAllCallstacks : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Capture Settings", meta = ( ConsoleVariable = "renderdoc.CaptureCallstacks", DisplayName = "Capture all call stacks", ToolTip = "If checked, RenderDoc will capture callstacks for all API calls.", ConfigRestartRequired = false))`
- L32 _public member_ `uint32 bReferenceAllResources : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Capture Settings", meta = ( ConsoleVariable = "renderdoc.ReferenceAllResources", DisplayName = "Reference all resources", ToolTip = "If checked, RenderDoc will include all rendering resources in the capture, even those that have not been used during the frame. Please note that doing this will significantly increase capture size.", ConfigRestartRequired = false))`
- L38 _public member_ `uint32 bSaveAllInitials : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Capture Settings", meta = ( ConsoleVariable = "renderdoc.SaveAllInitials", DisplayName = "Save all initial states", ToolTip = "If checked, RenderDoc will always capture the initial state of all rendering resources even if they are not likely to be used during the frame. Please note that doing this will significantly increase capture size.", ConfigRestartRequired = false))`
- L44 _public member_ `uint32 bCaptureDelayInSeconds : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Capture Settings", meta = ( ConsoleVariable = "renderdoc.CaptureDelayInSeconds", DisplayName = "Capture delay in seconds", ToolTip = "If checked, the capture delay's unit will be in seconds instead of frames.", ConfigRestartRequired = false))`
- L51 _public member_ `int32 CaptureDelay;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Capture Settings", meta = ( ConsoleVariable = "renderdoc.CaptureDelay", DisplayName = "Capture delay", ToolTip = "If > 0, RenderDoc will trigger the capture only after this amount of frames/seconds has passed.", ClampMin = 0, ConfigRestartRequired = false))`
- L58 _public member_ `int32 CaptureFrameCount;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Capture Settings", meta = ( ConsoleVariable = "renderdoc.CaptureFrameCount", DisplayName = "Capture frame count", ToolTip = "If > 1, the RenderDoc capture will encompass more than a single frame. Note: this implies that all activity in all viewports and editor windows will be captured (i.e. same as CaptureAllActivity)", ClampMin = 1, ConfigRestartRequired = false))`
- L64 _public member_ `uint32 bAutoAttach : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Settings", meta = ( ConsoleVariable = "renderdoc.AutoAttach", DisplayName = "Auto attach on startup", ToolTip = "If checked, then RenderDoc will attach on startup. Otherwise the command line argument '-AttachRenderDoc' is required." ))`
- L70 _public member_ `uint32 bShowHelpOnStartup : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Settings", meta = ( ConsoleVariable = "renderdoc.ShowHelpOnStartup", DisplayName = "Show help on startup", ToolTip = "If checked, a help window will be shown on startup.", ConfigRestartRequired = true))`
- L76 _public member_ `uint32 bEnableRenderDocCrashHandler : 1;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Settings", meta = ( ConsoleVariable = "renderdoc.EnableCrashHandler", DisplayName = "Use the RenderDoc crash handler", ToolTip = "If checked, the RenderDoc crash handler will be used if a crash occurs (Only use this if you know the problem is with RenderDoc and you want to notify the RenderDoc developers!).", ConfigRestartRequired = true))`
- L82 _public member_ `FString RenderDocBinaryPath;` — `UPROPERTY(config, EditAnywhere, Category = "Advanced Settings", meta = ( ConsoleVariable = "renderdoc.BinaryPath", DisplayName = "RenderDoc executable path", ToolTip = "Path to the main RenderDoc executable to use.", ConfigRestartRequired = true))`
- L85 _public prototype_ `virtual void PostInitProperties() override;`
- L86 _public prototype_ `virtual FName GetCategoryName() const;`
- L89 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RENDERDOCPLUGIN_API`
