# Editor / KismetWidgets

- module root: `Source/Editor/KismetWidgets`
- headers: 9; symbols: 205
- symbol kinds: class=10, delegate=9, enum=2, enumerator=8, function=15, macro=6, member=69, prototype=81, struct=2, typedef=3
- DynamicallyLoadedModuleNames: AssetTools, ContentBrowser
- PrivateDependencyModuleNames: BlueprintGraph, ClassViewer, ContentBrowserData, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, InputCore, Slate, SlateCore, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: AssetTools, ContentBrowser

### `Source/Editor/KismetWidgets/Public/CreateBlueprintFromActorDialog.h` (Public)


#### enum `ECreateBlueprintFromActorMode`  
`enum class ECreateBlueprintFromActorMode : uint8`  
_L18-24_
- desc: Enum defining which mode to use when creating the blueprint from the selected actors
- L20 _public enumerator_ `None` — Indicates that a user is unable to create blueprints from the currently selected actor set
- L21 _public enumerator_ `Harvest = 1` — Harvest all the components of the selected actors and create an actor blueprint with those components in it.
- L22 _public enumerator_ `Subclass = 2` — Create a subclass of the selected Actor's class with defaults from the selected Actor. Valid only when there is a single selected actor.
- L23 _public enumerator_ `ChildActor = 4` — Create an actor blueprint with each selected actor as a child actor component

#### class `FCreateBlueprintFromActorDialog`  
`class FCreateBlueprintFromActorDialog`  
_L27-53_
- L37 _public prototype_ `static void OpenDialog(ECreateBlueprintFromActorMode CreateMode, AActor* InActorOverride = nullptr, bool bInReplaceActors = true);` — Static function to access constructing this window. @param CreateMode		The mode to use when creating a blueprint from the selected actors @param ActorOverride		If set convert the specified actor, if null use the currently selected actor
- L42 _public prototype_ `static ECreateBlueprintFromActorMode GetValidCreationMethods();` — Static function that returns which create modes are valid given the current selection set
- L52 _private prototype_ `static void OnCreateBlueprint(const FString& InAssetPath, UClass* ParentClass, ECreateBlueprintFromActorMode CreateMode, AActor* ActorToUse, bool bInReplaceActors);` — Create the blueprint in response to the path being specified by the user @param InAssetPath		Path of the asset to create @param bInHarvest		The mode to use when creating a blueprint from the selected actors

### `Source/Editor/KismetWidgets/Public/KismetWidgets.h` (Public)


#### class `FKismetWidgetsModule`  
`class FKismetWidgetsModule : public IModuleInterface`  
_L11-24_
- inherits: `IModuleInterface`
- desc: Slate style module, loaded by SlateApplication dynamically at startup
- L15 _public function_ `virtual void StartupModule() override`
- L20 _public function_ `virtual void ShutdownModule() override`

### `Source/Editor/KismetWidgets/Public/PinTypeSelectorFilter.h` (Public)


#### class `UPinTypeSelectorFilter`  
`class UPinTypeSelectorFilter : public UObject`  
_L11-19_
- reflection: `UCLASS(abstract, transient, MinimalAPI, config=Editor)`
- inherits: `UObject`
- L16 _public member_ `TSoftClassPtr<UPinTypeSelectorFilter> FilterClass = nullptr;` — `UPROPERTY(config)`
- L18 _public function_ `virtual TSharedPtr<IPinTypeSelectorFilter> GetPinTypeSelectorFilter() const`

### `Source/Editor/KismetWidgets/Public/SKismetLinearExpression.h` (Public)


