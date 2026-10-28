# Editor / AIGraph

- module root: `Source/Editor/AIGraph`
- headers: 10; symbols: 272
- symbol kinds: class=11, delegate=1, function=15, macro=9, member=48, prototype=181, struct=6, typedef=1
- DynamicallyLoadedModuleNames: AssetRegistry
- PrivateDependencyModuleNames: AIModule, ApplicationCore, BlueprintGraph, Core, GraphEditor, InputCore, Slate, SlateCore, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry
- PublicDependencyModuleNames: CoreUObject, Engine

### `Source/Editor/AIGraph/Classes/AIGraph.h` (Public)


#### class `UAIGraph`  
`class UAIGraph : public UEdGraph`  
_L21-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L26 _private member_ `int32 GraphVersion;` — `UPROPERTY()`
- L28 _private prototype_ `virtual void OnCreated();`
- L29 _private prototype_ `virtual void OnLoaded();`
- L30 _private prototype_ `virtual void Initialize();`
- L32 _private prototype_ `virtual void UpdateAsset(int32 UpdateFlags = 0);`
- L33 _private prototype_ `virtual void UpdateVersion();`
- L34 _private prototype_ `virtual void MarkVersion();`
- L36 _private prototype_ `virtual void OnSubNodeDropped();`
- L37 _private prototype_ `virtual void OnNodesPasted(const FString& ImportStr);`
- L39 _private prototype_ `bool UpdateUnknownNodeClasses();`
- L42 _private prototype_ `void UpdateDeprecatedClasses();` — `UE_DEPRECATED(5.6, "This method was only used to fetch error messages and log them. It has been renamed to better fit its purpose. Use UpdateErrorMessages instead.")`
- L45 _private prototype_ `void UpdateErrorMessages();` — Sets error messages and logs errors about nodes.
- L46 _private prototype_ `void RemoveOrphanedNodes();`
- L47 _private prototype_ `void UpdateClassData();`
- L49 _private prototype_ `bool IsLocked() const;`
- L50 _private prototype_ `void LockUpdates();`
- L51 _private prototype_ `void UnlockUpdates();`
- L54 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L62 _protected member_ `uint32 bLockUpdates : 1;` — if set, graph modifications won't cause updates in internal tree structure flag allows freezing update during heavy changes like pasting new nodes
- L64 _protected prototype_ `virtual void CollectAllNodeInstances(TSet<UObject*>& NodeInstances);`
- L65 _protected prototype_ `virtual bool CanRemoveNestedObject(UObject* TestObject) const;`
- L66 _protected prototype_ `virtual void OnNodeInstanceRemoved(UObject* NodeInstance);`
- L68 _protected prototype_ `UEdGraphPin* FindGraphNodePin(UEdGraphNode* Node, EEdGraphPinDirection Dir);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AIGRAPH_API`

### `Source/Editor/AIGraph/Classes/AIGraphNode.h` (Public)


