# Plugins / ModelingEditorUI

- module root: `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI`
- headers: 13; symbols: 288
- symbol kinds: class=16, delegate=5, enum=2, enumerator=4, function=41, macro=7, member=91, namespace=6, prototype=110, struct=5, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, ContentBrowser, ContentBrowserData, CoreUObject, DeveloperSettings, EditorFramework, EditorWidgets, Engine, InputCore, InteractiveToolsFramework, LevelEditor, MeshModelingTools, MeshModelingToolsEditorOnlyExp, ModelingComponents, ModelingUI, Persona, Projects, Slate, SlateCore, StatusBar, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Private/ModelingEditorUIStyle.h` (Private)


#### class `FModelingEditorUIStyle`  
`class FModelingEditorUIStyle final : public FSlateStyleSet`  
_L12-68_
- inherits: `FSlateStyleSet`
- L16 _public function_ `FModelingEditorUIStyle() : FSlateStyleSet("ModelingEditorUIStyle")`
- L58 _public function_ `static FModelingEditorUIStyle& Get()`
- L64 _public function_ `~FModelingEditorUIStyle()`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Private/ModelingWidgets/SMeshLayers.h` (Private)


#### class `FMeshLayerElement`  
`class FMeshLayerElement`  
_L15-50_
- desc: Represents a single mesh layer within the List
- L18 _public prototype_ `static TSharedRef<ITableRow> MakeListRowWidget( const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FMeshLayerElement> InMeshLayerElement, TSharedPtr<SMeshLayersList> InMeshLayerListWidget);`
- L23 _public function_ `static TSharedRef<FMeshLayerElement> Make( const int32 InLayerIndex, const TSharedPtr<SMeshLayersList>& InLayerListWidget)`
- L31 _public function_ `int32 GetIndexInStack() const`
- L32 _public function_ `void SetIndexInStack(const int32 InIndex)`
- L34 _public function_ `TWeakPtr<SMeshLayersList> GetLayerList() const`
- L36 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);`
- L37 _public member_ `FOnRenameRequested OnRenameRequested;`
- L40 _private member_ `int32 IndexInStack = INDEX_NONE;`
- L41 _private member_ `TWeakPtr<SMeshLayersList> LayerListWidget;`
- L44 _private prototype_ `FMeshLayerElement() = default;` — hidden constructors, always use Make above
- L45 _private function_ `FMeshLayerElement( const int32 InIndexInStack, const TSharedPtr<SMeshLayersList>& InLayerListWidget) : IndexInStack(InIndexInStack), LayerListWidget(InLayerListWidget)`

#### class `SMeshLayersList`  
`class SMeshLayersList : public SListView<TSharedPtr<FMeshLayerElement>>`  
_L55-116_
- inherits: `SListView<TSharedPtr<FMeshLayerElement>>`
- desc: Represents the list of mesh layers - works within the MeshLayersStack widget
- L58 _public function_ `SLATE_BEGIN_ARGS(SMeshLayersList) : _InAllowAddRemove(true) , _InAllowReordering(true)`
- L61 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IMeshLayersController>, InController)`
- L69 _public prototype_ `void Construct(const FArguments& InArgs);`
- L71 _public prototype_ `TSharedRef<ITableRow> MakeListRowWidget(TSharedPtr<FMeshLayerElement> InLayerElement, const TSharedRef<STableViewBase>& OwnerTable);`
- L74 _public prototype_ `FReply OnDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — drag and drop operations
- L77 _public prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FMeshLayerElement> TargetLayer);`
- L81 _public prototype_ `FReply OnAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FMeshLayerElement> TargetLayer);`
- L88 _public prototype_ `void OnSelectionChanged(TSharedPtr<FMeshLayerElement> InLayer, ESelectInfo::Type SelectInfo) const;` — renaming
- L89 _public prototype_ `void OnItemClicked(TSharedPtr<FMeshLayerElement> InLayer);`
- L90 _public prototype_ `void RequestRenameSelectedLayer() const;`
- L94 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — delete layer from stack
- L95 _public prototype_ `void DeleteMeshLayer(TSharedPtr<FMeshLayerElement> LayerToDelete);`
- L98 _public prototype_ `void RefreshAndRestore();` — must be called after refresh
- L100 _public function_ `TArray<TSharedPtr<FMeshLayerElement>>& GetLayers()`
- L101 _public function_ `TWeakPtr<IMeshLayersController> GetController()`
- L103 _public function_ `bool GetAllowReordering() const`
- L104 _public function_ `bool GetAllowAddRemove() const`
- L107 _private member_ `bool bAllowReordering = true;`
- L108 _private member_ `bool bAllowAddRemove = true;`
- L111 _private member_ `TArray<TSharedPtr<FMeshLayerElement>> Layers;` — the layers contained in this list
- L113 _private member_ `TWeakPtr<IMeshLayersController> Controller;`
- L115 _private member_ `TWeakPtr<FMeshLayerElement> LastSelectedLayer;`

