# Plugins / MeshPartitionEditorUI

- module root: `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI`
- headers: 14; symbols: 440
- symbol kinds: class=18, delegate=2, enum=1, enumerator=9, function=15, macro=3, member=108, namespace=30, prototype=203, struct=45, typedef=6
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DynamicMesh, Engine, GeometryAlgorithms, GeometryCore, GeometryFramework, GeometryScriptingEditor, InputCore, LevelEditor, MeshConversion, MeshPartition, MeshPartitionEditor, ModelingEditorUI, Projects, PropertyEditor, RHI, RenderCore, Renderer, SceneOutliner, Slate, SlateCore, SourceControl, TedsEditorCompatibility, TedsOutliner, TedsQueryStack, TedsTableViewer, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/MeshPartitionEditorUIStyle.h` (Private)


#### class `FMegaMeshEditorUIStyle`  
`class FMegaMeshEditorUIStyle`  
_L9-28_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static void ReloadTextures();` — Reloads textures used by slate renderer
- L19 _public prototype_ `static TSharedRef<ISlateStyle> Get();` — @return The Slate style set for the Shooter game
- L21 _public prototype_ `static FName GetStyleSetName();`
- L24 _private prototype_ `static TSharedRef<class FSlateStyleSet> Create();`
- L25 _private prototype_ `static FString InContent(const FString& InRelativePath, const ANSICHAR* InExtension);`
- L27 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleInstance;`

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/MeshPartitionToggleableConstraintNameCustomization.h` (Private)


#### class `UE::MeshPartition::FToggleableConstraintNameCustomization`  
`class FToggleableConstraintNameCustomization : public IPropertyTypeCustomization`  
_L18-38_
- inherits: `IPropertyTypeCustomization`
- desc: Creates a widget that has a toggle that either uses GetOptions metadata function for constraining the options, or allows text entry if the toggle is off.
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L24 _public function_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — Does nothing, so that the child row is placed inline where the channel name selector is placed.
- L29 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L35 _private member_ `TSharedPtr<SSearchableComboBox> ComboBox;`
- L36 _private member_ `TArray<TSharedPtr<FString>> ChannelOptions;`
- L37 _private prototype_ `void ReinitializeOptions(TSharedRef<IPropertyHandle> StructHandle, bool& bCurrentNameIsValidOption);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/UI/MeshPartitionBuildCostWidget.h` (Private)


#### struct `UE::MeshPartition::FMegaMeshBuildCostWidgetHeaderConstructor`  
`struct FMegaMeshBuildCostWidgetHeaderConstructor : public FSimpleWidgetConstructor`  
_L25-41_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L30 _public prototype_ `FMegaMeshBuildCostWidgetHeaderConstructor();`
- L31 _public prototype_ `~FMegaMeshBuildCostWidgetHeaderConstructor() override = default;`
- L33 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FMegaMeshBuildCostWidgetConstructorDelegator`  
`struct FMegaMeshBuildCostWidgetConstructorDelegator : public FSimpleWidgetConstructor`  
_L44-60_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L49 _public prototype_ `FMegaMeshBuildCostWidgetConstructorDelegator();`
- L50 _public prototype_ `~FMegaMeshBuildCostWidgetConstructorDelegator() override = default;`
- L52 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FMegaMeshBuildCostWidgetConstructor`  
`struct FMegaMeshBuildCostWidgetConstructor : public FSimpleWidgetConstructor`  
_L64-80_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L69 _public prototype_ `FMegaMeshBuildCostWidgetConstructor();`
- L70 _public prototype_ `~FMegaMeshBuildCostWidgetConstructor() override = default;`
- L72 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UE::MeshPartition::SMegaMeshBuildCostWidget`  
`class SMegaMeshBuildCostWidget : public SCompoundWidget`  
_L84-113_
- inherits: `SCompoundWidget`
- L86 _private typedef_ `using RowHandle = UE::Editor::DataStorage::RowHandle;`
- L89 _public function_ `SLATE_BEGIN_ARGS(SMegaMeshBuildCostWidget)`
- L90 _public prototype_ `SLATE_ATTRIBUTE(bool, UseAggregateView);`
- L91 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow, const RowHandle& InWidgetRow);`
- L99 _protected prototype_ `FText GetLabel() const;`
- L100 _protected prototype_ `FSlateColor GetColor() const;`
- L102 _protected prototype_ `const FSlateBrush* GetAggregateImageBrush() const;`
- L103 _protected prototype_ `FSlateColor GetAggregateColor() const;`
- L105 _protected member_ `RowHandle TargetRow;`
- L106 _protected member_ `RowHandle WidgetRow;`
- L110 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L111 _private prototype_ `static UE::Editor::DataStorage::IUiProvider* GetDataStorageUI();`
- L112 _private prototype_ `static UE::Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`

