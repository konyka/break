# Plugins / CommonConversationEditor

- module root: `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor`
- headers: 13; symbols: 347
- symbol kinds: class=13, delegate=3, function=13, macro=1, member=89, namespace=5, prototype=211, struct=7, typedef=5
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AIGraph, ApplicationCore, CommonConversationGraph, CommonConversationRuntime, CoreUObject, Engine, GraphEditor, InputCore, Kismet, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationDebugger.h` (Private)


#### class `FConversationDebugger`  
`class FConversationDebugger : public FTickableGameObject`  
_L20-216_
- inherits: `FTickableGameObject`
- L23 _public prototype_ `FConversationDebugger();`
- L24 _public prototype_ `~FConversationDebugger();`
- L26 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L27 _public prototype_ `virtual bool IsTickable() const override;`
- L28 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L29 _public function_ `virtual bool IsTickableInEditor() const override`
- L30 _public function_ `virtual TStatId GetStatId() const override`
- L33 _public prototype_ `void Refresh();` — Refresh the debugging information we are displaying (only when paused, as Tick() updates when running)
- L35 _public prototype_ `void Setup(UConversationDatabase* InTreeAsset, TSharedRef<class FConversationEditor> InEditorOwner);`
- L38 _public prototype_ `void CacheRootNode();` — Store the root node for easy access if we have not already
- L40 _public prototype_ `bool IsDebuggerReady() const;`
- L41 _public prototype_ `bool IsDebuggerRunning() const;`
- L42 _public prototype_ `bool IsShowingCurrentState() const;`
- L43 _public prototype_ `int32 GetShownStateIndex() const;`
- L45 _public prototype_ `void OnObjectSelected(UObject* Object);`
- L46 _public prototype_ `void OnAIDebugSelected(const APawn* Pawn);`
- L48 _public prototype_ `void OnBeginPIE(const bool bIsSimulating);` — void OnTreeStarted(const UConversationComponent& OwnerComp, const UConversationDatabase& InTreeAsset);
- L49 _public prototype_ `void OnEndPIE(const bool bIsSimulating);`
- L50 _public prototype_ `void OnPausePIE(const bool bIsSimulating);`
- L52 _public prototype_ `void OnBreakpointAdded(UConversationGraphNode* Node);`
- L53 _public prototype_ `void OnBreakpointRemoved(UConversationGraphNode* Node);`
- L55 _public prototype_ `void StepBackInto();`
- L56 _public prototype_ `void StepBackOver();`
- L57 _public prototype_ `void StepForwardInto();`
- L58 _public prototype_ `void StepForwardOver();`
- L59 _public prototype_ `void StepOut();`
- L60 _public prototype_ `bool CanStepBackInto() const;`
- L61 _public prototype_ `bool CanStepBackOver() const;`
- L62 _public prototype_ `bool CanStepForwardInto() const;`
- L63 _public prototype_ `bool CanStepForwardOver() const;`
- L64 _public prototype_ `bool CanStepOut() const;`
- L66 _public prototype_ `static void StopPlaySession();`
- L67 _public prototype_ `static void PausePlaySession();`
- L68 _public prototype_ `static void ResumePlaySession();`
- L69 _public prototype_ `static bool IsPlaySessionPaused();`
- L70 _public prototype_ `static bool IsPlaySessionRunning();`
- L71 _public prototype_ `static bool IsPIESimulating();`
- L72 _public prototype_ `static bool IsPIENotSimulating();`
- L74 _public prototype_ `FString GetDebuggedInstanceDesc() const;`
- L79 _public prototype_ `void InitializeFromParent(class FConversationDebugger* ParentDebugger);`
- L80 _public prototype_ `bool HasContinuousNextStep() const;`
- L81 _public prototype_ `bool HasContinuousPrevStep() const;`
- L89 _public prototype_ `FText FindValueForKey(const FName& InKeyName, bool bUseCurrentState) const;` — Find a (display) value for a given key. @param	InKeyName			Key to find a value for @param	bUseCurrentState	Whether to use the current (present) state or the state at the active step index @return the value to display to the user.
- L92 _public prototype_ `float GetTimeStamp(bool bUseCurrentState) const;` — Gets the timestamp to be displayed, either current or saved
- L95 _public prototype_ `DECLARE_EVENT_OneParam(FConversationDebugger, FOnDebuggedBlackboardChanged, UBlackboardData*);` — Delegate fired when the debugged blackboard is changed
- L96 _public function_ `FOnDebuggedBlackboardChanged& OnDebuggedBlackboardChanged()`
- L101 _private member_ `TWeakPtr<FConversationEditor> EditorOwner;` — owning editor
- L104 _private member_ `UConversationDatabase* TreeAsset;` — asset for debugging
- L113 _private member_ `int32 DebuggerInstanceIndex;` — matching debugger instance index from component's stack
- L116 _private member_ `int32 ActiveStepIndex;` — index of state from buffer to show
- L119 _private member_ `int32 DisplayedStepIndex;` — index of displayed step, used to detect changes
- L122 _private member_ `int32 LastValidStepId;` — id of last valid step
- L125 _private member_ `int32 StepForwardIntoIdx;` — indices of display steps for different step actions
- L126 _private member_ `int32 StepForwardOverIdx;`
- L127 _private member_ `int32 StepBackIntoIdx;`
- L128 _private member_ `int32 StepBackOverIdx;`
- L129 _private member_ `int32 StepOutIdx;`
- L132 _private member_ `TArray<uint16> ActiveBreakpoints;` — execution indices of currently active breakpoints
- L138 _private member_ `uint32 bIsPIEActive : 1;` — cached PIE state
- L141 _private member_ `uint32 bIsCurrentSubtree : 1;` — set when debugger instance is currently active one
- L144 _private member_ `uint16 StoppedOnBreakpointExecutionIndex;` — execution index of node that caused activated the breakpoint
- L147 _private member_ `TMap<FName, FString> SavedValues;` — Lookup of currently debugged blackboard values
- L148 _private member_ `TMap<FName, FString> CurrentValues;`
- L151 _private member_ `float SavedTimestamp;` — Debugger timestamps
- L152 _private member_ `float CurrentTimestamp;`
- L155 _private prototype_ `void UpdateDebuggerInstance();` — set value of DebuggerInstanceIndex variable
- L158 _private prototype_ `void ClearDebuggerState(bool bKeepSubtree = false);` — clear all runtime variables
- L161 _private prototype_ `void OnActiveNodeChanged(const TArray<uint16>& ActivePath, const TArray<uint16>& PrevStepPath);` — try using breakpoints on node change
- L165 _private prototype_ `void FindMatchingTreeInstance();` — scan all actors and try to find matching BT component used only when user starts PIE before opening editor
- L174 _private prototype_ `void FindLockedDebugActor(class UWorld* World);` — try to find pawn currently locked by ai debug tool
- L177 _private prototype_ `void CollectBreakpointsFromAsset(class UConversationGraphNode* Node);` — recursively collect all breakpoint indices from child nodes
- L180 _private prototype_ `void UpdateAssetFlags(const struct FConversationDebuggerInstance& Data, class UConversationGraphNode* Node, int32 StepIdx);` — recursively update node flags on all child nodes
- L186 _private prototype_ `void SetCompositeDecoratorFlags(const struct FConversationDebuggerInstance& Data, class UConversationGraphNode_CompositeDecorator* Node);` — set debugger flags on GraphNode for composite decorator
- L189 _private prototype_ `void UpdateAssetRuntimeDescription(const TArray<FString>& RuntimeDescriptions, class UConversationGraphNode* Node);` — recursively update node flags on all child nodes
- L198 _private prototype_ `void UpdateDebuggerViewOnInstanceChange();` — updates variables in debugger details view
- L199 _private prototype_ `void UpdateDebuggerViewOnStepChange();`
- L200 _private prototype_ `void UpdateDebuggerViewOnTick();`
- L203 _private prototype_ `int32 FindActiveInstanceIdx(int32 StepIdx) const;` — find valid instance for given debugger step
- L206 _private prototype_ `void UpdateCurrentSubtree();` — check if currently debugged instance is active subtree
- L209 _private prototype_ `void UpdateCurrentStep(int32 PrevStepIdx, int32 NewStepIdx);` — updates currently displayed execution step
- L212 _private prototype_ `void UpdateAvailableActions();` — updates button states
- L215 _private member_ `FOnDebuggedBlackboardChanged OnDebuggedBlackboardChangedEvent;` — Delegate fired when the debugged blackboard is changed

#### Free symbols / members of external scopes

- L95 _delegate_ `DECLARE_EVENT_OneParam(FConversationDebugger, FOnDebuggedBlackboardChanged, UBlackboardData*);` — Delegate fired when the debugged blackboard is changed

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationEditor.h` (Private)


