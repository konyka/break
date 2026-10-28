# Editor / EditorWidgets

- module root: `Source/Editor/EditorWidgets`
- headers: 26; symbols: 722
- symbol kinds: class=31, delegate=25, enum=4, enumerator=19, function=109, macro=14, member=214, namespace=15, prototype=264, struct=11, typedef=16
- DynamicallyLoadedModuleNames: AssetRegistry
- PrivateIncludePathModuleNames: AssetRegistry
- PublicDependencyModuleNames: AssetDefinition, Core, CoreUObject, EditorConfig, Engine, InputCore, Slate, SlateCore, ToolWidgets, UnrealEd

### `Source/Editor/EditorWidgets/Private/EditorWidgetsStyle.h` (Private)


#### class `FEditorWidgetsStyle`  
`class FEditorWidgetsStyle`  
_L10-23_
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static const ISlateStyle& Get();`
- L18 _public prototype_ `static const FName& GetStyleSetName();`
- L22 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;` — Singleton instances of this style.

### `Source/Editor/EditorWidgets/Private/SAssetDiscoveryIndicator.h` (Private)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SAssetDiscoveryIndicator>`  
_L23-26_
- L25 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SAssetDiscoveryIndicator`  
`class SAssetDiscoveryIndicator : public SCompoundWidget`  
_L29-114_
- inherits: `SCompoundWidget`
- desc: An indicator for the progress of the asset registry background search
- L32 _public function_ `SLATE_BEGIN_ARGS( SAssetDiscoveryIndicator ) : _ScaleMode(EAssetDiscoveryIndicatorScaleMode::Scale_None) , _FadeIn(true)`
- L42 _public prototype_ `SLATE_ARGUMENT( EAssetDiscoveryIndicatorScaleMode::Type, ScaleMode ) SLATE_ARGUMENT( FMargin, Padding ) SLATE_ARGUMENT( bool, FadeIn ) SLATE_END_ARGS() virtual ~SAssetDiscoveryIndicator();` — The way the indicator will scale out when done displaying progress
- L56 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L59 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SCompoundWidget interface
- L62 _public prototype_ `void OnAssetRegistryFileLoadProgress(const IAssetRegistry::FFileLoadProgressUpdateData& ProgressUpdateData);` — Handles updating the progress from the asset registry
- L65 _public prototype_ `void OnAssetRegistryFilesLoaded();` — Handles updating the progress from the asset registry
- L68 _public prototype_ `FText GetMainStatusText() const;` — Gets the main status text
- L71 _public prototype_ `FText GetSubStatusText() const;` — Gets the sub status text
- L74 _public prototype_ `TOptional<float> GetProgress() const;` — Gets the progress bar fraction
- L77 _public prototype_ `EVisibility GetSubStatusTextVisibility() const;` — Gets the sub status text visbility
- L80 _public prototype_ `float GetStatusTextWrapWidth() const;` — Get the current wrap point for the status text
- L83 _public prototype_ `FSlateColor GetBorderBackgroundColor() const;` — Gets the background's opacity
- L86 _public prototype_ `FLinearColor GetIndicatorColorAndOpacity() const;` — Gets the whole widget's opacity
- L89 _public prototype_ `FVector2D GetIndicatorDesiredSizeScale() const;` — Gets the whole widget's opacity
- L92 _public prototype_ `EVisibility GetIndicatorVisibility() const;` — Gets the whole widget's visibility
- L96 _private member_ `FText MainStatusText;` — The main status text
- L99 _private member_ `FText SubStatusText;` — The sub status text (if any)
- L102 _private member_ `TOptional<float> Progress;` — The asset registry's asset discovery progress as a percentage
- L105 _private member_ `float StatusTextWrapWidth;` — The current wrap point for the status text
- L108 _private member_ `EAssetDiscoveryIndicatorScaleMode::Type ScaleMode;` — The way the indicator will scale in/out before/after displaying progress
- L111 _private member_ `FCurveSequence FadeAnimation;` — The fade in/out animation
- L112 _private member_ `FCurveHandle FadeCurve;`
- L113 _private member_ `FCurveHandle ScaleCurve;`

### `Source/Editor/EditorWidgets/Private/SObjectNameEditableTextBox.h` (Private)


#### class `SObjectNameEditableTextBox`  
`class SObjectNameEditableTextBox : public IObjectNameEditableTextBox`  
_L27-120_
- inherits: `IObjectNameEditableTextBox`
- desc: Widget wraps an editable text box for viewing the names of objects or editing the labels of actors
- L30 _public function_ `SLATE_BEGIN_ARGS(SObjectNameEditableTextBox)`
- L32 _public prototype_ `SLATE_ARGUMENT(TArray<TWeakObjectPtr<UObject>>, Objects) SLATE_ARGUMENT(TWeakPtr<UE::EditorWidgets::FObjectNameEditSinkRegistry>, Registry) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L47 _protected prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L49 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L53 _private prototype_ `EActiveTimerReturnType UpdateHighlightSpringState( double InCurrentTime, float InDeltaTime );` — Updates whether the highlight spring effect is happening
- L56 _private prototype_ `FText GetNameText() const;` — Getter for the Text attribute of the editable text inside this widget
- L59 _private prototype_ `EVisibility GetNameVisibility() const;` — Should the name editing text box even be visible?
- L62 _private prototype_ `FText GetNameTooltipText() const;` — Getter for the ToolTipText attribute of the editable text inside this widget
- L65 _private prototype_ `void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);` — Getter for the OnTextCommitted event of the editable text inside this widget
- L68 _private prototype_ `bool IsReadOnly() const;` — Getter for the IsReadOnly attribute of the editable text inside this widget
- L71 _private prototype_ `FText GetObjectDisplayName(TWeakObjectPtr<UObject> Object) const;` — Helper function to access name registry and retrieve display name
- L74 _private prototype_ `EVisibility GetNameSuffixVisibility() const;` — Helper function to access name registry and determine if the name has a suffix
- L77 _private prototype_ `FText GetObjectDisplayNameSuffix() const;` — Access name registry and retrieve the name suffix, if there is one
- L80 _private member_ `TArray<TWeakObjectPtr<UObject>> Objects;` — The list of objects whose names are edited by the widget
- L83 _private member_ `FString UserSetCommonName;` — The current user-entered text for a list of more than one object
- L86 _private member_ `static const float HighlightRectLeftOffset;` — How many pixels to extend the highlight rectangle's left side horizontally
- L89 _private member_ `static const float HighlightRectRightOffset;` — How many pixels to extend the highlight rectangle's right side horizontally
- L92 _private member_ `static const float HighlightTargetSpringConstant;` — How quickly the highlight 'targeting' rectangle will slide around.  Larger is faster.
- L95 _private member_ `static const float HighlightTargetEffectDuration;` — Duration of animation highlight target effects
- L98 _private member_ `static const float HighlightTargetOpacity;` — Opacity of the highlight target effect overlay
- L101 _private member_ `static const float CommittingAnimOffsetPercent;` — How large the highlight target effect will be when highlighting, as a scalar percentage of font height
- L104 _private member_ `FFloatSpring1D HighlightTargetLeftSpring;` — Highlight "targeting" visual effect left position
- L107 _private member_ `FFloatSpring1D HighlightTargetRightSpring;` — Highlight "targeting" visual effect right position
- L110 _private member_ `double LastCommittedTime;` — Last time that the user had a major interaction with the highlight
- L113 _private member_ `TSharedPtr< SInlineEditableTextBlock > TextBox;` — The text box used to edit object names
- L116 _private member_ `TWeakPtr<UE::EditorWidgets::FObjectNameEditSinkRegistry> ObjectNameEditSinkRegistry;` — The registry for object names
- L119 _private member_ `bool bUpdateHighlightSpring;` — Temp flag to trigger a highlight spring update in the passive tick (because that's where the geometry is)

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace EditorWidgets` (scope `UE`)

### `Source/Editor/EditorWidgets/Private/STransportControl.h` (Private)


#### class `STransportControl`  
`class STransportControl : public ITransportControl, public FTickableEditorObject`  
_L19-74_
- inherits: `ITransportControl,FTickableEditorObject`
- L22 _public function_ `SLATE_BEGIN_ARGS(STransportControl) : _TransportArgs()`
- L25 _public prototype_ `SLATE_ARGUMENT(FTransportControlArgs, TransportArgs) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L35 _public prototype_ `virtual ~STransportControl() = default;`
- L40 _public prototype_ `virtual bool IsTickable() const override;`
- L41 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L42 _public function_ `virtual TStatId GetStatId() const override`
- L45 _private prototype_ `const FSlateBrush* GetForwardStatusIcon() const;`
- L46 _private prototype_ `FText GetForwardStatusTooltip() const;`
- L47 _private prototype_ `const FSlateBrush* GetRecordStatusIcon() const;`
- L48 _private prototype_ `FText GetRecordStatusTooltip() const;`
- L49 _private prototype_ `const FSlateBrush* GetBackwardStatusIcon() const;`
- L50 _private prototype_ `const FSlateBrush* GetLoopStatusIcon() const;`
- L51 _private prototype_ `FText GetLoopStatusTooltip() const;`
- L54 _private prototype_ `EActiveTimerReturnType TickPlayback( double InCurrentTime, float InDeltaTime );` — Executes the OnTickPlayback delegate
- L56 _private prototype_ `FReply OnToggleLooping();`
- L59 _private prototype_ `TSharedPtr<SWidget> MakeTransportControlWidget(ETransportControlWidgetType WidgetType, const FOnMakeTransportWidget& MakeCustomWidgetDelegate = FOnMakeTransportWidget());` — Make default transport control widgets
- L63 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the active timer
- L66 _private member_ `bool bIsActiveTimerRegistered;` — Whether the active timer is currently registered
- L68 _private member_ `FTransportControlArgs TransportControlArgs;`
- L70 _private member_ `TSharedPtr<SButton> ForwardPlayButton;`
- L71 _private member_ `TSharedPtr<SButton> BackwardPlayButton;`
- L72 _private member_ `TSharedPtr<SButton> RecordButton;`
- L73 _private member_ `TSharedPtr<SButton> LoopButton;`

### `Source/Editor/EditorWidgets/Private/TemplateStringSyntaxHighlighterMarshaller.h` (Private)


#### class `FTemplateStringSyntaxHighlighterMarshaller`  
`class FTemplateStringSyntaxHighlighterMarshaller : public FSyntaxHighlighterTextLayoutMarshaller`  
_L19-54_
- inherits: `FSyntaxHighlighterTextLayoutMarshaller`
- desc: Get/set the raw text to/from a text layout, and also inject syntax highlighting for our rich-text markup
- L40 _public prototype_ `static TSharedRef<FTemplateStringSyntaxHighlighterMarshaller> Create(const FSyntaxTextStyle& InSyntaxTextStyle);`
- L42 _public prototype_ `virtual ~FTemplateStringSyntaxHighlighterMarshaller() override = default;`
- L48 _protected prototype_ `virtual void ParseTokens(const FString& SourceString, FTextLayout& TargetTextLayout, TArray<ISyntaxTokenizer::FTokenizedLine> TokenizedLines) override;`
- L50 _protected prototype_ `FTemplateStringSyntaxHighlighterMarshaller(TSharedPtr<ISyntaxTokenizer> InTokenizer, const FSyntaxTextStyle& InSyntaxTextStyle);`
- L53 _protected member_ `FSyntaxTextStyle SyntaxTextStyle;` — Styles used to display the text

#### struct `FTemplateStringSyntaxHighlighterMarshaller::FSyntaxTextStyle`  
`struct FSyntaxTextStyle`  
_L22-38_
- L24 _public function_ `FSyntaxTextStyle() : NormalTextStyle(FEditorWidgetsStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.Template.Normal")) , ArgumentTextStyle(FEditorWidgetsStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.Template.Argument"))`
- L30 _public function_ `FSyntaxTextStyle(const FTextBlockStyle& InNormalTextStyle, const FTextBlockStyle& InArgumentTextStyle) : NormalTextStyle(InNormalTextStyle) , ArgumentTextStyle(InArgumentTextStyle)`
- L36 _public member_ `FTextBlockStyle NormalTextStyle;`
- L37 _public member_ `FTextBlockStyle ArgumentTextStyle;`

### `Source/Editor/EditorWidgets/Public/AssetDiscoveryIndicator.h` (Public)


#### enum `EAssetDiscoveryIndicatorScaleMode::Type`  
`enum Type`  
_L9-15_
- L11 _public enumerator_ `Scale_None`
- L12 _public enumerator_ `Scale_Vertical`
- L13 _public enumerator_ `Scale_Horizontal`
- L14 _public enumerator_ `Scale_Both`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace EAssetDiscoveryIndicatorScaleMode`

### `Source/Editor/EditorWidgets/Public/DetailNameAreaObjectFilterRegistry.h` (Public)


#### class `UE::EditorWidgets::IDetailNameAreaObjectFilter`  
`class IDetailNameAreaObjectFilter`  
_L16-22_
- L19 _public prototype_ `virtual ~IDetailNameAreaObjectFilter() = default;`
- L20 _public prototype_ `virtual FName GetFilterName() const = 0;`
- L21 _public prototype_ `virtual void FilterSelectedObjectsForNameArea(TArray<TWeakObjectPtr<UObject>>& InOutObjects) = 0;`

#### class `UE::EditorWidgets::FDetailNameAreaObjectFilterRegistry`  
`class FDetailNameAreaObjectFilterRegistry`  
_L24-36_
- L28 _public prototype_ `void RegisterDetailNameAreaObjectFilter(TUniquePtr<IDetailNameAreaObjectFilter>&& NewNameAreaFilter);`
- L29 _public prototype_ `void UnregisterDetailNameAreaObjectFilter(const FName& FilterName);`
- L31 _public prototype_ `void ApplyAllFiltersToSelectedObjects(TArray<TWeakObjectPtr<UObject>>& InOutObjects) const;`
- L35 _private member_ `TMap<FName, TUniquePtr<IDetailNameAreaObjectFilter>> ObjectFilters;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORWIDGETS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace EditorWidgets` (scope `UE`)

### `Source/Editor/EditorWidgets/Public/EditorWidgets.h` (Public)
_(no declarations extracted)_

### `Source/Editor/EditorWidgets/Public/EditorWidgetsModule.h` (Public)


#### class `IObjectNameEditableTextBox`  
`class IObjectNameEditableTextBox : public SCompoundWidget`  
_L28-30_
- inherits: `SCompoundWidget`
- desc: Interface for the widget that wraps an editable text box for viewing the names of objects or editing the labels of actors

#### class `FEditorWidgetsModule`  
`class FEditorWidgetsModule : public IModuleInterface`  
_L35-91_
- inherits: `IModuleInterface`
- desc: Editor Widgets module
- L42 _public prototype_ `virtual void StartupModule();` — Called right after the plugin DLL has been loaded and the plugin object has been created
- L47 _public prototype_ `virtual void ShutdownModule();` — Called before the plugin is unloaded, right before the plugin object is destroyed.
- L55 _public prototype_ `virtual TSharedRef<IObjectNameEditableTextBox> CreateObjectNameEditableTextBox(const TArray<TWeakObjectPtr<UObject>>& Objects);` — Creates a new text box for viewing the names of objects or editing the labels of actors @param Objects		The list of objects that the editable text box shows/edits the names @return The new editable text box
- L64 _public prototype_ `virtual TSharedRef<SWidget> CreateAssetDiscoveryIndicator(EAssetDiscoveryIndicatorScaleMode::Type ScaleMode = EAssetDiscoveryIndicatorScaleMode::Scale_None, FMargin Padding = FMargin(0), bool bFadeIn = true);` — Creates a widget that visualizes the asset discovery progress and collapses away when complete @param ScaleMode		The direction the widget will scale when animating in and out @param Padding		The padding to apply to the widget internally @return The indicator widget
- L72 _public prototype_ `virtual TSharedRef<ITransportControl> CreateTransportControl(const FTransportControlArgs& Args);` — Creates a widget that allows play/pause, and general time controls @param Args The arguments used to generate the widget @return The transport control widget
- L79 _public prototype_ `virtual TSharedRef<UE::EditorWidgets::FObjectNameEditSinkRegistry> GetObjectNameEditSinkRegistry() const;` — Gets the registry of name edit 'sinks' used for getting and editing object display names @return The registry
- L81 _public prototype_ `virtual TSharedRef<UE::EditorWidgets::FDetailNameAreaObjectFilterRegistry> GetDetailNameAreaObjectFilterRegistry() const;`
- L84 _public member_ `static const FName EditorWidgetsAppIdentifier;` — Editor Widgets app identifier string
- L88 _private member_ `TSharedPtr<UE::EditorWidgets::FObjectNameEditSinkRegistry> ObjectNameEditSinkRegistry;` — Registry for name interfaces
- L90 _private member_ `TSharedPtr<UE::EditorWidgets::FDetailNameAreaObjectFilterRegistry> DetailNameAreaObjectFilterRegistry;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace EditorWidgets` (scope `UE`)

### `Source/Editor/EditorWidgets/Public/Filters/AssetFilter.h` (Public)


#### class `FAssetFilter`  
`template<typename FilterType> class FAssetFilter : public FFilterBase<FilterType>`  
_L17-166_
- inherits: `FFilterBase<FilterType>`
- desc: A filter used by SFilterBar that wraps all the back-end filters into one FFilterBase for convenience
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCompareItemWithClassNames, FilterType , const TSet<FTopLevelAssetPath>& );` — A delegate that the user can use to specify how to compare their Filter Item to a list of Asset Types represented as FNames
- L27 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FConvertItemToAssetData, FilterType , FAssetData& );` — A delegate that the user can use to specify how to convert their Filter Item into an FAssetData @return: true if the Filter Item was successfully converted, false if not (the current item will not be tested for asset filters if so)
- L30 _public function_ `FAssetFilter() : FFilterBase<FilterType>(nullptr)`
- L36 _public function_ `void SetBackendFilter(const FARFilter& InBackendFilter)`
- L45 _public function_ `void SetComparisonFunction(FCompareItemWithClassNames InOnCompareItem)`
- L50 _public function_ `void SetConversionFunction(FConvertItemToAssetData InOnConvertItem)`
- L56 _public function_ `virtual FString GetName() const override` — Returns the system name for this filter
- L62 _public function_ `virtual FText GetDisplayName() const override` — Returns the human readable name for this filter
- L69 _public function_ `virtual FText GetToolTipText() const override` — Returns the tooltip for this filter, shown in the filters menu
- L76 _public function_ `virtual FLinearColor GetColor() const override` — Returns the color this filter button will be when displayed as a button
- L82 _public function_ `virtual FName GetIconName() const override` — Returns the name of the icon to use in menu entries
- L88 _public function_ `virtual bool IsInverseFilter() const override` — Returns true if the filter should be in the list when disabled and not in the list when enabled
- L93 _public function_ `virtual bool PassesFilter( FilterType InItem ) const override`
- L132 _public function_ `virtual void ActiveStateChanged(bool bActive) override` — Notification that the filter became active or inactive
- L138 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override` — Called when the right-click context menu is being built for this filter
- L144 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override` — Can be overriden for custom FilterBar subclasses to save settings, currently not implemented in any gneeric Filter Bar
- L150 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override` — Can be overriden for custom FilterBar subclasses to load settings, currently not implemented in any gneeric Filter Bar
- L158 _protected member_ `FARCompiledFilter CompiledBackendFilter;` — The compiled BackendFilter that contains all the Asset Filters attached to this Filter
- L161 _protected member_ `FCompareItemWithClassNames OnCompareItem;` — Delegate used to compare an item to a UClass represented by an FName
- L164 _protected member_ `FConvertItemToAssetData OnConvertItem;` — Delegate used to convert an item to an FAssetData

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCompareItemWithClassNames, FilterType , const TSet<FTopLevelAssetPath>& );` — A delegate that the user can use to specify how to compare their Filter Item to a list of Asset Types represented as FNames
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FConvertItemToAssetData, FilterType , FAssetData& );` — A delegate that the user can use to specify how to convert their Filter Item into an FAssetData @return: true if the Filter Item was successfully converted, false if not (the current item will not be tested for asset filters if so)

