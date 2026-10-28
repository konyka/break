# Plugins / PixelStreamingEditor

- module root: `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor`
- headers: 10; symbols: 167
- symbol kinds: class=9, delegate=1, enum=1, enumerator=2, externvar=3, function=17, member=41, namespace=15, prototype=78
- PrivateDependencyModuleNames: AVCodecsCore, ApplicationCore, Core, CoreUObject, DesktopPlatform, EditorStyle, Engine, EngineSettings, HTTP, InputCore, Json, LevelEditor, MainFrame, PixelCapture, PixelStreaming, PixelStreamingInput, PixelStreamingServers, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, Sockets, ToolMenus, UnrealEd

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Private/EditorSubmixListener.h` (Private)


#### class `UE::EditorPixelStreaming::FEditorSubmixListener`  
`class FEditorSubmixListener : public ISubmixBufferListener`  
_L11-35_
- inherits: `ISubmixBufferListener`
- L14 _public prototype_ `static TSharedRef<FEditorSubmixListener, ESPMode::ThreadSafe> Create(const FAudioDeviceHandle& DeviceHandle);`
- L15 _public prototype_ `virtual ~FEditorSubmixListener();`
- L18 _public prototype_ `void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override;` — ISubmixBufferListener interface
- L22 _public prototype_ `void Shutdown();`
- L24 _public prototype_ `virtual const FString& GetListenerName() const override;`
- L30 _protected prototype_ `FEditorSubmixListener(const FAudioDeviceHandle& AudioDevice);`
- L33 _private member_ `Audio::FDeviceId AudioDeviceId;`
- L34 _private member_ `TSharedPtr<IPixelStreamingAudioInput> AudioInput;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace EditorPixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Private/PixelStreamingCommands.h` (Private)


#### class `UE::EditorPixelStreaming::FPixelStreamingCommands`  
`class FPixelStreamingCommands : public TCommands<FPixelStreamingCommands>`  
_L14-33_
- inherits: `TCommands<FPixelStreamingCommands>`
- L17 _public function_ `FPixelStreamingCommands() : TCommands<FPixelStreamingCommands>(TEXT("PixelStreaming"), NSLOCTEXT("Contexts", "PixelStreaming", "PixelStreaming Plugin"), NAME_None, FName(TEXT("PixelStreamingStyle")))`
- L22 _public prototype_ `virtual void RegisterCommands() override;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ExternalSignalling;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> VP8;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> VP9;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> H264;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> AV1;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> StartSignalling;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> StopSignalling;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> StreamLevelEditor;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> StreamEditor;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace EditorPixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Private/PixelStreamingEditorModule.h` (Private)


#### class `FPixelStreamingEditorModule`  
`class FPixelStreamingEditorModule : public IPixelStreamingEditorModule`  
_L18-77_
- inherits: `IPixelStreamingEditorModule`
- L22 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `virtual void StartStreaming(UE::EditorPixelStreaming::EStreamTypes InStreamType) override;`
- L26 _public prototype_ `virtual void StopStreaming() override;`
- L28 _public prototype_ `virtual void StartSignalling() override;`
- L29 _public prototype_ `virtual void StopSignalling() override;`
- L30 _public prototype_ `virtual TSharedPtr<UE::PixelStreamingServers::IServer> GetSignallingServer() override;`
- L32 _public prototype_ `virtual void SetSignallingDomain(const FString& InSignallingDomain) override;`
- L33 _public function_ `virtual FString GetSignallingDomain() override`
- L34 _public prototype_ `virtual void SetStreamerPort(int32 InStreamerPort) override;`
- L35 _public function_ `virtual int32 GetStreamerPort() override`
- L36 _public prototype_ `virtual void SetViewerPort(int32 InViewerPort) override;`
- L37 _public function_ `virtual int32 GetViewerPort() override`
- L39 _public prototype_ `virtual bool UseExternalSignallingServer() override;`
- L40 _public prototype_ `virtual void UseExternalSignallingServer(bool bInUseExternalSignallingServer) override;`
- L43 _public function_ `virtual FString GetEditorStreamerID() const`
- L46 _private prototype_ `void InitEditorStreaming(IPixelStreamingModule& Module);`
- L47 _private prototype_ `bool ParseResolution(const TCHAR* InResolution, uint32& OutX, uint32& OutY);`
- L48 _private prototype_ `void MaybeResizeEditor(TSharedPtr<SWindow> RootWindow);`
- L49 _private prototype_ `void OnFrameSizeChanged(TWeakPtr<FIntRect> NewTargetRect);`
- L50 _private prototype_ `void DisableCPUThrottlingSetting();`
- L51 _private prototype_ `void RestoreCPUThrottlingSetting();`
- L53 _private member_ `TSharedPtr<UE::EditorPixelStreaming::FPixelStreamingToolbar> Toolbar;`
- L55 _private member_ `TSharedPtr<UE::PixelStreamingServers::IServer> SignallingServer;` — Signalling/webserver
- L57 _private member_ `TSharedPtr<FMonitoredProcess> DownloadProcess;` — Download process for PS web frontend files (if we want to view output in the browser)
- L59 _private member_ `FString SignallingDomain;` — The signalling server host: eg ws://127.0.0.1
- L61 _private member_ `FString EditorStreamerID;` — The ID for the Editor stream, eg "Editor"
- L63 _private member_ `int32 StreamerPort;` — The port the streamer will connect to. eg 8888
- L66 _private member_ `int32 ViewerPort = 8080;` — ports <1000 require superuser privileges on Linux
- L68 _private member_ `int32 ViewerPort = 80;`
- L71 _private member_ `TSharedPtr<IPixelStreamingStreamer> EditorStreamer;` — The streamer used by the PixelStreamingEditor module
- L73 _private member_ `bool bUseExternalSignallingServer = false;`
- L74 _private member_ `bool bOldCPUThrottlingSetting = false;`
- L76 _private member_ `TMap<Audio::FDeviceId, TSharedPtr<UE::EditorPixelStreaming::FEditorSubmixListener, ESPMode::ThreadSafe>> AudioInputs;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace EditorPixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Private/PixelStreamingToolbar.h` (Private)


#### class `UE::EditorPixelStreaming::FPixelStreamingToolbar`  
`class FPixelStreamingToolbar`  
_L15-36_
- L18 _public prototype_ `FPixelStreamingToolbar();`
- L19 _public prototype_ `virtual ~FPixelStreamingToolbar();`
- L20 _public prototype_ `void StartStreaming();`
- L21 _public prototype_ `void StopStreaming();`
- L22 _public prototype_ `static TSharedRef<SWidget> GeneratePixelStreamingMenuContent(TSharedPtr<FUICommandList> InCommandList);`
- L23 _public prototype_ `static FText GetActiveViewportName();`
- L24 _public prototype_ `static const FSlateBrush* GetActiveViewportIcon();`
- L27 _private prototype_ `void RegisterMenus();`
- L28 _private prototype_ `void RegisterEmbeddedSignallingServerConfig(FMenuBuilder& MenuBuilder);`
- L29 _private prototype_ `void RegisterRemoteSignallingServerConfig(FMenuBuilder& MenuBuilder);`
- L30 _private prototype_ `void RegisterSignallingServerURLs(FMenuBuilder& MenuBuilder);`
- L31 _private prototype_ `void RegisterStreamerControls(FMenuBuilder& MenuBuilder);`
- L32 _private prototype_ `void RegisterVCamControls(FMenuBuilder& MenuBuilder);`
- L33 _private prototype_ `void RegisterCodecConfig(FMenuBuilder& MenuBuilder);`
- L35 _private member_ `TSharedPtr<class FUICommandList> PluginCommands;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace EditorPixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Private/Settings.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace EditorPixelStreaming` (scope `UE`)
- L9 _namespace_ `namespace Settings` (scope `UE::EditorPixelStreaming`)
- L11 _prototype_ `extern void InitialiseSettings();` (scope `UE::EditorPixelStreaming::Settings`)
- L14 _externvar_ `extern TAutoConsoleVariable<bool> CVarEditorPixelStreamingStartOnLaunch;` (scope `UE::EditorPixelStreaming::Settings`)
- L15 _externvar_ `extern TAutoConsoleVariable<bool> CVarEditorPixelStreamingUseRemoteSignallingServer;` (scope `UE::EditorPixelStreaming::Settings`)
- L16 _externvar_ `extern TAutoConsoleVariable<FString> CVarEditorPixelStreamingSource;` (scope `UE::EditorPixelStreaming::Settings`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Public/IPixelStreamingEditorModule.h` (Public)