#### struct `UE::MeshPartition::FMegaMeshBuildCostAggregateWidgetConstructor`  
`struct FMegaMeshBuildCostAggregateWidgetConstructor : public FSimpleWidgetConstructor`  
_L116-132_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L121 _public prototype_ `FMegaMeshBuildCostAggregateWidgetConstructor();`
- L122 _public prototype_ `~FMegaMeshBuildCostAggregateWidgetConstructor() override = default;`
- L124 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UE::MeshPartition::SBuildStatsToolTip`  
`class SBuildStatsToolTip : public SToolTip`  
_L135-162_
- inherits: `SToolTip`
- L138 _public function_ `SLATE_BEGIN_ARGS(SBuildStatsToolTip) : _TargetRow(UE::Editor::DataStorage::InvalidRowHandle) , _DataStorage(nullptr)`
- L144 _public prototype_ `SLATE_ARGUMENT(UE::Editor::DataStorage::RowHandle, TargetRow) SLATE_ARGUMENT(UE::Editor::DataStorage::ICoreProvider*, DataStorage) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L151 _public prototype_ `FSlateColor GetColor(double Time, FMegaMeshTimingStatistics TimingStats) const;`
- L154 _public prototype_ `virtual bool IsEmpty() const override;` — IToolTip interface
- L155 _public prototype_ `virtual void OnOpening() override;`
- L156 _public prototype_ `virtual bool IsInteractive() const override;`
- L157 _public prototype_ `virtual void OnClosed() override;`
- L160 _private member_ `UE::Editor::DataStorage::ICoreProvider* DataStorage = nullptr;`
- L161 _private member_ `UE::Editor::DataStorage::RowHandle TargetRowHandle = UE::Editor::DataStorage::InvalidRowHandle;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/UI/MeshPartitionHierarchyWidget.h` (Private)


#### struct `UE::MeshPartition::FHierarchyWidget`  
`struct FHierarchyWidget : public FSimpleWidgetConstructor`  
_L28-44_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FSimpleWidgetConstructor`
- L33 _public prototype_ `FHierarchyWidget();`
- L34 _public prototype_ `~FHierarchyWidget() override = default;`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UE::MeshPartition::SHierarchyWidget`  
`class SHierarchyWidget : public SCompoundWidget`  
_L48-75_
- inherits: `SCompoundWidget`
- desc: Widget responsible for managing the visibility for a single item
- L50 _private typedef_ `using RowHandle = Editor::DataStorage::RowHandle;`
- L53 _public function_ `SLATE_BEGIN_ARGS(MeshPartition::SHierarchyWidget)`
- L54 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow, const RowHandle& InWidgetRow);`
- L59 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L63 _protected member_ `RowHandle TargetRow;`
- L64 _protected member_ `RowHandle WidgetRow;`
- L66 _protected member_ `TArray<TSharedPtr<FText>> ChildrenLabels;`
- L67 _protected member_ `TSharedPtr<SListView<TSharedPtr<FText>>> ChildrenListView;`
- L69 _protected prototype_ `TSharedRef<ITableRow> GenerateItemRow(TSharedPtr<FText> Entry, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L72 _private prototype_ `static Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L73 _private prototype_ `static Editor::DataStorage::ICoreProvider* GetDataStorageUI();`
- L74 _private prototype_ `static Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHPARTITIONEDITORUI_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/UI/MeshPartitionLayerBuildWidget.h` (Private)


#### struct `UE::MeshPartition::FMegaMeshLayerBuildWidgetHeaderConstructor`  
`struct FMegaMeshLayerBuildWidgetHeaderConstructor : public FSimpleWidgetConstructor`  
_L24-40_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L29 _public prototype_ `FMegaMeshLayerBuildWidgetHeaderConstructor();`
- L30 _public prototype_ `~FMegaMeshLayerBuildWidgetHeaderConstructor() override = default;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FMegaMeshLayerBuildWidget`  
`struct FMegaMeshLayerBuildWidget : public FSimpleWidgetConstructor`  
_L44-60_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L49 _public prototype_ `FMegaMeshLayerBuildWidget();`
- L50 _public prototype_ `~FMegaMeshLayerBuildWidget() override = default;`
- L52 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UE::MeshPartition::SMegaMeshLayerBuildWidget`  
`class SMegaMeshLayerBuildWidget : public SImage`  
_L64-144_
- inherits: `SImage`
- desc: Widget responsible for managing the visibility for a single item
- L66 _private typedef_ `using RowHandle = Editor::DataStorage::RowHandle;`
- L83 _public function_ `SLATE_BEGIN_ARGS(SMegaMeshLayerBuildWidget)`
- L84 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow, const RowHandle& InWidgetRow);`
- L92 _protected function_ `virtual bool IsEnabled() const` — Returns whether the widget is enabled or not
- L95 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;` — Get the brush for this widget
- L97 _protected prototype_ `FReply HandleClick();`
- L99 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L102 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Called when the mouse button is pressed down on this widget
- L105 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Process a mouse up message
- L108 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;` — Called when this widget had captured the mouse, but that capture has been revoked for some reason.
- L110 _protected prototype_ `virtual FSlateColor GetForegroundColor() const;`
- L113 _protected prototype_ `void SetIsVisible(const bool bVisible);` — Set the item this widget is responsible for to be hidden or shown
- L115 _protected member_ `RowHandle TargetRow;`
- L116 _protected member_ `RowHandle WidgetRow;`
- L119 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;` — Scoped undo transaction
- L122 _protected member_ `const FSlateBrush* AutoVisibleHoveredBrush;` — Visibility brushes for the various states
- L123 _protected member_ `const FSlateBrush* AutoVisibleNotHoveredBrush;`
- L124 _protected member_ `const FSlateBrush* VisibleHoveredBrush;`
- L125 _protected member_ `const FSlateBrush* VisibleNotHoveredBrush;`
- L126 _protected member_ `const FSlateBrush* NotVisibleHoveredBrush;`
- L127 _protected member_ `const FSlateBrush* NotVisibleNotHoveredBrush;`
- L129 _protected member_ `const FSlateBrush* DisabledBuildToBrush;`
- L130 _protected member_ `const FSlateBrush* TargetBuildToBrush;`
- L131 _protected member_ `const FSlateBrush* LayerBuildToBrush;`
- L132 _protected member_ `const FSlateBrush* LayerAutoBuildToBrush;`
- L133 _protected member_ `const FSlateBrush* ModifierBuildToBrush;`
- L134 _protected member_ `const FSlateBrush* ModifierAutoBuildToBrush;`
- L137 _private prototype_ `BuildCondition GetBuildConditionForRow() const;`
- L139 _private prototype_ `FSceneOutlinerTreeItemPtr GetTreeItem(RowHandle InRow) const;`
- L141 _private prototype_ `static Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L142 _private prototype_ `static Editor::DataStorage::ICoreProvider* GetDataStorageUI();`
- L143 _private prototype_ `static Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`

#### enum `UE::MeshPartition::SMegaMeshLayerBuildWidget::BuildCondition`  
`enum BuildCondition`  
_L68-80_
- L70 _public enumerator_ `NotBuilt = 0`
- L71 _public enumerator_ `TargetedForBuild = 1`
- L72 _public enumerator_ `AutoBuilt = 2`
- L73 _public enumerator_ `Modifier = 4`
- L74 _public enumerator_ `Layer = 8`
- L76 _public enumerator_ `ModifierTargetedForBuild = 5`
- L77 _public enumerator_ `ModifierAutoBuilt = 6`
- L78 _public enumerator_ `LayerTargetedForBuild = 9`
- L79 _public enumerator_ `LayerAutoBuilt = 10`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/UI/MeshPartitionLayerNameWidget.h` (Private)


