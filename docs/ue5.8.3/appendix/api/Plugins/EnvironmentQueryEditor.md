# Plugins / EnvironmentQueryEditor

- module root: `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor`
- headers: 20; symbols: 325
- symbol kinds: class=20, delegate=1, function=18, member=78, namespace=6, prototype=184, struct=4, typedef=1, variable=13
- PrivateDependencyModuleNames: AIGraph, AIModule, AssetDefinition, Core, CoreUObject, Engine, GraphEditor, InputCore, KismetWidgets, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/AssetDefinition_EnvironmentQuery.h` (Private)


#### class `UAssetDefinition_EnvironmentQuery`  
`class UAssetDefinition_EnvironmentQuery : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _protected prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/DetailCustomizations/EnvDirectionCustomization.h` (Private)


#### class `FEnvDirectionCustomization`  
`class FEnvDirectionCustomization : public IPropertyTypeCustomization`  
_L11-31_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L17 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( );`
- L24 _protected member_ `TSharedPtr<IPropertyHandle> ModeProp;`
- L25 _protected member_ `bool bIsRotation;`
- L27 _protected prototype_ `FText GetShortDescription() const;`
- L28 _protected prototype_ `EVisibility GetTwoPointsVisibility() const;`
- L29 _protected prototype_ `EVisibility GetRotationVisibility() const;`
- L30 _protected prototype_ `void OnModeChanged();`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/DetailCustomizations/EnvQueryTestDetails.h` (Private)


#### class `FEnvQueryTestDetails`  
`class FEnvQueryTestDetails : public IDetailCustomization`  
_L16-122_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L37 _protected member_ `TSharedPtr<IPropertyHandle> FilterTypeHandle;`
- L38 _protected member_ `TSharedPtr<IPropertyHandle> ScoreEquationHandle;`
- L39 _protected member_ `TSharedPtr<IPropertyHandle> TestPurposeHandle;`
- L40 _protected member_ `TSharedPtr<IPropertyHandle> ClampMinTypeHandle;`
- L41 _protected member_ `TSharedPtr<IPropertyHandle> ClampMaxTypeHandle;`
- L42 _protected member_ `TSharedPtr<IPropertyHandle> ScoreClampMinHandle;`
- L43 _protected member_ `TSharedPtr<IPropertyHandle> FloatValueMinHandle;`
- L44 _protected member_ `TSharedPtr<IPropertyHandle> ScoreClampMaxHandle;`
- L45 _protected member_ `TSharedPtr<IPropertyHandle> FloatValueMaxHandle;`
- L46 _protected member_ `TSharedPtr<IPropertyHandle> MultipleContextFilterOpHandle;`
- L47 _protected member_ `TSharedPtr<IPropertyHandle> ScoreHandle;`
- L48 _protected member_ `TSharedPtr<IPropertyHandle> ScoreNormalizationTypeHandle;`
- L49 _protected member_ `TSharedPtr<IPropertyHandle> ScoreReferenceValueHandle;`
- L50 _protected member_ `TSharedPtr<IPropertyHandle> MultipleContextScoreOpHandle;`
- L52 _protected prototype_ `bool IsFiltering() const;`
- L53 _protected prototype_ `bool IsScoring() const;`
- L55 _protected prototype_ `bool UsesFilterMin() const;`
- L56 _protected prototype_ `bool UsesFilterMax() const;`
- L58 _protected prototype_ `FText GetCurrentFilterTestDesc() const;`
- L59 _protected prototype_ `FText GetScoreEquationInfo() const;`
- L61 _protected prototype_ `EVisibility GetScoreVisibility() const;`
- L62 _protected prototype_ `EVisibility GetClampingVisibility() const;`
- L64 _protected prototype_ `TSharedRef<SWidget> OnGetFilterTestContent();`
- L65 _protected prototype_ `void BuildFilterTestValues();`
- L67 _protected prototype_ `void BuildScoreEquationValues();`
- L68 _protected prototype_ `TSharedRef<SWidget> OnGetEquationValuesContent();`
- L69 _protected prototype_ `FText GetEquationValuesDesc() const;`
- L70 _protected prototype_ `void OnScoreEquationChange(int32 Index);`
- L72 _protected prototype_ `void OnFilterTestChange(int32 Index);`
- L73 _protected prototype_ `void OnClampMinTestChange(int32 Index);`
- L74 _protected prototype_ `void OnClampMaxTestChange(int32 Index);`
- L76 _protected prototype_ `TSharedRef<SWidget> OnGetClampMaxTypeContent();`
- L77 _protected prototype_ `FText GetClampMaxTypeDesc() const;`
- L79 _protected prototype_ `TSharedRef<SWidget> OnGetClampMinTypeContent();`
- L80 _protected prototype_ `FText GetClampMinTypeDesc() const;`
- L82 _protected prototype_ `bool IsMatchingBoolValue() const;`
- L85 _protected prototype_ `EVisibility GetFloatTestVisibility() const;` — Is this a float test at all?
- L88 _protected prototype_ `EVisibility GetFloatFilterVisibility() const;` — Is this a float test that is filtering?
- L91 _protected prototype_ `EVisibility GetFloatScoreVisibility() const;` — Is this a float test that is scoring?
- L93 _protected prototype_ `EVisibility GetTestPreviewVisibility() const;`
- L94 _protected prototype_ `EVisibility GetVisibilityOfFloatValueMin() const;`
- L95 _protected prototype_ `EVisibility GetVisibilityOfFloatValueMax() const;`
- L96 _protected prototype_ `EVisibility GetVisibilityOfValueMinForScoreClamping() const;`
- L97 _protected prototype_ `EVisibility GetVisibilityOfValueMaxForScoreClamping() const;`
- L98 _protected prototype_ `EVisibility GetVisibilityForFiltering() const;`
- L99 _protected prototype_ `EVisibility GetBoolValueVisibilityForScoring() const;`
- L100 _protected prototype_ `EVisibility GetBoolValueVisibility() const;`
- L101 _protected prototype_ `EVisibility GetVisibilityOfScoreClampMinimum() const;`
- L102 _protected prototype_ `EVisibility GetVisibilityOfScoreClampMaximum() const;`
- L104 _protected prototype_ `void BuildScoreClampingTypeValues(bool bBuildMinValues, TArray<FTextIntPair>& ClampTypeValues) const;`
- L106 _protected prototype_ `void UpdateTestFunctionPreview() const;`
- L107 _protected prototype_ `void FillEquationSamples(uint8 EquationType, bool bInversed, TArray<float>& Samples) const;`
- L108 _protected member_ `TSharedPtr<STestFunctionWidget> PreviewWidget;`
- L111 _protected member_ `TArray<FTextIntPair> FilterTestValues;`
- L113 _protected member_ `TArray<FTextIntPair> ClampMinTypeValues;`
- L114 _protected member_ `TArray<FTextIntPair> ClampMaxTypeValues;`
- L116 _protected member_ `TArray<FTextIntPair> ScoreEquationValues;`
- L118 _protected member_ `TWeakObjectPtr<UObject> MyTest;`
- L120 _protected function_ `FORCEINLINE bool AllowWritingToFiltersFromScore() const`
- L121 _protected member_ `TAttribute<bool> AllowWriting;`

#### struct `FEnvQueryTestDetails::FTextIntPair`  
`struct FTextIntPair`  
_L28-35_
- desc: cached name, value pairs of enums that may change available options based on other options.
- L30 _public member_ `FText Text;`
- L31 _public member_ `int32 Int;`
- L33 _public function_ `FTextIntPair()`
- L34 _public function_ `FTextIntPair(FText InText, int32 InInt) : Text(InText), Int(InInt)`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/DetailCustomizations/EnvTraceDataCustomization.h` (Private)