### `Source/Editor/EditorWidgets/Public/Filters/CustomClassFilterData.h` (Public)


#### class `FCustomClassFilterData`  
`class FCustomClassFilterData`  
_L27-88_
- desc: Helper Class that can be used to provide custom class filters to the Filter Widget Using this for Type Filters ensures that the type filters get OR'd together For example: filtering for StaticMeshActor and DirectionalLight will show assets that belong to either of those types.
- L32 _public prototype_ `FCustomClassFilterData(UAssetDefinition* InAssetDefinition, const FAssetFilterData& InAssetTypeAction);` — You can provide an IAssetTypeActions for your type to get all the information from that
- L35 _public prototype_ `FCustomClassFilterData(UClass* InClass, TSharedPtr<FFilterCategory> InCategory, FLinearColor InColor);` — Or you can provide a UClass, a Category and a Color to identify the filter
- L38 _public prototype_ `void AddCategory(TSharedPtr<FFilterCategory> InCategory);` — Unlike normal filters, Type Filters are allowed to belong to multiple categories
- L41 _public prototype_ `UClass* GetClass() const;` — Get the UClass associated with this filter
- L44 _public prototype_ `TArray<TSharedPtr<FFilterCategory>> GetCategories() const;` — Get the Catgories this filter belongs to
- L47 _public prototype_ `FLinearColor GetColor() const;` — Get the color of this filter
- L50 _public prototype_ `void BuildBackendFilter(FARFilter& OutFilter);` — Add this filter to the input BackendFilter
- L53 _public prototype_ `FText GetName() const;` — Get the logical name of this filter class
- L56 _public prototype_ `FString GetFilterName() const;` — Get the display name of this filter class
- L61 _public prototype_ `FTopLevelAssetPath GetClassPathName() const;` — Returns class path name as a package + class FName pair
- L66 _private member_ `TWeakObjectPtr<UClass> Class;` — The Class the filter is associated with (if it does not have an AssetTypeAction)
- L69 _private member_ `FString FilterName;` — The Filter name
- L72 _private member_ `FText FilterDisplayName;` — The Filter display name
- L75 _private member_ `FTopLevelAssetPath ClassPathName;` — The class path of the class associated with the filter
- L78 _private member_ `FARFilter Filter;` — The actual asset registry filter.
- L81 _private member_ `TArray<TSharedPtr<FFilterCategory>> Categories;` — The Categories the filter will show up under
- L84 _private member_ `FLinearColor Color;` — The Color of the filter (if it does not have an AssetTypeAction to get the color from)
- L87 _private member_ `TWeakObjectPtr<UAssetDefinition> AssetDefinitionPtr;` — An optional AssetDefinition to get information about the filter class

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API EDITORWIDGETS_API`

### `Source/Editor/EditorWidgets/Public/Filters/FilterBarConfig.h` (Public)


#### struct `FCustomTextFilterState`  
`struct FCustomTextFilterState`  
_L24-41_
- reflection: `USTRUCT()`
- L32 _public member_ `bool bIsChecked = false;` — `UPROPERTY()` — Whether the custom filter is checked, i.e visible in the filter bar
- L36 _public member_ `bool bIsActive = false;` — `UPROPERTY()` — Whether the custom filter is active, i.e visible and enabled in the filter bar
- L40 _public member_ `FCustomTextFilterData FilterData;` — `UPROPERTY()` — The data inside the custom text filter

#### struct `FFilterBarSettings`  
`struct FFilterBarSettings`  
_L44-82_
- reflection: `USTRUCT()`
- L52 _public member_ `TMap<FString, bool> CustomFilters;` — `UPROPERTY()` — Map of currently visible custom filters, along with their enabled state
- L56 _public member_ `TMap<FString, bool> TypeFilters;` — `UPROPERTY()` — Map of currently visible asset type filters, along with their enabled state
- L60 _public member_ `TArray<FCustomTextFilterState> CustomTextFilters;` — `UPROPERTY()` — Array of custom text filters the user has created
- L63 _public member_ `bool bIsLayoutSaved = false;` — `UPROPERTY()`
- L66 _public member_ `EFilterBarLayout FilterBarLayout = EFilterBarLayout::Horizontal;` — `UPROPERTY()`
- L70 _public member_ `bool bFilterRecursively = true;` — `UPROPERTY()` — Whether to filter paths recursively. Also @see UContentBrowserSettings::FilterRecursively
- L74 _public member_ `bool bSortFiltersAlphabetically = true;` — `UPROPERTY()` — Whether filters are sorted and displayed alphabetically or in the order they were added
- L76 _public function_ `void Empty()`

#### class `UFilterBarConfig`  
`class UFilterBarConfig : public UEditorConfigBase`  
_L85-100_
- reflection: `UCLASS(MinimalAPI, EditorConfig="FilterBar")`
- inherits: `UEditorConfigBase`
- L91 _public prototype_ `static void Initialize();`
- L92 _public function_ `static UFilterBarConfig* Get()`
- L95 _public member_ `TMap<FName, FFilterBarSettings> FilterBars;` — `UPROPERTY(meta=(EditorConfig))`
- L99 _private member_ `static TObjectPtr<UFilterBarConfig> Instance;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API EDITORWIDGETS_API`

### `Source/Editor/EditorWidgets/Public/Filters/SAssetFilterBar.h` (Public)


#### struct `UE::Editor::Widgets::FFilterCategoryMenu`  
`struct FFilterCategoryMenu`  
_L80-90_
- desc: A local struct to describe a category in the filter menu
- L83 _public member_ `TArray<TSharedPtr<FCustomClassFilterData>> Classes;` — The Classes that belong to this category
- L86 _public member_ `FName SectionExtensionHook;` — Menu section
- L87 _public member_ `FText SectionHeading;`
- L89 _public prototype_ `FFilterCategoryMenu(const FName& InSectionExtensionHook, const FText& InSectionHeading);`

#### class `UAssetFilterBarContext`  
`class UAssetFilterBarContext : public UObject`  
_L100-109_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: ToolMenuContext that is used to create the Add Filter Menu
- L105 _public member_ `TSharedPtr<FFilterCategory> MenuExpansion;`
- L106 _public member_ `FOnPopulateAddAssetFilterMenu PopulateFilterMenu;`
- L107 _public member_ `FOnFilterAssetType OnFilterAssetType;`
- L108 _public member_ `FOnExtendAddFilterMenu OnExtendAddFilterMenu;`

#### class `FFilterBarBase`  
`class FFilterBarBase`  
_L114-134_
- desc: A non-templated base class for SAssetFilterBar, where functionality that does not depend on the type of item being filtered lives
- L119 _protected prototype_ `FFilterBarSettings* GetMutableConfig();` — Get a mutable version of this filter bar's config
- L122 _protected prototype_ `const FFilterBarSettings* GetConstConfig() const;` — Get a const version of this filter bar's config
- L125 _protected prototype_ `void SaveConfig();` — Save this filte bar's data to the config file
- L128 _protected prototype_ `void InitializeConfig();` — Initialize and load this filter bar's config
- L133 _protected member_ `FName FilterBarIdentifier;` — Unique name for this filter bar

#### class `SAssetFilterBar`  
`template<typename FilterType> class SAssetFilterBar : public SBasicFilterBar<FilterType>, public FFilterBarBase`  
_L171-1317_
- inherits: `SBasicFilterBar<FilterType>,FFilterBarBase`
- desc: An Asset Filter Bar widget, which can be used to filter items of type [FilterType] given a list of custom filters along with built in support for AssetType filters @see SFilterBar in EditorWidgets, which is a simplified version of this widget for most use cases which is probably what you want to use @see SBasicFilterBar in ToolWidgets if you want a simple FilterBar without AssetType Filters (usable in non editor builds) @see SFilterList in ContentBrowser for an extremely complex example of how to use this widget, though for most cases you probably want to use SFilterBar NOTE: The filter functions create copies, so you want to use SAssetFilterBar<TSharedPtr<ItemType>> etc instead of SAssetFilterBar<ItemType> when possible NOTE: You will need to also add "ToolWidgets" as a dependency to your module to use this widget Sample Usage: SAssignNew(MyFilterBar, SAssetFilterBar<FText>) .OnFilterChanged() // A delegate for when the list of filters changes .CustomFilters() // An array of filters available to this FilterBar (@see FGenericFilter to create simple delegate based filters) Use the GetAllActiveFilters() and GetCombinedBackendFilter() functions to get all the custom and asset filters respectively NOTE: GetCombinedBackendFilter returns an FARFilter, and it is on the user of this widget to compile it/use it to filter their items. If you want more straightforward filtering, look at SFilterBar which streamlines this Use MakeAddFilterButton() to make the button that summons the dropd
- L175 _public typedef_ `using FOnFilterChanged = typename SBasicFilterBar<FilterType>::FOnFilterChanged;`
- L176 _public typedef_ `using FCreateTextFilter = typename SBasicFilterBar<FilterType>::FCreateTextFilter;`
- L178 _public function_ `SLATE_BEGIN_ARGS( SAssetFilterBar<FilterType> ) : _FilterMenuName(FName("FilterBar.FilterMenu")) , _UseDefaultAssetFilters(true) , _FilterBarLayout(EFilterBarLayout::Horizontal) , _CanChangeOrientation(false) , _FilterPillStyle(EFilterPillStyle::Default) , _DefaultMenuExpansionCategory(EAssetCategoryPaths::Basic) , _bUseSectionsForCustomCategories(false)`
- L191 _public prototype_ `SLATE_EVENT( FOnFilterChanged, OnFilterChanged ) SLATE_EVENT( FOnExtendAddFilterMenu, OnExtendAddFilterMenu ) SLATE_ARGUMENT( TArray<TSharedRef<FFilterBase<FilterType>>>, CustomFilters) SLATE_ARGUMENT( TArray<TSharedRef<FCustomClassFilterData>>, CustomClassFilters) SLATE_ARGUMENT(FCreateTextFilter, CreateTextFilter) SLATE_ARGUMENT(TSharedPtr<SFilterSearchBox>, FilterSearchBox) SLATE_ARGUMENT(FName, FilterMenuName) SLATE_ARGUMENT(FName, FilterBarIdentifier) SLATE_ARGUMENT(bool, UseDefaultAssetFilters) SLATE_EVENT(SBasicFilterBar<FilterType>::FOnFilterBarLayoutChanging, OnFilterBarLayoutChanging) SLATE_ARGUMENT(EFilterBarLayout, FilterBarLayout) SLATE_ARGUMENT(bool, CanChangeOrientation)` — Delegate for when filters have changed
- L248 _public function_ `void Construct( const FArguments& InArgs )` — Constructs this widget with InArgs
- L285 _public function_ `virtual void SaveSettings()`
- L301 _public function_ `virtual void LoadSettings()`
- L325 _protected function_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L347 _protected function_ `void SaveCustomTextFilters(FFilterBarSettings* FilterBarConfig)` — Save all the custom class filters (created by the user) into the specified config
- L375 _protected function_ `virtual void SaveSettingsInternal(FFilterBarSettings* InSettingsToSave)`
- L386 _protected function_ `void SaveFilters(FFilterBarSettings* FilterBarConfig)` — Save all the custom filters (created programmatically) into the specified config
- L417 _protected function_ `void LoadCustomTextFilters(const FFilterBarSettings* FilterBarConfig)` — Load all the custom class filters (created by the user) from the specified config
- L448 _protected function_ `void LoadFilters(const FFilterBarSettings* FilterBarConfig)` — Load all the custom filters (created programmatically) from the specified config
- L516 _protected typedef_ `typedef typename SBasicFilterBar<FilterType>::SFilter SFilter;`
- L655 _public function_ `FARFilter GetCombinedBackendFilter() const` — Use this function to get an FARFilter that represents all the AssetType filters that are currently active
- L699 _public function_ `bool DoesAssetTypeFilterExist(const FTopLevelAssetPath& InClassPath)` — Check if there is a filter associated with the given class represented by FTopLevelAssetPath in the filter bar @param	InClassPath		The Class the filter is associated with
- L717 _public function_ `void SetAssetTypeFilterCheckState(const FTopLevelAssetPath& InClassPath, ECheckBoxState InCheckState, bool bEnableFilter = true)` — Set the check box state of the specified filter (in the filter drop down) and pin/unpin a filter widget on/from the filter bar. When a filter is pinned (was not already pinned), it is activated if requested and deactivated when unpinned. @param	InClassPath		The Class the filter is associated with (must exist in the widget) @param	InCheckState	The CheckState to apply to the flter @param	bEnableFilter	Whether the filter should be enabled when it is pinned
- L750 _public function_ `ECheckBoxState GetAssetTypeFilterCheckState(const FTopLevelAssetPath& InClassPath) const`
- L766 _public function_ `bool IsAssetTypeFilterActive(const FTopLevelAssetPath& InClassPath) const` — Returns true if the specified filter is both checked (pinned on the filter bar) and active (contributing to filter the result). @param	InClassPath		The Class the filter is associated with
- L784 _public function_ `void ToggleAssetTypeFilterEnabled(const FTopLevelAssetPath& InClassPath, bool bEnable)` — If a filter with the input class name is Checked (i.e visible in the bar), enable/disable it @see SetFilterCheckState to set the check state and GetFilterCheckState to check if it is checked @param	InClassPath		The Class the filter is associated with @param	bEnable			Whether to enable or disable the filter
- L797 _public function_ `virtual void RemoveAllFilters() override` — Remove all filters from the filter bar, while disabling any active ones
- L804 _public function_ `void FilterByType(TSharedPtr<FCustomClassFilterData> CustomClassFilterData)` — Handler for when filter by type is selected
- L821 _public function_ `void FilterByTypeCategory(TSharedPtr<FFilterCategory> TypeCategory, TArray<TSharedPtr<FCustomClassFilterData>> Classes)` — Handler for when filter by type category is selected
- L848 _public function_ `void SetActiveFilters(TConstArrayView<FTopLevelAssetPath> InFilters)` — Set the active asset filters for this filter list
- L860 _protected function_ `virtual void RemoveAllButThis(const TSharedRef<SFilter>& FilterToKeep) override` — AssetFilter specific override to SBasicFilterBar::RemoveAllButThis
- L884 _protected function_ `TSharedRef<SFilter> AddAssetFilterToBar(const TSharedPtr<FCustomClassFilterData>& CustomClassFilter)` — Add an AssetFilter to the toolbar, making it "Active" but not enabled
- L907 _protected function_ `virtual void RemoveFilter(const TSharedRef<SFilter>& FilterToRemove) override` — Remove a filter from the filter bar
- L915 _protected function_ `void RemoveAssetFilter(const TSharedPtr<FCustomClassFilterData>& CustomClassData, bool ExecuteOnFilterChanged = true)` — Handler for when the remove filter button was clicked on a filter
- L945 _protected function_ `void CreateAssetTypeActionFilters()` — Create the default set of IAssetTypeActions Filters provided with the widget if requested
- L1038 _protected function_ `void CreateFiltersMenuCategory(FToolMenuSection& Section, const TArray<TSharedPtr<FCustomClassFilterData>> CustomClassFilterDatas) const` — Handler for when the add filter menu is populated by a category
- L1059 _protected function_ `void CreateFiltersMenuCategory(UToolMenu* InMenu, const TArray<TSharedPtr<FCustomClassFilterData>> CustomClassFilterDatas) const`
- L1067 _protected function_ `virtual UAssetFilterBarContext* CreateAssetFilterBarContext()` — Override this if you want to change aspects on the add filter menu. You can opt to only override the OnFilterAssetType member to exclude assets, or choose to override the entire populate callback
- L1082 _protected function_ `virtual TSharedRef<SWidget> MakeAddFilterMenu() override final` — Handler for when the add filter button was clicked
- L1105 _protected function_ `virtual void PopulateAddFilterMenu(UToolMenu* Menu, TSharedPtr<FFilterCategory> MenuExpansion, FOnFilterAssetType OnFilterAssetType)` — Handler to Populate the Add Filter Menu. Use OnFilterAssetType in Subclasses to add classes to the exclusion list
- L1187 _protected function_ `bool IsClassTypeInUse(TSharedPtr<FCustomClassFilterData> Class) const` — Handler to determine the "checked" state of class filter in the filter dropdown
- L1201 _protected function_ `ECheckBoxState IsTypeCategoryChecked(TSharedPtr<FFilterCategory> TypeCategory, TArray<TSharedPtr<FCustomClassFilterData>> Classes) const` — Handler to determine the "checked" state of an type category in the filter dropdown
- L1234 _protected function_ `bool IsTypeCategoryInUse(TSharedPtr<FFilterCategory> TypeCategory, TArray<TSharedPtr<FCustomClassFilterData>> Classes) const` — Function to check if a given type category is in use
- L1247 _protected function_ `void OnCopyFilters() const`
- L1257 _protected function_ `void OnPasteFilters()`
- L1270 _protected function_ `bool CanPasteFilters() const`
- L1287 _protected member_ `TWeakPtr<FUICommandList> CommandListWeak;` — The command list we bind to
- L1290 _protected member_ `TArray< TSharedRef<SAssetFilter> > AssetFilters;` — A copy of all AssetFilters in this->Filters for convenient access
- L1293 _protected member_ `TArray<TSharedRef<FCustomClassFilterData>> CustomClassFilters;` — List of custom Class Filters that will be shown in the filter bar
- L1296 _protected member_ `TArray<TSharedRef<FCustomClassFilterData>> UserCustomClassFilters;` — Copy of Custom Class Filters that were provided by the user, and not autopopulated from AssetTypeActions
- L1298 _protected member_ `FName FilterMenuName;`
- L1300 _protected member_ `TMap<FName, TSharedPtr<FFilterCategory>> AssetFilterCategories;`
- L1303 _protected member_ `bool bUseDefaultAssetFilters = false;` — Whether the filter bar provides the default Asset Filters
- L1306 _protected member_ `EAssetClassAction AssetClassAction = EAssetClassAction::ViewAsset;` — The AssetClassAction used to get the permission list from the Asset Tools Module
- L1310 _protected member_ `TMap<FString, bool> UnknownTypeFilters;` — A map of any type filters we encounter while calling LoadSettings(), but don't have in this instance of the filter bar. These are stored so we can save these when calling SaveSettings() so that they are not lost
- L1314 _private member_ `TOptional<FAssetCategoryPath> DefaultMenuExpansionCategory;` — The filter menu category to expand.
- L1316 _private member_ `FDelegateHandle AssetRegistryVersionChangeHandle;`
- L1320 _function_ `template <typename FilterType> SAssetFilterBar<FilterType>::~SAssetFilterBar()`

#### class `SAssetFilterBar::SAssetFilter`  
`class SAssetFilter : public SFilter`  
_L519-650_
- inherits: `SFilter`
- desc: A subclass of SFilter in SBasicFilterBar to add functionality for Asset Filters
- L521 _private typedef_ `using FOnRequestRemove = typename SBasicFilterBar<FilterType>::SFilter::FOnRequestRemove;`
- L522 _private typedef_ `using FOnRequestEnableOnly = typename SBasicFilterBar<FilterType>::SFilter::FOnRequestEnableOnly;`
- L523 _private typedef_ `using FOnRequestEnableAll = typename SBasicFilterBar<FilterType>::SFilter::FOnRequestEnableAll;`
- L524 _private typedef_ `using FOnRequestDisableAll = typename SBasicFilterBar<FilterType>::SFilter::FOnRequestDisableAll;`
- L525 _private typedef_ `using FOnRequestRemoveAll = typename SBasicFilterBar<FilterType>::SFilter::FOnRequestRemoveAll;`
- L526 _private typedef_ `using FOnRequestRemoveAllButThis = typename SBasicFilterBar<FilterType>::SFilter::FOnRequestRemoveAllButThis;`
- L528 _private function_ `SLATE_BEGIN_ARGS( SAssetFilter )`
- L531 _private function_ `SLATE_ARGUMENT( TSharedPtr<FCustomClassFilterData>, CustomClassFilter )` — The Custom Class Data that is associated with this filter
- L598 _public function_ `FARFilter GetBackendFilter() const` — Returns this widgets contribution to the combined filter
- L611 _public function_ `const TSharedPtr<FCustomClassFilterData>& GetCustomClassFilterData() const` — Gets the asset type actions associated with this filter
- L616 _public function_ `void SetCustomClassFilterData(const TSharedRef<FCustomClassFilterData>& InCustomClassFilterData)`
- L622 _public function_ `virtual FText GetFilterDisplayName() const override` — Returns the display name for this filter
- L635 _public function_ `virtual FString GetFilterName() const override`
- L649 _protected member_ `TSharedPtr<FCustomClassFilterData> CustomClassFilter;` — The asset type actions that are associated with this filter

#### Free symbols / members of external scopes

- L62 _macro_ `#define UE_API EDITORWIDGETS_API`
- L67 _macro_ `#define LOCTEXT_NAMESPACE "FilterBar"`
- L72 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterAssetType, UClass* );` — Delegate that subclasses can use to specify classes to not include in this filter Returning false for a class will prevent it from showing up in the add filter dropdown
- L72 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterAssetType, UClass* );` — Delegate that subclasses can use to specify classes to not include in this filter Returning false for a class will prevent it from showing up in the add filter dropdown
- L75 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnPopulateAddAssetFilterMenu, UToolMenu*, TSharedPtr<FFilterCategory>, FOnFilterAssetType) namespace UE::Editor::Widgets { struct FFilterCategoryMenu { TArray<TSharedPtr<FCustomClassFilterData>> Classes; FName SectionExtensionHook; FText SectionHeading; FFilterCategoryMenu(const FName& InSectionExtensionHook, const FText& InSectionHeading); }; TMap<TSharedPtr<FFilterCategory>, FFilterCategoryMenu> BuildCategoryToMenuMap( TMap<FName, TSharedPtr<FFilterCategory>>& InAssetFilterCategories, TConstArrayView<TSharedRef<FCustomClassFilterData>> InCustomClassFilters, const FOnFilterAssetType& InOnFilterAssetType); } UCLASS(MinimalAPI) class UAssetFilterBarContext : public UObject { GENERATED_BODY() public: TSharedPtr<FFilterCategory> MenuExpansion; FOnPopulateAddAssetFilterMenu PopulateFilterMenu; FOnFilterAssetType OnFilterAssetType; FOnExtendAddFilterMenu OnExtendAddFilterMenu; };` — Delegate used by SAssetFilterBar to populate the add filter menu
- L77 _namespace_ `namespace UE`
- L77 _namespace_ `namespace Editor` (scope `UE`)
- L77 _namespace_ `namespace Widgets` (scope `UE::Editor`)
- L92 _prototype_ `TMap<TSharedPtr<FFilterCategory>, FFilterCategoryMenu> BuildCategoryToMenuMap( TMap<FName, TSharedPtr<FFilterCategory>>& InAssetFilterCategories, TConstArrayView<TSharedRef<FCustomClassFilterData>> InCustomClassFilters, const FOnFilterAssetType& InOnFilterAssetType);` (scope `UE::Editor::Widgets`)
- L282 _function_ `AssetRegistryVersionChangeHandle = UAssetDefinitionRegistry::Get()->OnAssetDefinitionRegistryVersionChange().AddLambda([this](UAssetDefinitionRegistry*) { CreateAssetTypeActionFilters(); });` (scope `SAssetFilterBar::Construct`)
- L911 _function_ `AssetFilters.RemoveAll([&FilterToRemove](TSharedRef<SAssetFilter>& AssetFilter) { return AssetFilter == FilterToRemove; });` (scope `SAssetFilterBar::RemoveFilter`)
- L1013 _function_ `` (scope `SAssetFilterBar::CreateAssetTypeActionFilters`)
- L1091 _function_ `` (scope `SAssetFilterBar::MakeAddFilterMenu`)
- L1151 _function_ `CategoryToMenuMap.KeySort([](const TSharedPtr<FFilterCategory>& A, const TSharedPtr<FFilterCategory>& B) { return A->Title.CompareTo(B->Title) < 0; });` (scope `SAssetFilterBar::PopulateAddFilterMenu`) — Sort by category name so that we add the submenus in alphabetical order
- L1159 _function_ `` (scope `SAssetFilterBar::PopulateAddFilterMenu`)

### `Source/Editor/EditorWidgets/Public/Filters/SFilterBar.h` (Public)


#### class `SFilterBar`  
`template<typename FilterType> class SFilterBar : public SAssetFilterBar<FilterType>`  
_L37-167_
- inherits: `SAssetFilterBar<FilterType>`
- desc: A Filter Bar widget, which can be used to filter items of type [FilterType] given a list of custom filters along with built in support for Asset Type filters @see SBasicFilterBar if you don't want Asset Type filters, or if you want a filter bar usable in non-editor situations NOTE: You will need to also add "ToolWidgets" as a dependency to your module to use this widget NOTE: The filter functions create copies, so you want to use SFilterBar<TSharedPtr<ItemType>> etc instead of SFilterBar<ItemType> when possible NOTE: The user must specify one of the following: a) OnConvertItemToAssetData:   A conversion function to convert FilterType to an FAssetData. Specifying this will filter the asset type through the AssetRegistry, which is potentially more thorough and fast b) OnCompareItemWithClassName: A comparison function to check if an Item (FilterType) is the same as an AssetType (represented by an FName). This allows to user to directly text compare with Class Names (UObjectBase::GetFName), which is easier but potentially slower Sample Usage: SAssignNew(MyFilterBar, SFilterBar<FText>) .OnFilterChanged() // A delegate for when the list of filters changes .CustomFilters() // An array of filters available to this FilterBar (@see FGenericFilter to create simple delegate based filters) .OnConvertItemToAssetData() // Conversion Function as mentioned above Use the GetAllActiveFilters() function to get the FilterCollection of Active Filters in this FilterBar, that can be used to filter y
- L40 _public typedef_ `using FOnFilterChanged = typename SBasicFilterBar<FilterType>::FOnFilterChanged;`
- L41 _public typedef_ `using FConvertItemToAssetData = typename FAssetFilter<FilterType>::FConvertItemToAssetData;`
- L42 _public typedef_ `using FCompareItemWithClassNames = typename FAssetFilter<FilterType>::FCompareItemWithClassNames;`
- L43 _public typedef_ `using FCreateTextFilter = typename SBasicFilterBar<FilterType>::FCreateTextFilter;`
- L44 _public typedef_ `using SFilter = typename SBasicFilterBar<FilterType>::SFilter;`
- L46 _public function_ `SLATE_BEGIN_ARGS( SFilterBar<FilterType> ) : _FilterBarIdentifier(NAME_None) , _UseDefaultAssetFilters(true) , _FilterBarLayout(EFilterBarLayout::Horizontal) , _CanChangeOrientation(false) , _FilterPillStyle(EFilterPillStyle::Default) , _DefaultMenuExpansionCategory(EAssetCategoryPaths::Basic)`
- L58 _public prototype_ `SLATE_EVENT( FOnFilterChanged, OnFilterChanged ) SLATE_EVENT( FConvertItemToAssetData, OnConvertItemToAssetData ) SLATE_EVENT( FCompareItemWithClassNames, OnCompareItemWithClassNames ) SLATE_ARGUMENT( TArray<TSharedRef<FFilterBase<FilterType>>>, CustomFilters) SLATE_ARGUMENT(FName, FilterBarIdentifier) SLATE_EVENT( FOnExtendAddFilterMenu, OnExtendAddFilterMenu ) SLATE_ARGUMENT( TArray<TSharedRef<FCustomClassFilterData>>, CustomClassFilters) SLATE_ARGUMENT(bool, UseDefaultAssetFilters) SLATE_ARGUMENT(FCreateTextFilter, CreateTextFilter) SLATE_ARGUMENT(TSharedPtr<SFilterSearchBox>, FilterSearchBox) SLATE_ARGUMENT(EFilterBarLayout, FilterBarLayout) SLATE_ARGUMENT(bool, CanChangeOrientation)` — Delegate for when filters have changed
- L104 _public function_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs )`
- L148 _public function_ `virtual TSharedPtr< TFilterCollection<FilterType> > GetAllActiveFilters() override` — Use this function to get all currently active filters (to filter your items) NOTE: Must be called every time the filters change (OnFilterChanged) to make sure you get the correct combined filter
- L157 _private function_ `void UpdateAssetFilter()`
- L166 _private member_ `TSharedPtr<FAssetFilter<FilterType>> AssetFilter;` — The invisible filter used to conduct Asset Type filtering

