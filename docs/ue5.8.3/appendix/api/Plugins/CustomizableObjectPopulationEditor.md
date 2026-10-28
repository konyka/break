# Plugins / CustomizableObjectPopulationEditor

- module root: `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor`
- headers: 18; symbols: 424
- symbol kinds: class=27, externvar=4, function=30, member=158, namespace=7, prototype=198
- DynamicallyLoadedModuleNames: ClassViewer, MainFrame, SceneOutliner
- PrivateDependencyModuleNames: AdvancedPreviewScene, AppFramework, AssetDefinition, AssetTools, ClothingSystemRuntimeCommon, ContentBrowser, Core, CoreUObject, Engine, GraphEditor, InputCore, Kismet, LevelEditor, MutableRuntime, MutableTools, Projects, RHI, RawMesh, RenderCore, Slate, SlateCore, TargetPlatform, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: CustomizableObject, CustomizableObjectEditor, CustomizableObjectPopulation, PropertyEditor

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/AssetDefinition_CustomizableObjectPopulation.h` (Private)


#### class `UAssetDefinition_CustomizableObjectPopulation`  
`class UAssetDefinition_CustomizableObjectPopulation final : public UAssetDefinitionDefault`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override`
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L25 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L27 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/AssetDefinition_CustomizableObjectPopulationClass.h` (Private)


#### class `UAssetDefinition_CustomizableObjectPopulationClass`  
`class UAssetDefinition_CustomizableObjectPopulationClass final : public UAssetDefinitionDefault`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override`
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L25 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L27 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/CustomizableObjectPopulationClassDetails.h` (Private)


#### class `SRangeSquare`  
`class SRangeSquare : public SCompoundWidget`  
_L30-73_
- inherits: `SCompoundWidget`
- desc: Widgt that draws a Square to represent a range
- L34 _public function_ `SLATE_BEGIN_ARGS(SRangeSquare) : _SquareColor(FColor(255, 180, 180, 255)),_bDiscrete(false)`
- L35 _public prototype_ `SLATE_ARGUMENT(FColor, SquareColor) SLATE_ARGUMENT(TArray<FConstraintRanges>*, Ranges) SLATE_ARGUMENT(bool, bDiscrete) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _public prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L44 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Allow mouse management
- L45 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _public prototype_ `FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L47 _public prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L52 _private member_ `FColor SquareColor;` — Color of the Square
- L55 _private member_ `TArray<FConstraintRanges>* Ranges;` — Pointer to the list of ranges
- L57 _private member_ `int32 SelectedRangeIndex;`
- L60 _private member_ `FVector2D TextureRectangle;` — Size of the texture decoration of the parameter
- L63 _private member_ `bool bDiscrete;` — The range will be a single value
- L66 _private member_ `bool bMouseDownMin;` — Indicates if the mouse is down on the Min Value
- L69 _private member_ `bool bMouseDownMax;` — Indicates if the mouse is down on the Max
- L72 _private member_ `FSlateBrush Brush;` — Brush to draw the decorations of a parameter option

#### class `SRangeWidget`  
`class SRangeWidget : public SCompoundWidget`  
_L77-124_
- inherits: `SCompoundWidget`
- desc: Widget to manage the ranges of a constraint
- L81 _public function_ `SLATE_BEGIN_ARGS(SRangeWidget):_bDiscrete(false)`
- L82 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_ARGUMENT(IDetailLayoutBuilder*, DetailBuilderPtr) SLATE_ARGUMENT(int32, CharactericticIndex) SLATE_ARGUMENT(int32, ConstraintIndex) SLATE_ARGUMENT(int32, RangeIndex) SLATE_ARGUMENT(bool, bDiscrete) SLATE_ARGUMENT(bool, bRanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L94 _public prototype_ `FReply OnRemoveRangeButtonPressed();` — Callback to remove a Range from the Ranges list of the contraint
- L97 _public prototype_ `void OnMinValueCommited(float InValue, ETextCommit::Type InCommitType);` — Callbacks for the commit of the value of the SpinBox
- L98 _public prototype_ `void OnMaxValueCommited(float InValue, ETextCommit::Type InCommitType);`
- L101 _public prototype_ `void OnMinValueChanged(float InValue);` — Callbacks for the change of the value of the SpinBox
- L102 _public prototype_ `void OnMaxValueChanged(float InValue);`
- L107 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the Population class of the Detials view
- L110 _private member_ `IDetailLayoutBuilder* DetailBuilderPtr = nullptr;` — Pointer to the builder passed by CustomizeDetails method
- L113 _private member_ `int32 CharactericticIndex;` — Index of the characteristic
- L116 _private member_ `int32 ConstraintIndex;` — Index of the contraint
- L119 _private member_ `int32 RangeIndex;` — Index of the Range
- L122 _private member_ `bool bDiscrete;` — The range will be a single value

#### class `SCustomEditorLine`  
`class SCustomEditorLine : public SCompoundWidget`  
_L128-151_
- inherits: `SCompoundWidget`
- desc: Widget to draw a line in the editor
- L132 _public function_ `SLATE_BEGIN_ARGS(SCustomEditorLine) : _LineColor(FColor(50,50,50,255)), _Length(0.0f),_Horizontal(true)`
- L133 _public prototype_ `SLATE_ARGUMENT(FColor, LineColor) SLATE_ARGUMENT(float, Length) SLATE_ARGUMENT(bool, Horizontal) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L139 _public prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L144 _private member_ `FColor LineColor;` — Color of the line
- L147 _private member_ `float Length;` — Length of the line, if 0.0 then will be the length of the tab
- L150 _private member_ `bool Horizontal;` — Bool that represents de orientation of the line. True means an horizontal line, false means a vertical line

