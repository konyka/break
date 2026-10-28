# Runtime / FriendsAndChat

- module root: `Source/Runtime/FriendsAndChat`
- headers: 9; symbols: 356
- symbol kinds: class=2, delegate=1, function=30, member=175, namespace=1, prototype=140, struct=7
- PrivateDependencyModuleNames: SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Slate

### `Source/Runtime/FriendsAndChat/Public/FriendsAndChat.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/FriendsAndChat/Public/FriendsAndChatStyle.h` (Public)


#### struct `FFriendsAndChatStyle`  
`struct FFriendsAndChatStyle : public FSlateWidgetStyle`  
_L26-108_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Interface for the services manager.
- L32 _public function_ `FFriendsAndChatStyle()` — Default Constructor
- L35 _public function_ `virtual ~FFriendsAndChatStyle()` — Default Destructor
- L40 _public function_ `virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override` — Override widget style function.
- L43 _public member_ `static const FName TypeName;` — Holds the widget type name
- L49 _public function_ `virtual const FName GetTypeName() const override` — Get the type name. @return the type name
- L55 _public prototype_ `static const FFriendsAndChatStyle& GetDefault();` — Get the default style. @return the default style
- L60 _public member_ `FScrollBarStyle ScrollBarStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L61 _public prototype_ `FFriendsAndChatStyle& SetScrollbarStyle(const FScrollBarStyle& InScrollBarStyle);`
- L65 _public member_ `FButtonStyle ActionButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — SFriendActions Action Button style
- L66 _public prototype_ `FFriendsAndChatStyle& SetActionButtonStyle(const FButtonStyle& ButtonStyle);`
- L69 _public member_ `FFriendsFontStyle FriendsSmallFontStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L70 _public prototype_ `FFriendsAndChatStyle& SetSmallFriendsFontStyle(const FFriendsFontStyle& FontStyle);`
- L73 _public member_ `FFriendsFontStyle FriendsNormalFontStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L74 _public prototype_ `FFriendsAndChatStyle& SetNormalFriendsFontStyle(const FFriendsFontStyle& FontStyle);`
- L77 _public member_ `FFriendsFontStyle FriendsLargeFontStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L78 _public prototype_ `FFriendsAndChatStyle& SetLargeFriendsFontStyle(const FFriendsFontStyle& FontStyle);`
- L81 _public member_ `FFriendsFontStyle ChatFontStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L82 _public prototype_ `FFriendsAndChatStyle& SetChatFontStyle(const FFriendsFontStyle& FontStyle);`
- L85 _public member_ `FCheckBoxStyle CheckBoxStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L86 _public prototype_ `FFriendsAndChatStyle& SetCheckBoxStyle(const FCheckBoxStyle& InCheckBoxStyle);`
- L89 _public member_ `FCheckBoxStyle RadioBoxStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L90 _public prototype_ `FFriendsAndChatStyle& SetRadioBoxStyle(const FCheckBoxStyle& InRadioBoxStyle);`
- L94 _public member_ `FFriendsListStyle FriendsListStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L95 _public prototype_ `FFriendsAndChatStyle& SetFriendsListStyle(const FFriendsListStyle& InFriendsListStyle);`
- L98 _public member_ `FFriendsChatStyle FriendsChatStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L99 _public prototype_ `FFriendsAndChatStyle& SetFriendsChatStyle(const FFriendsChatStyle& InFriendsChatStyle);`
- L102 _public member_ `FFriendsChatChromeStyle FriendsChatChromeStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L103 _public prototype_ `FFriendsAndChatStyle& SetFriendsChatChromeStyle(const FFriendsChatChromeStyle& InFriendsChatChromeStyle);`
- L106 _public member_ `FFriendsMarkupStyle FriendsMarkupStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L107 _public prototype_ `FFriendsAndChatStyle& SetFriendsMarkupStyle(const FFriendsMarkupStyle& InFriendsMarkupStyle);`

