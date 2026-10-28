# Editor / TextureEditor

- module root: `Source/Editor/TextureEditor`
- headers: 12; symbols: 431
- symbol kinds: class=10, enum=6, enumerator=16, externvar=1, function=15, macro=1, member=144, namespace=1, prototype=230, struct=1, variable=6
- DynamicallyLoadedModuleNames: MainFrame, WorkspaceMenuStructure
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache, DesktopPlatform, DeveloperToolSettings, EditorFramework, EditorWidgets, Engine, ImageCore, InputCore, MediaAssets, Projects, PropertyEditor, RHI, RenderCore, Slate, SlateCore, TextureBuildUtilities, TextureCompressor, UnrealEd
- PrivateIncludePathModuleNames: Settings

### `Source/Editor/TextureEditor/Classes/TextureEditorSettings.h` (Public)


#### enum `ETextureEditorBackgrounds`  
`enum ETextureEditorBackgrounds : int`  
_L16-21_
- reflection: `UENUM()`
- desc: Enumerates background for the texture editor view port.
- L18 _public enumerator_ `TextureEditorBackground_SolidColor UMETA(DisplayName="Solid Color")`
- L19 _public enumerator_ `TextureEditorBackground_Checkered UMETA(DisplayName="Checkered")`
- L20 _public enumerator_ `TextureEditorBackground_CheckeredFill UMETA(DisplayName="Checkered (Fill)")`

#### enum `ETextureEditorSampling`  
`enum ETextureEditorSampling : int`  
_L24-28_
- reflection: `UENUM()`
- L26 _public enumerator_ `TextureEditorSampling_Default UMETA(DisplayName = "Default Sampling")`
- L27 _public enumerator_ `TextureEditorSampling_Point UMETA(DisplayName = "Nearest-Point Sampling")`

#### enum `ETextureEditorVolumeViewMode`  
`enum ETextureEditorVolumeViewMode : int`  
_L31-35_
- reflection: `UENUM()`
- L33 _public enumerator_ `TextureEditorVolumeViewMode_DepthSlices UMETA(DisplayName="Depth Slices")`
- L34 _public enumerator_ `TextureEditorVolumeViewMode_VolumeTrace UMETA(DisplayName="Trace Into Volume")`

#### enum `ETextureEditorCubemapViewMode`  
`enum ETextureEditorCubemapViewMode : int`  
_L38-42_
- reflection: `UENUM()`
- L40 _public enumerator_ `TextureEditorCubemapViewMode_2DView UMETA(DisplayName = "2D View")`
- L41 _public enumerator_ `TextureEditorCubemapViewMode_3DView UMETA(DisplayName = "3D View")`

#### enum `ETextureEditorZoomMode`  
`enum class ETextureEditorZoomMode : uint8`  
_L45-50_
- reflection: `UENUM()`
- L47 _public enumerator_ `Custom UMETA(DisplayName = "Specific Zoom Level")` — First so that any new modes added don't change serialized value
- L48 _public enumerator_ `Fit UMETA(DisplayName = "Scale Down to Fit")`
- L49 _public enumerator_ `Fill UMETA(DisplayName = "Scale to Fill")`

#### class `UTextureEditorSettings`  
`class UTextureEditorSettings : public UObject`  
_L56-117_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Implements the Editor's user settings.
- L65 _public member_ `TEnumAsByte<ETextureEditorBackgrounds> Background;` — `UPROPERTY(config)` — The type of background to draw in the texture editor view port.
- L69 _public member_ `TEnumAsByte<ETextureEditorSampling> Sampling;` — `UPROPERTY(config)` — The texture sampling mode used to render textures in the texture editor view port.
- L73 _public member_ `TEnumAsByte<ETextureEditorVolumeViewMode> VolumeViewMode;` — `UPROPERTY(config)` — The view mode when previewing volume textures.
- L77 _public member_ `TEnumAsByte<ETextureEditorCubemapViewMode> CubemapViewMode;` — `UPROPERTY(config)` — The view mode when previewing cubemap textures.
- L81 _public member_ `FColor BackgroundColor;` — `UPROPERTY(config, EditAnywhere, Category=Background)` — Background and foreground color used by Texture preview view ports.
- L85 _public member_ `FColor CheckerColorOne;` — `UPROPERTY(config, EditAnywhere, Category=Background)` — The first color of the checkered background.
- L89 _public member_ `FColor CheckerColorTwo;` — `UPROPERTY(config, EditAnywhere, Category=Background)` — The second color of the checkered background.
- L93 _public member_ `int32 CheckerSize;` — `UPROPERTY(config, EditAnywhere, Category=Background, meta=(ClampMin="2", ClampMax="4096"))` — The size of the checkered background tiles.
- L97 _public member_ `float ViewportTextScale = 1.f;` — `UPROPERTY(config, EditAnywhere, Category=Foreground, meta=(ClampMin="0.1"))` — The draw scale of the text on the viewport for infos, warnings, errors...
- L104 _public member_ `bool FitToViewport;` — `UE_DEPRECATED(4.26, "There are now more than 2 zoom modes, so this value is no longer used. Please use ZoomMode instead.")` — `UPROPERTY(config)` — Whether the texture should scale to fit the view port.
- L108 _public member_ `ETextureEditorZoomMode ZoomMode;` — `UPROPERTY(config)` — Whether the texture should scale to fit or fill the view port, or use a custom zoom level.
- L112 _public member_ `FColor TextureBorderColor;` — `UPROPERTY(config, EditAnywhere, Category=TextureBorder)` — Color to use for the texture border, if enabled.
- L116 _public member_ `bool TextureBorderEnabled;` — `UPROPERTY(config)` — If true, displays a border around the texture.

### `Source/Editor/TextureEditor/Private/Customizations/CurveLinearColorAtlasDetailsCustomization.h` (Private)


