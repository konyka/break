# Plugins / RigMapperEditor

- module root: `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor`
- headers: 15; symbols: 411
- symbol kinds: class=25, delegate=3, enum=1, enumerator=4, function=49, macro=11, member=80, prototype=233, struct=3, typedef=2
- PrivateDependencyModuleNames: AnimGraph, AssetTools, BlueprintGraph, ContentBrowser, ControlRig, ControlRigDeveloper, Core, CoreUObject, InputCore, LevelSequence, MessageLog, MovieScene, MovieSceneTracks, Sequencer, Slate, SlateCore, TargetPlatform, ToolMenus
- PublicDependencyModuleNames: EditorSubsystem, Engine, GraphEditor, RigMapper, UnrealEd

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperDefinitionAssetTypeActions.h` (Private)


#### class `FRigMapperDefinitionAssetTypeActions`  
`class FRigMapperDefinitionAssetTypeActions : public FAssetTypeActions_Base`  
_L13-21_
- inherits: `FAssetTypeActions_Base`
- desc: The asset actions for the URigMapperDefinition data asset class and link to its asset editor toolkit
- L16 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L17 _public prototype_ `virtual FText GetName() const override;`
- L18 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L19 _public prototype_ `virtual uint32 GetCategories() override;`
- L20 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperDefinitionEditorToolkit.h` (Private)


#### class `FRigMapperDefinitionEditorToolkit`  
`class FRigMapperDefinitionEditorToolkit : public FAssetEditorToolkit, public FSelfRegisteringEditorUndoClient`  
_L21-90_
- inherits: `FAssetEditorToolkit,FSelfRegisteringEditorUndoClient`
- desc: The toolkit for the URigMapperDefinition asset editor
- L25 _public prototype_ `void Initialize(URigMapperDefinition* InDefinition, EToolkitMode::Type InMode, TSharedPtr<IToolkitHost> InToolkitHost);`
- L28 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L29 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L30 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L31 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L32 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L33 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L34 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L38 _public prototype_ `void PostUndo(bool bSuccess) override;`
- L39 _public prototype_ `void PostRedo(bool bSuccess) override;`
- L42 _public function_ `TSharedPtr<SRigMapperDefinitionGraphEditor> GetGraphEditorWidget() const`
- L61 _protected prototype_ `void OnClose() override;`
- L64 _private prototype_ `TSharedRef<SDockTab> SpawnGraphTab(const FSpawnTabArgs& SpawnTabArgs);`
- L65 _private prototype_ `TSharedRef<SDockTab> SpawnDetailsTab(const FSpawnTabArgs& SpawnTabArgs);`
- L66 _private prototype_ `TSharedRef<SDockTab> SpawnStructureTab(const FSpawnTabArgs& SpawnTabArgs);`
- L68 _private prototype_ `bool HandleIsPropertyVisible(const FPropertyAndParent& PropertyAndParent);`
- L69 _private prototype_ `void HandleNodePropertyChanged(const FPropertyChangedEvent& PropertyChangedEvent);`
- L70 _private prototype_ `void HandleGraphStructureUpdated();`
- L71 _private prototype_ `void HandleGraphSelectionChanged(const TSet<UObject*>& Nodes);`
- L73 _private prototype_ `void HandleStructureSelectionChanged(ESelectInfo::Type SelectInfo, TArray<FString> SelectedInputs, TArray<FString> SelectedFeatures, TArray<FString> SelectedOutputs, TArray<FString> SelectedNullOutputs);`
- L76 _private member_ `static const FName DefinitionEditorGraphTabId;`
- L77 _private member_ `static const FName DefinitionEditorStructureTabId;`
- L78 _private member_ `static const FName DefinitionEditorDetailsTabId;`
- L80 _private member_ `static const TMap<FName, ERigMapperFeatureType> PropertyNameToNodeTypeMapping;`
- L82 _private member_ `TObjectPtr<URigMapperDefinition> Definition;`
- L84 _private member_ `TSharedPtr<SRigMapperDefinitionGraphEditor> GraphEditor;`
- L85 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L86 _private member_ `TSharedPtr<SRigMapperDefinitionStructureView> StructureView;`
- L87 _private member_ `TSharedPtr<SDockTab> GraphTab;`
- L88 _private member_ `TWeakObjectPtr<URigMapperDefinitionEditorGraphNode> SelectedGraphNode;`

