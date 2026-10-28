# Plugins / SceneStateEventGraph

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateEventGraph`
- headers: 6; symbols: 61
- symbol kinds: class=6, member=11, prototype=43, struct=1
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, KismetCompiler, SceneStateEvent, UnrealEd

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventGraph/Private/K2Node_SceneStateBroadcastEvent.h` (Private)


#### class `UK2Node_SceneStateBroadcastEvent`  
`class UK2Node_SceneStateBroadcastEvent : public UK2Node_SceneStateEventBase`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UK2Node_SceneStateEventBase`
- L14 _public prototype_ `UK2Node_SceneStateBroadcastEvent();`
- L18 _protected prototype_ `virtual void AllocateDefaultPins() override;`
- L19 _protected prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L23 _protected prototype_ `virtual void ExpandNode(FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph) override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventGraph/Private/K2Node_SceneStateEventBase.h` (Private)


#### class `UK2Node_SceneStateEventBase`  
`class UK2Node_SceneStateEventBase : public UK2Node`  
_L10-84_
- reflection: `UCLASS(Abstract)`
- inherits: `UK2Node`
- L16 _protected member_ `static const FLazyName PN_EventStream;` — Common Pin Names
- L17 _protected member_ `static const FLazyName PN_WorldContextObject;`
- L19 _protected prototype_ `FText GetSchemaDisplayNameText() const;`
- L21 _protected prototype_ `FString GetSchemaHandleStringValue() const;`
- L23 _protected prototype_ `void OnEventSchemaChanged();`
- L25 _protected prototype_ `bool IsEventDataPin(const UEdGraphPin* InPin) const;`
- L27 _protected prototype_ `void CreateEventDataPins(TConstArrayView<UEdGraphPin*> InPinsToSearch);`
- L29 _protected prototype_ `void MoveEventDataPins(FKismetCompilerContext& InCompilerContext, UEdGraphNode* InTargetIntermediateNode);`
- L31 _protected prototype_ `bool ConnectPinsToIntermediate(FKismetCompilerContext& InCompilerContext, UK2Node* InTargetIntermediateNode, FName InSourcePin, FName InTargetPin);`
- L49 _protected prototype_ `bool ChainNode(FNodeExpansionContext& Context, const UK2Node* InNode);` — Adds the provided intermediate node sequentially after the last chained node, or if it's the first node moves the exec pins of this node to the intermediate node's exec pins
- L52 _protected prototype_ `bool FinishChain(const FNodeExpansionContext& Context);` — Finishes chain by moving the then pins of this node to the last chained node's then pin
- L55 _protected prototype_ `void SpawnEventDataNodes(FNodeExpansionContext& Context);` — Spawns the intermediate nodes relating to event data. Only does it if the event has parameters (i.e. a valid event struct)
- L57 _protected prototype_ `UEdGraphPin* FindPin(FName InPinName, TConstArrayView<UEdGraphPin*> InPinsToSearch) const;`
- L60 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L64 _protected prototype_ `virtual bool HasExternalDependencies(TArray<UStruct*>* OutOptionalOutput) const override;`
- L65 _protected prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* InTargetGraph) const override;`
- L66 _protected prototype_ `virtual void PostPlacedNewNode() override;`
- L70 _protected prototype_ `virtual bool ShouldShowNodeProperties() const override;`
- L71 _protected prototype_ `virtual bool IsNodeSafeToIgnore() const override;`
- L72 _protected prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& InOldPins) override;`
- L73 _protected prototype_ `virtual void GetNodeAttributes(TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes) const override;`
- L74 _protected prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L75 _protected prototype_ `virtual FText GetMenuCategory() const override;`
- L79 _protected member_ `FSceneStateEventSchemaHandle EventSchemaHandle;` — `UPROPERTY(EditAnywhere, Category="Scene State Event")`
- L81 _protected member_ `EEdGraphPinDirection EventDataPinDirection = EGPD_Input;`
- L83 _protected member_ `bool bHasEventData = true;`

#### struct `UK2Node_SceneStateEventBase::FNodeExpansionContext`  
`struct FNodeExpansionContext`  
_L33-43_
- L36 _public member_ `FKismetCompilerContext& CompilerContext;` — Compiler context provided by the expand node func
- L38 _public member_ `UEdGraph* SourceGraph;` — Source graph provided by the expand node func
- L40 _public member_ `UEdGraphPin* EventDataPin;` — Input intermediate pin to connect the event data output to
- L42 _public member_ `const UK2Node* ChainingNode = nullptr;` — Last node that was added to the chain. Starts as null

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventGraph/Private/K2Node_SceneStateFindEvent.h` (Private)


