# Plugins / UAFAnimGraphEditor

- module root: `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor`
- headers: 29; symbols: 459
- symbol kinds: class=33, delegate=6, enum=3, enumerator=9, externvar=2, function=45, macro=2, member=113, namespace=71, prototype=162, struct=13
- PrivateDependencyModuleNames: AssetDefinition, BlueprintGraph, CoreUObject, DeveloperSettings, EditorWidgets, Engine, GameplayInsights, GraphEditor, InputCore, Kismet, MessageLog, Persona, PropertyEditor, RewindDebuggerInterface, RigVM, RigVMDeveloper, RigVMEditor, Settings, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UAF, UAFAnimGraph, UAFAnimGraphUncookedOnly, UAFEditor, UAFUncookedOnly, UnrealEd, WorkspaceEditor
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Internal/Graph/AnimNextAnimationGraphFactory.h` (Internal)


#### class `UUAFAnimGraphFactory`  
`class UUAFAnimGraphFactory : public UFactory`  
_L10-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `UUAFAnimGraphFactory();`
- L16 _private prototype_ `virtual bool ConfigureProperties() override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L18 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/AnimGraphViewportController.h` (Private)


#### class `UE::UAF::Editor::FAnimGraphViewportController`  
`class FAnimGraphViewportController : public Workspace::IWorkspaceViewportController`  
_L9-15_
- inherits: `Workspace::IWorkspaceViewportController`
- L11 _private prototype_ `virtual void OnEnter(const FViewportContext& InViewportContext) override;`
- L12 _private prototype_ `virtual void OnExit(FAdvancedPreviewScene* PreviewScene) override;`
- L14 _private member_ `TArray<AActor*> PreviewActors;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/AssetPreview/UAFGraphAssetPreview.h` (Private)


#### struct `UE::UAF::Editor::FUAFGraphAssetPreviewFactory`  
`struct FUAFGraphAssetPreviewFactory : public FUAFAssetPreviewFactory`  
_L23-31_
- inherits: `FUAFAssetPreviewFactory`
- desc: Experimental. May be removed / relocated whenever we switch to the future generic content browser IAssetPreviewCustomization API. Factory for UAF Graph Asset Preview widgets.
- L28 _public prototype_ `virtual TSharedRef<IUAFAssetPreview> CreateAssetPreviewWidget(TSharedPtr<FAssetEditorToolkit> InAssetEditorToolkit, const FAssetData& InAssetData) const override;`
- L29 _public prototype_ `virtual const UStruct* GetPreviewType() const override;`

#### class `UE::UAF::Editor::SUAFGraphAssetPreview`  
`class SUAFGraphAssetPreview : public IUAFAssetViewportPreview`  
_L39-71_
- inherits: `IUAFAssetViewportPreview`
- desc: Experimental. May be removed / relocated whenever we switch to the future generic content browser IAssetPreviewCustomization API. Preview widget for UAF Graph Assets. Includes an interactable viewport. Currently these previews only work in a UAF workspace that has set it's preview skeletal mesh.
- L44 _public prototype_ `virtual const UStruct* GetAssetPreviewType() const override;`
- L50 _protected prototype_ `virtual bool OnSameTypeAssetSelected(const FAssetData& InAssetData) override;`
- L54 _protected prototype_ `virtual void OnCustomizePreviewScene(FAdvancedPreviewScene& InPreviewScene, FEditorViewportClient& InEditorViewportClient) override;`
- L60 _protected member_ `USkeletalMeshComponent* PreviewComponent = nullptr;` — Skeletal component to preview the animation asset on. Lifetime maintained by PreviewScene in IUAFAssetViewportPreview
- L63 _protected member_ `UUAFComponent* UAFComponent = nullptr;` — UAF Graph Preview Driver. Lifetime maintained by PreviewScene in IUAFAssetViewportPreview
- L70 _protected member_ `UUAFViewportSceneDescription* UAFSceneDescription = nullptr;` — Object used to describe UAF previews. Lifetime maintained by workspace editor. Currently we only acquire this by checking if the current editor is a workspace editor & acquiring it's viewport scene description.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Factory/AnimNextFactoryParamsDetails.h` (Private)


#### class `UE::UAF::Editor::FAnimNextFactoryParamsDetails`  
`class FAnimNextFactoryParamsDetails : public IPropertyTypeCustomization`  
_L10-17_
- inherits: `IPropertyTypeCustomization`
- L13 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L14 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L16 _private member_ `TSharedPtr<IPropertyHandle> TraitDescsHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/AnimNextAnimGraphEntryAssetDefinitions.h` (Private)


#### class `UAssetDefinition_AnimNextAnimationGraphEntry`  
`class UAssetDefinition_AnimNextAnimationGraphEntry : public UAssetDefinitionDefault`  
_L12-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition interface
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public prototype_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AnimNextAnimGraphEntryAssetDefinitions"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/AnimNextAnimationGraphAssetDefinition.h` (Private)


#### class `UAssetDefinition_AnimNextAnimationGraph`  
`class UAssetDefinition_AnimNextAnimationGraph : public UAssetDefinitionDefault`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition interface
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public function_ `virtual bool ShouldSaveExternalPackages() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AnimNextAssetDefinitions"`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/AnimNextAnimationGraphItemDetails.h` (Private)


#### class `UE::UAF::Editor::FAnimNextAnimationGraphItemDetails`  
`class FAnimNextAnimationGraphItemDetails : public FAnimNextAssetItemDetails`  
_L10-17_
- inherits: `FAnimNextAssetItemDetails`
- L13 _public prototype_ `FAnimNextAnimationGraphItemDetails() = default;`
- L15 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/AnimNextAnimationGraphMenuExtensions.h` (Private)


