# Plugins / SceneStateBlueprint

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint`
- headers: 8; symbols: 118
- symbol kinds: class=3, delegate=1, enum=1, enumerator=2, externvar=1, function=2, macro=3, member=19, namespace=14, prototype=68, struct=4
- PrivateDependencyModuleNames: SceneState, SceneStateEvent, StructUtilsEditor, UnrealEd
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, PropertyBindingUtils, SceneStateBinding, SceneStateMachineGraph, SlateCore

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Private/SceneStateBlueprintBindingUtils.h` (Private)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SceneState` (scope `UE`)
- L20 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L28 _prototype_ `USceneStateMachineStateNode* FindStateMatchingId(const USceneStateBlueprint& InBlueprint, const FGuid& InStructId);` (scope `UE::SceneState::Graph`) — Finds the state node with id that matches the given struct id. @param InBlueprint the blueprint to look into @param InStructId the struct id to look for @return the found state node matching the given struct id, or null if not found
- L36 _prototype_ `void GetStateBindingDescs(const USceneStateMachineStateNode* InStateNode, TArray<TInstancedStruct<FSceneStateBindingDesc>>& OutBindingDescs, FString InCategory);` (scope `UE::SceneState::Graph`) — Gathers the Binding Descs for a State Node @param InStateNode the state to find binding descs for @param OutBindingDescs the returned binding descs @param InCategory the category to append to the binding descs
- L39 _prototype_ `FSceneStateBindingDesc CreateBindingDesc(const USceneStateBlueprint& InBlueprint);` (scope `UE::SceneState::Graph`) — Creates the Binding Struct Desc for the Variables in the given Blueprint
- L42 _prototype_ `FSceneStateBindingDesc CreateBindingDesc(const USceneStateMachineGraph& InGraph);` (scope `UE::SceneState::Graph`) — Creates the Binding Struct Desc for the Parameters in the given State Machine Graph
- L45 _prototype_ `FSceneStateBindingDesc CreateBindingDesc(const USceneStateMachineStateNode& InStateNode);` (scope `UE::SceneState::Graph`) — Creates the Binding Struct Desc for the Parameters in the given State Node
- L48 _prototype_ `FSceneStateBindingDesc CreateBindingDesc(const USceneStateMachineTransitionNode& InTransitionNode);` (scope `UE::SceneState::Graph`) — Creates the Binding Struct Desc for the Parameters in the given Transition Node
- L51 _prototype_ `FSceneStateBindingDesc CreateBindingDesc(const FSceneStateBindingFunction& InBindingFunctionChecked);` (scope `UE::SceneState::Graph`) — Creates the Binding Struct Desc for the given binding function
- L59 _prototype_ `void GetGlobalBindingDescs(const USceneStateBlueprint& InBlueprint, const FGuid& InTargetStructId, TArray<TInstancedStruct<FSceneStateBindingDesc>>& OutBindingDescs);` (scope `UE::SceneState::Graph`) — Gathers all the global binding descs. Here 'global' means within the scope of the blueprint. @param InBlueprint the blueprint @param InTargetStructId the struct to gather the binding descs for @param OutBindingDescs all the binding descs that can be bound for the target struct
- L67 _prototype_ `void GetFunctionBindingDescs(const USceneStateBlueprint& InBlueprint, const FGuid& InTargetStructId, TArray<TInstancedStruct<FSceneStateBindingDesc>>& OutBindingDescs);` (scope `UE::SceneState::Graph`) — Gathers all the binding descs for functions bound to the given struct id. @param InBlueprint the blueprint @param InTargetStructId the struct to gather the binding descs for @param OutBindingDescs all the binding descs that are bound to the target struct
- L75 _prototype_ `USceneStateMachineGraph* FindStateMachineMatchingId(const USceneStateBlueprint& InBlueprint, const FGuid& InStructId);` (scope `UE::SceneState::Graph`) — Finds the state machine graph with id that matches the given struct id. @param InBlueprint the blueprint to look into @param InStructId the struct id to look for @return the found state machine graph matching the given struct id
- L83 _prototype_ `void GetStateMachineBindingDescs(const USceneStateBlueprint& InBlueprint, const USceneStateMachineGraph& InGraph, TArray<TInstancedStruct<FSceneStateBindingDesc>>& OutBindingDescs);` (scope `UE::SceneState::Graph`) — Gathers all the binding descs for a given state machine graph @param InBlueprint the blueprint containing the graph @param InGraph the state machine graph @param OutBindingDescs all the binding descs that can be bound for the state machine graph
- L91 _prototype_ `USceneStateMachineTaskNode* FindTaskNodeContainingId(const USceneStateBlueprint& InBlueprint, const FGuid& InStructId);` (scope `UE::SceneState::Graph`) — Finds the Task node with Task that contains a given struct id. @param InBlueprint the blueprint to look into @param InStructId the struct id to look for @return the found node containing the given struct id
- L99 _prototype_ `void GetTaskBindingDescs(const USceneStateBlueprint& InBlueprint, const USceneStateMachineTaskNode& InTaskNode, TArray<TInstancedStruct<FSceneStateBindingDesc>>& OutBindingDescs);` (scope `UE::SceneState::Graph`) — Gathers all the binding descs for a given Task Node @param InBlueprint the blueprint containing the task node @param InTaskNode the task node @param OutBindingDescs all the binding descs that can be bound for the task node
- L108 _prototype_ `const FSceneStateBindingFunction* FindBindingFunctionMatchingId(const USceneStateBlueprint& InBlueprint, const FGuid& InStructId, FGuid* OutOwnerStructId = nullptr);` (scope `UE::SceneState::Graph`) — Finds the binding function that matches the given struct id. @param InBlueprint the blueprint to look into @param InStructId the struct id to look for @param OutOwnerStructId (optional) the found binding function's owner struct id @return the found binding function matching the given struct id
- L116 _prototype_ `USceneStateMachineTransitionNode* FindTransitionMatchingId(const USceneStateBlueprint& InBlueprint, const FGuid& InStructId);` (scope `UE::SceneState::Graph`) — Finds the transition node with id that matches the given struct id. @param InBlueprint the blueprint to look into @param InStructId the struct id to look for @return the found transition node matching the given struct id
- L124 _prototype_ `void GetTransitionBindingDescs(const USceneStateBlueprint& InBlueprint, const USceneStateMachineTransitionNode& InTransitionNode, TArray<TInstancedStruct<FSceneStateBindingDesc>>& OutBindingDescs);` (scope `UE::SceneState::Graph`) — Gathers all the binding descs for a given transition node @param InBlueprint the blueprint containing the transition node @param InTransitionNode the transition node @param OutBindingDescs all the binding descs that can be bound for the task node
- L133 _prototype_ `bool FindBindingDescById(const USceneStateBlueprint& InBlueprint, const FGuid& InStructId, TInstancedStruct<FSceneStateBindingDesc>& OutBindingDesc);` (scope `UE::SceneState::Graph`) — Finds the binding desc matching the given id @param InBlueprint the blueprint to look in @param InStructId the id to match @param OutBindingDesc the found binding desc @return true if the binding desc was found, false otherwise
- L142 _prototype_ `bool FindDataViewById(const USceneStateBlueprint& InBlueprint, const FGuid& InStructId, FPropertyBindingDataView& OutDataView);` (scope `UE::SceneState::Graph`) — Finds the data view matching the given struct id @param InBlueprint the blueprint to look in @param InStructId the id to match @param OutDataView the data view of the struct instance if found @return true if the struct was found, false otherwise

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Private/SceneStateBlueprintLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateBlueprint, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneStateBlueprint, Log, All);`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Private/SceneStateBlueprintUtils.h` (Private)


#### enum `UE::SceneState::Graph::EIterationResult`  
`enum class EIterationResult : uint8`  
_L20-24_
- L22 _public enumerator_ `Continue`
- L23 _public enumerator_ `Break`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PropertyBinding` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SceneState` (scope `UE`)
- L18 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L32 _prototype_ `void VisitNodes(TConstArrayView<UEdGraph*> InGraphs, TFunctionRef<void(USceneStateMachineNode*, EIterationResult&)> InFunc);` (scope `UE::SceneState::Graph`) — Visits all the Scene State Machine Nodes in the given Graphs recursively. For each node it calls the passed in function @param InGraphs the graphs to look into @param InFunc the callable for each node, with option to break execution
- L40 _prototype_ `void VisitGraphs(TConstArrayView<UEdGraph*> InGraphs, TFunctionRef<void(USceneStateMachineGraph*, EIterationResult&)> InFunc);` (scope `UE::SceneState::Graph`) — Visits all the Scene State Machine Graphs in the given Graphs recursively. For each node it calls the passed in function @param InGraphs the graphs to look into @param InFunc the callable for each node, with option to break execution
- L47 _prototype_ `void CreateBlueprintVariables(USceneStateBlueprint* InBlueprint, TArrayView<UE::PropertyBinding::FPropertyCreationDescriptor> InPropertyCreationDescs);` (scope `UE::SceneState::Graph`) — Creates Blueprint Variables that match the given Creation Descs @param InBlueprint the blueprint to add variables to @param InPropertyCreationDescs describes property names, types, etc
- L50 _prototype_ `int32 FindIndexOfGraphInParent(UEdGraph* InGraph);` (scope `UE::SceneState::Graph`) — Finds the index of the specified graph in the parent (if it is not reorderable, then we will return INDEX_NONE)
- L53 _prototype_ `bool MoveGraph(UEdGraph* InGraph, int32 InTargetIndex);` (scope `UE::SceneState::Graph`) — Reorders the specified graph to be at the given target index in the parent

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Public/Actions/SceneStateBlueprintAction_Graph.h` (Public)


