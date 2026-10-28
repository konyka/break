# Plugins / MediaPlayerEditor

- module root: `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor`
- headers: 54; symbols: 586
- symbol kinds: class=54, delegate=2, enum=6, enumerator=25, function=63, macro=10, member=134, namespace=6, prototype=283, struct=3
- DynamicallyLoadedModuleNames: AssetTools, MainFrame, Media, WorkspaceMenuStructure
- PrivateDependencyModuleNames: ApplicationCore, AudioMixer, ComponentVisualizers, ContentBrowser, CoreUObject, DesktopPlatform, DesktopWidgets, EditorFramework, EditorWidgets, Engine, InputCore, MediaAssets, MediaUtils, PropertyEditor, RHI, RenderCore, Renderer, TextureEditor, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: AssetTools, Media
- PublicDependencyModuleNames: AssetDefinition, Core, Slate, SlateCore

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Internal/Providers/ViewportTileVisibilityProvider.h` (Internal)


#### class `UE::MediaPlayerEditor::FViewportTileVisibilityProvider`  
`class FViewportTileVisibilityProvider : public FMediaTileVisibilityProvider`  
_L27-46_
- inherits: `FMediaTileVisibilityProvider`
- desc: Tile-visibility provider for widgets that show a media texture in a viewport (no zoom/pan/sub-region). Picks the integer mip pair bracketing log2(SourceSize / DisplaySize) and marks every tile at those mips visible. Both mips are needed because trilinear filtering blends them - loading just one starves the blend. Threading: SetDisplaySizePx is game-thread; GatherVisibleTiles runs on a resolver worker thread and may be called concurrently with itself. Mutex protects DisplaySizePx. Lifetime: consumer holds the TSharedPtr; resolver tracks it weakly. Drop the TSharedPtr to detach.
- L31 _public prototype_ `void SetDisplaySizePx(FIntPoint InSizePx);` — Update the on-screen pixel size of the widget hosting this provider. Game-thread only.
- L34 _public prototype_ `virtual void GatherVisibleTiles(const FMediaSequenceInfo& InSequenceInfo, FMediaTileVisibilityRequest& OutRequest) const override;`
- L37 _public prototype_ `virtual bool IsAlive() const override;`
- L42 _private member_ `mutable FCriticalSection Mutex;` — Guards DisplaySizePx against the cross-thread access between SetDisplaySizePx and GatherVisibleTiles.
- L45 _private member_ `FIntPoint DisplaySizePx = FIntPoint::ZeroValue;` — Latest on-screen pixel size pushed by the consumer. Zero until the first SetDisplaySizePx call.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MediaPlayerEditor` (scope `UE`)

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/AssetDefinition/AssetDefinition_FileMediaSource.h` (Private)


#### class `UAssetDefinition_FileMediaSource`  
`class UAssetDefinition_FileMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/AssetDefinition/AssetDefinition_MediaPlayer.h` (Private)


#### class `UAssetDefinition_MediaPlayer`  
`class UAssetDefinition_MediaPlayer : public UAssetDefinitionDefault`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/AssetDefinition/AssetDefinition_MediaPlaylist.h` (Private)


#### class `UAssetDefinition_MediaPlaylist`  
`class UAssetDefinition_MediaPlaylist : public UAssetDefinitionDefault`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/AssetDefinition/AssetDefinition_MediaTexture.h` (Private)


#### class `UAssetDefinition_MediaTexture`  
`class UAssetDefinition_MediaTexture : public UAssetDefinitionDefault`  
_L9-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/AssetDefinition/AssetDefinition_PlatformMediaSource.h` (Private)


#### class `UAssetDefinition_PlatformMediaSource`  
`class UAssetDefinition_PlatformMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/AssetDefinition/AssetDefinition_StreamMediaSource.h` (Private)


#### class `UAssetDefinition_StreamMediaSource`  
`class UAssetDefinition_StreamMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Customizations/BaseMediaSourceCustomization.h` (Private)


#### class `FBaseMediaSourceCustomization`  
`class FBaseMediaSourceCustomization : public IDetailCustomization`  
_L16-71_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the UMediaSource class.
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L32 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L46 _protected prototype_ `TSharedRef<SWidget> MakePlatformPlayersMenu(const FString& IniPlatformName, const TArray<IMediaPlayerFactory*>& PlayerFactories);` — Create a player selection menu widget for the specified platform. @param IniPlatformName The INI name of the platform to create the menu for. @param PlayerFactories The available player factories. @return The menu widget.
- L53 _protected prototype_ `TSharedRef<SWidget> MakePlatformPlayerNamesValueWidget();` — Makes a widget for the DefaultPlayers property value. @return The widget.
- L60 _protected prototype_ `void SetPlatformPlayerNamesValue(FString PlatformName, FName PlayerName);` — Set the value of the PlatformPlayerNames property. @param PlayerName The name of the player to set.
- L65 _private prototype_ `FText HandlePlatformPlayersComboButtonText(FString PlatformName) const;` — Callback for getting the text content of a platform player override combo button.
- L70 _private member_ `TSharedPtr<IPropertyHandle> PlatformPlayerNamesProperty;` — Pointer to the DefaultPlayers property handle.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Customizations/FileMediaSourceCustomization.h` (Private)


#### class `FFileMediaSourceCustomization`  
`class FFileMediaSourceCustomization : public IDetailCustomization`  
_L15-59_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the UFileMediaSource class.
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L31 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L38 _private prototype_ `FString GetResolvedFilePath() const;` — Returns the fully resolved path of the selected media file.
- L41 _private prototype_ `FString HandleFilePathBrowseDirectory() const;` — Callback for getting the browse directory.
- L44 _private prototype_ `FString HandleFilePathPickerFilePath() const;` — Callback for getting the selected path in the URL picker widget.
- L47 _private prototype_ `FString HandleFilePathPickerFileTypeFilter() const;` — Callback for getting the file type filter for the URL picker.
- L50 _private prototype_ `void HandleFilePathPickerPathPicked(const FString& PickedPath);` — Callback for picking a path in the URL picker.
- L53 _private prototype_ `EVisibility HandleFilePathWarningIconVisibility() const;` — Callback for getting the visibility of warning icon for invalid URLs.
- L58 _private member_ `TSharedPtr<IPropertyHandle> FilePathProperty;` — Pointer to the FilePath property handle.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Customizations/MediaTextureCustomization.h` (Private)


#### class `FMediaTextureCustomization`  
`class FMediaTextureCustomization : public IDetailCustomization`  
_L17-37_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the UMediaTexture class.
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L33 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Customizations/PlatformMediaSourceCustomization.h` (Private)


#### class `FPlatformMediaSourceCustomization`  
`class FPlatformMediaSourceCustomization : public IDetailCustomization`  
_L17-69_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the UPlatformMediaSource class.
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L33 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L45 _protected prototype_ `TSharedRef<SWidget> MakePlatformMediaSourcesValueWidget();` — Makes a widget for the DefaultPlayers property value. @return The widget.
- L52 _protected prototype_ `void SetPlatformMediaSourcesValue(FString PlatformName, UMediaSource* MediaSource);` — Set the value of the PlatformMediaSources property. @param MediaSource The media source to set.
- L57 _private prototype_ `void HandleMediaSourceEntryBoxChanged(const FAssetData& AssetData, FString PlatformName);` — Callback for when a per-platform media source property changed.
- L60 _private prototype_ `FString HandleMediaSourceEntryBoxObjectPath(FString PlatformName) const;` — Callback for getting the currently selected object in a per-platform media source property.
- L63 _private prototype_ `bool HandleMediaSourceEntryBoxShouldFilterAsset(const FAssetData& AssetData);` — Callback for filtering media source assets.
- L68 _private member_ `TSharedPtr<IPropertyHandle> PlatformMediaSourcesProperty;` — Pointer to the DefaultPlayers property handle.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Customizations/StreamMediaSourceCustomization.h` (Private)