#### struct `UE::UAF::Editor::FAnimationGraphMenuExtensions`  
`struct FAnimationGraphMenuExtensions`  
_L15-19_
- L17 _public prototype_ `static void RegisterMenus();`
- L18 _public prototype_ `static void UnregisterMenus();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/AnimNextGraphDetails.h` (Private)


#### class `UE::UAF::Editor::FAnimNextGraphDetails`  
`class FAnimNextGraphDetails : public IPropertyTypeCustomization`  
_L10-15_
- inherits: `IPropertyTypeCustomization`
- L13 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L14 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/AnimNextGraphPanelNodeFactory.h` (Private)


#### class `FAnimNextGraphPanelNodeFactory`  
`class FAnimNextGraphPanelNodeFactory : public FGraphPanelNodeFactory`  
_L7-10_
- inherits: `FGraphPanelNodeFactory`
- L9 _private prototype_ `virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/AnimNextGraphPanelPinFactory.h` (Private)


#### class `FAnimNextGraphPanelPinFactory`  
`class FAnimNextGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L7-10_
- inherits: `FGraphPanelPinFactory`
- L9 _private prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(UEdGraphPin* Pin) const override;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/GraphNodeTemplateDetails.h` (Private)


#### class `UE::UAF::Editor::FGraphNodeTemplateDetails`  
`class FGraphNodeTemplateDetails : public IDetailCustomization`  
_L15-48_
- inherits: `IDetailCustomization`
- L18 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L20 _private prototype_ `const FRigVMNodeLayout* GetNodeLayout() const;`
- L21 _private prototype_ `TArray<FString> GetUncategorizedPins() const;`
- L22 _private prototype_ `TArray<FRigVMPinCategory> GetPinCategories() const;`
- L23 _private prototype_ `FString GetPinCategory(FString InPinPath) const;`
- L24 _private prototype_ `int32 GetPinIndexInCategory(FString InPinPath) const;`
- L25 _private prototype_ `FString GetPinLabel(FString InPinPath) const;`
- L26 _private prototype_ `FLinearColor GetPinColor(FString InPinPath) const;`
- L27 _private prototype_ `const FSlateBrush* GetPinIcon(FString InPinPath) const;`
- L28 _private prototype_ `void HandleCategoryAdded(FString InCategory);`
- L29 _private prototype_ `void HandleCategoryRemoved(FString InCategory);`
- L30 _private prototype_ `void HandleCategoryRenamed(FString InOldCategory, FString InNewCategory);`
- L31 _private prototype_ `void HandlePinCategoryChanged(FString InPinPath, FString InCategory);`
- L32 _private prototype_ `void HandlePinLabelChanged(FString InPinPath, FString InNewLabel);`
- L33 _private prototype_ `void HandlePinIndexInCategoryChanged(FString InPinPath, int32 InIndexInCategory);`
- L34 _private prototype_ `static bool ValidateName(FString InNewName, FText& OutErrorMessage);`
- L35 _private prototype_ `bool HandleValidateCategoryName(FString InCategoryPath, FString InNewName, FText& OutErrorMessage);`
- L36 _private prototype_ `bool HandleValidatePinDisplayName(FString InPinPath, FString InNewName, FText& OutErrorMessage);`
- L37 _private prototype_ `uint32 GetNodeLayoutHash() const;`
- L39 _private member_ `TWeakObjectPtr<UUAFGraphNodeTemplate> WeakTemplate;`
- L47 _private member_ `TArray<TUniquePtr<FCachedPinInfo>> CachedPinInfo;`

#### struct `UE::UAF::Editor::FGraphNodeTemplateDetails::FCachedPinInfo`  
`struct FCachedPinInfo`  
_L41-45_
- L43 _public member_ `FString PinName;`
- L44 _public member_ `FString PinCategory;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/PostProcessAnimationCustomization.h` (Private)


#### class `UE::UAF::Editor::FPostProcessAnimationCustomization`  
`class FPostProcessAnimationCustomization`  
_L12-19_
- L15 _public prototype_ `static bool OnShouldFilterPostProcessAnimation(const FAssetData& AssetData);`
- L16 _public prototype_ `static FString GetCurrentPostProcessAnimationPath(USkeletalMesh* SkeletalMesh);`
- L17 _public prototype_ `static void OnSetPostProcessAnimation(const FAssetData& AssetData, TStrongObjectPtr<USkeletalMesh> SkeletalMesh);`
- L18 _public prototype_ `static void OnCustomizeMeshDetails(IDetailLayoutBuilder& DetailLayout, TWeakObjectPtr<USkeletalMesh> SkeletalMeshWeak);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/SAnimNextGraphNode.h` (Private)


#### class `SAnimNextGraphNode`  
`class SAnimNextGraphNode : public SRigVMGraphNode`  
_L10-26_
- inherits: `SRigVMGraphNode`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAnimNextGraphNode) : _GraphNodeObj(nullptr)`
- L17 _public prototype_ `SLATE_ARGUMENT(UAnimNextEdGraphNode*, GraphNodeObj) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _private prototype_ `virtual TSharedRef<SWidget> CreateIconWidget() override;` — SGraphNode interface

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/STraitEditorView.h` (Private)