#### class `SPopulationClassConstraint`  
`class SPopulationClassConstraint : public SCompoundWidget`  
_L155-269_
- inherits: `SCompoundWidget`
- desc: Widget to represent a single constraint of a Characteristic
- L159 _public function_ `SLATE_BEGIN_ARGS(SPopulationClassConstraint)`
- L160 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_ARGUMENT(IDetailLayoutBuilder*, DetailBuilderPtr) SLATE_ARGUMENT(int32, CharactericticIndex) SLATE_ARGUMENT(int32, ConstraintIndex) SLATE_ARGUMENT(int32, ParameterIndex) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L172 _private prototype_ `void FillConstraintTypesOptions();` — Fills the combobox option source
- L175 _private prototype_ `void FillConstraintTypesStringOptions();` — Fills the contraint types option map to get the strings from the enums
- L178 _private prototype_ `TArray<EPopulationConstraintType> GetConstrinatTypes();` — Returns an array with all the contraint types
- L181 _private prototype_ `TSharedRef<SWidget> OnContraintTypeGenerateWidget(const TSharedPtr<EPopulationConstraintType> InMode) const;` — Builds the contraint types combobox widget
- L184 _private prototype_ `void OnComboBoxSelectionChanged(const TSharedPtr<EPopulationConstraintType> InSelectedMode, ESelectInfo::Type SelectInfo);` — Callback when the contraint type changes
- L187 _private prototype_ `FText ComboBoxSelectionLabel() const;` — Builds the label of the contraints ComboBox
- L190 _private prototype_ `FReply OnRemoveConstraintButtonPressed();` — Callback to remove the contraint
- L193 _private prototype_ `void OnSelectCurveAsset(const FAssetData & AssetData);` — Callback for the selection of the curve asset
- L196 _private prototype_ `FReply OnAddRangeButtonPressed();` — Callback that adds a range to the range contraint
- L199 _private prototype_ `void SetVisibilityCustom();` — Shows a different widget in function of the type of the constraint
- L202 _private prototype_ `void BuildBoolWidget();` — Builders for the different types of contraint widgets
- L203 _private prototype_ `void BuildDiscreteWidget();`
- L204 _private prototype_ `void BuildTagWidget();`
- L205 _private prototype_ `void BuildRangeWidget();`
- L206 _private prototype_ `void BuildCurveWidget();`
- L207 _private prototype_ `void BuildDiscreteColorWidget();`
- L210 _private prototype_ `void OnParameterOptionComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Callbacks to select a parameter option
- L212 _private prototype_ `void OnColorCurveSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L214 _private prototype_ `FReply OnColorPreviewClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L216 _private prototype_ `void OnSetConstantColorFromColorPicker(FLinearColor InColor);`
- L221 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the Population class of the Detials view
- L224 _private member_ `IDetailLayoutBuilder* DetailBuilderPtr = nullptr;` — Pointer to the builder passed by CustomizeDetails method
- L227 _private member_ `int32 CharactericticIndex;` — Index of the characteristic
- L230 _private member_ `int32 ConstraintIndex;` — Index of the contraint
- L233 _private member_ `int32 ParameterIndex;` — Index of the parameter
- L236 _private member_ `TArray< TSharedPtr<FString>> CustomizableObjectParameters;` — List of parameters of the customizable object for the parameters combobox
- L239 _private member_ `TArray< TSharedPtr < EPopulationConstraintType > > ConstraintTypes;` — List with the types of constraints
- L242 _private member_ `TMap<EPopulationConstraintType, FString> ConstraintTypesStrings;` — Map that relates the Constraint type enum with the string
- L245 _private member_ `TSharedPtr<SComboBox<TSharedPtr < EPopulationConstraintType > > > ConstraintTypesComboBox;` — ComboBox to selec the type of a constraint
- L248 _private member_ `TSharedPtr<SVerticalBox> BoolWidget;` — Widgets for the different types of Constraints
- L249 _private member_ `TSharedPtr<SVerticalBox> DiscreteWidget;`
- L250 _private member_ `TSharedPtr<SVerticalBox> TagWidget;`
- L251 _private member_ `TSharedPtr<SVerticalBox> RangeWidget;`
- L252 _private member_ `TSharedPtr<SVerticalBox> CurveWidget;`
- L253 _private member_ `TSharedPtr<SVerticalBox> DiscreteColorWidget;`
- L256 _private member_ `TArray<TSharedPtr<FString>> ParameterOptions;` — List with all the parameter options of the customizable object
- L259 _private member_ `TSharedPtr<STextComboBox> ParameterOptionsComboBox;` — ComboBox to select the parameter of a discrete contraint
- L262 _private member_ `TSharedPtr<STextComboBox> ColorOptionsComboBox;` — Combobox to select the used channel of the color curve
- L265 _private member_ `TArray< TSharedPtr<FString> > ColorOptions;` — Options of the Color Combobox R,G,B,A
- L268 _private member_ `TSharedPtr<SVerticalBox> ColorEditor;` — Pointer to store the color editors to manage the visibility

#### class `SPopulationClassCharacteristic`  
`class SPopulationClassCharacteristic : public SCompoundWidget`  
_L273-310_
- inherits: `SCompoundWidget`
- desc: Widget that manages a single characteristic of the population class
- L277 _public function_ `SLATE_BEGIN_ARGS(SPopulationClassCharacteristic)`
- L278 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_ARGUMENT(IDetailLayoutBuilder*, DetailBuilderPtr) SLATE_ARGUMENT(int32, CharactericticIndex) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L286 _public prototype_ `void OnParameterSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Callback that changes the parameter of the characteristic
- L289 _public prototype_ `FReply OnAddConstraintButtonPessed();` — Callback for the button that adds a constraint to the characteristic
- L292 _public prototype_ `FReply OnRemoveCharacteristicButtonPressed();` — Callback for the button that removes the characteristic from the population class
- L297 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the Population class of the Detials view
- L300 _private member_ `IDetailLayoutBuilder* DetailBuilderPtr = nullptr;` — Pointer to the builder passed by CustomizeDetails method
- L303 _private member_ `int32 CharactericticIndex;` — Index of the Characteristic being edited
- L306 _private member_ `TArray< TSharedPtr<FString>> CustomizableObjectParameters;` — List of parameters of the customizable object for the parameters combobox
- L309 _private member_ `TSharedPtr<SVerticalBox> ConstraintsWidgets;` — Widget to manage the constraints of a Characteristic of the Population Class