#### class `FConversationEditor`  
`class FConversationEditor : public FWorkflowCentricApplication, public FAIGraphEditor, public FNotifyHook`  
_L26-198_
- inherits: `FWorkflowCentricApplication,FAIGraphEditor,FNotifyHook`
- L29 _public prototype_ `FConversationEditor();`
- L31 _public prototype_ `virtual ~FConversationEditor();` — Destructor
- L33 _public member_ `FSimpleMulticastDelegate FocusedGraphEditorChanged;`
- L35 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L37 _public prototype_ `void InitConversationEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* InObject );`
- L39 _public prototype_ `static TSharedRef<FConversationEditor> CreateConversationEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UObject* Object);`
- L42 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L43 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L44 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L45 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L46 _public prototype_ `virtual FText GetToolkitName() const override;`
- L47 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L50 _public prototype_ `virtual void FocusWindow(UObject* ObjectToFocusOn = NULL);`
- L53 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L54 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L58 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L62 _public prototype_ `void OnNodeDoubleClicked(class UEdGraphNode* Node);` — Delegates
- L63 _public prototype_ `void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);`
- L64 _public prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);`
- L66 _public prototype_ `void OnEnableBreakpoint();`
- L67 _public prototype_ `bool CanEnableBreakpoint() const;`
- L68 _public prototype_ `void OnToggleBreakpoint();`
- L69 _public prototype_ `bool CanToggleBreakpoint() const;`
- L70 _public prototype_ `void OnDisableBreakpoint();`
- L71 _public prototype_ `bool CanDisableBreakpoint() const;`
- L72 _public prototype_ `void OnAddBreakpoint();`
- L73 _public prototype_ `bool CanAddBreakpoint() const;`
- L74 _public prototype_ `void OnRemoveBreakpoint();`
- L75 _public prototype_ `bool CanRemoveBreakpoint() const;`
- L77 _public prototype_ `void SearchConversationDatabase();`
- L78 _public prototype_ `bool CanSearchConversationDatabase() const;`
- L80 _public prototype_ `void JumpToNode(const UEdGraphNode* Node);`
- L82 _public prototype_ `bool IsPropertyEditable() const;`
- L83 _public prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L85 _public prototype_ `void UpdateToolbar();`
- L86 _public prototype_ `bool IsDebuggerReady() const;`
- L89 _public prototype_ `bool IsDebuggerPaused() const;` — Get whether the debugger is currently running and the PIE session is paused
- L91 _public prototype_ `TSharedRef<class SWidget> OnGetDebuggerActorsMenu();`
- L93 _public prototype_ `FText GetDebuggerActorDesc() const;` — void OnDebuggerActorSelected(TWeakObjectPtr<UConversationComponent> InstanceToDebug);
- L95 _public prototype_ `FGraphAppearanceInfo GetGraphAppearance() const;`
- L96 _public prototype_ `bool InEditingMode(bool bGraphIsEditable) const;`
- L98 _public prototype_ `EVisibility GetDebuggerDetailsVisibility() const;`
- L99 _public prototype_ `EVisibility GetInjectedNodeVisibility() const;`
- L101 _public prototype_ `TWeakPtr<SGraphEditor> GetFocusedGraphPtr() const;`
- L108 _public prototype_ `static FText GetLocalizedMode(FName InMode);` — Get the localized text to display for the specified mode @param	InMode	The mode to display @return the localized text representation of the mode
- L111 _public function_ `TSharedPtr<class FConversationEditorToolbar> GetToolbarBuilder()` — Access the toolbar builder for this editor
- L114 _public prototype_ `UConversationDatabase* GetConversationAsset() const;` — Get the behavior tree we are editing (if any)
- L117 _public prototype_ `TSharedRef<SWidget> SpawnProperties();` — Spawns the tab with the update graph inside
- L120 _public prototype_ `TSharedRef<SWidget> SpawnSearch();` — Spawns the search tab
- L123 _public prototype_ `TSharedRef<SWidget> SpawnConversationTree();` — Spawns the conversation tree tab
- L126 _public prototype_ `void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);` — @todo This is a hack for now until we reconcile the default toolbar with application modes [duplicated from counterpart in Blueprint Editor]
- L129 _public prototype_ `void RestoreConversation();` — Restores the behavior tree graph we were editing or creates a new one if none is available
- L132 _public prototype_ `void SaveEditedObjectState();` — Save the graph state for later editing
- L135 _public prototype_ `FText HandleGetDebugKeyValue(const FName& InKeyName, bool bUseCurrentState) const;` — Delegate handler for displaying debugger values
- L138 _public prototype_ `float HandleGetDebugTimeStamp(bool bUseCurrentState) const;` — Delegate handler for retrieving timestamp to display
- L141 _public prototype_ `bool CanCreateNewNodeClasses() const;` — Are we allowed to create new node classes right now?
- L144 _public prototype_ `TSharedRef<SWidget> HandleCreateNewClassMenu(UClass* BaseClass) const;` — Create the menu used to make a new task node
- L147 _public prototype_ `void HandleNewNodeClassPicked(UClass* InClass) const;` — Handler for when a node class is picked
- L150 _protected prototype_ `virtual void FixupPastedNodes(const TSet<UEdGraphNode*>& PastedGraphNodes, const TMap<FGuid , FGuid >& NewToOldNodeMapping) override;`
- L154 _private prototype_ `TSharedRef<class SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);` — Create widget for graph editing
- L157 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L160 _private prototype_ `void ExtendMenu();` — Add custom menu options
- L163 _private prototype_ `void BindCommonCommands();` — Setup common commands
- L166 _private prototype_ `void BindDebuggerToolbarCommands();` — Setup commands
- L169 _private prototype_ `virtual void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection) override;` — Called when the selection changes in the GraphEditor
- L172 _private prototype_ `void RefreshDebugger();` — Refresh the debugger's display
- L174 _private member_ `TSharedPtr<FDocumentTracker> DocumentManager;`
- L175 _private member_ `TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;`
- L178 _private member_ `UConversationDatabase* ConversationAsset;` — The conversation being edited
- L181 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View
- L183 _private member_ `TSharedPtr<class FConversationDebugger> Debugger;`
- L186 _private member_ `TSharedPtr<SFindInConversation> FindResults;` — Find results log as well as the search filter
- L188 _private member_ `TSharedPtr<SConversationTreeEditor> TreeEditor;`
- L190 _private member_ `uint32 bForceDisablePropertyEdit : 1;`
- L192 _private member_ `TSharedPtr<FConversationEditorToolbar> ToolbarBuilder;`
- L196 _public member_ `static const FName GraphViewMode;` — Modes in mode switcher
- L197 _public member_ `static const FName TreeViewMode;`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationEditorCommands.h` (Private)


