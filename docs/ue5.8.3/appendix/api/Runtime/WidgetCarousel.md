# Runtime / WidgetCarousel

- module root: `Source/Runtime/WidgetCarousel`
- headers: 6; symbols: 183
- symbol kinds: class=7, delegate=4, enum=2, enumerator=5, function=72, macro=2, member=60, namespace=1, prototype=25, struct=3, typedef=2
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Slate, SlateCore

### `Source/Runtime/WidgetCarousel/Public/SCarouselNavigationBar.h` (Public)


#### class `SCarouselNavigationBar`  
`class SCarouselNavigationBar : public SCompoundWidget`  
_L19-69_
- inherits: `SCompoundWidget`
- desc: A horizontal bar of buttons for navigating to a specific item in the widget carousel.
- L24 _public function_ `SLATE_BEGIN_ARGS(SCarouselNavigationBar) : _Style() , _OnSelectedIndexChanged() , _ItemCount(0) , _CurrentItemIndex(0) , _CurrentSlideAmount(0.0f)`
- L33 _public prototype_ `SLATE_STYLE_ARGUMENT(FWidgetCarouselNavigationBarStyle, Style) SLATE_EVENT(FOnSelectedIndexChanged, OnSelectedIndexChanged) SLATE_ARGUMENT(int32, ItemCount) SLATE_ATTRIBUTE(int32, CurrentItemIndex) SLATE_ATTRIBUTE(float, CurrentSlideAmount) SLATE_END_ARGS() int32 GetItemCount();`
- L51 _public prototype_ `void SetItemCount(int32 InItemCount);`
- L53 _public prototype_ `void Construct(const FArguments& InArgs);`
- L56 _private prototype_ `void BuildScrollBar();`
- L58 _private prototype_ `FReply HandleItemButtonClicked(int32 ItemIndex);`
- L60 _private prototype_ `FVector2D GetPlaceHolderPosition() const;`
- L63 _private member_ `const FWidgetCarouselNavigationBarStyle* Style;`
- L64 _private member_ `TSharedPtr<SHorizontalBox> WidgetScrollBox;`
- L65 _private member_ `FOnSelectedIndexChanged OnSelectedIndexChanged;`
- L66 _private member_ `int32 ItemCount;`
- L67 _private member_ `TAttribute<int32> CurrentItemIndex;`
- L68 _private member_ `TAttribute<float> CurrentSlideAmount;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "WidgetCarousel"`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectedIndexChanged, int32) public: SLATE_BEGIN_ARGS(SCarouselNavigationBar) : _Style() , _OnSelectedIndexChanged() , _ItemCount(0) , _CurrentItemIndex(0) , _CurrentSlideAmount(0.0f) {} SLATE_STYLE_ARGUMENT(FWidgetCarouselNavigationBarStyle, Style) SLATE_EVENT(FOnSelectedIndexChanged, OnSelectedIndexChanged) SLATE_ARGUMENT(int32, ItemCount) SLATE_ATTRIBUTE(int32, CurrentItemIndex) SLATE_ATTRIBUTE(float, CurrentSlideAmount) SLATE_END_ARGS() int32 GetItemCount();`

### `Source/Runtime/WidgetCarousel/Public/SCarouselNavigationButton.h` (Public)


#### class `SCarouselNavigationButton`  
`class SCarouselNavigationButton : public SCompoundWidget`  
_L27-269_
- inherits: `SCompoundWidget`
- desc: A widget used to navigate the carousel widget
- L112 _public function_ `SLATE_BEGIN_ARGS(SCarouselNavigationButton) : _Style()`
- L116 _public function_ `SLATE_STYLE_ARGUMENT(FWidgetCarouselNavigationButtonStyle, Style) SLATE_EVENT(FOnClicked, OnClicked) SLATE_ARGUMENT(ENavigationButtonDirection, Direction) SLATE_EVENT(FOnBeginPeek, OnBeginPeek) SLATE_EVENT(FOnEndPeek, OnEndPeek) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L196 _private function_ `FSlateColor GetButtonColor() const`
- L215 _private function_ `FSlateColor GetButtonImageColor() const`
- L230 _private function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`
- L263 _private member_ `const FWidgetCarouselNavigationButtonStyle* Style;`
- L264 _private member_ `TSharedPtr<SButton> HiddenButton;`
- L265 _private member_ `TSharedPtr<SButton> VisibleButton;`
- L267 _private member_ `float ImageTransparency;`
- L268 _private member_ `ENavigationButtonDirection Direction;`

#### class `SCarouselNavigationButton::SPeekBorder`  
`class SPeekBorder : public SBorder`  
_L35-102_
- inherits: `SBorder`
- L40 _public function_ `SLATE_BEGIN_ARGS(SPeekBorder) : _OnBeginPeek() , _OnEndPeek() , _HAlign(HAlign_Fill) , _VAlign(VAlign_Fill) , _Padding(FMargin(0))`
- L48 _public function_ `SLATE_EVENT(FOnBeginPeek, OnBeginPeek) SLATE_EVENT(FOnEndPeek, OnEndPeek) SLATE_ARGUMENT(EHorizontalAlignment, HAlign) SLATE_ARGUMENT(EVerticalAlignment, VAlign) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs)` — Called when the button is hovered
- L74 _public function_ `void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L86 _public function_ `void OnMouseLeave(const FPointerEvent& MouseEvent)`
- L100 _private member_ `FOnBeginPeek OnBeginPeek;`
- L101 _private member_ `FOnEndPeek OnEndPeek;`

