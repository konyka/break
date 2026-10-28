# Plugins / ColorGradingEditor

- module root: `Plugins/Editor/ColorGrading/Source/ColorGradingEditor`
- headers: 19; symbols: 415
- symbol kinds: class=17, delegate=9, function=50, macro=5, member=110, namespace=1, prototype=214, struct=7, typedef=2
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, CinematicCamera, Core, CoreUObject, DetailCustomizations, EditorStyle, Engine, InputCore, LevelEditor, PropertyEditor, PropertyPath, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: AdvancedWidgets, ObjectMixerEditor, SceneOutliner

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/ColorGradingCommands.h` (Private)


#### class `FColorGradingCommands`  
`class FColorGradingCommands : public TCommands<FColorGradingCommands>`  
_L11-27_
- inherits: `TCommands<FColorGradingCommands>`
- desc: Command list for the color grading drawer
- L15 _public function_ `FColorGradingCommands() : TCommands<FColorGradingCommands>(TEXT("ColorGrading"), NSLOCTEXT("Contexts", "ColorGrading", "Display Cluster Color Grading"), NAME_None, FColorGradingEditorStyle::Get().GetStyleSetName())`
- L20 _public prototype_ `virtual void RegisterCommands() override;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> SaturationColorWheelVisibility;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ContrastColorWheelVisibility;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ColorWheelSliderOrientationHorizontal;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ColorWheelSliderOrientationVertical;`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/ColorGradingEditorModule.h` (Private)


#### class `FColorGradingEditorModule`  
`class FColorGradingEditorModule : public IColorGradingEditor`  
_L16-43_
- inherits: `IColorGradingEditor`
- desc: Display Cluster Color Grading module
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public function_ `virtual FName GetColorGradingTabSpawnerId() const override`
- L27 _private prototype_ `void OnFEngineLoopInitComplete();` — Called right before the engine starts ticking
- L30 _private prototype_ `void RegisterLevelEditorLayout(FLayoutExtender& Extender);` — Register the level editor layout extension for the Color Grading panel
- L33 _private prototype_ `void RegisterMenuItem();` — Register the menu item that opens the Color Grading panel
- L36 _private prototype_ `TSharedRef<SDockTab> SpawnMainPanelTab(const FSpawnTabArgs& Args);` — Spawn the tab containing the Color Grading panel
- L39 _private member_ `static const FName ColorGradingPanelTabId;` — ID to uniquely identify the Color Grading panel tab
- L42 _private member_ `TSharedPtr<SColorGradingPanel> MainPanel;` — The main dockable color grading panel

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/ColorGradingEditorStyle.h` (Private)


#### class `FColorGradingEditorStyle`  
`class FColorGradingEditorStyle final : public FSlateStyleSet`  
_L14-44_
- inherits: `FSlateStyleSet`
- desc: Styleset for the color grading editor UI elements
- L18 _public function_ `FColorGradingEditorStyle() : FSlateStyleSet("ColorGradingEditorStyle")`
- L34 _public function_ `virtual ~FColorGradingEditorStyle()`
- L39 _public function_ `static FColorGradingEditorStyle& Get()`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/ColorGradingMixerObjectFilter.h` (Private)


#### class `UColorGradingMixerObjectFilter`  
`class UColorGradingMixerObjectFilter : public UObjectMixerObjectFilter`  
_L12-79_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew)`
- inherits: `UObjectMixerObjectFilter`
- L17 _public prototype_ `virtual TSet<UClass*> GetObjectClassesToFilter() const override;`
- L18 _public prototype_ `virtual TSet<TSubclassOf<AActor>> GetObjectClassesToPlace() const override;`
- L19 _public prototype_ `virtual TArray<AActor*> FindAssociatedActors(AActor* InActor) const override;`
- L20 _public prototype_ `virtual TArray<FObjectMixerEditorActorSubObject> GetActorSubObjects(AActor* InActor) const override;`
- L21 _public prototype_ `virtual bool IsActorAssociated(AActor* Actor, AActor* AssociatedActor) const override;`
- L22 _public prototype_ `virtual bool HasCustomDropHandling(const ISceneOutlinerTreeItem& DropTarget) const override;`
- L23 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L24 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L25 _public prototype_ `virtual TSet<FName> GetPropertiesThatRequireListRefresh() const override;`
- L26 _public prototype_ `virtual void OnContextMenuContextCreated(FToolMenuContext& Context) const override;`
- L28 _public function_ `virtual bool GetShowTransientObjects() const override`
- L33 _public function_ `virtual TSet<FName> GetColumnsToShowByDefault() const override`
- L38 _public function_ `virtual TSet<FName> GetColumnsToExclude() const`
- L43 _public function_ `virtual TSet<FName> GetForceAddedColumns() const override`
- L48 _public function_ `virtual bool ShouldIncludeUnsupportedProperties() const override`
- L53 _public function_ `virtual bool ShouldAllowHybridRows() const override`
- L61 _public function_ `virtual bool ShouldAllowColumnCustomizationByUser() const override`
- L66 _public function_ `virtual EObjectMixerInheritanceInclusionOptions GetObjectMixerPropertyInheritanceInclusionOptions() const override`
- L71 _public function_ `virtual EObjectMixerInheritanceInclusionOptions GetObjectMixerPlacementClassInclusionOptions() const override`
- L78 _private prototype_ `UObject* GetObjectForTreeItem(const ISceneOutlinerTreeItem& TreeItem) const;` — Given a tree item, get the object it represents

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COLORGRADINGEDITOR_API`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/ColorGradingMixerSelectionInterface.h` (Private)


#### class `FColorGradingMixerSelectionInterface`  
`class FColorGradingMixerSelectionInterface : public FLevelEditorObjectMixerSelectionInterface`  
_L10-26_
- inherits: `FLevelEditorObjectMixerSelectionInterface`
- desc: Custom selection interface for the color grading drawer's mixer to provide hooks for receiving selection events for actor sub-objects
- L13 _public prototype_ `FColorGradingMixerSelectionInterface();`
- L16 _public prototype_ `virtual void SelectSubObjects(const TArray<UObject*>& InSelectedSubObjects, bool bShouldSelect, bool bSelectEvenIfHidden) override;`
- L17 _public prototype_ `virtual TArray<UObject*> GetSelectedSubObjects() const override;`
- L21 _private prototype_ `void OnEditorSelectionChanged();`
- L25 _private member_ `TArray<TSharedPtr<IColorGradingMixerSelectionHandler>> SelectionHandlers;` — A list of intantiated selection handlers that will process selection of actor sub-objects

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/DataModelGenerators/ColorGradingDataModelGenerator_CameraActor.h` (Private)


#### class `FColorGradingDataModelGenerator_CameraActor`  
`class FColorGradingDataModelGenerator_CameraActor: public IColorGradingEditorDataModelGenerator`  
_L11-25_
- inherits: `IColorGradingEditorDataModelGenerator`
- desc: Color Grading Data Model Generator for the ACameraActor actor class
- L14 _public prototype_ `static TSharedRef<IColorGradingEditorDataModelGenerator> MakeInstance();`
- L17 _public prototype_ `virtual void Initialize(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L18 _public prototype_ `virtual void Destroy(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L19 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FColorGradingEditorDataModel& OutColorGradingDataModel) override;`
- L24 _private prototype_ `void AddPropertyToColorGradingElement(const TSharedPtr<IPropertyHandle>& PropertyHandle, FColorGradingEditorDataModel::FColorGradingElement& ColorGradingElement);` — Add a color grading property to the a color grading element, assigning it to the appropriate variable based on its metadata

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/DataModelGenerators/ColorGradingDataModelGenerator_PostProcessVolume.h` (Private)


