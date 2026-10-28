# Plugins / DataLinkEditor

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor`
- headers: 18; symbols: 176
- symbol kinds: class=17, delegate=1, function=5, member=35, namespace=6, prototype=110, variable=2
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, DataLink, DataLinkEdGraph, Engine, GraphEditor, PropertyEditor, Slate, SlateCore, StructUtilsEditor, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/AssetDefinition_DataLinkGraph.h` (Private)


#### class `UAssetDefinition_DataLinkGraph`  
`class UAssetDefinition_DataLinkGraph : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/Compiler/DataLinkGraphCompiler.h` (Private)


#### class `FDataLinkGraphCompiler`  
`class FDataLinkGraphCompiler`  
_L18-56_
- desc: Compiles a data link graph's ed graph and writes its results to the runtime data of the data link graph
- L21 _public prototype_ `explicit FDataLinkGraphCompiler(UDataLinkGraph* InDataLinkGraph);`
- L23 _public prototype_ `UE::DataLink::EGraphCompileStatus Compile();`
- L26 _private prototype_ `void CleanExistingGraph();`
- L28 _private prototype_ `bool CompileNodes();`
- L30 _private prototype_ `bool CreateCompiledNodes();`
- L32 _private prototype_ `UDataLinkNode* CompileNode(UDataLinkNode* InTemplateNode);`
- L34 _private prototype_ `void LinkNodes();`
- L36 _private prototype_ `bool SetInputOutputNodes();`
- L38 _private prototype_ `void AddGraphEntryNodes(const UDataLinkNode* InNode);`
- L40 _private prototype_ `UDataLinkNode* FindCompiledNode(const UDataLinkEdNode* InEdNode) const;`
- L42 _private member_ `TObjectPtr<UDataLinkGraph> DataLinkGraph;`
- L44 _private member_ `TObjectPtr<UDataLinkEdGraph> DataLinkEdGraph;`
- L46 _private member_ `TObjectPtr<const UDataLinkEdNode> OutputEdNode;`
- L52 _private member_ `FName OutputPinName;` — Pin name of the output ed node connecting to the cosmetic output node Indicating that this pin is the pin that will be containing the graph output data
- L55 _private member_ `TMap<const UDataLinkEdNode*, UDataLinkNode*> EdToCompiledMap;` — Map of the Editor Node to its Compiled Node

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DataLink` (scope `UE`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/Compiler/DataLinkGraphCompilerTool.h` (Private)


#### class `FDataLinkGraphCompilerTool`  
`class FDataLinkGraphCompilerTool : public TSharedFromThis<FDataLinkGraphCompilerTool>`  
_L19-38_
- inherits: `TSharedFromThis<FDataLinkGraphCompilerTool>`
- L22 _public prototype_ `static void ExtendMenu(UToolMenu* InMenu);`
- L24 _public prototype_ `explicit FDataLinkGraphCompilerTool(UDataLinkGraphAssetEditor* InAssetEditor);`
- L26 _public prototype_ `void BindCommands(const TSharedRef<FUICommandList>& InCommandList);`
- L28 _public prototype_ `void Compile();`
- L31 _private prototype_ `static void ExtendDynamicCompilerSection(FToolMenuSection& InSection);`
- L33 _private prototype_ `FSlateIcon GetCompileIcon() const;`
- L35 _private member_ `TObjectPtr<UDataLinkGraphAssetEditor> AssetEditor;`
- L37 _private member_ `UE::DataLink::EGraphCompileStatus LastCompiledStatus;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DataLink` (scope `UE`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkEditor, Log, All);`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkEditorModule.h` (Private)


#### class `FDataLinkEditorModule`  
`class FDataLinkEditorModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public prototype_ `void RegisterDetailCustomizations();`
- L18 _public prototype_ `void UnregisterDetailCustomizations();`
- L20 _public member_ `TArray<FName> CustomizedTypes;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkEditorStyle.h` (Private)


#### class `FDataLinkEditorStyle`  
`class FDataLinkEditorStyle final : public FSlateStyleSet`  
_L7-15_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `static FDataLinkEditorStyle& Get();`
- L12 _public prototype_ `FDataLinkEditorStyle();`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkGraphAssetEditor.h` (Private)


