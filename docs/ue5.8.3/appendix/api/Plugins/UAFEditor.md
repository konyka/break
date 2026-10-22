# Plugins / UAFEditor

- module root: `Plugins/Experimental/UAF/UAF/Source/UAFEditor`
- headers: 153; symbols: 2635
- symbol kinds: class=150, delegate=11, enum=13, enumerator=42, externvar=5, function=228, macro=14, member=620, namespace=404, prototype=1036, struct=75, typedef=32, variable=5
- PrivateDependencyModuleNames: AdvancedPreviewScene, AdvancedWidgets, AnimGraph, AnimationCore, ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, ClassViewer, ContentBrowser, ContentBrowserAssetDataSource, ContentBrowserData, ContentBrowserFileDataSource, Core, CoreUObject, DataHierarchyEditor, DesktopWidgets, DeveloperSettings, EditorFramework, EditorInteractiveToolsFramework, EditorSubsystem, EditorWidgets, Engine, GameplayInsights, GraphEditor, HierarchyTableAnimationRuntime, HierarchyTableEditor, HierarchyTableRuntime, InputCore, InteractiveToolsFramework, Kismet, KismetWidgets, Persona, Projects, PropertyBindingUtils, PropertyEditor, RewindDebuggerInterface, RigVM, RigVMDeveloper, RigVMEditor, SceneOutliner, Settings, Slate, SlateCore, SourceControl, StatusBar, StructUtilsEditor, SubobjectEditor, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UAF, UAFUncookedOnly, UniversalObjectLocator, UniversalObjectLocatorEditor, UnrealEd, UserAssetTagsEditor, WorkspaceEditor

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Common/AnimNextAssetItemDetails.h` (Internal)


#### class `UE::UAF::Editor::FAnimNextAssetItemDetails`  
`class FAnimNextAssetItemDetails : public UE::Workspace::IWorkspaceOutlinerItemDetails`  
_L13-23_
- inherits: `UE::Workspace::IWorkspaceOutlinerItemDetails`
- L16 _public prototype_ `FAnimNextAssetItemDetails() = default;`
- L18 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`
- L19 _public prototype_ `virtual bool HandleDoubleClick(const FToolMenuContext& ToolMenuContext) const override;`
- L21 _public prototype_ `static void RegisterToolMenuExtensions();`
- L22 _public prototype_ `static void UnregisterToolMenuExtensions();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Common/GraphEditorSchemaActions.h` (Internal)


#### struct `FAnimNextSchemaAction`  
`struct FAnimNextSchemaAction : public FEdGraphSchemaAction`  
_L19-33_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L23 _public prototype_ `FAnimNextSchemaAction() = default;`
- L25 _public function_ `FAnimNextSchemaAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords = FText::GetEmpty()) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), 0, MoveTemp(InKeywords))`
- L30 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const;`
- L32 _public prototype_ `virtual const FLinearColor& GetIconColor() const;`

#### struct `FAnimNextSchemaAction_RigUnit`  
`struct FAnimNextSchemaAction_RigUnit : public FAnimNextSchemaAction`  
_L36-56_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L40 _public prototype_ `FAnimNextSchemaAction_RigUnit() = default;`
- L42 _public function_ `FAnimNextSchemaAction_RigUnit(const TSubclassOf<URigVMUnitNode>& InNodeClass, UScriptStruct* InStructTemplate, FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords = FText::GetEmpty()) : FAnimNextSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InKeywords) , StructTemplate(InStructTemplate) , NodeClass(InNodeClass)`
- L49 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L50 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`
- L54 _private member_ `UScriptStruct* StructTemplate = nullptr;` — The script struct for our rig unit
- L55 _private member_ `TSubclassOf<URigVMUnitNode> NodeClass;`

#### struct `FAnimNextSchemaAction_DispatchFactory`  
`struct FAnimNextSchemaAction_DispatchFactory : public FAnimNextSchemaAction`  
_L60-80_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L64 _public prototype_ `FAnimNextSchemaAction_DispatchFactory() = default;`
- L66 _public function_ `FAnimNextSchemaAction_DispatchFactory(FName InNotation, FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords = FText::GetEmpty()) : FAnimNextSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InKeywords) , Notation(InNotation)`
- L71 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L74 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L75 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`
- L79 _private member_ `FName Notation;` — Notation for dispatch factory

#### struct `FAnimNextSchemaAction_Variable`  
`struct FAnimNextSchemaAction_Variable : public FAnimNextSchemaAction`  
_L84-116_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L95 _public prototype_ `FAnimNextSchemaAction_Variable() = default;`
- L97 _public prototype_ `FAnimNextSchemaAction_Variable(FName InName, const UObject* InSourceObject, const FAnimNextParamType& InType, const EVariableAccessorChoice InVariableAccessorChoice);`
- L100 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L101 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`
- L103 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L105 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L107 _public prototype_ `void SetVariableAccessorChoice(EVariableAccessorChoice InVariableAccessorChoice, bool bUpdateSearchData = false);`
- L110 _private member_ `FName Name;`
- L111 _private member_ `FString TypeObjectPath;`
- L112 _private member_ `FString SourceObjectPath;`
- L113 _private member_ `FString TypeName;`
- L114 _private member_ `EVariableAccessorChoice VariableAccessorChoice = EVariableAccessorChoice::Set;`
- L115 _private member_ `FLinearColor VariableColor;`

#### enum `FAnimNextSchemaAction_Variable::EVariableAccessorChoice`  
`enum class EVariableAccessorChoice`  
_L88-93_
- L90 _public enumerator_ `Set`
- L91 _public enumerator_ `Get`
- L92 _public enumerator_ `Deferred`

#### struct `FAnimNextSchemaAction_AddComment`  
`struct FAnimNextSchemaAction_AddComment : public FAnimNextSchemaAction`  
_L119-130_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L123 _public prototype_ `FAnimNextSchemaAction_AddComment();`
- L126 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L127 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`
- L129 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`

#### struct `FAnimNextSchemaAction_Function`  
`struct FAnimNextSchemaAction_Function : public FAnimNextSchemaAction`  
_L133-162_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L137 _public prototype_ `FAnimNextSchemaAction_Function() = default;`
- L139 _public prototype_ `FAnimNextSchemaAction_Function(const FRigVMGraphFunctionHeader& InReferencedPublicFunctionHeader, const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const FText& InKeywords = FText::GetEmpty());`
- L140 _public prototype_ `FAnimNextSchemaAction_Function(const URigVMLibraryNode* InFunctionLibraryNode, const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const FText& InKeywords = FText::GetEmpty());`
- L142 _public prototype_ `FAnimNextSchemaAction_Function(const URigVMLibraryNode* InFunctionLibraryNode);`
- L144 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L147 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L148 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`
- L153 _private member_ `FRigVMGraphFunctionHeader ReferencedPublicFunctionHeader;` — `UPROPERTY(Transient)` — The public function definition we will spawn from [optional]
- L157 _private member_ `bool bIsLocalFunction = false;` — `UPROPERTY(Transient)` — Marked as true for local function definitions
- L161 _private member_ `TSubclassOf<UEdGraphNode> NodeClass;` — `UPROPERTY(Transient)` — Holds the node type that this spawner will instantiate.

#### struct `FAnimNextSchemaAction_PromoteToVariable`  
`struct FAnimNextSchemaAction_PromoteToVariable : public FAnimNextSchemaAction`  
_L165-176_
- reflection: `USTRUCT()`
- inherits: `FAnimNextSchemaAction`
- L169 _public prototype_ `FAnimNextSchemaAction_PromoteToVariable();`
- L172 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface
- L173 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override`
- L175 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UAFEDITOR_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Common/SActionMenu.h` (Internal)


#### struct `UE::UAF::Editor::FActionMenuContextData`  
`struct FActionMenuContextData`  
_L29-41_
- L31 _public member_ `TArray<UObject*> SelectedObjects;`
- L33 _public member_ `UEdGraph* Graph = nullptr;`
- L34 _public member_ `FWorkspaceOutlinerItemExport Export;`
- L35 _public member_ `const URigVMSchema* RigVMSchema = nullptr;`
- L36 _public member_ `URigVMHost* RigVMHost = nullptr;`
- L37 _public member_ `IRigVMClientHost* RigVMClientHost = nullptr;`
- L38 _public member_ `URigVMController* RigVMController = nullptr;`
- L39 _public member_ `UUAFRigVMAssetEditorData* EditorData = nullptr;`
- L40 _public member_ `bool bShowGlobalManifestNodes = true;`

#### class `UE::UAF::Editor::SActionMenu`  
`class SActionMenu : public SBorder`  
_L43-97_
- inherits: `SBorder`
- L47 _public prototype_ `DECLARE_DELEGATE_TwoParams(FCollectAllGraphActions, FGraphContextMenuBuilder& , const FActionMenuContextData& );` — Delegate to retrieve the action list for the graph
- L50 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FClosedReason, bool , bool , bool );` — Delegate for the OnCloseReason event which is always raised when the SActionMenu closes
- L52 _public function_ `SLATE_BEGIN_ARGS(SActionMenu) : _NewNodePosition(FVector2D::ZeroVector) , _AutoExpandActionMenu(false)`
- L57 _public prototype_ `SLATE_ARGUMENT(FVector2D, NewNodePosition) SLATE_ARGUMENT(TArray<UEdGraphPin*>, DraggedFromPins) SLATE_ARGUMENT(SGraphEditor::FActionMenuClosed, OnClosedCallback) SLATE_ARGUMENT(bool, AutoExpandActionMenu) SLATE_EVENT(FClosedReason, OnCloseReason) SLATE_EVENT(FCollectAllGraphActions, OnCollectGraphActionsCallback) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraph* InGraph, const FWorkspaceOutlinerItemExport& InExport);`
- L70 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();`
- L73 _protected prototype_ `void OnActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& SelectedAction, ESelectInfo::Type InSelectionType);`
- L75 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);`
- L78 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu
- L80 _protected prototype_ `void CollectAllAnimNextGraphActions(FGraphContextMenuBuilder& MenuBuilder) const;`
- L83 _private member_ `FActionMenuContextData ContextData;`
- L85 _private member_ `bool bAutoExpandActionMenu = false;`
- L86 _private member_ `bool bActionExecuted = false;`
- L88 _private member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L89 _private member_ `FDeprecateSlateVector2D NewNodePosition = FVector2f::ZeroVector;`
- L91 _private member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L92 _private member_ `FClosedReason OnCloseReasonCallback;`
- L94 _private member_ `FCollectAllGraphActions OnCollectGraphActionsCallback;`
- L96 _private member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace UAF` (scope `UE`)
- L26 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L47 _delegate_ `DECLARE_DELEGATE_TwoParams(FCollectAllGraphActions, FGraphContextMenuBuilder& , const FActionMenuContextData& );` — Delegate to retrieve the action list for the graph
- L50 _delegate_ `DECLARE_DELEGATE_ThreeParams(FClosedReason, bool , bool , bool );` — Delegate for the OnCloseReason event which is always raised when the SActionMenu closes

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Common/SCategoryTableRow.h` (Internal)


#### class `UE::UAF::Editor::SCategoryHeaderTableRow`  
`template<typename ItemType> class SCategoryHeaderTableRow : public STableRow<ItemType>`  
_L17-102_
- inherits: `STableRow<ItemType>`
- desc: An entry category displayed in a tree view
- L20 _public function_ `SLATE_BEGIN_ARGS(SCategoryHeaderTableRow) : _Padding(FMargin(0.0f, 2.0f, .0f, 0.0f))`
- L23 _public function_ `SLATE_DEFAULT_SLOT(typename SCategoryHeaderTableRow::FArguments, Content) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)`
- L61 _public function_ `const FSlateBrush* GetBackgroundImage() const`
- L73 _public function_ `virtual void SetContent(TSharedRef< SWidget > InContent) override`
- L78 _public function_ `virtual void SetRowContent(TSharedRef< SWidget > InContent) override`
- L83 _public function_ `virtual const FSlateBrush* GetBorder() const`
- L88 _public function_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L101 _private member_ `TSharedPtr<SBorder> ContentBorder;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Common/SRigVMFunctionPicker.h` (Internal)


#### class `UE::UAF::Editor::SRigVMFunctionPicker`  
`class SRigVMFunctionPicker : public SCompoundWidget`  
_L30-161_
- inherits: `SCompoundWidget`
- desc: Picker widget the allows choosing a RigVM function
- L32 _private function_ `SLATE_BEGIN_ARGS(SRigVMFunctionPicker) : _AllowNew(true) , _AllowClear(true) , _ContentOnly(false) , _IsContextSensitive(true)`
- L40 _private prototype_ `SLATE_ARGUMENT(FAssetData, CurrentAsset)` — The 'current' asset, used for accessing private functions
- L82 _private prototype_ `void RequestRefreshEntries();` — Requests a refresh of the dropdown menu contents
- L85 _private prototype_ `void RefreshEntries();` — Refreshes the dropdown menu contents
- L144 _private member_ `FAssetData CurrentAsset;`
- L145 _private member_ `TWeakObjectPtr<UUAFRigVMAsset> WeakCurrentAsset;`
- L146 _private member_ `FOnRigVMFunctionPicked OnRigVMFunctionPicked;`
- L147 _private member_ `FSimpleDelegate OnNewFunction;`
- L148 _private member_ `TAttribute<FText> FunctionName;`
- L149 _private member_ `TAttribute<FText> FunctionToolTip;`
- L150 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L151 _private member_ `FText FilterText;`
- L152 _private member_ `TSharedPtr<STreeView<TSharedPtr<FEntry>>> TreeView;`
- L153 _private member_ `TArray<TSharedPtr<FEntry>> Entries;`
- L154 _private member_ `TArray<TSharedPtr<FEntry>> FilteredEntries;`
- L155 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L156 _private member_ `FOnFilterRigVMFunction OnFilterFunction;`
- L157 _private member_ `TArray<TWeakObjectPtr<const UUAFRigVMAsset>> FilterAssets;`
- L158 _private member_ `bool bIsContextSensitive = true;`
- L159 _private member_ `bool bAllowClear = false;`
- L160 _private member_ `bool bAllowNew = false;`

#### enum `UE::UAF::Editor::SRigVMFunctionPicker::EEntryType`  
`enum class EEntryType`  
_L87-93_
- L89 _public enumerator_ `None`
- L90 _public enumerator_ `Asset`
- L91 _public enumerator_ `Function`
- L92 _public enumerator_ `NewFunction`

#### struct `UE::UAF::Editor::SRigVMFunctionPicker::FEntry`  
`struct FEntry`  
_L95-105_
- L97 _public function_ `explicit FEntry(EEntryType InType) : Type(InType)`
- L101 _public member_ `EEntryType Type;`
- L102 _public member_ `FText Name;`
- L103 _public member_ `FText ToolTip;`
- L104 _public member_ `const FSlateBrush* Icon = nullptr;`

#### struct `UE::UAF::Editor::SRigVMFunctionPicker::FFunctionEntry`  
`struct FFunctionEntry : FEntry`  
_L107-117_
- inherits: `FEntry`
- L109 _public function_ `FFunctionEntry() : FEntry(EEntryType::Function)`
- L113 _public member_ `FRigVMGraphFunctionHeader FunctionHeader;`
- L114 _public member_ `const FSlateBrush* ReturnTypeIcon = nullptr;`
- L115 _public member_ `FSlateColor ReturnTypeColor = FLinearColor::Gray;`
- L116 _public member_ `FText ReturnTypeName;`

#### struct `UE::UAF::Editor::SRigVMFunctionPicker::FAssetEntry`  
`struct FAssetEntry : FEntry`  
_L119-128_
- inherits: `FEntry`
- L121 _public function_ `FAssetEntry() : FEntry(EEntryType::Asset)`
- L125 _public member_ `FAssetData Asset;`
- L126 _public member_ `TArray<TSharedPtr<FEntry>> Functions;`
- L127 _public member_ `TArray<TSharedPtr<FEntry>> FilteredFunctions;`

#### struct `UE::UAF::Editor::SRigVMFunctionPicker::FNewFunctionEntry`  
`struct FNewFunctionEntry : FEntry`  
_L130-135_
- inherits: `FEntry`
- L132 _public function_ `FNewFunctionEntry() : FEntry(EEntryType::NewFunction)`

#### struct `UE::UAF::Editor::SRigVMFunctionPicker::FNoneEntry`  
`struct FNoneEntry : FEntry`  
_L137-142_
- inherits: `FEntry`
- L139 _public function_ `FNoneEntry() : FEntry(EEntryType::None)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L24 _typedef_ `using FOnRigVMFunctionPicked = TDelegate<void(const FRigVMGraphFunctionHeader&)>;` (scope `UE::UAF::Editor`) — Delegate called when the user picks a function from the dropdown menu The header passed when selecting 'None' will be invalid
- L27 _typedef_ `using FOnFilterRigVMFunction = TDelegate<bool(const FRigVMGraphFunctionHeader&)>;` (scope `UE::UAF::Editor`) — Optional filter predicate: return true to include the function, false to exclude it

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Common/UAFVariableDragDropContext.h` (Internal)


#### class `UUAFVariableDragDropContext`  
`class UUAFVariableDragDropContext : public UObject`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TObjectPtr<UEdGraph> ParentGraph;` — `UPROPERTY()`
- L18 _public member_ `FVector2f Location;`
- L19 _public member_ `FName Name;`
- L20 _public member_ `FString TypeObjectPath;`
- L21 _public member_ `FString SourceObjectPath;`
- L22 _public member_ `FString TypeName;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/EditorUtils.h` (Internal)


#### struct `UE::UAF::Editor::FUtils`  
`struct FUtils`  
_L26-45_
- L28 _public prototype_ `static FName ValidateName(const UObject* InObject, const FString& InName);`
- L30 _public prototype_ `static void GetAllEntryNames(const UUAFRigVMAssetEditorData* InEditorData, TSet<FName>& OutNames);`
- L32 _public prototype_ `static FAnimNextParamType GetParameterTypeFromMetaData(const FStringView& InStringView);`
- L34 _public prototype_ `static void GetFilteredVariableTypeTree(TArray<TSharedPtr<UEdGraphSchema_K2::FPinTypeTreeInfo>>& TypeTree, ETypeTreeFilter TypeTreeFilter);`
- L36 _public prototype_ `static bool IsValidParameterNameString(FStringView InStringView, FText& OutErrorText);`
- L38 _public prototype_ `static bool IsValidParameterName(const FName InName, FText& OutErrorText);`
- L40 _public prototype_ `static bool IsValidParameterNameForEntry(const UAnimNextVariableEntry* Entry, const FText& InNewName, FText& OutErrorText);`
- L42 _public prototype_ `static bool AddSchemaRigUnitAction(const TSubclassOf<URigVMUnitNode>& UnitNodeClass, UScriptStruct* Struct, const FRigVMFunction& Function, FGraphContextMenuBuilder& InContexMenuBuilder);`
- L44 _public prototype_ `static void GetRigUnitStructMetadata(const UScriptStruct* Struct, FString& OutCategoryMetadata, FString& OutDisplayNameMetadata, FString& OutMenuDescSuffixMetadata);`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/ITraitStackEditor.h` (Internal)


#### struct `UE::UAF::Editor::FTraitStackData`  
`struct FTraitStackData`  
_L23-32_
- L25 _public prototype_ `FTraitStackData() = default;`
- L27 _public function_ `explicit FTraitStackData(const TWeakObjectPtr<UAnimNextEdGraphNode>& InEdGraphNodeWeak) : EdGraphNodeWeak(InEdGraphNodeWeak)`
- L31 _public member_ `TWeakObjectPtr<UAnimNextEdGraphNode> EdGraphNodeWeak = nullptr;`

#### class `UE::UAF::Editor::ITraitStackEditor`  
`class ITraitStackEditor : public IModularFeature`  
_L35-50_
- inherits: `IModularFeature`
- desc: Interface used to talk to the trait stack editor embedded in a workspace
- L38 _public member_ `static inline FLazyName ModularFeatureName = FLazyName(TEXT("Trai`
- L40 _public prototype_ `virtual ~ITraitStackEditor() = default;`
- L43 _public prototype_ `virtual void SetTraitData(const TSharedRef<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditor, const FTraitStackData& InTraitStackData) = 0;` — Sets the trait data to be displayed for the specified workspace editor instance
- L46 _public prototype_ `virtual TSharedRef<SWidget> CreateTraitHeaderWidget(IDetailCategoryBuilder& InCategory, IDetailPropertyRow& InPropertyRow, URigVMController* InController) = 0;` — Create a header widget for the trait in a trait stack node corresponding to InPropertyRow
- L49 _public prototype_ `virtual TSharedRef<SWidget> CreateTraitStackHeaderWidget(IDetailCategoryBuilder& InCategory, URigVMController* InController) = 0;` — Create a header widget for the stack in a trait stack node

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Workspace` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Module/AnimNextModuleFactory.h` (Internal)


#### class `UUAFSystemFactory`  
`class UUAFSystemFactory : public UFactory`  
_L10-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `UUAFSystemFactory();`
- L16 _private prototype_ `virtual bool ConfigureProperties() override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L18 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/UAF/AbstractSkeleton/SetBindingFactory.h` (Internal)


#### class `UAbstractSkeletonSetBindingFactory`  
`class UAbstractSkeletonSetBindingFactory : public UFactory`  
_L11-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `UAbstractSkeletonSetBindingFactory();`
- L17 _private prototype_ `virtual bool ConfigureProperties() override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L19 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/UAF/AbstractSkeleton/SetCollectionFactory.h` (Internal)


#### class `UAbstractSkeletonSetCollectionFactory`  
`class UAbstractSkeletonSetCollectionFactory : public UFactory`  
_L11-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `UAbstractSkeletonSetCollectionFactory();`
- L17 _private prototype_ `virtual bool ConfigureProperties() override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L19 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/UAFStyle.h` (Internal)


#### class `FUAFStyle`  
`class FUAFStyle final : public FSlateStyleSet`  
_L9-32_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `static FUAFStyle& Get();`
- L15 _private prototype_ `FUAFStyle();`
- L16 _private prototype_ `~FUAFStyle();`
- L19 _private prototype_ `static FString InResources(const FString& RelativePath);` — Resolve path relative to plugin's resources directory
- L21 _private prototype_ `void SetClassIcons();`
- L23 _private prototype_ `void SetVariablesOutlinerStyles();`
- L25 _private prototype_ `void SetTraitStyles();`
- L27 _private prototype_ `void SetAssetWizardStyles();`
- L29 _private prototype_ `void SetSetBindingStyles();`
- L31 _private prototype_ `void SetBlendProfileStyles();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UAFEDITOR_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Variables/AnimNextSharedVariablesFactory.h` (Internal)


#### class `UUAFSharedVariablesFactory`  
`class UUAFSharedVariablesFactory : public UFactory`  
_L10-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L15 _public prototype_ `UUAFSharedVariablesFactory();`
- L17 _public prototype_ `virtual bool ConfigureProperties() override;`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L19 _public function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Variables/VariablePickerArgs.h` (Internal)


#### enum `UE::UAF::Editor::EFilterVariableResult`  
`enum class EFilterVariableResult : int32`  
_L17-21_
- desc: Result of a filter operation via FOnFilterVariableType
- L19 _public enumerator_ `Include`
- L20 _public enumerator_ `Exclude`

#### struct `UE::UAF::Editor::FVariablePickerArgs`  
`struct FVariablePickerArgs`  
_L48-92_
- L50 _public prototype_ `FVariablePickerArgs() = default;`
- L53 _public member_ `FSimpleDelegate OnSelectionChanged;` — Delegate used to signal whether selection has changed
- L56 _public member_ `FOnVariablePicked OnVariablePicked;` — Delegate called when a single variable has been picked
- L59 _public member_ `FOnFilterVariable OnFilterVariable;` — Delegate called to filter variables for display to the user
- L63 _public member_ `FOnFilterVariableType OnFilterVariableType;` — Delegate called to filter variables by type for display to the user (RigVM registry checks, pin constraints, etc.) Applied as an additional gate on top of CompatibleTypes when both are set.
- L68 _public member_ `TArray<FAnimNextParamType> CompatibleTypes;` — If non-empty, the widget handles type-compat filtering and struct expansion internally. A variable passes if its type is directly compatible with any entry, or (with struct expansion) if it contains a compatible leaf. bAllowStructExpansion is auto-enabled when this is set.
- L71 _public member_ `FOnIsContextSensitive* OnIsContextSensitive = nullptr;` — Delegate called to determined context sensitivity
- L74 _public member_ `FOnContextSensitivityChanged OnContextSensitivityChanged;` — Delegate called when context sensitivity changes
- L77 _public member_ `FOnGetIncludeExcludeFilter OnGetIncludeExcludeFilter;` — Delegate called to get the inclusion/exclusion flags
- L80 _public member_ `EAnimNextExportedVariableFlags FlagInclusionFilter = EAnimNextExportedVariableFlags::Declared | EAnimNextExportedVariableFlags::Public;` — Default filter for AnimNext export flags to be used for variable list population (used if OnGetIncludeExcludeFilter is not overriden)
- L81 _public member_ `EAnimNextExportedVariableFlags FlagExclusionFilter = EAnimNextExportedVariableFlags::Referenced;`
- L84 _public member_ `bool bFocusSearchWidget = true;` — Whether the search box should be focused on widget creation
- L87 _public member_ `FOnSubPropertyVariablePicked OnSubPropertyVariablePicked;` — Fired when the user selects a sub-property leaf from inside a struct variable.
- L91 _public member_ `bool bAllowStructExpansion = false;` — If true, struct-type variables that contain at least one compatible sub-property appear in the list as expandable nodes.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L24 _typedef_ `using FOnFilterVariableType = TDelegate<EFilterVariableResult(const FAnimNextParamType& )>;` (scope `UE::UAF::Editor`) — Delegate called to filter variables by type for display to the user
- L27 _typedef_ `using FOnVariablePicked = TDelegate<void(const FAnimNextSoftVariableReference& , const FAnimNextParamType& )>;` (scope `UE::UAF::Editor`) — Delegate called when a variable has been picked. Graph argument is invalid when an unbound variable is chosen.
- L30 _typedef_ `using FOnFilterVariable = TDelegate<EFilterVariableResult(const FAnimNextSoftVariableReference& )>;` (scope `UE::UAF::Editor`) — Delegate called to filter variables for display to the user
- L33 _typedef_ `using FOnIsContextSensitive = TDelegate<bool()>;` (scope `UE::UAF::Editor`) — Delegate called to determined context sensitivity
- L36 _typedef_ `using FOnContextSensitivityChanged = TDelegate<void(bool)>;` (scope `UE::UAF::Editor`) — Delegate called when context sensitivity changes
- L39 _typedef_ `using FOnGetIncludeExcludeFilter = TDelegate<void(EAnimNextExportedVariableFlags& OutFlagInclusionFilter, EAnimNextExportedVariableFlags& OutFlagExclusionFilter)>;` (scope `UE::UAF::Editor`) — Delegate called to get the inclusion/exclusion flags
- L43 _typedef_ `using FOnSubPropertyVariablePicked = TDelegate<void( const FAnimNextSoftVariableReference& , const TArray<FName>& , const FAnimNextParamType& )>;` (scope `UE::UAF::Editor`) — Fired when the user picks a sub-property leaf from inside a struct variable. SubPropertyPath contains the chain of FNames from the top-level variable to the leaf.

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Internal/Workspace/AnimNextWorkspaceFactory.h` (Internal)


#### class `UAnimNextWorkspaceFactory`  
`class UAnimNextWorkspaceFactory : public UWorkspaceFactory`  
_L10-22_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UWorkspaceFactory`
- L14 _private prototype_ `UAnimNextWorkspaceFactory();`
- L17 _private prototype_ `virtual bool ConfigureProperties() override;` — UFactory interface
- L18 _private prototype_ `virtual FText GetDisplayName() const override;`
- L19 _private prototype_ `virtual uint32 GetMenuCategories() const override;`
- L20 _private prototype_ `virtual const TArray<FText>& GetMenuCategorySubMenus() const override;`
- L21 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/AnimNextEditorModule.h` (Private)


#### class `UE::UAF::Editor::FAnimNextEditorModule`  
`class FAnimNextEditorModule : public IAnimNextEditorModule`  
_L30-86_
- inherits: `IAnimNextEditorModule`
- L36 _private prototype_ `virtual void StartupModule() override;`
- L37 _private prototype_ `virtual void ShutdownModule() override;`
- L40 _private prototype_ `virtual void RegisterLocatorFragmentEditorType(FName InLocatorFragmentEditorName) override;` — IAnimNextEditorModule interface
- L41 _private prototype_ `virtual void UnregisterLocatorFragmentEditorType(FName InLocatorFragmentEditorName) override;`
- L42 _private prototype_ `virtual void AddWorkspaceSupportedAssetClass(const FTopLevelAssetPath& InClassAssetPath) override;`
- L43 _private prototype_ `virtual void RemoveWorkspaceSupportedAssetClass(const FTopLevelAssetPath& InClassAssetPath) override;`
- L44 _private prototype_ `virtual FDelegateHandle RegisterGraphMenuActionsProvider(const FOnCollectGraphMenuActionsDelegate& InCollectDelegate) override;`
- L45 _private prototype_ `virtual void UnregisterGraphMenuActionsProvider(const FDelegateHandle& InDelegateHandle) override;`
- L46 _private prototype_ `virtual void RegisterAssetCompilationHandler(const FTopLevelAssetPath& InClassPath, FAssetCompilationHandlerFactoryDelegate InAssetCompilationHandlerFactory) override;`
- L47 _private prototype_ `virtual void UnregisterAssetCompilationHandler(const FTopLevelAssetPath& InClassPath) override;`
- L48 _private prototype_ `virtual FDelegateHandle RegisterNodeDblClickHandler(const FNodeDblClickNotificationDelegate& InNodeDblClickNotificationDelegate) override;`
- L49 _private prototype_ `virtual void UnregisterNodeDblClickHandler(const FDelegateHandle& InDelegateHandle) override;`
- L50 _private prototype_ `virtual void EnableAssetWizard() override;`
- L51 _private prototype_ `virtual void DisableAssetWizard() override;`
- L54 _private prototype_ `void CollectGraphMenuActions(const TWeakPtr<UE::Workspace::IWorkspaceEditor>& WorkspaceEditor, FGraphContextMenuBuilder& InContextMenuBuilder, const FActionMenuContextData& InActionMenuContextData);`
- L56 _private prototype_ `void RegisterWorkspaceDocumentTypes(Workspace::IWorkspaceEditorModule& WorkspaceEditorModule);`
- L57 _private prototype_ `void UnregisterWorkspaceDocumentTypes();`
- L59 _private prototype_ `const FAssetCompilationHandlerFactoryDelegate* FindAssetCompilationHandlerFactory(UClass* InAssetClass) const;`
- L63 _private member_ `TSharedPtr<FParamNamePropertyTypeIdentifier> Identifier;` — Type identifier for parameter names
- L66 _private member_ `TSet<FName> LocatorFragmentEditorNames;` — Registered names for locator fragments
- L68 _private member_ `TArray<FTopLevelAssetPath> SupportedAssetClasses;`
- L70 _private member_ `FCollectGraphMenuActionsMulticast OnCollectGraphMenuActionsDelegateImpl;`
- L71 _private member_ `FNodeDblClickNotificationMulticast OnNodeDblClickHandlerMulticast;`
- L73 _private member_ `TMap<FTopLevelAssetPath, FAssetCompilationHandlerFactoryDelegate> AssetCompilationHandlerFactories;`
- L75 _private member_ `TSharedPtr<FAnimNextGraphPanelPinFactoryEditor> GraphPanelPinFactory;`
- L76 _private member_ `TSharedPtr<FModuleEventPropertyTypeIdentifier> ModuleEventPropertyTypeIdentifier;`
- L77 _private member_ `TSharedPtr<FUAFAssetDataPropertyIdentifier> UAFAssetDataPropertyIdentifier;`
- L79 _private member_ `FTopLevelAssetPath UAFRigVMAssetTopLevelAssetPath;`
- L80 _private member_ `FTopLevelAssetPath SystemTopLevelAssetPath;`
- L81 _private member_ `FTopLevelAssetPath SharedVariablesTopLevelAssetPath;`
- L83 _private member_ `FOutOfDateAssetCompilation PIE_UAFCompilationHandler;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Workspace` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UAF` (scope `UE`)
- L27 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/BindableValue/UAFBindableValueCustomization.h` (Private)