#### class `SKismetLinearExpression`  
`class SKismetLinearExpression : public SCompoundWidget`  
_L22-42_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS( SKismetLinearExpression ) : _IsEditable(true)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphPin* InitialInputPin);`
- L34 _public prototype_ `void SetExpressionRoot(UEdGraphPin* InputPin);`
- L36 _protected prototype_ `TSharedRef<SWidget> MakeNodeWidget(const UEdGraphNode* Node, const UEdGraphPin* FromPin);`
- L37 _protected prototype_ `TSharedRef<SWidget> MakePinWidget(const UEdGraphPin* Pin);`
- L40 _protected member_ `TAttribute<bool> IsEditable;`
- L41 _protected member_ `TSet<const UEdGraphNode*> VisitedNodes;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API KISMETWIDGETS_API`

### `Source/Editor/KismetWidgets/Public/SLevelOfDetailBranchNode.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SLevelOfDetailBranchNode>`  
_L25-28_
- L27 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SLevelOfDetailBranchNode`  
`class SLevelOfDetailBranchNode : public SCompoundWidget`  
_L30-75_
- inherits: `SCompoundWidget`
- L32 _private function_ `SLATE_BEGIN_ARGS(SLevelOfDetailBranchNode) : _UseLowDetailSlot(false)`
- L49 _public prototype_ `SLevelOfDetailBranchNode();`
- L51 _public prototype_ `void Construct(const FArguments& InArgs);`
- L54 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L58 _public prototype_ `void RefreshLODSlotContent();` — Determine whether we need to show the low-detail slot or high-detail slot
- L62 _protected member_ `int LastCachedValue;` — What kind of slot was shown last frame
- L65 _protected member_ `TAttribute<bool> ShowLowDetailAttr;` — The attribute indicating the kind of slot to show
- L68 _protected member_ `TSharedRef<SWidget> ChildSlotLowDetail;` — The low-detail child slot
- L71 _protected member_ `TSharedRef<SWidget> ChildSlotHighDetail;` — The high-detail child slot
- L73 _protected member_ `FOnGetActiveDetailSlotContent OnGetActiveDetailSlotContent;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API KISMETWIDGETS_API`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGetActiveDetailSlotContent, bool);`
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGetActiveDetailSlotContent, bool);`

### `Source/Editor/KismetWidgets/Public/SPinTypeSelector.h` (Public)


#### struct `FTopLevenshteinResult`  
`template <typename ItemType> struct FTopLevenshteinResult`  
_L58-80_
- L60 _public member_ `ItemType Item;`
- L61 _public member_ `float Score = INDEX_NONE;`
- L63 _public function_ `bool IsSet() const`
- L65 _public function_ `void CompareAndUpdate(FStringView SearchValue, const ItemType& NewItem, FStringView NewItemValue)`