#### class `UAIGraphNode`  
`class UAIGraphNode : public UEdGraphNode`  
_L20-122_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L26 _private member_ `struct FGraphNodeClassData ClassData;` — `UPROPERTY()` — instance class
- L29 _private member_ `TObjectPtr<UObject> NodeInstance;` — `UPROPERTY()`
- L32 _private member_ `TObjectPtr<UAIGraphNode> ParentNode;` — `UPROPERTY(transient)`
- L35 _private member_ `TArray<TObjectPtr<UAIGraphNode>> SubNodes;` — `UPROPERTY()`
- L39 _private member_ `int32 CopySubNodeIndex;` — `UPROPERTY()` — subnode index assigned during copy operation to connect nodes again on paste
- L43 _private member_ `uint32 bIsReadOnly : 1;` — `UPROPERTY()` — if set, all modifications (including delete/cut) are disabled
- L47 _private member_ `uint32 bIsSubNode : 1;` — `UPROPERTY()` — if set, this node will be always considered as subnode
- L51 _private member_ `FString ErrorMessage;` — `UPROPERTY()` — error message for node
- L54 _private prototype_ `virtual class UAIGraph* GetAIGraph();`
- L55 _private prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L56 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L57 _private prototype_ `virtual void PrepareForCopying() override;`
- L58 _private prototype_ `virtual bool CanDuplicateNode() const override;`
- L59 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L60 _private prototype_ `virtual void DestroyNode() override;`
- L61 _private prototype_ `virtual FText GetTooltipText() const override;`
- L62 _private prototype_ `virtual void NodeConnectionListChanged() override;`
- L63 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;`
- L64 _private prototype_ `virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results) override;`
- L65 _private prototype_ `virtual FString GetPropertyNameAndValueForDiff(const FProperty* Prop, const uint8* PropertyAddr) const override;`
- L70 _private prototype_ `virtual void PostEditImport() override;`
- L71 _private prototype_ `virtual void PostEditUndo() override;`
- L76 _private prototype_ `virtual UEdGraphPin* GetInputPin(int32 InputIndex = 0) const;` — @return the input pin for this state
- L78 _private prototype_ `virtual UEdGraphPin* GetOutputPin(int32 InputIndex = 0) const;` — @return the output pin for this state
- L79 _private function_ `virtual UEdGraph* GetBoundGraph() const`
- L81 _private prototype_ `virtual FText GetDescription() const;`
- L82 _private prototype_ `virtual void PostCopyNode();`
- L84 _private prototype_ `void AddSubNode(UAIGraphNode* SubNode, class UEdGraph* ParentGraph);`
- L85 _private prototype_ `void RemoveSubNode(UAIGraphNode* SubNode);`
- L86 _private prototype_ `virtual void RemoveAllSubNodes();`
- L87 _private prototype_ `virtual void OnSubNodeRemoved(UAIGraphNode* SubNode);`
- L88 _private prototype_ `virtual void OnSubNodeAdded(UAIGraphNode* SubNode);`
- L90 _private prototype_ `virtual int32 FindSubNodeDropIndex(UAIGraphNode* SubNode) const;`
- L91 _private prototype_ `virtual void InsertSubNodeAt(UAIGraphNode* SubNode, int32 DropIndex);`
- L94 _private prototype_ `virtual bool IsSubNode() const;` — check if node is subnode
- L97 _private prototype_ `virtual void InitializeInstance();` — initialize instance object
- L100 _private prototype_ `virtual bool RefreshNodeClass();` — reinitialize node instance
- L103 _private prototype_ `virtual void UpdateNodeClassData();` — updates ClassData from node instance
- L109 _private prototype_ `virtual void UpdateErrorMessage();` — Checks for any errors in this node and updates ErrorMessage with any resulting message Called every time the graph is serialized (i.e. loaded, saved, execution index changed, etc)
- L112 _private prototype_ `bool UsesBlueprint() const;` — Check if node instance uses blueprint for its implementation
- L115 _private prototype_ `virtual bool HasErrors() const;` — check if node has any errors, used for assigning colors on graph
- L117 _private prototype_ `static void UpdateNodeClassDataFrom(UClass* InstanceClass, FGraphNodeClassData& UpdatedData);`
- L121 _protected prototype_ `virtual void ResetNodeOwner();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AIGRAPH_API`

### `Source/Editor/AIGraph/Classes/AIGraphSchema.h` (Public)


#### struct `FAISchemaAction_AddComment`  
`struct FAISchemaAction_AddComment : public FEdGraphSchemaAction`  
_L18-31_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a comment to the graph
- L22 _public function_ `FAISchemaAction_AddComment() : FEdGraphSchemaAction()`
- L23 _public function_ `FAISchemaAction_AddComment(FText InDescription, FText InToolTip) : FEdGraphSchemaAction(FText(), MoveTemp(InDescription), MoveTemp(InToolTip), 0)`
- L29 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override final;` — FEdGraphSchemaAction interface

