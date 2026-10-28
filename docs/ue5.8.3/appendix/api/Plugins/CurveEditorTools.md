# Plugins / CurveEditorTools

- module root: `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools`
- headers: 35; symbols: 709
- symbol kinds: class=21, delegate=2, enum=10, enumerator=44, function=81, member=208, namespace=71, prototype=224, struct=33, typedef=9, variable=6
- PrivateDependencyModuleNames: AudioMixer, CoreUObject, EditorFramework, EditorStyle, InputCore, SequencerWidgets, SignalProcessing, Slate, SlateCore, TweeningUtils, TweeningUtilsEditor, UnrealEd
- PublicDependencyModuleNames: Core, CurveEditor, Engine

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/CurveEditorToolCommands.h` (Private)


#### class `FCurveEditorToolCommands`  
`class FCurveEditorToolCommands : public TCommands<FCurveEditorToolCommands>`  
_L11-36_
- inherits: `TCommands<FCurveEditorToolCommands>`
- desc: Defines commands for the Curve Editor Tools plugin which enables most functionality of the Curve Editor.
- L14 _public function_ `FCurveEditorToolCommands() : TCommands<FCurveEditorToolCommands> ( TEXT("CurveEditorTools"), NSLOCTEXT("Contexts", "CurveEditorTools", "Curve Editor Tools"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L25 _public member_ `TSharedPtr<FUICommandInfo> SetFocusPlaybackTime;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> SetFocusPlaybackRange;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> SetFocusSelectionRange;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> SetKeysInSelectionRange;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ActivateTransformTool;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ActivateRetimeTool;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ActivateMultiScaleTool;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ActivateLatticeTool;`
- L35 _public prototype_ `virtual void RegisterCommands() override;`

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Extensions/CurveEditorFocusExtension.h` (Private)


#### class `FCurveEditorFocusExtension`  
`class FCurveEditorFocusExtension : public ICurveEditorExtension, public TSharedFromThis<FCurveEditorFocusExtension>`  
_L9-35_
- inherits: `ICurveEditorExtension,TSharedFromThis<FCurveEditorFocusExtension>`
- L12 _public function_ `FCurveEditorFocusExtension(TWeakPtr<FCurveEditor> InCurveEditor) : WeakCurveEditor(InCurveEditor)`
- L18 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> CommandBindings) override;` — ICurveEditorExtension Interface
- L23 _private prototype_ `void FocusPlaybackRange();` — Focuses the curve editor around the current Playback Range of the linked Time Controller.
- L25 _private prototype_ `void FocusSelectionRange();` — Focuses the curve editor around the current Selection Range of the linked Time Controller (falls back to Playback Range if empty).
- L27 _private prototype_ `void SelectKeysInSelectionRange();` — Selects all keys within the current Selection Range (or Playback Range if no selection range is set).
- L29 _private prototype_ `void FocusPlaybackTime();` — Focuses the curve editor around the current Playback Time of the linked Time Controller without changing zoom level.
- L32 _private prototype_ `bool CanUseFocusExtensions() const;` — Checks to see if the Curve Editor has a valid Time Controller to use these focus extensions on.
- L34 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;`

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Extensions/Tweening/ContextAwareTweeningModel.h` (Private)


#### class `UE::CurveEditorTools::TContextAwareTweeningModel`  
`template<TweeningUtilsEditor::EBlendFunction BlendFunction> class TContextAwareTweeningModel : public TweeningUtilsEditor::FTweenModel`  
_L23-49_
- inherits: `TweeningUtilsEditor::FTweenModel`
- desc: This model tweens keys depending on the user selection: - When keys are selected, FCurveTweenModel will tween the selected keys. - When no keys are selected, we'll insert keys at the time controller's scrub position to all visible curves (those selected in tree view). If there's no such controller, nothing happens.
- L25 _private typedef_ `using Super = FTweenModel;`
- L28 _public prototype_ `explicit TContextAwareTweeningModel(TWeakPtr<FCurveEditor> InWeakCurveEditor);`
- L31 _public prototype_ `virtual void SetScaleMode(TweeningUtilsEditor::ETweenScaleMode InMode) override;`
- L32 _public prototype_ `virtual void StartBlendOperation() override;`
- L33 _public prototype_ `virtual void StopBlendOperation() override;`
- L34 _public prototype_ `virtual void BlendValues(float InNormalizedValue) override;`
- L40 _private member_ `const TWeakPtr<FCurveEditor> CurveEditor;` — The curve editor of which the keys are tweened.
- L43 _private member_ `TweeningUtilsEditor::TCurveTweenModel<BlendFunction> SelectionBasedModel;` — Tweens when there is a key selection.
- L45 _private member_ `const TSharedPtr<FTweenModel> NoKeySelectionModel;` — Injected model that tweens when there is no key selection. Can be nullptr.
- L48 _private prototype_ `template<typename TCallback> requires std::is_invocable_v<TCallback, TweeningUtilsEditor::FTweenModel&> void AccessCurrentModel(TCallback&& InCallback);`
- L56 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> TContextAwareTweeningModel<BlendFunction>::TContextAwareTweeningModel(TWeakPtr<FCurveEditor> InWeakCurveEditor) : CurveEditor(InWeakCurveEditor) , SelectionBasedModel(InWeakCurveEditor) , NoKeySelectionModel(MakeShared<TKeyInsertingTweenModel<BlendFunction>>(InWeakCurveEditor))`
- L63 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> void TContextAwareTweeningModel<BlendFunction>::SetScaleMode(TweeningUtilsEditor::ETweenScaleMode InMode)`
- L74 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> void TContextAwareTweeningModel<BlendFunction>::StartBlendOperation()`
- L83 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> void TContextAwareTweeningModel<BlendFunction>::StopBlendOperation()`
- L92 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> void TContextAwareTweeningModel<BlendFunction>::BlendValues(float InNormalizedValue)`
- L102 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> template <typename TCallback> requires std::is_invocable_v<TCallback, TweeningUtilsEditor::FTweenModel&> void TContextAwareTweeningModel<BlendFunction>::AccessCurrentModel(TCallback&& InCallback)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L77 _function_ `` (scope `UE::CurveEditorTools::TContextAwareTweeningModel::StartBlendOperation`)
- L86 _function_ `` (scope `UE::CurveEditorTools::TContextAwareTweeningModel::StopBlendOperation`)
- L95 _function_ `` (scope `UE::CurveEditorTools::TContextAwareTweeningModel::BlendValues`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Extensions/Tweening/CurveEditorTweenModels.h` (Private)


#### class `UE::CurveEditorTools::FCurveEditorTweenModels`  
`class FCurveEditorTweenModels : public TweeningUtilsEditor::FTweenModelArray`  
_L12-17_
- inherits: `TweeningUtilsEditor::FTweenModelArray`
- desc: Knows of the tween models used in curve editor.
- L16 _public prototype_ `explicit FCurveEditorTweenModels(const TWeakPtr<FCurveEditor> InCurveEditor);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Extensions/Tweening/KeyInsertingTweenModel.h` (Private)


#### class `UE::CurveEditorTools::TKeyInsertingTweenModel`  
`template<TweeningUtilsEditor::EBlendFunction BlendFunction> class TKeyInsertingTweenModel : public TweeningUtilsEditor::TCurveTweenModel<BlendFunction>`  
_L14-24_
- inherits: `TweeningUtilsEditor::TCurveTweenModel<BlendFunction>`
- desc: Inserts keys of visible curves into the current scrubber position.
- L16 _private typedef_ `using Super = TweeningUtilsEditor::TCurveTweenModel<BlendFunction>;`
- L19 _public function_ `explicit TKeyInsertingTweenModel(TWeakPtr<FCurveEditor> InWeakCurveEditor) : Super(MoveTemp(InWeakCurveEditor))`
- L22 _public prototype_ `virtual void StartBlendOperation() override;`
- L30 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> void TKeyInsertingTweenModel<BlendFunction>::StartBlendOperation()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Extensions/Tweening/TweenEditorExtension.h` (Private)


#### class `UE::CurveEditorTools::FTweenEditorExtension`  
`class FTweenEditorExtension : public ICurveEditorExtension, public FNoncopyable`  
_L18-42_
- inherits: `ICurveEditorExtension,FNoncopyable`
- desc: Manages the tweening tool in the curve editor.
- L22 _public prototype_ `explicit FTweenEditorExtension(TWeakPtr<FCurveEditor> InCurveEditor);`
- L25 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> InCommandList) override;`
- L26 _public prototype_ `virtual TSharedPtr<FExtender> MakeToolbarExtender(const TSharedRef<FUICommandList>& InCommandList) override;`
- L32 _private member_ `const TWeakPtr<FCurveEditor> WeakCurveEditor;` — The editor that owns us.
- L35 _private member_ `const TSharedRef<FCurveEditorTweenModels> TweenModelContainer;` — Holds the functions that ToolbarController shows: just the default, built-in ones.
- L38 _private member_ `TOptional<TweeningUtilsEditor::FTweenControllers> TweenControllers;` — Created by InitControllers.
- L41 _private prototype_ `bool InitControllers(TSharedRef<FUICommandList> InCommandList);` — Makes sure that ToolbarController is created.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TweeningUtilsEditor` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Filters/CurveEditorFFTFilter.h` (Private)


#### enum `ECurveEditorFFTFilterClass`  
`enum class ECurveEditorFFTFilterClass : uint8`  
_L13-17_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Butterworth`
- L16 _public enumerator_ `Chebyshev`

#### enum `ECurveEditorFFTFilterType`  
`enum class ECurveEditorFFTFilterType : uint8`  
_L20-24_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `Lowpass`
- L23 _public enumerator_ `Highpass`

#### class `UCurveEditorFFTFilter`  
`class UCurveEditorFFTFilter : public UCurveEditorFilterBase`  
_L27-50_
- reflection: `UCLASS(DisplayName="Fourier Transform (FFT)")`
- inherits: `UCurveEditorFilterBase`
- L31 _protected prototype_ `void ApplyFilter_Impl(TSharedRef<FCurveEditor> InCurveEditor, const TMap<FCurveModelID, FKeyHandleSet>& InKeysToOperateOn, TMap<FCurveModelID, FKeyHandleSet>& OutKeysToSelect) override;`
- L33 _public prototype_ `UCurveEditorFFTFilter();`
- L37 _public member_ `float CutoffFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, UIMax = 1), Category="Settings")` — Normalized between 0-1. In a low pass filter, the lower the value is the smoother the output. In a high pass filter the higher the value the smoother the output.
- L41 _public member_ `ECurveEditorFFTFilterType Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Which frequencies are allowed through. For example, low-pass will let low frequency through and remove high frequency noise.
- L45 _public member_ `ECurveEditorFFTFilterClass Response;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Which FFT filter implementation to use.
- L49 _public member_ `int32 Order;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=1, UIMax=8), Category = "Settings")` — The number of samples used to filter in the time domain. It maps how steep the roll off is for the filter.

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Misc/CurvePointSnapper.h` (Private)


#### class `UE::CurveEditorTools::FCurvePointSnapper`  
`class FCurvePointSnapper`  
_L17-38_
- desc: Util that you can snap points according to a curve editor's snapping settings.
- L22 _public prototype_ `static TOptional<FCurvePointSnapper> MakeSnapper(FCurveEditor& InCurveEditor, const FCurveModelID& InCurveModelId);` — @return Unset if there's no curve view from which to get the FCurveEditorScreenSpace transform.
- L25 _public prototype_ `FVector2D SnapPoint(const FVector2D& InCurveSpacePoint, EKeyMoveMode InDragMode = EKeyMoveMode::Unrestricted) const;` — Snaps the point as per the snapping settings
- L28 _public prototype_ `FKeyPosition SnapKey(const FKeyPosition& InKeyPosition, EKeyMoveMode InDragMode = EKeyMoveMode::Unrestricted) const;` — Snaps the key as per the snapping settings
- L32 _private function_ `explicit FCurvePointSnapper(const FCurveEditorScreenSpace& InCurveSpace, const FCurveSnapMetrics& InMetrics) : CurveSpace(InCurveSpace), SnapMetrics(InMetrics)`
- L36 _private member_ `const FCurveEditorScreenSpace CurveSpace;`
- L37 _private member_ `const FCurveSnapMetrics SnapMetrics;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Misc/CurveViewRebuildListener.h` (Private)


