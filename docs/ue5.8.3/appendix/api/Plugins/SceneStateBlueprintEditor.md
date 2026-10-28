# Plugins / SceneStateBlueprintEditor

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor`
- headers: 55; symbols: 686
- symbol kinds: class=50, delegate=1, enum=1, enumerator=3, function=30, macro=1, member=86, namespace=191, prototype=312, struct=7, typedef=4
- PrivateDependencyModuleNames: AssetDefinition, BlueprintGraph, DetailCustomizations, Engine, GraphEditor, InputCore, Kismet, KismetCompiler, KismetWidgets, PropertyBindingUtils, PropertyBindingUtilsEditor, PropertyEditor, SceneState, SceneStateBinding, SceneStateBlueprint, SceneStateEvent, SceneStateMachineEditor, SceneStateMachineGraph, SceneStateTransitionGraph, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets
- PublicDependencyModuleNames: Core, CoreUObject, SceneStateEditor, UnrealEd

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/AppModes/SceneStateAppModes.h` (Private)


#### struct `UE::SceneState::Editor::FAppModes`  
`struct FAppModes`  
_L13-20_
- desc: Describes all the available App Modes for the Scene State Editor
- L16 _public member_ `static const FName Blueprint;` — Available App Modes
- L19 _public prototype_ `static FText GetAppModeDisplayName(FName InAppMode);` — Retrieves the display name for a given app mode

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/AppModes/SceneStateBlueprintEditorMode.h` (Private)


#### class `UE::SceneState::Editor::FBlueprintAppMode`  
`class FBlueprintAppMode : public FBlueprintEditorApplicationMode`  
_L16-20_
- inherits: `FBlueprintEditorApplicationMode`
- desc: Defines the layout for the 'Blueprint' mode in the Scene State Editor
- L19 _public prototype_ `explicit FBlueprintAppMode(const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/AssetDefinition_SceneStateBlueprint.h` (Private)


#### class `UAssetDefinition_SceneStateBlueprint`  
`class UAssetDefinition_SceneStateBlueprint : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/AssetDefinition_SceneStateTaskBlueprint.h` (Private)


#### class `UAssetDefinition_SceneStateTaskBlueprint`  
`class UAssetDefinition_SceneStateTaskBlueprint : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Compiler/SceneStateBindingCompiler.h` (Private)


#### enum `UE::SceneState::Editor::EDataAccessType`  
`enum class EDataAccessType : uint8`  
_L26-31_
- desc: Describes the types how a binding can be batched
- L28 _public enumerator_ `None`
- L29 _public enumerator_ `Copy`
- L30 _public enumerator_ `Reference`

#### class `UE::SceneState::Editor::FBindingCompiler`  
`class FBindingCompiler`  
_L33-94_
- L36 _public prototype_ `explicit FBindingCompiler(FBlueprintCompilerContext& InContext, TNotNull<USceneStateBlueprint*> InBlueprint, TNotNull<USceneStateTemplateData*> InTemplateData);`
- L38 _public prototype_ `void Compile();`
- L41 _private prototype_ `void AddBindingDesc(FSceneStateBindingDesc&& InBindingDesc, FPropertyBindingDataView InDataView);`
- L43 _private prototype_ `void AddRootBindingDesc();`
- L44 _private prototype_ `void AddStateBindingDescs();`
- L45 _private prototype_ `void AddStateMachineBindingDescs();`
- L46 _private prototype_ `void AddTransitionBindingDescs();`
- L47 _private prototype_ `void AddTaskBindingDescs();`
- L48 _private prototype_ `void AddEventHandlerBindingDescs();`
- L49 _private prototype_ `void AddFunctionBindingDescs();`
- L51 _private prototype_ `bool ValidateBinding(const FSceneStateBinding& InBinding) const;`
- L53 _private prototype_ `void ResolveBindingDataHandles();`
- L54 _private prototype_ `void RemoveInvalidBindings();`
- L56 _private prototype_ `void GroupBindings();`
- L57 _private prototype_ `void CompileCopies();`
- L58 _private prototype_ `void CompileReferences();`
- L60 _private prototype_ `void OnBindingsBatchCompiled(FPropertyBindingIndex16 InBindingsBatch, const FSceneStateBindingDataHandle& InTargetDataHandle);`
- L62 _private prototype_ `FSceneStateBindingDataHandle GetDataHandleById(const FGuid& InStructId);`
- L65 _private member_ `FBlueprintCompilerContext& Context;` — Compiler context used for error logging
- L68 _private member_ `TObjectPtr<USceneStateBlueprint> Blueprint;` — The blueprint that generated the class
- L71 _private member_ `TObjectPtr<USceneStateTemplateData> TemplateData;` — The target to store the compiled bindings
- L74 _private member_ `FBindingFunctionCompiler BindingFunctionCompiler;` — Compiler for the functions found within the bindings
- L77 _private member_ `TMap<FGuid, const FPropertyBindingDataView> ValidBindingMap;` — Map of struct ids to their binding data view
- L80 _private member_ `TMap<FSceneStateBindingDataHandle, FPropertyBindingDataView> TemplateDataViewMap;` — Map of gathered binding data handle to the template data view
- L93 _private member_ `TMap<EDataAccessType, FBatchRange> BatchRangeMap;` — Map of the batching type to the binding range index for that type A map is not the best candidate to hold this information, and only used for readability.

#### struct `UE::SceneState::Editor::FBindingCompiler::FBatchRange`  
`struct FBatchRange`  
_L82-88_
- L85 _public member_ `int32 Index = INDEX_NONE;` — Start index of the batch, inclusive
- L87 _public member_ `int32 Count = 0;` — Number of elements in the batch

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SceneState` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace SceneState` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Compiler/SceneStateBindingFunctionCompiler.h` (Private)


#### class `UE::SceneState::Editor::FBindingFunctionCompiler`  
`class FBindingFunctionCompiler`  
_L14-46_
- desc: Compiles all the functions found throughout all the bindings
- L17 _public function_ `explicit FBindingFunctionCompiler(TNotNull<USceneStateTemplateData*> InTemplateData) : TemplateData(InTemplateData)`
- L23 _public prototype_ `void Compile();` — Compiles all the functions in all the bindings meant to have functions (Tasks, State Machines, Transitions)
- L26 _public prototype_ `FSceneStateRange GetFunctionRange(const FGuid& InTargetStructId) const;` — Gets the range of the compiled functions that are bound to the target struct id
- L30 _private prototype_ `void CompileFunctions(const FGuid& InTargetStructId);` — Compiles the functions found in all the bindings pointing towards target struct id
- L33 _private prototype_ `void CompileTaskFunctions();` — Compiles the functions for all the compiled tasks
- L36 _private prototype_ `void CompileStateMachineFunctions();` — Compiles the functions for all the compiled state machines
- L39 _private prototype_ `void CompileTransitionFunctions();` — Compiles the functions for all the compiled transitions
- L42 _private member_ `TObjectPtr<USceneStateTemplateData> TemplateData;` — The target to store the compiled functions
- L45 _private member_ `TMap<FGuid, FSceneStateRange> FunctionRangeMap;` — Map of the target struct id to its range of the functions in the generated class

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Compiler/SceneStateBlueprintCompilerContext.h` (Private)


#### class `UE::SceneState::Editor::FBlueprintCompilerContext`  
`class FBlueprintCompilerContext : public FKismetCompilerContext, public IStateMachineCompilerContext`  
_L16-54_
- inherits: `FKismetCompilerContext,IStateMachineCompilerContext`
- L19 _public prototype_ `explicit FBlueprintCompilerContext(USceneStateBlueprint* InBlueprint, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);`
- L22 _public prototype_ `const UClass* GetGeneratedClass() const;` — Returns the new generated class for this compilation
- L26 _private prototype_ `virtual void SpawnNewClass(const FString& InNewClassName) override;`
- L27 _private prototype_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* InClassToUse) override;`
- L28 _private prototype_ `virtual void EnsureProperGeneratedClass(UClass*& InOutTargetClass) override;`
- L29 _private prototype_ `virtual void SaveSubObjectsFromCleanAndSanitizeClass(FSubobjectCollection& OutSubObjectsToSave, UBlueprintGeneratedClass* InClassToClean) override;`
- L30 _private prototype_ `virtual void MergeUbergraphPagesIn(UEdGraph* InUbergraph) override;`
- L31 _private prototype_ `virtual void FinishCompilingClass(UClass* InClass) override;`
- L32 _private prototype_ `virtual void OnPostCDOCompiled(const UObject::FPostCDOCompiledContext& InContext) override;`
- L36 _private prototype_ `virtual USceneStateTemplateData* GetTemplateData() override;`
- L37 _private prototype_ `virtual FTransitionGraphCompileResult CompileTransitionGraph(USceneStateTransitionGraph* InTransitionGraph) override;`
- L41 _private prototype_ `void RecreateTemplateData();` — Recreates the template data owned by the generated class
- L44 _private prototype_ `void UpdateTaskIndices();` — Sets the Task Index and Parent State Index of each Task
- L47 _private prototype_ `void SetCompiledIndices();` — Sets the indices of each mapped type (State, StateMachine, Task) to their editor node for debugging
- L49 _private prototype_ `void CompileBindings();`
- L51 _private member_ `USceneStateGeneratedClass* NewGeneratedClass = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Compiler/SceneStateTransitionGraphCompiler.h` (Private)


#### class `UE::SceneState::Editor::FTransitionGraphCompiler`  
`class FTransitionGraphCompiler`  
_L25-87_
- desc: Compiler for the Transition K2 Graphs
- L28 _public prototype_ `explicit FTransitionGraphCompiler(FBlueprintCompilerContext& InCompilerContext, USceneStateTransitionGraph* InOriginalGraph);`
- L30 _public prototype_ `ETransitionGraphCompileReturnCode Compile();`
- L33 _public prototype_ `FName GetCustomEventName() const;` — Returns the name of the compiled event to call, if compilation succeeded
- L36 _public prototype_ `FName GetResultPropertyName() const;` — Returns the name of the compiled result property set by the compiled event, if compilation succeeded
- L44 _private prototype_ `bool CanSkipCompilation(bool& OutResult) const;` — Evaluates whether the transition graph can be skipped entirely if it always returns true or false @param OutResult the result that the transition will always evaluate to. Only correctly set if this function returns true @return true if the transition always evaluates to a fixed value
- L47 _private prototype_ `void CloneTransitionGraph();` — Copies the transition graph and moves the cloned nodes to the consolidated graph
- L50 _private prototype_ `void DiscoverResultNode();` — Finds the result node from the cloned graph (prior to the nodes moving to the consolidated graph)
- L53 _private prototype_ `void DiscoverParametersNodes();` — Finds all the parameters nodes from the cloned graph (prior to the nodes moving to the consolidated graph)
- L56 _private prototype_ `bool CreateTransitionResultProperty();` — Creates the transition result property to set for the custom event
- L59 _private prototype_ `void CreateTransitionEvaluationEvent();` — Creates and chains the nodes for evaluation (custom event, set result variable value , etc)
- L62 _private prototype_ `UK2Node_CustomEvent* CreateCustomEventNode();` — Creates the custom event node of the Evaluation Event
- L65 _private prototype_ `void LinkParametersNodes(UK2Node_CustomEvent* InCustomEvent);` — Links all the found parameter nodes to the pins (i.e. params) of the custom event
- L68 _private member_ `FBlueprintCompilerContext& Context;` — the owning blueprint compiler context
- L71 _private member_ `TObjectPtr<USceneStateTransitionGraph> OriginalGraph = nullptr;` — the original graph to clone
- L74 _private member_ `TObjectPtr<USceneStateTransitionGraph> ClonedGraph = nullptr;` — the copied graph
- L77 _private member_ `TObjectPtr<USceneStateTransitionResultNode> ResultNode = nullptr;` — the cloned result node discovered
- L80 _private member_ `FStructProperty* ResultProperty = nullptr;` — The compiled result property
- L83 _private member_ `FName CustomEventName;` — the name of the compiled custom event to call
- L86 _private member_ `TArray<TObjectPtr<USceneStateTransitionParametersNode>> ParametersNodes;` — the cloned parameter nodes discovered

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SceneState` (scope `UE`)
- L21 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugControls/SSceneStateDebugControls.h` (Private)


#### class `UE::SceneState::Editor::SDebugControls`  
`class SDebugControls : public SCompoundWidget`  
_L32-88_
- inherits: `SCompoundWidget`
- desc: Widget for displaying the controls for the debugged scene state object
- L35 _public function_ `SLATE_BEGIN_ARGS(SDebugControls)`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor);`
- L43 _public prototype_ `void Refresh();` — Updates to the latest blueprint's object being debugged
- L46 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L51 _private prototype_ `TSharedRef<SWidget> CreateContentWidget();` — Creates the widget to display when the tool is available
- L54 _private prototype_ `TSharedRef<SWidget> CreatePlaceholderWidget();` — Creates the widget to display when the tool is not available
- L57 _private prototype_ `TSharedRef<IDetailsView> CreateDebugControlsDetailsView(const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor) const;` — Creates a new details view for debug controls
- L60 _private prototype_ `TSharedRef<IDetailsView> CreateDebuggedObjectDetailsView(const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor) const;` — Creates a new details view for debugged object
- L63 _private prototype_ `void OnBlueprintDebugObjectChanged(const Graph::FBlueprintDebugObjectChange& InChange);` — Called when the blueprint debug object has changed
- L66 _private member_ `TSharedPtr<IDetailsView> DebugControlsDetailsView;` — Details view of the debug controls object
- L69 _private member_ `TSharedPtr<IDetailsView> DebuggedObjectDetailsView;` — Details view of the debugged object
- L72 _private member_ `TWeakPtr<FSceneStateBlueprintEditor> BlueprintEditorWeak;` — The blueprint editor owning this widget
- L75 _private member_ `TSharedPtr<SBorder> WidgetContainer;` — Container for the widget with the actual content
- L78 _private member_ `TSharedPtr<SWidget> ContentWidget;` — Debug control tools content widget when the tool is available
- L81 _private member_ `TSharedPtr<SWidget> PlaceholderWidget;` — Placeholder to use when the debug control tool is not available
- L84 _private member_ `TSharedPtr<FDebugControlsTool> DebugControlsTool;` — Class that handles the logic of this widget
- L87 _private member_ `FDelegateHandle OnBlueprintDebugObjectChangedHandle;` — Handle to the blueprint debug object changed delegate

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SceneState` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L22 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace SceneState` (scope `UE`)
- L28 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugControls/SceneStateDebugControlsObject.h` (Private)