#### struct `UE::SceneState::Graph::FBlueprintAction_Graph`  
`struct UE_INTERNAL FBlueprintAction_Graph : public FEdGraphSchemaAction_K2Graph`  
_L13-40_
- inherits: `FEdGraphSchemaAction_K2Graph`
- L15 _public prototype_ `FBlueprintAction_Graph() = default;`
- L26 _public prototype_ `explicit FBlueprintAction_Graph(const FArguments& InArgs);`
- L28 _public prototype_ `static FName StaticGetTypeId();`
- L31 _public prototype_ `virtual const FSlateBrush* GetPaletteIcon() const override;`
- L32 _public prototype_ `virtual FName GetTypeId() const override;`
- L33 _public prototype_ `virtual void MovePersistentItemToCategory(const FText& InNewCategory) override;`
- L34 _public prototype_ `virtual int32 GetReorderIndexInContainer() const override;`
- L35 _public prototype_ `virtual bool ReorderToBeforeAction(TSharedRef<FEdGraphSchemaAction> OtherAction) override;`
- L39 _private member_ `FSlateIcon Icon;`

#### struct `UE::SceneState::Graph::FBlueprintAction_Graph::FArguments`  
`struct FArguments`  
_L17-25_
- L19 _public member_ `UEdGraph* Graph = nullptr;`
- L20 _public member_ `EEdGraphSchemaAction_K2Graph::Type GraphType = EEdGraphSchemaAction_K2Graph::Graph;`
- L21 _public member_ `FText Category;`
- L22 _public member_ `FSlateIcon Icon;`
- L23 _public member_ `int32 Grouping = 0;`
- L24 _public member_ `int32 SectionID = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEBLUEPRINT_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Public/SceneStateBlueprint.h` (Public)