#### class `FEnvTraceDataCustomization`  
`class FEnvTraceDataCustomization : public IPropertyTypeCustomization`  
_L12-61_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L20 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L25 _protected prototype_ `void CacheTraceModes(TSharedRef<class IPropertyHandle> StructPropertyHandle);`
- L36 _protected member_ `TArray<FTextIntPair> TraceModes;`
- L37 _protected member_ `bool bCanShowProjection;`
- L38 _protected member_ `uint8 ActiveMode;`
- L40 _protected member_ `TSharedPtr<IPropertyHandle> PropTraceMode;`
- L41 _protected member_ `TSharedPtr<IPropertyHandle> PropTraceShape;`
- L42 _protected member_ `TSharedPtr<IPropertyHandle> PropTraceChannel;`
- L43 _protected member_ `TSharedPtr<IPropertyHandle> PropTraceChannelSerialized;`
- L44 _protected member_ `TSharedPtr<IPropertyHandle> PropTraceProfileName;`
- L46 _protected prototype_ `void OnTraceChannelChanged();`
- L47 _protected prototype_ `void OnTraceProfileChanged();`
- L48 _protected prototype_ `void OnTraceModeChanged(int32 Index);`
- L49 _protected prototype_ `TSharedRef<SWidget> OnGetTraceModeContent();`
- L50 _protected prototype_ `FText GetCurrentTraceModeDesc() const;`
- L51 _protected prototype_ `FText GetShortDescription() const;`
- L53 _protected prototype_ `EVisibility GetGeometryByChannelVisibility() const;`
- L54 _protected prototype_ `EVisibility GetGeometryByProfileVisibility() const;`
- L55 _protected prototype_ `EVisibility GetGeometryVisibility() const;`
- L56 _protected prototype_ `EVisibility GetNavigationVisibility() const;`
- L57 _protected prototype_ `EVisibility GetProjectionVisibility() const;`
- L58 _protected prototype_ `EVisibility GetExtentX() const;`
- L59 _protected prototype_ `EVisibility GetExtentY() const;`
- L60 _protected prototype_ `EVisibility GetExtentZ() const;`