#### struct `UE::MeshPartition::FNameWidgetHeaderConstructor`  
`struct FNameWidgetHeaderConstructor : public FSimpleWidgetConstructor`  
_L26-47_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L31 _public prototype_ `FNameWidgetHeaderConstructor();`
- L32 _public prototype_ `~FNameWidgetHeaderConstructor() override = default;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`
- L41 _public prototype_ `virtual TArray<TSharedPtr<const Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FMeshPartitionTypeInfoHeaderConstructor`  
`struct FMeshPartitionTypeInfoHeaderConstructor : public FSimpleWidgetConstructor`  
_L52-71_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Header constructor for the Type column in the Mesh Partition outliner. Explicitly returns no sorter, so it won't interfere with the primary sort column.
- L57 _public prototype_ `FMeshPartitionTypeInfoHeaderConstructor();`
- L58 _public prototype_ `~FMeshPartitionTypeInfoHeaderConstructor() override = default;`
- L60 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`
- L67 _public prototype_ `virtual TArray<TSharedPtr<const Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FMeshPartitionTypeInfoCellConstructor`  
`struct FMeshPartitionTypeInfoCellConstructor : public FTypeInfoWidgetConstructor`  
_L76-88_
- reflection: `USTRUCT()`
- inherits: `FTypeInfoWidgetConstructor`
- desc: Cell constructor for the Type column in the Mesh Partition outliner. Inherits display behavior from FTypeInfoWidgetConstructor but returns no sorter.
- L81 _public prototype_ `FMeshPartitionTypeInfoCellConstructor();`
- L82 _public prototype_ `~FMeshPartitionTypeInfoCellConstructor() override = default;`
- L84 _public prototype_ `virtual TArray<TSharedPtr<const Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UE::MeshPartition::FMegaMeshNameWidgetSorter`  
`class FMegaMeshNameWidgetSorter : public Editor::DataStorage::FColumnSorterInterface`  
_L90-96_
- inherits: `Editor::DataStorage::FColumnSorterInterface`
- L92 _private prototype_ `virtual ESortType GetSortType() const override;`
- L93 _private prototype_ `virtual FText GetShortName() const override;`
- L94 _private prototype_ `virtual int32 Compare(const Editor::DataStorage::ICoreProvider& Storage, Editor::DataStorage::RowHandle Left, Editor::DataStorage::RowHandle Right) const override;`
- L95 _private prototype_ `virtual Editor::DataStorage::FPrefixInfo CalculatePrefix(const Editor::DataStorage::ICoreProvider& Storage, Editor::DataStorage::RowHandle Row, uint32 ByteIndex) const override;`

#### struct `UE::MeshPartition::FMegaMeshNameWidgetConstructorDelegator`  
`struct FMegaMeshNameWidgetConstructorDelegator : public FSimpleWidgetConstructor`  
_L100-116_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L105 _public prototype_ `FMegaMeshNameWidgetConstructorDelegator();`
- L106 _public prototype_ `~FMegaMeshNameWidgetConstructorDelegator() override = default;`
- L108 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FMegaMeshLayerNameWidgetConstructor`  
`struct FMegaMeshLayerNameWidgetConstructor : public FSimpleWidgetConstructor`  
_L119-135_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L124 _public prototype_ `FMegaMeshLayerNameWidgetConstructor();`
- L125 _public prototype_ `~FMegaMeshLayerNameWidgetConstructor() override = default;`
- L127 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FMegaMeshModifierNameWidgetConstructor`  
`struct FMegaMeshModifierNameWidgetConstructor : public FSimpleWidgetConstructor`  
_L138-154_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L143 _public prototype_ `FMegaMeshModifierNameWidgetConstructor();`
- L144 _public prototype_ `~FMegaMeshModifierNameWidgetConstructor() override = default;`
- L146 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( Editor::DataStorage::ICoreProvider* DataStorage, Editor::DataStorage::IUiProvider* DataStorageUi, Editor::DataStorage::RowHandle TargetRow, Editor::DataStorage::RowHandle WidgetRow, const Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UE::MeshPartition::SMegaMeshLayerNameWidget`  
`class SMegaMeshLayerNameWidget : public SCompoundWidget`  
_L158-186_
- inherits: `SCompoundWidget`
- desc: Widget responsible for managing the visibility for a single item
- L160 _private typedef_ `using RowHandle = Editor::DataStorage::RowHandle;`
- L163 _public function_ `SLATE_BEGIN_ARGS(SMegaMeshLayerNameWidget)`
- L164 _public prototype_ `SLATE_ATTRIBUTE(FText, Label);`
- L165 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow, const RowHandle& InWidgetRow);`
- L172 _protected prototype_ `EVisibility GetIconVisibility() const;`
- L173 _protected prototype_ `const FSlateBrush* GetBrush() const;`
- L174 _protected prototype_ `FText GetLabel() const;`
- L176 _protected member_ `TAttribute<FText> Label;`
- L178 _protected member_ `RowHandle TargetRow;`
- L179 _protected member_ `RowHandle WidgetRow;`
- L183 _private prototype_ `static Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L184 _private prototype_ `static Editor::DataStorage::IUiProvider* GetDataStorageUI();`
- L185 _private prototype_ `static Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/UI/MeshPartitionLayerVisibilityWidget.h` (Private)