#### class `SPinTypeSelector`  
`class SPinTypeSelector : public SCompoundWidget`  
_L96-315_
- inherits: `SCompoundWidget`
- desc: Widget for modifying the type for a variable or pin
- L99 _public prototype_ `static TSharedRef<SWidget> ConstructPinTypeImage(const FSlateBrush* PrimaryIcon, const FSlateColor& PrimaryColor, const FSlateBrush* SecondaryIcon, const FSlateColor& SecondaryColor, TSharedPtr<SToolTip> InToolTip);`
- L100 _public prototype_ `static TSharedRef<SWidget> ConstructPinTypeImage(TAttribute<const FSlateBrush*> PrimaryIcon, TAttribute<FSlateColor> PrimaryColor, TAttribute<const FSlateBrush*> SecondaryIcon, TAttribute<FSlateColor> SecondaryColor );`
- L101 _public prototype_ `static TSharedRef<SWidget> ConstructPinTypeImage(UEdGraphPin* Pin);`
- L115 _public function_ `SLATE_BEGIN_ARGS(SPinTypeSelector) : _TargetPinType() , _Schema(nullptr) , _SchemaAction(nullptr) , _TypeTreeFilter(ETypeTreeFilter::None) , _bAllowArrays(true) , _TreeViewWidth(300.f) , _TreeViewHeight(350.f) , _Font(FAppStyle::GetFontStyle(TEXT("NormalFont"))) , _SelectorType(ESelectorType::Full) , _ReadOnly(false)`
- L143 _public prototype_ `void Construct(const FArguments& InArgs, FGetPinTypeTree GetPinTypeTreeFunc);`
- L146 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — SWidget interface
- L147 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L148 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L153 _protected prototype_ `const FSlateBrush* GetTypeIconImage() const;` — Gets the icon (value, array, set, or map) for the type being manipulated
- L156 _protected prototype_ `const FSlateBrush* GetSecondaryTypeIconImage() const;` — Gets the secondary icon (for maps, otherwise null) for the type being manipulated
- L159 _protected prototype_ `FSlateColor GetTypeIconColor() const;` — Gets the type-specific color for the type being manipulated
- L162 _protected prototype_ `FSlateColor GetSecondaryTypeIconColor() const;` — Gets the secondary type-specific color for the type being manipulated
- L165 _protected prototype_ `FText GetTypeDescription(bool bIncludeSubcategory = false) const;` — Gets a succinct type description for the type being manipulated
- L168 _protected prototype_ `FText GetSecondaryTypeDescription(bool bIncludeSubcategory = false) const;` — Gets the secondary type description. E.g. the value type for TMaps
- L171 _protected prototype_ `FText GetCombinedTypeDescription(bool bIncludeSubcategory = false) const;` — Gets a combined description of the primary, container, and secondary types. E.g. "Map of Strings to Floats"
- L173 _protected member_ `TSharedPtr<SComboButton> TypeComboButton;`
- L174 _protected member_ `TSharedPtr<SComboButton> SecondaryTypeComboButton;`
- L175 _protected member_ `TSharedPtr<SSearchBox> FilterTextBox;`
- L176 _protected member_ `TSharedPtr<SPinTypeTreeView> TypeTreeView;`
- L179 _protected member_ `TAttribute<FEdGraphPinType> TargetPinType;` — The pin attribute that we're modifying with this widget
- L182 _protected member_ `FOnPinTypeChanged OnTypeChanged;` — Delegate that is called every time the pin type changes (before and after).
- L183 _protected member_ `FOnPinTypeChanged OnTypePreChanged;`
- L186 _protected member_ `FGetPinTypeTree GetPinTypeTree;` — Delegate for the type selector to retrieve the pin type tree (passed into the Construct so the tree can depend on the situation)
- L189 _protected member_ `const UEdGraphSchema* Schema;` — Schema in charge of determining available types for this pin
- L192 _protected member_ `TWeakPtr<const FEdGraphSchemaAction> SchemaAction;` — Schema action related to the pin selection
- L195 _protected member_ `ETypeTreeFilter TypeTreeFilter;` — UEdgraphSchema::ETypeTreeFilter flags for filtering available types
- L198 _protected member_ `TAttribute<FOptionalSize> TreeViewWidth;` — Desired width of the tree view widget
- L201 _protected member_ `TAttribute<FOptionalSize> TreeViewHeight;` — Desired height of the tree view widget
- L204 _protected member_ `bool bIsRightMousePressed;` — TRUE when the right mouse button is pressed, keeps from handling a right click that does not begin in the widget
- L207 _protected member_ `bool bMenuContentIsSecondary = false;` — true if GetMenuContent was last called with bForSecondaryType == true
- L210 _protected member_ `ESelectorType SelectorType;` — Whether the selector is using the compact or full mode, or not a selector at all, but just the type image.
- L213 _protected member_ `TAttribute<bool> ReadOnly;` — Whether or not the type is read only and not editable (implies a different style)
- L216 _protected member_ `int32 NumFilteredPinTypeItems;` — Total number of filtered pin type items. This count excludes category items and reference subtypes.
- L219 _protected member_ `int32 NumValidPinTypeItems;` — Total number of valid pin type items, that could be filtered. This count excludes category items and reference subtypes.
- L222 _protected member_ `TArray<FObjectReferenceListItem> AllowedObjectReferenceTypes;` — Holds a cache of the allowed Object Reference types for the last sub-menu opened.
- L223 _protected member_ `TWeakPtr<SListView<FObjectReferenceListItem>> WeakListView;`
- L224 _protected member_ `TWeakPtr<SMenuOwner> PinTypeSelectorMenuOwner;`
- L227 _protected member_ `TArray<FObjectReferenceListItem> CurrentPinAllowedObjectReferenceTypes;` — Holds a cache of the allowed Object Reference types for the current pin type, to be shown inline.
- L230 _protected member_ `TArray<TSharedPtr<class IPinTypeSelectorFilter>> CustomFilters;` — An interface to optionally apply a custom filter to the available pin type items for display.
- L233 _protected prototype_ `ECheckBoxState IsArrayChecked() const;` — Array checkbox support functions
- L234 _protected prototype_ `void OnArrayCheckStateChanged(ECheckBoxState NewState);`
- L237 _protected prototype_ `void OnArrayStateToggled();` — Toggles the variable type as an array
- L240 _protected prototype_ `void OnContainerTypeSelectionChanged(EPinContainerType PinContainerType);` — Updates the variable container type:
- L243 _protected member_ `TArray<FPinTypeTreeItem> TypeTreeRoot;` — Array containing the unfiltered list of all supported types this pin could possibly have
- L245 _protected member_ `TArray<FPinTypeTreeItem> FilteredTypeTreeRoot;` — Array containing a filtered list, according to the text in the searchbox
- L248 _protected prototype_ `virtual TSharedRef<ITableRow> GenerateTypeTreeRow(FPinTypeTreeItem InItem, const TSharedRef<STableViewBase>& OwnerTree, bool bForSecondaryType);` — Treeview support functions
- L249 _protected prototype_ `void OnTypeSelectionChanged(FPinTypeTreeItem Selection, ESelectInfo::Type SelectInfo, bool bForSecondaryType);`
- L250 _protected prototype_ `void GetTypeChildren(FPinTypeTreeItem InItem, TArray<FPinTypeTreeItem>& OutChildren);`
- L253 _protected prototype_ `TSharedRef<ITableRow> GenerateObjectReferenceTreeRow(FObjectReferenceListItem InItem, const TSharedRef<STableViewBase>& OwnerTree);` — Listview support functions for sub-menu
- L254 _protected prototype_ `void OnObjectReferenceSelectionChanged(FObjectReferenceListItem InItem, ESelectInfo::Type SelectInfo, bool bForSecondaryType);`
- L257 _protected member_ `TSharedPtr<SMenuOwner> MenuContent;` — Reference to the menu content that's displayed when the type button is clicked on
- L258 _protected member_ `FEdGraphPinType MenuContextPinType;`
- L260 _protected prototype_ `virtual TSharedRef<SWidget> GetMenuContent(bool bForSecondaryType);`
- L261 _protected prototype_ `TSharedRef<SWidget> GetPinContainerTypeMenuContent();`
- L264 _protected member_ `FText SearchText;` — Type searching support
- L265 _protected prototype_ `void OnFilterTextChanged(const FText& NewText);`
- L266 _protected prototype_ `void OnFilterTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L269 _protected prototype_ `void FilterUnsupportedTypes(TArray<FPinTypeTreeItem>& UnfilteredList);` — Helper to generate the filtered list of types, based on the supported types of the schema
- L272 _protected prototype_ `bool GetChildrenMatchingSearch(const FText& SearchText, const TArray<FPinTypeTreeItem>& UnfilteredList, TArray<FPinTypeTreeItem>& OutFilteredList, FTopLevenshteinResult<FPinTypeTreeItem>& OutTopLevenshteinResult);` — Helper to generate the filtered list of types, based on the search string matching
- L275 _protected prototype_ `FText GetToolTipForComboBoxType() const;` — Callback to get the tooltip text for the pin type combo box
- L278 _protected prototype_ `FText GetToolTipForComboBoxSecondaryType() const;` — Callback to get the tooltip text for the secondary pin type combo box
- L281 _protected prototype_ `FText GetToolTipForArrayWidget() const;` — Callback to get the tooltip for the array button widget
- L284 _protected prototype_ `FText GetToolTipForContainerWidget() const;` — Callback to get the tooltip for the container type dropdown widget
- L287 _protected prototype_ `FText GetPinTypeItemCountText() const;` — Callback to get the display text for the total pin type item count
- L297 _protected prototype_ `TSharedRef<SWidget> CreateObjectReferenceWidget(FPinTypeTreeItem InItem, FEdGraphPinType& InPinType, const FSlateBrush* InIconBrush, FText InSimpleTooltip) const;` — Helper function to create widget for the sub-menu @param InItem				Tree item to use for the callback when a menu item is selected @param InPinType				Pin type for generation of the widget to display for the menu entry @param InIconBrush			Brush icon to use for the menu entry item @param InTooltip				The simple tooltip to use for the menu item, an advanced tooltip link will be auto-generated based on the PinCategory
- L300 _protected prototype_ `TSharedRef< SWidget > GetAllowedObjectTypes(FPinTypeTreeItem InItem, bool bForSecondaryType);` — Gets the allowable object types for an tree item, used for building the sub-menu
- L303 _protected prototype_ `void GenerateAllowedObjectTypesList(TArray<FObjectReferenceListItem>& OutList, FPinTypeTreeItem InItem, bool bForSecondaryType) const;` — Fills the provided array with generated list items based on a pin type's allowed reference types, which could then be used as the item source for a list view
- L311 _protected prototype_ `void OnSelectPinType(FPinTypeTreeItem InItem, FName InPinCategory, bool bForSecondaryType);` — When a pin type is selected, handle it @param InItem				Item selected @param InPinCategory			This is the PinType's category, must be provided separately as the PinType in the tree item is always Object Types for any object related type.
- L314 _protected prototype_ `void OnCustomFilterChanged();` — Called whenever the custom filter options are changed.

#### enum `SPinTypeSelector::ESelectorType`  
`enum class ESelectorType : uint8`  
_L104-113_
- desc: Which type of selector should be used: compact or full mode, or not a selector at all, but just the type image.
- L106 _public enumerator_ `None`
- L108 _public enumerator_ `Compact` — Shows only the type selector pill
- L110 _public enumerator_ `Partial` — Shows the type selector pill and full name of type
- L112 _public enumerator_ `Full` — Shows the type selector pill, full name of type, and container selection type

#### class `IPinTypeSelectorFilter`  
`class IPinTypeSelectorFilter`  
_L322-338_
- desc: An interface for implementing a custom pin type filter for the selector widget.
- L325 _public prototype_ `virtual ~IPinTypeSelectorFilter() = default;`
- L328 _public prototype_ `virtual bool ShouldShowPinTypeTreeItem(FPinTypeTreeItem InItem) const = 0;` — (Required) - Implement this method to filter the given pin type item and determine whether or not it should be displayed.
- L331 _public function_ `virtual FDelegateHandle RegisterOnFilterChanged(FSimpleDelegate InOnFilterChanged)` — (Optional) - Override this method to bind a delegate to call when the filter changes.
- L334 _public function_ `virtual void UnregisterOnFilterChanged(FDelegateHandle InDelegateHandle)` — (Optional) - Override this method to unbind a delegate that was previously bound to a filter change event.
- L337 _public function_ `virtual TSharedPtr<SWidget> GetFilterOptionsWidget()` — (Optional) - Override this method to return a widget that allows the user to toggle filter options on/off, etc.

#### Free symbols / members of external scopes

- L40 _macro_ `#define UE_API KISMETWIDGETS_API`
- L55 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPinTypeChanged, const FEdGraphPinType&) template <typename ItemType> struct FTopLevenshteinResult { ItemType Item; float Score = INDEX_NONE; bool IsSet() const { return Score != static_cast<float>(INDEX_NONE); } void CompareAndUpdate(FStringView SearchValue, const ItemType& NewItem, FStringView NewItemValue) { if (SearchValue.IsEmpty() || NewItemValue.IsEmpty()) { return; } const float WorstCase = static_cast<float>(SearchValue.Len() + NewItemValue.Len()); const float NormalizedDistance = 1.0f - static_cast<float>(Algo::LevenshteinDistance(SearchValue, NewItemValue)) / WorstCase; if (NormalizedDistance > Score) { Score = NormalizedDistance; Item = NewItem; } } };`
- L86 _typedef_ `typedef TSharedPtr<class UEdGraphSchema_K2::FPinTypeTreeInfo> FPinTypeTreeItem;`
- L87 _typedef_ `typedef STreeView<FPinTypeTreeItem> SPinTypeTreeView;`
- L89 _delegate_ `DECLARE_DELEGATE_TwoParams(FGetPinTypeTree, TArray<FPinTypeTreeItem >&, ETypeTreeFilter);`
- L89 _prototype_ `DECLARE_DELEGATE_TwoParams(FGetPinTypeTree, TArray<FPinTypeTreeItem >&, ETypeTreeFilter);`
- L93 _typedef_ `typedef TSharedPtr<struct FObjectReferenceType> FObjectReferenceListItem;`

### `Source/Editor/KismetWidgets/Public/SScrubControlPanel.h` (Public)


#### class `SScrubControlPanel`  
`class SScrubControlPanel : public SCompoundWidget`  
_L21-120_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS( SScrubControlPanel ) : _Value( 0 ) , _NumOfKeys() , _SequenceLength() , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _OnClickedForwardPlay() , _OnClickedRecord() , _OnClickedBackwardPlay() , _OnClickedForwardStep() , _OnClickedBackwardStep() , _OnClickedForwardEnd() , _OnClickedBackwardEnd() , _OnClickedToggleLoop() , _OnGetLooping() , _OnGetPlaybackMode() , _OnGetRecording() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence() , _OnTickPlayback() , _TransportControlWidgetsToCreate()`
- L50 _public prototype_ `SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE(bool, DisplayDrag) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement )`
- L100 _public prototype_ `SLATE_EVENT(FOnGetRecordButtonVisibility, OnGetRecordVisibility);`
- L102 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L111 _public prototype_ `virtual ~SScrubControlPanel() = default;`
- L114 _protected prototype_ `EVisibility GetRealtimeControlVisibility(bool bIsControlForRealtimeStreamingMode) const;`
- L117 _protected member_ `TSharedPtr<class SScrubWidget> ScrubWidget;`
- L119 _protected member_ `TAttribute<bool> IsRealtimeStreamingMode;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API KISMETWIDGETS_API`