#### class `UE::UAF::Editor::STraitEditorView`  
`class STraitEditorView : public SCompoundWidget`  
_L38-86_
- inherits: `SCompoundWidget`
- L41 _public prototype_ `STraitEditorView();`
- L43 _public function_ `SLATE_BEGIN_ARGS(STraitEditorView)`
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<UE::Workspace::IWorkspaceEditor> InWorkspaceEditorWeak);`
- L49 _public prototype_ `void SetTraitData(const FTraitStackData& InTraitStackData);`
- L52 _private prototype_ `FReply OnTraitClicked(const FTraitUID InTraitClicked);`
- L53 _private prototype_ `FReply OnTraitDeleteRequest(const FTraitUID InTraitUIDToDelete);`
- L54 _private prototype_ `FReply OnStackTraitDragAccepted(const FTraitUID DraggedTraitUID, const FTraitUID TargetTraitUID, EItemDropZone DropZone);`
- L55 _private prototype_ `void ExecuteTraitDrag(const FTraitUID DraggedTraitUID, const FTraitUID TargetTraitUID, EItemDropZone DropZone);`
- L56 _private prototype_ `void OnStatckTraitSelectionChanged(const FTraitUID InTraitSelected);`
- L57 _private prototype_ `TWeakPtr<FTraitDataEditorDef> OnGetSelectedTraitData() const;`
- L59 _private prototype_ `void Refresh();`
- L60 _private prototype_ `void RefreshWidgets();`
- L61 _private prototype_ `void RefreshTraitStack();`
- L63 _private prototype_ `void OnRequestRefresh();`
- L64 _private prototype_ `void RefreshTraitStackTraitsStatus();`
- L65 _private prototype_ `void UpdateTraitStatusInStack(const TArray<TSharedPtr<FTraitDataEditorDef>>& CurrentTraitsData, int32 TraitIndex, TSharedPtr<FTraitDataEditorDef>& TraitData);`
- L67 _private prototype_ `TSharedRef<SWidget> GetOptionsMenuWidget();`
- L69 _private prototype_ `int32 GetTraitPinIndex(UAnimNextEdGraphNode* InEdGraphNode, const TSharedPtr<FTraitDataEditorDef>& InTraitData, int32 TraitIndex = INDEX_NONE);`
- L71 _private prototype_ `static void GenerateTraitStackData(const TWeakObjectPtr<UAnimNextEdGraphNode>& EdGraphNodeWeak, TSharedPtr<FTraitEditorSharedData>& InTraitEditorSharedData);`
- L73 _private member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WorkspaceEditorWeak;`
- L74 _private member_ `TSharedPtr<FTraitEditorSharedData> TraitEditorSharedData;`
- L76 _private member_ `TSharedPtr<STraitListView> TraitListWidget;`
- L77 _private member_ `TSharedPtr<STraitStackView> TraitStackWidget;`
- L79 _private member_ `TSharedPtr<FTraitDataEditorDef> StackSelectedTrait;`
- L81 _private member_ `TWeakPtr<IMessageLogListing> CompilerResultsListingWeak;`
- L83 _private member_ `FTraitUID SelectedTraitUID;`
- L84 _private member_ `bool bStackContainsErrors = false;`
- L85 _private member_ `bool bShowTraitInterfaces = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Workspace` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace UAF` (scope `UE`)
- L35 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/STraitHandlePin.h` (Private)