#### class `SPopulationClassTagList`  
`class SPopulationClassTagList : public SCompoundWidget`  
_L314-358_
- inherits: `SCompoundWidget`
- desc: Widget that manages a single list
- L318 _public function_ `SLATE_BEGIN_ARGS(SPopulationClassTagList)`
- L319 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_ARGUMENT(IDetailLayoutBuilder*, DetailBuilderPtr) SLATE_ARGUMENT(int32, TagIndex) SLATE_ARGUMENT(TArray< FString >*, ListPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L330 _private prototype_ `void OnComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Callback for the combobox selection changed
- L333 _private prototype_ `FReply OnRemoveTagButtonPressed(int32 Index);` — Callback for the button that removes a tag from a list
- L338 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the Population class of the Detials view
- L341 _private member_ `FString TagValue;` — String Value to print the tag
- L344 _private member_ `int32 TagIndex;` — Index of the tag inside its List
- L347 _private member_ `TArray< TSharedPtr<FString>> AllTags;` — Option Source for the tags combobox
- L350 _private member_ `TArray< FString >* ListPtr;` — Pointer to the list to modify in this widget
- L353 _private member_ `IDetailLayoutBuilder* DetailBuilderPtr = nullptr;` — Pointer to the builder passed by CustomizeDetails method
- L356 _private member_ `TSharedPtr<STextComboBox> TagsComboBox;` — Combobox to select a tag

#### class `SPopulationClassTagManager`  
`class SPopulationClassTagManager : public SCompoundWidget`  
_L362-399_
- inherits: `SCompoundWidget`
- desc: Widget to manage the white and block lists of a Population Class
- L366 _public function_ `SLATE_BEGIN_ARGS(SPopulationClassTagManager)`
- L367 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_ARGUMENT(IDetailLayoutBuilder*, DetailBuilderPtr) SLATE_ARGUMENT(TArray< FString >*, AllowlistPtr) SLATE_ARGUMENT(TArray< FString >*, BlocklistPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L376 _public prototype_ `FReply OnAddTagButtonPressed(bool bIsAllowlist);` — Callback to add a new tag to on of the lists
- L379 _public prototype_ `void BuildAllowlistWidget();` — List Widget Builders
- L380 _public prototype_ `void BuildBlocklistWidget();`
- L385 _private member_ `TSharedPtr<SVerticalBox> AllowlistWidget;` — Widgets to view and add tags of the lists
- L386 _private member_ `TSharedPtr<SVerticalBox> BlocklistWidget;`
- L389 _private member_ `TArray< FString >* AllowlistPtr;` — Pointer to the list to modify in this widget
- L392 _private member_ `TArray< FString >* BlocklistPtr;` — Pointer to the list to modify in this widget
- L395 _private member_ `IDetailLayoutBuilder* DetailBuilderPtr = nullptr;` — Pointer to the builder passed by CustomizeDetails method
- L398 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the Population class of the Detials view

#### class `FCustomizableObjectPopulationClassDetails`  
`class FCustomizableObjectPopulationClassDetails : public IDetailCustomization`  
_L403-436_
- inherits: `IDetailCustomization`
- desc: Details view of the Customizable Object Population Class UObject
- L408 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L411 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface
- L414 _public prototype_ `void BuildCharacteristicsWidgets();` — Builds the Characteristics widget
- L417 _public prototype_ `FReply OnAddCharacteristicButtonPessed();` — Button callback that adds a Characteristic to the Population Class
- L420 _public prototype_ `void OnCustomizableObjectPropertyChanged();` — Callback of the Customizable Object Property
- L425 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the Population Class open in the Editor
- L428 _private member_ `TSharedPtr<SPopulationClassTagManager> TagManagementWidgets;` — Widget to manageme the white and block lists of the Population Class
- L431 _private member_ `TSharedPtr<SVerticalBox> CharacteristicsWidgets;` — Widget to manage tje characteristics of the Population Class
- L434 _private member_ `IDetailLayoutBuilder* DetailBuilderPtr = nullptr;` — Pointer to the builder passed by CustomizeDetails method

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`
- L11 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/CustomizableObjectPopulationClassEditor.h` (Private)


#### class `FCustomizableObjectPopulationClassEditor`  
`class FCustomizableObjectPopulationClassEditor : public ICustomizableObjectPopulationClassEditor, public FEditorUndoClient, public FNotifyHook, public FTickableEditorObject, public FGCObject`  
_L21-173_
- inherits: `ICustomizableObjectPopulationClassEditor,FEditorUndoClient,FNotifyHook,FTickableEditorObject,FGCObject`
- L30 _public prototype_ `FCustomizableObjectPopulationClassEditor();`
- L31 _public prototype_ `~FCustomizableObjectPopulationClassEditor();`
- L34 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — FGCObjet functions
- L35 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L38 _public prototype_ `void InitCustomizableObjectPopulationClassEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost >& InitToolkitHost, UCustomizableObjectPopulationClass* InObject);` — Editor init
- L41 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L42 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L43 _public prototype_ `virtual FText GetToolkitName() const override;`
- L44 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L45 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L48 _public prototype_ `virtual bool IsTickable(void) const override;` — FTickableGameObject interface
- L49 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L50 _public prototype_ `virtual TStatId GetStatId() const override;`
- L53 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L56 _public function_ `virtual UCustomizableObjectPopulationClass* GetCustomAsset()` — Begin ICustomAssetEditor initerface
- L57 _public prototype_ `virtual void SetCustomAsset(UCustomizableObjectPopulationClass* InCustomAsset) override;`
- L59 _public function_ `virtual FString GetReferencerName() const override`
- L67 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PopulationClassProperties(const FSpawnTabArgs& Args);` — Tab Spawners
- L68 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PopulationClassTagsTool(const FSpawnTabArgs& Args);`
- L69 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CurveEditor(const FSpawnTabArgs& Args);`
- L70 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L75 _private prototype_ `void BindCommands();` — Binds commands associated with the Static Mesh Editor.
- L78 _private prototype_ `void ExpandToolBar();` — Adds the Customizable Object Population Editor commands to the default toolbar
- L81 _private prototype_ `void SaveAsset_Execute() override;` — Save Customizable Object Population Class open in editor
- L83 _private prototype_ `bool CustomizableObjectCanBeSaved() const;`
- L84 _private prototype_ `void SaveCustomizableObject();`
- L85 _private prototype_ `bool EditorCurveCanBeSaved() const;`
- L86 _private prototype_ `void SaveEditorCurve();`
- L90 _private prototype_ `bool CanOpenInstance();` — Instance inspection functions
- L91 _private prototype_ `void OpenInstance();`
- L92 _private prototype_ `void OpenSkeletalMesh();`
- L96 _private prototype_ `bool CanOpenCustomizableObjectEditor();` — Opens the Customizable Object into an editor
- L97 _private prototype_ `void OpenCustomizableObjectInEditor();`
- L100 _private prototype_ `void TestPopulationClass();` — Generate instances in the viewport to test the population
- L102 _private prototype_ `TSharedRef<SWidget> GenerateTestPopulationMenuContent(TSharedRef<FUICommandList> InCommandList);`
- L104 _private prototype_ `TOptional<int32> GetTestPopulationInstancesNum() const;`
- L105 _private prototype_ `void OnTestPopulationInstancesNumChanged(int32 Value);`
- L107 _private prototype_ `TSharedRef<SWidget> GeneratePopulationClassInstancesMenuContent(TSharedRef<FUICommandList> InCommandList);`
- L108 _private prototype_ `TOptional<int32> GetPopulationClassAssetInstancesNum() const;`
- L109 _private prototype_ `void OnPopulationClassAssetInstancesNumChanged(int32 Value);`
- L112 _private prototype_ `void GeneratePopulationClassInstances();` — Generates instance assets of the population
- L115 _private prototype_ `void RecompileAllPopulations();` — Recompile all the populations where this class is referenced
- L120 _private member_ `TObjectPtr<UCustomizableObjectPopulationClass> PopulationClass;` — Pointer to the Population Class open in this editor
- L123 _private member_ `static const FName PopulationClassPropertiesTabId;` — Tabs IDs
- L124 _private member_ `static const FName PopulationClassTagsToolId;`
- L125 _private member_ `static const FName CurveEditorTabId;`
- L126 _private member_ `static const FName ViewportTabId;`
- L129 _private member_ `TSharedPtr<class IDetailsView> PopulationClassDetailsView;` — Population Class Property View
- L132 _private member_ `TSharedPtr<class SCustomizableObjectPopulationClassTagsTool> TagsTool;` — Tags Tool
- L135 _private member_ `TSharedPtr<class SCurveEditor> CurveEditor;` — Curve editor to edit the curve of a population class characteristic
- L137 _private member_ `class FCustomizableObjectPopulationClassDetails* PopulationClassDetailsPtr;`
- L140 _private member_ `TObjectPtr<UCurveBase> CurrentEditorCurve;` — Current curve shown in editor
- L143 _private member_ `bool bRefreshDetailsView;` — Indicates when the Details View needs to be refreshed
- L146 _private member_ `TSharedPtr<class SCustomizableObjectPopulationEditorViewport> Viewport;` — Editor Viewport
- L149 _private member_ `int32 TestPopulationInstancesNum;` — Number of instances that will be generated in the preview viewport
- L152 _private member_ `int32 PopulationClassAssetInstancesNum;` — Number of instances that will be generated and saved
- L155 _private member_ `TSharedPtr< SNumericEntryBox<int32> > TestPopulationInstancesNumEntry;` — Box to select the number of instances spawned in the viewport
- L158 _private member_ `TSharedPtr< SNumericEntryBox<int32> > PopulationClassAssetInstancesNumEntry;` — Box to select the number of instances to save
- L161 _private member_ `int32 ViewportColumns;` — Viewport instance configuration
- L162 _private member_ `int32 InstanceSeparation;`
- L163 _private member_ `TSharedPtr< SNumericEntryBox<int32> > ViewportColumnsEntry;`
- L164 _private member_ `TSharedPtr< SNumericEntryBox<int32> > InstanceSeparationEntry;`
- L167 _private member_ `TArray<TObjectPtr<class UCustomizableSkeletalComponent>> PreviewCustomizableSkeletalComponents;` — Components to preview instances on the viewport
- L168 _private member_ `TArray<TObjectPtr<class USkeletalMeshComponent>> PreviewSkeletalMeshComponents;`
- L169 _private member_ `TArray<class UCapsuleComponent*> ColliderComponents;`
- L170 _private member_ `TArray<TObjectPtr<UCustomizableObjectInstance>> ViewportInstances;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/CustomizableObjectPopulationEditor.h` (Private)