#### class `USceneStateDebugControlsObject`  
`class USceneStateDebugControlsObject : public UObject`  
_L13-21_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Temporary object used for debug controls
- L20 _public member_ `TArray<FSceneStateEventTemplate> Events;` — `UPROPERTY(EditAnywhere, Category="Event")` — Debug events to push

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugControls/SceneStateDebugControlsObjectDetails.h` (Private)


#### class `UE::SceneState::Editor::FDebugControlsObjectDetails`  
`class FDebugControlsObjectDetails : public IDetailCustomization`  
_L19-35_
- inherits: `IDetailCustomization`
- desc: Details customization for USceneStateDebugControlsObject
- L22 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L32 _private prototype_ `void CustomizeEventDetails(IDetailLayoutBuilder& InDetailBuilder);`
- L34 _private member_ `TArray<TWeakObjectPtr<USceneStateDebugControlsObject>> DebugControls;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugControls/SceneStateDebugControlsTabFactory.h` (Private)


#### class `UE::SceneState::Editor::FDebugControlsTabFactory`  
`class FDebugControlsTabFactory : public FTabFactory`  
_L10-20_
- inherits: `FTabFactory`
- L13 _public member_ `static const FName TabId;`
- L15 _public prototype_ `explicit FDebugControlsTabFactory(const TSharedRef<FSceneStateBlueprintEditor>& InEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugControls/SceneStateDebugControlsTool.h` (Private)


#### class `UE::SceneState::Editor::FDebugControlsTool`  
`class FDebugControlsTool : public TSharedFromThis<FDebugControlsTool>`  
_L31-83_
- inherits: `TSharedFromThis<FDebugControlsTool>`
- desc: Logic class for the debug controls widget
- L34 _public prototype_ `explicit FDebugControlsTool(const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor);`
- L36 _public function_ `const TSharedRef<FUICommandList>& GetCommandList() const`
- L42 _public prototype_ `bool IsAvailable() const;` — Returns whether the tool is ready to be used, by checking if the currently debugged object is active
- L45 _public prototype_ `void Initialize();` — Creates the debug controls objects and binds the command actions
- L48 _public prototype_ `void Tick(float InDeltaSeconds);` — Called to update the active debug executor if any
- L51 _public prototype_ `UObject* GetDebugControlsObject() const;` — Gets the debug controls object to show in details view
- L54 _public prototype_ `USceneStateObject* GetDebuggedObject() const;` — Retrieves the currently debugged object
- L58 _private prototype_ `const USceneStateMachineNode* GetSingleSelectedNode() const;` — Gets the single selected state machine node, or null if nothing is selected or multiple items are selected
- L61 _private prototype_ `void BindCommands();` — Adds the debug controls commands to the command list
- L64 _private prototype_ `bool CanDebugRunSelection();` — Whether there's any selected elements in the graph that can be debug executed. Only supports 1 selected element at a time
- L67 _private prototype_ `void DebugRunSelection();` — Runs the selected element in standalone
- L70 _private prototype_ `void PushEvents();` — Push the events in the debug controls object
- L73 _private member_ `TWeakPtr<FSceneStateBlueprintEditor> BlueprintEditorWeak;` — Blueprint editor owning this tool
- L76 _private member_ `TSharedRef<FUICommandList> ToolCommandList;` — Command list holding all the debug controls commands
- L79 _private member_ `TSharedPtr<FDebugExecutor> DebugExecutor;` — Current active executor
- L82 _private member_ `TStrongObjectPtr<USceneStateDebugControlsObject> DebugControlsObject;` — Object to add additional controls while also supporting transaction

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L21 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace SceneState` (scope `UE`)
- L27 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugControls/SceneStateDebugControlsToolbar.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L13 _prototype_ `TSharedRef<SWidget> CreateDebugControlsToolbar(const TSharedRef<FUICommandList>& InCommandList);` (scope `UE::SceneState::Editor`) — Creates the toolbar widget for the debug controls tab

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugExecutors/SceneStateDebugExecutor.h` (Private)


#### class `UE::SceneState::Editor::FDebugExecutor`  
`class FDebugExecutor : public FGCObject, public TSharedFromThis<FDebugExecutor>`  
_L16-64_
- inherits: `FGCObject,TSharedFromThis<FDebugExecutor>`
- desc: Base class to execute
- L19 _public prototype_ `explicit FDebugExecutor(USceneStateObject* InRootObject, const USceneStateMachineNode* InNode);`
- L24 _public prototype_ `void Start();` — Called to start the executor
- L27 _public prototype_ `void Tick(float InDeltaSeconds);` — Called every tick to update the executor
- L30 _public prototype_ `void Exit();` — Called to exit the executor
- L33 _protected function_ `FObjectKey GetNodeKey() const`
- L39 _protected function_ `virtual void OnStart(const FSceneStateExecutionContext& InExecutionContext)` — Called to start the executor
- L44 _protected function_ `virtual void OnTick(const FSceneStateExecutionContext& InExecutionContext, float InDeltaSeconds)` — Called every tick to update the executor
- L49 _protected function_ `virtual void OnExit(const FSceneStateExecutionContext& InExecutionContext)` — Called to exit the executor
- L54 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L55 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L60 _private member_ `FObjectKey NodeKey;` — The object key of the state machine node. Used to get the corresponding element in the generated class
- L63 _private member_ `FSceneStateExecutionContext ExecutionContext;` — Execution context to use

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugExecutors/SceneStateDebugStateExecutor.h` (Private)


#### class `UE::SceneState::Editor::FDebugStateExecutor`  
`class FDebugStateExecutor : public FDebugExecutor`  
_L13-34_
- inherits: `FDebugExecutor`
- desc: Debug executes the state corresponding to a given state node
- L16 _public function_ `explicit FDebugStateExecutor(USceneStateObject* InRootObject, const USceneStateMachineNode* InNode) : FDebugExecutor(InRootObject, InNode)`
- L23 _protected prototype_ `const FSceneState* GetState(const FSceneStateExecutionContext& InExecutionContext) const;` — Retrieves the state corresponding to the stored state node
- L26 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InExecutionContext) override;`
- L27 _protected prototype_ `virtual void OnTick(const FSceneStateExecutionContext& InExecutionContext, float InDeltaSeconds) override;`
- L28 _protected prototype_ `virtual void OnExit(const FSceneStateExecutionContext& InExecutionContext) override;`
- L33 _private prototype_ `void ConditionallyExit(const FSceneStateExecutionContext& InExecutionContext, const FSceneState& InState);` — Checks whether the state has all pending tasks completed and calls exit if so

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugExecutors/SceneStateDebugTaskExecutor.h` (Private)