#### struct `FMegaMeshVisibilityWidgetHeaderConstructor`  
`struct FMegaMeshVisibilityWidgetHeaderConstructor : public FSimpleWidgetConstructor`  
_L19-35_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L24 _public prototype_ `FMegaMeshVisibilityWidgetHeaderConstructor();`
- L25 _public prototype_ `~FMegaMeshVisibilityWidgetHeaderConstructor() override = default;`
- L27 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FMegaMeshVisibilityFlagWidget`  
`struct FMegaMeshVisibilityFlagWidget : public FSimpleWidgetConstructor`  
_L38-54_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L43 _public prototype_ `FMegaMeshVisibilityFlagWidget();`
- L44 _public prototype_ `~FMegaMeshVisibilityFlagWidget() override = default;`
- L46 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `SMegaMeshVisibilityWidget`  
`class SMegaMeshVisibilityWidget : public SImage`  
_L58-115_
- inherits: `SImage`
- desc: Widget responsible for managing the visibility for a single item
- L60 _private typedef_ `using RowHandle = UE::Editor::DataStorage::RowHandle;`
- L63 _public function_ `SLATE_BEGIN_ARGS(SMegaMeshVisibilityWidget)`
- L64 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow, const RowHandle& InWidgetRow);`
- L72 _protected function_ `virtual bool IsEnabled() const` — Returns whether the widget is enabled or not
- L75 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;` — Get the brush for this widget
- L77 _protected prototype_ `FReply HandleClick();`
- L79 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L82 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Called when the mouse button is pressed down on this widget
- L85 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Process a mouse up message
- L88 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;` — Called when this widget had captured the mouse, but that capture has been revoked for some reason.
- L90 _protected prototype_ `virtual FSlateColor GetForegroundColor() const;`
- L93 _protected prototype_ `bool IsVisible() const;` — Check if the TargetRow Object is Visible
- L96 _protected prototype_ `void SetIsVisible(const bool bVisible);` — Set the item this widget is responsible for to be hidden or shown
- L98 _protected member_ `RowHandle TargetRow;`
- L99 _protected member_ `RowHandle WidgetRow;`
- L102 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;` — Scoped undo transaction
- L105 _protected member_ `const FSlateBrush* VisibleHoveredBrush;` — Visibility brushes for the various states
- L106 _protected member_ `const FSlateBrush* VisibleNotHoveredBrush;`
- L107 _protected member_ `const FSlateBrush* NotVisibleHoveredBrush;`
- L108 _protected member_ `const FSlateBrush* NotVisibleNotHoveredBrush;`
- L112 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L113 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorageUI();`
- L114 _private prototype_ `static UE::Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/UI/MeshPartitionSettingsWidget.h` (Private)


