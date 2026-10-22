# Plugins / ChooserEditor

- module root: `Plugins/Chooser/Source/ChooserEditor`
- headers: 53; symbols: 736
- symbol kinds: class=50, delegate=8, enum=6, enumerator=12, externvar=1, function=81, macro=4, member=139, namespace=82, prototype=338, struct=8, typedef=7
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetTools, BlendStack, BlueprintGraph, Core, CoreUObject, DeveloperSettings, EditorStyle, EditorWidgets, Engine, GameplayInsights, GameplayTags, GameplayTagsEditor, GraphEditor, InputCore, KismetCompiler, Persona, PropertyEditor, RewindDebuggerInterface, Slate, SlateCore, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UnrealEd
- PublicDependencyModuleNames: Chooser

### `Plugins/Chooser/Source/ChooserEditor/Private/AssetDefinition_ChooserSignature.h` (Private)


#### class `UAssetDefinition_ChooserSignature`  
`class UAssetDefinition_ChooserSignature : public UAssetDefinitionDefault`  
_L11-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L20 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L31 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Chooser/Source/ChooserEditor/Private/AssetDefinition_ChooserTable.h` (Private)


#### class `UAssetDefinition_ChooserTable`  
`class UAssetDefinition_ChooserTable : public UAssetDefinitionDefault`  
_L11-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L20 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L31 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Chooser/Source/ChooserEditor/Private/BoolColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterBoolWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserAnalyzer.h` (Private)


#### class `FChooserAnalyzer`  
`class FChooserAnalyzer : public UE::Trace::IAnalyzer`  
_L10-29_
- inherits: `UE::Trace::IAnalyzer`
- L13 _public prototype_ `FChooserAnalyzer(TraceServices::IAnalysisSession& InSession, FChooserProvider& InProvider);`
- L15 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L16 _public function_ `virtual void OnAnalysisEnd() override`
- L17 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L27 _private member_ `TraceServices::IAnalysisSession& Session;`
- L28 _private member_ `FChooserProvider& Provider;`