#### struct `FAISchemaAction_NewNode`  
`struct FAISchemaAction_NewNode : public FEdGraphSchemaAction`  
_L35-58_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L41 _public member_ `TObjectPtr<class UAIGraphNode> NodeTemplate;` — `UPROPERTY()` — Template of node we want to create
- L43 _public function_ `FAISchemaAction_NewNode() : FEdGraphSchemaAction() , NodeTemplate(nullptr)`
- L48 _public function_ `FAISchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , NodeTemplate(nullptr)`
- L54 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L55 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L56 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### struct `FAISchemaAction_NewSubNode`  
`struct FAISchemaAction_NewSubNode : public FEdGraphSchemaAction`  
_L62-91_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a subnode to the selected node
- L68 _public member_ `TObjectPtr<class UAIGraphNode> NodeTemplate;` — `UPROPERTY()` — Template of node we want to create
- L72 _public member_ `TObjectPtr<class UAIGraphNode> ParentNode;` — `UPROPERTY()` — parent node
- L74 _public function_ `FAISchemaAction_NewSubNode() : FEdGraphSchemaAction() , NodeTemplate(nullptr) , ParentNode(nullptr)`
- L80 _public function_ `FAISchemaAction_NewSubNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , NodeTemplate(nullptr) , ParentNode(nullptr)`
- L87 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L88 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L89 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### class `UAIGraphSchema`  
`class UAIGraphSchema : public UEdGraphSchema`  
_L94-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L99 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L100 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L101 _private prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L102 _private prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L103 _private prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L104 _private prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;`
- L105 _private prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L106 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;`
- L107 _private prototype_ `virtual int32 GetNodeSelectionCount(const UEdGraph* Graph) const override;`
- L110 _private prototype_ `virtual void GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, int32 SubNodeFlags) const;`
- L111 _private prototype_ `virtual void GetSubNodeClasses(int32 SubNodeFlags, TArray<FGraphNodeClassData>& ClassData, UClass*& GraphNodeClass) const;`
- L115 _protected prototype_ `static TSharedPtr<FAISchemaAction_NewNode> AddNewNodeAction(FGraphActionListBuilderBase& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip);`
- L116 _protected prototype_ `static TSharedPtr<FAISchemaAction_NewSubNode> AddNewSubNodeAction(FGraphActionListBuilderBase& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AIGRAPH_API`

### `Source/Editor/AIGraph/Classes/AIGraphTypes.h` (Public)


#### struct `FGraphNodeClassData`  
`struct FGraphNodeClassData`  
_L13-63_
- reflection: `USTRUCT()`
- L17 _public function_ `FGraphNodeClassData()`
- L18 _public prototype_ `FGraphNodeClassData(UClass* InClass, const FString& InDeprecatedMessage);`
- L19 _public prototype_ `FGraphNodeClassData(const FTopLevelAssetPath& InGeneratedClassPath, UClass* InClass);`
- L20 _public prototype_ `FGraphNodeClassData(const FString& InAssetName, const FString& InGeneratedClassPackage, const FString& InClassName, UClass* InClass);`
- L22 _public prototype_ `FString ToString() const;`
- L23 _public prototype_ `FString GetClassName() const;`
- L24 _public prototype_ `FText GetCategory() const;`
- L25 _public prototype_ `FString GetDisplayName() const;`
- L26 _public prototype_ `FText GetTooltip() const;`
- L27 _public prototype_ `UClass* GetClass(bool bSilent = false);`
- L28 _public prototype_ `bool IsAbstract() const;`
- L30 _public function_ `FORCEINLINE bool IsBlueprint() const`
- L31 _public function_ `FORCEINLINE bool IsDeprecated() const`
- L32 _public function_ `FORCEINLINE FString GetDeprecatedMessage() const`
- L33 _public function_ `FORCEINLINE FString GetPackageName() const`
- L36 _public member_ `uint32 bIsHidden : 1;` — set when child class masked this one out (e.g. always use game specific class instead of engine one)
- L39 _public member_ `uint32 bHideParent : 1;` — set when class wants to hide parent class from selection (just one class up hierarchy)
- L44 _private member_ `TWeakObjectPtr<UClass> Class;` — pointer to uclass
- L48 _private member_ `FString AssetName;` — `UPROPERTY()` — path to class if it's not loaded yet
- L51 _private member_ `FString GeneratedClassPackage;` — `UPROPERTY()`
- L55 _private member_ `FString ClassName;` — `UPROPERTY()` — resolved name of class from asset data
- L59 _private member_ `FText Category;` — `UPROPERTY()` — User-defined category for this class
- L62 _private member_ `FString DeprecatedMessage;` — message for deprecated class

