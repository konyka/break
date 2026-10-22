# Plugins / ImageWidgets

- module root: `Plugins/Editor/ImageWidgets/Source/ImageWidgets`
- headers: 15; symbols: 396
- symbol kinds: class=15, delegate=18, enum=4, enumerator=9, function=17, member=139, namespace=34, prototype=145, struct=15

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ColorViewerSample/ColorViewer.h` (Private)


#### struct `UE::ImageWidgets::Sample::FToneMapping`  
`struct FToneMapping`  
_L15-35_
- desc: Provide tone mapping capabilities. In this simple example, this is limited to just normal RGB plus luminance (grayscale).
- L19 _public function_ `FToneMapping(EMode Mode) : Mode(Mode)`
- L24 _public function_ `FLinearColor GetToneMappedColor(const FLinearColor& Color) const`
- L34 _public member_ `EMode Mode;`

#### enum `UE::ImageWidgets::Sample::FToneMapping::EMode`  
`enum class EMode`  
_L17-17_
- L17 _public enumerator_ `enum class EMode { RGB, Lum }; FToneMapping(EMode Mode) : Mode(Mode) { } FLinearColor GetToneMappedColor(const FLinearColor& Color) const`
- L17 _public enumerator_ `enum class EMode { RGB, Lum }; FToneMapping(EMode Mode) : Mode(Mode) { } FLinearColor GetToneMappedColor(const FLinearColor& Color) const`

#### class `UE::ImageWidgets::Sample::FColorViewer`  
`class FColorViewer final : public IImageViewer`  
_L41-106_
- inherits: `IImageViewer`
- desc: Image viewer implementation used by the image widgets. It contains any image data, in this case just colors, and renders the image data in the viewport widgets based on the viewport provided parameters.
- L60 _public prototype_ `virtual FImageInfo GetCurrentImageInfo() const override;` — IImageViewer overrides - begin
- L61 _public prototype_ `virtual void DrawCurrentImage(FViewport* Viewport, FCanvas* Canvas, const FDrawProperties& Properties) override;`
- L62 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetCurrentImagePixelColor(FIntPoint PixelCoords, int32 MipLevel) const override;`
- L63 _public prototype_ `virtual void OnImageSelected(const FGuid& Guid) override;`
- L64 _public prototype_ `virtual bool IsValidImage(const FGuid& Guid) const override;`
- L65 _public prototype_ `virtual FText GetImageName(const FGuid& Guid) const override;`
- L69 _public prototype_ `const FColorItem* AddColor();` — Adds a color item.
- L72 _public prototype_ `void RemoveColor(const FGuid& Guid);` — Removes a color item.
- L75 _public prototype_ `const FColorItem* RandomizeColor();` — Sets a random color as the current "image" as a simple proxy for the image content changing and/or users choosing different images to display.
- L78 _public prototype_ `FToneMapping::EMode GetToneMapping() const;` — Access to tone mapping data. This is effectively used by the viewport toolbar extensions as well as when drawing the image.
- L79 _public prototype_ `void SetToneMapping(FToneMapping::EMode Mode);`
- L82 _public prototype_ `FLinearColor GetDefaultToneMappedColor(const FColor& Color) const;` — Apply default tone mapping to a given color. This is used to generate the catalog thumbnail.
- L86 _public member_ `inline static const FIntPoint ImageSize = 512;` — Hardcoded values for the image size for all color. In a more realistic application, this value would depend on the actual current image.
- L90 _private prototype_ `bool ColorIndexIsValid(int32 Index) const;` — Checks if a given index is a valid image.
- L93 _private prototype_ `bool ColorGuidIsValid(const FGuid& Guid) const;` — Checks if a given guid is a valid image.
- L96 _private prototype_ `void DrawImage(int32 Index, FCanvas* Canvas, const FDrawProperties::FPlacement& Placement, const FVector2d& UV0, const FVector2d& UV1) const;` — Draws the color image with the given index. The UVs determine if all or only a part of the image is drawn, i.e. for AB comparisons.
- L99 _private member_ `FToneMapping ToneMapping = FToneMapping::EMode::RGB;` — The tone mapping data.
- L102 _private member_ `TArray<FColorItem> Colors;` — The color for the currently displayed image.
- L105 _private member_ `int32 SelectedColorIndex = INDEX_NONE;` — Index of the currently selected image.

