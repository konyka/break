# Runtime / AppFramework

- module root: `Source/Runtime/AppFramework`
- headers: 17; symbols: 581
- symbol kinds: class=18, delegate=17, enum=4, enumerator=17, externvar=1, function=55, macro=1, member=202, prototype=259, struct=4, typedef=3
- DynamicallyLoadedModuleNames: SlateReflector
- PrivateDependencyModuleNames: InputCore
- PrivateIncludePathModuleNames: SlateReflector
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, Slate, SlateCore

### `Source/Runtime/AppFramework/Private/Framework/Testing/SLayoutExample.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `TSharedRef<SWidget> MakeLayoutExample();`

### `Source/Runtime/AppFramework/Private/Framework/Testing/SStarshipGallery.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `TSharedRef<SWidget> MakeStarshipGallery();` — @return a new Starship Widget Test Gallery

### `Source/Runtime/AppFramework/Private/Framework/Testing/STableViewTesting.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `TSharedRef<SWidget> MakeTableViewTesting();`

### `Source/Runtime/AppFramework/Private/Framework/Testing/SUserWidgetTest.h` (Private)


#### class `SUserWidgetExample`  
`class SUserWidgetExample : public SUserWidget`  
_L12-26_
- inherits: `SUserWidget`
- L17 _public function_ `SLATE_USER_ARGS(SUserWidgetExample) : _Title()`
- L20 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_END_ARGS() virtual void Construct( const FArguments& InArgs ) = 0;`
- L25 _public prototype_ `virtual void DoStuff() = 0;`

### `Source/Runtime/AppFramework/Private/Framework/Testing/SWidgetGallery.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `TSharedRef<SWidget> MakeWidgetGallery();` — @return a new Drag and Drop test widget

### `Source/Runtime/AppFramework/Private/Framework/Testing/TestStyle.h` (Private)


#### class `FTestStyle`  
`class FTestStyle`  
_L12-34_
- desc: Test slate style
- L16 _public prototype_ `static TSharedRef< class ISlateStyle > Create();`
- L19 _public function_ `static const ISlateStyle& Get()` — @return the singleton instance.
- L24 _public prototype_ `static void ResetToDefault();`
- L28 _private prototype_ `static void SetStyle( const TSharedRef< class ISlateStyle >& NewStyle );`
- L33 _private member_ `static TSharedPtr< class ISlateStyle > Instance;` — Singleton instances of this style.

### `Source/Runtime/AppFramework/Private/Widgets/Colors/SColorSlider.h` (Private)


#### class `SColorSlider`  
`class SColorSlider : public SCompoundWidget`  
_L17-156_
- inherits: `SCompoundWidget`
- desc: Implements a color slider widget. When the orientation is horizontal, it features an STextBlock label, a SSlider with color gradient drawn on top, and a SSpinBox. When the orientation is vertical, it features only the SSlider with color gradient
- L20 _public prototype_ `SColorSlider();`
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, float);` — Notification for numeric value change
- L25 _public function_ `SLATE_BEGIN_ARGS(SColorSlider) : _Value(0.0f) , _MinSpinBoxValue(0.0f) , _MaxSpinBoxValue(1.0f) , _MinSliderValue(0.0f) , _MaxSliderValue(1.0f) , _Delta(0.01f) , _SupportDynamicSliderMaxValue(true) , _Orientation(Orient_Horizontal) , _Label() , _GradientColors() , _HasAlphaBackground(false) , _UseSRGB(true) , _PreventThrottling(false) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _OnBeginSpinBoxMovement() , _OnEndSpinBoxMovement()`
- L47 _public prototype_ `SLATE_ATTRIBUTE(float, Value) SLATE_ATTRIBUTE(float, MinSpinBoxValue) SLATE_ATTRIBUTE(float, MaxSpinBoxValue) SLATE_ATTRIBUTE(float, MinSliderValue) SLATE_ATTRIBUTE(float, MaxSliderValue) SLATE_ATTRIBUTE(float, Delta) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMaxValue) SLATE_ATTRIBUTE(EOrientation, Orientation) SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(TArray<FLinearColor>, GradientColors) SLATE_ATTRIBUTE(bool, HasAlphaBackground) SLATE_ATTRIBUTE(bool, UseSRGB) SLATE_ARGUMENT(bool, PreventThrottling) SLATE_EVENT(FOnValueChanged, OnValueChanged)` — The value that determines where the slider handle is drawn
- L111 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L112 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L117 _private prototype_ `void OnSpinBoxValueCommitted(float NewValue, ETextCommit::Type CommitType);` — Update the max value of the slider if the value committed is higher than the current maximum slider value
- L121 _private member_ `TSlateAttribute<EOrientation, EInvalidateWidgetReason::Paint> Orientation;` — Orientation of the slider
- L124 _private member_ `TSlateAttribute<TArray<FLinearColor>, EInvalidateWidgetReason::Paint> GradientColors;` — The colors used in the gradient.
- L127 _private member_ `TSlateAttribute<bool, EInvalidateWidgetReason::Paint> bHasAlphaBackground;` — Whether a checker background is displayed for alpha viewing
- L130 _private member_ `TSlateAttribute<bool, EInvalidateWidgetReason::Paint> bUseSRGB;` — Whether to display sRGB color
- L133 _private member_ `TSlateAttribute<bool, EInvalidateWidgetReason::Paint> bSupportDynamicSliderMaxValue;` — Whether to dynamically update the maximum slider value
- L136 _private member_ `TSharedPtr<SSlider> Slider;` — Slider widget
- L139 _private member_ `float ColorSliderSize = 0.0f;` — Widget layout sizes
- L141 _private member_ `static constexpr float Padding = 8.0f;`
- L142 _private member_ `static constexpr float LabelSize = 8.0f;`
- L143 _private member_ `static constexpr float SpinBoxSize = 60.0f;`
- L145 _private member_ `static constexpr float HorizontalSliderLength = 123.0f;`
- L146 _private member_ `static constexpr float HorizontalSliderHeight = 20.0f;`
- L148 _private member_ `static constexpr float VerticalSliderWidth = 28.0f;`
- L149 _private member_ `static constexpr float VerticalSliderHeight = 200.0f;`
- L152 _private member_ `const FSlateBrush* BorderBrush;` — Styling brushes
- L153 _private member_ `const FSlateBrush* BorderActiveBrush;`
- L154 _private member_ `const FSlateBrush* BorderHoveredBrush;`
- L155 _private member_ `const FSlateBrush* AlphaBackgroundBrush;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, float);` — Notification for numeric value change

### `Source/Runtime/AppFramework/Private/Widgets/Colors/SColorValueSlider.h` (Private)


#### class `SColorValueSlider`  
`class SColorValueSlider : public SLeafWidget`  
_L27-174_
- inherits: `SLeafWidget`
- desc: The value slider is a simple control like the color wheel for selecting value.
- L32 _public function_ `SLATE_BEGIN_ARGS( SColorValueSlider ) : _SelectedColor() , _OnValueChanged() , _OnMouseCaptureBegin() , _OnMouseCaptureEnd()`
- L40 _public function_ `SLATE_ATTRIBUTE(FLinearColor, SelectedColor) SLATE_EVENT(FOnLinearColorValueChanged, OnValueChanged) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_END_ARGS() void Construct( const FArguments& InArgs )` — The current color selected by the user
- L63 _public function_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const`
- L101 _public function_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent )`
- L115 _public function_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent )`
- L129 _public function_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent )`
- L148 _public function_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent )`
- L153 _public function_ `virtual FVector2D ComputeDesiredSize(float) const`
- L161 _protected member_ `const FSlateBrush* SelectorImage;` — The color selector image to show
- L164 _protected member_ `TAttribute< FLinearColor > SelectedColor;` — The current color selected by the user
- L167 _protected member_ `FOnLinearColorValueChanged OnValueChanged;` — Invoked when a new value is selected on the color wheel
- L170 _protected member_ `FSimpleDelegate OnMouseCaptureBegin;` — Invoked when the mouse is pressed
- L173 _protected member_ `FSimpleDelegate OnMouseCaptureEnd;` — Invoked when the mouse is let up

### `Source/Runtime/AppFramework/Private/Widgets/Colors/SEyeDropperButton.h` (Private)


