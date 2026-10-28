# Plugins / CameraCalibrationEditor

- module root: `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor`
- headers: 53; symbols: 1410
- symbol kinds: class=61, delegate=8, enum=15, enumerator=47, function=105, macro=1, member=480, namespace=5, prototype=646, struct=35, typedef=7
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, CameraCalibrationCore, CinematicCamera, ContentBrowserData, Core, CoreUObject, CurveEditor, DesktopPlatform, DeveloperSettings, EditorStyle, EditorWidgets, Engine, ImageCore, InputCore, Json, JsonUtilities, LensComponent, MediaAssets, MediaFrameworkUtilities, MediaProfile, OpenCV, OpenCVHelper, PlacementMode, PropertyEditor, RenderCore, SequencerWidgets, Settings, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetDefinition_LensFile.h` (Private)


#### class `UAssetDefinition_LensFile`  
`class UAssetDefinition_LensFile : public UAssetDefinitionDefault`  
_L10-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _public function_ `virtual bool CanImport() const override`
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L21 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/CameraCalibrationCommands.h` (Private)


#### class `FCameraCalibrationCommands`  
`class FCameraCalibrationCommands : public TCommands<FCameraCalibrationCommands>`  
_L13-32_
- inherits: `TCommands<FCameraCalibrationCommands>`
- L17 _public function_ `FCameraCalibrationCommands() : TCommands<FCameraCalibrationCommands>(TEXT("CameraCalibration"), NSLOCTEXT("CameraCalibrationCommands", "CameraCalibrationCommandsEdit", "CameraCalibration"), NAME_None, FCameraCalibrationEditorStyle::Get().GetStyleSetName())`
- L24 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L27 _public member_ `TSharedPtr<FUICommandInfo> Edit;` — Edit the current lens distortion.
- L30 _public member_ `TSharedPtr<FUICommandInfo> ShowMediaPlaybackControls;` — Show the media playback control buttons.

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/CameraCalibrationCurveEditor.h` (Private)


#### class `FCameraCalibrationCurveEditor`  
`class FCameraCalibrationCurveEditor : public FCurveEditor`  
_L10-18_
- inherits: `FCurveEditor`
- desc: Custom Curve editor child class
- L13 _public prototype_ `FCameraCalibrationCurveEditor();`
- L17 _public member_ `FSimpleDelegate OnAddDataPointDelegate;` — Delegate instance when new Data Point added

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/CameraCalibrationEditorCommon.h` (Private)


#### struct `FDistortionInfoContainer`  
`struct FDistortionInfoContainer`  
_L15-24_
- reflection: `USTRUCT()`
- desc: Container of distortion data to use instanced customization to show parameter struct defined by the model
- L23 _public member_ `FDistortionInfo DistortionInfo;` — `UPROPERTY(EditAnywhere, Category = "Distortion", meta = (ShowOnlyInnerProperties))` — Distortion parameters

#### struct `FCachedFIZData`  
`struct FCachedFIZData`  
_L27-36_
- desc: Holds the last FIZ data that was evaluated
- L29 _public member_ `TOptional<float> RawFocus;`
- L30 _public member_ `TOptional<float> RawIris;`
- L31 _public member_ `TOptional<float> RawZoom;`
- L33 _public member_ `TOptional<float> EvaluatedFocus;`
- L34 _public member_ `TOptional<float> EvaluatedIris;`
- L35 _public member_ `TOptional<float> EvaluatedZoom;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/CameraCalibrationStepsController.h` (Private)


#### enum `EOverlayPassType`  
`enum class EOverlayPassType : uint8`  
_L33-37_
- desc: Enumeration of overlay passes used to indicate which overlay pass to interact with
- L35 _public enumerator_ `ToolOverlay = 0`
- L36 _public enumerator_ `UserOverlay = 1`

#### enum `ESimulcamViewportPortion`  
`enum class ESimulcamViewportPortion : uint8`  
_L40-44_
- desc: Enumeration specifying the portion of the viewport to consider when performing operations such as normalizing the mouse position or reading pixels from the media render target
- L42 _public enumerator_ `FullViewport = 0`
- L43 _public enumerator_ `CameraFeed = 1`

#### class `FCameraCalibrationStepsController`  
`class FCameraCalibrationStepsController : public TSharedFromThis<FCameraCalibrationStepsController>`  
_L49-328_
- inherits: `TSharedFromThis<FCameraCalibrationStepsController>`
- desc: Controller for SCameraCalibrationSteps, where the calibration steps are hosted in.
- L53 _public prototype_ `FCameraCalibrationStepsController(TWeakPtr<FCameraCalibrationToolkit> InCameraCalibrationToolkit, ULensFile* InLensFile);`
- L54 _public prototype_ `~FCameraCalibrationStepsController();`
- L57 _public prototype_ `void Initialize();` — Initialize resources.
- L60 _public prototype_ `TSharedPtr<SWidget> BuildUI();` — Returns the UI that this object controls
- L63 _public prototype_ `void InitializeMediaPlayer();` — Creates the media player and media texture used to play the media source
- L66 _public prototype_ `UMediaTexture* GetMediaOverlayTexture() const;` — Gets the texture used to display the media overlay
- L69 _public prototype_ `FIntPoint GetMediaOverlayResolution() const;` — Gets the resolution of the media overlay
- L72 _public prototype_ `FIntPoint GetCameraFeedSize() const;` — Returns the size of the camera feed (which may be smaller than the media overlay or the CG render)
- L75 _public prototype_ `float GetCameraFeedAspectRatio() const;` — Returns the aspect ratio of the camera feed
- L78 _public prototype_ `float GetWiperWeight() const;` — Returns the CG weight that is composited on top of the media
- L81 _public prototype_ `void SetWiperWeight(float InWeight);` — Sets the weight/alpha for that CG that is composited on top of the media. 0 means invisible.
- L84 _public prototype_ `void SetCamera(ACameraActor* InCamera);` — Sets the camera used for the CG
- L87 _public prototype_ `ACameraActor* GetCamera() const;` — Returns the camera used for the CG
- L90 _public prototype_ `void TogglePlay();` — Toggles the play/stop state of the media player
- L93 _public prototype_ `bool IsPaused() const;` — Returns true if the media player is paused
- L96 _public prototype_ `void Play();` — Set play on the media player
- L99 _public prototype_ `void Pause();` — Set pause on the media player
- L102 _public prototype_ `FLensFileEvaluationInputs GetLensFileEvaluationInputs() const;` — Returns the latest data used when evaluating the lens
- L105 _public prototype_ `ULensFile* GetLensFile() const;` — Returns the LensFile that this tool is using
- L108 _public prototype_ `ULensComponent* FindLensComponent() const;` — Returns the first LensComponent attached to the CG camera whose LensFile matches the open asset
- L111 _public prototype_ `const ULensDistortionModelHandlerBase* GetDistortionHandler() const;` — Returns the distortion handler used to distort the CG being displayed in the simulcam viewport
- L114 _public prototype_ `bool SetMediaSource(UMediaSource* InMediaSource);` — Sets the current media source being used in the calibration
- L117 _public prototype_ `bool SetMediaTexture(UMediaTexture* InMediaTexture);` — Sets the current media to a media texture being used in the calibration
- L120 _public prototype_ `bool SetMediaProfileSource(UMediaSource* InMediaProfileSource);` — Sets the current media to a media source in the active media profile
- L123 _public prototype_ `void ClearMedia();` — Clears out any media source or media texture currently being played
- L126 _public prototype_ `void GetMediaProfileSources(TArray<TWeakObjectPtr<UMediaSource>>& OutSources) const;` — Gets a list of valid media sources from the current media profile
- L129 _public prototype_ `TArray<TSoftObjectPtr<UMediaSource>> GetMediaSourceAssets() const;` — Gets all media source assets in the content browser
- L132 _public prototype_ `TArray<TSoftObjectPtr<UMediaTexture>> GetMediaTextureAssets() const;` — Gets all media texture assets in the content browser
- L135 _public prototype_ `FString GetMediaSourceUrl() const;` — Gets the current media source url being played. Empty if None
- L138 _public prototype_ `UMediaSource* GetMediaSource() const;` — Gets the current media source being played, or nullptr if nothing is being played
- L141 _public prototype_ `UMediaSource* GetMediaProfileSource() const;` — Gets the media source from the active media profile currently being played, or nullptr if no media profile source is being played
- L144 _public prototype_ `UMediaTexture* GetMediaTexture() const;` — Gets the current media texture being displayed, or nullptr if the media texture is not being overridden
- L150 _public prototype_ `UMediaPlayer* GetMediaPlayer() const;` — Gets the active media player being used; if an external media texture is being used, this returns the player that texture is linked to, otherwise, the internal media player is returned
- L153 _public prototype_ `const TConstArrayView<TStrongObjectPtr<UCameraCalibrationStep>> GetCalibrationSteps() const;` — Returns the calibration steps
- L156 _public prototype_ `void SelectStep(const FName& Name);` — Returns the calibration steps
- L159 _public prototype_ `bool CalculateNormalizedMouseClickPosition(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, FVector2f& OutPosition, ESimulcamViewportPortion ViewportPortion = ESimulcamViewportPortion::FullViewport) const;` — Calculates the normalized (0~1) coordinates in the simulcam viewport of the given mouse click
- L162 _public prototype_ `UWorld* GetWorld() const;` — Finds the world being used by the tool for finding and spawning objects
- L165 _public prototype_ `bool ReadMediaPixels(TArray<FColor>& Pixels, FIntPoint& Size, FText& OutErrorMessage, ESimulcamViewportPortion ViewportPortion = ESimulcamViewportPortion::FullViewport) const;` — Reads the pixels from the open media source
- L168 _public prototype_ `bool IsOverlayEnabled(EOverlayPassType OverlayPass = EOverlayPassType::ToolOverlay) const;` — Returns true if the overlay transform pass is currently enabled
- L171 _public prototype_ `void SetOverlayEnabled(const bool bEnabled = true, EOverlayPassType OverlayPass = EOverlayPassType::ToolOverlay);` — Sets the enabled state of the overlay transform pass
- L174 _public prototype_ `UMaterialInterface* GetOverlayMaterial(EOverlayPassType OverlayPass) const;` — Returns the overlay material used by the input overlay pass type
- L177 _public prototype_ `void SetOverlayMaterial(UMaterialInterface* OverlayMaterial, bool bShowOverlay = true, EOverlayPassType OverlayPass = EOverlayPassType::ToolOverlay);` — Sets the overlay material to be used by the overlay transform pass
- L180 _public prototype_ `void SetCameraFeedDimensionsFromMousePosition(FVector2D MousePosition);` — Use the input mouse position (representing any corner of the camera feed) and the dimensions of the media source to calculate the new size of the camera feed
- L183 _public prototype_ `void SetCameraFeedDimensions(FIntPoint Dimensions, bool bMarkAsOverridden);` — Set the camera feed dimensions info of the LensFile being edited
- L186 _public prototype_ `void ResetCameraFeedDimensions();` — Resets the camera feed dimensions by fitting it within the currently playing media source
- L191 _public prototype_ `void OnSimulcamViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called by the UI when the Simulcam Viewport is clicked
- L194 _public prototype_ `bool OnSimulcamViewportInputKey(const FKey& InKey, const EInputEvent& InEvent);` — Called by the UI when the Simulcam Viewport receives keyboard input
- L197 _public prototype_ `void OnSimulcamViewportMarqueeSelect(FVector2D StartPosition, FVector2D EndPosition);` — Called by the UI when the Simulcam Viewport receives a marquee select event
- L200 _public prototype_ `FReply OnRewindButtonClicked();` — Called by the UI when the rewind button is clicked
- L203 _public prototype_ `FReply OnReverseButtonClicked();` — Called by the UI when the reverse button is clicked
- L206 _public prototype_ `FReply OnStepBackButtonClicked();` — Called by the UI when the step back button is clicked
- L209 _public prototype_ `FReply OnPlayButtonClicked();` — Called by the UI when the play button is clicked
- L212 _public prototype_ `FReply OnPauseButtonClicked();` — Called by the UI when the pause button is clicked
- L215 _public prototype_ `FReply OnStepForwardButtonClicked();` — Called by the UI when the step forward button is clicked
- L218 _public prototype_ `FReply OnForwardButtonClicked();` — Called by the UI when the forward button is clicked
- L221 _public prototype_ `bool DoesMediaSupportSeeking() const;` — Returns true if the media player supports seeking
- L224 _public prototype_ `bool DoesMediaSupportNextReverseRate() const;` — Returns true if the media player supports a reverse rate that is faster than its current rate
- L227 _public prototype_ `bool DoesMediaSupportNextForwardRate() const;` — Returns true if the media player supports a forward rate that is faster than its current rate
- L230 _public prototype_ `float GetFasterReverseRate() const;` — Computes the reverse playback rate
- L233 _public prototype_ `float GetFasterForwardRate() const;` — Computes the fast forward playback rate
- L236 _public prototype_ `void ToggleShowMediaPlaybackControls();` — Toggle the setting that controls whether the media playback buttons will be visible in the UI
- L239 _public prototype_ `bool AreMediaPlaybackControlsVisible() const;` — Returns true if the media playback buttons are visible in the UI
- L244 _private prototype_ `ULensComponent* FindLensComponentOnCamera(ACameraActor* CineCamera) const;` — Returns the first lens component with a matching LensFile found on the input camera, or nullptr if none exists
- L247 _private prototype_ `void Cleanup();` — Releases resources used by the tool
- L250 _private prototype_ `ACameraActor* FindFirstCameraWithCurrentLens() const;` — Convenience function that returns the first camera it finds that is using the lens associated with this object.
- L253 _private prototype_ `ACameraActor* FindDefaultCamera() const;` — When no camera can be found using the current lens file, this function finds a default camera in the level to use
- L256 _private prototype_ `bool OnTick(float DeltaTime);` — Called by the core ticker
- L259 _private prototype_ `void CreateSteps();` — Finds and creates the available calibration steps
- L262 _private prototype_ `void MinimizeAspectRatioError(FIntPoint& CameraFeedDimensions, float CameraAspectRatio);` — Iteratively attempt to resize the camera feed until its aspect ratio matches the input camera aspect ratio
- L265 _private prototype_ `void OnActiveMediaProfileChanged(UMediaProfile* PreviousMediaProfile, UMediaProfile* NewMediaProfile);` — Raised when the active media profile is changed
- L268 _private prototype_ `bool CalculateCameraFeedCropRegion(FIntRect& OutCropRegion, FIntPoint& OutCropSize) const;` — Calculate the crop region for center-fit sampling of camera feed from media texture
- L273 _private member_ `TWeakPtr<FCameraCalibrationToolkit> CameraCalibrationToolkit;` — Pointer to the camera calibration toolkit
- L276 _private member_ `TArray<TStrongObjectPtr<UCameraCalibrationStep>> CalibrationSteps;` — Array of the calibration steps that this controller is managing
- L279 _private member_ `TWeakObjectPtr<class ULensFile> LensFile;` — The lens asset
- L282 _private member_ `int32 MediaProfileSourceIndex = INDEX_NONE;` — The index of the media source in the active media profile being played
- L285 _private member_ `TWeakObjectPtr<UMediaTexture> MediaTexture;` — The media texture used by the media plate
- L288 _private member_ `TWeakObjectPtr<UMediaTexture> ExternalMediaTexture;` — An external media texture to use by the media plate instead of the internal one
- L291 _private member_ `TStrongObjectPtr<UMediaPlayer> InternalMediaPlayer;` — The media player that is playing the selected media source
- L294 _private member_ `TStrongObjectPtr<UTextureRenderTarget2D> CachedMediaRenderTarget;` — Used to extract pixel data from the media texture, cached to avoid having to recreate it every time
- L297 _private member_ `TWeakObjectPtr<UMaterialInterface> ToolOverlayMaterial;` — The material used to render the overlay for the tool overlay pass
- L300 _private member_ `bool bToolOverlayEnabled = false;` — Whether the tool overlay is enabled
- L303 _private member_ `TWeakObjectPtr<UMaterialInterface> UserOverlayMaterial;` — The material used to render the overlay for the user overlay pass
- L306 _private member_ `bool bUserOverlayEnabled = false;` — Whether the user overlay is enabled
- L309 _private member_ `float WiperWeight = 0.5f;` — Wiper weight for overlaying the media texture on the CG render
- L312 _private member_ `FIntPoint LastMediaOverlayResolution;` — Keeps track of the last read media overlay resolution so that resolution changes can be detected
- L315 _private member_ `TWeakObjectPtr<ACameraActor> Camera;` — The currently selected camera
- L318 _private member_ `TWeakObjectPtr<UCineCameraComponent> CineCameraComponent;` — The currently selected camera's camera component
- L321 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — The delegate for the core ticker callback
- L324 _private member_ `FLensFileEvaluationInputs LensFileEvaluationInputs;` — Evaluation Data supplied by the Lens Component for the current frame. Only valid during the current frame.
- L327 _private member_ `bool bShowMediaPlaybackButtons = true;` — Setting to control whether the media playback buttons are visible

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/CameraCalibrationTimeSliderController.h` (Private)


#### class `FCameraCalibrationTimeSliderController`  
`class FCameraCalibrationTimeSliderController : public ITimeSliderController , public TSharedFromThis<FCameraCalibrationTimeSliderController> , public FTickableEditorObject`  
_L18-147_
- inherits: `ITimeSliderController,TSharedFromThis<FCameraCalibrationTimeSliderController>,FTickableEditorObject`
- desc: Controlling the time slider visuals from the given zoom, focus, iris input
- L25 _public prototype_ `FCameraCalibrationTimeSliderController(const TSharedRef<FCameraCalibrationStepsController>& InCalibrationStepsController, ULensFile* InLensFile);`
- L28 _public prototype_ `virtual int32 OnPaintTimeSlider( bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L29 _public prototype_ `virtual int32 OnPaintViewArea( const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, const FPaintViewAreaArgs& Args ) const override;`
- L30 _public prototype_ `virtual void SetViewRange( double NewRangeMin, double NewRangeMax, EViewRangeInterpolation Interpolation ) override;`
- L32 _public function_ `virtual FCursorReply OnCursorQuery( const SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override`
- L33 _public function_ `virtual FFrameRate GetDisplayRate() const override`
- L34 _public function_ `virtual FFrameRate GetTickResolution() const override`
- L35 _public function_ `virtual FFrameTime GetScrubPosition() const override`
- L36 _public function_ `virtual FAnimatedRange GetViewRange() const override`
- L40 _public function_ `virtual FReply OnMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L41 _public function_ `virtual FReply OnMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L42 _public function_ `virtual FReply OnMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L43 _public function_ `virtual FReply OnMouseWheel(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L47 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L48 _public function_ `virtual bool IsTickable() const override`
- L49 _public prototype_ `virtual TStatId GetStatId() const override;`
- L57 _public prototype_ `void UpdateSelection(const ELensDataCategory InCategory, const TOptional<float> InFloatPoint);` — Handler for category changed @param InCategory new category @param InFloatPoint new point value
- L60 _public prototype_ `void ResetSelection();` — Resets the selection and prevent the displaying
- L64 _private prototype_ `bool IsVisible() const;` — Whether time slider should be visible
- L121 _private prototype_ `void CommitPositionChange(const float InValue, const FString& InCategoryString);` — Time scrub line position handler @param InValue Input scrub value @param InCategoryString Scrub category name
- L125 _private member_ `FTimeSliderArgs TimeSliderArgs;` — Container for the input time slider delegates and properties
- L128 _private member_ `const FSlateBrush* ScrubHandleUpBrush;` — Brush for drawing an upwards facing scrub handles
- L131 _private member_ `const FSlateBrush* ScrubHandleDownBrush;` — Brush for drawing a downwards facing scrub handle
- L134 _private member_ `TWeakPtr<FCameraCalibrationStepsController> CalibrationStepsControllerWeakPtr;` — Holds the weak reference to SCameraCalibrationSteps, where the calibration steps are hosted in.
- L137 _private member_ `TOptional<ELensDataCategory> SelectedCategory;` — Selected Lens category
- L140 _private member_ `TOptional<float> SelectedFocus;` — Selected focus point
- L143 _private member_ `FScrubInput ScrubInput;` — Scrub input struct
- L146 _private member_ `TWeakObjectPtr<ULensFile> LensFileWeakPtr;` — Pointer for asset lens file

#### struct `FCameraCalibrationTimeSliderController::FScrubInput`  
`struct FScrubInput`  
_L73-112_
- desc: Scrub input using for visual and validation of input data
- L75 _public function_ `FScrubInput()`
- L78 _public function_ `FScrubInput(const float InValue, const FString& InCategoryString) : Value(InValue) , CategoryString(InCategoryString)`
- L86 _public function_ `bool IsValid() const` — Whether the scrub input is valid
- L89 _public function_ `const FString& GetFormattedCategoryString() const` — Get the formatted input string
- L92 _public function_ `void Reset()` — Reset the input values
- L98 _public function_ `TOptional<float> GetValue() const` — Get scrub input value
- L105 _private member_ `TOptional<float> Value;` — Input value
- L108 _private member_ `FString CategoryString;` — Input category string
- L111 _private member_ `FString FormattedCategoryString;` — Formatted string

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/CameraCalibrationToolkit.h` (Private)


#### class `FCameraCalibrationToolkit`  
`class FCameraCalibrationToolkit : public FAssetEditorToolkit`  
_L21-104_
- inherits: `FAssetEditorToolkit`
- desc: Toolkit to do camera calibration
- L23 _private typedef_ `using Super = FAssetEditorToolkit;`
- L27 _public prototype_ `static TSharedRef<FCameraCalibrationToolkit> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, ULensFile* InLensFile);` — Creates an editor for LensFile assets
- L36 _public prototype_ `void InitCameraCalibrationTool(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, ULensFile* InLensFile);` — Edits the specified table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InLensFile				The LensFile asset to edit
- L43 _public prototype_ `static TSharedPtr<SWindow> OpenPopupWindow(const FText& InTitle);` — Creates Popup Toolkit Window or bring it to front if window does exists @param	InTitle	Window Title
- L46 _public prototype_ `static void DestroyPopupWindow();` — Close the window and release the pointer
- L51 _protected prototype_ `virtual FText GetBaseToolkitName() const override;`
- L52 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L53 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L54 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L55 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L56 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L57 _protected prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L63 _private prototype_ `TSharedRef<SDockTab> HandleSpawnLensEditorTab(const FSpawnTabArgs& Args) const;` — Handle spawning the tab that holds the LensFile panel tab.
- L66 _private prototype_ `TSharedRef<SDockTab> HandleSpawnNodalOffsetTab(const FSpawnTabArgs& Args) const;` — Handle spawning the tab that holds the NodalOffset panel tab.
- L69 _private prototype_ `TSharedRef<SDockTab> HandleSpawnLensEvaluationTab(const FSpawnTabArgs& Args) const;` — Handle spawning the tab that holds the current evaluated data
- L71 _private prototype_ `FCachedFIZData GetFIZData() const;`
- L74 _private prototype_ `void BindCommands();` — Binds the UI commands to delegates.
- L77 _private prototype_ `void ExtendToolBar();` — Builds the toolbar widget for the camera calibration tools editor.
- L80 _private prototype_ `void ExtendMenu();` — Extend Toolkit Menu
- L85 _private member_ `ULensFile* LensFile = nullptr;` — Toolkit is adding a reference to the editing object so a standard pointer is ok
- L88 _private member_ `TSharedPtr<SLensFilePanel> LensEditorTab;` — Lens editor tab to do manual adjustments
- L91 _private member_ `TSharedPtr<SWidget> CalibrationStepsTab;` — Camera calibration tools
- L94 _private member_ `TSharedPtr<SLensEvaluation> LensEvaluationWidget;` — Data displaying evaluated data based on evaluation inputs
- L97 _private member_ `TSharedPtr<FCameraCalibrationStepsController> CalibrationStepsController;` — Calibration Steps Controller
- L100 _private member_ `static TWeakPtr<SWindow> PopupWindow;` — Singleton for the toolkit pop-up window.
- L103 _private member_ `TSharedPtr<FExtender> MenuExtender;` — Menu extender

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/Curves/LensDataCurveModel.h` (Private)


#### class `FLensDataCurveModel`  
`class FLensDataCurveModel : public FRichCurveEditorModel`  
_L17-57_
- inherits: `FRichCurveEditorModel`
- desc: Base class to handle displaying curves for various lens data types
- L20 _public prototype_ `FLensDataCurveModel(ULensFile* InOwner);`
- L23 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InKeyPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L24 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override;`
- L25 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L26 _public prototype_ `virtual bool IsValid() const override;`
- L27 _public prototype_ `virtual FRichCurve& GetRichCurve() override;`
- L28 _public prototype_ `virtual const FRichCurve& GetReadOnlyRichCurve() const override;`
- L32 _public prototype_ `virtual UObject* GetOwningObject() const override;`
- L35 _public prototype_ `virtual FText GetKeyLabel() const;`
- L36 _public prototype_ `virtual FText GetValueLabel() const;`
- L37 _public prototype_ `virtual FText GetValueUnitPrefixLabel() const;`
- L38 _public prototype_ `virtual FText GetValueUnitSuffixLabel() const;`
- L42 _public member_ `static ECurveEditorViewID ViewId;` — View ID that identifies the registered view type
- L47 _protected member_ `TStrongObjectPtr<ULensFile> LensFile;` — LensFile we are operating on
- L50 _protected member_ `FRichCurve CurrentCurve;` — Active curve pointer
- L53 _protected member_ `TAttribute<TRange<double>> ClampOutputRange;` — An optional clamp on the output values (y-axis) that the curve keys are allowed to have
- L56 _protected member_ `bool bIsCurveValid = false;` — Whether a valid curve was built from lens data

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/Curves/LensEncodersCurveModel.h` (Private)


#### enum `EEncoderType`  
`enum class EEncoderType : uint8`  
_L11-15_
- desc: Type of supported encoders
- L13 _public enumerator_ `Focus`
- L14 _public enumerator_ `Iris`

#### class `FLensEncodersCurveModel`  
`class FLensEncodersCurveModel : public FLensDataCurveModel`  
_L20-44_
- inherits: `FLensDataCurveModel`
- desc: Handles curves associated to encoder mapping
- L24 _public prototype_ `FLensEncodersCurveModel(ULensFile* InOwner, EEncoderType InType);`
- L27 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L31 _public prototype_ `virtual FText GetKeyLabel() const override;`
- L32 _public prototype_ `virtual FText GetValueLabel() const override;`
- L33 _public prototype_ `virtual FText GetValueUnitPrefixLabel() const override;`
- L34 _public prototype_ `virtual FText GetValueUnitSuffixLabel() const override;`
- L38 _protected prototype_ `void OnCurveModifiedCallback() const;`
- L43 _private member_ `EEncoderType EncoderType = EEncoderType::Focus;` — Type of encoder for which to display curve

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/Curves/LensMultiAxisCurveModel.h` (Private)


#### enum `ELensCurveAxis`  
`enum class ELensCurveAxis : uint8`  
_L8-12_
- L10 _public enumerator_ `Zoom`
- L11 _public enumerator_ `Focus`

#### class `FLensDataMultiAxisCurveModel`  
`class FLensDataMultiAxisCurveModel : public FLensDataCurveModel`  
_L17-42_
- inherits: `FLensDataCurveModel`
- desc: Curve model for lens data tables that have multiple axes (e.g focus and zoom), which can generate curves for either axis
- L20 _public prototype_ `FLensDataMultiAxisCurveModel(ULensFile* InOwner, ELensDataCategory InCategory, ELensCurveAxis InCurveAxis, float InCurveValue, int32 InParameterIndex);`
- L23 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L24 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType) override;`
- L25 _public prototype_ `virtual FText GetKeyLabel() const override;`
- L26 _public prototype_ `virtual FText GetValueLabel() const override;`
- L27 _public prototype_ `virtual FText GetValueUnitSuffixLabel() const override;`
- L32 _private member_ `ELensDataCategory Category;` — The category of the data table being displayed in the curve
- L35 _private member_ `ELensCurveAxis CurveAxis;` — The axis to use as the x-axis of the curve
- L38 _private member_ `float CurveValue = 0.0;` — The value to hold fixed on the axis that isn't being plotted
- L41 _private member_ `int32 ParameterIndex = INDEX_NONE;` — The index of the data table parameter whose values are plotted on the y-axis of the curve

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/ImageCenterTool.h` (Private)