#### struct `FGraphNodeClassNode`  
`struct FGraphNodeClassNode`  
_L65-74_
- L67 _public member_ `FGraphNodeClassData Data;`
- L68 _public member_ `FString ParentClassName;`
- L70 _public member_ `TSharedPtr<FGraphNodeClassNode> ParentNode;`
- L71 _public member_ `TArray<TSharedPtr<FGraphNodeClassNode> > SubNodes;`
- L73 _public prototype_ `void AddUniqueSubNode(TSharedPtr<FGraphNodeClassNode> SubNode);`

#### struct `FGraphNodeClassHelper`  
`struct FGraphNodeClassHelper`  
_L76-126_
- L78 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPackageListUpdated);`
- L80 _public prototype_ `FGraphNodeClassHelper(UClass* InRootClass);`
- L81 _public prototype_ `~FGraphNodeClassHelper();`
- L83 _public prototype_ `void GatherClasses(const UClass* BaseClass, TArray<FGraphNodeClassData>& AvailableClasses);`
- L84 _public prototype_ `static FString GetDeprecationMessage(const UClass* Class);`
- L86 _public prototype_ `void OnAssetAdded(const struct FAssetData& AssetData);`
- L87 _public prototype_ `void OnAssetRemoved(const struct FAssetData& AssetData);`
- L88 _public prototype_ `void InvalidateCache();`
- L89 _public prototype_ `void OnReloadComplete(EReloadCompleteReason Reason);`
- L91 _public prototype_ `static void AddUnknownClass(const FGraphNodeClassData& ClassData);`
- L92 _public prototype_ `static bool IsClassKnown(const FGraphNodeClassData& ClassData);`
- L93 _public member_ `static FOnPackageListUpdated OnPackageListUpdated;`
- L95 _public prototype_ `static int32 GetObservedBlueprintClassCount(UClass* BaseNativeClass);`
- L96 _public prototype_ `static void AddObservedBlueprintClasses(UClass* BaseNativeClass);`
- L97 _public prototype_ `void UpdateAvailableBlueprintClasses();`
- L100 _public prototype_ `void AddForcedHiddenClass(UClass* Class);` — Adds a single class to the list of hidden classes
- L103 _public prototype_ `void SetForcedHiddenClasses(const TSet<UClass*>& Classes);` — Overrides all previously set hidden classes
- L105 _public prototype_ `void SetGatherBlueprints(bool bGather);`
- L109 _private member_ `UClass* RootNodeClass;`
- L110 _private member_ `TSharedPtr<FGraphNodeClassNode> RootNode;`
- L111 _private member_ `static TArray<FName> UnknownPackages;`
- L112 _private member_ `static TMap<UClass*, int32> BlueprintClassCount;`
- L113 _private member_ `TSet<UClass*> ForcedHiddenClasses;`
- L114 _private member_ `bool bGatherBlueprints = true;`
- L116 _private prototype_ `TSharedPtr<FGraphNodeClassNode> CreateClassDataNode(const struct FAssetData& AssetData);`
- L117 _private prototype_ `TSharedPtr<FGraphNodeClassNode> FindBaseClassNode(TSharedPtr<FGraphNodeClassNode> Node, const FString& ClassName);`
- L118 _private prototype_ `void FindAllSubClasses(TSharedPtr<FGraphNodeClassNode> Node, TArray<FGraphNodeClassData>& AvailableClasses);`
- L120 _private prototype_ `void BuildClassGraph();`
- L121 _private prototype_ `void AddClassGraphChildren(TSharedPtr<FGraphNodeClassNode> Node, TArray<TSharedPtr<FGraphNodeClassNode> >& NodeList);`
- L123 _private prototype_ `bool IsHidingClass(UClass* Class);`
- L124 _private prototype_ `bool IsHidingParentClass(UClass* Class);`
- L125 _private prototype_ `bool IsPackageSaved(FName PackageName);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AIGRAPH_API`
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPackageListUpdated);`

### `Source/Editor/AIGraph/Public/AIGraphConnectionDrawingPolicy.h` (Public)


