# Editor / SequencerWidgets

- module root: `Source/Editor/SequencerWidgets`
- headers: 11; symbols: 228
- symbol kinds: class=7, delegate=8, enum=4, enumerator=18, function=24, macro=1, member=77, namespace=1, prototype=80, struct=6, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: MovieScene
- PublicIncludePathModuleNames: SequencerCore

### `Source/Editor/SequencerWidgets/Private/SSequencerTimeSlider.h` (Private)


#### class `SSequencerTimeSlider`  
`class SSequencerTimeSlider : public ITimeSlider`  
_L20-57_
- inherits: `ITimeSlider`
- L24 _public function_ `SLATE_BEGIN_ARGS(SSequencerTimeSlider) : _MirrorLabels( false )`
- L28 _public prototype_ `SLATE_ARGUMENT( bool, MirrorLabels ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef<ITimeSliderController> InTimeSliderController );` — If we should mirror the labels on the timeline
- L41 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L42 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L43 _protected prototype_ `virtual void OnMouseEnter( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L44 _protected prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L45 _protected prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L46 _protected prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L47 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L48 _protected prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L49 _protected prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L50 _protected prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L51 _protected prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L55 _private member_ `TSharedPtr<ITimeSliderController> TimeSliderController;`
- L56 _private member_ `bool bMirrorLabels;`

### `Source/Editor/SequencerWidgets/Private/STimeRange.h` (Private)


#### class `STimeRange`  
`class STimeRange : public ITimeSlider`  
_L13-93_
- inherits: `ITimeSlider`
- L16 _public function_ `SLATE_BEGIN_ARGS(STimeRange) : _ShowWorkingRange(true) , _ShowViewRange(false) , _ShowPlaybackRange(true) , _PlaybackRangeStartColor(FLinearColor::Red) , _PlaybackRangeEndColor(FLinearColor::Green)`
- L24 _public prototype_ `SLATE_ATTRIBUTE( TSharedPtr<INumericTypeInterface<double>>, NumericTypeInterface ) SLATE_ARGUMENT( bool, ShowWorkingRange ) SLATE_ARGUMENT( bool, ShowViewRange ) SLATE_ARGUMENT( bool, ShowPlaybackRange ) SLATE_ARGUMENT( bool, EnableWorkingRange ) SLATE_ARGUMENT( bool, EnableViewRange ) SLATE_ARGUMENT( bool, EnablePlaybackRange ) SLATE_ARGUMENT( FLinearColor, PlaybackRangeStartColor ) SLATE_ARGUMENT( FLinearColor, PlaybackRangeEndColor ) SLATE_DEFAULT_SLOT( FArguments, CenterContent ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef<ITimeSliderController> InTimeSliderController);` — Whether to show the working range
- L53 _protected prototype_ `double GetSpinboxDelta() const;`
- L57 _protected prototype_ `double PlayStartTime() const;`
- L58 _protected prototype_ `double PlayEndTime() const;`
- L60 _protected prototype_ `void OnPlayStartTimeCommitted(double NewValue, ETextCommit::Type InTextCommit);`
- L61 _protected prototype_ `void OnPlayEndTimeCommitted(double NewValue, ETextCommit::Type InTextCommit);`
- L63 _protected prototype_ `void OnPlayStartTimeChanged(double NewValue);`
- L64 _protected prototype_ `void OnPlayEndTimeChanged(double NewValue);`
- L68 _protected prototype_ `double ViewStartTime() const;`
- L69 _protected prototype_ `double ViewEndTime() const;`
- L71 _protected prototype_ `void OnViewStartTimeCommitted(double NewValue, ETextCommit::Type InTextCommit);`
- L72 _protected prototype_ `void OnViewEndTimeCommitted(double NewValue, ETextCommit::Type InTextCommit);`
- L74 _protected prototype_ `void OnViewStartTimeChanged(double NewValue);`
- L75 _protected prototype_ `void OnViewEndTimeChanged(double NewValue);`
- L79 _protected prototype_ `double WorkingStartTime() const;`
- L80 _protected prototype_ `double WorkingEndTime() const;`
- L82 _protected prototype_ `void OnWorkingStartTimeCommitted(double NewValue, ETextCommit::Type InTextCommit);`
- L83 _protected prototype_ `void OnWorkingEndTimeCommitted(double NewValue, ETextCommit::Type InTextCommit);`
- L85 _protected prototype_ `void OnWorkingStartTimeChanged(double NewValue);`
- L86 _protected prototype_ `void OnWorkingEndTimeChanged(double NewValue);`
- L89 _private member_ `TSharedPtr<ITimeSliderController> TimeSliderController;`
- L91 _private member_ `FLinearColor PlaybackRangeStartColor;`
- L92 _private member_ `FLinearColor PlaybackRangeEndColor;`

### `Source/Editor/SequencerWidgets/Private/STimeRangeSlider.h` (Private)


#### class `STimeRangeSlider`  
`class STimeRangeSlider : public SCompoundWidget`  
_L22-71_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(STimeRangeSlider)`
- L26 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef<ITimeSliderController> InTimeSliderController );`
- L32 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L33 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L34 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L35 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L36 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L37 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L38 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L41 _protected prototype_ `void ResetState();`
- L42 _protected prototype_ `void ResetHoveredState();`
- L43 _protected prototype_ `double ComputeDragDelta(const FPointerEvent& MouseEvent, double GeometryWidth) const;`
- L44 _protected prototype_ `void ComputeHandleOffsets(double& LeftHandleOffset, double& RightHandleOffset, double&HandleOffset, double GeometryWidth) const;`
- L48 _private member_ `bool bLeftHandleDragged;` — The left handle is being dragged
- L50 _private member_ `bool bRightHandleDragged;` — The right handle is being dragged
- L52 _private member_ `bool bHandleDragged;` — The handle is being dragged
- L55 _private member_ `bool bLeftHandleHovered;` — The left handle is hovered
- L57 _private member_ `bool bRightHandleHovered;` — The right handle is hovered
- L59 _private member_ `bool bHandleHovered;` — The handle is hovered
- L62 _private member_ `FVector2D MouseDownPosition;` — The position of the mouse on mouse down
- L65 _private member_ `TRange<double> MouseDownViewRange;` — The in/out view range on mouse down
- L68 _private member_ `TRange<double> LastViewRange;` — The in/out view range viewed before expansion
- L70 _private member_ `TSharedPtr<ITimeSliderController> TimeSliderController;`

### `Source/Editor/SequencerWidgets/Public/AnimatedRange.h` (Public)


#### struct `FAnimatedRange`  
`struct FAnimatedRange : public TRange<double>`  
_L10-41_
- inherits: `TRange<double>`
- desc: Structure used to wrap up a range, and an optional animation target
- L13 _public function_ `FAnimatedRange() : TRange()` — Default Construction
- L15 _public function_ `FAnimatedRange(double LowerBound, double UpperBound) : TRange(LowerBound, UpperBound)` — Construction from a lower and upper bound
- L17 _public function_ `FAnimatedRange(const TRange<double>& InRange) : TRange(InRange)` — Copy-construction from simple range
- L20 _public function_ `static TAttribute<TRange<double>> WrapAttribute(const TAttribute<FAnimatedRange>& InAttribute)` — Helper function to wrap an attribute to an animated range with a non-animated one
- L27 _public function_ `static TAttribute<FAnimatedRange> WrapAttribute(const TAttribute<TRange<double>>& InAttribute)` — Helper function to wrap an attribute to a non-animated range with an animated one
- L34 _public function_ `const TRange<double>& GetAnimationTarget() const` — Get the current animation target, or the whole view range when not animating
- L40 _public member_ `TOptional<TRange<double>> AnimationTarget;` — The animation target, if animating

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef TAttribute<TRange<double>> Attr;` (scope `FAnimatedRange::WrapAttribute`)
- L23 _function_ `return Attr::Create(Attr::FGetter::CreateLambda([=]() { return InAttribute.Get(); }));` (scope `FAnimatedRange::WrapAttribute`)
- L29 _typedef_ `typedef TAttribute<FAnimatedRange> Attr;` (scope `FAnimatedRange::WrapAttribute`)