### `Source/Editor/EditorWidgets/Public/IObjectNameEditSink.h` (Public)


#### class `UE::EditorWidgets::IObjectNameEditSink`  
`class IObjectNameEditSink`  
_L11-53_
- desc: ObjectNameEditSink provides an interface for the in-editor object name
- L15 _public prototype_ `virtual ~IObjectNameEditSink() = default;` — Virtual destructor
- L18 _public prototype_ `virtual UClass* GetSupportedClass() const = 0;` — Checks to see if the specified object is handled by this type.
- L21 _public prototype_ `virtual FText GetObjectDisplayName(UObject* Object) const = 0;` — Returns the display name for that object.
- L24 _public function_ `virtual bool IsObjectDisplayNameReadOnly(UObject* Object) const` — Whether or not the name can be edited
- L33 _public function_ `virtual bool SetObjectDisplayName(UObject* Object, FString DisplayName)` — Attempt to rename the object. Will fail if IsObjectDisplayNameReadOnly returns true. @return Whether or not the display name was successfully set
- L39 _public prototype_ `virtual FText GetObjectNameTooltip(UObject* Object) const = 0;` — Returns the tooltip text for that object
- L42 _public function_ `virtual bool ObjectDisplayNameHasSuffix(const UObject* Object) const` — Whether or not the name has a suffix
- L48 _public function_ `virtual FText GetObjectDisplayNameSuffix(const UObject* Object) const` — Returns the displayed suffix for that object.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace EditorWidgets` (scope `UE`)

### `Source/Editor/EditorWidgets/Public/ITransportControl.h` (Public)


#### enum `EPlaybackMode::Type`  
`enum Type`  
_L13-18_
- L15 _public enumerator_ `Stopped`
- L16 _public enumerator_ `PlayingForward`
- L17 _public enumerator_ `PlayingReverse`

#### enum `ETransportControlWidgetType`  
`enum class ETransportControlWidgetType : int32`  
_L28-39_
- L30 _public enumerator_ `BackwardEnd`
- L31 _public enumerator_ `BackwardStep`
- L32 _public enumerator_ `BackwardPlay`
- L33 _public enumerator_ `Record`
- L34 _public enumerator_ `ForwardPlay`
- L35 _public enumerator_ `ForwardStep`
- L36 _public enumerator_ `ForwardEnd`
- L37 _public enumerator_ `Loop`
- L38 _public enumerator_ `Custom`

#### struct `FTransportControlWidget`  
`struct FTransportControlWidget`  
_L44-60_
- desc: Descriptor for a transport control widget
- L46 _public function_ `FTransportControlWidget(ETransportControlWidgetType InWidgetType) : WidgetType(InWidgetType)`
- L50 _public function_ `FTransportControlWidget(FOnMakeTransportWidget InMakeCustomWidgetDelegate) : WidgetType(ETransportControlWidgetType::Custom) , MakeCustomWidgetDelegate(InMakeCustomWidgetDelegate)`
- L56 _public member_ `ETransportControlWidgetType WidgetType;` — Basic widget type
- L59 _public member_ `FOnMakeTransportWidget MakeCustomWidgetDelegate;` — Delegate used for making custom widgets

#### struct `FTransportControlArgs`  
`struct FTransportControlArgs`  
_L62-101_
- L64 _public function_ `FTransportControlArgs() : OnForwardPlay() , OnRecord() , OnBackwardPlay() , OnForwardStep() , OnBackwardStep() , OnForwardEnd() , OnBackwardEnd() , OnToggleLooping() , OnGetLooping() , OnGetPlaybackMode() , OnTickPlayback() , OnGetRecording() , bAreButtonsFocusable(true) , OnGetRecordButtonVisibility()`
- L81 _public member_ `FOnClicked OnForwardPlay;`
- L82 _public member_ `FOnClicked OnRecord;`
- L83 _public member_ `FOnClicked OnBackwardPlay;`
- L84 _public member_ `FOnClicked OnForwardStep;`
- L85 _public member_ `FOnClicked OnBackwardStep;`
- L86 _public member_ `FOnClicked OnForwardEnd;`
- L87 _public member_ `FOnClicked OnBackwardEnd;`
- L88 _public member_ `FOnClicked OnToggleLooping;`
- L89 _public member_ `FOnGetLooping OnGetLooping;`
- L90 _public member_ `FOnGetPlaybackMode OnGetPlaybackMode;`
- L91 _public member_ `FOnTickPlayback OnTickPlayback;`
- L92 _public member_ `FOnGetRecording OnGetRecording;`
- L93 _public member_ `bool bAreButtonsFocusable;`
- L94 _public member_ `FOnGetRecordButtonVisibility OnGetRecordButtonVisibility;`
- L100 _public member_ `TArray<FTransportControlWidget> WidgetsToCreate;` — Array of custom widgets to create - if this array is used the default widget ordering will be ignored in favor of this set of widgets

#### class `ITransportControl`  
`class ITransportControl : public SCompoundWidget`  
_L106-109_
- inherits: `SCompoundWidget`
- desc: Base class for a widget that allows transport control

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace EPlaybackMode`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnGetLooping) DECLARE_DELEGATE_RetVal(bool, FOnGetRecording) DECLARE_DELEGATE_RetVal(EPlaybackMode::Type, FOnGetPlaybackMode) DECLARE_DELEGATE_TwoParams(FOnTickPlayback, double , float ) DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnMakeTransportWidget) DECLARE_DELEGATE_RetVal(EVisibility, FOnGetRecordButtonVisibility) enum class ETransportControlWidgetType : int32 { BackwardEnd, BackwardStep, BackwardPlay, Record, ForwardPlay, ForwardStep, ForwardEnd, Loop, Custom };`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnGetRecording) DECLARE_DELEGATE_RetVal(EPlaybackMode::Type, FOnGetPlaybackMode) DECLARE_DELEGATE_TwoParams(FOnTickPlayback, double , float ) DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnMakeTransportWidget) DECLARE_DELEGATE_RetVal(EVisibility, FOnGetRecordButtonVisibility) enum class ETransportControlWidgetType : int32 { BackwardEnd, BackwardStep, BackwardPlay, Record, ForwardPlay, ForwardStep, ForwardEnd, Loop, Custom };`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(EPlaybackMode::Type, FOnGetPlaybackMode) DECLARE_DELEGATE_TwoParams(FOnTickPlayback, double , float ) DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnMakeTransportWidget) DECLARE_DELEGATE_RetVal(EVisibility, FOnGetRecordButtonVisibility) enum class ETransportControlWidgetType : int32 { BackwardEnd, BackwardStep, BackwardPlay, Record, ForwardPlay, ForwardStep, ForwardEnd, Loop, Custom };`
- L24 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnTickPlayback, double , float ) DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnMakeTransportWidget) DECLARE_DELEGATE_RetVal(EVisibility, FOnGetRecordButtonVisibility) enum class ETransportControlWidgetType : int32 { BackwardEnd, BackwardStep, BackwardPlay, Record, ForwardPlay, ForwardStep, ForwardEnd, Loop, Custom };`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FOnMakeTransportWidget) DECLARE_DELEGATE_RetVal(EVisibility, FOnGetRecordButtonVisibility) enum class ETransportControlWidgetType : int32 { BackwardEnd, BackwardStep, BackwardPlay, Record, ForwardPlay, ForwardStep, ForwardEnd, Loop, Custom };`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(EVisibility, FOnGetRecordButtonVisibility) enum class ETransportControlWidgetType : int32 { BackwardEnd, BackwardStep, BackwardPlay, Record, ForwardPlay, ForwardStep, ForwardEnd, Loop, Custom };`
- L41 _prototype_ `ENUM_RANGE_BY_COUNT(ETransportControlWidgetType, ETransportControlWidgetType::Custom);`