#### class `UImageCenterTool`  
`class UImageCenterTool : public UCameraCalibrationStep`  
_L15-64_
- reflection: `UCLASS()`
- inherits: `UCameraCalibrationStep`
- desc: UImageCenterTool is the controller for the image center panel.
- L22 _public prototype_ `virtual void Initialize(TWeakPtr<FCameraCalibrationStepsController> InCameraCalibrationStepController) override;`
- L23 _public prototype_ `virtual void Shutdown() override;`
- L24 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L25 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `virtual bool OnViewportInputKey(const FKey& InKey, const EInputEvent& InEvent) override;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L28 _public function_ `virtual FName FriendlyName() const override`
- L29 _public prototype_ `virtual bool DependsOnStep(UCameraCalibrationStep* Step) const override;`
- L30 _public prototype_ `virtual void Activate() override;`
- L31 _public prototype_ `virtual void Deactivate() override;`
- L32 _public prototype_ `virtual bool IsActive() const override;`
- L33 _public prototype_ `virtual UMaterialInstanceDynamic* GetOverlayMID() const override;`
- L34 _public prototype_ `virtual bool IsOverlayEnabled() const override;`
- L35 _public prototype_ `virtual FCameraCalibrationStepsController* GetCameraCalibrationStepsController() const override;`
- L39 _public prototype_ `UCameraImageCenterAlgo* GetAlgo() const;` — Returns the currently active algorithm
- L42 _public prototype_ `void SetAlgo(const FName& AlgoName);` — Sets the active algorithm by name
- L47 _public prototype_ `void OnSaveCurrentImageCenter();` — Called by the UI when the user wants to save the calibration data that the current algorithm is providing
- L52 _private member_ `TWeakPtr<FCameraCalibrationStepsController> CameraCalibrationStepsController;` — Pointer to the calibration steps controller
- L56 _private member_ `TObjectPtr<UCameraImageCenterAlgo> CurrentAlgo;` — `UPROPERTY(Transient)` — The currently selected algorithm
- L60 _private member_ `TMap<FName, TObjectPtr<UMaterialInstanceDynamic>> AlgoOverlayMIDs;` — `UPROPERTY(Transient)` — Map of algo names to overlay MIDs used by those algos
- L63 _private member_ `bool bIsActive = false;` — True if this tool is the active one in the panel

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/LensDistortionTool.h` (Private)


#### enum `ECalibrationPattern`  
`enum class ECalibrationPattern : uint8`  
_L25-31_
- reflection: `UENUM()`
- desc: List of supported calibration patterns
- L27 _public enumerator_ `Checkerboard`
- L28 _public enumerator_ `Aruco`
- L29 _public enumerator_ `Points`
- L30 _public enumerator_ `Charuco`

#### enum `EDatasetVersion`  
`enum class EDatasetVersion : uint8`  
_L34-42_
- desc: Version info to support backwards compatibility of dataset importing
- L36 _public enumerator_ `Invalid = 0`
- L37 _public enumerator_ `SeparateAlgoClasses = 1`
- L38 _public enumerator_ `CombinedAlgoClasses = 2`
- L41 _public enumerator_ `CurrentVersion = CombinedAlgoClasses` — Add new versions above

#### struct `FCalibrationRow`  
`struct FCalibrationRow`  
_L46-80_
- reflection: `USTRUCT()`
- desc: The data associated with a single captured calibration pattern/point
- L52 _public member_ `int32 Index = -1;` — `UPROPERTY()` — Index to display in list view
- L56 _public member_ `FObjectPoints ObjectPoints;` — `UPROPERTY()` — Set of captured 3D points for the calibrator in world space
- L60 _public member_ `FImagePoints ImagePoints;` — `UPROPERTY()` — Set of captured 2D pixel locations where the calibrator was detected in the image
- L64 _public member_ `FTransform CameraPose = FTransform::Identity;` — `UPROPERTY()` — Pose of the camera actor when this data for this row was captured
- L68 _public member_ `FTransform TargetPose = FTransform::Identity;` — `UPROPERTY()` — Pose of the calibrator actor when this data for this row was captured
- L72 _public member_ `ECalibrationPattern Pattern = ECalibrationPattern::Checkerboard;` — `UPROPERTY()` — The calibration pattern used to capture the data for this row
- L76 _public member_ `FIntPoint CheckerboardDimensions = FIntPoint(0, 0);` — `UPROPERTY()` — Dimensions of the detected checkerboard pattern (only valid if calibration pattern was ECalibrationPattern::Checkerboard)
- L79 _public member_ `FImage MediaImage;` — Stored frame from the media source associated with the data for this row

#### struct `FCalibrationDataset`  
`struct FCalibrationDataset`  
_L84-89_
- reflection: `USTRUCT()`
- desc: An array of captured rows with calibration data
- L88 _public member_ `TArray<TSharedPtr<FCalibrationRow>> CalibrationRows;`

#### struct `FLensCaptureSettings`  
`struct FLensCaptureSettings`  
_L93-120_
- reflection: `USTRUCT()`
- desc: Settings that control how data is captured in the tool
- L99 _public member_ `ECalibrationPattern CalibrationPattern = ECalibrationPattern::Checkerboard;` — `UPROPERTY(EditAnywhere, Category = "Capture Settings")` — The pattern to detect in the media image. CharUco is recommended when available.
- L103 _public member_ `TWeakObjectPtr<AActor> Calibrator;` — `UPROPERTY(EditAnywhere, Category = "Capture Settings")` — An actor with Calibration Point Components that represents the virtual version of a real calibration target
- L107 _public member_ `bool bIsCalibratorTracked = false;` — `UPROPERTY(EditAnywhere, Category = "Capture Settings")` — Set to true if the calibration target being used is tracked
- L111 _public member_ `bool bIsCameraTracked = false;` — `UPROPERTY(EditAnywhere, Category = "Capture Settings")` — Set to true if the camera being used is tracked
- L115 _public member_ `bool bShowOverlay = true;` — `UPROPERTY(EditAnywhere, Category = "Capture Settings", meta = (EditCondition = "CalibrationPattern != ECalibrationPattern::Points", EditConditionHides))` — Display a debug overlay over the simulcam viewport showing the detected patterns that have been captured
- L119 _public member_ `FText NextPoint;` — `UPROPERTY(VisibleAnywhere, Category = "Capture Settings", meta = (EditCondition = "CalibrationPattern == ECalibrationPattern::Points", EditConditionHides))` — The name of the next calibration point to locate in the image

#### struct `FLensSolverSettings`  
`struct FLensSolverSettings`  
_L124-154_
- reflection: `USTRUCT()`
- desc: Settings that control what and how the solver will compute the calibrated lens data
- L130 _public member_ `TSubclassOf<ULensDistortionSolver> SolverClass = ULensDistortionSolverOpenCV::StaticClass();` — `UPROPERTY(EditAnywhere, NoClear, Category = "Solver Settings", meta = (HideViewOptions, ShowDisplayNames))` — Select the solver to use when solving for calibrated lens data
- L137 _public member_ `bool bSolveNodalOffset = false;` — `UPROPERTY(EditAnywhere, Category = "Solver Settings")` — If true, the solver will calibrate for the nodal offset in addition to lens distortion. This property will be read-only if either IsCalibratorTracked or IsCameraTracked is unchecked because both are required to compute the nodal offset.
- L141 _public member_ `TOptional<double> FocalLengthGuess;` — `UPROPERTY(EditAnywhere, Category = "Solver Settings")` — An estimate for the focal length of the lens
- L145 _public member_ `bool bFixFocalLength = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Solver Settings", meta = (DisplayName = "Fix Focal Length During Optimization"))` — Set to true to prevent the solver from optimizing the focal length. The focal length guess will be used.
- L149 _public member_ `bool bFixImageCenter = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Solver Settings", meta = (DisplayName = "Fix Image Center During Optimization"))` — Set to true to prevent the solver from optimizing the image center. The image center will be assumed to be in the exact center.
- L153 _public member_ `bool bFixDistortion = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Solver Settings", meta = (DisplayName = "Fix Distortion During Optimization"))` — Set to true to prevent the solver from optimizing the distortion parameters. The current calibrated distortion parameters will be used.

#### struct `FLensDistortionSessionInfo`  
`struct FLensDistortionSessionInfo`  
_L157-167_
- desc: Data associated with a lens distortion calibration session
- L160 _public member_ `FDateTime StartTime;` — The date/time when the current calibration session started
- L163 _public member_ `int32 RowIndex = -1;` — The index of the next row in the current calibration session
- L166 _public member_ `bool bIsActive = false;` — True if a calibration session is currently in progress

#### class `ULensDistortionTool`  
`class ULensDistortionTool : public UCameraCalibrationStep`  
_L173-328_
- reflection: `UCLASS()`
- inherits: `UCameraCalibrationStep`
- desc: The primary tool used in the LensFile asset editor to capture and solve for calibrated lens data
- L181 _public prototype_ `virtual void Initialize(TWeakPtr<FCameraCalibrationStepsController> InCameraCalibrationStepController) override;`
- L182 _public prototype_ `virtual void Shutdown() override;`
- L183 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L184 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L185 _public prototype_ `virtual bool OnViewportMarqueeSelect(FVector2D StartPosition, FVector2D EndPosition) override;`
- L186 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L187 _public function_ `virtual FName FriendlyName() const override`
- L188 _public prototype_ `virtual bool DependsOnStep(UCameraCalibrationStep* Step) const override;`
- L189 _public prototype_ `virtual void Activate() override;`
- L190 _public prototype_ `virtual void Deactivate() override;`
- L191 _public prototype_ `virtual bool IsActive() const override;`
- L192 _public prototype_ `virtual UMaterialInstanceDynamic* GetOverlayMID() const override;`
- L193 _public prototype_ `virtual bool IsOverlayEnabled() const override;`
- L198 _private prototype_ `void StartCalibrationSession();` — Initiate a new calibration session (if one is not already active)
- L201 _private prototype_ `void EndCalibrationSession();` — End the current calibration session
- L204 _private prototype_ `void DeleteExportedRow(const int32& RowIndex) const;` — Deletes the .json file with the input row index that was previously exported for this session.
- L207 _private prototype_ `uint32 AdvanceSessionRowIndex();` — Increments the session index and returns its new value
- L210 _private prototype_ `void CalibrateLens();` — Called by the UI when the user wants to save the calibration data
- L213 _private prototype_ `void SaveCalibrationResult();` — Save the results from a finished distortion calibration to the Lens File
- L216 _private prototype_ `void CancelCalibration();` — Cancel an in-progress async calibration task
- L219 _private prototype_ `bool GetCalibrationStatus(FText& StatusText) const;` — Get the latest status from the lens distortion calibration. Returns true if the status has changed.
- L222 _private prototype_ `bool CaptureCalibrationData(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, FIntRect RegionOfInterest = FIntRect());` — Capture a calibration pattern (or raw points) from the media image and collect additional data needed for a full calibration row
- L225 _private prototype_ `bool DetectCheckerboardPattern(TArray<FColor>& Pixels, FIntPoint Size, FIntRect RegionOfInterest, TSharedPtr<FCalibrationRow> OutRow);` — Detects a checkerboard pattern in the input array of pixels (supplied by the media image) and fills out the 2D and 3D points in the output calibration row
- L228 _private prototype_ `bool DetectArucoPattern(TArray<FColor>& Pixels, FIntPoint Size, TSharedPtr<FCalibrationRow> OutRow);` — Detects an aruco pattern in the input array of pixels (supplied by the media image) and fills out the 2D and 3D points in the output calibration row
- L231 _private prototype_ `bool DetectCharucoPattern(TArray<FColor>& Pixels, FIntPoint Size, FIntRect RegionOfInterest, TSharedPtr<FCalibrationRow> OutRow);` — Detects a charuco pattern in the input array of pixels (supplied by the media image) and fills out the 2D and 3D points in the output calibration row
- L234 _private prototype_ `bool DetectPoint(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TSharedPtr<FCalibrationRow> OutRow);` — Captures the mouse position and the 3D world location of the current calibration component and and fills out the output calibration row
- L237 _private prototype_ `void ImportCalibrationDataset();` — Import a saved calibration data set from disk
- L240 _private prototype_ `void SetCalibrator(AActor* InCalibrator);` — Sets the calibrator object to be used. Updates the selection picker.
- L243 _private prototype_ `void UpdateCalibrationComponents();` — Caches the calibration point components of the current calibrator actor, and updates the list if those components become invalid
- L246 _private prototype_ `void ClearCalibrationRows();` — Clears the list of calibration rows
- L249 _private prototype_ `void SetComponentIndex(int32 Index);` — Updates the calibration point component index (used when the calbration pattern is ECalibrationPattern::Points)
- L252 _private prototype_ `void RefreshCoverage();` — Clears and redraws the overlay texture with the data from the captured calibration rows
- L255 _private prototype_ `void RescalePoints(TArray<FVector2D>& Points, FIntPoint DebugTextureSize, FIntPoint CameraFeedSize);` — Adjust the 2D location of every input pixel to account for differences between the size of the captured image and the overlay texture
- L258 _private prototype_ `void GenerateDummyCheckerboardPoints(TArray<FObjectPoints>& Samples3d, int32 NumImages, FIntPoint CheckerboardDimensions);` — Replace tracked checkerboard calibration points with a set of dummy 3D points
- L261 _private prototype_ `void GenerateObjectPointsInLocalSpace(TArray<FObjectPoints>& Samples3d);` — Generates the object points in local space. Available in case the solver requires it.
- L264 _private prototype_ `FString GetSessionSaveDir() const;` — Get the directory for the current session
- L267 _private prototype_ `FString GetRowFilename(int32 RowIndex) const;` — Get the filename of a row with the input index
- L273 _private prototype_ `int32 ImportCalibrationRow(const TSharedRef<FJsonObject>& CalibrationRowObject, const FImage& RowImage, EDatasetVersion DatasetVersion);` — Import a JsonObject of calibration data that represents a single calibration row. Returns the row index of the imported row.
- L276 _private prototype_ `void ExportSessionData();` — Export global session data to a .json file
- L279 _private prototype_ `void ExportCalibrationRow(TSharedPtr<FCalibrationRow> Row);` — Export the row data to a json file
- L283 _private member_ `TSharedPtr<SLensDistortionToolPanel> DistortionWidget;` — UI Widget for this tool
- L285 _private member_ `FLensSolverSettings SolverSettings;`
- L286 _private member_ `FLensCaptureSettings CaptureSettings;`
- L289 _private member_ `FCalibrationDataset Dataset;` — Collection of calibration rows containing the data needed to run a lens calibration
- L293 _private member_ `TObjectPtr<ULensDistortionSolver> Solver;` — `UPROPERTY(Transient)` — The solver object that runs the lens calibration on another thread. The ptr is stored to access the solver to get status updates and/or cancel the calibration from the game thread
- L296 _private member_ `FDistortionCalibrationTask CalibrationTask;` — An asynchronous task handle. When valid, the tool will poll its state to determine when the task has completed, and then extract the calibration result from this task handle.
- L299 _private member_ `FDistortionCalibrationResult CalibrationResult;` — The result from the most recently completed distortion calibration. It is saved as a member variable because the result is not saved immediately, but only if the user confirms that it should be saved.
- L302 _private member_ `TArray<TWeakObjectPtr<UCalibrationPointComponent>> CalibrationComponents;` — Container for the set of calibrator components selected in the component combobox
- L308 _private member_ `TArray<FVector> CachedComponentLocations;` — The 3D world locations of the calibration point components should all come from the same frame. Therefore, the locations are all saved at once when the first calibration point is selected (only applicable to ECalibrationPattern::Points)
- L311 _private member_ `int32 CalibrationComponentIndex = -1;` — Index of the next calibration point component to capture (only applicable to ECalibrationPattern::Points)
- L314 _private member_ `FLensDistortionSessionInfo SessionInfo;` — Capture session info, used to track whether newly captured data should be added to an existing dataset
- L317 _private member_ `bool bIsActive = false;` — True if this tool is the active tab in the UI
- L321 _private member_ `TObjectPtr<UMaterialInstanceDynamic> OverlayMID;` — `UPROPERTY(Transient)` — Material and Texture that draw the coverage overlay on top of the simulcam viewport during capture
- L324 _private member_ `TObjectPtr<UTexture2D> OverlayTexture;` — `UPROPERTY(Transient)`
- L327 _private member_ `TWeakPtr<FCameraCalibrationStepsController> WeakStepsController;` — Weak ptr to the steps controller that created this step

#### Free symbols / members of external scopes

- L21 _typedef_ `typedef UE::Tasks::TTask<FDistortionCalibrationResult> FDistortionCalibrationTask;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/LensInfoStep.h` (Private)