#### class `FCustomizableObjectPopulationEditor`  
`class FCustomizableObjectPopulationEditor : public ICustomizableObjectPopulationEditor, public FEditorUndoClient, public FNotifyHook, public FTickableEditorObject, public FGCObject`  
_L20-144_
- inherits: `ICustomizableObjectPopulationEditor,FEditorUndoClient,FNotifyHook,FTickableEditorObject,FGCObject`
- L29 _public prototype_ `FCustomizableObjectPopulationEditor();`
- L30 _public prototype_ `~FCustomizableObjectPopulationEditor();`
- L33 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — FGCObjet functions
- L34 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L37 _public prototype_ `void InitCustomizableObjectPopulationEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost >& InitToolkitHost, UCustomizableObjectPopulation* InObject);` — Editor init
- L40 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L41 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L42 _public prototype_ `virtual FText GetToolkitName() const override;`
- L43 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L44 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L47 _public prototype_ `virtual bool IsTickable(void) const override;` — FTickableGameObject interface
- L48 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L49 _public prototype_ `virtual TStatId GetStatId() const override;`
- L52 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L55 _public function_ `virtual UCustomizableObjectPopulation* GetCustomAsset()` — Begin ICustomAssetEditor initerface
- L56 _public prototype_ `virtual void SetCustomAsset(UCustomizableObjectPopulation* InCustomAsset) override;`
- L58 _public function_ `virtual FString GetReferencerName() const override`
- L66 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PopulationProperties(const FSpawnTabArgs& Args);` — Tab Spawners
- L67 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L72 _private prototype_ `void ExtendToolbar();` — Adds the Customizable Object Population Editor commands to the default toolbar
- L75 _private prototype_ `void BindCommands();` — Binds commands associated with the Static Mesh Editor.
- L78 _private prototype_ `void SaveAsset_Execute() override;` — Save Customizable Object Population open in editor
- L79 _private prototype_ `bool CanOpenInstance();`
- L83 _private prototype_ `void OpenInstance();` — Inspect instances functions
- L84 _private prototype_ `void OpenSkeletalMesh();`
- L87 _private prototype_ `TSharedRef<SWidget> GenerateTestPopulationMenuContent(TSharedRef<FUICommandList> InCommandList);`
- L88 _private prototype_ `TOptional<int32> GetTestPopulationInstancesNum() const;`
- L89 _private prototype_ `void OnTestPopulationInstancesNumChanged(int32 Value);`
- L91 _private prototype_ `TSharedRef<SWidget> GeneratePopulationInstancesMenuContent(TSharedRef<FUICommandList> InCommandList);`
- L92 _private prototype_ `TOptional<int32> GetPopulationAssetInstancesNum() const;`
- L93 _private prototype_ `void OnPopulationAssetInstancesNumChanged(int32 Value);`
- L96 _private prototype_ `void TestPopulation();` — Generate instances in the viewport to test the population
- L99 _private prototype_ `void GeneratePopulationInstances();` — Generates instance assets of the population
- L107 _private member_ `TObjectPtr<UCustomizableObjectPopulation> Population;` — Pointer to the Population Class open in this editor
- L110 _private member_ `static const FName PopulationPropertiesTabId;` — Tabs IDs
- L111 _private member_ `static const FName PopulationViewportTabId;`
- L114 _private member_ `TSharedPtr<class IDetailsView> PopulationDetailsView;` — Population Class Property View
- L117 _private member_ `TSharedPtr<class SCustomizableObjectPopulationEditorViewport> Viewport;` — Editor Viewport
- L120 _private member_ `int32 TestPopulationInstancesNum;` — Number of instances that will be generated in the preview viewport
- L123 _private member_ `int32 PopulationAssetInstancesNum;` — Number of instances that will be generated and saved
- L126 _private member_ `TSharedPtr< SNumericEntryBox<int32> > TestPopulationInstancesNumEntry;` — Box to select the number of instances spawned in the viewport
- L129 _private member_ `TSharedPtr< SNumericEntryBox<int32> > PopulationAssetInstancesNumEntry;` — Box to select the number of instances to save
- L132 _private member_ `int32 ViewportColumns;` — Viewport instance configuration
- L133 _private member_ `int32 InstanceSeparation;`
- L134 _private member_ `TSharedPtr< SNumericEntryBox<int32> > ViewportColumnsEntry;`
- L135 _private member_ `TSharedPtr< SNumericEntryBox<int32> > InstanceSeparationEntry;`
- L138 _private member_ `TArray<class UCustomizableSkeletalComponent*> PreviewCustomizableSkeletalComponents;` — Components to preview instances on the viewport
- L139 _private member_ `TArray<class USkeletalMeshComponent*> PreviewSkeletalMeshComponents;`
- L140 _private member_ `TArray<class UCapsuleComponent*> ColliderComponents;`
- L141 _private member_ `TArray<UCustomizableObjectInstance*> ViewportInstances;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/CustomizableObjectPopulationEditorStyle.h` (Private)


#### class `FCustomizableObjectPopulationEditorStyle`  
`class FCustomizableObjectPopulationEditorStyle`  
_L10-35_
- desc: Manages the style which provides resources for niagara editor widgets.
- L15 _public prototype_ `static void Initialize();` — Creates and Registers the plugin SlateStyle
- L18 _public prototype_ `static void Shutdown();` — Unregisters the plugin SlateStyle
- L21 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for niagara editor widgets
- L23 _public prototype_ `static FName GetStyleSetName();`
- L24 _public prototype_ `static FString RelativePathToPluginPath(const FString& RelativePath, const ANSICHAR* Extension);`
- L30 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();` — Creates the plugin style
- L34 _private member_ `static TSharedPtr< class FSlateStyleSet > CustomizableObjectPopulationEditorStyleInstance;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/CustomizableObjectPopulationEditorViewportClient.h` (Private)