#### class `FColorGradingDataModelGenerator_PostProcessVolume`  
`class FColorGradingDataModelGenerator_PostProcessVolume: public IColorGradingEditorDataModelGenerator`  
_L11-24_
- inherits: `IColorGradingEditorDataModelGenerator`
- desc: Color Grading Data Model Generator for the APostProcessVolume actor class
- L14 _public prototype_ `static TSharedRef<IColorGradingEditorDataModelGenerator> MakeInstance();`
- L17 _public prototype_ `virtual void Initialize(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L18 _public prototype_ `virtual void Destroy(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L19 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FColorGradingEditorDataModel& OutColorGradingDataModel) override;`
- L23 _private prototype_ `void AddPropertyToColorGradingElement(const TSharedPtr<IPropertyHandle>& PropertyHandle, FColorGradingEditorDataModel::FColorGradingElement& ColorGradingElement);`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/DetailView/FColorGradingDetailTreeItem.h` (Private)


#### class `FColorGradingDetailTreeItem`  
`class FColorGradingDetailTreeItem : public TSharedFromThis<FColorGradingDetailTreeItem>`  
_L14-84_
- inherits: `TSharedFromThis<FColorGradingDetailTreeItem>`
- desc: A wrapper used to abstract FDetailTreeNode, which is a private abstract class defined in PropertyEditor/Private
- L17 _public function_ `FColorGradingDetailTreeItem(const TSharedPtr<FDetailTreeNode>& InDetailTreeNode) : DetailTreeNode(InDetailTreeNode)`
- L22 _public prototype_ `void Initialize(const FOnFilterDetailTreeNode& NodeFilter);` — Initializes the detail tree item, creating any child tree items needed
- L25 _public function_ `TWeakPtr<FColorGradingDetailTreeItem> GetParent() const` — Gets the parent detail tree item of this item
- L28 _public function_ `bool HasChildren() const` — Gets whether this tree item has any children
- L31 _public prototype_ `void GetChildren(TArray<TSharedRef<FColorGradingDetailTreeItem>>& OutChildren) const;` — Gets the list of child tree items of this item
- L34 _public prototype_ `TWeakPtr<IDetailTreeNode> GetDetailTreeNode() const;` — Gets the underlying IDetailTreeNode this detail tree item wraps
- L37 _public function_ `TSharedPtr<IPropertyHandle> GetPropertyHandle() const` — Gets the property handle of the property this detail tree item represents
- L40 _public prototype_ `FName GetNodeName() const;` — Gets the name of this detail tree item
- L43 _public prototype_ `bool ShouldBeExpanded() const;` — Gets whether this detail tree item should be expanded
- L46 _public prototype_ `void OnItemExpansionChanged(bool bIsExpanded, bool bShouldSaveState);` — Raised when this detail tree item's expansion state has been changed
- L49 _public prototype_ `bool IsResetToDefaultVisible() const;` — Gets whether the "reset to default" button should be visible for this detail tree item
- L52 _public prototype_ `void ResetToDefault();` — Resets the property this detail tree item represents to its default value
- L55 _public prototype_ `TAttribute<bool> IsPropertyEditingEnabled() const;` — Gets an attribute that can be used to determine if property editing is enabled for this detail tree item
- L58 _public prototype_ `bool IsCategory() const;` — Gets whether this detail tree item is a category
- L61 _public prototype_ `bool IsItem() const;` — Gets whether this detail tree item is an item
- L64 _public prototype_ `bool IsReorderable() const;` — Gets whether this detail tree item can be reordered through a drag drop action
- L67 _public prototype_ `bool IsCopyable() const;` — Gets whether this detail tree item can be copied
- L70 _public prototype_ `void GenerateDetailWidgetRow(FDetailWidgetRow& OutDetailWidgetRow) const;` — Generates the row widgets for this detail tree item
- L74 _private member_ `TWeakPtr<FDetailTreeNode> DetailTreeNode;` — A weak pointer to the detail tree node this item wraps
- L77 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property handle for the property this item represents
- L80 _private member_ `TWeakPtr<FColorGradingDetailTreeItem> Parent;` — A weak pointer to this item's parent
- L83 _private member_ `TArray<TSharedRef<FColorGradingDetailTreeItem>> Children;` — A list of children of this item

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/DetailView/SColorGradingDetailTreeRow.h` (Private)


#### class `SColorGradingDetailTreeRow`  
`class SColorGradingDetailTreeRow : public STableRow<TSharedRef<FColorGradingDetailTreeItem>>`  
_L16-113_
- inherits: `STableRow<TSharedRef<FColorGradingDetailTreeItem>>`
- desc: A copy/combination of SDetailSingleItemRow and SDetailCategoryTableRow defined in PropertyEditor/Private, used to display properties in a custom detail view widget
- L19 _public function_ `SLATE_BEGIN_ARGS(SColorGradingDetailTreeRow)`
- L20 _public prototype_ `SLATE_END_ARGS()`
- L24 _public prototype_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override;`
- L25 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `TSharedPtr<IPropertyHandle> GetPropertyHandle() const;` — Gets the property handle of the property this row represents, if applicable
- L32 _public prototype_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation();` — Creates a new drag drop operation for the property row
- L36 _private prototype_ `TSharedRef<SWidget> CreatePropertyWidget(const FDetailColumnSizeData& InColumnSizeData);` — Creates the widgets necessary to display the property this row represents
- L39 _private prototype_ `void CreateGlobalExtensionWidgets(TArray<FPropertyRowExtensionButton>& OutExtensions) const;` — Broadcasts the property editor module's global row extension delegate
- L42 _private prototype_ `bool IsRowEnabled() const;` — Gets whether the row is enabled
- L45 _private prototype_ `bool IsRowValueEnabled() const;` — Gets whether the row's value is enabled
- L48 _private prototype_ `int32 GetPropertyIndent() const;` — Gets the level of indent this row is at
- L51 _private prototype_ `FSlateColor GetIndentBackgroundColor(int32 Indent) const;` — Gets the background color for the row depending on its level of indent
- L54 _private prototype_ `const FSlateBrush* GetRowBackgroundBrush() const;` — Gets the brush for the row's background border
- L57 _private prototype_ `FSlateColor GetRowBackgroundColor() const;` — Gets the color for the row's background border
- L60 _private prototype_ `const FSlateBrush* GetScrollWellBackgroundBrush(TWeakPtr<STableViewBase> OwnerTableViewWeak) const;` — Gets the brush for the row's scroll well
- L63 _private prototype_ `FSlateColor GetScrollWellBackgroundColor(TWeakPtr<STableViewBase> OwnerTableViewWeak) const;` — Gets the color for the row's scroll well
- L66 _private prototype_ `void OnResetToDefaultClicked();` — Raised when the property's Reset to Default button is pressed
- L69 _private prototype_ `bool CanResetToDefault() const;` — Gets whether the property's Reset to Default button can be pressed
- L72 _private prototype_ `void OnRowDragLeave(const FDragDropEvent& DragDropEvent);` — Raised when a drag drop event leaves this row
- L75 _private prototype_ `FReply OnRowAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedRef<FColorGradingDetailTreeItem> TargetItem);` — Raised when a drag drop event is released on this row
- L78 _private prototype_ `TOptional<EItemDropZone> CanRowAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedRef<FColorGradingDetailTreeItem> Type);` — Indicates whether the drag drop event can be accepted by this row
- L81 _private prototype_ `bool IsValidDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const;` — Gets whether the specified drag drop event is allowed to be dropped onto this row
- L84 _private prototype_ `int32 GetDropNewIndex(int32 OriginalIndex, int32 DropOntoIndex, EItemDropZone DropZone) const;` — Gets the index to use when another row has been dragged onto this row, and an array element swap is taking place
- L87 _private prototype_ `void CopyPropertyName();` — Copies the property name to the clipboard
- L90 _private prototype_ `void CopyPropertyValue();` — Copies the property value to the clipboard
- L93 _private prototype_ `bool CanPastePropertyValue();` — Checks to see if this property can receive a pasted value from the clipboard
- L96 _private prototype_ `void PastePropertyValue();` — Pastes the value in the clipboard into this property
- L99 _private prototype_ `void SetExpansionStateForAll(bool bShouldBeExpanded);` — Sets the expansion state for this row and all of its children
- L102 _private prototype_ `void SetExpansionStateRecursive(const TSharedRef<FColorGradingDetailTreeItem>& TreeItem, bool bShouldBeExpanded);` — Recursively sets the expansion state for the specified tree item and its children
- L106 _private member_ `TWeakPtr<FColorGradingDetailTreeItem> DetailTreeItem;` — A weak pointer to the detail tree item this row represents
- L109 _private member_ `FDetailWidgetRow WidgetRow;` — The cached property row widgets that were created for this row
- L112 _private member_ `TSharedPtr<SWidget> IndentWidget;` — The indent widget used to properly indent the row's widgets

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/SColorGradingColorWheel.h` (Private)