#### class `FFriendsAndChatModuleStyle`  
`class FFriendsAndChatModuleStyle`  
_L111-134_
- desc: Manages the style which provides resources for the rich text widget.
- L115 _public prototype_ `static void Initialize(FFriendsAndChatStyle FriendStyle);`
- L117 _public prototype_ `static void Shutdown();`
- L120 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L123 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the Friends and chat module
- L125 _public prototype_ `static FName GetStyleSetName();`
- L129 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create(FFriendsAndChatStyle FriendStyle);`
- L133 _private member_ `static TSharedPtr< class FSlateStyleSet > FriendsAndChatModuleStyleInstance;`

### `Source/Runtime/FriendsAndChat/Public/FriendsChatChromeStyle.h` (Public)


#### struct `FFriendsChatChromeStyle`  
`struct FFriendsChatChromeStyle : public FSlateWidgetStyle`  
_L18-112_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Interface for the services manager.
- L24 _public function_ `FFriendsChatChromeStyle()` — Default Constructor
- L27 _public function_ `virtual ~FFriendsChatChromeStyle()` — Default Destructor
- L32 _public function_ `virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override` — Override widget style function.
- L35 _public member_ `static const FName TypeName;` — Holds the widget type name
- L41 _public function_ `virtual const FName GetTypeName() const override` — Get the type name. @return the type name
- L47 _public prototype_ `static const FFriendsChatChromeStyle& GetDefault();` — Get the default style. @return the default style
- L50 _public member_ `FSlateBrush ChatBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L51 _public prototype_ `FFriendsChatChromeStyle& SetChatBackgroundBrush(const FSlateBrush& InChatBackgroundBrush);`
- L54 _public member_ `FSlateBrush ChatEntryBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L55 _public prototype_ `FFriendsChatChromeStyle& SetChatEntryBackgroundBrush(const FSlateBrush& InChatBackgroundBrush);`
- L58 _public member_ `FSlateBrush ChannelBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L59 _public prototype_ `FFriendsChatChromeStyle& SetChannelBackgroundBrush(const FSlateBrush& Value);`
- L62 _public member_ `FLinearColor ChatEntryBackgroundColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L63 _public prototype_ `FFriendsChatChromeStyle& SetChatEntryBackgroundColor(const FLinearColor& Value);`
- L66 _public member_ `FSlateBrush TabBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L67 _public prototype_ `FFriendsChatChromeStyle& SetTabBackgroundBrush(const FSlateBrush& InTabBackgroundBrush);`
- L70 _public member_ `FLinearColor NoneActiveTabColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L71 _public prototype_ `FFriendsChatChromeStyle& SetNoneActiveTabColor(const FLinearColor& Value);`
- L74 _public member_ `FLinearColor TabFontColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L75 _public prototype_ `FFriendsChatChromeStyle& SetTabFontColor(const FLinearColor& Value);`
- L78 _public member_ `FLinearColor TabFontColorInverted;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L79 _public prototype_ `FFriendsChatChromeStyle& SetTabFontColorInverted(const FLinearColor& Value);`
- L82 _public member_ `float TabWidth;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L83 _public prototype_ `FFriendsChatChromeStyle& SetTabWidth(float Value);`
- L86 _public member_ `FMargin TabPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L87 _public prototype_ `FFriendsChatChromeStyle& SetTabPadding(const FMargin& Value);`
- L90 _public member_ `FMargin ChatWindowPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L91 _public prototype_ `FFriendsChatChromeStyle& SetChatWindowPadding(const FMargin& Value);`
- L94 _public member_ `FMargin ChatWindowToEntryMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L95 _public prototype_ `FFriendsChatChromeStyle& SetChatWindowToEntryMargin(const FMargin& Value);`
- L98 _public member_ `FMargin ChatChannelPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L99 _public prototype_ `FFriendsChatChromeStyle& SetChatChannelPadding(const FMargin& Value);`
- L102 _public member_ `FMargin ChatEntryPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L103 _public prototype_ `FFriendsChatChromeStyle& SetChatEntryPadding(const FMargin& Value);`
- L106 _public member_ `FLinearColor ChatBackgroundColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L107 _public prototype_ `FFriendsChatChromeStyle& SetChatBackgroundColor(const FLinearColor& Value);`
- L110 _public member_ `FSlateBrush ChatMenuBackgroundBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L111 _public prototype_ `FFriendsChatChromeStyle& SetChatMenuBackgroundBrush(const FSlateBrush& InChatMenuBackgroundBrush);`

### `Source/Runtime/FriendsAndChat/Public/FriendsChatStyle.h` (Public)


#### struct `FFriendsChatStyle`  
`struct FFriendsChatStyle : public FSlateWidgetStyle`  
_L25-191_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Interface for the services manager.
- L31 _public function_ `FFriendsChatStyle() : TimeStampOpacity(0.5f) , ChatEntryPadding(0) , ChatEntryHeight(55) , FriendActionPadding(20, 15) , FriendActionHeaderPadding(20) , FriendActionStatusMargin(20, 0, 0, 0)` — Default Constructor
- L43 _public function_ `virtual ~FFriendsChatStyle()` — Default Destructor
- L48 _public function_ `virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override` — Override widget style function.
- L51 _public member_ `static const FName TypeName;` — Holds the widget type name
- L57 _public function_ `virtual const FName GetTypeName() const override` — Get the type name. @return the type name
- L63 _public prototype_ `static const FFriendsChatStyle& GetDefault();` — Get the default style. @return the default style
- L67 _public member_ `FTextBlockStyle TextStyle;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Text Style
- L68 _public prototype_ `FFriendsChatStyle& SetTextStyle(const FTextBlockStyle& InTextStyle);`
- L72 _public member_ `FTextBlockStyle TimeStampTextStyle;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Time Stamp Text Style
- L73 _public prototype_ `FFriendsChatStyle& SetTimeStampTextStyle(const FTextBlockStyle& InTextStyle);`
- L76 _public member_ `float TimeStampOpacity;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L77 _public prototype_ `FFriendsChatStyle& SetTimestampOpacity(float InOpacity);`
- L80 _public member_ `FLinearColor DefaultChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L81 _public prototype_ `FFriendsChatStyle& SetDefaultChatColor(const FLinearColor& InFontColor);`
- L84 _public member_ `FLinearColor WhisperChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L85 _public prototype_ `FFriendsChatStyle& SetWhisplerChatColor(const FLinearColor& InFontColor);`
- L88 _public member_ `FLinearColor GlobalChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L89 _public prototype_ `FFriendsChatStyle& SetGlobalChatColor(const FLinearColor& InFontColor);`
- L92 _public member_ `FLinearColor FounderChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L93 _public prototype_ `FFriendsChatStyle& SetFounderChatColor(const FLinearColor& InFontColor);`
- L96 _public member_ `FLinearColor GameChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L97 _public prototype_ `FFriendsChatStyle& SetGameChatColor(const FLinearColor& InFontColor);`
- L100 _public member_ `FLinearColor TeamChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L101 _public prototype_ `FFriendsChatStyle& SetTeamChatColor(const FLinearColor& InFontColor);`
- L104 _public member_ `FLinearColor PartyChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L105 _public prototype_ `FFriendsChatStyle& SetPartyChatColor(const FLinearColor& InFontColor);`
- L108 _public member_ `FLinearColor AdminChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L109 _public prototype_ `FFriendsChatStyle& SetAdminChatColor(const FLinearColor& InFontColor);`
- L112 _public member_ `FLinearColor GameAdminChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L113 _public prototype_ `FFriendsChatStyle& SetGameAdminChatColor(const FLinearColor& InFontColor);`
- L116 _public member_ `FLinearColor AddedItemChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L117 _public prototype_ `FFriendsChatStyle& SetAddedItemChatColor(const FLinearColor& InFontColor);`
- L120 _public member_ `FLinearColor CompletedItemChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L121 _public prototype_ `FFriendsChatStyle& SetCompletedItemChatColor(const FLinearColor& InFontColor);`
- L124 _public member_ `FLinearColor DiscardedItemChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L125 _public prototype_ `FFriendsChatStyle& SetDiscardedItemChatColor(const FLinearColor& InFontColor);`
- L128 _public member_ `FLinearColor WhisperHyperlinkChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L129 _public prototype_ `FFriendsChatStyle& SetWhisplerHyperlinkChatColor(const FLinearColor& InFontColor);`
- L132 _public member_ `FLinearColor GlobalHyperlinkChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L133 _public prototype_ `FFriendsChatStyle& SetGlobalHyperlinkChatColor(const FLinearColor& InFontColor);`
- L136 _public member_ `FLinearColor FounderHyperlinkChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L137 _public prototype_ `FFriendsChatStyle& SetFounderHyperlinkChatColor(const FLinearColor& InFontColor);`
- L140 _public member_ `FLinearColor GameHyperlinkChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L141 _public prototype_ `FFriendsChatStyle& SetGameHyperlinkChatColor(const FLinearColor& InFontColor);`
- L144 _public member_ `FLinearColor TeamHyperlinkChatColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L145 _public prototype_ `FFriendsChatStyle& SetTeamHyperlinkChatColor(const FLinearColor& InFontColor);`
- L148 _public member_ `FLinearColor PartyHyperlinkChatColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L149 _public prototype_ `FFriendsChatStyle& SetPartyHyperlinkChatColor(const FLinearColor& InFontColor);`
- L152 _public member_ `FLinearColor EnemyColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L153 _public prototype_ `FFriendsChatStyle& SetEnemyColor(const FLinearColor& InFontColor);`
- L156 _public member_ `FLinearColor FriendlyColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L157 _public prototype_ `FFriendsChatStyle& SetFriendlyColor(const FLinearColor& InFontColor);`
- L160 _public member_ `FEditableTextBoxStyle ChatEntryTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L161 _public prototype_ `FFriendsChatStyle& SetChatEntryTextStyle(const FEditableTextBoxStyle& InEditableTextStyle);`
- L164 _public member_ `FEditableTextBoxStyle ChatDisplayTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L165 _public prototype_ `FFriendsChatStyle& SetChatDisplayTextStyle(const FEditableTextBoxStyle& InEditableTextStyle);`
- L168 _public member_ `FScrollBoxStyle ScrollBorderStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L169 _public prototype_ `FFriendsChatStyle& SetScrollBorderStyle(const FScrollBoxStyle& InScrollBorderStyle);`
- L172 _public member_ `FSlateBrush MessageNotificationBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L173 _public prototype_ `FFriendsChatStyle& SetMessageNotificationBrush(const FSlateBrush& Brush);`
- L176 _public member_ `FMargin ChatEntryPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L177 _public prototype_ `FFriendsChatStyle& SetChatChannelPadding(const FMargin& Value);`
- L180 _public member_ `float ChatEntryHeight;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L181 _public prototype_ `FFriendsChatStyle& SetChatEntryHeight(float Value);`
- L184 _public member_ `FMargin FriendActionPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L187 _public member_ `FMargin FriendActionHeaderPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L190 _public member_ `FMargin FriendActionStatusMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EChatMessageType`