#### class `FRigMapperDefinitionEditorToolkit::FDetailsViewCustomization`  
`class FDetailsViewCustomization : public IDetailCustomization`  
_L47-58_
- inherits: `IDetailCustomization`
- L51 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L53 _public function_ `FDetailsViewCustomization()`
- L57 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperEditorModule.h` (Private)


#### class `FRigMapperEditorModule`  
`class FRigMapperEditorModule : public IModuleInterface`  
_L22-58_
- inherits: `IModuleInterface`
- desc: FRigMapperEditorModule The Editor Module for the Rig Mapper plugin
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `static void RegisterRigMapperDefinitionContextMenuEntries();`
- L31 _public prototype_ `static void RegisterRigMapperDefinitionToolbarEntries();`
- L32 _public prototype_ `static void RegisterRigMapperLinkedDefinitionsContextMenuEntries();`
- L33 _public prototype_ `static void RegisterRigMapperLinkedDefinitionsToolbarEntries();`
- L36 _private prototype_ `void RegisterSlateStyle();`
- L37 _private prototype_ `static bool GetUserPickedPath(FString& OutPath, bool bImport = true);`
- L38 _private prototype_ `static void LoadFromJson(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L39 _private prototype_ `static void ExportToJson(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L40 _private prototype_ `static void ValidateDefinition(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L41 _private prototype_ `static void BakeDefinitions(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L42 _private prototype_ `static void ValidateLinkedDefinitions(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L43 _private prototype_ `static void PopulateInputNodesFromMesh(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L44 _private prototype_ `static void PopulateOutputNodesFromMesh(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L45 _private prototype_ `static TArray<URigMapperDefinition*> GetDefinitionsFromContext(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L46 _private prototype_ `static TArray<URigMapperLinkedDefinitions*> GetLinkedDefinitionsFromContext(const FToolMenuContext& ToolMenuContext, bool bFromAssetEditor);`
- L49 _public member_ `static const FName AppIdentifier;`
- L50 _public member_ `static const FName MessageLogIdentifier;`
- L53 _private member_ `TSharedPtr<FSlateStyleSet> Style;`
- L55 _private member_ `TSharedPtr<FRigMapperDefinitionAssetTypeActions> RigMapperDefinitionAssetTypeActions;`
- L56 _private member_ `TSharedPtr<FRigMapperLinkedDefinitionsAssetTypeActions> RigMapperLinkedDefinitionsAssetTypeActions;`
- L57 _private member_ `TSharedPtr<FGraphPanelNodeFactory> RigMapperDefinitionGraphEditorNodeFactory;`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/RigMapperDefinitionEditorGraph.h` (Private)


#### class `URigMapperDefinitionEditorGraph`  
`class URigMapperDefinitionEditorGraph : public UEdGraph`  
_L22-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L27 _public prototype_ `void Initialize(URigMapperDefinition* InDefinition);`
- L29 _public member_ `FOnGraphStructureUpdated OnGraphStructureUpdated;`
- L30 _public member_ `FOnFocusNodeRequested OnFocusNodeRequested;`
- L37 _public prototype_ `void ApplyToDefinition();` — Applies graph nodes state to definition, discarding the previous state. Intended to call only on save and close so it does not call Modify() in order not to dirty the state of Definition again. If needed elsewhere, in order to preserve the undo stack, call Modify outside this method.
- L38 _public prototype_ `void RebuildGraph();`
- L39 _public function_ `void RequestRefreshLayout(bool bInRefreshLayout)`
- L40 _public function_ `bool NeedsRefreshLayout() const`
- L41 _public prototype_ `void LayoutNodes() const;`
- L43 _public function_ `URigMapperDefinition* GetDefinition() const`
- L45 _public prototype_ `void GetExistingNodeNames(const ERigMapperFeatureType InNodeType, TArray<FString>& OutExistingNames);`
- L47 _public prototype_ `URigMapperDefinitionEditorGraphNode* CreateGraphNode(const ERigMapperFeatureType InNodeType, UEdGraphPin* InFromPin, const FVector2f& InLocation, bool bSelectNewNode = true, const FString InDesiredNodeName = TEXT(""));`
- L48 _public prototype_ `TArray<URigMapperDefinitionEditorGraphNode*> GetNodesByName(const TArray<FString>& Inputs, const TArray<FString>& Features, const TArray<FString>& Outputs, const TArray<FString>& NullOutputs) const;`
- L50 _public prototype_ `URigMapperDefinitionEditorGraphNode* FindFeatureNodeByName(const FString& InNodeName);` — Retrieves first feature node that matches the InNodeName (assumes node names are unique and includes input nodes)
- L52 _public prototype_ `URigMapperDefinitionEditorGraphNode* FindOutputNodeByName(const FString& InNodeName);` — Retrieves first output node that matches the InNodeName (assumes output node names are unique and includes nulloutput nodes)
- L54 _public prototype_ `TArray<FString> GetNodesByType(ERigMapperFeatureType InNodeType) const;` — Retrieves all names of requested type nodes
- L56 _public prototype_ `bool UpdateNodeNameInMap(const FString& InOldName, const FString& InNewName, const ERigMapperFeatureType InNodeType);` — Updates the key in the node map when the node is renamed (assumes new name is unique)
- L58 _public prototype_ `bool RemoveNodeFromMap(const FString& InNodeName, const ERigMapperFeatureType InNodeType);` — Removes node from the map when deleted
- L60 _public prototype_ `void RebuildNodeMaps();` — Rebuilds node map from graph nodes
- L62 _public prototype_ `FVector2D GetNextNodeSlotPosition(ERigMapperFeatureType InNodeType) const;` — Gets the next available node position. Input types are placed in the input column; all other types in the output column.
- L64 _public prototype_ `FVector2D GetNextNodeSlotPositionFromNode(const URigMapperDefinitionEditorGraphNode* InNode) const;` — Gets the position for the next node below the given node
- L67 _private prototype_ `void ConstructNodes();`
- L68 _private prototype_ `void RemoveAllNodes();`
- L69 _private prototype_ `URigMapperDefinitionEditorGraphNode* ConstructGraphNode(const FString& NodeName, const ERigMapperFeatureType NodeType);`
- L70 _private prototype_ `URigMapperDefinitionEditorGraphNode* ConstructGraphNodesRec(URigMapperDefinition* Definition, const FString& InNodeName, bool bIsOutputNode);`
- L71 _private prototype_ `URigMapperDefinitionEditorGraphNode* ConstructOutputNode(URigMapperDefinition* Definition, const FString& NodeName);`
- L72 _private prototype_ `URigMapperDefinitionEditorGraphNode* ConstructFeatureNode(URigMapperDefinition* Definition, const FString& NodeName);`
- L73 _private prototype_ `static void LinkGraphNodes(URigMapperDefinitionEditorGraphNode* InNode, URigMapperDefinitionEditorGraphNode* OutNode);`
- L74 _private prototype_ `void LayoutNodeRec(URigMapperDefinitionEditorGraphNode* InNode, double InputsWidth, double PosY, TArray<URigMapperDefinitionEditorGraphNode*>& LayedOutNodes) const;`
- L76 _private prototype_ `void AddNodeToMap(const ERigMapperFeatureType NodeType, const FString& NodeName, URigMapperDefinitionEditorGraphNode* Node);`
- L79 _private member_ `TWeakObjectPtr<URigMapperDefinition> WeakDefinition;`
- L80 _private member_ `TMap<FString, URigMapperDefinitionEditorGraphNode*> InputNodes;`
- L81 _private member_ `TMap<FString, URigMapperDefinitionEditorGraphNode*> SDKNodes;`
- L82 _private member_ `TMap<FString, URigMapperDefinitionEditorGraphNode*> WSNodes;`
- L83 _private member_ `TMap<FString, URigMapperDefinitionEditorGraphNode*> MultiplyNodes;`
- L84 _private member_ `TMap<FString, URigMapperDefinitionEditorGraphNode*> MathNodes;`
- L85 _private member_ `TMap<FString, URigMapperDefinitionEditorGraphNode*> OutputNodes;`
- L86 _private member_ `TMap<FString, URigMapperDefinitionEditorGraphNode*> NullOutputNodes;`
- L88 _private member_ `bool bRefreshLayout = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGMAPPEREDITOR_API`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGraphStructureUpdated);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGraphStructureUpdated);`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFocusNodeRequested, URigMapperDefinitionEditorGraphNode*);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFocusNodeRequested, URigMapperDefinitionEditorGraphNode*);`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/RigMapperDefinitionEditorGraphNode.h` (Private)


#### class `URigMapperDefinitionEditorGraphNode`  
`class URigMapperDefinitionEditorGraphNode : public UEdGraphNode`  
_L18-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L29 _public member_ `FString NodeName;` — `UPROPERTY(EditAnywhere, Category = "Rig Mapper", meta = (DisplayPriority = 0))`
- L32 _public function_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override` — UEdGraphNode implementation
- L33 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L34 _public function_ `virtual FLinearColor GetNodeBodyTintColor() const override`
- L35 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L36 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L37 _public prototype_ `void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L38 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L39 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& Event) override;`
- L40 _public prototype_ `virtual void PostLoad() override;`
- L43 _public function_ `virtual void LoadFromFeature(const FRigMapperFeature* InFeature)`
- L44 _public function_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const`
- L45 _public prototype_ `void SetupNode(const FString& InNodeName, ERigMapperFeatureType InNodeType);`
- L47 _public function_ `ERigMapperFeatureType GetNodeType() const`
- L49 _public function_ `const FText& GetSubtitle() const`
- L51 _public function_ `virtual int32 GetMinInputPinCount() const`
- L52 _public function_ `virtual int32 GetMaxInputPinCount() const` — unlimited by default
- L53 _public function_ `virtual int32 GetInputPinCount() const`
- L54 _public function_ `virtual FString GetNodeNameFromInputPin(int32 PinIndex) const`
- L56 _public prototype_ `virtual void UpdateNodeFields();` — Updates node body
- L57 _public prototype_ `UEdGraphPin* CreateInputPin();`
- L58 _public prototype_ `UEdGraphPin* CreateOutputPin();`
- L59 _public prototype_ `bool RemoveInputPin(UEdGraphPin* InPinToRemove);`
- L60 _public function_ `const TArray<UEdGraphPin*>& GetInputPins() const`
- L61 _public function_ `UEdGraphPin* GetOutputPin() const`
- L63 _public function_ `void SetDimensions(const FVector2D& InDimensions)`
- L64 _public function_ `const FVector2D& GetDimensions() const`
- L66 _public function_ `void SetMargin(const FVector2D& InDMargin)`
- L67 _public function_ `const FVector2D& GetMargin() const`
- L69 _public prototype_ `void GetRect(FVector2D& TopLeft, FVector2D& BottomRight) const;`
- L71 _public prototype_ `void RelinkFeature(const FString& InNewInput, UEdGraphPin* InputPin);`
- L72 _public prototype_ `void AddNewInputLink(const FString& InNewInput);`
- L73 _public prototype_ `void RemoveLinksToFeature(const FString& InFeatureName);`
- L77 _protected member_ `FText NodeTitle;` — Cached title for the node
- L80 _protected member_ `FText NodeSubtitle;` — Cached subtitle for the node
- L83 _protected member_ `TArray<UEdGraphPin*> InputPins;` — Our input pins
- L86 _protected member_ `TArray<UEdGraphPin*> OutputPins;` — Our output pins
- L89 _protected member_ `FVector2D Dimensions = { 300, 50 };` — Cached dimensions of this node (used for layout)
- L92 _protected member_ `FVector2D Margin = { 0, 0 };` — Cached dimensions of this node (used for layout)
- L95 _protected member_ `ERigMapperFeatureType NodeType;` — `UPROPERTY()`
- L97 _protected member_ `FString PreviousNodeName;`

#### class `URigMapperDefinitionEditorGraphNode::NodeFactory`  
`class NodeFactory : public FGraphPanelNodeFactory`  
_L23-26_
- inherits: `FGraphPanelNodeFactory`
- L25 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;`

#### class `URigMapperDefinitionEditorGraphNode_Input`  
`class URigMapperDefinitionEditorGraphNode_Input : public URigMapperDefinitionEditorGraphNode`  
_L101-109_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigMapperDefinitionEditorGraphNode`
- L106 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L108 _public prototype_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const override;`

#### struct `FRigMapperWsInput`  
`struct FRigMapperWsInput`  
_L112-127_
- reflection: `USTRUCT(BlueprintType)`
- L117 _public function_ `FRigMapperWsInput()`
- L119 _public function_ `explicit FRigMapperWsInput(const FString& InName, const double InWeight) : Name(InName), Weight(InWeight)`
- L123 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rig Mapper")`
- L126 _public member_ `double Weight = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rig Mapper")`

#### class `URigMapperDefinitionEditorGraphNode_WeightedSum`  
`class URigMapperDefinitionEditorGraphNode_WeightedSum : public URigMapperDefinitionEditorGraphNode`  
_L130-154_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigMapperDefinitionEditorGraphNode`
- L136 _public member_ `TArray<FRigMapperWsInput> WeightedInputs;` — `UPROPERTY(EditAnywhere, Category = "Rig Mapper", meta = (DisplayPriority = 1))`
- L139 _public member_ `FRigMapperFeatureRange Range;` — `UPROPERTY(EditAnywhere, Category = "Rig Mapper", meta = (DisplayPriority = 1))`
- L141 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L143 _public prototype_ `virtual void LoadFromFeature(const FRigMapperFeature* InFeature) override;`
- L145 _public prototype_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const override;`
- L147 _public prototype_ `virtual void UpdateNodeFields() override;`
- L149 _public function_ `virtual int32 GetMinInputPinCount() const`
- L151 _public function_ `virtual int32 GetInputPinCount() const override`
- L153 _public prototype_ `virtual FString GetNodeNameFromInputPin(int32 PinIndex) const override;`

#### class `URigMapperDefinitionEditorGraphNode_SDK`  
`class URigMapperDefinitionEditorGraphNode_SDK : public URigMapperDefinitionEditorGraphNode`  
_L157-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigMapperDefinitionEditorGraphNode`
- L163 _public member_ `TArray<FRigMapperSdkKey> Keys;` — `UPROPERTY(EditAnywhere, Category = "Rig Mapper", meta = (DisplayPriority = 1))`
- L165 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L167 _public prototype_ `virtual void LoadFromFeature(const FRigMapperFeature* InFeature) override;`
- L169 _public prototype_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const override;`
- L171 _public prototype_ `virtual void UpdateNodeFields() override;`

#### class `URigMapperDefinitionEditorGraphNode_Multiply`  
`class URigMapperDefinitionEditorGraphNode_Multiply : public URigMapperDefinitionEditorGraphNode`  
_L176-188_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigMapperDefinitionEditorGraphNode`
- L181 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L183 _public prototype_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const override;`
- L185 _public prototype_ `virtual void UpdateNodeFields() override;`
- L187 _public function_ `virtual int32 GetMinInputPinCount() const override`

#### class `URigMapperDefinitionEditorGraphNode_MathOp`  
`class URigMapperDefinitionEditorGraphNode_MathOp : public URigMapperDefinitionEditorGraphNode`  
_L191-215_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigMapperDefinitionEditorGraphNode`
- L197 _public member_ `ERigMapperMathOperation Operation = ERigMapperMathOperation::Min;` — `UPROPERTY(EditAnywhere, Category = "Rig Mapper", meta = (DisplayPriority = 1))`
- L200 _public member_ `TArray<FRigMapperMathInput> Inputs;` — `UPROPERTY(EditAnywhere, Category = "Rig Mapper", meta = (DisplayPriority = 2))`
- L202 _public prototype_ `virtual void LoadFromFeature(const FRigMapperFeature* InFeature) override;`
- L204 _public prototype_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const override;`
- L206 _public prototype_ `virtual void UpdateNodeFields() override;`
- L208 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L210 _public prototype_ `virtual int32 GetMinInputPinCount() const override;`
- L212 _public function_ `virtual int32 GetInputPinCount() const override`
- L214 _public prototype_ `virtual FString GetNodeNameFromInputPin(int32 PinIndex) const override;`

#### class `URigMapperDefinitionEditorGraphNode_Output`  
`class URigMapperDefinitionEditorGraphNode_Output : public URigMapperDefinitionEditorGraphNode`  
_L218-226_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigMapperDefinitionEditorGraphNode`
- L223 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L225 _public prototype_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const override;`

#### class `URigMapperDefinitionEditorGraphNode_NullOutput`  
`class URigMapperDefinitionEditorGraphNode_NullOutput : public URigMapperDefinitionEditorGraphNode`  
_L229-237_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigMapperDefinitionEditorGraphNode`
- L234 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L236 _public prototype_ `virtual void ApplyToDefinition(URigMapperDefinition* OutDefinition) const override;`

#### class `URigMapperCommentNode`  
`class URigMapperCommentNode : public UEdGraphNode_Comment`  
_L240-246_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode_Comment`
- L245 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;` — This is needed because CachedCommentTitle is never updated after OnRenameNode like in Blueprint graphs where the Blueprint modification chain triggers automatically.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/RigMapperDefinitionEditorGraphSchema.h` (Private)


#### struct `FSchemaAction_SpawnRigMapperNode`  
`struct FSchemaAction_SpawnRigMapperNode : public FEdGraphSchemaAction`  
_L17-31_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L22 _public prototype_ `FSchemaAction_SpawnRigMapperNode();`
- L24 _public prototype_ `FSchemaAction_SpawnRigMapperNode(ERigMapperFeatureType InNodeType, const FText& InCategory, const FText& InDescription, const FText& InTooltip, const int InGrouping);`
- L27 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L30 _private member_ `ERigMapperFeatureType NodeType;`

#### struct `FSchemaAction_AddRigMapperComment`  
`struct FSchemaAction_AddRigMapperComment : public FEdGraphSchemaAction`  
_L35-45_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a 'comment' node to the graph
- L40 _public function_ `FSchemaAction_AddRigMapperComment()`
- L41 _public function_ `FSchemaAction_AddRigMapperComment(const FText& InCategory, const FText& InDescription, const FText& InTooltip) : FEdGraphSchemaAction(InCategory, InDescription, InTooltip, 0)`
- L44 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### class `URigMapperDefinitionEditorGraphSchema`  
`class URigMapperDefinitionEditorGraphSchema : public UEdGraphSchema`  
_L51-113_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L75 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UEdGraphSchema interface
- L76 _public function_ `virtual FName GetParentContextMenuName() const override`
- L77 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L78 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;`
- L79 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L80 _public prototype_ `virtual FPinConnectionResponse MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove = false, bool bNotifyLinkedNodes = false) const override;`
- L81 _public prototype_ `virtual FPinConnectionResponse CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy = false) const override;`
- L82 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L83 _public function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L84 _public prototype_ `virtual FPinConnectionResponse CanCreateNewNodes(UEdGraphPin* InSourcePin) const override;`
- L85 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;`
- L86 _public prototype_ `void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L87 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* InA, const UEdGraphPin* InB) const override;`
- L88 _public prototype_ `bool TryCreateConnection(UEdGraphPin* InA, UEdGraphPin* InB) const override;`
- L89 _public prototype_ `bool IsConnectionRelinkingAllowed(UEdGraphPin* InPin) const override;`
- L90 _public prototype_ `const FPinConnectionResponse CanRelinkConnectionToPin(const UEdGraphPin* OldSourcePin, const UEdGraphPin* TargetPinCandidate) const override;`
- L91 _public prototype_ `bool CreatePromotedConnection(UEdGraphPin* InA, UEdGraphPin* InB) const override;`
- L92 _public prototype_ `UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;`
- L93 _public prototype_ `void SetPinBeingDroppedOnNode(UEdGraphPin* InSourcePin) const override;`
- L94 _public prototype_ `bool TryRelinkConnectionTarget(UEdGraphPin* SourcePin, UEdGraphPin* OldTargetPin, UEdGraphPin* NewTargetPin, const TArray<UEdGraphNode*>& InSelectedGraphNodes) const override;`
- L95 _public prototype_ `bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* Node) const override;`
- L96 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;`
- L104 _public prototype_ `static URigMapperCommentNode* CreateCommentNode( UEdGraph* InParentGraph, const FVector2f& InLocation, const TArray<UEdGraphNode*>& InSelectedNodes, bool bInSelectNewNode = true);` — Creates a comment node on the graph. If SelectedNodes is not empty, sizes the comment to enclose them and ignores Location. Otherwise places at Location with default size.
- L112 _private member_ `mutable FString PinBeingDroppedNodeName = TEXT("");` — The name of the owning node of the pin that is being dropped on another node during a drag-drop operation. Controlled by SupportsDropPinOnNode().

#### class `URigMapperDefinitionEditorGraphSchema::ConnectionDrawingPolicy`  
`class ConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L56-72_
- inherits: `FConnectionDrawingPolicy`
- L59 _public function_ `ConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements) : FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements)`
- L67 _public function_ `virtual FVector2f ComputeSplineTangent(const FVector2f& Start, const FVector2f& End) const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/RigMapperGraphCommands.h` (Private)