#### enum `FChooserAnalyzer::(anonymous)`  
``  
_L21-25_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L22 _enumerator_ `RouteId_ChooserEvaluation` (scope `FChooserAnalyzer::__anonf73f4ceb0103`)
- L23 _enumerator_ `RouteId_ChooserEvaluation2` (scope `FChooserAnalyzer::__anonf73f4ceb0103`)
- L24 _enumerator_ `RouteId_ChooserValue` (scope `FChooserAnalyzer::__anonf73f4ceb0103`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserDetails.h` (Private)


#### class `UChooserRowDetails`  
`class UChooserRowDetails : public UObject`  
_L15-28_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class used for chooser editor details customization
- L20 _public prototype_ `bool ResultAssetFilter(const FAssetData& AssetData);` — `UFUNCTION()`
- L23 _public member_ `FInstancedPropertyBag Properties;` — `UPROPERTY(EditAnywhere, Category="Properties", meta=(FixedLayout, ShowOnlyInnerProperties))`
- L26 _public member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Instanced, Category="Hidden")`
- L27 _public member_ `int Row;`

#### class `UE::ChooserEditor::FChooserDetails`  
`class FChooserDetails : public IDetailCustomization`  
_L33-46_
- inherits: `IDetailCustomization`
- L36 _public function_ `FChooserDetails()`
- L37 _public prototype_ `virtual ~FChooserDetails() override = default;`
- L39 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L45 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### class `UE::ChooserEditor::FChooserRowDetails`  
`class FChooserRowDetails : public IDetailCustomization`  
_L48-61_
- inherits: `IDetailCustomization`
- L51 _public function_ `FChooserRowDetails()`
- L52 _public prototype_ `virtual ~FChooserRowDetails() override = default;`
- L54 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L60 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### class `UE::ChooserEditor::FChooserColumnDetails`  
`class FChooserColumnDetails : public IDetailCustomization`  
_L63-76_
- inherits: `IDetailCustomization`
- L66 _public function_ `FChooserColumnDetails()`
- L67 _public prototype_ `virtual ~FChooserColumnDetails() override = default;`
- L69 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L75 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserEditorModule.h` (Private)


#### class `UE::ChooserEditor::FEnumChangedListener`  
`class FEnumChangedListener : public FEnumEditorUtils::FEnumEditorManager::BaseNotifyOnChanged`  
_L18-22_
- inherits: `FEnumEditorUtils::FEnumEditorManager::BaseNotifyOnChanged`
- L20 _private prototype_ `virtual void PostChange(const UUserDefinedEnum* Changed, FEnumEditorUtils::EEnumEditorChangeInfo ChangedType) override;`
- L21 _private function_ `virtual void PreChange(const UUserDefinedEnum* Changed, FEnumEditorUtils::EEnumEditorChangeInfo ChangedType) override`

#### class `UE::ChooserEditor::FChooserEditorModule`  
`class FChooserEditorModule : public IChooserEditorModule`  
_L24-38_
- inherits: `IChooserEditorModule`
- L27 _public prototype_ `virtual TSharedPtr<IChooserTableViewModel> CreateChooserTableViewModel(UChooserTable* ChooserTable) override;`
- L28 _public prototype_ `virtual TSharedPtr<SWidget> CreateChooserTableView(TSharedPtr<IChooserTableViewModel> ViewModel, TSharedPtr<FUICommandList> CommandList) override;`
- L31 _private prototype_ `virtual void StartupModule() override;`
- L32 _private prototype_ `virtual void ShutdownModule() override;`
- L34 _private member_ `FRewindDebuggerChooser RewindDebuggerChooser;`
- L35 _private member_ `FChooserTraceModule ChooserTraceModule;`
- L37 _private member_ `FEnumChangedListener EnumChanged;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserEditorSettings.h` (Private)


#### class `UChooserEditorSettings`  
`class UChooserEditorSettings : public UDeveloperSettings`  
_L12-32_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta=(DisplayName="Chooser Editor"))`
- inherits: `UDeveloperSettings`
- L17 _public prototype_ `UChooserEditorSettings();`
- L20 _public prototype_ `virtual FText GetSectionText() const override;`
- L21 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L24 _public prototype_ `virtual FName GetCategoryName() const override;`
- L28 _public member_ `FString DefaultCreateType = "";` — `UPROPERTY(Config)` — Most Recently Used Chooser Initializer, will be used as the default on following chooser table creates
- L31 _public prototype_ `static UChooserEditorSettings& Get();` — Get Mutable CDO of UChooserEditorSettings

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserEditorWidgets.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `TSharedRef<SWidget> CreateAssetWidget(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged ValueChanged);` (scope `UE::ChooserEditor`)
- L10 _prototype_ `TSharedRef<SWidget> CreateSoftAssetWidget(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged ValueChanged);` (scope `UE::ChooserEditor`)
- L11 _prototype_ `TSharedRef<SWidget> CreateClassWidget(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged ValueChanged);` (scope `UE::ChooserEditor`)
- L12 _prototype_ `TSharedRef<SWidget> CreateEvaluateChooserWidget(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged ValueChanged);` (scope `UE::ChooserEditor`)
- L13 _prototype_ `TSharedRef<SWidget> CreateNestedChooserWidget(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged ValueChanged, IChooserTableWidgetInterface* ChooserWidgetInterface);` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserFactory.h` (Private)


#### class `UChooserTableFactory`  
`class UChooserTableFactory : public UChooserSignatureFactory`  
_L11-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UChooserSignatureFactory`
- L16 _public prototype_ `UChooserTableFactory();`
- L18 _public prototype_ `virtual bool ConfigureProperties() override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L20 _public function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`
- L24 _public function_ `virtual FName GetNewAssetThumbnailOverride() const override`

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserFindProperties.h` (Private)


#### class `UChooserFindProperties`  
`class UChooserFindProperties : public UAnimAssetFindReplaceProcessor_StringBase`  
_L11-24_
- reflection: `UCLASS(MinimalAPI, DisplayName="ChooserProperties")`
- inherits: `UAnimAssetFindReplaceProcessor_StringBase`
- desc: Find, replace and remove curves across assets
- L16 _private prototype_ `virtual FString GetFindResultStringFromAssetData(const FAssetData& InAssetData) const override;` — UAnimAssetFindReplaceProcessor interface
- L17 _private prototype_ `virtual TConstArrayView<UClass*> GetSupportedAssetTypes() const override;`
- L18 _private prototype_ `virtual bool ShouldFilterOutAsset(const FAssetData& InAssetData, bool& bOutIsOldAsset) const override;`
- L19 _private prototype_ `virtual void ReplaceInAsset(const FAssetData& InAssetData) const override;`
- L20 _private prototype_ `virtual void RemoveInAsset(const FAssetData& InAssetData) const override;`
- L23 _private prototype_ `virtual void GetAutoCompleteNames(TArrayView<FAssetData> InAssetDatas, TSet<FString>& OutUniqueNames) const override;` — UAnimAssetFindReplaceProcessor_StringBase interface

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserProvider.h` (Private)


#### struct `FChooserEvaluationData`  
`struct FChooserEvaluationData`  
_L19-23_
- L21 _public member_ `uint64 ChooserId;`
- L22 _public member_ `TArray<int32> SelectedIndices;`

#### struct `FChooserValueData`  
`struct FChooserValueData`  
_L25-31_
- L27 _public member_ `uint64 ChooserId;`
- L28 _public member_ `FName Key;`
- L30 _public member_ `TArray<uint8> Value;` — probably should get this using the linear allocator somehow:

#### class `FChooserProvider`  
`class FChooserProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L33-104_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L36 _public typedef_ `typedef TraceServices::ITimeline<FChooserEvaluationData> ChooserEvaluationTimeline;`
- L37 _public typedef_ `typedef TraceServices::ITimeline<FChooserValueData> ChooserValueTimeline;`
- L39 _public member_ `static FName ProviderName;`
- L41 _public prototype_ `FChooserProvider(TraceServices::IAnalysisSession& InSession);`
- L44 _public function_ `virtual void BeginRead() const override`
- L49 _public function_ `virtual void EndRead() const override`
- L54 _public function_ `virtual void ReadAccessCheck() const override`
- L60 _public function_ `virtual void BeginEdit() const override`
- L65 _public function_ `virtual void EndEdit() const override`
- L70 _public function_ `virtual void EditAccessCheck() const override`
- L75 _public prototype_ `bool ReadChooserEvaluationTimeline(uint64 InObjectId, TFunctionRef<void(const ChooserEvaluationTimeline&)> Callback) const;`
- L76 _public prototype_ `bool ReadChooserValueTimeline(uint64 InObjectId, TFunctionRef<void(const ChooserValueTimeline&)> Callback) const;`
- L77 _public prototype_ `void EnumerateChooserEvaluationTimelines(TFunctionRef<void(uint64 OwnerId, const ChooserEvaluationTimeline&)> Callback) const;`
- L81 _public prototype_ `void AppendChooserEvaluation(uint64 InObjectId, uint64 InChooser, TArrayView<const int32> InSelectedIndices, double InRecordingTime);`
- L83 _public function_ `void AppendChooserValue(uint64 InChooserId, uint64 InObjectId, double InRecordingTime, const FName& Key, TArrayView<const uint8> SerializedValue)`
- L96 _private prototype_ `uint32 GetTimelineIndex(uint64 ObjectId);`
- L98 _private member_ `TraceServices::IAnalysisSession& Session;`
- L99 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L101 _private member_ `TMap<uint64, uint32> ObjectIdToChooserEvaluationTimelines;`
- L102 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FChooserEvaluationData>>> ChooserEvaluationTimelines;`
- L103 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FChooserValueData>>> ChooserValueTimelines;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L16 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GChooserProviderLockState;` (scope `TraceServices`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserSignatureFactory.h` (Private)


#### class `UChooserSignatureFactory`  
`class UChooserSignatureFactory : public UFactory`  
_L12-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L17 _public prototype_ `UChooserSignatureFactory();`
- L19 _public prototype_ `virtual bool ConfigureProperties() override;`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L21 _public function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`
- L25 _public function_ `virtual FName GetNewAssetThumbnailOverride() const override`
- L28 _public member_ `FInstancedStruct ChooserInitializer;` — `UPROPERTY(EditAnywhere, DisplayName = "Chooser Type", NoClear, Category="Chooser Setup", meta = (ExcludeBaseStruct, BaseStruct = "/Script/ChooserEditor.ChooserInitializer"))`

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserTableEditor.h` (Private)


#### class `UE::ChooserEditor::FChooserTableEditor`  
`class FChooserTableEditor : public FAssetEditorToolkit`  
_L30-149_
- inherits: `FAssetEditorToolkit`
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<UObject*>, FGetDetailsViewObjects, const TArray<UObject*>&);` — Delegate that, given an array of assets, returns an array of objects to use in the details view of an FSimpleAssetEditor
- L37 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L38 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L48 _public prototype_ `void InitEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit, FGetDetailsViewObjects GetDetailsViewObjects );` — Edits the specified asset object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectsToEdit			The object to edit @param	GetDetailsViewObjects	If bound, a delegate to get the array of objects to use in the details view; uses ObjectsToEdit if not bound
- L50 _public prototype_ `virtual void FocusWindow(UObject* ObjectToFocusOn) override;`
- L52 _public prototype_ `FChooserTableEditor();`
- L55 _public prototype_ `virtual ~FChooserTableEditor();` — Destructor
- L57 _public prototype_ `virtual FName GetEditorName() const override;`
- L60 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L61 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L62 _public prototype_ `virtual FText GetToolkitName() const override;`
- L63 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L64 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L65 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L66 _public function_ `virtual bool IsPrimaryEditor() const override`
- L67 _public function_ `virtual bool IsSimpleAssetEditor() const override`
- L68 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L69 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L71 _public function_ `virtual FName GetToolMenuToolbarName(FName& OutParentName) const override`
- L78 _public prototype_ `void SetPropertyVisibilityDelegate(FIsPropertyVisible InVisibilityDelegate);` — Used to show or hide certain properties
- L80 _public prototype_ `void SetPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled InPropertyEditingDelegate);` — Can be used to disable the details view making it read-only
- L82 _public prototype_ `UChooserTable* GetRootChooser();`
- L83 _public prototype_ `void PushChooserTableToEdit(UChooserTable* Chooser);`
- L84 _public prototype_ `void SetChooserTableToEdit(UChooserTable* Chooser, bool bApplyToHistory = true);`
- L86 _private prototype_ `void AddHistory();`
- L87 _private prototype_ `bool CanNavigateBack() const;`
- L88 _private prototype_ `void NavigateBack();`
- L89 _private prototype_ `bool CanNavigateForward() const;`
- L90 _private prototype_ `void NavigateForward();`
- L91 _private prototype_ `void PopChooserTableToEdit();`
- L93 _private prototype_ `void RegisterMenus();`
- L96 _private prototype_ `TSharedRef<SDockTab> SpawnPropertiesTab( const FSpawnTabArgs& Args );` — Create the properties tab and its content
- L98 _private prototype_ `TSharedRef<SDockTab> SpawnTableTab( const FSpawnTabArgs& Args );` — Create the table tab and its content
- L100 _private prototype_ `TSharedRef<SDockTab> SpawnFindReplaceTab( const FSpawnTabArgs& Args );` — Create the find/replace tab and its content
- L102 _private prototype_ `TSharedRef<SDockTab> SpawnNestedTablesTreeTab( const FSpawnTabArgs& Args );` — Create the nested tables list tab and its content
- L105 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Called when objects need to be swapped out for new versions, like after a blueprint recompile.
- L108 _private member_ `TSharedPtr< class IDetailsView > DetailsView;` — Details view
- L112 _private member_ `static const FName ChooserEditorAppIdentifier;` — App Identifier.
- L115 _private member_ `static const FName PropertiesTabId;` — The tab ids for all the tabs used
- L116 _private member_ `static const FName FindReplaceTabId;`
- L117 _private member_ `static const FName TableTabId;`
- L118 _private member_ `static const FName NestedTablesTreeTabId;`
- L120 _private prototype_ `void RefreshNestedObjectTree();`
- L122 _private member_ `TSharedPtr<IChooserTableViewModel> ViewModel;`
- L124 _private member_ `TSharedPtr<SChooserTableWidget> ChooserTableWidget;`
- L126 _private member_ `TRingBuffer<UChooserTable*> History;`
- L127 _private member_ `int32 HistoryIndex = 0;`
- L128 _private member_ `TSharedPtr<SBreadcrumbTrail<UChooserTable*>> BreadcrumbTrail;`
- L131 _private prototype_ `TSharedRef<SWidget> MakeChoosersMenu(UObject* RootObject);`
- L132 _private prototype_ `void MakeChoosersMenuRecursive(UObject* Outer, FMenuBuilder& MenuBuilder, const FString& Indent);`
- L136 _public member_ `TSharedPtr<SNestedChooserTree> NestedChooserTree;`
- L139 _public member_ `static const FName ToolkitFName;` — The name given to all instances of this type of editor
- L141 _public prototype_ `static TSharedRef<FChooserTableEditor> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit, FGetDetailsViewObjects GetDetailsViewObjects = FGetDetailsViewObjects() );`
- L143 _public prototype_ `static TSharedRef<FChooserTableEditor> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit, FGetDetailsViewObjects GetDetailsViewObjects = FGetDetailsViewObjects() );`
- L145 _public prototype_ `static void RegisterWidgets();`
- L147 _public member_ `static FName EditorName;`
- L148 _public member_ `static FName ContextMenuName;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<UObject*>, FGetDetailsViewObjects, const TArray<UObject*>&);` — Delegate that, given an array of assets, returns an array of objects to use in the details view of an FSimpleAssetEditor

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserTableViewModel.h` (Private)


