# Plugins / GeometryCacheEd

- module root: `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd`
- headers: 15; symbols: 249
- symbol kinds: class=15, delegate=3, enum=1, enumerator=8, function=23, member=64, prototype=132, struct=2, typedef=1
- PublicDependencyModuleNames: AdvancedPreviewScene, AssetDefinition, AssetTools, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, GeometryCache, InputCore, NiagaraEditor, RHI, RenderCore, SequencerWidgets, Slate, SlateCore, TimeManagement, ToolMenus, UnrealEd

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Classes/ActorFactoryGeometryCache.h` (Public)


#### class `UActorFactoryGeometryCache`  
`class UActorFactoryGeometryCache : public UActorFactory`  
_L13-21_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UActorFactory`
- desc: Factory class for spawning and creating GeometryCacheActors
- L18 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L19 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Classes/AssetDefinition_GeometryCache.h` (Public)


#### class `UAssetDefinition_GeometryCache`  
`class UAssetDefinition_GeometryCache : public UAssetDefinitionDefault`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual bool CanImport() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Classes/GeometryCacheAssetBroker.h` (Public)


#### class `FGeometryCacheAssetBroker`  
`class FGeometryCacheAssetBroker : public IComponentAssetBroker`  
_L8-16_
- inherits: `IComponentAssetBroker`
- desc: AssetBroker class for GeometryCache assets
- L12 _public prototype_ `UClass* GetSupportedAssetClass() override;`
- L13 _public prototype_ `virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override;`
- L14 _public prototype_ `virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Classes/GeometryCacheThumbnailRenderer.h` (Public)