#### class `ULensInfoStep`  
`class ULensInfoStep : public UCameraCalibrationStep`  
_L16-77_
- reflection: `UCLASS()`
- inherits: `UCameraCalibrationStep`
- desc: ULensInfoStep is used as the initial step to provide information about the lens you are going to calibrate
- L23 _public prototype_ `virtual void Initialize(TWeakPtr<FCameraCalibrationStepsController> InCameraCalibrationStepController) override;`
- L24 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L25 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L26 _public function_ `virtual FName FriendlyName() const override`
- L27 _public prototype_ `virtual bool DependsOnStep(UCameraCalibrationStep* Step) const override;`
- L28 _public prototype_ `virtual void Activate() override;`
- L29 _public prototype_ `virtual void Deactivate() override;`
- L30 _public prototype_ `virtual bool IsActive() const override;`
- L36 _public prototype_ `void OnLensInfoChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — Triggered when user edits any of the LensInfo properties
- L39 _public prototype_ `void OnCameraFeedInfoChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — Triggered when user edits any of the CameraFeedInfo properties
- L42 _public prototype_ `void SaveLensInformation();` — Validates the new LensInfo settings and records a transaction for them
- L45 _public prototype_ `void ResetToDefault();` — Reapply the original LensInfo to the LensFile
- L48 _public prototype_ `bool DiffersFromDefault() const;` — Returns true if our LensInfo differs from the original info when the tool was opened
- L51 _public prototype_ `void ResetCameraFeedInfoToDefault();` — Reset the camera feed dimensions to their default value (recomputed by the Steps Controller)
- L54 _public prototype_ `bool CameraFeedInfoDiffersFromDefault() const;` — Returns true if the camera feed info has been overriden by the user
- L58 _private prototype_ `EVisibility HandleAspectRatioWarningVisibility() const;` — Determines the visibility of the aspect ratio warning by comparing the camera feed aspect ratio with that of the camera actor
- L61 _private prototype_ `EVisibility GetFilmbackWarningVisibility() const;` — Determines the visibility of the camera settings warning by comparing the filmback and squeeze factor in the LensFile with that of the camera actor
- L66 _private member_ `TWeakPtr<FCameraCalibrationStepsController> CameraCalibrationStepsController;` — Pointer to the calibration steps controller
- L69 _private member_ `bool bIsActive = false;` — True if this tool is the active one in the panel
- L72 _private member_ `FLensInfo OriginalLensInfo;` — Original LensInfo, used to reset the details back to default
- L76 _private member_ `FLensInfo CachedLensInfo;` — `UPROPERTY(Transient)` — Cached previous LensInfo, used to trigger correct transactions to allow for undo operations

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/NodalOffsetTool.h` (Private)


#### struct `FNodalOffsetSessionInfo`  
`struct FNodalOffsetSessionInfo`  
_L20-30_
- desc: Data associated with a nodal offset calibration session
- L23 _public member_ `FDateTime StartTime;` — The date/time when the current calibration session started
- L26 _public member_ `int32 RowIndex = -1;` — The index of the next row in the current calibration session
- L29 _public member_ `bool bIsActive = false;` — True if a calibration session is currently in progress

#### class `UNodalOffsetTool`  
`class UNodalOffsetTool : public UCameraCalibrationStep`  
_L39-119_
- reflection: `UCLASS()`
- inherits: `UCameraCalibrationStep`
- desc: FNodalOffsetTool is the controller for the nodal offset tool panel. It has the logic to bridge user input like selection of nodal offset algorithm or CG camera with the actions that follow. It houses convenience functions used to generate the data of what is presented to the user, and holds pointers to the relevant objects and structures.
- L46 _public prototype_ `virtual void Initialize(TWeakPtr<FCameraCalibrationStepsController> InCameraCalibrationStepController) override;`
- L47 _public prototype_ `virtual void Shutdown() override;`
- L48 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L49 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L50 _public prototype_ `virtual bool OnViewportMarqueeSelect(FVector2D StartPosition, FVector2D EndPosition) override;`
- L51 _public prototype_ `virtual bool OnViewportInputKey(const FKey& InKey, const EInputEvent& InEvent) override;`
- L52 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L53 _public function_ `virtual FName FriendlyName() const override`
- L54 _public prototype_ `virtual bool DependsOnStep(UCameraCalibrationStep* Step) const override;`
- L55 _public prototype_ `virtual void Activate() override;`
- L56 _public prototype_ `virtual void Deactivate() override;`
- L57 _public prototype_ `virtual FCameraCalibrationStepsController* GetCameraCalibrationStepsController() const override;`
- L58 _public prototype_ `virtual bool IsActive() const override;`
- L59 _public prototype_ `virtual UMaterialInstanceDynamic* GetOverlayMID() const override;`
- L60 _public prototype_ `virtual bool IsOverlayEnabled() const override;`
- L64 _public prototype_ `void SetNodalOffsetAlgo(const FName& AlgoName);` — Selects the nodal offset algorithm by name
- L67 _public prototype_ `UCameraNodalOffsetAlgo* GetNodalOffsetAlgo() const;` — Returns the currently selected nodal offset algorithm
- L70 _public prototype_ `void OnSaveCurrentNodalOffset();` — Called by the UI when the user wants to save the nodal offset that the current algorithm is providing
- L73 _public prototype_ `void StartCalibrationSession();` — Initiate a new calibration session (if one is not already active)
- L76 _public prototype_ `void EndCalibrationSession();` — End the current calibration session
- L79 _public prototype_ `uint32 AdvanceSessionRowIndex();` — Increments the session index and returns its new value
- L82 _public prototype_ `void ExportSessionData(const TSharedRef<FJsonObject>& SessionDataObject);` — Intended to be called by one of the algo objects. Exports the data needed by the algo for the current session to a .json file on disk.
- L85 _public prototype_ `void ExportCalibrationRow(int32 RowIndex, const TSharedRef<FJsonObject>& RowObject, const FImageView& RowImage = FImageView());` — Intended to be called by one of the algo objects. Exports the data associated with a single calibration row to a .json file on disk.
- L88 _public prototype_ `void DeleteExportedRow(const int32& RowIndex) const;` — Intended to be called by one of the algo objects. Deletes the .json file with the input row index that was previously exported for this session.
- L91 _public prototype_ `void ImportCalibrationDataset();` — Import a saved calibration data set from disk
- L95 _private prototype_ `FString GetSessionSaveDir() const;` — Get the directory for the current session
- L98 _private prototype_ `FString GetRowFilename(int32 RowIndex) const;` — Get the filename of a row with the input index
- L102 _public member_ `FNodalOffsetSessionInfo SessionInfo;` — Stores info about the current calibration session of this tool
- L107 _private member_ `TWeakPtr<FCameraCalibrationStepsController> CameraCalibrationStepsController;` — Pointer to the calibration steps controller
- L111 _private member_ `TObjectPtr<UCameraNodalOffsetAlgo> NodalOffsetAlgo;` — `UPROPERTY()` — The currently selected nodal offset algorithm
- L115 _private member_ `TMap<FName, TObjectPtr<UMaterialInstanceDynamic>> AlgoOverlayMIDs;` — `UPROPERTY(Transient)` — Map of algo names to overlay MIDs used by those algos
- L118 _private member_ `bool bIsActive = false;` — True if this tool is the active one in the panel

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SCameraCalibrationCurveEditorPanel.h` (Private)


#### class `SCameraCalibrationCurveEditorPanel`  
`class SCameraCalibrationCurveEditorPanel : public SCurveEditorPanel`  
_L16-45_
- inherits: `SCurveEditorPanel`
- desc: Camera Calibration Curve editor widget that reflects the state of an FCurveEditor
- L19 _public function_ `SLATE_BEGIN_ARGS( SCameraCalibrationCurveEditorPanel )`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor, TWeakPtr<ITimeSliderController> InTimeSliderControllerWeakPtr);`
- L27 _public prototype_ `TSharedPtr<FExtender> GetToolbarExtender();` — Copied from SCurveEditorPanel in order to have custom order and custom buttons in toolbar
- L31 _private prototype_ `TSharedRef<SWidget> MakeViewModeMenu();` — Generate the View Mode dropdown toolbar widget
- L34 _private prototype_ `TSharedRef<SWidget> MakeCurveEditorCurveViewOptionsMenu();` — Generate the Curve View Options dropdown toolbar widget
- L37 _private prototype_ `TSharedRef<SWidget> MakeTimeSnapMenu();` — Generate the Time Snap dropdown toolbar widget
- L40 _private prototype_ `TSharedRef<SWidget> MakeGridSpacingMenu();` — Generate the Grid Spacing dropdown toolbar widget
- L44 _private member_ `TWeakPtr<FCurveEditor> CurveEditorWeakPtr;` — The curve editor pointer

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SCameraCalibrationCurveEditorView.h` (Private)


#### class `SCameraCalibrationCurveEditorView`  
`class SCameraCalibrationCurveEditorView : public SCurveEditorViewAbsolute`  
_L13-62_
- inherits: `SCurveEditorViewAbsolute`
- desc: A Camera Calibration curve view supporting custom context menu
- L15 _private typedef_ `using Super = SCurveEditorViewAbsolute;`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`
- L21 _public prototype_ `virtual bool IsTimeSnapEnabled() const override;`
- L26 _protected prototype_ `virtual void PaintView(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L31 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _private prototype_ `void CreateContextMenu(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);` — Create context menu for Editor View widget
- L39 _private prototype_ `FText GetToolTipTitleText() const;` — Get the title text to use in the curve tooltip
- L42 _private prototype_ `FText GetToolTipKeyText() const;` — Get the key text to use in the curve tooltip
- L45 _private prototype_ `FText GetToolTipValueText() const;` — Get the value text to use in the curve tooltip
- L49 _private member_ `TWeakPtr<IMenu> ActiveContextMenu;` — Track if we have a context menu active. Used to suppress hover updates as it causes flickers in the CanExecute bindings.
- L52 _private member_ `TSharedPtr<SToolTip> CameraCalibrationCurveToolTipWidget;` — Customized tooltip widget for use when hovering over camera calibration curves
- L55 _private member_ `TOptional<FText> CachedToolTipTitleText;` — Title text to use in the curve tooltip
- L58 _private member_ `TOptional<FText> CachedToolTipKeyText;` — Key text to use in the curve tooltip
- L61 _private member_ `TOptional<FText> CachedToolTipValueText;` — Value text to use in the curve tooltip

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SCameraCalibrationLinkedPointsDialog.h` (Private)


#### class `SCameraCalibrationLinkedPointsDialog`  
`class SCameraCalibrationLinkedPointsDialog : public SCompoundWidget`  
_L18-106_
- inherits: `SCompoundWidget`
- desc: A generic dialog box that displays all points linked to a specific point, allowing the user to apply a single operation to multiple linked points
- L53 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnApplyLinkedAction, const TArray<FLinkedItem>& );`
- L55 _public function_ `SLATE_BEGIN_ARGS(SCameraCalibrationLinkedPointsDialog) : _AcceptButtonText(NSLOCTEXT("SCameraCalibrationLinkedPointsDialog", "AcceptLabel", "Accept"))`
- L58 _public prototype_ `SLATE_ARGUMENT(ELinkedItemMode, LinkedItemMode) SLATE_ATTRIBUTE(FText, DialogText) SLATE_ATTRIBUTE(FText, AcceptButtonText) SLATE_EVENT(FOnApplyLinkedAction, OnApplyLinkedAction) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULensFile* InLensFile, const FLinkedItem& InInitialItem);`
- L73 _public prototype_ `static void OpenWindow(const FText& WindowTitle, const TSharedRef<SCameraCalibrationLinkedPointsDialog>& DialogBox);` — Open a new linked points window and block until the window is closed @param WindowTitle The title of the window @param DialogBox The dialog widget to display in the window
- L77 _private prototype_ `void UpdateLinkedItems();` — Rebuilds the list of linked items and refreshes the tree view
- L80 _private prototype_ `FReply OnAcceptButtonClicked();` — Raised when the accept button is clicked
- L83 _private prototype_ `FReply OnCancelButtonClicked();` — Raised when the cancel button is clicked
- L87 _private member_ `TWeakPtr<SWindow> WindowWeakPtr;` — Modal window pointer
- L90 _private member_ `TWeakObjectPtr<ULensFile> WeakLensFile = nullptr;` — LensFile we're editing
- L93 _private member_ `FLinkedItem InitialItem = FLinkedItem((ELensDataCategory)0, 0.0f);` — The item linked items are being found for
- L96 _private member_ `TArray<TSharedPtr<FLinkedTreeItem>> LinkedItems;` — A list of items that are linked
- L99 _private member_ `TSharedPtr<STreeView<TSharedPtr<FLinkedTreeItem>>> LinkedItemsTree;` — Tree widget to display the linked items
- L102 _private member_ `ELinkedItemMode LinkedItemMode = ELinkedItemMode::Both;` — The mode of the dialog box
- L105 _private member_ `FOnApplyLinkedAction OnApplyLinkedAction;` — Delegate to raise when the accept button is pressed and an action needs to be applied to each selected linked item

#### struct `SCameraCalibrationLinkedPointsDialog::FLinkedItem`  
`struct FLinkedItem`  
_L22-38_
- desc: An item within a lens data table that is linked to the current item
- L24 _public function_ `FLinkedItem(ELensDataCategory InCategory, float InFocus) : Category(InCategory) , Focus(InFocus)`
- L29 _public function_ `FLinkedItem(ELensDataCategory InCategory, float InFocus, float InZoom) : Category(InCategory) , Focus(InFocus) , Zoom(InZoom)`
- L35 _public member_ `ELensDataCategory Category = (ELensDataCategory)0;`
- L36 _public member_ `float Focus = 0.0f;`
- L37 _public member_ `TOptional<float> Zoom = TOptional<float>();`

#### enum `SCameraCalibrationLinkedPointsDialog::ELinkedItemMode`  
`enum class ELinkedItemMode : uint8`  
_L41-51_
- desc: Indicates the mode of the dialog box
- L44 _public enumerator_ `Focus` — Only linked focus items will be displayed and selected from
- L47 _public enumerator_ `Zoom` — Only linked zoom items will be displayed and selected from
- L50 _public enumerator_ `Both` — Both focus and zoom items will be displayed, and their selection state is coupled

#### Free symbols / members of external scopes

- L53 _delegate_ `DECLARE_DELEGATE_OneParam(FOnApplyLinkedAction, const TArray<FLinkedItem>& );`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SCameraCalibrationSteps.h` (Private)


#### class `SCameraCalibrationSteps`  
`class SCameraCalibrationSteps : public SCompoundWidget, public FGCObject`  
_L27-128_
- inherits: `SCompoundWidget,FGCObject`
- desc: UI for the nodal offset calibration. It also holds the UI given by the selected nodal offset algorithm.
- L38 _private function_ `SLATE_BEGIN_ARGS(SCameraCalibrationSteps)`
- L42 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCameraCalibrationStepsController> InCalibrationStepsController);`
- L46 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L47 _protected function_ `virtual FString GetReferencerName() const override`
- L56 _private prototype_ `TSharedRef<SWidget> BuildCameraPickerWidget();` — Builds the UI used to pick the camera used for the CG layer of the comp
- L59 _private prototype_ `TSharedRef<SWidget> BuildSimulcamWiperWidget();` — Builds the UI for the simulcam wiper
- L62 _private prototype_ `TSharedRef<SWidget> BuildMediaSourceTypeWidget();` — Builds the media source type picker
- L65 _private prototype_ `TSharedRef<SWidget> BuildMediaSourceWidget();` — Builds the UI for the media source picker
- L68 _private prototype_ `TSharedRef<SWidget> BuildMediaSourceAssetPicker();` — Builds an asset picker for media source assets
- L71 _private prototype_ `TSharedRef<SWidget> BuildMediaTextureAssetPicker();` — Builds an asset picker for media texture assets
- L74 _private prototype_ `TSharedRef<SWidget> BuildMediaProfileSourcePicker();` — Builds a combo box that displays the media source in the current media profile
- L77 _private prototype_ `TSharedRef<SWidget> BuildOverlayWidget();` — Builds the UI for the overlay picker
- L80 _private prototype_ `TSharedRef<SWidget> BuildStepSelectionWidget();` — Builds the UI for the calibration step selection
- L83 _private prototype_ `void UpdateOverlayMaterialParameterWidget();` — Updates the material parameter widget to display the parameters for the currently selected overlay
- L86 _private prototype_ `void SelectStep(const FName& StepName);` — Expected to be called when user selects a new step via the UI
- L89 _private prototype_ `EVisibility GetMediaPlaybackControlsVisibility() const;` — Determines the visibility of the media playback control buttons
- L94 _private member_ `TWeakPtr<class FCameraCalibrationStepsController> CalibrationStepsController;` — The controller object
- L97 _private member_ `EMediaSourceType MediaSourceType = EMediaSourceType::MediaProfile;` — The currently selected media source type
- L100 _private member_ `TArray<TWeakObjectPtr<UMediaSource>> MediaProfileSources;` — Options source for the MediaSourcesComboBox. Lists the currently available media sources
- L103 _private member_ `TSharedPtr<SComboBox<TWeakObjectPtr<UMediaSource>>> MediaProfileSourcesComboBox;` — The combobox that presents the available media sources
- L106 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> OverlayComboBox;` — The combox that presents the available overlays
- L109 _private member_ `TSharedPtr<SHorizontalBox> OverlayParameterWidget;` — The overlay parameter widget that displays a category name and the parameter list
- L112 _private member_ `TSharedPtr<SVerticalBox> OverlayParameterListWidget;` — The overlay parameter list widget that display the scalar and vector parameters for the currently select overlay
- L115 _private member_ `TArray<TSharedPtr<FName>> SharedOverlayNames;` — List of overlay names for the combox box options
- L118 _private member_ `TMap<FName, TObjectPtr<UMaterialInstanceDynamic>> OverlayMIDs;` — Map of overlay names to MIDs to use for those overlays
- L121 _private member_ `TObjectPtr<UMaterialInstanceDynamic> CurrentOverlayMID;` — Current overlay MID in use, set by the overlay combo box
- L124 _private member_ `TSharedPtr<SWidgetSwitcher> StepWidgetSwitcher;` — Widget switcher to only display the UI of the selected step
- L127 _private member_ `TMap<FName, TSharedPtr<SCheckBox>> StepToggles;` — Step selection buttons

#### enum `SCameraCalibrationSteps::EMediaSourceType`  
`enum class EMediaSourceType : uint8`  
_L30-36_
- desc: Type indicating the kind of media source the user can pick from
- L32 _public enumerator_ `MediaSource`
- L33 _public enumerator_ `MediaTexture`
- L34 _public enumerator_ `MediaProfile`
- L35 _public enumerator_ `None`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SImageCenterToolPanel.h` (Private)


#### class `SImageCenterToolPanel`  
`class SImageCenterToolPanel : public SCompoundWidget`  
_L18-55_
- inherits: `SCompoundWidget`
- desc: UI for the image center adjustment tool. It also holds the UI given by the selected image center algorithm.
- L20 _private function_ `SLATE_BEGIN_ARGS(SImageCenterToolPanel)`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, UImageCenterTool* InImageCenterTool);`
- L29 _private prototype_ `TSharedRef<SWidget> BuildImageCenterUIWrapper();` — Builds the wrapper for the currently selected iamge center UI
- L32 _private prototype_ `TSharedRef<SWidget> BuildImageCenterAlgoPickerWidget();` — Builds the UI for the image center algorithm picker
- L35 _private prototype_ `void UpdateImageCenterUI();` — Updates the UI so that it matches the selected image center algorithm (if necessary)
- L38 _private prototype_ `void UpdateAlgosOptions();` — Refreshes the list of available image center algorithms shown in the AlgosComboBox
- L43 _private member_ `TWeakObjectPtr<class UImageCenterTool> ImageCenterTool;` — The image center tool controller object
- L46 _private member_ `TSharedPtr<class SVerticalBox> ImageCenterUI;` — The box containing the UI given by the selected image center algorithm
- L51 _private member_ `TArray<TSharedPtr<FString>> CurrentAlgos;` — Options source for the AlgosComboBox. Lists the currently available image center algorithms
- L54 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> AlgosComboBox;` — The combobox that presents the available image center algorithms

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensDataAddPointDialog.h` (Private)


#### class `SLensDataAddPointDialog`  
`class SLensDataAddPointDialog : public SCompoundWidget`  
_L15-141_
- inherits: `SCompoundWidget`
- L18 _private typedef_ `using Super = SCompoundWidget;`
- L22 _public function_ `SLATE_BEGIN_ARGS(SLensDataAddPointDialog)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(FCachedFIZData, CachedFIZData) SLATE_EVENT(FSimpleDelegate, OnDataPointAdded) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULensFile* InLensFile, ELensDataCategory InitialDataCategory);` — FIZ data
- L35 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L38 _public prototype_ `static void OpenDialog(ULensFile* InLensFile, ELensDataCategory InitialDataCategory, TAttribute<FCachedFIZData> InCachedFIZData, const FSimpleDelegate& InOnDataPointAdded);` — Finds currently opened dialog window or spawns a new one
- L43 _private prototype_ `FReply OnAddDataPointClicked();` — Called when AddPoint button is clicked
- L46 _private prototype_ `FReply OnCancelDataPointClicked();` — Called when Cancel button is clicked
- L49 _private prototype_ `TSharedRef<SWidget> MakeTrackingDataWidget();` — Makes the different widgets used in this dialog
- L50 _private prototype_ `TSharedRef<SWidget> MakeLensDataWidget();`
- L51 _private prototype_ `TSharedRef<SWidget> MakeButtonsWidget();`
- L52 _private prototype_ `TSharedRef<SWidget> MakeDataCategoryMenuWidget();`
- L53 _private prototype_ `TSharedRef<SWidget> MakeEncoderMappingWidget();`
- L56 _private prototype_ `void SetDataCategory(ELensDataCategory NewCategory);` — Updates the desired data category
- L59 _private prototype_ `void CloseDialog();` — Closes this dialog
- L62 _private prototype_ `bool IsTrackingDataOverrided(int32 Index) const;` — Whether tracking data is overrided or not
- L65 _private prototype_ `void OnOverrideTrackingData(ECheckBoxState NewState, int32 Index);` — Triggered when override TrackingData state changes
- L68 _private prototype_ `float GetTrackingData(int32 Index) const;` — Gets tracking data for Index
- L71 _private prototype_ `void SetTrackingData(float Value, int32 Index);` — Updates tracking data for desired Index
- L74 _private prototype_ `void RefreshEvaluationData();` — Updates the current inputs values
- L77 _private prototype_ `void AddDataToLensFile() const;` — Called when ready to add data to LensFile
- L80 _private prototype_ `void OnUnitsChanged();` — Called when the display units are changed
- L83 _private prototype_ `FVector2D GetDefaultFocalLengthValue() const;` — Returns the default value to display for focal length based on the display units of the LensFile
- L86 _private prototype_ `FVector2D GetDefaultImageCenterValue() const;` — Returns the default value to display for image center based on the display units of the LensFile
- L89 _private prototype_ `void NormalizeValue(FVector2D& InputValue) const;` — Normalize the input value based on the display units of the LensFile
- L104 _private member_ `FTrackingInputData TrackingInputData[2];`
- L107 _private member_ `TStrongObjectPtr<ULensFile> LensFile;` — LensFile being edited
- L110 _private member_ `TSharedPtr<SBorder> TrackingDataContainer;` — Container for tracking inputs
- L113 _private member_ `TSharedPtr<SBorder> LensDataContainer;` — Container for lens data
- L116 _private member_ `ELensDataCategory SelectedCategory = ELensDataCategory::NodalOffset;` — Category of data being added
- L119 _private member_ `float EncoderMappingValue = 0.0f;` — When adding an encoder mapping value, float holding the current one
- L122 _private member_ `TSharedPtr<TStructOnScope<FImageCenterInfo>> ImageCenterData;` — ImageCenterData, valid for image center category
- L125 _private member_ `TSharedPtr<TStructOnScope<FFocalLengthInfo>> FocalLengthData;` — FocalLengthInfo, valid for distortion or focal length category
- L128 _private member_ `TSharedPtr<TStructOnScope<FDistortionInfoContainer>> DistortionInfoData;` — DistortionInfo, valid for distortion category
- L131 _private member_ `TSharedPtr<TStructOnScope<FNodalPointOffset>> NodalOffsetData;` — NodalOffset, valid for nodal offset category
- L134 _private member_ `TSharedPtr<TStructOnScope<FSTMapInfo>> STMapData;` — STMapInfo, valid for STMap category
- L137 _private member_ `TAttribute<FCachedFIZData> CachedFIZ;` — Evaluated FIZ for the current frame
- L140 _private member_ `FSimpleDelegate OnDataPointAdded;` — Delegate to call when point is added to LensFile

#### struct `SLensDataAddPointDialog::FTrackingInputData`  
`struct FTrackingInputData`  
_L98-103_
- desc: Used to build tracking input widget Depending on the category, there is either one input (Encoder) or two (Focus / Zoom)
- L100 _public member_ `FString Label;`
- L101 _public member_ `bool bIsOverrided = false;`
- L102 _public member_ `float Value = 0.0f;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensDataCategoryListItem.h` (Private)


#### class `FLensDataCategoryItem`  
`class FLensDataCategoryItem : public TSharedFromThis<FLensDataCategoryItem>`  
_L21-49_
- inherits: `TSharedFromThis<FLensDataCategoryItem>`
- desc: Data category item
- L24 _public prototype_ `FLensDataCategoryItem(ULensFile* InLensFile, TWeakPtr<FLensDataCategoryItem> Parent, ELensDataCategory InCategory, int32 InParameterIndex, FName InLabel);`
- L25 _public prototype_ `virtual ~FLensDataCategoryItem() = default;`
- L28 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable);` — Makes the widget for its associated row
- L33 _public member_ `ELensDataCategory Category;` — Category this item is associated with
- L36 _public member_ `int32 ParameterIndex = INDEX_NONE;` — Used to identify which parameter this represents
- L39 _public member_ `FName Label;` — Label of this category
- L42 _public member_ `TWeakPtr<FLensDataCategoryItem> Parent;` — WeakPtr to parent of this item
- L45 _public member_ `TArray<TSharedPtr<FLensDataCategoryItem>> Children;` — Children of this category
- L48 _public member_ `TWeakObjectPtr<ULensFile> LensFile;` — LensFile being edited

#### class `SLensDataCategoryItem`  
`class SLensDataCategoryItem : public STableRow<TSharedPtr<FLensDataCategoryItem>>`  
_L54-70_
- inherits: `STableRow<TSharedPtr<FLensDataCategoryItem>>`
- desc: Data category row widget
- L56 _private function_ `SLATE_BEGIN_ARGS(SLensDataCategoryItem)`
- L57 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FLensDataCategoryItem> InItemData);`
- L64 _private prototype_ `FText GetLabelText() const;` — Returns the label of this row
- L69 _private member_ `TWeakPtr<FLensDataCategoryItem> WeakItem;` — WeakPtr to source data item

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensDataEditPointDialog.h` (Private)


