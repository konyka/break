# Plugins / DataLinkEdGraph

- module root: `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph`
- headers: 10; symbols: 101
- symbol kinds: class=6, delegate=1, function=8, member=18, prototype=64, struct=4
- PrivateDependencyModuleNames: BlueprintGraph, KismetCompiler, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DataLink, Engine

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Private/Actions/DataLinkGraphAction_NewNativeNode.h` (Private)


#### struct `FDataLinkGraphAction_NewNativeNode`  
`struct FDataLinkGraphAction_NewNativeNode : public FDataLinkGraphAction_NewNode`  
_L12-28_
- reflection: `USTRUCT()`
- inherits: `FDataLinkGraphAction_NewNode`
- L16 _public prototype_ `FDataLinkGraphAction_NewNativeNode() = default;`
- L18 _public prototype_ `explicit FDataLinkGraphAction_NewNativeNode(TSubclassOf<UDataLinkNode> InNodeClass, int32 InGrouping);`
- L22 _protected prototype_ `virtual TSubclassOf<UDataLinkNode> GetNodeClass() const override;`
- L23 _protected prototype_ `virtual void ConfigureNode(const FConfigContext& InContext) const override;`
- L27 _private member_ `TSubclassOf<UDataLinkNode> NodeClass;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Private/Actions/DataLinkGraphAction_NewNode.h` (Private)


#### struct `FDataLinkGraphAction_NewNode`  
`struct FDataLinkGraphAction_NewNode : public FEdGraphSchemaAction`  
_L12-36_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L16 _public prototype_ `FDataLinkGraphAction_NewNode() = default;`
- L19 _protected function_ `virtual TSubclassOf<UDataLinkNode> GetNodeClass() const`
- L29 _protected function_ `virtual void ConfigureNode(const FConfigContext& InContext) const`
- L34 _protected prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* InParentGraph, UEdGraphPin* InSourcePin, const FVector2f& InLocation, bool bInSelectNewNode = true) override;`

#### struct `FDataLinkGraphAction_NewNode::FConfigContext`  
`struct FConfigContext`  
_L24-28_
- L26 _public member_ `UDataLinkNode* TemplateNode;`
- L27 _public member_ `UEdGraphPin* SourcePin;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Private/Actions/DataLinkGraphAction_NewScriptNode.h` (Private)


#### struct `FDataLinkGraphAction_NewScriptNode`  
`struct FDataLinkGraphAction_NewScriptNode : public FDataLinkGraphAction_NewNode`  
_L10-28_
- reflection: `USTRUCT()`
- inherits: `FDataLinkGraphAction_NewNode`
- L14 _public prototype_ `FDataLinkGraphAction_NewScriptNode() = default;`
- L16 _public prototype_ `explicit FDataLinkGraphAction_NewScriptNode(const FAssetData& InNodeAsset, int32 InGrouping);`
- L20 _protected prototype_ `virtual TSubclassOf<UDataLinkNode> GetNodeClass() const override;`
- L21 _protected prototype_ `virtual void ConfigureNode(const FConfigContext& InContext) const override;`
- L25 _private prototype_ `TSubclassOf<UDataLinkScriptNode> GetScriptNodeClass() const;`
- L27 _private member_ `FAssetData NodeAsset;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Private/Blueprint/K2Node_AsyncDataLinkRequest.h` (Private)


#### class `UK2Node_AsyncDataLinkRequest`  
`class UK2Node_AsyncDataLinkRequest : public UK2Node_BaseAsyncTask`  
_L9-27_
- reflection: `UCLASS()`
- inherits: `UK2Node_BaseAsyncTask`
- L14 _public prototype_ `UK2Node_AsyncDataLinkRequest();`
- L16 _public prototype_ `UEdGraphPin* GetDataLinkInstancePin() const;`
- L17 _public prototype_ `UEdGraphPin* GetExecutionContextPin() const;`
- L18 _public prototype_ `UEdGraphPin* GetDataLinkSinkProviderPin() const;`
- L19 _public prototype_ `UEdGraphPin* GetOutputDataPin() const;`
- L20 _public prototype_ `UEdGraphPin* GetExecutionResultPin() const;`
- L21 _public prototype_ `UEdGraphPin* GetOnOutputDataPin() const;`
- L25 _protected prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Private/DataLinkEdGraphLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkEdGraph, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataLinkEdGraph, Log, All);`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Public/Blueprint/K2Node_DataLinkRequest.h` (Public)