#### class `FStreamMediaSourceCustomization`  
`class FStreamMediaSourceCustomization : public IDetailCustomization`  
_L13-47_
- inherits: `IDetailCustomization`
- desc: Customization for stream media sources, primarily used to add a 'discover URL' dropdown to the stream URL property
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L30 _private prototype_ `TSharedRef<SWidget> GetDiscoverUrlMenu();` — Creates the dropdown menu for the 'discover URL' combo button
- L33 _private prototype_ `void GetAudioCaptureDevicesSubmenu(FMenuBuilder& MenuBuilder);` — Fills the menu builder with options for found audio source URLs
- L36 _private prototype_ `void GetVideoCaptureDevicesSubmenu(FMenuBuilder& MenuBuilder);` — Fills the menu builder with options for found video source URLs
- L39 _private prototype_ `void MakeCaptureDeviceMenu(TArray<FMediaCaptureDeviceInfo>& DeviceInfos, FMenuBuilder& MenuBuilder);` — Fills the menu builder with entries for all provided device infos
- L42 _private prototype_ `void SetStreamMediaSourceUrl(FString InUrl);` — Raised when a user selects a URL entry in the 'discover URLs' dropdown, sets the stream URL to the selected URL
- L46 _private member_ `TSharedPtr<IPropertyHandle> StreamUrlHandle;` — Cached property handle for UStreamMediaSource.StreamUrl property

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Factories/FileMediaSourceFactoryNew.h` (Private)


#### class `UFileMediaSourceFactoryNew`  
`class UFileMediaSourceFactoryNew : public UFactory`  
_L14-26_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UFileMediaSource objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Factories/MediaPlayerFactoryNew.h` (Private)


#### struct `FMediaPlayerFactoryNewOptions`  
`struct FMediaPlayerFactoryNewOptions`  
_L13-17_
- desc: Options for UMediaPlayerFactoryNew.
- L15 _public member_ `bool CreateVideoTexture;`
- L16 _public member_ `bool OkClicked;`

#### class `UMediaPlayerFactoryNew`  
`class UMediaPlayerFactoryNew : public UFactory`  
_L24-41_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UMediaPlayer objects.
- L33 _public prototype_ `virtual bool ConfigureProperties() override;`
- L34 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L35 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L36 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L40 _private member_ `FMediaPlayerFactoryNewOptions Options;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Factories/MediaPlaylistFactoryNew.h` (Private)


#### class `UMediaPlaylistFactoryNew`  
`class UMediaPlaylistFactoryNew : public UFactory`  
_L14-26_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UMediaPlaylist objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Factories/MediaTextureFactoryNew.h` (Private)


#### class `UMediaTextureFactoryNew`  
`class UMediaTextureFactoryNew : public UFactory`  
_L14-26_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- desc: Implements a factory for UMediaTexture objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Factories/PlatformMediaSourceFactoryNew.h` (Private)


#### class `UPlatformMediaSourceFactoryNew`  
`class UPlatformMediaSourceFactoryNew : public UFactory`  
_L14-26_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UPlatformMediaSource objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Factories/StreamMediaSourceFactoryNew.h` (Private)


#### class `UStreamMediaSourceFactoryNew`  
`class UStreamMediaSourceFactoryNew : public UFactory`  
_L14-26_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UStreamMediaSource objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/MediaPlayerEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaPlayerEditor, Log, All);` — Log category for the MediaPlayerEditor module.
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaPlayerEditor, Log, All);` — Log category for the MediaPlayerEditor module.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Shared/MediaPlayerEditorMediaContext.h` (Private)


#### class `UMediaPlayerEditorMediaContext`  
`class UMediaPlayerEditorMediaContext : public UToolMenuContextBase`  
_L15-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UToolMenuContextBase`
- L21 _public function_ `void InitContext(UObject* InSelectedAsset, FName InStyleSetName = NAME_None)`
- L28 _public member_ `TObjectPtr<UObject> SelectedAsset;` — `UPROPERTY(BlueprintReadWrite, Category = "Editor Menus")`
- L31 _public member_ `FName StyleSetName;` — `UPROPERTY(BlueprintReadWrite, Category = "Editor Menus")`
- L33 _public member_ `TWeakPtr<SMediaPlayerEditorMedia> MediaPlayerEditorMedia;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Shared/MediaPlayerEditorSettings.h` (Private)


#### enum `EMediaPlayerEditorScale`  
`enum class EMediaPlayerEditorScale : uint8`  
_L13-23_
- reflection: `UENUM()`
- desc: Options for scaling the viewport's video texture.
- L16 _public enumerator_ `Fill` — Stretch non-uniformly to fill the viewport.
- L19 _public enumerator_ `Fit` — Scale uniformly, preserving aspect ratio.
- L22 _public enumerator_ `Original` — Do not stretch or scale.

#### enum `EMediaPlayerEditorBackground`  
`enum class EMediaPlayerEditorBackground : uint8`  
_L27-31_
- reflection: `UENUM()`
- desc: Background types
- L29 _public enumerator_ `Black`
- L30 _public enumerator_ `Checkered`

#### enum `EMediaPlayerEditorTimerUnit`  
`enum class EMediaPlayerEditorTimerUnit : uint8`  
_L35-41_
- reflection: `UENUM()`
- desc: Timer display units
- L38 _public enumerator_ `Timecode` — Display timer in HH:MM:SS format.
- L40 _public enumerator_ `FrameNumber` — Display timer as integer frame number.

#### class `UMediaPlayerEditorSettings`  
`class UMediaPlayerEditorSettings : public UObject`  
_L44-70_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L53 _public member_ `FName DesiredPlayerName;` — `UPROPERTY(config, EditAnywhere, Category=Viewer)` — The name of the desired native media player to use for playback.
- L57 _public member_ `bool ShowTextOverlays;` — `UPROPERTY(config, EditAnywhere, Category=Viewer)` — Whether to display overlay texts.
- L61 _public member_ `EMediaPlayerEditorTimerUnit TimerUnit = EMediaPlayerEditorTimerUnit::Timecode;` — `UPROPERTY(config, EditAnywhere, Category=Viewer)` — Whether to display the playback timer as frame number or timecode.
- L65 _public member_ `EMediaPlayerEditorScale ViewportScale;` — `UPROPERTY(config, EditAnywhere, Category=Viewer)` — How the video viewport should be scaled.
- L69 _public member_ `EMediaPlayerEditorBackground MediaBackground = EMediaPlayerEditorBackground::Black;` — `UPROPERTY(config, EditAnywhere, Category = Viewer)` — Which background to use on the video background.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Shared/MediaPlayerEditorStyle.h` (Private)


#### class `FMediaPlayerEditorStyle`  
`class FMediaPlayerEditorStyle : public FSlateStyleSet`  
_L11-21_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the media player editor UI.
- L17 _public prototype_ `FMediaPlayerEditorStyle();` — Default constructor.
- L20 _public prototype_ `~FMediaPlayerEditorStyle();` — Destructor.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Shared/MediaSourceRenderer.h` (Private)


#### class `UMediaSourceRenderer`  
`class UMediaSourceRenderer : public UObject , public IMediaSourceRendererInterface , public FTickableEditorObject`  
_L17-67_
- reflection: `UCLASS()`
- inherits: `UObject,IMediaSourceRendererInterface,FTickableEditorObject`
- desc: Renders a media source to a texture in editor builds.
- L25 _public prototype_ `virtual UMediaTexture* Open(UMediaSource* InMediaSource) override;` — IMediaSourceRendererInterface interface
- L28 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L29 _public function_ `virtual TStatId GetStatId() const override`
- L36 _private prototype_ `void Close();` — Cleans everything up. The media textue will remain so it can be used/reused.
- L40 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer = nullptr;` — `UPROPERTY(Transient)` — Holds the player we are using.
- L44 _private member_ `TObjectPtr<UMediaSource> MediaSource = nullptr;` — `UPROPERTY(Transient)` — Holds the media source we are using.
- L48 _private member_ `TObjectPtr<UMediaTexture> MediaTexture = nullptr;` — `UPROPERTY(Transient)` — Holds the media texture we are using.
- L61 _private member_ `EState CurrentState = EState::Closed;`
- L62 _private member_ `float WatchdogTimeRemaining = 0.0f;`
- L64 _private prototype_ `void OnMediaOpened(FString InURL);` — `UFUNCTION()`
- L66 _private prototype_ `void OnMediaOpenFailed(FString InURL);` — `UFUNCTION()`

