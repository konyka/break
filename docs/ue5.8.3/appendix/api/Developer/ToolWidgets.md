# Developer / ToolWidgets

- module root: `Source/Developer/ToolWidgets`
- headers: 48; symbols: 1265
- symbol kinds: class=46, delegate=39, enum=9, enumerator=35, function=230, macro=27, member=388, namespace=14, prototype=446, struct=27, typedef=4
- PrivateDependencyModuleNames: AppFramework, ApplicationCore
- PublicDependencyModuleNames: Core, CoreUObject, InputCore, Slate, SlateCore, ToolMenus, TypedElementFramework

### `Source/Developer/ToolWidgets/Private/Overlay/SDraggableBox.h` (Private)


#### class `UE::ToolWidgets::SDraggableBox`  
`class SDraggableBox : public SCompoundWidget`  
_L24-124_
- inherits: `SCompoundWidget`
- desc: A widget for the draggable box itself, which requires its parent to handle its positioning in response to the drag. Users probably shouldn't use this class directly; rather, they should use SDraggableBoxOverlay, which will put its contents into a draggable box and properly handle the dragging without the user having to set it up.
- L27 _public function_ `SLATE_BEGIN_ARGS(SDraggableBox) : _Draggable(true) , _DragOverridesCenterAlignment(false) , _Resizable(EResizeEdges::None) , _ResizeHandleThickness(5.f)`
- L33 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(bool, Draggable) SLATE_ATTRIBUTE(bool, DragOverridesCenterAlignment) SLATE_EVENT(FSimpleDelegate, OnUserDraggedToNewPosition) SLATE_ARGUMENT(EResizeEdges, Resizable) SLATE_ARGUMENT(float, ResizeHandleThickness) SLATE_EVENT(FSimpleDelegate, OnUserResized) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SDraggableBoxOverlay>& InDraggableOverlay);`
- L65 _public prototype_ `void OnDragUpdate(const FPointerEvent& InMouseEvent, const FDragInfo& InDragInfo, bool bInDropped);`
- L68 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L69 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L70 _public prototype_ `FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L71 _public prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L72 _public prototype_ `FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L73 _public prototype_ `FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L78 _protected member_ `TWeakPtr<SDraggableBoxOverlay> DraggableOverlayWeak;`
- L79 _protected member_ `TSharedPtr<SWidget> InnerWidget;`
- L84 _private member_ `TAttribute<bool> DraggableAttr;` — Whether this widget should be allowed to be dragged.
- L87 _private member_ `TAttribute<bool> DragOverridesCenterAlignmentAttr;` — Whether this widget can override center alignment when dragged.
- L90 _private member_ `FSimpleDelegate OnUserDraggedToNewPositionDelegate;` — The content you want to be able to drag around in the parent widget.
- L92 _private prototype_ `FVector2f GetCenterBoxAlignmentOffset() const;`
- L97 _private member_ `TSharedPtr<SBox> ContentSizeBox;` — SBox wrapper around the content that provides explicit WidthOverride/HeightOverride when resizing.
- L99 _private member_ `EResizeEdges ResizeEdges = EResizeEdges::None;`
- L100 _private member_ `float ResizeHandleThickness = 5.f;`
- L101 _private member_ `FSimpleDelegate OnUserResizedDelegate;`
- L104 _private member_ `EResizeEdges HoveredResizeEdge = EResizeEdges::None;` — Edge(s) the cursor is currently hovering over (no button held). Used for cursor feedback.
- L106 _private member_ `EResizeEdges ActiveResizeEdge = EResizeEdges::None;` — Edge(s) being actively resized (mouse captured).
- L109 _private member_ `FVector2f ResizeStartMousePos;` — Screen-space mouse position when the resize began.
- L111 _private member_ `FVector2f ResizeStartBoxSize;` — Box size (local) at the start of the resize.
- L113 _private member_ `FVector2f ResizeStartAlignmentOffset;` — Overlay alignment offset at the start of the resize (for Left/Top edge adjustment).
- L116 _private prototype_ `EResizeEdges GetEdgeAtLocalPosition(FVector2f LocalPos, FVector2f WidgetSize) const;` — Returns which configured edge(s) the given local position falls within.
- L118 _private prototype_ `FCursorReply GetCursorForEdge(EResizeEdges Edge) const;` — Returns the appropriate resize cursor reply for the given edge flags.
- L121 _private prototype_ `FOptionalSize GetWidthOverride() const;` — Bound to ContentSizeBox.WidthOverride - reads ExplicitBoxSize from the overlay.
- L123 _private prototype_ `FOptionalSize GetHeightOverride() const;` — Bound to ContentSizeBox.HeightOverride - reads ExplicitBoxSize from the overlay.

#### struct `UE::ToolWidgets::SDraggableBox::FDragInfo`  
`struct FDragInfo`  
_L57-63_
- L59 _public member_ `EHorizontalAlignment OriginalHorizontalAlignment = HAlign_Left;`
- L60 _public member_ `EVerticalAlignment OriginalVerticalAlignment = VAlign_Bottom;`
- L61 _public member_ `FVector2f OriginalAlignmentOffset = FVector2f::ZeroVector;`
- L62 _public member_ `FVector2f OriginalMousePosition;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ToolWidgets` (scope `UE`)

### `Source/Developer/ToolWidgets/Private/Sidebar/SSidebarButton.h` (Private)


#### class `SSidebarButton`  
`class SSidebarButton : public SCompoundWidget`  
_L29-89_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SSidebarButton)`
- L34 _public prototype_ `SLATE_ARGUMENT(float, MinButtonSize) SLATE_ARGUMENT(float, MaxButtonSize) SLATE_ARGUMENT(float, ButtonThickness) SLATE_EVENT(FOnSidebarButtonPressed, OnPressed) SLATE_EVENT(FOnSidebarPinToggled, OnPinToggled) SLATE_EVENT(FOnSidebarPinToggled, OnDockToggled) SLATE_EVENT(FOnGetContent, OnGetContextMenuContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSidebarDrawer>& InDrawer, const ESidebarTabLocation InTabLocation);`
- L45 _public prototype_ `void UpdateAppearance(const TSharedPtr<FSidebarDrawer>& InLastDrawerOpen);`
- L47 _public prototype_ `void OnTabRenamed(const TWeakPtr<FSidebarDrawer>& InDrawer);`
- L49 _public prototype_ `static EHorizontalAlignment GetHAlignFromTabLocation(const ESidebarTabLocation InTabLocation);`
- L50 _public prototype_ `static EVerticalAlignment GetVAlignFromTabLocation(const ESidebarTabLocation InTabLocation);`
- L53 _protected prototype_ `EVisibility GetActiveTabIndicatorVisibility() const;`
- L55 _protected prototype_ `EVisibility GetPinVisibility() const;`
- L56 _protected prototype_ `FText GetPinToolTipText() const;`
- L57 _protected prototype_ `ECheckBoxState IsPinChecked() const;`
- L58 _protected prototype_ `const FSlateBrush* GetPinImage() const;`
- L59 _protected prototype_ `void OnPinStateChanged(const ECheckBoxState InNewState);`
- L61 _protected prototype_ `EVisibility GetDockVisibility() const;`
- L62 _protected prototype_ `FText GetDockToolTipText() const;`
- L63 _protected prototype_ `ECheckBoxState IsDockChecked() const;`
- L64 _protected prototype_ `const FSlateBrush* GetDockImage() const;`
- L65 _protected prototype_ `void OnDockStateChanged(const ECheckBoxState InNewState);`
- L68 _protected prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L69 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L72 _protected member_ `TWeakPtr<FSidebarDrawer> DrawerWeak;`
- L73 _protected member_ `ESidebarTabLocation TabLocation = ESidebarTabLocation::Right;`
- L75 _protected member_ `FOnSidebarButtonPressed OnPressed;`
- L76 _protected member_ `FOnSidebarPinToggled OnPinToggled;`
- L77 _protected member_ `FOnSidebarDockToggled OnDockToggled;`
- L78 _protected member_ `FOnGetContent OnGetContextMenuContent;`
- L80 _protected member_ `const FDockTabStyle* DockTabStyle = nullptr;`
- L82 _protected member_ `TSharedPtr<SSidebarButtonText> Label;`
- L83 _protected member_ `TSharedPtr<SWidget> ActiveIndicator;`
- L84 _protected member_ `TSharedPtr<SBorder> OpenBorder;`
- L85 _protected member_ `TSharedPtr<SButton> MainButton;`
- L87 _protected member_ `TSharedPtr<SCheckBox> PinCheckBox;`
- L88 _protected member_ `TSharedPtr<SCheckBox> DockCheckBox;`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSidebarButtonPressed, const TSharedRef<FSidebarDrawer>&);`
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSidebarButtonPressed, const TSharedRef<FSidebarDrawer>&);`
- L26 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSidebarPinToggled, const TSharedRef<FSidebarDrawer>&, const bool );`
- L26 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSidebarPinToggled, const TSharedRef<FSidebarDrawer>&, const bool );`
- L27 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSidebarDockToggled, const TSharedRef<FSidebarDrawer>&, const bool );`
- L27 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSidebarDockToggled, const TSharedRef<FSidebarDrawer>&, const bool );`

### `Source/Developer/ToolWidgets/Private/Sidebar/SSidebarButtonText.h` (Private)


#### class `SSidebarButtonText`  
`class SSidebarButtonText : public SLeafWidget`  
_L23-56_
- inherits: `SLeafWidget`
- desc: Vertical text block for use in the tab drawer button. Text is aligned to the top of the widget if it fits without clipping; otherwise it is ellipsized and fills the widget height.
- L26 _public function_ `SLATE_BEGIN_ARGS(SSidebarButtonText) : _Text() , _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>(TEXT("NormalText"))) , _AngleDegrees(0) , _OverflowPolicy()`
- L32 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ATTRIBUTE(float, AngleDegrees) SLATE_ARGUMENT(TOptional<ETextOverflowPolicy>, OverflowPolicy) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `void SetText(const TAttribute<FText>& InText);`
- L42 _public prototype_ `void SetRotation(const TAttribute<float>& InAngleDegrees);`
- L46 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InCullingRect , FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L48 _protected prototype_ `virtual FVector2D ComputeDesiredSize(const float InLayoutScaleMultiplier) const override;`
- L51 _protected member_ `TAttribute<FText> Text;`
- L52 _protected member_ `FTextBlockStyle TextStyle;`
- L53 _protected member_ `TAttribute<float> AngleDegrees;`
- L55 _protected member_ `TUniquePtr<FSlateTextBlockLayout> TextLayoutCache;`

### `Source/Developer/ToolWidgets/Private/Sidebar/SSidebarDrawer.h` (Private)


#### class `SSidebarDrawer`  
`class SSidebarDrawer : public SCompoundWidget`  
_L23-137_
- inherits: `SCompoundWidget`
- desc: Handles sliding drawer animation
- L26 _public function_ `SLATE_BEGIN_ARGS(SSidebarDrawer) : _ShadowOffset(FVector2f(8.f, 8.f)) , _ExpanderHandleSize(5.f)`
- L33 _public prototype_ `SLATE_ARGUMENT(float, MinDrawerSize) SLATE_ARGUMENT(float, MaxDrawerSize) SLATE_ARGUMENT(float, TargetDrawerSize) SLATE_ARGUMENT(FDeprecateSlateVector2D, ShadowOffset) SLATE_ARGUMENT(float, ExpanderHandleSize) SLATE_EVENT(FOnSidebarDrawerTargetSizeChanged, OnDrawerSizeChanged) SLATE_EVENT(FGenericSidebarDrawerWidgetDelegate, OnDrawerFocused) SLATE_EVENT(FGenericSidebarDrawerWidgetDelegate, OnDrawerFocusLost) SLATE_EVENT(FGenericSidebarDrawerWidgetDelegate, OnOpenAnimationFinish) SLATE_EVENT(FGenericSidebarDrawerWidgetDelegate, OnCloseAnimationFinish) SLATE_END_ARGS() ~SSidebarDrawer(); void Construct(const FArguments& InArgs, const TSharedRef<FSidebarDrawer>& InDrawer, const ESidebarTabLocation InTabLocation); void Open(const bool bInAnimateOpen = true); void Close(const bool bInAnimateOpen = true);` — The minimum size a drawer can be when opened. This unit is in window space
- L56 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FSidebarDrawer>& InDrawer, const ESidebarTabLocation InTabLocation);`
- L63 _public prototype_ `void Open(const bool bInAnimateOpen = true);` — Opens the drawer. @param bInAnimateOpen Whether to play an animation when opening the drawer, defaults to true.
- L70 _public prototype_ `void Close(const bool bInAnimateOpen = true);` — Closes the drawer. @param bInAnimateOpen Whether to play an animation when closing the drawer, defaults to true.
- L73 _public prototype_ `bool IsOpen() const;` — @return True if the drawer is open.
- L76 _public prototype_ `bool IsClosing() const;` — @return True if the drawer is currently playing the close animation.
- L79 _public prototype_ `void SetCurrentSize(const float InSize);` — Sets the current size of the drawer in pixels, ignoring any open/close animation.
- L82 _public prototype_ `TSharedPtr<FSidebarDrawer> GetDrawer() const;` — @return The drawer associated with this drawer widget.
- L85 _protected member_ `static constexpr float AnimationLength = 0.15f;`
- L88 _protected prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L89 _protected prototype_ `virtual FVector2D ComputeDesiredSize(const float InLayoutScaleMultiplier) const override;`
- L90 _protected prototype_ `virtual void OnArrangeChildren(const FGeometry& InAllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L91 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InAllottedGeometry, const FPointerEvent& InMouseEvent) override;`
- L92 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InAllottedGeometry, const FPointerEvent& InMouseEvent) override;`
- L93 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& InAllottedGeometry, const FPointerEvent& InMouseEvent) override;`
- L94 _protected prototype_ `virtual void OnMouseLeave(const FPointerEvent& InMouseEvent) override;`
- L95 _protected prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& InGeometry, const FPointerEvent& InCursorEvent) const override;`
- L96 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InCullingRect , FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L100 _protected prototype_ `FGeometry GetRenderTransformedGeometry(const FGeometry& InAllottedGeometry) const;`
- L102 _protected prototype_ `FGeometry GetResizeHandleGeometry(const FGeometry& InAllottedGeometry) const;`
- L104 _protected prototype_ `EActiveTimerReturnType UpdateAnimation(const double InCurrentTime, const float InDeltaTime);`
- L106 _protected prototype_ `void OnGlobalFocusChanging(const FFocusEvent& InFocusEvent , const FWeakWidgetPath& InOldFocusedWidgetPath, const TSharedPtr<SWidget>& InOldFocusedWidget , const FWidgetPath& InNewFocusedWidgetPath, const TSharedPtr<SWidget>& InNewFocusedWidget);`
- L110 _protected member_ `TWeakPtr<FSidebarDrawer> DrawerWeak;`
- L111 _protected member_ `ESidebarTabLocation TabLocation = ESidebarTabLocation::Right;`
- L113 _protected member_ `float MinDrawerSize = 0.f;`
- L114 _protected member_ `float MaxDrawerSize = 0.f;`
- L115 _protected member_ `float TargetDrawerSize = 0.f;`
- L116 _protected member_ `FVector2f ShadowOffset = FVector2f::ZeroVector;`
- L117 _protected member_ `float ExpanderHandleSize = 5.f;`
- L119 _protected member_ `FOnSidebarDrawerTargetSizeChanged OnDrawerSizeChanged;`
- L120 _protected member_ `FGenericSidebarDrawerWidgetDelegate OnDrawerFocused;`
- L121 _protected member_ `FGenericSidebarDrawerWidgetDelegate OnDrawerFocusLost;`
- L122 _protected member_ `FGenericSidebarDrawerWidgetDelegate OnCloseAnimationFinish;`
- L123 _protected member_ `FGenericSidebarDrawerWidgetDelegate OnOpenAnimationFinish;`
- L125 _protected member_ `FCurveSequence OpenCloseAnimation;`
- L126 _protected member_ `TSharedPtr<FActiveTimerHandle> OpenCloseTimer;`
- L128 _protected member_ `FThrottleRequest ResizeThrottleHandle;`
- L129 _protected member_ `FThrottleRequest AnimationThrottle;`
- L131 _protected member_ `float CurrentSize = 0.f;`
- L133 _protected member_ `bool bIsResizing = false;`
- L134 _protected member_ `bool bIsResizeHandleHovered = false;`
- L135 _protected member_ `float InitialSizeAtResize = 0.f;`
- L136 _protected member_ `FGeometry InitialResizeGeometry;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FGenericSidebarDrawerWidgetDelegate, const TSharedRef<SSidebarDrawer>&);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FGenericSidebarDrawerWidgetDelegate, const TSharedRef<SSidebarDrawer>&);`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSidebarDrawerTargetSizeChanged, const TSharedRef<SSidebarDrawer>&, float);`
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSidebarDrawerTargetSizeChanged, const TSharedRef<SSidebarDrawer>&, float);`

### `Source/Developer/ToolWidgets/Private/Sidebar/SSidebarDrawerContent.h` (Private)


#### class `SSidebarDrawerContent`  
`class SSidebarDrawerContent : public SCompoundWidget`  
_L17-49_
- inherits: `SCompoundWidget`
- desc: Handles drawer multi-section display
- L20 _public function_ `SLATE_BEGIN_ARGS(SSidebarDrawerContent)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FSidebarDrawer>& InOwnerDrawerWeak);`
- L25 _public prototype_ `void BuildContent();`
- L28 _private prototype_ `void OnSectionSelected(const ECheckBoxState InCheckBoxState, const FName InSectionName);`
- L30 _private prototype_ `bool IsSectionSelected(const FName InSectionName) const;`
- L32 _private prototype_ `bool ShouldShowSection(const TWeakPtr<ISidebarDrawerContent>& InSectionWeak) const;`
- L34 _private prototype_ `EVisibility GetSectionButtonVisibility(TWeakPtr<ISidebarDrawerContent> InSectionWeak) const;`
- L36 _private prototype_ `EVisibility GetSectionContentVisibility(const FName InSectionName, TWeakPtr<ISidebarDrawerContent> InSectionWeak) const;`
- L38 _private prototype_ `ECheckBoxState GetSectionCheckBoxState(const FName InSectionName) const;`
- L40 _private prototype_ `TArray<TSharedRef<ISidebarDrawerContent>> GetOrderedSections() const;`
- L42 _private prototype_ `void AddContentSlot(const TSharedRef<ISidebarDrawerContent>& InDrawerContent);`
- L44 _private member_ `TWeakPtr<FSidebarDrawer> OwnerDrawerWeak;`
- L46 _private member_ `TSharedPtr<SWrapBox> ButtonBox;`
- L48 _private member_ `TSharedPtr<SVerticalBox> ContentBox;`

### `Source/Developer/ToolWidgets/Private/Sidebar/SidebarButtonMenuContext.h` (Private)


#### class `USidebarButtonMenuContext`  
`class USidebarButtonMenuContext : public UObject`  
_L12-37_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public function_ `void Init(const TWeakPtr<SSidebar>& InSidebarWeak, const TWeakPtr<FSidebarDrawer>& InDrawerWeak)`
- L23 _public function_ `TSharedPtr<SSidebar> GetSidebarWidget() const`
- L28 _public function_ `TSharedPtr<FSidebarDrawer> GetDrawer() const`
- L34 _protected member_ `TWeakPtr<SSidebar> SidebarWeak;`
- L36 _protected member_ `TWeakPtr<FSidebarDrawer> DrawerWeak;`

### `Source/Developer/ToolWidgets/Private/Sidebar/SidebarDrawer.h` (Private)


#### class `FSidebarDrawer`  
`class FSidebarDrawer`  
_L16-68_
- L19 _public function_ `FSidebarDrawer(FSidebarDrawerConfig&& InDrawerConfig) : Config(MoveTemp(InDrawerConfig))`
- L23 _public function_ `bool operator==(const FName InOtherId) const`
- L28 _public function_ `bool operator!=(const FName InOtherId) const`
- L33 _public function_ `bool operator==(const FSidebarDrawer& InOther) const`
- L38 _public function_ `bool operator!=(const FSidebarDrawer& InOther) const`
- L43 _public function_ `FName GetUniqueId() const`
- L48 _public member_ `FSidebarDrawerConfig Config;`
- L51 _public member_ `TSharedPtr<SWidget> ButtonWidget;` — Tab button widget for this drawer.
- L54 _public member_ `TSharedPtr<SSidebarDrawer> DrawerWidget;` — Tab sliding drawer widget that contains the content.
- L57 _public member_ `TSharedPtr<SWidget> ContentWidget;` — The content widget contains the section widgets.
- L59 _public member_ `TMap<FName, TSharedRef<ISidebarDrawerContent>> ContentSections;`
- L61 _public member_ `bool bDisablePin = false;`
- L62 _public member_ `bool bDisableDock = false;`
- L64 _public member_ `bool bIsOpen = false;`
- L65 _public member_ `FSidebarDrawerState State;`
- L67 _public member_ `FOnSidebarDrawerOpenClose OnDrawerOpenCloseDelegate;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSidebarDrawerOpenClose, const FName , const bool ) class FSidebarDrawer { public: FSidebarDrawer(FSidebarDrawerConfig&& InDrawerConfig) : Config(MoveTemp(InDrawerConfig)) {} bool operator==(const FName InOtherId) const { return Config.UniqueId == InOtherId; } bool operator!=(const FName InOtherId) const { return Config.UniqueId != InOtherId; } bool operator==(const FSidebarDrawer& InOther) const { return Config == InOther.Config; } bool operator!=(const FSidebarDrawer& InOther) const { return Config != InOther.Config; } FName GetUniqueId() const { return Config.UniqueId; } FSidebarDrawerConfig Config; TSharedPtr<SWidget> ButtonWidget;`

### `Source/Developer/ToolWidgets/Private/ToolWidgetsStylePrivate.h` (Private)


#### class `UE::ToolWidgets::Private::FToolWidgetsStylePrivate`  
`class FToolWidgetsStylePrivate final`  
_L10-27_
- desc: A supplementary Style container, accessible to the module only.

#### struct `UE::ToolWidgets::Private::FToolWidgetsStylePrivate::FButton`  
`struct FButton`  
_L13-17_
- L15 _public member_ `static constexpr float DefaultBorderPadding = 2.0f;` — This needs to be accounted for when padding buttons to achieve the desired height, may be overridden by ButtonStyle
- L16 _public member_ `static constexpr float DefaultBorderThickness = 1.0f;`

#### struct `UE::ToolWidgets::Private::FToolWidgetsStylePrivate::FActionButton`  
`struct FActionButton`  
_L19-26_
- L21 _public member_ `static constexpr float DefaultButtonHeight = 22.0f;` — Design standard
- L22 _public member_ `static constexpr float DefaultIconHeight = 16.0f;` — Vertical icon space should always be used to affect button size and ensure it's consistent regardless of icon presence
- L23 _public member_ `static constexpr float DefaultIconLabelSpacing = 3.0f;`
- L24 _public member_ `static constexpr float DefaultVerticalPadding = (DefaultButtonHeight - DefaultIconHeight) / 2.0f;` — Total Button Height - Icon Height (/2 for top and bottom)
- L25 _public member_ `static constexpr float DefaultHorizontalPadding = 2.0f;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ToolWidgets` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::ToolWidgets`)