#### class `UE::UAF::Editor::FBindableValueCustomization`  
`class FBindableValueCustomization : public IPropertyTypeCustomization`  
_L22-46_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for FBindableValueBase subclasses (FBindableBool, FBindableFloat, FBindableDouble, etc.). Places the constant-value widget and the SVariablePickerCombo side-by-side in the value content area. Reads/writes FBindableValueBase::Binding directly via EnumerateRawData — Binding has bare UPROPERTY() (no EditAnywhere) so it never appears in the property tree and cannot be reached via GetChildHandle.
- L25 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L30 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> ConstantValueHandle;`
- L38 _private member_ `const UScriptStruct* ResolvedStructClass = nullptr;`
- L39 _private member_ `bool bIsBindableStruct = false;`
- L40 _private member_ `bool bIsBindableTransform = false;`
- L42 _private member_ `bool bIsContextSensitive = true;`
- L43 _private member_ `TArray<TWeakObjectPtr<const UUAFRigVMAsset>> FilterAssets;`
- L44 _private member_ `TWeakObjectPtr<const UUAFRigVMAsset> CurrentRigVMAsset;`
- L45 _private member_ `FOnIsContextSensitive OnIsContextSensitiveDelegate;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextAssetFindReplaceVariables.h` (Private)


#### enum `ESearchScope`  
`enum class ESearchScope : uint8`  
_L26-31_
- reflection: `UENUM()`
- L28 _public enumerator_ `Global` — Filter against assets with AnimNext variable exports
- L29 _public enumerator_ `Workspace` — Filter against assets within workspace and any of their asset references (declaration or reference)
- L30 _public enumerator_ `Asset` — Filter against currently open asset and its recursive reference chain

#### class `UAnimNextAssetFindReplaceVariables`  
`class UAnimNextAssetFindReplaceVariables : public UAnimAssetFindReplaceProcessor`  
_L35-75_
- reflection: `UCLASS(MinimalAPI, DisplayName="UAF Variables")`
- inherits: `UAnimAssetFindReplaceProcessor`
- desc: Find, replace and remove AnimNext variable references across assets
- L40 _public prototype_ `UAnimNextAssetFindReplaceVariables() = default;`
- L42 _public prototype_ `static FSlateIcon GetIconFromSearchScope(ESearchScope InSearchScope);`
- L45 _public prototype_ `virtual FString GetFindResultStringFromAssetData(const FAssetData& InAssetData) const override;`
- L46 _public prototype_ `virtual TConstArrayView<UClass*> GetSupportedAssetTypes() const override;`
- L47 _public prototype_ `virtual bool ShouldFilterOutAsset(const FAssetData& InAssetData, bool& bOutIsOldAsset) const override;`
- L48 _public prototype_ `virtual void ReplaceInAsset(const FAssetData& InAssetData) const override;`
- L49 _public prototype_ `virtual void RemoveInAsset(const FAssetData& InAssetData) const override;`
- L50 _public prototype_ `virtual bool CanCurrentlyReplace() const override;`
- L51 _public function_ `virtual bool CanCurrentlyRemove() const override`
- L52 _public prototype_ `virtual void ExtendToolbar(FToolMenuSection& InSection) override;`
- L53 _public prototype_ `virtual TSharedRef<SWidget> MakeFindReplaceWidget() override;`
- L54 _public function_ `virtual bool SupportsMode(EAnimAssetFindReplaceMode InMode) const override`
- L57 _public prototype_ `void SetFindReferenceFromEntry(const UAnimNextVariableEntry* InVariableEntry);`
- L58 _public prototype_ `void SetFindReference(const FAnimNextSoftVariableReference& InVariableReference, const FAnimNextParamType& InVariableType);`
- L59 _public prototype_ `void SetSearchScope(ESearchScope InSearchScope);`
- L60 _public prototype_ `void SetWorkspaceEditor(TSharedRef<UE::Workspace::IWorkspaceEditor> InWorkspaceEditor);`
- L62 _protected prototype_ `bool IsSearchScopeEnable(ESearchScope InSearchScope) const;`
- L63 _protected prototype_ `ECheckBoxState IsCurrentSearchScope(ESearchScope InSearchScope) const;`
- L64 _protected prototype_ `void OnWorkspaceDocumentChanged(const UE::Workspace::FWorkspaceDocument& InDocument);`
- L66 _protected member_ `TSharedPtr<UE::UAF::Editor::SVariablePickerCombo> SearchVariableComboBox;`
- L67 _protected member_ `TSharedPtr<UE::UAF::Editor::SVariablePickerCombo> ReplaceVariableComboBox;`
- L69 _protected member_ `FAnimNextSoftVariableReference SearchReference;`
- L70 _protected member_ `FAnimNextParamType SearchType;`
- L71 _protected member_ `FAnimNextSoftVariableReference ReplaceReference;`
- L72 _protected member_ `ESearchScope CurrentSearchScope = ESearchScope::Global;`
- L74 _protected member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WeakWorkspaceEditor = nullptr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextCollapseNodeItemDetails.h` (Private)


#### class `UE::UAF::Editor::FAnimNextCollapseNodeItemDetails`  
`class FAnimNextCollapseNodeItemDetails : public UE::Workspace::IWorkspaceOutlinerItemDetails`  
_L10-28_
- inherits: `UE::Workspace::IWorkspaceOutlinerItemDetails`
- L13 _public prototype_ `FAnimNextCollapseNodeItemDetails() = default;`
- L14 _public prototype_ `virtual ~FAnimNextCollapseNodeItemDetails() override = default;`
- L16 _public prototype_ `virtual bool HandleDoubleClick(const FToolMenuContext& ToolMenuContext) const override;`
- L17 _public prototype_ `virtual bool CanDelete(const FWorkspaceOutlinerItemExport& Export) const override;`
- L18 _public prototype_ `virtual void Delete(TConstArrayView<FWorkspaceOutlinerItemExport> Exports) const override;`
- L19 _public prototype_ `virtual bool CanRename(const FWorkspaceOutlinerItemExport& Export) const override;`
- L20 _public prototype_ `virtual void Rename(const FWorkspaceOutlinerItemExport& Export, const FText& InName) const override;`
- L21 _public prototype_ `virtual bool ValidateName(const FWorkspaceOutlinerItemExport& Export, const FText& InName, FText& OutErrorMessage) const override;`
- L22 _public prototype_ `virtual UPackage* GetPackage(const FWorkspaceOutlinerItemExport& Export) const override;`
- L23 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`
- L24 _public prototype_ `virtual FString GetDisplayString(const FWorkspaceOutlinerItemExport& Export) const override;`
- L26 _public prototype_ `static void RegisterToolMenuExtensions();`
- L27 _public prototype_ `static void UnregisterToolMenuExtensions();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextCompilerResultsTabSummoner.h` (Private)


#### class `UE::UAF::Editor::SAnimNextCompilerResultsWidget`  
`class SAnimNextCompilerResultsWidget : public SCompoundWidget`  
_L15-37_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAnimNextCompilerResultsWidget)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditorWeak);`
- L24 _public function_ `inline TSharedPtr<class IMessageLogListing> GetCompilerResultsListing() const`
- L30 _private prototype_ `void CreateMessageLog(const TWeakPtr<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditorWeak);`
- L32 _private prototype_ `void HandleMessageTokenClicked(const TSharedRef<IMessageToken>& InToken);`
- L34 _private member_ `TSharedPtr<class IMessageLogListing> CompilerResultsListing;`
- L35 _private member_ `TSharedPtr<class SWidget> CompilerResults;`
- L36 _private member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WorkspaceEditorWeak;`

#### struct `UE::UAF::Editor::FAnimNextCompilerResultsTabSummoner`  
`struct FAnimNextCompilerResultsTabSummoner : public FWorkflowTabFactory`  
_L39-51_
- inherits: `FWorkflowTabFactory`
- L42 _public prototype_ `FAnimNextCompilerResultsTabSummoner(TSharedPtr<UE::Workspace::IWorkspaceEditor> InHostingApp);`
- L46 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L47 _private prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L50 _private member_ `TSharedPtr<class SAnimNextCompilerResultsWidget> AnimNextCompilerResultsWidget;` — The widget this tab spawner wraps

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Workspace` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextEdGraphNodeCustomization.h` (Private)


#### class `UE::UAF::Editor::FAnimNextEdGraphNodeCustomization`  
`class FAnimNextEdGraphNodeCustomization : public IDetailCustomization`  
_L28-146_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `FAnimNextEdGraphNodeCustomization() = default;`
- L32 _public prototype_ `explicit FAnimNextEdGraphNodeCustomization(const TWeakPtr<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditorWeak);`
- L38 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Called when details should be customized
- L40 _protected prototype_ `virtual void PendingDelete() override;` — Called when no longer used and will be deleted
- L106 _protected prototype_ `void CustomizeObjects(IDetailLayoutBuilder& DetailBuilder, const TArray<UObject*>& InObjects);`
- L108 _protected prototype_ `static void GenerateTraitData(UAnimNextEdGraphNode* EdGraphNode, TArray<TSharedPtr<FCategoryDetailsData>>& CategoryDetailsData);`
- L109 _protected prototype_ `static void GenerateRigVMData(UAnimNextEdGraphNode* EdGraphNode, TArray<TSharedPtr<FCategoryDetailsData>>& CategoryDetailsData);`
- L111 _protected prototype_ `static void PopulateCategory(IDetailLayoutBuilder& DetailBuilder, const TSharedPtr<FCategoryDetailsData>& CategoryDetailsData);`
- L112 _protected prototype_ `static void PopulateCategory(IDetailLayoutBuilder& DetailBuilder, const TSharedPtr<FTraitStackDetailsData>& TraitData);`
- L113 _protected prototype_ `static void PopulateCategory(IDetailLayoutBuilder& DetailBuilder, const TSharedPtr<FRigVMNodeDetailsData>& RigVMTypeData);`
- L115 _protected prototype_ `static void GenerateMemoryStorage(const TArray<TWeakObjectPtr<URigVMPin>> & ModelPinsToDisplay, FRigVMMemoryStorageStruct& MemoryStorage);`
- L117 _protected prototype_ `URigVMNode* GetNodeForLayout() const;`
- L118 _protected prototype_ `const FRigVMNodeLayout* GetNodeLayout() const;`
- L119 _protected prototype_ `TArray<FString> GetUncategorizedPins() const;`
- L120 _protected prototype_ `TArray<FRigVMPinCategory> GetPinCategories() const;`
- L121 _protected prototype_ `FString GetPinCategory(FString InPinPath) const;`
- L122 _protected prototype_ `int32 GetPinIndexInCategory(FString InPinPath) const;`
- L123 _protected prototype_ `FString GetPinLabel(FString InPinPath) const;`
- L124 _protected prototype_ `FLinearColor GetPinColor(FString InPinPath) const;`
- L125 _protected prototype_ `const FSlateBrush* GetPinIcon(FString InPinPath) const;`
- L126 _protected prototype_ `void HandleCategoryAdded(FString InCategory);`
- L127 _protected prototype_ `void HandleCategoryRemoved(FString InCategory);`
- L128 _protected prototype_ `void HandleCategoryRenamed(FString InOldCategory, FString InNewCategory);`
- L129 _protected prototype_ `void HandlePinCategoryChanged(FString InPinPath, FString InCategory);`
- L130 _protected prototype_ `void HandlePinLabelChanged(FString InPinPath, FString InNewLabel);`
- L131 _protected prototype_ `void HandlePinIndexInCategoryChanged(FString InPinPath, int32 InIndexInCategory);`
- L132 _protected prototype_ `static bool ValidateName(FString InNewName, FText& OutErrorMessage);`
- L133 _protected prototype_ `bool HandleValidateCategoryName(FString InCategoryPath, FString InNewName, FText& OutErrorMessage);`
- L134 _protected prototype_ `bool HandleValidatePinDisplayName(FString InPinPath, FString InNewName, FText& OutErrorMessage);`
- L135 _protected prototype_ `uint32 GetNodeLayoutHash() const;`
- L138 _protected member_ `TWeakInterfacePtr<IRigVMClientHost> WeakRigVMClientHost;` — The asset host we are editing
- L139 _protected member_ `TWeakObjectPtr<URigVMNode> WeakModelNode;`
- L140 _protected member_ `mutable TOptional<FRigVMNodeLayout> CachedNodeLayout;`
- L142 _protected member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WorkspaceEditorWeak;`
- L143 _protected member_ `TArray<TSharedPtr<FCategoryDetailsData>> CategoryDetailsData;`
- L145 _protected member_ `TSharedPtr<FRigVMGraphDetailCustomizationImpl> RigVMGraphDetailCustomizationImpl;`

#### struct `UE::UAF::Editor::FAnimNextEdGraphNodeCustomization::FCategoryDetailsData`  
`struct FCategoryDetailsData`  
_L44-69_
- L55 _public prototype_ `FCategoryDetailsData() = default;`
- L56 _public function_ `explicit FCategoryDetailsData(EType InType) : Type(InType)`
- L60 _public function_ `FCategoryDetailsData(EType InType, const FName& InName) : Type(InType) , Name(InName)`
- L66 _public member_ `EType Type = EType::Invalid;`
- L67 _public member_ `FName Name;`
- L68 _public member_ `TArray<TWeakObjectPtr<UAnimNextEdGraphNode>> EdGraphNodes;`

#### enum `UE::UAF::Editor::FAnimNextEdGraphNodeCustomization::FCategoryDetailsData::EType`  
`enum class EType : uint8`  
_L46-53_
- L48 _public enumerator_ `TraitStack = 0`
- L49 _public enumerator_ `RigVMNode`
- L51 _public enumerator_ `Invalid` — --- ---
- L52 _public enumerator_ `Num = Invalid`

#### struct `UE::UAF::Editor::FAnimNextEdGraphNodeCustomization::FTraitStackDetailsData`  
`struct FTraitStackDetailsData : FCategoryDetailsData`  
_L71-88_
- inherits: `FCategoryDetailsData`
- L73 _public function_ `FTraitStackDetailsData() : FCategoryDetailsData(FCategoryDetailsData::EType::TraitStack)`
- L77 _public function_ `explicit FTraitStackDetailsData(const FName InName, int32 InInstanceIndex) : FCategoryDetailsData(FCategoryDetailsData::EType::TraitStack, InName) , InstanceIndex(InInstanceIndex)`
- L83 _public member_ `TArray<TSharedPtr<FStructOnScope>> ScopedSharedDataInstances;`
- L84 _public member_ `TSharedPtr<IPropertyHandle> RootPropertyHandle;`
- L85 _public member_ `TArray<TSharedRef<IPropertyHandle>> PropertyHandles;`
- L87 _public member_ `int32 InstanceIndex;` — For traits that appear more than once, this allows us to disambiguate

#### struct `UE::UAF::Editor::FAnimNextEdGraphNodeCustomization::FRigVMNodeDetailsData`  
`struct FRigVMNodeDetailsData : FCategoryDetailsData`  
_L90-104_
- inherits: `FCategoryDetailsData`
- L92 _public function_ `FRigVMNodeDetailsData() : FCategoryDetailsData(FCategoryDetailsData::EType::RigVMNode)`
- L96 _public function_ `explicit FRigVMNodeDetailsData(const FName InName) : FCategoryDetailsData(FCategoryDetailsData::EType::RigVMNode, InName)`
- L101 _public member_ `TArray<FName> ModelPinsNamesToDisplay;`
- L102 _public member_ `TArray <TArray<FString>> ModelPinPaths;`
- L103 _public member_ `TArray <TSharedPtr<FRigVMMemoryStorageStruct>> MemoryStorages;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Workspace` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace UAF` (scope `UE`)
- L25 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextEntryAssetDefinitions.h` (Private)


#### class `UAssetDefinition_AnimNextVariableEntry`  
`class UAssetDefinition_AnimNextVariableEntry : public UAssetDefinitionDefault`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L20 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition interface
- L21 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L23 _public prototype_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override;`

#### class `UAssetDefinition_AnimNextEventGraphEntry`  
`class UAssetDefinition_AnimNextEventGraphEntry : public UAssetDefinitionDefault`  
_L27-37_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L33 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition interface
- L34 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L35 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L36 _public prototype_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override;`

#### class `UAssetDefinition_AnimNextSharedVariablesEntry`  
`class UAssetDefinition_AnimNextSharedVariablesEntry : public UAssetDefinitionDefault`  
_L40-50_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L46 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition interface
- L47 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L48 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L49 _public prototype_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "AnimNextAssetDefinitions"`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextFindTabSummoner.h` (Private)


#### struct `UE::UAF::Editor::FAnimNextFindTabSummoner`  
`struct FAnimNextFindTabSummoner : public FWorkflowTabFactory`  
_L22-34_
- inherits: `FWorkflowTabFactory`
- L25 _public prototype_ `FAnimNextFindTabSummoner(TSharedPtr<UE::Workspace::IWorkspaceEditor> InHostingApp);`
- L29 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L30 _private prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L33 _private member_ `TSharedPtr<SFindInAnimNextRigVMAsset> AnimNextFindResultsWidget;` — The widget this tab spawner wraps

#### struct `UE::UAF::Editor::FAnimNextFindAndReplaceTabSummoner`  
`struct FAnimNextFindAndReplaceTabSummoner : public FWorkflowTabFactory`  
_L36-48_
- inherits: `FWorkflowTabFactory`
- L39 _public prototype_ `FAnimNextFindAndReplaceTabSummoner(TSharedPtr<UE::Workspace::IWorkspaceEditor> InHostingApp);`
- L43 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L44 _private prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L47 _private member_ `TSharedPtr<IAnimAssetFindReplace> FindAndReplaceWidget;` — The widget this tab spawner wraps

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Workspace` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextGraphItemDetails.h` (Private)


#### class `UE::UAF::Editor::FAnimNextGraphItemDetails`  
`class FAnimNextGraphItemDetails : public UE::Workspace::IWorkspaceOutlinerItemDetails`  
_L10-26_
- inherits: `UE::Workspace::IWorkspaceOutlinerItemDetails`
- L13 _public prototype_ `FAnimNextGraphItemDetails() = default;`
- L14 _public prototype_ `virtual ~FAnimNextGraphItemDetails() override = default;`
- L15 _public prototype_ `virtual bool HandleDoubleClick(const FToolMenuContext& ToolMenuContext) const override;`
- L16 _public prototype_ `virtual bool CanDelete(const FWorkspaceOutlinerItemExport& Export) const override;`
- L17 _public prototype_ `virtual void Delete(TConstArrayView<FWorkspaceOutlinerItemExport> Exports) const override;`
- L18 _public prototype_ `virtual bool CanRename(const FWorkspaceOutlinerItemExport& Export) const override;`
- L19 _public prototype_ `virtual void Rename(const FWorkspaceOutlinerItemExport& Export, const FText& InName) const override;`
- L20 _public prototype_ `virtual bool ValidateName(const FWorkspaceOutlinerItemExport& Export, const FText& InName, FText& OutErrorMessage) const override;`
- L21 _public prototype_ `virtual UPackage* GetPackage(const FWorkspaceOutlinerItemExport& Export) const override;`
- L22 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`
- L24 _public prototype_ `static void RegisterToolMenuExtensions();`
- L25 _public prototype_ `static void UnregisterToolMenuExtensions();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextModuleItemDetails.h` (Private)


#### class `UE::UAF::Editor::FAnimNextModuleItemDetails`  
`class FAnimNextModuleItemDetails : public UE::Workspace::IWorkspaceOutlinerItemDetails`  
_L10-16_
- inherits: `UE::Workspace::IWorkspaceOutlinerItemDetails`
- L13 _public prototype_ `FAnimNextModuleItemDetails() = default;`
- L14 _public prototype_ `virtual ~FAnimNextModuleItemDetails() override = default;`
- L15 _public prototype_ `virtual const FSlateBrush* GetItemIcon(const FWorkspaceOutlinerItemExport& Export) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AnimNextRigVMAssetCommands.h` (Private)


#### class `UE::UAF::FAnimNextRigVMAssetCommands`  
`class FAnimNextRigVMAssetCommands : public TCommands<FAnimNextRigVMAssetCommands>`  
_L11-23_
- inherits: `TCommands<FAnimNextRigVMAssetCommands>`
- desc: Shared commands valid for any UAF RigVM Asset.
- L14 _public prototype_ `FAnimNextRigVMAssetCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> FindInAnimNextRigVMAsset;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> FindAndReplaceInAnimNextRigVMAsset;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> OpenUAFBrowser;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/AssetPreview/AnimSequenceAssetPreview.h` (Private)


#### struct `UE::UAF::Editor::FAnimSequenceAssetPreviewFactory`  
`struct FAnimSequenceAssetPreviewFactory : public FUAFAssetPreviewFactory`  
_L21-29_
- inherits: `FUAFAssetPreviewFactory`
- desc: Experimental. May be removed / relocated whenever we switch to the future generic content browser IAssetPreviewCustomization API. Factory for Anim Sequence Asset Preview widgets
- L26 _public prototype_ `virtual TSharedRef<IUAFAssetPreview> CreateAssetPreviewWidget(TSharedPtr<FAssetEditorToolkit> InAssetEditorToolkit, const FAssetData& InAssetData) const override;`
- L27 _public prototype_ `virtual const UStruct* GetPreviewType() const override;`

#### class `UE::UAF::Editor::SAnimSequenceAssetPreview`  
`class SAnimSequenceAssetPreview : public IUAFAssetViewportPreview`  
_L36-58_
- inherits: `IUAFAssetViewportPreview`
- desc: Experimental. May be removed / relocated whenever we switch to the future generic content browser IAssetPreviewCustomization API. Preview widget for anim sequences. Includes an interactable viewport.
- L41 _public prototype_ `virtual const UStruct* GetAssetPreviewType() const override;`
- L47 _protected prototype_ `virtual bool OnSameTypeAssetSelected(const FAssetData& InAssetData) override;`
- L51 _protected prototype_ `virtual void OnCustomizePreviewScene(FAdvancedPreviewScene& InPreviewScene, FEditorViewportClient& InEditorViewportClient) override;`
- L57 _protected member_ `UDebugSkelMeshComponent* PreviewComponent = nullptr;` — Skeletal component to preview the animation asset on. Lifetime maintained by PreviewScene in IUAFAssetViewportPreview

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/CommonOutlinerMode.h` (Private)


#### class `UE::UAF::Editor::FCommonOutlinerMode`  
`class FCommonOutlinerMode : public ISceneOutlinerMode`  
_L24-147_
- inherits: `ISceneOutlinerMode`
- L27 _public prototype_ `FCommonOutlinerMode(SSceneOutliner* InOutliner, const TSharedRef<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditor);`
- L30 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L31 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& OutCommandList) override;`
- L32 _public function_ `virtual bool CanRename() const override`
- L33 _public function_ `virtual bool CanDelete() const override`
- L34 _public function_ `virtual bool CanCopy() const override`
- L35 _public function_ `virtual bool CanCut() const override`
- L36 _public function_ `virtual bool CanPaste() const override`
- L37 _public prototype_ `virtual void OnItemClicked(FSceneOutlinerTreeItemPtr Item) override;`
- L38 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L39 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L40 _public function_ `virtual bool CanCustomizeToolbar() const override`
- L41 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L42 _public function_ `virtual bool CanSupportDragAndDrop() const override`
- L43 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const override;`
- L44 _public prototype_ `virtual bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const override;`
- L45 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L46 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L47 _public prototype_ `virtual FReply OnDragOverItem(const FDragDropEvent& Event, const ISceneOutlinerTreeItem& Item) const override;`
- L48 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L49 _public prototype_ `virtual int32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const override;`
- L52 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& InOutContext) const;`
- L54 _public prototype_ `void SetHighlightedItem(FSceneOutlinerTreeItemID InID) const;`
- L55 _public prototype_ `void ClearHighlightedItem(FSceneOutlinerTreeItemID InID) const;`
- L57 _public prototype_ `void SaveAsset() const;`
- L58 _public prototype_ `bool CanSaveAsset() const;`
- L59 _public prototype_ `void GetAssets(TArray<TSoftObjectPtr<UUAFRigVMAsset>>& OutAssets) const;`
- L60 _public prototype_ `SCommonOutliner* GetOutliner() const;`
- L62 _protected function_ `virtual void HandleItemSelection(const FSceneOutlinerItemSelection& Selection) const`
- L63 _protected function_ `virtual void Rename() const`
- L64 _protected function_ `virtual void Delete() const`
- L65 _protected function_ `virtual void Copy() const`
- L66 _protected function_ `virtual void Cut() const`
- L67 _protected function_ `virtual void Paste() const`
- L68 _protected function_ `virtual bool CanDuplicate() const`
- L69 _protected function_ `virtual void Duplicate() const`
- L70 _protected prototype_ `virtual void RegisterToolMenus();`
- L71 _protected function_ `virtual void AddCategory(TWeakObjectPtr<UUAFRigVMAssetEditorData> InWeakEditorData) const`
- L72 _protected function_ `virtual bool CanAddCategory(TWeakObjectPtr<UUAFRigVMAssetEditorData> InWeakEditorData) const`
- L73 _protected function_ `virtual void ReorderEntryItem(TSharedPtr<FOutlinerEntryItem> EntryItem, TSharedPtr<FOutlinerEntryItem> BeforeItem)`
- L74 _protected function_ `virtual void ReorderCategoryItem(TSharedPtr<FOutlinerCategoryItem> EntryItem, TSharedPtr<FOutlinerCategoryItem> BeforeItem) const`
- L75 _protected function_ `virtual void ReorderCategory(const FString& CategoryPath, const FString& BeforeCategoryPath, UUAFRigVMAsset* Asset) const`
- L76 _protected function_ `virtual void MoveCategoryToAsset(const FString& CategoryPath, UUAFRigVMAsset* FromAsset, UUAFRigVMAsset* ToAsset) const`
- L78 _protected function_ `virtual void FindReferences(ESearchScope InSearchScope) const`
- L79 _protected function_ `virtual bool CanFindReferences() const`
- L80 _protected function_ `virtual bool IsFindReferencesVisible(ESearchScope InSearchScope) const`
- L82 _protected prototype_ `void ResetOutlinerSelection() const;`
- L84 _protected prototype_ `void SetEntryExportAccessSpecifiersOnSelection(EAnimNextExportAccessSpecifier AnimNextExportAccessSpecifier) const;`
- L85 _protected prototype_ `bool CanModifyEntryExport() const;`
- L87 _protected prototype_ `void SetExpansionOnSelectedEntries(bool bExpand) const;`
- L88 _protected prototype_ `bool CanExpandEntries() const;`
- L89 _protected prototype_ `bool CanCollapseEntries() const;`
- L92 _protected typedef_ `typedef TFunction<TSharedPtr<FDragDropOperation>(const FSceneOutlinerTreeItemPtr&)> FDragDropOpConstructor;`
- L93 _protected member_ `TMap<FSceneOutlinerTreeItemType, FDragDropOpConstructor> ItemTypeToDragDropOpMap;`
- L96 _protected function_ `template<typename TreeItem> void RegisterDragDropOperationConstructor(FDragDropOpConstructor&& InFunc)`
- L101 _protected typedef_ `typedef TFunction<void(FSceneOutlinerDragDropPayload&, const FDragDropOperation&)> FDragDropOpParser;`
- L102 _protected member_ `TMap<FString, FDragDropOpParser> DragDropOperationTypeToParseFunc;`
- L105 _protected function_ `template<typename DragDropOpType> void RegisterDragDropOperationParser(FDragDropOpParser&& InFunc)`
- L110 _protected typedef_ `typedef TFunction<bool(ISceneOutlinerTreeItem&, TSharedRef<const FDragDropOperation>)> FHandleDragDropFunc;`
- L111 _protected typedef_ `typedef TFunction<FReply(const ISceneOutlinerTreeItem&, TSharedRef<FDragDropOperation>, FSceneOutlinerDragValidationInfo& OutInfo)> FHandleDragOverFunc;`
- L128 _protected member_ `TArray<FDragDropOperator> DragDropOperators;`
- L131 _protected function_ `template<typename SourceTreeItemType, typename TargetTreeItemType, typename DragDropOperationType> void RegisterDragDropOperator(FHandleDragOverFunc&& InDragOverFunc, FHandleDragDropFunc&& InDropFunc)`
- L139 _protected member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WeakWorkspaceEditor;`
- L140 _protected member_ `TSharedPtr<FUICommandList> CommandList;`
- L143 _public member_ `static FName ContextToolMenuName;`
- L144 _public member_ `static FName ContextToolAssetSectionName;`
- L145 _public member_ `static FName ContextToolEntrySectionName;`
- L146 _public member_ `static FName AddEntryContextMenuName;`