#### struct `UE::ImageWidgets::Sample::FColorViewer::FColorItem`  
`struct FColorItem`  
_L47-57_
- desc: Necessary data for a color item.
- L50 _public member_ `FGuid Guid;` — Unique identifier for each item
- L53 _public member_ `FColor Color;` — The actual color value
- L56 _public member_ `FDateTime DateTime;` — Timestamp for when the item was created

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L9 _namespace_ `namespace Sample` (scope `UE::ImageWidgets`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ColorViewerSample/ColorViewerCommands.h` (Private)


#### class `UE::ImageWidgets::Sample::FColorViewerCommands`  
`class FColorViewerCommands : public TCommands<FColorViewerCommands>`  
_L15-26_
- inherits: `TCommands<FColorViewerCommands>`
- desc: Provides commands used for the color viewer sample.
- L18 _public prototype_ `FColorViewerCommands();`
- L20 _public prototype_ `virtual void RegisterCommands() override;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> AddColor;` — Adding a new color entry
- L23 _public member_ `TSharedPtr<FUICommandInfo> RandomizeColor;` — Setting current entry to a random color
- L24 _public member_ `TSharedPtr<FUICommandInfo> ToneMappingRGB;` — Switching to RGB (no tone mapping)
- L25 _public member_ `TSharedPtr<FUICommandInfo> ToneMappingLum;` — Switching to luminance (grayscale tone mapping)

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L10 _namespace_ `namespace Sample` (scope `UE::ImageWidgets`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ColorViewerSample/ColorViewerStyle.h` (Private)


#### class `UE::ImageWidgets::Sample::FColorViewerStyle`  
`class FColorViewerStyle : public FSlateStyleSet`  
_L14-24_
- inherits: `FSlateStyleSet`
- desc: Style declarations for the color viewer sample.
- L17 _public member_ `static FName StyleName;`
- L19 _public prototype_ `static FColorViewerStyle& Get();`
- L22 _private prototype_ `FColorViewerStyle();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L9 _namespace_ `namespace Sample` (scope `UE::ImageWidgets`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ColorViewerSample/ColorViewerWidget.h` (Private)


#### class `UE::ImageWidgets::Sample::SColorViewerWidget`  
`class SColorViewerWidget : public SCompoundWidget`  
_L18-74_
- inherits: `SCompoundWidget`
- desc: Widget that contains and configures the image widgets.
- L21 _public function_ `SLATE_BEGIN_ARGS(SColorViewerWidget)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L31 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& Geometry, const FKeyEvent& KeyEvent) override;` — Forwards key presses to the command bindings.
- L35 _private prototype_ `void BindCommands();` — Binds all the commands.
- L38 _private prototype_ `void AddColorButtons(FToolBarBuilder& ToolbarBuilder) const;` — Functions for adding buttons as viewport toolbar extensions.
- L39 _private prototype_ `void AddToneMappingButtons(FToolBarBuilder& ToolbarBuilder) const;`
- L42 _private prototype_ `void AddColor();` — Add a new color entry to the catalog.
- L45 _private prototype_ `void RandomizeColor();` — Choose a random color for the current entry.
- L48 _private prototype_ `bool RandomizeColorEnabled() const;` — Checks if the Randomize Color action is available.
- L51 _private prototype_ `TSharedPtr<SWidget> GetGroupContextMenu(FName GroupName) const;` — Creates a context menu for a group.
- L54 _private prototype_ `TSharedPtr<SWidget> GetItemsContextMenu(const TArray<FGuid>& Guids) const;` — Creates a context menu for a set of selected guids.
- L57 _private member_ `TSharedPtr<FColorViewer> ColorViewer;` — The image viewer implementation that contains the image data and renders the image.
- L60 _private member_ `TSharedPtr<SSplitter> Splitter;` — Adjustable divider between catalog on the left and viewport on the right.
- L63 _private member_ `TSharedPtr<SImageCatalog> Catalog;` — The image catalog that holds all currently available images.
- L66 _private member_ `TSharedPtr<SImageViewport> Viewport;` — The image viewport in which the current image gets displayed in.
- L69 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The commands used by this sample widget.
- L72 _private member_ `FName GroupColors;` — Names for groups in the catalog.
- L73 _private member_ `FName GroupFavorites;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L13 _namespace_ `namespace Sample` (scope `UE::ImageWidgets`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ImageABComparison.h` (Private)


#### class `UE::ImageWidgets::FImageABComparison`  
`class FImageABComparison`  
_L14-82_
- desc: Provides data and logic for AB comparisons of images.
- L17 _public function_ `DECLARE_DELEGATE_RetVal(FGuid, FGetCurrentImageGuid) DECLARE_DELEGATE_RetVal_OneParam(bool, FImageIsValid, const FGuid&) DECLARE_DELEGATE_RetVal_OneParam(FText, FGetImageName, const FGuid&) FImageABComparison(FImageIsValid&& InImageIsValid, FGetCurrentImageGuid&& InGetCurrentImageGuid, FGetImageName&& InGetImageName) : ImageIsValid(MoveTemp(InImageIsValid)) , GetCurrentImageGuid(MoveTemp(InGetCurrentImageGuid)) , GetImageName(MoveTemp(InGetImageName))`
- L37 _public function_ `bool CanSetABComparison(EAorB AorB) const`
- L47 _public function_ `void SetABComparison(EAorB AorB, const FGuid& Guid)`
- L52 _public function_ `bool ABComparisonIsSet(EAorB AorB) const`
- L57 _public function_ `bool IsActive() const`
- L62 _public function_ `const FGuid& GetGuidA() const`
- L67 _public function_ `const FGuid& GetGuidB() const`
- L72 _public function_ `FText GetName(EAorB AorB) const`
- L78 _private member_ `FGuid Guids[2];`
- L79 _private member_ `FImageIsValid ImageIsValid;`
- L80 _private member_ `FGetCurrentImageGuid GetCurrentImageGuid;`
- L81 _private member_ `FGetImageName GetImageName;`

#### enum `UE::ImageWidgets::FImageABComparison::EAorB`  
`enum class EAorB : int8`  
_L31-35_
- L33 _public enumerator_ `A`
- L34 _public enumerator_ `B`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(FGuid, FGetCurrentImageGuid) DECLARE_DELEGATE_RetVal_OneParam(bool, FImageIsValid, const FGuid&) DECLARE_DELEGATE_RetVal_OneParam(FText, FGetImageName, const FGuid&) FImageABComparison(FImageIsValid&& InImageIsValid, FGetCurrentImageGuid&& InGetCurrentImageGuid, FGetImageName&& InGetImageName) : ImageIsValid(MoveTemp(InImageIsValid)) , GetCurrentImageGuid(MoveTemp(InGetCurrentImageGuid)) , GetImageName(MoveTemp(InGetImageName)) { check(ImageIsValid.IsBound()); check(GetCurrentImageGuid.IsBound()); check(GetImageName.IsBound()); } enum class EAorB : int8 { A, B };`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FImageIsValid, const FGuid&) DECLARE_DELEGATE_RetVal_OneParam(FText, FGetImageName, const FGuid&) FImageABComparison(FImageIsValid&& InImageIsValid, FGetCurrentImageGuid&& InGetCurrentImageGuid, FGetImageName&& InGetImageName) : ImageIsValid(MoveTemp(InImageIsValid)) , GetCurrentImageGuid(MoveTemp(InGetCurrentImageGuid)) , GetImageName(MoveTemp(InGetImageName)) { check(ImageIsValid.IsBound()); check(GetCurrentImageGuid.IsBound()); check(GetImageName.IsBound()); } enum class EAorB : int8 { A, B };`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetImageName, const FGuid&) FImageABComparison(FImageIsValid&& InImageIsValid, FGetCurrentImageGuid&& InGetCurrentImageGuid, FGetImageName&& InGetImageName) : ImageIsValid(MoveTemp(InImageIsValid)) , GetCurrentImageGuid(MoveTemp(InGetCurrentImageGuid)) , GetImageName(MoveTemp(InGetImageName)) { check(ImageIsValid.IsBound()); check(GetCurrentImageGuid.IsBound()); check(GetImageName.IsBound()); } enum class EAorB : int8 { A, B };`

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ImageViewportClient.h` (Private)