#### class `FCustomizableObjectPopulationEditorViewportClient`  
`class FCustomizableObjectPopulationEditorViewportClient : public FEditorViewportClient`  
_L14-45_
- inherits: `FEditorViewportClient`
- L18 _public prototype_ `FCustomizableObjectPopulationEditorViewportClient(const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);`
- L19 _public prototype_ `~FCustomizableObjectPopulationEditorViewportClient();`
- L21 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L23 _public prototype_ `void SetPreviewComponent(TArray<USkeletalMeshComponent*> InSkeletalMeshComponent, TArray<class UCapsuleComponent*> InColliderComponents);`
- L26 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L30 _public prototype_ `void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;` — Select an instance of the viewport
- L32 _public function_ `int32 GetSelectedInstance()`
- L37 _private member_ `TArray<TObjectPtr<USkeletalMeshComponent>> SkeletalMeshComponents;` — All the Skeletal Mesh components of the scene
- L40 _private member_ `TArray<TObjectPtr<class UCapsuleComponent>> ColliderComponents;` — All the Collider components of the scene
- L43 _private member_ `int32 SelectedInstance;` — index of the selected instance

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/SCustomizableObjectPopulationClassTagManager.h` (Private)


#### class `SCustomizableObjectPopulationClassTagsManager`  
`class SCustomizableObjectPopulationClassTagsManager : public SCompoundWidget`  
_L16-59_
- inherits: `SCompoundWidget`
- desc: Tool to manage the population class tags of a customizable object
- L20 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectPopulationClassTagsManager)`
- L21 _public prototype_ `SLATE_ARGUMENT(UCustomizableObject*, CustomizableObject) SLATE_ARGUMENT(UCustomizableObject*, RootObject) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `void RebuildWidget();`
- L29 _public prototype_ `void BuildTagSelector();`
- L30 _public prototype_ `void BuildTagManager();`
- L32 _public prototype_ `FReply OnAddTagSelectorButtonPressed();`
- L33 _public prototype_ `FReply OnAddTagButtonPressed();`
- L34 _public prototype_ `void OnComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo, int32 Index);`
- L35 _public prototype_ `FReply OnRemoveTagSelectorClicked(int32 Index);`
- L36 _public prototype_ `FReply OnRemoveTagClicked(int32 Index);`
- L37 _public prototype_ `void OnTextCommited(const FText& NewText, ETextCommit::Type InTextCommit, int32 Index);`
- L42 _private member_ `UCustomizableObject* CustomizableObject;` — Pointer to the Customizable object opened in the editor
- L45 _private member_ `UCustomizableObject* RootObject;` — Pointer to the root Customizable Object
- L48 _private member_ `TSharedPtr<class SScrollBox> ScrollBox;` — Widget Scrollbox
- L51 _private member_ `TSharedPtr<SVerticalBox> TagSelector;`
- L54 _private member_ `TSharedPtr<SVerticalBox> TagManager;`
- L57 _private member_ `TArray<TSharedPtr<FString>> TagOptions;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ESelectInfo`
- L8 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/SCustomizableObjectPopulationClassTagsTool.h` (Private)