#### class `SLensDataEditPointDialog`  
`template<typename TStructType> class SLensDataEditPointDialog : public SCompoundWidget`  
_L29-276_
- inherits: `SCompoundWidget`
- desc: Editing Lens Point Dialog, it opens in separate dialog popup window
- L41 _public function_ `DECLARE_DELEGATE_ThreeParams(FOnSave, TSharedPtr<TStructOnScope<TStructType>> , TOptional<float> , TOptional<float> ) SLATE_BEGIN_ARGS(SLensDataEditPointDialog)` — Delegate for save struct on scope with specific struct type
- L45 _public function_ `SLATE_EVENT(FOnSave, OnSave) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULensFile* InLensFile, ELensDataCategory InCategory, TSharedPtr<TStructOnScope<TStructType>> InStructToEdit, float InFocus, float InZoom)`
- L149 _private function_ `TSharedRef<SWidget> MakeTrackingDataWidget()`
- L221 _private function_ `FReply OnSaveDataPointClicked() const` — Save Button handler
- L251 _private function_ `FReply OnCancelDataPointClicked() const` — Cancel Button handler
- L260 _private member_ `TStrongObjectPtr<ULensFile> LensFile;` — LensFile being edited
- L263 _private member_ `ELensDataCategory Category = ELensDataCategory::Focus;` — The category of the data struct being edited
- L266 _private member_ `TSharedPtr<TStructOnScope<TStructType>> StructToEdit;` — Editing Struct for visualize with StructureDetailsView
- L269 _private member_ `FTrackingInputData Focus;` — Focus of the data point being edited
- L272 _private member_ `FTrackingInputData Zoom;` — Zoom of the data point being edited
- L275 _private member_ `FOnSave OnSaveDelegate;` — On save struct delegate instance

#### struct `SLensDataEditPointDialog::FTrackingInputData`  
`struct FTrackingInputData`  
_L32-37_
- L34 _public member_ `float InitialValue = 0.0;`
- L35 _public member_ `float CurrentValue = 0.0;`
- L36 _public member_ `bool bIsOverridden = false;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "LensDataEditPointDialog"`
- L41 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSave, TSharedPtr<TStructOnScope<TStructType>> , TOptional<float> , TOptional<float> ) SLATE_BEGIN_ARGS(SLensDataEditPointDialog) {} SLATE_EVENT(FOnSave, OnSave) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULensFile* InLensFile, ELensDataCategory InCategory, TSharedPtr<TStructOnScope<TStructType>> InStructToEdit, float InFocus, float InZoom) { StructToEdit = InStructToEdit; LensFile = TStrongObjectPtr<ULensFile>(InLensFile); Category = InCategory; Focus.InitialValue = Focus.CurrentValue = InFocus; Zoom.InitialValue = Zoom.CurrentValue = InZoom; OnSaveDelegate = InArgs._OnSave; const TSharedPtr<SWidget> LensDataWidget = [this]() { TSharedPtr<SWidget> WidgetToReturn;` — Delegate for save struct on scope with specific struct type
- L58 _function_ `` (scope `SLensDataEditPointDialog::SLATE_EVENT`)
- L154 _function_ `` (scope `SLensDataEditPointDialog::MakeTrackingDataWidget`)
- L162 _function_ `.IsChecked_Lambda([&Data]() { return Data.bIsOverridden ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }) .OnCheckStateChanged(FOnCheckStateChanged::CreateLambda([&Data](ECheckBoxState NewState) { Data.bIsOverridden = NewState == ECheckBoxState::Checked; })) .ToolTipText(LOCTEXT("TrackingDataCheckboxTooltip", "Check to override incoming tracking data for this point")) ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) .Padding(4.f, 0.f, 0.f, 0.f) [ SNew(STextBlock) .Text(FText::FromString(Label)) ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) [ SNew(SNumericEntryBox<float>) .IsEnabled_Lambda([&Data](){ return Data.bIsOverridden; }) .Value_Lambda([&Data]() { return TOptional<float>(Data.CurrentValue); }) .OnValueChanged(SNumericEntryBox<float>::FOnValueChanged::CreateLambda([&Data](float NewValue) { Data.CurrentValue = NewValue; })) ];` (scope `SLensDataEditPointDialog::MakeTrackingDataWidget::__anonc38825e00302`)
- L163 _function_ `.OnCheckStateChanged(FOnCheckStateChanged::CreateLambda([&Data](ECheckBoxState NewState) { Data.bIsOverridden = NewState == ECheckBoxState::Checked; })) .ToolTipText(LOCTEXT("TrackingDataCheckboxTooltip", "Check to override incoming tracking data for this point")) ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) .Padding(4.f, 0.f, 0.f, 0.f) [ SNew(STextBlock) .Text(FText::FromString(Label)) ] + SHorizontalBox::Slot() .VAlign(VAlign_Center) [ SNew(SNumericEntryBox<float>) .IsEnabled_Lambda([&Data](){ return Data.bIsOverridden; }) .Value_Lambda([&Data]() { return TOptional<float>(Data.CurrentValue); }) .OnValueChanged(SNumericEntryBox<float>::FOnValueChanged::CreateLambda([&Data](float NewValue) { Data.CurrentValue = NewValue; })) ];` (scope `SLensDataEditPointDialog::MakeTrackingDataWidget::__anonc38825e00302`)
- L177 _function_ `.IsEnabled_Lambda([&Data](){ return Data.bIsOverridden; }) .Value_Lambda([&Data]() { return TOptional<float>(Data.CurrentValue); }) .OnValueChanged(SNumericEntryBox<float>::FOnValueChanged::CreateLambda([&Data](float NewValue) { Data.CurrentValue = NewValue; })) ];` (scope `SLensDataEditPointDialog::MakeTrackingDataWidget::__anonc38825e00302`)
- L178 _function_ `.Value_Lambda([&Data]() { return TOptional<float>(Data.CurrentValue); }) .OnValueChanged(SNumericEntryBox<float>::FOnValueChanged::CreateLambda([&Data](float NewValue) { Data.CurrentValue = NewValue; })) ];` (scope `SLensDataEditPointDialog::MakeTrackingDataWidget::__anonc38825e00302`)
- L179 _function_ `.OnValueChanged(SNumericEntryBox<float>::FOnValueChanged::CreateLambda([&Data](float NewValue) { Data.CurrentValue = NewValue; })) ];` (scope `SLensDataEditPointDialog::MakeTrackingDataWidget::__anonc38825e00302`)
- L278 _namespace_ `namespace LensDataEditPointDialog`
- L282 _function_ `template<typename TStructType, typename TableType> TSharedPtr<TStructOnScope<TStructType>> GetStructToEdit(const float InFocus, const float InZoom, const TableType& InTable)` (scope `LensDataEditPointDialog`) — Get specific struct for edit, based on Data Table Type
- L299 _function_ `template<typename TStructType, typename TableType> static void OpenDialog(ULensFile* InLensFile, ELensDataCategory InCategory, const float InFocus, const float InZoom, TableType& InTable, const FSimpleDelegate& OnPointSaved)` (scope `LensDataEditPointDialog`) — Finds currently opened dialog window or spawns a new one for editing
- L301 _typedef_ `using FOnSaveType = typename SLensDataEditPointDialog<TStructType>::FOnSave;` (scope `LensDataEditPointDialog::OpenDialog`)
- L302 _typedef_ `using FStructType = TSharedPtr<TStructOnScope<TStructType>>;` (scope `LensDataEditPointDialog::OpenDialog`)
- L306 _function_ `` (scope `LensDataEditPointDialog::OpenDialog`)

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensDataListItem.h` (Private)


#### enum `ELensDataChangedReason`  
`enum class ELensDataChangedReason : uint8`  
_L12-16_
- L14 _public enumerator_ `DataRemoved`
- L15 _public enumerator_ `DataChanged`

#### class `FLensDataListItem`  
`class FLensDataListItem : public TSharedFromThis<FLensDataListItem>`  
_L23-51_
- inherits: `TSharedFromThis<FLensDataListItem>`
- desc: Data entry item
- L26 _public prototype_ `FLensDataListItem(ULensFile* InLensFile, ELensDataCategory InCategory, int32 InSubCategoryIndex, FOnDataChanged InOnDataChangedCallback);`
- L28 _public prototype_ `virtual ~FLensDataListItem() = default;`
- L30 _public prototype_ `virtual void OnRemoveRequested() const = 0;`
- L31 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable) = 0;`
- L32 _public function_ `virtual TOptional<float> GetFocus() const`
- L33 _public function_ `virtual TOptional<float> GetZoom() const`
- L34 _public function_ `virtual int32 GetIndex() const`
- L35 _public function_ `virtual void EditItem()`
- L38 _public member_ `ELensDataCategory Category;` — Lens data category of that entry
- L41 _public member_ `int32 SubCategoryIndex;` — Used to know if it's a root category or not
- L44 _public member_ `TWeakObjectPtr<ULensFile> WeakLensFile;` — LensFile we're editing
- L47 _public member_ `TArray<TSharedPtr<FLensDataListItem>> Children;` — Children of this item
- L50 _public member_ `FOnDataChanged OnDataChangedCallback;` — Delegate to call when data is changed

#### class `FEncoderDataListItem`  
`class FEncoderDataListItem : public FLensDataListItem`  
_L56-69_
- inherits: `FLensDataListItem`
- desc: Encoder item
- L59 _public prototype_ `FEncoderDataListItem(ULensFile* InLensFile, ELensDataCategory InCategory, float InInput, int32 InIndex, FOnDataChanged InOnDataChangedCallback);`
- L61 _public prototype_ `virtual void OnRemoveRequested() const override;`
- L62 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable) override;`
- L65 _public member_ `float InputValue;` — Encoder input
- L68 _public member_ `int32 EntryIndex;` — Identifier for this focus point

#### class `FFocusDataListItem`  
`class FFocusDataListItem : public FLensDataListItem`  
_L74-96_
- inherits: `FLensDataListItem`
- desc: Data entry item
- L77 _public prototype_ `FFocusDataListItem(ULensFile* InLensFile, ELensDataCategory InCategory, int32 InSubCategoryIndex, float InFocus, FOnDataChanged InOnDataChangedCallback);`
- L79 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable) override;`
- L80 _public prototype_ `virtual void OnRemoveRequested() const override;`
- L81 _public function_ `virtual TOptional<float> GetFocus() const override`
- L84 _public prototype_ `bool OnFocusValueChanged(float NewFocusValue);` — Raised when the focus value is changed on this focus item
- L88 _public prototype_ `bool ChangeLinkedFocusValues(float NewFocusValue) const;` — Creates a dialog box that allows users to change linked focus values when this focus item is changed @returns true if the user presses the accept button on the dialog, false otherwise
- L92 _public prototype_ `bool RemoveLinkedFocusValues() const;` — Creates a dialog box that allows users to remove linked focus and zoom values when this focus item is removed @returns true if the user presses the accept button on the dialog, false otherwise
- L95 _public member_ `float Focus;` — Focus value of this item

#### class `FZoomDataListItem`  
`class FZoomDataListItem : public FLensDataListItem`  
_L101-130_
- inherits: `FLensDataListItem`
- desc: Zoom data entry item
- L104 _public prototype_ `FZoomDataListItem(ULensFile* InLensFile, ELensDataCategory InCategory, int32 InSubCategoryIndex, const TSharedRef<FFocusDataListItem> InParent, float InZoom, FOnDataChanged InOnDataChangedCallback);`
- L107 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable) override;`
- L108 _public prototype_ `virtual void OnRemoveRequested() const override;`
- L109 _public prototype_ `virtual TOptional<float> GetFocus() const override;`
- L110 _public function_ `virtual TOptional<float> GetZoom() const override`
- L111 _public prototype_ `virtual void EditItem() override;`
- L115 _public prototype_ `bool OnZoomValueChanged(float NewZoomValue);` — Raised when the zoom value is changed on this zoom item
- L119 _public prototype_ `bool ChangeLinkedZoomValues(float NewZoomValue) const;` — Creates a dialog box that allows users to change linked zoom values when this zoom item is changed @returns true if the user presses the accept button on the dialog, false otherwise
- L123 _public prototype_ `bool RemoveLinkedZoomValues() const;` — Creates a dialog box that allows users to remove linked zoom values when this zoom item is removed @returns true if the user presses the accept button on the dialog, false otherwise
- L126 _public member_ `float Zoom = 0.0f;` — Zoom value of this item
- L129 _public member_ `TWeakPtr<FFocusDataListItem> WeakParent;` — Focus this zoom point is associated with

#### class `SLensDataItem`  
`class SLensDataItem : public STableRow<TSharedPtr<FLensDataListItem>>`  
_L135-185_
- inherits: `STableRow<TSharedPtr<FLensDataListItem>>`
- desc: Widget a focus point entry
- L139 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnEntryValueChanged, float );` — Delegate raised when the entry value of the data item has been changed. Returns whether the change should be committed or not
- L141 _public function_ `SLATE_BEGIN_ARGS(SLensDataItem) : _EntryLabel(FText::GetEmpty()) , _EntryValue(0.f) , _AllowRemoval(false) , _EditPointVisibility(EVisibility::Collapsed) , _AllowEditPoint(false)`
- L149 _public prototype_ `SLATE_ARGUMENT(FText, EntryLabel) SLATE_ARGUMENT(float, EntryValue) SLATE_ARGUMENT(bool, AllowRemoval) SLATE_ARGUMENT(EVisibility, EditPointVisibility) SLATE_ATTRIBUTE(bool, AllowEditPoint) SLATE_ATTRIBUTE(bool, AllowEditEntryValue) SLATE_EVENT(FOnEntryValueChanged, OnEntryValueChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FLensDataListItem> InItemData);`
- L170 _private prototype_ `FReply OnEditPointClicked() const;` — Edit Button Handler
- L173 _private prototype_ `FReply OnRemovePointClicked() const;` — Remove Button Handler
- L175 _private prototype_ `void OnEntryValueCommitted(float NewValue, ETextCommit::Type CommitType);`
- L180 _private member_ `TWeakPtr<FLensDataListItem> WeakItem;` — WeakPtr to source data item
- L182 _private member_ `float EntryValue = 0.0;`
- L183 _private member_ `bool bIsCommittingValue = false;`
- L184 _private member_ `FOnEntryValueChanged OnEntryValueChanged;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnDataChanged, ELensDataChangedReason , float , TOptional<float> );`
- L18 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnDataChanged, ELensDataChangedReason , float , TOptional<float> );`
- L139 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnEntryValueChanged, float );` — Delegate raised when the entry value of the data item has been changed. Returns whether the change should be committed or not

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensDataViewer.h` (Private)


#### class `SLensDataViewer`  
`class SLensDataViewer : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L25-157_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Widget used to display data from the LensFile
- L28 _public function_ `SLATE_BEGIN_ARGS(SLensDataViewer)`
- L32 _public prototype_ `SLATE_ATTRIBUTE(FCachedFIZData, CachedFIZData) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ULensFile* InLensFile, const TSharedRef<FCameraCalibrationStepsController>& InCalibrationStepsController);` — FIZ data
- L39 _public prototype_ `TSharedPtr<FLensDataCategoryItem> GetDataCategorySelection() const;` — Get the currently selected data category.
- L42 _public prototype_ `TSharedRef<ITableRow> OnGenerateDataCategoryRow(TSharedPtr<FLensDataCategoryItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generates one data category row
- L45 _public prototype_ `void OnGetDataCategoryItemChildren(TSharedPtr<FLensDataCategoryItem> Item, TArray<TSharedPtr<FLensDataCategoryItem>>& OutChildren);` — Used to get the children of a data category item
- L48 _public prototype_ `void OnDataCategorySelectionChanged(TSharedPtr<FLensDataCategoryItem> Item, ESelectInfo::Type SelectInfo);` — Triggered when data category selection has changed
- L51 _public prototype_ `TSharedPtr<FLensDataListItem> GetSelectedDataEntry() const;` — Get the currently selected data entry
- L54 _public prototype_ `TSharedRef<ITableRow> OnGenerateDataEntryRow(TSharedPtr<FLensDataListItem> Node, const TSharedRef<STableViewBase>& OwnerTable);` — Generates one data entry row
- L57 _public prototype_ `void OnGetDataEntryChildren(TSharedPtr<FLensDataListItem> Node, TArray<TSharedPtr<FLensDataListItem>>& OutNodes);` — Used to get the children of a data entry item
- L60 _public prototype_ `void OnDataEntrySelectionChanged(TSharedPtr<FLensDataListItem> Node, ESelectInfo::Type SelectInfo);` — Triggered when data entry selection has changed
- L63 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L64 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L70 _private prototype_ `TSharedRef<SWidget> MakeLensDataWidget();` — Makes the widget showing lens data and curve editor
- L73 _private prototype_ `TSharedRef<SWidget> MakeToolbarWidget(TSharedRef<SCameraCalibrationCurveEditorPanel> InEditorPanel);` — Makes the Toolbar with data manipulation buttons
- L76 _private prototype_ `TSharedRef<SWidget> MakeCurveEditorToolbarWidget();` — Makes the toolbar for the curve editor, which sits on top of the curve editor
- L79 _private prototype_ `void OnAddDataPointHandler();` — Curve Editor add point delegate handler
- L82 _private prototype_ `FReply OnClearLensFileClicked();` — Called when user clicks on Clear LensFile button
- L85 _private prototype_ `void OnDataModeChanged();` — Called when DataMode is changed
- L88 _private prototype_ `void Refresh();` — Refreshes the widget's trees
- L91 _private prototype_ `void RefreshDataCategoriesTree();` — Refreshes data categories tree
- L94 _private prototype_ `void RefreshDataEntriesTree();` — Refreshes data entries tree
- L97 _private prototype_ `void RefreshCurve() const;` — Refreshes curve editor
- L100 _private prototype_ `void RefreshTimeSlider() const;` — Refreshes time slider controller
- L103 _private prototype_ `void OnLensDataPointAdded();` — Callbacked when user clicks AddPoint from the dialog
- L106 _private prototype_ `void OnDataPointChanged(ELensDataChangedReason ChangedReason, float InFocus, TOptional<float> InZoom);` — Callbacked when user changes anything about the data point that may require a refresh
- L109 _private prototype_ `void OnDataTablePointsUpdated(ELensDataCategory InCategory);` — Called when the data table points list of a data category was updated
- L112 _private prototype_ `void UpdateDataSelection(const TSharedPtr<FLensDataListItem>& PreviousSelection);` — Used to keep same selected data point when rebuilding tree
- L115 _private prototype_ `EVisibility GetCurveAxisButtonVisibility() const;` — Gets whether the axis selection buttons should be visible in the curve editor toolbar
- L120 _private member_ `TSharedPtr<STreeView<TSharedPtr<FLensDataCategoryItem>>> TreeView;` — Data category TreeView
- L123 _private member_ `TArray<TSharedPtr<FLensDataCategoryItem>> DataCategories;` — List of data category items
- L129 _private member_ `TSharedPtr<FLensDataCategoryItem> CachedSelectedCategoryItem;` — Cached selected item to detect category change If category hasn't changed, don't recreate data entries
- L132 _private member_ `TSharedPtr<STreeView<TSharedPtr<FLensDataListItem>>> DataEntriesTree;` — Data items associated with selected data category TreeView
- L135 _private member_ `TArray<TSharedPtr<FLensDataListItem>> DataEntries;` — List of data items for the selected data category
- L138 _private member_ `TSharedPtr<STextBlock> DataEntryNameWidget;` — Data entries title
- L141 _private member_ `TStrongObjectPtr<ULensFile> LensFile;` — LensFile being edited
- L144 _private member_ `TSharedPtr<FCameraCalibrationCurveEditor> CurveEditor;` — Curve editor manager and panel to display
- L147 _private member_ `TSharedPtr<SCameraCalibrationCurveEditorPanel> CurvePanel;` — Child class of curve editor panel
- L150 _private member_ `ELensCurveAxis CurveAxisType = (ELensCurveAxis)0;` — The current axis type to display in the curve editor
- L153 _private member_ `TAttribute<FCachedFIZData> CachedFIZ;` — Evaluated FIZ for the current frame
- L156 _private member_ `TWeakPtr<FCameraCalibrationTimeSliderController> TimeSliderControllerWeakPtr;` — Weak reference to Time Slider Controller

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensDistortionToolPanel.h` (Private)


#### class `FCaptureSettingsCustomization`  
`class FCaptureSettingsCustomization : public IDetailCustomization`  
_L21-37_
- inherits: `IDetailCustomization`
- desc: Customization for the FCaptureSettings struct
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L27 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L28 _private member_ `TSharedPtr<IPropertyHandle> NextPointPropertyHandle;`
- L30 _private prototype_ `FText GetNextPointName() const;`
- L32 _private prototype_ `void OnCalibratorSelected(const FAssetData& AssetData);`
- L34 _private prototype_ `bool DoesAssetHaveCalibrationComponent(const FAssetData& AssetData) const;`
- L36 _private prototype_ `FAssetData GetCalibratorAssetData() const;`

#### class `SCalibrationDatasetRow`  
`class SCalibrationDatasetRow : public SMultiColumnTableRow<TSharedPtr<FCalibrationRow>>`  
_L40-52_
- inherits: `SMultiColumnTableRow<TSharedPtr<FCalibrationRow>>`
- desc: Row widget for the calibration row list view
- L43 _public function_ `SLATE_BEGIN_ARGS(SCalibrationDatasetRow)`
- L44 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView, TSharedPtr<FCalibrationRow>& InRowData);`
- L48 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L51 _private member_ `TSharedPtr<FCalibrationRow> RowData;`

#### class `SLensDistortionToolPanel`  
`class SLensDistortionToolPanel : public SCompoundWidget`  
_L55-104_
- inherits: `SCompoundWidget`
- desc: UI for the Lens Distortion step
- L57 _private function_ `SLATE_BEGIN_ARGS(SLensDistortionToolPanel)`
- L61 _public prototype_ `void Construct(const FArguments& InArgs, ULensDistortionTool* InTool, TWeakPtr<FCameraCalibrationStepsController> InStepsController);`
- L64 _public prototype_ `void RefreshListView();` — Refresh the dataset list view
- L67 _public prototype_ `void Shutdown();` — Hides the modal progress window before the rest of the UI is destroyed
- L70 _public prototype_ `void OpenProgressWindow();` — Shows the modal progress window
- L73 _public prototype_ `void MarkProgressFinished();` — Enables the OkayButton in the progress window
- L75 _public prototype_ `void UpdateProgressText(const FText& ProgressText);`
- L79 _private prototype_ `void OnCaptureSettingsChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — Callback to handle changes to the customized capture settings
- L80 _private prototype_ `bool IsSolverSettingPropertyReadOnly(const FPropertyAndParent& PropertyAndParent) const;`
- L82 _private prototype_ `TSharedRef<SWidget> BuildDatasetListView();`
- L83 _private prototype_ `TSharedRef<ITableRow> OnGenerateDatasetRow(TSharedPtr<FCalibrationRow> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L84 _private prototype_ `FReply OnDatasetRowKeyPressed(const FGeometry& Geometry, const FKeyEvent& KeyEvent);`
- L86 _private prototype_ `FReply OnClearCalibrationRowsClicked();`
- L87 _private prototype_ `FReply OnImportDatasetClicked();`
- L88 _private prototype_ `FReply OnCalibrateClicked();`
- L90 _private prototype_ `void BuildProgressWindow();`
- L91 _private prototype_ `FReply OnOkPressed();`
- L92 _private prototype_ `FReply OnCancelPressed();`
- L95 _private member_ `TWeakObjectPtr<ULensDistortionTool> Tool;`
- L96 _private member_ `TWeakPtr<FCameraCalibrationStepsController> WeakStepsController;`
- L98 _private member_ `TSharedPtr<SListView<TSharedPtr<FCalibrationRow>>> DatasetListView;`
- L99 _private member_ `TSharedPtr<SHeaderRow> DatasetListHeader;`
- L101 _private member_ `TSharedPtr<SWindow> ProgressWindow;`
- L102 _private member_ `TSharedPtr<STextBlock> ProgressTextWidget;`
- L103 _private member_ `TSharedPtr<SButton> OkayButton;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensEvaluation.h` (Private)


#### class `SLensEvaluation`  
`class SLensEvaluation : public SCompoundWidget`  
_L21-101_
- inherits: `SCompoundWidget`
- desc: Widget using lens file evaluation inputs to evaluate lens file and show resulting data
- L23 _private typedef_ `using Super = SCompoundWidget;`
- L25 _public function_ `SLATE_BEGIN_ARGS(SLensEvaluation)`
- L29 _public prototype_ `~SLensEvaluation();`
- L31 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCameraCalibrationStepsController> StepsController, ULensFile* InLensFile);`
- L34 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L38 _public function_ `FCachedFIZData GetLastEvaluatedData() const` — Returns last raw and evaluated FIZ data
- L43 _private prototype_ `void CacheLensFileEvaluationInputs();` — Caches latest evaluation inputs and evaluates LensFile for FIZ
- L46 _private prototype_ `void CacheLensFileData();` — Evaluates LensFile using tracking data
- L49 _private prototype_ `FText GetTrackedCameraLabel() const;` — Get the name of the selected camera actor
- L52 _private prototype_ `FSlateColor GetTrackedCameraLabelColor() const;` — Get the text color for the tracked camera text
- L55 _private prototype_ `FText GetLensComponentLabel() const;` — Get the name of the lens component driving the selected camera
- L58 _private prototype_ `FSlateColor GetLensComponentLabelColor() const;` — Get the text color for the lens component text
- L61 _private prototype_ `TSharedRef<SWidget> MakeTrackingWidget();` — Make widget to display selected camera and lens component
- L64 _private prototype_ `TSharedRef<SWidget> MakeRawInputFIZWidget() const;` — Make Raw FIZ widget
- L67 _private prototype_ `TSharedRef<SWidget> MakeEvaluatedFIZWidget() const;` — Make Evaluated FIZ widget
- L70 _private prototype_ `void MakeDistortionWidget(const TSubclassOf<ULensModel>& LensModel);` — Make widget showing distortion data evaluated from LensFile
- L73 _private prototype_ `TSharedRef<SWidget> MakeIntrinsicsWidget() const;` — Make widget showing Intrinsic data evaluated from LensFile
- L76 _private prototype_ `TSharedRef<SWidget> MakeNodalOffsetWidget() const;` — Make widget showing NodalOffset data evaluated from LensFile
- L81 _private member_ `TStrongObjectPtr<ULensFile> LensFile;` — LensFile being edited
- L84 _private member_ `bool bCouldEvaluateDistortion = false;` — Flags used to know what data is valid or not and adjust UI
- L85 _private member_ `bool bCouldEvaluateFocalLength = false;`
- L86 _private member_ `bool bCouldEvaluateImageCenter = false;`
- L87 _private member_ `bool bCouldEvaluateNodalOffset = false;`
- L90 _private member_ `TWeakPtr<FCameraCalibrationStepsController> WeakStepsController;` — Calibration steps controller
- L93 _private member_ `FCachedFIZData CachedFIZData;` — Cached LensFile evaluated data
- L94 _private member_ `FDistortionInfo CachedDistortionInfo;`
- L95 _private member_ `FFocalLengthInfo CachedFocalLengthInfo;`
- L96 _private member_ `FImageCenterInfo CachedImageCenter;`
- L97 _private member_ `FNodalPointOffset CachedNodalOffset;`
- L100 _private member_ `TSharedPtr<SVerticalBox> DistortionWidget;` — Distortion Widget that displays the evaluated distortion parameters

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SLensFilePanel.h` (Private)


#### class `SLensFilePanel`  
`class SLensFilePanel : public SCompoundWidget`  
_L16-35_
- inherits: `SCompoundWidget`
- desc: Main panel of lens file editor
- L18 _private function_ `SLATE_BEGIN_ARGS(SLensFilePanel)`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, ULensFile* InLensFile, const TSharedRef<FCameraCalibrationStepsController>& InCalibrationStepsController);`
- L31 _private member_ `TStrongObjectPtr<ULensFile> LensFile;` — Holds the preset asset.
- L34 _private member_ `TAttribute<FCachedFIZData> CachedFIZ;` — Evaluated FIZ for the current frame

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SNodalOffsetToolPanel.h` (Private)