#### class `SEyeDropperButton`  
`class SEyeDropperButton : public SButton`  
_L21-91_
- inherits: `SButton`
- desc: Class for placing a color picker eye-dropper button. A self contained until that only needs client code to set the display gamma and listen for the OnValueChanged events. It toggles the dropper when clicked. When active it captures the mouse, shows a dropper cursor and samples the pixel color constantly. It is stopped normally by hitting the ESC key.
- L24 _public function_ `DECLARE_DELEGATE_OneParam(FOnDropperComplete, bool) SLATE_BEGIN_ARGS( SEyeDropperButton ) : _OnValueChanged() , _OnBegin() , _OnComplete() , _DisplayGamma()`
- L34 _public prototype_ `SLATE_EVENT(FOnLinearColorValueChanged, OnValueChanged) SLATE_EVENT(FSimpleDelegate, OnBegin) SLATE_EVENT(FOnDropperComplete, OnComplete) SLATE_ATTRIBUTE(float, DisplayGamma) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Invoked when a new value is selected by the dropper
- L49 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L50 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L52 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L53 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L54 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L58 _private prototype_ `FReply OnClicked();`
- L60 _private prototype_ `EVisibility GetEscapeTextVisibility() const;`
- L62 _private prototype_ `FSlateColor GetDropperImageColor() const;`
- L64 _private prototype_ `bool IsMouseOver(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L66 _private prototype_ `void OnPreTick(float DeltaTime);`
- L67 _private prototype_ `void ResetDropperModeStates();`
- L72 _private member_ `FOnLinearColorValueChanged OnValueChanged;` — Invoked when a new value is selected by the dropper
- L75 _private member_ `FSimpleDelegate OnBegin;` — Invoked when the dropper goes from inactive to active
- L78 _private member_ `FOnDropperComplete OnComplete;` — Invoked when the dropper goes from active to inactive - can be used to commit colors by the owning picker
- L81 _private member_ `TAttribute<float> DisplayGamma;` — Sets the display Gamma setting - used to correct colors sampled from the screen
- L84 _private member_ `TOptional<FVector2D> LastCursorPosition;` — Previous Tick's cursor position
- L87 _private member_ `bool bWasClicked;` — Dropper states
- L88 _private member_ `bool bWasClickActivated;`
- L89 _private member_ `bool bWasLeft;`
- L90 _private member_ `bool bWasReEntered;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDropperComplete, bool) SLATE_BEGIN_ARGS( SEyeDropperButton ) : _OnValueChanged() , _OnBegin() , _OnComplete() , _DisplayGamma() {} SLATE_EVENT(FOnLinearColorValueChanged, OnValueChanged) SLATE_EVENT(FSimpleDelegate, OnBegin) SLATE_EVENT(FOnDropperComplete, OnComplete) SLATE_ATTRIBUTE(float, DisplayGamma) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Source/Runtime/AppFramework/Public/Widgets/Colors/SColorGradingPicker.h` (Public)


#### enum `EColorGradingModes`  
`enum class UE_DEPRECATED(5.5, "Color grading widgets and associated types have moved to the AdvancedWidgets module.") EColorGradingModes`  
_L21-29_
- desc: Enumerates color picker modes.
- L23 _public enumerator_ `Saturation`
- L24 _public enumerator_ `Contrast`
- L25 _public enumerator_ `Gamma`
- L26 _public enumerator_ `Gain`
- L27 _public enumerator_ `Offset`
- L28 _public enumerator_ `Invalid`

#### class `SColorGradingPicker`  
`class UE_DEPRECATED(5.5, "Color grading widgets and associated types have moved to the AdvancedWidgets module.") SColorGradingPicker : public SCompoundWidget`  
_L37-181_
- inherits: `SCompoundWidget`
- desc: Class for placing a color picker. If all you need is a standalone color picker, use the functions OpenColorGradingWheel and DestroyColorGradingWheel, since they hold a static instance of the color picker.
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L45 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnColorGradingPickerValueChanged, FVector4&, bool);` — Delegate called when the widget Color Data changed
- L48 _public function_ `SLATE_BEGIN_ARGS(SColorGradingPicker) : _AllowSpin(true) , _SupportDynamicSliderMaxValue(false) , _SupportDynamicSliderMinValue(false) , _MainDelta(0.01f) , _MainShiftMultiplier(10.f) , _MainCtrlMultiplier(0.1f) PRAGMA_DISABLE_DEPRECATION_WARNINGS , _ColorGradingModes(EColorGradingModes::Saturation) PRAGMA_ENABLE_DEPRECATION_WARNINGS , _OnColorCommitted() , _OnQueryCurrentColor()`
- L62 _public prototype_ `SLATE_ARGUMENT(TOptional<float>, ValueMin ) SLATE_ARGUMENT(TOptional<float>, ValueMax ) SLATE_ARGUMENT(TOptional<float>, SliderValueMin) SLATE_ARGUMENT(TOptional<float>, SliderValueMax) SLATE_ATTRIBUTE(bool, AllowSpin) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMaxValue) SLATE_ATTRIBUTE(bool, SupportDynamicSliderMinValue) SLATE_ARGUMENT( float, MainDelta ) SLATE_ARGUMENT(float, MainShiftMultiplier) SLATE_ARGUMENT(float, MainCtrlMultiplier) SLATE_ARGUMENT_DEPRECATED( int32, MainShiftMouseMovePixelPerDelta, 5.4, "Shift Mouse Move Pixel Per Delta is deprecated and incrementing by a fixed delta per pixel is no longer supported. Please use ShiftMultiplier and CtrlMultiplier which will multiply the step per mouse move") PRAGMA_DISABLE_DEPRECATION_WARNINGS SLATE_ARGUMENT( EColorGradingModes, ColorGradingModes) PRAGMA_ENABLE_DEPRECATION_WARNINGS PRAGMA_DISABLE_DEPRECATION_WARNINGS SLATE_EVENT(FOnColorGradingPickerValueChanged, OnColorCommitted ) PRAGMA_ENABLE_DEPRECATION_WARNINGS PRAGMA_DISABLE_DEPRECATION_WARNINGS SLATE_EVENT(FOnGetCurrentVector4Value, OnQueryCurrentColor) PRAGMA_ENABLE_DEPRECATION_WARNINGS SLATE_EVENT(FSimpleDelegate, OnBeginSliderMovement) SLATE_EVENT(FSimpleDelegate, OnEndSliderMovement)`
- L120 _public prototype_ `void Construct(const FArguments& InArgs );` — Construct the widget @param InArgs Declaration from which to construct the widget.
- L122 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMaxValueChangedDelegate()`
- L123 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMinValueChangedDelegate()`
- L126 _public prototype_ `void OnDynamicSliderMaxValueChanged(float NewMaxSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfHigher);` — Callback when the max/min spinner value are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L127 _public prototype_ `void OnDynamicSliderMinValueChanged(float NewMinSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfLower);`
- L131 _protected prototype_ `void TransformLinearColorRangeToColorGradingRange(FVector4 &VectorValue) const;`
- L132 _protected prototype_ `void TransformColorGradingRangeToLinearColorRange(FVector4 &VectorValue) const;`
- L133 _protected prototype_ `void TransformColorGradingRangeToLinearColorRange(float &FloatValue);`
- L135 _protected prototype_ `TOptional<float> OnGetMainValue() const;`
- L136 _protected prototype_ `void OnMainValueChanged(float InValue, bool ShouldCommitValueChanges);`
- L137 _protected prototype_ `void OnMainValueCommitted(float InValue, ETextCommit::Type CommitType);`
- L139 _protected prototype_ `FLinearColor GetCurrentLinearColor();`
- L141 _protected prototype_ `bool IsEntryBoxEnabled() const;`
- L144 _protected prototype_ `void HandleCurrentColorValueChanged(const FLinearColor& NewValue, bool ShouldCommitValueChanges);` — Callback for value changes in the color spectrum picker.
- L146 _protected prototype_ `void HandleColorWheelMouseCaptureBegin(const FLinearColor& InValue);`
- L147 _protected prototype_ `void HandleColorWheelMouseCaptureEnd(const FLinearColor& InValue);`
- L149 _protected prototype_ `void OnBeginSliderMovement();`
- L150 _protected prototype_ `void OnEndSliderMovement(float NewValue);`
- L151 _protected prototype_ `void AdjustRatioValue(FVector4 &NewValue);`
- L153 _protected member_ `bool bIsMouseDragging;`
- L154 _protected member_ `FVector4 StartDragRatio;`
- L156 _protected member_ `float SliderValueMin;`
- L157 _protected member_ `float SliderValueMax;`
- L158 _protected member_ `float MainDelta;`
- L159 _protected member_ `float MainShiftMultiplier;`
- L160 _protected member_ `float MainCtrlMultiplier;`
- L163 _protected member_ `EColorGradingModes ColorGradingModes;`
- L166 _protected member_ `TSharedPtr<SNumericEntryBox<float>> NumericEntryBoxWidget;`
- L169 _protected member_ `FOnColorGradingPickerValueChanged OnColorCommitted;` — Invoked when a new value is selected on the color wheel
- L172 _protected member_ `FOnGetCurrentVector4Value OnQueryCurrentColor;`
- L174 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMaxValueChanged;`
- L175 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMinValueChanged;`
- L177 _protected member_ `FSimpleDelegate ExternalBeginSliderMovementDelegate;`
- L178 _protected member_ `FSimpleDelegate ExternalEndSliderMovementDelegate;`
- L179 _protected member_ `FSimpleDelegate ExternalBeginMouseCaptureDelegate;`
- L180 _protected member_ `FSimpleDelegate ExternalEndMouseCaptureDelegate;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetCurrentVector4Value, FVector4&) enum class UE_DEPRECATED(5.5, "Color grading widgets and associated types have moved to the AdvancedWidgets module.") EColorGradingModes { Saturation, Contrast, Gamma, Gain, Offset, Invalid };`
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min spinner values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L45 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnColorGradingPickerValueChanged, FVector4&, bool);` — Delegate called when the widget Color Data changed

### `Source/Runtime/AppFramework/Public/Widgets/Colors/SColorPicker.h` (Public)


#### enum `EColorPickerChannels`  
`enum class EColorPickerChannels`  
_L31-40_
- desc: Enumerates color channels (do not reorder).
- L33 _public enumerator_ `Red`
- L34 _public enumerator_ `Green`
- L35 _public enumerator_ `Blue`
- L36 _public enumerator_ `Alpha`
- L37 _public enumerator_ `Hue`
- L38 _public enumerator_ `Saturation`
- L39 _public enumerator_ `Value`

#### enum `EColorPickerModes`  
`enum class EColorPickerModes`  
_L46-50_
- desc: Enumerates color picker modes.
- L48 _public enumerator_ `Spectrum`
- L49 _public enumerator_ `Wheel`

#### enum `EColorPickerHexMode`  
`enum class EColorPickerHexMode`  
_L56-60_
- desc: Enumerates hexadecimal text modes.
- L58 _public enumerator_ `SRGB`
- L59 _public enumerator_ `Linear`

#### struct `FColorChannels`  
`struct FColorChannels`  
_L66-77_
- desc: Struct for holding individual pointers to float values.
- L68 _public function_ `FColorChannels()`
- L73 _public member_ `float* Red;`
- L74 _public member_ `float* Green;`
- L75 _public member_ `float* Blue;`
- L76 _public member_ `float* Alpha;`