### `Source/Editor/KismetWidgets/Public/SScrubWidget.h` (Public)


#### class `SScrubWidget`  
`class SScrubWidget : public SCompoundWidget`  
_L42-179_
- inherits: `SCompoundWidget`
- L46 _public function_ `SLATE_BEGIN_ARGS(SScrubWidget) : _Value(0) , _NumOfKeys(10) , _SequenceLength() , _bAllowZoom(false) , _bDisplayAnimScrubBarEditing(true) , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence()`
- L63 _public prototype_ `SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE( bool, DisplayDrag ) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange ) SLATE_EVENT( FOnCropAnimSequence, OnCropAnimSequence ) SLATE_EVENT( FOnAddAnimSequence, OnAddAnimSequence ) SLATE_EVENT(FOnAppendAnimSequence, OnAppendAnimSequence) SLATE_EVENT( FOnReZeroAnimSequence, OnReZeroAnimSequence ) SLATE_ATTRIBUTE( TArray<float>, DraggableBars ) SLATE_EVENT( FOnScrubBarDrag, OnBarDrag ) SLATE_EVENT( FOnScrubBarCommit, OnBarCommit ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — The value to display
- L102 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L103 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L104 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L105 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L106 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L107 _public prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L108 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L111 _public prototype_ `static int32 GetDivider(float InputMinX, float InputMaxX, FVector2D WidgetSize, float SequenceLength, int32 NumFrames);` — `UE_DEPRECATED(5.6, "Use the helper function accepting FVector2f instead of FVector2D")`
- L112 _public prototype_ `static int32 GetDivider(float InputMinX, float InputMaxX, FVector2f WidgetSize, float SequenceLength, int32 NumFrames);`
- L122 _protected prototype_ `void CommitValue( float NewValue, bool bSliderClamp, bool bCommittedFromText );` — Call this method when the user's interaction has changed the value @param NewValue				Value resulting from the user's interaction @param bSliderClamp			true to clamp the slider value to the nearest delta value @param bCommittedFromText	true if the value was committed from the text box and not the slider
- L127 _private prototype_ `void CreateContextMenu( float CurrentFrameTime, const FPointerEvent& MouseEvent );` — Function to create context menu to display anim sequence editing options
- L130 _private prototype_ `void OnSequenceCroppedCalled( bool bFromStart, float CurrentFrameTime );` — Function to crop animation sequence before/after selected frame
- L133 _private prototype_ `void OnSequenceAddedCalled(bool bBefore, int32 CurrentFrameNumber);` — Function to crop animation sequence before/after selected frame
- L136 _private prototype_ `void OnSequenceAppendedCalled(const FText & InNewGroupText, ETextCommit::Type CommitInfo, bool bBegin);` — Function to append frames in the beginning or at the end
- L139 _private prototype_ `void OnShowPopupOfAppendAnimation(bool bBegin);` — Function to ask how many frames to append
- L142 _private prototype_ `void OnReZeroCalled(int32 FrameIndex);` — Function to zero out translation of the selected frame
- L144 _private member_ `TAttribute<float> ValueAttribute;`
- L145 _private member_ `FOnFloatValueChanged OnValueChanged;`
- L146 _private member_ `FSimpleDelegate OnBeginSliderMovement;`
- L147 _private member_ `FOnFloatValueChanged OnEndSliderMovement;`
- L149 _private member_ `TAttribute<float> ViewInputMin;`
- L150 _private member_ `TAttribute<float> ViewInputMax;`
- L151 _private member_ `FOnSetInputViewRange OnSetInputViewRange;`
- L152 _private member_ `FOnCropAnimSequence OnCropAnimSequence;`
- L153 _private member_ `FOnAddAnimSequence OnAddAnimSequence;`
- L154 _private member_ `FOnAppendAnimSequence OnAppendAnimSequence;`
- L155 _private member_ `FOnReZeroAnimSequence OnReZeroAnimSequence;`
- L158 _private member_ `TAttribute<TArray<float>> DraggableBars;` — Dragagble bars are generic lines drawn on the scrub widget that can be dragged with the mouse. This is very bare bones and just represents drawing/moving float values
- L159 _private member_ `FOnScrubBarDrag OnBarDrag;`
- L160 _private member_ `FOnScrubBarCommit OnBarCommit;`
- L163 _private member_ `float DistanceDragged;` — Distance Dragged
- L165 _private member_ `TAttribute<uint32> NumOfKeys;` — Number of Keys
- L166 _private member_ `TAttribute<float> SequenceLength;`
- L168 _private member_ `bool bDragging;` — The number of decimal places to display
- L169 _private member_ `bool bAllowZoom;`
- L170 _private member_ `bool bDisplayAnimScrubBarEditing;`
- L171 _private member_ `TAttribute<bool> bDisplayDrag;`
- L173 _private member_ `bool bPanning;` — If we are currently panning the panel
- L175 _private member_ `bool bMouseMovedDuringPanning;` — Has the mouse moved during panning - used to determine if we should open the context menu or not
- L177 _private member_ `int32 DraggableBarIndex;` — Bar Dragging
- L178 _private member_ `bool DraggingBar;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API KISMETWIDGETS_API`
- L35 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnCropAnimSequence, bool, float ) DECLARE_DELEGATE_TwoParams( FOnAddAnimSequence, bool, int32 ) DECLARE_DELEGATE_TwoParams( FOnAppendAnimSequence, bool, int32 ) DECLARE_DELEGATE_TwoParams( FOnScrubBarDrag, int32, float) DECLARE_DELEGATE_TwoParams( FOnScrubBarCommit, int32, float) DECLARE_DELEGATE_OneParam( FOnReZeroAnimSequence, int32 ) class SScrubWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SScrubWidget) : _Value(0) , _NumOfKeys(10) , _SequenceLength() , _bAllowZoom(false) , _bDisplayAnimScrubBarEditing(true) , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence() {} SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE( bool, DisplayDrag ) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement )` — A Slate SpinBox resembles traditional spin boxes in that it is a widget that provides keyboard-based and mouse-based manipulation of a numberic value. Mouse-based manipulation: drag anywhere on the spinbox to change the value. Keyboard-based manipulation: click on the spinbox to enter text mode.
- L36 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnAddAnimSequence, bool, int32 ) DECLARE_DELEGATE_TwoParams( FOnAppendAnimSequence, bool, int32 ) DECLARE_DELEGATE_TwoParams( FOnScrubBarDrag, int32, float) DECLARE_DELEGATE_TwoParams( FOnScrubBarCommit, int32, float) DECLARE_DELEGATE_OneParam( FOnReZeroAnimSequence, int32 ) class SScrubWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SScrubWidget) : _Value(0) , _NumOfKeys(10) , _SequenceLength() , _bAllowZoom(false) , _bDisplayAnimScrubBarEditing(true) , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence() {} SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE( bool, DisplayDrag ) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement )`
- L37 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnAppendAnimSequence, bool, int32 ) DECLARE_DELEGATE_TwoParams( FOnScrubBarDrag, int32, float) DECLARE_DELEGATE_TwoParams( FOnScrubBarCommit, int32, float) DECLARE_DELEGATE_OneParam( FOnReZeroAnimSequence, int32 ) class SScrubWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SScrubWidget) : _Value(0) , _NumOfKeys(10) , _SequenceLength() , _bAllowZoom(false) , _bDisplayAnimScrubBarEditing(true) , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence() {} SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE( bool, DisplayDrag ) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement ) SLATE_ATTRIBUTE( float, ViewInputMin )`
- L38 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnScrubBarDrag, int32, float) DECLARE_DELEGATE_TwoParams( FOnScrubBarCommit, int32, float) DECLARE_DELEGATE_OneParam( FOnReZeroAnimSequence, int32 ) class SScrubWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SScrubWidget) : _Value(0) , _NumOfKeys(10) , _SequenceLength() , _bAllowZoom(false) , _bDisplayAnimScrubBarEditing(true) , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence() {} SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE( bool, DisplayDrag ) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax )`
- L39 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnScrubBarCommit, int32, float) DECLARE_DELEGATE_OneParam( FOnReZeroAnimSequence, int32 ) class SScrubWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SScrubWidget) : _Value(0) , _NumOfKeys(10) , _SequenceLength() , _bAllowZoom(false) , _bDisplayAnimScrubBarEditing(true) , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence() {} SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE( bool, DisplayDrag ) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange )`
- L40 _delegate_ `DECLARE_DELEGATE_OneParam( FOnReZeroAnimSequence, int32 ) class SScrubWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SScrubWidget) : _Value(0) , _NumOfKeys(10) , _SequenceLength() , _bAllowZoom(false) , _bDisplayAnimScrubBarEditing(true) , _DisplayDrag(true) , _OnValueChanged() , _OnBeginSliderMovement() , _OnEndSliderMovement() , _ViewInputMin() , _ViewInputMax() , _OnSetInputViewRange() , _OnCropAnimSequence() {} SLATE_ATTRIBUTE( float, Value ) SLATE_ATTRIBUTE( uint32, NumOfKeys ) SLATE_ATTRIBUTE( float, SequenceLength ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing ) SLATE_ATTRIBUTE( bool, DisplayDrag ) SLATE_EVENT( FOnFloatValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnFloatValueChanged, OnEndSliderMovement ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange )`