#### class `SColorGradingColorWheel`  
`class SColorGradingColorWheel : public SCompoundWidget, public FEditorUndoClient`  
_L19-145_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: A widget which encapsulates a color picker and numeric sliders for each color component, hooked up to a color property handle
- L39 _public function_ `SLATE_BEGIN_ARGS(SColorGradingColorWheel)`
- L41 _public prototype_ `SLATE_ATTRIBUTE(UE::ColorGrading::EColorGradingColorDisplayMode, ColorDisplayMode) SLATE_ARGUMENT(TSharedPtr<SWidget>, HeaderContent) SLATE_END_ARGS() SColorGradingColorWheel();`
- L46 _public prototype_ `virtual ~SColorGradingColorWheel();`
- L48 _public prototype_ `void Construct(const FArguments& InArgs);`
- L51 _public prototype_ `void SetColorPropertyHandle(TSharedPtr<IPropertyHandle> InColorPropertyHandle);` — Sets the property handle for the color property to edit with this color wheel
- L54 _public prototype_ `void SetHeaderContent(const TSharedRef<SWidget>& HeaderContent);` — Sets the widget to display as the header of the color wheel
- L57 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L58 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L62 _public prototype_ `void OnPropertyValueChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);` — Called when any property changes
- L65 _private prototype_ `TSharedRef<SWidget> CreateColorGradingPicker();`
- L66 _private prototype_ `TSharedRef<SWidget> CreateColorComponentSliders();`
- L68 _private prototype_ `FColorPropertyMetadata GetColorPropertyMetadata() const;`
- L70 _private prototype_ `bool IsPropertyEnabled() const;`
- L71 _private prototype_ `EVisibility GetSlidersVisibility() const;`
- L72 _private prototype_ `EVisibility GetShortLayoutVisibility() const;`
- L73 _private prototype_ `EVisibility GetTallLayoutVisibility() const;`
- L74 _private prototype_ `int32 GetMaxWheelWidth() const;`
- L75 _private prototype_ `bool ShouldUseTallLayout() const;`
- L77 _private prototype_ `bool GetColor(FVector4& OutCurrentColor);`
- L78 _private prototype_ `void CommitColor(FVector4& NewValue, bool bShouldCommitValueChanges);`
- L79 _private prototype_ `void TransactColorValue();`
- L80 _private prototype_ `void RecalculateHSVColor();`
- L82 _private prototype_ `void BeginUsingColorPickerSlider();`
- L83 _private prototype_ `void EndUsingColorPickerSlider();`
- L84 _private prototype_ `void BeginUsingComponentSlider(uint32 ComponentIndex);`
- L85 _private prototype_ `void EndUsingComponentSlider(float NewValue, uint32 ComponentIndex);`
- L87 _private prototype_ `UE::ColorGrading::EColorGradingComponent GetComponent(uint32 ComponentIndex) const;`
- L88 _private prototype_ `TOptional<float> GetComponentValue(uint32 ComponentIndex) const;`
- L89 _private prototype_ `void SetComponentValue(float NewValue, uint32 ComponentIndex);`
- L91 _private prototype_ `bool ComponentSupportsDynamicSliderValue(bool bDefaultValue, uint32 ComponentIndex) const;`
- L92 _private prototype_ `void UpdateComponentDynamicSliderMinValue(float NewValue, TWeakPtr<SWidget> SourceWidget, bool bIsOriginator, bool bUpdateOnlyIfLower);`
- L93 _private prototype_ `void UpdateComponentDynamicSliderMaxValue(float NewValue, TWeakPtr<SWidget> SourceWidget, bool bIsOriginator, bool bUpdateOnlyIfHigher);`
- L95 _private prototype_ `TOptional<float> GetComponentMaxValue(TOptional<float> DefaultValue, uint32 ComponentIndex) const;`
- L96 _private prototype_ `TOptional<float> GetComponentMinSliderValue(TOptional<float> DefaultValue, uint32 ComponentIndex) const;`
- L97 _private prototype_ `TOptional<float> GetComponentMaxSliderValue(TOptional<float> DefaultValue, uint32 ComponentIndex) const;`
- L98 _private prototype_ `float GetComponentSliderDeltaValue(float DefaultValue, uint32 ComponentIndex) const;`
- L100 _private prototype_ `TOptional<float> GetMetadataMinValue() const;`
- L101 _private prototype_ `TOptional<float> GetMetadataMaxValue() const;`
- L102 _private prototype_ `TOptional<float> GetMetadataSliderMinValue() const;`
- L103 _private prototype_ `TOptional<float> GetMetadataSliderMaxValue() const;`
- L104 _private prototype_ `float GetMetadataDelta() const;`
- L105 _private prototype_ `float GetMetadataShiftMultiplier() const;`
- L106 _private prototype_ `float GetMetadataCtrlMultiplier() const;`
- L107 _private prototype_ `bool GetMetadataSupportDynamicSliderMinValue() const;`
- L108 _private prototype_ `bool GetMetadataSupportDynamicSliderMaxValue() const;`
- L112 _private member_ `const FVector2f ColumnPadding = FVector2f(16.f, 8.f);` — Padding applied to the whole column
- L114 _private member_ `TSharedPtr<UE::ColorGrading::SColorGradingPicker> ColorGradingPicker;`
- L115 _private member_ `TSharedPtr<SBox> HeaderBox;`
- L116 _private member_ `TSharedPtr<SBox> ColorPickerBox;`
- L117 _private member_ `TSharedPtr<SBox> ColorSlidersBox;`
- L120 _private member_ `FTrackedVector4PropertyHandle ColorPropertyHandle;` — The property handle of the linear color property being edited
- L123 _private member_ `TOptional<FColorPropertyMetadata> ColorPropertyMetadata;` — The metadata of the color property
- L126 _private member_ `TAttribute<UE::ColorGrading::EColorGradingColorDisplayMode> ColorDisplayMode;` — Attribute for the color mode type the color wheel is presenting the color components in
- L129 _private member_ `TOptional<float> ComponentSliderDynamicMinValue;` — Stored current min value of the color component numeric sliders
- L132 _private member_ `TOptional<float> ComponentSliderDynamicMaxValue;` — Stored current max value of the color component numeric sliders
- L135 _private member_ `bool bIsUsingColorPickerSlider = false;` — Indicates that the color picker slider is currently being used to change the color on the color picker
- L138 _private member_ `bool bIsUsingComponentSlider = false;` — Indicates that a component's numeric slider is currently being used to change the color
- L144 _private member_ `FLinearColor CurrentHSVColor;` — The current color in HSV space. Stored separately so that hue/saturation adjustments aren't lost when the color is 0.