#### class `FConversationEditorCommonCommands`  
`class FConversationEditorCommonCommands : public TCommands<FConversationEditorCommonCommands>`  
_L10-19_
- inherits: `TCommands<FConversationEditorCommonCommands>`
- L13 _public prototype_ `FConversationEditorCommonCommands();`
- L15 _public member_ `TSharedPtr<FUICommandInfo> SearchConversation;`
- L18 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `FConversationDebuggerCommands`  
`class FConversationDebuggerCommands : public TCommands<FConversationDebuggerCommands>`  
_L24-44_
- inherits: `TCommands<FConversationDebuggerCommands>`
- L27 _public prototype_ `FConversationDebuggerCommands();`
- L29 _public member_ `TSharedPtr<FUICommandInfo> BackInto;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> BackOver;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ForwardInto;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ForwardOver;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> StepOut;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> PausePlaySession;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ResumePlaySession;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> StopPlaySession;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> CurrentValues;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> SavedValues;`
- L43 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationEditorModes.h` (Private)


#### class `FConversationEditorApplicationMode_GraphView`  
`class FConversationEditorApplicationMode_GraphView : public FApplicationMode`  
_L14-28_
- inherits: `FApplicationMode`
- desc: Application mode for main conversation editing mode
- L17 _public prototype_ `FConversationEditorApplicationMode_GraphView(TSharedPtr<FConversationEditor> InConversationEditor);`
- L19 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L20 _public prototype_ `virtual void PreDeactivateMode() override;`
- L21 _public prototype_ `virtual void PostActivateMode() override;`
- L24 _protected member_ `TWeakPtr<FConversationEditor> ConversationEditor;`
- L27 _protected member_ `FWorkflowAllowedTabSet ConversationEditorTabFactories;` — Set of spawnable tabs in behavior tree editing mode

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationEditorTabFactories.h` (Private)