#### enum `UMediaSourceRenderer::EState`  
`enum class EState`  
_L50-60_
- L52 _public enumerator_ `Closed`
- L53 _public enumerator_ `Opening`
- L54 _public enumerator_ `Open`
- L55 _public enumerator_ `Playing`
- L56 _public enumerator_ `NotSupported`
- L57 _public enumerator_ `Failed`
- L58 _public enumerator_ `TimedOut`
- L59 _public enumerator_ `Errored`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Shared/MediaSourceThumbnailRenderer.h` (Private)


#### class `UMediaSourceThumbnailRenderer`  
`class UMediaSourceThumbnailRenderer : public UTextureThumbnailRenderer`  
_L15-33_
- reflection: `UCLASS()`
- inherits: `UTextureThumbnailRenderer`
- desc: Renders thumbnails for media sources.
- L22 _public prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;` — UThumbnailRenderer interface.
- L23 _public prototype_ `virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override;`
- L24 _public prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L31 _protected prototype_ `virtual UTexture* GetThumbnailTextureFromObject(UObject* Object) const;` — Gets the thumnbail from the object if the object is a media source.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Toolkits/MediaPlayerEditorToolkit.h` (Private)


#### class `FMediaPlayerEditorToolkit`  
`class FMediaPlayerEditorToolkit : public FMediaPlayerEditorToolkitMediaPlayerBase`  
_L14-62_
- inherits: `FMediaPlayerEditorToolkitMediaPlayerBase`
- desc: Implements an Editor toolkit for media players.
- L23 _public prototype_ `FMediaPlayerEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L32 _public prototype_ `void Initialize(UMediaPlayer* InMediaPlayer, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);` — Initializes the editor tool kit. @param InMediaPlayer The UMediaPlayer asset to edit. @param InMode The mode to create the toolkit in. @param InToolkitHost The toolkit host.
- L35 _public prototype_ `virtual void OnClose() override;`
- L36 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L37 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L41 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L42 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L43 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L47 _public function_ `virtual FString GetReferencerName() const override`
- L55 _protected prototype_ `virtual TSharedRef<FTabManager::FLayout> CreateLayout() override;`
- L56 _protected prototype_ `virtual void ExtendToolBar() override;`
- L61 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);` — Callback for spawning tabs.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Toolkits/MediaPlayerEditorToolkitBase.h` (Private)


#### class `FMediaPlayerEditorToolkitBase`  
`class FMediaPlayerEditorToolkitBase : public FAssetEditorToolkit , public FEditorUndoClient , public FGCObject`  
_L14-65_
- inherits: `FAssetEditorToolkit,FEditorUndoClient,FGCObject`
- desc: Base class for all Media Player Editor Toolkits
- L25 _public prototype_ `FMediaPlayerEditorToolkitBase(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L28 _public prototype_ `virtual ~FMediaPlayerEditorToolkitBase();` — Virtual destructor.
- L31 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L35 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L39 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L40 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L45 _protected member_ `TSharedRef<ISlateStyle> Style;` — Pointer to the style set to use for toolkits.
- L48 _protected function_ `virtual void BindCommands()` — Binds the UI commands to delegates.
- L51 _protected prototype_ `virtual TSharedRef<FTabManager::FLayout> CreateLayout() = 0;` — Sets up the default layout for the toolkit
- L54 _protected function_ `virtual void ExtendToolBar()` — Builds the toolbar widget for the media player editor.
- L64 _protected prototype_ `void Initialize(UObject* InAsset, FName InAppIdentifier, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);` — Initializes the editor tool kit. @param InAsset The object this toolkit is editing. @param InAppIdentifier The identifier for this specific toolkit. @param InMode The mode to create the toolkit in. @param InToolkitHost The toolkit host.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Toolkits/MediaPlayerEditorToolkitMediaPlayerBase.h` (Private)


#### class `FMediaPlayerEditorToolkitMediaPlayerBase`  
`class FMediaPlayerEditorToolkitMediaPlayerBase : public FMediaPlayerEditorToolkitBase`  
_L18-85_
- inherits: `FMediaPlayerEditorToolkitBase`
- desc: Base class for all Media Player Editor Toolkits using Media Players
- L27 _public prototype_ `FMediaPlayerEditorToolkitMediaPlayerBase(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L32 _public prototype_ `MediaPlayerEditor::MediaImage::ETextureChannelMask GetChannelMask() const;` — Returns the active mask.
- L37 _public prototype_ `bool IsChannelMasked(MediaPlayerEditor::MediaImage::ETextureChannelMask InChannel) const;` — Returns true if all the given channel mask is enabled.
- L46 _public prototype_ `void SetChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InMask);` — Sets a channel-based mask for the image. If only a single channel is displayed, it will show in greyscale. @param InMask to display.
- L51 _public prototype_ `void ToggleChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InChannelToToggle);` — Toggles the given mask in the channel mask.
- L54 _public prototype_ `virtual void OnClose() override;`
- L58 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L63 _protected member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — The media player to play the media with.
- L66 _protected member_ `TSharedPtr<SMediaPlayerEditorViewer> Viewer;` — The tab which displays the media.
- L73 _protected prototype_ `float GetForwardRate() const;` — Gets the playback rate for fast forward. @return Forward playback rate.
- L80 _protected prototype_ `float GetReverseRate() const;` — Gets the playback rate for reverse. @return Reverse playback rate.
- L83 _protected prototype_ `virtual void BindCommands() override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Toolkits/MediaPlaylistEditorToolkit.h` (Private)


#### class `FMediaPlaylistEditorToolkit`  
`class FMediaPlaylistEditorToolkit : public FMediaPlayerEditorToolkitBase`  
_L14-64_
- inherits: `FMediaPlayerEditorToolkitBase`
- desc: Implements an Editor toolkit for media play lists.
- L23 _public prototype_ `FMediaPlaylistEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L32 _public prototype_ `void Initialize(UMediaPlaylist* InMediaPlaylist, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);` — Initializes the editor tool kit. @param InMediaPlaylist The UMediaPlaylist asset to edit. @param InMode The mode to create the toolkit in. @param InToolkitHost The toolkit host.
- L35 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L36 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L40 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L41 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L42 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L46 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L47 _public function_ `virtual FString GetReferencerName() const override`
- L55 _protected prototype_ `virtual TSharedRef<FTabManager::FLayout> CreateLayout() override;`
- L60 _private member_ `TObjectPtr<UMediaPlaylist> MediaPlaylist;` — The media play list asset being edited.
- L63 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);` — Callback for spawning tabs.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Toolkits/MediaSourceEditorToolkit.h` (Private)


#### class `FMediaSourceEditorToolkit`  
`class FMediaSourceEditorToolkit : public FMediaPlayerEditorToolkitMediaPlayerBase`  
_L16-80_
- inherits: `FMediaPlayerEditorToolkitMediaPlayerBase`
- desc: Implements an Editor toolkit for media sources.
- L25 _public prototype_ `FMediaSourceEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L34 _public prototype_ `void Initialize(UMediaSource* InMediaSource, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);` — Initializes the editor tool kit. @param InMediaSource The UMediaSource asset to edit. @param InMode The mode to create the toolkit in. @param InToolkitHost The toolkit host.
- L37 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L38 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L42 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L43 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L44 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L48 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L49 _public function_ `virtual FString GetReferencerName() const override`
- L57 _protected prototype_ `virtual TSharedRef<FTabManager::FLayout> CreateLayout() override;`
- L58 _protected prototype_ `virtual void BindCommands() override;`
- L59 _protected prototype_ `virtual void ExtendToolBar() override;`
- L67 _private prototype_ `static void ValidateDesiredPlayer(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource);` — Validates that the given player can open the media source with the selected desired player. If not, the desired player is reset to fallback to the media source selection.
- L70 _private member_ `TObjectPtr<UMediaSource> MediaSource;` — The media source asset being edited.
- L73 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;` — The media texture to output the media to.
- L76 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);` — Callback for spawning tabs.
- L79 _private prototype_ `void GenerateThumbnail();` — Enqueues rendering commands to generate a thumbnail.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Visualizers/MediaSoundComponentVisualizer.h` (Private)