#### class `FCurveLinearColorAtlasDetails`  
`class FCurveLinearColorAtlasDetails : public FTextureDetails`  
_L14-26_
- inherits: `FTextureDetails`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _private function_ `FCurveLinearColorAtlasDetails()`
- L25 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/TextureEditor/Private/Customizations/TextureDetailsCustomization.h` (Private)


#### class `FTextureDetails`  
`class FTextureDetails : public IDetailCustomization`  
_L15-41_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _protected function_ `FTextureDetails() : bIsUsingSlider(false)`
- L27 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L29 _private prototype_ `TOptional<int32> OnGetMaxTextureSize() const;`
- L30 _private prototype_ `void OnMaxTextureSizeChanged(int32 NewValue);`
- L31 _private prototype_ `void OnMaxTextureSizeCommitted(int32 NewValue, ETextCommit::Type CommitInfo);`
- L32 _private prototype_ `void OnBeginSliderMovement();`
- L33 _private prototype_ `void OnEndSliderMovement(int32 NewValue);`
- L34 _private prototype_ `FReply OnOodleTextureSdkVersionClicked();`
- L36 _private member_ `TSharedPtr<IPropertyHandle> OodleTextureSdkVersionPropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> MaxTextureSizePropertyHandle;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> VirtualTextureStreamingPropertyHandle;`
- L39 _private member_ `TArray<TWeakObjectPtr<UObject>> TexturesBeingCustomized;`
- L40 _private member_ `bool bIsUsingSlider;`

### `Source/Editor/TextureEditor/Private/Menus/TextureEditorViewOptionsMenu.h` (Private)


#### class `FTextureEditorViewOptionsMenu`  
`class FTextureEditorViewOptionsMenu`  
_L14-74_
- desc: Static helper class for populating the "View Options" menu in the texture editor's view port.
- L23 _public function_ `static void MakeMenu(FMenuBuilder& MenuBuilder)` — Creates the menu. @param MenuBuilder The builder for the menu that owns this menu.
- L57 _protected function_ `static void GenerateBackgroundMenuContent( FMenuBuilder& MenuBuilder )` — Creates the 'Background' sub-menu. @param MenuBuilder The builder for the menu that owns this menu.
- L69 _protected function_ `static void GenerateSamplingMenuContent(FMenuBuilder& MenuBuilder)` — Creates the 'Sampling Mode' sub-menu. @param MenuBuilder The builder for the menu that owns this menu.

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "TextureEditorViewOptionsMenu"`

### `Source/Editor/TextureEditor/Private/Models/TextureEditorCommands.h` (Private)


#### class `FTextureEditorCommands`  
`class FTextureEditorCommands : public TCommands<FTextureEditorCommands>`  
_L17-87_
- inherits: `TCommands<FTextureEditorCommands>`
- desc: Holds the UI commands for the TextureEditorToolkit widget.
- L25 _public function_ `FTextureEditorCommands( ) : TCommands<FTextureEditorCommands>("TextureEditor", NSLOCTEXT("Contexts", "TextureEditor", "Texture Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Default constructor.
- L33 _public prototype_ `virtual void RegisterCommands() override;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> RedChannel;` — Toggles the red channel
- L41 _public member_ `TSharedPtr<FUICommandInfo> GreenChannel;` — Toggles the green channel
- L44 _public member_ `TSharedPtr<FUICommandInfo> BlueChannel;` — Toggles the blue channel
- L47 _public member_ `TSharedPtr<FUICommandInfo> AlphaChannel;` — Toggles the alpha channel
- L50 _public member_ `TSharedPtr<FUICommandInfo> Desaturation;` — Toggles color saturation
- L53 _public member_ `TSharedPtr<FUICommandInfo> FitToViewport;` — If enabled, the texture will be scaled down to fit within the viewport if needed
- L56 _public member_ `TSharedPtr<FUICommandInfo> FillToViewport;` — If enabled, the texture will be scaled to fill the viewport
- L59 _public member_ `TSharedPtr<FUICommandInfo> ZoomToNatural;` — If enabled, the texture will be zoomed back to its size (zoom level 100%)
- L62 _public member_ `TSharedPtr<FUICommandInfo> CheckeredBackground;` — Sets the checkered background pattern
- L65 _public member_ `TSharedPtr<FUICommandInfo> CheckeredBackgroundFill;` — Sets the checkered background pattern (filling the view port)
- L68 _public member_ `TSharedPtr<FUICommandInfo> SolidBackground;` — Sets the solid color background
- L71 _public member_ `TSharedPtr<FUICommandInfo> TextureBorder;` — If enabled, a border is drawn around the texture
- L74 _public member_ `TSharedPtr<FUICommandInfo> DefaultSampling;` — If enabled, default sampling is used for rendering the texture
- L77 _public member_ `TSharedPtr<FUICommandInfo> PointSampling;` — If enabled, nearest-point sampling is used for rendering the texture
- L80 _public member_ `TSharedPtr<FUICommandInfo> CompressNow;` — Compress the texture
- L83 _public member_ `TSharedPtr<FUICommandInfo> Reimport;` — Reimports the texture
- L86 _public member_ `TSharedPtr< FUICommandInfo > Settings;` — Open the texture editor settings.

### `Source/Editor/TextureEditor/Private/Models/TextureEditorViewportClient.h` (Private)


#### class `FTextureEditorViewportClient`  
`class FTextureEditorViewportClient : public FViewportClient , public FGCObject`  
_L16-75_
- inherits: `FViewportClient,FGCObject`
- L22 _public prototype_ `FTextureEditorViewportClient(TWeakPtr<ITextureEditorToolkit> InTextureEditor, TWeakPtr<STextureEditorViewport> InTextureEditorViewport);` — Constructor
- L26 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;` — FViewportClient interface
- L27 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;`
- L28 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& InEventArgs) override;`
- L29 _public prototype_ `virtual bool InputGesture(FViewport* Viewport, const FInputDeviceId DeviceId, EGestureEvent GestureType, EGesturePhase GesturePhase, const FVector2D& GestureDelta, bool bIsDirectionInvertedFromDevice, const uint64 Timestamp) override;`
- L30 _public function_ `virtual UWorld* GetWorld() const override`
- L31 _public prototype_ `virtual EMouseCursor::Type GetCursor(FViewport* Viewport, int32 X, int32 Y) override;`
- L34 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L35 _public function_ `virtual FString GetReferencerName() const override`
- L41 _public prototype_ `void ModifyCheckerboardTextureColors();` — Modifies the checkerboard texture's data
- L44 _public prototype_ `FText GetDisplayedResolution() const;` — Returns a string representation of the currently displayed textures resolution
- L47 _public prototype_ `float GetViewportVerticalScrollBarRatio() const;` — Returns the ratio of the size of the Texture texture to the size of the viewport
- L48 _public prototype_ `float GetViewportHorizontalScrollBarRatio() const;`
- L52 _private prototype_ `void UpdateScrollBars();` — Updates the states of the scrollbars
- L55 _private prototype_ `FVector2D GetViewportScrollBarPositions() const;` — Returns the positions of the scrollbars relative to the Texture textures
- L58 _private prototype_ `void DestroyCheckerboardTexture();` — Destroy the checkerboard texture if one exists
- L61 _private prototype_ `bool ShouldUseMousePanning(FViewport* Viewport) const;` — TRUE if right clicking and dragging for panning a texture 2D
- L65 _private member_ `TWeakPtr<ITextureEditorToolkit> TextureEditorPtr;` — Pointer back to the Texture editor tool that owns us
- L68 _private member_ `TWeakPtr<STextureEditorViewport> TextureEditorViewportPtr;` — Pointer back to the Texture viewport control that owns us
- L71 _private member_ `TObjectPtr<UTexture2D> CheckerboardTexture;` — Checkerboard texture
- L74 _private member_ `TUniquePtr<struct FTextureErrorLogger> TextureConsoleCapture;` — Output device to monitor the output log for anything relevant to us.