#### class `SNodalOffsetToolPanel`  
`class SNodalOffsetToolPanel : public SCompoundWidget`  
_L23-60_
- inherits: `SCompoundWidget`
- desc: UI for the nodal offset calibration. It also holds the UI given by the selected nodal offset algorithm.
- L25 _private function_ `SLATE_BEGIN_ARGS(SNodalOffsetToolPanel)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, UNodalOffsetTool* InNodalOffsetTool);`
- L34 _private prototype_ `TSharedRef<SWidget> BuildNodalOffsetUIWrapper();` — Builds the wrapper for the currently selected nodal offset UI
- L37 _private prototype_ `TSharedRef<SWidget> BuildNodalOffsetAlgoPickerWidget();` — Builds the UI for the nodal offset algorithm picker
- L40 _private prototype_ `void UpdateNodalOffsetUI();` — Updates the UI so that it matches the selected nodal offset algorithm (if necessary)
- L43 _private prototype_ `void UpdateAlgosOptions();` — Refreshes the list of available nodal offset algorithms shown in the AlgosComboBox
- L48 _private member_ `TWeakObjectPtr<class UNodalOffsetTool> NodalOffsetTool;` — The nodal offset tool controller object
- L51 _private member_ `TSharedPtr<class SVerticalBox> NodalOffsetUI;` — The box containing the UI given by the selected nodal offset algorithm
- L56 _private member_ `TArray<TSharedPtr<FString>> CurrentAlgos;` — Options source for the AlgosComboBox. Lists the currently available nodal offset algorithms
- L59 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> AlgosComboBox;` — The combobox that presents the available nodal offset algorithms

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/SSimulcamViewport.h` (Private)


#### class `SSimulcamViewport`  
`class SSimulcamViewport : public SCompoundWidget, public FSimulcamViewportElementsProvider`  
_L33-114_
- inherits: `SCompoundWidget,FSimulcamViewportElementsProvider`
- desc: Viewport that displays a level render from the perspective of a camera actor overlaid with a media texture overlay
- L36 _public function_ `SLATE_BEGIN_ARGS(SSimulcamViewport) : _ViewActor(nullptr), _FilmbackAspectRatio(1.0f), _MediaOverlayTexture(nullptr), _MediaOverlayOpacity(0.5f), _ToolOverlayMaterial(nullptr), _UserOverlayMaterial(nullptr), _OverrideTexture(nullptr), _WithZoom(true), _WithPan(true)`
- L48 _public prototype_ `SLATE_ATTRIBUTE(ACameraActor*, ViewActor) SLATE_ATTRIBUTE(float, FilmbackAspectRatio) SLATE_ATTRIBUTE(UTexture*, MediaOverlayTexture) SLATE_ATTRIBUTE(float, MediaOverlayOpacity) SLATE_ATTRIBUTE(UMaterialInterface*, ToolOverlayMaterial) SLATE_ATTRIBUTE(UMaterialInterface*, UserOverlayMaterial) SLATE_ARGUMENT(UTexture*, OverrideTexture) SLATE_EVENT(FSimulcamViewportClickedEventHandler, OnSimulcamViewportClicked) SLATE_EVENT(FSimulcamViewportInputKeyEventHandler, OnSimulcamViewportInputKey) SLATE_EVENT(FSimulcamViewportMarqueeSelectEventHandler, OnSimulcamViewportMarqueeSelect) SLATE_ATTRIBUTE(bool, WithZoom) SLATE_ATTRIBUTE(bool, WithPan) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L70 _public prototype_ `virtual ACameraActor* GetCameraActor() const override;`
- L71 _public prototype_ `virtual float GetCameraFeedAspectRatio() const override;`
- L72 _public prototype_ `virtual UTexture* GetMediaOverlayTexture() const override;`
- L73 _public prototype_ `virtual float GetMediaOverlayOpacity() const override;`
- L74 _public prototype_ `virtual UMaterialInterface* GetToolOverlayMaterial() const override;`
- L75 _public prototype_ `virtual UMaterialInterface* GetUserOverlayMaterial() const override;`
- L76 _public prototype_ `virtual UTexture* GetOverrideTexture() const override;`
- L77 _public function_ `virtual void OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent) override`
- L78 _public prototype_ `virtual bool OnViewportInputKey(const FKey& InKey, const EInputEvent& InInputEvent) override;`
- L79 _public function_ `virtual void OnMarqueeSelect(const FVector2D& InStartPosition, const FVector2D& InEndPosition) override`
- L84 _private member_ `TAttribute<ACameraActor*> ViewActor;` — The camera actor that the scene is rendering from
- L87 _private member_ `TAttribute<float> FilmbackAspectRatio;` — The aspect ratio of the camera's filmback
- L90 _private member_ `TAttribute<UTexture*> MediaOverlayTexture;` — The media texture to overlay onto the scene render
- L93 _private member_ `TAttribute<float> MediaOverlayOpacity;` — The opacity of the media overlay
- L96 _private member_ `TAttribute<UMaterialInterface*> ToolOverlayMaterial;` — The material to use to draw the tool overlay
- L99 _private member_ `TAttribute<UMaterialInterface*> UserOverlayMaterial;` — The material to use to draw the user overlay
- L102 _private member_ `TStrongObjectPtr<UTexture> OverrideTexture;` — An override texture that is displayed instead of the scene render and media overlay
- L105 _private member_ `FSimulcamViewportClickedEventHandler OnSimulcamViewportClicked;` — Delegate to be executed when the viewport area is clicked
- L108 _private member_ `FSimulcamViewportInputKeyEventHandler OnSimulcamViewportInputKey;` — Delegate to be executed when the viewport receives input key presses
- L111 _private member_ `FSimulcamViewportMarqueeSelectEventHandler OnSimulcamViewportMarqueeSelect;` — Delegate to be executed when the user performs a marquee selection on the viewport area
- L113 _private member_ `TSharedPtr<SSimulcamEditorViewport> TextureViewport;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FSimulcamViewportClickedEventHandler, const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);` — Delegate to be executed when the viewport area is clicked
- L22 _prototype_ `DECLARE_DELEGATE_TwoParams(FSimulcamViewportClickedEventHandler, const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);` — Delegate to be executed when the viewport area is clicked
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FSimulcamViewportInputKeyEventHandler, const FKey& Key, const EInputEvent& Event);` — Delegate to be executed when the viewport area receives a key event
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FSimulcamViewportInputKeyEventHandler, const FKey& Key, const EInputEvent& Event);` — Delegate to be executed when the viewport area receives a key event
- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FSimulcamViewportMarqueeSelectEventHandler, FVector2D StartPosition, FVector2D EndPosition);` — Delegate to be executed when the user performs a marquee selection on the viewport area
- L28 _prototype_ `DECLARE_DELEGATE_TwoParams(FSimulcamViewportMarqueeSelectEventHandler, FVector2D StartPosition, FVector2D EndPosition);` — Delegate to be executed when the user performs a marquee selection on the viewport area

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/Viewport/SSimulcamEditorViewport.h` (Private)


#### class `SSimulcamEditorViewport`  
`class SSimulcamEditorViewport : public SCompoundWidget`  
_L15-70_
- inherits: `SCompoundWidget`
- desc: Implements the texture editor's view port.
- L19 _public function_ `SLATE_BEGIN_ARGS(SSimulcamEditorViewport)`
- L28 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<SSimulcamViewport>& InSimulcamViewport, const bool bWithZoom, const bool bWithPan);` — Constructs the widget. @param InArgs The construction arguments.
- L31 _public prototype_ `void EnableRendering();` — Enable viewport rendering
- L33 _public prototype_ `void DisableRendering();` — Disable viewport rendering
- L36 _public prototype_ `TSharedPtr<FSceneViewport> GetViewport( ) const;` — Get the current SceneViewport
- L39 _public prototype_ `TSharedPtr<SViewport> GetViewportWidget( ) const;` — Get The SViewport Widget using this editor
- L42 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L51 _protected prototype_ `FText GetDisplayedResolution() const;` — Gets the displayed textures resolution as a string. @return Texture resolution string.
- L56 _private prototype_ `FText HandleZoomPercentageText( ) const;` — Callback for getting the zoom percentage text.
- L59 _private member_ `TWeakPtr<SSimulcamViewport> SimulcamViewportWeakPtr;`
- L62 _private member_ `TSharedPtr<FSimulcamEditorViewportClient> ViewportClient;` — Level viewport client.
- L64 _private member_ `TSharedPtr<FSceneViewport> Viewport;` — Slate viewport for rendering and IO.
- L66 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — Viewport widget.
- L69 _private member_ `bool bIsRenderingEnabled;` — Is rendering currently enabled? (disabled when reimporting a texture)

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/AssetEditor/Viewport/SimulcamEditorViewportClient.h` (Private)


#### class `FSimulcamViewportElementsProvider`  
`class FSimulcamViewportElementsProvider`  
_L16-30_
- desc: Interface used by the simulcam viewport client to retrieve any elements used for rendering the simulcam viewport
- L19 _public function_ `virtual ACameraActor* GetCameraActor() const`
- L20 _public function_ `virtual float GetCameraFeedAspectRatio() const`
- L21 _public function_ `virtual UTexture* GetMediaOverlayTexture() const`
- L22 _public function_ `virtual float GetMediaOverlayOpacity() const`
- L23 _public function_ `virtual UMaterialInterface* GetToolOverlayMaterial() const`
- L24 _public function_ `virtual UMaterialInterface* GetUserOverlayMaterial() const`
- L25 _public function_ `virtual UTexture* GetOverrideTexture() const`
- L27 _public function_ `virtual void OnViewportClicked(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)`
- L28 _public function_ `virtual bool OnViewportInputKey(const FKey& InKey, const EInputEvent& InInputEvent)`
- L29 _public function_ `virtual void OnMarqueeSelect(const FVector2D& InStartPosition, const FVector2D& InEndPosition)`

#### class `FSimulcamEditorViewportClient`  
`class FSimulcamEditorViewportClient : public FLevelEditorViewportClient`  
_L32-135_
- inherits: `FLevelEditorViewportClient`
- L36 _public member_ `static constexpr float MaxZoom = 16.0f;`
- L37 _public member_ `static constexpr float ZoomIncrement = 0.1f;`
- L41 _public prototype_ `FSimulcamEditorViewportClient(TSharedPtr<FSimulcamViewportElementsProvider> InElementsProvider, const bool bInWithZoom, const bool bInWithPan);` — Constructor
- L44 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — Begin FViewportClient interface
- L45 _public prototype_ `virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L46 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L47 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L48 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;`
- L49 _public prototype_ `virtual bool InputChar(FViewport* InViewport, int32 ControllerId, TCHAR Character) override;`
- L50 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& InEventArgs) override;`
- L51 _public prototype_ `virtual EMouseCursor::Type GetCursor(FViewport* InViewport, int32 X, int32 Y) override;`
- L52 _public prototype_ `virtual void MouseMove(FViewport* InViewport, int32 X, int32 Y) override;`
- L56 _public prototype_ `FText GetDisplayedResolution() const;` — Returns a string representation of the currently displayed textures resolution
- L59 _public prototype_ `float GetCurrentZoom() const;` — Gets the current zoom level of the view rectangle
- L62 _public prototype_ `float GetCurrentInvZoom() const;` — Gets the current inverse zoom level of the view rectangle
- L65 _public prototype_ `float GetMediaOverlayScale() const;` — Gets the amount that the media overlay texture is being scaled by, including zoom scaling
- L69 _private prototype_ `void PreDraw(FViewport* InViewport, FCanvas* Canvas);` — Performs any necessary processing needed before the viewport client renders
- L72 _private prototype_ `FVector2D GetMousePositionInMediaOverlaySpace() const;` — Gets the current mouse position in the pixel coordinates of the media overlay texture
- L75 _private prototype_ `FVector2D GetScaledMediaOverlayTextureSize() const;` — Gets the size the media overlay texture is being scaled to when displayed in the viewport
- L78 _private prototype_ `bool ShouldUseMousePanning(FViewport* InViewport) const;` — TRUE if right clicking and dragging for panning a texture 2D
- L81 _private prototype_ `float GetClampedHorizontalPanDelta(float MouseDelta);` — Converts a horizontal mouse delta in pixels and converts it to relative coordinates, clamping to ensure that the view rect stays bounded between 0.0 and 1.0
- L84 _private prototype_ `float GetClampedVerticalPanDelta(float MouseDelta);` — Converts a vertical mouse delta in pixels and converts it to relative coordinates, clamping to ensure that the view rect stays bounded between 0.0 and 1.0
- L86 _private prototype_ `void ChangeZoom(FViewport* InViewport, const FIntPoint& InMousePosition, float ZoomDelta);`
- L89 _private prototype_ `void ResetZoom();` — Zoom to fit the texture in the viewport
- L92 _private prototype_ `void ClampSelectionBoxSizeToTextureSize();` — Clamp the selection box size to only be large as the texture size
- L96 _private member_ `TWeakPtr<FSimulcamViewportElementsProvider> ElementsProvider;` — An interface that supplies all the necessary assets needed to render the simulcam viewport, and has handlers for various input events
- L99 _private member_ `TStrongObjectPtr<UMaterialInstanceDynamic> CropToViewRectMaterialInstance;` — Post process material to crop the viewport's output to the zoom/pan view rect
- L102 _private member_ `FIntPoint MousePosition = FIntPoint::ZeroValue;` — The position of the mouse within the viewport
- L105 _private member_ `FVector2D ViewportSize = FVector2D::ZeroVector;` — Cached viewport size, to keep track of when the viewport size has changed so various values can be recomputed
- L108 _private member_ `FVector2D CGViewportSize = FVector2D::ZeroVector;` — The size of the CG viewport when it is scaled down to fit within the media overlay
- L111 _private member_ `FBox2D ViewRect = FBox2D(FVector2D(0.0, 0.0), FVector2D(1.0, 1.0));` — Box that represents the portion of the texture and viewport the user is zoomed and panned to, in relative coordinates ((0, 0) is top left, (1, 1) is bottom right)
- L114 _private member_ `FVector2D MediaOverlayTextureOffset = FVector2D::ZeroVector;` — The offset from the viewport's top left corner that the media overlay texture must be placed to center it in the viewport
- L117 _private member_ `FVector2D MediaOverlayTexturePosition = FVector2D::ZeroVector;` — The position in pixel coordinates of the viewport at which the media overlay texture was last drawn
- L120 _private member_ `FIntPoint MediaOverlayTextureRawSize = FIntPoint::ZeroValue;` — The raw size of the media overlay texture
- L123 _private member_ `FVector2D MediaOverlayTextureScaledSize = FVector2D::ZeroVector;` — The size of the media overlay texture when scaled to fit inside the viewport
- L126 _private member_ `double MediaOverlayTextureScale = 1.0;` — The scale applied to the media overlay texture to match the rendered viewport size when the media overlay texture was last drawn
- L128 _private member_ `bool bWithZoom;`
- L129 _private member_ `bool bWithPan;`
- L131 _private member_ `bool bIsMarqueeSelecting = false;`
- L132 _private member_ `FVector2D SelectionStartTexture = FVector2D(0);`
- L133 _private member_ `FVector2D SelectionStartCanvas = FVector2D(0);`
- L134 _private member_ `FVector2D SelectionBoxSize = FVector2D(0);`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraCalibrationSolver.h` (Private)


#### struct `FObjectPoints`  
`struct FObjectPoints`  
_L24-31_
- reflection: `USTRUCT(BlueprintType)`
- desc: An array of 3D object points associated with a single calibration image. Structure is needed because Blueprints and Python do not support arrays of arrays.
- L30 _public member_ `TArray<FVector> Points;` — `UPROPERTY(BlueprintReadWrite, Category = "Calibration")` — 3D object points in an image

#### struct `FImagePoints`  
`struct FImagePoints`  
_L38-45_
- reflection: `USTRUCT(BlueprintType)`
- desc: An array of 2D image points associated with a single calibration image Structure is needed because Blueprints and Python do not support arrays of arrays.
- L44 _public member_ `TArray<FVector2D> Points;` — `UPROPERTY(BlueprintReadWrite, Category = "Calibration")` — 2D image points in an image

#### enum `ECalibrationFlags`  
`enum class ECalibrationFlags : uint32`  
_L51-63_
- reflection: `UENUM()`
- desc: Flags used to modify the execution of the calibration solver
- L53 _public enumerator_ `None = 0`
- L54 _public enumerator_ `UseIntrinsicGuess = 1 << 0`
- L55 _public enumerator_ `UseExtrinsicGuess = 1 << 1` — UseIntrinsicGuess = 1 << 0,    The solver will skip intrinsics initialization an use the input values of Focal Length and Image Center as the starting values for the optimization
- L56 _public enumerator_ `FixFocalLength = 1 << 2` — UseExtrinsicGuess = 1 << 1,    The solver will skip extrinsics initialization an use the input Camera Poses as the starting value for the optimization
- L57 _public enumerator_ `FixPrincipalPoint = 1 << 3` — FixFocalLength = 1 << 2,       The solver will not optimize the focal length
- L58 _public enumerator_ `FixExtrinsics = 1 << 4` — FixPrincipalPoint = 1 << 3,    The solver will not optimize the principal point
- L59 _public enumerator_ `FixDistortion = 1 << 5` — FixExtrinsics = 1 << 4,        The solver will not optimize the camera extrinsics
- L60 _public enumerator_ `FixAspectRatio = 1 << 6` — FixDistortion = 1 << 5,        The solver will fix all distortion values at 0
- L61 _public enumerator_ `SolveTargetOffset = 1 << 7` — FixAspectRatio = 1 << 6,       The solver will respect the input aspect ratio when solving for Fx and Fy
- L62 _public enumerator_ `GroupCameraPoses = 1 << 8` — SolveTargetOffset = 1 << 7,    The solver will solve for an offset for each image's input 3D object points

#### class `ULensDistortionSolver`  
`class ULensDistortionSolver : public UObject`  
_L69-138_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UObject`
- desc: Base lens distortion solver class that can be inherited from in Blueprints or Python
- L76 _public prototype_ `FDistortionCalibrationResult Solve( const TArray<FObjectPoints>& ObjectPointArray, const TArray<FImagePoints>& ImagePointArray, const FIntPoint ImageSize, const FVector2D& FocalLength, const FVector2D& ImageCenter, const TArray<float>& DistortionParameters, const TArray<FTransform>& CameraPoses, const TArray<FTransform>& TargetPoses, TSubclassOf<ULensModel> LensModel, double PixelAspect, ECalibrationFlags SolverFlags);` — `UFUNCTION(BlueprintNativeEvent, Category = "Calibration")` — Calibrate camera intrinsics and distortion from a set of input 3D-2D point correspondences and initial camera intrinsics guess.
- L91 _public prototype_ `FText GetDisplayName() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Calibration")` — Get the name of this solver class for displaying in the editor UI
- L95 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Calibration")` — Get the name of this solver class for displaying in the editor UI
- L99 _public prototype_ `bool GetStatusText(FText& OutStatusText);` — Get the latest status of the solve and marks the status as old. Returns true if this status was new, or false if this status was old.
- L102 _public function_ `void Cancel()` — Cancels the solve by setting bIsRunning to false, inidicating that the solver should stop executing the next time it checks IsRunning()
- L104 _public prototype_ `virtual FDistortionCalibrationResult Solve_Implementation( const TArray<FObjectPoints>& ObjectPointArray, const TArray<FImagePoints>& ImagePointArray, const FIntPoint ImageSize, const FVector2D& FocalLength, const FVector2D& ImageCenter, const TArray<float>& DistortionParameters, const TArray<FTransform>& CameraPoses, const TArray<FTransform>& TargetPoses, TSubclassOf<ULensModel> LensModel, double PixelAspect, ECalibrationFlags SolverFlags) PURE_VIRTUAL(ULensDistortionSolver::Solve_Implementation, return FDistortionCalibrationResult(););`
- L117 _public prototype_ `virtual FText GetDisplayName_Implementation() const PURE_VIRTUAL(ULensDistortionSolver::GetDisplayName_Implementation, return FText::GetEmpty(););`
- L119 _public function_ `virtual bool IsEnabled_Implementation() const`
- L124 _protected function_ `bool IsRunning() const` — `UFUNCTION(BlueprintCallable, Category = "Calibration")` — Returns true if the solver is currently running, and false if it has been cancelled. The solver should call this in critical loops in order to respond to cancellation requests.
- L127 _protected prototype_ `void SetStatusText(FText InStatusText);` — Sets the latest status text and marks bIsStatusNew to true
- L131 _protected member_ `std::atomic<bool> bIsRunning = true;` — True is the solver should continue executing. Set to false by Cancel(), indicating that the solver should early-out the next time it checks IsRunning()
- L134 _protected member_ `FText StatusText;` — Status text describing the current state of the solve
- L137 _protected member_ `bool bHasStatusChanged = false;` — Set to true by SetStatusText() when a new status is available. Set to false by GetStatusText(), indicating that the latest status has already been queried.