#### struct `SColorGradingColorWheel::FColorPropertyMetadata`  
`struct FColorPropertyMetadata`  
_L22-36_
- L24 _public member_ `UE::ColorGrading::EColorGradingModes ColorGradingMode = UE::ColorGrading::EColorGradingModes::Invalid;`
- L25 _public member_ `TOptional<float> MinValue = TOptional<float>();`
- L26 _public member_ `TOptional<float> MaxValue = TOptional<float>();`
- L27 _public member_ `TOptional<float> SliderMinValue = TOptional<float>();`
- L28 _public member_ `TOptional<float> SliderMaxValue = TOptional<float>();`
- L29 _public member_ `float SliderExponent = 1.0f;`
- L30 _public member_ `float Delta = 0.0f;`
- L31 _public member_ `int32 LinearDeltaSensitivity = 0;`
- L32 _public member_ `float ShiftMultiplier = 10.f;`
- L33 _public member_ `float CtrlMultiplier = 0.1f;`
- L34 _public member_ `bool bSupportDynamicSliderMaxValue = false;`
- L35 _public member_ `bool bSupportDynamicSliderMinValue = false;`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Private/SColorGradingColorWheelPanel.h` (Private)


#### class `SColorGradingColorWheelPanel`  
`class SColorGradingColorWheelPanel : public SCompoundWidget`  
_L21-92_
- inherits: `SCompoundWidget`
- desc: A panel that contains up to five color wheels (for saturation, contrast, gamma, gain, and offset) as well as a details view for extra, non-color properties
- L25 _private member_ `static const uint32 NumColorWheels = 5;` — The number of color wheels the color wheel panel displays (for saturation, contrast, gamma, gain, and offset)
- L30 _public function_ `SLATE_BEGIN_ARGS(SColorGradingColorWheelPanel)`
- L31 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FColorGradingEditorDataModel>, ColorGradingDataModelSource) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `void Refresh();` — Regenerates the color wheel panel from the current state of the data model source
- L40 _public prototype_ `void GetPanelState(FColorGradingPanelState& OutPanelState);` — Adds the state of the color wheel panel to the specified drawer state
- L43 _public prototype_ `void SetPanelState(const FColorGradingPanelState& InPanelState);` — Sets the state of the color wheel panel from the specified drawer state
- L46 _private prototype_ `TSharedRef<SWidget> MakeColorDisplayModeCheckbox();`
- L48 _private prototype_ `void FillColorGradingGroupProperty(const FColorGradingEditorDataModel::FColorGradingGroup& ColorGradingGroup);`
- L49 _private prototype_ `void ClearColorGradingGroupProperty();`
- L51 _private prototype_ `void FillColorGradingElementsToolBar(const TArray<FColorGradingEditorDataModel::FColorGradingElement>& ColorGradingElements);`
- L52 _private prototype_ `void ClearColorGradingElementsToolBar();`
- L54 _private prototype_ `void FillColorWheels(const FColorGradingEditorDataModel::FColorGradingElement& ColorGradingElement);`
- L55 _private prototype_ `void ClearColorWheels();`
- L57 _private prototype_ `TSharedRef<SWidget> CreateColorWheelHeaderWidget(const TSharedPtr<IPropertyHandle>& ColorPropertyHandle, const TOptional<FResetToDefaultOverride>& ResetToDefaultOverride);`
- L58 _private prototype_ `TSharedRef<SWidget> CreateColorPropertyExtensions(const TSharedPtr<IPropertyHandle>& ColorPropertyHandle, const TSharedPtr<IDetailTreeNode>& DetailTreeNode, const TOptional<FResetToDefaultOverride>& ResetToDefaultOverride);`
- L60 _private prototype_ `bool FilterDetailTreeNode(const TSharedRef<IDetailTreeNode>& InDetailTreeNode);`
- L62 _private prototype_ `void OnColorGradingGroupSelectionChanged();`
- L63 _private prototype_ `void OnColorGradingElementSelectionChanged();`
- L65 _private prototype_ `void OnColorGradingElementCheckedChanged(ECheckBoxState State, FText ElementName);`
- L67 _private prototype_ `ECheckBoxState IsColorGradingElementSelected(FText ElementName) const;`
- L68 _private prototype_ `EVisibility GetColorWheelPanelVisibility() const;`
- L69 _private prototype_ `EVisibility GetMultiSelectWarningVisibility() const;`
- L71 _private function_ `UE::ColorGrading::EColorGradingColorDisplayMode GetColorDisplayMode() const`
- L72 _private prototype_ `void OnColorDisplayModeChanged(UE::ColorGrading::EColorGradingColorDisplayMode InColorDisplayMode);`
- L73 _private prototype_ `FText GetColorDisplayModeLabel(UE::ColorGrading::EColorGradingColorDisplayMode InColorDisplayMode) const;`
- L74 _private prototype_ `FText GetColorDisplayModeToolTip(UE::ColorGrading::EColorGradingColorDisplayMode InColorDisplayMode) const;`
- L78 _private member_ `TSharedPtr<FColorGradingEditorDataModel> ColorGradingDataModel;` — The color grading data model that the panel is displaying
- L80 _private member_ `TSharedPtr<SBox> ColorGradingGroupPropertyBox;`
- L81 _private member_ `TSharedPtr<SHorizontalBox> ColorGradingElementsToolBarBox;`
- L83 _private member_ `TArray<TSharedPtr<SColorGradingColorWheel>> ColorWheels;`
- L85 _private member_ `TSharedPtr<SColorGradingDetailView> DetailView;`
- L88 _private member_ `int32 SelectedColorGradingGroup = INDEX_NONE;` — The currently selected color grading group
- L91 _private member_ `UE::ColorGrading::EColorGradingColorDisplayMode ColorDisplayMode = UE::ColorGrading::EColorGradingColorDisplayMode::RGB;` — The current color display mode for the color wheels

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/ColorGradingEditorDataModel.h` (Public)