#### class `FAIGraphConnectionDrawingPolicy`  
`class FAIGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L26-46_
- inherits: `FConnectionDrawingPolicy`
- L29 _protected member_ `UEdGraph* GraphObj;`
- L30 _protected member_ `TMap<UEdGraphNode*, int32> NodeWidgetMap;`
- L33 _public prototype_ `FAIGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L36 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface
- L37 _public prototype_ `virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& PinGeometries, FArrangedChildren& ArrangedNodes) override;`
- L38 _public prototype_ `virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params) override;`
- L39 _public prototype_ `virtual void DrawSplineWithArrow(const FVector2f& StartPoint, const FVector2f& EndPoint, const FConnectionParams& Params) override;`
- L40 _public prototype_ `virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2f& StartPoint, const FVector2f& EndPoint, UEdGraphPin* Pin) override;`
- L41 _public prototype_ `virtual FVector2f ComputeSplineTangent(const FVector2f& Start, const FVector2f& End) const override;`
- L45 _protected prototype_ `void Internal_DrawLineWithArrow(const UE::Slate::FDeprecateVector2DParameter& StartAnchorPoint, const UE::Slate::FDeprecateVector2DParameter& EndAnchorPoint, const FConnectionParams& Params);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AIGRAPH_API`

### `Source/Editor/AIGraph/Public/AIGraphEditor.h` (Public)


#### class `FAIGraphEditor`  
`class FAIGraphEditor : public FEditorUndoClient`  
_L11-62_
- inherits: `FEditorUndoClient`
- L14 _public prototype_ `FAIGraphEditor();`
- L15 _public prototype_ `virtual ~FAIGraphEditor();`
- L17 _public prototype_ `FGraphPanelSelectionSet GetSelectedNodes() const;`
- L18 _public prototype_ `virtual void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);`
- L21 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L22 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L25 _public prototype_ `void CreateCommandList();`
- L28 _public prototype_ `void SelectAllNodes();` — Delegates for graph editor commands
- L29 _public prototype_ `bool CanSelectAllNodes() const;`
- L30 _public prototype_ `void DeleteSelectedNodes();`
- L31 _public prototype_ `bool CanDeleteNodes() const;`
- L32 _public prototype_ `void DeleteSelectedDuplicatableNodes();`
- L33 _public prototype_ `void CutSelectedNodes();`
- L34 _public prototype_ `bool CanCutNodes() const;`
- L35 _public prototype_ `void CopySelectedNodes();`
- L36 _public prototype_ `bool CanCopyNodes() const;`
- L37 _public prototype_ `void PasteNodes();`
- L38 _public prototype_ `void PasteNodesHere(const FVector2D& Location);`
- L39 _public prototype_ `bool CanPasteNodes() const;`
- L40 _public prototype_ `void DuplicateNodes();`
- L41 _public prototype_ `bool CanDuplicateNodes() const;`
- L43 _public prototype_ `bool CanCreateComment() const;`
- L44 _public prototype_ `void OnCreateComment();`
- L47 _public prototype_ `virtual void OnClassListUpdated();`
- L50 _protected prototype_ `virtual void FixupPastedNodes(const TSet<UEdGraphNode*>& NewPastedGraphNodes, const TMap<FGuid , FGuid >& NewToOldNodeMapping);`
- L55 _protected member_ `TWeakPtr<SGraphEditor> UpdateGraphEdPtr;` — Currently focused graph
- L58 _protected member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — The command list for this editor
- L61 _protected member_ `FDelegateHandle OnClassListUpdatedDelegateHandle;` — Handle to the registered OnClassListUpdated delegate

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AIGRAPH_API`

### `Source/Editor/AIGraph/Public/AIGraphModule.h` (Public)


#### class `FAIGraphModule`  
`class FAIGraphModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAIGraph, Display, All);`

### `Source/Editor/AIGraph/Public/K2Node_AIMoveTo.h` (Public)


#### class `UK2Node_AIMoveTo`  
`class UK2Node_AIMoveTo : public UK2Node_BaseAsyncTask`  
_L19-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseAsyncTask`
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L29 _private prototype_ `virtual FText GetMenuCategory() const override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AIGRAPH_API`

### `Source/Editor/AIGraph/Public/SGraphEditorActionMenuAI.h` (Public)