#### class `FMediaSoundComponentVisualizer`  
`class FMediaSoundComponentVisualizer : public TAttenuatedComponentVisualizer<UMediaSoundComponent>`  
_L12-21_
- inherits: `TAttenuatedComponentVisualizer<UMediaSoundComponent>`
- desc: Visualizer for media sound components.
- L17 _private function_ `virtual bool IsVisualizerEnabled(const FEngineShowFlags& ShowFlags) const override`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaControls.h` (Private)


#### class `SMediaControls`  
`class SMediaControls : public SCompoundWidget`  
_L13-66_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SMediaControls)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FUICommandList> InCommandList, UMediaPlayer* InMediaPlayer);`
- L23 _protected member_ `TWeakPtr<FUICommandList> CommandListWeak;`
- L24 _protected member_ `TWeakObjectPtr<UMediaPlayer> PlayerWeak;`
- L26 _protected prototype_ `TSharedRef<SWidget> CreateControls();`
- L28 _protected prototype_ `bool PreviousMedia_IsEnabled() const;`
- L29 _protected prototype_ `FReply PreviousMedia_OnClicked();`
- L31 _protected prototype_ `bool Rewind_IsEnabled() const;`
- L32 _protected prototype_ `FReply Rewind_OnClicked();`
- L34 _protected prototype_ `bool PlayReverse_IsEnabled() const;`
- L35 _protected prototype_ `const FSlateBrush* PlayReverse_GetBrush() const;`
- L36 _protected prototype_ `FText PlayReverse_GetToolTip() const;`
- L37 _protected prototype_ `FReply PlayReverse_OnClicked();`
- L39 _protected prototype_ `bool Reverse_IsEnabled() const;`
- L40 _protected prototype_ `FReply Reverse_OnClicked();`
- L42 _protected prototype_ `bool StepBack_IsEnabled() const;`
- L43 _protected prototype_ `FReply StepBack_OnClicked();`
- L45 _protected prototype_ `bool Play_IsEnabled() const;`
- L46 _protected prototype_ `const FSlateBrush* Play_GetBrush() const;`
- L47 _protected prototype_ `FText Play_GetToolTip() const;`
- L48 _protected prototype_ `FReply Play_OnClicked();`
- L50 _protected prototype_ `bool StepForwardMedia_IsEnabled() const;`
- L51 _protected prototype_ `FReply StepForwardMedia_OnClicked();`
- L53 _protected prototype_ `bool Forward_IsEnabled() const;`
- L54 _protected prototype_ `FReply Forward_OnClicked();`
- L56 _protected prototype_ `bool JumpToEndMedia_IsEnabled() const;`
- L57 _protected prototype_ `FReply JumpToEndMedia_OnClicked();`
- L59 _protected prototype_ `bool NextMedia_IsEnabled() const;`
- L60 _protected prototype_ `FReply NextMedia_OnClicked();`
- L62 _protected prototype_ `bool OpenCloseMedia_IsEnabled() const;`
- L63 _protected prototype_ `const FSlateBrush* OpenCloseMedia_GetBrush() const;`
- L64 _protected prototype_ `FText OpenCloseMedia_GetToolTip() const;`
- L65 _protected prototype_ `FReply OpenCloseMedia_OnClicked();`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorCache.h` (Private)


#### class `SMediaPlayerEditorCache`  
`class SMediaPlayerEditorCache : public SLeafWidget`  
_L20-90_
- inherits: `SLeafWidget`
- desc: Implements the media player cache status visualizer widget.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorCache) : _PositionMarkerMargin(2.0f) , _PositionMarkerSize(2.0f) , _ProgressBarHeight(10.0f)`
- L32 _public prototype_ `SLATE_ATTRIBUTE(float, PositionMarkerMargin) SLATE_ATTRIBUTE(float, PositionMarkerSize) SLATE_ARGUMENT(float, ProgressBarHeight) SLATE_END_ARGS() SMediaPlayerEditorCache();` — Top margin of the position marker (in pixels).
- L54 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The UMediaPlayer asset to show the details for. @param InStyle The style set to use.
- L60 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L61 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L66 _protected prototype_ `void DrawPlayerPosition(FTimespan Time, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, const FLinearColor& Color) const;` — Draw the media player's current play head position.
- L69 _protected prototype_ `void DrawSampleCache(EMediaTrackType TrackType, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, float YPos, float YScale) const;` — Draw the caching state of the specified track type.
- L72 _protected prototype_ `void DrawSampleStates(const TRangeSet<FTimespan>& RangeSet, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, const FLinearColor& Color, float YPos, float YScale) const;` — Draw the caching state of the given media samples.
- L77 _private member_ `UMediaPlayer* MediaPlayer;` — The media player whose video texture is shown in this widget.
- L80 _private member_ `TAttribute<float> PositionMarkerMargin;` — Top margin of the position marker (in pixels).
- L83 _private member_ `TAttribute<float> PositionMarkerSize;` — Size of the position marker (in pixels).
- L86 _private member_ `TAttribute<float> ProgressBarHeight;` — Height of the progress bar (in pixels).
- L89 _private member_ `TSharedPtr<ISlateStyle> Style;` — The style set to use for this widget.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorDetails.h` (Private)


#### class `SMediaPlayerEditorDetails`  
`class SMediaPlayerEditorDetails : public SCompoundWidget`  
_L15-38_
- inherits: `SCompoundWidget`
- desc: Implements the details panel of the MediaPlayer asset editor.
- L20 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorDetails)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The MediaPlayer asset to show the details for. @param InStyleSet The style set to use.
- L37 _private member_ `UMediaPlayer* MediaPlayer;` — Pointer to the MediaPlayer asset that is being viewed.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorInfo.h` (Private)


#### class `SMediaPlayerEditorInfo`  
`class SMediaPlayerEditorInfo : public SCompoundWidget`  
_L17-48_
- inherits: `SCompoundWidget`
- desc: Implements the info panel of the MediaPlayer asset editor.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorInfo)`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The MediaPlayer asset to show the information for. @param InStyleSet The style set to use.
- L39 _private prototype_ `void HandleMediaPlayerMediaEvent(EMediaEvent Event);` — Callback for events from the media player.
- L44 _private member_ `TSharedPtr<STextBlock> InfoTextBlock;` — Text block for media information.
- L47 _private member_ `UMediaPlayer* MediaPlayer;` — Pointer to the MediaPlayer asset that is being viewed.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorMedia.h` (Private)


#### class `SMediaPlayerEditorMedia`  
`class SMediaPlayerEditorMedia : public SCompoundWidget`  
_L18-72_
- inherits: `SCompoundWidget`
- desc: Implements the media library of the MediaPlayer asset editor.
- L23 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorMedia)`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The MediaPlayer asset to show the details for. @param InStyleSet The style set to use.
- L38 _public prototype_ `static void RegisterMenus();` — Register menus associated with this widget
- L45 _public prototype_ `void OpenMediaAsset(UObject* Asset);` — Open an asset in the media player. @param Asset The asset to open.
- L49 _protected prototype_ `static void ShowMediaOpenFailedMessage();` — Show a message box for media opening failures.
- L54 _private prototype_ `void HandleAssetPickerAssetDoubleClicked(const struct FAssetData& AssetData);` — Callback for double-clicking an asset in the asset picker.
- L57 _private prototype_ `void HandleAssetPickerAssetEnterPressed(const TArray<FAssetData>& SelectedAssets);` — Callback for pressing Enter on a selected asset in the asset picker.
- L60 _private prototype_ `TSharedPtr<SWidget> HandleAssetPickerGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets);` — Callback for getting the context menu of an asset in the asset picker.
- L65 _private member_ `UMediaPlayer* MediaPlayer;` — Pointer to the MediaPlayer asset that is being viewed.
- L68 _private member_ `TSharedPtr<ISlateStyle> Style;` — The widget style set to use.
- L71 _private member_ `static const FName AssetPickerAssetContextMenuName;` — Name of the asset picker asset context menu

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorOutput.h` (Private)


#### class `SMediaPlayerEditorOutput`  
`class SMediaPlayerEditorOutput : public SCompoundWidget`  
_L29-109_
- inherits: `SCompoundWidget`
- desc: Handles content output in the viewer tab in the UMediaPlayer asset editor.
- L34 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorOutput)`
- L40 _public prototype_ `SMediaPlayerEditorOutput();` — Default constructor.
- L43 _public prototype_ `~SMediaPlayerEditorOutput();` — Destructor.
- L55 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, UMediaTexture* InMediaTexture, bool bInIsSoundEnabled);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The UMediaPlayer asset to show the details for. @param InMediaTexture The UMediaTexture asset to output video to. If nullptr then use our own. @param bInIsSoundEnabled If true then produce sound.
- L61 _public prototype_ `MediaPlayerEditor::MediaImage::ETextureChannelMask GetChannelMask() const;` — Returns the active mask.
- L70 _public prototype_ `void SetChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InMask);` — Sets a channel-based mask for the image. If only a single channel is displayed, it will show in greyscale. @param InMask to display.
- L76 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L81 _private prototype_ `void HandleMediaPlayerMediaEvent(EMediaEvent Event);` — Callback for media events from the media player.
- L86 _private member_ `TWeakObjectPtr<UMediaPlayer> MediaPlayer;` — The media player whose video texture is shown in this widget.
- L89 _private member_ `UMediaTexture* MediaTexture;` — The media texture to render the media player's video output.
- L92 _private member_ `UMediaSoundComponent* SoundComponent;` — The sound component to play the media player's audio output.
- L95 _private member_ `bool bIsOurMediaTexture;` — If true then we created MediaTexture and need to clean it up when we are done.
- L98 _private member_ `TSharedPtr<SMediaImage> MediaImage;` — The image widget displaying the media.
- L105 _private member_ `TSharedPtr<UE::MediaPlayerEditor::FViewportTileVisibilityProvider, ESPMode::ThreadSafe> TileVisibilityProvider;` — Tile-visibility provider that tells tiled-media readers (e.g. ImgMedia EXR sequences) to load only the tiles needed for this widget's on-screen pixel area. Owned here, held weakly by the per-loader resolver. Reset in the destructor before unregistering.
- L108 _private member_ `TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe> TextureTrackerObject;` — FMediaTextureTracker bookkeeping for our provider. Registered against MediaTexture.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MediaPlayerEditor` (scope `UE`)

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorOverlay.h` (Private)


#### class `SMediaPlayerEditorOverlay`  
`class SMediaPlayerEditorOverlay : public SCompoundWidget`  
_L17-56_
- inherits: `SCompoundWidget`
- desc: Draws text overlays for the UMediaPlayer asset editor.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorOverlay)`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The UMediaPlayer asset to show the details for.
- L39 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L45 _private member_ `TPimplPtr<FConfig> Configuration;`
- L48 _private member_ `TSharedPtr<SConstraintCanvas> Canvas;` — The canvas to draw into.
- L51 _private member_ `UMediaPlayer* MediaPlayer;` — The media player whose video texture is shown in this widget.
- L55 _private member_ `TSharedPtr<FInternal, ESPMode::ThreadSafe> Internal;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorPlaylist.h` (Private)