### `Source/Editor/SequencerWidgets/Public/ISequencerWidgetsModule.h` (Public)


#### enum `EShowRange`  
`enum class EShowRange`  
_L16-22_
- desc: Enum denoting which time ranges to display on a time range
- L18 _public enumerator_ `None = 0`
- L19 _public enumerator_ `WorkingRange = 1 << 0`
- L20 _public enumerator_ `ViewRange = 1 << 1`
- L21 _public enumerator_ `PlaybackRange = 1 << 2`

#### struct `FTimeRangeArgs`  
`struct FTimeRangeArgs`  
_L26-79_
- desc: Time range construction arguments
- L28 _public function_ `FTimeRangeArgs( EShowRange InShowRanges, TSharedRef<ITimeSliderController> InController, TAttribute<EVisibility> InVisibilityDelegate, TAttribute<TSharedPtr<INumericTypeInterface<double>>> InNumericTypeInterface, FLinearColor InPlaybackRangeStartColor = FLinearColor::Green, FLinearColor InPlaybackRangeEndColor = FLinearColor::Red ) : ShowRanges(InShowRanges) , EnableRanges(InShowRanges) , Controller(InController) , VisibilityDelegate(InVisibilityDelegate) , NumericTypeInterface(InNumericTypeInterface) , PlaybackRangeStartColor(InPlaybackRangeStartColor) , PlaybackRangeEndColor(InPlaybackRangeEndColor)`
- L46 _public function_ `FTimeRangeArgs( EShowRange InShowRanges, EShowRange InEnableRanges, TSharedRef<ITimeSliderController> InController, TAttribute<EVisibility> InVisibilityDelegate, TAttribute<TSharedPtr<INumericTypeInterface<double>>> InNumericTypeInterface, FLinearColor InPlaybackRangeStartColor = FLinearColor::Green, FLinearColor InPlaybackRangeEndColor = FLinearColor::Red ) : ShowRanges(InShowRanges) , EnableRanges(InEnableRanges) , Controller(InController) , VisibilityDelegate(InVisibilityDelegate) , NumericTypeInterface(InNumericTypeInterface) , PlaybackRangeStartColor(InPlaybackRangeStartColor) , PlaybackRangeEndColor(InPlaybackRangeEndColor)`
- L66 _public member_ `EShowRange ShowRanges;` — Which ranges to show
- L68 _public member_ `EShowRange EnableRanges;` — Which ranges to enable editing on
- L70 _public member_ `TSharedRef<ITimeSliderController> Controller;` — A time slider controller
- L72 _public member_ `TAttribute<EVisibility> VisibilityDelegate;` — Visibility delegate
- L74 _public member_ `TAttribute<TSharedPtr<INumericTypeInterface<double>>> NumericTypeInterface;` — Numeric type interface to use for frame<->time conversion
- L76 _public member_ `FLinearColor PlaybackRangeStartColor = FLinearColor::Green;` — Playback range start color
- L78 _public member_ `FLinearColor PlaybackRangeEndColor = FLinearColor::Red;` — Playback range end color