### `Source/Editor/EditorWidgets/Public/ObjectNameEditSinkRegistry.h` (Public)


#### class `UE::EditorWidgets::FObjectNameEditSinkRegistry`  
`class FObjectNameEditSinkRegistry`  
_L17-34_
- L20 _public prototype_ `FObjectNameEditSinkRegistry();`
- L23 _public prototype_ `void RegisterObjectNameEditSink(const TSharedRef<IObjectNameEditSink>& NewSink);` — Registers an object name edit sink so it can provide a name editing interface for an object type.
- L26 _public prototype_ `void UnregisterObjectNameEditSink(const TSharedRef<IObjectNameEditSink>& SinkToRemove);` — Unregisters a name edit sink. It will no longer provide a name editing interface for an object type.
- L29 _public prototype_ `TSharedPtr<IObjectNameEditSink> GetObjectNameEditSinkForClass(const UClass* Class) const;` — Gets the appropriate ObjectNameEditSink for the supplied class
- L33 _private member_ `TArray<TSharedRef<IObjectNameEditSink>> ObjectNameEditSinkList;` — The list of all registered ObjectNameEditSinks

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORWIDGETS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace EditorWidgets` (scope `UE`)

### `Source/Editor/EditorWidgets/Public/SAssetDropTarget.h` (Public)


#### class `SAssetDropTarget`  
`class SAssetDropTarget : public SDropTarget`  
_L28-127_
- inherits: `SDropTarget`
- desc: A widget that displays a hover cue and handles dropping assets of allowed types onto this widget
- L32 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnAssetDropped, UObject* );` — Called when a valid asset is dropped
- L35 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnAssetsDropped, const FDragDropEvent&, TArrayView<FAssetData> );` — Called when valid assets are dropped
- L38 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FIsAssetAcceptableForDrop, const UObject* );` — Called when we need to check if an asset type is valid for dropping
- L41 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FAreAssetsAcceptableForDrop, TArrayView<FAssetData> );` — Called when we need to check if an asset type is valid for dropping
- L44 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FIsAssetAcceptableForDropWithReason, const UObject*, FText& );` — Called when we need to check if an asset type is valid for dropping and also will have a reason if it is not
- L47 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FAreAssetsAcceptableForDropWithReason, TArrayView<FAssetData>, FText& );` — Called when we need to check if an asset type is valid for dropping and also will have a reason if it is not
- L49 _public function_ `SLATE_BEGIN_ARGS(SAssetDropTarget) : _bSupportsMultiDrop(false)`
- L53 _public function_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_EVENT( FOnAssetsDropped, OnAssetsDropped ) SLATE_EVENT( FAreAssetsAcceptableForDrop, OnAreAssetsAcceptableForDrop ) SLATE_EVENT( FAreAssetsAcceptableForDropWithReason, OnAreAssetsAcceptableForDropWithReason ) SLATE_ARGUMENT( bool, bSupportsMultiDrop ) SLATE_ATTRIBUTE(bool, bOnlyRecognizeOnDragEnter) FOnAssetsDropped ConvertObjectDropDelegate(const FOnAssetDropped& LegacyDelegate)` — Content to display for the in the drop target
- L77 _public function_ `FAreAssetsAcceptableForDrop ConvertObjectAcceptableDropDelegate(const FIsAssetAcceptableForDrop& LegacyDelegate)`
- L91 _public function_ `FAreAssetsAcceptableForDropWithReason ConvertObjectAcceptableDropWithReasonDelegate(const FIsAssetAcceptableForDropWithReason& LegacyDelegate)`
- L105 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs );`
- L110 _protected prototype_ `FReply OnDropped(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L111 _protected prototype_ `virtual bool OnAllowDrop(TSharedPtr<FDragDropOperation> DragDropOperation) const override;`
- L112 _protected prototype_ `virtual bool OnIsRecognized(TSharedPtr<FDragDropOperation> DragDropOperation) const override;`
- L113 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L116 _private prototype_ `TArray<FAssetData> GetDroppedAssets(TSharedPtr<FDragDropOperation> DragDropOperation, bool& bOutRecognizedEvent) const;`
- L120 _private member_ `FOnAssetsDropped OnAssetsDropped;` — Delegate to call when an asset is dropped
- L122 _private member_ `FAreAssetsAcceptableForDrop OnAreAssetsAcceptableForDrop;` — Delegate to call to check validity of the asset
- L124 _private member_ `FAreAssetsAcceptableForDropWithReason OnAreAssetsAcceptableForDropWithReason;` — Delegate to call to check validity of the asset if you will also provide a reason when returning false
- L126 _private member_ `bool bSupportsMultiDrop;` — Boolean to determine if this drop target can support multiple assets dropped, or only supports a single asset dropped at a time. False by default for legacy behavior.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API EDITORWIDGETS_API`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam( FOnAssetDropped, UObject* );` — Called when a valid asset is dropped
- L35 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnAssetsDropped, const FDragDropEvent&, TArrayView<FAssetData> );` — Called when valid assets are dropped
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FIsAssetAcceptableForDrop, const UObject* );` — Called when we need to check if an asset type is valid for dropping
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FAreAssetsAcceptableForDrop, TArrayView<FAssetData> );` — Called when we need to check if an asset type is valid for dropping
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FIsAssetAcceptableForDropWithReason, const UObject*, FText& );` — Called when we need to check if an asset type is valid for dropping and also will have a reason if it is not
- L47 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FAreAssetsAcceptableForDropWithReason, TArrayView<FAssetData>, FText& );` — Called when we need to check if an asset type is valid for dropping and also will have a reason if it is not
- L68 _function_ `` (scope `SAssetDropTarget::SLATE_DEFAULT_SLOT`)
- L80 _function_ `` (scope `SAssetDropTarget::ConvertObjectAcceptableDropDelegate`)
- L94 _function_ `` (scope `SAssetDropTarget::ConvertObjectAcceptableDropWithReasonDelegate`)

### `Source/Editor/EditorWidgets/Public/SAssetSearchBox.h` (Public)


#### struct `FAssetSearchBoxSuggestion`  
`struct FAssetSearchBoxSuggestion`  
_L40-58_
- desc: External suggestion entry provided to SAssetSearchBox
- L43 _public member_ `FString SuggestionString;` — The raw suggestion string that should be used with the search box
- L46 _public member_ `FText DisplayName;` — The user-facing display name of this suggestion
- L49 _public member_ `FText CategoryName;` — The user-facing category name of this suggestion (if any)
- L51 _public function_ `static FAssetSearchBoxSuggestion MakeSimpleSuggestion(FString InSuggestionString)`

#### class `SAssetSearchBox`  
`class SAssetSearchBox : public SCompoundWidget`  
_L72-244_
- inherits: `SCompoundWidget`
- L75 _public function_ `SLATE_BEGIN_ARGS(SAssetSearchBox) : _SuggestionListPlacement( MenuPlacement_BelowAnchor ) , _OnTextChanged() , _OnTextCommitted() , _InitialText() , _HintText() , _PossibleSuggestions(TArray<FAssetSearchBoxSuggestion>()) , _DelayChangeNotificationsWhileTyping( false ) , _MustMatchPossibleSuggestions( false ) , _ShowSearchHistory(false) , _SuggestionListHeight(250.f)`
- L89 _public prototype_ `SLATE_ARGUMENT( EMenuPlacement, SuggestionListPlacement ) SLATE_EVENT( FOnTextChanged, OnTextChanged ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_ATTRIBUTE( FText, InitialText ) SLATE_ATTRIBUTE( FText, HintText ) SLATE_ATTRIBUTE( TArray<FAssetSearchBoxSuggestion>, PossibleSuggestions ) SLATE_ATTRIBUTE( bool, DelayChangeNotificationsWhileTyping ) SLATE_ATTRIBUTE( bool, MustMatchPossibleSuggestions ) SLATE_EVENT( FOnAssetSearchBoxSuggestionFilter, OnAssetSearchBoxSuggestionFilter ) SLATE_EVENT( FOnAssetSearchBoxSuggestionChosen, OnAssetSearchBoxSuggestionChosen ) SLATE_EVENT( FOnKeyDown, OnKeyDownHandler ) SLATE_ATTRIBUTE(bool, ShowSearchHistory) SLATE_EVENT(SFilterSearchBox::FOnSaveSearchClicked, OnSaveSearchClicked) SLATE_ARGUMENT(float, SuggestionListHeight)` — Where to place the suggestion list
- L144 _public prototype_ `void SetText(const TAttribute< FText >& InNewText);` — Sets the text string currently being edited
- L147 _public prototype_ `FText GetText() const;` — Get the text string currently being edited
- L150 _public prototype_ `void SetError( const FText& InError );` — Set or clear the current error reporting information for this search box
- L151 _public prototype_ `void SetError( const FString& InError );`
- L154 _public prototype_ `void SetOnSaveSearchHandler(SFilterSearchBox::FOnSaveSearchClicked InOnSaveSearchHandler);` — Show a + button next to the current search and set the handler for when that is clicked
- L157 _public prototype_ `virtual FReply OnPreviewKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget implementation
- L158 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L159 _public prototype_ `virtual bool HasKeyboardFocus() const override;`
- L160 _public prototype_ `virtual FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent ) override;`
- L171 _private prototype_ `FReply HandleKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — First chance handler for key down events to the editable text widget
- L174 _private prototype_ `void HandleTextChanged(const FText& NewText);` — Handler for when text in the editable text box changed
- L177 _private prototype_ `void HandleTextCommitted(const FText& NewText, ETextCommit::Type CommitType);` — Handler for when text in the editable text box changed
- L180 _private prototype_ `void OnSelectionChanged( TSharedPtr<FSuggestionListEntry> NewValue, ESelectInfo::Type SelectInfo );` — Called by SListView when the selection changes in the suggestion list
- L183 _private prototype_ `TSharedRef<ITableRow> MakeSuggestionListItemWidget(TSharedPtr<FSuggestionListEntry> Suggestion, const TSharedRef<STableViewBase>& OwnerTable);` — Makes the widget for a suggestion message in the list view
- L186 _private prototype_ `FText GetHighlightText() const;` — Gets the text to highlight in the suggestion list
- L189 _private prototype_ `void UpdateSuggestionList();` — Updates and shows or hides the suggestion list
- L192 _private prototype_ `void FocusEditBox();` — Sets the focus to the InputText box
- L195 _private prototype_ `TSharedPtr<FSuggestionListEntry> GetSelectedSuggestion() const;` — Returns the currently selected suggestion
- L198 _private prototype_ `static void DefaultSuggestionFilterImpl(const FText& SearchText, TArray<FAssetSearchBoxSuggestion>& PossibleSuggestions, FText& SuggestionHighlightText);` — Default implementation of OnAssetSearchBoxSuggestionFilter, if no external implementation is provided
- L201 _private prototype_ `static FText DefaultSuggestionChosenImpl(const FText& SearchText, const FString& Suggestion);` — Default implementation of OnAssetSearchBoxSuggestionChosen, if no external implementation is provided
- L204 _private prototype_ `FOptionalSize GetSuggestionListWidth() const;` — Returns the width for the suggestion list
- L207 _private member_ `TSharedPtr< SFilterSearchBox > InputText;` — The editable text field
- L210 _private member_ `FText PreCommittedText;` — The the state of the text prior to being committed
- L213 _private member_ `FText SuggestionHighlightText;` — The highlight text to use for the suggestions list
- L216 _private member_ `TSharedPtr< SMenuAnchor > SuggestionBox;` — Auto completion elements
- L219 _private member_ `TArray< TSharedPtr<FSuggestionListEntry> > Suggestions;` — All suggestions stored in this widget for the list view
- L222 _private member_ `TSharedPtr< SListView< TSharedPtr<FSuggestionListEntry> > > SuggestionListView;` — The list view for showing all suggestions
- L225 _private member_ `FOnAssetSearchBoxSuggestionFilter OnAssetSearchBoxSuggestionFilter;` — Delegate to filter the given suggestion list, to allow custom filtering behavior
- L228 _private member_ `FOnAssetSearchBoxSuggestionChosen OnAssetSearchBoxSuggestionChosen;` — Delegate when a suggestion entry is chosen during an asset search, to allow custom compositing behavior of the suggestion into the search text
- L231 _private member_ `FOnTextChanged OnTextChanged;` — Delegate for when text is changed in the edit box
- L234 _private member_ `FOnTextCommitted OnTextCommitted;` — Delegate for when text is changed in the edit box
- L237 _private member_ `FOnKeyDown OnKeyDownHandler;` — Delegate for first chance handling for key down events
- L240 _private member_ `TAttribute< TArray<FAssetSearchBoxSuggestion> > PossibleSuggestions;` — All possible suggestions for the search text
- L243 _private member_ `bool bMustMatchPossibleSuggestions;` — Determines whether or not the committed text should match a suggestion

#### struct `SAssetSearchBox::FSuggestionListEntry`  
`struct FSuggestionListEntry`  
_L163-168_
- L165 _public member_ `FString Suggestion;`
- L166 _public member_ `FText DisplayName;`
- L167 _public member_ `bool bIsHeader = false;`

#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_API EDITORWIDGETS_API`
- L61 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnAssetSearchBoxSuggestionFilter, const FText& , TArray<FAssetSearchBoxSuggestion>& , FText& );` — A delegate for a callback to filter the given suggestion list, to allow custom filtering behavior
- L61 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnAssetSearchBoxSuggestionFilter, const FText& , TArray<FAssetSearchBoxSuggestion>& , FText& );` — A delegate for a callback to filter the given suggestion list, to allow custom filtering behavior
- L64 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnAssetSearchBoxSuggestionChosen, const FText& , const FString& );` — A delegate for a callback when a suggestion entry is chosen during an asset search, to allow custom compositing behavior of the suggestion into the search text
- L64 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnAssetSearchBoxSuggestionChosen, const FText& , const FString& );` — A delegate for a callback when a suggestion entry is chosen during an asset search, to allow custom compositing behavior of the suggestion into the search text