#### class `SMediaPlayerEditorPlaylist`  
`class SMediaPlayerEditorPlaylist : public SCompoundWidget`  
_L20-76_
- inherits: `SCompoundWidget`
- desc: Implements the play list of the MediaPlayer asset editor.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorPlaylist)`
- L31 _public prototype_ `SMediaPlayerEditorPlaylist();` — Default constructor.
- L34 _public prototype_ `~SMediaPlayerEditorPlaylist();` — Destructor.
- L45 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The MediaPlayer asset to show the details for. @param InStyleSet The style set to use.
- L50 _protected prototype_ `void ReloadMediaSourceList();` — Reload the list of media sources in the play list.
- L55 _private prototype_ `void HandleCoreObjectPropertyChanged(UObject* Object, struct FPropertyChangedEvent& ChangedEvent);` — Callback for when a UObject property has changed (used to monitor play list changed).
- L58 _private prototype_ `void HandleMediaPlayerMediaEvent(EMediaEvent Event);` — Callback for media player events.
- L61 _private prototype_ `FReply HandleSavePlaylistButtonClicked();` — Callback for clicking the Save button.
- L66 _private member_ `UMediaPlayer* MediaPlayer;` — Pointer to the MediaPlayer asset that is being viewed.
- L69 _private member_ `TArray<TSharedPtr<FMediaSourceTableEntry>> MediaSourceList;` — The list of media sources in the current play list.
- L72 _private member_ `TSharedPtr<SListView<TSharedPtr<FMediaSourceTableEntry>>> MediaSourceListView;` — Media source list view.
- L75 _private member_ `TSharedPtr<ISlateStyle> Style;` — The widget style to use.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorStats.h` (Private)


#### class `SMediaPlayerEditorStats`  
`class SMediaPlayerEditorStats : public SCompoundWidget`  
_L16-47_
- inherits: `SCompoundWidget`
- desc: Implements the stats panel of the MediaPlayer asset editor.
- L21 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorStats)`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The MediaPlayer asset to show the information for. @param InStyleSet The style set to use.
- L38 _private prototype_ `FText HandleStatsTextBlockText() const;` — Callback for getting the text of the statistics text block.
- L43 _private member_ `UMediaPlayer* MediaPlayer;` — Pointer to the MediaPlayer asset that is being viewed.
- L46 _private member_ `TSharedPtr<STextBlock> StatsTextBlock;` — Text block for media statistics.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerEditorViewport.h` (Private)


#### class `SMediaPlayerEditorViewport`  
`class SMediaPlayerEditorViewport : public SCompoundWidget`  
_L17-105_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorViewport)`
- L28 _public prototype_ `SMediaPlayerEditorViewport();` — Default constructor.
- L42 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, UMediaTexture* InMediaTexture, const TSharedRef<ISlateStyle>& InStyle, bool bInIsSoundEnabled, TSharedPtr<FUICommandList> InCommands);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The UMediaPlayer asset to show the details for. @param InMediaTexture The UMediaTexture asset to output video to. If nullptr then use our own. @param InStyle The style set to use. @param bInIsSoundEnabled If true then produce sound. @param InCommands Command list for keybinds.
- L49 _public function_ `void EnableMouseControl(bool bIsEnabled)` — Enables/disables using the mouse to control the viewport.
- L54 _public prototype_ `MediaPlayerEditor::MediaImage::ETextureChannelMask GetChannelMask() const;` — Returns the active mask.
- L63 _public prototype_ `void SetChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InMask);` — Sets a channel-based mask for the image. If only a single channel is displayed, it will show in greyscale. @param InMask to display.
- L69 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L70 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L75 _private prototype_ `FText HandleMediaPlayerNameText() const;` — Callback for getting the text of the player name overlay.
- L78 _private prototype_ `FText HandleMediaPlayerStateText() const;` — Callback for getting the text of the playback state overlay.
- L81 _private prototype_ `FText HandleMediaSourceNameText() const;` — Callback for getting the text of the media source name overlay.
- L84 _private prototype_ `FText HandleNotificationText() const;` — Callback for getting the text of the notification overlay.
- L87 _private prototype_ `const FSlateBrush* GetMediaBorderImage() const;` — Returns the image used for the background of the media.
- L92 _private member_ `UMediaPlayer* MediaPlayer;` — Pointer to the media player that is being viewed.
- L95 _private member_ `TSharedPtr<ISlateStyle> Style;` — The style set to use for this widget.
- L98 _private member_ `bool bIsMouseControlEnabled;` — True if the mouse can control things.
- L101 _private member_ `TSharedPtr<SMediaPlayerEditorOutput> Output;` — The output for the media player.
- L104 _private member_ `TWeakPtr<FUICommandList> CommandsWeak;` — Command list for executing commands.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlayerSlider.h` (Private)


#### class `SMediaPlayerSlider`  
`class SMediaPlayerSlider : public IMediaPlayerSlider`  
_L19-78_
- inherits: `IMediaPlayerSlider`
- desc: Implements a scrubber to visualize the current playback position of a Media Player and interact with it.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerSlider) : _Style(&FCoreStyle::Get().GetWidgetStyle<FSliderStyle>("Slider"))`
- L28 _public prototype_ `SLATE_STYLE_ARGUMENT(FSliderStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArrayView<TWeakObjectPtr<UMediaPlayer>> InMediaPlayers);` — The Slider style used to draw the scrubber.
- L35 _public prototype_ `virtual void SetSliderHandleColor(const FSlateColor& InSliderColor) override;`
- L36 _public prototype_ `virtual void SetSliderBarColor(const FSlateColor& InSliderColor) override;`
- L37 _public prototype_ `virtual void SetVisibleWhenInactive(EVisibility InVisibility) override;`
- L38 _public prototype_ `virtual FScrubEvent::RegistrationType& GetScrubEvent() override;`
- L42 _private prototype_ `bool DoesMediaPlayerSupportSeeking() const;`
- L43 _private prototype_ `void OnScrubBegin();`
- L44 _private prototype_ `void OnScrubEnd();`
- L45 _private prototype_ `void Seek(float InPlaybackPosition);`
- L46 _private prototype_ `float GetPlaybackPosition() const;`
- L47 _private prototype_ `EVisibility GetScrubberVisibility() const;`
- L48 _private prototype_ `float GetSliderValue() const;`
- L51 _private member_ `EVisibility VisibilityWhenInactive = EVisibility::Hidden;` — The scrubber visibility when inactive.
- L69 _private prototype_ `const FMediaPlayerEntry* FindValidPlayerEntryForTrackType(EMediaPlayerTrack InTrackType) const;`
- L71 _private member_ `TArray<FMediaPlayerEntry> MediaPlayerEntries;`
- L74 _private member_ `TSharedPtr<SSlider> ScrubberSlider;` — Holds the scrubber slider.
- L77 _private member_ `IMediaPlayerSlider::FScrubEvent ScrubEvent;` — Event subscribers can use to detect scrubbing.

#### struct `SMediaPlayerSlider::FMediaPlayerEntry`  
`struct FMediaPlayerEntry`  
_L53-67_
- L56 _public member_ `TWeakObjectPtr<UMediaPlayer> MediaPlayerWeak;` — Pointer to the media players that is are viewed.
- L59 _public member_ `float PreScrubRate = 0.0f;` — The playback rate prior to scrubbing.
- L61 _public member_ `float ScrubValue = 0.0f;` — The value currently being scrubbed to.
- L64 _public member_ `float LastScrubValue = -1.0f;` — The last value set with media player while scrubbing.
- L66 _public function_ `FMediaPlayerEntry(const TWeakObjectPtr<UMediaPlayer>& InMediaPlayerWeak) : MediaPlayerWeak(InMediaPlayerWeak)`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlaylistEditorDetails.h` (Private)