### `Source/Editor/KismetWidgets/Public/SSingleObjectDetailsPanel.h` (Public)


#### class `SSingleObjectDetailsPanel`  
`class SSingleObjectDetailsPanel : public SCompoundWidget`  
_L25-59_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SSingleObjectDetailsPanel)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class FUICommandList>, HostCommandList) SLATE_ARGUMENT(TSharedPtr<class FTabManager>, HostTabManager) SLATE_END_ARGS() void Construct(const FArguments& InArgs, bool bAutomaticallyObserveViaGetObjectToObserve = true, bool bAllowSearch = false);`
- L36 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L41 _protected prototype_ `virtual UObject* GetObjectToObserve() const;` — Should be implemented by derived classes to provide the object being observed
- L44 _protected prototype_ `void SetPropertyWindowContents(TArray<UObject*> Objects);`
- L47 _protected prototype_ `virtual TSharedRef<SWidget> PopulateSlot(TSharedRef<SWidget> PropertyEditorWidget);`
- L50 _protected member_ `TSharedPtr<class IDetailsView> PropertyView;` — Property viewing widget
- L54 _private member_ `TWeakObjectPtr<UObject> LastObservedObject;` — Cached object view
- L58 _private member_ `bool bAutoObserveObject;` — If true, GetObjectToObserve will be called every frame to update the object being displayed in the details panel Otherwise, users must call SetPropertyWindowContents manually

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API KISMETWIDGETS_API`
