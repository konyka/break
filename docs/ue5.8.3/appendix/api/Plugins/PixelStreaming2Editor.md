# Plugins / PixelStreaming2Editor

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor`
- headers: 11; symbols: 190
- symbol kinds: class=14, delegate=2, enum=1, enumerator=2, function=26, macro=3, member=40, namespace=12, prototype=90
- PrivateDependencyModuleNames: AVCodecsCore, ApplicationCore, AssetDefinition, Core, CoreUObject, DesktopPlatform, EditorStyle, Engine, EngineSettings, HTTP, InputCore, Json, LevelEditor, MainFrame, PixelCapture, PixelStreaming2, PixelStreaming2Core, PixelStreaming2Input, PixelStreaming2RTC, PixelStreaming2Servers, PixelStreaming2Settings, Projects, RHI, RenderCore, Renderer, Slate, Sockets, ToolMenus, UnrealEd
- PublicDependencyModuleNames: SlateCore

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Internal/PixelStreaming2Style.h` (Internal)


#### class `UE::EditorPixelStreaming2::FPixelStreaming2Style`  
`class FPixelStreaming2Style`  
_L10-26_
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L18 _public prototype_ `static FSlateStyleSet& Get();` — @return The Slate style set for the Shooter game
- L19 _public prototype_ `static FName GetStyleSetName();`
- L22 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L25 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API PIXELSTREAMING2EDITOR_API`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace EditorPixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Internal/VideoProducerBackBufferComposited.h` (Internal)


#### class `UE::EditorPixelStreaming2::FVideoProducerBackBufferComposited`  
`class FVideoProducerBackBufferComposited : public FVideoProducerBase`  
_L21-97_
- inherits: `FVideoProducerBase`
- desc: Use this if you want to send the full UE editor as video input.
- L24 _public prototype_ `static TSharedPtr<FVideoProducerBackBufferComposited> Create();`
- L25 _public prototype_ `virtual ~FVideoProducerBackBufferComposited();`
- L27 _public prototype_ `virtual FString ToString() override;`
- L30 _public function_ `virtual EVideoProducerCapabilities GetCapabilities()`
- L35 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrameSizeChanged, TWeakPtr<FIntRect>);`
- L36 _public member_ `FOnFrameSizeChanged OnFrameSizeChanged;`
- L67 _private prototype_ `FVideoProducerBackBufferComposited();`
- L68 _private prototype_ `void CompositeWindows(TSharedPtr<FVideoProducerUserData> UserData);`
- L70 _private prototype_ `void OnBackBufferReady(SWindow& SlateWindow, ISlateViewportProvider& ViewportProvider);`
- L71 _private prototype_ `void OnPreTick(float DeltaTime);`
- L73 _private member_ `FDelegateHandle OnBackBufferReadyToPresentHandle;`
- L74 _private member_ `FDelegateHandle OnPreTickHandle;`
- L76 _private member_ `TArray<FTexturedWindow> TopLevelWindows;`
- L78 _private member_ `FCriticalSection TopLevelWindowsCriticalSection;`
- L80 _private member_ `TSharedPtr<FIntRect> SharedFrameRect;`
- L85 _private function_ `template <class T> T VectorMax(const T A, const T B)` — Util functions for 2D vectors
- L92 _private function_ `template <class T> T VectorMin(const T A, const T B)`

#### class `UE::EditorPixelStreaming2::FVideoProducerBackBufferComposited::FTexturedWindow`  
`class FTexturedWindow`  
_L41-64_
- desc: Our class to keep window and texture information. Use of this struct prevents SWindow properties being updated composition as well as preventing deletion of our staging textures pre composition
- L44 _public function_ `FTexturedWindow(FVector2D InPositionInScreen, FVector2D InSizeInScreen, float InOpacity, EWindowType InType, SWindow* InOwningWindow) : PositionInScreen(InPositionInScreen), SizeInScreen(InSizeInScreen), Opacity(InOpacity), Type(InType), Texture(nullptr), OwningWindow(InOwningWindow)`
- L49 _public function_ `FVector2D GetPositionInScreen()`
- L50 _public function_ `FVector2D GetSizeInScreen()`
- L51 _public function_ `float GetOpacity()`
- L52 _public function_ `EWindowType GetType()`
- L53 _public function_ `SWindow* GetOwningWindow()`
- L54 _public function_ `TRefCountPtr<IPooledRenderTarget>& GetTexture()`
- L55 _public function_ `void SetTexture(TRefCountPtr<IPooledRenderTarget> InTexture)`
- L58 _private member_ `FVector2D PositionInScreen;`
- L59 _private member_ `FVector2D SizeInScreen;`
- L60 _private member_ `float Opacity;`
- L61 _private member_ `EWindowType Type;`
- L62 _private member_ `TRefCountPtr<IPooledRenderTarget> Texture;`
- L63 _private member_ `SWindow* OwningWindow;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2EDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace EditorPixelStreaming2` (scope `UE`)
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrameSizeChanged, TWeakPtr<FIntRect>);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Internal/VideoProducerLevelEditor.h` (Internal)