#### class `UE::UAF::STraitHandlePin`  
`class STraitHandlePin : public SGraphPin`  
_L22-37_
- inherits: `SGraphPin`
- L25 _public function_ `SLATE_BEGIN_ARGS(STraitHandlePin)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L32 _protected prototype_ `virtual const FSlateBrush* GetPinIcon() const override;`
- L35 _protected member_ `mutable const FSlateBrush* CachedImg_Pin_ConnectedHovered = nullptr;`
- L36 _protected member_ `mutable const FSlateBrush* CachedImg_Pin_DisconnectedHovered = nullptr;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/STraitListView.h` (Private)


#### class `UE::UAF::Editor::STraitListView`  
`class STraitListView : public SCompoundWidget`  
_L26-95_
- inherits: `SCompoundWidget`
- L30 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnTraitClicked, const FTraitUID);` — Used to notify the Trait Editor a Trait has been clicked on the available list
- L33 _public prototype_ `DECLARE_DELEGATE_RetVal(TWeakPtr<FTraitDataEditorDef>, FOnGetSelectedTraitData);` — Used to obtain the currently selected Trait in the Stack
- L36 _public function_ `SLATE_BEGIN_ARGS(STraitListView)`
- L38 _public prototype_ `SLATE_EVENT(FOnTraitClicked, OnTraitClicked) SLATE_EVENT(FOnGetSelectedTraitData, OnGetSelectedTraitData) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FTraitEditorSharedData>& InTraitEditorSharedData);`
- L46 _public prototype_ `void RefreshList();`
- L50 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L54 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L56 _private member_ `TSharedPtr<FTraitEditorSharedData> TraitEditorSharedData;`
- L58 _private member_ `TMap<FName, FTraitCategoryData> BaseTraitCategories;`
- L59 _private member_ `TMap<FName, FTraitCategoryData> AdditiveTraitCategories;`
- L61 _private member_ `TSharedPtr<FUICommandList> UICommandList;`
- L63 _private member_ `TSharedPtr< SSearchBox > TraitListFilterBox;`
- L64 _private member_ `TSharedPtr<STreeView<TSharedRef<FTraitListEntry>>> EntriesList;`
- L65 _private member_ `TArray<TSharedRef<FTraitListEntry>> Categories;`
- L67 _private member_ `FText FilterText;`
- L68 _private member_ `TArray<TSharedRef<FTraitListEntry>> FilteredEntries;`
- L70 _private member_ `TSet< TSharedRef<FTraitListEntry> > OldExpansionState;`
- L72 _private member_ `FOnTraitClicked OnTraitClicked;`
- L73 _private member_ `FOnGetSelectedTraitData OnGetSelectedTraitData;`
- L75 _private member_ `bool bIgnoreExpansion = false;`
- L78 _private prototype_ `bool HasValidEditorData() const;` — --- ---
- L79 _private prototype_ `TSharedPtr<FTraitDataEditorDef> GetSelectedTraitData() const;`
- L81 _private prototype_ `void StoreExpansionState();`
- L82 _private prototype_ `void RestoreExpansionState(TArray<TSharedRef<FTraitListEntry>>& AllEntries);`
- L83 _private prototype_ `void GetAllEntries(TArray<TSharedRef<FTraitListEntry>>& AllEntries) const;`
- L84 _private prototype_ `void ExpandAllCategories(const TArray<TSharedRef<FTraitListEntry>>& AllEntries);`
- L85 _private prototype_ `void RefreshEntries();`
- L86 _private prototype_ `void CreateTraitCategories(const FName& BaseCategoryName, const FText& BaseCategoryText, TMap<FName, FTraitCategoryData>& CategoriesMap);`
- L87 _private prototype_ `void RefreshFilter();`
- L89 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedRef<FTraitListEntry> InEntry, const TSharedRef<STableViewBase>& InOwnerTable);`
- L90 _private prototype_ `void HandleGetChildren(TSharedRef<FTraitListEntry> InEntry, TArray<TSharedRef<FTraitListEntry>>& OutChildren);`
- L91 _private prototype_ `void HandleItemScrolledIntoView(TSharedRef<FTraitListEntry> InEntry, const TSharedPtr<ITableRow>& InWidget);`
- L92 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FTraitListEntry> InEntry, ESelectInfo::Type InSelectionType);`
- L94 _private prototype_ `void GenerateTraitList();`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnTraitClicked, const FTraitUID);` — Used to notify the Trait Editor a Trait has been clicked on the available list
- L33 _delegate_ `DECLARE_DELEGATE_RetVal(TWeakPtr<FTraitDataEditorDef>, FOnGetSelectedTraitData);` — Used to obtain the currently selected Trait in the Stack

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/STraitStackView.h` (Private)


#### class `UE::UAF::Editor::STraitStackView`  
`class STraitStackView : public SCompoundWidget`  
_L28-87_
- inherits: `SCompoundWidget`
- L32 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnStatckTraitSelectionChanged, const FTraitUID );` — Used to notify the Trait Editor a Trait has been selected on the Stack
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnStackTraitDeleteRequest, const FTraitUID );` — Used to notify the Trait Editor a request to delete a Trait
- L38 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnStackTraitDragAccepted, const FTraitUID , const FTraitUID , EItemDropZone );` — Used to notify the Trait Editor a Trait Drag has been accepted on the Stack
- L41 _public prototype_ `STraitStackView();`
- L43 _public function_ `SLATE_BEGIN_ARGS(STraitStackView)`
- L46 _public prototype_ `SLATE_EVENT(FOnStackTraitDeleteRequest, OnTraitDeleteRequest) SLATE_EVENT(FOnStatckTraitSelectionChanged, OnStatckTraitSelectionChanged) SLATE_EVENT(FOnStackTraitDragAccepted, OnStackTraitDragAccepted) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FTraitEditorSharedData>& InTraitEditorSharedData);` — Called to notify a click on the delete button
- L58 _public prototype_ `void RefreshList();`
- L63 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L65 _private prototype_ `void HandleDelete();`
- L66 _private prototype_ `bool HasValidSelection() const;`
- L68 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedRef<FTraitStackViewEntry> InEntry, const TSharedRef<STableViewBase>& InOwnerTable);`
- L69 _private prototype_ `TSharedRef<SWidget> GetStackListItemWidget(const TWeakPtr<FTraitStackViewEntry>& InEntryWeak, const TSharedPtr<FTraitEditorSharedData>& TraitEditorSharedDataLocal);`
- L71 _private prototype_ `const TSharedPtr<FTraitDataEditorDef>& GetSelectedTraitData() const;`
- L72 _private prototype_ `const FTraitUID GetSelectedTraitUID() const;`
- L74 _private prototype_ `FReply ExecuteDelete(FTraitUID TraitUID);`
- L76 _private member_ `TSharedPtr<FUICommandList> UICommandList;`
- L78 _private member_ `TSharedPtr<FTraitDataEditorDef> SelectedTraitData;`
- L79 _private member_ `TSharedPtr<FTraitEditorSharedData> TraitEditorSharedData;`
- L81 _private member_ `FOnStackTraitDeleteRequest OnTraitDeleteRequest;`
- L82 _private member_ `FOnStatckTraitSelectionChanged OnStatckTraitSelectionChanged;`
- L83 _private member_ `FOnStackTraitDragAccepted OnStackTraitDragAccepted;`
- L85 _private member_ `TSharedRef<SListView<TSharedRef<FTraitStackViewEntry>>> EntriesList;`
- L86 _private member_ `TArray<TSharedRef<FTraitStackViewEntry>> Entries;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Workspace` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStatckTraitSelectionChanged, const FTraitUID );` — Used to notify the Trait Editor a Trait has been selected on the Stack
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnStackTraitDeleteRequest, const FTraitUID );` — Used to notify the Trait Editor a request to delete a Trait
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnStackTraitDragAccepted, const FTraitUID , const FTraitUID , EItemDropZone );` — Used to notify the Trait Editor a Trait Drag has been accepted on the Stack

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/TraitEditorDefs.h` (Private)