#### class `SColorPicker`  
`class SColorPicker : public SCompoundWidget`  
_L84-539_
- inherits: `SCompoundWidget`
- desc: Class for placing a color picker. If all you need is a standalone color picker, use the functions OpenColorPicker and DestroyColorPicker, since they hold a static instance of the color picker.
- L89 _public function_ `SLATE_BEGIN_ARGS(SColorPicker) : _TargetColorAttribute(FLinearColor(ForceInit)) , _ColorWheelBrush(FCoreStyle::Get().GetBrush("ColorWheel.HueValueCircle")) , _UseAlpha(true) , _OnlyRefreshOnMouseUp(false) , _OnlyRefreshOnOk(false) , _OnColorCommitted() , _PreColorCommitted() , _OnColorPickerCancelled() , _OnColorPickerWindowClosed() , _OnInteractivePickBegin() , _OnInteractivePickEnd() , _ParentWindow() , _DisplayGamma(2.2f) , _sRGBOverride() , _DisplayInlineVersion(false) , _OverrideColorPickerCreation(false) , _ExpandAdvancedSection(false) , _ClampValue(false) , _OptionalOwningDetailsView(nullptr)`
- L112 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, TargetColorAttribute) SLATE_ATTRIBUTE(const FSlateBrush*, ColorWheelBrush) SLATE_ARGUMENT_DEPRECATED(TArray<FColor*>, TargetFColors, 5.2, "TargetFColors is deprecated. Use OnColorCommitted to get the selected color.") SLATE_ARGUMENT_DEPRECATED(TArray<FLinearColor*>, TargetLinearColors, 5.2, "TargetLinearColors is deprecated. Use OnColorCommitted to get the selected color.") SLATE_ARGUMENT_DEPRECATED(TArray<FColorChannels>, TargetColorChannels, 5.2, "TargetColorChannels is deprecated. Use OnColorCommitted to get the selected color.") SLATE_ATTRIBUTE(bool, UseAlpha) SLATE_ATTRIBUTE(bool, OnlyRefreshOnMouseUp) SLATE_ATTRIBUTE(bool, OnlyRefreshOnOk) SLATE_EVENT(FOnLinearColorValueChanged, OnColorCommitted) UE_DEPRECATED(5.2, "PreColorCommitted is deprecated. Use OnColorCommitted to update your values.") SLATE_EVENT(FOnLinearColorValueChanged, PreColorCommitted) SLATE_EVENT(FOnColorPickerCancelled, OnColorPickerCancelled) SLATE_EVENT(FOnWindowClosed, OnColorPickerWindowClosed)` — The color that is being targeted as a TAttribute
- L187 _public prototype_ `~SColorPicker();` — Destructor.
- L196 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the widget @param InArgs Declaration from which to construct the widget.
- L199 _public function_ `TSharedPtr<SWidget> GetOptionalOwningDetailsView()` — Gets the (optionally set) owning details view of the current color picker
- L212 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnColorPickerCreationOverride, const TSharedRef<SColorPicker>&);` — Delegate to override color picker creation behavior
- L213 _public member_ `static FOnColorPickerCreationOverride OnColorPickerNonModalCreateOverride;`
- L216 _public prototype_ `DECLARE_DELEGATE(FOnColorPickerDestructionOverride);` — Delegate to override color picker destruction behavior
- L217 _public member_ `static FOnColorPickerDestructionOverride OnColorPickerDestroyOverride;`
- L236 _public prototype_ `static TSharedRef<SButton> CreateStandaloneEyeDropperButton(const FEyeDropperButtonArgs& InArgs);` — Creates a standalone eye dropper button that functions identically to the button within the color picker
- L241 _protected prototype_ `void BackupColors();` — Backup all the colors that are being modified
- L243 _protected prototype_ `bool ApplyNewTargetColor(bool bForceUpdate = false);`
- L245 _protected prototype_ `void GenerateDefaultColorPickerContent(bool bAdvancedSectionExpanded);`
- L246 _protected prototype_ `void GenerateInlineColorPickerContent();`
- L248 _protected function_ `FLinearColor GetCurrentColor() const`
- L254 _protected prototype_ `void DiscardColor();` — Calls the user defined delegate for when the color changes are discarded
- L257 _protected prototype_ `bool SetNewTargetColorRGB(const FLinearColor& NewValue, bool bForceUpdate = false);` — Sets new color in ether RGB or HSV
- L258 _protected prototype_ `bool SetNewTargetColorHSV(const FLinearColor& NewValue, bool bForceUpdate = false);`
- L260 _protected prototype_ `void UpdateColorPick();`
- L261 _protected prototype_ `void UpdateColorPickMouseUp();`
- L263 _protected prototype_ `void BeginAnimation(FLinearColor Start, FLinearColor End);`
- L266 _protected prototype_ `void HideSmallTrash();` — `UE_DEPRECATED(5.6, "HideSmallTrash is deprecated. The delete button for theme colors is managed by the SThemeColorBlocksBar widget.")`
- L269 _protected prototype_ `void ShowSmallTrash();` — `UE_DEPRECATED(5.6, "ShowSmallTrash is deprecated. The delete button for theme colors is managed by the SThemeColorBlocksBar widget.")`
- L272 _protected prototype_ `void CycleMode();` — Cycles the color picker's mode.
- L280 _protected prototype_ `TSharedRef<SWidget> MakeColorSlider(EColorPickerChannels Channel) const;` — Creates a color slider widget for the specified channel. @param Channel The color channel to create the widget for. @return The new slider.
- L288 _protected prototype_ `TSharedRef<SWidget> MakeColorSpinBox(EColorPickerChannels Channel) const;` — Creates a color spin box widget for the specified channel. @param Channel The color channel to create the widget for. @return The new spin box.
- L295 _protected prototype_ `TSharedRef<SWidget> MakeColorPreviewBox() const;` — Creates the color preview box widget. @return The new color preview box.
- L300 _private prototype_ `EActiveTimerReturnType AnimatePostConstruct(double InCurrentTime, float InDeltaTime);` — Callback for the active timer to animate the color post-construct
- L303 _private prototype_ `FLinearColor GetGradientEndColor(EColorPickerChannels Channel) const;` — Callback for getting the end color of a color spin box gradient.
- L306 _private prototype_ `FLinearColor GetGradientStartColor(EColorPickerChannels Channel) const;` — Callback for getting the start color of a color spin box gradient.
- L309 _private prototype_ `TArray<FLinearColor> GetGradientColors(EColorPickerChannels Channel) const;` — Callback for getting the array of colors for a color spin box gradient.
- L312 _private prototype_ `EColorBlockAlphaDisplayMode HandleColorPreviewAlphaMode() const;` — Callback for getting the alpha display mode of the color preview swatches.
- L315 _private prototype_ `FReply HandleCancelButtonClicked();` — Callback for clicking the Cancel button.
- L318 _private prototype_ `FReply HandleColorAreaMouseDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Callback for pressing a mouse button in the color area.
- L321 _private prototype_ `FReply HandleColorPickerModeButtonClicked();` — Callback for clicking the color picker mode button.
- L324 _private prototype_ `EVisibility HandleColorPickerModeVisibility(EColorPickerModes Mode) const;` — Callback for getting the visibility of the given color picker mode.
- L327 _private prototype_ `FReply ToggleThemePanelVisibility();` — Callback for setting the visibility of the themes panel.
- L330 _private prototype_ `const FSlateBrush* HandleThemePanelButtonImageBrush() const;` — Callback for getting the icon to display on the Show/Hide themes panel button.
- L333 _private prototype_ `EVisibility HandleThemesPanelVisibility() const;` — Callback for getting the visibility of the themes panel.
- L336 _private prototype_ `FText GetColorThemePanelToolTipText() const;` — Callback for getting the tooltip for the color theme panel
- L339 _private prototype_ `FLinearColor HandleColorSliderEndColor(EColorPickerChannels Channel) const;` — Callback for getting the end color of a color slider.
- L342 _private prototype_ `FLinearColor HandleColorSliderStartColor(EColorPickerChannels Channel) const;` — Callback for getting the start color of a color slider.
- L345 _private prototype_ `void HandleColorWheelValueChanged(FLinearColor NewValue);` — Callback for value changes in the color wheel picker.
- L348 _private prototype_ `void HandleColorSpectrumValueChanged(FLinearColor NewValue);` — Callback for value changes in the color spectrum picker.
- L351 _private prototype_ `float HandleColorSpinBoxValue(EColorPickerChannels Channel) const;` — Callback for getting the value of a color spin box.
- L354 _private prototype_ `void HandleColorSpinBoxValueChanged(float NewValue, EColorPickerChannels Channel);` — Callback for value changes in a color spin box.
- L357 _private prototype_ `void HandleEyeDropperButtonBegin();` — Callback for start of eye dropper interactions.
- L360 _private prototype_ `void HandleEyeDropperButtonComplete(bool bCancelled);` — Callback for completed eye dropper interactions.
- L363 _private prototype_ `FText HandleHexBoxText() const;` — Callback for getting the text in the hex linear box.
- L366 _private prototype_ `void HandleHexInputTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Callback for committed text in the hex input box (sRGB gamma).
- L369 _private prototype_ `void HandleHSVColorChanged(FLinearColor NewValue);` — Callback for changing the HSV value of the current color.
- L372 _private prototype_ `void HandleInteractiveChangeBegin();` — Callback for when interactive user input begins.
- L375 _private prototype_ `void HandleInteractiveChangeEnd();` — Callback for when interactive user input ends.
- L378 _private prototype_ `void HandleInteractiveChangeEnd(float NewValue);` — Callback for when interactive user input ends.
- L381 _private prototype_ `FReply HandleNewColorPreviewClicked();` — Callback for clicking the new color preview block.
- L384 _private prototype_ `FReply HandleOldColorPreviewClicked();` — Callback for clicking the old color preview block.
- L387 _private prototype_ `EVisibility HandleColorPreviewButtonVisibility() const;` — Callback for getting the visibility of the old/new color buttons
- L390 _private prototype_ `void SetNewColorPreviewImageVisibility(EVisibility InButtonVisibility);` — Callback for setting the visibility of the new color preview button image
- L393 _private prototype_ `void SetOldColorPreviewImageVisibility(EVisibility InButtonVisibility);` — Callback for setting the visibility of the old color preview button image
- L396 _private prototype_ `EVisibility GetNewColorPreviewImageVisibility() const;` — Callback for getting the visibility of the new color preview button image
- L399 _private prototype_ `EVisibility GetOldColorPreviewImageVisibility() const;` — Callback for getting the visibility of the old color preview button image
- L402 _private prototype_ `FReply HandleOkButtonClicked();` — Callback for clicking the OK button.
- L405 _private prototype_ `bool HandleColorPickerUseSRGB() const;` — Callback for checking whether sRGB colors should be rendered.
- L408 _private prototype_ `void HandleParentWindowClosed(const TSharedRef<SWindow>& Window);` — Callback for when the parent window has been closed.
- L411 _private prototype_ `void HandleRGBColorChanged(FLinearColor NewValue);` — Callback for changing the RGB value of the current color.
- L414 _private prototype_ `void HandleSRGBCheckBoxCheckStateChanged(ECheckBoxState InIsChecked);` — Callback for changing the checked state of the sRGB check box.
- L417 _private prototype_ `ECheckBoxState HandleSRGBCheckBoxIsChecked() const;` — Callback for determining whether the sRGB check box should be checked.
- L420 _private prototype_ `void HandleThemeBarColorSelected(FLinearColor NewValue);` — Callback for selecting a color in the color theme bar.
- L423 _private prototype_ `TSharedRef<SWidget> MakeHexModeMenu();` — Build the menu widget for selecting the hexadecimal text mode
- L426 _private prototype_ `FText HandleHexModeButtonText() const;` — Get the text to display on the hexadecimal text mode button
- L429 _private prototype_ `void OnHexModeSelected(EColorPickerHexMode InHexMode);` — Callback for when the hexadecimal text mode changes
- L434 _private member_ `TAttribute<FLinearColor> TargetColorAttribute;` — The color that is being targeted as a TAttribute
- L437 _private member_ `TAttribute<const FSlateBrush*> ColorWheelBrush;` — The brush used as Color wheel as a TAttribute
- L440 _private member_ `FLinearColor CurrentColorHSV;` — The current color being picked in HSV
- L443 _private member_ `FLinearColor CurrentColorRGB;` — The current color being picked in RGB
- L446 _private member_ `FLinearColor OldColor;` — The old color to be changed in HSV
- L449 _private member_ `FLinearColor ColorEnd;` — Color end point to animate to
- L452 _private member_ `FLinearColor ColorBegin;` — Color start point to animate from
- L455 _private member_ `EColorPickerModes CurrentMode;` — Holds the color picker's mode.
- L458 _private member_ `EColorPickerHexMode HexMode;` — Holds the color picker's hex mode.
- L461 _private member_ `float CurrentTime;` — Time, used for color animation
- L464 _private member_ `static const double MAX_ALLOWED_UPDATE_TIME;` — The max time allowed for updating before we shut off auto-updating
- L467 _private member_ `bool bPerfIsTooSlowToUpdate;` — If true, then the performance is too bad to have auto-updating
- L470 _private member_ `TAttribute<bool> bUseAlpha;` — Whether or not the color uses Alpha or not
- L473 _private member_ `bool bUseSRGB = false;` — Whether or not to display color as sRGB
- L476 _private member_ `bool bOnlyRefreshOnMouseUp;` — Prevents immediate refresh for performance reasons.
- L479 _private member_ `bool bOnlyRefreshOnOk;` — Prevents multiple refreshes when requested.
- L482 _private member_ `bool bClosedViaOkOrCancel;` — true if the picker was closed via the OK or Cancel buttons, false otherwise
- L485 _private member_ `TWeakPtr<SWindow> ParentWindowPtr;` — Pointer to the parent window, so we know to destroy it when done
- L488 _private member_ `TSharedPtr<SThemeColorBlocksBar> CurrentThemeBar;` — The widget which holds the currently selected theme
- L491 _private member_ `EVisibility NewColorPreviewImageVisibility;` — Visibility of the new color preview button image (visible when hovered)
- L494 _private member_ `EVisibility OldColorPreviewImageVisibility;` — Visibility of the old color preview button image (visible when hovered)
- L497 _private member_ `TAttribute<float> DisplayGamma;` — Sets the display Gamma setting - used to correct colors sampled from the screen
- L500 _private member_ `bool bColorPickerIsInlineVersion;` — True if this color picker is an inline color picker
- L503 _private member_ `bool bColorPickerCreationIsOverridden;` — True if something has overridden the color picker's creation behavior
- L506 _private member_ `bool bIsInteractive;` — Tracks whether the user is moving a value spin box, the color wheel and the dropper
- L509 _private member_ `bool bValidCreationOverrideExists;` — Is true if the color picker creation behavior can be overridden
- L512 _private member_ `bool bClampValue;` — The current display gamma used to correct colors picked from the display.
- L515 _private member_ `bool bIsThemePanelVisible;` — Whether or not the color themes panel is visible or collapsed
- L520 _private member_ `FOnLinearColorValueChanged OnColorCommitted;` — Invoked when a new value is selected on the color wheel
- L523 _private member_ `FOnColorPickerCancelled OnColorPickerCancelled;` — Invoked when the color picker cancel button is pressed
- L526 _private member_ `FSimpleDelegate OnInteractivePickBegin;` — Invoked when a slider drag, color wheel drag or dropper grab starts
- L529 _private member_ `FSimpleDelegate OnInteractivePickEnd;` — Invoked when a slider drag, color wheel drag or dropper grab finishes
- L532 _private member_ `FOnWindowClosed OnColorPickerWindowClosed;` — Invoked when the color picker window closes.
- L535 _private member_ `TWeakPtr<SWidget> OptionalOwningDetailsView;` — Allows a details view to own the color picker so refreshing another details view doesn't close it
- L538 _private member_ `TSharedPtr<SColorWheel> ColorWheel;` — The Color Wheel widget embedded in this picker