#### class `UGeometryCacheThumbnailRenderer`  
`class UGeometryCacheThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L20-36_
- reflection: `UCLASS(config = Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L25 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L29 _private prototype_ `virtual void BeginDestroy() override;`
- L32 _private member_ `FGeometryCacheThumbnailScene* ThumbnailScene;`
- L34 _public prototype_ `virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Classes/GeometryCacheThumbnailScene.h` (Public)


#### class `FGeometryCacheThumbnailScene`  
`class FGeometryCacheThumbnailScene : public FThumbnailPreviewScene`  
_L10-26_
- inherits: `FThumbnailPreviewScene`
- L14 _public prototype_ `FGeometryCacheThumbnailScene();` — Constructor
- L17 _public prototype_ `void SetGeometryCache(UGeometryCache* GeometryCache);` — Sets the static mesh to use in the next CreateView()
- L21 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;` — FThumbnailPreviewScene implementation
- L25 _private member_ `AGeometryCacheActor* PreviewActor;` — The static mesh actor used to display all static mesh thumbnails

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/GeometryCacheAssetEditorToolkit.h` (Private)


#### class `FGeometryCacheAssetEditorToolkit`  
`class FGeometryCacheAssetEditorToolkit : public FAssetEditorToolkit`  
_L16-61_
- inherits: `FAssetEditorToolkit`
- L19 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L20 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L29 _public prototype_ `void InitCustomAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UGeometryCache * InCustomAsset);` — Edits the specified asset object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InCustomAsset			The Custom Asset to Edit
- L31 _public prototype_ `FGeometryCacheAssetEditorToolkit();`
- L32 _public prototype_ `virtual ~FGeometryCacheAssetEditorToolkit() = default;`
- L35 _public prototype_ `virtual FName GetToolkitFName() const override;` — Begin IToolkit interface
- L36 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L37 _public prototype_ `virtual FText GetToolkitName() const override;`
- L38 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L39 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L40 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L41 _public function_ `virtual bool IsPrimaryEditor() const override`
- L42 _public prototype_ `virtual void OnClose() override;`
- L46 _private prototype_ `void InitPreviewComponents();`
- L49 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L50 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetProperties(const FSpawnTabArgs& Args);`
- L51 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AnimationProperties(const FSpawnTabArgs& Args);`
- L52 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSceneProperties(const FSpawnTabArgs& Args);`
- L55 _private member_ `TWeakObjectPtr<UGeometryCache> GeometryCacheAsset;`
- L56 _private member_ `TWeakObjectPtr<UGeometryCacheComponent> PreviewGeometryCacheComponent;`
- L58 _private member_ `TSharedPtr<SGeometryCacheEditorViewport> ViewportTab;`
- L59 _private member_ `TSharedPtr<IDetailsView> DetailView_AssetProperties;`
- L60 _private member_ `TSharedPtr<FGeometryCacheTimelineBindingAsset> BindingAsset;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/GeometryCacheTimeSliderController.h` (Private)


#### class `FGeometryCacheTimeSlideController`  
`class FGeometryCacheTimeSlideController : public ITimeSliderController, public TSharedFromThis<FGeometryCacheTimeSlideController>`  
_L15-187_
- inherits: `ITimeSliderController,TSharedFromThis<FGeometryCacheTimeSlideController>`
- L21 _public prototype_ `FGeometryCacheTimeSlideController(const FTimeSliderArgs& InArgs, TWeakPtr<SGeometryCacheTimeline> GeometryCacheTimeline);`
- L22 _public prototype_ `~FGeometryCacheTimeSlideController();`
- L25 _public prototype_ `virtual int32 OnPaintTimeSlider(bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — ITimeSliderController Interface
- L26 _public prototype_ `virtual int32 OnPaintViewArea(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, const FPaintViewAreaArgs& Args) const override;`
- L27 _public prototype_ `virtual FReply OnMouseButtonDown(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual FReply OnMouseButtonUp(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual FReply OnMouseMove(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `virtual FReply OnMouseWheel(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual FCursorReply OnCursorQuery(const SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L33 _public prototype_ `virtual void SetViewRange(double NewRangeMin, double NewRangeMax, EViewRangeInterpolation Interpolation) override;`
- L34 _public prototype_ `virtual void SetClampRange(double NewRangeMin, double NewRangeMax) override;`
- L35 _public prototype_ `virtual void SetPlayRange(FFrameNumber RangeStart, int32 RangeDuration) override;`
- L36 _public function_ `virtual FFrameRate GetDisplayRate() const override`
- L37 _public function_ `virtual FFrameRate GetTickResolution() const override`
- L38 _public function_ `virtual FAnimatedRange GetViewRange() const override`
- L39 _public function_ `virtual FAnimatedRange GetClampRange() const override`
- L40 _public function_ `virtual TRange<FFrameNumber> GetPlayRange() const override`
- L41 _public function_ `virtual FFrameTime GetScrubPosition() const`
- L42 _public function_ `virtual void SetScrubPosition(FFrameTime InTime, bool bEvaluate)`
- L51 _public prototype_ `void ClampViewRange(double& NewRangeMin, double& NewRangeMax);` — Clamp the given range to the clamp range @param NewRangeMin		The new lower bound of the range @param NewRangeMax		The new upper bound of the range
- L59 _public prototype_ `bool ZoomByDelta(float InDelta, float MousePositionFraction = 0.5f);` — Zoom the range by a given delta. @param InDelta					The total amount to zoom by (+ve = zoom out, -ve = zoom in) @param MousePositionFraction		Bias to apply to lower/upper extents of the range. (0 = lower, 0.5 = equal, 1 = upper)
- L66 _public prototype_ `void PanByDelta(float InDelta);` — Pan the range by a given delta @param InDelta		The total amount to pan by (+ve = pan forwards in time, -ve = pan backwards in time)
- L69 _public prototype_ `FFrameTime GetFrameTimeFromMouse(const FGeometry& Geometry, FVector2D ScreenSpacePosition) const;` — Determine frame time from a mouse position
- L78 _private prototype_ `void CommitScrubPosition(FFrameTime NewValue, bool bIsScrubbing);` — Call this method when the user's interaction has changed the scrub position @param NewValue				Value resulting from the user's interaction @param bIsScrubbing			True if done via scrubbing, false if just releasing scrubbing
- L88 _private prototype_ `void DrawTicks(FSlateWindowElementList& OutDrawElements, const TRange<double>& ViewRange, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs) const;` — Draw time tick marks @param OutDrawElements	List to add draw elements to @param ViewRange			The currently visible time range in seconds @param RangeToScreen		Time range to screen space converter @param InArgs			Parameters for drawing the tick lines
- L95 _private prototype_ `int32 DrawSelectionRange(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen, const FPaintPlaybackRangeArgs& Args) const;` — Draw the selection range. @return The new layer ID.
- L102 _private prototype_ `int32 DrawPlaybackRange(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen, const FPaintPlaybackRangeArgs& Args) const;` — Draw the playback range. @return the new layer ID
- L107 _private prototype_ `bool HitTestRangeStart(const FScrubRangeToScreen& RangeToScreen, const TRange<double>& Range, float HitPixel) const;` — Hit test the lower bound of a range
- L112 _private prototype_ `bool HitTestRangeEnd(const FScrubRangeToScreen& RangeToScreen, const TRange<double>& Range, float HitPixel) const;` — Hit test the upper bound of a range
- L114 _private prototype_ `void SetPlaybackRangeStart(FFrameNumber NewStart);`
- L115 _private prototype_ `void SetPlaybackRangeEnd(FFrameNumber NewEnd);`
- L117 _private prototype_ `void SetSelectionRangeStart(FFrameNumber NewStart);`
- L118 _private prototype_ `void SetSelectionRangeEnd(FFrameNumber NewEnd);`
- L120 _private prototype_ `FFrameTime ComputeFrameTimeFromMouse(const FGeometry& Geometry, FVector2D ScreenSpacePosition, FScrubRangeToScreen RangeToScreen, bool CheckSnapping = true) const;`
- L130 _private prototype_ `FScrubPixelRange GetHitTestScrubberPixelRange(FFrameTime ScrubTime, const FScrubRangeToScreen& RangeToScreen) const;`
- L132 _private prototype_ `FScrubPixelRange GetScrubberPixelRange(FFrameTime ScrubTime, const FScrubRangeToScreen& RangeToScreen) const;`
- L133 _private prototype_ `FScrubPixelRange GetScrubberPixelRange(FFrameTime ScrubTime, FFrameRate Resolution, FFrameRate PlayRate, const FScrubRangeToScreen& RangeToScreen, float DilationPixels = 0.f) const;`
- L136 _private member_ `FTimeSliderArgs TimeSliderArgs;`
- L139 _private member_ `TWeakPtr<SGeometryCacheTimeline> WeakTimeline;` — Pointer back to the timeline
- L142 _private member_ `const FSlateBrush* ScrubFillBrush;` — Brush for drawing the fill area on the scrubber
- L145 _private member_ `const FSlateBrush* ScrubHandleUpBrush;` — Brush for drawing an upwards facing scrub handles
- L148 _private member_ `const FSlateBrush* ScrubHandleDownBrush;` — Brush for drawing a downwards facing scrub handle
- L151 _private member_ `const FSlateBrush* EditableTimeBrush;` — Brush for drawing an editable time
- L155 _private member_ `float DistanceDragged;` — Total mouse delta during dragging
- L170 _private member_ `DragType MouseDragType;`
- L173 _private member_ `bool bPanning;` — If we are currently panning the panel
- L176 _private member_ `int32 DraggedTimeIndex;` — Index of the current dragged time
- L179 _private member_ `FVector2D MouseDownPosition[2];` — Mouse down position range
- L182 _private member_ `FGeometry MouseDownGeometry;` — Geometry on mouse down
- L185 _private member_ `TArray<TRange<double>> ViewRangeStack;` — Range stack

#### struct `FGeometryCacheTimeSlideController::FScrubPixelRange`  
`struct FScrubPixelRange`  
_L123-128_
- L125 _public member_ `TRange<float> Range;`
- L126 _public member_ `TRange<float> HandleRange;`
- L127 _public member_ `bool bClamped;`

#### enum `FGeometryCacheTimeSlideController::DragType`  
`enum DragType`  
_L158-168_
- desc: If we are dragging a scrubber or dragging to set the time range
- L160 _public enumerator_ `DRAG_SCRUBBING_TIME`
- L161 _public enumerator_ `DRAG_SETTING_RANGE`
- L162 _public enumerator_ `DRAG_PLAYBACK_START`
- L163 _public enumerator_ `DRAG_PLAYBACK_END`
- L164 _public enumerator_ `DRAG_SELECTION_START`
- L165 _public enumerator_ `DRAG_SELECTION_END`
- L166 _public enumerator_ `DRAG_TIME`
- L167 _public enumerator_ `DRAG_NONE`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/GeometryCacheTimelineBindingAsset.h` (Private)


#### class `FGeometryCacheTimelineBindingAsset`  
`class FGeometryCacheTimelineBindingAsset : public TSharedFromThis<FGeometryCacheTimelineBindingAsset>`  
_L14-63_
- inherits: `TSharedFromThis<FGeometryCacheTimelineBindingAsset>`
- L17 _public prototype_ `FGeometryCacheTimelineBindingAsset(TWeakObjectPtr<UGeometryCacheComponent> InPreviewComponent);`
- L19 _public function_ `TWeakObjectPtr<UGeometryCacheComponent> GetPreviewComponent() const`
- L22 _public prototype_ `FFrameRate GetFrameRate() const;` — Get the framerate specified by the anim sequence
- L25 _public prototype_ `int32 GetTickResolution() const;` — Get the tick resolution we are displaying at
- L28 _public prototype_ `FAnimatedRange GetViewRange() const;` — Get the current view range
- L31 _public prototype_ `void SetViewRange(TRange<double> InRange);` — Set the current view range
- L34 _public prototype_ `FAnimatedRange GetWorkingRange() const;` — Get the working range of the model's data
- L37 _public prototype_ `TRange<FFrameNumber> GetPlaybackRange() const;` — Get the playback range of the model's data
- L40 _public prototype_ `FFrameNumber GetScrubPosition() const;` — Get the current scrub position
- L43 _public prototype_ `float GetScrubTime() const;` — Get the current scrub time
- L46 _public prototype_ `void SetScrubPosition(FFrameTime NewScrubPostion) const;` — Set the current scrub position
- L49 _public prototype_ `void HandleViewRangeChanged(TRange<double> InRange, EViewRangeInterpolation InInterpolation);` — Handle the view range being changed
- L52 _public prototype_ `void HandleWorkingRangeChanged(TRange<double> InRange);` — Handle the working range being changed
- L55 _private member_ `TWeakObjectPtr<UGeometryCacheComponent> PreviewComponent;`
- L57 _private member_ `FAnimatedRange ViewRange;`
- L59 _private member_ `FAnimatedRange WorkingRange;`
- L61 _private member_ `FAnimatedRange PlaybackRange;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/Widgets/SGeometryCacheEditorViewport.h` (Private)


#### class `SGeometryCacheEditorViewport`  
`class SGeometryCacheEditorViewport : public SEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider`  
_L21-69_
- inherits: `SEditorViewport,FGCObject,ICommonEditorViewportToolbarInfoProvider`
- L24 _public prototype_ `void Construct(const FArguments& InArgs);`
- L26 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L27 _public function_ `virtual FString GetReferencerName() const override`
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L35 _public prototype_ `virtual TSharedRef<SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L36 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L37 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L41 _public prototype_ `void SetGeometryCacheComponent(UGeometryCacheComponent* InGeometryCacheComponent);` — Set the component to preview
- L43 _public function_ `TSharedPtr<FAdvancedPreviewScene> GetAdvancedPreviewScene()`
- L47 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L48 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L49 _protected prototype_ `virtual EVisibility OnGetViewportContentVisibility() const override;`
- L50 _protected prototype_ `virtual void BindCommands() override;`
- L51 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L52 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<class SOverlay> Overlay) override;`
- L55 _private prototype_ `bool IsVisible() const override;`
- L57 _private prototype_ `FText BuildStatsText() const;`
- L60 _private member_ `TWeakPtr<SDockTab> ParentTab;` — The parent tab where this viewport resides
- L63 _private member_ `TSharedPtr<FGeometryCacheEditorViewportClient> SystemViewportClient;` — Level viewport client
- L66 _private member_ `TSharedPtr<FAdvancedPreviewScene> AdvancedPreviewScene;` — Preview Scene - uses advanced preview settings
- L68 _private member_ `TObjectPtr<UGeometryCacheComponent> PreviewGeometryCacheComponent;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/Widgets/SGeometryCacheTimeline.h` (Private)


#### class `SGeometryCacheTimeline`  
`class SGeometryCacheTimeline : public SCompoundWidget`  
_L20-64_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SGeometryCacheTimeline)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FGeometryCacheTimelineBindingAsset>& InBindingAsset);`
- L29 _public function_ `TSharedRef<INumericTypeInterface<double>> GetNumericTypeInterface() const` — Get numeric Type interface for converting between frame numbers and display formats.
- L32 _public prototype_ `bool GetGridMetrics(float PhysicalWidth, double& OutMajorInterval, int32& OutMinorDivisions) const;` — Compute a major grid interval and number of minor divisions to display
- L35 _private prototype_ `void HandleScrubPositionChanged(FFrameTime NewScrubPosition, bool bIsScrubbing, bool bEvaluate) const;`
- L37 _private prototype_ `void InitTrackNames();`
- L39 _private function_ `float GetColumnFillCoefficient(int32 ColumnIndex) const`
- L44 _private prototype_ `void OnColumnFillCoefficientChanged(float FillCoefficient, int32 ColumnIndex);`
- L46 _private prototype_ `TSharedRef<ITableRow> HandleTimelineListViewGenerateRow(TSharedPtr<FString> Text, const TSharedRef<STableViewBase>& OwnerTable);`
- L49 _private member_ `float ColumnFillCoefficients[2];` — The fill coefficients of each column in the grid.
- L51 _private member_ `TWeakPtr<FGeometryCacheTimelineBindingAsset> BindingAsset;`
- L53 _private member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;`
- L55 _private member_ `TSharedPtr<FGeometryCacheTimeSlideController> TimeSliderController;`
- L57 _private member_ `TSharedPtr<ITimeSlider> TimeSlider;`
- L59 _private member_ `TArray<TSharedPtr<FString>> TrackNames;`
- L61 _private member_ `TSharedPtr<SListView<TSharedPtr<FString> > > TracksListView;`
- L63 _private member_ `TAttribute<FAnimatedRange> ViewRange;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/Widgets/SGeometryCacheTimelineOverlay.h` (Private)


#### class `SGeometryCacheTimelineOverlay`  
`class SGeometryCacheTimelineOverlay : public SCompoundWidget`  
_L19-54_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SGeometryCacheTimelineOverlay) : _DisplayTickLines(true) , _DisplayScrubPosition(false)`
- L27 _public function_ `SLATE_ATTRIBUTE(bool, DisplayTickLines) SLATE_ATTRIBUTE(bool, DisplayScrubPosition) SLATE_ATTRIBUTE(FPaintPlaybackRangeArgs, PaintPlaybackRangeArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FGeometryCacheTimeSlideController> InTimeSliderController)`
- L43 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget Interface
- L47 _private member_ `TSharedPtr<FGeometryCacheTimeSlideController> TimeSliderController;` — Controller for manipulating time
- L49 _private member_ `TAttribute<bool> bDisplayScrubPosition;` — Whether or not to display the scrub position
- L51 _private member_ `TAttribute<bool> bDisplayTickLines;` — Whether or not to display tick lines
- L53 _private member_ `TAttribute<FPaintPlaybackRangeArgs> PaintPlaybackRangeArgs;` — User-supplied options for drawing playback range

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/Widgets/SGeometryCacheTimelineSplitterOverlay.h` (Private)


#### class `SGeometryCacheTimelineSplitterOverlay`  
`class SGeometryCacheTimelineSplitterOverlay : public SOverlay`  
_L20-41_
- inherits: `SOverlay`
- desc: Splitter used on the anim timeline as an overlay. Input is disabled on all areas except the draggable positions
- L23 _public typedef_ `typedef SSplitter::FArguments FArguments;`
- L25 _public prototype_ `void Construct( const FArguments& InArgs );`
- L28 _public prototype_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;` — SwWidget interface
- L29 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L30 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L31 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L32 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L33 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L34 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L37 _private prototype_ `FMargin GetSplitterHandlePadding(int32 Index) const;`
- L39 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L40 _private member_ `mutable TArray<FMargin> SlotPadding;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/Widgets/SGeometryCacheTimelineTransportControls.h` (Private)


#### class `SGeometryCacheTimelineTransportControls`  
`class SGeometryCacheTimelineTransportControls : public SCompoundWidget`  
_L13-46_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SGeometryCacheTimelineTransportControls)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FGeometryCacheTimelineBindingAsset>& InBindingAsset);`
- L24 _private prototype_ `FReply OnClick_Forward_Step();`
- L26 _private prototype_ `FReply OnClick_Forward_End();`
- L28 _private prototype_ `FReply OnClick_Backward_Step();`
- L30 _private prototype_ `FReply OnClick_Backward_End();`
- L32 _private prototype_ `FReply OnClick_Forward();`
- L34 _private prototype_ `FReply OnClick_Backward();`
- L36 _private prototype_ `FReply OnClick_ToggleLoop();`
- L38 _private prototype_ `bool IsLoopStatusOn() const;`
- L40 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L43 _private member_ `TWeakPtr<FGeometryCacheTimelineBindingAsset> WeakBindingAsset;`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Private/Widgets/STimelineCustomTransportControl.h` (Private)


#### struct `FGeometryCacheTimelineTransportControlArgs`  
`struct FGeometryCacheTimelineTransportControlArgs`  
_L23-50_
- L25 _public function_ `FGeometryCacheTimelineTransportControlArgs() : OnForwardPlay() , OnBackwardPlay() , OnForwardStep() , OnBackwardStep() , OnForwardEnd() , OnBackwardEnd() , OnToggleLooping() , OnGetLooping() , OnGetPlaybackMode() , OnTickPlayback() , bAreButtonsFocusable(true)`
- L39 _public member_ `FOnClicked OnForwardPlay;`
- L40 _public member_ `FOnClicked OnBackwardPlay;`
- L41 _public member_ `FOnClicked OnForwardStep;`
- L42 _public member_ `FOnClicked OnBackwardStep;`
- L43 _public member_ `FOnClicked OnForwardEnd;`
- L44 _public member_ `FOnClicked OnBackwardEnd;`
- L45 _public member_ `FOnClicked OnToggleLooping;`
- L46 _public member_ `FOnGetLooping OnGetLooping;`
- L47 _public member_ `FOnGetPlaybackMode OnGetPlaybackMode;`
- L48 _public member_ `FOnTickPlayback OnTickPlayback;`
- L49 _public member_ `bool bAreButtonsFocusable;`

#### class `STimelineCustomTransportControl`  
`class STimelineCustomTransportControl : public ITransportControl, public FTickableEditorObject`  
_L52-105_
- inherits: `ITransportControl,FTickableEditorObject`
- L55 _public function_ `SLATE_BEGIN_ARGS(STimelineCustomTransportControl) :_TransportArgs()`
- L58 _public prototype_ `SLATE_ARGUMENT(FGeometryCacheTimelineTransportControlArgs, TransportArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L68 _public prototype_ `virtual ~STimelineCustomTransportControl() = default;`
- L73 _public prototype_ `virtual bool IsTickable() const override;`
- L74 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L75 _public function_ `virtual TStatId GetStatId() const override`
- L79 _private prototype_ `const FSlateBrush* GetForwardStatusIcon() const;`
- L80 _private prototype_ `FText GetForwardStatusTooltip() const;`
- L81 _private prototype_ `const FSlateBrush* GetBackwardStatusIcon() const;`
- L82 _private prototype_ `const FSlateBrush* GetLoopStatusIcon() const;`
- L83 _private prototype_ `FText GetLoopStatusTooltip() const;`
- L86 _private prototype_ `EActiveTimerReturnType TickPlayback(double InCurrentTime, float InDeltaTime);` — Executes the OnTickPlayback delegate
- L88 _private prototype_ `FReply OnToggleLooping();`
- L91 _private prototype_ `TSharedPtr<SWidget> MakeTransportControlWidget(ETransportControlWidgetType WidgetType, bool bAreButtonsFocusable, const FOnMakeTransportWidget& MakeCustomWidgetDelegate = FOnMakeTransportWidget());` — Make default transport control widgets
- L95 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the active timer
- L98 _private member_ `bool bIsActiveTimerRegistered;` — Whether the active timer is currently registered
- L100 _private member_ `FGeometryCacheTimelineTransportControlArgs TransportControlArgs;`
- L102 _private member_ `TSharedPtr<SButton> ForwardPlayButton;`
- L103 _private member_ `TSharedPtr<SButton> BackwardPlayButton;`
- L104 _private member_ `TSharedPtr<SButton> LoopButton;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnGetLooping) DECLARE_DELEGATE_RetVal(EPlaybackMode::Type, FOnGetPlaybackMode) DECLARE_DELEGATE_TwoParams(FOnTickPlayback, double , float ) struct FGeometryCacheTimelineTransportControlArgs { FGeometryCacheTimelineTransportControlArgs() : OnForwardPlay() , OnBackwardPlay() , OnForwardStep() , OnBackwardStep() , OnForwardEnd() , OnBackwardEnd() , OnToggleLooping() , OnGetLooping() , OnGetPlaybackMode() , OnTickPlayback() , bAreButtonsFocusable(true) {} FOnClicked OnForwardPlay; FOnClicked OnBackwardPlay; FOnClicked OnForwardStep; FOnClicked OnBackwardStep; FOnClicked OnForwardEnd; FOnClicked OnBackwardEnd; FOnClicked OnToggleLooping; FOnGetLooping OnGetLooping; FOnGetPlaybackMode OnGetPlaybackMode; FOnTickPlayback OnTickPlayback; bool bAreButtonsFocusable; };`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal(EPlaybackMode::Type, FOnGetPlaybackMode) DECLARE_DELEGATE_TwoParams(FOnTickPlayback, double , float ) struct FGeometryCacheTimelineTransportControlArgs { FGeometryCacheTimelineTransportControlArgs() : OnForwardPlay() , OnBackwardPlay() , OnForwardStep() , OnBackwardStep() , OnForwardEnd() , OnBackwardEnd() , OnToggleLooping() , OnGetLooping() , OnGetPlaybackMode() , OnTickPlayback() , bAreButtonsFocusable(true) {} FOnClicked OnForwardPlay; FOnClicked OnBackwardPlay; FOnClicked OnForwardStep; FOnClicked OnBackwardStep; FOnClicked OnForwardEnd; FOnClicked OnBackwardEnd; FOnClicked OnToggleLooping; FOnGetLooping OnGetLooping; FOnGetPlaybackMode OnGetPlaybackMode; FOnTickPlayback OnTickPlayback; bool bAreButtonsFocusable; };`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnTickPlayback, double , float ) struct FGeometryCacheTimelineTransportControlArgs { FGeometryCacheTimelineTransportControlArgs() : OnForwardPlay() , OnBackwardPlay() , OnForwardStep() , OnBackwardStep() , OnForwardEnd() , OnBackwardEnd() , OnToggleLooping() , OnGetLooping() , OnGetPlaybackMode() , OnTickPlayback() , bAreButtonsFocusable(true) {} FOnClicked OnForwardPlay; FOnClicked OnBackwardPlay; FOnClicked OnForwardStep; FOnClicked OnBackwardStep; FOnClicked OnForwardEnd; FOnClicked OnBackwardEnd; FOnClicked OnToggleLooping; FOnGetLooping OnGetLooping; FOnGetPlaybackMode OnGetPlaybackMode; FOnTickPlayback OnTickPlayback; bool bAreButtonsFocusable; };`

### `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Public/GeometryCacheEdModule.h` (Public)


#### class `FGeometryCacheEdModule`  
`class FGeometryCacheEdModule : public IModuleInterface`  
_L10-40_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L13 _public function_ `FGeometryCacheEdModule()`
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
- L24 _public function_ `static inline FGeometryCacheEdModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L39 _private member_ `class FGeometryCacheAssetBroker* AssetBroker;`