#### class `UDataLinkGraphAssetEditor`  
`class UDataLinkGraphAssetEditor : public UAssetEditor`  
_L13-37_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- L18 _public prototype_ `void Initialize(UDataLinkGraph* InDataLinkGraph);`
- L20 _public prototype_ `TSharedPtr<FDataLinkGraphAssetToolkit> GetToolkit() const;`
- L22 _public prototype_ `TSharedPtr<FUICommandList> GetToolkitCommands() const;`
- L24 _public prototype_ `UDataLinkGraph* GetDataLinkGraph() const;`
- L26 _public prototype_ `UDataLinkEdGraph* GetDataLinkEdGraph() const;`
- L30 _protected prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;`
- L31 _protected prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L36 _private member_ `TObjectPtr<UDataLinkGraph> DataLinkGraph;` — `UPROPERTY()`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkGraphAssetToolkit.h` (Private)


#### class `FDataLinkGraphAssetToolkit`  
`class FDataLinkGraphAssetToolkit : public FBaseAssetToolkit`  
_L14-59_
- inherits: `FBaseAssetToolkit`
- L17 _public prototype_ `explicit FDataLinkGraphAssetToolkit(UDataLinkGraphAssetEditor* InAssetEditor);`
- L19 _public prototype_ `TSharedPtr<IDetailsView> GetDetailsView() const;`
- L22 _public prototype_ `virtual void RegisterToolbar() override;`
- L23 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& InMenuContext) override;`
- L24 _public prototype_ `virtual void CreateWidgets() override;`
- L25 _public prototype_ `virtual TSharedRef<IDetailsView> CreateDetailsView() override;`
- L26 _public prototype_ `virtual void PostInitAssetEditor() override;`
- L30 _public prototype_ `virtual void MapToolkitCommands() override;`
- L34 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L35 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L36 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L39 _public function_ `const FDataLinkGraphCompilerTool& GetCompilerTool() const`
- L44 _public function_ `const FDataLinkPreviewTool& GetPreviewTool() const`
- L50 _private prototype_ `void OnGraphChanged(const FEdGraphEditAction& InAction);`
- L52 _private member_ `TObjectPtr<UDataLinkGraphAssetEditor> AssetEditor;`
- L54 _private member_ `TSharedRef<FDataLinkGraphEditorTool> GraphTool;`
- L56 _private member_ `TSharedRef<FDataLinkGraphCompilerTool> CompilerTool;`
- L58 _private member_ `TSharedRef<FDataLinkPreviewTool> PreviewTool;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkGraphCommands.h` (Private)


#### class `FDataLinkGraphCommands`  
`class FDataLinkGraphCommands : public TCommands<FDataLinkGraphCommands>`  
_L7-25_
- inherits: `TCommands<FDataLinkGraphCommands>`
- L10 _public prototype_ `FDataLinkGraphCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> Compile;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> RunPreview;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> StopPreview;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> ClearPreviewOutput;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ClearPreviewCache;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkGraphEditorMenuContext.h` (Private)


#### class `UDataLinkGraphEditorMenuContext`  
`class UDataLinkGraphEditorMenuContext : public UObject, public IDataLinkEditorMenuContext`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UObject,IDataLinkEditorMenuContext`
- L19 _public prototype_ `virtual FConstStructView FindPreviewOutputData() const override;`
- L20 _public prototype_ `virtual FString GetAssetPath() const override;`
- L23 _public member_ `TWeakPtr<FDataLinkGraphAssetToolkit> ToolkitWeak;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DataLinkGraphFactory.h` (Private)