#### class `SMediaPlaylistEditorDetails`  
`class SMediaPlaylistEditorDetails : public SCompoundWidget`  
_L15-38_
- inherits: `SCompoundWidget`
- desc: Implements the details panel of the MediaPlaylist asset editor.
- L20 _public function_ `SLATE_BEGIN_ARGS(SMediaPlaylistEditorDetails)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlaylist& InMediaPlaylist, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlaylist The MediaPlaylist asset to show the details for. @param InStyleSet The style set to use.
- L37 _private member_ `UMediaPlaylist* MediaPlaylist;` — Pointer to the MediaPlaylist asset that is being viewed.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaPlaylistEditorMedia.h` (Private)


#### class `SMediaPlaylistEditorMedia`  
`class SMediaPlaylistEditorMedia : public SCompoundWidget`  
_L15-43_
- inherits: `SCompoundWidget`
- desc: Implements the media library of the MediaPlaylist asset editor.
- L20 _public function_ `SLATE_BEGIN_ARGS(SMediaPlaylistEditorMedia)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlaylist& InMediaPlaylist, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlaylist The MediaPlaylist asset to show the details for. @param InStyleSet The style set to use.
- L37 _private prototype_ `void HandleAssetPickerAssetDoubleClicked(const struct FAssetData& AssetData);` — Callback for double-clicking an asset in the asset picker.
- L42 _private member_ `UMediaPlaylist* MediaPlaylist;` — Pointer to the MediaPlaylist asset that is being viewed.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaSourceEditorDetails.h` (Private)


#### class `SMediaSourceEditorDetails`  
`class SMediaSourceEditorDetails : public SCompoundWidget`  
_L14-37_
- inherits: `SCompoundWidget`
- desc: Implements the details panel of the MediaSource asset editor.
- L19 _public function_ `SLATE_BEGIN_ARGS(SMediaSourceEditorDetails)`
- L31 _public prototype_ `void Construct(const FArguments& InArgs, UMediaSource& InMediaSource, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget. @param InArgs		The declaration data for this widget. @param InMediaSource	The MediaSource to show the details for. @param InStyleSet	The style set to use.
- L36 _private member_ `TObjectPtr<UMediaSource> MediaSource;` — Pointer to the MediaPlate that is being viewed.

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Widgets/SMediaSourceTableRow.h` (Private)


#### struct `FMediaSourceTableEntry`  
`struct FMediaSourceTableEntry`  
_L21-34_
- L24 _public member_ `int32 Index;` — The media source's index in the table.
- L27 _public member_ `TWeakObjectPtr<UMediaSource> MediaSource;` — The media source.
- L30 _public function_ `FMediaSourceTableEntry(int32 InIndex, UMediaSource* InMediaSource) : Index(InIndex) , MediaSource(InMediaSource)` — Create and initialize a new instance.

#### class `SMediaSourceTableRow`  
`class SMediaSourceTableRow : public SMultiColumnTableRow<TSharedPtr<FMediaSourceTableEntry>>`  
_L40-127_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMediaSourceTableEntry>>`
- desc: Implements a row widget in a media source list.
- L45 _public function_ `SLATE_BEGIN_ARGS(SMediaSourceTableRow)`
- L59 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)` — Constructs the widget. @param InArgs The construction arguments. @param InOwnerTableView The table view that owns this row.
- L76 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override`
- L120 _private member_ `TSharedPtr<FMediaSourceTableEntry> Entry;` — The table entry being shown in this row.
- L123 _private member_ `TAttribute<bool> Opened;` — Whether the media source shown in this row is currently opened in a media player.
- L126 _private member_ `TSharedPtr<ISlateStyle> Style;` — The widget's visual style.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "SMediaSourceTableRow"`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/AssetDefinition/AssetDefinition_MediaSource.h` (Public)


#### class `UAssetDefinition_MediaSource`  
`class UAssetDefinition_MediaSource : public UAssetDefinitionDefault`  
_L9-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L15 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/AssetTools/MediaSourceActions.h` (Public)


#### class `FMediaSourceActions`  
`class FMediaSourceActions : public FAssetTypeActions_Base`  
_L17-33_
- inherits: `FAssetTypeActions_Base`
- desc: Implements an action for UMediaSource assets.
- L24 _public prototype_ `virtual bool CanFilter() override;`
- L25 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L26 _public prototype_ `virtual uint32 GetCategories() override;`
- L27 _public prototype_ `virtual FText GetName() const override;`
- L28 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L29 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L30 _public prototype_ `virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`
- L32 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/MediaPlayerEditorModule.h` (Public)


#### class `IMediaPlayerSlider`  
`class IMediaPlayerSlider : public SCompoundWidget`  
_L17-44_
- inherits: `SCompoundWidget`
- desc: Interface for MediaPlayer Playback Scrubber Widget
- L21 _public prototype_ `virtual void SetSliderHandleColor(const FSlateColor& InSliderColor) = 0;` — Set the Scrubber Slider Handle Color
- L24 _public prototype_ `virtual void SetSliderBarColor(const FSlateColor& InSliderColor) = 0;` — Set the Scrubber Slider Color
- L27 _public prototype_ `virtual void SetVisibleWhenInactive(EVisibility InVisibility) = 0;` — Set the Scrubber Slider Visibility, when the player is inactive
- L40 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FScrubEvent, EScrubEventType , TConstArrayView<UMediaPlayer*> , float ) virtual FScrubEvent::RegistrationType& GetScrubEvent() = 0;`

#### enum `IMediaPlayerSlider::EScrubEventType`  
`enum class EScrubEventType : uint8`  
_L30-38_
- desc: When scrubbing of the created slider occurs, this enum is used in FScrubEvent to inform subscribers about the slider state.
- L33 _public enumerator_ `Begin` — Scrubbing has started.
- L35 _public enumerator_ `Update` — Scrubbing is ongoing and the position of the scrub has changed.
- L37 _public enumerator_ `End` — Scrubbing has stopped.

#### class `IMediaPlayerEditorModule`  
`class IMediaPlayerEditorModule : public IModuleInterface`  
_L49-73_
- inherits: `IModuleInterface`
- desc: Interface for the MediaPlayerEditor module.
- L55 _public prototype_ `virtual TSharedPtr<ISlateStyle> GetStyle() = 0;` — Get the style used by this module.
- L64 _public prototype_ `virtual TSharedRef<IMediaPlayerSlider> CreateMediaPlayerSliderWidget(UMediaPlayer* InMediaPlayer, const FSliderStyle& InStyle = FCoreStyle::Get().GetWidgetStyle<FSliderStyle>("Slider")` — `UE_DEPRECATED(5.5, "Use version with TArrayView instead")` — Creates a Widget to visualize playback time and scrub the content played by a Media Player @param InMediaPlayer: the player affected by the widget @param InStyle: the style chosen for this slider widget @return Scrubber Widget
- L72 _public prototype_ `virtual TSharedRef<IMediaPlayerSlider> CreateMediaPlayerSliderWidget(const TArrayView<TWeakObjectPtr<UMediaPlayer>> InMediaPlayers, const FSliderStyle& InStyle = FCoreStyle::Get().GetWidgetStyle<FSliderStyle>("Slider")` — Creates a Widget to visualize playback time and scrub the content played by Media Players @param InMediaPlayers: the players affected by the widget @param InStyle: the style chosen for this slider widget @return Scrubber Widget

#### Free symbols / members of external scopes

- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FScrubEvent, EScrubEventType , TConstArrayView<UMediaPlayer*> , float ) virtual FScrubEvent::RegistrationType& GetScrubEvent() = 0;`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/Models/MediaPlayerEditorCommands.h` (Public)