### `Source/Editor/TextureEditor/Private/TextureEditorConstants.h` (Private)


#### Free symbols / members of external scopes

- L8 _variable_ `const double MaxZoom = 16.0;` — MaxZoom and MinZoom should both be powers of two
- L9 _variable_ `const double MinZoom = 1.0/64;`
- L11 _variable_ `const int ZoomFactorLogSteps = 8;` — ZoomFactor is multiplicative such that an integer number of steps will give a power of two zoom (50% or 200%)
- L12 _variable_ `const double ZoomFactor = pow(2.0,1.0/ZoomFactorLogSteps);`
- L15 _variable_ `const int32 MaxExposure = 10;` — Specifies the maximum allowed exposure bias.
- L18 _variable_ `const int32 MinExposure = -10;` — Specifies the minimum allowed exposure bias.

### `Source/Editor/TextureEditor/Private/TextureEditorToolkit.h` (Private)


#### enum `ETextureChannelButton`  
`enum class ETextureChannelButton : uint8`  
_L26-32_
- L28 _public enumerator_ `Red`
- L29 _public enumerator_ `Green`
- L30 _public enumerator_ `Blue`
- L31 _public enumerator_ `Alpha`

#### class `FTextureEditorToolkit`  
`class FTextureEditorToolkit : public ITextureEditorToolkit , public FEditorUndoClient , public FGCObject`  
_L37-622_
- inherits: `ITextureEditorToolkit,FEditorUndoClient,FGCObject`
- desc: Implements an Editor toolkit for textures.
- L43 _public prototype_ `FTextureEditorToolkit();`
- L48 _public prototype_ `virtual ~FTextureEditorToolkit( );` — Destructor.
- L59 _public prototype_ `void InitTextureEditor( const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit );` — Edits the specified Texture object. @param Mode The tool kit mode. @param InitToolkitHost @param ObjectToEdit The texture object to edit.
- L63 _public prototype_ `virtual FString GetDocumentationLink( ) const override;` — FAssetEditorToolkit interface
- L64 _public prototype_ `virtual void RegisterTabSpawners( const TSharedRef<class FTabManager>& TabManager ) override;`
- L65 _public prototype_ `virtual void UnregisterTabSpawners( const TSharedRef<class FTabManager>& TabManager ) override;`
- L68 _public prototype_ `virtual void CalculateTextureDimensions(int32& OutWidth, int32& OutHeight, int32& OutDepth, int32& OutArraySize, bool bInIncludeBorderSize) const override;` — ITextureEditorToolkit interface
- L69 _public prototype_ `virtual ESimpleElementBlendMode GetColourChannelBlendMode( ) const override;`
- L70 _public prototype_ `virtual int32 GetMipLevel( ) const override;`
- L71 _public prototype_ `virtual int32 GetLayer() const override;`
- L72 _public prototype_ `virtual int32 GetSlice() const override;`
- L73 _public prototype_ `virtual int32 GetFace() const override;`
- L74 _public prototype_ `virtual UTexture* GetTexture( ) const override;`
- L75 _public prototype_ `virtual bool HasValidTextureResource( ) const override;`
- L76 _public prototype_ `virtual bool GetUseSpecifiedMip( ) const override;`
- L77 _public prototype_ `virtual bool GetUseSpecifiedSlice() const override;`
- L78 _public prototype_ `virtual bool GetUseSpecifiedFace() const override;`
- L79 _public prototype_ `virtual double GetCustomZoomLevel( ) const override;`
- L80 _public prototype_ `virtual void SetCustomZoomLevel(double ZoomValue) override;`
- L81 _public prototype_ `virtual void PopulateQuickInfo( ) override;`
- L82 _public prototype_ `virtual void SetZoomMode( const ETextureEditorZoomMode ZoomMode ) override;`
- L83 _public prototype_ `virtual ETextureEditorZoomMode GetZoomMode() const override;`
- L84 _public prototype_ `virtual double CalculateDisplayedZoomLevel() const override;`
- L85 _public prototype_ `virtual void ZoomIn( ) override;`
- L86 _public prototype_ `virtual void ZoomOut( ) override;`
- L87 _public prototype_ `virtual float GetVolumeOpacity( ) const override;`
- L88 _public prototype_ `virtual void SetVolumeOpacity( float VolumeOpacity ) override;`
- L89 _public prototype_ `virtual ETextureEditorVolumeViewMode GetVolumeViewMode() const override;`
- L90 _public prototype_ `virtual void SetVolumeViewMode(const ETextureEditorVolumeViewMode VolumeViewMode) override;`
- L91 _public prototype_ `virtual ETextureEditorCubemapViewMode GetCubemapViewMode() const override;`
- L92 _public prototype_ `virtual void SetCubemapViewMode(const ETextureEditorCubemapViewMode CubemapViewMode) override;`
- L93 _public prototype_ `virtual bool IsUsingOrientation() const override;`
- L94 _public prototype_ `virtual const FRotator& GetOrientation() const override;`
- L95 _public prototype_ `virtual void SetOrientation(const FRotator& InOrientation) override;`
- L96 _public prototype_ `virtual void ResetOrientation() override;`
- L97 _public prototype_ `virtual ETextureEditorSampling GetSampling() const override;`
- L98 _public function_ `virtual int32 GetExposureBias() const override`
- L102 _public function_ `virtual EVisibility GetVisibilityWhileAssetCompiling() const override`
- L108 _public prototype_ `virtual FText GetBaseToolkitName( ) const override;` — IToolkit interface
- L109 _public prototype_ `virtual FName GetToolkitFName( ) const override;`
- L110 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale( ) const override;`
- L111 _public prototype_ `virtual FString GetWorldCentricTabPrefix( ) const override;`
- L114 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L115 _public function_ `virtual FString GetReferencerName() const override`
- L122 _protected prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L123 _protected prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L128 _protected prototype_ `void BindCommands( );` — Binds the UI commands to delegates.
- L135 _protected prototype_ `TSharedRef<SWidget> BuildTexturePropertiesWidget( );` — Creates the texture properties details widget. @return The widget.
- L140 _protected prototype_ `void CreateInternalWidgets( );` — Creates all internal widgets for the tabs to point at.
- L145 _protected prototype_ `void ExtendToolBar( );` — Builds the toolbar widget for the Texture editor.
- L147 _protected prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L153 _protected prototype_ `TOptional<int32> GetMaxMipLevel( ) const;` — Gets the highest mip map level that this texture supports. @return Mip map level.
- L158 _protected prototype_ `int32 GetNumMips() const;` — Gets the number of mips that this texture supports.
- L163 _protected prototype_ `EPixelFormat GetPixelFormat() const;` — Gets the texture format of this texture.
- L168 _protected prototype_ `TOptional<int32> GetMaxLayer() const;` — Gets the highest layer index for this texture.
- L173 _protected prototype_ `TOptional<int32> GetMaxSlice() const;` — Gets the highest slice index for this texture.
- L178 _protected prototype_ `bool IsCubeTexture( ) const;` — Checks whether the texture being edited is a cube map texture.
- L183 _protected prototype_ `bool IsVolumeTexture() const;` — Checks whether the texture being edited is a volume texture.
- L188 _protected prototype_ `bool Is2DArrayTexture() const;` — Checks whether the texture being edited is a texture 2D array.
- L193 _protected prototype_ `bool IsArrayTexture() const;` — Checks whether the texture being edited is a texture array (Cube or 2D).
- L195 _protected prototype_ `TSharedRef<SWidget> OnGenerateMipMapLevelMenu();`
- L196 _protected prototype_ `TSharedRef<SWidget> OnGenerateSettingsMenu();`
- L198 _private prototype_ `bool IsChannelButtonEnabled(ETextureChannelButton Button) const;`
- L199 _private prototype_ `FSlateColor GetChannelButtonBackgroundColor(ETextureChannelButton Button) const;`
- L200 _private prototype_ `FSlateColor GetChannelButtonForegroundColor(ETextureChannelButton Button) const;`
- L201 _private prototype_ `void OnChannelButtonCheckStateChanged(ETextureChannelButton Button);`
- L202 _private prototype_ `ECheckBoxState OnGetChannelButtonCheckState(ETextureChannelButton Button) const;`
- L205 _private prototype_ `void HandleCheckeredBackgroundActionExecute( ETextureEditorBackgrounds Background );` — Callback for toggling the Checkered Background action.
- L208 _private prototype_ `bool HandleCheckeredBackgroundActionIsChecked( ETextureEditorBackgrounds Background );` — Callback for getting the checked state of the Checkered Background action.
- L211 _private prototype_ `void HandleSamplingActionExecute(ETextureEditorSampling Sampling);` — Callback for toggling the Sampling action.
- L214 _private prototype_ `bool HandleSamplingActionIsChecked(ETextureEditorSampling Sampling);` — Callback for getting the checked state of the Sampling action.
- L217 _private prototype_ `void HandleVolumeViewModeActionExecute( ETextureEditorVolumeViewMode InViewMode );` — Callback for toggling the volume view action.
- L220 _private prototype_ `bool HandleVolumeViewModeActionIsChecked( ETextureEditorVolumeViewMode InViewMode );` — Callback for getting the checked state of the volume view action.
- L223 _private prototype_ `void HandleCubemapViewModeActionExecute(ETextureEditorCubemapViewMode InViewMode);` — Callback for toggling the cubemap view action.
- L226 _private prototype_ `bool HandleCubemapViewModeActionIsChecked(ETextureEditorCubemapViewMode InViewMode);` — Callback for getting the checked state of the cubemap view action.
- L229 _private prototype_ `void HandleCompressNowActionExecute( );` — Callback for toggling the Compress Now action.
- L232 _private prototype_ `bool HandleCompressNowActionCanExecute( ) const;` — Callback for getting the checked state of the Compress Now action.
- L235 _private prototype_ `void HandleFitToViewportActionExecute( );` — Callback for executing the Fit To Viewport action.
- L238 _private prototype_ `void HandleFillToViewportActionExecute( );` — Callback for executing the Fill To Viewport action.
- L240 _private prototype_ `virtual bool IsFitToViewport() const;`
- L241 _private prototype_ `virtual bool IsFillToViewport() const;`
- L244 _private prototype_ `void HandleZoomToNaturalActionExecute( );` — Callback for executing the Fit To 100% action.
- L247 _private prototype_ `void HandleMipLevelCheckBoxCheckedStateChanged( ECheckBoxState InNewState );` — Callback for changing the checked state of the MipMap check box.
- L250 _private prototype_ `ECheckBoxState HandleMipLevelCheckBoxIsChecked( ) const;` — Callback for getting the checked state of the MipMap check box.
- L253 _private prototype_ `bool HandleMipLevelCheckBoxIsEnabled( ) const;` — Callback for determining whether the MipMap check box is enabled.
- L256 _private prototype_ `void HandleMipLevelChanged( int32 NewMipLevel );` — Callback for changing the value of the mip map level entry box.
- L259 _private prototype_ `TOptional<int32> HandleMipLevelEntryBoxValue( ) const;` — Callback for getting the value of the mip map level entry box.
- L261 _private prototype_ `FReply HandleMipMapMinusButtonClicked();`
- L263 _private prototype_ `FReply HandleMipMapPlusButtonClicked();`
- L265 _private prototype_ `void HandleLayerEntryBoxChanged(int32 NewMipLevel);`
- L266 _private prototype_ `TOptional<int32> HandleLayerEntryBoxValue() const;`
- L268 _private prototype_ `bool HasLayers() const;`
- L271 _private prototype_ `bool HasSlices() const;` — Returns true if the current texture supports slice selection.
- L274 _private prototype_ `int32 GetNumSlices() const;` — Gets the number of slices that can be selected for this texture.
- L277 _private prototype_ `bool HandleSliceCheckBoxIsEnabled() const;` — Callback for determining whether the slice check box is enabled.
- L280 _private prototype_ `ECheckBoxState HandleSliceCheckBoxIsChecked() const;` — Callback for getting the checked state of the slice check box.
- L283 _private prototype_ `void HandleSliceCheckBoxCheckedStateChanged(ECheckBoxState InNewState);` — Callback for changing the checked state of the slice check box.
- L286 _private prototype_ `TOptional<int32> HandleSliceEntryBoxValue() const;` — Callback for getting the value of the slice index entry box.
- L289 _private prototype_ `void HandleSliceEntryBoxChanged(int32 Slice);` — Callback for changing the value of the slice index entry box.
- L292 _private prototype_ `ECheckBoxState HandleFaceCheckBoxIsChecked() const;` — Callback for getting the checked state of the face check box.
- L295 _private prototype_ `void HandleFaceCheckBoxCheckedStateChanged(ECheckBoxState InNewState);` — Callback for changing the checked state of the face check box.
- L298 _private prototype_ `TOptional<int32> HandleFaceEntryBoxValue() const;` — Callback for getting the value of the face index entry box.
- L301 _private prototype_ `void HandleFaceEntryBoxChanged(int32 Face);` — Callback for changing the value of the face index entry box.
- L304 _private prototype_ `ECheckBoxState HandleView3DCheckBoxIsChecked() const;` — Callback for getting the checked state of the 3D View check box.
- L307 _private prototype_ `void HandleView3DCheckBoxCheckedStateChanged(ECheckBoxState InNewState);` — Callback for changing the checked state of the 3D View check box.
- L310 _private prototype_ `bool HandleReimportActionCanExecute( ) const;` — Callback for determining whether the Reimport action can execute.
- L313 _private prototype_ `void HandleReimportActionExecute( );` — Callback for executing the Reimport action.
- L316 _private prototype_ `void HandleReimportManagerPostReimport( UObject* InObject, bool bSuccess );` — Callback that is executed after the reimport manager reimported an asset.
- L319 _private prototype_ `void HandleReimportManagerPreReimport( UObject* InObject );` — Callback that is executed before the reimport manager reimported an asset.
- L322 _private prototype_ `void HandleAssetPostImport(UFactory* InFactory, UObject* InObject);` — Callback that is executed once an asset is imported
- L325 _private prototype_ `void HandleDesaturationChannelActionExecute( );` — Callback for toggling the Desaturation channel action.
- L328 _private prototype_ `bool HandleDesaturationChannelActionIsChecked( ) const;` — Callback for getting the checked state of the Desaturation channel action.
- L331 _private prototype_ `void HandleSettingsActionExecute( );` — Callback for determining whether the Settings action can execute.
- L334 _private prototype_ `TSharedRef<SDockTab> HandleTabSpawnerSpawnProperties(const FSpawnTabArgs& Args);` — Tab spawner callbacks
- L335 _private prototype_ `TSharedRef<SDockTab> HandleTabSpawnerSpawnViewport( const FSpawnTabArgs& Args );`
- L336 _private prototype_ `TSharedRef<SDockTab> HandleTabSpawnerSpawnOodle(const FSpawnTabArgs& Args);`
- L337 _private prototype_ `TSharedRef<SDockTab> HandleTabSpawnerSpawnPlatforms(const FSpawnTabArgs& Args);`
- L340 _private prototype_ `void HandleTextureBorderActionExecute( );` — Callback for toggling the Texture Border action.
- L343 _private prototype_ `bool HandleTextureBorderActionIsChecked( ) const;` — Callback for getting the checked state of the Texture Border action.
- L346 _private prototype_ `EVisibility HandleExposureBiasWidgetVisibility() const;` — Callback for getting the visibility of the exposure bias widget.
- L349 _private prototype_ `TOptional<int32> HandleExposureBiasBoxValue() const;` — Callback for getting the exposure bias.
- L352 _private prototype_ `void HandleExposureBiasBoxValueChanged(int32 NewExposure);` — Callback for changing the exposure bias.
- L355 _private prototype_ `void HandleOpacitySliderChanged(float NewValue);` — Callback for changes in the zoom slider.
- L358 _private prototype_ `TOptional<float> HandleOpacitySliderValue() const;` — Callback for getting the zoom slider's value.
- L361 _private prototype_ `void HandleZoomMenuEntryClicked(double ZoomValue);` — Callback for clicking an item in the 'Zoom' menu.
- L364 _private prototype_ `void HandleZoomMenuFillClicked();` — Callback for clicking the 'Fill' item in the 'Zoom' menu.
- L367 _private prototype_ `bool IsZoomMenuFillChecked() const;` — Callback for setting the checked state of the 'Fill' item in the 'Zoom' menu.
- L370 _private prototype_ `void HandleZoomMenuFitClicked();` — Callback for clicking the 'Fit' item in the 'Zoom' menu.
- L373 _private prototype_ `bool IsZoomMenuFitChecked() const;` — Callback for setting the checked state of the 'Fit' item in the 'Zoom' menu.
- L376 _private prototype_ `FText HandleZoomPercentageText() const;` — Callback for getting the zoom percentage text.
- L379 _private prototype_ `void HandleZoomSliderChanged(float NewValue);` — Callback for changes in the zoom slider.
- L382 _private prototype_ `float HandleZoomSliderValue() const;` — Callback for getting the zoom slider's value.
- L385 _private prototype_ `FReply HandleViewOptionsMenuButtonClicked();` — Callback for clicking the View Options menu button.
- L387 _private prototype_ `TSharedRef<SWidget> MakeChannelControlWidget();`
- L388 _private prototype_ `TSharedRef<SWidget> MakeLODControlWidget();`
- L389 _private prototype_ `TSharedRef<SWidget> MakeLayerControlWidget();`
- L390 _private prototype_ `TSharedRef<SWidget> MakeSliceControlWidget();`
- L391 _private prototype_ `TSharedRef<SWidget> MakeFaceControlWidget();`
- L392 _private prototype_ `TSharedRef<SWidget> MakeExposureContolWidget();`
- L393 _private prototype_ `TSharedRef<SWidget> MakeOpacityControlWidget();`
- L394 _private prototype_ `TSharedRef<SWidget> MakeZoomControlWidget();`
- L395 _private prototype_ `TSharedRef<SWidget> MakeView3DControlWidget();`
- L396 _private prototype_ `TSharedRef<SWidget> MakePlatformSelectorWidget();`
- L400 _private member_ `TObjectPtr<UTexture> Texture;` — The Texture asset being inspected
- L403 _private member_ `TSharedPtr<STextureEditorViewport> TextureViewport;` — Viewport
- L406 _private member_ `TSharedPtr<SVerticalBox> OodleTabContainer;` — Oodle tab
- L407 _private member_ `TSharedPtr<SVerticalBox> PlatformsTabContainer;`
- L410 _private member_ `TSharedPtr<SVerticalBox> TextureProperties;` — Properties tab
- L413 _private member_ `TSharedPtr<class IDetailsView> TexturePropertiesWidget;` — Properties tree view
- L416 _private member_ `TSharedPtr<STextBlock> ImportedText;` — Quick info text blocks
- L417 _private member_ `TSharedPtr<STextBlock> CurrentText;`
- L418 _private member_ `TSharedPtr<STextBlock> MaxInGameText;`
- L419 _private member_ `TSharedPtr<STextBlock> SizeText;`
- L420 _private member_ `TSharedPtr<STextBlock> MethodText;`
- L421 _private member_ `TSharedPtr<STextBlock> FormatText;`
- L422 _private member_ `TSharedPtr<STextBlock> LODBiasText;`
- L423 _private member_ `TSharedPtr<STextBlock> HasAlphaChannelText;`
- L424 _private member_ `TSharedPtr<STextBlock> SourceMipsAlphaDetectedText;`
- L425 _private member_ `TSharedPtr<SButton> DetectSourceAlphaButton;`
- L426 _private member_ `TSharedPtr<STextBlock> NumMipsText;`
- L427 _private member_ `TSharedPtr<STextBlock> MipLevelTextBlock;`
- L428 _private member_ `TSharedPtr<STextBlock> EncodeSpeedText;`
- L429 _private member_ `TSharedPtr<STextBlock> SceneCaptureSizeText;`
- L430 _private member_ `TSharedPtr<STextBlock> SceneCaptureNameText;`
- L433 _private member_ `TSharedPtr<STextBlock> OodleRDOText;` — oodle details text blocks.
- L434 _private member_ `TSharedPtr<STextBlock> OodleEffortText;`
- L435 _private member_ `TSharedPtr<STextBlock> OodleTilingText;`
- L436 _private member_ `TSharedPtr<STextBlock> OodleRDOSourceText;`
- L437 _private member_ `TSharedPtr<STextBlock> OodleEncoderText;`
- L438 _private member_ `TSharedPtr<STextBlock> OodleEncodeSpeedText;`
- L441 _private member_ `TSharedPtr<STextBlock> OodleRDOEnabledLabel;` — oodle details labels
- L442 _private member_ `TSharedPtr<STextBlock> OodleRDOSourceLabel;`
- L443 _private member_ `TSharedPtr<STextBlock> OodleEffortLabel;`
- L444 _private member_ `TSharedPtr<STextBlock> OodleTilingLabel;`
- L447 _private member_ `TSharedPtr<SMenuAnchor> ViewOptionsMenuAnchor;` — Holds the anchor for the view options menu.
- L450 _private member_ `bool bIsRedChannel;` — If true, displays the red channel
- L453 _private member_ `bool bIsGreenChannel;` — If true, displays the green channel
- L456 _private member_ `bool bIsBlueChannel;` — If true, displays the blue channel
- L459 _private member_ `bool bIsAlphaChannel;` — If true, displays the alpha channel
- L462 _private member_ `bool bIsDesaturation;` — If true, desaturates the texture
- L465 _private member_ `int32 PreviewEffectiveTextureWidth;` — The maximum width/height at which the texture will render in the preview window
- L466 _private member_ `int32 PreviewEffectiveTextureHeight;`
- L469 _private member_ `int32 SpecifiedMipLevel;` — Which mip level should be shown
- L472 _private member_ `bool bUseSpecifiedMipLevel;` — When true, the specified mip value is used. Top mip is used when false.
- L475 _private member_ `int32 SpecifiedLayer;` — Which layer should be shown
- L478 _private member_ `int32 SpecifiedSlice;` — Which slice should be shown
- L481 _private member_ `bool bUseSpecifiedSlice;` — When true, the specified slice index value is used, otherwise the value of -1 is used.
- L484 _private member_ `int32 SpecifiedFace;` — Which cubemap face should be shown
- L487 _private member_ `bool bUseSpecifiedFace;` — When true, the specified cubemap face index value is used, otherwise the value of -1 is used.
- L490 _private member_ `double Zoom;` — The texture's zoom factor.
- L492 _private member_ `FName ViewingPlatform;` — NAME_None if viewing editor.
- L495 _private member_ `int32 ExposureBias;` — Which exposure level should be used, in FStop e.g. 0:original, -1:half as bright, 1:2x as bright, 2:4x as bright.
- L498 _private member_ `ETextureEditorZoomMode ZoomMode;` — This toolkit's current zoom mode
- L501 _private member_ `float VolumeOpacity;` — For volume texture, defines an opacity to see through the volume when tracing.
- L504 _private member_ `ETextureEditorVolumeViewMode VolumeViewMode;` — This toolkit's current volume view mode
- L507 _private member_ `ETextureEditorCubemapViewMode CubemapViewMode;` — This toolkit's current cubemap view mode
- L510 _private member_ `ETextureEditorSampling Sampling;` — This toolkit's current sampling mode
- L513 _private member_ `FRotator Orientation;` — Orientation of the texture in 3d when using "3D View" mode
- L515 _private member_ `bool bIsVolumeTexture;`
- L517 _private member_ `TArray<TSharedPtr<FString>> AvailablePlatforms;`
- L518 _private member_ `TArray<FName> AvailablePlatformNames;`
- L548 _private member_ `TSharedPtr<SListView<TSharedPtr<FPlatformTextureFormats>>> PlatformTextureFormatsWidget;`
- L549 _private member_ `TArray<TSharedPtr<FPlatformTextureFormats>> PlatformTextureFormatList;`
- L550 _private prototype_ `TSharedRef<ITableRow> MakePlatformTextureFormatWidget(TSharedPtr<FPlatformTextureFormats> PlatformTextureFormat, const TSharedRef<STableViewBase>& OwnerTable);`
- L552 _private member_ `TMap<FName, TPair<TSharedPtr<STextBlock>, TSharedPtr<STextBlock>>> PlatformFormatDetails;`
- L555 _private member_ `TSharedPtr<class SCheckBox> OodleOverrideCheck;` — Objects and callbacks for the custom encoding settings checkbox
- L556 _private prototype_ `void OnUseEditorOodleSettingsChanged(ECheckBoxState NewState);`
- L557 _private prototype_ `ECheckBoxState UseEditorOodleSettingsChecked() const;`
- L559 _private prototype_ `FReply DetectSourceAlphaButton_Clicked();`
- L560 _private prototype_ `bool CanPlatformPreview() const;`
- L563 _private prototype_ `bool EditorOodleSettingsEnabled() const;` — callback for enabling custom encoding sub-controls
- L566 _private prototype_ `int32 GetEditorOodleSettingsEffort() const;` — accessor callbacks for custom encoding sub controls
- L567 _private prototype_ `void EditorOodleSettingsEffortChanged(int32 NewValue, ESelectInfo::Type SelectionType);`
- L568 _private prototype_ `TOptional<int32> GetEditorOodleSettingsRDO() const;`
- L569 _private prototype_ `void EditorOodleSettingsRDOCommitted(int32 NewValue, ETextCommit::Type CommitType);`
- L570 _private prototype_ `int32 GetEditorOodleSettingsTiling() const;`
- L571 _private prototype_ `void EditorOodleSettingsTilingChanged(int32 NewValue, ESelectInfo::Type SelectionType);`
- L574 _private member_ `TVariant<FString, UE::DerivedData::FCacheKeyProxy> OodleCompressedPreviewDDCKey;` — This is the key we have compressed for oodle preview, so we can catch changes.
- L580 _private member_ `bool bEstimateCompressionEnabled = false;` — -- Start on disc estimation controls/fns
- L581 _private function_ `bool EstimateCompressionEnabled() const`
- L584 _private member_ `FOodleDataCompression::ECompressionLevel OodleCompressionLevel;` — Parsed from packaging settings.
- L585 _private member_ `FOodleDataCompression::ECompressor OodleCompressor;`
- L586 _private member_ `uint32 CompressionBlockSize;`
- L589 _private member_ `TFuture<TTuple<uint64, uint64>> OutstandingEstimation;` — Valid if we've kicked off an estimation task and are waiting for the result.
- L592 _private member_ `TSharedPtr<class SCheckBox> OodleEstimateCheck;` — Controls
- L593 _private prototype_ `void OnEstimateCompressionChanged(ECheckBoxState NewState);`
- L594 _private prototype_ `ECheckBoxState EstimateCompressionChecked() const;`
- L596 _private member_ `TSharedPtr<STextBlock> OodleCompressorUsed;`
- L597 _private member_ `TSharedPtr<STextBlock> OodleLevelUsed;`
- L598 _private member_ `TSharedPtr<STextBlock> OodleCompressionBlockUsed;`
- L599 _private member_ `TSharedPtr<STextBlock> OodleEstimateRaw;`
- L600 _private member_ `TSharedPtr<STextBlock> OodleEstimateCompressed;`
- L603 _private member_ `TArray< TSharedPtr< FString > > PackagingSettingsNames;` — For the packaging settings combo box
- L604 _private prototype_ `void PackagingSettingsChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L609 _private prototype_ `void PostTextureRecode();`
- L613 _public member_ `TSharedPtr<class FTextureEditorCustomEncode> CustomEncoding;` — These are on a separate object so then engine can share the type without needing our module.
- L618 _private member_ `static const FName ViewportTabId;` — Tab names
- L619 _private member_ `static const FName PropertiesTabId;`
- L620 _private member_ `static const FName OodleTabId;`
- L621 _private member_ `static const FName PlatformsTabId;`