#### class `USceneStateBlueprint`  
`class USceneStateBlueprint : public UBlueprint, public ISceneStateSchemaProvider, public ISceneStateBindingCollectionOwner`  
_L18-134_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Scene State Blueprint")`
- inherits: `UBlueprint,ISceneStateSchemaProvider,ISceneStateBindingCollectionOwner`
- L23 _public prototype_ `USceneStateBlueprint(const FObjectInitializer& InObjectInitializer);`
- L25 _public function_ `const FGuid& GetRootId() const`
- L31 _public function_ `template<typename T> T* FindExtension() const`
- L36 _public prototype_ `UBlueprintExtension* FindExtension(TSubclassOf<UBlueprintExtension> InClass) const;`
- L38 _public prototype_ `FSceneStateBindingDesc CreateRootBinding() const;`
- L50 _public prototype_ `void GetBindingStructs(const FGetBindableStructsParams& InParams, TArray<TInstancedStruct<FSceneStateBindingDesc>>& OutBindingDescs) const;` — Gathers the binding structs for a given struct id.
- L53 _public prototype_ `bool ForEachBindingFunction(TFunctionRef<bool(const FSceneStateBindingFunction&, const FPropertyBindingBinding&)> InFunc) const;` — Iterates all functions found within the bindings
- L56 _public prototype_ `virtual FSceneStateBindingCollection& GetBindingCollection() override;`
- L57 _public prototype_ `virtual const FSceneStateBindingCollection& GetBindingCollection() const override;`
- L58 _public prototype_ `virtual bool ForEachBindableFunction(TFunctionRef<bool(const FSceneStateBindingDesc&, const UE::SceneState::FBindingFunctionInfo&)> InFunc) const override;`
- L62 _public prototype_ `virtual void GetBindableStructs(const FGuid InTargetStructId, TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& OutStructDescs) const override;`
- L63 _public prototype_ `virtual bool GetBindableStructByID(const FGuid InStructId, TInstancedStruct<FPropertyBindingBindableStructDescriptor>& OutStructDesc) const override;`
- L64 _public prototype_ `virtual bool GetBindingDataViewByID(const FGuid InStructId, FPropertyBindingDataView& OutDataView) const override;`
- L65 _public prototype_ `virtual FPropertyBindingBindingCollection* GetEditorPropertyBindings() override;`
- L66 _public prototype_ `virtual const FPropertyBindingBindingCollection* GetEditorPropertyBindings() const override;`
- L67 _public prototype_ `virtual bool CanCreateParameter(const FGuid InStructId) const override;`
- L68 _public prototype_ `virtual void CreateParametersForStruct(const FGuid InStructId, TArrayView<UE::PropertyBinding::FPropertyCreationDescriptor> InOutCreationDescs) override;`
- L69 _public prototype_ `virtual void AppendBindablePropertyFunctionStructs(TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& InOutStructs) const override;`
- L73 _public prototype_ `void SetSceneStateSchema(TSubclassOf<USceneStateSchema> InSchemaClass);` — Sets the scene state schema to use for this blueprint
- L76 _public prototype_ `virtual TSubclassOf<USceneStateSchema> GetSceneStateSchemaClass() const override;`
- L80 _public prototype_ `virtual void SetObjectBeingDebugged(UObject* InNewObject) override;`
- L81 _public prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L82 _public prototype_ `virtual void GetReparentingRules(TSet<const UClass*>& OutAllowedChildrenOfClasses, TSet<const UClass*>& OutDisallowedChildrenOfClasses) const override;`
- L83 _public prototype_ `virtual bool SupportedByDefaultBlueprintFactory() const override;`
- L84 _public prototype_ `virtual void LoadModulesRequiredForCompilation() override;`
- L85 _public prototype_ `virtual bool IsValidForBytecodeOnlyRecompile() const override;`
- L89 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L90 _public prototype_ `virtual void PostLoad() override;`
- L91 _public prototype_ `virtual void BeginDestroy() override;`
- L96 _public member_ `TArray<TObjectPtr<UEdGraph>> StateMachineGraphs;` — `UPROPERTY()` — The top level State Machine Graphs of this State. Does not include the state machine graphs of nested state nodes
- L100 _public member_ `FSceneStateBindingCollection BindingCollection;` — `UPROPERTY()` — Holds all the editor bindings prior to compilation
- L104 _private prototype_ `void OnRenameVariableReferences(UBlueprint* InBlueprint, UClass* InVariableClass, const FName& InOldVariableName, const FName& InNewVariableName);` — Called when a blueprint variable has been renamed. Used to fix the bindings to the variable being renamed to use the new name
- L107 _private prototype_ `void RenameVariableReferenceInPath(FPropertyBindingPath& InPath, FName InOldVariableName, FName InNewVariableName);` — Called when a blueprint variable has been renamed. Used to fix the path to the variable being renamed to use the new name
- L110 _private prototype_ `void OnGraphParametersChanged(USceneStateMachineGraph* InGraph);` — Called when a state machine graph's parameters have changed
- L113 _private prototype_ `void OnStateParametersChanged(USceneStateMachineStateNode* InStateNode);` — Called when a state's parameters have changed
- L116 _private prototype_ `void UpdateParametersBindings(FPropertyBindingPath& InPath, const FGuid& InParametersId, const FInstancedPropertyBag& InParameters);` — Called when parameters have changed. Used to fix the path to parameters that have possibly been renamed
- L120 _private member_ `TSubclassOf<USceneStateSchema> SceneStateSchemaClass;` — `UPROPERTY(VisibleAnywhere, Category="Scene State", AssetRegistrySearchable)` — Scene State schema class to use for this blueprint
- L124 _private member_ `FGuid RootId;` — `UPROPERTY()` — Unique id representing this blueprint / generated class as a bindable struct
- L127 _private member_ `FDelegateHandle OnRenameVariableReferencesHandle;` — Handle to the delegate when a blueprint variable has been renamed
- L130 _private member_ `FDelegateHandle OnGraphParametersChangedHandle;` — Handle to the delegate when a state machine graph parameters have changed
- L133 _private member_ `FDelegateHandle OnStateParametersChangedHandle;` — Handle to the delegate when a state parameters have changed