#### class `SMeshLayerItem`  
`class SMeshLayerItem : public STableRow<TSharedPtr<FMeshLayerElement>>`  
_L121-146_
- inherits: `STableRow<TSharedPtr<FMeshLayerElement>>`
- desc: Builds a UI element representing a single mesh layer
- L124 _public function_ `SLATE_BEGIN_ARGS(SMeshLayerItem)`
- L125 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SMeshLayersList>, InMeshLayersList) SLATE_ARGUMENT(TWeakPtr<FMeshLayerElement>, InMeshLayerElement) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable);`
- L132 _public prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type InCommitType) const;` — RENAMING op
- L133 _public prototype_ `FText GetName() const;`
- L136 _public member_ `static float LayersHorizontalPadding;`
- L137 _public member_ `static float LayersVerticalPadding;`
- L141 _private prototype_ `bool IsLayerEnabled() const;`
- L143 _private member_ `TWeakPtr<SMeshLayersList> ListView;`
- L144 _private member_ `TWeakPtr<FMeshLayerElement> Element;`
- L145 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditNameWidget;`

#### class `FMeshLayerStackDragDropOp`  
`class FMeshLayerStackDragDropOp : public FDecoratedDragDropOp`  
_L151-167_
- inherits: `FDecoratedDragDropOp`
- desc: Support for drag and drop operations within the MeshLayers
- L155 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMeshLayerStackDragDropOp, FDecoratedDragDropOp) static TSharedRef<FMeshLayerStackDragDropOp> New(TWeakPtr<FMeshLayerElement> InElement);`
- L159 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L161 _public prototype_ `static int32 GetIndexToMoveTo( const TSharedPtr<FMeshLayerElement>& InDraggedElement, const TSharedPtr<FMeshLayerElement>& InTargetElement, const EItemDropZone InDropZone);`
- L166 _public member_ `TWeakPtr<FMeshLayerElement> Element;`

#### Free symbols / members of external scopes

- L36 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingEditorUIModule.h` (Public)


#### class `FModelingEditorUIModule`  
`class FModelingEditorUIModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `TArray<FName> CustomizedClasses;`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/MeshLayersController.h` (Public)


#### class `IMeshLayersController`  
`class IMeshLayersController`  
_L16-95_
- L19 _public prototype_ `virtual ~IMeshLayersController() = default;`
- L23 _public function_ `virtual int32 AddMeshLayer()` — Adds a new mesh layer to the bottom of the stack @return the stack index of the new layer.
- L28 _public function_ `virtual bool RemoveMeshLayer(const int32 InLayerIndex)` — Remove the mesh layer at the given stack index. @param InLayerIndex the index of the layer to remove @return true if layer was found and removed, false otherwise
- L32 _public function_ `virtual void SetActiveLayer(const int32 InLayerIndex) const` — Sets the layer with the given index as the Active one @param InLayerIndex the index of the layer to set as active
- L36 _public function_ `virtual int32 GetActiveLayer() const` — Gets the layer that is currently active @return index of the currently active layer
- L41 _public function_ `virtual void SetLayerName(const int32 InLayerIndex, const FName InName) const` — Set the name of the layer at the given index in the stack. @param InName the new name to use @param InLayerIndex the index of the layer to be renamed
- L46 _public function_ `virtual FName GetLayerName(const int32 InLayerIndex) const` — Get the name of the layer at the given index in the stack. @param InLayerIndex the index of the layer to get the name of @return the name of the layer or None if the index was invalid
- L52 _public function_ `virtual void SetLayerWeight(const int32 InLayerIndex, const double InWeight, const EPropertyChangeType::Type ChangeType) const` — Sets the layer weight at the given index in the stack. @param InLayerIndex the index of the layer to set the weight of @param InWeight the new weight to set the layer to @param ChangeType the type of property change we want when setting the layer weight.
- L57 _public function_ `virtual double GetLayerWeight(const int32 InLayerIndex) const` — Gets the layer weight at the given index in the stack. @param InLayerIndex the index of the layer to get the weight of @return the weight of the layer or none if the index was invalid
- L61 _public prototype_ `virtual int32 GetNumMeshLayers() const = 0;` — Get the number of Layers in the stack. @return int, the number of layers
- L66 _public function_ `virtual bool MoveLayerInStack(int32 InLayerToMoveIndex, int32 InTargetIndex)` — Move the mesh layer at the given index to the target index. @param InLayerToMoveIndex the index of the layer to be moved @param InTargetIndex the index where the layer should be moved to
- L80 _public function_ `virtual void RefreshLayersStackView() const` — Refresh the view of the layer stack
- L83 _public function_ `virtual void SetProperties(UMeshSculptLayerProperties* InProperties)` — Connect the properties to be displayed and modified
- L85 _public function_ `virtual void SetProperties(UE::MeshPartition::UProjectMeshLayersModifier* InProperties)` — Connect the modifier to be displayed and modified
- L88 _public function_ `virtual TSharedPtr<SMeshLayersStack> GetLayerStackView()` — Retrieve the Stack View
- L90 _public function_ `virtual void SetLayerStackView(const TSharedPtr<SMeshLayersStack>& InLayersStackView)` — Set the stack view
- L94 _protected member_ `TSharedPtr<SMeshLayersStack> LayersStackView;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)
- L97 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshLayers, Warning, All);`
- L97 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshLayers, Warning, All);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/ModelingCustomizationUtil.h` (Public)