#### struct `SColorPicker::FEyeDropperButtonArgs`  
`struct FEyeDropperButtonArgs`  
_L220-233_
- desc: Eye dropper button creation args
- L223 _public member_ `TDelegate<void(FLinearColor)> OnValueChanged;` — Invoked when a new value is selected by the dropper
- L226 _public member_ `FSimpleDelegate OnBegin;` — Invoked when the dropper goes from inactive to active
- L229 _public member_ `TDelegate<void(bool)> OnComplete;` — Invoked when the dropper goes from active to inactive
- L232 _public member_ `TAttribute<float> DisplayGamma = TAttribute<float>();` — Sets the display Gamma setting - used to correct colors sampled from the screen

#### struct `FColorPickerArgs`  
`struct FColorPickerArgs`  
_L542-627_
- L545 _public member_ `bool bIsModal = false;` — Whether or not the new color picker is modal.
- L548 _public member_ `TSharedPtr<SWidget> ParentWidget;` — The parent for the new color picker window
- L551 _public member_ `bool bUseAlpha = false;` — Whether or not to enable the alpha slider.
- L554 _public member_ `bool bOnlyRefreshOnMouseUp = false;` — Whether to disable the refresh except on mouse up for performance reasons.
- L557 _public member_ `bool bOnlyRefreshOnOk = false;` — Whether to disable the refresh until the picker closes.
- L560 _public member_ `bool bExpandAdvancedSection = true;` — Whether to automatically expand the Advanced section.
- L563 _public member_ `bool bOpenAsMenu = false;` — Whether to open the color picker as a menu window.
- L566 _public member_ `bool bClampValue = false;` — Set true if values should be max to 1.0. HDR values may go over 1.0.
- L569 _public member_ `TAttribute<float> DisplayGamma = 2.2f;` — The current display gamma used to correct colors picked from the display.
- L572 _public member_ `TOptional<bool> sRGBOverride = TOptional<bool>();` — If set overrides the global option for the desired setting of sRGB mode.
- L576 _public member_ `const TArray<FColor*>* ColorArray = nullptr;` — An array of FColors to target.
- L580 _public member_ `const TArray<FLinearColor*>* LinearColorArray = nullptr;` — An array of FLinearColors to target.
- L584 _public member_ `const TArray<FColorChannels>* ColorChannelsArray = nullptr;` — An array of FColorChannels to target. (deprecated now that wx is gone?)
- L587 _public member_ `FOnLinearColorValueChanged OnColorCommitted;` — A delegate to be called when the color changes.
- L591 _public member_ `FOnLinearColorValueChanged PreColorCommitted;` — A delegate to be called before the color change is committed.
- L594 _public member_ `FOnWindowClosed OnColorPickerWindowClosed;` — A delegate to be called when the color picker window closes.
- L597 _public member_ `FOnColorPickerCancelled OnColorPickerCancelled;` — A delegate to be called when the color picker cancel button is pressed
- L600 _public member_ `FSimpleDelegate OnInteractivePickBegin;` — A delegate to be called when a slider drag, color wheel drag or dropper grab starts
- L603 _public member_ `FSimpleDelegate OnInteractivePickEnd;` — A delegate to be called when a slider drag, color wheel drag or dropper grab finishes
- L607 _public member_ `FLinearColor InitialColorOverride = FLinearColor::White;` — Overrides the initial color set on the color picker.
- L610 _public member_ `FLinearColor InitialColor = FLinearColor::White;` — The initial color set on the color picker.
- L613 _public member_ `TSharedPtr<SWidget> OptionalOwningDetailsView;` — Allows a details view to own the color picker so refreshing another details view doesn't close it
- L616 _public prototype_ `FColorPickerArgs() = default;` — Default constructor.
- L618 _public function_ `FColorPickerArgs(FLinearColor InInitialColor, FOnLinearColorValueChanged InOnColorCommitted) : OnColorCommitted(MoveTemp(InOnColorCommitted)) , InitialColor(InInitialColor)`
- L624 _public prototype_ `FColorPickerArgs(const FColorPickerArgs&) = default;`
- L625 _public prototype_ `FColorPickerArgs(FColorPickerArgs&&) = default;`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColorPickerCancelled, FLinearColor);` — Called when the color picker cancel button is pressed
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnColorPickerCancelled, FLinearColor);` — Called when the color picker cancel button is pressed
- L212 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColorPickerCreationOverride, const TSharedRef<SColorPicker>&);` — Delegate to override color picker creation behavior
- L216 _delegate_ `DECLARE_DELEGATE(FOnColorPickerDestructionOverride);` — Delegate to override color picker destruction behavior
- L630 _prototype_ `TSharedPtr<SColorPicker> GetColorPicker();` — Get a pointer to the static color picker, or nullptr if it does not exist.
- L633 _prototype_ `bool OpenColorPicker(const FColorPickerArgs& Args);` — Open up the static color picker, destroying any previously existing one.
- L639 _prototype_ `void DestroyColorPicker();` — Destroy the current color picker. Necessary if the values the color picker currently targets become invalid.

### `Source/Runtime/AppFramework/Public/Widgets/Colors/SColorThemes.h` (Public)


#### struct `FColorInfo`  
`struct FColorInfo`  
_L28-45_
- L30 _public member_ `TSharedPtr<FLinearColor> Color;`
- L32 _public member_ `FText Label;`
- L34 _public function_ `FColorInfo(TSharedPtr<FLinearColor> InColor)`
- L40 _public function_ `FColorInfo(TSharedPtr<FLinearColor> InColor, FText InLabel)`

#### class `FColorTheme`  
`class FColorTheme`  
_L51-89_
- desc: A Color Theme is a name and an array of Colors. It also holds and array of refresh callbacks which it calls every time it changes at all.
- L55 _public prototype_ `FColorTheme(const FString& InName = TEXT(""), const TArray< TSharedPtr<FColorInfo> >& InColors = TArray< TSharedPtr<FColorInfo> >());`
- L58 _public function_ `const TArray< TSharedPtr<FColorInfo> >& GetColors() const` — Get a list of all the colors in the theme
- L64 _public prototype_ `void InsertNewColor(TSharedPtr<FLinearColor> InColor, int32 InsertPosition);` — Insert a color at a specific point in the list and broadcast change
- L65 _public prototype_ `void InsertNewColor(TSharedPtr<FColorInfo> InColor, int32 InsertPosition);`
- L68 _public prototype_ `int32 FindApproxColor(const FLinearColor& InColor, float Tolerance = KINDA_SMALL_NUMBER) const;` — Check to see if a color is already present in the list
- L71 _public prototype_ `void RemoveAll();` — Remove all colors from the list, broadcast change
- L74 _public prototype_ `int32 RemoveColor(const TSharedPtr<FLinearColor> InColor);` — Remove specific color from the list, broadcast change
- L76 _public member_ `FString Name;`
- L78 _public prototype_ `DECLARE_EVENT( FColorTheme, FRefreshEvent );`
- L79 _public function_ `FRefreshEvent& OnRefresh()`
- L86 _private member_ `TArray< TSharedPtr<FColorInfo> > Colors;`
- L88 _private member_ `FRefreshEvent RefreshEvent;`

#### class `SColorTrash`  
`class UE_DEPRECATED(5.6, "SColorTrash is deprecated. SThemeColorBlocksBar now uses a simple SButton for its delete button.") SColorTrash : public SCompoundWidget`  
_L96-144_
- inherits: `SCompoundWidget`
- desc: The SColorTrash is a multipurpose widget which allows FColorDragDrops to be dropped on to to be
- L101 _public function_ `SLATE_BEGIN_ARGS(SColorTrash) : _UsesSmallIcon(false)`
- L105 _public prototype_ `SLATE_ATTRIBUTE(bool, UsesSmallIcon) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L119 _protected prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;` — Called during drag and drop when the drag enters a widget. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L127 _protected prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;` — Called during drag and drop when the drag leaves a widget. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L136 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;` — Called when the user is dropping something onto a widget; terminates drag and drop. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L138 _protected prototype_ `const FSlateBrush* GetBorderStyle() const;`
- L143 _private member_ `bool bBorderActivated;` — Determines whether to draw the border to show activation

#### class `SThemeColorBlock`  
`class SThemeColorBlock : public SCompoundWidget`  
_L152-261_
- inherits: `SCompoundWidget`
- desc: SThemeColorBlocks are Color Blocks which point to a Color in a ColorTheme. They can be dragged and dropped, and clicking on one in the Color Picker will give the color that they point to.
- L157 _public function_ `SLATE_BEGIN_ARGS(SThemeColorBlock) : _Color() , _ColorInfo() , _OnSelectColor() , _Parent() , _ShowTrashCallback() , _HideTrashCallback() , _UseSRGB() , _UseAlpha() , _SupportsDrag(true)`
- L170 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FLinearColor>, Color) SLATE_ATTRIBUTE(TSharedPtr<FColorInfo>, ColorInfo) SLATE_EVENT(FOnLinearColorValueChanged, OnSelectColor) SLATE_ATTRIBUTE(TSharedPtr<SThemeColorBlocksBar>, Parent) SLATE_EVENT(FSimpleDelegate, ShowTrashCallback) SLATE_EVENT(FSimpleDelegate, HideTrashCallback) SLATE_ATTRIBUTE(bool, UseSRGB) SLATE_ATTRIBUTE(bool, UseAlpha) SLATE_ATTRIBUTE(bool, SupportsDrag) SLATE_END_ARGS() void Construct(const FArguments& InArgs );` — A pointer to the color this block uses
- L207 _private prototype_ `void OnColorBlockRename();`
- L208 _private prototype_ `FText GetLabel() const;`
- L209 _private prototype_ `void SetLabel(const FText& NewColorLabel, ETextCommit::Type CommitInfo);`
- L210 _private prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L211 _private prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L212 _private prototype_ `virtual FReply OnDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L214 _private prototype_ `FLinearColor GetColor() const;`
- L216 _private prototype_ `FText GetRedText() const;`
- L217 _private prototype_ `FText GetGreenText() const;`
- L218 _private prototype_ `FText GetBlueText() const;`
- L219 _private prototype_ `FText GetAlphaText() const;`
- L220 _private prototype_ `FText GetHueText() const;`
- L221 _private prototype_ `FText GetSaturationText() const;`
- L222 _private prototype_ `FText GetValueText() const;`
- L227 _private prototype_ `FText FormatToolTipText(const FText& ColorIdentifier, float Value) const;` — Function for formatting text for the tooltip which has limited space.
- L229 _private prototype_ `EColorBlockAlphaDisplayMode OnGetAlphaDisplayMode() const;`
- L230 _private prototype_ `bool OnReadShowBackgroundForAlpha() const;`
- L231 _private prototype_ `EVisibility OnGetAlphaVisibility() const;`
- L233 _private prototype_ `EVisibility OnGetLabelVisibility() const;`
- L236 _private member_ `TWeakPtr<FLinearColor> ColorPtr;` — A pointer to the color this block uses
- L239 _private member_ `TSharedPtr<FColorInfo> ColorInfo;` — The info for this color block
- L242 _private member_ `TWeakPtr<SThemeColorBlocksBar> ParentPtr;` — A pointer to the theme color blocks bar that is this block's origin
- L245 _private member_ `FOnLinearColorValueChanged OnSelectColor;` — Event called when this block is clicked
- L248 _private member_ `FSimpleDelegate ShowTrashCallback;` — Callback to pass down to the FColorDragDrop for it to show the trash
- L251 _private member_ `FSimpleDelegate HideTrashCallback;` — Callback to pass down to the FColorDragDrop for it to hide the trash
- L254 _private member_ `TAttribute<bool> bUseSRGB;` — Whether to use display sRGB color
- L257 _private member_ `TAttribute<bool> bUseAlpha;` — Whether or not the color uses Alpha or not
- L260 _private member_ `TAttribute<bool> bSupportsDrag;` — Whether the color block supports drag/drop operations

#### class `SColorThemeBar`  
`class UE_DEPRECATED(5.6, "SColorThemeBar is deprecated. SColorThemesViewer now displays a standard menu with a list of available themes.") SColorThemeBar : public SCompoundWidget`  
_L271-338_
- inherits: `SCompoundWidget`
- desc: SColorThemeBars include a ThemeColorBlocksBar in addition to a label. Clicking on one will select it and set the currently used color theme to it
- L275 _public function_ `SLATE_BEGIN_ARGS(SColorThemeBar) : _ColorTheme() , _OnCurrentThemeChanged() , _ShowTrashCallback() , _HideTrashCallback() , _UseSRGB() , _UseAlpha()`
- L285 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FColorTheme>, ColorTheme) SLATE_EVENT(FOnCurrentThemeChanged, OnCurrentThemeChanged) SLATE_EVENT(FSimpleDelegate, ShowTrashCallback) SLATE_EVENT(FSimpleDelegate, HideTrashCallback) SLATE_ATTRIBUTE(bool, UseSRGB) SLATE_ATTRIBUTE(bool, UseAlpha) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The color theme that this bar is displaying
- L312 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );` — The system calls this method to notify the widget that a mouse button was pressed within it. This event is bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event @return Whether the event was handled along with possible requests for the system to take action.
- L316 _private prototype_ `FText GetThemeName() const;`
- L319 _private member_ `TSharedPtr<STextBlock> ThemeNameText;` — Text Block which shows the Color Theme's name
- L322 _private member_ `TWeakPtr<FColorTheme> ColorTheme;` — Color Theme that this bar is displaying
- L325 _private member_ `FOnCurrentThemeChanged OnCurrentThemeChanged;` — Callback to execute when the global current theme has changed
- L328 _private member_ `FSimpleDelegate ShowTrashCallback;` — Callback to pass down to the FColorDragDrop for it to show the trash
- L331 _private member_ `FSimpleDelegate HideTrashCallback;` — Callback to pass down to the FColorDragDrop for it to hide the trash
- L334 _private member_ `TAttribute<bool> bUseSRGB;` — Whether to use display sRGB color
- L337 _private member_ `TAttribute<bool> bUseAlpha;` — Whether or not the color uses Alpha or not

