# Plugins / VEUVEditor

- module root: `Plugins/Experimental/VEUV/Source/VEUVEditor`
- headers: 1; symbols: 142
- symbol kinds: class=4, delegate=3, enum=2, enumerator=10, function=17, member=55, prototype=48, struct=3
- PrivateDependencyModuleNames: InputCore, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, Engine, VEUVCore

### `Plugins/Experimental/VEUV/Source/VEUVEditor/Private/VEUVDebugPanel.h` (Private)


#### enum `EVEUVVisualizationMode`  
`enum class EVEUVVisualizationMode : uint8`  
_L18-25_
- L20 _public enumerator_ `UVLayout`
- L21 _public enumerator_ `Faces`
- L22 _public enumerator_ `Charts`
- L23 _public enumerator_ `ErrorPlot`
- L24 _public enumerator_ `Stats`

#### class `SVEUVCanvas`  
`class SVEUVCanvas : public SLeafWidget`  
_L27-115_
- inherits: `SLeafWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SVEUVCanvas)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `void Clear();` — Reset view and content
- L39 _public prototype_ `void FitToContent();` — Fit the view to content bounds
- L42 _public function_ `void RequestFitToContent()` — Deferred fit
- L45 _public function_ `FVector2f GetViewOffset() const` — View state accessors
- L46 _public function_ `FVector2f GetViewZoom() const`
- L48 _public prototype_ `DECLARE_DELEGATE(FOnViewChanged);`
- L49 _public member_ `FOnViewChanged OnViewChanged;`
- L52 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget overrides
- L53 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L54 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L55 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L60 _protected function_ `virtual FBox2f GetContentBounds() const` — Override to provide content bounds in data space
- L63 _protected function_ `virtual int32 PaintContent(const FGeometry& Geometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, FVector2f Scale, FVector2f Origin) const` — Override to render content on top of the grid
- L66 _protected function_ `virtual void ClearContent()` — Override to clear derived content
- L69 _protected function_ `virtual bool HasContent() const` — Returns true if there is content to display
- L72 _protected function_ `FVector2f UVToScreen(FVector2f UV, FVector2f Scale, FVector2f Origin) const` — Transform data coordinate to screen position
- L81 _protected prototype_ `FVector2f GetScale(const FGeometry& Geometry) const;` — Get the pixel-to-normalized scale factor
- L84 _protected prototype_ `FVector2f ScreenToNormalized(const FGeometry& Geometry, FVector2f ScreenPos) const;` — Convert screen position to normalized viewport coordinates
- L87 _protected prototype_ `FVector2f ScreenToDataUV(const FGeometry& Geometry, FVector2f ScreenPos) const;` — Convert screen position to data-space UV coordinates
- L90 _protected member_ `FVector2f ViewOffset = FVector2f(0.0f, 0.0f);` — View state
- L91 _protected member_ `FVector2f ViewZoom = FVector2f(1.0f, 1.0f);`
- L94 _protected member_ `FVector2f PanStart = FVector2f::ZeroVector;` — Pan state
- L95 _protected member_ `FVector2f PanOffsetStart = FVector2f::ZeroVector;`
- L96 _protected member_ `bool bIsPanning = false;`
- L99 _protected member_ `bool bUniformZoom = true;` — View configuration (set by derived classes during Build)
- L100 _protected member_ `bool bFlipY = false;`
- L103 _protected member_ `bool bPendingFitToContent = false;` — Deferred fit-to-content (executed on next Tick when geometry is valid)
- L107 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SLeafWidget overrides
- L108 _private prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L111 _private prototype_ `int32 DrawGrid(FSlateWindowElementList& OutDrawElements, int32 LayerId, FVector2f Scale, FVector2f Origin, FVector2f AbsOrigin, FVector2f ViewportSize) const;` — Draw the background grid, axes, and tick labels
- L114 _private function_ `virtual bool ShouldDrawUnitBox() const` — Whether to draw the UV 0-1 unit box (overridden by mesh viewport)

#### struct `FVEUVHitResult`  
`struct FVEUVHitResult`  
_L117-122_
- L119 _public member_ `int32 FaceIndex = INDEX_NONE;`
- L120 _public member_ `int32 ChartIndex = INDEX_NONE;`
- L121 _public member_ `FVector2f UV;`

#### class `SVEUVMeshViewport`  
`class SVEUVMeshViewport : public SVEUVCanvas`  
_L124-179_
- inherits: `SVEUVCanvas`
- L133 _public function_ `SLATE_BEGIN_ARGS(SVEUVMeshViewport)`
- L134 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L139 _public prototype_ `void BuildMesh(TSharedPtr<VEUV::FDebugCapture> InCapture, EVEUVVisualizationMode Mode);` — Build mesh from a debug capture
- L142 _public prototype_ `void BuildMeshFromSnapshot(TSharedPtr<VEUV::FDebugCapture> InCapture, const VEUV::FDebugCapture::FGeometrySnapshot& Snapshot);` — Build mesh from a geometry snapshot
- L145 _public prototype_ `bool HitTest(const FGeometry& Geometry, FVector2f ScreenPos, FVEUVHitResult& OutHit) const;` — Find the face and chart at a screen position
- L148 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget overrides
- L149 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L150 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L151 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L153 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const FVEUVHitResult&);`
- L154 _public member_ `FOnSelectionChanged OnSelectionChanged;`
- L156 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDoubleClick, const FVEUVHitResult&);`
- L157 _public member_ `FOnDoubleClick OnDoubleClick;`
- L159 _public member_ `FVEUVHitResult LastHit;`
- L161 _public member_ `bool bShowWireframe = false;`
- L164 _protected prototype_ `virtual FBox2f GetContentBounds() const override;`
- L165 _protected prototype_ `virtual int32 PaintContent(const FGeometry& Geometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, FVector2f Scale, FVector2f Origin) const override;`
- L166 _protected prototype_ `virtual void ClearContent() override;`
- L167 _protected function_ `virtual bool HasContent() const override`
- L168 _protected function_ `virtual bool ShouldDrawUnitBox() const override`
- L171 _private member_ `TArray<FMeshVertex> Vertices;`
- L172 _private member_ `TArray<uint32> Indices;`
- L173 _private member_ `TSharedPtr<VEUV::FDebugCapture> Capture;`
- L174 _private member_ `bool bIsDraggingSelection = false;`
- L177 _private member_ `TSharedPtr<FSlateMaterialBrush> GridMaterialBrush;` — Optional material brush for UV grid visualization
- L178 _private member_ `bool bUseMaterialBrush = false;`

#### struct `SVEUVMeshViewport::FMeshVertex`  
`struct FMeshVertex`  
_L127-131_
- L129 _public member_ `FVector2f UV;`
- L130 _public member_ `FColor Color;`

#### class `SVEUVPlotViewport`  
`class SVEUVPlotViewport : public SVEUVCanvas`  
_L181-222_
- inherits: `SVEUVCanvas`
- L191 _public function_ `SLATE_BEGIN_ARGS(SVEUVPlotViewport)`
- L192 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L197 _public prototype_ `void BuildPlot(TArray<FPlotSeries>&& InSeries);` — Build plot from series data
- L200 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget overrides
- L203 _public member_ `bool bLogScale = true;` — Log scale Y axis
- L206 _protected prototype_ `virtual FBox2f GetContentBounds() const override;`
- L207 _protected prototype_ `virtual int32 PaintContent(const FGeometry& Geometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, FVector2f Scale, FVector2f Origin) const override;`
- L208 _protected prototype_ `virtual void ClearContent() override;`
- L209 _protected function_ `virtual bool HasContent() const override`
- L213 _private function_ `float TransformY(float Y) const` — Transform Y
- L219 _private member_ `TArray<FPlotSeries> PlotSeries;`
- L220 _private member_ `TSet<FString> HiddenSeries;`
- L221 _private member_ `mutable TArray<FBox2f> LegendEntryBounds;`

#### struct `SVEUVPlotViewport::FPlotSeries`  
`struct FPlotSeries`  
_L184-189_
- L186 _public member_ `TArray<FVector2f> Points;`
- L187 _public member_ `FLinearColor Color;`
- L188 _public member_ `FString Label;`

#### class `SVEUVDebugPanel`  
`class SVEUVDebugPanel : public SCompoundWidget`  
_L224-293_
- inherits: `SCompoundWidget`
- L227 _public function_ `SLATE_BEGIN_ARGS(SVEUVDebugPanel)`
- L228 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L231 _public prototype_ `virtual ~SVEUVDebugPanel();`
- L234 _private prototype_ `void OnCaptureAdded();`
- L235 _private prototype_ `void RefreshCaptureList();`
- L236 _private prototype_ `void RebuildComboBoxSource();`
- L237 _private prototype_ `void SelectCapture(int32 Index);`
- L238 _private prototype_ `void SetVisualizationMode(EVEUVVisualizationMode Mode);`
- L239 _private prototype_ `void RebuildMeshData();`
- L240 _private prototype_ `void DrawWorldDebug();`
- L242 _private prototype_ `EActiveTimerReturnType OnPlaybackTick(double InCurrentTime, float InDeltaTime);`
- L245 _private prototype_ `SVEUVCanvas* GetActiveCanvas() const;` — Get whichever canvas is currently active
- L247 _private prototype_ `TSharedRef<SWidget> GenerateComboBoxRow(TSharedPtr<int32> InItem);`
- L248 _private prototype_ `void OnComboBoxSelectionChanged(TSharedPtr<int32> InItem, ESelectInfo::Type SelectInfo);`
- L249 _private prototype_ `FText GetSelectedComboBoxText() const;`
- L251 _private member_ `TArray<TSharedPtr<VEUV::FDebugCapture>> Captures;`
- L252 _private member_ `FDelegateHandle CaptureAddedHandle;`
- L254 _private member_ `int32 SelectedCaptureIndex = INDEX_NONE;`
- L255 _private member_ `int32 LastSelectedChart = INDEX_NONE;`
- L256 _private member_ `EVEUVVisualizationMode CurrentMode = EVEUVVisualizationMode::UVLayout;`
- L267 _private member_ `ESampleFilter SampleFilter = ESampleFilter::All;`
- L269 _private member_ `bool bShowVoxels = true;`
- L270 _private member_ `bool bShowSettings = false;`
- L272 _private member_ `TSharedPtr<IStructureDetailsView> SettingsDetailsView;`
- L273 _private member_ `TSharedPtr<FStructOnScope> SettingsStructData;`
- L274 _private member_ `TSharedPtr<SBox> SettingsPanel;`
- L276 _private member_ `TSharedPtr<SVEUVMeshViewport> MeshViewport;`
- L277 _private member_ `TSharedPtr<SVEUVPlotViewport> PlotViewport;`
- L278 _private member_ `TSharedPtr<SCheckBox> LogScaleCheckbox;`
- L279 _private member_ `TSharedPtr<SBox> ViewportContainer;`
- L280 _private member_ `TSharedPtr<STextBlock> StatsText;`
- L281 _private member_ `TArray<TSharedPtr<int32>> ComboBoxSource;`
- L282 _private member_ `TSharedPtr<SComboBox<TSharedPtr<int32>>> BuildComboBox;`
- L283 _private member_ `TArray<TSharedPtr<int32>> SnapshotComboBoxSource;`
- L284 _private member_ `TSharedPtr<SComboBox<TSharedPtr<int32>>> SnapshotComboBox;`
- L287 _private member_ `int32 SelectedSnapshotIndex = INDEX_NONE;` — Snapshot history selection
- L290 _private member_ `float PlaybackFPS = 32.0f;` — Snapshot playback
- L291 _private member_ `float PlaybackAccumulator = 0.0f;`
- L292 _private member_ `bool bPlayingSnapshots = false;`

#### enum `SVEUVDebugPanel::ESampleFilter`  
`enum class ESampleFilter : uint8`  
_L259-266_
- desc: Sample visibility filter
- L261 _public enumerator_ `None`
- L262 _public enumerator_ `All`
- L263 _public enumerator_ `Area`
- L264 _public enumerator_ `Complexity`
- L265 _public enumerator_ `Adaptive`

#### Free symbols / members of external scopes

- L48 _delegate_ `DECLARE_DELEGATE(FOnViewChanged);`
- L153 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const FVEUVHitResult&);`
- L156 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDoubleClick, const FVEUVHitResult&);`