#### class `IPixelStreamingEditorModule`  
`class IPixelStreamingEditorModule : public IModuleInterface`  
_L14-123_
- inherits: `IModuleInterface`
- desc: The public interface of the Pixel Streaming Editor module.
- L23 _public function_ `static inline IPixelStreamingEditorModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L40 _public prototype_ `virtual void StartStreaming(UE::EditorPixelStreaming::EStreamTypes InStreamType) = 0;` — Starts the editor specific streamer. @param InStreamType The stream type for this streamer.
- L46 _public prototype_ `virtual void StopStreaming() = 0;` — Starts the editor specific streamer.
- L52 _public prototype_ `virtual void StartSignalling() = 0;` — Start the inbuilt C++ signalling server
- L58 _public prototype_ `virtual void StopSignalling() = 0;` — Stop the inbuilt C++ signalling server
- L65 _public prototype_ `virtual TSharedPtr<UE::PixelStreamingServers::IServer> GetSignallingServer() = 0;` — Get the inbuilt C++ signalling server @return TSharedPtr<UE::PixelStreamingServers::IServer> The signalling server
- L72 _public prototype_ `virtual void SetSignallingDomain(const FString& InSignallingDomain) = 0;` — Set the domain for the inbuilt c++ signalling server @param InSignallingDomain The domain for the inbuilt c++ signalling server
- L79 _public prototype_ `virtual FString GetSignallingDomain() = 0;` — Get the domain for the inbuilt c++ signalling server @return FString The inbuilt c++ signalling server's domain
- L86 _public prototype_ `virtual void SetStreamerPort(int32 InStreamerPort) = 0;` — Set the port streamers connect to for the inbuilt c++ signalling server @param InStreamerPort The port streamers connect to for the inbuilt c++ signalling server
- L93 _public prototype_ `virtual int32 GetStreamerPort() = 0;` — Get the port streamers connect to for the inbuilt c++ signalling server @return int32 The inbuilt c++ signalling server's port for streamers connect to
- L100 _public prototype_ `virtual void SetViewerPort(int32 InViewerPort) = 0;` — Set the port viewers connect to for the inbuilt c++ signalling server @param InViewerPort The port viewers connect to for the inbuilt c++ signalling server
- L107 _public prototype_ `virtual int32 GetViewerPort() = 0;` — Get the port viewers connect to for the inbuilt c++ signalling server @return int32 The inbuilt c++ signalling server's port for viewers connect to
- L115 _public prototype_ `virtual bool UseExternalSignallingServer() = 0;` — @brief Get if streamers should use an external signalling server or the inbuilt c++ signalling server @return true Use an external signalling server @return false Use the inbuilt c++ signalling server
- L122 _public prototype_ `virtual void UseExternalSignallingServer(bool bUseExternalSignallingServer) = 0;` — @brief Set if streamers should use an external signalling server or the inbuilt c++ signalling server @param bUseExternalSignallingServer Should streamers use an external signalling server

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Public/PixelStreamingEditorUtils.h` (Public)