#### class `UK2Node_SceneStateFindEvent`  
`class UK2Node_SceneStateFindEvent : public UK2Node_SceneStateFindEventBase`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UK2Node_SceneStateFindEventBase`
- L14 _public prototype_ `UK2Node_SceneStateFindEvent();`
- L18 _protected prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L22 _protected prototype_ `virtual void ExpandNode(FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph) override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventGraph/Private/K2Node_SceneStateFindEventBase.h` (Private)


#### class `UK2Node_SceneStateFindEventBase`  
`class UK2Node_SceneStateFindEventBase : public UK2Node_SceneStateEventBase`  
_L12-48_
- reflection: `UCLASS(Abstract)`
- inherits: `UK2Node_SceneStateEventBase`
- desc: Base Implementation of Find Event for FindEvent and HasEvent nodes
- L17 _public prototype_ `UK2Node_SceneStateFindEventBase();`
- L21 _protected prototype_ `bool CanHandleCapturedEventsOnly(FKismetCompilerContext* InCompilerContext = nullptr) const;` — Whether a Context Object input pin is required to retrieve the Event Handler Id
- L24 _protected prototype_ `bool FindEventHandlerId(FKismetCompilerContext& InCompilerContext, FGuid& OutHandlerId) const;` — Attempts to Find a Handler Id only if the node is outered to the Event Handler Provider
- L27 _protected prototype_ `UK2Node_CallFunction* SpawnFindEventNode(FName InFindEventFunctionName, FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph);` — Spawns the Find Event Node and sets up the default pins (Event Stream, Handler Id, etc)
- L30 _protected prototype_ `virtual void PostRename(UObject* InOldOuter, const FName InOldName) override;`
- L31 _protected prototype_ `virtual void PostEditUndo() override;`
- L35 _protected prototype_ `virtual void AllocateDefaultPins() override;`
- L39 _protected prototype_ `virtual bool IsNodePure() const override;`
- L44 _protected member_ `bool bCapturedEventsOnly = true;` — `UPROPERTY(EditAnywhere, Category="Scene State Event", meta=(DisplayAfter="EventSchema", EditCondition="bCanHandleCapturedEventsOnly", EditConditionHides, HideEditConditionToggle))` — Whether to only consider Events captured by a containing object that handles events
- L47 _protected member_ `bool bCanHandleCapturedEventsOnly = false;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventGraph/Private/K2Node_SceneStateHasEvent.h` (Private)


#### class `UK2Node_SceneStateHasEvent`  
`class UK2Node_SceneStateHasEvent : public UK2Node_SceneStateFindEventBase`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UK2Node_SceneStateFindEventBase`
- L14 _public prototype_ `UK2Node_SceneStateHasEvent();`
- L18 _protected prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L22 _protected prototype_ `virtual void ExpandNode(FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph) override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateEventGraph/Private/K2Node_SceneStatePushEvent.h` (Private)


#### class `UK2Node_SceneStatePushEvent`  
`class UK2Node_SceneStatePushEvent : public UK2Node_SceneStateEventBase`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UK2Node_SceneStateEventBase`
- L14 _public prototype_ `UK2Node_SceneStatePushEvent();`
- L18 _protected prototype_ `virtual void AllocateDefaultPins() override;`
- L19 _protected prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L23 _protected prototype_ `virtual void ExpandNode(FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph) override;`
