# Runtime / GameMenuBuilder

- module root: `Source/Runtime/GameMenuBuilder`
- headers: 8; symbols: 266
- symbol kinds: class=9, delegate=9, enum=3, enumerator=10, function=46, member=89, namespace=3, prototype=95, struct=1, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore

### `Source/Runtime/GameMenuBuilder/Public/GameMenuBuilder.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/GameMenuBuilder/Public/GameMenuBuilderModule.h` (Public)


#### class `IGameMenuBuilderModule`  
`class IGameMenuBuilderModule : public IModuleInterface`  
_L13-28_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IGameMenuBuilderModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed

#### class `FGameMenuBuilderModule`  
`class FGameMenuBuilderModule : public IGameMenuBuilderModule`  
_L30-40_
- inherits: `IGameMenuBuilderModule`
- L32 _private function_ `virtual void StartupModule() override`
- L36 _private function_ `void SetStyleName()`

### `Source/Runtime/GameMenuBuilder/Public/GameMenuBuilderStyle.h` (Public)


#### class `FGameMenuBuilderStyle`  
`class FGameMenuBuilderStyle`  
_L12-33_
- L16 _public prototype_ `static void Initialize(const FString StyleName);`
- L18 _public prototype_ `static void Shutdown();`
- L21 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L24 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set
- L26 _public prototype_ `static FName GetStyleSetName();`
- L30 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create(const FString StyleName);`
- L32 _private member_ `static TSharedPtr< class FSlateStyleSet > SimpleStyleInstance;`

### `Source/Runtime/GameMenuBuilder/Public/GameMenuItem.h` (Public)


#### enum `EGameMenuItemType::Type`  
`enum Type`  
_L15-21_
- L17 _public enumerator_ `Root`
- L18 _public enumerator_ `Standard`
- L19 _public enumerator_ `MultiChoice`
- L20 _public enumerator_ `CustomWidget`

#### class `FGameMenuItem`  
`class FGameMenuItem : public TSharedFromThis<FGameMenuItem>`  
_L24-120_
- inherits: `TSharedFromThis<FGameMenuItem>`
- L28 _public prototype_ `DECLARE_DELEGATE(FOnConfirmMenuItem);` — confirm menu item delegate
- L31 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnOptionChanged, TSharedPtr<FGameMenuItem>, int32);` — multi-choice option changed, parameters are menu item itself and new multi-choice index
- L34 _public member_ `FOnConfirmMenuItem OnConfirmMenuItem;` — delegate, which is executed by SSimpleMenuWidget if user confirms this menu item
- L37 _public member_ `FOnOptionChanged OnOptionChanged;` — multi-choice option changed, parameters are menu item itself and new multi-choice index
- L40 _public member_ `EGameMenuItemType::Type MenuItemType;` — menu item type
- L43 _public member_ `FText Text;` — menu item text
- L46 _public member_ `TSharedPtr<class FGameMenuPage> SubMenu;` — sub menu if present
- L49 _public member_ `TSharedPtr<SGameMenuItemWidget> Widget;` — shared pointer to actual slate widget representing the menu item
- L52 _public member_ `TSharedPtr<SGameMenuItemWidget> CustomWidget;` — shared pointer to actual slate widget representing the custom menu item, ie whole options screen
- L55 _public member_ `TArray<FText> MultiChoice;` — texts for multiple choice menu item (like INF AMMO ON/OFF or difficulty/resolution etc)
- L58 _public member_ `int32 MinMultiChoiceIndex;` — set to other value than -1 to limit the options range
- L61 _public member_ `int32 MaxMultiChoiceIndex;` — set to other value than -1 to limit the options range
- L64 _public member_ `int32 SelectedMultiChoice;` — selected multi-choice index for this menu item
- L67 _public member_ `bool bInactive;` — true if this item is active
- L70 _public function_ `FGameMenuItem(FText _text)` — constructor accepting menu item text
- L79 _public function_ `FGameMenuItem(TSharedPtr<SGameMenuItemWidget> InWidget)` — custom widgets cannot contain sub menus, all functionality must be handled by custom widget itself
- L88 _public function_ `FGameMenuItem(FText InText, TArray<FText> InOptions, int32 InDefaultIndex=0)` — constructor for multi-choice item
- L98 _public function_ `bool ConfirmPressed()`
- L110 _public function_ `static TSharedRef<FGameMenuItem> CreateRoot()` — create special root item
- L116 _private function_ `FGameMenuItem()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EGameMenuItemType`
- L28 _delegate_ `DECLARE_DELEGATE(FOnConfirmMenuItem);` — confirm menu item delegate
- L31 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnOptionChanged, TSharedPtr<FGameMenuItem>, int32);` — multi-choice option changed, parameters are menu item itself and new multi-choice index

### `Source/Runtime/GameMenuBuilder/Public/GameMenuPage.h` (Public)


#### class `FGameMenuPage`  
`class FGameMenuPage : public TSharedFromThis<FGameMenuPage>`  
_L16-230_
- inherits: `TSharedFromThis<FGameMenuPage>`
- L19 _public prototype_ `FGameMenuPage();`
- L22 _public prototype_ `DECLARE_DELEGATE(FOnMenuGoBack);` — Delegate for when user is going back from submenu.
- L25 _public prototype_ `DECLARE_DELEGATE(FOnMenuHidden);` — Delegate for when menu is hidden.
- L28 _public prototype_ `DECLARE_DELEGATE(FOnMenuOpening);` — Delegate for when menu is about to open.
- L37 _public prototype_ `bool InitialiseRootMenu(APlayerController* InPCOwner, const FString& InStyleName, UGameViewportClient* InGameViewport);` — Initialize the menu page widget and set this menu as root. @param	InPCOwner		Player controller that owns this menu. @param	InStyleName		Name of the menu style to use. @param	InGameViewport	Gameviewport on which to place the menu. @returns true on success. (Will fail if viewport invalid)
- L39 _public prototype_ `void DestroyRootMenu();`
- L42 _public prototype_ `int32 NumItems() const;` — Return the number of items in menu item list.
- L45 _public prototype_ `TSharedPtr<FGameMenuItem> GetItem(int32 Index) const;` — Get the specified item in the menu item list. Will assert if the value is out of range.
- L48 _public prototype_ `bool IsValidMenuEntryIndex(int32 Index) const;` — Is the supplied index with the valid range of menu items. Returns false if it is not.
- L51 _public member_ `TWeakObjectPtr<APlayerController> PCOwner;` — Weak pointer to Owning player controller.
- L54 _public prototype_ `void ShowRootMenu();` — Builds the menu widget and shows the menu.
- L57 _public member_ `int32 SelectedIndex;` — Current selection in this menu.
- L60 _public member_ `FText MenuTitle;` — The menu title.
- L69 _public prototype_ `TSharedRef<FGameMenuItem> AddMenuItem(const FText& Text, TSharedPtr<FGameMenuPage> InSubMenu = nullptr);` — Add a menu item. @param	Text		The string for the item (EG START GAME) @param	InSubMenu	Any submenu associated with the item @returns A shared reference to the created item
- L81 _public function_ `template< class UserClass > inline TSharedRef<FGameMenuItem> AddMenuItem(const FText& InText, UserClass* InObj, typename FGameMenuItem::FOnConfirmMenuItem::TMethodPtr< UserClass > InMethod)` — Add a menu item. @param	Text		Label of the menu item @param	InObj		Menu page object @param	InMethod	Method to call when selection changes. @returns  SharedRef to the MenuItem that was created.
- L99 _public function_ `template< class UserClass > inline TSharedRef<FGameMenuItem> AddMenuItemWithOptions(const FText& Text, const TArray<FText>& OptionsList, UserClass* InObj, typename FGameMenuItem::FOnOptionChanged::TMethodPtr< UserClass > InMethod)` — Add a menu entry with a variable number of selectable options @param	Text		Label of the menu item @param	OptionsList	List of selectable items @param	InObj		Menu page object @param	InMethod	Method to call when selection changes. @returns  SharedRef to the MenuItem that was created.
- L117 _public function_ `template< class UserClass > inline TSharedRef<FGameMenuItem> AddCustomMenuItem(const FText& Text, TSharedPtr<SGameMenuItemWidget> CustomWidget, UserClass* InObj, typename FGameMenuItem::FOnOptionChanged::TMethodPtr< UserClass > InMethod)` — Add a custom menu entry @param	Text		Label of the menu item @param @param @param @returns  SharedRef to the MenuItem that was created.
- L132 _public function_ `template< class UserClass > inline void SetCancelHandler(UserClass* InObj, typename FGameMenuPage::FOnMenuGoBack::TMethodPtr< UserClass > InMethod)` — Add a handler for the menu being canceled. @param	InObj		Menu page object @param	InMethod	Method to call when selection changes.
- L144 _public function_ `template< class UserClass > inline void SetOnHiddenHandler(UserClass* InObj, typename FGameMenuPage::FOnMenuHidden::TMethodPtr< UserClass > InMethod)` — Add a handler for the menu being canceled. @param	InObj		Menu page object @param	InMethod	Method to call when menu has been hidden.
- L156 _public function_ `template< class UserClass > inline void SetAcceptHandler(UserClass* InObj, typename FGameMenuPage::FOnMenuGoBack::TMethodPtr< UserClass > InMethod)` — Add a handler for the menu being accepted. @param	InObj		Menu page object @param	InMethod	Method to call when selection changes.
- L168 _public function_ `template< class UserClass > inline void SetOnOpenHandler(UserClass* InObj, typename FGameMenuPage::FOnMenuHidden::TMethodPtr< UserClass > InMethod)` — Add a handler for the menu being opened. @param	InObj		Menu page object @param	InMethod	Method to call when menu is about to open.
- L178 _public prototype_ `void LockControls(bool bLockState);` — Lock/Unlock the menu and prevent user interaction. @param		bLockState	true to lock
- L181 _public member_ `TSharedPtr<SGameMenuPageWidget> RootMenuPageWidget;` — The widget that is the menu.
- L184 _public function_ `void MenuGoBack()` — Executed when user want's to go back to previous menu.
- L190 _public function_ `void MenuGoBackCancel()` — Called when user want's to CANCEL and go back to previous menu.
- L196 _public function_ `void MenuHidden()` — Called when the menu has finished hiding.
- L202 _public function_ `void MenuOpening()` — Called when the menu is about to be opened.
- L208 _public prototype_ `void HideMenu();` — Hide the menu.
- L211 _public prototype_ `void RemoveAllItems();` — Remove all the items from the item array.
- L216 _protected member_ `FOnMenuGoBack OnGoBack;` — Executed when user want's to go back to previous menu.
- L219 _protected member_ `FOnMenuGoBack OnGoBackCancel;` — Executed when user want's to CANCEL and go back to previous menu.
- L222 _protected member_ `FOnMenuHidden OnMenuHidden;` — Delegate, which is executed when menu is finished hiding.
- L225 _protected member_ `FOnMenuOpening OnMenuOpening;` — Delegate, which is executed when menu is about to open.
- L228 _protected typedef_ `typedef TArray< TSharedPtr<FGameMenuItem> > MenuItemList;` — Array of menu items that represents the menu.
- L229 _protected member_ `MenuItemList MenuItems;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE(FOnMenuGoBack);` — Delegate for when user is going back from submenu.
- L25 _delegate_ `DECLARE_DELEGATE(FOnMenuHidden);` — Delegate for when menu is hidden.
- L28 _delegate_ `DECLARE_DELEGATE(FOnMenuOpening);` — Delegate for when menu is about to open.

### `Source/Runtime/GameMenuBuilder/Public/GameMenuWidgetStyle.h` (Public)


#### enum `GameMenuLayoutType::Type`  
`enum Type : int`  
_L19-25_
- L22 _public enumerator_ `Single` — Single one page menu.
- L24 _public enumerator_ `SideBySide` — Side by side menu. Main menu on left, any sub menu on right.

#### struct `FGameMenuStyle`  
`struct FGameMenuStyle : public FSlateWidgetStyle`  
_L29-181_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- L33 _public prototype_ `FGameMenuStyle();`
- L34 _public prototype_ `virtual ~FGameMenuStyle();`
- L37 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;` — FSlateWidgetStyle
- L38 _public member_ `static const FName TypeName;`
- L39 _public function_ `virtual const FName GetTypeName() const override`
- L40 _public prototype_ `static const FGameMenuStyle& GetDefault();`
- L46 _public member_ `FSlateBrush MenuTopBrush;` — `UPROPERTY(EditAnywhere, Category = Brushes)` — The brush used to draw the top of the menu
- L47 _public function_ `FGameMenuStyle& SetMenuTopBrush(const FSlateBrush& InMenuTopBrush)`
- L53 _public member_ `FSlateBrush MenuFrameBrush;` — `UPROPERTY(EditAnywhere, Category = Brushes)` — The brush used to draw the menu border
- L54 _public function_ `FGameMenuStyle& SetMenuFrameBrush(const FSlateBrush& InMenuFrameBrush)`
- L60 _public member_ `FSlateBrush MenuBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Brushes)` — The brush used to draw the menu background
- L61 _public function_ `FGameMenuStyle& SetMenuBackgroundBrush(const FSlateBrush& InMenuBackgroundBrush)`
- L67 _public member_ `FSlateBrush MenuSelectBrush;` — `UPROPERTY(EditAnywhere, Category = Brushes)` — The brush used to draw the selected menu item
- L68 _public function_ `FGameMenuStyle& SetMenuSelectBrush(const FSlateBrush& InMenuSelectBrush)`
- L74 _public member_ `FSlateSound MenuEnterSound;` — `UPROPERTY(EditAnywhere, Category = Sound)` — The sound the menu should play when entering a sub-menu
- L75 _public function_ `FGameMenuStyle& SetMenuEnterSound(const FSlateSound& InMenuEnterSound)`
- L81 _public member_ `FSlateSound MenuBackSound;` — `UPROPERTY(EditAnywhere, Category = Sound)` — The sound the menu should play when returning to a parent menu
- L82 _public function_ `FGameMenuStyle& SetMenuBackSound(const FSlateSound& InMenuBackSound)`
- L88 _public member_ `FSlateSound OptionChangeSound;` — `UPROPERTY(EditAnywhere, Category = Sound)` — The sound the menu should play when a menu option is changed
- L89 _public function_ `FGameMenuStyle& SetOptionChangeSound(const FSlateSound& InOptionChangeSound)`
- L95 _public member_ `FSlateSound MenuItemChangeSound;` — `UPROPERTY(EditAnywhere, Category = Sound)` — The sound the menu should play when the selected menu item is changed
- L96 _public function_ `FGameMenuStyle& SetMenuItemChangeSound(const FSlateSound& InMenuItemChangeSound)`
- L102 _public member_ `FSlateSound MenuItemInactiveSound;` — `UPROPERTY(EditAnywhere, Category = Sound)` — The sound the menu should play when the selected menu item is disabled or unbound
- L103 _public function_ `FGameMenuStyle& SetMenuItemInactiveSound(const FSlateSound& InMenuItemInactiveSound)`
- L109 _public member_ `FSlateSound MenuItemChosenSound;` — `UPROPERTY(EditAnywhere, Category = Sound)` — The sound the menu should play when the selected menu item is chosen
- L110 _public function_ `FGameMenuStyle& SetMenuItemChosenSound(const FSlateSound& InMenuItemChosenSound)`
- L116 _public member_ `float LeftMarginPercent;` — `UPROPERTY(EditAnywhere, Category = Layout)` — The left hand margin for the main menu
- L117 _public function_ `FGameMenuStyle& SetMenuLeftMarginPercent(const float InLeftMarginPercent)`
- L123 _public member_ `float SubMenuMarginPercent;` — `UPROPERTY(EditAnywhere, Category = Layout)` — The left hand margin for the sub menu
- L124 _public function_ `FGameMenuStyle& SetSubMenuMarginPercent(const float InSubMenuMarginPercent)`
- L130 _public member_ `TEnumAsByte<GameMenuLayoutType::Type> LayoutType;` — `UPROPERTY(EditAnywhere, Category = Layout)` — Layout type.
- L131 _public function_ `FGameMenuStyle& SetMenuTitleColor(const GameMenuLayoutType::Type InLayoutType)`
- L137 _public member_ `FMargin TitleBorderMargin;` — `UPROPERTY(EditAnywhere, Category = Layout)` — Title border margin.
- L138 _public function_ `FGameMenuStyle& SetTitleBorderMargin(const FMargin InTitleBorderMargin)`
- L144 _public member_ `FMargin ItemBorderMargin;` — `UPROPERTY(EditAnywhere, Category = Layout)` — Item border margin.
- L145 _public function_ `FGameMenuStyle& SetItemBorderMargin(const FMargin InItemBorderMargin)`
- L151 _public member_ `TEnumAsByte<EHorizontalAlignment> TitleHorizontalAlignment;` — `UPROPERTY(EditAnywhere, Category = Layout)` — Title horizontal alignment.
- L152 _public function_ `FGameMenuStyle& SetTitleHorizontalAlignment(const EHorizontalAlignment InTitleHorizontalAlignment)`
- L158 _public member_ `TEnumAsByte<EVerticalAlignment> TitleVerticalAlignment;` — `UPROPERTY(EditAnywhere, Category = Layout)` — Title vertical alignment.
- L159 _public function_ `FGameMenuStyle& SetTitleVerticalAlignment(const EVerticalAlignment InTitleVerticalAlignment)`
- L165 _public member_ `TEnumAsByte<EVerticalAlignment> PanelsVerticalAlignment;` — `UPROPERTY(EditAnywhere, Category = Layout)` — Panel vertical alignment.
- L166 _public function_ `FGameMenuStyle& SetPanelsVerticalAlignment(const EVerticalAlignment InPanelsVerticalAlignment)`
- L172 _public member_ `float AnimationSpeed;` — `UPROPERTY(EditAnywhere, Category = Animation)` — Speed at which the menu initially appears.
- L173 _public function_ `FGameMenuStyle& SetMainAnimDuration(const float InAnimationSpeed)`
- L179 _public member_ `FSlateColor TextColor;` — `UPROPERTY(EditAnywhere, Category = Color)` — Color of the text.
- L180 _public function_ `FGameMenuStyle& SetTextColor(const FSlateColor InTextColor)`