#### class `ISequencerWidgetsModule`  
`class ISequencerWidgetsModule : public IModuleInterface`  
_L84-93_
- inherits: `IModuleInterface`
- desc: The public interface of SequencerModule
- L89 _public prototype_ `virtual TSharedRef<ITimeSlider> CreateTimeSlider( const TSharedRef<ITimeSliderController>& InController, bool bMirrorLabels ) = 0;`
- L90 _public prototype_ `virtual TSharedRef<ITimeSlider> CreateTimeSlider( const TSharedRef<ITimeSliderController>& InController, const TAttribute<EVisibility>& VisibilityDelegate, bool bMirrorLabels ) = 0;`
- L91 _public prototype_ `virtual TSharedRef<SWidget> CreateTimeRangeSlider( const TSharedRef<class ITimeSliderController>& InController ) = 0;`
- L92 _public prototype_ `virtual TSharedRef<ITimeSlider> CreateTimeRange( const FTimeRangeArgs& InArgs, const TSharedRef<SWidget>& Content ) = 0;`

#### Free symbols / members of external scopes

- L23 _prototype_ `ENUM_CLASS_FLAGS(EShowRange);`

### `Source/Editor/SequencerWidgets/Public/ITimeSlider.h` (Public)


#### struct `FPaintPlaybackRangeArgs`  
`struct FPaintPlaybackRangeArgs`  
_L19-36_
- L21 _public function_ `FPaintPlaybackRangeArgs() : StartBrush(nullptr), EndBrush(nullptr), BrushWidth(0.f), SolidFillOpacity(0.f)`
- L25 _public function_ `FPaintPlaybackRangeArgs(const FSlateBrush* InStartBrush, const FSlateBrush* InEndBrush, float InBrushWidth) : StartBrush(InStartBrush), EndBrush(InEndBrush), BrushWidth(InBrushWidth)`
- L29 _public member_ `const FSlateBrush* StartBrush;` — Brush to use for the start bound
- L31 _public member_ `const FSlateBrush* EndBrush;` — Brush to use for the end bound
- L33 _public member_ `float BrushWidth;` — The width of the above brushes, in slate units
- L35 _public member_ `float SolidFillOpacity;` — level of opacity for the fill color between the range markers