#### class `UChooserColumnDetails`  
`class UChooserColumnDetails : public UObject`  
_L25-32_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class used for chooser editor details customization
- L30 _public member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(EditAnywhere, Instanced, Category="Hidden")`
- L31 _public member_ `int32 Column = -1;`

#### class `UE::ChooserEditor::FChooserTableViewModel`  
`class FChooserTableViewModel : public IChooserTableViewModel, public IChooserTableWidgetInterface, public FSelfRegisteringEditorUndoClient`  
_L44-210_
- inherits: `IChooserTableViewModel,IChooserTableWidgetInterface,FSelfRegisteringEditorUndoClient`
- L48 _public prototype_ `FChooserTableViewModel(UChooserTable* Chooser);`
- L50 _public function_ `virtual void OpenObject(UObject* Object) override`
- L56 _public function_ `virtual void SetOpenObjectDelegate(FOpenObject InOpenObjectDelegate) override` — IChooserTableViewModel interface
- L61 _public function_ `virtual void SetShowDetailsDelegate(FShowDetails InShowDetailsDelegate) override`
- L66 _public prototype_ `virtual void RegisterMenus(TSharedPtr<FUICommandList> CommandList) override;`
- L68 _public function_ `virtual const UChooserTable* GetRootChooser() const override`
- L69 _public function_ `virtual UChooserTable* GetRootChooser() override`
- L71 _public function_ `virtual UChooserTable* GetChooser() override`
- L72 _public function_ `virtual const UChooserTable* GetChooser() const override`
- L74 _public prototype_ `virtual void RefreshAll() override;`
- L76 _public prototype_ `virtual void SetChooser(UChooserTable* Chooser) override;`
- L78 _public prototype_ `virtual void AutoPopulateAll() override;`
- L80 _public prototype_ `virtual void SelectRootProperties() override;`
- L82 _public prototype_ `void MakeDebugTargetMenu(UToolMenu* InToolMenu);`
- L85 _public prototype_ `virtual void NotifyPreChange( FProperty* PropertyAboutToChange ) override;` — Begin FNotifyHook Interface
- L86 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L88 _public prototype_ `int32 GetNumRows() const;`
- L90 _public prototype_ `bool AreRowsDisabled(TConstArrayView<int32> RowIndices) const;`
- L91 _public prototype_ `bool IsColumnDisabled(int32 ColumnIndex) const;`
- L92 _public prototype_ `void ToggleDisableRows(TConstArrayView<int32> RowIndices);`
- L93 _public prototype_ `void ToggleDisableColumn(int32 ColumnIndex);`
- L94 _public prototype_ `void DuplicateColumn(int32 ColumnIndex);`
- L95 _public prototype_ `void DuplicateRows(TConstArrayView<int32> RowIndices);`
- L96 _public prototype_ `bool HasFallbackSelected();`
- L98 _public prototype_ `bool IsRandomizeColumn(int32 ColumnIndex);`
- L100 _public prototype_ `bool CanMoveRowsUp(TConstArrayView<int32> RowIndices);`
- L101 _public prototype_ `bool CanMoveRowsDown(TConstArrayView<int32> RowIndices);`
- L102 _public prototype_ `bool CanMoveColumnLeft(int32 ColumnIndex);`
- L103 _public prototype_ `void MoveColumnLeft(int32 ColumnIndex);`
- L104 _public prototype_ `bool CanMoveColumnRight(int32 ColumnIndex);`
- L105 _public prototype_ `void MoveColumnRight(int32 ColumnIndex);`
- L107 _public prototype_ `void CopyColumn(int32 ColumnIndex);`
- L108 _public prototype_ `void CopyRows(TConstArrayView<int> RowIndices);`
- L110 _public prototype_ `void RemoveDisabledData();`
- L112 _public prototype_ `bool CanAutoPopulateColumn(int32 ColumnIndex) const;`
- L113 _public prototype_ `bool CanAutoPopulateRows() const;`
- L114 _public prototype_ `void AutoPopulateColumn(int32 ColumnIndex);`
- L115 _public prototype_ `void AutoPopulateRows(TConstArrayView<int> RowIndices);`
- L116 _public prototype_ `void AutoPopulateRow(int32 Index);`
- L118 _public prototype_ `void ClearSelectedColumn();`
- L119 _public prototype_ `void DeleteColumn(int32 Index);`
- L120 _public prototype_ `void AddColumn(const UScriptStruct* ColumnType);`
- L123 _public prototype_ `void DeleteRows(TConstArrayView<int32> RowsToDelete);`
- L124 _public prototype_ `int32 DeleteRowsInternal(TConstArrayView<int32> RowsToDelete, int32 RowIndexToRemember = 0);`
- L126 _public prototype_ `void MoveRows(TConstArrayView<int32> RowIndices, int32 TargetIndex);`
- L127 _public prototype_ `int32 MoveColumn(int32 SourceIndex, int32 TargetIndex);`
- L128 _public prototype_ `void Paste();`
- L129 _public prototype_ `bool CanPaste() const;`
- L136 _public prototype_ `void RefreshRowSelectionDetails();`
- L137 _public function_ `ESelectionType GetCurrentSelectionType() const`
- L138 _public function_ `void SetCurrentSelectionType(ESelectionType SelectionType)`
- L140 _public prototype_ `void RefreshAssetRegistry();` — update nested chooser info in asset registry
- L142 _public prototype_ `void ClearSelectedRows();`
- L143 _public prototype_ `void SelectRows(const TConstArrayView<int32>& Rows);` — called internally to change row selection after operations
- L144 _public prototype_ `void SelectColumn(UChooserTable* Chooser, int32 Index);`
- L145 _public prototype_ `bool IsRowSelected(int32 RowIndex);`
- L146 _public prototype_ `bool IsColumnSelected(int32 ColumnIndex);`
- L147 _public prototype_ `bool HasSelection() const;`
- L148 _public prototype_ `bool HasRowsSelected() const;`
- L149 _public prototype_ `bool HasColumnSelected() const;`
- L151 _public prototype_ `void SetSelectedRows(const TConstArrayView<int32>& Rows);` — called by widget when list view selection changes
- L153 _public function_ `int32 GetSelectedColumn()`
- L162 _public function_ `TConstArrayView<int32> GetSelectedRows() const`
- L167 _public member_ `ESelectionType CurrentSelectionType = ESelectionType::Root;`
- L169 _public member_ `TArray<int32> SelectedRowIndices;`
- L170 _public member_ `TStrongObjectPtr<UChooserColumnDetails> SelectedColumn;`
- L171 _public member_ `TArray<TObjectPtr<UChooserRowDetails>> SelectedRows;`
- L173 _public member_ `TArray<TStrongObjectPtr<UChooserRowDetails>> SelectedRowsCache;` — cache of objects to reuse for SelectedRows
- L175 _public member_ `FOpenObject OpenObjectDelegate;`
- L176 _public member_ `FShowDetails ShowDetailsDelegate;`
- L177 _public member_ `FRefreshTable RefreshTableColumnsDelegate;`
- L178 _public member_ `FRefreshTable RefreshTableRowsDelegate;`
- L179 _public member_ `FSelectRows SelectRowsDelegate;`
- L181 _public prototype_ `UChooserTable* CopyColumnInternal(int32 ColumnIndex);`
- L182 _public prototype_ `UChooserTable* CopyRowsInternal(TConstArrayView<int32> RowIndices);`
- L183 _public prototype_ `void PasteInternal(UChooserTable* PasteObject, int32 PasteRowIndex=-1);`
- L185 _public prototype_ `void UpdateTableRows();`
- L186 _public prototype_ `void UpdateTableColumns();`
- L188 _public prototype_ `void QueueRowTransaction(UChooserRowDetails* RowDetails);`
- L189 _public prototype_ `void OnObjectsTransacted(UObject* Object, const FTransactionObjectEvent& Event);`
- L192 _public prototype_ `virtual bool MatchesContext( const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts ) const override;` — FEditorUndoClient Interface
- L193 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L194 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L197 _private prototype_ `void AutoPopulateColumn(FChooserColumnBase& Column);`
- L199 _private prototype_ `bool HandleTicker(float DeltaTime);`
- L201 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;`
- L204 _private member_ `UChooserTable* RootChooser = nullptr;` — the root asset for the chooser editor
- L207 _private member_ `UChooserTable* CurrentChooser = nullptr;` — the current (possibly nested) chooser table being edited
- L209 _private member_ `TArray<TWeakObjectPtr<UChooserRowDetails>> QueuedRowTransactions;`