#### struct `UE::UAF::Editor::FCommonOutlinerMode::FDragDropOperator`  
`struct FDragDropOperator`  
_L112-126_
- L114 _public function_ `bool operator==(const FDragDropOperator& Other) const`
- L121 _public member_ `FSceneOutlinerTreeItemType TargetType;`
- L122 _public member_ `FSceneOutlinerTreeItemType SourceType;`
- L123 _public member_ `FString OpType;`
- L124 _public member_ `FHandleDragOverFunc DragOverFunc;`
- L125 _public member_ `FHandleDragDropFunc DragDropFunc;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerAssetItem.h` (Private)


#### struct `UE::UAF::Editor::FOutlinerAssetItem`  
`struct FOutlinerAssetItem : FOutlinerItem`  
_L16-55_
- inherits: `FOutlinerItem`
- L18 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L27 _public prototype_ `FOutlinerAssetItem(FSceneOutlinerTreeItemType InType, const FItemData& InItemData);`
- L28 _public function_ `FOutlinerAssetItem(const FItemData& InItemData) : FOutlinerAssetItem(Type, InItemData)`
- L29 _public prototype_ `virtual ~FOutlinerAssetItem() override = default;`
- L32 _public prototype_ `virtual bool IsValid() const override;`
- L33 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L34 _public prototype_ `virtual FString GetDisplayString() const override;`
- L35 _public function_ `virtual bool CanInteract() const override`
- L36 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L37 _public prototype_ `virtual FString GetPackageName() const override;`
- L41 _public prototype_ `virtual void Rename(const FText& InNewName) const override;` — Renames the item to the specified name
- L44 _public prototype_ `virtual bool ValidateName(const FText& InNewName, FText& OutErrorMessage) const override;` — Validates the new item name
- L46 _public prototype_ `FReply OnSharedVariableWidgetMouseUp(const FGeometry&, const FPointerEvent& PointerEvent, const FSoftObjectPath ClickedSharedVariablesPath) const;`
- L47 _public prototype_ `FReply OnRemoveSharedVariable(const FSoftObjectPath ClickedSharedVariablesPath) const;`
- L50 _public member_ `TSoftObjectPtr<UUAFRigVMAsset> SoftAsset;` — Soft ptr to the underlying asset, which may not be loaded yet
- L52 _public member_ `TArray<const FSoftObjectPath> SharedVariableSourcePaths;`
- L54 _public member_ `TSharedPtr<class SOutlinerAssetLabel> AssetLabel;`

#### struct `UE::UAF::Editor::FOutlinerAssetItem::FItemData`  
`struct FItemData`  
_L20-25_
- L22 _public member_ `const TSoftObjectPtr<UUAFRigVMAsset>& Asset;`
- L23 _public member_ `const int32 SortValue;`
- L24 _public member_ `const TArrayView<const FSoftObjectPath> ImplementedSharedVariablesPaths;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerCategoryItem.h` (Private)


#### struct `UE::UAF::Editor::FOutlinerCategoryItem`  
`struct FOutlinerCategoryItem : FOutlinerItem`  
_L13-39_
- inherits: `FOutlinerItem`
- L15 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L27 _public prototype_ `FOutlinerCategoryItem(FSceneOutlinerTreeItemType InType, const FItemData& InItemData);`
- L30 _public function_ `virtual bool CanInteract() const override`
- L31 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override final;`
- L32 _public prototype_ `virtual FString GetDisplayString() const override final;`
- L33 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L36 _public member_ `FString CategoryName;`
- L37 _public member_ `FString ParentCategoryName;`
- L38 _public member_ `FString CategoryPath;`

#### struct `UE::UAF::Editor::FOutlinerCategoryItem::FItemData`  
`struct FItemData`  
_L17-25_
- L19 _public member_ `TWeakObjectPtr<UUAFRigVMAsset> InWeakOwner;`
- L20 _public member_ `int32 SortValue;`
- L22 _public member_ `FStringView InCategoryName;`
- L23 _public member_ `FStringView InParentCategoryName;`
- L24 _public member_ `FStringView InCategoryPath;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerColumns.h` (Private)


#### class `UE::UAF::Editor::FOutlinerAccessSpecifierColumn`  
`class FOutlinerAccessSpecifierColumn : public ISceneOutlinerColumn`  
_L9-24_
- inherits: `ISceneOutlinerColumn`
- L12 _public prototype_ `static FName GetID();`
- L14 _public prototype_ `FOutlinerAccessSpecifierColumn(ISceneOutliner& SceneOutliner);`
- L17 _public function_ `virtual FName GetColumnID() override final` — ISceneOutlinerColumn interface
- L18 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override final;`
- L19 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override final;`
- L20 _public function_ `virtual bool SupportsSorting() const override final`
- L23 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerCommands.h` (Private)


#### class `UE::UAF::Editor::FOutlinerCommands`  
`class FOutlinerCommands : public TCommands<FOutlinerCommands>`  
_L12-31_
- inherits: `TCommands<FOutlinerCommands>`
- L16 _public function_ `FOutlinerCommands() : TCommands<FOutlinerCommands>( TEXT("Outliner"), LOCTEXT("OutlinerCommandsLabel", "Outliner Commands"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L20 _public prototype_ `virtual void RegisterCommands() override;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> SaveAsset;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> FindReferences;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> FindReferencesInWorkspace;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> FindReferencesInAsset;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> MakeEntryPublic;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> MakeEntryPrivate;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> OpenInNewTab;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ExpandEntries;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> CollapseEntries;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "OutlinerCommands"`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerDragDropOps.h` (Private)


#### class `UE::UAF::Editor::FVariableDragDropOp`  
`class FVariableDragDropOp : public FGraphSchemaActionDragDropAction`  
_L19-33_
- inherits: `FGraphSchemaActionDragDropAction`
- L22 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FVariableDragDropOp, FGraphSchemaActionDragDropAction) static TSharedPtr<FVariableDragDropOp> New(TSharedPtr<FAnimNextSchemaAction_Variable> InAction, TSharedPtr<FVariablesOutlinerEntryItem> InEntry);`
- L27 _public prototype_ `virtual void GetDefaultStatusSymbol(const FSlateBrush*& PrimaryBrushOut, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut) const override;` — FGraphSchemaActionDragDropAction interface
- L28 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L30 _public prototype_ `TSharedPtr<FAnimNextSchemaAction_Variable> GetAction() const;`
- L32 _public member_ `TWeakPtr<FVariablesOutlinerEntryItem> WeakItem;`

#### class `UE::UAF::Editor::FFunctionDragDropOp`  
`class FFunctionDragDropOp : public FGraphSchemaActionDragDropAction`  
_L35-48_
- inherits: `FGraphSchemaActionDragDropAction`
- L38 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FFunctionDragDropOp, FGraphSchemaActionDragDropAction) static TSharedPtr<FFunctionDragDropOp> New(TSharedPtr<FAnimNextSchemaAction_Function> InAction, TSharedPtr<FFunctionsOutlinerEntryItem> InEntry);`
- L43 _public prototype_ `virtual void GetDefaultStatusSymbol(const FSlateBrush*& PrimaryBrushOut, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut) const override;` — FGraphSchemaActionDragDropAction interface
- L45 _public prototype_ `TSharedPtr<FAnimNextSchemaAction_Function> GetAction() const;`
- L47 _public member_ `TWeakPtr<FFunctionsOutlinerEntryItem> WeakItem;`

#### class `UE::UAF::Editor::FCategoryDragDropOp`  
`class FCategoryDragDropOp : public FDecoratedDragDropOp`  
_L50-58_
- inherits: `FDecoratedDragDropOp`
- L53 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FCategoryDragDropOp, FDecoratedDragDropOp) static TSharedPtr<FCategoryDragDropOp> New(TSharedPtr<FOutlinerCategoryItem> InEntry);`
- L57 _public member_ `TWeakPtr<FOutlinerCategoryItem> WeakItem;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerEntryItem.h` (Private)


#### struct `UE::UAF::Editor::FOutlinerEntryItem`  
`struct FOutlinerEntryItem : FOutlinerItem`  
_L12-27_
- inherits: `FOutlinerItem`
- L14 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L16 _public prototype_ `FOutlinerEntryItem(FSceneOutlinerTreeItemType InType, const FItemData& InItemData);`
- L17 _public function_ `virtual ~FOutlinerEntryItem() override`
- L19 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L21 _public prototype_ `virtual bool IsReadOnly() const = 0;`
- L22 _public prototype_ `virtual void SetAccessSpecifier(const EAnimNextExportAccessSpecifier& InSpecifier) const = 0;`
- L23 _public prototype_ `virtual EAnimNextExportAccessSpecifier GetAccessSpecifier() const = 0;`
- L24 _public prototype_ `virtual bool CanSetAccessSpecifier() const = 0;`
- L25 _public prototype_ `virtual FStringView GetCategoryPath() const = 0;`
- L26 _public function_ `virtual void GetItemIconAndColor(const FSlateBrush*& OutIcon, FSlateColor& OutColor) const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerEntryItemWidget.h` (Private)


#### class `UE::UAF::Editor::SOutlinerEntryLabel`  
`class SOutlinerEntryLabel : FSceneOutlinerCommonLabelData, public SCompoundWidget`  
_L14-34_
- inherits: `FSceneOutlinerCommonLabelData,SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(SOutlinerEntryLabel)`
- L17 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FOutlinerEntryItem& InTreeItem, ISceneOutliner& SceneOutliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow);`
- L21 _private prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L23 _protected prototype_ `FText GetDirtyTooltipText() const;`
- L24 _protected prototype_ `const FSlateBrush* GetDirtyImageBrush() const;`
- L25 _protected prototype_ `FText GetDisplayText() const;`
- L26 _protected prototype_ `void OnTextCommited(const FText& InLabel, ETextCommit::Type InCommitInfo) const;`
- L27 _protected prototype_ `bool OnVerifyTextChanged(const FText& InLabel, FText& OutErrorMessage) const;`
- L28 _protected prototype_ `bool IsReadOnly() const;`
- L30 _protected member_ `TWeakPtr<FOutlinerEntryItem> TreeItem;`
- L31 _protected member_ `TSharedPtr<SInlineEditableTextBlock> TextBlock;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerHierarchy.h` (Private)


#### class `UE::UAF::Editor::FOutlinerHierarchy`  
`class FOutlinerHierarchy : public ISceneOutlinerHierarchy`  
_L16-35_
- inherits: `ISceneOutlinerHierarchy`
- L19 _public prototype_ `FOutlinerHierarchy(ISceneOutlinerMode* Mode);`
- L20 _public prototype_ `FOutlinerHierarchy(const FOutlinerHierarchy&) = delete;`
- L21 _public prototype_ `FOutlinerHierarchy& operator=(const FOutlinerHierarchy&) = delete;`
- L24 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`
- L25 _public function_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override`
- L26 _public prototype_ `virtual void CreateItemsForAsset(const UUAFRigVMAssetEditorData* EditorData, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const = 0;`
- L29 _protected prototype_ `void ProcessAsset(const TSoftObjectPtr<UUAFRigVMAsset>& InSoftAsset, int32 Depth, TArray<FSceneOutlinerTreeItemPtr>& OutItems, TArray<const FSoftObjectPath>& OutSharedVariableSourcePaths) const;`
- L30 _protected prototype_ `void RetrieveSharedAssetPaths(const TSoftObjectPtr<UUAFRigVMAsset>& InSoftAsset, TArray<const FSoftObjectPath>& OutSharedVariableSourcePaths) const;`
- L32 _protected member_ `mutable TSet<TWeakObjectPtr<const UUAFRigVMAsset>> WeakProcessedAssets;`
- L33 _protected member_ `mutable TSet<TWeakObjectPtr<const UScriptStruct>> WeakProcessedStructs;`
- L34 _protected member_ `mutable TSet<TWeakObjectPtr<const UObject>> WeakProcessedRigVMAssets;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L15 _externvar_ `extern TAutoConsoleVariable<bool> GOutputHierarchyDebugInformationCvar;` (scope `UE::UAF::Editor`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerItem.h` (Private)


#### struct `UE::UAF::Editor::FOutlinerItem`  
`struct FOutlinerItem : ISceneOutlinerTreeItem`  
_L11-35_
- inherits: `ISceneOutlinerTreeItem`
- L13 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L20 _public function_ `FOutlinerItem(FSceneOutlinerTreeItemType InType, const FItemData& InItemData) : ISceneOutlinerTreeItem(InType), WeakOwner(InItemData.Asset), SortValue(InItemData.SortValue)`
- L23 _public prototype_ `virtual FString GetPackageName() const override;`
- L24 _public prototype_ `virtual bool IsValid() const override;`
- L28 _public function_ `virtual void Rename(const FText& InNewName) const` — Renames the item to the specified name
- L30 _public function_ `virtual bool ValidateName(const FText& InNewName, FText& OutErrorMessage) const` — Validates the new item name
- L31 _public prototype_ `virtual UPackage* GetPackage() const;`
- L33 _public member_ `TWeakObjectPtr<UUAFRigVMAsset> WeakOwner;`
- L34 _public member_ `int32 SortValue = 0;`

#### struct `UE::UAF::Editor::FOutlinerItem::FItemData`  
`struct FItemData`  
_L14-18_
- L16 _public member_ `const TWeakObjectPtr<UUAFRigVMAsset>& Asset;`
- L17 _public member_ `const int32 SortValue;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/OutlinerItemMenuContexts.h` (Private)


#### class `UE::UAF::Editor::UVariablesOutlinerItemMenuContext`  
`class UVariablesOutlinerItemMenuContext : public UObject`  
_L22-30_
- reflection: `UCLASS()`
- inherits: `UObject`
- L29 _public member_ `TArray<TWeakObjectPtr<UUAFRigVMAssetEntry>> WeakEntries;` — `UPROPERTY()` — Currently selected entries

#### class `UE::UAF::Editor::UFunctionsOutlinerItemMenuContext`  
`class UFunctionsOutlinerItemMenuContext : public UObject`  
_L33-36_
- reflection: `UCLASS()`
- inherits: `UObject`

#### class `UE::UAF::Editor::UCommonOutlinerItemMenuContext`  
`class UCommonOutlinerItemMenuContext : public UObject`  
_L39-51_
- reflection: `UCLASS()`
- inherits: `UObject`
- L46 _public member_ `TArray<TWeakObjectPtr<UUAFRigVMAssetEditorData>> WeakEditorDatas;` — `UPROPERTY()` — Currently selected asset's editor data
- L48 _public member_ `TWeakPtr<SCommonOutliner> WeakOutliner;`
- L49 _public member_ `TWeakPtr<Workspace::IWorkspaceEditor> WeakWorkspaceEditor;`
- L50 _public member_ `TWeakPtr<FUICommandList> WeakCommandList;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Workspace` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace UAF` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/Outliner/SCommonOutliner.h` (Private)