#### class `SColorThemesViewer`  
`class SColorThemesViewer : public SCompoundWidget`  
_L344-449_
- inherits: `SCompoundWidget`
- desc: The widget that manages the dropdown menu in the Color Themes Panel
- L348 _public function_ `SLATE_BEGIN_ARGS(SColorThemesViewer)`
- L353 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L358 _public prototype_ `TSharedPtr<FColorTheme> GetCurrentColorTheme() const;` — Gets the current color theme
- L361 _public prototype_ `TSharedPtr<FColorTheme> GetRecents() const;` — Gets the recents color theme
- L364 _public prototype_ `void SetUseAlpha(const TAttribute<bool>& InUseAlpha);` — `UE_DEPRECATED(5.6, "SetUseAlpha is deprecated. Set the UseAlpha attribute of SThemeColorBlocksBar to control the opacity of theme colors.")`
- L367 _public prototype_ `static void LoadColorThemesFromIni();` — Load the color theme settings from the config
- L370 _public prototype_ `static void SaveColorThemesToIni();` — Save the color theme settings to the config
- L373 _public prototype_ `DECLARE_EVENT( SColorThemesViewer, FCurrentThemeChangedEvent );` — Callbacks to execute whenever we change the global current theme
- L374 _public function_ `FCurrentThemeChangedEvent& OnCurrentThemeChanged()`
- L380 _public member_ `static bool bSRGBEnabled;` — `UE_DEPRECATED(5.6, "bSRGBEnabled is deprecated. Set the UseSRGB attribute of SThemeColorBlocksBar to control the sRGB display of theme colors.")`
- L383 _public prototype_ `void MenuToStandardNoReturn();` — `UE_DEPRECATED(5.6, "MenuToStandardNoReturn is deprecated. SColorThemesViewer completely manages its own ToolsMenu.")`
- L386 _public prototype_ `bool IsRecentsThemeActive() const;` — Returns true if the currently chosen theme is the "Recents" theme
- L390 _private prototype_ `void BuildMenu(FMenuBuilder& MenuBuilder);` — Generate the content for the dropdown menu
- L393 _private prototype_ `void StartRename();` — Initiate a rename interaction
- L396 _private prototype_ `void StopRename();` — Terminate a rename interaction
- L399 _private prototype_ `void RefreshMenuWidget();` — Redraw the dropdown menu widget to update while keeping the menu open
- L401 _private prototype_ `void NewColorTheme();`
- L402 _private prototype_ `void DuplicateColorTheme();`
- L403 _private prototype_ `void DeleteColorTheme();`
- L406 _private prototype_ `void CommitThemeName(const FText& InText, ETextCommit::Type InCommitType);` — Rename theme if the user has pressed Enter in the RenameTextBox
- L407 _private prototype_ `void UpdateThemeNameFromTextBox();`
- L410 _private prototype_ `void SetCurrentColorTheme(TSharedPtr<FColorTheme> NewTheme);` — Sets the current color theme to the existing theme
- L413 _private prototype_ `void OnMenuOpenChanged(bool bIsOpen);` — Callback when the dropdown menu is opened/closed
- L415 _private prototype_ `const FSlateBrush* GetComboButtonImage() const;`
- L418 _private prototype_ `static TSharedPtr<FColorTheme> GetDefaultColorTheme(bool bCreateNew = false);` — Gets the default color theme, optionally creates it if not present
- L420 _private prototype_ `static TSharedPtr<FColorTheme> GetColorTheme(const FString& ThemeName);` — Gets the color theme, creates it if not present
- L422 _private prototype_ `static TSharedPtr<FColorTheme> IsColorTheme(const FString& ThemeName);` — Checks to see if this is a color theme, returns success
- L424 _private prototype_ `static FString MakeUniqueThemeName(const FString& ThemeName);` — Makes the passed theme name unique so it doesn't clash with pre-existing themes
- L426 _private prototype_ `static TSharedPtr<FColorTheme> NewColorTheme(const FString& ThemeName, const TArray< TSharedPtr<FColorInfo> >& ThemeColors = TArray< TSharedPtr<FColorInfo> >());` — Creates a new theme, ensuring the name is unique
- L430 _private member_ `TSharedPtr<SMultiBoxWidget> MultiBoxWidget;` — The MultiBox widget of the combo button
- L433 _private member_ `TSharedPtr<SEditableTextBox> RenameTextBox;` — The text box for renaming themes
- L436 _private member_ `FCurrentThemeChangedEvent CurrentThemeChangedEvent;` — Callbacks to execute whenever we change the global current theme
- L439 _private member_ `TAttribute<bool> bUseAlpha;` — Whether or not the color uses Alpha or not
- L442 _private member_ `static TArray<TSharedPtr<FColorTheme>> ColorThemes;` — A static holder of the color themes for the entire program
- L445 _private member_ `static TSharedPtr<FColorTheme> Recents;` — A static color theme comprised of the most recently accepted color values
- L448 _private member_ `static TWeakPtr<FColorTheme> CurrentlySelectedThemePtr;` — A static pointer to the color theme that is currently selected for the entire program