#### struct `FEnvTraceDataCustomization::FTextIntPair`  
`struct FTextIntPair`  
_L28-35_
- desc: cached names of trace modes
- L30 _public member_ `FText Text;`
- L31 _public member_ `int32 Int;`
- L33 _public function_ `FTextIntPair()`
- L34 _public function_ `FTextIntPair(FText InText, int32 InInt) : Text(InText), Int(InInt)`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/EnvironmentQueryColors.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace EnvironmentQueryColors`
- L11 _namespace_ `namespace NodeBody` (scope `EnvironmentQueryColors`)
- L13 _variable_ `const FLinearColor Default(0.15f, 0.15f, 0.15f);` (scope `EnvironmentQueryColors::NodeBody`)
- L14 _variable_ `const FLinearColor Generator(0.1f, 0.1f, 0.1f);` (scope `EnvironmentQueryColors::NodeBody`)
- L15 _variable_ `const FLinearColor Test(0.0f, 0.07f, 0.4f);` (scope `EnvironmentQueryColors::NodeBody`)
- L16 _variable_ `const FLinearColor TestInactive(0.1f, 0.1f, 0.1f);` (scope `EnvironmentQueryColors::NodeBody`)
- L17 _variable_ `const FLinearColor Error(1.0f, 0.0f, 0.0f);` (scope `EnvironmentQueryColors::NodeBody`)
- L20 _namespace_ `namespace NodeBorder` (scope `EnvironmentQueryColors`)
- L22 _variable_ `const FLinearColor Default(0.08f, 0.08f, 0.08f);` (scope `EnvironmentQueryColors::NodeBorder`)
- L23 _variable_ `const FLinearColor Selected(1.00f, 0.08f, 0.08f);` (scope `EnvironmentQueryColors::NodeBorder`)
- L26 _namespace_ `namespace Pin` (scope `EnvironmentQueryColors`)
- L28 _variable_ `const FLinearColor Default(0.02f, 0.02f, 0.02f);` (scope `EnvironmentQueryColors::Pin`)
- L29 _variable_ `const FLinearColor Hover(1.0f, 0.7f, 0.0f);` (scope `EnvironmentQueryColors::Pin`)
- L32 _namespace_ `namespace Action` (scope `EnvironmentQueryColors`)
- L34 _variable_ `const FLinearColor DragMarker(1.0f, 1.0f, 0.2f);` (scope `EnvironmentQueryColors::Action`)
- L35 _variable_ `const FLinearColor Weight(0.0f, 1.0f, 1.0f);` (scope `EnvironmentQueryColors::Action`)
- L36 _variable_ `const FLinearColor WeightNamed(0.2f, 0.2f, 0.2f);` (scope `EnvironmentQueryColors::Action`)
- L37 _variable_ `const FLinearColor Profiler(0.1f, 0.1f, 0.1f, 1.0f);` (scope `EnvironmentQueryColors::Action`)

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/EnvironmentQueryEditor.h` (Private)