#### enum `UE::ChooserEditor::FChooserTableViewModel::ESelectionType`  
`enum class ESelectionType`  
_L131-134_
- L133 _public enumerator_ `Root`
- L133 _public enumerator_ `Root`
- L133 _public enumerator_ `Root`

#### Free symbols / members of external scopes

- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L41 _delegate_ `DECLARE_DELEGATE(FRefreshTable);`
- L41 _prototype_ `DECLARE_DELEGATE(FRefreshTable);` (scope `UE::ChooserEditor`)
- L42 _delegate_ `DECLARE_DELEGATE_OneParam(FSelectRows, TConstArrayView<int32>);`
- L42 _prototype_ `DECLARE_DELEGATE_OneParam(FSelectRows, TConstArrayView<int32>);` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserTraceModule.h` (Private)


#### class `FChooserTraceModule`  
`class FChooserTraceModule : public TraceServices::IModule`  
_L10-22_
- inherits: `TraceServices::IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L15 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L16 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L17 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L18 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L21 _private member_ `static FName ModuleName;`

### `Plugins/Chooser/Source/ChooserEditor/Private/ChooserTrack.h` (Private)


#### class `UE::ChooserEditor::FChooserTrack`  
`class FChooserTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L14-41_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L17 _public prototype_ `FChooserTrack(uint64 InObjectId, uint64 InChooserId);`
- L18 _public prototype_ `virtual ~FChooserTrack();`
- L20 _public function_ `uint64 GetChooserId()`
- L22 _private prototype_ `virtual bool UpdateInternal() override;`
- L23 _private prototype_ `TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L24 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L25 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L26 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L27 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L29 _private prototype_ `virtual bool HandleDoubleClickInternal() override;` — virtual FName GetNameInternal() const override { return Category; }
- L31 _private prototype_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetEventData() const;`
- L33 _private member_ `mutable TSharedPtr<SEventTimelineView::FTimelineEventData> EventData;`
- L34 _private member_ `mutable int EventUpdateRequested = 0;`
- L36 _private member_ `UChooserTable* ChooserTable = 0;`
- L37 _private member_ `uint64 ObjectId;`
- L38 _private member_ `uint64 ChooserId;`
- L39 _private member_ `FSlateIcon Icon;`
- L40 _private member_ `FText TrackName;`

#### class `UE::ChooserEditor::FChoosersTrack`  
`class FChoosersTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L46-64_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- desc: Parent track
- L49 _public prototype_ `FChoosersTrack(uint64 InObjectId);`
- L51 _private prototype_ `virtual bool UpdateInternal() override;`
- L52 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L54 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L55 _private function_ `virtual FName GetNameInternal() const override`
- L56 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L57 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L58 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L60 _private member_ `FSlateIcon Icon;`
- L61 _private member_ `uint64 ObjectId;`
- L63 _private member_ `TArray<TSharedPtr<FChooserTrack>> Children;`

#### class `UE::ChooserEditor::FChoosersTrackCreator`  
`class FChoosersTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L67-75_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L70 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L71 _private prototype_ `virtual FName GetNameInternal() const override;`
- L72 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L73 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L74 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/CurveOverrideCustomization.h` (Private)


#### class `UE::ChooserEditor::FCurveOverrideListCustomization`  
`class FCurveOverrideListCustomization : public IPropertyTypeCustomization`  
_L10-16_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L15 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### class `UE::ChooserEditor::FCurveOverrideCustomization`  
`class FCurveOverrideCustomization : public IPropertyTypeCustomization`  
_L19-25_
- inherits: `IPropertyTypeCustomization`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/EnumColumnEditor.h` (Private)


#### class `UE::ChooserEditor::SEnumCell`  
`class SEnumCell : public SCompoundWidget`  
_L14-40_
- inherits: `SCompoundWidget`
- desc: Enum combo box widget with a dynamic UEnum
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueSet, int);`
- L20 _public function_ `SLATE_BEGIN_ARGS(SEnumCell)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(const UEnum*, Enum);`
- L24 _public prototype_ `SLATE_ATTRIBUTE(int32, EnumValue);`
- L25 _public prototype_ `SLATE_EVENT(FOnValueSet, OnValueSet) SLATE_END_ARGS() TSharedRef<SWidget> GenerateEnumMenu() const;`
- L30 _public prototype_ `TSharedRef<SWidget> CreateEnumComboBox();`
- L32 _public prototype_ `void Construct( const FArguments& InArgs);`
- L34 _public prototype_ `virtual ~SEnumCell() = default;`
- L37 _private member_ `FOnValueSet OnValueSet;`
- L38 _private member_ `TAttribute<int32> EnumValue;`
- L39 _private member_ `TAttribute<const UEnum*> Enum;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "EnumColumnEditor"`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueSet, int);`
- L42 _prototype_ `void RegisterEnumWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/FloatDistanceColumnEditor.h` (Private)


#### class `UFloatAutoPopulatorBlueprint`  
`class UFloatAutoPopulatorBlueprint : public UFloatAutoPopulator`  
_L15-23_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UFloatAutoPopulator`
- L20 _public prototype_ `void AutoPopulate(UObject* Object, bool& Success, float& Value);` — `UFUNCTION(BlueprintImplementableEvent)`
- L22 _public function_ `virtual void NativeAutoPopulate(UObject* InObject, bool& OutSuccess, float& OutValue)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L11 _prototype_ `void RegisterFloatDistanceWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/FloatRangeColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterFloatRangeWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/FrameTimeCustomization.h` (Private)


#### enum `ETimeFloatFormat`  
`enum class ETimeFloatFormat`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `Frames`
- L14 _public enumerator_ `Seconds`

#### class `UE::ChooserEditor::FFrameTimePropertyTypeIdentifier`  
`class FFrameTimePropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L20-27_
- inherits: `IPropertyTypeIdentifier`
- L23 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& PropertyHandle) const override`

#### class `UE::ChooserEditor::FFrameTimeCustomization`  
`class FFrameTimeCustomization : public IPropertyTypeCustomization`  
_L29-35_
- inherits: `IPropertyTypeCustomization`
- L33 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L34 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/GameplayTagColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterGameplayTagWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/GameplayTagQueryColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L7 _prototype_ `void RegisterGameplayTagQueryWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/MultiEnumColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterMultiEnumWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/NameColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterNameWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ObjectClassColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterObjectClassWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/ObjectColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterObjectWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/OutputEnumColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterOutputEnumWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/OutputFloatColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterOutputFloatWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/OutputNameColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterOutputNameWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/OutputObjectColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterOutputObjectWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/OutputStructColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterStructWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/PropertyAccessChainCustomization.h` (Private)


#### class `UE::ChooserEditor::FPropertyAccessChainCustomization`  
`class FPropertyAccessChainCustomization : public IPropertyTypeCustomization`  
_L10-18_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `FPropertyAccessChainCustomization()`
- L16 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L17 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/RandomizeColumnEditor.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L9 _prototype_ `void RegisterRandomizeWidgets();` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Private/RewindDebuggerChooser.h` (Private)