#### struct `FConversationDetailsSummoner`  
`struct FConversationDetailsSummoner : public FWorkflowTabFactory`  
_L12-22_
- inherits: `FWorkflowTabFactory`
- L15 _public prototype_ `FConversationDetailsSummoner(TSharedPtr<FConversationEditor> InConversationEditorPtr);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L18 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<FConversationEditor> ConversationEditorPtr;`

#### struct `FConversationSearchSummoner`  
`struct FConversationSearchSummoner : public FWorkflowTabFactory`  
_L24-34_
- inherits: `FWorkflowTabFactory`
- L27 _public prototype_ `FConversationSearchSummoner(TSharedPtr<FConversationEditor> InConversationEditorPtr);`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L30 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L33 _protected member_ `TWeakPtr<FConversationEditor> ConversationEditorPtr;`

#### struct `FConversationTreeEditorSummoner`  
`struct FConversationTreeEditorSummoner : public FWorkflowTabFactory`  
_L36-46_
- inherits: `FWorkflowTabFactory`
- L39 _public prototype_ `FConversationTreeEditorSummoner(TSharedPtr<FConversationEditor> InConversationEditorPtr);`
- L41 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L42 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L45 _protected member_ `TWeakPtr<FConversationEditor> ConversationEditorPtr;`