#### struct `FTextureEditorToolkit::FPlatformTextureFormats`  
`struct FPlatformTextureFormats`  
_L521-545_
- L523 _public member_ `FName PlatformName;`
- L524 _public member_ `FName TextureFormatName;`
- L529 _public member_ `EPixelFormat PixelFormat_AlphaTrue = PF_Unknown;` — Pixel formats for whether we detected alpha in the texture source. Only matters for Auto* texture formats. If we don't know the texture source alpha information we show both.
- L530 _public member_ `EPixelFormat PixelFormat_AlphaFalse = PF_Unknown;`
- L531 _public member_ `bool bKnowAlphaTransparency = false;`
- L532 _public member_ `bool bHasTransparentAlpha = false;`
- L533 _public member_ `bool bIsVirtual = false;`
- L534 _public member_ `int32 Width = 0;`
- L535 _public member_ `int32 Height = 0;`
- L536 _public member_ `int32 NumMips_TotalAfterLOD = 0;`
- L537 _public member_ `int32 NumMips_Optional = 0;`
- L538 _public member_ `int32 NumMips_Streaming = 0;`
- L539 _public member_ `int32 NumMips_Tail = 0;`
- L540 _public member_ `int8 LODBias = 0;`
- L541 _public member_ `uint64 MipChainSizeInBytes_Streaming = 0;`
- L542 _public member_ `uint64 MipChainSizeInBytes_Inline = 0;`
- L543 _public member_ `uint64 MipChainSizeInBytes_Optional = 0;`
- L544 _public member_ `TArray<uint64, TInlineAllocator<MAX_TEXTURE_MIP_COUNT>> MipSizesInBytes;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace FOodleDataCompression`