#### class `SSingleTagWidget`  
`class SSingleTagWidget : public SCompoundWidget`  
_L22-60_
- inherits: `SCompoundWidget`
- desc: Widget to manage a single tag
- L26 _public function_ `SLATE_BEGIN_ARGS(SSingleTagWidget)`
- L27 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_ARGUMENT(class SCustomizableObjectPopulationClassTagsTool*, TagsToolPtr) SLATE_ARGUMENT(int32, TagIndex) SLATE_ARGUMENT(TArray<FString>*, TagsList) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `void OnTagsComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Callback for OnSelectionchanged of the tags ComboBox
- L39 _public prototype_ `FReply OnRemoveTagButtonPressed();` — Callback for OnClicked of the remove tag button
- L44 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the population class that is being edited
- L47 _private member_ `TArray<TSharedPtr<FString>> ComboBoxTagsOptions;` — List with all the tags for the tags ComboBox Options
- L50 _private member_ `TSharedPtr<STextComboBox> TagsComboBox;` — ComboBox with all the possigle tags
- L53 _private member_ `int32 TagIndex;` — Index of the tag
- L56 _private member_ `class SCustomizableObjectPopulationClassTagsTool* TagsToolPtr;` — Pointer to the tags tool
- L59 _private member_ `TArray<FString>* TagsList;` — List of tags of the selected parameter

#### class `SParameterTagWidget`  
`class SParameterTagWidget : public SCompoundWidget`  
_L64-89_
- inherits: `SCompoundWidget`
- desc: Widget to manage the tags of a parameter
- L68 _public function_ `SLATE_BEGIN_ARGS(SParameterTagWidget)`
- L69 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_ARGUMENT(class SCustomizableObjectPopulationClassTagsTool*, TagsToolPtr) SLATE_ARGUMENT(TArray<FString>*, TagsList) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L79 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the population class that is being edited
- L82 _private member_ `class SCustomizableObjectPopulationClassTagsTool* TagsToolPtr;` — Pointer to the tags tool
- L85 _private member_ `TArray<FString>* TagsList;` — List of tags of the selected parameter
- L88 _private member_ `TSharedPtr<SVerticalBox> Rows;` — Row representation of the tags

#### class `SCustomizableObjectPopulationClassTagsTool`  
`class SCustomizableObjectPopulationClassTagsTool : public SCompoundWidget`  
_L93-183_
- inherits: `SCompoundWidget`
- desc: Tool to manage the tags of the parameters and its parameter options
- L97 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectPopulationClassTagsTool)`
- L98 _public prototype_ `SLATE_ARGUMENT(UCustomizableObjectPopulationClass*, PopulationClass) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L102 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L105 _public prototype_ `void GenerateTagsManager();` — Widget Generators
- L106 _public prototype_ `void GenerateTagsViewer();`
- L107 _public prototype_ `void GenerateParameterManager();`
- L108 _public prototype_ `void GenerateParameterOptionsManager();`
- L109 _public prototype_ `void GenerateChildSlot();`
- L112 _public prototype_ `FReply OnRemoveTagButtonPressed(int32 Index);` — Callback for the OnClicked of the RemoveTag button
- L115 _public prototype_ `FReply OnAddTagButtonPressed();` — Callback for the OnClicked of the RemoveTag button
- L118 _public prototype_ `void OnSearchBoxFilterTextChanged(const FText& InText);` — Callback for the OnTextChanged of the Searchbox
- L121 _public prototype_ `void OnSearchBoxTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Callback for the OnTextCommited of the Searchbox
- L124 _public prototype_ `void OnParameterComboBoxSelectionChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Callback for the OnSelectionChanged of parameters ComboBox
- L127 _public prototype_ `FReply OnParameterAddTagButtonPressed();` — Callback for the OnClicked AddTag button of a parameter
- L130 _public prototype_ `FReply OnParameterOptionAddTagButtonPressed(FString ParameterOptionName);` — Callback for the OnClicked AddTag button of a parameter optiion
- L133 _public prototype_ `const FSlateBrush* GetExpandableAreaBorderImage(const SExpandableArea& Area);` — Returns the image used to render the expandable area title bar with respect to its hover/expand state.
- L138 _private member_ `UCustomizableObjectPopulationClass* PopulationClass;` — Pointer to the population class that is being edited
- L141 _private member_ `UCustomizableObject* SelectedCustomizableObject;` — Pointer to the Customizable Object of the Population Class
- L144 _private member_ `TSharedPtr<SExpandableArea> TagsManagerExpandableArea;` — Expandable area widget of the tags manager
- L147 _private member_ `TSharedPtr<SVerticalBox> TagsManager;` — Widget that stores the Tags Manager
- L150 _private member_ `TSharedPtr<SVerticalBox> TagsViewer;` — Widget that shows the Tags
- L153 _private member_ `TSharedPtr<SHorizontalBox> ParametersManager;` — Widget that stores the Parameters Manager
- L156 _private member_ `TSharedPtr<SExpandableArea> ParameterOptionsManagerExpandableArea;` — Expandable area widget of the parameters options manager
- L159 _private member_ `TSharedPtr<SVerticalBox> ParameterOptionsManager;` — Widget that stores the Parameter Options Manager
- L162 _private member_ `TSharedPtr<SSearchBox> SearchBoxWidget;` — Search box of the ComboButton
- L165 _private member_ `FString SearchItem;` — Stores the input of the Searchboc widget
- L168 _private member_ `TSharedPtr<STextComboBox> ParameterComboBox;` — Parameters Combobox Widget
- L171 _private member_ `TArray<TSharedPtr<FString>> ParameterComboBoxOptions;` — Options shown in the parameters combobox
- L174 _private member_ `FString LastSelectedParameter;` — Selected parameter of the parameter combobox
- L177 _private member_ `TSharedPtr<class SScrollBox> ScrollBox;` — Widget Scrollbox
- L178 _private member_ `TSharedPtr<class SScrollBox> TagsScrollBox;`
- L181 _private member_ `bool bNeedsUpdate;` — if true means that the tool needs to be redrawed

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ESelectInfo`
- L8 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/SCustomizableObjectPopulationEditorViewport.h` (Private)


#### class `SCustomizableObjectPopulationEditorViewport`  
`class SCustomizableObjectPopulationEditorViewport : public SEditorViewport, public FGCObject`  
_L17-63_
- inherits: `SEditorViewport,FGCObject`
- L21 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectPopulationEditorViewport)` — the OwnerHUD var is passed to the widget so the owner can be set.
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L29 _public prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L31 _public prototype_ `void SetPreviewComponents(const TArray<USkeletalMeshComponent*>& SkeletalMeshes, const TArray<class UCapsuleComponent*>& ColliderComponents, int32 Columns, int32 Separation);`
- L36 _public prototype_ `void RefreshViewport();`
- L38 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L41 _public prototype_ `int32 GetSelectedInstance();` — Returns the index of the selected instance in the viewport
- L43 _public function_ `virtual FString GetReferencerName() const override`
- L51 _private member_ `TSharedPtr<class FCustomizableObjectPopulationEditorViewportClient> EditorViewportClient;` — Editor viewport client
- L54 _private member_ `TSharedPtr< FAdvancedPreviewScene > PreviewScene;` — The preview scene that we are viewing
- L57 _private member_ `TArray<TObjectPtr<USkeletalMeshComponent>> PreviewSkeletalMeshes;` — Current skeletal meshes
- L60 _private member_ `TArray<UCapsuleComponent*> PreviewCollisionComponents;` — Current Collider Components
- L62 _private prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Private/MuCOPE/SCustomizableObjectPopulationEditorViewportToolBar.h` (Private)


#### class `SCustomizableObjectPopulationEditorViewportToolBar`  
`class SCustomizableObjectPopulationEditorViewportToolBar : public SViewportToolBar`  
_L16-73_
- inherits: `SViewportToolBar`
- desc: A level viewport toolbar widget that is placed in a viewport
- L19 _public function_ `SLATE_BEGIN_ARGS(SCustomizableObjectPopulationEditorViewportToolBar)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class SCustomizableObjectPopulationEditorViewport> InViewport);`
- L30 _private prototype_ `TSharedRef<SWidget> GenerateViewMenu() const;` — Generates the toolbar view menu content @return The widget containing the view menu content
- L37 _private prototype_ `TSharedRef<SWidget> GenerateViewportTypeMenu() const;` — Generates the toolbar viewport type menu content @return The widget containing the viewport type menu content
- L42 _private prototype_ `FSlateColor GetFontColor() const;` — Generate color of the text on the top
- L45 _private prototype_ `float OnGetFOVValue() const;` — Called by the FOV slider in the perspective viewport to get the FOV value
- L47 _private prototype_ `void OnFOVValueChanged(float NewValue) const;` — Called when the FOV slider is adjusted in the perspective viewport
- L49 _private function_ `void OnFOVValueCommitted(float NewValue, ETextCommit::Type CommitInfo)` — Called when a value is entered into the FOV slider/box in the perspective viewport
- L52 _private prototype_ `FReply OnMenuClicked();` — Callback for drop-down menu with FOV and high resolution screenshot options currently
- L55 _private prototype_ `TSharedRef<SWidget> GenerateOptionsMenu() const;` — Generates drop-down menu with FOV and high resolution screenshot options currently
- L58 _private prototype_ `TSharedRef<SWidget> GenerateFOVMenu() const;` — Generates widgets for viewport camera FOV control
- L62 _private member_ `TWeakPtr<class SCustomizableObjectPopulationEditorViewport> Viewport;` — The viewport that we are in
- L65 _private member_ `TSharedPtr<class SButton> CompileErrorLayout;` — Layout to show information about instance skeletal mesh update / CO asset data
- L68 _private member_ `TSharedPtr<class SButton> UpdateInfoLayout;` — Layout to show if the skeletal mesh of a functional CO is being updated
- L70 _private member_ `SViewportToolBar* CastedViewportToolbar;`
- L72 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Public/MuCOPE/CustomizableObjectPopulationClassEditorActions.h` (Public)


