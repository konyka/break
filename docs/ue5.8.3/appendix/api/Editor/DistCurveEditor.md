# Editor / DistCurveEditor

- module root: `Source/Editor/DistCurveEditor`
- headers: 8; symbols: 350
- symbol kinds: class=8, delegate=1, enum=3, enumerator=8, externvar=1, function=21, macro=13, member=136, namespace=1, prototype=148, struct=10
- DynamicallyLoadedModuleNames: MainFrame, PropertyEditor
- PrivateDependencyModuleNames: AppFramework, Core, CoreUObject, EditorFramework, Engine, InputCore, LevelEditor, RenderCore, Slate, SlateCore, UnrealEd
- PublicIncludePathModuleNames: UnrealEd

### `Source/Editor/DistCurveEditor/Private/CurveEditorActions.h` (Private)


#### class `FDistCurveEditorCommands`  
`class FDistCurveEditorCommands : public TCommands<FDistCurveEditorCommands>`  
_L18-59_
- inherits: `TCommands<FDistCurveEditorCommands>`
- L22 _public function_ `FDistCurveEditorCommands() : TCommands<FDistCurveEditorCommands>("CurveEditor", NSLOCTEXT("Contexts", "CurveEditor", "CurveEditor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L29 _public member_ `TSharedPtr<FUICommandInfo> RemoveCurve;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllCurves;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> SetTime;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> SetValue;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> SetColor;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> DeleteKeys;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ScaleTimes;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ScaleValues;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ScaleSingleCurveTimes;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ScaleSingleCurveValues;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> ScaleSingleSubCurveValues;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> FitHorizontally;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> FitVertically;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> Fit;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> PanMode;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> ZoomMode;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> CurveAuto;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> CurveAutoClamped;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> CurveUser;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> CurveBreak;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> Linear;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> Constant;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> FlattenTangents;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> StraightenTangents;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> ShowAllTangents;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> CreateTab;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> DeleteTab;`
- L58 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/DistCurveEditor/Private/CurveEditorHitProxies.h` (Private)


#### struct `HCurveEditorLabelProxy`  
`struct HCurveEditorLabelProxy : public HHitProxy`  
_L12-22_
- inherits: `HHitProxy`
- L14 _public prototype_ `DECLARE_HIT_PROXY();`
- L16 _public member_ `int32 CurveIndex;`
- L18 _public function_ `HCurveEditorLabelProxy(int32 InCurveIndex) : HHitProxy(HPP_UI), CurveIndex(InCurveIndex)`

#### struct `HCurveEditorHideCurveProxy`  
`struct HCurveEditorHideCurveProxy : public HHitProxy`  
_L24-34_
- inherits: `HHitProxy`
- L26 _public prototype_ `DECLARE_HIT_PROXY();`
- L28 _public member_ `int32 CurveIndex;`
- L30 _public function_ `HCurveEditorHideCurveProxy(int32 InCurveIndex) : HHitProxy(HPP_UI), CurveIndex(InCurveIndex)`

#### struct `HCurveEditorKeyProxy`  
`struct HCurveEditorKeyProxy : public HHitProxy`  
_L36-50_
- inherits: `HHitProxy`
- L38 _public prototype_ `DECLARE_HIT_PROXY();`
- L40 _public member_ `int32 CurveIndex;`
- L41 _public member_ `int32 SubIndex;`
- L42 _public member_ `int32 KeyIndex;`
- L44 _public function_ `HCurveEditorKeyProxy(int32 InCurveIndex, int32 InSubIndex, int32 InKeyIndex) : HHitProxy(HPP_UI), CurveIndex(InCurveIndex), SubIndex(InSubIndex), KeyIndex(InKeyIndex)`

#### struct `HCurveEditorKeyHandleProxy`  
`struct HCurveEditorKeyHandleProxy : public HHitProxy`  
_L52-68_
- inherits: `HHitProxy`
- L54 _public prototype_ `DECLARE_HIT_PROXY();`
- L56 _public member_ `int32 CurveIndex;`
- L57 _public member_ `int32 SubIndex;`
- L58 _public member_ `int32 KeyIndex;`
- L59 _public member_ `bool bArriving;`
- L61 _public function_ `HCurveEditorKeyHandleProxy(int32 InCurveIndex, int32 InSubIndex, int32 InKeyIndex, bool bInArriving) : HHitProxy(HPP_UI), CurveIndex(InCurveIndex), SubIndex(InSubIndex), KeyIndex(InKeyIndex), bArriving(bInArriving)`

