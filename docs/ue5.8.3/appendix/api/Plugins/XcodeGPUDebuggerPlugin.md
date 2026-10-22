# Plugins / XcodeGPUDebuggerPlugin

- module root: `Plugins/Developer/XcodeGPUDebuggerPlugin/Source/XcodeGPUDebuggerPlugin`
- headers: 5; symbols: 40
- symbol kinds: class=5, delegate=1, function=3, member=8, prototype=23
- DynamicallyLoadedModuleNames: LevelEditor
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, DesktopPlatform, DeveloperSettings, Engine, GameProjectGeneration, InputCore, InputDevice, MainFrame, MetalRHI, Projects, RHI, RenderCore, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Developer/XcodeGPUDebuggerPlugin/Source/XcodeGPUDebuggerPlugin/Private/SXcodeGPUDebuggerPluginEditorExtension.h` (Private)


#### class `FXcodeGPUDebuggerPluginEditorExtension`  
`class FXcodeGPUDebuggerPluginEditorExtension`  
_L15-27_
- L18 _public prototype_ `FXcodeGPUDebuggerPluginEditorExtension(FXcodeGPUDebuggerPluginModule* ThePlugin);`
- L19 _public prototype_ `~FXcodeGPUDebuggerPluginEditorExtension();`
- L22 _private prototype_ `void Initialize(FXcodeGPUDebuggerPluginModule* ThePlugin);`
- L23 _private prototype_ `void OnEditorLoaded(SWindow& SlateWindow);`
- L25 _private member_ `FDelegateHandle LoadedDelegateHandle;`
- L26 _private member_ `bool IsEditorInitialized;`

### `Plugins/Developer/XcodeGPUDebuggerPlugin/Source/XcodeGPUDebuggerPlugin/Private/XcodeGPUDebuggerPluginCommands.h` (Private)


#### class `FXcodeGPUDebuggerPluginCommands`  
`class FXcodeGPUDebuggerPluginCommands : public TCommands<FXcodeGPUDebuggerPluginCommands>`  
_L10-21_
- inherits: `TCommands<FXcodeGPUDebuggerPluginCommands>`
- L13 _public function_ `FXcodeGPUDebuggerPluginCommands() : TCommands<FXcodeGPUDebuggerPluginCommands>(TEXT("XcodeGPUDebuggerPlugin"), NSLOCTEXT("Contexts", "XcodeGPUDebuggerPlugin", "XcodeGPUDebugger Plugin"), NAME_None, FXcodeGPUDebuggerPluginStyle::Get()->GetStyleSetName())`
- L18 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<class FUICommandInfo> CaptureFrame;`

### `Plugins/Developer/XcodeGPUDebuggerPlugin/Source/XcodeGPUDebuggerPlugin/Private/XcodeGPUDebuggerPluginModule.h` (Private)


#### class `FXcodeGPUDebuggerPluginModule`  
`class FXcodeGPUDebuggerPluginModule : public IXcodeGPUDebuggerPlugin`  
_L11-58_
- inherits: `IXcodeGPUDebuggerPlugin`
- L18 _public prototype_ `virtual void CaptureFrame(FViewport* InViewport, uint32 InFlags, FString const& InDestFileName) override;`
- L19 _public prototype_ `virtual void BeginCapture(FRHICommandListImmediate* InRHICommandList, uint32 InFlags, FString const& InDestFileName) override;`
- L20 _public prototype_ `virtual void EndCapture(FRHICommandListImmediate* InRHICommandList) override;`
- L25 _protected prototype_ `virtual void StartupModule() override;`
- L26 _protected prototype_ `virtual void ShutdownModule() override;`
- L30 _protected prototype_ `virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L34 _private prototype_ `void Tick(float DeltaTime);`
- L37 _private prototype_ `void InjectDebugExecKeybind();` — Injects a debug key bind into the local player so that the hot key works the same in game
- L40 _private prototype_ `void CaptureFrame();` — Helper function for CVar command binding.
- L42 _private prototype_ `void DoFrameCaptureCurrentViewport(FViewport* InViewport, uint32 InFlags, FString const& InDestFileName);`
- L44 _private prototype_ `void BeginFrameCapture(const FString& InCaptureFileName);`
- L45 _private prototype_ `void EndFrameCapture(void* HWnd, uint32 Flags, FString const& DestFileName);`
- L47 _private prototype_ `void StartXcode(FString CapturePath);`
- L50 _private member_ `uint32 CaptureFlags;`
- L51 _private member_ `uint32 bCaptureInProgress:1;`
- L53 _private member_ `FString CaptureFileName;`
- L56 _private member_ `FXcodeGPUDebuggerPluginEditorExtension* EditorExtensions;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(XcodeGPUDebuggerPlugin, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(XcodeGPUDebuggerPlugin, Log, All);`

### `Plugins/Developer/XcodeGPUDebuggerPlugin/Source/XcodeGPUDebuggerPlugin/Private/XcodeGPUDebuggerPluginStyle.h` (Private)


#### class `FXcodeGPUDebuggerPluginStyle`  
`class FXcodeGPUDebuggerPluginStyle`  
_L9-21_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L17 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L20 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;`

### `Plugins/Developer/XcodeGPUDebuggerPlugin/Source/XcodeGPUDebuggerPlugin/Public/IXcodeGPUDebuggerPlugin.h` (Public)


#### class `IXcodeGPUDebuggerPlugin`  
`class IXcodeGPUDebuggerPlugin : public IInputDeviceModule, public IRenderCaptureProvider`  
_L8-20_
- inherits: `IInputDeviceModule,IRenderCaptureProvider`
- L11 _public function_ `static inline IXcodeGPUDebuggerPlugin& Get()`
- L16 _public function_ `static inline bool IsAvailable()`