#### class `UE::UAF::Editor::SCommonOutliner`  
`class SCommonOutliner : public SSceneOutliner`  
_L26-56_
- inherits: `SSceneOutliner`
- L31 _public function_ `SLATE_BEGIN_ARGS(SCommonOutliner)`
- L32 _public prototype_ `SLATE_EVENT(FAssetEditorDataDelegate, BindAssetDelegate) SLATE_EVENT(FAssetEditorDataDelegate, UnbindAssetDelegate) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FSceneOutlinerInitializationOptions& InitOptions);`
- L38 _public prototype_ `void SetExport(const FWorkspaceOutlinerItemExport& InExport);`
- L39 _public function_ `TConstArrayView<TSoftObjectPtr<UUAFRigVMAsset>> GetAssetsView() const`
- L40 _public prototype_ `void UpdateAssets();`
- L41 _public prototype_ `bool HasAssets() const;`
- L44 _protected prototype_ `void SetAssets(TConstArrayView<TSoftObjectPtr<UUAFRigVMAsset>> InAssets);`
- L45 _protected prototype_ `void HandleAssetLoaded(const FSoftObjectPath& InSoftObjectPath, UUAFRigVMAsset* InAsset);`
- L46 _protected prototype_ `void SetHighlightedItem(FSceneOutlinerTreeItemPtr Item) const;`
- L47 _protected prototype_ `void ClearHighlightedItem(FSceneOutlinerTreeItemPtr Item) const;`
- L48 _protected prototype_ `void RegisterAssetDelegates(const UUAFRigVMAsset* InAsset);`
- L49 _protected prototype_ `void UnregisterAssetDelegates(const UUAFRigVMAsset* InAsset);`
- L51 _private member_ `TArray<TSoftObjectPtr<UUAFRigVMAsset>> Assets;`
- L52 _private member_ `FWorkspaceOutlinerItemExport Export;`
- L54 _private member_ `FAssetEditorDataDelegate BindAssetDelegate;`
- L55 _private member_ `FAssetEditorDataDelegate UnbindAssetDelegate;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Workspace` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace UAF` (scope `UE`)
- L21 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FAssetEditorDataDelegate, UUAFRigVMAssetEditorData*) class SCommonOutliner : public SSceneOutliner { friend class FCommonOutlinerMode; public: SLATE_BEGIN_ARGS(SCommonOutliner) {} SLATE_EVENT(FAssetEditorDataDelegate, BindAssetDelegate) SLATE_EVENT(FAssetEditorDataDelegate, UnbindAssetDelegate) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FSceneOutlinerInitializationOptions& InitOptions); void SetExport(const FWorkspaceOutlinerItemExport& InExport); TConstArrayView<TSoftObjectPtr<UUAFRigVMAsset>> GetAssetsView() const { return Assets; } void UpdateAssets(); bool HasAssets() const; protected: void SetAssets(TConstArrayView<TSoftObjectPtr<UUAFRigVMAsset>> InAssets); void HandleAssetLoaded(const FSoftObjectPath& InSoftObjectPath, UUAFRigVMAsset* InAsset); void SetHighlightedItem(FSceneOutlinerTreeItemPtr Item) const; void ClearHighlightedItem(FSceneOutlinerTreeItemPtr Item) const; void RegisterAssetDelegates(const UUAFRigVMAsset* InAsset); void UnregisterAssetDelegates(const UUAFRigVMAsset* InAsset); private: TArray<TSoftObjectPtr<UUAFRigVMAsset>> Assets; FWorkspaceOutlinerItemExport Export; FAssetEditorDataDelegate BindAssetDelegate; FAssetEditorDataDelegate UnbindAssetDelegate; };`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/RigVMAssetViewMenuContext.h` (Private)


#### class `URigVMAssetViewMenuContext`  
`class URigVMAssetViewMenuContext : public UObject`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UObject`
- L20 _private member_ `TWeakPtr<UE::UAF::Editor::SRigVMAssetView> RigVMAssetView;` — The RigVM asset view that we are editing

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/SUAFBrowser.h` (Private)


#### class `UE::UAF::Editor::SUAFBrowser`  
`class SUAFBrowser : public SCompoundWidget`  
_L40-203_
- inherits: `SCompoundWidget`
- desc: Experimental. Widget for searching for UAF related assets Note: The implementation of this widget may change in the future as we move to use an in-progress capability of the content browser to preview assets.
- L45 _public function_ `SLATE_BEGIN_ARGS(SUAFBrowser)`
- L54 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<UE::Workspace::IWorkspaceEditor>& InHostingApp, ETabState::Type InTabState);`
- L59 _private prototype_ `TSharedRef<SWidget> Construct_GetMainBrowserContents();` — Builds the top level of the UAF Browser, including preview splitter. Contents need to be ordered dynamically based on orientation.
- L62 _private prototype_ `TSharedRef<SWidget> Construct_GetTaggedAssetBrowser();` — Builds the tagged asset browser part of the UAF browser. IE: Asset picker
- L65 _private prototype_ `TSharedRef<SWidget> Construct_GetAssetPreviewWidget();` — Builds the tagged asset preview part of the UAF browser. Ex: Viewport. In the future this may get replaced by a native content browser API.
- L68 _private prototype_ `TSharedRef<SWidget> Construct_GetAssetPreviewNotSupportedWidget();` — Builds fallack when preview not supported by type in UAF browser Preview.
- L73 _private member_ `static FName AddNewMenuName;` — Used for UToolMenu registration of add menu.
- L87 _private prototype_ `void OnOverrideAssetPickerConfig(FAssetPickerConfig& Config);` — Callback to override asset picker configs for our tagged asset browser
- L90 _private prototype_ `void PopulatePluginFilters(FAssetPickerConfig& Config);` — Populates Config.ExtraFrontendFilters with plugin-based filters discovered from project settings and IPluginManager.
- L93 _private prototype_ `void OnContentSearchTextChanged(const FText& SearchText);` — Called when the content area search box text changes; updates the suggestion strip.
- L96 _private prototype_ `void OnFilterSuggestionSelected();` — Called when any suggestion chip is clicked; returns keyboard focus to the search box.
- L99 _private prototype_ `void OnExtendAssetPickerTopBar(TSharedRef<SHorizontalBox> InAssetPickerTopBar);` — Callback to customize top bar of our asset browser. To add layout control buttons.
- L102 _private prototype_ `TSharedRef<SWidget> OnExtendAssetPickerTopBar_GetDrawerDockButton();` — Builds button for docking the UAF Browser. This just unhides the in-layout browser tab.
- L105 _private prototype_ `TSharedRef<SWidget> OnExtendAssetPickerTopBar_GetToggleSwapHotkeyButton();` — Builds button for swapping hotkey behavior (sidebar to statusbar).
- L108 _private prototype_ `FReply OnSwapHotkeyButtonClicked();` — Callback for when swap hotkey is pressed. Changes hotkey behavior in project settings & hides all drawers.
- L111 _private prototype_ `FReply OnDockDrawerButtonClicked();` — Callback for when dock to drawer button is pressed. Hides all drawers and invokes docked browser tab.
- L114 _private prototype_ `void OnActiveSectionChanged(const UTaggedAssetBrowserSection* NewSection);` — Callback for when the active tagged asset browser section changes. Rebuilds add/import buttons.
- L117 _private prototype_ `void OnPrimaryFilterSelectionChanged();` — Callback for when the primary filter tree selection changes. Rebuilds add/import buttons.
- L120 _private prototype_ `TSharedRef<SWidget> BuildAddImportButtons();` — Builds the add/import button(s) appropriate for the current active section.
- L123 _private prototype_ `TSharedRef<SWidget> BuildAddMenu();` — Generates the add menu widget for the per-instance ToolMenu.
- L126 _private prototype_ `void CreateAssetWithNameDialog(UClass* InFactoryClass, const FText& AssetTypeName);` — Shows a modal dialog to name the new asset, then creates it if confirmed.
- L129 _private prototype_ `void CreateAssetWithNameDialog(UFactory* InFactory, const FText& AssetTypeName);` — Overload that accepts a pre-configured factory (e.g. UBlueprintFactory with ParentClass already set).
- L132 _private prototype_ `FReply OnImportButtonClicked();` — Opens the OS import dialog targeting the current asset folder.
- L135 _private prototype_ `FString GetNewAssetPath() const;` — Returns the package folder path to use for asset creation/import.
- L138 _private prototype_ `TArray<UClass*> GetCurrentSectionFilterClasses() const;` — Collects UClass pointers from the currently selected primary filter items in the tagged asset browser.
- L141 _private prototype_ `EUAFAddButtonMode GetAddButtonMode(const TArray<UClass*>& SectionClasses) const;` — Determines which button(s) to show based on which section classes have creatable factories.
- L146 _private prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Intercepts Tab from the search box to redirect focus to the first suggestion chip.
- L149 _private prototype_ `void OnAssetSelected(const FAssetData& InAssetData);` — Callback for when an asset is selected.
- L152 _private prototype_ `void OnAssetsDragged(const TArray<FAssetData>& InAssetData);` — Callback for when assets are dragged
- L155 _private prototype_ `void OnExternalColumnVisibilityChanged(const TArray<FString>& HiddenColumnIds);` — Callback to sync settings changes across UAF Browser instances
- L158 _private prototype_ `void OnBrowserColumnVisibilityChanged(const TArray<FString>& HiddenColumnIds);` — Callback to write column visibility changes to .ini & UAF settings
- L163 _private member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WeakHostingApp = nullptr;` — App Hosting this Browser, to query settings against
- L166 _private member_ `TWeakObjectPtr<const UTaggedAssetBrowserSection> CurrentActiveSection;` — The currently active section, updated via OnActiveSectionChanged.
- L169 _private member_ `TSharedPtr<SHorizontalBox> AddImportButtonContainer;` — Container for the add/import button(s). Rebuilt reactively on section change.
- L172 _private member_ `ETabState::Type TabState = ETabState::ClosedTab;` — Current Tab host type, so we can resturucture layout based on how this tab is being hosted (Sidebar / statusbar / etc).
- L178 _private member_ `SVerticalBox::FSlot* AssetPreviewSlot = nullptr;` — Experimental. Slot used to swap between different asset preview widgets. Note: Long term this functionality will get replaced by the generic IAssetPreviewCustomization API.
- L184 _private member_ `TWeakPtr<IUAFAssetPreview> AssetPreviewWidgetWeak = nullptr;` — Experimental. Widget used to preview an asset. Persisted weakly here so that we can tell it to just update if swapping betweeen assets of the same type
- L187 _private member_ `FSaveAssetViewSettingsDelegate SaveAssetViewSettingsDelegate;` — Delegate write asset browser config .ini  whenever changes occur.
- L190 _private member_ `FLoadAssetViewSettingsDelegate LoadAssetViewSettingsDelegate;` — Delegate fired to refresh asset browser whenever config .ini changes occur.
- L193 _private member_ `TArray<TSharedRef<FFrontendFilter_UAFPlugin>> PluginFilters;` — Plugin frontend filters added to the content area filter bar. Kept so we can match them against search text.
- L196 _private member_ `TSharedPtr<STaggedAssetBrowser> TaggedAssetBrowser;` — The tagged asset browser widget; held so we can access the asset picker and filter list directly.
- L199 _private member_ `TSharedPtr<SUAFBrowserFilterSuggestionStrip> SuggestionStrip;` — Horizontally-scrolling strip of filter suggestion chips, shown when search text matches a known filter.
- L202 _private member_ `TWeakPtr<SWidget> WeakSearchBox;` — Weak reference to the content area search box widget, captured when OnContentSearchTextChanged fires. Used to restore focus after a chip click.

#### enum `UE::UAF::Editor::SUAFBrowser::EUAFAddButtonMode`  
`enum class EUAFAddButtonMode`  
_L76-82_
- desc: How AddButton should appear based on filter(s) active.
- L78 _public enumerator_ `AddOnly`
- L79 _public enumerator_ `ImportOnly`
- L80 _public enumerator_ `Both`
- L81 _public enumerator_ `Default`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace UAF` (scope `UE`)
- L31 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/SUAFBrowserFilterSuggestionStrip.h` (Private)


#### struct `FFilterSuggestion`  
`struct FFilterSuggestion`  
_L18-32_
- desc: Display-and-activation descriptor for a single suggestion chip in the UAF Browser filter suggestion strip. Decouples display (name, icon, color) from activation logic so the strip doesn't need to know the filter type.
- L20 _public member_ `FText DisplayName;`
- L21 _public member_ `FName IconName;`
- L22 _public member_ `FLinearColor Color = FLinearColor::White;`
- L28 _public member_ `FName Category = FName(TEXT("Misc` — Row grouping key. Use one of the built-in SUAFBrowserFilterSuggestionStrip::Category* constants or any FName to create a custom row. The FName string is used as the row label.
- L31 _public member_ `TDelegate<void()> OnActivate;` — Executed when the chip is clicked (or activated via keyboard) to apply the associated filter.

#### class `SUAFBrowserFilterSuggestionStrip`  
`class SUAFBrowserFilterSuggestionStrip : public SCompoundWidget`  
_L47-100_
- inherits: `SCompoundWidget`
- desc: A horizontally-scrolling, categorized strip of filter suggestion chips. Appears at the bottom of the UAF Browser when the user types text that matches available filters. Suggestions are grouped into named rows determined by FFilterSuggestion::Category. Each row is only visible when it has at least one matching suggestion. Keyboard navigation: - Tab (from search box): moves focus to the first chip (intercepted by parent SUAFBrowser) - Left / Right: move focus within the current row - Up / Down: move focus to the corresponding chip in the adjacent row (wraps, no-op if single row) - Enter / Space: activate the focused chip (handled natively by SButton)
- L51 _public member_ `static const FName CategoryPlugins;` — Built-in category key constants. The FName string doubles as the row label.
- L52 _public member_ `static const FName CategoryTypes;`
- L53 _public member_ `static const FName CategoryMisc;`
- L55 _public function_ `SLATE_BEGIN_ARGS(SUAFBrowserFilterSuggestionStrip)`
- L57 _public prototype_ `SLATE_EVENT(TDelegate<void()>, OnFilterSuggestionSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Called after any chip's OnActivate fires. Use to restore search box focus and clear search text.
- L63 _public prototype_ `void SetSuggestions(const TArray<TSharedRef<FFilterSuggestion>>& Suggestions);` — Updates the displayed suggestion chips, grouped into rows by Category FName. Collapses the strip when Suggestions is empty.
- L66 _public prototype_ `bool HasAnySuggestions() const;` — Returns true if any category row has at least one chip.
- L69 _public prototype_ `void FocusFirstChip();` — Moves keyboard focus to the first chip in the first non-empty row.
- L71 _public prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L81 _private prototype_ `TSharedRef<SWidget> BuildChipWidget(TSharedRef<FFilterSuggestion> Suggestion);`
- L82 _private prototype_ `FReply OnChipClicked(TSharedRef<FFilterSuggestion> Suggestion);`
- L88 _private member_ `static const TArray<FName> DefaultCategoryOrder;` — Defines the preferred display order for known category keys. Any unknown keys encountered in SetSuggestions() are appended in the order they first appear.
- L91 _private member_ `TArray<FFilterSuggestionRow> ActiveRows;` — Live rows, rebuilt on every SetSuggestions() call. Only contains categories with at least one suggestion.
- L94 _private member_ `TSharedPtr<SVerticalBox> RowsContainer;` — Vertical container into which row widgets are added dynamically in SetSuggestions().
- L97 _private member_ `TSharedPtr<STextBlock> HintTextWidget;` — Hint text above the rows; toggled between invite and navigation hints depending on focus state.
- L99 _private member_ `TDelegate<void()> OnFilterSuggestionSelectedDelegate;`

#### struct `SUAFBrowserFilterSuggestionStrip::FFilterSuggestionRow`  
`struct FFilterSuggestionRow`  
_L75-79_
- desc: Internal per-row data, rebuilt on every SetSuggestions() call.
- L77 _public member_ `FName CategoryKey;`
- L78 _public member_ `TArray<TSharedRef<SWidget>> ChipWidgets;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/TaggedAssetBrowser_UAFBrowserFilters.h` (Private)


#### class `UTaggedAssetBrowserFilter_NativeClass`  
`class UTaggedAssetBrowserFilter_NativeClass : public UTaggedAssetBrowserFilter_Class`  
_L18-29_
- reflection: `UCLASS(DisplayName="Native Classes")`
- inherits: `UTaggedAssetBrowserFilter_Class`
- desc: Experimental. Temp filter to allow us to find BP whose BPGC would match a class filter. Our solution here isn't as robust as we would like. But it does work for UAF Browser MVP needs.
- L24 _public prototype_ `virtual void ModifyARFilterInternal(FARFilter& Filter) const override;`
- L28 _public member_ `bool bSearchNativeParentClasses = false;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — True to search for a native parent class, useful for finding BPs whose BPGCs would match but BP itself does not match.

#### class `UTaggedAssetBrowserFilter_Skeleton`  
`class UTaggedAssetBrowserFilter_Skeleton : public UTaggedAssetBrowserFilterBase`  
_L34-54_
- reflection: `UCLASS(DisplayName="Skeleton")`
- inherits: `UTaggedAssetBrowserFilterBase`
- desc: Filter for a specifc skeleton
- L40 _public prototype_ `virtual FString ToString() const override;`
- L41 _public function_ `virtual TOptional<FString> GetInstanceIdentifier() const override`
- L42 _public prototype_ `virtual FText GetTooltip() const override;`
- L43 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L45 _public prototype_ `virtual void ModifyARFilterInternal(FARFilter& Filter) const override;`
- L49 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Skeleton to search for.
- L53 _public member_ `FName FilterName;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — Name for this class filter, by default will use name of the skeleton

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFEDITOR_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/UAFBrowserFrontendFilters.h` (Private)


#### class `FFrontendFilter_UAFPlugin`  
`class FFrontendFilter_UAFPlugin : public FFrontendFilter`  
_L11-51_
- inherits: `FFrontendFilter`
- desc: A content browser frontend filter that restricts the asset view to content from a specific Unreal Engine plugin. These filters appear under the "Plugins" category in the UAF Browser's "Add Filter" dropdown.
- L14 _public function_ `FFrontendFilter_UAFPlugin(TSharedPtr<FFrontendFilterCategory> InCategory, const FString& InPluginName, const FString& InFriendlyName, const FString& InPluginContentPath) : FFrontendFilter(MoveTemp(InCategory)) , PluginName(InPluginName) , FriendlyName(InFriendlyName) , PluginContentPath(InPluginContentPath)`
- L25 _public function_ `virtual FString GetName() const override` — FFilterBase interface
- L26 _public function_ `virtual FText GetDisplayName() const override`
- L27 _public function_ `virtual FText GetToolTipText() const override`
- L34 _public function_ `virtual FLinearColor GetColor() const override`
- L35 _public function_ `virtual FName GetIconName() const override`
- L38 _public function_ `virtual bool PassesFilter(FAssetFilterType InItem) const override` — FFrontendFilter interface
- L44 _public function_ `const FString& GetPluginName() const` — Returns the plugin name (without the friendly display name). Used for matching against search text.
- L47 _private member_ `FString PluginName;`
- L48 _private member_ `FString FriendlyName;`
- L50 _private member_ `FString PluginContentPath;` — Package path prefix for this plugin's content, e.g. "/Cosmo/".

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/UAFBrowserMenuContext.h` (Private)


#### class `UUAFBrowserMenuContext`  
`class UUAFBrowserMenuContext : public UObject`  
_L11-18_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Context object passed to per-instance UAF Browser add-new ToolMenu sections.
- L17 _public member_ `TWeakPtr<UE::UAF::Editor::SUAFBrowser> WeakOwningBrowser;` — Browser that owns this context object.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Common/UAFBrowserTabSummoner.h` (Private)


#### struct `UE::UAF::Editor::FUAFBrowserTabSummoner`  
`struct FUAFBrowserTabSummoner : public FWorkflowTabFactory`  
_L23-56_
- inherits: `FWorkflowTabFactory`
- L28 _public member_ `static const FName DockedTabID;` — Docked Tab ID. We have 3 distinct, non synchronized tabs. The UAF editor will manage hotkey / layouts for the user.
- L31 _public member_ `static const FName SidebarTabID;` — Sidebar Tab ID. We have 3 distinct, non synchronized tabs. The UAF editor will manage hotkey / layouts for the user.
- L34 _public member_ `static const FName DrawerTabID;` — Drawer Tab ID. We have 3 distinct, non synchronized tabs. The UAF editor will manage hotkey / layouts for the user.
- L37 _public member_ `static const FName StatusBarSystemDrawerID;` — ID for this tab within the status bar system. Used to communicate with status bar system.
- L39 _public prototype_ `static void ToggleDrawer();`
- L43 _public prototype_ `FUAFBrowserTabSummoner(TSharedPtr<UE::Workspace::IWorkspaceEditor> InHostingApp, ETabState::Type InTabState, FName InTabName, FText InTabLabel);`
- L46 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L47 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L52 _private member_ `TSharedPtr<SUAFBrowser> UAFBrowserWidget;` — The widget this tab spawner wraps
- L55 _private member_ `ETabState::Type TabState = ETabState::ClosedTab;` — Current state of the tab, needed for the tab to change layout

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Workspace` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/EditorCVars.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L7 _namespace_ `namespace CVars` (scope `UE::UAF::Editor`)
- L10 _externvar_ `extern TAutoConsoleVariable<bool> GUseWorkspaceEditor;` (scope `UE::UAF::Editor::CVars`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Functions/Outliner/FunctionOutlinerEntry.h` (Private)


#### struct `UE::UAF::Editor::FFunctionsOutlinerEntryItem`  
`struct FFunctionsOutlinerEntryItem : FOutlinerEntryItem`  
_L14-55_
- inherits: `FOutlinerEntryItem`
- L16 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L25 _public prototype_ `FFunctionsOutlinerEntryItem() = delete;`
- L26 _public prototype_ `FFunctionsOutlinerEntryItem(const FItemData& ItemData);`
- L29 _public prototype_ `virtual bool IsValid() const override;`
- L30 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L31 _public prototype_ `virtual FString GetDisplayString() const override;`
- L32 _public function_ `virtual bool CanInteract() const override`
- L33 _public prototype_ `virtual FString GetPackageName() const override;`
- L37 _public prototype_ `virtual void Rename(const FText& InNewName) const override;` — Renames the item to the specified name
- L40 _public prototype_ `virtual bool ValidateName(const FText& InNewName, FText& OutErrorMessage) const override;` — Validates the new item name
- L42 _public prototype_ `virtual FStringView GetCategoryPath() const override;`
- L44 _public prototype_ `virtual void SetAccessSpecifier(const EAnimNextExportAccessSpecifier& InSpecifier) const override;`
- L45 _public prototype_ `virtual EAnimNextExportAccessSpecifier GetAccessSpecifier() const override;`
- L46 _public prototype_ `virtual bool CanSetAccessSpecifier() const override;`
- L47 _public prototype_ `virtual bool IsReadOnly() const override;`
- L48 _public prototype_ `virtual void GetItemIconAndColor(const FSlateBrush*& OutBrush, FSlateColor& OutColor) const override;`
- L51 _public member_ `TWeakObjectPtr<URigVMLibraryNode> WeakLibraryNode;` — Ptr to the underlying RigVM library node representing this function within the RigVMAsset
- L54 _public member_ `TWeakObjectPtr<const UUAFSharedVariablesEntry> WeakSharedVariablesEntry;` — The data interface entry this entry is from, if any

#### struct `UE::UAF::Editor::FFunctionsOutlinerEntryItem::FItemData`  
`struct FItemData`  
_L18-23_
- L20 _public member_ `const TWeakObjectPtr<UUAFRigVMAsset>& Asset;`
- L21 _public member_ `const int32 SortValue;`
- L22 _public member_ `URigVMLibraryNode* LibraryNode;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Functions/Outliner/FunctionsOutlinerCategoryItem.h` (Private)


#### struct `UE::UAF::Editor::FFunctionsOutlinerCategoryItem`  
`struct FFunctionsOutlinerCategoryItem : FOutlinerCategoryItem`  
_L13-21_
- inherits: `FOutlinerCategoryItem`
- L15 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L17 _public prototype_ `FFunctionsOutlinerCategoryItem(const FOutlinerCategoryItem::FItemData& InItemData);`
- L19 _public prototype_ `virtual void Rename(const FText& InNewName) const override final;`
- L20 _public prototype_ `virtual bool ValidateName(const FText& InNewName, FText& OutErrorMessage) const override final;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Functions/Outliner/FunctionsOutlinerCollapsedGraphItem.h` (Private)


#### struct `UE::UAF::Editor::FFunctionsOutlinerCollapsedGraphItem`  
`struct FFunctionsOutlinerCollapsedGraphItem : FOutlinerEntryItem`  
_L12-46_
- inherits: `FOutlinerEntryItem`
- L14 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L24 _public prototype_ `FFunctionsOutlinerCollapsedGraphItem() = delete;`
- L25 _public prototype_ `FFunctionsOutlinerCollapsedGraphItem(const FItemData& ItemData);`
- L28 _public prototype_ `virtual bool IsValid() const override;`
- L29 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L30 _public prototype_ `virtual FString GetDisplayString() const override;`
- L31 _public function_ `virtual bool CanInteract() const override`
- L32 _public prototype_ `virtual FString GetPackageName() const override;`
- L35 _public prototype_ `virtual bool IsReadOnly() const override;`
- L36 _public function_ `virtual void SetAccessSpecifier(const EAnimNextExportAccessSpecifier& InSpecifier) const override`
- L37 _public prototype_ `virtual EAnimNextExportAccessSpecifier GetAccessSpecifier() const override;`
- L38 _public prototype_ `virtual bool CanSetAccessSpecifier() const override;`
- L39 _public prototype_ `virtual FStringView GetCategoryPath() const override;`
- L40 _public prototype_ `virtual void GetItemIconAndColor(const FSlateBrush*& OutBrush, FSlateColor& OutColor) const override;`
- L41 _public prototype_ `virtual void Rename(const FText& InNewName) const override;`
- L42 _public prototype_ `virtual bool ValidateName(const FText& InNewName, FText& OutErrorMessage) const override;`
- L44 _public member_ `TWeakObjectPtr<URigVMCollapseNode> WeakCollapseNode;`
- L45 _public member_ `TWeakObjectPtr<URigVMLibraryNode> WeakOwningNode;`

#### struct `UE::UAF::Editor::FFunctionsOutlinerCollapsedGraphItem::FItemData`  
`struct FItemData`  
_L16-22_
- L18 _public member_ `const TWeakObjectPtr<UUAFRigVMAsset>& Asset;`
- L19 _public member_ `const int32 SortValue;`
- L20 _public member_ `URigVMCollapseNode* CollapseNode;`
- L21 _public member_ `URigVMLibraryNode* OwningNode;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Functions/Outliner/FunctionsOutlinerColumns.h` (Private)


#### class `UE::UAF::Editor::FFunctionsOutlinerOutputColumn`  
`class FFunctionsOutlinerOutputColumn : public ISceneOutlinerColumn`  
_L10-25_
- inherits: `ISceneOutlinerColumn`
- L13 _public prototype_ `static FName GetID();`
- L15 _public prototype_ `FFunctionsOutlinerOutputColumn(ISceneOutliner& SceneOutliner);`
- L18 _public function_ `virtual FName GetColumnID() override` — ISceneOutlinerColumn interface
- L19 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L20 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L21 _public function_ `virtual bool SupportsSorting() const override`
- L24 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Functions/Outliner/FunctionsOutlinerHierarchy.h` (Private)


#### class `UE::UAF::Editor::FFunctionsOutlinerHierarchy`  
`class FFunctionsOutlinerHierarchy : public FOutlinerHierarchy`  
_L11-20_
- inherits: `FOutlinerHierarchy`
- L14 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;`
- L16 _public prototype_ `FFunctionsOutlinerHierarchy(ISceneOutlinerMode* Mode);`
- L17 _public prototype_ `virtual void CreateItemsForAsset(const UUAFRigVMAssetEditorData* EditorData, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`
- L19 _private prototype_ `void RecurseCollapseNodeGraphs(const UUAFRigVMAssetEditorData* EditorData, TArray<FSceneOutlinerTreeItemPtr>& OutItems, URigVMLibraryNode* LibraryNode) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Functions/Outliner/FunctionsOutlinerMode.h` (Private)


#### class `UE::UAF::Editor::FFunctionsOutlinerMode`  
`class FFunctionsOutlinerMode : public FCommonOutlinerMode`  
_L12-52_
- inherits: `FCommonOutlinerMode`
- L15 _public prototype_ `FFunctionsOutlinerMode(SCommonOutliner* InFunctionsOutliner, const TSharedRef<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditor);`
- L18 _public prototype_ `virtual bool CanRename() const override;`
- L19 _public prototype_ `virtual bool CanDelete() const override;`
- L20 _public prototype_ `virtual bool CanCopy() const override;`
- L21 _public prototype_ `virtual bool CanCut() const override;`
- L22 _public prototype_ `virtual bool CanPaste() const override;`
- L23 _public prototype_ `virtual bool CanDuplicate() const override;`
- L24 _public prototype_ `virtual void Rename() const override;`
- L25 _public prototype_ `virtual void Delete() const override;`
- L26 _public prototype_ `virtual void Copy() const override;`
- L27 _public prototype_ `virtual void Cut() const override;`
- L28 _public prototype_ `virtual void Paste() const override;`
- L29 _public prototype_ `virtual void Duplicate() const override;`
- L30 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& InOutContext) const override;`
- L31 _public prototype_ `virtual void HandleItemSelection(const FSceneOutlinerItemSelection& Selection) const override;`
- L32 _public prototype_ `virtual void RegisterToolMenus() override;`
- L36 _public prototype_ `virtual void Rebuild() override;`
- L37 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L38 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L39 _public prototype_ `virtual bool UpdateOperationDecorator(const FDragDropEvent& Event, const FSceneOutlinerDragValidationInfo* ValidationInfo) const override;`
- L40 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& OutCommandList) override;`
- L42 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L45 _protected prototype_ `static void PopulateNewFunctionToolMenuEntries(UToolMenu* InMenu, bool bAddSeparator);`
- L48 _private prototype_ `bool OpenFunctionItem(const FSceneOutlinerTreeItemPtr Item, FDocumentTracker::EOpenDocumentCause OpenDocumentCause = FDocumentTracker::NavigatingCurrentDocument) const;`
- L49 _private prototype_ `void OpenSelectedFunctionsInNewTab() const;`
- L50 _private prototype_ `bool CanOpenSelectedFunctionsInNewTab() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Functions/Outliner/FunctionsOutlinerView.h` (Private)


#### class `UE::UAF::Editor::SFunctionsView`  
`class SFunctionsView : public SCompoundWidget`  
_L29-44_
- inherits: `SCompoundWidget`
- L31 _private function_ `SLATE_BEGIN_ARGS(SFunctionsView)`
- L32 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<UE::Workspace::IWorkspaceEditor> InWorkspaceEditor);`
- L35 _private prototype_ `void SetExportDirectly(const FWorkspaceOutlinerItemExport& InExport) const;`
- L37 _private prototype_ `void HandleFocusedDocumentChanged(const UE::Workspace::FWorkspaceDocument& InDocument) const;`
- L39 _private prototype_ `void OnEditorDataModified(UUAFRigVMAssetEditorData* InEditorData, EAnimNextEditorDataNotifType InType, UObject* InSubject) const;`
- L40 _private prototype_ `void OnRigVMModified(ERigVMGraphNotifType NotifType, URigVMGraph* Graph, UObject* Subject) const;`
- L43 _private member_ `TSharedPtr<SCommonOutliner> FunctionsOutliner;`

#### struct `UE::UAF::Editor::FAnimNextFunctionsTabSummoner`  
`struct FAnimNextFunctionsTabSummoner : public FWorkflowTabFactory`  
_L46-58_
- inherits: `FWorkflowTabFactory`
- L49 _public prototype_ `FAnimNextFunctionsTabSummoner(TSharedPtr<UE::Workspace::IWorkspaceEditor> InHostingApp);`
- L53 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L54 _private prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L57 _private member_ `TSharedPtr<SFunctionsView> FunctionsView;` — The widget this tab spawner wraps

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Workspace` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L27 _externvar_ `extern const FLazyName FunctionsTabName;` (scope `UE::UAF::Editor`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Graph/AnimNextEdGraphCustomization.h` (Private)


#### class `UE::UAF::Editor::FAnimNextEdGraphCustomization`  
`class FAnimNextEdGraphCustomization : public IDetailCustomization`  
_L26-37_
- inherits: `IDetailCustomization`
- L28 _private prototype_ `FAnimNextEdGraphCustomization() = default;`
- L31 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L36 _private member_ `TSharedPtr<FRigVMGraphDetailCustomizationImpl> RigVMGraphDetailCustomizationImpl;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Workspace` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Graph/AnimNextGraphPanelPinFactory.h` (Private)


#### class `FAnimNextGraphPanelPinFactoryEditor`  
`class FAnimNextGraphPanelPinFactoryEditor : public FGraphPanelPinFactory`  
_L10-15_
- inherits: `FGraphPanelPinFactory`
- L14 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;` — FGraphPanelPinFactory interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFEDITOR_API`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Graph/SGraphPinModuleEvent.h` (Private)


#### class `UE::UAF::Editor::SGraphPinModuleEvent`  
`class SGraphPinModuleEvent : public SGraphPin`  
_L10-20_
- inherits: `SGraphPin`
- L13 _public function_ `SLATE_BEGIN_ARGS(SGraphPinModuleEvent)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L19 _private prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Graph/SModuleEventPicker.h` (Private)


#### class `UE::UAF::Editor::SModuleEventPicker`  
`class SModuleEventPicker : public SCompoundWidget`  
_L10-37_
- inherits: `SCompoundWidget`
- L13 _public typedef_ `using FOnEventPicked = TDelegate<void(FName InEventName)>;`
- L14 _public typedef_ `using FOnGetSelectedEvent = TDelegate<FName()>;`
- L16 _public function_ `SLATE_BEGIN_ARGS(SModuleEventPicker)`
- L18 _public prototype_ `SLATE_ARGUMENT(TArray<UObject*>, ContextObjects) SLATE_EVENT(FOnEventPicked, OnEventPicked) SLATE_EVENT(FOnGetSelectedEvent, OnGetSelectedEvent) SLATE_ARGUMENT(FName, InitiallySelectedEvent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `void RefreshEntries();`
- L34 _private member_ `TArray<TSharedPtr<FName>> EventNamesSource;` — Names to be displayed in the combo box
- L36 _private member_ `TArray<TWeakObjectPtr<UObject>> ContextObjects;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Module/AnimNextModuleAssetDefinition.h` (Private)


#### class `UAssetDefinition_AnimNextModule`  
`class UAssetDefinition_AnimNextModule : public UAssetDefinitionDefault`  
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

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Module/ModuleEventPropertyCustomization.h` (Private)


#### class `UE::UAF::Editor::FModuleEventPropertyTypeIdentifier`  
`class FModuleEventPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L11-14_
- inherits: `IPropertyTypeIdentifier`
- L13 _private prototype_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override;`

#### class `UE::UAF::Editor::FModuleEventPropertyCustomization`  
`class FModuleEventPropertyCustomization : public IPropertyTypeCustomization`  
_L16-24_
- inherits: `IPropertyTypeCustomization`
- L20 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L21 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/PIEAssetCompilationHandler.h` (Private)


#### class `UE::UAF::Editor::FOutOfDateAssetCompilation`  
`class FOutOfDateAssetCompilation : public PIE::IOutOfDateAssetCompilation`  
_L10-14_
- inherits: `PIE::IOutOfDateAssetCompilation`
- L13 _private prototype_ `virtual bool HandleOutOfDateAssets_Internal(const FRequestPlaySessionParams& InPlaySessionParams, TArray<UObject*>& OutAssetsWithErrors) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Param/AnimNextActorLocatorEditor.h` (Private)


#### class `UE::UAF::Editor::FActorLocatorEditor`  
`class FActorLocatorEditor : public UE::UniversalObjectLocator::ILocatorFragmentEditor`  
_L11-24_
- inherits: `UE::UniversalObjectLocator::ILocatorFragmentEditor`
- L14 _private prototype_ `virtual UE::UniversalObjectLocator::ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;` — ILocatorFragmentEditor interface
- L15 _private prototype_ `virtual bool IsAllowedInContext(FName InContextName) const override;`
- L16 _private prototype_ `virtual bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L17 _private prototype_ `virtual UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L18 _private prototype_ `virtual TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L19 _private prototype_ `virtual FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L20 _private prototype_ `virtual FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L21 _private prototype_ `virtual FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L22 _private prototype_ `virtual UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L23 _private prototype_ `virtual FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Param/AnimNextComponentLocatorEditor.h` (Private)


#### class `UE::UAF::Editor::FComponentLocatorEditor`  
`class FComponentLocatorEditor : public UE::UniversalObjectLocator::ILocatorFragmentEditor`  
_L11-24_
- inherits: `UE::UniversalObjectLocator::ILocatorFragmentEditor`
- L14 _private prototype_ `virtual UE::UniversalObjectLocator::ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;` — ILocatorFragmentEditor interface
- L15 _private prototype_ `virtual bool IsAllowedInContext(FName InContextName) const override;`
- L16 _private prototype_ `virtual bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L17 _private prototype_ `virtual UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L18 _private prototype_ `virtual TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L19 _private prototype_ `virtual FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L20 _private prototype_ `virtual FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L21 _private prototype_ `virtual FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L22 _private prototype_ `virtual UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L23 _private prototype_ `virtual FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Param/AnimNextLocatorContext.h` (Private)


#### class `UE::UAF::Editor::FLocatorContext`  
`class FLocatorContext : public UE::UniversalObjectLocator::ILocatorFragmentEditorContext`  
_L13-27_
- inherits: `UE::UniversalObjectLocator::ILocatorFragmentEditorContext`
- L16 _private function_ `virtual UObject* GetContext(const IPropertyHandle& InPropertyHandle) const override` — ILocatorFragmentEditorContext interface
- L22 _private function_ `virtual bool IsFragmentAllowed(FName InFragmentName) const override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Param/ObjectCastLocatorEditor.h` (Private)


#### class `UE::UAF::Editor::FObjectCastLocatorEditor`  
`class FObjectCastLocatorEditor : public UE::UniversalObjectLocator::ILocatorFragmentEditor`  
_L11-24_
- inherits: `UE::UniversalObjectLocator::ILocatorFragmentEditor`
- L14 _private prototype_ `virtual UE::UniversalObjectLocator::ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;` — ILocatorFragmentEditor interface
- L15 _private prototype_ `virtual bool IsAllowedInContext(FName InContextName) const override;`
- L16 _private prototype_ `virtual bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L17 _private prototype_ `virtual UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L18 _private prototype_ `virtual TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L19 _private prototype_ `virtual FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L20 _private prototype_ `virtual FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L21 _private prototype_ `virtual FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L22 _private prototype_ `virtual UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L23 _private prototype_ `virtual FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Param/ObjectFunctionLocatorEditor.h` (Private)


#### class `UE::UAF::Editor::FObjectFunctionLocatorEditor`  
`class FObjectFunctionLocatorEditor : public UE::UniversalObjectLocator::ILocatorFragmentEditor`  
_L11-24_
- inherits: `UE::UniversalObjectLocator::ILocatorFragmentEditor`
- L14 _private prototype_ `virtual UE::UniversalObjectLocator::ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;` — ILocatorFragmentEditor interface
- L15 _private prototype_ `virtual bool IsAllowedInContext(FName InContextName) const override;`
- L16 _private prototype_ `virtual bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L17 _private prototype_ `virtual UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L18 _private prototype_ `virtual TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L19 _private prototype_ `virtual FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L20 _private prototype_ `virtual FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L21 _private prototype_ `virtual FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L22 _private prototype_ `virtual UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L23 _private prototype_ `virtual FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Param/ObjectPropertyLocatorEditor.h` (Private)


#### class `UE::UAF::Editor::FObjectPropertyLocatorEditor`  
`class FObjectPropertyLocatorEditor : public UE::UniversalObjectLocator::ILocatorFragmentEditor`  
_L11-24_
- inherits: `UE::UniversalObjectLocator::ILocatorFragmentEditor`
- L14 _private prototype_ `virtual UE::UniversalObjectLocator::ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;` — ILocatorFragmentEditor interface
- L15 _private prototype_ `virtual bool IsAllowedInContext(FName InContextName) const override;`
- L16 _private prototype_ `virtual bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L17 _private prototype_ `virtual UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L18 _private prototype_ `virtual TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L19 _private prototype_ `virtual FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L20 _private prototype_ `virtual FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L21 _private prototype_ `virtual FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L22 _private prototype_ `virtual UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L23 _private prototype_ `virtual FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Param/ParamTypePropertyCustomization.h` (Private)


#### class `UE::UAF::Editor::FParamTypePropertyTypeCustomization`  
`class FParamTypePropertyTypeCustomization : public IPropertyTypeCustomization`  
_L11-17_
- inherits: `IPropertyTypeCustomization`
- L15 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L16 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/RewindDebugger/AnimNextAnalyzer.h` (Private)


#### class `FUAFAnalyzer`  
`class FUAFAnalyzer : public UE::Trace::IAnalyzer`  
_L13-33_
- inherits: `UE::Trace::IAnalyzer`
- L16 _public prototype_ `FUAFAnalyzer(TraceServices::IAnalysisSession& InSession, FUAFProvider& InProvider);`
- L18 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L19 _public function_ `virtual void OnAnalysisEnd() override`
- L20 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L31 _private member_ `TraceServices::IAnalysisSession& Session;`
- L32 _private member_ `FUAFProvider& Provider;`

#### enum `FUAFAnalyzer::(anonymous)`  
``  
_L24-29_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L25 _enumerator_ `RouteId_Module` (scope `FUAFAnalyzer::__anonc5eb91130103`)
- L26 _enumerator_ `RouteId_InstanceVariables` (scope `FUAFAnalyzer::__anonc5eb91130103`)
- L27 _enumerator_ `RouteId_InstanceVariablesStruct` (scope `FUAFAnalyzer::__anonc5eb91130103`)
- L28 _enumerator_ `RouteId_InstanceVariableDescriptions` (scope `FUAFAnalyzer::__anonc5eb91130103`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/RewindDebugger/AnimNextModuleTrack.h` (Private)


#### struct `FInstancedPropertyBagDetails`  
`struct FInstancedPropertyBagDetails`  
_L18-27_
- reflection: `USTRUCT()`
- L23 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = Details)`
- L26 _public member_ `FInstancedPropertyBag PropertyBag;` — `UPROPERTY(EditAnywhere, Category = Details, meta=(ShowOnlyInnerProperties))`

#### class `UPropertyBagDetailsObject`  
`class UPropertyBagDetailsObject : public UObject`  
_L30-40_
- reflection: `UCLASS()`
- inherits: `UObject`
- L36 _public member_ `TArray<FInstancedPropertyBagDetails> Properties;` — `UPROPERTY(EditAnywhere, Category=Details, meta=(TitleProperty = "Name"))`
- L39 _public member_ `TArray<FInstancedStruct> NativeProperties;` — `UPROPERTY(EditAnywhere, Category=Details)`

#### class `UE::UAF::Editor::FAnimNextModuleTrack`  
`class FAnimNextModuleTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L46-92_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- L49 _public prototype_ `FAnimNextModuleTrack(uint64 InstanceId);`
- L50 _public prototype_ `virtual ~FAnimNextModuleTrack();`
- L52 _public function_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetExistenceRange() const`
- L54 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L55 _private prototype_ `virtual bool UpdateInternal() override;`
- L57 _private function_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override`
- L62 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L67 _private function_ `virtual FName GetNameInternal() const override`
- L72 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L77 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L78 _private prototype_ `virtual bool HandleDoubleClickInternal() override;`
- L80 _private prototype_ `void Initialize();`
- L81 _private prototype_ `UPropertyBagDetailsObject* InitializeDetailsObject();`
- L83 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L84 _private member_ `FSlateIcon Icon;`
- L85 _private member_ `uint64 InstanceId;`
- L86 _private member_ `double PreviousScrubTime = -1.0;`
- L87 _private member_ `TWeakObjectPtr<UPropertyBagDetailsObject> DetailsObjectWeakPtr;`
- L88 _private member_ `TSharedPtr<SEventTimelineView::FTimelineEventData> ExistenceRange;`
- L89 _private member_ `mutable FText DisplayNameCache;`
- L91 _private member_ `TArray<FPropertyBagPropertyDesc> PropertyDescriptions;`

#### class `UE::UAF::Editor::FAnimNextModuleTrackCreator`  
`class FAnimNextModuleTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L95-113_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- L98 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L99 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L100 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L101 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L104 _private function_ `virtual FName GetNameInternal() const override`
- L109 _private function_ `virtual bool IsCreatingPrimaryChildTrackInternal() const override`

#### Free symbols / members of external scopes

- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace UAF` (scope `UE`)
- L43 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/RewindDebugger/AnimNextProvider.h` (Private)


#### struct `FPropertyDescriptionData`  
`struct FPropertyDescriptionData`  
_L22-28_
- L24 _public function_ `FPropertyDescriptionData(TConstArrayView<uint8> DataView, const FString& InName) : PropertyBagData(DataView), Name(InName)`
- L25 _public member_ `TArray<uint8> PropertyBagData;`
- L27 _public member_ `FString Name;`

#### enum `EPropertyVariableDataType`  
`enum class EPropertyVariableDataType`  
_L30-34_
- L32 _public enumerator_ `PropertyBag`
- L33 _public enumerator_ `InstancedStruct`

#### struct `FPropertyVariableData`  
`struct FPropertyVariableData`  
_L36-44_
- L38 _public function_ `FPropertyVariableData(EPropertyVariableDataType VariableDataType, uint32 DescriptionHash, TConstArrayView<uint8> Data) : ValueType (VariableDataType), DescriptionHash(DescriptionHash) , ValueData(Data)`
- L41 _public member_ `EPropertyVariableDataType ValueType;`
- L42 _public member_ `uint32 DescriptionHash;`
- L43 _public member_ `TArray<uint8> ValueData;`

#### struct `FDataInterfaceData`  
`struct FDataInterfaceData`  
_L46-66_
- L48 _public function_ `FDataInterfaceData(TraceServices::IAnalysisSession& Session) : VariablesTimeline(Session.GetLinearAllocator( )), InstanceId (0), HostInstanceId (0), OuterObjectId (0), AssetId (0), StartTime (-1), EndTime (-1)`
- L59 _public member_ `TraceServices::TPointTimeline<FPropertyVariableData> VariablesTimeline;`
- L60 _public member_ `uint64 InstanceId;`
- L61 _public member_ `uint64 HostInstanceId;`
- L62 _public member_ `uint64 OuterObjectId;`
- L63 _public member_ `uint64 AssetId;`
- L64 _public member_ `double StartTime;`
- L65 _public member_ `double EndTime;`

#### class `FUAFProvider`  
`class FUAFProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L68-126_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L71 _public member_ `static FName ProviderName;`
- L73 _public prototype_ `FUAFProvider(TraceServices::IAnalysisSession& InSession);`
- L76 _public function_ `virtual void BeginRead() const override`
- L81 _public function_ `virtual void EndRead() const override`
- L86 _public function_ `virtual void ReadAccessCheck() const override`
- L92 _public function_ `virtual void BeginEdit() const override`
- L97 _public function_ `virtual void EndEdit() const override`
- L102 _public function_ `virtual void EditAccessCheck() const override`
- L107 _public prototype_ `void AppendInstance(uint64 InstanceId, uint64 HostInstanceId, uint64 AssetId, uint64 OuterObjectId);`
- L108 _public prototype_ `void AppendVariables(double ProfileTime, double RecordingTime, uint64 InModuleInstanceId, EPropertyVariableDataType PropertyVariableDataType, uint32 PropertyDescriptionHash, const TArrayView<const uint8>& VariableData);`
- L109 _public prototype_ `void AppendVariableDescriptions(uint32 PropertyDescriptionHash, const TArrayView<const uint8>& VariableDescriptionData, const FString& Name);`
- L111 _public prototype_ `bool GetModuleId(uint64 ComponentId, uint64& OutModuleId) const;`
- L112 _public prototype_ `const FDataInterfaceData* GetDataInterfaceData(uint64 DataInterfaceId) const;`
- L113 _public function_ `const FPropertyDescriptionData* GetPropertyDescriptionData(uint32 PropertyDescriptionHash) const`
- L115 _public prototype_ `void EnumerateChildInstances(uint64 InstanceId, TFunctionRef<void(const FDataInterfaceData&)> Callback) const;`
- L116 _public prototype_ `void EnumerateDataInterfaces(const double StartTime, TFunctionRef<void(const TSharedRef<const FDataInterfaceData>)> Callback) const;`
- L119 _private member_ `TraceServices::IAnalysisSession& Session;`
- L120 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L122 _private member_ `TMap<uint64, uint64> ComponentIdToSystemId;`
- L123 _private member_ `TMap<uint64, TSharedRef<FDataInterfaceData>> DataInterfaceData;`
- L124 _private member_ `TMap<uint64, TArray<TSharedRef<FDataInterfaceData>>> HostToChildDataMap;`
- L125 _private member_ `TMap<uint32, FPropertyDescriptionData> HashToPropertyDescriptionDataMap;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace TraceServices`
- L19 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GUAFProviderLockState;` (scope `TraceServices`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/RewindDebugger/AnimNextTraceModule.h` (Private)


#### class `FUAFTraceModule`  
`class FUAFTraceModule : public TraceServices::IModule`  
_L13-25_
- inherits: `TraceServices::IModule`
- L17 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L18 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L19 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L20 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L21 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L24 _private member_ `static FName ModuleName;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/RewindDebugger/RewindDebuggerAnimNext.h` (Private)


#### class `FRewindDebuggerUAF`  
`class FRewindDebuggerUAF : public IRewindDebuggerExtension`  
_L13-20_
- inherits: `IRewindDebuggerExtension`
- L16 _public prototype_ `FRewindDebuggerUAF();`
- L17 _public function_ `virtual ~FRewindDebuggerUAF()`
- L19 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/RigVMCommands.h` (Private)


#### class `UE::UAF::FRigVMCommands`  
`class FRigVMCommands : public TCommands<FRigVMCommands>`  
_L11-20_
- inherits: `TCommands<FRigVMCommands>`
- desc: The commands for general AnimNext RVM graph editing
- L14 _public prototype_ `FRigVMCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> Compile;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> AutoCompile;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Settings/UAFEditorProjectSettings.h` (Private)


#### class `UUAFEditorProjectSettings`  
`class UUAFEditorProjectSettings : public UDeveloperSettings`  
_L12-30_
- reflection: `UCLASS(MinimalAPI, Config = Editor, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: UAF Editor Settings that are shared across a project.
- L16 _private prototype_ `UUAFEditorProjectSettings();`
- L21 _public member_ `FSoftObjectPath UAFBrowserCategoryConfiguration;` — `UPROPERTY(config, EditAnywhere, DisplayName = "UAF Browser Configuration", Category = UAF, meta = (AllowedClasses = "/Script/UserAssetTagsEditor.TaggedAssetBrowserConfiguration"))` — The configuration used the UAF browser for setting up categories
- L25 _public member_ `TArray<FName> AdditionalBrowserPluginFilters;` — `UPROPERTY(config, EditAnywhere, DisplayName = "Additional Browser Plugin Filters", Category = "UAF Browser Plugin Filters")` — Additional plugin names to include in the UAF Browser filter bar beyond the auto-discovered project plugins.
- L29 _public member_ `TArray<FName> ExcludedBrowserPluginFilters;` — `UPROPERTY(config, EditAnywhere, DisplayName = "Excluded Browser Plugin Filters", Category = "UAF Browser Plugin Filters")` — Plugin names to exclude from the auto-discovered project plugin list in the UAF Browser filter bar.

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Settings/UAFEditorUserSettings.h` (Private)


#### class `UUAFEditorUserSettings`  
`class UUAFEditorUserSettings : public UDeveloperSettings`  
_L12-39_
- reflection: `UCLASS(MinimalAPI, Config = EditorPerProjectUserSettings, meta = (DisplayName = "UAF Editor User Settings"))`
- inherits: `UDeveloperSettings`
- desc: UAF Editor Settings that are unique per user.
- L16 _private prototype_ `UUAFEditorUserSettings();`
- L22 _public member_ `bool bSummonUAFBrowserHotkeyOpensSidebar = true;` — `UPROPERTY(EditAnywhere, Category="UAF", Config)` — True if the UAF Browser hotkey opens the sidebar (Right), false will open status bar (Bottom)
- L26 _public member_ `bool bAutoOpenFunctionsInSeparateTabs = true;` — `UPROPERTY(EditAnywhere, Category="UAF", Config)` — If true, functions in UAF workspaces will open in a separate tab per default
- L30 _public member_ `bool bAutoCompileOutOfDateAssets = true;` — `UPROPERTY(EditAnywhere, Category="UAF", Config)` — If true, when user starts PIE any UAF assets requiring compilation will automatically be compiled
- L34 _public member_ `TArray<FString> UAFBrowserHiddenColumns;` — `UPROPERTY(EditAnywhere, Category="UAF|Browser", Config)` — Default columns to hide in the UAF Browser asset list. Applies to all browser instances (docked, sidebar, drawer).
- L37 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBrowserHiddenColumnsChanged, const TArray<FString>& );` — Broadcasts to synchronize column visibility across all browser instances.
- L38 _public member_ `FOnBrowserHiddenColumnsChanged OnBrowserHiddenColumnsChanged;`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBrowserHiddenColumnsChanged, const TArray<FString>& );` — Broadcasts to synchronize column visibility across all browser instances.

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/AbstractSkeletonAnimationEditorsExtender.h` (Private)


#### class `UAnimationEditorsAssetFamilyExtension_AbstractSkeleton`  
`class UAnimationEditorsAssetFamilyExtension_AbstractSkeleton : public UAnimationEditorsAssetFamilyExtension`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UAnimationEditorsAssetFamilyExtension`
- L16 _public prototype_ `virtual TObjectPtr<UClass> GetAssetClass() const override;` — UAnimationEditorsAssetFamilyExtension
- L17 _public prototype_ `virtual FText GetAssetTypeDisplayName() const override;`
- L18 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon() const override;`
- L19 _public prototype_ `virtual void FindAssetsOfType(TArray<FAssetData>& OutAssets, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L20 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L21 _public prototype_ `virtual void FindCounterpartAssets(const UObject* InAsset, IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) override;`
- L22 _public prototype_ `virtual void GetPosition(FName& OutBeforeClass, FName& OutAfterClass) const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/AbstractSkeletonEditor.h` (Private)


#### class `UE::UAF::Editor::FAbstractSkeletonEditor`  
`class FAbstractSkeletonEditor : public FWorkflowCentricApplication, public IAbstractSkeletonEditor`  
_L15-51_
- inherits: `FWorkflowCentricApplication,IAbstractSkeletonEditor`
- L18 _public prototype_ `void InitEditor(const TArray<UObject*>& InObjects, const TSharedPtr<IToolkitHost> InToolkitHost);`
- L21 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L22 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L23 _public prototype_ `virtual void CreateEditorModeManager() override;`
- L25 _public prototype_ `virtual FText GetToolkitName() const override;`
- L26 _public prototype_ `virtual const FSlateBrush* GetDefaultTabIcon() const override;`
- L27 _public prototype_ `virtual FLinearColor GetDefaultTabColor() const override;`
- L28 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L29 _public function_ `virtual FName GetToolkitFName() const override`
- L30 _public function_ `virtual FText GetBaseToolkitName() const override`
- L31 _public function_ `virtual FString GetWorldCentricTabPrefix() const override`
- L32 _public function_ `virtual FLinearColor GetWorldCentricTabColorScale() const override`
- L36 _public prototype_ `virtual TSharedPtr<IPersonaToolkit> GetPersonaToolkit() const override;`
- L40 _private prototype_ `void ExtendToolbar();`
- L42 _private member_ `TWeakObjectPtr<UAbstractSkeletonSetBinding> SetBinding;`
- L44 _private member_ `TWeakObjectPtr<UAbstractSkeletonLabelBinding> LabelBinding;`
- L46 _private member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit;`
- L48 _private member_ `TSharedPtr<SDockTab> SetsTab;`
- L50 _private member_ `TSharedPtr<SDockTab> LabelsTab;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/IAbstractSkeletonEditor.h` (Private)


#### class `UE::UAF::Editor::IAbstractSkeletonEditor`  
`class IAbstractSkeletonEditor`  
_L12-17_
- L15 _public prototype_ `virtual ~IAbstractSkeletonEditor() = default;`
- L16 _public prototype_ `virtual TSharedPtr<IPersonaToolkit> GetPersonaToolkit() const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/BoneDragDrop.h` (Private)


#### class `UE::UAF::Editor::FBoneDragDropOp`  
`class FBoneDragDropOp : public FDecoratedDragDropOp`  
_L15-100_
- inherits: `FDecoratedDragDropOp`
- L18 _public function_ `DRAG_DROP_OPERATOR_TYPE(FBoneDragDropOp, FDecoratedDragDropOp) static TSharedRef<FBoneDragDropOp> New(const TWeakObjectPtr<UAbstractSkeletonLabelBinding> InLabelBinding, const FName InBoneName)`
- L31 _public function_ `TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L92 _public function_ `void SetHoveredLabel(const FName InLabel)`
- L97 _public member_ `TWeakObjectPtr<UAbstractSkeletonLabelBinding> LabelBinding;`
- L98 _public member_ `FName BoneName;`
- L99 _public member_ `FName HoveredLabel;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "UE::UAF::Editor::FBoneDragDropOp"`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L45 _function_ `` (scope `UE::UAF::Editor::FBoneDragDropOp::GetDefaultDecorator`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/ILabelBinding.h` (Private)


#### class `UE::UAF::Editor::ILabelBindingWidget`  
`class ILabelBindingWidget`  
_L13-23_
- L16 _public prototype_ `virtual ~ILabelBindingWidget() = default;`
- L18 _public prototype_ `virtual void ScrollToLabel(const TObjectPtr<const UAbstractSkeletonLabelCollection> InLabelCollection, const FName InLabel) = 0;`
- L20 _public prototype_ `virtual void RepopulateTreeData() = 0;`
- L22 _public prototype_ `virtual TWeakObjectPtr<UAbstractSkeletonLabelBinding> GetLabelBinding() const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/ILabelSkeletonTree.h` (Private)


#### class `UE::UAF::Editor::ILabelSkeletonTreeWidget`  
`class ILabelSkeletonTreeWidget`  
_L10-18_
- L13 _public prototype_ `virtual ~ILabelSkeletonTreeWidget() = default;`
- L15 _public prototype_ `virtual void ScrollToBone(const FName InBoneName) = 0;`
- L17 _public prototype_ `virtual void RepopulateTreeData() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/ILabelsTab.h` (Private)


#### class `UE::UAF::Editor::ILabelsTab`  
`class ILabelsTab`  
_L13-25_
- L16 _public prototype_ `virtual ~ILabelsTab() = default;`
- L18 _public prototype_ `virtual TSharedPtr<ILabelBindingWidget> GetLabelBindingWidget() const = 0;`
- L20 _public prototype_ `virtual TSharedPtr<ILabelSkeletonTreeWidget> GetLabelSkeletonTreeWidget() const = 0;`
- L22 _public prototype_ `virtual void RepopulateLabelData() = 0;`
- L24 _public prototype_ `virtual TWeakPtr<IAbstractSkeletonEditor> GetAbstractSkeletonEditor() const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/LabelBindingAssetDefinition.h` (Private)


#### class `UAssetDefinition_AbstractSkeletonLabelBinding`  
`class UAssetDefinition_AbstractSkeletonLabelBinding : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/LabelBindingFactory.h` (Private)


#### class `UAbstractSkeletonLabelBindingFactory`  
`class UAbstractSkeletonLabelBindingFactory : public UFactory`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _private prototype_ `UAbstractSkeletonLabelBindingFactory();`
- L17 _private prototype_ `virtual bool ConfigureProperties() override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L19 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/LabelCollectionAssetDefinition.h` (Private)


#### class `UAssetDefinition_AbstractSkeletonLabelCollection`  
`class UAssetDefinition_AbstractSkeletonLabelCollection : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/LabelCollectionEditor.h` (Private)


#### class `UE::UAF::Editor::FLabelCollectionEditorToolkit`  
`class FLabelCollectionEditorToolkit : public FAssetEditorToolkit`  
_L12-31_
- inherits: `FAssetEditorToolkit`
- L15 _public prototype_ `void InitEditor(const TArray<UObject*>& InObjects);`
- L18 _public prototype_ `void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L19 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L21 _public function_ `FName GetToolkitFName() const override`
- L22 _public function_ `FText GetBaseToolkitName() const override`
- L23 _public function_ `FString GetWorldCentricTabPrefix() const override`
- L24 _public function_ `FLinearColor GetWorldCentricTabColorScale() const override`
- L28 _private prototype_ `TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);`
- L30 _private member_ `TWeakObjectPtr<UAbstractSkeletonLabelCollection> LabelCollection;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/LabelCollectionFactory.h` (Private)


#### class `UAbstractSkeletonLabelCollectionFactory`  
`class UAbstractSkeletonLabelCollectionFactory : public UFactory`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _private prototype_ `UAbstractSkeletonLabelCollectionFactory();`
- L17 _private prototype_ `virtual bool ConfigureProperties() override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L19 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/LabelDragDrop.h` (Private)


#### class `UE::UAF::Editor::FLabelDragDropOp`  
`class FLabelDragDropOp : public FDecoratedDragDropOp`  
_L12-41_
- inherits: `FDecoratedDragDropOp`
- L15 _public function_ `DRAG_DROP_OPERATOR_TYPE(FLabelDragDropOp, FDecoratedDragDropOp) static TSharedRef<FLabelDragDropOp> New(const TWeakObjectPtr<const UAbstractSkeletonLabelCollection> InLabelCollection, const FName InLabel)`
- L28 _public function_ `TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L39 _public member_ `TWeakObjectPtr<const UAbstractSkeletonLabelCollection> LabelCollection;`
- L40 _public member_ `FName Label;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/SLabelBinding.h` (Private)


#### class `UE::UAF::Editor::SLabelBinding`  
`class SLabelBinding : public SCompoundWidget, public FSelfRegisteringEditorUndoClient, public ILabelBindingWidget`  
_L23-117_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient,ILabelBindingWidget`
- L25 _private function_ `SLATE_BEGIN_ARGS(SLabelBinding)`
- L39 _public typedef_ `using FTreeItemPtr = TSharedPtr<ITreeItem>;`
- L68 _public prototype_ `void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonLabelBinding> InSetBinding, TSharedPtr<ILabelsTab> InLabelsTabInterface);`
- L71 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L72 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L75 _public prototype_ `virtual void ScrollToLabel(const TObjectPtr<const UAbstractSkeletonLabelCollection> InLabelCollection, const FName InLabel) override;` — ILabelBindingWidget
- L76 _public prototype_ `virtual void RepopulateTreeData() override;`
- L77 _public prototype_ `virtual TWeakObjectPtr<UAbstractSkeletonLabelBinding> GetLabelBinding() const override;`
- L80 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L82 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(FTreeItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L84 _private prototype_ `void TreeView_OnGetChildren(FTreeItemPtr InItem, TArray<FTreeItemPtr>& OutChildren);`
- L86 _private prototype_ `TSharedPtr<SWidget> TreeView_OnContextMenuOpening();`
- L88 _private prototype_ `void ExpandAllTreeItems();`
- L90 _private prototype_ `void BindCommands();`
- L92 _private prototype_ `TArray<FTreeItemPtr> GetAllTreeItems();`
- L94 _private prototype_ `void OnImportLabelCollection();`
- L96 _private prototype_ `TSharedRef<SWidget> CreateImportCollectionWidget();`
- L98 _private prototype_ `void OnRemoveSelected();`
- L100 _private member_ `TSharedPtr<ILabelsTab> LabelsTabInterface;`
- L103 _public member_ `TWeakObjectPtr<UAbstractSkeletonLabelBinding> LabelBinding;`
- L106 _private member_ `TSharedPtr<STreeView<FTreeItemPtr>> TreeView;`
- L108 _private member_ `TArray<FTreeItemPtr> RootItems;`
- L110 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L112 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L114 _private member_ `FSimpleDelegate OnTreeRefreshed;`
- L116 _private member_ `bool bRepopulating = false;`

#### struct `UE::UAF::Editor::SLabelBinding::ITreeItem`  
`struct ITreeItem`  
_L30-37_
- L32 _public prototype_ `virtual ~ITreeItem() = default;`
- L33 _public prototype_ `virtual void GetChildren(TArray<TSharedPtr<ITreeItem>>& OutChildren) = 0;`
- L34 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) = 0;`
- L35 _public prototype_ `virtual bool GenerateContextMenu(SLabelBinding& SetBindingWidget, FMenuBuilder& Menu) = 0;`
- L36 _public prototype_ `virtual void OnRemove() = 0;`

#### struct `UE::UAF::Editor::SLabelBinding::FTreeItem_LabelBinding`  
`struct FTreeItem_LabelBinding : public ITreeItem`  
_L41-53_
- inherits: `ITreeItem`
- L43 _public prototype_ `virtual ~FTreeItem_LabelBinding() override = default;`
- L44 _public prototype_ `virtual void GetChildren(TArray<FTreeItemPtr>& OutChildren) override;`
- L45 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L46 _public prototype_ `virtual bool GenerateContextMenu(SLabelBinding& SetBindingWidget, FMenuBuilder& Menu) override;`
- L47 _public prototype_ `virtual void OnRemove() override;`
- L49 _public member_ `FName Label;`
- L50 _public member_ `FName BoneName;`
- L51 _public member_ `TWeakObjectPtr<const UAbstractSkeletonLabelCollection> LabelCollection;`
- L52 _public member_ `TSharedPtr<ILabelsTab> LabelsTabInterface;`

#### struct `UE::UAF::Editor::SLabelBinding::FTreeItem_LabelCollection`  
`struct FTreeItem_LabelCollection : public ITreeItem`  
_L55-66_
- inherits: `ITreeItem`
- L57 _public prototype_ `virtual ~FTreeItem_LabelCollection() override = default;`
- L58 _public prototype_ `virtual void GetChildren(TArray<FTreeItemPtr>& OutChildren) override;`
- L59 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L60 _public prototype_ `virtual bool GenerateContextMenu(SLabelBinding& SetBindingWidget, FMenuBuilder& Menu) override;`
- L61 _public prototype_ `virtual void OnRemove() override;`
- L63 _public member_ `TWeakObjectPtr<const UAbstractSkeletonLabelCollection> LabelCollection;`
- L64 _public member_ `TArray<TSharedPtr<FTreeItem_LabelBinding>> LabelBindings;`
- L65 _public member_ `TSharedPtr<ILabelsTab> LabelsTabInterface;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/SLabelCollection.h` (Private)


#### class `UE::UAF::Editor::SLabelCollection`  
`class SLabelCollection : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L18-89_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L20 _private function_ `SLATE_BEGIN_ARGS(SLabelCollection)`
- L38 _public typedef_ `using FListItemPtr = TSharedPtr<FListItem>;`
- L40 _public prototype_ `virtual void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonLabelCollection> InLabelCollection);`
- L43 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L44 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L47 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L49 _private prototype_ `TSharedRef<ITableRow> ListView_OnGenerateRow(FListItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L51 _private prototype_ `TSharedPtr<SWidget> ListView_OnContextMenuOpening();`
- L53 _private prototype_ `void ListView_OnItemScrolledIntoView(FListItemPtr InItem, const TSharedPtr<ITableRow>& InWidget);`
- L55 _private prototype_ `void ListView_OnMouseButtonDoubleClick(FListItemPtr InItem);`
- L57 _private prototype_ `void OnAddLabel();`
- L59 _private prototype_ `void OnRenameLabel();`
- L61 _private prototype_ `void OnRemoveLabel();`
- L63 _private prototype_ `void RepopulateListData();`
- L65 _private prototype_ `void BindCommands();`
- L67 _private prototype_ `void OnItemRenamed(const FName OldLabel, const FName NewLabel);`
- L69 _private prototype_ `bool CanRenameItem(const FName OldLabel, const FName NewLabel) const;`
- L71 _private prototype_ `void ApplySearchFilter();`
- L74 _private member_ `TWeakObjectPtr<UAbstractSkeletonLabelCollection> LabelCollection;`
- L76 _private member_ `TSharedPtr<SListView<FListItemPtr>> ListView;`
- L78 _private member_ `TArray<FListItemPtr> ListItems;`
- L80 _private member_ `TArray<FListItemPtr> FilteredItems;`
- L82 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L84 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L86 _private member_ `FListItemPtr ItemToRename;`
- L88 _private member_ `FText SearchText;`

#### struct `UE::UAF::Editor::SLabelCollection::FListItem`  
`struct FListItem`  
_L24-36_
- L26 _public member_ `FName Label;`
- L28 _public prototype_ `DECLARE_DELEGATE(FOnRequestRename);`
- L29 _public member_ `FOnRequestRename OnRequestRename;`
- L31 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanRenameTo, const FName , const FName );`
- L32 _public member_ `FCanRenameTo CanRenameTo;`
- L34 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnRenamed, const FName , const FName );`
- L35 _public member_ `FOnRenamed OnRenamed;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L28 _delegate_ `DECLARE_DELEGATE(FOnRequestRename);`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanRenameTo, const FName , const FName );`
- L34 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRenamed, const FName , const FName );`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/SLabelSkeletonTree.h` (Private)


#### class `UE::UAF::Editor::SLabelSkeletonTree`  
`class SLabelSkeletonTree : public SCompoundWidget, public FSelfRegisteringEditorUndoClient, public ILabelSkeletonTreeWidget`  
_L22-89_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient,ILabelSkeletonTreeWidget`
- L24 _private function_ `SLATE_BEGIN_ARGS(SLabelSkeletonTree)`
- L42 _public typedef_ `using FTreeItemPtr = TSharedPtr<FTreeItem>;`
- L44 _public prototype_ `void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonLabelBinding> InSetBinding, TSharedPtr<ILabelsTab> InLabelsTabInterface);`
- L47 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L48 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L51 _public prototype_ `virtual void ScrollToBone(const FName InBoneName) override;` — ILabelSkeletonTreeWidget
- L52 _public prototype_ `virtual void RepopulateTreeData() override;`
- L55 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L57 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(FTreeItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L59 _private prototype_ `void TreeView_OnGetChildren(FTreeItemPtr InItem, TArray<FTreeItemPtr>& OutChildren);`
- L61 _private prototype_ `TSharedPtr<SWidget> TreeView_OnContextMenuOpening();`
- L63 _private prototype_ `void ExpandAllTreeItems();`
- L65 _private prototype_ `void BindCommands();`
- L67 _private prototype_ `TArray<FTreeItemPtr> GetAllTreeItems();`
- L70 _private prototype_ `void HandleBoneSelectionChanged(const TArray<FName>& InBoneNames, ESelectInfo::Type InSelectInfo);` — Triggered when a bone is selected in the viewport
- L73 _public member_ `TWeakObjectPtr<UAbstractSkeletonLabelBinding> LabelBinding;`
- L76 _private member_ `TSharedPtr<STreeView<FTreeItemPtr>> TreeView;`
- L78 _private member_ `TArray<FTreeItemPtr> RootItems;`
- L80 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L82 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L84 _private member_ `FSimpleDelegate OnTreeRefreshed;`
- L86 _private member_ `bool bRepopulating = false;`
- L88 _private member_ `TSharedPtr<ILabelsTab> LabelsTabInterface;`

#### struct `UE::UAF::Editor::SLabelSkeletonTree::FTreeItem`  
`struct FTreeItem`  
_L29-40_
- L37 _public member_ `FName BoneName;`
- L38 _public member_ `TArray<TSharedPtr<FTreeItem>> Children;`
- L39 _public member_ `TArray<FBindings> AssignedLabels;`

#### struct `UE::UAF::Editor::SLabelSkeletonTree::FTreeItem::FBindings`  
`struct FBindings`  
_L31-35_
- L33 _public member_ `TWeakObjectPtr<const UAbstractSkeletonLabelCollection> LabelCollection;`
- L34 _public member_ `FName Label;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Labels/SLabelsTab.h` (Private)


#### class `UE::UAF::Editor::SLabelsTab`  
`class SLabelsTab : public SCompoundWidget, public ILabelsTab`  
_L19-59_
- inherits: `SCompoundWidget,ILabelsTab`
- L28 _public function_ `SLATE_BEGIN_ARGS(SLabelsTab)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ParentTab) SLATE_ARGUMENT(TWeakObjectPtr<UAbstractSkeletonLabelBinding>, LabelBinding) SLATE_ARGUMENT(TWeakPtr<IAbstractSkeletonEditor>, AbstractSkeletonEditor) SLATE_END_ARGS() virtual TSharedPtr<ILabelBindingWidget> GetLabelBindingWidget() const override;`
- L36 _public prototype_ `virtual TSharedPtr<ILabelSkeletonTreeWidget> GetLabelSkeletonTreeWidget() const override;`
- L37 _public prototype_ `virtual void RepopulateLabelData() override;`
- L38 _public prototype_ `virtual TWeakPtr<IAbstractSkeletonEditor> GetAbstractSkeletonEditor() const override;`
- L40 _public prototype_ `virtual void Construct(const FArguments& InArgs);`
- L43 _private prototype_ `void HandleTabManagerPersistLayout(const TSharedRef<FTabManager::FLayout>& LayoutToSave);`
- L46 _private member_ `TWeakObjectPtr<UAbstractSkeletonLabelBinding> LabelBinding;`
- L48 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L50 _private member_ `TSharedPtr<SDockTab> LabelSkeletonTreeTab;`
- L52 _private member_ `TSharedPtr<SLabelSkeletonTree> LabelSkeletonTreeWidget;`
- L54 _private member_ `TSharedPtr<SDockTab> LabelBindingTab;`
- L56 _private member_ `TSharedPtr<SLabelBinding> LabelBindingWidget;`
- L58 _private member_ `TWeakPtr<IAbstractSkeletonEditor> AbstractSkeletonEditor;`

#### struct `UE::UAF::Editor::SLabelsTab::FTabs`  
`struct FTabs`  
_L22-26_
- L24 _public member_ `static FName SkeletonTreeId;`
- L25 _public member_ `static FName LabelBindingsId;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/AttributeDragDrop.h` (Private)


#### class `UE::UAF::Editor::FAttributeDragDropOp`  
`class FAttributeDragDropOp : public FDecoratedDragDropOp`  
_L11-21_
- inherits: `FDecoratedDragDropOp`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAttributeDragDropOp, FDecoratedDragDropOp) static TSharedRef<FAttributeDragDropOp> New(TArray<FAnimationAttributeIdentifier>&& InAttributes);`
- L18 _public prototype_ `TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L20 _public member_ `TArray<FAnimationAttributeIdentifier> Attributes;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/Commands.h` (Private)


#### class `UE::UAF::Editor::FSetBindingEditorCommands`  
`class FSetBindingEditorCommands : public TCommands<FSetBindingEditorCommands>`  
_L13-31_
- inherits: `TCommands<FSetBindingEditorCommands>`
- L16 _public function_ `FSetBindingEditorCommands() : TCommands<FSetBindingEditorCommands> ( TEXT("SetBindingEditorCommands"), NSLOCTEXT("SetBindingEditorCommands", "SetBindingEditorCommands", "Set Binding Editor Commands"), NAME_None, FUAFStyle::Get().GetStyleSetName() )`
- L27 _public prototype_ `virtual void RegisterCommands() override;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> UnbindSelection;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SelectWithChildren;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SAttributesList.h` (Private)


#### class `UE::UAF::Editor::SAttributesList`  
`class SAttributesList : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L19-74_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAttributesList)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonSetBinding> SetBinding);`
- L27 _public prototype_ `void SetSetBinding(TWeakObjectPtr<UAbstractSkeletonSetBinding> InSetBinding);`
- L39 _public typedef_ `using FListItemPtr = TSharedPtr<FListItem>;`
- L43 _private prototype_ `virtual void Tick(const FGeometry& AllocatedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SCompoundWidget
- L46 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L47 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L49 _private prototype_ `void RepopulateListData();`
- L51 _private prototype_ `void RegisterMenus();`
- L53 _private prototype_ `void HandleAddNewAttribute();`
- L56 _private prototype_ `void HandleBindingsChanged();` — Called when the bindings inside the set binding asset we're editing have been modified
- L58 _private prototype_ `TSharedRef<ITableRow> ListView_OnGenerateRow(FListItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L60 _private prototype_ `TSharedPtr<SWidget> ListView_OnContextMenuOpening();`
- L62 _private prototype_ `TSharedRef<SWidget> CreateAddAttributeWidget();`
- L65 _private member_ `TArray<FListItemPtr> ListItems;`
- L67 _private member_ `TSharedPtr<SListView<FListItemPtr>> ListView;`
- L69 _private member_ `TWeakObjectPtr<UAbstractSkeletonSetBinding> SetBinding;`
- L71 _private member_ `FDelegateHandle OnBindingsChangedHandle;`
- L73 _private member_ `bool bListDirty = false;`

#### struct `UE::UAF::Editor::SAttributesList::FListItem`  
`struct FListItem`  
_L30-37_
- L32 _public prototype_ `FListItem(const FName InSetName, const FAnimationAttributeIdentifier& InAttribute);`
- L34 _public member_ `FAnimationAttributeIdentifier Attribute;`
- L35 _public member_ `FName SetName;`
- L36 _public member_ `TWeakPtr<SInlineEditableTextBlock> EditableTextBlock;`

#### class `UAttributesListMenuContext`  
`class UAttributesListMenuContext : public UObject`  
_L79-85_
- reflection: `UCLASS()`
- inherits: `UObject`
- L84 _public member_ `TWeakPtr<UE::UAF::Editor::SAttributesList> SetBindingWidget;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SSetBinding.h` (Private)


#### class `UE::UAF::Editor::SSetBinding`  
`class SSetBinding : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L20-167_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L22 _private function_ `SLATE_BEGIN_ARGS(SSetBinding)`
- L118 _public prototype_ `void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonSetBinding> InSetBinding);`
- L120 _public prototype_ `void SetSetBinding(TWeakObjectPtr<UAbstractSkeletonSetBinding> InSetBinding);`
- L124 _private prototype_ `virtual void Tick(const FGeometry& AllocatedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SCompoundWidget
- L125 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L128 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L129 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L131 _private prototype_ `void RepopulateTreeData();`
- L133 _private prototype_ `void BindCommands();`
- L135 _private prototype_ `void ExpandAllTreeItems();`
- L137 _private prototype_ `TArray<TSharedPtr<ITreeItem>> GetAllTreeItems();`
- L140 _private prototype_ `void HandleBindingsChanged();` — Called when the bindings inside the set binding asset we're editing have been modified
- L142 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(TSharedPtr<ITreeItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L144 _private prototype_ `void TreeView_OnGetChildren(TSharedPtr<ITreeItem> InItem, TArray<TSharedPtr<ITreeItem>>& OutChildren);`
- L146 _private prototype_ `TSharedPtr<SWidget> TreeView_OnContextMenuOpening();`
- L148 _private prototype_ `bool CanUnbindSelection() const;`
- L150 _private prototype_ `void HandleUnbindSelection();`
- L153 _public member_ `TWeakObjectPtr<UAbstractSkeletonSetBinding> SetBinding;`
- L156 _private member_ `TSharedPtr<STreeView<TSharedPtr<ITreeItem>>> TreeView;`
- L158 _private member_ `TArray<TSharedPtr<ITreeItem>> RootItems;`
- L160 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L162 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L164 _private member_ `FDelegateHandle OnBindingsChangedHandle;`
- L166 _private member_ `bool bTreeDirty = false;`

#### enum `UE::UAF::Editor::SSetBinding::ETreeItem`  
`enum class ETreeItem : uint8`  
_L28-33_
- desc: Sorting here determines ordering in the tree view
- L30 _public enumerator_ `Bone`
- L31 _public enumerator_ `Attribute`
- L32 _public enumerator_ `Set`

#### struct `UE::UAF::Editor::SSetBinding::ITreeItem`  
`struct ITreeItem`  
_L35-49_
- L37 _public function_ `ITreeItem(SSetBinding& InSetBindingWidget) : SetBindingWidget(InSetBindingWidget)`
- L42 _public prototype_ `virtual ~ITreeItem() = default;`
- L43 _public prototype_ `virtual ETreeItem GetType() const = 0;`
- L44 _public prototype_ `virtual void GetChildren(TArray<TSharedPtr<ITreeItem>>& OutChildren) = 0;`
- L45 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) = 0;`
- L46 _public prototype_ `virtual void SortChildren() = 0;`
- L48 _public member_ `SSetBinding& SetBindingWidget;`

#### struct `UE::UAF::Editor::SSetBinding::FTreeItem_Set`  
`struct FTreeItem_Set : public ITreeItem`  
_L51-74_
- inherits: `ITreeItem`
- L53 _public function_ `FTreeItem_Set(SSetBinding& InSetBindingWidget, FAbstractSkeletonSet InSet, bool bInIsDeletedSet, int32 InSetIndex) : ITreeItem(InSetBindingWidget) , Set(InSet) , bIsDeletedSet(bInIsDeletedSet) , SetIndex(InSetIndex)`
- L61 _public prototype_ `virtual ~FTreeItem_Set() override = default;`
- L63 _public function_ `static ETreeItem StaticGetType()`
- L65 _public function_ `virtual ETreeItem GetType() const override`
- L66 _public prototype_ `virtual void GetChildren(TArray<TSharedPtr<ITreeItem>>& OutChildren) override;`
- L67 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L68 _public prototype_ `virtual void SortChildren() override;`
- L70 _public member_ `FAbstractSkeletonSet Set;`
- L71 _public member_ `TArray<TSharedPtr<ITreeItem>> Children;`
- L72 _public member_ `bool bIsDeletedSet;`
- L73 _public member_ `int32 SetIndex;`

#### struct `UE::UAF::Editor::SSetBinding::FTreeItem_Bone`  
`struct FTreeItem_Bone : public ITreeItem`  
_L76-96_
- inherits: `ITreeItem`
- L78 _public function_ `FTreeItem_Bone(SSetBinding& InSetBindingWidget, FAbstractSkeleton_BoneBinding InBinding, int32 InBoneIndex) : ITreeItem(InSetBindingWidget) , Binding(InBinding) , BoneIndex(InBoneIndex)`
- L85 _public prototype_ `virtual ~FTreeItem_Bone() override = default;`
- L87 _public function_ `static ETreeItem StaticGetType()`
- L89 _public function_ `virtual ETreeItem GetType() const override`
- L90 _public prototype_ `virtual void GetChildren(TArray<TSharedPtr<ITreeItem>>& OutChildren) override;`
- L91 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L92 _public function_ `virtual void SortChildren() override`
- L94 _public member_ `FAbstractSkeleton_BoneBinding Binding;`
- L95 _public member_ `int32 BoneIndex;`

#### struct `UE::UAF::Editor::SSetBinding::FTreeItem_Attribute`  
`struct FTreeItem_Attribute : public ITreeItem`  
_L98-116_
- inherits: `ITreeItem`
- L100 _public function_ `FTreeItem_Attribute(SSetBinding& InSetBindingWidget, FAbstractSkeleton_AttributeBinding InBinding) : ITreeItem(InSetBindingWidget) , Binding(InBinding)`
- L106 _public prototype_ `virtual ~FTreeItem_Attribute() override = default;`
- L108 _public function_ `static ETreeItem StaticGetType()`
- L110 _public function_ `virtual ETreeItem GetType() const override`
- L111 _public prototype_ `virtual void GetChildren(TArray<TSharedPtr<ITreeItem>>& OutChildren) override;`
- L112 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L113 _public function_ `virtual void SortChildren() override`
- L115 _public member_ `FAbstractSkeleton_AttributeBinding Binding;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SSetCollection.h` (Private)


#### class `UE::UAF::Editor::SSetCollection`  
`class SSetCollection : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L15-31_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L17 _private function_ `SLATE_BEGIN_ARGS(SSetCollection)`
- L18 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonSetCollection> InSetCollection);`
- L23 _private prototype_ `void OnSetsChanged() const;`
- L26 _private member_ `TWeakObjectPtr<UAbstractSkeletonSetCollection> SetCollection;`
- L27 _private member_ `TSharedPtr<SSetCollectionTreeView> TreeView;`
- L28 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L30 _private member_ `FDelegateHandle OnSetsChangedHandle;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SSetCollectionTreeView.h` (Private)


#### struct `UE::UAF::Editor::FSetCollectionTreeItem`  
`struct FSetCollectionTreeItem`  
_L17-23_
- L19 _public member_ `FAbstractSkeletonSet Set;`
- L20 _public member_ `TArray<FSetCollectionTreeItemPtr> Children;`
- L21 _public member_ `FSimpleDelegate OnRequestRename;`
- L22 _public member_ `bool bVisible = true;`

#### class `UE::UAF::Editor::SSetCollectionTreeView`  
`class SSetCollectionTreeView : public STreeView<FSetCollectionTreeItemPtr>, public FSelfRegisteringEditorUndoClient`  
_L25-86_
- inherits: `STreeView<FSetCollectionTreeItemPtr>,FSelfRegisteringEditorUndoClient`
- L27 _private function_ `SLATE_BEGIN_ARGS(SSetCollectionTreeView)`
- L29 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonSetCollection> InSetCollection);`
- L32 _private prototype_ `virtual ~SSetCollectionTreeView();`
- L35 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L36 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L38 _private prototype_ `void BindCommands();`
- L39 _private prototype_ `void RepopulateTreeData();`
- L41 _private prototype_ `void HandleAddSet();`
- L42 _private prototype_ `void HandleRenameSet();`
- L43 _private prototype_ `void HandleRemoveSet();`
- L45 _private prototype_ `void OnSetsChanged();`
- L47 _private prototype_ `void ExpandAllTreeItems();`
- L48 _private prototype_ `TArray<FSetCollectionTreeItemPtr> GetAllTreeItems();`
- L50 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(FSetCollectionTreeItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L51 _private prototype_ `void TreeView_OnGetChildren(FSetCollectionTreeItemPtr InItem, TArray<FSetCollectionTreeItemPtr>& OutChildren);`
- L52 _private prototype_ `TSharedPtr<SWidget> TreeView_OnContextMenuOpening();`
- L53 _private prototype_ `void TreeView_OnItemScrolledIntoView(FSetCollectionTreeItemPtr InItem, const TSharedPtr<ITableRow>& InWidget);`
- L54 _private prototype_ `void TreeView_OnMouseButtonDoubleClick(FSetCollectionTreeItemPtr InItem);`
- L56 _private prototype_ `void RenameSet(const FName OldSetName, const FName NewSetName);`
- L58 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L60 _private prototype_ `void SetFilterText(const FText& InText);`
- L63 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L64 _private prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L65 _private prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent);`
- L66 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L68 _private prototype_ `FSetCollectionTreeItemPtr GetTreeItem(const FName SetName);`
- L70 _private prototype_ `void UpdateTreeItemVisibility();`
- L72 _private member_ `TArray<FSetCollectionTreeItemPtr> RootItems;`
- L74 _private member_ `TWeakObjectPtr<UAbstractSkeletonSetCollection> SetCollection;`
- L76 _private member_ `FName RequestedSetNameToRename;`
- L77 _private member_ `FSetCollectionTreeItemPtr RequestedSetItemToRename;`
- L79 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L81 _private member_ `FDelegateHandle OnSetsChangedHandle;`
- L83 _private member_ `bool bNeedsRebuilding = false;`
- L85 _private member_ `FText FilterText;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L15 _typedef_ `using FSetCollectionTreeItemPtr = TSharedPtr<FSetCollectionTreeItem>;` (scope `UE::UAF::Editor`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SSetSkeletonTree.h` (Private)


#### class `UE::UAF::Editor::SSetsSkeletonTree`  
`class SSetsSkeletonTree : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L17-82_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L29 _public function_ `SLATE_BEGIN_ARGS(SSetsSkeletonTree)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakObjectPtr<UAbstractSkeletonSetBinding> SetBinding);`
- L34 _public prototype_ `void SetSetBinding(TWeakObjectPtr<UAbstractSkeletonSetBinding> InSetBinding);`
- L38 _private prototype_ `virtual void Tick(const FGeometry& AllocatedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SCompoundWidget
- L39 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L42 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient interface
- L43 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L45 _private prototype_ `void RepopulateTreeData();`
- L47 _private prototype_ `void BindCommands();`
- L50 _private prototype_ `void HandleBindingsChanged();` — Called when the bindings inside the set binding asset we're editing have been modified
- L52 _private prototype_ `void HandleUnbindSelection();`
- L54 _private prototype_ `void HandleSelectWithChildren();`
- L56 _private prototype_ `bool IsSelectionNonEmpty() const;`
- L58 _private prototype_ `bool IsSelectionSingle() const;`
- L62 _private prototype_ `TArray<TSharedPtr<FTreeItem>> GetAllDescendentTreeItems(const TArray<TSharedPtr<FTreeItem>> ParentItems);` — Returns a list of the provided parents and all of their descendents Beware, the descendents of ParentItems should be non-overlapping!
- L64 _private prototype_ `TSharedRef<ITableRow> TreeView_OnGenerateRow(TSharedPtr<FTreeItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L66 _private prototype_ `void TreeView_OnGetChildren(TSharedPtr<FTreeItem> InParent, TArray<TSharedPtr<FTreeItem>>& OutChildren);`
- L68 _private prototype_ `TSharedPtr<SWidget> TreeView_OnContextMenuOpening();`
- L71 _private member_ `TWeakObjectPtr<UAbstractSkeletonSetBinding> SetBinding;`
- L73 _private member_ `TArray<TSharedPtr<FTreeItem>> RootItems;`
- L75 _private member_ `TSharedPtr<STreeView<TSharedPtr<FTreeItem>>> TreeView;`
- L77 _private member_ `FDelegateHandle OnBindingsChangedHandle;`
- L79 _private member_ `bool bTreeDirty = false;`
- L81 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### struct `UE::UAF::Editor::SSetsSkeletonTree::FTreeItem`  
`struct FTreeItem`  
_L20-27_
- L22 _public member_ `FName BoneName;`
- L23 _public member_ `FName BoundSet;`
- L25 _public member_ `TWeakPtr<FTreeItem> Parent;`
- L26 _public member_ `TArray<TSharedPtr<FTreeItem>> Children;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SSetsTab.h` (Private)


#### class `UE::UAF::Editor::SSetsTab`  
`class SSetsTab : public SCompoundWidget`  
_L18-39_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SSetsTab)`
- L22 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ParentTab) SLATE_ARGUMENT(TWeakObjectPtr<UAbstractSkeletonSetBinding>, SetBinding) SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `void HandleTabManagerPersistLayout(const TSharedRef<FTabManager::FLayout>& LayoutToSave);`
- L32 _private member_ `TWeakObjectPtr<UAbstractSkeletonSetBinding> SetBinding;`
- L34 _private member_ `TSharedPtr<SSetsSkeletonTree> SkeletonTreeWidget;`
- L35 _private member_ `TSharedPtr<SAttributesList> AttributesListWidget;`
- L36 _private member_ `TSharedPtr<SSetBinding> SetBindingWidget;`
- L38 _private member_ `TSharedPtr<FTabManager> TabManager;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SetBindingAssetDefinition.h` (Private)


#### class `UAssetDefinition_AbstractSkeletonSetBinding`  
`class UAssetDefinition_AbstractSkeletonSetBinding : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SetCollectionAssetDefinition.h` (Private)


#### class `UAssetDefinition_AbstractSkeletonSetCollection`  
`class UAssetDefinition_AbstractSkeletonSetCollection : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SetCollectionEditor.h` (Private)


#### class `UE::UAF::Editor::FSetCollectionEditorToolkit`  
`class FSetCollectionEditorToolkit : public FAssetEditorToolkit`  
_L11-28_
- inherits: `FAssetEditorToolkit`
- L14 _public prototype_ `void InitEditor(const TArray<UObject*>& InObjects);`
- L17 _public prototype_ `void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L18 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L20 _public function_ `FName GetToolkitFName() const override`
- L21 _public function_ `FText GetBaseToolkitName() const override`
- L22 _public function_ `FString GetWorldCentricTabPrefix() const override`
- L23 _public function_ `FLinearColor GetWorldCentricTabColorScale() const override`
- L27 _private member_ `TWeakObjectPtr<UAbstractSkeletonSetCollection> SetCollection;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SetDragDrop.h` (Private)


#### class `UE::UAF::Editor::FSetDragDropOp`  
`class FSetDragDropOp : public FDecoratedDragDropOp`  
_L11-41_
- inherits: `FDecoratedDragDropOp`
- L21 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FSetDragDropOp, FDecoratedDragDropOp) static TSharedRef<FSetDragDropOp> New(TArray<FAbstractSkeletonSet>&& InSets);`
- L25 _public prototype_ `virtual void Construct() override;`
- L27 _public prototype_ `TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L29 _public prototype_ `void SetOperation(const EOperation InOperation, const FName InOperationSetName);`
- L30 _public prototype_ `void ClearOperation();`
- L32 _public prototype_ `const TArray<FAbstractSkeletonSet>& GetDraggedSets() const;`
- L35 _private member_ `TArray<FAbstractSkeletonSet> Sets;`
- L37 _private member_ `EOperation Operation = EOperation::None;`
- L38 _private member_ `FName OperationSetName;`
- L40 _private member_ `FText CachedSetsText;`

#### enum `UE::UAF::Editor::FSetDragDropOp::EOperation`  
`enum class EOperation : uint8`  
_L14-19_
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `Reparent`
- L18 _public enumerator_ `Bind`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/AbstractSkeleton/Sets/SkeletonTreeDragDrop.h` (Private)


#### class `UE::UAF::Editor::FSkeletonTreeDragDropOp`  
`class FSkeletonTreeDragDropOp : public FDecoratedDragDropOp`  
_L11-38_
- inherits: `FDecoratedDragDropOp`
- L14 _public function_ `DRAG_DROP_OPERATOR_TYPE(FSkeletonTreeDragDropOp, FDecoratedDragDropOp) static TSharedRef<FSkeletonTreeDragDropOp> New(TArray<TSharedPtr<SSetsSkeletonTree::FTreeItem>>&& InItems)`
- L26 _public function_ `TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L37 _public member_ `TArray<TSharedPtr<SSetsSkeletonTree::FTreeItem>> Items;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/BlendMask/BlendMaskAssetDefinition.h` (Private)


#### class `UAssetDefinition_UAFBlendMask`  
`class UAssetDefinition_UAFBlendMask : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/BlendMask/BlendMaskEditorToolkit.h` (Private)


#### class `UE::UAF::FBlendMaskEditorToolkit`  
`class FBlendMaskEditorToolkit : public FAssetEditorToolkit`  
_L14-39_
- inherits: `FAssetEditorToolkit`
- L17 _public prototype_ `void InitEditor(const TArray<UObject*>& InObjects);`
- L20 _public prototype_ `void OnClose() override;`
- L22 _public prototype_ `void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L23 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L25 _public function_ `FName GetToolkitFName() const override`
- L26 _public prototype_ `FText GetBaseToolkitName() const override;`
- L27 _public function_ `FString GetWorldCentricTabPrefix() const override`
- L28 _public function_ `FLinearColor GetWorldCentricTabColorScale() const override`
- L32 _private prototype_ `void OnSkeletonHierarchyChanged();`
- L34 _private prototype_ `void ExtendToolbar();`
- L36 _private member_ `TObjectPtr<UUAFBlendMask> BlendMask;`
- L38 _private member_ `TSharedPtr<IHierarchyTable> HierarchyTableWidgetInterface;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/BlendMask/BlendMaskFactory.h` (Private)


#### class `UUAFBlendMaskFactory`  
`class UUAFBlendMaskFactory : public UFactory`  
_L14-30_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L19 _public prototype_ `UUAFBlendMaskFactory();`
- L22 _public prototype_ `UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L23 _public prototype_ `virtual bool ConfigureProperties() override;`
- L27 _private member_ `TObjectPtr<UHierarchyTable_TableTypeHandler> TableHandler;` — `UPROPERTY()`
- L29 _private member_ `FInstancedStruct TableMetadata;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/BlendProfile/BlendProfileAssetDefinition.h` (Private)


#### class `UAssetDefinition_UAFBlendProfile`  
`class UAssetDefinition_UAFBlendProfile : public UAssetDefinitionDefault`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual void GetAssetStatusInfo(const TSharedPtr<IAssetStatusInfoProvider>& InAssetStatusInfoProvider, TArray<FAssetDisplayInfo>& OutStatusInfo) const;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/BlendProfile/BlendProfileEditorToolkit.h` (Private)


#### class `UE::UAF::FBlendProfileEditorToolkit`  
`class FBlendProfileEditorToolkit : public FAssetEditorToolkit`  
_L14-39_
- inherits: `FAssetEditorToolkit`
- L17 _public prototype_ `void InitEditor(const TArray<UObject*>& InObjects);`
- L20 _public prototype_ `void OnClose() override;`
- L22 _public prototype_ `void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L23 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L25 _public function_ `FName GetToolkitFName() const override`
- L26 _public prototype_ `FText GetBaseToolkitName() const override;`
- L27 _public function_ `FString GetWorldCentricTabPrefix() const override`
- L28 _public function_ `FLinearColor GetWorldCentricTabColorScale() const override`
- L32 _private prototype_ `void OnSkeletonHierarchyChanged();`
- L34 _private prototype_ `void ExtendToolbar();`
- L36 _private member_ `TObjectPtr<UUAFBlendProfile> BlendProfile;`
- L38 _private member_ `TSharedPtr<IHierarchyTable> HierarchyTableWidgetInterface;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/BlendProfile/BlendProfileFactory.h` (Private)


#### class `UUAFBlendProfileFactory`  
`class UUAFBlendProfileFactory : public UFactory`  
_L15-37_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L20 _public prototype_ `UUAFBlendProfileFactory();`
- L23 _public prototype_ `UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L24 _public prototype_ `virtual bool ConfigureProperties() override;`
- L27 _private prototype_ `bool ConfigureBlendProfileType();`
- L29 _private prototype_ `bool ConfigureBlendProfileHierarchy();`
- L32 _private member_ `TObjectPtr<UHierarchyTable_TableTypeHandler> TableHandler;` — `UPROPERTY()`
- L34 _private member_ `EUAFBlendProfileType BlendProfileType;`
- L36 _private member_ `FInstancedStruct TableMetadata;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Debug/SVariableWatch.h` (Private)


#### class `UE::UAF::Editor::SVariableWatch`  
`class SVariableWatch : public SCompoundWidget`  
_L24-98_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SVariableWatch)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditor);`
- L42 _public typedef_ `using FDebugInstanceTreeItemPtr = TSharedPtr<FDebugInstance>;`
- L44 _public typedef_ `using FVariablesBoxItemPtr = TSharedPtr<FName>;`
- L47 _private prototype_ `void HandleWorkspaceEditorModeChanged(const FEditorModeID& EditorModeId, bool bIsEnteringMode);`
- L49 _private prototype_ `void HandleRewindDebuggerUpdate(float DeltaTime, IRewindDebugger* RewindDebugger);`
- L51 _private prototype_ `void RegenerateDebugInstances(const bool bForceRegenerate);`
- L52 _private prototype_ `void OnDebugInstanceChanged();`
- L54 _private prototype_ `void HandleFocusedDocumentChanged(const UE::Workspace::FWorkspaceDocument& InDocument);`
- L55 _private prototype_ `void HandleWorkspaceDebugObjectChanged(TWeakObjectPtr<UObject> InObject);`
- L57 _private prototype_ `void InstanceTreeView_OnGetChildren(FDebugInstanceTreeItemPtr InItem, TArray<FDebugInstanceTreeItemPtr>& OutChildren);`
- L58 _private prototype_ `TSharedRef<ITableRow> InstanceTreeView_OnGenerateRow(FDebugInstanceTreeItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L59 _private prototype_ `void InstanceTreeView_OnSelectionChanged(FDebugInstanceTreeItemPtr NewSelection, ESelectInfo::Type);`
- L61 _private prototype_ `TSharedRef<ITableRow> VariablesListView_OnGenerateRow(const FVariablesBoxItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L64 _private member_ `IRewindDebugger* RewindDebugger = nullptr;`
- L66 _private member_ `FInstancedPropertyBag Properties;`
- L67 _private member_ `FInstancedStruct NativeProperties;`
- L70 _private member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WorkspaceEditor;`
- L72 _private member_ `TArray<FDebugInstanceTreeItemPtr> RootDebugInstances;`
- L73 _private member_ `TMap<uint64, FDebugInstanceTreeItemPtr> DebugInstances;`
- L75 _private member_ `TSharedPtr<STreeView<FDebugInstanceTreeItemPtr>> DebugInstanceTreeView;`
- L77 _private member_ `FDebugInstanceTreeItemPtr SelectedDebugInstance;`
- L86 _public typedef_ `using FTreeItemPtr = TSharedPtr<FTreeItem>;`
- L88 _public member_ `TSharedPtr<STreeView<FTreeItemPtr>> TreeView;`
- L91 _private member_ `TSharedPtr<SListView<FVariablesBoxItemPtr>> VariablesBox;`
- L93 _private member_ `TArray<FVariablesBoxItemPtr> VariablesBoxSource;`
- L95 _private member_ `TArray<FTreeItemPtr> TreeItems;`
- L97 _private member_ `uint64 SelectedDebugInstanceId = 0;`

#### struct `UE::UAF::Editor::SVariableWatch::FDebugInstance`  
`struct FDebugInstance`  
_L35-40_
- L37 _public member_ `uint64 InstanceId;`
- L38 _public member_ `uint64 HostInstanceId;`
- L39 _public member_ `UObject* Asset;`

#### class `UE::UAF::Editor::SVariableWatch::FTreeItem`  
`class FTreeItem`  
_L80-84_
- L83 _public member_ `TStrongObjectPtr<UUAFRigVMAssetEntry> AssetEntry;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Debug/VariableWatchTabSummoner.h` (Private)


#### struct `UE::UAF::Editor::FVariableWatchTabSummoner`  
`struct FVariableWatchTabSummoner : public FWorkflowTabFactory`  
_L13-25_
- inherits: `FWorkflowTabFactory`
- L16 _public prototype_ `FVariableWatchTabSummoner(TSharedPtr<UE::Workspace::IWorkspaceEditor> InHostingApp);`
- L20 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L21 _private prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _private member_ `TSharedPtr<SVariableWatch> Widget;` — The widget this tab spawner wraps

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Viewport/SystemViewportController.h` (Private)


#### class `UE::UAF::Editor::FSystemViewportController`  
`class FSystemViewportController : public Workspace::IWorkspaceViewportController`  
_L9-15_
- inherits: `Workspace::IWorkspaceViewportController`
- L11 _private prototype_ `virtual void OnEnter(const FViewportContext& InViewportContext) override;`
- L12 _private prototype_ `virtual void OnExit(FAdvancedPreviewScene* PreviewScene) override;`
- L14 _private member_ `TArray<AActor*> PreviewActors;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Wizard/AssetWizard.h` (Private)


#### class `UE::UAF::Editor::FAssetWizard`  
`class FAssetWizard`  
_L13-22_
- L16 _public prototype_ `static void Launch();`
- L19 _private prototype_ `static void ShowTemplatePicker();`
- L21 _private prototype_ `static void CreateAssets(const TObjectPtr<const UUAFTemplateDataAsset> Template, const TObjectPtr<const UUAFTemplateConfig> TemplateConfig);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Wizard/STemplatePicker.h` (Private)


#### class `UE::UAF::Editor::STemplatePicker`  
`class STemplatePicker : public SCompoundWidget, public FGCObject`  
_L18-90_
- inherits: `SCompoundWidget,FGCObject`
- L23 _public function_ `SLATE_BEGIN_ARGS(STemplatePicker)`
- L24 _public prototype_ `SLATE_EVENT(FOnTemplateSelected, OnTemplateSelected) SLATE_EVENT(FSimpleDelegate, OnCancel) SLATE_END_ARGS() virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L30 _public function_ `virtual FString GetReferencerName() const override`
- L35 _public prototype_ `void Construct(const FArguments& InArgs);`
- L38 _private prototype_ `void RefreshModuleTemplates();`
- L40 _private prototype_ `void HandleSelectedTemplateChanged();`
- L42 _private prototype_ `void HandleUseTemplate();`
- L44 _private prototype_ `void HandleOutputPathChanged();`
- L46 _private prototype_ `void HandleBlueprintToModifyChanged();`
- L48 _private prototype_ `void UpdateUserAssetNames();`
- L50 _private prototype_ `bool CanCreateAssets() const;`
- L63 _private typedef_ `using FTemplateItemPtr = TSharedPtr<FTemplate>;`
- L65 _private member_ `TSharedPtr<STileView<FTemplateItemPtr>> TemplatesTileView;`
- L67 _private member_ `TArray<FTemplateItemPtr> Templates;`
- L69 _private member_ `FTemplateItemPtr SelectedTemplate;`
- L71 _private member_ `TSharedPtr<SHorizontalBox> TagsHBox;`
- L73 _private member_ `EPanel ShowPanel = EPanel::Details;`
- L81 _private member_ `TArray<TSharedPtr<FAssetMetadata>> IncludedAssets;`
- L83 _private member_ `FOnTemplateSelected OnTemplateSelected;`
- L85 _private member_ `TObjectPtr<UUAFTemplateConfig> TemplateConfig;`
- L87 _private member_ `TSharedPtr<SListView<TSharedPtr<FAssetMetadata>>> IncludedAssetsListView;`
- L89 _private member_ `mutable FText ErrorText;`

#### enum `UE::UAF::Editor::STemplatePicker::EPanel`  
`enum class EPanel`  
_L52-56_
- L54 _public enumerator_ `Overview`
- L55 _public enumerator_ `Details`

#### struct `UE::UAF::Editor::STemplatePicker::FTemplate`  
`struct FTemplate`  
_L58-61_
- L60 _public member_ `TObjectPtr<UUAFTemplateDataAsset> Template;`

#### struct `UE::UAF::Editor::STemplatePicker::FAssetMetadata`  
`struct FAssetMetadata`  
_L75-79_
- L77 _public member_ `FString AssetRename;`
- L78 _public member_ `FAssetData AssetData;`

#### class `UE::UAF::Editor::SModuleTemplate`  
`class SModuleTemplate : public STableRow<TSharedPtr<STemplatePicker::FTemplate>>`  
_L92-103_
- inherits: `STableRow<TSharedPtr<STemplatePicker::FTemplate>>`
- L95 _public function_ `SLATE_BEGIN_ARGS(SModuleTemplate)`
- L96 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<STemplatePicker::FTemplate>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable);`
- L102 _private member_ `TSharedPtr<STemplatePicker::FTemplate> Item;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnTemplateSelected, const TObjectPtr<const UUAFTemplateDataAsset>, const TObjectPtr<const UUAFTemplateConfig>);`
- L16 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnTemplateSelected, const TObjectPtr<const UUAFTemplateDataAsset>, const TObjectPtr<const UUAFTemplateConfig>);` (scope `UE::UAF::Editor`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Wizard/TemplateConfig.h` (Private)


#### enum `ETemplateBlueprintMode`  
`enum class ETemplateBlueprintMode`  
_L15-20_
- reflection: `UENUM()`
- L17 _public enumerator_ `CreateNewBlueprint`
- L18 _public enumerator_ `ModifyExistingBlueprint`
- L19 _public enumerator_ `DoNothing`

#### class `UUAFTemplateConfig`  
`class UUAFTemplateConfig : public UObject`  
_L23-57_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L30 _public member_ `ETemplateBlueprintMode BlueprintMode = ETemplateBlueprintMode::CreateNewBlueprint;` — `UPROPERTY(Config, EditAnywhere, Category = "Config")` — Whether the template should also set up a new Blueprint for this template
- L33 _public member_ `FString BlueprintAssetName;` — `UPROPERTY(Config, EditAnywhere, Category = "Config", Meta = (EditCondition = "BlueprintMode == ETemplateBlueprintMode::CreateNewBlueprint", EditConditionHides))`
- L36 _public member_ `TSubclassOf<AActor> BlueprintClass = APawn::StaticClass();` — `UPROPERTY(Config, EditAnywhere, Category = "Config", Meta = (EditCondition = "BlueprintMode == ETemplateBlueprintMode::CreateNewBlueprint", EditConditionHides))`
- L39 _public member_ `TSoftObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(Config, EditAnywhere, Category = "Config", Meta = (EditCondition = "BlueprintMode == ETemplateBlueprintMode::CreateNewBlueprint", EditConditionHides))`
- L42 _public member_ `TSoftObjectPtr<UBlueprint> BlueprintToModify;` — `UPROPERTY(EditAnywhere, Category = "Config", Meta = (EditCondition = "BlueprintMode == ETemplateBlueprintMode::ModifyExistingBlueprint", EditConditionHides, DisallowCreateNew))`
- L45 _public member_ `FDirectoryPath OutputPath;` — `UPROPERTY(EditAnywhere, Category = "Output", Meta = (ContentDir))`
- L48 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject
- L50 _public member_ `FSimpleMulticastDelegate OnOutputPathChanged;`
- L51 _public member_ `FSimpleMulticastDelegate OnBlueprintToModifyChanged;`
- L53 _public prototype_ `void Reset();`
- L56 _public member_ `TArray<FString> AssetNaming;`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Wizard/TemplateDataAsset.h` (Private)


#### class `UUAFTemplateDataAsset`  
`class UUAFTemplateDataAsset : public UPrimaryDataAsset`  
_L14-51_
- reflection: `UCLASS()`
- inherits: `UPrimaryDataAsset`
- L20 _public member_ `FText Title;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L23 _public member_ `FText Description;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L26 _public member_ `FString DocumentationUrl;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L29 _public member_ `TArray<FText> Tags;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L32 _public member_ `FSlateBrush ThumbnailImage;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L35 _public member_ `FSlateBrush DetailsImage;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L39 _public member_ `TArray<TObjectPtr<UObject>> Assets;` — `UPROPERTY(EditAnywhere, Category = Default)` — These are the assets that form this template. Each of these will be duplicated into the user's chosen directory (with references patched).
- L43 _public member_ `TObjectPtr<UObject> AssetToOpen;` — `UPROPERTY(EditAnywhere, Category = Default)` — This is the asset that will be opened automatically once the wizard has finished creating the assets for this template.
- L47 _public member_ `TObjectPtr<UUAFSystem> SystemToAssignToComponent;` — `UPROPERTY(EditAnywhere, Category = Default)` — This is the UAF system that we will assign to the UAF component if the user is configuring a blueprint.
- L50 _public member_ `FString DefaultBlueprintAssetName;` — `UPROPERTY(EditAnywhere, Category = Default)`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Workspace/IDebugObjectSelector.h` (Private)


#### class `UE::UAF::Editor::IDebugObjectSelector`  
`class IDebugObjectSelector`  
_L9-21_
- L12 _public prototype_ `virtual ~IDebugObjectSelector() = default;`
- L14 _public typedef_ `using FOnDebugObjectChanged = TMulticastDelegate<void(TWeakObjectPtr<UObject>)>;`
- L16 _public prototype_ `virtual TWeakObjectPtr<UObject> GetDebugObject() const = 0;`
- L18 _public prototype_ `virtual FDelegateHandle RegisterOnDebugObjectChanged(FOnDebugObjectChanged::FDelegate InDelegate) = 0;`
- L20 _public prototype_ `virtual bool UnregisterOnDebugObjectChanged(const FDelegateHandle InHandle) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Workspace/IUAFWorkspaceRewindDebugger.h` (Private)


#### class `UE::UAF::Editor::IUAFWorkspaceRewindDebugger`  
`class IUAFWorkspaceRewindDebugger`  
_L9-18_
- L12 _public prototype_ `virtual ~IUAFWorkspaceRewindDebugger() = default;`
- L14 _public typedef_ `using FOnRewindDebuggerUpdate = TMulticastDelegate<void(float, class IRewindDebugger*)>;`
- L16 _public prototype_ `virtual FDelegateHandle RegisterOnRewindDebuggerUpdate(FOnRewindDebuggerUpdate::FDelegate InDelegate) = 0;`
- L17 _public prototype_ `virtual bool UnregisterOnRewindDebuggerUpdate(const FDelegateHandle InHandle) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Workspace/RewindDebuggerExtension.h` (Private)


#### class `UE::UAF::Editor::FRewindDebuggerWorkspaceExtension`  
`class FRewindDebuggerWorkspaceExtension : public IRewindDebuggerExtension, public IUAFWorkspaceRewindDebugger`  
_L18-35_
- inherits: `IRewindDebuggerExtension,IUAFWorkspaceRewindDebugger`
- desc: FRewindDebuggerWorkspaceExtension exists to allow any systems interacting with the workspace editor to query a centralized rewind debugger extension instead of having to define and register their own.
- L21 _public prototype_ `virtual ~FRewindDebuggerWorkspaceExtension() override = default;`
- L24 _public prototype_ `virtual FDelegateHandle RegisterOnRewindDebuggerUpdate(FOnRewindDebuggerUpdate::FDelegate InDelegate) override;` — IUAFWorkspaceRewindDebugger
- L25 _public prototype_ `virtual bool UnregisterOnRewindDebuggerUpdate(const FDelegateHandle InHandle) override;`
- L29 _private prototype_ `virtual FString GetName() override;` — IRewindDebuggerExtension
- L30 _private prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`
- L33 _private member_ `FOnRewindDebuggerUpdate OnRewindDebuggerUpdate;`
- L34 _private member_ `float LastScrubTime = 0.0f;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Workspace/SDebugObjectSelector.h` (Private)


#### class `UE::UAF::Editor::SDebugObjectSelector`  
`class SDebugObjectSelector : public SCompoundWidget, public IDebugObjectSelector`  
_L11-40_
- inherits: `SCompoundWidget,IDebugObjectSelector`
- L14 _public function_ `DECLARE_DELEGATE_OneParam(FGetDebugObjects, TArray<UObject*>&) SLATE_BEGIN_ARGS(SDebugObjectSelector)`
- L18 _public prototype_ `SLATE_EVENT(FGetDebugObjects, GetDebugObjects) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _public prototype_ `virtual TWeakObjectPtr<UObject> GetDebugObject() const override;` — IDebugObjectSelector
- L25 _public prototype_ `virtual FDelegateHandle RegisterOnDebugObjectChanged(FOnDebugObjectChanged::FDelegate InDelegate) override;`
- L26 _public prototype_ `virtual bool UnregisterOnDebugObjectChanged(const FDelegateHandle InHandle) override;`
- L29 _private prototype_ `TSharedRef<SWidget> ComboBox_OnGenerateWidget(TSharedPtr<FBlueprintDebugObjectInstance> InItem);`
- L30 _private prototype_ `void ComboBox_OnSelectionChanged(TSharedPtr<FBlueprintDebugObjectInstance> NewSelection, ESelectInfo::Type SelectInfo);`
- L31 _private prototype_ `void ComboBox_OnComboBoxOpening();`
- L33 _private prototype_ `void RegenerateDebugObjects();`
- L35 _private member_ `FOnDebugObjectChanged OnDebugObjectChangedDelegate;`
- L36 _private member_ `FGetDebugObjects GetDebugObjectsDelegate;`
- L38 _private member_ `TArray<TSharedPtr<FBlueprintDebugObjectInstance>> DebugObjects;`
- L39 _private member_ `TSharedPtr<FBlueprintDebugObjectInstance> Selected;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UAF` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FGetDebugObjects, TArray<UObject*>&) SLATE_BEGIN_ARGS(SDebugObjectSelector) {} SLATE_EVENT(FGetDebugObjects, GetDebugObjects) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/AnimNextSharedVariablesAssetDefinition.h` (Private)


#### class `UAssetDefinition_AnimNextSharedVariables`  
`class UAssetDefinition_AnimNextSharedVariables : public UAssetDefinitionDefault`  
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

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/AnimNextVariableSettings.h` (Private)


#### class `UAnimNextVariableSettings`  
`class UAnimNextVariableSettings : public UDeveloperSettings`  
_L11-41_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- L15 _private prototype_ `UAnimNextVariableSettings();`
- L19 _public prototype_ `const FAnimNextParamType& GetLastVariableType() const;` — Get the type of the last variable that we created
- L22 _public prototype_ `void SetLastVariableType(const FAnimNextParamType& InLastVariableType);` — Set the type of the last variable that we created
- L25 _public prototype_ `FName GetLastVariableName() const;` — Get the name of the last variable that we created
- L28 _public prototype_ `void SetLastVariableName(FName InLastVariableName);` — Set the name of the last variable that we created
- L30 _public prototype_ `SPinTypeSelector::ESelectorType GetVariablesViewDefaultPinSelectorType() const;`
- L31 _public prototype_ `void SetVariablesViewDefaultPinSelectorType(SPinTypeSelector::ESelectorType InLastSelectorType);`
- L34 _private member_ `FAnimNextParamType LastVariableType = FAnimNextParamType::GetType<bool>();` — `UPROPERTY(Transient)`
- L37 _private member_ `FName LastVariableName = FName("New` — `UPROPERTY(Transient)`
- L40 _private member_ `uint32 VariablesViewPinSelectorType = static_cast<uint32>(SPinTypeSelector::ESelectorType::Partial);` — `UPROPERTY(VisibleAnywhere, Category="UAF", Config)`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerCategoryItem.h` (Private)


#### struct `UE::UAF::Editor::FVariablesOutlinerCategoryItem`  
`struct FVariablesOutlinerCategoryItem : FOutlinerCategoryItem`  
_L13-21_
- inherits: `FOutlinerCategoryItem`
- L15 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L17 _public prototype_ `FVariablesOutlinerCategoryItem(const FOutlinerCategoryItem::FItemData& IntemData);`
- L19 _public prototype_ `virtual void Rename(const FText& InNewName) const override final;`
- L20 _public prototype_ `virtual bool ValidateName(const FText& InNewName, FText& OutErrorMessage) const override final;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerColumns.h` (Private)


#### class `UE::UAF::Editor::FVariablesOutlinerTypeColumn`  
`class FVariablesOutlinerTypeColumn : public ISceneOutlinerColumn`  
_L19-38_
- inherits: `ISceneOutlinerColumn`
- L22 _public prototype_ `static FName GetID();`
- L24 _public prototype_ `FVariablesOutlinerTypeColumn(ISceneOutliner& SceneOutliner);`
- L27 _public function_ `virtual FName GetColumnID() override` — ISceneOutlinerColumn interface
- L28 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L29 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L30 _public function_ `virtual bool SupportsSorting() const override`
- L33 _protected prototype_ `float GetColumnWidth() const;`
- L36 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`
- L37 _private member_ `SPinTypeSelector::ESelectorType SelectorType;`

#### class `UE::UAF::Editor::FVariablesOutlinerValueColumn`  
`class FVariablesOutlinerValueColumn : public ISceneOutlinerColumn`  
_L40-57_
- inherits: `ISceneOutlinerColumn`
- L43 _public prototype_ `static FName GetID();`
- L45 _public function_ `FVariablesOutlinerValueColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L50 _public function_ `virtual FName GetColumnID() override` — ISceneOutlinerColumn interface
- L51 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L52 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L53 _public function_ `virtual bool SupportsSorting() const override`
- L56 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)
- L16 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerCommands.h` (Private)


#### class `FVariablesOutlinerCommands`  
`class FVariablesOutlinerCommands : public TCommands<FVariablesOutlinerCommands>`  
_L10-23_
- inherits: `TCommands<FVariablesOutlinerCommands>`
- L14 _public function_ `FVariablesOutlinerCommands() : TCommands<FVariablesOutlinerCommands>( TEXT("VariablesOutliner"), LOCTEXT("VariablesOutlinerCommands", "Variables Outliner Commands"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L18 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> AddNewVariable;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AddNewVariables;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> CreateSharedVariablesAssets;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "VariablesOutlinerCommands"`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerEntryItem.h` (Private)


#### struct `UE::UAF::Editor::FVariablesOutlinerEntryItem`  
`struct FVariablesOutlinerEntryItem : FOutlinerEntryItem`  
_L14-60_
- inherits: `FOutlinerEntryItem`
- L16 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L25 _public prototype_ `FVariablesOutlinerEntryItem() = delete;`
- L26 _public prototype_ `FVariablesOutlinerEntryItem(const FVariablesOutlinerEntryItem::FItemData& InItemData);`
- L29 _public prototype_ `virtual bool IsValid() const override;`
- L30 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L31 _public prototype_ `virtual FString GetDisplayString() const override;`
- L32 _public function_ `virtual bool CanInteract() const override`
- L33 _public prototype_ `virtual FString GetPackageName() const override;`
- L37 _public prototype_ `virtual void Rename(const FText& InNewName) const override;` — Renames the item to the specified name
- L40 _public prototype_ `virtual bool ValidateName(const FText& InNewName, FText& OutErrorMessage) const override;` — Validates the new item name
- L42 _public prototype_ `virtual void SetAccessSpecifier(const EAnimNextExportAccessSpecifier& InSpecifier) const override;`
- L43 _public prototype_ `virtual EAnimNextExportAccessSpecifier GetAccessSpecifier() const override;`
- L44 _public prototype_ `virtual bool CanSetAccessSpecifier() const override;`
- L45 _public prototype_ `virtual FStringView GetCategoryPath() const override;`
- L46 _public prototype_ `virtual bool IsReadOnly() const override;`
- L48 _public function_ `bool HasStructOwner() const`
- L51 _public member_ `TWeakObjectPtr<UAnimNextVariableEntry> WeakEntry;` — Ptr to the underlying entry if this variable came from an asset
- L54 _public member_ `TWeakObjectPtr<const UUAFSharedVariablesEntry> WeakSharedVariablesEntry;` — The data interface entry this entry is from, if any
- L57 _public member_ `TFieldPath<const FProperty> PropertyPath;` — Ptr to the property if this variable came from a struct
- L59 _public member_ `bool bStructOwner = false;`

#### struct `UE::UAF::Editor::FVariablesOutlinerEntryItem::FItemData`  
`struct FItemData`  
_L18-23_
- L20 _public member_ `UAnimNextVariableEntry* Entry;`
- L21 _public member_ `const FProperty* Property;`
- L22 _public member_ `int32 SortValue;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerHierarchy.h` (Private)


#### class `UE::UAF::Editor::FVariablesOutlinerHierarchy`  
`class FVariablesOutlinerHierarchy : public FOutlinerHierarchy`  
_L15-27_
- inherits: `FOutlinerHierarchy`
- L18 _public prototype_ `FVariablesOutlinerHierarchy(ISceneOutlinerMode* Mode);`
- L19 _public prototype_ `FVariablesOutlinerHierarchy(const FVariablesOutlinerHierarchy&) = delete;`
- L20 _public prototype_ `FVariablesOutlinerHierarchy& operator=(const FVariablesOutlinerHierarchy&) = delete;`
- L23 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;`
- L26 _public prototype_ `virtual void CreateItemsForAsset(const UUAFRigVMAssetEditorData* EditorData, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerMode.h` (Private)


#### struct `FVariableClipboardData`  
`struct FVariableClipboardData`  
_L20-59_
- reflection: `USTRUCT()`
- L25 _public member_ `FSoftObjectPath SoftSourceObjectPath;` — `UPROPERTY()`
- L28 _public member_ `EAnimNextExportAccessSpecifier Access = EAnimNextExportAccessSpecifier::Private;` — `UPROPERTY()`
- L31 _public member_ `FName ParameterName;` — `UPROPERTY()`
- L34 _public member_ `FAnimNextParamType Type;` — `UPROPERTY()`
- L37 _public member_ `FAnimNextVariableBinding Binding;` — `UPROPERTY()`
- L40 _public member_ `FString Comment;` — `UPROPERTY()`
- L43 _public member_ `FString Category;` — `UPROPERTY()`
- L46 _public member_ `FString DefaultValue;` — `UPROPERTY()`
- L48 _public function_ `bool operator==(const FVariableClipboardData& Other) const`

#### struct `FVariablesOutlinerClipboardData`  
`struct FVariablesOutlinerClipboardData`  
_L62-74_
- reflection: `USTRUCT()`
- L67 _public member_ `TArray<FVariableClipboardData> Variables;` — `UPROPERTY()`
- L70 _public member_ `bool bCutOperation = false;` — `UPROPERTY()`
- L73 _public member_ `bool bCategorySelectedForOperation = false;` — `UPROPERTY()`

#### class `UE::UAF::Editor::FVariablesOutlinerMode`  
`class FVariablesOutlinerMode : public FCommonOutlinerMode`  
_L78-135_
- inherits: `FCommonOutlinerMode`
- L81 _public prototype_ `FVariablesOutlinerMode(SCommonOutliner* InOutliner, const TSharedRef<UE::Workspace::IWorkspaceEditor>& InWorkspaceEditor);`
- L84 _public prototype_ `virtual void HandleItemSelection(const FSceneOutlinerItemSelection& Selection) const override;`
- L85 _public prototype_ `virtual void RegisterToolMenus() override;`
- L86 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& InOutContext) const override;`
- L87 _public prototype_ `virtual void ReorderCategoryItem(TSharedPtr<FOutlinerCategoryItem> EntryItem, TSharedPtr<FOutlinerCategoryItem> BeforeItem) const override;`
- L88 _public prototype_ `virtual void ReorderCategory(const FString& CategoryName, const FString& BeforeCategoryName, UUAFRigVMAsset* Asset) const override;`
- L89 _public prototype_ `virtual void MoveCategoryToAsset(const FString& CategoryPath, UUAFRigVMAsset* FromAsset, UUAFRigVMAsset* ToAsset) const override;`
- L93 _public prototype_ `virtual void Rebuild() override;`
- L94 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L95 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& OutCommandList) override;`
- L96 _public prototype_ `virtual bool UpdateOperationDecorator(const FDragDropEvent& Event, const FSceneOutlinerDragValidationInfo* ValidationInfo) const override;`
- L97 _public prototype_ `static void PopulateNewVariableToolMenuEntries(UToolMenu* InMenu, bool bAddSeparator);`
- L99 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L104 _protected prototype_ `virtual void Rename() const override;` — QQ begin/end overrides
- L105 _protected prototype_ `virtual bool CanRename() const override;`
- L107 _protected prototype_ `virtual void Delete() const override;`
- L108 _protected prototype_ `virtual bool CanDelete() const override;`
- L110 _protected prototype_ `virtual void Copy() const override;`
- L111 _protected prototype_ `virtual bool CanCopy() const override;`
- L113 _protected prototype_ `virtual void Cut() const override;`
- L114 _protected prototype_ `virtual bool CanCut() const override;`
- L116 _protected prototype_ `virtual void Paste() const override;`
- L117 _protected prototype_ `virtual bool CanPaste() const override;`
- L119 _protected prototype_ `void CheckOverlappingVariableNamesRecursively(const UUAFRigVMAssetEditorData* EditorData, const TArray<FName>& BaseVariableNames, TMap<FName, FSoftObjectPath>& OutOverlappingVariableNames) const;`
- L120 _protected prototype_ `virtual void AddCategory(TWeakObjectPtr<UUAFRigVMAssetEditorData> InWeakEditorData) const override;`
- L122 _protected prototype_ `virtual void Duplicate() const override;`
- L123 _protected prototype_ `virtual bool CanDuplicate() const override;`
- L125 _protected prototype_ `virtual void FindReferences(ESearchScope InSearchScope) const override;`
- L126 _protected prototype_ `virtual bool CanFindReferences() const override;`
- L127 _protected prototype_ `virtual bool IsFindReferencesVisible(ESearchScope InSearchScope) const override;`
- L129 _protected prototype_ `bool IsAsset() const;`
- L131 _protected prototype_ `void CreateSharedVariablesAssets() const;`
- L132 _protected prototype_ `bool CanCreateSharedVariablesAssets() const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)
- L76 _namespace_ `namespace UE`
- L76 _namespace_ `namespace UAF` (scope `UE`)
- L76 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerRigVMAssetSharedVariablesItem.h` (Private)


#### struct `UE::UAF::Editor::FVariablesOutlinerRigVMAssetSharedVariablesItem`  
`struct FVariablesOutlinerRigVMAssetSharedVariablesItem : FOutlinerItem`  
_L16-32_
- inherits: `FOutlinerItem`
- L18 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L20 _public prototype_ `FVariablesOutlinerRigVMAssetSharedVariablesItem(const TScriptInterface<const IRigVMRuntimeAssetInterface>& InRigVMAsset);`
- L23 _public prototype_ `virtual bool IsValid() const override;`
- L24 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L25 _public prototype_ `virtual FString GetDisplayString() const override;`
- L26 _public function_ `virtual bool CanInteract() const override`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L28 _public prototype_ `virtual FString GetPackageName() const override;`
- L31 _public member_ `TScriptInterface<const IRigVMRuntimeAssetInterface> RigVMAsset;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/Outliner/VariablesOutlinerStructSharedVariablesItem.h` (Private)


#### struct `UE::UAF::Editor::FVariablesOutlinerStructSharedVariablesItem`  
`struct FVariablesOutlinerStructSharedVariablesItem : FOutlinerItem`  
_L15-31_
- inherits: `FOutlinerItem`
- L17 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L19 _public prototype_ `FVariablesOutlinerStructSharedVariablesItem(const TObjectPtr<const UScriptStruct> InStruct);`
- L22 _public prototype_ `virtual bool IsValid() const override;`
- L23 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L24 _public prototype_ `virtual FString GetDisplayString() const override;`
- L25 _public function_ `virtual bool CanInteract() const override`
- L26 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L27 _public prototype_ `virtual FString GetPackageName() const override;`
- L30 _public member_ `TObjectPtr<const UScriptStruct> Struct;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/SGraphPinVariableReference.h` (Private)


#### class `UE::UAF::Editor::SGraphPinVariableReference`  
`class SGraphPinVariableReference : public SGraphPin`  
_L24-62_
- inherits: `SGraphPin`
- desc: A pin widget that allows picking AnimNext variable references
- L26 _private function_ `SLATE_BEGIN_ARGS(SGraphPinVariableReference) : _GraphNode(nullptr)`
- L30 _private prototype_ `SLATE_ARGUMENT(UEdGraphNode*, GraphNode) SLATE_ARGUMENT(FAnimNextParamType, FilterType) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L39 _private prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L41 _private prototype_ `void UpdateCachedData();`
- L43 _private prototype_ `void HandleGraphModified(ERigVMGraphNotifType InType, URigVMGraph* InGraph, UObject* InSubject);`
- L45 _private member_ `UEdGraphNode* Node = nullptr;`
- L47 _private member_ `URigVMPin* ModelPin = nullptr;`
- L49 _private member_ `FAnimNextParamType FilterType;`
- L51 _private member_ `FAnimNextSoftVariableReference CachedVariableReference;`
- L53 _private member_ `FAnimNextParamType CachedType;`
- L55 _private member_ `TSharedPtr<SVariablePickerCombo> PickerCombo;`
- L57 _private member_ `TWeakObjectPtr<UUAFRigVMAsset> WeakFilterAsset;`
- L59 _private member_ `FOnIsContextSensitive OnIsContextSensitiveDelegate;`
- L61 _private member_ `bool bIsContextSensitive = true;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/SVariablePicker.h` (Private)


#### class `UE::UAF::Editor::SVariablePicker`  
`class SVariablePicker : public SCompoundWidget`  
_L21-99_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SVariablePicker)`
- L26 _public prototype_ `SLATE_ARGUMENT(FVariablePickerArgs, Args) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _private prototype_ `void RefreshEntries();`
- L35 _private prototype_ `bool GetFieldInfo(UE::PropertyViewer::SPropertyViewer::FHandle InHandle, const FFieldVariant& InField, FAnimNextSoftVariableReference& OutVariableReference, FAnimNextParamType& OutType) const;`
- L37 _private prototype_ `void HandleFieldPicked(UE::PropertyViewer::SPropertyViewer::FHandle InHandle, TArrayView<const FFieldVariant> InFields, ESelectInfo::Type InSelectionType);`
- L39 _private prototype_ `TSharedRef<SWidget> HandleGenerateContainer(UE::PropertyViewer::SPropertyViewer::FHandle InHandle, TOptional<FText> InDisplayName);`
- L43 _private prototype_ `bool IsDirectlyCompatible(const FAnimNextParamType& TestType) const;` — Returns true if TestType is directly compatible with any entry in Args.CompatibleTypes. Returns true unconditionally when CompatibleTypes is empty.
- L46 _private prototype_ `bool HasCompatibleLeaf(const UScriptStruct* Struct, TSet<const UScriptStruct*>& Visited) const;` — Returns true if Struct has any directly-compatible leaf at any depth.
- L51 _private member_ `FVariablePickerArgs Args;`
- L53 _private member_ `TSharedPtr<UE::PropertyViewer::SPropertyViewer> PropertyViewer;`
- L55 _private member_ `FText FilterText;`
- L57 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L77 _private member_ `} FieldExpander;`
- L79 _private member_ `TUniquePtr<FFieldIterator> FieldIterator;`
- L96 _private member_ `TArray<FContainerInfo> CachedContainers;`
- L98 _private member_ `TMap<UE::PropertyViewer::SPropertyViewer::FHandle, int32> ContainerMap;`

#### struct `UE::UAF::Editor::SVariablePicker::FFieldIterator`  
`struct FFieldIterator : UE::PropertyViewer::IFieldIterator`  
_L59-69_
- inherits: `UE::PropertyViewer::IFieldIterator`
- L61 _public prototype_ `FFieldIterator() = default;`
- L63 _public prototype_ `virtual TArray<FFieldVariant> GetFields(const UStruct* Struct, const FName FieldName, const UStruct* ContainerStruct) const override;`
- L65 _public member_ `TArray<FAnimNextParamType> CompatibleTypes;`
- L66 _public member_ `SVariablePicker* Outer = nullptr;`
- L67 _public member_ `const UStruct* CurrentStruct = nullptr;`
- L68 _public member_ `bool bAllowStructExpansion = false;`

#### struct `UE::UAF::Editor::SVariablePicker::FFieldExpander`  
`struct FFieldExpander : UE::PropertyViewer::IFieldExpander`  
_L71-77_
- inherits: `UE::PropertyViewer::IFieldExpander`
- L73 _public prototype_ `virtual TOptional<const UClass*> CanExpandObject(const FObjectPropertyBase* Property, const UObject* Instance) const override;`
- L74 _public prototype_ `virtual bool CanExpandScriptStruct(const FStructProperty* StructProperty) const override;`
- L75 _public prototype_ `virtual TOptional<const UStruct*> GetExpandedFunction(const UFunction* Function) const override;`
- L76 _public member_ `bool bAllowStructExpansion = false;`

#### struct `UE::UAF::Editor::SVariablePicker::FContainerInfo`  
`struct FContainerInfo`  
_L81-94_
- L83 _public function_ `FContainerInfo(const FText& InDisplayName, const FText& InTooltipText, const FAssetData& InAssetData, TUniquePtr<FInstancedPropertyBag>&& InPropertyBag) : DisplayName(InDisplayName) , TooltipText(InTooltipText) , PropertyBag(MoveTemp(InPropertyBag)) , AssetData(InAssetData)`
- L90 _public member_ `FText DisplayName;`
- L91 _public member_ `FText TooltipText;`
- L92 _public member_ `TUniquePtr<FInstancedPropertyBag> PropertyBag;`
- L93 _public member_ `FAssetData AssetData;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/SVariablesView.h` (Private)


#### class `UE::UAF::Editor::SVariablesView`  
`class SVariablesView : public SCompoundWidget`  
_L30-45_
- inherits: `SCompoundWidget`
- L32 _private function_ `SLATE_BEGIN_ARGS(SVariablesView)`
- L33 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<UE::Workspace::IWorkspaceEditor> InWorkspaceEditor);`
- L37 _private prototype_ `void SetExportDirectly(const FWorkspaceOutlinerItemExport& InExport) const;`
- L39 _private prototype_ `void HandleFocusedDocumentChanged(const UE::Workspace::FWorkspaceDocument& InDocument) const;`
- L40 _private prototype_ `void OnEditorDataModified(UUAFRigVMAssetEditorData* InEditorData, EAnimNextEditorDataNotifType InType, UObject* InSubject) const;`
- L44 _private member_ `TSharedPtr<SCommonOutliner> VariablesOutliner;`