#### class `UE::CurveEditorTools::FCurveViewRebuildListener`  
`class FCurveViewRebuildListener : public FNoncopyable`  
_L18-36_
- inherits: `FNoncopyable`
- desc: Invokes OnCurveViewRebuilt when the curve editor's SCurveEditorPanel::OnPostRebuildCurveViews is invoked. This handles clean-up, etc. so the using code does not need to worry about it.
- L22 _public prototype_ `explicit FCurveViewRebuildListener(const TSharedRef<FCurveEditor>& InCurveEditor);`
- L23 _public prototype_ `~FCurveViewRebuildListener();`
- L25 _public function_ `FSimpleMulticastDelegate& OnCurveViewRebuilt()`
- L30 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Used to unsubscribe on destruction.
- L33 _private member_ `FSimpleMulticastDelegate OnCurveModifiedDelegate;` — Invokes when any of the listeners is changed.
- L35 _private function_ `void BroadcastOnCurveModified() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Misc/VectorMathUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L11 _prototype_ `bool IsPointInTriangle(const FVector2D& Point, const FVector2D& Vertex1, const FVector2D& Vertex2, const FVector2D& Vertex3);` (scope `UE::CurveEditorTools`) — @return Whether Point is in the triangle spanned by the input vertices.
- L13 _prototype_ `void InsetQuadBy(FVector2D& A, FVector2D& B, FVector2D& C, FVector2D& D, float InsetAmount);` (scope `UE::CurveEditorTools`) — @return Makes a smaller quad in the same shape but with the edges moved inside by InsetAmount.
- L23 _prototype_ `FTransform2d TransformRectBetweenSpaces( const FVector2D& InMinSource, const FVector2D& InMaxSource, const FVector2D& InMinTarget, const FVector2D& InMaxTarget );` (scope `UE::CurveEditorTools`) — Computes the transform for transforming a rectangle from source space to another target space. @param InMinSource The bottom left corner of the rectangle in absolute space @param InMaxSource The top right corner of the rectangle in absolute space @param InMinTarget The equivalent bottom left corner in curve space @param InMaxTarget The equivalent top right corner in curve space
- L38 _prototype_ `FVector2D TransformAbsoluteToCurveSpace(const FTransform2d& InAbsToCurveSpace, const FVector2D& InPoint);` (scope `UE::CurveEditorTools`) — Transforms a point from absolute key space to a SCurveEditorView's curve space. Absolute key space are the literal FKeyPosition::InputValue and OutputValue. Curve space are the axis values the SCurveEditorView displays the keys at (e.g. in Normalized the max value is displayed at curve space value 1.0). @param InAbsToCurveSpace Result of SCurveEditorView::GetViewToCurveTransform @param InPoint The point in absolute space to transform @return The point in curve space
- L49 _prototype_ `FVector2D TransformCurveSpaceToAbsolute(const FTransform2d& InAbsToCurveSpace, const FVector2D& InPoint);` (scope `UE::CurveEditorTools`) — Transforms a point from SCurveEditorView's curve space to absolute key space. Absolute key space are the literal FKeyPosition::InputValue and OutputValue. Curve space are the axis values the SCurveEditorView displays the keys at (e.g. in Normalized the max value is displayed at curve space value 1.0). @param InAbsToCurveSpace Result of SCurveEditorView::GetViewToCurveTransform @param InPoint The point in curve space to transform @return The point in absolute space

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/CurveEditorMultiScaleTool.h` (Private)


#### enum `EMultiScaleAnchorFlags`  
`enum class EMultiScaleAnchorFlags : uint8`  
_L19-26_
- L21 _public enumerator_ `None = 0x00`
- L22 _public enumerator_ `XSlider = 0x01`
- L23 _public enumerator_ `YSlider = 0x02`
- L24 _public enumerator_ `XSidebar = 0x04`
- L25 _public enumerator_ `YSidebar = 0x08`

#### enum `EMultiScalePivotType`  
`enum class EMultiScalePivotType : uint8`  
_L31-37_
- reflection: `UENUM()`
- L33 _public enumerator_ `Average`
- L34 _public enumerator_ `BoundCenter`
- L35 _public enumerator_ `FirstKey`
- L36 _public enumerator_ `LastKey`

#### struct `FCurveEditorMultiScaleWidget`  
`struct FCurveEditorMultiScaleWidget`  
_L39-75_
- L41 _public function_ `FCurveEditorMultiScaleWidget()`
- L48 _public member_ `EMultiScaleAnchorFlags SelectedAnchorFlags;`
- L50 _public function_ `FGeometry MakeGeometry(const FGeometry& InWidgetGeometry) const`
- L55 _public prototype_ `EMultiScaleAnchorFlags GetAnchorFlagsForMousePosition(const FGeometry& InWidgetGeometry, float InUIXScaleFactor, float InUIYScaleFactor, const FVector2D& InMouseScreenPosition) const;`
- L57 _public prototype_ `void GetXSidebarGeometry(const FGeometry& InWidgetGeometry, const FGeometry& InViewGeometry, bool bInSelected, FGeometry& OutSidebar) const;`
- L58 _public prototype_ `void GetYSidebarGeometry(const FGeometry& InWidgetGeometry, const FGeometry& InViewGeometry, bool bInSelected, FGeometry& OutSidebar) const;`
- L60 _public prototype_ `void GetXSliderGeometry(const FGeometry& InWidgetGeometry, float InUIScaleFactor, FGeometry& OutSlider) const;`
- L61 _public prototype_ `void GetYSliderGeometry(const FGeometry& InWidgetGeometry, float InUIScaleFactor, FGeometry& OutSlider) const;`
- L63 _public member_ `FVector2D Size;`
- L64 _public member_ `FVector2D Position;`
- L65 _public member_ `bool Visible;`
- L67 _public member_ `FVector2D ParentSpaceDragBegin;`
- L70 _public member_ `FVector2D BoundsSize;` — stores the physical bounds instead of the marquee bounds, for scale calculations
- L71 _public member_ `FVector2D BoundsPosition;`
- L73 _public member_ `FVector2D StartSize;`
- L74 _public member_ `FVector2D StartPosition;`

#### struct `FMultiScaleToolOptions`  
`struct FMultiScaleToolOptions`  
_L78-90_
- reflection: `USTRUCT()`
- L83 _public member_ `float XScale = 1.f;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L86 _public member_ `float YScale = 1.f;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L89 _public member_ `EMultiScalePivotType PivotType = EMultiScalePivotType::Average;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`