#### struct `FConversationGraphEditorSummoner`  
`struct FConversationGraphEditorSummoner : public FDocumentTabFactoryForObjects<UEdGraph>`  
_L48-67_
- inherits: `FDocumentTabFactoryForObjects<UEdGraph>`
- L51 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);`
- L53 _public prototype_ `FConversationGraphEditorSummoner(TSharedPtr<FConversationEditor> InConversationEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);`
- L55 _public prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;`
- L56 _public prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;`
- L59 _protected prototype_ `virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override;`
- L60 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L61 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L62 _protected prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L65 _protected member_ `TWeakPtr<FConversationEditor> ConversationEditorPtr;`
- L66 _protected member_ `FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;`

#### Free symbols / members of external scopes

- L51 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationEditorTabs.h` (Private)


#### struct `FConversationEditorTabs`  
`struct FConversationEditorTabs`  
_L8-17_
- L11 _public member_ `static const FName GraphDetailsID;` — Tab identifiers
- L12 _public member_ `static const FName SearchID;`
- L15 _public member_ `static const FName GraphEditorID;` — Document tab identifiers
- L16 _public member_ `static const FName TreeEditorID;`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationEditorToolbar.h` (Private)


#### class `FConversationEditorToolbar`  
`class FConversationEditorToolbar : public TSharedFromThis<FConversationEditorToolbar>`  
_L12-28_
- inherits: `TSharedFromThis<FConversationEditorToolbar>`
- L15 _public function_ `FConversationEditorToolbar(TSharedPtr<FConversationEditor> InConversationEditor) : ConversationEditor(InConversationEditor)`
- L18 _public prototype_ `void AddDebuggerToolbar(TSharedPtr<FExtender> Extender);`
- L19 _public prototype_ `void AddConversationEditorToolbar(TSharedPtr<FExtender> Extender);`
- L22 _private prototype_ `void FillDebuggerToolbar(FToolBarBuilder& ToolbarBuilder);`
- L23 _private prototype_ `void FillConversationEditorToolbar(FToolBarBuilder& ToolbarBuilder);`
- L27 _protected member_ `TWeakPtr<FConversationEditor> ConversationEditor;` — Pointer back to the blueprint editor tool that owns us

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/ConversationEditorUtils.h` (Private)


#### struct `ConversationEditorUtils::FPropertySelectionInfo`  
`struct FPropertySelectionInfo`  
_L9-14_
- L11 _public function_ `FPropertySelectionInfo()`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ConversationEditorUtils`
- L17 _prototype_ `TArray<UObject*> GetSelectionForPropertyEditor(const TSet<UObject*>& InSelection, FPropertySelectionInfo& OutSelectionInfo);` (scope `ConversationEditorUtils`) — Given a selection of nodes, return the instances that should be selected be selected for editing in the property panel

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/FindInConversationGraph.h` (Private)