#### class `FRigMapperGraphCommands`  
`class FRigMapperGraphCommands : public TCommands<FRigMapperGraphCommands>`  
_L9-24_
- inherits: `TCommands<FRigMapperGraphCommands>`
- L12 _public function_ `FRigMapperGraphCommands() : TCommands<FRigMapperGraphCommands>( TEXT("RigMapperGraph"), NSLOCTEXT("RigMapperDefinitionGraphCommands", "RigMapperDefinitionGraphCommands", "Rig Mapper Graph commands"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L20 _public member_ `TSharedPtr<FUICommandInfo> FocusConnectedNodes;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> CreateComment;`
- L23 _public prototype_ `virtual void RegisterCommands() override;`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/SRigMapperDefinitionGraphEditor.h` (Private)


#### class `SRigMapperDefinitionGraphEditor`  
`class SRigMapperDefinitionGraphEditor : public SCompoundWidget`  
_L19-86_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SRigMapperDefinitionGraphEditor)`
- L28 _public prototype_ `virtual ~SRigMapperDefinitionGraphEditor() override;`
- L31 _public prototype_ `void Construct(const FArguments& InArgs, URigMapperDefinition* InDefinition);` — Constructs this widget with InArgs
- L33 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L35 _public prototype_ `void SelectNodes(const TArray<FString>& Inputs, const TArray<FString>& Features, const TArray<FString>& Outputs, const TArray<FString>& NullOutputs);`
- L36 _public prototype_ `void RebuildGraph();`
- L37 _public prototype_ `void RefreshGraphNode(URigMapperDefinitionEditorGraphNode* InNode);`
- L38 _public prototype_ `void CaptureKeyboard();`
- L40 _public function_ `TSharedPtr<SRigMapperValidationBanner> GetValidationBanner() const`
- L45 _public function_ `TObjectPtr<URigMapperDefinitionEditorGraph> GetEditorGraphObject() const`
- L51 _private prototype_ `void ZoomToFitNodes(const TArray<URigMapperDefinitionEditorGraphNode*>& SelectedNodes) const;`
- L52 _private prototype_ `static void GetAllLinkedNodes(const URigMapperDefinitionEditorGraphNode* BaseNode, TArray<URigMapperDefinitionEditorGraphNode*>& LinkedNodes, bool bDescend);`
- L53 _private prototype_ `void HandleSelectionChanged(const TSet<UObject*>& Nodes);`
- L54 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L56 _private prototype_ `void BindCommands();`
- L57 _private prototype_ `void OnDeleteSelectedNodes();`
- L58 _private prototype_ `bool CanDeleteNodes();`
- L60 _private prototype_ `void SetFocusOnNode(URigMapperDefinitionEditorGraphNode* InNode);`
- L61 _private prototype_ `void ClearFocusMode();`
- L62 _private prototype_ `void ApplyFocusOpacity();`
- L63 _private prototype_ `void OnToggleFocusMode();`
- L64 _private prototype_ `void OnCreateComment();`
- L67 _public member_ `SGraphEditor::FOnSelectionChanged OnSelectionChanged;`
- L70 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;`
- L71 _private member_ `TObjectPtr<URigMapperDefinitionEditorGraph> GraphObj;`
- L73 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Commands that are bound to delegates
- L74 _private member_ `TSharedPtr<SRigMapperValidationBanner> ValidationBanner;`
- L77 _private member_ `bool bFocusMode = false;` — Designates if focus mode is on
- L79 _private member_ `TSet<URigMapperDefinitionEditorGraphNode*> FocusedNodes;` — Nodes connected in the single chain focused by the user
- L81 _private member_ `bool bSelectingNodes = false;`
- L83 _private member_ `bool bFocusLinkedNodes = true;`
- L85 _private member_ `bool bDeferZoom = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/SRigMapperDefinitionGraphEditorNode.h` (Private)