#### class `SGraphEditorActionMenuAI`  
`class SGraphEditorActionMenuAI : public SBorder`  
_L28-69_
- inherits: `SBorder`
- L31 _public function_ `SLATE_BEGIN_ARGS(SGraphEditorActionMenuAI) : _GraphObj( static_cast<UEdGraph*>(NULL) ) ,_GraphNode(NULL) , _NewNodePosition( FVector2D::ZeroVector ) , _AutoExpandActionMenu( false ) , _SubNodeFlags(0)`
- L39 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( UAIGraphNode*, GraphNode) SLATE_ARGUMENT( FVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_ARGUMENT( bool, AutoExpandActionMenu ) SLATE_ARGUMENT( int32, SubNodeFlags) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L50 _public prototype_ `~SGraphEditorActionMenuAI();`
- L52 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();`
- L55 _protected member_ `UEdGraph* GraphObj;`
- L56 _protected member_ `UAIGraphNode* GraphNode;`
- L57 _protected member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L58 _protected member_ `FVector2D NewNodePosition;`
- L59 _protected member_ `bool AutoExpandActionMenu;`
- L60 _protected member_ `int32 SubNodeFlags;`
- L62 _protected member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L63 _protected member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L65 _protected prototype_ `void OnActionSelected( const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedAction, ESelectInfo::Type InSelectionType );`
- L68 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AIGRAPH_API`

### `Source/Editor/AIGraph/Public/SGraphNodeAI.h` (Public)


#### class `FDragAIGraphNode`  
`class FDragAIGraphNode : public FDragNode`  
_L22-36_
- inherits: `FDragNode`
- L25 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDragAIGraphNode, FDragNode) static TSharedRef<FDragAIGraphNode> New(const TSharedRef<SGraphPanel>& InGraphPanel, const TSharedRef<SGraphNode>& InDraggedNode);`
- L28 _public prototype_ `static TSharedRef<FDragAIGraphNode> New(const TSharedRef<SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphNode> >& InDraggedNodes);`
- L30 _public prototype_ `UAIGraphNode* GetDropTargetNode() const;`
- L32 _public member_ `double StartTime;`
- L35 _protected typedef_ `typedef FDragNode Super;`

#### class `SGraphNodeAI`  
`class SGraphNodeAI : public SGraphNode`  
_L38-83_
- inherits: `SGraphNode`
- L41 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeAI)`
- L42 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAIGraphNode* InNode);`
- L47 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L48 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L49 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L50 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L51 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L52 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent) override;`
- L53 _public prototype_ `virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;`
- L54 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L58 _public prototype_ `FReply OnMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);` — handle mouse down on the node
- L61 _public prototype_ `virtual void AddSubNode(TSharedPtr<SGraphNode> SubNodeWidget);` — adds subnode widget inside current node
- L64 _public prototype_ `TSharedPtr<SGraphNode> GetSubNodeUnderCursor(const FGeometry& WidgetGeometry, const FPointerEvent& MouseEvent);` — gets decorator or service node if one is found under mouse cursor
- L67 _public prototype_ `EVisibility GetDragOverMarkerVisibility() const;` — gets drag over marker visibility
- L70 _public prototype_ `void SetDragMarker(bool bEnabled);` — sets drag marker visible or collapsed on this node
- L73 _protected member_ `TArray< TSharedPtr<SGraphNode> > SubNodes;`
- L75 _protected member_ `uint32 bDragMarkerVisible : 1;`
- L77 _protected prototype_ `virtual FText GetTitle() const;`
- L78 _protected prototype_ `virtual FText GetDescription() const;`
- L79 _protected prototype_ `virtual EVisibility GetDescriptionVisibility() const;`
- L81 _protected prototype_ `virtual FText GetPreviewCornerText() const;`
- L82 _protected prototype_ `virtual const FSlateBrush* GetNameIcon() const;`

#### class `SGraphPinAI`  
`class SGraphPinAI : public SGraphPin`  
_L85-99_
- inherits: `SGraphPin`
- L88 _public function_ `SLATE_BEGIN_ARGS(SGraphPinAI)`
- L89 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L94 _protected prototype_ `virtual FSlateColor GetPinColor() const override;`
- L95 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L98 _protected prototype_ `const FSlateBrush* GetPinBorder() const;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AIGRAPH_API`