#### class `FFindInConversationResult`  
`class FFindInConversationResult`  
_L15-50_
- desc: Item that matched the search results
- L19 _public prototype_ `FFindInConversationResult(const FString& InValue);` — Create a root (or only text) result
- L22 _public prototype_ `FFindInConversationResult(const FString& InValue, TSharedPtr<FFindInConversationResult>& InParent, UEdGraphNode* InNode);` — Create a BT node result
- L25 _public prototype_ `FReply OnClick(TWeakPtr<class FConversationEditor> ConversationEditor, TSharedPtr<FFindInConversationResult> Root);` — Called when user clicks on the search item
- L28 _public prototype_ `TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L31 _public prototype_ `FString GetCommentText() const;` — Gets the comment on this node if any
- L34 _public prototype_ `FString GetNodeTypeText() const;` — Gets the node type
- L37 _public prototype_ `void SetNodeHighlight(bool bHighlight);` — Highlights conversation graph nodes
- L40 _public member_ `TArray< TSharedPtr<FFindInConversationResult> > Children;` — Any children listed under this conversation node
- L43 _public member_ `FString Value;` — The string value for this result
- L46 _public member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;` — The graph node that this search result refers to
- L49 _public member_ `TWeakPtr<FFindInConversationResult> Parent;` — Search result parent

#### class `SFindInConversation`  
`class SFindInConversation : public SCompoundWidget`  
_L53-116_
- inherits: `SCompoundWidget`
- desc: Widget for searching for (BT nodes) across focused Conversation
- L56 _public function_ `SLATE_BEGIN_ARGS(SFindInConversation)`
- L57 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FConversationEditor> InConversationEditor);`
- L62 _public prototype_ `void FocusForUse();` — Focuses this widget's search box
- L65 _private typedef_ `typedef TSharedPtr<FFindInConversationResult> FSearchResult;`
- L66 _private typedef_ `typedef STreeView<FSearchResult> STreeViewType;`
- L69 _private prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L72 _private prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user commits text
- L75 _private prototype_ `void OnGetChildren(FSearchResult InItem, TArray<FSearchResult>& OutChildren);` — Get the children of a row
- L78 _private prototype_ `void OnTreeSelectionChanged(FSearchResult Item, ESelectInfo::Type SelectInfo);` — Called when user clicks on a new result
- L81 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L84 _private prototype_ `void InitiateSearch();` — Begins the search based on the SearchValue
- L87 _private prototype_ `void MatchTokens(const TArray<FString>& Tokens);` — Find any results that contain all of the tokens
- L90 _private prototype_ `void MatchTokensInChild(const TArray<FString>& Tokens, UEdGraphNode* Child, FSearchResult ParentNode);` — Find if child contains all of the tokens and add a result accordingly
- L93 _private prototype_ `static bool StringMatchesSearchTokens(const TArray<FString>& Tokens, const FString& ComparisonString);` — Determines if a string matches the search tokens
- L97 _private member_ `TWeakPtr<class FConversationEditor> ConversationEditorPtr;` — Pointer back to the behavior tree editor that owns us
- L100 _private member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L103 _private member_ `TSharedPtr<class SSearchBox> SearchTextField;` — The search text box
- L106 _private member_ `TArray<FSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L109 _private member_ `FSearchResult RootSearchResult;` — we need to keep a handle on the root result, because it won't show up in the tree
- L112 _private member_ `FText HighlightText;` — The string to highlight in the results
- L115 _private member_ `FString SearchValue;` — The string to search for

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectInfo`
- L11 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/SConversationDiff.h` (Private)