#### class `FCurveEditorMultiScaleTool`  
`class FCurveEditorMultiScaleTool : public ICurveEditorToolExtension`  
_L92-186_
- inherits: `ICurveEditorToolExtension`
- L95 _public function_ `FCurveEditorMultiScaleTool(TWeakPtr<FCurveEditor> InCurveEditor) : WeakCurveEditor(InCurveEditor)`
- L104 _public prototype_ `virtual void OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — ICurveEditorToolExtension
- L105 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L106 _public prototype_ `virtual FReply OnMouseButtonDown(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L107 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(TSharedRef<SWidget> OwningWidget, const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L108 _public prototype_ `virtual FReply OnMouseButtonUp(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L109 _public prototype_ `virtual FReply OnMouseMove(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L110 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L111 _public function_ `virtual void OnToolActivated() override`
- L112 _public function_ `virtual void OnToolDeactivated() override`
- L113 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> CommandBindings) override;`
- L115 _public function_ `TSharedPtr<FStructOnScope> GetToolOptions() const override`
- L116 _public prototype_ `virtual void OnToolOptionsUpdated(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L117 _public prototype_ `virtual FText GetLabel() const override;`
- L118 _public prototype_ `virtual FText GetDescription() const override;`
- L119 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L123 _private prototype_ `void OnDragStart();`
- L124 _private prototype_ `void OnDrag(const FPointerEvent& InMouseEvent, const FVector2D& InMousePosition);`
- L125 _private prototype_ `void OnDragEnd();`
- L126 _private prototype_ `void StopDragIfPossible();`
- L127 _private prototype_ `void UpdateBoundingBox();`
- L129 _private prototype_ `void ScaleUnique(const FVector2D& InChangeAmount, const bool bInAffectsX, const bool bInAffectsY);`
- L139 _private prototype_ `void ApplyLastKeyPositions();` — Calls SetKeyPositions with FKeyData::LastDraggedKeyPositions and EPropertyChangeType::ValueSet tro trigger any final operations. Some FCurveModels, such as Sequencer's FCurveChannelModel, perform special operations with EPropertyChangeType::ValueSet, e.g. cleansing of stacked values. Called at end of drag.
- L143 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Weak pointer back to the owning curve editor.
- L146 _private member_ `TUniquePtr<UE::CurveEditor::FScopedCurveChange> ActiveTransaction;` — The currently open transaction (if any)
- L149 _private member_ `TOptional<FDelayedDrag> DelayedDrag;` — Set when attempting to move a drag handle.
- L150 _private member_ `TOptional<FVector2D> DragDelta;`
- L152 _private member_ `TOptional<UE::CurveEditor::FTangentSelectionFlattener> TangentFlattener;` — Squishes the tangents vertically depending on how much we move the keys vertically.
- L174 _private member_ `TArray<FKeyData> KeysByCurve;` — Key dragging data stored per-curve
- L175 _private member_ `TRange<double> InputMinMax;`
- L178 _private member_ `FMultiScaleToolOptions ToolOptions;` — UStruct that displays properties to be modified on screen
- L179 _private member_ `TSharedPtr<FStructOnScope> ToolOptionsOnScope;`
- L182 _private member_ `FCurveEditorMultiScaleWidget MultiScaleWidget;` — Multi select widget to store selection's current state
- L185 _private prototype_ `FVector2D GetPivot(FCurveModel* InCurve, const TArray<FKeyPosition>& InKeyPositions) const;`

#### struct `FCurveEditorMultiScaleTool::FKeyData`  
`struct FKeyData`  
_L155-171_
- desc: Used to cache selected key data when doing transform operations
- L157 _public function_ `FKeyData(FCurveModelID InCurveID) : CurveID(InCurveID)`
- L162 _public member_ `FCurveModelID CurveID;` — The curve that contains the keys we're dragging
- L164 _public member_ `TArray<FKeyHandle> Handles;` — All the handles within a given curve that we are dragging
- L166 _public member_ `TArray<FKeyPosition> StartKeyPositions;` — The extended key info for each of the above handles
- L168 _public member_ `TArray<FKeyPosition> LastDraggedKeyPositions;` — Used in OnEndDrag to send final key updates
- L170 _public member_ `FVector2D Pivot;` — Pivot to scale from

#### Free symbols / members of external scopes

- L28 _prototype_ `ENUM_CLASS_FLAGS(EMultiScaleAnchorFlags);`

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/CurveEditorTransformTool.h` (Private)


#### enum `ECurveEditorAnchorFlags`  
`enum class ECurveEditorAnchorFlags : uint16`  
_L18-32_
- L20 _public enumerator_ `None = 0x00`
- L21 _public enumerator_ `Top = 0x01`
- L22 _public enumerator_ `Left = 0x02`
- L23 _public enumerator_ `Right = 0x04`
- L24 _public enumerator_ `Bottom = 0x08`
- L25 _public enumerator_ `Center = 0x10`
- L26 _public enumerator_ `FalloffTopLeft = 0x20`
- L27 _public enumerator_ `FalloffTopRight = 0x40`
- L28 _public enumerator_ `FalloffLeft = 0x80`
- L29 _public enumerator_ `FalloffRight = 0x100`
- L30 _public enumerator_ `FalloffAll = FalloffTopLeft | FalloffTopRight | FalloffLeft | FalloffRight`
- L31 _public enumerator_ `ScaleCenter = 0x200`

#### enum `EToolTransformInterpType`  
`enum class EToolTransformInterpType : uint8`  
_L35-44_
- reflection: `UENUM()`
- L37 _public enumerator_ `Linear`
- L38 _public enumerator_ `Sinusoidal`
- L39 _public enumerator_ `Cubic`
- L40 _public enumerator_ `CircularIn`
- L41 _public enumerator_ `CircularOut`
- L42 _public enumerator_ `ExpIn`
- L43 _public enumerator_ `ExpOut`

#### struct `FCurveEditorTransformWidget`  
`struct FCurveEditorTransformWidget`  
_L48-84_
- L50 _public function_ `FCurveEditorTransformWidget()`
- L57 _public member_ `ECurveEditorAnchorFlags SelectedAnchorFlags;`
- L58 _public member_ `ECurveEditorAnchorFlags DisplayAnchorFlags;`
- L60 _public function_ `FGeometry MakeGeometry(const FGeometry& InWidgetGeometry) const`
- L65 _public prototype_ `ECurveEditorAnchorFlags GetAnchorFlagsForMousePosition(const FGeometry& InWidgetGeometry, float FalloffHeight, float FalloffWidth, const FVector2D& RelativeScaleCenter, const FVector2D& InMouseScreenPosition) const;`
- L67 _public prototype_ `void GetCenterGeometry(const FGeometry& InWidgetGeometry, FGeometry& OutCenter) const;`
- L68 _public prototype_ `void GetSidebarGeometry(const FGeometry& InWidgetGeometry, FGeometry& OutLeft, FGeometry& OutRight, FGeometry& OutTop, FGeometry& OutBottom) const;`
- L69 _public prototype_ `void GetCornerGeometry(const FGeometry& InWidgetGeometry, FGeometry& OutTopLeft, FGeometry& OutTopRight, FGeometry& OutBottomLeft, FGeometry& OutBottomRight) const;`
- L70 _public prototype_ `void GetFalloffGeometry(const FGeometry& InWidgetGeometry, float FalloffHeight, float FalloffWidth, FGeometry& OutTopLeft, FGeometry& OutTopRight, FGeometry& OutLeft, FGeometry& OutRight) const;`
- L71 _public prototype_ `void GetScaleCenterGeometry(const FGeometry& InWidgetGeometry, FVector2D ScaleCenter, FGeometry& OutInputBoxGeometry) const;`
- L72 _public prototype_ `void GetCenterIndicatorGeometry(const FGeometry& InWidgetGeometry, FGeometry& OutCenterIndicatorGeometry) const;`
- L74 _public member_ `FVector2D Size;`
- L75 _public member_ `FVector2D Position;`
- L76 _public member_ `bool Visible;`
- L79 _public member_ `FVector2D BoundsSize;` — stores the physical bounds instead of the marquee bounds, for scale calculations
- L80 _public member_ `FVector2D BoundsPosition;`
- L82 _public member_ `FVector2D StartSize;`
- L83 _public member_ `FVector2D StartPosition;`

#### struct `FTransformToolOptions`  
`struct FTransformToolOptions`  
_L87-112_
- reflection: `USTRUCT()`
- L92 _public member_ `float UpperBound = 0.f;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L95 _public member_ `float LowerBound = 0.f;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L98 _public member_ `FFrameNumber LeftBound;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L101 _public member_ `FFrameNumber RightBound;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L104 _public member_ `FFrameNumber ScaleCenterX;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L107 _public member_ `float ScaleCenterY = 0.f;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions)`
- L111 _public member_ `EToolTransformInterpType FalloffInterpType = EToolTransformInterpType::Linear;` — `UPROPERTY(Transient, EditAnywhere, Category = ToolOptions, Meta = (ToolTip = "Interpolation type for soft selection (activate by holding ctrl)"))` — specifies the falloff type applied to curve selection

#### class `FCurveEditorTransformTool`  
`class FCurveEditorTransformTool : public ICurveEditorToolExtension`  
_L114-222_
- inherits: `ICurveEditorToolExtension`
- L117 _public function_ `FCurveEditorTransformTool(TWeakPtr<FCurveEditor> InCurveEditor) : WeakCurveEditor(InCurveEditor) , FalloffHeight(0.0f) , FalloffWidth(0.0f) , RelativeScaleCenter(FVector2D(0.5f, 0.5f)) , DisplayRelativeScaleCenter(FVector2D(0.5f, 0.5f))`
- L128 _public prototype_ `virtual void OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — ICurveEditorToolExtension Interface
- L129 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L130 _public prototype_ `virtual void OnToolActivated() override;`
- L131 _public prototype_ `virtual void OnToolDeactivated() override;`
- L132 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> CommandBindings) override;`
- L133 _public prototype_ `virtual FReply OnMouseButtonDown(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L134 _public prototype_ `virtual FReply OnMouseMove(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L135 _public prototype_ `virtual FReply OnMouseButtonUp(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L136 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent);`
- L137 _public function_ `TSharedPtr<FStructOnScope> GetToolOptions() const override`
- L138 _public prototype_ `virtual void OnToolOptionsUpdated(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L139 _public prototype_ `virtual FText GetLabel() const override;`
- L140 _public prototype_ `virtual FText GetDescription() const override;`
- L141 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L145 _private prototype_ `void UpdateMarqueeBoundingBox();`
- L146 _private prototype_ `void UpdateToolOptions();`
- L147 _private prototype_ `void DrawMarqueeWidget(const FCurveEditorTransformWidget& InTransformWidget, const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, const int32 InPaintOnLayerId, const FWidgetStyle& InWidgetStyle, const bool bInParentEnabled) const;`
- L148 _private prototype_ `void ScaleFrom(const FVector2D& InPanelSpaceCenter, const FVector2D& InChangeAmount, const bool bInFalloffOn, const bool bInAffectsX, const bool bInAffectsY);`
- L150 _private prototype_ `void OnDragStart();`
- L151 _private prototype_ `void OnDrag(const FPointerEvent& InMouseEvent, const FVector2D& InLocalMousePosition);`
- L152 _private prototype_ `void OnDragEnd();`
- L153 _private prototype_ `void StopDragIfPossible();`
- L157 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Weak pointer back to the Curve Editor this belongs to.
- L160 _private member_ `TUniquePtr<UE::CurveEditor::FScopedCurveChange> ActiveTransaction;` — The currently open transaction (if any)
- L163 _private member_ `FCurveEditorTransformWidget TransformWidget;` — Cached information about our transform tool such as interaction state, etc.
- L166 _private member_ `TOptional<FDelayedDrag> DelayedDrag;` — Set when attempting to move a drag handle. This allows us to tell the difference between a click and a click-drag.
- L168 _private member_ `TOptional<UE::CurveEditor::FTangentSelectionFlattener> TangentFlattener;` — Squishes the tangents vertically depending on how much we move the keys vertically.
- L188 _private member_ `TArray<FKeyData> KeysByCurve;` — Key dragging data stored per-curve
- L189 _private member_ `TRange<double> InputMinMax;`
- L191 _private member_ `FVector2D InitialMousePosition;`
- L192 _private member_ `FVector2D LastMousePosition;`
- L193 _private member_ `FCurveEditorAxisSnap::FSnapState SnappingState;`
- L196 _private member_ `FTransformToolOptions ToolOptions;` — UStruct that displays properties to be modified on screen
- L197 _private member_ `TSharedPtr<FStructOnScope> ToolOptionsOnScope;`
- L201 _private member_ `float FalloffHeight;` — Soft Selection Height, if 0.0 as we go up to 1.0 we go up to the top edge
- L203 _private member_ `float FalloffWidth;` — Soft Selection Width, if 0.0 we peak directly at the midpoint gradually scaling out till we reach 1.0fff
- L206 _private member_ `bool bCurvesHaveSameScales;` — Whether or not the selections have the same view transforms
- L209 _private member_ `FVector2D RelativeScaleCenter;` — point to scale from, relative to current bounds
- L212 _private member_ `FVector2D DisplayRelativeScaleCenter;` — Same as the above, but flipped when the scale amount is inverted for display
- L215 _private prototype_ `double GetFalloffWeight(double InputValue) const;` — Get Soft Select Change Based upon Input Value and internal soft selection weight values
- L218 _private prototype_ `double ModifyWeightByInterpType(double Weight) const;` — Modify the Falloff Weight by type of Interpolation
- L221 _private member_ `uint32 SelectionSerialNumber = 0;` — Selection serial number, used to update the toolbox

#### struct `FCurveEditorTransformTool::FKeyData`  
`struct FKeyData`  
_L171-185_
- desc: Used to cache selected key data when doing transform operations
- L173 _public function_ `FKeyData(FCurveModelID InCurveID) : CurveID(InCurveID)`
- L178 _public member_ `FCurveModelID CurveID;` — The curve that contains the keys we're dragging
- L180 _public member_ `TArray<FKeyHandle> Handles;` — All the handles within a given curve that we are dragging
- L182 _public member_ `TArray<FKeyPosition> StartKeyPositions;` — The extended key info for each of the above handles
- L184 _public member_ `TArray<FKeyPosition> LastDraggedKeyPositions;` — Used in OnEndDrag to send final key updates

#### Free symbols / members of external scopes

- L46 _prototype_ `ENUM_CLASS_FLAGS(ECurveEditorAnchorFlags);`

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/CurveEditorLatticeTool.h` (Private)


#### class `UE::CurveEditorTools::FCurveEditorLatticeTool`  
`class FCurveEditorLatticeTool : public ICurveEditorToolExtension, public FGCObject`  
_L45-180_
- inherits: `ICurveEditorToolExtension,FGCObject`
- desc: Places a lattice deformer over the selection. The lattice is a quadrilateral you can reshape by moving the points or edges. Reshaping the quad recomputes the underlying key positions. The lattice does mirroring when: - Dragging top edge down / bottom edge up: As the edge moves closer to the opposite edge, user set tangents are flattened and then inverted. - Dragging a control point to the top / bottom edge: Similar as the previous case but a fallout is applied to the key to the left / right of the control point. See documentation on FLatticeDeformerState::Deformer and FLatticeDeformerState::PerCurveData to understand the linear spaces the lattice math operates on.
- L49 _public prototype_ `explicit FCurveEditorLatticeTool(TWeakPtr<FCurveEditor> InCurveEditor);`
- L53 _public prototype_ `virtual void Tick(const FGeometry& InViewContainerGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L54 _public prototype_ `virtual void OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InViewContainerGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InPaintOnLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L55 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(TSharedRef<SWidget> OwningWidget, const FGeometry& InViewContainerGeometry, const FPointerEvent& InMouseEvent) override;`
- L56 _public prototype_ `virtual FReply OnMouseButtonDown(TSharedRef<SWidget> InOwningWidget, const FGeometry& InViewContainerGeometry, const FPointerEvent& InMouseEvent) override;`
- L57 _public prototype_ `virtual FReply OnMouseButtonUp(TSharedRef<SWidget> InOwningWidget, const FGeometry& InViewContainerGeometry, const FPointerEvent& MouseEvent) override;`
- L58 _public prototype_ `virtual FReply OnMouseMove(TSharedRef<SWidget> InOwningWidget, const FGeometry& InViewContainerGeometry, const FPointerEvent& InMouseEvent) override;`
- L59 _public prototype_ `virtual void OnFinishedPointerInput() override;`
- L60 _public prototype_ `virtual void OnToolActivated() override;`
- L61 _public prototype_ `virtual void OnToolDeactivated() override;`
- L62 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> CommandBindings) override;`
- L63 _public prototype_ `virtual FText GetLabel() const override;`
- L64 _public prototype_ `virtual FText GetDescription() const override;`
- L65 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L69 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L70 _public function_ `virtual FString GetReferencerName() const override`
- L76 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Weak pointer back to the owning curve editor.
- L79 _private member_ `TOptional<FLatticeDeformerState> LatticeDeformerState;` — Set when there is a valid selection in view.
- L82 _private member_ `TOptional<FLatticeControlsDrawData> DrawData;` — How to draw LatticeDeformer. Set only when the selection, over which the controls are drawn, is visible.
- L85 _private member_ `FVector2D FinalMouseScreenSpacePosition;` — The last mouse position received by OnMouseMove.
- L87 _private member_ `TOptional<FDelayedDragData> DelayedDragData;` — Data used to detect dragging.
- L93 _private member_ `TObjectPtr<UCurveEditorTools_LatticeUndoObject> UndoObject;` — We store the shape of the lattice grid before starting the drag operation. This way, we can restore the shape of the grid when the user undo-es.
- L96 _private prototype_ `void UpdateDeformerBounds(const TSharedRef<FCurveEditor>& InCurveEditor);` — Creates or destroys LatticeDeformer based on the selection.
- L99 _private prototype_ `void OnCurvesModified();` — Updates the bounds after the user has externally moved the keys, e.g. MMB move keys, etc.
- L101 _private prototype_ `void OnSelectionChanged();` — Skips recomputing the bounds if the selection was changed due us modifying curves (e.g. because of stacked keys being removed)
- L103 _private function_ `void OnCurvePanelRebuilt()` — Regenerates the lattice.
- L105 _private prototype_ `void OnTransactionStateChanged(const FTransactionContext& TransactionContext, ETransactionStateEventType TransactionStateEvent);`
- L108 _private prototype_ `void RecomputeLatticeGrid(const TSharedRef<FCurveEditor>& InCurveEditor, ELatticeUpdateFlags InRefreshFlags = ELatticeUpdateFlags::None);` — Call this if the keys have externally moved. Tries to fit the lattice grid over the keys or reconstructs a new rectangular one if not possible.
- L109 _private prototype_ `void RecomputeLatticeGrid(ELatticeUpdateFlags InRefreshFlags = ELatticeUpdateFlags::None);`
- L112 _private prototype_ `void RecomputeDrawData(const FGeometry& InViewContainerGeometry, const TSharedPtr<FCurveEditor>& InCurveEditor);` — Recomputes all draw data.
- L114 _private prototype_ `TArray<FVector2D> ComputeDrawControlPoints(const FCurveEditor& InCurveEditor) const;` — Populates the control points and edges.
- L115 _private prototype_ `TArray<FLatticeControlEdge> ComputeDrawControlEdges(TConstArrayView<FVector2D> InControlPoints) const;`
- L118 _private prototype_ `void CancelDrag();` — Stops the active drag operation.
- L120 _private prototype_ `void StartDragDrop(const FGeometry& InViewContainerGeometry, const FPointerEvent& InMouseEvent);` — Creates a drag-drop operation based on the hover state.
- L122 _private prototype_ `TOptional<FDragOpData> CreateDragDrop(const FLatticeBounds& InBounds, const FLatticeHoverState& InHoverState);` — Starts a new drag drop operation based on whether a control point, edge, or cell is hovered.
- L123 _private prototype_ `TOptional<FDragOpData> CreateDragDrop_Point(const FLatticeBounds& InBounds, int32 InControlPointIndex);`
- L124 _private prototype_ `TOptional<FDragOpData> CreateDragDrop_Edge(const FLatticeBounds& InBounds, int32 InEdgeIndex);`
- L125 _private prototype_ `TOptional<FDragOpData> CreateDragDrop_Cell(const FLatticeBounds& InBounds, int32 InCellIndex);`
- L128 _private typedef_ `using FMovePointsSignature = void(FCurveEditorLatticeTool::*)( FPerCurveDeformer2D& InDeformer, FCurveModel& InCurveModel, TConstArrayView<int32> InVertexIndices, TConstArrayView<FVector2D> InNewControlPointPositions, EPropertyChangeType::Type InChangeType, EKeyMoveMode InSnapMode );` — User actions: things the user can directly do in the UI.
- L134 _private prototype_ `void HandleDragPoints( FMovePointsSignature InMovePointsCallback, TConstArrayView<int32> InVertexIndices, TConstArrayView<FVector2D> InNewControlPoints, EPropertyChangeType::Type InChangeType, EKeyMoveMode InSnapMode );` — Handles dragging a control point, edge, or the lattice center.
- L139 _private prototype_ `void HandleMoveEdgeToOpposite(int32 InEdgeIndex);` — Handles double-clicking an edge.
- L141 _private prototype_ `void HandleMirrorGrid();` — Handles double-clicking the lattice center.
- L144 _private prototype_ `void OnMoveControlPoint( FPerCurveDeformer2D& InDeformer, FCurveModel& InCurveModel, TConstArrayView<int32> InVertexIndices, TConstArrayView<FVector2D> InNewControlPointPositions, EPropertyChangeType::Type InChangeType, EKeyMoveMode InSnapMode );` — Called when a control point is dragged.
- L149 _private prototype_ `void OnMoveEdge(FPerCurveDeformer2D& InDeformer, FCurveModel& InCurveModel, TConstArrayView<int32> InVertexIndices, TConstArrayView<FVector2D> InNewControlPointPositions, EPropertyChangeType::Type InChangeType, EKeyMoveMode InSnapMode );` — Called when an edge is dragged.
- L154 _private prototype_ `void OnSetControlPoints( FPerCurveDeformer2D& InDeformer, FCurveModel& InCurveModel, TConstArrayView<int32> InControlPointsToUpdate, TConstArrayView<FVector2D> InNewControlPoints, EPropertyChangeType::Type InChangeType, EKeyMoveMode InSnapMode = EKeyMoveMode::Unrestricted );` — Generic function for updating control points.
- L161 _private prototype_ `void MoveEdgeToOpposite(FPerCurveDeformer2D& InDeformer, FCurveModel& InCurveModel, FCurveEditor& InCurveEditor, int32 InEdgeIndex);` — Moves the clicked edge to the opposite edge, effectively flattening the curve sections.
- L163 _private prototype_ `void MirrorGrid(FPerCurveDeformer2D& InDeformer, FCurveModel& InCurveModel, FCurveEditor& InCurveEditor);` — Mirrors all points in the grid across an imaginary, x-axis aligned edge going through the grid center. Only if the grid consists of a single cell.
- L165 _private function_ `const FLatticeDeformer2D& GetGlobalDeformer() const`
- L166 _private function_ `FLatticeDeformer2D& GetGlobalDeformer()`
- L172 _private prototype_ `template<typename TCallback> requires std::is_invocable_r_v<bool, TCallback, const FLatticeHoverState&, const FLatticeBounds&, const FCurveEditor&> bool ComputeHoverStateForLeftClick(const FGeometry& InViewContainerGeometry, const FPointerEvent& InMouseEvent, TCallback&& InCallback);` — Invokes InCallback if there is a lattice grid shown and the user left clicks somewhere. @return False if InCallback was not invoked. Otherwise, whatever InCallback returned.
- L175 _private prototype_ `void UnregisterDelegates() const;` — Shared logic for unregistering global delegates.
- L178 _private prototype_ `void SaveUndoState(const FCurveEditor& InCurveEditor);` — Saves the undo state in the undo object.
- L179 _private prototype_ `bool ApplyUndoState(FCurveEditor& InCurveEditor);`
- L182 _function_ `inline void FCurveEditorLatticeTool::RecomputeLatticeGrid(ELatticeUpdateFlags InRefreshFlags)`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Drag/DelayedDragData.h` (Private)


#### struct `UE::CurveEditorTools::FDelayedDragData`  
`struct FDelayedDragData`  
_L14-32_
- desc: Data used while the user is holding down the left mouse button. Once the mouse has moved enough, we "detect" a drag.
- L17 _public member_ `FDelayedDrag DelayedDrag;` — Set when attempting to move a drag handle. This allows us to tell the difference between a click and a click-drag.
- L20 _public member_ `const FLatticeBounds Bounds;` — Bounds when the op was started.
- L22 _public member_ `const FLatticeHoverState HoverState;` — Hover state when the op was started.
- L25 _public member_ `TOptional<FDragOpData> ActiveOperation;` — Set if the drag up was started.
- L27 _public function_ `explicit FDelayedDragData( const FVector2D& InInitialPosition, const FKey& InEffectiveKey, const FLatticeBounds& InBounds, const FLatticeHoverState& InHoverState ) : DelayedDrag(InInitialPosition, InEffectiveKey), Bounds(InBounds), HoverState(InHoverState)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Drag/DragOpData.h` (Private)


#### struct `UE::CurveEditorTools::FDragOpData`  
`struct FDragOpData`  
_L15-46_
- desc: Data used after FDelayedDragData has detected a drag. The user is now actively dragging a control point, edge, or cell.
- L18 _public member_ `TUniquePtr<FLatticeDragOp> DragOp;` — Handles drags that started on a control point.
- L20 _public member_ `TUniquePtr<FScopedTransaction> Transaction;` — This transaction is active for the duration of the drag.
- L22 _public member_ `TUniquePtr<CurveEditor::FScopedCurveChange> KeyChange;` — Transactions the key changes
- L25 _public member_ `TMap<FCurveModelID, FLatticeEdgeTangentsMirrorOp> EdgeTangentMirroringOps;` — Adjust tangents while dragging on an edge.
- L27 _public member_ `TMap<FCurveModelID, FLatticePointTangentsMirrorOp> PointTangentMirroringOps;` — Adjusts tangents while dragging on a control point.
- L30 _public member_ `bool bSavedUndoState = false;` — False until the first drag actually changes keys. We only need to capture undo state just before the first change.
- L32 _public function_ `explicit FDragOpData(TWeakPtr<FCurveEditor> InCurveEditor, TUniquePtr<FLatticeDragOp> DragOp, const FText& TransactionText) : DragOp(MoveTemp(DragOp)) , Transaction(MakeUnique<FScopedTransaction>(TEXT("CurveEditorLatticeTool"), TransactionText, nullptr)) , KeyChange([InCurveEditor] { using namespace UE::CurveEditor; return MakeUnique<FScopedCurveChange>( FCurvesSnapshotBuilder( InCurveEditor, ECurveChangeFlags::MoveKeysAndRemoveStackedKeys | ECurveChangeFlags::KeyAttributes ).TrackSelectedCurves() ); }())`
- L36 _public function_ ``

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Drag/EKeyMoveMode.h` (Private)


#### enum `UE::CurveEditorTools::EKeyMoveMode`  
`enum class EKeyMoveMode : uint8`  
_L11-22_
- desc: Describes how keys are supposed to be snapped when using the lattice tool.
- L14 _public enumerator_ `Unrestricted` — Mouse is unlocked, i.e can move freely in 2D space.
- L17 _public enumerator_ `IgnoreX` — Do not move the keys in X direction. E.g. when user has shift pressed and is moving up / down (in y direction).
- L19 _public enumerator_ `IgnoreY` — Do not move the keys in Y direction. E.g. when user has shift pressed and is moving left / right (in x direction).
- L21 _public enumerator_ `IgnoreAll = IgnoreY | IgnoreX`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L23 _prototype_ `ENUM_CLASS_FLAGS(EKeyMoveMode);` (scope `UE::CurveEditorTools`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Drag/LatticeDragOp.h` (Private)


#### class `UE::CurveEditorTools::FLatticeDragOp`  
`class FLatticeDragOp`  
_L18-73_
- desc: Handles updating the lattice deformer's control point(s) in response to a drag.
- L22 _public prototype_ `explicit FLatticeDragOp(TWeakPtr<FCurveEditor> InCurveEditor);`
- L24 _public prototype_ `void BeginDrag(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, const FVector2D& InInitialMousePosition);`
- L25 _public prototype_ `void MoveMouse(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);`
- L26 _public prototype_ `void FinishedPointerInput();`
- L27 _public prototype_ `void EndDrag(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);`
- L28 _public prototype_ `void CancelDrag();`
- L30 _public prototype_ `virtual ~FLatticeDragOp() = default;`
- L34 _protected function_ `virtual void OnBeginDrag(const FGeometry& InGeometry, const FVector2D& InInitialMousePosition, EKeyMoveMode InSnapMode)`
- L35 _protected function_ `virtual void OnMoveMouse(const FGeometry& InGeometry, const FVector2D& InScreenPosition, EKeyMoveMode InSnapMode)`
- L36 _protected function_ `virtual void OnEndDrag(const FGeometry& InGeometry, const FVector2D& InMousePosition, EKeyMoveMode InSnapMode)`
- L37 _protected function_ `virtual void OnCancelDrag()`
- L39 _protected function_ `TWeakPtr<FCurveEditor> GetCurveEditor() const`
- L40 _protected function_ `FVector2D GetInitialMousePosition() const`
- L45 _private member_ `const TWeakPtr<FCurveEditor> CurveEditor;` — Used to get snapping settings.
- L48 _private member_ `FVector2D InitialMousePosition;` — Set by OnBeginDrag.
- L50 _private member_ `FVector2D LastMousePosition;` — Used by the snap logic. Set every time mouse moved.
- L53 _private member_ `FCurveEditorAxisSnap::FSnapState SnapState;` — Passed to the snap logic
- L70 _private member_ `TOptional<FAccumulatedMouseMovement> AccumulatedMouseMovement;`
- L72 _private prototype_ `void AccumulateMouseMovement(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);`

#### struct `UE::CurveEditorTools::FLatticeDragOp::FAccumulatedMouseMovement`  
`struct FAccumulatedMouseMovement`  
_L55-69_
- L57 _public member_ `const FGeometry CachedGeometry;`
- L60 _public member_ `FVector2D AccumulatedPosition;` — The mouse position that has been accumulated by processing all pumped input this tick.
- L62 _public member_ `EKeyMoveMode LastDragMode;` — The mouse lock mode that has been accumulated by processing all pumped input this tick.
- L64 _public function_ `explicit FAccumulatedMouseMovement(const FGeometry& InCachedGeometry, const FVector2D& InInitialPosition, EKeyMoveMode InInitialDragMode) : CachedGeometry(InCachedGeometry) , AccumulatedPosition(InInitialPosition) , LastDragMode(InInitialDragMode)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Drag/LatticeDragOp_MoveControlPoints.h` (Private)


#### class `UE::CurveEditorTools::FLatticeDragOp_MoveControlPoints`  
`class FLatticeDragOp_MoveControlPoints : public FLatticeDragOp`  
_L20-63_
- inherits: `FLatticeDragOp`
- desc: Given an array of control points, invokes a delegate with the update control point locations based on the mouse movement.
- L24 _public typedef_ `using FOnBeginDragOperation = FSimpleDelegate;`
- L25 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnControlPointsMoved, const TConstArrayView<FVector2D>& InNewControlPointPositions, EKeyMoveMode InSnapMode);`
- L27 _public prototype_ `explicit FLatticeDragOp_MoveControlPoints( TWeakPtr<FCurveEditor> InCurveEditor, FControlPointArray InInitialControlPoints, const FLatticeBounds& InBounds, FOnBeginDragOperation InOnBeginDragControlPointsDelegate, FOnControlPointsMoved InInteractiveDragControlPointsDelegate, FOnControlPointsMoved InFinishDragControlPointsDelegate );`
- L39 _protected prototype_ `virtual void OnBeginDrag(const FGeometry& InGeometry, const FVector2D& InInitialMousePosition, EKeyMoveMode InSnapMode) override;`
- L40 _protected prototype_ `virtual void OnMoveMouse(const FGeometry& InGeometry, const FVector2D& InScreenPosition, EKeyMoveMode InSnapMode) override;`
- L41 _protected prototype_ `virtual void OnEndDrag(const FGeometry& InGeometry, const FVector2D& InMousePosition, EKeyMoveMode InSnapMode) override;`
- L47 _private member_ `const FControlPointArray InitialControlPoints;` — Initial positions of the control points.
- L49 _private member_ `const FLatticeBounds Bounds;` — Used to transform points
- L52 _private member_ `const FOnBeginDragOperation OnBeginDragControlPointsDelegate;` — Invoked when the drag operation begins. A call to OnFinishDragControlPointsDelegate will follow some time in the future.
- L54 _private member_ `const FOnControlPointsMoved OnInteractiveDragControlPointsDelegate;` — Invoked while the mouse button is down.
- L56 _private member_ `const FOnControlPointsMoved OnFinishDragControlPointsDelegate;` — Invoked one last time when the mouse button is lifted.
- L59 _private member_ `FControlPointArray UpdatedControlPointPositions;` — Updated every time the mouse moves: InitialControlPoints + DeltaMouseMove.
- L62 _private prototype_ `void UpdateControlPoints(const FGeometry& InGeometry, const FVector2D& InScreenPosition);` — Updates UpdatedControlPointPositions.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L17 _typedef_ `using FControlPointArray = TArray<FVector2D, TInlineAllocator<4>>;` (scope `UE::CurveEditorTools`)
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnControlPointsMoved, const TConstArrayView<FVector2D>& InNewControlPointPositions, EKeyMoveMode InSnapMode);`

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/LatticeControlsDrawData.h` (Private)


#### struct `UE::CurveEditorTools::FLatticeHoverState`  
`struct FLatticeHoverState`  
_L17-34_
- desc: Describes what is hovered in the control widget.
- L20 _public member_ `TOptional<int32> HoveredControlPoint;` — Index to ControlPointMatrix. Indicates hovered control point.
- L25 _public member_ `TOptional<int32> HoveredEdge;` — Index to edge. @see Indexing of edges in FLatticeDeformer2D.
- L31 _public member_ `TOptional<int32> HoveredCell;` — Index to the cell. @see Indexing of cells in FLatticeDeformer2D.
- L33 _public function_ `bool IsHovered() const`

#### struct `UE::CurveEditorTools::FLatticeControlsDrawData`  
`struct FLatticeControlsDrawData`  
_L42-54_
- desc: Holds the data required to draw a lattice control widget. This struct represents the exact information the drawing algorithm requires. The intention is that the drawing thus becomes as straighforward as possible. This way, if we wanted to, we could unit test the produced FLatticeControlsDrawData.
- L45 _public member_ `TArray<FVector2D> ControlPoints;` — The control points in the space of the SCurveEditorViewContainer (i.e. what's passed into ICurveEditorToolExtension::OnPaint).
- L47 _public member_ `TArray<FLatticeControlEdge> ControlEdges;` — The edges to draw
- L50 _public member_ `int32 MatrixWidth;` — Number of points in x-direction. Correlates with ControlPoints.Num().
- L53 _public member_ `FLatticeHoverState HoverState;` — Determines which index in ControlPoints or ControlEdges should be drawn as hovered.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/LatticeDeformer2D.h` (Private)


#### struct `UE::CurveEditorTools::FLatticeControlEdge`  
`struct FLatticeControlEdge`  
_L18-33_
- L21 _public member_ `FVector2D Points[2];` — This allows us to convert TArray<FLatticeControlEdge> to TArray<FVector2D> by just taking the pointer to Points.
- L23 _public function_ `const FVector2D& Start() const`
- L24 _public function_ `const FVector2D& End() const`
- L26 _public function_ `FVector2D& Start()`
- L27 _public function_ `FVector2D& End()`
- L29 _public function_ `explicit FLatticeControlEdge() : FLatticeControlEdge(FVector2D::ZeroVector, FVector2D::ZeroVector)`
- L30 _public function_ `explicit FLatticeControlEdge(const FVector2D& Start, const FVector2D& End) : Points`

#### struct `UE::CurveEditorTools::FPointIndex`  
`struct FPointIndex`  
_L36-44_
- desc: Describes how to locate a key in FLatticeDeformer2D
- L39 _public member_ `int32 CellIndex;` — Index of the cell in the lattice.
- L41 _public member_ `int32 IndexInCell;` — Index in the cell's key array.
- L43 _public function_ `explicit FPointIndex(int32 InCellIndex, int32 InIndexInCell) : CellIndex(InCellIndex), IndexInCell(InIndexInCell)`

#### class `UE::CurveEditorTools::FLatticeDeformer2D`  
`class FLatticeDeformer2D`  
_L76-176_
- desc: Implements a lattice deformer for 2D operations. ===== Indexing ==== Control points: 0---1---2---3 |   |   |   | 4---5---6---7 |   |   |   | 8---9--10--11 Below, x are control points and - / I are edges. Edge indices are numbered by rows then by columns, i.e. x--0--x--1--x 6     7     8 x--2--x--3--x 9     10    11 x--4--x--5--x Cells indices are numbered from top-left to bottom-right, i.e. x---x---x I 0 I 1 I x---x---x In the future, if FLatticeDeformer2D needs to be generalized / extracted from this module, FKeyInCurveId can become a templated parameter since FLatticeDeformer2D does not directly depend on it.
- L81 _public prototype_ `explicit FLatticeDeformer2D(int32 InNumCellsInX, int32 InNumCellsInY, const FVector2D& InBottomLeft, const FVector2D& InTopRight);` — Completely resets this deformer and sets a new grid.
- L84 _public prototype_ `void UpdateControlPoints( TConstArrayView<int32> InControlPointsToUpdate, TConstArrayView<FVector2D> InNewControlPoints, const TFunctionRef<void(const FPointIndex&, const FVector2D&)> HandleKeyChange );` — Moves the specified control points and recomputes the affected points.
- L90 _public prototype_ `void SetControlsPointNoRecompute(TConstArrayView<int32> InControlPointsToUpdate, TConstArrayView<FVector2D> InNewControlPoints);` — Sets the value of the control points without recomputing the values of the keys. Useful if you are resetting to a previous state.
- L93 _public function_ `TConstArrayView<FVector2D> GetControlPoints() const` — @return The control points, which is a flattened matrix.
- L95 _public prototype_ `FLatticeControlEdge GetControlEdge(int32 InEdgeIndex) const;` — @param InIndex 0 <= InIndex < GetNumEdges()
- L101 _public prototype_ `FEdgeVertexIndices GetEdgeIndices(int32 InEdgeIndex) const;` — @param InEdgeIndex 0 <= InEdgeIndex < NumEdges(). @return Indices to GetControlPoints or all INDEX_NONE if invalid.
- L106 _public prototype_ `FCellVertexIndices GetCellIndices(int32 InCellIndex) const;` — @param InCellIndex 0 <= InCellIndex < NumCells() @return Indices to GetControlPoints or all INDEX_NONE if invalid.
- L109 _public prototype_ `void SetKeyCoordsInCell(int32 InCellIndex, TArray<FLatticeKeyCoords> InNewKeyCoords);` — Sets the key coords of keys in the cell. This is useful for restoring previous data.
- L111 _public prototype_ `TConstArrayView<FLatticeKeyCoords> GetKeyCoordsInCell(int32 InCellIndex) const;` — @return The coordinates of the keys in the cell.
- L114 _public prototype_ `int32 FindCellContainingPoint(const FVector2D& InPoint) const;` — @return The vertices of the cell containing InPoint, or all INDEX_NONE if not contained.
- L117 _public prototype_ `int32 NumKeys() const;` — @return Counts the number of keys stored in all cells.
- L119 _public function_ `int32 NumControlPoints() const`
- L120 _public function_ `int32 NumPointsInWidth() const`
- L121 _public function_ `int32 NumPointsInHeight() const`
- L122 _public prototype_ `int32 NumEdges() const;`
- L123 _public function_ `int32 NumCellsInWidth() const`
- L124 _public function_ `int32 NumCellsInHeight() const`
- L125 _public prototype_ `int32 NumCells() const;`
- L138 _protected prototype_ `void AddPoints_BeforeLatticeMoved( TConstArrayView<FVector2D> InPoints, TFunctionRef<void(int32 InputIndex, const FPointIndex&)> OnPointIndexed = [](auto, auto){} );` — Adds the given points to the lattice grid. This function assumes that none of the control points have yet been moved: if so, the computed weights are incorrect. The computation of the weights requires that all cells are rectangular. Exposed only to subclasses so subclasses can control how points are added. If this was public, you could downcast sub-classes to this base class and break the Liskov-Substitution principle.
- L140 _protected function_ `TConstArrayView<FVector2D> InPoints, TFunctionRef<void(int32 InputIndex, const FPointIndex&)> OnPointIndexed = [](auto, auto)`
- L144 _protected prototype_ `FLatticeKeyCoords ComputeSingleCellWeights(const FCellVertexIndices& InIndices, const FVector2D& InPoint) const;` — Computes the weights for InKeyData such that only the corners of the cell it is in affect it.
- L149 _private member_ `const FIntPoint CellDimensions;` — The number of cells in X and Y direction.
- L157 _private member_ `TArray<FVector2D> ControlPoints;` — The control points of the deformer. Moving a control point causes the keys it affects to change transform as well. This is a flat matrix of dimension CellDimensions.X + 1 * CellDimensions.Y + 1, i.e. the 1st point in the 2nd row would be ControlPointMatrix[CellDimensions.X + 2]
- L169 _private member_ `TArray<FCellData> Cells;` — Caches which points belong to which cells. Moving a control point causes the keys it affects to change transform as well. This is a flat matrix of dimension CellDimensions.X * CellDimensions.Y , i.e. the 1st point in the 2nd row would be ControlPointMatrix[CellDimensions.X + 1]
- L172 _private prototype_ `void RecomputeCell(int32 InCellIndex, const TFunctionRef<void(const FPointIndex&, const FVector2D&)> HandleKeyChange);` — Recomputes all key positions in the cell. Call this when cell has changed its control points.
- L175 _private prototype_ `FVector2D RecomputeKeyValue(const FLatticeKeyCoords& InPointCoords, const FCellVertexIndices& InIndices) const;` — Computes the value the key should by computing the weighted linear product of all control points affecting it.

#### struct `UE::CurveEditorTools::FLatticeDeformer2D::FCellData`  
`struct FCellData`  
_L159-162_
- L161 _public member_ `TArray<FLatticeKeyCoords> KeyCoords;`

#### class `UE::CurveEditorTools::TLatticeDeformer2D`  
`template<typename TPointMetaData> class TLatticeDeformer2D : public FLatticeDeformer2D`  
_L180-252_
- inherits: `FLatticeDeformer2D`
- desc: Allows you to attach meta-data to each key position.
- L182 _private typedef_ `using Super = FLatticeDeformer2D;`
- L187 _public function_ `explicit TLatticeDeformer2D(int32 InNumCellsInX, int32 InNumCellsInY, const FVector2D& InBottomLeft, const FVector2D& InTopRight) : Super(InNumCellsInX, InNumCellsInY, InBottomLeft, InTopRight)` — Completely resets this deformer and sets a new grid.
- L199 _public function_ `void AddPoints_BeforeLatticeMoved(TConstArrayView<TPointMetaData> InKeys, TConstArrayView<FVector2D> InPoints)` — Computes the weights for each of the points. This function assumes that none of the control points have yet been moved: if so, the computed weights are incorrect. The computation of the weights requires that all cells are rectangular.
- L215 _public function_ `void UpdateControlPoints(TConstArrayView<int32> InControlPointsToUpdate, TConstArrayView<FVector2D> InNewControlPoints, const TFunctionRef<void(const TPointMetaData&, const FVector2D&)> HandleKeyChange )` — Moves the specified control points and recomputes the affected points.
- L228 _public function_ `TConstArrayView<TPointMetaData> GetCellMetaData(int32 InCellIndex) const` — @return The key IDs of the keys in the cell.
- L234 _public function_ `void SetCellMetaData(int32 InCellIndex, TArray<TPointMetaData> InNewKeyCoords)` — Sets the key IDs of the keys in the cell.
- L251 _private member_ `TArray<FCellMetaData> CellMetaData;` — Same length as FLatticeDeformer2D::Cells

#### struct `UE::CurveEditorTools::TLatticeDeformer2D::FCellMetaData`  
`struct FCellMetaData`  
_L244-248_
- L247 _public member_ `TArray<TPointMetaData> PointMetaData;` — Same length as the equivalent KeyCoords array of FCellData.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L47 _typedef_ `using FLatticeKeyCoords = FVector2D;` (scope `UE::CurveEditorTools`) — Identifies the normalized coordinates a key has in a cell.
- L207 _function_ `` (scope `UE::CurveEditorTools::TLatticeDeformer2D::AddPoints_BeforeLatticeMoved`)
- L221 _function_ `` (scope `UE::CurveEditorTools::TLatticeDeformer2D::UpdateControlPoints`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/LatticeDeformerState.h` (Private)


#### enum `UE::CurveEditorTools::ELatticeUpdateFlags`  
`enum class ELatticeUpdateFlags : uint8`  
_L17-31_
- L19 _public enumerator_ `None`
- L30 _public enumerator_ `TryRestoreBoundsFromUndo = 1 << 1` — Tries to restore the grid bounds from what is saved in the undo object. This is set when an undo operation is performed. If the data is compatible, the grid is restored to that and the grid is not recomputed. If the data is incompatible, the entire deformer is recomputed. The data may be incompatible, if e.g. you switched from normalized view to absolute view.

#### struct `UE::CurveEditorTools::FLatticeDeformerState`  
`struct FLatticeDeformerState`  
_L35-74_
- desc: Holds any data that exists only when the deformer exists. The deformer exists the selection consists of least 2 keys at different locations.
- L44 _public member_ `FTransform2d ControlPointToCurveSpace;` — Transforms the absolute Deformer.GetControlPoints(), which are just the FKeyPosition values, to curve space values of the current view. Reminder: CurveSpace are axis values that the SCurveEditorView displays on its axis. In Absolute mode, that's the literal FKeyPosition values In Normalized mode, Y is in 0 to 1 range (and X continues to be FKeyPosition::InputValue).
- L55 _public member_ `FGlobalLatticeDeformer2D GlobalDeformer;` — Empty "deformer" that exists purely for the UI. Its control points, edges, etc. are displayed in the view. Each curve has its own lattice deformer that actually moves that curves keys. The per curve deformers control points are the result of applying the per-curve transform to Deformer. This is needed to support all view modes (Absolute, Normalized, etc.) The Deformer's control points are always in absolute key space (i.e. exactly the values for FKeyPosition::InputValue and OutputValue).
- L56 _public member_ `TMap<FCurveModelID, FPerCurveLatticeData> PerCurveData;`
- L59 _public member_ `CurveEditor::FCurveChangeListener CurveChangeListener;` — Tells us when a curve is externally modified, so we can update the bounds.
- L61 _public member_ `FCurveViewRebuildListener PanelRebuildListener;` — Tells us when the panel is regenerated, in which case we must regenerate the lattice shape (e.g. could go from absolute -> normalized mode).
- L64 _public member_ `bool bIsModifyingCurves = false;` — Guard to not recompute bounds when FCurveModel::OnCurveModified broadcasts due to a change we have initiated.
- L66 _public member_ `bool bHasRequestedRefresh = false;` — If true, the curves have been modified and the lattice overlay should be recomputed next frame.
- L68 _public member_ `ELatticeUpdateFlags RefreshFlags = ELatticeUpdateFlags::None;` — The flags to use when bHasRequestedRefresh == true.
- L70 _public prototype_ `explicit FLatticeDeformerState(const FLatticeBounds& Lattice, const TSharedRef<FCurveEditor>& InCurveEditor);`
- L73 _public prototype_ `TArray<FVector2D> TransformControlPointsToCurveSpace() const;` — @return Control points transformed to SCurveEditorView's curve space.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L32 _prototype_ `ENUM_CLASS_FLAGS(ELatticeUpdateFlags);` (scope `UE::CurveEditorTools`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/LatticeFwd.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L14 _typedef_ `using FGlobalLatticeDeformer2D = FLatticeDeformer2D;` (scope `UE::CurveEditorTools`) — We never add any points to this deformer. It's just used to keep track of the control points & edges displayed in the view.
- L15 _typedef_ `using FPerCurveDeformer2D = TLatticeDeformer2D<FLatticePointMetaData>;` (scope `UE::CurveEditorTools`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/LatticePointMetaData.h` (Private)


#### struct `UE::CurveEditorTools::FLatticePointMetaData`  
`struct FLatticePointMetaData`  
_L12-21_
- desc: Extra that stored for each point added to the lattice grid.
- L15 _public member_ `FKeyHandle KeyHandle;` — The handle for the key this lattice point corresponds to.
- L18 _public member_ `FKeyPosition OriginalPosition;` — The position the key had before the lattice started moving it.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L23 _function_ `inline FArchive& operator<<(FArchive& InArchive, FLatticePointMetaData& InMetaData)` (scope `UE::CurveEditorTools`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Mirror/LatticeEdgeTangentMirrorOp.h` (Private)


#### class `UE::CurveEditorTools::FLatticeEdgeTangentsMirrorOp`  
`class FLatticeEdgeTangentsMirrorOp`  
_L23-65_
- desc: Provides functionality to drag the top or bottom edge of a lattice grid and mirror the tangents accordingly. @note This operation only affects the tangents. Key positions must be adjusted separately using the lattice grid algorithm.
- L31 _public prototype_ `static TOptional<FLatticeEdgeTangentsMirrorOp> MakeMirrorOpForDragLatticeEdge( int32 InEdgeIndex, const FCurveModelID& InCurveId, const FPerCurveDeformer2D& InDeformer, const FCurveEditor& InCurveEditor UE_LIFETIMEBOUND );` — Util function that creates a mirror op for dragging InEdgeIndex. @return Valid if InEdgeIndex is an edge that should do mirroring when dragged, i.e. a top or bottom edge
- L37 _public prototype_ `void OnMoveEdge(TConstArrayView<FVector2D> InNewEdge, const FCurveEditor& InCurveEditor);` — Call with info about where the new edge is located.
- L42 _private member_ `const int32 EdgeIndex;` — Indexs of the edge being moved.
- L54 _private member_ `FCurveMirrorData CurveMirrorData;` — Computes the tangents
- L56 _private function_ `explicit FLatticeEdgeTangentsMirrorOp(int32 InEdgeIndex, FCurveMirrorData InMirrorData) : EdgeIndex(InEdgeIndex), CurveMirrorData(MoveTemp(InMirrorData))`
- L61 _private prototype_ `static TOptional<FCurveMirrorData> ComputeTangentMirrorData( int32 InEdgeIndex, const FCurveEditor& InCurveEditor, const FLatticeDeformer2D& InCurveDeformer, const FCurveModelID& InCurve, TConstArrayView<FLatticePointMetaData> InMetaData );` — Tracks keys that have tangents that can be mirrored. The mirror midpoints are computed based off of InCurveDeformer.

#### struct `UE::CurveEditorTools::FLatticeEdgeTangentsMirrorOp::FCurveMirrorData`  
`struct FCurveMirrorData`  
_L44-52_
- L46 _public member_ `FCurveModelID CurveId;`
- L47 _public member_ `CurveEditor::FTangentMirrorSolver Solver;`
- L49 _public function_ `explicit FCurveMirrorData(FCurveModelID InCurveId, CurveEditor::FTangentMirrorSolver&& InSolver) : CurveId(InCurveId), Solver(MoveTemp(InSolver))`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Mirror/LatticePointTangentMirrorOp.h` (Private)


#### class `UE::CurveEditorTools::FLatticePointTangentsMirrorOp`  
`class FLatticePointTangentsMirrorOp`  
_L28-73_
- desc: Provides functionality to drag a control point of a lattice grid and mirror the tangents accordingly. This implementation differs from dragging an edge: a falloff is applied to all tangents. Tangents are flattened the full amount the closer they are to the dragged control point. Tangents of keys on the other side of the lattice grid are flattened less. @note This operation only affects the tangents. Key positions must be adjusted separately using the lattice grid algorithm.
- L36 _public prototype_ `static TOptional<FLatticePointTangentsMirrorOp> MakeMirrorOpForDragLatticeControlPoint( int32 InControlPointIndex, const FCurveModelID& InCurveId, const FPerCurveDeformer2D& InDeformer, const FCurveEditor& InCurveEditor UE_LIFETIMEBOUND );` — When dragging InControlPointIndex, checks whether the deformer contains keys that need mirroring, which are those that are user specified. @return Set if there were keys to mirror when dragging the specifiec control point. Unset otherwise.
- L42 _public prototype_ `void OnMovePoint(const FVector2D& InControlPoint, const FCurveEditor& CurveEditor);` — Call with info about where the new control point is located.
- L60 _private member_ `FCurveMirrorData CurveData;` — Per curve data for performing mirroring.
- L62 _private function_ `explicit FLatticePointTangentsMirrorOp(FCurveMirrorData&& InCurveData) : CurveData(MoveTemp(InCurveData))`
- L70 _private prototype_ `static TOptional<FCurveMirrorData> ComputeTangentMirrorData( int32 InControlPointIndex, const FCurveEditor& CurveEditor, const FCurveModelID& InCurveId, const FPerCurveDeformer2D& InDeformer );` — Adds all keys that can be mirrored to this operation. @return True, if any of the lattice's keys need mirroring.

#### struct `UE::CurveEditorTools::FLatticePointTangentsMirrorOp::FCurveMirrorData`  
`struct FCurveMirrorData`  
_L46-58_
- L49 _public member_ `FCurveModelID CurveId;` — CurveId of the curve whose tangents are being mirrored
- L51 _public member_ `CurveEditor::FTangentMirrorSolver TangentMirrorSolver;` — Mirrors the curve's keys.
- L53 _public member_ `TArray<float> FalloffValues;` — Equal length as TangentMirrorSolver.CurveData.KeyHandles. Contains the falloff values we pre-computed for each key.
- L55 _public function_ `explicit FCurveMirrorData(FCurveModelID CurveId, CurveEditor::FTangentMirrorSolver&& TangentMirrorSolver, TArray<float>&& FalloffValues) : CurveId(CurveId), TangentMirrorSolver(MoveTemp(TangentMirrorSolver)), FalloffValues(MoveTemp(FalloffValues))`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditor` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Mirror/MirrorUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L12 _function_ `inline double ChooseConsistentEdgeVert(ELatticeEdgeType EdgeType, const FVector2D& Vert1, const FVector2D& Vert2)` (scope `UE::CurveEditorTools`) — Consistenly chooses the same vertex on the top or bottom edge ASSUMING that the vertices are always transformed uniformly (e.g. move both up by x units, etc.)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Misc/DeformerUtils.h` (Private)


#### struct `UE::CurveEditorTools::FMoveEdgeToOppositeData`  
`struct FMoveEdgeToOppositeData`  
_L13-18_
- L15 _public member_ `int32 OppositeEdgeIndex;`
- L16 _public member_ `FEdgeVertexIndices EdgeIndices;`
- L17 _public member_ `FLatticeControlEdge EdgeControlPoints;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L21 _prototype_ `TOptional<FMoveEdgeToOppositeData> ComputeMoveEdgeToOppositeData(const FLatticeDeformer2D& InDeformer, int32 InEdgeIndex);` (scope `UE::CurveEditorTools`) — @return Information about the edge to move to the opposite. Can only move the top or bottom edge.

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Misc/LatticeDrawUtils.h` (Private)


#### struct `UE::CurveEditorTools::FLatticeBounds`  
`struct FLatticeBounds`  
_L32-51_
- L35 _public member_ `bool bIsVisible = false;` — If false, then do not discard the other values.
- L38 _public member_ `FVector2D MinValues;` — Absolute key values, i.e. FKeyPosition::InputValue, FKeyPosition::OutputValue.
- L39 _public member_ `FVector2D MaxValues;`
- L42 _public member_ `FVector2D MinSlatePosition;` — Values on screen, but transformed to screen space.
- L43 _public member_ `FVector2D MaxSlatePosition;`
- L47 _public member_ `FVector2d MinValuesCurveSpace;` — Axis values in curve space of the current view mode. For example, in normalized mode, where the Y-axis only has values from 0 to 1, a Y could be 0.8, etc.
- L48 _public member_ `FVector2d MaxValuesCurveSpace;`
- L50 _public prototype_ `static FLatticeBounds MakeCombined(const FLatticeBounds& InFirst, const FLatticeBounds& InOther);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L30 _prototype_ `FSlateLayoutTransform ComputeViewToViewContainerTransform(const SCurveEditorView& InView, const FCurveEditor& InCurveEditor);` (scope `UE::CurveEditorTools`) — Obtains the transform required to transform evaluated key positions to that space used by ICurveEditorToolExtension::OnPaint. The widget hierarchy is SCurveEditorViewContainer -> SCurveEditorView. - SCurveEditorView is used to evaluate key positions. - ICurveEditorToolExtension::OnPaint receives the FGeometry of SCurveEditorView
- L54 _prototype_ `FLatticeBounds ComputeBounds(const FCurveEditor& InCurveEditor);` (scope `UE::CurveEditorTools`) — Computes the min and max slate and value points in the user's selection.
- L56 _prototype_ `FLatticeBounds ComputeCurveBounds(const FCurveEditor& InCurveEditor, const FCurveModelID& InCurveId, TConstArrayView<FKeyHandle> InKeys);` (scope `UE::CurveEditorTools`) — Computes the bounds just for the given curve.
- L67 _prototype_ `bool TransformViewToViewContainer( const FCurveEditor& InCurveEditor, TConstArrayView<FVector2D> InControlPoints, TArrayView<FVector2D> OutTransformedToViewContainer );` (scope `UE::CurveEditorTools`) — Transforms the values of the control points to where they should be drawn in InLatticeGeometry. @param InCurveEditor Needed to get interactive view for transforming values. @param InBounds The bounds as computed by ComputeBounds @param InLatticeGeometry The result of MakeLatticeGeometry @param InControlPoints The points to transform @param OutTransformedToViewContainer Will contain the transformed points; must be equal length to InControlPoints. @return Whether OutTransformed was written to.
- L82 _prototype_ `FLatticeHoverState ComputeLatticeHoverState( const FGeometry& InViewContainerGeometry, const FVector2D& InMouseScreenPosition, TConstArrayView<FVector2D> InControlPoints, TConstArrayView<FLatticeControlEdge> InControlEdges, int32 InNumPointsInX, int32 InNumCells );` (scope `UE::CurveEditorTools`) — Computes which elements should be hovered. @param InViewContainerGeometry The result of MakeLatticeGeometry @param InMouseScreenPosition The screen space position of the mouse @param InControlPoints The control points of the lattice deformer, already transformed using TransformControlPointsToSlate. @param InControlEdges The edges of the lattice deformer. @param InNumPointsInX The number of points InControlPoints has in x direction @param InNumCells Total number of cells in the deformer
- L98 _prototype_ `void DrawLatticeControls( const FLatticeControlsDrawData& InDrawData, const FGeometry& InViewContainerGeometry, FSlateWindowElementList& OutDrawElements, int32 InPaintOnLayerId );` (scope `UE::CurveEditorTools`) — Draws the lattice controls. @param InDrawData @param InViewContainerGeometry The result of MakeLatticeGeometry @param OutDrawElements @param InPaintOnLayerId

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Misc/LatticeUtils.h` (Private)


#### struct `UE::CurveEditorTools::FMatrixIndices`  
`struct FMatrixIndices`  
_L22-26_
- L24 _public member_ `int32 Column;` — X
- L25 _public member_ `int32 Row;` — Y

#### struct `UE::CurveEditorTools::FCellCornerIndices`  
`struct FCellCornerIndices`  
_L30-36_
- L32 _public member_ `int32 TopLeft;`
- L33 _public member_ `int32 TopRight;`
- L34 _public member_ `int32 BottomRight;`
- L35 _public member_ `int32 BottomLeft;`

#### struct `UE::CurveEditorTools::FEdgeVertexIndices`  
`struct FEdgeVertexIndices`  
_L40-44_
- L42 _public member_ `int32 Start = INDEX_NONE;`
- L43 _public member_ `int32 End = INDEX_NONE;`

#### struct `UE::CurveEditorTools::FCellVertexIndices`  
`struct FCellVertexIndices`  
_L53-65_
- L55 _public member_ `int32 TopLeft = INDEX_NONE;`
- L56 _public member_ `int32 TopRight = INDEX_NONE;`
- L57 _public member_ `int32 BottomRight = INDEX_NONE;`
- L58 _public member_ `int32 BottomLeft = INDEX_NONE;`
- L60 _public function_ `bool IsValid() const`

#### enum `UE::CurveEditorTools::ELatticeEdgeType`  
`enum class ELatticeEdgeType : uint8`  
_L73-79_
- L75 _public enumerator_ `Top`
- L76 _public enumerator_ `Bottom`
- L77 _public enumerator_ `Left`
- L78 _public enumerator_ `Right`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L20 _prototype_ `int32 MatrixIndicesToFlatIndex(int32 InColumn, int32 InRow, int32 InNumColumns);` (scope `UE::CurveEditorTools`) — @return Index you can use in a TArray representing a 2D matrix.
- L28 _prototype_ `FMatrixIndices FlatIndexToMatrixIndices(int32 InFlatIndex, int32 InNumColumns);` (scope `UE::CurveEditorTools`) — @return Matrix Column and Row that InFlatIndex maps to if matrix is InNumColumns wide. Does not check bounds.
- L38 _prototype_ `FCellCornerIndices GetMatrixCellSlotsWithCorner(int32 InCornerIndex, int32 InNumLatticePointColumns, int32 InNumLatticePointRows);` (scope `UE::CurveEditorTools`) — Suppose you have nxm matrix of lattice points that forms a (n-1)x(m-1) matrix of cells, returns the flat indices of the cells that share InCornerIndex.
- L51 _prototype_ `FEdgeVertexIndices GetEdgeIndices(int32 InEdgeIndex, int32 InNumPointsInWidth, int32 InNumPointsInHeight);` (scope `UE::CurveEditorTools`) — @param InEdgeIndex Index of the edge according to how it is described in FLatticeDeformer2D. @param InNumPointsInWidth The number of points in the x direction (num cells in x-direction + 1) @param InNumPointsInHeight The number of points in the z direction (num cells in z-direction + 1) @return The corner indices of the cell.
- L71 _prototype_ `FCellVertexIndices GetCellIndices(int32 InCellIndex, int32 InNumPointsInWidth);` (scope `UE::CurveEditorTools`) — @param InCellIndex Index of the cell according to how it is described in FLatticeDeformer2D. @param InNumPointsInWidth The number of points in the x direction (num cells in x-direction + 1) @return The corner indices of the cell.
- L81 _prototype_ `constexpr int32 GetEdgeIndexInSingleCellGrid(ELatticeEdgeType Type);` (scope `UE::CurveEditorTools`) — @return Assuming the lattice grid consists of a single cell, gets the specified edge.
- L83 _prototype_ `constexpr ELatticeEdgeType GetEdgeTypeFromIndexInSingleCellGrid(int32 InEdgeIndex);` (scope `UE::CurveEditorTools`) — @return Assuming the lattice grid consists of a single cell, gets type of edge based off of its index.
- L86 _prototype_ `constexpr ELatticeEdgeType GetOppositeEdge(ELatticeEdgeType Type);` (scope `UE::CurveEditorTools`) — @return The opposite edge of the passed in edge
- L89 _prototype_ `bool IsLatticeTooSmall(const FVector2D& InMin, const FVector2D& InMax);` (scope `UE::CurveEditorTools`) — @return Whether a lattice can be formed by these points.
- L92 _prototype_ `TArray<FVector2D> GenerateControlPoints(int32 InNumCellsInX, int32 InNumCellsInY, const FVector2D& InBottomLeft, const FVector2D& InTopRight);` (scope `UE::CurveEditorTools`) — @return The lattice control points given the construction arguments. Use GetCellIndices to access cell control points.
- L95 _prototype_ `TArray<FVector2D> TransformPoints(const FTransform2d& InTransform, TConstArrayView<FVector2D> InControlPoints);` (scope `UE::CurveEditorTools`) — @return InControlPoints transformed by InTransform.
- L98 _namespace_ `namespace UE`
- L98 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L100 _function_ `constexpr int32 GetEdgeIndexInSingleCellGrid(ELatticeEdgeType Type)` (scope `UE::CurveEditorTools`)
- L106 _function_ `constexpr ELatticeEdgeType GetEdgeTypeFromIndexInSingleCellGrid(int32 InEdgeIndex)` (scope `UE::CurveEditorTools`)
- L112 _function_ `constexpr ELatticeEdgeType GetOppositeEdge(ELatticeEdgeType Type)` (scope `UE::CurveEditorTools`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/PerCurveLatticeData.h` (Private)


#### struct `UE::CurveEditorTools::FPerCurveLatticeData`  
`struct FPerCurveLatticeData`  
_L20-49_
- desc: Data stored per curve in FCurveEditorLatticeTool.
- L26 _public member_ `FPerCurveDeformer2D CurveDeformer;` — Deformers for each curve; the control points are global deformer's control points transformed by the per-curve transform. The per-curve deformers' control points are always in absolute key space (i.e. exactly the values for FKeyPosition::InputValue and OutputValue).
- L48 _public member_ `FTransform2d GlobalDeformerToCurveDeformer;` — Transform from the global deformer's control points to per-curve lattice control points. The transform depends on the view: - In Absolute view, this is effectively an identity matrix. - For Normalized view, let's use an example: - Suppose the following curves: Curve A: global min and max absolute values are y=0 and y=100, respectively. Curve B: global min and max absolute values are y=50 and y=150, respectively. - Suppose the user selects keys such that Deformer is placed with bottom & top edge at y=0.6 & y=0.8 respectively. - Deformer's bottom & top edge's absolute values would be y=60 and y=130 (--> the min & max absolute values across all selected curves). - The per-curve lattices would be placed as follows Curve A: lattice bottom & top edge at y=60 and y=80, respectively. Curve B: lattice bottom & top edge at y=110 and y=130, respectively. - The per-curve transforms are computed such that the Deformer's lattice with bottom & top edge at y=60 and y=130 and transformed to the local lattices of Curve A (y=60 and y=80) and Curve B(y=110 and y=130), respectively. The computation of the per-curve transform uses the per-curve transform of SCurveEditorView::GetViewToCurveTransform, which implements Absolute, Normalized, etc. views.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L52 _prototype_ `TMap<FCurveModelID, FPerCurveLatticeData> BuildPerLatticeData(const FLatticeBounds& Lattice, const FCurveEditor& InCurveEditor);` (scope `UE::CurveEditorTools`) — Builds the per curve data for lattice.

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Undo/LatticeSnapshot.h` (Private)


#### struct `UE::CurveEditorTools::FPerCurveSnapshot`  
`struct FPerCurveSnapshot`  
_L16-24_
- L18 _public member_ `FTransform2d GlobalToLocalTransform;`
- L19 _public member_ `TArray<FLatticeKeyCoords> KeyCoords;`
- L21 _public member_ `TArray<FLatticePointMetaData> MetaData;` — The metadata for each point in the cell.

#### struct `UE::CurveEditorTools::FLatticeSnapshot`  
`struct FLatticeSnapshot`  
_L26-44_
- L29 _public member_ `TOptional<ECurveEditorViewID> ViewMode;` — The view mode the editor was in when during this snapshot. The snapshot can only be applied if the editor is currently in the same view mode.
- L31 _public member_ `uint32 SelectionSerialNumber;` — The selection serial number the editor had when this snapshot was taken. The snapshot can only be applied the selection states are the same.
- L34 _public member_ `FTransform2d ControlPointToCurveSpace;` — Corresponds to FLatticeDeformerState::ControlPointToCurveSpace.
- L36 _public member_ `TArray<FVector2D> GlobalControlPoints;` — The controls points the global lattice had. Corresponds to FLatticeDeformerState::GlobalDeformer.
- L38 _public member_ `TMap<FCurveModelID, FPerCurveSnapshot> PerCurveData;` — Corresponds to FLatticeDeformerState::PerCurveData.
- L41 _public prototype_ `bool CanApplySnapshot(const FCurveEditor& InCurveEditor) const;` — @return Whether the saved data is compatible with the currentl state of InCurveEditor.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L50 _prototype_ `bool ApplySnapshot( const FLatticeSnapshot& InSnapshot, const FCurveEditor& InCurveEditor, FTransform2d& OutControlPointToCurveSpace, FGlobalLatticeDeformer2D& OutGlobalDeformer, TMap<FCurveModelID, FPerCurveLatticeData>& OutPerCurveData );` (scope `UE::CurveEditorTools`) — Tries to apply the snapshot if possible. @return Whether the data was applied.
- L57 _prototype_ `FLatticeSnapshot TakeSnapshot( const FCurveEditor& InCurveEditor, const FTransform2d& InControlPointToCurveSpace, const FGlobalLatticeDeformer2D& InGlobalDeformer, const TMap<FCurveModelID, FPerCurveLatticeData>& InPerCurveData );` (scope `UE::CurveEditorTools`) — Takes a snapshot of the lattice tool and the curve editor's data required in the future to validate that the data can be applied.

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Lattice/Undo/LatticeUndoObject.h` (Private)


#### class `UCurveEditorTools_LatticeUndoObject`  
`class UCurveEditorTools_LatticeUndoObject : public UObject`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Stores data for the purposes of undo / redo in the lattice tool.
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPostEditUndo);`
- L19 _public member_ `FOnPostEditUndo OnPostEditUndo;` — Invoked when the user has performed an undo / redo operation. You should call RestoreState.
- L22 _public member_ `UE::CurveEditorTools::FLatticeSnapshot Snapshot;` — Data that is undone / redone by the transaction sytem.
- L25 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L26 _public prototype_ `virtual void PostEditUndo() override;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPostEditUndo);`

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Retime/CurveEditorRetimeTool.h` (Private)


#### class `UCurveEditorRetimeToolData`  
`class UCurveEditorRetimeToolData : public UObject`  
_L19-28_
- reflection: `UCLASS()`
- inherits: `UObject`
- L27 _public member_ `TArray<FCurveEditorRetimeAnchor> RetimingAnchors;` — `UPROPERTY()`

#### class `UE::CurveEditorTools::FCurveEditorRetimeTool`  
`class FCurveEditorRetimeTool : public ICurveEditorToolExtension`  
_L32-110_
- inherits: `ICurveEditorToolExtension`
- L35 _public prototype_ `FCurveEditorRetimeTool(TWeakPtr<FCurveEditor> InCurveEditor);`
- L36 _public prototype_ `~FCurveEditorRetimeTool();`
- L39 _public prototype_ `virtual void OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — ICurveEditorToolExtension
- L40 _public prototype_ `virtual FReply OnKeyDown(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L41 _public prototype_ `virtual FReply OnKeyUp(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L42 _public prototype_ `virtual FReply OnMouseButtonDown(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(TSharedRef<SWidget> OwningWidget, const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L44 _public prototype_ `virtual FReply OnMouseButtonUp(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L45 _public prototype_ `virtual FReply OnMouseMove(TSharedRef<SWidget> OwningWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L47 _public prototype_ `virtual void OnToolActivated() override;`
- L48 _public prototype_ `virtual void OnToolDeactivated() override;`
- L49 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> CommandBindings) override;`
- L50 _public prototype_ `virtual FText GetLabel() const override;`
- L51 _public prototype_ `virtual FText GetDescription() const override;`
- L52 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L56 _private prototype_ `virtual void DrawAnchor(const FCurveEditorRetimeAnchor& InAnchor, const FCurveEditorRetimeAnchor* OptionalNextAnchor, const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 PaintOnLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L57 _private prototype_ `virtual void OnDragStart();`
- L59 _private prototype_ `virtual void OnDrag(const FVector2D& InStartPosition, const FVector2D& InMousePosition);` — Execute retiming or anchor movement depending on which part of the anchor the user clicked.
- L60 _private prototype_ `virtual void OnDragEnd();`
- L62 _private prototype_ `void StopDragIfPossible();`
- L65 _private prototype_ `void OnDrag_RetimeKeysAndAnchors(const double DragDeltaFromStartPx);` — Adjust the positions of keys by moving anchors.
- L67 _private prototype_ `void OnDrag_MoveAnchors(const double DragDeltaFromStartPx);` — Adjust the position of anchors without adjusting the timing of the keys.
- L69 _private prototype_ `void SortAnchorsByTime();` — Sort all anchors by input time to ensure they're always sorted from least to greatest as drawing and between segments counts on this behaviour.
- L71 _private prototype_ `void RecomputeLastDraggedFrameNumbersFromDrag(const FCurveEditor& CurveEditor, const int32 ChannelIndex, const double DragDeltaFromStartPx);` — Calculate positions of keys on the curve after retiming and save them to ChannelData.LastDraggedFrameNumbers for setting the key positions in OnDrag_RetimeKeysAndAnchors.
- L74 _private prototype_ `bool IsScrubTimeKeyEvent(const FKeyEvent& InKeyEvent) const;` — Returns true if the key event is a scrub time key event
- L78 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;` — Weak pointer back to the owning curve editor.
- L81 _private member_ `UCurveEditorRetimeToolData* RetimeData;` — The retiming data for this tool. This is a UObject for Undo/Redo purposes. Created and added to the root set on construction of the tool.
- L100 _private member_ `TOptional<FTransaction> ActiveTransaction;` — The currently open transaction (if any)
- L103 _private member_ `TOptional<Retime::FMouseDownData> MouseDownOp;` — Set when attempting to move a drag handle.
- L106 _private member_ `TMap<FCurveModelID, FKeyHandleSet> CachedSelectionSet;` — Cached user selection for keys. We clear this when the tool is opened and restore it when they leave
- L109 _private member_ `bool bScrubbing = false;` — True while scrubbing

#### struct `UE::CurveEditorTools::FCurveEditorRetimeTool::FTransaction`  
`struct FTransaction`  
_L83-98_
- L85 _public member_ `FScopedTransaction Transaction;`
- L86 _public member_ `CurveEditor::FScopedCurveChange KeyChange;`
- L88 _public function_ `explicit FTransaction(TWeakPtr<FCurveEditor> InCurveEditor, const FText& Description) : Transaction(Description) , KeyChange([InCurveEditor] { using namespace UE::CurveEditor; return FCurvesSnapshotBuilder( InCurveEditor, ECurveChangeFlags::KeyAttributes | ECurveChangeFlags::MoveKeysAndRemoveStackedKeys ).TrackAllCurves(); }())`
- L91 _public function_ ``

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace CurveEditorTools` (scope `UE`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Retime/RetimeAnchor.h` (Private)


#### struct `FCurveEditorRetimeAnchor`  
`struct FCurveEditorRetimeAnchor`  
_L9-47_
- reflection: `USTRUCT()`
- L13 _public function_ `FCurveEditorRetimeAnchor() : ValueInSeconds(0.0) , bIsSelected(false) , bIsHighlighted(false) , bIsCloseBtnHighlighted(false)`
- L21 _public function_ `FCurveEditorRetimeAnchor(double InSeconds) : ValueInSeconds(InSeconds) , bIsSelected(false) , bIsHighlighted(false) , bIsCloseBtnHighlighted(false)`
- L31 _public member_ `double ValueInSeconds;` — `UPROPERTY()` — The time on the Timeline that this anchor is anchored at.
- L35 _public member_ `bool bIsSelected;` — `UPROPERTY()` — Is this anchor currently selected?
- L38 _public member_ `bool bIsHighlighted;` — Is this anchor currently highlighted? An anchor can be both selected and highlighted.
- L41 _public member_ `bool bIsCloseBtnHighlighted;` — Is the close button highlighted?
- L44 _public prototype_ `void GetPaintGeometry(const FGeometry& InWidgetGeometry, const FCurveEditor& InCurveEditor, FGeometry& OutMoveOnlyBarGeometry, FGeometry& OutRetimeBarGeometry, FGeometry& OutCloseButtonGeometry) const;` — Calculate the paint geometry for this anchor.
- L46 _public prototype_ `void GetHitGeometry(const FGeometry& InWidgetGeometry, const FCurveEditor& InCurveEditor, FGeometry& OutMoveOnlyBarGeometry, FGeometry& OutRetimeBarGeometry, FGeometry& OutCloseButtonGeometry) const;` — Calculate the wider hitbox geometry for this anchor.

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L51 _variable_ `constexpr double AnchorMoveOnlyBarWidth = 3.0;` (scope `UE::CurveEditorTools`)
- L52 _variable_ `constexpr double AnchorRetimeBarWidth = 5.0;` (scope `UE::CurveEditorTools`)
- L53 _variable_ `constexpr double CloseButtonWidth = 18.0;` (scope `UE::CurveEditorTools`)
- L54 _variable_ `constexpr double CloseButtonPadding = 2.0;` (scope `UE::CurveEditorTools`)
- L55 _variable_ `constexpr double HighlightOpacity = 0.75;` (scope `UE::CurveEditorTools`)
- L56 _variable_ `const double ExtraPadding = 8.0;` (scope `UE::CurveEditorTools`)

### `Plugins/Editor/CurveEditorTools/Source/CurveEditorTools/Private/Tools/Retime/RetimeDragData.h` (Private)


#### struct `UE::CurveEditorTools::Retime::FPreDragChannelData`  
`struct FPreDragChannelData`  
_L10-22_
- L12 _public function_ `explicit FPreDragChannelData(FCurveModelID InCurveModel) : CurveID(InCurveModel)`
- L15 _public member_ `TArray<FKeyHandle> Handles;` — Array of all the handles in the section at the start of the drag
- L17 _public member_ `TArray<FKeyPosition> FrameNumbers;` — Array of all the above handle's times, one per index of Handles
- L19 _public member_ `TArray<FKeyPosition> LastDraggedFrameNumbers;` — Array of all the above handle's last dragged times, one per index of Handles
- L21 _public member_ `FCurveModelID CurveID;` — The ID of the curve the data corresponds to.

#### struct `UE::CurveEditorTools::Retime::FPreDragCurveData`  
`struct FPreDragCurveData`  
_L24-30_
- L27 _public member_ `TArray<FPreDragChannelData> CurveChannels;` — Array of all the channels in the section before it was resized
- L29 _public member_ `TArray<double> RetimeAnchorStartTimes;` — The times on the Timeline that anchors are anchored at.

#### enum `UE::CurveEditorTools::Retime::EDragMode`  
`enum class EDragMode : uint8`  
_L33-39_
- desc: Type of operation to execute, determined by which part of the anchor the user clicked at the start of the drag.
- L36 _public enumerator_ `RetimeMode` — Moving anchors will retime key positions accordingly.
- L38 _public enumerator_ `MoveAnchorMode` — MoveAnchorMode: Anchors can be moved without affecting key positions.

#### struct `UE::CurveEditorTools::Retime::FMouseDownData`  
`struct FMouseDownData`  
_L41-53_
- L44 _public member_ `TOptional<FPreDragCurveData> PreDragCurveData;` — Set if CurrentDragMode == RetimeMode and once DelayedDrag has been detected.
- L47 _public member_ `FDelayedDrag DelayedDrag;` — Started on mouse down if any part of an anchor was clicked.
- L50 _public member_ `EDragMode CurrentDragMode;` — Active drag behavior (retime keys or move anchors).
- L52 _public function_ `FMouseDownData(const FDelayedDrag& InDrag, const EDragMode InMode) : DelayedDrag(InDrag), CurrentDragMode(InMode)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditorTools` (scope `UE`)
- L8 _namespace_ `namespace Retime` (scope `UE::CurveEditorTools`)