#### class `SThemeColorBlocksBar`  
`class SThemeColorBlocksBar : public SPanel`  
_L455-606_
- inherits: `SPanel`
- desc: A panel for displaying SColorBlocks in a FColorTheme
- L460 _public prototype_ `DECLARE_DELEGATE_RetVal(FLinearColor, FOnGetActiveColor);` — Delegate for hooking up to an inline editable text block 'IsSelected' check.
- L462 _public function_ `SLATE_BEGIN_ARGS(SThemeColorBlocksBar) : _OnSelectColor() , _OnGetActiveColor() , _UseSRGB() , _UseAlpha()`
- L473 _public prototype_ `SLATE_EVENT(FOnLinearColorValueChanged, OnSelectColor) SLATE_EVENT(FOnGetActiveColor, OnGetActiveColor) UE_DEPRECATED(5.6, "ShowTrashCallback is deprecated. Visibility of the delete button is managed by this widget internally.") SLATE_EVENT(FSimpleDelegate, ShowTrashCallback) UE_DEPRECATED(5.6, "HideTrashCallback is deprecated. Visibility of the delete button is managed by this widget internally.") SLATE_EVENT(FSimpleDelegate, HideTrashCallback) SLATE_ARGUMENT_DEPRECATED(FText, EmptyText, 5.6, "EmptyText is deprecated. This widget no longer displays any text when no themes have been created.") SLATE_ATTRIBUTE(bool, UseSRGB) SLATE_ATTRIBUTE(bool, UseAlpha) SLATE_END_ARGS() SThemeColorBlocksBar();` — Event called when a color block is clicked
- L497 _public prototype_ `void Construct(const FArguments& InArgs);`
- L500 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L501 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L502 _public prototype_ `virtual FChildren* GetChildren() override;`
- L503 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L504 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L505 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L506 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L514 _public prototype_ `void AddNewColorBlock(FLinearColor Color, int32 InsertPosition, bool bAllowRepeat = false);` — Adds a new color block to the Bar @param Color				The	color the new block will be @param InsertPosition	The location the block will be at
- L517 _public prototype_ `void AddToRecents(FLinearColor Color);` — Adds a new color block to the Recents color theme
- L520 _public prototype_ `bool IsRecentsThemeActive() const;` — Returns true if the currently selected theme is Recents
- L527 _public prototype_ `int32 RemoveColorBlock(TSharedPtr<FLinearColor> ColorToRemove);` — @param ColorToRemove		The pointer to the color that should be removed @return					The index of the removed color block, INDEX_NONE if it can't be found
- L530 _public prototype_ `void RemoveRefreshCallback();` — `UE_DEPRECATED(5.6, "RemoveRefreshCallback is deprecated. Color theme changes are handled by this widget internally")`
- L533 _public prototype_ `void AddRefreshCallback();` — `UE_DEPRECATED(5.6, "RemoveRefreshCallback is deprecated. Color theme changes are handled by this widget internally")`
- L538 _public prototype_ `void Refresh();` — Rebuilds the entire bar, regenerating all the constituent color blocks
- L541 _public prototype_ `void SetPlaceholderGrabOffset(FVector2D GrabOffset);` — `UE_DEPRECATED(5.6, "SetPlaceholderGrabOffset is deprecated. The Placeholder position is managed by this widget internally.")`
- L544 _public prototype_ `void ShowDeleteButton();` — Make the delete button visible and hide the add button
- L547 _public prototype_ `void HideDeleteButton();` — Hide the delete button and make the add button visible
- L551 _private prototype_ `FReply OnAddButtonClicked();` — Callback when the add button is clicked to add the current color picker color to the current theme
- L554 _private prototype_ `void OnThemeChanged();` — Callback when the user changes the currently selected theme, which prompts this widget to update the color blocks being displayed
- L557 _private prototype_ `EVisibility GetAddButtonVisibility() const;` — Get the visibility of the add button (which is hidden if the delete button is visible)
- L560 _private prototype_ `EVisibility GetDeleteButtonVisibility() const;` — Get the visibility of the delete button (which is hidden unless the user is dragging a color block)
- L563 _private member_ `TSlotlessChildren<SWidget> Children;` — The children blocks of this panel
- L566 _private member_ `TArray<TSharedPtr<SThemeColorBlock>> ColorBlocks;` — Array of color blocks belonging to the currently selected color theme
- L572 _private member_ `TSharedPtr<FColorTheme> ColorTheme;` — The Color Theme that this SThemeColorBlockBar is displaying. This is a TAttribute so it can re-get the theme when it changes rather than rely on a delegate to refresh it
- L575 _private member_ `FOnLinearColorValueChanged OnSelectColor;` — Event called when a color block is clicked
- L578 _private member_ `FOnGetActiveColor OnGetActiveColor;` — Event called to retrieve the current color from the color picker
- L581 _private member_ `FSimpleDelegate RefreshCallback;` — Callback to pass to the Color Theme. Holds a handle to this bar's Refresh method
- L584 _private member_ `FDelegateHandle RefreshCallbackHandle;` — Handle to the registered RefreshCallback delegate
- L587 _private member_ `TAttribute<bool> bUseSRGB;` — Whether to use display sRGB color
- L590 _private member_ `TAttribute<bool> bUseAlpha;` — Whether or not the color uses Alpha or not
- L593 _private member_ `bool bShowDeleteButton = false;` — Whether or not the delete button is currently visible
- L596 _private member_ `TSharedPtr<SBorder> DragShadow;` — Placeholder widget to show where a dropped color block will be added to the color theme
- L599 _private member_ `TSharedPtr<SOverlay> AddDeleteOverlay;` — Overlay widget that shows either the add button or the delete button
- L602 _private member_ `TSharedPtr<SColorThemesViewer> ThemesViewer;` — Custom combo button widget featuring a menu with the list of color themes and actions related to those themes
- L605 _private member_ `TOptional<int32> PlaceholderIndex;` — Index in the panel indicating where the drag shadow placeholder widget should be drawn

