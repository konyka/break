# Plugins / MediaViewer

- module root: `Plugins/Media/MediaViewer/Source/MediaViewer`
- headers: 54; symbols: 1564
- symbol kinds: class=41, delegate=31, enum=11, enumerator=39, function=74, member=354, namespace=170, prototype=776, struct=55, typedef=6, variable=7
- PrivateDependencyModuleNames: CQTest

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/ColorImageViewer.h` (Private)


#### class `UE::MediaViewer::Private::FColorImageViewer`  
`class FColorImageViewer : public FMediaImageViewer`  
_L15-78_
- inherits: `FMediaImageViewer`
- L58 _public member_ `static const FLazyName ItemTypeName;`
- L60 _public prototype_ `FColorImageViewer();`
- L61 _public prototype_ `FColorImageViewer(const FLinearColor& InColor, const FText& InDisplayName);`
- L62 _public prototype_ `FColorImageViewer(const FGuid& InId, const FLinearColor& InColor, const FText& InDisplayName);`
- L64 _public prototype_ `virtual ~FColorImageViewer() = default;`
- L67 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L68 _public function_ `virtual bool SupportsMip() const override`
- L69 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L73 _public prototype_ `virtual FString GetReferencerName() const override;`
- L77 _protected member_ `static TSharedRef<FSlateColorBrush> ColorBrush;`

#### struct `UE::MediaViewer::Private::FColorImageViewer::FFactory`  
`struct FFactory : public IMediaImageViewerFactory`  
_L18-35_
- inherits: `IMediaImageViewerFactory`
- L20 _public function_ `FFactory()`
- L25 _public function_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const override`
- L26 _public function_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const override`
- L27 _public function_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override`
- L29 _public function_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const override`
- L30 _public function_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const override`
- L31 _public function_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override`
- L33 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const override;`
- L34 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const override;`

#### struct `UE::MediaViewer::Private::FColorImageViewer::FItem`  
`struct FItem : public FMediaViewerLibraryItem`  
_L37-56_
- inherits: `FMediaViewerLibraryItem`
- L39 _public prototype_ `static FLinearColor LoadFromString(const FString& InString);`
- L41 _public prototype_ `FItem(const FText& InName, const FText& InToolTip, const FLinearColor& InColor);`
- L43 _public prototype_ `FItem(const FGuid& InId, const FText& InName, const FText& InToolTip, const FLinearColor& InColor);`
- L45 _public prototype_ `FItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L47 _public prototype_ `virtual ~FItem() override = default;`
- L50 _public prototype_ `virtual FName GetItemType() const override;`
- L51 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L52 _public prototype_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail() override;`
- L53 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L54 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaViewer` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/LevelEditorViewportImageViewer.h` (Private)


#### class `UE::MediaViewer::Private::FLevelEditorViewportImageViewer`  
`class FLevelEditorViewportImageViewer : public FSceneViewportImageViewer`  
_L12-77_
- inherits: `FSceneViewportImageViewer`
- L61 _public member_ `static const FLazyName ItemTypeName;`
- L64 _public prototype_ `FLevelEditorViewportImageViewer(const FString& InStringValue);` — InStringValue should be Viewport0 to Viewport3
- L65 _public prototype_ `FLevelEditorViewportImageViewer(const FGuid& InId, const FString& InStringValue);`
- L68 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L72 _protected member_ `FString StringValue;`
- L75 _protected prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry) override;`

#### struct `UE::MediaViewer::Private::FLevelEditorViewportImageViewer::FFactory`  
`struct FFactory : public IMediaImageViewerFactory`  
_L15-32_
- inherits: `IMediaImageViewerFactory`
- L17 _public function_ `FFactory()`
- L22 _public function_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const override`
- L23 _public function_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const override`
- L24 _public function_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override`
- L26 _public function_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const override`
- L27 _public function_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const override`
- L28 _public function_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override`
- L30 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const override;`
- L31 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const override;`

#### struct `UE::MediaViewer::Private::FLevelEditorViewportImageViewer::FItem`  
`struct FItem : public FMediaViewerLibraryItem`  
_L34-59_
- inherits: `FMediaViewerLibraryItem`
- L36 _public prototype_ `static FGuid GetIdForViewport(const FString& InConfigKey, bool bCreateIfInvalid);`
- L37 _public prototype_ `static TSharedPtr<FSceneViewport> GetViewportFromConfigKey(const FString& InConfigKey);`
- L38 _public prototype_ `static TSharedPtr<FSceneViewport> GetViewportFromStringValue(const FString& InStringValue);`
- L40 _public prototype_ `FItem(const FString& InConfigKey);`
- L42 _public prototype_ `FItem(const FGuid& InId, const FString& InConfigKey);`
- L44 _public prototype_ `FItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L46 _public prototype_ `virtual ~FItem() override = default;`
- L49 _public prototype_ `virtual FName GetItemType() const override;`
- L50 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L51 _public prototype_ `virtual FSlateColor GetItemTypeColor() const override;`
- L52 _public prototype_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail() override;`
- L53 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L54 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`
- L58 _protected prototype_ `UTextureRenderTarget2D* CreateRenderTargetThumbnail();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MediaViewer` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/MaterialInterfaceImageViewer.h` (Private)


#### struct `FMaterialInterfaceImageViewerSettings`  
`struct FMaterialInterfaceImageViewerSettings`  
_L19-35_
- reflection: `USTRUCT()`
- L24 _public member_ `TObjectPtr<UMaterialInterface> MaterialInterface = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Material")`
- L27 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Material")`
- L31 _public member_ `bool bRealTime = false;` — `UPROPERTY(EditAnywhere, Category = "Material")` — Will render the material every frame.
- L34 _public member_ `int32 RenderTargetSize = 256;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (ClampMin = 32, UIMin = 32, ClampMax = 2048, UIMax = 2048))`

#### class `UE::MediaViewer::Private::FMaterialInterfaceImageViewer`  
`class FMaterialInterfaceImageViewer : public FMediaImageViewer`  
_L40-120_
- inherits: `FMediaImageViewer`
- L86 _public member_ `static const FLazyName ItemTypeName;`
- L88 _public prototype_ `FMaterialInterfaceImageViewer(TNotNull<UMaterialInterface*> InMaterialInterface);`
- L89 _public prototype_ `FMaterialInterfaceImageViewer(const FGuid& InId, TNotNull<UMaterialInterface*> InMaterialInterface);`
- L94 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L95 _public prototype_ `virtual bool OnOwnerCleanup(UObject* InObject) override;`
- L96 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L97 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomSettingsOnScope() const override;`
- L98 _public prototype_ `virtual void OnMirrored() override;`
- L99 _public prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry) override;`
- L103 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L107 _public prototype_ `virtual FString GetReferencerName() const override;`
- L108 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L112 _protected member_ `FMaterialInterfaceImageViewerSettings MaterialSettings;`
- L113 _protected member_ `TSharedPtr<FTextureSampleCache> SampleCache;`
- L115 _protected prototype_ `void CreateBrush();`
- L117 _protected prototype_ `void RenderMaterial();`
- L119 _protected prototype_ `void OnMaterialCompiled(UMaterialInterface* InMaterialInterface);`

#### struct `UE::MediaViewer::Private::FMaterialInterfaceImageViewer::FFactory`  
`struct FFactory : public IMediaImageViewerFactory`  
_L43-60_
- inherits: `IMediaImageViewerFactory`
- L45 _public function_ `FFactory()`
- L50 _public prototype_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const override;`
- L51 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const override;`
- L52 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override;`
- L54 _public prototype_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const override;`
- L55 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const override;`
- L56 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override;`
- L58 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const override;`
- L59 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const override;`

#### struct `UE::MediaViewer::Private::FMaterialInterfaceImageViewer::FItem`  
`struct FItem : public FMediaViewerLibraryItem`  
_L62-84_
- inherits: `FMediaViewerLibraryItem`
- L64 _public prototype_ `FItem(const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UMaterialInterface*> InMaterial);`
- L66 _public prototype_ `FItem(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UMaterialInterface*> InMaterial);`
- L68 _public prototype_ `FItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L70 _public prototype_ `virtual ~FItem() override = default;`
- L73 _public prototype_ `virtual FName GetItemType() const override;`
- L74 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L75 _public prototype_ `virtual FSlateColor GetItemTypeColor() const override;`
- L76 _public prototype_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail() override;`
- L77 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L78 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`
- L79 _public prototype_ `virtual TOptional<FAssetData> AsAsset() const override;`
- L83 _protected prototype_ `UTextureRenderTarget2D* CreateRenderTargetThumbnail();`

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace MediaViewer` (scope `UE`)
- L37 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/MediaSourceImageViewer.h` (Private)


#### struct `FMediaSourceImageViewerSettings`  
`struct FMediaSourceImageViewerSettings`  
_L25-34_
- reflection: `USTRUCT()`
- L30 _public member_ `TObjectPtr<UMediaSource> MediaSource = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Texture")`
- L33 _public member_ `TEnumAsByte<TextureMipGenSettings> MipGenType = TextureMipGenSettings::TMGS_Unfiltered;` — `UPROPERTY(VisibleAnywhere, Category = "Texture")`

#### class `UE::MediaViewer::Private::FMediaSourceImageViewer`  
`class FMediaSourceImageViewer : public FMediaImageViewer`  
_L41-177_
- inherits: `FMediaImageViewer`
- L119 _public member_ `static const FLazyName ItemTypeName_Asset;`
- L120 _public member_ `static const FLazyName ItemTypeName_File;`
- L122 _public prototype_ `FMediaSourceImageViewer(TNotNull<UMediaSource*> InMediaSource, const FText& InDisplayName);`
- L123 _public prototype_ `FMediaSourceImageViewer(const FGuid& InId, TNotNull<UMediaSource*> InMediaSource, const FText& InDisplayName);`
- L127 _public prototype_ `UMediaStream* GetMediaStream() const;`
- L137 _public prototype_ `void UpdateTileVisibilityViewport(FIntPoint InDisplayRectPx, float InDPIScale);` — Push the latest panel viewport state to the tile-visibility provider so that the underlying tiled-media reader (e.g. ImgMedia EXR) requests only the tiles needed for what's actually visible on screen. Called by SMediaSourceOverlay::Tick. @param InDisplayRectPx Image area in absolute (post-DPI) screen pixels. @param InDPIScale      Slate-to-physical DPI scale of the panel.
- L140 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L141 _public prototype_ `virtual bool OnOwnerCleanup(UObject* InObject) override;`
- L142 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L143 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomSettingsOnScope() const override;`
- L144 _public prototype_ `virtual void OnMirrored() override;`
- L145 _public prototype_ `virtual TSharedPtr<SWidget> GetOverlayWidget(EMediaImageViewerPosition InPosition, const TSharedPtr<FMediaViewerDelegates>& InDelegates) override;`
- L146 _public prototype_ `virtual void ExtendStatusBar(UE::MediaViewer::FMediaImageStatusBarExtender& InOutStatusBarExtender) override;`
- L150 _public prototype_ `virtual FString GetReferencerName() const override;`
- L151 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L155 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L159 _protected member_ `FMediaSourceImageViewerSettings MediaSourceSettings;`
- L160 _protected member_ `TObjectPtr<UMediaStream> MediaStream;`
- L161 _protected member_ `TSharedPtr<FTextureSampleCache> SampleCache;`
- L164 _protected member_ `TSharedPtr<FViewerTileVisibilityProvider, ESPMode::ThreadSafe> TileVisibilityProvider;` — Tile-visibility provider exposed via FMediaTextureTracker; the widget pushes viewport state into it each Tick.
- L167 _protected member_ `TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe> TextureTrackerObject;` — FMediaTextureTracker bookkeeping for the provider. Registered against the player's MediaTexture.
- L170 _protected member_ `TWeakObjectPtr<UMediaTexture> RegisteredMediaTexture;` — The MediaTexture we registered with on the tracker - kept so the dtor can unregister against the same one.
- L172 _protected prototype_ `void AddPlayerName(const TSharedRef<SHorizontalBox>& InStatusBar);`
- L175 _protected prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry) override;`

#### struct `UE::MediaViewer::Private::FMediaSourceImageViewer::FFactory`  
`struct FFactory : public IMediaImageViewerFactory`  
_L44-61_
- inherits: `IMediaImageViewerFactory`
- L46 _public function_ `FFactory()`
- L51 _public prototype_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const override;`
- L52 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const override;`
- L53 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override;`
- L55 _public prototype_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const override;`
- L56 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const override;`
- L57 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override;`
- L59 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const override;`
- L60 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const override;`

#### struct `UE::MediaViewer::Private::FMediaSourceImageViewer::FItem`  
`struct FItem : public FMediaViewerLibraryItem, public FGCObject`  
_L63-80_
- inherits: `FMediaViewerLibraryItem,FGCObject`
- L65 _public member_ `TObjectPtr<UTexture> Texture;`
- L67 _public prototype_ `FItem(const FText& InName, const FText& InToolTip, bool bInTransient, const FString& InStringValue);`
- L69 _public prototype_ `FItem(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bInTransient, const FString& InStringValue);`
- L72 _public prototype_ `virtual FSlateColor GetItemTypeColor() const override;`
- L73 _public prototype_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail() override;`
- L77 _public prototype_ `virtual FString GetReferencerName() const override;`
- L78 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`

#### struct `UE::MediaViewer::Private::FMediaSourceImageViewer::FAssetItem`  
`struct FAssetItem : public FItem`  
_L82-99_
- inherits: `FItem`
- L84 _public prototype_ `FAssetItem(const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UMediaSource*> InMediaSource);`
- L86 _public prototype_ `FAssetItem(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UMediaSource*> InMediaSource);`
- L88 _public prototype_ `FAssetItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L90 _public prototype_ `virtual ~FAssetItem() override = default;`
- L93 _public prototype_ `virtual FName GetItemType() const override;`
- L94 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L95 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L96 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`
- L97 _public prototype_ `virtual TOptional<FAssetData> AsAsset() const override;`

#### struct `UE::MediaViewer::Private::FMediaSourceImageViewer::FExternalItem`  
`struct FExternalItem : public FItem`  
_L101-117_
- inherits: `FItem`
- L103 _public prototype_ `FExternalItem(const FText& InName, const FText& InToolTip, const FString& InFilePath);`
- L105 _public prototype_ `FExternalItem(const FGuid& InId, const FText& InName, const FText& InToolTip, const FString& InFilePath);`
- L107 _public prototype_ `FExternalItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L109 _public prototype_ `virtual ~FExternalItem() override = default;`
- L112 _public prototype_ `virtual FName GetItemType() const override;`
- L113 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L114 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L115 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace MediaViewer` (scope `UE`)
- L36 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/MediaTextureImageViewer.h` (Private)


#### struct `FMediaTextureImageViewerSettings`  
`struct FMediaTextureImageViewerSettings`  
_L17-26_
- reflection: `USTRUCT()`
- L22 _public member_ `bool bRealTime = true;` — `UPROPERTY(EditAnywhere, Category = "Material")`
- L25 _public member_ `TObjectPtr<UMediaTexture> MediaTexture = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Texture")`

#### class `UE::MediaViewer::Private::FMediaTextureImageViewer`  
`class FMediaTextureImageViewer : public FMediaImageViewer`  
_L31-105_
- inherits: `FMediaImageViewer`
- L74 _public member_ `static const FLazyName ItemTypeName;`
- L76 _public prototype_ `FMediaTextureImageViewer(TNotNull<UMediaTexture*> InMediaTexture);`
- L77 _public prototype_ `FMediaTextureImageViewer(const FGuid& InId, TNotNull<UMediaTexture*> InMediaTexture);`
- L79 _public prototype_ `virtual ~FMediaTextureImageViewer() override = default;`
- L82 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L83 _public prototype_ `virtual bool OnOwnerCleanup(UObject* InObject) override;`
- L84 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L85 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomSettingsOnScope() const override;`
- L86 _public prototype_ `virtual void OnMirrored() override;`
- L90 _public prototype_ `virtual FString GetReferencerName() const override;`
- L91 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L95 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L100 _protected prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry) override;`
- L103 _protected member_ `FMediaTextureImageViewerSettings MediaTextureSettings;`
- L104 _protected member_ `TSharedPtr<FTextureSampleCache> SampleCache;`

#### struct `UE::MediaViewer::Private::FMediaTextureImageViewer::FFactory`  
`struct FFactory : public IMediaImageViewerFactory`  
_L34-51_
- inherits: `IMediaImageViewerFactory`
- L36 _public function_ `FFactory()`
- L41 _public prototype_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const override;`
- L42 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const override;`
- L43 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override;`
- L45 _public prototype_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const override;`
- L46 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const override;`
- L47 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override;`
- L49 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const override;`
- L50 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const override;`

#### struct `UE::MediaViewer::Private::FMediaTextureImageViewer::FItem`  
`struct FItem : public FMediaViewerLibraryItem`  
_L53-72_
- inherits: `FMediaViewerLibraryItem`
- L55 _public prototype_ `FItem(const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UMediaTexture*> InMediaTexture);`
- L57 _public prototype_ `FItem(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UMediaTexture*> InMediaTexture);`
- L59 _public prototype_ `FItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L61 _public prototype_ `virtual ~FItem() override = default;`
- L64 _public prototype_ `virtual FName GetItemType() const override;`
- L65 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L66 _public prototype_ `virtual FSlateColor GetItemTypeColor() const override;`
- L67 _public prototype_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail() override;`
- L68 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L69 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`
- L70 _public prototype_ `virtual TOptional<FAssetData> AsAsset() const override;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace MediaViewer` (scope `UE`)
- L28 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/NullImageViewer.h` (Private)


#### class `UE::MediaViewer::Private::FNullImageViewer`  
`class FNullImageViewer : public FMediaImageViewer`  
_L10-31_
- inherits: `FMediaImageViewer`
- L13 _public prototype_ `static TSharedRef<FNullImageViewer> GetNullImageViewer();`
- L15 _public prototype_ `FNullImageViewer();`
- L16 _public prototype_ `virtual ~FNullImageViewer() = default;`
- L19 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L23 _public prototype_ `virtual FString GetReferencerName() const override;`
- L28 _protected prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L29 _protected prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MediaViewer` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/SceneViewportImageViewer.h` (Private)


#### class `UE::MediaViewer::Private::FSceneViewportImageViewer`  
`class FSceneViewportImageViewer : public FViewportImageViewer`  
_L12-24_
- inherits: `FViewportImageViewer`
- L15 _public prototype_ `FSceneViewportImageViewer(const TSharedPtr<FSceneViewport>& InViewport, const FText& InName);`
- L16 _public prototype_ `FSceneViewportImageViewer(const FGuid& InId, const TSharedPtr<FSceneViewport>& InViewport, const FText& InDisplayName);`
- L19 _protected member_ `TWeakPtr<FSceneViewport> ViewportWeak;`
- L22 _protected prototype_ `virtual FViewport* GetViewport() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MediaViewer` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/Texture2DImageViewer.h` (Private)


#### struct `FTexture2DImageViewerSettings`  
`struct FTexture2DImageViewerSettings`  
_L19-25_
- reflection: `USTRUCT()`
- L24 _public member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Texture")`

#### class `UE::MediaViewer::Private::FTexture2DImageViewer`  
`class FTexture2DImageViewer : public FMediaImageViewer`  
_L30-122_
- inherits: `FMediaImageViewer`
- L80 _public member_ `static const FLazyName ItemTypeName;`
- L82 _public prototype_ `FTexture2DImageViewer(TNotNull<UTexture2D*> InTexture);`
- L83 _public prototype_ `FTexture2DImageViewer(const FGuid& InId, TNotNull<UTexture2D*> InTexture);`
- L91 _public prototype_ `FTexture2DImageViewer(TNotNull<UTexture2D*> InTexture, const FText& InDisplayName);` — Constructs a viewer for InTexture but overrides the display name shown in the viewer UI with InDisplayName. Use this when the texture's UObject name (which cannot contain dots or other characters allowed in file names) does not match the label the user expects to see.
- L93 _public prototype_ `virtual ~FTexture2DImageViewer() override = default;`
- L96 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L97 _public prototype_ `virtual bool OnOwnerCleanup(UObject* InObject) override;`
- L98 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L99 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomSettingsOnScope() const override;`
- L100 _public prototype_ `virtual void OnMirrored() override;`
- L104 _public prototype_ `virtual FString GetReferencerName() const override;`
- L105 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L109 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L113 _protected member_ `FTexture2DImageViewerSettings TextureSettings;`
- L114 _protected member_ `TSharedPtr<FTextureSampleCache> SampleCache;`
- L115 _protected member_ `bool bValidImageSize;`
- L117 _protected prototype_ `TOptional<FIntPoint> GetTextureSize() const;`
- L120 _protected prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry) override;`