#### struct `FPaintViewAreaArgs`  
`struct FPaintViewAreaArgs`  
_L38-52_
- L40 _public function_ `FPaintViewAreaArgs() : bDisplayTickLines(false), bDisplayScrubPosition(false), bDisplayMarkedFrames(false)`
- L45 _public member_ `bool bDisplayTickLines;` — Whether to display tick lines
- L47 _public member_ `bool bDisplayScrubPosition;` — Whether to display the scrub position
- L49 _public member_ `bool bDisplayMarkedFrames;` — Whether to display the marked frames
- L51 _public member_ `TOptional<FPaintPlaybackRangeArgs> PlaybackRangeArgs;` — Optional Paint args for the playback range

#### enum `ETimeSliderPlaybackStatus`  
`enum ETimeSliderPlaybackStatus`  
_L54-63_
- L56 _public enumerator_ `Stopped`
- L57 _public enumerator_ `Playing`
- L58 _public enumerator_ `Scrubbing`
- L59 _public enumerator_ `Jumping`
- L60 _public enumerator_ `Stepping`
- L61 _public enumerator_ `Paused`
- L62 _public enumerator_ `MAX`

#### class `ITimeSliderController`  
`class ITimeSliderController : public ISequencerInputHandler`  
_L65-164_
- inherits: `ISequencerInputHandler`
- L68 _public prototype_ `virtual ~ITimeSliderController() override = default;`
- L70 _public prototype_ `virtual int32 OnPaintTimeSlider( bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const = 0;`
- L72 _public prototype_ `virtual int32 OnPaintViewArea( const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, const FPaintViewAreaArgs& Args ) const = 0;`
- L74 _public function_ `virtual FReply OnTimeSliderMouseButtonDown(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L79 _public function_ `virtual FReply OnTimeSliderMouseButtonUp(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L84 _public function_ `virtual FReply OnTimeSliderMouseMove(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L89 _public function_ `virtual FReply OnTimeSliderMouseWheel(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L94 _public function_ `virtual double ComputeHeight() const`
- L97 _public prototype_ `virtual FFrameRate GetDisplayRate() const = 0;` — Get the current play rate for this controller
- L100 _public prototype_ `virtual FFrameRate GetTickResolution() const = 0;` — Get the current tick resolution for this controller
- L103 _public prototype_ `virtual FAnimatedRange GetViewRange() const;` — Get the current view range for this controller
- L106 _public prototype_ `virtual FAnimatedRange GetClampRange() const;` — Get the current clamp range for this controller
- L109 _public prototype_ `virtual TRange<FFrameNumber> GetPlayRange() const;` — Get the current play range for this controller
- L112 _public prototype_ `virtual TRange<FFrameNumber> GetTimeBounds() const;` — Get the current time bounds for this controller. The time bounds should be a subset of the playback range.
- L115 _public prototype_ `virtual TRange<FFrameNumber> GetSelectionRange() const;` — Get the current selection range for this controller
- L118 _public prototype_ `virtual FFrameTime GetScrubPosition() const;` — Get the current time for the Scrub handle which indicates what range is being evaluated.
- L121 _public prototype_ `virtual void SetScrubPosition(FFrameTime InTime, bool bEvaluate);` — Set the current time for the Scrub handle which indicates what range is being evaluated.
- L124 _public prototype_ `virtual void SetStoppedPosition(FFrameTime InTime);` — Set the current time for the handle when playback is stopped
- L127 _public prototype_ `virtual void SetPlaybackStatus(ETimeSliderPlaybackStatus InStatus);` — Set the playback status for the controller
- L130 _public prototype_ `virtual ETimeSliderPlaybackStatus GetPlaybackStatus() const;` — Get the playback status for the controller, by default it is ETimeSliderPlaybackStatus::Stopped
- L140 _public prototype_ `virtual void SetViewRange(double NewRangeMin, double NewRangeMax, EViewRangeInterpolation Interpolation);` — Set a new range based on a min, max and an interpolation mode @param NewRangeMin		The new lower bound of the range @param NewRangeMax		The new upper bound of the range @param Interpolation		How to set the new range (either immediately, or animated)
- L148 _public prototype_ `virtual void SetClampRange(double NewRangeMin, double NewRangeMax);` — Set a new clamp range based on a min, max @param NewRangeMin		The new lower bound of the clamp range @param NewRangeMax		The new upper bound of the clamp range
- L156 _public prototype_ `virtual void SetPlayRange(FFrameNumber RangeStart, int32 RangeDuration);` — Set a new playback range based on a min, max @param RangeStart		The new lower bound of the playback range @param RangeDuration		The total number of frames that we play for
- L163 _public prototype_ `virtual void SetSelectionRange(const TRange<FFrameNumber>& NewRange);` — Set a new selection range @param NewRange		The new selection range

#### class `ITimeSlider`  
`class ITimeSlider : public SCompoundWidget`  
_L169-175_
- inherits: `SCompoundWidget`
- desc: Base class for a widget that scrubs time or frames
- L172 _public function_ `SLATE_BEGIN_ARGS(ITimeSlider)`

### `Source/Editor/SequencerWidgets/Public/STemporarilyFocusedSpinBox.h` (Public)


#### struct `STemporarilyFocusedSpinBox`  
`template<typename T> struct STemporarilyFocusedSpinBox : SSpinBox<T>`  
_L13-31_
- inherits: `SSpinBox<T>`
- desc: A widget that holds a widget that is to be refocused on completion
- L16 _public function_ `void Setup()`
- L21 _public function_ `void Refocus()`
- L30 _private member_ `TWeakPtr<SWidget> PreviousFocusedWidget;`

### `Source/Editor/SequencerWidgets/Public/SequencerWidgetsDelegates.h` (Public)


#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnScrubPositionChanged, FFrameTime, bool, bool) DECLARE_DELEGATE_TwoParams(FOnViewRangeChanged, TRange<double>, EViewRangeInterpolation) DECLARE_DELEGATE_OneParam(FOnTimeRangeChanged, TRange<double>) DECLARE_DELEGATE_OneParam(FOnFrameRangeChanged, TRange<FFrameNumber>) DECLARE_DELEGATE_TwoParams(FOnSetMarkedFrame, int32, FFrameNumber) DECLARE_DELEGATE_OneParam(FOnAddMarkedFrame, FFrameNumber) DECLARE_DELEGATE_RetVal_TwoParams(FFrameNumber, FOnGetNearestKey, FFrameTime, ENearestKeyOption) DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`
- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnViewRangeChanged, TRange<double>, EViewRangeInterpolation) DECLARE_DELEGATE_OneParam(FOnTimeRangeChanged, TRange<double>) DECLARE_DELEGATE_OneParam(FOnFrameRangeChanged, TRange<FFrameNumber>) DECLARE_DELEGATE_TwoParams(FOnSetMarkedFrame, int32, FFrameNumber) DECLARE_DELEGATE_OneParam(FOnAddMarkedFrame, FFrameNumber) DECLARE_DELEGATE_RetVal_TwoParams(FFrameNumber, FOnGetNearestKey, FFrameTime, ENearestKeyOption) DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTimeRangeChanged, TRange<double>) DECLARE_DELEGATE_OneParam(FOnFrameRangeChanged, TRange<FFrameNumber>) DECLARE_DELEGATE_TwoParams(FOnSetMarkedFrame, int32, FFrameNumber) DECLARE_DELEGATE_OneParam(FOnAddMarkedFrame, FFrameNumber) DECLARE_DELEGATE_RetVal_TwoParams(FFrameNumber, FOnGetNearestKey, FFrameTime, ENearestKeyOption) DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFrameRangeChanged, TRange<FFrameNumber>) DECLARE_DELEGATE_TwoParams(FOnSetMarkedFrame, int32, FFrameNumber) DECLARE_DELEGATE_OneParam(FOnAddMarkedFrame, FFrameNumber) DECLARE_DELEGATE_RetVal_TwoParams(FFrameNumber, FOnGetNearestKey, FFrameTime, ENearestKeyOption) DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`
- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSetMarkedFrame, int32, FFrameNumber) DECLARE_DELEGATE_OneParam(FOnAddMarkedFrame, FFrameNumber) DECLARE_DELEGATE_RetVal_TwoParams(FFrameNumber, FOnGetNearestKey, FFrameTime, ENearestKeyOption) DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAddMarkedFrame, FFrameNumber) DECLARE_DELEGATE_RetVal_TwoParams(FFrameNumber, FOnGetNearestKey, FFrameTime, ENearestKeyOption) DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FFrameNumber, FOnGetNearestKey, FFrameTime, ENearestKeyOption) DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnScrubPositionParentChanged, FMovieSceneSequenceID)`