#### class `SRigMapperDefinitionGraphEditorNode`  
`class SRigMapperDefinitionGraphEditorNode : public SGraphNode`  
_L15-39_
- inherits: `SGraphNode`
- L18 _public function_ `SLATE_BEGIN_ARGS(SRigMapperDefinitionGraphEditorNode)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, URigMapperDefinitionEditorGraphNode* InNode);`
- L26 _public prototype_ `void CreatePinWidgets() override;`
- L29 _protected prototype_ `FSlateColor GetNodeColor() const;`
- L30 _protected prototype_ `FText GetNodeTitle() const;`
- L31 _protected prototype_ `FText GetNodeSubtitle() const;`
- L32 _protected function_ `EVisibility GetShowNodeSubtitle() const`
- L35 _protected prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L36 _protected prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L37 _protected prototype_ `TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L38 _protected prototype_ `void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/SRigMapperDefinitionStructureView.h` (Private)


#### class `SRigMapperDefinitionStructureView`  
`class SRigMapperDefinitionStructureView : public SCompoundWidget`  
_L19-82_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SRigMapperDefinitionStructureView)`
- L28 _public prototype_ `DECLARE_DELEGATE_FiveParams(FOnSelectionChanged, ESelectInfo::Type, TArray<FString>, TArray<FString>, TArray<FString>, TArray<FString>);`
- L31 _public prototype_ `void Construct(const FArguments& InArgs, URigMapperDefinitionEditorGraph* InGraph);` — Constructs this widget with InArgs
- L33 _public prototype_ `bool SelectNode(const FString& NodeName, ERigMapperFeatureType NodeType, bool bSelected);`
- L34 _public prototype_ `void RebuildTree();`
- L35 _public prototype_ `void ClearSelection() const;`
- L36 _public prototype_ `bool IsNodeOrChildSelected(ERigMapperFeatureType NodeType, int32 ArrayIndex) const;`
- L37 _public prototype_ `bool IsSelectionEmpty() const;`
- L40 _public member_ `FOnSelectionChanged OnSelectionChanged;`
- L43 _private prototype_ `void GenerateParentNodes();`
- L44 _private prototype_ `void GenerateChildrenNodes();`
- L45 _private prototype_ `void HandleTreeNodesSelectionChanged(TSharedPtr<FString> Node, ESelectInfo::Type SelectInfo);`
- L46 _private prototype_ `void TransformElementToString(TSharedPtr<FString> String, TArray<FString>& Strings);`
- L47 _private prototype_ `void OnFilterTextChanged(const FText& Text);`
- L48 _private prototype_ `void FilterNodes(const TArray<TSharedPtr<FString>>& ParentNodes, TArray<TSharedPtr<FString>>& FilteredNodes);`
- L50 _private prototype_ `TSharedRef<ITableRow> OnGenerateTreeRow(TSharedPtr<FString> NodeName, const TSharedRef<STableViewBase>& TableViewBase);`
- L51 _private prototype_ `void OnGetTreeNodeChildren(TSharedPtr<FString> NodeName, TArray<TSharedPtr<FString>>& Children);`
- L53 _private prototype_ `TSharedPtr<FString> GetParentAndChildrenNodes(ERigMapperFeatureType NodeType, TArray<TSharedPtr<FString>>& OutChildren);`
- L54 _private prototype_ `TArray<TSharedPtr<FString>>* GetChildrenNodes(ERigMapperFeatureType NodeType);`
- L55 _private prototype_ `const TArray<TSharedPtr<FString>>* GetChildrenNodes(ERigMapperFeatureType NodeType) const;`
- L58 _private member_ `static const int32 NumNodeTypes;`
- L59 _private member_ `static const int32 NumFeatureTypes;`
- L61 _private member_ `static const FString InputsNodeName;`
- L62 _private member_ `static const FString FeaturesNodeName;`
- L63 _private member_ `static const FString MultiplyNodeName;`
- L64 _private member_ `static const FString MathNodeName;`
- L65 _private member_ `static const FString WsNodeName;`
- L66 _private member_ `static const FString SdkNodeName;`
- L67 _private member_ `static const FString OutputNodeName;`
- L68 _private member_ `static const FString NullOutputNodeName;`
- L70 _private member_ `TWeakObjectPtr<URigMapperDefinitionEditorGraph> Graph;`
- L72 _private member_ `TSharedPtr<STreeView<TSharedPtr<FString>>> TreeView;`
- L74 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L75 _private member_ `TSharedPtr<TTextFilter<TSharedPtr<FString>>> SearchBoxFilter;`
- L77 _private member_ `TArray<TSharedPtr<FString>> RootNodes;`
- L78 _private member_ `TArray<TSharedPtr<FString>> FilteredRootNodes;`
- L80 _private member_ `TMap<TSharedPtr<FString>, TArray<TSharedPtr<FString>>> ParentsAndChildrenNodes;`
- L81 _private member_ `TMap<ERigMapperFeatureType, TSharedPtr<FString>> ParentNodesMapping;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGMAPPEREDITOR_API`
- L28 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnSelectionChanged, ESelectInfo::Type, TArray<FString>, TArray<FString>, TArray<FString>, TArray<FString>);`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperGraph/SRigMapperValidationBanner.h` (Private)