#### class `UE::ImageWidgets::FImageViewportClient`  
`class FImageViewportClient : public FEditorViewportClient`  
_L23-97_
- inherits: `FEditorViewportClient`
- desc: Viewport client for controlling the camera and drawing viewport contents.
- L26 _public prototype_ `FImageViewportClient(const TWeakPtr<SEditorViewport>& InEditorViewport, FGetImageSize&& InGetImageSize, FDrawImage&& InDrawImage, FGetDrawSettings&& InGetDrawSettings, FGetLayoutAndDPIScaleFactor&& InGetLayoutAndDPIScaleFactor, FGetLayoutScaleFactor&& InGetLayoutScaleFactor, const FImageABComparison* InABComparison, const SImageViewport::FControllerSettings& InControllerSettings);`
- L32 _public prototype_ `virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L35 _public prototype_ `virtual EMouseCursor::Type GetCursor(FViewport* InViewport, int32 X, int32 Y) override;` — FEditorViewportClient overrides - begin
- L36 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L37 _public prototype_ `virtual void TrackingStarted(const FInputEventState& InputState, bool bIsDraggingWidget, bool bNudge) override;`
- L38 _public prototype_ `virtual void TrackingStopped() override;`
- L41 _public prototype_ `int32 GetMipLevel() const;`
- L42 _public prototype_ `void SetMipLevel(int32 InMipLevel);`
- L43 _public prototype_ `FImageViewportController::FZoomSettings GetZoom() const;`
- L44 _public prototype_ `void SetZoom(FImageViewportController::EZoomMode Mode, double Zoom);`
- L45 _public prototype_ `void ResetController(FIntPoint ImageSize);`
- L46 _public prototype_ `void ResetZoom(FIntPoint ImageSize);`
- L48 _public prototype_ `TPair<bool, FVector2d> GetPixelCoordinatesUnderCursor() const;`
- L61 _private prototype_ `FVector2d GetCurrentDrag() const;`
- L62 _private prototype_ `IImageViewer::FDrawProperties::FPlacement GetPlacementProperties(FIntPoint ImageSize, FVector2d ScaledViewportSize) const;`
- L63 _private prototype_ `IImageViewer::FDrawProperties::FMip GetMipProperties() const;`
- L65 _private prototype_ `void CreateOrDestroyCheckerTextureIfSettingsChanged(const SImageViewport::FDrawSettings& DrawSettings);`
- L66 _private prototype_ `bool MouseIsOverABComparisonDivider(FIntPoint MousePos) const;`
- L68 _private prototype_ `FVector2d GetScaledViewportSize() const;`
- L70 _private member_ `FGetImageSize GetImageSize;`
- L71 _private member_ `FDrawImage DrawImage;`
- L72 _private member_ `FGetDrawSettings GetDrawSettings;`
- L73 _private member_ `FGetLayoutAndDPIScaleFactor GetLayoutAndDPIScaleFactor;`
- L74 _private member_ `FGetLayoutScaleFactor GetLayoutScaleFactor;`
- L75 _private member_ `SImageViewport::FControllerSettings::FOnInputKey OnInputKey;`
- L76 _private member_ `const FImageABComparison* ABComparison;`
- L78 _private member_ `bool bDragging = false;`
- L79 _private member_ `FIntPoint DraggingStart;`
- L81 _private member_ `bool bMipSelected = true;`
- L82 _private member_ `int32 MipLevel = INDEX_NONE;`
- L84 _private member_ `IImageViewer::FDrawProperties::FPlacement CachedPlacement;`
- L85 _private member_ `bool bCachedPlacementIsValid = false;`
- L87 _private member_ `FImageViewportController Controller;`
- L89 _private member_ `TStrongObjectPtr<UTexture2D> CheckerTexture;`
- L90 _private member_ `FCheckerTextureSettings CachedCheckerTextureSettings;`
- L92 _private member_ `FVector2d CachedScaledViewportSize = FVector2d::ZeroVector;`
- L93 _private member_ `bool bZoomOnResize = false;`
- L95 _private member_ `double ABComparisonDivider = 0.5;`
- L96 _private member_ `bool bDraggingABComparisonDivider = false;`

#### struct `UE::ImageWidgets::FImageViewportClient::FCheckerTextureSettings`  
`struct FCheckerTextureSettings`  
_L51-59_
- L53 _public prototype_ `bool operator==(const FCheckerTextureSettings&) const = default;`
- L55 _public member_ `bool bEnabled = false;`
- L56 _public member_ `FLinearColor Color1;`
- L57 _public member_ `FLinearColor Color2;`
- L58 _public member_ `uint32 CheckerSize = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(FIntPoint, FGetImageSize) DECLARE_DELEGATE_ThreeParams(FDrawImage, FViewport*, FCanvas*, const IImageViewer::FDrawProperties&) DECLARE_DELEGATE_RetVal(SImageViewport::FDrawSettings, FGetDrawSettings) DECLARE_DELEGATE_RetVal(float, FGetLayoutAndDPIScaleFactor) DECLARE_DELEGATE_RetVal(float, FGetLayoutScaleFactor) class FImageViewportClient : public FEditorViewportClient { public: FImageViewportClient(const TWeakPtr<SEditorViewport>& InEditorViewport, FGetImageSize&& InGetImageSize, FDrawImage&& InDrawImage, FGetDrawSettings&& InGetDrawSettings, FGetLayoutAndDPIScaleFactor&& InGetLayoutAndDPIScaleFactor, FGetLayoutScaleFactor&& InGetLayoutScaleFactor, const FImageABComparison* InABComparison, const SImageViewport::FControllerSettings& InControllerSettings); virtual ~FImageViewportClient() override; virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L15 _delegate_ `DECLARE_DELEGATE_ThreeParams(FDrawImage, FViewport*, FCanvas*, const IImageViewer::FDrawProperties&) DECLARE_DELEGATE_RetVal(SImageViewport::FDrawSettings, FGetDrawSettings) DECLARE_DELEGATE_RetVal(float, FGetLayoutAndDPIScaleFactor) DECLARE_DELEGATE_RetVal(float, FGetLayoutScaleFactor) class FImageViewportClient : public FEditorViewportClient { public: FImageViewportClient(const TWeakPtr<SEditorViewport>& InEditorViewport, FGetImageSize&& InGetImageSize, FDrawImage&& InDrawImage, FGetDrawSettings&& InGetDrawSettings, FGetLayoutAndDPIScaleFactor&& InGetLayoutAndDPIScaleFactor, FGetLayoutScaleFactor&& InGetLayoutScaleFactor, const FImageABComparison* InABComparison, const SImageViewport::FControllerSettings& InControllerSettings); virtual ~FImageViewportClient() override; virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal(SImageViewport::FDrawSettings, FGetDrawSettings) DECLARE_DELEGATE_RetVal(float, FGetLayoutAndDPIScaleFactor) DECLARE_DELEGATE_RetVal(float, FGetLayoutScaleFactor) class FImageViewportClient : public FEditorViewportClient { public: FImageViewportClient(const TWeakPtr<SEditorViewport>& InEditorViewport, FGetImageSize&& InGetImageSize, FDrawImage&& InDrawImage, FGetDrawSettings&& InGetDrawSettings, FGetLayoutAndDPIScaleFactor&& InGetLayoutAndDPIScaleFactor, FGetLayoutScaleFactor&& InGetLayoutScaleFactor, const FImageABComparison* InABComparison, const SImageViewport::FControllerSettings& InControllerSettings); virtual ~FImageViewportClient() override; virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(float, FGetLayoutAndDPIScaleFactor) DECLARE_DELEGATE_RetVal(float, FGetLayoutScaleFactor) class FImageViewportClient : public FEditorViewportClient { public: FImageViewportClient(const TWeakPtr<SEditorViewport>& InEditorViewport, FGetImageSize&& InGetImageSize, FDrawImage&& InDrawImage, FGetDrawSettings&& InGetDrawSettings, FGetLayoutAndDPIScaleFactor&& InGetLayoutAndDPIScaleFactor, FGetLayoutScaleFactor&& InGetLayoutScaleFactor, const FImageABComparison* InABComparison, const SImageViewport::FControllerSettings& InControllerSettings); virtual ~FImageViewportClient() override; virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal(float, FGetLayoutScaleFactor) class FImageViewportClient : public FEditorViewportClient { public: FImageViewportClient(const TWeakPtr<SEditorViewport>& InEditorViewport, FGetImageSize&& InGetImageSize, FDrawImage&& InDrawImage, FGetDrawSettings&& InGetDrawSettings, FGetLayoutAndDPIScaleFactor&& InGetLayoutAndDPIScaleFactor, FGetLayoutScaleFactor&& InGetLayoutScaleFactor, const FImageABComparison* InABComparison, const SImageViewport::FControllerSettings& InControllerSettings); virtual ~FImageViewportClient() override; virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ImageViewportController.h` (Private)


#### class `UE::ImageWidgets::FImageViewportController`  
`class FImageViewportController`  
_L15-47_
- desc: Camera controller for the 2D viewport supporting panning and zooming. Note: All function parameters relating to the viewport need to be passed in with DPI scaling taken into account!
- L32 _public prototype_ `explicit FImageViewportController(EZoomMode DefaultZoomMode);`
- L34 _public prototype_ `void Pan(FVector2d ViewportDeltaWithDPIScaling);`
- L35 _public prototype_ `void Reset(FIntPoint ImageSize, FVector2d ViewportSizeWithDPIScaling);`
- L36 _public prototype_ `void ZoomIn(FVector2d CursorPixelPos, FIntPoint ImageSize);`
- L37 _public prototype_ `void ZoomOut(FVector2d CursorPixelPos, FIntPoint ImageSize);`
- L39 _public prototype_ `FVector2d GetPan(FVector2d Drag) const;`
- L40 _public prototype_ `FZoomSettings GetZoom() const;`
- L41 _public prototype_ `void SetZoom(EZoomMode ZoomMode, double Zoom, FIntPoint ImageSize, FVector2d ViewportSizeWithDPIScaling);`
- L44 _private member_ `FVector2d PanAmount;`
- L45 _private member_ `FZoomSettings ZoomSettings;`
- L46 _private member_ `EZoomMode DefaultZoomMode;`

#### enum `UE::ImageWidgets::FImageViewportController::EZoomMode`  
`enum class EZoomMode`  
_L18-23_
- L20 _public enumerator_ `Fit = static_cast<int32>(SImageViewport::FControllerSettings::EDefaultZoomMode::Fit)`
- L21 _public enumerator_ `Fill = static_cast<int32>(SImageViewport::FControllerSettings::EDefaultZoomMode::Fill)`
- L22 _public enumerator_ `Custom`

#### struct `UE::ImageWidgets::FImageViewportController::FZoomSettings`  
`struct FZoomSettings`  
_L26-30_
- L28 _public member_ `EZoomMode Mode;`
- L29 _public member_ `double Zoom;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ImageWidgets` (scope `UE`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ImageWidgetsCommands.h` (Private)


#### class `UE::ImageWidgets::FImageWidgetsCommands`  
`class FImageWidgetsCommands : public TCommands<FImageWidgetsCommands>`  
_L13-34_
- inherits: `TCommands<FImageWidgetsCommands>`
- desc: Provides commands used for the image widgets.
- L16 _public prototype_ `FImageWidgetsCommands();`
- L18 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> MipMinus;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> MipPlus;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ToggleOverlay;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> Zoom12;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> Zoom25;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> Zoom50;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> Zoom100;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> Zoom200;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> Zoom400;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> Zoom800;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ZoomFit;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ZoomFill;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ImageWidgets` (scope `UE`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ImageWidgetsLogCategory.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImageWidgets, Log, All) }`

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/ImageWidgetsStyle.h` (Private)


#### class `UE::ImageWidgets::FImageWidgetsStyle`  
`class FImageWidgetsStyle : public FSlateStyleSet`  
_L12-22_
- inherits: `FSlateStyleSet`
- desc: Style declarations for the image widgets.
- L15 _public member_ `static FName StyleName;`
- L17 _public prototype_ `static FImageWidgetsStyle& Get();`
- L20 _private prototype_ `FImageWidgetsStyle();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ImageWidgets` (scope `UE`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/SImageCatalogItem.h` (Private)


#### class `UE::ImageWidgets::SImageCatalogItem`  
`class SImageCatalogItem : public SCompoundWidget`  
_L15-30_
- inherits: `SCompoundWidget`
- desc: Widget for a single item row in the catalog.
- L18 _public function_ `SLATE_BEGIN_ARGS(SImageCatalogItem)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FImageCatalogItemData>& InItemData);`
- L24 _private prototype_ `FText GetItemInfo() const;`
- L25 _private prototype_ `FText GetItemName() const;`
- L26 _private prototype_ `const FSlateBrush* GetItemThumbnail() const;`
- L27 _private prototype_ `FText GetItemToolTip() const;`
- L29 _private member_ `TSharedPtr<FImageCatalogItemData> ItemData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ImageWidgets` (scope `UE`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Private/SImageViewportToolbar.h` (Private)


#### class `UE::ImageWidgets::SImageViewportToolbar`  
`class SImageViewportToolbar : public SViewportToolBar`  
_L23-79_
- inherits: `SViewportToolBar`
- desc: Extendable toolbar for the image viewport.
- L28 _public function_ `DECLARE_DELEGATE_RetVal(bool, FHasImage) DECLARE_DELEGATE_RetVal(int32, FNumMips) DECLARE_DELEGATE_RetVal(FGuid, FImageGuid) DECLARE_DELEGATE_RetVal(SImageViewport::FOverlaySettings, FGetOverlaySettings) SLATE_BEGIN_ARGS(SImageViewportToolbar)` — Callbacks to image viewport to retrieve necessary image metadata.
- L50 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FImageViewportClient>& InViewportClient, const TSharedPtr<FUICommandList>& InCommandList, FConstructParameters Parameters);`
- L54 _private prototype_ `FSlimHorizontalToolBarBuilder GetToolbarBuilder(const TSharedPtr<FExtender>& Extender) const;`
- L55 _private prototype_ `TSharedRef<SWidget> MakeLeftToolbar(const TSharedPtr<FExtender>& Extender);`
- L56 _private prototype_ `TSharedRef<SWidget> MakeCenterToolbar(const TSharedPtr<FExtender>& Extender, bool bEnableABComparison);`
- L57 _private prototype_ `TSharedRef<SWidget> MakeRightToolbar(const TSharedPtr<FExtender>& Extender);`
- L59 _private prototype_ `EVisibility GetZoomMenuVisibility() const;`
- L60 _private prototype_ `EVisibility GetMipMenuVisibility() const;`
- L61 _private prototype_ `EVisibility GetABVisibility() const;`
- L62 _private prototype_ `FText GetMipMenuLabel() const;`
- L63 _private prototype_ `TSharedRef<SWidget> MakeMipMenu() const;`
- L65 _private prototype_ `FText GetZoomMenuLabel() const;`
- L66 _private prototype_ `TSharedRef<SWidget> MakeZoomMenu() const;`
- L68 _private member_ `TSharedPtr<FImageViewportClient> ViewportClient;`
- L69 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L71 _private member_ `FHasImage HasImage;`
- L72 _private member_ `FNumMips NumMips;`
- L73 _private member_ `FImageGuid ImageGuid;`
- L74 _private member_ `FGetLayoutAndDPIScaleFactor GetLayoutAndDPIScaleFactor;`
- L75 _private member_ `FGetOverlaySettings GetOverlaySettings;`
- L76 _private member_ `FImageABComparison* ABComparison = nullptr;`
- L77 _private member_ `const ISlateStyle* ToolbarExtenderStyle = nullptr;`
- L78 _private member_ `FName ToolbarExtenderStyleName;`

#### struct `UE::ImageWidgets::SImageViewportToolbar::FConstructParameters`  
`struct FConstructParameters`  
_L37-48_
- desc: Parameter for constructing the toolbar.
- L39 _public member_ `FHasImage HasImage;`
- L40 _public member_ `FNumMips NumMips;`
- L41 _public member_ `FImageGuid ImageGuid;`
- L42 _public member_ `FGetLayoutAndDPIScaleFactor GetLayoutAndDPIScaleFactor;`
- L43 _public member_ `FGetOverlaySettings GetOverlaySettings;`
- L44 _public member_ `FImageABComparison* ABComparison = nullptr;`
- L45 _public member_ `TSharedPtr<FExtender> ToolbarExtender;`
- L46 _public member_ `const ISlateStyle* ToolbarExtenderStyle = nullptr;`
- L47 _public member_ `FName ToolbarExtenderStyleName;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FHasImage) DECLARE_DELEGATE_RetVal(int32, FNumMips) DECLARE_DELEGATE_RetVal(FGuid, FImageGuid) DECLARE_DELEGATE_RetVal(SImageViewport::FOverlaySettings, FGetOverlaySettings) SLATE_BEGIN_ARGS(SImageViewportToolbar) {} SLATE_END_ARGS() struct FConstructParameters { FHasImage HasImage; FNumMips NumMips; FImageGuid ImageGuid; FGetLayoutAndDPIScaleFactor GetLayoutAndDPIScaleFactor; FGetOverlaySettings GetOverlaySettings; FImageABComparison* ABComparison = nullptr; TSharedPtr<FExtender> ToolbarExtender; const ISlateStyle* ToolbarExtenderStyle = nullptr; FName ToolbarExtenderStyleName; };` — Callbacks to image viewport to retrieve necessary image metadata.
- L29 _delegate_ `DECLARE_DELEGATE_RetVal(int32, FNumMips) DECLARE_DELEGATE_RetVal(FGuid, FImageGuid) DECLARE_DELEGATE_RetVal(SImageViewport::FOverlaySettings, FGetOverlaySettings) SLATE_BEGIN_ARGS(SImageViewportToolbar) {} SLATE_END_ARGS() struct FConstructParameters { FHasImage HasImage; FNumMips NumMips; FImageGuid ImageGuid; FGetLayoutAndDPIScaleFactor GetLayoutAndDPIScaleFactor; FGetOverlaySettings GetOverlaySettings; FImageABComparison* ABComparison = nullptr; TSharedPtr<FExtender> ToolbarExtender; const ISlateStyle* ToolbarExtenderStyle = nullptr; FName ToolbarExtenderStyleName; };`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal(FGuid, FImageGuid) DECLARE_DELEGATE_RetVal(SImageViewport::FOverlaySettings, FGetOverlaySettings) SLATE_BEGIN_ARGS(SImageViewportToolbar) {} SLATE_END_ARGS() struct FConstructParameters { FHasImage HasImage; FNumMips NumMips; FImageGuid ImageGuid; FGetLayoutAndDPIScaleFactor GetLayoutAndDPIScaleFactor; FGetOverlaySettings GetOverlaySettings; FImageABComparison* ABComparison = nullptr; TSharedPtr<FExtender> ToolbarExtender; const ISlateStyle* ToolbarExtenderStyle = nullptr; FName ToolbarExtenderStyleName; };`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal(SImageViewport::FOverlaySettings, FGetOverlaySettings) SLATE_BEGIN_ARGS(SImageViewportToolbar) {} SLATE_END_ARGS() struct FConstructParameters { FHasImage HasImage; FNumMips NumMips; FImageGuid ImageGuid; FGetLayoutAndDPIScaleFactor GetLayoutAndDPIScaleFactor; FGetOverlaySettings GetOverlaySettings; FImageABComparison* ABComparison = nullptr; TSharedPtr<FExtender> ToolbarExtender; const ISlateStyle* ToolbarExtenderStyle = nullptr; FName ToolbarExtenderStyleName; };`

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Public/IImageViewer.h` (Public)