### `Source/Editor/SequencerWidgets/Public/TimeSliderArgs.h` (Public)


#### enum `ENearestKeyOption`  
`enum class ENearestKeyOption : uint8`  
_L22-37_
- desc: Enum specifying how to find the nearest key
- L24 _public enumerator_ `NKO_None = 0x00`
- L27 _public enumerator_ `NKO_SearchKeys = 0x01` — Search keys
- L30 _public enumerator_ `NKO_SearchSections = 0x02` — Search sections
- L33 _public enumerator_ `NKO_SearchMarkers = 0x04` — Search markers
- L36 _public enumerator_ `NKO_SearchAllTracks UE_DEPRECATED(5.4, "Search all tracks has been deprecated") = 0x08` — Search all tracks

#### struct `FTimeSliderArgs`  
`struct FTimeSliderArgs`  
_L40-171_
- L42 _public function_ `FTimeSliderArgs() : ScrubPosition(0) , ViewRange(FAnimatedRange(0.0f, 5.0f)) , ClampRange(FAnimatedRange(-FLT_MAX / 2.f, FLT_MAX / 2.f)) , AllowZoom(true)`
- L50 _public member_ `TAttribute<FFrameTime> ScrubPosition;` — The scrub position
- L53 _public member_ `TAttribute<FString> ScrubPositionText;` — The scrub position text
- L56 _public member_ `TAttribute<FMovieSceneSequenceID> ScrubPositionParent;` — The parent sequence that the scrub position display text is relative to
- L59 _public member_ `FOnScrubPositionParentChanged OnScrubPositionParentChanged;` — Called when the scrub position parent sequence is changed
- L62 _public member_ `TAttribute<TArray<FMovieSceneSequenceID>> ScrubPositionParentChain;` — Attribute for the parent sequence chain of the current sequence
- L65 _public member_ `TAttribute< FAnimatedRange > ViewRange;` — View time range
- L68 _public member_ `TAttribute< FAnimatedRange > ClampRange;` — Clamp time range
- L71 _public member_ `FOnScrubPositionChanged OnScrubPositionChanged;` — Called when the scrub position changes
- L74 _public member_ `FSimpleDelegate OnBeginScrubberMovement;` — Called right before the scrubber begins to move
- L77 _public member_ `FSimpleDelegate OnEndScrubberMovement;` — Called right after the scrubber handle is released by the user
- L80 _public member_ `FOnViewRangeChanged OnViewRangeChanged;` — Called when the view range changes
- L83 _public member_ `FOnTimeRangeChanged OnClampRangeChanged;` — Called when the clamp range changes
- L86 _public member_ `FOnGetNearestKey OnGetNearestKey;` — Delegate that is called when getting the nearest key
- L89 _public member_ `TAttribute<TOptional<TRange<FFrameNumber>>> SubSequenceRange;` — Attribute defining the active sub-sequence range for this controller
- L92 _public member_ `TAttribute<TRange<FFrameNumber>> PlaybackRange;` — Attribute defining the playback range for this controller
- L95 _public member_ `TAttribute<TRange<FFrameNumber>> TimeBounds;` — Attribute defining the time bounds for this controller. The time bounds should be a subset of the playback range.
- L98 _public member_ `TAttribute<FFrameRate> DisplayRate;` — Attribute for the current sequence's display rate
- L101 _public member_ `TAttribute<FFrameRate> TickResolution;` — Attribute for the current sequence's tick resolution
- L104 _public member_ `FOnFrameRangeChanged OnPlaybackRangeChanged;` — Delegate that is called when the playback range wants to change
- L107 _public member_ `FSimpleDelegate OnPlaybackRangeBeginDrag;` — Called right before the playback range starts to be dragged
- L110 _public member_ `FSimpleDelegate OnPlaybackRangeEndDrag;` — Called right after the playback range has finished being dragged
- L113 _public member_ `TAttribute<TRange<FFrameNumber>> SelectionRange;` — Attribute defining the selection range for this controller
- L116 _public member_ `FOnFrameRangeChanged OnSelectionRangeChanged;` — Delegate that is called when the selection range wants to change
- L119 _public member_ `FSimpleDelegate OnSelectionRangeBeginDrag;` — Called right before the selection range starts to be dragged
- L122 _public member_ `FSimpleDelegate OnSelectionRangeEndDrag;` — Called right after the selection range has finished being dragged
- L125 _public member_ `FSimpleDelegate OnMarkBeginDrag;` — Called right before a mark starts to be dragged
- L128 _public member_ `FSimpleDelegate OnMarkEndDrag;` — Called right after a mark has finished being dragged
- L131 _public member_ `TAttribute<TSet<FFrameNumber>> VerticalFrames;` — Attribute for the current sequence's vertical frames
- L134 _public member_ `TAttribute<TArray<FMovieSceneMarkedFrame>> MarkedFrames;` — Attribute for the current sequence's marked frames
- L137 _public member_ `TAttribute<TArray<FMovieSceneMarkedFrame>> GlobalMarkedFrames;` — Attribute for the marked frames that might need to be shown, but do not belong to the current sequence
- L140 _public member_ `FOnSetMarkedFrame OnSetMarkedFrame;` — Called when the marked frame needs to be set
- L143 _public member_ `FOnAddMarkedFrame OnAddMarkedFrame;` — Called when a marked frame is added
- L146 _public member_ `FSimpleDelegate OnDeleteAllMarkedFrames;` — Called when all marked frames should be deleted
- L149 _public member_ `TAttribute<EMovieScenePlayerStatus::Type> PlaybackStatus;` — Round the scrub position to an integer during playback
- L152 _public member_ `TAttribute<bool> IsPlaybackRangeLocked;` — Attribute defining whether the playback range is locked
- L155 _public member_ `TAttribute<bool> AreMarkedFramesLocked;` — Attribute defining whether the marked frames are locked
- L158 _public member_ `TAttribute<float> TimeSnapInterval;` — Attribute defining the time snap interval
- L161 _public member_ `FSimpleDelegate OnTogglePlaybackRangeLocked;` — Called when toggling the playback range lock
- L164 _public member_ `FSimpleDelegate OnToggleMarkedFramesLocked;` — Called when toggling the marked frames lock
- L167 _public member_ `bool AllowZoom;` — If we are allowed to zoom
- L170 _public member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;` — Numeric Type interface for converting between frame numbers and display formats.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EMovieScenePlayerStatus`
- L38 _prototype_ `ENUM_CLASS_FLAGS(ENearestKeyOption);`