#### struct `UE::MediaViewer::Private::FTexture2DImageViewer::FFactory`  
`struct FFactory : public IMediaImageViewerFactory`  
_L33-50_
- inherits: `IMediaImageViewerFactory`
- L35 _public function_ `FFactory()`
- L40 _public prototype_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const override;`
- L41 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const override;`
- L42 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override;`
- L44 _public prototype_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const override;`
- L45 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const override;`
- L46 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override;`
- L48 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const override;`
- L49 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const override;`

#### struct `UE::MediaViewer::Private::FTexture2DImageViewer::FItem`  
`struct FItem : public FMediaViewerLibraryItem, public FGCObject`  
_L52-78_
- inherits: `FMediaViewerLibraryItem,FGCObject`
- L54 _public member_ `mutable TObjectPtr<UTexture2D> Texture;`
- L56 _public prototype_ `FItem(const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UTexture2D*> InTexture);`
- L58 _public prototype_ `FItem(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UTexture2D*> InTexture);`
- L60 _public prototype_ `FItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L62 _public prototype_ `virtual ~FItem() override = default;`
- L65 _public prototype_ `virtual FName GetItemType() const override;`
- L66 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L67 _public prototype_ `virtual FSlateColor GetItemTypeColor() const override;`
- L68 _public prototype_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail() override;`
- L69 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L70 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`
- L71 _public prototype_ `virtual TOptional<FAssetData> AsAsset() const override;`
- L75 _public prototype_ `virtual FString GetReferencerName() const override;`
- L76 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace MediaViewer` (scope `UE`)
- L27 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/TextureMipCache.h` (Private)


#### class `UE::MediaViewer::Private::FTextureMipCache`  
`class FTextureMipCache`  
_L16-44_
- L32 _public prototype_ `FTextureMipCache();`
- L33 _public prototype_ `FTextureMipCache(TNotNull<UTexture*> InTexture);`
- L35 _public prototype_ `const FImage* GetMipImage(int32 InMipLevel) const;`
- L37 _public prototype_ `void Invalidate();`
- L40 _protected member_ `TWeakObjectPtr<UTexture> TextureWeak;`
- L41 _protected member_ `TArray<FMipCache> Mips;`
- L43 _protected prototype_ `void CreateMipImage(int32 InMipLevel);`

#### enum `UE::MediaViewer::Private::FTextureMipCache::EMipState`  
`enum class EMipState`  
_L19-24_
- L21 _public enumerator_ `NotCached = 0`
- L22 _public enumerator_ `Cached`
- L23 _public enumerator_ `Failed`

#### struct `UE::MediaViewer::Private::FTextureMipCache::FMipCache`  
`struct FMipCache`  
_L26-30_
- L28 _public member_ `EMipState State;`
- L29 _public member_ `FImage Image;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MediaViewer` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/TextureRenderTarget2DImageViewer.h` (Private)


#### struct `FTextureRenderTarget2DImageViewerSettings`  
`struct FTextureRenderTarget2DImageViewerSettings`  
_L17-23_
- reflection: `USTRUCT()`
- L22 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Texture")`

#### class `UE::MediaViewer::Private::FTextureRenderTarget2DImageViewer`  
`class FTextureRenderTarget2DImageViewer : public FMediaImageViewer`  
_L28-98_
- inherits: `FMediaImageViewer`
- L71 _public member_ `static const FLazyName ItemTypeName;`
- L73 _public prototype_ `FTextureRenderTarget2DImageViewer(TNotNull<UTextureRenderTarget2D*> InTextureRenderTarget2D);`
- L74 _public prototype_ `FTextureRenderTarget2DImageViewer(const FGuid& InId, TNotNull<UTextureRenderTarget2D*> InTextureRenderTarget2D);`
- L76 _public prototype_ `virtual ~FTextureRenderTarget2DImageViewer() = default;`
- L79 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const override;`
- L80 _public prototype_ `virtual bool OnOwnerCleanup(UObject* InObject) override;`
- L81 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L82 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomSettingsOnScope() const override;`
- L83 _public prototype_ `virtual void OnMirrored() override;`
- L87 _public prototype_ `virtual FString GetReferencerName() const override;`
- L88 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L92 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L96 _protected member_ `FTextureRenderTarget2DImageViewerSettings RenderTargetSettings;`
- L97 _protected member_ `TSharedPtr<FTextureSampleCache> SampleCache;`

#### struct `UE::MediaViewer::Private::FTextureRenderTarget2DImageViewer::FFactory`  
`struct FFactory : public IMediaImageViewerFactory`  
_L31-48_
- inherits: `IMediaImageViewerFactory`
- L33 _public function_ `FFactory()`
- L38 _public prototype_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const override;`
- L39 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const override;`
- L40 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override;`
- L42 _public prototype_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const override;`
- L43 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const override;`
- L44 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override;`
- L46 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const override;`
- L47 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const override;`

#### struct `UE::MediaViewer::Private::FTextureRenderTarget2DImageViewer::FItem`  
`struct FItem : public FMediaViewerLibraryItem`  
_L50-69_
- inherits: `FMediaViewerLibraryItem`
- L52 _public prototype_ `FItem(const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UTextureRenderTarget2D*> InRenderTarget);`
- L54 _public prototype_ `FItem(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bInTransient, TNotNull<UTextureRenderTarget2D*> InRenderTarget);`
- L56 _public prototype_ `FItem(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryItem& InItem);`
- L58 _public prototype_ `virtual ~FItem() override = default;`
- L61 _public prototype_ `virtual FName GetItemType() const override;`
- L62 _public prototype_ `virtual FText GetItemTypeDisplayName() const override;`
- L63 _public prototype_ `virtual FSlateColor GetItemTypeColor() const override;`
- L64 _public prototype_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail() override;`
- L65 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer() const override;`
- L66 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const override;`
- L67 _public prototype_ `virtual TOptional<FAssetData> AsAsset() const override;`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MediaViewer` (scope `UE`)
- L25 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/TextureSampleCache.h` (Private)


#### class `UE::MediaViewer::Private::FTextureSampleCache`  
`class FTextureSampleCache : public TSharedFromThis<FTextureSampleCache>, public FGCObject`  
_L36-100_
- inherits: `TSharedFromThis<FTextureSampleCache>,FGCObject`
- desc: Asynchronous single-pixel color sampler for an arbitrary UTexture. Used by the Media Viewer color picker / status bar. A 1x1 sub-region of the source is blitted into a tiny RTF_RGBA16f intermediate and read back via FRHIGPUTextureReadback, so sampling is non-blocking even on multi-gigabyte sources. Game-thread callers get the most recently completed sample; results lag by ~1-2 frames during rapid movement. Gated by CVar MediaViewer.EnableColorPicker (default true). All public methods are game-thread only; cross-thread state lives in FMediaViewerTextureSampleResource. Must be owned via TSharedPtr.
- L46 _public prototype_ `FTextureSampleCache(TNotNull<UTexture*> InTexture, EPixelFormat InPixelFormat);` — Constructs a cache that samples colors from the given texture. @param InTexture     Source texture; held weakly, sampling no-ops once it's GC'd. @param InPixelFormat Reserved; currently unused (path normalizes through RTF_RGBA16f).
- L52 _public prototype_ `bool IsValid() const;` — Returns true if the source texture is still alive.
- L69 _public prototype_ `const FLinearColor* GetPixelColor(const FIntPoint& InPixelCoordinates, uint8 InMipLevel = 0, const TOptional<FTimespan>& InTime = {});` — Returns the last sampled color, kicking a new readback if coordinates, mip level, or media time differ from the cached sample. Non-blocking. Out-of-bounds coordinates are clamped on the render thread. @param InPixelCoordinates Coordinates in mip 0 space. Internally shifted to the target mip's dimensions before sampling. @param InMipLevel         Mip to sample. Clamped to the source's mip range; the picker tracks the viewer's displayed mip so visibility-provider sources sample fresh data. @param InTime             Optional media time; forces a new sample on frame changes at the same pixel for time-varying sources. @return Pointer to the last published color, or nullptr if no sample has completed yet. Valid until the next call on this cache.
- L72 _public prototype_ `void MarkDirty();` — Forces the next GetPixelColor to kick a fresh readback even if coords/time match.
- L80 _public prototype_ `void Invalidate();` — Clears the cached sample and discards the result of any in-flight readback so it cannot republish a stale color. The submitted GPU work itself is not aborted; it completes and writes into the staging texture, which is then reused by the next EnqueueCopy.
- L83 _public prototype_ `virtual FString GetReferencerName() const override;`
- L84 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L89 _protected member_ `TWeakObjectPtr<UTexture> TextureWeak;` — Source texture, held weakly so sampling no-ops once it's GC'd.
- L92 _protected member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — 1x1 RTF_RGBA16f intermediate, lazily created on the first sample and reused thereafter.
- L99 _protected member_ `TSharedPtr<FMediaViewerTextureSampleResource> SampleResource;` — Owns the FRHIGPUTextureReadback and the cross-thread cached sample. Registered via BeginInitResource in the constructor, released on the render thread in the destructor. Captured as a WeakPtr by sample render commands.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MediaViewer` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/ImageViewers/ViewportImageViewer.h` (Private)


#### struct `FViewportImageViewerSettings`  
`struct FViewportImageViewerSettings`  
_L20-30_
- reflection: `USTRUCT()`
- L25 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Material")`
- L29 _public member_ `bool bRealTime = true;` — `UPROPERTY(EditAnywhere, Category = "Material")` — Will render the viewport every frame.

#### class `UE::MediaViewer::Private::FViewportImageViewer`  
`class FViewportImageViewer : public FMediaImageViewer`  
_L35-88_
- inherits: `FMediaImageViewer`
- L38 _public prototype_ `FViewportImageViewer(const FMediaImageViewerInfo& InImageInfo);`
- L43 _public prototype_ `virtual bool IsValid() const override;`
- L44 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const override;`
- L45 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomSettingsOnScope() const override;`
- L46 _public prototype_ `virtual void OnMirrored() override;`
- L50 _public prototype_ `virtual FString GetReferencerName() const override;`
- L51 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L55 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L66 _protected prototype_ `static void RenderViewport(TNotNull<FViewport*> InViewport, TNotNull<UTextureRenderTarget2D*> InRenderTarget, FRenderComplete InRenderComplete, bool bResizeTargetToViewport = true);`
- L69 _protected member_ `FViewportImageViewerSettings ViewportSettings;`
- L70 _protected member_ `TSharedPtr<FTextureSampleCache> SampleCache;`
- L71 _protected member_ `FDelegateHandle OnEndFrameRTHandle;`
- L72 _protected member_ `ERenderState RenderState;`
- L73 _protected member_ `bool bResizeTargetToViewport;`
- L75 _protected prototype_ `virtual FViewport* GetViewport() const = 0;`
- L77 _protected prototype_ `void CreateBrush();`
- L79 _protected prototype_ `void RequestRender(bool bInResizeTargetToViewport);`
- L81 _protected prototype_ `void ConditionallyRequestRender();`
- L83 _protected prototype_ `void OnRenderComplete(bool bInSuccess);`
- L86 _protected prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry) override;`

#### enum `UE::MediaViewer::Private::FViewportImageViewer::ERenderState`  
`enum class ERenderState : uint8`  
_L59-64_
- L61 _public enumerator_ `NotRendered`
- L62 _public enumerator_ `RenderQueued`
- L63 _public enumerator_ `Invalidated`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace MediaViewer` (scope `UE`)
- L32 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Library/LevelEditorViewportGroup.h` (Private)


#### struct `UE::MediaViewer::Private::FLevelEditorViewportGroup`  
`struct FLevelEditorViewportGroup : public FMediaViewerLibraryDynamicGroup`  
_L13-22_
- inherits: `FMediaViewerLibraryDynamicGroup`
- desc: A group that generates entries based on available level editor viewports.
- L15 _public prototype_ `FLevelEditorViewportGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary);`
- L16 _public prototype_ `FLevelEditorViewportGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary, const FGuid& InId);`
- L18 _public prototype_ `virtual ~FLevelEditorViewportGroup() override = default;`
- L21 _protected prototype_ `static TArray<TSharedRef<FMediaViewerLibraryItem>> GetLevelEditorViewportItems();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MediaViewer` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Library/MediaTextureGroup.h` (Private)


#### struct `UE::MediaViewer::Private::FMediaTextureGroup`  
`struct FMediaTextureGroup : public FMediaViewerLibraryDynamicGroup`  
_L13-22_
- inherits: `FMediaViewerLibraryDynamicGroup`
- desc: A group that generates entries based on available UMediaTextures.
- L15 _public prototype_ `FMediaTextureGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary);`
- L16 _public prototype_ `FMediaTextureGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary, const FGuid& InId);`
- L18 _public prototype_ `virtual ~FMediaTextureGroup() override = default;`
- L21 _protected prototype_ `static TArray<TSharedRef<FMediaViewerLibraryItem>> GetMediaTextureItems();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MediaViewer` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Library/MediaTrackGroup.h` (Private)


#### struct `UE::MediaViewer::Private::FMediaTrackGroup`  
`struct FMediaTrackGroup : public FMediaViewerLibraryDynamicGroup`  
_L13-22_
- inherits: `FMediaViewerLibraryDynamicGroup`
- desc: A group that generates entries based on available UMediaTracks.
- L15 _public prototype_ `FMediaTrackGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary);`
- L16 _public prototype_ `FMediaTrackGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary, const FGuid& InId);`
- L18 _public prototype_ `virtual ~FMediaTrackGroup() override = default;`
- L21 _protected prototype_ `static TArray<TSharedRef<FMediaViewerLibraryItem>> GetMediaTrackItems();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MediaViewer` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Library/MediaViewerLibrary.h` (Private)


#### class `UE::MediaViewer::Private::FMediaViewerLibrary`  
`class FMediaViewerLibrary : public IMediaViewerLibrary, public TSharedFromThis<FMediaViewerLibrary>`  
_L23-70_
- inherits: `IMediaViewerLibrary,TSharedFromThis<FMediaViewerLibrary>`
- desc: Implementation of @see IMediaViewerLibrary.
- L28 _public prototype_ `FMediaViewerLibrary();`
- L30 _public prototype_ `virtual ~FMediaViewerLibrary() = default;`
- L32 _public prototype_ `bool CanDragDropGroup(const FGuid& InGroupId) const;`
- L34 _public prototype_ `bool CanDragDropItem(const FGroupItem& InItem) const;`
- L37 _public prototype_ `virtual const FGuid& GetDefaultGroupId() const override;`
- L38 _public prototype_ `virtual const FGuid& GetHistoryGroupId() const override;`
- L39 _public prototype_ `virtual const FGuid& GetSnapshotsGroupId() const override;`
- L40 _public prototype_ `virtual const TArray<TSharedRef<const FMediaViewerLibraryGroup>>& GetGroups() const override;`
- L41 _public prototype_ `virtual bool AddGroup(const TSharedRef<FMediaViewerLibraryGroup>& InNewGroup) override;`
- L42 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryGroup> GetGroup(const FGuid& InGroupIdToRemove) const override;`
- L43 _public prototype_ `virtual int32 EmptyGroup(const FGuid& InGroupId) override;`
- L44 _public prototype_ `virtual void RemoveInvalidGroupItems(const FGuid& InGroup) override;`
- L45 _public prototype_ `virtual bool CanRemoveGroup(const FGuid& InGroupIdToRemove) const override;`
- L46 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryGroup> RemoveGroup(const FGuid& InGroupIdToRemove) override;`
- L47 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> FindItemByValue(FName InItemType, const FString& InStringValue) const override;`
- L48 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> GetItem(const FGuid& InItemId) const override;`
- L49 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryGroup> GetItemGroup(const FGuid& InItemId) const override;`
- L50 _public prototype_ `virtual bool AddItem(const TSharedRef<FMediaViewerLibraryItem>& InNewItem) override;`
- L51 _public prototype_ `virtual bool AddItemToGroup(const TSharedRef<FMediaViewerLibraryItem>& InNewItem, TOptional<FGuid> InTargetGroupId = {}, int32 InIndex = INDEX_NONE) override;`
- L53 _public prototype_ `virtual bool AddItemBelowItem(const TSharedRef<FMediaViewerLibraryItem>& InNewItem, const FGroupItem& InTargetItem) override;`
- L54 _public prototype_ `virtual bool MoveItemToGroup(const FGroupItem& InItemToMove, const FGuid& InTargetGroupId, int32 InIndex = INDEX_NONE) override;`
- L55 _public prototype_ `virtual bool MoveItemWithinGroup(const FGroupItem& InItemToMove, int32 InIndex) override;`
- L56 _public prototype_ `virtual bool MoveItemBelowItem(const FGroupItem& InItemToMove, const FGroupItem& InTargetItem) override;`
- L57 _public prototype_ `virtual bool CanRemoveItemFromGroup(const FGroupItem& InItemToRemove) const override;`
- L58 _public prototype_ `virtual bool RemoveItemFromGroup(const FGroupItem& InItemToRemove) override;`
- L59 _public prototype_ `virtual bool CanRemoveItem(const FGuid& InItemIdToRemove) const override;`
- L60 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> RemoveItem(const FGuid& InItemIdToRemove) override;`
- L61 _public prototype_ `virtual FOnChanged::RegistrationType& GetOnChanged() override;`
- L65 _protected member_ `TArray<TSharedRef<FMediaViewerLibraryGroup>> Groups;`
- L66 _protected member_ `TMap<FGuid, TSharedRef<FMediaViewerLibraryItem>> Items;`
- L67 _protected member_ `FOnChanged OnChangedDelegate;`
- L69 _protected prototype_ `void OnChanged(FMediaViewerLibrary::EChangeType InChangeType);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MediaViewer` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::MediaViewer`)
- L18 _variable_ `constexpr int32 MaxHistoryEntries = 20;` (scope `UE::MediaViewer::Private`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Library/MediaViewerLibraryIni.h` (Private)


#### struct `FMediaViewerLibraryItemData`  
`struct FMediaViewerLibraryItemData`  
_L23-32_
- reflection: `USTRUCT()`
- L28 _public member_ `FName ItemType;` — `UPROPERTY()`
- L31 _public member_ `FMediaViewerLibraryItem Item;` — `UPROPERTY()`

#### struct `FMediaViewerImageState`  
`struct FMediaViewerImageState`  
_L35-50_
- reflection: `USTRUCT()`
- L40 _public member_ `FName ImageType;` — `UPROPERTY(Config)`
- L43 _public member_ `FString StringValue;` — `UPROPERTY(Config)`
- L46 _public member_ `FMediaImageViewerPanelSettings PanelSettings;` — `UPROPERTY(Config)`
- L49 _public member_ `FMediaImagePaintSettings PaintSettings;` — `UPROPERTY(Config)`

#### struct `FMediaViewerState`  
`struct FMediaViewerState`  
_L53-65_
- reflection: `USTRUCT()`
- L58 _public member_ `FMediaViewerSettings ViewerSettings;` — `UPROPERTY(Config)`
- L61 _public member_ `EMediaImageViewerActivePosition ActiveView = EMediaImageViewerActivePosition::Single;` — `UPROPERTY(Config)`
- L64 _public member_ `TArray<FMediaViewerImageState> Images;` — `UPROPERTY(Config)`