#### class `UE::ImageWidgets::IImageViewer`  
`class IImageViewer`  
_L17-146_
- desc: Interface for a component that wants to show image related content with the Slate widgets in the ImageWidget module. In this context, an "image" is considered to be any 2D content that is contained within an axis-aligned rectangle.
- L105 _public prototype_ `virtual FImageInfo GetCurrentImageInfo() const = 0;` — Provides any necessary metadata for the image widgets about the image that is currently supposed to be displayed. This data is generic in the sense that the image widgets don't need to know any of the image structure, its content or how to draw it. Instead, the image drawing is done directly via @see DrawCurrentImage. @return information about the image to be displayed
- L113 _public prototype_ `virtual void DrawCurrentImage(FViewport* Viewport, FCanvas* Canvas, const FDrawProperties& Properties) = 0;` — Draws the image that is currently supposed to be displayed within the 2D viewport. @param Viewport The viewport the image is drawn into @param Canvas The canvas used for drawing the image @param Properties Information for drawing the image based on the current image viewport state
- L121 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetCurrentImagePixelColor(FIntPoint PixelCoords, int32 MipLevel) const = 0;` — Provides information about a given pixel. @param PixelCoords XY coordinates for the pixel @param MipLevel MIP level that is currently displayed; this can be ignored for images not supporting MIPs @return Either a color value in byte or float format, i.e. FColor or FLinearColor, or no value if there is no valid pixel at the provided coordinates
- L128 _public prototype_ `virtual void OnImageSelected(const FGuid& Guid) = 0;` — Notifies about the image with the given GUID being selected. This can be implemented as an empty function if the image viewer implementation does not support switching between different images. @param Guid Unique identifier of the selected image
- L135 _public prototype_ `virtual bool IsValidImage(const FGuid& Guid) const = 0;` — Returns if a given GUID represents a currently available image. @param Guid Unique identifier of the potentially available image @return true if the GUID represents a currently available image
- L142 _public prototype_ `virtual FText GetImageName(const FGuid& Guid) const = 0;` — Returns the name of a currently available image. This is potentially used in the UI to refer to an image. @param Guid Unique identifier of the potentially available image @return Name of the image if the GUID represents a currently available image
- L145 _protected prototype_ `~IImageViewer() = default;`

#### struct `UE::ImageWidgets::IImageViewer::FImageInfo`  
`struct FImageInfo`  
_L23-36_
- desc: Information about an image to be displayed.
- L26 _public member_ `FGuid Guid;` — Unique image identifier. It can encode any helpful metadata as long as no two provided images have the same GUID.
- L29 _public member_ `FIntPoint Size;` — XY size of the image in pixels.
- L32 _public member_ `int32 NumMips;` — Number of available MIPs. This should be set to zero if the image type does not support mips.
- L35 _public member_ `bool bIsValid;` — Indicates that this image is valid for display.

#### struct `UE::ImageWidgets::IImageViewer::FDrawProperties`  
`struct FDrawProperties`  
_L41-97_
- desc: Information necessary for correctly drawing an image.
- L94 _public member_ `FPlacement Placement;`
- L95 _public member_ `FMip Mip;`
- L96 _public member_ `FABComparison ABComparison;`

#### struct `UE::ImageWidgets::IImageViewer::FDrawProperties::FPlacement`  
`struct FPlacement`  
_L46-60_
- desc: Where in the 2D plane the image rectangle is supposed to be drawn.
- L49 _public member_ `FVector2d Offset;` — Offset from the origin, i.e. (0, 0).
- L52 _public member_ `FVector2d Size;` — XY size of the axis aligned rectangle containing the image.
- L59 _public member_ `double ZoomFactor;` — The zoom factor used for the image. While this might not be necessary for drawing the image, it can be helpful in certain use cases. For example, interpolation could explicitly be turned off when zooming into a texture to show the discrete pixel contents of the texture instead of the interpolated result.

#### struct `UE::ImageWidgets::IImageViewer::FDrawProperties::FMip`  
`struct FMip`  
_L65-69_
- desc: Information about MIP levels. This can be ignored if the image type does not support MIPs.
- L68 _public member_ `float MipLevel;` — The selected MIP level.

#### struct `UE::ImageWidgets::IImageViewer::FDrawProperties::FABComparison`  
`struct FABComparison`  
_L74-92_
- desc: Information necessary for rendering AB comparisons.
- L77 _public function_ `bool IsActive() const` — @return true if an AB comparison should be drawn instead of a single image.
- L80 _public member_ `FGuid GuidA;` — Unique identifier for image A.
- L83 _public member_ `FGuid GuidB;` — Unique identifier for image B.
- L91 _public member_ `double Threshold;` — Value between 0..1 to indicate where the threshold between images A and B is. A value of 0 means that only B should be drawn. A value of 0.5 means that the left half of A and the right half of B should be drawn. A value of 1 means that only A should be drawn.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ImageWidgets` (scope `UE`)

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Public/SImageCatalog.h` (Public)


#### struct `UE::ImageWidgets::FImageCatalogItemData`  
`struct FImageCatalogItemData`  
_L14-32_
- desc: Contains all data for a catalog item.
- L16 _public prototype_ `FImageCatalogItemData(FGuid Guid, const FSlateBrush& Brush, const FText& Name, const FText& Info, const FText& ToolTip);`
- L19 _public member_ `FGuid Guid;` — Unique identifier for the catalog item
- L22 _public member_ `FSlateBrush Thumbnail;` — Brush used for displaying the item's thumbnail
- L25 _public member_ `FText Name;` — Name of the item
- L28 _public member_ `FText Info;` — Auxiliary information for the item
- L31 _public member_ `FText ToolTip;` — Tooltip that is shown when hovering over any part of the item's widget in the catalog

#### class `UE::ImageWidgets::SImageCatalog`  
`class SImageCatalog : public SCompoundWidget`  
_L39-373_
- inherits: `SCompoundWidget`
- desc: Generic catalog widget for listing and interacting with 2D image-like content. Each catalog item is represented by its own widget based on its @see FImageCatalogItemData. Entries in the catalog can be assigned to customizable groups.
- L46 _public function_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, const FGuid&) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetGroupContextMenu, FName) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetItemsContextMenu, const TArray<FGuid>&) SLATE_BEGIN_ARGS(SImageCatalog) : _DefaultGroupName(NAME_None) , _DefaultGroupHeading(FText()) , _SelectionMode(ESelectionMode::Multi) , _bAllowSelectionAcrossGroups(false) , _bShowEmptyGroups(false)` — Delegate that gets called when an item is selected in the catalog. The given @see FGuid identifies the item that was selected.
- L70 _public prototype_ `SLATE_ARGUMENT(FName, DefaultGroupName) SLATE_ARGUMENT(FText, DefaultGroupHeading) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetGroupContextMenu, OnGetGroupContextMenu) SLATE_EVENT(FOnGetItemsContextMenu, OnGetItemsContextMenu) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_ARGUMENT(bool, bAllowSelectionAcrossGroups) SLATE_ARGUMENT(bool, bShowEmptyGroups) SLATE_END_ARGS() void Construct(const FArguments& Args);` — Name of the default group, i.e. the group that gets used when no group is explicitly specified.
- L103 _public prototype_ `FName GetDefaultGroupName() const;` — @returns The name of the default group.
- L111 _public prototype_ `bool AddGroup(FName Name, const FText& Heading);` — Add a custom group to the catalog. @param Name Unique identifier for the group. @param Heading Header text to be used for the group; no header will be shown if this is empty. @returns False if a group with the given name already exits, otherwise true.
- L121 _public prototype_ `bool AddGroup(FName Name, const FText& Heading, FName BeforeGroupWithThisName);` — Add a custom group to the catalog before an already existing group. @param Name Unique identifier for the group. @param Heading Header text to be used for the group; no header will be shown if this is empty. @param BeforeGroupWithThisName Name of an already existing group before which the new custom group is going to be added. @returns False if a group with the given name already exits or if the group before which the new group is supposed to be added does not exist, otherwise true.
- L129 _public prototype_ `bool SetGroupHeading(FName Name, const FText& Heading);` — Set the header text for an existing group. @param Name Unique identifier for the group. @param Heading Header text to be used for the group; no header will be shown if this is empty. @returns False if a group with the given name does not exist, otherwise true.
- L137 _public prototype_ `TOptional<TArray<FGuid>> RemoveGroup(FName Name);` — Remove an existing group and any items in the group. @param Name Unique identifier of the group; must not be the default group name. @returns An empty value if a group with the given name does not exist, otherwise a list of unique identifiers for the items that were in the group and got removed from the catalog.
- L147 _public prototype_ `TOptional<TArray<FGuid>> RemoveGroup(FName Name, FName GroupToMoveItemsInto);` — Remove an existing group, and moves any items in the group into another group. Note that if the other group does not exist, the items get moved into the default group instead. @param Name Unique identifier of the group; must not be the default group name. @param GroupToMoveItemsInto Name of an already existing group in which the items from the removed group get moved into. @returns An empty value if a group with the given name does not exist, otherwise a list of unique identifiers for the items that were in the group and got moved into the other group.
- L153 _public prototype_ `int32 NumGroups() const;` — Return the number of groups in the catalog including the default group. @returns The number of groups in the catalog.
- L160 _public prototype_ `TOptional<FName> GetGroupNameAt(int32 Index) const;` — Return the name of the group at a given position. @param Index Position of the group, with 0 being the first, and @see NumGroups() - 1 being the last. @returns An empty value if the given position is invalid, otherwise the name of the group at that position.
- L167 _public prototype_ `bool AddItem(const TSharedPtr<FImageCatalogItemData>& Item);` — Add an item to the default group. @param Item Data for the item that is being added. @returns True if the item was added successfully.
- L176 _public prototype_ `bool AddItem(const TSharedPtr<FImageCatalogItemData>& Item, const FGuid& BeforeItemWithThisGuid);` — Add an item to the default group right before an existing item. If the unique identifier for the other item is invalid or not in the default group, the item will be added at the end of the default group instead. @param Item Data for the item that is being added. @param BeforeItemWithThisGuid Unique identifier of the other item before which the new item should be added. @returns True if the item was added successfully.
- L184 _public prototype_ `bool AddItem(const TSharedPtr<FImageCatalogItemData>& Item, FName Group);` — Add an item to an existing group. @param Item Data for the item that should be added. @param Group Name of the existing group to which the item should be added. @returns False if a group with the given name does not exist, otherwise true.
- L194 _public prototype_ `bool AddItem(const TSharedPtr<FImageCatalogItemData>& Item, FName Group, const FGuid& BeforeItemWithThisGuid);` — Add an item to an existing group right before an existing item. If the unique identifier for the other item is invalid or not in the given group, the item will be added at the end of the group instead. @param Item Data for the item that should be added. @param Group Name of the existing group to which the item should be added. @param BeforeItemWithThisGuid Unique identifier of the other item before which the new item should be added. @returns False if a group with the given name does not exist, otherwise true.
- L203 _public prototype_ `bool MoveItem(const FGuid& Guid, const FGuid& BeforeItemWithThisGuid);` — Move an already existing item before another item within the same group. @param Guid The unique identifier of the existing item that should be moved. @param BeforeItemWithThisGuid Unique identifier of the other item before which the item should be moved. @returns False if the item to be moved or the item before which it should be moved does not exist or if both are not in the same group, otherwise true.
- L212 _public prototype_ `bool MoveItem(const FGuid& Guid, FName Group);` — Move an already existing item to another group. @param Guid The unique identifier of the existing item that should be moved. @param Group Name of the existing group to which the item should be moved. @returns False if an item with the given unique identifier does not exist, a group with the given name does not exist, or the item is already in the given group, otherwise true.
- L222 _public prototype_ `bool MoveItem(const FGuid& Guid, FName Group, const FGuid& BeforeItemWithThisGuid);` — Move an already existing item to another group, before another item within that group. @param Guid The unique identifier of the existing item that should be moved. @param Group Name of the existing group to which the item should be moved. @param BeforeItemWithThisGuid Unique identifier of the other item before which the item should be moved. @returns False if an item with the given unique identifier does not exist, a group with the given name does not exist, or the item is already in the given group, otherwise true.
- L229 _public prototype_ `bool RemoveItem(const FGuid& Guid);` — Remove an existing item. @param Guid The unique identifier of the existing item. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L235 _public prototype_ `int32 NumItems() const;` — Return the total number of items in the catalog. @returns The number of items in the catalog across all groups.
- L242 _public prototype_ `int32 NumItems(FName Group) const;` — Return the number of items in a group. @param Group Name of an existing group. @returns The number of items in the given group.
- L249 _public prototype_ `TSharedPtr<const FImageCatalogItemData> GetItem(const FGuid& Guid) const;` — Retrieve the existing item for a given unique identifier. @param Guid The unique identifier of the item. @return The pointer to the item or an invalid pointer if no item with the given unique identifier exists.
- L256 _public prototype_ `TOptional<FName> GetItemGroupName(const FGuid& Guid) const;` — Return the group an existing item belongs to. @param Guid The unique identifier of the existing item. @returns An empty value if an item with the given unique identifier does not exist, otherwise the name of the group the item belongs to.
- L263 _public prototype_ `TOptional<int32> GetItemIndex(const FGuid& Guid) const;` — Return the index of an existing item within the group it belongs to. @param Guid The unique identifier of the existing item. @returns An empty value if no item with the given unique identifier exists, otherwise index of the item in the group.
- L271 _public prototype_ `TOptional<TTuple<FName, int32>> GetItemGroupNameAndIndex(const FGuid& Guid) const;` — Return an existing item's group and the index within that group. @param Guid The unique identifier of the existing item. @returns An empty value if an item with the given unique identifier does not exist, otherwise the name of the group the item belongs to and the index of the item in the group.
- L278 _public prototype_ `TSharedPtr<const FImageCatalogItemData> GetItemAt(int32 Index) const;` — Retrieve the existing item for a given index within the default group. @param Index Index of the item in the default group; should be at least 0 and less than @see NumItems(@see GetDefaultGroup()). @returns The pointer to the item or an invalid pointer if the index is invalid.
- L286 _public prototype_ `TSharedPtr<const FImageCatalogItemData> GetItemAt(int32 Index, FName Group) const;` — Retrieve the existing item within a given group for a given index. @param Index Index of the item in the given group; should be at least 0 and less than @see NumItems(Group). @param Group Name of an existing group. @returns The pointer to the item or an invalid pointer if the group does not exist or the index is invalid.
- L293 _public prototype_ `TOptional<FGuid> GetItemGuidAt(int32 Index) const;` — Retrieve the unique identifier of an existing item at the given index within the default group. @param Index Index of the item in the default group; should be at least 0 and less than @see NumItems(@see GetDefaultGroup()). @return Unique identifier of the item or no value if the index is invalid.
- L301 _public prototype_ `TOptional<FGuid> GetItemGuidAt(int32 Index, FName Group) const;` — Retrieve the unique identifier of an existing item at the given index within the given group. @param Index Index of the item in the given group; should be at least 0 and less than @see NumItems(Group). @param Group Name of an existing group. @return Unique identifier of the item or no value if the group does not exist or the index is invalid.
- L308 _public prototype_ `bool SelectItem(const FGuid& Guid);` — Select an existing item. @param Guid The unique identifier of the existing item. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L315 _public prototype_ `bool DeselectItem(const FGuid& Guid);` — Deselect an existing item. @param Guid The unique identifier of the existing item. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L320 _public prototype_ `void ClearSelection();` — Clear any selection in the catalog, i.e. across all groups.
- L327 _public prototype_ `bool ClearSelection(FName Group);` — Clear the selection for a given group; selections in other groups will be unchanged. @param Group Name of an existing group. @returns False if a group with the given name does not exist
- L334 _public prototype_ `bool UpdateItem(const FImageCatalogItemData& Item);` — Update an existing item's data. The item data needs to contain the item's unique identifier. @param Item Data for the exiting item that should be updated, including its unique identifier. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L342 _public prototype_ `bool UpdateItemInfo(const FGuid& Guid, const FText& Info);` — Update the info text of an existing item. @param Guid The unique identifier of the existing item. @param Info Text for the info label in the item's widget. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L351 _public prototype_ `bool UpdateItemName(const FGuid& Guid, const FText& Name);` — Update the name of an existing item. Nothing happens if no item with the given unique identifier exists in the catalog. @param Guid The unique identifier of the existing item. @param Name Text for the name label in the item's widget. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L360 _public prototype_ `bool UpdateItemThumbnail(const FGuid& Guid, const FSlateBrush& Thumbnail);` — Update the thumbnail of an existing item. Nothing happens if no item with the given unique identifier exists in the catalog. @param Guid The unique identifier of the existing item. @param Thumbnail Brush used for the thumbnail in the item's widget. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L369 _public prototype_ `bool UpdateItemToolTip(const FGuid& Guid, const FText& ToolTip);` — Update the tooltip text of an existing item. Nothing happens if no item with the given unique identifier exists in the catalog. @param Guid The unique identifier of the existing item. @param ToolTip Text for the tooltip label in the item's widget. @returns False if an item with the given unique identifier does not exist, otherwise true.
- L372 _private member_ `TPimplPtr<class FImpl> Impl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L46 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, const FGuid&) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetGroupContextMenu, FName) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetItemsContextMenu, const TArray<FGuid>&) SLATE_BEGIN_ARGS(SImageCatalog) : _DefaultGroupName(NAME_None) , _DefaultGroupHeading(FText()) , _SelectionMode(ESelectionMode::Multi) , _bAllowSelectionAcrossGroups(false) , _bShowEmptyGroups(false) { } SLATE_ARGUMENT(FName, DefaultGroupName) SLATE_ARGUMENT(FText, DefaultGroupHeading) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetGroupContextMenu, OnGetGroupContextMenu) SLATE_EVENT(FOnGetItemsContextMenu, OnGetItemsContextMenu) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode)` — Delegate that gets called when an item is selected in the catalog. The given @see FGuid identifies the item that was selected.
- L52 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetGroupContextMenu, FName) DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetItemsContextMenu, const TArray<FGuid>&) SLATE_BEGIN_ARGS(SImageCatalog) : _DefaultGroupName(NAME_None) , _DefaultGroupHeading(FText()) , _SelectionMode(ESelectionMode::Multi) , _bAllowSelectionAcrossGroups(false) , _bShowEmptyGroups(false) { } SLATE_ARGUMENT(FName, DefaultGroupName) SLATE_ARGUMENT(FText, DefaultGroupHeading) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetGroupContextMenu, OnGetGroupContextMenu) SLATE_EVENT(FOnGetItemsContextMenu, OnGetItemsContextMenu) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_ARGUMENT(bool, bAllowSelectionAcrossGroups) SLATE_ARGUMENT(bool, bShowEmptyGroups)` — Delegate that gets called for creating a context menu for a group. Return @see SNullWidget::NullWidget to not show a context menu.
- L58 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FOnGetItemsContextMenu, const TArray<FGuid>&) SLATE_BEGIN_ARGS(SImageCatalog) : _DefaultGroupName(NAME_None) , _DefaultGroupHeading(FText()) , _SelectionMode(ESelectionMode::Multi) , _bAllowSelectionAcrossGroups(false) , _bShowEmptyGroups(false) { } SLATE_ARGUMENT(FName, DefaultGroupName) SLATE_ARGUMENT(FText, DefaultGroupHeading) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetGroupContextMenu, OnGetGroupContextMenu) SLATE_EVENT(FOnGetItemsContextMenu, OnGetItemsContextMenu) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_ARGUMENT(bool, bAllowSelectionAcrossGroups) SLATE_ARGUMENT(bool, bShowEmptyGroups) SLATE_END_ARGS()` — Delegate that gets called for creating a context menu for a set of selected items. Return @see SNullWidget::NullWidget to not show a context menu.