#### struct `UE::UAF::Editor::FTraitStackTraitStatus`  
`struct FTraitStackTraitStatus`  
_L25-71_
- L47 _public function_ `bool HasWarnings() const`
- L51 _public function_ `bool HasErrors() const`
- L56 _public member_ `EStackStatus TraitStatus = EStackStatus::Invalid;`
- L57 _public member_ `TArray<FStatusMessage> StatusMessages;`
- L58 _public member_ `TArray<FTraitInterfaceUID> MissingInterfaces;`
- L60 _public function_ `bool HasStatusType(EStackStatus InStatus) const`

#### enum `UE::UAF::Editor::FTraitStackTraitStatus::EStackStatus`  
`enum class EStackStatus : uint8`  
_L27-33_
- L29 _public enumerator_ `Invalid`
- L30 _public enumerator_ `Ok`
- L31 _public enumerator_ `Warning`
- L32 _public enumerator_ `Error`

#### struct `UE::UAF::Editor::FTraitStackTraitStatus::FStatusMessage`  
`struct FStatusMessage`  
_L35-45_
- L37 _public prototype_ `FStatusMessage() = default;`
- L38 _public function_ `FStatusMessage(EStackStatus InStatus, const FText& InMessageText) : Status(InStatus) , MessageText(InMessageText)`
- L43 _public member_ `EStackStatus Status = EStackStatus::Invalid;`
- L44 _public member_ `FText MessageText;`

#### struct `UE::UAF::Editor::FTraitDataEditorDef`  
`struct FTraitDataEditorDef`  
_L73-110_
- L75 _public prototype_ `FTraitDataEditorDef() = default;`
- L77 _public function_ `FTraitDataEditorDef(const FTrait& Trait, const FText& InTraitDisplayName) : TraitName(Trait.GetTraitName()) , TraitDisplayName(InTraitDisplayName) , TraitUID(Trait.GetTraitUID()) , TraitMode(Trait.GetTraitMode()) , ImplementedInterfaces(Trait.GetTraitInterfaces()) , RequiredInterfaces(Trait.GetTraitRequiredInterfaces())`
- L87 _public function_ `FTraitDataEditorDef(const FName& InTraitName, const FText& InTraitDisplayName, FTraitUID InTraitUUID, ETraitMode InTraitMode, const TArray<FTraitInterfaceUID>& InImplementedInterfaces, const TArray<FTraitInterfaceUID>& InRequiredInterfaces, bool bInMultipleInstanceSupport) : TraitName(InTraitName) , TraitDisplayName(InTraitDisplayName) , TraitUID(InTraitUUID) , TraitMode(InTraitMode) , ImplementedInterfaces(InImplementedInterfaces) , RequiredInterfaces(InRequiredInterfaces) , bMultipleInstanceSupport(bInMultipleInstanceSupport)`
- L97 _public member_ `FName TraitName;`
- L98 _public member_ `FText TraitDisplayName;`
- L99 _public member_ `FTraitUID TraitUID;`
- L100 _public member_ `ETraitMode TraitMode = ETraitMode::Invalid;`
- L102 _public member_ `TArray<FTraitInterfaceUID> ImplementedInterfaces;`
- L103 _public member_ `TArray<int32> ImplementedInterfacesStackListIndexes;`
- L104 _public member_ `TArray<FTraitInterfaceUID> RequiredInterfaces;`
- L105 _public member_ `TArray<int32> RequiredInterfacesStackListIndexes;`
- L107 _public member_ `bool bMultipleInstanceSupport = false;`
- L109 _public member_ `FTraitStackTraitStatus StackStatus;`

#### struct `UE::UAF::Editor::FTraitCategoryData`  
`struct FTraitCategoryData`  
_L112-125_
- L114 _public prototype_ `FTraitCategoryData() = default;`
- L116 _public function_ `FTraitCategoryData( const FName& InCategory, const FText& InCategoryText) : Category(InCategory) , CategoryText(InCategoryText)`
- L121 _public member_ `FName Category;`
- L122 _public member_ `FText CategoryText;`
- L124 _public member_ `TArray<TSharedPtr<FTraitDataEditorDef>> TraitList;`