#### class `FMediaPlayerEditorCommands`  
`class FMediaPlayerEditorCommands : public TCommands<FMediaPlayerEditorCommands>`  
_L13-91_
- inherits: `TCommands<FMediaPlayerEditorCommands>`
- desc: Holds the UI commands for the MediaPlayerEditorToolkit widget.
- L17 _public prototype_ `static const FMediaPlayerEditorCommands& GetExternal();`
- L20 _public function_ `FMediaPlayerEditorCommands() : TCommands<FMediaPlayerEditorCommands>("MediaPlayerEditor", NSLOCTEXT("Contexts", "MediaPlayerEditor", "MediaPlayer Editor"), NAME_None, "MediaPlayerEditorStyle")` — Default constructor.
- L28 _public prototype_ `virtual void RegisterCommands() override;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> CloseMedia;` — Close the currently opened media.
- L36 _public member_ `TSharedPtr<FUICommandInfo> ForwardMedia;` — Plays media forward at ever increasing speed.
- L39 _public member_ `TSharedPtr<FUICommandInfo> GenerateThumbnail;` — Generate a thumnbnail.
- L42 _public member_ `TSharedPtr<FUICommandInfo> NextMedia;` — Jump to next item in the play list.
- L45 _public member_ `TSharedPtr<FUICommandInfo> OpenMedia;` — Open the current media.
- L48 _public member_ `TSharedPtr<FUICommandInfo> PauseMedia;` — Pauses media playback.
- L51 _public member_ `TSharedPtr<FUICommandInfo> PlayMedia;` — Starts media playback.
- L54 _public member_ `TSharedPtr<FUICommandInfo> PlayReverseMedia;` — Starts media playback in reverse.
- L57 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayPauseMedia;` — Toggles between media play and pause.
- L60 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayReversePauseMedia;` — Toggles between media reverse play and pause.
- L63 _public member_ `TSharedPtr<FUICommandInfo> PreviousMedia;` — Jump to previous item in the play list.
- L66 _public member_ `TSharedPtr<FUICommandInfo> ReverseMedia;` — Reverses media playback at ever increasing speed.
- L69 _public member_ `TSharedPtr<FUICommandInfo> RewindMedia;` — Rewinds the media to the beginning.
- L72 _public member_ `TSharedPtr<FUICommandInfo> JumpToEndMedia;` — Fast forwards the media to the end.
- L75 _public member_ `TSharedPtr<FUICommandInfo> StepForwardMedia;` — Step forward media 1 frame
- L78 _public member_ `TSharedPtr<FUICommandInfo> StepBackwardMedia;` — Step backward media 1 frame.
- L81 _public member_ `TSharedPtr<FUICommandInfo> ToggledRedTextureChannel;` — Toggles red texture channel.
- L84 _public member_ `TSharedPtr<FUICommandInfo> ToggledGreenTextureChannel;` — Toggles green texture channel.
- L87 _public member_ `TSharedPtr<FUICommandInfo> ToggledBlueTextureChannel;` — Toggles blue texture channel.
- L90 _public member_ `TSharedPtr<FUICommandInfo> ToggledAlphaTextureChannel;` — Toggles alpha texture channel.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/Widgets/SMediaImage.h` (Public)


#### enum `MediaPlayerEditor::MediaImage::ETextureChannelMask`  
`enum class ETextureChannelMask : uint8`  
_L21-30_
- L23 _public enumerator_ `None = 0`
- L24 _public enumerator_ `Red = 1 << 0`
- L25 _public enumerator_ `Green = 1 << 1`
- L26 _public enumerator_ `Blue = 1 << 2`
- L27 _public enumerator_ `Alpha = 1 << 3`
- L28 _public enumerator_ `RGB = Red | Green | Blue`
- L29 _public enumerator_ `RGBA = Red | Green | Blue | Alpha`

#### class `SMediaImage`  
`class SMediaImage : public SCompoundWidget`  
_L35-97_
- inherits: `SCompoundWidget`
- L38 _public function_ `SLATE_BEGIN_ARGS(SMediaImage)`
- L39 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, BrushImageSize);`
- L45 _public prototype_ `SMediaImage();` — Default constructor.
- L55 _public prototype_ `void Construct(const FArguments& InArgs, UTexture* InTexture);` — Construct this widget @param InArgs The declaration data for this widget. @param InTexture The source texture to render if any
- L64 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Tick this widget @param InAllottedGeometry Geometry of the widget. @param InCurrentTime CurrentTime of the engine. @param InDeltaTime Deltatime since last frame.
- L69 _public prototype_ `MediaPlayerEditor::MediaImage::ETextureChannelMask GetChannelMask() const;` — Returns the active mask.
- L78 _public prototype_ `void SetChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InMask);` — Sets a channel-based mask for the image. If only a single channel is displayed, it will show in greyscale. @param InMask to display.
- L81 _private member_ `static TMap<MediaPlayerEditor::MediaImage::ETextureChannelMask, TStrongObjectPtr<UMaterial>> CachedMaterials;`
- L84 _private member_ `TStrongObjectPtr<UMaterialInstanceDynamic> MaterialAInstance;` — The Slate brush that renders the material and its nodes.
- L87 _private member_ `TSharedPtr<FSlateBrush> MaterialBrush;` — The brush used to render the media.
- L90 _private member_ `TAttribute<FVector2D> BrushImageSize;` — Brush image size attribute.
- L93 _private member_ `TWeakObjectPtr<UTexture> TextureWeak;` — The texture being displayed
- L96 _private member_ `MediaPlayerEditor::MediaImage::ETextureChannelMask Mask;` — The active mask

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`
- L17 _namespace_ `namespace MediaPlayerEditor`
- L19 _namespace_ `namespace MediaImage` (scope `MediaPlayerEditor`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(ETextureChannelMask);` (scope `MediaPlayerEditor::MediaImage`)

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/Widgets/SMediaImageTextureChannelToggle.h` (Public)


#### class `SMediaImageTextureChannelToggle`  
`class SMediaImageTextureChannelToggle : public SCompoundWidget`  
_L18-49_
- inherits: `SCompoundWidget`
- desc: Implements a button to toggle the contents of a texture channel for the SMediaPlayerEditorViewer
- L22 _public function_ `SLATE_BEGIN_ARGS(SMediaImageTextureChannelToggle)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SMediaPlayerEditorViewer> InViewer, MediaPlayerEditor::MediaImage::ETextureChannelMask InChannel, TSharedPtr<FUICommandList> InCommandList);`
- L36 _private member_ `TWeakPtr<SMediaPlayerEditorViewer> ViewerWeak;`
- L37 _private member_ `MediaPlayerEditor::MediaImage::ETextureChannelMask Channel;`
- L38 _private member_ `TWeakPtr<FUICommandList> CommandListWeak;`
- L40 _private prototype_ `FSlateColor GetChannelButtonBackgroundColor() const;`
- L42 _private prototype_ `FSlateColor GetChannelButtonForegroundColor() const;`
- L44 _private prototype_ `ECheckBoxState OnGetChannelButtonCheckState() const;`
- L46 _private prototype_ `bool IsChannelButtonEnabled() const;`
- L48 _private prototype_ `void OnChannelButtonCheckStateChanged(ECheckBoxState InNewState);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/Widgets/SMediaPlayerEditorMediaDetails.h` (Public)


#### class `SMediaPlayerEditorMediaDetails`  
`class SMediaPlayerEditorMediaDetails : public SCompoundWidget`  
_L18-75_
- inherits: `SCompoundWidget`
- desc: Implements the media details panel of the MediaPlayer asset editor.
- L23 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorMediaDetails)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer* InMediaPlayer, UMediaTexture* InMediaTexture, FName InTextStyleName = NAME_None);` — Construct this widget. @param InArgs			The declaration data for this widget. @param InMediaPlayer		The MediaPlayer to show the details for. @param InMediaTexture	The MediaTexture to show the details for. @param InTextStyleName	The text style name to use.
- L40 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L44 _protected prototype_ `virtual UMediaPlayer* GetMediaPlayer() const;` — Accessor for media player.
- L47 _protected prototype_ `virtual UMediaTexture* GetMediaTexture() const;` — Accessor for the media texture.
- L54 _private prototype_ `void UpdateDetails();` — Updates our widgets to reflect the current state.
- L57 _private member_ `TWeakObjectPtr<UMediaPlayer> MediaPlayerWeak;` — Pointer to the MediaPlayer that is being viewed.
- L59 _private member_ `TWeakObjectPtr<UMediaTexture> MediaTextureWeak;` — Pointer to the MediaTexture that is being viewed.
- L62 _private member_ `TSharedPtr<STextBlock> MediaPlayerName;` — Our widgets.
- L63 _private member_ `TSharedPtr<STextBlock> FormatText;`
- L64 _private member_ `TSharedPtr<STextBlock> FrameRateText;`
- L65 _private member_ `TSharedPtr<STextBlock> LODBiasText;`
- L66 _private member_ `TSharedPtr<STextBlock> MethodText;`
- L67 _private member_ `TSharedPtr<STextBlock> NumMipsText;`
- L68 _private member_ `TSharedPtr<STextBlock> NumTilesText;`
- L69 _private member_ `TSharedPtr<STextBlock> ResolutionText;`
- L70 _private member_ `TSharedPtr<STextBlock> ResourceSizeText;`
- L71 _private member_ `TSharedPtr<STextBlock> StartTimecodeText;`
- L72 _private member_ `TSharedPtr<STextBlock> SeekPerformance;`
- L73 _private member_ `TSharedPtr<STextBlock> VideoDecoderProvider;`
- L74 _private member_ `TSharedPtr<STextBlock> AudioDecoderProvider;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/Widgets/SMediaPlayerEditorViewer.h` (Public)