### `Source/Editor/EditorWidgets/Public/SDropTarget.h` (Public)


#### class `SDropTarget`  
`class SDropTarget : public SCompoundWidget`  
_L34-167_
- inherits: `SCompoundWidget`
- desc: A widget that displays a hover cue and handles dropping assets of allowed types onto this widget
- L37 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FVerifyDrag, TSharedPtr<FDragDropOperation>);`
- L38 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDragAction, const FDragDropEvent&);`
- L39 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnDropDeprecated, TSharedPtr<FDragDropOperation>);`
- L41 _public function_ `SLATE_BEGIN_ARGS(SDropTarget) : _ValidColor(FStyleColors::AccentBlue) , _InvalidColor(FStyleColors::Error) , _VerticalImage(FAppStyle::GetBrush("WideDash.Vertical")) , _HorizontalImage(FAppStyle::GetBrush("WideDash.Horizontal")) , _BackgroundImage(FAppStyle::GetBrush("DropTarget.Background")) , _bOnlyRecognizeOnDragEnter(false) , _bUseAllowDropCache(false)`
- L52 _public function_ `FArguments& BackgroundColor(const FLinearColor& InBackgroundColor)` — `UE_DEPRECATED(5.0, "BackgroundColor has been removed. You may alter the background brush to get the same effect.")`
- L58 _public function_ `FArguments& BackgroundColorHover(const FLinearColor& InBackgroundColor)` — `UE_DEPRECATED(5.0, "BackgroundColorHover has been removed. You may alter the background brush when hovered to get the same effect.")`
- L63 _public function_ `SLATE_DEFAULT_SLOT( FArguments, Content ) SLATE_ARGUMENT(FSlateColor, ValidColor) SLATE_ARGUMENT(FSlateColor, InvalidColor) SLATE_ARGUMENT(const FSlateBrush*, VerticalImage) SLATE_ARGUMENT(const FSlateBrush*, HorizontalImage) SLATE_ATTRIBUTE(const FSlateBrush*, BackgroundImage) SLATE_EVENT(FOnDrop, OnDropped) SLATE_EVENT(FVerifyDrag, OnAllowDrop) SLATE_EVENT(FVerifyDrag, OnIsRecognized) SLATE_EVENT(FOnDragAction, OnDragEnter) SLATE_EVENT(FOnDragAction, OnDragLeave) SLATE_ATTRIBUTE(bool, bOnlyRecognizeOnDragEnter) SLATE_ARGUMENT(bool, bUseAllowDropCache) FOnDrop ConvertOnDropFn(const FOnDropDeprecated& LegacyDelegate)` — Content to display for the in the drop target
- L100 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs );`
- L104 _public function_ `void ClearAllowDropCache()`
- L111 _protected prototype_ `bool AllowDrop(TSharedPtr<FDragDropOperation> DragDropOperation) const;`
- L113 _protected prototype_ `virtual bool OnAllowDrop(TSharedPtr<FDragDropOperation> DragDropOperation) const;`
- L114 _protected prototype_ `virtual bool OnIsRecognized(TSharedPtr<FDragDropOperation> DragDropOperation) const;`
- L116 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L119 _protected prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;` — SWidget interface
- L120 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L121 _protected prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L122 _protected prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L123 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L127 _protected prototype_ `EVisibility GetDragOverlayVisibility() const;` — @return Visibility of the overlay text when dragging is occurring.
- L130 _protected prototype_ `FSlateColor GetBackgroundBrightness() const;` — Get the brightness on the background.
- L133 _protected function_ `bool IsDragOver() const` — Returns true if this drop target is currently being hovered over by a drag drop event
- L137 _private member_ `FOnDrop DroppedEvent;` — Delegate to call when an asset is dropped
- L139 _private member_ `FVerifyDrag AllowDropEvent;` — Delegate to call to check validity of the asset
- L141 _private member_ `FVerifyDrag IsRecognizedEvent;` — Delegate to call to check validity of the asset
- L142 _private member_ `FOnDragAction OnDragEnterEvent;`
- L143 _private member_ `FOnDragAction OnDragLeaveEvent;`
- L145 _private member_ `TAttribute<bool> bOnlyRecognizeOnDragEnter;` — Attribute to check if the drop target should only be useable when actually dragging over it.
- L146 _private member_ `bool bUseAllowDropCache = false;`
- L149 _private member_ `FSlateColor ValidColor;` — The color of the vertical/horizontal images when the drop data is valid
- L151 _private member_ `FSlateColor InvalidColor;` — The color of the vertical/horizontal images when the drop data is not valid
- L153 _private member_ `const FSlateBrush* VerticalImage;` — Vertical border image that is used.
- L155 _private member_ `const FSlateBrush* HorizontalImage;` — Horizontal border image that is used.
- L158 _private member_ `mutable bool bIsDragEventRecognized;` — Whether or not we are being dragged over by a recognized event
- L160 _private member_ `mutable bool bAllowDrop;` — Whether or not we currently allow dropping
- L162 _private member_ `mutable bool bIsDragOver;` — Is the drag operation currently over our airspace?
- L164 _private member_ `mutable TOptional<bool> AllowDropCache;`
- L165 _private member_ `bool bIsDragDropping = false;`
- L166 _private member_ `bool bWasDragDroppingLastFrame = false;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API EDITORWIDGETS_API`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FVerifyDrag, TSharedPtr<FDragDropOperation>);`
- L38 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDragAction, const FDragDropEvent&);`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnDropDeprecated, TSharedPtr<FDragDropOperation>);`
- L90 _function_ `` (scope `SDropTarget::SLATE_DEFAULT_SLOT`)