#### enum `UE::EditorPixelStreaming::EStreamTypes`  
`enum class EStreamTypes : uint8`  
_L13-17_
- L15 _public enumerator_ `LevelEditorViewport = 0`
- L16 _public enumerator_ `Editor = 1`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace EditorPixelStreaming` (scope `UE`)
- L19 _prototype_ `FString ToString(EStreamTypes StreamType);` (scope `UE::EditorPixelStreaming`)
- L20 _prototype_ `const TCHAR* ToString(EWindowType Type);` (scope `UE::EditorPixelStreaming`)
- L21 _prototype_ `const FString HashWindow(SWindow& SlateWindow, const FTextureRHIRef& FrameBuffer);` (scope `UE::EditorPixelStreaming`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Public/PixelStreamingStyle.h` (Public)


#### class `UE::EditorPixelStreaming::FPixelStreamingStyle`  
`class FPixelStreamingStyle`  
_L9-25_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L17 _public prototype_ `static FSlateStyleSet& Get();` — @return The Slate style set for the Shooter game
- L18 _public prototype_ `static FName GetStyleSetName();`
- L21 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L24 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace EditorPixelStreaming` (scope `UE`)

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Public/PixelStreamingVideoInputBackBufferComposited.h` (Public)


#### class `FPixelStreamingVideoInputBackBufferComposited`  
`class FPixelStreamingVideoInputBackBufferComposited : public FPixelStreamingVideoInputRHI`  
_L15-85_
- inherits: `FPixelStreamingVideoInputRHI`
- desc: Use this if you want to send the full UE editor as video input.
- L18 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputBackBufferComposited> Create();`
- L19 _public prototype_ `virtual ~FPixelStreamingVideoInputBackBufferComposited();`
- L21 _public prototype_ `virtual FString ToString() override;`
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrameSizeChanged, TWeakPtr<FIntRect>);`
- L24 _public member_ `FOnFrameSizeChanged OnFrameSizeChanged;`
- L55 _private prototype_ `FPixelStreamingVideoInputBackBufferComposited();`
- L56 _private prototype_ `void CompositeWindows();`
- L58 _private prototype_ `void OnBackBufferReady(SWindow &SlateWindow, ISlateViewportProvider& ViewportProvider);`
- L59 _private prototype_ `void OnPreTick(float DeltaTime);`
- L61 _private member_ `FDelegateHandle OnBackBufferReadyToPresentHandle;`
- L62 _private member_ `FDelegateHandle OnPreTickHandle;`
- L64 _private member_ `TArray<FTexturedWindow> TopLevelWindows;`
- L66 _private member_ `FCriticalSection TopLevelWindowsCriticalSection;`
- L68 _private member_ `TSharedPtr<FIntRect> SharedFrameRect;`
- L73 _private function_ `template <class T> T VectorMax(const T A, const T B)` — Util functions for 2D vectors
- L80 _private function_ `template <class T> T VectorMin(const T A, const T B)`