#### class `UMediaViewerLibraryIni`  
`class UMediaViewerLibraryIni : public UObject`  
_L68-105_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L73 _public prototype_ `static UMediaViewerLibraryIni& Get();`
- L75 _public prototype_ `UMediaViewerLibraryIni();`
- L77 _public prototype_ `void SaveLibrary(const TSharedRef<UE::MediaViewer::IMediaViewerLibrary>& InLibrary);`
- L79 _public prototype_ `void LoadLibrary(const TSharedRef<UE::MediaViewer::IMediaViewerLibrary>& InLibrary) const;`
- L81 _public prototype_ `bool HasGroup(const FGuid& InGroupId) const;`
- L83 _public prototype_ `bool HasItem(const FGuid& InItemId) const;`
- L85 _public prototype_ `TConstArrayView<FMediaViewerState> GetBookmarks() const;`
- L87 _public prototype_ `void SetBookmark(int32 InIndex, const FMediaViewerState& InState);`
- L89 _public prototype_ `TOptional<FMediaViewerState> GetLastOpenedState() const;`
- L91 _public prototype_ `void SetLastOpenedState(const FMediaViewerState& InState);`
- L95 _protected member_ `TArray<FMediaViewerLibraryGroup> Groups;` — `UPROPERTY(Config)`
- L98 _protected member_ `TArray<FMediaViewerLibraryItemData> Items;` — `UPROPERTY(Config)`
- L101 _protected member_ `TArray<FMediaViewerState> Bookmarks;` — `UPROPERTY(Config)`
- L104 _protected member_ `TOptional<FMediaViewerState> LastOpenedState;` — `UPROPERTY(Config)`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MediaViewer` (scope `UE`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Library/TextureRenderTarget2DGroup.h` (Private)


#### struct `UE::MediaViewer::Private::FTextureRenderTarget2DGroup`  
`struct FTextureRenderTarget2DGroup : public FMediaViewerLibraryDynamicGroup`  
_L13-22_
- inherits: `FMediaViewerLibraryDynamicGroup`
- desc: A group that generates entries based on available UTextureRenderTarget2Ds.
- L15 _public prototype_ `FTextureRenderTarget2DGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary);`
- L16 _public prototype_ `FTextureRenderTarget2DGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary, const FGuid& InId);`
- L18 _public prototype_ `virtual ~FTextureRenderTarget2DGroup() override = default;`
- L21 _protected prototype_ `static TArray<TSharedRef<FMediaViewerLibraryItem>> GetTextureRenderTarget2DItems();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MediaViewer` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/MediaViewerCommands.h` (Private)


#### class `UE::MediaViewer::Private::FMediaViewerCommands`  
`class FMediaViewerCommands : public TCommands<FMediaViewerCommands>`  
_L12-106_
- inherits: `TCommands<FMediaViewerCommands>`
- L15 _public prototype_ `FMediaViewerCommands();`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> ToggleOverlay;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> MoveLeft;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> MoveRight;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> MoveUp;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> MoveDown;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> MoveForward;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> MoveBackward;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> RotatePlusYaw;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> RotateMinusYaw;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> RotatePlusPitch;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> RotateMinusPitch;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> RotatePlusRoll;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> RotateMinusRoll;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ScaleUp;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ScaleDown;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoFiltering;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> TogglePixelGrid;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> ToggleMipOverride;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> IncreaseMipLevel;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> DecreaseMipLevel;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> Scale12;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> Scale25;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> Scale50;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> Scale100;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> Scale200;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> Scale400;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> Scale800;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> Scale1000;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> ScaleToFit;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> CopyTransform;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> ResetTransform;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> ResetAllTransforms;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> ToggleLockedTransform;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> MirrorHorizonal;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> MirrorVertical;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> MirrorDepth;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> SecondImageOpacityMinus;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> SecondImageOpacityPlus;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> CopyColor;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> AddToLibrary;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> SwapAB;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> Snapshot;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> QuickRewindVideo;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> RewindVideo;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> StepBackVideo;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> ToggleVideoPlay;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> StepForwardVideo;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> FastForwardVideo;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> QuickFastForwardVideo;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> OpenNewTab;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark1;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark2;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark3;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark4;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark5;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark6;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark7;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark8;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark9;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> OpenBookmark10;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark1;`
- L97 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark2;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark3;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark4;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark5;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark6;`
- L102 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark7;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark8;`
- L104 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark9;`
- L105 _public member_ `TSharedPtr<FUICommandInfo> SaveBookmark10;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MediaViewer` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/MediaViewerContentBrowserIntegration.h` (Private)


#### class `UE::MediaViewer::FMediaViewerContentBrowserIntegration`  
`class FMediaViewerContentBrowserIntegration : public TSharedFromThis<FMediaViewerContentBrowserIntegration>`  
_L16-35_
- inherits: `TSharedFromThis<FMediaViewerContentBrowserIntegration>`
- L19 _public function_ `static const TSharedRef<FMediaViewerContentBrowserIntegration>& Get()`
- L25 _public prototype_ `void Integrate();`
- L27 _public prototype_ `void Disintegrate();`
- L30 _protected prototype_ `static void OpenInMediaViewer(TArray<FAssetData> InSelectedAssets);`
- L32 _protected member_ `FDelegateHandle ContentBrowserAssetHandle;`
- L34 _protected prototype_ `TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& InSelectedAssets);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MediaViewer` (scope `UE`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/MediaViewerModule.h` (Private)


#### class `UE::MediaViewer::Private::FMediaViewerModule`  
`class FMediaViewerModule : public IMediaViewerModule`  
_L24-83_
- inherits: `IMediaViewerModule`
- L27 _public member_ `static const FLazyName TabId;`
- L28 _public member_ `static const FLazyName StandaloneTabId;`
- L30 _public prototype_ `FMediaViewerModule();`
- L33 _public prototype_ `virtual bool IsFactoryRegistered(FName InFactoryName) const override;`
- L34 _public prototype_ `virtual bool HasFactoryFor(const FAssetData& InAssetData) const override;`
- L35 _public prototype_ `virtual bool HasFactoryFor(UObject* InObject) const override;`
- L36 _public prototype_ `virtual void RegisterFactory(FName InFactoryName, const TSharedRef<IMediaImageViewerFactory>& InFactory) override;`
- L37 _public prototype_ `virtual void UnregisterFactory(FName InFactoryName) override;`
- L38 _public prototype_ `virtual bool OpenTab() override;`
- L39 _public prototype_ `virtual bool OpenTab(const FMediaViewerArgs& InMediaViewerArgs) override;`
- L40 _public prototype_ `virtual TSharedRef<IMediaViewerLibrary> GetLibrary() const;`
- L41 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const override;`
- L42 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const override;`
- L43 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(FName InItemType, const FMediaViewerLibraryItem& InSavedItem) const override;`
- L44 _public prototype_ `virtual bool HasImage(EMediaImageViewerPosition InPosition) const override;`
- L45 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> GetImage(EMediaImageViewerPosition InPosition) const override;`
- L46 _public prototype_ `virtual bool SetImage(EMediaImageViewerPosition InPosition, const FAssetData& InAssetData) override;`
- L47 _public prototype_ `virtual bool SetImage(EMediaImageViewerPosition InPosition, UObject* InObject) override;`
- L48 _public prototype_ `virtual bool SetImage(EMediaImageViewerPosition InPosition, const TSharedRef<FMediaImageViewer> InImageViewer) override;`
- L49 _public prototype_ `virtual bool ClearImage(EMediaImageViewerPosition InPosition) override;`
- L50 _public prototype_ `virtual TSharedRef<SMediaViewerTab> CreateMediaViewer(const FMediaViewerArgs& InMediaViewerArgs) override;`
- L51 _public prototype_ `virtual TSharedRef<IMediaViewerLibraryWidget> CreateLibrary(const IMediaViewerLibraryWidget::FArgs& InArgs) override;`
- L52 _public prototype_ `virtual TSharedPtr<SDockTab> OpenStandaloneTab();`
- L56 _public prototype_ `virtual void StartupModule() override;`
- L57 _public prototype_ `virtual void ShutdownModule() override;`
- L61 _private prototype_ `static void OnTabClosed(TSharedRef<SDockTab> InDockTab);`
- L63 _private member_ `TMap<FName, TSharedRef<IMediaImageViewerFactory>> Factories;`
- L64 _private member_ `TSharedRef<IMediaViewerLibrary> Library;`
- L66 _private prototype_ `void RegisterLevelEditorMenuItems();`
- L67 _private prototype_ `void UnregisterLevelEditorMenuItems();`
- L69 _private prototype_ `TSharedPtr<SMediaViewerTab> GetLiveTab() const;`
- L71 _private prototype_ `TSharedPtr<SMediaViewerTab> SpawnTab() const;`
- L73 _private prototype_ `TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& InArgs);`
- L75 _private prototype_ `bool SetTabBody(const TSharedRef<SMediaViewerTab>& InViewerTab);`
- L77 _private prototype_ `void RegisterDefaultImageViewers();`
- L78 _private prototype_ `void UnregisterAllImageViewers();`
- L80 _private prototype_ `void SaveHistory(const TSharedRef<SMediaViewerLibrary> InLibrary);`
- L82 _private prototype_ `void LoadHistory(const TSharedRef<SMediaViewerLibrary> InLibrary);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaViewer` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MediaViewer` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/MediaViewerStyle.h` (Private)


#### class `UE::MediaViewer::Private::FMediaViewerStyle`  
`class FMediaViewerStyle : public FSlateStyleSet`  
_L13-23_
- inherits: `FSlateStyleSet`
- desc: Style declarations for the image widgets.
- L16 _public member_ `static const FName StyleName;`
- L18 _public prototype_ `static FMediaViewerStyle& Get();`
- L21 _private prototype_ `FMediaViewerStyle();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MediaViewer` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/MediaViewerUtils.h` (Private)


#### class `UMediaViewerUserData`  
`class UMediaViewerUserData : public UAssetUserData`  
_L33-36_
- reflection: `UCLASS()`
- inherits: `UAssetUserData`

#### enum `UE::MediaViewer::Private::EShaderCompileFlags`  
`enum class EShaderCompileFlags : uint8`  
_L43-59_
- desc: Render Material optional flags.
- L45 _public enumerator_ `None = 0`
- L56 _public enumerator_ `EnsureIsComplete = 1<<0` — Flag that controls how the shader-readiness gate is enforced: - if present (default): block on UMaterialInterface::EnsureIsComplete before rendering. The RT is guaranteed populated on success. Use this for one-shot callers and any caller that can't gracefully handle a "not yet" result. - if not present: non-blocking. If the shader map for the current platform isn't complete yet (@see IsMaterialShaderMapComplete) the call returns false with the RT untouched, and the caller is expected to retry on a later frame. Use this for per-frame / mip-cache paths where a synchronous compile stall is undesirable.
- L58 _public enumerator_ `Default = EnsureIsComplete`