#### struct `USceneStateBlueprint::FGetBindableStructsParams`  
`struct FGetBindableStructsParams`  
_L40-48_
- L43 _public member_ `FGuid TargetStructId;` — Struct id to look bindable structs for
- L45 _public member_ `bool bIncludeGlobalDescs = true;` — Whether to include the global bindings to the struct
- L47 _public member_ `bool bIncludeFunctions = false;` — Whether to include the binding functions bound to the struct

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCENESTATEBLUEPRINT_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Public/SceneStateBlueprintDelegates.h` (Public)


#### struct `UE::SceneState::Graph::FBlueprintDebugObjectChange`  
`struct FBlueprintDebugObjectChange`  
_L16-22_
- L19 _public member_ `TObjectPtr<USceneStateBlueprint> Blueprint;` — The blueprint whose debug object got changed
- L21 _public member_ `TObjectPtr<UObject> DebugObject;` — The new debug object

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEBLUEPRINT_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L30 _externvar_ `extern TMulticastDelegate<void(const FBlueprintDebugObjectChange&)> OnBlueprintDebugObjectChanged;` (scope `UE::SceneState::Graph`) — Delegate called when the debug object of a blueprint has changed. Blueprint Editor doesn't have a dedicated delegate for this and instead calls IBlueprintEditor::RefreshMyBlueprint, or IBlueprintEditor::RefreshEditors. Additionally, these refresh functions are not called in every place the debug object is changed (e.g. in UWorld::TransferBlueprintDebugReferences). UBlueprint::DebuggingWorldRegistrationHelper is closer to what is needed, but still requires a valid UWorld to have been found. This delegate solves this by broadcasting in USceneStateBlueprint::SetObjectBeingDebugged without requiring a valid world.

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Public/SceneStateBlueprintExtension.h` (Public)


#### class `USceneStateBlueprintExtension`  
`class USceneStateBlueprintExtension : public UBlueprintExtension`  
_L9-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintExtension`
- L14 _private prototype_ `virtual void GetAllGraphs(TArray<UEdGraph*>& OutGraphs) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBlueprint/Public/SceneStateTaskBlueprint.h` (Public)


#### class `USceneStateTaskBlueprint`  
`class USceneStateTaskBlueprint : public UBlueprint`  
_L9-18_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Scene State Task Blueprint")`
- inherits: `UBlueprint`
- L14 _private prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L15 _private prototype_ `virtual void GetReparentingRules(TSet<const UClass*>& OutAllowedChildrenOfClasses, TSet<const UClass*>& OutDisallowedChildrenOfClasses) const override;`
- L16 _private prototype_ `virtual bool SupportedByDefaultBlueprintFactory() const override;`