#### class `FRewindDebuggerChooser`  
`class FRewindDebuggerChooser : public IRewindDebuggerExtension`  
_L10-18_
- inherits: `IRewindDebuggerExtension`
- L13 _public prototype_ `FRewindDebuggerChooser();`
- L14 _public prototype_ `virtual ~FRewindDebuggerChooser() = default;`
- L16 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`
- L17 _public function_ `virtual FString GetName()`

### `Plugins/Chooser/Source/ChooserEditor/Private/SChooserColumnHandle.h` (Private)


#### class `UE::ChooserEditor::FChooserColumnDragDropOp`  
`class FChooserColumnDragDropOp : public FDecoratedDragDropOp`  
_L11-21_
- inherits: `FDecoratedDragDropOp`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FChooserColumnDragDropOp, FDecoratedDragDropOp) TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L17 _public member_ `uint32 ColumnIndex;`
- L20 _public prototype_ `static TSharedRef<FChooserColumnDragDropOp> New(TSharedPtr<FChooserTableViewModel> InViewModel, uint32 InColumnIndex);` — Constructs the drag drop operation

#### class `UE::ChooserEditor::SChooserColumnHandle`  
`class SChooserColumnHandle : public SCompoundWidget`  
_L23-53_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SChooserColumnHandle)`
- L28 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<FChooserTableViewModel>, ViewModel) SLATE_ARGUMENT(uint32, ColumnIndex) SLATE_ARGUMENT(bool, NoDropAfter) SLATE_ATTRIBUTE(bool, TableHasFocus);`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L39 _public prototype_ `void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L40 _public prototype_ `void OnDragLeave(const FDragDropEvent& DragDropEvent);`
- L41 _public prototype_ `FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L42 _public prototype_ `FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L45 _private member_ `TAttribute<bool> TableHasFocus;`
- L46 _private member_ `TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L47 _private member_ `int32 ColumnIndex = 0;`
- L48 _private member_ `int32 DragActiveCounter = 0;`
- L49 _private member_ `bool bDragActive = false;`
- L50 _private member_ `bool bDropBefore = false;`
- L51 _private member_ `bool bDropSupported = false;`
- L52 _private member_ `bool bNoDropAfter = false;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/SChooserCreateColumnButton.h` (Private)


#### class `UE::ChooserEditor::SChooserCreateColumnButton`  
`class SChooserCreateColumnButton : public SCompoundWidget`  
_L15-29_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SChooserCreateColumnButton)`
- L20 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FChooserTableViewModel>, ViewModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _private member_ `TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L28 _private prototype_ `TSharedRef<SWidget> MakeCreateColumnMenu();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/SChooserCreateDialog.h` (Private)


#### class `SChooserCreateDialog`  
`class SChooserCreateDialog : public SCompoundWidget`  
_L14-46_
- inherits: `SCompoundWidget`
- desc: Dialog to configure creation properties
- L17 _public function_ `SLATE_BEGIN_ARGS( SChooserCreateDialog )`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L25 _public prototype_ `bool ConfigureProperties(TWeakObjectPtr<UChooserSignatureFactory> InChooserFactory);` — Sets properties for the supplied AnimBlueprintFactory
- L30 _private prototype_ `FReply OkClicked();` — Handler for when ok is clicked
- L32 _private prototype_ `void CloseDialog(bool bWasPicked=false);`
- L35 _private prototype_ `FReply CancelClicked();` — Handler for when cancel is clicked
- L36 _private prototype_ `FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent );`
- L40 _private member_ `TWeakObjectPtr<UChooserSignatureFactory> ChooserFactory;` — The factory for which we are setting up properties
- L41 _private member_ `TSharedPtr<SWindow> Window;`
- L42 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L45 _private member_ `bool bOkClicked = false;` — True if Ok was clicked

### `Plugins/Chooser/Source/ChooserEditor/Private/SChooserCreateRowButton.h` (Private)


#### class `UE::ChooserEditor::SChooserCreateRowButton`  
`class SChooserCreateRowButton : public SCompoundWidget`  
_L15-29_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SChooserCreateRowButton)`
- L20 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FChooserTableViewModel>, ViewModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _private member_ `TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L28 _private prototype_ `TSharedRef<SWidget> MakeCreateRowMenu();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/SChooserRowHandle.h` (Private)


#### class `UE::ChooserEditor::FChooserRowDragDropOp`  
`class FChooserRowDragDropOp : public FDecoratedDragDropOp`  
_L13-26_
- inherits: `FDecoratedDragDropOp`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FChooserRowDragDropOp, FDecoratedDragDropOp) UChooserTable* RowData = nullptr;`
- L19 _public member_ `int32 TransactionIndex = -1;`
- L20 _public member_ `TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L23 _public prototype_ `static TSharedRef<FChooserRowDragDropOp> New(TSharedPtr<FChooserTableViewModel> InViewModel, uint32 InRowIndex);` — Constructs the drag drop operation
- L25 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`