#### class `FCustomizableObjectPopulationClassEditorCommands`  
`class FCustomizableObjectPopulationClassEditorCommands : public TCommands<FCustomizableObjectPopulationClassEditorCommands>`  
_L9-29_
- inherits: `TCommands<FCustomizableObjectPopulationClassEditorCommands>`
- L13 _public prototype_ `FCustomizableObjectPopulationClassEditorCommands();`
- L15 _public member_ `TSharedPtr< FUICommandInfo > Save;`
- L16 _public member_ `TSharedPtr< FUICommandInfo > SaveCustomizableObject;`
- L17 _public member_ `TSharedPtr< FUICommandInfo > OpenCustomizableObjectEditor;`
- L18 _public member_ `TSharedPtr< FUICommandInfo > SaveEditorCurve;`
- L19 _public member_ `TSharedPtr< FUICommandInfo > TestPopulationClass;`
- L20 _public member_ `TSharedPtr< FUICommandInfo > GenerateInstances;`
- L21 _public member_ `TSharedPtr< FUICommandInfo > InspectSelectedInstance;`
- L22 _public member_ `TSharedPtr< FUICommandInfo > InspectSelectedSkeletalMesh;`
- L27 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Public/MuCOPE/CustomizableObjectPopulationClassFactory.h` (Public)


#### class `UCustomizableObjectPopulationClassFactory`  
`class UCustomizableObjectPopulationClassFactory : public UFactory`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L19 _private prototype_ `UCustomizableObjectPopulationClassFactory();`
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Public/MuCOPE/CustomizableObjectPopulationEditorActions.h` (Public)