#### enum `SCarouselNavigationButton::ENavigationButtonDirection`  
`enum class ENavigationButtonDirection`  
_L106-110_
- L108 _public enumerator_ `Left`
- L109 _public enumerator_ `Right`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "WidgetCarousel"`
- L30 _delegate_ `DECLARE_DELEGATE(FOnBeginPeek) DECLARE_DELEGATE(FOnEndPeek) public: class SPeekBorder : public SBorder { public: SLATE_BEGIN_ARGS(SPeekBorder) : _OnBeginPeek() , _OnEndPeek() , _HAlign(HAlign_Fill) , _VAlign(VAlign_Fill) , _Padding(FMargin(0)) {} SLATE_EVENT(FOnBeginPeek, OnBeginPeek) SLATE_EVENT(FOnEndPeek, OnEndPeek) SLATE_ARGUMENT(EHorizontalAlignment, HAlign) SLATE_ARGUMENT(EVerticalAlignment, VAlign) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { OnBeginPeek = InArgs._OnBeginPeek; OnEndPeek = InArgs._OnEndPeek; SBorder::Construct(SBorder::FArguments() .HAlign(InArgs._HAlign) .VAlign(InArgs._VAlign) .Padding(InArgs._Padding) .BorderImage(FStyleDefaults::GetNoBrush()) [`
- L31 _delegate_ `DECLARE_DELEGATE(FOnEndPeek) public: class SPeekBorder : public SBorder { public: SLATE_BEGIN_ARGS(SPeekBorder) : _OnBeginPeek() , _OnEndPeek() , _HAlign(HAlign_Fill) , _VAlign(VAlign_Fill) , _Padding(FMargin(0)) {} SLATE_EVENT(FOnBeginPeek, OnBeginPeek) SLATE_EVENT(FOnEndPeek, OnEndPeek) SLATE_ARGUMENT(EHorizontalAlignment, HAlign) SLATE_ARGUMENT(EVerticalAlignment, VAlign) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { OnBeginPeek = InArgs._OnBeginPeek; OnEndPeek = InArgs._OnEndPeek; SBorder::Construct(SBorder::FArguments() .HAlign(InArgs._HAlign) .VAlign(InArgs._VAlign) .Padding(InArgs._Padding) .BorderImage(FStyleDefaults::GetNoBrush()) [ InArgs._Content.Widget`

### `Source/Runtime/WidgetCarousel/Public/SWidgetCarousel.h` (Public)


#### enum `EWidgetCarouselScrollDirection::Type`  
`enum Type`  
_L23-31_
- L26 _public enumerator_ `Carousel_Left` — Scroll the carousel left.
- L28 _public enumerator_ `Carousel_Right` — Scroll the carousel right.
- L30 _public enumerator_ `Carousel_Center` — Center the carousel

#### struct `FCarouselDisplayItem`  
`struct FCarouselDisplayItem : public TSharedFromThis<FCarouselDisplayItem>`  
_L35-415_
- inherits: `TSharedFromThis<FCarouselDisplayItem>`
- desc: The Carousel display widget that gets animated by the carousel widget
- L40 _public function_ `FCarouselDisplayItem() : OpacityValue( 0.f ) , SlideValue( 0.f ) , DesiredOpacityValue( 0.f ) , SlideValueLeftLimit( -1.0f ) , SlideValueRightLimit( 1.0f ) , PeakValueLeftLimit(-0.05f) , PeakValueRightLimit(0.05f) , OptimalSlideValue( 0.0f ) , DesiredSlideValue( 0.f ) , bTransition( false ) , bPeak(false) , bFade( false ) , MoveSpeed( 5.0f ) , PeakSpeed(.2f) , PeakDistance(0.05f) , FadeRate( 2.0f ) , Visibility(EVisibility::Visible)` — Construct the display widget.
- L71 _public function_ `void ScrollIn( EWidgetCarouselScrollDirection::Type ScrollDirection )` — Scroll in the widget. @ScrollDirection The scroll direction.
- L84 _public function_ `void PeakIn(EWidgetCarouselScrollDirection::Type ScrollDirection)` — Scroll out the widget. @param ScrollDirection - The scroll direction.
- L118 _public function_ `void Tick( float DeltaTime )` — Tick the widget - animate the slide / fade. @param DeltaTime - The delta time.
- L146 _public function_ `bool BlendWidget( const float& DeltaTime, const float& DesiredValue, const float& Speed, float& OutCurrentValue )` — Blend the widget fade / transform to the desired value. @param DeltaTime - The delta time. @param DesiredValue - The desired value. @param Speed - Speed to transform. @param OutCurrentValue - The value to set. @return True if still blending, false otherwise
- L187 _public function_ `void SetWidgetContent( TSharedRef<SWidget> InContent )` — Set the content of the widget to display. @param InContent - The widget to display.
- L213 _public function_ `TSharedRef<SWidget> GetWidgetContent() const`
- L236 _public function_ `TSharedPtr< SFxWidget > GetSFXWidget()` — Get the FX widget to display. @return The FX widget.
- L245 _public function_ `void SetOpacity( float InOpacity )` — Get the widget opacity. @param InOpacity - the desired opacity.
- L251 _public function_ `void SetVisibility(EVisibility InVisibility)`
- L262 _public function_ `void SetSlide( float InSlide, bool bClearTransition = false)` — Set the slide position. @param InSlide - the desired slide position. @param bClearTransition - Clear any transitions.
- L278 _public function_ `void SetMoveSpeed( float DesiredMoveSpeed )` — Set the desired move speed. @param DesiredMoveSpeed - the desired move speed.
- L287 _public function_ `void SetSliderLeftLimit( float DesiredLeftLimit )` — Set the desired left limit. The widget will go to this position when scrolling out and left. @param DesiredLeftLimit - the desired left limit.
- L296 _public function_ `void SetSliderRightLimit( float DesiredRightLimit )` — Set the desired right limit. The widget will go to this position when scrolling out and right. @param DesiredRightLimit - the desired right limit.
- L301 _public function_ `void SetSliderPeakLeftLimit(float DesiredLimit)`
- L306 _public function_ `void SetSliderPeakRightLimit(float DesiredLimit)`
- L315 _public function_ `void SetSliderOptimalPostion( float DesiredOptimalSlideValue )` — Set the optimal slide position. The widget will go to this position when in view. @param DesiredOptimalSlideValue - the desired optimal position.
- L324 _public function_ `void SetFadeRate( float DesiredFadeRate )` — Set the fade rate. The widget fade in and out at this amount per frame. @param DesiredFadeRate - the desired fade value.
- L329 _public function_ `bool IsInTransition()`
- L334 _public function_ `const float GetSlideValue() const`
- L339 _public function_ `const float GetMoveSpeed() const`
- L350 _protected function_ `FVector2D GetSlide() const` — Get the slide position - used by the FX widget to get its position. @return The slide position.
- L357 _protected member_ `float OpacityValue;` — Holds the Opacity Value. 0 == transparent
- L360 _protected member_ `float SlideValue;` — The slide position
- L363 _protected member_ `float DesiredOpacityValue;` — The desired opacity value
- L366 _protected member_ `float SlideValueLeftLimit;` — The max left position
- L369 _protected member_ `float SlideValueRightLimit;` — The max right position
- L372 _protected member_ `float PeakValueLeftLimit;` — The left peak position
- L375 _protected member_ `float PeakValueRightLimit;` — The right peak position
- L378 _protected member_ `float OptimalSlideValue;` — The slide value to display the widget on screen
- L381 _protected member_ `float DesiredSlideValue;` — The desired slide value
- L384 _protected member_ `bool bTransition;` — Holds if widget is in transition
- L387 _protected member_ `bool bPeak;` — Hold if the widget is peaking
- L390 _protected member_ `bool bFade;` — Holds if the widget is fading in or out
- L393 _protected member_ `bool bFadeInAndOut;` — Holds if the widget should fade in or out
- L396 _protected member_ `float MoveSpeed;` — The maximum move speed of the widget
- L399 _protected member_ `float PeakSpeed;` — The Peak speed
- L402 _protected member_ `float PeakDistance;` — The Peak Distance
- L405 _protected member_ `float FadeRate;` — The amount by which a widget fades per frame
- L408 _protected member_ `TSharedPtr< SFxWidget > FXWidget;` — Holds the FX widget that does the transitioning
- L411 _protected member_ `FCurveSequence SlideInCurve;` — Holds the peak curve
- L414 _protected member_ `EVisibility Visibility;` — The current visibility of the display item

#### class `SWidgetCarousel`  
`template <typename ItemType> class SWidgetCarousel : public SCompoundWidget`  
_L423-842_
- inherits: `SCompoundWidget`
- desc: Implements a widget Carousel. A widget Carousel displays widgets that can be scrolled in and out.
- L428 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCarouselPageChanged, int32 );`
- L429 _public typedef_ `typedef typename TSlateDelegates< ItemType >::FOnGenerateWidget FOnGenerateWidget;`
- L431 _public function_ `SLATE_BEGIN_ARGS(SWidgetCarousel<ItemType>) : _WidgetItemsSource( static_cast<const TArray<ItemType>*>(NULL) ) , _MoveSpeed( 1.f ) , _SlideValueLeftLimit( -1.f ) , _SlideValueRightLimit( 1.f ) , _PeakValueLeftLimit(-0.05f) , _PeakValueRightLimit(0.05f) , _FadeRate( 1.0f )`
- L468 _public function_ `void Construct( const FArguments& InArgs )` — Constructs the widget.
- L513 _public function_ `void GenerateCurrentWidgets()`
- L555 _public function_ `int32 GetWidgetIndex()` — Get the current widget index. @return The visible widget index
- L565 _public function_ `void SetActiveWidgetIndex(int32 Index)` — Sets the active widget to display at the specified index. @param Index - The desired widget index.
- L584 _public function_ `void SetNextWidget()` — Scroll right.
- L595 _public function_ `void SetPreviousWidget()` — Scroll left.
- L603 _public function_ `void Peak(EWidgetCarouselScrollDirection::Type Direction)`
- L617 _public function_ `void SetItemSource( const TArray<ItemType>* InWidgetItemsSource )` — Set the item source, and scroll to the first item. @param The item source
- L626 _public function_ `float GetPrimarySlide()`
- L631 _public function_ `void SetMoveSpeed(float InMoveSpeed)`
- L641 _public function_ `float GetMoveSpeed() const`
- L646 _public function_ `void ResetTransition()`
- L659 _protected function_ `void GenerateWidgets( )` — Regenerate the widgets to display them.
- L683 _protected function_ `void SwapBuffer(EWidgetCarouselScrollDirection::Type ScrollDirection, int32 OverrideWidgetIndex = INDEX_NONE)` — Swap the buffer index.
- L747 _protected function_ `void SetSliderLimits()`
- L768 _protected function_ `int32 GetLeftWidgetIndex(int32 Index)`
- L778 _protected function_ `int32 GetRightWidgetIndex(int32 Index)`
- L788 _protected function_ `bool IsInTransition()`
- L793 _protected function_ `EActiveTimerReturnType RegisteredTick(double InCurrentTime, float InDeltaTime)`
- L806 _protected member_ `TSharedPtr< FCarouselDisplayItem > LeftCarouselWidget;` — Holds the CarouselWidgets
- L807 _protected member_ `TSharedPtr< FCarouselDisplayItem > CenterCarouselWidget;`
- L808 _protected member_ `TSharedPtr< FCarouselDisplayItem > RightCarouselWidget;`
- L811 _protected member_ `const TArray<ItemType>* ItemsSource;` — Pointer to the array of data items that we are observing
- L814 _protected member_ `FOnGenerateWidget OnGenerateWidget;` — Hold the delegate to be invoked when a widget changes.
- L817 _protected member_ `FOnCarouselPageChanged OnPageChanged;` — Hold the delegate to be invoked when the current page changes.
- L820 _protected member_ `TSharedPtr< SHorizontalBox > WidgetDisplayBox;` — Holds the widget display box.
- L823 _protected member_ `int32 WidgetIndex;` — Holds the visible widget index.
- L826 _protected member_ `float MoveSpeed;` — Holds the move speed
- L829 _protected member_ `float SlideValueLeftLimit;` — Holds The left limit
- L832 _protected member_ `float SlideValueRightLimit;` — The right limit
- L835 _protected member_ `float PeakValueLeftLimit;` — Holds The peak left limit
- L838 _protected member_ `float PeakValueRightLimit;` — The peak right limit
- L841 _protected member_ `float FadeRate;` — The fade rate

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace EWidgetCarouselScrollDirection`
- L428 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCarouselPageChanged, int32 );`

### `Source/Runtime/WidgetCarousel/Public/SWidgetCarouselWithNavigation.h` (Public)


#### class `SWidgetCarouselWithNavigation`  
`template <typename ItemType> class SWidgetCarouselWithNavigation : public SCompoundWidget`  
_L25-188_
- inherits: `SCompoundWidget`
- desc: A widget carousel which includes embedded left and right navigation buttons and a navigation bar below.
- L29 _public typedef_ `typedef typename TSlateDelegates< ItemType >::FOnGenerateWidget FOnGenerateWidget;`
- L31 _public function_ `SLATE_BEGIN_ARGS(SWidgetCarouselWithNavigation<ItemType>) : _NavigationBarStyle() , _NavigationButtonStyle() , _WidgetItemsSource(static_cast<const TArray<ItemType>*>(NULL))`
- L37 _public prototype_ `SLATE_STYLE_ARGUMENT(FWidgetCarouselNavigationBarStyle, NavigationBarStyle) SLATE_STYLE_ARGUMENT(FWidgetCarouselNavigationButtonStyle, NavigationButtonStyle) SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_ARGUMENT(const TArray<ItemType>*, WidgetItemsSource) SLATE_END_ARGS();`
- L49 _public function_ `void Construct(const FArguments& InArgs)`
- L134 _public prototype_ `~SWidgetCarouselWithNavigation() = default;`
- L137 _private function_ `TSharedRef<SWidget> GenerateWidget(ItemType Item)`
- L142 _private function_ `FReply HandleNextButtonClicked()`
- L148 _private function_ `FReply HandlePreviousButtonClicked()`
- L154 _private function_ `void HandlePeak(EWidgetCarouselScrollDirection::Type Direction)`
- L159 _private function_ `EVisibility GetScreenshotVisibility() const`
- L164 _private function_ `EVisibility GetScreenshotNavigationVisibility() const`
- L169 _private function_ `int32 GetCurrentItemIndex() const`
- L174 _private function_ `float GetCurrentSlideAmount() const`
- L179 _private function_ `void CarouselScrollBarIndexChanged(int32 NewIndex)`
- L185 _private member_ `TSharedPtr<SWidgetCarousel<ItemType>> Carousel;`
- L186 _private member_ `FOnGenerateWidget OnGenerateWidget;`
- L187 _private member_ `const TArray<ItemType>* WidgetItemsSource;`

### `Source/Runtime/WidgetCarousel/Public/WidgetCarouselModule.h` (Public)


#### class `FWidgetCarouselModule`  
`class FWidgetCarouselModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- desc: Implements the WidgetCarousel module.
- L15 _public prototype_ `virtual void StartupModule( ) override;`
- L17 _public prototype_ `virtual void ShutdownModule( ) override;`

### `Source/Runtime/WidgetCarousel/Public/WidgetCarouselStyle.h` (Public)


#### struct `FWidgetCarouselNavigationButtonStyle`  
`struct FWidgetCarouselNavigationButtonStyle : public FSlateWidgetStyle`  
_L14-40_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- L18 _public prototype_ `FWidgetCarouselNavigationButtonStyle();`
- L20 _public prototype_ `virtual ~FWidgetCarouselNavigationButtonStyle() = default;`
- L22 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*> & OutBrushes) const override;`
- L24 _public member_ `static const FName TypeName;`
- L25 _public function_ `virtual const FName GetTypeName() const override`
- L27 _public prototype_ `static const FWidgetCarouselNavigationButtonStyle& GetDefault();`
- L30 _public member_ `FButtonStyle InnerButtonStyle;` — `UPROPERTY()`
- L31 _public function_ `FWidgetCarouselNavigationButtonStyle& SetInnerButtonStyle(const FButtonStyle& InInnerButtonStyle)`
- L34 _public member_ `FSlateBrush NavigationButtonLeftImage;` — `UPROPERTY()`
- L35 _public function_ `FWidgetCarouselNavigationButtonStyle& SetNavigationButtonLeftImage(const FSlateBrush& InNavigationButtonLeftImage)`
- L38 _public member_ `FSlateBrush NavigationButtonRightImage;` — `UPROPERTY()`
- L39 _public function_ `FWidgetCarouselNavigationButtonStyle& SetNavigationButtonRightImage(const FSlateBrush& InNavigationButtonRightImage)`

#### struct `FWidgetCarouselNavigationBarStyle`  
`struct FWidgetCarouselNavigationBarStyle : public FSlateWidgetStyle`  
_L43-73_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- L47 _public prototype_ `FWidgetCarouselNavigationBarStyle();`
- L49 _public prototype_ `virtual ~FWidgetCarouselNavigationBarStyle() = default;`
- L51 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*> & OutBrushes) const override;`
- L53 _public member_ `static const FName TypeName;`
- L54 _public function_ `virtual const FName GetTypeName() const override`
- L56 _public prototype_ `static const FWidgetCarouselNavigationBarStyle& GetDefault();`
- L59 _public member_ `FSlateBrush HighlightBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)`
- L60 _public function_ `FWidgetCarouselNavigationBarStyle& SetHighlightBrush(const FSlateBrush& InHighlightBrush)`
- L63 _public member_ `FButtonStyle LeftButtonStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)`
- L64 _public function_ `FWidgetCarouselNavigationBarStyle& SetLeftButtonStyle(const FButtonStyle& InLeftButtonStyle)`
- L67 _public member_ `FButtonStyle CenterButtonStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)`
- L68 _public function_ `FWidgetCarouselNavigationBarStyle& SetCenterButtonStyle(const FButtonStyle& InCenterButtonStyle)`
- L71 _public member_ `FButtonStyle RightButtonStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)`
- L72 _public function_ `FWidgetCarouselNavigationBarStyle& SetRightButtonStyle(const FButtonStyle& InRightButtonStyle)`

#### class `FWidgetCarouselModuleStyle`  
`class FWidgetCarouselModuleStyle`  
_L76-99_
- desc: Manages the style which provides resources for the add content dialog.
- L80 _public prototype_ `static void Initialize();`
- L82 _public prototype_ `static void Shutdown();`
- L85 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L88 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the widget carousel
- L90 _public prototype_ `static FName GetStyleSetName();`
- L94 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L98 _private member_ `static TSharedPtr< class FSlateStyleSet > WidgetCarouselStyleInstance;`