#### class `UFilterSettings`  
`class UFilterSettings : public UObject`  
_L37-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L43 _public function_ `FFilterSettingsModifiedSignature& GetOnModified()`
- L49 _public member_ `TSoftObjectPtr<AActor> BoundsFilterActor;` — `UPROPERTY(EditAnywhere, Category = "FilterData")`
- L58 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);` — Posts a message to the OnModified delegate with the modified FProperty @warning Please consider listening to OnModified instead of overriding this function @warning this function is currently only called in Editor (not at runtime)
- L63 _protected member_ `FFilterSettingsModifiedSignature OnModified;`

#### class `UE::MeshPartition::SMegaMeshSettingsWidget`  
`class SMegaMeshSettingsWidget : public SCompoundWidget, public FGCObject`  
_L79-142_
- inherits: `SCompoundWidget,FGCObject`
- desc: Widget for displaying a single group tag.
- L84 _public function_ `SLATE_BEGIN_ARGS(SMegaMeshSettingsWidget)`
- L87 _public prototype_ `SLATE_END_ARGS();`
- L89 _public prototype_ `SMegaMeshSettingsWidget();`
- L90 _public prototype_ `~SMegaMeshSettingsWidget();`
- L91 _public prototype_ `void Construct(const FArguments& InArgs);`
- L92 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L93 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L94 _public function_ `virtual FString GetReferencerName() const override`
- L105 _private member_ `TSharedPtr<IDetailsView> FilterDetailsView;`
- L106 _private member_ `TObjectPtr<UFilterSettings> FilterSettings;`
- L107 _private member_ `TWeakObjectPtr<AActor> PreviousBoundsFilterActor;`
- L109 _private member_ `TArray<TSharedPtr<FMegaMeshEntry>> MegaMeshList;`
- L110 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FMegaMeshEntry>>> MegaMeshSelector;`
- L111 _private member_ `TSharedPtr<FMegaMeshEntry> ActiveMegaMesh;`
- L112 _private member_ `TSharedPtr<STextBlock> DefinitionPath;`
- L113 _private member_ `TSharedPtr<SSceneOutliner> Outliner;`
- L114 _private member_ `TSharedPtr<UE::Editor::DataStorage::STedsCompositeHierarchyViewer> HierarchyViewer;`
- L117 _private prototype_ `TSharedRef<SSceneOutliner> CreateOutliner(const FSceneOutlinerInitializationOptions& InInitOptions, const Editor::Outliner::FTedsOutlinerParams& InInitTedsOptions) const;` — Refresh the rows in the current view by syncing the the items source
- L118 _private prototype_ `TSharedRef<SSceneOutliner> CreateOutlinerWidget();`
- L119 _private prototype_ `TSharedRef<UE::Editor::DataStorage::STedsCompositeHierarchyViewer> CreateHierarchyWidget();`
- L120 _private prototype_ `void OnComboBoxSelectionChanged(TSharedPtr<FMegaMeshEntry> InNewSelection, ESelectInfo::Type SelectInfo);`
- L121 _private prototype_ `TSharedRef<SWidget> GenerateMegaMeshEntry(TSharedPtr<FMegaMeshEntry> InItem);`
- L122 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L123 _private prototype_ `void OnMegaMeshSelectorOpening();`
- L124 _private prototype_ `FText GetActiveMegaMeshLabel() const;`
- L125 _private prototype_ `FText GetActiveDefinitionLabel() const;`
- L126 _private prototype_ `void OpenDefinitionInContentBrowser();`
- L127 _private prototype_ `bool CanOpenDefinitionInContentBrowser() const;`
- L128 _private prototype_ `FReply OnMegaMeshSelectClicked();`
- L129 _private prototype_ `bool IsActiveMegaMesh() const;`
- L130 _private prototype_ `void RebuildMegaMeshSelectionList();`
- L131 _private prototype_ `void OnOutlinerSelectionChanged(ESelectInfo::Type SelectInfo);`
- L132 _private prototype_ `void UpdateDetailsViewFromOutliner();`
- L133 _private prototype_ `void UpdateLevelSelectionFromOutliner();`
- L135 _private prototype_ `void OnFilterSettingsModified(UObject*, FProperty*);`
- L136 _private prototype_ `void OnLevelSelectionChanged(UObject* InObject);`
- L138 _private prototype_ `Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L139 _private prototype_ `Editor::DataStorage::IUiProvider* GetDataStorageUI();`
- L140 _private prototype_ `Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`

#### struct `UE::MeshPartition::SMegaMeshSettingsWidget::FMegaMeshEntry`  
`struct FMegaMeshEntry`  
_L98-103_
- L99 _public member_ `TWeakObjectPtr<AMeshPartition> MegaMesh;`
- L100 _public member_ `TWeakObjectPtr<UMeshPartitionDefinition> Definition;`
- L101 _public member_ `FString MegaMeshLabel;`
- L102 _public member_ `Editor::DataStorage::RowHandle MegaMeshRow;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHPARTITIONEDITORUI_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Editor` (scope `UE`)
- L28 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FFilterSettingsModifiedSignature, UObject*, FProperty*);`
- L33 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FFilterSettingsModifiedSignature, UObject*, FProperty*);`
- L67 _namespace_ `namespace UE`
- L67 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Private/UI/ParentActorWidget.h` (Private)