#### struct `UE::ModelingUI::ModelingUIConstants`  
`struct ModelingUIConstants`  
_L24-34_
- desc: Constants used for various standard Modeling UI gizmos/etc
- L27 _public member_ `static constexpr int DetailRowVertPadding = 4;` — top/bottom padding for detail row widgets, to be consistent w/ standard details panel
- L30 _public member_ `static constexpr int LabelWidgetMinPadding = 4;` — minimum padding between label and widget, for tight packing scenarios
- L33 _public member_ `static constexpr int MultiWidgetRowHorzPadding = 10;` — padding between multiple widgets in a horizontal row (eg for two widgets, this is the padding between them) (("widget" here is often label+widget))

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ModelingUI` (scope `UE`)
- L43 _prototype_ `TSharedRef<SBox> WrapInFixedWidthBox(TSharedRef<SWidget> SubWidget, int32 Width);` (scope `UE::ModelingUI`) — Wrap a widget in a fixed-width (ie non-resizable) box
- L50 _prototype_ `TSharedRef<SHorizontalBox> MakeFixedWidthLabelSliderHBox( TSharedPtr<IPropertyHandle> LabelHandle, TSharedPtr<SDynamicNumericEntry::FDataSource> SliderDataSource, int32 LabelFixedWidth);` (scope `UE::ModelingUI`) — Make an HBox for a label/slider pair, with the label in a fixed-width box (ie no resizing) The Label is taken from the existing label of a UProperty Handle
- L59 _prototype_ `TSharedRef<SHorizontalBox> MakeToggleSliderHBox( TSharedPtr<IPropertyHandle> BoolToggleHandle, FText ToggleLabelText, TSharedPtr<SDynamicNumericEntry::FDataSource> SliderDataSource, int32 ToggleFixedWidth);` (scope `UE::ModelingUI`) — Make an HBox for a label/slider pair, with the label in a fixed-width box (ie no resizing) The Label is taken from the existing label of a UProperty Handle
- L69 _prototype_ `TSharedRef<SHorizontalBox> MakeTwoWidgetDetailRowHBox( TSharedRef<SWidget> Widget1, TSharedRef<SWidget> Widget2, float FillWidth1 = 1.0f, float FillWidth2 = 1.0f);` (scope `UE::ModelingUI`) — Make an HBox for two widgets in a details row, with standard padding between them
- L79 _prototype_ `TSharedRef<SCheckBox> MakeBoolToggleButton( TSharedPtr<IPropertyHandle> BoolToggleHandle, FText ButtonLabelText, TFunction<void(bool)> ToggledCallback = [](bool) {}, int HorzPadding = 4);` (scope `UE::ModelingUI`) — Make a Button that can be clicked to toggle the value of a bool UProperty. When true, the button is highlighted
- L82 _function_ `TSharedPtr<IPropertyHandle> BoolToggleHandle, FText ButtonLabelText, TFunction<void(bool)> ToggledCallback = [](bool)` (scope `UE::ModelingUI`)
- L92 _prototype_ `void ProcessChildWidgetsByType( const TSharedRef<SWidget>& RootWidget, const FString& WidgetType, TFunction<bool(TSharedRef<SWidget>&)> ProcessFunc);` (scope `UE::ModelingUI`) — Run ProcessFunc over each child widget of WidgetType under RootWidget. @param RootWidget the root widget to search from. @param WidgetType the type of widgets to consider @param ProcessFunc the function to run on each instance of the widget. If return value is false, stop further processing.
- L104 _function_ `template<typename SlotType> void SetCustomWidgetErrorString( FText ErrorString, SlotType& Slot)` (scope `UE::ModelingUI`) — Create an error-string widget and add it to the Slot argument, to give the (developer) feedback about slate programming errors @param ErrorString error message @param Slot Object that supports bracket[SWidget] operator, such as any Box Slot object (eg can be called w/ SCompoundWidget::ChildSlot as the Slot argument)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/SComboPanel.h` (Public)