#### struct `UE::UAF::Editor::FAnimNextVariablesTabSummoner`  
`struct FAnimNextVariablesTabSummoner : public FWorkflowTabFactory`  
_L47-59_
- inherits: `FWorkflowTabFactory`
- L50 _public prototype_ `FAnimNextVariablesTabSummoner(TSharedPtr<UE::Workspace::IWorkspaceEditor> InHostingApp);`
- L54 _private prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L55 _private prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L58 _private member_ `TSharedPtr<SVariablesView> VariablesView;` — The widget this tab spawner wraps

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Workspace` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L28 _externvar_ `extern const FLazyName VariablesTabName;` (scope `UE::UAF::Editor`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/UAFAssetDataPropertyCustomization.h` (Private)


#### class `FUAFAssetDataPropertyIdentifier`  
`class FUAFAssetDataPropertyIdentifier : public IPropertyTypeIdentifier`  
_L11-14_
- inherits: `IPropertyTypeIdentifier`
- L13 _private prototype_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& PropertyHandle) const override;`

#### class `FUAFAssetDataPropertyCustomization`  
`class FUAFAssetDataPropertyCustomization : public IPropertyTypeCustomization`  
_L16-30_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `FUAFAssetDataPropertyCustomization();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _private prototype_ `static bool ValidateAssetDataForDrop(UScriptStruct* BaseAssetType, const FAssetData& AssetData);`
- L29 _private prototype_ `static void TrySetAsset(TSharedPtr<IPropertyHandle> AssetPropertyHandle, const FAssetData& InAsset);`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/VariableBindingPropertyCustomization.h` (Private)


#### class `UE::UAF::Editor::FVariableBindingPropertyCustomization`  
`class FVariableBindingPropertyCustomization : public IPropertyTypeCustomization, public FNotifyHook`  
_L18-59_
- inherits: `IPropertyTypeCustomization,FNotifyHook`
- L22 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged) override;` — FNotifyHook interface
- L28 _private prototype_ `void OnBindingChanged();`
- L29 _private prototype_ `void Refresh();`
- L30 _private prototype_ `void OnEditorDataModified(ERigVMGraphNotifType NotifType, URigVMGraph* Graph, UObject* Subject, TWeakObjectPtr<UAnimNextVariableEntry> WeakEntry);`
- L32 _private prototype_ `void RequestRefresh();`
- L35 _private prototype_ `static FText GetBindingDisplayNameText(TConstStructView<FAnimNextVariableBindingData> InBindingData);` — Gets a name to display for a variable binding in the editor
- L38 _private prototype_ `static FText GetBindingTooltipText(TConstStructView<FAnimNextVariableBindingData> InBindingData);` — Gets a name to display for a variable binding's tooltip in the editor
- L41 _private prototype_ `static bool ValidateBinding(TConstStructView<FAnimNextVariableBindingData> InBindingData);` — Checks a binding for validity in the editor
- L44 _private prototype_ `TSharedRef<SWidget> CreateBindingWidget() const;` — Create a binding widget
- L47 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L48 _private member_ `TSharedPtr<IPropertyHandle> BindingDataHandle;`
- L49 _private member_ `FAnimNextParamType Type;`
- L50 _private member_ `FText NameText;`
- L51 _private member_ `FText TooltipText;`
- L52 _private member_ `const FSlateBrush* Icon = nullptr;`
- L53 _private member_ `FSlateColor IconColor = FLinearColor::Gray;`
- L54 _private member_ `TSharedPtr<SWidget> ValueWidget;`
- L55 _private member_ `TSharedPtr<SWidget> ContainerWidget;`
- L56 _private member_ `bool bIsBindingValid = false;`
- L57 _private member_ `bool bRefreshRequested = false;`
- L58 _private member_ `bool bShowBindingSelector = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/VariableCustomization.h` (Private)


