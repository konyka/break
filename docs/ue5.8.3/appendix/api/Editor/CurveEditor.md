# Editor / CurveEditor

- module root: `Source/Editor/CurveEditor`
- headers: 130; symbols: 2826
- symbol kinds: class=95, delegate=23, enum=27, enumerator=113, function=601, macro=47, member=712, namespace=205, prototype=909, struct=88, typedef=3, variable=3
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, Core, CoreUObject, EditorFramework, Engine, InputCore, PropertyEditor, Slate, SlateCore, TimeManagement, ToolMenus, TraceLog, UMG, UnrealEd
- PublicDependencyModuleNames: SequencerWidgets

### `Source/Editor/CurveEditor/Private/CurveEditorContextMenu.h` (Private)


#### struct `FCurveEditorContextMenu`  
`struct FCurveEditorContextMenu`  
_L13-16_
- L15 _public prototype_ `static void BuildMenu(FMenuBuilder& MenuBuilder, TSharedRef<FCurveEditor> CurveEditor, TOptional<FCurvePointHandle> ClickedPoint, TOptional<FCurveModelID> HoveredCurve);`

### `Source/Editor/CurveEditor/Private/CurveEditorCopyBuffer.h` (Private)


#### class `UCurveEditorCopyableCurveKeys`  
`class UCurveEditorCopyableCurveKeys : public UObject`  
_L10-39_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TArray<FKeyPosition> KeyPositions;` — `UPROPERTY()`
- L19 _public member_ `TArray<FKeyAttributes> KeyAttributes;` — `UPROPERTY()`
- L23 _public member_ `FString ShortDisplayName;` — `UPROPERTY()` — This curve's short display name. Used in situations where other mechanisms provide enough context about what the curve is (such as "X")
- L27 _public member_ `FString LongDisplayName;` — `UPROPERTY()` — This curve's long display name. Used in situations where the UI doesn't provide enough context about what the curve is otherwise (such as "Floor.Transform.X")
- L31 _public member_ `FString IntentionName;` — `UPROPERTY()` — This curve's short intention (such as Transform.X or Scale.X). Used internally to match up curves when saving/restoring curves between different objects.
- L38 _public member_ `FString LongIntentionName;` — `UPROPERTY()` — This curve's long intention (such as foot_fk_l.Transform.X or foot_fk_r.Scale.X). Used internally to match up curves when saving/restoring curves between different objects. Long intention names have priority in copy/paste over short intention names, but we fall back to short intention if it's unclear what the user is trying to do.

#### class `UCurveEditorCopyBuffer`  
`class UCurveEditorCopyBuffer : public UObject`  
_L42-55_
- reflection: `UCLASS()`
- inherits: `UObject`
- L48 _public member_ `TArray<TObjectPtr<UCurveEditorCopyableCurveKeys>> Curves;` — `UPROPERTY(Instanced)`
- L51 _public member_ `double TimeOffset;` — `UPROPERTY()`
- L54 _public member_ `bool bAbsolutePosition;` — `UPROPERTY()`

### `Source/Editor/CurveEditor/Private/CurveEditorEditObjectContainer.h` (Private)


#### struct `FCurveEditorEditObjectContainer`  
`struct FCurveEditorEditObjectContainer : FGCObject`  
_L9-33_
- inherits: `FGCObject`
- L11 _public prototype_ `FCurveEditorEditObjectContainer() = default;`
- L13 _public prototype_ `FCurveEditorEditObjectContainer(const FCurveEditorEditObjectContainer&) = delete;`
- L14 _public prototype_ `FCurveEditorEditObjectContainer& operator=(const FCurveEditorEditObjectContainer&) = delete;`
- L16 _public prototype_ `FCurveEditorEditObjectContainer(FCurveEditorEditObjectContainer&&) = delete;`
- L17 _public prototype_ `FCurveEditorEditObjectContainer& operator=(FCurveEditorEditObjectContainer&&) = delete;`
- L19 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L26 _public function_ `virtual FString GetReferencerName() const override`
- L32 _public member_ `TMap<FCurveModelID, TMap<FKeyHandle, TObjectPtr<UObject>> > CurveIDToKeyProxies;`

### `Source/Editor/CurveEditor/Private/CurveEditorSelectionPrivate.h` (Private)


#### class `UE::CurveEditor::KeySelection::FAddInternal`  
`class FAddInternal`  
_L13-24_
- desc: Implements passkey pattern to restrict access to FCurveEditorSelection::AddInternal.
- L17 _private function_ `explicit FAddInternal( FCurveEditorSelection& Selection, FCurveModelID CurveID, ECurvePointType PointType, TArrayView<const FKeyHandle> Keys, bool bIncrementSerialNumber = true )`

#### class `UE::CurveEditor::KeySelection::FSetSerialNumber`  
`class FSetSerialNumber`  
_L27-37_
- desc: Implements passkey pattern to restrict access to FCurveEditorSelection::SerialNumber.
- L31 _private function_ `explicit FSetSerialNumber( FCurveEditorSelection& Selection, int32 NewSerialNumber )`

#### class `UE::CurveEditor::KeySelection::FIncrementOnSelectionChangedSuppressionCount`  
`class FIncrementOnSelectionChangedSuppressionCount`  
_L40-50_
- desc: Implements passkey pattern to restrict access to FCurveEditorSelection::IncrementOnSelectionChangedSuppressionCount.
- L44 _private function_ `explicit FIncrementOnSelectionChangedSuppressionCount( FCurveEditorSelection& Selection )`

#### class `UE::CurveEditor::KeySelection::FDecrementOnSelectionChangedSuppressionCount`  
`class FDecrementOnSelectionChangedSuppressionCount`  
_L53-63_
- desc: Implements passkey pattern to restrict access to FCurveEditorSelection::DecrementOnSelectionChangedSuppressionCount.
- L57 _private function_ `explicit FDecrementOnSelectionChangedSuppressionCount( FCurveEditorSelection& Selection )`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditor` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)
- L10 _namespace_ `namespace KeySelection` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Private/CurveEditorTrace.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `UE_TRACE_CHANNEL_EXTERN(CurveEditorChannel);`
- L8 _macro_ `#define SCOPED_CURVE_EDITOR_TRACE(TraceName) TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(TraceName, CurveEditorChannel)`

### `Source/Editor/CurveEditor/Private/CurveEditorViewRegistry.h` (Private)


#### class `FCurveEditorViewRegistry`  
`class FCurveEditorViewRegistry`  
_L17-63_
- desc: Central, private registry of distinct view types that can be added to any curve editor panel based on which views the selected set of curve model's supports. Public interface is through ICurveEditorModule::RegisterView and ICurveEditorModule::UnregisterView
- L24 _public prototype_ `static FCurveEditorViewRegistry& Get();` — Singleton access to the view registry
- L34 _public prototype_ `ECurveEditorViewID RegisterCustomView(const FOnCreateCurveEditorView& InCreateViewDelegate);` — Register a new view type @note: A maximum of 64 registered view types are supported. View type IDs are not recycled. @param InCreateViewDelegate    (required) A bound delegate that creates a new instance of the view widget. Delegate signature is TSharedRef<SCurveEditorView> Function(TWeakPtr<FCurveEditor>); @return A new custom view ID that identifies the registered view type. Any curve models that wish to support this view must |= this enum to its FCurveModel::SupportedViews;
- L42 _public prototype_ `void UnregisterCustomView(ECurveEditorViewID ViewID);` — Unregister a previously registered view type @param ViewID                  The view ID obtained from calling RegisterCustomView. Must be >= ECurveEditorViewID::CUSTOM_START
- L52 _public prototype_ `TSharedPtr<SCurveEditorView> ConstructView(ECurveEditorViewID ViewID, TWeakPtr<FCurveEditor> WeakCurveEditor);` — Construct an instance of a view widget from its identifier @param ViewID                  The Identifier of the view to create. Must be a single ID, not a bitwise combination of IDs. @param WeakCurveEditor         A weak pointer to the curve editor on which the view is to be added. @return A new curve editor view widget, or nullptr if the ViewID does not correspond to a registered view type.
- L56 _private prototype_ `FCurveEditorViewRegistry();`
- L59 _private member_ `ECurveEditorViewID NextViewID;` — (default: ECurveEditorViewID::CUSTOM_START) The ID that the next registered view will receive
- L62 _private member_ `TMap<ECurveEditorViewID, FOnCreateCurveEditorView> CustomViews;` — Mapping of single view IDs to their factory delegates

### `Source/Editor/CurveEditor/Private/DragOperations/CurveEditorDragOperation_Marquee.h` (Private)


#### class `FCurveEditorDragOperation_Marquee`  
`class FCurveEditorDragOperation_Marquee : public ICurveEditorDragOperation`  
_L18-43_
- inherits: `ICurveEditorDragOperation`
- L22 _public prototype_ `FCurveEditorDragOperation_Marquee(FCurveEditor* InCurveEditor);`
- L23 _public prototype_ `FCurveEditorDragOperation_Marquee(FCurveEditor* InCurveEditor, SCurveEditorView* InLockedToView);`
- L25 _public prototype_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual void OnEndDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual void OnPaint(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId) override;`
- L33 _private member_ `TOptional<UE::CurveEditor::FScopedSelectionChange> SelectionChange;` — Makes this change undo / redo able. Set for the duration of the drag.
- L36 _private member_ `FSlateRect Marquee;` — The current marquee rectangle
- L38 _private member_ `FCurveEditor* CurveEditor;` — Ptr back to the curve editor
- L40 _private member_ `SCurveEditorView* LockedToView;` — When valid, marquee selection should only occur inside this view; all geometries are in local space
- L42 _private member_ `FVector2D RealInitialPosition;` — Real Initial Position do to the delayed drag

### `Source/Editor/CurveEditor/Private/DragOperations/CurveEditorDragOperation_MoveKeys.h` (Private)


#### class `FCurveEditorDragOperation_MoveKeys`  
`class FCurveEditorDragOperation_MoveKeys : public ICurveEditorKeyDragOperation`  
_L18-79_
- inherits: `ICurveEditorKeyDragOperation`
- L23 _public prototype_ `virtual void OnInitialize(FCurveEditor* CurveEditor, const TOptional<FCurvePointHandle>& CardinalPoint) override;`
- L24 _public prototype_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L25 _public prototype_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `virtual void OnFinishedPointerInput() override;`
- L27 _public prototype_ `virtual void OnEndDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual void OnCancelDrag() override;`
- L34 _private member_ `FCurveEditor* CurveEditor;` — Ptr back to the curve editor
- L35 _private member_ `TOptional<FCurvePointHandle> CardinalPoint;`
- L37 _private member_ `FVector2D LastMousePosition;`
- L40 _private member_ `TOptional<UE::CurveEditor::FScopedCurveChange> ScopedKeyChange;` — Transacts the moved keys.
- L61 _private member_ `TArray<FKeyData> KeysByCurve;` — Key dragging data stored per-curve
- L63 _private member_ `FCurveEditorAxisSnap::FSnapState SnappingState;`
- L74 _private member_ `TOptional<FAccumulatedMouseMovement> AccumulatedMouseMovement;`
- L76 _private prototype_ `FAccumulatedMouseMovement& GetOrAddAccumulatedMouseMovement(const FVector2D& InitialPosition);`
- L78 _private prototype_ `void UpdateFromDrag(const FVector2D& InitialPosition, const FVector2D& MousePosition);`

#### struct `FCurveEditorDragOperation_MoveKeys::FKeyData`  
`struct FKeyData`  
_L42-58_
- L44 _public function_ `FKeyData(FCurveModelID InCurveID) : CurveID(InCurveID)`
- L49 _public member_ `FCurveModelID CurveID;` — The curve that contains the keys we're dragging
- L51 _public member_ `TArray<FKeyHandle> Handles;` — All the handles within a given curve that we are dragging
- L53 _public member_ `TArray<FKeyPosition> StartKeyPositions;` — The extended key info for each of the above handles
- L55 _public member_ `TArray<FKeyPosition> LastDraggedKeyPositions;` — Used in OnEndDrag to send final key updates
- L57 _public member_ `FTransform2d InitialDragTransform;` — Initial curve transform for this curve

#### struct `FCurveEditorDragOperation_MoveKeys::FAccumulatedMouseMovement`  
`struct FAccumulatedMouseMovement`  
_L65-73_
- L67 _public member_ `const FVector2D InitialPosition;`
- L68 _public member_ `FVector2D EndMousePosition;`
- L70 _public function_ `explicit FAccumulatedMouseMovement(const FVector2D& InitialPosition) : InitialPosition(InitialPosition)`

### `Source/Editor/CurveEditor/Private/DragOperations/CurveEditorDragOperation_Pan.h` (Private)


#### class `FCurveEditorDragOperation_PanView`  
`class FCurveEditorDragOperation_PanView : public ICurveEditorDragOperation`  
_L15-36_
- inherits: `ICurveEditorDragOperation`
- L18 _public prototype_ `FCurveEditorDragOperation_PanView(FCurveEditor* CurveEditor, TSharedPtr<SCurveEditorView> InView);`
- L20 _public prototype_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L21 _public prototype_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L22 _public prototype_ `virtual FReply OnMouseWheel(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L26 _private member_ `FCurveEditor* CurveEditor;`
- L27 _private member_ `TSharedPtr<SCurveEditorView> View;`
- L29 _private member_ `bool bIsDragging;`
- L31 _private member_ `double InitialInputMin, InitialInputMax;`
- L31 _private member_ `double InitialInputMin, InitialInputMax;`
- L32 _private member_ `double InitialOutputMin, InitialOutputMax;`
- L32 _private member_ `double InitialOutputMin, InitialOutputMax;`
- L33 _private member_ `FCurveEditorAxisSnap::FSnapState SnappingState;`
- L34 _private member_ `FVector2D LastMousePosition;`

#### class `FCurveEditorDragOperation_PanInput`  
`class FCurveEditorDragOperation_PanInput : public ICurveEditorDragOperation`  
_L38-50_
- inherits: `ICurveEditorDragOperation`
- L41 _public prototype_ `FCurveEditorDragOperation_PanInput(FCurveEditor* CurveEditor);`
- L43 _public prototype_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L44 _public prototype_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L48 _private member_ `FCurveEditor* CurveEditor;`
- L49 _private member_ `double InitialInputMin, InitialInputMax;`
- L49 _private member_ `double InitialInputMin, InitialInputMax;`

### `Source/Editor/CurveEditor/Private/DragOperations/CurveEditorDragOperation_ScrubTime.h` (Private)


#### class `FCurveEditorDragOperation_ScrubTime`  
`class FCurveEditorDragOperation_ScrubTime : public ICurveEditorDragOperation`  
_L16-36_
- inherits: `ICurveEditorDragOperation`
- L19 _public prototype_ `FCurveEditorDragOperation_ScrubTime(FCurveEditor* CurveEditor);`
- L21 _public prototype_ `virtual void OnMouseButtonDown(FVector2D InitialPosition, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L22 _public prototype_ `virtual void OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L23 _public prototype_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L24 _public prototype_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L25 _public prototype_ `virtual void OnEndDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual void OnCancelDrag() override;`
- L31 _private member_ `FCurveEditor* CurveEditor;`
- L32 _private member_ `FCurveEditorAxisSnap::FSnapState SnappingState;`
- L33 _private member_ `FVector2D LastMousePosition;`
- L34 _private member_ `double InitialTime;`
- L35 _private member_ `ETimeSliderPlaybackStatus NextPlayerStatus;`

### `Source/Editor/CurveEditor/Private/DragOperations/CurveEditorDragOperation_Tangent.h` (Private)


#### class `CurveEditorDragOperation::FTangentSolver`  
`class FTangentSolver`  
_L22-104_
- desc: Solves the tangent offset for a single key depending on mouse button and modifier keys
- L25 _public prototype_ `FTangentSolver(ECurvePointType InPointType, FKeyAttributes InInitialKeyAttributes);`
- L34 _public prototype_ `void Process(FCurveEditor* CurveEditor, const FPointerEvent& MouseEvent, const FCurveEditorScreenSpace& CurveSpace, const FVector2D& PixelDelta);` — Solves the tangent considering the current mouse position, the mouse buttons and modifier keys @param MouseEvent			The mouse event to Process @param CurveSpace			The screen space of the curve editor @param PixelDelta			The mouse position delta from the initial mouse position in pixels
- L37 _public function_ `const FKeyAttributes& GetKeyAttributes() const` — Returns the current key attributes
- L40 _public function_ `const FKeyAttributes& GetInitialKeyAttributes() const` — Returns the initial key attributes
- L82 _private prototype_ `void SolveTangentConstantWeight(const FSolverParams& Params);` — Solves tangent leaving the weight untouched. Useful when tangent weight mode is disabled.
- L85 _private prototype_ `void SolveTangentMutableWeight(const FSolverParams& Params, float InitialWeight);` — Solves tangent and weight. Useful when tangent weight mode is enabled.
- L91 _private prototype_ `void MendNearlyZeroXTangentOffset(const bool bArriveTangent, FVector2D& InOutTangentOffset) const;` — Prevents the handle from crossing over the 0 point. Curve editor would handle it but it creates an ugly pop in the curve and it lets the Arrive tangents become Leave tangents which defeats the point.
- L94 _private member_ `TOptional<FVector2D> LastTangentOffset;` — Holds the last tanget offset. Useful when editing the tangent or weight exclusively.
- L97 _private member_ `FKeyAttributes KeyAttributes;` — The current attributes
- L100 _private member_ `const FKeyAttributes InitialKeyAttributes;` — The initial attributes of the key
- L103 _private member_ `const ECurvePointType PointType;` — The point type of the key handle for which the tangent is solved

#### struct `CurveEditorDragOperation::FTangentSolver::FSolverParams`  
`struct FSolverParams`  
_L44-79_
- desc: Struct that holds relevant data to compute the new tangent
- L46 _public prototype_ `FSolverParams( FCurveEditor* InCurveEditor, const FPointerEvent& InMouseEvent, const FCurveEditorScreenSpace& InCurveSpace, const FVector2D& InPixelDelta, const float InDisplayRatio, const bool bInArriveTangent, const float InInitialTangent);`
- L56 _public member_ `FCurveEditor* CurveEditor;` — The curve editor
- L59 _public member_ `const FPointerEvent& MouseEvent;` — The current mouse event
- L62 _public member_ `const FCurveEditorScreenSpace& CurveSpace;` — The current curve space
- L65 _public member_ `const FVector2D& PixelDelta;` — The delta of the mouse cursor from the initial position in pixels
- L68 _public member_ `const float DisplayRatio;` — The current display ratio
- L71 _public member_ `const bool bArriveTangent;` — True if the tangent to process is an arrive tangent, else it is a leave tangent
- L74 _public member_ `const float InitialTangent;` — The initial tangent when the drag drop op started
- L77 _public prototype_ `FSolverParams(const FSolverParams&) = delete;` — Non-copyable
- L78 _public prototype_ `FSolverParams& operator=(const FSolverParams&) = delete;`

#### class `FCurveEditorDragOperation_Tangent`  
`class FCurveEditorDragOperation_Tangent : public ICurveEditorKeyDragOperation`  
_L107-144_
- inherits: `ICurveEditorKeyDragOperation`
- L111 _public prototype_ `virtual void OnInitialize(FCurveEditor* InCurveEditor, const TOptional<FCurvePointHandle>& InCardinalPoint) override;`
- L112 _public prototype_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L113 _public prototype_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L114 _public prototype_ `virtual void OnEndDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L115 _public prototype_ `virtual void OnCancelDrag() override;`
- L119 _private member_ `FCurveEditor* CurveEditor;` — Ptr back to the curve editor
- L140 _private member_ `TArray<FKeyData> KeysByCurve;` — Key dragging data stored per-curve
- L143 _private member_ `TOptional<UE::CurveEditor::FScopedCurveChange> ScopedKeyChange;` — Transacts the keys' tangents.

#### struct `FCurveEditorDragOperation_Tangent::FKeyData`  
`struct FKeyData`  
_L123-137_
- L125 _public function_ `FKeyData(FCurveModelID InCurveID) : CurveID(InCurveID)`
- L130 _public member_ `FCurveModelID CurveID;` — The curve that contains the keys we're dragging
- L133 _public member_ `TArray<FKeyHandle> Handles;` — The handles that are being dragged
- L136 _public member_ `TArray<CurveEditorDragOperation::FTangentSolver> TangentSolvers;` — Tangent solvers for the handles that are being dragged

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace CurveEditorDragOperation`

### `Source/Editor/CurveEditor/Private/DragOperations/CurveEditorDragOperation_Zoom.h` (Private)


#### class `FCurveEditorDragOperation_Zoom`  
`class FCurveEditorDragOperation_Zoom : public ICurveEditorDragOperation`  
_L14-34_
- inherits: `ICurveEditorDragOperation`
- L18 _public prototype_ `FCurveEditorDragOperation_Zoom(FCurveEditor* InCurveEditor, TSharedPtr<SCurveEditorView> InOptionalView = nullptr);`
- L20 _public prototype_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L21 _public prototype_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent) override;`
- L25 _private member_ `FCurveEditor* CurveEditor;`
- L26 _private member_ `TSharedPtr<SCurveEditorView> OptionalView;`
- L28 _private member_ `FVector2D ZoomFactor;`
- L29 _private member_ `double ZoomOriginX, ZoomOriginY;`
- L29 _private member_ `double ZoomOriginX, ZoomOriginY;`
- L30 _private member_ `double OriginalInputRange, OriginalOutputRange;`
- L30 _private member_ `double OriginalInputRange, OriginalOutputRange;`
- L32 _private prototype_ `double GetZoomMultiplier_InputAxis(double InMovedMouseX) const;`
- L33 _private prototype_ `double GetZoomMultiplier_OutputAxis(double InMovedMouseY) const;`

### `Source/Editor/CurveEditor/Private/DragOperations/KeyDragOperationUtils.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditor` (scope `UE`)
- L18 _prototype_ `TUniquePtr<ICurveEditorKeyDragOperation> CreateAndInitializeKeyDrag( FCurveEditor& InCurveEditor, ECurvePointType InKeyType, const TOptional<FCurvePointHandle>& InCardinalPoint );` (scope `UE::CurveEditor`) — Creates the drag operation based on InKeyType.
- L23 _prototype_ `TUniquePtr<FScopedTransaction> CreateKeyOperationTransaction(ECurvePointType InKeyType, const int32 InNumKeys);` (scope `UE::CurveEditor`) — Creates the transaction that the ICurveEditorKeyDragOperation created by CreateKeyDrag would use.
- L25 _prototype_ `TUniquePtr<FScopedTransaction> CreateKeyOperationTransaction(const FCurveEditor& InCurveEditor, ECurvePointType InKeyType);` (scope `UE::CurveEditor`) — Version that determines the number of selected keys.

### `Source/Editor/CurveEditor/Private/Filters/CurveEditorBakeFilterCustomization.h` (Private)


#### class `FCurveEditorBakeFilterCustomization`  
`class FCurveEditorBakeFilterCustomization : public IDetailCustomization`  
_L14-26_
- inherits: `IDetailCustomization`
- desc: Customizes a UCurveEditorBakeFilter
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/CurveEditor/Private/Filters/FilterUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditor` (scope `UE`)
- L14 _namespace_ `namespace FilterUtils` (scope `UE::CurveEditor`)
- L17 _prototype_ `void ApplyFilter(const TSharedRef<FCurveEditor>& InCurveEditor, UCurveEditorFilterBase& InFilter);` (scope `UE::CurveEditor::FilterUtils`) — Applies the filter to the entire user selection.
- L20 _prototype_ `void ApplyFilter( const TSharedRef<FCurveEditor>& InCurveEditor, UCurveEditorFilterBase& InFilter, const TMap<FCurveModelID, FKeyHandleSet>& InSelectedKeys, bool bResetSelection );` (scope `UE::CurveEditor::FilterUtils`) — Applies the filter to the supplied keys.

### `Source/Editor/CurveEditor/Private/Misc/Attributes/AttributeAccumulationUtils.h` (Private)


#### struct `UE::CurveEditor::FAccumulatedCurveInfo`  
`struct FAccumulatedCurveInfo`  
_L14-19_
- desc: Used to hold curve and key attributes to update the Common Curve Info with.
- L16 _public member_ `bool bSelectionSupportsWeightedTangents = false;`
- L17 _public member_ `TOptional<FCurveAttributes> CurveAttributes;`
- L18 _public member_ `TOptional<FKeyAttributes> KeyAttributes;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L22 _prototype_ `void UpdateCommonCurveInfo(const FCurveEditor& InCurveEditor, bool& bOutSelectionSupportsWeightedTangents, FCurveAttributes& OutCachedCommonCurveAttributes, FKeyAttributes& OutCachedCommonKeyAttributes);` (scope `UE::CurveEditor`) — Update current curve selection attributes, if no keys are selected, info of all curves currently contained in the Curve Editor is used.
- L25 _prototype_ `FAccumulatedCurveInfo AccumulateSelectedCurvesInfo(const FCurveEditor& InCurveEditor);` (scope `UE::CurveEditor`) — Gather curve and key attributes from all currently selected curves.
- L27 _prototype_ `FAccumulatedCurveInfo AccumulateAllCurvesInfo(const FCurveEditor& InCurveEditor);` (scope `UE::CurveEditor`) — Gather curve and key attributes from all curves currently contained in the Curve Editor regardless of visibility. .
- L30 _prototype_ `void AccumulateCurveInfo(const FCurveModel* InCurve, TConstArrayView<const FKeyHandle> InKeys, FAccumulatedCurveInfo& InOutAccumulatedAttributes);` (scope `UE::CurveEditor`) — Add curve and key attributes from the given curve and the keys on it to the accumulated info.

### `Source/Editor/CurveEditor/Private/Misc/Attributes/SharedCurveInfoModel.h` (Private)


#### class `UE::CurveEditor::FSharedCurveInfoModel`  
`class FSharedCurveInfoModel : public FNoncopyable, public FTickableEditorObject`  
_L22-74_
- inherits: `FNoncopyable,FTickableEditorObject`
- desc: Keeps track of information that is shared for all keys: either for all selected keys, or if no keys are selected, all keys in view. Detects when changes are made to the curves and refreshes the informationa at the end of tick.
- L26 _public prototype_ `explicit FSharedCurveInfoModel(const TSharedRef<FCurveEditor>& InCurveEditor, const TSharedRef<SCurveEditorViewContainer>& InViewContainer);`
- L27 _public prototype_ `~FSharedCurveInfoModel();`
- L29 _public function_ `bool DoesSelectionSupportWeightedTangents() const`
- L30 _public function_ `const FCurveAttributes& GetCachedCommonCurveAttributes() const`
- L31 _public function_ `const FKeyAttributes& GetCachedCommonKeyAttributes() const`
- L33 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L34 _public prototype_ `virtual TStatId GetStatId() const override;`
- L39 _private member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — Owning curve editor. Needed to (un)subscribe from relevant change events.
- L47 _private member_ `const TWeakPtr<SCurveEditorViewContainer> ViewContainer;` — This is used to detect any external changes made to curves. Specifically, this UI calls FCurveModel::HasChangedAndResetTest and broadcasts a delegate when a change is detected. Ideally, we would not reference UI here but another model.
- L50 _private member_ `FCurveChangeListener CurveModifiedListener;` — Subscribed to FCurveModel::OnCurveModified of all curves.
- L52 _private member_ `uint32 ActiveCurvesSerialNumber;` — Last FCurveEditor::ActiveCurvesSerialNumber. Used to detect changes.
- L55 _private member_ `bool bSelectionSupportsWeightedTangents = false;` — True if the current selection supports weighted tangents, false otherwise
- L57 _private member_ `FCurveAttributes CachedCommonCurveAttributes;` — Cached curve attributes that are common to all visible curves
- L59 _private member_ `FKeyAttributes CachedCommonKeyAttributes;` — Cached key attributes that are common to all selected keys
- L62 _private prototype_ `void DeferToRefreshToEndOfFrame();` — Enqueues a call to Refresh that will take place at the end of the current tick.
- L64 _private prototype_ `void Refresh();` — Updates the shared curve info
- L66 _private prototype_ `bool HasDeferredRefresh() const;` — @return Whether a call to Refresh is enqueued
- L68 _private prototype_ `void ClearPendingRefresh() const;` — Clears the subscription to FCoreDelegates.
- L71 _private function_ `void OnCurveArrayChanged(FCurveModel*, bool, const FCurveEditor*)` — On next Refresh, we'll resubscribe to all FCurveModel::OnCurveModified delegates.
- L73 _private function_ `void OnCurveHasChanged(const FCurveModelID&)` — Invoked when some FCurveModel::HasChangedAndRestTest returned true.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Misc/SmartSnap.h` (Private)


#### struct `UE::CurveEditor::FSmartSnapResult`  
`struct FSmartSnapResult`  
_L22-27_
- L24 _public member_ `TArray<FKeyHandle> RemovedKeys;`
- L25 _public member_ `TArray<FKeyHandle> UpdatedKeys;`
- L26 _public member_ `TArray<FKeyPosition> NewPositions;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CurveEditor` (scope `UE`)
- L20 _prototype_ `bool CanSmartSnapSelection(const FCurveEditorSelection& InSelection);` (scope `UE::CurveEditor`) — @return Whether the selection contains keys that can be snapped.
- L30 _prototype_ `void EnumerateSmartSnappableKeys( const FCurveEditor& InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect, const TFunctionRef<void(const FCurveModelID& CurveModelId, FCurveModel& CurveModel, const FSmartSnapResult& SnapResult)>& InProcessSmartSnapping );` (scope `UE::CurveEditor`) — Calls InProcessSmartSnapping for each curve on which smart snapping can be performed.
- L38 _prototype_ `FSmartSnapResult ComputeSmartSnap( const FCurveModel& InModel, TConstArrayView<FKeyHandle> InHandles, TConstArrayView<FKeyPosition> InPositions, const FFrameRate& InFrameRate );` (scope `UE::CurveEditor`) — Computes how to modify the curve model: Tries to snap keys to the closest whole frame placing the key on the intersection of curve and an imaginary vertical frame.
- L43 _prototype_ `void ApplySmartSnap( FCurveModel& InModel, const FSmartSnapResult& InSmartSnap, double CurrentTime = 0.0 );` (scope `UE::CurveEditor`) — Applies the computed smart snapping to InModel.

### `Source/Editor/CurveEditor/Private/Modification/CurveEditorTransactionObject.h` (Private)


#### class `UCurveEditorTransactionObject`  
`class UCurveEditorTransactionObject : public UObject`  
_L18-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The object type that the transaction system associates FCommandChanges for the FCurveEditor with. By design, the transaction system requires a UObject to associate FCommandChanges with. This is usually an asset. Conceptually, instances of this class will act as an "asset" and the associated FCurveEditor contains the "asset data", i.e. its  FCurveModels.
- L24 _public member_ `TWeakPtr<FCurveEditor> OwningCurveEditor;` — The curve editor this object is associated with. Used by commands to retrieve the

### `Source/Editor/CurveEditor/Private/Modification/Keys/CurveAttributeChangeUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditor` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditor` (scope `UE`)
- L14 _namespace_ `namespace CurveAttributes` (scope `UE::CurveEditor`)
- L22 _prototype_ `FCurveAttributeChangeData_PerCurve Diff(const FCurveAttributes& InOriginal, const FCurveAttributes& InTarget);` (scope `UE::CurveEditor::CurveAttributes`) — Computes the delta change to get from InOriginal to InTarget. @param InOriginal The original curve attributes. @param InTarget The new curve attributes.
- L25 _prototype_ `void ApplyChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FCurveAttributeChangeData& InDeltaChange);` (scope `UE::CurveEditor::CurveAttributes`) — Applies InDeltaChange to InCurves (redo).
- L27 _prototype_ `void RevertChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FCurveAttributeChangeData& InDeltaChange);` (scope `UE::CurveEditor::CurveAttributes`) — Reverts InDeltaChange from InCurves (undo).

### `Source/Editor/CurveEditor/Private/Modification/Keys/Diff/AllCurvesGenericChangeBuilder.h` (Private)


#### class `UE::CurveEditor::FAllCurvesGenericChangeBuilder`  
`class FAllCurvesGenericChangeBuilder : public IMultiCurveChangeVisitor`  
_L13-29_
- inherits: `IMultiCurveChangeVisitor`
- desc: Aggregates all curve changes into a single FGenericCurveChangeData.
- L17 _public member_ `FGenericCurveChangeData CurveChangeData;`
- L19 _public function_ `explicit FAllCurvesGenericChangeBuilder(const FCurveEditor& InCurveEditor UE_LIFETIMEBOUND) : CurveEditor(InCurveEditor)`
- L22 _public prototype_ `virtual void ProcessChange(const FCurveModelID& InCurveModel, TFunctionRef<void(ISingleCurveChangeVisitor&)> InProcessCallback) override;`
- L28 _private member_ `const FCurveEditor& CurveEditor;` — Curve editor instance. Caller is responsible for keeping it alive.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Modification/Keys/Diff/AppendPerCurveGenericChangeVisitor.h` (Private)


#### class `UE::CurveEditor::FAppendPerCurveGenericChangeVisitor`  
`class FAppendPerCurveGenericChangeVisitor : public ISingleCurveChangeVisitor`  
_L11-46_
- inherits: `ISingleCurveChangeVisitor`
- L13 _private member_ `const FCurveModelID CurveId;`
- L14 _private member_ `FGenericCurveChangeData& CurveChangeData;`
- L17 _public function_ `explicit FAppendPerCurveGenericChangeVisitor(const FCurveModelID InCurveId, FGenericCurveChangeData& InCurveChangeData UE_LIFETIMEBOUND) : CurveId(InCurveId) , CurveChangeData(InCurveChangeData)`
- L22 _public function_ `virtual void ProcessMoveKeys(FMoveKeysChangeData_PerCurve&& InData) override`
- L27 _public function_ `virtual void ProcessAddKeys(FCurveKeyData&& InData) override`
- L32 _public function_ `virtual void ProcessRemoveKeys(FCurveKeyData&& InData) override`
- L37 _public function_ `virtual void ProcessKeyAttributesChange(FKeyAttributeChangeData_PerCurve&& InData) override`
- L42 _public function_ `virtual void ProcessCurveAttributesChange(FCurveAttributeChangeData_PerCurve&& InData) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Modification/Keys/Diff/MultiGenericCommandAppender.h` (Private)


#### class `UE::CurveEditor::FMultiGenericCommandAppender`  
`class FMultiGenericCommandAppender : public IMultiCurveChangeVisitor`  
_L21-48_
- inherits: `IMultiCurveChangeVisitor`
- desc: Handles appending FGenericCurveChangeCommands to the transaction system. - StoreUndo is called for each FCurveModel that returns non-null from FCurveModel::GetOwningObject. These objects will have their package's dirty flag stored to the undo buffer. - One catch all FGenericCurveChangeCommand is created for all other FCurveModels that returned null from FCurveModel::GetOwningObject.
- L25 _public function_ `explicit FMultiGenericCommandAppender(TSharedPtr<FCurveEditor> InCurveEditor) : CurveEditor(MoveTemp(InCurveEditor))`
- L29 _public function_ `SIZE_T GetAllocationSize() const`
- L32 _public prototype_ `virtual void ProcessChange(const FCurveModelID& InCurveModel, TFunctionRef<void(ISingleCurveChangeVisitor&)> InProcessCallback) override;`
- L33 _public prototype_ `virtual void PostProcessChanges() override;`
- L39 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;` — The curve editor to which we append the change commands.
- L42 _private member_ `FGenericCurveChangeData ChangesToCurvesWithoutUObject;` — Holds the changes made to FCurveModel's that returned no UObject from FCurveModel::GetOwningObject.
- L45 _private member_ `SIZE_T AllocationSize = 0;` — How much memory was allocated by all undo changes.
- L47 _private prototype_ `void ProcessDiff(const FCurveModelID& InCurveId, FGenericCurveChangeData&& InData);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Modification/Keys/GenericCurveChangeCommand.h` (Private)


#### class `UE::CurveEditor::FGenericCurveChangeCommand`  
`class FGenericCurveChangeCommand : public FCurveEditorCommandChange`  
_L18-39_
- inherits: `FCurveEditorCommandChange`
- desc: Captures any changes to keys including and limited to: - Move keys, - Add new keys, - Remove keys, - Change key attributes, - Change curve attributes
- L22 _public function_ `explicit FGenericCurveChangeCommand(TSharedPtr<FCurveEditor> InCurveEditor, FGenericCurveChangeData InDeltaChange) : FCurveEditorCommandChange(MoveTemp(InCurveEditor))`
- L25 _public function_ `, DeltaChange([InDeltaChange = MoveTemp(InDeltaChange)]() mutable { InDeltaChange.Shrink(); return InDeltaChange; }())` — Make sure to Shrink() whatever is passed to us so it takes up as little memory as possible.
- L29 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L30 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L31 _public prototype_ `virtual SIZE_T GetSize() const override;`
- L32 _public prototype_ `virtual FString ToString() const override;`
- L38 _private member_ `const FGenericCurveChangeData DeltaChange;` — The change made to the selection.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Modification/Keys/KeyAttributeChangeUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace CurveEditor` (scope `UE`)
- L19 _namespace_ `namespace KeyAttributes` (scope `UE::CurveEditor`)
- L28 _prototype_ `FKeyAttributeChangeData_PerCurve Diff( const TConstArrayView<FKeyHandle> InKeysBeforeChange, const TConstArrayView<FKeyAttributes> InOriginal, const TConstArrayView<FKeyAttributes> InTarget );` (scope `UE::CurveEditor::KeyAttributes`) — Computes the delta change to get from InOriginal to InTarget. @param InKeysBeforeChange The keys for which to check whether they have changed. @param InOriginal The original positions of the keys. @param InTarget The new positions of the keys.
- L35 _prototype_ `void ApplyChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FKeyAttributeChangeData& InDeltaChange);` (scope `UE::CurveEditor::KeyAttributes`) — Applies InDeltaChange to InCurves (redo).
- L37 _prototype_ `void RevertChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FKeyAttributeChangeData& InDeltaChange);` (scope `UE::CurveEditor::KeyAttributes`) — Reverts InDeltaChange from InCurves (undo).

### `Source/Editor/CurveEditor/Private/Modification/Keys/KeyExistenceUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditor` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CurveEditor` (scope `UE`)
- L20 _prototype_ `void AddKeys(FCurveModel& InCurveModel, const FCurveKeyData& InKeyChange);` (scope `UE::CurveEditor`) — Adds the keys saved in InKeyChange to InCurveModel.
- L22 _prototype_ `void RemoveKeys(FCurveModel& InCurveModel, const FCurveKeyData& InKeyChange, const double InCurrentSliderTime = 0);` (scope `UE::CurveEditor`) — Removes the keys saved in InKeyChange from InCurveModel.
- L24 _namespace_ `namespace KeyInsertion` (scope `UE::CurveEditor`)
- L29 _prototype_ `FCurveKeyData Diff(TConstArrayView<FKeyHandle> InOriginalKeys, const FCurveModel& InCurveModel);` (scope `UE::CurveEditor::KeyInsertion`) — Returns the keys that are new - comparing InOriginalKeys to the current state of InCurveModel. @return The keys that have been added to InCurveModel.
- L32 _prototype_ `void ApplyChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FAddKeysChangeData& InDeltaChange);` (scope `UE::CurveEditor::KeyInsertion`) — Adds the keys in InDeltaChange to the curves.
- L34 _prototype_ `void RevertChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FAddKeysChangeData& InDeltaChange, const double InCurrentSliderTime = 0 );` (scope `UE::CurveEditor::KeyInsertion`) — Removes the keys in InDeltaChange from the curves.
- L39 _namespace_ `namespace KeyRemoval` (scope `UE::CurveEditor`)
- L45 _prototype_ `FCurveKeyData Diff( TConstArrayView<FKeyHandle> InOriginalKeys, TConstArrayView<FKeyPosition> InOriginalPositions, TConstArrayView<FKeyAttributes> InOriginalAttrs, const FCurveModel& InCurveModel );` (scope `UE::CurveEditor::KeyRemoval`) — Returns the keys that have been removed - comparing InOriginalKeys to the current state of InCurveModel. @return The keys that have been removed from InCurveModel
- L51 _prototype_ `TArray<FKeyHandle> Diff(TConstArrayView<FKeyHandle> InOriginalKeys, const FCurveModel& InCurveModel);` (scope `UE::CurveEditor::KeyRemoval`) — @return The keys that have been removed from InCurveModel.
- L54 _prototype_ `void ApplyChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FRemoveKeysChangeData& InDeltaChange, const double InCurrentSliderTime = 0 );` (scope `UE::CurveEditor::KeyRemoval`) — Removes the keys in InDeltaChange from the curves.
- L58 _prototype_ `void RevertChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FRemoveKeysChangeData& InDeltaChange);` (scope `UE::CurveEditor::KeyRemoval`) — Adds the keys in InDeltaChange to the curves.

### `Source/Editor/CurveEditor/Private/Modification/Keys/MoveKeysChangeUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace CurveEditor` (scope `UE`)
- L18 _namespace_ `namespace MoveKeys` (scope `UE::CurveEditor`)
- L27 _prototype_ `FMoveKeysChangeData_PerCurve Diff( const TConstArrayView<FKeyHandle> InKeysBeforeChange, const TConstArrayView<FKeyPosition> InOriginal, const TConstArrayView<FKeyPosition> InTarget );` (scope `UE::CurveEditor::MoveKeys`) — Computes the delta change to get from InOriginal to InTarget. @param InKeysBeforeChange The keys for which to check whether they have moved. @param InOriginal The original positions of the keys. @param InTarget The new positions of the keys.
- L34 _prototype_ `void ApplyChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FMoveKeysChangeData& InDeltaChange);` (scope `UE::CurveEditor::MoveKeys`) — Applies InDeltaChange to InCurves (redo).
- L37 _prototype_ `void RevertChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FMoveKeysChangeData& InDeltaChange);` (scope `UE::CurveEditor::MoveKeys`) — Reverts InDeltaChange from InCurves (undo).

### `Source/Editor/CurveEditor/Private/Modification/Resolution/CurveModelIdCache.h` (Private)


#### struct `UE::CurveEditor::FCurveModelIdCache`  
`struct FCurveModelIdCache`  
_L35-50_
- desc: Keeps track of curve metadata so FCurveModelID are reused when conceptually the same FCurveModels are re-added to FCurveEditor. This is relevant for command-based undo / redo to work correctly. ====== Background ====== Consider the following scenario 1. User clicks a curve to view it. AddCurve is called: a curve representing X may be added with ID=42, 2. User does an undo-able action. FGenericCurveChangeCommand saves change data mapped to ID=42. 3. User clicks another curve. RemoveCurve is called: the curve with ID=42 is removed. 4. User clicks the X curve again to view it again. AddCurve is called again: the curve representing X is adde back to FCurveEditor. In order for FGenericCurveChangeCommand to continue working, in step 4, the curve must be added back using the same FCurveModelID. Systems can be explicit by calling FCurveModel::InitCurveId before calling FCurveEditor::AddCurve. However, there are 2 issues with this approach: 1. that is cumbersome to work with, 2. command-based undo was added later so many older editor systems currently do not bother to re-use FCurveModelIDs. ===== Class purpose ====== So CurveEditor provides a "service" to such systems: provided that the FCurveModel they re-add has the same metadata (owner object, short name, etc.), CurveEditor will automatically attempt to re-use the ID that the re-added curve had when it was last added. That covers a lot of use cases. Systems for which this logic is not enough should just call FCurveModel::InitCurveI
- L41 _public member_ `TMap<TObjectKey<UObject>, TArray<FCurveModelID>> OwnerToCurvesCache;` — Maps UObjects to the FCurveModels they own or used to own. Since most FCurveModel have an owning UObject, we can speed up search using this map.
- L49 _public member_ `TArray<FCurveData> CurveMetaData;` — Holds all curve data ever added to FCurveEditor. Never removed from. Sorted by FCurveModelID to allow for binary search.

#### struct `UE::CurveEditor::FCurveModelIdCache::FCurveData`  
`struct FCurveData`  
_L43-47_
- L45 _public member_ `FCurveModelID CurveId;`
- L46 _public member_ `FCurveMetaDataIdentifiers MetaData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L64 _prototype_ `FCurveModelID InitCurveModelIdWithReusedOrNewId( FCurveModelIdCache& InCache, FCurveModel& InCurveModel, const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InExistingCurves );` (scope `UE::CurveEditor`) — Called by FCurveEditor::AddCurve to init the FCurveModelID for the new curve. Tries to reuse an old FCurveModelID if matches the metadata of an old curve. Priority order: - Use InCurveModel's FCurveModel::CurveId, if set. - Search whether InCurveModel's metadata matches that of CurveMetaData in FCurveEditor in the past, then use the cached FCurveModelID. - Generate a new ID and cache. @param InCache Cache holding the metadata @param InCurveModel The curve about to be added @param InExistingCurves Curves that already exist. Used to handle clashing metadata (i.e. when InCurveModel's metadata already is in use)
- L73 _prototype_ `const FCurveMetaDataIdentifiers* FindMetaData(const FCurveModelIdCache& InCache, const FCurveModelID& InCurveId);` (scope `UE::CurveEditor`) — Performs binary search to metadata associated with InCurveId. @return Metadata associated with InCurveId

### `Source/Editor/CurveEditor/Private/Modification/Resolution/ResolveCurveModelPasskey.h` (Private)


#### class `UE::CurveEditor::FResolveCurveModelPasskey`  
`class FResolveCurveModelPasskey`  
_L13-23_
- desc: Implements passkey pattern to restrict access to FCurveEditor::ResolveCurveModel.
- L19 _private function_ `static TUniquePtr<FCurveModel> ResolveCurveModel(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CurveEditor` (scope `UE`)
- L10 _prototype_ `TUniquePtr<FCurveModel> ResolveCurveModel(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId);` (scope `UE::CurveEditor`) — Tries to re-create a FCurveModel that was in this FCurveEditor previously but has since been removed.
- L25 _function_ `inline TUniquePtr<FCurveModel> ResolveCurveModel(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId)` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Private/Modification/Resolution/ResolveCurveModelUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Modification/Selection/SelectionChangeCommand.h` (Private)


#### class `UE::CurveEditor::FSelectionChangeCommand`  
`class FSelectionChangeCommand : public FCurveEditorCommandChange`  
_L11-31_
- inherits: `FCurveEditorCommandChange`
- desc: Changes that changes the curve editor's selection.
- L15 _public function_ `explicit FSelectionChangeCommand(TSharedPtr<FCurveEditor> InCurveEditor, FSelectionDeltaChange InDeltaChange) : FCurveEditorCommandChange(MoveTemp(InCurveEditor)) , DeltaChange([InDeltaChange = MoveTemp(InDeltaChange)]() mutable { InDeltaChange.Shrink(); return InDeltaChange; }())`
- L17 _public function_ `, DeltaChange([InDeltaChange = MoveTemp(InDeltaChange)]() mutable { InDeltaChange.Shrink(); return InDeltaChange; }())`
- L21 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L22 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L23 _public prototype_ `virtual SIZE_T GetSize() const override;`
- L24 _public prototype_ `virtual FString ToString() const override;`
- L30 _private member_ `const FSelectionDeltaChange DeltaChange;` — The change made to the selection.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Modification/Selection/SelectionChangeUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)
- L17 _prototype_ `FSelectionDeltaChange DiffSelection(const FCurveEditorSelection& InOriginal, const FCurveEditorSelection& InTarget);` (scope `UE::CurveEditor`) — Computes the delta change to get from InOriginal to InTarget.
- L20 _prototype_ `void ApplySelectionChange(FCurveEditorSelection& InOutChange, const FSelectionDeltaChange& InDeltaChange);` (scope `UE::CurveEditor`) — Applies InDeltaChange to InOutSelection (redo operation).
- L22 _prototype_ `void RevertSelectionChange(FCurveEditorSelection& InOutChange, const FSelectionDeltaChange& InDeltaChange);` (scope `UE::CurveEditor`) — Reverts InDeltaChange from InOutSelection (undo operation).
- L25 _namespace_ `namespace SelectionDiffDetail` (scope `UE::CurveEditor`)
- L25 _prototype_ `namespace SelectionDiffDetail` (scope `UE::CurveEditor::SelectionDiffDetail`) — Private - needed for FAddInternal.
- L26 _namespace_ `namespace SelectionDiffDetail` (scope `UE::CurveEditor`)
- L26 _prototype_ `namespace SelectionDiffDetail` (scope `UE::CurveEditor::SelectionDiffDetail`)

### `Source/Editor/CurveEditor/Private/Modification/Selection/SelectionDeltaChange.h` (Private)


#### struct `UE::CurveEditor::FCurveSelectionDeltaChange`  
`struct FCurveSelectionDeltaChange`  
_L14-37_
- desc: Changes made to a single curve's selection
- L19 _public member_ `TArray<TPair<FKeyHandle, ECurvePointType>> AddedKeys;` — The keys that were added and its point type.
- L24 _public member_ `TArray<TPair<FKeyHandle, ECurvePointType>> RemovedKeys;` — The keys that were removed. Can contain a key handle that is in AddedKeys. In that case, the point type was changed.
- L26 _public function_ `SIZE_T GetAllocatedSize() const`
- L32 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### struct `UE::CurveEditor::FSelectionDeltaChange`  
`struct FSelectionDeltaChange`  
_L40-71_
- desc: Changes made to the curve editor selection
- L43 _public member_ `TMap<FCurveModelID, FCurveSelectionDeltaChange> ChangedCurves;` — The per curve changes.
- L46 _public member_ `uint32 OldSerialNumber = 0;` — Serial number of selection before the change.
- L48 _public member_ `uint32 NewSerialNumber = 0;` — Serial number of selection after the change.
- L50 _public function_ `bool HasChanges() const`
- L51 _public function_ `operator bool() const`
- L53 _public function_ `SIZE_T GetAllocatedSize() const`
- L63 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L57 _function_ `` (scope `UE::CurveEditor::FSelectionDeltaChange::GetAllocatedSize`)

### `Source/Editor/CurveEditor/Private/Modification/Utils/ModifyCurveObjectDetector.h` (Private)


#### enum `UE::CurveEditor::EModifyDetectionLevel`  
`enum EModifyDetectionLevel : uint8`  
_L15-15_
- L15 _public enumerator_ `enum EModifyDetectionLevel : uint8 { None, Warn, Ensure, EnsureAlways }; /** * Logs warnings`
- L15 _public enumerator_ `enum EModifyDetectionLevel : uint8 { None, Warn, Ensure, EnsureAlways }; /** * Logs warnings`
- L15 _public enumerator_ `enum EModifyDetectionLevel : uint8 { None, Warn, Ensure, EnsureAlways }; /** * Logs warnings`
- L15 _public enumerator_ `enum EModifyDetectionLevel : uint8 { None, Warn, Ensure, EnsureAlways }; /** * Logs warnings`

#### class `UE::CurveEditor::FModifyCurveObjectDetector`  
`class FModifyCurveObjectDetector : public FNoncopyable`  
_L21-50_
- inherits: `FNoncopyable`
- desc: Logs warnings, ensures, etc. if any FCurveModel::GetOwningObject() is modified. @see FScopedCurveChange.
- L25 _public prototype_ `explicit FModifyCurveObjectDetector( TWeakPtr<FCurveEditor> InCurveEditor, EModifyDetectionLevel InLevel, FString InWarningMessage, TArray<FCurveModelID> InTrackedCurves );`
- L29 _public prototype_ `explicit FModifyCurveObjectDetector( TWeakPtr<FCurveEditor> InCurveEditor, EModifyDetectionLevel InLevel, FString InWarningMessage, const FCurvesSnapshot& InSnapshot );`
- L34 _public prototype_ `~FModifyCurveObjectDetector();`
- L39 _private member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — Used to get the owning objects for the curves.
- L42 _private member_ `const TArray<FCurveModelID> TrackedCurves;` — The curves that should not be modified.
- L45 _private member_ `const EModifyDetectionLevel DetectionLevel;` — Determines the action to take when modification is detected.
- L47 _private member_ `const FString WarningMessage;` — Message to log in the warning
- L49 _private prototype_ `void OnObjectModified(UObject* Object) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/RichCurveKeyProxy.h` (Private)


#### class `URichCurveKeyProxy`  
`class URichCurveKeyProxy : public UObject, public ICurveEditorKeyProxy`  
_L16-113_
- reflection: `UCLASS()`
- inherits: `UObject,ICurveEditorKeyProxy`
- L24 _public function_ `void Initialize(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, FKeyHandle InKeyHandle, TWeakObjectPtr<UObject> InWeakOwner)` — Initialize this key proxy object by caching the underlying key object, and retrieving the time/value each tick
- L50 _private function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`
- L78 _private function_ `virtual void UpdateValuesFromRawData() override`
- L101 _private member_ `FRichCurveKey Value;` — `UPROPERTY(EditAnywhere, Category="Key", meta=(ShowOnlyInnerProperties))` — User-facing value of the key, applied to the actual key on PostEditChange, and updated every tick
- L106 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Cached curve editor
- L108 _private member_ `FCurveModelID CurveModelID;` — Cached curve model ID for this rich curve's key
- L110 _private member_ `FKeyHandle KeyHandle = FKeyHandle::Invalid();` — Cached key handle that this key proxy relates to
- L112 _private member_ `TWeakObjectPtr<UObject> WeakOwner;` — Cached owner in which the raw curve resides

### `Source/Editor/CurveEditor/Private/SCurveEditorViewContainer.h` (Private)


#### class `SCurveEditorViewContainer`  
`class SCurveEditorViewContainer : public SVerticalBox`  
_L38-135_
- inherits: `SVerticalBox`
- desc: Curve editor widget that reflects the state of an FCurveEditor
- L40 _private function_ `SLATE_BEGIN_ARGS(SCurveEditorViewContainer) : _MinimumPanelHeight(300.0f)`
- L45 _private prototype_ `SLATE_ARGUMENT(TSharedPtr<ITimeSliderController>, ExternalTimeSliderController) SLATE_ARGUMENT(float, MinimumPanelHeight) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor);` — Optional Time Slider Controller which allows us to synchronize with an externally controlled Time Slider
- L56 _private function_ `TArrayView<const TSharedPtr<SCurveEditorView>> GetViews() const`
- L58 _private prototype_ `void AddView(TSharedRef<SCurveEditorView> ViewToAdd);`
- L60 _private prototype_ `void Clear();`
- L63 _private function_ `UE::CurveEditor::FOnCurveHasChangedExternally& OnCurveHasChangedExternally()` — Invoked when any of the views has invoked FCurveModel::HasChangedAndResetTest, and it returned true.
- L68 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget Interface
- L69 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L70 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const;`
- L71 _private prototype_ `virtual bool ComputeVolatility() const override;`
- L75 _private prototype_ `virtual FReply OnPreviewMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — ~ Mouse interaction
- L76 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L77 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L78 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L79 _private prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L80 _private prototype_ `virtual void OnFinishedPointerInput() override;`
- L81 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L82 _private prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L83 _private prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L84 _private prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L86 _private function_ `virtual bool SupportsKeyboardFocus() const override`
- L87 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L88 _private prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L92 _private prototype_ `FMargin GetSlotPadding(int32 SlotIndex) const;`
- L94 _private prototype_ `void OnCurveEditorToolChanged(FCurveEditorToolID InToolId);`
- L96 _private prototype_ `void ExpandInputBounds(float NewWidth);`
- L98 _private prototype_ `bool IsScrubTimeKeyEvent(const FKeyEvent& InKeyEvent);`
- L100 _private prototype_ `void BroadcastOnCurveHasChangedExternally(const FCurveModelID& InCurveModelId) const;`
- L105 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;` — The curve editor pointer
- L108 _private member_ `TSharedPtr<ITimeSliderController> TimeSliderController;` — Optional time slider controller
- L111 _private member_ `TOptional<FCurveEditorDelayedDrag> DragOperation;` — (Optional) the current drag operation
- L113 _private member_ `bool bHadMouseMovesThisTick = false;` — Whether DragOperation needs to have OnFinishedPointerInput called this tick.
- L116 _private member_ `TArray<TSharedPtr<SCurveEditorView>> Views;` — Array of views whose cache may need to be updated and may need their height updating on tick.
- L119 _private member_ `TSharedPtr<SRetainerWidget> RetainerWidget;` — Possible pointer to a retainer widget that we may need to force update
- L122 _private member_ `UE::CurveEditor::FOnCurveHasChangedExternally OnCurveHasChangedExternallyDelegate;` — Invoked when any of the views has invoked FCurveModel::HasChangedAndResetTest, and it returned true.
- L128 _private member_ `bool bCaughtMouseDown;` — Whether or not this widget caught an OnMouseDown notification Used to check if the selection should be cleared
- L131 _private member_ `float MinimumPanelHeight;` — The minimum height for this container panel.
- L134 _private member_ `bool bIsScrubbingTime = false;` — Whether or not we are scrubbing time

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Private/Selection/SelectionCleanser.h` (Private)


#### class `UE::CurveEditor::FSelectionCleanser`  
`class FSelectionCleanser : public FNoncopyable , public FEditorUndoClient`  
_L24-45_
- inherits: `FNoncopyable,FEditorUndoClient`
- desc: Makes sure that the FCurveEditor::Selection does not contain any stale keys, i.e. to prevent that the selection contains FKeyHandles and FCurveModelIds that do not exist in the FCurveEditor. Stale keys presents issues with context menus and other things that are activated when there is a selection set. Cleansing happens when: - An undo / redo operation is performed (regardless whether it directly affects FCurveEditor - the data underlying the FCurveModel may change) - An undoable action is recorded to FTransactionManager. Effectively, this means that if you use FScopedCurveChange to make changes to curves, this manager will handle cleansing selection.
- L30 _public prototype_ `explicit FSelectionCleanser(const TSharedRef<FCurveEditor>& InCurveEditor);`
- L31 _public prototype_ `~FSelectionCleanser();`
- L34 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L35 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L41 _private member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — Instance that owns us. Used to check which curves are currently present.
- L44 _private prototype_ `void OnCurvesChanged(const FGenericCurveChangeData& InChange) const;` — Invoked when a (transactional) change happens to curves.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Private/Selection/SelectionUtils.h` (Private)


#### enum `UE::CurveEditor::ECleanseResult`  
`enum class ECleanseResult : uint8`  
_L16-16_
- L16 _public enumerator_ `enum class ECleanseResult : uint8 { NoStaleKeys, HadStaleKeys }; ECleanseResult CleanseSelection(const TSharedRef<FCurveEditor>& InCurveEditor, FCurveEditorSelection& InSelection); ECleanseResult CleanseSelection(const TSharedRef<FCurveEditor>& InCurveEditor, FCurveEditorSelection& InSelection, TConstArrayView<FCurveModelID> InOnlyTheseCurves`
- L16 _public enumerator_ `enum class ECleanseResult : uint8 { NoStaleKeys, HadStaleKeys }; ECleanseResult CleanseSelection(const TSharedRef<FCurveEditor>& InCurveEditor, FCurveEditorSelection& InSelection); ECleanseResult CleanseSelection(const TSharedRef<FCurveEditor>& InCurveEditor, FCurveEditorSelection& InSelection, TConstArrayView<FCurveModelID> InOnlyTheseCurves`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditor` (scope `UE`)
- L19 _prototype_ `ECleanseResult CleanseSelection(const TSharedRef<FCurveEditor>& InCurveEditor, FCurveEditorSelection& InSelection);` (scope `UE::CurveEditor`) — Removes all curve models and keys from InSelection that do not exist in InCurveEditor.
- L22 _prototype_ `ECleanseResult CleanseSelection(const TSharedRef<FCurveEditor>& InCurveEditor, FCurveEditorSelection& InSelection, TConstArrayView<FCurveModelID> InOnlyTheseCurves );` (scope `UE::CurveEditor`) — Overload that will only remove 1. those FKeyHandles belonging to curves in InOnlyTheseCurves, 2. the curves in InOnlyTheseCurves.
- L27 _prototype_ `TMap<FCurveModelID, FKeyHandleSet> ResolveSelectedOrRelativeKeys(const FCurveEditor& InCurveEditor);` (scope `UE::CurveEditor`) — Returns the explicit key selection, or keys after the current scrub time if nothing is selected.

### `Source/Editor/CurveEditor/Public/CurveDataAbstraction.h` (Public)


#### struct `FKeyPosition`  
`struct FKeyPosition`  
_L17-46_
- reflection: `USTRUCT()`
- desc: Generic key position information for a key on a curve
- L21 _public function_ `FKeyPosition() : InputValue(0.0), OutputValue(0.0)`
- L25 _public function_ `FKeyPosition(double Input, double Output) : InputValue(Input), OutputValue(Output)`
- L29 _public function_ `FKeyPosition Transform(const FTransform2d& InTransform) const`
- L38 _public member_ `double InputValue;` — `UPROPERTY()` — The key's input (x-axis) position (i.e. it's time)
- L42 _public member_ `double OutputValue;` — `UPROPERTY()` — The key's output (t-axis) position (i.e. it's value)
- L44 _public prototype_ `bool operator==(const FKeyPosition& Other) const = default;`
- L45 _public prototype_ `bool operator!=(const FKeyPosition& Other) const = default;`

#### struct `FKeyAttributes`  
`struct FKeyAttributes`  
_L52-210_
- reflection: `USTRUCT()`
- desc: Extended attributes that the curve editor understands
- L56 _public function_ `FKeyAttributes()`
- L77 _public function_ `bool HasArriveTangent() const` — Check whether this key has the specified attributes
- L78 _public function_ `bool HasLeaveTangent() const`
- L79 _public function_ `bool HasInterpMode() const`
- L80 _public function_ `bool HasTangentMode() const`
- L81 _public function_ `bool HasTangentWeightMode() const`
- L82 _public function_ `bool HasArriveTangentWeight() const`
- L83 _public function_ `bool HasLeaveTangentWeight() const`
- L88 _public function_ `float GetArriveTangent() const` — Retrieve specific attributes for this key. Must check such attributes exist.
- L89 _public function_ `float GetLeaveTangent() const`
- L90 _public function_ `ERichCurveInterpMode GetInterpMode() const`
- L91 _public function_ `ERichCurveTangentMode GetTangentMode() const`
- L92 _public function_ `ERichCurveTangentWeightMode GetTangentWeightMode()const`
- L93 _public function_ `float GetArriveTangentWeight() const`
- L94 _public function_ `float GetLeaveTangentWeight() const`
- L99 _public function_ `FKeyAttributes& SetArriveTangent(float InArriveTangent)` — Set the attributes for this key
- L100 _public function_ `FKeyAttributes& SetLeaveTangent(float InLeaveTangent)`
- L101 _public function_ `FKeyAttributes& SetInterpMode(ERichCurveInterpMode InInterpMode)`
- L102 _public function_ `FKeyAttributes& SetTangentMode(ERichCurveTangentMode InTangentMode)`
- L103 _public function_ `FKeyAttributes& SetTangentWeightMode(ERichCurveTangentWeightMode InTangentWeightMode)`
- L104 _public function_ `FKeyAttributes& SetArriveTangentWeight(float InArriveTangentWeight)`
- L105 _public function_ `FKeyAttributes& SetLeaveTangentWeight(float InLeaveTangentWeight)`
- L110 _public function_ `void UnsetArriveTangent()` — Reset specific attributes of this key, implying such attributes are not supported
- L111 _public function_ `void UnsetLeaveTangent()`
- L112 _public function_ `void UnsetInterpMode()`
- L113 _public function_ `void UnsetTangentMode()`
- L114 _public function_ `void UnsetTangentWeightMode()`
- L115 _public function_ `void UnsetArriveTangentWeight()`
- L116 _public function_ `void UnsetLeaveTangentWeight()`
- L121 _public function_ `static FKeyAttributes MaskCommon(const FKeyAttributes& A, const FKeyAttributes& B)` — Generate a new set of attributes that contains only those attributes common to both A and B
- L161 _public prototype_ `bool operator==(const FKeyAttributes& Other) const = default;`
- L162 _public prototype_ `bool operator!=(const FKeyAttributes& Other) const = default;`
- L168 _private member_ `uint8 bHasArriveTangent : 1;` — `UPROPERTY()` — True if this key supports entry tangents
- L171 _private member_ `uint8 bHasLeaveTangent : 1;` — `UPROPERTY()` — True if this key supports exit tangents
- L174 _private member_ `uint8 bHasInterpMode : 1;` — `UPROPERTY()` — True if this key supports interpolation modes
- L177 _private member_ `uint8 bHasTangentMode : 1;` — `UPROPERTY()` — True if this key supports tangent modes
- L180 _private member_ `uint8 bHasTangentWeightMode : 1;` — `UPROPERTY()` — True if this key supports tangent modes
- L183 _private member_ `uint8 bHasArriveTangentWeight : 1;` — `UPROPERTY()` — True if this key supports entry tangents weights
- L186 _private member_ `uint8 bHasLeaveTangentWeight : 1;` — `UPROPERTY()` — True if this key supports exit tangents weights
- L190 _private member_ `float ArriveTangent{};` — `UPROPERTY()` — This key's entry tangent, if bHasArriveTangent
- L193 _private member_ `float LeaveTangent{};` — `UPROPERTY()` — This key's exit tangent, if bHasLeaveTangent
- L196 _private member_ `TEnumAsByte<ERichCurveInterpMode> InterpMode;` — `UPROPERTY()` — This key's interpolation mode, if bHasInterpMode
- L199 _private member_ `TEnumAsByte<ERichCurveTangentMode> TangentMode;` — `UPROPERTY()` — This key's tangent mode, if bHasTangentMode
- L202 _private member_ `TEnumAsByte<ERichCurveTangentWeightMode> TangentWeightMode;` — `UPROPERTY()` — This key's tangent weight mode, if bHasTangentWeightMode
- L205 _private member_ `float ArriveTangentWeight{};` — `UPROPERTY()` — This key's entry tangent weight, if bHasArriveTangentWeight
- L208 _private member_ `float LeaveTangentWeight{};` — `UPROPERTY()` — This key's exit tangent weight, if bHasLeaveTangentWeight

### `Source/Editor/CurveEditor/Public/CurveDrawInfo.h` (Public)


#### struct `FKeyDrawInfo`  
`struct FKeyDrawInfo`  
_L17-32_
- desc: Structure that defines how to draw a particular key
- L19 _public function_ `FKeyDrawInfo() : ScreenSize(0.f, 0.f) , Brush(nullptr)`
- L25 _public member_ `FVector2D ScreenSize;` — The size of the key on screen in slate units
- L28 _public member_ `const FSlateBrush* Brush;` — The brush to use to draw the key
- L31 _public member_ `TOptional<FLinearColor> Tint;` — A tint to apply to the brush

#### struct `FCurvePointInfo`  
`struct FCurvePointInfo`  
_L39-63_
- desc: Structure that defines the necessary data for painting a given curve point
- L41 _public function_ `FCurvePointInfo(FKeyHandle InHandle) : KeyHandle(InHandle) , ScreenPosition(0.f, 0.f) , LineDelta(0.f, 0.f) , Type(ECurvePointType::Key) , LayerBias(0)`
- L50 _public member_ `FKeyHandle KeyHandle;` — This point's key handle
- L52 _public member_ `FVector2D ScreenPosition;` — The position of the point on screen
- L54 _public member_ `FVector2D LineDelta;` — A screen space delta position that defines where to draw a line connected to this point. No line is drawn if zero.
- L56 _public member_ `ECurvePointType Type;` — The type of the point
- L58 _public member_ `int32 LayerBias;` — A layer bias to draw the point with (higher integers draw on top)
- L60 _public member_ `FKeyDrawInfo DrawInfo;` — DrawInfo to use when rendering this point. Allows customization of points on a per-point basis instead of per-curve.
- L62 _public member_ `bool bDraw = true;` — If false, the key will not be painted.

#### struct `FCurveDrawParams`  
`struct FCurveDrawParams`  
_L69-136_
- desc: Structure that defines the necessary data for painting a whole curve
- L72 _public member_ `FLinearColor Color;` — The color to draw this curve
- L75 _public member_ `TArray<FVector2D> InterpolatingPoints;` — An array of screen-space points that define this curve's shape. Rendered as a continuous line.
- L78 _public member_ `TArray<FCurvePointInfo> Points;` — An array of distinct curve points for the visible range.
- L81 _public member_ `FKeyDrawInfo ArriveTangentDrawInfo;` — Value defining how to draw keys of type ECurvePointType::ArriveTangent.
- L84 _public member_ `FKeyDrawInfo LeaveTangentDrawInfo;` — Value defining how to draw keys of type ECurvePointType::LeaveTangent.
- L87 _public member_ `float Thickness = 2.f;` — Thickness of this curve
- L90 _public member_ `float DashLengthPx = 0.f;` — The color to draw this curve
- L93 _public member_ `uint8 bKeyDrawEnabled : 1;` — Whether or not to draw keys on the curve.
- L96 _public member_ `uint8 bDrawInterpolatingPoints : 1 = true;` — If false, the interpolating points will not be painted.
- L101 _public function_ `FCurveDrawParams(FCurveModelID InID) : Color(0.2f, 0.2f, 0.2f) , bKeyDrawEnabled(1) , ID(InID)` — Construct new draw parameters for the specified curve ID
- L110 _public function_ `FCurveModelID GetID() const` — Get the curve ID that these draw parameters relate to
- L118 _public function_ `const FKeyDrawInfo& GetKeyDrawInfo(ECurvePointType Type, const int32 InPointIndex) const` — Retrieve the draw information for drawing the specified type of curve point
- L132 _private member_ `FCurveModelID ID;` — Immutable curve ID
- L135 _private member_ `FKeyDrawInfo InvalidDrawInfo;` — Immutable dummy key draw info to return

### `Source/Editor/CurveEditor/Public/CurveEditor.h` (Public)


#### enum `ECurveEditorTangentTypes`  
`enum class ECurveEditorTangentTypes : int32`  
_L70-81_
- desc: Enums to describe supported tangent types, by default support all but smart auto
- L72 _public enumerator_ `InterpolationConstant = 0x1`
- L73 _public enumerator_ `InterpolationLinear = 0x2`
- L74 _public enumerator_ `InterpolationCubicAuto = 0x4`
- L76 _public enumerator_ `InterpolationCubicUser = 0x8`
- L77 _public enumerator_ `InterpolationCubicBreak = 0x10`
- L78 _public enumerator_ `InterpolationCubicWeighted = 0x20`
- L79 _public enumerator_ `InterpolationCubicSmartAuto = 0x40`

#### class `FCurveEditor`  
`class FCurveEditor : public FEditorUndoClient , public TSharedFromThis<FCurveEditor>`  
_L83-829_
- inherits: `FEditorUndoClient,TSharedFromThis<FCurveEditor>`
- L92 _public member_ `FCurveEditorSelection Selection;` — Container holding the current key/tangent selection
- L97 _public member_ `TAttribute<FFrameRate> InputSnapRateAttribute;` — Attribute used to retrieve the current input snap rate (also used for display)
- L100 _public member_ `TAttribute<TOptional<float>> FixedGridSpacingAttribute;` — Attribute used to retrieve the current value-axis grid line state
- L103 _public member_ `TAttribute<bool> InputSnapEnabledAttribute;` — Attribute used to determine if we should snap input values
- L106 _public member_ `TAttribute<bool> OutputSnapEnabledAttribute;` — Attribute used to determine if we should snap output values
- L109 _public member_ `FOnSetBoolean OnInputSnapEnabledChanged;` — Delegate that is invoked when the input snapping has been enabled/disabled
- L112 _public member_ `FOnSetBoolean OnOutputSnapEnabledChanged;` — Delegate that is invoked when the output snapping has been enabled/disabled
- L115 _public member_ `TAttribute<FKeyAttributes> DefaultKeyAttributes;` — Attribute used for determining default attributes to apply to a newly create key
- L118 _public member_ `TAttribute<FText> GridLineLabelFormatXAttribute, GridLineLabelFormatYAttribute;` — Grid line label text format strings for the X and Y axis
- L118 _public member_ `TAttribute<FText> GridLineLabelFormatXAttribute, GridLineLabelFormatYAttribute;` — Grid line label text format strings for the X and Y axis
- L121 _public member_ `TAttribute<double> InputZoomToFitPadding;` — Padding applied to zoom-to-fit the input
- L124 _public member_ `TAttribute<double> OutputZoomToFitPadding;` — Padding applied to zoom-to-fit the output
- L127 _public member_ `FOnActiveToolChanged OnActiveToolChangedDelegate;` — Delegate that is invoked when a tool becomes active. Also fired when the tool goes inactive.
- L130 _public member_ `FOnCurveColorsChanged OnCurveColorsChangedDelegate;` — Delegate that is invoked when the curve colors are changed.
- L137 _public prototype_ `FCurveEditor();` — Constructor
- L142 _public prototype_ `FCurveEditor(const FCurveEditor&) = delete;` — Non-copyable (shared ptr semantics)
- L143 _public prototype_ `FCurveEditor& operator=(const FCurveEditor&) = delete;`
- L145 _public prototype_ `virtual ~FCurveEditor();`
- L147 _public prototype_ `void InitCurveEditor(const FCurveEditorInitParams& InInitParams);`
- L149 _public prototype_ `virtual int32 GetSupportedTangentTypes();`
- L151 _public function_ `UE::CurveEditor::FTransactionManager* GetTransactionManager() const`
- L153 _public function_ `UE::CurveEditor::FCurveModelIdCache* GetCurveMetaDataCache() const` — @return Metadata cache for reusing FCurveModelIDs when re-adding curves. For now, not API exported as it's for internal CurveEditor use only.
- L157 _public prototype_ `void SetPanel(TSharedPtr<SCurveEditorPanel> InPanel);`
- L159 _public prototype_ `TSharedPtr<SCurveEditorPanel> GetPanel() const;`
- L161 _public prototype_ `void SetView(TSharedPtr<SCurveEditorView> InPanel);`
- L163 _public prototype_ `TSharedPtr<SCurveEditorView> GetView() const;`
- L165 _public prototype_ `FCurveEditorScreenSpaceH GetPanelInputSpace() const;`
- L167 _public prototype_ `void ResetMinMaxes();`
- L175 _public prototype_ `void ZoomToFit(EAxisList::Type Axes = EAxisList::All);` — Zoom the curve editor to fit all the selected curves (or all curves if none selected) @param Axes         (Optional) Axes to lock the zoom to
- L181 _public prototype_ `void ZoomToFitAll(EAxisList::Type Axes = EAxisList::All);` — Zoom the curve editor to fit all the currently visible curves @param Axes         (Optional) Axes to lock the zoom to
- L188 _public prototype_ `void ZoomToFitCurves(TArrayView<const FCurveModelID> CurveModelIDs, EAxisList::Type Axes = EAxisList::All);` — Zoom the curve editor to fit the requested curves. @param CurveModelIDs The curve IDs to zoom to fit. @param Axes         (Optional) Axes to lock the zoom to
- L194 _public prototype_ `void ZoomToFitSelection(EAxisList::Type Axes = EAxisList::All);` — Zoom the curve editor to fit all the current key selection. Zooms to fit all if less than 2 keys are selected. @param Axes         (Optional) Axes to lock the zoom to
- L197 _public prototype_ `const FCurveEditorZoomScaleConfig& GetZoomScaleConfig() const;` — @return The config to use for scaling the zooms.
- L202 _public prototype_ `void SetBounds(TUniquePtr<ICurveEditorBounds>&& InBounds);` — Assign a new bounds container to this curve editor
- L206 _public function_ `const ICurveEditorBounds& GetBounds() const` — Retrieve the current curve editor bounds implementation
- L210 _public function_ `ICurveEditorBounds& GetBounds()` — Retrieve the current curve editor bounds implementation
- L214 _public function_ `void SetTimeSliderController(TSharedPtr<ITimeSliderController> InTimeSliderController)` — Sets a Time Slider controller for this Curve Editor to be sync'd against. Can be null.
- L218 _public function_ `TSharedPtr<ITimeSliderController> GetTimeSliderController() const` — Retrieve the optional Time Slider Controller that this Curve Editor may be sync'd with.
- L222 _public function_ `TSharedPtr<FUICommandList> GetCommands() const` — Retrieve this curve editor's command list
- L226 _public prototype_ `bool IsToolActive(const FCurveEditorToolID InToolID) const;` — Returns true of the specified tool is currently active.
- L230 _public prototype_ `void MakeToolActive(const FCurveEditorToolID InToolID);` — Attempts to make the specified tool the active tool. This will cancel the current tool if there is one.
- L235 _public prototype_ `ICurveEditorToolExtension* GetCurrentTool() const;` — Attempts to get the currently active tool. Will return nullptr if there is no active tool. Do not store a reference to this returned pointer, instead only store FCurveEditorToolIDs!
- L237 _public prototype_ `FCurveEditorToolID AddTool(TUniquePtr<ICurveEditorToolExtension>&& InTool);`
- L247 _public prototype_ `void AddAxis(const FName& InIdentifier, TSharedPtr<FCurveEditorAxis> InAxis);` — Adds a new axis to this curve editor with the specified name. @note Calling this function with the same identifier as a previously registered axis will overwrite the axis with the new one. @param InIdentifier      A unique identifer for this axis that can be subsequently used to look up this axis @param InAxis            The axis definition
- L252 _public prototype_ `TSharedPtr<FCurveEditorAxis> FindAxis(const FName& InIdentifier) const;` — Find an axis by its ID
- L257 _public prototype_ `void RemoveAxis(const FName& InIdentifier);` — Remove the axis with the specified ID
- L262 _public prototype_ `void ClearAxes();` — Remove all custom axes definitions
- L265 _public prototype_ `void TranslateSelectedKeys(double SecondsToAdd);` — Nudge left or right
- L266 _public prototype_ `void TranslateSelectedKeysLeft();`
- L267 _public prototype_ `void TranslateSelectedKeysRight();`
- L270 _public prototype_ `void SnapToSelectedKey();` — Snap time to the first selected key
- L274 _public function_ `void SetSelectionRangeStart()` — `UE_DEPRECATED(5.8, "SetSelectionRangeStart is no longer specialized for the Curve Editor")` — Selection range for ie. looping playback
- L276 _public function_ `void SetSelectionRangeEnd()` — `UE_DEPRECATED(5.8, "SetSelectionRangeEnd is no longer specialized for the Curve Editor")`
- L278 _public function_ `void ClearSelectionRange()` — `UE_DEPRECATED(5.8, "ClearSelectionRange is no longer specialized for the Curve Editor")`
- L281 _public prototype_ `void SelectAllKeys();` — Selection
- L282 _public prototype_ `void SelectForward();`
- L283 _public prototype_ `void SelectBackward();`
- L284 _public prototype_ `void SelectNone();`
- L285 _public prototype_ `void InvertSelection();`
- L288 _public prototype_ `void ToggleExpandCollapseNodes(bool bRecursive);` — Toggle the expansion state of the selected nodes or all nodes if none selected
- L291 _public prototype_ `void ExpandAllNodes();` — Expand all nodes in the tree
- L294 _public prototype_ `void CollapseAllNodes();` — Collapse all nodes in the tree
- L297 _public prototype_ `void SortAllNodes();` — Sort all nodes in the tree
- L304 _public prototype_ `FCurveModel* FindCurve(FCurveModelID CurveID) const;` — Find a curve by its ID @return a ptr to the curve if found, nullptr otherwise
- L309 _public prototype_ `FCurveModelID AddCurve(TUniquePtr<FCurveModel>&& InCurve);` — Add a new curve to this editor
- L310 _public prototype_ `FCurveModelID AddCurveForTreeItem(TUniquePtr<FCurveModel>&& InCurve, FCurveEditorTreeItemID TreeItemID);`
- L315 _public prototype_ `void RemoveCurve(FCurveModelID InCurveID);` — Remove a curve from this editor.
- L318 _public prototype_ `void RemoveAllCurves();` — Remove all curves from this editor
- L320 _public prototype_ `bool IsCurvePinned(FCurveModelID InCurveID) const;`
- L322 _public prototype_ `void PinCurve(FCurveModelID InCurveID);`
- L324 _public prototype_ `void UnpinCurve(FCurveModelID InCurveID);`
- L326 _public function_ `const TSet<FCurveModelID>& GetPinnedCurves() const`
- L331 _public prototype_ `const SCurveEditorView* FindFirstInteractiveView(FCurveModelID InCurveID) const;`
- L336 _public function_ `UCurveEditorSettings* GetSettings() const` — Retrieve this curve editor's settings
- L340 _public prototype_ `const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& GetCurves() const;` — Access all the curves currently contained in the Curve Editor regardless of visibility.
- L342 _public function_ `FCurveEditorSelection& GetSelection()`
- L343 _public function_ `const FCurveEditorSelection& GetSelection() const`
- L348 _public prototype_ `FCurveSnapMetrics GetCurveSnapMetrics(FCurveModelID CurveModel) const;` — Generate a utility struct for snapping values
- L353 _public function_ `TOptional<float> GetGridSpacing() const` — Returns the value grid line spacing state
- L358 _public function_ `FCurveEditorAxisSnap GetAxisSnap() const` — Returned the cached struct for snapping editing movement to a specific axis based on user preferences.
- L359 _public function_ `void SetAxisSnap(const FCurveEditorAxisSnap& InAxisSnap)`
- L360 _public function_ `TAttribute<FText> GetGridLineLabelFormatXAttribute() const`
- L361 _public function_ `TAttribute<FText> GetGridLineLabelFormatYAttribute() const`
- L362 _public function_ `TAttribute<FKeyAttributes> GetDefaultKeyAttributes() const`
- L364 _public function_ `void SuppressBoundTransformUpdates(bool bSuppress)`
- L365 _public function_ `bool AreBoundTransformUpdatesSuppressed() const`
- L368 _public prototype_ `TSet<FCurveModelID> GetSelectionFromTreeAndKeys() const;` — Return the curve model IDs that are selected in the tree or have selected keys
- L370 _public prototype_ `TSet<FCurveModelID> GetEditedCurves() const;`
- L372 _public function_ `TAttribute<FKeyAttributes> GetDefaultKeyAttribute() const` — Attribute used for determining default attributes to apply to a newly create key
- L374 _public prototype_ `void AddBufferedCurves(const TSet<FCurveModelID>& InCurves);` — Create a copy of the specified set of curves.
- L376 _public prototype_ `bool ApplyBufferedCurves(const TSet<FCurveModelID>& InCurvesToApplyTo, const bool bSwapBufferCurves);` — Attempts to apply the buffered curve to the passed in curve set. Returns true on success.
- L378 _public function_ `int32 GetNumBufferedCurves() const` — Return the number of stored Buffered Curves.
- L380 _public function_ `const TArray<TUniquePtr<IBufferedCurveModel>>& GetBufferedCurves() const` — Return the array of buffered curves
- L382 _public prototype_ `bool IsActiveBufferedCurve(const TUniquePtr<IBufferedCurveModel>& BufferedCurve) const;` — Returns whether the buffered curve is to be acted on, ie. selected, in the tree view or with selected keys
- L387 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient
- L388 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L391 _public function_ `const TArray<TSharedRef<ICurveEditorExtension>> GetEditorExtensions() const`
- L396 _public function_ `const TMap<FCurveEditorToolID, TUniquePtr<ICurveEditorToolExtension>>& GetToolExtensions() const`
- L406 _public prototype_ `FCurveEditorTreeItem& GetTreeItem(FCurveEditorTreeItemID ItemID);` — Retrieve a tree item from its ID
- L411 _public prototype_ `const FCurveEditorTreeItem& GetTreeItem(FCurveEditorTreeItemID ItemID) const;` — Retrieve a tree item from its ID
- L416 _public prototype_ `FCurveEditorTreeItem* FindTreeItem(FCurveEditorTreeItemID ItemID);` — Finds a tree item from its ID
- L421 _public prototype_ `const FCurveEditorTreeItem* FindTreeItem(FCurveEditorTreeItemID ItemID) const;` — Finds a tree item from its ID
- L426 _public prototype_ `const TArray<FCurveEditorTreeItemID>& GetRootTreeItems() const;` — Get const access to the entire set of root tree items
- L432 _public prototype_ `FCurveEditorTreeItemID GetTreeIDFromCurveID(FCurveModelID CurveID) const;` — Find a tree ID id associated with a CurveModelID
- L437 _public prototype_ `FCurveEditorTreeItem* AddTreeItem(FCurveEditorTreeItemID ParentID);` — Add a new tree item to this curve editor
- L442 _public prototype_ `void RemoveTreeItem(FCurveEditorTreeItemID ItemID);` — Remove a tree item from the curve editor
- L447 _public prototype_ `void RemoveAllTreeItems();` — Remove all tree items from the curve editor
- L452 _public prototype_ `void SetTreeSelection(TArray<FCurveEditorTreeItemID>&& TreeItems);` — Set the tree selection directly
- L457 _public prototype_ `void RemoveFromTreeSelection(TArrayView<const FCurveEditorTreeItemID> TreeItems);` — Removes items from the current tree selection.
- L462 _public prototype_ `ECurveEditorTreeSelectionState GetTreeSelectionState(FCurveEditorTreeItemID TreeItemID) const;` — Check whether this tree item is selected
- L467 _public prototype_ `const TMap<FCurveEditorTreeItemID, ECurveEditorTreeSelectionState>& GetTreeSelection() const;` — Retrieve the current tree selection
- L472 _public function_ `FCurveEditorTree* GetTree()` — Access the curve editor tree.
- L480 _public function_ `const FCurveEditorTree* GetTree() const` — Access the curve editor tree.
- L488 _public function_ `bool IsDoingDirectSelection() const` — Whether or not we are are doign a direct selection, could be used to see why a curve model is being created or destroyed, by direct selection or by sequencer filtering?
- L497 _public function_ `uint32 GetActiveCurvesSerialNumber() const` — Retrieve a serial number that is incremented any time a curve is added or removed
- L507 _public prototype_ `bool ShouldAutoFrame() const;` — Check whether this curve editor can automatically zoom to the current selection
- L513 _public prototype_ `bool IsInputSnappingEnabled() const;` — Check whether keys should be snapped to the input display rate when dragging around
- L514 _public prototype_ `void ToggleInputSnapping();`
- L519 _public prototype_ `bool IsOutputSnappingEnabled() const;` — Check whether keys should be snapped to the output snap interval when dragging around
- L520 _public prototype_ `void ToggleOutputSnapping();`
- L551 _public member_ `FCurveFlipRangeSettings HorizontalCurveFlipRangeSettings;`
- L552 _public member_ `FCurveFlipRangeSettings VerticalCurveFlipRangeSettings;`
- L557 _public prototype_ `void FlipCurve(ECurveFlipDirection Direction);` — Flip the selected curve horizontally or vertically
- L558 _public prototype_ `static void FlipCurveHorizontal(TArray<FKeyPosition>& AllKeyPositions, TArray<FKeyAttributes>& AllKeyAttributes, ECurveFlipRangeType RangeType, float InRangeMin, float InRangeMax, double CurveMinTime, double CurveMaxTime);`
- L560 _public prototype_ `static void FlipCurveVertical(TArray<FKeyPosition>& AllKeyPositions, TArray<FKeyAttributes>& AllKeyAttributes, ECurveFlipRangeType RangeType, float InRangeMin, float InRangeMax, double CurveMinVal, double CurveMaxVal);`
- L568 _public prototype_ `void CutSelection();` — Cut the currently selected keys
- L573 _public prototype_ `void CopySelection() const;` — Copy the currently selected keys
- L578 _public prototype_ `bool CanPaste(const FString& TextToImport) const;` — Returns whether the current clipboard contains objects which CurveEditor can paste
- L581 _protected prototype_ `void ImportCopyBufferFromText(const FString& TextToImport, TArray<UCurveEditorCopyBuffer*>& ImportedCopyBuffers) const;`
- L582 _protected prototype_ `TSet<FCurveModelID> GetTargetCurvesForPaste() const;`
- L585 _protected prototype_ `bool CopyBufferCurveToCurveID(const UCurveEditorCopyableCurveKeys* InSourceCurve, const FCurveModelID InTargetCurve, TOptional<double> InTimeOffset, const bool bInAddToSelection, const bool bInOverwriteRange);` — `UE_DEPRECATED(5.6, "Use the version that takes in ECurveEditorPasteMode and ECurveEditorPasteFlags instead.")`
- L586 _protected prototype_ `bool CopyBufferCurveToCurveID(const UCurveEditorCopyableCurveKeys* InSourceCurve, const FCurveModelID InTargetCurve, TOptional<double> InTimeOffset, UE::CurveEditor::ECurveEditorPasteMode InMode, UE::CurveEditor::ECurveEditorPasteFlags InFlags );`
- L590 _protected prototype_ `void GetChildCurveModelIDs(const FCurveEditorTreeItemID TreeItemID, TSet<FCurveModelID>& CurveModelIDs) const;`
- L595 _public prototype_ `void PasteKeys(TSet<FCurveModelID> CurveModelIDs, const bool bInOverwriteRange = false);` — `UE_DEPRECATED(5.6, "Use the version that takes FKeyPasteArg instead.")` — Paste keys
- L602 _public prototype_ `void PasteKeys(UE::CurveEditor::FKeyPasteArgs InArgs = {});` — Pastes keys. @param CurveModelIds Only the curve model IDs specified in this set. If empty, paste all in the clipboard. @param Flags Flags that modify the operation.
- L607 _public prototype_ `void DeleteSelection();` — Delete the currently selected keys
- L612 _public prototype_ `void ResetSelectedKeysToDefaultValues();` — Reset selected keys to their curve's default value, for curves that support it.
- L617 _public prototype_ `bool CanResetSelectedKeysToDefaultValues() const;` — Returns true if any selected key belongs to a curve that has a default value.
- L622 _public prototype_ `void FlattenSelection();` — Flatten the tangents on the selected keys
- L627 _public prototype_ `void StraightenSelection();` — Straighten the tangents on the selected keys
- L632 _public prototype_ `void MatchLastTangentToFirst(bool bLastToFirst = true);` — Sets the last keys tangents to match the first, if bFirstToLast is false do the opposite
- L637 _public prototype_ `void SetRandomCurveColorsForSelected();` — Set random curve colors
- L642 _public prototype_ `void SetCurveColorsForSelected();` — Pick a curve color and set on selected
- L647 _public prototype_ `bool CanFlattenOrStraightenSelection() const;` — Do we currently have keys to flatten or straighten?
- L650 _public prototype_ `void SmartSnapSelection();` — Snaps the selected keys to their nearest whole frames and positions them on the frame intersection with the frame.
- L652 _public prototype_ `bool CanSmartSnapSelection() const;` — @return Whether there is any key selection.
- L659 _public prototype_ `void UpdateGeometry(const FGeometry& CurrentGeometry);` — Called by SCurveEditorPanel to update the allocated geometry for this curve editor.
- L669 _public function_ `virtual void GetGridLinesX(TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels) const` — Called by SCurveEditorPanel to determine where to draw grid lines along the X-axis. This allows synchronization with an external data source (such as Sequencer's Timeline ticker). A similar function for the Y grid lines is not provided due to the Curve Editor's ability to have multiple views with repeated gridlines and values.
- L677 _public prototype_ `void BindCommands();` — Bind UI commands that this curve editor responds to
- L680 _public prototype_ `TSharedPtr<UE::CurveEditor::FPromotedFilterContainer> GetToolbarPromotedFilters() const;` — @return The object managing which filters are promoted to the toolbar for quick access.
- L685 _public function_ `void SuspendBroadcast()` — Suspend or resume broadcast of curve array changing
- L690 _public function_ `void ResumeBroadcast()`
- L696 _public function_ `bool IsBroadcasting()`
- L701 _public prototype_ `void BroadcastCurveChanged(FCurveModel* InCurve);`
- L708 _protected prototype_ `void ConstructXGridLines(TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels) const;` — Construct grid lines along the current display frame rate or time-base
- L716 _protected prototype_ `void ZoomToFitInternal(EAxisList::Type Axes, const TMap<FCurveModelID, FKeyHandleSet>& CurveKeySet);` — Internal zoom to fit implementation @param Axes        The axes to zoom (only X or Y supported) @param CurveKeySet Map from curve ID to keys that should be considered for zoom. Empty key sets will cause the entire curve range to be zoomed.
- L721 _protected prototype_ `void ApplyBufferedCurveToTarget(const IBufferedCurveModel* BufferedCurve, FCurveModel* TargetCurve);` — Apply a specific buffered curve to a specific target curve.
- L723 _protected prototype_ `void OnCustomColorsChanged();`
- L724 _protected prototype_ `void OnAxisSnappingChanged();`
- L729 _protected member_ `TUniquePtr<ICurveEditorBounds> Bounds;` — Curve editor bounds implementation
- L732 _protected member_ `TMap<FCurveModelID, TUniquePtr<FCurveModel>> CurveData;` — Map from curve model ID to the actual curve model
- L734 _protected member_ `TMap<FCurveModelID, FCurveEditorTreeItemID> TreeIDByCurveID;` — Map from curve model ID to its originating tree item
- L736 _protected member_ `TMultiMap<FCurveModelID, FCurveModelID> ChildCurves;` — Map of child curves
- L739 _protected member_ `TSortedMap<FName, TSharedPtr<FCurveEditorAxis>, FDefaultAllocator, FNameFastLess> CustomAxes;` — Map of all axes
- L742 _protected member_ `TSet<FCurveModelID> PinnedCurves;` — Set of pinned curve models
- L744 _protected member_ `TWeakPtr<SCurveEditorPanel> WeakPanel;`
- L746 _protected member_ `TWeakPtr<SCurveEditorView> WeakView;`
- L749 _protected member_ `FCurveEditorTree Tree;` — Hierarchical information pertaining to curve data
- L752 _protected member_ `TOptional<FCurveEditorToolID> ActiveTool;` — The currently active tool if any. If unset then no tool is currently active and the next selection will default to the first tool.
- L755 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — UI command list of actions mapped to this curve editor
- L758 _protected member_ `UCurveEditorSettings* Settings;` — Curve editor settings object
- L761 _protected member_ `TArray<TSharedRef<ICurveEditorExtension>> EditorExtensions;` — List of editor extensions we have initialized.
- L764 _protected member_ `TAttribute<const FCurveEditorZoomScaleConfig*> ZoomScalingAttr;` — The zoom scale config that was passed in to us in InitCurveEditor.
- L767 _protected member_ `TMap<FCurveEditorToolID, TUniquePtr<ICurveEditorToolExtension>> ToolExtensions;` — List of tool extensions we have initialized.
- L770 _protected member_ `TWeakPtr<ITimeSliderController> WeakTimeSliderController;` — Optional external Time Slider controller to sync with. Enables some additional functionality.
- L776 _protected member_ `bool bBoundTransformUpdatesSuppressed;` — Should attempts to update the bounds of each curve be ignored? This allows tools to keep the bounds from being automatically updated each frame which allows Normalized views to push past their boundaries without the normalization ratio changing per-frame as you drag.
- L779 _protected member_ `FCurveEditorAxisSnap AxisSnapMetrics;` — Track which axis UI movements should be snapped to (where applicable) based on limitations imposed by the UI.
- L782 _protected member_ `TArray<TUniquePtr<IBufferedCurveModel>> BufferedCurves;` — Buffered Curves. When a curve is buffered it is copied and the new copy is uniquely owned by the Curve Editor.
- L785 _protected member_ `uint32 ActiveCurvesSerialNumber;` — A serial number that is incremented any time the currently active set of curves are changed
- L788 _protected member_ `int32 SuspendBroadcastCount;` — Counter to suspend broadcasting of changed delegates
- L791 _protected member_ `TUniquePtr<UE::CurveEditor::FTransactionManager> TransactionManager;` — Orchestrates transaction that affect this curve editor.
- L794 _protected member_ `TPimplPtr<UE::CurveEditor::FSelectionCleanser> SelectionCleanser;` — Makes sure that selection does not reference stale FKeyHandles or FCurveModelIds, i.e. after undo or an operation has removed keys.
- L800 _protected member_ `TPimplPtr<UE::CurveEditor::FCurveModelIdCache> CurveModelIdCache;` — Tries to re-use FCurveModelIDs when the conceptually same FCurveModel is added back to FCurveEditor using AddCurve. @see FCurveModelIdCache.
- L810 _private member_ `UE::CurveEditor::FResolveCurveModelDelegate ResolveCurveModelDelegate;` — Internally used for editing FCurveModels after they've been removed FCurveEditor::CurveData (e.g. once they're no longer visible). Important for applying undo / redo commands on curves that are not visible when the user issues the undo / redo operation.
- L813 _private prototype_ `TUniquePtr<FCurveModel> ResolveCurve(const FCurveModelID& InCurveID) const;` — Tries to re-create a FCurveModel that was in this FCurveEditor previously but has since been removed.
- L819 _private member_ `FVector2D CachedPhysicalSize;` — Cached physical size of the panel representing this editor
- L822 _private prototype_ `void HandleCurveColorChanged(FCurveModelID CurveId);` — Invoked when a curve's color changes (FCurveModel::SetColor is called).
- L828 _public member_ `FOnCurveArrayChanged OnCurveArrayChanged;` — Delegate that's broadcast when the curve display changes.

#### enum `FCurveEditor::ECurveFlipDirection`  
`enum class ECurveFlipDirection : uint8`  
_L523-527_
- desc: Curve flip direction types
- L525 _public enumerator_ `Horizontal`
- L526 _public enumerator_ `Vertical`

#### enum `FCurveEditor::ECurveFlipRangeType`  
`enum class ECurveFlipRangeType : uint8`  
_L530-535_
- desc: Curve Flip selection types
- L532 _public enumerator_ `KeyRange`
- L533 _public enumerator_ `CurveRange`
- L534 _public enumerator_ `CustomRange`

#### struct `FCurveEditor::FCurveFlipRangeSettings`  
`struct FCurveFlipRangeSettings`  
_L538-550_
- desc: Settings for Curve Flip dropdown menu selections
- L540 _public member_ `ECurveFlipRangeType RangeType;`
- L541 _public member_ `float MinRange;`
- L542 _public member_ `float MaxRange;`
- L544 _public function_ `FCurveFlipRangeSettings() : RangeType(ECurveFlipRangeType::CustomRange) , MinRange(0.0f) , MaxRange(1.0f)`

#### Free symbols / members of external scopes

- L41 _macro_ `#define UE_API CURVEEDITOR_API`
- L60 _namespace_ `namespace UE`
- L60 _namespace_ `namespace CurveEditor` (scope `UE`)
- L61 _namespace_ `namespace UE`
- L61 _namespace_ `namespace CurveEditor` (scope `UE`)
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace CurveEditor` (scope `UE`)
- L64 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetBoolean, bool) DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveToolChanged, FCurveEditorToolID) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCurveArrayChanged, FCurveModel*, bool ,const FCurveEditor*);`
- L64 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetBoolean, bool) DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveToolChanged, FCurveEditorToolID) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCurveArrayChanged, FCurveModel*, bool ,const FCurveEditor*);`
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveToolChanged, FCurveEditorToolID) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCurveArrayChanged, FCurveModel*, bool ,const FCurveEditor*);`
- L66 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCurveArrayChanged, FCurveModel*, bool ,const FCurveEditor*);`
- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurveColorsChanged, TConstArrayView<FCurveModelID>);`
- L67 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurveColorsChanged, TConstArrayView<FCurveModelID>);`

### `Source/Editor/CurveEditor/Public/CurveEditorAxis.h` (Public)


#### enum `ECurveEditorAxisOrientation`  
`enum class ECurveEditorAxisOrientation : uint8`  
_L14-20_
- desc: Curve editor axis orientation enumeration
- L16 _public enumerator_ `Horizontal = 1`
- L17 _public enumerator_ `Vertical = 2`
- L19 _public enumerator_ `Both = Horizontal | Vertical`

#### class `FCurveEditorAxis`  
`class FCurveEditorAxis`  
_L26-57_
- desc: Class that models an underlying curve data structure through a generic abstraction that the curve editor understands.
- L30 _public prototype_ `virtual ~FCurveEditorAxis() = default;`
- L35 _public prototype_ `virtual bool HasLabels() const;` — Check whether this axis can draw labels
- L41 _public prototype_ `virtual FText MakeLabel(double Value) const;` — Make a label for the specified value
- L47 _public prototype_ `virtual void GetGridLines(const FCurveEditor& CurveEditor, const SCurveEditorView& View, FCurveEditorViewAxisID AxisID, TArray<double>& OutMajorGridLines, TArray<double>& OutMinorGridLines, ECurveEditorAxisOrientation Axis) const;` — Get the grid lines for this axis definition
- L56 _public member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;` — An optional numeric type interface for displaying values on this axis

#### class `FLinearCurveEditorAxis`  
`class FLinearCurveEditorAxis : public FCurveEditorAxis`  
_L63-68_
- inherits: `FCurveEditorAxis`
- desc: Implementation of FCurveEditorAxis that draws grid lines on a linear basis
- L66 _private prototype_ `virtual void GetGridLines(const FCurveEditor& CurveEditor, const SCurveEditorView& View, FCurveEditorViewAxisID AxisID, TArray<double>& OutMajorGridLines, TArray<double>& OutMinorGridLines, ECurveEditorAxisOrientation Axis) const override;`

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_CLASS_FLAGS(ECurveEditorAxisOrientation);`

### `Source/Editor/CurveEditor/Public/CurveEditorCommands.h` (Public)


#### class `FCurveEditorCommands`  
`class FCurveEditorCommands : public TCommands<FCurveEditorCommands>`  
_L20-143_
- inherits: `TCommands<FCurveEditorCommands>`
- desc: Defines commands for SCurveEditorPanel (and UnrealEd::SCurveEditor)
- L23 _public function_ `FCurveEditorCommands() : TCommands<FCurveEditorCommands> ( TEXT("GenericCurveEditor"), NSLOCTEXT("Contexts", "GenericCurveEditor", "Curve Editor"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFitHorizontal;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFitVertical;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFit;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFitAll;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ToggleInputSnapping;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> ToggleOutputSnapping;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> FlipCurveHorizontal;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> FlipCurveVertical;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> ToggleExpandCollapseNodes;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ToggleExpandCollapseNodesAndDescendants;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ExpandAllNodes;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> CollapseAllNodes;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> SortAllNodes;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> InterpolationConstant;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> InterpolationLinear;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> InterpolationCubicAuto;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> InterpolationCubicSmartAuto;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> InterpolationCubicUser;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> InterpolationCubicBreak;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> InterpolationToggleWeighted;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> FlattenTangents;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> StraightenTangents;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> SmartSnapKeys;`
- L64 _public member_ `TSharedPtr< FUICommandInfo > MatchLastTangentToFirst;`
- L65 _public member_ `TSharedPtr< FUICommandInfo > MatchFirstTangentToLast;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> BakeCurve;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> ReduceCurve;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> SetPreInfinityExtrapCycle;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> SetPreInfinityExtrapCycleWithOffset;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> SetPreInfinityExtrapOscillate;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> SetPreInfinityExtrapLinear;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> SetPreInfinityExtrapConstant;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> SetPostInfinityExtrapCycle;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> SetPostInfinityExtrapCycleWithOffset;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> SetPostInfinityExtrapOscillate;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> SetPostInfinityExtrapLinear;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> SetPostInfinityExtrapConstant;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> SetAllTangentsVisibility;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> SetUserTangentsVisibility;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> SetSelectedKeysTangentVisibility;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> SetNoTangentsVisibility;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoFrameCurveEditor;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> ToggleSnapTimeToSelection;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowBufferedCurves;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowCurveEditorCurveToolTips;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowTransportControls;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowBars;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowValueIndicatorLines;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> SetRandomCurveColorsForSelected;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> SetCurveColorsForSelected;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> AddKeyHovered;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> PasteKeysHovered;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> PasteAndMerge;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> PasteRelative;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> AddKeyToAllCurves;`
- L104 _public member_ `TSharedPtr<FUICommandInfo> AddKeyToSelectedCurves;`
- L105 _public member_ `TSharedPtr<FUICommandInfo> ResetKeysToDefaultValues;`
- L108 _public member_ `TSharedPtr<FUICommandInfo> SetViewModeAbsolute;`
- L109 _public member_ `TSharedPtr<FUICommandInfo> SetViewModeStacked;`
- L110 _public member_ `TSharedPtr<FUICommandInfo> SetViewModeNormalized;`
- L112 _public member_ `TSharedPtr<FUICommandInfo> DeactivateCurrentTool;`
- L114 _public member_ `TSharedPtr<FUICommandInfo> SelectAllKeys;`
- L115 _public member_ `TSharedPtr<FUICommandInfo> DeselectAllKeys;`
- L117 _public member_ `TSharedPtr<FUICommandInfo> SelectForward;`
- L118 _public member_ `TSharedPtr<FUICommandInfo> SelectBackward;`
- L119 _public member_ `TSharedPtr<FUICommandInfo> SelectNone;`
- L120 _public member_ `TSharedPtr<FUICommandInfo> InvertSelection;`
- L122 _public member_ `TSharedPtr<FUICommandInfo> BufferVisibleCurves;`
- L123 _public member_ `TSharedPtr<FUICommandInfo> SwapBufferedCurves;`
- L124 _public member_ `TSharedPtr<FUICommandInfo> ApplyBufferedCurves;`
- L127 _public member_ `TSharedPtr<FUICommandInfo> OpenUserImplementableFilterWindow;` — User Filtering
- L130 _public member_ `TSharedPtr<FUICommandInfo> SetAxisSnappingNone;` — Axis Snapping
- L131 _public member_ `TSharedPtr<FUICommandInfo> SetAxisSnappingHorizontal;`
- L132 _public member_ `TSharedPtr<FUICommandInfo> SetAxisSnappingVertical;`
- L135 _public member_ `TSharedPtr<FUICommandInfo> TranslateSelectedKeysLeft;` — Key Movement
- L136 _public member_ `TSharedPtr<FUICommandInfo> TranslateSelectedKeysRight;`
- L139 _public member_ `TSharedPtr<FUICommandInfo> ScrubTime;` — Time Management
- L142 _public prototype_ `virtual void RegisterCommands() override;`

### `Source/Editor/CurveEditor/Public/CurveEditorCurveDrawParamsCache.h` (Public)


#### class `UE::CurveEditor::FCurveDrawParamsCache`  
`class FCurveDrawParamsCache : public TSharedFromThis<FCurveDrawParamsCache>`  
_L28-126_
- inherits: `TSharedFromThis<FCurveDrawParamsCache>`
- desc: Caches curve draw params for curves of a curve editor.
- L73 _public prototype_ `FCurveDrawParamsCache();`
- L79 _public prototype_ `void Invalidate(const TSharedRef<SCurveEditorView>& CurveEditorView, TConstArrayView<FCurveModelID> ModelIDs = {});` — Invalidates the cache for specified view and curve model IDs and causes an update on cached data. The cache may perform updates that are not instantly relevant asynchronously. To update data synchronous use UpdateCurveDrawParamSynchonous instead.
- L85 _public function_ `ECurveCacheFlags GetCurveCacheFlags() const` — Returns how the curve cache has changed since it was last generated. Note for a data change it may only effect certain data (curves) not every drawn curve
- L88 _public function_ `const FCachedCurveEditorData& GetCurveEditorData() const` — Returns cached data common to the curve editor
- L91 _public function_ `const TArray<FCurveDrawParams>& GetCurveDrawParams() const` — Returns the current draw params
- L94 _public prototype_ `void UpdateAllCurveDrawParamSynchonous(const TSharedRef<SCurveEditorView>& CurveEditorView, const TArray<FCurveModelID>& CurveModelIDs, TArray<FCurveDrawParams>& OutParams);` — Updates curve draw params for all specified curve models, synchronous.
- L97 _public prototype_ `void UpdateCurveDrawParamsSynchonous(const FCurveEditorScreenSpace& CurveSpace, FCurveModel* CurveModel, const FCurveModelID& ModelID, FCurveDrawParams& Params);` — Gets curve draw params for a curve model, synchronous.
- L101 _private prototype_ `void UpdateCurveCacheFlags(const TSharedRef<SCurveEditorView>& CurveEditorView);` — Updates the curve cache flags
- L104 _private prototype_ `void DrawCurves(const TSharedRef<SCurveEditorView>& CurveEditorView, TConstArrayView<FCurveModelID> ModelIDs = {});` — Draws the curves, possibly async
- L107 _private prototype_ `void UpdateCurveDrawParams(const TSharedRef<SCurveEditorView>& CurveEditorView, const TArray<FCurveDrawParamsHandle>& CurveDrawParamsHandles);` — Updates curve draw params, possibly async
- L110 _private member_ `ECurveCacheFlags CurveCacheFlags = ECurveCacheFlags::UpdateAll;` — Curve cache flags that change based upon data or view getting modified
- L113 _private member_ `TArray<FCurveDrawParams> CachedDrawParams;` — The actual cached draw params
- L116 _private member_ `FCachedCurveEditorData CachedCurveEditorData;` — Cached data common to the curve editor
- L119 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — The curve editor that owns this cache
- L125 _private member_ `FOnCurveHasChangedExternally OnCurveHasChangedExternallyDelegate;` — Invoked when FCurveModel::HasChangedAndResetTest returns true. Only used by SCurveEditorView at the moment thus not public API.

#### enum `UE::CurveEditor::FCurveDrawParamsCache::ECurveCacheFlags`  
`enum class ECurveCacheFlags : uint8`  
_L39-43_
- desc: Flag enum signifying how the curve cache has changed since it was last generated
- L41 _public enumerator_ `CheckCurves = 0` — The cache may be valid need to check each curve to see if they are still valid
- L42 _public enumerator_ `UpdateAll = 1 << 0` — Update all curves

#### struct `UE::CurveEditor::FCurveDrawParamsCache::FCachedCurveEditorData`  
`struct FCachedCurveEditorData`  
_L46-71_
- desc: Set of cached values we need to check each tick to see if we need to redo cache
- L49 _public member_ `uint32 ActiveCurvesSerialNumber = 0;` — Serial number cached from FCurveEditor::GetActiveCurvesSerialNumber() on tick
- L52 _public member_ `uint32 SelectionSerialNumber = 0;` — Serial number bached from CurveEditorSelecstion::GetSerialNumber
- L55 _public member_ `ECurveEditorTangentVisibility TangentVisibility = ECurveEditorTangentVisibility::NoTangents;` — Cached Tangent Visibility
- L58 _public member_ `double InputMin = 0.0;` — Cached input min value
- L61 _public member_ `double InputMax = 0.0;` — Cached input max value
- L64 _public member_ `double OutputMin = 0.0;` — Cached output min value
- L67 _public member_ `double OutputMax = 0.0;` — Cached output max value
- L70 _public member_ `FVector2D CachedGeometrySize = FVector2D::ZeroVector;` — Cached Geometry Size

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace CurveEditor` (scope `UE`)
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurveHasChangedExternally, const FCurveModelID&);` — Invoked when FCurveModel::HasChangedAndResetTest returns true.
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurveHasChangedExternally, const FCurveModelID&);` (scope `UE::CurveEditor`) — Invoked when FCurveModel::HasChangedAndResetTest returns true.

### `Source/Editor/CurveEditor/Public/CurveEditorCurveDrawParamsHandle.h` (Public)


#### struct `UE::CurveEditor::FCurveDrawParamsHandle`  
`struct FCurveDrawParamsHandle`  
_L17-42_
- desc: Handle for an entry in the draw params array
- L19 _public prototype_ `FCurveDrawParamsHandle() = default;`
- L22 _public prototype_ `FCurveDrawParamsHandle(const TSharedRef<FCurveDrawParamsCache>& InDrawParamsCache, const int32 InIndex);` — Constructs the handle from the index in curve draw params.
- L28 _public prototype_ `FCurveDrawParams* Get() const;` — Returns the draw params or nullptr if the draw params no longer exists. Does a slow lookup if the array changed.
- L31 _public function_ `const FCurveModelID& GetID() const` — Returns the curve model ID that corresponds to these curve draw params.
- L35 _private member_ `FCurveModelID CurveModelID;` — The curve model ID that corresponds to the curve draw params
- L38 _private member_ `mutable int32 Index = INDEX_NONE;` — Index of the draw params in the array of the draw params cache
- L41 _private member_ `TWeakPtr<class FCurveDrawParamsCache> WeakDrawParamsCache;` — Weak ptr to the draw params cache that owns the draw params

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CURVEEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/CurveEditorDelegates.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditor` (scope `UE`)
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TUniquePtr<FCurveModel>, FResolveCurveModelDelegate, const FCurveModelLookUpArgs& );` — Tries to resolve a FCurveModel. This is intended for asking the external systems owning the FCurveEditor instance to construct the temporary FCurveModel API, e.g. when perform an undo / redo operation for a FCurveModel that is not currently visible (FCurveEditor::CurveData only contains visible curves). Can return nullptr if the curve cannot be resolved.
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TUniquePtr<FCurveModel>, FResolveCurveModelDelegate, const FCurveModelLookUpArgs& );` (scope `UE::CurveEditor`) — Tries to resolve a FCurveModel. This is intended for asking the external systems owning the FCurveEditor instance to construct the temporary FCurveModel API, e.g. when perform an undo / redo operation for a FCurveModel that is not currently visible (FCurveEditor::CurveData only contains visible curves). Can return nullptr if the curve cannot be resolved.

### `Source/Editor/CurveEditor/Public/CurveEditorHelpers.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace CurveEditor`
- L17 _prototype_ `FVector2D ComputeScreenSpaceTangentOffset(const FCurveEditorScreenSpace& CurveSpace, float Tangent, float Weight);` (scope `CurveEditor`)
- L19 _prototype_ `void TangentAndWeightFromOffset(const FCurveEditorScreenSpace& CurveSpace, const FVector2D& TangentOffset, float& OutTangent, float& OutWeight);` (scope `CurveEditor`)
- L21 _prototype_ `FVector2D GetVectorFromSlopeAndLength(float Slope, float Length);` (scope `CurveEditor`)
- L23 _prototype_ `void PopulateGridLineValues(float PhysicalSize, double ViewMin, double ViewMax, uint8 InMinorDivisions, TArray<double>& OutMajorGridLines, TArray<double>& OutMinorGridLines);` (scope `CurveEditor`)
- L25 _prototype_ `void ConstructYGridLines(const FCurveEditorScreenSpace& ViewSpace, uint8 InMinorDivisions, TArray<float>& OutMajorGridLines, TArray<float>& OutMinorGridLines, FText GridLineLabelFormatY, TArray<FText>* OutMajorGridLabels);` (scope `CurveEditor`)
- L27 _prototype_ `void ConstructFixedYGridLines(const FCurveEditorScreenSpace& ViewSpace, uint8 InMinorDivisions, double InMinorGridStep, TArray<float>& OutMajorGridLines, TArray<float>& OutMinorGridLines, FText GridLineLabelFormatY, TArray<FText>* OutMajorGridLabels, TOptional<double> InOutputMin, TOptional<double> InOutputMax);` (scope `CurveEditor`)

### `Source/Editor/CurveEditor/Public/CurveEditorKeyProxy.h` (Public)


#### class `UCurveEditorKeyProxy`  
`class UCurveEditorKeyProxy : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICurveEditorKeyProxy`  
`class ICurveEditorKeyProxy`  
_L20-30_
- desc: Interface that can be implemented by any object passed to a curve editor to use as a key editing proxy. When used, UpdateValuesFromRawData will be called every frame to optionally retrieve the current values of the key for this proxy.
- L29 _public prototype_ `virtual void UpdateValuesFromRawData() = 0;` — Called by the curve editor to update this instance's properties with the underlying raw data, if necessary

### `Source/Editor/CurveEditor/Public/CurveEditorScreenSpace.h` (Public)


#### struct `FCurveEditorScreenSpaceH`  
`struct FCurveEditorScreenSpaceH`  
_L17-86_
- desc: Utility struct used for converting to/from curve editor screen space
- L22 _public function_ `FCurveEditorScreenSpaceH(double InPixelWidth, double InInputMin, double InInputMax) : PixelWidth(FMath::Max(InPixelWidth, 1.0)) , InputMin(InInputMin), InputMax(InInputMax)` — Construction from a physical size, and input/output range
- L35 _public function_ `FORCEINLINE double ScreenToSeconds(double ScreenPosition) const` — Convert a horizontal screen position in slate units to a value in seconds
- L41 _public function_ `FORCEINLINE double SecondsToScreen(double InSeconds) const` — Convert a value in seconds to a horizontal screen position in slate units
- L49 _public function_ `FORCEINLINE double PixelsPerInput() const` — Retrieve the number of slate units per input value
- L58 _public function_ `FORCEINLINE double GetInputMin() const` — Get the minimum input value displayed on the screen
- L60 _public function_ `FORCEINLINE double GetInputMax() const` — Get the maximum input value displayed on the screen
- L62 _public function_ `FORCEINLINE double GetPhysicalWidth() const` — Get the physical width of the screen
- L69 _public function_ `FCurveEditorScreenSpaceH ToCurveSpace(const FTransform2d& CurveTransform) const` — Transform this screen space into a curve space using the specified transform
- L84 _private member_ `double PixelWidth;`
- L85 _private member_ `double InputMin, InputMax;`
- L85 _private member_ `double InputMin, InputMax;`

#### struct `FCurveEditorScreenSpaceV`  
`struct FCurveEditorScreenSpaceV`  
_L92-161_
- desc: Utility struct used for converting to/from curve editor screen space
- L97 _public function_ `FCurveEditorScreenSpaceV(double InPixelHeight, double InOutputMin, double InOutputMax) : PixelHeight(FMath::Max(InPixelHeight, 1.0)) , OutputMin(InOutputMin), OutputMax(InOutputMax)` — Construction from a physical size, and input/output range
- L110 _public function_ `FORCEINLINE double ScreenToValue(double ScreenPosition) const` — Convert a vertical screen position in slate units to a value
- L116 _public function_ `double ValueToScreen(double InValue) const` — Convert a value to a vertical screen position in slate units
- L124 _public function_ `FORCEINLINE double PixelsPerOutput() const` — Retrieve the number of slate units per output value
- L133 _public function_ `FORCEINLINE double GetOutputMin() const` — Get the minimum output value displayed on the screen
- L135 _public function_ `FORCEINLINE double GetOutputMax() const` — Get the maximum output value displayed on the screen
- L137 _public function_ `FORCEINLINE double GetPhysicalHeight() const` — Get the physical height of the screen
- L144 _public function_ `FCurveEditorScreenSpaceV ToCurveSpace(const FTransform2d& CurveTransform) const` — Transform this screen space into a curve space using the specified transform
- L159 _private member_ `double PixelHeight;`
- L160 _private member_ `double OutputMin, OutputMax;`
- L160 _private member_ `double OutputMin, OutputMax;`

#### struct `FCurveEditorScreenSpace`  
`struct FCurveEditorScreenSpace : FCurveEditorScreenSpaceH, FCurveEditorScreenSpaceV`  
_L166-213_
- inherits: `FCurveEditorScreenSpaceH,FCurveEditorScreenSpaceV`
- desc: Utility struct used for converting to/from curve editor screen space
- L171 _public function_ `FCurveEditorScreenSpace(FVector2D InPixelSize, double InInputMin, double InInputMax, double InOutputMin, double InOutputMax) : FCurveEditorScreenSpaceH(InPixelSize.X, InInputMin, InInputMax) , FCurveEditorScreenSpaceV(InPixelSize.Y, InOutputMin, InOutputMax)` — Construction from a physical size, and input/output range
- L179 _public function_ `FORCEINLINE FVector2D GetPhysicalSize() const` — Get the physical size of the screen
- L186 _public function_ `FCurveEditorScreenSpace ToCurveSpace(const FTransform2d& CurveTransform) const` — Transform this screen space into a curve space using the specified transform
- L198 _public function_ `bool operator==(const FCurveEditorScreenSpace& Other) const`
- L209 _public function_ `bool operator !=(const FCurveEditorScreenSpace& Other)`

### `Source/Editor/CurveEditor/Public/CurveEditorSelection.h` (Public)


#### struct `FKeyHandleSet`  
`struct FKeyHandleSet`  
_L37-99_
- desc: A set of key handles implemented as a sorted array for transparent passing to TArrayView<> APIs. Lookup is achieved via binary search: O(log(n)).
- L42 _public prototype_ `void Add(FKeyHandle Handle, ECurvePointType PointType);` — Add a new key handle to this set
- L47 _public prototype_ `void Toggle(FKeyHandle Handle, ECurvePointType PointType);` — Remove a handle from this set if it already exists, otherwise add it to the set
- L52 _public prototype_ `void Remove(FKeyHandle Handle, ECurvePointType PointType);` — Remove a handle from this set
- L60 _public prototype_ `void Replace(const TArrayView<const FKeyHandle>& InKeys, const ECurvePointType InPointType);` — Replace this set with exactly these keys and assign them this point type @param InKeys The array of key handles to reset the set with. @param InPointType The point type to associate with the keys.
- L65 _public prototype_ `bool Contains(FKeyHandle Handle, ECurvePointType PointType) const;` — Check whether the specified handle exists in this set
- L70 _public function_ `FORCEINLINE int32 Num() const` — Retrieve the number of handles in this set
- L75 _public function_ `FORCEINLINE TArrayView<const FKeyHandle> AsArray() const` — Retrieve a constant view of this set as an array
- L80 _public function_ `ECurvePointType PointType(FKeyHandle Handle) const` — Retrieve the point type for this handle
- L95 _private member_ `TArray<FKeyHandle, TInlineAllocator<1>> SortedHandles;` — Sorted array of key handles
- L98 _private member_ `TMap<FKeyHandle, ECurvePointType> HandleToPointType;` — Map of handle to point type (point, left, or right tangent)

#### class `FScopedSelectionChangedEventSuppressor`  
`class FScopedSelectionChangedEventSuppressor`  
_L101-109_
- L104 _public prototype_ `explicit FScopedSelectionChangedEventSuppressor(FCurveEditorSelection& InSelection);`
- L105 _public prototype_ `~FScopedSelectionChangedEventSuppressor();`
- L108 _private member_ `FCurveEditorSelection& Selection;`

#### struct `FCurveEditorSelection`  
`struct FCurveEditorSelection`  
_L115-279_
- desc: Class responsible for tracking selections of keys. Only one type of point selection is supported at a time (key, arrive tangent, or leave tangent)
- L125 _public prototype_ `FCurveEditorSelection();` — Default constructor
- L131 _public prototype_ `FCurveEditorSelection(TWeakPtr<FCurveEditor> InWeakCurveEditor);` — Constructor which takes a reference to the curve editor, which is used to find if a model is read only
- L136 _public function_ `FORCEINLINE uint32 GetSerialNumber() const` — Retrieve this selection's serial number. Incremented whenever a change is made to the selection.
- L141 _public function_ `FORCEINLINE bool IsEmpty() const` — Check whether the selection is empty
- L146 _public function_ `FORCEINLINE const TMap<FCurveModelID, FKeyHandleSet>& GetAll() const` — Retrieve all selected key handles, organized by curve ID
- L151 _public prototype_ `const FKeyHandleSet* FindForCurve(FCurveModelID InCurveID) const;` — Retrieve a set of selected key handles for the specified curve
- L156 _public prototype_ `int32 Count() const;` — Count the total number of selected keys by accumulating the number of selected keys for each curve
- L161 _public prototype_ `bool IsSelected(FCurvePointHandle InHandle) const;` — Check whether the specified handle is selected
- L166 _public prototype_ `bool Contains(FCurveModelID CurveID, FKeyHandle KeyHandle, ECurvePointType PointType) const;` — Check whether the specified handle and curve ID is contained in this selection.
- L169 _public prototype_ `FSimpleMulticastDelegate& OnSelectionChanged();` — Invoked when the selection changes.
- L176 _public prototype_ `void Add(FCurvePointHandle InHandle);` — Add a point handle to this selection, changing the selection type if necessary.
- L181 _public prototype_ `void Add(FCurveModelID CurveID, ECurvePointType PointType, FKeyHandle KeyHandle);` — Add a key handle to this selection, changing the selection type if necessary.
- L186 _public prototype_ `void Add(FCurveModelID CurveID, ECurvePointType PointType, TArrayView<const FKeyHandle> Keys);` — Add key handles to this selection, changing the selection type if necessary.
- L194 _public prototype_ `void Replace(const TMap<FCurveModelID, FKeyHandleSet>& InCurveToSelectedKeys);` — Replaces the current key selection in one batched update using prebuilt per-curve key-handle sets. Curves that are invalid or read-only are skipped using the same validation rules as Add(...). @param InCurveToSelectedKeys Map of curve IDs to the exact selected keys to apply for each curve.
- L204 _public prototype_ `void Replace(const TMap<FCurveModelID, TArray<FKeyHandle>>& InCurveToSelectedKeys, const ECurvePointType InPointType);` — Replaces the current key selection in one batched update using raw per-curve key-handle arrays. Curves that are invalid or read-only are skipped using the same validation rules as Add(...). All keys supplied for a given curve are associated with InPointType. @param InCurveToSelectedKeys Map of curve IDs to the selected key handles to apply for each curve. @param InPointType Point type to assign to every supplied key handle.
- L211 _public prototype_ `void Toggle(FCurvePointHandle InHandle);` — Toggle the selection of the specified point handle, changing the selection type if necessary.
- L216 _public prototype_ `void Toggle(FCurveModelID CurveID, ECurvePointType PointType, FKeyHandle KeyHandle);` — Toggle the selection of the specified key handle, changing the selection type if necessary.
- L221 _public prototype_ `void Toggle(FCurveModelID CurveID, ECurvePointType PointType, TArrayView<const FKeyHandle> Keys);` — Toggle the selection of the specified key handles, changing the selection type if necessary.
- L228 _public prototype_ `void Remove(FCurvePointHandle InHandle);` — Remove the specified point handle from the selection
- L233 _public prototype_ `void Remove(FCurveModelID CurveID, ECurvePointType PointType, FKeyHandle KeyHandle);` — Remove the specified key handle from the selection
- L238 _public prototype_ `void Remove(FCurveModelID CurveID, ECurvePointType PointType, TArrayView<const FKeyHandle> Keys);` — Remove the specified key handles from the selection
- L243 _public prototype_ `void Remove(FCurveModelID InCurveID);` — Remove all key handles associated with the specified curve ID from the selection
- L248 _public prototype_ `void Clear();` — Clear the selection entirely
- L253 _public prototype_ `void SerializeSelection(FArchive& Ar);` — Serializes the SerialNumber and CurveToSelectedKeys.
- L258 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Weak reference to the curve editor to check whether keys are locked or not
- L261 _private member_ `uint32 SerialNumber;` — A serial number that increments every time a change is made to the selection
- L264 _private member_ `TMap<FCurveModelID, FKeyHandleSet> CurveToSelectedKeys;` — A map of selected handles stored by curve ID
- L267 _private member_ `UE::CurveEditor::FSuppressibleEventBroadcaster OnSelectionChangedBroadcaster;` — Invoked when the selection changes.
- L270 _private prototype_ `void IncrementOnSelectionChangedSuppressionCount();` — Prevents OnSelectionChanged from being Broadcast until a matching call to DecrementOnSelectionChangedSuppressionCount is made.
- L272 _private prototype_ `void DecrementOnSelectionChangedSuppressionCount();` — Allows OnSelectionChanged to be Broadcast if the counter reaches 0. Invokes OnSelectionChanged if a change has been made since.
- L275 _private prototype_ `void AddInternal(FCurveModelID CurveID, ECurvePointType PointType, TArrayView<const FKeyHandle> Keys, bool bIncrementSerialNumber = true);` — Adds the specified key handles from the selection without validating whether CurveId and Keys exists in the owning curve editor.
- L278 _private prototype_ `void PostChangesMade();` — Shared logic after some changes have been made.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CURVEEDITOR_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace CurveEditor` (scope `UE`)
- L23 _namespace_ `namespace KeySelection` (scope `UE::CurveEditor`)
- L85 _function_ `friend FArchive& operator<<(FArchive& Ar, FKeyHandleSet& HandleSet)` — Serializes the handle set

### `Source/Editor/CurveEditor/Public/CurveEditorSettings.h` (Public)


#### enum `ECurveEditorPanningMouseButton`  
`enum class ECurveEditorPanningMouseButton : uint8`  
_L25-30_
- reflection: `UENUM()`
- L27 _public enumerator_ `Right UMETA(DisplayName = "Right")`
- L28 _public enumerator_ `AltMiddle UMETA(DisplayName = "Alt-Middle")`
- L29 _public enumerator_ `RightOrAltMiddle UMETA(DisplayName = "Right or Alt-Middle")`

#### enum `ECurveEditorTangentVisibility`  
`enum class ECurveEditorTangentVisibility : uint8`  
_L34-47_
- reflection: `UENUM()`
- desc: Defines visibility states for the tangents in the curve editor.
- L37 _public enumerator_ `AllTangents` — All tangents should be visible.
- L39 _public enumerator_ `SelectedKeys` — Only tangents from selected keys should be visible.
- L41 _public enumerator_ `NoTangents` — Don't display tangents.
- L43 _public enumerator_ `UserTangents` — Only tangents that are user edited, i.e. set to user or break should be visible.
- L46 _public enumerator_ `Num UMETA(Hidden)` — Add new entries above.

#### enum `ECurveEditorZoomPosition`  
`enum class ECurveEditorZoomPosition : uint8`  
_L51-58_
- reflection: `UENUM()`
- desc: Defines the position to center the zoom about in the curve editor.
- L54 _public enumerator_ `CurrentTime UMETA(DisplayName = "Playhead")` — Playhead.
- L57 _public enumerator_ `MousePosition UMETA(DisplayName = "Mouse Position")` — Mouse Position.

#### enum `ECurveEditorSnapAxis`  
`enum class ECurveEditorSnapAxis : uint8`  
_L62-70_
- reflection: `UENUM()`
- desc: Defines the axis to snap to when dragging.
- L65 _public enumerator_ `CESA_None UMETA(DisplayName = "None")` — Don't snap to any axis when dragging.
- L67 _public enumerator_ `CESA_X UMETA(DisplayName = "X Only")` — Snap to the x axis when dragging.
- L69 _public enumerator_ `CESA_Y UMETA(DisplayName = "Y Only")` — Snap to the y axis when dragging.

#### struct `FCustomColorForChannel`  
`struct FCustomColorForChannel`  
_L74-88_
- reflection: `USTRUCT()`
- desc: Custom Color Object
- L78 _public function_ `FCustomColorForChannel() : Object(nullptr), Color(1.0f, 1.0f, 1.0f, 1.0f)`
- L81 _public member_ `TSoftClassPtr<UObject> Object;` — `UPROPERTY(EditAnywhere, Category = "Custom Colors")`
- L83 _public member_ `FString PropertyName;` — `UPROPERTY(EditAnywhere, Category = "Custom Colors")`
- L85 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category = "Custom Colors")`

#### struct `FCustomColorForSpaceSwitch`  
`struct FCustomColorForSpaceSwitch`  
_L92-103_
- reflection: `USTRUCT()`
- desc: Custom Color Object
- L96 _public function_ `FCustomColorForSpaceSwitch() : Color(1.0f, 1.0f, 1.0f, 1.0f)`
- L99 _public member_ `FString ControlName;` — `UPROPERTY(EditAnywhere, Category = "Space Switch Colors")`
- L101 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category = "Space Switch Colors")`

#### class `UCurveEditorSettings`  
`class UCurveEditorSettings : public UObject`  
_L107-326_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Serializable options for curve editor.
- L112 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCustomColorsChanged);`
- L113 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAxisSnappingChanged);`
- L114 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnShowValueIndicatorsChanged);`
- L116 _public prototype_ `UCurveEditorSettings();`
- L119 _public prototype_ `bool AllowMousePan(const FPointerEvent& MouseEvent) const;` — Get whether the mouse event allows panning or editing
- L120 _public prototype_ `bool AllowMouseEdit(const FPointerEvent& MouseEvent) const;`
- L123 _public prototype_ `bool GetAutoFrameCurveEditor() const;` — Gets whether or not the curve editor auto frames the selected curves.
- L125 _public prototype_ `void SetAutoFrameCurveEditor(bool InbAutoFrameCurveEditor);` — Sets whether or not the curve editor auto frames the selected curves.
- L128 _public prototype_ `bool GetShowTransportControls() const;` — Gets whether or not the curve editor shows the transport controls panel.
- L130 _public prototype_ `void SetShowTransportControls(const bool bInShow);` — Sets whether or not the curve editor shows the transport controls panel.
- L133 _public prototype_ `bool GetShowBars() const;` — Gets whether or not the curve editor shows key bar style curves, like for constraints and spaces.
- L135 _public prototype_ `void SetShowBars(bool InShowBars);` — Sets whether or not the curve editor shows key bar style curves, like for constraints and spaces.
- L138 _public prototype_ `int32 GetFrameInputPadding() const;` — Gets the number of pixels to pad input framing
- L140 _public prototype_ `void SetFrameInputPadding(int32 InFrameInputPadding);` — Sets the number of pixels to pad input framing
- L143 _public prototype_ `int32 GetFrameOutputPadding() const;` — Gets the number of pixels to pad output framing
- L145 _public prototype_ `void SetFrameOutputPadding(int32 InFrameOutputPadding);` — Sets the number of pixels to pad output framing
- L148 _public prototype_ `bool GetShowBufferedCurves() const;` — Gets whether or not to show buffered curves in the curve editor.
- L150 _public prototype_ `void SetShowBufferedCurves(bool InbShowBufferedCurves);` — Sets whether or not to show buffered curves in the curve editor.
- L154 _public prototype_ `bool GetCubicAddKeyPrefersUserTangent() const;` — Get whether inserted key will be user tangent when possible.
- L156 _public prototype_ `void SetCubicAddKeyPrefersUserTangent(bool bInCubicAddKeyPrefersUserTangent);` — Sets wGet whether inserted key will be user tangent when possible.
- L159 _public prototype_ `bool GetShowCurveEditorCurveToolTips() const;` — Gets whether or not to show curve tool tips in the curve editor.
- L161 _public prototype_ `void SetShowCurveEditorCurveToolTips(bool InbShowCurveEditorCurveToolTips);` — Sets whether or not to show curve tool tips in the curve editor.
- L164 _public prototype_ `ECurveEditorTangentVisibility GetTangentVisibility() const;` — Gets the current tangent visibility.
- L166 _public prototype_ `void SetTangentVisibility(ECurveEditorTangentVisibility InTangentVisibility);` — Sets the current tangent visibility.
- L169 _public prototype_ `ECurveEditorZoomPosition GetZoomPosition() const;` — Get zoom in/out position (mouse position or current time).
- L171 _public prototype_ `void SetZoomPosition(ECurveEditorZoomPosition InZoomPosition);` — Set zoom in/out position (mouse position or current time).
- L174 _public prototype_ `ECurveEditorSnapAxis GetSnapAxis() const;` — Get snap axis.
- L176 _public prototype_ `void SetSnapAxis(ECurveEditorSnapAxis InSnapAxis);` — Set snap axis.
- L179 _public prototype_ `bool GetSnapTimeToSelection() const;` — Get whether to snap the time to the currently selected key.
- L181 _public prototype_ `void SetSnapTimeToSelection(bool bInSnapTimeToSelection);` — Set whether to snap the time to the currently selected key.
- L184 _public prototype_ `void SetSelectionColor(const FLinearColor& InColor);` — Set the selection color.
- L186 _public prototype_ `FLinearColor GetSelectionColor() const;` — Get the selection color.
- L189 _public prototype_ `TOptional<FLinearColor> GetCustomColor(UClass* InClass, const FString& InPropertyName) const;` — Get custom color for object and property if it exists, if it doesn't the optional won't be set
- L191 _public prototype_ `void SetCustomColor(UClass* InClass, const FString& InPropertyName, FLinearColor InColor);` — Set Custom Color for the specified parameters.
- L193 _public prototype_ `void DeleteCustomColor(UClass* InClass, const FString& InPropertyName);` — Delete Custom Color for the specified parameters.
- L196 _public function_ `FOnCustomColorsChanged& GetOnCustomColorsChanged()` — Gets the multicast delegate which is run whenever custom colors have changed.
- L198 _public function_ `FOnAxisSnappingChanged& GetOnAxisSnappingChanged()` — Gets the multicast delegate which is run whenever axis snapping has changed.
- L200 _public function_ `FOnShowValueIndicatorsChanged& OnShowValueIndicatorsChanged()` — Gets the multicast delegate which is run whenever showing the value indicator lines has changed.
- L203 _public prototype_ `TOptional<FLinearColor> GetSpaceSwitchColor(const FString& InControlName) const;` — Get custom color for space name. Parent and World are reserved names and will be used instead of the specified control name.
- L205 _public prototype_ `void SetSpaceSwitchColor(const FString& InControlName, FLinearColor InColor);` — Set Custom Space SwitchColor for the specified control name.
- L207 _public prototype_ `void DeleteSpaceSwitchColor(const FString& InControlName);` — Delete Custom Space Switch Color for the specified control name.
- L210 _public prototype_ `static FLinearColor GetNextRandomColor();` — Helper function to get next random linear color
- L213 _public function_ `float GetTreeViewWidth() const` — Gets the tree view width percentage
- L215 _public prototype_ `void SetTreeViewWidth(float InTreeViewWidth);` — Sets the tree view width percentage
- L218 _public function_ `float GetMarqueePointSensitivity() const` — Gets how sensitive the selection marquee should be when selecting points.
- L220 _public prototype_ `void SetMarqueePointSensitivity(float InMarqueePointSensitivity);` — Sets how sensitive the selection marquee should be when selecting points.
- L223 _public function_ `bool GetShowValueIndicators() const` — @return Whether to draw a value indicator line for the minimum and maximum key in the selected key range.
- L225 _public prototype_ `void SetShowValueIndicators(bool bValue);` — Sets whether to draw a value indicator line for the minimum and maximum key in the selected key range.
- L228 _public prototype_ `bool GetScrubTimeStartFromCursor() const;` — Gets whether or not scrubbing time hot key starts from cursor.
- L230 _public prototype_ `void SetScrubTimeStartFromCursor(bool bInValue);` — Sets whether or not scrubbing time hot key starts from cursor.
- L233 _public prototype_ `bool GetMiddleMouseButtonAddsKey() const;` — Gets whether middle mouse button adds a keyframe in the curve editor.
- L235 _public prototype_ `void SetMiddleMouseButtonAddsKey(bool bInValue);` — Sets whether middle mouse button adds a keyframe in the curve editor.
- L239 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L242 _protected member_ `ECurveEditorPanningMouseButton PanningMouseButton;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L246 _protected member_ `bool bMiddleMouseButtonAddsKey;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")` — When enabled, clicking middle mouse button on a curve adds a keyframe at that position
- L249 _protected member_ `bool bAutoFrameCurveEditor;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor")`
- L252 _protected member_ `bool bShowTransportControls;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L255 _protected member_ `bool bShowBars;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L259 _protected member_ `int32 FrameInputPadding;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta=(ClampMin=0))` — Number of pixels to add as padding in the input axis when framing curve keys
- L263 _protected member_ `int32 FrameOutputPadding;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta=(ClampMin=0))` — Number of pixels to add as padding in the output axis when framing curve keys
- L266 _protected member_ `bool bShowBufferedCurves;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor")`
- L269 _protected member_ `bool bShowCurveEditorCurveToolTips;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor")`
- L272 _protected member_ `ECurveEditorTangentVisibility TangentVisibility;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor")`
- L275 _protected member_ `ECurveEditorZoomPosition ZoomPosition;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L278 _protected member_ `ECurveEditorSnapAxis SnapAxis;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L281 _protected member_ `bool bSnapTimeToSelection;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor")`
- L284 _protected member_ `FLinearColor SelectionColor;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L287 _protected member_ `TArray<FCustomColorForChannel> CustomColors;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor")`
- L290 _protected member_ `FLinearColor ParentSpaceCustomColor;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L293 _protected member_ `FLinearColor WorldSpaceCustomColor;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L296 _protected member_ `TArray<FCustomColorForSpaceSwitch> ControlSpaceCustomColors;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L299 _protected member_ `float TreeViewWidth;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")`
- L303 _protected member_ `bool bScrubTimeStartFromCursor;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")` — When enabled, scrubbing time hotkey will move time from initial cursor position
- L307 _protected member_ `bool bCubicAddKeyPrefersUserTangent;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")` — When enabled, inserted key will be user tangent when possible
- L316 _protected member_ `float MarqueePointSensitivity = 0.45f;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor", meta = (ClampMin = 0.0, ClampMax = 1.0))` — Determines how close you must move the selection marque to the center of a point in order to select it. This is the percentage of point's center to the point's widget border that must be overlapped with the marquee in order for the point to be selected. 1.0 means as soon as marquee overlaps any portion of the point. 0.0 means you must touch the point's center to select it.
- L320 _protected member_ `bool bShowValueIndicators = true;` — `UPROPERTY(config, EditAnywhere, Category = "Curve Editor")` — When you select a single curve, whether to draw a dotted line for the minimum and maximum key in the selected key range.
- L323 _private member_ `FOnCustomColorsChanged OnCustomColorsChangedEvent;`
- L324 _private member_ `FOnAxisSnappingChanged OnAxisSnappingChangedEvent;`
- L325 _private member_ `FOnShowValueIndicatorsChanged OnShowValueIndicatorsChangedEvent;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API CURVEEDITOR_API`
- L112 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCustomColorsChanged);`
- L113 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAxisSnappingChanged);`
- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnShowValueIndicatorsChanged);`

### `Source/Editor/CurveEditor/Public/CurveEditorSnapMetrics.h` (Public)


#### struct `FCurveSnapMetrics`  
`struct FCurveSnapMetrics`  
_L12-45_
- L14 _public function_ `FCurveSnapMetrics()`
- L21 _public member_ `uint8 bSnapOutputValues : 1;` — Whether we are snapping to the output snap interval
- L24 _public member_ `uint8 bSnapInputValues : 1;` — Whether we are snapping to the input snap rate
- L27 _public member_ `TArray<double> AllGridLines;` — Grid lines to snap to
- L30 _public member_ `FFrameRate InputSnapRate;` — The input snap rate
- L33 _public function_ `FORCEINLINE double SnapInputSeconds(double InputTime) const` — Snap the specified input time to the input snap rate if necessary
- L39 _public function_ `FORCEINLINE double SnapOutput(double OutputValue) const` — Snap the specified output value to the output snap interval if necessary

#### struct `FCurveEditorAxisSnap`  
`struct FCurveEditorAxisSnap`  
_L50-153_
- desc: Utility struct that acts as a way to control snapping to a specific axis based on UI settings, or shift key.
- L78 _public member_ `ECurveEditorSnapAxis RestrictedAxisList;` — Can be set to either X, Y, or None to control which axis GetSnappedPosition snaps to. User can override None by pressing shift.
- L80 _public function_ `FCurveEditorAxisSnap()`
- L94 _public function_ `FVector2D GetSnappedPosition( const FVector2D& InitialPosition, const FVector2D& LastPosition, const FVector2D& CurrentPosition, const FPointerEvent& MouseEvent, FSnapState& InOutSnapState, const bool bIgnoreAxisLock = false )` — Combines an InitialPosition and mouse movement to produce a final position that respects the axis snapping settings. Pressing shift ignores the snapping settings. For example, if movement is constrained to x-axis only and the mouse moves in direction FVector2D{ 100, 200 }, only the delta movement of FVector2D{ 100, 0} is applied. @return The end position resulting from applying the snapping behavior to the mouse movement.

#### struct `FCurveEditorAxisSnap::FSnapState`  
`struct FSnapState`  
_L56-75_
- desc: Snapping is not stateless but we want to manage it through the central area. This allows state to be passed into from the calling area but still centralize the logic of handling it.
- L58 _public function_ `FSnapState()`
- L63 _public function_ `void Reset()`
- L71 _public member_ `FVector2D MousePosOnShiftStart;`
- L72 _public member_ `FVector2D MouseLockVector;`
- L73 _public member_ `bool bHasPassedThreshold;`
- L74 _public member_ `bool bHasStartPosition;`

#### Free symbols / members of external scopes

- L42 _function_ `return bSnapOutputValues && !AllGridLines.IsEmpty() ? *Algo::MinElement(AllGridLines, [OutputValue](double Val1, double Val2) { return FMath::Abs(Val1 - OutputValue) < FMath::Abs(Val2 - OutputValue); } ) : OutputValue;` (scope `FCurveSnapMetrics::SnapOutput`)

### `Source/Editor/CurveEditor/Public/CurveEditorTypes.h` (Public)


#### enum `ECurvePointType`  
`enum class ECurvePointType : uint8`  
_L17-24_
- desc: Enum for representing the type of a key point in the curve editor
- L19 _public enumerator_ `None = 0x000`
- L20 _public enumerator_ `Key = 0x001`
- L21 _public enumerator_ `ArriveTangent = 0x002`
- L22 _public enumerator_ `LeaveTangent = 0x004`
- L23 _public enumerator_ `Any = Key | ArriveTangent | LeaveTangent`

#### enum `ECurveEditorTreeSelectionState`  
`enum class ECurveEditorTreeSelectionState : uint8`  
_L27-30_
- L29 _public enumerator_ `None`
- L29 _public enumerator_ `None`
- L29 _public enumerator_ `None`

#### enum `ECurveEditorViewID`  
`enum class ECurveEditorViewID : uint64`  
_L33-43_
- desc: Enumeration identifying a single specific view type, or a combination thereof
- L35 _public enumerator_ `Invalid = 0`
- L37 _public enumerator_ `Absolute = 1 << 0`
- L38 _public enumerator_ `Normalized = 1 << 1`
- L39 _public enumerator_ `Stacked = 1 << 2`
- L41 _public enumerator_ `CUSTOM_START = 1 << 3`
- L42 _public enumerator_ `ANY_BUILT_IN = Absolute | Normalized | Stacked`

#### struct `FCurveModelID`  
`struct FCurveModelID`  
_L50-110_
- desc: A unique identifier for a curve model existing on a curve editor
- L53 _public function_ `FCurveModelID() : ID(0)` — Default constructor is needed by e.g. TArray::operator<<
- L58 _public prototype_ `static FCurveModelID Unique();` — Generate a new curve model ID
- L63 _public function_ `bool IsValid() const` — @return Whether this ID is valid (was constructed with Unique)
- L109 _private member_ `uint32 ID;` — Internal serial ID

#### struct `FCurvePointHandle`  
`struct FCurvePointHandle`  
_L118-130_
- desc: A unique handle to a particular point handle (key, tangent handle etc) on a curve, represented by the key's handle, its curve ID, and its type
- L120 _public function_ `FCurvePointHandle(FCurveModelID InCurveID, ECurvePointType InPointType, FKeyHandle InKeyHandle) : CurveID(InCurveID), PointType(InPointType), KeyHandle(InKeyHandle)`
- L125 _public member_ `FCurveModelID CurveID;` — The curve ID of the key's curve
- L127 _public member_ `ECurvePointType PointType;` — The type of this point
- L129 _public member_ `FKeyHandle KeyHandle;` — The key handle for the underlying key

#### struct `FCurveEditorTreeItemID`  
`struct FCurveEditorTreeItemID`  
_L132-172_
- L134 _public function_ `FCurveEditorTreeItemID() : Value(0)`
- L153 _public function_ `static FCurveEditorTreeItemID Invalid()`
- L158 _public function_ `bool IsValid() const`
- L163 _public function_ `uint32 GetValue() const`
- L171 _protected member_ `uint32 Value;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CURVEEDITOR_API`
- L44 _prototype_ `ENUM_CLASS_FLAGS(ECurveEditorViewID);`
- L68 _function_ `FORCEINLINE friend bool operator==(FCurveModelID A, FCurveModelID B)` — Check two IDs for equality
- L76 _function_ `FORCEINLINE friend bool operator!=(FCurveModelID A, FCurveModelID B)` — Check two IDs for inequality
- L84 _function_ `FORCEINLINE friend bool operator<(FCurveModelID A, FCurveModelID B)` — Test whether A is less than B
- L92 _function_ `FORCEINLINE friend uint32 GetTypeHash(FCurveModelID In)` — Hash a curve model ID
- L100 _function_ `FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FCurveModelID& Handle)` — Save a curve model ID
- L138 _function_ `friend bool operator==(FCurveEditorTreeItemID A, FCurveEditorTreeItemID B)`
- L143 _function_ `friend bool operator!=(FCurveEditorTreeItemID A, FCurveEditorTreeItemID B)`
- L148 _function_ `friend uint32 GetTypeHash(FCurveEditorTreeItemID ID)`

### `Source/Editor/CurveEditor/Public/CurveEditorZoomScaleConfig.h` (Public)


#### struct `FCurveEditorZoomScaleConfig`  
`struct FCurveEditorZoomScaleConfig`  
_L9-117_
- reflection: `USTRUCT()`
- L15 _public member_ `double MouseWheelZoomMultiplier = 1.0;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta = (ClampMin = 0.05, ClampMax = 32.0))` — Multiplier when zooming uniformly using mouse wheel. 1.0 means normal. Values < 1.0, make zoom 'slower', and > 1.0 zoom 'faster'.
- L33 _public member_ `FRuntimeFloatCurve HorizontalZoomScale;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta=( DisplayName="Right mouse (input axis)", XAxisName="Input Axis Length", YAxisName="Zoom Factor"))` — Easing function when zooming out on the X-axis using Alt+Shift+RMB + move mouse left/right. X-value is how far the mouse has travelled on the X-axis. Positive when zooming out, negative when zooming in. Y-Value is the resulting zoom multiplier. Must be >= 0.0. When zooming out (i.e. x < 0), the Y value must be <= 1.0 or zooming is unstable. Tip: You can use "CurveEditor.LogHorizontalZoomMultipliers" CVar to make tuning the x and y values easier. Example: - For Sequencer, the frame rate is the length of 1 (unit length). - So if Sequencer's target FPS is set to 30, and 45 frames are visible on the X-Axis in Curve Editor, we say the X-axis is 1.5 units wide. - We'd look up the value 1.5 in this easing function and use that as zoom multiplier.
- L51 _public member_ `FRuntimeFloatCurve VerticalZoomScale;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta=( DisplayName="Right mouse (output axis)", XAxisName="Output Axis Length", YAxisName="Zoom Factor"))` — Easing function when zooming out on the Y-axis using Alt+RMB + move mouse up/down. X-value is how far the mouse has travelled on the Y-axis.  Positive when zooming out, negative when zooming in. Y-Value is the resulting zoom multiplier. Must be >= 0.0. When zooming out (i.e. x < 0), the Y value must be <= 1.0 or zooming is unstable. Tip: You can use "CurveEditor.LogVerticalZoomMultipliers" CVar to make tuning the x and y values easier. Example: - Suppose in Curve Editor, the Y-axis bounds are +2000 to -1000. - The height of the Y-axis is thus 3000. - We'd look up the value of 3000 in this easing function and use that as zoom multiplier.
- L55 _public member_ `bool bLimitHorizontalZoomOut = false;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta = (ClampMin = 0.00))` — If true, when zooming out using right-click the vertical axis size will be limited.
- L64 _public member_ `double MaxHorizontalZoomOut = 10000.0;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta = (ClampMin = 0.00, EditCondition = "bLimitHorizontalZoomOut", EditConditionHides))` — If bLimitHorizontalZoomOut is true, then this max allowed value range the input axis can show. Example: If this is 1000, and you have zoomed out so the axis shows -200 and 800, you can zoom out no further. For Sequencer, this is the max number of seconds. So, you need multiply this with the target FPS. So 1000 would mean a max of 3000 frames with a target FPS of 30.
- L68 _public member_ `bool bLimitVerticalZoomOut = false;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta = (ClampMin = 0.00))` — If true, when zooming out using right-click the horizontal axis size will be limited.
- L74 _public member_ `double MaxVerticalZoomOut = 10000.0;` — `UPROPERTY(config, EditAnywhere, Category="Curve Editor", meta = (ClampMin = 0.00, EditCondition = "bLimitVerticalZoomOut", EditConditionHides))` — If bLimitVerticalZoomOut is true, then this max allowed value range the output axis can show. Example: If this is 1000, and you have zoomed out so the axis shows -200 and 800, you can zoom out no further.
- L76 _public function_ `FCurveEditorZoomScaleConfig()`
- L92 _public function_ `double GetMouseWheelZoomMultiplierClamped() const`
- L99 _public function_ `double EvalHorizontalZoom(double InAxisSize) const` — Evaluates VerticalZoomScale. @param InAxisSize Absolute value is Max - Min displayed axis values. Positive when zooming out, negative when zooming in. @return Correctly clamped zoom factor.
- L111 _public function_ `double EvalVerticalZoom(double InAxisSize) const` — Evaluates VerticalZoomScale. @param InAxisSize Absolute value is Max - Min displayed axis values. Positive when zooming out, negative when zooming in. @return Correctly clamped zoom factor.

### `Source/Editor/CurveEditor/Public/CurveModel.h` (Public)


#### class `FCurveModel`  
`class FCurveModel`  
_L51-754_
- desc: Class that models an underlying curve data structure through a generic abstraction that the curve editor understands.
- L56 _public function_ `FCurveModel() : Color(0.2f,0.2f,0.2f) , bKeyDrawEnabled(true) , SupportedViews(ECurveEditorViewID::ANY_BUILT_IN)`
- L62 _public function_ `virtual ~FCurveModel()`
- L70 _public prototype_ `virtual const void* GetCurve() const = 0;` — Access the raw pointer of the curve data
- L75 _public prototype_ `virtual void Modify() = 0;` — Explicitly modify the curve data. Called before any change is made to the curve.
- L84 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const = 0;` — Draw the curve for the specified curve editor by populating an array with points on the curve between which lines should be drawn @param CurveEditor             Reference to the curve editor that is drawing the curve. Can be used to cull the interpolating points to the visible region. @param ScreenSpace			  A transform which indicates the use case for the drawn curve. This lets you simplify curves based on their screenspace representation. @param OutInterpolatingPoints  Array to populate with points (time, value) that lie on the curve.
- L95 _public function_ `virtual UE::CurveEditor::ICurveEditorCurveCachePool* DrawCurveToCachePool( const TSharedRef<FCurveEditor>& CurveEditor, const UE::CurveEditor::FCurveDrawParamsHandle& CurveDrawParamsHandle, const FCurveEditorScreenSpace& ScreenSpace)` — Draws curve draw params to a cache pool. Curves can implement this to improve performance over DrawCurve by caching their data. @param WeakCurveEditor			Weak reference to the curve editor that is drawing the curve. @param CurveDrawParamsHandle		A handle to the actual curve draw params. @param ScreenSpace				The screenspace of this curve @return							Returns the cache pool or nullptr if the curve model does not implement a cache pool.
- L104 _public function_ `virtual void GetKeys(const FCurveEditor& CurveEditor, double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const` — `UE_DEPRECATED(5.5, "Implement the version that doesn't take the Curve Editor parameter.")`
- L118 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const = 0;` — Retrieve all keys that lie in the specified time and value range @param MinTime                 Minimum key time to return in seconds @param MaxTime                 Maximum key time to return in seconds @param MinValue                Minimum key value to return @param MaxValue                Maximum key value to return @param OutKeyHandles           Array to populate with key handles that reside within the specified ranges
- L124 _public prototype_ `virtual void GetAllKeys(TArray<FKeyHandle>& OutKeyHandles) const;` — Gets all keys in the curve. Prefer this function over GetKeys because it has the potential to be much faster (GetValueRange evaluation can be slow for bezier curves).
- L129 _public function_ `TArray<FKeyHandle> GetAllKeys() const` — Gets all keys in the curve. Prefer this function over GetKeys because it has the potential to be much faster (GetValueRange evaluation can be slow for bezier curves).
- L138 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles = nullptr) = 0;` — Add keys to this curve @param InPositions             Key positions for the new keys @param InAttributes            Key attributes for the new keys, one per key position @param OutKeyHandles           (Optional) Pointer to an array view of size InPositions.Num() that should be populated with newly added key handles
- L141 _public function_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys)` — `UE_DEPRECATED(5.6, "Implement the version that uses the current time.")`
- L151 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) = 0;` — Remove all the keys with the specified key handles from this curve @param InKeys				Array of key handles to be removed from this curve @param InCurrentTime			Current time slider position, may be used to set any default value to the current value at that time if no keys exist
- L154 _public prototype_ `virtual void PutKeys(TConstArrayView<FKeyHandle> InKeys, TConstArrayView<FKeyPosition> InKeyPositions, TConstArrayView<FKeyAttributes> InAttributes);` — Adds the given keys if they are not yet present, or overwrites their current data if already present.
- L173 _public function_ `virtual void ReplaceKeyHandles(TConstArrayView<FKeyHandle> InCurrentHandles, TConstArrayView<FKeyHandle> InNewHandles)` — Remaps InNewHandles to reference the keys that InCurrentHandles reference. After this function concludes, the FKeyHandle InCurrentHandles no longer reference any keys in this curve. This operation is needed if you have to add keys that are mapped to specific FKeyHandle instances. A use case for this is undo / redo. Suppose the following user action sequence: 1. Move FKeyHandle(42), 2. Delete FKeyHandle(42), 3. Undo. In step 3, we must add the key back. Calling FCurveEditor::AddKeys generates a new FKeyHandle, but we need to add it back as FKeyHandle(42); otherwise step 1's reference to FKeyHandle(42) breaks and undoing the movement action would not work. FKeyHandle in InNewHandles that are already mapped to a key are skipped.. The corresponding InCurrentHandles is left unchanged and continues to reference the same key as before the call. FKeyHandles in InCurrentHandles that reference no keys are skipped. @param InCurrentHandles Key handles that are currentl in the curve model @param InNewHandles The key handles to remap to. Each index corresponds to the same index in InCurrentHandles.
- L181 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const = 0;` — Retrieve all key positions that pertain to the specified input key handles @param InKeys                  Array of key handles to get positions for @param OutKeyPositions         Array to receive key positions, one per index of InKeys
- L189 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) = 0;` — Assign key positions for the specified key handles @param InKeys                 Array of key handles to set positions for @param InKeyPositions         Array of desired key positions to be applied to each of the corresponding key handles
- L198 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const = 0;` — Populate the specified draw info structure with data describing how to draw the specified point type @param PointType              The type of point to be drawn @param InKeyHandle			 The specific key (if possible, otherwise FKeyHandle::Invalid()) to get the info for. @param OutDrawInfo            Data structure to be populated with draw info for this type of point
- L205 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const = 0;` — Get range of input time. @param MinTime Minimum Time @param MaxTime Minimum Time
- L211 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const = 0;` — Get range of output values. @param MinValue Minimum Value @param MaxValue Minimum Value
- L220 _public function_ `virtual void GetValueRange(double InMinTime, double InMaxTime, double& MinValue, double& MaxValue) const` — Get range of output value based on specified input times. By default will just get the range without a specified time @param MinTime Minimum Time @param MaxTime Maximium Time @param MinValue Minimum Value @param MaxValue Minimum Value
- L226 _public prototype_ `virtual int32 GetNumKeys() const = 0;` — Get the number of keys @param The number of keys
- L234 _public prototype_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const = 0;` — Get neighboring keys given the key handle @param InKeyHandle The key handle to get neighboring keys for @param OutPreviousKeyHandle The previous key handle @param OutNextKeyHandle The next key handle
- L247 _public prototype_ `virtual void GetClosestKeysTo(double InTime, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const;` — Finds the key before and after InTime. If there is a key at InTime, then OutPreviousKeyHandle and OutNextKeyHandle are set to the same value. If there are multiple keys at InTime (stacked), the implementation can return an arbitrary one as long as it is consistent (e.g. always the "first one") provided the internal state has not changed. @param InTime The time near which to search for keys @param OutPreviousKeyHandle The key with time <= InTime that is closest to InTime. Unset if there is no such key. @param OutNextKeyHandle The key with time >= InTime that is closest to InTime. Unset if there is no such key.
- L256 _public function_ `virtual TPair<ERichCurveInterpMode, ERichCurveTangentMode> GetInterpolationMode(const double& InTime, ERichCurveInterpMode DefaultInterpolationMode, ERichCurveTangentMode DefaultTangentMode) const` — Get the interpolation mode to use at a specified time @param InTime						The time we are looking for an interpolation mode @param DefaultInterpolationMode		Current default interpolation mode, returned if other keys not found or interpolation not supported @return Interpolation mode to use at that frame
- L268 _public prototype_ `virtual bool Evaluate(double InTime, double& OutValue) const = 0;` — Evaluate this curve at the specified time @param InTime                 The time to evaluate at, in seconds. @param Outvalue               Value to receive the evaluation result @return true if this curve was successfully evaluated, false otherwise
- L281 _public function_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const` — Retrieve ALL key attributes that pertain to the specified input key handles. This function is legacy. Prefer use of GetKeyAttributesIncludingAutoComputed or GetKeyAttributesExcludingAutoComputed. @see GetKeyAttributesIncludingAutoComputed (introduced 5.6). @param InKeys                Array of key handles to get attributes for @param OutAttributes         Array to receive key attributes, one per index of InKeys
- L296 _public function_ `virtual void GetKeyAttributesIncludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const` — Gets the value of ALL attributes including those that are auto-computed. Use this version if you want to know values e.g. the tangents or weights. Useful for UI code that visualizes tangents. The result is not intended to be passed to SetKeyAttributes; calling SetKeyAttributes would correct the passed in attributes to reflect the user settings. Typically, attributes reflect the settings that the user has manually configured for the keys, so certain attributes may remain unset. For instance, when TangentMode == RCTM_Auto, tangents and weights are automatically computed, meaning attributes like ArriveTangent are not explicitly set. Setting ArriveTangent would imply a user-defined value, which is incompatible with TangentMode == RCTM_Auto. In some situations, you don't want to know the values the user has set but the values as they would be used for evaluation, e.g. tangents, weights, etc. For these cases, you can use GetKeyAttributesIncludingAutoComputed.
- L314 _public function_ `virtual void GetKeyAttributesExcludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const` — Gets the attributes set by the user. This specifically excludes auto-computed values. Use this version if you want the "true" state of the keys. You can pass the result of this to SetKeyAttributes. Useful e.g. for copy-pasting keys. Typically, attributes reflect the settings that the user has manually configured for the keys, so certain attributes may remain unset. For instance, when TangentMode == RCTM_Auto, tangents and weights are automatically computed, meaning attributes like ArriveTangent are not explicitly set. Setting ArriveTangent would imply a user-defined value, which is incompatible with TangentMode == RCTM_Auto. This function returns only user-set values. @param InKeys                Array of key handles to get attributes for @param OutAttributes         Array to receive key attributes, one per index of InKeys
- L323 _public function_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified)` — Assign key attributes for the specified key handles @param InKeys                 Array of key handles to set attributes for @param InAttributes           Array of desired key attributes to be applied to each of the corresponding key handles
- L331 _public function_ `virtual void GetCurveAttributes(FCurveAttributes& OutAttributes) const` — Retrieve curve attributes for this curve @param OutAttributes          Attributes structure to populate with attributes that are relevant for this curve
- L339 _public function_ `virtual void SetCurveAttributes(const FCurveAttributes& InAttributes)` — Assign curve attributes for this curve @param InAttributes           Attributes structure to assign to this curve
- L345 _public function_ `virtual double GetInputDisplayOffset() const` — Retrieve an option input display offset (in seconds) to apply to all this curve's drawing
- L353 _public function_ `virtual FLinearColor GetColor() const` — Retrieve this curve's color
- L366 _public function_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects)` — Create key proxy objects for the specified key handles. One object should be assigned to OutObjects per index within InKeyHandles @param InWeakCurveEditor      The curve editor @param InCurveModelID         The curve model id for these key handles @param InKeyHandles           Array of key handles to create edit objects for @param OutObjects             (Out) Array to receive objects that should be used to edit each of the input key handles.
- L370 _public function_ `virtual void CreateKeyProxies(TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects)` — `UE_DEPRECATED(5.7, "Implement the version that takes a curve editor and curve model ID")`
- L377 _public function_ `virtual void MakeChildCurves(TArray<TUniquePtr<FCurveModel>>& OutChildCurves) const` — Called when this curve model is added to a curve editor in order to construct additional 'child' curves that are owned by this curve
- L387 _public function_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const` — Creates a copy of this curve, stored in a minimal buffered curve object. Buffered curves are used to cache the positions and attributes of a curve's keys. After creation, a buffered curve can be applied to any curve to set it to its saved state. Each curve must implement its own buffered curve which inherits IBufferedCurve and implements the DrawCurve method in order for it to be drawn on screen. Optionally implemented
- L395 _public function_ `virtual FTransform2d GetCurveTransform() const` — Return a per-curve transform for this model, if used by the view
- L403 _public function_ `virtual bool IsReadOnly() const` — Returns whether the curve model should be edited or not
- L411 _public function_ `virtual bool HasDefaultValue() const` — Returns whether this curve has a default value that selected keys can be reset to.
- L416 _public function_ `virtual double GetDefaultValue() const` — Returns the default value for this curve. Only meaningful when HasDefaultValue() returns true.
- L421 _public function_ `virtual UObject* GetOwningObject() const` — Get the UObject that owns this CurveModel, for example for Sequencer this would be the UMovieSceneSection
- L427 _public function_ `virtual bool HasChangedAndResetTest()` — Get if has changed and then reset it, this can be used for caching
- L435 _public function_ `virtual void AllocateAxes(FCurveEditor* InCurveEditor, TSharedPtr<FCurveEditorAxis>& OutHorizontalAxis, TSharedPtr<FCurveEditorAxis>& OutVerticalAxis) const` — Allocate and/or assign axes for the this curve
- L443 _public function_ `virtual void GetCurveColorObjectAndName(UObject** OutObject, FString& OutName) const` — Get the Object and the name to be used to store the curve model color (see UCurveEditorSettings). By default this is the owning object and the intent name, but it can be overriden, for example for Sequencer it may be the bound object
- L451 _public prototype_ `void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, const FKeyAttributes& InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified);` — Helper function for assigning a the same attributes to a number of keys
- L456 _public prototype_ `TOptional<FKeyHandle> AddKey(const FKeyPosition& NewKeyPosition, const FKeyAttributes& InAttributes);` — Helper function for adding a single key to this curve
- L460 _public function_ `FORCEINLINE FSimpleMulticastDelegate& OnCurveModified()` — Get a multicast delegate, fired when modifications are made to this curve
- L466 _public function_ `FORCEINLINE FSimpleMulticastDelegate& OnPostColorChanged()` — @return Multicast delegate invoked after the color is changed.
- L477 _public prototype_ `virtual UObject* GetOwningObjectOrOuter(UClass* Class) const;` — Get the owning object of this curve as the specified type, or search its outer chain if it is not the specified type. Subclasses can override the UClass-taking virtual below to inject objects (e.g. a directly-stored UMovieSceneSection on time warp curves whose owning getter is sequence-outered rather than section-outered).
- L480 _public function_ `template<typename T> T* GetOwningObjectOrOuter() const`
- L492 _public function_ `FORCEINLINE FText GetShortDisplayName() const` — Access this curve's short display name. This is useful when there are other UI elements which describe enough context about the curve that a long name is not needed (ie: Showing just "X" because other UI elements give the object/group context).
- L500 _public function_ `FORCEINLINE void SetShortDisplayName(const FText& InDisplayName)` — Assign a short display name for this curve
- L510 _public function_ `FORCEINLINE FText GetLongDisplayName() const` — Access this curve's long display name. This is useful when you want more context about the curve, such as the object it belongs to, or the group (ie: "Floor.Transform.X") instead of just "X" or "Transform.X"
- L524 _public function_ `FORCEINLINE void SetLongDisplayName(const FText& InLongDisplayName)` — Assign a long display name for this curve used in contexts where additional context is useful.
- L541 _public function_ `FORCEINLINE FString GetIntentionName() const` — This is an internal name used to try to match different curves with each other. When saving and later restoring curves on a different set of curves we need a name that gives enough context to match them up by intention, and not long or short name. For example, a curve might have a short name of "X", and a long name of "Floor.Transform.Location.X". If you wanted to copy a set of transform curves and paste them onto another transform, we use this context to match the names together to ensure your Transform.X gets applied to the other Transform.X - in this example the intention is for the curve to represent a "Location.X" (so it should be pasteable on any other curve which says their context is a "Location.X" as well). This is more reliable and more flexible than relying on short display names (not enough context in the case of seeing Location.X, and Scale.X) and better than relying on long display names (too much context and no reliable way to substring them).
- L550 _public function_ `FORCEINLINE void SetIntentionName(const FString& InIntentionName)` — Assign an intention name for this curve which is used internally when applying one curve to another in situations where multiple curves are visible.
- L555 _public function_ `FORCEINLINE void SetLongIntentionName(const FString& InIntentionName)`
- L560 _public function_ `FORCEINLINE FString GetLongIntentionName() const`
- L565 _public function_ `FORCEINLINE void SetChannelName(const FName& InChannelName)`
- L570 _public function_ `FORCEINLINE FName GetChannelName() const`
- L575 _public function_ `FORCEINLINE void SetColor(const FLinearColor& InColor)`
- L584 _public function_ `FORCEINLINE float GetDashLength() const` — Get the dash length used for rendering this curve (0 indicates a solid line should be used)
- L592 _public function_ `FORCEINLINE void SetDashLength(float InDashLengthPx)` — Set the dash length used for rendering this curve (0 indicates a solid line should be used)
- L600 _public function_ `FORCEINLINE float GetThickness() const` — Get this curve's visual thickness in screen space
- L608 _public function_ `FORCEINLINE void SetThickness(float InThickness)` — Set this curve's visual thickness in screen space
- L616 _public function_ `FORCEINLINE bool IsKeyDrawEnabled() const` — Retrieves whether or not to disable drawing keys
- L624 _public function_ `FORCEINLINE void SetIsKeyDrawEnabled(TAttribute<bool> bInKeyDrawEnabled)` — Assign whether or not to disable drawing keys
- L632 _public function_ `ECurveEditorViewID GetSupportedViews() const` — Retrieve this curve's supported views
- L638 _public function_ `void InitCurveId(FCurveModelID InCurveModelID = FCurveModelID::Unique())` — Inits this curve with an optionally specified ID.
- L647 _public function_ `const FCurveModelID& GetOrInitId()` — @return A valid curve ID
- L657 _public function_ `const TOptional<FCurveModelID>& GetId() const` — @return The curve ID - can be unset.
- L662 _protected member_ `FText ShortDisplayName;` — This curve's short display name. Used in situations where other mechanisms provide enough context about what the curve is (such as "X")
- L665 _protected member_ `FText LongDisplayName;` — This curve's long display name. Used in situations where the UI doesn't provide enough context about what the curve is otherwise (such as "Floor.Transform.X")
- L668 _protected member_ `FString IntentionName;` — This curve's short intention (such as Transform.X or Scale.X). Used internally to match up curves when saving/restoring curves between different objects.
- L674 _protected member_ `FString LongIntentionName;` — This curve's long intention (such as foot_fk_l.Transform.X or foot_fk_r.Scale.X). Used internally to match up curves when saving/restoring curves between different objects. Long intention names have priority in copy/paste over short intention names, but we fall back to short intention if it's unclear what the user is trying to do.
- L679 _protected member_ `FName ChannelName;` — The original channel name, used mostly to make sure names match with BP/Scripting
- L682 _protected member_ `FLinearColor Color;` — This curve's display color
- L685 _protected member_ `TAttribute<bool> bKeyDrawEnabled;` — Whether or not to draw curve's keys
- L688 _protected member_ `float DashLengthPx = 0.f;` — When this curve is to be drawn dashed, the length of each dash (or 0.f if solid)
- L691 _protected member_ `float Thickness = 2.f;` — Default thickness for this curve
- L694 _protected member_ `ECurveEditorViewID SupportedViews;` — A set of views supported by this curve
- L697 _protected member_ `FSimpleMulticastDelegate CurveModifiedDelegate;` — Multicast delegate broadcast on curve modification
- L700 _protected member_ `FSimpleMulticastDelegate PostColorChangedDelegate;` — Invokes by SetColor
- L703 _protected function_ `bool IsInChangeScope() const` — @return Whether this curve model is currently in a change scope.
- L716 _protected function_ `virtual void OnOpenRootChangeScope()` — Starts a scope of related changes. The curve model will receive a matching OnCloseRootChangeScope call when the scope ends. The curve model implementation should use this to defer any post-change type of delegates until OnCloseRootChangeScope is invoked. The primary use case is recording changes using FScopedCurveChange. Do not call Modify() on the FCurveObject::GetOwningObject(). In the future, this may be extended so the curve model can append internal FChange commands as well, which are to be ordered correctly with the changes made to the curve model. An example may be that SetKeyPositions should cause a call to UMovieSceneSection::ExpandToFrame. @see FScopedCurveChange "Interaction with Modify()-based undo" section
- L718 _protected function_ `virtual void OnCloseRootChangeScope()` — Closes the scope of related changes. The curve model can now call any callbacks it had deferred during the change scope.
- L727 _private member_ `TOptional<FCurveModelID> CurveId;` — This curve's unique ID. You can set the ID when you construct the curve. If left unspecified, this is initialized by FCurveEditor when you add the curve. The ID can only be set once during the lifetime of the FCurveModel to inconsistencies, e.g. TMap<FCurveModelId, TUniquePtr<FCurveModel>>.
- L734 _private member_ `int32 ChangeScopeCounter = 0;` — When positive, we're in a change scope. Otherwise, in no change scope. It is valid to mutate the curve model outside a change scope. The changes are just not considered to be related.
- L744 _private prototype_ `void OpenChangeScope();` — Starts a scope of related changes. This is used by the new undo system to avoid Modify call on the FCurveModel::GetOwningObject(). Every call must be matched by CloseChangeScope. It's ok to call this multiple times after the scope has been started already. @see OnOpenRootChangeScope, which is called when the scope is initially started.
- L753 _private prototype_ `void CloseChangeScope();` — Closes a scope of related changes. This is used by the new undo system. Every call matches a previous call to OpenChangeScope. It's ok to call this multiple times after the scope has been started already. @see OnCloseRootChangeScope, which is called when the scope outermost scope is closed.

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API CURVEEDITOR_API`
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace CurveEditor` (scope `UE`)
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace CurveEditor` (scope `UE`)
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Filters/CurveEditorBakeFilter.h` (Public)


#### struct `FCurveEditorBakeFilterRange`  
`struct FCurveEditorBakeFilterRange`  
_L24-33_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `FFrameNumber Min = FFrameNumber(0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`
- L32 _public member_ `FFrameNumber Max = FFrameNumber(10);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`

#### class `UCurveEditorBakeFilter`  
`class UCurveEditorBakeFilter : public UCurveEditorFilterBase`  
_L36-88_
- reflection: `UCLASS(MinimalAPI, DisplayName="Bake")`
- inherits: `UCurveEditorFilterBase`
- L40 _public function_ `UCurveEditorBakeFilter()`
- L51 _protected prototype_ `virtual void InitializeFilter_Impl(TSharedRef<FCurveEditor> InCurveEditoro) override;`
- L52 _protected prototype_ `virtual void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect) override;`
- L53 _protected prototype_ `virtual bool CanApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor) override;`
- L59 _public member_ `float BakeIntervalInSeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))` — The interval between baked keys when there is no valid Display Rate and Tick Resolution.
- L63 _public member_ `FFrameNumber BakeInterval;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — The interval between baked keys.
- L67 _public member_ `bool bCustomRangeOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — When enabled, CustomRange will be used for the bake region. Otherwise the selected keys will be used.
- L71 _public member_ `float CustomRangeMinInSeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bCustomRangeOverride"))` — Specifies a custom range to use for baking when there is no valid Display Rate and Tick Resolution.
- L75 _public member_ `float CustomRangeMaxInSeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bCustomRangeOverride"))` — Specifies a custom range to use for baking when there is no valid Display Rate and Tick Resolution.
- L79 _public member_ `FCurveEditorBakeFilterRange CustomRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bCustomRangeOverride"))` — Specifies a custom range to use for baking
- L83 _public member_ `bool bUseSeconds;` — `UPROPERTY()` — When enabled, will use BakeIntervalInSeconds and CustomRangeInSeconds. Otherwise, use BakeInterval and CustomRange which are defined by the Display Rate and Tick Resolution.
- L86 _private member_ `FFrameRate InitialDisplayRate;`
- L87 _private member_ `FFrameRate InitialTickResolution;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Filters/CurveEditorEulerFilter.h` (Public)


#### class `UCurveEditorEulerFilter`  
`class UCurveEditorEulerFilter : public UCurveEditorFilterBase`  
_L25-36_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Euler", meta = ( CurveEditorLabel = "Euler Filter", CurveEditorDescription = "Uses the Euler filter to correct jumps in rotation caused by angle wrapping or gimbal lock. For example, instead of wrapping around with a large jump from 178° to -178°, it smoothly interpolates a 4° transition, ensuring natural and continuous movement."))`
- inherits: `UCurveEditorFilterBase`
- L29 _public function_ `UCurveEditorEulerFilter()`
- L33 _protected prototype_ `virtual void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect) override;`
- L34 _protected prototype_ `virtual bool CanApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor) override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Filters/CurveEditorFilterBase.h` (Public)


#### class `UCurveEditorFilterBase`  
`class UCurveEditorFilterBase : public UObject`  
_L29-161_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config=EditorSettings)`
- inherits: `UObject`
- desc: An abstract base class for Curve Editor Filtering. If you inherit from this class your class will automatically show up in the Curve Editor's Filter dropdown. This allows projects to easily create custom filters to edit curve data as they only have to implement this class. Any UPROPERTY(EditAnywhere) properties exposed on the class will show up in the Curve Editor Filter panel which allows you to easily create customizable properties or advanced filters that rely on user supplied settings. The CDO is directly edited in the Curve Editor Filter panel so if you wish to save user settings between runs you can add the "config" property to your UPROPERTY() and it will automatically get saved.
- L36 _public prototype_ `static FText GetLabel(const TSubclassOf<UCurveEditorFilterBase>& InClass);` — `UCLASS(meta = (CurveEditorLabel = "value"))`
- L38 _public prototype_ `static FText GetDescription(const TSubclassOf<UCurveEditorFilterBase>& InClass);` — `UCLASS(meta = (CurveEditorDescription = "value"))`
- L43 _public prototype_ `static FSlateIcon GetIcon(const TSubclassOf<UCurveEditorFilterBase>& InClass);` — @return The icon associated with this class. Icons can be overriden in editor styles (e.g. FStarshipEditorStyle) with "ClassIcon.ClassName". @see FSlateIconFinder::FindIconForClass
- L48 _public function_ `void InitializeFilter(TSharedRef<FCurveEditor> InCurveEditor)` — Initialize this filter and any parameters it depends on
- L56 _public function_ `bool CanApplyFilter(TSharedRef<FCurveEditor> InCurveEditor)` — Check whether this filter can be applied to the specified curve editor
- L69 _public function_ `void ApplyFilter(TSharedRef<FCurveEditor> InCurveEditor, FCurveModelID InCurve, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect)` — Applies the filter to all keys on the specified curve. @param		InCurveEditor		The curve editor that owns the FCurveModelIDs to operate on. @param		InCurve				The curve to operate on. @param		OutKeysToSelect		The filter will empty and initialize the set and return you a set of curves and handles that the filter thinks should be selected after operating. This is useful for filters that create or destroy keys as it allows them to maintain the appearance that the selection has not been modified.
- L86 _public function_ `void ApplyFilter(TSharedRef<FCurveEditor> InCurveEditor, FCurveModelID InCurve, TArrayView<FKeyHandle> InKeyHandles, TArray<FKeyHandle>& OutKeysToSelect)` — Applies the filter to all keys on the specified curves. The curves are passed to the filter as a set so that a filter can choose to operate on multiple curves at once if data from other curves is important. @param		InCurveEditor		The curve editor that owns the FCurveModelIDs to operate on. @param		InCurve				The curve to operate on. @param		OutKeysToSelect		Returns an array containing the keys that the filter thinks should be selected after operating. This is useful for filters that create or destroy keys as it allows them to maintain the appearance that the selection has not been modified.
- L116 _public function_ `void ApplyFilter(TSharedRef<FCurveEditor> InCurveEditor, const TSet<FCurveModelID>& InCurves, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect)` — Applies the filter to all keys on the specified curves. The curves are passed to the filter as a set so that a filter can choose to operate on multiple curves at once if data from other curves is important. @param		InCurveEditor		The curve editor that owns the FCurveModelIDs to operate on. @param		InCurve				The set of curves to operate on. @param		OutKeysToSelect		The filter will empty and initialize the set and return you a set of curves and handles that the filter thinks should be selected after operating. This is useful for filters that create or destroy keys as it allows them to maintain the appearance that the selection has not been modified.
- L145 _public function_ `void ApplyFilter(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect)` — Applies the filter to all keys on the specified curves and specified keys. The curves are passed to the filter as a set so that a filter can choose to operate on multiple curves at once if data from other curves is important. Be warned that many filter operations operate on ranges so the specified keys may be interpreted as a min/max bounds by a filter and all keys in that curve between the two may get selected. @param		InCurveEditor		The curve editor that owns the FCurveModelIDs to operate on. @param		InKeysToOperateOn	The set of curves to operate on and the keys associated with each curve that the user wishes to apply the filter to. @param		OutKeysToSelect		The filter will empty and initialize the set and return you a set of curves and handles that the filter thinks should be selected after operating. This is useful for filters that create or destroy keys as it allows them to maintain the appearance that the selection has not been modified.
- L153 _protected function_ `virtual void InitializeFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor)` — Implementation function for initializing this filter
- L157 _protected function_ `virtual void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect)` — An implementation must override this function to implement filtering functionality. This is named different and doesn't use function overloading due to C++ name resolution issues which prevent calling base class functions of the same name (even with different signatures) from a pointer to the derived class.
- L160 _protected prototype_ `virtual bool CanApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor);` — Implementation function for determining whether this filter can be applied

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Filters/CurveEditorGaussianFilter.h` (Public)


#### struct `FGaussianParams`  
`struct FGaussianParams`  
_L21-32_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `int32 KernelWidth = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "3", ClampMax = "9999", UIMin = "3", UIMax = "9999"))` — Sigma that determines how 'fat' the filter is, higher value means fatter width
- L28 _public function_ `void Reset()`

#### class `UCurveEditorGaussianFilter`  
`class UCurveEditorGaussianFilter : public UCurveEditorFilterBase`  
_L35-59_
- reflection: `UCLASS(DisplayName = "Gaussian", CollapseCategories)`
- inherits: `UCurveEditorFilterBase`
- L39 _public function_ `UCurveEditorGaussianFilter()`
- L46 _public prototype_ `static void Gaussian(FCurveModel* Curve, const FGaussianParams& InParams, const TOptional<FKeyHandleSet>& KeyHandleSet, FKeyHandleSet& OutHandleSet);` — @param Curve to perform Gaussian @param InParams Params to use to peform reduction @param KeyHandleSet Optional set of keys to operate on, if not set we will operate on all of them @param OutHandleSet The set of new keys.
- L49 _protected prototype_ `void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect) override;`
- L51 _protected prototype_ `static TArray<double> CalculateKernel(int32 KernelWidth);`
- L52 _protected prototype_ `static double ApplyKernel(int32 Index, const TArray<double> Kernel, const TArray<FKeyPosition>& KeyPositions);`
- L57 _public member_ `FGaussianParams GaussianParams;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`

### `Source/Editor/CurveEditor/Public/Filters/CurveEditorReduceFilter.h` (Public)


#### class `UCurveEditorReduceFilter`  
`class UCurveEditorReduceFilter : public UCurveEditorFilterBase`  
_L20-46_
- reflection: `UCLASS(DisplayName="Simplify")`
- inherits: `UCurveEditorFilterBase`
- L24 _public function_ `UCurveEditorReduceFilter()`
- L32 _protected prototype_ `void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect) override;`
- L37 _public member_ `float Tolerance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Minimum change in values required for a key to be considered distinct enough to keep.
- L41 _public member_ `bool bTryRemoveUserSetTangentKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Flag whether or not to use SampleRate for sampling between evaluated keys, which allows for removing user-tangent keys.
- L45 _public member_ `FFrameRate SampleRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bTryRemoveUserSetTangentKeys"))` — Rate at which the curve should be sampled to compare against value tolerance.

### `Source/Editor/CurveEditor/Public/Filters/CurveEditorSmartReduceFilter.h` (Public)


#### struct `FSmartReduceParams`  
`struct FSmartReduceParams`  
_L21-47_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `float TolerancePercentage = 5.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))` — Tolerance threshold, set as a percentage of the value's range
- L30 _public member_ `FFrameRate SampleRate = FFrameRate(30, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Rate at which the curve should be sampled to compare against value tolerance.
- L34 _public member_ `bool bDeleteStaticChannels = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Remove all keys from static channels, and set that value as the default
- L38 _public member_ `bool bOnlyReduceStaticChannels = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Only reduce static channels
- L40 _public function_ `void Reset()`

#### class `UCurveEditorSmartReduceFilter`  
`class UCurveEditorSmartReduceFilter : public UCurveEditorFilterBase`  
_L50-72_
- reflection: `UCLASS(DisplayName = "Smart Reduce", CollapseCategories)`
- inherits: `UCurveEditorFilterBase`
- L54 _public function_ `UCurveEditorSmartReduceFilter()`
- L62 _public prototype_ `static void SmartReduce(FCurveModel* Curve, const FSmartReduceParams& InParams, const TOptional<FKeyHandleSet>& KeyHandleSet, const bool bNeedToTestExisting, FKeyHandleSet& OutHandleSet);` — @param Curve to perform a reduction that works by finding where values change velocity and then perform a tolerance based bisection on these intervals. @param InParams Params to use to peform reduction @param KeyHandleSet Optional set of keys to operate on, if not set we will operate on all of them @param bNeedToTestExisting If true we will test existing keys for custom tangents so we keep them, if false we don't need to test, for example after a bake @param OutHandleSet The set of new keys.
- L65 _protected prototype_ `void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect) override;`
- L70 _public member_ `FSmartReduceParams SmartReduceParams;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`

### `Source/Editor/CurveEditor/Public/Filters/CurveEditorSmartSnapFilter.h` (Public)


#### class `UCurveEditorSmartSnapFilter`  
`class UCurveEditorSmartSnapFilter : public UCurveEditorFilterBase`  
_L18-27_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Smart Snap", meta = ( CurveEditorLabel = "Smart Snap", CurveEditorDescription = "Snaps selected keys to the closest whole frame.\nThe key is placed where the curve intersects with the frame (imagine vertical line going down from the frame)."))`
- inherits: `UCurveEditorFilterBase`
- L24 _protected prototype_ `virtual void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect) override;`
- L25 _protected prototype_ `virtual bool CanApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Filters/PromotedFilterCommandBinder.h` (Public)


#### class `UE::CurveEditor::FPromotedFilterCommandBinder`  
`class FPromotedFilterCommandBinder : public FNoncopyable`  
_L23-55_
- inherits: `FNoncopyable`
- desc: Binds and unbinds commands that are created by FPromotedFilterContainer. When a filter is added to FPromotedFilterContainer, it creates a command to invoke that filter. This class is responsible to bind / unbind it.
- L32 _public prototype_ `explicit FPromotedFilterCommandBinder( const TSharedRef<FPromotedFilterContainer>& InContainer, const TSharedRef<FUICommandList>& InCommandList, const TSharedRef<FCurveEditor>& InCurveEditor );` — @param InContainer Holds the promoted filter commands to bind to. The caller ensures that it outlives the constructed object. @param InCommandList The command list to bind commands to. @param InCurveEditor The curve editor on which the filters will be applied.
- L37 _public prototype_ `~FPromotedFilterCommandBinder();`
- L42 _private member_ `const TWeakPtr<FPromotedFilterContainer> Container;` — The filter container this object binds to.
- L44 _private member_ `const TWeakPtr<FUICommandList> CommandList;` — Commands are added to and removed from this list.
- L46 _private member_ `const TWeakPtr<FCurveEditor> CurveEditor;` — Passed to filter as argument.
- L48 _private prototype_ `void OnFilterAdded(UCurveEditorFilterBase& InFilter, const TSharedRef<FUICommandInfo>& InCommand) const;`
- L49 _private prototype_ `void OnFilterRemoved(UCurveEditorFilterBase& InFilter, const TSharedRef<FUICommandInfo>& InCommand) const;`
- L51 _private prototype_ `void MapAction(UCurveEditorFilterBase& InFilter, const TSharedRef<FUICommandInfo>& InCommand, FUICommandList& CommandListPin) const;`
- L53 _private prototype_ `void ApplyFilter(UCurveEditorFilterBase* InFilter, TWeakPtr<FUICommandInfo> Command) const;`
- L54 _private prototype_ `bool CanApplyFilter(UCurveEditorFilterBase* InFilter, TWeakPtr<FUICommandInfo> Command) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CURVEEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Filters/PromotedFilterContainer.h` (Public)


#### class `UE::CurveEditor::FPromotedFilterContainer`  
`class FPromotedFilterContainer : public FGCObject , public FNoncopyable`  
_L34-106_
- inherits: `FGCObject,FNoncopyable`
- desc: Holds the state for surfacing filters to the toolbar from the SCurveEditorFilterPanel, so the user can access & apply them more quickly. TODO UE-230269: For now, the curve editor only adds the Euler filter to this container. Once UE-230269 is addressed (allowing users to surface filters to the toolbar via UI), this class should be extended to persistently save the user-specified filter settings,  e.g. the FGaussianParams for the UCurveEditorGaussianFilter, etc.
- L43 _public prototype_ `explicit FPromotedFilterContainer(FName InContextName);` — @param InContextName The ID to give the underlying FBindingContext. Must be globally unique.
- L47 _public prototype_ `void AppendToBuilder(FToolBarBuilder& InToolBarBuilder, const FMenuEntryResizeParams& InResizeParams = {}) const;` — Appends the filters to InToolbarBuilder.
- L49 _public prototype_ `void AppendToBuilder(FMenuBuilder& InMenuBuilder) const;` — Appends the filters to InMenuBuilder.
- L55 _public prototype_ `void AddInstance(UCurveEditorFilterBase& InFilter);` — Promotes a filter. For simplicity, each class can only have one instance promoted (e.g. you cannot call AddInstance with two different UCurveEditorEulerFilter instances).
- L58 _public prototype_ `void RemoveInstance(UCurveEditorFilterBase& InFilter);` — Removes a filter instance. You can pass in a CDO, too.
- L61 _public prototype_ `template<typename TCallback> requires std::is_invocable_v<TCallback, UCurveEditorFilterBase&, const TSharedRef<FUICommandInfo>&> void ForEachFilter(TCallback&& Callback);`
- L63 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FFilterDelegate, UCurveEditorFilterBase&, const TSharedRef<FUICommandInfo>&);`
- L65 _public function_ `FFilterDelegate& OnFilterAdded()` — Broadcasts when a filter is added to this container.
- L67 _public function_ `FFilterDelegate& OnFilterRemoved()` — Broadcasts when a filter is removed from this container.
- L70 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L71 _public function_ `virtual FString GetReferencerName() const override`
- L77 _private member_ `const TSharedRef<FBindingContext> CommandContext;` — Needed to dynamically create FUICommandInfo.
- L80 _private member_ `FFilterDelegate OnFilterAddedDelegate;` — Broadcasts when a filter is added to this container.
- L82 _private member_ `FFilterDelegate OnFilterRemovedDelegate;` — Broadcasts when a filter is removed from this container.
- L102 _private member_ `TArray<FFilterData> PromotedFilters;` — The filters that have been promoted.
- L104 _private prototype_ `int32 IndexOf(const UClass* InFilterClass) const;`
- L105 _private prototype_ `void RemoveAtInternal(int32 InIndex);`
- L109 _function_ `template <typename TCallback> requires std::is_invocable_v<TCallback, UCurveEditorFilterBase&, const TSharedRef<FUICommandInfo>&> void FPromotedFilterContainer::ForEachFilter(TCallback&& Callback)`

#### struct `UE::CurveEditor::FPromotedFilterContainer::FFilterData`  
`struct FFilterData`  
_L84-99_
- L87 _public member_ `UCurveEditorFilterBase& FilterInstance;` — The instance to apply. This can be the CDO or an actual owned instance.
- L93 _public member_ `TSharedRef<FUICommandInfo> Command;` — Command info for this instance, which is used to the filter to menu / toolbar builders. In the future, it also allows users to bind shortcuts to it.
- L95 _public function_ `explicit FFilterData(UCurveEditorFilterBase& InFilter UE_LIFETIMEBOUND, TSharedRef<FUICommandInfo> InCommand) : FilterInstance(InFilter) , Command(InCommand)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CURVEEDITOR_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace CurveEditor` (scope `UE`)
- L63 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FFilterDelegate, UCurveEditorFilterBase&, const TSharedRef<FUICommandInfo>&);`

### `Source/Editor/CurveEditor/Public/Filters/SCurveEditorFilterPanel.h` (Public)


#### class `SCurveEditorFilterPanel`  
`class SCurveEditorFilterPanel : public SCompoundWidget`  
_L21-58_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorFilterPanel)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor, UClass* DefaultFilterClass);`
- L30 _public prototype_ `void SetFilterClass(UClass* InClass);`
- L34 _public prototype_ `static TSharedPtr<SCurveEditorFilterPanel> OpenDialog(TSharedPtr<SWindow> RootWindow, TSharedRef<FCurveEditor> InHostCurveEditor, TSubclassOf<UCurveEditorFilterBase> DefaultFilterClass);` — Call this to request opening a window containing this panel.
- L37 _public prototype_ `static void CloseDialog();` — Closes the dialog if there is one open.
- L40 _public function_ `TSharedPtr<class IDetailsView> GetDetailsView() const` — The details view for filter class properties
- L43 _public member_ `FSimpleDelegate OnFilterClassChanged;` — Delegate for when the chosen filter class has changed
- L46 _protected prototype_ `FReply OnApplyClicked();`
- L47 _protected prototype_ `bool CanApplyFilter() const;`
- L48 _protected prototype_ `FText GetCurrentFilterText() const;`
- L51 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Weak pointer to the curve editor which created this filter.
- L54 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The Details View in our UI that we update each time they choose a class.
- L57 _private member_ `static TWeakPtr<SWindow> ExistingFilterWindow;` — Singleton for the pop-up window.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/IBufferedCurveModel.h` (Public)


#### class `IBufferedCurveModel`  
`class IBufferedCurveModel`  
_L16-69_
- desc: Represents a buffered curve which can be applied to a standard curve model
- L19 _public function_ `IBufferedCurveModel(TArray<FKeyPosition>&& InKeyPositions, TArray<FKeyAttributes>&& InKeyAttributes, const FString& InLongDisplayName, const double InValueMin, const double InValueMax) : KeyPositions(MoveTemp(InKeyPositions)) , KeyAttributes(MoveTemp(InKeyAttributes)) , LongDisplayName(InLongDisplayName) , ValueMin(InValueMin) , ValueMax(InValueMax)`
- L27 _public prototype_ `virtual ~IBufferedCurveModel() = default;`
- L30 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const = 0;` — draws the curve into an array of (input, output) pairs with a given screen space
- L37 _public prototype_ `virtual bool Evaluate(double InTime, double& OutValue) const = 0;` — @param InTime The time at which to evaluate the curve. @param OutValue The evaluated curve value at InTime, if this function returned true. @return Whether the curve was evaluated.
- L44 _public function_ `FORCEINLINE void GetKeyPositions(TArray<FKeyPosition>& OutKeyPositions) const` — Retrieve all key positions stored in this buffered curve @param OutKeyPositions         Array to receive key positions, one per index of InKeys
- L51 _public function_ `FORCEINLINE void GetKeyAttributes(TArray<FKeyAttributes>& OutKeyAttributes) const` — Retrieve all key attributes stored in this buffered curve @param OutAttributes         Array to receive key attributes, one per index of InKeys
- L56 _public function_ `FORCEINLINE FString GetLongDisplayName() const` — Returns the full/long display name of the curves. Buffered curves can only be applied to the original curve it was stored from.
- L59 _public function_ `FORCEINLINE double GetValueMin() const` — returns the lowest output value in curve space for this buffered curve
- L62 _public function_ `FORCEINLINE double GetValueMax() const` — returns the highest output value in curve space for this buffered curve
- L65 _protected member_ `TArray<FKeyPosition> KeyPositions;`
- L66 _protected member_ `TArray<FKeyAttributes> KeyAttributes;`
- L67 _protected member_ `FString LongDisplayName;`
- L68 _protected member_ `double ValueMin, ValueMax;`
- L68 _protected member_ `double ValueMin, ValueMax;`

### `Source/Editor/CurveEditor/Public/ICurveEditorBounds.h` (Public)


#### struct `ICurveEditorBounds`  
`struct ICurveEditorBounds`  
_L7-13_
- L9 _public prototype_ `virtual ~ICurveEditorBounds()= default;`
- L11 _public prototype_ `virtual void GetInputBounds(double& OutMin, double& OutMax) const = 0;`
- L12 _public prototype_ `virtual void SetInputBounds(double InMin, double InMax) = 0;`

#### struct `FStaticCurveEditorBounds`  
`struct FStaticCurveEditorBounds : ICurveEditorBounds`  
_L16-32_
- inherits: `ICurveEditorBounds`
- L18 _public member_ `double InputMin = 0.0;`
- L19 _public member_ `double InputMax = 1.0;`
- L21 _public function_ `virtual void GetInputBounds(double& OutMin, double& OutMax) const override final`
- L27 _public function_ `virtual void SetInputBounds(double InMin, double InMax) override final`

### `Source/Editor/CurveEditor/Public/ICurveEditorCurveCachePool.h` (Public)


#### class `UE::CurveEditor::ICurveEditorCurveCachePool`  
`class ICurveEditorCurveCachePool`  
_L12-17_
- L16 _public prototype_ `virtual void DrawCachedCurves(TWeakPtr<const FCurveEditor> WeakCurveEditor) = 0;` — Draws the cached curves. Called when all curves were drawn to the curve cache pool.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/ICurveEditorDragOperation.h` (Public)


#### class `ICurveEditorDragOperation`  
`class ICurveEditorDragOperation`  
_L25-118_
- desc: Interface for all drag operations in the curve editor
- L29 _public function_ `ICurveEditorDragOperation()`
- L32 _public prototype_ `virtual ~ICurveEditorDragOperation() = default;`
- L37 _public prototype_ `void MouseButtonDown(FVector2D InitialPosition, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Mouse button down
- L43 _public prototype_ `void MouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Mouse button up
- L48 _public prototype_ `void BeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent);` — Begin this drag operation with the specified initial and current positions
- L53 _public prototype_ `void Drag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent);` — Continue this drag operation with the specified initial and current positions
- L56 _public prototype_ `void FinishedPointerInput();` — Process any mouse input that this drag operation may have accumulated.
- L61 _public prototype_ `FReply MouseWheel(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent);` — Potentially Evaluate a MouseWheel event which occcured during this drag operation
- L66 _public prototype_ `void EndDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent);` — Finish this drag operation with the specified initial and current positions
- L71 _public prototype_ `void Paint(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId);` — Paint this drag operation onto the specified layer
- L76 _public prototype_ `void CancelDrag();` — Cancel this drag operation
- L81 _protected function_ `virtual void OnMouseButtonDown(FVector2D InitialPosition, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — Implementation method for derived types to handle mouse down
- L85 _protected function_ `virtual void OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — Implementation method for derived types to handle mouse up
- L89 _protected function_ `virtual void OnBeginDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent)` — Implementation method for derived types to begin a drag
- L93 _protected function_ `virtual void OnDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent)` — Implementation method for derived types to continue a drag
- L97 _protected function_ `virtual void OnFinishedPointerInput()` — Implementation method for derived types to process any accumulated drags.
- L101 _protected function_ `virtual FReply OnMouseWheel(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent)` — Implementation method for derived types to evaluate a mousewheel event
- L107 _protected function_ `virtual void OnEndDrag(FVector2D InitialPosition, FVector2D CurrentPosition, const FPointerEvent& MouseEvent)` — Implementation method for derived types to finish a drag
- L111 _protected function_ `virtual void OnPaint(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId)` — Implementation method for derived types to paint this drag
- L115 _protected function_ `virtual void OnCancelDrag()` — Implementation method for derived types to cancel a drag

#### class `ICurveEditorKeyDragOperation`  
`class ICurveEditorKeyDragOperation : public ICurveEditorDragOperation`  
_L123-138_
- inherits: `ICurveEditorDragOperation`
- desc: Interface for all key drag operations in the curve editor
- L132 _public prototype_ `void Initialize(FCurveEditor* InCurveEditor, const TOptional<FCurvePointHandle>& CardinalPoint);` — Initialize this drag operation using the specified curve editor pointer and an optional cardinal point @param InCurveEditor       Curve editor pointer. Guaranteed to persist for the lifetime of this drag. @param CardinalPoint       The point that should be considered the origin of this drag.
- L137 _protected function_ `virtual void OnInitialize(FCurveEditor* InCurveEditor, const TOptional<FCurvePointHandle>& CardinalPoint)` — Implementation method for derived types to initialize a drag

#### struct `FCurveEditorDelayedDrag`  
`struct FCurveEditorDelayedDrag : FDelayedDrag`  
_L143-182_
- inherits: `FDelayedDrag`
- desc: Utility struct used to facilitate a delayed drag operation with an implementation interface
- L146 _public member_ `TUniquePtr<ICurveEditorDragOperation> DragImpl;` — The drag implementation to use once the drag has started
- L156 _public member_ `TUniquePtr<FScopedTransaction> Transaction;` — Transaction associated with the operation. Only created for certain operations as not all operations need to transact. Depending on the operation, this transaction may contain more changes than those created by the drag operation. For example, when clicking a curve with middle mouse button, we may insert a key first and then start moving that key using the drag operation; the transaction would contain the key insertion and selection change and the drag operation may append a change for moving the inserted key. This is the reason that the ICurveEditorDragOperation is not responsible for creating the FScopedTransaction.
- L161 _public function_ `FCurveEditorDelayedDrag(FVector2D InInitialPosition, FKey InEffectiveKey) : FDelayedDrag(InInitialPosition, InEffectiveKey)` — Start a delayed drag operation at the specified position and effective key
- L168 _public function_ `void Cancel()` — Cancels the drag operation and transaction.

### `Source/Editor/CurveEditor/Public/ICurveEditorExtension.h` (Public)


#### class `ICurveEditorExtension`  
`class ICurveEditorExtension`  
_L9-27_
- L12 _public prototype_ `virtual ~ICurveEditorExtension() = default;`
- L19 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> CommandBindings) = 0;` — Allows the editors to bind commands. @param CommandBindings The existing command bindings to map to.
- L26 _public function_ `virtual TSharedPtr<FExtender> MakeToolbarExtender(const TSharedRef<FUICommandList>& InCommandList)` — Allows the editors to extend the toolbar. @param InCommandList The existing command bindings to map to.

### `Source/Editor/CurveEditor/Public/ICurveEditorModule.h` (Public)


#### struct `FCurveEditorInitParams`  
`struct FCurveEditorInitParams`  
_L34-51_
- desc: Curve Editor initialization parameters.
- L36 _public function_ `FCurveEditorInitParams()`
- L40 _public member_ `TArray<TSharedRef<ICurveEditorExtension>> AdditionalEditorExtensions;` — Extensions you want to inject for this curve editor.
- L43 _public member_ `TAttribute<const FCurveEditorZoomScaleConfig*> ZoomScalingAttr;` — Optional. If set, defines multipliers for zooming.
- L50 _public member_ `UE::CurveEditor::FResolveCurveModelDelegate ResolveCurveModelDelegate;` — Internally used for editing FCurveModels after they've been removed FCurveEditor::CurveData (e.g. once they're no longer visible). Important for applying undo / redo commands on curves that are not visible when the user issues the undo / redo operation. You can skip providing this if you never call FCurveEditor::RemoveCurve.

#### class `ICurveEditorModule`  
`class ICurveEditorModule : public IModuleInterface`  
_L56-103_
- inherits: `IModuleInterface`
- desc: Interface for the Curve Editor module.
- L60 _public function_ `static ICurveEditorModule& Get()`
- L64 _public function_ `static bool IsAvailable()`
- L69 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FCurveEditorMenuExtender, const TSharedRef<FUICommandList>);`
- L70 _public prototype_ `virtual ~ICurveEditorModule() = default;`
- L72 _public prototype_ `virtual FDelegateHandle RegisterEditorExtension(FOnCreateCurveEditorExtension InOnCreateCurveEditorExtension) = 0;`
- L73 _public prototype_ `virtual void UnregisterEditorExtension(FDelegateHandle InHandle) = 0;`
- L75 _public prototype_ `virtual FDelegateHandle RegisterToolExtension(FOnCreateCurveEditorToolExtension InOnCreateCurveEditorToolExtension) = 0;`
- L76 _public prototype_ `virtual void UnregisterToolExtension(FDelegateHandle InHandle) = 0;`
- L85 _public prototype_ `virtual ECurveEditorViewID RegisterView(FOnCreateCurveEditorView InCreateViewDelegate) = 0;` — Register a new view factory function that can be used on the curve editor when relevant curves are found @note: A maximum of 64 registered view types are supported. View type IDs are not recycled. @param InCreateViewDelegate (required) A bound delegate that creates a new instance of the view widget. Delegate signature is TSharedRef<SCurveEditorView> Function(TWeakPtr<FCurveEditor>); @return A new custom view ID that identifies the registered view type. Any curve models that wish to support this view must |= this enum to its FCurveModel::SupportedViews;
- L92 _public prototype_ `virtual void UnregisterView(ECurveEditorViewID InViewID) = 0;` — Unregister a previously registered view type @param InViewID The view ID obtained from calling RegisterCustomView. Must be >= ECurveEditorViewID::CUSTOM_START
- L94 _public prototype_ `virtual TArray<FCurveEditorMenuExtender>& GetAllToolBarMenuExtenders() = 0;`
- L96 _public prototype_ `virtual TArrayView<const FOnCreateCurveEditorExtension> GetEditorExtensions() const = 0;`
- L97 _public prototype_ `virtual TArrayView<const FOnCreateCurveEditorToolExtension> GetToolExtensions() const = 0;`
- L102 _public prototype_ `virtual TSharedPtr<UE::CurveEditor::FPromotedFilterContainer> GetGlobalToolbarPromotedFilters() const = 0;` — @return The global setting of which filters should be promoted to the toolbar in the curve editor.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace CurveEditor` (scope `UE`)
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<ICurveEditorExtension>, FOnCreateCurveEditorExtension, TWeakPtr<FCurveEditor>);` — A delegate which will create an extension for the Curve Editor. Used for adding new buttons and functionality to the editor as a whole.
- L23 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<ICurveEditorExtension>, FOnCreateCurveEditorExtension, TWeakPtr<FCurveEditor>);` — A delegate which will create an extension for the Curve Editor. Used for adding new buttons and functionality to the editor as a whole.
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TUniquePtr<ICurveEditorToolExtension>, FOnCreateCurveEditorToolExtension, TWeakPtr<FCurveEditor>);` — A delegate which will create a tool extension for the Curve Editor. Used for registering new tools which can only have one active at once.
- L26 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TUniquePtr<ICurveEditorToolExtension>, FOnCreateCurveEditorToolExtension, TWeakPtr<FCurveEditor>);` — A delegate which will create a tool extension for the Curve Editor. Used for registering new tools which can only have one active at once.
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SCurveEditorView>, FOnCreateCurveEditorView, TWeakPtr<FCurveEditor>);` — A delegate used for creating a new curve editor view
- L29 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SCurveEditorView>, FOnCreateCurveEditorView, TWeakPtr<FCurveEditor>);` — A delegate used for creating a new curve editor view
- L69 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FCurveEditorMenuExtender, const TSharedRef<FUICommandList>);`

### `Source/Editor/CurveEditor/Public/ICurveEditorToolExtension.h` (Public)


#### struct `FCurveEditorToolID`  
`struct FCurveEditorToolID`  
_L23-73_
- desc: A unique identifier for a tool in the curve editor
- L28 _public function_ `static FCurveEditorToolID Unique()` — Generate a new tool ID
- L37 _public function_ `static FCurveEditorToolID Unset()`
- L69 _private function_ `FCurveEditorToolID()`
- L72 _private member_ `uint32 ID;` — Internal serial ID

#### class `ICurveEditorToolExtension`  
`class ICurveEditorToolExtension`  
_L83-150_
- desc: You can extend the Curve Editor toolset by implementing this interface. The Curve Editor guarantees that only one tool will be active at any given time. A tool needs to specify if they handled certain mouse events so that these events can be bubbled to the rest of the Curve Editor to allow common functionality of selecting/deselecting keys, panning, etc.
- L86 _public function_ `ICurveEditorToolExtension() : ToolID(FCurveEditorToolID::Unset())`
- L91 _public prototype_ `virtual ~ICurveEditorToolExtension() = default;`
- L94 _public prototype_ `virtual void OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const = 0;` — Effectively SWidget Interface
- L95 _public function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)`
- L96 _public function_ `virtual FReply OnKeyDown(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)`
- L97 _public function_ `virtual FReply OnKeyUp(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)`
- L98 _public function_ `virtual FReply OnMouseButtonDown(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L99 _public function_ `virtual FReply OnMouseButtonUp(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L100 _public function_ `virtual FReply OnMouseMove(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L101 _public function_ `virtual FReply OnMouseButtonDoubleClick(TSharedRef<SWidget> OwningWidget, const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)`
- L102 _public function_ `virtual void OnFinishedPointerInput()`
- L103 _public function_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent)`
- L104 _public function_ `virtual TSharedPtr<FStructOnScope> GetToolOptions() const`
- L105 _public function_ `virtual void OnToolOptionsUpdated(const FPropertyChangedEvent& PropertyChangedEvent)`
- L112 _public prototype_ `virtual void OnToolActivated() = 0;` — This is called when the tool is activated by switching from another tool. The current tool (if any) will have OnToolDeactivated called first before the new tool has OnToolActivated called.
- L118 _public prototype_ `virtual void OnToolDeactivated() = 0;` — This is called when the tool is deactivated by switching to another tool. This will be called before the new tool has OnToolActivated called.
- L125 _public function_ `virtual void BindCommands(TSharedRef<FUICommandList> CommandBindings)` — Allows the tool to bind commands. @param CommandBindings The existing command bindings to map to.
- L134 _public function_ `virtual void SetToolID(const FCurveEditorToolID InToolID)`
- L140 _public prototype_ `virtual FText GetLabel() const = 0;` — @return Label for this tool. Displayed by toolbar combo button.
- L142 _public prototype_ `virtual FText GetDescription() const = 0;` — @return Description for this tool. Displayed by toolbar combo button.
- L144 _public prototype_ `virtual FSlateIcon GetIcon() const = 0;` — @return Icon for this tool. Displayed by toolbar combo button.
- L146 _public member_ `FOnOptionsRefresh OnOptionsRefreshDelegate;`
- L149 _protected member_ `FCurveEditorToolID ToolID;`

#### Free symbols / members of external scopes

- L47 _function_ `FORCEINLINE friend bool operator==(FCurveEditorToolID A, FCurveEditorToolID B)` — Check two IDs for equality
- L55 _function_ `FORCEINLINE friend bool operator!=(FCurveEditorToolID A, FCurveEditorToolID B)` — Check two IDs for inequality
- L63 _function_ `FORCEINLINE friend uint32 GetTypeHash(FCurveEditorToolID In)` — Hash a tool ID
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOptionsRefresh);`
- L75 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOptionsRefresh);`

### `Source/Editor/CurveEditor/Public/InvertedCurveModel.h` (Public)


#### class `UE::CurveEditor::TInvertedCurveModel`  
`template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> class TInvertedCurveModel : public TBase`  
_L11-31_
- inherits: `TBase`
- L16 _public prototype_ `template<typename... TArg> explicit TInvertedCurveModel(TArg&&... Arg);`
- L18 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;`
- L19 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override;`
- L20 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles = nullptr) override;`
- L21 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L22 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L23 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L24 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L25 _public prototype_ `virtual bool Evaluate(double InTime, double& OutValue) const override;`
- L26 _public prototype_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L27 _public prototype_ `virtual void GetKeyAttributesIncludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L28 _public prototype_ `virtual void GetKeyAttributesExcludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L29 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L30 _public prototype_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const override;`
- L115 _function_ `template <typename TBase> requires std::is_base_of_v<FCurveModel, TBase> template <typename ... TArg> TInvertedCurveModel<TBase>::TInvertedCurveModel(TArg&&... Arg) : TBase(Forward<TArg>(Arg)...)`
- L120 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::DrawCurve( const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints ) const`
- L132 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const`
- L140 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::AddKeys( TArrayView<const FKeyPosition> InPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles )`
- L152 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const`
- L159 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::SetKeyPositions( TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType )`
- L169 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const`
- L175 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::GetValueRange(double& MinValue, double& MaxValue) const`
- L184 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> bool TInvertedCurveModel<TBase>::Evaluate(double InTime, double& OutValue) const`
- L195 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const`
- L202 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::GetKeyAttributesIncludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const`
- L209 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::GetKeyAttributesExcludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const`
- L216 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> void TInvertedCurveModel<TBase>::SetKeyAttributes( TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType )`
- L226 _function_ `template<typename TBase> requires std::is_base_of_v<FCurveModel, TBase> TUniquePtr<IBufferedCurveModel> TInvertedCurveModel<TBase>::CreateBufferedCurveCopy() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditor` (scope `UE`)
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace CurveEditor` (scope `UE`)
- L36 _namespace_ `namespace Private` (scope `UE::CurveEditor`)
- L38 _function_ `static FKeyPosition InvertKeyPosition(const FKeyPosition& KeyPosition)` (scope `UE::CurveEditor::Private`)
- L44 _function_ `template <typename InT, typename OutT> static void InvertKeyPositions(const InT& Input, OutT&& Output)` (scope `UE::CurveEditor::Private`)
- L47 _function_ `` (scope `UE::CurveEditor::Private::InvertKeyPositions`)
- L52 _function_ `static void InvertKeyPositions(TArrayView<FKeyPosition> Output)` (scope `UE::CurveEditor::Private`)
- L60 _function_ `static float InvertTangent(float Tangent)` (scope `UE::CurveEditor::Private`)
- L66 _function_ `static FKeyAttributes InvertKeyAttributes(FKeyAttributes Attributes)` (scope `UE::CurveEditor::Private`)
- L80 _function_ `template <typename InT, typename OutT> static void InvertKeyAttributes(const InT& Input, OutT&& Output)` (scope `UE::CurveEditor::Private`)
- L83 _function_ `` (scope `UE::CurveEditor::Private::InvertKeyAttributes`)
- L88 _function_ `static void InvertKeyAttributes(TArrayView<FKeyAttributes> Output)` (scope `UE::CurveEditor::Private`)
- L96 _function_ `static TArray<FKeyPosition> CopyAndInvertKeyPositionsFromBuffer(const IBufferedCurveModel& RealBuffer)` (scope `UE::CurveEditor::Private`)
- L104 _function_ `static TArray<FKeyAttributes> CopyAndInvertKeyAttributesFromBuffer(const IBufferedCurveModel& RealBuffer)` (scope `UE::CurveEditor::Private`)

### `Source/Editor/CurveEditor/Public/KeyBarCurveModel.h` (Public)


#### class `FKeyBarCurveModel`  
`class FKeyBarCurveModel: public FCurveModel`  
_L31-78_
- inherits: `FCurveModel`
- desc: Class that provides functionality to represents keys as continuous ranges.
- L35 _public prototype_ `FKeyBarCurveModel();`
- L36 _public prototype_ `~FKeyBarCurveModel();`
- L38 _public function_ `virtual const void* GetCurve() const override`
- L39 _public function_ `virtual void Modify() override`
- L40 _public function_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override`
- L41 _public function_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override`
- L42 _public function_ `virtual void AddKeys(TArrayView<const FKeyPosition> InPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles = nullptr) override`
- L43 _public function_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override`
- L44 _public function_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override`
- L45 _public function_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions,const EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override`
- L46 _public function_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override`
- L47 _public function_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override`
- L48 _public function_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override`
- L49 _public function_ `virtual int32 GetNumKeys() const override`
- L50 _public function_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override`
- L51 _public function_ `virtual bool Evaluate(double InTime, double& OutValue) const override`
- L57 _public function_ `virtual void BuildContextMenu(const FCurveEditor& CurveEditor, FMenuBuilder& MenuBuilder, TOptional<FCurvePointHandle> ClickedPoint)`
- L73 _public function_ `virtual TArray<FKeyBarCurveModel::FBarRange> FindRanges()` — Find all of the ranges in this model. This should return an increasing set of ranges.

#### struct `FKeyBarCurveModel::FBarRange`  
`struct FBarRange`  
_L62-69_
- desc: Bar Ranges for the Keys
- L65 _public member_ `bool bRangeIsInfinite = true;` — Spaces have ifinite ranges, Constraints don't
- L66 _public member_ `TRange<double> Range;`
- L67 _public member_ `FName Name;`
- L68 _public member_ `FLinearColor Color;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Misc/CurveChangeListener.h` (Public)


#### class `UE::CurveEditor::FCurveChangeListener`  
`class FCurveChangeListener : public FNoncopyable`  
_L18-49_
- inherits: `FNoncopyable`
- desc: Listens to changes made to curves and cleans the subscriptions on destruction.
- L22 _public prototype_ `explicit FCurveChangeListener(const TSharedRef<FCurveEditor>& InCurveEditor, TArray<FCurveModelID> InCurvesToListenTo);`
- L23 _public prototype_ `~FCurveChangeListener();`
- L26 _public prototype_ `void ResubscribeTo(TArray<FCurveModelID> InNewCurvesToSubscribeTo);` — Changes the curves to subscribe to.
- L29 _public prototype_ `static FCurveChangeListener MakeForAllCurves(const TSharedRef<FCurveEditor>& InCurveEditor);` — @return Change listener that subscribes to all FCurveModels on InCurveEditor.
- L31 _public prototype_ `static FCurveChangeListener MakeForSelectedCurves(const TSharedRef<FCurveEditor>& InCurveEditor);` — @return Change listener that subscribed only to the FCurveModels CURRENTLY selected.
- L33 _public function_ `FSimpleMulticastDelegate& OnCurveModified()`
- L38 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Used to unsubscribe on destruction.
- L40 _private member_ `TArray<FCurveModelID> SubscribedToCurves;` — The curves we subscribed to
- L43 _private member_ `FSimpleMulticastDelegate OnCurveModifiedDelegate;` — Invokes when any of the listeners is changed.
- L45 _private function_ `void HandleCurveModified() const`
- L47 _private prototype_ `void SubscribeToCurves();`
- L48 _private prototype_ `void UnsubscribeFromCurves();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Misc/InputState.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CURVEEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CurveEditor` (scope `UE`)
- L16 _namespace_ `namespace InputState` (scope `UE::CurveEditor`)
- L20 _prototype_ `void Initialize();` (scope `UE::CurveEditor::InputState`) — Initializes the shared input state processor used to track scrub chords across Slate widgets.
- L23 _prototype_ `void Shutdown();` (scope `UE::CurveEditor::InputState`) — Shuts down the shared input state processor and clears any tracked scrub state.
- L31 _prototype_ `bool IsChordPressed(const FInputChord& InChord, const FModifierKeysState& InModifierKeys);` (scope `UE::CurveEditor::InputState`) — Returns whether the specified input chord is currently pressed. @param InChord The chord to test. @param InModifierKeys The modifier key state to evaluate against the chord. @return True if the chord key is pressed and its modifiers match, otherwise false.
- L38 _prototype_ `bool IsCommandPressed(const TSharedPtr<FUICommandInfo>& InCommandInfo);` (scope `UE::CurveEditor::InputState`) — Returns whether any active chord for the specified command is currently pressed. @param InCommandInfo The command whose active chords should be tested. @return True if an active chord for the command is currently pressed, otherwise false.
- L46 _prototype_ `bool IsCommandPressed(const TSharedPtr<FUICommandInfo>& InCommandInfo, const FKeyEvent& InKeyEvent);` (scope `UE::CurveEditor::InputState`) — Returns whether the specified key event matches any active chord for the command. @param InCommandInfo The command whose active chords should be tested. @param InKeyEvent The key event to evaluate against the command's active chords. @return True if the key event matches an active chord for the command, otherwise false.
- L54 _prototype_ `bool IsScrubTimeCommandPressed(const TSharedPtr<FUICommandInfo>& InCommandInfo);` (scope `UE::CurveEditor::InputState`) — Returns whether scrub time should currently be treated as active for the specified command. This includes both the live command chord state and any latched scrub state tracked across widget handoff. @param InCommandInfo The scrub command whose active chords should be tested. @return True if scrub time is currently active for the command, otherwise false.
- L62 _prototype_ `void SetCommandPressed(const TSharedPtr<FUICommandInfo>& InCommandInfo , const FKey& InKey, const bool bInPressed);` (scope `UE::CurveEditor::InputState`) — Explicitly updates the tracked pressed state for any active command chord that uses the specified key. @param InCommandInfo The command whose active chords should be tested. @param InKey The key whose pressed state should be updated. @param bInPressed True if the key is now pressed, false if it is released.
- L71 _prototype_ `void SetCommandPressed(const TSharedPtr<FUICommandInfo>& InCommandInfo , const FModifierKeysState& InModifierKeys, const bool bInPressed);` (scope `UE::CurveEditor::InputState`) — Explicitly updates the tracked pressed state for any active command chord whose modifiers match the provided modifier state. @param InCommandInfo The command whose active chords should be tested. @param InModifierKeys The modifier key state to evaluate against the command's active chords. @param bInPressed True if matching chord keys should be treated as pressed, false otherwise.
- L80 _prototype_ `void SetCommandPressed(const TSharedPtr<FUICommandInfo>& InCommandInfo , const FViewport* InViewport, const bool bInPressed);` (scope `UE::CurveEditor::InputState`) — Explicitly updates the tracked pressed state for any active command chord whose key is currently down in the specified viewport. @param InCommandInfo The command whose active chords should be tested. @param InViewport The viewport whose key state should be queried. @param bInPressed True if matching chord keys should be treated as pressed, false otherwise.
- L88 _prototype_ `void SetKeyPressed(const FKey& InKey, const bool bInPressed);` (scope `UE::CurveEditor::InputState`) — Explicitly updates the tracked pressed state for a non-modifier key. @param InKey The key whose pressed state should be updated. @param bInPressed True if the key is now pressed, false if it is released.
- L95 _prototype_ `void SetScrubTimeKeyPressed(const FKey& InKey, const bool bInPressed);` (scope `UE::CurveEditor::InputState`) — Explicitly updates the latched scrub-time state for a key participating in a scrub interaction. @param InKey The key whose scrub-time pressed state should be updated. @param bInPressed True if the key should be considered active for scrub time, false otherwise.
- L101 _prototype_ `bool IsScrubTimeActive();` (scope `UE::CurveEditor::InputState`) — Returns whether scrub time is currently latched as active. @return True if scrub time is active, otherwise false.

### `Source/Editor/CurveEditor/Public/Misc/KeyPasteArgs.h` (Public)


#### enum `UE::CurveEditor::ECurveEditorPasteMode`  
`enum class ECurveEditorPasteMode : uint8`  
_L15-21_
- desc: Defines the merging behaviour of the paste operation.
- L18 _public enumerator_ `OverwriteRange` — Pastes the keys from the clipboard overwriting any key in destination track between the first and last pasted keys
- L20 _public enumerator_ `Merge` — Existing keys are mostly retained. Existing keys are only replaced by pasted keys that have the same X value.

#### enum `UE::CurveEditor::ECurveEditorPasteFlags`  
`enum class ECurveEditorPasteFlags : uint8`  
_L24-34_
- desc: Enhances the paste operation
- L26 _public enumerator_ `None`
- L29 _public enumerator_ `SetSelection = 1 << 0` — Set the selection to the pasted keys.
- L31 _public enumerator_ `Relative = 1 << 1` — Pastes the keys from the clipboard aligning them to the nearest key to the left of the scrubber
- L33 _public enumerator_ `Default = SetSelection`

#### struct `UE::CurveEditor::FKeyPasteArgs`  
`struct FKeyPasteArgs`  
_L38-47_
- desc: Arguments for pasting keys in FCurveEditor.
- L41 _public member_ `TSet<FCurveModelID> CurveModelIds;` — Only the curve model IDs specified in this set. If empty, paste all in the clipboard.
- L42 _public member_ `ECurveEditorPasteMode Mode = ECurveEditorPasteMode::OverwriteRange;`
- L43 _public member_ `ECurveEditorPasteFlags Flags = ECurveEditorPasteFlags::Default;`
- L46 _public member_ `FText OverrideTransactionName = NSLOCTEXT("CurveEditor` — The name of the transaction

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L35 _prototype_ `ENUM_CLASS_FLAGS(ECurveEditorPasteFlags);` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Public/Misc/Mirror/MirrorUtils.h` (Public)


#### struct `UE::CurveEditor::FCurveBounds`  
`struct FCurveBounds`  
_L27-35_
- L30 _public member_ `double Min;` — All keys are above this.
- L32 _public member_ `double Max;` — All keys are below this
- L34 _public function_ `double Delta() const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditor` (scope `UE`)
- L23 _prototype_ `template<typename TCallback, typename TMapAllocator = FDefaultSetAllocator, typename TArrayAllocator = FDefaultAllocator> requires std::is_invocable_v<TCallback, TConstArrayView<FKeyHandle>, const FCurveModelID&, double , double , double > void MirrorOnMidpoint( const TMap<FCurveModelID, TArray<FKeyHandle, TArrayAllocator>, TMapAllocator>& InKeysToMirror, FCurveEditor& InCurveEditor, TCallback&& InProcess );` (scope `UE::CurveEditor`) — Finds the mid-point of every curve's passed in key handles and mirrors all points on the imaginary line going through it. @param InKeysToMirror Curve to the keys on it to mirror @param InCurveEditor The editor to which the keys belong
- L37 _prototype_ `FCurveBounds FindMinMaxHeight( TConstArrayView<FKeyHandle> InKeys, const FCurveModel& InCurveModel );` (scope `UE::CurveEditor`) — @return Find the min and max height values.
- L54 _prototype_ `void MirrorKeyPositions( TConstArrayView<FKeyHandle> InKeysToMirror, const FCurveModelID& InCurveId, double InBottomHeight, double InTopHeight, double InMirrorHeight, FCurveEditor& InCurveEditor );` (scope `UE::CurveEditor`) — Recomputes the key position OutputValues as if the points were mirrored accross an imaginary x-axis aligned mirror edge. The mirror Edge is positioned between the top and bottom edge. @note This function only recalculates key positions. Tangents must be set separately. @param InKeysToMirror Keys located between BottomHeight and TopHeight, whose tangents will be recomputed. @param InCurveId The curve the keys belong to @param InBottomHeight The height of the bottom edge. @param InTopHeight The height of the top edge. @param InMirrorHeight The height of the imaginary x-axis-aligned mirror edge across which tangents are mirrored. @param InCurveEditor Reference to the curve editor used to set key attributes.
- L73 _prototype_ `void MirrorTangents( TConstArrayView<FKeyHandle> InKeysToMirror, const FCurveModelID& InCurveId, double InBottomHeight, double InTopHeight, double InMirrorHeight, FCurveEditor& InCurveEditor );` (scope `UE::CurveEditor`) — Recomputes the tangents of specified keys as if the points were mirrored across an imaginary x-axis aligned mirror edge. The mirror edge is positioned between the top and bottom edges. @note This function only recalculates tangents. Key positions must be set separately. @param InKeysToMirror Keys located between BottomHeight and TopHeight, whose tangents will be recomputed. @param InCurveId The curve the keys belong to @param InBottomHeight The height of the bottom edge. @param InTopHeight The height of the top edge. @param InMirrorHeight The height of the imaginary x-axis-aligned mirror edge across which tangents are mirrored. @param InCurveEditor Reference to the curve editor used to set key attributes.
- L80 _namespace_ `namespace UE`
- L80 _namespace_ `namespace CurveEditor` (scope `UE`)
- L84 _function_ `template<typename TCallback, typename TMapAllocator, typename TArrayAllocator> requires std::is_invocable_v<TCallback, TConstArrayView<FKeyHandle>, const FCurveModelID&, double , double , double > void MirrorOnMidpoint( const TMap<FCurveModelID, TArray<FKeyHandle, TArrayAllocator>, TMapAllocator>& InKeysToMirror, FCurveEditor& InCurveEditor, TCallback&& InProcess )` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Public/Misc/Mirror/MultiCurveMirrorUtils.h` (Public)


#### struct `UE::CurveEditor::FMirrorableTangentInfo`  
`struct FMirrorableTangentInfo`  
_L14-30_
- L17 _public member_ `TArray<FKeyHandle> MirrorableKeys;` — Keys that can be mirrored, i.e. have RCTM_User or RCTM_Break mode.
- L19 _public member_ `TArray<FKeyAttributes> InitialAttributes;` — The attributes corresponding to each of MirrorableKeys.
- L24 _public member_ `TArray<FVector2D> Tangents;` — The tangents corresponding to each of MirrorableKeys. X is arrive tangent, Y is leave tangent. Copied values of the corresponding InitialAttributes indices. If there is no leave tangent, Y is 0.
- L26 _public member_ `TArray<double> KeyHeights;` — The FKeyPosition::OutputValue corresponding to each of MirrableKeys.
- L28 _public function_ `bool HasData() const`
- L29 _public function_ `operator bool() const`

#### struct `UE::CurveEditor::FCurveTangentMirrorData`  
`struct FCurveTangentMirrorData`  
_L38-67_
- desc: Holds data about mirroring keys in a single curve.
- L44 _public member_ `const TUniformMirrorSolver<FVector2D> TangentSolver;` — This will mirror the tangents of KeyHandles. The X component corresponds to ArriveTangent and Y to LeaveTangent. TMirrorSolver::InitialValues and TMirrorSolver::InitialKeyHeights correspond to KeyHandles.
- L46 _public member_ `const TArray<FKeyHandle> KeyHandles;` — The keys to interpolate. Only tangents that are user specified are referenced here.
- L48 _public member_ `TArray<FKeyAttributes> AttributesToSet;` — Same length as KeyHandles.
- L50 _public function_ `explicit FCurveTangentMirrorData(TUniformMirrorSolver<FVector2D> InTangentSolver, TArray<FKeyHandle> InKeys, TArray<FKeyAttributes> InInitialAttributes) : TangentSolver(MoveTemp(InTangentSolver)) , KeyHandles(MoveTemp(InKeys)) , AttributesToSet(MoveTemp(InInitialAttributes))`
- L59 _public function_ `explicit FCurveTangentMirrorData( FMirrorableTangentInfo InInfo, double InStartHeight, double InMirrorMidpoint, const FVector2D& InMidpointOffset = FVector2D::ZeroVector ) : FCurveTangentMirrorData( TUniformMirrorSolver<FVector2D>(InStartHeight, InMirrorMidpoint, MoveTemp(InInfo.Tangents), MoveTemp(InInfo.KeyHeights), InMidpointOffset), MoveTemp(InInfo.MirrorableKeys), MoveTemp(InInfo.InitialAttributes) )`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)
- L33 _prototype_ `FMirrorableTangentInfo FilterMirrorableTangents( const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys );` (scope `UE::CurveEditor`) — @return Information you can use to FCurveTangentMirrorData.
- L71 _prototype_ `void RecomputeMirroringParallel( const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, FCurveTangentMirrorData& InCurveData, double InMirrorValue );` (scope `UE::CurveEditor`) — Mirrors the tangents stores in InCurveData.
- L79 _prototype_ `template<typename TCallback> requires std::is_invocable_r_v<FVector2D, TCallback, int32, const FVector2D&> void RecomputeMirroringParallel( const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, FCurveTangentMirrorData& InCurveData, double InMirrorValue, TCallback&& InPostProcessTangents );` (scope `UE::CurveEditor`) — Mirrors the tangents stores in InCurveData. This version accepts a callback for post-processing, which is useful for e.g. applying a falloff to the interpolated values.
- L85 _namespace_ `namespace UE`
- L85 _namespace_ `namespace CurveEditor` (scope `UE`)
- L87 _function_ `inline void RecomputeMirroringParallel( const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, FCurveTangentMirrorData& InCurveData, double InMirrorValue )` (scope `UE::CurveEditor`)
- L93 _function_ `` (scope `UE::CurveEditor::RecomputeMirroringParallel`)
- L100 _function_ `template<typename TCallback> requires std::is_invocable_r_v<FVector2D, TCallback, int32 , const FVector2D& > void RecomputeMirroringParallel( const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, FCurveTangentMirrorData& InCurveData, double InMirrorValue, TCallback&& InPostProcessTangents )` (scope `UE::CurveEditor`) — Mirrors the tangents stores in InCurveData.

### `Source/Editor/CurveEditor/Public/Misc/Mirror/PositionMirrorSolver.h` (Public)


#### class `UE::CurveEditor::FPositionMirrorSolver`  
`class FPositionMirrorSolver`  
_L34-92_
- desc: This class facilitates the movement of a dragged edge and recalculates the key heights for all specified keys. The heights are linearly interpolated, ensuring that if the dragged edge crosses to the opposite side of the mirror edge, the keys will flip to the other side. Inputs: - Height of the dragged edge aligned to the x-axis - Height of the x-axis-aligned mirror edge - Keys originally located between the dragged and mirror edges Example: Given a grid with a single key at a height 100, moving the top edge: - An equal distance past the bottom edge will result in a height of -100 for the key. - Halfway between the starting position and the bottom edge will result in a height of 50 for the key. @note This class only recalculates key positions. To adjust the tangents of the keys use e.g. FTangentMirrorSolver.
- L46 _public prototype_ `explicit FPositionMirrorSolver( FCurveEditor& InCurveEditor UE_LIFETIMEBOUND, double InStartY, double InMiddlePointY );` — InStartY and InMiddlePointY define two imaginary, x-axis aligned lines. All keys added must be between or on these two lines for the mirroring to work as expected. @param InCurveEditor Used to get and set tangent values @param InStartY The height of the line that is moved. It determines how the tangents are interpolated. @param InMiddlePointY The height of the line on which the points are moved.
- L62 _public prototype_ `bool AddKeyPositions(const FCurveModelID& InCurveId, TArray<FKeyHandle> InKeys, TArray<FKeyPosition> InPositions = {});` — Adds key positions that are to be mirrored. InStartY and InMiddlePointY define two imaginary, x-axis aligned lines. All keys must be between or on these two lines for the mirroring to work as expected. @param InCurveId The curve that all keys lie on @param InKeys The keys whose tangents to recompute @param InPositions The positions of the keys, if you have them already (optimization). If not, pass in empty and the key positions are determined. @return Whether any of the keys can be interpolated (only user specified tangents can be interpolated).
- L65 _public prototype_ `void OnMoveEdge(double InDraggedEdgeHeight);` — Recomputes the tangents angles and updates the key attributes.
- L70 _private member_ `FCurveEditor& CurveEditor;` — Used to set tangents angles.
- L73 _private member_ `const double StartY;` — Height of the dragged line.
- L75 _private member_ `const double MiddlePointY;` — Height of the mirroring line.
- L91 _private member_ `TMap<FCurveModelID, FCachedCurveData> AllCurveData;` — This memory is reuse across OnMoveEdge to hold the updated tangents. Caching the memory speeds up the recomputation.

#### struct `UE::CurveEditor::FPositionMirrorSolver::FCachedCurveData`  
`struct FCachedCurveData`  
_L77-89_
- L79 _public member_ `const TUniformMirrorSolver<double> TangentSolver;`
- L81 _public member_ `const TArray<FKeyHandle> KeyHandles;`
- L82 _public member_ `TArray<FKeyPosition> PositionsToSet;`
- L84 _public function_ `explicit FCachedCurveData(TUniformMirrorSolver<double> InTangentSolver, TArray<FKeyHandle> InKeys, TArray<FKeyPosition> InPositions) : TangentSolver(MoveTemp(InTangentSolver)) , KeyHandles(MoveTemp(InKeys)) , PositionsToSet(MoveTemp(InPositions))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Misc/Mirror/SingleKeyMirrorData.h` (Public)


#### enum `UE::CurveEditor::ESide`  
`enum class ESide`  
_L15-15_
- L15 _public enumerator_ `enum class ESide { Left, Right }; /** * Information about a center key and its neighbor's heights. * @see FTangentSingleKeyFlattener */ struct FKeyNeighborData {`
- L15 _public enumerator_ `enum class ESide { Left, Right }; /** * Information about a center key and its neighbor's heights. * @see FTangentSingleKeyFlattener */ struct FKeyNeighborData {`

#### struct `UE::CurveEditor::FKeyNeighborData`  
`struct FKeyNeighborData`  
_L21-36_
- desc: Information about a center key and its neighbor's heights. @see FTangentSingleKeyFlattener
- L24 _public member_ `double CenterInitialHeight;` — Height of the key in the center.
- L27 _public member_ `TOptional<double> LeftKeyHeight;` — Height of the key to the left of the center key.
- L29 _public member_ `TOptional<double> RightKeyHeight;` — Height of the key to the right of the center key.
- L32 _public function_ `TOptional<double> Choose(ESide InSide) const` — @return The height of the neighbor specified.
- L35 _public function_ `bool IsEmpty() const` — @return Whether the center key has any neighbors.

#### struct `UE::CurveEditor::FSingleKeyMirrorData`  
`struct FSingleKeyMirrorData`  
_L42-71_
- desc: Information used to flatten tangent of a single key. @see FTangentSingleKeyFlattener
- L45 _public member_ `FKeyHandle CenterKey;` — The center key, which is being moved.
- L47 _public member_ `FKeyNeighborData NeighborData;` — Info about the key's neighbor hood. Used to compute the mirror value.
- L50 _public member_ `FCurveTangentMirrorData TangentMirrorData;` — The data used to interpolate the key
- L53 _public member_ `ESide AnchorKeySide;` — Indicates the neighbor of the interpolated key with which the base interpolation distance initialized
- L55 _public member_ `double InitialDistanceToAnchorPoint;` — The distance the center key had to the anchor key, when the data was initialized
- L58 _public function_ `FKeyHandle GetKeyHandle() const` — @return The key whose tangent is being flattened
- L60 _public function_ `explicit FSingleKeyMirrorData( FKeyHandle InCenterKey, const FKeyNeighborData& InNeighborData, FCurveTangentMirrorData InTangentMirrorData, ESide InAnchorPoint, double InInitialDistanceToAnchorPoint ) : CenterKey(InCenterKey) , NeighborData(InNeighborData) , TangentMirrorData(MoveTemp(InTangentMirrorData)) , AnchorKeySide(InAnchorPoint) , InitialDistanceToAnchorPoint(InInitialDistanceToAnchorPoint)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CURVEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Misc/Mirror/TangentMirrorSolver.h` (Public)


#### class `UE::CurveEditor::FTangentMirrorSolver`  
`class FTangentMirrorSolver`  
_L31-80_
- desc: Given keys that are between an imaginary, x-axis aligned mirror edge and dragged edge, this class facilitates recalculates the tangents for all specified keys. The tangents are linearly interpolated, ensuring that if the dragged edge crosses to the opposite side of the mirror edge, the tangents will flip, resulting in mirrored curves. Inputs: - Height of the dragged edge aligned to the x-axis - Height of the x-axis-aligned mirror edge - Keys originally located between the dragged and mirror edges Example: Given a grid with a single key at a 45-degree angle, moving the top edge: - An equal distance past the bottom edge will result in a tangent of -45 degrees for the key. - Halfway between the starting position and the bottom edge will result in a tangent of 22.5 degrees for the key. @note This class only recalculates tangents. To adjust the positions of the keys use e.g. FPositionMirrorSolver.
- L36 _public member_ `const double StartY;` — Height of the dragged line.
- L38 _public member_ `const double MiddlePointY;` — Height of the mirroring line.
- L41 _public member_ `TMap<FCurveModelID, FCurveTangentMirrorData> CurveData;` — This memory is reused across OnMoveEdge to hold the updated tangents. Caching the memory speeds up the re-computation.
- L50 _public prototype_ `explicit FTangentMirrorSolver( double InStartY, double InMiddlePointY );` — InStartY and InMiddlePointY define two imaginary, x-axis aligned lines. All keys added must be between or on these two lines for the mirroring to work as expected. @param InStartY The height of the line that is moved. It determines how the tangents are interpolated. @param InMiddlePointY The height of the line on which the points are moved.
- L65 _public prototype_ `bool AddTangents(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys);` — Adds tangents that are be mirrored. InStartY and InMiddlePointY define two imaginary, x-axis aligned lines. All keys must be between or on these two lines for the mirroring to work as expected. @param InCurveEditor Used to get and set tangent values @param InCurveId The curve that all keys lie on @param InKeys The keys whose tangents to recompute @return Whether any of the keys can be interpolated (only user specified tangents can be interpolated).
- L74 _public prototype_ `template<typename TProcessCallback> requires std::is_invocable_v<TProcessCallback, const FMirrorableTangentInfo& > bool AddTangents( const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys, TProcessCallback&& InProcessTangentInfo );` — Version that allows you to do additional processing for the tangents. For example,  you may want to compute falloff values for each key. In that case, you probably want to manually iterate CurveData and use the version of RecomputeMirroringParallel that allows you to interpolate tangent values further.
- L79 _public prototype_ `void OnMoveEdge(const FCurveEditor& InCurveEditor, double InDraggedEdgeHeight);` — Recomputes the tangents angles and updates the key attributes.
- L85 _function_ `inline FTangentMirrorSolver::FTangentMirrorSolver(double InStartY, double InMiddlePointY) : StartY(InStartY) , MiddlePointY(InMiddlePointY)`
- L90 _function_ `inline bool FTangentMirrorSolver::AddTangents(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys)`
- L96 _function_ `template <typename TProcessCallback> requires std::is_invocable_v<TProcessCallback, const FMirrorableTangentInfo&> bool FTangentMirrorSolver::AddTangents( const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys, TProcessCallback&& InProcessTangentInfo )`
- L113 _function_ `inline void FTangentMirrorSolver::OnMoveEdge(const FCurveEditor& InCurveEditor, double InDraggedEdgeHeight)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)
- L83 _namespace_ `namespace UE`
- L83 _namespace_ `namespace CurveEditor` (scope `UE`)
- L92 _function_ `return AddTangents(InCurveEditor, InCurveId, InKeys, [](const FMirrorableTangentInfo&){});` (scope `UE::CurveEditor::FTangentMirrorSolver::AddTangents`)

### `Source/Editor/CurveEditor/Public/Misc/Mirror/TangentSelectionFlattener.h` (Public)


#### class `UE::CurveEditor::FTangentSelectionFlattener`  
`class FTangentSelectionFlattener`  
_L22-45_
- desc: Given some keys, this class squishes the curves based on how much the selection is squished vertically. The squishing of the curves is achieved by interpolating the tangents to 0. This is useful if you have a selection of keys, apply some operation that will move the keys, and want to flatten the curves. Example use case is e.g. tweening.
- L26 _public prototype_ `FTangentSelectionFlattener() = default;`
- L27 _public function_ `explicit FTangentSelectionFlattener(const FCurveEditor& InCurveEditor)`
- L30 _public prototype_ `bool ResetFromSelection(const FCurveEditor& InCurveEditor);` — Inits the tangent data from the curve editor's selection.
- L33 _public prototype_ `bool AddTangents(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys);` — @return Whether any interpolatable tangents were added (only tangents that are RCTM_User or RCTM_Break).
- L40 _public prototype_ `void ComputeMirroringParallel(const FCurveEditor& InCurveEditor, bool bTopHasCrossedBottomEdge = false);` — Call in response to the keys having moved. Recomputes user specified tangents and flattens them. @param InCurveEditor Used to update key positions @param bTopHasCrossedBottomEdge If since this was initialized, the top edge has moved across the bottom edge.
- L44 _private member_ `TMap<FCurveModelID, FCurveTangentMirrorData> CachedCurveData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CURVEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Misc/Mirror/TangentSingleKeyFlattener.h` (Public)


#### class `UE::CurveEditor::FTangentSingleKeyFlattener`  
`class FTangentSingleKeyFlattener`  
_L37-63_
- desc: Flattens the tangents of a single key per curve whose tangent mode is user-specified (RCTM_User or RCTM_Break). The degree of flattening is proportional to how close the key moves toward a neighboring key vertically: reaching the neighbor results in fully flat (zero) tangents and passing the neighbor causes it to flip. === Algorithm for a center key k === AddTangents (call once to initialize): 1. Find the left and right neighbors of k. 2. Pick an anchor neighbor: prefer left, fall back to right. 3. Record initial_distance = |k.Y - anchor.Y|. (No-ops if k has no neighbors, or if k and anchor share the same Y value.) ComputeMirroringParallel (call each time k moves to recompute tangents): 1. Compute a blend height; a value that shrinks toward 0 as k approaches either neighbor: - Moving toward anchor:   blend = |k.Y - anchor.Y| - Moving toward opposite: blend = initial_distance * (1 - |current_distance_to_anchor - initial_distance| / |k_initial.Y - opposite.Y|) 2. If k has crossed past the target neighbor, flip the tangent direction. 3. Scale the tangents linearly by blend via RecomputeMirroringParallel. @see FTangentSelectionFlattener For flattening consecutive keys.
- L41 _public prototype_ `FTangentSingleKeyFlattener() = default;`
- L44 _public prototype_ `bool ResetFromSelection(const FCurveEditor& InCurveEditor);` — Inits the tangent data from the curve editor's selection.
- L51 _public prototype_ `bool AddTangents(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys);` — Searches the range for exactly 1 key that has user specified tangents and adds the key as blend info. If there are more than 1 such keys, nothing happens. @return Whether any data was added.
- L58 _public prototype_ `void ComputeMirroringParallel(const FCurveEditor& InCurveEditor, ESide InKeyToMirrorTo);` — Recomputes the keys's tangents based on where on their vertical distance to the specified neighboring keys. @param InCurveEditor Used to update key positions @param InKeyToMirrorTo The neighboring key to use as pivot for mirror computation.
- L62 _private member_ `TMap<FCurveModelID, FSingleKeyMirrorData> CachedCurveData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CURVEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Misc/Mirror/UniformMirrorSolver.h` (Public)


#### class `UE::CurveEditor::TUniformMirrorSolver`  
`template<typename TNumeric> class TUniformMirrorSolver`  
_L30-77_
- desc: This class computes linear interpolation for values involving the movement of edges in a rectangular selection of keys. While best used for tangent angles, it could be applied to any key attributes that can be interpolated linearly. For example: - When the top edge is moved downward, the interpolated values decrease linearly to 0 as the edge approaches the bottom edge. If the top edge moves past the bottom edge (the "midpoint"), the values invert, transitioning past zero into the opposite sign. - Similarly, when the bottom edge is moved upward toward the top edge, the same interpolation and inversion logic applies. This class handles the described interpolation logic in a generic manner. It is agnostic to the type or source of the values being interpolated and how the computed values are applied. Its sole responsibility is to perform linear interpolation based on the edge movement. @param TNumeric Must support operator+(TNumeric, TNumeric) itself and operator*(TNumeric,double). E.g. float, double, FVector2D, FVector, etc.
- L34 _public function_ `explicit TUniformMirrorSolver( double StartY, double MiddlePointY, TArray<TNumeric> InInterpolatedValues, TArray<double> InKeyHeights, TNumeric InMiddlePointBaseValue = TNumeric(0) ) : StartY(StartY) , MiddlePointY(MiddlePointY) , InitialValues(MoveTemp(InInterpolatedValues)) , InitialKeyHeights(MoveTemp(InKeyHeights)) , MiddlePointBaseValue(InMiddlePointBaseValue)`
- L52 _public function_ `template<typename TCallback> requires std::is_invocable_v<TCallback, int32 , const TNumeric& > void ComputeMirroringParallel(double InNewHeight, TCallback&& InProcessTangent) const` — Recomputes the values in response to the edge being moved. @param InNewHeight The new height of the moved edge @param InProcessTangent Processes the new tangent angles (in radians).
- L64 _public function_ `int32 NumValues() const`
- L67 _public member_ `const double StartY;` — The Y component at which the drag started.
- L69 _public member_ `const double MiddlePointY;` — The Y component at which the tangents reach 0 slope.
- L72 _public member_ `const TArray<TNumeric> InitialValues;` — The initial tangent angles in radians. Indices coincide with InitialKeyHeights.
- L74 _public member_ `const TArray<double> InitialKeyHeights;` — The initial heights of all keys. Indices coincide with InitialKeyHeights.
- L76 _public member_ `const TNumeric MiddlePointBaseValue;` — The value that should be at MiddlePointY.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L57 _function_ `` (scope `UE::CurveEditor::TUniformMirrorSolver::ComputeMirroringParallel`)

### `Source/Editor/CurveEditor/Public/Misc/ResizeParamUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L17 _prototype_ `FMenuEntryResizeParams MakeResizeParams(FStringView UISpecifier, const ISlateStyle& Style = FAppStyle::Get());` (scope `UE::CurveEditor`) — Looks up the CurveEditor.AllowClipping.[UISpecifier] and CurveEditor.ClipPriority.[UISpecifier] from the given style. @return Resizing params to use for the toolbar item.
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace CurveEditor` (scope `UE`)
- L22 _function_ `inline FMenuEntryResizeParams MakeResizeParams(FStringView UISpecifier, const ISlateStyle& Style)` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Public/Misc/SuppressibleEventBroadcaster.h` (Public)


#### class `UE::CurveEditor::FSuppressibleEventBroadcaster`  
`class FSuppressibleEventBroadcaster`  
_L17-71_
- desc: Wraps a simple multicast delegate with a counter. While the counter is positive, the event cannot be broadcast. Once the counter reaches 0, the event is broadcast. This is a reusable optimization that is useful to change-type events.
- L21 _public function_ `void IncrementSuppressionCount()`
- L26 _public function_ `void DecrementSuppressionCount()`
- L42 _public function_ `void Broadcast()`
- L56 _public function_ `FSimpleMulticastDelegate& OnChanged()` — @return The event that is broadcast. This exists only for convenience: by design, you're NOT supposed to call Broadcast on this directly.
- L61 _private member_ `int32 SuppressionCount = 0;` — When 0, the event can be broadcast.
- L67 _private member_ `bool bWasEventSuppressed = false;` — This is set to true when Broadcast is called while SuppressionCount > 0. If true, then DecrementSuppressionCount will broadcast the event when count reaches 0.
- L70 _private member_ `FSimpleMulticastDelegate Event;` — The event to broadcast

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/CurveEditorCommandChange.h` (Public)


#### class `UE::CurveEditor::FCurveEditorCommandChange`  
`class FCurveEditorCommandChange : public FCommandChange`  
_L15-37_
- inherits: `FCommandChange`
- desc: Base class for actions that support undo / redo in the curve editor.
- L19 _public function_ `explicit FCurveEditorCommandChange(TSharedPtr<FCurveEditor> InCurveEditor) : WeakCurveEditor(MoveTemp(InCurveEditor))`
- L24 _public prototype_ `virtual bool HasExpired(UObject* InObject) const override;`
- L25 _public prototype_ `virtual FString ToString() const override;`
- L31 _protected prototype_ `TSharedPtr<FCurveEditor> GetCurveEditor() const;` — @return The curve editor associated with Object.
- L36 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — The curve editor this operation was performed on.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CURVEEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/CurveChangeDiff.h` (Public)


#### class `UE::CurveEditor::FCurveChangeDiff`  
`class FCurveChangeDiff`  
_L41-73_
- desc: Utility that holds a snapshot of some curve data for the purposes of later comparing changes made to those curves. This is useful for actions that take multiple frames, e.g. the user dragging keys. Start by constructing FCurvesSnapshotBuilder instance, adding the curves you want to diff later, and when the operation is done call ComputeDiff to compute the change. Note: This class introduces some overhead by temporarily saving the curve state. If the change is a one-off (i.e. not interactive) you usually know exactly what will change, so you can consider building the change directly. It's still fine to use this class in that case as it simplifies the code: the overhead is usually acceptable. @see FScopedKeyChange For some profiling data.
- L45 _public function_ `explicit FCurveChangeDiff(TWeakPtr<FCurveEditor> InCurveEditor, FCurvesSnapshot InSnapshot, ECurveChangeFlags InOps = ECurveChangeFlags::All) : WeakCurveEditor(MoveTemp(InCurveEditor)) , Operations(InOps) , Snapshot(MoveTemp(InSnapshot))`
- L51 _public function_ `FCurveChangeDiff(FCurvesSnapshotBuilder InBuilder) : FCurveChangeDiff(InBuilder.WeakCurveEditor, MoveTemp(InBuilder.Snapshot), InBuilder.CapturedDataFlags)`
- L56 _public prototype_ `FGenericCurveChangeData ComputeDiff() const;` — Computes what has changed on the given curves.
- L59 _public prototype_ `void ProcessDiffs(IMultiCurveChangeVisitor& InChangeBuilder) const;` — Passes all changes to the given instance.
- L62 _public function_ `const FCurvesSnapshot& GetSnapshot() const` — The snapshot against which is diffed.
- L67 _private member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — Needed to look up curves and compare state.
- L69 _private member_ `const ECurveChangeFlags Operations;` — The operations that we should diff with.
- L72 _private member_ `const FCurvesSnapshot Snapshot;` — Data that ComputeDiff diffs against.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)
- L19 _prototype_ `FGenericCurveChangeData ComputeDiff( const FCurveEditor& InCurveEditor, const ECurveChangeFlags InOperations, const FCurvesSnapshot& InSnapshot );` (scope `UE::CurveEditor`) — @return FGenericCurveChangeData containing what has changed for the data saved in InSnapshot.
- L24 _prototype_ `void ProcessChanges( const FCurveEditor& InCurveEditor, const ECurveChangeFlags InOperations, const FCurvesSnapshot& InSnapshot, IMultiCurveChangeVisitor& InChangeVisitor );` (scope `UE::CurveEditor`) — Computes what has changed for the data saved in InSnapshot and passes those changes to IMultiCurveChangeVisitor to perform any processing.

### `Source/Editor/CurveEditor/Public/Modification/Keys/CurvesSnapshotBuilder.h` (Public)


#### struct `UE::CurveEditor::FCurvesSnapshotBuilder`  
`struct FCurvesSnapshotBuilder`  
_L17-69_
- desc: Utility for selectively capturing state of curves based on some ECurveChangeFlags. Intended for constructing either a FCurvesSnapshot or FCurveChangeDiff.
- L20 _public member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — Needed to look up curves and compare state.
- L22 _public member_ `const ECurveChangeFlags CapturedDataFlags;` — The operations that we should diff with.
- L25 _public member_ `FCurvesSnapshot Snapshot;` — Data that ComputeDiff diffs against.
- L27 _public function_ `explicit FCurvesSnapshotBuilder( TWeakPtr<FCurveEditor> InCurveEditor, ECurveChangeFlags InOps = ECurveChangeFlags::All ) : WeakCurveEditor(MoveTemp(InCurveEditor)) , CapturedDataFlags(InOps)`
- L35 _public function_ `explicit FCurvesSnapshotBuilder( TWeakPtr<FCurveEditor> InCurveEditor, const FCurveModelID& InCurveId, ECurveChangeFlags InOps = ECurveChangeFlags::All ) : FCurvesSnapshotBuilder(MoveTemp(InCurveEditor), InOps)` — Util constructor for tracking a single curve.
- L44 _public function_ `template<typename TRangeType> explicit FCurvesSnapshotBuilder( TWeakPtr<FCurveEditor> InCurveEditor, const TRangeType& InRangeType, ECurveChangeFlags InOps = ECurveChangeFlags::All ) : FCurvesSnapshotBuilder(MoveTemp(InCurveEditor), InOps)` — Util constructor for tracking a container of curves (TSet, TMap, TArray, TArrayView, TConstArrayView)
- L53 _public prototype_ `FCurvesSnapshotBuilder& TrackCurve(const FCurveModelID& InCurveId);` — Tracks all keys on InCurveModel.
- L54 _public prototype_ `FCurvesSnapshotBuilder& TrackCurves(TConstArrayView<FCurveModelID> InCurves);`
- L55 _public prototype_ `FCurvesSnapshotBuilder& TrackCurves(const TSet<FCurveModelID>& InCurves);`
- L57 _public prototype_ `template<typename T> FCurvesSnapshotBuilder& TrackCurves(const TMap<FCurveModelID, T>& InCurveMapping);`
- L60 _public prototype_ `FCurvesSnapshotBuilder& TrackCurve(const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> Keys);` — Tracks only the specified keys. Incompatible with EKeyChangeOperationFlags::AddKeys.
- L63 _public prototype_ `FCurvesSnapshotBuilder& TrackSelectedKeys();` — Tracks all curves that are selected: adds only their selected keys. Incompatible with EKeyChangeOperationFlags::AddKeys.
- L65 _public prototype_ `FCurvesSnapshotBuilder& TrackSelectedCurves();` — Tracks all curves that are selected: adds all keys of those curves.
- L68 _public prototype_ `FCurvesSnapshotBuilder& TrackAllCurves();` — Tracks all curves.
- L72 _function_ `template <typename T> FCurvesSnapshotBuilder& FCurvesSnapshotBuilder::TrackCurves(const TMap<FCurveModelID, T>& InCurveMapping)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/AddKeysChangeData.h` (Public)


#### struct `UE::CurveEditor::FAddKeysChangeData`  
`struct FAddKeysChangeData`  
_L9-30_
- L15 _public member_ `TMap<FCurveModelID, FCurveKeyData> SavedCurveState;` — On undo, remove the FKeyDataSnapshot::Keys. On redo, add back FKeyDataSnapshot::Keys together with the saved positions and attributes.
- L17 _public function_ `bool HasChanges() const`
- L18 _public function_ `operator bool() const`
- L19 _public function_ `SIZE_T GetAllocatedSize() const`
- L22 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/CurveAttributeChangeData.h` (Public)


#### struct `UE::CurveEditor::FCurveAttributeChangeData_PerCurve`  
`struct FCurveAttributeChangeData_PerCurve`  
_L10-22_
- desc: Stores data for restoring the curve attributes of a single curve.
- L13 _public member_ `FCurveAttributes BeforeChange;` — The key attributes before the change. Set attributes to this on undo.
- L15 _public member_ `FCurveAttributes AfterChange;` — The key attributes after the change. Set attributes to this on undo.
- L17 _public function_ `bool HasChanges() const`
- L18 _public function_ `operator bool() const`

#### struct `UE::CurveEditor::FCurveAttributeChangeData`  
`struct FCurveAttributeChangeData`  
_L25-32_
- desc: Stores data for restoring curves attributes of multiple curves.
- L27 _public member_ `TMap<FCurveModelID, FCurveAttributeChangeData_PerCurve> ChangeData;`
- L29 _public function_ `bool HasChanges() const`
- L30 _public function_ `operator bool() const`
- L31 _public function_ `SIZE_T GetAllocatedSize() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/CurveKeyDataMap.h` (Public)


#### struct `UE::CurveEditor::FCurveKeyData`  
`struct FCurveKeyData`  
_L13-61_
- desc: Holds data for restoring keys on a curve.
- L19 _public member_ `TArray<FKeyHandle> KeyHandles;` — The tracked key handles. Contains all key handles if EKeyChangeOperationFlags::AddKeys. Always set.
- L27 _public member_ `TArray<FKeyPosition> KeyPositions;` — The positions of Handles. Each index matches that of Handles. Set only for EKeyChangeOperationFlags::MoveKeys. Either same length as Handles or 0 length.
- L35 _public member_ `TArray<FKeyAttributes> KeyAttributes;` — The attributes of Handles. Each index matches that of Handles. Set only for EKeyChangeOperationFlags::KeyAttributes. Either same length as Handles or 0 length.
- L37 _public function_ `bool HasKeyPositions() const`
- L38 _public function_ `bool HasKeyAttributes() const`
- L40 _public function_ `bool HasData() const`
- L41 _public function_ `operator bool() const`
- L43 _public function_ `SIZE_T GetAllocatedSize() const`
- L46 _public function_ `template<typename T> static SIZE_T GetAllocatedSize(const TMap<T, FCurveKeyData>& InMapping)`
- L55 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### struct `UE::CurveEditor::FCurveKeyDataMap`  
`struct FCurveKeyDataMap`  
_L64-73_
- desc: Snapshot of curve editor content.
- L67 _public member_ `TMap<FCurveModelID, FCurveKeyData> SavedCurveState;` — The state that the curves had.
- L69 _public prototype_ `FCurveKeyDataMap() = default;`
- L70 _public function_ `explicit FCurveKeyDataMap(TMap<FCurveModelID, FCurveKeyData> SavedCurveState) : SavedCurveState(MoveTemp(SavedCurveState))`
- L72 _public function_ `SIZE_T GetAllocatedSize() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)
- L49 _function_ `` (scope `UE::CurveEditor::FCurveKeyData::GetAllocatedSize`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/CurvesSnapshot.h` (Public)


#### struct `UE::CurveEditor::FCurveDiffingData`  
`struct FCurveDiffingData : FCurveKeyData`  
_L20-40_
- inherits: `FCurveKeyData`
- desc: Holds data that is captured to diff a curves previous state to a current state. Not all data needs to be captured, e.g. Handles, KeyPositions, Attributes can be empty and CurveAttributes unset. It would be pointless to construct this without any members set. If either KeyPositions or Attributes is set, then Handles is also set. Intended to be built using FCurvesSnapshotBuilder and ECurveChangeFlags.
- L23 _public member_ `TOptional<FCurveAttributes> CurveAttributes;` — The curve attributes if they were captured.
- L25 _public function_ `bool HasCurveAttributes() const`
- L27 _public function_ `bool HasData() const`
- L28 _public function_ `operator bool() const`
- L30 _public function_ `SIZE_T GetAllocatedSize() const`
- L33 _public function_ `template<typename T> static SIZE_T GetAllocatedSize(const TMap<T, FCurveDiffingData>& InMapping)`

#### struct `UE::CurveEditor::FCurvesSnapshot`  
`struct FCurvesSnapshot`  
_L43-57_
- desc: Holds selected data about curves. This data is usually used to diff against changes made to those curves.
- L51 _public member_ `TMap<FCurveModelID, FCurveDiffingData> CurveData;` — The info about the curves. Not all members of FCurveDiffingData need to contain data: just the members intended for diffing. Intended to be built using FCurvesSnapshotBuilder and ECurveChangeFlags.
- L53 _public prototype_ `FCurvesSnapshot() = default;`
- L54 _public function_ `explicit FCurvesSnapshot(TMap<FCurveModelID, FCurveDiffingData> InCurveData) : CurveData(MoveTemp(InCurveData))`
- L56 _public function_ `SIZE_T GetAllocatedSize() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)
- L36 _function_ `` (scope `UE::CurveEditor::FCurveDiffingData::GetAllocatedSize`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/GenericCurveChangeData.h` (Public)


#### struct `UE::CurveEditor::FGenericCurveChangeData`  
`struct FGenericCurveChangeData`  
_L14-51_
- desc: Stores changes made to curves in the curve editor.
- L16 _public member_ `FMoveKeysChangeData MoveKeysData;`
- L17 _public member_ `FAddKeysChangeData AddKeysData;`
- L18 _public member_ `FRemoveKeysChangeData RemoveKeysData;`
- L19 _public member_ `FKeyAttributeChangeData KeyAttributeData;`
- L20 _public member_ `FCurveAttributeChangeData CurveAttributeData;`
- L22 _public function_ `bool HasChanges() const`
- L23 _public function_ `operator bool() const`
- L26 _public function_ `int32 NumChangeTypes() const` — @return The number of distinct change types. Useful for testing.
- L34 _public function_ `SIZE_T GetAllocatedSize() const`
- L44 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/KeyAttributeChangeData.h` (Public)


#### struct `UE::CurveEditor::FKeyAttributeChangeData_PerCurve`  
`struct FKeyAttributeChangeData_PerCurve`  
_L14-40_
- desc: Stores data for restoring key attributes for a single curve.
- L17 _public member_ `TArray<FKeyHandle> Handles;` — The key handles that changed attributes.
- L25 _public member_ `TArray<FKeyAttributes> BeforeChange;` — The key attributes before the change. Set attributes to this on undo. Each index corresponds to Handles.
- L27 _public member_ `TArray<FKeyAttributes> AfterChange;` — The key attributes after the change. Set attributes to this on redo. Each index corresponds to Handles.
- L29 _public function_ `bool HasChanges() const`
- L30 _public function_ `operator bool() const`
- L31 _public function_ `SIZE_T GetAllocatedSize() const`
- L34 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### struct `UE::CurveEditor::FKeyAttributeChangeData`  
`struct FKeyAttributeChangeData`  
_L43-67_
- desc: Stores data for restoring key attributes of multiple curves.
- L45 _public member_ `TMap<FCurveModelID, FKeyAttributeChangeData_PerCurve> ChangedCurves;`
- L47 _public function_ `bool HasChanges() const`
- L48 _public function_ `operator bool() const`
- L49 _public function_ `SIZE_T GetAllocatedSize() const`
- L59 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L53 _function_ `` (scope `UE::CurveEditor::FKeyAttributeChangeData::GetAllocatedSize`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/MoveKeysChangeData.h` (Public)


#### struct `UE::CurveEditor::FMoveKeysChangeData_PerCurve`  
`struct FMoveKeysChangeData_PerCurve`  
_L12-35_
- L15 _public member_ `TArray<FKeyHandle> Handles;` — The moved key handles.
- L23 _public member_ `TArray<FVector2f> Translations;` — The amount the corresponding key was moved. When applying (redo) the change, add the value to the key position. When reverting (undo) the change, subtract the value.
- L25 _public function_ `bool HasChanges() const`
- L26 _public function_ `operator bool() const`
- L27 _public function_ `SIZE_T GetAllocatedSize() const`
- L30 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### struct `UE::CurveEditor::FMoveKeysChangeData`  
`struct FMoveKeysChangeData`  
_L41-66_
- desc: Data for an operation that translates keys. This can still be improved: if all keys were transformed uniformly, then we only need to store a single FVector2f.
- L44 _public member_ `TMap<FCurveModelID, FMoveKeysChangeData_PerCurve> ChangedCurves;` — The per curve changes.
- L46 _public function_ `bool HasChanges() const`
- L47 _public function_ `operator bool() const`
- L48 _public function_ `SIZE_T GetAllocatedSize() const`
- L58 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditor` (scope `UE`)
- L52 _function_ `` (scope `UE::CurveEditor::FMoveKeysChangeData::GetAllocatedSize`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Data/RemoveKeysChangeData.h` (Public)


#### struct `UE::CurveEditor::FRemoveKeysChangeData`  
`struct FRemoveKeysChangeData`  
_L11-32_
- L17 _public member_ `TMap<FCurveModelID, FCurveKeyData> SavedCurveState;` — On undo, add back FKeyDataSnapshot::Keys together with the saved positions and attributes. On redo, remove the FKeyDataSnapshot::Keys.
- L19 _public function_ `bool HasChanges() const`
- L20 _public function_ `operator bool() const`
- L21 _public function_ `SIZE_T GetAllocatedSize() const`
- L24 _public function_ `void Shrink()` — Shrinks the containers' used memory to smallest possible to store elements currently in it.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Diff/IMultiCurveChangeVisitor.h` (Public)


#### class `UE::CurveEditor::IMultiCurveChangeVisitor`  
`class IMultiCurveChangeVisitor`  
_L18-44_
- desc: Interface for processing changes made to multiple FCurveModels. @see ISingleCurveChangeVisitor @see FCurveChangeDiff
- L36 _public prototype_ `virtual void ProcessChange(const FCurveModelID& InCurveModel, TFunctionRef<void(ISingleCurveChangeVisitor&)> InProcessCallback) = 0;` — Called when changes are about to be processed for InCurveModel. You are supposed to construct some ICurveChangeVisitor and call InProcessCallback with it. InProcessCallback will only use your visitor for the duration of the function call. This pattern allows construction of your visitor on the stack (avoiding heap allocating it). A sample implementation could be: void FFooDiffBuilder::ProcessChange(const FCurveModelID& InCurveModel, TFunctionRef<void(ICurveChangeVisitor&)> InProcessCallback) { FFooCurveChangeVisitor MyVisitor(InCurveModel); InProcessCallback(MyVisitor); }
- L39 _public function_ `virtual void PreProcessChanges()` — Called before any ProcessChange calls are made.
- L41 _public function_ `virtual void PostProcessChanges()` — Called after all changes have been listed, i.e. no more ProcessChange will follow.
- L43 _public prototype_ `virtual ~IMultiCurveChangeVisitor() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/Diff/ISingleCurveChangeVisitor.h` (Public)


#### class `UE::CurveEditor::ISingleCurveChangeVisitor`  
`class ISingleCurveChangeVisitor`  
_L17-37_
- desc: Interface for processing changes made to a single FCurveModel. @see ICurveDiffBuilder @see FCurveChangeDiff
- L22 _public function_ `virtual void ProcessMoveKeys(FMoveKeysChangeData_PerCurve&& InData)` — Processes moved keys. Only called if InData contains any changes, i.e. InData.HasChanges() == true.
- L25 _public function_ `virtual void ProcessAddKeys(FCurveKeyData&& InData)` — Processes added keys. Only called if InData contains any changes, i.e. InData.HasChanges() == true.
- L28 _public function_ `virtual void ProcessRemoveKeys(FCurveKeyData&& InData)` — Processes removed keys. Only called if InData contains any changes, i.e. InData.HasChanges() == true.
- L31 _public function_ `virtual void ProcessKeyAttributesChange(FKeyAttributeChangeData_PerCurve&& InData)` — Processes changed key attributes. Only called if InData contains any changes, i.e. InData.HasChanges() == true.
- L34 _public function_ `virtual void ProcessCurveAttributesChange(FCurveAttributeChangeData_PerCurve&& InData)` — Processes changed curve attributes. Only called if InData contains any changes, i.e. InData.HasChanges() == true.
- L36 _public prototype_ `virtual ~ISingleCurveChangeVisitor() = default;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/ECurveChangeFlags.h` (Public)


#### enum `UE::CurveEditor::ECurveChangeFlags`  
`enum class ECurveChangeFlags : uint8`  
_L11-39_
- desc: Flags about the types of changes that can be made to a curve.
- L13 _public enumerator_ `None`
- L16 _public enumerator_ `MoveKeys = 1 << 0` — Detect change of FKeyPosition for FKeyHandles that are present before and after the change.
- L18 _public enumerator_ `AddKeys = 1 << 1` — Detect FKeyHandles that are present after the change, but were not present before the change.
- L20 _public enumerator_ `RemoveKeys = 1 << 2` — Detect FKeyHandles that are not present after the change, but were present before the change.
- L25 _public enumerator_ `KeyAttributes = 1 << 3` — Detect FKeyAttributes that are different after the change. The attribute changes are detected for FKeyHandles that are present before and after the change.
- L27 _public enumerator_ `CurveAttributes = 1 << 4` — Detect changes to the curve attributes, e.g. pre and post extrapolation, etc.
- L34 _public enumerator_ `MoveKeysAndRemoveStackedKeys = MoveKeys | RemoveKeys` — Use when you move keys and the keys may end up being stacked (i.e. have the same x positions). When keys have the same x positions, curve editor removes the stacked keys so there's only 1 at the same x position. So removed keys must be tracked.
- L36 _public enumerator_ `KeyData = MoveKeys | AddKeys | RemoveKeys | KeyAttributes` — Track anything that modifies key data.
- L38 _public enumerator_ `All = KeyData | CurveAttributes` — All data should be tracked.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditor` (scope `UE`)
- L40 _prototype_ `ENUM_CLASS_FLAGS(ECurveChangeFlags);` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Public/Modification/Keys/GenericCurveChangeUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CURVEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CurveEditor` (scope `UE`)
- L16 _namespace_ `namespace GenericCurveChange` (scope `UE::CurveEditor`)
- L19 _prototype_ `void ApplyChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FGenericCurveChangeData& InDeltaChange, const double InCurrentSliderPos = 0 );` (scope `UE::CurveEditor::GenericCurveChange`) — Applies InDeltaChange to InCurves (redo).
- L23 _prototype_ `void RevertChange(const TMap<FCurveModelID, TUniquePtr<FCurveModel>>& InCurves, const FGenericCurveChangeData& InDeltaChange, const double InCurrentSliderPos = 0 );` (scope `UE::CurveEditor::GenericCurveChange`) — Reverts InDeltaChange from InCurves (undo).
- L28 _prototype_ `void ApplyChange(const FCurveEditor& InCurveEditor, const FGenericCurveChangeData& InDeltaChange);` (scope `UE::CurveEditor::GenericCurveChange`) — Applies InDeltaChange to InCurveEditor (redo).
- L30 _prototype_ `void RevertChange(const FCurveEditor& InCurveEditor, const FGenericCurveChangeData& InDeltaChange);` (scope `UE::CurveEditor::GenericCurveChange`) — Reverts InDeltaChange from InCurveEditor (undo).

### `Source/Editor/CurveEditor/Public/Modification/Keys/SnapshotPerfDebugUtils.h` (Public)


#### class `UE::CurveEditor::TCurvesSnapshotPerfInfo`  
`template<typename T> class TCurvesSnapshotPerfInfo`  
_L17-34_
- desc: Utility for retrieving some common performance data about FCurveDiffingData (or a collection thereof).
- L19 _private member_ `const TMap<T, FCurveDiffingData>& Data;`
- L22 _public function_ `explicit TCurvesSnapshotPerfInfo(const TMap<T, FCurveDiffingData>& InMap UE_LIFETIMEBOUND) : Data(InMap)`
- L23 _public function_ `explicit TCurvesSnapshotPerfInfo(const FCurvesSnapshot& InSnapshot UE_LIFETIMEBOUND) : Data(InSnapshot.CurveData)`
- L25 _public prototype_ `SIZE_T GetTotalAllocatedSize() const;`
- L27 _public prototype_ `SIZE_T NumKeys() const;`
- L28 _public prototype_ `SIZE_T NumPositions() const;`
- L29 _public prototype_ `SIZE_T NumAttributes() const;`
- L31 _public prototype_ `SIZE_T GetAllocatedSize_Keys() const;`
- L32 _public prototype_ `SIZE_T GetAllocatedSize_Positions() const;`
- L33 _public prototype_ `SIZE_T GetAllocatedSize_Attributes() const;`
- L68 _function_ `template <typename T> SIZE_T TCurvesSnapshotPerfInfo<T>::GetTotalAllocatedSize() const`
- L77 _function_ `template <typename T> SIZE_T TCurvesSnapshotPerfInfo<T>::NumKeys() const`
- L86 _function_ `template <typename T> SIZE_T TCurvesSnapshotPerfInfo<T>::NumPositions() const`
- L95 _function_ `template <typename T> SIZE_T TCurvesSnapshotPerfInfo<T>::NumAttributes() const`
- L104 _function_ `template <typename T> SIZE_T TCurvesSnapshotPerfInfo<T>::GetAllocatedSize_Keys() const`
- L113 _function_ `template <typename T> SIZE_T TCurvesSnapshotPerfInfo<T>::GetAllocatedSize_Positions() const`
- L122 _function_ `template <typename T> SIZE_T TCurvesSnapshotPerfInfo<T>::GetAllocatedSize_Attributes() const`

#### enum `UE::CurveEditor::ECurvesSnapshotPerfFlags`  
`enum class ECurvesSnapshotPerfFlags`  
_L36-47_
- L38 _public enumerator_ `None`
- L40 _public enumerator_ `TotalAllocatedSize = 1 << 0`
- L42 _public enumerator_ `Keys = 1 << 1`
- L43 _public enumerator_ `Positions = 1 << 2`
- L44 _public enumerator_ `Attributes = 1 << 3`
- L46 _public enumerator_ `All = TotalAllocatedSize | Keys | Positions | Attributes`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)
- L48 _prototype_ `ENUM_CLASS_FLAGS(ECurvesSnapshotPerfFlags);` (scope `UE::CurveEditor`)
- L52 _prototype_ `template<typename T> FString DumpSnapshotPerfData(const TCurvesSnapshotPerfInfo<T> InData, ECurvesSnapshotPerfFlags InFlags = ECurvesSnapshotPerfFlags::All);` (scope `UE::CurveEditor`) — Converts the specified info into a string.
- L55 _function_ `template<typename T> FString DumpSnapshotPerfData(const TMap<T, FCurveDiffingData>& InMap, ECurvesSnapshotPerfFlags InFlags = ECurvesSnapshotPerfFlags::All)` (scope `UE::CurveEditor`)
- L59 _function_ `inline FString DumpSnapshotPerfData(const FCurvesSnapshot& InSnapshot, ECurvesSnapshotPerfFlags InFlags = ECurvesSnapshotPerfFlags::All)` (scope `UE::CurveEditor`)
- L65 _namespace_ `namespace UE`
- L65 _namespace_ `namespace CurveEditor` (scope `UE`)
- L71 _function_ `` (scope `UE::CurveEditor::TCurvesSnapshotPerfInfo::GetTotalAllocatedSize`)
- L80 _function_ `` (scope `UE::CurveEditor::TCurvesSnapshotPerfInfo::NumKeys`)
- L89 _function_ `` (scope `UE::CurveEditor::TCurvesSnapshotPerfInfo::NumPositions`)
- L98 _function_ `` (scope `UE::CurveEditor::TCurvesSnapshotPerfInfo::NumAttributes`)
- L107 _function_ `` (scope `UE::CurveEditor::TCurvesSnapshotPerfInfo::GetAllocatedSize_Keys`)
- L116 _function_ `` (scope `UE::CurveEditor::TCurvesSnapshotPerfInfo::GetAllocatedSize_Positions`)
- L125 _function_ `` (scope `UE::CurveEditor::TCurvesSnapshotPerfInfo::GetAllocatedSize_Attributes`)
- L131 _function_ `template <typename T> FString DumpSnapshotPerfData(const TCurvesSnapshotPerfInfo<T> InData, ECurvesSnapshotPerfFlags InFlags)` (scope `UE::CurveEditor`)
- L136 _function_ `` (scope `UE::CurveEditor::DumpSnapshotPerfData`)

### `Source/Editor/CurveEditor/Public/Modification/Resolution/CurveMetaDataIdentifiers.h` (Public)


#### struct `UE::CurveEditor::FCurveMetaDataIdentifiers`  
`struct FCurveMetaDataIdentifiers`  
_L15-58_
- desc: Meta data about a FCurveModel useful to cache FCurveModelID when a curve with the same data is re-added to FCurveEditor.
- L18 _public member_ `TWeakObjectPtr<UObject> Owner;` — The UObject that owned the CurveModel.
- L21 _public member_ `FText ShortDisplayName;` — This curve's short display name. Used in situations where other mechanisms provide enough context about what the curve is (such as "X")
- L23 _public member_ `FText LongDisplayName;` — This curve's long display name. Used in situations where the UI doesn't provide enough context about what the curve is otherwise (such as "Floor.Transform.X")
- L26 _public member_ `FString IntentionName;` — This curve's short intention (such as Transform.X or Scale.X). Used internally to match up curves when saving/restoring curves between different objects.
- L31 _public member_ `FString LongIntentionName;` — This curve's long intention (such as foot_fk_l.Transform.X or foot_fk_r.Scale.X). Used internally to match up curves when saving/restoring curves between different objects. Long intention names have priority in copy/paste over short intention names, but we fall back to short intention if it's unclear what the user is trying to do.
- L34 _public member_ `FName ChannelName;` — The original channel name, used mostly to make sure names match with BP/Scripting
- L36 _public function_ `explicit FCurveMetaDataIdentifiers(const FCurveModel& InCurveModel) : Owner(InCurveModel.GetOwningObject()) , ShortDisplayName(InCurveModel.GetShortDisplayName()) , LongDisplayName(InCurveModel.GetLongDisplayName()) , IntentionName(InCurveModel.GetIntentionName()) , LongIntentionName(InCurveModel.GetLongIntentionName()) , ChannelName(InCurveModel.GetChannelName())`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)
- L45 _function_ `friend bool operator==(const FCurveMetaDataIdentifiers& Left, const FCurveMetaDataIdentifiers& Right)` (scope `UE::CurveEditor`)
- L54 _function_ `friend bool operator!=(const FCurveMetaDataIdentifiers& Left, const FCurveMetaDataIdentifiers& Right)` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Public/Modification/Resolution/CurveModelLookUpInfo.h` (Public)


#### struct `UE::CurveEditor::FCurveModelLookUpArgs`  
`struct FCurveModelLookUpArgs`  
_L22-34_
- desc: These arguments are used to temporarily resolve FCurveModel after it has been removed from FCurveEditor. Remember, FCurveModel::CurveData only holds the curves that are currently visible. Some systems, e.g. undo / redo with FGenericCurveCommandChange, require a curve model later.
- L25 _public member_ `const FCurveEditor& CurveEditor;` — The curve editor instance we're operating on
- L27 _public member_ `FCurveModelID CurveID;` — The curve trying to be resolved.
- L29 _public function_ `explicit FCurveModelLookUpArgs(const FCurveEditor& CurveEditor, const FCurveModelID& CurveID) : CurveEditor(CurveEditor), CurveID(CurveID)`
- L33 _public prototype_ `const FCurveMetaDataIdentifiers* GetCurveMetaData() const;` — @return Metadata information the curve had when it was last added FCurveEditor::AddCurve.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/TransactionManager.h` (Public)


#### class `UE::CurveEditor::FTransactionManager`  
`class FTransactionManager : public FNoncopyable, public FGCObject`  
_L21-84_
- inherits: `FNoncopyable,FGCObject`
- desc: Interacts with the transaction system to enable command-based actions for curve editor.
- L25 _public prototype_ `explicit FTransactionManager(TWeakPtr<FCurveEditor> InCurveEditor);`
- L28 _public prototype_ `void AppendCurveChange(UObject* InObject, FGenericCurveChangeData InChange, const FText& InDescription = FText::GetEmpty()) const;` — Appends a changes made to curves. It is associated with the current transaction.
- L34 _public prototype_ `void AppendCurveChange(FGenericCurveChangeData InChange, const FText& InDescription = FText::GetEmpty()) const;` — Appends a changes made to curves. It is associated with the current transaction. Use this version when there is no UObject the change can be associated with - otherwise use the UObject overload.
- L46 _public prototype_ `void AppendChange(UObject* InObject, TUniquePtr<FCurveEditorCommandChange> InChange, const FText& InDescription = FText::GetEmpty()) const;` — Appends a change to the current transaction and associates it with an UObject. You should prefer this overload whenever possible because it causes the object's package's dirty flag to be saved and restore by the undo system. Example: If you're modifying a FCurveModel, you'd pass in FCurveModel::GetOwningObject. @param InObject The object being modified @param InChange The change to associate with the currently open transaction @param InDescription Description of the change
- L59 _public prototype_ `void AppendChange(TUniquePtr<FCurveEditorCommandChange> InChange, const FText& InDescription = FText::GetEmpty()) const;` — Appends a change to the current transaction. Use this version when there is no UObject the change can be associated with - otherwise use the UObject overload. The transaction can consist of multiple changes, e.g. - system 1 may move keys, and - system 2 could coniditonally snap the keys to full frames after checking that the user has toggled auto-snapping @param InChange The change to associate with the currently open transaction @param InDescription Description of the change
- L61 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCommandAppended);`
- L63 _public function_ `FOnCommandAppended& OnCommandAppended()` — Invoked after a command has been appended to the undo stack.
- L65 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurvesChanged, const FGenericCurveChangeData&) FOnCurvesChanged& OnCurvesChanged()`
- L70 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L71 _public prototype_ `virtual FString GetReferencerName() const override;`
- L77 _private member_ `TObjectPtr<UCurveEditorTransactionObject> DummyTransactionObject;` — The UObject that transactions are associated with. The transaction system needs to associate FCommandChanges with an UObject.
- L80 _private member_ `FOnCommandAppended OnCommandAppendedDelegate;` — Invoked after a command has been appended to the undo stack.
- L83 _private member_ `FOnCurvesChanged OnCurvesChangedDelegate;` — Invoked when transaction changes to curves are made.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CURVEEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CurveEditor` (scope `UE`)
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCommandAppended);`
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurvesChanged, const FGenericCurveChangeData&) FOnCurvesChanged& OnCurvesChanged() { return OnCurvesChangedDelegate; }`

### `Source/Editor/CurveEditor/Public/Modification/Utils/ScopedChangeBase.h` (Public)


#### class `UE::CurveEditor::FScopedChangeBase`  
`class FScopedChangeBase`  
_L19-51_
- inherits: `FNoncopyable`
- desc: Base class for scoped changes that intend to append a command to the transaction system when the scope ends. It detects if constructed within a FScopedTransaction context: by calling IsCancelled(), you can handle the case of the root transaction being cancelled.
- L27 _public prototype_ `[[nodiscard]] explicit FScopedChangeBase(TWeakPtr<FCurveEditor> InCurveEditor, const FText& InDescription);`
- L30 _public function_ `void Cancel()` — Prevent the change from being appended.
- L35 _protected member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — Used to diff selection and append the change to the transaction system.
- L37 _protected member_ `const FText Description;` — Description to use for the change
- L40 _protected prototype_ `bool IsCancelled() const;` — Whether the change should be appended.
- L43 _protected prototype_ `void TryAppendCommand(TUniquePtr<FCurveEditorCommandChange> InCommand) const;` — Appends the change if it is not cancelled.
- L48 _private member_ `const bool bWasStartedInTransaction;` — Whether we were constructed in a transaction. Used to detect whether the transaction has since been cancelled.
- L50 _private member_ `bool bIsCancelled = false;` — Whether to skip submitting the change when the scope ends.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Modification/Utils/ScopedCurveChange.h` (Public)


#### enum `UE::CurveEditor::EScopedKeyChangeFlags`  
`enum class EScopedKeyChangeFlags : uint8`  
_L16-24_
- L18 _public enumerator_ `None`
- L21 _public enumerator_ `RevertOnCancel = 1 << 0` — Revert the change if FScopedKeyChange or surrounding FScopedTransaction becomes cancelled.
- L23 _public enumerator_ `Default = RevertOnCancel`

#### class `UE::CurveEditor::FScopedCurveChange`  
`class FScopedCurveChange : public FScopedChangeBase`  
_L107-146_
- inherits: `FScopedChangeBase`
- desc: Starts a transaction. Detects changes made to the curves specified on construction and adds it as an undo-able action. When the scope ends, checks whether keys were added, removed, moved, or its attributes (FKeyAttributes or FCurveAttributes) were edited. ========== Performance ========== This class exists for convenience, faster iteration times, and more concise code but introduces overhead by temporarily buffering the curves. If the overhead is too great, consider building the change directly, and appending it to the transaction manager manually. However, in practice, the overhead should not be a concern, and for simplicity, usage of FScopedKeyChange is encouraged and preferred. Stress test 15th of July, 2025, Development Build, Sequencer: ControlRigExample -> CopyPaste_Level-> PossessableBindings_CopyPaste -> Select Possessable_FKCR_CopyPaste - Set Interp Linear:	109.782 keys,	Undo Size: 5.582 MiB,		Diff buffer size: 2.955 MiB,	Diff time: 4.2 ms - Move Keys:            109.782 keys,	Undo Size: 1.36 MiB,		Diff buffer size: 2.117 MiB,	Diff time: 5.3 ms - Drag Tangents:        109.782 keys,	Undo Size: 5.582 MiB,		Diff buffer size: 2.955 MiB,	Diff time: 4.4 ms - Blend values:         109.782 keys,	Undo Size: 6.583 MiB,		Diff buffer size: 4.654 MiB,	Diff time: 10.7 ms - Delete Keys:          109.782 keys,	Undo Size: 5.395 MiB,		Diff buffer size: 4.63 MiB,		Diff time: 1.8 ms These are the stats logged by CurveEditor.LogDiffPerfStats 1. ========== Combining FScopedKeyChange and F
- L117 _public prototype_ `[[nodiscard]] explicit FScopedCurveChange( TWeakPtr<FCurveEditor> InCurveEditor, FCurveChangeDiff InKeyChangeDiff, const FText& InDescription, EScopedKeyChangeFlags InFlags );` — @param InCurveEditor The curve @param InKeyChangeDiff Contains the data that is supposed to be diffed against @param InDescription Optional description that will be used for the transaction title. This title does not matter if you have a surrounding FScopedTransaction. @param InFlags Extra flags to affect the behaviour of the change
- L121 _public prototype_ `[[nodiscard]] explicit FScopedCurveChange( FCurvesSnapshotBuilder InDataToDiff, const FText& InDescription = FText::GetEmpty(), EScopedKeyChangeFlags InFlags = EScopedKeyChangeFlags::Default );`
- L125 _public prototype_ `~FScopedCurveChange();`
- L135 _private member_ `FScopedTransaction Transaction;` — The transaction active during the change. This is required because FCurveModel implementations mark the owning package dirty when keys are modified. This achieves that undoing the change will unmark the package as dirty, if it was not dirty before the change.
- L138 _private member_ `const FCurveChangeDiff ChangeDiff;` — Checks for changes.
- L140 _private member_ `const EScopedKeyChangeFlags Flags;` — Flags about the change, e.g. whether to revert changes if cancelled, etc.
- L143 _private member_ `TPimplPtr<FModifyCurveObjectDetector> CurveModificationDetector;` — Util for warning about curves being modified.
- L145 _private prototype_ `void FinalizeChangesForNewUndoSystem();`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditor` (scope `UE`)
- L25 _prototype_ `ENUM_CLASS_FLAGS(EScopedKeyChangeFlags);` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Public/Modification/Utils/ScopedSelectionChange.h` (Public)


#### enum `UE::CurveEditor::EScopedSelectionChangeFlags`  
`enum class EScopedSelectionChangeFlags : uint8`  
_L15-31_
- L17 _public enumerator_ `None`
- L20 _public enumerator_ `RevertOnCancel = 1 << 0` — Revert the change if FScopedSelectionChange or surrounding FScopedTransaction becomes cancelled.
- L28 _public enumerator_ `SuppressOnSelectionChangedEvent = 1 << 1` — While the scope is constructed, also construct a FScopedSelectionChangeEventSuppression. If set, then the curve editor's FCurveEditorSelection::OnSelectionChanged will not be broadcast during the scope. Once the scope ends, and a change has been made to selection, FCurveEditorSelection::OnSelectionChanged is invoked.
- L30 _public enumerator_ `Default = RevertOnCancel | SuppressOnSelectionChangedEvent`

#### class `UE::CurveEditor::FScopedSelectionChange`  
`class FScopedSelectionChange : public FScopedChangeBase`  
_L49-73_
- inherits: `FScopedChangeBase`
- desc: Saves the current selection state and on destruction compares it against the then current selection. If the selection has changed when the scope ends, then - it appends an undo-able action to the curve editor transaction manager, - conditionally reverts the change if you called FScopedTransaction::Cancel on the surrounding transaction, - conditionally broadcasts FCurveEditorSelection::OnSelectionChanged if you set EScopedSelectionChangeFlags::SuppressOnSelectionChangedEvent. You can safely use this within the scope of a FScopedTransaction. In that case, the command will be added as sub-transaction to the parent transaction. The following is operations are supported: - Combination with FScopedKeyChange (@see FScopedKeyChange for detailed explanation). - Nesting within FScopedTransaction; if the outer FScopedTransaction is cancelled, FScopedSelectionChange can detect this (@see EScopedSelectionChangeFlags). - Nested FScopedSelectionChange
- L53 _public prototype_ `[[nodiscard]] explicit FScopedSelectionChange( TWeakPtr<FCurveEditor> InCurveEditor, EScopedSelectionChangeFlags InFlags = EScopedSelectionChangeFlags::Default );`
- L56 _public prototype_ `[[nodiscard]] explicit FScopedSelectionChange( TWeakPtr<FCurveEditor> InCurveEditor, const FText& InDescription, EScopedSelectionChangeFlags = EScopedSelectionChangeFlags::Default );`
- L61 _public prototype_ `~FScopedSelectionChange();`
- L66 _private member_ `const EScopedSelectionChangeFlags Flags;` — Flags that affect the behaviour of this change.
- L69 _private member_ `TOptional<FScopedSelectionChangeEventSuppression> SelectionChangedSuppressor;` — Suppresses FCurveEditorSelection::OnSelectionChanged until the scope ends. Only set if the flags requested it.
- L72 _private member_ `FCurveEditorSelection OriginalSelection;` — The selection the editor had when the transaction was started.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CURVEEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CurveEditor` (scope `UE`)
- L32 _prototype_ `ENUM_CLASS_FLAGS(EScopedSelectionChangeFlags);` (scope `UE::CurveEditor`)

### `Source/Editor/CurveEditor/Public/RichCurveEditorModel.h` (Public)


#### class `FRichCurveEditorModel`  
`class FRichCurveEditorModel : public FCurveModel`  
_L33-87_
- inherits: `FCurveModel`
- L36 _public prototype_ `FRichCurveEditorModel(UObject* InOwner);`
- L38 _public prototype_ `virtual const void* GetCurve() const override;`
- L40 _public prototype_ `virtual void Modify() override;`
- L42 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;`
- L43 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override;`
- L44 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L46 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L47 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L49 _public prototype_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L50 _public prototype_ `virtual void GetKeyAttributesExcludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L51 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L53 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutCurveAttributes) const override;`
- L54 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InCurveAttributes) override;`
- L55 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L56 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L57 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L58 _public prototype_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override;`
- L59 _public prototype_ `virtual TPair<ERichCurveInterpMode, ERichCurveTangentMode> GetInterpolationMode(const double& InTime, ERichCurveInterpMode DefaultInterpolationMode, ERichCurveTangentMode DefaultTangentMode) const override;`
- L61 _public prototype_ `virtual bool Evaluate(double ProspectiveTime, double& OutValue) const override;`
- L62 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InKeyPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L63 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override;`
- L65 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;`
- L67 _public prototype_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const override;`
- L69 _public function_ `virtual UObject* GetOwningObject() const override`
- L72 _public function_ `void SetClampInputRange(TAttribute<TRange<double>> InClampInputRange)` — Set a range to clamp key input values
- L76 _public prototype_ `virtual bool IsValid() const = 0;` — Check for whether this rich curve is valid. This is required mostly in the case of undo/redo, where curves can potentially become invalid underneath this model before owners get their undo/redo callbacks
- L79 _public prototype_ `virtual FRichCurve& GetRichCurve() = 0;` — Get the rich curve we are operating on
- L80 _public prototype_ `virtual const FRichCurve& GetReadOnlyRichCurve() const = 0;`
- L84 _private member_ `TWeakObjectPtr<> WeakOwner;`
- L86 _private member_ `TAttribute<TRange<double>> ClampInputRange;`

#### class `FRichCurveEditorModelRaw`  
`class FRichCurveEditorModelRaw : public FRichCurveEditorModel`  
_L90-107_
- inherits: `FRichCurveEditorModel`
- desc: Rich curve model operating on a raw curve ptr
- L93 _public prototype_ `FRichCurveEditorModelRaw(FRichCurve* InRichCurve, UObject* InOwner);`
- L95 _public prototype_ `virtual bool IsReadOnly() const override;`
- L97 _public prototype_ `void SetIsReadOnly(TAttribute<bool> InReadOnlyAttribute);`
- L100 _public function_ `virtual bool IsValid() const override` — FRichCurveEditorModel interface
- L101 _public prototype_ `virtual FRichCurve& GetRichCurve() override;`
- L102 _public prototype_ `virtual const FRichCurve& GetReadOnlyRichCurve() const override;`
- L105 _private member_ `FRichCurve* RichCurve;`
- L106 _private member_ `TAttribute<bool> ReadOnlyAttribute;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/SCurveEditorPanel.h` (Public)


#### class `SCurveEditorPanel`  
`class SCurveEditorPanel : public SCompoundWidget`  
_L61-449_
- inherits: `SCompoundWidget`
- desc: Curve editor widget that reflects the state of an FCurveEditor
- L63 _private function_ `SLATE_BEGIN_ARGS(SCurveEditorPanel) : _GridLineTint(FLinearColor(0.1f, 0.1f, 0.1f, 1.f)) , _MinimumViewPanelHeight(300.0f)`
- L69 _private prototype_ `SLATE_ATTRIBUTE(FLinearColor, GridLineTint) SLATE_ARGUMENT(TSharedPtr<FTabManager>, TabManager) SLATE_ARGUMENT(TSharedPtr<ITimeSliderController>, ExternalTimeSliderController) SLATE_ATTRIBUTE(FText, DisabledTimeSnapTooltip) SLATE_NAMED_SLOT(FArguments, TreeContent) SLATE_ARGUMENT(float, MinimumViewPanelHeight) SLATE_END_ARGS() SCurveEditorPanel();` — Color to draw grid lines
- L89 _private prototype_ `~SCurveEditorPanel();`
- L94 _private prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor);` — Construct a new curve editor panel widget
- L99 _private function_ `TSharedPtr<FUICommandList> GetCommands() const` — Access the combined command list for this curve editor and panel widget
- L107 _private function_ `TSharedPtr<class SCurveKeyDetailPanel> GetKeyDetailsView() const` — Access the details view used for editing selected keys
- L115 _private function_ `TSharedPtr<class SCurveEditorFilterPanel> GetFilterPanel() const` — Access the filter panel
- L123 _private function_ `TSharedPtr<class SCurveEditorToolProperties> GetToolPropertiesPanel() const` — Access the tool properties panel
- L128 _private prototype_ `void AddView(TSharedRef<SCurveEditorView> ViewToAdd);`
- L130 _private prototype_ `void RemoveView(TSharedRef<SCurveEditorView> ViewToRemove);`
- L136 _private prototype_ `TSharedPtr<FExtender> GetToolbarExtender();` — This returns an extender which is pre-configured with the standard set of Toolbar Icons. Implementers of SCurveEditorPanel should use this to generate the icons and then add any additional context-specific icons (such as save buttons in the Asset Editor) to ensure that the Curve Editor has a consistent set (and order) of icons across all usages.
- L139 _private prototype_ `const FGeometry& GetScrollPanelGeometry() const;` — Access the cached geometry of the outer scroll panel that contains this panel's views
- L142 _private prototype_ `const FGeometry& GetViewContainerGeometry() const;` — Access the cached geometry of container housing all this panel's views
- L145 _private prototype_ `TArrayView<const TSharedPtr<SCurveEditorView>> GetViews() const;` — Get all the views stored in this panel.
- L148 _private function_ `FLinearColor GetGridLineTint() const` — Get the grid line tint to be used for views on panel
- L151 _private prototype_ `void ScrollBy(float Amount);` — Scroll this panel's view scroll box vertically by the specified amount
- L160 _private function_ `TMultiMap<FCurveModelID, TSharedRef<SCurveEditorView>>::TConstKeyIterator FindViews(TRetainedRef<FCurveModelID> InCurveID)` — Find all the views that the specified curve is being displayed on @note: Returns an in-place iterator to this curve's view mapping. Adding or removing curves from views *will* invalidate this iterator. @param InCurveID The identifier of the curve to find views for @return An iterator to all the views that this cuvrve is displayed within.
- L168 _private prototype_ `void RemoveCurveFromViews(FCurveModelID InCurveID);` — Remove the specified curve from all views it is currently displayed on.
- L171 _private function_ `ECurveEditorViewID GetViewMode() const` — Get the last set View Mode for this UI. Utility function for the UI.
- L174 _private prototype_ `void PostUndo();` — Undo occurred, invalidate or update internal structures
- L177 _private prototype_ `void ResetMinMaxes();` — Reset Stored Min/Max's
- L180 _private prototype_ `void UpdateAxisSnapping();` — Update the axis snapping based on the settings.
- L183 _private member_ `FSimpleDelegate OnFilterClassChanged;` — Delegate for when the chosen filter class has changed
- L184 _private prototype_ `void FilterClassChanged();`
- L187 _private prototype_ `void EnablePendingFocusOnHovering(const bool InEnabled);` — Enable/disable pending focus
- L190 _private function_ `FSimpleMulticastDelegate& OnPostRebuildCurveViews()` — Broadcasts after the curve views have been rebuilt (by RebuildCurveViews).
- L194 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget Interface
- L198 _private function_ `virtual bool SupportsKeyboardFocus() const override` — ~ Keyboard interaction
- L199 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L200 _private prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L201 _private prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L204 _private prototype_ `TSharedPtr<FExtender> CombineEditorExtensions() const;` — @return Extender combining all ICurveEditorModule::GetAllToolBarMenuExtenders and the owning FCurveEditor's ICurveEditorExtensions.
- L206 _private prototype_ `void BuildToolbar(FToolBarBuilder& InToolBarBuilder, TSharedPtr<FExtender> InBaseExtender);` — Adds all base curve editor UI elements to ToolbarBuilder.
- L208 _private prototype_ `TSharedRef<SWidget> MakeTimeSnapMenu();`
- L209 _private prototype_ `FText GetTimeSnapMenuTooltip() const;`
- L211 _private prototype_ `TSharedRef<SWidget> MakeGridSpacingMenu();`
- L212 _private prototype_ `TSharedRef<SWidget> MakeAxisSnapMenu();`
- L214 _private prototype_ `bool IsInlineEditPanelEditable() const;`
- L215 _private prototype_ `EVisibility ShouldInstructionOverlayBeVisible() const;`
- L219 _private prototype_ `TSharedRef<SWidget> MakeToolsComboMenu(TSharedPtr<FExtender> InExtender);`
- L220 _private prototype_ `FText GetCurrentToolLabel() const;`
- L221 _private prototype_ `FText GetCurrentToolDescription() const;`
- L222 _private prototype_ `FSlateIcon GetCurrentToolIcon() const;`
- L227 _private prototype_ `TSharedRef<SWidget> MakeTangentModeMenu();` — Tangent mode toolbar combo button
- L228 _private prototype_ `FText GetTangentModeLabel() const;`
- L229 _private prototype_ `FText GetTangentModeTooltip() const;`
- L230 _private prototype_ `FSlateIcon GetTangentModeIcon() const;`
- L247 _private prototype_ `ETangentModeComboState DetermineTangentMode() const;`
- L254 _private prototype_ `EVisibility GetSplitterVisibility() const;` — Get the visibility for the value splitter control
- L257 _private prototype_ `void UpdateTime();` — ~ Event bindings
- L258 _private prototype_ `void UpdateEditBox();`
- L261 _private prototype_ `TSharedRef<SWidget> MakeCurveEditorCurveViewOptionsMenu(TSharedPtr<FExtender> InExtender);` — Creates the drop-down list you see when changing Curve View options.
- L263 _private prototype_ `TSharedRef<SWidget> MakeCurvesMenu(TSharedPtr<FExtender> InExtender);` — Creates the drop-down for changing curves on a whole.
- L264 _private prototype_ `void AddPreInfinityToMenu(FMenuBuilder& InMenuBuilder);`
- L265 _private prototype_ `void AddPostInfinityToMenu(FMenuBuilder& InMenuBuilder);`
- L266 _private prototype_ `FSlateIcon GetCurveExtrapolationPreIcon() const;`
- L267 _private prototype_ `FSlateIcon GetCurveExtrapolationPostIcon() const;`
- L270 _private prototype_ `void ShowCurveFilterUI(TSubclassOf<UCurveEditorFilterBase> FilterClass);` — Creates the Curve Editor Filter UI and pre-populates it with the specified class.
- L277 _private prototype_ `void BindCommands();` — Bind command mappings for this widget
- L280 _private prototype_ `void HandleSetKeyAttributesCommand(FKeyAttributes InKeyAttributes, FText InDescription);` — Assign new attributes to the currently selected keys
- L282 _private prototype_ `void SetKeyAttributesOnSelection(const FKeyAttributes& InKeyAttributes, const FText& InDescription) const;` — Sets the key attributes on all selected keys.
- L284 _private prototype_ `void SetKeyAttributesOnAllCurves(const FKeyAttributes& InKeyAttributes, const FText& InDescription) const;` — Sets the key attributes on all keys.
- L289 _private prototype_ `void SetCurveAttributes(FCurveAttributes CurveAttributes, FText Description);` — Assign new curve attributes to all visible curves
- L292 _private prototype_ `bool CompareCommonInterpolationMode(ERichCurveInterpMode InterpMode) const;` — Compare all the currently selected keys' interp modes against the specified interp mode
- L295 _private prototype_ `bool CompareCommonTangentMode(ERichCurveInterpMode InterpMode, ERichCurveTangentMode TangentMode) const;` — Compare all the currently selected keys' tangent modes against the specified tangent mode
- L298 _private prototype_ `bool CompareCommonTangentWeightMode(ERichCurveInterpMode InterpMode, ERichCurveTangentWeightMode TangentWeightMode) const;` — Compare all the currently selected keys' tangent modes against the specified tangent mode
- L301 _private prototype_ `bool CompareCommonPreExtrapolationMode(ERichCurveExtrapolation PreExtrapolationMode) const;` — Compare all the visible curves' pre-extrapolation modes against the specified extrapolation mode
- L304 _private prototype_ `bool CompareCommonPostExtrapolationMode(ERichCurveExtrapolation PostExtrapolationMode) const;` — Compare all the visible curves' post-extrapolation modes against the specified extrapolation mode
- L309 _private prototype_ `void ToggleWeightedTangents();` — Toggle weighted tangents on the current selection
- L314 _private prototype_ `bool CanToggleWeightedTangents() const;` — Check whether we can toggle weighted tangents on the current selection
- L319 _private prototype_ `bool CanSetKeyInterpolation() const;` — Check whether or not we can set a key interpolation on the current selection. If no keys are selected, you can't set an interpolation!
- L322 _private prototype_ `void SetAxisSnapping(ECurveEditorSnapAxis);` — Sets the axis snapping to the specified value. Only supports X, Y and None.
- L325 _private function_ `TSharedPtr<FCurveEditor> GetCurveEditor() const` — Get a reference to the curve editor this panel represents.
- L327 _private function_ `float GetColumnFillCoefficient(int32 ColumnIndex) const`
- L334 _private prototype_ `void OnColumnFillCoefficientChanged(float FillCoefficient, int32 ColumnIndex);` — Called when a column fill percentage is changed by a splitter slot.
- L336 _private prototype_ `void OnSplitterFinishedResizing();`
- L348 _private prototype_ `TSharedPtr<SCurveEditorView> CreateViewOfType(FCurveModelID CurveModelID, ECurveEditorViewID ViewTypeID, bool bPinned);` — Create a new view for a model of the specified type, and add the curve to the view @param CurveModelID The ID of the curve we're creating a view for @param ViewTypeID   The ID of the view we'd like to create @param bPinned      Whether the view should be pinned or not @return A new view or nullptr if one could not be created
- L353 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;` — The curve editor pointer
- L356 _private member_ `TMultiMap<FCurveModelID, TSharedRef<SCurveEditorView>> CurveViews;` — Map from curve model ID to the views that it is on
- L359 _private member_ `TSet<TSharedRef<SCurveEditorView>> ExternalViews;` — Set of externally added views
- L362 _private member_ `TOptional<FCurveEditorDelayedDrag> DragOperation;` — (Optional) the current drag operation
- L365 _private member_ `TPimplPtr<UE::CurveEditor::FSharedCurveInfoModel> SharedCurveInfo;` — Keeps track about information that is equal for all selected keys, or all keys if none are selected.
- L368 _private member_ `TAttribute<FLinearColor> GridLineTintAttribute;` — Attribute used for retrieving the desired grid line color
- L371 _private member_ `TAttribute<FText> DisabledTimeSnapTooltipAttribute;` — Attribute used for retrieving the tooltip for when the Time Snap control is disabled. Specifying this causes the Time Snap Adjustment to be disabled.
- L374 _private member_ `TSharedPtr<SCurveKeyDetailPanel> KeyDetailsView;` — Edit panel
- L377 _private member_ `TSharedPtr<SCurveEditorFilterPanel> FilterPanel;` — Filter panel
- L380 _private member_ `TSharedPtr<SCurveEditorToolProperties> ToolPropertiesPanel;` — Tool options panel
- L383 _private member_ `TMap<FCurveModelID, TSharedPtr<SWidget>> CurveToEditUI;` — Map of edit UI widgets for each curve in the current selection set
- L386 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for widget specific command bindings
- L389 _private member_ `TUniquePtr<UE::CurveEditor::FPromotedFilterCommandBinder> ToolbarPromotedFilterBinder;` — Binds commands from FPromotedFilterContainer so the filters surfaced from SCurveEditorFilterPanel show up in the toolbar.
- L392 _private member_ `uint32 CachedSelectionSerialNumber;` — Cached serial number from the curve editor selection. Used to update edit UIs when the selection changes.
- L397 _private prototype_ `void SetViewMode(const ECurveEditorViewID NewViewMode);` — Sets the View Mode for the UI to the specified mode. This will destroy and re-create all views, but leave additional pinned views unmodified.
- L400 _private prototype_ `bool CompareViewMode(const ECurveEditorViewID InViewMode) const;` — Compare if our current view mode matches the specified one. Utility function for the UI.
- L403 _private prototype_ `void RebuildCurveViews();` — Rebuild the Curve Views layout to match the currently specified View Mode.
- L406 _private prototype_ `void OnCurveEditorToolChanged(FCurveEditorToolID InToolId);` — Reconstructs the properties widget on tool switch
- L409 _private member_ `double LastOutputMin = DBL_MAX;` — Last Output Min and Max values for the views
- L410 _private member_ `double LastOutputMax = DBL_MIN;`
- L413 _private member_ `ECurveEditorViewID DefaultViewID;` — The last set View Mode for this UI.
- L416 _private member_ `FSimpleMulticastDelegate OnPostRebuildCurveViewsDelegate;` — Broadcasts after the curve views have been rebuilt (by RebuildCurveViews).
- L418 _private member_ `TMultiMap<ECurveEditorViewID, TSharedRef<SCurveEditorView>> FreeViewsByType;`
- L421 _private member_ `TSharedPtr<SScrollBox> ScrollBox;` — The scrool box that all curve views live inside
- L424 _private member_ `TSharedPtr<SCurveEditorViewContainer> CurveViewsContainer;` — The container for all our vertically laid out curve views.
- L429 _private member_ `FPendingWidgetFocus PendingFocus;` — Pending focus handler
- L432 _private member_ `bool bNeedsRefresh;` — Whether to explicitly refresh the views for this panel
- L435 _private member_ `uint32 CachedActiveCurvesSerialNumber;` — Serial number cached from FCurveEditor::GetActiveCurvesSerialNumber() on tick
- L438 _private member_ `FGeometry CachedViewGeometry;` — A copy of the View Geometry used to represent the View portion of the Curve Editor.
- L441 _private member_ `float ColumnFillCoefficients[2];` — The fill coefficients of each column in the grid.
- L443 _private member_ `TSharedPtr<class SSplitter> TreeViewSplitter;`
- L446 _private member_ `TUniquePtr<FCurveEditorEditObjectContainer> EditObjects;` — Container of objects that are being used to edit keys on the curve editor
- L448 _private member_ `TWeakPtr<FTabManager> WeakTabManager;`

#### enum `SCurveEditorPanel::ETangentModeComboState`  
`enum class ETangentModeComboState : uint8`  
_L232-246_
- L235 _public enumerator_ `Constant` — All keys in selection share the following mode:
- L236 _public enumerator_ `Linear`
- L237 _public enumerator_ `CubicAuto`
- L238 _public enumerator_ `CubicSmartAuto`
- L239 _public enumerator_ `CubicUser`
- L240 _public enumerator_ `CubicBreak`
- L243 _public enumerator_ `Mixed` — The keys are mixed
- L245 _public enumerator_ `NoKeys` — There are no keys in view so nothing can be set.

#### Free symbols / members of external scopes

- L32 _macro_ `#define UE_API CURVEEDITOR_API`
- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace CurveEditor` (scope `UE`)
- L56 _namespace_ `namespace UE`
- L56 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/SCurveEditorToolProperties.h` (Public)


#### class `SCurveEditorToolProperties`  
`class SCurveEditorToolProperties : public SCompoundWidget`  
_L19-58_
- inherits: `SCompoundWidget`
- desc: Widget to show curve editor tool extension properties
- L22 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorToolProperties)`
- L27 _public function_ `SCurveEditorToolProperties() : ToolId(FCurveEditorToolID::Unset())`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor, FCurveEditorToolID ToolId);`
- L35 _public prototype_ `void OnToolChanged(FCurveEditorToolID NewToolId);` — Called when the curve editor tool changes Sets the new tool ID and rebuilds the details view
- L38 _public function_ `TSharedPtr<class IStructureDetailsView> GetStructureDetailsView() const` — The details view for tool properties
- L46 _private prototype_ `void RebuildProperties();` — Rebuilds details view Called either by the tool itself when it's properties change or when the curve editor tool changes
- L52 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);` — Called when the user enters in a new value for one of the properties Calls OnToolOptionsUpdated on the current tool
- L55 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;`
- L56 _private member_ `TSharedPtr<IStructureDetailsView> DetailsView;`
- L57 _private member_ `FCurveEditorToolID ToolId;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/SCurveEditorView.h` (Public)


#### struct `FCurveEditorViewAxisID`  
`struct FCurveEditorViewAxisID`  
_L41-94_
- desc: Identifier for a specific axis on a view. These identifiers are transient and should not be stored externally.
- L43 _public function_ `FCurveEditorViewAxisID() : Index(std::numeric_limits<uint8>::max())`
- L46 _public function_ `explicit FCurveEditorViewAxisID(uint8 InIndex) : Index(InIndex)`
- L52 _public function_ `explicit operator bool() const`
- L79 _private function_ `operator int32() const`
- L85 _private function_ `FCurveEditorViewAxisID& operator=(int32 InIndex)`
- L93 _private member_ `uint8 Index;`

#### class `SCurveEditorView`  
`class SCurveEditorView : public SCompoundWidget`  
_L120-515_
- inherits: `SCompoundWidget`
- desc: This is the base widget type for all views that exist on a curve editor panel. A view may contain 0 or more curves (stored in CurveInfoByID). SCurveEditorViews are directly housed within a single SCurveEditorViewContainer which arranges each view vertically in order. View types: A view may have a centrally registered ID (See FCurveEditorViewRegistry and FCurveModel::GetSupportedViews) which allows any external curve model type to express support for any other view type. 3 built-in views are provided: Absolute:   Shows 1 or more curves on a single 2D-scrollable grid using a single zoomable view-space. Normalized: Shows 1 or more curves on a single grid scrollable horizontally with all curves normalized to the extents of the view Stacked:    Shows 1 or more curves on separate fixed-height grids scrollable horizontally each curve normalized to the extents of its own grid Unregistered curve views may still be added to the view by calling SCurveEditorPanel::AddView Space Transformations: Views must define a valid 2-dimensional space (ViewSpace) that is used to convert from a pixel position to the virtual view space. Views may additionally implement per-curve transformations from view space to curve space, to allow for specific layouts/scales of curves within them. Per-curve transforms are stored inside FCurveInfo::ViewToCurveTransform Sizing: Views may be size in one of 2 ways: * Auto sized (bAutoSize=true): views derive their height from the widget's desired size; * Stretched (bA
- L127 _public prototype_ `SCurveEditorView();` — Default constructor
- L128 _public prototype_ `~SCurveEditorView();`
- L133 _public prototype_ `FCurveEditorScreenSpace GetViewSpace() const;` — Get the default screen space ultility that defines this view's input, output and pixel metrics
- L138 _public prototype_ `FCurveEditorScreenSpace GetViewSpace(const FName& InHorizontalAxis, const FName& InVerticalAxis) const;` — Get the screen space ultility that defines this view's input, output and pixel metrics for the specified axis combination
- L144 _public prototype_ `FCurveEditorScreenSpace GetCurveSpace(FCurveModelID CurveID) const;` — Get the screen space ultility that defines the specified curves's input, output and pixel metrics. The resulting struct defines the transformation from this view's widget pixel space to the curve input/output space
- L147 _public prototype_ `FTransform2d GetViewToCurveTransform(FCurveModelID CurveID) const;` — @return The transform used to translate view space (absolute key coordinates) to the curve space (e.g. 0-1 range in normalized view).
- L152 _public prototype_ `FCurveEditorScreenSpaceH GetHorizontalAxisSpace(FCurveEditorViewAxisID ID) const;` — Retrieve the horizontal screen-space information for the specified axis
- L157 _public prototype_ `FCurveEditorScreenSpaceV GetVerticalAxisSpace(FCurveEditorViewAxisID ID) const;` — Retrieve the vertical screen-space information for the specified axis
- L162 _public prototype_ `FCurveEditorViewAxisID GetAxisForCurve(FCurveModelID CurveID, ECurveEditorAxisOrientation AxisOrientation) const;` — Retrueve the axis ID assigned to the specified curve and orientation
- L167 _public prototype_ `TSharedPtr<FCurveEditorAxis> GetAxis(FCurveEditorViewAxisID ID, ECurveEditorAxisOrientation AxisOrientation) const;` — Retrueve the axis associated with the specified ID and orientation
- L172 _public function_ `bool ShouldAutoSize() const` — Check whether this view should auto size to fit its FixedHeight or child slot content
- L180 _public function_ `bool IsInteractive() const` — Check whether this view can be interacted with. This should be checked by any tool or edit mode attempting to manipulated curves on this view.
- L188 _public function_ `bool HasCapacity() const` — Check whether this view has space for any more curves
- L196 _public function_ `int32 NumCurves() const` — Retrieve the number of curves that exist on this view
- L204 _public prototype_ `void GetInputBounds(double& OutInputMin, double& OutInputMax) const;` — Retrieve this view's input bounds, accounting for any offsets or padding from the outer container
- L209 _public function_ `double GetOutputMin() const` — Retrieve this view's minimum output bound in view space
- L217 _public function_ `double GetOutputMax() const` — Retrieve this view's maximum output bound in view space
- L225 _public prototype_ `void SetOutputBounds(double InOutputMin, double InOutputMax, FCurveEditorViewAxisID AxisID = FCurveEditorViewAxisID());` — Set this view's output bounds
- L230 _public prototype_ `void SetInputBounds(double InInputMin, double InInputMax, FCurveEditorViewAxisID AxisID = FCurveEditorViewAxisID());` — Set this view's input bounds
- L237 _public prototype_ `void Zoom(const FVector2D& Amount);` — Zoom this view in or out around its center point @param Amount       The amount to zoom by horizontally and vertically as a factor of the current size
- L246 _public prototype_ `void ZoomAround(const FVector2D& Amount, double InputOrigin, double OutputOrigin);` — Zoom this view in or out around the specified point @param Amount       The amount to zoom by horizontally and vertically as a factor of the current size @param TimeOrigin   The time origin to zoom around @param ValueOrigin  The value origin to zoom around
- L249 _public prototype_ `virtual void CheckCacheAndInvalidateIfNeeded();` — This should be called every tick by an owning widget, to see if the cache is valid, which will then recreate it and invalidate widget
- L252 _public function_ `virtual void UpdateViewToTransformCurves()` — `UE_DEPRECATED(5.3, "Use UpdateViewToTransformCurves(double InputMin, double InputMax) instead.")`
- L255 _public function_ `virtual void UpdateViewToTransformCurves(double InputMin, double InputMax)` — Function to make sure to update the view to the transform curves, we need to do this before we cache
- L258 _public prototype_ `virtual void FrameVertical(double InOutputMin, double InOutputMax, FCurveEditorViewAxisID AxisID = FCurveEditorViewAxisID());` — Frame the view vertially by the input and output bounds, peformaing any custom clipping as needed
- L261 _public prototype_ `virtual void FrameHorizontal(double InInputMin, double InInputMax, FCurveEditorViewAxisID AxisID = FCurveEditorViewAxisID());` — Frame the view horizontall by the input and output bounds, peformaing any custom clipping as needed
- L264 _public prototype_ `TSharedPtr<FCurveEditor> GetCurveEditor() const;` — Returns the cure editor associated with this view, or nullptr if the view is not specific to a curve editor
- L267 _public prototype_ `UE::CurveEditor::FOnCurveHasChangedExternally& OnCurveHasChangedExternally();` — Invoked when we detect that a curve needs to be redrawn, i.e. when FCurveModel::HasChangedAndResetTest returns true.
- L278 _public function_ `virtual bool GetPointsWithinWidgetRange(const FSlateRect& WidgetRectangle, TArray<FCurvePointHandle>* OutPoints) const` — Retrieve all the curve points that overlap the specified rectangle in widget space @param WidgetRectangle  The rectangle to hit test against. May not hit points that would exist outside of the view's visible bounds. @param OutPoints        (required) pointer to an array to populate with overlapping points @return Whether any points were within the widget range
- L288 _public function_ `virtual bool GetCurveWithinWidgetRange(const FSlateRect& WidgetRectangle, TArray<FCurvePointHandle>* OutPoints) const` — Retrieve all the curve points, if any of the interpolating points overlap the specified rectangle in widget space @param WidgetRectangle  The rectangle to hit test against. May not hit points that would exist outside of the view's visible bounds. @param OutPoints        (required) pointer to an array to populate with overlapping points @return Whether any points were within the widget range
- L300 _public function_ `bool GetPointsThenCurveWithinWidgetRange(const FSlateRect& WidgetRectangle, TArray<FCurvePointHandle>* OutPoints) const` — Tries to retrieve all curve points that overlap the rectangle. If no points are found, selects the overlapping curves instead. @param WidgetRectangle  The rectangle to hit test against. May not hit points that would exist outside of the view's visible bounds. @param OutPoints        (required) pointer to an array to populate with overlapping points @return Whether anything was selected.
- L308 _public function_ `virtual TOptional<FCurveModelID> GetHoveredCurve() const` — Retrieve the id of the hovered curve
- L313 _public function_ `virtual void BindCommands()` — Bind UI commands for this view
- L320 _public function_ `virtual void OnCurveListChanged()` — Invoked when a curve has been added or removed from this list. @note: Care should be taken here to not impede performance as this will get called each time a curve is added/removed
- L326 _public function_ `virtual bool IsTimeSnapEnabled() const` — Should the tools respect the global snapping rules for Time (X axis) input when manipulating a curve in this view. Can be set to false to ignore the snap setting.
- L334 _public function_ `virtual bool IsValueSnapEnabled() const` — Should the tools respect the global snapping rules for Value (Y axis) input when manipulating a curve in this view. Can be set to false to ignore the snap setting.
- L339 _public function_ `virtual void GetGridLinesX(TSharedRef<const FCurveEditor> CurveEditor, TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels = nullptr) const`
- L340 _public function_ `virtual void GetGridLinesY(TSharedRef<const FCurveEditor> CurveEditor, TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels = nullptr) const`
- L343 _public prototype_ `void RefreshRetainer();` — Request a new render from the retainer widget
- L346 _public prototype_ `void UpdateCustomAxes();` — Update the custom axes if necessary
- L351 _protected prototype_ `void InitCurveEditorReference(const TSharedRef<FCurveEditor>& InCurveEditor);` — Inits this view with the curve editor and sets up required callbacks.
- L355 _protected prototype_ `void GetCurveDrawParams(TArray<FCurveDrawParams>& OutDrawParams);` — `UE_DEPRECATED(5.6, "Instead use the CurveDrawParamsCache, use FCurveDrawParamsCache::GetCurveDrawParamsSynchronous to get Curve Draw Parms as with this function.")` — Gets info about the curves being drawn. Converts actual curves into an abstract series of lines/points/handles/etc.
- L359 _protected prototype_ `void GetCurveDrawParam(TSharedPtr<FCurveEditor>& CurveEditor, const FCurveModelID& ModelID, FCurveModel* CurveModel, FCurveDrawParams& OutDrawParam) const;` — `UE_DEPRECATED(5.6, "Instead use GetCurveDrawParamsCache, use FCurveDrawParamsCache::GetCurveDrawParamSynchronous to get Curve Draw Parm as with this function.")` — Gets curve draw params  get the cache by calling a single curve
- L362 _protected prototype_ `void UpdateCurveViewTransformsFromModels();` — Update all the curve view transforms from curve models
- L365 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L366 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L374 _private prototype_ `void AddCurve(FCurveModelID CurveID);` — Add a curve to this view
- L377 _private prototype_ `void RemoveCurve(FCurveModelID CurveID);` — Add a curve from this view
- L382 _public member_ `uint8 bPinned : 1;` — (Default: false) When true, this view has been pinned to the top of the view container. Only takes affect from the next call to SCurveEditorPanel::RebuildCurveViews.
- L384 _public member_ `uint8 bInteractive : 1;` — (Default: true) When true, this view should accept interactive operations such as drags and tool interaction
- L386 _public member_ `uint8 bFixedOutputBounds : 1;` — (Default: false) When true, this view has fixed vertical bounds that should never be changed by zooming or panning
- L388 _public member_ `uint8 bAutoSize : 1;` — (Default: true) See class notes - defines whether this view should size to its desired size (true) or stretch to the height of the panel (false). Only takes affect from the next call to SCurveEditorPanel::RebuildCurveViews.
- L390 _public member_ `uint8 bAllowEmpty : 1;` — (Default: false) Defines whether this view should remain on the panel UI even if it does not represent any curves.
- L392 _public member_ `uint8 bAllowModelViewTransforms : 1;` — (Default: false) When true, custom axes need to be rebuilt before use.
- L394 _public member_ `uint8 bUpdateModelViewTransforms : 1;` — (Default: false) When true, custom axes need to be rebuilt before use.
- L396 _public member_ `uint8 bNeedsDefaultGridLinesH : 1;` — (Default: true) When true, this view has models that need the default grid lines drawing.
- L398 _public member_ `uint8 bNeedsDefaultGridLinesV : 1;` — (Default: true) When true, this view has models that need the default grid lines drawing.
- L401 _public member_ `int8 SortBias = 0;` — (Default: 0) Should be assigned on Construction of derived types. Defines a custom sort bias to use when sorting the stack of views (before sorting by pinned/unpinned state)
- L404 _public member_ `ECurveEditorViewID ViewTypeID = ECurveEditorViewID::Invalid;` — This view's type identifier. Assigned by the curve editor panel after construction.
- L407 _public member_ `int32 RelativeOrder = TNumericLimits<int32>::Max();` — Transient integer that is assigned each time the view container order is changed, to guarantee relative ordering of views when the list changes
- L410 _public member_ `int32 MaximumCapacity = 0;` — The maximum number of curves allowed on this view, or 0 for no limit
- L413 _public member_ `TAttribute<float> FixedHeight;` — (Optional) Attribute that defines a fixed height for this view. Overrides ChildSlot's desired size when set
- L418 _protected member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — The curve editor associated with this view.
- L421 _protected member_ `double OutputMin = 0.0;` — This view's minimum visible output value
- L424 _protected member_ `double OutputMax = 1.0;` — This view's maximum visible output value
- L438 _protected member_ `TSortedMap<FCurveModelID, FCurveInfo, TInlineAllocator<1>> CurveInfoByID;` — Map from curve identifier to specific info pertaining to that curve for this view. @note: Should only be added to or removed from in AddCurve/RemoveCurve. Derived types must only change the FCurveInfo contained within this map.
- L448 _protected member_ `TArray<FAxisInfo> CustomHorizontalAxes;`
- L449 _protected member_ `TArray<FAxisInfo> CustomVerticalAxes;`
- L451 _protected function_ `FAxisInfo& GetHorizontalAxisInfo(FCurveEditorViewAxisID ID)`
- L456 _protected function_ `FAxisInfo& GetVerticalAxisInfo(FCurveEditorViewAxisID ID)`
- L473 _protected member_ `ECurveCacheFlags CurveCacheFlags;` — `UE_DEPRECATED(5.6, "Instead use the CurveDrawParamsCache, call FCurveDrawParamsCache::GetCurveCacheFlags to get current flags. Use FCurveDrawParamsCache::Update to update them.")` — Curve cache flags that change based upon data or view getting modified
- L478 _protected member_ `TArray<FCurveDrawParams> CachedDrawParams;` — `UE_DEPRECATED(5.5, "Instead use the CurveDrawParamsCache, call GetCurveDrawParamsSynchronous.")` — Curve draw parameters that are re-generated on tick if the cache has changed. We generate them once and then they're used in multiple places per frame.
- L481 _protected member_ `TSharedPtr<UE::CurveEditor::FCurveDrawParamsCache> CurveDrawParamsCache;` — Cache for curve draw params
- L504 _protected member_ `FCachedValuesToCheck CachedValues;` — `UE_DEPRECATED(5.6, "Instead use the CurveDrawParamsCache, use FCurveDrawParamsCache::GetCurveEditorData to get cached values. Use FCurveDrawParamsCache::Update to update them.")`
- L508 _protected member_ `TSharedPtr<SRetainerWidget> RetainerWidget;` — Possible pointer to a retainer widget that we may need to force update
- L511 _public function_ `void SetRetainerWidget(TSharedPtr<SRetainerWidget>& InWidget)`

#### struct `SCurveEditorView::FCurveInfo`  
`struct FCurveInfo`  
_L426-433_
- L429 _public member_ `int32 CurveIndex;` — The linear index of the curve within this view determined by the order curves were added.
- L430 _public member_ `FTransform2d ViewToCurveTransform;`
- L431 _public member_ `FCurveEditorViewAxisID HorizontalAxis;`
- L432 _public member_ `FCurveEditorViewAxisID VerticalAxis;`

#### struct `SCurveEditorView::FAxisInfo`  
`struct FAxisInfo`  
_L440-446_
- L442 _public member_ `TSharedPtr<FCurveEditorAxis> Axis;`
- L443 _public member_ `double Min = 0.0;`
- L444 _public member_ `double Max = 1.0;`
- L445 _public member_ `int32 UseCount = 0;`

#### enum `SCurveEditorView::ECurveCacheFlags`  
`enum class UE_DEPRECATED(5.6, "Instead use the CurveDrawParamsCache, call FCurveDrawParamsCache::ECurveCacheFlags to get a corresponding type.") ECurveCacheFlags : uint8`  
_L464-468_
- desc: Flag enum signifying how the curve cache has changed since it was last generated Note for a data change it may only effect certain data(curves) not every drawn curve
- L466 _public enumerator_ `CheckCurves = 0` — The cache may be valid need to check each curve to see if they are still valid
- L467 _public enumerator_ `All = 1 << 0` — Get all

#### struct `SCurveEditorView::FCachedValuesToCheck`  
`struct UE_DEPRECATED(5.6, "Instead use the CurveDrawParamsCache, call FCurveDrawParamsCache::FCachedCurveEditorData to get a corresponding type.") FCachedValuesToCheck`  
_L484-500_
- desc: Set of Cached values we need to check each tick to see if we need to redo cache
- L487 _public member_ `uint32 CachedActiveCurvesSerialNumber;` — Serial number cached from FCurveEditor::GetActiveCurvesSerialNumber() on tick
- L490 _public member_ `uint32 CachedSelectionSerialNumber;` — Serial number bached from CurveEditorSelecstion::GetSerialNumber
- L493 _public member_ `ECurveEditorTangentVisibility CachedTangentVisibility;` — Cached Tangent Visibility
- L496 _public member_ `double CachedInputMin, CachedInputMax, CachedOutputMin, CachedOutputMax;` — Cached input and output min max values to see if we need to recalc curves, though we need to poll it's safer
- L496 _public member_ `double CachedInputMin, CachedInputMax, CachedOutputMin, CachedOutputMax;` — Cached input and output min max values to see if we need to recalc curves, though we need to poll it's safer
- L496 _public member_ `double CachedInputMin, CachedInputMax, CachedOutputMin, CachedOutputMax;` — Cached input and output min max values to see if we need to recalc curves, though we need to poll it's safer
- L496 _public member_ `double CachedInputMin, CachedInputMax, CachedOutputMin, CachedOutputMax;` — Cached input and output min max values to see if we need to recalc curves, though we need to poll it's safer
- L499 _public member_ `FVector2D CachedGeometrySize;` — Cached Geometry Size

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API CURVEEDITOR_API`
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace CurveEditor` (scope `UE`)
- L57 _function_ `friend uint32 GetTypeHash(FCurveEditorViewAxisID In)`
- L62 _function_ `friend bool operator==(FCurveEditorViewAxisID A, FCurveEditorViewAxisID B)`
- L67 _function_ `friend bool operator!=(FCurveEditorViewAxisID A, FCurveEditorViewAxisID B)`
- L72 _function_ `friend bool operator<(FCurveEditorViewAxisID A, FCurveEditorViewAxisID B)`

### `Source/Editor/CurveEditor/Public/SCurveKeyDetailPanel.h` (Public)


#### class `SCurveKeyDetailPanel`  
`class SCurveKeyDetailPanel : public SCompoundWidget`  
_L20-40_
- inherits: `SCompoundWidget`
- desc: Inline details panel that lets you edit the Time and Value of a generic FCurveEditor Key
- L23 _public function_ `SLATE_BEGIN_ARGS(SCurveKeyDetailPanel)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor);`
- L29 _public function_ `TSharedPtr<IPropertyRowGenerator> GetPropertyRowGenerator() const`
- L32 _private prototype_ `void PropertyRowsRefreshed();`
- L33 _private prototype_ `void ConstructChildLayout(TSharedPtr<SWidget> TimeWidget, TSharedPtr<SWidget> ValueWidget);`
- L36 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L38 _private member_ `TSharedPtr<SWidget> TempTimeWidget;`
- L39 _private member_ `TSharedPtr<SWidget> TempValueWidget;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/SCurveViewerPanel.h` (Public)


#### class `SCurveViewerPanel`  
`class SCurveViewerPanel : public SCurveEditorView`  
_L29-68_
- inherits: `SCurveEditorView`
- desc: Curve viewer widget that reflects the state of an FCurveEditor
- L31 _private function_ `SLATE_BEGIN_ARGS(SCurveViewerPanel)`
- L33 _private prototype_ `SLATE_ATTRIBUTE(float, CurveThickness) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FCurveEditor> InCurveEditor);`
- L45 _private function_ `const TArray<FCurveDrawParams>& GetCachedDrawParams() const` — Access the draw parameters that this curve editor has cached for this frame
- L52 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L53 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L60 _public prototype_ `void DrawCurves(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, ESlateDrawEffect DrawEffects) const;` — Draw curve data
- L64 _private member_ `TArray<FCurveDrawParams> CachedDrawParams;` — Curve draw parameters that are re-generated on tick
- L67 _private member_ `TAttribute<float> CurveThickness;` — Thickness of the displayed curve

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/SGridLineSpacingList.h` (Public)


#### class `SGridLineSpacingList`  
`class SGridLineSpacingList : public SCompoundWidget`  
_L23-188_
- inherits: `SCompoundWidget`
- desc: A widget which creates a list of pre-determined numbers and a spot to enter a custom number. Similar to SNumericList but without the dropdown menu.
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnValueChanged, TOptional<float> );`
- L66 _public function_ `SLATE_BEGIN_ARGS( SGridLineSpacingList ) : _DropDownValues() , _MinDesiredValueWidth( 40) , _bShowNamedValue(true)`
- L73 _public function_ `SLATE_ARGUMENT( TArray<FNamedValue>, DropDownValues ) SLATE_ATTRIBUTE( float, MinDesiredValueWidth ) SLATE_ATTRIBUTE( TOptional<float>, Value ) SLATE_ATTRIBUTE(bool, bShowNamedValue) SLATE_ATTRIBUTE( FText, HeaderText) SLATE_EVENT( FOnValueChanged, OnValueChanged ) SLATE_END_ARGS() void Construct( const FArguments& InArgs )` — The values which are used to populate the drop down menu.
- L129 _private function_ `void AddMenuEntry(FMenuBuilder& MenuBuilder, const FNamedValue& Info)`
- L145 _private function_ `bool IsSameValue(TOptional<float> InValue) const`
- L151 _private function_ `FText GetValueText() const` — Get the value text for displaying in the custom entry box. We use a textbox here so we can show actual names from the original list if possible.
- L167 _private function_ `void ValueTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit)`
- L177 _private function_ `void SetValue( TOptional<float> InValue )`
- L184 _private member_ `TArray<FNamedValue> DropDownValues;`
- L185 _private member_ `TAttribute<bool> bShowNamedValue;`
- L186 _private member_ `TAttribute<TOptional<float>> Value;`
- L187 _private member_ `FOnValueChanged OnValueChanged;`

#### class `SGridLineSpacingList::FNamedValue`  
`class FNamedValue`  
_L30-63_
- desc: Represents a named numeric value for display in the drop down menu.
- L37 _public function_ `FNamedValue( TOptional<float> InValue, FText InName, FText InDescription )` — Creates a new FNamedValue @InValue The numeric value to be assigned @InName The display text for the value in the UI @InDescription The description of the value used in tooltips or wherever a longer description is needed.
- L44 _public function_ `TOptional<float> GetValue() const`
- L49 _public function_ `FText GetName() const`
- L54 _public function_ `FText GetDescription() const`
- L60 _private member_ `TOptional<float> Value;`
- L61 _private member_ `FText Name;`
- L62 _private member_ `FText Description;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_OneParam( FOnValueChanged, TOptional<float> );`

### `Source/Editor/CurveEditor/Public/Selection/ScopedSelectionChangeEventSuppression.h` (Public)


#### class `UE::CurveEditor::FScopedSelectionChangeEventSuppression`  
`class FScopedSelectionChangeEventSuppression : public FNoncopyable`  
_L36-47_
- inherits: `FNoncopyable`
- desc: Prevents FCurveEditorSelection::OnSelectionChanged from being broadcast while the constructed scope is open. Once all scopes end, and if changes to selection have been made, FCurveEditorSelection::OnSelectionChanged is broadcast exactly once. Nesting FScopedSelectionChangeEventSuppression is supported. This is an optimization if you are going to make multiple changes to selection and want the delegate to be broadcast after you're done. Example usage: TSharedRef<FCurveEditor> MyCurveEditor = ...; { FScopedSelectionChangeEventSuppression SuppressChangeEvents(MyCurveEditor); MyCurveEditor->Selection.Toggle(FooCurveId, ECurvePointType::Key, FooKeyHandle); // Normally this would invoke OnSelectionChanged. MyCurveEditor->Selection.Toggle(BarCurveId, ECurvePointType::Key, BarKeyHandle); // So would this { FScopedSelectionChangeEventSuppression AnotherChange(MyCurveEditor); MyCurveEditor->Selection.Toggle(BazCurveId, ECurvePointType::Key, BazKeyHandle); //~ FCurveEditorSelection::OnSelectionChanged not invoked due to the outer scope. } // ~FScopedSelectionChangeEventSuppression will now invoke FCurveEditorSelection::OnSelectionChanged once exactly. }
- L40 _public prototype_ `explicit FScopedSelectionChangeEventSuppression(const TSharedRef<FCurveEditor>& InCurveEditor);`
- L41 _public prototype_ `~FScopedSelectionChangeEventSuppression();`
- L46 _private member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — Handles the case of curve editor being destroyed during the scope, which should not happen but we handle for safety.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CURVEEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditor` (scope `UE`)

### `Source/Editor/CurveEditor/Public/Tree/CurveEditorTree.h` (Public)


#### enum `ECurveEditorTreeFilterState`  
`enum class ECurveEditorTreeFilterState : uint8`  
_L28-46_
- desc: Enumeration of bitmask values specifying how a specific tree item is interpreted by the current set of filters
- L31 _public enumerator_ `NoMatch = 0x00` — The item did not match any filter, and neither did any of its parents or children
- L34 _public enumerator_ `ImplicitChild = (1<<0)` — One of this item's parents matched a filter (ie it resides within a matched item)
- L37 _public enumerator_ `ImplicitParent = (1<<1)` — One of this item's descendant children matched a filter (ie it is a parent of a matched item)
- L40 _public enumerator_ `Match = (1<<2)` — This item itself matched one or more of the filters
- L43 _public enumerator_ `Expand = (1<<3)` — This item in the tree should be expanded according to one or more of the filters
- L45 _public enumerator_ `MatchBitMask = (ImplicitParent | Match | ImplicitChild)`

#### struct `FScopedCurveEditorTreeEventGuard`  
`struct FScopedCurveEditorTreeEventGuard`  
_L52-69_
- desc: Scoped guard that prevents the broadcast of tree events for the duration of its lifetime. Will trigger necessary events after the last remaining guard has been destroyed.
- L54 _public prototype_ `explicit FScopedCurveEditorTreeEventGuard(FCurveEditorTree* InTree);`
- L55 _public prototype_ `~FScopedCurveEditorTreeEventGuard();`
- L57 _public prototype_ `FScopedCurveEditorTreeEventGuard(FScopedCurveEditorTreeEventGuard&& RHS);`
- L58 _public prototype_ `FScopedCurveEditorTreeEventGuard& operator=(FScopedCurveEditorTreeEventGuard&& RHS);`
- L62 _private member_ `uint32 CachedItemSerialNumber;` — OnItemsChanged.SerialNumber cached on construction. Used to detect whether OnItemsChanged should be broadcast.
- L64 _private member_ `uint32 CachedSelectionSerialNumber;` — OnSelectionChanged.SerialNumber cached on construction. Used to detect whether OnSelectionChanged should be broadcast.
- L66 _private member_ `uint32 CachedFiltersSerialNumber;` — OnFiltersChanged.SerialNumber cached on construction. Used to detect whether OnFiltersChanged should be broadcast.
- L68 _private member_ `FCurveEditorTree* Tree;` — Pointer back to the owning tree

#### class `FCurveEditorTreeDelegate`  
`class FCurveEditorTreeDelegate : public FSimpleMulticastDelegate`  
_L74-89_
- inherits: `FSimpleMulticastDelegate`
- desc: Generic multicast delegate that guards against re-entrancy for the curve editor tree
- L82 _private prototype_ `void Broadcast();` — Broadcast this delegate provided it is not re-entrant
- L85 _private member_ `bool bBroadcasting = false;` — Whether this delegate is currently broadcasting
- L88 _private member_ `uint32 SerialNumber = 0;` — Serial number that is incremented any time this delegate should be broadcast

#### struct `FCurveEditorTreeEvents`  
`struct FCurveEditorTreeEvents`  
_L95-113_
- desc: Struct that represents an event for when the tree has been changed. This type carefully only allows FScopedCurveEditorTreeEventGuard to broadcast the event, and makes special checks for re-entrancy
- L98 _public member_ `FCurveEditorTreeDelegate OnItemsChanged;` — Event that is broadcast when the tree items container has changed
- L101 _public member_ `FCurveEditorTreeDelegate OnSelectionChanged;` — Event that is broadcast when the selection has changed
- L104 _public member_ `FCurveEditorTreeDelegate OnFiltersChanged;` — Event that is broadcast when any kind of filtering has changed (ie active state, filters being added/removed etc)
- L111 _private member_ `uint32 UpdateGuardCounter = 0;` — Counter that is incremented for each living instance of FScopedCurveEditorTreeEventGuard

#### struct `FSortedCurveEditorTreeItems`  
`struct FSortedCurveEditorTreeItems`  
_L118-125_
- desc: Container specifying a linear set of child identifiers and
- L121 _public member_ `bool bRequiresSort = false;` — (default: false) Whether the child ID array needs re-sorting or not
- L124 _public member_ `TArray<FCurveEditorTreeItemID> ChildIDs;` — Sorted list of child IDs

#### struct `FCurveEditorTreeItem`  
`struct FCurveEditorTreeItem`  
_L131-233_
- desc: Concrete type used as a tree item for the curve editor. No need to derive from this type - custom behaviour is implemented through ICurveEditorTreeItem. Implemented in this way to ensure that all hierarchical information can be reasoned about within the curve editor itself, and allow for mixing of tree item types from any usage domain.
- L134 _public function_ `FCurveEditorTreeItemID GetID() const` — @return This item's unique identifier within the tree
- L140 _public function_ `FCurveEditorTreeItemID GetParentID() const` — @return This parent's unique identifier within the tree, or FCurveEditorTreeItemID::Invalid for root items
- L150 _public function_ `TArrayView<const FCurveEditorTreeItemID> GetChildren() const` — Access the sorted list of children for this item @return An array view to this item's children
- L158 _public function_ `const TOptional<FString>& GetUniquePathName() const` — Get optional unique path name for the tree editor item
- L163 _public function_ `void SetUniquePathName(const TOptional<FString>& InName)` — Set optional unique path name for the tree editor item
- L169 _public function_ `TSharedPtr<ICurveEditorTreeItem> GetItem() const` — Access the user-specified implementation for this tree item @return A strong pointer to the implementation or null if it has expired, or was never assigned
- L177 _public function_ `void SetWeakItem(TWeakPtr<ICurveEditorTreeItem> InItem)` — Overwrite this item's implementation with an externally held implementation to this tree item. Does not hold a strong reference.
- L186 _public function_ `void SetStrongItem(TSharedPtr<ICurveEditorTreeItem> InItem)` — Overwrite this item's implementation, holding a strong reference to it for the lifetime of this tree item.
- L195 _public function_ `TArrayView<const FCurveModelID> GetCurves() const` — Get all the curves currently represented by this tree item. Items may not be created until the tree item has been selected
- L203 _public prototype_ `TArrayView<const FCurveModelID> GetOrCreateCurves(FCurveEditor* CurveEditor);` — Retrieve all the curves for this tree item, creating them through ICurveEditorTreeItem::CreateCurveModels if there are none
- L208 _public prototype_ `void DestroyCurves(FCurveEditor* CurveEditor);` — Destroy any previously constructed curve models that this tree item owns
- L213 _public prototype_ `void DestroyUnpinnedCurves(FCurveEditor* CurveEditor);` — Destroy any previously constructed unpinned curve models that this tree item owns
- L220 _private member_ `FCurveEditorTreeItemID ThisID;` — This item's ID
- L222 _private member_ `FCurveEditorTreeItemID ParentID;` — This parent's ID or FCurveEditorTreeItemID::Invalid() for root nodes
- L224 _private member_ `TOptional<FString> UniquePathName;` — Optional Unique Path Name
- L226 _private member_ `TWeakPtr<ICurveEditorTreeItem> WeakItemImpl;` — A weak pointer to an externally held implementation. Mutually exclusive to StrongItemImpl.
- L228 _private member_ `TSharedPtr<ICurveEditorTreeItem> StrongItemImpl;` — A strong pointer to an implementation for this tree item. Mutually exclusive to WeakItemImpl.
- L230 _private member_ `TArray<FCurveModelID, TInlineAllocator<1>> Curves;` — All the curves currently added to the curve editor from this tree item.
- L232 _private member_ `FSortedCurveEditorTreeItems Children;` — This item's sorted children.

#### struct `FCurveEditorFilterStates`  
`struct FCurveEditorFilterStates`  
_L239-357_
- desc: Sparse map of filter states specifying items that have matched a filter
- L244 _public function_ `void Reset()` — Reset all the filter states currently being tracked (does not affect IsActive
- L251 _public function_ `int32 GetNumMatched() const`
- L256 _public function_ `int32 GetNumMatchedImplicitly() const`
- L265 _public function_ `ECurveEditorTreeFilterState Get(FCurveEditorTreeItemID ItemID) const` — Retrieve the filter state for a specific tree item ID @return The item's filter state, or ECurveEditorTreeFilterState::Match if filters are not currently active.
- L278 _public function_ `template <typename CallableT> void ForEachItemState(CallableT Callable) const`
- L286 _public function_ `void SetFilterState(FCurveEditorTreeItemID ItemID, ECurveEditorTreeFilterState NewState)` — Assign a new filter state to an item
- L323 _public function_ `bool IsActive() const` — Check whether filters are active or not
- L331 _public function_ `void Activate()` — Activate the filters so that they begin to take effect
- L339 _public function_ `void Deactivate()` — Deactivate the filters so that they no longer take effect
- L347 _private member_ `bool bIsActive = false;` — Whether filters should be active or not
- L350 _private member_ `int32 NumMatched = 0;` — The total number of nodes that have matched all the filters
- L353 _private member_ `int32 NumMatchedImplicitly = 0;` — The total number of nodes that have not matched the filters but have a parent or child that did
- L356 _private member_ `TMap<FCurveEditorTreeItemID, ECurveEditorTreeFilterState> FilterStates;` — Filter state map. Items with no implicit or explicit filter state are not present

#### class `FCurveEditorTree`  
`class FCurveEditorTree`  
_L366-626_
- desc: Complete implementation of a curve editor tree. Only really defines the hierarchy and selection states for tree items.
- L372 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTreeItemSortPredicate, const ICurveEditorTreeItem* , const ICurveEditorTreeItem* );` — `UE_DEPRECATED(5.8, "Use FCurveTreeItemSortPredicate instead.")` — Defines a predicate for sorting curve editor tree item implementations.
- L374 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCurveTreeItemSortPredicate, const FCurveEditorTreeItem& , const FCurveEditorTreeItem& );` — Returns whether ItemA < ItemB.
- L377 _public member_ `FCurveEditorTreeEvents Events;` — Structure containing all the events for this tree
- L379 _public prototype_ `FCurveEditorTree();`
- L384 _public prototype_ `FCurveEditorTreeItem& GetItem(FCurveEditorTreeItemID ItemID);` — Retrieve an item from its ID, assuming it is definitely valid
- L389 _public prototype_ `const FCurveEditorTreeItem& GetItem(FCurveEditorTreeItemID ItemID) const;` — Retrieve an item from its ID, assuming it is definitely valid
- L394 _public prototype_ `FCurveEditorTreeItem* FindItem(FCurveEditorTreeItemID ItemID);` — Retrieve an item from its ID or nullptr if the ID is not valid
- L399 _public prototype_ `const FCurveEditorTreeItem* FindItem(FCurveEditorTreeItemID ItemID) const;` — Retrieve an item from its ID or nullptr if the ID is not valid
- L404 _public prototype_ `const TArray<FCurveEditorTreeItemID>& GetRootItems() const;` — Retrieve this curve editor's root items irrespective of filter state
- L409 _public prototype_ `const TMap<FCurveEditorTreeItemID, FCurveEditorTreeItem>& GetAllItems() const;` — Retrieve all the items stored in this tree irrespective of filter state
- L416 _public prototype_ `FCurveEditorTreeItem* AddItem(FCurveEditorTreeItemID ParentID);` — Add a new empty item to the tree @param ParentID The ID of the desired parent for the new item, or FCurveEditorTreeItemID::Invalid for root nodes
- L424 _public prototype_ `void RemoveItem(FCurveEditorTreeItemID ItemID, FCurveEditor* CurveEditor);` — Remove an item and all its children from this tree, destroying any curves it may have created. @param ItemID The ID of the item to remove @param CurveEditor (required) Pointer to the curve editor that owns this tree to remove curves from
- L429 _public prototype_ `void RunFilters();` — Run all the filters on this tree, updating filter state for all tree items
- L436 _public prototype_ `void AddFilter(TWeakPtr<FCurveEditorTreeFilter> NewFilter);` — Add a new filter to this tree. Does not run the filter (and thus update any tree views) until RunFilters is called. @param NewFilter The new filter to add to this tree
- L443 _public prototype_ `void RemoveFilter(TWeakPtr<FCurveEditorTreeFilter> FilterToRemove);` — Remove an existing filter from this tree. Does not re-run the filters (and thus update any tree views) until RunFilters is called. @param FilterToRemove The filter to remove from this tree
- L448 _public prototype_ `TArrayView<const TWeakPtr<FCurveEditorTreeFilter>> GetFilters() const;` — Direct access to all current filters (potentially including expired ones)
- L453 _public prototype_ `void ClearFilters();` — Clear all filters from the tree
- L461 _public prototype_ `const FCurveEditorTreeFilter* FindFilterByType(ECurveEditorTreeFilterType Type) const;` — Attempt to locate a filter by its type @param Type The type of the filter to find @return A pointer to the filter, or nullptr if one could not be found
- L467 _public prototype_ `void SetSortPredicate(FTreeItemSortPredicate InSortPredicate);` — Sets a predicate which will be used to sort tree items after they're been marked as needing sort.
- L471 _public prototype_ `void SetSortPredicate(FCurveTreeItemSortPredicate InSortPredicate);` — Sets a predicate which will be used to sort tree items after they're been marked as needing sort.
- L476 _public prototype_ `void SortTreeItems();` — Sorts all tree items which have been marked for sorting if the sort predicate has been set.
- L482 _public prototype_ `void SetDirectSelection(TArray<FCurveEditorTreeItemID>&& TreeItems, FCurveEditor* InCurveEditor);` — Inform this tree that the specified tree item IDs have been directly selected on the UI. @note: This populates both implicit and explicit selection state for the supplied items and any children/parents
- L487 _public prototype_ `void RemoveFromSelection(TArrayView<const FCurveEditorTreeItemID> TreeItems, FCurveEditor* InCurveEditor);` — Removes tree items from the current selection.
- L492 _public prototype_ `const TMap<FCurveEditorTreeItemID, ECurveEditorTreeSelectionState>& GetSelection() const;` — Access the selection state for this tree. Items that are neither implicitly or explicitly selected are not present in the map.
- L497 _public prototype_ `ECurveEditorTreeSelectionState GetSelectionState(FCurveEditorTreeItemID InTreeItemID) const;` — Check a specific tree item's selection state
- L502 _public prototype_ `const FCurveEditorFilterStates& GetFilterStates() const;` — Access the filter state for this tree. Items that are neither implicitly or explicitly filtered-in are not present in the map.
- L507 _public prototype_ `ECurveEditorTreeFilterState GetFilterState(FCurveEditorTreeItemID InTreeItemID) const;` — Check a specific tree item's filter state
- L513 _public function_ `FScopedCurveEditorTreeEventGuard ScopedEventGuard()` — Retrieve a scoped event guard that will block broadcast of events until the last guard on the stack goes out of scope Can be used to defer broadcasts in situations where many changes are made to the tree at a time.
- L521 _public prototype_ `void Compact();` — Compact the memory used by this tree (does not modify any meaningful state)
- L526 _public prototype_ `void ToggleExpansionState(bool bRecursive);` — Toggle the expansion state of the selected nodes or all nodes if none selected
- L529 _public prototype_ `void ExpandAllNodes();` — Expand all nodes in the tree
- L532 _public prototype_ `void CollapseAllNodes();` — Collapse all nodes in the tree
- L534 _public function_ `FOnCurveEditorToggleExpansionState& GetToggleExpansionState()`
- L539 _public function_ `FOnCurveEditorExpandAllNodes& GetOnExpandAllNodes()`
- L544 _public function_ `FOnCurveEditorCollapseAllNodes& GetOnCollapseAllNodes()`
- L552 _public prototype_ `TArray<FCurveEditorTreeItemID> GetCachedExpandedItems() const;` — Get cached expanded items
- L557 _public prototype_ `void SetItemExpansion(FCurveEditorTreeItemID InTreeItemID, bool bInExpansion);` — Set Item expansion state
- L562 _public function_ `bool IsDoingDirectSelection() const` — Whether or not we are are doign a direct selection, could be used to see why a curve model is being created or destroyed, by direct selection or by sequencer filtering?
- L570 _public prototype_ `void RecreateModelsFromExistingSelection(FCurveEditor* CurveEditor);` — Recreate the curve models from the existing selection, this may be needed in case of a setting change.
- L575 _private prototype_ `void RemoveChildrenRecursive(TArray<FCurveEditorTreeItemID>&& Children, FCurveEditor* CurveEditor);` — Recursively removes children without removing them from the parent (assuming the parent is also being removed)
- L585 _private prototype_ `ECurveEditorTreeFilterState PerformFilterPass(TArrayView<const FCurveEditorTreeFilter* const> FilterPtrs, TArrayView<const FCurveEditorTreeItemID> ItemsToFilter, ECurveEditorTreeFilterState InheritedState);` — Run the specified filters over the specified items and their recursive children, storing the results in this instance's FilterStates struct. @param FilterPtrs     Array of non-null pointers to filters to use. Items are considered matched if they match any filter in this array. @param ItemsToFilter  Array item IDs to filter @param InheritedState The filter state for each item to receive if it does not directly match a filter (either ECurveEditorTreeFilterState::NoMatch or ECurveEditorTreeFilterState::InheritedChild) @return Raised state flags which should be applied to parents of the filtered items.
- L590 _private prototype_ `void SortTreeItems(FSortedCurveEditorTreeItems& TreeItemIDsToSort);` — Recursively sorts the tree item ids using the sort predicate.
- L593 _private member_ `FCurveEditorTreeItemID NextTreeItemID;` — Incrementing ID for the next tree item to be created
- L596 _private member_ `TMap<FCurveEditorTreeItemID, FCurveEditorTreeItem> Items;` — Map of all tree items by their ID
- L599 _private member_ `TArray<TWeakPtr<FCurveEditorTreeFilter>> WeakFilters;` — Array of all filters that are currently active on this tree
- L602 _private member_ `FSortedCurveEditorTreeItems RootItems;` — Hierarchical information for the tree
- L603 _private member_ `TMap<FCurveEditorTreeItemID, FSortedCurveEditorTreeItems> ChildItemIDs;`
- L606 _private member_ `TMap<FCurveEditorTreeItemID, ECurveEditorTreeSelectionState> Selection;` — Selection state map. Items with no implicit or explicit selection are not present
- L609 _private member_ `FCurveEditorFilterStates FilterStates;` — Filter state map. Items with no implicit or explicit filter state are not present
- L612 _private member_ `FCurveTreeItemSortPredicate SortPredicate;` — A predicate which will be used to sort tree items after they're been marked as needing sort.
- L615 _private member_ `FOnCurveEditorToggleExpansionState ToggleExpansionStateDelegate;` — Delegate for when toggle expansion state is invoked
- L618 _private member_ `FOnCurveEditorExpandAllNodes ExpandAllNodesDelegate;` — Delegates for expand/collapse all
- L619 _private member_ `FOnCurveEditorCollapseAllNodes CollapseAllNodesDelegate;`
- L622 _private member_ `TSet<int32> CachedExpandedItems;` — Set of cached expanded items, based on GetTypedHash(FString)
- L625 _private member_ `bool bIsDoingDirectSelection = false;` — Whether or not we are are doign a direct selection, could be used to see why a curve model is being created or destroyed, by direct selection or by sequencer filtering?

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CURVEEDITOR_API`
- L47 _prototype_ `ENUM_CLASS_FLAGS(ECurveEditorTreeFilterState);`
- L359 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurveEditorToggleExpansionState, bool);`
- L359 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurveEditorToggleExpansionState, bool);`
- L360 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCurveEditorExpandAllNodes);`
- L360 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCurveEditorExpandAllNodes);`
- L361 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCurveEditorCollapseAllNodes);`
- L361 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCurveEditorCollapseAllNodes);`
- L372 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTreeItemSortPredicate, const ICurveEditorTreeItem* , const ICurveEditorTreeItem* );`
- L374 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCurveTreeItemSortPredicate, const FCurveEditorTreeItem& , const FCurveEditorTreeItem& );` — Returns whether ItemA < ItemB.

### `Source/Editor/CurveEditor/Public/Tree/CurveEditorTreeFilter.h` (Public)


#### enum `ECurveEditorTreeFilterType`  
`enum class ECurveEditorTreeFilterType : uint32`  
_L26-35_
- L29 _public enumerator_ `Text` — Filter is a FCurveEditorTreeTextFilter instance
- L31 _public enumerator_ `CUSTOM_START`
- L34 _public enumerator_ `First = Text`

#### struct `FCurveEditorTreeFilter`  
`struct FCurveEditorTreeFilter`  
_L42-96_
- desc: Base class for all filters that can be applied to a curve editor tree. Filters are identifyable through their type (see GetType()), which is a pre-registered static value retrieved through RegisterFilterType(). Client types can inspect this for supported types, and static_cast<> for implementation details. Filters also contain a pass, which is used to separate filters into separate passes. Filters applied within the same pass are matched as a boolean OR, filters in different passes are matched as a boolean AND.
- L44 _public function_ `FCurveEditorTreeFilter(ECurveEditorTreeFilterType InFilterType, int32 InFilterPass) : FilterType(InFilterType) , FilterPass(InFilterPass) , bExpandToMatchedItems(true)`
- L50 _public prototype_ `virtual ~FCurveEditorTreeFilter() = default;`
- L55 _public function_ `ECurveEditorTreeFilterType GetType() const` — @return The type of this filter as registered by RegisterFilterType
- L63 _public function_ `int32 GetFilterPass() const` — @return The pass index that should be used when applying this filter
- L71 _public function_ `bool ShouldExpandOnMatch() const` — @return If tree paths should be expanded down to matched items
- L84 _public prototype_ `static ECurveEditorTreeFilterType RegisterFilterType();` — Register a new filter type that is passed to ICurveEditorTreeItem::Filter @param InTreeItem The tree item to test @return true if the item matches the filter, false otherwise
- L89 _protected member_ `ECurveEditorTreeFilterType FilterType;` — The static type of this filter as retrieved by RegisterFilterType
- L92 _protected member_ `int32 FilterPass;` — Defines which pass this filter should be applied in
- L95 _protected member_ `bool bExpandToMatchedItems : 1;` — Determines if tree paths should be expanded down to matched items

#### struct `FCurveEditorTreeTextFilterToken`  
`struct FCurveEditorTreeTextFilterToken`  
_L99-108_
- desc: A specific text token (containing neither spaces nor .)
- L101 _public member_ `FString Token;`
- L104 _public function_ `bool Match(const TCHAR* InString) const` — Match this token against a string

#### struct `FCurveEditorTreeTextFilterTerm`  
`struct FCurveEditorTreeTextFilterTerm`  
_L111-161_
- desc: A text filter term containing >= 1 sparate tokens ordered from child to parent
- L158 _public prototype_ `FMatchResult Match(FStringView InString) const;` — Match a string against these tokens
- L160 _public member_ `TArray<FCurveEditorTreeTextFilterToken, TInlineAllocator<1>> ChildToParentTokens;`

#### struct `FCurveEditorTreeTextFilterTerm::FMatchResult`  
`struct FMatchResult`  
_L117-153_
- desc: Struct representing the result of a match operation, including any remaining tokens that need to be matched recursively upwards
- L120 _public function_ `FMatchResult() : bMatched(false)` — Default constructor to an empty result that did not match
- L125 _public function_ `FMatchResult(TArrayView<const FCurveEditorTreeTextFilterToken> InRemainingTokens) : RemainingTokens(InRemainingTokens) , bMatched(true)` — Constructor that creates a successful match with optional remaining tokens
- L131 _public prototype_ `FMatchResult Match(FStringView InString) const;` — Match another string against the remaining tokens for this result
- L134 _public function_ `bool IsAnyMatch() const` — Check whether this result is a partial or total match. Returns false if any match has failed.
- L139 _public function_ `bool IsPartialMatch() const` — Check whether this result matched, but still has tokens left to match
- L144 _public function_ `bool IsTotalMatch() const` — Check whether this result has completely matched all tokens
- L151 _private member_ `TArrayView<const FCurveEditorTreeTextFilterToken> RemainingTokens;`
- L152 _private member_ `bool bMatched;`

#### struct `FCurveEditorTreeTextFilter`  
`struct FCurveEditorTreeTextFilter : FCurveEditorTreeFilter`  
_L166-207_
- inherits: `FCurveEditorTreeFilter`
- desc: Built-in text filter of type ECurveEditorTreeFilterType::Text. Filter terms are applied as a case-insensitive boolean OR substring match.
- L169 _public member_ `FText InputText;` — Original input filter text.
- L172 _public member_ `static const int32 DefaultPass = 1000;` — Default pass for text filters.
- L175 _public function_ `FCurveEditorTreeTextFilter() : FCurveEditorTreeFilter(ECurveEditorTreeFilterType::Text, DefaultPass)` — Default constructor
- L184 _public prototype_ `void AssignFromText(const FString& FilterString);` — Assign a new filter string to this filter, resetting any previous filter terms @param FilterString   The new filter string that should be parsed into this filter
- L189 _public function_ `bool IsEmpty() const` — Check whether this filter is empty (ie, has no filter terms)
- L198 _public function_ `TArrayView<const FCurveEditorTreeTextFilterTerm> GetTerms() const` — Access all the filter terms contained within this filter. Each term comprises an array of text tokens that must match from child to parent. Valid to call if IsEmpty() == true, but the resulting array view will be empty.
- L206 _private member_ `TArray<FCurveEditorTreeTextFilterTerm, TInlineAllocator<4>> ChildToParentFilterTerms;` — Arrays of case-insensitive terms to find within tree items. Each term is an array of strings that must be matched from child to parent.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Tree/CurveEditorTreeTraits.h` (Public)


#### struct `TListTypeTraits`  
`template<> struct TListTypeTraits<FCurveEditorTreeItemID>`  
_L11-53_
- L20 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FCurveEditorTreeItemID, TSharedRef<ITableRow>, false>;`
- L21 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FCurveEditorTreeItemID, FSparseItemInfo, false>;`
- L22 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FCurveEditorTreeItemID>;`
- L25 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FCurveEditorTreeItemID>&, TSet<FCurveEditorTreeItemID>&, TMap< const U*, FCurveEditorTreeItemID >&)`
- L27 _public function_ `static bool IsPtrValid(NullableType InPtr)`
- L32 _public function_ `static void ResetPtr(NullableType& InPtr)`
- L37 _public function_ `static NullableType MakeNullPtr()`
- L42 _public function_ `static FCurveEditorTreeItemID NullableItemTypeConvertToItemType(NullableType InPtr)`
- L47 _public function_ `static FString DebugDump(FCurveEditorTreeItemID InPtr)`

#### struct `TListTypeTraits::NullableType`  
`struct NullableType : FCurveEditorTreeItemID`  
_L14-18_
- inherits: `FCurveEditorTreeItemID`
- L16 _public function_ `NullableType(TYPE_OF_NULLPTR)`
- L17 _public function_ `NullableType(FCurveEditorTreeItemID Other) : FCurveEditorTreeItemID(Other)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L52-52_

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<FCurveEditorTreeItemID>`  
_L56-62_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L59-61_

#### Free symbols / members of external scopes

- L60 _enumerator_ `Value = true` (scope `TIsValidListItem::__anond958543d0103`)

### `Source/Editor/CurveEditor/Public/Tree/ICurveEditorTreeItem.h` (Public)


#### struct `ICurveEditorTreeItem`  
`struct ICurveEditorTreeItem`  
_L27-71_
- desc: Optional implementation interface for any tree item to be shown on the curve editor tree.
- L29 _public prototype_ `virtual ~ICurveEditorTreeItem() = default;`
- L40 _public prototype_ `virtual TSharedPtr<SWidget> GenerateCurveEditorTreeWidget(const FName& InColumnName, TWeakPtr<FCurveEditor> InCurveEditor, FCurveEditorTreeItemID InTreeItemID, const TSharedRef<ITableRow>& InTableRow) = 0;` — Generate the widget content for the specified column name of the curve editor tree view @param InColumnName     The name of the column to generate widget content for. See FColumnNames for valid names. @param InCurveEditor    Weak pointer to the curve editor instance. Persistent TSharedPtrs should not be held to this pointer. @param InTreeItemID     The ID of the tree item that this interface is assigned to @param InTableRow       The table row that will house the widget content @return (Optional) Widget content for this column, or nullptr if none is necessary for this column.
- L47 _public prototype_ `virtual void CreateCurveModels(TArray<TUniquePtr<FCurveModel>>& OutCurveModels) = 0;` — Populate the specified array with curve models that are represented by this tree item @param OutCurveModels  Array of curve models to be populated with the curves of this tree item
- L55 _public function_ `virtual bool PassesFilter(const FCurveEditorTreeFilter* InFilter) const` — Check whether this tree item passes the specified filter. Filter's types can be checked using FCurveEditorTreeFilter::GetType() and static_casted for known filter types. @param InFilter        The filter to test against. @return True if this item is deemed to have passed the filter, false otherwise
- L70 _public member_ `static const FColumnNames ColumnNames;`

#### struct `ICurveEditorTreeItem::FColumnNames`  
`struct FColumnNames`  
_L58-68_
- desc: Structure of pre-defined supported column names for the curve editor outliner
- L61 _public member_ `FName Label;` — Generic label content
- L63 _public member_ `FName SelectHeader;` — Right-aligned column for select buttons
- L65 _public member_ `FName PinHeader;` — Right-aligned column for pin buttons
- L67 _public prototype_ `FColumnNames();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Tree/SCurveEditorTree.h` (Public)


#### class `SCurveEditorTree`  
`class SCurveEditorTree : public STreeView<FCurveEditorTreeItemID>`  
_L31-94_
- inherits: `STreeView<FCurveEditorTreeItemID>`
- L36 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorTree) : _SelectColumnWidth(24.f)`
- L39 _public prototype_ `SLATE_ARGUMENT(float, SelectColumnWidth) SLATE_EVENT(FOnMouseButtonDoubleClick, OnMouseButtonDoubleClick) SLATE_EVENT(FOnTableViewScrolled, OnTreeViewScrolled) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FCurveEditor> InCurveEditor);`
- L47 _public function_ `const TArray<FCurveEditorTreeItemID>& GetSourceItems() const`
- L49 _public prototype_ `TSharedRef<ITableRow> GenerateRow(FCurveEditorTreeItemID ItemID, const TSharedRef<STableViewBase>& OwnerTable);`
- L51 _public prototype_ `void GetTreeItemChildren(FCurveEditorTreeItemID Parent, TArray<FCurveEditorTreeItemID>& OutChildren);`
- L55 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L60 _private prototype_ `void OnTreeSelectionChanged(FCurveEditorTreeItemID, ESelectInfo::Type);`
- L62 _private prototype_ `void SetItemExpansionRecursive(FCurveEditorTreeItemID Model, bool bInExpansionState);`
- L64 _private prototype_ `void OnExpansionChanged(FCurveEditorTreeItemID Model, bool bInExpansionState);`
- L66 _private prototype_ `void RefreshTree();`
- L68 _private prototype_ `void RefreshTreeWidgetSelection();`
- L70 _private prototype_ `void ToggleExpansionState(bool bRecursive);`
- L72 _private prototype_ `void ExpandAllNodes();`
- L74 _private prototype_ `void CollapseAllNodes();`
- L76 _private prototype_ `FCurveEditorTreeItemID FindVisibleSelectionProxy(const FCurveEditorTreeItemID InItemID) const;`
- L80 _private member_ `bool bFilterWasActive;`
- L82 _private member_ `TArray<FCurveEditorTreeItemID> RootItems;`
- L85 _private member_ `TSet<FCurveEditorTreeItemID> PreFilterExpandedItems;` — Set of item IDs that were expanded before a filter was applied
- L87 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;`
- L89 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L91 _private member_ `bool bUpdatingTreeWidgetSelection;`
- L92 _private member_ `bool bUpdatingCurveEditorTreeSelection;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Tree/SCurveEditorTreeFilterStatusBar.h` (Public)


#### class `SCurveEditorTreeFilterStatusBar`  
`class SCurveEditorTreeFilterStatusBar : public SCompoundWidget`  
_L16-47_
- inherits: `SCompoundWidget`
- desc: Widget that shows the metrics for the current tree filter in the curve editor (in the form "Showing {0} of {1} items ({2} selected)")
- L19 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorTreeFilterStatusBar)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FCurveEditor> InCurveEditor);`
- L25 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L27 _public prototype_ `void ShowStatusBar();`
- L28 _public prototype_ `void HideStatusBar();`
- L29 _public prototype_ `void FadeOutStatusBar();`
- L34 _private prototype_ `EVisibility GetVisibilityFromFilter() const;` — Request the visibility of the clear hyperlink widget based on whether there's a filter active or not
- L37 _private prototype_ `void UpdateText();` — Update the filter text to represent the current filter states in the tree
- L40 _private prototype_ `void ClearFilters();` — Clear all the filters in the tree - called as a result of the user clicking on the 'clear' hyperlink
- L44 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;`
- L45 _private member_ `TSharedPtr<STextBlock> TextBlock;`
- L46 _private member_ `double OpacityThrobEndTime = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Tree/SCurveEditorTreePin.h` (Public)


#### class `SCurveEditorTreePin`  
`class SCurveEditorTreePin : public SCompoundWidget`  
_L20-46_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorTreePin)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor, FCurveEditorTreeItemID InTreeItemID, const TSharedRef<ITableRow>& InTableRow);`
- L30 _private prototype_ `FReply TogglePinned();`
- L31 _private prototype_ `const FSlateBrush* GetPinBrush() const;`
- L33 _private prototype_ `bool IsPinnedRecursive(FCurveEditorTreeItemID InTreeItem, FCurveEditor* CurveEditor) const;`
- L35 _private prototype_ `void PinRecursive(FCurveEditorTreeItemID InTreeItem, FCurveEditor* CurveEditor) const;`
- L37 _private prototype_ `void UnpinRecursive(FCurveEditorTreeItemID InTreeItem, FCurveEditor* CurveEditor, TArray<FCurveEditorTreeItemID>& OutUnpinnedItems) const;`
- L39 _private prototype_ `EVisibility GetPinVisibility() const;`
- L43 _private member_ `TWeakPtr<ITableRow> WeakTableRow;`
- L44 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;`
- L45 _private member_ `FCurveEditorTreeItemID TreeItemID;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Tree/SCurveEditorTreeSelect.h` (Public)


#### class `SCurveEditorTreeSelect`  
`class SCurveEditorTreeSelect : public SCompoundWidget`  
_L19-40_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorTreeSelect)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor, FCurveEditorTreeItemID InTreeItemID, const TSharedRef<ITableRow>& InTableRow);`
- L29 _private prototype_ `FReply SelectAll();`
- L31 _private prototype_ `const FSlateBrush* GetSelectBrush() const;`
- L33 _private prototype_ `EVisibility GetSelectVisibility() const;`
- L37 _private member_ `TWeakPtr<ITableRow> WeakTableRow;`
- L38 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;`
- L39 _private member_ `FCurveEditorTreeItemID TreeItemID;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Tree/SCurveEditorTreeTextFilter.h` (Public)


#### class `SCurveEditorTreeTextFilter`  
`class SCurveEditorTreeTextFilter : public SCompoundWidget`  
_L19-41_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SCurveEditorTreeTextFilter)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FCurveEditor> CurveEditor);`
- L29 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;` — SWidget Interface
- L30 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L34 _private prototype_ `void CreateSearchBox();`
- L35 _private prototype_ `void OnTreeFilterListChanged();`
- L36 _private prototype_ `void OnFilterTextChanged(const FText& FilterText);`
- L38 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L39 _private member_ `TSharedPtr<FCurveEditorTreeTextFilter> Filter;`
- L40 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Views/SCurveEditorViewAbsolute.h` (Public)


#### class `SCurveEditorViewAbsolute`  
`class SCurveEditorViewAbsolute : public SInteractiveCurveEditorView`  
_L15-21_
- inherits: `SInteractiveCurveEditorView`
- desc: A Normalized curve view supporting one or more curves with their own screen transform that normalizes the vertical curve range to [-1,1]
- L19 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Views/SCurveEditorViewNormalized.h` (Public)


#### class `SCurveEditorViewNormalized`  
`class SCurveEditorViewNormalized : public SInteractiveCurveEditorView, public FSelfRegisteringEditorUndoClient`  
_L26-71_
- inherits: `SInteractiveCurveEditorView,FSelfRegisteringEditorUndoClient`
- desc: A Normalized curve view supporting one or more curves with their own screen transform that normalizes the vertical curve range to [-1,1]
- L30 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`
- L33 _public function_ `virtual bool IsValueSnapEnabled() const override` — Tools should use vertical snapping since grid lines to snap to will usually be visible
- L35 _public prototype_ `virtual void UpdateViewToTransformCurves(double InputMin, double InputMax) override;`
- L37 _public prototype_ `void FrameVertical(double InOutputMin, double InOutputMax, FCurveEditorViewAxisID AxisID = FCurveEditorViewAxisID()) override;`
- L39 _public prototype_ `virtual void OnCurveListChanged() override;`
- L43 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L44 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L48 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget Interface
- L49 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L52 _protected prototype_ `virtual void PaintView(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L54 _protected prototype_ `virtual void DrawBufferedCurves(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L57 _protected prototype_ `void InternalUpdateViewToTransformCurves();` — Helper to call UpdateViewToTransformCurves from internal methods
- L63 _protected prototype_ `void ClampToTimeController(double& OutMin, double& OutMax) const;` — Limits OutMin and OutMax to the time controller playback range, i.e. OutMin >= TimeController's min and OutMax <= TimeController's max. This corresponds green, left and red, right horizontal lines on the frame ruler.
- L67 _private prototype_ `void RecomputeViewToCurveTransform(const TSharedRef<FCurveEditor>& CurveEditor, FCurveModelID CurveID, FCurveInfo& CurveInfo);` — Recomputes a single curve's ViewToCurveTransform from its current value range.
- L70 _private member_ `TSet<FCurveModelID> InitializedCurves;` — Curve IDs whose ViewToCurveTransform has been computed at least once.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Views/SCurveEditorViewStacked.h` (Public)


#### class `SCurveEditorViewStacked`  
`class SCurveEditorViewStacked : public SInteractiveCurveEditorView`  
_L25-53_
- inherits: `SInteractiveCurveEditorView`
- desc: A Normalized curve view supporting one or more curves with their own screen transform that normalizes the vertical curve range to [-1,1]
- L29 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`
- L32 _public function_ `virtual bool IsValueSnapEnabled() const override` — Tools should use vertical snapping since grid lines to snap to will usually be visible
- L34 _public prototype_ `virtual void UpdateViewToTransformCurves(double InputMin, double InputMax) override;`
- L38 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L39 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L41 _protected prototype_ `virtual void PaintView(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L42 _protected prototype_ `virtual void GetGridLinesY(TSharedRef<const FCurveEditor> CurveEditor, TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels = nullptr) const override;`
- L44 _protected prototype_ `virtual void DrawViewGrids(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L45 _protected prototype_ `virtual void DrawLabels(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L46 _protected prototype_ `virtual void DrawBufferedCurves(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L49 _protected member_ `float StackedHeight;` — Stacked height per curve
- L52 _protected member_ `float StackedPadding;` — Stacked padding per curve

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CURVEEDITOR_API`

### `Source/Editor/CurveEditor/Public/Views/SInteractiveCurveEditorView.h` (Public)


#### enum `CurveViewConstants::ELayerOffset::(anonymous)`  
``  
_L65-79_

#### class `SInteractiveCurveEditorView`  
`class SInteractiveCurveEditorView : public SCurveEditorView`  
_L85-279_
- inherits: `SCurveEditorView`
- L89 _public function_ `SLATE_BEGIN_ARGS(SInteractiveCurveEditorView) : _BackgroundTint(FLinearColor::White) , _MaximumCapacity(0) , _AutoSize(true)`
- L95 _public prototype_ `SLATE_ARGUMENT(FLinearColor, BackgroundTint) SLATE_ARGUMENT(int32, MaximumCapacity) SLATE_ATTRIBUTE(float, FixedHeight) SLATE_ARGUMENT(bool, AutoSize) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`
- L107 _public prototype_ `virtual void GetGridLinesX(TSharedRef<const FCurveEditor> CurveEditor, TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels = nullptr) const override;`
- L108 _public prototype_ `virtual void GetGridLinesY(TSharedRef<const FCurveEditor> CurveEditor, TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels = nullptr) const override;`
- L110 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder, TOptional<FCurvePointHandle> ClickedPoint, TOptional<FCurveModelID> HoveredCurveID);`
- L115 _protected prototype_ `virtual bool GetPointsWithinWidgetRange(const FSlateRect& WidgetRectangle, TArray<FCurvePointHandle>* OutPoints) const override;`
- L116 _protected prototype_ `virtual bool GetCurveWithinWidgetRange(const FSlateRect& WidgetRectangle, TArray<FCurvePointHandle>* OutPoints) const override;`
- L117 _protected prototype_ `virtual TOptional<FCurveModelID> GetHoveredCurve() const override;`
- L119 _protected prototype_ `virtual FText FormatToolTipCurveName(const FCurveModel& CurveModel) const;`
- L120 _protected prototype_ `virtual FText FormatToolTipTime(const FCurveModel& CurveModel, double EvaluatedTime) const;`
- L121 _protected prototype_ `virtual FText FormatToolTipValue(const FCurveModel& CurveModel, double EvaluatedValue) const;`
- L123 _protected prototype_ `virtual void PaintView(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L128 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget Interface
- L129 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L130 _protected prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L131 _protected prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L132 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L133 _protected prototype_ `virtual void OnFinishedPointerInput() override;`
- L134 _protected prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L135 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L136 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L139 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L144 _protected prototype_ `void DrawBackground(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L145 _protected prototype_ `void DrawGridLines(TSharedRef<FCurveEditor> CurveEditor, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L146 _protected prototype_ `void DrawCurves(TSharedRef<FCurveEditor> CurveEditor, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, ESlateDrawEffect DrawEffects) const;`
- L147 _protected prototype_ `void DrawBufferedCurves(TSharedRef<FCurveEditor> CurveEditor, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, ESlateDrawEffect DrawEffects) const;`
- L148 _protected prototype_ `void DrawValueIndicatorLines(TSharedRef<FCurveEditor> InCurveEditor, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InBaseLayerId) const;`
- L151 _protected prototype_ `void UpdatedKeysWithValueIndicatorLines(const FCurveEditor& InCurveEditor) const;` — Updates the keys that will be drawn with value indicator lines.
- L153 _protected prototype_ `bool PickPointsToPlaceValueIndicatorLinesOn(const FCurveModel& InCurveModel, const FKeyHandleSet& InUserSelectedKeys, FKeyHandle& OutMinKey, FKeyHandle& OutMaxKey) const;` — Picks which keys will have value indicator lines drawn for them. Returns true if the selection.
- L155 _protected prototype_ `FSlateColor GetCurveCaptionColor() const;`
- L156 _protected prototype_ `FText GetCurveCaption() const;`
- L160 _private prototype_ `void HandleDirectKeySelectionByMouse(TSharedPtr<FCurveEditor> CurveEditor, const FPointerEvent& MouseEvent, TOptional<FCurvePointHandle> MouseDownPoint);`
- L162 _private prototype_ `void CreateContextMenu(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L165 _private prototype_ `void UpdateCurveProximities(FVector2D MousePixel);` — Updates our distance to the curve neareast to the cursor.
- L167 _private prototype_ `TOptional<FCurvePointHandle> HitPoint(FVector2D MousePixel) const;`
- L169 _private prototype_ `bool IsToolTipEnabled() const;`
- L170 _private prototype_ `FText GetToolTipCurveName() const;`
- L171 _private prototype_ `FText GetToolTipTimeText() const;`
- L172 _private prototype_ `FText GetToolTipValueText() const;`
- L183 _private prototype_ `double GetTangentValue(const double InTime, const double InValue, FCurveModel* CurveToAddTo, double DeltaTime) const;` — Returns the proper tangent value so we can keep the curve remain the original shape @param InTime		The time we are trying to add a key to @param InValue		The value we are trying to add a key to @param CurveToAddTo  The curve we are trying to add a key to @param DeltaTime		Negative to get the left tangent, positive for right. Remember to use FMath::Abs() when needed @return				The tangent value relatives to the DeltaTime upon mouse click's position
- L186 _private prototype_ `void AddKeyAtScrubTime(bool bUseSelection);` — ~ Command binding callbacks
- L188 _private function_ `void AddKeyAtScrubTime(TSet<FCurveModelID> ForCurves)` — `UE_DEPRECATED(5.8, "Please, use AddKeyAtScrubTime that takes bUseSelection parameter")`
- L189 _private prototype_ `void AddKeyAtMousePosition(TSet<FCurveModelID> ForCurves);`
- L190 _private prototype_ `void AddKeyAtTime(const TSet<FCurveModelID>& ToCurves, double InTime);`
- L191 _private prototype_ `void PasteKeys(TSet<FCurveModelID> ToCurves);`
- L192 _private prototype_ `void ResetKeysToDefaultValues(bool bUseSelection);`
- L193 _private prototype_ `void OnCurveEditorToolChanged(FCurveEditorToolID InToolId);`
- L194 _private prototype_ `void OnShowValueIndicatorsChanged();`
- L199 _private prototype_ `void RebindContextualActions(FVector2D InMousePosition);` — Rebind contextual command mappings that rely on the mouse position
- L202 _private prototype_ `void BufferCurves();` — Copy the curves from this view and set them as the Curve Editor's buffered curve support.
- L204 _private prototype_ `void ApplyBufferCurves(const bool bSwapBufferCurves);` — Attempt to apply the previously buffered curves to the currently selected curves.
- L206 _private prototype_ `bool CanBufferedCurves() const;` — Check if it's legal to buffer any of our selected curves.
- L208 _private prototype_ `bool CanApplyBufferedCurves() const;` — Check if it's legal to apply any of the buffered curves to our currently selected curves.
- L210 _private prototype_ `FKeyAttributes GetDefaultKeyAttributesForCurveTime(const FCurveEditor& CurveEditor, const FCurveModel& CurveModel, double EvalTime) const;` — Returns interpolation mode and tangent mode based on neighbours or default curve editor if no neighbours .
- L215 _protected member_ `FLinearColor BackgroundTint;` — Background tint for this widget
- L220 _private member_ `TOptional<FCurveEditorDelayedDrag> DragOperation;` — (Optional) the current drag operation
- L222 _private member_ `bool bHadMouseMovesThisTick = false;` — Whether DragOperation needs to have OnFinishedPointerInput called this tick.
- L233 _private member_ `TOptional<FCachedToolTipData> CachedToolTipData;`
- L236 _private member_ `TArray<TTuple<FCurveModelID, float>> CurveProximities;` — Array of curve proximities in slate units that's updated on mouse move. Does not necessarily hold all curves.
- L239 _private member_ `TWeakPtr<IMenu> ActiveContextMenu;` — Track if we have a context menu active. Used to suppress hover updates as it causes flickers in the CanExecute bindings.
- L242 _private member_ `FVector2D CachedMousePosition;` — Cached location of the mouse relative to this widget each tick. This is so that command bindings related to the mouse cursor can create them at the right time.
- L245 _private member_ `mutable FText CachedCurveCaption;` — Cached curve caption, used to determine when to refresh the retainer
- L248 _private member_ `mutable FSlateColor CachedCurveCaptionColor;` — Cached curve caption color, used to determine when to refresh the retainer
- L250 _private member_ `mutable bool bNeedsRefresh = false;`
- L278 _private member_ `mutable TOptional<FValueIndicatorLineData> ValueIndicatorLineDrawData;` — We draw up to 2 horizontal value indicator line on the keys that a user selects. This makes it easier for the user to see a selected key's value in relation to other keys. Requirements: - Only draw value indicator line if 1 curve is selected. More curves selected = no line. - The value indicator lines are drawn through the min and max value keys in the selected range. - If only 1 key is selected, only draw 1 line (obviously). The per-curve upper limit of value indicator lines that are drawn is configured in UCurveEditorSettings::MaxNumHorizontalSelectionLinesPerCurve. This is called in OnPaint, which is const. Mutable is a workaround.

#### struct `SInteractiveCurveEditorView::FCachedToolTipData`  
`struct FCachedToolTipData`  
_L224-231_
- L226 _public function_ `FCachedToolTipData()`
- L228 _public member_ `FText Text;`
- L229 _public member_ `FText EvaluatedValue;`
- L230 _public member_ `FText EvaluatedTime;`

#### struct `SInteractiveCurveEditorView::FValueIndicatorLineData`  
`struct FValueIndicatorLineData`  
_L252-265_
- L255 _public member_ `const FCurveModelID HighlightedCurve;` — The curve for which the value indicator lines are being drawn.
- L258 _public member_ `FKeyHandle MinKey = FKeyHandle::Invalid();` — Key handle to the min item through which a value indicator line is being drawn.
- L260 _public member_ `FKeyHandle MaxKey = FKeyHandle::Invalid();` — Key handle to the max item through which a value indicator line is being drawn. If the user only has 1 key selected, this is FKeyHandle::Invalid().
- L262 _public function_ `explicit FValueIndicatorLineData(const FCurveModelID& HighlightedCurve, const FKeyHandle& MinKey, const FKeyHandle& MaxKey) : HighlightedCurve(HighlightedCurve) , MinKey(MinKey), MaxKey(MaxKey)`

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API CURVEEDITOR_API`
- L50 _namespace_ `namespace CurveViewConstants`
- L53 _variable_ `constexpr float CurveLabelOffsetX = 15.f;` (scope `CurveViewConstants`) — The default offset from the top-right corner of curve views for curve labels to be drawn.
- L54 _variable_ `constexpr float CurveLabelOffsetY = 10.f;` (scope `CurveViewConstants`)
- L56 _variable_ `constexpr FLinearColor BufferedCurveColor = FLinearColor(.4f, .4f, .4f);` (scope `CurveViewConstants`)
- L62 _namespace_ `namespace ELayerOffset` (scope `CurveViewConstants`)
- L66 _enumerator_ `Background = 0` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L67 _enumerator_ `GridLines = 1` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L68 _enumerator_ `GridOverlays = 2` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L69 _enumerator_ `GridLabels = 3` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L70 _enumerator_ `Curves = 10` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L71 _enumerator_ `HoveredCurves = 15` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L72 _enumerator_ `Keys = 20` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L73 _enumerator_ `SelectedKeys = 30` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L74 _enumerator_ `Tools = 35` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L75 _enumerator_ `DragOperations = 40` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L76 _enumerator_ `Labels = 45` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L77 _enumerator_ `WidgetContent = 50` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
- L78 _enumerator_ `Last = Labels` (scope `CurveViewConstants::ELayerOffset::__anonf8ec74c00103`)