#### class `UGameMenuWidgetStyle`  
`class UGameMenuWidgetStyle : public USlateWidgetStyleContainerBase`  
_L187-200_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `USlateWidgetStyleContainerBase`
- L194 _public member_ `FGameMenuStyle MenuStyle;` — `UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))` — The actual data describing the menu's appearance.
- L196 _public function_ `virtual const struct FSlateWidgetStyle* const GetStyle() const override`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace GameMenuLayoutType`

### `Source/Runtime/GameMenuBuilder/Public/SGameMenuItemWidget.h` (Public)


#### class `SGameMenuItemWidget`  
`class SGameMenuItemWidget : public SCompoundWidget`  
_L23-139_
- inherits: `SCompoundWidget`
- desc: Menu item widget
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnArrowPressed, int );`
- L28 _public function_ `SLATE_BEGIN_ARGS(SGameMenuItemWidget)`
- L32 _public prototype_ `SLATE_STYLE_ARGUMENT(FGameMenuStyle, MenuStyle) SLATE_ARGUMENT(TWeakObjectPtr<APlayerController>, PCOwner) SLATE_EVENT(FOnClicked, OnClicked) SLATE_EVENT(FOnArrowPressed, OnArrowPressed) SLATE_ATTRIBUTE(FText, Text) SLATE_ARGUMENT(bool, bIsMultichoice) SLATE_ATTRIBUTE(FText, OptionText) SLATE_ARGUMENT(TOptional<float>, InactiveTextAlpha) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — style to use for this menu item
- L62 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L64 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L66 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L68 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L72 _public prototype_ `void SetMenuItemActive(bool bIsMenuItemActive);` — Sets this menu item as active (selected)
- L75 _public member_ `EVisibility LeftArrowVisible;` — set in option item to enable left arrow
- L78 _public member_ `EVisibility RightArrowVisible;` — set in option item to enable right arrow
- L81 _public prototype_ `void SetMenuOwner(TWeakObjectPtr<class APlayerController> InPCOwner);` — Set pointer to our parent Player Controller.
- L84 _public prototype_ `void SetMenuStyle(const FGameMenuStyle* InMenuStyle);` — Set pointer to our style.
- L86 _public prototype_ `void SetClickedDelegate(FOnClicked InOnClicked);`
- L89 _public prototype_ `void SetArrowPressedDelegate(FOnArrowPressed InOnArrowPressed);` — Delegate to execute when one of arrows was pressed.
- L93 _protected member_ `FOnClicked OnClicked;` — Delegate to execute when the button is clicked.
- L96 _protected member_ `FOnArrowPressed OnArrowPressed;` — Delegate to execute when one of arrows was pressed.
- L99 _protected member_ `TAttribute< FText > Text;` — Menu item text attribute.
- L102 _protected member_ `TAttribute< FText > OptionText;` — Menu item option text attribute.
- L105 _protected member_ `float InactiveTextAlpha;` — Inactive text alpha value.
- L108 _protected member_ `bool bIsActiveMenuItem;` — Active item flag.
- L111 _protected member_ `bool bIsMultichoice;` — Does this menu item represent multi-choice field.
- L114 _protected member_ `TWeakObjectPtr<class APlayerController> PCOwner;` — Pointer to our parent Player Controller.
- L117 _protected member_ `const FGameMenuStyle* MenuStyle;` — The Style of the menu.
- L122 _private prototype_ `FSlateColor GetButtonBgColor() const;` — Getter for menu item background color.
- L125 _private prototype_ `FSlateColor GetButtonTextColor() const;` — Getter for menu item text color.
- L128 _private prototype_ `EVisibility GetLeftArrowVisibility() const;` — Getter for left option arrow visibility.
- L131 _private prototype_ `EVisibility GetRightArrowVisibility() const;` — Getter for right option arrow visibility.
- L134 _private prototype_ `FReply OnRightArrowDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Right arrrow pressed delegate.
- L137 _private prototype_ `FReply OnLeftArrowDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Left Arrow pressed handler.

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_OneParam( FOnArrowPressed, int );`