#### class `UE::UAF::Editor::FVariableCustomization`  
`class FVariableCustomization : public IDetailCustomization`  
_L16-51_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `FVariableCustomization();`
- L23 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Called when details should be customized
- L29 _private prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;` — Called when details should be customized, this version allows the customization to store a weak ptr to the layout builder. This allows property changes to trigger a force refresh of the detail panel.
- L31 _private prototype_ `FText GetName() const;`
- L32 _private prototype_ `void SetName(const FText& InNewText, ETextCommit::Type InCommitType);`
- L33 _private prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L35 _private prototype_ `FText GetCategory() const;`
- L36 _private prototype_ `void SetCategory(const FText& InNewCategory, ETextCommit::Type InCommitType);`
- L37 _private prototype_ `bool OnVerifyCategoryName(const FText& InText, FText& OutErrorMessage);`
- L38 _private prototype_ `void OnCategorySelectionChanged(TSharedPtr<FText> ProposedSelection, ESelectInfo::Type);`
- L39 _private prototype_ `void PopulateCategories();`
- L40 _private prototype_ `void SetCategory(const FString& CategoryName);`
- L42 _private member_ `TSharedPtr<SListView<TSharedPtr<FText>>> CategoryListView;`
- L43 _private member_ `TSharedPtr<SComboButton> CategoryComboButton;`
- L44 _private member_ `TArray<TSharedPtr<FText>> Categories;`
- L46 _private member_ `TArray<TWeakObjectPtr<UAnimNextVariableEntry>> Variables;`
- L47 _private member_ `TWeakObjectPtr<UUAFRigVMAsset> OuterRigVMAsset;`
- L49 _private member_ `TWeakPtr<IDetailLayoutBuilder> WeakLayoutBuilder;`
- L50 _private member_ `FString DefaultCategoryName;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/VariableOverrideCommands.h` (Private)


#### class `UE::UAF::FVariableOverrideCommands`  
`class FVariableOverrideCommands : public TCommands<FVariableOverrideCommands>`  
_L11-21_
- inherits: `TCommands<FVariableOverrideCommands>`
- desc: The Commands for the variable overrides menu
- L14 _public prototype_ `FVariableOverrideCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> OverrideVariable;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> ResetPropertyToDefault;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ClearOverride;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/VariableReferencePropertyCustomization.h` (Private)


#### class `UE::UAF::Editor::FVariableReferencePropertyCustomization`  
`class FVariableReferencePropertyCustomization : public IPropertyTypeCustomization`  
_L17-45_
- inherits: `IPropertyTypeCustomization`
- L20 _protected prototype_ `virtual void SetValue(const FAnimNextSoftVariableReference& InVariableReference, void* InValue) const;`
- L21 _protected prototype_ `virtual FAnimNextSoftVariableReference GetValue(const void* InValue) const;`
- L25 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L26 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _private prototype_ `void UpdateCachedData();`
- L30 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L32 _private member_ `FAnimNextSoftVariableReference CachedVariableReference;`
- L34 _private member_ `FAnimNextParamType CachedType;`
- L36 _private member_ `FAnimNextParamType FilterType;`
- L38 _private member_ `TArray<TWeakObjectPtr<const UUAFRigVMAsset>> FilterAssets;`
- L40 _private member_ `FOnIsContextSensitive OnIsContextSensitiveDelegate;`
- L42 _private member_ `bool bIsContextSensitive = true;`
- L44 _private member_ `bool bMultipleValues = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Workspace/AnimNextWorkspaceEditorMode.h` (Private)


#### class `UAnimNextWorkspaceEditorMode`  
`class UAnimNextWorkspaceEditorMode : public UEdMode`  
_L32-103_
- reflection: `UCLASS(Transient)`
- inherits: `UEdMode`
- L37 _public member_ `const static FEditorModeID EM_AnimNextWorkspace;`
- L39 _public prototype_ `UAnimNextWorkspaceEditorMode();`
- L42 _public function_ `UE::UAF::Editor::ECompileStatus GetLatestCompileStatus() const` — Get the current compilation status
- L45 _public function_ `const FAnimNextWorkspaceState& GetState() const` — Get the currently stored workspace state
- L47 _public prototype_ `TSharedPtr<UE::UAF::Editor::FRewindDebuggerWorkspaceExtension> GetRewindDebuggerExtension();`
- L49 _public prototype_ `TSharedPtr<UE::UAF::Editor::IDebugObjectSelector> GetDebugObjectSelector();`
- L51 _public prototype_ `bool IsAutoCompileChecked() const;`
- L55 _private function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override` — UEdMode interface
- L56 _private prototype_ `virtual void Enter() override;`
- L57 _private prototype_ `virtual void Exit() override;`
- L58 _private prototype_ `virtual void BindCommands() override;`
- L59 _private function_ `virtual bool UsesToolkits() const override`
- L60 _private prototype_ `void HandleCompile();`
- L61 _private prototype_ `bool CanCompile() const;`
- L62 _private prototype_ `void HandleAutoCompile();`
- L65 _private prototype_ `void UpdateCompileStatus();` — Updates the compile status. Scans all opened assets in the workspace.
- L68 _private prototype_ `void HandleRigVMCompiledEvent(UObject* InAsset, URigVM* InVM, FRigVMExtendedExecuteContext& InExtendedExecuteContext);` — Handle an asset in the workspace getting compiled
- L71 _private prototype_ `void HandleRigVMModifiedEvent(ERigVMGraphNotifType InType, URigVMGraph* InGraph, UObject* InSubject, TWeakObjectPtr<UUAFRigVMAssetEditorData> WeakEditorData);` — Handle an asset getting modified
- L74 _private prototype_ `void HandleFocusedDocumentChanged(const UE::Workspace::FWorkspaceDocument& InDocument);` — Handle the document focus changing
- L76 _private prototype_ `TSharedPtr<UE::Workspace::IWorkspaceEditor> GetWorkspaceEditor() const;`
- L79 _private prototype_ `TSharedPtr<UE::UAF::Editor::IAssetCompilationHandler> GetAssetCompiler(UObject* InAsset);` — Lazily construct an asset compiler for the supplied asset
- L81 _private prototype_ `void GetDebugObjects(TArray<UObject*>& OutObjects);`
- L86 _private member_ `FAnimNextWorkspaceState State;`
- L89 _private member_ `TMap<FObjectKey, TSharedRef<UE::UAF::Editor::IAssetCompilationHandler>> AssetCompilers;` — Asset compilers for all current assets
- L92 _private member_ `TSet<TObjectKey<UObject>> WeakAssets;` — All assets that we are currently tracking for compilation status
- L95 _private member_ `UE::UAF::Editor::ECompileStatus CompileStatus = UE::UAF::Editor::ECompileStatus::Unknown;` — Current compilation status
- L97 _private member_ `TSharedPtr<UE::UAF::Editor::FRewindDebuggerWorkspaceExtension> RewindDebuggerExtension;`
- L99 _private member_ `TSharedPtr<UE::UAF::Editor::IDebugObjectSelector> DebugObjectSelector;`
- L102 _private member_ `TSharedPtr<SWidget> UAFBrowserStatusbarWidget = nullptr;` — UAF browser status bar widget, used to store a custom drawer next to the content browser

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Workspace` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Workspace/AnimNextWorkspaceSchema.h` (Private)