#### class `FEnvironmentQueryEditor`  
`class FEnvironmentQueryEditor : public IEnvironmentQueryEditor, public FAIGraphEditor`  
_L15-72_
- inherits: `IEnvironmentQueryEditor,FAIGraphEditor`
- L20 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L21 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L23 _public prototype_ `void InitEnvironmentQueryEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UEnvQuery* Script );`
- L26 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L27 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L28 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L29 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L32 _public prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L33 _public prototype_ `void OnStatsDataChange();`
- L37 _protected prototype_ `virtual void SaveAsset_Execute() override;` — Called when "Save" is clicked for this asset
- L38 _protected prototype_ `void ExtendToolbar();`
- L39 _protected prototype_ `void BindCommands();`
- L41 _protected prototype_ `void OnLoadStats();`
- L42 _protected prototype_ `void OnSaveStats();`
- L46 _private prototype_ `TSharedRef<class SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);` — Create widget for graph editing
- L49 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L52 _private prototype_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection) override;` — Called when the selection changes in the GraphEditor
- L55 _private prototype_ `TSharedRef<SDockTab> SpawnTab_UpdateGraph(const FSpawnTabArgs& Args);` — Spawns the tab with the update graph inside
- L56 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);`
- L57 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Profiler(const FSpawnTabArgs& Args);`
- L62 _private member_ `UEnvQuery* Query;` — Query being edited
- L65 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View
- L66 _private member_ `TSharedPtr<SEnvQueryProfiler> ProfilerView;`
- L69 _private member_ `static const FName EQSUpdateGraphTabId;` — Graph editor tab
- L70 _private member_ `static const FName EQSPropertiesTabId;`
- L71 _private member_ `static const FName EQSProfilerTabId;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/SEnvQueryLoadGraph.h` (Private)


#### class `SEnvQueryLoadGraph`  
`class SEnvQueryLoadGraph : public SLeafWidget`  
_L12-26_
- inherits: `SLeafWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SEnvQueryLoadGraph)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L21 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L24 _public member_ `FEQSDebugger::FStatsInfo Stats;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/SEnvQueryProfiler.h` (Private)


#### class `SEnvQueryProfiler`  
`class SEnvQueryProfiler : public SCompoundWidget`  
_L10-58_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SEnvQueryProfiler)`
- L28 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `void BuildStatData();`
- L32 _public prototype_ `void ForceUpdate();`
- L34 _public prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FStatData, ESPMode::ThreadSafe> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L35 _public function_ `FText GetHeaderDesc() const`
- L36 _public function_ `FText GetGraphViewTitle() const`
- L37 _public prototype_ `EVisibility GetGraphViewVisibility() const;`
- L38 _public prototype_ `ECheckBoxState GetShowDetailsState() const;`
- L39 _public prototype_ `void OnShowDetailsChanged(ECheckBoxState NewState);`
- L40 _public prototype_ `void OnItemDoubleClicked(TSharedPtr<SEnvQueryProfiler::FStatData, ESPMode::ThreadSafe> Item);`
- L42 _public function_ `FName GetCurrentQueryKey() const`
- L46 _private member_ `TArray<TSharedPtr<FStatData, ESPMode::ThreadSafe> > StatData;`
- L47 _private member_ `TSharedPtr<SListView< TSharedPtr<FStatData, ESPMode::ThreadSafe> > > ListView;`
- L48 _private member_ `TSharedPtr<SEnvQueryLoadGraph> GraphView;`
- L50 _private member_ `FText CachedHeaderDesc;`
- L51 _private member_ `FText CachedGraphDesc;`
- L52 _private member_ `FName OwnerQueryName;`
- L53 _private member_ `FName MatchingQueryName;`
- L54 _private member_ `FSimpleDelegate OnDataChanged;`
- L56 _private member_ `float TimeToNextUpdate;`
- L57 _private member_ `uint32 bShowDetails : 1;`

#### struct `SEnvQueryProfiler::FStatData`  
`struct FStatData : public TSharedFromThis<FStatData, ESPMode::ThreadSafe>`  
_L18-26_
- inherits: `TSharedFromThis<FStatData,ESPMode::ThreadSafe>`
- L20 _public member_ `FName QueryName;`
- L21 _public member_ `double WorstTime;`
- L22 _public member_ `double AverageTime;`
- L23 _public member_ `float AverageLoad;`
- L24 _public member_ `int32 NumRuns;`
- L25 _public member_ `bool bIsHighlighted;`

#### class `SEnvQueryProfilerTableRow`  
`class SEnvQueryProfilerTableRow : public SMultiColumnTableRow<FEnvQueryProfilerStatDataPtr>`  
_L62-76_
- inherits: `SMultiColumnTableRow<FEnvQueryProfilerStatDataPtr>`
- L65 _public function_ `SLATE_BEGIN_ARGS(SEnvQueryProfilerTableRow)`
- L66 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const FEnvQueryProfilerStatDataPtr InStatInfo);`
- L69 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L70 _public prototype_ `const FSlateBrush* GetBorder() const;`
- L71 _public prototype_ `FReply OnBrowseClicked();`
- L75 _private member_ `FEnvQueryProfilerStatDataPtr StatInfo;`