#### class `FCustomizableObjectPopulationEditorCommands`  
`class FCustomizableObjectPopulationEditorCommands : public TCommands<FCustomizableObjectPopulationEditorCommands>`  
_L9-26_
- inherits: `TCommands<FCustomizableObjectPopulationEditorCommands>`
- L13 _public prototype_ `FCustomizableObjectPopulationEditorCommands();`
- L15 _public member_ `TSharedPtr< FUICommandInfo > Save;`
- L16 _public member_ `TSharedPtr< FUICommandInfo > TestPopulation;`
- L17 _public member_ `TSharedPtr< FUICommandInfo > GenerateInstances;`
- L18 _public member_ `TSharedPtr< FUICommandInfo > InspectSelectedInstance;`
- L19 _public member_ `TSharedPtr< FUICommandInfo > InspectSelectedSkeletalMesh;`
- L24 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Public/MuCOPE/CustomizableObjectPopulationEditorModule.h` (Public)


#### class `ICustomizableObjectPopulationEditorModule`  
`class ICustomizableObjectPopulationEditorModule : public IModuleInterface`  
_L22-40_
- inherits: `IModuleInterface`
- desc: Customizable object population editor module interface
- L27 _public function_ `static inline ICustomizableObjectPopulationEditorModule& Get()`
- L35 _public prototype_ `virtual TSharedRef<ICustomizableObjectPopulationEditor> CreateCustomizableObjectPopulationEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UCustomizableObjectPopulation* CustomizablePopulation) = 0;` — Creates a new customizable object population editor.
- L36 _public prototype_ `virtual TSharedRef<ICustomizableObjectPopulationClassEditor> CreateCustomizableObjectPopulationClassEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UCustomizableObjectPopulationClass* CustomizablePopulationClass) = 0;`
- L37 _public function_ `virtual TSharedPtr<class FExtensibilityManager> GetCustomizableObjectPopulationEditorToolBarExtensibilityManager()`

#### Free symbols / members of external scopes

- L14 _externvar_ `extern const FName CustomizableObjectEditorAppIdentifier;`
- L15 _externvar_ `extern const FName CustomizableObjectInstanceEditorAppIdentifier;`
- L16 _externvar_ `extern const FName CustomizableObjectPopulationEditorAppIdentifier;`
- L17 _externvar_ `extern const FName CustomizableObjectPopulationClassEditorAppIdentifier;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Public/MuCOPE/CustomizableObjectPopulationFactory.h` (Public)


#### class `UCustomizableObjectPopulationFactory`  
`class UCustomizableObjectPopulationFactory : public UFactory`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L19 _private prototype_ `UCustomizableObjectPopulationFactory();`
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Public/MuCOPE/ICustomizableObjectPopulationClassEditor.h` (Public)


#### class `ICustomizableObjectPopulationClassEditor`  
`class ICustomizableObjectPopulationClassEditor : public FAssetEditorToolkit`  
_L12-20_
- inherits: `FAssetEditorToolkit`
- desc: Public interface to Static Mesh Editor
- L16 _public prototype_ `virtual UCustomizableObjectPopulationClass* GetCustomAsset() = 0;` — Retrieves the current custom asset.
- L19 _public function_ `virtual void SetCustomAsset(UCustomizableObjectPopulationClass* InCustomAsset)` — Set the current custom asset.

### `Plugins/Experimental/MutablePopulation/Source/CustomizableObjectPopulationEditor/Public/MuCOPE/ICustomizableObjectPopulationEditor.h` (Public)


#### class `ICustomizableObjectPopulationEditor`  
`class ICustomizableObjectPopulationEditor : public FAssetEditorToolkit`  
_L12-20_
- inherits: `FAssetEditorToolkit`
- desc: Public interface to Static Mesh Editor
- L16 _public prototype_ `virtual UCustomizableObjectPopulation* GetCustomAsset() = 0;` — Retrieves the current custom asset.
- L19 _public function_ `virtual void SetCustomAsset(UCustomizableObjectPopulation* InCustomAsset)` — Set the current custom asset.