#### class `ULensDistortionSolverOpenCV`  
`class ULensDistortionSolverOpenCV : public ULensDistortionSolver`  
_L146-292_
- reflection: `UCLASS(meta = (DisplayName="OpenCV Solver"))`
- inherits: `ULensDistortionSolver`
- L155 _public prototype_ `virtual FDistortionCalibrationResult Solve_Implementation( const TArray<FObjectPoints>& ObjectPointArray, const TArray<FImagePoints>& ImagePointArray, const FIntPoint ImageSize, const FVector2D& FocalLength, const FVector2D& ImageCenter, const TArray<float>& DistortionParameters, const TArray<FTransform>& CameraPoses, const TArray<FTransform>& TargetPoses, TSubclassOf<ULensModel> LensModel, double PixelAspect, ECalibrationFlags SolverFlags) override;` — Calibrate camera intrinsics and distortion parameters using a set of input 3D and 2D point correspondences Returns the root mean reprojection error between the input image points and the projection of the input object points
- L168 _public prototype_ `virtual FText GetDisplayName_Implementation() const override;`
- L173 _private prototype_ `void InitCameraIntrinsics( const cv::Mat& ObjectPoints, const cv::Mat& ImagePoints, const cv::Mat& NumPoints, const cv::Size ImageSize, cv::Mat& CameraMatrix, bool bUseCanonicalPlaneInit);` — Initialize the camera matrix of intrinsic parameters using linear algebra techniques
- L182 _private prototype_ `void InitCameraExtrinsics( const TSubclassOf<ULensModel> LensModel, const cv::Mat& ObjectPoints, const cv::Mat& ImagePoints, const cv::Mat& CameraMatrix, const cv::Mat& DistCoeffs, const cv::Size ImageSize, cv::Mat& Rotation, cv::Mat& Translation, const ECalibrationFlags SolverFlags, bool bUseCanonicalPlaneInit);` — Initialize the camera extrinsics (rotation and translation vectors) for each image using linear algebra techniques
- L195 _private prototype_ `void ProjectPoints( const TSubclassOf<ULensModel> LensModel, const cv::Mat& ObjectPoints, const FTransform& TargetPose, const cv::Mat& ObjectPointOffsetRotation, const cv::Mat& ObjectPointOffsetTranslation, const cv::Mat& Rotation, const cv::Mat& Translation, const cv::Mat& CameraMatrix, const cv::Mat& DistCoeffs, const cv::Size ImageSize, cv::Mat& ProjectedPoints);` — Project the input object points to 2D using the input camera intrinsics, extrinsics, and distortion parameters
- L225 _private prototype_ `void ProjectPointsAnamorphic( const cv::Mat& ObjectPoints, const cv::Mat& Rotation, const cv::Mat& Translation, const cv::Mat& CameraMatrix, const cv::Mat& DistCoeffs, const cv::Size ImageSize, cv::Mat& ProjectedPoints, cv::Mat& Jacobian, ECalibrationFlags SolverFlags);` — Project the input object points to 2D using the input camera intrinsics, extrinsics, and anamorphic distortion parameters
- L237 _private prototype_ `void ProjectPointsSpherical( const cv::Mat& ObjectPoints, const FTransform& TargetPose, const cv::Mat& ObjectPointOffsetRotation, const cv::Mat& ObjectPointOffsetTranslation, const cv::Mat& Rotation, const cv::Mat& Translation, const cv::Mat& CameraMatrix, const cv::Mat& DistCoeffs, cv::Mat& ProjectedPoints, cv::Mat& Jacobian, ECalibrationFlags SolverFlags);` — Project the input object points to 2D using the input camera intrinsics, extrinsics, and spherical distortion parameters
- L251 _private prototype_ `void GatherPoints( const TArray<FObjectPoints>& InObjectPointsArray, const TArray<FImagePoints>& InImagePointsArray, cv::Mat& ObjectPointsMat, cv::Mat& ImagePointsMat);` — Copy the input 3D and 2D points to OpenCV matrices for ease of use with the solver
- L258 _private prototype_ `void SubdivideJacobian( const cv::Mat& Jacobian, cv::Mat& JacRotation, cv::Mat& JacTranslation, cv::Mat& JacFocalLength, cv::Mat& JacImageCenter, cv::Mat& JacObjectPointOffsetRotation, cv::Mat& JacObjectPointOffsetTranslation, cv::Mat& JacDistortion, ECalibrationFlags SolverFlags);` — Divide large jacobian matrix into smaller views for each of the parameter groups the solver will solve
- L270 _private prototype_ `void FindUniqueCameraPoses(const TArray<FTransform>& InCameraPoses, TArray<FTransform>& OutUniqueCameraPoses, TArray<int32>& OutUniquePoseIndices);` — Find the unique set of camera poses and the index into that set for each image
- L273 _private prototype_ `bool CanUseHomographyInitialization(const cv::Mat& ObjectPoints, double Tolerance = 1e-6);` — Check if the input points lie in a canonical plane suitable for homography
- L276 _private prototype_ `void InitIntrinsicsFromCanonicalPlane( const cv::Mat& ObjectPoints, const cv::Mat& ImagePoints, const cv::Mat& NumPoints, const cv::Size ImageSize, cv::Mat& CameraMatrix);` — Initialize camera intrinsics from 2D plane points using homography
- L284 _private prototype_ `void InitIntrinsicsFrom3DPoints( const cv::Mat& ObjectPoints, const cv::Mat& ImagePoints, const cv::Mat& NumPoints, const cv::Size ImageSize, cv::Mat& CameraMatrix);` — Initialize camera intrinsics from 3D world coordinates (not requiring canonical plane like homography)

#### class `FCameraCalibrationSolver`  
`class FCameraCalibrationSolver`  
_L294-306_
- L299 _public prototype_ `static double OptimizeNodalOffset( const TArray<TArray<FVector>>& InObjectPoints, const TArray<TArray<FVector2f>>& InImagePoints, const FVector2D& InFocalLength, const FVector2D& InImageCenter, const TArray<FTransform>& InCameraPoses, FTransform& InOutNodalOffset);` — Optimize the input nodal offset transform by running a downhill solver that attempts to minimize the reprojection error of the input points

#### class `FLevMarqSolver`  
`class FLevMarqSolver`  
_L311-387_
- desc: Levenberg–Marquardt solver for solving least-squares problems
- L330 _public prototype_ `FLevMarqSolver(int NumParamsToSolve, int NumErrors, int NumMaxIterations, ESymmetryMode SymmetryMode = ESymmetryMode::LowerToUpper);`
- L333 _public prototype_ `bool Update();` — Update the solver with the input jacobian and error matrices
- L336 _public prototype_ `bool UpdateAlt();` — Update the solver with the input pre-multiplied jacobian and error matrices
- L340 _private prototype_ `void Step();` — Step the solver, modifying the values of each of the parameters
- L343 _private prototype_ `void SubMatrix(const cv::Mat& Src, cv::Mat& Dst, const cv::Mat& Cols, const cv::Mat& Rows);` — Create a submatrix from the source matrix using only the columns and rows specified
- L347 _public member_ `cv::Mat Params;` — Parameters solved by this solver
- L350 _public member_ `cv::Mat Mask;` — Mask specifiying which parameters in the parameter list should not be modified
- L353 _public member_ `ESolverState State = ESolverState::Started;` — Current solver state
- L356 _public member_ `double ErrorNorm = 0;` — Average error for the current parameter set
- L359 _public member_ `cv::Mat Jacobian;` — Jacobian Matrix
- L362 _public member_ `cv::Mat Error;` — Error Matrix
- L365 _public member_ `cv::Mat JacTJac;` — Jacobian Transposed multiplied by the Jacobian
- L368 _public member_ `cv::Mat JacTErr;` — Jacobian Transposed multiplied by the Error
- L372 _private member_ `cv::Mat PreviousParams;` — Stores the previous values of each parameter
- L375 _private member_ `double PreviousErrorNorm = DBL_MAX;` — Previous average error
- L378 _private member_ `int MaxIterations = 0;` — Maximum number of iterations the solver will do
- L381 _private member_ `int Iterations = 0;` — Current number of iterations
- L384 _private member_ `ESymmetryMode SymmMode;` — Mode to use when copying half of the symmetric matrix
- L386 _private member_ `int LambdaLog10 = -3;`

#### enum `FLevMarqSolver::ESymmetryMode`  
`enum class ESymmetryMode : uint8`  
_L315-319_
- desc: Mode for copying the contents of symmetric matrix
- L317 _public enumerator_ `LowerToUpper`
- L318 _public enumerator_ `UpperToLower`

#### enum `FLevMarqSolver::ESolverState`  
`enum class ESolverState : uint8`  
_L322-328_
- desc: State used by the solver in its state machine
- L324 _public enumerator_ `Done = 0`
- L325 _public enumerator_ `Started = 1`
- L326 _public enumerator_ `ComputeJacobian = 2`
- L327 _public enumerator_ `CheckError = 3`

#### class `FOptimizeNodalOffsetSolver`  
`class FOptimizeNodalOffsetSolver : public cv::MinProblemSolver::Function`  
_L389-405_
- inherits: `cv::MinProblemSolver::Function`
- L394 _public prototype_ `int getDims() const;`
- L395 _public prototype_ `double calc(const double* x) const;`
- L399 _public member_ `FVector2D FocalLength;`
- L400 _public member_ `FVector2D ImageCenter;`
- L402 _public member_ `TArray<FTransform> CameraPoses;`
- L403 _public member_ `TArray<TArray<FVector>> Points3d;`
- L404 _public member_ `TArray<TArray<FVector2f>> Points2d;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraImageCenterAlgoManual.h` (Private)


#### class `UCameraImageCenterAlgoManual`  
`class UCameraImageCenterAlgoManual : public UCameraImageCenterAlgo`  
_L19-73_
- reflection: `UCLASS()`
- inherits: `UCameraImageCenterAlgo`
- desc: Implements an image center adjustment algorithm. The Manual algorithm simply takes manual input from the user and adjusts the image center by small increments
- L26 _public prototype_ `virtual void Initialize(UImageCenterTool* InImageCenterTool) override;`
- L27 _public prototype_ `virtual void Shutdown() override;`
- L28 _public prototype_ `virtual void Activate() override;`
- L29 _public prototype_ `virtual void Deactivate() override;`
- L30 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L31 _public prototype_ `virtual bool OnViewportInputKey(const FKey& InKey, const EInputEvent& InEvent) override;`
- L32 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L33 _public function_ `virtual FName FriendlyName() const override`
- L34 _public prototype_ `virtual bool HasImageCenterChanged() override;`
- L35 _public prototype_ `virtual void OnSavedImageCenter() override;`
- L40 _private prototype_ `TSharedRef<SWidget> BuildSensitivityWidget();` — Builds the UI of the sensitivity widget
- L43 _private prototype_ `void ApplyOrRevertAdjustedImageCenter();` — Open a dialog to let the user decide whether to save their adjustments or revert to the original state
- L48 _private member_ `FImageCenterInfo OriginalImageCenter;` — `UPROPERTY(Transient)` — Cached original image center that was evaluated at the current focus and zoom
- L52 _private member_ `FImageCenterInfo AdjustedImageCenter;` — `UPROPERTY(Transient)` — Latest image center that may have been adjusted by manual user input
- L56 _private member_ `TWeakObjectPtr<UImageCenterTool> Tool;` — The image center tool controller
- L59 _private member_ `TWeakObjectPtr<ULensFile> LensFile;` — The LensFile being edited
- L62 _private member_ `float CurrentEvalFocus;` — Cached focus and zoom that were used to evaluate the original image center
- L63 _private member_ `float CurrentEvalZoom;`
- L66 _private member_ `FIntPoint RenderTargetSize;` — Size of the render target displayed in the viewport
- L69 _private member_ `float AdjustmentIncrement = 0.5f;` — Increment (in pixels) that the image center will be adjusted by each individual key press
- L72 _private member_ `TArray<TSharedPtr<float>> SensitivtyOptions;` — Array of sensitivity options to display to the user to set the adjustement increment

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraNodalOffsetAlgoAruco.h` (Private)


#### class `UCameraNodalOffsetAlgoAruco`  
`class UCameraNodalOffsetAlgoAruco : public UCameraNodalOffsetAlgoPoints`  
_L16-44_
- reflection: `UCLASS()`
- inherits: `UCameraNodalOffsetAlgoPoints`
- desc: Implements a nodal offset calibration algorithm. It uses 3d points (UCalibrationPointComponent) specified in a selectable calibrator that should be named after the correponding Aruco markers.
- L23 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L25 _public function_ `virtual FName FriendlyName() const override`
- L26 _public function_ `virtual FName ShortName() const override`
- L27 _public prototype_ `virtual TSharedRef<SWidget> BuildHelpWidget() override;`
- L33 _protected member_ `bool bShouldShowDetectionWindow = false;` — True if a detection window should be shown after every capture
- L38 _protected prototype_ `TSharedRef<SWidget> BuildShowDetectionWidget();` — Builds the UI for the user to select if they want a detection window to be shown after every capture
- L43 _protected prototype_ `virtual bool PopulatePoints(FText& OutErrorMessage);` — Populates the calibration rows. True if successful.

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraNodalOffsetAlgoCharuco.h` (Private)


#### class `UCameraNodalOffsetAlgoCharuco`  
`class UCameraNodalOffsetAlgoCharuco : public UCameraNodalOffsetAlgoPoints`  
_L20-70_
- reflection: `UCLASS()`
- inherits: `UCameraNodalOffsetAlgoPoints`
- desc: Implements a nodal offset calibration algorithm based on a Charuco board. Charuco combines the benefits of checkerboard corners (high precision) with ArUco markers (robust detection and orientation).
- L27 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual bool OnViewportMarqueeSelect(FVector2D StartPosition, FVector2D EndPosition) override;`
- L29 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L30 _public function_ `virtual FName FriendlyName() const override`
- L31 _public function_ `virtual FName ShortName() const override`
- L32 _public prototype_ `virtual TSharedRef<SWidget> BuildHelpWidget() override;`
- L39 _protected prototype_ `virtual AActor* FindFirstCalibrator() const override;`
- L45 _protected prototype_ `TSharedRef<SWidget> BuildCharucoBoardPickerWidget();` — Builds the UI for the Charuco board picker
- L48 _protected prototype_ `TSharedRef<SWidget> BuildShowDetectionWidget();` — Builds the UI for showing/hiding detection visualization
- L51 _protected prototype_ `virtual bool PopulatePoints(FText& OutErrorMessage);` — Populates the calibration rows with detected Charuco corners. True if successful.
- L54 _protected prototype_ `virtual bool PopulatePoints(FText& OutErrorMessage, const FIntRect& ROI);` — Populates the calibration rows with detected Charuco corners using ROI. True if successful.
- L57 _protected prototype_ `void ShowDetectionVisualization(const FCharucoCorners& DetectedCorners, const TArray<FColor>& Image, FIntPoint ImageSize, const FIntRect& ROI = FIntRect());` — Shows a debug window with the detected corners and markers, optionally showing ROI
- L60 _protected prototype_ `void DrawROIRectangle(UTexture2D* DebugTexture, const FIntRect& ROI, FIntPoint ImageSize);` — Draws an ROI rectangle on the debug texture
- L66 _protected member_ `bool bShouldShowDetectionWindow = false;` — `UPROPERTY()` — True if a detection window should be shown after every capture
- L69 _protected member_ `FCharucoBoardConfig CachedBoardConfig;` — Cached Charuco board configuration from the selected board actor

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraNodalOffsetAlgoCheckerboard.h` (Private)


#### class `UCameraNodalOffsetAlgoCheckerboard`  
`class UCameraNodalOffsetAlgoCheckerboard : public UCameraNodalOffsetAlgoPoints`  
_L17-46_
- reflection: `UCLASS()`
- inherits: `UCameraNodalOffsetAlgoPoints`
- desc: Implements a nodal offset calibration algorithm based on a checkerboard. It requires the checkerboard to be upright in the image due to symmetry ambiguity.
- L24 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L25 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L26 _public function_ `virtual FName FriendlyName() const override`
- L27 _public function_ `virtual FName ShortName() const override`
- L28 _public prototype_ `virtual TSharedRef<SWidget> BuildHelpWidget() override;`
- L34 _protected prototype_ `virtual AActor* FindFirstCalibrator() const override;`
- L40 _protected prototype_ `TSharedRef<SWidget> BuildCheckerboardPickerWidget();` — Builds the UI of the checkerboard device picker
- L45 _protected prototype_ `virtual bool PopulatePoints(FText& OutErrorMessage);` — Populates the calibration rows. True if successful.

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraNodalOffsetAlgoManual.h` (Private)


#### class `UCameraNodalOffsetAlgoManual`  
`class UCameraNodalOffsetAlgoManual : public UCameraNodalOffsetAlgo`  
_L18-137_
- reflection: `UCLASS()`
- inherits: `UCameraNodalOffsetAlgo`
- desc: Nodal Offset "algo" for making manual adjustments to the nodal offset using location and rotation widgets
- L32 _public prototype_ `virtual void Initialize(UNodalOffsetTool* InNodalOffsetTool) override;`
- L33 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L34 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L36 _public function_ `virtual FName FriendlyName() const override`
- L41 _public function_ `virtual FName ShortName() const override`
- L46 _public prototype_ `virtual TSharedRef<SWidget> BuildHelpWidget() override;`
- L51 _protected prototype_ `TOptional<double> GetLocation(EAxis::Type Axis) const;` — Returns the value of the nodal offset's location offset for the given axis
- L54 _protected prototype_ `TOptional<double> GetRotation(EAxis::Type Axis) const;` — Returns the value of the nodal offset's rotation offset for the given axis
- L57 _protected prototype_ `void SetLocation(double NewValue, EAxis::Type Axis);` — Updates the value of the nodal offset's location offset for the given axis to the input value
- L60 _protected prototype_ `void SetRotation(double NewValue, EAxis::Type Axis);` — Updates the value of the nodal offset's rotation offset for the given axis to the input value
- L63 _protected prototype_ `void UpdateNodalOffset(FVector LocationOffset, FRotator RotationOffset);` — Updates the camera's pose by the new location and rotation offset and computes the new nodal offset that would get to the new camera pose
- L66 _protected prototype_ `void SaveNodalOffset(FNodalPointOffset NewNodalOffset);` — Saves the input nodal offset to the Lens File at the current Focus and Zoom
- L69 _protected prototype_ `void OnBeginSlider();` — Triggered when the user begins dragging any of the location/rotation sliders, caching the current camera pose and nodal offset, and beginning a new transaction
- L72 _protected prototype_ `void OnEndSlider(double NewValue);` — Triggered when the uesr releases any of the location/rotation sliders, ending the current transaction
- L75 _protected prototype_ `FReply OnUndoManualChanges();` — Reset the nodal offset at the current Focus and Zoom to their values before the user began making any manual adjustments
- L78 _protected prototype_ `FReply AddNodalPointAtEvalInputs();` — Add a new nodal offset point to the Lens File at the current Focus and Zoom
- L81 _protected prototype_ `TSharedRef<SWidget> BuildSensitivityWidget();` — Create the sensitivity checkbox widgets
- L84 _protected prototype_ `TSharedRef<SWidget> BuildLocationWidget();` — Create the location widget
- L87 _protected prototype_ `TSharedRef<SWidget> BuildRotationWidget();` — Create the roation widget
- L90 _protected prototype_ `EVisibility GetNodalPointVisibility(bool bShowIfNodalPointExists) const;` — Determines widget visibility based on whether there is a nodal offset point at the current Focus and Zoom
- L93 _protected prototype_ `bool DoesNodalPointExist() const;` — Returns true if there is a nodal offset point at the current Focus and Zoom
- L96 _protected prototype_ `double GetSensitivity() const;` — Returns a value corresponding to the currently selected sensitivity to drive the delta of the location and rotation sliders
- L99 _protected prototype_ `ECheckBoxState IsSensitivityOptionSelected(EAdjustmentSensitivity InSensitivity) const;` — Determines whether the input sensitivity option is currently selected
- L102 _protected prototype_ `void OnSensitivityChanged(ECheckBoxState CheckBoxState, EAdjustmentSensitivity InSensitivity);` — Changes the current adjustment sensitivity
- L105 _protected prototype_ `ACameraActor* GetCamera();` — Returns the camera actor that the nodal offset is being applied to
- L108 _protected prototype_ `FCameraCalibrationStepsController* GetStepsController();` — Returns the steps controller
- L112 _protected member_ `TWeakObjectPtr<UNodalOffsetTool> NodalOffsetTool;` — Weak pointer to the tool that created this algo
- L115 _protected member_ `FLensFileEvaluationInputs CachedEvalInputs;` — The most recent Focus and Zoom values used to evaluate the Lens File
- L118 _protected member_ `FNodalPointOffset StartingNodalOffset;` — The value of the nodal offset before the user begins to make any manual adjustments. This is reset any time the Focus and Zoom are changed.
- L121 _protected member_ `FNodalPointOffset CurrentNodalOffset;` — The current value of the nodal offset at the current Focus and Zoom
- L124 _protected member_ `FNodalPointOffset BaseNodalOffset;` — Cached value of the nodal offset immediately before an adjustment is made (or when the user begins dragging to slider) to compute the new nodal offset from the updated camera pose
- L127 _protected member_ `FTransform BaseCameraTransform;` — Cached value of the camera pose immediately before an adjustment is made (or when the user begins dragging to slider) to compute the new nodal offset from the updated camera pose
- L130 _protected member_ `bool bNodalPointExists = true;` — Whether there is a nodal offset point in the Lens File at the current Focus and Zoom
- L133 _protected member_ `bool bIsSliderMoving = false;` — Whether the user is currently moving any of the location/rotation sliders
- L136 _protected member_ `EAdjustmentSensitivity CurrentSensitivity;` — The current sensitivitiy, used to set the delta of the location/rotation sliders

#### enum `UCameraNodalOffsetAlgoManual::EAdjustmentSensitivity`  
`enum class EAdjustmentSensitivity : uint8`  
_L24-29_
- desc: Sensitivity options for interacting with the location and rotation widget sliders
- L26 _public enumerator_ `Fine`
- L27 _public enumerator_ `Medium`
- L28 _public enumerator_ `Coarse`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraNodalOffsetAlgoOpticalAxis.h` (Private)