### `Source/Editor/EditorWidgets/Public/SEnumCombo.h` (Public)


#### class `SEnumComboBox`  
`class SEnumComboBox : public SComboButton`  
_L24-91_
- inherits: `SComboButton`
- L27 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnEnumSelectionChanged, int32, ESelectInfo::Type);`
- L31 _public function_ `SLATE_BEGIN_ARGS(SEnumComboBox) : _CurrentValue() , _ContentPadding(FMargin(4.0, 2.0)) , _ComboButtonStyle(&FAppStyle::Get().GetWidgetStyle<FComboButtonStyle>("ComboButton")) , _ButtonStyle(nullptr) , _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText")) , _bForceBitFlags(false)`
- L40 _public prototype_ `SLATE_ATTRIBUTE(int32, CurrentValue) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ATTRIBUTE(FText, OverrideNoFlagsSetText) SLATE_EVENT(FOnEnumSelectionChanged, OnEnumSelectionChanged) SLATE_EVENT(FOnGetToolTipForValue, OnGetToolTipForValue) SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT(TArray<int32>, EnumValueSubset) SLATE_ARGUMENT(bool, bForceBitFlags) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UEnum* InEnum);`
- L56 _private prototype_ `FText GetCurrentValueText() const;`
- L57 _private prototype_ `FText GetCurrentValueTooltip() const;`
- L58 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L75 _private member_ `const UEnum* Enum;`
- L77 _private member_ `TAttribute<int32> CurrentValue;`
- L79 _private member_ `TAttribute<FSlateFontInfo> Font;`
- L80 _private member_ `TAttribute<FText> OverrideNoFlagsSetText;`
- L82 _private member_ `TArray<FEnumInfo> VisibleEnums;`
- L84 _private member_ `bool bUpdatingSelectionInternally;`
- L86 _private member_ `bool bIsBitflagsEnum;`
- L88 _private member_ `FOnGetToolTipForValue OnGetToolTipForValue;`
- L90 _private member_ `FOnEnumSelectionChanged OnEnumSelectionChangedDelegate;`