#### class `SMediaPlayerEditorViewer`  
`class SMediaPlayerEditorViewer : public SCompoundWidget`  
_L32-196_
- inherits: `SCompoundWidget`
- desc: Implements the contents of the viewer tab in the UMediaPlayer asset editor.
- L37 _public function_ `SLATE_BEGIN_ARGS(SMediaPlayerEditorViewer) : _bShowUrl(true)`
- L51 _public prototype_ `SMediaPlayerEditorViewer();` — Default constructor.
- L54 _public prototype_ `~SMediaPlayerEditorViewer();` — Destructor.
- L67 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlayer& InMediaPlayer, UMediaTexture* InMediaTexture, const TSharedRef<ISlateStyle>& InStyle, bool bInIsSoundEnabled);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlayer The UMediaPlayer asset to show the details for. @param InMediaTexture The UMediaTexture asset to output video to. If nullptr then use our own. @param InStyle The style set to use. @param bInIsSoundEnabled If true then produce sound.
- L71 _public prototype_ `UMediaPlayer* GetMediaPlayer() const;`
- L76 _public prototype_ `void EnableMouseControl(bool bIsEnabled);` — Enables/disables using the mouse to control the viewport.
- L81 _public prototype_ `MediaPlayerEditor::MediaImage::ETextureChannelMask GetChannelMask() const;` — Returns the active mask.
- L86 _public prototype_ `bool IsChannelMasked(MediaPlayerEditor::MediaImage::ETextureChannelMask InChannel) const;` — Returns true if all the given channel mask is enabled.
- L95 _public prototype_ `void SetChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InMask);` — Sets a channel-based mask for the image. If only a single channel is displayed, it will show in greyscale. @param InMask to display.
- L100 _public prototype_ `void ToggleChannelMask(MediaPlayerEditor::MediaImage::ETextureChannelMask InChannelToToggle);` — Toggles the given mask in the channel mask.
- L106 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L107 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L108 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L109 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L119 _protected prototype_ `void MakeCaptureDeviceMenu(TArray<FMediaCaptureDeviceInfo>& DeviceInfos, FMenuBuilder& MenuBuilder);` — Populate a menu from the given capture device information. @param DeviceInfos The capture device information. @param MenuBuilder The builder for the menu.
- L122 _protected prototype_ `void OpenUrl(const FText& TextUrl);` — Open the specified media URL.
- L125 _protected prototype_ `void SetDesiredPlayerName(FName PlayerName);` — Set the name of the desired native media player.
- L130 _private prototype_ `void HandleAudioCaptureDevicesMenuNewMenu(FMenuBuilder& MenuBuilder);` — Callback for creating the audio capture devices sub-menu.
- L133 _private prototype_ `void HandleDecoderMenuNewMenu(FMenuBuilder& MenuBuilder);` — Callback for creating the player sub-menu.
- L136 _private prototype_ `FText HandleFpsTextBlockText() const;` — Callback for getting the text of the FPS text block.
- L139 _private prototype_ `void HandleFormatMenuNewMenu(FMenuBuilder& MenuBuilder, EMediaPlayerTrack TrackType);` — Callback for creating a track format sub-menu.
- L142 _private prototype_ `void HandleMediaPlayerMediaEvent(EMediaEvent Event);` — Callback for media player events.
- L145 _private prototype_ `void HandleScaleMenuNewMenu(FMenuBuilder& MenuBuilder);` — Callback for creating the Scale sub-menu.
- L148 _private prototype_ `FText HandleTimerTextBlockText() const;` — Callback for getting the text of the timer text block.
- L151 _private prototype_ `FText HandleTimerTextBlockToolTipText() const;` — Callback for getting the tool tip of the timer text block.
- L154 _private prototype_ `void HandleBackgroundMenuNewMenu(FMenuBuilder& MenuBuilder);` — Callback for creating the Background sub-menu.
- L157 _private prototype_ `void HandleTimerUnitMenuNewMenu(FMenuBuilder& MenuBuilder);` — Callback for creating the timer units sub-menu.
- L160 _private prototype_ `void HandleTrackMenuNewMenu(FMenuBuilder& MenuBuilder, EMediaPlayerTrack TrackType);` — Callback for creating a track sub-menu.
- L163 _private prototype_ `FReply HandleUrlBoxKeyDown(const FGeometry&, const FKeyEvent& KeyEvent);` — Callback for handling key down events in the URL text box.
- L166 _private prototype_ `void HandleVideoCaptureDevicesMenuNewMenu(FMenuBuilder& MenuBuilder);` — Callback for creating the video capture devices sub-menu.
- L169 _private prototype_ `TSharedRef<SWidget> CreatePlayerControls();` — Creates controls for the media
- L174 _private member_ `bool DragOver;` — Whether something is currently being dragged over the widget.
- L177 _private member_ `bool DragValid;` — Whether the dragged object is a media file that can be played.
- L180 _private member_ `FText LastUrl;` — The text that was last typed into the URL box.
- L183 _private member_ `UMediaPlayer* MediaPlayer;` — Pointer to the media player that is being viewed.
- L186 _private member_ `TSharedPtr<ISlateStyle> Style;` — The style set to use for this widget.
- L189 _private member_ `TSharedPtr<SEditableTextBox> UrlTextBox;` — Media URL text box.
- L192 _private member_ `TSharedPtr<SMediaPlayerEditorViewport> PlayerViewport;` — The viewport that shows the media.
- L195 _private member_ `TWeakPtr<FUICommandList> CommandListWeak;` — The controls that can be executed by this viewer.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`

### `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Public/Widgets/SMediaPlaylistEditorTracks.h` (Public)


#### class `SMediaPlaylistEditorTracks`  
`class SMediaPlaylistEditorTracks : public SCompoundWidget`  
_L18-90_
- inherits: `SCompoundWidget`
- desc: Implements the tracks view of the MediaPlaylist.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMediaPlaylistEditorTracks) : _ShowAddEntryButton(false)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, UMediaPlaylist* InMediaPlaylist, const TSharedRef<ISlateStyle>& InStyle);` — Construct this widget @param InArgs The declaration data for this widget. @param InMediaPlaylist The MediaPlaylist asset to show the details for. @param InStyleSet The style set to use.
- L44 _protected member_ `TWeakObjectPtr<UMediaPlaylist> MediaPlaylistPtr;` — Pointer to the MediaPlaylist asset that is being viewed.
- L46 _protected member_ `TSharedPtr<SVerticalBox> SourcesContainer;` — Pointer to the container for the media sources.
- L52 _protected member_ `bool bShowAddEntryButton = false;` — Flag to enable/disable a button which can be used to add items to the currently selected Playlist. Set by "ShowAddEntryButton" slate argument. If no Playlist is selected, button will be hidden anyway.
- L57 _protected prototype_ `void RefreshPlaylist();` — This should be called when the playlist changes so we can update the UI.
- L62 _protected prototype_ `void AddToPlaylist();` — Adds a blank entry to the playlist.
- L69 _protected prototype_ `FString GetMediaSourcePath(int32 Index) const;` — Gets the object path for the media source object. @param	Index		Index in the playlist of the media source object.
- L77 _protected prototype_ `void OnMediaSourceChanged(const FAssetData& AssetData, int32 Index);` — Called when the media source widget changes. @param	AssetData	The media source. @param	Index		Index in the playlist of the media source object.
- L80 _protected prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);` — Engine callback to detect when the media is changed.
- L83 _protected prototype_ `EVisibility GetAddEntryButtonVisibility() const;` — Returns the current visibility for the button used to add items to the currently selected Playlist, if any
- L86 _protected prototype_ `EVisibility GetSourcesContainerHeaderTextVisibility() const;` — Returns the current visibility of the header area (before or in place of the current Playlist items)
- L89 _protected prototype_ `FText GetSourcesContainerHeaderText() const;` — Returns the text to be displayed in the header area (before or in place of the current Playlist items)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIAPLAYEREDITOR_API`