#### class `IColorGradingEditorDataModelGenerator`  
`class IColorGradingEditorDataModelGenerator : public TSharedFromThis<IColorGradingEditorDataModelGenerator>`  
_L18-28_
- inherits: `TSharedFromThis<IColorGradingEditorDataModelGenerator>`
- desc: Interface that allows color grading data models to be generated for specific UObjects
- L21 _public prototype_ `virtual ~IColorGradingEditorDataModelGenerator() = default;`
- L23 _public prototype_ `virtual void Initialize(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) = 0;`
- L24 _public prototype_ `virtual void Destroy(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) = 0;`
- L27 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, class FColorGradingEditorDataModel& OutColorGradingDataModel) = 0;` — Called when the color grading data model should be generated by this generator

#### class `FColorGradingEditorDataModel`  
`class FColorGradingEditorDataModel : public TSharedFromThis<FColorGradingEditorDataModel>`  
_L36-226_
- inherits: `TSharedFromThis<FColorGradingEditorDataModel>`
- desc: A data model that stores the color grading properties from a UObject, which allows UObjects with widely varying color grading interfaces to be used with the color grading panel.
- L41 _public function_ `template<class T> static void RegisterColorGradingDataModelGenerator(FGetDetailsDataModelGenerator CreateGeneratorDelegate)` — Registers a new data model generator used to populate a color grading data model for the specified class
- L49 _private member_ `static TMap<TWeakObjectPtr<UClass>, FGetDetailsDataModelGenerator> RegisteredDataModelGenerators;` — A list of data model generators, indexed by class name, that have been registered
- L117 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDataModelGenerated);`
- L118 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnColorGradingSelectionChanged);`
- L119 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorGradingGroupDeleted, int32);`
- L120 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnColorGradingGroupRenamed, int32, const FText&);`
- L123 _public prototype_ `FColorGradingEditorDataModel();`
- L126 _public function_ `TSharedRef<IPropertyRowGenerator> GetPropertyRowGenerator() const` — Gets the property row generator that was used to generate this data model
- L129 _public prototype_ `TArray<TWeakObjectPtr<UObject>> GetObjects() const;` — Gets the list of objects from which the color grading properties were generated from
- L132 _public prototype_ `void SetObjects(const TArray<UObject*>& InObjects);` — Sets the objects from which the color grading properties will be generated from
- L135 _public prototype_ `bool HasObjectOfType(const UClass* InClass) const;` — Gets whether the data model has objects of the specified class
- L138 _public prototype_ `void Reset();` — Resets the data model to be empty
- L141 _public prototype_ `void GetPanelState(FColorGradingPanelState& OutPanelState);` — Adds the state of the data model to the specified drawer state
- L144 _public prototype_ `void SetPanelState(const FColorGradingPanelState& InPanelState);` — Sets the state of the data model from the specified drawer state
- L147 _public function_ `int32 GetSelectedColorGradingGroupIndex() const` — Gets the index of the selected color grading group
- L150 _public prototype_ `FColorGradingGroup* GetSelectedColorGradingGroup();` — Gets a pointer to the selected color grading group, or null if there isn't a valid selection
- L153 _public prototype_ `void SetSelectedColorGradingGroup(int32 InColorGradingGroupIndex);` — Sets the selected color grading group
- L156 _public function_ `FOnDataModelGenerated& OnDataModelGenerated()` — Gets the delegate that is raised when the data model is generated
- L159 _public function_ `FOnColorGradingSelectionChanged& OnColorGradingGroupSelectionChanged()` — Gets the delegate that is raised when the selected color grading group has changed
- L162 _public function_ `int32 GetSelectedColorGradingElementIndex() const` — Gets the index of the selected color grading element
- L165 _public prototype_ `FColorGradingElement* GetSelectedColorGradingElement();` — Gets a pointer to the selected color grading element, or null if there isn't a valid selection
- L168 _public prototype_ `void SetSelectedColorGradingElement(int32 InColorGradingElementIndex);` — Sets the selected color grading element
- L171 _public function_ `FOnColorGradingSelectionChanged& OnColorGradingElementSelectionChanged()` — Gets the delegate that is raised when the selected color grading element has changed
- L174 _public function_ `FOnColorGradingGroupDeleted& OnColorGradingGroupDeleted()` — Gets the delegate that is raised when a color grading group is deleted by the user
- L177 _public function_ `FOnColorGradingGroupRenamed& OnColorGradingGroupRenamed()` — Gets the delegate that is raised when a color grading group is renamed by the user
- L181 _private prototype_ `void InitializeDataModelGenerator(UClass* InClass);` — Initializes any needed data model generators for the specified class
- L184 _private prototype_ `TSharedPtr<IColorGradingEditorDataModelGenerator> GetDataModelGenerator(UClass* InClass) const;` — Attempts to find an instance of a data model generator that can be used for the specified class
- L187 _private prototype_ `void OnPropertyRowGeneratorRefreshed();` — Callback that is raised when the property row generator the data model is generated from has been refreshed
- L191 _public member_ `TArray<FColorGradingGroup> ColorGradingGroups;` — A list of color grading groups in the color grading data model
- L194 _public member_ `TSharedPtr<SWidget> ColorGradingGroupToolBarWidget = nullptr;` — An optional widget to append to the end of the color grading group toolbar
- L197 _public member_ `bool bShowColorGradingGroupToolBar = false;` — Indicates whether the color grading groups should be visible/selectable in a toolbar
- L201 _private member_ `TMap<TWeakObjectPtr<UClass>, TSharedPtr<IColorGradingEditorDataModelGenerator>> DataModelGeneratorInstances;` — A list of data model generators that have been created to generate the data model for the current objects
- L204 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The property row generator which manages the property handles of the color grading objects
- L207 _private member_ `int32 SelectedColorGradingGroupIndex = INDEX_NONE;` — The currently selected color grading element
- L210 _private member_ `int32 SelectedColorGradingElementIndex = INDEX_NONE;` — The currently selected color grading element
- L213 _private member_ `FOnDataModelGenerated OnDataModelGeneratedDelegate;` — Delegate that is raised when the data model has been generated
- L216 _private member_ `FOnColorGradingSelectionChanged OnColorGradingGroupSelectionChangedDelegate;` — Delegate that is raised when the selected color grading group has been changed
- L219 _private member_ `FOnColorGradingSelectionChanged OnColorGradingElementSelectionChangedDelegate;` — Delegate that is raised when the selected color grading element has been changed
- L222 _private member_ `FOnColorGradingGroupDeleted OnColorGradingGroupDeletedDelegate;` — Delegate that is raised when a color grading group is being deleted
- L225 _private member_ `FOnColorGradingGroupRenamed OnColorGradingGroupRenamedDelegate;` — Delegate that is raised when a color grading group is being renamed

#### struct `FColorGradingEditorDataModel::FColorGradingElement`  
`struct FColorGradingElement`  
_L53-87_
- desc: Stores the property handles for the color properties for a single color grading element (Shadows, Midtones, etc.)
- L56 _public member_ `FText DisplayName;` — The display name of the color grading element
- L59 _public member_ `TSharedPtr<IPropertyHandle> SaturationPropertyHandle;` — Property handle of the color property used for saturation
- L62 _public member_ `TOptional<FResetToDefaultOverride> SaturationResetToDefaultOverride;` — Optional reset to default handler for the saturation property
- L65 _public member_ `TSharedPtr<IPropertyHandle> ContrastPropertyHandle;` — Property handle of the color property used for contrast
- L68 _public member_ `TOptional<FResetToDefaultOverride> ContrastResetToDefaultOverride;` — Optional reset to default handler for the contrast property
- L71 _public member_ `TSharedPtr<IPropertyHandle> GammaPropertyHandle;` — Property handle of the color property used for gamma
- L74 _public member_ `TOptional<FResetToDefaultOverride> GammaResetToDefaultOverride;` — Optional reset to default handler for the gamma property
- L77 _public member_ `TSharedPtr<IPropertyHandle> GainPropertyHandle;` — Property handle of the color property used for gain
- L80 _public member_ `TOptional<FResetToDefaultOverride> GainResetToDefaultOverride;` — Optional reset to default handler for the gain property
- L83 _public member_ `TSharedPtr<IPropertyHandle> OffsetPropertyHandle;` — Property handle of the color property used for offset
- L86 _public member_ `TOptional<FResetToDefaultOverride> OffsetResetToDefaultOverride;` — Optional reset to default handler for the offset property

#### struct `FColorGradingEditorDataModel::FColorGradingGroup`  
`struct FColorGradingGroup`  
_L90-115_
- desc: Stores a list of color grading elements that form a single color grading group
- L93 _public member_ `FText DisplayName = FText::GetEmpty();` — The display name of the color grading group
- L96 _public member_ `TSharedPtr<IPropertyHandle> GroupPropertyHandle = nullptr;` — The handle of the property that the color grading properties are generated from
- L99 _public member_ `TSharedPtr<SWidget> GroupHeaderWidget = nullptr;` — The widget displayed in the color wheel panel's header for this group, usually just a text block to show the group's name
- L102 _public member_ `TSharedPtr<IPropertyHandle> EditConditionPropertyHandle = nullptr;` — The handle of the property that controls the editing condition of the properties in the color grading group
- L105 _public member_ `TArray<FColorGradingElement> ColorGradingElements;` — The list of color grading elements (Shadows, Midtones, etc.) that belong in the group
- L108 _public member_ `TArray<FName> DetailsViewCategories;` — A list of categories of properties to display in the detail view of the color grading panel
- L111 _public member_ `bool bCanBeDeleted = false;` — Indicates that the color grading group can be deleted by the user
- L114 _public member_ `bool bCanBeRenamed = false;` — Indicates that the color grading group can be renamed by the user

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COLORGRADINGEDITOR_API`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IColorGradingEditorDataModelGenerator>, FGetDetailsDataModelGenerator);`
- L30 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IColorGradingEditorDataModelGenerator>, FGetDetailsDataModelGenerator);`
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDataModelGenerated);`
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnColorGradingSelectionChanged);`
- L119 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorGradingGroupDeleted, int32);`
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnColorGradingGroupRenamed, int32, const FText&);`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/ColorGradingEditorUtil.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ColorGradingEditorUtil`
- L15 _prototype_ `TSharedRef<SWidget> MakeColorGradingLaunchButton(bool bWrapInBox = true);` (scope `ColorGradingEditorUtil`) — Make a button that opens the Color Grading editor. @param bWrapInBox If true, wrap the button in a box that centers it and adds standard padding for use in the Details panel.

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/ColorGradingMixerContextObject.h` (Public)


