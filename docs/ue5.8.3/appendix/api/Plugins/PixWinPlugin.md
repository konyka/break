# Plugins / PixWinPlugin

- module root: `Plugins/Developer/PixWinPlugin/Source/PixWinPlugin`
- headers: 5; symbols: 42
- symbol kinds: class=5, delegate=1, function=4, member=10, namespace=2, prototype=20
- DynamicallyLoadedModuleNames: LevelEditor
- PrivateDependencyModuleNames: WinPixEventRuntime

### `Plugins/Developer/PixWinPlugin/Source/PixWinPlugin/Private/PixWinPluginCommands.h` (Private)


#### class `FPixWinPluginCommands`  
`class FPixWinPluginCommands : public TCommands<FPixWinPluginCommands>`  
_L10-21_
- inherits: `TCommands<FPixWinPluginCommands>`
- L13 _public function_ `FPixWinPluginCommands() : TCommands<FPixWinPluginCommands>(TEXT("PixWinPlugin"), NSLOCTEXT("Contexts", "PixWinPlugin", "PixWin Plugin"), NAME_None, FPixWinPluginStyle::Get()->GetStyleSetName())`
- L18 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<class FUICommandInfo> CaptureFrame;`

### `Plugins/Developer/PixWinPlugin/Source/PixWinPlugin/Private/PixWinPluginModule.h` (Private)


#### class `FPixWinPluginModule`  
`class FPixWinPluginModule : public IPixWinPlugin`  
_L18-67_
- inherits: `IPixWinPlugin`
- desc: PIX capture plugin implementation.
- L24 _public prototype_ `virtual void CaptureFrame(FViewport* InViewport, uint32 InFlags, const FString& InDestFileName) override;`
- L25 _public prototype_ `virtual void BeginCapture(FRHICommandListImmediate* InRHICommandList, uint32 InFlags, const FString& InDestFileName) override;`
- L26 _public prototype_ `virtual void EndCapture(FRHICommandListImmediate* InRHICommandList) override;`
- L31 _protected prototype_ `virtual void StartupModule() override;`
- L32 _protected prototype_ `virtual void ShutdownModule() override;`
- L36 _protected prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L40 _private prototype_ `void OnPostEngineInit();`
- L43 _private prototype_ `void Tick(float DeltaTime);` — Tick to handle full frame capture events.
- L45 _private prototype_ `void DoFrameCaptureCurrentViewport(FViewport* InViewport, uint32 InFlags, const FString& InDestFileName);`
- L47 _private prototype_ `void BeginFrameCapture(void* HWnd, const FString& DestFileName);`
- L48 _private prototype_ `void EndFrameCapture(uint32 InFlags, const FString& DestFileName);`
- L51 _private function_ `void CaptureFrame()` — Helper function for CVar command binding.
- L53 _private member_ `Impl::FPixGraphicsAnalysisInterface* PixGraphicsAnalysisInterface = nullptr;`
- L54 _private member_ `FAutoConsoleCommand* ConsoleCommandCaptureFrame = nullptr;`
- L56 _private member_ `bool bBeginCaptureNextTick = false;`
- L57 _private member_ `bool bEndCaptureNextTick = false;`
- L59 _private member_ `bool bCurrentlyAttached = false;`
- L61 _private member_ `FString CurrentCaptureDestFileName;`
- L62 _private member_ `uint32 CurrentCaptureFlags = 0u;`
- L65 _private member_ `TSharedPtr<FPixWinPluginEditorExtension> EditorExtension;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(PixWinPlugin, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(PixWinPlugin, Log, All);`
- L14 _namespace_ `namespace Impl`
- L15 _namespace_ `namespace Impl`

### `Plugins/Developer/PixWinPlugin/Source/PixWinPlugin/Private/PixWinPluginStyle.h` (Private)


#### class `FPixWinPluginStyle`  
`class FPixWinPluginStyle`  
_L9-21_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr<class ISlateStyle> Get();`
- L17 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L20 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;`

### `Plugins/Developer/PixWinPlugin/Source/PixWinPlugin/Private/SPixWinPluginEditorExtension.h` (Private)


#### class `FPixWinPluginEditorExtension`  
`class FPixWinPluginEditorExtension`  
_L15-23_
- L18 _public prototype_ `FPixWinPluginEditorExtension(FPixWinPluginModule* ThePlugin);`
- L19 _public prototype_ `~FPixWinPluginEditorExtension();`
- L22 _private prototype_ `void Initialize(FPixWinPluginModule* ThePlugin);`

### `Plugins/Developer/PixWinPlugin/Source/PixWinPlugin/Public/IPixWinPlugin.h` (Public)


#### class `IPixWinPlugin`  
`class IPixWinPlugin : public IInputDeviceModule, public IRenderCaptureProvider`  
_L10-22_
- inherits: `IInputDeviceModule,IRenderCaptureProvider`
- desc: PIX capture plugin interface.
- L13 _public function_ `static inline IPixWinPlugin& Get()`
- L18 _public function_ `static inline bool IsAvailable()`