#### class `UE::ChooserEditor::SChooserRowHandle`  
`class SChooserRowHandle : public SCompoundWidget`  
_L28-46_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(SChooserRowHandle)`
- L33 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<FChooserTableViewModel>, ViewModel) SLATE_ARGUMENT(uint32, RowIndex) SLATE_END_ARGS() void Construct(const FArguments& InArgs, bool bShowImage);`
- L40 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L44 _private member_ `TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L45 _private member_ `uint32 RowIndex = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/SChooserTableRow.h` (Private)


#### struct `UE::ChooserEditor::FChooserTableRow`  
`struct FChooserTableRow`  
_L14-18_
- L16 _public function_ `FChooserTableRow(int32 i)`
- L17 _public member_ `int32 RowIndex;`

#### class `UE::ChooserEditor::SChooserTableRow`  
`class SChooserTableRow : public SMultiColumnTableRow<TSharedPtr<FChooserTableRow>>`  
_L20-53_
- inherits: `SMultiColumnTableRow<TSharedPtr<FChooserTableRow>>`
- L23 _public function_ `SLATE_BEGIN_ARGS(SChooserTableRow)`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FChooserTableRow>, Entry) SLATE_ARGUMENT(UChooserTable*, Chooser) SLATE_ARGUMENT(TSharedPtr<FChooserTableViewModel>, ViewModel) SLATE_ATTRIBUTE(bool, TableHasFocus);` — The list item for this row
- L33 _public prototype_ `void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView);`
- L36 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the list view.
- L37 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L38 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L39 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L40 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L41 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L44 _private member_ `TAttribute<bool> TableHasFocus;`
- L45 _private member_ `TSharedPtr<FChooserTableRow> RowIndex;`
- L46 _private member_ `UChooserTable* Chooser;`
- L47 _private member_ `TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L48 _private member_ `TSharedPtr<SBorder> CacheBorder;`
- L49 _private member_ `int DragActiveCounter = 0;`
- L50 _private member_ `bool bDragActive = false;`
- L51 _private member_ `bool bDropSupported = false;`
- L52 _private member_ `bool bDropAbove = false;`

#### enum `UE::ChooserEditor::SChooserTableRow::(anonymous)`  
`enum`  
_L31-31_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L31 _enumerator_ `enum { SpecialIndex_AddRow = -1, SpecialIndex_Fallback = -2 }; void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView); virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override; virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override; virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;` (scope `UE::ChooserEditor::SChooserTableRow::__anone77f2ab80103`)
- L31 _enumerator_ `enum { SpecialIndex_AddRow = -1, SpecialIndex_Fallback = -2 }; void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView); virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override; virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override; virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;` (scope `UE::ChooserEditor::SChooserTableRow::__anone77f2ab80103`)

### `Plugins/Chooser/Source/ChooserEditor/Private/SChooserTableWidget.h` (Private)


#### class `UE::ChooserEditor::SChooserTableWidget`  
`class SChooserTableWidget : public IChooserTableView`  
_L15-90_
- inherits: `IChooserTableView`
- L18 _public function_ `SLATE_BEGIN_ARGS(SChooserTableWidget)`
- L20 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, Commands) SLATE_ARGUMENT(TSharedPtr<IChooserTableViewModel>, ViewModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `void SelectRows(const TConstArrayView<int32> Rows);`
- L28 _public prototype_ `void SelectRow(int32 RowIndex, bool bClear = true);`
- L30 _public prototype_ `void UpdateTableColumns();`
- L31 _public prototype_ `void UpdateTableRows();`
- L33 _public prototype_ `void ClearSelection();`
- L34 _public prototype_ `void GetSelectedItems(TArray<TSharedPtr<FChooserTableRow>> &SelectedItems);`
- L36 _public prototype_ `int GetSelectedColumn() const;`
- L38 _public prototype_ `bool TableHasFocus() const;`
- L42 _public prototype_ `bool HasSelection() const;`
- L43 _public prototype_ `bool HasRowsSelected() const;`
- L44 _public prototype_ `bool HasColumnSelected() const;`
- L46 _public prototype_ `void SelectRootProperties();`
- L48 _public prototype_ `bool CanAutoPopulateSelection() const;`
- L49 _public prototype_ `void AutoPopulateSelection();`
- L50 _public prototype_ `void AutoPopulateAll();`
- L52 _public prototype_ `void RemoveDisabledData();`
- L53 _public prototype_ `void DeleteSelection();`
- L54 _public prototype_ `void DuplicateSelection();`
- L56 _public prototype_ `bool IsSelectionDisabled() const;`
- L57 _public prototype_ `void ToggleDisableSelection();`
- L59 _public prototype_ `void CopySelection();`
- L60 _public prototype_ `void CutSelection();`
- L61 _public prototype_ `bool CanPaste() const;`
- L62 _public prototype_ `void Paste();`
- L64 _public prototype_ `bool CanMoveRowsUp();`
- L65 _public prototype_ `void MoveRowsUp();`
- L66 _public prototype_ `bool CanMoveRowsDown();`
- L67 _public prototype_ `void MoveRowsDown();`
- L68 _public prototype_ `bool CanMoveColumnLeft();`
- L69 _public prototype_ `void MoveColumnLeft();`
- L70 _public prototype_ `bool CanMoveColumnRight();`
- L71 _public prototype_ `void MoveColumnRight();`
- L74 _public function_ `virtual TSharedPtr<IChooserTableViewModel> GetViewModel() override`
- L77 _private prototype_ `void BindCommands(TSharedPtr<FUICommandList> CommandList);`
- L79 _private member_ `TSharedPtr<SListView<TSharedPtr<FChooserTableRow>>> TableView;`
- L80 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L82 _private member_ `TSharedPtr<SWidget> CreateColumnComboButton;`
- L83 _private prototype_ `TSharedPtr<SWidget> GenerateRowContextMenu();`
- L84 _private prototype_ `TSharedRef<ITableRow> GenerateTableRow(TSharedPtr<FChooserTableRow> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L86 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L88 _private member_ `TSharedPtr<FChooserTableViewModel> ChooserViewModel;`
- L89 _private member_ `TArray<TSharedPtr<FChooserTableRow>> TableRows;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Private/SNestedChooserTree.h` (Private)


#### struct `UE::ChooserEditor::FNestedChooserTreeEntry`  
`struct FNestedChooserTreeEntry`  
_L14-18_
- L16 _public member_ `UObject* Object = nullptr;`
- L17 _public member_ `bool bExpanded = true;`

#### class `UE::ChooserEditor::SNestedChooserTree`  
`class SNestedChooserTree : public SCompoundWidget`  
_L20-46_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SNestedChooserTree)`
- L25 _public prototype_ `SLATE_ARGUMENT(FChooserTableEditor*, ChooserEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `void RefreshAll();`
- L33 _private prototype_ `TSharedPtr<SWidget> TreeViewContextMenuOpening();`
- L34 _private prototype_ `TSharedRef<ITableRow> TreeViewGenerateRow(TSharedPtr<FNestedChooserTreeEntry> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L35 _private prototype_ `void TreeViewGetChildren(TSharedPtr<FNestedChooserTreeEntry> InItem, TArray<TSharedPtr<FNestedChooserTreeEntry>>& OutChildren);`
- L36 _private prototype_ `void TreeViewDoubleClicked(TSharedPtr<FNestedChooserTreeEntry> SelectedObject);`
- L37 _private prototype_ `void DeleteNestedObject();`
- L38 _private prototype_ `void RenameNestedObject();`
- L40 _private member_ `FChooserTableEditor* ChooserEditor = nullptr;`
- L41 _private member_ `UChooserTable* RootChooser = nullptr;`
- L42 _private member_ `TSharedPtr<STreeView<TSharedPtr<FNestedChooserTreeEntry>>> TreeView;`
- L44 _private member_ `TArray<TSharedPtr<FNestedChooserTreeEntry>> TreeEntries;`
- L45 _private member_ `TArray<TSharedPtr<FNestedChooserTreeEntry>> AllChoosers;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Public/ChooserColumnHeader.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L13 _prototype_ `TSharedRef<SWidget> MakeColumnHeaderWidget(UChooserTable* Chooser, FChooserColumnBase* Column, const FText& ColumnName,const FText& ColumnTooltip, const FSlateBrush* ColumnIcon, TSharedPtr<SWidget> DebugWidget, FChooserWidgetValueChanged ValueChanged = FChooserWidgetValueChanged());` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Public/ChooserEditorStyle.h` (Public)


#### class `UE::ChooserEditor::FChooserEditorStyle`  
`class FChooserEditorStyle : FSlateStyleSet`  
_L10-22_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `FChooserEditorStyle();`
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L21 _private member_ `static TSharedPtr< FChooserEditorStyle > StyleInstance;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Public/ChooserInitializer.h` (Public)


#### struct `FChooserInitializer`  
`struct FChooserInitializer`  
_L10-31_
- reflection: `USTRUCT()`
- L13 _public prototype_ `virtual ~FChooserInitializer() = default;`
- L15 _public function_ `virtual UClass* OverrideClass(UClass* Class) const`
- L20 _public function_ `virtual void InitializeSignature(UChooserSignature* ChooserSignature) const`
- L30 _public function_ `virtual void Initialize(UChooserTable* Chooser) const` — Deprecated, implement InitializeSignature

#### struct `FGenericChooserInitializer`  
`struct FGenericChooserInitializer : public FChooserInitializer`  
_L35-53_
- reflection: `USTRUCT(DisplayName="Generic Chooser", Meta = (ToolTip="A ChooserTable for use in Blueprint, which can return an arbitrary Asset type or Class, and can take any number of Objects or Structs as Parameters."))`
- inherits: `FChooserInitializer`
- L39 _public prototype_ `virtual void InitializeSignature(UChooserSignature* ChooserSignature) const override;`
- L43 _public member_ `EObjectChooserResultType ResultType = EObjectChooserResultType::ObjectResult;` — `UPROPERTY(EditAnywhere, DisplayName = "Result Type", Category="Result")` — The kind of output this chooser has (Object or Class)
- L48 _public member_ `TObjectPtr<UClass> OutputObjectType;` — `UPROPERTY(EditAnywhere, DisplayName= "Result Class", Category="Result", Meta = (AllowAbstract=true))` — The Class of Object this Chooser returns when ResultType is set to ObjectOfType, or the Parent Class of the Classes returned by this chooser when ResultType is set to ClassOfType
- L52 _public member_ `TArray<FInstancedStruct> ContextData;` — `UPROPERTY(EditAnywhere, DisplayName = "Parameters", NoClear, Meta = (ExpandByDefault, ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ContextObjectTypeBase"), Category = "Parameters")` — Parameter Objects or Structs from which the chooser can read or write properties

#### struct `FChooserPlayerInitializer`  
`struct FChooserPlayerInitializer : public FChooserInitializer`  
_L56-63_
- reflection: `USTRUCT(DisplayName="Animation Chooser", meta = (ToolTip="A ChooserTable for use with the ChooserPlayer AnimGraph node.\nReturns an AnimAsset, and takes an AnimInstance, and a ChooserPlayerSettings struct as parameters."))`
- inherits: `FChooserInitializer`
- L59 _public prototype_ `virtual void InitializeSignature(UChooserSignature* Chooser) const override;`
- L62 _public member_ `TObjectPtr<UClass> AnimClass;` — `UPROPERTY(EditAnywhere, Category="AnimClass")`

#### struct `FNoPrimaryResultChooserInitializer`  
`struct FNoPrimaryResultChooserInitializer : public FChooserInitializer`  
_L66-75_
- reflection: `USTRUCT(DisplayName="No Primary Result Chooser", Meta = (ToolTip="A ChooserTable for use in Blueprint, which returns no primary result but writes to outputs (useful if you are interested in returning only integral types like a float or string). Note: this table can't evaluate or nest other tables, and will set its outputs to the first row that matches (no 'multi' mode)."))`
- inherits: `FChooserInitializer`
- L70 _public prototype_ `virtual void InitializeSignature(UChooserSignature* Chooser) const override;`
- L74 _public member_ `TArray<FInstancedStruct> ContextData;` — `UPROPERTY(EditAnywhere, DisplayName = "Parameters", NoClear, Meta = (ExpandByDefault, ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ContextObjectTypeBase"), Category = "Parameters")` — Parameter Objects or Structs from which the chooser can read or write properties

### `Plugins/Chooser/Source/ChooserEditor/Public/ChooserTableEditorCommands.h` (Public)


#### class `FChooserTableEditorCommands`  
`class FChooserTableEditorCommands : public TCommands<FChooserTableEditorCommands>`  
_L11-43_
- inherits: `TCommands<FChooserTableEditorCommands>`
- L15 _public function_ `FChooserTableEditorCommands() : TCommands<FChooserTableEditorCommands>("ChooserTableEditor", NSLOCTEXT("Contexts", "ChooserTableEditor", "Chooser Table Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L20 _public member_ `TSharedPtr<FUICommandInfo> EditChooserSettings;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AutoPopulateAll;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> AutoPopulateSelection;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> RemoveDisabledData;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> Disable;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> MoveLeft;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> MoveRight;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> MoveUp;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> MoveDown;`
- L31 _public function_ `virtual void RegisterCommands() override` — Initialize commands

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "ChooserTableEditorCommands"`

### `Plugins/Chooser/Source/ChooserEditor/Public/IChooserEditorModule.h` (Public)


#### class `UE::ChooserEditor::IChooserEditorModule`  
`class IChooserEditorModule : public IModuleInterface`  
_L15-20_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual TSharedPtr<IChooserTableViewModel> CreateChooserTableViewModel(UChooserTable* ChooserTable) = 0;`
- L19 _public prototype_ `virtual TSharedPtr<SWidget> CreateChooserTableView(TSharedPtr<IChooserTableViewModel> ViewModel, TSharedPtr<FUICommandList> CommandList) = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Public/IChooserTableView.h` (Public)


#### class `UE::ChooserEditor::IChooserTableView`  
`class IChooserTableView : public SCompoundWidget`  
_L15-19_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `virtual TSharedPtr<IChooserTableViewModel> GetViewModel() = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Public/IChooserTableViewModel.h` (Public)


#### class `UE::ChooserEditor::IChooserTableViewModel`  
`class IChooserTableViewModel : public TSharedFromThis<IChooserTableViewModel>, public FNotifyHook`  
_L22-42_
- inherits: `TSharedFromThis<IChooserTableViewModel>,FNotifyHook`
- L25 _public function_ `virtual ~IChooserTableViewModel()`
- L27 _public prototype_ `virtual void SetShowDetailsDelegate(FShowDetails InShowDetailsDelegate) = 0;`
- L28 _public prototype_ `virtual void SetOpenObjectDelegate(FOpenObject InOpenObjectDelegate) = 0;`
- L29 _public prototype_ `virtual void RegisterMenus(TSharedPtr<FUICommandList> CommandList) = 0;`
- L31 _public prototype_ `virtual const UChooserTable* GetRootChooser() const = 0;`
- L32 _public prototype_ `virtual UChooserTable* GetRootChooser() = 0;`
- L33 _public prototype_ `virtual UChooserTable* GetChooser() = 0;`
- L34 _public prototype_ `virtual const UChooserTable* GetChooser() const = 0;`
- L35 _public prototype_ `virtual void SetChooser(UChooserTable* Chooser) = 0;`
- L37 _public prototype_ `virtual void RefreshAll() = 0;`
- L38 _public prototype_ `virtual void AutoPopulateAll() = 0;`
- L39 _public prototype_ `virtual void SelectRootProperties() = 0;`
- L41 _public member_ `static const FName ChooserToolbarName;`

#### class `UChooserEditorToolMenuContext`  
`class UChooserEditorToolMenuContext : public UObject`  
_L47-53_
- reflection: `UCLASS()`
- inherits: `UObject`
- L52 _public member_ `TWeakPtr<UE::ChooserEditor::IChooserTableViewModel> ViewModel;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FShowDetails, const TArray<UObject*>&);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FShowDetails, const TArray<UObject*>&);` (scope `UE::ChooserEditor`)
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOpenObject, UObject*);`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOpenObject, UObject*);` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Public/ObjectChooserClassFilter.h` (Public)