#### struct `HCurveEditorLineProxy`  
`struct HCurveEditorLineProxy : public HHitProxy`  
_L70-82_
- inherits: `HHitProxy`
- L72 _public prototype_ `DECLARE_HIT_PROXY();`
- L74 _public member_ `int32 CurveIndex;`
- L75 _public member_ `int32 SubIndex;`
- L77 _public function_ `HCurveEditorLineProxy(int32 InCurveIndex, int32 InSubIndex) : HHitProxy(HPP_UI), CurveIndex(InCurveIndex), SubIndex(InSubIndex)`

#### struct `HCurveEditorLabelBkgProxy`  
`struct HCurveEditorLabelBkgProxy : public HHitProxy`  
_L84-88_
- inherits: `HHitProxy`
- L86 _public prototype_ `DECLARE_HIT_PROXY();`
- L87 _public function_ `HCurveEditorLabelBkgProxy(): HHitProxy(HPP_UI)`

#### struct `HCurveEditorHideSubCurveProxy`  
`struct HCurveEditorHideSubCurveProxy : public HHitProxy`  
_L90-102_
- inherits: `HHitProxy`
- L92 _public prototype_ `DECLARE_HIT_PROXY();`
- L94 _public member_ `int32 CurveIndex;`
- L95 _public member_ `int32 SubCurveIndex;`
- L97 _public function_ `HCurveEditorHideSubCurveProxy(int32 InCurveIndex, int32 InSubCurveIndex) : HHitProxy(HPP_UI), CurveIndex(InCurveIndex), SubCurveIndex(InSubCurveIndex)`

### `Source/Editor/DistCurveEditor/Private/CurveEditorSharedData.h` (Private)


#### struct `FCurveEditorModKey`  
`struct FCurveEditorModKey`  
_L34-49_
- L36 _public member_ `int32 CurveIndex;`
- L37 _public member_ `int32 KeyIndex;`
- L39 _public function_ `FCurveEditorModKey(int32 InCurveIndex, int32 InKeyIndex)`
- L45 _public function_ `bool operator==(const FCurveEditorModKey& Other) const`

#### struct `FCurveEditorSelectedKey`  
`struct FCurveEditorSelectedKey`  
_L56-86_
- L58 _public member_ `int32 CurveIndex;`
- L59 _public member_ `int32 SubIndex;`
- L60 _public member_ `int32 KeyIndex;`
- L61 _public member_ `float UnsnappedIn;`
- L62 _public member_ `float UnsnappedOut;`
- L64 _public function_ `FCurveEditorSelectedKey(int32 InCurveIndex, int32 InSubIndex, int32 InKeyIndex)`
- L73 _public function_ `bool operator==(const FCurveEditorSelectedKey& Other) const`

#### class `FCurveEditorSharedData`  
`class FCurveEditorSharedData`  
_L93-151_
- L97 _public prototype_ `FCurveEditorSharedData(UInterpCurveEdSetup* InEdSetup);` — Constructor/Destructor
- L98 _public prototype_ `virtual ~FCurveEditorSharedData();`
- L101 _public prototype_ `void SetCurveView(float StartIn, float EndIn, float StartOut, float EndOut);` — Sets up the viewing region
- L112 _public member_ `UInterpCurveEdSetup* EdSetup;` — Object for working with tabs and distribution data
- L115 _public member_ `UCurveEdOptions* EditorOptions;` — Object containing curve editor configuration info
- L118 _public member_ `FCurveEdNotifyInterface* NotifyObject;` — Object to be notified when changes are made to the curve editor
- L121 _public member_ `ECurveEdMode EdMode;` — Pan or zoom mode
- L124 _public member_ `TArray<FCurveEditorSelectedKey> SelectedKeys;` — Currently selected keys
- L127 _public member_ `int32 RightClickCurveIndex;` — Index of the curve that was right-clicked
- L128 _public member_ `int32 RightClickCurveSubIndex;`
- L131 _public member_ `const int32 LabelEntryHeight;` — Individual and total draw heights for labels
- L132 _public member_ `int32 LabelContentBoxHeight;`
- L135 _public member_ `float StartIn;` — Draw info
- L136 _public member_ `float EndIn;`
- L137 _public member_ `float StartOut;`
- L138 _public member_ `float EndOut;`
- L139 _public member_ `float MaxViewRange;`
- L140 _public member_ `float MinViewRange;`
- L141 _public member_ `bool bShowPositionMarker;`
- L142 _public member_ `float MarkerPosition;`
- L143 _public member_ `FColor MarkerColor;`
- L144 _public member_ `bool bShowEndMarker;`
- L145 _public member_ `float EndMarkerPosition;`
- L146 _public member_ `bool bShowRegionMarker;`
- L147 _public member_ `float RegionStart;`
- L148 _public member_ `float RegionEnd;`
- L149 _public member_ `FColor RegionFillColor;`
- L150 _public member_ `bool bShowAllCurveTangents;`

