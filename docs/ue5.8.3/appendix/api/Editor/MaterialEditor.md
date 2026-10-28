# Editor / MaterialEditor

- module root: `Source/Editor/MaterialEditor`
- headers: 52; symbols: 2528
- symbol kinds: class=98, delegate=16, enum=12, enumerator=71, externvar=2, function=271, macro=18, member=672, namespace=2, prototype=1319, struct=41, typedef=6
- DynamicallyLoadedModuleNames: AssetTools, ClassViewer, SceneOutliner, WorkspaceMenuStructure
- PrivateDependencyModuleNames: AdvancedPreviewScene, AppFramework, ApplicationCore, AssetRegistry, ContentBrowser, ContentBrowserData, Core, CoreUObject, EditorFramework, EditorStyle, EditorSubsystem, Engine, GraphEditor, InputCore, Kismet, Landscape, MainFrame, MaterialUtilities, PhysicsCore, Projects, PropertyEditor, RHI, RenderCore, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: AssetTools, EditorWidgets, MessageLog

### `Source/Editor/MaterialEditor/Internal/DiffTool/MaterialDiffPanel.h` (Internal)


#### struct `FMaterialDiffPanel`  
`struct FMaterialDiffPanel : public FGCObject`  
_L25-111_
- inherits: `FGCObject`
- desc: Panel used to display the MaterialGraph
- L28 _public prototype_ `void GeneratePanel(UEdGraph* NewGraph, UEdGraph* OldGraph);` — Generate a panel for NewGraph diffed against OldGraph
- L31 _public prototype_ `void GeneratePanel(UEdGraph* Graph, TSharedPtr<TArray<FDiffSingleResult>> DiffResults, TAttribute<int32> FocusedDiffResult);` — Generate a panel that displays the Graph and reflects the items in the DiffResults
- L34 _public prototype_ `void CopySelectedNodes();` — Called when user hits keyboard shortcut to copy nodes
- L37 _public prototype_ `FGraphPanelSelectionSet GetSelectedNodes() const;` — Gets whatever nodes are selected in the Graph Editor
- L40 _public prototype_ `bool CanCopyNodes() const;` — Can user copy any of the selected nodes?
- L42 _public prototype_ `void SelectDownstreamNodes() const;`
- L43 _public prototype_ `void SelectUpstreamNodes() const;`
- L45 _public prototype_ `void OnPreviewNode();`
- L48 _public prototype_ `void FocusDiff(UEdGraphPin& Pin);` — Functions used to focus/find a particular change in a diff result
- L49 _public prototype_ `void FocusDiff(UEdGraphNode& Node);`
- L51 _public prototype_ `TSharedRef<SWidget> GetMaterialNodeDetailsViewWidget() const;`
- L53 _public prototype_ `void SetViewportToDisplay();`
- L55 _public prototype_ `TSharedRef<SWidget> GetViewportToDisplay() const;`
- L57 _public prototype_ `void SetViewportVisibility(bool bShowViewport);`
- L59 _public prototype_ `void SetPreviewExpression(UMaterialExpression* NewPreviewExpression);`
- L61 _public prototype_ `void SetPreviewMaterial(UMaterialInterface* InMaterialInterface) const;`
- L63 _public prototype_ `void UpdatePreviewMaterial() const;`
- L66 _public member_ `TObjectPtr<UMaterialGraph> MaterialGraph = nullptr;` — The MaterialGraph we are showing
- L69 _public member_ `TSharedPtr<SBox> GraphEditorBox;` — The box around the graph editor, used to change the content when new graphs are set
- L72 _public member_ `TSharedPtr<IDetailsView> MaterialNodeDetailsView;` — The details view associated with the MaterialNode of the focused MaterialGraphNode
- L74 _public member_ `TSharedPtr<SMaterialEditor3DPreviewViewport> Preview3DViewport;`
- L76 _public member_ `TSharedPtr<SMaterialEditorUIPreviewViewport> Preview2DViewport;`
- L78 _public member_ `TObjectPtr<UMaterial> ExpressionPreviewMaterial = nullptr;`
- L80 _public member_ `TObjectPtr<UMaterialExpression> PreviewExpression = nullptr;`
- L83 _public member_ `TWeakPtr<SGraphEditor> GraphEditor;` — The graph editor which does the work of displaying the graph
- L86 _public member_ `FRevisionInfo RevisionInfo;` — Revision information for this Material
- L89 _public member_ `bool bShowAssetName = true;` — True if we should show a name identifying which asset this panel is displaying
- L92 _public member_ `TSharedPtr<SWidget> OverlayGraphRevisionInfo;` — The widget that contains the revision info in graph mode
- L95 _public member_ `FPropertyPath PropertyToFocus;` — The property that we will highlight in MaterialNodeDetailsView
- L98 _public member_ `TObjectPtr<UMaterialInstance> MaterialInstance = nullptr;` — The material instance being diffed (nullptr when diffing base materials)
- L101 _public member_ `TObjectPtr<UMaterialEditorInstanceConstant> EditorProxy = nullptr;` — Editor proxy used to display all parameter types including static switches (nullptr when diffing base materials)
- L104 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L105 _public prototype_ `virtual FString GetReferencerName() const override;`
- L110 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this diff panel

### `Source/Editor/MaterialEditor/Internal/DiffTool/Widgets/SMaterialDiff.h` (Internal)


#### struct `FMaterialDiffResultItem`  
`struct FMaterialDiffResultItem : public FDiffResultItem`  
_L26-30_
- inherits: `FDiffResultItem`
- L29 _public member_ `FPropertyPath Property;` — Not empty if the DiffResultItem is a property changed

#### class `SMaterialDiff`  
`class SMaterialDiff : public SCompoundWidget`  
_L33-206_
- inherits: `SCompoundWidget`
- desc: Visual Diff between two Material Graphs
- L36 _public function_ `SLATE_BEGIN_ARGS(SMaterialDiff)`
- L37 _public prototype_ `SLATE_ARGUMENT(TObjectPtr<UMaterialGraph>, OldMaterialGraph) SLATE_ARGUMENT(TObjectPtr<UMaterialGraph>, NewMaterialGraph) SLATE_ARGUMENT(FRevisionInfo, OldRevision) SLATE_ARGUMENT(FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_ARGUMENT(TObjectPtr<UMaterialInstance>, OldMaterialInstance) SLATE_ARGUMENT(TObjectPtr<UMaterialInstance>, NewMaterialInstance) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L51 _public prototype_ `void OnGraphChanged(FMaterialToDiff* Diff);` — Called when a new Graph is clicked on by user
- L54 _public prototype_ `void OnGraphSelectionChanged(TSharedPtr<FMaterialToDiff> Item, ESelectInfo::Type SelectionType);` — Called when user clicks on a new graph list item
- L57 _public prototype_ `void OnDiffListSelectionChanged(TSharedPtr<FMaterialDiffResultItem> TheDiff);` — Called when user clicks on an entry in the listview of differences
- L60 _public prototype_ `static TSharedRef<SWidget> DefaultEmptyPanel();` — Helper function for generating an empty widget
- L63 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow(FText WindowTitle, TObjectPtr<UMaterialGraph> OldMaterialGraph, TObjectPtr<UMaterialGraph> NewMaterialGraph, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision);` — Helper function to create a window that holds a diff widget
- L66 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow(TObjectPtr<UMaterialGraph> OldMaterialGraph, TObjectPtr<UMaterialGraph> NewMaterialGraph, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision, const UClass* ObjectClass);` — Helper function to create a window that holds a diff widget (default window title)
- L69 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow(FText WindowTitle, TObjectPtr<UMaterialInstance> OldMaterialInstance, TObjectPtr<UMaterialInstance> NewMaterialInstance, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision);` — Create a diff window for two material instances
- L72 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow(TObjectPtr<UMaterialInstance> OldMaterialInstance, TObjectPtr<UMaterialInstance> NewMaterialInstance, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision, const UClass* ObjectClass);` — Create a diff window for two material instances (default window title)
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWindowClosedEvent, TSharedRef<SMaterialDiff>) FOnWindowClosedEvent OnWindowClosedEvent;`
- L79 _protected prototype_ `void NextDiff();` — Called when user clicks button to go to next difference
- L82 _protected prototype_ `void PrevDiff();` — Called when user clicks button to go to prev difference
- L85 _protected prototype_ `bool HasNextDiff() const;` — Called to determine whether we have a list of differences to cycle through
- L86 _protected prototype_ `bool HasPrevDiff() const;`
- L89 _protected prototype_ `void ToggleViewport();` — User toggles the option to show/hide preview viewports
- L92 _protected prototype_ `FSlateIcon GetViewportImage() const;` — Get the image to show for the toggle viewport option
- L95 _protected prototype_ `FMaterialToDiff* FindGraphToDiffEntry(const FString& GraphPath);` — Find the FMaterialToDiff that displays the graph with GraphPath relative path
- L98 _protected prototype_ `void FocusOnMaterialGraphRevisions(FMaterialToDiff* Diff);` — Bring these revisions of graph into focus on main display
- L101 _protected prototype_ `void OnToggleLockView();` — User toggles the option to lock the views between the two material graphs
- L104 _protected prototype_ `void OnToggleSplitViewMode();` — User toggles the option to change the split view mode betwwen vertical and horizontal
- L107 _protected prototype_ `FSlateIcon GetLockViewImage() const;` — Get the image to show for the toggle lock option
- L110 _protected prototype_ `FSlateIcon GetSplitViewModeImage() const;` — Get the image to show for the toggle split view mode option
- L113 _protected prototype_ `void ResetGraphEditors();` — Reset the graph editor, called when user switches graphs to display
- L116 _protected member_ `TSharedPtr<FMaterialToDiff> MaterialGraphToDiff;` — Material Graph to diff, is added to panel
- L119 _protected prototype_ `FMaterialDiffPanel& GetDiffPanelForNode(UEdGraphNode& Node);` — Get Graph editor associated with this Graph
- L122 _protected prototype_ `void HandleGraphChanged(const FString& GraphPath);` — Event handler that updates the graph view when user selects a new graph
- L125 _protected prototype_ `void GenerateDifferencesList();` — Function used to generate the list of differences and the widgets needed to calculate that list
- L128 _protected prototype_ `void OnCloseAssetEditor(UObject* Asset, EAssetEditorCloseReason CloseReason);` — Called when editor may need to be closed
- L140 _protected prototype_ `FMaterialGraphDiffControl GenerateMaterialGraphPanel();`
- L142 _protected prototype_ `TSharedRef<SOverlay> GenerateMaterialGraphWidgetForPanel(FMaterialDiffPanel& OutDiffPanel) const;`
- L143 _protected prototype_ `TSharedRef<SBox> GenerateRevisionInfoWidgetForPanel(TSharedPtr<SWidget>& OutGeneratedWidget, const FText& InRevisionText) const;`
- L146 _protected prototype_ `void SetCurrentMode(FName NewMode);` — Accessor and event handler for toggling between diff view modes - only GraphMode for now:
- L148 _protected function_ `FName GetCurrentMode() const`
- L150 _protected prototype_ `void OnModeChanged(const FName& InNewViewMode) const;`
- L152 _protected prototype_ `void UpdateTopSectionVisibility(const FName& InNewViewMode) const;`
- L154 _protected prototype_ `void SetCurrentWidgetIndex(int32 Index);`
- L155 _protected prototype_ `int32 GetCurrentWidgetIndex() const;`
- L157 _protected member_ `FName CurrentMode;`
- L159 _protected member_ `FMaterialDiffPanel PanelOld, PanelNew;`
- L159 _protected member_ `FMaterialDiffPanel PanelOld, PanelNew;`
- L162 _protected member_ `bool bLockViews = true;` — If the two views should be locked
- L165 _protected member_ `bool bVerticalSplitGraphMode = true;` — If the view on Graph Mode should be divided vertically
- L168 _protected member_ `bool bShowViewport = true;` — If the preview Viewports should be shown
- L171 _protected member_ `bool bShowGraphDiff = true;` — Should we show the graph diff?
- L174 _protected member_ `TSharedPtr<SBox> ModeContents;` — Contents widget that we swap when mode changes (defaults, components, etc)
- L176 _protected member_ `TSharedPtr<SSplitter> TopRevisionInfoWidget;`
- L178 _protected member_ `TSharedPtr<SSplitter> DiffGraphSplitter;`
- L180 _protected member_ `TSharedPtr<SSplitter> GraphToolBarWidget;`
- L182 _protected member_ `TSharedPtr<SWidgetSwitcher> WidgetSwitcher;`
- L184 _protected member_ `int32 CurrentWidgetIndex = 0;`
- L187 _protected member_ `TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>> PrimaryDifferencesList;` — Tree of differences collected across all panels:
- L190 _protected member_ `TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>> RealDifferences;` — List of all differences, cached so that we can iterate only the differences and not labels, etc:
- L193 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> DifferencesTreeView;` — Tree view that displays the differences, cached for the buttons that iterate the differences:
- L196 _protected member_ `TMap<FName, FMaterialGraphDiffControl> ModePanels;` — Stored references to widgets used to display various parts of a material, from the mode name
- L199 _protected member_ `TWeakPtr<SWindow> WeakParentWindow;` — A pointer to the window holding this
- L201 _protected member_ `FDelegateHandle AssetEditorCloseDelegate;`
- L205 _private prototype_ `void AddMaterialInstanceDetailCustomization(const TSharedRef<IDetailsView>& DetailsView);` — Registers FMaterialInstanceParameterDetails customization on instance diff details views

#### struct `SMaterialDiff::FMaterialGraphDiffControl`  
`struct FMaterialGraphDiffControl`  
_L130-138_
- L132 _public function_ `FMaterialGraphDiffControl() : Widget(), DiffControl(nullptr)`
- L136 _public member_ `TSharedPtr<SWidget> Widget;`
- L137 _public member_ `TSharedPtr<IDiffControl> DiffControl;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MATERIALEDITOR_API`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWindowClosedEvent, TSharedRef<SMaterialDiff>) FOnWindowClosedEvent OnWindowClosedEvent;`

### `Source/Editor/MaterialEditor/Private/DiffTool/MaterialToDiff.h` (Private)


#### struct `FMaterialToDiff`  
`struct FMaterialToDiff : public TSharedFromThis<FMaterialToDiff>, IDiffControl`  
_L16-59_
- inherits: `TSharedFromThis<FMaterialToDiff>,IDiffControl`
- desc: Category list item for a MaterialGraph
- L18 _public prototype_ `FMaterialToDiff(SMaterialDiff* DiffWidget, UMaterialGraph* OldGraph, UMaterialGraph* NewGraph, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision);`
- L22 _public prototype_ `virtual void GenerateTreeEntries(TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& OutTreeEntries, TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& OutRealDifferences) override;` — Add widgets to the differences tree
- L25 _public prototype_ `UMaterialGraph* GetOldGraph() const;` — Get old(left) graph
- L28 _public prototype_ `UMaterialGraph* GetNewGraph() const;` — Get new(right) graph
- L31 _public member_ `TArray<TSharedPtr<FMaterialDiffResultItem>> DiffListSource;` — Source for list view
- L32 _public member_ `TSharedPtr<TArray<FDiffSingleResult>> FoundDiffs;`
- L35 _public member_ `int32 RealDifferencesStartIndex = INDEX_NONE;` — Index of the first item in RealDifferences that was generated by this graph
- L39 _private prototype_ `FText GetToolTip();` — Get tooltip for category
- L42 _private prototype_ `TSharedRef<SWidget> GenerateCategoryWidget();` — Generate Widget for category list
- L45 _private prototype_ `void BuildDiffSourceArray();` — Build up the Diff Source Array
- L48 _private member_ `SMaterialDiff* DiffWidget;` — Diff widget
- L51 _private member_ `UMaterialGraph* OldGraph;` — The old graph(left)
- L54 _private member_ `UMaterialGraph* NewGraph;` — The new graph(right)
- L57 _private member_ `FRevisionInfo OldRevision;` — Description of Old and New graph
- L58 _private member_ `FRevisionInfo NewRevision;`

### `Source/Editor/MaterialEditor/Private/DiffTool/Widgets/SMaterialRevisionMenu.h` (Private)


#### class `SMaterialRevisionMenu`  
`class SMaterialRevisionMenu : public SCompoundWidget`  
_L19-65_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SMaterialRevisionMenu) : _bIncludeLocalRevision(false)`
- L25 _public prototype_ `SLATE_ARGUMENT(bool, bIncludeLocalRevision) SLATE_EVENT(FOnRevisionSelected, OnRevisionSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UObject const* MaterialObj);`
- L30 _public prototype_ `virtual ~SMaterialRevisionMenu();`
- L33 _public prototype_ `static void MakeDiffMenu(UToolMenu* Menu);` — helper function to add the diff menu to a UToolMenu:
- L37 _private prototype_ `EVisibility GetInProgressVisibility() const;` — Delegate used to determine the visibility 'in progress' widgets
- L40 _private prototype_ `EVisibility GetCancelButtonVisibility() const;` — Delegate used to determine the visibility of the cancel button
- L43 _private prototype_ `FReply OnCancelButtonClicked() const;` — Delegate used to cancel a source control operation in progress
- L46 _private prototype_ `void OnSourceControlQueryComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Callback for when the source control operation is complete
- L49 _private member_ `bool bIncludeLocalRevision;` — Whether or not we should include the local revision to the menu
- L52 _private member_ `FOnRevisionSelected OnRevisionSelected;` — Called when we select one Revision from the list in the menu
- L55 _private member_ `FString Filename;` — The name of the file we want revision info for
- L58 _private member_ `TSharedPtr<SVerticalBox> MenuBox;` — The box we are using to display our menu
- L61 _private member_ `TSharedPtr<FUpdateStatus, ESPMode::ThreadSafe> SourceControlQueryOp;` — The source control operation in progress
- L64 _private member_ `uint32 SourceControlQueryState;` — The state of the SCC query

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRevisionSelected, const FRevisionInfo&) public : SLATE_BEGIN_ARGS(SMaterialRevisionMenu) : _bIncludeLocalRevision(false) {} SLATE_ARGUMENT(bool, bIncludeLocalRevision) SLATE_EVENT(FOnRevisionSelected, OnRevisionSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UObject const* MaterialObj);`

### `Source/Editor/MaterialEditor/Private/MaterialEditor.h` (Private)


#### class `FMatExpressionPreview`  
`class FMatExpressionPreview : public FEditorMaterialResourceBase, public FMaterialRenderProxy`  
_L57-185_
- inherits: `FEditorMaterialResourceBase,FMaterialRenderProxy`
- desc: Class for rendering previews of material expressions in the material editor's linked object viewport.
- L60 _public prototype_ `FMatExpressionPreview();`
- L61 _public prototype_ `FMatExpressionPreview(UMaterialExpression* InExpression);`
- L63 _public prototype_ `virtual ~FMatExpressionPreview();`
- L65 _public function_ `virtual bool PrepareDestroy_GameThread() override`
- L71 _public function_ `virtual void PrepareDestroy_RenderThread() override`
- L77 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L88 _public prototype_ `virtual bool ShouldCache(const FShaderType* ShaderType, const FVertexFactoryType* VertexFactoryType) const override;` — Should the shader for this material with the given platform, shader type and vertex factory type combination be compiled @param ShaderType	Which shader is being compiled @param VertexFactory	Which vertex factory is being compiled (can be NULL) @return true if the shader should be compiled
- L92 _public function_ `virtual const FMaterial* GetMaterialNoFallback(ERHIFeatureLevel::Type InFeatureLevel) const override` — FMaterialRenderProxy interface.
- L101 _public function_ `virtual const FMaterialRenderProxy* GetFallback(ERHIFeatureLevel::Type InFeatureLevel) const override`
- L106 _public function_ `virtual bool GetParameterValue(EMaterialParameterType Type, const FHashedMaterialParameterInfo& ParameterInfo, FMaterialParameterValue& OutValue, const FMaterialRenderContext& Context) const override`
- L117 _public prototype_ `virtual int32 CompilePropertyAndSetMaterialProperty(EMaterialProperty Property, FMaterialCompiler* Compiler, EShaderFrequency OverrideShaderFrequency, bool bUsePreviousFrameTime) const override;` — Entry point for compiling a specific material property.  This must call SetMaterialProperty.
- L119 _public function_ `virtual UMaterialExpression* GetMaterialGraphNodePreviewExpression() const override`
- L121 _public function_ `virtual EMaterialDomain GetMaterialDomain() const override`
- L122 _public function_ `virtual FString GetMaterialUsageDescription() const override`
- L123 _public function_ `virtual bool IsPreview() const override`
- L124 _public function_ `virtual bool IsTwoSided() const override`
- L125 _public function_ `virtual bool IsThinSurface() const override`
- L126 _public function_ `virtual bool IsDitheredLODTransition() const override`
- L127 _public function_ `virtual bool IsLightFunction() const override`
- L128 _public function_ `virtual bool IsDeferredDecal() const override`
- L129 _public function_ `virtual bool IsUIMaterial() const override`
- L130 _public function_ `virtual bool IsPostProcessMaterial() const override`
- L131 _public function_ `virtual bool IsVolumetricPrimitive() const override`
- L132 _public function_ `virtual bool IsSpecialEngineMaterial() const override`
- L133 _public function_ `virtual bool IsWireframe() const override`
- L134 _public function_ `virtual bool IsMasked() const override`
- L135 _public function_ `virtual enum EBlendMode GetBlendMode() const override`
- L136 _public function_ `virtual bool GetRootNodeOverridesDefaultRefraction()const override`
- L137 _public function_ `virtual FMaterialShadingModelField GetShadingModels() const override`
- L138 _public function_ `virtual bool IsShadingModelFromMaterialExpression() const override`
- L139 _public function_ `virtual float GetOpacityMaskClipValue() const override`
- L140 _public function_ `virtual bool GetCastDynamicShadowAsMasked() const override`
- L141 _public function_ `virtual FString GetFriendlyName() const override`
- L145 _public function_ `virtual bool IsPersistent() const override` — Should shaders compiled for this material be saved to disk?
- L146 _public function_ `virtual FGuid GetMaterialId() const override`
- L147 _public function_ `const UMaterialExpression* GetExpression() const`
- L153 _public prototype_ `virtual UMaterialInterface* GetMaterialInterface() const override;` — This material interface is solely needed for the translator to be able to parse the graph for the Substrate tree.
- L155 _public prototype_ `virtual void NotifyCompilationFinished() override;`
- L156 _public prototype_ `virtual bool IsUsingNewHLSLGenerator() const override;`
- L163 _public function_ `virtual void GatherExpressionsForCustomInterpolators(TArray<UMaterialExpression*>& OutExpressions) const override`
- L175 _public prototype_ `virtual bool CheckInValidStateForCompilation(class FMaterialCompiler* Compiler) const override;` — Checks that no pre-compilation errors have been detected and if so it reports them using specified compiler. @return whether no errors occurred.
- L177 _public member_ `float UnrelatedNodesOpacity;`
- L179 _public function_ `int32 GetCompiledPreviewNumChannels() const`
- L182 _private member_ `TWeakObjectPtr<UMaterialExpression> Expression;`
- L183 _private member_ `FGuid Id;`
- L184 _private member_ `mutable int32 CompiledPreviewNumChannels = 0;`

#### struct `FMaterialExpression`  
`struct FMaterialExpression`  
_L188-199_
- desc: Wrapper for each material expression, including a trimmed name
- L190 _public member_ `FString Name;`
- L191 _public member_ `UClass* MaterialClass;`
- L192 _public member_ `FText CreationDescription;`
- L193 _public member_ `FText CreationName;`

#### struct `FCategorizedMaterialExpressionNode`  
`struct FCategorizedMaterialExpressionNode`  
_L202-206_
- desc: Static array of categorized material expression classes.
- L204 _public member_ `FText CategoryName;`
- L205 _public member_ `TArray<FMaterialExpression> MaterialExpressions;`

#### struct `FMaterialInfo`  
`struct FMaterialInfo`  
_L209-218_
- desc: Used to display material information, compile errors etc.
- L211 _public member_ `FString Text;`
- L212 _public member_ `FLinearColor Color;`
- L214 _public function_ `FMaterialInfo(const FString& InText, const FLinearColor& InColor) : Text(InText) , Color(InColor)`

#### class `FMaterialEditor`  
`class FMaterialEditor : public IMaterialEditor, public FGCObject, public FTickableGameObject, public FEditorUndoClient, public FNotifyHook`  
_L223-1186_
- inherits: `IMaterialEditor,FGCObject,FTickableGameObject,FEditorUndoClient,FNotifyHook`
- desc: Material Editor class
- L227 _public prototype_ `void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);` — @todo This is a hack for now until we reconcile the default toolbar with application modes
- L228 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L229 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L232 _public prototype_ `void InitEditorForMaterial(UMaterial* InMaterial);` — Initializes the editor to use a material. Should be the first thing called.
- L235 _public prototype_ `void InitEditorForMaterialFunction(UMaterialFunction* InMaterialFunction);` — Initializes the editor to use a material function. Should be the first thing called.
- L244 _public prototype_ `void InitMaterialEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit );` — Edits the specified material object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit			The material or material function to edit
- L247 _public prototype_ `FMaterialEditor();` — Constructor
- L249 _public prototype_ `virtual ~FMaterialEditor();`
- L252 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L253 _public function_ `virtual FString GetReferencerName() const override`
- L259 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L260 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L261 _public prototype_ `virtual FText GetToolkitName() const override;`
- L262 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L263 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L264 _public prototype_ `virtual void InitToolMenuContext(struct FToolMenuContext& MenuContext) override;`
- L268 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L274 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — @return Returns the color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode.
- L277 _public prototype_ `virtual UMaterialInterface* GetMaterialInterface() const override;` — The material instance applied to the preview mesh.
- L282 _public prototype_ `virtual void DrawMessages( FViewport* Viewport, FCanvas* Canvas ) override;` — Draws messages on the specified viewport and canvas.
- L287 _public prototype_ `void RecenterEditor();` — Recenter the editor to either the material inputs or the first material function output
- L290 _public prototype_ `bool SetPreviewAsset(UObject* InAsset);` — Passes instructions to the preview viewport
- L291 _public prototype_ `bool SetPreviewAssetByName(const TCHAR* InAssetName);`
- L292 _public prototype_ `void SetPreviewMaterial(UMaterialInterface* InMaterialInterface);`
- L297 _public prototype_ `void RefreshPreviewViewport();` — Refreshes the viewport containing the preview mesh.
- L300 _public prototype_ `void UpdatePreviewCustomPrimitiveData();` — Pushes the currently set custom primitive data to the preview mesh component.
- L303 _public prototype_ `void RegenerateCodeView(bool bForce=false);` — Regenerates the code view widget with new text
- L308 _public prototype_ `void UpdatePreviewMaterial(bool bForce=false);` — Recompiles the material used in the preview window.
- L314 _public prototype_ `bool UpdateOriginalMaterial();` — Updates the original material with the changes made in the editor @return true if the update was successful.  False if update was canceled (eg attempted to update Default Material with errors, which would cause a crash).
- L319 _public prototype_ `void UpdateMaterialInfoLog();` — Updates list of Material Info used to show stats
- L320 _public prototype_ `void UpdateMaterialPlatformStats();`
- L325 _public prototype_ `void UpdateGraphNodeStates();` — Updates flags on the Material Nodes to avoid expensive look up calls when rendering
- L336 _public prototype_ `bool UpdateGraphNodeState(UEdGraph* Graph, const FMaterialResource* ErrorMaterialResource, TArray<UMaterialExpression*>& VisibleExpressions, bool bShowAllNodes);` — Updates flags on the Material Nodes for a single graph and it's subgraphs. @param	Graph					Material graph to update @param	ErrorMaterialResource	Material Resource containing known errors to draw for graph @param	VisibleExpressions		List of expressions that should be visible (As in not grayed out / disabled). @param	bShowAllNodes           True implies all nodes should be visible. @return	True if we updated the error state of this material during graph update.
- L339 _public function_ `TSharedRef<class IDetailsView> GetDetailView() const` — Widget Accessors
- L341 _public prototype_ `virtual void UpdateDetailView() override;`
- L344 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject interface
- L346 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L351 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L356 _public function_ `virtual bool IsTickableInEditor() const override`
- L361 _public prototype_ `virtual TStatId GetStatId() const override;`
- L364 _public prototype_ `static void UpdateThumbnailInfoPreviewMesh(UMaterialInterface* MatInterface);` — Pushes the PreviewMesh assigned the the material instance to the thumbnail info
- L367 _public prototype_ `void SetPreviewExpression(UMaterialExpression* NewPreviewExpression);` — Sets the expression to be previewed.
- L370 _public prototype_ `void JumpToNode(const UEdGraphNode* Node);` — Pan the view to center on a particular node
- L373 _public prototype_ `virtual void OnGraphEditorFocused(const TSharedRef<class SGraphEditor>& InGraphEditor);` — Called when graph editor focus is changed
- L376 _public prototype_ `virtual void OnGraphEditorBackgrounded(const TSharedRef<SGraphEditor>& InGraphEditor);` — Called when the graph editor tab is backgrounded
- L379 _public prototype_ `bool FindOpenTabsContainingDocument(const UObject* DocumentID, TArray< TSharedPtr<SDockTab> >& Results);` — Finds any open tabs containing the specified document and adds them to the specified array; returns true if at least one is found
- L382 _public prototype_ `TSharedPtr<SDockTab> OpenDocument(const UObject* DocumentID, FDocumentTracker::EOpenDocumentCause Cause);` — Open workflow document tab
- L385 _public prototype_ `void CloseDocumentTab(const UObject* DocumentID);` — Close workflow document tab
- L388 _public prototype_ `virtual UMaterialExpression* CreateNewMaterialExpression(UClass* NewExpressionClass, const FVector2D& NodePos, bool bAutoSelect, bool bAutoAssignResource, const class UEdGraph* Graph = nullptr) override;` — IMaterial Editor Interface
- L389 _public prototype_ `virtual UMaterialExpressionComposite* CreateNewMaterialExpressionComposite(const FVector2D& NodePos, const class UEdGraph* Graph = nullptr) override;`
- L390 _public prototype_ `virtual UMaterialExpressionComment* CreateNewMaterialExpressionComment(const FVector2D& NodePos, const class UEdGraph* Graph = nullptr) override;`
- L391 _public prototype_ `virtual void ForceRefreshExpressionPreviews() override;`
- L392 _public prototype_ `virtual void AddToSelection(UMaterialExpression* Expression) override;`
- L393 _public prototype_ `virtual void JumpToExpression(UMaterialExpression* Expression) override;`
- L394 _public prototype_ `virtual void DeleteSelectedNodes() override;`
- L395 _public prototype_ `virtual FText GetOriginalObjectName() const override;`
- L396 _public prototype_ `virtual TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter() const override;`
- L397 _public prototype_ `virtual void UpdateMaterialAfterGraphChange() override;`
- L398 _public prototype_ `virtual void MarkMaterialDirty() override;`
- L399 _public prototype_ `virtual void JumpToHyperlink(const UObject* ObjectReference) override;`
- L400 _public prototype_ `virtual bool CanPasteNodes() const override;`
- L401 _public prototype_ `virtual void PasteNodesHere(const FVector2D& Location, const class UEdGraph* Graph = nullptr) override;`
- L402 _public prototype_ `virtual int32 GetNumberOfSelectedNodes() const override;`
- L403 _public prototype_ `virtual TSet<UObject*> GetSelectedNodes() const override;`
- L404 _public prototype_ `virtual void GetBoundsForNode(const UEdGraphNode* InNode, class FSlateRect& OutRect, float InPadding) const override;`
- L405 _public prototype_ `virtual FMatExpressionPreview* GetExpressionPreview(UMaterialExpression* InExpression) override;`
- L406 _public prototype_ `virtual void DeleteNodes(const TArray<class UEdGraphNode*>& NodesToDelete) override;`
- L407 _public prototype_ `virtual void GenerateInheritanceMenu(class UToolMenu* Menu) override;`
- L408 _public prototype_ `virtual void RefreshStatsMaterials() override;`
- L410 _public prototype_ `void DeleteSelectedNodes(bool bShowConfirmation);`
- L411 _public prototype_ `void DeleteNodes(const TArray<class UEdGraphNode*>& NodesToDelete, bool bShowConfirmation);`
- L412 _public prototype_ `FString CopyNodesToBuffer(const FGraphPanelSelectionSet& Nodes);`
- L413 _public prototype_ `FString CopyNodesToBuffer(const TSet<UEdGraphNode*>& Nodes);`
- L414 _public prototype_ `void PasteNodesHereFromBuffer(const FVector2D& Location, const class UEdGraph* Graph, const FString& TextToImport, TMap<FGuid, FGuid>* OutOldToNewGuids);`
- L415 _public prototype_ `void UpdateStatsMaterials();`
- L418 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager()` — Gets the extensibility managers for outside entities to extend material editor's menus and toolbars
- L419 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager()`
- L421 _public function_ `FORCEINLINE bool IsShowingBuiltinStats()`
- L427 _public prototype_ `virtual void NotifyExternalMaterialChange() override;` — call this to notify the editor that the edited material changed from outside
- L430 _public prototype_ `void FocusDetailsPanel();` — Called to bring focus to the details panel
- L433 _public prototype_ `void RebuildInheritanceList();` — Rebuilds the inheritance list for this material.
- L436 _public prototype_ `static void AddInheritanceMenuEntry(FToolMenuSection& Section, const FAssetData& AssetData, bool bIsFunctionPreviewMaterial);` — Add entry to hierarchy menu
- L438 _public prototype_ `virtual void AddGraphEditorPinActionsToContextMenu(FToolMenuSection& InSection) const override;`
- L441 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;` — Overrides function in FEditorUndoClient. Called to see if the context of the current undo/redo operation is a match for the client.
- L447 _public prototype_ `static void NotifyAllUserSceneTextureLoadOrUnload(UMaterialInterface* MaterialInterface);` — Notifies all other editors that the given material with a UserSceneTexture output was loaded or unloaded, so they can refresh their preview window if needed.  Utility function shared between UMaterial and UMaterialInstance editors.
- L451 _public prototype_ `void SelectNamedRerouteUsages(UMaterialExpressionNamedRerouteDeclaration* Declaration);` — Find all usages of the given Named Reroute Declaration and show them in the Find Results tab
- L454 _public member_ `bool bMaterialDirty;` — Set to true when modifications have been made to the material
- L457 _public member_ `bool bStatsFromPreviewMaterial;` — Set to true if stats should be displayed from the preview material.
- L460 _public member_ `bool bDestructing = false;` — Set to true when editor is being destructed
- L463 _public member_ `TObjectPtr<UMaterial> Material;` — The material applied to the preview mesh.
- L465 _public member_ `TArray<TObjectPtr<UMaterialInstance>> DerivedMaterialInstances;`
- L466 _public member_ `TArray<TObjectPtr<UMaterialInstance>> OriginalDerivedMaterialInstances;`
- L469 _public member_ `TObjectPtr<UMaterial> OriginalMaterial;` — The source material being edited by this material editor. Only will be updated when Material's settings are copied over this material
- L472 _public member_ `TObjectPtr<UMaterial> ExpressionPreviewMaterial;` — The material applied to the preview mesh when previewing an expression.
- L475 _public member_ `TObjectPtr<UMaterial> EmptyMaterial;` — An empty copy of the preview material. Allows displaying of stats about the built in cost of the current material.
- L478 _public member_ `TObjectPtr<UMaterialExpression> PreviewExpression;` — The expression currently being previewed.  This is NULL when not in expression preview mode.
- L484 _public member_ `TObjectPtr<UMaterialFunction> MaterialFunction;` — Material function being edited. If this is non-NULL, a function is being edited and Material is being used to preview it.
- L487 _public member_ `UObject* OriginalMaterialObject;` — The original material or material function being edited by this material editor..
- L490 _public member_ `TObjectPtr<UMaterialEditorOptions> EditorOptions;` — Configuration class used to store editor settings across sessions.
- L493 _public member_ `TSharedPtr<FDocumentTracker> DocumentManager;` — Document manager for workflow tabs
- L496 _public member_ `TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;` — Factory that spawns graph editors; used to look up all tabs spawned by it.
- L519 _protected prototype_ `virtual void GetSaveableObjects(TArray<UObject*>& OutObjects) const override;`
- L520 _protected prototype_ `virtual void SaveAsset_Execute() override;`
- L521 _protected prototype_ `virtual void SaveAssetAs_Execute() override;`
- L522 _protected prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L526 _protected prototype_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L533 _protected prototype_ `void OnNodeDoubleClicked(class UEdGraphNode* Node);` — Called when a node is double clicked @param	Node	The Node that was clicked
- L542 _protected prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when a node's title is committed for a rename @param	NewText				New title text @param	CommitInfo			How text was committed @param	NodeBeingChanged	The node being changed
- L552 _protected prototype_ `bool OnVerifyNodeTextCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage);` — Verifies that the node text entered is valid for the node @param	NewText			New node text @param	NodeBeingChanged	The node being changed @param	OutErrorMessage		Error message to display if text is invalid @return	True if the text is valid, false otherwise
- L563 _protected prototype_ `FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph);` — Handles spawning a graph node in the current graph using the passed in chord @param	InChord		Chord that was just performed @param	InPosition	Current cursor position @param	InGraph		Graph that chord was performed in @return	FReply	Whether chord was handled
- L566 _protected prototype_ `void ModifyMaterial();` — Calls Modify() on the Material and its editor only data, as well as MaterialFunction (and its editor only data) if present
- L569 _protected prototype_ `void SelectAllNodes();` — Select every node in the graph
- L571 _protected prototype_ `bool CanSelectAllNodes() const;` — Whether we can select every node
- L574 _protected prototype_ `bool CanDeleteNodes() const;` — Whether we are able to delete the currently selected nodes
- L576 _protected prototype_ `void DeleteSelectedDuplicatableNodes();` — Delete only the currently selected nodes that can be duplicated
- L578 _protected prototype_ `void DeleteNodesInternal(const TArray<class UEdGraphNode*>& NodesToDelete, bool& bHaveExpressionsToDelete, bool& bPreviewExpressionDeleted, bool bForceDeletion = false);` — Recursively deletes nodes if needed
- L581 _protected prototype_ `void CopySelectedNodes();` — Copy the currently selected nodes
- L583 _protected prototype_ `bool CanCopyNodes() const;` — Whether we are able to copy the currently selected nodes
- L586 _protected prototype_ `void PasteNodes();` — Paste the contents of the clipboard
- L589 _protected prototype_ `void PostPasteMaterialExpression(UMaterialExpression* NewExpression);` — Handle transient properties, and other things that can't be done in PostPasteNode
- L592 _protected prototype_ `void CutSelectedNodes();` — Cut the currently selected nodes
- L594 _protected prototype_ `bool CanCutNodes() const;` — Whether we are able to cut the currently selected nodes
- L597 _protected prototype_ `void DuplicateNodes();` — Duplicate the currently selected nodes
- L599 _protected prototype_ `bool CanDuplicateNodes() const;` — Whether we are able to duplicate the currently selected nodes
- L602 _protected prototype_ `void UndoGraphAction();` — Called to undo the last action
- L605 _protected prototype_ `void RedoGraphAction();` — Called to redo the last undone action
- L608 _protected prototype_ `void OnRenameNode();` — On starting to rename node
- L611 _protected prototype_ `bool CanRenameNodes() const;` — Check if node can be renamed
- L614 _protected prototype_ `void OnCollapseNodes();` — Collapse node group
- L616 _protected prototype_ `bool CanCollapseNodes() const;` — Check if nodes can be collapsed
- L619 _protected prototype_ `void OnExpandNodes();` — Expand node group
- L621 _protected prototype_ `bool CanExpandNodes() const;` — Check if node can be expanded
- L624 _protected prototype_ `void OnOpenSelectedNodesInNewTab();` — Opens collapsed nodes in a new tab
- L626 _protected prototype_ `bool CanOpenSelectedNodesInNewTab() const;` — Check if selected nodes can be opened in a new tab
- L628 _protected prototype_ `void OnAlignTop();`
- L629 _protected prototype_ `void OnAlignMiddle();`
- L630 _protected prototype_ `void OnAlignBottom();`
- L631 _protected prototype_ `void OnAlignLeft();`
- L632 _protected prototype_ `void OnAlignCenter();`
- L633 _protected prototype_ `void OnAlignRight();`
- L635 _protected prototype_ `void OnStraightenConnections();`
- L637 _protected prototype_ `void OnDistributeNodesH();`
- L638 _protected prototype_ `void OnDistributeNodesV();`
- L641 _private prototype_ `void OnMessageLogLinkActivated(const class TSharedRef<IMessageToken>& Token);`
- L644 _private prototype_ `void ExtendToolbar();` — Builds the toolbar widget for the material editor
- L645 _private prototype_ `void RegisterToolBar();`
- L648 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);` — Creates the toolbar buttons. Bound by ExtendToolbar
- L650 _private prototype_ `void GeneratePreviewMenuContent(class UToolMenu* Menu);`
- L653 _private prototype_ `virtual bool ApproveSetPreviewAsset(UObject* InAsset) override;` — Allows editor to veto the setting of a preview asset
- L656 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L659 _private prototype_ `void UpdateAndGetMaterialExpressionGroups(TArray<FString>* OutGroups);` — Updates and returns all groups for all material expressions
- L662 _private prototype_ `void UpdateMaterialExpressionGroups();` — Updates all groups for all material expressions
- L665 _private prototype_ `void UpdatePreviewViewportsVisibility();` — Updates the 3D and UI preview viewport visibility based on material domain
- L668 _private prototype_ `void NotifyUserSceneTextureLoadOrUnload();` — Called to notify other material editors when a post process material with a UserSceneTexture output is loaded or unloaded, as the material may be used in their preview
- L688 _private prototype_ `void CollapseNodesIntoGraph(UEdGraphNode* InGatewayNode, UMaterialGraphNode* InEntryNode, UMaterialGraphNode* InResultNode, UEdGraph* InSourceGraph, UEdGraph* InDestinationGraph, TSet<UEdGraphNode*>& InCollapsableNodes);` — Collapses a selection of nodes into a graph for composite. @param InGatewayNode				The node replacing the selection of nodes @param InEntryNode				The entry node in the graph @param InResultNode				The result node in the graph @param InSourceGraph				The graph the selection is from @param InDestinationGraph		The destination graph to move the selected nodes to @param InCollapsableNodes		The selection of nodes being collapsed
- L691 _private prototype_ `void CollapseNodes(TSet<class UEdGraphNode*>& InCollapsableNodes);` — Called when a selection of nodes are being collapsed into a sub-graph
- L700 _private prototype_ `void ExpandNode(UEdGraphNode* InNodeToExpand, UEdGraph* InSourceGraph, TSet<UEdGraphNode*>& OutExpandedNodes);` — Expands passed in node @param InNodeToExpand			The node containing the selection of nodes that ill be removed @param InSourceGraph				The graph containing the original node, @param OutExpandedNodes			The nodes expanded into the source graph
- L709 _private prototype_ `void MoveNodesToAveragePos(TSet<UEdGraphNode*>& AverageNodes, FVector2D SourcePos, bool bExpandedNodesNeedUniqueGuid = false) const;` — Move the given set of nodes to an average spot near the Source position @param AverageNodes					The nodes to move @param SourcePos						The source position used to average the nodes around @param bExpandedNodesNeedUniqueGuid	If true then a new Guid will be generated for each node in the set
- L722 _private prototype_ `static void MoveNodesToGraph(TArray<UEdGraphNode*>& SourceNodes, UEdGraph* DestinationGraph, TSet<UEdGraphNode*>& OutExpandedNodes, UEdGraphNode** OutEntry, UEdGraphNode** OutResult, const bool bIsCollapsedGraph = false);` — Move every node from the source graph to the destination graph. Add Each node that is moved to the OutExpandedNodes set. If the source graph is a function graph, keep track of the entry and result nodes in the given Out Parameters. @param SourceNodes		Nodes to move @param DestinationGraph	Graph to move nodes to @param OutExpandedNodes	Set of each node that was moved from the source to destination graph @param OutEntry			Pointer to the function entry node @param OutResult			Pointer to the function result node @param bIsCollapsedGraph	Whether or not the source graph is collapsed
- L735 _private prototype_ `static bool CollapseGatewayNode(UEdGraphNode* InNode, UEdGraphNode* InEntryNode, UEdGraphNode* InResultNode, TSet<UEdGraphNode*>* OutExpandedNodes = nullptr);` — Makes connections into/or out of the gateway node, connect directly to the associated networks on the opposite side of the tunnel When done, none of the pins on the gateway node will be connected to anything. Requires both this gateway node and it's associated node to be in the same graph already (post-merging) @param InGatewayNode			The function or tunnel node @param InEntryNode			The entry node in the inner graph @param InResultNode			The result node in the inner graph @return						Returns TRUE if successful
- L738 _private prototype_ `void SetQualityPreview(EMaterialQualityLevel::Type NewQuality);` — Helper functions for the quality level node display toggling
- L739 _private prototype_ `bool IsQualityPreviewChecked(EMaterialQualityLevel::Type TestQuality);`
- L740 _private prototype_ `EMaterialQualityLevel::Type GetQualityPreviewLevel() const;`
- L743 _private prototype_ `void SetFeaturePreview(ERHIFeatureLevel::Type NewFeatureLevel);` — Helper functions for the feature level node display toggling
- L744 _private prototype_ `bool IsFeaturePreviewChecked(ERHIFeatureLevel::Type TestFeatureLevel) const;`
- L745 _private prototype_ `bool IsFeaturePreviewAvailable(ERHIFeatureLevel::Type TestFeatureLevel) const;`
- L748 _private prototype_ `void UpdateSubstrateTopologyPreview();` — Update Substrate topology preview
- L751 _private prototype_ `void CreateDerivedMaterialInstancesPreviews();` — Create array of derived material instances used in conjunction with preview material in material stats
- L754 _private prototype_ `UMaterialGraphNode* GetFirstSelectedGraphNode() const;` — Returns nullptr if nothing selected
- L761 _private prototype_ `void LoadEditorSettings();` — Load editor settings from disk (docking state, window pos/size, option state, etc).
- L766 _private prototype_ `void SaveEditorSettings();` — Saves editor settings to disk (docking state, window pos/size, option state, etc).
- L777 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates
- L780 _private prototype_ `void OnApply();` — Command for the apply button
- L781 _private prototype_ `bool OnApplyEnabled() const;`
- L783 _private prototype_ `void OnCameraHome();` — Command for the camera home button
- L785 _private prototype_ `void OnHideConnectors();` — Command for the hide unused connectors button
- L786 _private prototype_ `bool IsOnHideConnectorsChecked() const;`
- L788 _private prototype_ `void ToggleLivePreview();` — Command for the Toggle Live Preview button
- L789 _private prototype_ `bool IsToggleLivePreviewChecked() const;`
- L791 _private prototype_ `void ToggleRealTimeExpressions();` — Command for the Toggle Real Time button
- L792 _private prototype_ `bool IsToggleRealTimeExpressionsChecked() const;`
- L794 _private prototype_ `void OnAlwaysRefreshAllPreviews();` — Command for the Refresh all previews button
- L795 _private prototype_ `bool IsOnAlwaysRefreshAllPreviews() const;`
- L798 _private prototype_ `void ToggleHideUnrelatedNodes();` — Make nodes which are unrelated to the selected nodes fade out
- L799 _private prototype_ `bool IsToggleHideUnrelatedNodesChecked() const;`
- L800 _private prototype_ `bool IsSelectFocusedNodesEnabled() const;`
- L801 _private prototype_ `void CollectDownstreamNodes(UMaterialGraphNode* CurrentNode, TArray<UMaterialGraphNode*>& CollectedNodes);`
- L802 _private prototype_ `void CollectUpstreamNodes(UMaterialGraphNode* CurrentNode, TArray<UMaterialGraphNode*>& CollectedNodes);`
- L803 _private prototype_ `void HideUnrelatedNodes();`
- L804 _private prototype_ `void SelectMaterialGraphNodes(SGraphEditor& InGraphEd, const TArray<UMaterialGraphNode*>& InNodes);`
- L807 _private prototype_ `void MakeHideUnrelatedNodesOptionsMenu(class UToolMenu* Menu);` — Make a drop down menu to control the opacity of unrelated nodes
- L808 _private prototype_ `void OnLockNodeStateCheckStateChanged(ECheckBoxState NewCheckedState);`
- L809 _private prototype_ `void OnFocusWholeChainCheckStateChanged(ECheckBoxState NewCheckedState);`
- L810 _private prototype_ `void OnSelectFocusedNodesCheckStateChanged(ECheckBoxState NewCheckedState);`
- L813 _private prototype_ `void OnUseCurrentTexture();` — Command for using currently selected texture
- L815 _private prototype_ `void OnConvertObjects();` — Command for converting nodes to objects
- L817 _private prototype_ `void OnConvertTextures();` — Command for converting nodes to textures
- L819 _private prototype_ `void OnCollapseToFunction();` — Command for collapsing nodes to a function
- L820 _private prototype_ `bool CanCollapseToFunction() const;`
- L822 _private prototype_ `void OnExpandMaterialFunctionNode();` — Command for expanding a function
- L823 _private prototype_ `bool CanExpandMaterialFunctionNode() const;`
- L825 _private prototype_ `void OnPromoteObjects();` — Command for promoting nodes to double precision
- L827 _private prototype_ `void OnSelectNamedRerouteDeclaration();` — Command to select local variable declaration
- L829 _private prototype_ `void OnSelectNamedRerouteUsages();` — Command to select local variable usages
- L831 _private prototype_ `void OnCreateRerouteUsageFromDeclaration();` — Command to create reroute usage node from declaration
- L833 _private prototype_ `void OnConvertRerouteToNamedReroute();` — Command to convert a reroute node to local variables
- L835 _private prototype_ `void OnConvertNamedRerouteToReroute();` — Command to convert local variables to a reroute node
- L837 _private prototype_ `void OnPreviewNode();` — Command for previewing a selected node
- L839 _private prototype_ `void OnPreviewHoveredNode();` — Command for previewing the currently-hovered node
- L845 _private prototype_ `virtual void PreviewNode(UMaterialGraphNode* InGraphNode) override;` — Call to Preview a InGraphNode. If InGraphNode is the currently-previewed node, will stop previewing
- L848 _private prototype_ `virtual void SetCustomPrimitiveData(TConstArrayView<float> CustomFloats) override;` — Set the custom primitive data to use in the preview display area
- L851 _private prototype_ `void OnToggleRealtimePreview();` — Command for toggling real time preview of selected node
- L853 _private prototype_ `void OnSelectDownstreamNodes();` — Command to select nodes downstream of selected node
- L855 _private prototype_ `void OnSelectUpstreamNodes();` — Command to select nodes upstream of selected node
- L857 _private prototype_ `void OnForceRefreshPreviews();` — Command to force a refresh of all previews (triggered by space bar)
- L859 _private prototype_ `void OnCreateComment();` — Create comment node on graph
- L861 _private prototype_ `void OnCreateComponentMaskNode();` — Create ComponentMask node on graph
- L863 _private prototype_ `void OnFindInMaterial();` — Bring up the search tab
- L866 _private prototype_ `void OnPromoteToParameter(const FToolMenuContext& InMenuContext) const;` — Will promote selected pin to a parameter of the pin type
- L869 _private prototype_ `bool OnCanPromoteToParameter(const FToolMenuContext& InMenuContext) const;` — Used to know if we can promote selected pin to a parameter of the pin type
- L872 _private prototype_ `UClass* GetOnPromoteToParameterClass(const UEdGraphPin* TargetPin) const;` — Will  return the UClass to create from the Pin Type
- L875 _private prototype_ `bool OnCanResetToDefault(const FToolMenuContext& InMenuContext) const;` — Used to know if we can reset the selected pin to it's default value
- L878 _private prototype_ `void OnResetToDefault(const FToolMenuContext& InMenuContext) const;` — Will reset selected pin to it's default value
- L881 _private prototype_ `bool OnCanDeletePin(const FToolMenuContext& InMenuContext) const;` — Used to know if we can delete the selected pin
- L884 _private prototype_ `void OnDeletePin(const FToolMenuContext& InMenuContext) const;` — Will delete the selected pin
- L895 _private prototype_ `void OnCreateSubstrateNodeForPin(const FToolMenuContext& InMenuContext, ESubstrateNodeForPin NodeForPin) const;` — Will create a Substrate node as input to the pin
- L897 _private prototype_ `bool OnCanCreateSubstrateNodeForPin(const FToolMenuContext& InMenuContext, ESubstrateNodeForPin NodeForPin) const;` — Used to know if we can create a Substrate node as input to the pin
- L900 _private prototype_ `void OnGoToDocumentation();` — Open documentation for the selected node class
- L902 _private prototype_ `bool CanGoToDocumentation();` — Can we open documentation for the selected node
- L905 _private prototype_ `void OnGoToDefinition();` — Open C++ header for the selected node class
- L907 _private prototype_ `bool CanGoToDefinition() const;` — Can we open the C++ header for the selected node
- L910 _private prototype_ `FString GetDocLinkForSelectedNode();` — Util to try and get doc link for the currently selected node
- L913 _private prototype_ `FString GetDocLinkBaseUrlForSelectedNode();` — Util to try and get the base URL for the doc link for the currently selected node
- L916 _private prototype_ `void RenameAssetFromRegistry(const FAssetData& InAddedAssetData, const FString& InNewName);` — Callback from the Asset Registry when an asset is renamed.
- L919 _private prototype_ `void OnMaterialUsageFlagsChanged(class UMaterial* MaterialThatChanged, int32 FlagThatChanged);` — Callback to tell the Material Editor that a materials usage flags have been changed
- L922 _private prototype_ `void OnAssetPostImport(UFactory* InFactory, UObject* InObject);` — Callback when an asset is imported
- L924 _private prototype_ `void OnNumericParameterDefaultChanged(class UMaterialExpression*, EMaterialParameterType Type, FName ParameterName, const UE::Shader::FValue& Value);`
- L925 _private prototype_ `void OnParameterDefaultChanged();`
- L927 _private prototype_ `void SetNumericParameterDefaultOnDependentMaterials(EMaterialParameterType Type, FName ParameterName, const UE::Shader::FValue& Value);`
- L928 _private prototype_ `void ClearNumericParameterDefaultOnDependentMaterials(EMaterialParameterType Type, FName ParameterName);`
- L931 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L932 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L935 _private prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;` — FNotifyHook interface
- L936 _private prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L939 _private function_ `void SetMaterialDirty()` — Flags the material as dirty
- L942 _private prototype_ `void ToggleCollapsed(UMaterialExpression* MaterialExpression);` — Toggles the collapsed flag of a Material Expression and updates preview
- L948 _private prototype_ `void RefreshExpressionPreviews(bool bForceRefreshAll = false);` — Refreshes material expression previews.  Refreshes all previews if bAlwaysRefreshAllPreviews is true. Otherwise, refreshes only those previews that have a bRealtimePreview of true.
- L950 _private prototype_ `virtual void RefreshGraphFromOriginal() override;`
- L958 _private prototype_ `void RefreshExpressionPreview(UMaterialExpression* MaterialExpression, bool bRecompile);` — Refreshes the preview for the specified material expression.  Does nothing if the specified expression has a bRealtimePreview of false. @param	MaterialExpression		The material expression to update.
- L963 _private prototype_ `FMatExpressionPreview* GetExpressionPreview(UMaterialExpression* MaterialExpression, bool& bNewlyCreated);` — Returns the expression preview for the specified material expression.
- L967 _private prototype_ `void OnColorPickerCommitted(FLinearColor LinearColor, TWeakObjectPtr<UObject> ColorPickerObject);` — Called whenever the color picker is used and accepted.
- L970 _private prototype_ `TSharedRef<class SGraphEditor> CreateGraphEditorWidget(TSharedRef<class FTabInfo> InTabInfo, class UEdGraph* InGraph);` — Create new graph editor widget
- L973 _private prototype_ `FGraphAppearanceInfo GetGraphAppearance() const;` — Gets the current Material Graph's appearance
- L976 _private prototype_ `TArray<UMaterialGraphNode*> GetSelectionRelatedNodes();` — Gets the upstream and downstream nodes related to the current selection.
- L981 _private prototype_ `void CleanUnusedExpressions();` — Deletes any disconnected material expressions.
- L986 _private prototype_ `void FixupMismatchedSamplerExpressions();` — Fixes up the samplers for all broken texture sample expressions.
- L991 _private prototype_ `void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);` — Cleans up any referenced resources.
- L996 _private prototype_ `void OnPostWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);` — Refreshes editor after world cleanup.
- L1006 _private prototype_ `void DeepCopyExpressions(UMaterialGraph* CopyGraph, UMaterialExpression* NewSubgraphExpression);` — Perform a deep copy of all expressions within the given graph. @param	CopyGraph, graph whose expression's need a deep copy @param	NewSubgraphExpression, material expression that will be used as the subgraph expression for all deep copied expressions, and will become the graph's new subgraph expression
- L1015 _private prototype_ `bool CheckExpressionRemovalWarnings(const TArray<UEdGraphNode*>& NodesToRemove);` — Displays a warning message to the user if the expressions to remove would cause any issues @param NodesToRemove The expression nodes we wish to remove @return Whether the user agrees to remove these expressions
- L1018 _private prototype_ `void RemoveSelectedExpressionFromFavorites();` — Removes the selected expression from the favorites list.
- L1020 _private prototype_ `void AddSelectedExpressionToFavorites();` — Adds the selected expression to the favorites list.
- L1023 _private prototype_ `void SetEditorInstanceForWidgets() const;` — Updates internal material editor widgets
- L1026 _private prototype_ `void JumpToNodeByGuid(const FGuid& InGuid);` — Jumps to and selects the node corresponding to the given guid, even if it exists in another asset.
- L1029 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Preview(const FSpawnTabArgs& Args);`
- L1030 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MaterialProperties(const FSpawnTabArgs& Args);`
- L1031 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Palette(const FSpawnTabArgs& Args);`
- L1032 _private prototype_ `TSharedRef<SDockTab> SpawnTab_NamedReroutes(const FSpawnTabArgs& Args);`
- L1033 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Find(const FSpawnTabArgs& Args);`
- L1034 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);`
- L1035 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ParameterDefaults(const FSpawnTabArgs& Args);`
- L1036 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CustomPrimitiveData(const FSpawnTabArgs& Args);`
- L1037 _private prototype_ `TSharedRef<SDockTab> SpawnTab_LayerProperties(const FSpawnTabArgs& Args);`
- L1038 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Substrate(const FSpawnTabArgs& Args);`
- L1039 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MaterialExpressionsOverview(const FSpawnTabArgs& Args);`
- L1041 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L1042 _private prototype_ `void OnGraphChanged(const FEdGraphEditAction& Action);`
- L1043 _private prototype_ `void OnFinishedChangingParametersFromOverview(const FPropertyChangedEvent& PropertyChangedEvent);`
- L1044 _private prototype_ `void OnChangeBreadCrumbGraph(class UEdGraph* InGraph);`
- L1045 _private prototype_ `void GeneratorRowsRefreshed();`
- L1046 _private prototype_ `void UpdateGenerator();`
- L1047 _private prototype_ `void NavigateTab(FDocumentTracker::EOpenDocumentCause InCause);`
- L1050 _private member_ `TSharedPtr<class IDetailsView> MaterialDetailsView;` — Property View
- L1053 _private member_ `TWeakPtr<class SGraphEditor> FocusedGraphEdPtr;` — Currently focused graph editor
- L1056 _private member_ `TWeakPtr<class SNotificationItem> ExternalRefreshNotificationPtr;` — Outstanding "material refreshed from external edit" toast, kept so back-to-back refreshes don't stack.
- L1059 _private member_ `TSharedPtr<class SMaterialEditor3DPreviewViewport> PreviewViewport;` — Preview Viewport widget
- L1062 _private member_ `TSharedPtr<class SMaterialEditorUIPreviewViewport> PreviewUIViewport;` — Preview viewport widget used for UI materials
- L1065 _private member_ `FString MaterialErrorHash;` — Hashed error code use to refresh the error displaying widget when this will change
- L1068 _private member_ `TSharedPtr<class SMaterialPalette> Palette;` — Palette of Material Expressions and functions
- L1071 _private member_ `TSharedPtr<class SMaterialNamedReroutesPanel> NamedReroutesPanel;` — Panel listing Named Reroute Declaration nodes
- L1074 _private member_ `FDelegateHandle OnGraphChangedDelegateHandle;` — Handle for the material graph's OnGraphChanged delegate (used to refresh the Named Reroutes panel)
- L1077 _private member_ `TSharedPtr<class SMaterialEditorSubstrateWidget> SubstrateWidget;` — The Substrate control tab
- L1080 _private member_ `TSharedPtr<class SWidget> Stats;` — Stats log, with the log listing that it reflects
- L1081 _private member_ `TSharedPtr<class IMessageLogListing> StatsListing;`
- L1084 _private member_ `TSharedPtr<class SFindInMaterial> FindResults;` — Find results log as well as the search filter
- L1087 _private member_ `TSharedPtr<class SMaterialParametersOverviewPanel> MaterialParametersOverviewWidget;` — Parameter overview list View
- L1090 _private member_ `TSharedPtr<class SMaterialExpressionsOverviewPanel> MaterialExpressionsOverviewWidget;` — Shared texture samplers list view
- L1093 _private member_ `TSharedPtr<class SMaterialCustomPrimitiveDataPanel> MaterialCustomPrimitiveDataWidget;` — Custom primitive data widget
- L1096 _private member_ `TSharedPtr<class SMaterialLayersFunctionsMaterialWrapper> MaterialLayersFunctionsInstance;` — Layer Properties View
- L1099 _private member_ `FScopedTransaction* ScopedTransaction;` — The current transaction.
- L1102 _private member_ `bool bAlwaysRefreshAllPreviews;` — If true, always refresh all expression previews.  This overrides UMaterialExpression::bRealtimePreview.
- L1105 _private member_ `TArray<TRefCountPtr<FMatExpressionPreview>> ExpressionPreviews;` — Material expression previews.
- L1108 _private member_ `TArray<TSharedPtr<FMaterialInfo>> MaterialInfoList;` — Used to store material errors
- L1110 _private member_ `TSet<TTuple<EMaterialParameterType, FName>> OverriddenNumericParametersToRevert;`
- L1113 _private member_ `bool bHideUnusedConnectors;` — If true, don't render connectors that are not connected to anything.
- L1116 _private member_ `bool bLivePreview;` — If true, the preview material is compiled on every edit of the material. If false, only on Apply.
- L1119 _private member_ `bool bIsRealtime;` — Just storing this choice for now, not sure what difference it will make to Graph Editor
- L1122 _private member_ `bool bShowBuiltinStats;` — If true, show stats for an empty material. Helps artists to judge the cost of their changes to the graph.
- L1125 _private member_ `bool bHideUnrelatedNodes;` — If true, fade out nodes which are unrelated to the selected nodes automatically.
- L1128 _private member_ `bool bLockNodeFadeState;` — Lock the current fade state of each node
- L1131 _private member_ `bool bFocusWholeChain;` — Focus all nodes in the same output chain
- L1134 _private member_ `bool bSelectFocusedNodes;` — Select focused nodes.
- L1137 _private member_ `bool bFocusSelectionInProgress;` — Used to avoid selection operations while automated selection takes place.
- L1140 _private member_ `bool bSelectRegularNode;` — If a regular node (not a comment node, not the output node) has been selected
- L1143 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this editor
- L1145 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L1146 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L1149 _private member_ `TObjectPtr<class UMaterialEditorPreviewParameters> MaterialEditorInstance;` — Object that stores all of the possible parameters we can edit.
- L1152 _private member_ `TSharedPtr<class FMaterialStats> MaterialStatsManager;` — Object used as material statistics manager
- L1155 _private member_ `TWeakPtr<SDockTab> SpawnedDetailsTab;` — Tab that holds the details panel
- L1158 _private member_ `EMaterialQualityLevel::Type NodeQualityLevel;` — Stores the quality level used to preview the material graph
- L1161 _private member_ `ERHIFeatureLevel::Type NodeFeatureLevel;` — Stores the feature level used to preview the material graph
- L1164 _private member_ `bool bPreviewStaticSwitches;` — True if we want to preview static switches, disabling inactive nodes in the graph
- L1167 _private member_ `bool bPreviewFeaturesChanged;` — True if the quality level or feature level to preview has been changed
- L1170 _private member_ `TArray< FAssetData > MaterialChildList;` — List of children used to populate the inheritance list chain.
- L1173 _private member_ `TArray< FAssetData > FunctionChildList;` — List of children used to populate the inheritance list chain.
- L1175 _private member_ `TSharedPtr<class IPropertyRowGenerator> Generator;`
- L1178 _private member_ `FDelegateHandle OnWorldCleanupDelegateHandle;` — Delegate handles for FWorldDelegates registrations.
- L1179 _private member_ `FDelegateHandle OnPostWorldCleanupDelegateHandle;`
- L1182 _private member_ `TSharedPtr<STextBlock> NumShadersText;` — The text for the number of shaders in the material.
- L1185 _private member_ `TArray<float> CustomPrimitiveDataFloats;` — Current custom primitive data set

#### struct `FMaterialEditor::FScopedMaterialChecker`  
`struct FScopedMaterialChecker`  
_L503-515_
- desc: Helper struct used to validate the state of the material after the material editor performs an operation, searching for any invalid state.
- L508 _public member_ `FMaterialEditor* Editor;` — The material editor performing the operation
- L511 _public member_ `const char* DebugEditName;` — Name of the operation being performed, logged when an issue is reported
- L513 _public prototype_ `FScopedMaterialChecker(FMaterialEditor* Editor, const char* DebugEditName);`
- L514 _public prototype_ `~FScopedMaterialChecker();`

#### enum `FMaterialEditor::ESubstrateNodeForPin`  
`enum class ESubstrateNodeForPin : uint8`  
_L886-893_
- L888 _public enumerator_ `Slab`
- L889 _public enumerator_ `HorizontalMix`
- L890 _public enumerator_ `VerticalLayer`
- L891 _public enumerator_ `Weight`
- L892 _public enumerator_ `Select`

#### Free symbols / members of external scopes

- L52 _typedef_ `typedef TSet<class UObject*> FGraphPanelSelectionSet;`
- L158 _function_ `friend FArchive& operator<< ( FArchive& Ar, FMatExpressionPreview& V )`
- L195 _function_ `friend bool operator==(const FMaterialExpression& A,const FMaterialExpression& B)`

### `Source/Editor/MaterialEditor/Private/MaterialEditorDelegates.h` (Private)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FSelectMaterialNode, const FGuid& InNodeGuid);`
- L10 _prototype_ `DECLARE_DELEGATE_OneParam(FSelectMaterialNode, const FGuid& InNodeGuid);`

### `Source/Editor/MaterialEditor/Private/MaterialEditorDetailCustomization.h` (Private)


#### class `FMaterialExpressionParameterDetails`  
`class FMaterialExpressionParameterDetails : public IDetailCustomization`  
_L17-62_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance(FOnCollectParameterGroups InCollectGroupsDelegate);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `FMaterialExpressionParameterDetails(FOnCollectParameterGroups InCollectGroupsDelegate);` — Constructor requires a delegate to populate group names with
- L28 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L32 _protected prototype_ `FMaterialExpressionParameterDetails();` — Default constructor for child overrides
- L35 _protected prototype_ `void PopulateGroups();` — Populates the group name that this parameter details uses
- L38 _protected prototype_ `TSharedRef< ITableRow > MakeDetailsGroupViewWidget( TSharedPtr<FString> Item, const TSharedRef< STableViewBase >& OwnerTable );` — Functions used to make the custom combo button with editable text
- L39 _protected prototype_ `void OnSelectionChanged( TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo );`
- L40 _protected prototype_ `void OnTextCommitted( const FText& InText, ETextCommit::Type CommitInfo);`
- L41 _protected prototype_ `FString OnGetString() const;`
- L42 _protected prototype_ `FText OnGetText() const;`
- L43 _protected prototype_ `void OnSliderMinMaxEdited();`
- L47 _protected member_ `TSharedPtr<class IPropertyHandle> GroupPropertyHandle;` — The property handle to the groups
- L50 _protected member_ `TWeakPtr<SComboButton> GroupComboButton;` — Custom widgets (combo button with editable text) to access the property with
- L51 _protected member_ `TWeakPtr<SEditableText> GroupEditBox;`
- L52 _protected member_ `TWeakPtr<SListView<TSharedPtr<FString>>> GroupListView;`
- L55 _protected member_ `FOnCollectParameterGroups CollectGroupsDelegate;` — Delegate to call to collect a list of groups with
- L58 _protected member_ `TArray<TSharedPtr<FString>> GroupsSource;` — A list of all group names to choose from
- L60 _protected member_ `TArray<TWeakObjectPtr<UObject>> ScalarParameterObjects;`
- L61 _protected member_ `TArray<TSharedPtr<IPropertyHandle>> DefaultValueHandles;`

#### class `FMaterialExpressionLayersParameterDetails`  
`class FMaterialExpressionLayersParameterDetails : public FMaterialExpressionParameterDetails`  
_L64-78_
- inherits: `FMaterialExpressionParameterDetails`
- L69 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance(FOnCollectParameterGroups InCollectGroupsDelegate);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L72 _public prototype_ `FMaterialExpressionLayersParameterDetails(FOnCollectParameterGroups InCollectGroupsDelegate);` — Constructor requires a delegate to populate group names with
- L75 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L77 _public prototype_ `void ResetCategory(IDetailLayoutBuilder* DetailLayout);`

#### class `FMaterialExpressionCollectionParameterDetails`  
`class FMaterialExpressionCollectionParameterDetails : public IDetailCustomization`  
_L84-128_
- inherits: `IDetailCustomization`
- desc: Customizes the details of a CollectionParameter node, specifically creating a vertical box for ParameterName with only valid entries based on the current collection.
- L89 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance(bool bInIncludeScalars);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L92 _public prototype_ `FMaterialExpressionCollectionParameterDetails(bool bInIncludeScalars);` — Constructor requires a delegate to populate group names with
- L95 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L99 _private prototype_ `void PopulateParameters(const FString& FilterText);` — Populates the group name that this parameter details uses
- L102 _private prototype_ `TSharedRef< ITableRow > MakeDetailsGroupViewWidget( TSharedPtr<FString> Item, const TSharedRef< STableViewBase >& OwnerTable );` — Functions used to make the custom combo button with editable text
- L103 _private prototype_ `void OnSelectionChanged( TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo );`
- L104 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L106 _private prototype_ `FText GetToolTipText() const;`
- L107 _private prototype_ `FText GetParameterNameString() const;`
- L108 _private prototype_ `bool IsParameterNameComboEnabled() const;`
- L109 _private prototype_ `void OnCollectionChanged();`
- L113 _private member_ `TSharedPtr<class IPropertyHandle> CollectionPropertyHandle;`
- L116 _private member_ `TSharedPtr<class IPropertyHandle> ParameterNamePropertyHandle;` — The property handle to the parameter name
- L118 _private member_ `TWeakPtr<SComboButton> ParameterComboButton;`
- L119 _private member_ `TWeakPtr<SListView<TSharedPtr<FString>>> ParameterListView;`
- L121 _private member_ `TSharedPtr<class SSearchBox> ParameterSearchBox;` — Text entry to filter parameters
- L124 _private member_ `TArray<TSharedPtr<FString>> ParametersSource;` — A list of all parameter names to choose from
- L127 _private member_ `bool bIncludeScalars;` — Whether to include scalars in this detail customization

#### class `FMaterialExpressionCompositeDetails`  
`class FMaterialExpressionCompositeDetails : public IDetailCustomization`  
_L135-144_
- inherits: `IDetailCustomization`
- desc: Customizes the details of a Composite node, specifically exposing pinbases.
- L140 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L143 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

#### class `FMaterialExpressionColorRampCustomization`  
`class FMaterialExpressionColorRampCustomization : public IDetailCustomization`  
_L149-158_
- inherits: `IDetailCustomization`
- desc: Customizes the details of a Color Ramp node, adding a gradient slider to the panel
- L154 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L157 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

#### class `FMaterialExpressionOperatorCustomization`  
`class FMaterialExpressionOperatorCustomization : public IDetailCustomization`  
_L163-171_
- inherits: `IDetailCustomization`
- desc: Customizes the details of Operator node
- L167 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L170 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

#### class `FMaterialDetailCustomization`  
`class FMaterialDetailCustomization : public IDetailCustomization`  
_L173-182_
- inherits: `IDetailCustomization`
- L178 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L181 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface

#### class `FMaterialFunctionDetailCustomization`  
`class FMaterialFunctionDetailCustomization : public IDetailCustomization`  
_L184-193_
- inherits: `IDetailCustomization`
- L189 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L192 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCollectParameterGroups, TArray<FString>*);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCollectParameterGroups, TArray<FString>*);`

### `Source/Editor/MaterialEditor/Private/MaterialEditorHelpers.h` (Private)


#### class `FMaterialEditorHelpers`  
`class FMaterialEditorHelpers`  
_L12-24_
- L15 _public prototype_ `static void CollapseToFunction(FMaterialEditor& MaterialEditor);`
- L16 _public prototype_ `static void ExpandNode(FMaterialEditor& MaterialEditor);`
- L17 _public prototype_ `static void ExpandNode(FMaterialEditor& MaterialEditor, FMaterialEditor& FunctionMaterialEditor, UMaterialGraphNode* FunctionCallNode);`
- L18 _public prototype_ `static FMaterialEditor* OpenMaterialEditorForAsset(UObject* Asset);`
- L20 _private prototype_ `static FBox2D GetNodesBounds(FMaterialEditor& MaterialEditor, const TSet<UEdGraphNode*>& Nodes);`
- L21 _private prototype_ `static void FindNewNodes(FMaterialEditor& MaterialEditor, TMap<FGuid, UMaterialGraphNode*>& OutOldGuidToNewNode, const TMap<FGuid, FGuid>& OldToNewGuids);`
- L22 _private prototype_ `static UEdGraphPin* FindNewPin(UEdGraphPin* OldPin, const TMap<FGuid, UMaterialGraphNode*>& OldGuidToNewNode);`

### `Source/Editor/MaterialEditor/Private/MaterialEditorInstanceDetailCustomization.h` (Private)


#### class `FMaterialInstanceParameterDetails`  
`class FMaterialInstanceParameterDetails : public IDetailCustomization`  
_L27-144_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `static TSharedRef<class IDetailCustomization> MakeInstance(UMaterialEditorInstanceConstant* MaterialInstance, SMaterialLayersFunctionsInstanceWrapper* MaterialLayersFunctionsInstance, FGetShowHiddenParameters InShowHiddenDelegate);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L34 _public prototype_ `FMaterialInstanceParameterDetails(UMaterialEditorInstanceConstant* MaterialInstance, SMaterialLayersFunctionsInstanceWrapper* MaterialLayersFunctionsInstance, FGetShowHiddenParameters InShowHiddenDelegate);` — Constructor
- L37 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L41 _private prototype_ `FString GetFunctionParentPath() const;` — Returns the function parent path
- L44 _private prototype_ `void CreateGroupsWidget(TSharedRef<IPropertyHandle> ParameterGroupsProperty, class IDetailCategoryBuilder& GroupsCategory);` — Builds the custom parameter groups category
- L45 _private prototype_ `void CreateParameterCollectionOverrideCategory(TSharedRef<IPropertyHandle> ParameterGroupsProperty, class IDetailLayoutBuilder& DetailLayout);`
- L48 _private prototype_ `void CreateSingleGroupWidget(struct FEditorParameterGroup& ParameterGroup, TSharedPtr<IPropertyHandle> ParameterGroupProperty, class IDetailGroup& DetailGroup, int32 GroupIndex = -1, bool bForceShowParam = false);` — Builds the widget for an individual parameter group
- L51 _private prototype_ `void EnableGroupParameters(TArray<int32> ParameterGroupIndices, bool bShouldEnable);` — Enable/Disable all parameter properties in a group
- L54 _private prototype_ `bool OnShouldSetAsset(const FAssetData& InAssetData) const;` — Called to check if an asset can be set as a parent
- L57 _private prototype_ `void OnAssetChanged(const FAssetData& InAssetData, TSharedRef<IPropertyHandle> InHandle);` — Called when an asset is set as a parent
- L60 _private prototype_ `EVisibility ShouldShowMaterialRefractionSettings() const;` — Returns true if the refraction options should be displayed
- L63 _private prototype_ `EVisibility ShouldShowSubsurfaceProfile() const;` — Returns true if the Subsurface Profile options should be displayed
- L66 _private prototype_ `EVisibility ShouldShowSpecularProfile() const;` — Returns true if the Specular Profile options should be displayed
- L69 _private prototype_ `EVisibility ShouldShowToonProfile() const;` — Returns true if the Toon Profile options should be displayed
- L77 _private prototype_ `void OnCopyParameterValues(TArray<int32> ParameterGroupIndices);` — Copy all parameter values in a parameter group to the clipboard in the format "Param1=\"Value1\"\nParams2=\"Value2\"..."
- L80 _private prototype_ `bool CanCopyParameterValues(TArray<int32> ParameterGroupIndices);` — Whether it is possible to copy parameter values for the given parent group index
- L86 _private prototype_ `void OnPasteParameterValues(TArray<int32> ParameterGroupIndices);` — Paste parameter values from the clipboard, assumed to be in the format copied by CopyParameterValues.
- L92 _private prototype_ `bool CanPasteParameterValues(TArray<int32> ParameterGroupIndices);` — Whether it is possible to paste parameter values onto the given group index, and if there is anything on the clipboard to paste from.
- L95 _private prototype_ `void CreateLightmassOverrideWidgets(IDetailLayoutBuilder& DetailLayout);` — Creates all the lightmass property override widgets.
- L98 _private prototype_ `void CreatePostProcessOverrideWidgets(IDetailLayoutBuilder& DetailLayout);` — Creates Blendable Location / Priority and UserSceneTexture input / output override widgets.
- L103 _private prototype_ `void CreateBasePropertyOverrideWidgets(IDetailLayoutBuilder& DetailLayout, IDetailGroup& MaterialPropertyOverrideGroup);` — Creates all the base property override widgets.
- L105 _private prototype_ `void CreateUsageFlagOverrideWidgets(IDetailLayoutBuilder& DetailLayout, IDetailCategoryBuilder& CategoryBuilder);` — Creates all the usage flag override widgets.
- L107 _private prototype_ `EVisibility IsOverriddenAndVisible(TAttribute<bool> IsOverridden) const;`
- L108 _private prototype_ `EVisibility IsOverriddenAndVisibleShadingModels(TAttribute<bool> IsOverridden) const;`
- L109 _private prototype_ `EVisibility IsOverriddenAndVisibleSubstrateOnly(TAttribute<bool> IsOverridden) const;`
- L135 _private member_ `UMaterialEditorInstanceConstant* MaterialEditorInstance;` — Object that stores all of the possible parameters we can edit
- L137 _private member_ `SMaterialLayersFunctionsInstanceWrapper* MaterialLayersFunctionsInstance;`
- L140 _private member_ `FGetShowHiddenParameters ShowHiddenDelegate;` — Delegate to call to determine if hidden parameters should be shown
- L143 _private member_ `TWeakPtr<class IPropertyUtilities> PropertyUtilities;` — Associated FMaterialInstance utilities

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FGetShowHiddenParameters, bool&);`
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FGetShowHiddenParameters, bool&);`
- L111 _macro_ `#define DECLARE_OVERRIDE_MEMBER_FUNCS(PropertyName) \`

### `Source/Editor/MaterialEditor/Private/MaterialEditorTabs.h` (Private)


#### struct `FMaterialEditorTabs`  
`struct FMaterialEditorTabs`  
_L8-26_
- desc: Material editor tabs identifiers
- L11 _public member_ `static const FName PreviewTabId;` — The tab id for the Material fixture types tab
- L12 _public member_ `static const FName PropertiesTabId;`
- L13 _public member_ `static const FName PaletteTabId;`
- L14 _public member_ `static const FName FindTabId;`
- L15 _public member_ `static const FName GraphEditor;`
- L16 _public member_ `static const FName PreviewSettingsTabId;`
- L17 _public member_ `static const FName ParameterDefaultsTabId;`
- L18 _public member_ `static const FName CustomPrimitiveTabId;`
- L19 _public member_ `static const FName LayerPropertiesTabId;`
- L20 _public member_ `static const FName SubstrateTabId;`
- L21 _public member_ `static const FName MaterialOverviewTabId;`
- L22 _public member_ `static const FName NamedReroutesTabId;`
- L25 _public prototype_ `FMaterialEditorTabs() = delete;` — Disable default constructor

#### struct `FMaterialInstanceEditorTabs`  
`struct FMaterialInstanceEditorTabs`  
_L28-38_
- L31 _public member_ `static const FName PreviewTabId;` — The ids for the tabs spawned by this toolkit
- L32 _public member_ `static const FName PropertiesTabId;`
- L33 _public member_ `static const FName LayerPropertiesTabId;`
- L34 _public member_ `static const FName PreviewSettingsTabId;`
- L37 _public prototype_ `FMaterialInstanceEditorTabs() = delete;` — Disable default constructor

### `Source/Editor/MaterialEditor/Private/MaterialEditorViewportToolbarSections.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MaterialEditor` (scope `UE`)
- L12 _prototype_ `TSharedRef<SWidget> CreateShowMenuWidget(const TSharedRef<SMaterialEditor3DPreviewViewport>& InMaterialEditorViewport, bool bInShowViewportStatsToggle = true);` (scope `UE::MaterialEditor`)
- L13 _prototype_ `void ExtendPreviewSceneSettingsSubmenu(FName InSubmenuName);` (scope `UE::MaterialEditor`)

### `Source/Editor/MaterialEditor/Private/MaterialExpressionClasses.h` (Private)


#### class `MaterialExpressionClasses`  
`class MaterialExpressionClasses`  
_L9-72_
- L13 _public prototype_ `static MaterialExpressionClasses* Get();` — Gets singleton instance
- L22 _public prototype_ `bool IsMaterialExpressionInFavorites(UMaterialExpression* InExpression);` — Checks if the given expression is in the favorites list... @param	InExpression	The expression to check for. @return	bool			true if it's in the list, false if not.
- L27 _public prototype_ `void RemoveMaterialExpressionFromFavorites(UClass* InExpression);` — Remove the expression from the favorites menu list.
- L32 _public prototype_ `void AddMaterialExpressionToFavorites(UClass* InExpression);` — Add the expression to the favorites menu list.
- L35 _public member_ `TArray<struct FMaterialExpression> AllExpressionClasses;` — array of UMaterialExpression-derived classes, shared between all material editor instances.
- L36 _public member_ `TArray<struct FMaterialExpression> FavoriteExpressionClasses;`
- L39 _public member_ `TArray<struct FCategorizedMaterialExpressionNode> CategorizedExpressionClasses;` — array of UMaterialExpression-derived classes, shared between all material editor instances.
- L40 _public member_ `TArray<struct FMaterialExpression> UnassignedExpressionClasses;`
- L43 _private prototype_ `MaterialExpressionClasses();`
- L45 _private prototype_ `virtual ~MaterialExpressionClasses();`
- L50 _private prototype_ `const UStruct* GetExpressionInputStruct();`
- L60 _private prototype_ `struct FCategorizedMaterialExpressionNode* GetCategoryNode(const FText& InCategoryName, bool bCreate);` — Grab the expression array for the given category. @param	InCategoryName	The category to retrieve @param	bCreate			If true, create the entry if not found. @return	The category node.
- L65 _private prototype_ `void InitMaterialExpressionClasses();` — Initializes the list of UMaterialExpression-derived classes shared between all material editor instances.
- L71 _private member_ `bool bInitialized;` — true if the list of UMaterialExpression-derived classes shared between material editors has already been created.

### `Source/Editor/MaterialEditor/Private/MaterialGraphConnectionDrawingPolicy.h` (Private)


#### class `FMaterialGraphConnectionDrawingPolicy`  
`class FMaterialGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L23-47_
- inherits: `FConnectionDrawingPolicy`
- desc: This class draws the connections for an UEdGraph using a MaterialGraph schema
- L26 _protected member_ `UMaterialGraph* MaterialGraph;`
- L27 _protected member_ `const UMaterialGraphSchema* MaterialGraphSchema;`
- L30 _protected member_ `TMap<class UMaterialGraphNode_Knot*, bool> KnotToReversedDirectionMap;` — Each time a knot is encountered, input geometry is compared to output geometry to see if the pins on the knot need to be reversed
- L32 _protected prototype_ `bool ShouldChangeTangentForKnot(class UMaterialGraphNode_Knot* Knot);`
- L33 _protected prototype_ `bool GetAverageConnectedPosition(class UMaterialGraphNode_Knot* Knot, EEdGraphPinDirection Direction, FVector2f& OutPos) const;`
- L34 _protected prototype_ `bool FindPinCenter(UEdGraphPin* Pin, FVector2f& OutCenter) const;`
- L37 _public prototype_ `FMaterialGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L39 _public prototype_ `virtual TSharedPtr<IToolTip> GetConnectionToolTip(const SGraphPanel& GraphPanel, const FGraphSplineOverlapResult& OverlapData) const override;`
- L42 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface
- L46 _private prototype_ `FText GetNodePinInfo(const TSharedPtr<SGraphPin>& PinWidget) const;`

#### struct `FMaterialEditorGraphPinConnectionFactory`  
`struct FMaterialEditorGraphPinConnectionFactory : public FGraphPanelPinConnectionFactory`  
_L49-53_
- inherits: `FGraphPanelPinConnectionFactory`
- L52 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionPolicy(const class UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const class FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`

### `Source/Editor/MaterialEditor/Private/MaterialInstanceEditor.h` (Private)


#### class `FMaterialInstanceEditor`  
`class FMaterialInstanceEditor : public IMaterialEditor, public FNotifyHook, public FGCObject, public FEditorUndoClient, public FTickableEditorObject`  
_L31-283_
- inherits: `IMaterialEditor,FNotifyHook,FGCObject,FEditorUndoClient,FTickableEditorObject`
- desc: Material Instance Editor class
- L35 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L36 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L39 _public prototype_ `void InitEditorForMaterial(UMaterialInstance* InMaterial);` — Initializes the editor to use a material. Should be the first thing called.
- L42 _public prototype_ `void InitEditorForMaterialFunction(UMaterialFunctionInstance* InMaterialFunction);` — Initializes the editor to use a material function. Should be the first thing called.
- L51 _public prototype_ `void InitMaterialInstanceEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit );` — Edits the specified material instance object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit			The material instance to edit
- L53 _public prototype_ `FMaterialInstanceEditor();`
- L55 _public prototype_ `virtual ~FMaterialInstanceEditor();`
- L58 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L59 _public function_ `virtual FString GetReferencerName() const override`
- L65 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L66 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L67 _public prototype_ `virtual FText GetToolkitName() const override;`
- L68 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L69 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L70 _public prototype_ `virtual void InitToolMenuContext(struct FToolMenuContext& MenuContext) override;`
- L73 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — @return Returns the color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode.
- L76 _public prototype_ `virtual UMaterialInterface* GetMaterialInterface() const override;` — The material instance applied to the preview mesh.
- L79 _public prototype_ `virtual void NotifyPreChange( FProperty* PropertyAboutToChange ) override;` — Pre edit change notify for properties.
- L82 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged ) override;` — Post edit change notify for properties.
- L84 _public prototype_ `void PreSavePackage(UPackage* Obj, FObjectPreSaveContext ObjectSaveContext);`
- L87 _public prototype_ `void RebuildInheritanceList();` — Rebuilds the inheritance list for this material instance.
- L90 _public prototype_ `void RebuildMaterialInstanceEditor();` — Rebuilds the editor when the original material changes
- L95 _public prototype_ `virtual void DrawMessages( FViewport* Viewport, FCanvas* Canvas ) override;` — Draws messages on the specified viewport and canvas.
- L102 _public prototype_ `void DrawOnScreenMessages(FCanvas* Canvas, int32& DrawPositionY);` — Draws generic on screen messages. @param Canvas - The canvas on which to draw. @param DrawPositionY - The Y position at which to draw. Upon return contains the Y value following the last line of text drawn.
- L105 _public prototype_ `bool SetPreviewAsset(UObject* InAsset);` — Passes instructions to the preview viewport
- L106 _public prototype_ `bool SetPreviewAssetByName(const TCHAR* InMeshName);`
- L107 _public prototype_ `void SetPreviewMaterial(UMaterialInterface* InMaterialInterface);`
- L110 _public prototype_ `void GetShowHiddenParameters(bool& bShowHiddenParameters);` — Returns true if hidden parameters should be shown
- L113 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager()` — Gets the extensibility managers for outside entities to extend material editor's menus and toolbars
- L114 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager()`
- L116 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L117 _public prototype_ `virtual TStatId GetStatId() const override;`
- L120 _public prototype_ `virtual void NotifyExternalMaterialChange() override;` — call this to notify the editor that the edited material changed from outside
- L123 _public prototype_ `virtual TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter() const override;` — IMaterial Editor Interface
- L124 _public prototype_ `virtual void GenerateInheritanceMenu(class UToolMenu* Menu) override;`
- L126 _public prototype_ `void RefreshPreviewViewport();`
- L129 _public prototype_ `void Refresh();` — Refresh the viewport and property window
- L131 _public function_ `bool IsDestructing() const`
- L135 _protected prototype_ `virtual void SaveAsset_Execute() override;`
- L136 _protected prototype_ `virtual void SaveAssetAs_Execute() override;`
- L137 _protected prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L140 _protected prototype_ `void SaveSettings();` — Saves editor settings.
- L143 _protected prototype_ `void LoadSettings();` — Loads editor settings.
- L146 _protected prototype_ `void OpenSelectedParentEditor(UMaterialInterface* InMaterialInterface);` — Opens the editor for the selected parent.
- L147 _protected prototype_ `void OpenSelectedParentEditor(UMaterialFunctionInterface* InMaterialFunction);`
- L150 _protected prototype_ `void UpdatePropertyWindow();` — Updated the properties pane
- L152 _protected prototype_ `virtual UObject* GetSyncObject();`
- L156 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates
- L159 _private prototype_ `void OnApply();` — Command for the apply button
- L160 _private prototype_ `bool OnApplyEnabled() const;`
- L161 _private prototype_ `bool OnApplyVisible() const;`
- L165 _private prototype_ `void ToggleShowAllMaterialParameters();` — Commands for the ShowAllMaterialParametersEnabled button
- L166 _private prototype_ `bool IsShowAllMaterialParametersChecked() const;`
- L169 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L172 _private prototype_ `void FilterOverriddenProperties();` — Delegate for overriding Show Modified to Show Overridden instead
- L175 _private prototype_ `void UpdatePreviewViewportsVisibility();` — Updates the 3D and UI preview viewport visibility based on material domain
- L177 _private prototype_ `void RegisterToolBar();`
- L179 _private prototype_ `void ExtendToolbar();` — Builds the toolbar widget for the material editor
- L182 _private prototype_ `void ReInitMaterialFunctionProxies();` — If re-initializing for a material function instance re-generate the proxy materials
- L185 _private prototype_ `virtual bool ApproveSetPreviewAsset(UObject* InAsset) override;`
- L188 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Preview( const FSpawnTabArgs& Args );` — Spawns the preview tab
- L191 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties( const FSpawnTabArgs& Args );` — Spawns the properties tab
- L194 _private prototype_ `TSharedRef<SDockTab> SpawnTab_LayerProperties(const FSpawnTabArgs& Args);` — Spawns the properties tab
- L197 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);` — Spawns the advanced preview settings tab
- L200 _private prototype_ `void AddToSpawnedToolPanels( const FName& TabIdentifier, const TSharedRef<SDockTab>& SpawnedTab );` — Caches the specified tab for later retrieval
- L203 _private prototype_ `void RefreshPreviewAsset();` — Refreshes the preview asset
- L205 _private prototype_ `void RefreshOnScreenTextureWarnings();`
- L208 _private prototype_ `virtual void PostUndo( bool bSuccess ) override;`
- L209 _private prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L213 _private prototype_ `void NotifyUserSceneTextureLoadOrUnload();` — Called to notify other material editors when a post process material with a UserSceneTexture output is loaded or unloaded, as the material may be used in their preview
- L226 _private member_ `TMap< FName, TWeakPtr<class SDockTab> > SpawnedToolPanels;` — List of open tool panels; used to ensure only one exists at any one time
- L229 _private member_ `TSharedPtr<class SMaterialEditor3DPreviewViewport> PreviewVC;` — Preview Viewport widget
- L232 _private member_ `TSharedPtr<class SMaterialEditorUIPreviewViewport> PreviewUIViewport;` — Preview viewport widget used for UI materials
- L235 _private member_ `TSharedPtr<class IDetailsView> MaterialInstanceDetails;` — Property View
- L238 _private member_ `TSharedPtr<class SMaterialLayersFunctionsInstanceWrapper> MaterialLayersFunctionsInstance;` — Layer Properties View
- L241 _private member_ `TArray< FAssetData > MaterialParentList;` — List of parents used to populate the inheritance list chain.
- L244 _private member_ `TArray< FAssetData > FunctionParentList;` — List of parents used to populate the inheritance list chain.
- L247 _private member_ `TArray< FAssetData > MaterialChildList;` — List of children used to populate the inheritance list chain.
- L250 _private member_ `TArray< FAssetData > FunctionChildList;` — List of children used to populate the inheritance list chain.
- L253 _private member_ `TArray<FOnScreenMessage> OnScreenMessages;` — List of all current on-screen messages to display
- L256 _private member_ `TObjectPtr<UMaterialEditorInstanceConstant> MaterialEditorInstance;` — Object that stores all of the possible parameters we can edit.
- L259 _private member_ `bool bShowAllMaterialParameters;` — Whether or not we should be displaying all the material parameters
- L262 _private member_ `bool bIsFunctionPreviewMaterial;` — If editing instance of a function instead of a material.
- L265 _private member_ `bool bDestructing = false;` — Set to true when editor is being destructed
- L268 _private member_ `TSharedPtr<class SMaterialEditorSubstrateWidget> SubstrateWidget;` — The Substrate control tab
- L270 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L271 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L273 _private member_ `UMaterialFunctionInstance* MaterialFunctionOriginal;`
- L274 _private member_ `UMaterialFunctionInstance* MaterialFunctionInstance;`
- L275 _private member_ `UMaterial* FunctionMaterialProxy;`
- L276 _private member_ `UMaterialInstanceConstant* FunctionInstanceProxy;`
- L279 _private member_ `TSharedPtr<class FMaterialStats> MaterialStatsManager;` — Object used as material statistics manager
- L282 _private member_ `TSharedPtr<STextBlock> NumShadersPillText;` — The text for the number of shaders in the material.

#### struct `FMaterialInstanceEditor::FOnScreenMessage`  
`struct FOnScreenMessage`  
_L216-223_
- L218 _public prototype_ `FOnScreenMessage() = default;`
- L219 _public function_ `FOnScreenMessage(const FLinearColor& InColor, const FString& InMessage) : Message(InMessage), Color(InColor)`
- L221 _public member_ `FString Message;`
- L222 _public member_ `FLinearColor Color;`

### `Source/Editor/MaterialEditor/Private/MaterialLayersFunctionsCustomization.h` (Private)


#### enum `EMaterialLayerRowType`  
`enum EMaterialLayerRowType`  
_L12-16_
- L14 _public enumerator_ `Layer`
- L15 _public enumerator_ `Blend`

#### class `FMaterialLayersFunctionsCustomization`  
`class FMaterialLayersFunctionsCustomization : public IDetailCustomNodeBuilder, public TSharedFromThis< FMaterialLayersFunctionsCustomization >`  
_L19-87_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMaterialLayersFunctionsCustomization>`
- desc: Customize the appearance of an FMaterialLayersFunction
- L22 _public prototype_ `FMaterialLayersFunctionsCustomization(const TSharedPtr<class IPropertyHandle>& StructPropertyHandle, const class IDetailLayoutBuilder* InDetailLayout);`
- L24 _public prototype_ `void AddLayer();` — Adds a layer and the corresponding blend to the FMaterialLayerFunctions
- L26 _public prototype_ `void RemoveLayer(int32 Index);` — Removes a layer and any corresponding blend from the FMaterialLayerFunctions
- L28 _public prototype_ `void RefreshOnAssetChange(const struct FAssetData& InAssetData, int32 Index, EMaterialParameterAssociation MaterialType);`
- L30 _public function_ `FMaterialLayersFunctions* GetMaterialLayersFunctions() const` — Getter for the FMaterialLayersFunctions for this customization
- L34 _public function_ `TSharedPtr<IPropertyUtilities> GetPropertyUtilities() const`
- L38 _public prototype_ `void RebuildChildren();`
- L40 _protected function_ `void OnObjectChanged(const FAssetData&)`
- L41 _protected prototype_ `void ResetToDefault();`
- L42 _protected prototype_ `bool IsResetToDefaultVisible() const;`
- L46 _protected function_ `virtual bool RequiresTick() const override` — IDetailCustomNodeBuilder interface
- L47 _protected function_ `virtual void Tick(float DeltaTime) override`
- L48 _protected prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L49 _protected prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L50 _protected function_ `virtual FName GetName() const override`
- L51 _protected function_ `virtual bool InitiallyCollapsed() const override`
- L52 _protected function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override`
- L58 _protected function_ `void OnDetailGroupReset()` — Callback when user click the Group reset button
- L62 _protected prototype_ `FText GetLayerName(int32 Counter) const;` — Returns the user-editable name of a layer within the Material Layers Function
- L65 _protected prototype_ `void OnNameChanged(const FText& InText, ETextCommit::Type CommitInfo, int32 Counter);` — Called when a layer is renamed by the user
- L70 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L72 _private member_ `TSharedPtr<IPropertyHandle> LayerHandle;` — Layer array handle
- L74 _private member_ `TSharedPtr<IPropertyHandle> BlendHandle;` — Blend array handle
- L76 _private member_ `TSharedPtr<IPropertyHandle> SavedStructPropertyHandle;` — Property handle for the FMaterialLayerFunction
- L78 _private member_ `class IDetailLayoutBuilder* SavedLayoutBuilder;` — Layout builder that contains this custom builder
- L80 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;` — Associated FMaterialLayerFunction utilities
- L82 _private member_ `FMaterialLayersFunctions* MaterialLayersFunctions;` — FMaterialLayersFunctions instance this customization is currently editing
- L83 _private member_ `TArray<class IDetailGroup*> DetailGroups;`
- L86 _public prototype_ `FString GetLayerAssetPath(FMaterialParameterInfo InInfo) const;`

#### class `FMaterialLayerFunctionElement`  
`class FMaterialLayerFunctionElement : public IDetailCustomNodeBuilder, public TSharedFromThis< FMaterialLayerFunctionElement >`  
_L89-127_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMaterialLayerFunctionElement>`
- L93 _public prototype_ `FMaterialLayerFunctionElement(FMaterialLayersFunctionsCustomization* InCustomization, TWeakPtr<IPropertyHandle> InPropertyHandle, EMaterialLayerRowType InRowType);`
- L95 _public prototype_ `static void ResetLayerAssetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle, TSharedPtr<IPropertyHandle> InPropertyHandle, FMaterialLayersFunctionsCustomization* InCustomization, int32 InIndex, EMaterialLayerRowType MaterialType);` — Callback when user click the reset button of the material row property
- L97 _public prototype_ `static bool CanResetLayerAssetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle, TSharedPtr<IPropertyHandle> InPropertyHandle, FMaterialLayersFunctionsCustomization* InCustomization, int32 InIndex, EMaterialLayerRowType MaterialType);`
- L101 _public function_ `uint32 GetIndex() const` — Getter for the index of this row
- L102 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L108 _private function_ `virtual bool RequiresTick() const override` — IDetailCustomNodeBuilder interface
- L109 _private function_ `virtual void Tick(float DeltaTime) override`
- L110 _private function_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override`
- L111 _private function_ `virtual FName GetName() const override`
- L112 _private function_ `virtual bool InitiallyCollapsed() const override`
- L113 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override`
- L114 _private function_ `void OnDetailGroupReset()`
- L120 _private member_ `TSharedPtr<IPropertyHandle> RowPropertyHandle;` — The property handle for the property displayed by this row
- L122 _private member_ `FMaterialLayersFunctionsCustomization* ParentCustomization;` — The parent customization that created this row
- L124 _private member_ `EMaterialLayerRowType RowType;` — Whether this row is for a layer or a blend
- L126 _private member_ `int32 Index;` — The array index of this row in the Layers or Blends array

### `Source/Editor/MaterialEditor/Private/MaterialStats.h` (Private)


#### struct `FShaderStatsInfo`  
`struct FShaderStatsInfo`  
_L15-100_
- desc: structure used to store various statistics extracted from compiled shaders
- L23 _public member_ `TMap<ERepresentativeShader, FContent> ShaderInstructionCount;`
- L24 _public member_ `TMap<ERepresentativeShader, FContent> GenericShaderStatistics;`
- L25 _public member_ `FContent SamplersCount;`
- L26 _public member_ `FContent InterpolatorsCount;`
- L27 _public member_ `FContent TextureSampleCount;`
- L28 _public member_ `FContent VirtualTextureLookupCount;`
- L29 _public member_ `FContent VirtualTextureStackCount;`
- L30 _public member_ `FContent ShaderCount;`
- L31 _public member_ `FContent PreShaderCount;`
- L32 _public member_ `FContent LWCUsage;`
- L33 _public member_ `FString StrShaderErrors;`
- L35 _public function_ `void Reset()`
- L67 _public function_ `void Empty()`
- L96 _public function_ `bool HasErrors()`

#### struct `FShaderStatsInfo::FContent`  
`struct FContent`  
_L17-21_
- L19 _public member_ `FString StrDescription;`
- L20 _public member_ `FString StrDescriptionLong;`

#### struct `FMaterialShaderEntry`  
`struct FMaterialShaderEntry`  
_L102-107_
- L104 _public member_ `FShaderId ShaderId;`
- L105 _public member_ `FString ShaderName;`
- L106 _public member_ `FString ShaderFullName;`

#### struct `FShaderPlatformSettings`  
`struct FShaderPlatformSettings`  
_L111-304_
- desc: structure used to manage shader compilation and source code extraction for a specified shader platform used for building the material stats
- L168 _private member_ `FPlatformData PlatformData[EMaterialQualityLevel::Num];` — array of the above defined data structure, for each material quality setting
- L171 _private member_ `EPlatformCategoryType PlatformType;` — type of platform for this material setting (Desktop, Android etc)
- L173 _private member_ `EShaderPlatform PlatformShaderID;` — shader type used for this material setting (eg VULKAN_SM5)
- L175 _private member_ `FName PlatformName;` — The name of the platform given at its creation time (ie the constructor)
- L177 _private member_ `FName PlatformNameID;` — The id of the platform computed from PlatformID
- L179 _private member_ `FString PlatformDescription;`
- L182 _private member_ `bool bPresentInGrid = false;` — if true this will be visible in the material stats. grid
- L185 _private member_ `bool bAlwaysOn = false;` — if true this platform is always present in material stats grid
- L188 _private member_ `bool bAllowCodeView = false;` — if true this will be listed in the 'view code' menu
- L191 _private member_ `bool bAllowPresenceInGrid = false;` — if true this can be added in the stats grid widget to be analyzed
- L194 _private member_ `UMaterial *Material = nullptr;` — pointer to the material whose stats are analyzed
- L196 _private member_ `UMaterialInstance *MaterialInstance = nullptr;` — pointer to the material instance whose stats are analyzed
- L198 _private member_ `TArray<TObjectPtr<UMaterialInstance>> DerivedMaterialInstances;` — array of derived material instances whose stats are analyzed
- L203 _private prototype_ `bool CheckShaders(bool bIgnoreCooldown);` — returns true if shaders are being recompiled, false otherwise
- L206 _private prototype_ `void AllocateMaterialResources();` — builds material resources needed to compile shaders
- L209 _private prototype_ `void ClearResources();` — frees the material resources allocated by AllocateMaterialResources()
- L212 _public prototype_ `FShaderPlatformSettings( const EPlatformCategoryType _PlatformType, const EShaderPlatform _ShaderPlatformID, const FName _Name, const bool _bAllowPresenceInGrid, const bool _bAllowCodeView, const FString& _Description, const bool bAlwaysOn);`
- L220 _public prototype_ `~FShaderPlatformSettings();`
- L223 _public prototype_ `FORCEINLINE FName GetPlatformName() const;` — returns the name of this platform given in the constructor
- L226 _public prototype_ `FORCEINLINE FName GetPlatformID() const;` — retuns the id of this platform as a FName computed by FMaterialStatsUtils::ShaderPlatformTypeName()
- L229 _public prototype_ `FORCEINLINE EPlatformCategoryType GetCategoryType() const;` — returns the type of this platform (desktop, android, ios...)
- L231 _public prototype_ `FORCEINLINE FString GetPlatformDescription() const;`
- L234 _public prototype_ `FORCEINLINE TSharedPtr<class SScrollBox> GetShaderViewerScrollBox(const EMaterialQualityLevel::Type QualityLevel);` — returns the assigned scrollbox used to view shaders for a specific material quality level
- L238 _public prototype_ `FORCEINLINE void SetCodeViewerTab(const EMaterialQualityLevel::Type QualityLevel, TSharedRef<SDockTab> Tab);` — we need this to keep track of opened tabs
- L241 _public prototype_ `FORCEINLINE TWeakPtr<class SDockTab> GetCodeViewerTab(const EMaterialQualityLevel::Type QualityLevel);` — retrives the pointer to the spawned window tab that contains the shader code
- L244 _public prototype_ `FORCEINLINE const TArray<TSharedPtr<FMaterialShaderEntry>> *GetShaderEntries(const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);` — returns an array with the names of all the compiled shaders for this material with specified quality level, can return nullptr if no instance index is not available
- L247 _public prototype_ `void SetExtractStatsFlag(const EMaterialQualityLevel::Type QualityType, const bool bValue);` — when set this flag will indicate the presence of this material with a particular quality level inside the stats widget
- L250 _public prototype_ `FORCEINLINE bool IsCodeViewAllowed() const;` — returns whether or not this material is allowed to display its shader code; set in the contructor
- L252 _public prototype_ `FORCEINLINE bool IsStatsGridPresenceAllowed() const;`
- L255 _public prototype_ `FORCEINLINE void SetCodeViewNeeded(const EMaterialQualityLevel::Type Quality, const bool bValue);` — flag the need to extract and display the shaders generated by this material with a certain quality level
- L258 _public prototype_ `FORCEINLINE bool IsPresentInGrid() const;` — returns whether or not this material was chosen to be displayed in the stats grid widget with any material quality level
- L261 _public prototype_ `FORCEINLINE bool IsAlwaysOn() const;` — returns whether or not this material is always presnet in the stats grid widget
- L264 _public prototype_ `FORCEINLINE bool FlipPresentInGrid();` — used by the grid widget to enable or disable the presence of this material
- L267 _public prototype_ `FORCEINLINE void SetPresentInGrid(const bool bValue);` — used  to enable or disable the presence of this material in the stats grid widget
- L270 _public prototype_ `FORCEINLINE void SetNeedShaderCompilation(const EMaterialQualityLevel::Type QualityLevel, const bool bValue, const bool bOnlyCompileDerivedMI);` — flags shader compilation for a specific quality level
- L273 _public prototype_ `FORCEINLINE EShaderPlatform GetPlatformShaderType() const;` — returns the shader type used by this platform as set at construction time
- L276 _public prototype_ `FORCEINLINE FPlatformData& GetPlatformData(const EMaterialQualityLevel::Type QualityLevel);` — returns a reference to the platform settings used for a specified material quality level; see the definition of FPlatformData inner structure
- L279 _public prototype_ `FORCEINLINE FInstanceData& GetInstanceData(const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);` — returns a reference to the platform instance data used for a specified material quality level and instance index; see the definition of FInstanceData inner structure
- L282 _public prototype_ `FText GetSelectedShaderViewComboText(EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) const;` — returns the shader name chosen in the shader viewer combo-box
- L285 _public prototype_ `void OnShaderViewComboSelectionChanged(TSharedPtr<FMaterialShaderEntry> Item, EMaterialQualityLevel::Type QualityType, const int32 InstanceIndex);` — callback function called when we change the content of the shader viewer combo-box, used to select a different shader to be displayed
- L288 _public prototype_ `FText GetShaderCodeText(const EMaterialQualityLevel::Type QualityType, const int32 InstanceIndex);` — returns the actual shader source selected by the shaders viewer's combo-box
- L291 _public prototype_ `FText GetShaderCountText(const EMaterialQualityLevel::Type QualityType, const int32 InstanceIndex);` — returns the number of shaders in this material w/o compiling shaders
- L294 _public prototype_ `FString GetShadersStats() const;` — returns all shaders' stats concatenated together
- L297 _public prototype_ `void SetMaterial(UMaterial *InBaseMaterial, UMaterialInstance *InBaseMaterialInstance, const TArray<TObjectPtr<UMaterialInstance>>& InDerivedMaterialInstances);` — call this whenever the analyzed material or material instance is changed
- L301 _public prototype_ `bool Update();` — returns true if something changed for this the update call, false otherwise
- L303 _public prototype_ `bool CachePendingShaders();`
- L640 _function_ `FORCEINLINE FShaderPlatformSettings::~FShaderPlatformSettings()` — FShaderPlatformSettings implementation
- L645 _function_ `FORCEINLINE FName FShaderPlatformSettings::GetPlatformName() const`
- L650 _function_ `FORCEINLINE FName FShaderPlatformSettings::GetPlatformID() const`
- L655 _function_ `FORCEINLINE EPlatformCategoryType FShaderPlatformSettings::GetCategoryType() const`
- L660 _function_ `FORCEINLINE FString FShaderPlatformSettings::GetPlatformDescription() const`
- L665 _function_ `FORCEINLINE TSharedPtr<class SScrollBox> FShaderPlatformSettings::GetShaderViewerScrollBox(const EMaterialQualityLevel::Type QualityLevel)`
- L671 _function_ `FORCEINLINE void FShaderPlatformSettings::SetCodeViewerTab(const EMaterialQualityLevel::Type QualityLevel, TSharedRef<SDockTab> Tab)`
- L677 _function_ `FORCEINLINE TWeakPtr<class SDockTab> FShaderPlatformSettings::GetCodeViewerTab(const EMaterialQualityLevel::Type QualityLevel)`
- L683 _function_ `FORCEINLINE const TArray<TSharedPtr<FMaterialShaderEntry>> *FShaderPlatformSettings::GetShaderEntries(const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex)`
- L697 _function_ `FORCEINLINE void FShaderPlatformSettings::SetExtractStatsFlag(const EMaterialQualityLevel::Type QualityType, const bool bValue)`
- L703 _function_ `FORCEINLINE bool FShaderPlatformSettings::IsCodeViewAllowed() const`
- L708 _function_ `FORCEINLINE bool FShaderPlatformSettings::IsStatsGridPresenceAllowed() const`
- L713 _function_ `FORCEINLINE void FShaderPlatformSettings::SetCodeViewNeeded(const EMaterialQualityLevel::Type Quality, const bool bValue)`
- L718 _function_ `FORCEINLINE bool FShaderPlatformSettings::IsPresentInGrid() const`
- L723 _function_ `FORCEINLINE bool FShaderPlatformSettings::IsAlwaysOn() const`
- L728 _function_ `FORCEINLINE bool FShaderPlatformSettings::FlipPresentInGrid()`
- L735 _function_ `FORCEINLINE void FShaderPlatformSettings::SetPresentInGrid(const bool bValue)`
- L757 _function_ `FORCEINLINE void FShaderPlatformSettings::SetNeedShaderCompilation(const EMaterialQualityLevel::Type QualityLevel, const bool bValue, const bool bOnlyCompileDerivedMI)`
- L768 _function_ `FORCEINLINE EShaderPlatform FShaderPlatformSettings::GetPlatformShaderType() const`
- L773 _function_ `FORCEINLINE FShaderPlatformSettings::FPlatformData& FShaderPlatformSettings::GetPlatformData(const EMaterialQualityLevel::Type QualityLevel)`
- L779 _function_ `FORCEINLINE FShaderPlatformSettings::FInstanceData& FShaderPlatformSettings::GetInstanceData(const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex)`

#### struct `FShaderPlatformSettings::FInstanceData`  
`struct FInstanceData`  
_L114-141_
- L118 _public member_ `FMaterialResourceStats* MaterialResourcesStats;` — pointer to the material resource created for this platform mainly used to compile the shaders and extract information from them
- L122 _public member_ `TArray<TSharedPtr<FMaterialShaderEntry>> ArrShaderEntries;` — array of shader ids for this platform; needed to fill ComboBox in MaterialEditor's shader viewer generated from ShaderID.ShaderType->GetFName()
- L125 _public member_ `FMaterialShaderEntry ComboBoxSelectedEntry;` — ComboBox current entry
- L128 _public member_ `bool bUpdateShaderCode = false;` — when true we should update the content of [FText ShaderCode] variable
- L130 _public member_ `FText ShaderCode;` — cached shader code computed by FShaderPlatformSettings::GetShaderCode()
- L132 _public member_ `bool bCompilingShaders = false;` — flag that marks an ongoing shader compilation
- L134 _public member_ `bool bNeedShaderRecompilation = false;` — flag suggests we needed to recompile shaders due to changes in the material
- L136 _public member_ `bool bOnlyCompileMostComplexShader = false;` — flag suggests we only need to compile the most complex shader from available set
- L138 _public member_ `bool bNeedToWarnAboutCompilationErrors = false;` — flag suggests we needed to warn the user due to compilation errors
- L140 _public member_ `FShaderStatsInfo ShaderStatsInfo;`

#### struct `FShaderPlatformSettings::FPlatformData`  
`struct FPlatformData`  
_L145-163_
- desc: inner structure used to hold properties for a single material platform and with a specific quality level
- L148 _public member_ `TArray<FInstanceData> Instances;` — Array of material instances including base material and any material instances derived from it
- L151 _public member_ `bool bExtractStats = false;` — flag that marks the usage of this data structure
- L154 _public member_ `bool bExtractCode = false;` — true when code is listed in its own tab
- L157 _public member_ `TSharedPtr<class SScrollBox> CodeScrollBox;` — object used to display the content of [FText ShaderCode]
- L159 _public member_ `TWeakPtr<class SDockTab> CodeViewerTab;` — weak pointer to the spawned shader code viewer tab
- L162 _public member_ `double LastTimeCompilationRequested = 0.0;` — Time when the previous compilation was requested.

#### class `FMaterialStats`  
`class FMaterialStats : public FGCObject, public TSharedFromThis<FMaterialStats>`  
_L312-545_
- inherits: `FGCObject,TSharedFromThis<FMaterialStats>`
- desc: also manages material stats extraction and stats grid content
- L318 _private member_ `TMapPlatformTypeSettings ShaderPlatformStatsDB;` — maps that contain the collection of all platforms from which we can extract statistics
- L319 _private member_ `TMapPlatformSettings PlatformTypeDB;` — sorted by platform type (desktop, android, ios etc)
- L322 _private member_ `TSharedPtr<class SMaterialEditorStatsWidget> GridStatsWidget;` — pointer to the widget that will display the collected data from all the above platforms
- L323 _private member_ `TSharedPtr<class SWidget> OldStatsWidget;`
- L324 _private member_ `TSharedPtr<class IMessageLogListing> OldStatsListing;`
- L327 _private member_ `TSharedPtr<class FMaterialStatsGrid> StatsGrid;` — pointer to the logical grid that will prepare data to be displayed by the above GridStatsWidget
- L330 _private member_ `bool bArrStatsQualitySelector[EMaterialQualityLevel::Num] = { false };` — array of bools that flag a specific global material quality setting of the stats grid widget
- L331 _private member_ `bool bArrStatsQualitySelectorAlwaysOn[EMaterialQualityLevel::Num] = { false };`
- L334 _private member_ `EMaterialStatsDerivedMIOption MaterialStatsDerivedMIOption = EMaterialStatsDerivedMIOption::CompileOnly;` — inspect all derived material instances also
- L337 _private member_ `TArray<FString> MaterialNames;` — names of the analyzed materials
- L340 _private member_ `static const FName StatsTabId;` — the id of the stats grid widget tab
- L341 _private member_ `static const FName OldStatsTabId;`
- L342 _private member_ `static const FName HLSLCodeTabId;`
- L345 _private member_ `bool bShowStats = false;` — If true, show material stats like number of shader instructions.
- L346 _private member_ `bool bShowOldStats = false;`
- L349 _private member_ `TWeakPtr<SDockTab> StatsTab;` — Tracks whether the code tab is open, so we don't have to update it when closed.
- L350 _private member_ `TWeakPtr<SDockTab> OldStatsTab;`
- L351 _private member_ `TWeakPtr<SDockTab> HLSLTab;`
- L354 _private member_ `FString HLSLCode;` — Cached HLSL code for analyzed material
- L357 _private member_ `FString PreviousTranslatorHLSLCode;` — If the new translator is enabled this will contain the source for the old translator.  Useful for comparing.
- L360 _private member_ `FString MaterialIR;` — Cached IR from the new translator if enabled
- L362 _private member_ `TObjectPtr<class UMaterialStatsOptions >Options = nullptr;`
- L365 _private member_ `class IMaterialEditor *MaterialEditor = nullptr;` — Pointer to Material Editor or to Material Instance Editor set by Initialize() function
- L368 _private member_ `class UMaterialInterface *MaterialInterface = nullptr;` — pointer to the material interface whose stats are analyzed
- L371 _private member_ `TArray<TObjectPtr<UMaterialInstance>> DerivedMaterialInstances;` — array of pointers to derived material instances whose stats are analyzed
- L374 _private member_ `TArray<FString> LastGridMessages;` — grid warning messages
- L375 _private member_ `double LastGridMessagesUpdate = 0.0;`
- L377 _private member_ `bool bNeedsGridRefresh = false;`
- L379 _private member_ `TMulticastDelegate<void()> RefreshDependentTabs;`
- L381 _private member_ `TSharedPtr<FHLSLSyntaxHighlighterMarshaller> SyntaxHighlighter;`
- L385 _private prototype_ `TSharedPtr<FShaderPlatformSettings> AddShaderPlatform(const EPlatformCategoryType PlatformType, const EShaderPlatform PlatformID, const FName PlatformName, const bool bAllowCodeView, const FString& Description, const bool bAlwaysOn = false);` — adds a specified platform in the grid widget for analysis; usually called from BuildShaderPlatformDB()
- L388 _private prototype_ `void BuildShaderPlatformDB(const bool bAllowIgnoringCompilationErrors);` — build a collection of available shader platform for which we can extract various statistics
- L391 _private prototype_ `TSharedRef<class SDockTab> SpawnTab_ShaderCode(const class FSpawnTabArgs& Args, const EShaderPlatform PlatformID, const EMaterialQualityLevel::Type QualityType, const int32 InstanceIndex);` — this will spawn the window that will display the a specific set of shaders from the analyzed material
- L392 _private prototype_ `TSharedRef<class SDockTab> SpawnTab_HLSLCode(const class FSpawnTabArgs& Args);`
- L394 _private prototype_ `TSharedRef<SWidget> BuildShaderCodeWidget(FText TextLabel, TFunction<FText(void)>&& InShaderCodeCallback, TFunction<FReply(void)>&& InCopyCodeCallback, TAttribute<EVisibility> InVisibilityAttribute);`
- L397 _private prototype_ `static FName MakeTabName(const EPlatformCategoryType PlatformType, const EShaderPlatform ShaderPlatformType, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);` — utility function used to build names for the shader viewing tabs
- L400 _private prototype_ `void BuildStatsTab();` — functions responsible for construction and spawning of the window that will display the stats grid widget
- L401 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Stats(const FSpawnTabArgs& Args);`
- L403 _private prototype_ `void BuildOldStatsTab();`
- L404 _private prototype_ `TSharedRef<SDockTab> SpawnTab_OldStats(const FSpawnTabArgs& Args);`
- L407 _private prototype_ `void BuildViewShaderCodeMenus();` — adds shader view menus for the given IMaterialEditor
- L410 _private prototype_ `void ToggleStats();` — displays or hides the window that displays the stats grid widget
- L411 _private prototype_ `void ToggleOldStats();`
- L412 _private prototype_ `void SetShowStats(const bool bValue);`
- L413 _private prototype_ `void SetShowOldStats(const bool bValue);`
- L416 _private prototype_ `void SetShaderPlatformUseCodeView(const EShaderPlatform PlatformID, const EMaterialQualityLevel::Type Quality, const bool bValue);` — wrapper function that calls SetCodeViewNeeded on the specified platform to signal the need (or not) to extract compile its shaders and extract the source code
- L419 _private prototype_ `bool IsCodeViewWindowActive() const;` — checks if there are any opened windows that display shader code
- L422 _private prototype_ `FORCEINLINE bool IsShowingStats() const;` — true when we are displaying any content in the stats grid widget
- L423 _private prototype_ `FORCEINLINE bool IsShowingOldStats() const;`
- L426 _private prototype_ `void RefreshStatsGrid();` — triggers and refresh call for the stats grid widget
- L428 _private prototype_ `void DisplayStatsGrid(const bool bShow);` — this will display/hide the stats grid widget
- L429 _private prototype_ `void DisplayOldStats(const bool bShow);`
- L431 _private prototype_ `void LoadSettings(const bool bAllowIgnoringCompilationErrors);`
- L432 _private prototype_ `void SaveSettings();`
- L436 _private prototype_ `void ComputeGridWarnings();` — the actual display is handled by the SMaterialEditorStatsWidget class
- L439 _private prototype_ `void ExtractHLSLCode();` — extracts the HLSL code for analyzed material
- L442 _private function_ `FMaterialStats()` — use FMaterialStatsUtils::CreateMaterialStats() to create an instance of this class
- L444 _public prototype_ `~FMaterialStats();`
- L449 _public prototype_ `static FORCEINLINE FName GetGridStatsTabName();` — return the name of the window that displays the grid stats widget
- L450 _public prototype_ `static FORCEINLINE FName GetGridOldStatsTabName();`
- L453 _public prototype_ `FORCEINLINE FString GetMaterialName(const int32 InstanceIndex) const;` — returns the material name we're analyzing
- L456 _public prototype_ `FORCEINLINE TSharedPtr<class SMaterialEditorStatsWidget> GetGridStatsWidget();` — returns a pointer to the material stats grid widget
- L459 _public prototype_ `FORCEINLINE const TMapPlatformTypeSettings& GetPlatformsDB() const;` — functions that return references to the collection of stored platforms that analyze the current material
- L460 _public prototype_ `FORCEINLINE const TMapPlatformSettings& GetPlatformsTypeDB() const;`
- L462 _public prototype_ `FORCEINLINE TSharedPtr<FMaterialStatsGrid> GetStatsGrid();`
- L464 _public prototype_ `FORCEINLINE TSharedPtr<class IMessageLogListing> GetOldStatsListing();`
- L467 _public prototype_ `bool SwitchStatsQualityFlag(const EMaterialQualityLevel::Type Quality);` — functions used to query or set a material quality level that is to be analyzed in the material stats grid widget
- L468 _public prototype_ `void SetStatusQualityFlag(const EMaterialQualityLevel::Type Quality, const bool bValue);`
- L469 _public prototype_ `FORCEINLINE bool GetStatsQualityFlag(const EMaterialQualityLevel::Type Quality);`
- L470 _public prototype_ `FORCEINLINE bool GetStatsQualityFlagAlwaysOn(const EMaterialQualityLevel::Type Quality);`
- L472 _public prototype_ `void SetMaterialStatsDerivedMIOption(const EMaterialStatsDerivedMIOption value);`
- L473 _public prototype_ `FORCEINLINE EMaterialStatsDerivedMIOption GetMaterialStatsDerivedMIOption() const;`
- L474 _public prototype_ `FORCEINLINE bool GetProvideDerivedMIFlag() const;`
- L477 _public prototype_ `bool SwitchShaderPlatformUseStats(const EShaderPlatform PlatformID);` — switches on or off the presence of a specified shader platform inside the stats grid widget for this material
- L480 _public prototype_ `void SetMaterialsDisplayNames(const TArray<FString>& Names);` — Sets the name of the material that will be displayed in the stats grid widget
- L483 _public prototype_ `FName GetPlatformName(const EShaderPlatform InEnumValue) const;` — returns a platform name given at its construction time
- L486 _public prototype_ `EShaderPlatform GetShaderPlatformID(const FName InName) const;` — returns the shader type used by a platform with the specified name
- L489 _public prototype_ `TSharedPtr<FShaderPlatformSettings> GetPlatformSettings(const EShaderPlatform PlatformID);` — utility functions that return pointers to the requested platforms
- L490 _public prototype_ `TSharedPtr<FShaderPlatformSettings> GetPlatformSettings(const FName PlatformName);`
- L493 _public prototype_ `FText GetShaderCodeText(const EShaderPlatform PlatformID, const EMaterialQualityLevel::Type QualityType, const int32 InstanceIndex);` — returns the shader code computed by the specified platform with some quality level
- L496 _public prototype_ `FText GetShaderCountText(const EShaderPlatform PlatformID, const EMaterialQualityLevel::Type QualityType, const int32 InstanceIndex);` — returns the number of shaders in the material with the specified platform with some quality level.  Does this without compiling shaders.
- L499 _public prototype_ `FString GetShadersStats() const;` — returns all shaders' stats concatenated together
- L502 _public prototype_ `void SignalMaterialChanged();` — call this whenever some material property is changed, as it will trigger shader recompilation
- L505 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L506 _public function_ `virtual FString GetReferencerName() const override`
- L516 _public prototype_ `void RegisterTabs();` — call this from chosen IMaterialEditor, when all other tabs are registered, to add the material stats grid tab and shader view menus
- L519 _public prototype_ `void UnregisterTabs();` — call this from chosen IMaterialEditor, when all other tabs are unregistered, to remove material stats grid tab and shader view menus
- L523 _private prototype_ `void Initialize(IMaterialEditor *MaterialEditor, const bool bShowMaterialInstancesMenu, const bool bAllowIgnoringCompilationErrors);` — this function will do the setup procedure and its called from FMaterialStatsUtils::CreateMaterialStats()
- L531 _public prototype_ `void Update();` — call this from chosen IMaterialEditor whenever an update to this analysis tool in appropriate
- L534 _public prototype_ `void CacheAndCompilePendingShaders();` — call this to request caching required shaders regardless of cooldown
- L537 _public prototype_ `void SetMaterial(UMaterial *InMaterial, const TArray<TObjectPtr<UMaterialInstance>>& InDerivedMaterialInstances);` — this will set the material or material instance to be analyzed by this class
- L538 _public prototype_ `void SetMaterial(UMaterialInstance *InMaterialInstance);`
- L544 _public prototype_ `bool AnyNewCompilationErrors(const int32 StartingFromInstanceIndex = 0);` — returns true if any new compilation errors are discovered
- L551 _function_ `FORCEINLINE const TMapPlatformTypeSettings& FMaterialStats::GetPlatformsDB() const`
- L556 _function_ `FORCEINLINE const TMapPlatformSettings& FMaterialStats::GetPlatformsTypeDB() const`
- L561 _function_ `FORCEINLINE TSharedPtr<FMaterialStatsGrid> FMaterialStats::GetStatsGrid()`
- L566 _function_ `FORCEINLINE TSharedPtr<class IMessageLogListing> FMaterialStats::GetOldStatsListing()`
- L571 _function_ `FORCEINLINE bool FMaterialStats::IsShowingStats() const`
- L576 _function_ `FORCEINLINE bool FMaterialStats::IsShowingOldStats() const`
- L581 _function_ `FORCEINLINE void FMaterialStats::SetMaterialsDisplayNames(const TArray<FString>& Names)`
- L586 _function_ `FORCEINLINE FString FMaterialStats::GetMaterialName(const int32 InstanceIndex) const`
- L598 _function_ `FORCEINLINE FName FMaterialStats::GetGridStatsTabName()`
- L603 _function_ `FORCEINLINE FName FMaterialStats::GetGridOldStatsTabName()`
- L608 _function_ `FORCEINLINE bool FMaterialStats::GetStatsQualityFlag(const EMaterialQualityLevel::Type Quality)`
- L614 _function_ `FORCEINLINE bool FMaterialStats::GetStatsQualityFlagAlwaysOn(const EMaterialQualityLevel::Type Quality)`
- L620 _function_ `FORCEINLINE EMaterialStatsDerivedMIOption FMaterialStats::GetMaterialStatsDerivedMIOption() const`
- L625 _function_ `FORCEINLINE bool FMaterialStats::GetProvideDerivedMIFlag() const`
- L630 _function_ `FORCEINLINE TSharedPtr<class SMaterialEditorStatsWidget> FMaterialStats::GetGridStatsWidget()`

#### Free symbols / members of external scopes

- L307 _typedef_ `using TMapPlatformSettings = TMap<EPlatformCategoryType, TArray<TSharedPtr<FShaderPlatformSettings>>>;` — name alias used bellow in FMaterialStats
- L308 _typedef_ `using TMapPlatformTypeSettings = TMap<EShaderPlatform, TSharedPtr<FShaderPlatformSettings>>;`

### `Source/Editor/MaterialEditor/Private/MaterialStatsGrid.h` (Private)


#### class `FGridCell`  
`class FGridCell`  
_L15-57_
- desc: class to represent a single cell inside the material stats grid
- L26 _protected member_ `FSlateColor CellColor;` — attributes used at display time to configure widgets
- L27 _protected member_ `bool bBoldContent = false;`
- L29 _protected member_ `EHorizontalAlignment HAlignment = EHorizontalAlignment::HAlign_Center;`
- L30 _protected member_ `EVerticalAlignment VAlignment = EVerticalAlignment::VAlign_Center;`
- L33 _public prototype_ `FGridCell();`
- L34 _public prototype_ `virtual ~FGridCell() = default;`
- L37 _public prototype_ `virtual FString GetCellContent() = 0;` — returns the main content of this cell
- L39 _public prototype_ `virtual FString GetCellContentLong() = 0;` — this can be used for tool tips or other detailed descriptions
- L41 _public prototype_ `FORCEINLINE FSlateColor GetColor() const;`
- L42 _public prototype_ `FORCEINLINE void SetColor(const FSlateColor& Color);`
- L44 _public prototype_ `FORCEINLINE bool IsContentBold() const;`
- L45 _public prototype_ `FORCEINLINE void SetContentBold(bool bValue);`
- L47 _public prototype_ `virtual EHorizontalAlignment GetHorizontalAlignment();`
- L48 _public prototype_ `FORCEINLINE void SetHorizontalAlignment(EHorizontalAlignment Align);`
- L50 _public prototype_ `FORCEINLINE EVerticalAlignment GetVerticalAlignment() const;`
- L51 _public prototype_ `FORCEINLINE void SetVerticalAlignment(EVerticalAlignment Align);`
- L53 _public function_ `virtual EIcon GetIcon() const`
- L435 _function_ `FORCEINLINE FSlateColor FGridCell::GetColor() const`
- L440 _function_ `FORCEINLINE void FGridCell::SetColor(const FSlateColor& Color)`
- L445 _function_ `FORCEINLINE bool FGridCell::IsContentBold() const`
- L450 _function_ `FORCEINLINE void FGridCell::SetContentBold(bool bValue)`
- L455 _function_ `FORCEINLINE EHorizontalAlignment FGridCell::GetHorizontalAlignment()`
- L460 _function_ `FORCEINLINE void FGridCell::SetHorizontalAlignment(EHorizontalAlignment Align)`
- L465 _function_ `FORCEINLINE EVerticalAlignment FGridCell::GetVerticalAlignment() const`
- L470 _function_ `FORCEINLINE void FGridCell::SetVerticalAlignment(EVerticalAlignment Align)`

#### enum `FGridCell::EIcon`  
`enum class EIcon`  
_L18-22_
- L20 _public enumerator_ `None`
- L21 _public enumerator_ `Error`

#### class `FGridCell_Empty`  
`class FGridCell_Empty : public FGridCell`  
_L60-65_
- inherits: `FGridCell`
- desc: this time of cell with just return an empty string and its mainly used to separate rows
- L63 _public prototype_ `FString GetCellContent() override;`
- L64 _public prototype_ `FString GetCellContentLong() override;`

#### class `FGridCell_StaticString`  
`class FGridCell_StaticString : public FGridCell`  
_L68-78_
- inherits: `FGridCell`
- desc: cell that stores & returns a simple static string
- L70 _private member_ `FString Content;`
- L71 _private member_ `FString ContentLong;`
- L74 _public prototype_ `FGridCell_StaticString(const FString& _Content, const FString& _ContentLong);`
- L76 _public prototype_ `FString GetCellContent() override;`
- L77 _public prototype_ `FString GetCellContentLong() override;`

#### enum `EShaderInfoType`  
`enum class EShaderInfoType`  
_L81-94_
- desc: enumeration used to classify arguments for FGridCell_ShaderValue
- L83 _public enumerator_ `Name`
- L84 _public enumerator_ `InstructionsCount`
- L85 _public enumerator_ `SamplersCount`
- L86 _public enumerator_ `InterpolatorsCount`
- L87 _public enumerator_ `TextureSampleCount`
- L88 _public enumerator_ `VirtualTextureLookupCount`
- L89 _public enumerator_ `VirtualTextureStackCount`
- L90 _public enumerator_ `ShaderCount`
- L91 _public enumerator_ `PreShaderCount`
- L92 _public enumerator_ `LWCUsage`
- L93 _public enumerator_ `GenericShaderStatistics`

#### class `FGridCell_ShaderValue`  
`class FGridCell_ShaderValue : public FGridCell`  
_L97-117_
- inherits: `FGridCell`
- desc: this type of cell will query certain type of informations from the material
- L100 _private member_ `TWeakPtr<class FMaterialStats> MaterialStatsWPtr;`
- L102 _private member_ `EShaderInfoType InfoType;`
- L103 _private member_ `ERepresentativeShader ShaderType;`
- L104 _private member_ `EMaterialQualityLevel::Type QualityLevel;`
- L105 _private member_ `EShaderPlatform PlatformType;`
- L106 _private member_ `int32 InstanceIndex;`
- L108 _private prototype_ `FString InternalGetContent(bool bLongContent);`
- L111 _public prototype_ `FGridCell_ShaderValue(const TWeakPtr<FMaterialStats>& _MaterialStatsWPtr, const EShaderInfoType _InfoType, const ERepresentativeShader _ShaderType, const EMaterialQualityLevel::Type _QualityLevel, const EShaderPlatform _PlatformType, const int32 _InstanceIndex);`
- L114 _public prototype_ `FString GetCellContent() override;`
- L115 _public prototype_ `FString GetCellContentLong() override;`
- L116 _public prototype_ `EIcon GetIcon() const override;`

#### class `FStatsGridRow`  
`class FStatsGridRow`  
_L120-150_
- desc: virtual class to model grid row generation
- L124 _protected member_ `TMap<FName, TSharedPtr<FGridCell>> RowCells;` — key is column name
- L127 _protected prototype_ `void AddCell(FName ColumnName, TSharedPtr<FGridCell> Cell);`
- L128 _protected prototype_ `void RemoveCell(FName ColumnName);`
- L131 _protected prototype_ `void FillPlatformCellsHelper(TSharedPtr<FMaterialStats> StatsManager);` — helper function that will loop through all platforms present in the grid and attempt to build their columns by calling AddPlatform() function
- L134 _public function_ `FStatsGridRow()`
- L135 _public prototype_ `virtual ~FStatsGridRow() = default;`
- L138 _public prototype_ `virtual void CreateRow(TSharedPtr<FMaterialStats> StatsManager) = 0;` — this function should generate all needed cells
- L141 _public prototype_ `virtual void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> PlatformPtr, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) = 0;` — Add/RemovePlatforms should be called when a platform is added or removed from the grid
- L142 _public prototype_ `virtual void RemovePlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> PlatformPtr, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);`
- L144 _public prototype_ `TSharedPtr<FGridCell> GetCell(const FName ColumnName);`
- L146 _public function_ `void RemoveAll()`

#### class `FStatsGridRow_Empty`  
`class FStatsGridRow_Empty : public FStatsGridRow`  
_L153-159_
- inherits: `FStatsGridRow`
- desc: separator row
- L156 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L158 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_Name`  
`class FStatsGridRow_Name : public FStatsGridRow`  
_L162-168_
- inherits: `FStatsGridRow`
- desc: material/instance name
- L165 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L167 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_Quality`  
`class FStatsGridRow_Quality : public FStatsGridRow`  
_L171-177_
- inherits: `FStatsGridRow`
- desc: row that will produce static string from EMaterialQualityLevel::Type
- L174 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L176 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_Shaders`  
`class FStatsGridRow_Shaders : public FStatsGridRow`  
_L180-207_
- inherits: `FStatsGridRow`
- desc: row that will extract and the number of instructions for each used shader
- L192 _private member_ `bool bIsHeaderRow = false;` — if this is true it will add a text in the 'description' column with 'fragment/vertex shader' text
- L194 _private member_ `bool bInstructionRow = true;`
- L197 _private member_ `ERepresentativeShader ShaderType;` — EShaderType ShaderType;
- L199 _private prototype_ `EShaderClass GetShaderClass(const ERepresentativeShader Shader);`
- L202 _public prototype_ `FStatsGridRow_Shaders(ERepresentativeShader RepresentativeShader, bool bHeader, bool bInstructionRow);`
- L204 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L206 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### enum `FStatsGridRow_Shaders::EShaderClass`  
`enum class EShaderClass`  
_L183-188_
- L185 _public enumerator_ `VertexShader`
- L186 _public enumerator_ `FragmentShader`
- L187 _public enumerator_ `ComputeShader`

#### class `FStatsGridRow_Samplers`  
`class FStatsGridRow_Samplers : public FStatsGridRow`  
_L210-216_
- inherits: `FStatsGridRow`
- desc: this row will display the global number of samplers present in the material for a specified platform
- L213 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L215 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_Interpolators`  
`class FStatsGridRow_Interpolators : public FStatsGridRow`  
_L219-225_
- inherits: `FStatsGridRow`
- desc: this row will display the global number of interpolators present in the material for a specified platform
- L222 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L224 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_NumTextureSamples`  
`class FStatsGridRow_NumTextureSamples : public FStatsGridRow`  
_L228-234_
- inherits: `FStatsGridRow`
- desc: this row will display the global number of texture samples present in the material for a specified platform
- L231 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L233 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_NumVirtualTextureLookups`  
`class FStatsGridRow_NumVirtualTextureLookups : public FStatsGridRow`  
_L237-243_
- inherits: `FStatsGridRow`
- desc: this row will display the global number of virtual texture lookups present in the material for a specified platform
- L240 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L242 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_NumVirtualTextureStacks`  
`class FStatsGridRow_NumVirtualTextureStacks : public FStatsGridRow`  
_L246-252_
- inherits: `FStatsGridRow`
- desc: this row will display the global number of virtual texture stacks present in the material for a specified platform
- L249 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L251 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_NumShaders`  
`class FStatsGridRow_NumShaders : public FStatsGridRow`  
_L255-261_
- inherits: `FStatsGridRow`
- desc: this row will display the total number of shaders present in the material for a specified platform
- L258 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L260 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_NumPreshaders`  
`class FStatsGridRow_NumPreshaders : public FStatsGridRow`  
_L264-270_
- inherits: `FStatsGridRow`
- desc: this row will display the total number of shaders present in the material for a specified platform
- L267 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L269 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FStatsGridRow_LWCUsage`  
`class FStatsGridRow_LWCUsage : public FStatsGridRow`  
_L273-279_
- inherits: `FStatsGridRow`
- desc: this row will display the LWC usage in the material for a specified platform
- L276 _public prototype_ `void CreateRow(TSharedPtr<FMaterialStats> StatsManager) override;`
- L278 _public prototype_ `void AddPlatform(TSharedPtr<FMaterialStats> StatsManager, const TSharedPtr<FShaderPlatformSettings> Platform, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex) override;`

#### class `FMaterialStatsGrid`  
`class FMaterialStatsGrid`  
_L282-405_
- desc: class that models the logical material stats grid
- L315 _private member_ `TMap<ERowType, TSharedPtr<FStatsGridRow>> StaticRows;` — collection of row object that will not change as shader platforms are added or removed
- L317 _private member_ `TArray<TSharedPtr<FStatsGridRow>> VertexShaderRows;` — array of shader columns that vary with the number of shaders present in each analyzed material
- L318 _private member_ `TArray<TSharedPtr<FStatsGridRow>> FragmentShaderRows;`
- L329 _private member_ `TMap<FName, FColumnInfo> GridColumnContent;` — collection of column information sorted by their names
- L335 _private member_ `TArray<TSharedPtr<int32>> RowIDs;` — array feed into a SListView used by GridStatsWidget each entry is a pointer to the id of each row inside the grid the ids are assembled/disassabled with AssembleRowKey()/DissasambleRowKey()
- L338 _private member_ `TWeakPtr<class FMaterialStats> StatsManagerWPtr;` — pointer to stats manager who will actually create an instance of this class
- L341 _private member_ `TStaticArray<bool, (int32)ERepresentativeShader::Num> UsedShaders;` — helper array that mark the presence or absence of each type of shader (ERepresentativeShader) in the analyzed material
- L345 _private member_ `EGlobalErrorsType PlatformErrorsType;` — this will be updated every time a shader is compiled
- L348 _public member_ `const static FName DescriptorColumnName;`
- L349 _public member_ `const static FName ShaderColumnName;`
- L350 _public member_ `const static FName ShaderStatisticColumnName;`
- L353 _private prototype_ `void AddColumnInfo(TSharedPtr<FShaderPlatformSettings> PlatformPtr, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);`
- L354 _private prototype_ `void RemoveColumnInfo(TSharedPtr<FShaderPlatformSettings> PlatformPtr, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);`
- L357 _private prototype_ `void BuildColumnInfo();` — this function will go through all available shader platforms and will call build the content of GridColumnContent
- L361 _private prototype_ `void BuildShaderRows();` — BuildShaderRows will be called after each shader compilation
- L362 _private prototype_ `void BuildStaticRows();`
- L364 _private prototype_ `void CheckForErrors();`
- L367 _private prototype_ `void CollectShaderInfo(const TSharedPtr<FShaderPlatformSettings>& PlatformPtr, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);` — this functions will build the content of UsedShaders array
- L368 _private prototype_ `void CollectShaderInfo();`
- L371 _private prototype_ `void BuildKeyAndInsert(const ERowType RowType, int16 Index = 0);` — functions that build the row ids array used by GridStatsWidget to identify available rows inside this logical grid
- L372 _private prototype_ `void BuildRowIds();`
- L375 _private prototype_ `FORCEINLINE int32 AssembleRowKey(const ERowType RowType, const int16 Index);` — helper functions to create an ID for each row
- L376 _private prototype_ `FORCEINLINE void DissasambleRowKey(ERowType& RowType, int32& Index, const int32 Key);`
- L378 _private prototype_ `void AddOrRemovePlatform(TSharedPtr<FShaderPlatformSettings> PlatformPtr, const bool bAdd, const EMaterialQualityLevel::Type QualityLevel, const int32 InstanceIndex);`
- L381 _public prototype_ `FMaterialStatsGrid(TWeakPtr<FMaterialStats> _StatsManager);`
- L382 _public prototype_ `~FMaterialStatsGrid();`
- L384 _public prototype_ `TSharedPtr<FGridCell> GetCell(int32 RowID, FName ColumnName);`
- L386 _public prototype_ `FORCEINLINE const TArray<TSharedPtr<int32>>* GetGridRowIDs() const;`
- L388 _public prototype_ `FORCEINLINE TArray<FName> GetVisibleColumnNames() const;`
- L390 _public prototype_ `void OnShaderChanged();`
- L391 _public prototype_ `void OnColumnNumChanged();`
- L393 _public prototype_ `void OnAddOrRemovePlatform(TSharedPtr<FShaderPlatformSettings> PlatformPtr);`
- L394 _public prototype_ `void OnQualitySettingChanged(const EMaterialQualityLevel::Type QualityLevel);`
- L397 _public prototype_ `void BuildGrid();` — call to build the content of this grid
- L399 _public prototype_ `FString GetColumnContent(const FName ColumnName) const;`
- L400 _public prototype_ `FString GetColumnContentLong(const FName ColumnName) const;`
- L401 _public prototype_ `FSlateColor GetColumnColor(const FName ColumnName) const;`
- L404 _public prototype_ `static FName MakePlatformColumnName(const TSharedPtr<FShaderPlatformSettings>& Platform, const EMaterialQualityLevel::Type Quality, const int32 InstanceIndex);` — helper function that will assemble a column name from the given arguments
- L409 _function_ `FORCEINLINE const TArray<TSharedPtr<int32>> *FMaterialStatsGrid::GetGridRowIDs() const` — FShaderStatsGrid implementation
- L414 _function_ `FORCEINLINE int32 FMaterialStatsGrid::AssembleRowKey(const ERowType RowType, const int16 Index)`
- L420 _function_ `FORCEINLINE void FMaterialStatsGrid::DissasambleRowKey(ERowType& RowType, int32& Index, const int32 Key)`
- L426 _function_ `FORCEINLINE TArray<FName> FMaterialStatsGrid::GetVisibleColumnNames() const`

#### enum `FMaterialStatsGrid::EGlobalErrorsType`  
`enum class EGlobalErrorsType`  
_L285-293_
- desc: enum used whether any shader platform reported errors
- L288 _public enumerator_ `NoErrors` — no errors at all
- L290 _public enumerator_ `SpecificPlatformErrors` — there are some platform specific errors
- L292 _public enumerator_ `GlobalPlatformErrors` — all platforms have errors

#### enum `FMaterialStatsGrid::ERowType`  
`enum class ERowType`  
_L296-312_
- desc: enum used to differentiate between various row types
- L298 _public enumerator_ `Empty`
- L299 _public enumerator_ `Name`
- L300 _public enumerator_ `Quality`
- L301 _public enumerator_ `Samplers`
- L302 _public enumerator_ `Interpolators`
- L303 _public enumerator_ `TextureSamples`
- L304 _public enumerator_ `VirtualTextureLookups`
- L305 _public enumerator_ `VirtualTextureStacks`
- L306 _public enumerator_ `Shaders`
- L307 _public enumerator_ `PreShaders`
- L308 _public enumerator_ `LWCUsage`
- L310 _public enumerator_ `VertexShader`
- L311 _public enumerator_ `FragmentShader`

#### struct `FMaterialStatsGrid::FColumnInfo`  
`struct FColumnInfo`  
_L321-326_
- desc: this structure will held additional informations about the columns of this grid, needed at display time
- L323 _public member_ `FString Content = TEXT("");`
- L324 _public member_ `FString ContentLong = TEXT("");`
- L325 _public member_ `FSlateColor Color = FStyleColors::Foreground;`

### `Source/Editor/MaterialEditor/Private/SMaterialEditorCustomPrimitiveDataWidget.h` (Private)


#### struct `FCustomPrimitiveDataRowData`  
`struct FCustomPrimitiveDataRowData`  
_L21-29_
- desc: Data for a row in the list of custom primitive data entries
- L23 _public function_ `FCustomPrimitiveDataRowData(int32 InSlot, FString InName, float InPreviewValue, bool bInIsDuplicate = false) : Slot(InSlot), Name(InName), PreviewValue(InPreviewValue), bIsDuplicate(bInIsDuplicate)`
- L25 _public member_ `int32 Slot = 0;`
- L26 _public member_ `FString Name = "";`
- L27 _public member_ `float PreviewValue = 0.0f;`
- L28 _public member_ `bool bIsDuplicate = false;`

#### class `SMaterialCustomPrimitiveDataPanel`  
`class SMaterialCustomPrimitiveDataPanel : public SCompoundWidget`  
_L31-77_
- inherits: `SCompoundWidget`
- L34 _public function_ `SLATE_BEGIN_ARGS(SMaterialCustomPrimitiveDataPanel)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, IMaterialEditor* MaterialEditor, UMaterialEditorPreviewParameters* InMaterialEditorInstance);`
- L39 _public function_ `void SetEditorInstance(UMaterialEditorPreviewParameters* InMaterialEditorInstance)`
- L43 _private prototype_ `void Refresh();`
- L45 _private prototype_ `void RefreshCustomPrimitiveData();`
- L47 _private prototype_ `TArray<float> MakeCustomPrimitiveFloatData() const;`
- L50 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FCustomPrimitiveDataRowData> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Adds a new textbox with the string to the list
- L53 _private prototype_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when a mouse button is down in the table area
- L56 _private prototype_ `void ClearPreviewValues();` — Clears all the preview values
- L59 _private prototype_ `void CopyDefaultToPreviewValues();` — Copies all the default node values to the preview values.
- L62 _private member_ `TArray<TSharedPtr<FCustomPrimitiveDataRowData>> Items;` — The list of strings
- L65 _private member_ `TSharedPtr<SListView<TSharedPtr<FCustomPrimitiveDataRowData>>> ListViewWidget;` — The actual UI list
- L67 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L70 _private member_ `bool bUsePreviewValues = true;` — When enabled the preview values will be set as custom primitive data.
- L73 _private member_ `IMaterialEditor* MaterialEditor = nullptr;` — Pointer to the material editor interface
- L76 _private member_ `UMaterialEditorPreviewParameters* MaterialEditorInstance;` — The set of material parameters this is associated with

### `Source/Editor/MaterialEditor/Private/SMaterialEditorStatsWidget.h` (Private)


#### class `SMaterialEditorStatsWidget`  
`class SMaterialEditorStatsWidget : public SCompoundWidget`  
_L17-97_
- inherits: `SCompoundWidget`
- desc: Widget class used to display stats extracted from materials; used in the material editor
- L20 _public function_ `SLATE_BEGIN_ARGS(SMaterialEditorStatsWidget) : _MaterialStatsWPtr(nullptr) , _ShowMaterialInstancesMenu(true) , _AllowIgnoringCompilationErrors(true)`
- L26 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FMaterialStats>, MaterialStatsWPtr) SLATE_ARGUMENT(bool, ShowMaterialInstancesMenu) SLATE_ARGUMENT(bool, AllowIgnoringCompilationErrors) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `TSharedRef<ITableRow> MakeMaterialInfoWidget(const TSharedPtr<int32> Item, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback used to populate SListView
- L37 _public prototype_ `void RequestRefresh();` — Request a refresh of the list view
- L39 _public prototype_ `void AddMessage(const FString& Message, const bool bIsError);`
- L40 _public prototype_ `void ClearMessages();`
- L42 _public prototype_ `void FillWarningMessages();`
- L44 _public prototype_ `static FName GetRegularFontStyleName();`
- L45 _public prototype_ `static FName GetBoldFontStyleName();`
- L47 _public prototype_ `void OnColumnNumChanged();`
- L50 _private prototype_ `void RebuildColumns();`
- L51 _private prototype_ `uint32 CountSubPlatforms(EPlatformCategoryType Category) const;`
- L52 _private prototype_ `void AddColumn(const FName ColumnName);`
- L53 _private prototype_ `void InsertColumnAfter(const FName ColumnName, const FName PreviousColumn);`
- L54 _private prototype_ `void RemoveColumn(const FName ColumnName);`
- L56 _private prototype_ `SHeaderRow::FColumn::FArguments CreateColumnArgs(const FName ColumnName);`
- L58 _private prototype_ `float GetColumnSize(const FName ColumnName) const;`
- L60 _private prototype_ `TSharedRef<SWidget> GetSettingsButtonContent();`
- L62 _private prototype_ `void CreatePlatformMenus(class FMenuBuilder& Builder, EPlatformCategoryType Category);`
- L63 _private prototype_ `void CreatePlatformCategoryMenus(class FMenuBuilder& Builder);`
- L65 _private prototype_ `static FText MaterialStatsDerivedMIOptionToDescription(const EMaterialStatsDerivedMIOption Option);`
- L67 _private prototype_ `void CreateQualityMenus(class FMenuBuilder& Builder);`
- L68 _private prototype_ `void CreateDerivedMaterialsMenu(class FMenuBuilder& Builder);`
- L69 _private prototype_ `void CreateGlobalQualityMenu(class FMenuBuilder& Builder);`
- L71 _private prototype_ `void OnFlipQualityState(const ECheckBoxState NewState, const EMaterialQualityLevel::Type QualitySetting);`
- L73 _private prototype_ `TSharedPtr<SWidget> BuildMessageArea();`
- L75 _private prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L78 _protected member_ `static const float ColumnSizeSmall;`
- L79 _protected member_ `static const float ColumnSizeMedium;`
- L80 _protected member_ `static const float ColumnSizeLarge;`
- L81 _protected member_ `static const float ColumnSizeExtraLarge;`
- L83 _protected member_ `static const FName RegularFontStyle;`
- L84 _protected member_ `static const FName BoldFontStyle;`
- L86 _protected member_ `TSharedPtr<SVerticalBox> MessageBoxWidget;`
- L88 _protected member_ `TWeakPtr<FMaterialStats> MaterialStatsWPtr;`
- L89 _protected member_ `bool bShowMaterialInstancesMenu;`
- L90 _protected member_ `bool bAllowIgnoringCompilationErrors;`
- L92 _protected member_ `TSharedPtr<SListView<TSharedPtr<int32>>> MaterialInfoList;`
- L94 _protected member_ `TSharedPtr<SHeaderRow> PlatformColumnHeader;`
- L96 _protected member_ `TArray<TSharedPtr<EMaterialStatsDerivedMIOption>> DerivedMaterialInstancesComboBoxItems;`

### `Source/Editor/MaterialEditor/Private/SMaterialEditorSubstrateWidget.h` (Private)


#### class `SMaterialEditorSubstrateWidget`  
`class SMaterialEditorSubstrateWidget : public SCompoundWidget`  
_L19-84_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SMaterialEditorSubstrateWidget)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<IMaterialEditor> InMaterialEditorPtr);`
- L29 _public function_ `void UpdateFromMaterial()`
- L32 _public prototype_ `virtual TSharedRef<SWidget> GetContent();` — Gets the widget contents of the app
- L34 _public prototype_ `virtual ~SMaterialEditorSubstrateWidget();`
- L37 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L41 _private member_ `TSharedPtr<class SCheckBox> CheckBoxForceFullSimplification;`
- L42 _private member_ `TSharedPtr<class SCheckBox> CheckBoxBytesPerPixelOverride;`
- L43 _private member_ `TSharedPtr<class SCheckBox> CheckBoxClosuresPerPixelOverride;`
- L45 _private member_ `TSharedPtr<class SNumericEntryBox<uint32>> BytesPerPixelOverrideInput;`
- L46 _private member_ `TSharedPtr<class SNumericEntryBox<uint32>> ClosuresPerPixelOverrideInput;`
- L48 _private member_ `TSharedPtr<class SButton> ButtonApplyToPreview;`
- L50 _private member_ `TSharedPtr<class STextBlock> MaterialBudgetTextBlock;`
- L51 _private member_ `TSharedPtr<class STextBlock> MaterialFeatures0TextBlock;`
- L52 _private member_ `TSharedPtr<class STextBlock> MaterialFeatures1TextBlock;`
- L53 _private member_ `TSharedPtr<class STextBlock> MaterialFeatures2TextBlock;`
- L54 _private member_ `TSharedPtr<class STextBlock> DescriptionTextBlock;`
- L56 _private member_ `TSharedPtr<class SBox> MaterialBox;`
- L58 _private prototype_ `FReply OnButtonApplyToPreview();`
- L61 _private member_ `TWeakPtr<IMaterialEditor> MaterialEditorPtr;` — Pointer back to the material editor that owns this
- L63 _private member_ `bool bUpdateRequested = true;`
- L65 _private member_ `bool bBytesPerPixelStartedTransaction;`
- L66 _private member_ `uint32 BytesPerPixelOverride;`
- L67 _private prototype_ `void OnBytesPerPixelChanged(uint32 NewValue);`
- L68 _private prototype_ `void OnBytesPerPixelCommitted(uint32 NewValue, ETextCommit::Type InCommitType);`
- L69 _private prototype_ `void OnBeginBytesPerPixelSliderMovement();`
- L70 _private prototype_ `void OnEndBytesPerPixelSliderMovement(uint32 NewValue);`
- L71 _private prototype_ `TOptional<uint32> GetBytesPerPixelValue() const;`
- L73 _private prototype_ `void OnCheckBoxBytesPerPixelChanged(ECheckBoxState InCheckBoxState);`
- L75 _private member_ `bool bClosuresPerPixelStartedTransaction;`
- L76 _private member_ `uint32 ClosuresPerPixelOverride;`
- L77 _private prototype_ `void OnClosuresPerPixelChanged(uint32 NewValue);`
- L78 _private prototype_ `void OnClosuresPerPixelCommitted(uint32 NewValue, ETextCommit::Type InCommitType);`
- L79 _private prototype_ `void OnBeginClosuresPerPixelSliderMovement();`
- L80 _private prototype_ `void OnEndClosuresPerPixelSliderMovement(uint32 NewValue);`
- L81 _private prototype_ `TOptional<uint32> GetClosuresPerPixelValue() const;`
- L83 _private prototype_ `void OnCheckBoxClosuresPerPixelChanged(ECheckBoxState InCheckBoxState);`

### `Source/Editor/MaterialEditor/Private/SMaterialEditorTitleBar.h` (Private)


#### class `SMaterialEditorTitleBar`  
`class SMaterialEditorTitleBar : public SCompoundWidget`  
_L19-69_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS( SMaterialEditorTitleBar ) : _TitleText() , _EdGraphObj(nullptr) , _MaterialInfoList(nullptr)`
- L28 _public prototype_ `SLATE_ATTRIBUTE( FText, TitleText ) SLATE_ARGUMENT( UEdGraph*, EdGraphObj ) SLATE_ARGUMENT( const TArray<TSharedPtr<FMaterialInfo>>*, MaterialInfoList ) SLATE_EVENT( FEdGraphEvent, OnDifferentGraphCrumbClicked ) SLATE_ARGUMENT( TSharedPtr<SWidget>, HistoryNavigationWidget ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `TSharedRef<ITableRow> MakeMaterialInfoWidget(TSharedPtr<FMaterialInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Callback used to populate SListView
- L41 _public prototype_ `void RequestRefresh();` — Request a refresh of the list view
- L44 _public member_ `TSharedPtr<SListView<TSharedPtr<FMaterialInfo>>> MaterialInfoList;` — Material info we display when compile errors occur.
- L48 _protected member_ `TSharedPtr<SScrollBox> BreadcrumbTrailScrollBox;`
- L51 _protected member_ `UEdGraph* EdGraphObj;` — Edited graph
- L54 _protected member_ `TSharedPtr< SBreadcrumbTrail<UEdGraph*> > BreadcrumbTrail;` — Breadcrumb trail widget
- L57 _protected member_ `FEdGraphEvent OnDifferentGraphCrumbClicked;` — Callback to call when the user wants to change the active graph via the breadcrumb trail
- L60 _protected prototype_ `const FSlateBrush* GetTypeGlyph() const;` — Get the icon to use
- L63 _protected prototype_ `UEdGraph* GetOuterGraph(UObject* Obj);` — Function to fetch outer class which is of type UEGraph.
- L66 _protected prototype_ `void OnBreadcrumbClicked(UEdGraph* const& Item);` — Helper methods
- L67 _protected prototype_ `void RebuildBreadcrumbTrail();`
- L68 _protected prototype_ `static FText GetTitleForOneCrumb(const UEdGraph* BaseGraph, const UEdGraph* CurrGraph);`

### `Source/Editor/MaterialEditor/Private/SMaterialEditorTopologyWidget.h` (Private)


#### class `SMaterialEditorTopologyWidget`  
`class SMaterialEditorTopologyWidget : public SCompoundWidget`  
_L20-51_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SMaterialEditorTopologyWidget)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<IMaterialEditor> InMaterialEditorPtr);`
- L30 _public function_ `void UpdateFromMaterial()`
- L33 _public prototype_ `virtual TSharedRef<SWidget> GetContent();` — Gets the widget contents of the app
- L35 _public prototype_ `virtual ~SMaterialEditorTopologyWidget();`
- L38 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L40 _public prototype_ `static const TSharedRef<SWidget> ProcessOperatorAsThumbnails(const struct FSubstrateMaterialCompilationOutput& CompilationOutput, const struct FMaterialLayersFunctions* LayersFunctions);`
- L44 _private member_ `TSharedPtr<class SBox> MaterialBox;`
- L47 _private member_ `TWeakPtr<IMaterialEditor> MaterialEditorPtr;` — Pointer back to the material editor that owns this
- L49 _private member_ `bool bUpdateRequested = true;`

### `Source/Editor/MaterialEditor/Private/SMaterialEditorViewport.h` (Private)


#### struct `MaterialSlotPreviewInfo`  
`struct MaterialSlotPreviewInfo`  
_L26-31_
- desc: Helper struct for containing data for the material slot submenu UI and where to apply the preview material
- L28 _public member_ `FName SlotName;`
- L29 _public member_ `TObjectPtr<UMaterialInterface> OriginalMaterial;`
- L30 _public member_ `mutable bool bSlotEnabled;`

#### class `SMaterialEditor3DPreviewViewport`  
`class SMaterialEditor3DPreviewViewport : public SEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider`  
_L36-177_
- inherits: `SEditorViewport,FGCObject,ICommonEditorViewportToolbarInfoProvider`
- desc: Material Editor Preview viewport widget
- L39 _public function_ `SLATE_BEGIN_ARGS( SMaterialEditor3DPreviewViewport ) : _PreviewMaterial(nullptr)`
- L41 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IMaterialEditor>, MaterialEditor) SLATE_ARGUMENT(UMaterialInterface*, PreviewMaterial) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _public prototype_ `~SMaterialEditor3DPreviewViewport();`
- L48 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L49 _public function_ `virtual FString GetReferencerName() const override`
- L54 _public prototype_ `void RefreshViewport();`
- L62 _public prototype_ `bool SetPreviewAsset(UObject* InAsset);` — Sets the mesh on which to preview the material.  One of either InStaticMesh or InSkeletalMesh must be non-NULL! Does nothing if a skeletal mesh was specified but the material has bUsedWithSkeletalMesh=false. @return	true if a mesh was set successfully, false otherwise.
- L71 _public prototype_ `bool SetPreviewAssetByName(const TCHAR* InAssetName);` — Sets the preview asset to the named asset, if it can be found and is convertible into a UMeshComponent subclass. Does nothing if the named asset is not found or if the named asset is a skeletal mesh but the material has bUsedWithSkeletalMesh=false. @return	true if the named asset was found and set successfully, false otherwise.
- L73 _public prototype_ `void SetPreviewMaterial(UMaterialInterface* InMaterialInterface);`
- L76 _public member_ `TObjectPtr<UMeshComponent> PreviewMeshComponent;` — Component for the preview mesh.
- L79 _public member_ `TObjectPtr<UMaterialInterface> PreviewMaterial;` — Material for the preview mesh
- L82 _public member_ `EThumbnailPrimType PreviewPrimType;` — The preview primitive we are using.
- L85 _public prototype_ `void OnAddedToTab( const TSharedRef<SDockTab>& OwnerTab );` — The material editor has been added to a tab
- L87 _public function_ `TSharedRef<class FAdvancedPreviewScene> GetPreviewScene()`
- L90 _public prototype_ `void OnSetPreviewPrimitive(EThumbnailPrimType PrimType);` — Event handlers
- L91 _public prototype_ `bool IsPreviewPrimitiveChecked(EThumbnailPrimType PrimType) const;`
- L92 _public prototype_ `void OnSetPreviewMeshFromSelection();`
- L93 _public prototype_ `bool IsPreviewMeshFromSelectionChecked() const;`
- L94 _public prototype_ `void OnSetPreviewMeshMaterialSlots();`
- L95 _public prototype_ `bool DoesPreviewMeshContainSlots() const;`
- L97 _public prototype_ `void TogglePreviewBackground();`
- L98 _public prototype_ `bool IsTogglePreviewBackgroundChecked() const;`
- L101 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L102 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L103 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L108 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L109 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L110 _protected prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L111 _protected prototype_ `TSharedRef<SWidget> GenerateMaterialSlotMenu();`
- L113 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<class SOverlay> Overlay) override;`
- L114 _protected prototype_ `virtual EVisibility OnGetViewportContentVisibility() const override;`
- L115 _protected prototype_ `virtual void BindCommands() override;`
- L116 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L119 _protected prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InEvent) override;`
- L124 _private prototype_ `UMaterialInterface* GetPreviewingMaterialInterface();` — If we have a MaterialEditor, it will look up the preview material from that. Otherwise it will fallback to previewing this material
- L126 _private prototype_ `void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L129 _private prototype_ `void ApplyStateToAllSlots(bool bState);` — Helper function for applying state logic to all material slots + updates
- L132 _private prototype_ `void OnSelectAllSlots();` — Set true for usage to all material slots
- L135 _private prototype_ `void OnSelectNoSlots();` — Set false for usage to all material slots
- L138 _private prototype_ `void OnMaterialSlotCheckStateChanged(ECheckBoxState NewState, int32 SlotIndex);` — Updates the scene preview mesh when a checkbox state changes
- L141 _private prototype_ `ECheckBoxState IsMaterialSlotChecked(int32 SlotIndex) const;` — Returns if a material slot is checked/should show the preview material
- L144 _private member_ `TWeakPtr<SDockTab> ParentTab;` — The parent tab where this viewport resides
- L147 _private member_ `TSharedPtr<class SMaterialEditorTopologyWidget> SubstrateWidget;` — The Substrate control tab
- L149 _private prototype_ `bool IsVisible() const override;`
- L152 _private member_ `TWeakPtr<IMaterialEditor> MaterialEditorPtr;` — Pointer back to the material editor tool that owns us
- L155 _private member_ `TWeakObjectPtr<UMaterialInterface> PreviewMaterialPtr;` — The material we're previewing if we're not hosted by a material editor. Used for diffs.
- L158 _private member_ `TSharedPtr<class FMaterialEditorViewportClient> EditorViewportClient;` — Level viewport client
- L161 _private member_ `TSharedPtr<class FAdvancedPreviewScene> AdvancedPreviewScene;` — Preview Scene - uses advanced preview settings
- L164 _private member_ `TObjectPtr<class APostProcessVolume> PostProcessVolumeActor;` — Post process volume actor.
- L167 _private member_ `FCoreUObjectDelegates::FOnObjectPropertyChanged::FDelegate OnPropertyChangedHandle;` — Property changed delegate.
- L170 _private member_ `FDelegateHandle OnPropertyChangedHandleDelegateHandle;` — Handle to the registered OnPropertyChangedHandle delegate.
- L173 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.
- L176 _private member_ `TArray<const MaterialSlotPreviewInfo> MaterialSlots;` — Material Slot data for populating and processing the material slot selections

#### class `SMaterialEditorUIPreviewViewport`  
`class SMaterialEditorUIPreviewViewport : public SCompoundWidget`  
_L182-228_
- inherits: `SCompoundWidget`
- desc: A preview viewport used for 2D UI materials
- L185 _public function_ `SLATE_BEGIN_ARGS( SMaterialEditorUIPreviewViewport )`
- L186 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UMaterialInterface* PreviewMaterial );`
- L189 _public prototype_ `virtual ~SMaterialEditorUIPreviewViewport();`
- L191 _public prototype_ `void SetPreviewMaterial(UMaterialInterface* InMaterialInterface);`
- L194 _private prototype_ `void OnPreviewXChanged( int32 NewValue );`
- L195 _private prototype_ `void OnPreviewXCommitted( int32 NewValue, ETextCommit::Type );`
- L196 _private prototype_ `void OnPreviewYChanged( int32 NewValue );`
- L197 _private prototype_ `void OnPreviewYCommitted( int32 NewValue, ETextCommit::Type );`
- L198 _private function_ `TOptional<int32> OnGetPreviewXValue() const`
- L199 _private function_ `TOptional<int32> OnGetPreviewYValue() const`
- L201 _private prototype_ `bool IsBackgroundTypeChecked(EBackgroundType BackgroundType) const;`
- L202 _private prototype_ `bool IsShowBorderChecked() const;`
- L204 _private prototype_ `void SetBackgroundType(EBackgroundType NewBackgroundType);`
- L205 _private prototype_ `void ToggleShowBorder();`
- L207 _private prototype_ `FMenuBuilder BuildViewOptionsMenu(bool bForContextMenu = false);`
- L208 _private prototype_ `FReply OnViewportClicked(const FGeometry& Geometry, const FPointerEvent& MouseEvent);`
- L209 _private prototype_ `void ShowContextMenu(const FGeometry& Geometry, const FPointerEvent& MouseEvent);`
- L211 _private prototype_ `FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L212 _private prototype_ `void HandleSettingsActionExecute();`
- L213 _private prototype_ `void HandleSettingsChanged();`
- L215 _private prototype_ `void HandleDidZoom();`
- L216 _private prototype_ `void ExecuteZoomToActual();`
- L217 _private prototype_ `bool CanZoomToActual() const;`
- L218 _private prototype_ `FSlateColor GetZoomTextColorAndOpacity() const;`
- L219 _private prototype_ `FText GetZoomText() const;`
- L220 _private prototype_ `FText GetDisplayedAtSizeText() const;`
- L223 _private member_ `FIntPoint PreviewSize;`
- L224 _private member_ `TSharedPtr<class SMaterialEditorUIPreviewZoomer> PreviewZoomer;`
- L225 _private member_ `TSharedPtr<SWidget> PreviewArea;`
- L226 _private member_ `FPreviewBackgroundSettings BackgroundSettings;`
- L227 _private member_ `FCurveSequence ZoomLevelFade;`

### `Source/Editor/MaterialEditor/Private/SMaterialExpressionsOverviewWidget.h` (Private)


#### struct `FSharedSamplerDataRowData`  
`struct FSharedSamplerDataRowData`  
_L18-25_
- desc: Data for a row in the list of shared sampler entries
- L20 _public function_ `FSharedSamplerDataRowData(FString InName, int32 InCount, bool bInIsDuplicate = false) : Name(InName), Count(InCount), bIsDuplicate(bInIsDuplicate)`
- L22 _public member_ `FString Name = "";`
- L23 _public member_ `int32 Count = 0;`
- L24 _public member_ `bool bIsDuplicate = false;`

#### class `SMaterialExpressionsOverviewPanel`  
`class SMaterialExpressionsOverviewPanel : public SCompoundWidget`  
_L28-70_
- inherits: `SCompoundWidget`
- desc: ********* SMaterialExpressionsOverviewPanel *******
- L31 _public function_ `SLATE_BEGIN_ARGS(SMaterialExpressionsOverviewPanel) : _InMaterialEditorInstance(nullptr) , _InGenerator() , _InMaterialDetailsView()`
- L37 _public prototype_ `SLATE_ARGUMENT(UMaterialEditorPreviewParameters*, InMaterialEditorInstance) SLATE_ARGUMENT(TSharedPtr<class IPropertyRowGenerator>, InGenerator) SLATE_ARGUMENT(TSharedPtr<class IDetailsView>, InMaterialDetailsView) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L45 _public prototype_ `void SetEditorInstance(UMaterialEditorPreviewParameters* InMaterialEditorInstance);` — Sets the Material Editor Preview Parameters to be displayed and refreshes the UI
- L48 _public function_ `void SetMaterialDetailsView(TSharedPtr<class IDetailsView> InDetailsView)` — The material details widget is initialized after this widget is created so we cannot pass the view into the constructor
- L51 _private prototype_ `void Refresh();`
- L54 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FSharedSamplerDataRowData> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Adds a new text box with the string to the list
- L55 _private member_ `TWeakPtr<class IPropertyRowGenerator> Generator;`
- L57 _private prototype_ `void OnMouseButtonClick(const TSharedPtr<FSharedSamplerDataRowData> RowData);`
- L60 _private member_ `TArray<TSharedPtr<FSharedSamplerDataRowData>> Items;` — The list of strings
- L63 _private member_ `TSharedPtr<SListView<TSharedPtr<FSharedSamplerDataRowData>>> ListViewWidget;` — The actual UI list
- L66 _private member_ `UMaterialEditorPreviewParameters* MaterialEditorInstance;` — The set of material parameters this is associated with
- L69 _private member_ `TSharedPtr<class IDetailsView> MaterialDetailsView;` — Pointer to the Material Editor instance this widget was created for

### `Source/Editor/MaterialEditor/Private/SMaterialLayersFunctionsTree.h` (Private)


#### class `SMaterialLayersFunctionsInstanceTreeItem`  
`class SMaterialLayersFunctionsInstanceTreeItem : public STableRow< TSharedPtr<FSortedParamData> >, public IDraggableItem`  
_L28-98_
- inherits: `STableRow<TSharedPtr<FSortedParamData>>,IDraggableItem`
- L32 _public function_ `SLATE_BEGIN_ARGS(SMaterialLayersFunctionsInstanceTreeItem) : _StackParameterData(nullptr), _MaterialEditorInstance(nullptr)`
- L38 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSortedParamData>, StackParameterData) SLATE_ARGUMENT(UMaterialEditorInstanceConstant*, MaterialEditorInstance) SLATE_ARGUMENT(SMaterialLayersFunctionsInstanceTree*, InTree) SLATE_END_ARGS() bool bIsBeingDragged;` — The item content.
- L46 _private member_ `bool bIsHoveredDragTarget;`
- L49 _private prototype_ `const FSlateBrush* GetBorderImage() const;`
- L51 _private prototype_ `FSlateColor GetOuterBackgroundColor(TSharedPtr<FSortedParamData> InParamData) const;`
- L54 _public prototype_ `void RefreshOnRowChange(const FAssetData& AssetData, SMaterialLayersFunctionsInstanceTree* InTree);`
- L55 _public prototype_ `bool GetFilterState(SMaterialLayersFunctionsInstanceTree* InTree, TSharedPtr<FSortedParamData> InStackData) const;`
- L56 _public prototype_ `void FilterClicked(const ECheckBoxState NewCheckedState, SMaterialLayersFunctionsInstanceTree* InTree, TSharedPtr<FSortedParamData> InStackData);`
- L57 _public prototype_ `ECheckBoxState GetFilterChecked(SMaterialLayersFunctionsInstanceTree* InTree, TSharedPtr<FSortedParamData> InStackData) const;`
- L58 _public prototype_ `FText GetLayerName(SMaterialLayersFunctionsInstanceTree* InTree, int32 Counter) const;`
- L59 _public prototype_ `void OnNameChanged(const FText& InText, ETextCommit::Type CommitInfo, SMaterialLayersFunctionsInstanceTree* InTree, int32 Counter);`
- L62 _public function_ `void OnLayerDragEnter(const FDragDropEvent& DragDropEvent) override`
- L70 _public function_ `void OnLayerDragLeave(const FDragDropEvent& DragDropEvent) override`
- L75 _public function_ `void OnLayerDragDetected() override`
- L80 _public prototype_ `FReply OnLayerDrop(const FDragDropEvent& DragDropEvent);`
- L81 _public prototype_ `void OnOverrideParameter(bool NewValue, class UDEditorParameterValue* Parameter);`
- L82 _public prototype_ `void OnOverrideParameter(bool NewValue, TObjectPtr<UDEditorParameterValue> Parameter);`
- L88 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Construct the widget @param InArgs   A declaration from which to construct the widget
- L91 _public member_ `TSharedPtr<FSortedParamData> StackParameterData;` — The node info to build the tree view row from.
- L93 _public member_ `SMaterialLayersFunctionsInstanceTree* Tree;`
- L95 _public member_ `UMaterialEditorInstanceConstant* MaterialEditorInstance;`
- L97 _public prototype_ `FString GetInstancePath(SMaterialLayersFunctionsInstanceTree* InTree) const;`

#### class `SMaterialLayersFunctionsWrapper`  
`class SMaterialLayersFunctionsWrapper: public SCompoundWidget`  
_L100-106_
- inherits: `SCompoundWidget`
- L103 _public prototype_ `virtual void SetEditorInstance(UMaterialEditorParameters* InMaterialEditorInstance) = 0;`
- L104 _public prototype_ `virtual void Refresh() = 0;`

#### class `SMaterialLayersFunctionsInstanceWrapper`  
`class SMaterialLayersFunctionsInstanceWrapper : public SMaterialLayersFunctionsWrapper`  
_L108-140_
- inherits: `SMaterialLayersFunctionsWrapper`
- L111 _public function_ `SLATE_BEGIN_ARGS(SMaterialLayersFunctionsInstanceWrapper) : _InMaterialEditorInstance(nullptr), _InGenerator(nullptr), _InShowHiddenDelegate(), _InNotifyHook(nullptr)`
- L118 _public prototype_ `SLATE_ARGUMENT(UMaterialEditorParameters*, InMaterialEditorInstance) SLATE_ARGUMENT(TSharedPtr<class IPropertyRowGenerator>, InGenerator) SLATE_ARGUMENT(FGetShowHiddenParameters, InShowHiddenDelegate) SLATE_ARGUMENT(FNotifyHook*, InNotifyHook) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L125 _public prototype_ `virtual void SetEditorInstance(UMaterialEditorParameters* InMaterialEditorInstance) override;`
- L126 _public prototype_ `virtual void Refresh() override;`
- L127 _public prototype_ `bool HasLayers() const;`
- L129 _public prototype_ `TSharedPtr<class IPropertyRowGenerator> GetGenerator();`
- L130 _public member_ `TAttribute<ECheckBoxState> IsParamChecked;`
- L131 _public member_ `TWeakObjectPtr<class UDEditorParameterValue> LayerParameter;`
- L132 _public member_ `class UMaterialEditorParameters* MaterialEditorInstance;`
- L134 _public member_ `TSharedPtr<class SMaterialLayersTree> NestedTree;`
- L135 _public member_ `FSimpleDelegate OnLayerPropertyChanged;`
- L139 _private member_ `TWeakPtr<class IPropertyRowGenerator> Generator;`

#### class `SMaterialLayersTree`  
`class SMaterialLayersTree: public STreeView<TSharedPtr<FSortedParamData>>`  
_L142-154_
- inherits: `STreeView<TSharedPtr<FSortedParamData>>`
- L145 _public prototype_ `virtual void CreateGroupsWidget() = 0;`
- L146 _public prototype_ `virtual TWeakObjectPtr<class UDEditorParameterValue> GetFunctionParameter() = 0;`
- L147 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetTreeThumbnailPool() = 0;`
- L148 _public prototype_ `virtual EVisibility GetRelinkLayersToParentVisibility() const = 0;`
- L149 _public prototype_ `virtual FReply RelinkLayersToParent() = 0;`
- L150 _public prototype_ `virtual void SetMaterialEditorInstance(UMaterialEditorParameters* InMaterialEditorInstance) = 0;`
- L151 _public prototype_ `virtual void UpdateThumbnailMaterial(TEnumAsByte<EMaterialParameterAssociation> InAssociation, int32 InIndex, bool bAlterBlendIndex = false) = 0;`
- L152 _public function_ `virtual void CollectAssetStackItemsRecursively(TSharedPtr<FSortedParamData> Item, TArray<TSharedPtr<FSortedParamData>>& OutGroupsContainer, TArray<uint32>& OutNodeIdsContainer)`
- L153 _public function_ `virtual void AddRootNodeLayer()`

#### class `SMaterialLayersFunctionsInstanceTree`  
`class SMaterialLayersFunctionsInstanceTree : public SMaterialLayersTree`  
_L155-235_
- inherits: `SMaterialLayersTree`
- L159 _public function_ `SLATE_BEGIN_ARGS(SMaterialLayersFunctionsInstanceTree) : _InMaterialEditorInstance(nullptr) , _InNotifyHook(nullptr)`
- L164 _public prototype_ `SLATE_ARGUMENT(UMaterialEditorInstanceConstant*, InMaterialEditorInstance) SLATE_ARGUMENT(SMaterialLayersFunctionsInstanceWrapper*, InWrapper) SLATE_ARGUMENT(FGetShowHiddenParameters, InShowHiddenDelegate) SLATE_ARGUMENT(FNotifyHook*, InNotifyHook) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L172 _public prototype_ `TSharedRef< ITableRow > OnGenerateRowMaterialLayersFunctionsTreeView(TSharedPtr<FSortedParamData> Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L173 _public prototype_ `void OnGetChildrenMaterialLayersFunctionsTreeView(TSharedPtr<FSortedParamData> InParent, TArray< TSharedPtr<FSortedParamData> >& OutChildren);`
- L174 _public prototype_ `void OnExpansionChanged(TSharedPtr<FSortedParamData> Item, bool bIsExpanded);`
- L175 _public prototype_ `void SetParentsExpansionState();`
- L177 _public function_ `void ShowHiddenValues(bool& bShowHiddenParameters)`
- L178 _public member_ `TWeakObjectPtr<class UDEditorParameterValue> FunctionParameter;`
- L179 _public member_ `struct FMaterialLayersFunctions* FunctionInstance;`
- L180 _public member_ `TSharedPtr<IPropertyHandle> FunctionInstanceHandle;`
- L181 _public prototype_ `void RefreshOnAssetChange(const struct FAssetData& InAssetData, int32 Index, EMaterialParameterAssociation MaterialType);`
- L182 _public prototype_ `void ResetAssetToDefault(TSharedPtr<FSortedParamData> InData);`
- L183 _public prototype_ `void AddLayer();`
- L184 _public function_ `virtual void AddRootNodeLayer() override`
- L185 _public prototype_ `void RemoveLayer(int32 Index);`
- L186 _public prototype_ `FReply UnlinkLayer(int32 Index);`
- L187 _public prototype_ `virtual FReply RelinkLayersToParent() override;`
- L188 _public prototype_ `EVisibility GetUnlinkLayerVisibility(int32 Index) const;`
- L189 _public prototype_ `virtual EVisibility GetRelinkLayersToParentVisibility() const override;`
- L190 _public function_ `virtual void SetMaterialEditorInstance(UMaterialEditorParameters* InMaterialEditorInstance) override`
- L191 _public prototype_ `FReply ToggleLayerVisibility(int32 Index);`
- L192 _public prototype_ `virtual TSharedPtr<class FAssetThumbnailPool> GetTreeThumbnailPool() override;`
- L195 _public member_ `UMaterialEditorInstanceConstant* MaterialEditorInstance;` — Object that stores all of the possible parameters we can edit
- L198 _public prototype_ `virtual void CreateGroupsWidget() override;` — Builds the custom parameter groups category
- L199 _public function_ `virtual TWeakObjectPtr<class UDEditorParameterValue> GetFunctionParameter() override`
- L201 _public prototype_ `bool IsLayerVisible(int32 Index) const;`
- L203 _public function_ `SMaterialLayersFunctionsInstanceWrapper* GetWrapper()`
- L207 _public prototype_ `TSharedRef<SWidget> CreateThumbnailWidget(EMaterialParameterAssociation InAssociation, int32 InIndex, float InThumbnailSize);`
- L208 _public prototype_ `virtual void UpdateThumbnailMaterial(TEnumAsByte<EMaterialParameterAssociation> InAssociation, int32 InIndex, bool bAlterBlendIndex = false) override;`
- L209 _public prototype_ `FReply OnThumbnailDoubleClick(const FGeometry& Geometry, const FPointerEvent& MouseEvent, EMaterialParameterAssociation InAssociation, int32 InIndex);`
- L210 _public prototype_ `bool IsOverriddenExpression(class UDEditorParameterValue* Parameter, int32 InIndex);`
- L211 _public prototype_ `bool IsOverriddenExpression(TObjectPtr<UDEditorParameterValue> Parameter, int32 InIndex);`
- L213 _public prototype_ `FGetShowHiddenParameters GetShowHiddenDelegate() const;`
- L216 _protected prototype_ `void ShowSubParameters(TSharedPtr<FSortedParamData> ParentParameter);`
- L219 _private member_ `TArray<TSharedPtr<FSortedParamData>> LayerProperties;`
- L221 _private member_ `TArray<FUnsortedParamData> NonLayerProperties;`
- L223 _private member_ `FDetailColumnSizeData ColumnSizeData;`
- L225 _private member_ `SMaterialLayersFunctionsInstanceWrapper* Wrapper;`
- L227 _private member_ `TSharedPtr<class IPropertyRowGenerator> Generator;`
- L229 _private member_ `bool bLayerIsolated;`
- L232 _private member_ `FGetShowHiddenParameters ShowHiddenDelegate;` — Delegate to call to determine if hidden parameters should be shown
- L234 _private member_ `FNotifyHook* NotifyHook = nullptr;`

#### class `SMaterialLayersFunctionsMaterialTreeItem`  
`class SMaterialLayersFunctionsMaterialTreeItem : public STableRow< TSharedPtr<FSortedParamData> >`  
_L241-284_
- inherits: `STableRow<TSharedPtr<FSortedParamData>>`
- L245 _public function_ `SLATE_BEGIN_ARGS(SMaterialLayersFunctionsMaterialTreeItem) : _StackParameterData(nullptr), _MaterialEditorInstance(nullptr)`
- L251 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSortedParamData>, StackParameterData) SLATE_ARGUMENT(UMaterialEditorPreviewParameters*, MaterialEditorInstance) SLATE_ARGUMENT(SMaterialLayersFunctionsMaterialTree*, InTree) SLATE_END_ARGS() FDetailColumnSizeData ColumnSizeData;` — The item content.
- L257 _public member_ `bool bIsBeingDragged;`
- L260 _private member_ `bool bIsHoveredDragTarget;`
- L261 _private prototype_ `const FSlateBrush* GetBorderImage() const;`
- L263 _private prototype_ `FSlateColor GetOuterBackgroundColor(TSharedPtr<FSortedParamData> InParamData) const;`
- L266 _public prototype_ `void RefreshOnRowChange(const FAssetData& AssetData, SMaterialLayersFunctionsMaterialTree* InTree);`
- L267 _public prototype_ `FText GetLayerName(SMaterialLayersFunctionsMaterialTree* InTree, int32 Counter) const;`
- L274 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Construct the widget @param InArgs   A declaration from which to construct the widget
- L277 _public member_ `TSharedPtr<FSortedParamData> StackParameterData;` — The node info to build the tree view row from.
- L279 _public member_ `SMaterialLayersFunctionsMaterialTree* Tree;`
- L281 _public member_ `UMaterialEditorPreviewParameters* MaterialEditorInstance;`
- L283 _public prototype_ `FString GetInstancePath(SMaterialLayersFunctionsMaterialTree* InTree) const;`

#### class `SMaterialLayersFunctionsMaterialWrapper`  
`class SMaterialLayersFunctionsMaterialWrapper : public SMaterialLayersFunctionsWrapper`  
_L286-308_
- inherits: `SMaterialLayersFunctionsWrapper`
- L289 _public function_ `SLATE_BEGIN_ARGS(SMaterialLayersFunctionsMaterialWrapper) : _InMaterialEditorInstance(nullptr) , _InGenerator()`
- L294 _public prototype_ `SLATE_ARGUMENT(UMaterialEditorPreviewParameters*, InMaterialEditorInstance) SLATE_ARGUMENT(TSharedPtr<class IPropertyRowGenerator>, InGenerator) SLATE_END_ARGS() virtual void Refresh() override;`
- L299 _public prototype_ `void Construct(const FArguments& InArgs);`
- L300 _public prototype_ `virtual void SetEditorInstance(UMaterialEditorParameters* InMaterialEditorInstance) override;`
- L301 _public prototype_ `TSharedPtr<class IPropertyRowGenerator> GetGenerator();`
- L302 _public member_ `TWeakObjectPtr<class UDEditorParameterValue> LayerParameter;`
- L303 _public member_ `class UMaterialEditorPreviewParameters* MaterialEditorInstance;`
- L304 _public member_ `TSharedPtr<class SMaterialLayersFunctionsMaterialTree> NestedTree;`
- L307 _private member_ `TWeakPtr<class IPropertyRowGenerator> Generator;`

#### class `SMaterialLayersFunctionsMaterialTree`  
`class SMaterialLayersFunctionsMaterialTree : public STreeView<TSharedPtr<FSortedParamData>>`  
_L310-356_
- inherits: `STreeView<TSharedPtr<FSortedParamData>>`
- L314 _public function_ `SLATE_BEGIN_ARGS(SMaterialLayersFunctionsMaterialTree) : _InMaterialEditorInstance(nullptr)`
- L318 _public prototype_ `SLATE_ARGUMENT(UMaterialEditorPreviewParameters*, InMaterialEditorInstance) SLATE_ARGUMENT(SMaterialLayersFunctionsMaterialWrapper*, InWrapper) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L324 _public prototype_ `TSharedRef< ITableRow > OnGenerateRowMaterialLayersFunctionsTreeView(TSharedPtr<FSortedParamData> Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L325 _public prototype_ `void OnGetChildrenMaterialLayersFunctionsTreeView(TSharedPtr<FSortedParamData> InParent, TArray< TSharedPtr<FSortedParamData> >& OutChildren);`
- L326 _public prototype_ `void OnExpansionChanged(TSharedPtr<FSortedParamData> Item, bool bIsExpanded);`
- L327 _public prototype_ `void SetParentsExpansionState();`
- L328 _public function_ `void ShowHiddenValues(bool& bShowHiddenParameters)`
- L329 _public member_ `TWeakObjectPtr<class UDEditorParameterValue> FunctionParameter;`
- L330 _public member_ `struct FMaterialLayersFunctions* FunctionInstance;`
- L331 _public member_ `TSharedPtr<IPropertyHandle> FunctionInstanceHandle;`
- L332 _public prototype_ `TSharedPtr<class FAssetThumbnailPool> GetTreeThumbnailPool();`
- L335 _public member_ `UMaterialEditorPreviewParameters* MaterialEditorInstance;` — Object that stores all of the possible parameters we can edit
- L338 _public prototype_ `void CreateGroupsWidget();` — Builds the custom parameter groups category
- L340 _public function_ `SMaterialLayersFunctionsMaterialWrapper* GetWrapper()`
- L342 _public prototype_ `TSharedRef<SWidget> CreateThumbnailWidget(EMaterialParameterAssociation InAssociation, int32 InIndex, float InThumbnailSize);`
- L343 _public prototype_ `void UpdateThumbnailMaterial(TEnumAsByte<EMaterialParameterAssociation> InAssociation, int32 InIndex, bool bAlterBlendIndex = false);`
- L346 _protected prototype_ `void ShowSubParameters(TSharedPtr<FSortedParamData> ParentParameter);`
- L349 _private member_ `TArray<TSharedPtr<FSortedParamData>> LayerProperties;`
- L351 _private member_ `TArray<FUnsortedParamData> NonLayerProperties;`
- L353 _private member_ `FDetailColumnSizeData ColumnSizeData;`
- L355 _private member_ `SMaterialLayersFunctionsMaterialWrapper* Wrapper;`

### `Source/Editor/MaterialEditor/Private/SMaterialNamedReroutesPanel.h` (Private)


#### class `SMaterialNamedRerouteItem`  
`class SMaterialNamedRerouteItem : public SGraphPaletteItem`  
_L12-22_
- inherits: `SGraphPaletteItem`
- desc: Widget for displaying a single named reroute item with a color swatch
- L15 _public function_ `SLATE_BEGIN_ARGS(SMaterialNamedRerouteItem)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);`
- L21 _private prototype_ `virtual FText GetItemTooltip() const override;`

#### class `SMaterialNamedReroutesPanel`  
`class SMaterialNamedReroutesPanel : public SGraphPalette`  
_L27-53_
- inherits: `SGraphPalette`
- desc: Panel listing all Named Reroute Declaration nodes in the current material
- L30 _public function_ `SLATE_BEGIN_ARGS(SMaterialNamedReroutesPanel)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FMaterialEditor> InMaterialEditorPtr);`
- L36 _public prototype_ `void RequestRefresh();` — Force a full refresh of the list (e.g. when declarations are added/removed or properties change)
- L40 _protected prototype_ `virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;` — SGraphPalette Interface
- L41 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;`
- L45 _protected prototype_ `void OnActionDoubleClicked(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions);` — Called when an action is selected in the list - navigates to the declaration node
- L49 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Creates the right-click context menu for panel items
- L52 _private member_ `TWeakPtr<FMaterialEditor> MaterialEditorPtr;` — Pointer back to the material editor that owns us

### `Source/Editor/MaterialEditor/Private/SMaterialPalette.h` (Private)


#### class `SMaterialPaletteItem`  
`class SMaterialPaletteItem : public SGraphPaletteItem`  
_L15-28_
- inherits: `SGraphPaletteItem`
- desc: Widget for displaying a single item
- L18 _public function_ `SLATE_BEGIN_ARGS( SMaterialPaletteItem )`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);`
- L25 _private prototype_ `TSharedRef<SWidget> CreateHotkeyDisplayWidget(const TSharedPtr<const FInputChord> HotkeyChord);` — Create the hotkey display widget
- L27 _private prototype_ `virtual FText GetItemTooltip() const override;`

#### class `SMaterialPalette`  
`class SMaterialPalette : public SGraphPalette`  
_L32-76_
- inherits: `SGraphPalette`
- L35 _public function_ `SLATE_BEGIN_ARGS( SMaterialPalette )`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FMaterialEditor> InMaterialEditorPtr);`
- L42 _protected prototype_ `virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;` — SGraphPalette Interface
- L43 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;`
- L47 _protected prototype_ `FString GetFilterCategoryName() const;` — Get the currently selected category name
- L50 _protected prototype_ `void CategorySelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — Callback for when the selected category changes
- L53 _protected prototype_ `void AddAssetFromAssetRegistry(const FAssetData& InAddedAssetData);` — Callback from the Asset Registry when a new asset is added.
- L56 _protected prototype_ `void RemoveAssetFromRegistry(const FAssetData& InAddedAssetData);` — Callback from the Asset Registry when an asset is removed.
- L59 _protected prototype_ `void RenameAssetFromRegistry(const FAssetData& InAddedAssetData, const FString& InNewName);` — Callback from the Asset Registry when an asset is renamed.
- L61 _protected prototype_ `void RefreshAssetInRegistry(const FAssetData& InAddedAssetData);`
- L63 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L67 _protected member_ `TWeakPtr<FMaterialEditor> MaterialEditorPtr;` — Pointer back to the material editor that owns us
- L70 _protected member_ `TArray< TSharedPtr<FString> > CategoryNames;` — List of available Category Names
- L73 _protected member_ `TSharedPtr<STextComboBox> CategoryComboBox;` — Combo box used to select category
- L75 _protected member_ `bool bNeedRefresh = false;`

### `Source/Editor/MaterialEditor/Private/SMaterialParametersOverviewWidget.h` (Private)


#### class `SMaterialParametersOverviewTreeItem`  
`class SMaterialParametersOverviewTreeItem : public STableRow< TSharedPtr<FSortedParamData> >`  
_L24-62_
- inherits: `STableRow<TSharedPtr<FSortedParamData>>`
- desc: ********* SMaterialParametersOverviewTreeItem *******
- L28 _public function_ `SLATE_BEGIN_ARGS(SMaterialParametersOverviewTreeItem) : _StackParameterData(nullptr), _MaterialEditorInstance(nullptr)`
- L34 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSortedParamData>, StackParameterData) SLATE_ARGUMENT(UMaterialEditorPreviewParameters*, MaterialEditorInstance) SLATE_ARGUMENT(TSharedPtr<SMaterialParametersOverviewTree>, InTree) SLATE_END_ARGS() void RefreshOnRowChange(const FAssetData& AssetData, TSharedPtr<SMaterialParametersOverviewTree> InTree);` — The item content.
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Construct the widget @param InArgs   A declaration from which to construct the widget
- L49 _private prototype_ `const FSlateBrush* GetBorderImage() const;`
- L51 _private prototype_ `FSlateColor GetOuterBackgroundColor(TSharedPtr<FSortedParamData> InParamData) const;`
- L55 _private member_ `TSharedPtr<FSortedParamData> StackParameterData;` — The node info to build the tree view row from.
- L58 _private member_ `TWeakPtr<SMaterialParametersOverviewTree> Tree;` — The tree that contains this item
- L61 _private member_ `UMaterialEditorPreviewParameters* MaterialEditorInstance;` — The set of material parameters this is associated with

#### class `SMaterialParametersOverviewPanel`  
`class SMaterialParametersOverviewPanel : public SCompoundWidget`  
_L65-97_
- inherits: `SCompoundWidget`
- desc: ********* SMaterialParametersOverviewPanel *******
- L68 _public function_ `SLATE_BEGIN_ARGS(SMaterialParametersOverviewPanel) : _InMaterialEditorInstance(nullptr) , _InGenerator()`
- L73 _public prototype_ `SLATE_ARGUMENT(UMaterialEditorPreviewParameters*, InMaterialEditorInstance) SLATE_ARGUMENT(TSharedPtr<class IPropertyRowGenerator>, InGenerator) SLATE_EVENT(FSelectMaterialNode, SelectMaterialNode) SLATE_END_ARGS() void Refresh();`
- L78 _public prototype_ `void Construct(const FArguments& InArgs);`
- L79 _public prototype_ `void UpdateEditorInstance(UMaterialEditorPreviewParameters* InMaterialEditorInstance);`
- L80 _public prototype_ `TSharedPtr<class IPropertyRowGenerator> GetGenerator();`
- L83 _private prototype_ `const FSlateBrush* GetBackgroundImage() const;`
- L85 _private prototype_ `int32 GetPanelIndex() const;`
- L89 _private member_ `class UMaterialEditorPreviewParameters* MaterialEditorInstance;` — The set of material parameters this is associated with
- L92 _private member_ `TSharedPtr<class SMaterialParametersOverviewTree> NestedTree;` — The tree contained in this item
- L94 _private member_ `TSharedPtr<class SScrollBar> ExternalScrollbar;`
- L95 _private member_ `TWeakPtr<class IPropertyRowGenerator> Generator;`

#### class `SMaterialParametersOverviewTree`  
`class SMaterialParametersOverviewTree : public STreeView<TSharedPtr<FSortedParamData>>`  
_L100-158_
- inherits: `STreeView<TSharedPtr<FSortedParamData>>`
- desc: ********* SMaterialParametersOverviewTree *******
- L106 _public function_ `SLATE_BEGIN_ARGS(SMaterialParametersOverviewTree) : _InMaterialEditorInstance(nullptr) , _InOwner(nullptr) , _InScrollbar()`
- L112 _public prototype_ `SLATE_ARGUMENT(UMaterialEditorPreviewParameters*, InMaterialEditorInstance) SLATE_ARGUMENT(TSharedPtr<SMaterialParametersOverviewPanel>, InOwner) SLATE_ARGUMENT(TSharedPtr<SScrollBar>, InScrollbar) SLATE_EVENT(FSelectMaterialNode, SelectMaterialNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L120 _public prototype_ `TSharedRef< ITableRow > OnGenerateRowMaterialLayersFunctionsTreeView(TSharedPtr<FSortedParamData> Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L121 _public prototype_ `void OnGetChildrenMaterialLayersFunctionsTreeView(TSharedPtr<FSortedParamData> InParent, TArray< TSharedPtr<FSortedParamData> >& OutChildren);`
- L122 _public prototype_ `void OnExpansionChanged(TSharedPtr<FSortedParamData> Item, bool bIsExpanded);`
- L123 _public prototype_ `void SetParentsExpansionState();`
- L125 _public prototype_ `TSharedPtr<class FAssetThumbnailPool> GetTreeThumbnailPool();`
- L128 _public member_ `UMaterialEditorPreviewParameters* MaterialEditorInstance;` — Object that stores all of the possible parameters we can edit
- L131 _public prototype_ `void CreateGroupsWidget();` — Builds the custom parameter groups category
- L133 _public function_ `TWeakPtr<SMaterialParametersOverviewPanel> GetOwner()`
- L134 _public function_ `bool HasAnyParameters() const`
- L136 _public function_ `FDetailColumnSizeData& GetColumnSizeData()`
- L138 _public prototype_ `virtual bool Private_OnItemDoubleClicked(TSharedPtr<FSortedParamData> TheItem) override;`
- L142 _protected prototype_ `void ShowSubParameters();`
- L146 _private member_ `TArray<TSharedPtr<FSortedParamData>> SortedParameters;`
- L148 _private member_ `TArray<FUnsortedParamData> UnsortedParameters;`
- L150 _private member_ `TWeakPtr<SMaterialParametersOverviewPanel> Owner;`
- L152 _private member_ `bool bHasAnyParameters;`
- L154 _private member_ `FDetailColumnSizeData ColumnSizeData;`
- L157 _private member_ `FSelectMaterialNode SelectMaterialNodeDelegate;` — Called when a node should be selected in the material editor.

### `Source/Editor/MaterialEditor/Private/SubstrateMaterialEditorStyle.h` (Private)


#### class `FSubstrateMaterialEditorStyle`  
`class FSubstrateMaterialEditorStyle`  
_L8-27_
- L11 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static FName GetStyleSetName();`
- L15 _public prototype_ `static const ISlateStyle& Get();`
- L17 _public prototype_ `static FLinearColor GetColor(const FName& InName);`
- L18 _public prototype_ `static const FSlateBrush* GetBrush(const FName& InName);`
- L21 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`
- L23 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L25 _private prototype_ `static void SetupLayerViewStyles(const TSharedRef<FSlateStyleSet>& Style);`
- L26 _private prototype_ `static void SetupTextStyles(const TSharedRef<FSlateStyleSet>& Style);`

### `Source/Editor/MaterialEditor/Private/Tabs/MaterialEditorTabFactories.h` (Private)


#### struct `FMaterialGraphEditorSummoner`  
`struct FMaterialGraphEditorSummoner : public FDocumentTabFactoryForObjects<UEdGraph>`  
_L26-85_
- inherits: `FDocumentTabFactoryForObjects<UEdGraph>`
- L29 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UEdGraph*);`
- L31 _public prototype_ `FMaterialGraphEditorSummoner(TSharedPtr<class FMaterialEditor> InMaterialEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);`
- L33 _public prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;`
- L35 _public prototype_ `virtual void OnTabBackgrounded(TSharedPtr<SDockTab> Tab) const override;`
- L37 _public prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;`
- L39 _public prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L41 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const override;`
- L44 _protected function_ `virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override`
- L72 _protected prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L74 _protected prototype_ `virtual TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& SpawnArgs, TWeakPtr<FTabManager> WeakTabManager) const override;`
- L76 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L78 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L80 _protected prototype_ `virtual TSharedRef<FGenericTabHistory> CreateTabHistoryNode(TSharedPtr<FTabPayload> Payload) override;`
- L83 _protected member_ `TWeakPtr<class FMaterialEditor> MaterialEditorPtr;`
- L84 _protected member_ `FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;`

#### struct `FMaterialGraphTabHistory`  
`struct FMaterialGraphTabHistory : public FGenericTabHistory`  
_L91-121_
- inherits: `FGenericTabHistory`
- L98 _public function_ `FMaterialGraphTabHistory(TSharedPtr<FDocumentTabFactory> InFactory, TSharedPtr<FTabPayload> InPayload) : FGenericTabHistory(InFactory, InPayload) , SavedLocation(FVector2f::ZeroVector) , SavedZoomAmount(INDEX_NONE)` — @param InFactory		The factory used to regenerate the content @param InPayload		The payload object used to regenerate the content
- L106 _public prototype_ `virtual void EvokeHistory(TSharedPtr<FTabInfo> InTabInfo, bool bPrevTabMatches) override;`
- L108 _public prototype_ `virtual void SaveHistory() override;`
- L110 _public prototype_ `virtual void RestoreHistory() override;`
- L114 _private member_ `TWeakPtr< class SGraphEditor > GraphEditor;` — The graph editor represented by this history node. While this node is inactive, the graph editor is invalid
- L116 _private member_ `FDeprecateSlateVector2D SavedLocation;` — Saved location the graph editor was at when this history node was last visited
- L118 _private member_ `float SavedZoomAmount;` — Saved zoom the graph editor was at when this history node was last visited
- L120 _private member_ `FGuid SavedBookmarkId;` — Saved bookmark ID the graph editor was at when this history node was last visited

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "MaterialEditorTabFactories"`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UEdGraph*);`
- L47 _function_ `` (scope `FMaterialGraphEditorSummoner::ConstructTabNameForObject`)

### `Source/Editor/MaterialEditor/Public/FindInMaterial.h` (Public)


#### class `FFindInMaterialResult`  
`class FFindInMaterialResult`  
_L18-74_
- desc: Item that matched the search results
- L22 _public prototype_ `FFindInMaterialResult(const FString& InValue);` — Create a root (or only text) result
- L25 _public prototype_ `FFindInMaterialResult(const FString& InValue, TSharedPtr<FFindInMaterialResult>& InParent, UClass* InClass, int InDuplicationIndex);` — Create a listing for a search result
- L28 _public prototype_ `FFindInMaterialResult(const FString& InValue, TSharedPtr<FFindInMaterialResult>& InParent, UEdGraphPin* InPin);` — Create a listing for a pin result
- L31 _public prototype_ `FFindInMaterialResult(const FString& InValue, TSharedPtr<FFindInMaterialResult>& InParent, UEdGraphNode* InNode);` — Create a listing for a node result
- L34 _public prototype_ `FReply OnClick(TWeakPtr<class FMaterialEditor> MaterialEditor);` — Called when user clicks on the search item
- L37 _public prototype_ `FText GetCategory() const;` — Get Category for this search result
- L40 _public prototype_ `TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L43 _public prototype_ `FString GetCommentText() const;` — Gets the comment on this node if any
- L46 _public prototype_ `FString GetValueText() const;` — Gets the value of the pin if any
- L49 _public member_ `TArray< TSharedPtr<FFindInMaterialResult> > Children;` — Any children listed under this category
- L52 _public member_ `TWeakPtr<FFindInMaterialResult> Parent;` — Search result Parent
- L55 _public member_ `FString Value;` — The meta string that was stored in the asset registry for this item
- L58 _public member_ `int DuplicationIndex;` — The graph may have multiple instances of whatever we are looking for, this tells us which instance # we refer to
- L61 _public member_ `UClass* Class;` — The class this item refers to
- L64 _public member_ `FEdGraphPinReference Pin;` — The pin that this search result refers to
- L67 _public member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;` — The graph node that this search result refers to (if not by asset registry or UK2Node)
- L70 _public member_ `FString CommentText;` — Display text for comment information
- L73 _public member_ `bool bEmbeddedViaNode = false;` — Boolean for marking that the result was found embedded in another node e.g. cascading MFs

#### class `SFindInMaterial`  
`class SFindInMaterial : public SCompoundWidget`  
_L78-147_
- inherits: `SCompoundWidget`
- desc: Widget for searching for items that are part of a UEdGraph
- L81 _public function_ `SLATE_BEGIN_ARGS(SFindInMaterial)`
- L82 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FMaterialEditor> InMaterialEditor);`
- L87 _public prototype_ `void FocusForUse();` — Focuses this widget's search box
- L90 _public prototype_ `void PopulateSearchItems(const TArray<UEdGraphNode*>& Nodes);` — Clears out the existing search items and repopulates the list with these nodes
- L93 _protected typedef_ `typedef TSharedPtr<FFindInMaterialResult> FSearchResult;`
- L94 _protected typedef_ `typedef STreeView<FSearchResult> STreeViewType;`
- L97 _protected prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L100 _protected prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L103 _protected prototype_ `void OnGetChildren(FSearchResult InItem, TArray<FSearchResult>& OutChildren);` — Get the children of a row
- L106 _protected prototype_ `void OnTreeSelectionChanged(FSearchResult Item, ESelectInfo::Type SelectInfo);` — Called when user clicks on a new result
- L109 _protected prototype_ `void OnTreeSelectionDoubleClick(FSearchResult Item);` — Called when user double clicks on a new result
- L112 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L115 _protected prototype_ `void InitiateSearch();` — Begins the search based on the SearchValue
- L118 _protected prototype_ `void MatchTokens(const TArray<FString>& Tokens);` — Find any results that contain all of the tokens
- L121 _protected prototype_ `void MatchTokensInGraph(const UEdGraph* Graph, const TArray<FString>& Tokens);` — Find any results that contain all of the tokens in provided graph and subgraphs
- L124 _protected prototype_ `static bool StringMatchesSearchTokens(const TArray<FString>& Tokens, const FString& ComparisonString);` — Determines if a string matches the search tokens
- L128 _protected member_ `TWeakPtr<class FMaterialEditor> MaterialEditorPtr;` — Pointer back to the Material editor that owns us
- L131 _protected member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L134 _protected member_ `TSharedPtr<class SSearchBox> SearchTextField;` — The search text box
- L137 _protected member_ `TArray<FSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L140 _protected member_ `FSearchResult RootSearchResult;` — we need to keep a handle on the root result, because it won't show up in the tree
- L143 _protected member_ `FText HighlightText;` — The string to highlight in the results
- L146 _protected member_ `FString SearchValue;` — The string to search for

### `Source/Editor/MaterialEditor/Public/IMaterialEditor.h` (Public)


#### class `IMaterialEditor`  
`class IMaterialEditor : public FWorkflowCentricApplication, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L23-186_
- inherits: `FWorkflowCentricApplication,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Public interface to Material Editor
- L37 _public function_ `virtual UMaterialExpression* CreateNewMaterialExpression(UClass* NewExpressionClass, const FVector2D& NodePos, bool bAutoSelect, bool bAutoAssignResource, const class UEdGraph* Graph = nullptr)` — Creates a new material expression of the specified class. @param	NewExpressionClass		The type of material expression to add.  Must be a child of UMaterialExpression. @param	NodePos					Position of the new node. @param	bAutoSelect				If true, deselect all expressions and select the newly created one. @param	bAutoAssignResource		If true, assign resources to new expression. @param	Graph            		Graph to create new expression within. @return	UMaterialExpression*	Newly created material expression
- L47 _public function_ `virtual UMaterialExpressionComposite* CreateNewMaterialExpressionComposite(const FVector2D& NodePos, const class UEdGraph* Graph = nullptr)` — Creates a new material expression composite, along with related child pinbase expressions @param	NodePos							Position of the new composite @param	Graph							Graph to create new expression within. @return	UMaterialExpressionComposite*	Newly created material expression composite
- L57 _public function_ `virtual UMaterialExpressionComment* CreateNewMaterialExpressionComment(const FVector2D& NodePos, const class UEdGraph* Graph = nullptr)` — Creates a new material expression comment @param	NodePos						Position of the new comment @return	UMaterialExpressionComment*	Newly created material expression comment @param	Graph            			Graph to create new expression within.
- L62 _public function_ `virtual void ForceRefreshExpressionPreviews()` — Refreshes all material expression previews, regardless of whether or not realtime previews are enabled.
- L67 _public function_ `virtual void AddToSelection(UMaterialExpression* Expression)` — Add the specified material expression's graph node to the list of selected nodes
- L72 _public function_ `virtual void JumpToExpression(UMaterialExpression* Expression)` — Jumps to the node for this expression, if possible
- L77 _public function_ `virtual void DeleteSelectedNodes()` — Disconnects and removes the selected material graph nodes.
- L82 _public function_ `virtual void DeleteNodes(const TArray<class UEdGraphNode*>& NodesToDelete)` — Delete an array of Material Graph Nodes and their corresponding expressions/comments
- L87 _public function_ `virtual FText GetOriginalObjectName() const` — Gets the name of the material or material function that we are editing
- L92 _public function_ `virtual TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter() const` — Creates an IAssetReferenceFilter that can be used to check if an asset is valid to be used with this material.
- L98 _public function_ `virtual void UpdateMaterialAfterGraphChange()` — Re-links the material and updates its representation in the editor, used when graph is changed outside of editor code.
- L101 _public function_ `virtual void MarkMaterialDirty()` — Marks the material as dirty.
- L103 _public function_ `virtual void UpdateDetailView()`
- L110 _public function_ `virtual void JumpToHyperlink(const UObject* ObjectReference)` — Jumps to a specific node or graph @param	ObjectReference			Object to jump to
- L113 _public function_ `virtual bool CanPasteNodes() const` — Checks whether nodes can currently be pasted
- L116 _public function_ `virtual void PasteNodesHere(const FVector2D& Location, const class UEdGraph* Graph = nullptr)` — Paste nodes at a specific location
- L119 _public function_ `virtual int32 GetNumberOfSelectedNodes() const` — Gets the number of selected nodes
- L122 _public function_ `virtual TSet<UObject*> GetSelectedNodes() const` — Get the currently selected set of nodes
- L125 _public function_ `virtual void GetBoundsForNode(const UEdGraphNode* InNode, class FSlateRect& OutRect, float InPadding) const` — Get the visible bounds of the given graph node
- L134 _public function_ `virtual FMaterialRenderProxy* GetExpressionPreview(UMaterialExpression* InExpression)` — Gets the preview for an expression @param	InExpression			The expression to preview @return	FMaterialRenderProxy*	The expression preview
- L141 _public function_ `virtual void UpdateSearch( bool bQueryChanged )` — Updates the SearchResults array based on the search query @param	bQueryChanged		Indicates whether the update is because of a query change or a potential material content change.
- L144 _public prototype_ `virtual UMaterialInterface* GetMaterialInterface() const = 0;` — The material instance applied to the preview mesh.
- L147 _public prototype_ `virtual bool ApproveSetPreviewAsset(UObject* InAsset) = 0;` — Allows editor to veto the setting of a preview mesh
- L150 _public prototype_ `virtual void DrawMessages( FViewport* Viewport, FCanvas* Canvas ) = 0;` — Draws messages on the specified viewport and canvas.
- L153 _public prototype_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FRegisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being registered
- L154 _public function_ `virtual FRegisterTabSpawnersEvent& OnRegisterTabSpawners()`
- L157 _public prototype_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FUnregisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being unregistered
- L158 _public function_ `virtual FUnregisterTabSpawnersEvent& OnUnregisterTabSpawners()`
- L161 _public prototype_ `DECLARE_EVENT(IMaterialEditorModule, FMaterialEditorClosedEvent);` — Delegate to be called when this IMaterialEditor is about to be destroyed
- L162 _public function_ `virtual FMaterialEditorClosedEvent& OnMaterialEditorClosed()`
- L165 _public function_ `virtual void NotifyExternalMaterialChange()` — call this to notify the editor that the edited material changed from outside
- L168 _public function_ `virtual void RefreshGraphFromOriginal()` — Rebuild the preview + graph view from the asset under edit (Material or MaterialFunction).
- L171 _public function_ `virtual void GenerateInheritanceMenu(class UToolMenu* Menu)` — Fills inheritance drop down menu
- L174 _public function_ `virtual void RefreshStatsMaterials()` — Updates materials used in material stats
- L177 _public function_ `virtual void PreviewNode(UMaterialGraphNode* InGraphNode)` — Start/Stop Previewing the specified material graph node
- L180 _public function_ `virtual void SetCustomPrimitiveData(TConstArrayView<float> CustomFloats)` — Set the custom primitive data to use in the preview display area
- L183 _private member_ `FMaterialEditorClosedEvent MaterialEditorClosedEvent;`
- L184 _private member_ `FRegisterTabSpawnersEvent RegisterTabSpawnersEvent;`
- L185 _private member_ `FUnregisterTabSpawnersEvent UnregisterTabSpawnersEvent;`

#### Free symbols / members of external scopes

- L153 _delegate_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FRegisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being registered
- L157 _delegate_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FUnregisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being unregistered
- L161 _delegate_ `DECLARE_EVENT(IMaterialEditorModule, FMaterialEditorClosedEvent);` — Delegate to be called when this IMaterialEditor is about to be destroyed

### `Source/Editor/MaterialEditor/Public/MaterialEditingLibrary.h` (Public)


#### struct `FMaterialStatistics`  
`struct FMaterialStatistics`  
_L21-56_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public member_ `int32 NumVertexShaderInstructions = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Statistics)` — Number of instructions used by most expensive vertex shader in the material
- L31 _public member_ `int32 NumPixelShaderInstructions = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Statistics)` — Number of instructions used by most expensive pixel shader in the material
- L35 _public member_ `int32 NumSamplers = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Statistics)` — Number of samplers required by the material
- L39 _public member_ `int32 NumVertexTextureSamples = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Statistics)` — Number of textures sampled by the vertex shader
- L43 _public member_ `int32 NumPixelTextureSamples = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statistics)` — Number of textures sampled by the pixel shader
- L47 _public member_ `int32 NumVirtualTextureSamples = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statistics)` — Number of virtual textures sampled
- L51 _public member_ `int32 NumUVScalars = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statistics)` — Number of interpolator scalars required for UVs
- L55 _public member_ `int32 NumInterpolatorScalars = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statistics)` — Number of interpolator scalars required for user-defined interpolators

#### struct `FDebugShaderInfo`  
`struct FDebugShaderInfo`  
_L60-71_
- reflection: `USTRUCT(BlueprintType)`
- desc: This struct represents a single shader in a material.
- L66 _public member_ `FName VertexFactoryName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Statistics)` — Name of the vertex factory that this shader belongs to.  Could be NAME_None for material-only shaders.
- L70 _public member_ `FName ShaderTypeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Statistics)` — Name of the shader type for this shader

#### class `UMaterialEditingLibrary`  
`class UMaterialEditingLibrary : public UBlueprintFunctionLibrary`  
_L75-619_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint library for creating/editing Materials
- L92 _public prototype_ `static UMaterialExpression* CreateMaterialExpressionEx(UMaterial* Material, UMaterialFunction* MaterialFunction, TSubclassOf<UMaterialExpression> ExpressionClass, UObject* SelectedAsset = nullptr, int32 NodePosX = 0, int32 NodePosY = 0, bool bAllowMarkingPackageDirty = true);` — Create a new material expression node within the supplied material, optionally specifying asset to use @note	If a MaterialFunction and Material are specified, expression is added to Material and not MaterialFunction, assuming Material is a preview that will be copied to Function later by user. @param	Material					Material asset to add an expression to @param	MaterialFunction			Specified if adding an expression to a MaterialFunction, used as Outer for new expression object @param	SelectedAsset				If specified, new node will attempt to use this asset, if of the appropriate type (e.g. Texture for a TextureSampler) @param	ExpressionClass				Class of expression to add @param	NodePosX					X position of new expression node @param	NodePosY					Y position of new expression node @param	bAllowMarkingPackageDirty	Packages can't be marked dirty outside of the game thread. If this is false, package will need to be dirtied through other means.
- L99 _public prototype_ `static void RebuildMaterialInstanceEditors(UMaterial* BaseMaterial);` — Rebuilds dependent Material Instance Editors @param	BaseMaterial	Material that MaterialInstance must be based on for Material Instance Editor to be rebuilt
- L105 _public prototype_ `static void RebuildMaterialInstanceEditors(UMaterialFunction* BaseFunction);` — Rebuilds dependent Material Instance Editors @param	BaseMaterial	Material that MaterialInstance must be based on for Material Instance Editor to be rebuilt
- L114 _public prototype_ `static void RefreshMaterialEditor(UMaterial* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Refresh an open Material Editor's preview from its source asset. Call after script-driven edits so the editor reflects the change. No-op if no editor is open for the asset. Discards any in-editor edits not yet applied back to the asset. @param	Material	Material whose open editor should be refreshed.
- L122 _public prototype_ `static void RefreshMaterialFunctionEditor(UMaterialFunction* MaterialFunction);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Refresh an open Material Function Editor's preview from its source asset. Same semantics as RefreshMaterialEditor. @param	MaterialFunction	MaterialFunction whose open editor should be refreshed.
- L131 _public prototype_ `static void RefreshMaterialInstanceEditor(UMaterialInstanceConstant* Instance);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Refresh an open Material Instance Editor's parameter and inheritance views. Call after script-driven edits so the editor reflects the change. No-op if no editor is open for the instance. @param	Instance	Material Instance whose open editor should be refreshed.
- L137 _public prototype_ `static TArray<UMaterialExpression*> GetMaterialFunctionExpressions(const UMaterialFunction* MaterialFunction);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — returns the Expressions contained in this Material Function. Does not include nested Expressions.
- L141 _public prototype_ `static TArray<UMaterialExpression*> GetMaterialExpressions(const UMaterial* Material);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — returns the Expressions contained in this Material. Does not include nested Expressions.
- L145 _public prototype_ `static int32 GetNumMaterialExpressions(const UMaterial* Material);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Returns number of material expressions in the supplied material
- L150 _public prototype_ `static void DeleteAllMaterialExpressions(UMaterial* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Delete all material expressions in the supplied material
- L154 _public prototype_ `static void DeleteMaterialExpression(UMaterial* Material, UMaterialExpression* Expression);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Delete a specific expression from a material. Will disconnect from other expressions.
- L158 _public prototype_ `static void DeleteUnusedExpressions(UMaterial* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Delete all expressions not reachable from any material output. Call recompile afterwards.
- L168 _public prototype_ `static UMaterialExpression* CreateMaterialExpression(UMaterial* Material, TSubclassOf<UMaterialExpression> ExpressionClass, int32 NodePosX=0, int32 NodePosY=0);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Create a new material expression node within the supplied material @param	Material			Material asset to add an expression to @param	ExpressionClass		Class of expression to add @param	NodePosX			X position of new expression node @param	NodePosY			Y position of new expression node
- L179 _public prototype_ `static UMaterialExpression* DuplicateMaterialExpression(UMaterial* Material, UMaterialFunction* MaterialFunction, UMaterialExpression* Expression);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Duplicates the provided material expression adding it to the same material / material function, and copying parameters. Note: Does not duplicate transient properties (Ex: GraphNode). @param	Material			Material asset to add an expression to @param	MaterialFunction	Specified if adding an expression to a MaterialFunction, used as Outer for new expression object @param	SourceExpression	Expression to be duplicated
- L188 _public prototype_ `static bool SetMaterialUsage(UMaterial* Material, EMaterialUsage Usage, bool& bNeedsRecompile);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing", meta = (DeprecatedFunction, DeprecationMessage = "Use SetBaseMaterialUsage instead"))` — Enable a particular usage for the supplied material (e.g. SkeletalMesh, ParticleSprite etc) @param	Material			Material to change usage for @param	Usage				New usage type to enable for this material @param	bNeedsRecompile		Returned to indicate if material needs recompiling after this change
- L196 _public prototype_ `static bool HasMaterialUsage(UMaterialInterface* Material, EMaterialUsage Usage);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Check if a particular usage is enabled for the supplied material (e.g. SkeletalMesh, ParticleSprite etc) @param	Material			Material to check usage for @param	Usage				Usage type to check for this material
- L205 _public prototype_ `static void SetBaseMaterialUsage(UMaterial* Material, EMaterialUsage Usage, bool bValue = true);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Enable or disable a particular usage for the supplied material @param	Material			Material to change usage for @param	Usage				Usage type @param	bValue				Whether to enable the usage
- L213 _public prototype_ `static bool HasMaterialUsageOverride(UMaterialInstanceConstant* MaterialInstance, EMaterialUsage Usage);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Check if a if the supplied material instance has an override for the particular usage @param	MaterialInstance	Material instance to check override for @param	Usage				Usage type to check for this material
- L223 _public prototype_ `static void SetMaterialUsageOverride(UMaterialInstanceConstant* MaterialInstance, EMaterialUsage Usage, bool bOverride = true, bool bValue = true);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the material usage override for the supplied material instance @param	MaterialInstance	Material instance to change usage for @param	Usage				Usage type @param	bOverride			Whether to enable the override (set to false to default to Parent setting) @param	bValue				Whether to enable the usage (only if bOverride is true)
- L232 _public prototype_ `static bool ConnectMaterialProperty(UMaterialExpression* FromExpression, FString FromOutputName, EMaterialProperty Property);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Connect a material expression output to one of the material property inputs (e.g. diffuse color, opacity etc) @param	FromExpression		Expression to make connection from @param	FromOutputName		Name of output of FromExpression to make connection from @param	Property			Property input on material to make connection to
- L242 _public prototype_ `static bool ConnectMaterialExpressions(UMaterialExpression* FromExpression, FString FromOutputName, UMaterialExpression* ToExpression, FString ToInputName);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Create connection between two material expressions @param	FromExpression		Expression to make connection from @param	FromOutputName		Name of output of FromExpression to make connection from. Leave empty to use first output. @param	ToExpression		Expression to make connection to @param	ToInputName			Name of input of ToExpression to make connection to. Leave empty to use first input.
- L251 _public prototype_ `static bool DisconnectMaterialExpressions(UMaterialExpression* ToExpression, FString ToInputName);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Disconnect the input pin of a material expression, removing whatever is currently connected to it. @param	ToExpression	Expression whose input pin should be disconnected @param	ToInputName		Name of the input pin to disconnect. @return	true if a connection was broken, false if the pin was already disconnected or not found
- L260 _public prototype_ `static bool DisconnectMaterialProperty(UMaterial* Material, EMaterialProperty Property);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Disconnect the expression node currently connected to a material property input (e.g. base color, roughness). @param	Material	Material asset to modify @param	Property	Property input on material to disconnect @return	true if a connection was broken, false if the input was already disconnected
- L267 _public prototype_ `static TArray<FString> RecompileMaterial(UMaterial* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Trigger a recompile of a material. Must be performed after making changes to the graph to have changes reflected. @return Any compiler error messages produced during compilation. Empty if compilation succeeded.
- L270 _public prototype_ `DECLARE_DELEGATE(FOnItemComplete) static void RecompileMaterials(TArray<UMaterial*>& Materials, FOnItemComplete const& OnItemComplete);` — Item complete callback for use when processing arrays of items. Allows higher level to tick UI etc.
- L286 _public prototype_ `static TArray<FDebugShaderInfo> GetShaderInfoFromTypeInfo(const TArray<FDebugShaderTypeInfo>& InShaderTypeInfos);` — Flattens shader type info into a flat list of individual shader entries, stripping the per-type grouping from FDebugShaderTypeInfo. @param InShaderTypeInfos  Grouped shader type information (e.g., from GetDebugShaderTypeInfo) @return Flat array of all individual FDebugShaderInfo across all types
- L292 _public prototype_ `static void LayoutMaterialExpressions(UMaterial* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Layouts the expressions in a grid pattern
- L296 _public prototype_ `static float GetMaterialDefaultScalarParameterValue(UMaterial* Material, FName ParameterName);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the default scalar (float) parameter value from a Material
- L301 _public prototype_ `static UTexture* GetMaterialDefaultTextureParameterValue(UMaterial* Material, FName ParameterName);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the default texture parameter value from a Material
- L305 _public prototype_ `static FLinearColor GetMaterialDefaultVectorParameterValue(UMaterial* Material, FName ParameterName);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the default vector parameter value from a Material
- L309 _public prototype_ `static bool GetMaterialDefaultStaticSwitchParameterValue(UMaterial* Material, FName ParameterName);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the default static switch parameter value from a Material
- L313 _public prototype_ `static TSet<UObject*> GetMaterialSelectedNodes(UMaterial* Material);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the set of selected nodes from an active material editor
- L317 _public prototype_ `static UMaterialExpression* GetMaterialPropertyInputNode(UMaterial* Material, EMaterialProperty Property);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the node providing the output for a given material property from an active material editor
- L321 _public prototype_ `static FString GetMaterialPropertyInputNodeOutputName(UMaterial* Material, EMaterialProperty Property);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the node output name providing the output for a given material property from an active material editor
- L325 _public prototype_ `static TArray<FString> GetMaterialExpressionInputNames(UMaterialExpression* MaterialExpression);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the array of input pin names for a material expression
- L329 _public prototype_ `static TArray<int32> GetMaterialExpressionInputTypes(UMaterialExpression* MaterialExpression);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the array of input pin types for a material expression
- L333 _public prototype_ `static TArray<FString> GetMaterialExpressionOutputNames(UMaterialExpression* MaterialExpression);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the array of output pin names for a material expression
- L337 _public prototype_ `static TArray<UMaterialExpression*> GetInputsForMaterialExpression(UMaterial* Material, UMaterialExpression* MaterialExpression);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the set of nodes acting as inputs to a node from an active material editor
- L341 _public prototype_ `static TArray<UMaterialExpression*> GetInputsForMaterialFunctionExpression(UMaterialFunction* MaterialFunction, UMaterialExpression* MaterialExpression);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the set of nodes acting as inputs to a node in a material function graph
- L345 _public prototype_ `static bool GetInputNodeOutputNameForMaterialExpression(UMaterialExpression* MaterialExpression, UMaterialExpression* InputNode, FString& OutputName);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the output name of input node connected to MaterialExpression from an active material editor
- L349 _public prototype_ `static void GetMaterialExpressionNodePosition(UMaterialExpression* MaterialExpression, int32& NodePosX, int32& NodePosY);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the position of the MaterialExpression node.
- L353 _public prototype_ `static TArray<UTexture*> GetUsedTextures(UMaterial* Material);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing", meta = (DeprecatedFunction, DeprecationMessage = "Use GetMaterialUsedTextures instead since it works with Material Instances."))` — Get the list of textures used by a material
- L357 _public prototype_ `static TArray<UTexture*> GetMaterialUsedTextures(UMaterialInterface* MaterialInterface);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the list of textures used by a material
- L363 _public prototype_ `static int32 GetNumMaterialExpressionsInFunction(const UMaterialFunction* MaterialFunction);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Returns number of material expressions in the supplied material
- L373 _public prototype_ `static UMaterialExpression* CreateMaterialExpressionInFunction(UMaterialFunction* MaterialFunction, TSubclassOf<UMaterialExpression> ExpressionClass, int32 NodePosX = 0, int32 NodePosY = 0);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Create a new material expression node within the supplied material function @param	MaterialFunction	Material function asset to add an expression to @param	ExpressionClass		Class of expression to add @param	NodePosX			X position of new expression node @param	NodePosY			Y position of new expression node
- L377 _public prototype_ `static void DeleteAllMaterialExpressionsInFunction(UMaterialFunction* MaterialFunction);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Delete all material expressions in the supplied material function
- L381 _public prototype_ `static void DeleteMaterialExpressionInFunction(UMaterialFunction* MaterialFunction, UMaterialExpression* Expression);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Delete a specific expression from a material function. Will disconnect from other expressions.
- L388 _public prototype_ `static void UpdateMaterialFunction(UMaterialFunctionInterface* MaterialFunction, UMaterial* PreviewMaterial = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing", meta = (HidePin = "PreviewMaterial"))` — Update a Material Function after edits have been made. Will recompile any Materials that use the supplied Material Function.
- L396 _public prototype_ `static void UpdateMaterialFunctions(TArray<UMaterialFunctionInterface*>& MaterialFunctions, FOnItemComplete const& OnItemComplete);` — Update an array of Material Functions after edits have been made. Will recompile any Materials that use the supplied Material Function. Faster than individual calls to UpdateMaterialFunction(). Calls OnItemComplete after each material function is processed.
- L402 _public prototype_ `static void LayoutMaterialFunctionExpressions(UMaterialFunction* MaterialFunction);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Layouts the expressions in a grid pattern
- L408 _public prototype_ `static void SetMaterialInstanceParent(UMaterialInstanceConstant* Instance, UMaterialInterface* NewParent);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the parent Material or Material Instance to use for this Material Instance
- L412 _public prototype_ `static void ClearAllMaterialInstanceParameters(UMaterialInstanceConstant* Instance);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Clears all material parameters set by this Material Instance
- L417 _public prototype_ `static float GetMaterialInstanceScalarParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the current scalar (float) parameter value from a Material Instance
- L421 _public prototype_ `static bool SetMaterialInstanceScalarParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, float Value, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the scalar (float) parameter value for a Material Instance
- L426 _public prototype_ `static UTexture* GetMaterialInstanceTextureParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the current texture parameter value from a Material Instance
- L430 _public prototype_ `static bool SetMaterialInstanceTextureParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, UTexture* Value, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the texture parameter value for a Material Instance
- L435 _public prototype_ `static URuntimeVirtualTexture* GetMaterialInstanceRuntimeVirtualTextureParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the current texture parameter value from a Material Instance
- L439 _public prototype_ `static bool SetMaterialInstanceRuntimeVirtualTextureParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, URuntimeVirtualTexture* Value, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the texture parameter value for a Material Instance
- L444 _public prototype_ `static USparseVolumeTexture* GetMaterialInstanceSparseVolumeTextureParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the current texture parameter value from a Material Instance
- L448 _public prototype_ `static bool SetMaterialInstanceSparseVolumeTextureParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, USparseVolumeTexture* Value, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the texture parameter value for a Material Instance
- L453 _public prototype_ `static FLinearColor GetMaterialInstanceVectorParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the current vector parameter value from a Material Instance
- L457 _public prototype_ `static bool SetMaterialInstanceVectorParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, FLinearColor Value, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the vector parameter value for a Material Instance
- L461 _public prototype_ `static bool GetMaterialInstanceStaticSwitchParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Get the current static switch parameter value from a Material Instance
- L465 _public prototype_ `static bool SetMaterialInstanceStaticSwitchParameterValue(UMaterialInstanceConstant* Instance, FName ParameterName, bool Value, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter, bool bUpdateMaterialInstance = true);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set the static switch parameter value for a Material Instance
- L475 _public prototype_ `static bool IsMaterialInstanceParameterOverridden(UMaterialInstanceConstant* Instance, FName ParameterName, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintPure, Category = "MaterialEditing")` — Check whether a parameter is overridden in this Material Instance. @param	Instance		Material Instance to query @param	ParameterName	Name of the parameter @param	Association		Parameter association type @return Whether the parameter is overridden in this instance
- L486 _public prototype_ `static bool SetMaterialInstanceParameterOverride(UMaterialInstanceConstant* Instance, FName ParameterName, bool bOverride, EMaterialParameterAssociation Association = EMaterialParameterAssociation::GlobalParameter);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Set whether a parameter override is enabled in this Material Instance. @param	Instance		Material Instance to modify @param	ParameterName	Name of the parameter @param	bOverride		Whether the parameter should be overridden @param	Association		Parameter association type @return Whether the operation succeeded (false if Instance is null or the parameter was not found)
- L490 _public prototype_ `static void UpdateMaterialInstance(UMaterialInstanceConstant* Instance);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Called after making modifications to a Material Instance to recompile shaders etc.
- L494 _public prototype_ `static void GetChildInstances(UMaterialInterface* Parent, TArray<FAssetData>& ChildInstances);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Gets all direct child mat instances
- L498 _public prototype_ `static void GetMaterialsReferencingFunction(UMaterialFunction* InFunction, TArray<FAssetData>& OutMaterials);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Gets all materials that use a material function
- L502 _public prototype_ `static void GetScalarParameterNames(UMaterialInterface* Material, TArray<FName>& ParameterNames);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Gets all scalar parameter names
- L506 _public prototype_ `static void GetVectorParameterNames(UMaterialInterface* Material, TArray<FName>& ParameterNames);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Gets all vector parameter names
- L510 _public prototype_ `static void GetTextureParameterNames(UMaterialInterface* Material, TArray<FName>& ParameterNames);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Gets all texture parameter names
- L514 _public prototype_ `static void GetStaticSwitchParameterNames(UMaterialInterface* Material, TArray<FName>& ParameterNames);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Gets all static switch parameter names
- L524 _public prototype_ `static bool GetScalarParameterSource(UMaterialInterface* Material, const FName ParameterName, FSoftObjectPath& ParameterSource);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns the path of the asset where the parameter originated, as well as true/false if it was found @param	Material	The material or material instance you want to look up a parameter from @param	ParameterName		The parameter name @param	ParameterSource		The soft object path of the asset the parameter originates in @return	Whether or not the parameter was found in this material
- L534 _public prototype_ `static bool GetVectorParameterSource(UMaterialInterface* Material, const FName ParameterName, FSoftObjectPath& ParameterSource);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns the path of the asset where the parameter originated, as well as true/false if it was found @param	Material	The material or material instance you want to look up a parameter from @param	ParameterName		The parameter name @param	ParameterSource		The soft object path of the asset the parameter originates in @return	Whether or not the parameter was found in this material
- L544 _public prototype_ `static bool GetTextureParameterSource(UMaterialInterface* Material, const FName ParameterName, FSoftObjectPath& ParameterSource);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns the path of the asset where the parameter originated, as well as true/false if it was found @param	Material	The material or material instance you want to look up a parameter from @param	ParameterName		The parameter name @param	ParameterSource		The soft object path of the asset the parameter originates in @return	Whether or not the parameter was found in this material
- L566 _public prototype_ `static bool RenameMaterialParameterGroup(UMaterial* Material, const FName OldGroupName, const FName NewGroupName);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Renames a material parameter group within the specified material. This function allows you to rename an existing parameter group in a material. It iterates all parameters within the material, finds all the one belonging to the `OldGroupName` group and switches those parameters to be in the `NewGroupName` group.  This function only affects parameters that belong to the specified group. To remove the groups from the parameters the new group name can be 'None'.  If the OldGroupName does not exist in the material, the function will return false.   If the NewGroupName already exists, the parameters will be "merged" into the existing group. @param Material       The material asset in which the parameter group resides. @param OldGroupName   The current name of the parameter group to rename. @param NewGroupName   The new name to assign to the parameter group. @return true if the rename operation was successful; false otherwise. @see RenameMaterialFunctionParameterGroup
- L588 _public prototype_ `static bool RenameMaterialFunctionParameterGroup(UMaterialFunctionInterface* MaterialFunction, const FName OldGroupName, const FName NewGroupName);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Renames a material parameter group within the specified material function. This function allows you to rename an existing parameter group in a material function. It iterates all parameters within the material function, finds all the one belonging to the `OldGroupName` group and switches those parameters to be in the `NewGroupName` group.  This function only affects parameters that belong to the specified group. To remove the groups from the parameters the new group name can be 'None'.  If the OldGroupName does not exist in the material, the function will return false.   If the NewGroupName already exists, the parameters will be "merged" into the existing group. @param MaterialFunction	The material function asset in which the parameter group resides. @param OldGroupName		The current name of the parameter group to rename. @param NewGroupName		The new name to assign to the parameter group. @return true if the rename operation was successful; false otherwise. @see RenameMaterialParameterGroup
- L598 _public prototype_ `static bool GetStaticSwitchParameterSource(UMaterialInterface* Material, const FName ParameterName, FSoftObjectPath& ParameterSource);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns the path of the asset where the parameter originated, as well as true/false if it was found @param	Material	The material or material instance you want to look up a parameter from @param	ParameterName		The parameter name @param	ParameterSource		The soft object path of the asset the parameter originates in @return	Whether or not the parameter was found in this material
- L602 _public prototype_ `static int32 GetNumShaderTypes(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns the number of shader types (including pipeline shader types) for the given material.
- L606 _public prototype_ `static TArray<FDebugShaderInfo> ListShaders(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns a list of all the shaders contained in this material.
- L610 _public prototype_ `static FMaterialStatistics GetStatistics(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns statistics about the given material
- L614 _public prototype_ `static UMaterialInterface* GetNaniteOverrideMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "MaterialEditing")` — Returns any nanite override material for the given material
- L617 _private prototype_ `static void RecompileMaterialInternal(const TArray<UMaterial*>& Material, const FOnItemComplete* OnItemComplete);`
- L618 _private prototype_ `static void UpdateMaterialFunctionInternal(FMaterialUpdateContext& UpdateContext, UMaterialFunctionInterface* MaterialFunction, UMaterial* PreviewMaterial);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MATERIALEDITOR_API`
- L270 _delegate_ `DECLARE_DELEGATE(FOnItemComplete) static void RecompileMaterials(TArray<UMaterial*>& Materials, FOnItemComplete const& OnItemComplete);` — Item complete callback for use when processing arrays of items. Allows higher level to tick UI etc.

### `Source/Editor/MaterialEditor/Public/MaterialEditor/MaterialNodes/SGraphNodeMaterialBase.h` (Public)


#### class `FPreviewViewport`  
`class FPreviewViewport : public ISlateViewport`  
_L33-59_
- inherits: `ISlateViewport`
- L36 _public prototype_ `FPreviewViewport(class UMaterialGraphNode* InNode);`
- L37 _public prototype_ `~FPreviewViewport();`
- L40 _public prototype_ `virtual TUniquePtr<UE::Slate::FPaintScope> Paint(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, const int32 LayerId, const FWidgetStyle& InWidgetStyle, const bool bParentEnabled) override;` — ISlateViewport interface
- L41 _public prototype_ `virtual FIntPoint GetSize() const override;`
- L42 _public function_ `virtual class FSlateShaderResource* GetViewportRenderTargetTexture() const override`
- L43 _public function_ `virtual bool RequiresVsync() const override`
- L44 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L45 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L49 _public member_ `UMaterialGraphNode* MaterialNode;` — Material node to get expression preview from
- L51 _public member_ `FThreadSafePreviewPtr PreviewElement;` — Custom Slate Element to display the preview
- L53 _public member_ `TOptional<FVector2D> HoveredUV;` — The current UV we are hovered over, if any.
- L58 _private prototype_ `void UpdatePreviewNodeRenderProxy();` — Updates the expression preview render proxy from a graph node

#### class `FPreviewElement`  
`class FPreviewElement : public ICustomSlateElement`  
_L61-124_
- inherits: `ICustomSlateElement`
- L64 _public prototype_ `FPreviewElement();`
- L65 _public prototype_ `virtual ~FPreviewElement();`
- L78 _public prototype_ `bool BeginRenderingCanvas(const FIntRect& InCanvasRect, const FIntRect& InClippingRect, UMaterialGraphNode* InGraphNode, bool bInIsRealtime, bool bInShouldReadback);` — Sets up the canvas for rendering @param	InCanvasRect			Size of the canvas tile @param	InClippingRect			How to clip the canvas tile @param	InGraphNode				The graph node for the material preview @param	bInIsRealtime			Whether preview is using realtime values @param	bInShouldReadback		Whether we should readback the render target data or not @return	Whether there is anything to render
- L83 _public prototype_ `void UpdateExpressionPreview(UMaterialGraphNode* PreviewNode);` — Updates the expression preview render proxy from a graph node on the render thread
- L88 _public prototype_ `TOptional<FLinearColor> GetReadbackValue(const FVector2D& UV) const;` — Returns the readback value at the provided coordinated, unset if no readback data existss.
- L93 _public prototype_ `void ClearReadback();` — Clear any pending readbacks that may be in flight to ensure we don't read stale data later.
- L99 _private prototype_ `virtual void Draw_RenderThread(FRDGBuilder& GraphBuilder, const FDrawPassInputs& Inputs) override;` — ICustomSlateElement interface
- L101 _private prototype_ `void Readback_RenderThread(FRDGBuilder& GraphBuilder);`
- L105 _private member_ `TUniquePtr<class FSlateMaterialPreviewRenderTarget> RenderTarget;` — Render target that the canvas renders to
- L107 _private member_ `FMaterialRenderProxy* ExpressionPreview = nullptr;` — Render proxy for the expression preview
- L109 _private member_ `bool bIsRealtime = false;` — Whether preview is using realtime values
- L112 _private member_ `bool bShouldReadback = false;` — Used on the render thread to determine if we should readback the data or not.
- L114 _private member_ `bool bReadbackPending = false;` — Used on the render thread to determine if we have a readback in flight or not.
- L116 _private member_ `TUniquePtr<class FSlateMaterialPreviewRenderTarget> ReadbackRenderTarget;` — Readback render target, different from the regular render target as we need float range
- L118 _private member_ `TUniquePtr<class FRHIGPUTextureReadback> GPUTextureReadback;` — Readback primitive
- L120 _private member_ `static constexpr int32 ReadbackDimension = 128;`
- L122 _private member_ `mutable UE::FMutex ReadbackDataGuard;`
- L123 _private member_ `TArray<FFloat16Color> ReadbackData;`

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SGraphNodeMaterialBase>`  
_L127-130_
- L129 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeMaterialBase`  
`class SGraphNodeMaterialBase : public SGraphNode`  
_L132-193_
- inherits: `SGraphNode`
- L135 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMaterialBase)`
- L136 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UMaterialGraphNode* InNode);`
- L141 _public prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface
- L145 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;` — SNodePanel::SNode interface
- L148 _public function_ `UMaterialGraphNode* GetMaterialGraphNode() const`
- L151 _public prototype_ `virtual void PopulateMetaTag(class FGraphNodeMetaData* TagMeta) const override;` — Populate a meta data tag with information about this graph node
- L155 _protected prototype_ `virtual void AddPin( const TSharedRef<SGraphPin>& PinToAdd ) override;` — SGraphNode interface
- L156 _protected prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L157 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleRightWidget() override;`
- L159 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L160 _protected prototype_ `virtual void OnAdvancedViewChanged(const ECheckBoxState NewCheckedState) override;`
- L164 _protected prototype_ `TSharedRef<SWidget> CreatePreviewWidget();` — Creates a preview viewport if necessary
- L167 _protected prototype_ `EVisibility ExpressionPreviewVisibility() const;` — Returns visibility of Expression Preview viewport
- L170 _protected prototype_ `FText ExpressionPreviewOverlayText() const;` — Returns text to over lay over the expression preview viewport
- L173 _protected prototype_ `FText ExpressionPreviewValueText() const;` — Returns text to over lay as the tooltip value text
- L176 _protected prototype_ `FReply OnTogglePreviewClicked();` — Called when we click to preview node button
- L179 _protected prototype_ `void OnExpressionPreviewChanged(const ECheckBoxState NewCheckedState);` — Show/hide Expression Preview
- L182 _protected prototype_ `ECheckBoxState IsExpressionPreviewChecked() const;` — hidden == unchecked, shown == checked
- L185 _protected prototype_ `const FSlateBrush* GetExpressionPreviewArrow() const;` — Up when shown, down when hidden
- L189 _protected member_ `TSharedPtr<FPreviewViewport> PreviewViewport;` — Slate viewport for rendering preview via custom slate element
- L192 _protected member_ `UMaterialGraphNode* MaterialNode;` — Cached material graph node pointer to avoid casting

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MATERIALEDITOR_API`
- L31 _typedef_ `typedef TSharedPtr<class FPreviewElement, ESPMode::ThreadSafe> FThreadSafePreviewPtr;`

### `Source/Editor/MaterialEditor/Public/MaterialEditor/MaterialNodes/SGraphNodeMaterialComposite.h` (Public)


#### class `SGraphNodeMaterialComposite`  
`class SGraphNodeMaterialComposite : public SGraphNodeMaterialBase`  
_L20-47_
- inherits: `SGraphNodeMaterialBase`
- desc: @TODO: This class is mostly C&P from UK2Node_Composite, consolidate composites to not be BP specific.
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMaterialComposite)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMaterialGraphNode_Composite* InNode);`
- L29 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L30 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L34 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;` — SNodePanel::SNode interface
- L37 _protected prototype_ `virtual UEdGraph* GetInnerGraph() const;`
- L40 _private prototype_ `FText GetPreviewCornerText() const;`
- L41 _private prototype_ `FText GetTooltipTextForNode() const;`
- L43 _private prototype_ `TSharedRef<SWidget> CreateNodeBody();`
- L46 _private member_ `UMaterialGraphNode_Composite* CompositeNode;` — Cached material graph node pointer to avoid casting

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditor/MaterialNodes/SGraphNodeMaterialConvert.h` (Public)


#### class `FConvertDragDropOp`  
`class FConvertDragDropOp : public FDragDropOperation`  
_L23-41_
- inherits: `FDragDropOperation`
- L26 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FConvertDragDropOp, FDragDropOperation) FConvertDragDropOp(TSharedPtr<SConvertInnerPin> InSourcePin);`
- L31 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;`
- L35 _public prototype_ `TSharedPtr<SConvertInnerPin> GetSourcePin() const;`
- L36 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetScreenPosition() const;`
- L39 _protected member_ `TSharedPtr<SConvertInnerPin> SourcePin;`
- L40 _protected member_ `FVector2f ScreenPosition;`

#### class `SMaterialExpressionConvertGraphPin`  
`class SMaterialExpressionConvertGraphPin : public SGraphPin`  
_L47-64_
- inherits: `SGraphPin`
- L50 _public function_ `SLATE_BEGIN_ARGS(SMaterialExpressionConvertGraphPin)`
- L51 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L55 _public prototype_ `void CreateInnerPins(TSharedRef<SGraphNodeMaterialConvert> InOwningGraphNodeWidget);`
- L57 _public function_ `const TArray<TSharedRef<SConvertInnerPin>>& GetInnerPins() const`
- L59 _public prototype_ `bool IsHoveredOverPrimaryPin() const;`
- L63 _private member_ `TArray<TSharedRef<SConvertInnerPin>> InnerPins;` — Inner Pins, one for each component

#### class `SConvertInnerPin`  
`class SConvertInnerPin : public SCompoundWidget`  
_L71-140_
- inherits: `SCompoundWidget`
- desc: Class for the inner pins we'll use to route values in SGraphNodeMaterialConvert
- L74 _public function_ `SLATE_BEGIN_ARGS(SConvertInnerPin)`
- L75 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedPtr<SGraphNodeMaterialConvert> InOwningNode, TSharedPtr<SMaterialExpressionConvertGraphPin> InOwningPin, bool bInIsInputPin, int32 InPinIndex, int32 InComponentIndex );`
- L87 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L96 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L97 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L98 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L99 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L102 _public prototype_ `const FSlateBrush* GetPinBrush() const;`
- L103 _public prototype_ `void CancelDragDrop();`
- L104 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetPinCenterAbsolute() const;`
- L107 _public prototype_ `void AddConnection(TSharedPtr<SConvertInnerPin> InOtherPin);` — Adds a connection to WeakConnectedPins
- L110 _public prototype_ `void RemoveConnection(TSharedPtr<SConvertInnerPin> InOtherPin);` — Removes a connection from WeakConnectedPins
- L113 _public prototype_ `void RemoveAllConnections();` — Clears WeakConnectedPins
- L116 _public prototype_ `void BreakConnections();` — Calls into the owning node to break connections and refresh the material node
- L118 _public prototype_ `EVisibility GetDefaultValueVisibility() const;`
- L119 _public prototype_ `TOptional<float> GetDefaultValue() const;`
- L120 _public prototype_ `void SetDefaultValue(float InDefaultValue, ETextCommit::Type CommitType);`
- L122 _public prototype_ `EVisibility GetPinNameVisibility() const;`
- L123 _public prototype_ `FText GetPinName() const;`
- L125 _public function_ `bool IsInputPin() const`
- L126 _public function_ `int32 GetPinIndex() const`
- L127 _public function_ `int32 GetComponentIndex() const`
- L131 _protected member_ `TWeakPtr<SGraphNodeMaterialConvert> WeakOwningNode;` — Input Data
- L132 _protected member_ `TWeakPtr<SMaterialExpressionConvertGraphPin> WeakOwningPin;`
- L133 _protected member_ `bool bIsInputPin = false;`
- L134 _protected member_ `int32 PinIndex = INDEX_NONE;`
- L135 _protected member_ `int32 ComponentIndex = INDEX_NONE;`
- L137 _protected member_ `TSharedPtr<SImage> PinImage;`
- L138 _protected member_ `TSet<TWeakPtr<SConvertInnerPin>> WeakConnectedPins;`
- L139 _protected member_ `mutable FVector2f CenterAbsolute;`

#### class `SGraphNodeMaterialConvert`  
`class SGraphNodeMaterialConvert : public SGraphNodeMaterialBase`  
_L146-203_
- inherits: `SGraphNodeMaterialBase`
- L149 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMaterialConvert)`
- L150 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UMaterialGraphNode* InNode);`
- L155 _public prototype_ `virtual void CreatePinWidgets() override;`
- L156 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L157 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L159 _public prototype_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;`
- L160 _public prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;`
- L161 _public prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L164 _public prototype_ `FReply OnAddInputPinClicked();`
- L165 _public prototype_ `FReply OnAddOutputPinClicked();`
- L167 _public prototype_ `TSharedRef<SWidget> CreateAddPinContextMenu(bool bInputPin);`
- L168 _public prototype_ `void AddNewPin(bool bInputPin, EMaterialExpressionConvertType ConvertType);`
- L171 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L182 _public prototype_ `void FormConnection(TSharedPtr<SConvertInnerPin> InnerPinA, TSharedPtr<SConvertInnerPin> InnerPinB);`
- L183 _public prototype_ `void BreakConnections(TSharedPtr<SConvertInnerPin> InnerPin);`
- L185 _public prototype_ `TOptional<float> GetDefaultValue(TSharedPtr<const SConvertInnerPin> InnerPin) const;`
- L186 _public prototype_ `void SetDefaultValue(TSharedPtr<SConvertInnerPin> InnerPin, const float InDefaultValue);`
- L188 _public function_ `void SetCurrentDragDropOp(TSharedPtr<FConvertDragDropOp> InDragDropOp)`
- L189 _public function_ `TSharedPtr<FConvertDragDropOp> GetCurrentDragDropOp() const`
- L192 _protected prototype_ `TSharedPtr<SConvertInnerPin> GetInnerPin(bool bInputPin, const int32 InPinIndex, const int32 InComponentIndex) const;`
- L193 _protected prototype_ `void MakeConnectionCurve( const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& InOutLayerId, const FVector2f& InCurveStart, const FVector2f& InCurveEnd ) const;`
- L202 _private member_ `TSharedPtr<FConvertDragDropOp> CurrentDragDropOp;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditor/MaterialNodes/SGraphNodeMaterialCustom.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNodeMaterialCustom>`  
_L15-18_
- L17 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeMaterialCustom`  
`class SGraphNodeMaterialCustom : public SGraphNodeMaterialBase`  
_L20-52_
- inherits: `SGraphNodeMaterialBase`
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMaterialCustom)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UMaterialGraphNode* InNode);`
- L28 _public function_ `UMaterialGraphNode* GetMaterialGraphNode() const`
- L30 _public prototype_ `FText GetHlslText() const;`
- L31 _public prototype_ `void OnCustomHlslTextCommited(const FText& InText, ETextCommit::Type InType);`
- L35 _protected prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;` — SGraphNode interface
- L36 _protected prototype_ `virtual void CreateAdvancedViewArrow(TSharedPtr<SVerticalBox> MainBox) override;`
- L37 _protected prototype_ `virtual EVisibility AdvancedViewArrowVisibility() const override;`
- L38 _protected prototype_ `virtual void OnAdvancedViewChanged( const ECheckBoxState NewCheckedState ) override;`
- L39 _protected prototype_ `virtual ECheckBoxState IsAdvancedViewChecked() const override;`
- L40 _protected prototype_ `virtual const FSlateBrush* GetAdvancedViewArrow() const override;`
- L44 _private prototype_ `EVisibility CodeVisibility() const;`
- L45 _private prototype_ `EVisibility PixelDiscardVisibility() const;`
- L49 _protected member_ `TSharedPtr<FHLSLSyntaxHighlighterMarshaller> SyntaxHighlighter;` — Shader text box
- L50 _protected member_ `TSharedPtr<SMultiLineEditableTextBox> ShaderTextBox;`
- L51 _protected member_ `TWeakObjectPtr<UMaterialExpressionCustom> WeakCustomExpression;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditor/MaterialNodes/SGraphNodeMaterialOperator.h` (Public)


#### class `SMaterialExpressionOperatorGraphPin`  
`class SMaterialExpressionOperatorGraphPin : public SGraphPin`  
_L15-33_
- inherits: `SGraphPin`
- desc: Custom SGraphPin for handling array of inputs
- L18 _public function_ `SLATE_BEGIN_ARGS(SMaterialExpressionOperatorGraphPin)`
- L19 _public prototype_ `SLATE_ARGUMENT(int32, ArrayIndex) SLATE_ARGUMENT(UMaterialExpressionOperator*, OperatorExpression) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L27 _protected prototype_ `TOptional<NumericType> GetNumericValue() const;`
- L28 _protected prototype_ `void SetNumericValue(NumericType NewValue, ETextCommit::Type CommitInfo);`
- L31 _private member_ `int32 ArrayIndex;`
- L32 _private member_ `UMaterialExpressionOperator* OperatorExpression;`

#### class `SGraphNodeMaterialOperator`  
`class SGraphNodeMaterialOperator : public SGraphNodeMaterialBase`  
_L36-72_
- inherits: `SGraphNodeMaterialBase`
- L39 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMaterialOperator)`
- L40 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UMaterialGraphNode* InNode);`
- L46 _protected prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;` — SGraphNode interface
- L47 _protected prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* InPin) const override;`
- L48 _protected prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;`
- L53 _private prototype_ `UMaterialExpressionOperator* GetMaterialExpression() const;` — Get the Material Expression
- L56 _private prototype_ `FReply OnAddPinClicked();` — Event for adding a pin
- L59 _private member_ `TWeakPtr<SButton> OperatorButton;` — Button on Operator Graph Node for Operator Selection Menu
- L62 _private prototype_ `FReply OnOperatorMenuClicked();` — Event for Operator Selection Menu
- L65 _private prototype_ `TSharedRef<SWidget> BuildOperatorMenu();` — Create Operator Selection Menu
- L68 _private prototype_ `void OnOperatorMenuSelected(EMaterialExpressionOperatorKind NewKind);` — Event for selecting operator
- L71 _private prototype_ `FText GetOperatorDisplayName() const;` — Get Operator Display Name

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditor/MaterialNodes/SGraphNodeMaterialResult.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNodeMaterialResult>`  
_L16-19_
- L18 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeMaterialResult`  
`class SGraphNodeMaterialResult : public SGraphNode`  
_L21-40_
- inherits: `SGraphNode`
- L24 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMaterialResult)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UMaterialGraphNode_Root* InNode);`
- L30 _public prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface
- L31 _public prototype_ `virtual void PopulateMetaTag(FGraphNodeMetaData* TagMeta) const override;`
- L35 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;` — SNodePanel::SNode interface
- L39 _private member_ `UMaterialGraphNode_Root* RootNode;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditor/MaterialPins/SGraphPinMaterialInput.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinMaterialInput>`  
_L15-18_
- L17 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinMaterialInput`  
`class SGraphPinMaterialInput : public SGraphPin`  
_L20-33_
- inherits: `SGraphPin`
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphPinMaterialInput)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L30 _protected prototype_ `virtual FSlateColor GetPinColor() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditor/SGraphSubstrateMaterial.h` (Public)


#### struct `FSubstrateWidget`  
`struct FSubstrateWidget`  
_L14-22_
- L16 _public prototype_ `static const TSharedRef<SWidget> ProcessOperator(const FSubstrateMaterialCompilationOutput& CompilationOutput);`
- L17 _public prototype_ `static const TSharedRef<SWidget> ProcessOperator(const FSubstrateMaterialCompilationOutput& CompilationOutput, const TArray<FGuid>& InGuid);`
- L18 _public prototype_ `static void GetPinColor(TSharedPtr<SGraphPin>& Out, const UMaterialGraphNode* InNode);`
- L19 _public prototype_ `static FLinearColor GetConnectionColor();`
- L20 _public prototype_ `static bool HasInputSubstrateType(const UEdGraphPin* InPin);`
- L21 _public prototype_ `static bool HasOutputSubstrateType(const UEdGraphPin* InPin);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditorActions.h` (Public)


#### class `FMaterialEditorCommands`  
`class FMaterialEditorCommands : public TCommands<FMaterialEditorCommands>`  
_L30-246_
- inherits: `TCommands<FMaterialEditorCommands>`
- desc: Unreal material editor actions
- L34 _public function_ `FMaterialEditorCommands() : TCommands<FMaterialEditorCommands> ( "MaterialEditor",`
- L48 _public member_ `TSharedPtr< FUICommandInfo > Apply;` — Applys the following material to the world
- L51 _public member_ `TSharedPtr< FUICommandInfo > Flatten;` — Flattens the material to a texture for mobile devices
- L58 _public member_ `TSharedPtr< FUICommandInfo > ShowAllMaterialParameters;` — Toggles between showing all the material parameters or not
- L65 _public member_ `TSharedPtr< FUICommandInfo > SetCylinderPreview;` — Sets the preview mesh to a cylinder
- L68 _public member_ `TSharedPtr< FUICommandInfo > SetSpherePreview;` — Sets the preview mesh to a sphere
- L71 _public member_ `TSharedPtr< FUICommandInfo > SetPlanePreview;` — Sets the preview mesh to a plane
- L74 _public member_ `TSharedPtr< FUICommandInfo > SetCubePreview;` — Sets the preview mesh to a cube
- L77 _public member_ `TSharedPtr< FUICommandInfo > SetShaderBallPreview;` — Sets the preview mesh to a shader ball
- L80 _public member_ `TSharedPtr< FUICommandInfo > SetPreviewMeshFromSelection;` — Sets the preview mesh to the current selection in the level editor
- L83 _public member_ `TSharedPtr< FUICommandInfo > SelectPreviewMeshMaterialSlots;` — Set the material slots of the PreviewMesh to apply this material to
- L86 _public member_ `TSharedPtr< FUICommandInfo > TogglePreviewBackground;` — Toggles the preview pane's background
- L94 _public member_ `TSharedPtr< FUICommandInfo > CameraHome;` — Moves the canvas camera to the home position
- L97 _public member_ `TSharedPtr< FUICommandInfo > CleanUnusedExpressions;` — Removes any unused nodes
- L100 _public member_ `TSharedPtr<FUICommandInfo> FixupMismatchedSamplers;` — Fixes up broken sampler nodes
- L103 _public member_ `TSharedPtr< FUICommandInfo > ShowHideConnectors;` — Shows or hides unused connectors
- L106 _public member_ `TSharedPtr< FUICommandInfo > ToggleLivePreview;` — Toggles live updating of the preview material.
- L109 _public member_ `TSharedPtr< FUICommandInfo > ToggleHideUnrelatedNodes;` — Fade nodes which are not connected to the selected nodes.
- L112 _public member_ `TSharedPtr< FUICommandInfo > ToggleRealtimeExpressions;` — Toggles real time expression nodes
- L115 _public member_ `TSharedPtr< FUICommandInfo > AlwaysRefreshAllPreviews;` — Always refresh all previews when enabled
- L118 _public member_ `TSharedPtr< FUICommandInfo > ToggleMaterialStats;` — Toggles the material stats on the canvas pane
- L121 _public member_ `TSharedPtr< FUICommandInfo > TogglePlatformStats;` — Shows material stats and errors for multiple shader platforms.
- L124 _public member_ `TSharedPtr< FUICommandInfo > NewComment;` — Creates a new comment node
- L127 _public member_ `TSharedPtr< FUICommandInfo > UseCurrentTexture;` — Uses the texture in the content browser for the selected node
- L130 _public member_ `TSharedPtr< FUICommandInfo > MatertialPasteHere;` — Pastes the copied items at the current location
- L133 _public member_ `TSharedPtr< FUICommandInfo > ConvertObjects;` — Converts selected objects to parameters
- L136 _public member_ `TSharedPtr< FUICommandInfo > PromoteToDouble;` — Convert the selected parameters from 'float' to 'double'
- L139 _public member_ `TSharedPtr< FUICommandInfo > PromoteToFloat;` — Convert the selected parameters from 'double' to 'float'
- L142 _public member_ `TSharedPtr< FUICommandInfo > ConvertToTextureObjects;` — Converts selected texture type into another
- L143 _public member_ `TSharedPtr< FUICommandInfo > ConvertToTextureSamples;`
- L146 _public member_ `TSharedPtr< FUICommandInfo > ConvertToConstant;` — Converts selected objects to constants
- L149 _public member_ `TSharedPtr< FUICommandInfo > SelectNamedRerouteDeclaration;` — Local variables select helpers
- L150 _public member_ `TSharedPtr< FUICommandInfo > SelectNamedRerouteUsages;`
- L151 _public member_ `TSharedPtr<FUICommandInfo> CreateRerouteUsageFromDeclaration;`
- L154 _public member_ `TSharedPtr< FUICommandInfo > ConvertRerouteToNamedReroute;` — Conversion between reroute nodes and local variables
- L155 _public member_ `TSharedPtr< FUICommandInfo > ConvertNamedRerouteToReroute;`
- L158 _public member_ `TSharedPtr< FUICommandInfo > StopPreviewNode;` — Stops a node from being previewed in the viewport
- L161 _public member_ `TSharedPtr< FUICommandInfo > StartPreviewNode;` — Makes the selected node be previewed in the viewport
- L164 _public member_ `TSharedPtr< FUICommandInfo > PreviewHoveredNode;` — Previews the currently-hovered node
- L167 _public member_ `TSharedPtr< FUICommandInfo > EnableRealtimePreviewNode;` — Enables realtime previewing of this node
- L170 _public member_ `TSharedPtr< FUICommandInfo > DisableRealtimePreviewNode;` — Disables realtime previewing of this node
- L173 _public member_ `TSharedPtr< FUICommandInfo > BreakAllLinks;` — Breaks all outgoing links on the selected node
- L176 _public member_ `TSharedPtr< FUICommandInfo > DuplicateObjects;` — Duplicates all selected objects
- L179 _public member_ `TSharedPtr< FUICommandInfo > DeleteObjects;` — Deletes all selected objects
- L182 _public member_ `TSharedPtr< FUICommandInfo > SelectDownstreamNodes;` — Selects all nodes that use the selected node's outgoing links
- L185 _public member_ `TSharedPtr< FUICommandInfo > SelectUpstreamNodes;` — Selects all nodes that use the selected node's incoming links
- L188 _public member_ `TSharedPtr< FUICommandInfo > RemoveFromFavorites;` — Removes the selected expression from your favorites
- L191 _public member_ `TSharedPtr< FUICommandInfo > AddToFavorites;` — Adds the selected expression to your favorites
- L194 _public member_ `TSharedPtr< FUICommandInfo > BreakLink;` — Deletes the selected link
- L197 _public member_ `TSharedPtr< FUICommandInfo > ForceRefreshPreviews;` — Forces a refresh of all previews
- L200 _public member_ `TSharedPtr< FUICommandInfo > FindInMaterial;` — Finds expressions in current material
- L203 _public member_ `TSharedPtr< FUICommandInfo > CreateComponentMaskNode;` — Create component mask node
- L206 _public member_ `TSharedPtr< FUICommandInfo > PromoteToParameter;` — Promote pin to parameter
- L209 _public member_ `TSharedPtr< FUICommandInfo > ResetToDefault;` — Reset pin to default value
- L212 _public member_ `TSharedPtr< FUICommandInfo > DeletePin;` — Delete Pin
- L215 _public member_ `TSharedPtr< FUICommandInfo > CreateSlabNode;` — Create slab node
- L218 _public member_ `TSharedPtr< FUICommandInfo > CreateHorizontalMixNode;` — Create horizontal mix node
- L221 _public member_ `TSharedPtr< FUICommandInfo > CreateVerticalLayerNode;` — Create vertical layer node
- L224 _public member_ `TSharedPtr< FUICommandInfo > CreateWeightNode;` — Create weight node
- L227 _public member_ `TSharedPtr< FUICommandInfo > CreateSelectNode;` — Create select node
- L229 _public member_ `TSharedPtr< FUICommandInfo > QualityLevel_All;`
- L230 _public member_ `TSharedPtr< FUICommandInfo > QualityLevel_Epic;`
- L231 _public member_ `TSharedPtr< FUICommandInfo > QualityLevel_High;`
- L232 _public member_ `TSharedPtr< FUICommandInfo > QualityLevel_Medium;`
- L233 _public member_ `TSharedPtr< FUICommandInfo > QualityLevel_Low;`
- L235 _public member_ `TSharedPtr< FUICommandInfo > FeatureLevel_All;`
- L236 _public member_ `TSharedPtr< FUICommandInfo > FeatureLevel_Mobile;`
- L237 _public member_ `TSharedPtr< FUICommandInfo > FeatureLevel_SM5;`
- L238 _public member_ `TSharedPtr< FUICommandInfo > FeatureLevel_SM6;`
- L243 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `FExpressionSpawnInfo`  
`class FExpressionSpawnInfo`  
_L251-274_
- L255 _public function_ `FExpressionSpawnInfo(UClass* InMaterialExpressionClass) : MaterialExpressionClass(InMaterialExpressionClass)` — Constructor
- L258 _public member_ `TSharedPtr< FUICommandInfo > CommandInfo;` — Holds the UI Command to verify chords for this action are held
- L267 _public prototype_ `TSharedPtr< FEdGraphSchemaAction > GetAction(UEdGraph* InDestGraph);` — Creates an action to be used for placing a node into the graph @param	InDestGraph		The graph the action should be created for @return					A fully prepared action containing the information to spawn the node
- L269 _public function_ `UClass* GetClass()`
- L273 _private member_ `UClass* MaterialExpressionClass;` — Type of expression to spawn

#### class `FMaterialEditorSpawnNodeCommands`  
`class FMaterialEditorSpawnNodeCommands : public TCommands<FMaterialEditorSpawnNodeCommands>`  
_L280-305_
- inherits: `TCommands<FMaterialEditorSpawnNodeCommands>`
- desc: Handles spawn node commands for the Material Editor
- L284 _public function_ `FMaterialEditorSpawnNodeCommands() : TCommands<FMaterialEditorSpawnNodeCommands>( TEXT("MaterialEditorSpawnNodes"), NSLOCTEXT("Contexts", "MaterialEditor_SpawnNodes", "Material Editor - Spawn Nodes"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Constructor
- L290 _public prototype_ `virtual void RegisterCommands() override;` — TCommands interface
- L298 _public prototype_ `TSharedPtr< FEdGraphSchemaAction > GetGraphActionByChord(FInputChord& InChord, UEdGraph* InDestGraph) const;` — Returns a graph action assigned to the passed in chord @param InChord		The chord to use for lookup @param InDestGraph	The graph to create the graph action for, used for validation purposes and to link any important node data to the graph
- L300 _public prototype_ `const TSharedPtr<const FInputChord> GetChordByClass(UClass* MaterialExpressionClass) const;`
- L304 _private member_ `TArray< TSharedPtr< class FExpressionSpawnInfo > > NodeCommands;` — An array of all the possible commands for spawning nodes

### `Source/Editor/MaterialEditor/Public/MaterialEditorContext.h` (Public)


#### class `UMaterialEditorMenuContext`  
`class UMaterialEditorMenuContext : public UObject`  
_L12-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L18 _public member_ `TWeakPtr<IMaterialEditor> MaterialEditor;`

### `Source/Editor/MaterialEditor/Public/MaterialEditorGraphPanelPinFactory.h` (Public)


#### class `FMaterialEditorGraphPanelPinFactory`  
`class FMaterialEditorGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L9-15_
- inherits: `FGraphPanelPinFactory`
- L14 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;` — FGraphPanelPinFactory interface

### `Source/Editor/MaterialEditor/Public/MaterialEditorModes.h` (Public)


#### struct `FMaterialEditorApplicationModes`  
`struct FMaterialEditorApplicationModes`  
_L12-33_
- L15 _public member_ `static const FName StandardMaterialEditorMode;` — Mode identifiers
- L16 _public function_ `static FText GetLocalizedMode(const FName InMode)`
- L30 _public prototype_ `static TSharedPtr<FTabManager::FLayout> GetDefaultEditorLayout(TSharedPtr<class FMaterialEditor> InMaterialEditor);`
- L32 _private function_ `FMaterialEditorApplicationModes()`

#### class `FMaterialEditorApplicationMode`  
`class FMaterialEditorApplicationMode : public FApplicationMode`  
_L36-49_
- inherits: `FApplicationMode`
- desc: Even though we currently only have one mode of operation, we still need a application mode to handle factory tab spawning
- L39 _public prototype_ `FMaterialEditorApplicationMode(TSharedPtr<class FMaterialEditor> InMaterialEditor);`
- L41 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L45 _protected member_ `TWeakPtr<FMaterialEditor> MyMaterialEditor;`
- L48 _protected member_ `FWorkflowAllowedTabSet MaterialEditorTabFactories;` — Set of spawnable tabs handled by workflow factories

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditorModule.h` (Public)


#### class `IMaterialEditorModule`  
`class IMaterialEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L26-85_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Material editor module interface
- L33 _public prototype_ `virtual TSharedRef<IMaterialEditor> CreateMaterialEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterial* Material ) = 0;` — Creates a new material editor, either for a material or a material function
- L34 _public prototype_ `virtual TSharedRef<IMaterialEditor> CreateMaterialEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterialFunction* MaterialFunction ) = 0;`
- L35 _public prototype_ `virtual TSharedRef<IMaterialEditor> CreateMaterialInstanceEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterialInstance* MaterialInstance ) = 0;`
- L36 _public prototype_ `virtual TSharedRef<IMaterialEditor> CreateMaterialInstanceEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterialFunctionInstance* MaterialFunction ) = 0;`
- L45 _public prototype_ `virtual void GetVisibleMaterialParameters(const class UMaterial* Material, class UMaterialInstance* MaterialInstance, TArray<FMaterialParameterInfo>& VisibleExpressions) = 0;` — Retrieves all visible parameters within the material. @param	Material			The material to retrieve the parameters from. @param	MaterialInstance	The material instance that contains all parameter overrides. @param	VisibleExpressions	The array that will contain the name's of the visible parameter expressions.
- L48 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FMaterialMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the material menus
- L49 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FMaterialMenuExtender_MaterialInterface, const UMaterialInterface*);`
- L50 _public function_ `virtual TArray<FMaterialMenuExtender>& GetAllMaterialCanvasMenuExtenders()`
- L51 _public function_ `virtual TArray<FMaterialMenuExtender_MaterialInterface>& GetAllMaterialDragDropContextMenuExtenders()`
- L54 _public prototype_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FMaterialEditorOpenedEvent, TWeakPtr<IMaterialEditor>);` — Delegate to be called when a Material Editor is created, for toolbar, tab, and menu extension
- L55 _public function_ `virtual FMaterialEditorOpenedEvent& OnMaterialEditorOpened()`
- L58 _public prototype_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FMaterialFunctionEditorOpenedEvent, TWeakPtr<IMaterialEditor>);` — Delegate to be called when a Material Function Editor is created, for toolbar, tab, and menu extension
- L59 _public function_ `virtual FMaterialFunctionEditorOpenedEvent& OnMaterialFunctionEditorOpened()`
- L62 _public prototype_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FMaterialInstanceEditorOpenedEvent, TWeakPtr<IMaterialEditor>);` — Delegate to be called when a Material Instance Editor is created, for toolbar, tab, and menu extension
- L63 _public function_ `virtual FMaterialInstanceEditorOpenedEvent& OnMaterialInstanceEditorOpened()`
- L71 _public function_ `static inline IMaterialEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L79 _private member_ `TArray<FMaterialMenuExtender> MaterialCanvasMenuExtenders;` — All extender delegates for the material menus
- L80 _private member_ `TArray<FMaterialMenuExtender_MaterialInterface> MaterialInheritanceMenuExtenders;`
- L82 _private member_ `FMaterialEditorOpenedEvent MaterialEditorOpenedEvent;`
- L83 _private member_ `FMaterialFunctionEditorOpenedEvent MaterialFunctionEditorOpenedEvent;`
- L84 _private member_ `FMaterialInstanceEditorOpenedEvent MaterialInstanceEditorOpenedEvent;`

#### Free symbols / members of external scopes

- L20 _externvar_ `extern const FName MaterialEditorAppIdentifier;`
- L21 _externvar_ `extern const FName MaterialInstanceEditorAppIdentifier;`
- L48 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FMaterialMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the material menus
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FMaterialMenuExtender_MaterialInterface, const UMaterialInterface*);`
- L54 _delegate_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FMaterialEditorOpenedEvent, TWeakPtr<IMaterialEditor>);` — Delegate to be called when a Material Editor is created, for toolbar, tab, and menu extension
- L58 _delegate_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FMaterialFunctionEditorOpenedEvent, TWeakPtr<IMaterialEditor>);` — Delegate to be called when a Material Function Editor is created, for toolbar, tab, and menu extension
- L62 _delegate_ `DECLARE_EVENT_OneParam(IMaterialEditorModule, FMaterialInstanceEditorOpenedEvent, TWeakPtr<IMaterialEditor>);` — Delegate to be called when a Material Instance Editor is created, for toolbar, tab, and menu extension

### `Source/Editor/MaterialEditor/Public/MaterialEditorSettings.h` (Public)


#### enum `EOfflineShaderCompiler`  
`enum class EOfflineShaderCompiler : uint8`  
_L12-16_
- reflection: `UENUM()`
- desc: Enumerates offline shader compiler for the material editor
- L14 _public enumerator_ `Mali UMETA(DisplayName = "Mali Offline Compiler")`
- L15 _public enumerator_ `Adreno UMETA(DisplayName = "Adreno Offline Compiler")`

#### enum `EBackgroundType`  
`enum class EBackgroundType : uint8`  
_L22-26_
- reflection: `UENUM()`
- desc: Enumerates background for the material editor UI viewport (similar to ETextureEditorBackgrounds)
- L24 _public enumerator_ `SolidColor UMETA(DisplayName = "Solid Color")`
- L25 _public enumerator_ `Checkered UMETA(DisplayName = "Checkered")`

#### struct `FCheckerboardSettings`  
`struct FCheckerboardSettings`  
_L29-52_
- reflection: `USTRUCT()`
- L35 _public member_ `FColor ColorOne;` — `UPROPERTY(EditAnywhere, Category = "Checkerboard")` — The first color of the checkerboard.
- L39 _public member_ `FColor ColorTwo;` — `UPROPERTY(EditAnywhere, Category = "Checkerboard")` — The second color of the checkerboard
- L43 _public member_ `int32 Size;` — `UPROPERTY(EditAnywhere, meta = (ClampMin = "2", ClampMax = "4096"), Category = "Checkerboard")` — The size of the checkered tiles
- L45 _public function_ `FCheckerboardSettings() : ColorOne(FColor(128, 128, 128)) , ColorTwo(FColor(64, 64, 64)) , Size(32)`

#### struct `FPreviewBackgroundSettings`  
`struct FPreviewBackgroundSettings`  
_L67-100_
- reflection: `USTRUCT()`
- L73 _public member_ `bool bShowBorder;` — `UPROPERTY()` — If true, displays a border around the texture (configured via the material editor)
- L77 _public member_ `FColor BorderColor;` — `UPROPERTY(EditAnywhere, Category = "Background")` — Color to use for the border, if enabled
- L81 _public member_ `EBackgroundType BackgroundType;` — `UPROPERTY()` — The type of background to show (configured via the material editor)
- L85 _public member_ `FColor BackgroundColor;` — `UPROPERTY(EditAnywhere, Category = "Background")` — The color used as the background of the preview
- L88 _public member_ `FCheckerboardSettings Checkerboard;` — `UPROPERTY(EditAnywhere, Category = "Background")`
- L91 _public function_ `FPreviewBackgroundSettings() : bShowBorder(false) , BorderColor(FColor::White) , BackgroundType(EBackgroundType::SolidColor) , BackgroundColor(FColor::Black)` — Note: For now these defaults match the historical material editor behavior, not the texture editor's defaults

#### class `UMaterialEditorSettings`  
`class UMaterialEditorSettings : public UObject`  
_L103-219_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L111 _public member_ `FSoftObjectPath MaterialWizardConfiguration;` — `UPROPERTY(config, EditAnywhere, Category = Wizard, meta=(AllowedClasses="/Script/UserAssetTagsEditor.TaggedAssetBrowserConfiguration"))` — The configuration used in the Material Asset Wizard when creating a new Material. If not set, Content Browser uses the old factory without wizard.
- L115 _public member_ `FSoftObjectPath MaterialInstanceWizardConfiguration;` — `UPROPERTY(config, EditAnywhere, Category = Wizard, meta=(AllowedClasses="/Script/UserAssetTagsEditor.TaggedAssetBrowserConfiguration"))` — The configuration used in the Material Asset Wizard when creating a new Material Instance. If not set, Content Browser uses the old factory without wizard.
- L121 _public member_ `bool bAllowIgnoringCompilationErrors = true;` — `UPROPERTY(config, EditAnywhere, Category = "Editor Defaults", meta = (DisplayName = "Allow Ignoring Compilation Errors"))` — Allow ignoring compilation errors of platform shaders and derived materials.
- L125 _public member_ `float ContextMenuNodeTitleWeight = 25.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Node Title Weight"))` — The amount of weight placed on the search items title".
- L129 _public member_ `float ContextMenuKeywordWeight = 30.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Keyword Weight"))` — The amount of weight placed on search items keyword.
- L133 _public member_ `float ContextMenuDescriptionWeight = 4.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Menu description Weight"))` — amount of weight placed on description that match what the user has typed in.
- L137 _public member_ `float ContextMenuCategoryWeight = 4.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Category Weight"))` — The amount of weight placed on categories that match what the user has typed.
- L141 _public member_ `float ContextMenuWholeMatchLocalizedWeightMultiplier = 0.5f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Whole Match Localized Weight Multiplier"))` — The multiplier given if there is an exact localized match to the search.
- L145 _public member_ `float ContextMenuWholeMatchWeightMultiplier = 0.5f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Whole Match Weight Multiplier"))` — The multiplier given if there is an exact match to the search term.
- L149 _public member_ `float ContextMenuStartsWithBonusWeightMultiplier = 4.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Starts With Bonus Weight Multiplier"))` — The multiplier given if the keyword starts with a term the user typed in.
- L153 _public member_ `float ContextMenuPercentageMatchWeightMultiplier = 1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Percentage Match Weight Multiplier"))` — A multiplier for how much weight to give something based on the percentage match it is.
- L157 _public member_ `float ContextMenuShorterMatchWeight = 10.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Context Menu", meta = (DisplayName = "Shorter Match Weight"))` — Increasing this weight will make shorter words preferred.
- L165 _public member_ `EOfflineShaderCompiler OfflineCompiler;` — `UPROPERTY(config, EditAnywhere, Category = "Offline Shader Compilers", meta = (DisplayName = "Offline Shader Compiler"))` — Offline shader compiler to use. Mali Offline Compiler: Official website address: https://developer.arm.com/products/software-development-tools/graphics-development-tools/mali-offline-compiler/downloads Adreno Offline Compiler: Official website address: https://developer.qualcomm.com/software/adreno-gpu-sdk/tools
- L171 _public member_ `FFilePath OfflineCompilerPath;` — `UPROPERTY(config, EditAnywhere, Category = "Offline Shader Compilers", meta = (DisplayName = "Offline Compiler Path"))` — Path to user installed shader compiler that can be used by the material editor to compile and extract shader informations for Android platforms.
- L177 _public member_ `FString GPUTarget;` — `UPROPERTY(config, EditAnywhere, Category = "Offline Shader Compilers", meta = (DisplayName = "GPU Target", EditCondition = "OfflineCompiler == EOfflineShaderCompiler::Adreno"))` — The GPU target if the offline shader compiler needs one (Adreno GPU only).
- L183 _public member_ `bool bSaveCompilerStatsFiles = false;` — `UPROPERTY(config, EditAnywhere, Category = "Offline Shader Compilers", meta = (DisplayName = "Save Compiler Stats Files", EditCondition = "OfflineCompiler == EOfflineShaderCompiler::Adreno"))` — Whether to save offline compiler stats files to Engine\Shaders
- L189 _public member_ `bool bDumpAll;` — `UPROPERTY(config, EditAnywhere, Category = "Offline Shader Compilers", meta = (DisplayName = "Dump All Stats To Compiler Stats Files", EditCondition = "OfflineCompiler == EOfflineShaderCompiler::Adreno"))` — Whether to dump stats only or all information to file (Adreno GPU only).
- L194 _protected member_ `int32 DefaultPreviewWidth = 250;` — `UPROPERTY(config, EditAnywhere, meta=(ClampMin=1, ClampMax=4096), Category="User Interface Domain")` — The width (in pixels) of the preview viewport when a material editor is first opened
- L198 _protected member_ `int32 DefaultPreviewHeight = 250;` — `UPROPERTY(config, EditAnywhere, meta=(ClampMin=1, ClampMax=4096), Category="User Interface Domain")` — The height (in pixels) of the preview viewport when a material editor is first opened
- L203 _public member_ `FPreviewBackgroundSettings PreviewBackground;` — `UPROPERTY(config, EditAnywhere, Category = "User Interface Domain")` — Configures the background shown behind the UI material preview
- L205 _public function_ `FIntPoint GetPreviewViewportStartingSize() const`
- L212 _public member_ `FSimpleMulticastDelegate OnPostEditChange;` — Allow listening for changes just to this settings object without having to listen to all UObjects
- L213 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override`

#### Free symbols / members of external scopes

- L54 _function_ `inline bool operator==(const FCheckerboardSettings& Lhs, const FCheckerboardSettings& Rhs)`
- L61 _function_ `inline bool operator!=(const FCheckerboardSettings& Lhs, const FCheckerboardSettings& Rhs)`

### `Source/Editor/MaterialEditor/Public/MaterialEditorUtilities.h` (Public)


#### class `FGetVisibleMaterialParametersFunctionState`  
`class FGetVisibleMaterialParametersFunctionState`  
_L27-44_
- L31 _public function_ `FGetVisibleMaterialParametersFunctionState(UMaterialExpressionMaterialFunctionCall* InFunctionCall) : FunctionCall(InFunctionCall)`
- L40 _public member_ `class UMaterialExpressionMaterialFunctionCall* FunctionCall;`
- L41 _public member_ `TArray<FMaterialExpressionKey> ExpressionStack;`
- L42 _public member_ `TSet<FMaterialExpressionKey> VisitedExpressions;`
- L43 _public member_ `FMaterialParameterInfo StackParameterInfo;`

#### class `FMaterialEditorUtilities`  
`class FMaterialEditorUtilities`  
_L46-319_
- L58 _public prototype_ `static UMaterialExpression* CreateNewMaterialExpression(const class UEdGraph* Graph, UClass* NewExpressionClass, const UE::Slate::FDeprecateVector2DParameter& NodePos, bool bAutoSelect, bool bAutoAssignResource);` — Creates a new material expression of the specified class on the material represented by a graph. @param	Graph				Graph representing a material. @param	NewExpressionClass	The type of material expression to add.  Must be a child of UMaterialExpression. @param	NodePos				Position of the new node. @param	bAutoSelect			If true, deselect all expressions and select the newly created one. @param	bAutoAssignResource	If true, assign resources to new expression.
- L69 _public function_ `template<typename MaterialExpressionClass> static MaterialExpressionClass* CreateNewMaterialExpression(const UEdGraph* Graph, const UE::Slate::FDeprecateVector2DParameter& NodePos, bool bAutoSelect, bool bAutoAssignResource = false)` — Creates a new material expression of the specified class on the material represented by a graph. @param	Graph					Graph representing a material. @param	NodePos					Position of the new node. @param	bAutoSelect				If true, deselect all expressions and select the newly created one. @param	bAutoAssignResource		If true, assign resources to new expression.
- L83 _public prototype_ `static UMaterialExpressionComposite* CreateNewMaterialExpressionComposite(const class UEdGraph* Graph, const FVector2D& NodePos);` — Creates a new material expression composite on the material represented by a graph. @param	Graph	Graph to add comment to @param	NodePos	Position to place new comment at @return	UMaterialExpressionComment*	Newly created comment
- L93 _public prototype_ `static UMaterialExpressionComment* CreateNewMaterialExpressionComment(const class UEdGraph* Graph, const FVector2D& NodePos);` — Creates a new material expression comment on the material represented by a graph. @param	Graph	Graph to add comment to @param	NodePos	Position to place new comment at @return	UMaterialExpressionComment*	Newly created comment
- L100 _public prototype_ `static void ForceRefreshExpressionPreviews(const class UEdGraph* Graph);` — Refreshes all material expression previews, regardless of whether or not realtime previews are enabled. @param	Graph	Graph representing a material.
- L108 _public prototype_ `static void AddToSelection(const class UEdGraph* Graph, UMaterialExpression* Expression);` — Add the specified object to the list of selected objects @param	Graph	Graph representing a material. @param	Obj		Object to add to selection.
- L115 _public prototype_ `static void DeleteSelectedNodes(const class UEdGraph* Graph);` — Disconnects and removes the selected material graph nodes. @param	Graph	Graph representing a material.
- L122 _public prototype_ `static void DeleteNodes(const class UEdGraph* Graph, const TArray<UEdGraphNode*>& NodesToDelete);` — Delete the specified nodes from the graph. @param Graph Graph representing the material. @param NodesToDelete Array of nodes to be removed from the graph.
- L130 _public prototype_ `static FText GetOriginalObjectName(const class UEdGraph* Graph);` — Gets the name of the material or material function that we are editing @param	Graph	Graph representing a material or material function.
- L137 _public prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeMaterialAssetReferenceFilter(const class UEdGraph* Graph);` — Creates an IAssetReferenceFilter that can be used to check if an asset is valid to be used with this material. @param	Graph	Graph representing a material or material function.
- L144 _public prototype_ `static void UpdateMaterialAfterGraphChange(const class UEdGraph* Graph);` — Re-links the material and updates its representation in the editor @param	Graph	Graph representing a material or material function.
- L147 _public prototype_ `static void MarkMaterialDirty(const class UEdGraph* Graph);` — Mark the material as dirty.
- L149 _public prototype_ `static void UpdateDetailView(const class UEdGraph* Graph);`
- L152 _public prototype_ `static bool CanPasteNodes(const class UEdGraph* Graph);` — Can we paste to this graph?
- L155 _public prototype_ `static void PasteNodesHere(class UEdGraph* Graph, const FVector2D& Location);` — Perform paste on graph, at location
- L158 _public prototype_ `static int32 GetNumberOfSelectedNodes(const class UEdGraph* Graph);` — Gets the number of selected nodes on this graph
- L167 _public prototype_ `static void GetMaterialExpressionActions(FGraphActionMenuBuilder& ActionMenuBuilder, bool bMaterialFunction);` — `UE_DEPRECATED(5.8, "Should call version that provides a UMaterial or UMaterialFunction")` — Get all actions for placing material expressions @param [in,out]	ActionMenuBuilder	The output menu builder. @param bMaterialFunction				Whether we're dealing with a Material Function
- L175 _public prototype_ `static void GetMaterialExpressionActions(FGraphActionMenuBuilder& ActionMenuBuilder, const UObject* MaterialOrFunction);` — Get all actions for placing material expressions @param [in,out]	ActionMenuBuilder	The output menu builder. @param MaterialOrFunction			A UMaterial or UMaterialFunction object
- L182 _public prototype_ `static bool IsMaterialExpressionInFavorites(UMaterialExpression* InExpression);` — Check whether an expression is in the favourites list @param	InExpression	The Expression we are checking
- L192 _public prototype_ `static FMaterialRenderProxy* GetExpressionPreview(const class UEdGraph* Graph, UMaterialExpression* InExpression);` — Get a preview material render proxy for an expression @param	Graph			Graph representing material @param	InExpression	Expression we want preview for @return	FMaterialRenderProxy*	Preview for this expression or NULL
- L199 _public prototype_ `static void UpdateSearchResults(const class UEdGraph* Graph);` — Updates the material editor search results @param	Graph			Graph representing material
- L211 _public prototype_ `static void GetVisibleMaterialParameters(const UMaterial *Material, UMaterialInstance *MaterialInstance, TArray<FMaterialParameterInfo> &VisibleExpressions);` — Retrieves all visible parameters within the material. @param	Material			The material to retrieve the parameters from. @param	MaterialInstance	The material instance that contains all parameter overrides. @param	VisisbleExpressions	The array that will contain the name's of the visible parameter expressions.
- L214 _public prototype_ `static const FFunctionExpressionInput* FindInputById(const UMaterialExpressionFunctionInput* InputExpression, const TArray<FFunctionExpressionInput>& Inputs);` — Finds an input in the passed in array with a matching Id.
- L227 _public prototype_ `static bool GetStaticSwitchExpressionValue(UMaterialInstance* MaterialInstance, UMaterialExpression *SwitchValueExpression, bool& OutValue, FGuid& OutExpressionID, TArray<FGetVisibleMaterialParametersFunctionState*>& FunctionStack);` — Returns the value for a static switch material expression. @param	MaterialInstance		The material instance that contains all parameter overrides. @param	SwitchValueExpression	The switch expression to find the value for. @param	OutValue				The value for the switch expression. @param	OutExpressionID			The Guid of the expression that is input as the switch value. @param	FunctionStack			The current function stack frame. @return	Returns true if a value for the switch expression is found, otherwise returns false.
- L235 _public prototype_ `static void InitExpressions(UMaterial* Material);` — Populates the specified material's Expressions array (eg if cooked out or old content). Also ensures materials and expressions are RF_Transactional for undo/redo support. @param	Material	Material we are initializing
- L242 _public prototype_ `static void BuildTextureStreamingData(UMaterialInterface* MaterialInterface);` — Build the texture streaming data for a given material. Also update the parent hierarchy has only the delta are stored. @param	MaterialInterface	The material to update.
- L245 _public prototype_ `static TSharedPtr<class IMaterialEditor> GetIMaterialEditorForObject(const UObject* ObjectToFocusOn);` — Get IMaterialEditor for given object, if it exists
- L248 _public prototype_ `static void BringFocusAttentionOnObject(const UObject* ObjectToFocusOn);` — Get IMaterialEditor to focus on given object, if it exists
- L252 _public prototype_ `static void OnOpenMaterial(const FAssetData InMaterial);` — Commands for the Parents menu
- L253 _public prototype_ `static void OnOpenFunction(const FAssetData InFunction);`
- L254 _public prototype_ `static void OnShowMaterialInContentBrowser(const FAssetData InMaterial);`
- L255 _public prototype_ `static void OnShowFunctionInContentBrowser(const FAssetData InFunction);`
- L262 _public prototype_ `static void RefreshPostProcessPreviewMaterials(UMaterialInterface* ExcludeMaterialInterface, bool bRedrawOnly = false);` — Triggers a refresh or redraw for post process preview materials and material instances.  A refresh is useful when a material generating a UserSceneTexture output is loaded or unloaded.  Other loaded materials that have UserSceneTexture inputs may include the material in question in their preview, which necessitates a refresh.  A redraw is useful when debug settings change that may affect post process material viewports.
- L266 _private prototype_ `static void OpenSelectedParentEditor(UMaterialFunctionInterface* InMaterialFunction);`
- L267 _private prototype_ `static void OpenSelectedParentEditor(UMaterialInterface* InMaterialInterface);`
- L276 _private prototype_ `static void GetVisibleMaterialParametersFromExpression( FMaterialExpressionKey MaterialExpressionKey, UMaterialInstance* MaterialInstance, TArray<FMaterialParameterInfo>& VisibleExpressions, TArray<FGetVisibleMaterialParametersFunctionState*>& FunctionStack);` — Recursively walks the expression tree and parses the visible expression branches. @param	MaterialExpression				The expression to parse. @param	MaterialInstance				The material instance that contains all parameter overrides. @param	VisisbleExpressions				The array that will contain the name's of the visible parameter expressions.
- L291 _private prototype_ `static void AddMaterialExpressionCategory(FGraphActionMenuBuilder& ActionMenuBuilder, FText CategoryName, TArray<struct FMaterialExpression>* MaterialExpressions, bool bMaterialFunction);` — `UE_DEPRECATED(5.8, "Should call version that provides a UMaterial or UMaterialFunction")` — Adds a category of Material Expressions to an action builder @param	ActionMenuBuilder	The builder to add to. @param	CategoryName		The name of the category. @param	MaterialExpressions	List of Material Expressions in the category. @param	bMaterialFunction	Whether we are building for a material function.
- L301 _private prototype_ `static void AddMaterialExpressionCategory(FGraphActionMenuBuilder& ActionMenuBuilder, FText CategoryName, TArray<struct FMaterialExpression>* MaterialExpressions, const UObject* MaterialOrFunction);` — Adds a category of Material Expressions to an action builder @param	ActionMenuBuilder	The builder to add to. @param	CategoryName		The name of the category. @param	MaterialExpressions	List of Material Expressions in the category. @param	MaterialOrFunction	UMaterial or UMaterialFunction object
- L314 _public prototype_ `static bool HasCompatibleConnection(UClass* ExpressionClass, uint32 TestType, EEdGraphPinDirection TestDirection, bool bMaterialFunction);` — `UE_DEPRECATED(5.8, "Use the HasCompatibleConnection(..., EMaterialValueType, ...) overload instead")` — Checks whether a Material Expression class has any connections that are compatible with a type/direction @param	ExpressionClass		Class of Expression we are testing against. @param	TestType			Material Value Type we are testing. @param	TestDirection		Pin Direction we are testing. @param	bMaterialFunction	Whether we are testing for a material function.
- L315 _public prototype_ `static bool HasCompatibleConnection(UClass* ExpressionClass, EMaterialValueType TestType, EEdGraphPinDirection TestDirection, bool bMaterialFunction);`
- L318 _public function_ `FMaterialEditorUtilities()` — Constructor

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialEditorValidation.h` (Public)


#### struct `FMaterialEditorValidatorContext`  
`struct FMaterialEditorValidatorContext`  
_L13-18_
- desc: Context for validators to use/fill during Validate() call.
- L15 _public member_ `FText Message;`
- L16 _public member_ `FText HyperlinkText;`
- L17 _public member_ `FSimpleDelegate HyperlinkAction;`

#### class `UMaterialEditorValidatorBase`  
`class UMaterialEditorValidatorBase : public UObject`  
_L22-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base interface for validators that can be registered with the UMaterialEditorValidationSubsystem.
- L28 _public function_ `virtual bool Validate(UMaterialInterface* InMaterial, FMaterialEditorValidatorContext& InContext) const` — Return false if there are validation errors, and output any validation meesage in InContext.

#### class `UMaterialEditorValidationSubsystem`  
`class UMaterialEditorValidationSubsystem : public UEditorSubsystem`  
_L33-50_
- reflection: `UCLASS(MinimalAPI, Config = Editor)`
- inherits: `UEditorSubsystem`
- desc: Editor subsystem for registering and running material validators in the material editor tools.
- L39 _public prototype_ `void AddValidator(UMaterialEditorValidatorBase* InValidator);` — Register a validator. Added validators will be called on Validate().
- L41 _public prototype_ `void RemoveValidator(UMaterialEditorValidatorBase* InValidator);` — Unregister a validator.
- L44 _public prototype_ `bool Validate(UMaterialInterface* InMaterial, FMaterialEditorValidatorContext& InContext) const;` — Call Validate() on all registered validators.
- L49 _private member_ `TArray<TObjectPtr<UMaterialEditorValidatorBase>> Validators;` — `UPROPERTY()` — The array of registered validators.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialNodes/SGraphNodeMaterialComment.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNodeMaterialComment>`  
_L16-19_
- L18 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeMaterialComment`  
`class SGraphNodeMaterialComment : public SGraphNodeComment`  
_L21-36_
- inherits: `SGraphNodeComment`
- L24 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMaterialComment)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UMaterialGraphNode_Comment* InNode);`
- L30 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;` — SNodePanel::SNode interface
- L35 _private member_ `UMaterialGraphNode_Comment* CommentNode;` — Cached material graph node pointer to avoid casting

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MATERIALEDITOR_API`

### `Source/Editor/MaterialEditor/Public/MaterialPropertyHelpers.h` (Public)


#### enum `EStackDataType`  
`enum EStackDataType`  
_L32-39_
- L34 _public enumerator_ `Stack`
- L35 _public enumerator_ `Asset`
- L36 _public enumerator_ `Group`
- L37 _public enumerator_ `Property`
- L38 _public enumerator_ `PropertyChild`

#### struct `FSortedParamData`  
`struct FSortedParamData`  
_L42-65_
- reflection: `USTRUCT()`
- L47 _public member_ `EStackDataType StackDataType;`
- L50 _public member_ `TObjectPtr<UDEditorParameterValue> Parameter = nullptr;` — `UPROPERTY(Transient)`
- L52 _public member_ `FName PropertyName;`
- L54 _public member_ `FEditorParameterGroup Group;`
- L56 _public member_ `FMaterialParameterInfo ParameterInfo;`
- L58 _public member_ `TSharedPtr<IDetailTreeNode> ParameterNode;`
- L60 _public member_ `TSharedPtr<IPropertyHandle> ParameterHandle;`
- L62 _public member_ `TArray<TSharedPtr<struct FSortedParamData>> Children;`
- L64 _public member_ `FString NodeKey;`

#### struct `FUnsortedParamData`  
`struct FUnsortedParamData`  
_L68-77_
- reflection: `USTRUCT()`
- L72 _public member_ `TObjectPtr<UDEditorParameterValue> Parameter = nullptr;` — `UPROPERTY(Transient)`
- L73 _public member_ `FEditorParameterGroup ParameterGroup;`
- L74 _public member_ `TSharedPtr<IDetailTreeNode> ParameterNode;`
- L75 _public member_ `FName UnsortedName;`
- L76 _public member_ `TSharedPtr<IPropertyHandle> ParameterHandle;`

#### class `IDraggableItem`  
`class IDraggableItem`  
_L82-88_
- desc: Interface for items that can be dragged and can show a layer handle
- L85 _public prototype_ `virtual void OnLayerDragEnter(const FDragDropEvent& DragDropEvent) = 0;`
- L86 _public prototype_ `virtual void OnLayerDragLeave(const FDragDropEvent& DragDropEvent) = 0;`
- L87 _public prototype_ `virtual void OnLayerDragDetected() = 0;`

#### class `SLayerHandle`  
`class SLayerHandle : public SCompoundWidget`  
_L90-112_
- inherits: `SCompoundWidget`
- L93 _public function_ `SLATE_BEGIN_ARGS(SLayerHandle)`
- L95 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<IDraggableItem>, OwningStack) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L101 _public function_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L107 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L108 _public prototype_ `TSharedPtr<class FLayerDragDropOp> CreateDragDropOperation(TSharedPtr<IDraggableItem> InOwningStack);`
- L111 _private member_ `TWeakPtr<IDraggableItem> OwningStack;`

#### class `FLayerDragDropOp`  
`class FLayerDragDropOp final : public FDecoratedDragDropOp`  
_L115-148_
- inherits: `FDecoratedDragDropOp`
- L118 _public function_ `DRAG_DROP_OPERATOR_TYPE(FLayerDragDropOp, FDecoratedDragDropOp) FLayerDragDropOp(TSharedPtr<IDraggableItem> InOwningStack)`
- L140 _public member_ `TSharedPtr<SWidget> DecoratorWidget;`
- L142 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L147 _public member_ `TWeakPtr<class IDraggableItem> OwningStack;`

#### struct `FMaterialParameterPropertyRowOverrides`  
`struct FMaterialParameterPropertyRowOverrides`  
_L151-180_
- desc: Overridable properties on material parameter property rows.
- L159 _public member_ `TAttribute<bool> EditConditionValue;` — Override the default EditConditionValue attribute. If not specified, FMaterialPropertyHelpers::IsOverriddenExpression will be used.
- L166 _public member_ `TOptional<FOnBooleanValueChanged> OnEditConditionValueChanged;` — Override the default OnEditConditionValueChanged delegate. If not specified, FMaterialPropertyHelpers::OnOverrideParameter will be used.
- L173 _public member_ `TAttribute<EVisibility> Visibility;` — Override the default Visibility attribute. If not specified, FMaterialPropertyHelpers::ShouldShowExpression will be used.
- L179 _public member_ `FGetShowHiddenParameters ShowHiddenDelegate;` — If Visibility is not overridden, this delegate will be passed as the last argument to FMaterialPropertyHelpers::ShouldShowExpression.

#### class `FMaterialPropertyHelpers`  
`class FMaterialPropertyHelpers`  
_L186-272_
- L189 _public prototype_ `static bool ShouldCreatePropertyRowForParameter(UDEditorParameterValue* Parameter);`
- L190 _public prototype_ `static bool ShouldCreateChildPropertiesForParameter(UDEditorParameterValue* Parameter);`
- L191 _public prototype_ `static void ConfigurePropertyRowForParameter(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterValueProperty, UMaterialEditorInstanceConstant* MaterialEditorInstance, const FMaterialParameterPropertyRowOverrides& RowOverrides = FMaterialParameterPropertyRowOverrides());`
- L193 _public prototype_ `static void SetPropertyRowParameterWidget(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterProperty, UMaterialEditorParameters* MaterialEditorParameters);`
- L194 _public prototype_ `static void SetPropertyRowMaskParameterWidget(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterValueProperty);`
- L195 _public prototype_ `static void SetPropertyRowVectorChannelMaskParameterWidget(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterValueProperty, UMaterialEditorParameters* MaterialEditorParameters);`
- L196 _public prototype_ `static void SetPropertyRowScalarAtlasPositionParameterWidget(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterValueProperty, UMaterialEditorParameters* MaterialEditorParameters);`
- L197 _public prototype_ `static void SetPropertyRowScalarEnumerationParameterWidget(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterValueProperty, const TSoftObjectPtr<UObject>& SoftEnumeration);`
- L198 _public prototype_ `static void SetPropertyRowTextureParameterWidget(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterValueProperty, UMaterialEditorParameters* MaterialEditorParameters);`
- L199 _public prototype_ `static void SetPropertyRowParameterCollectionParameterWidget(IDetailPropertyRow& PropertyRow, UDEditorParameterValue* Parameter, TSharedPtr<IPropertyHandle> ParameterValueProperty, class UMaterialParameterCollection* BaseParameterCollection, TArray<TSharedRef<IPropertyHandle>>&& AllPropertyHandles);`
- L202 _public prototype_ `static bool IsOverriddenExpression(UDEditorParameterValue* Parameter);` — Returns true if the parameter is being overridden
- L203 _public function_ `static bool IsOverriddenExpression(TObjectPtr<UDEditorParameterValue> Parameter)`
- L204 _public function_ `static bool IsOverriddenExpression(TWeakObjectPtr<UDEditorParameterValue> Parameter)`
- L205 _public prototype_ `static ECheckBoxState IsOverriddenExpressionCheckbox(UDEditorParameterValue* Parameter);`
- L206 _public prototype_ `static bool UsesCustomPrimitiveData(UDEditorParameterValue* Parameter);`
- L209 _public prototype_ `static FText GetParameterExpressionDescription(UDEditorParameterValue* Parameter, UObject* MaterialEditorInstance);` — Gets the expression description of this parameter from the base material
- L211 _public prototype_ `static FText GetParameterTooltip(UDEditorParameterValue* Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance);`
- L212 _public prototype_ `static FText GetParameterTooltip(UDEditorParameterValue* Parameter, UMaterial* Material);`
- L215 _public prototype_ `static FText GetParameterTooltip(UDEditorParameterValue* Parameter, UObject* MaterialEditorInstance);` — `UE_DEPRECATED(5.8, "Please use the fully typed method instead.")`
- L219 _public prototype_ `static void OnOverrideParameter(bool NewValue, UDEditorParameterValue* Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance);` — Called when a parameter is overridden;
- L221 _public prototype_ `static EVisibility ShouldShowExpression(UDEditorParameterValue* Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance, FGetShowHiddenParameters ShowHiddenDelegate);`
- L222 _public function_ `static EVisibility ShouldShowExpression(TObjectPtr<UDEditorParameterValue> Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance, FGetShowHiddenParameters ShowHiddenDelegate)`
- L225 _public prototype_ `static FResetToDefaultOverride CreateResetToDefaultOverride(UDEditorParameterValue* Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance, TSharedPtr<IPropertyHandle> ParameterValueProperty);` — Generic material property reset to default implementation.  Resets Parameter to default
- L226 _public prototype_ `static void ResetToDefault(UDEditorParameterValue* Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance, TSharedPtr<IPropertyHandle> ParameterValueProperty);`
- L227 _public prototype_ `static bool ShouldShowResetToDefault(UDEditorParameterValue* Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance);`
- L230 _public prototype_ `static void ResetLayerAssetToDefault(UDEditorParameterValue* InParameter, TEnumAsByte<EMaterialParameterAssociation> InAssociation, int32 Index, UMaterialEditorInstanceConstant* MaterialEditorInstance);` — Specific resets for layer and blend asses
- L232 _public prototype_ `static bool ShouldLayerAssetShowResetToDefault(TSharedPtr<FSortedParamData> InParameterData, UMaterialInstanceConstant* InMaterialInstance);` — If reset to default button should show for a layer or blend asset
- L233 _public function_ `static bool ShouldLayerAssetShowResetToDefault(TSharedPtr<FSortedParamData> InParameterData, TObjectPtr<UMaterialInstanceConstant> InMaterialInstance)`
- L235 _public prototype_ `static void OnMaterialLayerAssetChanged(const struct FAssetData& InAssetData, int32 Index, EMaterialParameterAssociation MaterialType, TSharedPtr<class IPropertyHandle> InHandle, FMaterialLayersFunctions* InMaterialFunction);`
- L237 _public prototype_ `static bool FilterLayerAssets(const struct FAssetData& InAssetData, FMaterialLayersFunctions* LayerFunction, EMaterialParameterAssociation MaterialType, int32 Index);`
- L239 _public prototype_ `static FReply OnClickedSaveNewMaterialInstance(class UMaterialInterface* Object, UObject* EditorObject);`
- L240 _public function_ `static FReply OnClickedSaveNewMaterialInstance(TObjectPtr<class UMaterialInterface> Object, UObject* EditorObject)`
- L242 _public prototype_ `static void CopyMaterialToInstance(class UMaterialInstanceConstant* ChildInstance, TArray<FEditorParameterGroup> &ParameterGroups);`
- L243 _public prototype_ `static void TransitionAndCopyParameters(class UMaterialInstanceConstant* ChildInstance, TArray<FEditorParameterGroup> &ParameterGroups, bool bForceCopy = false);`
- L244 _public prototype_ `static FReply OnClickedSaveNewFunctionInstance(class UMaterialFunctionInterface* Object, class UMaterialInterface* PreviewMaterial, UObject* EditorObject);`
- L245 _public prototype_ `static FReply OnClickedSaveNewLayerInstance(class UMaterialFunctionInterface* Object, TSharedPtr<FSortedParamData> InSortedData);`
- L247 _public prototype_ `static void GetVectorChannelMaskComboBoxStrings(TArray<TSharedPtr<FString>>& OutComboBoxStrings, TArray<TSharedPtr<class SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems);`
- L248 _public prototype_ `static FString GetVectorChannelMaskValue(UDEditorParameterValue* InParameter);`
- L249 _public prototype_ `static void SetVectorChannelMaskValue(const FString& StringValue, TSharedPtr<IPropertyHandle> PropertyHandle, UDEditorParameterValue* InParameter, UObject* MaterialEditorInstance);`
- L251 _public prototype_ `static TArray<class UFactory*> GetAssetFactories(EMaterialParameterAssociation AssetType);`
- L257 _public prototype_ `static FEditorParameterGroup& GetParameterGroup(class UMaterial* InMaterial, FName& ParameterGroup, TArray<FEditorParameterGroup>& ParameterGroups);` — Returns group for parameter. Creates one if needed. @param ParameterGroup		Name to be looked for.
- L259 _public prototype_ `static TSharedRef<SWidget> MakeStackReorderHandle(TSharedPtr<IDraggableItem> InOwningStack);`
- L261 _public prototype_ `static bool OnShouldSetCurveAsset(const FAssetData& AssetData, TSoftObjectPtr<UCurveLinearColorAtlas> InAtlas);`
- L262 _public prototype_ `static bool OnShouldFilterCurveAsset(const FAssetData& AssetData, TSoftObjectPtr<UCurveLinearColorAtlas> InAtlas);`
- L263 _public prototype_ `static void SetPositionFromCurveAsset(const FAssetData& AssetData, TSoftObjectPtr<UCurveLinearColorAtlas> InAtlas, class UDEditorScalarParameterValue* InParameter, TSharedPtr<IPropertyHandle> PropertyHandle, UObject* MaterialEditorInstance);`
- L265 _public prototype_ `static void ResetCurveToDefault(UDEditorParameterValue* Parameter, UMaterialEditorInstanceConstant* MaterialEditorInstance);`
- L267 _public prototype_ `static TSharedRef<SWidget> CreateScalarEnumerationParameterValueWidget(TSoftObjectPtr<UObject> const& SoftEnumeration, TSharedPtr<IPropertyHandle> ParameterValueProperty);`
- L269 _public member_ `static FText LayerID;`
- L270 _public member_ `static FText BlendID;`
- L271 _public member_ `static FName LayerParamName;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MATERIALEDITOR_API`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FGetShowHiddenParameters, bool&);`
- L30 _prototype_ `DECLARE_DELEGATE_OneParam(FGetShowHiddenParameters, bool&);`

### `Source/Editor/MaterialEditor/Public/MaterialStatsCommon.h` (Public)


#### class `FMaterialResourceStats`  
`class FMaterialResourceStats : public FMaterialResource`  
_L12-36_
- inherits: `FMaterialResource`
- desc: custom resource material class used to mark the resource as used for shader stats extraction
- L15 _public function_ `FMaterialResourceStats()`
- L16 _public prototype_ `virtual ~FMaterialResourceStats() = default;`
- L18 _public function_ `FORCEINLINE UMaterial* GetMaterial()`
- L26 _public function_ `virtual bool IsPersistent() const override` — Should shaders compiled for this material be saved to disk?
- L29 _public function_ `virtual bool IsPreview() const override` — Use preview settings when compiling material. Used to avoid culling nodes behind landscape weights.
- L32 _public function_ `virtual bool RequiresSynchronousCompilation() const override` — Material resource stats never requires a synchronous compilation, otherwise opening up empty (newly created) material instance will block compiling default mat's shaders.
- L35 _public prototype_ `virtual void SetupExtraCompilationSettings(FExtraShaderCompilerSettings& Settings) const override;` — this will enable shader source extraction and pass paths to (eventual) offline shader compilers

#### enum `EPlatformCategoryType`  
`enum class EPlatformCategoryType : int32`  
_L39-47_
- desc: enumeration used to group shader platforms
- L41 _public enumerator_ `Desktop`
- L42 _public enumerator_ `Android`
- L43 _public enumerator_ `IOS`
- L44 _public enumerator_ `Console`
- L46 _public enumerator_ `Num`

#### enum `ERepresentativeShader`  
`enum class ERepresentativeShader`  
_L50-74_
- desc: enumeration containing the "types" of used shaders to display statistics
- L52 _public enumerator_ `FirstFragmentShader`
- L53 _public enumerator_ `StationarySurface = FirstFragmentShader`
- L54 _public enumerator_ `StationarySurfaceCSM`
- L55 _public enumerator_ `StationarySurfaceNPointLights`
- L56 _public enumerator_ `DynamicallyLitObject`
- L57 _public enumerator_ `RuntimeVirtualTextureOutput`
- L58 _public enumerator_ `UIDefaultFragmentShader`
- L59 _public enumerator_ `UIDynamicFragmentShader`
- L60 _public enumerator_ `LastFragmentShader = UIDynamicFragmentShader`
- L62 _public enumerator_ `FirstVertexShader`
- L63 _public enumerator_ `StaticMesh = FirstVertexShader`
- L64 _public enumerator_ `SkeletalMesh`
- L65 _public enumerator_ `SkinnedCloth`
- L67 _public enumerator_ `UIDefaultVertexShader`
- L68 _public enumerator_ `UIInstancedVertexShader`
- L69 _public enumerator_ `LastVertexShader = UIInstancedVertexShader`
- L71 _public enumerator_ `NaniteMesh`
- L73 _public enumerator_ `Num`

#### class `FMaterialStatsUtils`  
`class FMaterialStatsUtils`  
_L77-130_
- desc: class used for various stats utilities
- L101 _public prototype_ `static TSharedPtr<class FMaterialStats> CreateMaterialStats(class IMaterialEditor* MaterialEditor, const bool bShowMaterialInstancesMenu, const bool bAllowIgnoringCompilationErrors);` — call this to create an instance to FMaterialStats
- L104 _public prototype_ `static FString MaterialQualityToString(const EMaterialQualityLevel::Type Quality);` — utility functions that translate various enum values to strings
- L105 _public prototype_ `static FString MaterialQualityToShortString(const EMaterialQualityLevel::Type Quality);`
- L106 _public prototype_ `static EMaterialQualityLevel::Type StringToMaterialQuality(const FString& StrQuality);`
- L108 _public prototype_ `static FString GetPlatformTypeName(const EPlatformCategoryType InEnumValue);`
- L109 _public prototype_ `static FString ShaderPlatformTypeName(const EShaderPlatform PlatformID);`
- L115 _public prototype_ `static void GetRepresentativeInstructionCounts(TArray<FShaderInstructionsInfo>& Results, const class FMaterialResource* Target);` — Gets instruction counts that best represent the likely usage of this material based on shading model and other factors. @param Results - an array of descriptions to be populated
- L117 _public prototype_ `static void GetRepresentativeShaderTypesAndDescriptions(TMap<FName, TArray<FRepresentativeShaderInfo>>& OutShaderTypeNameAndDescriptions, const class FMaterial* TargetMaterial);`
- L118 _public prototype_ `static void ExtractMatertialStatsInfo(EShaderPlatform ShaderPlatform, struct FShaderStatsInfo& OutInfo, const FMaterialResource* Target);`
- L120 _public prototype_ `static FString RepresentativeShaderTypeToString(const ERepresentativeShader ShaderType);`
- L122 _public prototype_ `static FSlateColor QualitySettingColor(const EMaterialQualityLevel::Type QualityType);`
- L123 _public prototype_ `static FSlateColor PlatformTypeColor(EPlatformCategoryType PlatformType);`
- L125 _public prototype_ `static bool IsPlatformOfflineCompilerAvailable(const EShaderPlatform ShaderPlatform);`
- L127 _public prototype_ `static FString GetPlatformOfflineCompilerPath(const EShaderPlatform ShaderPlatform);` — `UE_DEPRECATED(5.5, "GetPlatformOfflineCompilerPath is no longer used; Use GetPlatformOfflineCompilerSettings instead.")`
- L128 _public prototype_ `static void GetPlatformOfflineCompilerSettings(const EShaderPlatform ShaderPlatform, FExtraShaderCompilerSettings& SCSettings);`
- L129 _public prototype_ `static bool PlatformNeedsOfflineCompiler(const EShaderPlatform ShaderPlatform);`

#### struct `FMaterialStatsUtils::FShaderInstructionsInfo`  
`struct FShaderInstructionsInfo`  
_L80-86_
- L82 _public member_ `ERepresentativeShader ShaderType;`
- L83 _public member_ `FString ShaderDescription;`
- L84 _public member_ `FString ShaderStatisticsString;`
- L85 _public member_ `int32 InstructionCount;`

#### struct `FMaterialStatsUtils::FRepresentativeShaderInfo`  
`struct FRepresentativeShaderInfo`  
_L88-97_
- L90 _public member_ `ERepresentativeShader ShaderType;`
- L91 _public member_ `FName ShaderName;`
- L92 _public member_ `FString ShaderDescription;`
- L94 _public function_ `FRepresentativeShaderInfo(const ERepresentativeShader _ShaderType, const FName _ShaderName, const FString& _StrDescription) : ShaderType(_ShaderType), ShaderName(_ShaderName), ShaderDescription(_StrDescription)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MATERIALEDITOR_API`