#### class `UE::ChooserEditor::FInterfaceClassFilter`  
`class FInterfaceClassFilter : public IClassViewerFilter`  
_L10-27_
- inherits: `IClassViewerFilter`
- desc: Filter class for things which implement a particular interface
- L13 _public function_ `FInterfaceClassFilter(UClass* InInterfaceType) : InterfaceType(InInterfaceType)`
- L14 _public prototype_ `virtual ~FInterfaceClassFilter() override = default;`
- L16 _public function_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< class FClassViewerFilterFuncs > InFilterFuncs ) override`
- L21 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const class IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< class FClassViewerFilterFuncs > InFilterFuncs) override`
- L26 _private member_ `UClass* InterfaceType;`

#### class `UE::ChooserEditor::FStructFilter`  
`class FStructFilter : public IStructViewerFilter`  
_L29-49_
- inherits: `IStructViewerFilter`
- L32 _public function_ `FStructFilter(const UScriptStruct* InBaseType) : BaseType(InBaseType)`
- L34 _public function_ `virtual bool IsStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const UScriptStruct* InStruct, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override`
- L43 _public function_ `virtual bool IsUnloadedStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const FSoftObjectPath& InStructPath, TSharedRef<class FStructViewerFilterFuncs> InFilterFuncs)`
- L48 _private member_ `const UScriptStruct* BaseType;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChooserEditor` (scope `UE`)

### `Plugins/Chooser/Source/ChooserEditor/Public/ObjectChooserWidgetFactories.h` (Public)


#### enum `UE::ChooserEditor::(anonymous)`  
`enum`  
_L19-19_

#### enum `UE::ChooserEditor::(anonymous)`  
`enum`  
_L20-20_

#### class `UE::ChooserEditor::IChooserTableWidgetInterface`  
`class IChooserTableWidgetInterface`  
_L22-27_
- L25 _public function_ `virtual ~IChooserTableWidgetInterface()`
- L26 _public prototype_ `virtual void OpenObject(UObject* Object) = 0;`