#### class `UCameraNodalOffsetAlgoOpticalAxis`  
`class UCameraNodalOffsetAlgoOpticalAxis : public UCameraNodalOffsetAlgoPoints`  
_L22-107_
- reflection: `UCLASS()`
- inherits: `UCameraNodalOffsetAlgoPoints`
- desc: Implements a nodal offset calibration algorithm that relies on the idea that the nodal point of the lens lies along the optical axis of the lens, and that the optical axis can be found by finding multiple points in 3D that map to the principal point of the lens in 2D. The algorithm uses 3d points (UCalibrationPointComponent) specified in a selectable calibrator with features that the user can identify. By aligning that feature such that it projects to the principal point of the lens (easily identifiable using the automatically enabled crosshair overlay), the user captures two or more 3D points. The algorithm computes a line that connects those points, pointing away from the camera, which will be the optical axis. The nodal point is then found by moving the camera along that optical axis until the calibrator appears perfectly aligned in the composite image (CG + Media).
- L28 _public prototype_ `virtual void Initialize(UNodalOffsetTool* InNodalOffsetTool) override;`
- L29 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L30 _public prototype_ `virtual bool OnViewportInputKey(const FKey& InKey, const EInputEvent& InEvent) override;`
- L31 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L32 _public prototype_ `virtual bool GetNodalOffset(FNodalPointOffset& OutNodalOffset, float& OutFocus, float& OutZoom, float& OutError, FText& OutErrorMessage) override;`
- L33 _public function_ `virtual FName FriendlyName() const override`
- L34 _public function_ `virtual FName ShortName() const override`
- L35 _public prototype_ `virtual UMaterialInterface* GetOverlayMaterial() const override;`
- L36 _public prototype_ `virtual bool IsOverlayEnabled() const override;`
- L37 _public prototype_ `virtual TSharedRef<SWidget> BuildHelpWidget() override;`
- L42 _protected member_ `TOptional<FVector> OpticalAxis;` — The axis passing through the center of the lens, on which lies the nodal point
- L45 _protected member_ `FVector PointAlongAxis = FVector::ZeroVector;` — A point that lies along the optical axis (not necessarily the nodal point)
- L48 _protected member_ `FRotator LookAtRotation = FRotator::ZeroRotator;` — The rotation in which the camera is looking (along the optical axis)
- L52 _protected member_ `FNodalPointOffset AdjustedNodalOffset;` — `UPROPERTY(Transient)` — The current value of the nodal offset that has been written to the lens file, but not necessarily transacted
- L56 _protected member_ `FNodalPointOffset LastSavedNodalOffset;` — `UPROPERTY(Transient)` — The last nodal offset to have been saved and transacted
- L60 _protected member_ `float EntrancePupilPosition = 0.0f;` — `UPROPERTY(Transient)` — The parametric position along the optical axis where the nodal points sits
- L64 _protected member_ `float LastSavedEntrancePupilPosition = 0.0f;` — `UPROPERTY(Transient)` — The last entrance pupil position to have been saved and transacted
- L67 _protected member_ `FTransform CachedInverseCameraPose = FTransform::Identity;` — Cached inverse of the camera pose when the points were captured
- L70 _protected member_ `FTransform CachedNodalOffset = FTransform::Identity;` — Cached nodal offset of the camera when the points were captured
- L73 _protected member_ `float CachedFocus = 0.0f;` — Cached evaluated focus and zoom values when the points were captured
- L74 _protected member_ `float CachedZoom = 0.0f;`
- L78 _protected member_ `TObjectPtr<UTextureRenderTarget2D> OverlayTexture;` — `UPROPERTY(Transient)` — Texture used to draw the crosshair overlay
- L81 _protected member_ `float AdjustmentIncrement = 0.05f;` — Increment (in pixels) that the entrance pupil position will be adjusted by each individual key press
- L84 _protected member_ `TArray<TSharedPtr<float>> SensitivityOptions;` — Array of sensitivity options to display to the user to set the adjustment increment
- L87 _protected member_ `bool bFocusZoomWarningIssued = false;` — Used to avoid spamming the user with warnings about changing focus/zoom values
- L90 _protected member_ `FVector2D LastPrincipalPoint = FVector2D::ZeroVector;` — Used to track changes to the principal point so that the crosshair overlay can be updated
- L94 _protected prototype_ `TSharedRef<SWidget> BuildEntrancePupilPositionWidget();` — Build a widget that allows the user to manually enter a value for the entrance pupil position
- L97 _protected prototype_ `TSharedRef<SWidget> BuildSensitivityWidget();` — Builds the UI of the sensitivity widget
- L100 _protected prototype_ `FNodalPointOffset ComputeNodalOffset() const;` — Compute the nodal offset based on the cached data and the current entrance pupil position
- L103 _protected prototype_ `bool UpdateNodalOffset();` — Recomputes the nodal offset and updates the lens file table
- L106 _protected prototype_ `void SaveUpdatedNodalOffset();` — Modifies the Lens File so that there is a transaction associated with the most recent nodal offset update

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Calibrators/CameraNodalOffsetAlgoPoints.h` (Private)


#### struct `FNodalOffsetPointsCalibratorPointData`  
`struct FNodalOffsetPointsCalibratorPointData`  
_L30-45_
- reflection: `USTRUCT()`
- desc: Holds information of the identified calibrator 2d point for a given sample of a 2d-3d correlation
- L36 _public member_ `bool bIsValid = false;` — `UPROPERTY()` — True if the rest of the contents are valid.
- L40 _public member_ `FString Name;` — `UPROPERTY()` — The name of the 3d calibrator point, as defined in the mesh
- L44 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY()` — The world space 3d location of the point

#### struct `FNodalOffsetPointsCameraData`  
`struct FNodalOffsetPointsCameraData`  
_L49-108_
- reflection: `USTRUCT()`
- desc: Holds information of the camera pose for a given sample of a 2d-3d correlation
- L55 _public member_ `bool bIsValid = false;` — `UPROPERTY()` — True if the rest of the contents are valid.
- L59 _public member_ `uint32 UniqueId = INDEX_NONE;` — `UPROPERTY()` — The unique id of the camera object. Used to detect camera selection changes during a calibration session.
- L63 _public member_ `FTransform Pose = FTransform::Identity;` — `UPROPERTY()` — The camera pose
- L67 _public member_ `bool bWasNodalOffsetApplied = false;` — `UPROPERTY()` — True if the cached camera pose included a nodal offset
- L71 _public member_ `bool bWasDistortionEvaluated = false;` — `UPROPERTY()` — True if distortion was evaluated (using this LensFile)
- L75 _public member_ `float InputFocus = 0.0f;` — `UPROPERTY()` — Input focus from lens file evaluation data
- L79 _public member_ `float InputZoom = 0.0f;` — `UPROPERTY()` — Input zoom from lens file evaluation data
- L83 _public member_ `FTransform ParentPose = FTransform::Identity;` — `UPROPERTY()` — The parent pose (expected to be the tracker origin)
- L87 _public member_ `uint32 ParentUniqueId = INDEX_NONE;` — `UPROPERTY()` — The parent unique id
- L91 _public member_ `FTransform CalibratorPose = FTransform::Identity;` — `UPROPERTY()` — Calibrator Pose
- L95 _public member_ `FTransform CalibratorParentPose = FTransform::Identity;` — `UPROPERTY()` — Calibrator ParentPose
- L99 _public member_ `TMap<uint32, FTransform> CalibratorComponentPoses;` — `UPROPERTY()` — Calibrator ComponentPose
- L103 _public member_ `uint32 CalibratorUniqueId = INDEX_NONE;` — `UPROPERTY()` — Calibrator unique id
- L107 _public member_ `uint32 CalibratorParentUniqueId = INDEX_NONE;` — `UPROPERTY()` — Calibrator parent unique id

#### struct `FNodalOffsetPointsRowData`  
`struct FNodalOffsetPointsRowData`  
_L112-139_
- reflection: `USTRUCT()`
- desc: Holds information of the calibrator 3d point for a given sample of a 2d-3d correlation
- L118 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY()` — Index of this calibration row
- L122 _public member_ `FVector2f Point2D = FVector2f::ZeroVector;` — `UPROPERTY()` — Normalized 0~1 2d location of the identified calibrator point in the media plate.
- L126 _public member_ `FVector2f UndistortedPoint2D = FVector2f::ZeroVector;` — `UPROPERTY()` — Location of Point2D after it has been undistorted
- L130 _public member_ `bool bUndistortedIsValid = false;` — `UPROPERTY()` — True if this row has had its Point2D undistorted
- L134 _public member_ `FNodalOffsetPointsCalibratorPointData CalibratorPointData;` — `UPROPERTY()` — Holds information of the calibrator point data for this sample.
- L138 _public member_ `FNodalOffsetPointsCameraData CameraData;` — `UPROPERTY()` — Holds information of the camera data for this sample

#### class `UCameraNodalOffsetAlgoPoints`  
`class UCameraNodalOffsetAlgoPoints : public UCameraNodalOffsetAlgo`  
_L152-413_
- reflection: `UCLASS()`
- inherits: `UCameraNodalOffsetAlgo`
- desc: Implements a nodal offset calibration algorithm. It uses 3d points (UCalibrationPointComponent) specified in a selectable calibrator with features that the user can identify by clicking on the simulcam viewport, and after enough points have been identified, it can calculate the nodal offset that needs to be applied to the associated camera in order to align its CG with the live action media plate. Limitations: - Only supports Brown–Conrady model lens model (FSphericalDistortionParameters) - The camera or the lens should not be moved during the calibration of each nodal offset sample.
- L159 _public prototype_ `virtual void Initialize(UNodalOffsetTool* InNodalOffsetTool) override;`
- L160 _public prototype_ `virtual void Shutdown() override;`
- L161 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L162 _public prototype_ `virtual bool OnViewportClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L163 _public prototype_ `virtual TSharedRef<SWidget> BuildUI() override;`
- L164 _public prototype_ `virtual bool GetNodalOffset(FNodalPointOffset& OutNodalOffset, float& OutFocus, float& OutZoom, float& OutError, FText& OutErrorMessage) override;`
- L165 _public function_ `virtual FName FriendlyName() const override`
- L166 _public function_ `virtual FName ShortName() const override`
- L167 _public prototype_ `virtual void OnSavedNodalOffset() override;`
- L168 _public prototype_ `virtual bool HasCalibrationData() const override;`
- L169 _public prototype_ `virtual void PreImportCalibrationData() override;`
- L170 _public prototype_ `virtual int32 ImportCalibrationRow(const TSharedRef<FJsonObject>& CalibrationRowObject, const FImage& RowImage) override;`
- L171 _public prototype_ `virtual void PostImportCalibrationData() override;`
- L172 _public prototype_ `virtual TSharedRef<SWidget> BuildHelpWidget() override;`
- L193 _protected member_ `static const int DATASET_VERSION;` — Version of the current calibration dataset
- L196 _protected member_ `TWeakObjectPtr<UNodalOffsetTool> NodalOffsetTool;` — The nodal offset tool controller
- L199 _protected member_ `TWeakObjectPtr<AActor> Calibrator;` — The currently selected calibrator object. It is expected to contain one or more UCalibrationPointComponent in it
- L202 _protected member_ `TArray<TWeakObjectPtr<const UCalibrationPointComponent>> ActiveCalibratorComponents;` — Container for the set of calibrator components selected in the component combobox
- L205 _protected member_ `TArray<TSharedPtr<FCalibratorPointData>> CurrentCalibratorPoints;` — Options source for the CalibratorPointsComboBox. Lists the calibrator points found in the selected calibrator object
- L208 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FCalibratorPointData>>> CalibratorPointsComboBox;` — Allows the selection of calibrator point that will be visually identified in the simulcam viewport
- L211 _protected member_ `TArray<TSharedPtr<FNodalOffsetPointsRowData>> CalibrationRows;` — Rows source for the CalibrationListView
- L214 _protected member_ `TSharedPtr<SListView<TSharedPtr<FNodalOffsetPointsRowData>>> CalibrationListView;` — Displays the list of calibration points that will be used to calculate the nodal offset
- L217 _protected member_ `TArray<FNodalOffsetPointsCalibratorPointData> LastCalibratorPoints;` — Caches the last calibrator point 3d location.  Will hold last value before the nodal offset tool is paused
- L220 _protected member_ `FNodalOffsetPointsCameraData LastCameraData;` — Caches the last camera data.  Will hold last value before the nodal offset tool is paused
- L223 _protected member_ `static constexpr uint32 NumInlineAllocations = 32;` — Instructs the inline allocation policy how many elements to allocate in a single allocation
- L228 _protected prototype_ `TSharedRef<SWidget> BuildCalibrationDevicePickerWidget();` — Builds the UI of the calibration device picker
- L231 _protected prototype_ `TSharedRef<SWidget> BuildCalibrationComponentPickerWidget();` — Builds the UI of the calibration component picker
- L234 _protected prototype_ `TSharedRef<SWidget> BuildCalibrationPointsTable();` — Builds the UI of the calibration points table
- L237 _protected prototype_ `TSharedRef<SWidget> BuildCalibrationPointsComboBox();` — Buils the UI for selecting the current calibrator point
- L240 _protected prototype_ `TSharedRef<SWidget> BuildCalibrationActionButtons();` — Builds the UI for the action buttons (RemoveLast, ClearAll)
- L243 _protected prototype_ `TSharedRef<SWidget> BuildCalibrationComponentMenu();` — Builds the UI of the calibration component picker
- L248 _protected prototype_ `virtual AActor* FindFirstCalibrator() const;` — Returns the first calibrator object in the scene that it can find
- L251 _protected prototype_ `void SetCalibrator(AActor* InCalibrator);` — Sets the calibrator object to be used. Updates the selection picker.
- L254 _protected prototype_ `AActor* GetCalibrator() const;` — Returns the currently selected calibrator object.
- L257 _protected prototype_ `void ClearCalibrationRows();` — Clears the list of calibration sample rows
- L260 _protected prototype_ `void UndistortCalibrationRowPoints();` — Undistort the 2D points in each calibration row using the current distortion displacement map
- L270 _protected prototype_ `bool CalibratorPointCacheFromName(const FString& Name, FNodalOffsetPointsCalibratorPointData& CalibratorPointCache) const;` — Retrieves by name the calibration point data of the currently selected calibrator. @param Name The name of the point (namespaced if it is a subpoint). @param CalibratorPointCache This data structure will be populated with the information found. @return True if successful.
- L273 _protected prototype_ `bool GetCurrentCalibratorPointLocation(FVector& OutLocation);` — Returns the world 3d location of the currently selected calibrator
- L276 _protected prototype_ `bool AdvanceCalibratorPoint();` — Selects the next available UCalibrationPointComponent of the currently selected calibrator object. Returns true when it wraps around
- L279 _protected prototype_ `void OnCalibrationComponentSelected(const UCalibrationPointComponent* const SelectedComponent);` — Add or remove the selected component from the set of active components and refresh the calibrator point combobox
- L282 _protected prototype_ `bool IsCalibrationComponentSelected(const UCalibrationPointComponent* const SelectedComponent) const;` — Returns true if the input component is in the set of active calibration components
- L285 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Update any calibration components in the set of active components if they were replaced by an in-editor event
- L288 _protected prototype_ `virtual bool ValidateNewRow(TSharedPtr<FNodalOffsetPointsRowData>& Row, FText& OutErrorMessage) const;` — Validates a new calibration point to determine if it should be added as a new sample row
- L291 _protected prototype_ `bool ApplyNodalOffsetToCalibrator();` — Applies the nodal offset to the calibrator
- L294 _protected prototype_ `bool ApplyNodalOffsetToTrackingOrigin();` — Applies the nodal offset to the tracker origin (normally the camera parent)
- L297 _protected prototype_ `bool ApplyNodalOffsetToCalibratorParent();` — Applies the nodal offset to the parent of the calibrator
- L300 _protected prototype_ `bool ApplyNodalOffsetToCalibratorComponents();` — Applies the nodal offset to the parent of the calibrator
- L303 _protected prototype_ `bool BasicCalibrationChecksPass(const TArray<TSharedPtr<FNodalOffsetPointsRowData>>& Rows, FText& OutErrorMessage) const;` — Does basic checks on the data before performing the actual calibration
- L313 _protected prototype_ `bool GetStepsControllerAndLensFile(const FCameraCalibrationStepsController** OutStepsController, const ULensFile** OutLensFile) const;` — Gets the step controller and the lens file. @param OutStepsController Steps Controller @param OutLensFile Lens File @return True if successful
- L324 _protected prototype_ `bool CalculatedOptimalCameraComponentPose( FTransform& OutDesiredCameraTransform, const TArray<TSharedPtr<FNodalOffsetPointsRowData>>& Rows, FText& OutErrorMessage) const;` — Calculates the optimal camera component pose that minimizes the reprojection error @param OutDesiredCameraTransform The camera transform in world coordinates that minimizes the reprojection error. @param Rows Calibration samples. @param OutErrorMessage Documents any error that may have happened. @return True if successful.
- L341 _protected prototype_ `bool GetNodalOffsetSinglePose( FNodalPointOffset& OutNodalOffset, float& OutFocus, float& OutZoom, float& OutError, const TArray<TSharedPtr<FNodalOffsetPointsRowData>>& Rows, FText& OutErrorMessage) const;` — Calculates nodal offset based on a single camera pose @param OutNodalOffset Camera nodal offset @param OutFocus Focus distance associated with this nodal offset @param OutZoom Focal length associated with this nodal offset @param OutError Reprojection error @param Rows Calibration samples @param OutErrorMessage Describes any error that may have happened @return True if successful
- L355 _protected prototype_ `void GroupRowsByCameraPose( TArray<TSharedPtr<TArray<TSharedPtr<FNodalOffsetPointsRowData>>>>& OutSamePoseRowGroups, const TArray<TSharedPtr<FNodalOffsetPointsRowData>>& Rows) const;` — Groups the calibration samples by camera pose. @param OutSamePoseRowGroups Output array of arrays of samples, where the samples in each group have the same camera pose. @param Rows Ungrouped calibration samples.
- L366 _protected prototype_ `bool CalibratorMovedAcrossGroups(const TArray<TSharedPtr<TArray<TSharedPtr<FNodalOffsetPointsRowData>>>>& OutSamePoseRowGroups) const;` — Detects if the calibrator moved significantly in the given sample points @param OutSamePoseRowGroups Array of array of calibration samples. @return True if the calibrator moved significantly across all the samples.
- L375 _protected prototype_ `bool CalibratorMovedInAnyRow(const TArray<TSharedPtr<FNodalOffsetPointsRowData>>& Rows) const;` — Detects if the calibrator moved significantly in the given sample points @param Rows Array of calibration samples. @return True if the calibrator moved significantly across all the samples.
- L386 _protected prototype_ `bool CalcTrackingOriginPoseForSingleCamPose( const TArray<TSharedPtr<FNodalOffsetPointsRowData>>& Rows, FTransform& OutTransform, FText& OutErrorMessage);` — Calculates the optimal camera parent transform that minimizes the reprojection of the sample points. @param Rows The calibration points @param OutTransform The optimal camera parent transform @param OutErrorMessage Describes any errors encountered @return True if successful
- L400 _protected prototype_ `bool CalcCalibratorPoseForSingleCamPose( const TArray<TSharedPtr<FNodalOffsetPointsRowData>>& Rows, FTransform& OutTransform, FText& OutErrorMessage);` — Calculates the optimal calibrator transform that minimizes the reprojection of the sample points. @param Rows The calibration points @param OutTransform The optimal calibrator transform @param OutErrorMessage Describes any errors encountered @return True if successful
- L406 _protected prototype_ `double MinimizeReprojectionError(FTransform& InOutNodalOffset, const TArray<TSharedPtr<TArray<TSharedPtr<FNodalOffsetPointsRowData>>>>& SamePoseRowGroups) const;` — Refine the input nodal offset by running a minimization algorithm designed to minimize the sum of the reprojection errors for the camera views in the set of input pose groups
- L409 _protected prototype_ `void ExportSessionData();` — Export global session data to a .json file
- L412 _protected prototype_ `void ExportRow(TSharedPtr<FNodalOffsetPointsRowData> Row);` — Export the row data to a json file

#### struct `UCameraNodalOffsetAlgoPoints::FCalibratorPointData`  
`struct FCalibratorPointData`  
_L181-189_
- desc: Holds item information a given calibrator point in the calibrator model
- L183 _public function_ `FCalibratorPointData(FString& InName) : Name(InName)`
- L188 _public member_ `FString Name;` — Name of the calibrator 3d point, as defined in the mesh

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace CameraNodalOffsetAlgoPoints`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/CameraCalibrationEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraCalibrationEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraCalibrationEditor, Log, All);`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/CameraCalibrationEditorModule.h` (Private)