#### struct `SEnumComboBox::FEnumInfo`  
`struct FEnumInfo`  
_L62-73_
- L64 _public prototype_ `FEnumInfo() = default;`
- L65 _public function_ `FEnumInfo(const int32 InIndex, const int32 InValue, const FText InDisplayName, const FText InTooltipText) : Index(InIndex), Value(InValue), DisplayName(InDisplayName), TooltipText(InTooltipText)`
- L69 _public member_ `int32 Index = 0;`
- L70 _public member_ `int32 Value = 0;`
- L71 _public member_ `FText DisplayName;`
- L72 _public member_ `FText TooltipText;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API EDITORWIDGETS_API`
- L27 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnEnumSelectionChanged, int32, ESelectInfo::Type);`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetToolTipForValue, int32 ) public: SLATE_BEGIN_ARGS(SEnumComboBox) : _CurrentValue() , _ContentPadding(FMargin(4.0, 2.0)) , _ComboButtonStyle(&FAppStyle::Get().GetWidgetStyle<FComboButtonStyle>("ComboButton")) , _ButtonStyle(nullptr) , _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText")) , _bForceBitFlags(false) {} SLATE_ATTRIBUTE(int32, CurrentValue) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ATTRIBUTE(FText, OverrideNoFlagsSetText) SLATE_EVENT(FOnEnumSelectionChanged, OnEnumSelectionChanged) SLATE_EVENT(FOnGetToolTipForValue, OnGetToolTipForValue) SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT(TArray<int32>, EnumValueSubset) SLATE_ARGUMENT(bool, bForceBitFlags) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UEnum* InEnum);`

### `Source/Editor/EditorWidgets/Public/SInputChord.h` (Public)