### `Source/Runtime/FriendsAndChat/Public/FriendsComboStyle.h` (Public)


#### struct `FFriendsComboStyle`  
`struct FFriendsComboStyle : public FSlateWidgetStyle`  
_L20-123_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Interface for the services manager.
- L26 _public function_ `FFriendsComboStyle()` — Default Constructor
- L29 _public function_ `virtual ~FFriendsComboStyle()` — Default Destructor
- L34 _public function_ `virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override` — Override widget style function.
- L37 _public member_ `static const FName TypeName;` — Holds the widget type name
- L43 _public function_ `virtual const FName GetTypeName() const override` — Get the type name. @return the type name
- L49 _public prototype_ `static const FFriendsComboStyle& GetDefault();` — Get the default style. @return the default style
- L52 _public member_ `FButtonStyle ComboItemButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L53 _public prototype_ `FFriendsComboStyle& SetComboItemButtonStyle(const FButtonStyle& ButtonStyle);`
- L56 _public member_ `FLinearColor ComboItemTextColorNormal;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L57 _public prototype_ `FFriendsComboStyle& SetComboItemTextColorNormal(const FLinearColor& InColor);`
- L60 _public member_ `FLinearColor ComboItemTextColorInverted;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L61 _public prototype_ `FFriendsComboStyle& SetComboItemTextColorInverted(const FLinearColor& InColor);`
- L64 _public member_ `FTextBlockStyle ComboItemTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L65 _public prototype_ `FFriendsComboStyle& SetComboItemTextStyle(const FTextBlockStyle& InTextStyle);`
- L68 _public member_ `FTextBlockStyle FriendsComboTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L69 _public prototype_ `FFriendsComboStyle& SetFriendsComboTextStyle(const FTextBlockStyle& InTextStyle);`
- L72 _public member_ `FVector2D StatusButtonSize;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L73 _public prototype_ `FFriendsComboStyle& SetStatusButtonSize(const FVector2D& InStatusButtonSize);`
- L76 _public member_ `FVector2D ActionComboButtonSize;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L77 _public prototype_ `FFriendsComboStyle& SetActionComboButtonSize(const FVector2D& InActionComboButtonSize);`
- L80 _public member_ `FComboButtonStyle ActionComboButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L81 _public prototype_ `FFriendsComboStyle& SetActionComboButtonStyle(const FComboButtonStyle& ButtonStyle);`
- L84 _public member_ `FTextBlockStyle ActionComboButtonTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L85 _public prototype_ `FFriendsComboStyle& SetActionComboButtonTextStyle(const FTextBlockStyle& TextStyle);`
- L88 _public member_ `FMargin ComboMenuPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L89 _public prototype_ `FFriendsComboStyle& SetComboMenuPadding(const FMargin& InPadding);`
- L92 _public member_ `FMargin ComboItemPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L93 _public prototype_ `FFriendsComboStyle& SetComboItemPadding(const FMargin& InPadding);`
- L96 _public member_ `FMargin ComboItemContentPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L97 _public prototype_ `FFriendsComboStyle& SetComboItemContentPadding(const FMargin& InPadding);`
- L101 _public member_ `FSlateBrush FriendComboBackgroundLeftBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Combo Button menu background image (left)
- L102 _public prototype_ `FFriendsComboStyle& SetFriendComboBackgroundLeftBrush(const FSlateBrush& BrushStyle);`
- L106 _public member_ `FSlateBrush FriendComboBackgroundRightBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Combo Button menu background image (right)
- L107 _public prototype_ `FFriendsComboStyle& SetFriendComboBackgroundRightBrush(const FSlateBrush& BrushStyle);`
- L111 _public member_ `FSlateBrush FriendComboBackgroundLeftFlippedBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Combo Button menu background image (left-flipped) - for MenuPlacement_ComboBoxRight menus
- L112 _public prototype_ `FFriendsComboStyle& SetFriendComboBackgroundLeftFlippedBrush(const FSlateBrush& BrushStyle);`
- L116 _public member_ `FSlateBrush FriendComboBackgroundRightFlippedBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Combo Button menu background image (right-flipped) - for MenuPlacement_ComboBoxRight menus
- L117 _public prototype_ `FFriendsComboStyle& SetFriendComboBackgroundRightFlippedBrush(const FSlateBrush& BrushStyle);`
- L121 _public member_ `FComboButtonStyle FriendListComboButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Combo Button style
- L122 _public prototype_ `FFriendsComboStyle& SetFriendsListComboButtonStyle(const FComboButtonStyle& ButtonStyle);`

### `Source/Runtime/FriendsAndChat/Public/FriendsFontStyle.h` (Public)


#### struct `FFriendsFontStyle`  
`struct FFriendsFontStyle : public FSlateWidgetStyle`  
_L21-99_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Interface for the services manager.
- L27 _public function_ `FFriendsFontStyle()` — Default Constructor
- L30 _public function_ `virtual ~FFriendsFontStyle()` — Default Destructor
- L35 _public function_ `virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override` — Override widget style function.
- L38 _public member_ `static const FName TypeName;` — Holds the widget type name
- L44 _public function_ `virtual const FName GetTypeName() const override` — Get the type name. @return the type name
- L50 _public prototype_ `static const FFriendsFontStyle& GetDefault();` — Get the default style. @return the default style
- L54 _public member_ `FSlateFontInfo FriendsFontSmall;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Font Style
- L55 _public prototype_ `FFriendsFontStyle& SetFontSmall(const FSlateFontInfo& InFontStyle);`
- L59 _public member_ `FSlateFontInfo FriendsFontSmallBold;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Font Style
- L60 _public prototype_ `FFriendsFontStyle& SetFontSmallBold(const FSlateFontInfo& InFontStyle);`
- L64 _public member_ `FSlateFontInfo FriendsFontNormal;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Font Style
- L65 _public prototype_ `FFriendsFontStyle& SetFontNormal(const FSlateFontInfo& InFontStyle);`
- L69 _public member_ `FSlateFontInfo FriendsFontNormalBold;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Font Style
- L70 _public prototype_ `FFriendsFontStyle& SetFontNormalBold(const FSlateFontInfo& InFontStyle);`
- L74 _public member_ `FSlateFontInfo FriendsFontLarge;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Font Style
- L75 _public prototype_ `FFriendsFontStyle& SetFontLarge(const FSlateFontInfo& InFontStyle);`
- L79 _public member_ `FSlateFontInfo FriendsFontLargeBold;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Font Style
- L80 _public prototype_ `FFriendsFontStyle& SetFontLargeBold(const FSlateFontInfo& InFontStyle);`
- L84 _public member_ `FSlateFontInfo FriendsChatFont;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Font Style
- L85 _public prototype_ `FFriendsFontStyle& SetChatFont(const FSlateFontInfo& InFontStyle);`
- L89 _public member_ `FLinearColor DefaultFontColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Default Font Color
- L90 _public prototype_ `FFriendsFontStyle& SetDefaultFontColor(const FLinearColor& InFontColor);`
- L93 _public member_ `FLinearColor InvertedFontColor;` — `UPROPERTY(EditAnywhere, Category=Appearance)`
- L94 _public prototype_ `FFriendsFontStyle& SetInvertedFontColor(const FLinearColor& InFontColor);`
- L97 _public member_ `FLinearColor DefaultDullFontColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L98 _public prototype_ `FFriendsFontStyle& SetDefaultDullFontColor(const FLinearColor& InFontColor);`