#### class `FCameraCalibrationEditorModule`  
`class FCameraCalibrationEditorModule : public IModuleInterface`  
_L17-58_
- inherits: `IModuleInterface`
- desc: Implements the CameraCalibrationEditor module.
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _private prototype_ `void RegisterPlacementModeItems();` — Register items to show up in the Place Actors panel.
- L32 _private prototype_ `void UnregisterPlacementModeItems();` — Unregister items in Place Actors panel
- L35 _private prototype_ `void RegisterOverlayMaterials();` — Register overlay materials to use in the calibration tool
- L38 _private prototype_ `void UnregisterOverlayMaterials();` — Unregister overlay materials
- L41 _private prototype_ `void RegisterCharucoBoardTextureGenerator();` — Register Charuco board texture generator with the calibration subsystem
- L44 _private prototype_ `void UnregisterCharucoBoardTextureGenerator();` — Unregister Charuco board texture generator
- L47 _private prototype_ `const FPlacementCategoryInfo* GetVirtualProductionCategoryRegisteredInfo() const;` — Gathers the Info on the Virtual Production Place Actors Category
- L51 _private member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;`
- L52 _private member_ `FDelegateHandle PostEngineInitHandle;`
- L53 _private member_ `FDelegateHandle PostEngineInitHandle_PlacementMode;`
- L54 _private member_ `FDelegateHandle PostEngineInitHandle_OverlayMaterials;`
- L55 _private member_ `FDelegateHandle PostEngineInitHandle_CharucoGenerator;`
- L57 _private member_ `TArray<TOptional<FPlacementModeID>> PlaceActors;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/CameraCalibrationUtilsPrivate.h` (Private)


#### struct `FArucoCalibrationPoint`  
`struct FArucoCalibrationPoint`  
_L17-36_
- reflection: `USTRUCT()`
- desc: Structure representing an aruco marker, including ID, Name, and corner coordinates in 2D image space and 3D world space
- L23 _public member_ `FVector Corners3D[4] = { FVector::ZeroVector, FVector::ZeroVector, FVector::ZeroVector, FVector::ZeroVector };` — `UPROPERTY()` — 3D locations (in world space) of each corner
- L27 _public member_ `FVector2f Corners2D[4] = { FVector2f::ZeroVector, FVector2f::ZeroVector, FVector2f::ZeroVector, FVector2f::ZeroVector };` — `UPROPERTY()` — 2D locations (in pixels) of each corner
- L31 _public member_ `int32 MarkerID = -1;` — `UPROPERTY()` — Aruco Marker ID
- L35 _public member_ `FString Name;` — `UPROPERTY()` — Name of the marker (follows the naming convention of "[DictionaryName]-[MarkerID]")

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace CameraCalibration` (scope `UE`)
- L38 _namespace_ `namespace Private` (scope `UE::CameraCalibration`)
- L41 _prototype_ `EArucoDictionary GetArucoDictionaryForCalibrator(AActor* CalibratorActor);` (scope `UE::CameraCalibration::Private`) — Returns the aruco dictionary that matches the calibration point component(s) of the input calibrator actor
- L44 _prototype_ `EArucoDictionary GetArucoDictionaryFromName(FString Name);` (scope `UE::CameraCalibration::Private`) — Get the aruco dictionary from a string representation matching the dictionary name
- L47 _prototype_ `FString GetArucoDictionaryName(EArucoDictionary Dictionary);` (scope `UE::CameraCalibration::Private`) — Get the string representation of the input aruco dictionary
- L50 _function_ `inline EArucoDictionary ShadowToOpenCV(EArucoDictionaryShadow Shadow)` (scope `UE::CameraCalibration::Private`) — Convert shadow enum to OpenCV enum
- L56 _function_ `inline EArucoDictionaryShadow OpenCVToShadow(EArucoDictionary OpenCV)` (scope `UE::CameraCalibration::Private`) — Convert OpenCV enum to shadow enum
- L62 _prototype_ `void FindActorsWithCalibrationComponents(TArray<AActor*>& ActorsWithCalibrationComponents);` (scope `UE::CameraCalibration::Private`) — Find all actors in the current world that have a calibration point component attached (excluding CDOs and actors in levels that are not currently visible)
- L65 _prototype_ `bool FindArucoCalibrationPoint(const TArray<TWeakObjectPtr<UCalibrationPointComponent>>& CalibrationComponents, EArucoDictionary ArucoDictionary, const FArucoMarker& ArucoMarker, FArucoCalibrationPoint& OutArucoCalibrationPoint);` (scope `UE::CameraCalibration::Private`) — Find an aruco marker calibration point in one of the input calibration components that matches the input dictionary and marker ID
- L68 _prototype_ `void ClearTexture(UTexture2D* Texture, FColor ClearColor = FColor::Transparent);` (scope `UE::CameraCalibration::Private`) — Set every pixel in the input texture to the clear color
- L71 _prototype_ `void SetTextureData(UTexture2D* Texture, const TArray<FColor>& PixelData);` (scope `UE::CameraCalibration::Private`) — Set the texture data to the input array of pixels
- L74 _prototype_ `void GroupPointsByCameraPose(TArray<FObjectPoints>& InOutObjectPoints, TArray<FImagePoints>& InOutImagePoints, TArray<FTransform>& InOutCameraPoses);` (scope `UE::CameraCalibration::Private`) — Group the input points together if they share the same camera pose, and output the unique camera poses

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Exporters/LensFileExporter.h` (Private)


#### class `ULensFileExporter`  
`class ULensFileExporter : public UExporter`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L18 _private prototype_ `bool ExportText(const class FExportObjectInnerContext* Context, UObject* Object, const TCHAR* Type, FOutputDevice& Ar, FFeedbackContext* Warn, uint32 PortFlags ) override;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Factories/LensFileFactoryNew.h` (Private)


#### class `ULensFileFactoryNew`  
`class ULensFileFactoryNew : public UFactory`  
_L15-28_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for ULensFile objects.
- L21 _public prototype_ `ULensFileFactoryNew();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L26 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/Factories/LensFileImporterFactory.h` (Private)


#### class `ULensFileImporterFactory`  
`class ULensFileImporterFactory : public UFactory , public FReimportHandler`  
_L11-40_
- reflection: `UCLASS()`
- inherits: `UFactory,FReimportHandler`
- L18 _public prototype_ `ULensFileImporterFactory(const FObjectInitializer& ObjectInitializer);`
- L23 _protected prototype_ `virtual FText GetToolTip() const override;`
- L24 _protected prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L25 _protected prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;`
- L29 _protected prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L30 _protected prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L31 _protected prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L33 _protected function_ `virtual TObjectPtr<UObject>* GetFactoryObject() const override`
- L38 _protected member_ `mutable TObjectPtr<UObject> GCMark{this};`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/LensFileExchangeFormat.h` (Private)


#### enum `ELensFileUnit`  
`enum class ELensFileUnit`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `Millimeters`
- L14 _public enumerator_ `Normalized`

#### enum `ENodalOffsetCoordinateSystem`  
`enum class ENodalOffsetCoordinateSystem`  
_L18-21_
- reflection: `UENUM()`
- L20 _public enumerator_ `OpenCV`

#### struct `FLensInfoExchange`  
`struct FLensInfoExchange`  
_L24-38_
- reflection: `USTRUCT()`
- L28 _public prototype_ `FLensInfoExchange(const class ULensFile* LensFile = nullptr);`
- L31 _public member_ `FName SerialNumber;` — `UPROPERTY()`
- L34 _public member_ `FName ModelName;` — `UPROPERTY()`
- L37 _public member_ `FName DistortionModel;` — `UPROPERTY()`

#### struct `FLensFileUserMetadataEntry`  
`struct FLensFileUserMetadataEntry`  
_L41-50_
- reflection: `USTRUCT()`
- L46 _public member_ `FName Name;` — `UPROPERTY()`
- L49 _public member_ `FName Value;` — `UPROPERTY()`

#### struct `FLensFileMetadata`  
`struct FLensFileMetadata`  
_L53-82_
- reflection: `USTRUCT()`
- L57 _public prototype_ `FLensFileMetadata(const class ULensFile* LensFile = nullptr);`
- L60 _public member_ `FName Type;` — `UPROPERTY()`
- L63 _public member_ `FName Version;` — `UPROPERTY()`
- L66 _public member_ `FLensInfoExchange LensInfo;` — `UPROPERTY()`
- L69 _public member_ `FName Name;` — `UPROPERTY()`
- L72 _public member_ `ENodalOffsetCoordinateSystem NodalOffsetCoordinateSystem = ENodalOffsetCoordinateSystem::OpenCV;` — `UPROPERTY()`
- L75 _public member_ `ELensFileUnit FxFyUnits = ELensFileUnit::Normalized;` — `UPROPERTY()`
- L78 _public member_ `ELensFileUnit CxCyUnits = ELensFileUnit::Normalized;` — `UPROPERTY()`
- L81 _public member_ `TArray<FLensFileUserMetadataEntry> UserMetadata;` — `UPROPERTY()`

#### struct `FLensFileSensorDimensions`  
`struct FLensFileSensorDimensions`  
_L86-98_
- reflection: `USTRUCT()`
- L91 _public member_ `float Width = 0.0f;` — `UPROPERTY()`
- L94 _public member_ `float Height = 0.0f;` — `UPROPERTY()`
- L97 _public member_ `ELensFileUnit Units = ELensFileUnit::Normalized;` — `UPROPERTY()`

#### struct `FLensFileImageDimensions`  
`struct FLensFileImageDimensions`  
_L101-110_
- reflection: `USTRUCT()`
- L106 _public member_ `int32 Width = 0;` — `UPROPERTY()`
- L109 _public member_ `int32 Height = 0;` — `UPROPERTY()`

#### struct `FLensFileParameterTableRow`  
`struct FLensFileParameterTableRow`  
_L113-121_
- reflection: `USTRUCT()`
- L117 _public prototype_ `explicit FLensFileParameterTableRow(int32 InNumHeaders = 0);`
- L120 _public member_ `TArray<float> Values;` — `UPROPERTY()`

#### struct `FLensFileParameterTable`  
`struct FLensFileParameterTable`  
_L124-136_
- reflection: `USTRUCT()`
- L129 _public member_ `FName ParameterName;` — `UPROPERTY()`
- L132 _public member_ `TArray<FName> Header;` — `UPROPERTY()`
- L135 _public member_ `TArray<FLensFileParameterTableRow> Data;` — `UPROPERTY()`

#### struct `FLensFileParameterTableImporter`  
`struct FLensFileParameterTableImporter`  
_L139-153_
- reflection: `USTRUCT()`
- L144 _public member_ `FName ParameterName;` — `UPROPERTY()`
- L147 _public member_ `FString Header;` — `UPROPERTY()`
- L150 _public member_ `FString Data;` — `UPROPERTY()`
- L152 _public prototype_ `bool ConvertToParameterTable(struct FLensFileParameterTable& OutParamterTable, class FFeedbackContext* InWarn) const;`

#### struct `FLensFileExchange`  
`struct FLensFileExchange`  
_L156-223_
- reflection: `USTRUCT()`
- L160 _public prototype_ `FLensFileExchange(const class ULensFile* LensFile = nullptr);`
- L162 _public prototype_ `FLensFileExchange(const TSharedRef<class FJsonObject>& InLensFileJson, bool& bOutIsValidJson, class FFeedbackContext* InWarn);`
- L164 _public prototype_ `bool PopulateLensFile(class ULensFile& LensFile) const;`
- L167 _public member_ `FLensFileMetadata Metadata;` — `UPROPERTY()`
- L170 _public member_ `FLensFileSensorDimensions SensorDimensions;` — `UPROPERTY()`
- L173 _public member_ `FLensFileImageDimensions ImageDimensions;` — `UPROPERTY()`
- L176 _public member_ `TArray<FLensFileParameterTable> CameraParameterTables;` — `UPROPERTY()`
- L179 _public member_ `TArray<FLensFileParameterTable> EncoderTables;` — `UPROPERTY()`
- L181 _public member_ `constexpr static TCHAR LensFileType[] = TEXT("Len`
- L182 _public member_ `constexpr static TCHAR LensFileVersion[] = TEXT("0.0`
- L184 _public member_ `constexpr static TCHAR FocusEncoderHeaderName[] = TEXT("Foc`
- L185 _public member_ `constexpr static TCHAR ZoomEncoderHeaderName[] = TEXT("Zoo`
- L186 _public member_ `constexpr static TCHAR IrisEncoderHeaderName[] = TEXT("Iri`
- L188 _public member_ `constexpr static TCHAR FocusCMHeaderName[] = TEXT("Foc`
- L189 _public member_ `constexpr static TCHAR IrisFstopHeaderName[] = TEXT("Iri`
- L191 _public member_ `constexpr static TCHAR FocalLengthFxHeaderName[] = TEXT("Fx"`
- L192 _public member_ `constexpr static TCHAR FocalLengthFyHeaderName[] = TEXT("Fy"`
- L194 _public member_ `constexpr static TCHAR ImageCenterCxHeaderName[] = TEXT("Cx"`
- L195 _public member_ `constexpr static TCHAR ImageCenterCyHeaderName[] = TEXT("Cy"`
- L197 _public member_ `constexpr static TCHAR NodalOffsetQxHeaderName[] = TEXT("Qx"`
- L198 _public member_ `constexpr static TCHAR NodalOffsetQyHeaderName[] = TEXT("Qy"`
- L199 _public member_ `constexpr static TCHAR NodalOffsetQzHeaderName[] = TEXT("Qz"`
- L200 _public member_ `constexpr static TCHAR NodalOffsetQwHeaderName[] = TEXT("Qw"`
- L202 _public member_ `constexpr static TCHAR NodalOffsetTxHeaderName[] = TEXT("Tx"`
- L203 _public member_ `constexpr static TCHAR NodalOffsetTyHeaderName[] = TEXT("Ty"`
- L204 _public member_ `constexpr static TCHAR NodalOffsetTzHeaderName[] = TEXT("Tz"`
- L207 _private member_ `FFeedbackContext* FeedbackContext;`
- L209 _private prototype_ `FFeedbackContext* GetFeedbackContext() const;`
- L211 _private prototype_ `void ExtractFocalLengthTable(const class ULensFile* LensFile);`
- L212 _private prototype_ `void ExtractImageCenterTable(const class ULensFile* LensFile);`
- L213 _private prototype_ `void ExtractNodalOffsetTable(const class ULensFile* LensFile);`
- L214 _private prototype_ `void ExtractEncoderTables(const class ULensFile* LensFile);`
- L215 _private prototype_ `void ExtractDistortionParameters(const class ULensFile* LensFile);`
- L216 _private prototype_ `void ExtractSTMaps(const class ULensFile* LensFile);`
- L218 _private prototype_ `void PopulateFocalLengthTable(class ULensFile& OutLensFile, const FLensFileParameterTable& FocalLengthTable) const;`
- L219 _private prototype_ `void PopulateImageCenterTable(class ULensFile& OutLensFile, const FLensFileParameterTable& InImageCenterTable) const;`
- L220 _private prototype_ `void PopulateNodalOffsetTable(class ULensFile& OutLensFile, const FLensFileParameterTable& InNodalOffsetTable) const;`
- L221 _private prototype_ `void PopulateDistortionTable(class ULensFile& OutLensFile, const FLensFileParameterTable& InDistortionTable) const;`
- L222 _private prototype_ `void PopulateEncoderTable(struct FRichCurve& OutCurve, const FLensFileParameterTable& InEncoderTable, const TCHAR* InputHeaderName, const TCHAR* OutputHeaderName) const;`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/TestCameraCalibration.h` (Private)


#### class `UAutoCalibrationTest`  
`class UAutoCalibrationTest : public UObject`  
_L9-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Exposes RunTests to BP and Python for ease of running a test in the editor
- L16 _public prototype_ `static void RunTests(FString Filename, bool bLogVerboseTestDescription = false);` — `UFUNCTION(BlueprintCallable, Category = "Calibration")` — Runs the calibration test set defined in the input file

#### struct `FCalibrationDatasetImage`  
`struct FCalibrationDatasetImage`  
_L21-36_
- reflection: `USTRUCT()`
- desc: Useful to deserialize a single json file from a calibration dataset
- L26 _public member_ `TArray<FVector2D> Points2d;` — `UPROPERTY()`
- L29 _public member_ `TArray<FVector> Points3d;` — `UPROPERTY()`
- L32 _public member_ `int32 ImageWidth = -1;` — `UPROPERTY()`
- L35 _public member_ `int32 ImageHeight = -1;` — `UPROPERTY()`

#### struct `FLocationRotation`  
`struct FLocationRotation`  
_L43-52_
- reflection: `USTRUCT()`
- desc: Useful because this struct will be more human-readable when serialized to json than FTransform. FRotator is easier to read/write than FTransform's FQuat, and the automated tests do not use FTransform's scale.
- L48 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY()`
- L51 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY()`

#### struct `FCameraProfile`  
`struct FCameraProfile`  
_L56-84_
- reflection: `USTRUCT()`
- desc: Description of a camera / lens, useful for projecting 3D calibrator points to 2D
- L61 _public member_ `FVector2D SensorSize = FVector2D(-1.0);` — `UPROPERTY()`
- L64 _public member_ `FIntPoint ImageSize = FIntPoint(-1);` — `UPROPERTY()`
- L67 _public member_ `double FocalLengthInMM = -1.0;` — `UPROPERTY()`
- L70 _public member_ `FVector2D ImageCenter = FVector2D(-1.0);` — `UPROPERTY()`
- L73 _public member_ `TArray<float> DistortionParameters;` — `UPROPERTY()`
- L75 _public function_ `FVector2D ConvertFocalLengthToPixels(double FocalLength) const`
- L80 _public function_ `FVector2D GetFxFyInPixels() const`

#### struct `FCheckerboardProfile`  
`struct FCheckerboardProfile`  
_L88-102_
- reflection: `USTRUCT()`
- desc: Description of a checkerboard calibrator, useful for generating sets of 3D calibration points in world space
- L93 _public member_ `FIntPoint CheckerboardDimensions = FIntPoint(-1);` — `UPROPERTY()`
- L96 _public member_ `double SquareSize = -1.0;` — `UPROPERTY()`
- L98 _public function_ `FIntPoint GetCornerDimensions() const`

#### struct `FSolverSettings`  
`struct FSolverSettings`  
_L106-136_
- reflection: `USTRUCT()`
- desc: Settings for the camera calibration solver
- L111 _public member_ `double FocalLengthGuess = -1.0;` — `UPROPERTY()`
- L114 _public member_ `FVector2D ImageCenterGuess = FVector2D(-1.0);` — `UPROPERTY()`
- L117 _public member_ `TOptional<bool> bUseIntrinsicGuess;` — `UPROPERTY()`
- L120 _public member_ `TOptional<bool> bUseExtrinsicGuess;` — `UPROPERTY()`
- L123 _public member_ `TOptional<bool> bFixFocalLength;` — `UPROPERTY()`
- L126 _public member_ `TOptional<bool> bFixPrincipalPoint;` — `UPROPERTY()`
- L129 _public member_ `TOptional<bool> bFixExtrinsics;` — `UPROPERTY()`
- L132 _public member_ `TOptional<bool> bFixDistortion;` — `UPROPERTY()`
- L135 _public member_ `TOptional<bool> bFixAspectRatio;` — `UPROPERTY()`

#### struct `FCalibrationTest`  
`struct FCalibrationTest`  
_L140-187_
- reflection: `USTRUCT()`
- desc: Full camera calibration test description
- L145 _public member_ `int32 TestIndex = 0;` — `UPROPERTY()`
- L148 _public member_ `int32 BaseTestIndex = -1;` — `UPROPERTY()`
- L151 _public member_ `FString DatasetPath;` — `UPROPERTY()`
- L154 _public member_ `FCameraProfile CameraProfile;` — `UPROPERTY()`
- L157 _public member_ `FCheckerboardProfile CheckerboardProfile;` — `UPROPERTY()`
- L160 _public member_ `TArray<FLocationRotation> CameraPoses;` — `UPROPERTY()`
- L163 _public member_ `TArray<FLocationRotation> CheckerboardPoses;` — `UPROPERTY()`
- L166 _public member_ `FSolverSettings SolverSettings;` — `UPROPERTY()`
- L168 _public function_ `void GetCameraTransforms(TArray<FTransform>& Transforms) const`
- L173 _public function_ `void GetCheckerboardTransforms(TArray<FTransform>& Transforms) const`
- L178 _public function_ `void GetTransforms(const TArray<FLocationRotation>& Poses, TArray<FTransform>& Transforms) const`

#### struct `FCalibrationTestSet`  
`struct FCalibrationTestSet`  
_L191-197_
- reflection: `USTRUCT()`
- desc: Set of camera calibration test descriptions
- L196 _public member_ `TArray<FCalibrationTest> Tests;` — `UPROPERTY()`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/TestCameraCalibrationSettings.h` (Private)


#### class `UTestCameraCalibrationSettings`  
`class UTestCameraCalibrationSettings : public UDeveloperSettings`  
_L13-117_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- desc: Settings for the camera calibration testing
- L18 _public prototype_ `UTestCameraCalibrationSettings();`
- L21 _public prototype_ `virtual FName GetCategoryName() const;`
- L23 _public prototype_ `virtual FText GetSectionText() const override;`
- L24 _public prototype_ `virtual FName GetSectionName() const override;`
- L34 _public member_ `FIntPoint ImageSize = FIntPoint(1920, 1080);` — `UPROPERTY(config, EditAnywhere, Category = "True Camera Properties")` — Size of the image that the test camera would generate
- L38 _public member_ `FVector2f SensorDimensions = FVector2f(23.76f, 13.365f);` — `UPROPERTY(config, EditAnywhere, Category = "True Camera Properties")` — Size of the sensor (in mm) of the test camera
- L42 _public member_ `FTransform CameraTransform = FTransform::Identity;` — `UPROPERTY(config, EditAnywhere, Category = "True Camera Properties")` — True 3D pose of the test camera
- L46 _public member_ `double FocalLength = 35.0;` — `UPROPERTY(config, EditAnywhere, Category = "True Camera Properties")` — True focal length of the test camera
- L50 _public member_ `FSphericalDistortionParameters SphericalDistortionParameters;` — `UPROPERTY(config, EditAnywhere, Category = "True Camera Properties")` — True distortion coefficients of the test lens
- L54 _public member_ `int32 NumCameraViews = 1;` — `UPROPERTY(config, EditAnywhere, Category = "True Camera Properties")` — Number of camera views to generate images from
- L58 _public member_ `FIntPoint CheckerboardDimensions = FIntPoint(16, 9);` — `UPROPERTY(config, EditAnywhere, Category = "Calibrator Properties")` — Number of squares in the checkerboard (columns x rows)
- L62 _public member_ `double CheckerboardSquareSize = 5.0;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrator Properties")` — Size (in cm) of the length of each square of the checkerboard
- L66 _public member_ `double CalibratorDistanceFromCamera = 200.0;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrator Properties")` — Distance (in cm) to place the test calibrator from the test camera
- L70 _public member_ `double ObjectPointNoiseScale = 0.0;` — `UPROPERTY(config, EditAnywhere, Category = "Input Data Errors")` — Maximum amount of random noise (in cm) to add to 3D object points
- L74 _public member_ `double ImagePointNoiseScale = 0.0;` — `UPROPERTY(config, EditAnywhere, Category = "Input Data Errors")` — Maximum amount of random noise (in pixels) to add to the 2D image points
- L78 _public member_ `bool bUseCameraIntrinsicGuess = false;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings")` — If true, the solver will use the estimated focal length as an initial guess for the calibrated focal length
- L82 _public member_ `double EstimatedFocalLength = 35.0;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings", meta = (EditCondition = "bUseCameraIntrinsicGuess == true"))` — User-provided guess for the focal length
- L86 _public member_ `bool bUseCameraExtrinsicGuess = false;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings")` — If true, the solver will use the estimate camera transform as an initial guess for the calibrated camera pose
- L90 _public member_ `FTransform EstimatedCameraTransform = FTransform::Identity;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings", meta = (EditCondition = "bUseCameraExtrinsicGuess == true"))` — User-provided guess for the camera pose
- L94 _public member_ `bool bFixFocalLength = false;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings")` — If true, the solver will not try to solve for focal length, and will use the focal length estimate
- L98 _public member_ `bool bFixImageCenter = false;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings")` — If true, the solver will not try to solve for image center, and will use (0.5, 0.5)
- L102 _public member_ `bool bFixExtrinsics = false;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings")` — If true, the solver will not try to solve for the camera pose, and will use the camera transform estimate
- L106 _public member_ `bool bFixDistortion = false;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings")` — If true, the solver will not try to solve for distortion
- L110 _public member_ `bool bFixZeroDistortion = false;` — `UPROPERTY(config, EditAnywhere, Category = "Calibrate Camera Solver Settings")` — If true, the solver will not try to solve for distortion, and will assume there is zero distortion in the image
- L114 _public member_ `bool bShowCheckerboardImage = false;` — `UPROPERTY(config, EditAnywhere, Category = "Debug")` — If true, a debug image will be displayed showing the 2D projected points of the test checkerboard for each of the camera views

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/UI/CameraCalibrationEditorStyle.h` (Private)


#### class `FCameraCalibrationEditorStyle`  
`class FCameraCalibrationEditorStyle final : public FSlateStyleSet`  
_L14-59_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the camera calibration tools UI.
- L19 _public function_ `FCameraCalibrationEditorStyle() : FSlateStyleSet("CameraCalibrationEditorStyle")` — Default constructor.
- L49 _public function_ `virtual ~FCameraCalibrationEditorStyle()` — Virtual destructor.
- L54 _public function_ `static FCameraCalibrationEditorStyle& Get()`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/UI/CameraCalibrationMenuEntry.h` (Private)


#### class `FCameraCalibrationMenuEntry`  
`class FCameraCalibrationMenuEntry`  
_L11-16_
- L14 _public prototype_ `static void Register();`
- L15 _public prototype_ `static void Unregister();`

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/UI/CameraCalibrationWidgetHelpers.h` (Private)


#### class `FCameraCalibrationWidgetHelpers`  
`class FCameraCalibrationWidgetHelpers`  
_L16-36_
- desc: Helpers to build UI used by the Camera Calibration modules.
- L20 _public prototype_ `static TSharedRef<SWidget> BuildLabelWidgetPair(FText&& Text, TSharedRef<SWidget> Widget);` — Builds a UI with a horizontal box with a lable on the left and the provided widget on the right
- L23 _public member_ `static const int32 DefaultRowHeight;` — Stores the default row height used throughout the Camera Calibration UI
- L26 _public prototype_ `static void DisplayTextureInWindowAlmostFullScreen(UTexture2D* Texture, FText&& Title, float ScreenMarginFactor = 0.85f);` — Displays a window with the given texture, preserving aspect ratio and almost full screen
- L31 _public prototype_ `static bool ShowMergeFocusWarning(bool& bOutReplaceExistingZoomPoints);` — Displays a warning dialog box asking if a user wants to merge one focus point into another @param bOutReplaceExistingZoomPoints Whether the user wants to replace existing zoom points in the merge @return true if the user accepted the merge, false otherwise
- L35 _public prototype_ `static bool ShowReplaceZoomWarning();` — Displays a warning dialog box asking if the user wants to replace one zoom point with another @return true if the user accepted the replace, false otherwise

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/UI/SFilterableActorPicker.h` (Private)


#### class `SFilterableActorPicker`  
`class SFilterableActorPicker : public SCompoundWidget`  
_L13-55_
- inherits: `SCompoundWidget`
- desc: Picker that can filter actors.
- L16 _public function_ `SLATE_BEGIN_ARGS(SFilterableActorPicker) : _ActorAssetData()`
- L20 _public prototype_ `SLATE_ATTRIBUTE(FAssetData, ActorAssetData) SLATE_EVENT(FOnSetObject, OnSetObject) SLATE_EVENT(FOnShouldFilterAsset, OnShouldFilterAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _private prototype_ `FText OnGetAssetName() const;` — /  Returns the name of the selected actor, to be displayed in the dropdown
- L35 _private prototype_ `void SetActorAssetData(const FAssetData& AssetData);` — /  Called when the actor has been selected
- L38 _private prototype_ `void GetActorAssetData(FAssetData& OutAssetData) const;` — Fills out the asset data with the current selection
- L43 _private member_ `FOnSetObject OnSetObject;` — Delegate to call when our object actor is set
- L46 _private member_ `FOnShouldFilterAsset OnShouldFilterAsset;` — Delegate for filtering valid actors
- L49 _private member_ `TAttribute<FAssetData> ActorAssetData;` — Current actor asset data
- L54 _private member_ `TSharedPtr<class SComboButton> AssetComboButton;` — The ComboButton used by the picker

### `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/UI/SImageTexture.h` (Private)


#### class `SImageTexture`  
`class SImageTexture : public SCompoundWidget`  
_L16-38_
- inherits: `SCompoundWidget`
- desc: Widget that holds a reference to a UTexture and creates an SImage for that Texture using a brush
- L18 _private function_ `SLATE_BEGIN_ARGS(SImageTexture) : _MinDesiredWidth(FOptionalSize()) , _MinDesiredHeight(FOptionalSize()) , _MaxDesiredWidth(FOptionalSize()) , _MaxDesiredHeight(FOptionalSize())`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, UTexture2D* InTexture);`
- L36 _private member_ `FSlateBrush Brush;`
- L37 _private member_ `TStrongObjectPtr<UTexture2D> Texture;`