### `Source/Editor/TextureEditor/Private/Widgets/STextureEditorViewport.h` (Private)


#### class `STextureEditorViewport`  
`class STextureEditorViewport : public SCompoundWidget`  
_L19-104_
- inherits: `SCompoundWidget`
- desc: Implements the texture editor's view port.
- L24 _public function_ `SLATE_BEGIN_ARGS(STextureEditorViewport)`
- L25 _public prototype_ `SLATE_END_ARGS() void AddReferencedObjects( FReferenceCollector& Collector );`
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<ITextureEditorToolkit>& InToolkit );` — Constructs the widget. @param InArgs The construction arguments.
- L41 _public prototype_ `void ModifyCheckerboardTextureColors( );` — Modifies the checkerboard texture's data.
- L45 _public prototype_ `void EnableRendering();` — Enable viewport rendering
- L48 _public prototype_ `void DisableRendering();` — Disable viewport rendering
- L50 _public prototype_ `TSharedPtr<FSceneViewport> GetViewport( ) const;`
- L51 _public prototype_ `TSharedPtr<SViewport> GetViewportWidget( ) const;`
- L52 _public prototype_ `TSharedPtr<SScrollBar> GetVerticalScrollBar( ) const;`
- L53 _public prototype_ `TSharedPtr<SScrollBar> GetHorizontalScrollBar( ) const;`
- L59 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L68 _protected prototype_ `FText GetDisplayedResolution() const;` — Gets the displayed textures resolution as a string. @return Texture resolution string.
- L73 _private prototype_ `void HandleHorizontalScrollBarScrolled( float InScrollOffsetFraction );` — Callback for the horizontal scroll bar.
- L76 _private prototype_ `EVisibility HandleHorizontalScrollBarVisibility( ) const;` — Callback for getting the visibility of the horizontal scroll bar.
- L79 _private prototype_ `void HandleVerticalScrollBarScrolled( float InScrollOffsetFraction );` — Callback for the vertical scroll bar.
- L82 _private prototype_ `EVisibility HandleVerticalScrollBarVisibility( ) const;` — Callback for getting the visibility of the horizontal scroll bar.
- L85 _private member_ `TWeakPtr<ITextureEditorToolkit> ToolkitPtr;` — Pointer back to the Texture editor tool that owns us.
- L88 _private member_ `TSharedPtr<class FTextureEditorViewportClient> ViewportClient;` — Level viewport client.
- L91 _private member_ `TSharedPtr<FSceneViewport> Viewport;` — Slate viewport for rendering and IO.
- L94 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — Viewport widget.
- L97 _private member_ `TSharedPtr<SScrollBar> TextureViewportVerticalScrollBar;` — Vertical scrollbar.
- L100 _private member_ `TSharedPtr<SScrollBar> TextureViewportHorizontalScrollBar;` — Horizontal scrollbar.
- L103 _private member_ `bool bIsRenderingEnabled = true;` — Is rendering currently enabled? (disabled when reimporting a texture)

### `Source/Editor/TextureEditor/Public/Interfaces/ITextureEditorModule.h` (Public)


#### class `ITextureEditorModule`  
`class ITextureEditorModule : public IModuleInterface , public IHasMenuExtensibility , public IHasToolBarExtensibility`  
_L15-30_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Interface for texture editor modules.
- L29 _public prototype_ `virtual TSharedRef<ITextureEditorToolkit> CreateTextureEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UTexture* Texture ) = 0;` — Creates a new Texture editor. @param Mode @param InitToolkitHost @param Texture

### `Source/Editor/TextureEditor/Public/Interfaces/ITextureEditorToolkit.h` (Public)


#### class `ITextureEditorToolkit`  
`class ITextureEditorToolkit : public FAssetEditorToolkit`  
_L15-86_
- inherits: `FAssetEditorToolkit`
- desc: Interface for texture editor tool kits.
- L21 _public prototype_ `virtual UTexture* GetTexture() const = 0;` — Returns the Texture asset being inspected by the Texture editor
- L24 _public prototype_ `virtual bool HasValidTextureResource() const = 0;` — Returns if the Texture asset being inspected has a valid texture resource
- L27 _public prototype_ `virtual void PopulateQuickInfo() = 0;` — Refreshes the quick info panel
- L30 _public prototype_ `virtual void CalculateTextureDimensions(int32& OutWidth, int32& OutHeight, int32& OutDepth, int32& OutArraySize, bool bInIncludeBorderSize) const = 0;` — Calculates the display size of the texture, optionally including the size of the displayed texture border
- L33 _public prototype_ `virtual int32 GetMipLevel() const = 0;` — Accessors
- L34 _public prototype_ `virtual int32 GetLayer() const = 0;`
- L35 _public prototype_ `virtual int32 GetSlice() const = 0;`
- L36 _public prototype_ `virtual int32 GetFace() const = 0;`
- L37 _public prototype_ `virtual ESimpleElementBlendMode GetColourChannelBlendMode() const = 0;`
- L38 _public prototype_ `virtual bool GetUseSpecifiedMip() const = 0;`
- L39 _public prototype_ `virtual bool GetUseSpecifiedSlice() const = 0;`
- L40 _public prototype_ `virtual bool GetUseSpecifiedFace() const = 0;`
- L41 _public prototype_ `virtual double GetCustomZoomLevel() const = 0;`
- L42 _public prototype_ `virtual void SetCustomZoomLevel( double ZoomValue ) = 0;`
- L43 _public prototype_ `virtual void ZoomIn() = 0;`
- L44 _public prototype_ `virtual void ZoomOut() = 0;`
- L45 _public prototype_ `virtual ETextureEditorZoomMode GetZoomMode() const = 0;`
- L46 _public prototype_ `virtual void SetZoomMode( const ETextureEditorZoomMode ZoomMode ) = 0;`
- L47 _public prototype_ `virtual double CalculateDisplayedZoomLevel() const = 0;`
- L48 _public prototype_ `virtual float GetVolumeOpacity( ) const = 0;`
- L49 _public prototype_ `virtual void SetVolumeOpacity( float VolumeOpacity ) = 0;`
- L50 _public prototype_ `virtual ETextureEditorVolumeViewMode GetVolumeViewMode() const = 0;`
- L51 _public prototype_ `virtual void SetVolumeViewMode(const ETextureEditorVolumeViewMode VolumeViewMode) = 0;`
- L52 _public prototype_ `virtual ETextureEditorCubemapViewMode GetCubemapViewMode() const = 0;`
- L53 _public prototype_ `virtual void SetCubemapViewMode(const ETextureEditorCubemapViewMode CubemapViewMode) = 0;`
- L54 _public prototype_ `virtual bool IsUsingOrientation() const = 0;`
- L55 _public prototype_ `virtual const FRotator& GetOrientation() const = 0;`
- L56 _public prototype_ `virtual void SetOrientation(const FRotator& InOrientation) = 0;`
- L57 _public prototype_ `virtual void ResetOrientation() = 0;`
- L58 _public prototype_ `virtual ETextureEditorSampling GetSampling() const = 0;`
- L59 _public prototype_ `virtual int32 GetExposureBias() const = 0;`
- L60 _public prototype_ `virtual bool IsVolumeTexture() const = 0;`
- L67 _public function_ `void ToggleFitToViewport()` — `UE_DEPRECATED(4.26, "There are now commands for switching to individual zoom modes rather than toggling. Please use SetZoomMode() instead.")` — Toggles the fit-to-viewport mode. If already on, will return to the last custom zoom level.
- L82 _public function_ `bool IsCurrentZoomMode(ETextureEditorZoomMode ZoomMode) const` — Returns true if this is the current zoom mode. Useful for Slate bindings.

### `Source/Editor/TextureEditor/Public/TextureEditor.h` (Public)


#### Free symbols / members of external scopes

- L17 _externvar_ `extern const FName TextureEditorAppIdentifier;`