#### struct `UE::UAF::Editor::FTraitEditorSharedData`  
`struct FTraitEditorSharedData`  
_L127-141_
- L129 _public member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WorkspaceEditorWeak;`
- L130 _public member_ `TWeakObjectPtr<UAnimNextEdGraphNode> EdGraphNodeWeak = nullptr;`
- L131 _public member_ `TSharedPtr<TArray<TSharedPtr<FTraitDataEditorDef>>> CurrentTraitsDataShared;`
- L133 _public member_ `TArray<FTraitInterfaceUID> StackUsedInterfaces;`
- L134 _public member_ `TArray<FTraitInterfaceUID> StackMissingInterfaces;`
- L135 _public member_ `TArray<int32> StackUsedInteraceMissingIndexes;`
- L137 _public member_ `bool bStackContainsErrors = false;`
- L138 _public member_ `bool bShowTraitInterfaces = false;`
- L139 _public member_ `bool bShowTraitInterfacesIfWarningsOrErrors = false;`
- L140 _public member_ `bool bAdvancedView = false;`

#### struct `UE::UAF::Editor::FTraitEditorUtils`  
`struct FTraitEditorUtils`  
_L143-164_
- L145 _public prototype_ `static FSlateColor GetTraitIconErrorDisplayColor(const FTraitStackTraitStatus& InTraitStatus);`
- L146 _public prototype_ `static FSlateColor GetTraitTextDisplayColor(const ETraitMode TraitMode);`
- L147 _public prototype_ `static FSlateColor GetTraitBackroundDisplayColor(const ETraitMode TraitMode, bool bIsSelected = false, bool bIsHovered = false);`
- L156 _public prototype_ `static TSharedRef<SWidget> GetInterfaceListWidget(EInterfaceDisplayType InterfaceDisplayType, const TSharedPtr<FTraitDataEditorDef>& InTraitDataShared, const TSharedPtr<FTraitEditorSharedData>& InTraitEditorSharedDataShared);`
- L157 _public prototype_ `static TSharedRef<SWidget> GetInterfaceWidget(EInterfaceDisplayType InterfaceDisplayType, FTraitInterfaceUID InterfaceUID, const TSharedPtr<FTraitDataEditorDef>& InTraitDataShared, const TSharedPtr<FTraitEditorSharedData>& InTraitEditorSharedDataShared);`
- L158 _public prototype_ `static void GenerateStackInterfacesUsedIndexes(TSharedPtr<FTraitDataEditorDef>& TraitData, const TSharedPtr<FTraitEditorSharedData>& InTraitEditorSharedData);`
- L160 _public prototype_ `static TSharedPtr<FTraitDataEditorDef> FindTraitInCurrentStackData(const FTraitUID InTraitUID, TSharedPtr<TArray<TSharedPtr<FTraitDataEditorDef>>> CurrentTraitsDataShared, int32* OutIndex = nullptr);`
- L163 _public prototype_ `static bool IsInternal(const FTraitInterfaceUID& InterfaceUID);` — Internal Interfaces are not shown in the Traits Editor

#### enum `UE::UAF::Editor::FTraitEditorUtils::EInterfaceDisplayType`  
`enum class EInterfaceDisplayType : uint8`  
_L149-155_
- L151 _public enumerator_ `ListImplemented`
- L152 _public enumerator_ `ListRequired`
- L153 _public enumerator_ `StackImplemented`
- L154 _public enumerator_ `StackRequired`

#### class `UE::UAF::Editor::FTraitListDragDropBase`  
`class FTraitListDragDropBase : public FDecoratedDragDropOp`  
_L167-180_
- inherits: `FDecoratedDragDropOp`
- desc: --- FTraitListDragDropBase ---
- L171 _public function_ `const TWeakPtr<FTraitDataEditorDef>& GetDraggedTraitData() const` — @return The identifier being dragged
- L176 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L179 _protected member_ `TWeakPtr<FTraitDataEditorDef> DraggedTraitDataWeak;`

#### class `UE::UAF::Editor::FTraitListDragDropOp`  
`class FTraitListDragDropOp : public FTraitListDragDropBase`  
_L183-195_
- inherits: `FTraitListDragDropBase`
- desc: --- FTraitListDragDropOp ---
- L186 _public function_ `DRAG_DROP_OPERATOR_TYPE(FTraitListDragDropOp, FDecoratedDragDropOp) static TSharedRef<FTraitListDragDropOp> New(TWeakPtr<FTraitDataEditorDef> InDraggedTraitDataWeak)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Workspace` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Graph/TraitEditorTabSummoner.h` (Private)