#### class `FColorDragDrop`  
`class FColorDragDrop : public FDragDropOperation`  
_L613-673_
- inherits: `FDragDropOperation`
- desc: This operation is a color which can be dragged and dropped between widgets. Represents a SThemeColorBlock that is dragged around, and can be dropped into a color trash.
- L617 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FColorDragDrop, FDragDropOperation) FColorDragDrop(FLinearColor InColor, bool bInUseSRGB, bool bInUseAlpha, FSimpleDelegate InTrashShowCallback, FSimpleDelegate InTrashHideCallback);`
- L622 _public prototype_ `virtual void OnDrop( bool bDropWasHandled, const FPointerEvent& MouseEvent ) override;`
- L623 _public prototype_ `virtual void OnDragged( const class FDragDropEvent& DragDropEvent ) override;`
- L624 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L628 _public prototype_ `void MarkForAdd();` — Makes the decorator window fully opaque to visually indicate that the color will be added when dropped
- L631 _public prototype_ `void MarkForDelete();` — Makes the decorator window slightly transparent to visually indicate that the color will be deleted when dropped
- L643 _public prototype_ `static TSharedRef<FColorDragDrop> New(FLinearColor InColor, bool bSRGB, bool bUseAlpha, FSimpleDelegate TrashShowCallback = FSimpleDelegate(), FSimpleDelegate TrashHideCallback = FSimpleDelegate(), TSharedPtr<SThemeColorBlocksBar> Origin = TSharedPtr<SThemeColorBlocksBar>(), int32 OriginPosition = 0);` — Makes a new FColorDragDrop to hold on to @param InColor			The color to be dragged and dropped @param bSRGB				Whether the color is sRGB @param bUseAlpha			Whether the colors alpha is important @param TrashShowCallback	Called when this operation is created @param TrashHideCallback Called when this operation is dropped @param Origin			The SThemeColorBlockBar that this operation is from @param OriginPosition	The position in it's origin that it is from
- L648 _public member_ `FLinearColor Color;` — The color currently held onto by this drag drop operation
- L651 _public member_ `bool bUseSRGB;` — Whether or not the color uses sRGB
- L654 _public member_ `bool bUseAlpha;` — Whether or not the color uses Alpha
- L657 _public member_ `TWeakPtr<SThemeColorBlocksBar> OriginBar;` — `UE_DEPRECATED(5.6, "OriginBar is deprecated. This operation no longer needs direct access to the SThemeColorBlocksBar widget.")`
- L660 _public member_ `int32 OriginBarPosition;` — `UE_DEPRECATED(5.6, "OriginBarPosition is deprecated. This operation no longer needs to know its position in the SThemeColorBlocksBar widget.")`
- L663 _public member_ `FSimpleDelegate ShowTrash;` — Callback to show the delete button of the SThemeColorBlocksBar when this is dropped
- L666 _public member_ `FSimpleDelegate HideTrash;` — Callback to hide the delete button of the SThemeColorBlocksBar when this is dropped
- L669 _public member_ `bool bSetForDeletion;` — `UE_DEPRECATED(5.6, "bSetForDeletion is deprecated. This operation no longer deletes any color blocks from the SThemeColorBlocksBar widget.")`
- L672 _public member_ `FVector2D BlockSize;` — `UE_DEPRECATED(5.6, "BlockSize is deprecated. This operation now uses the size of the cursor decorator window internally.")`

#### Free symbols / members of external scopes

- L78 _delegate_ `DECLARE_EVENT( FColorTheme, FRefreshEvent );`
- L264 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCurrentThemeChanged, TSharedPtr<FColorTheme>) class UE_DEPRECATED(5.6, "SColorThemeBar is deprecated. SColorThemesViewer now displays a standard menu with a list of available themes.") SColorThemeBar : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SColorThemeBar) : _ColorTheme() , _OnCurrentThemeChanged() , _ShowTrashCallback() , _HideTrashCallback() , _UseSRGB() , _UseAlpha() { } SLATE_ATTRIBUTE(TSharedPtr<FColorTheme>, ColorTheme) SLATE_EVENT(FOnCurrentThemeChanged, OnCurrentThemeChanged) SLATE_EVENT(FSimpleDelegate, ShowTrashCallback) SLATE_EVENT(FSimpleDelegate, HideTrashCallback) SLATE_ATTRIBUTE(bool, UseSRGB) SLATE_ATTRIBUTE(bool, UseAlpha) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L373 _delegate_ `DECLARE_EVENT( SColorThemesViewer, FCurrentThemeChangedEvent );` — Callbacks to execute whenever we change the global current theme
- L460 _delegate_ `DECLARE_DELEGATE_RetVal(FLinearColor, FOnGetActiveColor);` — Delegate for hooking up to an inline editable text block 'IsSelected' check.

### `Source/Runtime/AppFramework/Public/Widgets/Testing/SPerfSuite.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `void SummonPerfTestSuite();`

### `Source/Runtime/AppFramework/Public/Widgets/Testing/SStarshipSuite.h` (Public)


#### Free symbols / members of external scopes

- L10 _externvar_ `extern const FLazyName StarshipGalleryTabName;`
- L11 _prototype_ `void RegisterStarshipGalleryTabSpawner();`
- L12 _prototype_ `void UnregisterStarshipGalleryTabSpawner();`
- L13 _prototype_ `void RestoreStarshipSuite();`

### `Source/Runtime/AppFramework/Public/Widgets/Testing/STestSuite.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `void RestoreSlateTestSuite();`
- L10 _prototype_ `void MakeSplitterTest();`

### `Source/Runtime/AppFramework/Public/Widgets/Views/SMultipleOptionTable.h` (Public)


#### class `SOptionTableRow`  
`template<typename OptionType> class SOptionTableRow : public SMultiColumnTableRow< TSharedPtr<OptionType> >`  
_L31-106_
- inherits: `SMultiColumnTableRow<TSharedPtr<OptionType>>`
- desc: Implements a row widget for an option list.
- L35 _public typedef_ `typedef typename TSlateDelegates< OptionType >::FOnGenerateWidget FOnGenerateWidget;`
- L36 _public typedef_ `typedef typename STableRow< TSharedPtr<OptionType> >::FArguments FOptionTableRowArgs;`
- L38 _public function_ `SLATE_BEGIN_ARGS(SOptionTableRow)`
- L53 _public function_ `void Construct( const FArguments& InArgs)` — Constructs the widget. @param InArgs The construction arguments.
- L70 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override` — Generates the widget for the specified column. @param ColumnName The name of the column to generate the widget for. @return The widget.
- L87 _private function_ `void HandleCheckBoxCheckStateChanged( ECheckBoxState NewState )` — Callback for changing the checked state of the check box.
- L93 _private function_ `ECheckBoxState HandleCheckBoxIsChecked( ) const` — Callback for determining the checked state of the check box.
- L99 _public member_ `TSharedPtr<SCheckBox> CheckBox;`
- L102 _private member_ `OptionType Option;`
- L103 _private member_ `FOnCheckStateChanged OnCheckStateChanged;`
- L104 _private member_ `TAttribute<ECheckBoxState> IsChecked;`
- L105 _private member_ `FOnGenerateWidget OnGenerateWidget;`

#### class `SMultipleOptionTable`  
`template<typename OptionType> class SMultipleOptionTable : public SCompoundWidget`  
_L109-170_
- inherits: `SCompoundWidget`
- L112 _public typedef_ `typedef typename TSlateDelegates< OptionType >::FOnGenerateWidget FOnGenerateOptionWidget;`
- L115 _public prototype_ `DECLARE_DELEGATE(FOnPreBatchSelect);` — This callback will be used before selecting or deselecting all of the options. May be of use for optimization.
- L118 _public prototype_ `DECLARE_DELEGATE(FOnPostBatchSelect);` — This callback will be used after selecting or deselecting all of the options. May be of use for optimization.
- L120 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnOptionSelectionChanged, bool, OptionType);`
- L121 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsOptionSelected, OptionType);`
- L123 _public function_ `SLATE_BEGIN_ARGS( SMultipleOptionTable<OptionType> )`
- L133 _public prototype_ `void Construct(const FArguments& InArgs, const TArray< OptionType >* const InOptions);`
- L136 _public prototype_ `void RequestTableRefresh();` — Refreshes the list view. Useful if the options array is modified.
- L140 _private prototype_ `TSharedRef<class ITableRow> HandleOptionListViewGenerateRow(OptionType Option, const TSharedRef< class STableViewBase >& OwnerTableView);` — Generates the special row widget for this list view widget.
- L143 _private prototype_ `TSharedRef<SWidget> GenerateWidgetForOption(OptionType Option);` — Calls the provided user callback to generate a widget to display the specified option.
- L146 _private prototype_ `void HandleCheckBoxCheckStateChanged(ECheckBoxState NewState, OptionType Option) const;` — Calls the provided user callback to notify them that an option has been checked or unchecked.
- L149 _private prototype_ `ECheckBoxState HandleCheckBoxIsChecked(OptionType Option) const;` — Calls the provided user callback to be notified that an option is selected or unselected in some way.
- L152 _private prototype_ `void HandleAllHyperlinkNavigate();` — Selects all options.
- L155 _private prototype_ `void HandleNoneHyperlinkNavigate();` — Deselects all options.
- L158 _private prototype_ `EVisibility HandleHyperlinkVisibility() const;` — Collapses hyperlinks for selecting/deselecting all options based on whether there are multiple options.
- L161 _private member_ `const TArray< OptionType >* Options;`
- L162 _private member_ `FOnPreBatchSelect OnPreBatchSelect;`
- L163 _private member_ `FOnPostBatchSelect OnPostBatchSelect;`
- L164 _private member_ `FOnGenerateOptionWidget OnGenerateOptionWidget;`
- L165 _private member_ `FOnOptionSelectionChanged OnOptionSelectionChanged;`
- L166 _private member_ `FIsOptionSelected IsOptionSelected;`
- L167 _private member_ `TAttribute<FOptionalSize> ListHeight;`
- L169 _private member_ `TSharedPtr< SListView< OptionType > > OptionListView;`
- L173 _function_ `template<typename OptionType> void SMultipleOptionTable<OptionType>::Construct(const FArguments& InArgs, const TArray< OptionType >* const InOptions)`
- L259 _function_ `template<typename OptionType> void SMultipleOptionTable<OptionType>::RequestTableRefresh()`
- L265 _function_ `template<typename OptionType> TSharedRef<class ITableRow> SMultipleOptionTable<OptionType>::HandleOptionListViewGenerateRow(OptionType Option, const TSharedRef< class STableViewBase >& OwnerTableView)`
- L276 _function_ `template<typename OptionType> TSharedRef<SWidget> SMultipleOptionTable<OptionType>::GenerateWidgetForOption(OptionType Option)`
- L282 _function_ `template<typename OptionType> void SMultipleOptionTable<OptionType>::HandleCheckBoxCheckStateChanged(ECheckBoxState NewState, OptionType Option) const`
- L288 _function_ `template<typename OptionType> ECheckBoxState SMultipleOptionTable<OptionType>::HandleCheckBoxIsChecked(OptionType Option) const`
- L294 _function_ `template<typename OptionType> void SMultipleOptionTable<OptionType>::HandleAllHyperlinkNavigate()`
- L305 _function_ `template<typename OptionType> void SMultipleOptionTable<OptionType>::HandleNoneHyperlinkNavigate()`
- L316 _function_ `template<typename OptionType> EVisibility SMultipleOptionTable<OptionType>::HandleHyperlinkVisibility() const`

#### Free symbols / members of external scopes

- L25 _macro_ `#define LOCTEXT_NAMESPACE "SMultipleOptionTable"`
- L115 _delegate_ `DECLARE_DELEGATE(FOnPreBatchSelect);` — This callback will be used before selecting or deselecting all of the options. May be of use for optimization.
- L118 _delegate_ `DECLARE_DELEGATE(FOnPostBatchSelect);` — This callback will be used after selecting or deselecting all of the options. May be of use for optimization.
- L120 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnOptionSelectionChanged, bool, OptionType);`
- L121 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsOptionSelected, OptionType);`