#### class `SComboPanel`  
`class SComboPanel : public SCompoundWidget`  
_L26-137_
- inherits: `SCompoundWidget`
- desc: SComboPanel provides a ComboBox-type interface but instead of a drop-down list, a STileView panel ("Flyout") is shown with an icon for each selectable item. Various options for the ComboButton are available, eg a single large icon, icon with adjacent label, etc. Client provides a TArray<TSharedPtr<FComboPanelItem>> via the .ListItems() argument, where SComboPanel::FComboPanelItem contains the label, icon, and integer identifier for each selectable option.
- L49 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnActiveItemChanged, TSharedPtr<FComboPanelItem>);` — Event that fires when selection changes
- L50 _public typedef_ `typedef FOnActiveItemChanged FOnSelectionChanged;`
- L54 _public function_ `SLATE_BEGIN_ARGS( SComboPanel ) : _ComboButtonTileSize(50, 50) , _FlyoutTileSize(85, 85) , _FlyoutSize(600, 400) , _OnSelectionChanged() , _ComboDisplayType(EComboDisplayType::LargeIcon) , _InitialSelectionIndex(0)`
- L65 _public prototype_ `SLATE_ARGUMENT(FVector2D, ComboButtonTileSize) SLATE_ARGUMENT(FVector2D, FlyoutTileSize) SLATE_ARGUMENT(FVector2D, FlyoutSize) SLATE_ARGUMENT( TArray<TSharedPtr<FComboPanelItem>> , ListItems ) SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_ATTRIBUTE( FText, FlyoutHeaderText ) SLATE_ARGUMENT(EComboDisplayType, ComboDisplayType) SLATE_ARGUMENT(int, InitialSelectionIndex) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — The size of the combo button icon tile
- L103 _public prototype_ `void SetSelectionIndex(int InSelectionIndex);` — Sets the currently selected index without user interaction. @param InSelectionIndex The new selection index for the widget
- L106 _protected member_ `FVector2D ComboButtonTileSize;`
- L107 _protected member_ `FVector2D FlyoutTileSize;`
- L108 _protected member_ `FVector2D FlyoutSize;`
- L111 _protected member_ `TArray<TSharedPtr<FComboPanelItem>> Items;` — Pointer to the array of data items that we are observing
- L114 _protected member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate to invoke when selection changes.
- L117 _protected prototype_ `virtual TSharedRef<ITableRow> CreateFlyoutIconTile( TSharedPtr<FComboPanelItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — STileView functions
- L120 _protected prototype_ `virtual void FlyoutSelectionChanged( TSharedPtr<FComboPanelItem> SelectedItemIn, ESelectInfo::Type SelectInfo);`
- L126 _protected prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — SComboButton functions
- L127 _protected prototype_ `void OnMenuOpenChanged(bool bOpen);`
- L130 _protected member_ `TSharedPtr<FSlateBrush> MissingIcon;` — Icon to use when Item does not have a valid icon
- L132 _protected member_ `TSharedPtr<FComboPanelItem> SelectedItem;`
- L134 _protected member_ `TSharedPtr<SComboButton> ComboButton;`
- L135 _protected member_ `TSharedPtr<STileView<TSharedPtr<FComboPanelItem>>> TileView;`
- L136 _protected member_ `TSharedPtr<SBox> TileViewContainer;`

#### struct `SComboPanel::FComboPanelItem`  
`struct FComboPanelItem`  
_L30-38_
- desc: Item in the Combo Flyout (ie selectable option).
- L33 _public member_ `FText Name;` — Text label shown as overlay on the icon
- L35 _public member_ `const FSlateBrush* Icon = nullptr;` — Icon
- L37 _public member_ `int Identifier = 0;` — Integer identifier. Must be unique for each Item.

#### enum `SComboPanel::EComboDisplayType`  
`enum class EComboDisplayType`  
_L41-46_
- desc: EComboDisplayType is used to specify the widgets in the ComboButton (ie non-expanded widget)
- L44 _public enumerator_ `LargeIcon` — Display a single large icon with overlay label, the same as is shown in the flyout
- L45 _public enumerator_ `IconAndLabel`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGEDITORUI_API`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FOnActiveItemChanged, TSharedPtr<FComboPanelItem>);` — Event that fires when selection changes

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/SDynamicNumericEntry.h` (Public)


#### class `SDynamicNumericEntry`  
`class SDynamicNumericEntry : public SCompoundWidget`  
_L17-68_
- inherits: `SCompoundWidget`
- desc: SNumericEntryBox wrapper that supports custom Get/SetValue and dynamic value/UI range
- L34 _public function_ `SLATE_BEGIN_ARGS( SDynamicNumericEntry ) : _MaxNumFloatDigits(2)`
- L39 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FDataSource>, Source ) SLATE_ARGUMENT( int, MaxNumFloatDigits ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L54 _public prototype_ `static TSharedPtr<FDataSource> MakeSimpleDataSource(TSharedPtr<IPropertyHandle> PropertyHandle, TInterval<float> ValueRange, TInterval<float> UIRange);`
- L57 _protected member_ `TSharedPtr<FDataSource> Source;`
- L58 _protected member_ `TSharedPtr<SNumericEntryBox<float>> NumericEntry;`
- L59 _protected member_ `TSharedPtr<TDefaultNumericTypeInterface<float>> TypeInterface;`
- L61 _protected member_ `float LastSliderCommittedValue;`
- L62 _protected prototype_ `void OnValueChanged(float NewValue);`
- L63 _protected prototype_ `void OnValueCommitted(float NewValue, ETextCommit::Type CommitInfo);`
- L65 _protected member_ `bool bIsUsingSlider = false;`
- L66 _protected prototype_ `void OnBeginSliderMovement();`
- L67 _protected prototype_ `void OnEndSliderMovement(float NewValue);`

#### struct `SDynamicNumericEntry::FDataSource`  
`struct FDataSource`  
_L24-30_
- L26 _public member_ `TFunction<void(float, EPropertyValueSetFlags::Type)> SetValue;`
- L27 _public member_ `TFunction<float()> GetValue;`
- L28 _public member_ `TFunction<TInterval<float>()> GetValueRange;`
- L29 _public member_ `TFunction<TInterval<float>()> GetUIRange;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGEDITORUI_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/SMeshLayersStack.h` (Public)


#### class `SMeshLayersStack`  
`class SMeshLayersStack : public SCompoundWidget, public FEditorUndoClient`  
_L15-34_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: top level view of a stack of mesh layers shows the main menu for adding layers to the stack, and a list view of layers
- L19 _public function_ `SLATE_BEGIN_ARGS(SMeshLayersStack) : _InAllowAddRemove(true) , _InAllowReordering(true)`
- L22 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IMeshLayersController>, InController) SLATE_ARGUMENT(bool, InAllowAddRemove) SLATE_ARGUMENT(bool, InAllowReordering) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IMeshLayersController>& InController);`
- L29 _public prototype_ `void RefreshStackView() const;`
- L32 _private member_ `TWeakPtr<IMeshLayersController> Controller;`
- L33 _private member_ `TSharedPtr<SMeshLayersList> ListView;`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/STickDelegateWidget.h` (Public)