### `Source/Developer/ToolWidgets/Private/ToolWidgetsUtilitiesPrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ToolWidgets` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::ToolWidgets`)
- L12 _namespace_ `namespace ActionButton` (scope `UE::ToolWidgets::Private`)
- L14 _prototype_ `TSharedRef<SWidget> MakeButtonContent( const TAttribute<const FSlateBrush*>& InIcon, const TAttribute<FSlateColor>& InIconColorAndOpacity, const TAttribute<FText>& InText, const FTextBlockStyle* InTextBlockStyle);` (scope `UE::ToolWidgets::Private::ActionButton`)
- L20 _prototype_ `TSharedRef<SWidget> MakeButtonContent( const FActionButtonStyle* InActionButtonStyle, const TAttribute<const FSlateBrush*>& InIcon, const TAttribute<FSlateColor>& InIconColorAndOpacity, const TAttribute<FText>& InText, const FTextBlockStyle* InTextBlockStyle);` (scope `UE::ToolWidgets::Private::ActionButton`)
- L27 _prototype_ `TAttribute<FMargin> MakeIconPaddingOverride(const TAttribute<const FSlateBrush*>& Icon, const FMargin& ButtonStylePadding, const TOptional<FMargin>& IconPadding);` (scope `UE::ToolWidgets::Private::ActionButton`)

### `Source/Developer/ToolWidgets/Public/Columns/SlateDelegateColumns.h` (Public)


#### struct `FExternalWidgetSelectionColumn`  
`struct FExternalWidgetSelectionColumn : public FEditorDataStorageColumn`  
_L16-27_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed selection"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row when an external widget manages selection for the widget referenced by the row, such as an owning SListView or STreeView
- L26 _public member_ `TSharedPtr<FIsSelected> IsSelected;` — Delegate to execute to check the status of if the widget is selected or not Only needs to be hooked up if an external widget is managing selection, such as a SListView or STreeView. E.g usage: Enables renaming by clicking the label twice if the widget is editable. @see SInlineEditableTextBlock::IsSelected

#### struct `FWidgetContextMenuColumn`  
`struct FWidgetContextMenuColumn : public FEditorDataStorageColumn`  
_L33-37_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with context menu"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to provide a context menu for the widget
- L36 _public member_ `TSharedPtr<FOnContextMenuOpening> OnContextMenuOpening;`

#### struct `FWidgetRowScrolledIntoView`  
`struct FWidgetRowScrolledIntoView : public FEditorDataStorageColumn`  
_L43-49_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with row scrolled into view delegate"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row for table views to allow systems to specify behavior when a row is scrolled into view
- L45 _public typedef_ `using FOnItemScrolledIntoView = TSlateDelegates<FTedsRowHandle>::FOnItemScrolledIntoView;`
- L48 _public member_ `TSharedPtr<FOnItemScrolledIntoView> OnItemScrolledIntoView;`

#### struct `FWidgetDoubleClickedColumn`  
`struct FWidgetDoubleClickedColumn : public FEditorDataStorageColumn`  
_L55-61_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with item scrolled into view delegate"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to specify behavior when the widget is double clicked
- L57 _public typedef_ `using FOnMouseButtonDoubleClick = TSlateDelegates<FTedsRowHandle>::FOnMouseButtonDoubleClick;`
- L60 _public member_ `TSharedPtr<FOnMouseButtonDoubleClick> OnMouseButtonDoubleClick;`