#### enum `FCurveEditorSharedData::ECurveEdMode`  
`enum ECurveEdMode`  
_L104-108_
- desc: Mouse drag mode types
- L106 _public enumerator_ `CEM_Pan`
- L107 _public enumerator_ `CEM_Zoom`

#### Free symbols / members of external scopes

- L9 _macro_ `#define CURVEED_MAX_CURVES 6`
- L11 _macro_ `#define CURVEEDENTRY_HIDECURVE_BIT (0x00000001) // Used by macros only`
- L12 _macro_ `#define CURVEEDENTRY_HIDECURVE(x) ((x) & CURVEEDENTRY_HIDECURVE_BIT)`
- L13 _macro_ `#define CURVEEDENTRY_TOGGLE_HIDECURVE(x) ((x) = ((x) ^ CURVEEDENTRY_HIDECURVE_BIT))`
- L14 _macro_ `#define CURVEEDENTRY_SET_HIDECURVE(x, flg) ((x) = ((flg) ? ((x) | CURVEEDENTRY_HIDECURVE_BIT) : ((x) &~ CURVEEDENTRY_HIDECURVE_BIT)))`
- L16 _macro_ `#define CURVEEDENTRY_HIDESUBCURVE_BIT(idx) (1 << ((idx) + 1)) // Used by macros only`
- L17 _macro_ `#define CURVEEDENTRY_HIDESUBCURVE(x, idx) ((x) & CURVEEDENTRY_HIDESUBCURVE_BIT(idx))`
- L18 _macro_ `#define CURVEEDENTRY_TOGGLE_HIDESUBCURVE(x, idx) ((x) = ((x) ^ CURVEEDENTRY_HIDESUBCURVE_BIT(idx)))`
- L19 _macro_ `#define CURVEEDENTRY_SET_HIDESUBCURVE(x, idx, flg) ((x) = ((flg) ? ((x) | CURVEEDENTRY_HIDESUBCURVE_BIT(idx)) : ((x) &~ CURVEEDENTRY_HIDESUBCURVE_BIT(idx))))`
- L21 _macro_ `#define CURVEEDENTRY_SELECTED_BIT (0x80000000) // Used by macros only`
- L22 _macro_ `#define CURVEEDENTRY_SELECTED(x) ((x) & CURVEEDENTRY_SELECTED_BIT)`
- L23 _macro_ `#define CURVEEDENTRY_TOGGLE_SELECTED(x) ((x) = ((x) ^ CURVEEDENTRY_SELECTED_BIT))`
- L24 _macro_ `#define CURVEEDENTRY_SET_SELECTED(x, flg) ((x) = ((flg) ? ((x) | CURVEEDENTRY_SELECTED_BIT) : ((x) &~ CURVEEDENTRY_SELECTED_BIT)))`

### `Source/Editor/DistCurveEditor/Private/CurveEditorViewportClient.h` (Private)


