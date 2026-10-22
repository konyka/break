# Plugins / SceneStateTransitionGraph

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph`
- headers: 7; symbols: 34
- symbol kinds: class=7, member=2, namespace=3, prototype=21, struct=1
- PrivateDependencyModuleNames: GraphEditor, UnrealEd
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, SceneState

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph/Private/SceneStateTransitionOptionalPinManager.h` (Private)


#### struct `UE::SceneState::Graph::FTransitionOptionalPinManager`  
`struct FTransitionOptionalPinManager : FOptionalPinManager`  
_L10-20_
- inherits: `FOptionalPinManager`
- L13 _public prototype_ `virtual void PostInitNewPin(UEdGraphPin* InPin , FOptionalPinFromProperty& InRecord , int32 InArrayIndex , FProperty* InProperty , uint8* InPropertyAddress , uint8* InDefaultPropertyAddress) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph/Public/ISceneStateTransitionGraphProvider.h` (Public)


#### class `USceneStateTransitionGraphProvider`  
`class USceneStateTransitionGraphProvider : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ISceneStateTransitionGraphProvider`  
`class ISceneStateTransitionGraphProvider`  
_L18-34_
- L24 _public prototype_ `virtual FText GetTitle() const = 0;` — Gets the Title of this Provider, to use as the Display Title of the Bound Graph
- L30 _public prototype_ `virtual bool IsBoundToGraphLifetime(UEdGraph& InGraph) const = 0;` — Determines whether the provider is bound to the given Ed Graph. In other words, whether the provider (as an ed node) should be destroyed when the bound graph is being deleted
- L33 _public prototype_ `virtual UEdGraphNode* AsNode() = 0;` — The provider casted as an ed graph node

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph/Public/Nodes/SceneStateTransitionResultNode.h` (Public)


#### class `USceneStateTransitionResultNode`  
`class USceneStateTransitionResultNode : public UK2Node`  
_L10-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L16 _public prototype_ `virtual FString GetDescriptiveCompiledName() const override;`
- L17 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* InSchema) const override;`
- L18 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L19 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L20 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L21 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L22 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L23 _public prototype_ `virtual FText GetTooltipText() const override;`
- L24 _public prototype_ `virtual bool IsNodeRootSet() const override;`
- L28 _public member_ `FSceneStateTransitionResult Result;` — `UPROPERTY(EditAnywhere, Category="Scene State Transition")`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph/Public/SceneStateConduitGraph.h` (Public)


#### class `USceneStateConduitGraph`  
`class USceneStateConduitGraph : public USceneStateTransitionGraph`  
_L9-12_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneStateTransitionGraph`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph/Public/SceneStateConduitGraphSchema.h` (Public)


#### class `USceneStateConduitGraphSchema`  
`class USceneStateConduitGraphSchema : public USceneStateTransitionGraphSchema`  
_L9-12_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneStateTransitionGraphSchema`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph/Public/SceneStateTransitionGraph.h` (Public)


#### class `USceneStateTransitionGraph`  
`class USceneStateTransitionGraph : public UEdGraph`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L17 _public member_ `TObjectPtr<USceneStateTransitionResultNode> ResultNode;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateTransitionGraph/Public/SceneStateTransitionGraphSchema.h` (Public)


#### class `USceneStateTransitionGraphSchema`  
`class USceneStateTransitionGraphSchema : public UEdGraphSchema_K2`  
_L9-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- L15 _public prototype_ `virtual EGraphType GetGraphType(const UEdGraph* InGraph) const override;`
- L16 _public prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& InGraph) const override;`
- L17 _public prototype_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override;`
- L18 _public prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& InGraph, FGraphDisplayInfo& OutDisplayInfo) const override;`
- L19 _public prototype_ `virtual bool ShouldAlwaysPurgeOnModification() const override;`
- L20 _public prototype_ `virtual void HandleGraphBeingDeleted(UEdGraph& InGraphBeingRemoved) const override;`
- L24 _public prototype_ `virtual bool DoesSupportCollapsedNodes() const override;`
- L25 _public prototype_ `virtual bool DoesSupportEventDispatcher() const override;`