#### Free symbols / members of external scopes

- L60 _typedef_ `typedef TSharedPtr<SEnvQueryProfiler::FStatData, ESPMode::ThreadSafe> FEnvQueryProfilerStatDataPtr;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/SGraphNode_EnvironmentQuery.h` (Private)


#### class `SGraphNode_EnvironmentQuery`  
`class SGraphNode_EnvironmentQuery : public SGraphNodeAI`  
_L10-46_
- inherits: `SGraphNodeAI`
- L13 _public function_ `SLATE_BEGIN_ARGS(SGraphNode_EnvironmentQuery)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEnvironmentQueryGraphNode* InNode);`
- L19 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L20 _public prototype_ `virtual void CreatePinWidgets() override;`
- L24 _public prototype_ `virtual void AddSubNode(TSharedPtr<SGraphNode> SubNodeWidget) override;` — adds decorator widget inside current node
- L26 _public prototype_ `EVisibility GetWeightMarkerVisibility() const;`
- L27 _public prototype_ `TOptional<float> GetWeightProgressBarPercent() const;`
- L28 _public prototype_ `FSlateColor GetWeightProgressBarColor() const;`
- L30 _public prototype_ `EVisibility GetTestToggleVisibility() const;`
- L31 _public prototype_ `ECheckBoxState IsTestToggleChecked() const;`
- L32 _public prototype_ `void OnTestToggleChanged(ECheckBoxState NewState);`
- L34 _public prototype_ `FSlateColor GetProfilerTestSlateColor() const;`
- L35 _public prototype_ `EVisibility GetProfilerTestVisibility() const;`
- L36 _public prototype_ `EVisibility GetProfilerOptionVisibility() const;`
- L37 _public prototype_ `FText GetProfilerDescAverage() const;`
- L38 _public prototype_ `FText GetProfilerDescWorst() const;`
- L39 _public prototype_ `FText GetProfilerDescOption() const;`
- L42 _protected member_ `TSharedPtr<SVerticalBox> TestBox;`
- L44 _protected prototype_ `FSlateColor GetBorderBackgroundColor() const;`
- L45 _protected prototype_ `FSlateColor GetBackgroundColor() const;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Private/STestFunctionWidget.h` (Private)