#### class `UE::EditorPixelStreaming2::FVideoProducerLevelEditor`  
`class FVideoProducerLevelEditor : public FVideoProducerViewportBase`  
_L20-35_
- inherits: `FVideoProducerViewportBase`
- desc: Use this if you want to send the UE primary scene viewport as video input - will only work in editor.
- L23 _public prototype_ `static TSharedPtr<FVideoProducerLevelEditor> Create();`
- L24 _public prototype_ `virtual ~FVideoProducerLevelEditor() = default;`
- L26 _public prototype_ `virtual FString ToString() override;`
- L29 _protected prototype_ `virtual bool ShouldCaptureViewport() override;`
- L32 _private prototype_ `FVideoProducerLevelEditor() = default;`
- L34 _private prototype_ `void OnPreTick(float DeltaTime);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELSTREAMING2EDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace EditorPixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Private/AssetDefinition_PixelStreaming2MediaTexture.h` (Private)


#### class `UAssetDefinition_PixelStreaming2MediaTexture`  
`class UAssetDefinition_PixelStreaming2MediaTexture : public UAssetDefinitionDefault`  
_L9-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Private/AssetDefinition_VideoProducer.h` (Private)


#### class `UAssetDefinition_VideoProducer`  
`class UAssetDefinition_VideoProducer : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public function_ `virtual void BuildFilters(TArray<FAssetFilterData>& OutFilters) const override`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Private/Factories.h` (Private)


#### class `UPixelStreaming2MediaTextureFactory`  
`class UPixelStreaming2MediaTextureFactory : public UFactory`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: ---------- UPixelStreaming2MediaTextureFactory -------------------
- L18 _public prototype_ `virtual FText GetDisplayName() const override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UPixelStreaming2VideoProducerBackBufferFactory`  
`class UPixelStreaming2VideoProducerBackBufferFactory : public UFactory`  
_L26-34_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: ---------- UPixelStreaming2VideoProducerBackBufferFactory -------------------
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`
- L32 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L33 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UPixelStreaming2VideoProducerMediaCaptureFactory`  
`class UPixelStreaming2VideoProducerMediaCaptureFactory : public UFactory`  
_L40-48_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: ---------- UPixelStreaming2VideoProducerMediaCaptureFactory -------------------
- L45 _public prototype_ `virtual FText GetDisplayName() const override;`
- L46 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L47 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UPixelStreaming2VideoProducerRenderTargetFactory`  
`class UPixelStreaming2VideoProducerRenderTargetFactory : public UFactory`  
_L54-62_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: ---------- UPixelStreaming2VideoProducerRenderTargetFactory -------------------
- L59 _public prototype_ `virtual FText GetDisplayName() const override;`
- L60 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L61 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Editor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Editor, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Private/PixelStreaming2Commands.h` (Private)


#### class `UE::EditorPixelStreaming2::FPixelStreaming2Commands`  
`class FPixelStreaming2Commands : public TCommands<FPixelStreaming2Commands>`  
_L13-33_
- inherits: `TCommands<FPixelStreaming2Commands>`
- L16 _public function_ `FPixelStreaming2Commands() : TCommands<FPixelStreaming2Commands>(TEXT("PixelStreaming2"), NSLOCTEXT("Contexts", "PixelStreaming2", "PixelStreaming2 Plugin"), NAME_None, FName(TEXT("PixelStreaming2Style")))`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ExternalSignalling;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ServeHttps;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> VP8;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> VP9;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> H264;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> AV1;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> StartSignalling;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> StopSignalling;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> StreamLevelEditor;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> StreamEditor;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace EditorPixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Private/PixelStreaming2EditorModule.h` (Private)