#### class `UColorGradingMixerContextObject`  
`class UColorGradingMixerContextObject : public UObject`  
_L11-14_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Empty class which can be added to an FToolMenuContext to indicate that the menu originates from the Color Grading panel.

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/ColorGradingMixerObjectFilterRegistry.h` (Public)


#### struct `IColorGradingMixerObjectHierarchyConfig`  
`struct IColorGradingMixerObjectHierarchyConfig : public TSharedFromThis<IColorGradingMixerObjectHierarchyConfig>`  
_L16-51_
- inherits: `TSharedFromThis<IColorGradingMixerObjectHierarchyConfig>`
- desc: Interface to configure how an object is displayed in the Color Grading panel's outliner
- L19 _public prototype_ `virtual ~IColorGradingMixerObjectHierarchyConfig() = default;`
- L22 _public function_ `virtual TArray<AActor*> FindAssociatedActors(UObject* ParentObject) const` — Generate a list of additional actors to include as children in the ObjectMixer hierarchy for the given object
- L29 _public function_ `virtual bool IsActorAssociated(UObject* ParentObject, AActor* AssociatedActor) const` — Return true if AssociatedActor is associated with ParentObject. This should return true if the actor would be included in FindAssociatedActors, but is a separate function to avoid allocating an array every time.
- L32 _public function_ `virtual TArray<FObjectMixerEditorActorSubObject> GetActorSubObjects(UObject* ParentObject) const` — Generate a list of additional sub-objects to include as children in the ObjectMixer hierarchy for the given object
- L38 _public function_ `virtual bool HasCustomDropHandling() const` — If true, this has custom handling for drop operations and will override the hierarchy's default behaviour with the ValidateDrop and OnDrop functions.
- L41 _public function_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(UObject* DropTarget, const FSceneOutlinerDragDropPayload& Payload) const` — Test whether the specified payload can be dropped onto a tree item representing this object
- L44 _public function_ `virtual bool OnDrop(UObject* DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const` — Called when a payload is dropped onto a target. If this returns true, the outliner will be refreshed after the operation.
- L50 _public function_ `virtual TSet<FName> GetPropertiesThatRequireListRefresh() const` — If a property is changed that has a name found in this set, the color grading mixer hierarchy will be refreshed. Add a property name to this list if you expect the list to change in some way after changing that property.

#### struct `IColorGradingMixerSelectionHandler`  
`struct IColorGradingMixerSelectionHandler : public TSharedFromThis<IColorGradingMixerSelectionHandler>`  
_L56-74_
- inherits: `TSharedFromThis<IColorGradingMixerSelectionHandler>`
- desc: Interface for custom selection handlers that can receive selection events from the color grading drawer's mixer
- L59 _public prototype_ `DECLARE_DELEGATE(FOnSelectionChanged);`
- L61 _public prototype_ `virtual ~IColorGradingMixerSelectionHandler() = default;`
- L64 _public function_ `virtual bool CanSelectSubObject(const UObject* InObject)` — Returns true if this handler can handle synchronizing the specified object
- L67 _public function_ `virtual void SelectSubObjects(const TArray<UObject*>& InSelectedObjects, bool bShouldSelect, bool bSelectEvenIfHidden) const` — Called when the color grading mixer synchronizes its selection to the rest of the editor
- L70 _public function_ `virtual TArray<UObject*> GetSelectedSubObjectsInEditor() const` — Called when the color grading mixer synchronizes its selection from selected objects in the editor. Retrieves a list of all sub-objects selected in the editor
- L73 _public member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate that can be invoked to cause the color grading mixer to re-synchronize its selection to the editor's selection