#### class `UE::ChooserEditor::FObjectChooserWidgetFactories`  
`class FObjectChooserWidgetFactories`  
_L36-70_
- L40 _public prototype_ `static TSharedPtr<SWidget> CreateWidget(bool bReadOnly, UObject* TransactionObject, UScriptStruct* DataBaseType, FInstancedStruct* Data, UClass* ResultBaseClass, FChooserWidgetValueChanged ValueChanged = FChooserWidgetValueChanged(), IChooserTableWidgetInterface* ChooserWidgetInterface = nullptr, FText NullValueDisplayText = FText());`
- L43 _public prototype_ `static TSharedPtr<SWidget> CreateWidget(bool ReadOnly, UObject* TransactionObject, void* Value, const UStruct* ValueType, UClass* ResultBaseClass, FChooserWidgetValueChanged ValueChanged = FChooserWidgetValueChanged(), IChooserTableWidgetInterface* ChooserWidgetInterface = nullptr);`
- L46 _public prototype_ `static TSharedPtr<SWidget> CreateWidget(bool ReadOnly, UObject* TransactionObject, const UScriptStruct* BaseType, void* Value, const UStruct* ValueType, UClass* ResultBaseClass, const FOnStructPicked& CreateClassCallback, TSharedPtr<SBorder>* InnerWidget = nullptr, FChooserWidgetValueChanged ValueChanged = FChooserWidgetValueChanged(), IChooserTableWidgetInterface* ChooserWidgetInterface = nullptr, FText NullValueDisplayText = FText());`
- L51 _public prototype_ `static TSharedPtr<SWidget> CreateColumnWidget(FChooserColumnBase* Column, const UStruct* ColumnType, UChooserTable* Chooser, int Row);` — todo: chooser should be a UObject
- L53 _public prototype_ `static void RegisterWidgets();`
- L55 _public prototype_ `static void RegisterWidgetCreator(const UStruct* Type, FNewChooserWidgetCreator Creator);`
- L56 _public prototype_ `static void RegisterWidgetCreator(const UStruct* Type, FChooserWidgetCreator Creator);`
- L57 _public prototype_ `static void RegisterColumnWidgetCreator(const UStruct* ColumnType, FColumnWidgetCreator Creator);`
- L59 _public prototype_ `static void RegisterParameterMenuCreator(const UStruct* ParameterBaseType, FParameterMenuCreator);`
- L60 _public prototype_ `static void CreateParametersMenu(const UStruct* ParameterBaseType, UObject* TransactionObject, const IHasContextClass* ContextOwner, FInstancedStruct* Parameter, FMenuBuilder& MenuBuilder, TFunction<void()> BindingChanged);`
- L63 _private member_ `static TMap<const UStruct*, FColumnWidgetCreator> ColumnWidgetCreators;`
- L64 _private member_ `static TMap<const UStruct*, FChooserWidgetCreator> ChooserWidgetCreators;`
- L65 _private member_ `static TMap<const UStruct*, FNewChooserWidgetCreator> NewChooserWidgetCreators;`
- L67 _private typedef_ `typedef TMultiMap<const UStruct*, FParameterMenuCreator> FParameterMenuCreatorMap;`
- L69 _private member_ `static FParameterMenuCreatorMap ParameterMenuCreators;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHOOSEREDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L19 _enumerator_ `enum { ColumnWidget_SpecialIndex_Header = -1 }; enum { ColumnWidget_SpecialIndex_Fallback = -2 }; class IChooserTableWidgetInterface { public: virtual ~IChooserTableWidgetInterface() {} virtual void OpenObject(UObject* Object) = 0;` (scope `UE::ChooserEditor::__anon4ed483440103`)
- L20 _enumerator_ `enum { ColumnWidget_SpecialIndex_Fallback = -2 }; class IChooserTableWidgetInterface { public: virtual ~IChooserTableWidgetInterface() {} virtual void OpenObject(UObject* Object) = 0; };` (scope `UE::ChooserEditor::__anon4ed483440203`)
- L29 _delegate_ `DECLARE_DELEGATE(FChooserWidgetValueChanged) typedef TFunction<TSharedRef<SWidget>(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged, IChooserTableWidgetInterface* ChooserTableWidgetInterface)> FNewChooserWidgetCreator;`
- L30 _typedef_ `typedef TFunction<TSharedRef<SWidget>(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged, IChooserTableWidgetInterface* ChooserTableWidgetInterface)> FNewChooserWidgetCreator;` (scope `UE::ChooserEditor`)
- L31 _typedef_ `typedef TFunction<TSharedRef<SWidget>(bool bReadOnly, UObject* TransactionObject, void* Value, UClass* ResultBaseClass, FChooserWidgetValueChanged)> FChooserWidgetCreator;` (scope `UE::ChooserEditor`)
- L32 _typedef_ `typedef TFunction<TSharedRef<SWidget>(UChooserTable* Chooser, FChooserColumnBase* Column, int Row)> FColumnWidgetCreator;` (scope `UE::ChooserEditor`)
- L34 _typedef_ `typedef TFunction<void(UObject* TransactionObject, const IHasContextClass* ContextOwner, FInstancedStruct* Parameter, FMenuBuilder& MenuBuilder, TFunction<void()> BindingChanged)> FParameterMenuCreator;` (scope `UE::ChooserEditor`)

### `Plugins/Chooser/Source/ChooserEditor/Public/SPropertyAccessChainWidget.h` (Public)


#### class `UE::ChooserEditor::SPropertyAccessChainWidget`  
`class SPropertyAccessChainWidget : public SCompoundWidget`  
_L20-56_
- inherits: `SCompoundWidget`
- desc: Wrapper widget for Property access widget, which can update when the target Class changes
- L23 _public function_ `SLATE_BEGIN_ARGS(SPropertyAccessChainWidget)`
- L26 _public prototype_ `SLATE_ARGUMENT(IHasContextClass*, ContextClassOwner) SLATE_ARGUMENT(FString, TypeFilter);`
- L28 _public prototype_ `SLATE_ARGUMENT(FString, BindingColor);`
- L29 _public prototype_ `SLATE_ARGUMENT(bool, AllowFunctions);`
- L30 _public prototype_ `SLATE_EVENT(FOnAddBinding, OnAddBinding);`
- L31 _public prototype_ `SLATE_EVENT(FPropertyAccessChainChanged, OnValueChanged);`
- L32 _public prototype_ `SLATE_ATTRIBUTE(FChooserPropertyBinding*, PropertyBindingValue);`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs);`
- L37 _public prototype_ `virtual ~SPropertyAccessChainWidget();`
- L40 _public prototype_ `static void SetPropertyBinding(IHasContextClass* HasContext, const TArray<FBindingChainElement>& InBindingChain, FChooserPropertyBinding& OutPropertyBinding);` — Assign result from Property Access Widget to an FChooserPropertyBinding (Helper for OnAddBinding implementations)
- L43 _private prototype_ `TSharedRef<SWidget> CreatePropertyAccessWidget();`
- L44 _private prototype_ `void UpdateWidget();`
- L45 _private prototype_ `void ContextClassChanged();`
- L47 _private member_ `FString TypeFilter;`
- L48 _private member_ `FString AlternateTypeFilter;`
- L49 _private member_ `FString BindingColor;`
- L50 _private prototype_ `FDelegateHandle ContextClassChangedHandle();`
- L51 _private member_ `IHasContextClass* ContextClassOwner = nullptr;`
- L52 _private member_ `FOnAddBinding OnAddBinding;`
- L53 _private member_ `FPropertyAccessChainChanged OnValueChanged;`
- L54 _private member_ `TAttribute<FChooserPropertyBinding*> PropertyBindingValue;`
- L55 _private member_ `bool bAllowFunctions;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHOOSEREDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ChooserEditor` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE(FPropertyAccessChainChanged)`
- L58 _prototype_ `void CreatePropertyAccessMenus(const FString& TypeFilter, FOnAddBinding OnAddBinding, const IHasContextClass* ContextClassOwner, FInstancedStruct* Parameter, FMenuBuilder& MenuBuilder);` (scope `UE::ChooserEditor`)
- L65 _function_ `template <typename PropertyType> void CreatePropertyAccessMenus(const FString& TypeFilter, UObject* TransactionObject, const IHasContextClass* ContextClassOwner, FInstancedStruct* Parameter, FMenuBuilder& MenuBuilder, TFunction<void ()> BindingChanged)`
- L69 _function_ `` (scope `CreatePropertyAccessMenus`)