#### class `UAnimNextWorkspaceSchema`  
`class UAnimNextWorkspaceSchema : public UWorkspaceSchema`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UWorkspaceSchema`
- desc: Workspace schema allowing all asset types
- L17 _private prototype_ `virtual FText GetDisplayName() const override;` — UWorkspaceSchema interface
- L18 _private prototype_ `virtual TConstArrayView<FTopLevelAssetPath> GetSupportedAssetClassPaths() const override;`
- L19 _private prototype_ `virtual void OnSaveWorkspaceState(TSharedRef<UE::Workspace::IWorkspaceEditor> InWorkspaceEditor, FInstancedStruct& OutWorkspaceState) const override;`
- L20 _private prototype_ `virtual void OnLoadWorkspaceState(TSharedRef<UE::Workspace::IWorkspaceEditor> InWorkspaceEditor, const FInstancedStruct& InWorkspaceState) const override;`
- L21 _private function_ `virtual bool SupportsViewport() const`
- L22 _private function_ `virtual TObjectPtr<UWorkspaceViewportSceneDescription> CreateSceneDescription() const`
- L23 _private function_ `virtual bool SupportsMultipleAssets() const`
- L24 _private function_ `virtual bool HasPersistentRootAsset() const`
- L25 _private function_ `virtual bool CanSaveWorkspace() const`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Workspace/AnimNextWorkspaceState.h` (Private)