#### class `SConversationDiff`  
`class SConversationDiff: public SCompoundWidget`  
_L20-190_
- inherits: `SCompoundWidget`
- L25 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOpenInDefaults, UConversationDatabase* , UConversationDatabase*);` — Delegate for default Diff tool
- L27 _public function_ `SLATE_BEGIN_ARGS(SConversationDiff )`
- L28 _public prototype_ `SLATE_ARGUMENT(UConversationDatabase*, OldBank) SLATE_ARGUMENT(UConversationDatabase*, NewBank) SLATE_ARGUMENT(FRevisionInfo, OldRevision) SLATE_ARGUMENT(FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_EVENT(FOpenInDefaults, OpenInDefaults) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L109 _private typedef_ `typedef TSharedPtr<struct FTreeDiffResultItem> FSharedDiffOnGraph;` — Type def for our Table item
- L112 _private typedef_ `typedef SListView<FSharedDiffOnGraph > SListViewType;` — Type def of our Table Type
- L119 _private prototype_ `FReply OnOpenInDefaults();` — User clicks defaults view button to display defaults in remote diff tool @return If its been handled
- L125 _private prototype_ `TSharedRef<SWidget> GenerateDiffListWidget();` — Generate list of differences @return The widget containing the Difference list
- L130 _private prototype_ `void BuildDiffSourceArray();` — Build up the Diff Source Array
- L135 _private prototype_ `void NextDiff();` — Go to Next Difference
- L140 _private prototype_ `void PrevDiff();` — Go to Previous Difference
- L146 _private prototype_ `int32 GetCurrentDiffIndex();` — Get current Index into the diff array @return The Index
- L153 _private prototype_ `void OnSelectionChanged(FSharedDiffOnGraph Item, ESelectInfo::Type SelectionType);` — Called when difference selection is changed @param Item The item that was selected @param SelectionType The way it was selected
- L161 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSharedDiffOnGraph Item, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated @param Item The item being generated @param OwnerTable The table its going into @return The Row that was inserted
- L168 _private prototype_ `SGraphEditor* GetGraphEditorForGraph(UEdGraph* Graph) const;` — Get the Slate graph editor of the supplied Graph @param Graph The graph we want the Editor from @return The Graph Editor
- L174 _private member_ `FOpenInDefaults OpenInDefaults;` — Delegate to call when user wishes to view the defaults
- L177 _private member_ `FConversationDiffPanel PanelOld, PanelNew;` — The 2 panels we will be comparing
- L177 _private member_ `FConversationDiffPanel PanelOld, PanelNew;` — The 2 panels we will be comparing
- L180 _private member_ `TArray<FSharedDiffOnGraph> DiffListSource;` — Source for list view
- L183 _private member_ `TSharedPtr<FUICommandList> KeyCommands;` — Key commands processed by this widget
- L186 _private member_ `TSharedPtr<SListViewType> DiffList;` — ListView of differences
- L189 _private member_ `UEdGraphPin* LastOtherPinTarget;` — The last other pin the user clicked on

#### struct `SConversationDiff::FConversationDiffPanel`  
`struct FConversationDiffPanel`  
_L41-106_
- desc: Panel used to display the conversation
- L44 _public prototype_ `FConversationDiffPanel();` — Constructor
- L51 _public prototype_ `void GeneratePanel(UEdGraph* Graph, UEdGraph* GraphToDiff);` — Generates the slate for this panel @param Graph        The Left side graph. @param GraphToDiff  The right side graph to diff against
- L57 _public prototype_ `FText GetTitle() const;` — Returns title for this panel @return The Title
- L62 _public prototype_ `void CopySelectedNodes();` — Called when user hits keyboard shortcut to copy nodes
- L67 _public prototype_ `void OnSelectionChanged( const FGraphPanelSelectionSet& Selection );` — Called When graph node gains focus
- L72 _public prototype_ `bool IsPropertyEditable();` — Delegate to say if a node property should be editable
- L78 _public prototype_ `FGraphPanelSelectionSet GetSelectedNodes() const;` — Gets whatever nodes are selected in the Graph Editor @return Gets the selected nodes in the graph
- L84 _public prototype_ `bool CanCopyNodes() const;` — Can user copy any of the selected nodes? @return True if can copy
- L87 _public member_ `UConversationDatabase* ConversationBank;` — The behavior Tree that owns the graph we are showing
- L90 _public member_ `FRevisionInfo RevisionInfo;` — Revision information for this behavior tree
- L93 _public member_ `TSharedPtr<SBorder> GraphEditorBorder;` — The border around the graph editor, used to change the content when new graphs are set
- L96 _public member_ `TWeakPtr<class SGraphEditor> GraphEditor;` — The graph editor which does the work of displaying the graph
- L99 _public member_ `bool bShowAssetName;` — If we should show a name identifying which asset this panel is displaying
- L102 _public member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this diff panel
- L105 _public member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOpenInDefaults, UConversationDatabase* , UConversationDatabase*);` — Delegate for default Diff tool

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Private/SConversationTreeEditor.h` (Private)