#### struct `FColorGradingMixerObjectFilterRegistry`  
`struct FColorGradingMixerObjectFilterRegistry`  
_L81-142_
- desc: Contains functions for controlling which classes can be managed from the Color Grading panel's ObjectMixer-based hierarchy panel
- L90 _public function_ `static void RegisterObjectClassToFilter(UClass* Class, FGetObjectHierarchyConfig CreateConfigDelegate = nullptr)` — Register an object class that can be seen in a Color Grading panel's object list. @param Class The object class to register @param Config Optional delegate that creates a configuration for how the object will be displayed in the hierarchy
- L101 _public function_ `static void RegisterActorClassToPlace(TSubclassOf<AActor> Class)` — Register an actor class that can be placed from the Color Grading panel's object list
- L110 _public function_ `static void RegisterSelectionHandler(FGetSelectionHandler InCreateHandlerDelegate)` — Registers a new selection handler with the color drawer that will receive selection related events from the drawer's mixer @param InCreateHandlerDelegate A delegate that is invoked to create the selection handler when needed
- L116 _public function_ `static const TSet<UClass*>& GetObjectClassesToFilter()` — Get the set of object classes that can be seen in a Color Grading panel's object list
- L119 _public function_ `static const TSet<TSubclassOf<AActor>>& GetActorClassesToPlace()` — Get the set of actor classes that can be placed from a Color Grading panel's object list
- L122 _public prototype_ `static const IColorGradingMixerObjectHierarchyConfig* GetClassHierarchyConfig(TSubclassOf<AActor> Class);` — Get the hierarchy configuration for a class, or null if none was provided
- L125 _public prototype_ `static TArray<TSharedPtr<IColorGradingMixerSelectionHandler>> CreateSelectionHandlers();` — Instantiates a list of all selection handlers that have been registered to the color grading drawer
- L129 _private member_ `inline static TSet<UClass*> ObjectClassesToFilter;` — Set of classes that can be seen in the object panel
- L132 _private member_ `inline static TSet<TSubclassOf<AActor>> ActorClassesToPlace;` — Set of classes that can be placed from the object panel
- L135 _private member_ `inline static TMap<TWeakObjectPtr<UClass>, FGetObjectHierarchyConfig> HierarchyConfigs;` — Map from object class to hierarchy configuration, if provided
- L138 _private member_ `inline static TMap<TWeakObjectPtr<UClass>, TSharedPtr<IColorGradingMixerObjectHierarchyConfig>> HierarchyConfigInstances;` — Map from object class to hierarchy configuration instance. If null, none exist for the class
- L141 _private member_ `inline static TArray<FGetSelectionHandler> SelectionHandlers;` — List of handlers that process custom selection synchronization for specific color gradable objects

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COLORGRADINGEDITOR_API`
- L53 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IColorGradingMixerObjectHierarchyConfig>, FGetObjectHierarchyConfig);`
- L53 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IColorGradingMixerObjectHierarchyConfig>, FGetObjectHierarchyConfig);`
- L59 _delegate_ `DECLARE_DELEGATE(FOnSelectionChanged);`
- L76 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IColorGradingMixerSelectionHandler>, FGetSelectionHandler);`
- L76 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IColorGradingMixerSelectionHandler>, FGetSelectionHandler);`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/ColorGradingPanelState.h` (Public)


#### struct `FColorGradingPanelState`  
`struct FColorGradingPanelState`  
_L13-36_
- desc: Stores the state of the color grading panel UI that can be reloaded in cases where the panel or any of its elements are reloaded (such as when the containing drawer is reopened or docked)
- L16 _public member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;` — The objects that are selected in the list
- L23 _public member_ `TArray<TWeakObjectPtr<UObject>> ControlledObjects;` — The objects that are being controlled by the color grading controls. This can differ from SelectedObjects when SelectedObjects contains objects that are associated with a color-gradable object, but don't have controls themselves.
- L26 _public member_ `int32 SelectedColorGradingGroup = INDEX_NONE;` — The color grading group that is selected
- L29 _public member_ `int32 SelectedColorGradingElement = INDEX_NONE;` — The color grading element that is selected
- L32 _public member_ `UE::ColorGrading::EColorGradingColorDisplayMode ColorDisplayMode;` — The color display mode of the color wheels
- L35 _public member_ `TArray<int32> SelectedDetailsSubsections;` — Indicates which subsections were selected for each section in the details panel

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/DetailView/SColorGradingDetailView.h` (Public)


#### class `SColorGradingDetailView`  
`class SColorGradingDetailView : public SCompoundWidget`  
_L33-107_
- inherits: `SCompoundWidget`
- desc: A custom detail view based on SDetailView that uses a property row generator as a source for the property nodes instead of generating them manually. Using an existing property row generator allows the detail view to display an object's properties much faster than the ordinary SDetailView, which has to regenerate a new property node tree every time the object being displayed is changed
- L36 _public function_ `SLATE_BEGIN_ARGS(SColorGradingDetailView)`
- L37 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyRowGenerator>, PropertyRowGeneratorSource) SLATE_EVENT(FOnFilterDetailTreeNode, OnFilterDetailTreeNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L44 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L48 _public prototype_ `void Refresh();` — Regenerates this widget based on the current state of its property row generator source
- L51 _public prototype_ `void SaveExpandedItems();` — Saves the expansion state of all properties being displayed in this detail view to the user's config file
- L54 _public prototype_ `void RestoreExpandedItems();` — Restores the expansion state of all properties being displayed in this detail view from the user's config file
- L58 _private prototype_ `void UpdateTreeNodes();` — Updates the detail tree using the current state of the property row generator source
- L61 _private prototype_ `void UpdateExpansionState(const TSharedRef<FColorGradingDetailTreeItem> InTreeItem);` — Updates the expansion state of the specified tree item using the stored expansion state configuration
- L64 _private prototype_ `void SetNodeExpansionState(TSharedRef<FColorGradingDetailTreeItem> InTreeNode, bool bIsItemExpanded, bool bRecursive);` — Sets the expansion state of the specified tree item, and optionally recursively sets the expansion state of its children
- L67 _private prototype_ `TSharedRef<ITableRow> GenerateNodeRow(TSharedRef<FColorGradingDetailTreeItem> InTreeNode, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a table row widget for the specified tree item
- L70 _private prototype_ `void GetChildrenForNode(TSharedRef<FColorGradingDetailTreeItem> InTreeNode, TArray<TSharedRef<FColorGradingDetailTreeItem>>& OutChildren);` — Gets a list of child tree items for the specified tree item
- L73 _private prototype_ `void OnSetExpansionRecursive(TSharedRef<FColorGradingDetailTreeItem> InTreeNode, bool bIsItemExpanded);` — Raised when the underlying tree widget is setting the expansion state of the specified tree item recursively
- L76 _private prototype_ `void OnExpansionChanged(TSharedRef<FColorGradingDetailTreeItem> InTreeNode, bool bIsItemExpanded);` — Raised when the underlying tree widget is setting the expansion state of the specified tree item
- L79 _private prototype_ `void OnRowReleased(const TSharedRef<ITableRow>& TableRow);` — Raised when the underlying tree widget is releasing the specified table row
- L82 _private prototype_ `EVisibility GetScrollBarVisibility() const;` — Gets the visibility of the scrollbar for the detail view
- L85 _private typedef_ `typedef STreeView<TSharedRef<FColorGradingDetailTreeItem>> SDetailTree;`
- L88 _private member_ `TSharedPtr<SDetailTree> DetailTree;` — The underlying tree view used to display the property widgets
- L91 _private member_ `TArray<TSharedRef<FColorGradingDetailTreeItem>> RootTreeNodes;` — The source list of the root detail tree nodes being displayed by the tree widget
- L94 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGeneratorSource;` — The property row generator to generate the property widgets from
- L97 _private member_ `FDetailColumnSizeData ColumnSizeData;` — Column sizing data for the properties
- L100 _private member_ `TMap<TWeakPtr<FColorGradingDetailTreeItem>, bool> TreeItemsToSetExpansionState;` — A list of tree items whose expansion state needs to be set on the next tick
- L103 _private member_ `TSet<FString> ExpandedDetailNodes;` — A list of currently expanded detail nodes
- L106 _private member_ `FOnFilterDetailTreeNode OnFilterDetailTreeNode;` — Delegate used to filter or process the detail tree nodes that are displayed in the detail view

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COLORGRADINGEDITOR_API`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterDetailTreeNode, const TSharedRef<IDetailTreeNode>&);`
- L26 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterDetailTreeNode, const TSharedRef<IDetailTreeNode>&);`

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/IColorGradingEditor.h` (Public)