#### struct `UE::UAF::Editor::FTraitEditorTabSummoner`  
`struct FTraitEditorTabSummoner : public FWorkflowTabFactory`  
_L20-32_
- inherits: `FWorkflowTabFactory`
- L23 _public prototype_ `FTraitEditorTabSummoner(const TSharedPtr<UE::Workspace::IWorkspaceEditor>& InHostingApp);`
- L27 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L28 _private prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L31 _private member_ `TSharedPtr<STraitEditorView> TraitEditorView;` — The widget this tab spawner wraps

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Workspace` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L16 _externvar_ `extern const FLazyName TraitEditorTabName;` (scope `UE::UAF::Editor`)
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTraitEditorCreated, TSharedRef<STraitEditorView>);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTraitEditorCreated, TSharedRef<STraitEditorView>);` (scope `UE::UAF::Editor`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/RewindDebugger/AnimNextAnimGraphAnalyzer.h` (Private)


#### class `FAnimNextAnimGraphAnalyzer`  
`class FAnimNextAnimGraphAnalyzer : public UE::Trace::IAnalyzer`  
_L10-27_
- inherits: `UE::Trace::IAnalyzer`
- L13 _public prototype_ `FAnimNextAnimGraphAnalyzer(TraceServices::IAnalysisSession& InSession, FAnimNextAnimGraphProvider& InProvider);`
- L15 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L16 _public function_ `virtual void OnAnalysisEnd() override`
- L17 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L25 _private member_ `TraceServices::IAnalysisSession& Session;`
- L26 _private member_ `FAnimNextAnimGraphProvider& Provider;`

#### enum `FAnimNextAnimGraphAnalyzer::(anonymous)`  
``  
_L21-23_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L22 _enumerator_ `RouteId_EvaluationProgram` (scope `FAnimNextAnimGraphAnalyzer::__anone7358a580103`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/RewindDebugger/AnimNextAnimGraphProvider.h` (Private)


#### struct `FEvaluationProgramData`  
`struct FEvaluationProgramData`  
_L19-30_
- L21 _public function_ `FEvaluationProgramData(TraceServices::IAnalysisSession& Session) : GraphInstanceId(0), EvaluationProgramTimeline(Session.GetLinearAllocator( ))`
- L28 _public member_ `uint64 GraphInstanceId;`
- L29 _public member_ `TraceServices::TPointTimeline<TArray<uint8>> EvaluationProgramTimeline;`

#### class `FAnimNextAnimGraphProvider`  
`class FAnimNextAnimGraphProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L32-84_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L35 _public member_ `static FName ProviderName;`
- L37 _public prototype_ `FAnimNextAnimGraphProvider(TraceServices::IAnalysisSession& InSession);`
- L40 _public function_ `virtual void BeginRead() const override`
- L45 _public function_ `virtual void EndRead() const override`
- L50 _public function_ `virtual void ReadAccessCheck() const override`
- L56 _public function_ `virtual void BeginEdit() const override`
- L61 _public function_ `virtual void EndEdit() const override`
- L66 _public function_ `virtual void EditAccessCheck() const override`
- L71 _public prototype_ `const FEvaluationProgramData* GetEvaluationProgramData(uint64 GraphInstanceId) const;`
- L72 _public prototype_ `void AppendEvaluationProgram(double ProfileTime, double RecordingTime, uint64 ObjectInstanceId, uint64 GraphInstanceId, const TArrayView<const uint8>& ProgramData);`
- L74 _public prototype_ `void EnumerateEvaluationGraphs(uint64 OuterObjectId, TFunctionRef<void(uint64 GraphInstanceId)> Callback) const;`
- L77 _private member_ `TraceServices::IAnalysisSession& Session;`
- L78 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L80 _private member_ `TMap<uint64, TSharedRef<FEvaluationProgramData>> EvaluationProgramData;`
- L83 _private member_ `TMultiMap<uint64, uint64> EvaluationGraphs;` — map from object id to a list of graph instance ids that have evaluation data

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L16 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GAnimNextAnimGraphProviderLockState;` (scope `TraceServices`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/RewindDebugger/AnimNextAnimGraphTraceModule.h` (Private)


#### class `FAnimNextAnimGraphTraceModule`  
`class FAnimNextAnimGraphTraceModule : public TraceServices::IModule`  
_L10-22_
- inherits: `TraceServices::IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L15 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L16 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L17 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L18 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L21 _private member_ `static FName ModuleName;`

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/RewindDebugger/EvaluationProgramTrack.h` (Private)


#### class `UEvaluationProgramDetailsObject`  
`class UEvaluationProgramDetailsObject : public UObject`  
_L15-22_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public member_ `FSerializableEvaluationProgram Program;` — `UPROPERTY(EditAnywhere, Category=Details, meta=(ShowOnlyInnerProperties))`

#### class `UE::UAF::Editor::FEvaluationProgramTrack`  
`class FEvaluationProgramTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L27-56_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L30 _public prototype_ `FEvaluationProgramTrack(uint64 InObjectId);`
- L31 _public prototype_ `FEvaluationProgramTrack(uint64 InObjectId, uint64 InstanceId);`
- L32 _public prototype_ `virtual ~FEvaluationProgramTrack();`
- L34 _public function_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetExistenceRange() const`
- L36 _private prototype_ `virtual bool UpdateInternal() override;`
- L37 _private function_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override`
- L39 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L40 _private function_ `virtual FName GetNameInternal() const override`
- L41 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L42 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L44 _private prototype_ `void Initialize();`
- L45 _private prototype_ `UEvaluationProgramDetailsObject* InitializeDetailsObject();`
- L47 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L48 _private member_ `FSlateIcon Icon;`
- L49 _private member_ `uint64 ObjectId;`
- L50 _private member_ `uint64 InstanceId = 0;`
- L51 _private member_ `double PreviousScrubTime = -1.0;`
- L52 _private member_ `TWeakObjectPtr<UEvaluationProgramDetailsObject> DetailsObjectWeakPtr;`
- L53 _private member_ `TSharedPtr<SEventTimelineView::FTimelineEventData> ExistenceRange;`

#### class `UE::UAF::Editor::FEvaluationProgramTrackCreator`  
`class FEvaluationProgramTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L59-67_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L62 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L63 _private function_ `virtual FName GetNameInternal() const override`
- L64 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L65 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L66 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/RewindDebugger/SequenceInfoTrack.h` (Private)


#### struct `FAnimNextSyncMarkerTraceInfo`  
`struct FAnimNextSyncMarkerTraceInfo`  
_L17-26_
- reflection: `USTRUCT()`
- L22 _public member_ `float Time = 0.0f;` — `UPROPERTY()`
- L25 _public member_ `FName Name;` — `UPROPERTY()`

#### struct `FAnimNextSequenceTraceInfo`  
`struct FAnimNextSequenceTraceInfo`  
_L29-49_
- reflection: `USTRUCT()`
- L33 _public function_ `FORCEINLINE float CalcAnimTimeRatio() const`
- L39 _public member_ `TWeakObjectPtr<const UAnimSequence> AnimSequence;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L42 _public member_ `float DurationSeconds = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L45 _public member_ `float CurrentTimeSeconds = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`
- L48 _public member_ `TArray<FAnimNextSyncMarkerTraceInfo> SyncMarkers;` — `UPROPERTY(VisibleAnywhere, Category = Properties)`

#### class `USequenceInfoDetailsObject`  
`class USequenceInfoDetailsObject : public UObject`  
_L52-59_
- reflection: `UCLASS()`
- inherits: `UObject`
- L58 _public member_ `TArray<FAnimNextSequenceTraceInfo> SequenceTraceInfo;` — `UPROPERTY(EditAnywhere, Category=Details, meta=(ShowOnlyInnerProperties, FullyExpand=true))`

#### class `UE::UAF::Editor::FAnimNextSequenceTraceInfoCustomization`  
`class FAnimNextSequenceTraceInfoCustomization : public IPropertyTypeCustomization`  
_L63-72_
- inherits: `IPropertyTypeCustomization`
- L66 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L69 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::UAF::Editor::FSequenceInfoTrack`  
`class FSequenceInfoTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L74-108_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L77 _public prototype_ `FSequenceInfoTrack(uint64 InObjectId);`
- L78 _public prototype_ `FSequenceInfoTrack(uint64 InObjectId, uint64 InstanceId);`
- L79 _public prototype_ `virtual ~FSequenceInfoTrack();`
- L81 _public function_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetExistenceRange() const`
- L83 _public member_ `static constexpr const TCHAR* TrackName = TEXT("Seq`
- L86 _private prototype_ `virtual bool UpdateInternal() override;`
- L87 _private function_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override`
- L89 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L90 _private function_ `virtual FName GetNameInternal() const override`
- L91 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L92 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L94 _private prototype_ `void Initialize();`
- L95 _private prototype_ `USequenceInfoDetailsObject* InitializeDetailsObject();`
- L97 _private prototype_ `static void RefreshSequenceInfoFromEvaluationProgram(TArray<FAnimNextSequenceTraceInfo>& OutSequenceInfo, const FSerializableEvaluationProgram& Program);`
- L99 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L100 _private member_ `FSlateIcon Icon;`
- L101 _private member_ `uint64 ObjectId;`
- L102 _private member_ `uint64 InstanceId = 0;`
- L103 _private member_ `double PreviousScrubTime = -1.0;`
- L104 _private member_ `TWeakObjectPtr<USequenceInfoDetailsObject> DetailsObjectWeakPtr;`
- L105 _private member_ `TSharedPtr<SEventTimelineView::FTimelineEventData> ExistenceRange;`

#### class `UE::UAF::Editor::FSequenceInfoTrackCreator`  
`class FSequenceInfoTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L111-119_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L114 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L115 _private function_ `virtual FName GetNameInternal() const override`
- L116 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L117 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L118 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L61 _namespace_ `namespace UE`
- L61 _namespace_ `namespace UAF` (scope `UE`)
- L61 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Settings/UAFAnimGraphEditorProjectSettings.h` (Private)


#### class `UUAFAnimGraphEditorProjectSettings`  
`class UUAFAnimGraphEditorProjectSettings : public UDeveloperSettings`  
_L14-27_
- reflection: `UCLASS(MinimalAPI, Config = Editor, defaultconfig, DisplayName = "UAF Anim Graph Settings")`
- inherits: `UDeveloperSettings`
- desc: UAF Anim Graph Editor Settings that are shared across a project.
- L19 _public prototype_ `virtual void PostInitProperties() override;`
- L20 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L26 _public member_ `int32 MaxGraphUpdateLoopCount = 1000;` — `UPROPERTY(Config, EditAnywhere, Category="UAF|Graph", meta=(ConsoleVariable="UAF.MaxGraphUpdateLoopCount"))` — The maximum amount of update loops per frame before a graph is considered to be stuck in an endless loop and breaks out of the update This setting is linked with the CVar UAF.MaxGraphUpdateLoopCount

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/TraitStackEditor.h` (Private)


#### class `UE::UAF::Editor::FTraitStackEditor`  
`class FTraitStackEditor : public ITraitStackEditor`  
_L16-22_
- inherits: `ITraitStackEditor`
- desc: Interface used to talk to the trait stack editor embedded in a workspace
- L19 _private prototype_ `virtual void SetTraitData(const TSharedRef<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditor, const FTraitStackData& InTraitStackData) override;` — ITraitStackEditor interface
- L20 _private prototype_ `virtual TSharedRef<SWidget> CreateTraitHeaderWidget(IDetailCategoryBuilder& InCategory, IDetailPropertyRow& InPropertyRow, URigVMController* InController) override;`
- L21 _private prototype_ `virtual TSharedRef<SWidget> CreateTraitStackHeaderWidget(IDetailCategoryBuilder& InCategory, URigVMController* InController) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Traits/AnimNextCallFunctionSharedDataDetails.h` (Private)


#### class `UE::UAF::Editor::FCallFunctionSharedDataDetails`  
`class FCallFunctionSharedDataDetails : public IPropertyTypeCustomization`  
_L10-20_
- inherits: `IPropertyTypeCustomization`
- L13 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L14 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L16 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L17 _private member_ `TSharedPtr<IPropertyHandle> FunctionPropertyHandle;`
- L18 _private member_ `TSharedPtr<IPropertyHandle> FunctionHeaderPropertyHandle;`
- L19 _private member_ `TSharedPtr<IPropertyHandle> FunctionEventPropertyHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Traits/UAFCallFunctionInfoDetails.h` (Private)


#### class `UE::UAF::Editor::FCallFunctionInfoDetails`  
`class FCallFunctionInfoDetails : public IPropertyTypeCustomization`  
_L10-20_
- inherits: `IPropertyTypeCustomization`
- L13 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L14 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L16 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L17 _private member_ `TSharedPtr<IPropertyHandle> FunctionPropertyHandle;`
- L18 _private member_ `TSharedPtr<IPropertyHandle> FunctionHeaderPropertyHandle;`
- L19 _private member_ `TSharedPtr<IPropertyHandle> FunctionEventPropertyHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)