#### class `FConversationTreeNode`  
`class FConversationTreeNode : public TSharedFromThis<FConversationTreeNode>`  
_L17-52_
- inherits: `TSharedFromThis<FConversationTreeNode>`
- desc: Item that matched the search results
- L21 _public prototype_ `FConversationTreeNode(UEdGraphNode* InNode, const TSharedPtr<const FConversationTreeNode>& InParent);` — Create a BT node result
- L24 _public prototype_ `FReply OnClick(TWeakPtr<FConversationEditor> ConversationEditor);` — Called when user clicks on the search item
- L27 _public prototype_ `TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L30 _public prototype_ `FString GetCommentText() const;` — Gets the comment on this node if any
- L33 _public prototype_ `FText GetNodeTypeText() const;` — Gets the node type
- L35 _public prototype_ `FText GetText() const;`
- L37 _public function_ `UEdGraphNode* GetGraphNode() const`
- L39 _public prototype_ `const TArray< TSharedPtr<FConversationTreeNode> >& GetChildren() const;`
- L42 _public member_ `TWeakPtr<const FConversationTreeNode> ParentPtr;` — Search result parent
- L45 _private member_ `mutable bool bChildrenDirty = true;`
- L48 _private member_ `mutable TArray< TSharedPtr<FConversationTreeNode> > Children;` — Any children listed under this conversation node
- L51 _private member_ `TWeakObjectPtr<UEdGraphNode> GraphNodePtr;` — The graph node that this search result refers to

#### class `SConversationTreeEditor`  
`class SConversationTreeEditor : public SCompoundWidget`  
_L55-94_
- inherits: `SCompoundWidget`
- L58 _public function_ `SLATE_BEGIN_ARGS(SConversationTreeEditor)`
- L59 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FConversationEditor> InConversationEditor);`
- L64 _private typedef_ `typedef STreeView<TSharedPtr<FConversationTreeNode>> STreeViewType;`
- L67 _private prototype_ `void OnGetChildren(TSharedPtr<FConversationTreeNode> InItem, TArray<TSharedPtr<FConversationTreeNode>>& OutChildren);` — Get the children of a row
- L70 _private prototype_ `void OnTreeSelectionChanged(TSharedPtr<FConversationTreeNode> Item, ESelectInfo::Type SelectInfo);` — Called when user clicks on a new result
- L73 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FConversationTreeNode> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L75 _private prototype_ `void OnFocusedGraphChanged();`
- L76 _private prototype_ `void OnGraphChanged(const FEdGraphEditAction& Action);`
- L79 _private prototype_ `void RefreshTree();` — Begins the search based on the SearchValue
- L80 _private prototype_ `void BuildTree();`
- L84 _private member_ `TWeakPtr<class FConversationEditor> ConversationEditorPtr;` — Pointer back to the behavior tree editor that owns us
- L87 _private member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L90 _private member_ `TArray<TSharedPtr<FConversationTreeNode>> RootNodes;` — This buffer stores the currently displayed results
- L93 _private member_ `FString SearchValue;` — The string to search for

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Public/AssetTypeActions_ConversationDatabase.h` (Public)


#### class `FAssetTypeActions_ConversationDatabase`  
`class FAssetTypeActions_ConversationDatabase : public FAssetTypeActions_Base`  
_L11-26_
- inherits: `FAssetTypeActions_Base`
- L15 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L16 _public function_ `virtual FColor GetTypeColor() const override`
- L17 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L18 _public prototype_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;`
- L19 _public prototype_ `virtual uint32 GetCategories() override;`
- L20 _public prototype_ `virtual void PerformAssetDiff(UObject* Asset1, UObject* Asset2, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override;`
- L25 _private prototype_ `void OpenInDefaults(UConversationDatabase* OldBank, UConversationDatabase* NewBank) const;` — Called to open the Behavior Tree defaults view, this opens whatever text diff tool the user has

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COMMONCONVERSATIONEDITOR_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationEditor/Public/CommonConversationEditorModule.h` (Public)


#### class `FCommonConversationEditorModule`  
`class FCommonConversationEditorModule : public IModuleInterface`  
_L11-21_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `TArray<TSharedPtr<FAssetTypeActions_Base>> ItemDataAssetTypeActions;`