#### class `UDataLinkGraphFactory`  
`class UDataLinkGraphFactory : public UFactory`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _public prototype_ `UDataLinkGraphFactory();`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L19 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DetailsView/DataLinkInputDataCustomization.h` (Private)


#### class `FDataLinkInputDataCustomization`  
`class FDataLinkInputDataCustomization : public IPropertyTypeCustomization`  
_L7-27_
- inherits: `IPropertyTypeCustomization`
- L10 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L17 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L18 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L22 _protected prototype_ `FText GetInputDisplayName() const;` — Returns the current value of the input display name property handle
- L26 _private member_ `TSharedPtr<IPropertyHandle> DisplayNameHandle;` — Handle to the Input Data Display Name

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/DetailsView/DataLinkInstanceCustomization.h` (Private)


#### class `FDataLinkInstanceCustomization`  
`class FDataLinkInstanceCustomization : public IPropertyTypeCustomization`  
_L11-42_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(bool bInGenerateHeader)`
- L19 _public prototype_ `explicit FDataLinkInstanceCustomization(bool bInGenerateHeader);`
- L25 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L26 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L29 _protected prototype_ `void OnGraphCompiled(UDataLinkGraph* InDataLinkGraph);`
- L31 _protected prototype_ `UDataLinkGraph* GetDataLinkGraph() const;`
- L33 _protected prototype_ `TArray<FDataLinkInputData>* GetInputData() const;`
- L35 _protected prototype_ `void OnGraphChanged();`
- L36 _protected prototype_ `void UpdateInputData();`
- L38 _protected member_ `TSharedPtr<IPropertyHandle> DataLinkGraphHandle;`
- L39 _protected member_ `TSharedPtr<IPropertyHandle> InputDataHandle;`
- L41 _protected member_ `bool bGenerateHeader;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/Graph/DataLinkGraphEditorTool.h` (Private)


#### class `FDataLinkGraphEditorTool`  
`class FDataLinkGraphEditorTool : public TSharedFromThis<FDataLinkGraphEditorTool>`  
_L19-63_
- inherits: `TSharedFromThis<FDataLinkGraphEditorTool>`
- L22 _public member_ `static const FLazyName GraphEditorTabID;`
- L24 _public prototype_ `explicit FDataLinkGraphEditorTool(UDataLinkGraphAssetEditor* InAssetEditor);`
- L26 _public prototype_ `void BindCommands(const TSharedRef<FUICommandList>& InCommandList);`
- L28 _public prototype_ `void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager, const TSharedPtr<FWorkspaceItem>& InAssetEditorTabsCategory);`
- L29 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager);`
- L31 _public prototype_ `void CreateWidgets();`
- L34 _protected prototype_ `void SelectAllNodes();`
- L36 _protected prototype_ `bool CanDeleteSelectedNodes() const;`
- L37 _protected prototype_ `void DeleteSelectedNodes();`
- L39 _protected prototype_ `bool CanCopySelectedNodes() const;`
- L40 _protected prototype_ `void CopySelectedNodes();`
- L42 _protected prototype_ `bool CanCutSelectedNodes() const;`
- L43 _protected prototype_ `void CutSelectedNodes();`
- L45 _protected prototype_ `bool CanPasteNodes() const;`
- L46 _protected prototype_ `void PasteNodes();`
- L48 _protected prototype_ `bool CanDuplicateSelectedNodes() const;`
- L49 _protected prototype_ `void DuplicateSelectedNodes();`
- L52 _private prototype_ `TSet<UObject*> CopySelectedNodesInternal();`
- L54 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& InTabArgs) const;`
- L56 _private prototype_ `void OnSelectedNodesChanged(const TSet<UObject*>& InSelectionSet);`
- L58 _private member_ `TObjectPtr<UDataLinkGraphAssetEditor> AssetEditor;`
- L60 _private member_ `TSharedRef<FUICommandList> GraphEditorCommands;`
- L62 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/Preview/DataLinkPreviewData.h` (Private)