#### enum `ERigMapperValidationBannerState`  
`enum class ERigMapperValidationBannerState : uint8`  
_L9-15_
- L11 _public enumerator_ `Hidden`
- L12 _public enumerator_ `Success`
- L13 _public enumerator_ `Warning`
- L14 _public enumerator_ `Error`

#### class `SRigMapperValidationBanner`  
`class SRigMapperValidationBanner : public SCompoundWidget`  
_L17-44_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SRigMapperValidationBanner)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `void SetValidationResult(const FRigMapperValidationContext& InContext);`
- L26 _public prototype_ `void Clear();`
- L29 _private prototype_ `EVisibility GetBannerVisibility() const;`
- L30 _private prototype_ `FSlateColor GetBannerColor() const;`
- L31 _private prototype_ `const FSlateBrush* GetStatusIcon() const;`
- L32 _private prototype_ `FText GetSummaryText() const;`
- L33 _private prototype_ `FText GetDetailText() const;`
- L34 _private prototype_ `EVisibility GetDetailVisibility() const;`
- L35 _private prototype_ `EVisibility GetShowLogVisibility() const;`
- L37 _private prototype_ `FReply OnDismissClicked();`
- L38 _private prototype_ `FReply OnShowLogClicked();`
- L39 _private prototype_ `FReply OnToggleDetailClicked();`
- L41 _private member_ `ERigMapperValidationBannerState State = ERigMapperValidationBannerState::Hidden;`
- L42 _private member_ `FRigMapperValidationContext CachedContext;`
- L43 _private member_ `bool bDetailExpanded = false;`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Private/RigMapperLinkedDefinitionsAssetTypeActions.h` (Private)


#### class `FRigMapperLinkedDefinitionsAssetTypeActions`  
`class FRigMapperLinkedDefinitionsAssetTypeActions : public FAssetTypeActions_Base`  
_L13-20_
- inherits: `FAssetTypeActions_Base`
- desc: The asset actions for the URigMapperLinkedDefinitions data asset class and link to its asset editor toolkit
- L16 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L17 _public prototype_ `virtual FText GetName() const override;`
- L18 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L19 _public prototype_ `virtual uint32 GetCategories() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Public/AnimGraphNode_RigMapper.h` (Public)


#### class `UAnimGraphNode_RigMapper`  
`class UAnimGraphNode_RigMapper : public UAnimGraphNode_Base`  
_L17-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L23 _public member_ `FAnimNode_RigMapper Node;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L27 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L28 _public prototype_ `virtual FText GetTooltipText() const override;`
- L29 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L30 _public prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L34 _public prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;` — UAnimGraphNode_Base interface
- L35 _public prototype_ `virtual FEditorModeID GetEditorMode() const override;`
- L36 _public prototype_ `virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;`
- L37 _public prototype_ `virtual void CopyNodeDataToPreviewNode(FAnimNode_Base* InPreviewNode) override;`
- L38 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGMAPPEREDITOR_API`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Public/RigMapperEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigMapperEditor, Log, All);`

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperEditor/Public/RigMapperEditorSubsystem.h` (Public)