#### struct `FWidgetEnterEditModeColumn`  
`struct FWidgetEnterEditModeColumn : public FEditorDataStorageColumn`  
_L67-71_
- reflection: `USTRUCT(meta = (DisplayName = "On Label Edit"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column that triggers a signal when the label is edited.
- L70 _public member_ `TSharedPtr<FSimpleDelegate> OnEnterEditMode;`

### `Source/Developer/ToolWidgets/Public/Columns/SlateHeaderColumns.h` (Public)


#### struct `FHeaderWidgetSizeColumn`  
`struct FHeaderWidgetSizeColumn final : public FEditorDataStorageColumn`  
_L14-28_
- reflection: `USTRUCT(meta = (DisplayName = "Header widget with custom size"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a header widget row to control the sizing when the default behavior is incorrect.
- L18 _public member_ `EColumnSizeMode::Type ColumnSizeMode;`
- L27 _public member_ `float Width;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — Fill: Column stretches to this fraction of the header row Fixed: Column is fixed at this width in slate units and cannot be resized Manual: Column defaults to this width in slate units and can be user-sized FillSized: Column stretches as Fill but is initialized with this width in slate units

### `Source/Developer/ToolWidgets/Public/Dialog/DialogCommands.h` (Public)


#### class `FDialogCommands`  
`class FDialogCommands : public TCommands<FDialogCommands>`  
_L18-31_
- inherits: `TCommands<FDialogCommands>`
- desc: Class containing commands for dialog actions common to most dialogs
- L21 _public prototype_ `FDialogCommands();`
- L24 _public member_ `TSharedPtr<FUICommandInfo> Cancel;` — Trigger the default cancellation action for the current dialog
- L27 _public member_ `TSharedPtr<FUICommandInfo> Confirm;` — Trigger the default confirmation action for the current dialog
- L30 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/Dialog/DialogUtils.h` (Public)


#### struct `FDialogButtonTexts`  
`struct FDialogButtonTexts`  
_L12-31_
- L14 _public prototype_ `static const FDialogButtonTexts& Get();`
- L17 _public member_ `const FText No;` — Common dialog button texts
- L18 _public member_ `const FText Yes;`
- L19 _public member_ `const FText YesAll;`
- L20 _public member_ `const FText NoAll;`
- L21 _public member_ `const FText Cancel;`
- L22 _public member_ `const FText Ok;`
- L23 _public member_ `const FText Retry;`
- L24 _public member_ `const FText Continue;`
- L27 _private prototype_ `FDialogButtonTexts(const FDialogButtonTexts&) = delete;`
- L28 _private prototype_ `FDialogButtonTexts& operator=(const FDialogButtonTexts&) = delete;`
- L30 _private prototype_ `FDialogButtonTexts();`

#### class `FDialogUtils`  
`class FDialogUtils`  
_L33-38_
- L37 _public prototype_ `static const FSlateBrush* GetMessageCategoryIcon(const EAppMsgCategory MessageCategory);` — Returns the Slate brush corresponding to the provided message category

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/Dialog/SCustomDialog.h` (Public)


#### class `SCustomDialog`  
`class SCustomDialog : public SWindow`  
_L38-265_
- inherits: `SWindow`
- desc: This is a custom dialog class, which allows any Slate widget to be used as the contents, with any number of auto-generated buttons that have any text. It also supports adding a custom icon to the dialog. Usage: TSharedRef<SCustomDialog> HelloWorldDialog = SNew(SCustomDialog) .Title(FText(LOCTEXT("HelloWorldTitleExample", "Hello, World!"))) .Content() [ SNew(SImage).Image(FName(TEXT("Hello")))) ] .Buttons({ SCustomDialog::FButton(LOCTEXT("OK", "OK")), SCustomDialog::FButton(LOCTEXT("Cancel", "Cancel")) }); returns 0 when OK is pressed, 1 when Cancel is pressed, -1 if the window is closed const int ButtonPressed = HelloWorldDialog->ShowModal(); Note: If the content is only text, see SMessageDialog.
- L94 _public function_ `SLATE_BEGIN_ARGS(SCustomDialog) : _AutoCloseOnButtonPress(true) , _Icon(nullptr) , _HAlignIcon(HAlign_Left) , _VAlignIcon(VAlign_Center) , _HAlignButtonBox(HAlign_Fill) , _VAlignButtonBox(VAlign_Fill) , _RootPadding(FMargin(4.f)) , _ButtonAreaPadding(FMargin(20.f, 16.f, 0.f, 0.f)) , _UseScrollBox(true) , _ScrollBoxMaxHeight(300.f) , _HAlignContent(HAlign_Left) , _VAlignContent(VAlign_Center) , _ClientSize(FVector2f::ZeroVector)`
- L115 _public prototype_ `SLATE_ARGUMENT(FText, Title) /** The content to display above the button;` — Title to display for the dialog.
- L199 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L206 _public prototype_ `void Show();` — Show the dialog. This method will return immediately.
- L211 _public prototype_ `int32 ShowModal(const int32 InDefaultReturnValue = INDEX_NONE);` — Show a modal dialog. Will block until an input is received. Returns the index of the button that was pressed or InDefaultReturnValue if in unattended mode.
- L214 _public prototype_ `void SetOnCancelHotkeyPressed(const FSimpleDelegate& InOnCancelHotkeyPressed);` — Assigns a function to the Cancel hotkey
- L217 _public prototype_ `void SetOnConfirmHotkeyPressed(const FSimpleDelegate& InOnConfirmHotkeyPressed);` — Assigns a function to the Confirm hotkey
- L220 _public prototype_ `void SetGetWidgetToFocusOnActivate(const FGetFocusWidget& InGetWidgetToFocusOnActivate);` — Sets the function to call when activating to get the widget to focus
- L222 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L224 _public prototype_ `virtual bool OnIsActiveChanged(const FWindowActivateEvent& ActivateEvent) override;`
- L228 _private prototype_ `TSharedRef<SWidget> CreateContentBox(const FArguments& InArgs);`
- L229 _private prototype_ `TSharedRef<SWidget> CreateButtonBox(const FArguments& InArgs);`
- L231 _private prototype_ `FReply OnButtonClicked(FSimpleDelegate OnClicked, int32 ButtonIndex);`
- L232 _private prototype_ `void OnHotkeyPressed(FSimpleDelegate OnClicked, int32 ButtonIndex);`
- L234 _private prototype_ `bool CanExecuteCancel() const;`
- L235 _private prototype_ `void ExecuteCancel();`
- L237 _private prototype_ `bool CanExecuteConfirm() const;`
- L238 _private prototype_ `void ExecuteConfirm();`
- L241 _private member_ `int32 LastPressedButton = INDEX_NONE;` — The index of the button that was pressed last.
- L243 _private member_ `FSimpleDelegate OnClosed;`
- L246 _private member_ `bool bAutoCloseOnButtonPress = true;` — Whether to close the window when any button is pressed or triggered via hotkey
- L249 _private member_ `bool bGeneratedCancelButton = false;` — Whether a Cancel button has been generated
- L252 _private member_ `bool bGeneratedConfirmButton = false;` — Whether a Confirm button has been generated
- L255 _private member_ `FSimpleDelegate OnCancelHotkeyPressed;` — Function to call when the Cancel hotkey (Escape) is pressed
- L258 _private member_ `FSimpleDelegate OnConfirmHotkeyPressed;` — Function to call when the Confirm hotkey (Enter) is pressed
- L261 _private member_ `FGetFocusWidget GetWidgetToFocusOnActivate;` — Function to call when activating to get the widget to focus
- L264 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for the dialog

#### enum `SCustomDialog::EButtonRole`  
`enum class EButtonRole`  
_L44-49_
- desc: Determines whether a button is triggered via the Cancel or Confirm hotkeys. If more than one button is assigned the same role, the last with that role will be used.
- L46 _public enumerator_ `Custom`
- L47 _public enumerator_ `Cancel`
- L48 _public enumerator_ `Confirm`

#### struct `SCustomDialog::FButton`  
`struct FButton`  
_L51-92_
- L53 _public function_ `FButton(TAttribute<FText> InButtonText, FSimpleDelegate InOnClicked = FSimpleDelegate(), const EButtonRole InButtonRole = EButtonRole::Custom) : ButtonText(MoveTemp(InButtonText)) , ButtonIsEnabled(true) , OnClicked(MoveTemp(InOnClicked)) , ButtonRole(InButtonRole)`
- L61 _public function_ `FButton& SetIsEnabled(TAttribute<bool> InButtonIsEnabled)` — Set whether this button enabled
- L64 _public function_ `FButton& SetToolTipText(TAttribute<FText> InButtonToolTipText)` — Set the tooltip text to use for this button
- L67 _public function_ `FButton& SetPrimary(bool bValue)` — Primary buttons are highlighted
- L70 _public function_ `FButton& SetOnClicked(FSimpleDelegate InOnClicked)` — Called when the button is clicked
- L74 _public function_ `FButton& SetButtonRole(const EButtonRole InButtonRole)` — Button role is used to determine whether the button should be triggered via the Cancel and Confirm hotkeys. The Cancel and Confirm roles should each only be used on a single button.
- L83 _public function_ `FButton& SetFocus()` — Whether to focus this button. Focus rules: 1: If a button has SetFocus(), use the last one 2: If a button is marked primary, use the last one 3: If a button has the Confirm role, use the last one 3: Otherwise, use the last button
- L85 _public member_ `TAttribute<FText> ButtonText;`
- L86 _public member_ `TAttribute<FText> ButtonToolTipText;`
- L87 _public member_ `TAttribute<bool> ButtonIsEnabled;`
- L88 _public member_ `FSimpleDelegate OnClicked;`
- L89 _public member_ `EButtonRole ButtonRole;`
- L90 _public member_ `bool bIsPrimary = false;`
- L91 _public member_ `bool bShouldFocus = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FGetFocusWidget);` — Delegate for functions to get the appropriate widget to focus on activation
- L14 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FGetFocusWidget);` — Delegate for functions to get the appropriate widget to focus on activation

### `Source/Developer/ToolWidgets/Public/Dialog/SMessageDialog.h` (Public)


#### class `SMessageDialog`  
`class SMessageDialog : public SCustomDialog`  
_L14-89_
- inherits: `SCustomDialog`
- desc: Special case of SCustomDialog dedicated to only displaying text messages. This class enforces uniform style and also adds a button for copying the message.
- L18 _public typedef_ `using FButton = SCustomDialog::FButton;` — Convenience for code using this class
- L20 _public function_ `SLATE_BEGIN_ARGS(SMessageDialog) : _AutoCloseOnButtonPress(true) , _UseRichText(true) , _DecoratorStyleSet(nullptr) , _Icon(nullptr) , _UseScrollBox(true) , _ScrollBoxMaxHeight(300.f) , _WrapMessageAt(512.f)`
- L33 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(FText, Message) SLATE_ARGUMENT(TArray<FButton>, Buttons) SLATE_EVENT(FSimpleDelegate, OnClosed) SLATE_ARGUMENT(SWindow::FArguments, WindowArguments) SLATE_ARGUMENT(bool, AutoCloseOnButtonPress) SLATE_ARGUMENT(bool, UseRichText) SLATE_ARGUMENT(TArray<TSharedRef<class ITextDecorator>>, Decorators) SLATE_ARGUMENT(const ISlateStyle*, DecoratorStyleSet) SLATE_ARGUMENT(const FSlateBrush*, Icon) SLATE_ARGUMENT(bool, UseScrollBox) SLATE_ARGUMENT(float, ScrollBoxMaxHeight) SLATE_ATTRIBUTE(float, WrapMessageAt)` — Title to display for the dialog.
- L80 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L82 _public prototype_ `virtual FReply OnCopyMessage();`
- L86 _private member_ `FText Message;`
- L88 _private prototype_ `void CopyMessageToClipboard();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/Filters/CustomTextFilters.h` (Public)


#### struct `FCustomTextFilterData`  
`struct FCustomTextFilterData`  
_L14-32_
- reflection: `USTRUCT()`
- desc: Struct containing the data that SCustomTextFilterDialog is currently editing
- L19 _public member_ `FText FilterLabel;` — `UPROPERTY()`
- L22 _public member_ `FText FilterString;` — `UPROPERTY()`
- L25 _public member_ `FLinearColor FilterColor;` — `UPROPERTY()`
- L27 _public function_ `FCustomTextFilterData() : FilterColor(FLinearColor::White)`

#### class `ICustomTextFilter`  
`template<typename FilterType> class ICustomTextFilter`  
_L39-53_
- desc: Interface class to define how a custom text filter converts to/from FCustomTextFilterData FCustomTextFilter contains a generic implementation that can be used for most cases, look at FFrontendFilter_CustomText in the Content Browser for an example of a specific implementation
- L43 _public prototype_ `virtual ~ICustomTextFilter() = default;`
- L46 _public prototype_ `virtual void SetFromCustomTextFilterData(const FCustomTextFilterData& InFilterData) = 0;` — Set the internals of this filter from an FCustomTextFilterData
- L49 _public prototype_ `virtual FCustomTextFilterData CreateCustomTextFilterData() const = 0;` — Create an FCustomTextFilterData from the internals of this filter
- L52 _public prototype_ `virtual TSharedPtr<FFilterBase<FilterType>> GetFilter() = 0;` — Get the actual filter

#### class `FCustomTextFilter`  
`template<typename FilterType> class FCustomTextFilter : public FFilterBase<FilterType>, public ICustomTextFilter<FilterType>, public TSharedFromThis<FCustomTextFilter<FilterType>>`  
_L61-209_
- inherits: `FFilterBase<FilterType>,ICustomTextFilter<FilterType>,TSharedFromThis<FCustomTextFilter<FilterType>>`
- desc: A generic CustomTextFilter that can be created by providing a TTextFilter. Provide a delegate to a filter bar widget's CreateTextFilter argument that creates an instance of this class to handle most generic text comparisons.
- L68 _public function_ `FCustomTextFilter(TSharedPtr<TTextFilter<FilterType>> InTextFilter) : FFilterBase<FilterType>(nullptr) , TextFilter(InTextFilter)`
- L76 _public function_ `virtual FString GetName() const override` — Returns the system name for this filter
- L82 _public function_ `virtual FText GetDisplayName() const override` — Returns the human readable name for this filter
- L88 _public function_ `virtual void SetDisplayName(const FText& InDisplayName)` — Set the human readable name for this filter
- L94 _public function_ `virtual FText GetToolTipText() const override` — Returns the tooltip for this filter, shown in the filters menu
- L100 _public function_ `virtual FLinearColor GetColor() const override` — Returns the color this filter button will be when displayed as a button
- L106 _public function_ `virtual void SetColor(const FLinearColor& InColor)` — Set the color this filter button will be when displayed as a button
- L112 _public function_ `virtual FName GetIconName() const override` — Returns the name of the icon to use in menu entries
- L118 _public function_ `virtual bool IsInverseFilter() const override` — Returns true if the filter should be in the list when disabled and not in the list when enabled
- L123 _public function_ `virtual bool PassesFilter( FilterType InItem ) const override`
- L129 _public function_ `virtual FText GetFilterString() const` — Get the actual text this filter is using to test against
- L135 _public function_ `virtual void SetFilterString(const FText& InFilterString)` — Set the actual text this filter is using to test against
- L141 _public function_ `static FName GetFilterTypeName()` — All FCustomTextFilters have the same internal name, this is a helper function to get that name to test against
- L149 _public function_ `virtual void SetFromCustomTextFilterData(const FCustomTextFilterData& InFilterData) override` — Set the internals of this filter from an FCustomTextFilterData
- L157 _public function_ `virtual FCustomTextFilterData CreateCustomTextFilterData() const override` — Create an FCustomTextFilterData from the internals of this filter
- L168 _public function_ `virtual TSharedPtr<FFilterBase<FilterType>> GetFilter() override` — Get the actual filter
- L176 _public function_ `virtual void ActiveStateChanged(bool bActive) override` — Notification that the filter became active or inactive
- L182 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override` — Called when the right-click context menu is being built for this filter
- L188 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override` — Can be overriden for custom FilterBar subclasses to save settings, currently not implemented in any generic Filter Bar
- L194 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override` — Can be overriden for custom FilterBar subclasses to load settings, currently not implemented in any generic Filter Bar
- L202 _protected member_ `TSharedPtr<TTextFilter<FilterType>> TextFilter;` — The actual Text Filter containing information about the text being tested against
- L205 _protected member_ `FText DisplayName;` — The Display Name of this custom filter that the user sees
- L208 _protected member_ `FLinearColor Color;` — The Color of this filter pill

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "CustomTextFilters"`

### `Source/Developer/ToolWidgets/Public/Filters/FilterBase.h` (Public)


#### class `FFilterCategory`  
`class FFilterCategory`  
_L13-23_
- L16 _public function_ `FFilterCategory(const FText& InTitle, const FText& InTooltip) : Title(InTitle), Tooltip(InTooltip)`
- L19 _public member_ `const FText Title;` — The title of this category, used for the menu heading
- L22 _public member_ `const FText Tooltip;` — The menu tooltip for this category

#### class `FFilterBase`  
`template<typename FilterType> class FFilterBase : public IFilter<FilterType>`  
_L32-132_
- inherits: `IFilter<FilterType>`
- desc: The base class for all Filters that can be used with FilterBar Widgets @see FGenericFilter for a subclass that allows easy creation of filters
- L36 _public function_ `FFilterBase(TSharedPtr<FFilterCategory> InCategory) : FilterCategory(MoveTemp(InCategory))`
- L39 _public prototype_ `virtual FString GetName() const override = 0;` — Returns the system name for this filter
- L42 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the human readable name for this filter
- L45 _public prototype_ `virtual FText GetToolTipText() const = 0;` — Returns the tooltip for this filter, shown in the filters menu
- L48 _public prototype_ `virtual FLinearColor GetColor() const = 0;` — Returns the color this filter button will be when displayed as a button
- L51 _public prototype_ `virtual FName GetIconName() const = 0;` — Returns the name of the icon to use in menu entries
- L56 _public prototype_ `virtual bool IsInverseFilter() const = 0;` — If true, the filter will be active in the FilterBar when it is inactive in the UI (i.e the filter pill is grayed out) @See: FFrontendFilter_ShowOtherDevelopers in Content Browser
- L59 _public prototype_ `virtual void ActiveStateChanged(bool bActive) = 0;` — Notification that the filter became active or inactive
- L62 _public prototype_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) = 0;` — Called when the right-click context menu is being built for this filter
- L65 _public prototype_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const = 0;` — Can be overriden for custom FilterBar subclasses to save settings, currently not implemented in any gneeric Filter Bar
- L68 _public prototype_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) = 0;` — Can be overriden for custom FilterBar subclasses to load settings, currently not implemented in any gneeric Filter Bar
- L75 _public function_ `void SetActive(bool bActive)` — Set this filter as checked, and activates or deactivates it. @note this only works for filters registered by a widget such as SBasicFilterBar that manages them and should be called by external code rather than by the managing widget itself.
- L78 _public function_ `bool IsActive() const` — Checks whether the filter is checked/pinned and active/enabled
- L92 _public function_ `static void SetActiveInCollection(TSharedRef<FFilterBase<FilterType>> This, bool bActive, TFilterCollection<FilterType>& Collection)` — Manage the state of a filter in a collection taking into account whether it is an inverse filter or not. Adds or removes the filter from the collcetion and calls ActiveStateChanged
- L112 _public prototype_ `DECLARE_DERIVED_EVENT( FFilterBase, IFilter<FilterType>::FChangedEvent, FChangedEvent );` — IFilter implementation
- L113 _public function_ `virtual FChangedEvent& OnChanged() override`
- L115 _public function_ `TSharedPtr<FFilterCategory> GetCategory()`
- L118 _protected function_ `void BroadcastChangedEvent() const`
- L120 _protected member_ `FChangedEvent ChangedEvent;`
- L123 _protected prototype_ `DECLARE_EVENT_OneParam(FFilterBase, FSetActiveEvent, bool);` — This event is broadcast to when this filter is set Active
- L124 _protected member_ `FSetActiveEvent SetActiveEvent;`
- L126 _protected prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsActiveEvent);`
- L127 _protected member_ `FIsActiveEvent IsActiveEvent;`
- L129 _protected member_ `TSharedPtr<FFilterCategory> FilterCategory;`

#### Free symbols / members of external scopes

- L112 _delegate_ `DECLARE_DERIVED_EVENT( FFilterBase, IFilter<FilterType>::FChangedEvent, FChangedEvent );` — IFilter implementation
- L123 _delegate_ `DECLARE_EVENT_OneParam(FFilterBase, FSetActiveEvent, bool);` — This event is broadcast to when this filter is set Active
- L126 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsActiveEvent);`

### `Source/Developer/ToolWidgets/Public/Filters/GenericFilter.h` (Public)


#### class `FGenericFilter`  
`template<typename FilterType> class FGenericFilter : public FFilterBase<FilterType>`  
_L16-127_
- inherits: `FFilterBase<FilterType>`
- desc: A generic filter that can be used with the various FilterBar Widgets Takes in a Category, Name, Display Name and Delegate which specifies how to filter an item You can optionally specify a Tooltip, Icon Name or Color
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnItemFiltered, FilterType);`
- L22 _public function_ `FGenericFilter(TSharedPtr<FFilterCategory> InCategory, const FString& InName, const FText &DisplayName, FOnItemFiltered InFilterDelegate) : FFilterBase<FilterType>(InCategory), Name(InName), DisplayName(DisplayName), FilterDelegate(InFilterDelegate), Color(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))`
- L29 _public function_ `virtual FString GetName() const override` — Returns the system name for this filter
- L35 _public function_ `virtual FText GetDisplayName() const override` — Returns the human readable name for this filter
- L40 _public function_ `void SetToolTipText(const FText& InToolTip)`
- L46 _public function_ `virtual FText GetToolTipText() const override` — Returns the tooltip for this filter, shown in the filters menu
- L51 _public function_ `void SetColor(const FLinearColor& InColor)`
- L57 _public function_ `virtual FLinearColor GetColor() const override` — Returns the color this filter button will be when displayed as a button
- L62 _public function_ `void SetIconName(const FName& InIconName)`
- L68 _public function_ `virtual FName GetIconName() const override` — Returns the name of the icon to use in menu entries
- L74 _public function_ `virtual bool IsInverseFilter() const override` — Returns true if the filter should be in the list when disabled and not in the list when enabled
- L79 _public function_ `virtual bool PassesFilter( FilterType InItem ) const override`
- L92 _public function_ `virtual void ActiveStateChanged(bool bActive) override` — Notification that the filter became active or inactive
- L98 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override` — Called when the right-click context menu is being built for this filter
- L104 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override` — Can be overriden for custom FilterBar subclasses to save settings, currently not implemented in any generic Filter Bar
- L110 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override` — Can be overriden for custom FilterBar subclasses to load settings, currently not implemented in any generic Filter Bar
- L118 _protected member_ `FString Name;` — Required members
- L119 _protected member_ `FText DisplayName;`
- L120 _protected member_ `FOnItemFiltered FilterDelegate;`
- L123 _protected member_ `FText ToolTip;` — Optional members
- L124 _protected member_ `FLinearColor Color;`
- L125 _protected member_ `FName IconName;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnItemFiltered, FilterType);`

### `Source/Developer/ToolWidgets/Public/Filters/SBasicFilterBar.h` (Public)


#### class `UFilterBarContext`  
`class UFilterBarContext : public UObject`  
_L41-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: ToolMenuContext that is used to create the Add Filter Menu
- L46 _public member_ `FOnPopulateAddFilterMenu PopulateFilterMenu;`
- L47 _public member_ `FOnExtendAddFilterMenu OnExtendAddFilterMenu;`

#### enum `EFilterBarLayout`  
`enum class EFilterBarLayout : uint8`  
_L52-56_
- reflection: `UENUM()`
- desc: Describes if the filters are laid out horizontally (ScrollBox) or vertically (WrapBox)
- L54 _public enumerator_ `Horizontal`
- L55 _public enumerator_ `Vertical`

#### enum `EFilterPillStyle`  
`enum class EFilterPillStyle : uint8`  
_L60-64_
- reflection: `UENUM()`
- desc: Describes how each individual filter pill looks like
- L62 _public enumerator_ `Default` — The default style you see in the Content Browser, pills showing the color and filter name
- L63 _public enumerator_ `Basic` — Simple filter pills that only show the name like you see in the Outliner

#### class `SBasicFilterBar`  
`template<typename FilterType> class SBasicFilterBar : public SCompoundWidget`  
_L84-1781_
- inherits: `SCompoundWidget`
- L88 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFilterBarLayoutChanging, EFilterBarLayout ) DECLARE_DELEGATE( FOnFilterChanged );` — Delegate for when layout changes
- L94 _public prototype_ `DECLARE_DELEGATE_RetVal( TSharedPtr<ICustomTextFilter<FilterType>>, FCreateTextFilter);` — Delegate to create a TTextFilter used to compare FilterType with text queries
- L96 _public function_ `SLATE_BEGIN_ARGS( SBasicFilterBar<FilterType> ) : _FilterBarLayout(EFilterBarLayout::Horizontal) , _CanChangeOrientation(false) , _FilterPillStyle(EFilterPillStyle::Default) , _UseSectionsForCategories(false) , _bPinAllFrontendFilters(false) , _bSortFilters(true)`
- L106 _public function_ `SLATE_EVENT( FOnFilterChanged, OnFilterChanged ) SLATE_EVENT( FOnExtendAddFilterMenu, OnExtendAddFilterMenu ) SLATE_ARGUMENT( TArray<TSharedRef<FFilterBase<FilterType>>>, CustomFilters) SLATE_ARGUMENT(FCreateTextFilter, CreateTextFilter) SLATE_ARGUMENT(TSharedPtr<SFilterSearchBox>, FilterSearchBox) SLATE_EVENT(FOnFilterBarLayoutChanging, OnFilterBarLayoutChanging) SLATE_ARGUMENT(EFilterBarLayout, FilterBarLayout) SLATE_ARGUMENT(bool, CanChangeOrientation) SLATE_ARGUMENT(EFilterPillStyle, FilterPillStyle) SLATE_ARGUMENT(bool, UseSectionsForCategories) SLATE_ARGUMENT(bool, bPinAllFrontendFilters) SLATE_ARGUMENT(bool, bSortFilters)` — Delegate for when filters have changed
- L208 _public function_ `void AddFilter(TSharedRef<FFilterBase<FilterType>> InFilter)` — Add a custom filter to the FilterBar. NOTE: This only adds it to the Add Filter Menu, and does not automatically add it to the filter bar or activate it
- L230 _public function_ `EFilterBarLayout GetFilterLayout()`
- L235 _public function_ `virtual void SetFilterLayout(EFilterBarLayout InFilterBarLayout)`
- L263 _public function_ `static TSharedRef<SWidget> MakeAddFilterButton(TSharedRef<SBasicFilterBar<FilterType>> InFilterBar)` — Makes the button that summons the Add Filter dropdown on click
- L289 _public function_ `void AttachFilterSearchBox(TSharedPtr<SFilterSearchBox> InFilterSearchBox)` — Attach an SFilterSearchBox to this filter bar, overriding the SFilterSearchBox:: OnSaveSearchClicked event to save a search as a filter
- L771 _public function_ `bool HasAnyFilters() const` — Returns true if any filters are applied
- L777 _public function_ `TSharedPtr<FFilterBase<FilterType>> GetFilter(const FString& InName) const` — Retrieve a specific filter
- L792 _public function_ `virtual TSharedPtr< TFilterCollection<FilterType> > GetAllActiveFilters()` — Use this function to get all currently active filters (to filter your items) Not const on purpose: Subclasses might need to update the filter collection before getting it
- L798 _public function_ `void EnableAllFilters()` — Enable all the filters that are currently visible on the filter bar
- L813 _public function_ `void DisableAllFilters()` — Disable all the filters that are currently visible on the filter bar
- L828 _public function_ `virtual void RemoveAllFilters()` — Remove all filters from the filter bar, while disabling any active ones
- L851 _public function_ `void SetFilterCheckState(const TSharedPtr<FFilterBase<FilterType>>& InFilter, ECheckBoxState InCheckState)` — Set the check box state of the specified filter (in the filter drop down) and pin/unpin a filter widget on/from the filter bar. When a filter is pinned (was not already pinned), it is activated and deactivated when unpinned.
- L874 _public function_ `ECheckBoxState GetFilterCheckState(const TSharedPtr<FFilterBase<FilterType>>& InFilter) const` — Returns the check box state of the specified filter (in the filter drop down). This tells whether the filter is pinned or not on the filter bar, but not if filter is active or not. @see IsFilterActive().
- L880 _public function_ `bool IsFilterActive(const TSharedPtr<FFilterBase<FilterType>>& InFilter) const` — Returns true if the specified filter is both checked (pinned on the filter bar) and active (contributing to filter the result).
- L896 _public function_ `bool GetSortFiltersAlphabetically() const` — Are we sorting filters alphabetically
- L902 _public function_ `void SetSortFiltersAlphabetically(bool bInSort)` — Set filtering method for filters
- L914 _protected function_ `const FSlateBrush* GetFilterBadgeIcon() const` — Overlay for filter icon, badge if there are any active filters
- L928 _protected function_ `virtual void RemoveAllButThis(const TSharedRef<SFilter>& FilterToKeep)` — Remove all filters except the specified one
- L953 _protected function_ `void AddWidgetToLayout(const TSharedRef<SWidget> WidgetToAdd)` — Add a widget to the current filter layout
- L987 _protected function_ `void RemoveWidgetFromLayout(const TSharedRef<SWidget> WidgetToRemove)` — Remove a widget from the current filter layout
- L1000 _protected function_ `void SetFrontendFilterActive(const TSharedRef<FFilterBase<FilterType>>& Filter, bool bActive)` — Sets the active state of a frontend filter.
- L1006 _protected function_ `TSharedRef<SFilter> AddFilterToBar(const TSharedRef<FFilterBase<FilterType>>& Filter)` — 'Activate' A filter by adding it to the filter bar, does not turn it on
- L1026 _protected function_ `void AddFilterToBar(const TSharedRef<SFilter>& FilterToAdd)` — 'Activate' A filter by adding it to the filter bar, does not turn it on
- L1043 _protected function_ `virtual void Tick(const FGeometry& InGeometry, const double InCurrentTime, const float InDeltaTime) override` — Updates filters in the layout if requested
- L1083 _protected function_ `void EnableOnlyThisFilter(const TSharedRef<SFilter>& FilterToEnable)` — Handler for when the enable only this button was clicked on a single filter
- L1099 _protected function_ `void RemoveFilter(const TSharedRef<FFilterBase<FilterType>>& InFilterToRemove, bool ExecuteOnFilterChanged= true)` — Remove a filter from the filter bar
- L1125 _protected function_ `virtual void RemoveFilter(const TSharedRef<SFilter>& FilterToRemove)` — Remove a filter from the filter bar
- L1139 _protected function_ `void RemoveFilterAndUpdate(const TSharedRef<SFilter>& FilterToRemove)` — Remove a filter from the filter bar
- L1148 _protected function_ `void FrontendFilterChanged(TSharedRef<FFilterBase<FilterType>> FrontendFilter)` — Handler for when a frontend filter state has changed
- L1168 _protected function_ `void CreateOtherFiltersMenuCategory(FToolMenuSection& Section, TSharedPtr<FFilterCategory> MenuCategory) const` — Handler for when the add filter menu is populated by a non-category
- L1190 _protected function_ `void CreateOtherFiltersMenuCategory(UToolMenu* InMenu, TSharedPtr<FFilterCategory> MenuCategory) const` — Handler for when the add filter menu is populated by a non-category
- L1196 _protected function_ `void FrontendFilterClicked(TSharedRef<FFilterBase<FilterType>> FrontendFilter)` — Handler for a frontend filter is clicked
- L1210 _protected function_ `bool IsFrontendFilterInUse(TSharedRef<FFilterBase<FilterType>> FrontendFilter) const` — Handler to check if a frontend filter is in use
- L1224 _protected function_ `void FrontendFilterCategoryClicked(TSharedPtr<FFilterCategory> MenuCategory)` — Handler for when a filter category is clicked
- L1255 _protected function_ `bool IsFrontendFilterCategoryInUse(TSharedPtr<FFilterCategory> MenuCategory) const` — Handler to check if a filter category is in use
- L1269 _protected function_ `ECheckBoxState IsFrontendFilterCategoryChecked(TSharedPtr<FFilterCategory> MenuCategory) const` — Handler to determine the "checked" state of a frontend filter category in the filter dropdown
- L1305 _protected function_ `void OnResetFilters()` — Called when reset filters option is pressed
- L1311 _protected function_ `void OnSetFilterActive(bool bActive, TWeakPtr<FFilterBase<FilterType>> InWeakFilter)` — Called externally to check/pin a filter, and activates/deactivates it
- L1336 _protected function_ `bool OnIsFilterActive(TWeakPtr<FFilterBase<FilterType>> InWeakFilter)` — Called externally to determine if a filter has been checked/pinned and activated
- L1355 _protected function_ `void CustomTextFilterClicked(ECheckBoxState CheckBoxState, TSharedRef<ICustomTextFilter<FilterType>> Filter)` — Handler for when a checkbox next to a custom text filter is clicked
- L1370 _protected function_ `virtual void OnCreateCustomTextFilter(const FCustomTextFilterData& InFilterData, bool bApplyFilter)` — Handler for when a custom text filter is created
- L1399 _protected function_ `virtual void OnModifyCustomTextFilter(const FCustomTextFilterData& InFilterData, TSharedPtr<ICustomTextFilter<FilterType>> InFilter)` — Handler for when a custom text filter is modified
- L1429 _protected function_ `virtual void OnDeleteCustomTextFilter(const TSharedPtr<ICustomTextFilter<FilterType>> InFilter)` — Handler for when a custom text filter is deleted
- L1447 _protected function_ `virtual void OnCancelCustomTextFilterDialog()` — Handler to close the custom text filter dialog
- L1455 _protected function_ `void GetAllCustomTextFilterLabels(TArray<FText>& OutFilterLabels)`
- L1465 _protected function_ `void CreateCustomTextFilterWindow(const FCustomTextFilterData& CustomTextFilterData, TSharedPtr<ICustomTextFilter<FilterType>> InFilter)` — Creates a dialog box with the SCustomTextFilterDialog Widget
- L1501 _protected function_ `void CreateAddCustomTextFilterWindow()` — Creates a dialog box to Add a custom text filter
- L1507 _protected function_ `void CreateEditCustomTextFilterWindow(TSharedPtr<ICustomTextFilter<FilterType>> InFilter)` — Creates a dialog box to Edit an existing custom text filter
- L1520 _protected function_ `void CreateCustomTextFilterFromSearch(const FText& InSearchText)` — Creates a dialog to add a custom text filter from the given search text
- L1530 _protected function_ `void CreateTextFiltersMenu(UToolMenu* InMenu)` — Populate the Custom Filters submenu in the Add Filter dropdown
- L1613 _protected function_ `void PopulateCommonFilterSections(UToolMenu* Menu)` — Helper function to add common sections to the Add Filter Menu
- L1641 _protected function_ `void PopulateCustomFilters(UToolMenu* Menu)` — Helper function to add all custom filters to the Add Filter Menu
- L1675 _protected function_ `void RequestFiltersUpdate()` — Request a filter list update next tick
- L1683 _private function_ `virtual TSharedRef<SWidget> MakeAddFilterMenu()` — Handler for when the add filter button was clicked
- L1711 _private function_ `void PopulateAddFilterMenu(UToolMenu* Menu)` — Function to populate the add filter menu
- L1719 _private member_ `bool bRequestFiltersUpdate = false;` — Whether a refresh is requested next tick to re-render filters in the bar
- L1724 _protected member_ `TSharedPtr<SWrapBox> HorizontalFilterBox;` — The horizontal wrap box which contains all the filters (used in the horizontal layout)
- L1727 _protected member_ `TSharedPtr<SScrollBox> VerticalFilterBox;` — The vertical scroll box which contains all the filters (used in the vertical layout)
- L1730 _protected member_ `TSharedPtr<SWidgetSwitcher> FilterBox;` — The widget switcher containing the horizontal and vertical filter widgets
- L1733 _protected member_ `EFilterBarLayout FilterBarLayout;` — The current Filter Layout being used
- L1736 _protected member_ `FOnFilterBarLayoutChanging OnFilterBarLayoutChanging;` — Delegate for when the layout is changed
- L1739 _protected member_ `TArray< TSharedRef<SFilter> > Filters;` — All SFilters in the list
- L1742 _protected member_ `TArray< TSharedRef< FFilterBase<FilterType> > > AllFrontendFilters;` — All possible filter objects
- L1745 _protected member_ `TSharedPtr< TFilterCollection<FilterType> > ActiveFilters;` — Currently active filter objects
- L1748 _protected member_ `TArray< TSharedPtr<FFilterCategory> > AllFilterCategories;` — All filter categories (for menu construction)
- L1751 _protected member_ `FOnFilterChanged OnFilterChanged;` — Delegate for when filters have changed
- L1754 _protected member_ `FOnExtendAddFilterMenu OnExtendAddFilterMenu;` — Delegate to extend the AddFilter Menu
- L1757 _protected member_ `FCreateTextFilter CreateTextFilter;` — A delegate used to create a TTextFilter for FilterType
- L1760 _protected member_ `TArray< TSharedRef< ICustomTextFilter<FilterType> > > CustomTextFilters;` — Custom text filters that a user can create
- L1763 _protected member_ `TWeakPtr<SWindow> CustomTextFilterWindow;` — The window containing the custom text filter dialog
- L1766 _protected member_ `bool bCanChangeOrientation;` — Whether the orientation can be changed after initailization
- L1769 _protected member_ `bool bUseSectionsForCategories;` — Whether to use submenus or sections for categories in the filter menu
- L1772 _protected member_ `bool bPinAllFrontendFilters;` — Whether to pin all front end filters by default. Will add them from the Add Filter menu to the UI, but does not necessarily activate them.
- L1775 _protected member_ `EFilterPillStyle FilterPillStyle;` — Determines how each individual pill looks like
- L1778 _protected member_ `bool bSortFiltersAlphabetically;` — Determines whether filters are sorted in the bar or appear in the order they are added

#### class `SBasicFilterBar::SFilterCheckBox`  
`class SFilterCheckBox : public SCheckBox`  
_L301-366_
- inherits: `SCheckBox`
- desc: A class for check boxes in the filter list. If you double click a filter checkbox, you will enable it and disable all others
- L305 _public function_ `void SetOnFilterCtrlClicked(const FOnClicked& NewFilterCtrlClicked)`
- L310 _public function_ `void SetOnFilterAltClicked(const FOnClicked& NewFilterAltClicked)`
- L315 _public function_ `void SetOnFilterDoubleClicked( const FOnClicked& NewFilterDoubleClicked )`
- L320 _public function_ `void SetOnFilterMiddleButtonClicked( const FOnClicked& NewFilterMiddleButtonClicked )`
- L325 _public function_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override`
- L337 _public function_ `virtual FReply OnMouseButtonUp( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override`
- L362 _private member_ `FOnClicked OnFilterCtrlClicked;`
- L363 _private member_ `FOnClicked OnFilterAltClicked;`
- L364 _private member_ `FOnClicked OnFilterDoubleClicked;`
- L365 _private member_ `FOnClicked OnFilterMiddleButtonClicked;`

#### class `SBasicFilterBar::SFilter`  
`class SFilter : public SCompoundWidget`  
_L373-766_
- inherits: `SCompoundWidget`
- desc: A single filter in the filter list. Can be removed by clicking the remove button on it.
- L376 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnRequestRemove, const TSharedRef<SFilter>& );`
- L377 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnRequestRemoveAllButThis, const TSharedRef<SFilter>& );`
- L378 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnRequestEnableOnly, const TSharedRef<SFilter>& );`
- L379 _public prototype_ `DECLARE_DELEGATE( FOnRequestEnableAll );`
- L380 _public prototype_ `DECLARE_DELEGATE( FOnRequestDisableAll );`
- L381 _public prototype_ `DECLARE_DELEGATE( FOnRequestRemoveAll );`
- L383 _public function_ `SLATE_BEGIN_ARGS( SFilter )`
- L386 _public function_ `SLATE_ARGUMENT( TSharedPtr<FFilterBase<FilterType>>, FrontendFilter ) SLATE_EVENT( SBasicFilterBar<FilterType>::FOnFilterChanged, OnFilterChanged ) SLATE_EVENT( FOnRequestRemove, OnRequestRemove ) SLATE_EVENT( FOnRequestEnableOnly, OnRequestEnableOnly ) SLATE_EVENT(FOnRequestEnableAll, OnRequestEnableAll) SLATE_EVENT( FOnRequestDisableAll, OnRequestDisableAll ) SLATE_EVENT( FOnRequestRemoveAll, OnRequestRemoveAll ) SLATE_EVENT( FOnRequestRemoveAllButThis, OnRequestRemoveAllButThis ) SLATE_ARGUMENT(EFilterPillStyle, FilterPillStyle) SLATE_END_ARGS() void Construct( const FArguments& InArgs )` — If this is an front end filter, this is the filter object
- L439 _public function_ `void SetEnabled(bool InEnabled, bool InExecuteOnFilterChanged = true)` — Sets whether or not this filter is applied to the combined filter
- L452 _public function_ `bool IsEnabled() const` — Returns true if this filter contributes to the combined filter
- L459 _public function_ `const TSharedPtr<FFilterBase<FilterType>>& GetFrontendFilter() const` — If this is an front end filter, this is the filter object
- L465 _public function_ `virtual FText GetFilterDisplayName() const` — Returns the display name for this filter
- L481 _public function_ `virtual FString GetFilterName() const`
- L494 _protected function_ `void Construct_Internal(EFilterPillStyle InFilterPillStyle)` — Function that constructs the actual widget for subclasses to call
- L563 _protected function_ `void FilterToggled(ECheckBoxState NewState)` — Handler for when the filter checkbox is clicked
- L570 _protected function_ `FReply FilterCtrlClicked()` — Handler for when the filter checkbox is clicked and a control key is pressed
- L577 _protected function_ `FReply FilterAltClicked()` — Handler for when the filter checkbox is clicked and an alt key is pressed
- L584 _protected function_ `FReply FilterDoubleClicked()` — Handler for when the filter checkbox is double clicked
- L595 _protected function_ `FReply FilterMiddleButtonClicked()` — Handler for when the filter checkbox is middle button clicked
- L602 _protected function_ `TSharedRef<SWidget> GetRightClickMenuContent()` — Handler to create a right click menu
- L669 _protected function_ `void RemoveFilter()` — Removes this filter from the filter list
- L676 _protected function_ `void RemoveAllButThis()` — Remove all but this filter from the filter list.
- L683 _protected function_ `void EnableOnly()` — Enables only this filter from the filter list
- L690 _protected function_ `void EnableAllFilters()` — Enables all filters in the list
- L696 _protected function_ `void DisableAllFilters()` — Disables all active filters in the list
- L702 _protected function_ `void RemoveAllFilters()` — Removes all filters in the list
- L708 _protected function_ `ECheckBoxState IsChecked() const` — Handler to determine the "checked" state of the filter checkbox
- L714 _protected function_ `FSlateColor GetFilterImageColorAndOpacity() const` — Handler to determine the color of the checkbox when it is checked
- L719 _protected function_ `EVisibility GetFilterOverlayVisibility() const`
- L725 _protected function_ `FMargin GetFilterNamePadding() const` — Handler to determine the padding of the checkbox text when it is pressed
- L732 _protected member_ `FOnFilterChanged OnFilterChanged;` — Invoked when the filter toggled
- L735 _protected member_ `FOnRequestRemove OnRequestRemove;` — Invoked when a request to remove this filter originated from within this filter
- L738 _protected member_ `FOnRequestEnableOnly OnRequestEnableOnly;` — Invoked when a request to enable only this filter originated from within this filter
- L741 _protected member_ `FOnRequestEnableAll OnRequestEnableAll;` — Invoked when a request to enable all filters originated from within this filter
- L744 _protected member_ `FOnRequestDisableAll OnRequestDisableAll;` — Invoked when a request to disable all filters originated from within this filter
- L747 _protected member_ `FOnRequestDisableAll OnRequestRemoveAll;` — Invoked when a request to remove all filters originated from within this filter
- L750 _protected member_ `FOnRequestRemoveAllButThis OnRequestRemoveAllButThis;` — Invoked when a request to remove all filters except this one originated from within this filter
- L753 _protected member_ `bool bEnabled;` — true when this filter should be applied to the search
- L756 _protected member_ `TSharedPtr<FFilterBase<FilterType>> FrontendFilter;` — If this is an front end filter, this is the filter object
- L759 _protected member_ `TSharedPtr<SFilterCheckBox> ToggleButtonPtr;` — The button to toggle the filter on or off
- L762 _protected member_ `FLinearColor FilterColor;` — The color of the checkbox for this filter
- L765 _protected member_ `TAttribute<FText> FilterToolTip;` — The tooltip for this filter

#### struct `FFrontendFilterExternalActivationHelper`  
`template<typename FilterType> struct FFrontendFilterExternalActivationHelper`  
_L1785-1793_
- desc: Helper struct to avoid friending the whole of SBasicFilterBarSBasicFilterBar
- L1787 _public function_ `static void BindToFilter(TSharedRef<SBasicFilterBar<FilterType>> InFilterList, TSharedRef<FFilterBase<FilterType>> InFrontendFilter)`

#### Free symbols / members of external scopes

- L32 _macro_ `#define LOCTEXT_NAMESPACE "FilterBar"`
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPopulateAddFilterMenu, UToolMenu*) DECLARE_DELEGATE_OneParam( FOnExtendAddFilterMenu, UToolMenu* );` — Delegate used by SBasicFilterBar to populate the add filter menu
- L35 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPopulateAddFilterMenu, UToolMenu*) DECLARE_DELEGATE_OneParam( FOnExtendAddFilterMenu, UToolMenu* );` — Delegate used by SBasicFilterBar to populate the add filter menu
- L37 _delegate_ `DECLARE_DELEGATE_OneParam( FOnExtendAddFilterMenu, UToolMenu* );` — Delegate to extend a menu after it has been generated dynamically.
- L88 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFilterBarLayoutChanging, EFilterBarLayout ) DECLARE_DELEGATE( FOnFilterChanged );` — Delegate for when layout changes
- L91 _delegate_ `DECLARE_DELEGATE( FOnFilterChanged );` — Delegate for when filters have changed
- L94 _delegate_ `DECLARE_DELEGATE_RetVal( TSharedPtr<ICustomTextFilter<FilterType>>, FCreateTextFilter);` — Delegate to create a TTextFilter used to compare FilterType with text queries
- L175 _function_ `` (scope `SBasicFilterBar::SLATE_EVENT`)
- L376 _delegate_ `DECLARE_DELEGATE_OneParam( FOnRequestRemove, const TSharedRef<SFilter>& );`
- L377 _delegate_ `DECLARE_DELEGATE_OneParam( FOnRequestRemoveAllButThis, const TSharedRef<SFilter>& );`
- L378 _delegate_ `DECLARE_DELEGATE_OneParam( FOnRequestEnableOnly, const TSharedRef<SFilter>& );`
- L379 _delegate_ `DECLARE_DELEGATE( FOnRequestEnableAll );`
- L380 _delegate_ `DECLARE_DELEGATE( FOnRequestDisableAll );`
- L381 _delegate_ `DECLARE_DELEGATE( FOnRequestRemoveAll );`
- L544 _function_ `.IsEnabled_Lambda([this] {return bEnabled;}) ] ] ];` (scope `SBasicFilterBar::SFilter::Construct_Internal`)
- L1053 _function_ `` (scope `SBasicFilterBar::Tick`)
- L1557 _function_ `` (scope `SBasicFilterBar::CreateTextFiltersMenu`)
- L1623 _function_ `FExecuteAction::CreateSP(this, &SBasicFilterBar<FilterType>::OnResetFilters), FCanExecuteAction::CreateLambda([this]() { return HasAnyFilters(); })) );` (scope `SBasicFilterBar::PopulateCommonFilterSections`)
- L1693 _function_ `` (scope `SBasicFilterBar::MakeAddFilterMenu`)

### `Source/Developer/ToolWidgets/Public/Filters/SCustomTextFilterDialog.h` (Public)


#### class `SCustomTextFilterDialog`  
`class SCustomTextFilterDialog : public SCompoundWidget`  
_L13-102_
- inherits: `SCompoundWidget`
- L17 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnCreateFilter, const FCustomTextFilterData& , bool );`
- L18 _public prototype_ `DECLARE_DELEGATE(FOnDeleteFilter);`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnModifyFilter, const FCustomTextFilterData& );`
- L20 _public prototype_ `DECLARE_DELEGATE(FOnCancelClicked);`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGetFilterLabels, TArray<FText> & );`
- L23 _public function_ `SLATE_BEGIN_ARGS(SCustomTextFilterDialog) : _InEnableColorEditing(true)`
- L28 _public prototype_ `SLATE_ARGUMENT(FCustomTextFilterData, FilterData) SLATE_ARGUMENT(bool, InEditMode) SLATE_ARGUMENT(bool, InEnableColorEditing) SLATE_EVENT(FOnCreateFilter, OnCreateFilter) SLATE_EVENT(FOnDeleteFilter, OnDeleteFilter) SLATE_EVENT(FOnCancelClicked, OnCancelClicked) SLATE_EVENT(FOnModifyFilter, OnModifyFilter) SLATE_EVENT(FOnGetFilterLabels, OnGetFilterLabels) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — The filter that this dialog is creating/editing
- L59 _protected prototype_ `FReply ColorBlock_OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Handler for when the color block is clicked to open the color picker
- L61 _protected prototype_ `void HandleColorValueChanged(FLinearColor NewValue);`
- L63 _protected prototype_ `FReply OnDeleteButtonClicked() const;`
- L65 _protected prototype_ `FReply OnCreateFilterButtonClicked(bool bApplyFilter) const;`
- L67 _protected prototype_ `FReply OnCancelButtonClicked() const;`
- L69 _protected prototype_ `FReply OnModifyButtonClicked() const;`
- L71 _protected prototype_ `bool CheckFilterValidity() const;`
- L76 _protected member_ `bool bInEditMode;` — True if we are editing a filter, false if we are creating a new filter
- L79 _protected member_ `bool bEnableColorEditing;` — True if we want to give the user the ability to pick a color for the filter in the edit/create menu
- L82 _protected member_ `FCustomTextFilterData FilterData;` — The current filter data we are editing
- L85 _protected member_ `FCustomTextFilterData InitialFilterData;` — The initial, unedited filter data we were provided
- L87 _protected member_ `FOnCreateFilter OnCreateFilter;`
- L89 _protected member_ `FOnDeleteFilter OnDeleteFilter;`
- L91 _protected member_ `FOnCancelClicked OnCancelClicked;`
- L93 _protected member_ `FOnModifyFilter OnModifyFilter;`
- L95 _protected member_ `FOnGetFilterLabels OnGetFilterLabels;`
- L98 _protected member_ `TSharedPtr<SColorBlock> ColorBlock;` — The color block widget that edits the filter color
- L101 _protected member_ `TSharedPtr<SEditableTextBox> FilterLabelTextBox;` — The widget that edits the filter label

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TOOLWIDGETS_API`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCreateFilter, const FCustomTextFilterData& , bool );`
- L18 _delegate_ `DECLARE_DELEGATE(FOnDeleteFilter);`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnModifyFilter, const FCustomTextFilterData& );`
- L20 _delegate_ `DECLARE_DELEGATE(FOnCancelClicked);`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetFilterLabels, TArray<FText> & );`

### `Source/Developer/ToolWidgets/Public/Filters/SFilterSearchBox.h` (Public)


#### class `SFilterSearchBox`  
`class SFilterSearchBox : public SCompoundWidget`  
_L22-164_
- inherits: `SCompoundWidget`
- desc: A SearchBox widget that contains support for displaying search history When used with a FilterBar widget (@see SBasicFilterBar or SFilterBar), it allows the user to save searches from the history as filter pills
- L26 _public function_ `DECLARE_DELEGATE_OneParam(FOnSaveSearchClicked, const FText&) SLATE_BEGIN_ARGS(SFilterSearchBox) : _OnTextChanged() , _OnTextCommitted() , _InitialText() , _HintText() , _ShowSearchHistory(true) , _MaxSearchHistory(5) , _DelayChangeNotificationsWhileTyping( false ) , _DelayChangeNotificationsWhileTypingSeconds(0.25f)`
- L40 _public prototype_ `SLATE_EVENT( FOnTextChanged, OnTextChanged ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_ATTRIBUTE( FText, InitialText ) SLATE_ATTRIBUTE( FText, HintText ) SLATE_ATTRIBUTE(bool, ShowSearchHistory) SLATE_ARGUMENT(int32, MaxSearchHistory) SLATE_ARGUMENT(TArrayView<FText>, SearchHistory) SLATE_ATTRIBUTE( bool, DelayChangeNotificationsWhileTyping ) SLATE_ATTRIBUTE( float, DelayChangeNotificationsWhileTypingSeconds ) SLATE_EVENT(FOnKeyDown, OnKeyDownHandler) SLATE_EVENT(FOnSaveSearchClicked, OnSaveSearchClicked) PRAGMA_DISABLE_EXPERIMENTAL_WARNINGS SLATE_ARGUMENT(TSharedPtr<SWidget>, ExtraWidget) PRAGMA_ENABLE_EXPERIMENTAL_WARNINGS` — Invoked whenever the text changes
- L86 _public prototype_ `void SetText(const TAttribute< FText >& InNewText);` — Sets the text string currently being edited
- L89 _public prototype_ `FText GetText() const;` — Get the text string currently being edited
- L92 _public prototype_ `TArray<FText> GetSearchHistory() const;` — Get the current Search History excluding the placeholder empty search text
- L95 _public prototype_ `void SetError( const FText& InError );` — Set or clear the current error reporting information for this search box
- L96 _public prototype_ `void SetError( const FString& InError );`
- L99 _public prototype_ `void OnFocusLost(const FFocusEvent& InFocusEvent) override;` — SWidget interface
- L100 _public prototype_ `virtual bool HasKeyboardFocus() const override;`
- L101 _public prototype_ `bool SupportsKeyboardFocus() const;`
- L102 _public prototype_ `FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent );`
- L105 _public prototype_ `void SetOnSaveSearchHandler(FOnSaveSearchClicked InOnSaveSearchHandler);` — Show a + button next to the current search, and set the handler for when that is clicked
- L108 _public prototype_ `FTextSelection GetSelection() const;` — Get the current selection
- L111 _public prototype_ `void SelectText(const FTextLocation& InSelectionStart, const FTextLocation& InCursorLocation);` — Select a block of text
- L116 _private prototype_ `void HandleTextChanged(const FText& NewText);` — Handler for when text in the editable text box changed
- L119 _private prototype_ `void HandleTextCommitted(const FText& NewText, ETextCommit::Type CommitType);` — Handler for when text in the editable text box changed
- L122 _private prototype_ `void UpdateSearchHistory(const FText &NewText);` — Add the given search text to the search history
- L125 _private prototype_ `void OnSelectionChanged( TSharedPtr<FText> NewValue, ESelectInfo::Type SelectInfo );` — Called by SListView when the selection changes in the search history list
- L128 _private prototype_ `TSharedRef<ITableRow> MakeSearchHistoryRowWidget(TSharedPtr<FText> SearchText, const TSharedRef<STableViewBase>& OwnerTable);` — Makes the widget for a single search history row in the list view
- L131 _private prototype_ `FReply OnClickedSearchHistory();` — Handler for when the chevron to open the search history is clicked
- L134 _private prototype_ `EVisibility GetSearchHistoryVisibility() const;` — Whether the search history dropdown chevron is visible
- L139 _private member_ `TAttribute<bool> bShowSearchHistory;` — Whether we are showing the search history
- L142 _private member_ `TSharedPtr<SFilterSearchBoxImpl> SearchBox;` — The actual Search Box
- L145 _private member_ `FOnTextChanged OnTextChanged;` — Delegate for when text is changed in the edit box
- L148 _private member_ `FOnTextCommitted OnTextCommitted;` — Delegate for when text is changed in the edit box
- L151 _private member_ `int32 MaxSearchHistory;` — The max amount of items to show in the Search History
- L154 _private member_ `TArray<TSharedPtr<FText>> SearchHistory;` — The array containing the last few searched items
- L157 _private member_ `TSharedPtr< SMenuAnchor > SearchHistoryBox;` — Search History elements
- L160 _private member_ `TSharedPtr<SListView< TSharedPtr<FText>>> SearchHistoryListView;` — The ListView containing our search history
- L163 _private member_ `TSharedPtr<FText> EmptySearchHistoryText;` — The Text that shows up when there are no items in the search history

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLWIDGETS_API`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSaveSearchClicked, const FText&) SLATE_BEGIN_ARGS(SFilterSearchBox) : _OnTextChanged() , _OnTextCommitted() , _InitialText() , _HintText() , _ShowSearchHistory(true) , _MaxSearchHistory(5) , _DelayChangeNotificationsWhileTyping( false ) , _DelayChangeNotificationsWhileTypingSeconds(0.25f) {} SLATE_EVENT( FOnTextChanged, OnTextChanged ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_ATTRIBUTE( FText, InitialText ) SLATE_ATTRIBUTE( FText, HintText ) SLATE_ATTRIBUTE(bool, ShowSearchHistory) SLATE_ARGUMENT(int32, MaxSearchHistory) SLATE_ARGUMENT(TArrayView<FText>, SearchHistory) SLATE_ATTRIBUTE( bool, DelayChangeNotificationsWhileTyping ) SLATE_ATTRIBUTE( float, DelayChangeNotificationsWhileTypingSeconds )`

### `Source/Developer/ToolWidgets/Public/Overlay/DragBoxPosition.h` (Public)


#### struct `FToolWidget_DragBoxPosition`  
`struct FToolWidget_DragBoxPosition`  
_L10-36_
- reflection: `USTRUCT()`
- desc: Used to restore position of widget in SDraggableBoxOverlay.
- L15 _public member_ `FVector2f RelativeOffset = FVector2f::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Layout")`
- L18 _public member_ `TEnumAsByte<EHorizontalAlignment> HAlign = HAlign_Left;` — `UPROPERTY(EditAnywhere, Category = "Layout")`
- L21 _public member_ `TEnumAsByte<EVerticalAlignment> VAlign = VAlign_Bottom;` — `UPROPERTY(EditAnywhere, Category = "Layout")`
- L23 _public prototype_ `FToolWidget_DragBoxPosition() = default;`
- L24 _public function_ `explicit FToolWidget_DragBoxPosition( const FVector2f& RelativeOffset, const TEnumAsByte<EHorizontalAlignment>& HAlign, const TEnumAsByte<EVerticalAlignment>& VAlign ) : RelativeOffset(RelativeOffset) , HAlign(HAlign) , VAlign(VAlign)`
- L32 _public function_ `bool operator==(const FToolWidget_DragBoxPosition& Other) const`

### `Source/Developer/ToolWidgets/Public/Overlay/SDraggableBoxOverlay.h` (Public)


#### enum `UE::ToolWidgets::EResizeEdges`  
`enum class EResizeEdges : uint8`  
_L20-28_
- desc: Flags that specify which edges of an SDraggableBoxOverlay are user-resizable.
- L22 _public enumerator_ `None = 0`
- L23 _public enumerator_ `Left = 1 << 0`
- L24 _public enumerator_ `Right = 1 << 1`
- L25 _public enumerator_ `Top = 1 << 2`
- L26 _public enumerator_ `Bottom = 1 << 3`
- L27 _public enumerator_ `All = Left | Right | Top | Bottom`

#### class `UE::ToolWidgets::SDraggableBoxOverlay`  
`class SDraggableBoxOverlay : public SCompoundWidget`  
_L39-174_
- inherits: `SCompoundWidget`
- desc: Class that can be used to place a draggable box into a viewport or some other large widget as an overlay. Just place the widget that you want to be draggable as the contents. This overlay will remain confined to the bounds of the viewport dimensions. It anchors the content to the corners of the parent widget: e.g. when a user drags it from the bottom-left to the bottom-right corner and drags the right side of the viewport, the widget moves relative to the right side.
- L43 _public function_ `SLATE_BEGIN_ARGS(SDraggableBoxOverlay) : _HAlign(HAlign_Left) , _VAlign(VAlign_Bottom) , _InitialAlignmentOffset(FVector2f::ZeroVector) , _Draggable(true) , _Resizable(EResizeEdges::None) , _ResizeHandleThickness(5.f) , _MinimumBoxWidth(TOptional<float>(20.f)) , _MinimumBoxHeight(TOptional<float>(20.f))`
- L54 _public prototype_ `SLATE_ARGUMENT(EHorizontalAlignment, HAlign) SLATE_ARGUMENT(EVerticalAlignment, VAlign) SLATE_ARGUMENT(FVector2f, InitialAlignmentOffset) SLATE_ATTRIBUTE_DEPRECATED(bool, IsDraggable, 5.8, "Use Draggable instead.") SLATE_ATTRIBUTE(bool, Draggable) SLATE_ATTRIBUTE(bool, DragOverridesCenterAlignment) SLATE_EVENT(FSimpleDelegate, OnUserDraggedToNewPosition) SLATE_ARGUMENT(EResizeEdges, Resizable) SLATE_ARGUMENT(float, ResizeHandleThickness) SLATE_ATTRIBUTE(TOptional<float>, MinimumBoxWidth) SLATE_ATTRIBUTE(TOptional<float>, MinimumBoxHeight) SLATE_ATTRIBUTE(TOptional<float>, MaximumBoxWidth) SLATE_ATTRIBUTE(TOptional<float>, MaximumBoxHeight) SLATE_ARGUMENT(TOptional<float>, WidthOverride) SLATE_ARGUMENT(TOptional<float>, HeightOverride) SLATE_EVENT(FSimpleDelegate, OnUserResized) SLATE_DEFAULT_SLOT(FArguments, Content)` — Use this to specify whether to align to the left or right. Center and Fill prevent repositioning horizontally.
- L99 _public prototype_ `FVector2f GetBoxAlignmentOffset() const;` — @return The current position of the box on the viewport relative to HAlign and VAlign.
- L108 _public prototype_ `void SetBoxAlignmentOffset(const FVector2f& InOffset, bool bInRecomputeAnchorPoints = true);` — Sets the content's position relative to the current anchor points. @param InOffset Offset relative to the current HAlign and VAlign, e.g. X = 100 means an offset of 100 from the left or right widget side. @param bInRecomputeAnchorPoints Whether you want HAlign and VAlign recomputed, e.g. if HAlign is currently left, parent is 200 wide, and InOffset.X == 150, this would recompute HAlign to be right.
- L110 _public prototype_ `EHorizontalAlignment GetBoxHorizontalAlignment() const;`
- L111 _public prototype_ `void SetBoxHorizontalAlignment(EHorizontalAlignment InAlignment);`
- L113 _public prototype_ `EVerticalAlignment GetBoxVerticalAlignment() const;`
- L114 _public prototype_ `void SetBoxVerticalAlignment(EVerticalAlignment InAlignment);`
- L117 _public prototype_ `FToolWidget_DragBoxPosition GetDragBoxPosition() const;` — Gets information to restore this content's position. This is useful for saving in config files.
- L119 _public prototype_ `void SetDragBoxPosition(const FToolWidget_DragBoxPosition& InPosition);` — Sets the content's position. This is useful for loading a widget position saved in a config file.
- L122 _public prototype_ `void RestoreFromDragBoxPosition(const FToolWidget_DragBoxPosition& InWidgetPosition);` — `UE_DEPRECATED(5.8, "Use SetDragBoxPosition instead.")` — Restores the content position. This is useful for loading a widget position saved in a config file.
- L125 _public prototype_ `TOptional<float> GetWidthOverride() const;` — Returns the explicit width override set by a user resize, or unset if the box is content-sized on this axis.
- L127 _public prototype_ `void SetWidthOverride(const TOptional<float>& NewWidth);` — Sets an explicit width override. Pass an unset optional to revert to content sizing on this axis.
- L130 _public prototype_ `TOptional<float> GetHeightOverride() const;` — Returns the explicit height override set by a user resize, or unset if the box is content-sized on this axis.
- L132 _public prototype_ `void SetHeightOverride(const TOptional<float>& NewHeight);` — Sets an explicit height override. Pass an unset optional to revert to content sizing on this axis.
- L134 _public prototype_ `TOptional<float> GetMinimumBoxWidth() const;`
- L135 _public prototype_ `TOptional<float> GetMaximumBoxWidth() const;`
- L136 _public prototype_ `TOptional<float> GetMinimumBoxHeight() const;`
- L137 _public prototype_ `TOptional<float> GetMaximumBoxHeight() const;`
- L142 _protected member_ `TSharedPtr<SBox> Container;` — Contains the DraggableBox and repositions it relative to our parent.
- L144 _protected member_ `TSharedPtr<SWidget> DraggableBox;` — Contains the content and handles the drag-drop behaviour.
- L147 _protected member_ `TOptional<float> WidthOverride;` — Width override set by a user resize operation. Unset means the box sizes itself to its content on this axis.
- L149 _protected member_ `TOptional<float> HeightOverride;` — Height override set by a user resize operation. Unset means the box sizes itself to its content on this axis.
- L151 _protected member_ `TAttribute<TOptional<float>> MinimumBoxWidth;` — Minimum allowed box width when the user resizes.
- L153 _protected member_ `TAttribute<TOptional<float>> MinimumBoxHeight;` — Minimum allowed box height when the user resizes.
- L155 _protected member_ `TAttribute<TOptional<float>> MaximumBoxWidth;` — Maximum allowed box width when the user resizes.
- L157 _protected member_ `TAttribute<TOptional<float>> MaximumBoxHeight;` — Maximum allowed box height when the user resizes.
- L160 _protected member_ `EHorizontalAlignment HorizontalAlignment = HAlign_Fill;` — Affects the horizontal alignment of the content widget relative to the parent widget.
- L162 _protected member_ `EVerticalAlignment VerticalAlignment = VAlign_Fill;` — Affects the vertical alignment of the content widget relative to the parent widget.
- L164 _protected member_ `FMargin Padding;` — The padding of the content widget.
- L166 _protected prototype_ `FMargin GetPadding() const;`
- L173 _protected prototype_ `FVector2f RecomputeAnchorPoints(const FVector2f& InOffset);` — Recomputes HorizontalAlignment and VerticalAlignment if InOffset is too far away from the current corner. @param InOffset Offset relative to current HorizontalAlignment and VerticalAlignment @return New offset relative to recomputed HorizontalAlignment and VerticalAlignment

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ToolWidgets` (scope `UE`)

### `Source/Developer/ToolWidgets/Public/SActionButton.h` (Public)


#### class `IActionButton`  
`class IActionButton`  
_L13-20_
- L16 _public prototype_ `virtual ~IActionButton() = default;`
- L18 _public prototype_ `virtual void SetMenuContentWidgetToFocus(TWeakPtr<SWidget> InWidget) = 0;`
- L19 _public prototype_ `virtual void SetIsMenuOpen(bool bInIsOpen, bool bInIsFocused) = 0;`

#### class `SActionButton`  
`class SActionButton : public SCompoundWidget , public IActionButton`  
_L23-108_
- inherits: `SCompoundWidget,IActionButton`
- desc: A Button that is used to call out/highlight an option. It can also be used to open a menu.
- L28 _public function_ `SLATE_BEGIN_ARGS(SActionButton) : _ActionButtonStyle(nullptr) , _ButtonStyle(nullptr) , _IconButtonStyle(nullptr) , _ComboButtonStyle(nullptr) , _TextBlockStyle(nullptr)`
- L36 _public prototype_ `SLATE_STYLE_ARGUMENT(FActionButtonStyle, ActionButtonStyle) SLATE_ATTRIBUTE(EActionButtonType, ActionButtonType) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, IconButtonStyle) SLATE_ATTRIBUTE(FMargin, ButtonContentPadding) SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle) SLATE_ARGUMENT(TOptional<bool>, HasDownArrow) SLATE_ARGUMENT(TOptional<EHorizontalAlignment>, HorizontalContentAlignment) SLATE_ATTRIBUTE(FText, Text) SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextBlockStyle) SLATE_ATTRIBUTE(const FSlateBrush*, Icon) SLATE_ATTRIBUTE(FSlateColor, IconColorAndOpacity) #pragma region Button SLATE_EVENT(FOnClicked, OnClicked)`
- L91 _public prototype_ `virtual void SetMenuContentWidgetToFocus(TWeakPtr<SWidget> InWidget) override;`
- L92 _public prototype_ `virtual void SetIsMenuOpen(bool bInIsOpen, bool bInIsFocused) override;`
- L96 _protected prototype_ `virtual FSlateColor GetIconColorAndOpacity() const;`
- L99 _protected member_ `TSharedPtr<SComboButton> ComboButton;`
- L100 _protected member_ `TSharedPtr<class SButton> Button;`
- L102 _protected member_ `TAttribute<EActionButtonType> ActionButtonType = EActionButtonType::Default;`
- L103 _protected member_ `const FActionButtonStyle* ActionButtonStyle = nullptr;`
- L104 _protected member_ `const FButtonStyle* ButtonStyle = nullptr;`
- L105 _protected member_ `const FButtonStyle* IconButtonStyle = nullptr;`
- L106 _protected member_ `const FComboButtonStyle* ComboButtonStyle = nullptr;`
- L107 _protected member_ `const FTextBlockStyle* TextBlockStyle = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SAvatar.h` (Public)


#### class `SAvatar`  
`class SAvatar : public SCompoundWidget`  
_L14-64_
- inherits: `SCompoundWidget`
- desc: Widget for displaying a user avatar icon. The avatar's background color is computed based on the Identifier. The avatar's displayed letter is the initial letter of the Description if it's alpha numeric, or a question mark otherwise.
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvatar) : _HeightOverride(17.f), _WidthOverride(17.f), _ShowInitial(true)`
- L31 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget
- L34 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — The custom OnPaint handler necessary because we want to draw a circle
- L40 _private prototype_ `uint32 Hash() const;` — Computes a hash value using the djb2 algorithm. @return the hash value of the Identifier
- L48 _private prototype_ `FColor ComputeBackgroundColor() const;` — Computes the avatar's background color based on the Identifier Calls the Hash() function above to calculate an HSV color which is transformed into an FColor that ultimately represents the user's avatar color. @return the RGB representation of the Identifier
- L51 _private member_ `FString Identifier;` — The Identifier of the avatar
- L54 _private member_ `FString Description;` — The Description of the avatar
- L57 _private member_ `FColor BackgroundColor;` — The BackgroundColor used
- L60 _private member_ `FColor ForegroundColor;` — The ForegroundColor used (text)
- L63 _private member_ `bool bShowInitial;` — The setting that determines if we're showing the initial

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SCheckBoxList.h` (Public)


#### class `SCheckBoxList`  
`class SCheckBoxList: public SCompoundWidget`  
_L30-75_
- inherits: `SCompoundWidget`
- desc: A widget that can be used inside a CustomDialog to display a list of checkboxes
- L32 _private function_ `SLATE_BEGIN_ARGS(SCheckBoxList) : _CheckBoxStyle(&FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("Checkbox")) , _IncludeGlobalCheckBoxInHeaderRow(true)`
- L47 _public prototype_ `void Construct(const FArguments& Arguments);`
- L48 _public prototype_ `void Construct(const FArguments& Arguments, const TArray<FText>& Items, bool bIsChecked);`
- L49 _public prototype_ `void Construct(const FArguments& Arguments, const TArray<TSharedRef<SWidget>>& Items, bool bIsChecked);`
- L51 _public prototype_ `int32 AddItem(const FText& Text, bool bIsChecked);`
- L52 _public prototype_ `int32 AddItem(TSharedRef<SWidget> Widget, bool bIsChecked);`
- L53 _public prototype_ `void RemoveAll();`
- L54 _public prototype_ `void RemoveItem(int32 Index);`
- L55 _public prototype_ `bool IsItemChecked(int32 Index) const;`
- L57 _public prototype_ `TArray<bool> GetValues() const;`
- L58 _public prototype_ `int32 GetNumCheckboxes() const;`
- L61 _private prototype_ `void UpdateAllChecked();`
- L62 _private prototype_ `ECheckBoxState GetToggleSelectedState() const;`
- L63 _private prototype_ `void OnToggleSelectedCheckBox(ECheckBoxState InNewState);`
- L64 _private prototype_ `void OnItemCheckBox(TSharedRef<CheckBoxList::FItemPair> InItem);`
- L66 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedRef<CheckBoxList::FItemPair> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L68 _private member_ `ECheckBoxState bAllCheckedState = ECheckBoxState::Unchecked;`
- L69 _private member_ `TArray<TSharedRef<CheckBoxList::FItemPair>> Items;`
- L71 _private member_ `const FCheckBoxStyle* CheckBoxStyle = nullptr;`
- L72 _private member_ `TSharedPtr<SListView<TSharedRef<CheckBoxList::FItemPair>>> ListView;`
- L74 _private member_ `FOnCheckListItemStateChanged OnItemCheckStateChanged;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TOOLWIDGETS_API`
- L22 _namespace_ `namespace CheckBoxList`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCheckListItemStateChanged, int );`
- L27 _prototype_ `DECLARE_DELEGATE_OneParam( FOnCheckListItemStateChanged, int );`

### `Source/Developer/ToolWidgets/Public/SNegativeActionButton.h` (Public)


#### enum `EActionButtonStyle`  
`enum class EActionButtonStyle`  
_L13-17_
- L15 _public enumerator_ `Warning`
- L16 _public enumerator_ `Error`

#### class `SNegativeActionButton`  
`class SNegativeActionButton : public SCompoundWidget , public IActionButton`  
_L22-64_
- inherits: `SCompoundWidget,IActionButton`
- desc: A Button that is used to call out/highlight a negative option (Warnings or Errors like Force Delete). It can also be used to open a menu.
- L27 _public function_ `SLATE_BEGIN_ARGS(SNegativeActionButton) : _ActionButtonStyle(EActionButtonStyle::Error)`
- L32 _public prototype_ `SLATE_ATTRIBUTE(EActionButtonStyle, ActionButtonStyle) SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(const FSlateBrush*, Icon) SLATE_EVENT(FOnClicked, OnClicked) SLATE_NAMED_SLOT(FArguments, MenuContent) SLATE_EVENT(FOnGetContent, OnGetMenuContent) SLATE_EVENT(FOnComboBoxOpened, OnComboBoxOpened) SLATE_EVENT(FOnIsOpenChanged, OnMenuOpenChanged) SLATE_END_ARGS() SNegativeActionButton() = default;` — Determines whether this is a Warning or Error.
- L55 _public prototype_ `void Construct(const FArguments& InArgs);`
- L58 _public prototype_ `virtual void SetMenuContentWidgetToFocus(TWeakPtr<SWidget> InWidget) override;`
- L59 _public prototype_ `virtual void SetIsMenuOpen(bool bInIsOpen, bool bInIsFocused) override;`
- L63 _private member_ `TSharedPtr<SActionButton> ActionButton;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SPositiveActionButton.h` (Public)


#### class `SPositiveActionButton`  
`class SPositiveActionButton : public SCompoundWidget , public IActionButton`  
_L15-53_
- inherits: `SCompoundWidget,IActionButton`
- desc: A Button that is used to call out/highlight a positive option (Add, Save etc). It can also be used to open a menu.
- L20 _public function_ `SLATE_BEGIN_ARGS(SPositiveActionButton) : _Icon(FAppStyle::Get().GetBrush("Icons.Plus"))`
- L25 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(const FSlateBrush*, Icon) SLATE_EVENT(FOnClicked, OnClicked) SLATE_NAMED_SLOT(FArguments, MenuContent) SLATE_EVENT(FOnGetContent, OnGetMenuContent) SLATE_EVENT(FOnComboBoxOpened, OnComboBoxOpened) SLATE_EVENT(FOnIsOpenChanged, OnMenuOpenChanged) SLATE_END_ARGS() SPositiveActionButton() = default;` — The text to display in the button.
- L44 _public prototype_ `void Construct(const FArguments& InArgs);`
- L47 _public prototype_ `virtual void SetMenuContentWidgetToFocus(TWeakPtr<SWidget> InWidget) override;`
- L48 _public prototype_ `virtual void SetIsMenuOpen(bool bInIsOpen, bool bInIsFocused) override;`
- L52 _private member_ `TSharedPtr<SActionButton> ActionButton;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SPrimaryButton.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SPrimaryButton>`  
_L12-15_
- L14 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SPrimaryButton`  
`class SPrimaryButton : public SButton`  
_L17-36_
- inherits: `SButton`
- L21 _public function_ `SLATE_BEGIN_ARGS(SPrimaryButton)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(const FSlateBrush*, Icon) SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The text to display in the button.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SResizeBox.h` (Public)


#### class `SVerticalResizeBox`  
`class SVerticalResizeBox : public SCompoundWidget`  
_L10-55_
- inherits: `SCompoundWidget`
- L13 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnContentHeightChanged, float);`
- L16 _public function_ `SLATE_BEGIN_ARGS(SVerticalResizeBox) : _HandleHeight(5) , _ContentHeight(50) , _HandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) , _HandleHighlightColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f))`
- L22 _public prototype_ `SLATE_ARGUMENT(float, HandleHeight) SLATE_ATTRIBUTE(float, ContentHeight) SLATE_ATTRIBUTE(FLinearColor, HandleColor) SLATE_ATTRIBUTE(FLinearColor, HandleHighlightColor) SLATE_EVENT(FOnContentHeightChanged, ContentHeightChanged) SLATE_DEFAULT_SLOT(FArguments, Content);`
- L28 _public prototype_ `SLATE_END_ARGS();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L33 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L34 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L35 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L36 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L39 _private prototype_ `FOptionalSize GetHeightOverride() const;`
- L42 _private member_ `TOptional<float> LastMouseLocation;`
- L44 _private member_ `TAttribute<float> ContentHeight;`
- L45 _private member_ `float HandleHeight;`
- L47 _private member_ `float DragStartLocation;`
- L48 _private member_ `float DragStartContentHeight;`
- L50 _private member_ `TAttribute<FLinearColor> HandleColor;`
- L51 _private member_ `TAttribute<FLinearColor> HandleHighlightColor;`
- L52 _private member_ `FSlateBrush HandleBrush;`
- L54 _private member_ `FOnContentHeightChanged ContentHeightChanged;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnContentHeightChanged, float);`

### `Source/Developer/ToolWidgets/Public/SRichTextWarningOrErrorBox.h` (Public)


#### class `SRichTextWarningOrErrorBox`  
`class SRichTextWarningOrErrorBox : public SWarningOrErrorBox`  
_L11-19_
- inherits: `SWarningOrErrorBox`
- L15 _public prototype_ `void Construct(const FArguments& InArgs);`
- L18 _private member_ `TAttribute<EMessageStyle> MessageStyle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SSearchToggleButton.h` (Public)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SSearchToggleButton>`  
_L22-25_
- L24 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SSearchToggleButton`  
`class SSearchToggleButton : public SCompoundWidget`  
_L27-58_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SSearchToggleButton) : _Style(&FAppStyle::Get().GetWidgetStyle<FSearchBoxStyle>("SearchBox"))`
- L34 _public prototype_ `SLATE_STYLE_ARGUMENT(FSearchBoxStyle, Style) SLATE_EVENT(FOnSearchBoxShown, OnSearchBoxShown) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SSearchBox> SearchBox);` — Search box style (used to match the glass icon)
- L44 _public function_ `bool IsExpanded() const` — @return true if the search area is expanded and the search box exposed
- L47 _public prototype_ `void SetExpanded(bool bInExpanded);` — Sets whether or not the search area is expanded to expose the search box
- L50 _private prototype_ `ECheckBoxState GetToggleButtonState() const;`
- L51 _private prototype_ `void OnToggleButtonStateChanged(ECheckBoxState CheckBoxState);`
- L52 _private prototype_ `EVisibility GetSearchBoxVisibility() const;`
- L54 _private member_ `const FSearchBoxStyle* SearchStyle;`
- L55 _private member_ `bool bIsExpanded;`
- L56 _private member_ `FOnSearchBoxShown OnSearchBoxShown;`
- L57 _private member_ `TWeakPtr<SSearchBox> SearchBoxPtr;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TOOLWIDGETS_API`
- L19 _delegate_ `DECLARE_DELEGATE(FOnSearchBoxShown) template<> struct TWidgetTypeTraits<class SSearchToggleButton> { static constexpr bool SupportsInvalidation() { return true; } };`

### `Source/Developer/ToolWidgets/Public/SSearchableComboBox.h` (Public)
_(no declarations extracted)_

### `Source/Developer/ToolWidgets/Public/SSegmentedProgressBar.h` (Public)


#### struct `FSegmentedProgressBarStyle`  
`struct FSegmentedProgressBarStyle`  
_L13-44_
- L15 _public member_ `FSlateColor BusyColor;`
- L16 _public member_ `FSlateColor PendingColor;`
- L17 _public member_ `FSlateColor ErrorColor;`
- L18 _public member_ `FSlateColor CompleteColor;`
- L19 _public member_ `FSlateColor CanceledColor;`
- L20 _public member_ `FSlateColor SkippedColor;`
- L21 _public member_ `FSlateColor AllCompleteColor;`
- L23 _public member_ `const FSlateBrush* FullCircleBrush = nullptr;`
- L24 _public member_ `const FSlateBrush* OuterCircleBrush = nullptr;`
- L25 _public member_ `const FSlateBrush* OuterCircleBusyBrush = nullptr;`
- L26 _public member_ `const FSlateBrush* BadgeSuccessBrush = nullptr;`
- L27 _public member_ `const FSlateBrush* BadgeErrorBrush = nullptr;`
- L28 _public member_ `const FSlateBrush* BadgeAllCompleteBrush = nullptr;`
- L30 _public function_ `FSegmentedProgressBarStyle& SetBusyColor(FSlateColor InColor)`
- L31 _public function_ `FSegmentedProgressBarStyle& SetPendingColor(FSlateColor InColor)`
- L32 _public function_ `FSegmentedProgressBarStyle& SetErrorColor(FSlateColor InColor)`
- L33 _public function_ `FSegmentedProgressBarStyle& SetCompleteColor(FSlateColor InColor)`
- L34 _public function_ `FSegmentedProgressBarStyle& SetCanceledColor(FSlateColor InColor)`
- L35 _public function_ `FSegmentedProgressBarStyle& SetSkippedColor(FSlateColor InColor)`
- L36 _public function_ `FSegmentedProgressBarStyle& SetAllCompleteColor(FSlateColor InColor)`
- L38 _public function_ `FSegmentedProgressBarStyle& SetFullCircleBrush(const FSlateBrush* InBrush)`
- L39 _public function_ `FSegmentedProgressBarStyle& SetOuterCircleBrush(const FSlateBrush* InBrush)`
- L40 _public function_ `FSegmentedProgressBarStyle& SetOuterCircleBusyBrush(const FSlateBrush* InBrush)`
- L41 _public function_ `FSegmentedProgressBarStyle& SetBadgeSuccessBrush(const FSlateBrush* InBrush)`
- L42 _public function_ `FSegmentedProgressBarStyle& SetBadgeErrorBrush(const FSlateBrush* InBrush)`
- L43 _public function_ `FSegmentedProgressBarStyle& SetBadgeAllCompleteBrush(const FSlateBrush* InBrush)`

#### class `SSegmentedProgressBar`  
`class SSegmentedProgressBar : public SCompoundWidget`  
_L46-182_
- inherits: `SCompoundWidget`
- L106 _public function_ `static FSlot::FSlotArguments Slot()`
- L111 _public function_ `SLATE_BEGIN_ARGS(SSegmentedProgressBar)`
- L112 _public prototype_ `SLATE_SLOT_ARGUMENT(FSlot, Slots) SLATE_ARGUMENT(FSegmentedProgressBarStyle, Style) SLATE_ARGUMENT_DEFAULT(bool, bAutoPromoteNextPending) = true;`
- L117 _public typedef_ `using FScopedWidgetSlotArguments = typename TPanelChildren<FSlot>::FScopedWidgetSlotArguments;`
- L118 _public function_ `FScopedWidgetSlotArguments AddSlot(bool bRebuildChildren = true)`
- L123 _public prototype_ `FScopedWidgetSlotArguments InsertSlot(int32 Index = INDEX_NONE, bool bRebuildChildren = true);`
- L125 _public function_ `FSlot& GetSlot(int32 SlotIndex)`
- L130 _public function_ `const FSlot& GetSlot(int32 SlotIndex) const`
- L135 _public function_ `int32 NumSlots() const`
- L140 _public function_ `void ClearChildren()`
- L145 _public function_ `SSegmentedProgressBar() : Children(this)`
- L153 _public prototype_ `void Construct(const FArguments& Arguments);`
- L154 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L157 _private prototype_ `void RebuildChildren();`
- L158 _private prototype_ `void AddChildSeparatorBar( TSharedPtr<class SHorizontalBox> SlotBox, int32 ChildIndex ) const;`
- L159 _private prototype_ `TSharedRef<SWidget> ConstructChild( const FSlot& Slot, int32 ChildIndex ) const;`
- L161 _private prototype_ `void CacheChildStates();`
- L162 _private prototype_ `EState GetChildState( int32 ChildIndex ) const;`
- L164 _private prototype_ `FLinearColor GetSeparatorBarColor( int32 ChildIndex ) const;`
- L165 _private prototype_ `FSlateColor GetCircleColor( int32 ChildIndex ) const;`
- L166 _private prototype_ `FSlateColor GetIconColor( int32 ChildIndex ) const;`
- L167 _private prototype_ `EVisibility GetFullCircleVisibility( int32 ChildIndex ) const;`
- L168 _private prototype_ `EVisibility GetOuterCircleVisibility( int32 ChildIndex ) const;`
- L169 _private prototype_ `EVisibility GetProgressCircleVisibility( int32 ChildIndex ) const;`
- L170 _private prototype_ `EVisibility GetOverlayVisibility( int32 ChildIndex ) const;`
- L171 _private prototype_ `const FSlateBrush* GetOverlayIcon( int32 ChildIndex ) const;`
- L172 _private prototype_ `TOptional<FSlateRenderTransform> GetProgressCircleTransform( int32 ChildIndex ) const;`
- L174 _private member_ `FSegmentedProgressBarStyle Style;`
- L175 _private member_ `TPanelChildren<FSlot> Children;`
- L176 _private member_ `TArray<EState> CachedChildStates;`
- L177 _private member_ `EState CachedOverallState = EState::None;`
- L178 _private member_ `bool bAutoPromoteNextPending = true;`
- L180 _private member_ `FCurveSequence ThrobberAnimation;`
- L181 _private member_ `const float LineSize = 4;`

#### enum `SSegmentedProgressBar::EState`  
`enum class EState : uint8`  
_L49-58_
- L51 _public enumerator_ `None`
- L52 _public enumerator_ `Busy`
- L53 _public enumerator_ `Canceled`
- L54 _public enumerator_ `Completed`
- L55 _public enumerator_ `Failed`
- L56 _public enumerator_ `Pending`
- L57 _public enumerator_ `Skipped`

#### struct `SSegmentedProgressBar::FSlot`  
`struct FSlot : public TSlotBase<FSlot>`  
_L61-104_
- inherits: `TSlotBase<FSlot>`
- L64 _public function_ `FSlot() : TSlotBase<FSlot>() , Image(nullptr)`
- L69 _public function_ `SLATE_SLOT_BEGIN_ARGS(FSlot, TSlotBase<FSlot>) SLATE_ATTRIBUTE(const FSlateBrush*, Image) SLATE_ATTRIBUTE(EState, State) SLATE_ATTRIBUTE(FText, ToolTipText) SLATE_ARGUMENT(TSharedPtr<SWidget>, LabelContent) SLATE_SLOT_END_ARGS() void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs)`
- L98 _protected member_ `TAttribute<const FSlateBrush*> Image;`
- L99 _protected member_ `TAttribute<EState> State;`
- L100 _protected member_ `TAttribute<FText> ToolTipText;`
- L101 _protected member_ `TSharedPtr<SWidget> LabelContent;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SSegmentedTimelineView.h` (Public)


#### class `SSegmentedTimelineView`  
`class SSegmentedTimelineView : public SCompoundWidget`  
_L17-68_
- inherits: `SCompoundWidget`
- desc: a timeline view which renders a block for in the timeline where the object exists
- L29 _public function_ `SLATE_BEGIN_ARGS(SSegmentedTimelineView) : _ViewRange(TRange<double>(0.0,10.0)) , _DesiredSize(FVector2f(100.f,20.f))`
- L34 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L37 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FSegmentData>, SegmentData);` — Existence Time Range
- L40 _public prototype_ `SLATE_ATTRIBUTE(FVector2f, DesiredSize);` — Desired widget size
- L43 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, FillColor);` — Fill Color
- L45 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L57 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L58 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L60 _protected prototype_ `int32 PaintBlock(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const;`
- L62 _protected member_ `TAttribute<TRange<double>> ViewRange;`
- L63 _protected member_ `TAttribute<TSharedPtr<FSegmentData>> SegmentData;`
- L64 _protected member_ `TAttribute<FVector2f> DesiredSize;`
- L65 _protected member_ `TAttribute<FLinearColor> FillColor;`
- L67 _protected member_ `const FSlateBrush* WhiteBrush;`

#### struct `SSegmentedTimelineView::FSegmentData`  
`struct FSegmentData`  
_L20-27_
- L23 _public member_ `TArray<TRange<double>> Segments;`
- L26 _public member_ `TOptional<TArray<FLinearColor>> AlternatingSegmentsColors;` — This is an optional array of alternating colors. Every segment will use the next color in this array and will wrap around if the number of colors provided is > than the number of segments.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SSimpleButton.h` (Public)


#### class `SSimpleButton`  
`class SSimpleButton : public SButton`  
_L12-30_
- inherits: `SButton`
- L16 _public function_ `SLATE_BEGIN_ARGS(SSimpleButton)`
- L19 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(const FSlateBrush*, Icon) SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() SSimpleButton() = default;` — The text to display in the button.
- L29 _public prototype_ `void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SSimpleComboButton.h` (Public)


#### class `SSimpleComboButton`  
`class SSimpleComboButton : public SComboButton , public IActionButton`  
_L13-45_
- inherits: `SComboButton,IActionButton`
- L18 _public function_ `SLATE_BEGIN_ARGS(SSimpleComboButton) : _HasDownArrow(false) , _UsesSmallText(false)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(const FSlateBrush*, Icon) SLATE_NAMED_SLOT(FArguments, MenuContent) SLATE_EVENT(FOnGetContent, OnGetMenuContent) SLATE_EVENT(FOnComboBoxOpened, OnComboBoxOpened) SLATE_EVENT(FOnIsOpenChanged, OnMenuOpenChanged) SLATE_ARGUMENT(bool, HasDownArrow) SLATE_ARGUMENT(bool, UsesSmallText) SLATE_END_ARGS() SSimpleComboButton() = default;` — The text to display in the button.
- L39 _public prototype_ `void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `virtual void SetMenuContentWidgetToFocus(TWeakPtr<SWidget> InWidget) override;`
- L43 _public prototype_ `virtual void SetIsMenuOpen(bool bInIsOpen, bool bInIsFocused) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SSimpleTimeSlider.h` (Public)


#### class `SSimpleTimeSlider`  
`class SSimpleTimeSlider : public SCompoundWidget`  
_L17-223_
- inherits: `SCompoundWidget`
- L20 _public function_ `DECLARE_DELEGATE_OneParam( FOnRangeChanged, TRange<double> ) DECLARE_DELEGATE_TwoParams( FOnScrubPositionChanged, double, bool ) DECLARE_DELEGATE_RetVal_OneParam( FString, FOnFormatTickLabel, double ) SLATE_BEGIN_ARGS(SSimpleTimeSlider) : _MirrorLabels( false ) , _ScrubPosition(0.0) , _ViewRange(TRange<double>(0.0,10.0)) , _ClampRange(TRange<double>(0.0,10.0)) , _AllowZoom (true) , _AllowPan (true) , _CursorSize(0.f) , _ClampRangeHighlightColor(FLinearColor(0.05f,0.05f,0.05f,1.0f)) , _ClampRangeHighlightSize(1.0f) , _DesiredSize(FVector2f(100.f,22.f))`
- L37 _public prototype_ `SLATE_ATTRIBUTE( bool, MirrorLabels ) SLATE_ATTRIBUTE(double, ScrubPosition);` — If we should mirror the labels on the timeline
- L43 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L46 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ClampRange);` — Clamp time range
- L49 _public prototype_ `SLATE_ATTRIBUTE(bool, AllowZoom);` — If we are allowed to zoom
- L52 _public prototype_ `SLATE_ATTRIBUTE(bool, AllowPan);` — If we are allowed to pan
- L55 _public prototype_ `SLATE_ATTRIBUTE(float, CursorSize);` — Cursor range for data like histogram graphs, etc.
- L58 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, ClampRangeHighlightColor);` — Color overlay for active range
- L61 _public prototype_ `SLATE_ATTRIBUTE(float, ClampRangeHighlightSize);` — Size of clamp range overlay 0.0 for none 1.0 for the height of the slider
- L64 _public prototype_ `SLATE_ARGUMENT(FVector2f, DesiredSize);` — Widget desired size
- L68 _public prototype_ `SLATE_EVENT(FOnScrubPositionChanged, OnScrubPositionChanged);` — Called when the scrub position changes
- L71 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnBeginScrubberMovement);` — Called right before the scrubber begins to move
- L74 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnEndScrubberMovement);` — Called right after the scrubber handle is released by the user
- L77 _public prototype_ `SLATE_EVENT(FOnRangeChanged, OnViewRangeChanged);` — Called when the view range changes
- L80 _public prototype_ `SLATE_EVENT(FOnFormatTickLabel, OnFormatTickLabel);` — Optional callback to format tick labels. If unbound, default "%.2f" / "%.3f" formatting is used.
- L83 _public prototype_ `SLATE_ARGUMENT(TOptional<uint32>, MinPixelsPerDisplayTick);` — Minimum pixels between each minor tick mark. Larger values produce sparser ticks and labels. If unset, falls back to the default in ScrubConstants.
- L85 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L95 _public function_ `TRange<double> GetTimeRange()`
- L96 _public prototype_ `void SetTimeRange(double MinValue, double MaxValue);`
- L97 _public prototype_ `void SetClampRange(double MinValue, double MaxValue);`
- L98 _public function_ `bool IsPanning()`
- L157 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L158 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L159 _protected prototype_ `virtual FReply OnPreviewMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L160 _protected prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L161 _protected prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L162 _protected prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L164 _protected prototype_ `int32 OnPaintTimeSlider( bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const;`
- L173 _protected prototype_ `void DrawTicks( FSlateWindowElementList& OutDrawElements, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs ) const;` — Draws time tick marks @param OutDrawElements	List to add draw elements to @param RangeToScreen		Time range to screen space converter @param InArgs			Parameters for drawing the tick lines
- L175 _protected prototype_ `double GetTimeAtCursorPosition(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L183 _protected prototype_ `void CommitScrubPosition( double NewValue, bool bIsScrubbing );` — Call this method when the user's interaction has changed the scrub position @param NewValue				Value resulting from the user's interaction @param bIsScrubbing			True if done via scrubbing, false if just releasing scrubbing
- L185 _protected member_ `TAttribute<double> ScrubPosition;`
- L186 _protected member_ `TAttribute<TRange<double>> ViewRange;`
- L187 _protected member_ `TAttribute<TRange<double>> ClampRange;`
- L188 _protected member_ `TAttribute<double> TimeSnapInterval;`
- L189 _protected member_ `TAttribute<bool> AllowZoom;`
- L190 _protected member_ `TAttribute<bool> AllowPan;`
- L191 _protected member_ `TAttribute<float> CursorSize;`
- L192 _protected member_ `TAttribute<FLinearColor> ClampRangeHighlightColor;`
- L193 _protected member_ `TAttribute<float> ClampRangeHighlightSize;`
- L194 _protected member_ `TAttribute<bool> MirrorLabels;`
- L196 _protected member_ `FOnScrubPositionChanged OnScrubPositionChanged;`
- L198 _protected member_ `FSimpleDelegate OnBeginScrubberMovement;` — Called right before the scrubber begins to move
- L200 _protected member_ `FSimpleDelegate OnEndScrubberMovement;` — Delegate called right after the scrubber handle is released by the user
- L201 _protected member_ `FOnRangeChanged OnViewRangeChanged;`
- L202 _protected member_ `FOnFormatTickLabel OnFormatTickLabel;`
- L203 _protected member_ `uint32 MinPixelsPerDisplayTick = 0u;`
- L206 _protected member_ `const FSlateBrush* ScrubHandleUp;` — Brush for drawing an upwards facing scrub handle
- L208 _protected member_ `const FSlateBrush* ScrubHandleDown;` — Brush for drawing a downwards facing scrub handle
- L210 _protected member_ `const FSlateBrush* CursorBackground;` — Brush for drawing cursor background to visualize cursor size
- L212 _protected member_ `float DistanceDragged;` — Total mouse delta during dragging
- L214 _protected member_ `bool bDraggingScrubber;` — If we are dragging the scrubber
- L216 _protected member_ `bool bPanning;` — If we are currently panning the panel
- L218 _protected member_ `TSharedPtr<SScrollBar> Scrollbar;` — /
- L219 _protected member_ `FVector2f SoftwareCursorPosition;`
- L220 _protected member_ `FVector2f DesiredSize;`

#### struct `SSimpleTimeSlider::FScrubRangeToScreen`  
`struct FScrubRangeToScreen`  
_L101-130_
- desc: Utility struct for converting between scrub range space and local/absolute screen space
- L103 _public member_ `FVector2f WidgetSize;`
- L105 _public member_ `TRange<double> ViewInput;`
- L106 _public member_ `double ViewInputRange;`
- L107 _public member_ `float PixelsPerInput;`
- L109 _public function_ `FScrubRangeToScreen(TRange<double> InViewInput, const UE::Slate::FDeprecateVector2DParameter& InWidgetSize )`
- L119 _public function_ `double LocalXToInput(const float ScreenX) const` — Local Widget Space -> Curve Input domain.
- L126 _public function_ `float InputToLocalX(const double Input) const` — Curve Input domain -> local Widget Space

#### struct `SSimpleTimeSlider::FDrawTickArgs`  
`struct FDrawTickArgs`  
_L134-154_
- L137 _public member_ `FGeometry AllottedGeometry;` — Geometry of the area
- L139 _public member_ `FSlateRect ClippingRect;` — Clipping rect of the area
- L141 _public member_ `FLinearColor TickColor;` — Color of each tick
- L143 _public member_ `float TickOffset;` — Offset in Y where to start the tick
- L145 _public member_ `float MajorTickHeight;` — Height in of major ticks
- L147 _public member_ `int32 StartLayer;` — Start layer for elements
- L149 _public member_ `ESlateDrawEffect DrawEffects;` — Draw effects to apply
- L151 _public member_ `bool bOnlyDrawMajorTicks;` — Whether or not to only draw major ticks
- L153 _public member_ `bool bMirrorLabels;` — Whether or not to mirror labels

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam( FOnRangeChanged, TRange<double> ) DECLARE_DELEGATE_TwoParams( FOnScrubPositionChanged, double, bool ) DECLARE_DELEGATE_RetVal_OneParam( FString, FOnFormatTickLabel, double ) SLATE_BEGIN_ARGS(SSimpleTimeSlider) : _MirrorLabels( false ) , _ScrubPosition(0.0) , _ViewRange(TRange<double>(0.0,10.0)) , _ClampRange(TRange<double>(0.0,10.0)) , _AllowZoom (true) , _AllowPan (true) , _CursorSize(0.f) , _ClampRangeHighlightColor(FLinearColor(0.05f,0.05f,0.05f,1.0f)) , _ClampRangeHighlightSize(1.0f) , _DesiredSize(FVector2f(100.f,22.f)) {} SLATE_ATTRIBUTE( bool, MirrorLabels ) SLATE_ATTRIBUTE(double, ScrubPosition);`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnScrubPositionChanged, double, bool ) DECLARE_DELEGATE_RetVal_OneParam( FString, FOnFormatTickLabel, double ) SLATE_BEGIN_ARGS(SSimpleTimeSlider) : _MirrorLabels( false ) , _ScrubPosition(0.0) , _ViewRange(TRange<double>(0.0,10.0)) , _ClampRange(TRange<double>(0.0,10.0)) , _AllowZoom (true) , _AllowPan (true) , _CursorSize(0.f) , _ClampRangeHighlightColor(FLinearColor(0.05f,0.05f,0.05f,1.0f)) , _ClampRangeHighlightSize(1.0f) , _DesiredSize(FVector2f(100.f,22.f)) {} SLATE_ATTRIBUTE( bool, MirrorLabels ) SLATE_ATTRIBUTE(double, ScrubPosition);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( FString, FOnFormatTickLabel, double ) SLATE_BEGIN_ARGS(SSimpleTimeSlider) : _MirrorLabels( false ) , _ScrubPosition(0.0) , _ViewRange(TRange<double>(0.0,10.0)) , _ClampRange(TRange<double>(0.0,10.0)) , _AllowZoom (true) , _AllowPan (true) , _CursorSize(0.f) , _ClampRangeHighlightColor(FLinearColor(0.05f,0.05f,0.05f,1.0f)) , _ClampRangeHighlightSize(1.0f) , _DesiredSize(FVector2f(100.f,22.f)) {} SLATE_ATTRIBUTE( bool, MirrorLabels ) SLATE_ATTRIBUTE(double, ScrubPosition);`

### `Source/Developer/ToolWidgets/Public/SWarningOrErrorBox.h` (Public)


#### enum `EMessageStyle`  
`enum class EMessageStyle`  
_L10-14_
- L12 _public enumerator_ `Warning`
- L13 _public enumerator_ `Error`

#### class `SWarningOrErrorBox`  
`class SWarningOrErrorBox : public SBorder`  
_L16-48_
- inherits: `SBorder`
- L19 _public function_ `SLATE_BEGIN_ARGS(SWarningOrErrorBox) : _MessageStyle(EMessageStyle::Warning) , _Padding(16.0f) , _IconSize(24,24) , _AutoWrapText(true) , _ContentHAlign(EHorizontalAlignment::HAlign_Right) , _ContentVAlign(EVerticalAlignment::VAlign_Center) , _Content()`
- L28 _public prototype_ `SLATE_ATTRIBUTE(FText, Message) SLATE_ATTRIBUTE(EMessageStyle, MessageStyle) SLATE_ARGUMENT(FMargin, Padding) SLATE_ARGUMENT(FVector2D, IconSize) SLATE_ARGUMENT(bool, AutoWrapText) SLATE_ARGUMENT(EHorizontalAlignment, ContentHAlign) SLATE_ARGUMENT(EVerticalAlignment, ContentVAlign) SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _private member_ `TAttribute<EMessageStyle> MessageStyle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/SWidgetDrawer.h` (Public)


#### struct `FOpenDrawerData`  
`struct FOpenDrawerData`  
_L20-35_
- L22 _public member_ `FName DrawerId;`
- L23 _public member_ `TSharedPtr<SDrawerOverlay> DrawerOverlay;`
- L24 _public member_ `TWeakPtr<SWindow> WindowWithOverlayContent;`
- L26 _public function_ `bool IsValid() const`
- L31 _public function_ `bool operator==(const FName InDrawerId) const`

#### class `SWidgetDrawer`  
`class SWidgetDrawer : public SCompoundWidget`  
_L37-124_
- inherits: `SCompoundWidget`
- L39 _private function_ `SLATE_BEGIN_ARGS(SWidgetDrawer)`
- L44 _public prototype_ `~SWidgetDrawer();`
- L50 _public prototype_ `void Construct(const FArguments& InArgs, FName InStatusBarName);` — @param InArgs @param InStatusBarName Unique ID used to for writing to config file. Config file saves target drawer height.
- L52 _public function_ `virtual bool SupportsKeyboardFocus() const`
- L58 _public prototype_ `void RegisterDrawer(FWidgetDrawerConfig&& Drawer, int32 SlotIndex = INDEX_NONE);` — Registers a new drawer with this status bar. Registering will add a button to open and close the drawer
- L66 _public prototype_ `void UnregisterDrawer(FName DrawerId);` — Unregisters drawer with the given DrawerId. This will dismiss the drawer immediately if its opened, and destroy the status bar widget that opens/closes the drawer @param DrawerId name of the registered drawer to unregister
- L73 _public prototype_ `void OpenDrawer(const FName DrawerId);` — Opens a drawer @param DrawerId Name of the registered drawer to open
- L81 _public prototype_ `bool DismissDrawer(const TSharedPtr<SWidget>& NewlyFocusedWidget);` — Dismisses an open drawer with an animation.  The drawer contents are removed once the animation is complete @param NewlyFocusedWidget Optional widget to focus @return true if any open drawer was dismissed
- L87 _public prototype_ `void CloseDrawerImmediately(FName DrawerId = NAME_None);` — Closes a drawer immediately with no closing animation. Needed for when UI is shutting down or to prevent conflicts where a drawer is open in two places at once. @param DrawerId The name of the drawer to close. If no name is specified all drawers are closed immediately
- L90 _public prototype_ `bool IsDrawerOpened(const FName DrawerId) const;` — Is a specific registered drawer currently open
- L93 _public prototype_ `bool IsAnyOtherDrawerOpened(const FName DrawerId) const;` — Is any drawer other than the one specified by DrawerId opened
- L95 _public function_ `FName GetDrawerName() const`
- L96 _public prototype_ `FString GetSerializableName() const;`
- L101 _private prototype_ `void OnGlobalFocusChanging(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);` — Called when global focus changes which is used to determine if we should close an opened content browser drawer
- L103 _private prototype_ `void OnActiveTabChanged(TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated);` — Called when active tab changes which is used to determine if we should close an opened content browser drawer
- L104 _private prototype_ `void OnDrawerHeightChanged(float TargetHeight);`
- L106 _private prototype_ `TSharedRef<SWidget> MakeStatusBarDrawerButton(const FWidgetDrawerConfig& Drawer);`
- L108 _private prototype_ `FReply OnDrawerButtonClicked(const FName DrawerId);`
- L110 _private prototype_ `void CloseDrawerImmediatelyInternal(const FOpenDrawerData& Data);`
- L114 _private member_ `TArray<FWidgetDrawerConfig> RegisteredDrawers;`
- L116 _private member_ `TMap<FName, TWeakPtr<SWidget>> DrawerIdToContentWidget;`
- L118 _private member_ `TArray<FOpenDrawerData> DismissingDrawers;`
- L120 _private member_ `TSharedPtr<SHorizontalBox> DrawerBox;`
- L122 _private member_ `FName DrawerName;`
- L123 _private member_ `FOpenDrawerData OpenedDrawer;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TOOLWIDGETS_API`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStatusBarDrawerTargetHeightChanged, float);`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStatusBarDrawerTargetHeightChanged, float);`

### `Source/Developer/ToolWidgets/Public/Sidebar/ISidebarDrawerContent.h` (Public)


#### class `ISidebarDrawerContent`  
`class ISidebarDrawerContent : public TSharedFromThis<ISidebarDrawerContent>`  
_L12-40_
- inherits: `TSharedFromThis<ISidebarDrawerContent>`
- L15 _public prototype_ `virtual ~ISidebarDrawerContent() = default;`
- L18 _public prototype_ `virtual FName GetUniqueId() const = 0;` — Gets the unique Id used to identify the sidebar drawer.
- L21 _public prototype_ `virtual FName GetSectionId() const = 0;` — Gets the section unique Id used to identify the drawer section.
- L24 _public prototype_ `virtual FText GetSectionDisplayText() const = 0;` — Gets the section text to display on the section button.
- L27 _public function_ `virtual bool ShouldShowSection() const` — Returns true if this section should be displayed.
- L30 _public function_ `virtual TOptional<float> GetSectionFillHeight() const` — Sets the optional slot height stretch coefficient. If not set, auto sizes the slot.
- L33 _public function_ `virtual int32 GetSortOrder() const` — Gets the section sort order. Lower values will be put at the above higher values.
- L36 _public prototype_ `virtual TSharedRef<SWidget> CreateContentWidget() = 0;` — Constructs the content widget for a sidebar drawer.
- L39 _public function_ `virtual void OnDrawerOpenClose(const bool bOpen)` — Event that fires when the drawer is opened or closed.

### `Source/Developer/ToolWidgets/Public/Sidebar/SSidebar.h` (Public)


#### enum `ESidebarTabLocation`  
`enum class ESidebarTabLocation : uint8`  
_L33-43_
- desc: The direction that a tab drawer opens relative to the location of the sidebar. NOTE: Effort has been made to support top and bottom sidebar locations, but this has not been thoroughly tested and ironed out because there is currently no use case.
- L36 _public enumerator_ `Left` — Open from left to right
- L38 _public enumerator_ `Right` — Open from right to left
- L40 _public enumerator_ `Top` — Open from bottom to top
- L42 _public enumerator_ `Bottom` — Open from top to bottom

#### class `SSidebar`  
`class SSidebar : public SCompoundWidget`  
_L52-285_
- inherits: `SCompoundWidget`
- desc: Static sidebar tab widget that cannot be dragged or moved to a different location. Multiple drawers can be registered to a single sidebar and each drawer can have its own sections, each of which can be displayed single, in combination, or all together through buttons at the top of the drawer.
- L57 _public member_ `static constexpr float MinTabButtonSize = 100.f;`
- L58 _public member_ `static constexpr float MaxTabButtonSize = 200.f;`
- L59 _public member_ `static constexpr float TabButtonThickness = 25.f;`
- L61 _public function_ `SLATE_BEGIN_ARGS(SSidebar) : _HideWhenAllDocked(false) , _AlwaysUseMaxButtonSize(false) , _DisablePin(false) , _DisableDock(false)`
- L68 _public prototype_ `SLATE_ARGUMENT(ESidebarTabLocation, TabLocation) SLATE_ARGUMENT(float, InitialDrawerSize) SLATE_ARGUMENT(FOnGetContent, OnGetContent) SLATE_ARGUMENT(bool, HideWhenAllDocked) SLATE_ARGUMENT(bool, AlwaysUseMaxButtonSize) SLATE_ARGUMENT(bool, DisablePin) SLATE_ARGUMENT(bool, DisableDock) SLATE_EVENT(FOnSidebarStateChanged, OnStateChanged) SLATE_END_ARGS() virtual ~SSidebar() override;` — The direction that a tab drawer opens relative to the location of the sidebar.
- L94 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SSidebarContainer>& InContainerWidget);` — Constructs the sidebar widget. @param InArgs Widget construction arguments @param InContainerWidget Container widget used to manage the drawer sidebar widgets @param InDockLocation Parent widget that will contain the drawer content widget when docked
- L103 _public prototype_ `bool RegisterDrawer(FSidebarDrawerConfig&& InDrawerConfig);` — Registers and displays a new drawer in the sidebar. @param InDrawerConfig Configuration info for the new drawer @return True if the new drawer registration was successful.
- L112 _public prototype_ `bool UnregisterDrawer(const FName InDrawerId);` — Unregisters and removes a drawer from the sidebar. @param InDrawerId Unique drawer Id to unregister @return True if the drawer removal was successful.
- L121 _public prototype_ `bool ContainsDrawer(const FName InDrawerId) const;` — Checks if a drawer exists in the sidebar. @param InDrawerId Unique drawer Id to check exists @return True if the sidebar contains a drawer with the specified Id.
- L124 _public prototype_ `int32 GetDrawerCount() const;` — @return The number of drawers that exist in the sidebar.
- L134 _public prototype_ `bool RegisterDrawerSection(const FName InDrawerId, const TSharedPtr<ISidebarDrawerContent>& InSection);` — Registers and displays a new drawer section in the sidebar. @param InDrawerId Unique drawer Id to register @param InSection Drawer content interface for the section @return True if the new drawer section registration was successful.
- L144 _public prototype_ `bool UnregisterDrawerSection(const FName InDrawerId, const FName InSectionId);` — Unregisters and removes a drawer section from the sidebar. @param InDrawerId Unique drawer Id that contains the section to unregister @param InSectionId Unique drawer section Id to unregister @return True if the drawer removal was successful.
- L154 _public prototype_ `bool ContainsDrawerSection(const FName InDrawerId, const FName InSectionId) const;` — Checks if a drawer section exists within a sidebar drawer. @param InDrawerId Unique Id of the drawer to look for the section in @param InSectionId Unique drawer section Id to check exists @return True if the sidebar contains a drawer with the specified Id.
- L163 _public prototype_ `bool TryOpenDrawer(const FName InDrawerId);` — Attempt to open a specific drawer in the sidebar. @param InDrawerId Unique Id of the drawer to attempt to open @return True if the drawer exists in this sidebar and was opened.
- L166 _public prototype_ `void CloseAllDrawers(const bool bInAnimate = true);` — Closes any drawers that are open.
- L169 _public prototype_ `bool HasDrawerOpened() const;` — @return True if the sidebar has any drawer that is opened.
- L178 _public prototype_ `bool IsDrawerOpened(const FName InDrawerId) const;` — Checks if a drawer is opened. @param InDrawerId Unique Id of the drawer to check @return True if the specified drawer is currently opened.
- L181 _public prototype_ `FName GetOpenedDrawerId() const;` — @return The unique drawer Id that is currently open.
- L184 _public prototype_ `bool HasDrawerPinned() const;` — @return True if the sidebar has any drawer that is pinned.
- L193 _public prototype_ `bool IsDrawerPinned(const FName InDrawerId) const;` — Checks if a drawer is pinned. @param InDrawerId Unique Id of the drawer to check @return True if the specified drawer is currently pinned.
- L196 _public prototype_ `TSet<FName> GetPinnedDrawerIds() const;` — @return List of drawer Ids that are pinned.
- L204 _public prototype_ `void SetDrawerPinned(const FName InDrawerId, const bool bInIsPinned);` — Pins a drawer so it stays open even when focus is lost. @param InDrawerId Unique Id of the drawer to pin @param bInIsPinned New pin state to set
- L207 _public prototype_ `bool HasDrawerDocked() const;` — @return True if the sidebar has any drawer that is docked.
- L210 _public prototype_ `bool IsDrawerDocked(const FName InDrawerId) const;` — @return True if the specified drawer Id is docked.
- L213 _public prototype_ `TSet<FName> GetDockedDrawerIds() const;` — @return List of drawer Ids that are docked.
- L221 _public prototype_ `void SetDrawerDocked(const FName InDrawerId, const bool bInIsDocked);` — Docks a drawer so it embeds itself into the content. @param InDrawerId Unique Id of the drawer to dock @param bInIsDocked New dock state to set
- L224 _public prototype_ `void UndockAllDrawers();` — Undocks any drawers that are docked.
- L227 _public prototype_ `void UnpinAllDrawers();` — Unpins any drawers that are pinned.
- L230 _public prototype_ `bool IsHorizontal() const;` — @return True if the sidebar is set to animate horizontally.
- L233 _public prototype_ `bool IsVertical() const;` — @return True if the sidebar is set to animate vertically.
- L236 _public prototype_ `FSidebarState GetState() const;` — @return The current state of the sidebar to save/restore.
- L239 _public prototype_ `ESidebarTabLocation GetTabLocation() const;` — @return The location of the sidebar (left, right, top, bottom).
- L241 _public prototype_ `TSharedRef<SWidget> GetMainContent() const;`
- L244 _public prototype_ `void RebuildDrawer(const FName InDrawerId, const bool bInOnlyIfOpen = true);` — Rebuilds a drawer's content (unless it has been overriden).
- L247 _private prototype_ `EVisibility GetSidebarVisibility() const;`
- L249 _private prototype_ `void RecreateDrawerWidgets();`
- L251 _private prototype_ `void OnTabDrawerButtonPressed(const TSharedRef<FSidebarDrawer>& InDrawer);`
- L252 _private prototype_ `void OnDrawerTabPinToggled(const TSharedRef<FSidebarDrawer>& InDrawer, const bool bIsPinned);`
- L253 _private prototype_ `void OnDrawerTabDockToggled(const TSharedRef<FSidebarDrawer>& InDrawer, const bool bIsDocked);`
- L255 _private prototype_ `TSharedRef<SWidget> OnGetTabDrawerContextMenuWidget(TSharedRef<FSidebarDrawer> InDrawer);`
- L256 _private prototype_ `void BuildOptionsMenu(UToolMenu* const InMenu);`
- L259 _private prototype_ `void RemoveDrawer(const TSharedRef<FSidebarDrawer>& InDrawer);` — Removes a single drawer for a specified tab from this sidebar. Removal is done instantly not waiting for any close animation.
- L262 _private prototype_ `void RemoveAllDrawers();` — Removes all drawers instantly (including drawers for pinned tabs).
- L264 _private prototype_ `TSharedPtr<FSidebarDrawer> FindDrawer(const FName InDrawerId) const;`
- L266 _private prototype_ `void SetWidgetDrawerSize(const TSharedRef<FSidebarDrawer>& InDrawer);`
- L268 _private prototype_ `bool AreAllDrawersDocked() const;`
- L270 _private prototype_ `const TArray<TSharedRef<FSidebarDrawer>>& GetAllDrawers() const;`
- L272 _private member_ `TWeakPtr<SSidebarContainer> ContainerWidgetWeak;`
- L274 _private member_ `ESidebarTabLocation TabLocation = ESidebarTabLocation::Right;`
- L275 _private member_ `FOnGetContent OnGetContent;`
- L276 _private member_ `bool bHideWhenAllDocked = false;`
- L277 _private member_ `bool bAlwaysUseMaxButtonSize = false;`
- L278 _private member_ `bool bDisablePin = false;`
- L279 _private member_ `bool bDisableDock = false;`
- L280 _private member_ `FOnSidebarStateChanged OnStateChanged;`
- L282 _private member_ `TSharedPtr<SScrollBox> TabButtonContainer;`
- L284 _private member_ `TArray<TSharedRef<FSidebarDrawer>> Drawers;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TOOLWIDGETS_API`
- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSidebarStateChanged, const FSidebarState& );`
- L45 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSidebarStateChanged, const FSidebarState& );`

### `Source/Developer/ToolWidgets/Public/Sidebar/SSidebarContainer.h` (Public)


#### class `SSidebarContainer`  
`class SSidebarContainer : public SCompoundWidget`  
_L19-135_
- inherits: `SCompoundWidget`
- desc: A container for a sidebar widget that manages the slider drawer overlay widgets and a default docking location for all drawers.
- L24 _public function_ `SLATE_BEGIN_ARGS(SSidebarContainer)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `void RebuildSidebar(const TSharedRef<SSidebar>& InSidebarWidget, const FSidebarState& InState);`
- L32 _public prototype_ `float GetContentSlotSize() const;`
- L33 _public prototype_ `float GetSidebarSlotSize() const;`
- L35 _public prototype_ `EOrientation GetSplitterOrientation() const;`
- L36 _public prototype_ `ESidebarTabLocation GetTabLocation() const;`
- L37 _public prototype_ `float GetCurrentDrawerSize() const;`
- L38 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetOverlaySize() const;`
- L40 _public prototype_ `void CloseAllDrawerWidgets(const bool bInAnimate);`
- L43 _public prototype_ `void SummonPinnedTabIfNothingOpened();` — Reopens the pinned tab only if there are no other open drawers. This should be used to bring pinned tabs back after other tabs lose focus/are closed.
- L46 _public prototype_ `void UpdateDrawerTabAppearance();` — Updates the appearance of drawer tabs.
- L48 _public prototype_ `FName GetOpenedDrawerId() const;`
- L51 _protected prototype_ `void Reconstruct(const FSidebarState& InState = FSidebarState());`
- L53 _protected prototype_ `TSharedRef<SWidget> ConstructBoxPanel(const FSidebarState& InState);`
- L54 _protected prototype_ `void ConstructSplitterPanel(const FSidebarState& InState);`
- L56 _protected prototype_ `FMargin CalculateSlotMargin() const;`
- L58 _protected prototype_ `void CreateDrawerWidget(const TSharedRef<FSidebarDrawer>& InDrawer);`
- L60 _protected prototype_ `TSharedRef<SWidget> GetSidebarDrawerContent(const TSharedRef<FSidebarDrawer>& InDrawer) const;`
- L62 _protected prototype_ `bool AddDrawerOverlaySlot(const TSharedRef<FSidebarDrawer>& InDrawer);`
- L63 _protected prototype_ `bool RemoveDrawerOverlaySlot(const TSharedRef<FSidebarDrawer>& InDrawer, const bool bInAnimate);`
- L65 _protected prototype_ `void AddContentDockSlot();`
- L66 _protected prototype_ `void RemoveContentDockSlot();`
- L68 _protected prototype_ `void AddSidebarDockSlot(const FName InDockDrawerId);`
- L69 _protected prototype_ `void RemoveSidebarDockSlot();`
- L71 _protected prototype_ `void OnTabDrawerFocusLost(const TSharedRef<SSidebarDrawer>& InDrawerWidget);`
- L72 _protected prototype_ `void OnOpenAnimationFinish(const TSharedRef<SSidebarDrawer>& InDrawerWidget);`
- L73 _protected prototype_ `void OnCloseAnimationFinish(const TSharedRef<SSidebarDrawer>& InDrawerWidget);`
- L74 _protected prototype_ `void OnDrawerSizeChanged(const TSharedRef<SSidebarDrawer>& InDrawerWidget, const float InNewPixelSize);`
- L76 _protected prototype_ `EActiveTimerReturnType OnOpenPendingDrawerTimer(const double InCurrentTime, const float InDeltaTime);`
- L78 _protected prototype_ `void OpenDrawerNextFrame(const TSharedRef<FSidebarDrawer>& InDrawer, const bool bInAnimate = true);`
- L79 _protected prototype_ `void OpenDrawer_Internal(const TSharedRef<FSidebarDrawer>& InDrawer, const bool bInAnimate = true);`
- L80 _protected prototype_ `void CloseDrawer_Internal(const TSharedRef<FSidebarDrawer>& InDrawer, const bool bInAnimate = true , const bool bInSummonPinnedTabIfNothingOpened = true);`
- L83 _protected prototype_ `void DockDrawer_Internal(const TSharedRef<FSidebarDrawer>& InDrawer);`
- L84 _protected prototype_ `void UndockDrawer_Internal(const TSharedRef<FSidebarDrawer>& InDrawer);`
- L86 _protected prototype_ `TSharedPtr<FSidebarDrawer> FindDrawer(const FName InDrawerId) const;`
- L87 _protected prototype_ `TSharedPtr<FSidebarDrawer> FindFirstPinnedTab() const;`
- L89 _protected prototype_ `TSharedPtr<SSidebarDrawer> FindOpenDrawerWidget(const TSharedRef<FSidebarDrawer>& InDrawer) const;`
- L91 _protected prototype_ `TSharedPtr<FSidebarDrawer> GetForegroundDrawer() const;`
- L94 _protected prototype_ `void OnContentSlotResizing(const float InFillPercent);` — Event that occurs when the docked main content slot is being resized by the user (while mouse down).
- L96 _protected prototype_ `void OnSidebarSlotResizing(const float InFillPercent);` — Event that occurs when the docked sidebar slot is being resized by the user (while mouse down).
- L99 _protected prototype_ `void OnSplitterResized();` — Event that occurs when the main splitter widget has finished being resized by the user (mouse up).
- L101 _protected prototype_ `int32 GetContentSlotIndex() const;`
- L102 _protected prototype_ `int32 GetSidebarSlotIndex() const;`
- L104 _protected prototype_ `void BroadcastDrawerOpenClose(const TSharedRef<FSidebarDrawer>& InDrawer, const bool bOpen);`
- L107 _protected member_ `TSharedPtr<SSidebar> SidebarWidget;` — The sidebar widget associated with this container. One sidebar widget per container.
- L110 _protected member_ `TSharedPtr<SSplitter> MainSplitter;` — The main splitter widget used when a drawer is docked.
- L113 _protected member_ `TSharedPtr<SOverlay> DrawersOverlay;` — Overlay used to draw drawer widgets on top of the rest of the content.
- L118 _protected member_ `TArray<TSharedRef<SSidebarDrawer>> OpenDrawerWidgets;` — Generally speaking one drawer is only ever open at once but we animate any previous drawer closing so there could be more than one while an animation is playing. A docked drawer is also considered open, along with any user opened/pinned drawers.
- L120 _protected member_ `TArray<TSharedRef<SSidebarDrawer>> ClosingDrawerWidgets;`
- L122 _protected member_ `TWeakPtr<FSidebarDrawer> PendingTabToOpen;`
- L123 _protected member_ `bool bAnimatePendingTabOpen = false;`
- L124 _protected member_ `TSharedPtr<FActiveTimerHandle> OpenPendingDrawerTimerHandle;`
- L126 _protected member_ `float ContentSizePercent = 0.8f;`
- L127 _protected member_ `float SidebarSizePercent = 0.2f;`
- L129 _protected member_ `TAttribute<float> ContentSlotSize;`
- L130 _protected member_ `TAttribute<float> SidebarSlotSize;`
- L132 _protected member_ `bool bWantsToAutoDock = false;`
- L133 _protected member_ `float ContentSizeBeforeResize = 0.f;`
- L134 _protected member_ `float SidebarSizeBeforeResize = 0.f;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/Sidebar/SidebarDrawerConfig.h` (Public)


#### struct `FSidebarDrawerConfig`  
`struct FSidebarDrawerConfig`  
_L16-60_
- desc: Configuration information used to register a sidebar drawer.
- L18 _public function_ `bool operator==(const FName InOtherId) const`
- L23 _public function_ `bool operator!=(const FName InOtherId) const`
- L28 _public function_ `bool operator==(const FSidebarDrawerConfig& InOther) const`
- L33 _public function_ `bool operator!=(const FSidebarDrawerConfig& InOther) const`
- L39 _public member_ `FName UniqueId;` — Unique Id used to identify the drawer
- L42 _public member_ `float SortOrder = 10.f;` — Primary sort order of the drawer tab button. Secondary sort by ButtonText property.
- L45 _public member_ `TAttribute<FText> ButtonText;` — Text to display on the drawer tab button
- L48 _public member_ `TAttribute<FText> ToolTipText;` — ToolTip text to display for the drawer tab button
- L51 _public member_ `TAttribute<const FSlateBrush*> Icon;` — Icon to display for the drawer tab button
- L54 _public member_ `FSidebarDrawerState InitialState;` — The state of the sidebar drawer. (Visible, Pinned, Docked, Size)
- L57 _public member_ `TSharedPtr<SWidget> OverrideContentWidget;` — Optional content widget to use instead of registering sections.

### `Source/Developer/ToolWidgets/Public/Sidebar/SidebarState.h` (Public)


#### struct `FSidebarDrawerState`  
`struct FSidebarDrawerState`  
_L11-33_
- reflection: `USTRUCT()`
- desc: Represents the state of a sidebar drawer to be saved/restored to/from config.
- L15 _public function_ `FSidebarDrawerState()`
- L16 _public function_ `FSidebarDrawerState(const FName InDrawerId)`
- L22 _public member_ `FName DrawerId = NAME_None;` — `UPROPERTY()`
- L26 _public member_ `TSet<FName> SelectedSections;` — `UPROPERTY()` — Names of all sections that were last selected
- L29 _public member_ `bool bIsPinned = false;` — `UPROPERTY()`
- L32 _public member_ `bool bIsDocked = false;` — `UPROPERTY()`

#### struct `FSidebarState`  
`struct FSidebarState`  
_L37-83_
- reflection: `USTRUCT()`
- desc: Represents the state of a sidebar to be saved/restored to/from config.
- L42 _public member_ `static constexpr float DefaultSize = 0.25f;`
- L43 _public member_ `static constexpr float MinSize = 0.005f;`
- L44 _public member_ `static constexpr float MaxSize = 0.5f;`
- L45 _public member_ `static constexpr float AutoDockThresholdSize = 0.05f;`
- L48 _public prototype_ `bool IsValid() const;` — @return True if any property has been changed from default
- L50 _public prototype_ `bool IsHidden() const;`
- L51 _public prototype_ `bool IsVisible() const;`
- L53 _public prototype_ `void SetHidden(const bool bInHidden);`
- L54 _public prototype_ `void SetVisible(const bool bInVisible);`
- L56 _public prototype_ `float GetDrawerSize() const;`
- L57 _public prototype_ `void SetDrawerSize(const float InSize);`
- L59 _public prototype_ `void GetDrawerSizes(float& OutDrawerSize, float& OutContentSize) const;`
- L60 _public prototype_ `void SetDrawerSizes(const float InDrawerSize, const float InContentSize);`
- L62 _public prototype_ `const TArray<FSidebarDrawerState>& GetDrawerStates() const;`
- L64 _public prototype_ `FSidebarDrawerState& FindOrAddDrawerState(const FSidebarDrawerState& InDrawerState);`
- L65 _public prototype_ `const FSidebarDrawerState* FindDrawerState(const FSidebarDrawerState& InDrawerState);`
- L68 _public prototype_ `void SaveDrawerState(const FSidebarDrawerState& InState);` — Saves the state of a drawer. If the drawers state already exists in config, it will be replaced.
- L72 _protected member_ `bool bHidden = false;` — `UPROPERTY()`
- L75 _protected member_ `float DrawerSize = 0.f;` — `UPROPERTY()`
- L79 _protected member_ `float ContentSize = 0.f;` — `UPROPERTY()` — Save the other splitter slot size to exactly restore the size when a drawer is docked in a SSplitter widget.
- L82 _protected member_ `TArray<FSidebarDrawerState> DrawerStates;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TOOLWIDGETS_API`

### `Source/Developer/ToolWidgets/Public/ToolWidgetsSlateTypes.h` (Public)


#### enum `EActionButtonType`  
`enum class EActionButtonType : uint8`  
_L11-21_
- L13 _public enumerator_ `Default` — A default, grey button
- L14 _public enumerator_ `Simple` — A button with a left-aligned label, and no background or border when unhovered
- L15 _public enumerator_ `Primary` — A primary blue button with white text, use for buttons when it's the next logical step (ie. "Next", "OK")
- L16 _public enumerator_ `Positive` — A grey button with a green icon indicating a positive action, like "Add"
- L17 _public enumerator_ `Warning` — A grey button with a yellow icon indicating a negative action, like "Mute"
- L18 _public enumerator_ `Error` — A grey button with a red icon indicating a negative action, like "Cancel"
- L20 _public enumerator_ `Num`

#### struct `FActionButtonStyle`  
`struct FActionButtonStyle : public FSlateWidgetStyle`  
_L27-151_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an SActionButton
- L31 _public prototype_ `FActionButtonStyle();`
- L33 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L35 _public member_ `static const FName TypeName;`
- L36 _public prototype_ `virtual const FName GetTypeName() const override;`
- L38 _public prototype_ `static const FActionButtonStyle& GetDefault();`
- L43 _public prototype_ `EActionButtonType GetActionButtonType() const;` — The type to use for our SActionButton.
- L44 _public prototype_ `FActionButtonStyle& SetActionButtonType(const EActionButtonType InActionButtonType);`
- L50 _public member_ `FButtonStyle ButtonStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — The style to use for our SButton.
- L51 _public prototype_ `FActionButtonStyle& SetButtonStyle(const FButtonStyle& InButtonStyle);`
- L56 _public prototype_ `const FButtonStyle& GetIconButtonStyle() const;` — The style to use for our SButton when an icon is present. ButtonStyle used if not specified.
- L57 _public prototype_ `FActionButtonStyle& SetIconButtonStyle(const FButtonStyle& InButtonStyle);`
- L63 _public member_ `TOptional<FMargin> ButtonContentPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Spacing between button's border and the content. Default uses ButtonStyle.
- L65 _public prototype_ `FMargin GetButtonContentPadding() const;`
- L66 _public prototype_ `FActionButtonStyle& SetButtonContentPadding(const FMargin& InContentPadding);`
- L72 _public member_ `FComboButtonStyle ComboButtonStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — The style to use for our SComboButton.
- L73 _public prototype_ `FActionButtonStyle& SetComboButtonStyle(const FComboButtonStyle& InComboButtonStyle);`
- L79 _public member_ `bool bHasDownArrow;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Whether to show a down arrow for the combo button
- L80 _public prototype_ `FActionButtonStyle& SetHasDownArrow(const bool& bInHasDownArrow);`
- L86 _public member_ `TOptional<FMargin> ComboButtonContentPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Spacing between button's border and the content. Default uses ComboButtonStyle.
- L88 _public prototype_ `FMargin GetComboButtonContentPadding() const;`
- L89 _public prototype_ `FActionButtonStyle& SetComboButtonContentPadding(const FMargin& InContentPadding);`
- L95 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalContentAlignment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Horizontal Content alignment within the button.
- L96 _public prototype_ `FActionButtonStyle& SetHorizontalContentAlignment(const EHorizontalAlignment& InAlignment);`
- L102 _public member_ `FTextBlockStyle TextBlockStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — The style to use for the button Text.
- L103 _public prototype_ `FActionButtonStyle& SetTextBlockStyle(const FTextBlockStyle& InTextBlockStyle);`
- L109 _public member_ `TOptional<FSlateBrush> IconBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)` — Icon Brush to use.
- L110 _public prototype_ `FActionButtonStyle& SetIconBrush(const FSlateBrush& InIconBrush);`
- L116 _public member_ `TOptional<FSlateColor> IconColorAndOpacity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Icon Color/Tint, defaults is determined by ActionButtonType.
- L117 _public prototype_ `FActionButtonStyle& SetIconColorAndOpacity(const FSlateColor& InIconColorAndOpacity);`
- L123 _public member_ `TOptional<FMargin> IconNormalPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — If set and the button's icon is non-null, overrides the button style's additional spacing between the button's border and the content when not pressed.
- L124 _public prototype_ `FActionButtonStyle& SetIconNormalPadding(const FMargin& InIconNormalPadding);`
- L130 _public member_ `TOptional<FMargin> IconPressedPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — If set and the button's icon is non-null, overrides the button style's additional spacing between the button's border and the content when pressed.
- L131 _public prototype_ `FActionButtonStyle& SetIconPressedPadding(const FMargin& InIconPressedPadding);`
- L137 _public prototype_ `void UnlinkColors();` — Unlinks all colors in this style. @see FSlateColor::Unlink
- L144 _private member_ `FName ActionButtonType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (AllowPrivateAccess = "true", GetOptions = "Engine.ToolSlateWidgetTypesFunctionLibrary.GetActionButtonTypeNames"))` — The type to use for our SActionButton.
- L150 _private member_ `TOptional<FButtonStyle> IconButtonStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (AllowPrivateAccess = "true"))` — The style to use for our SButton when an icon is present. ButtonStyle used if not specified.

#### class `UToolSlateWidgetTypesFunctionLibrary`  
`class UToolSlateWidgetTypesFunctionLibrary : public UObject`  
_L154-164_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L162 _public prototype_ `static const TArray<FName>& GetActionButtonTypeNames();` — `UFUNCTION()`

### `Source/Developer/ToolWidgets/Public/ToolWidgetsStyle.h` (Public)


#### class `UE::ToolWidgets::FToolWidgetsStyle`  
`class FToolWidgetsStyle final : public FSlateStyleSet`  
_L9-20_
- inherits: `FSlateStyleSet`
- L13 _public member_ `static FName StyleName;`
- L15 _public prototype_ `static FToolWidgetsStyle& Get();`
- L18 _private prototype_ `FToolWidgetsStyle();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ToolWidgets` (scope `UE`)

### `Source/Developer/ToolWidgets/Public/WidgetDrawerConfig.h` (Public)


#### struct `FWidgetDrawerConfig`  
`struct FWidgetDrawerConfig`  
_L15-42_
- L17 _public function_ `FWidgetDrawerConfig(FName InUniqueId) : UniqueId(InUniqueId)`
- L21 _public member_ `FName UniqueId;`
- L22 _public member_ `FOnGetContent GetDrawerContentDelegate;`
- L23 _public member_ `FOnGetVisiblity GetDrawerButtonVisibilityDelegate;`
- L24 _public member_ `FOnStatusBarDrawerOpened OnDrawerOpenedDelegate;`
- L25 _public member_ `FOnStatusBarDrawerDismissed OnDrawerDismissedDelegate;`
- L27 _public member_ `TSharedPtr<SWidget> CustomWidget;`
- L28 _public member_ `FText ButtonText;`
- L29 _public member_ `FText ToolTipText;`
- L30 _public member_ `const FSlateBrush* Icon = nullptr;`
- L31 _public member_ `TSharedRef<SHorizontalBox> CustomButtonWidgets = SNew(SHorizontalBox);`
- L33 _public function_ `bool operator==(const FName& OtherId) const`
- L38 _public function_ `bool operator==(const FWidgetDrawerConfig& Other) const`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStatusBarDrawerOpened, FName StatusBarName) DECLARE_DELEGATE_OneParam(FOnStatusBarDrawerDismissed, const TSharedPtr<SWidget>&) DECLARE_DELEGATE_RetVal_OneParam(EVisibility, FOnGetVisiblity, FName StatusBarName) struct FWidgetDrawerConfig { FWidgetDrawerConfig(FName InUniqueId) : UniqueId(InUniqueId) {} FName UniqueId; FOnGetContent GetDrawerContentDelegate; FOnGetVisiblity GetDrawerButtonVisibilityDelegate; FOnStatusBarDrawerOpened OnDrawerOpenedDelegate; FOnStatusBarDrawerDismissed OnDrawerDismissedDelegate; TSharedPtr<SWidget> CustomWidget; FText ButtonText; FText ToolTipText; const FSlateBrush* Icon = nullptr; TSharedRef<SHorizontalBox> CustomButtonWidgets = SNew(SHorizontalBox); bool operator==(const FName& OtherId) const { return UniqueId == OtherId; } bool operator==(const FWidgetDrawerConfig& Other) const { return UniqueId == Other.UniqueId; } };`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStatusBarDrawerDismissed, const TSharedPtr<SWidget>&) DECLARE_DELEGATE_RetVal_OneParam(EVisibility, FOnGetVisiblity, FName StatusBarName) struct FWidgetDrawerConfig { FWidgetDrawerConfig(FName InUniqueId) : UniqueId(InUniqueId) {} FName UniqueId; FOnGetContent GetDrawerContentDelegate; FOnGetVisiblity GetDrawerButtonVisibilityDelegate; FOnStatusBarDrawerOpened OnDrawerOpenedDelegate; FOnStatusBarDrawerDismissed OnDrawerDismissedDelegate; TSharedPtr<SWidget> CustomWidget; FText ButtonText; FText ToolTipText; const FSlateBrush* Icon = nullptr; TSharedRef<SHorizontalBox> CustomButtonWidgets = SNew(SHorizontalBox); bool operator==(const FName& OtherId) const { return UniqueId == OtherId; } bool operator==(const FWidgetDrawerConfig& Other) const { return UniqueId == Other.UniqueId; } };`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EVisibility, FOnGetVisiblity, FName StatusBarName) struct FWidgetDrawerConfig { FWidgetDrawerConfig(FName InUniqueId) : UniqueId(InUniqueId) {} FName UniqueId; FOnGetContent GetDrawerContentDelegate; FOnGetVisiblity GetDrawerButtonVisibilityDelegate; FOnStatusBarDrawerOpened OnDrawerOpenedDelegate; FOnStatusBarDrawerDismissed OnDrawerDismissedDelegate; TSharedPtr<SWidget> CustomWidget; FText ButtonText; FText ToolTipText; const FSlateBrush* Icon = nullptr; TSharedRef<SHorizontalBox> CustomButtonWidgets = SNew(SHorizontalBox); bool operator==(const FName& OtherId) const { return UniqueId == OtherId; } bool operator==(const FWidgetDrawerConfig& Other) const { return UniqueId == Other.UniqueId; } };`