### `Source/Editor/SequencerWidgets/Public/ViewRangeInterpolation.h` (Public)


#### enum `EViewRangeInterpolation`  
`enum class EViewRangeInterpolation`  
_L6-12_
- desc: Enum specifying how to interpolate to a new view range
- L9 _public enumerator_ `Animated` — Use an externally defined animated interpolation
- L11 _public enumerator_ `Immediate` — Set the view range immediately

### `Source/Editor/SequencerWidgets/Public/WidgetFocusUtils.h` (Public)


#### class `FPendingWidgetFocus`  
`class FPendingWidgetFocus : public TSharedFromThis<FPendingWidgetFocus>`  
_L22-50_
- inherits: `TSharedFromThis<FPendingWidgetFocus>`
- L26 _public prototype_ `FPendingWidgetFocus() = default;`
- L27 _public prototype_ `FPendingWidgetFocus(const TArray<FName>& InTypesKeepingFocus);`
- L29 _public prototype_ `static FPendingWidgetFocus MakeNoTextEdit();`
- L31 _public prototype_ `~FPendingWidgetFocus();`
- L33 _public prototype_ `void Enable(const bool InEnabled);`
- L34 _public prototype_ `bool IsEnabled() const;`
- L36 _public prototype_ `void SetPendingFocusIfNeeded(const TWeakPtr<SWidget>& InWidget);`
- L37 _public prototype_ `void ResetPendingFocus();`
- L41 _private prototype_ `void OnPreInputKeyDown(const FKeyEvent&);`
- L42 _private prototype_ `void OnPreInputButtonDown(const FPointerEvent&);`
- L43 _private prototype_ `bool CanFocusBeStolen() const;`
- L45 _private member_ `TFunction<void()> PendingFocusFunction;`
- L46 _private member_ `FDelegateHandle PreInputKeyDownHandle;`
- L47 _private member_ `FDelegateHandle PreInputButtonDownHandle;`
- L49 _private member_ `TArray<FName> KeepingFocus;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERWIDGETS_API`