#### class `UE::MediaViewer::Private::FMediaViewerUtils`  
`class FMediaViewerUtils`  
_L64-157_
- L68 _public member_ `static constexpr const TCHAR* MipRenderMaterialPath = TEXT("/Sc` — Path to the UI material used by FMediaImageViewer to sample a texture at a specific mip level.
- L76 _public prototype_ `static void PreloadMaterialAssets();` — Loads the materials this module needs to render with and kicks off their shader compilation in the background, so the shader maps are ready before any user-facing code path tries to use them. Strong references are kept for the rest of the editor session. Safe to call repeatedly; each load only happens once.
- L83 _public prototype_ `static void ReleasePreloadedMaterialAssets();` — Releases the strong references held by PreloadMaterialAssets. Must be called from the module's ShutdownModule (i.e. before UObject teardown) so we don't reach into the UObject system from a static destructor at process exit.
- L91 _public prototype_ `static void ConditionallyCompileMaterial(TNotNull<UMaterialInterface*> InMaterial);` — If the material's shader map for the current rendering platform is not complete yet, submits an async compile job at Normal priority. Does not block the game thread: callers needing the material to actually render should fall back gracefully until the shader map reports complete.
- L105 _public prototype_ `static bool IsMaterialShaderMapComplete(TNotNull<UMaterialInterface*> InMaterial);` — Returns true only when the material's shader map for the current rendering platform has been confirmed complete. Returns false in every other case, including: - the material has no parent UMaterial, or - the parent has no FMaterialResource for the current platform yet (a genuine not-ready signal that can appear, for example, after a feature-level switch). Use to gate draw calls that depend on the shaders being ready without forcing a synchronous compile. IsCompiling() / IsComplete() on a freshly created MID are unreliable (see the comment on UMaterialInterface::EnsureIsComplete) - this is why we query the parent's FMaterialResource directly.
- L108 _public prototype_ `static TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(TArrayView64<uint8> InPixelData, EPixelFormat InPixelFormat, const FIntPoint& InTextureSize, const FIntPoint& InPixelCoords, int32 InMipLevel);` — Retrieves the pixel color of a given pixel based on its pixel format. Or none if out of range.
- L115 _public prototype_ `static UTextureRenderTarget2D* CreateRenderTarget(const FIntPoint& InSize, bool bInTransparent, ETextureRenderTargetFormat InFormat = ETextureRenderTargetFormat::RTF_RGBA8);` — Creates a render target texture parented to the transient package. The target will have the @see UMediaViewerUserData asset data to differentiate it from other render targets.
- L123 _public prototype_ `static UTextureRenderTarget2D* RenderMaterial(TNotNull<UMaterialInterface*> InMaterial);` — Creates a 256x256 render target (@see CreateRenderTarget, transparent if the material is a UI material) and renders the material to it. Inherits the two-arg overload's default blocking behavior, so the returned RT is guaranteed populated on first use - intended for one-shot callers (thumbnails, brush creation) that have no retry path.
- L135 _public prototype_ `static bool RenderMaterial( const TNotNull<UMaterialInterface*> InMaterial, const TNotNull<UTextureRenderTarget2D*> InRenderTarget, const EShaderCompileFlags InFlags = EShaderCompileFlags::Default);` — Renders the given material to the given render target using FWidgetRenderer and an FSlateMaterialBrush. @see EShaderCompileFlags for blocking vs non-blocking behavior. @return true if the render was issued, false if it was skipped. False can mean either the material is not a UI material, or (when EShaderCompileFlags::EnsureIsComplete is not set) the shader map wasn't complete. In the latter case the caller MUST treat the return as "try again later" - caching it as success will latch a transient not-ready result into a permanent black RT.
- L141 _public prototype_ `static TSharedRef<IStructureDetailsView> CreateStructDetailsView(TSharedRef<FStructOnScope> InStructOnScope, const FText& InCustomName, FNotifyHook* InNotifyHook = nullptr);` — Creates a struct details view based on the given struct. The view will have most settings disabled for a clean view.
- L149 _public prototype_ `static FColor CorrectGamma(const FColor& InColor);` — Corrects the gamma levels in the given color. @return The corrected color.
- L156 _public prototype_ `static FLinearColor CorrectGamma(const FLinearColor& InColor);` — Corrects the gamma levels in the given color. @return The corrected color.

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace MediaViewer` (scope `UE`)
- L38 _namespace_ `namespace Private` (scope `UE::MediaViewer`)
- L60 _prototype_ `ENUM_CLASS_FLAGS(EShaderCompileFlags);` (scope `UE::MediaViewer::Private`)
- L62 _delegate_ `DECLARE_DELEGATE_OneParam(FRenderComplete, bool ) class FMediaViewerUtils { public: static constexpr const TCHAR* MipRenderMaterialPath = TEXT("/Script/Engine.Material'/MediaViewer/M_TextureMip.M_TextureMip'"); static void PreloadMaterialAssets(); static void ReleasePreloadedMaterialAssets(); static void ConditionallyCompileMaterial(TNotNull<UMaterialInterface*> InMaterial); /** * Returns true only when the material's shader map for the current rendering platform * has been confirmed complete. Returns false in every other case, including: * - the material has no parent UMaterial, or * - the parent has no FMaterialResource for the current platform yet (a genuine * not-ready signal that can appear, for example, after a feature-level switch). * * Use to gate draw calls that depend on the shaders being ready without forcing a * synchronous compile. IsCompiling() / IsComplete() on a freshly created MID are`

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Providers/ViewerTileVisibilityProvider.h` (Private)


#### class `UE::MediaViewer::Private::FViewerTileVisibilityProvider`  
`class FViewerTileVisibilityProvider final : public FMediaTileVisibilityProvider`  
_L15-57_
- inherits: `FMediaTileVisibilityProvider`
- desc: Tile-visibility provider that derives mip pair and tile coverage from a visible source rect plus its on-screen size.
- L32 _public prototype_ `void Update(const FUpdateInputs& InInputs);` — Replace the current viewport state used by the next GatherVisibleTiles call. thread safe.
- L43 _public prototype_ `int32 GetDisplayedMipFloor() const;` — Returns the highest-resolution mip currently visible (floor of the LOD-derived mip, matching what GatherVisibleTiles loads). Returns INDEX_NONE before the first Update call or when the inputs are degenerate. MipOverride, when set, is returned directly. Used by the color picker to sample from the same mip the viewer is displaying - visibility-provider-driven sources only refresh visible mips, so reading mip 0 would return stale or never-uploaded data.
- L46 _public prototype_ `virtual void GatherVisibleTiles(const FMediaSequenceInfo& InSequenceInfo, FMediaTileVisibilityRequest& OutRequest) const override;`
- L48 _public function_ `virtual bool IsAlive() const override`
- L53 _private member_ `mutable FCriticalSection Mutex;` — Guards Inputs against the cross-thread access between Update and GatherVisibleTiles.
- L56 _private member_ `FUpdateInputs Inputs;` — Latest viewport state pushed by the consumer. Default-constructed (empty) until first Update call.

#### struct `UE::MediaViewer::Private::FViewerTileVisibilityProvider::FUpdateInputs`  
`struct FUpdateInputs`  
_L19-29_
- desc: Snapshot of the consumer-pushed viewport state consumed by the next GatherVisibleTiles call.
- L22 _public member_ `FBox2D VisibleSourceRect = FBox2D(ForceInit);` — Visible part of the source in source-pixel coordinates. Empty until first Update.
- L25 _public member_ `FVector2D DisplayedSizePx = FVector2D::ZeroVector;` — Physical-pixel size of the area displaying VisibleSourceRect. Drives mip selection.
- L28 _public member_ `TOptional<int32> MipOverride;` — Optional pinned mip; overrides the LOD-derived mip pair when set.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MediaViewer` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/MediaViewerLibraryGroupItem.h` (Private)


#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<UE::MediaViewer::IMediaViewerLibrary::FGroupItem>`  
_L9-15_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L12-14_

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<UE::MediaViewer::IMediaViewerLibrary::FGroupItem>`  
_L21-67_
- desc: Functionality (e.g. setting the value, testing invalid value) specialized for FGroupItem.
- L24 _public typedef_ `typedef UE::MediaViewer::IMediaViewerLibrary::FGroupItem NullableType;`
- L26 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MediaViewer::IMediaViewerLibrary::FGroupItem, TSharedRef<ITableRow>, false>;`
- L27 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MediaViewer::IMediaViewerLibrary::FGroupItem, FSparseItemInfo, false>;`
- L28 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MediaViewer::IMediaViewerLibrary::FGroupItem>;`
- L31 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector& InCollector, TArray<UE::MediaViewer::IMediaViewerLibrary::FGroupItem>& ItemsWithGeneratedWidgets, TSet<UE::MediaViewer::IMediaViewerLibrary::FGroupItem>& SelectedItems, TMap<const U*, UE::MediaViewer::IMediaViewerLibrary::FGroupItem>& WidgetToItemMap)`
- L38 _public function_ `static bool IsPtrValid(const UE::MediaViewer::IMediaViewerLibrary::FGroupItem& InValue)`
- L43 _public function_ `static void ResetPtr(UE::MediaViewer::IMediaViewerLibrary::FGroupItem& InValue)`
- L49 _public function_ `static UE::MediaViewer::IMediaViewerLibrary::FGroupItem MakeNullPtr()`
- L54 _public function_ `static UE::MediaViewer::IMediaViewerLibrary::FGroupItem NullableItemTypeConvertToItemType(const UE::MediaViewer::IMediaViewerLibrary::FGroupItem& InValue)`
- L59 _public function_ `static FString DebugDump(UE::MediaViewer::IMediaViewerLibrary::FGroupItem InValue)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L64-66_

#### Free symbols / members of external scopes

- L13 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon9a6f30410103`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/MediaViewerLibraryItemAssetDragDropOperation.h` (Private)


#### class `UE::MediaViewer::Private::FMediaViewerLibraryItemAssetDragDropOperation`  
`class FMediaViewerLibraryItemAssetDragDropOperation : public FAssetDragDropOp`  
_L25-48_
- inherits: `FAssetDragDropOp`
- L28 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMediaViewerLibraryItemAssetDragDropOperation, FAssetDragDropOp) FMediaViewerLibraryItemAssetDragDropOperation(const TSharedRef<IMediaViewerLibrary>& InLibrary, const IMediaViewerLibrary::FGroupItem& InGroupItem);`
- L33 _public prototype_ `virtual ~FMediaViewerLibraryItemAssetDragDropOperation() override = default;`
- L35 _public prototype_ `const IMediaViewerLibrary::FGroupItem& GetGroupItem() const;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L39 _public prototype_ `virtual FCursorReply OnCursorQuery() override;`
- L43 _protected member_ `IMediaViewerLibrary::FGroupItem GroupItem;`
- L44 _protected member_ `TSharedPtr<FSlateBrush> ThumbnailBrush;`
- L45 _protected member_ `TSharedRef<SBorder> Decorator;`
- L47 _protected prototype_ `void CreateDecorator(const TSharedPtr<FMediaViewerLibraryItem>& InItem);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MediaViewer` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MediaViewer` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/MediaViewerLibraryItemDragDropOperation.h` (Private)


#### class `UE::MediaViewer::Private::FMediaViewerLibraryItemDragDropOperation`  
`class FMediaViewerLibraryItemDragDropOperation : public FDecoratedDragDropOp`  
_L25-48_
- inherits: `FDecoratedDragDropOp`
- L28 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMediaViewerLibraryItemDragDropOperation, FDecoratedDragDropOp) FMediaViewerLibraryItemDragDropOperation(const TSharedRef<IMediaViewerLibrary>& InLibrary, const IMediaViewerLibrary::FGroupItem& InGroupItem);`
- L33 _public prototype_ `virtual ~FMediaViewerLibraryItemDragDropOperation() override = default;`
- L35 _public prototype_ `const IMediaViewerLibrary::FGroupItem& GetGroupItem() const;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L39 _public prototype_ `virtual FCursorReply OnCursorQuery() override;`
- L43 _protected member_ `IMediaViewerLibrary::FGroupItem GroupItem;`
- L44 _protected member_ `TSharedPtr<FSlateBrush> ThumbnailBrush;`
- L45 _protected member_ `TSharedRef<SBorder> Decorator;`
- L47 _protected prototype_ `void CreateDecorator(const TSharedPtr<FMediaViewerLibraryItem>& InItem);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MediaViewer` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MediaViewer` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/MediaViewerSettings.h` (Private)


#### enum `EMediaViewerMediaSyncType`  
`enum class EMediaViewerMediaSyncType : uint8`  
_L17-30_
- reflection: `UENUM()`
- L20 _public enumerator_ `RelativeTime` — The offset is relative to the start time on both videos. A scrub change of 2s in video A will move video B also by 2s.
- L23 _public enumerator_ `RelativeProgress` — The offset is relative to slider value on both videos. A scrub change of 10% in video A will move video B by 10%.
- L26 _public enumerator_ `AbsoluteTime` — Time is synced exactly between videos. Video A changing from 5s to 10s will change video B from *anything* to 10s.
- L29 _public enumerator_ `AbsoluteProgress` — Video progress is synced exactly between videos. Video A changing from 10% to 30% will change video B from *anything* to 30%.

#### struct `FMediaViewerSettings`  
`struct FMediaViewerSettings`  
_L34-79_
- reflection: `USTRUCT()`
- desc: Settings for the viewer.
- L40 _public member_ `FLinearColor ClearColor = FStyleColors::Black.GetSpecifiedColor();` — `UPROPERTY(EditAnywhere, Config, Category = "Background")` — Color painted to the viewer behind the images.
- L44 _public member_ `TSoftObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY(EditAnywhere, Config, Category = "Background")` — Texture tiled behind the images, on top of the clear color.
- L48 _public member_ `FVector2D Offset = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, Config, Category = "Background", meta = (EditCondition = "Texture != nullptr"))` — Offset of the tiled background texture.
- L53 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Config, Category = "Background", meta = (UIMin = 0.1, ClampMin = 0.1, UIMax = 10, ClampMax = 10, EditCondition = "Texture != nullptr"))` — Scale of the tiled background texture.
- L57 _public member_ `bool bAreTransformsLocked = true;` — `UPROPERTY(EditAnywhere, Config, Category = "AB View", DisplayName = "Lock Transforms")` — If true, when one image transform changes, the other image transforms will change an equal amount.
- L61 _public member_ `TEnumAsByte<EOrientation> ABOrientation = Orient_Horizontal;` — `UPROPERTY(Config)` — When in AB view, whether the viewers are split horizontally or vertically.
- L66 _public member_ `float ABSplitterLocation = 50.f;` — `UPROPERTY(EditAnywhere, Config, Category = "AB View", DisplayName = "AB Splitter Location", meta = (UIMin = 0, ClampMin = 0, UIMax = 100, ClampMax = 100, Units = "Percent"))` — Splitter location (0-100)
- L75 _public member_ `float SecondImageOpacity = 100.f;` — `UPROPERTY(EditAnywhere, Config, Category = "AB View", DisplayName = "B Image Opacity", meta = (UIMin = 0, ClampMin = 0, UIMax = 100, ClampMax = 100, Units = "Percent"))` — Opacity of the second/B image (0-100). At 100%, the first/A image is rendered only on the left/top side. Below 100%, the first/A image is rendered on the entire panel with B overlaid on top of it, translucently.
- L78 _public member_ `EMediaViewerMediaSyncType MediaSyncType = EMediaViewerMediaSyncType::RelativeTime;` — `UPROPERTY(EditAnywhere, Config, Category = "Media")`

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaImageViewerDetails.h` (Private)


#### class `UE::MediaViewer::Private::SMediaImageViewerDetails`  
`class SMediaImageViewerDetails : public SCompoundWidget`  
_L20-47_
- inherits: `SCompoundWidget`
- L22 _private function_ `SLATE_DECLARE_WIDGET(SMediaImageViewerDetails, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaImageViewerDetails)`
- L29 _public prototype_ `SMediaImageViewerDetails();`
- L30 _public prototype_ `virtual ~SMediaImageViewerDetails() = default;`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, EMediaImageViewerPosition InPosition, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L35 _protected member_ `EMediaImageViewerPosition Position;`
- L36 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;`
- L38 _protected member_ `TSharedPtr<IStructureDetailsView> PanelDetailsView;`
- L39 _protected member_ `TSharedPtr<IStructureDetailsView> PaintDetailsView;`
- L40 _protected member_ `TSharedPtr<IStructureDetailsView> CustomDetailsView;`
- L42 _protected prototype_ `TSharedRef<SWidget> CreatePanelSettings();`
- L44 _protected prototype_ `TSharedRef<SWidget> CreatePaintSettings();`
- L46 _protected prototype_ `TSharedPtr<SWidget> CreateCustomSettings();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MediaViewer` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MediaViewer` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaImageViewerOverlay.h` (Private)


#### class `UE::MediaViewer::Private::SMediaImageViewerOverlay`  
`class SMediaImageViewerOverlay : public SCompoundWidget`  
_L29-195_
- inherits: `SCompoundWidget`
- desc: Display and control for a viewer. Status bar, mouse and keyboard input, etc.
- L31 _private function_ `SLATE_DECLARE_WIDGET(SMediaImageViewerOverlay, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaImageViewerOverlay) : _bComparisonView(true) , _bScaleToFit(false)`
- L42 _public prototype_ `SMediaImageViewerOverlay();`
- L44 _public prototype_ `virtual ~SMediaImageViewerOverlay() override = default;`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, EMediaImageViewerPosition InPosition, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L48 _public prototype_ `void PostConstruct();`
- L50 _public prototype_ `TSharedPtr<FMediaImageViewer> GetImageViewer() const;`
- L52 _public prototype_ `const TSharedRef<FUICommandList>& GetCommandList() const;`
- L55 _public prototype_ `FIntPoint GetImageViewerPixelCoordinates() const;` — Gets the pixel coordinate of mouse on the image. May be outside of the image.
- L58 _public prototype_ `FVector2D GetImageViewerPixelCoordinates_Exact() const;` — Gets the pixel coordinate of mouse on the image. May be outside of the image. Subpixel accuracy
- L60 _public prototype_ `bool IsCursorOverImageViewer() const;`
- L63 _public prototype_ `void UpdateMouse(const TOptional<FVector2D>& InMousePosition);` — Triggers a mouse update.
- L65 _public prototype_ `bool IsOverlayEnabled() const;`
- L66 _public prototype_ `void ToggleOverlay();`
- L69 _public prototype_ `void MultiplyScaleAroundCursor(float InMultipler);` — Zooms the view in or out and maintains the cursor in the same relative position.
- L72 _public prototype_ `void ScaleToFit(bool bInUseTransformLock);` — Scales the image to fit the viewer.
- L75 _public prototype_ `void Try_Mirror(EMediaImageMirrorPlane InPlane);` — Either mirror this viewer or all viewers if transforms are locked.
- L78 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& InMyGeometry, const FPointerEvent& InCursorEvent) const override;`
- L79 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InMyGeometry, const FKeyEvent& InKeyEvent) override;`
- L80 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L81 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L82 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L83 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L84 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L100 _protected member_ `EMediaImageViewerPosition Position;`
- L101 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;`
- L102 _protected member_ `TSharedPtr<FMediaViewerLibraryItem> CachedItem;`
- L103 _protected member_ `TSharedRef<FUICommandList> CommandList;`
- L104 _protected member_ `bool bComparisonView;`
- L106 _protected member_ `FName DragButtonName;` — Name of the button which is currently performing a drag operation.
- L107 _protected member_ `EDragType DragType;`
- L108 _protected member_ `FVector2D DragStartCursor;`
- L109 _protected member_ `FVector DragStartOffset;`
- L110 _protected member_ `float LastDragScaleValue;`
- L112 _protected member_ `FIntPoint LastCursorPosition;` — For moving the image based on cursor location.
- L113 _protected member_ `TSharedPtr<SMediaImageViewerStatusBar> StatusBar;`
- L114 _protected member_ `TSharedPtr<SOverlay> Overlay;`
- L116 _protected member_ `bool bOverlayEnabled;` — Toggles the visibility of the overlay.
- L118 _protected member_ `bool bScaleToFit;` — Whether, on first valid paint, it should scale to fit.
- L120 _protected prototype_ `void BindCommands();`
- L122 _protected prototype_ `TSharedRef<SWidget> CreateOverlay(bool bInComparisonView);`
- L124 _protected prototype_ `TSharedRef<SWidget> CreateStatusBar(const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L126 _protected prototype_ `void OnDragButtonUp(FName InKeyName);`
- L127 _protected prototype_ `void UpdateDragPosition();`
- L128 _protected prototype_ `void UpdateDragScale();`
- L129 _protected prototype_ `void UpdateDragExternal();`
- L131 _protected prototype_ `EVisibility GetDragDescriptionVisibility() const;`
- L134 _protected prototype_ `FVector GetOffset() const;` — Interact with the image viewer's offset.
- L135 _protected prototype_ `void Try_AddOffset(FVector InOffset);` — Either local or 'send to all' if transform is locked
- L136 _protected prototype_ `void AddOffset(const FVector& InOffset);`
- L137 _protected prototype_ `void SetOffset(const FVector& InOffset);`
- L140 _protected prototype_ `FRotator GetRotation() const;` — Interact with the image viewer's rotation.
- L141 _protected prototype_ `void Try_AddRotation(FRotator InRotation);` — Either local or 'send to all' if transform is locked
- L142 _protected prototype_ `void AddRotation(const FRotator& InRotation);`
- L143 _protected prototype_ `void SetRotation(const FRotator& InRotation);`
- L146 _protected prototype_ `float GetScale() const;` — Interact with the image viewer's scale.
- L147 _protected prototype_ `void Try_SetScale(float InScale);` — Either local or 'send to all' if transform is locked
- L148 _protected prototype_ `void SetScale(float InScale);`
- L149 _protected prototype_ `float GetScaleModifier();`
- L150 _protected prototype_ `void ScaleUp();`
- L151 _protected prototype_ `void ScaleDown();`
- L152 _protected prototype_ `void Try_MultipyScale(float InMultiple);`
- L153 _protected prototype_ `void MultiplyScale(float InMultiple);`
- L155 _protected prototype_ `ECheckBoxState IsAutoFilteringEnabled() const;`
- L156 _protected prototype_ `void ToggleAutoFiltering();`
- L158 _protected prototype_ `bool CanTogglePixelGrid() const;`
- L159 _protected prototype_ `ECheckBoxState IsPixelGridEnabled() const;`
- L160 _protected prototype_ `void TogglePixelGrid();`
- L162 _protected prototype_ `ECheckBoxState GetMipOverrideState() const;`
- L163 _protected prototype_ `void ToggleMipOverride();`
- L164 _protected prototype_ `void IncreaseMipLevel();`
- L165 _protected prototype_ `void DecreaseMipLevel();`
- L168 _protected prototype_ `void ResetTransform();` — Interact with the image viewer's entire transform.
- L169 _protected prototype_ `bool CanResetAllTransforms();`
- L170 _protected prototype_ `void ResetAllTransforms();`
- L171 _protected prototype_ `void Try_ResetTransform();` — Either local or 'send to all' if transform is locked
- L172 _protected prototype_ `void Try_SetTransform(FVector InOffset, FRotator InRotation, float InScale);` — Either local or 'send to all' if transform is locked
- L173 _protected prototype_ `bool CanCopyTransform();`
- L174 _protected prototype_ `void CopyTransform();`
- L177 _protected prototype_ `ECheckBoxState GetMirroredState(EMediaImageMirrorPlane InPlane) const;` — Interact with the image viewer's mirror settings.
- L178 _protected prototype_ `void Mirror(EMediaImageMirrorPlane InPlane);`
- L181 _protected prototype_ `uint8 GetMipLevel() const;` — Interact with the image viewer's mip level.
- L182 _protected prototype_ `void AdjustMipLevel(int8 InAdjustment);`
- L183 _protected prototype_ `void SetMipLevel(uint8 InMipLevel);`
- L186 _protected prototype_ `void CopyColor();` — Copies the color under the cursor, if possible.
- L189 _protected prototype_ `bool CanAddToLibrary() const;` — For adding the active image viewer to the library, if it can.
- L190 _protected prototype_ `void AddToLibrary();`
- L192 _protected prototype_ `TSharedRef<SWidget> CreateMenu();`
- L194 _protected prototype_ `EVisibility HintText_GetVisibility() const;`

#### enum `UE::MediaViewer::Private::SMediaImageViewerOverlay::EDragType`  
`enum class EDragType : uint8`  
_L88-98_
- L91 _public enumerator_ `None` — No drag operatio is active.
- L93 _public enumerator_ `Offset` — Whether the widget is performing an internal offset drag operation.
- L95 _public enumerator_ `Scale` — Whether the widget is performing an internal scale drag operation.
- L97 _public enumerator_ `External` — Whether an image viewer is performing its own drag operation.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MediaViewer` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MediaViewer` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaImageViewerStatusBar.h` (Private)


#### class `UE::MediaViewer::Private::SMediaImageViewerStatusBar`  
`class SMediaImageViewerStatusBar : public SCompoundWidget`  
_L20-46_
- inherits: `SCompoundWidget`
- L22 _private function_ `SLATE_DECLARE_WIDGET(SMediaImageViewerStatusBar, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaImageViewerStatusBar)`
- L29 _public prototype_ `SMediaImageViewerStatusBar();`
- L31 _public prototype_ `virtual ~SMediaImageViewerStatusBar() override = default;`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, EMediaImageViewerPosition InPosition, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L36 _protected member_ `EMediaImageViewerPosition Position;`
- L37 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;`
- L39 _protected prototype_ `TSharedRef<SWidget> BuildStatusBar();`
- L41 _protected prototype_ `FText GetResolutionLabel() const;`
- L43 _protected prototype_ `FText GetColorPickerLabel() const;`
- L45 _protected prototype_ `FLinearColor GetColorBlockColor() const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaViewer` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MediaViewer` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaSourceOverlay.h` (Private)


#### class `UE::MediaViewer::Private::SMediaSourceOverlay`  
`class SMediaSourceOverlay : public SCompoundWidget`  
_L37-154_
- inherits: `SCompoundWidget`
- L39 _private function_ `SLATE_DECLARE_WIDGET(SMediaSourceOverlay, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaSourceOverlay)`
- L46 _public prototype_ `virtual ~SMediaSourceOverlay() override = default;`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMediaSourceImageViewer>& InImageViewer, EMediaImageViewerPosition InPosition, const TSharedPtr<FMediaViewerDelegates>& InDelegates);`
- L52 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _protected member_ `TWeakPtr<FMediaSourceImageViewer> ImageViewerWeak;` — The image viewer being controlled by this overlay.
- L60 _protected member_ `EMediaImageViewerPosition Position;` — The position in the viewer occupied by this image viewer.
- L63 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;` — The delegates used to communicate with other widgets.
- L66 _protected member_ `TSharedPtr<SBox> Container;` — Container so the overlay can be toggled on and off.
- L69 _protected member_ `TOptional<float> FrameRateFloat;` — The frame rate stored before a scrub-based pause event.
- L71 _protected member_ `mutable TOptional<FText> TotalFrames;`
- L72 _protected member_ `mutable TOptional<FText> TotalTime;`
- L75 _protected member_ `TVariant<FTimespan, float> SyncedScrubStartTime;` — When a sync scrub is started, this stores the start of this media.
- L76 _protected member_ `TOptional<float> RateWhenScrubEventReceived;`
- L79 _protected member_ `double LastInteractionTime = -1.0;` — The last time the mouse was moved over the widget.
- L81 _protected prototype_ `UMediaStream* GetMediaStream() const;`
- L83 _protected prototype_ `IMediaStreamPlayer* GetMediaStreamPlayer() const;`
- L85 _protected prototype_ `UMediaPlayer* GetMediaPlayer() const;`
- L88 _protected prototype_ `void TrySetFrameRate();` — Attempt to store the frame rate of the currently playing media.
- L90 _protected prototype_ `void BindCommands();`
- L92 _protected prototype_ `TSharedRef<SWidget> CreateSlider();`
- L95 _protected prototype_ `TSharedRef<SWidget> CreateControls();` — Create play controls. Play, pause, etc.
- L97 _protected prototype_ `FText GetCurrentFrame() const;`
- L98 _protected prototype_ `FText GetTotalFrames() const;`
- L100 _protected prototype_ `FText GetCurrentTime() const;`
- L101 _protected prototype_ `FText GetTotalTime() const;`
- L103 _protected prototype_ `bool Rewind_IsEnabled() const;`
- L104 _protected prototype_ `FReply Rewind_OnClicked();`
- L106 _protected prototype_ `bool Reverse_IsEnabled() const;`
- L107 _protected prototype_ `const FSlateBrush* Reverse_GetBrush() const;`
- L108 _protected prototype_ `FText Reverse_GetToolTip() const;`
- L109 _protected prototype_ `FReply Reverse_OnClicked();`
- L111 _protected prototype_ `bool StepBack_IsEnabled() const;`
- L112 _protected prototype_ `FReply StepBack_OnClicked();`
- L114 _protected prototype_ `bool Play_IsEnabled() const;`
- L115 _protected prototype_ `const FSlateBrush* Play_GetBrush() const;`
- L116 _protected prototype_ `FText Play_GetToolTip() const;`
- L117 _protected prototype_ `FReply Play_OnClicked();`
- L119 _protected prototype_ `bool StepForward_IsEnabled() const;`
- L120 _protected prototype_ `FReply StepForward_OnClicked();`
- L122 _protected prototype_ `bool Forward_IsEnabled() const;`
- L123 _protected prototype_ `FReply Forward_OnClicked();`
- L126 _protected prototype_ `void SendEvent(FName InEventName);` — Broadcasts an event that can be received by others.
- L129 _protected prototype_ `void ReceiveEvent(const FMediaImageViewerEventParams& InEventParams);` — Receive an event broadcast by somebody else.
- L132 _protected prototype_ `void OnScrub(IMediaPlayerSlider::EScrubEventType InScrubEvent, TConstArrayView<UMediaPlayer*> InMediaPlayers, float InScrubPosition);` — Triggered when this player's scrub bar is manually moved.
- L135 _protected prototype_ `static bool Command_Rewind(UMediaPlayer* InMediaPlayer);` — Execute commands on the given media player.
- L136 _protected prototype_ `static bool Command_Reverse(UMediaPlayer* InMediaPlayer);`
- L137 _protected prototype_ `static bool Command_StepBack(UMediaPlayer* InMediaPlayer);`
- L138 _protected prototype_ `static bool Command_Play(UMediaPlayer* InMediaPlayer);`
- L139 _protected prototype_ `static bool Command_Pause(UMediaPlayer* InMediaPlayer);`
- L140 _protected prototype_ `static bool Command_StepForward(UMediaPlayer* InMediaPlayer);`
- L141 _protected prototype_ `static bool Command_Forward(UMediaPlayer* InMediaPlayer);`
- L144 _protected prototype_ `void ReceiveScrub(const MediaSourceOverlay::Events::FMediaImageViewerScrubEventParams& InEventParams);` — Triggered when a scrub event is received from someone else.
- L147 _protected prototype_ `void AddOffset_Time(float InOffset);` — Add a offset to the current media. Optionally broadcasts it to others as a scrub event.
- L150 _protected prototype_ `void AddOffset_Frame(int32 InOffset);` — Add a offset to the current media. Optionally broadcasts it to others as a scrub event. Supports 1 and -1.
- L153 _protected prototype_ `void TogglePlay();` — Toggles between play and pause. Forward only.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MediaViewer` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace MediaViewer` (scope `UE`)
- L27 _namespace_ `namespace Private` (scope `UE::MediaViewer`)
- L32 _namespace_ `namespace MediaSourceOverlay` (scope `UE::MediaViewer::Private`)
- L32 _namespace_ `namespace Events` (scope `UE::MediaViewer::Private::MediaSourceOverlay`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewer.h` (Private)


#### enum `EMediaImageViewerActivePosition`  
`enum class EMediaImageViewerActivePosition : uint8`  
_L43-47_
- reflection: `UENUM()`
- L45 _public enumerator_ `Single`
- L46 _public enumerator_ `Both`

#### class `UE::MediaViewer::Private::SMediaViewer`  
`class SMediaViewer : public SCompoundWidget, public FGCObject`  
_L52-282_
- inherits: `SCompoundWidget,FGCObject`
- L54 _private function_ `SLATE_DECLARE_WIDGET(SMediaViewer, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaViewer) : _ClearColor(FLinearColor::Black)`
- L63 _public member_ `static constexpr float MaxScale = 20.f;`
- L64 _public member_ `static constexpr float MinScale = 0.01f;`
- L66 _public prototype_ `SMediaViewer();`
- L70 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SMediaViewerTab>& InTab, const FMediaViewerArgs& InMediaViewerArgs, const TSharedRef<FMediaImageViewer>& InImageViewerFirst, const TSharedRef<FMediaImageViewer>& InImageViewerSecond);`
- L73 _public function_ `const FMediaViewerArgs& GetArgs() const`
- L75 _public prototype_ `TSharedRef<IMediaViewerLibrary> GetLibrary() const;`
- L77 _public prototype_ `TSharedPtr<FMediaImageViewer> GetImageViewer(EMediaImageViewerPosition InPosition) const;`
- L79 _public prototype_ `void SetImageViewer(EMediaImageViewerPosition InPosition, const TSharedRef<FMediaImageViewer>& InImageViewer);`
- L81 _public prototype_ `void ClearImageViewer(EMediaImageViewerPosition InPosition);`
- L83 _public prototype_ `bool IsShowingBothImageViewers() const;`
- L85 _public prototype_ `void SwapABImageViewers();`
- L87 _public prototype_ `void SetSingleView();`
- L89 _public prototype_ `void SetABView();`
- L92 _public prototype_ `void SetABOrientation(EOrientation InOrientation);` — Sets the orientation of the A/B view.
- L95 _public prototype_ `EMediaImageViewerPosition GetHoveredImageViewer() const;` — Returns the position that the mouse is hovering based _only_ on the position of the mouse compared to the splitter.
- L98 _public prototype_ `FVector2D GetLocalCursorPosition() const;` — Returns the local position of the cursor on the viewer.
- L101 _public prototype_ `void InvalidateView();` — Triggers a recreation of the view on tick.
- L104 _public prototype_ `TSharedRef<FMediaViewerDelegates> GetDelegates() const;` — Returns the bound delegates of this viewer.
- L106 _public prototype_ `FMediaViewerState GetState() const;`
- L108 _public prototype_ `void LoadState(const FMediaViewerState& InState);`
- L110 _public prototype_ `void SaveBookmark(int32 InIndex, bool bInSaveConfig);`
- L112 _public prototype_ `void LoadBookmark(int32 InIndex);`
- L114 _public prototype_ `void SaveLastOpenedState(bool bInSaveConfig);`
- L117 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L118 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& InOutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L120 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InMyGeometry, const FKeyEvent& InKeyEvent) override;`
- L124 _public prototype_ `virtual FString GetReferencerName() const override;`
- L125 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L129 _protected member_ `static const FSlateColorBrush BackgroundColorBrush;`
- L132 _protected member_ `TWeakPtr<SMediaViewerTab> Tab;` — Owner of this viewer.
- L134 _protected member_ `FMediaViewerArgs MediaViewerArgs;` — Construction args (unchangeable)
- L136 _protected member_ `FMediaViewerSettings MediaViewerSettings;` — Mutable settings
- L138 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;` — Delegates for sub-widgets. Similar to an advanced command list.
- L140 _protected member_ `TSharedRef<FUICommandList> CommandList;` — Command list for the entire viewer.
- L143 _protected member_ `TSharedPtr<SMediaViewerLibraryPrivate> Library;` — Library of available image viewers
- L145 _protected member_ `TSharedPtr<SVerticalBox> Layout;` — Main layout of the viewer.
- L147 _protected member_ `SVerticalBox::FSlot* ToolbarSlot;` — Toolbar slot for direct access and replacement.
- L149 _protected member_ `SVerticalBox::FSlot* ContentSlot;` — Content slot for direct access and replacement.
- L152 _protected member_ `mutable FSlateImageBrush BackgroundTextureBrush;` — Background brush used to render the tiled background texture.
- L155 _protected member_ `TSharedPtr<FMediaImageViewer> ImageViewers[static_cast<int32>(EMediaImageViewerPosition::COUNT)];` — Viewers currently open in the viewer. May be FNullImageViewer for an invalid viewer.
- L157 _protected member_ `EMediaImageViewerActivePosition ActiveView;` — The active view configuration.
- L159 _protected member_ `EMediaImageViewerActivePosition RequestedView;` — The requested view configuration.
- L161 _protected member_ `bool ScaleToFit[static_cast<int32>(EMediaImageViewerPosition::COUNT)];` — Whether to scale to fit on rebuild view.
- L164 _protected member_ `int32 TickCount = 0;` — A check to see if we need to load old states.
- L166 _protected member_ `FVector2D CursorLocalPosition;`
- L168 _protected member_ `mutable FVector2D ViewerSize;`
- L169 _protected member_ `mutable FVector2D ViewerPosition;`
- L172 _protected member_ `bool bInvalidated;` — Do we need to be recreated next tick?
- L175 _protected prototype_ `void CreateDelegates();` — Create and assign the list of delegates.
- L178 _protected prototype_ `void BindCommands();` — Binds commands.
- L181 _protected prototype_ `TSharedRef<SMediaImageViewerOverlay> CreateOverlay(EMediaImageViewerPosition InPosition, bool bInComparisonView);` — Create and overlay widget for the given position.
- L184 _protected prototype_ `TSharedRef<SWidget> CreateToolbar();` — Creates the toolbar.
- L187 _protected prototype_ `void CreateView();` — Examines the available images and creates an appropriate view.
- L190 _protected prototype_ `void CreateSingleView(EMediaImageViewerPosition InPosition);` — Creates a view for a single image viewer.
- L193 _protected prototype_ `void CreateABView();` — Creates a view comparing 2 images.
- L196 _protected prototype_ `TSharedPtr<SMediaImageViewerOverlay> GetOverlay(EMediaImageViewerPosition InPosition) const;` — Returns the overlay for the given position, if it exists.
- L199 _protected prototype_ `float GetDPIScale() const;` — Returns the DPI scale of the window.
- L202 _protected prototype_ `void OnABResized(float InSize);` — When the splitter is resized, this is triggered to update @see ABSplitterLocation.
- L205 _protected prototype_ `bool IsImageViewerNull(EMediaImageViewerPosition InPosition) const;` — Returns trus if the image viewer is null or an FNullImageViewer.
- L208 _protected prototype_ `void AddOffsetToAll(const FVector& InOffset);` — Adds an offset to all image viewers.
- L211 _protected prototype_ `void AddRotationToAll(const FRotator& InRotation);` — Adds a rotation to all image viewers.
- L214 _protected prototype_ `void MultiplyScaleToAll(float InMultiple);` — Multiplays the scale of all image viewers by a value.
- L217 _protected prototype_ `void MultiplyScaleAroundCursorToAll(float InMultiple);` — Multiplays the scale of all image viewers by a value keeping the cursor in the same relative position for each image.
- L220 _protected prototype_ `void SetTransformToAll(const FVector& InOffset, const FRotator& InRotation, float InScale);` — Sets the transform of all image viewers to the given values.
- L223 _protected prototype_ `void ResetTransformToAll();` — Resets the transform of all image viewers to 0,0,0; 0,0,0; 1
- L226 _protected prototype_ `void CopyTransformToAll(EMediaImageViewerPosition InPosition) const;` — Copies the transform of the given image viewer to all other image viewers.
- L229 _protected prototype_ `void MirrorAll(EMediaImageMirrorPlane InPlane, bool bInSet);` — Sets the mirror plane flag on all image viewers.
- L235 _protected prototype_ `FIntPoint GetPixelCoordinates(EMediaImageViewerPosition InPosition) const;` — Returns the coordinates of the given image that the mousee is currently hovering. May not be inside the image.
- L238 _protected prototype_ `bool IsOverImage(EMediaImageViewerPosition InPosition) const;` — Returns if the mouse is currently hovering the given image. Inside the image.
- L241 _protected prototype_ `TSharedPtr<FUICommandList> GetOverlayCommandList(EMediaImageViewerPosition InPosition) const;` — Returns the command list of the given overlay.
- L244 _protected prototype_ `float GetSecondImageOpacity() const;` — For dealing with the second/B image opacity.
- L245 _protected prototype_ `void AdjustSecondImageOpacity(float InAdjustment);`
- L246 _protected prototype_ `void SetSecondImageOpacity(float InOpacity);`
- L249 _protected prototype_ `ECheckBoxState AreOverlaysEnabled() const;` — For toggling off the status bar and custom overlays of the image viewers.
- L250 _protected prototype_ `void ToggleOverlays();`
- L253 _protected prototype_ `ECheckBoxState AreLockedTransformEnabled() const;` — For locking the image viewer transforms.
- L254 _protected prototype_ `void ToggleLockedTransform();`
- L256 _protected prototype_ `void CheckLastOpenedState();`
- L258 _protected prototype_ `bool CanTakeSnapshot() const;`
- L259 _protected prototype_ `void TakeSnapshot();`
- L261 _protected prototype_ `void DrawImageViewers(UCanvas* InCanvas) const;`
- L263 _protected prototype_ `void OpenNewTab();`
- L265 _protected prototype_ `void LoadLastOpenedState();`
- L267 _protected prototype_ `bool CanOpenBookmark(int32 InIndex) const;`
- L268 _protected prototype_ `void OpenBookmark(int32 InIndex);`
- L269 _protected prototype_ `bool CanSaveBookmark() const;`
- L270 _protected prototype_ `void SaveBookmark(int32 InIndex);`
- L272 _protected prototype_ `void OnOwnerCleanup(UObject* InOuter);`
- L274 _protected prototype_ `void OnWorldCleanUp(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);`
- L276 _protected prototype_ `void OnPackageDeleted(UPackage* InPackage);`
- L278 _protected prototype_ `void OnAssetsDeleted(const TArray<UObject*>& InAssets);`
- L281 _protected prototype_ `void Mirror(EMediaImageMirrorPlane InPlane);` — Forwards the mirror bind to the first valid viewer.

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MediaViewer` (scope `UE`)
- L33 _namespace_ `namespace Private` (scope `UE::MediaViewer`)
- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace MediaViewer` (scope `UE`)
- L49 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewerDropTarget.h` (Private)


#### class `UE::MediaViewer::Private::SMediaViewerDropTarget`  
`class SMediaViewerDropTarget : public SCompoundWidget`  
_L20-98_
- inherits: `SCompoundWidget`
- L22 _private function_ `SLATE_DECLARE_WIDGET(SMediaViewerDropTarget, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaViewerDropTarget) : _Position(EMediaImageViewerPosition::First) , _bComparisonView(false) , _bForceComparisonView(false)`
- L36 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L39 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& InDragDropEvent) override;`
- L44 _protected prototype_ `static TArray<FAssetData> GetAssetsWithImageViewer(TConstArrayView<FAssetData> InAssets);` — Filters the given assets and returns the ones with a registered image viewer handler class.
- L46 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;`
- L47 _protected member_ `EMediaImageViewerPosition Position;`
- L48 _protected member_ `bool bComparisonView;`
- L49 _protected member_ `bool bForceComparisonView;`
- L51 _protected prototype_ `EVisibility GetDragDescriptionVisibility() const;`
- L53 _protected prototype_ `bool OnAllowDrop(TSharedPtr<FDragDropOperation> InDragDropOperation) const;`
- L55 _protected prototype_ `bool OnIsRecognized(TSharedPtr<FDragDropOperation> InDragDropOperation) const;`
- L57 _protected prototype_ `FReply OnDropped(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L64 _protected prototype_ `void HandleDroppedMediaViewerOp(const FMediaViewerLibraryItemDragDropOperation& InMediaViewerOp);` — Takes the dragged library item(s) and displays them in the viewer. If one is dragged, it will replace the current image viewer. If 2 or more are dragged, the first 2 will be put in comparison mode, replacing whatever is being shown.
- L71 _protected prototype_ `void HandleDroppedAssets(const TArrayView<FAssetData> InDroppedAssets);` — Takes the dragged assets and displays them in the viewer, if they have a registered image viewer handler class. If one is dragged, it will replace the current image viewer. If 2 or more are dragged, the first 2 will be put in comparison mode, replacing whatever is being shown.
- L80 _protected prototype_ `void HandleDroppedFileOp(const FExternalDragOperation& InFileDragDropOp);` — Takes the dragged files and attempts to open them. Single standalone images are loaded as a transient texture; numbered sequence frames and directories use the image media player; other recognized media types use UMediaPlayer. If one is dragged, it will replace the current image viewer. If 2 or more are dragged, the first 2 will be put in comparison mode, replacing whatever is being shown.
- L87 _protected prototype_ `bool CreateAndSetImageSequence(const FExternalDragOperation& InFileDragDropOp);` — Looks at the dragged files and determines if it can be turned into an image media source. If it can, it will ask the user to save the asset and then open it in the media viewer. Returns true if an asset was created.
- L97 _protected prototype_ `static bool ShowFrameRatePickerDialog(FFrameRate& OutFrameRate, const FFrameRate& InDefaultFrameRate = FFrameRate(24, 1));` — Shows a modal dialog to let the user pick a frame rate for an image sequence. @param OutFrameRate Receives the selected frame rate. @param InDefaultFrameRate The frame rate to pre-select in the dialog. @return True if the user confirmed.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MediaViewer` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MediaViewer` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewerDropTargetInternal.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaViewer` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::MediaViewer`)
- L27 _prototype_ `bool GetFrameNumberAndStem(const FString& InFilename, const FString& InExtension, int32& OutFrameNumber, FString& OutStem);` (scope `UE::MediaViewer::Private`) — Extracts a trailing frame number and the preceding stem from a filename, ignoring the extension. For example, "render.0042.exr" yields stem "render." and number 42. Leading zeros are skipped when counting significant digits to avoid spurious overflow rejection of zero-padded sequence filenames (e.g. "frame_00000042.png"). Out-params are only written on the success (true) path. @param InFilename      Filename without path (may include extension). @param InExtension     Extension string without the leading dot. @param OutFrameNumber  Receives the parsed frame number on success. @param OutStem         Receives the prefix before the digit run on success. @return True if a valid trailing integer was found and fits in int32.
- L34 _prototype_ `FFrameRate FindClosestCommonFrameRate(float InRate);` (scope `UE::MediaViewer::Private`) — Maps a raw float fps to the closest entry in FCommonFrameRates::GetAll(). Falls back to FFrameRate(24, 1) (the ImgMediaSource default) when the input is non-positive or no common rate is closer than the initial 24 fps guess.
- L46 _prototype_ `bool DetectImageSequence(const FString& InFilePath, int32& OutDroppedFrameNumber, int32& OutFirstFrameNumber);` (scope `UE::MediaViewer::Private`) — Returns true if the file is part of a numbered image sequence (strict: every sibling with the same extension must share the stem and have a trailing frame number, and at least one matching sibling must exist). Out-params are only set on success. @param InFilePath The full path to the file. @param OutDroppedFrameNumber If a sequence is detected, the frame number of the dropped file. @param OutFirstFrameNumber If a sequence is detected, the smallest frame number among matching siblings. @return True if the file is part of a sequence (the dropped file plus at least one sibling).

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewerLibrary.h` (Private)


#### class `UE::MediaViewer::Private::SMediaViewerLibrary`  
`class SMediaViewerLibrary : public SCompoundWidget, public IMediaViewerLibraryWidget`  
_L27-68_
- inherits: `SCompoundWidget,IMediaViewerLibraryWidget`
- desc: Implementation of @see IMediaViewerLibraryWidget.
- L32 _public function_ `SLATE_BEGIN_ARGS(SMediaViewerLibrary)`
- L36 _public prototype_ `SMediaViewerLibrary();`
- L40 _public prototype_ `void Construct(const FArguments& InArgs, const FArgs& InMediaViewerLibraryArgs, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L42 _public prototype_ `void OnLibraryChanged(TSharedRef<IMediaViewerLibrary> InLibrary, IMediaViewerLibrary::EChangeType InChangeType);`
- L45 _public prototype_ `virtual TSharedRef<SWidget> ToWidget() override;`
- L46 _public prototype_ `virtual TSharedRef<IMediaViewerLibrary> GetLibrary() const override;`
- L50 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L54 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;`
- L55 _protected member_ `TSharedPtr<IMediaViewerLibrary> Library;`
- L56 _protected member_ `FGroupFilter GroupFilter;`
- L57 _protected member_ `TArray<IMediaViewerLibrary::FGroupItem> Groups;`
- L58 _protected member_ `TSharedPtr<STreeView<IMediaViewerLibrary::FGroupItem>> TreeView;`
- L60 _protected prototype_ `void UpdateGroups();`
- L62 _protected prototype_ `TSharedRef<class ITableRow> OnGenerateItemRow(IMediaViewerLibrary::FGroupItem InEntry, const TSharedRef<STableViewBase>& InOwningTable);`
- L65 _protected prototype_ `void OnGetChildren(IMediaViewerLibrary::FGroupItem InParent, TArray<IMediaViewerLibrary::FGroupItem>& OutChildren);`
- L67 _protected prototype_ `void OnGroupExpanded(IMediaViewerLibrary::FGroupItem InGroup, bool bExpanded);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MediaViewer` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MediaViewer` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewerLibraryGroup.h` (Private)


#### class `UE::MediaViewer::Private::SMediaViewerLibraryGroup`  
`class SMediaViewerLibraryGroup : public STableRow<IMediaViewerLibrary::FGroupItem>`  
_L24-62_
- inherits: `STableRow<IMediaViewerLibrary::FGroupItem>`
- L26 _private typedef_ `using FSuperType = STableRow<IMediaViewerLibrary::FGroupItem>;`
- L28 _private function_ `SLATE_DECLARE_WIDGET(SMediaViewerLibraryGroup, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaViewerLibraryGroup)`
- L35 _public prototype_ `SMediaViewerLibraryGroup();`
- L37 _public prototype_ `virtual ~SMediaViewerLibraryGroup() override = default;`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwningTable, const TSharedRef<IMediaViewerLibrary>& InLibrary, const FGuid& InGroupId);`
- L43 _public prototype_ `virtual void OnDragEnter(const FGeometry& InMyGeometry, const FDragDropEvent& InEvent) override;`
- L44 _public prototype_ `virtual FReply OnDrop(const FGeometry& InMyGeometry, const FDragDropEvent& InEvent) override;`
- L48 _protected member_ `TWeakPtr<IMediaViewerLibrary> LibraryWeak;`
- L49 _protected member_ `FGuid GroupId;`
- L51 _protected prototype_ `FText GetGroupName() const;`
- L53 _protected prototype_ `FReply OnRemoveButtonClicked();`
- L55 _protected prototype_ `FReply OnRefreshButtonClicked();`
- L57 _protected prototype_ `bool CanAcceptLibraryItem(const IMediaViewerLibrary::FGroupItem& InDraggedGroupItem) const;`
- L58 _protected prototype_ `void OnLibraryItemDropped(const IMediaViewerLibrary::FGroupItem& InDroppedGroupItem) const;`
- L60 _protected prototype_ `bool CanAcceptAssets(TConstArrayView<FAssetData> InAssetData) const;`
- L61 _protected prototype_ `void OnAssetsDropped(TConstArrayView<FAssetData> InAssetData);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MediaViewer` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MediaViewer` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewerLibraryItem.h` (Private)


#### class `UE::MediaViewer::Private::SMediaViewerLibraryItem`  
`class SMediaViewerLibraryItem : public STableRow<IMediaViewerLibrary::FGroupItem>`  
_L28-85_
- inherits: `STableRow<IMediaViewerLibrary::FGroupItem>`
- L30 _private typedef_ `using FSuperType = STableRow<IMediaViewerLibrary::FGroupItem>;`
- L32 _private function_ `SLATE_DECLARE_WIDGET(SMediaViewerLibraryItem, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaViewerLibraryItem)`
- L39 _public prototype_ `SMediaViewerLibraryItem();`
- L41 _public prototype_ `virtual ~SMediaViewerLibraryItem() override = default;`
- L43 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwningTable, const TSharedRef<IMediaViewerLibrary>& InLibrary, const IMediaViewerLibrary::FGroupItem& InGroupItem, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L48 _public prototype_ `virtual void OnDragEnter(const FGeometry& InMyGeometry, const FDragDropEvent& InEvent) override;`
- L49 _public prototype_ `virtual FReply OnDrop(const FGeometry& InMyGeometry, const FDragDropEvent& InEvent) override;`
- L53 _protected member_ `TWeakPtr<IMediaViewerLibrary> LibraryWeak;`
- L54 _protected member_ `IMediaViewerLibrary::FGroupItem GroupItem;`
- L55 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;`
- L56 _protected member_ `TSharedPtr<FMediaViewerLibraryItem> Item;`
- L57 _protected member_ `TSharedPtr<FSlateBrush> ThumbnailBrush;`
- L59 _protected prototype_ `FLinearColor GetBorderColor() const;`
- L61 _protected prototype_ `FLinearColor GetFillColor() const;`
- L63 _protected prototype_ `bool IsActive(EMediaImageViewerPosition InPosition) const;`
- L65 _protected prototype_ `EVisibility GetHoveredOrActiveVisibility() const;`
- L67 _protected prototype_ `void SetImageViewer(EMediaImageViewerPosition InPosition);`
- L69 _protected prototype_ `void ClearImageViewer(EMediaImageViewerPosition InPosition);`
- L71 _protected prototype_ `ECheckBoxState IsActiveState(EMediaImageViewerPosition InPosition) const;`
- L72 _protected prototype_ `void OnUseButtonClicked(ECheckBoxState InCheckState, EMediaImageViewerPosition InPosition);`
- L74 _protected prototype_ `FReply OnRemoveButtonClicked();`
- L76 _protected prototype_ `FReply OnDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InPointerEvent);`
- L78 _protected prototype_ `bool CanAcceptLibraryItem(const IMediaViewerLibrary::FGroupItem& InDraggedGroupItem) const;`
- L79 _protected prototype_ `void OnLibraryItemDropped(const IMediaViewerLibrary::FGroupItem& InDroppedGroupItem) const;`
- L81 _protected prototype_ `bool CanAcceptAssets(TConstArrayView<FAssetData> InAssetData) const;`
- L82 _protected prototype_ `void OnAssetsDropped(TConstArrayView<FAssetData> InAssetData);`
- L84 _protected prototype_ `const FSlateBrush* GetThumbnail() const;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MediaViewer` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MediaViewer` (scope `UE`)
- L25 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewerLibraryPrivate.h` (Private)


#### class `UE::MediaViewer::Private::SMediaViewerLibraryPrivate`  
`class SMediaViewerLibraryPrivate : public SCompoundWidget`  
_L24-45_
- inherits: `SCompoundWidget`
- L26 _private function_ `SLATE_DECLARE_WIDGET(SMediaViewerLibraryPrivate, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaViewerLibraryPrivate)`
- L34 _public prototype_ `SMediaViewerLibraryPrivate();`
- L35 _public prototype_ `virtual ~SMediaViewerLibraryPrivate() = default;`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L39 _public prototype_ `TSharedRef<IMediaViewerLibrary> GetLibrary() const;`
- L41 _public prototype_ `void OnImageViewerOpened(const TSharedRef<FMediaImageViewer>& InImageViewer);`
- L44 _protected member_ `TSharedPtr<SMediaViewerLibrary> Library;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MediaViewer` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MediaViewer` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/SMediaViewerToolbar.h` (Private)


#### class `UE::MediaViewer::Private::SMediaViewerToolbar`  
`class SMediaViewerToolbar : public SViewportToolBar, public FNotifyHook`  
_L24-61_
- inherits: `SViewportToolBar,FNotifyHook`
- desc: Toolbar for the Media Viewer.
- L26 _private function_ `SLATE_DECLARE_WIDGET(SMediaViewerToolbar, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaViewerToolbar)`
- L33 _public prototype_ `SMediaViewerToolbar();`
- L35 _public prototype_ `virtual ~SMediaViewerToolbar() override = default;`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FMediaViewerDelegates>& InDelegates);`
- L40 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L44 _protected member_ `TSharedPtr<FMediaViewerDelegates> Delegates;`
- L45 _protected member_ `TSharedPtr<SWidget> ImageDetails[static_cast<int32>(EMediaImageViewerPosition::COUNT)];`
- L46 _protected member_ `TSharedPtr<IStructureDetailsView> MediaViewerSettingsView;`
- L47 _protected member_ `TSharedPtr<SWidget> MediaViewerSettingsWidget;`
- L49 _protected prototype_ `TSharedRef<SWidget> MakeSideToolbar(EMediaImageViewerPosition InPosition, FName InToolbarName);`
- L51 _protected prototype_ `TSharedRef<SWidget> MakeCenterToolbar();`
- L53 _protected prototype_ `TSharedRef<SWidget> GetBackgroundTextureSettingsWidget() const;`
- L55 _protected prototype_ `FText GetScaleMenuLabel(EMediaImageViewerPosition InPosition) const;`
- L56 _protected prototype_ `TSharedRef<SWidget> MakeScaleMenu(EMediaImageViewerPosition InPosition) const;`
- L58 _protected prototype_ `TSharedRef<SWidget> GetDetailsWidget(EMediaImageViewerPosition InPosition) const;`
- L60 _protected prototype_ `FReply OnSaveToLibraryClicked();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaViewer` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MediaViewer` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::MediaViewer`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Widgets/StrongSlateImageBrush.h` (Private)


#### struct `FStrongSlateImageBrush`  
`struct FStrongSlateImageBrush : public FSlateImageBrush, public FGCObject`  
_L11-25_
- inherits: `FSlateImageBrush,FGCObject`
- desc: Ignores the Margin. Just renders the image. Can tile the image instead of stretching.
- L13 _public prototype_ `FStrongSlateImageBrush(UObject* InResourceObject, const UE::Slate::FDeprecateVector2DParameter& InImageSize, const FSlateColor& InTint = FSlateColor(FLinearColor(1, 1, 1, 1)), ESlateBrushTileType::Type InTiling = ESlateBrushTileType::NoTile, ESlateBrushImageType::Type InImageType = ESlateBrushImageType::FullColor);`
- L19 _public prototype_ `virtual FString GetReferencerName() const override;`
- L20 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L24 _protected member_ `TObjectPtr<UObject> ResourceObjectPtr;`

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/IMediaViewerModule.h` (Public)


#### class `UE::MediaViewer::IMediaViewerModule`  
`class IMediaViewerModule : public IModuleInterface`  
_L30-91_
- inherits: `IModuleInterface`
- desc: Media Viewer - Display and compare media
- L33 _public function_ `static IMediaViewerModule& Get()`
- L42 _public prototype_ `virtual bool IsFactoryRegistered(FName InFactoryName) const = 0;`
- L43 _public prototype_ `virtual bool HasFactoryFor(const FAssetData& InAssetData) const = 0;`
- L44 _public prototype_ `virtual bool HasFactoryFor(UObject* InObject) const = 0;`
- L45 _public prototype_ `virtual void RegisterFactory(FName InFactoryName, const TSharedRef<IMediaImageViewerFactory>& InFactory) = 0;`
- L46 _public prototype_ `virtual void UnregisterFactory(FName InFactoryName) = 0;`
- L53 _public prototype_ `virtual bool OpenTab() = 0;` — Will open the tab if necessary. Will give the opened tab focus.
- L56 _public prototype_ `virtual bool OpenTab(const FMediaViewerArgs& InMediaViewerArgs) = 0;` — If the settings differ from the currently opened tab's settings, it will regenerate the entire display.
- L59 _public prototype_ `virtual TSharedRef<IMediaViewerLibrary> GetLibrary() const = 0;` — Returns the Library, which is common between all tabs.
- L61 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const = 0;`
- L62 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const = 0;`
- L63 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(FName InItemType, const FMediaViewerLibraryItem& InSavedItem) const = 0;`
- L65 _public prototype_ `virtual bool HasImage(EMediaImageViewerPosition InPosition) const = 0;`
- L66 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> GetImage(EMediaImageViewerPosition InPosition) const = 0;`
- L72 _public prototype_ `virtual bool SetImage(EMediaImageViewerPosition InPosition, const FAssetData& InAssetData) = 0;` — If the widget is open, these will control the displayed images programmatically. Returns true if the widget is open and a generator is found.
- L73 _public prototype_ `virtual bool SetImage(EMediaImageViewerPosition InPosition, UObject* InObject) = 0;`
- L74 _public prototype_ `virtual bool SetImage(EMediaImageViewerPosition InPosition, const TSharedRef<FMediaImageViewer> InImageViewer) = 0;`
- L75 _public prototype_ `virtual bool ClearImage(EMediaImageViewerPosition InPosition) = 0;`
- L82 _public prototype_ `virtual TSharedRef<SMediaViewerTab> CreateMediaViewer(const FMediaViewerArgs& InMediaViewerArgs) = 0;` — Create a raw copy of the reference viewer.
- L85 _public prototype_ `virtual TSharedRef<IMediaViewerLibraryWidget> CreateLibrary(const IMediaViewerLibraryWidget::FArgs& InArgs) = 0;` — Creates a Library widget.
- L90 _public prototype_ `virtual TSharedPtr<SDockTab> OpenStandaloneTab() = 0;` — Methods for creating new standalone tabs

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MediaViewer` (scope `UE`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/ImageViewer/IMediaImageViewerFactory.h` (Public)


#### struct `UE::MediaViewer::IMediaImageViewerFactory`  
`struct IMediaImageViewerFactory`  
_L18-41_
- L21 _public member_ `int32 Priority = 5000;` — Priorities should be in the range of 1000 (first) to 10000 (last).
- L24 _public prototype_ `virtual bool SupportsAsset(const FAssetData& InAssetData) const = 0;` — Whether this factory supports this asset type.
- L26 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(const FAssetData& InAssetData) const = 0;` — Creates an image viewer based on this asset.
- L28 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FAssetData& InAssetData) const = 0;` — Creates a library item based on this asset.
- L31 _public prototype_ `virtual bool SupportsObject(TNotNull<UObject*> InObject) const = 0;` — Whether this factory supports this object.
- L33 _public prototype_ `virtual TSharedPtr<FMediaImageViewer> CreateImageViewer(TNotNull<UObject*> InObject) const = 0;` — Create an image viewer based on this object.
- L35 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(TNotNull<UObject*> InObject) const = 0;` — Create a library item based on this object.
- L38 _public prototype_ `virtual bool SupportsItemType(FName InItemType) const = 0;` — Whether this item type is supported (E.g. "Texture2D" or "Color").
- L40 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem(const FMediaViewerLibraryItem& InSavedItem) const = 0;` — Recreate this library item as the correct subclass.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MediaViewer` (scope `UE`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/ImageViewer/MediaImageViewer.h` (Public)


#### struct `FMediaImageViewerPanelSettings`  
`struct FMediaImageViewerPanelSettings`  
_L52-70_
- reflection: `USTRUCT()`
- desc: Settings related to drawing panel contents other than the image itself.
- L62 _public member_ `TOptional<FLinearColor> BackgroundColor;` — `UPROPERTY(EditAnywhere, Config, Category = "Panel")` — Color for the background within the image rectangle. If this is different to the clear color, it shows where the image is even if nothing is drawn.
- L69 _public member_ `TSoftObjectPtr<UTexture> BackgroundTexture;` — `UPROPERTY(EditAnywhere, Config, Category = "Panel")` — If set, this is drawn over the top of the background color. Example usage: checkered background.

#### enum `EMediaImageMirrorPlane`  
`enum class EMediaImageMirrorPlane : uint8`  
_L73-83_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L75 _public enumerator_ `None = 0 UMETA(Hidden)`
- L76 _public enumerator_ `Horizontal = 1 << 0`
- L77 _public enumerator_ `Vertical = 1 << 1`
- L78 _public enumerator_ `Depth = 1 << 2 UMETA(ToolTip = "3D Only")` — Front to back flipping
- L80 _public enumerator_ `MAX = Depth UMETA(Hidden)`
- L81 _public enumerator_ `TwoDim = Horizontal | Vertical UMETA(Hidden)`
- L82 _public enumerator_ `ThreeDim = TwoDim | Depth UMETA(Hidden)`

#### struct `FMediaImagePaintSettings`  
`struct FMediaImagePaintSettings`  
_L87-179_
- reflection: `USTRUCT()`
- L98 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Config, Category = "Media")` — Offset from the origin (center) of the viewer. X: Horizontal (L->R) Y: Vertical (T->B) Z: Depth (F->B)
- L102 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Config, Category = "Media")` — Rotation about the offset, for 3d objects.
- L109 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Config, Category = "Media")` — The scale of the image. A scale of 2 will mean the image is twice as big.
- L115 _public member_ `uint8 MirrorPlanes = 0;` — `UPROPERTY(EditAnywhere, Config, Category = "Media", meta = (Bitmask, BitmaskEnum = "/Script/MediaViewer.EMediaImageMirrorPlane"))` — Image mirroring along the center axes
- L123 _public member_ `bool bAutoFilteringEnabled = true;` — `UPROPERTY(EditAnywhere, Config, Category = "Media")` — When true, bilinear filtering is automatically disabled (nearest-neighbor sampling) once the zoom level reaches AutoFilteringThreshold. This allows individual pixels to be seen clearly when zoomed in far enough.
- L131 _public member_ `float AutoFilteringThreshold = 4.0f;` — `UPROPERTY(EditAnywhere, Config, Category = "Media", meta = (EditCondition = "bAutoFilteringEnabled", UIMin = 1.0, ClampMin = 1.0, UIMax = 8.0, ClampMax = 8.0, Units = "x"))` — The zoom scale at which filtering is automatically disabled when bAutoFilteringEnabled is true. A value of 2.0 means filtering is disabled at 200% zoom and above.
- L138 _public member_ `bool bPixelGridEnabled = true;` — `UPROPERTY(EditAnywhere, Config, Category = "Media")` — When true, a pixel grid overlay is drawn when zoomed in with nearest-neighbor filtering active, making individual pixel boundaries clearly visible.
- L145 _public member_ `float PixelGridThreshold = 9.f;` — `UPROPERTY(EditAnywhere, Config, Category = "Media", meta = (EditCondition = "bPixelGridEnabled", UIMin = 8.0, ClampMin = 1.0, UIMax = 128.0, ClampMax = 128.0))` — Minimum screen-pixel size a source pixel must reach before the grid is drawn.
- L149 _public member_ `bool bEnableMipOverride = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Media", meta = (InlineEditConditionToggle))` — Whether to enable the MipOverride
- L155 _public member_ `uint8 MipOverride = 0;` — `UPROPERTY(EditAnywhere, Config, Category = "Media", meta = (EditCondition = "bEnableMipOverride", UIMin = 0, ClampMin = 0, UIMax = 10, ClampMax = 10))` — The requested mip level. If the mip isn't available, the highest available value will be used.
- L161 _public member_ `FLinearColor Tint = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Config, Category = "Media")` — Color to tint the image brush with.
- L164 _public function_ `TOptional<uint8> GetMipOverride() const` — Returns a Mip value, if enabled.
- L175 _public function_ `uint8 GetMipLevel() const` — Always returns a Mip value, even if unset, will default to 0.

#### struct `UE::MediaViewer::FMediaImageViewerInfo`  
`struct FMediaImageViewerInfo`  
_L188-198_
- desc: Information about the image viewer's image.
- L191 _public member_ `FGuid Id;` — Unique Id for the *source*.
- L193 _public member_ `FIntPoint Size;` — Size of the image to draw.
- L195 _public member_ `int32 MipCount;` — The number of mips the image has.
- L197 _public member_ `FText DisplayName;` — The name of the image.

#### struct `UE::MediaViewer::FMediaImageSlatePaintParams`  
`struct FMediaImageSlatePaintParams`  
_L203-231_
- desc: Parameters used by the image viewers to paint their image.
- L206 _public member_ `const FPaintArgs& Args;` — Slate paint args.
- L208 _public member_ `const FGeometry& AllottedGeometry;` — Slate geometry for the panel.
- L210 _public member_ `const FSlateRect& MyCullingRect;` — Culling rect for the panel.
- L212 _public member_ `const FWidgetStyle& WidgetStyle;` — Slate for the panel.
- L214 _public member_ `const bool bParentEnabled;` — Whether the parent painted widget was enabled.
- L216 _public member_ `const FFloatRange& UVRange;` — UV Range to draw the image on, either horizontally (L->R) and vertically (T->B).
- L218 _public member_ `const float DPIScale;` — Scale of the panel.
- L220 _public member_ `const EOrientation Orientation;` — Orientation of the panel split.
- L222 _public member_ `const FVector2D ViewerSize;` — Size of the panel in the window.
- L224 _public member_ `const FVector2D ViewerPosition;` — Position of the panel in the window.
- L226 _public member_ `float ImageOpacity;` — Opacity to draw the image with. 0-1.
- L228 _public member_ `int32 LayerId;` — Layer Id to draw the image onto. Increment it if you draw anything.
- L230 _public member_ `FSlateWindowElementList& DrawElements;` — List of elements to draw into the layer.

#### struct `UE::MediaViewer::FMediaImageSlatePaintGeometry`  
`struct FMediaImageSlatePaintGeometry`  
_L234-242_
- desc: Geometry of the image within the panel.
- L237 _public member_ `const FVector2D Position;` — Position of the image within the painted area.
- L239 _public member_ `const FVector2D Size;` — Size of the image within the painted area.
- L241 _public member_ `const FPaintGeometry Geometry;` — Slate geometry of the image within the painted area.

#### struct `UE::MediaViewer::FMediaImageCanvasPaintParams`  
`struct FMediaImageCanvasPaintParams`  
_L247-257_
- desc: Parameters used by the image viewers to paint their image.
- L250 _public member_ `UCanvas* Canvas;` — The canvas to draw on.
- L252 _public member_ `const FFloatRange& UVRange;` — UV Range to draw the image on, either horizontally (L->R) and vertically (T->B).
- L254 _public member_ `const EOrientation Orientation;` — Orientation of the panel split.
- L256 _public member_ `float ImageOpacity;` — Opacity to draw the image with. 0-1.

#### struct `UE::MediaViewer::FMediaImageCanvasPaintGeometry`  
`struct FMediaImageCanvasPaintGeometry`  
_L260-266_
- desc: Geometry of the image within the panel.
- L263 _public member_ `const FVector2D Position;` — Position of the image within the painted area.
- L265 _public member_ `const FVector2D Size;` — Size of the image within the painted area.

#### class `UE::MediaViewer::FMediaImageViewer`  
`class FMediaImageViewer : public FNotifyHook, public FGCObject, public TSharedFromThis<FMediaImageViewer>`  
_L271-449_
- inherits: `FNotifyHook,FGCObject,TSharedFromThis<FMediaImageViewer>`
- desc: Image resource for the AB Image Viewer representing a source that can be displayed as a 2d image.
- L282 _public prototype_ `static FText GetObjectDisplayName(const UObject* InObject);` — Given an object, tries to fetch a nice display name for it. If it's contained within an actor, it will return the actor's label / name. Otherwise it returns the object's name.
- L284 _public prototype_ `FMediaImageViewer(const FMediaImageViewerInfo& InImageInfo);`
- L286 _public prototype_ `virtual ~FMediaImageViewer() override = default;`
- L288 _public function_ `const FMediaImageViewerInfo& GetInfo() const`
- L290 _public function_ `virtual bool IsValid() const`
- L292 _public function_ `virtual bool SupportsMip() const`
- L299 _public prototype_ `void UpdateId(const FGuid& InId);` — Called, for instance, when an image is dropped into the viewer and it creates an image viewer, but the image already exists in the library. This image viewer should have its id updated to reflect the id already in the library.
- L301 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> CreateLibraryItem() const = 0;`
- L303 _public function_ `const FMediaImageViewerPanelSettings& GetPanelSettings() const`
- L304 _public function_ `FMediaImageViewerPanelSettings& GetPanelSettings()`
- L306 _public function_ `const FMediaImagePaintSettings& GetPaintSettings() const`
- L307 _public function_ `FMediaImagePaintSettings& GetPaintSettings()`
- L309 _public prototype_ `void InitBackgroundTexture();`
- L311 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetPixelColor(const FIntPoint& InPixelCoords, int32 InMipLevel) const = 0;`
- L314 _public prototype_ `void Paint(FMediaImageSlatePaintParams& InPaintParams);` — Paint the panel and image on to the viewer.
- L317 _public prototype_ `void Paint(const FMediaImageCanvasPaintParams& InPaintParams);` — Paint the panel and image to a canvas.
- L323 _public function_ `virtual void ExtendToolbar(const TSharedRef<FExtender>& InOutToolbarExtender)` — Extend the tool bar (top). @see MediaViewer.h @param InOutToolbarExtender The extender to populate.
- L329 _public function_ `virtual void ExtendStatusBar(FMediaImageStatusBarExtender& InOutStatusBarExtender)` — Extend the status bar (top over overlay). @see MediaViewer.h @param InOutStatusBarExtender - The extender to populate.
- L338 _public function_ `virtual TSharedPtr<SWidget> GetOverlayWidget(EMediaImageViewerPosition InPosition, const TSharedPtr<FMediaViewerDelegates>& InDelegates)` — Returns a widget to place on the overlay. If the widget is on the A position, it should be left aligned. If the widget is in the B position, it should be right aligned. The above alignment will be used for the widget's slot. If no overlay is required, return nullptr.
- L347 _public function_ `virtual bool OnTrackingStarted(const FInputEventState& InInputState, const FIntPoint& InMousePosition)` — Responds to tracking started in this viewer's viewport. @param   InputState - The state of the input when tracking started. @param   MousePosition - The position of the mouse when tracking started. @returns True if custom tracking was started.
- L354 _public function_ `virtual void OnTrackingStopped(const FIntPoint& InMousePosition)` — Responds to tracking stopped in this viewer's viewport. @param   MousePosition - The position of the mouse when tracking started.
- L362 _public function_ `virtual void OnMouseMove(const FVector2D& InMousePosition)` — Responds to mouse movement in this viewer's viewport. @param   MousePosition - The position of the mouse when tracking stoppped. @returns True if custom tracking was stopped.
- L371 _public function_ `virtual bool OnKeyPressed(const FInputKeyEventArgs& InEventArgs)` — Responds to key input in this image's viewport. Note: this is after the ImageWidgets internal event consumption. @param   InputState - The state of the input when tracking started. @returns True if the input was consumed.
- L376 _public function_ `virtual TSharedPtr<FStructOnScope> GetCustomSettingsOnScope() const` — Returns a custom struct on scope to display media-specific settings to the user.
- L379 _public prototype_ `bool IsMirrored(EMediaImageMirrorPlane InPlane) const;` — Returns true if the image is mirrored on the given axis.
- L382 _public prototype_ `void SetMirrored(EMediaImageMirrorPlane InPlane, bool bInSet);` — Use to set mirror flag, don't set directly!
- L385 _public function_ `virtual void OnMirrored()` — Triggered when a shape is mirrored.
- L388 _public prototype_ `FVector2D GetViewerCenter(const FVector2D& InViewerSize) const;` — Returns the center of the viewer, not necessarily the center of the splitter it's contained within.
- L391 _public prototype_ `FVector2D GetPaintOffsetForViewerCenter(const FVector2D& InViewerSize) const;` — Returns the location of the top-left corner of the image for it to be painted in the centre of the viewer.
- L394 _public prototype_ `FVector2D GetPaintOffset(const FVector2D& InViewerSize, const FVector2D& InViewerPosition) const;` — Applies paint settings to the default center position.
- L397 _public prototype_ `FVector2D GetPaintSize() const;` — Returns the size of the image, including things like scale.
- L400 _public function_ `virtual bool OnOwnerCleanup(UObject* InObject)` — Called when a potential outer has been removed. Returns true if this is no longer valid.
- L406 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L410 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L414 _protected member_ `static const FSlateColorBrush BackgroundColorBrush;`
- L416 _protected member_ `FMediaImageViewerInfo ImageInfo;`
- L417 _protected member_ `FMediaImageViewerPanelSettings PanelSettings;`
- L418 _protected member_ `FMediaImagePaintSettings PaintSettings;`
- L419 _protected member_ `FSlateImageBrush BackgroundImageBrush;`
- L420 _protected member_ `TSharedPtr<FSlateBrush> Brush;`
- L421 _protected member_ `ESlateDrawEffect DrawEffects = ESlateDrawEffect::NoPixelSnapping;`
- L422 _protected member_ `TStrongObjectPtr<UMaterialInstanceDynamic> MipAdjustedMaterial;`
- L423 _protected member_ `TStrongObjectPtr<UTextureRenderTarget2D> MipAdjustedRenderTarget;`
- L424 _protected member_ `TSharedPtr<FSlateBrush> MipAdjustedBrush;`
- L425 _protected member_ `bool bInvalidatedMipTexture = true;`
- L434 _protected prototype_ `bool UpdateMipBrush();` — Refreshes MipAdjustedRenderTarget / MipAdjustedBrush for the current mip level. Returns true if the brush is drawable this frame. False is "skip this frame" - it covers transient cases like the mip material's shaders still compiling, where bInvalidatedMipTexture stays true so the next paint retries. Callers should fall back to plain Brush, not treat false as fatal.
- L436 _protected prototype_ `FSlateClippingZone CreateSlateClippingZone(const FSlateRect& InCullingRect, float InDPIScale, const FVector2D& InViewerPosition, EOrientation InOrientation, const FFloatRange& InUVRange) const;`
- L439 _protected prototype_ `virtual void PaintPanel(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry);`
- L441 _protected prototype_ `virtual void PaintImage(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry);`
- L444 _protected prototype_ `virtual void PaintPixelGrid(FMediaImageSlatePaintParams& InPaintParams, const FMediaImageSlatePaintGeometry& InPaintGeometry);` — Draws a pixel boundary grid over the image when nearest-neighbor filtering is active.
- L446 _protected prototype_ `virtual void PaintPanel(const FMediaImageCanvasPaintParams& InPaintParams, const FMediaImageCanvasPaintGeometry& InPaintGeometry);`
- L448 _protected prototype_ `virtual void PaintImage(const FMediaImageCanvasPaintParams& InPaintParams, const FMediaImageCanvasPaintGeometry& InPaintGeometry);`

#### struct `UE::MediaViewer::FMediaImageViewer::FPrivateToken`  
`struct FPrivateToken`  
_L274-274_

#### Free symbols / members of external scopes

- L181 _namespace_ `namespace UE`
- L181 _namespace_ `namespace MediaViewer` (scope `UE`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Library/IMediaViewerLibrary.h` (Public)


#### class `UE::MediaViewer::IMediaViewerLibrary`  
`class IMediaViewerLibrary`  
_L24-208_
- desc: Groups are identified by a single GUID. Items are identified by a single GUID. Library Items associate an item's GUID with a position in the Library. They are uniquely identified by an item GUID and a group GUID.
- L38 _public function_ `friend int32 GetTypeHash(const IMediaViewerLibrary::FGroupItem& InGroupItem)`
- L57 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChanged, TSharedRef<IMediaViewerLibrary> , EChangeType) virtual const FGuid& GetDefaultGroupId() const = 0;`
- L67 _public prototype_ `virtual const FGuid& GetHistoryGroupId() const = 0;` — @returns The id of the history group.
- L72 _public prototype_ `virtual const FGuid& GetSnapshotsGroupId() const = 0;` — @returns The id of the snapshot group.
- L77 _public prototype_ `virtual const TArray<TSharedRef<const FMediaViewerLibraryGroup>>& GetGroups() const = 0;` — Return the list of groups.
- L84 _public prototype_ `virtual bool AddGroup(const TSharedRef<FMediaViewerLibraryGroup>& InNewGroup) = 0;` — Add a custom group to the Library. @param InNewGroup Group to be added. Id must be unique. @returns False if a group with the given name already exits, otherwise true.
- L91 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryGroup> GetGroup(const FGuid& InGroupId) const = 0;` — Return the group with the given id. Do not change guid or items manually. @param InGroupId The unique if of the group @returns An nullptr if the given id is invalid, otherwise the id of the group at that position.
- L97 _public prototype_ `virtual int32 EmptyGroup(const FGuid& InGroupId) = 0;` — Removes all items from a group. @returns The number of items removed.
- L102 _public prototype_ `virtual void RemoveInvalidGroupItems(const FGuid& InGroup) = 0;` — Scans the group and removes invalid entries.
- L107 _public prototype_ `virtual bool CanRemoveGroup(const FGuid& InGroupIdToRemove) const = 0;` — Returns true if the group with this id can be removed.
- L114 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryGroup> RemoveGroup(const FGuid& InGroupIdToRemove) = 0;` — Remove an existing group and any items in the group. @param InGroupIdToRemove Unique identifier of the group. Must not be the default group name. @returns The group that was removed, including all its items.
- L119 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> FindItemByValue(FName InItemType, const FString& InStringValue) const = 0;` — Returns the first item that matches the item type and string value.
- L126 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> GetItem(const FGuid& InItemId) const = 0;` — Retrieve the existing item for a given unique identifier. Do not change guid or group manually. @param InItemId The unique identifier of the item. @return The pointer to the item or an invalid pointer if no item with the given unique identifier exists.
- L133 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryGroup> GetItemGroup(const FGuid& InItemId) const = 0;` — Finds the first group containing the given Item Id. @param InItemId The unique identifier of the item. @return The group containing the item or null.
- L139 _public prototype_ `virtual bool AddItem(const TSharedRef<FMediaViewerLibraryItem>& InNewItem) = 0;` — Adds an item to the Library without place it in a group @param InNewItem Data for the item that is being added.
- L148 _public prototype_ `virtual bool AddItemToGroup(const TSharedRef<FMediaViewerLibraryItem>& InNewItem, TOptional<FGuid> InTargetGroupId = {}, int32 InIndex = INDEX_NONE) = 0;` — Add an item to a group. @param InNewItem Data for the item that is being added. @param InTargetGroupId Id of the group. Default group is used if the id is empty. @param InIndex Index in the array of items in the group. @returns True if the item was added successfully. Will fail if an invalid group id is supplied or the item already exists.
- L157 _public prototype_ `virtual bool AddItemBelowItem(const TSharedRef<FMediaViewerLibraryItem>& InNewItem, const FGroupItem& InTargetItem) = 0;` — Add an item below another item. @param InNewItem New item that is being added. @param InTargetItem Group/Item to add below. @returns True if the item was added successfully. Will fail if an invalid group id is supplied or the item already exists.
- L166 _public prototype_ `virtual bool MoveItemToGroup(const FGroupItem& InItemToMove, const FGuid& InTargetGroupId, int32 InIndex = INDEX_NONE) = 0;` — Move an already existing to another group, adding it to the end of the group. @param InItemToMove The existing group/item that should be moved. @param InTargetGroupId Unique identifier of the group it should be moved into. @param InIndex Index in the array of items in the group. @returns False if the the item or group don't exist, or the item is already in that group.
- L174 _public prototype_ `virtual bool MoveItemWithinGroup(const FGroupItem& InItemToMove, int32 InIndex) = 0;` — Move an already existing to another place inside its group. @param InItemToMove The existing group/item that should be moved. @param InIndex Index in the array of items in the group. @returns False if the the item doesn't exist, or the item is already at that index.
- L182 _public prototype_ `virtual bool MoveItemBelowItem(const FGroupItem& InItemToMove, const FGroupItem& InTargetItem) = 0;` — Move an already existing item below another, potentially changing its group. @param InItemToMove The existing group/item that should be moved. @param InTargetItem The group/item below which the item should be moved. @returns False if the either item doesn't exist. Otherwise true.
- L187 _public prototype_ `virtual bool CanRemoveItemFromGroup(const FGroupItem& InItemToRemove) const = 0;` — Returns true if this item can be removed from the group.
- L192 _public prototype_ `virtual bool RemoveItemFromGroup(const FGroupItem& InItemToRemove) = 0;` — Return true if the item was removed from the group.
- L197 _public prototype_ `virtual bool CanRemoveItem(const FGuid& InItemIdToRemove) const = 0;` — Returns true if this item can be removed from every group.
- L202 _public prototype_ `virtual TSharedPtr<FMediaViewerLibraryItem> RemoveItem(const FGuid& InItemIdToRemove) = 0;` — Return true if the item was removed from every group.
- L207 _public prototype_ `virtual FOnChanged::RegistrationType& GetOnChanged() = 0;` — When a changed is triggered, this event is triggered.

#### struct `UE::MediaViewer::IMediaViewerLibrary::FGroupItem`  
`struct FGroupItem`  
_L27-45_
- L29 _public member_ `FGuid GroupId;`
- L30 _public member_ `FGuid ItemId;`
- L32 _public function_ `bool operator==(const FGroupItem& InOther) const`

#### enum `UE::MediaViewer::IMediaViewerLibrary::EChangeType`  
`enum class EChangeType : uint8`  
_L47-55_
- L49 _public enumerator_ `GroupAdded`
- L50 _public enumerator_ `GroupRemoved`
- L51 _public enumerator_ `GroupItemsChanged`
- L52 _public enumerator_ `ItemAdded`
- L53 _public enumerator_ `ItemRemoved`
- L54 _public enumerator_ `ItemGroupChanged`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MediaViewer` (scope `UE`)
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChanged, TSharedRef<IMediaViewerLibrary> , EChangeType) virtual const FGuid& GetDefaultGroupId() const = 0;`

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Library/MediaViewerLibraryDynamicGroup.h` (Public)


#### struct `UE::MediaViewer::FMediaViewerLibraryDynamicGroup`  
`struct FMediaViewerLibraryDynamicGroup : public FMediaViewerLibraryGroup`  
_L18-40_
- inherits: `FMediaViewerLibraryGroup`
- desc: Contains all data for a Library group which has dynamic elements based on an external source.
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FMediaViewerLibraryItem>>, FGenerateItems) FMediaViewerLibraryDynamicGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary, const FText& InName, const FText& InToolTip, FGenerateItems InItemGenerator);`
- L25 _public prototype_ `FMediaViewerLibraryDynamicGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary, const FGuid& InId, const FText& InName, const FText& InToolTip, FGenerateItems InItemGenerator);`
- L28 _public prototype_ `virtual ~FMediaViewerLibraryDynamicGroup() override = default;`
- L30 _public prototype_ `virtual void UpdateItems();`
- L32 _public prototype_ `FSimpleMulticastDelegate::RegistrationType& GetOnItemsUpdated();`
- L35 _protected member_ `TWeakPtr<IMediaViewerLibrary> LibraryWeak;`
- L36 _protected member_ `FGenerateItems GenerateItemsDelegate;`
- L37 _protected member_ `FSimpleMulticastDelegate OnItemsUpdated;`
- L39 _protected prototype_ `TOptional<TArray<FGuid>> GetUpdatedIs(const TArray<FGuid>& InCurrentIds);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MediaViewer` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<TSharedRef<FMediaViewerLibraryItem>>, FGenerateItems) FMediaViewerLibraryDynamicGroup(const TSharedRef<IMediaViewerLibrary>& InLibrary, const FText& InName, const FText& InToolTip, FGenerateItems InItemGenerator);`

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Library/MediaViewerLibraryEntry.h` (Public)


#### enum `UE::MediaViewer::EMediaViewerLibraryEntryType`  
`enum class EMediaViewerLibraryEntryType`  
_L14-19_
- L16 _public enumerator_ `Invalid`
- L17 _public enumerator_ `Group`
- L18 _public enumerator_ `Item`

#### struct `FMediaViewerLibraryEntry`  
`struct FMediaViewerLibraryEntry`  
_L27-61_
- reflection: `USTRUCT()`
- desc: Contains all data for a Library group
- L33 _public member_ `FText Name;` — `UPROPERTY()` — Name of this entry.
- L37 _public member_ `FText ToolTip;` — `UPROPERTY()` — Tooltip that is shown when hovering over any part of the item's widget in the Library.
- L39 _public prototype_ `FMediaViewerLibraryEntry();`
- L40 _public prototype_ `FMediaViewerLibraryEntry(const FText& InName, const FText& InToolTip);`
- L41 _public prototype_ `FMediaViewerLibraryEntry(const FGuid& InId, const FText& InName, const FText& InToolTip);`
- L43 _public prototype_ `virtual ~FMediaViewerLibraryEntry() = default;`
- L45 _public prototype_ `const FGuid& GetId() const;`
- L47 _public prototype_ `void InvalidateId();`
- L49 _public function_ `virtual UE::MediaViewer::EMediaViewerLibraryEntryType GetEntryType() const`
- L51 _public function_ `bool operator==(const FMediaViewerLibraryEntry& InOther) const`
- L60 _protected member_ `FGuid Id;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — Unique id for this entry.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MediaViewer` (scope `UE`)
- L63 _function_ `inline int32 GetTypeHash(const FMediaViewerLibraryEntry& InEntry)`

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Library/MediaViewerLibraryGroup.h` (Public)


#### struct `FMediaViewerLibraryGroup`  
`struct FMediaViewerLibraryGroup : public FMediaViewerLibraryEntry`  
_L20-68_
- reflection: `USTRUCT()`
- inherits: `FMediaViewerLibraryEntry`
- desc: Contains all data for a Library group
- L30 _public prototype_ `FMediaViewerLibraryGroup();`
- L31 _public prototype_ `FMediaViewerLibraryGroup(const FText& InName, const FText& InToolTip, bool bDynamic);`
- L32 _public prototype_ `FMediaViewerLibraryGroup(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bDynamic);`
- L33 _public prototype_ `FMediaViewerLibraryGroup(FPrivateToken&& InPrivateToken, const FMediaViewerLibraryGroup& InSavedGroup);`
- L35 _public prototype_ `virtual ~FMediaViewerLibraryGroup() override = default;`
- L37 _public prototype_ `const TArray<FGuid>& GetItems() const;`
- L40 _public prototype_ `int32 AddItem(const FGuid& InItemUd, int32 InIndex = INDEX_NONE);` — Returns the index the item was added to in the list.
- L42 _public prototype_ `int32 FindItemIndex(const FGuid& InItemId) const;`
- L44 _public prototype_ `bool ContainsItem(const FGuid& InItemId) const;`
- L46 _public prototype_ `bool RemoveItem(const FGuid& InItemId);`
- L48 _public prototype_ `bool RemoveItemAt(int32 InIndex);`
- L51 _public prototype_ `int32 Empty();` — Returns the number of elements removed.
- L57 _public prototype_ `bool IsDynamic() const;` — If true the group's contents are generated dynamically and not saved. Its contents can be saved to the history group or copied to other groups.
- L60 _public function_ `virtual UE::MediaViewer::EMediaViewerLibraryEntryType GetEntryType() const`
- L64 _protected member_ `bool bDynamic;`
- L67 _protected member_ `TArray<FGuid> Items;` — `UPROPERTY()`

#### struct `FMediaViewerLibraryGroup::FPrivateToken`  
`struct FPrivateToken`  
_L25-25_

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Library/MediaViewerLibraryItem.h` (Public)


#### struct `FMediaViewerLibraryItem`  
`struct FMediaViewerLibraryItem : public FMediaViewerLibraryEntry`  
_L30-90_
- reflection: `USTRUCT()`
- inherits: `FMediaViewerLibraryEntry`
- desc: Contains all data for a Library item.
- L39 _public function_ `template<class InObjectType> static InObjectType* LoadAssetFromString(const FString& InString)`
- L49 _public prototype_ `FMediaViewerLibraryItem();`
- L51 _public prototype_ `FMediaViewerLibraryItem(const FText& InName, const FText& InToolTip, bool bInTransient, const FString& InStringValue = TEXT(""));`
- L54 _public prototype_ `FMediaViewerLibraryItem(const FGuid& InId, const FText& InName, const FText& InToolTip, bool bInTransient, const FString& InStringValue = TEXT(""));`
- L57 _public prototype_ `virtual ~FMediaViewerLibraryItem() override = default;`
- L59 _public prototype_ `virtual FName GetItemType() const;`
- L61 _public prototype_ `virtual FText GetItemTypeDisplayName() const;`
- L63 _public prototype_ `virtual FSlateColor GetItemTypeColor() const;`
- L65 _public prototype_ `bool IsTransient() const;`
- L67 _public function_ `virtual TSharedPtr<FSlateBrush> CreateThumbnail()`
- L69 _public function_ `virtual TSharedPtr<UE::MediaViewer::FMediaImageViewer> CreateImageViewer() const`
- L71 _public function_ `virtual TSharedPtr<FMediaViewerLibraryItem> Clone() const`
- L73 _public prototype_ `const FString& GetStringValue() const;`
- L75 _public function_ `virtual TOptional<FAssetData> AsAsset() const`
- L78 _public function_ `virtual UE::MediaViewer::EMediaViewerLibraryEntryType GetEntryType() const override`
- L82 _protected prototype_ `static FSlateColor GetClassColor(UClass* InClass);`
- L85 _protected member_ `bool bTransient;` — If all this entry and all its children are transient.
- L89 _protected member_ `FString StringValue;` — `UPROPERTY()` — Used to serialize the object.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MediaViewer` (scope `UE`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/MediaViewer.h` (Public)


#### enum `UE::MediaViewer::EMediaImageViewerPosition`  
`enum class EMediaImageViewerPosition : uint8`  
_L28-33_
- L30 _public enumerator_ `First = 0`
- L31 _public enumerator_ `Second = 1`
- L32 _public enumerator_ `COUNT = 2`

#### struct `UE::MediaViewer::FMediaViewerArgs`  
`struct FMediaViewerArgs`  
_L35-49_
- L37 _public member_ `bool bShowSidebar = true;`
- L38 _public member_ `bool bShowToolbar = true;`
- L39 _public member_ `bool bShowImageViewerStatusBar = true;`
- L40 _public member_ `bool bAllowABComparison = true;`
- L42 _public function_ `bool operator==(const FMediaViewerArgs& InOther) const`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaViewer, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaViewer, Log, All);`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MediaViewer` (scope `UE`)
- L14 _namespace_ `namespace ToolbarSections` (scope `UE::MediaViewer`)
- L16 _variable_ `const FLazyName ToolbarLeft = TEXT("Too` (scope `UE::MediaViewer::ToolbarSections`)
- L17 _variable_ `const FLazyName ToolbarCenter = TEXT("Too` (scope `UE::MediaViewer::ToolbarSections`)
- L18 _variable_ `const FLazyName ToolbarRight = TEXT("Too` (scope `UE::MediaViewer::ToolbarSections`)
- L21 _namespace_ `namespace StatusBarSections` (scope `UE::MediaViewer`)
- L23 _variable_ `const FLazyName StatusBarLeft = TEXT("Sta` (scope `UE::MediaViewer::StatusBarSections`)
- L24 _variable_ `const FLazyName StatusBarCenter = TEXT("Sta` (scope `UE::MediaViewer::StatusBarSections`)
- L25 _variable_ `const FLazyName StatusBarRight = TEXT("Sta` (scope `UE::MediaViewer::StatusBarSections`)

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/MediaViewerDelegates.h` (Public)


#### struct `UE::MediaViewer::FMediaImageViewerEventParams`  
`struct FMediaImageViewerEventParams`  
_L25-29_
- L27 _public member_ `TSharedPtr<FMediaImageViewer> FromViewer;`
- L28 _public member_ `FName EventName;`

#### struct `UE::MediaViewer::FMediaViewerDelegates`  
`struct FMediaViewerDelegates`  
_L31-169_
- L33 _public prototype_ `DECLARE_DELEGATE_RetVal(FVector2D, FGetLocation) DECLARE_DELEGATE_RetVal(EOrientation, FGetOrientation) DECLARE_DELEGATE_OneParam(FSetOrientation, EOrientation) DECLARE_DELEGATE_RetVal(EMediaImageViewerActivePosition, FGetActiveView) DECLARE_DELEGATE_RetVal(bool, FGetBool) DECLARE_DELEGATE_RetVal(float, FGetFloat) DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGA ...`
- L65 _public member_ `FSimpleDelegate SetABView;` — Changes to AB view.
- L68 _public member_ `FGetOrientation GetABOrientation;` — Gets the orientation in A/B mode. Will return the currently selected orientation even if not in A/B mode.
- L71 _public member_ `FSetOrientation SetABOrientation;` — Sets the orientation in A/B mode. Will set the next expected orientation even if not in A/B mode.
- L74 _public member_ `FGetActiveView GetActiveView;` — Returns a bitflag value indicating which image viewers are currently active (have images, not null or null image viewer).
- L77 _public member_ `FGetSettings GetSettings;` — Gets a pointer to the Media Viewer configurable settings.
- L80 _public member_ `FGetLocation GetViewerSize;` — Gets the size of the viewer paint area.
- L83 _public member_ `FGetLocation GetViewerPosition;` — Gets the position of the viewer paint area in the window.
- L86 _public member_ `FGetLocation GetCursorLocation;` — Gets the local cursor location on the window.
- L89 _public member_ `FSimpleDelegate SwapAB;` — Swaps the A and B viewers, including their transforms.
- L92 _public member_ `FGetBool AreTransformsLocked;` — Returns true if the transforms of multi-image-viewer views are locked in sync.
- L95 _public member_ `FSimpleDelegate ToggleLockedTransform;` — Toggles the transform lock for all image viewers.
- L98 _public member_ `FAddOffset AddOffsetToAll;` — Add an offset to all image viewers.
- L101 _public member_ `FAddRotation AddRotationToAll;` — Adds a rotation to all image viewers.
- L104 _public member_ `FMultiplyScale MultiplyScaleToAll;` — Multiplies the scale of all image viewers.
- L107 _public member_ `FMultiplyScale MultiplyScaleAroundCursorToAll;` — Multiplies the scale of all image viewers.
- L110 _public member_ `FSetTransform SetTransformToAll;` — Sets the transform of all image viewers.
- L113 _public member_ `FSimpleDelegate ResetTransformToAll;` — Resets the transform of all image viewers to 0,0,0; 0,0,0; 1.
- L116 _public member_ `FSetAllMirrorPlaneFlags MirrorAll;` — Set the mirror plane flag (on/off) to all image viewers.
- L119 _public member_ `FGetFloat GetSecondImageViewerOpacity;` — Gets the opacity of the second/B image viewer.
- L122 _public member_ `FSetFloat SetSecondImageViewerOpacity;` — Sets the opacity of the second/B image viewer.
- L125 _public member_ `FGetFloat GetABSplitterLocation;` — Gets the splitter location in percent (0-100)
- L128 _public member_ `FSetFloat SetABSplitterLocation;` — Sets the splitter location in percent (0-100)
- L131 _public member_ `FGetLibrary GetLibrary;` — Gets the image viewer library.
- L134 _public member_ `FSimpleDelegate RefreshView;` — Forces a refresh of the view on next tick.
- L137 _public member_ `FGetCommandList GetCommandList;` — Returns the command list for the general view.
- L140 _public member_ `FGetBool IsOverViewer;` — Returns true if the mouse is over the viewer.
- L147 _public member_ `FGetImageViewer GetImageViewer;` — Gets the image viewer in the given position.
- L150 _public member_ `FSetImageViewer SetImageViewer;` — Sets the image viewer in the given position.
- L153 _public member_ `FSimpleForPosition ClearImageViewer;` — Sets the image viewer in the given position to the null viewer.
- L156 _public member_ `FGetLocationForPosition GetPixelCoordinates;` — Gets the pixel coordinates hovered by the mouse for the image viewer in the given position.
- L159 _public member_ `FGetBoolForPosition IsOverImage;` — Returns true if the mouse is over the image viewer in the given position.
- L162 _public member_ `FSimpleForPosition CopyTransformToAll;` — Copies the transform of the image viewer in the given position to all other image viewers.
- L165 _public member_ `FGetCommandListForPosition GetCommandListForPosition;` — Gets the command list for image viewer in the given position.
- L168 _public member_ `FImageViewerEvent ImageViewerEvent;` — Generic event that can be broadcast between image viewers and controls.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MediaViewer` (scope `UE`)
- L33 _delegate_ `DECLARE_DELEGATE_RetVal(FVector2D, FGetLocation) DECLARE_DELEGATE_RetVal(EOrientation, FGetOrientation) DECLARE_DELEGATE_OneParam(FSetOrientation, EOrientation) DECLARE_DELEGATE_RetVal(EMediaImageViewerActivePosition, FGetActiveView) DECLARE_DELEGATE_RetVal(bool, FGetBool) DECLARE_DELEGATE_RetVal(float, FGetFloat) DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGA`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal(EOrientation, FGetOrientation) DECLARE_DELEGATE_OneParam(FSetOrientation, EOrientation) DECLARE_DELEGATE_RetVal(EMediaImageViewerActivePosition, FGetActiveView) DECLARE_DELEGATE_RetVal(bool, FGetBool) DECLARE_DELEGATE_RetVal(float, FGetFloat) DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageV`
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FSetOrientation, EOrientation) DECLARE_DELEGATE_RetVal(EMediaImageViewerActivePosition, FGetActiveView) DECLARE_DELEGATE_RetVal(bool, FGetBool) DECLARE_DELEGATE_RetVal(float, FGetFloat) DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal(EMediaImageViewerActivePosition, FGetActiveView) DECLARE_DELEGATE_RetVal(bool, FGetBool) DECLARE_DELEGATE_RetVal(float, FGetFloat) DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FGetBool) DECLARE_DELEGATE_RetVal(float, FGetFloat) DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L38 _delegate_ `DECLARE_DELEGATE_RetVal(float, FGetFloat) DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FSetFloat, float) DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L40 _delegate_ `DECLARE_DELEGATE_OneParam(FAddOffset, const FVector&) DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L41 _delegate_ `DECLARE_DELEGATE_OneParam(FAddRotation, const FRotator&) DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L42 _delegate_ `DECLARE_DELEGATE_OneParam(FMultiplyScale, float) DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L43 _delegate_ `DECLARE_DELEGATE_ThreeParams(FSetTransform, const FVector&, const FRotator&, float) DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal(FMediaViewerSettings*, FGetSettings) DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L45 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IMediaViewerLibrary>, FGetLibrary) DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L46 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FGetCommandList) DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L47 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetAllMirrorPlaneFlags, EMediaImageMirrorPlane, bool ) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FMediaImageViewer>, FGetImageViewer, EMediaImageViewerPosition) DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L50 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetImageViewer, EMediaImageViewerPosition, const TSharedRef<FMediaImageViewer>&) DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FSimpleForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L52 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FIntPoint, FGetLocationForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L53 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FGetBoolForPosition, EMediaImageViewerPosition) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L54 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<FUICommandList>, FGetCommandListForPosition, EMediaImageViewerPosition) DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FImageViewerEvent, const FMediaImageViewerEventParams&)`

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Widgets/IMediaViewerLibraryWidget.h` (Public)


#### class `UE::MediaViewer::IMediaViewerLibraryWidget`  
`class IMediaViewerLibraryWidget`  
_L19-63_
- desc: Displays a visual representation of a @see IMediaViewerLibrary.
- L57 _public prototype_ `virtual TSharedRef<SWidget> ToWidget() = 0;` — Converts this interface to its underlying widget.
- L62 _public prototype_ `virtual TSharedRef<IMediaViewerLibrary> GetLibrary() const = 0;` — Returns the underlying IMediaViewerLibrary implementation.

#### struct `UE::MediaViewer::IMediaViewerLibraryWidget::FArgs`  
`struct FArgs`  
_L46-52_
- L48 _public member_ `FOnImageViewerOpened OnImageViewerOpened;`
- L49 _public member_ `FOnGetGroupContextMenu OnGetGroupContextMenu;`
- L50 _public member_ `FOnGetItemContextMenu OnGetItemContextMenu;`
- L51 _public member_ `FGroupFilter GroupFilter;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MediaViewer` (scope `UE`)
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnImageViewerOpened, const FGuid&) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetGroupContextMenu, FName) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetItemContextMenu, const TArray<FMediaViewerLibraryItem>&) DECLARE_DELEGATE_RetVal_TwoParams(bool, FGroupFilter, const TSharedRef<const IMediaViewerLibrary>& InLibrary, const TSharedRef<const FMediaViewerLibraryGroup>& InGroup) struct FArgs { FOnImageViewerOpened OnImageViewerOpened; FOnGetGroupContextMenu OnGetGroupContextMenu; FOnGetItemContextMenu OnGetItemContextMenu; FGroupFilter GroupFilter; };` — Delegate that gets called when an item is selected in the Library. The given @see FGuid identifies the item that was selected.
- L32 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetGroupContextMenu, FName) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetItemContextMenu, const TArray<FMediaViewerLibraryItem>&) DECLARE_DELEGATE_RetVal_TwoParams(bool, FGroupFilter, const TSharedRef<const IMediaViewerLibrary>& InLibrary, const TSharedRef<const FMediaViewerLibraryGroup>& InGroup) struct FArgs { FOnImageViewerOpened OnImageViewerOpened; FOnGetGroupContextMenu OnGetGroupContextMenu; FOnGetItemContextMenu OnGetItemContextMenu; FGroupFilter GroupFilter; };` — Delegate that gets called for creating a context menu for a group. Return @see SNullWidget::NullWidget to not show a context menu.
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetItemContextMenu, const TArray<FMediaViewerLibraryItem>&) DECLARE_DELEGATE_RetVal_TwoParams(bool, FGroupFilter, const TSharedRef<const IMediaViewerLibrary>& InLibrary, const TSharedRef<const FMediaViewerLibraryGroup>& InGroup) struct FArgs { FOnImageViewerOpened OnImageViewerOpened; FOnGetGroupContextMenu OnGetGroupContextMenu; FOnGetItemContextMenu OnGetItemContextMenu; FGroupFilter GroupFilter; };` — Delegate that gets called for creating a context menu for a set of selected items. Return @see SNullWidget::NullWidget to not show a context menu.
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGroupFilter, const TSharedRef<const IMediaViewerLibrary>& InLibrary, const TSharedRef<const FMediaViewerLibraryGroup>& InGroup) struct FArgs { FOnImageViewerOpened OnImageViewerOpened; FOnGetGroupContextMenu OnGetGroupContextMenu; FOnGetItemContextMenu OnGetItemContextMenu; FGroupFilter GroupFilter; };` — Returns true to display the group. Return false to hide the group.

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Widgets/MediaImageStatusBarExtender.h` (Public)


#### struct `UE::MediaViewer::FMediaImageStatusBarExtension`  
`struct FMediaImageStatusBarExtension`  
_L18-31_
- L25 _public prototype_ `DECLARE_DELEGATE_OneParam(FDelegate, const TSharedRef<SHorizontalBox>&);` — Delegate that gets called for each extension when the status bar is constructed. The given @see SHorizontalBox is the layout container that the widget for the extension needs to be added to by calling. @see SHorizontalBox::AddSlot().
- L27 _public member_ `FName Hook;`
- L28 _public member_ `EExtensionHook::Position HookPosition = EExtensionHook::Before;`
- L29 _public member_ `TSharedPtr<FUICommandList> CommandList;`
- L30 _public member_ `FDelegate Delegate;`

#### class `UE::MediaViewer::FMediaImageStatusBarExtender`  
`class FMediaImageStatusBarExtender`  
_L33-52_
- L43 _public prototype_ `void AddExtension(FName InExtensionHook, EExtensionHook::Position InHookPosition, const TSharedPtr<FUICommandList>& InCommands, const FMediaImageStatusBarExtension::FDelegate& InDelegate);` — Adds an extension to the status bar. @param ExtensionHook The section the extension is applied to. @param HookPosition Where in relation to the section the extension is applied to. @param Commands The UI command list responsible for handling actions used in the widgets added in the extension. @param Delegate Delegate called for adding the extension widgets when the status bar is constructed.
- L47 _public prototype_ `void Apply(FName InExtensionHook, EExtensionHook::Position InHookPosition, const TSharedRef<SHorizontalBox>& InHorizontalBox) const;` — Used by the viewport to add extensions to the status bar.
- L51 _private member_ `TArray<FMediaImageStatusBarExtension> Extensions;` — List of extensions that get applied to the viewport status bar.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MediaViewer` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FDelegate, const TSharedRef<SHorizontalBox>&);` — Delegate that gets called for each extension when the status bar is constructed. The given @see SHorizontalBox is the layout container that the widget for the extension needs to be added to by calling. @see SHorizontalBox::AddSlot().

### `Plugins/Media/MediaViewer/Source/MediaViewer/Public/Widgets/SMediaViewerTab.h` (Public)


#### class `UE::MediaViewer::SMediaViewerTab`  
`class SMediaViewerTab : public SCompoundWidget`  
_L21-51_
- inherits: `SCompoundWidget`
- L23 _private function_ `SLATE_DECLARE_WIDGET(SMediaViewerTab, SCompoundWidget) SLATE_BEGIN_ARGS(SMediaViewerTab)`
- L33 _public prototype_ `SMediaViewerTab();`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const FMediaViewerArgs& InMediaViewerArgs);`
- L39 _public prototype_ `const FMediaViewerArgs& GetArgs() const;`
- L41 _public prototype_ `TSharedRef<IMediaViewerLibrary> GetLibrary() const;`
- L43 _public prototype_ `TSharedPtr<FMediaImageViewer> GetImageViewer(EMediaImageViewerPosition InPosition) const;`
- L45 _public prototype_ `void SetImageViewer(EMediaImageViewerPosition InPosition, TSharedPtr<FMediaImageViewer> InImageViewer);`
- L47 _public prototype_ `TSharedRef<Private::SMediaViewer> GetViewer() const;`
- L50 _protected member_ `TSharedPtr<Private::SMediaViewer> Viewer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MediaViewer` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::MediaViewer`)