#### class `UE::SceneState::Editor::FDebugTaskExecutor`  
`class FDebugTaskExecutor : public FDebugExecutor`  
_L11-38_
- inherits: `FDebugExecutor`
- desc: Debug executes the task corresponding to a given task node
- L14 _public function_ `explicit FDebugTaskExecutor(USceneStateObject* InRootObject, const USceneStateMachineNode* InTaskNode) : FDebugExecutor(InRootObject, InTaskNode)`
- L21 _protected prototype_ `const FSceneStateTask* GetTask(const FSceneStateExecutionContext& InExecutionContext) const;` — Retrieves the task corresponding to the stored task node
- L24 _protected prototype_ `const FSceneState* GetState(TNotNull<const USceneStateTemplateData*> InTemplateData) const;` — Retrieves the state corresponding to the stored state node
- L27 _protected prototype_ `void Setup(const FSceneStateExecutionContext& InExecutionContext, const FSceneStateTask& InTask);` — Called to allocate the task instance
- L30 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InExecutionContext) override;`
- L31 _protected prototype_ `virtual void OnTick(const FSceneStateExecutionContext& InExecutionContext, float InDeltaSeconds) override;`
- L32 _protected prototype_ `virtual void OnExit(const FSceneStateExecutionContext& InExecutionContext) override;`
- L37 _private prototype_ `void ConditionallyExit(const FSceneStateTask& InTask, const FSceneStateExecutionContext& InExecutionContext);` — Checks whether the task completed and calls exit if so

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugView/SSceneStateDebugView.h` (Private)