#### struct `FAnimNextWorkspaceState`  
`struct FAnimNextWorkspaceState`  
_L9-12_
- reflection: `USTRUCT()`
- desc: Custom persistent workspace state

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/AssetCompilationHandler.h` (Public)


#### class `UE::UAF::Editor::FAssetCompilationHandler`  
`class FAssetCompilationHandler : public IAssetCompilationHandler`  
_L14-25_
- inherits: `IAssetCompilationHandler`
- desc: Asset compiler that can compile assets based on UUAFRigVMAsset
- L17 _public prototype_ `explicit FAssetCompilationHandler(const UObject* InAsset);`
- L21 _protected prototype_ `virtual void Compile(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, UObject* InAsset) override;` — IAssetCompilationHandler interface
- L22 _protected prototype_ `virtual void SetAutoCompile(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, UObject* InAsset, bool bInAutoCompile) override;`
- L23 _protected prototype_ `virtual bool GetAutoCompile(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, const UObject* InAsset) const override;`
- L24 _protected prototype_ `virtual ECompileStatus GetCompileStatus(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, const UObject* InAsset) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UAFEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/Common/AssetPreview/IUAFAssetPreview.h` (Public)


#### struct `UE::UAF::Editor::FUAFAssetPreviewFactory`  
`struct FUAFAssetPreviewFactory`  
_L40-51_
- desc: Experimental. May be removed whenever we switch to the future generic content browser IAssetPreviewCustomization API. Base struct for factories that can create IUAFAssetPreview widgets. @TODO: Reconsider the type constraint. It is okay but some factories may support multiple types. Should we allow for multiple factories for the same type based on a priority system?
- L45 _public prototype_ `virtual TSharedRef<IUAFAssetPreview> CreateAssetPreviewWidget(TSharedPtr<FAssetEditorToolkit> InAssetEditorToolkit, const FAssetData& InAssetData) const = 0;` — Callback used to create the preview for the given asset data.
- L48 _public prototype_ `virtual const UStruct* GetPreviewType() const = 0;` — Get the preview type this factory is used for.
- L50 _public prototype_ `virtual ~FUAFAssetPreviewFactory() = default;`

#### class `UE::UAF::Editor::IUAFAssetPreview`  
`class IUAFAssetPreview : public SCompoundWidget`  
_L62-128_
- inherits: `SCompoundWidget`
- desc: Experimental. May be removed whenever we switch to the future generic content browser IAssetPreviewCustomization API. Base class for asset preview widgets. Currently previews are restricted to UAF, but may not be in the future. @TODO: This class currently supports individual async loading, but users may want to async preload a set of assets for responsiveness. @TODO: Once we use the future content browser API, consider removing the "UAF" aspect of this class. Maybe move to engine as IAsyncAssetPreview? Need editor buy in first.
- L66 _public function_ `SLATE_BEGIN_ARGS(IUAFAssetPreview)`
- L67 _public prototype_ `SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs, TSharedPtr<FAssetEditorToolkit> InAssetEditorToolkit, const FAssetData& InAssetData);`
- L77 _public prototype_ `virtual void OnSameTypeAssetSelectedAsync(const FAssetData& InAssetData);` — Callback for when another asset of the same type is selected. Will load the asset async before updating preview. When different assets are selected this preview should be replaced.
- L80 _public prototype_ `virtual const UStruct* GetAssetPreviewType() const = 0;` — Utility method to get the current preview type this widget is associated with.
- L83 _public prototype_ `virtual void RequestAsyncLoad(const FSoftObjectPath& SoftObject, TFunction<void()>&& Callback);` — Utility method to load an asset async with function callback
- L86 _public prototype_ `virtual void RequestAsyncLoad(const FSoftObjectPath& SoftObject, FStreamableDelegate DelegateToCall);` — Utility method to load an asset async with a delegate callback
- L89 _public prototype_ `virtual void CancelAsyncLoad();` — Utility method to cancel async load of asset to preview
- L98 _protected prototype_ `virtual bool OnSameTypeAssetSelected(const FAssetData& InAssetData) = 0;` — Callback for when another asset of the same type is selected & loaded. @return True if we were able to set up a valid preview for the given asset
- L101 _protected prototype_ `virtual void OnConstructAsyncPreviewWidget(const FAssetData& InAssetData);` — Called to show a loading widget when the asset is loading, and a preview widget when the asset is done loading.
- L104 _protected prototype_ `virtual TSharedRef<SWidget> OnConstructLoadingAssetPreviewWidget();` — Callback used to construct preview widget when async loading is occuring. Results should be stored in CachedLoadingAssetPreviewWidget.
- L110 _protected prototype_ `virtual TSharedRef<SWidget> OnConstructAssetPreviewWidget();` — Callback used to construct preview widget whenever async loading is done or an asset is already loaded. Implementers are encouraged to cache their results on first create to avoid widget recreation overhead.
- L115 _protected member_ `TWeakPtr<FAssetEditorToolkit> AssetEditorToolkitPtr;` — Pointer back to the editor that owns us
- L118 _protected member_ `FAssetData CachedCurrentAssetData;` — Last asset data previewed by this widget
- L121 _protected member_ `TSharedPtr<FStreamableHandle> StreamingHandle;` — Handle for currently streaming asset, we load assets async for previews by default.
- L124 _protected member_ `FSoftObjectPath StreamingObjectPath;` — Path for currently streaming asset
- L127 _protected member_ `TSharedPtr<SWidget> CachedLoadingAssetPreviewWidget;` — Cached loading widget. Saved so we can communicate with it and don't need to re-create it uncessarily.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UAFEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace UAF` (scope `UE`)
- L28 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/Common/AssetPreview/IUAFAssetViewportPreview.h` (Public)


#### class `UE::UAF::Editor::IUAFAssetViewportPreview`  
`class IUAFAssetViewportPreview : public IUAFAssetPreview`  
_L29-66_
- inherits: `IUAFAssetPreview`
- desc: Experimental. May be removed / relocated whenever we switch to the future generic content browser IAssetPreviewCustomization API. Base class for asset previews that want to use an viewport and don't want to roll their own viewport implementation @TODO: Same consideration as above. Later on consider removing "UAF" aspect from this.
- L35 _protected prototype_ `virtual TSharedRef<SWidget> OnConstructAssetPreviewWidget() override;`
- L49 _protected prototype_ `virtual void OnCustomizePreviewScene(FAdvancedPreviewScene& InPreviewScene, FEditorViewportClient& InEditorViewportClient) = 0;` — Require child classes to customize preview scene / viewport. These are passed together as viewport customizations may depend on the preview scene. Note: Params are passed for convience. They are technically not needed since child classes have access. @param InPreviewScene - Same as our local preview scene. Implementation should set this up to some meaningful asset preview. @param InEditorViewportClient - Viewport client for camera setup and other controls.
- L54 _protected member_ `TSharedPtr<UE::Workspace::SWorkspaceViewport> ViewportWidget;` — The actual viewport widget. Used as cached result for OnConstructAssetPreviewWidget.
- L57 _protected member_ `TSharedPtr<FSceneViewport> SceneViewport;` — The scene viewport data
- L60 _protected member_ `TUniquePtr<FAdvancedPreviewScene> PreviewScene;` — The scene to show in the asset previews
- L65 _protected prototype_ `virtual EActiveTimerReturnType UpdatePreviewWorld(double InCurrentTime, float InDeltaTime);` — Callback to tick the preview world

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UAFEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/Common/AssetPreview/UAFAssetPreviewFactorySubsystem.h` (Public)


#### class `UUAFAssetPreviewFactorySubsystem`  
`class UUAFAssetPreviewFactorySubsystem : public UEditorSubsystem`  
_L26-46_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UEditorSubsystem`
- desc: Experimental & Intended for removal. This class associates asset types to preview widgets for the UAF browser. However it is intended to be replaced with a future API within the editor / content browser that does the same. See: IUAFAssetPreview.h for more future design considerations.
- L37 _public prototype_ `bool AddAssetPreviewFactory(TSharedPtr<UE::UAF::Editor::FUAFAssetPreviewFactory> InFactory);` — Method to associate a preview factory with some type. For now only supports one factory per type. @return True if the factory was added for the type, false if we already have a type for it
- L40 _public prototype_ `const TSharedPtr<UE::UAF::Editor::FUAFAssetPreviewFactory> GetAssetPreviewFactory(const UStruct* InPreviewType) const;` — Get a Factory for the given type, or nullptr if no factory exists.
- L45 _private member_ `TMap<const UStruct*, TSharedPtr<UE::UAF::Editor::FUAFAssetPreviewFactory>> AssetTypeFactoryMap;` — Map of classes to preview factories

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UAFEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/FindInAnimNextRigVMAsset.h` (Public)


#### class `UE::UAF::Editor::FFindInAnimNextRigVMAssetResult`  
`class FFindInAnimNextRigVMAssetResult : public FFindInGraphResult`  
_L15-24_
- inherits: `FFindInGraphResult`
- desc: Item that matched the search results
- L19 _public prototype_ `FFindInAnimNextRigVMAssetResult(const FFindInGraphResult::FCreateParams& InCreateParams);`
- L22 _public prototype_ `virtual void JumpToNode(TWeakPtr<FAssetEditorToolkit> AssetEditorToolkit, const UEdGraphNode* InNode) const override;`

#### class `UE::UAF::Editor::SFindInAnimNextRigVMAsset`  
`class SFindInAnimNextRigVMAsset : public SFindInGraph`  
_L28-38_
- inherits: `SFindInGraph`
- desc: Widget for searching for items that are part of a AnimNextRigVMAsset Graph
- L34 _protected prototype_ `virtual TSharedPtr<FFindInGraphResult> MakeSearchResult(const FFindInGraphResult::FCreateParams& InParams) override;`
- L35 _protected prototype_ `virtual void MatchTokens(const TArray<FString>& Tokens) override;`
- L36 _protected prototype_ `virtual bool MatchTokensInNode(const UEdGraphNode* Node, const TArray<FString>& Tokens) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UAF` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/IAnimNextEditorModule.h` (Public)


#### class `UE::UAF::Editor::IAnimNextEditorModule`  
`class IAnimNextEditorModule : public IModuleInterface`  
_L38-94_
- inherits: `IModuleInterface`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FCollectGraphMenuActionsMulticast, const TWeakPtr<UE::Workspace::IWorkspaceEditor>& , FGraphContextMenuBuilder& , const FActionMenuContextData& );`
- L42 _public typedef_ `typedef FCollectGraphMenuActionsMulticast::FDelegate FOnCollectGraphMenuActionsDelegate;`
- L44 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNodeDblClickNotificationMulticast, const UE::Workspace::FWorkspaceEditorContext& , const UEdGraphNode* );`
- L45 _public typedef_ `typedef FNodeDblClickNotificationMulticast::FDelegate FNodeDblClickNotificationDelegate;`
- L49 _public prototype_ `virtual void RegisterLocatorFragmentEditorType(FName InLocatorFragmentEditorName) = 0;` — Register a valid fragment type name to be used with parameter UOLs @param InLocatorFragmentEditorName The name of the locator fragment editor
- L53 _public prototype_ `virtual void UnregisterLocatorFragmentEditorType(FName InLocatorFragmentEditorName) = 0;` — Unregister a valid fragment type name to be used with parameter UOLs @param InLocatorFragmentEditorName The name of the locator fragment editor
- L57 _public prototype_ `virtual void AddWorkspaceSupportedAssetClass(const FTopLevelAssetPath& InClassAssetPath) = 0;` — Add a UClass path to the set of classes which can be opened within an AnimNext Workspace @param InClassAssetPath Asset path for to-be-registered Class
- L61 _public prototype_ `virtual void RemoveWorkspaceSupportedAssetClass(const FTopLevelAssetPath& InClassAssetPath) = 0;` — Remove a UClass path to the set of classes which can be opened within an AnimNext Workspace @param InClassAssetPath Asset path for to-be-unregistered Class
- L66 _public prototype_ `virtual FDelegateHandle RegisterGraphMenuActionsProvider(const FOnCollectGraphMenuActionsDelegate& InCollectDelegate) = 0;` — Register a graph context menu actions provider @param InCollectDelegate Delegate to add @return FDelegateHandle
- L70 _public prototype_ `virtual void UnregisterGraphMenuActionsProvider(const FDelegateHandle& InDelegateHandle) = 0;` — Unregister a graph context menu actions provider @param InDelegateHandle Handle of the delegate to remove
- L75 _public prototype_ `virtual void RegisterAssetCompilationHandler(const FTopLevelAssetPath& InClassPath, FAssetCompilationHandlerFactoryDelegate InAssetCompilationHandlerFactory) = 0;` — Register an asset compilation handler @param InClassPath The path of the asset's class @param InAssetCompilerFactory A factory function used to make an asset compiler for an asset
- L79 _public prototype_ `virtual void UnregisterAssetCompilationHandler(const FTopLevelAssetPath& InClassPath) = 0;` — Unregister an asset compilation handler @param InClassPath The path of the asset's class
- L83 _public prototype_ `virtual FDelegateHandle RegisterNodeDblClickHandler(const FNodeDblClickNotificationDelegate& InNodeDblClickNotificationDelegate) = 0;` — Register a node double click notifications handler @param InGraphNodeActionsHandler Handler interface to register
- L87 _public prototype_ `virtual void UnregisterNodeDblClickHandler(const FDelegateHandle& InDelegateHandle) = 0;` — Unregister a node double click notifications handler @param InDelegateHandle Handle of the delegate to remove
- L90 _public prototype_ `virtual void EnableAssetWizard() = 0;` — Adds the UAF asset wizard to the content browser asset menu
- L93 _public prototype_ `virtual void DisableAssetWizard() = 0;` — Removes the UAF asset wizard from the content browser asset menu

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)
- L20 _typedef_ `typedef TSet<class UObject*> FGraphPanelSelectionSet;`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L25 _variable_ `const FLazyName CompilerResultsTabName("Com` (scope `UE::UAF::Editor`)
- L26 _variable_ `const FLazyName LogListingName("Ani` (scope `UE::UAF::Editor`)
- L27 _variable_ `const FLazyName FindTabName("Fin` (scope `UE::UAF::Editor`)
- L28 _variable_ `const FLazyName FindAndReplaceTabName("Fin` (scope `UE::UAF::Editor`)
- L29 _variable_ `const FLazyName UAFBrowserTabName("UAF` (scope `UE::UAF::Editor`)
- L36 _typedef_ `using FAssetCompilationHandlerFactoryDelegate = TDelegate<TSharedRef<IAssetCompilationHandler>(UObject*)>;` (scope `UE::UAF::Editor`) — A factory function used to make an asset compilation handler for an asset
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FCollectGraphMenuActionsMulticast, const TWeakPtr<UE::Workspace::IWorkspaceEditor>& , FGraphContextMenuBuilder& , const FActionMenuContextData& );`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNodeDblClickNotificationMulticast, const UE::Workspace::FWorkspaceEditorContext& , const UEdGraphNode* );`

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/IAssetCompilationHandler.h` (Public)


#### enum `UE::UAF::Editor::ECompileStatus`  
`enum class ECompileStatus : uint8`  
_L16-23_
- desc: Status of compilation. Order matters - status is compared by magnitude to indicate severity
- L18 _public enumerator_ `Unknown`
- L19 _public enumerator_ `UpToDate`
- L20 _public enumerator_ `Dirty`
- L21 _public enumerator_ `Warning`
- L22 _public enumerator_ `Error`

#### class `UE::UAF::Editor::IAssetCompilationHandler`  
`class IAssetCompilationHandler : public TSharedFromThis<IAssetCompilationHandler>`  
_L25-47_
- inherits: `TSharedFromThis<IAssetCompilationHandler>`
- L28 _public prototype_ `virtual ~IAssetCompilationHandler() = default;`
- L31 _public prototype_ `virtual void Compile(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, UObject* InAsset) = 0;` — Called to compile an asset from the editor
- L34 _public function_ `virtual void SetAutoCompile(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, UObject* InAsset, bool bInAutoCompile)` — Called to set the auto compile mode of the asset
- L37 _public function_ `virtual bool GetAutoCompile(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, const UObject* InAsset) const` — Called to get the auto compile mode of the asset
- L40 _public function_ `virtual ECompileStatus GetCompileStatus(TSharedRef<Workspace::IWorkspaceEditor> InWorkspaceEditor, const UObject* InAsset) const` — Called to get the compile status of the asset
- L43 _public function_ `FSimpleDelegate& OnCompileStatusChanged()` — Called to notify that the compile status of the asset may have changed
- L46 _private member_ `FSimpleDelegate CompileStatusChangedDelegate;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Workspace` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/UAF/Viewport/ViewportSceneDescription.h` (Public)


#### class `UUAFViewportSceneDescription`  
`class UUAFViewportSceneDescription : public UWorkspaceViewportSceneDescription`  
_L20-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorkspaceViewportSceneDescription`
- L25 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L31 _public member_ `TObjectPtr<UPreviewMeshCollection> AdditionalMeshes;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)

### `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Public/Variables/SVariablePickerCombo.h` (Public)


#### class `UE::UAF::Editor::SVariablePickerCombo`  
`class SVariablePickerCombo : public SCompoundWidget`  
_L28-97_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(SVariablePickerCombo)`
- L34 _public prototype_ `SLATE_ARGUMENT(FVariablePickerArgs, PickerArgs) SLATE_EVENT(FOnGetVariableReference, OnGetVariableReference) SLATE_EVENT(FOnGetVariableType, OnGetVariableType) SLATE_ATTRIBUTE(FText, VariableName) SLATE_ATTRIBUTE(FText, VariableTooltip) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Arguments for configuring the picker in the dropdown menu
- L53 _private prototype_ `void RequestRefresh();`
- L56 _private member_ `FOnGetVariableReference OnGetVariableReferenceDelegate;` — Retrieves the variable reference to display
- L59 _private member_ `FOnGetVariableType OnGetVariableTypeDelegate;` — Retrieves the variable type to display
- L62 _private member_ `FEdGraphPinType PinType;` — Cached pin type
- L65 _private member_ `FAnimNextSoftVariableReference CachedVariableReference;` — Cached variable reference
- L68 _private member_ `TAttribute<FText> VariableName;` — Attribute for variable name
- L71 _private member_ `TAttribute<FText> VariableTooltip;` — Attribute for variable tooltip
- L74 _private member_ `FText CachedVariableNameText;` — Cached display name
- L77 _private member_ `FText CachedVariableNameTooltipText;` — Cached tooltip
- L80 _private member_ `FAnimNextParamType VariableType;` — Cached variable type
- L83 _private member_ `const FSlateBrush* Icon = nullptr;` — Cached icon
- L86 _private member_ `FSlateColor IconColor = FLinearColor::Gray;` — Cached color
- L89 _private member_ `TWeakPtr<SVariablePicker> PickerWidget;` — Picker widget used to focus after the popup is displayed
- L92 _private member_ `FVariablePickerArgs PickerArgs;` — Arguments for the picker popup
- L94 _private member_ `bool bRefreshRequested = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::UAF`)
- L23 _typedef_ `using FOnGetVariableReference = TDelegate<FAnimNextSoftVariableReference()>;` (scope `UE::UAF::Editor`) — Retrieves the variable reference to display
- L26 _typedef_ `using FOnGetVariableType = TDelegate<FAnimNextParamType()>;` (scope `UE::UAF::Editor`) — Retrieves the variable type to display