### `Source/Runtime/GameMenuBuilder/Public/SGameMenuPageWidget.h` (Public)


#### enum `EPanelState::Type`  
`enum Type`  
_L35-45_
- L38 _public enumerator_ `Opening` — Menu is opening.
- L40 _public enumerator_ `Open` — Menu is open.
- L42 _public enumerator_ `Closing` — Menu is closing.
- L44 _public enumerator_ `Closed` — Menu is closed.

#### class `FMenuPanel`  
`class FMenuPanel`  
_L52-85_
- desc: Simple class to contain the menu panels/animations
- L55 _public prototype_ `FMenuPanel();`
- L57 _public prototype_ `void Tick(float Delta);`
- L60 _public prototype_ `void ClosePanel(TSharedRef<SWidget> OwnerWidget);` — Close the panel
- L63 _public prototype_ `void OpenPanel(TSharedRef<SWidget> OwnerWidget);` — Open the panel
- L66 _public prototype_ `void ForcePanelOpen();` — Force the panel to be fully open.
- L69 _public prototype_ `void ForcePanelClosed();` — Force the panel to be fully closed.
- L71 _public prototype_ `void SetStyle(const FGameMenuStyle* InStyle);`
- L74 _public member_ `FPanelStateChanged OnStateChanged;` — Delegate called when the panel becomes open or closed.
- L77 _public member_ `FCurveHandle AnimationHandle;` — Animation curve/handle for panel animation.
- L80 _public member_ `EPanelState::Type CurrentState;` — The current state of the panel.
- L84 _private member_ `FCurveSequence AnimationSequence;` — Animation sequence used to open or close the panel.

