# Plugins / BlueprintSnapNodes

- module root: `Plugins/Experimental/BlueprintSnapNodes/Source/BlueprintSnapNodes`
- headers: 4; symbols: 47
- symbol kinds: class=5, function=5, member=8, prototype=28, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: BlueprintGraph, CoreUObject, EditorFramework, EditorStyle, Engine, GraphEditor, InputCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/BlueprintSnapNodes/Source/BlueprintSnapNodes/Private/K2Node_SnapContainer.h` (Private)


#### class `UK2Node_SnapContainer`  
`class UK2Node_SnapContainer : public UK2Node_Composite`  
_L13-51_
- reflection: `UCLASS()`
- inherits: `UK2Node_Composite`
- desc: @TODO: Write a comment
- L19 _public member_ `TObjectPtr<UK2Node> RootNode;` — `UPROPERTY()`
- L22 _public prototype_ `UK2Node_SnapContainer(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L29 _public prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L31 _public prototype_ `virtual void ReconstructNode() override;`
- L32 _public prototype_ `virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results) override;`
- L33 _public function_ `virtual bool ShouldMergeChildGraphs() const override`
- L34 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L35 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L36 _public prototype_ `virtual FText GetKeywords() const override;`
- L40 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L41 _public function_ `virtual bool IsNodePure() const`
- L45 _public function_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override`
- L50 _private member_ `TSharedPtr<class FCompilerResultsLog> CachedMessageLog;` — Cached so we don't have to regenerate it when the graph is recompiled

### `Plugins/Experimental/BlueprintSnapNodes/Source/BlueprintSnapNodes/Private/SGraphNodeSnapContainer.h` (Private)


#### class `SGraphNodeSnapContainer`  
`class SGraphNodeSnapContainer : public SGraphNodeK2Base`  
_L11-32_
- inherits: `SGraphNodeK2Base`
- L14 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeSnapContainer)`
- L16 _public typedef_ `typedef SGraphNodeK2Base Super;`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, UK2Node_SnapContainer* InNode);`
- L21 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L22 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L25 _protected prototype_ `virtual UEdGraph* GetInnerGraph() const;`
- L28 _private prototype_ `FText GetPreviewCornerText() const;`
- L29 _private prototype_ `FText GetTooltipTextForNode() const;`
- L31 _private prototype_ `TSharedRef<SWidget> CreateNodeBody();`

### `Plugins/Experimental/BlueprintSnapNodes/Source/BlueprintSnapNodes/Private/SGraphSnapContainerRow.h` (Private)


#### class `FGraphSnapContainerBuilder`  
`class FGraphSnapContainerBuilder`  
_L17-31_
- L20 _public prototype_ `static TSharedRef<SWidget> CreateSnapContainerWidgets(UEdGraph* ModelGraph, UEdGraphNode* RootNode);`
- L23 _private prototype_ `FGraphSnapContainerBuilder(UEdGraph* InGraph);`
- L25 _private prototype_ `TSharedRef<SWidget> MakeNodeWidget(UEdGraphNode* Node, UEdGraphPin* FromPin);`
- L26 _private prototype_ `TSharedRef<SWidget> MakePinWidget(UEdGraphPin* Pin);`
- L27 _private prototype_ `TSharedRef<SWidget> MakeFunctionCallWidget(UK2Node* AnyNode);`
- L29 _private member_ `UEdGraph* Graph;`
- L30 _private member_ `TSet<const UEdGraphNode*> VisitedNodes;`

#### class `SGraphSnapContainerEntry`  
`class SGraphSnapContainerEntry : public SCompoundWidget`  
_L36-55_
- inherits: `SCompoundWidget`
- L39 _public function_ `SLATE_BEGIN_ARGS(SGraphSnapContainerEntry)`
- L40 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphNode* InNode, UEdGraphPin* InPin, TSharedPtr<SWidget> InChildWidget);`
- L45 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L46 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L47 _public prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() override;`
- L51 _private member_ `UEdGraphNode* TargetNode;`
- L52 _private member_ `UEdGraphPin* TargetPin;`
- L54 _private member_ `TSharedPtr<SGraphPin> DefaultValuePinWidget;`

### `Plugins/Experimental/BlueprintSnapNodes/Source/BlueprintSnapNodes/Public/BlueprintSnapNodes.h` (Public)


#### class `FBlueprintSnapNodesModule`  
`class FBlueprintSnapNodesModule : public IModuleInterface`  
_L10-21_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `TSharedPtr<FBlueprintSnapNodeWidgetFactory> NodeWidgetFactory;`