#### class `URigMapperEditorSubsystem`  
`class URigMapperEditorSubsystem : public UEditorSubsystem`  
_L29-184_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: URigMapperEditorSubsystem Subsystem to remap animation from/to all kinds of formats using the Rig Mapper API.
- L39 _public prototype_ `static bool ConvertCsv(const FFilePath& InputFile, const FFilePath& OutputFile, const TArray<URigMapperDefinition*>& Definitions, bool bOutputIntermediateCsvFiles = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Remap a CSV file using the given definitions, and optionally outputting separate files for each definition's output The following header is expected at the first line of the CSV file: curve_name, frame_number, value
- L47 _public prototype_ `static bool ConvertCsvToAnimSequence(const FFilePath& InputFile, UAnimSequence* Target, const TArray<URigMapperDefinition*>& Definitions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Import a CSV file to an existing anim sequence, remapping it using the given definitions The following header is expected at the first line of the CSV file: curve_name, frame_number, value The target sequence rate will be unchanged (see SetAnimSequenceRate if required)
- L54 _public prototype_ `static UAnimSequence* ConvertCsvToAnimSequenceNew(const FFilePath& InputFile, USkeletalMesh* TargetMesh, const TArray<URigMapperDefinition*>& Definitions, const FFrameRate& FrameRate, const FDirectoryPath& NewAssetPath, const FName NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Import a CSV file to a new anim sequence asset, remapping it using the given definitions The following header is expected at the first line of the CSV file: curve_name, frame_number, value
- L63 _public prototype_ `static bool ConvertCsvToControlRigSection(const FFilePath& InputFile, UMovieSceneControlRigParameterSection* Target, const TArray<URigMapperDefinition*>& Definitions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Import a CSV file to the given control rig section, remapping it using the given definitions The following header is expected at the first line of the CSV file: curve_name, frame_number, value Control Rig transform/vector2d/float channels are currently supported The target sequence rate will be unchanged
- L71 _public prototype_ `static UMovieSceneControlRigParameterSection* ConvertCsvToControlRigSectionNew(const FFilePath& InputFile, USkeletalMesh* TargetMesh, const TArray<URigMapperDefinition*>& Definitions, const FFrameRate& FrameRate, const TSubclassOf<UControlRig>& ControlRigClass, const FDirectoryPath& NewAssetPath, const FName NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Import a CSV file to a control rig section in a new Level Sqeuence, remapping it using the given definitions The following header is expected at the first line of the CSV file: curve_name, frame_number, value Control Rig transform/vector2d/float channels are currently supported
- L78 _public prototype_ `static bool ConvertAnimSequence(const UAnimSequence* Source, UAnimSequence* Target, const TArray<URigMapperDefinition*>& Definitions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Remap an anim sequence to another existing one, remapping it using the given definitions The target sequence rate will be unchanged (see SetAnimSequenceRate if required)
- L84 _public prototype_ `static UAnimSequence* ConvertAnimSequenceNew(const UAnimSequence* Source, USkeletalMesh* TargetMesh, const TArray<URigMapperDefinition*>& Definitions, const FDirectoryPath& NewAssetPath, const FName NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Remap an anim sequence to a new one, remapping it using the given definitions
- L90 _public prototype_ `static bool ConvertAnimSequenceToCsv(const UAnimSequence* Source, const FFilePath& OutputFile, const TArray<URigMapperDefinition*>& Definitions, bool bOutputIntermediateCsvFiles = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Export a CSV file from an anim sequence, remapping it using the given definitions
- L98 _public prototype_ `static bool ConvertAnimSequenceToControlRigSection(const UAnimSequence* Source, UMovieSceneControlRigParameterSection* Target, const TArray<URigMapperDefinition*>& Definitions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Convert an AnimSequence to an existing Control Rig section, remapping it using the given definitions Control Rig transform/vector2d/float channels are currently supported The target sequence rate will be unchanged
- L105 _public prototype_ `static UMovieSceneControlRigParameterSection* ConvertAnimSequenceToControlRigSectionNew(const UAnimSequence* Source, USkeletalMesh* TargetMesh, const TArray<URigMapperDefinition*>& Definitions, const TSubclassOf<UControlRig>& ControlRigClass, const FDirectoryPath& NewAssetPath, const FName NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Convert an AnimSequence to a Control Rig section in a new Level Sequence, remapping it using the given definitions Control Rig transform/vector2d/float channels are currently supported
- L113 _public prototype_ `static bool ConvertControlRigSection(const UMovieSceneControlRigParameterSection* Source, UMovieSceneControlRigParameterSection* Target, const TArray<URigMapperDefinition*>& Definitions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Convert a Control Rig section to another existing one, remapping it using the given definitions Control Rig transform/vector2d/float channels are currently supported The target sequence rate will be unchanged
- L120 _public prototype_ `static UMovieSceneControlRigParameterSection* ConvertControlRigSectionNew(const UMovieSceneControlRigParameterSection* Source, USkeletalMesh* TargetMesh, const TArray<URigMapperDefinition*>& Definitions, const TSubclassOf<UControlRig>& ControlRigClass, const FDirectoryPath& NewAssetPath, const FName NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Convert a Control Rig section to a section in a new Level Sequence, remapping it using the given definitions Control Rig transform/vector2d/float channels are currently supported
- L126 _public prototype_ `static bool ConvertControlRigSectionToCsv(const UMovieSceneControlRigParameterSection* Source, const FFilePath& OutputFile, const TArray<URigMapperDefinition*>& Definitions, bool bOutputIntermediateCsvFiles = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Export a CSV file from a Control Rig Section, remapping it using the given definitions
- L133 _public prototype_ `static bool ConvertControlRigSectionToAnimSequence(const UMovieSceneControlRigParameterSection* Source, UAnimSequence* Target, const TArray<URigMapperDefinition*>& Definitions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Convert a Control Rig section to an existing AnimSequence, remapping it using the given definitions The target sequence rate will be unchanged
- L139 _public prototype_ `static UAnimSequence* ConvertControlRigSectionToAnimSequenceNew(const UMovieSceneControlRigParameterSection* Source, USkeletalMesh* TargetMesh, const TArray<URigMapperDefinition*>& Definitions, const FDirectoryPath& NewAssetPath, const FName NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")` — Convert a Control Rig section to a new AnimSequence asset, remapping it using the given definitions
- L142 _public prototype_ `static ULevelSequence* GetSequenceFromSection(const UMovieSceneControlRigParameterSection* Section);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")`
- L145 _public prototype_ `static TArray<UMovieSceneControlRigParameterSection*> GetSectionsFromSequence(ULevelSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")`
- L148 _public prototype_ `static FFrameRate GetAnimSequenceRate(const UAnimSequence* AnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")`
- L151 _public prototype_ `static void SetAnimSequenceRate(UAnimSequence* AnimSequence, FFrameRate FrameRate, bool bSetImportProperties);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting|Animation|Rig Mapper")`
- L153 _public typedef_ `using FFrameValues = TArray<FRigMapperProcessor::FPoseValues>;`
- L157 _public prototype_ `static bool LoadCurveValuesFromAnimSequence(const UAnimSequence* InSource, const USkeleton* InSourceSkeleton, TArray<FName>& OutCurveNames, TArray<FFrameTime>& OutFrameTimes, FFrameValues& OutCurveValuesPerFrame, TArray<int32> & OutCurveFlags, TArray<FLinearColor> & OutCurveColors);` — Load curve values from animation sequence (not blueprint callable)
- L161 _private typedef_ `using FFramePoses = TArray<FRigMapperProcessor::FPose>;`
- L163 _private prototype_ `static bool ConvertCurveValuesToCsv(TArray<FString>& CurveNames, const TArray<FFrameTime>& FrameTimes, FFrameValues& CurveValuesPerFrame, const FFilePath& OutputFile, const TArray<URigMapperDefinition*>& Definitions, bool bOutputIntermediateCsvFiles);`
- L165 _private prototype_ `static bool WriteCurveValuesToCsv(const FFilePath& OutputFile, const TArray<FString>& CurveNames, const TArray<FFrameTime>& FrameTimes, const FFrameValues& CurveValuesPerFrame);`
- L167 _private prototype_ `static bool LoadCurveValuesFromCsv(const FFilePath& InputFile, TArray<FString>& CurveNames, TArray<FFrameTime>& FrameTimes, FFrameValues& CurveValuesPerFrame);`
- L169 _private prototype_ `static bool ConvertCurveValuesToAnimSequence(TArray<FString>& CurveNames, const TArray<FFrameTime>& FrameTimes, FFrameValues& CurveValuesPerFrame, UAnimSequence* Target, const TArray<URigMapperDefinition*>& Definitions);`
- L171 _private prototype_ `static bool AddCurveValuesToAnimSequence(UAnimSequence* Target, const TArray<FString>& CurveNames, const TArray<FFrameTime>& FrameTimes, const FFrameValues& CurveValuesPerFrame);`
- L173 _private prototype_ `static bool LoadCurveValuesFromAnimSequence(const UAnimSequence* Source, TArray<FString>& CurveNames, TArray<FFrameTime>& FrameTimes, FFrameValues& CurveValuesPerFrame);`
- L175 _private prototype_ `static bool ConvertCurveValuesToControlRigSection(TArray<FString>& CurveNames, const TArray<FFrameTime>& FrameTimes, FFrameValues& CurveValuesPerFrame, UMovieSceneControlRigParameterSection* Target, const TArray<URigMapperDefinition*>& Definitions);`
- L177 _private prototype_ `static bool AddCurveValuesToControlRigSection(UMovieSceneControlRigParameterSection* Target, const TArray<FString>& CurveNames, const TArray<FFrameTime>& FrameTimes, const FFrameValues& CurveValuesPerFrame);`
- L179 _private prototype_ `static bool LoadCurveValuesFromControlRigSection(const UMovieSceneControlRigParameterSection* Source, TArray<FString>& CurveNames, TArray<FFrameTime>& FrameTimes, FFrameValues& CurveValuesPerFrame, const TArray<FString>& InputNames);`
- L181 _private prototype_ `static bool BakeSparseKeys(const FFramePoses& Poses, const TArray<FString>& CurveNames, TArray<FFrameTime>& FrameTimes, FFrameValues& CurveValuesPerFrame);`
- L183 _private prototype_ `static void SparseBakeCurve(const FString& CurveName, int32 CurveIndex, float CurveValue, FFrameValues& CurveValuesPerFrame, const TArray<FFrameTime>& FrameTimesInOrder, int32 FrameIndex, const FFramePoses& Poses, const TArray<FFrameTime>& FrameTimes, const int32 ActualFrameIndex);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API RIGMAPPEREDITOR_API`