#### class `FCurveEditorViewportClient`  
`class FCurveEditorViewportClient : public FCommonViewportClient`  
_L29-172_
- inherits: `FCommonViewportClient`
- L33 _public prototype_ `FCurveEditorViewportClient(TWeakPtr<SDistributionCurveEditor> InCurveEditor, TWeakPtr<SCurveEditorViewport> InCurveEditorViewport);` — Constructor
- L37 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;` — FViewportClient interface
- L38 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L39 _public prototype_ `virtual void MouseMove(FViewport* Viewport, int32 X, int32 Y) override;`
- L40 _public prototype_ `virtual void CapturedMouseMove(FViewport* Viewport, int32 X, int32 Y) override;`
- L41 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& Args) override;`
- L44 _public prototype_ `void Exec(const TCHAR* Cmd);` — Exec handler
- L47 _public prototype_ `float GetViewportVerticalScrollBarRatio() const;` — Returns the ratio of the size of the particle emitters to the size of the viewport
- L50 _public prototype_ `void SetInSnap(bool bEnabled, float SnapAmount, bool bInSnapToFrames);` — Set snap behavior
- L53 _public prototype_ `virtual float UpdateViewportClientWindowDPIScale() const override;` — FViewport interface
- L64 _private prototype_ `bool ProcessNonGraphHit(HHitProxy* HitResult);` — Checks to see if the hit was on a non-graph element and processes
- L67 _private prototype_ `void UpdateScrollBars();` — Updates the states of the scrollbars
- L70 _private prototype_ `void ChangeViewportScrollBarPosition(EScrollDirection Direction);` — Changes the position of the vertical scrollbar (on a mouse scrollwheel event)
- L73 _private prototype_ `FVector2D GetViewportScrollBarPositions() const;` — Returns the positions of the scrollbars relative to the Particle Particles
- L76 _private prototype_ `void DrawEntry(FViewport* Viewport, FCanvas* Canvas, const FCurveEdEntry& Entry, int32 CurveIndex);` — Drawing utils
- L77 _private prototype_ `void DrawGrid(FViewport* Viewport, FCanvas* Canvas);`
- L80 _private prototype_ `FIntPoint CalcScreenPos(const FVector2D& Val);` — Helper methods
- L81 _private prototype_ `FVector2D CalcValuePoint(const FVector2D& Pos);`
- L82 _private prototype_ `FColor GetLineColor(FCurveEdInterface* EdInterface, float InVal, bool bFloatingPointColor);`
- L83 _private prototype_ `FVector2D CalcTangentDir(float Tangent);`
- L84 _private prototype_ `float CalcTangent(const FVector2D& HandleDelta);`
- L85 _private prototype_ `float SnapIn(float InValue);`
- L88 _private prototype_ `int32 AddNewKeypoint(int32 InCurveIndex, int32 InSubIndex, const FIntPoint& ScreenPos);` — Adds a new key
- L91 _private prototype_ `void AddKeyToSelection(int32 InCurveIndex, int32 InSubIndex, int32 InKeyIndex);` — Add/remove a key to/from the selection
- L92 _private prototype_ `void RemoveKeyFromSelection(int32 InCurveIndex, int32 InSubIndex, int32 InKeyIndex);`
- L95 _private prototype_ `bool KeyIsInSelection(int32 InCurveIndex, int32 InSubIndex, int32 InKeyIndex);` — Returns true if the specified key is currently selected
- L98 _private prototype_ `void BeginMoveSelectedKeys();` — Handles keys being moved by the user
- L99 _private prototype_ `void MoveSelectedKeys(float DeltaIn, float DeltaOut);`
- L100 _private prototype_ `void EndMoveSelectedKeys();`
- L103 _private prototype_ `void MoveCurveHandle(const FVector2D& NewHandleVal);` — Handles keys being moved by the user
- L106 _private prototype_ `void ToggleCurveHidden(int32 InCurveIndex);` — Hide/show curves
- L107 _private prototype_ `void ToggleSubCurveHidden(int32 InCurveIndex, int32 InSubCurveIndex);`
- L109 _private prototype_ `void HandleWindowDPIScaleChanged(TSharedRef<SWindow> Window);`
- L113 _private member_ `TWeakPtr<SDistributionCurveEditor> CurveEditorPtr;` — Pointer back to the Particle editor tool that owns us
- L116 _private member_ `TWeakPtr<SCurveEditorViewport> CurveEditorViewportPtr;` — Pointer back to the Particle viewport control that owns us
- L119 _private member_ `TSharedPtr<FCurveEditorSharedData> SharedData;` — Data and methods shared across multiple classes
- L121 _private member_ `FIntPoint LabelOrigin2D;`
- L123 _private member_ `const int32 LabelWidth;`
- L124 _private member_ `const int32 ColorKeyWidth;`
- L125 _private member_ `const float ZoomSpeed;`
- L126 _private member_ `const float MouseZoomSpeed;`
- L127 _private member_ `const float HandleLength;`
- L128 _private member_ `const float FitMargin;`
- L129 _private member_ `const int32 CurveDrawRes;`
- L131 _private member_ `int32 DragStartMouseX;`
- L132 _private member_ `int32 DragStartMouseY;`
- L133 _private member_ `int32 OldMouseX;`
- L134 _private member_ `int32 OldMouseY;`
- L135 _private member_ `bool bPanning;`
- L136 _private member_ `bool bMouseDown;`
- L137 _private member_ `bool bDraggingHandle;`
- L138 _private member_ `bool bBegunMoving;`
- L139 _private member_ `ECurveEdMovementAxisLock MovementAxisLock;`
- L140 _private member_ `bool bBoxSelecting;`
- L141 _private member_ `bool bKeyAdded;`
- L142 _private member_ `int32 DistanceDragged;`
- L143 _private member_ `int32 BoxStartX;`
- L144 _private member_ `int32 BoxStartY;`
- L145 _private member_ `int32 BoxEndX;`
- L146 _private member_ `int32 BoxEndY;`
- L148 _private member_ `float CurveViewX;`
- L149 _private member_ `float CurveViewY;`
- L150 _private member_ `float PixelsPerIn;`
- L151 _private member_ `float PixelsPerOut;`
- L152 _private member_ `FLinearColor BackgroundColor;`
- L153 _private member_ `FLinearColor LabelColor;`
- L154 _private member_ `FLinearColor SelectedLabelColor;`
- L155 _private member_ `FLinearColor GridColor;`
- L156 _private member_ `FLinearColor GridTextColor;`
- L157 _private member_ `FLinearColor LabelBlockBkgColor;`
- L158 _private member_ `FLinearColor SelectedKeyColor;`
- L160 _private member_ `int32 MouseOverCurveIndex;`
- L161 _private member_ `int32 MouseOverSubIndex;`
- L162 _private member_ `int32 MouseOverKeyIndex;`
- L164 _private member_ `int32 HandleCurveIndex;`
- L165 _private member_ `int32 HandleSubIndex;`
- L166 _private member_ `int32 HandleKeyIndex;`
- L167 _private member_ `bool bHandleArriving;`
- L169 _private member_ `bool bSnapEnabled;`
- L170 _private member_ `float InSnapAmount;`
- L171 _private member_ `bool bSnapToFrames;`