#### class `UK2Node_DataLinkRequest`  
`class UE_DEPRECATED(5.7, "Data Link Request deprecated. Use Data Link Executor Object instead.") UK2Node_DataLinkRequest : public UK2Node`  
_L11-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L16 _public member_ `static const FLazyName PN_DataLinkInstance;`
- L17 _public member_ `static const FLazyName PN_ExecutionContext;`
- L18 _public member_ `static const FLazyName PN_DataLinkSinkProvider;`
- L19 _public member_ `static const FLazyName PN_Success;`
- L20 _public member_ `static const FLazyName PN_Failure;`
- L23 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L24 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* InTargetGraph) const override;`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L26 _public prototype_ `virtual bool IsDeprecated() const override;`
- L27 _public prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType InDeprecationType) const override;`
- L31 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& InCompilerContext, UEdGraph* InSourceGraph) override;`
- L32 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L33 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L34 _public prototype_ `virtual FText GetMenuCategory() const override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Public/DataLinkEdGraph.h` (Public)


#### class `UDataLinkEdGraph`  
`class UDataLinkEdGraph : public UEdGraph`  
_L12-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L17 _public prototype_ `UDataLinkEdGraph();`
- L23 _public prototype_ `UDataLinkEdOutputNode* FindOutputNode() const;` — Finds the 'cosmetic' output node @see UDataLinkEdOutputNode
- L26 _public prototype_ `void InitializeNodes();` — Initializes all the nodes in this graph, recreating pins of outdated nodes to ensure these are up-to-date with their templates
- L29 _public prototype_ `virtual void BeginDestroy() override;`
- L30 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L33 _public prototype_ `void DirtyGraph();`
- L35 _public prototype_ `bool IsCompiledGraphUpToDate() const;`
- L38 _private prototype_ `void OnGraphCompiled(UDataLinkGraph* InCompiledGraph);`
- L45 _private member_ `FGuid ChangeId;` — `UPROPERTY()` — Represents id of graph changes that haven't been compiled yet. Note: if a change occurs, this id will be regenerated only if the Last Compiled Change Id matches the current change id.
- L49 _private member_ `FGuid LastCompiledChangeId;` — `UPROPERTY()` — The Change Id that was last compiled
- L51 _private member_ `FDelegateHandle OnGraphCompiledHandle;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Public/DataLinkEdGraphSchema.h` (Public)


#### class `UDataLinkEdGraphSchema`  
`class UDataLinkEdGraphSchema : public UEdGraphSchema`  
_L9-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L15 _public member_ `static const FLazyName PC_Data;` — Pin Categories
- L18 _public member_ `static const FLinearColor PCC_Data;` — Pin Category Colors
- L21 _public prototype_ `bool IsConnectionLooping(const UEdGraphPin* InInputPin, const UEdGraphPin* InOutputPin) const;` — Check whether connecting these pins would cause a loop
- L24 _public prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& InGraph) const override;`
- L25 _public prototype_ `virtual bool ArePinsCompatible(const UEdGraphPin* InPinA, const UEdGraphPin* InPinB, const UClass* InCallingContext = nullptr, bool bInIgnoreArray = false) const override;`
- L26 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& InContextMenuBuilder) const override;`
- L27 _public prototype_ `virtual void GetContextMenuActions(UToolMenu* InMenu, UGraphNodeContextMenuContext* InContext) const override;`
- L28 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* InSourcePin, const UEdGraphPin* InTargetPin) const override;`
- L29 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& InPinType) const override;`
- L30 _public prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& InGraph, FGraphDisplayInfo& OutDisplayInfo) const override;`

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Public/Nodes/DataLinkEdNode.h` (Public)


#### class `UDataLinkEdNode`  
`class UDataLinkEdNode : public UEdGraphNode`  
_L14-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L19 _public member_ `static const FLazyName MD_InvalidatesNode;`
- L20 _public member_ `static const FLazyName PN_Output;`
- L22 _public prototype_ `void SetTemplateNodeClass(TSubclassOf<UDataLinkNode> InNodeClass, bool bInReconstructNode = true);`
- L24 _public prototype_ `void ForEachPinConnection(TFunctionRef<void(const UEdGraphPin&, const UDataLinkEdNode&, const UEdGraphPin&)> InFunction) const;`
- L26 _public function_ `UDataLinkNode* GetTemplateNode() const`
- L32 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* InFromPin) override;`
- L33 _public prototype_ `virtual void ReconstructNode() override;`
- L34 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* InSchema) const override;`
- L35 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L36 _public prototype_ `virtual FText GetTooltipText() const override;`
- L37 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* InPin) override;`
- L41 _public prototype_ `virtual void PostLoad() override;`
- L42 _public prototype_ `virtual void PostEditUndo() override;`
- L43 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L46 _public function_ `static FName GetTemplateNodePropertyName()`
- L51 _public prototype_ `void UpdateMetadata();`
- L53 _public prototype_ `void NotifyNodeChanged();`
- L59 _public prototype_ `virtual bool RequiresPinRecreation() const;` — Checks against the current Template Node to determine if the Ed Node's structure matches the Template Node's @return true if the structures mismatch and requires node reconstruction
- L62 _public prototype_ `void RefreshPins();` — Destroys existing pins and recreates new ones based on the underlying Template Node while also restoring pin links where available
- L71 _private prototype_ `bool SyncPins(EEdGraphPinDirection InPinDirection, TConstArrayView<FDataLinkPin> InTemplatePins);` — Syncs the node pins to match the given data link pins @param InPinDirection the direction of pins to consider @param InTemplatePins the pins to match @return true if the pin structure was changed
- L75 _private member_ `TObjectPtr<UDataLinkNode> TemplateNode;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Data Link")` — Underlying Data Link Node this Editor Node represents
- L78 _private member_ `FDataLinkNodeMetadata NodeMetadata;` — Cached metadata from the Template Node

### `Plugins/VirtualProduction/DataLink/Source/DataLinkEdGraph/Public/Nodes/DataLinkEdOutputNode.h` (Public)


#### class `UDataLinkEdOutputNode`  
`class UDataLinkEdOutputNode : public UDataLinkEdNode`  
_L14-33_
- reflection: `UCLASS(MinimalAPI, DisplayName="Output")`
- inherits: `UDataLinkEdNode`
- desc: A 'cosmetic' output node. This is considered cosmetic because it does not get compiled in and is used only to iterate through the nodes that should be considered for compilation.
- L20 _public prototype_ `UEdGraphPin* GetOutputResultPin() const;` — Retrieves the output result pin
- L23 _public function_ `virtual bool RequiresPinRecreation() const override`
- L27 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const;`
- L28 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _public function_ `virtual bool CanDuplicateNode() const override`
- L30 _public function_ `virtual bool CanUserDeleteNode() const override`
- L31 _public function_ `virtual bool GetCanRenameNode() const override`