#### class `UE::EditorPixelStreaming2::FPixelStreaming2EditorModule`  
`class FPixelStreaming2EditorModule : public IPixelStreaming2EditorModule`  
_L14-92_
- inherits: `IPixelStreaming2EditorModule`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual void StartStreaming(EPixelStreaming2EditorStreamTypes InStreamType) override;`
- L22 _public prototype_ `virtual void StopStreaming() override;`
- L24 _public prototype_ `virtual void StartSignalling() override;`
- L25 _public prototype_ `virtual void StopSignalling(bool bForce) override;`
- L26 _public prototype_ `virtual TSharedPtr<UE::PixelStreaming2Servers::IServer> GetSignallingServer() override;`
- L28 _public prototype_ `virtual void SetSignallingDomain(const FString& InSignallingDomain) override;`
- L29 _public function_ `virtual FString GetSignallingDomain() override`
- L30 _public prototype_ `virtual void SetStreamerPort(int32 InStreamerPort) override;`
- L31 _public function_ `virtual int32 GetStreamerPort() override`
- L32 _public prototype_ `virtual void SetViewerPort(int32 InViewerPort) override;`
- L33 _public function_ `virtual int32 GetViewerPort() override`
- L34 _public prototype_ `virtual void SetServeHttps(bool bServeHttps) override;`
- L35 _public function_ `virtual bool GetServeHttps() override`
- L36 _public prototype_ `virtual void SetSSLCertificatePath(const FString& Path) override;`
- L37 _public function_ `virtual FString GetSSLCertificatePath() override`
- L38 _public prototype_ `virtual void SetSSLPrivateKeyPath(const FString& Path) override;`
- L39 _public function_ `virtual FString GetSSLPrivateKeyPath() override`
- L42 _public function_ `virtual FString GetEditorStreamerID() const`
- L45 _private prototype_ `void InitEditorStreaming(IPixelStreaming2RTCModule& Module);`
- L46 _private prototype_ `bool ParseResolution(const TCHAR* InResolution, uint32& OutX, uint32& OutY);`
- L47 _private prototype_ `void MaybeResizeEditor(TSharedPtr<SWindow> RootWindow);`
- L48 _private prototype_ `void DisableCPUThrottlingSetting();`
- L49 _private prototype_ `void RestoreCPUThrottlingSetting(bool bForce = false);`
- L50 _private prototype_ `void StopSignallingAfterFrames(uint8 FrameDelay);`
- L53 _private prototype_ `void OnBeginPIE(bool bIsSimulating);`
- L54 _private prototype_ `void OnEndPIE(bool bIsSimulating);`
- L57 _private member_ `TSharedPtr<FPixelStreaming2Toolbar> Toolbar;`
- L59 _private member_ `TSharedPtr<UE::PixelStreaming2Servers::IServer> SignallingServer;` — Signalling/webserver
- L61 _private member_ `TSharedPtr<FMonitoredProcess> DownloadProcess;` — Download process for PS web frontend files (if we want to view output in the browser)
- L63 _private member_ `FString SignallingDomain;` — The signalling server host: eg ws://127.0.0.1
- L65 _private member_ `int32 StreamerPort;` — The port the streamer will connect to. eg 8888
- L68 _private member_ `int32 ViewerPort = 8080;` — ports <1000 require superuser privileges on Linux
- L70 _private member_ `int32 ViewerPort = 80;`
- L73 _private member_ `bool bServeHttps = false;`
- L75 _private member_ `FString SSLCertificatePath;`
- L77 _private member_ `FString SSLPrivateKeyPath;`
- L79 _private member_ `FString EditorStreamerID;`
- L82 _private member_ `TSharedPtr<IPixelStreaming2Streamer> EditorStreamer;` — The streamer used by the PixelStreaming2Editor module
- L85 _private member_ `TSharedPtr<IPixelStreaming2Streamer> PIEStreamer;`
- L89 _private member_ `bool bOldCPUThrottlingSetting = false;` — The original throttling setting prior to first streamer disabling it
- L91 _private member_ `std::atomic<int> CpuThrottlingSetCount = 0;` — Number of streamers that have requested the throttling be disabled

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EditorPixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Private/PixelStreaming2Toolbar.h` (Private)


#### class `UE::EditorPixelStreaming2::FPixelStreaming2Toolbar`  
`class FPixelStreaming2Toolbar`  
_L10-43_
- L13 _public prototype_ `FPixelStreaming2Toolbar();`
- L14 _public prototype_ `virtual ~FPixelStreaming2Toolbar();`
- L15 _public prototype_ `void StartStreaming();`
- L16 _public prototype_ `void StopStreaming();`
- L17 _public prototype_ `static TSharedRef<SWidget> GeneratePixelStreaming2MenuContent(TSharedPtr<FUICommandList> InCommandList);`
- L18 _public prototype_ `static FText GetActiveViewportName();`
- L19 _public prototype_ `static const FSlateBrush* GetActiveViewportIcon();`
- L22 _private prototype_ `void RegisterMenus();`
- L23 _private prototype_ `void RegisterEmbeddedSignallingServerConfig(FMenuBuilder& MenuBuilder);`
- L24 _private prototype_ `void RegisterRemoteSignallingServerConfig(FMenuBuilder& MenuBuilder);`
- L25 _private prototype_ `void RegisterSignallingServerURLs(FMenuBuilder& MenuBuilder);`
- L26 _private prototype_ `void RegisterStreamerControls(FMenuBuilder& MenuBuilder);`
- L27 _private prototype_ `void RegisterVCamControls(FMenuBuilder& MenuBuilder);`
- L28 _private prototype_ `void RegisterCodecConfig(FMenuBuilder& MenuBuilder);`
- L36 _private prototype_ `void OnOpenFileBrowserClicked(EFileType FileType);`
- L38 _private member_ `TSharedPtr<class FUICommandList> PluginCommands;`
- L42 _private member_ `FString LastBrowsePath;` — Store the last opened path so users don't have to constantly re-navigate to a certs folder when choosing cert and key