#### class `IColorGradingEditor`  
`class IColorGradingEditor : public IModuleInterface`  
_L12-43_
- inherits: `IModuleInterface`
- desc: Display Cluster Color Grading module interface
- L15 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Col`
- L18 _public prototype_ `virtual ~IColorGradingEditor() = default;`
- L21 _public prototype_ `virtual FName GetColorGradingTabSpawnerId() const = 0;` — Get the ID of the main color grading tab
- L29 _public function_ `static inline IColorGradingEditor& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L39 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Editor/ColorGrading/Source/ColorGradingEditor/Public/SColorGradingPanel.h` (Public)


#### class `SColorGradingPanel`  
`class SColorGradingPanel : public SCompoundWidget, public FEditorUndoClient`  
_L25-160_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Main panel of a color grading drawer widget, which displays color wheels or selected object details
- L28 _public prototype_ `~SColorGradingPanel();`
- L30 _public function_ `SLATE_BEGIN_ARGS(SColorGradingPanel) : _IsInDrawer(false)`
- L35 _public prototype_ `SLATE_ARGUMENT(bool, IsInDrawer) SLATE_ATTRIBUTE(UWorld*, OverrideWorld) SLATE_EVENT(FSimpleDelegate, OnDocked) SLATE_ARGUMENT(FColorGradingActorFilter, ActorFilter) SLATE_ARGUMENT(TSharedPtr<IObjectMixerSelectionInterface>, SelectionInterface) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Indicates whether this widget is in a drawer or docked in a tab
- L54 _public prototype_ `void Refresh();` — Refreshes the panel's UI to match the current state of the level
- L57 _public prototype_ `void GetPanelState(FColorGradingPanelState& OutPanelState) const;` — Gets the state of the panel UI
- L60 _public prototype_ `void SetPanelState(const FColorGradingPanelState& InPanelState);` — Sets the state of the panel UI
- L67 _public prototype_ `void SetSelectedObjects(const TArray<UObject*>& SelectedObjects, const TArray<UObject*>* ControlledObjects = nullptr);` — Set the list of selected objects, updating state and data model as appropriate. If ControlledObjects is provided, only the objects in that array will be used to display the color grading wheels. Otherwise, the controlled objects will use the contents of SelectedObjects.
- L71 _private prototype_ `TSharedRef<SWidget> CreateDockInLayoutButton();` — Creates the button used to dock the drawer in the operator panel
- L74 _private prototype_ `UWorld* GetWorld();` — Get the world currently being edited
- L77 _private prototype_ `void RefreshColorGradingList();` — Refreshes the object list, filling it with the current color gradable objects from the root actor and world
- L80 _private prototype_ `void FillColorGradingGroupToolBar();` — Fills the color grading group toolbar using the color grading data model
- L83 _private prototype_ `EVisibility GetColorGradingGroupToolBarVisibility() const;` — Gets the visibility state of the color grading group toolbar
- L86 _private prototype_ `ECheckBoxState IsColorGradingGroupSelected(int32 GroupIndex) const;` — Gets whether the color grading group at the specified index is currently selected
- L89 _private prototype_ `void OnColorGradingGroupCheckedChanged(ECheckBoxState State, int32 GroupIndex);` — Raised when the user has selected the specified color grading group
- L92 _private prototype_ `FText GetColorGradingGroupDisplayName(int32 GroupIndex) const;` — Gets the display name of the specified color grading group
- L95 _private prototype_ `FSlateFontInfo GetColorGradingGroupDisplayNameFont(int32 GroupIndex) const;` — Gets the font of the display name label of the specified color grading group
- L98 _private prototype_ `TSharedRef<SWidget> GetColorGradingGroupMenuContent(int32 GroupIndex);` — Gets the content for the right click menu for the color grading group
- L101 _private prototype_ `void OnColorGradingGroupDeleted(int32 GroupIndex);` — Raised when a color grading group has been deleted by the user
- L104 _private prototype_ `void OnColorGradingGroupRequestRename(int32 GroupIndex);` — Raised when a rename has been requested on a color grading group
- L107 _private prototype_ `void OnColorGradingGroupRenamed(const FText& InText, ETextCommit::Type TextCommitType, int32 GroupIndex);` — Raised when a rename has been committed on a color grading group
- L110 _private prototype_ `void OnColorGradingDataModelGenerated();` — Raised when the color grading data model has been generated
- L113 _private prototype_ `FReply DockInLayout();` — Raised when the "Dock in Layout" button has been clicked
- L116 _private prototype_ `void OnListSelectionChanged(FSceneOutlinerTreeItemPtr TreeItem, ESelectInfo::Type Type);` — Raised when the user has selected a new item in any of the drawer's list views
- L119 _private prototype_ `void OnListSelectionSynchronized();` — Raised when the drawer's outliner has been synchronized with the editor selection
- L122 _private prototype_ `void UpdateSelectionFromList();` — Update the selected items to match the list view
- L125 _private prototype_ `void GetSelectedAndControlledObjects(const TArray<FSceneOutlinerTreeItemPtr>& InSelectedItems, TArray<UObject*>& OutSelectedObjects, TArray<UObject*>& OutControlledObjects) const;` — Given an array of selected tree items, determine which objects will be selected and/or controlled
- L129 _private member_ `TSharedPtr<FObjectMixerEditorList> ObjectListModel;` — Model for the object mixer list used to display the color gradable object hierarchy.
- L132 _private member_ `TSharedPtr<SHorizontalBox> ColorGradingGroupToolBarBox;` — Box containing the color grading groups
- L135 _private member_ `TArray<TSharedPtr<SInlineEditableTextBlock>> ColorGradingGroupTextBlocks;` — List of editable text blocks containing color grading group names
- L138 _private member_ `TSharedPtr<SColorGradingColorWheelPanel> ColorWheelPanel;` — Panel containing the color wheels
- L141 _private member_ `TAttribute<UWorld*> OverrideWorld;` — The world from which to retrieve actors, if one was provided
- L144 _private member_ `TSharedPtr<SSceneOutliner> ColorGradingObjectListView;` — Color grading object list widget being displayed in the drawer's list panel
- L147 _private member_ `TSharedPtr<FColorGradingEditorDataModel> ColorGradingDataModel;` — The color grading data model for the currently selected objects
- L150 _private member_ `bool bIsInDrawer;` — Indicates whether this widget is in a drawer or docked in a tab
- L153 _private member_ `bool bRefreshOnNextTick = false;` — Indicates that the panel should refresh itself on the next tick
- L156 _private member_ `FSimpleDelegate DockCallback;` — The function to call when the user presses the dock button
- L159 _private member_ `FColorGradingActorFilter ActorFilter;` — Function used to filter actors before adding them to the object list.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COLORGRADINGEDITOR_API`
- L22 _typedef_ `using FColorGradingActorFilter = TFunction<bool(const AActor*)>;`