#### class `SInputChord`  
`class SInputChord : public SCompoundWidget`  
_L17-49_
- inherits: `SCompoundWidget`
- desc: Displays a given input chord in a user-friendly way. ie. "[Keyboard Icon] Ctrl + C | Copy"
- L20 _public function_ `SLATE_BEGIN_ARGS(SInputChord) : _InputLabelStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>(TEXT("NormalText"))) , _ActionLabelStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>(TEXT("NormalText")))`
- L25 _public prototype_ `SLATE_ARGUMENT(const FSlateBrush*, Icon) SLATE_ARGUMENT(FText, InputLabel) SLATE_STYLE_ARGUMENT(FTextBlockStyle, InputLabelStyle) SLATE_ARGUMENT(FText, ActionLabel) SLATE_STYLE_ARGUMENT(FTextBlockStyle, ActionLabelStyle) SLATE_ARGUMENT(TSharedPtr<SWidget>, InputLabelDelimiterOverride) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The Icon should be derived from an FInputChord, usually a keyboard or mouse icon.
- L42 _public prototype_ `static TSharedRef<SInputChord> MakeForInputChord(const FInputChord& InInputChord, const FText& InActionLabel = { });` — Create an SInputChord widget for the given InputChord and (optional) ActionLabel. The InputLabel (ie. "Ctrl + C") is derived from the InputChord.
- L45 _public prototype_ `static TSharedRef<SInputChord> MakeForCommandInfo(const FUICommandInfo& InCommandInfo, const EMultipleKeyBindingIndex InKeyBindingIndex = EMultipleKeyBindingIndex::Primary);` — Create an SInputChord widget for the given CommandInfo. Optionally, provide a KeyBindingIndex for commands with multiple bindings.
- L48 _private prototype_ `static const FSlateBrush* GetIconForInputChord(const FInputChord& InInputChord);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORWIDGETS_API`

### `Source/Editor/EditorWidgets/Public/SMetaDataView.h` (Public)


#### class `SMetaDataView`  
`class SMetaDataView : public SCompoundWidget`  
_L23-41_
- inherits: `SCompoundWidget`
- desc: The widget to display metadata as a table of tag/value rows
- L26 _public function_ `SLATE_BEGIN_ARGS(SMetaDataView)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TMap<FName, FString>& InMetadata);`
- L38 _private member_ `TArray< TSharedPtr< FMetaDataLine > > MetaDataLines;`
- L40 _private prototype_ `TSharedRef< ITableRow > OnGenerateRow(const TSharedPtr< FMetaDataLine > Item, const TSharedRef< STableViewBase >& OwnerTable);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API EDITORWIDGETS_API`

### `Source/Editor/EditorWidgets/Public/SPopoutTabInlineContent.h` (Public)


#### class `SPopoutTabInlineContent`  
`class SPopoutTabInlineContent : public SCompoundWidget`  
_L22-199_
- inherits: `SCompoundWidget`
- desc: Inline content that can be popped out to a tab window. Manages the registration of the tab window.
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsPoppedOut) DECLARE_DELEGATE_OneParam(FOnPopoutStateChanged, const bool );`
- L29 _public prototype_ `static TSharedRef<SButton> CreateToggleButton(const TSharedRef<SPopoutTabInlineContent>& InOwner , const FText& InTooltipText = NSLOCTEXT("ToolWidgets", "PopoutTabInlineContentToolTip", "Open this content in its own tab window") , const FSlateBrush* const InIconBrush = FAppStyle::GetBrush(TEXT("Profi` — Constructs a default toggle button that can be used to pop out or pop in the content
- L33 _public function_ `SLATE_BEGIN_ARGS(SPopoutTabInlineContent) : _ContentHAlign(HAlign_Center) , _ContentVAlign(VAlign_Center) , _TabManager(nullptr) , _TabId(NAME_None) , _TabDisplayName(FText::GetEmpty()) , _TabIcon() , _TabRole(ETabRole::NomadTab) , _TabGroup(nullptr) , _Autosize(false) , _AutosizeWhenFloating(false) , _CanDragToPopout(false) , _ShowDragBorder(true) , _HideDockTabStackTab(false) , _InitiallyPoppedOut(false) , _OnPopoutStateChanged() , _OnGetMenuContent()`
- L52 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(EHorizontalAlignment, ContentHAlign) SLATE_ARGUMENT(EVerticalAlignment, ContentVAlign) SLATE_ARGUMENT(TWeakPtr<FTabManager>, TabManager) SLATE_ARGUMENT(FName, TabId) SLATE_ARGUMENT(FText, TabDisplayName) SLATE_ARGUMENT(FSlateIcon, TabIcon) SLATE_ARGUMENT(ETabRole, TabRole) SLATE_ARGUMENT(TSharedPtr<FWorkspaceItem>, TabGroup) SLATE_ARGUMENT(bool, Autosize) SLATE_ARGUMENT(bool, AutosizeWhenFloating) SLATE_ARGUMENT(bool, CanDragToPopout) SLATE_ARGUMENT(bool, ShowDragBorder) SLATE_ARGUMENT(bool, HideDockTabStackTab) SLATE_ARGUMENT(bool, InitiallyPoppedOut) SLATE_EVENT(FOnPopoutStateChanged, OnPopoutStateChanged) SLATE_EVENT(FOnGetContent, OnGetMenuContent) SLATE_END_ARGS() virtual ~SPopoutTabInlineContent() override;` — Inline content to pop out
- L92 _public prototype_ `void Construct(const FArguments& InArgs);`
- L95 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) const override;`
- L96 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L97 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L98 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& InPointerEvent) override;`
- L99 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L107 _public prototype_ `bool IsPoppedOut() const;` — Checks whether the inline content is currently popped out as a tab window. @return True if the content is popped out, otherwise false.
- L117 _public prototype_ `void Popout(const bool bInPopout);` — Modifies the popout state of the inline content. Popping out the content detaches it from its current container and moves it to a new tab window, while turning off the popout state reattaches it to its original container. @param bInPopout If true, the content is popped out to a separate tab window. If false, the content is returned to its original container.
- L122 _public prototype_ `void TogglePopout();` — Toggles the popout state of the inline content. Switches the content between its popped-out and embedded states.
- L126 _private prototype_ `TSharedPtr<FTabManager> GetTabManager() const;` — Gets the passed in tab manager or the global tab manager none was passed or null
- L129 _private prototype_ `bool IsUniqueTabId() const;` — Checks if the passed in tab Id is unique and does not conflict with any other existing tabs
- L131 _private prototype_ `void RegisterTab();`
- L132 _private prototype_ `void UnregisterTab();`
- L134 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& InArgs);`
- L135 _private prototype_ `void CloseTab();`
- L137 _private prototype_ `void OnTabActivated(const TSharedRef<SDockTab> InDockTab, const ETabActivationCause InActivationCause);`
- L138 _private prototype_ `void OnTabClosed(const TSharedRef<SDockTab> InDockTab);`
- L139 _private prototype_ `void OnTabRelocated();`
- L140 _private prototype_ `void OnTabForegrounded(const TSharedPtr<SDockTab> InNewTab, const TSharedPtr<SDockTab> InPreviousTab);`
- L142 _private prototype_ `TSharedRef<SWidget> CreateDefaultMenuContent();`
- L144 _private prototype_ `EVisibility GetContentVisibility() const;`
- L145 _private prototype_ `EVisibility GetContentBorderVisibility() const;`
- L147 _private prototype_ `void RegisterAutoSizeTimer(const TSharedPtr<SDockTab>& InDockTab = nullptr);`
- L148 _private prototype_ `void UnregisterAutoSizeTimer();`
- L149 _private prototype_ `EActiveTimerReturnType HandleAutoSizeWindowTimer(const double InCurrentTime , const float InDeltaTime, const TWeakPtr<SDockTab> InWeakTab);`
- L152 _private prototype_ `void TryHideStackTab();`
- L154 _private prototype_ `void BroadcastPopoutStateChanged(const bool bInNewPoppedOut);`
- L156 _private prototype_ `void RestoreInlineContent();`
- L158 _private prototype_ `void SubscribeToTabForegrounded();`
- L159 _private prototype_ `void UnsubscribeFromTabForegrounded();`
- L162 _private prototype_ `static bool IsTabFloating(const TSharedRef<SDockTab>& InDockTab);` — @return True if the tab is popped out and the tab is undocked
- L165 _private member_ `TWeakPtr<SWidget> WeakContentWidget;` — Cached slate constructor arguments
- L166 _private member_ `TWeakPtr<FTabManager> WeakTabManager;`
- L167 _private member_ `FName TabId;`
- L168 _private member_ `FText TabDisplayName;`
- L169 _private member_ `FSlateIcon TabIcon;`
- L170 _private member_ `ETabRole TabRole = ETabRole::NomadTab;`
- L171 _private member_ `TWeakPtr<FWorkspaceItem> WeakTabGroup;`
- L172 _private member_ `bool bAutosize = false;`
- L173 _private member_ `bool bAutosizeWhenFloating = false;`
- L174 _private member_ `bool bCanDragToPopout = false;`
- L175 _private member_ `bool bShowDragBorder = true;`
- L176 _private member_ `bool bHideDockTabStackTab = false;`
- L177 _private member_ `FOnPopoutStateChanged PopoutStateChangedDelegate;`
- L178 _private member_ `FOnGetContent GetMenuContentDelegate;`
- L180 _private member_ `TWeakPtr<SDockTab> WeakSpawnedDockTab;`
- L182 _private member_ `bool bTabRegistered = false;`
- L183 _private member_ `bool bPoppedOut = false;`
- L184 _private member_ `bool bIsForeground = false;`
- L185 _private member_ `bool bWantsToPopout = false;`
- L187 _private member_ `bool bLeftMouseDownOverWidget = false;`
- L188 _private member_ `bool bRightMouseDownOverWidget = false;`
- L190 _private member_ `FDelegateHandle TabForegroundedDelegateHandle;`
- L191 _private member_ `FOnActiveTabChanged::FDelegate TabForegroundedDelegate;`
- L193 _private member_ `TSharedPtr<FActiveTimerHandle> SetupWindowTimerHandle;`
- L196 _private member_ `TSharedPtr<SBox> InlineContentContainer;` — Inline container that owns the content when not popped out
- L198 _private member_ `TSharedPtr<SWidget> DetachedContentWidget;` — Strong ref while content is moved out of the inline host and into the dock tab

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORWIDGETS_API`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsPoppedOut) DECLARE_DELEGATE_OneParam(FOnPopoutStateChanged, const bool );`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPopoutStateChanged, const bool );`

### `Source/Editor/EditorWidgets/Public/STemplateStringEditableTextBox.h` (Public)


#### class `STemplateStringEditableTextBox`  
`class STemplateStringEditableTextBox : public SCompoundWidget`  
_L17-113_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(STemplateStringEditableTextBox) : _Style(nullptr) , _AllowMultiLine(false) , _IsReadOnly(false)`
- L26 _public prototype_ `SLATE_STYLE_ARGUMENT(FEditableTextBoxStyle, Style) SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FText, ResolvedText) SLATE_ATTRIBUTE(TConstArrayView<FString>, ValidArguments) SLATE_ARGUMENT(TSharedPtr<ITextLayoutMarshaller>, Marshaller) SLATE_ATTRIBUTE(bool, AllowMultiLine) SLATE_ATTRIBUTE(bool, IsReadOnly) SLATE_EVENT(FOnVerifyTextChanged, OnValidateTokenizedText) SLATE_EVENT(FOnTextChanged, OnTextChanged) SLATE_EVENT(FOnTextCommitted, OnTextCommitted) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The styling of the textbox.
- L62 _private prototype_ `FText GetText() const;` — @return Text contents based on current state
- L64 _private prototype_ `const FSlateBrush* GetBorderImage() const;`
- L65 _private prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L67 _private prototype_ `void SetStyle(const FEditableTextBoxStyle* InStyle);`
- L69 _private prototype_ `void SetError(const FText& InError) const;`
- L71 _private prototype_ `virtual bool HasKeyboardFocus() const override;`
- L72 _private prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L73 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L75 _private prototype_ `bool ValidateTokenizedText(const FText& InTokenizedText);`
- L76 _private prototype_ `bool ValidateTokenBraces(const FText& InTokenizedText, FText& OutError);`
- L77 _private prototype_ `bool ValidateTokenArgs(const FText& InTokenizedText, FText& OutError);`
- L79 _private prototype_ `bool ParseArgs(const FString& InTokenizedTextString, TArray<FString>& OutArgs);`
- L81 _private prototype_ `void OnEditableTextChanged(const FText& InTokenizedText);`
- L82 _private prototype_ `void OnEditableTextCommitted(const FText& InTokenizedText, ETextCommit::Type InCommitType);`
- L86 _private member_ `TSharedPtr<SMultiLineEditableText> EditableText;` — Editable text widget.
- L89 _private member_ `const FEditableTextBoxStyle* TextBoxStyle = nullptr;` — Style shared between Editable and NonEditable text widgets.
- L91 _private member_ `TSharedPtr<SHorizontalBox> Box;`
- L93 _private member_ `TSharedPtr<SBox> HScrollBarBox;`
- L94 _private member_ `TSharedPtr<SScrollBar> HScrollBar;`
- L96 _private member_ `TSharedPtr<SBox> VScrollBarBox;`
- L97 _private member_ `TSharedPtr<SScrollBar> VScrollBar;`
- L99 _private member_ `TSharedPtr<class IErrorReportingWidget> ErrorReporting;`
- L101 _private member_ `TAttribute<FText> TokenizedText;`
- L102 _private member_ `TAttribute<FText> ResolvedText;`
- L103 _private member_ `TAttribute<TConstArrayView<FString>> ValidArguments;`
- L106 _private member_ `FOnVerifyTextChanged OnValidateTokenizedText;` — Callback to verify tokenized text when changed. Will return an error message to denote problems.
- L109 _private member_ `FOnTextChanged OnTokenizedTextChanged;` — Callback when tokenized text is changed.
- L112 _private member_ `FOnTextCommitted OnTokenizedTextCommitted;` — Callback when tokenized text is committed.

### `Source/Editor/EditorWidgets/Public/STextPropertyEditableTextBox.h` (Public)


#### class `IEditableTextProperty`  
`class IEditableTextProperty`  
_L53-105_
- desc: Interface to allow STextPropertyEditableTextBox to be used to edit both properties and Blueprint pins
- L63 _public prototype_ `virtual ~IEditableTextProperty() = default;`
- L66 _public prototype_ `virtual bool IsMultiLineText() const = 0;` — Are the text properties being edited marked as multi-line?
- L69 _public prototype_ `virtual bool IsPassword() const = 0;` — Are the text properties being edited marked as password fields?
- L72 _public prototype_ `virtual bool IsReadOnly() const = 0;` — Are the text properties being edited read-only?
- L75 _public prototype_ `virtual bool IsDefaultValue() const = 0;` — Is the value associated with the properties the default value?
- L78 _public prototype_ `virtual FText GetToolTipText() const = 0;` — Get the tooltip text associated with the property being edited
- L81 _public prototype_ `virtual int32 GetNumTexts() const = 0;` — Get the number of FText instances being edited by this property
- L84 _public prototype_ `virtual FText GetText(const int32 InIndex) const = 0;` — Get the text at the given index (check against GetNumTexts)
- L87 _public prototype_ `virtual void SetText(const int32 InIndex, const FText& InText) = 0;` — Set the text at the given index (check against GetNumTexts)
- L90 _public prototype_ `virtual bool IsValidText(const FText& InText, FText& OutErrorMsg) const = 0;` — Check to see if the given text is valid to use
- L94 _public prototype_ `virtual void GetStableTextId(const int32 InIndex, const ETextPropertyEditAction InEditAction, const FString& InTextSource, const FString& InProposedNamespace, const FString& InProposedKey, FString& OutStableNamespace, FString& OutStableKey) const = 0;` — Get the stable text ID for the given index (check against GetNumTexts)
- L100 _protected prototype_ `static void StaticStableTextId(UObject* InObject, const ETextPropertyEditAction InEditAction, const FString& InTextSource, const FString& InProposedNamespace, const FString& InProposedKey, FString& OutStableNamespace, FString& OutStableKey);` — Get the localization ID we should use for the given object, and the given text instance
- L103 _protected prototype_ `static void StaticStableTextId(UPackage* InPackage, const ETextPropertyEditAction InEditAction, const FString& InTextSource, const FString& InProposedNamespace, const FString& InProposedKey, FString& OutStableNamespace, FString& OutStableKey);` — Get the localization ID we should use for the given package, and the given text instance

#### enum `IEditableTextProperty::ETextPropertyEditAction`  
`enum class ETextPropertyEditAction : uint8`  
_L56-61_
- L58 _public enumerator_ `EditedNamespace = (uint8)TextNamespaceUtil::ETextEditAction::Namespace`
- L59 _public enumerator_ `EditedKey = (uint8)TextNamespaceUtil::ETextEditAction::Key`
- L60 _public enumerator_ `EditedSource = (uint8)TextNamespaceUtil::ETextEditAction::SourceString`

#### class `STextPropertyEditableStringTableReference`  
`class STextPropertyEditableStringTableReference : public SCompoundWidget`  
_L108-176_
- inherits: `SCompoundWidget`
- desc: A widget that can be used for editing the string table referenced for FText instances
- L110 _private function_ `SLATE_BEGIN_ARGS(STextPropertyEditableStringTableReference) : _ComboStyle(&FCoreStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox")) , _ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton")) , _AllowUnlink(false)`
- L126 _public prototype_ `void Construct(const FArguments& Arguments, const TSharedRef<IEditableTextProperty>& InEditableTextProperty);`
- L135 _private prototype_ `void GetTableIdAndKey(FName& OutTableId, FString& OutKey) const;`
- L136 _private prototype_ `void SetTableIdAndKey(const FName InTableId, const FString& InKey);`
- L138 _private prototype_ `void OnOptionsFilterTextChanged(const FText& InNewText);`
- L139 _private prototype_ `void OnKeysFilterTextChanged(const FText& InNewText);`
- L141 _private prototype_ `TSharedRef<SWidget> OnGetStringTableComboOptions();`
- L142 _private prototype_ `TSharedRef<class ITableRow> OnGenerateStringTableComboOption(TSharedPtr<FAvailableStringTable> InItem, const TSharedRef<class STableViewBase>& OwnerTable);`
- L143 _private prototype_ `TSharedRef<SWidget> OnGetStringTableKeyOptions();`
- L144 _private prototype_ `TSharedRef<class ITableRow> OnGenerateStringTableKeyOption(TSharedPtr<FString> InItem, const TSharedRef<class STableViewBase>& OwnerTable);`
- L146 _private prototype_ `void OnStringTableComboChanged(TSharedPtr<FAvailableStringTable> NewSelection, ESelectInfo::Type SelectInfo);`
- L147 _private prototype_ `void UpdateStringTableComboOptions();`
- L148 _private prototype_ `FText GetStringTableComboContent() const;`
- L149 _private prototype_ `FText GetStringTableComboToolTip() const;`
- L151 _private prototype_ `void OnKeyComboChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L152 _private prototype_ `void UpdateStringTableKeyOptions();`
- L153 _private prototype_ `FText GetKeyComboContent() const;`
- L154 _private prototype_ `FText GetKeyComboToolTip() const;`
- L156 _private prototype_ `bool IsUnlinkEnabled() const;`
- L157 _private prototype_ `FReply OnUnlinkClicked();`
- L159 _private member_ `TSharedPtr<IEditableTextProperty> EditableTextProperty;`
- L161 _private typedef_ `using FOptionTextFilter = TTextFilter< TSharedPtr<FAvailableStringTable> >;`
- L162 _private member_ `TSharedPtr<FOptionTextFilter> OptionTextFilter;`
- L163 _private member_ `TSharedPtr<SSearchBox> OptionsSearchBox;`
- L165 _private typedef_ `using FKeyTextFilter = TTextFilter< TSharedPtr<FString> >;`
- L166 _private member_ `TSharedPtr<FKeyTextFilter> KeyTextFilter;`
- L167 _private member_ `TSharedPtr<SSearchBox> KeysSearchBox;`
- L169 _private member_ `TSharedPtr<SComboButton> StringTableOptionsCombo;`
- L170 _private member_ `TSharedPtr<SListView<TSharedPtr<FAvailableStringTable>>> StringTableOptionsList;`
- L171 _private member_ `TSharedPtr<SComboButton> StringTableKeysCombo;`
- L172 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> StringTableKeysList;`
- L174 _private member_ `TArray<TSharedPtr<FAvailableStringTable>> StringTableComboOptions;`
- L175 _private member_ `TArray<TSharedPtr<FString>> KeyComboOptions;`

#### struct `STextPropertyEditableStringTableReference::FAvailableStringTable`  
`struct FAvailableStringTable`  
_L129-133_
- L131 _public member_ `FName TableId;`
- L132 _public member_ `FText DisplayName;`

#### class `STextPropertyEditableTextBox`  
`class STextPropertyEditableTextBox : public SCompoundWidget`  
_L179-264_
- inherits: `SCompoundWidget`
- desc: A widget that can be used for editing FText instances
- L181 _private function_ `SLATE_BEGIN_ARGS(STextPropertyEditableTextBox) : _Style(&FCoreStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox")) , _Font() , _ForegroundColor() , _WrapTextAt(0.0f) , _AutoWrapText(false) , _MinDesiredWidth() , _MaxDesiredHeight(300.0f)`
- L207 _public prototype_ `void Construct(const FArguments& Arguments, const TSharedRef<IEditableTextProperty>& InEditableTextProperty);`
- L208 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L209 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L212 _private prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);`
- L213 _private prototype_ `bool CanEdit() const;`
- L214 _private prototype_ `bool IsCultureInvariantFlagEnabled() const;`
- L215 _private prototype_ `bool IsSourceTextReadOnly() const;`
- L216 _private prototype_ `bool IsIdentityReadOnly() const;`
- L217 _private prototype_ `FText GetToolTipText() const;`
- L218 _private prototype_ `bool IsTextLocalizable() const;`
- L220 _private prototype_ `FText GetTextValue() const;`
- L221 _private prototype_ `void OnTextChanged(const FText& NewText);`
- L222 _private prototype_ `void OnTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L223 _private prototype_ `void SetTextError(const FText& InErrorMsg);`
- L225 _private prototype_ `FText GetNamespaceValue() const;`
- L226 _private prototype_ `void OnNamespaceChanged(const FText& NewText);`
- L227 _private prototype_ `void OnNamespaceCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L229 _private prototype_ `FText GetKeyValue() const;`
- L231 _private prototype_ `void OnKeyChanged(const FText& NewText);`
- L232 _private prototype_ `void OnKeyCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L234 _private prototype_ `FText GetPackageValue() const;`
- L237 _private prototype_ `FText GetDevNotesValue() const;`
- L238 _private prototype_ `void OnDevNotesCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L240 _private prototype_ `ECheckBoxState GetLocalizableCheckState() const;`
- L242 _private prototype_ `void HandleLocalizableCheckStateChanged(ECheckBoxState InCheckboxState);`
- L244 _private prototype_ `FText GetAdvancedTextSettingsComboToolTip() const;`
- L245 _private prototype_ `const FSlateBrush* GetAdvancedTextSettingsComboImage() const;`
- L247 _private prototype_ `bool IsValidIdentity(const FText& InIdentity, FText* OutReason = nullptr, const FText* InErrorCtx = nullptr) const;`
- L249 _private member_ `TSharedPtr<IEditableTextProperty> EditableTextProperty;`
- L251 _private member_ `TSharedPtr<class SWidget> PrimaryWidget;`
- L253 _private member_ `TSharedPtr<SMultiLineEditableTextBox> MultiLineWidget;`
- L255 _private member_ `TSharedPtr<SEditableTextBox> SingleLineWidget;`
- L257 _private member_ `TSharedPtr<SEditableTextBox> NamespaceEditableTextBox;`
- L259 _private member_ `TSharedPtr<SEditableTextBox> KeyEditableTextBox;`
- L261 _private member_ `bool bIsMultiLine = false;`
- L263 _private member_ `static FText MultipleValuesText;`

#### Free symbols / members of external scopes

- L39 _macro_ `#define UE_API EDITORWIDGETS_API`