### `Source/Runtime/FriendsAndChat/Public/FriendsListStyle.h` (Public)


#### struct `FFriendsListStyle`  
`struct FFriendsListStyle : public FSlateWidgetStyle`  
_L20-347_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Interface for the services manager.
- L26 _public function_ `FFriendsListStyle() : BackButtonMargin(0.0, 0.0, 0.0, 1.0) , HeaderButtonMargin(0.0, 0.0, 1.0, 0.0) , FriendsListMargin(0.0, 1.0, 0.0, 0.0) , BackButtonContentMargin(15.0, 13.0, 0.0, 13.0) , FriendsListNoFriendsMargin(15.0, 10.0, 15.0, 0.0) , FriendsListHeaderMargin(45.0, 20.0, 0.0, 20.0) , FriendsListHeaderCountMargin(5.0, 20.0, 0.0, 20.0) , HeaderButtonContentMargin(0.0, 13.0) , FriendItemMargin(0.0, 17.0) , FriendItemStatusMargin(15.0, 0.0) , FriendItemPresenceMargin(27.0, 0.0, 35.0, 0.0) , FriendItemPlatformMargin(0, 0, 5, 0) , FriendItemTextScrollerMargin(5, 0, 0, 0) , ConfirmationBorderMargin(0.0, 0.0, 5.0, 0.0) , ConfirmationButtonMargin(5.0, 0.0, 0.0, 0.0) , ConfirmationButtonContentMargin(5.0, 20.0) , NoneFriendContentMargin(0) , NoneFriendContentHeight(75.f) , NoneFriendIconWidth(40.f) , SubMenuBackIconMargin(0.0, 0.0, 20.0, 0.0) , SubMenuPageIconMargin(20.0, 0.0) , RadioSettingTitleMargin(45.0, 10.0) , SubMenuSearchIconMargin(20.0, 50.0) , SubMenuSearchTextMargin(0.0, 0.0, 0.0, 0.0) , SubMenuBackButtonMargin(20.0) , SubMenuSettingButtonMargin(37.0, 20.0, 45.0, 20.0) , SubMenuListMargin(0.0, 5.0) , SubMenuSeperatorThickness(2.f) , PresenceSeperatorThickness(1.f) , FriendTipMargin(0, 10, 15, 10) , FriendTipSeperatorMargin(0, 10) , ToolTipMargin(10.0) , TipStatusMargin(0.0, 0.0, 15.0, 0.0) , AddButtonMargin(50, 12) , AddButtonSpacing(12.f, 25.f)` — Default Constructor
- L65 _public function_ `virtual ~FFriendsListStyle()` — Default Destructor
- L70 _public function_ `virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override` — Override widget style function.
- L73 _public member_ `static const FName TypeName;` — Holds the widget type name
- L79 _public function_ `virtual const FName GetTypeName() const override` — Get the type name. @return the type name
- L85 _public prototype_ `static const FFriendsListStyle& GetDefault();` — Get the default style. @return the default style
- L89 _public member_ `FButtonStyle GlobalChatButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Style
- L90 _public prototype_ `FFriendsListStyle& SetGlobalChatButtonStyle(const FButtonStyle& ButtonStyle);`
- L93 _public member_ `FSlateBrush GlobalChatIcon;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L94 _public prototype_ `FFriendsListStyle& SetGlobalChatIcon(const FSlateBrush& BrushStyle);`
- L98 _public member_ `FButtonStyle FriendItemButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Open Button style
- L99 _public prototype_ `FFriendsListStyle& SetFriendItemButtonStyle(const FButtonStyle& ButtonStyle);`
- L102 _public member_ `FButtonStyle ConfirmButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L103 _public prototype_ `FFriendsListStyle& SetConfirmButtonStyle(const FButtonStyle& ButtonStyle);`
- L106 _public member_ `FButtonStyle CancelButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L107 _public prototype_ `FFriendsListStyle& SetCancelButtonStyle(const FButtonStyle& ButtonStyle);`
- L110 _public member_ `FSlateColor ButtonContentColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L111 _public prototype_ `FFriendsListStyle& SetButtonContentColor(const FSlateColor& InColor);`
- L114 _public member_ `FSlateColor ButtonHoverContentColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L115 _public prototype_ `FFriendsListStyle& SetButtonHoverContentColor(const FSlateColor& InColor);`
- L119 _public member_ `FSlateBrush ActionMenuArrowBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Optional content for the Add Friend button
- L120 _public prototype_ `FFriendsListStyle& SetActionMenuArrowBrush(const FSlateBrush& BrushStyle);`
- L123 _public member_ `FSlateBrush ToolTipArrowBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L124 _public prototype_ `FFriendsListStyle& SetToolTipArrowBrush(const FSlateBrush& BrushStyle);`
- L127 _public member_ `FButtonStyle BackButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L128 _public prototype_ `FFriendsListStyle& SetBackButtonStyle(const FButtonStyle& ButtonStyle);`
- L131 _public member_ `FButtonStyle HeaderButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L132 _public prototype_ `FFriendsListStyle& SetHeaderButtonStyle(const FButtonStyle& ButtonStyle);`
- L136 _public member_ `FButtonStyle FriendListActionButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends List Action Button style
- L137 _public prototype_ `FFriendsListStyle& SetFriendListActionButtonStyle(const FButtonStyle& ButtonStyle);`
- L141 _public member_ `FSlateBrush AddFriendButtonContentBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Optional content for the Add Friend button
- L142 _public prototype_ `FFriendsListStyle& SetAddFriendButtonContentBrush(const FSlateBrush& BrushStyle);`
- L146 _public member_ `FSlateBrush StatusIconBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friend Image brush style
- L147 _public prototype_ `FFriendsListStyle& SetStatusIconBrush(const FSlateBrush& BrushStyle);`
- L150 _public member_ `FSlateBrush PCIconBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L151 _public prototype_ `FFriendsListStyle& SetPCIconBrush(const FSlateBrush& BrushStyle);`
- L154 _public member_ `FSlateBrush ConsoleIconBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L155 _public prototype_ `FFriendsListStyle& SetConsoleIconBrush(const FSlateBrush& BrushStyle);`
- L158 _public member_ `FSlateBrush EpicIconBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L159 _public prototype_ `FFriendsListStyle& SetEpicIconBrush(const FSlateBrush& BrushStyle);`
- L163 _public member_ `FSlateBrush FriendImageBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friend Image brush style
- L164 _public prototype_ `FFriendsListStyle& SetFriendImageBrush(const FSlateBrush& BrushStyle);`
- L168 _public member_ `FSlateBrush OfflineBrush;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Offline brush style
- L169 _public prototype_ `FFriendsListStyle& SetOfflineBrush(const FSlateBrush& InOffLine);`
- L173 _public member_ `FSlateBrush OnlineBrush;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Online brush style
- L174 _public prototype_ `FFriendsListStyle& SetOnlineBrush(const FSlateBrush& InOnLine);`
- L178 _public member_ `FSlateBrush AwayBrush;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Away brush style
- L179 _public prototype_ `FFriendsListStyle& SetAwayBrush(const FSlateBrush& AwayBrush);`
- L183 _public member_ `FSlateBrush SpectateBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Away brush style
- L184 _public prototype_ `FFriendsListStyle& SetSpectateBrush(const FSlateBrush& SpectateBrush);`
- L188 _public member_ `FSlateBrush FriendsContainerBackground;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends window background
- L189 _public prototype_ `FFriendsListStyle& SetFriendContainerBackground(const FSlateBrush& InFriendContainerBackground);`
- L193 _public member_ `FSlateBrush FriendsListBackground;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Friends window background
- L194 _public prototype_ `FFriendsListStyle& SetFriendsListBackground(const FSlateBrush& InBrush);`
- L197 _public member_ `FEditableTextBoxStyle AddFriendEditableTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L198 _public prototype_ `FFriendsListStyle& SetAddFriendEditableTextStyle(const FEditableTextBoxStyle& InEditableTextStyle);`
- L201 _public member_ `FVector2D UserPresenceImageSize;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L202 _public prototype_ `FFriendsListStyle& SetUserPresenceImageSize(const FVector2D& InUserPresenceImageSize);`
- L205 _public member_ `FSlateBrush BackBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L206 _public prototype_ `FFriendsListStyle& SetBackBrush(const FSlateBrush& Brush);`
- L209 _public member_ `FSlateBrush SelectedOptionBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L210 _public prototype_ `FFriendsListStyle& SetSelectedOptionBrush(const FSlateBrush& Brush);`
- L213 _public member_ `FSlateBrush SettingsBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L214 _public prototype_ `FFriendsListStyle& SetSettingsBrush(const FSlateBrush& Brush);`
- L217 _public member_ `FSlateBrush SeperatorBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L218 _public prototype_ `FFriendsListStyle& SetSeperatorBrush(const FSlateBrush& Brush);`
- L221 _public member_ `FSlateBrush PresenceSeperatorBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L222 _public prototype_ `FFriendsListStyle& SetPresenceSeperatorBrush(const FSlateBrush& Brush);`
- L225 _public member_ `FSlateBrush FontSizeBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L226 _public prototype_ `FFriendsListStyle& SetFontSizeBrush(const FSlateBrush& Brush);`
- L229 _public member_ `FSlateBrush SearchBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L230 _public prototype_ `FFriendsListStyle& SetSearchBrush(const FSlateBrush& Brush);`
- L233 _public member_ `FMargin BackButtonMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L236 _public member_ `FMargin HeaderButtonMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L239 _public member_ `FMargin FriendsListMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L242 _public member_ `FMargin BackButtonContentMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L245 _public member_ `FMargin FriendsListNoFriendsMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L248 _public member_ `FMargin FriendsListHeaderMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L251 _public member_ `FMargin FriendsListHeaderCountMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L254 _public member_ `FMargin HeaderButtonContentMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L257 _public member_ `FMargin FriendItemMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L260 _public member_ `FMargin FriendItemStatusMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L263 _public member_ `FMargin FriendItemPresenceMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L266 _public member_ `FMargin FriendItemPlatformMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L269 _public member_ `FMargin FriendItemTextScrollerMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L272 _public member_ `FMargin ConfirmationBorderMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L275 _public member_ `FMargin ConfirmationButtonMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L278 _public member_ `FMargin ConfirmationButtonContentMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L281 _public member_ `FMargin NoneFriendContentMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L284 _public member_ `float NoneFriendContentHeight;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L287 _public member_ `float NoneFriendIconWidth;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L290 _public member_ `FMargin SubMenuBackIconMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L293 _public member_ `FMargin SubMenuPageIconMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L296 _public member_ `FMargin RadioSettingTitleMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L299 _public member_ `FMargin SubMenuSearchIconMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L302 _public member_ `FMargin SubMenuSearchTextMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L305 _public member_ `FMargin SubMenuBackButtonMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L308 _public member_ `FMargin SubMenuSettingButtonMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L311 _public member_ `FMargin SubMenuListMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L314 _public member_ `float SubMenuSeperatorThickness;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L317 _public member_ `float PresenceSeperatorThickness;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L320 _public member_ `FMargin FriendTipMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L323 _public member_ `FMargin FriendTipSeperatorMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L326 _public member_ `FMargin ToolTipMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L329 _public member_ `FMargin TipStatusMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L332 _public member_ `FMargin AddButtonMargin;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L335 _public member_ `FVector2D AddButtonSpacing;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L341 _public member_ `FSlateBrush ClanDetailsBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L342 _public prototype_ `FFriendsListStyle& SetClanDetailsBrush(const FSlateBrush& Brush);`
- L345 _public member_ `FSlateBrush ClanMembersBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L346 _public prototype_ `FFriendsListStyle& SetClanMembersBrush(const FSlateBrush& Brush);`