#### class `UE::SceneState::Editor::SDebugView`  
`class SDebugView : public SCompoundWidget`  
_L28-62_
- inherits: `SCompoundWidget`
- desc: Widget for displaying the currently debugged object view
- L31 _public function_ `SLATE_BEGIN_ARGS(SDebugView)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor);`
- L39 _public prototype_ `void Refresh();` — Updates to the latest blueprint's object being debugged
- L43 _private prototype_ `TSharedPtr<SWidget> GetViewWidget() const;` — Gets the widget to display
- L46 _private prototype_ `void OnBlueprintDebugObjectChanged(const Graph::FBlueprintDebugObjectChange& InChange);` — Called when the blueprint debug object has changed
- L49 _private prototype_ `USceneStateObject* GetDebuggedObject() const;` — Retrieves the currently debugged object
- L52 _private member_ `TWeakPtr<FSceneStateBlueprintEditor> BlueprintEditorWeak;` — The blueprint editor owning this widget
- L55 _private member_ `TSharedPtr<SWidget> PlaceholderWidget;` — The placeholder widget to use when no valid view widget is found
- L58 _private member_ `TSharedPtr<SBorder> ViewContainer;` — Widget containing the view
- L61 _private member_ `FDelegateHandle OnBlueprintDebugObjectChangedHandle;` — Handle to the blueprint debug object changed delegate

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L18 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SceneState` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DebugView/SceneStateDebugViewTabFactory.h` (Private)


#### class `UE::SceneState::Editor::FDebugViewTabFactory`  
`class FDebugViewTabFactory : public FTabFactory`  
_L10-20_
- inherits: `FTabFactory`
- L13 _public member_ `static const FName TabId;`
- L15 _public prototype_ `explicit FDebugViewTabFactory(const TSharedRef<FSceneStateBlueprintEditor>& InEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateBindingFunctionCustomization.h` (Private)


#### class `UE::SceneState::Editor::FBindingFunctionCustomization`  
`class FBindingFunctionCustomization : public IPropertyTypeCustomization`  
_L11-23_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for FSceneStateBindingFunction
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateBindingsChildrenCustomization.h` (Private)


#### class `UE::SceneState::Editor::FBindingFunctionStructProvider`  
`class FBindingFunctionStructProvider : public IStructureDataProvider`  
_L16-36_
- inherits: `IStructureDataProvider`
- desc: Provides the binding function data view for a given target path
- L19 _public prototype_ `explicit FBindingFunctionStructProvider(ISceneStateBindingCollectionOwner* InBindingsOwnerChecked, FPropertyBindingPath InTargetPath);`
- L22 _public prototype_ `virtual bool IsValid() const override;`
- L23 _public prototype_ `virtual const UStruct* GetBaseStructure() const override;`
- L24 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* InExpectedBaseStructure) const override;`
- L28 _public prototype_ `static bool HasValidBindingFunction(ISceneStateBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath);` — Returns whether there is a valid binding function at the given target path
- L32 _private prototype_ `static FStructView GetBindingFunctionView(ISceneStateBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath);` — Retrieves the binding function at the given target path if any
- L34 _private member_ `TWeakInterfacePtr<ISceneStateBindingCollectionOwner> BindingsOwnerWeak;`
- L35 _private member_ `FPropertyBindingPath TargetPath;`

#### class `UE::SceneState::Editor::FBindingsChildrenCustomization`  
`class FBindingsChildrenCustomization : public IDetailPropertyChildrenCustomizationHandler`  
_L39-46_
- inherits: `IDetailPropertyChildrenCustomizationHandler`
- desc: Overrides bound property's children composition.
- L43 _public prototype_ `virtual bool ShouldCustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle) override;`
- L44 _public prototype_ `virtual void CustomizeChildren(IDetailChildrenBuilder& InChildrenBuilder, TSharedPtr<IPropertyHandle> InPropertyHandle) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateBlueprintPropertyReferenceCustomization.h` (Private)


#### class `USceneStatePropertyReferenceSchema`  
`class USceneStatePropertyReferenceSchema : public UEdGraphSchema_K2`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema_K2`
- desc: Property Reference Schema to allow customizing the requirements (e.g. supported containers).
- L19 _public prototype_ `virtual bool SupportsPinTypeContainer(TWeakPtr<const FEdGraphSchemaAction> InSchemaAction, const FEdGraphPinType& InPinType, const EPinContainerType& InContainerType) const override;`

#### class `UE::SceneState::Editor::FBlueprintPropertyReferenceCustomization`  
`class FBlueprintPropertyReferenceCustomization : public IPropertyTypeCustomization`  
_L27-48_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for FSceneStateBlueprintPropertyReference
- L30 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L36 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L37 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L41 _private prototype_ `bool GetPropertyReference(FSceneStateBlueprintPropertyReference& OutPropertyReference) const;`
- L43 _private prototype_ `FEdGraphPinType GetPinType() const;`
- L45 _private prototype_ `void OnPinTypeChanged(const FEdGraphPinType& InPinType) const;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SceneState` (scope `UE`)
- L23 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateBlueprintableTaskInstanceCustomization.h` (Private)


#### class `UE::SceneState::Editor::FBlueprintableTaskInstanceCustomization`  
`class FBlueprintableTaskInstanceCustomization : public IPropertyTypeCustomization`  
_L10-25_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L24 _protected prototype_ `void CustomizeTask(const TSharedRef<IPropertyHandle>& InTaskHandle, IDetailChildrenBuilder& InChildBuilder);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateCachedBindingData.h` (Private)