#### class `STestFunctionWidget`  
`class STestFunctionWidget : public SLeafWidget`  
_L15-33_
- inherits: `SLeafWidget`
- desc: Debug console widget, designed to be summoned on top of a viewport or window
- L19 _public function_ `SLATE_BEGIN_ARGS(STestFunctionWidget)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L26 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L28 _public member_ `TWeakObjectPtr<UEnvQueryTest> DrawTestOb;`
- L32 _private prototype_ `FVector2D GetWidgetPosition(float X, float Y, const FGeometry& Geom) const;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/ActorFactoryEnvironmentQuery.h` (Public)


#### class `UActorFactoryEnvironmentQuery`  
`class UActorFactoryEnvironmentQuery : public UActorFactory`  
_L12-24_
- reflection: `UCLASS(MinimalAPI, config=Editor, collapsecategories, hidecategories=Object)`
- inherits: `UActorFactory`
- L16 _private prototype_ `UActorFactoryEnvironmentQuery();`
- L20 _protected prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L21 _protected prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L22 _protected prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EdGraphSchema_EnvironmentQuery.h` (Public)


#### class `UEdGraphSchema_EnvironmentQuery`  
`class UEdGraphSchema_EnvironmentQuery : public UAIGraphSchema`  
_L14-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAIGraphSchema`
- L19 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L20 _private prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L21 _private prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L22 _private prototype_ `virtual const FPinConnectionResponse CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const override;`
- L26 _private prototype_ `virtual void GetSubNodeClasses(int32 SubNodeFlags, TArray<FGraphNodeClassData>& ClassData, UClass*& GraphNodeClass) const override;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EnvironmentQueryEditorModule.h` (Public)


#### class `FEnvironmentQueryEditorModule`  
`class FEnvironmentQueryEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L14-38_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `virtual TSharedRef<IEnvironmentQueryEditor> CreateEnvironmentQueryEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, class UEnvQuery* Query);` — Creates an instance of EQS editor.  Only virtual so that it can be called across the DLL boundary.
- L25 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars
- L26 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L29 _public member_ `static const FName EnvironmentQueryEditorAppIdentifier;` — EQS Editor app identifier string
- L31 _public function_ `TSharedPtr<FGraphNodeClassHelper> GetClassCache()`
- L34 _private member_ `TSharedPtr<FGraphNodeClassHelper> ClassCache;`
- L36 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L37 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEnvironmentQueryEditor, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEnvironmentQueryEditor, Log, All);`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EnvironmentQueryFactory.h` (Public)


#### class `UEnvironmentQueryFactory`  
`class UEnvironmentQueryFactory : public UFactory`  
_L9-17_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L14 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;` — UFactory interface
- L15 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EnvironmentQueryGraph.h` (Public)


