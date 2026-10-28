# Editor / EditorStyle

- module root: `Source/Editor/EditorStyle`
- headers: 5; symbols: 220
- symbol kinds: class=5, function=21, macro=2, member=141, prototype=51
- PrivateDependencyModuleNames: DesktopPlatform, EditorFramework, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: PropertyEditor, Settings
- PublicDependencyModuleNames: Core, CoreUObject, Slate

### `Source/Editor/EditorStyle/Private/StarshipStyle.h` (Private)


#### class `FStarshipEditorStyle`  
`class FStarshipEditorStyle : public FEditorStyle`  
_L25-160_
- inherits: `FEditorStyle`
- desc: Declares the Editor's visual style.
- L30 _public prototype_ `static void Initialize();`
- L31 _public prototype_ `static void Shutdown();`
- L33 _public function_ `static void SyncCustomizations()`
- L38 _public prototype_ `static const FName& GetStyleSetName();`
- L150 _public function_ `static TSharedRef<class FStarshipEditorStyle::FStyle> Create()`
- L158 _public member_ `static TSharedPtr<FStarshipEditorStyle::FStyle> StyleInstance;`
- L159 _public member_ `static FName StyleSetName;`

#### class `FStarshipEditorStyle::FStyle`  
`class FStyle : public FSlateStyleSet`  
_L40-148_
- inherits: `FSlateStyleSet`
- L43 _public prototype_ `FStyle();`
- L44 _public prototype_ `~FStyle();`
- L46 _public prototype_ `void Initialize();`
- L47 _public prototype_ `void SetupGeneralStyles();`
- L48 _public prototype_ `void SetupLevelGeneralStyles();`
- L49 _public prototype_ `void SetupWorldBrowserStyles();`
- L50 _public prototype_ `void SetupWorldPartitionStyles();`
- L51 _public prototype_ `void SetupSequencerStyles();`
- L52 _public prototype_ `void SetupViewportStyles();`
- L53 _public prototype_ `void SetupNewViewportToolbarStyles();`
- L54 _public prototype_ `void SetupOldViewportToolbarStyles();`
- L55 _public prototype_ `void SetupLegacyViewportToolbarStyles();`
- L56 _public prototype_ `void SetupDepthBarStyles();`
- L57 _public prototype_ `void SetupMenuBarStyles();`
- L58 _public prototype_ `void SetupGeneralIcons();`
- L59 _public prototype_ `void SetupWindowStyles();`
- L60 _public prototype_ `void SetupProjectBadgeStyle();`
- L61 _public prototype_ `void SetupDockingStyles();`
- L62 _public prototype_ `void SetupTutorialStyles();`
- L63 _public prototype_ `void SetupTranslationEditorStyles();`
- L64 _public prototype_ `void SetupLocalizationDashboardStyles();`
- L65 _public prototype_ `void SetupPropertyEditorStyles();`
- L66 _public prototype_ `void SetupProfilerStyle();`
- L67 _public prototype_ `void SetupGraphEditorStyles();`
- L68 _public prototype_ `void SetupLevelEditorStyle();`
- L69 _public prototype_ `void SetupPersonaStyle();`
- L70 _public prototype_ `void SetupClassThumbnailOverlays();`
- L71 _public prototype_ `void SetupClassIconsAndThumbnails();`
- L72 _public prototype_ `void SetupContentBrowserStyle();`
- L73 _public prototype_ `void SetupLandscapeEditorStyle();`
- L74 _public prototype_ `void SetupToolkitStyles();`
- L75 _public prototype_ `void SetupUnsavedAssetsStyles();`
- L76 _public prototype_ `void SetupSourceControlStyles();`
- L77 _public prototype_ `void SetupAutomationStyles();`
- L78 _public prototype_ `void SetupUMGEditorStyles();`
- L79 _public prototype_ `void SetupHomeScreenStyles();`
- L80 _public prototype_ `void SetupMyBlueprintStyles();`
- L81 _public prototype_ `void SetupStatusBarStyle();`
- L82 _public prototype_ `void SetupColorPickerStyle();`
- L83 _public prototype_ `void SetupDerivedDataStyle();`
- L84 _public prototype_ `void SetupSourceCodeStyles();`
- L86 _public prototype_ `void SettingsChanged(FName PropertyName);`
- L87 _public prototype_ `void SyncSettings();`
- L88 _public prototype_ `void SyncParentStyles();`
- L90 _public prototype_ `static void SetColor(const TSharedRef<FLinearColor>& Source, const FLinearColor& Value);`
- L91 _public prototype_ `static bool IncludeEditorSpecificStyles();`
- L93 _public member_ `static const FVector2f Icon7x16;`
- L94 _public member_ `static const FVector2f Icon8x4;`
- L95 _public member_ `static const FVector2f Icon16x4;`
- L96 _public member_ `static const FVector2f Icon8x8;`
- L97 _public member_ `static const FVector2f Icon10x10;`
- L98 _public member_ `static const FVector2f Icon12x12;`
- L99 _public member_ `static const FVector2f Icon12x16;`
- L100 _public member_ `static const FVector2f Icon14x14;`
- L101 _public member_ `static const FVector2f Icon16x16;`
- L102 _public member_ `static const FVector2f Icon16x20;`
- L103 _public member_ `static const FVector2f Icon20x20;`
- L104 _public member_ `static const FVector2f Icon22x22;`
- L105 _public member_ `static const FVector2f Icon24x24;`
- L106 _public member_ `static const FVector2f Icon25x25;`
- L107 _public member_ `static const FVector2f Icon32x32;`
- L108 _public member_ `static const FVector2f Icon40x40;`
- L109 _public member_ `static const FVector2f Icon48x48;`
- L110 _public member_ `static const FVector2f Icon64x64;`
- L111 _public member_ `static const FVector2f Icon36x24;`
- L112 _public member_ `static const FVector2f Icon128x128;`
- L115 _public member_ `const TSharedRef< FLinearColor > SelectionColor_Subdued_LinearRef;` — These are the colors that are updated by the user style customizations
- L116 _public member_ `const TSharedRef< FLinearColor > HighlightColor_LinearRef;`
- L117 _public member_ `const TSharedRef< FLinearColor > WindowHighlightColor_LinearRef;`
- L121 _public member_ `FSlateColor DefaultForeground;` — These are the Slate colors which reference those above; these are the colors to put into the style Most of these are owned by our parent style
- L122 _public member_ `FSlateColor InvertedForeground;`
- L123 _public member_ `FSlateColor SelectorColor;`
- L124 _public member_ `FSlateColor SelectionColor;`
- L125 _public member_ `FSlateColor SelectionColor_Inactive;`
- L126 _public member_ `FSlateColor SelectionColor_Pressed;`
- L128 _public member_ `const FSlateColor SelectionColor_Subdued;`
- L129 _public member_ `const FSlateColor HighlightColor;`
- L130 _public member_ `const FSlateColor WindowHighlightColor;`
- L133 _public member_ `const FSlateColor InheritedFromBlueprintTextColor;` — These are common colors used throughout the editor in multiple style elements
- L136 _public member_ `FTextBlockStyle NormalText;` — Styles inherited from the parent style
- L137 _public member_ `FEditableTextBoxStyle NormalEditableTextBoxStyle;`
- L138 _public member_ `FTableRowStyle NormalTableRowStyle;`
- L139 _public member_ `FButtonStyle Button;`
- L140 _public member_ `FButtonStyle HoverHintOnly;`
- L141 _public member_ `FButtonStyle NoBorder;`
- L142 _public member_ `FScrollBarStyle ScrollBar;`
- L143 _public member_ `FSlateFontInfo NormalFont;`
- L145 _public member_ `FSlateBrush* WindowTitleOverride;`
- L147 _public member_ `FDelegateHandle SettingChangedHandler;`