#### struct `UE::SceneState::Editor::FSceneStateCachedBindingData`  
`struct FSceneStateCachedBindingData : UE::PropertyBinding::FCachedBindingData, TSharedFromThis<FSceneStateCachedBindingData>`  
_L22-46_
- inherits: `UE::PropertyBinding::FCachedBindingData,TSharedFromThis<FSceneStateCachedBindingData>`
- L24 _public typedef_ `using Super = UE::PropertyBinding::FCachedBindingData;`
- L28 _public prototype_ `const FProperty* GetProperty() const;` — Gets the property from the property handle if valid
- L31 _public prototype_ `virtual void UpdatePropertyReferenceTooltip(const FProperty& InProperty, FTextBuilder& InOutTextBuilder) const override;`
- L32 _public prototype_ `virtual FPinInfo GetPinInfoForProperty(TNotNull<const FProperty*> InProperty, FPropertyBindingDataView InTargetDataView) const override;`
- L33 _public prototype_ `virtual bool IsPropertyReference(const FProperty& InProperty) override;`
- L34 _public prototype_ `virtual void UpdateSourcePropertyPath(TConstStructView<FPropertyBindingBindableStructDescriptor> InDescriptor, const FPropertyBindingPath& InSourcePath, FString& OutString);`
- L35 _public prototype_ `virtual bool CanBindToContextStructInternal(const UStruct* InStruct, const int32 InStructIndex) override;`
- L36 _public prototype_ `virtual bool CanAcceptPropertyOrChildrenInternal(const FProperty& InSourceProperty, TConstArrayView<FBindingChainElement, int> InBindingChain) override;`
- L37 _public prototype_ `virtual void GetSourceDataViewForNewBinding(TNotNull<IPropertyBindingBindingCollectionOwner*> InBindingsOwner, TConstStructView<FPropertyBindingBindableStructDescriptor> InDescriptor, FPropertyBindingDataView& OutSourceDataView) override;`
- L38 _public prototype_ `virtual bool AddBindingInternal(TConstStructView<FPropertyBindingBindableStructDescriptor> InDescriptor, FPropertyBindingPath& InOutSourcePath, const FPropertyBindingPath& InTargetPath) override;`
- L39 _public prototype_ `virtual void AddPropertyInfoOverride(const FProperty& InProperty, TArray<TSharedPtr<const UE::PropertyBinding::FPropertyInfoOverride>>& OutPropertyInfoOverrides) const override;`
- L40 _public prototype_ `virtual bool DeterminePropertiesCompatibilityInternal(const FProperty* InSourceProperty,const FProperty* InTargetProperty,const void* InSourcePropertyValue,const void* InTargetPropertyValue,bool& bOutAreCompatible) const override;`
- L41 _public prototype_ `virtual bool GetPropertyFunctionText(FConstStructView InPropertyFunctionStructView, FText& OutText) const;`
- L42 _public prototype_ `virtual bool GetPropertyFunctionTooltipText(FConstStructView InPropertyFunctionStructView, FText& OutText) const;`
- L43 _public prototype_ `virtual bool GetPropertyFunctionIconColor(FConstStructView InPropertyFunctionStructView, FLinearColor& OutColor) const;`
- L44 _public prototype_ `virtual bool GetPropertyFunctionImage(FConstStructView InPropertyFunctionStructView, const FSlateBrush*& OutImage) const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L10 _prototype_ `bool IsOutputProperty(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` (scope `UE::SceneState::Editor`) — Determines whether the given property handle is deemed as an 'output' for a function
- L13 _prototype_ `bool IsOutputProperty(const FProperty* InProperty);` (scope `UE::SceneState::Editor`) — Determines whether the given property is deemed as an 'output' for a function
- L16 _prototype_ `const FProperty* FindSingleOutputProperty(const UStruct* InStruct);` (scope `UE::SceneState::Editor`) — Returns the single property deemed as 'output' for a function. Returns null if none or multiple found.
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SceneState` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateInstancedStructDataProvider.h` (Private)


#### class `UE::SceneState::Editor::FInstancedStructDataProvider`  
`class FInstancedStructDataProvider : public IStructureDataProvider`  
_L16-39_
- inherits: `IStructureDataProvider`
- desc: Structure Data Provider for Instanced Struct properties
- L19 _public prototype_ `FInstancedStructDataProvider() = default;`
- L21 _public prototype_ `explicit FInstancedStructDataProvider(const TSharedPtr<IPropertyHandle>& InInstancedStructHandle);`
- L23 _public prototype_ `virtual ~FInstancedStructDataProvider() override = default;`
- L26 _public prototype_ `virtual bool IsValid() const override;`
- L27 _public prototype_ `virtual const UStruct* GetBaseStructure() const override;`
- L28 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* InExpectedBaseStructure) const override;`
- L29 _public prototype_ `virtual bool IsPropertyIndirection() const override;`
- L30 _public prototype_ `virtual uint8* GetValueBaseAddress(uint8* InParentValueAddress, const UStruct* InExpectedBaseStructure) const override;`
- L35 _protected prototype_ `void EnumerateInstances(TFunctionRef<bool(const UScriptStruct*, uint8*, UPackage*)> InFunctor) const;` — Calls the given functor for every instanced struct instance that this handle manages
- L38 _protected member_ `TSharedPtr<IPropertyHandle> InstancedStructHandle;` — Handle to the Instanced Struct property

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateMachineGraphCustomization.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineGraphCustomization`  
`class FStateMachineGraphCustomization : public IDetailCustomization`  
_L13-24_
- inherits: `IDetailCustomization`
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateMachineStateNodeCustomization.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineStateNodeCustomization`  
`class FStateMachineStateNodeCustomization : public IDetailCustomization`  
_L10-21_
- inherits: `IDetailCustomization`
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateMachineTaskInstanceCustomization.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineTaskInstanceCustomization`  
`class FStateMachineTaskInstanceCustomization : public IPropertyTypeCustomization`  
_L10-22_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateMachineTaskNodeCustomization.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineTaskNodeCustomization`  
`class FStateMachineTaskNodeCustomization : public IDetailCustomization`  
_L10-21_
- inherits: `IDetailCustomization`
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateMachineTransitionNodeCustomization.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineTransitionNodeCustomization`  
`class FStateMachineTransitionNodeCustomization : public IDetailCustomization`  
_L10-21_
- inherits: `IDetailCustomization`
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStateParameterDetails.h` (Private)


#### class `UE::SceneState::Editor::FParameterDetails`  
`class FParameterDetails : public FPropertyBagInstanceDataDetails`  
_L13-29_
- inherits: `FPropertyBagInstanceDataDetails`
- L16 _public prototype_ `static TSharedRef<SWidget> BuildHeader(IDetailLayoutBuilder& InDetailBuilder, const TSharedRef<IPropertyHandle>& InParametersHandle);`
- L18 _public prototype_ `explicit FParameterDetails(const TSharedRef<IPropertyHandle>& InStructProperty , const TSharedRef<IPropertyUtilities>& InPropUtils , const FGuid& InParametersId , bool bInFixedLayout);`
- L24 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& InChildRow) override;`
- L28 _private member_ `FGuid ParametersId;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStatePlayerTaskInstanceCustomization.h` (Private)


#### class `UE::SceneState::Editor::FPlayerTaskInstanceCustomization`  
`class FPlayerTaskInstanceCustomization : public IPropertyTypeCustomization`  
_L10-25_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L24 _protected prototype_ `void CustomizePlayer(const TSharedRef<IPropertyHandle>& InPlayerHandle, IDetailChildrenBuilder& InChildBuilder);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/SceneStatePropertyBindingExtension.h` (Private)


#### class `UE::SceneState::Editor::FBindingExtension`  
`class FBindingExtension : public FPropertyBindingExtension`  
_L10-25_
- inherits: `FPropertyBindingExtension`
- L14 _public prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L18 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& InPropertyHandle) const override;`
- L19 _public prototype_ `virtual TSharedPtr<UE::PropertyBinding::FCachedBindingData> CreateCachedBindingData(IPropertyBindingBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath, const TSharedPtr<IPropertyHandle>& InPropertyHandle, TConstArrayView<TInstancedStruct<FPropertyBindingBindableStructDescriptor>> InAccessibleStructs) const override;`
- L20 _public prototype_ `virtual bool GetPromotionToParameterOverrideInternal(const FProperty& InProperty, bool& bOutOverride) const override;`
- L21 _public prototype_ `virtual void UpdateContextStruct(TConstStructView<FPropertyBindingBindableStructDescriptor> InStructDesc, FBindingContextStruct& InOutContextStruct, TMap<FString, FText>& InOutSectionNames) const override;`
- L22 _public prototype_ `virtual bool CanBindToProperty(const FPropertyBindingPath& InTargetPath, const IPropertyHandle& InPropertyHandle) const override;`
- L23 _public prototype_ `virtual bool CanBindToArrayElements() const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/DetailsView/Widgets/SSceneStateMachinePicker.h` (Private)


#### struct `UE::SceneState::Editor::FStateMachinePickerOption`  
`struct FStateMachinePickerOption`  
_L17-22_
- L19 _public member_ `FName Name;`
- L20 _public member_ `FGuid Id;`
- L21 _public member_ `TWeakObjectPtr<USceneStateMachineGraph> GraphWeak;`