#### class `UDataLinkPreviewData`  
`class UDataLinkPreviewData : public UObject`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public member_ `FDataLinkInstance DataLinkInstance;` — `UPROPERTY(EditAnywhere, Category="Input Data")`
- L20 _public member_ `FInstancedStruct OutputData;` — `UPROPERTY(VisibleAnywhere, Category="Output Data", meta=(StructTypeConst))`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Private/Preview/DataLinkPreviewTool.h` (Private)


#### class `FDataLinkPreviewTool`  
`class FDataLinkPreviewTool : public FGCObject, public TSharedFromThis<FDataLinkPreviewTool>`  
_L23-88_
- inherits: `FGCObject,TSharedFromThis<FDataLinkPreviewTool>`
- desc: Handles executing a preview of the Data Link Graph with input data from within the Editor itself
- L26 _public member_ `static const FLazyName PreviewTabID;`
- L28 _public prototype_ `explicit FDataLinkPreviewTool(UDataLinkGraphAssetEditor* InAssetEditor);`
- L30 _public prototype_ `void Initialize();`
- L32 _public prototype_ `void BindCommands(const TSharedRef<FUICommandList>& InCommandList);`
- L34 _public prototype_ `void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager, const TSharedPtr<FWorkspaceItem>& InAssetEditorTabsCategory);`
- L36 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager);`
- L38 _public prototype_ `void CreateWidgets();`
- L40 _public function_ `const UDataLinkPreviewData* GetPreviewData() const`
- L47 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L48 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L52 _private prototype_ `bool CanRunPreview() const;`
- L53 _private prototype_ `void RunPreview();`
- L55 _private prototype_ `bool CanStopPreview() const;`
- L56 _private prototype_ `void StopPreview();`
- L58 _private prototype_ `bool CanClearOutput() const;`
- L59 _private prototype_ `void ClearOutput();`
- L61 _private prototype_ `bool CanClearCache() const;`
- L62 _private prototype_ `void ClearCache();`
- L64 _private prototype_ `void OnPreviewOutputData(const FDataLinkExecutor& InExecutor, FConstStructView InOutputDataView);`
- L66 _private prototype_ `void RegisterToolbar();`
- L68 _private prototype_ `void CreateDetailsView();`
- L70 _private prototype_ `TSharedRef<SWidget> CreateContentWidget() const;`
- L72 _private prototype_ `TSharedRef<SWidget> CreateToolbar() const;`
- L74 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& InTabArgs) const;`
- L76 _private member_ `TObjectPtr<UDataLinkGraphAssetEditor> AssetEditor;`
- L78 _private member_ `TSharedPtr<IDetailsView> PreviewDetails;`
- L81 _private member_ `TObjectPtr<UDataLinkPreviewData> PreviewData;` — Preview object holding the input and output data
- L84 _private member_ `TSharedPtr<FDataLinkExecutor> Executor;` — Current Executor taking place
- L87 _private member_ `TSharedPtr<FDataLinkSink> Sink;` — Data Sink to use for Executor

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Public/DataLinkEditorNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DataLinkEditor` (scope `UE`)
- L9 _variable_ `const FLazyName PreviewToolbarName(TEXT("Data` (scope `UE::DataLinkEditor`)
- L10 _variable_ `const FLazyName PreviewSectionName(TEXT("Prev` (scope `UE::DataLinkEditor`)

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEditor/Public/IDataLinkEditorMenuContext.h` (Public)


#### class `UDataLinkEditorMenuContext`  
`class UDataLinkEditorMenuContext : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IDataLinkEditorMenuContext`  
`class IDataLinkEditorMenuContext`  
_L16-29_
- L25 _public prototype_ `virtual FConstStructView FindPreviewOutputData() const = 0;` — Finds the latest preview output data. Could return invalid struct. @note Existing views can be invalidated at any time by the user so handle these views as short-lived!
- L28 _public prototype_ `virtual FString GetAssetPath() const = 0;` — Retrieves the asset path of the currently edited asset