### `Source/Runtime/AppFramework/Public/Widgets/Workflow/SWizard.h` (Public)


#### class `SWizard`  
`class SWizard : public SCompoundWidget`  
_L33-430_
- inherits: `SCompoundWidget`
- desc: Implements a wizard widget.
- L168 _public function_ `SLATE_BEGIN_ARGS(SWizard) : _ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("Button")) , _CancelButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("Button")) , _FinishButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton")) , _ButtonTextStyle(&FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("DialogButtonText")) , _CanFinish(true) , _FinishButtonText(NSLOCTEXT("SWizard", "DefaultFinishButtonText", "Finish")) , _FinishButtonToolTip(NSLOCTEXT("SWizard", "DefaultFinishButtonTooltip", "Finish the wizard")) , _InitialPageIndex(0) , _DesiredSize(FVector2D(0, 0)) , _ShowPageList(true) , _ShowCancelButton(true) , _ShowBreadcrumbs(false) , _BreadcrumbButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FButtonStyle >("BreadcrumbButton")) , _BreadcrumbTextStyle(&FCoreStyle::Get().GetWidgetStyle< FTextBlockStyle >("NormalText")) , _ShowHistoryButtons(true) , _ShowPageTitle(false) , _PageTitleTextStyle(&FCoreStyle::Get().GetWidgetStyle< FTextBlockStyle >("Wizard.PageTitle")) , _PageFooter()`
- L192 _public prototype_ `SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, CancelButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, FinishButtonStyle) SLATE_STYLE_ARGUMENT(FTextBlockStyle, ButtonTextStyle) SLATE_ATTRIBUTE(bool, CanFinish) SLATE_ATTRIBUTE(FText, FinishButtonText) SLATE_ATTRIBUTE(FText, FinishButtonToolTip) SLATE_ATTRIBUTE(int32, InitialPageIndex) SLATE_ATTRIBUTE(FVector2D, DesiredSize) SLATE_EVENT(FSimpleDelegate, OnCanceled) SLATE_EVENT(FSimpleDelegate, OnFinished) SLATE_EVENT(FOnClicked, OnFirstPageBackClicked)` — The button style used by next and back.
- L255 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, BreadcrumbTextStyle);` — The text style to use for breadcrumbs if ShowBreadcrumbs is set to true.
- L258 _public prototype_ `SLATE_ARGUMENT(bool, ShowHistoryButtons) SLATE_ARGUMENT(bool, ShowPageTitle) SLATE_STYLE_ARGUMENT(FTextBlockStyle, PageTitleTextStyle);` — Holds a flag indicating whether the previous and next buttons can be shown (default = true)
- L279 _public prototype_ `bool CanShowPage( int32 PageIndex ) const;` — Checks whether the page with the specified index can be shown. @param PageIndex The index of the page to check. @return true if the page can be shown, false otherwise.
- L286 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget. @param InArgs The declaration data for this widget.
- L293 _public prototype_ `int32 GetNumPages() const;` — Gets the number of pages that this wizard contains. @return The number of pages.
- L299 _public prototype_ `int32 GetCurrentPageIndex() const;` — Get the index of the current page. @return The index of the current page.
- L307 _public prototype_ `int32 GetPageIndex( const TSharedPtr<SWidget>& PageWidget ) const;` — Gets the index of the specified wizard page widget. @param PageWidget The page widget to get the index for. @return The index of the page, or INDEX_NONE if not found.
- L314 _public prototype_ `void ShowPage( int32 PageIndex );` — Attempts to show the page with the specified index. @param PageIndex The index of the page to show.
- L317 _public prototype_ `void AdvanceToPage( int32 PageIndex );` — Shows the page with the specified index, but preserves page history.
- L320 _public prototype_ `TSharedPtr<SWidget> GetWidgetToFocusOnActivate();` — Get the widget to focus on activation
- L326 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L336 _public function_ `static FWizardPage::FArguments Page()` — Returns a new slot for a page. @param PageName The name of the page. @return A new slot.
- L345 _private prototype_ `FReply HandleCancelButtonClicked();` — Callback for clicking the 'Cancel' button.
- L348 _private prototype_ `FReply HandleFinishButtonClicked();` — Callback for clicking the 'Launch' button.
- L351 _private prototype_ `FReply HandleNextButtonClicked();` — Callback for clicking the 'Next' button.
- L354 _private prototype_ `bool HandleNextButtonIsEnabled() const;` — Callback for getting the enabled state of the 'Next' button.
- L357 _private prototype_ `EVisibility HandleNextButtonVisibility() const;` — Callback for getting the visibility of the 'Next' button.
- L360 _private prototype_ `void HandlePageButtonCheckStateChanged( ECheckBoxState NewState, int32 PageIndex );` — Callback for getting the checked state of a page button.
- L363 _private prototype_ `ECheckBoxState HandlePageButtonIsChecked( int32 PageIndex ) const;` — Callback for clicking a page button.
- L366 _private prototype_ `bool HandlePageButtonIsEnabled( int32 PageIndex ) const;` — Callback for getting the enabled state of a page button.
- L369 _private prototype_ `FReply HandlePrevButtonClicked();` — Callback for clicking the 'Previous' button.
- L372 _private prototype_ `bool HandlePrevButtonIsEnabled() const;` — Callback for getting the enabled state of the 'Previous' button.
- L375 _private prototype_ `EVisibility HandlePrevButtonVisibility() const;` — Callback for getting the visibility of the 'Previous' button.
- L378 _private prototype_ `void HandleBreadcrumbClicked(const int32& PageIndex);` — Callback for when a breadcrumb is clicked.
- L381 _private prototype_ `int32 GetNextPageIndex() const;` — Get the next page index to display.
- L384 _private prototype_ `int32 GetPrevPageIndex() const;` — Get the previous page index to display.
- L387 _private prototype_ `FText HandleGetPageTitle() const;` — Get the page title to display for the current page.
- L392 _private member_ `FVector2D DesiredSize;` — Holds the wizard's desired size.
- L395 _private member_ `TIndirectArray<FWizardPage> Pages;` — Holds the collection of wizard pages.
- L398 _private member_ `TSharedPtr<SWidgetSwitcher> WidgetSwitcher;` — Holds the widget switcher.
- L401 _private member_ `TSharedPtr<SBreadcrumbTrail<int32>> BreadcrumbTrail;` — Holds the breadcrumb trail.
- L404 _private member_ `bool bShowHistoryButtons;` — Whether to show the "Previous" and "Next" buttons
- L406 _private member_ `TSharedPtr<SWidget> FinishButton;`
- L411 _private member_ `FSimpleDelegate OnCanceled;` — Holds a delegate to be invoked when the 'Cancel' button has been clicked.
- L414 _private member_ `FSimpleDelegate OnFinished;` — Holds a delegate to be invoked when the 'Finish' button has been clicked.
- L417 _private member_ `FOnClicked OnNextClicked;` — Holds a delegate to be invoked when the 'Next' button has been clicked.
- L420 _private member_ `FOnClicked OnPrevClicked;` — Holds a delegate to be invoked when the 'Previous' button has been clicked.
- L423 _private member_ `FOnClicked OnFirstPageBackClicked;` — Holds a delegate to be invoked when the 'Previous' button has been clicked on the first page.
- L426 _private member_ `FOnGetPageIndex OnGetNextPageIndex;` — Exposes a delegate to be invoked to control whether the 'Next' button is enabled, and where to attempt to move to if it is clicked.
- L429 _private member_ `FOnGetPageIndex OnTryToMoveToPage;` — Exposes a delegate to be invoked when the wizard's 'Next' button is clicked to allow redirection to another page if processing fails

#### class `SWizard::FWizardPage`  
`class FWizardPage`  
_L41-164_
- desc: Implements a wizard page.
- L45 _public function_ `SLATE_BEGIN_ARGS(FWizardPage) : _ButtonContent() , _CanShow(true) , _PageContent()`
- L78 _public function_ `FWizardPage( const FArguments& InArgs ) : ButtonContent(InArgs._ButtonContent) , Showable(InArgs._CanShow) , OnEnterDelegate(InArgs._OnEnter) , OnLeaveDelegate(InArgs._OnLeave) , PageContent(InArgs._PageContent) , Name(InArgs._Name)` — Creates and initializes a new instance. @param InArgs The arguments for the page.
- L94 _public function_ `bool CanShow() const` — Checks whether the page can be shown. @return true if the page can be shown, false otherwise.
- L100 _public function_ `FText GetName() const` — Gets the display name of the page.
- L110 _public function_ `const TSharedRef<SWidget>& GetButtonContent() const` — Gets the button content. @return The button content widget.
- L120 _public function_ `const TSharedRef<SWidget>& GetPageContent() const` — Gets the page content. @return The page contents.
- L130 _public function_ `FSimpleDelegate& OnEnter()` — Gets a delegate to be invoked when this page is being entered. @return The delegate.
- L140 _public function_ `FSimpleDelegate& OnLeave()` — Gets a delegate to be invoked when this page is being left. @return The delegate.
- L148 _private member_ `TAlwaysValidWidget ButtonContent;` — Holds the button content.
- L151 _private member_ `TAttribute<bool> Showable;` — Holds a flag indicating whether this page can be activated.
- L154 _private member_ `FSimpleDelegate OnEnterDelegate;` — Holds a delegate to be invoked when the page is activated.
- L157 _private member_ `FSimpleDelegate OnLeaveDelegate;` — Holds a delegate to be invoked when the page is deactivated.
- L160 _private member_ `TAlwaysValidWidget PageContent;` — Holds the page content.
- L163 _private member_ `TAttribute<FText> Name;` — Holds the name of the page.

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FOnGetPageIndex, int32) class SWizard : public SCompoundWidget { public: class FWizardPage { public: SLATE_BEGIN_ARGS(FWizardPage) : _ButtonContent() , _CanShow(true) , _PageContent() { } SLATE_NAMED_SLOT(FArguments, ButtonContent) SLATE_ATTRIBUTE(FText, Name) SLATE_ATTRIBUTE(bool, CanShow) SLATE_EVENT(FSimpleDelegate, OnEnter) SLATE_EVENT(FSimpleDelegate, OnLeave) SLATE_DEFAULT_SLOT(FArguments, PageContent)` — Delegate type for getting the next page to show. The parameter is the current page index. The return value should be the next page index.