#### enum `FCurveEditorViewportClient::ECurveEdMovementAxisLock`  
`enum ECurveEdMovementAxisLock`  
_L56-61_
- desc: Curve editor key movement axis locking
- L58 _public enumerator_ `AxisLock_None`
- L59 _public enumerator_ `AxisLock_Horizontal`
- L60 _public enumerator_ `AxisLock_Vertical`

### `Source/Editor/DistCurveEditor/Private/SCurveEditorViewport.h` (Private)


#### class `SCurveEditorViewport`  
`class SCurveEditorViewport : public SCompoundWidget`  
_L23-88_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorViewport) : _CurveEdOptions(IDistributionCurveEditor::FCurveEdOptions())`
- L30 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SDistributionCurveEditor>, CurveEditor) SLATE_ARGUMENT(IDistributionCurveEditor::FCurveEdOptions, CurveEdOptions) SLATE_END_ARGS() ~SCurveEditorViewport();`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L41 _public prototype_ `void RefreshViewport();` — Refreshes the viewport
- L44 _public prototype_ `bool IsVisible() const;` — Returns true if the viewport is visible
- L47 _public prototype_ `void SetVerticalScrollBarPosition(float Position);` — Scrolls the scrollbar... expected range is from 0.0 to 1.0
- L53 _public prototype_ `void AdjustScrollBar();` — Updates the scroll bar for the current state of the window's size and content layout.  This should be called when either the window size changes or the vertical size of the content contained in the window changes.
- L56 _public prototype_ `TSharedPtr<FSceneViewport> GetViewport() const;` — Accessors
- L57 _public prototype_ `TSharedPtr<FCurveEditorViewportClient> GetViewportClient() const;`
- L58 _public prototype_ `TSharedPtr<SViewport> GetViewportWidget() const;`
- L59 _public prototype_ `TSharedPtr<SScrollBar> GetVerticalScrollBar() const;`
- L62 _protected prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L65 _protected prototype_ `EVisibility GetViewportVerticalScrollBarVisibility() const;` — Returns the visibility of the viewport scrollbars
- L68 _protected prototype_ `void OnViewportVerticalScrollBarScrolled(float InScrollOffsetFraction);` — Called when the viewport scrollbars are scrolled
- L72 _private member_ `TWeakPtr<SDistributionCurveEditor> CurveEditorPtr;` — Pointer back to the Texture editor tool that owns us
- L75 _private member_ `TSharedPtr<FCurveEditorViewportClient> ViewportClient;` — Level viewport client
- L78 _private member_ `TSharedPtr<FSceneViewport> Viewport;` — Slate viewport for rendering and I/O
- L81 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — Viewport widget
- L84 _private member_ `TSharedPtr<SScrollBar> ViewportVerticalScrollBar;` — Vertical scrollbar
- L87 _private member_ `int32 PrevViewportHeight;` — Height of the viewport on the last call to Tick