#### class `SGameMenuPageWidget`  
`class SGameMenuPageWidget : public SCompoundWidget`  
_L90-391_
- inherits: `SCompoundWidget`
- desc: Simple Menu page widget class
- L93 _public function_ `SLATE_BEGIN_ARGS(SGameMenuPageWidget) : _PCOwner()`
- L97 _public prototype_ `SLATE_STYLE_ARGUMENT(FGameMenuStyle, MenuStyle) SLATE_ARGUMENT(TWeakObjectPtr<APlayerController>, PCOwner) SLATE_ARGUMENT(bool, GameMenu) SLATE_END_ARGS() DECLARE_DELEGATE(FOnToggleMenu); DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, TSharedPtr<class FGameMenuItem>, TSharedPtr<class FGameMenuItem>); void Construct(const FArguments& InArgs);` — style to use for this menu item.
- L113 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, TSharedPtr<class FGameMenuItem>, TSharedPtr<class FGameMenuItem>);` — Delegate for selection changing. Passes old and new selection.
- L116 _public prototype_ `void Construct(const FArguments& InArgs);` — every widget needs a construction function.
- L120 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — Update function.
- L123 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Mouse button down handler.
- L126 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Key down handler.
- L129 _public function_ `virtual bool SupportsKeyboardFocus() const override` — says that we can support keyboard focus.
- L132 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;` — The menu sets up the appropriate mouse settings upon focus.
- L142 _public prototype_ `virtual void OnMainPanelStateChange(bool bWasOpened);` — Callback handler for when the state of the main panel changes. @param bWasOpened	whether the panel was opened or closed. is TRUE if panel opened.
- L151 _public prototype_ `virtual void OnSubPanelStateChange(bool bWasOpened);` — Callback handler for when the state of the sub panel changes.b @param bWasOpened	whether the panel was opened or closed. is TRUE if panel opened.
- L154 _public prototype_ `void SetupAnimations();` — Setups misc animation sequences.
- L157 _public prototype_ `void EnterSubMenu(TSharedPtr<FGameMenuPage> InSubMenu);` — Make the currently selected menu sub menu new main menu if valid.
- L165 _public prototype_ `void MenuGoBack(bool bIsCancel=false);` — Go back the the previous menu. @param	bIsCancel	if true will be treated as CANCEL (IE escape pressed).
- L168 _public prototype_ `void ConfirmMenuItem();` — Confirms current menu item and performs an action. Will also play selection sound.
- L176 _public prototype_ `void BuildAndShowMenu(TSharedPtr< FGameMenuPage > InMenu);` — Show the given menu and make it the current menu. @param InMenu	The menu to show and set as the current menu. If this is NULL Current menu will be used if valid.
- L179 _public prototype_ `void HideMenu();` — Hide the menu.
- L187 _public prototype_ `void UpdateArrows(TSharedPtr<class FGameMenuItem> InMenuItem);` — Updates arrows visibility for multi-choice menu item. @param	InMenuItem The item to update.
- L195 _public prototype_ `void ChangeOption(int32 InMoveBy);` — Change the currently selection option of the currently selected menu item. @param	InMoveBy		Number to change the option by.
- L198 _public prototype_ `void LockControls(bool bEnable);` — disable/enable moving around menu.
- L206 _public prototype_ `void OpenMainPanel(TSharedPtr< FGameMenuPage > InMenu);` — Set the current menu and 'open' it as the main panel. @param InMenu	The menu to open and set as current.
- L214 _public prototype_ `bool SelectItem(int32 InSelection);` — Select a given item from an index @param InSelection	The index of the item to select @returns true if selection changed.
- L216 _public prototype_ `void ResetMenu();`
- L219 _public member_ `TWeakObjectPtr<UGameViewportClient> MyGameViewport;` — The viewport I am attached to.
- L221 _public prototype_ `TSharedPtr< FGameMenuPage > GetCurrentMenu();`
- L225 _protected prototype_ `void SetCurrentMenu(TSharedPtr< FGameMenuPage > InMenu);` — Set the current menu. Also sets the owner widget of that menu to this and resets the previous menu owner.
- L228 _protected prototype_ `EVisibility GetSlateVisibility() const;` — Sets hit test invisibility when console is up.
- L231 _protected prototype_ `EVisibility GetSubMenuVisiblity() const;` — Returns true if the submenu should be visible.
- L234 _protected prototype_ `float GetUIScale() const;` — Gets current scale for drawing menu.
- L245 _protected prototype_ `void BuildPanelButtons(TSharedPtr< FGameMenuPage > InPanel, TSharedPtr<SVerticalBox> InBox, int32 InPreviousIndex);` — Rebuild the widgets in the main menu widget. Selected item will be set from InPreviousIndex unless it is invalid. @param		InPanel		The FGameMenuPage we are building the panel from. @param		InBox		The SVerticalBox in which to build the widgets from the given panel. @param		PreviousIndex	The previous menu index. (Can be INDEX_NONE)
- L248 _protected prototype_ `FLinearColor GetPanelsColor() const;` — Misc Getters used for animating/fading various menu facets.
- L249 _protected prototype_ `FSlateColor GetPanelsBackgroundColor() const;`
- L250 _protected prototype_ `FMargin GetMainMenuOffset() const;`
- L251 _protected prototype_ `FMargin GetSubMenuOffset() const;`
- L252 _protected prototype_ `FMargin GetMenuTitleOffset() const;`
- L253 _protected prototype_ `FMargin GetMenuOffset() const;`
- L254 _protected prototype_ `FMargin GetMenuItemPadding() const;`
- L255 _protected prototype_ `FMargin GetSubMenuItemPadding() const;`
- L256 _protected prototype_ `FSlateColor GetTitleColor() const;`
- L257 _protected prototype_ `FSlateColor GetTextColor() const;`
- L265 _protected prototype_ `virtual FReply SelectionChanged(int32 SelectionIndex);` — Callback for when one of the menu items is selected. @param	SelectionIndex	The index selection. @returns	Will return UNHANDLED if the current menu is invalid, HANDLED in all other cases including if the controls are locked.
- L273 _protected prototype_ `virtual FReply MouseButtonClicked(int32 SelectionIndex);` — Callback for handling mouse click. @param	SelectionIndex	The index selection. @returns	Will return UNHANDLED if the current menu is invalid, HANDLED in all other cases including if the controls are locked.
- L281 _protected prototype_ `FText GetOptionText(TSharedPtr<class FGameMenuItem> MenuItem) const;` — Gets currently selected multi-choice option. @param	SelectionIndex	The index selection. @returns	Will return UNHANDLED if the current menu is invalid, HANDLED in all other cases including if the controls are locked.
- L284 _protected prototype_ `FText GetMenuTitle() const;` — Gets current menu title string.
- L287 _protected prototype_ `EVisibility GetMenuTitleVisibility() const;` — Gets the menu title visibility based on if the title text is empty.
- L290 _protected prototype_ `void FadeIn();` — Start the main menu open fade/anim and set keyboard focu.s
- L297 _protected prototype_ `void SetTitleAnimation(bool bShowTitle);` — Animates the title widget. @param	bShowTitle	true to show the title, false to hide it.
- L300 _protected prototype_ `void OpenPendingSubMenu();` — Opens any pending sub menu if there is one.
- L306 _protected member_ `FText CurrentMenuTitle;` — Current menu title if present.
- L309 _protected member_ `bool bConsoleVisible;` — If console is currently opened.
- L312 _protected member_ `FMenuPanel MainMenuPanel;` — Container instance for main panel.
- L315 _protected member_ `FMenuPanel SubMenuPanel;` — Container instance for sub menu panel (only relevant with side by side layout).
- L318 _protected member_ `TSharedPtr< FGameMenuPage > NextMenu;` — Next menu (for transition and displaying as the right menu).
- L321 _protected member_ `TSharedPtr< FGameMenuPage > CurrentMenu;` — Currently active menu.
- L324 _protected member_ `TAttribute<float> UIScale;` — Current UI scale attribute.
- L327 _protected member_ `FCurveSequence MenuWidgetAnimation;` — Our curve sequence and the related handles.
- L330 _protected member_ `FCurveHandle TopColorCurve;` — Used for main menu logo fade in animation at the beginning.
- L333 _protected member_ `FCurveHandle ColorFadeCurve;` — Used for menu background fade in animation at the beginning.
- L336 _protected member_ `FCurveHandle MenuAnimationCurve;` — Used for menu buttons slide in animation at the beginning.
- L339 _protected member_ `FCurveSequence TitleWidgetAnimation;` — Our curve sequence and the related handles.
- L342 _protected member_ `FCurveHandle TitleWidgetCurve;` — Used to animate the title widget (NYI)
- L345 _protected member_ `TWeakObjectPtr<class APlayerController> PCOwner;` — Weak pointer to our parent Player Controller.
- L348 _protected member_ `FIntPoint ScreenRes;` — Screen resolution.
- L351 _protected member_ `int32 MainAnimNumber;` — Animation type index.
- L354 _protected member_ `int32 SelectedIndex;` — Selected index of current menu.
- L357 _protected member_ `uint8 bMenuHiding : 1;` — Flag when playing hiding animation.
- L360 _protected member_ `uint8 bMenuHidden : 1;` — Flag when playing hiding animation.
- L363 _protected member_ `uint8 bGameMenu : 1;` — If this is in game menu.
- L366 _protected member_ `uint8 bControlsLocked : 1;` — If moving around menu is currently locked.
- L369 _protected member_ `TSharedPtr< FGameMenuPage > PendingMainMenu;` — Menu that will override current one after transition animation.
- L372 _protected member_ `TSharedPtr< FGameMenuPage > PendingSubMenu;` — Menu that will become the submenu after transition animation.
- L375 _protected member_ `TSharedPtr<SVerticalBox> MainPanel;` — Current menu layout box.
- L378 _protected member_ `TSharedPtr<SVerticalBox> SubPanel;` — Sub menu layout box.
- L381 _protected member_ `const FGameMenuStyle* MenuStyle;` — Style to use for this menu item.
- L384 _protected member_ `TArray< TSharedPtr< FGameMenuPage>> MenuHistory;` — Stack of previous menus.
- L387 _protected member_ `FOnToggleMenu OnToggleMenu;` — Bind if menu should be hidden from outside by controller button.
- L390 _protected member_ `FOnSelectionChanged OnSelectionChange;` — Executed when the user selects an item.

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace EPanelState`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FPanelStateChanged, bool);`
- L49 _prototype_ `DECLARE_DELEGATE_OneParam(FPanelStateChanged, bool);`
- L110 _delegate_ `DECLARE_DELEGATE(FOnToggleMenu);` — Delegate to call when in-game menu should be hidden using controller buttons - it's workaround as when joystick is captured, even when sending FReply::Unhandled, binding does not receive input :(
- L113 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, TSharedPtr<class FGameMenuItem>, TSharedPtr<class FGameMenuItem>);` — Delegate for selection changing. Passes old and new selection.