#### struct `UE::MeshPartition::FParentActorWidgetHeaderConstructor`  
`struct FParentActorWidgetHeaderConstructor : public FSimpleWidgetConstructor`  
_L22-38_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L27 _public prototype_ `FParentActorWidgetHeaderConstructor();`
- L28 _public prototype_ `~FParentActorWidgetHeaderConstructor() override = default;`
- L30 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `UE::MeshPartition::FParentActorWidgetConstructor`  
`struct FParentActorWidgetConstructor : public FSimpleWidgetConstructor`  
_L41-57_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L46 _public prototype_ `FParentActorWidgetConstructor();`
- L47 _public prototype_ `~FParentActorWidgetConstructor() override = default;`
- L49 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UE::MeshPartition::SParentActorWidget`  
`class SParentActorWidget : public SCompoundWidget`  
_L61-85_
- inherits: `SCompoundWidget`
- desc: Widget responsible for displaying the owning actor of a modifier
- L63 _private typedef_ `using RowHandle = UE::Editor::DataStorage::RowHandle;`
- L66 _public function_ `SLATE_BEGIN_ARGS(SParentActorWidget)`
- L67 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow, const RowHandle& InWidgetRow);`
- L74 _protected member_ `RowHandle TargetRow;`
- L75 _protected member_ `RowHandle WidgetRow;`
- L80 _private prototype_ `FText GetParentActorLabel() const;`
- L82 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L83 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorageUI();`
- L84 _private prototype_ `static UE::Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Public/Columns/LayerOutlinerColumns.h` (Public)


#### struct `UE::MeshPartition::FMegaMeshRowParentColumn`  
`struct FMegaMeshRowParentColumn final : public FEditorDataStorageColumn`  
_L17-25_
- reflection: `USTRUCT(meta = (DisplayName = "Parent"))`
- inherits: `FEditorDataStorageColumn`
- L21 _public member_ `UE::Editor::DataStorage::RowHandle Parent;`
- L23 _public member_ `TArray<UE::Editor::DataStorage::RowHandle> Children;`
- L24 _public member_ `TMap<UE::Editor::DataStorage::RowHandle, int32> ChildrenSet;`

#### struct `UE::MeshPartition::FUnresolvedMegaMeshLayer`  
`struct FUnresolvedMegaMeshLayer : public FEditorDataStorageColumn`  
_L28-34_
- reflection: `USTRUCT(meta = (DisplayName = "Unresolved Modifier Layer"))`
- inherits: `FEditorDataStorageColumn`
- L32 _public member_ `FString LayerName;`
- L33 _public member_ `FName Layer;`

#### struct `UE::MeshPartition::FMegaMeshBoundsFilterSourceTag`  
`struct FMegaMeshBoundsFilterSourceTag final : public FEditorDataStorageTag`  
_L37-40_
- reflection: `USTRUCT(meta = (DisplayName = "Is MeshPartition Bounds Filter Source"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FParentActorRefColumn`  
`struct FParentActorRefColumn : public FEditorDataStorageColumn`  
_L43-48_
- reflection: `USTRUCT(meta = (DisplayName = "Parent Actor Reference"))`
- inherits: `FEditorDataStorageColumn`
- L47 _public member_ `UE::Editor::DataStorage::RowHandle ParentActor;`

#### struct `UE::MeshPartition::FIsMegaMeshObjectTag`  
`struct FIsMegaMeshObjectTag final : public FEditorDataStorageTag`  
_L51-54_
- reflection: `USTRUCT(meta = (DisplayName = "Is this Object an AMeshPartition"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FIsMegaMeshModifierTag`  
`struct FIsMegaMeshModifierTag final : public FEditorDataStorageTag`  
_L57-60_
- reflection: `USTRUCT(meta = (DisplayName = "Is this Object a Mesh Partition Modifier"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshLayerUpdatedTag`  
`struct FMegaMeshLayerUpdatedTag final : public FEditorDataStorageTag`  
_L63-66_
- reflection: `USTRUCT(meta = (DisplayName = "Layer tags need updating"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshAffectsFilterBounds`  
`struct FMegaMeshAffectsFilterBounds final : public FEditorDataStorageTag`  
_L69-72_
- reflection: `USTRUCT(meta = (DisplayName = "Modifier Affects a Selected Base Section"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FIsMegaMeshModifierAssignedTag`  
`struct FIsMegaMeshModifierAssignedTag final : public FEditorDataStorageTag`  
_L75-78_
- reflection: `USTRUCT(meta = (DisplayName = "Is this Mesh Partition Modifier assigned to a Mesh Partition?"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshNotHiddenInOutlinerTag`  
`struct FMegaMeshNotHiddenInOutlinerTag final : public FEditorDataStorageTag`  
_L81-84_
- reflection: `USTRUCT(meta = (DisplayName = "Not Hidden in Mesh Partition Outliner"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshTimingStatistics`  
`struct FMegaMeshTimingStatistics : public FEditorDataStorageColumn`  
_L87-93_
- reflection: `USTRUCT(meta = (DisplayName = "Mesh Partition Timing Statistics"))`
- inherits: `FEditorDataStorageColumn`
- L91 _public member_ `double TotalTimeMean;`
- L92 _public member_ `double TotalTimeStandardDeviation;`

#### struct `UE::MeshPartition::FMegaMeshModifierTiming`  
`struct FMegaMeshModifierTiming : public FEditorDataStorageColumn`  
_L96-104_
- reflection: `USTRUCT(meta = (DisplayName = "Modifier Timing"))`
- inherits: `FEditorDataStorageColumn`
- L100 _public member_ `int InstanceCount;`
- L101 _public member_ `double TotalTime;`
- L102 _public member_ `double MinTime;`
- L103 _public member_ `double MaxTime;`

#### struct `UE::MeshPartition::FIsMegaMeshDefinitionObjectTag`  
`struct FIsMegaMeshDefinitionObjectTag final : public FEditorDataStorageTag`  
_L107-110_
- reflection: `USTRUCT(meta = (DisplayName = "Is this Object an UMeshPartitionDefinition"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshActiveLayerTag`  
`struct FMegaMeshActiveLayerTag final : public FEditorDataStorageTag`  
_L113-116_
- reflection: `USTRUCT(meta = (DisplayName = "Is Active Layer"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FIsMegaMeshDefinitionLayerTag`  
`struct FIsMegaMeshDefinitionLayerTag final : public FEditorDataStorageTag`  
_L119-122_
- reflection: `USTRUCT(meta = (DisplayName = "Is this a UMeshPartitionDefinition Layer"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshUpdatedTag`  
`struct FMegaMeshUpdatedTag final : public FEditorDataStorageTag`  
_L125-128_
- reflection: `USTRUCT(meta = (DisplayName = "Was this row updated since the last frame?"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshBuildToHereTag`  
`struct FMegaMeshBuildToHereTag final : public FEditorDataStorageTag`  
_L131-134_
- reflection: `USTRUCT(meta = (DisplayName = "Mark for build to here"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshPriorityColumn`  
`struct FMegaMeshPriorityColumn final : public FEditorDataStorageColumn`  
_L137-143_
- reflection: `USTRUCT(meta = (DisplayName = "Priority"))`
- inherits: `FEditorDataStorageColumn`
- L142 _public member_ `uint32 Priority = 0;` — `UPROPERTY()`

#### struct `UE::MeshPartition::FMegaMeshModifierSortColumn`  
`struct FMegaMeshModifierSortColumn final : public FEditorDataStorageColumn`  
_L146-152_
- reflection: `USTRUCT(meta = (DisplayName = "Sort Key"))`
- inherits: `FEditorDataStorageColumn`
- L151 _public member_ `uint32 SortKey = 0;` — `UPROPERTY()`

#### struct `UE::MeshPartition::FMegaMeshReferenceColumn`  
`struct FMegaMeshReferenceColumn final : public FEditorDataStorageColumn`  
_L155-161_
- reflection: `USTRUCT(meta = (DisplayName = "Mesh Partition Reference"))`
- inherits: `FEditorDataStorageColumn`
- L160 _public member_ `TWeakObjectPtr<AMeshPartition> Mesh = nullptr;` — `UPROPERTY()`

#### struct `UE::MeshPartition::FAutoMegaMeshBuildVisibilityTag`  
`struct FAutoMegaMeshBuildVisibilityTag final : public FEditorDataStorageTag`  
_L164-167_
- reflection: `USTRUCT(meta = (DisplayName = "Auto Build Visibility"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshBuildToStatus`  
`struct FMegaMeshBuildToStatus final : public FEditorDataStorageColumn`  
_L170-178_
- reflection: `USTRUCT(meta = (DisplayName = "Build Visibility Status"))`
- inherits: `FEditorDataStorageColumn`
- L175 _public member_ `uint32 LayerBuildToIndex = 0;` — `UPROPERTY()`
- L177 _public member_ `UE::Editor::DataStorage::RowHandle ModiferToBuildTo;`

#### struct `UE::MeshPartition::FMegaMeshBuildUpToThisLayerColumn`  
`struct FMegaMeshBuildUpToThisLayerColumn final : public FEditorDataStorageColumn`  
_L181-187_
- reflection: `USTRUCT(meta = (DisplayName = "Build Up To This Layer"))`
- inherits: `FEditorDataStorageColumn`
- L186 _public member_ `bool Enabled = true;` — `UPROPERTY()`

#### struct `UE::MeshPartition::FMegaMeshDrawBoundsColumn`  
`struct FMegaMeshDrawBoundsColumn final : public FEditorDataStorageColumn`  
_L190-196_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Bounds"))`
- inherits: `FEditorDataStorageColumn`
- L195 _public member_ `bool bEnabled = false;` — `UPROPERTY()`

#### struct `UE::MeshPartition::FMegaMeshVisualizationsActiveTag`  
`struct FMegaMeshVisualizationsActiveTag final : public FEditorDataStorageTag`  
_L200-203_
- reflection: `USTRUCT(meta = (DisplayName = "Active Mesh Partition for Visualizing"))`
- inherits: `FEditorDataStorageTag`

#### struct `UE::MeshPartition::FMegaMeshLayerNameColumn`  
`struct FMegaMeshLayerNameColumn final : public FEditorDataStorageColumn`  
_L206-212_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- L211 _public member_ `FName Name;` — `UPROPERTY()`

#### struct `UE::MeshPartition::FIsMegaMeshActiveInOutlinerTag`  
`struct FIsMegaMeshActiveInOutlinerTag final : public FEditorDataStorageTag`  
_L215-218_
- reflection: `USTRUCT(meta = (DisplayName = "This row is visible in the Mesh Partition outliner"))`
- inherits: `FEditorDataStorageTag`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Public/MeshPartitionEditorUIModule.h` (Public)


#### class `UE::MeshPartition::FMegaMeshEditorUIModule`  
`class FMegaMeshEditorUIModule : public IModuleInterface`  
_L21-51_
- inherits: `IModuleInterface`
- L24 _public prototype_ `void RegisterTabSpawners(const TSharedPtr<FWorkspaceItem>& WorkspaceGroup);`
- L25 _public prototype_ `void UnregisterTabSpawners();`
- L28 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _private prototype_ `void OnPostEngineInit();`
- L33 _private member_ `TArray<FName> VisualizersToUnregisterOnShutdown;`
- L34 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;`
- L35 _private member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`
- L37 _private prototype_ `void RegisterPropertyEditorCategories();`
- L38 _private prototype_ `TSharedRef<SDockTab> MakeMegaMeshSettingsTab(const FSpawnTabArgs&);`
- L39 _private prototype_ `TSharedRef<SWidget> GetMegaMeshSettings(const TSharedRef<SDockTab>& InParentTab);`
- L41 _private member_ `bool bHasRegisteredTabSpawners = false;`
- L42 _private member_ `TWeakPtr<SMegaMeshSettingsWidget> MegaMeshSettingsPtr;`
- L44 _private member_ `TSharedPtr<FExtender> ScalabilityMenuExtender;`
- L45 _private prototype_ `void AddScalabilitySubMenu(FMenuBuilder& InMenuBuilder);`
- L46 _private prototype_ `void FillScalabilitySubmenu(FMenuBuilder& InMenuBuilder);`
- L48 _private prototype_ `TSharedRef<SWidget> CreateEnablePreviewSectionSimplificationWidget();`
- L49 _private prototype_ `TSharedRef<SWidget> CreatePreviewSectionSimplificationEdgeLengthWidget();`
- L50 _private prototype_ `TSharedRef<SWidget> CreatePreviewSectionSimplificationMinVertexNumberWidget();`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMeshEditorUI, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMeshEditorUI, Log, All);`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Public/MeshPartitionModifiersCustomizations.h` (Public)


#### class `UE::MeshPartition::FMegaMeshProjectSculptLayersModifierDetails`  
`class FMegaMeshProjectSculptLayersModifierDetails : public IDetailCustomization`  
_L19-32_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `FMegaMeshProjectSculptLayersModifierDetails();`
- L23 _public prototype_ `virtual ~FMegaMeshProjectSculptLayersModifierDetails();`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L26 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L29 _private member_ `TSharedRef<IMeshLayersController> Controller;`
- L30 _private member_ `FDelegateHandle ModifierUpdatesHandle;`
- L31 _private member_ `TWeakObjectPtr<MeshPartition::UProjectMeshLayersModifier> Modifier;`

#### class `UE::MeshPartition::FMegaMeshTexturePatchDetails`  
`class FMegaMeshTexturePatchDetails : public IDetailCustomization`  
_L34-52_
- inherits: `IDetailCustomization`
- L37 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L39 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L42 _private prototype_ `void ReparentHeightDisplacement(IDetailLayoutBuilder& DetailBuilder);`
- L44 _private prototype_ `void AddWeightChannelCopyButtons(IDetailLayoutBuilder& DetailBuilder);`
- L46 _private prototype_ `void AddTessellationCheckbox(IDetailLayoutBuilder& DetailBuilder);`
- L48 _private member_ `TSharedPtr<IPropertyHandle> TessellationModeProperty;`
- L49 _private member_ `TSharedPtr<SCheckBox> CheckBoxTessellation;`
- L50 _private member_ `TSharedPtr<SCheckBox> CheckBoxTessellationFast;`
- L51 _private member_ `bool bTessellationFast { false };`

#### class `UE::MeshPartition::FSplineSoftObjectPointerDetails`  
`class FSplineSoftObjectPointerDetails : public IDetailCustomization`  
_L54-68_
- inherits: `IDetailCustomization`
- L57 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L58 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L62 _private prototype_ `void AddComboBox(IDetailLayoutBuilder& DetailBuilder);`
- L64 _private member_ `TWeakObjectPtr<MeshPartition::USplineModifier> SplineModifier;`
- L65 _private member_ `TArray<TWeakObjectPtr<USplineComponent>> Splines;`
- L66 _private member_ `TArray<TSharedPtr<FString>> SplineNames;`
- L67 _private member_ `TSharedPtr<FString> SelectedName;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Public/MeshPartitionTedsFactory.h` (Public)


#### class `UE::MeshPartition::UMegaMeshTedsFactory`  
`class UMegaMeshTedsFactory : public UEditorDataStorageFactory`  
_L20-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorDataStorageFactory`
- L28 _public prototype_ `virtual void PreRegister(Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L29 _public prototype_ `virtual void PostRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L31 _public prototype_ `virtual void RegisterTables(Editor::DataStorage::ICoreProvider& DataStorage, Editor::DataStorage::ICompatibilityProvider& CompatibilityDataStorage) override;`
- L33 _public prototype_ `virtual void RegisterQueries(Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L34 _public prototype_ `virtual void RegisterHierarchies(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L36 _public prototype_ `virtual void RegisterWidgetConstructors(Editor::DataStorage::ICoreProvider& DataStorage, Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L38 _public prototype_ `virtual void RegisterWidgetPurposes(Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L40 _public prototype_ `virtual void PreShutdown(Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L44 _public member_ `Editor::DataStorage::QueryHandle MegaMeshQuery;`
- L45 _public member_ `Editor::DataStorage::QueryHandle DefinitionLayerQueryRO;`
- L46 _public member_ `Editor::DataStorage::QueryHandle ActiveLayerQuery;`
- L47 _public member_ `Editor::DataStorage::QueryHandle MegaMeshModifierQueryRW;`
- L48 _public member_ `Editor::DataStorage::FHierarchyHandle MegaMeshHierarchy;`
- L53 _private member_ `std::atomic<bool> bShouldUpdateModifierSortKeys = false;`
- L54 _private member_ `std::atomic<bool> bShouldResolveBoundsFiltering = false;`
- L56 _private prototype_ `void ResolveLayerRows();`
- L57 _private prototype_ `void GenerateModifierSortKeys();`
- L58 _private prototype_ `void ResolveBoundsFiltering();`
- L59 _private prototype_ `void CleanMegaMeshRows(uint32 MapFlags);`
- L61 _private prototype_ `void OnMegaMeshChanged(const FOnChangedEventInfo&);`
- L63 _private member_ `Editor::DataStorage::TableHandle MegaMeshTable;`
- L64 _private member_ `Editor::DataStorage::TableHandle MegaMeshDefinitionTable;`
- L65 _private member_ `Editor::DataStorage::TableHandle MegaMeshDefinitionLayerTable;`
- L66 _private member_ `Editor::DataStorage::TableHandle MegaMeshModifierTable;`
- L68 _private member_ `Editor::DataStorage::QueryHandle DefinitionLayerQueryRW;`
- L69 _private member_ `Editor::DataStorage::QueryHandle DefinitionQuery;`
- L70 _private member_ `Editor::DataStorage::QueryHandle MegaMeshQueryRW;`
- L71 _private member_ `Editor::DataStorage::QueryHandle UnresolvedRetrievalQuery;`
- L72 _private member_ `Editor::DataStorage::QueryHandle BoundsFilterObjectQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITIONEDITORUI_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartitionEditorUI/Public/SculptLayersModifierController.h` (Public)


#### class `UE::MeshPartition::FSculptLayersModifiersController`  
`class FSculptLayersModifiersController : public IMeshLayersController`  
_L9-33_
- inherits: `IMeshLayersController`
- L12 _public prototype_ `FSculptLayersModifiersController();`
- L16 _public function_ `MeshPartition::UProjectMeshLayersModifier* GetProperties() const` — get access to the Properties. Warning: do not make modifications to the asset directly, use the controller API
- L17 _public function_ `virtual void SetProperties(MeshPartition::UProjectMeshLayersModifier* InProperties) override`
- L23 _private member_ `TObjectPtr<MeshPartition::UProjectMeshLayersModifier> Properties = nullptr;`
- L27 _public prototype_ `virtual FName GetLayerName(const int32 InLayerIndex) const override;`
- L28 _public prototype_ `virtual void SetLayerName(const int32 InLayerIndex, const FName InName) const override;`
- L29 _public prototype_ `virtual double GetLayerWeight(const int32 InLayerIndex) const override;`
- L30 _public prototype_ `virtual void SetLayerWeight(const int32 InLayerIndex, const double InWeight, EPropertyChangeType::Type ChangeType) const override;`
- L31 _public prototype_ `virtual int32 GetNumMeshLayers() const override;`
- L32 _public prototype_ `virtual void RefreshLayersStackView() const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshPartition` (scope `UE`)