### `Source/Editor/EditorStyle/Public/EditorFontGlyphs.h` (Public)


#### class `FEditorFontGlyphs`  
`class FEditorFontGlyphs`  
_L11-298_
- L15 _public member_ `static FText Angle_Double_Left;` — (laquo, quote, previous, back) http://fortawesome.github.io/Font-Awesome/icon/angle-double-left/
- L18 _public member_ `static FText Angle_Double_Right;` — (raquo, quote, next, forward) http://fortawesome.github.io/Font-Awesome/icon/angle-double-right/
- L21 _public member_ `static FText Angle_Left;` — (previous, back) http://fortawesome.github.io/Font-Awesome/icon/angle-left/
- L24 _public member_ `static FText Angle_Right;` — (next, forward) http://fortawesome.github.io/Font-Awesome/icon/angle-right/
- L27 _public member_ `static FText Angle_Up;` — http://fortawesome.github.io/Font-Awesome/icon/angle-up/
- L30 _public member_ `static FText Archive;` — (box, storage) http://fortawesome.github.io/Font-Awesome/icon/archive/
- L33 _public member_ `static FText Arrow_Circle_O_Right;` — (next, forward) http://fortawesome.github.io/Font-Awesome/icon/arrow-circle-o-right/
- L36 _public member_ `static FText Arrow_Down;` — (download) http://fortawesome.github.io/Font-Awesome/icon/arrow-down/
- L39 _public member_ `static FText Arrow_Left;` — (previous, back) http://fortawesome.github.io/Font-Awesome/icon/arrow-left/
- L42 _public member_ `static FText Arrow_Right;` — (next, forward) http://fortawesome.github.io/Font-Awesome/icon/arrow-right/
- L45 _public member_ `static FText Arrows;` — (move, reorder, resize) http://fortawesome.github.io/Font-Awesome/icon/arrows/
- L48 _public member_ `static FText Ban;` — (delete, remove, trash, hide, block, stop, abort, cancel) http://fortawesome.github.io/Font-Awesome/icon/ban/
- L51 _public member_ `static FText Bars;` — (menu, drag, reorder, settings, list, ul, ol, checklist, todo, list, hamburger) http://fortawesome.github.io/Font-Awesome/icon/bars/
- L54 _public member_ `static FText Book;` — (read, documentation) http://fortawesome.github.io/Font-Awesome/icon/book/
- L57 _public member_ `static FText Bug;` — (report, insect) http://fortawesome.github.io/Font-Awesome/icon/bug/
- L60 _public member_ `static FText Car;` — (vehicle) http://fortawesome.github.io/Font-Awesome/icon/car/
- L63 _public member_ `static FText Caret_Down;` — (more, dropdown, menu, triangle down) http://fortawesome.github.io/Font-Awesome/icon/caret-down/
- L66 _public member_ `static FText Caret_Right;` — (next, forward, triangle right) http://fortawesome.github.io/Font-Awesome/icon/caret-right/
- L69 _public member_ `static FText Caret_Square_O_Down;` — (more, dropdown, menu) http://fortawesome.github.io/Font-Awesome/icon/caret-square-o-down/
- L72 _public member_ `static FText Caret_Square_O_Left;` — (previous, back) http://fortawesome.github.io/Font-Awesome/icon/caret-square-o-left/
- L75 _public member_ `static FText Caret_Square_O_Right;` — (next, forward) http://fortawesome.github.io/Font-Awesome/icon/caret-square-o-right/
- L78 _public member_ `static FText Caret_Square_O_Up;` — http://fortawesome.github.io/Font-Awesome/icon/caret-square-o-up/
- L81 _public member_ `static FText Caret_Up;` — (triangle up) http://fortawesome.github.io/Font-Awesome/icon/caret-up/
- L84 _public member_ `static FText Check;` — (checkmark, done, todo, agree, accept, confirm, tick) http://fortawesome.github.io/Font-Awesome/icon/check/
- L87 _public member_ `static FText Check_Circle;` — (todo, done, agree, accept, confirm) http://fortawesome.github.io/Font-Awesome/icon/check-circle/
- L90 _public member_ `static FText Circle;` — (dot, notification) http://fortawesome.github.io/Font-Awesome/icon/circle/
- L93 _public member_ `static FText Circle_O;` — http://fortawesome.github.io/Font-Awesome/icon/circle-o/
- L96 _public member_ `static FText Clock_O;` — (watch, timer, late, timestamp) http://fortawesome.github.io/Font-Awesome/icon/clock-o/
- L99 _public member_ `static FText Cog;` — (settings) http://fortawesome.github.io/Font-Awesome/icon/cog/
- L102 _public member_ `static FText Cogs;` — (settings) http://fortawesome.github.io/Font-Awesome/icon/cogs/
- L105 _public member_ `static FText Crosshairs;` — (picker) http://fortawesome.github.io/Font-Awesome/icon/crosshairs/
- L108 _public member_ `static FText Database;` — http://fortawesome.github.io/Font-Awesome/icon/database/
- L111 _public member_ `static FText Download;` — (import) http://fortawesome.github.io/Font-Awesome/icon/download/
- L114 _public member_ `static FText Eraser;` — http://fortawesome.github.io/Font-Awesome/icon/eraser/
- L117 _public member_ `static FText Exchange;` — (transfer, arrows) http://fortawesome.github.io/Font-Awesome/icon/exchange/
- L120 _public member_ `static FText Exclamation;` — (warning, error, problem, notification, notify, alert) http://fortawesome.github.io/Font-Awesome/icon/exclamation/
- L123 _public member_ `static FText Exclamation_Triangle;` — (warning, error, problem, notification, alert) http://fortawesome.github.io/Font-Awesome/icon/exclamation-triangle/
- L126 _public member_ `static FText Expand;` — (enlarge, bigger, resize) http://fortawesome.github.io/Font-Awesome/icon/expand/
- L129 _public member_ `static FText External_Link;` — (open, new) http://fortawesome.github.io/Font-Awesome/icon/external-link/
- L132 _public member_ `static FText Eye;` — (show, visible, views) http://fortawesome.github.io/Font-Awesome/icon/eye/
- L135 _public member_ `static FText Eye_Slash;` — (toggle, show, hide, visible, visiblity, views) http://fortawesome.github.io/Font-Awesome/icon/eye-slash/
- L138 _public member_ `static FText Fast_Forward;` — (next, end, last) http://fortawesome.github.io/Font-Awesome/icon/fast-forward/
- L141 _public member_ `static FText File;` — (new, page, pdf, document) http://fortawesome.github.io/Font-Awesome/icon/file/
- L144 _public member_ `static FText Film;` — (movie) http://fortawesome.github.io/Font-Awesome/icon/film/
- L147 _public member_ `static FText Filter;` — (funnel, options) http://fortawesome.github.io/Font-Awesome/icon/filter/
- L150 _public member_ `static FText Floppy_O;` — http://fortawesome.github.io/Font-Awesome/icon/floppy-o/
- L153 _public member_ `static FText Folder;` — http://fortawesome.github.io/Font-Awesome/icon/folder/
- L156 _public member_ `static FText Folder_Open;` — http://fortawesome.github.io/Font-Awesome/icon/folder-open/
- L159 _public member_ `static FText Hourglass;` — http://fortawesome.github.io/Font-Awesome/icon/hourglass/
- L162 _public member_ `static FText Hourglass_O;` — http://fortawesome.github.io/Font-Awesome/icon/hourglass-o/
- L165 _public member_ `static FText Info;` — (help, information, more, details) http://fortawesome.github.io/Font-Awesome/icon/info/
- L168 _public member_ `static FText Info_Circle;` — (help, information, more, details) http://fortawesome.github.io/Font-Awesome/icon/info-circle/
- L171 _public member_ `static FText Level_Down;` — http://fortawesome.github.io/Font-Awesome/icon/level-down/
- L174 _public member_ `static FText Level_Up;` — http://fortawesome.github.io/Font-Awesome/icon/level-up/
- L177 _public member_ `static FText Lightbulb_O;` — (idea, inspiration) http://fortawesome.github.io/Font-Awesome/icon/lightbulb-o/
- L180 _public member_ `static FText Line_Chart;` — (graph, analytics) http://fortawesome.github.io/Font-Awesome/icon/line-chart/
- L183 _public member_ `static FText Link;` — (chain) http://fortawesome.github.io/Font-Awesome/icon/link/
- L186 _public member_ `static FText Lock;` — (protect, admin) http://fortawesome.github.io/Font-Awesome/icon/lock/
- L189 _public member_ `static FText Long_Arrow_Down;` — http://fortawesome.github.io/Font-Awesome/icon/long-arrow-down/
- L192 _public member_ `static FText Long_Arrow_Right;` — http://fortawesome.github.io/Font-Awesome/icon/long-arrow-right/
- L195 _public member_ `static FText Map;` — http://fortawesome.github.io/Font-Awesome/icon/map/
- L198 _public member_ `static FText Map_Marker;` — (map, pin, location, coordinates, localize, address, travel, where, place) http://fortawesome.github.io/Font-Awesome/icon/map-marker/
- L201 _public member_ `static FText Minus;` — (hide, minify, delete, remove, trash, hide, collapse) http://fortawesome.github.io/Font-Awesome/icon/minus/
- L204 _public member_ `static FText Minus_Circle;` — (delete, remove, trash, hide) http://fortawesome.github.io/Font-Awesome/icon/minus-circle/
- L207 _public member_ `static FText Paper_Plane;` — http://fortawesome.github.io/Font-Awesome/icon/paper-plane/
- L210 _public member_ `static FText Pause;` — (wait) http://fortawesome.github.io/Font-Awesome/icon/pause/
- L213 _public member_ `static FText Pause_Circle;` — http://fortawesome.github.io/Font-Awesome/icon/pause-circle/
- L216 _public member_ `static FText Pencil;` — (write, edit, update) http://fortawesome.github.io/Font-Awesome/icon/pencil/
- L219 _public member_ `static FText Pencil_Square;` — (write, edit, update) http://fortawesome.github.io/Font-Awesome/icon/pencil-square/
- L222 _public member_ `static FText Play;` — (start, playing, music, sound) http://fortawesome.github.io/Font-Awesome/icon/play/
- L225 _public member_ `static FText Play_Circle;` — (start, playing) http://fortawesome.github.io/Font-Awesome/icon/play-circle/
- L228 _public member_ `static FText Plug;` — http://fortawesome.github.io/Font-Awesome/icon/plug/
- L231 _public member_ `static FText Plus;` — (add, new, create, expand) http://fortawesome.github.io/Font-Awesome/icon/plus/
- L234 _public member_ `static FText Plus_Circle;` — (add, new, create, expand) http://fortawesome.github.io/Font-Awesome/icon/plus-circle/
- L237 _public member_ `static FText Question;` — (help, information, unknown, support) http://fortawesome.github.io/Font-Awesome/icon/question/
- L240 _public member_ `static FText Random;` — (sort, shuffle) http://fortawesome.github.io/Font-Awesome/icon/random/
- L243 _public member_ `static FText Recycle;` — http://fortawesome.github.io/Font-Awesome/icon/recycle/
- L246 _public member_ `static FText Refresh;` — (reload, sync) http://fortawesome.github.io/Font-Awesome/icon/refresh/
- L249 _public member_ `static FText Share;` — http://fortawesome.github.io/Font-Awesome/icon/share/
- L252 _public member_ `static FText Share_Alt;` — http://fortawesome.github.io/Font-Awesome/icon/share-alt/
- L255 _public member_ `static FText Sign_In;` — (enter, join, log in, login, sign up, sign in, signin, signup, arrow) http://fortawesome.github.io/Font-Awesome/icon/sign-in/
- L258 _public member_ `static FText Sign_Out;` — (log out, logout, leave, exit, arrow) http://fortawesome.github.io/Font-Awesome/icon/sign-out/
- L261 _public member_ `static FText Square;` — (block, box) http://fortawesome.github.io/Font-Awesome/icon/square/
- L264 _public member_ `static FText Star;` — (award, achievement, night, rating, score) http://fortawesome.github.io/Font-Awesome/icon/star/
- L267 _public member_ `static FText Step_Forward;` — (next, end, last) http://fortawesome.github.io/Font-Awesome/icon/step-forward/
- L270 _public member_ `static FText Stop;` — (block, box, square) http://fortawesome.github.io/Font-Awesome/icon/stop/
- L273 _public member_ `static FText Terminal;` — (command, prompt, code) http://fortawesome.github.io/Font-Awesome/icon/terminal/
- L276 _public member_ `static FText Th;` — (blocks, squares, boxes) http://fortawesome.github.io/Font-Awesome/icon/th/
- L279 _public member_ `static FText Thumb_Tack;` — (marker, pin, location, coordinates) http://fortawesome.github.io/Font-Awesome/icon/thumb-tack/
- L282 _public member_ `static FText Times;` — (close, exit, x, cross) http://fortawesome.github.io/Font-Awesome/icon/times/
- L285 _public member_ `static FText Times_Circle;` — (close, exit, x) http://fortawesome.github.io/Font-Awesome/icon/times-circle/
- L288 _public member_ `static FText Trash;` — (garbage, delete, remove, hide) http://fortawesome.github.io/Font-Awesome/icon/trash/
- L291 _public member_ `static FText Undo;` — (back) http://fortawesome.github.io/Font-Awesome/icon/undo/
- L294 _public member_ `static FText Unlock;` — (protect, admin, password, lock) http://fortawesome.github.io/Font-Awesome/icon/unlock/
- L297 _public member_ `static FText Video_Camera;` — (film, movie, record) http://fortawesome.github.io/Font-Awesome/icon/video-camera/

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API EDITORSTYLE_API`

### `Source/Editor/EditorStyle/Public/EditorStyle.h` (Public)
_(no declarations extracted)_

### `Source/Editor/EditorStyle/Public/EditorStyleSet.h` (Public)


#### class `FEditorStyle`  
`class FEditorStyle`  
_L34-193_
- desc: A collection of named properties that guide the appearance of Slate.
- L52 _public function_ `static const ISlateStyle& Get( )` — `UE_DEPRECATED(5.1, "FEditorStyle::Get() is deprecated, use FAppStyle::Get() instead.")` — @return the Application Style NOTE: Until the Editor can be fully updated, calling FEditorStyle::Get() or any of its static convenience functions will will return the AppStyle instead of the style definied in this class. Using the AppStyle is preferred in most cases as it allows the style to be changed on an application level. In cases requiring explicit use of the EditorStyle where a Slate Widget should not take on the appearance of the rest of the application, use FEditorStyle::GetEditorStyle().
- L59 _public function_ `static const T& GetWidgetStyle( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetWidgetStyle() is deprecated, use FAppStyle::GetWidgetStyle() instead.")`
- L65 _public function_ `static float GetFloat( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetFloat() is deprecated, use FAppStyle::GetFloat() instead.")`
- L71 _public function_ `static FVector2D GetVector( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetVector() is deprecated, use FAppStyle::GetVector() instead.")`
- L77 _public function_ `static const FLinearColor& GetColor( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetColor() is deprecated, use FAppStyle::GetColor() instead.")`
- L83 _public function_ `static const FSlateColor GetSlateColor( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetSlateColor() is deprecated, use FAppStyle::GetSlateColor() instead.")`
- L89 _public function_ `static const FMargin& GetMargin( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetMargin() is deprecated, use FAppStyle::GetMargin() instead.")`
- L95 _public function_ `static const FSlateBrush* GetBrush( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetBrush() is deprecated, use FAppStyle::GetBrush() instead.")`
- L101 _public function_ `static const TSharedPtr< FSlateDynamicImageBrush > GetDynamicImageBrush( FName BrushTemplate, FName TextureName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetDynamicImageBrush() is deprecated, use FAppStyle::GetDynamicImageBrush() instead.")`
- L107 _public function_ `static const TSharedPtr< FSlateDynamicImageBrush > GetDynamicImageBrush( FName BrushTemplate, const ANSICHAR* Specifier, class UTexture2D* TextureResource, FName TextureName )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetDynamicImageBrush() is deprecated, use FAppStyle::GetDynamicImageBrush() instead.")`
- L113 _public function_ `static const TSharedPtr< FSlateDynamicImageBrush > GetDynamicImageBrush( FName BrushTemplate, class UTexture2D* TextureResource, FName TextureName )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetDynamicImageBrush() is deprecated, use FAppStyle::GetDynamicImageBrush() instead.")`
- L119 _public function_ `static const FSlateSound& GetSound( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetSound() is deprecated, use FAppStyle::GetSound() instead.")`
- L125 _public function_ `static FSlateFontInfo GetFontStyle( FName PropertyName, const ANSICHAR* Specifier = NULL )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetFontStyle() is deprecated, use FAppStyle::GetFontStyle() instead.")`
- L131 _public function_ `static const FSlateBrush* GetDefaultBrush()` — `UE_DEPRECATED(5.1, "FEditorStyle::GetDefaultBrush() is deprecated, use FAppStyle::GetDefaultBrush() instead.")`
- L137 _public function_ `static const FSlateBrush* GetNoBrush()` — `UE_DEPRECATED(5.1, "FEditorStyle::GetNoBrush() is deprecated, use FAppStyle::GetNoBrush() instead.")`
- L143 _public function_ `static const FSlateBrush* GetOptionalBrush( FName PropertyName, const ANSICHAR* Specifier = NULL, const FSlateBrush* const DefaultBrush = FStyleDefaults::GetNoBrush() )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetOptionalBrush() is deprecated, use FAppStyle::GetOptionalBrush() instead.")`
- L149 _public function_ `static void GetResources( TArray< const FSlateBrush* >& OutResources )` — `UE_DEPRECATED(5.1, "FEditorStyle::GetResources() is deprecated, use FAppStyle::GetResources() instead.")`
- L155 _public function_ `static const FName& GetStyleSetName()` — `UE_DEPRECATED(5.1, "FEditorStyle::GetStyleSetName() is deprecated, use FAppStyle::GetAppStyleSetName() instead.")`
- L170 _public function_ `static FName Join( FName A, const ANSICHAR* B )` — `UE_DEPRECATED(5.1, "FEditorStyle::Join() is deprecated, use FAppStyle::Join() instead.")` — Concatenates two FNames.e If A and B are "Path.To" and ".Something" the result "Path.To.Something". @param A  First FName @param B  Second name @return New FName that is A concatenated with B.
- L182 _public prototype_ `static void ResetToDefault();`
- L187 _protected prototype_ `static void SetStyle( const TSharedRef< class ISlateStyle >& NewStyle );`
- L192 _private member_ `static TSharedPtr< class ISlateStyle > Instance;` — Singleton instance of the slate style

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API EDITORSTYLE_API`

### `Source/Editor/EditorStyle/Public/Interfaces/IEditorStyleModule.h` (Public)


#### class `IEditorStyleModule`  
`class IEditorStyleModule : public IModuleInterface`  
_L7-10_
- inherits: `IModuleInterface`