#### class `STickDelegateWidget`  
`class STickDelegateWidget : public SCompoundWidget`  
_L17-35_
- inherits: `SCompoundWidget`
- desc: Simple widget that calls its OnTickDelegate in its Tick function, to allow for custom tick behavior via composition instead of having to create a class and override the method, for instance when creating custom slate in-line somewhere.
- L21 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnTick, const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L23 _public function_ `SLATE_BEGIN_ARGS(STickDelegateWidget)`
- L24 _public prototype_ `SLATE_EVENT(FOnTick, OnTickDelegate) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L34 _protected member_ `FOnTick OnTickDelegate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGEDITORUI_API`
- L21 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnTick, const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/SToolInputAssetComboPanel.h` (Public)


#### enum `EThumbnailDisplayMode`  
`enum class EThumbnailDisplayMode`  
_L26-30_
- L28 _public enumerator_ `AssetThumbnail`
- L29 _public enumerator_ `AssetName`

#### class `SToolInputAssetComboPanel`  
`class SToolInputAssetComboPanel : public SCompoundWidget`  
_L45-202_
- inherits: `SCompoundWidget`
- desc: SToolInputAssetComboPanel provides a similar UI to SComboPanel but specifically for picking Assets. The standard widget is a SComboButton that displays a thumbnail of the selected Asset, and on click a flyout panel is shown that has an Asset Picker tile view, as well as (optionally) a list of recently-used Assets, and also Collection-based filters. Drag-and-drop onto the SComboButton is also supported, and the "selected Asset" can be mapped to/from a PropertyHandle. However note that a PropertyHandle is *not* required, each time the selection is modified the OnSelectionChanged(AssetData) delegate will also fire. Note that "No Selection" is valid option by default
- L49 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectedAssetChanged, const FAssetData& AssetData);`
- L87 _public function_ `SLATE_BEGIN_ARGS( SToolInputAssetComboPanel ) : _ComboButtonTileSize(50, 50) , _FlyoutTileSize(85, 85) , _FlyoutSize(600, 400) , _AssetClassType(0) , _OnSelectionChanged() , _InitiallySelectedAsset() , _AssetThumbnailLabel(EThumbnailLabel::NoLabel) , _bForceShowEngineContent(false) , _bForceShowPluginContent(false) , _AssetViewType(EAssetViewType::Tile) , _ThumbnailDisplayMode(EThumbnailDisplayMode::AssetThumbnail)`
- L103 _public prototype_ `SLATE_ARGUMENT(FVector2D, ComboButtonTileSize) SLATE_ARGUMENT(FVector2D, FlyoutTileSize) SLATE_ARGUMENT(FVector2D, FlyoutSize) SLATE_ARGUMENT( TSharedPtr<IPropertyHandle>, Property ) SLATE_ARGUMENT( FText, ToolTipText ) SLATE_ARGUMENT( UClass*, AssetClassType ) SLATE_ARGUMENT(TSharedPtr<IRecentAssetsProvider>, RecentAssetsProvider) SLATE_ARGUMENT(TArray<FNamedCollectionList>, CollectionSets) SLATE_EVENT( FOnSelectedAssetChanged, OnSelectionChanged ) SLATE_ARGUMENT( FAssetData, InitiallySelectedAsset) SLATE_ARGUMENT( EThumbnailLabel::Type, AssetThumbnailLabel) SLATE_ARGUMENT(bool, bForceShowEngineContent) SLATE_ARGUMENT(bool, bForceShowPluginContent) SLATE_ARGUMENT(EAssetViewType::Type, AssetViewType)` — The size of the combo button icon tile
- L158 _public prototype_ `void RefreshThumbnailFromProperty();` — refresh the thumbnail using the AssetComboPanel's Property
- L160 _public prototype_ `void RefreshThumbnail(const FAssetData& InAssetData) const;` — refresh the thumbnail using provided AssetData, for cases where Property may not be available
- L164 _protected member_ `FVector2D ComboButtonTileSize;`
- L165 _protected member_ `FVector2D FlyoutTileSize;`
- L166 _protected member_ `FVector2D FlyoutSize;`
- L167 _protected member_ `TSharedPtr<IPropertyHandle> Property;`
- L168 _protected member_ `UClass* AssetClassType = nullptr;`
- L169 _protected member_ `EThumbnailDisplayMode ThumbnailDisplayMode;`
- L173 _protected member_ `FOnSelectedAssetChanged OnSelectionChanged;` — Delegate to invoke when selection changes.
- L175 _protected member_ `TSharedPtr<SComboButton> ComboButton;`
- L176 _protected member_ `TSharedPtr<FAssetThumbnailPool> ThumbnailPool;`
- L177 _protected member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;`
- L178 _protected member_ `TSharedPtr<SBorder> ThumbnailBorder;`
- L180 _protected member_ `TSharedPtr<IRecentAssetsProvider> RecentAssetsProvider;`
- L187 _protected member_ `TArray<TSharedPtr<FRecentAssetInfo>> RecentAssetData;`
- L189 _protected member_ `TArray<TSharedPtr<FAssetThumbnail>> RecentThumbnails;`
- L190 _protected member_ `TArray<TSharedPtr<SBox>> RecentThumbnailWidgets;`
- L192 _protected prototype_ `void UpdateRecentAssets();`
- L194 _protected prototype_ `virtual void NewAssetSelected(const FAssetData& AssetData);`
- L195 _protected prototype_ `virtual FReply OnAssetThumbnailDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L197 _protected prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForRecentList(TSharedPtr<FRecentAssetInfo> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L199 _protected member_ `TArray<FNamedCollectionList> CollectionSets;`
- L200 _protected member_ `int32 ActiveCollectionSetIndex = -1;`
- L201 _protected prototype_ `TSharedRef<SWidget> MakeCollectionSetsButtonPanel(TSharedRef<SToolInputAssetPicker> AssetPickerView);`

#### struct `SToolInputAssetComboPanel::FNamedCollectionList`  
`struct FNamedCollectionList`  
_L52-72_
- desc: List of Collections with associated Name, used to provide pickable Collection filters
- L54 _public prototype_ `FNamedCollectionList() = default;`
- L58 _public prototype_ `FNamedCollectionList(const FNamedCollectionList&) = default;`
- L59 _public prototype_ `FNamedCollectionList(FNamedCollectionList&&) = default;`
- L61 _public prototype_ `FNamedCollectionList& operator=(const FNamedCollectionList&) = default;`
- L62 _public prototype_ `FNamedCollectionList& operator=(FNamedCollectionList&&) = default;`
- L66 _public member_ `FString Name;`
- L68 _public member_ `TArray<FCollectionRef> Collections;`
- L71 _public member_ `TArray<FCollectionNameType> CollectionNames;` — `UE_DEPRECATED(5.6, "Use Collections instead.")`

#### class `SToolInputAssetComboPanel::IRecentAssetsProvider`  
`class IRecentAssetsProvider`  
_L75-83_
- desc: IRecentAssetsProvider allows the Client to specify a set of "recently-used" Assets which the SToolInputAssetComboPanel will try to update as the selected Asset changes
- L78 _public prototype_ `virtual ~IRecentAssetsProvider() = default;`
- L80 _public prototype_ `virtual TArray<FAssetData> GetRecentAssetsList() = 0;` — SToolInputAssetComboPanel calls this to get the recent-assets list each time the flyout is opened
- L82 _public prototype_ `virtual void NotifyNewAsset(const FAssetData& NewAsset) = 0;` — SToolInputAssetComboPanel calls this whenever the selected asset changes

#### struct `SToolInputAssetComboPanel::FRecentAssetInfo`  
`struct FRecentAssetInfo`  
_L182-186_
- L184 _public member_ `int Index;`
- L185 _public member_ `FAssetData AssetData;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MODELINGEDITORUI_API`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectedAssetChanged, const FAssetData& AssetData);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/SToolInputAssetPicker.h` (Public)