#### class `UE::SceneState::Editor::SStateMachinePicker`  
`class SStateMachinePicker : public SCompoundWidget`  
_L28-64_
- inherits: `SCompoundWidget`
- desc: Widget that shows the available State Machine Graphs that are set to 'Manual' as names, but underneath handles them / saves these as Guids
- L31 _public function_ `SLATE_BEGIN_ARGS(SStateMachinePicker)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InStateMachineIdHandle, const TSharedRef<IPropertyHandle>& InParametersHandle);`
- L39 _private prototype_ `void OnParametersChanged(USceneStateMachineGraph* InGraph);`
- L41 _private prototype_ `FText GetStateMachineName() const;`
- L43 _private prototype_ `void RefreshOptions();`
- L45 _private prototype_ `void RefreshParameters();`
- L47 _private prototype_ `void ForEachInstancedPropertyBag(TFunctionRef<bool(FInstancedPropertyBag&)> InFunctor);`
- L49 _private prototype_ `TSharedRef<SWidget> GenerateOptionWidget(TSharedRef<FStateMachinePickerOption> InOption);`
- L51 _private prototype_ `void OnOptionSelectionChanged(TSharedPtr<FStateMachinePickerOption> InSelectedOption, ESelectInfo::Type InSelectInfo);`
- L53 _private member_ `TSharedPtr<IPropertyHandle> StateMachineIdHandle;`
- L54 _private member_ `TSharedPtr<IPropertyHandle> ParametersHandle;`
- L56 _private member_ `TSharedPtr<SComboBox<TSharedRef<FStateMachinePickerOption>>> Picker;`
- L57 _private member_ `TArray<TSharedRef<FStateMachinePickerOption>> PickerOptions;`
- L59 _private member_ `TSharedPtr<FStateMachinePickerOption> SelectedOption;`
- L60 _private member_ `FDelegateHandle OnParametersChangedHandle;`
- L63 _private member_ `TSet<FGuid> StateMachineIdsToIgnore;` — State machine ids that this picker should not display as options

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SceneState` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Menus/SceneStateMachineAddMenu.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineAddMenu`  
`class FStateMachineAddMenu : public TSharedFromThis<FStateMachineAddMenu>`  
_L14-30_
- inherits: `TSharedFromThis<FStateMachineAddMenu>`
- L17 _public prototype_ `FStateMachineAddMenu();`
- L19 _public prototype_ `void BindCommands(const TSharedRef<FUICommandList>& InCommandList);`
- L21 _public function_ `static FName GetMenuName()`
- L26 _public prototype_ `TSharedRef<SWidget> GenerateWidget();`
- L29 _private member_ `TSharedRef<FUICommandList> CommandList;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Menus/SceneStateMachineContextMenu.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineContextMenu`  
`class FStateMachineContextMenu : public TSharedFromThis<FStateMachineContextMenu>`  
_L27-55_
- inherits: `TSharedFromThis<FStateMachineContextMenu>`
- L30 _public prototype_ `explicit FStateMachineContextMenu(const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor, const TSharedRef<SGraphActionMenu>& InGraphActionMenu);`
- L32 _public prototype_ `void BindCommands(const TSharedRef<FUICommandList>& InCommandList);`
- L34 _public function_ `static FName GetMenuName()`
- L39 _public prototype_ `TSharedRef<SWidget> GenerateWidget();`
- L42 _private prototype_ `TSharedPtr<Graph::FBlueprintAction_Graph> GetSelectedGraphAction() const;`
- L44 _private prototype_ `bool CanRename() const;`
- L45 _private prototype_ `void Rename();`
- L47 _private prototype_ `bool CanDelete() const;`
- L48 _private prototype_ `void Delete();`
- L50 _private member_ `TWeakPtr<FSceneStateBlueprintEditor> BlueprintEditorWeak;`
- L52 _private member_ `TWeakPtr<SGraphActionMenu> GraphActionMenuWeak;`
- L54 _private member_ `TSharedRef<FUICommandList> CommandList;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L18 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SceneState` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateBlueprintEditor.h` (Private)


#### class `UE::SceneState::Editor::FSceneStateBlueprintEditor`  
`class FSceneStateBlueprintEditor : public FBlueprintEditor`  
_L28-78_
- inherits: `FBlueprintEditor`
- desc: Blueprint Editor for the Scene State Object
- L31 _public typedef_ `using Super = FBlueprintEditor;`
- L33 _public member_ `static const FLazyName SelectionState_StateMachine;`
- L35 _public prototype_ `FSceneStateBlueprintEditor();`
- L38 _public prototype_ `void Init(USceneStateBlueprint* InBlueprint, const FAssetOpenArgs& InOpenArgs);`
- L40 _public prototype_ `void AddStateMachine();`
- L42 _public prototype_ `TSharedRef<SWidget> CreateStateMachineMenu();`
- L44 _public prototype_ `void AddBlueprintExtensions(USceneStateBlueprint& InBlueprint);`
- L47 _public prototype_ `void OnDebugObjectChanged(const Graph::FBlueprintDebugObjectChange& InDebugObjectChange);` — Called when the debug object has changed
- L50 _public prototype_ `virtual void RefreshEditors(ERefreshBlueprintEditorReason::Type InReason) override;`
- L51 _public prototype_ `virtual void RefreshMyBlueprint();`
- L52 _public prototype_ `virtual void JumpToHyperlink(const UObject* InObjectReference, bool bInRequestRename) override;`
- L57 _public prototype_ `virtual bool InEditingMode() const;`
- L58 _public prototype_ `virtual void CreateDefaultTabContents(const TArray<UBlueprint*>& InBlueprints) override;`
- L59 _public prototype_ `virtual void CreateDefaultCommands() override;`
- L60 _public prototype_ `virtual void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bInShouldOpenInDefaultsMode, bool bInNewlyCreated) override;`
- L61 _public prototype_ `virtual bool IsInAScriptingMode() const override;`
- L62 _public prototype_ `virtual void ClearSelectionStateFor(FName InSelectionOwner);`
- L66 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L67 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L72 _private member_ `TSharedPtr<UE::SceneState::FDebugger> Debugger;` — The current active debugger, or null if no debugger is attached
- L74 _private member_ `TSharedPtr<SStateMachineMenu> StateMachineMenu;`
- L77 _private member_ `FDelegateHandle OnDebugObjectChangedHandle;` — Handle to the delegate called when the debug object has changed

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L18 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SceneState` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateBlueprintEditorCommands.h` (Private)


#### class `UE::SceneState::Editor::FBlueprintEditorCommands`  
`class FBlueprintEditorCommands : public TCommands<FBlueprintEditorCommands>`  
_L10-23_
- inherits: `TCommands<FBlueprintEditorCommands>`
- L13 _public prototype_ `FBlueprintEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> AddStateMachine;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> DebugPushEvent;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> DebugRunSelection;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateBlueprintEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateBlueprintEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateBlueprintEditor, Log, All);`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateBlueprintEditorModule.h` (Private)


#### class `UE::SceneState::Editor::FBlueprintEditorModule`  
`class FBlueprintEditorModule : public IBlueprintEditorModule`  
_L11-47_
- inherits: `IBlueprintEditorModule`
- L14 _public prototype_ `static const FBlueprintEditorModule& GetInternal();`
- L16 _public function_ `const FContextEditorRegistry& GetContextEditorRegistry() const`
- L23 _protected prototype_ `virtual void StartupModule() override;`
- L24 _protected prototype_ `virtual void ShutdownModule() override;`
- L28 _protected prototype_ `virtual void RegisterCompiler(TSubclassOf<USceneStateBlueprint> InBlueprintClass) override;`
- L29 _protected prototype_ `virtual void RegisterContextEditor(const TSharedPtr<IContextEditor>& InContextEditor) override;`
- L30 _protected prototype_ `virtual void UnregisterContextEditor(const TSharedPtr<IContextEditor>& InContextEditor) override;`
- L33 _protected prototype_ `void RegisterCompiler();`
- L35 _protected prototype_ `void RegisterDefaultEvents();`
- L36 _protected prototype_ `void UnregisterDefaultEvents();`
- L38 _protected prototype_ `void RegisterDetailCustomizations();`
- L39 _protected prototype_ `void UnregisterDetailCustomizations();`
- L41 _protected member_ `FContextEditorRegistry ContextEditorRegistry;`
- L43 _protected member_ `TArray<FName> CustomizedTypes;`
- L44 _protected member_ `TArray<FName> CustomizedClasses;`
- L46 _protected member_ `FDelegateHandle PostEngineInitHandle;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SceneState` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateBlueprintEditorStyle.h` (Private)


#### class `UE::SceneState::Editor::FBlueprintEditorStyle`  
`class FBlueprintEditorStyle : public FSlateStyleSet`  
_L14-27_
- inherits: `FSlateStyleSet`
- L17 _public function_ `static FBlueprintEditorStyle& Get()`
- L23 _public prototype_ `FBlueprintEditorStyle();`
- L26 _public prototype_ `FSlateIcon GetGraphSchemaIcon(TSubclassOf<UEdGraphSchema> InSchemaClass) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateContextEditorRegistry.h` (Private)


#### class `UE::SceneState::Editor::FContextEditorRegistry`  
`class FContextEditorRegistry`  
_L17-31_
- desc: Holds all the registered context editors
- L21 _public prototype_ `void RegisterContextEditor(const TSharedPtr<IContextEditor>& InContextEditor);` — Registers the given context editor if valid
- L24 _public prototype_ `void UnregisterContextEditor(const TSharedPtr<IContextEditor>& InContextEditor);` — Unregisters the given context editor
- L27 _public prototype_ `TSharedPtr<IContextEditor> FindContextEditor(const UObject* InContextObject) const;` — Finds the most relevant context editor to the given context object
- L30 _private member_ `TArray<TSharedPtr<IContextEditor>> ContextEditors;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SceneState` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateTaskBlueprintEditor.h` (Private)