### `Plugins/Editor/ImageWidgets/Source/ImageWidgets/Public/SImageViewport.h` (Public)


#### class `UE::ImageWidgets::SImageViewport`  
`class SImageViewport : public SEditorViewport`  
_L23-311_
- inherits: `SEditorViewport`
- desc: Generic viewport for displaying and interacting with 2D image-like content. The drawing of the images is deferred to an @see IImageViewer implementation that needs to be provided upon construction. This viewport only uses the metadata provided by the image viewer to have sufficient information about the image without being aware of its actual format or contents.
- L151 _public function_ `SLATE_BEGIN_ARGS(SImageViewport) : _ToolbarExtenderStyle(nullptr) , _bABComparisonEnabled(false)`
- L158 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FExtender>, ToolbarExtender) SLATE_ARGUMENT(const ISlateStyle*, ToolbarExtenderStyle) SLATE_ARGUMENT(FName, ToolbarExtenderStyleName) /** Extensions for the viewport status bar;` — Extensions for the viewport toolbar; valid hooks are "ToolbarLeft", "ToolbarCenter", "ToolbarRight"
- L194 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IImageViewer>& InImageViewer);` — Function used by Slate to construct the image viewport widget with the given arguments. @param InArgs Slate arguments defined above @param InImageViewer @see IImageViewer implementation that holds and draws the actual image contents.
- L201 _public prototype_ `TSharedPtr<SViewportToolBar> GetParentToolbar() const;` — Provides access to the viewport toolbar, which is needed to dynamically generate certain toolbar widgets, e.g. an @see SEditorViewportToolbarMenu, as part of a toolbar extension. @return Pointer to the viewport toolbar
- L220 _public prototype_ `FPixelCoordinatesUnderCursorResult GetPixelCoordinatesUnderCursor() const;` — Provides the pixel coordinates under the cursor. @return Pixel coordinates result under the cursor; see @see FPixelCoordinatesUnderCursorResult for more details
- L225 _public prototype_ `void RequestRedraw() const;` — Request to redraw the viewport contents as soon as possible.
- L231 _public prototype_ `void ResetController(FIntPoint ImageSize) const;` — Resets the camera controller to default values. @param ImageSize Size of the currently displayed image in pixels
- L236 _public prototype_ `void ResetMip() const;` — Resets the MIP level to the default.
- L242 _public prototype_ `void ResetZoom(FIntPoint ImageSize) const;` — Resets the zoom to default. @param ImageSize Size of the currently displayed image in pixels
- L246 _public function_ `virtual bool IsVisible() const override` — Overriding this method avoids the 0.25 seconds update delay in SEditorViewport.
- L248 _protected prototype_ `virtual void BindCommands() override;`
- L249 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L250 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L254 _protected prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;` — SCompoundWidget overrides - begin
- L258 _private prototype_ `TSharedRef<SWidget> MakeViewportToolbarOverlay();`
- L261 _private prototype_ `TSharedRef<SWidget> MakeStatusBar(TSharedRef<SOverlay> Overlay);` — Create the status bar widgets.
- L264 _private prototype_ `float GetDPIScaleFactor() const;` — Provides the window DPI scale factor.
- L267 _private prototype_ `float GetLayoutScaleFactor() const;` — Provides the external layout factor (ratio of accumulated scale to window DPI).
- L270 _private prototype_ `float GetLayoutAndDPIScaleFactor() const;` — Provides the layout and DPI scale factor, i.e. the full accumulated geometry scale.
- L273 _private prototype_ `FText GetPickerLabel() const;` — Provides the text for the color picker display in the status bar.
- L276 _private prototype_ `FText GetResolutionLabel() const;` — Provides the text for the resolution display in the status bar.
- L279 _private member_ `TAttribute<FDrawSettings> DrawSettings;` — Makes the draw settings available either as fixed values or via a callback to the outside of the viewport.
- L282 _private member_ `TAttribute<FOverlaySettings> OverlaySettings;` — Makes the overlay settings available either as fixed values or via a callback to the outside of the viewport.
- L285 _private member_ `bool bABComparisonEnabled = false;` — Flag that determines if AB comparison widgets are enabled or not. The value does not change after the call to @see Construct().
- L288 _private member_ `TPimplPtr<FImageABComparison> ABComparison;` — Data and logic related to AB comparisons. This is effectively unused when @see bABComparisonEnabled is set to false.
- L291 _private member_ `TSharedPtr<IImageViewer> ImageViewer;` — The image viewer that holds and draws the actual images.
- L294 _private member_ `TSharedPtr<FImageViewportClient> ImageViewportClient;` — The viewport client that takes care of camera controls and displaying the viewport contents.
- L297 _private member_ `TSharedPtr<SImageViewportToolbar> ImageViewportToolbar;` — The toolbar that controls some of the behavior of the viewport and optionally also the image viewer via toolbar extensions.
- L300 _private member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extensions provided by the call to @see Construct(). This pointer is reset after the extensions were applied during construction.
- L303 _private member_ `const ISlateStyle* ToolbarExtenderStyle = nullptr;` — Style override for toolbar extender. Only used during construction, then reset.
- L304 _private member_ `FName ToolbarExtenderStyleName;`
- L307 _private member_ `TSharedPtr<FStatusBarExtender> StatusBarExtender;` — Status bar extensions provided by the call to @see Construct(). This pointer is reset after the extensions were applied during construction.
- L310 _private member_ `mutable float AllottedGeometryScale = 1.0f;` — Cached scale for the allotted geometry; used to correctly incorporate the overall scale of the layout when drawing the image.

#### class `UE::ImageWidgets::SImageViewport::FStatusBarExtender`  
`class FStatusBarExtender`  
_L31-59_
- desc: Contains any extensions widgets for the viewport toolbar. This implementation is similar to the existing toolbar extender, i.e. FExtender, which is designed to only work with dedicated toolbar builders and can currently not be used with status bars.
- L39 _public prototype_ `DECLARE_DELEGATE_OneParam(FDelegate, SHorizontalBox&);` — Delegate that gets called for each extension when the status bar is constructed. The given @see SHorizontalBox is the layout container that the widget for the extension needs to be added to by calling @see SHorizontalBox::AddSlot().
- L48 _public prototype_ `void AddExtension(FName ExtensionHook, EExtensionHook::Position HookPosition, const TSharedPtr<FUICommandList>& Commands, const FDelegate& Delegate);` — Adds an extension to the status bar. @param ExtensionHook The section the extension is applied to @param HookPosition Where in relation to the section the extension is applied to @param Commands The UI command list responsible for handling actions used in the widgets added in the extension @param Delegate Delegate called for adding the extension widgets when the status bar is constructed
- L55 _private prototype_ `void Apply(FName ExtensionHook, EExtensionHook::Position HookPosition, SHorizontalBox& HorizontalBox) const;` — Used by the viewport to add extensions to the status bar.
- L58 _private member_ `TArray<TPimplPtr<FStatusBarExtension>> Extensions;` — List of extensions that get applied to the viewport status bar.

#### struct `UE::ImageWidgets::SImageViewport::FDrawSettings`  
`struct FDrawSettings`  
_L64-97_
- desc: Settings related to drawing viewport contents other than the image itself.
- L67 _public member_ `FLinearColor ClearColor = FLinearColor::Black;` — Clear color for the viewport.
- L72 _public member_ `bool bBorderEnabled = false;` — Flag that enables drawing a border around the image. If enabled, the border is drawn underneath the image. The center of the line drawn for the border is at the exact edge of the image, i.e. when the image is drawn on top of it, the outer half of the border is visible, and the inner half is occluded by the image.
- L75 _public member_ `float BorderThickness = 1.0f;` — Thickness of the border.
- L78 _public member_ `FLinearColor BorderColor = FVector3f(0.2f);` — Color of the border
- L81 _public member_ `bool bBackgroundColorEnabled = false;` — Flag that enables the drawing of the background color within the image rectangle.
- L84 _public member_ `FLinearColor BackgroundColor = FLinearColor::Black;` — Color for the background within the image rectangle. If this is different to the clear color, it shows where the image is even if nothing is drawn.
- L87 _public member_ `bool bBackgroundCheckerEnabled = false;` — Flag that enabled the drawing of a background checker texture. If this is enabled, the texture is drawn on top of the background color.
- L90 _public member_ `FLinearColor BackgroundCheckerColor1 = FLinearColor::White;` — First color used in the background checker texture.
- L93 _public member_ `FLinearColor BackgroundCheckerColor2 = FVector3f(0.8f);` — Second color used in the background checker texture.
- L96 _public member_ `uint32 BackgroundCheckerSize = 8;` — Size of a single square within the background checker texture in pixels.

#### struct `UE::ImageWidgets::SImageViewport::FControllerSettings`  
`struct FControllerSettings`  
_L102-128_
- desc: Settings related to viewport controls.
- L118 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnInputKey, const FInputKeyEventArgs& EventArgs);` — Delegate for custom input key event handling in the viewport client. The delegate is called after the image viewports input key events were handled, e.g. zoom or view reset via F key, and before a call to @see FEditorViewportClient::InputKey(). @param	EventArgs - The Input event args. @return	True to consume the key event, false to pass it on.
- L121 _public member_ `EDefaultZoomMode DefaultZoomMode = EDefaultZoomMode::Fit;` — Zoom mode that gets set on viewport construction and whenever the viewport controller is reset via @see ResetController().
- L124 _public member_ `FOnInputKey OnInputKey;` — Delegate for custom input key handling.
- L127 _public member_ `bool bZoomOnResize = false;` — Adjusts zoom to be proportional to viewport resizes, e.g. doubling the viewport size will double the zoom.

#### enum `UE::ImageWidgets::SImageViewport::FControllerSettings::EDefaultZoomMode`  
`enum class EDefaultZoomMode`  
_L104-108_
- L106 _public enumerator_ `Fit` — Make the image fit within the viewport, but do not make it larger than the original size.
- L107 _public enumerator_ `Fill` — Make the image fit within the viewport, and if it is smaller than the viewport, zoom in to fill the viewport.

#### struct `UE::ImageWidgets::SImageViewport::FOverlaySettings`  
`struct FOverlaySettings`  
_L133-149_
- desc: Settings related to the viewport overlay.
- L136 _public member_ `bool bDisableZoomButton = false;` — Do not show the zoom button in the left toolbar.
- L139 _public member_ `bool bDisableMipButton = false;` — Do not show the MIP button in the left toolbar.
- L142 _public member_ `bool bDisableABComparisonButtons = false;` — Do not show the AB comparison buttons in the center toolbar.
- L145 _public member_ `bool bDisableStatusBarLeft = false;` — Do not show the bottom left status bar.
- L148 _public member_ `bool bDisableStatusBarRight = false;` — Do not show the bottom right status bar.

#### struct `UE::ImageWidgets::SImageViewport::FPixelCoordinatesUnderCursorResult`  
`struct FPixelCoordinatesUnderCursorResult`  
_L206-214_
- desc: Result for calls to @see GetPixelCoordinatesUnderCursor.
- L209 _public member_ `bool bIsValid = false;` — Indicates that the cursor position is currently valid. This is set to false, for example, when the cursor is outside the widget.
- L213 _public member_ `FVector2d Coordinates;` — Pixel coordinates under the cursor relative to the image rectangle size and placement. Note that the coordinates might be outside the image rectangle, i.e. values might be negative or larger than the image size.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FDelegate, SHorizontalBox&);` — Delegate that gets called for each extension when the status bar is constructed. The given @see SHorizontalBox is the layout container that the widget for the extension needs to be added to by calling @see SHorizontalBox::AddSlot().
- L118 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnInputKey, const FInputKeyEventArgs& EventArgs);` — Delegate for custom input key event handling in the viewport client. The delegate is called after the image viewports input key events were handled, e.g. zoom or view reset via F key, and before a call to @see FEditorViewportClient::InputKey(). @param	EventArgs - The Input event args. @return	True to consume the key event, false to pass it on.