### `Source/Runtime/FriendsAndChat/Public/FriendsMarkupStyle.h` (Public)


#### struct `FFriendsMarkupStyle`  
`struct FFriendsMarkupStyle : public FSlateWidgetStyle`  
_L19-92_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Interface for the services manager.
- L25 _public function_ `FFriendsMarkupStyle() : SeperatorThickness(2.0) , MarkupPadding(0, 7) , ButtonPadding(30, 7)` — Default Constructor
- L32 _public function_ `virtual ~FFriendsMarkupStyle()` — Default Destructor
- L37 _public function_ `virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override` — Override widget style function.
- L40 _public member_ `static const FName TypeName;` — Holds the widget type name
- L46 _public function_ `virtual const FName GetTypeName() const override` — Get the type name. @return the type name
- L52 _public prototype_ `static const FFriendsMarkupStyle& GetDefault();` — Get the default style. @return the default style
- L56 _public member_ `FButtonStyle MarkupButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Markup Button style
- L57 _public prototype_ `FFriendsMarkupStyle& SetMarkupButtonStyle(const FButtonStyle& ButtonStyle);`
- L60 _public member_ `FTextBlockStyle MarkupTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L61 _public prototype_ `FFriendsMarkupStyle& SetMarkupTextStyle(const FTextBlockStyle& InTextStyle);`
- L64 _public member_ `FSlateBrush MarkupBackground;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L65 _public prototype_ `FFriendsMarkupStyle& SetMarkupBackgroundBrush(const FSlateBrush& InChatBackgroundBrush);`
- L68 _public member_ `FSlateColor ButtonColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L69 _public prototype_ `FFriendsMarkupStyle& SetButtonColor(const FSlateColor& InColor);`
- L72 _public member_ `FSlateColor ButtonHoverColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L73 _public prototype_ `FFriendsMarkupStyle& SetButtonHoverColor(const FSlateColor& InColor);`
- L76 _public member_ `FSlateColor TipColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L77 _public prototype_ `FFriendsMarkupStyle& SetTipColor(const FSlateColor& InColor);`
- L80 _public member_ `FSlateBrush SeperatorBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L81 _public prototype_ `FFriendsMarkupStyle& SetSeperatorBrush(const FSlateBrush& Brush);`
- L84 _public member_ `float SeperatorThickness;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L87 _public member_ `FMargin MarkupPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L90 _public member_ `FMargin ButtonPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)`

### `Source/Runtime/FriendsAndChat/Public/Interfaces/IFriendsAndChatModule.h` (Public)


#### class `IFriendsAndChatModule`  
`class IFriendsAndChatModule : public IModuleInterface`  
_L14-36_
- inherits: `IModuleInterface`
- desc: Interface for the Friends and chat manager.
- L25 _public function_ `static inline IFriendsAndChatModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L30 _public prototype_ `virtual void ShutdownStyle() = 0;`
- L35 _public function_ `virtual ~IFriendsAndChatModule()` — Virtual destructor.

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FFriendsSystemReady ) class IFriendsAndChatModule : public IModuleInterface { public: static inline IFriendsAndChatModule& Get() { return FModuleManager::LoadModuleChecked<IFriendsAndChatModule>("FriendsAndChat"); } virtual void ShutdownStyle() = 0; public: virtual ~IFriendsAndChatModule() { } };`