#### class `UEnvironmentQueryGraph`  
`class UEnvironmentQueryGraph : public UAIGraph`  
_L13-44_
- reflection: `UCLASS()`
- inherits: `UAIGraph`
- L17 _private prototype_ `virtual void Initialize() override;`
- L18 _private prototype_ `virtual void OnLoaded() override;`
- L19 _private prototype_ `virtual void UpdateVersion() override;`
- L20 _private prototype_ `virtual void MarkVersion() override;`
- L21 _private prototype_ `virtual void UpdateAsset(int32 UpdateFlags = 0) override;`
- L23 _private prototype_ `void UpdateDeprecatedGeneratorClasses();`
- L24 _private prototype_ `void SpawnMissingNodes();`
- L25 _private prototype_ `void CalculateAllWeights();`
- L26 _private prototype_ `void CreateEnvQueryFromGraph(class UEnvironmentQueryGraphNode* RootEdNode);`
- L28 _private prototype_ `void ResetProfilerStats();`
- L30 _private prototype_ `void StoreProfilerStats(const FEQSDebugger::FStatsInfo& Stats);`
- L35 _protected prototype_ `void UpdateVersion_NestedNodes();`
- L36 _protected prototype_ `void UpdateVersion_FixupOuters();`
- L37 _protected prototype_ `void UpdateVersion_CollectClassData();`
- L39 _protected prototype_ `virtual void CollectAllNodeInstances(TSet<UObject*>& NodeInstances) override;`
- L40 _protected prototype_ `virtual void OnNodeInstanceRemoved(UObject* NodeInstance) override;`
- L41 _protected prototype_ `virtual void OnNodesPasted(const FString& ImportStr) override;`
- L43 _protected prototype_ `void SpawnMissingSubNodes(UEnvQueryOption* Option, TSet<UEnvQueryTest*> ExistingTests, UEnvironmentQueryGraphNode* OptionNode);`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EnvironmentQueryGraphNode.h` (Public)


#### struct `FEnvionmentQueryNodeStats`  
`struct FEnvionmentQueryNodeStats`  
_L12-19_
- L14 _public member_ `float MaxTime;`
- L15 _public member_ `float AvgTime;`
- L16 _public member_ `int32 MaxNumProcessedItems;`
- L18 _public function_ `FEnvionmentQueryNodeStats() : MaxTime(0.0f), AvgTime(0.0f), MaxNumProcessedItems(0)`

#### class `UEnvironmentQueryGraphNode`  
`class UEnvironmentQueryGraphNode : public UAIGraphNode`  
_L22-32_
- reflection: `UCLASS()`
- inherits: `UAIGraphNode`
- L26 _private prototype_ `virtual class UEnvironmentQueryGraph* GetEnvironmentQueryGraph();`
- L28 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _private prototype_ `virtual FText GetDescription() const override;`
- L31 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ENodeTitleType`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EnvironmentQueryGraphNode_Option.h` (Public)


#### class `UEnvironmentQueryGraphNode_Option`  
`class UEnvironmentQueryGraphNode_Option : public UEnvironmentQueryGraphNode`  
_L11-36_
- reflection: `UCLASS()`
- inherits: `UEnvironmentQueryGraphNode`
- L15 _private member_ `uint32 bStatShowOverlay : 1;`
- L16 _private member_ `TArray<FEnvionmentQueryNodeStats> StatsPerGenerator;`
- L17 _private member_ `float StatAvgPickRate;`
- L19 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L20 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L21 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _private prototype_ `virtual FText GetDescription() const override;`
- L24 _private prototype_ `virtual void PrepareForCopying() override;`
- L25 _private prototype_ `virtual void UpdateNodeClassData() override;`
- L27 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L28 _private prototype_ `void CreateAddTestSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;`
- L30 _private prototype_ `void CalculateWeights();`
- L31 _private prototype_ `void UpdateNodeData();`
- L35 _protected prototype_ `virtual void ResetNodeOwner() override;`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EnvironmentQueryGraphNode_Root.h` (Public)


#### class `UEnvironmentQueryGraphNode_Root`  
`class UEnvironmentQueryGraphNode_Root : public UEnvironmentQueryGraphNode`  
_L8-24_
- reflection: `UCLASS()`
- inherits: `UEnvironmentQueryGraphNode`
- L13 _private member_ `TArray<FString> DebugMessages;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L16 _private member_ `bool bHasDebugError;` — `UPROPERTY()`
- L18 _private prototype_ `void LogDebugMessage(const FString& Message);`
- L19 _private prototype_ `void LogDebugError(const FString& Message);`
- L21 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private function_ `virtual bool HasErrors() const override`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/EnvironmentQueryGraphNode_Test.h` (Public)


#### class `UEnvironmentQueryGraphNode_Test`  
`class UEnvironmentQueryGraphNode_Test : public UEnvironmentQueryGraphNode`  
_L9-33_
- reflection: `UCLASS()`
- inherits: `UEnvironmentQueryGraphNode`
- L15 _private member_ `float TestWeightPct;` — `UPROPERTY()` — weight percent for display
- L19 _private member_ `uint32 bHasNamedWeight : 1;` — `UPROPERTY()` — weight is passed as named param
- L23 _private member_ `uint32 bTestEnabled : 1;` — `UPROPERTY()` — toggles test
- L25 _private member_ `uint32 bStatShowOverlay : 1;`
- L26 _private member_ `FEnvionmentQueryNodeStats Stats;`
- L28 _private prototype_ `virtual void InitializeInstance() override;`
- L29 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L30 _private prototype_ `virtual FText GetDescription() const override;`
- L32 _private prototype_ `void SetDisplayedWeight(float Pct, bool bNamed);`

### `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/IEnvironmentQueryEditor.h` (Public)


#### class `IEnvironmentQueryEditor`  
`class IEnvironmentQueryEditor : public FAssetEditorToolkit`  
_L9-14_
- inherits: `FAssetEditorToolkit`
- desc: EnvQuery Editor public interface