#### enum `UE::EditorPixelStreaming2::FPixelStreaming2Toolbar::EFileType`  
`enum class EFileType : uint8`  
_L30-34_
- L32 _public enumerator_ `Certificate`
- L33 _public enumerator_ `PrivateKey`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace EditorPixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Editor/Public/IPixelStreaming2EditorModule.h` (Public)


#### class `IPixelStreaming2EditorModule`  
`class IPixelStreaming2EditorModule : public IModuleInterface`  
_L15-152_
- inherits: `IModuleInterface`
- desc: Public interface that manages Pixel Streaming specific functionality within the Unreal Editor. Provides various features for controlling Pixel Streaming, such as starting and stopping the streamer.
- L24 _public function_ `static inline IPixelStreaming2EditorModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded. @return True if the module is loaded.
- L41 _public prototype_ `virtual void StartStreaming(EPixelStreaming2EditorStreamTypes InStreamType) = 0;` — Starts the editor specific streamer. @param InStreamType The stream type for this streamer.
- L47 _public prototype_ `virtual void StopStreaming() = 0;` — Starts the editor specific streamer.
- L53 _public prototype_ `virtual void StartSignalling() = 0;` — Start the inbuilt C++ signalling server
- L60 _public prototype_ `virtual void StopSignalling(bool bForce = true) = 0;` — Stop the inbuilt C++ signalling server @param bForce If true, will stop the server even if there are active streamers connected. Default is true.
- L67 _public prototype_ `virtual TSharedPtr<UE::PixelStreaming2Servers::IServer> GetSignallingServer() = 0;` — Get the inbuilt C++ signalling server @return TSharedPtr<UE::PixelStreaming2Servers::IServer> The signalling server
- L74 _public prototype_ `virtual void SetSignallingDomain(const FString& InSignallingDomain) = 0;` — Set the domain for the inbuilt c++ signalling server @param InSignallingDomain The domain for the inbuilt c++ signalling server
- L81 _public prototype_ `virtual FString GetSignallingDomain() = 0;` — Get the domain for the inbuilt c++ signalling server @return FString The inbuilt c++ signalling server's domain
- L88 _public prototype_ `virtual void SetStreamerPort(int32 InStreamerPort) = 0;` — Set the port streamers connect to for the inbuilt c++ signalling server @param InStreamerPort The port streamers connect to for the inbuilt c++ signalling server
- L95 _public prototype_ `virtual int32 GetStreamerPort() = 0;` — Get the port streamers connect to for the inbuilt c++ signalling server @return int32 The inbuilt c++ signalling server's port for streamers connect to
- L102 _public prototype_ `virtual void SetViewerPort(int32 InViewerPort) = 0;` — Set the port viewers connect to for the inbuilt c++ signalling server @param InViewerPort The port viewers connect to for the inbuilt c++ signalling server
- L109 _public prototype_ `virtual int32 GetViewerPort() = 0;` — Get the port viewers connect to for the inbuilt c++ signalling server @return int32 The inbuilt c++ signalling server's port for viewers connect to
- L116 _public prototype_ `virtual void SetServeHttps(bool bServeHttps) = 0;` — Set whether frontend content should be served of HTTPS for the inbuilt c++ signalling server @param bServeHttps
- L123 _public prototype_ `virtual bool GetServeHttps() = 0;` — Get the bool indicating if frontend content is being served over HTTPS for the inbuilt c++ signalling server @return bool true if frontend content is being served over https, else false.
- L130 _public prototype_ `virtual void SetSSLCertificatePath(const FString& Path) = 0;` — Set the path to file containing the SSL certificate. Required if frontend content is being served of HTTPS for the inbuilt c++ signalling server @param Path The path to file containing the SSL certificate.
- L137 _public prototype_ `virtual FString GetSSLCertificatePath() = 0;` — Get the path to file containing the SSL certificate. @return FString The path to file containing the SSL certificate.
- L144 _public prototype_ `virtual void SetSSLPrivateKeyPath(const FString& Path) = 0;` — Set the path to file containing the SSL private key. Required if frontend content is being served of HTTPS for the inbuilt c++ signalling server @param Path The path to file containing the SSL private key.
- L151 _public prototype_ `virtual FString GetSSLPrivateKeyPath() = 0;` — Get the path to file containing the SSL private key. @return FString The path to file containing the SSL private key.