#### class `UE::SceneState::Editor::FSceneStateTaskBlueprintEditor`  
`class FSceneStateTaskBlueprintEditor : public FBlueprintEditor`  
_L12-24_
- inherits: `FBlueprintEditor`
- L15 _public typedef_ `using Super = FBlueprintEditor;`
- L17 _public prototype_ `void Init(USceneStateTaskBlueprint* InBlueprint, const FAssetOpenArgs& InOpenArgs);`
- L21 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L22 _protected prototype_ `virtual FText GetBaseToolkitName() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/SceneStateTaskBlueprintFactory.h` (Private)


#### class `USceneStateTaskBlueprintFactory`  
`class USceneStateTaskBlueprintFactory : public UFactory`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L17 _public prototype_ `USceneStateTaskBlueprintFactory();`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L22 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn, FName InCallingContext) override;`
- L27 _public member_ `TSubclassOf<USceneStateBlueprintableTask> ParentClass;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/TabFactories/SceneStateStateMachineTabFactory.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineTabFactory`  
`class FStateMachineTabFactory : public FTabFactory`  
_L10-20_
- inherits: `FTabFactory`
- L13 _public member_ `static const FName TabId;`
- L15 _public prototype_ `explicit FStateMachineTabFactory(const TSharedRef<FSceneStateBlueprintEditor>& InEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/TabFactories/SceneStateTabFactory.h` (Private)


#### class `UE::SceneState::Editor::FTabFactory`  
`class FTabFactory : public FWorkflowTabFactory`  
_L16-22_
- inherits: `FWorkflowTabFactory`
- desc: Base class for all Tab Factories in Scene State Blueprint Editor
- L19 _public prototype_ `explicit FTabFactory(FName InTabId, const TSharedRef<FSceneStateBlueprintEditor>& InEditor);`
- L21 _public prototype_ `TSharedPtr<FSceneStateBlueprintEditor> GetEditor() const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Tasks/SceneStateBlueprintableTaskDesc.h` (Private)


#### struct `FSceneStateBlueprintableTaskDesc`  
`struct FSceneStateBlueprintableTaskDesc : public FSceneStateTaskDesc`  
_L10-22_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskDesc`
- desc: Task Desc for FSceneStateBlueprintableTaskWrapper
- L14 _public prototype_ `FSceneStateBlueprintableTaskDesc();`
- L18 _protected prototype_ `virtual bool OnGetDisplayName(const FSceneStateTaskDescContext& InContext, FText& OutDisplayName) const override;`
- L19 _protected prototype_ `virtual bool OnGetTooltip(const FSceneStateTaskDescContext& InContext, FText& OutDescription) const override;`
- L20 _protected prototype_ `virtual bool OnGetJumpTarget(const FSceneStateTaskDescContext& InContext, UObject*& OutJumpTarget) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Tasks/SceneStateMachineTaskDesc.h` (Private)


#### struct `FSceneStateMachineTaskDesc`  
`struct FSceneStateMachineTaskDesc : public FSceneStateTaskDesc`  
_L10-21_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskDesc`
- desc: Task Desc for FSceneStateMachineTask
- L14 _public prototype_ `FSceneStateMachineTaskDesc();`
- L18 _protected prototype_ `virtual bool OnGetJumpTarget(const FSceneStateTaskDescContext& InContext, UObject*& OutJumpTarget) const override;`
- L19 _protected prototype_ `virtual void OnStructIdsChanged(const FSceneStateTaskDescMutableContext& InContext, const UE::SceneState::FStructIdChange& InChange) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Widgets/SSceneStateBlueprintPaletteItem.h` (Private)


#### class `UE::SceneState::Editor::SBlueprintPaletteItem`  
`class SBlueprintPaletteItem : public SGraphPaletteItem`  
_L16-28_
- inherits: `SGraphPaletteItem`
- desc: Widget for displaying a Blueprint Item
- L19 _public function_ `SLATE_BEGIN_ARGS(SBlueprintPaletteItem)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData, TWeakPtr<FSceneStateBlueprintEditor> InBlueprintEditorWeak);`
- L26 _private prototype_ `virtual void OnNameTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Widgets/SSceneStateStateMachineMenu.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineMenu`  
`class SStateMachineMenu : public SCompoundWidget`  
_L31-112_
- inherits: `SCompoundWidget`
- L34 _public function_ `SLATE_BEGIN_ARGS(SStateMachineMenu)`
- L37 _public prototype_ `SStateMachineMenu();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FSceneStateBlueprintEditor>& InBlueprintEditor);`
- L43 _public prototype_ `void RefreshMenu();`
- L45 _public prototype_ `void ClearSelection();`
- L48 _private prototype_ `UBlueprint* GetBlueprint() const;`
- L50 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L52 _private prototype_ `FText GetSearchText() const;`
- L54 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L56 _private prototype_ `TSharedRef<SWidget> CreateAddNewMenuWidget();`
- L58 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L60 _private prototype_ `TSharedRef<SWidget> CreateWidgetForAction(FCreateWidgetForActionData* InCreateData);`
- L62 _private prototype_ `void GetGraphActionDetails(const TSharedPtr<FEdGraphSchemaAction>& InAction, UObject*& OutDetailsObject, FText& OutDetailsText) const;`
- L64 _private prototype_ `void OnGraphActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, ESelectInfo::Type InSelectionType);`
- L67 _private prototype_ `FReply OnGraphActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& InMouseEvent);` — Called when dragging the graph action entry
- L69 _private prototype_ `bool ShouldProcessNode(TNotNull<const USceneStateMachineNode*> InGraphNode) const;`
- L70 _private prototype_ `void CollectNodeActionsRecursive(TNotNull<USceneStateMachineNode*> InNode, FText InCategory, FGraphActionListBuilderBase& OutActions);`
- L72 _private prototype_ `bool ShouldProcessGraph(UEdGraph* InGraph) const;`
- L73 _private prototype_ `void CollectGraphActionsRecursive(UEdGraph* InGraph, FText InCategory, int32 InGraphType, FGraphActionListBuilderBase& OutActions);`
- L75 _private prototype_ `void CollectGraphActions(FGraphActionListBuilderBase& OutActions);`
- L77 _private prototype_ `void CollectSections(TArray<int32>& OutSectionIds);`
- L79 _private prototype_ `FText GetSectionTitle(int32 InSectionId) const;`
- L81 _private prototype_ `TSharedRef<SWidget> CreateSectionWidget(TSharedRef<SWidget> InRowWidget, int32 InSectionId);`
- L83 _private prototype_ `FReply OnSectionAddButtonClicked(int32 InSectionId);`
- L85 _private prototype_ `void OnGraphActionDoubleClicked(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions);`
- L87 _private prototype_ `void ExecuteGraphAction(const TSharedPtr<FEdGraphSchemaAction>& InAction);`
- L89 _private prototype_ `bool CanRequestRenameOnActionNode(TWeakPtr<FGraphActionNode> InSelectedNodeWeak) const;`
- L92 _private prototype_ `void OnCategoryTextCommitted(const FText& InText, ETextCommit::Type InCommitType, TWeakPtr<FGraphActionNode> InTargetAction);` — Called when a category target item has been renamed
- L95 _private prototype_ `virtual void Tick(const FGeometry& InGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L96 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L99 _private member_ `TWeakPtr<FSceneStateBlueprintEditor> BlueprintEditorWeak;`
- L101 _private member_ `TSharedRef<FUICommandList> CommandList;`
- L103 _private member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L105 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L107 _private member_ `TSharedPtr<FStateMachineAddMenu> AddMenu;`
- L109 _private member_ `TSharedPtr<FStateMachineContextMenu> ContextMenu;`
- L111 _private member_ `bool bPendingRefresh = false;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SceneState` (scope `UE`)
- L21 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace SceneState` (scope `UE`)
- L28 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Private/Widgets/SceneStateMachineItemDragDropOp.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineItemDragDropOp`  
`class FStateMachineItemDragDropOp : public FGraphSchemaActionDragDropAction`  
_L16-40_
- inherits: `FGraphSchemaActionDragDropAction`
- desc: Drag Drop Op for State Machine Menu Entries
- L19 _public typedef_ `using Super = FGraphSchemaActionDragDropAction;`
- L21 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FStateMachineItemDragDropOp, FGraphSchemaActionDragDropAction) static TSharedRef<FGraphSchemaActionDragDropAction> New(const TSharedPtr<FEdGraphSchemaAction>& InActionNode);`
- L26 _public prototype_ `virtual void HoverTargetChanged() override;`
- L27 _public prototype_ `virtual FReply DroppedOnCategory(FText InCategory) override;`
- L28 _public prototype_ `virtual FReply DroppedOnAction(TSharedRef<FEdGraphSchemaAction> InAction) override;`
- L33 _private prototype_ `void OnHoverCategory(const FText& InCategory);` — Called when hovering over a category
- L36 _private prototype_ `void OnHoverTargetAction(const TSharedRef<FEdGraphSchemaAction>& InTargetAction);` — Called when hovering over a target action
- L38 _private prototype_ `void SetFeedbackMessageOk(const FText& InMessage);`
- L39 _private prototype_ `void SetFeedbackMessageError(const FText& InMessage);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Public/ISceneStateBlueprintEditorModule.h` (Public)


#### class `UE::SceneState::Editor::IBlueprintEditorModule`  
`class IBlueprintEditorModule : public IModuleInterface`  
_L19-46_
- inherits: `IModuleInterface`
- L21 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("Sce`
- L24 _public function_ `static bool IsLoaded()`
- L29 _public function_ `static IBlueprintEditorModule& Get()`
- L34 _public function_ `static IBlueprintEditorModule* GetPtr()`
- L39 _public prototype_ `virtual void RegisterCompiler(TSubclassOf<USceneStateBlueprint> InBlueprintClass) = 0;`
- L42 _public prototype_ `virtual void RegisterContextEditor(const TSharedPtr<IContextEditor>& InContextEditor) = 0;` — Registers the context editor that defines editor-only logic for a given context class/object
- L45 _public prototype_ `virtual void UnregisterContextEditor(const TSharedPtr<IContextEditor>& InContextEditor) = 0;` — Unregisters the context editor from the current list

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Public/ISceneStateContextEditor.h` (Public)


#### class `UE::SceneState::Editor::IContextEditor`  
`class IContextEditor`  
_L17-30_
- desc: Defines editor-only logic for a given context class/object
- L26 _public prototype_ `virtual void GetContextClasses(TArray<TSubclassOf<UObject>>& OutContextClasses) const = 0;` — Gets the context object classes to support
- L29 _public prototype_ `virtual TSharedPtr<SWidget> CreateViewWidget(const FContextParams& InContextParams) const = 0;` — Retrieves the widget to use for the debug viewer

#### struct `UE::SceneState::Editor::IContextEditor::FContextParams`  
`struct FContextParams`  
_L20-23_
- L22 _public member_ `TObjectPtr<UObject> ContextObject;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Public/SceneStateBlueprintEditorUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEBLUEPRINTEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L19 _prototype_ `FGuid FindTaskId(const TSharedRef<IPropertyHandle>& InPropertyHandle);` (scope `UE::SceneState::Editor`) — Finds the Task Id for a given Property Handle by first finding the outer Task Node and returning its Task id.
- L27 _prototype_ `bool IsObjectPropertyOfClass(const FProperty* InProperty, const UClass* InClass);` (scope `UE::SceneState::Editor`) — Returns whether a given property is an object property of a given class @param InProperty the property to check @param InClass the class to check @return true if the property is an object property of the given class
- L35 _prototype_ `bool IsStruct(const FProperty* InProperty, const UScriptStruct* InStruct);` (scope `UE::SceneState::Editor`) — Returns whether a given property is of a given struct type @param InProperty the property to check @param InStruct the type to check @return true if the property is a struct property of the given struct type
- L43 _prototype_ `FPropertyAccess::Result GetGuid(const TSharedRef<IPropertyHandle>& InGuidPropertyHandle, FGuid& OutGuid);` (scope `UE::SceneState::Editor`) — Gets the Guid value from the Property Handle. @param InGuidPropertyHandle the guid property handle to get the guid value from @param OutGuid the returned guid if the operation was successful @return whether the guid was obtained successfully, or whether it failed or had multiple values
- L50 _prototype_ `TSharedRef<IStructureDataProvider> CreateInstancedStructDataProvider(const TSharedRef<IPropertyHandle>& InStructHandle);` (scope `UE::SceneState::Editor`) — Tries to create a structure data provider for the given instanced struct property handle @param InStructHandle the instanced struct property handle to create a struct data provider for @return the created struct data provider
- L58 _prototype_ `bool CompareParametersLayout(const FInstancedPropertyBag& InParametersA, const FInstancedPropertyBag& InParametersB);` (scope `UE::SceneState::Editor`) — Compares the structure layout of two property bags @param InParametersA the first property bag comparand @param InParametersB the second property bag comparand @return true if both have the same number of properties with same names and compatible types.
- L61 _prototype_ `void AssignBindingId(const TSharedRef<IPropertyHandle>& InPropertyHandle, const FGuid& InTaskId);` (scope `UE::SceneState::Editor`) — Sets the Instance Meta-data of a given property handle to a Task Id guid
- L64 _prototype_ `UClass* FindCommonBase(const TSharedRef<IPropertyHandle>& InPropertyHandle);` (scope `UE::SceneState::Editor`) — Finds the Common Class for all the Objects within the Object Property Handle
- L72 _prototype_ `bool AddObjectProperties(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, uint64 InDisallowedFlags = CPF_DisableEditOnInstance);` (scope `UE::SceneState::Editor`) — Helper function to add the Common properties of the object property handle to the Child Builder @param InPropertyHandle the object property handle to get the common properties from @param InChildBuilder the builder to add the properties to @param InDisallowedFlags filter flags. Any property with any of these flags will be skipped

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprintEditor/Public/SceneStateBlueprintFactory.h` (Public)


#### class `USceneStateBlueprintFactory`  
`class USceneStateBlueprintFactory : public UFactory`  
_L15-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L20 _public prototype_ `USceneStateBlueprintFactory();`
- L22 _public prototype_ `static UEdGraph* AddStateMachine(USceneStateBlueprint* InBlueprint);`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`
- L26 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L27 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L28 _public prototype_ `virtual bool ConfigureProperties() override;`
- L29 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L30 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn, FName InCallingContext) override;`
- L35 _public member_ `TSubclassOf<USceneStateSchema> SchemaClass;` — `UPROPERTY()` — Scene state schema to use
- L38 _public member_ `TSubclassOf<USceneStateObject> ParentClass;` — `UPROPERTY()`