#### class `SToolInputAssetPicker`  
`class SToolInputAssetPicker : public SCompoundWidget`  
_L40-136_
- inherits: `SCompoundWidget`
- desc: SToolInputAssetPicker is designed to support Asset picking in Modeling Tools, where the Assets in question are input parameters/options to Tools, eg such as a brush alpha texture for use in a Painting/Sculpting Tool. Implementation is derived from SAssetPicker (private class in the ContentBrowser module). However many optional features have been stripped out as they are not relevant in the Modeling-Tool Parameters context. Most settings are provided via the FAssetPickerConfig, which is passed to an SAssetView internally. Unless you are really certain you need to use this class directly, it's likely that you are looking for SToolInputAssetComboPanel, which provides a combobox/flyout-style widget suitable for user interface panels.
- L43 _public function_ `SLATE_BEGIN_ARGS( SToolInputAssetPicker )`
- L46 _public prototype_ `SLATE_ARGUMENT(FAssetPickerConfig, AssetPickerConfig) SLATE_END_ARGS() virtual ~SToolInputAssetPicker();` — A struct containing details about how the asset picker should behave
- L53 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L56 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget implementation
- L60 _public function_ `const TSharedPtr<SAssetView>& GetAssetView() const` — Return the associated AssetView
- L66 _public prototype_ `virtual void UpdateAssetSourceCollections(TArray<FCollectionRef> Collections);` — Update the set of input Assets to be only based on the given set of Collections (or all Assets, if the Collections list is empty)
- L69 _public prototype_ `virtual void UpdateAssetSourceCollections(TArray<FCollectionNameType> Collections);` — `UE_DEPRECATED(5.6, "Use the FCollectionRef overload instead.")`
- L73 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct( double InCurrentTime, float InDeltaTime );` — Focuses the search box post-construct
- L76 _private prototype_ `FReply HandleKeyDownFromSearchBox(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — Special case handling for SAssetSearchBox key commands
- L79 _private prototype_ `void SetSearchBoxText(const FText& InSearchText);` — Called when the editable text needs to be set or cleared
- L82 _private prototype_ `void OnSearchBoxChanged(const FText& InSearchText);` — Called by the editable text control when the search text is changed by the user
- L85 _private prototype_ `void OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);` — Called by the editable text control when the user commits a text change
- L88 _private prototype_ `FReply OnNoneButtonClicked();` — Handler for when the "None" button is clicked
- L91 _private prototype_ `void HandleItemSelectionChanged(const FContentBrowserItem& InSelectedItem, ESelectInfo::Type InSelectInfo);` — Handle forwarding picking events. We wrap OnAssetSelected here to prevent 'Direct' selections being identified as user actions
- L94 _private prototype_ `void HandleItemsActivated(TArrayView<const FContentBrowserItem> ActivatedItems, EAssetTypeActivationMethod::Type ActivationMethod);` — Handler for when the user double clicks, presses enter, or presses space on an asset
- L97 _private prototype_ `void RefreshAssetView(bool bRefreshSources);` — Forces a refresh
- L100 _private prototype_ `FText GetHighlightedText() const;` — @return The text to highlight on the assets
- L105 _private member_ `TSharedPtr<FAssetFilterCollectionType> FrontendFilters;` — The list of FrontendFilters currently applied to the asset view
- L108 _private member_ `TSharedPtr<SAssetView> AssetViewPtr;` — The asset view widget
- L111 _private member_ `TSharedPtr<SAssetSearchBox> SearchBoxPtr;` — The search box
- L114 _private member_ `FOnAssetSelected OnAssetSelected;` — Called to when an asset is selected or the none button is pressed
- L117 _private member_ `FOnAssetEnterPressed OnAssetEnterPressed;` — Called when enter is pressed while an asset is selected
- L120 _private member_ `FOnAssetsActivated OnAssetsActivated;` — Called when any number of assets are activated
- L123 _private member_ `bool bPendingFocusNextFrame;` — True if the search box will take keyboard focus next frame
- L126 _private member_ `TSharedPtr< FAssetFilterCollectionType > FilterCollection;` — Filters needed for filtering the assets
- L127 _private member_ `TSharedPtr<FAssetTextFilter> TextFilter;`
- L129 _private member_ `EAssetTypeCategories::Type DefaultFilterMenuExpansion;`
- L132 _private member_ `FAssetViewContentSources CurrentContentSources;` — The sources data currently used by the picker
- L135 _private member_ `FARFilter CurrentBackendFilter;` — Current filter we are using, needed reset asset view after we have custom filtered

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MODELINGEDITORUI_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/ModelingWidgets/SculptLayersController.h` (Public)


#### class `FSculptLayersController`  
`class FSculptLayersController : public IMeshLayersController`  
_L9-41_
- inherits: `IMeshLayersController`
- L12 _public prototype_ `FSculptLayersController();`
- L16 _public function_ `UMeshSculptLayerProperties* GetProperties() const` — get access to the Properties. Warning: do not make modifications to the asset directly, use the controller API
- L17 _public function_ `virtual void SetProperties(UMeshSculptLayerProperties* InProperties) override`
- L23 _private member_ `TObjectPtr<UMeshSculptLayerProperties> Properties = nullptr;`
- L27 _public prototype_ `virtual int32 AddMeshLayer() override;`
- L28 _public prototype_ `virtual bool RemoveMeshLayer(const int32 InLayerIndex) override;`
- L30 _public prototype_ `virtual void SetActiveLayer(const int32 InLayerIndex) const override;`
- L31 _public prototype_ `virtual int32 GetActiveLayer() const override;`
- L33 _public prototype_ `virtual void SetLayerName(const int32 InLayerIndex, const FName InName) const override;`
- L34 _public prototype_ `virtual FName GetLayerName(const int32 InLayerIndex) const override;`
- L35 _public prototype_ `virtual void SetLayerWeight(const int32 InLayerIndex, const double InWeight, const EPropertyChangeType::Type ChangeType) const override;`
- L36 _public prototype_ `virtual double GetLayerWeight(const int32 InLayerIndex) const override;`
- L38 _public prototype_ `virtual int32 GetNumMeshLayers() const override;`
- L39 _public prototype_ `virtual bool MoveLayerInStack(int32 InLayerToMoveIndex, int32 InTargetIndex) override;`
- L40 _public prototype_ `virtual void RefreshLayersStackView() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MODELINGEDITORUI_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingEditorUI/Public/STransformGizmoNumericalUIOverlay.h` (Public)


#### class `STransformGizmoNumericalUIOverlay`  
`class STransformGizmoNumericalUIOverlay : public SCompoundWidget`  
_L31-141_
- inherits: `SCompoundWidget`
- desc: An overlay that contains a draggable panel that mirrors the values of a UCombinedTransformGizmo and allows them to be settable by scrubbing the values or typing. To use it, just add the overlay to your viewport and call BindToGizmoContextObject (sometime after TransformGizmoUtil::RegisterTransformGizmoContextObject has already been called). This will bind any gizmos subsequently created through TransformGizmoUtil to the panel. MakeNumericalUISubMenu creates a submenu that can be slotted somewhere to enable/disable the UI panel or to reset its position in the viewport.
- L35 _public function_ `SLATE_BEGIN_ARGS(STransformGizmoNumericalUIOverlay) : _bPositionRelativeToBottom(true) , _DefaultLeftPadding(15) , _DefaultVerticalPadding(15) , _TranslationScrubSensitivity(1)`
- L44 _public prototype_ `SLATE_ARGUMENT(bool, bPositionRelativeToBottom)` — When true (the default) the panel is positioned by measuring a distance from the bottom of the viewport, and resizing the viewport will keep that distance the same.
- L61 _public prototype_ `virtual ~STransformGizmoNumericalUIOverlay();`
- L67 _public prototype_ `bool BindToGizmoContextObject(UInteractiveToolsContext* ToolsContext);` — Binding to the context object makes it so that the overlay gets attached to any subsequently created transform gizmos.
- L69 _public function_ `virtual bool IsEnabled()`
- L70 _public prototype_ `virtual void SetEnabled(bool bEnabledIn);`
- L75 _public prototype_ `virtual void ResetPositionInViewport();` — Resets the position of the draggable UI box in the overlay to its default.
- L80 _public prototype_ `virtual void MakeNumericalUISubMenu(FMenuBuilder& MenuBuilder);` — Creates a submenu to deal with the numerical UI, for placement in some toolbar by the mode/editor.
- L85 _public prototype_ `virtual void Reset();` — Clears all gizmo bindings
- L91 _public prototype_ `virtual void SetCustomDisplayConversionFunctions( TFunction<FVector3d(const FVector3d& InternalValue)> InternalToDisplayConversionIn, TFunction<FVector3d(const FVector3d& DisplayValue)> DisplayToInternalConversionIn, double TranslationScrubSensitivityIn = 1.0);` — Allows the positional (translation) copmonent to be displayed in different units than the gizmo world, for instance in a UV editor where the world coordinates are not actually 0 to 1.
- L103 _public prototype_ `virtual void SetDefaultLocalReferenceTransform(const TOptional<FTransform>& CustomReferenceTransform);` — After calling this function, any newly initialized gizmos will be given the provided reference transform as their custom reference transform. This mainly meant to allow the UI to be used in a 2D situation (e.g. UV editor) where the gizmos only have two axes. Normally, we only allow delta mode in such a case, but the 2D editor can provide the used plane's reference transform to allow the gizmos to be usable in destination mode as well.
- L108 _protected member_ `FVector3d DisplayTranslation;` — Currently displayed values
- L109 _protected member_ `FVector3d DisplayEulerAngles;`
- L110 _protected member_ `FVector3d DisplayScale;`
- L113 _protected member_ `TSharedPtr<FTransformGizmoDataBinder> DataBinder;` — Holds the functionality that binds the displayed values to the gizmo.
- L115 _protected member_ `TSharedPtr<UE::ToolWidgets::SDraggableBoxOverlay> DraggableBoxOverlay;`
- L118 _protected member_ `TSharedPtr<SBorder> WidgetContents;` — The part of the UI that changes when a different gizmo is chosen
- L121 _protected member_ `float DefaultLeftPadding = 15.0f;` — The values to which the UI positioning is reset if asked
- L122 _protected member_ `float DefaultVerticalPadding = 75.0f;`
- L125 _protected prototype_ `TSharedRef<SWidget> CreateWidgetForGizmo(ETransformGizmoSubElements GizmoElements);` — Helpers for building the UI when changing gizmo
- L126 _protected prototype_ `SNumericEntryBox<double>::FArguments CreateComponentBaseArgs(FVector3d& TargetVector, int ComponentIndex, TAttribute<bool> IsEnabled);`
- L127 _protected prototype_ `TSharedRef<SWidget> CreateTranslationComponent(int ComponentIndex, TAttribute<bool> IsEnabled);`
- L128 _protected prototype_ `TSharedRef<SWidget> CreateRotationComponent(int ComponentIndex, TAttribute<bool> IsEnabled);`
- L129 _protected prototype_ `TSharedRef<SWidget> CreateScaleComponent(int ComponentIndex, TAttribute<bool> IsEnabled);`
- L133 _protected member_ `EToolContextCoordinateSystem LastCoordinateSystem;` — We have to respond to coordinate system changes for the gizmo, and to do that we need to be able to poll on tick, since we don't get notifications about it.
- L134 _protected prototype_ `void OnTickWidget(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L137 _protected member_ `double TranslationScrubSensitivity = 1;` — Modifier for scrubbing translation, if we're using custom display functions.
- L139 _protected member_ `bool bIsEnabled = true;`
- L140 _protected member_ `bool bPositionRelativeToBottom = true;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGEDITORUI_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ToolWidgets` (scope `UE`)