### `Source/Editor/DistCurveEditor/Private/SDistributionCurveEditor.h` (Private)


#### enum `ECurveScaleScope::Type`  
`enum Type`  
_L35-45_
- L38 _public enumerator_ `All` — All curves in the current editor
- L41 _public enumerator_ `Current` — The current curve
- L44 _public enumerator_ `CurrentSub` — The current sub-curve

#### class `SDistributionCurveEditor`  
`class SDistributionCurveEditor : public IDistributionCurveEditor`  
_L52-202_
- inherits: `IDistributionCurveEditor`
- L55 _public function_ `SLATE_BEGIN_ARGS(SDistributionCurveEditor) : _EdSetup(NULL) , _NotifyObject(NULL) , _CurveEdOptions(FCurveEdOptions())`
- L61 _public prototype_ `SLATE_ARGUMENT(UInterpCurveEdSetup*, EdSetup) SLATE_ARGUMENT(FCurveEdNotifyInterface*, NotifyObject) SLATE_ARGUMENT(FCurveEdOptions, CurveEdOptions) SLATE_END_ARGS() SDistributionCurveEditor();`
- L68 _public prototype_ `virtual ~SDistributionCurveEditor();`
- L71 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget functions
- L74 _public prototype_ `virtual void RefreshViewport() override;` — IDistributionCurveEditor interface
- L75 _public prototype_ `virtual void CurveChanged() override;`
- L76 _public prototype_ `virtual void SetCurveVisible(const UObject* InCurve, bool bShow) override;`
- L77 _public prototype_ `virtual void ClearAllVisibleCurves() override;`
- L78 _public prototype_ `virtual void SetCurveSelected(const UObject* InCurve, bool bSelected) override;`
- L79 _public prototype_ `virtual void ClearAllSelectedCurves() override;`
- L80 _public prototype_ `virtual void ScrollToFirstSelected() override;`
- L81 _public prototype_ `virtual void SetActiveTabToFirstSelected() override;`
- L82 _public prototype_ `virtual UInterpCurveEdSetup* GetEdSetup() override;`
- L83 _public prototype_ `virtual float GetStartIn() override;`
- L84 _public prototype_ `virtual float GetEndIn() override;`
- L85 _public prototype_ `virtual void SetPositionMarker(bool bEnabled, float InPosition, const FColor& InMarkerColor) override;`
- L86 _public prototype_ `virtual void SetEndMarker(bool bEnabled, float InEndPosition) override;`
- L87 _public prototype_ `virtual void SetRegionMarker(bool bEnabled, float InRegionStart, float InRegionEnd, const FColor& InRegionFillColor) override;`
- L88 _public prototype_ `virtual void SetInSnap(bool bEnabled, float SnapAmount, bool bInSnapToFrames) override;`
- L89 _public prototype_ `virtual void SetViewInterval(float StartIn, float EndIn) override;`
- L91 _public prototype_ `virtual void FitViewHorizontally() override;` — Fits the curve editor view horizontally to the curve data
- L93 _public prototype_ `virtual void FitViewVertically() override;` — Fits the curve editor view vertically to the curve data
- L96 _public prototype_ `TSharedPtr<FCurveEditorSharedData> GetSharedData();` — Accessors
- L99 _public prototype_ `void OnDeleteKeys();` — Toolbar/menu command methods
- L100 _public prototype_ `void OnFit();`
- L101 _public prototype_ `void OnFitToSelected();`
- L102 _public prototype_ `void OnFitHorizontally();`
- L103 _public prototype_ `void OnFitVertically();`
- L104 _public prototype_ `void OnSetTangentType(int32 NewType);`
- L107 _public prototype_ `void OpenLabelMenu();` — Methods for opening context menus
- L108 _public prototype_ `void OpenKeyMenu();`
- L109 _public prototype_ `void OpenGeneralMenu();`
- L110 _public prototype_ `void OpenCurveMenu();`
- L112 _public prototype_ `void CloseEntryPopup();`
- L115 _private prototype_ `void CreateLayout(FCurveEdOptions CurveEdOptions);` — Creates the geometry mode controls
- L118 _private prototype_ `EVisibility GetLargeIconVisibility() const;` — Query whether or not we're in small icon mode
- L121 _private prototype_ `TSharedRef<SHorizontalBox> BuildToolBar();` — Builds the toolbar widget for the ParticleSystem editor
- L124 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates
- L127 _private prototype_ `void OnRemoveCurve();` — Toolbar/menu command methods
- L128 _private prototype_ `void OnRemoveAllCurves();`
- L129 _private prototype_ `void OnSetTime();`
- L130 _private prototype_ `void OnSetValue();`
- L131 _private prototype_ `void OnSetColor();`
- L132 _private prototype_ `void OnScaleTimes(ECurveScaleScope::Type Scope);`
- L133 _private prototype_ `void OnScaleValues(ECurveScaleScope::Type Scope);`
- L134 _private prototype_ `void OnScaleSingleCurveTimes();`
- L135 _private prototype_ `void OnScaleSingleCurveValues();`
- L136 _private prototype_ `void OnSetMode(int32 NewMode);`
- L137 _private prototype_ `bool IsModeChecked(int32 Mode) const;`
- L138 _private prototype_ `bool IsTangentTypeChecked(int32 Type) const;`
- L139 _private prototype_ `void OnFlattenTangents();`
- L140 _private prototype_ `void OnStraightenTangents();`
- L141 _private prototype_ `void OnShowAllTangents();`
- L142 _private prototype_ `bool IsShowAllTangentsChecked() const;`
- L143 _private prototype_ `void OnCreateTab();`
- L144 _private prototype_ `void OnDeleteTab();`
- L147 _private prototype_ `TSharedRef<SWidget> BuildMenuWidgetLabel();` — Methods for building context menus
- L148 _private prototype_ `TSharedRef<SWidget> BuildMenuWidgetKey();`
- L149 _private prototype_ `TSharedRef<SWidget> BuildMenuWidgetGeneral();`
- L150 _private prototype_ `TSharedRef<SWidget> BuildMenuWidgetCurve();`
- L153 _private prototype_ `void TabSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — Methods related to the tab combobox
- L154 _private prototype_ `void SetTabSelection(TSharedPtr<FString> NewSelection, bool bUpdateWidget);`
- L157 _private prototype_ `void KeyTimeCommitted(const FText& CommentText, ETextCommit::Type CommitInfo);` — On commit callbacks for various user input dialogs
- L158 _private prototype_ `void KeyValueCommitted(const FText& CommentText, ETextCommit::Type CommitInfo);`
- L159 _private prototype_ `void ScaleTimeCommitted(const FText& CommentText, ETextCommit::Type CommitInfo, ECurveScaleScope::Type Scope);`
- L160 _private prototype_ `void ScaleValueCommitted(const FText& CommentText, ETextCommit::Type CommitInfo, ECurveScaleScope::Type Scope);`
- L161 _private prototype_ `void TabNameCommitted(const FText& CommentText, ETextCommit::Type CommitInfo);`
- L164 _private prototype_ `bool NotifyPendingCurveChange(bool bSelectedOnly);` — Helper function to handle undo/redo
- L167 _private prototype_ `void ModifyTangents(bool bDoStraighten);` — Straightens or flattens all curve tangents
- L170 _private prototype_ `TSharedPtr<FString> GetSelectedTab() const;` — Helper method to set selected tab
- L173 _private prototype_ `void IterateKeys(TFunctionRef<void(int32, int32, FCurveEdEntry&, FCurveEdInterface&)> IteratorCallback);` — Helper function to iterate all selected curve keys if any are selected, otherwise all the keys in all the curves
- L177 _private member_ `TSharedRef<FUICommandList> UICommandList;` — A list commands to execute if a user presses the corresponding keybinding in the text box
- L180 _private member_ `TSharedPtr<SCurveEditorViewport> Viewport;` — Viewport
- L183 _private member_ `TSharedPtr<SHorizontalBox> Toolbar;` — Toolbar
- L186 _private member_ `TSharedPtr<FCurveEditorSharedData> SharedData;` — Data and methods shared across multiple classes
- L189 _private member_ `TWeakPtr<IMenu> EntryMenu;` — Reference to owner of the current popup
- L192 _private member_ `TSharedPtr<STextComboBox> TabNamesComboBox;` — Tabs dropdown
- L195 _private member_ `TArray< TSharedPtr<FString> > TabNames;` — Names of the curve tabs
- L198 _private member_ `const float FitMargin;` — Buffer amount used when fitting the viewport to the curve
- L201 _private member_ `TSharedPtr<FString> SelectedTab;` — Selected Tab to use

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCurveEd, Log, All);`
- L30 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCurveEd, Log, All);`
- L33 _namespace_ `namespace ECurveScaleScope`

### `Source/Editor/DistCurveEditor/Public/DistCurveEditorModule.h` (Public)


#### class `IDistributionCurveEditorModule`  
`class IDistributionCurveEditorModule : public IModuleInterface`  
_L20-26_
- inherits: `IModuleInterface`
- L24 _public prototype_ `virtual TSharedRef<IDistributionCurveEditor> CreateCurveEditorWidget(UInterpCurveEdSetup* EdSetup, FCurveEdNotifyInterface* NotifyObject) = 0;`
- L25 _public prototype_ `virtual TSharedRef<IDistributionCurveEditor> CreateCurveEditorWidget(UInterpCurveEdSetup* EdSetup, FCurveEdNotifyInterface* NotifyObject, IDistributionCurveEditor::FCurveEdOptions Options) = 0;`

#### Free symbols / members of external scopes

- L13 _externvar_ `extern const FName DistCurveEditorAppIdentifier;`

### `Source/Editor/DistCurveEditor/Public/IDistCurveEditor.h` (Public)


#### class `FCurveEdNotifyInterface`  
`class FCurveEdNotifyInterface`  
_L14-31_
- L17 _public function_ `virtual void PreEditCurve(TArray<UObject*> CurvesAboutToChange)`
- L18 _public function_ `virtual void PostEditCurve()`
- L20 _public function_ `virtual void MovedKey()`
- L22 _public function_ `virtual void DesireUndo()`
- L23 _public function_ `virtual void DesireRedo()`
- L30 _public function_ `virtual void OnCurveLabelClicked(UObject* CurveObject)` — Called by the Curve Editor when a Curve Label is clicked on @param	CurveObject	The curve object whose label was clicked on

#### class `IDistributionCurveEditor`  
`class IDistributionCurveEditor : public SCompoundWidget`  
_L38-87_
- inherits: `SCompoundWidget`
- L42 _public prototype_ `virtual void RefreshViewport() = 0;` — Refreshes the viewport
- L45 _public prototype_ `virtual void CurveChanged() = 0;` — Clears selected keys and updates the viewport
- L48 _public prototype_ `virtual void SetCurveVisible(const UObject* InCurve, bool bShow) = 0;` — Shows a curve
- L51 _public prototype_ `virtual void ClearAllVisibleCurves() = 0;` — Hides all curves
- L54 _public prototype_ `virtual void SetCurveSelected(const UObject* InCurve, bool bSelected) = 0;` — Selects a curve
- L57 _public prototype_ `virtual void ClearAllSelectedCurves() = 0;` — Deselects all curves
- L60 _public prototype_ `virtual void ScrollToFirstSelected() = 0;` — Scrolls the curve labels to the first selected curve
- L63 _public prototype_ `virtual void SetActiveTabToFirstSelected() = 0;` — Finds/activates the tab containing the first selected curve
- L66 _public prototype_ `virtual UInterpCurveEdSetup* GetEdSetup() = 0;` — Accessors
- L67 _public prototype_ `virtual float GetStartIn() = 0;`
- L68 _public prototype_ `virtual float GetEndIn() = 0;`
- L69 _public prototype_ `virtual void SetPositionMarker(bool bEnabled, float InPosition, const FColor& InMarkerColor) = 0;`
- L70 _public prototype_ `virtual void SetEndMarker(bool bEnabled, float InEndPosition) = 0;`
- L71 _public prototype_ `virtual void SetRegionMarker(bool bEnabled, float InRegionStart, float InRegionEnd, const FColor& InRegionFillColor) = 0;`
- L72 _public prototype_ `virtual void SetInSnap(bool bEnabled, float SnapAmount, bool bInSnapToFrames) = 0;`
- L73 _public prototype_ `virtual void SetViewInterval(float StartIn, float EndIn) = 0;`
- L76 _public prototype_ `virtual void FitViewHorizontally() = 0;` — Fit Accessors
- L77 _public prototype_ `virtual void FitViewVertically() = 0;`

#### struct `IDistributionCurveEditor::FCurveEdOptions`  
`struct FCurveEdOptions`  
_L80-86_
- desc: Additional Options
- L82 _public member_ `bool bAlwaysShowScrollbar;`
- L83 _public function_ `FCurveEdOptions() :bAlwaysShowScrollbar(false)`