#### class `FPixelStreamingVideoInputBackBufferComposited::FTexturedWindow`  
`class FTexturedWindow`  
_L29-52_
- desc: Our class to keep window and texture information. Use of this struct prevents SWindow properties being updated composition as well as preventing deletion of our staging textures pre composition
- L32 _public function_ `FTexturedWindow(FVector2D InPositionInScreen, FVector2D InSizeInScreen, float InOpacity, EWindowType InType, SWindow *InOwningWindow) : PositionInScreen(InPositionInScreen), SizeInScreen(InSizeInScreen), Opacity(InOpacity), Type(InType), Texture(nullptr), OwningWindow(InOwningWindow)`
- L37 _public function_ `FVector2D GetPositionInScreen()`
- L38 _public function_ `FVector2D GetSizeInScreen()`
- L39 _public function_ `float GetOpacity()`
- L40 _public function_ `EWindowType GetType()`
- L41 _public function_ `SWindow *GetOwningWindow()`
- L42 _public function_ `TRefCountPtr<IPooledRenderTarget> &GetTexture()`
- L43 _public function_ `void SetTexture(TRefCountPtr<IPooledRenderTarget> InTexture)`
- L46 _private member_ `FVector2D PositionInScreen;`
- L47 _private member_ `FVector2D SizeInScreen;`
- L48 _private member_ `float Opacity;`
- L49 _private member_ `EWindowType Type;`
- L50 _private member_ `TRefCountPtr<IPooledRenderTarget> Texture;`
- L51 _private member_ `SWindow *OwningWindow;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrameSizeChanged, TWeakPtr<FIntRect>);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingEditor/Public/PixelStreamingVideoInputViewport.h` (Public)


#### class `FPixelStreamingVideoInputViewport`  
`class FPixelStreamingVideoInputViewport : public FPixelStreamingVideoInputRHI`  
_L13-35_
- inherits: `FPixelStreamingVideoInputRHI`
- desc: Use this if you want to send the UE primary scene viewport as video input - will only work in editor.
- L16 _public prototype_ `static TSharedPtr<FPixelStreamingVideoInputViewport> Create(TSharedPtr<IPixelStreamingStreamer> InAssociatedStreamer);`
- L17 _public prototype_ `virtual ~FPixelStreamingVideoInputViewport();`
- L19 _public prototype_ `virtual FString ToString() override;`
- L22 _private prototype_ `FPixelStreamingVideoInputViewport() = default;`
- L24 _private prototype_ `bool FilterWindow(SWindow& Window);`
- L25 _private prototype_ `void OnWindowRendered(SWindow& Window);`
- L26 _private prototype_ `void OnPIEViewportRendered(FViewport* InViewport);`
- L27 _private prototype_ `void SubmitViewport(FViewport* InViewport);`
- L29 _private member_ `FDelegateHandle DelegateHandle;`
- L30 _private member_ `FDelegateHandle PIEDelegateHandle;`
- L32 _private member_ `FName TargetViewportType = FName(FString(TEXT("Scene`
- L34 _private member_ `TWeakPtr<IPixelStreamingStreamer> AssociatedStreamer;`
